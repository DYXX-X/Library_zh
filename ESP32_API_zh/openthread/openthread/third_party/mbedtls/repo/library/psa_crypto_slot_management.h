/*
 *  基于Mbed TLS加密的PSA加密层
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

#ifndef PSA_CRYPTO_SLOT_MANAGEMENT_H
#define PSA_CRYPTO_SLOT_MANAGEMENT_H

#include "psa/crypto.h"
#include "psa_crypto_core.h"
#include "psa_crypto_se.h"

/* 键槽数（加1，因为未使用0）。为了简单起见，该值目前是一个编译时间常数。*/
#define PSA_KEY_SLOT_COUNT 32

/** 易失性密钥标识符的范围。
 *
 *  密钥标识符的实现范围的最后PSA_KEY_SLOT_COUNT标识符为易失性密钥标识符保留。易失密钥标识符等于#PSA_key_ID_volatile_MIN加上包含易失密钥定义的密钥槽的索引。
 */

/** 易失性密钥标识符的最小值。
 */
#define PSA_KEY_ID_VOLATILE_MIN  ( PSA_KEY_ID_VENDOR_MAX - \
                                   PSA_KEY_SLOT_COUNT + 1 )

/** 易失性密钥标识符的最大值。
 */
#define PSA_KEY_ID_VOLATILE_MAX  PSA_KEY_ID_VENDOR_MAX

/** 测试密钥标识符是否为易失性密钥标识符。
 *
 * \param key_id要测试的密钥标识符。
 *
 * \retval 1密钥标识符是易失性密钥标识符。\retval 0密钥标识符不是易失性密钥标识符。
 */
static inline int psa_key_id_is_volatile( psa_key_id_t key_id )
{
    return( ( key_id >= PSA_KEY_ID_VOLATILE_MIN ) &&
            ( key_id <= PSA_KEY_ID_VOLATILE_MAX ) );
}

/** 获取给定标识符的密钥的描述并锁定它。
 *
 * 易失性密钥和加载的持久性密钥的描述存储在密钥槽中。此函数返回一个指针，指向包含给定标识符的密钥描述的密钥槽。
 *
 * 对于持久密钥，如果尚未完成，则函数会将密钥的描述加载到密钥槽中。
 *
 * 成功后，返回的钥匙槽被锁定。呼叫方有责任在其不再访问钥匙槽时解锁钥匙槽。
 *
 * \param key要查询的密钥标识符。\param[out]p_slot成功时，“p_slot”包含指向密钥槽的指针，该指针包含由\p key标识的密钥的描述。
 *
 * \retval#PSA_SUCCESS\p p_slot包含指向密钥槽的指针，该密钥槽包含由\p key标识的密钥的描述。钥匙槽计数器已递增。\retval#PSA_ERROR_BAD_STATE库尚未初始化。\retval#PSA_ERROR_INVALID_HANDLE\p密钥不是有效的密钥标识符。\retval#PSA_ERROR_INSUFFIE_MEMORY\p密钥是持久密钥标识符。该实现没有足够的资源来加载持久密钥。这可能是由于缺少空钥匙槽或可用内存。\retval#PSA_ERROR_DOES_NOT_EXIST没有密钥标识符为\p的密钥。\retval#PSA_ERROR_CORRUPTION_DETECTED \retval#PSA错误_STORAGE_FAILURE\retval#PSA_ERROR_DATA_CORRUPT
 */
psa_status_t psa_get_and_lock_key_slot( mbedtls_svc_key_id_t key,
                                        psa_key_slot_t **p_slot );

/** 初始化钥匙槽结构。
 *
 * \retval#PSA_SUCCESS当前此函数始终成功。
 */
psa_status_t psa_initialize_key_slots( void );

/** 删除内存中关键插槽中的所有数据。
 *
 * 这不会影响持久性存储。*/
void psa_wipe_all_key_slots( void );

/** 找到一个空闲的钥匙槽。
 *
 * 此函数返回一个可供使用且处于接地状态（所有位为零）的钥匙槽。成功后，钥匙槽被锁定。呼叫方有责任在其不再访问钥匙槽时解锁钥匙槽。
 *
 * \param[out]volatile_key_id成功时，返回的插槽关联的volatile密钥标识符。\param[out]p_slot成功时，指向槽的指针。
 *
 * \retval#PSA_SUCCESS\retval#PSA错误_充分_记忆\retval#PSA_ERROR_BAD_STATE
 */
psa_status_t psa_get_empty_key_slot( psa_key_id_t *volatile_key_id,
                                     psa_key_slot_t **p_slot );

/** 锁定钥匙槽。
 *
 * 此函数将钥匙槽锁定计数器递增1。
 *
 * \param[in]slot密钥槽。
 *
 * \retval#PSA_SUCCESS钥匙槽锁定计数器已递增。\retval#PSA_ERROR_CORRUPTION_DETECTED锁定计数器已达到其最大值，且未增加。
 */
static inline psa_status_t psa_lock_key_slot( psa_key_slot_t *slot )
{
    if( slot->lock_count >= SIZE_MAX )
        return( PSA_ERROR_CORRUPTION_DETECTED );

    slot->lock_count++;

    return( PSA_SUCCESS );
}

/** 解锁钥匙槽。
 *
 * 此功能将钥匙槽锁定计数器减1。
 *
 * \注意：为了简化在检索密钥槽时的错误处理，NULL输入指针是有效的，在这种情况下，函数将成功返回而无需执行任何操作。
 *
 * \param[in]slot密钥槽。\retval#PSA_SUCCESS\p插槽为空，或者密钥插槽锁定计数器已成功递减。\retval#PSA_ERROR_CORRUPTION_DETECTED锁定计数器等于0。
 *
 */
psa_status_t psa_unlock_key_slot( psa_key_slot_t *slot );

/** 测试生存期是否指定外部密码处理器中的密钥。
 *
 * \param lifetime要测试的生存期。
 *
 * \retval 1生存期指定外部密钥。在此生命周期内应该有一个注册的驱动程序，否则无法创建或操作密钥。\retval 0生存期指定易失性或内部存储中的密钥。
 */
static inline int psa_key_lifetime_is_external( psa_key_lifetime_t lifetime )
{
    return( PSA_KEY_LIFETIME_GET_LOCATION( lifetime )
                != PSA_KEY_LOCATION_LOCAL_STORAGE );
}

/** 验证密钥的位置。
 *
 * 此函数检查钥匙的属性是否指向PSA Core已知的位置，如果要在外部位置找到钥匙，则返回驱动程序功能表。
 *
 * \param[in]lifetime键的lifetime属性。\param[out]p_drv成功时，当密钥位于外部存储中时，返回指向与该密钥的存储位置相关联的驱动程序表的指针。
 *
 * \retval#PSA_SUCCESS\retval#PSA错误_INVALID_ARGUMENT
 */
psa_status_t psa_validate_key_location( psa_key_lifetime_t lifetime,
                                        psa_se_drv_table_entry_t **p_drv );

/** 验证密钥的持久性。
 *
 * \param[in]lifetime键的lifetime属性。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_ARGUMENT密钥是持久的，但不支持持久密钥。
 */
psa_status_t psa_validate_key_persistence( psa_key_lifetime_t lifetime );

/** 验证密钥标识符。
 *
 * \param[in]key密钥标识符。\param[in]vendor_ok非零表示允许供应商范围内的密钥标识符，否则不允许使用易失性密钥标识符\c 0。
 *
 * \retval#PSA_SUCCESS标识符有效。\retval#PSA_ERROR_INVALID_ARGUMENT密钥标识符无效。
 */
psa_status_t psa_validate_key_id( mbedtls_svc_key_id_t key, int vendor_ok );

#endif /* PSA_CRYPTO_SLOT_MANAGEMENT_H */

