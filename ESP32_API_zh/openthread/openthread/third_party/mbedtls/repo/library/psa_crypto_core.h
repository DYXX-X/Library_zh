/*
 *  PSA加密核心内部接口
 */
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_CORE_H
#define PSA_CRYPTO_CORE_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "psa/crypto.h"
#include "psa/crypto_se_driver.h"

/** 表示密钥槽的数据结构，包含一个密钥的密钥材料和元数据。
 */
typedef struct
{
    psa_core_key_attributes_t attr;

    /*
     * 库持有的钥匙槽上的锁数。
     *
     * 每当库函数通过一个专用的内部API检索到一个指向密钥槽的指针时，此计数器将递增一。
     *
     * 每当库函数停止访问密钥槽并通过调用psa_nlock_key_slot（）API对其进行声明时，此计数器将减1。
     *
     * 此计数器用于防止在库可以访问钥匙槽时重置钥匙槽。例如，在以下情况下需要这样的控制：。如果出现密钥槽饥饿，所有密钥槽都包含密钥的描述，并且库要求描述密钥槽中不存在的持久密钥，则无法回收库当前访问的密钥槽以释放密钥槽以加载持久密钥。在多线程应用程序中，当库通过另一个线程使用密钥时，一个线程请求关闭、清除或销毁该密钥。
     */
    size_t lock_count;

    union
    {
        /* 动态分配的密钥数据缓冲区。在psa_export_key（）中指定的格式。*/
        struct key_data
        {
            uint8_t *data;
            size_t bytes;
        } key;
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
        /* 安全元素中的任何密钥类型*/
        struct se
        {
            psa_key_slot_number_t slot_number;
        } se;
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */
    } data;
} psa_key_slot_t;

/* 仅在内部使用的关键属性标志掩码。目前没有。*/
#define PSA_KA_MASK_INTERNAL_ONLY (     \
        0 )

/** 测试钥匙槽是否被占用。
 *
 * 如果密钥类型为非零，则会占用密钥槽。这是因为任何有效的密钥都不能将0作为其密钥类型。
 *
 * \param[in]slot要测试的密钥槽。
 *
 * \如果插槽被占用，则返回1，否则返回0。
 */
static inline int psa_is_key_slot_occupied( const psa_key_slot_t *slot )
{
    return( slot->attr.type != 0 );
}

/** 测试钥匙槽是否锁定。
 *
 * 如果钥匙槽的锁计数器严格大于0，则钥匙槽被锁定。
 *
 * \param[in]slot要测试的密钥槽。
 *
 * \如果插槽被锁定，则返回1，否则返回0。
 */
static inline int psa_is_key_slot_locked( const psa_key_slot_t *slot )
{
    return( slot->lock_count > 0 );
}

/** 从psa_key_slot_t:：attr:：core:：flags中检索标志。
 *
 * \param[in]slot要查询的密钥槽。\param mask要提取的位掩码。
 *
 * \return给定槽中的键属性标志，按位和\p掩码。
 */
static inline uint16_t psa_key_slot_get_flags( const psa_key_slot_t *slot,
                                               uint16_t mask )
{
    return( slot->attr.flags & mask );
}

/** 在psa_key_slot_t:：attr:：core:：flags中设置标志。
 *
 * \param[in，out]slot要修改的密钥槽。\param mask要修改的位掩码。\param value选定位的新值。
 */
static inline void psa_key_slot_set_flags( psa_key_slot_t *slot,
                                           uint16_t mask,
                                           uint16_t value )
{
    slot->attr.flags = ( ( ~mask & slot->attr.flags ) |
                              ( mask & value ) );
}

/** 启用psa_key_slot_t:：attr:：core:：flags中的标志。
 *
 * \param[in，out]slot要修改的密钥槽。\param mask要设置的位掩码。
 */
static inline void psa_key_slot_set_bits_in_flags( psa_key_slot_t *slot,
                                                   uint16_t mask )
{
    slot->attr.flags |= mask;
}

/** 关闭psa_key_slot_t:：attr:：core:：flags中的标志。
 *
 * \param[in，out]slot要修改的密钥槽。\param mask要清除的位掩码。
 */
static inline void psa_key_slot_clear_bits( psa_key_slot_t *slot,
                                            uint16_t mask )
{
    slot->attr.flags &= ~mask;
}

/** 彻底清除内存中的插槽，包括其策略。
 *
 * 永久存储不受影响。
 *
 * \param[in，out]slot要擦除的密钥槽。
 *
 * \retval#PSA_SUCCESS成功。这包括已经完全擦除的钥匙槽的情况。\retval#PSA_ERROR_CORRUPTION_DETECTED
 */
psa_status_t psa_wipe_key_slot( psa_key_slot_t *slot );

/** 将密钥数据（以导出格式）复制到空密钥槽中。
 *
 * 此函数假定插槽尚未包含任何密钥材料。失败时，插槽内容不变。
 *
 * \param[in，out]slot要将密钥复制到的密钥槽。\param[in]包含密钥材料的数据缓冲区。\param data_length密钥缓冲区的大小。
 *
 * \retval#PSA_SUCCESS密钥已成功复制。\retval#PSA_ERROR_INSUFFIE_MEMORY没有足够的内存用于分配复制缓冲区。\retval#PSA_ERROR_ALREADY_EXISTS插槽中已存在其他密钥材料。
 */
psa_status_t psa_copy_key_material_into_slot( psa_key_slot_t *slot,
                                              const uint8_t *data,
                                              size_t data_length );

/** 将mbed TLS错误代码转换为PSA错误代码
 *
 * \注意：此功能仅为方便Mbed TLS而提供，可随时删除，恕不另行通知。
 *
 * \param ret mbed TLS抛出错误代码
 *
 * \return相应的PSA错误代码
 */
psa_status_t mbedtls_to_psa_error( int ret );

#endif /* PSA_CRYPTO_CORE_H */

