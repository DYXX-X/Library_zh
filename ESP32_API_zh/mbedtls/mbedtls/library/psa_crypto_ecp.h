/*
 *  基于Mbed TLS加密的PSA ECP层
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

#ifndef PSA_CRYPTO_ECP_H
#define PSA_CRYPTO_ECP_H

#include <psa/crypto.h>
#include <mbedtls/ecp.h>

/** 将密钥缓冲区的内容加载到内部ECP表示中
 *
 * \param[in]type数据中包含的键的类型。\param[in]curve_bits曲线的标称比特大小。它必须与传入数据的表示一致。这可以是0，在这种情况下，比特大小是从\p data_length推断出来的（这对于当前支持或在可预见的将来将支持的所有密钥类型和表示格式格式都是可能的）。\param[in]data从中加载表示的缓冲区。\param[in]data_length数据的大小（以字节为单位）。\param[out]p_ecp成功时返回指向ecp上下文的指针。调用方负责释放上下文的内容和上下文本身。
 */
psa_status_t mbedtls_psa_ecp_load_representation( psa_key_type_t type,
                                                  size_t curve_bits,
                                                  const uint8_t *data,
                                                  size_t data_length,
                                                  mbedtls_ecp_keypair **p_ecp );

/** 以二进制格式导入ECP密钥。
 *
 * \注意：此函数的签名是PSA驱动程序import_key入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的import_key入口点。
 *
 * \param[in]attributes要导入的密钥的属性。\param[in]data包含导入格式密钥数据的缓冲区。\param[in]data_length数据缓冲区的大小（字节）。\param[out]key_buffer包含输出格式密钥数据的缓冲区。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。此大小大于或等于\p data_length。\param[out]key_buffer_length写入\p key_buffer的数据长度（字节）。\param[out]bits以位数表示的密钥大小。
 *
 * \retval#PSA_SUCCESS已成功导入ECP密钥。\retval#PSA_ERROR_INVALID_ARGUMENT密钥数据格式不正确。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_CORRUPTION_DETECTED
 */
psa_status_t mbedtls_psa_ecp_import_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *data, size_t data_length,
    uint8_t *key_buffer, size_t key_buffer_size,
    size_t *key_buffer_length, size_t *bits );

/** 导出ECP密钥以导出表示
 *
 * \param[in]type要导出的密钥类型（公钥/私钥）\param[in]ecp要导出的内部ecp表示形式\param[out]data要导出到的缓冲区\param[iin]data_size要导出到缓冲区的长度\param[ut]data_length写入数据的字节数
 */
psa_status_t mbedtls_psa_ecp_export_key( psa_key_type_t type,
                                         mbedtls_ecp_keypair *ecp,
                                         uint8_t *data,
                                         size_t data_size,
                                         size_t *data_length );

/** 以二进制格式导出ECP公钥或ECP密钥对的公共部分。
 *
 * \注意：此函数的签名是PSA驱动程序export_public_key入口点的签名。此函数充当PSA驱动程序接口规范中定义的export_public_key入口点。
 *
 * \param[in]attributes要导出的密钥的属性。\param[in]key_buffer要导出的密钥的材质或上下文。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[out]data要写入密钥数据的缓冲区。\param[in]data_size数据缓冲区的大小（字节）。\param[out]data_length成功时，写入数据的字节数
 *
 * \retval#PSA_SUCCESS已成功导出ECP公钥。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILUE\retval#PSA_ERROR_CORRUPTION_DETECTED \retval#1PSA_ERROR_STORAGE_FAILURE \retval#2PSA_ERROR_INSUFFIE_MEMORY
 */
psa_status_t mbedtls_psa_ecp_export_public_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    uint8_t *data, size_t data_size, size_t *data_length );

/**
 * \brief生成ECP密钥。
 *
 * \注意：函数的签名是PSA驱动程序generate_key入口点的签名。
 *
 * \param[in]attributes要生成的ECP密钥的属性。\param[out]key_buffer要写入密钥数据的缓冲区。\param[in]key_buffer_size \p key_buffer的大小（字节）。\param[out]key_buffer_length成功时，写入\p key_buffer的字节数。
 *
 * \retval#PSA_SUCCESS密钥已成功生成。\retval#PSA_ERROR_NOT_SUPPORTED密钥长度或类型不受支持。\retval#PSA_ERROR_BUFFER_TOO_SMALL \p key_BUFFER的大小太小。
 */
psa_status_t mbedtls_psa_ecp_generate_key(
    const psa_key_attributes_t *attributes,
    uint8_t *key_buffer, size_t key_buffer_size, size_t *key_buffer_length );

/** 使用ECDSA对已计算的哈希进行签名。
 *
 * \注意：此函数的签名是PSA驱动程序sign_hash入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的sign_hash入口点。
 *
 * \param[in]attributes用于操作的ECC密钥的属性。\param[in]key_buffer包含ECC密钥上下文的缓冲区。总体安排\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[in]alg随机化或确定性ECDSA算法。\param[in]hash要签名的哈希或消息。\param[in]hash_length哈希缓冲区的大小（字节）。\param[out]signature要写入签名的缓冲区。\param[in]signature_size签名缓冲区的大小（字节）。\param[out]signature_length成功时，构成返回签名值的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_BUFFER_TOO_SMALL签名缓冲区的大小太小。您可以通过调用#PSA_SIG_OUTPUT_size（\c PSA_KEY_TYPE_ECC_KEY_PAIR，\c KEY_bits，\p alg）来确定足够的缓冲区大小，其中\c KEY_bits是ECC密钥的位大小。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#5PSA_ERROR_CORRUPTION_DETECTED \retval#8PSA_ERROR_inSUFFIE_ENTROPY
 */
psa_status_t mbedtls_psa_ecdsa_sign_hash(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg, const uint8_t *hash, size_t hash_length,
    uint8_t *signature, size_t signature_size, size_t *signature_length );

/**
 * \brief验证ECDSA哈希或短消息签名。
 *
 * \注意：此函数的签名是PSA驱动程序verify_hash入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的verify_hash入口点。
 *
 * \param[in]attributes用于操作的ECC密钥的属性。\param[in]key_buffer包含ECC密钥上下文的缓冲区。总体安排\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[in]alg随机化或确定性ECDSA算法。\param[in]hash要验证其签名的哈希或消息。\param[in]hash_length哈希缓冲区的大小（字节）。\param[in]签名缓冲区，包含要验证的签名。\param[in]signature_length签名缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS签名有效。\retval#PSA_ERROR_INVALID_SIGNATURE计算已成功执行，但传递的签名不是有效签名。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY
 */
psa_status_t mbedtls_psa_ecdsa_verify_hash(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg, const uint8_t *hash, size_t hash_length,
    const uint8_t *signature, size_t signature_length );

#endif /* PSA_CRYPTO_ECP_H */

