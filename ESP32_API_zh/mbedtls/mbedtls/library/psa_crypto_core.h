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

/** 恒定时间缓冲区比较
 *
 * \param[in]用于比较的左侧缓冲区。\param[in]b用于比较的右侧缓冲区。\param n要比较的字节数。
 *
 * \如果缓冲区内容相等，则返回0，否则返回非零
 */
static inline int mbedtls_psa_safer_memcmp(
    const uint8_t *a, const uint8_t *b, size_t n )
{
    size_t i;
    unsigned char diff = 0;

    for( i = 0; i < n; i++ )
        diff |= a[i] ^ b[i];

    return( diff );
}

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

    /* 动态分配的密钥数据缓冲区。在psa_export_key（）中指定的格式。*/
    struct key_data
    {
        uint8_t *data;
        size_t bytes;
    } key;
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

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
/** 从存储密钥描述的密钥槽中获取密钥的SE槽编号。
 *
 * \param[in]slot要查询的密钥槽。这必须是存储动态注册的安全元素的密钥描述的密钥槽，否则行为是未定义的。
 */
static inline psa_key_slot_number_t psa_key_slot_get_slot_number(
    const psa_key_slot_t *slot )
{
    return( *( (psa_key_slot_number_t *)( slot->key.data ) ) );
}
#endif

/** 彻底清除内存中的插槽，包括其策略。
 *
 * 永久存储不受影响。
 *
 * \param[in，out]slot要擦除的密钥槽。
 *
 * \retval#PSA_SUCCESS成功。这包括已经完全擦除的钥匙槽的情况。\retval#PSA_ERROR_CORRUPTION_DETECTED
 */
psa_status_t psa_wipe_key_slot( psa_key_slot_t *slot );

/** 尝试将缓冲区分配给空密钥槽。
 *
 * \param[in，out]slot要将缓冲区附加到的插槽。\param[in]buffer_length请求的缓冲区大小。
 *
 * \retval#PSA_SUCCESS缓冲区已成功分配。\retval#PSA_ERROR_INSUFFIE_MEMORY没有足够的内存用于分配。\retval#PSA_ERROR_ALREADY_EXISTS尝试将缓冲区分配给非空密钥槽。
 */
psa_status_t psa_allocate_buffer_to_slot( psa_key_slot_t *slot,
                                          size_t buffer_length );

/**从插槽擦除密钥数据。保留元数据，如策略。*/
psa_status_t psa_remove_key_data_from_memory( psa_key_slot_t *slot );

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

/** 在给定加密算法PSA标识符以及要与加密算法一起使用的密钥的PSA类型和大小的情况下，获取Mbed TLS加密信息。
 *
 * \param alg PSA密码算法标识符\param key_type PSA密钥类型\param key _bits密钥的大小（以位为单位）\param[out]cipher_id Mbed TLS密码算法标识符
 *
 * \return密码算法的Mbed TLS密码信息。\c如果不支持PSA密码算法，则为NULL。
 */
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_psa(
    psa_algorithm_t alg, psa_key_type_t key_type, size_t key_bits,
    mbedtls_cipher_id_t *cipher_id );

/** 以二进制格式导入密钥。
 *
 * \注意：此函数的签名是PSA驱动程序import_key入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的import_key入口点。
 *
 * \param[in]attributes要导入的密钥的属性。\param[in]data包含导入格式密钥数据的缓冲区。\param[in]data_length数据缓冲区的大小（字节）。\param[out]key_buffer成功返回时包含输出格式密钥数据的缓冲区。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。此大小大于或等于\p data_length。\param[out]key_buffer_length写入\p key_buffer的数据长度（字节）。\param[out]bits以位数表示的密钥大小。
 *
 * \retval#PSA_SUCCESS密钥已成功导入。\retval#PSA_ERROR_INVALID_ARGUMENT密钥数据格式不正确。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_CORRUPTION_DETECTED
 */
psa_status_t psa_import_key_into_slot(
    const psa_key_attributes_t *attributes,
    const uint8_t *data, size_t data_length,
    uint8_t *key_buffer, size_t key_buffer_size,
    size_t *key_buffer_length, size_t *bits );

/** 以二进制格式导出密钥
 *
 * \注意：此函数的签名是PSA驱动程序export_key入口点的签名。此函数充当PSA驱动程序接口规范中定义的export_key入口点。
 *
 * \param[in]attributes要导出的密钥的属性。\param[in]key_buffer要导出的密钥的材质或上下文。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[out]data要写入密钥数据的缓冲区。\param[in]data_size数据缓冲区的大小（字节）。\param[out]data_length成功时，写入数据的字节数
 *
 * \retval#PSA_SUCCESS密钥导出成功。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILUE\retval#PSA_ERROR_CORRUPTION_DETECTED \retval#1PSA_ERROR_STORAGE_FAILURE \retval#2PSA_ERROR_INSUFFIE_MEMORY
 */
psa_status_t psa_export_key_internal(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    uint8_t *data, size_t data_size, size_t *data_length );

/** 以二进制格式导出公钥或密钥对的公共部分。
 *
 * \注意：此函数的签名是PSA驱动程序export_public_key入口点的签名。此函数充当PSA驱动程序接口规范中定义的export_public_key入口点。
 *
 * \param[in]attributes要导出的密钥的属性。\param[in]key_buffer要导出的密钥的材质或上下文。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[out]data要写入密钥数据的缓冲区。\param[in]data_size数据缓冲区的大小（字节）。\param[out]data_length成功时，写入数据的字节数
 *
 * \retval#PSA_SUCCESS已成功导出公钥。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILUE\retval#PSA_ERROR_CORRUPTION_DETECTED \retval#1PSA_ERROR_STORAGE_FAILURE \retval#2PSA_ERROR_INSUFFIE_MEMORY
 */
psa_status_t psa_export_public_key_internal(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    uint8_t *data, size_t data_size, size_t *data_length );

/**
 * \brief生成密钥。
 *
 * \注意：函数的签名是PSA驱动程序generate_key入口点的签名。
 *
 * \param[in]attributes要生成的密钥的属性。\param[out]key_buffer要写入密钥数据的缓冲区。\param[in]key_buffer_size \p key_buffer的大小（字节）。\param[out]key_buffer_length成功时，写入\p key_buffer的字节数。
 *
 * \retval#PSA_SUCCESS密钥已成功生成。\retval#PSA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_NOT_SUPPORTED不支持以位或类型表示的密钥大小。\retval#PSA_ERROR_BUFFER_TOO_SMALL \p key_BUFFER的大小太小。
 */
psa_status_t psa_generate_key_internal( const psa_key_attributes_t *attributes,
                                        uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        size_t *key_buffer_length );

/** 使用私钥签名邮件。对于哈希和符号算法，这包括哈希步骤。
 *
 * \注意：此函数的签名是PSA驱动程序sign_message入口点的签名。此函数充当PSA驱动程序接口规范中定义的透明驱动程序的sign_message入口点。
 *
 * \注意：此函数将调用psa_sign_hash的驱动程序，并再次执行驱动程序调度。
 *
 * \param[in]attributes用于操作的键的属性。\param[in]key_buffer包含密钥上下文的缓冲区。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[in]alg与密钥类型兼容的签名算法。\param[in]input要签名的输入消息。\param[in]input_length输入缓冲区的大小（以字节为单位）。\param[out]signature要写入签名的缓冲区。\param[in]signature_size签名缓冲区的大小（字节）。\param[out]signature_length成功时，构成返回签名值的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_BUFFER_TOO_SMALL签名缓冲区的大小太小。您可以通过调用#PSA_SIG_OUTPUT_size（\c key_type，\c key_bits，\p alg）来确定足够的缓冲区大小，其中\c keytype和\c key_bits分别是密钥的类型和位大小。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#5PSA_ERROR_CORRUPTION_DETECTED \retval#8PSA_ERROR_inSUFFIE_ENTROPY
 */
psa_status_t psa_sign_message_builtin(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg, const uint8_t *input, size_t input_length,
    uint8_t *signature, size_t signature_size, size_t *signature_length );

/** 使用哈希和签名验证算法，使用公钥验证消息的签名。
 *
 * \注意：此函数的签名是PSA驱动程序verify_message入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的verify_message入口点。
 *
 * \注意：此函数将调用psa_verify_hash的驱动程序，并再次执行驱动程序调度。
 *
 * \param[in]attributes用于操作的键的属性。\param[in]key_buffer包含密钥上下文的缓冲区。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[in]alg与密钥类型兼容的签名算法。\param[in]input要验证其签名的消息。\param[in]input_length输入缓冲区的大小（字节）。\param[in]签名缓冲区，包含要验证的签名。\param[in]signature_length签名缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS签名有效。\retval#PSA_ERROR_INVALID_SIGNATURE计算已成功执行，但传递的签名不是有效签名。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY
 */
psa_status_t psa_verify_message_builtin(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg, const uint8_t *input, size_t input_length,
    const uint8_t *signature, size_t signature_length );

/** 使用私钥对已计算的哈希进行签名。
 *
 * \注意：此函数的签名是PSA驱动程序sign_hash入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的sign_hash入口点。
 *
 * \param[in]attributes用于操作的键的属性。\param[in]key_buffer包含密钥上下文的缓冲区。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[in]alg与密钥类型兼容的签名算法。\param[in]hash要签名的哈希或消息。\param[in]hash_length哈希缓冲区的大小（字节）。\param[out]signature要写入签名的缓冲区。\param[in]signature_size签名缓冲区的大小（字节）。\param[out]signature_length成功时，构成返回签名值的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_BUFFER_TOO_SMALL签名缓冲区的大小太小。您可以通过调用#PSA_SIG_OUTPUT_size（\c key_type，\c key_bits，\p alg）来确定足够的缓冲区大小，其中\c keytype和\c key_bits分别是密钥的类型和位大小。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#5PSA_ERROR_CORRUPTION_DETECTED \retval#8PSA_ERROR_inSUFFIE_ENTROPY
 */
psa_status_t psa_sign_hash_builtin(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg, const uint8_t *hash, size_t hash_length,
    uint8_t *signature, size_t signature_size, size_t *signature_length );

/**
 * \brief使用公钥验证哈希或短消息的签名。
 *
 * \注意：此函数的签名是PSA驱动程序verify_hash入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的verify_hash入口点。
 *
 * \param[in]attributes用于操作的键的属性。\param[in]key_buffer包含密钥上下文的缓冲区。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[in]alg与密钥类型兼容的签名算法。\param[in]hash要验证其签名的哈希或消息。\param[in]hash_length哈希缓冲区的大小（字节）。\param[in]签名缓冲区，包含要验证的签名。\param[in]signature_length签名缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS签名有效。\retval#PSA_ERROR_INVALID_SIGNATURE计算已成功执行，但传递的签名不是有效签名。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY
 */
psa_status_t psa_verify_hash_builtin(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg, const uint8_t *hash, size_t hash_length,
    const uint8_t *signature, size_t signature_length );

#endif /* PSA_CRYPTO_CORE_H */

