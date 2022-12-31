/*
 *  基于Mbed TLS软件加密的PSA MAC层
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

#ifndef PSA_CRYPTO_MAC_H
#define PSA_CRYPTO_MAC_H

#include <psa/crypto.h>

/** 使用Mbed TLS计算消息的MAC（消息验证码）。
 *
 * \注意：此函数的签名是PSA驱动程序mac_compute入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的mac_compute入口点。
 *
 * \param[in]attributes用于操作的键的属性。\param[in]key_buffer包含用于计算MAC的密钥的缓冲区。此缓冲区包含psa_export_key（）定义的导出表示中的密钥（即原始密钥字节）。\param key_buffer_size \p key_bbuffer缓冲区的大小（以字节为单位）。\param alg要使用的MAC算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_MAC（\p alg）为真）。\param[in]包含输入消息的输入缓冲区。\param input_length输入缓冲区的大小（字节）。\param[out]mac要写入mac值的缓冲区。\param mac_size \p mac缓冲区的大小（字节）。\param[out]mac_length成功时，构成mac值的字节数。
 *
 * \retval#PSA_SUCCESS成功。\不支持retval#PSA_ERROR_NOT_SUPPORTED\p alg。\retval#PSA_ERROR_BUFFER_TOO_SMALL\p mac_size太小\retval#PSA ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_CORRUPTION_DETECTED
 */
psa_status_t mbedtls_psa_mac_compute(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *mac,
    size_t mac_size,
    size_t *mac_length);

/** 使用Mbed TLS设置多部分MAC计算操作。
 *
 * \注意：此函数的签名是PSA驱动程序mac_sign_setup入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的mac_sign_setup入口点。
 *
 * \param[in，out]operation要设置的操作对象。它必须已初始化，但尚未使用。\param[in]attributes用于操作的键的属性。\param[in]key_buffer包含用于计算MAC的密钥的缓冲区。此缓冲区包含psa_export_key（）定义的导出表示中的密钥（即原始密钥字节）。\param key_buffer_size \p key_bbuffer缓冲区的大小（以字节为单位）。\param alg要使用的MAC算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_MAC（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\不支持retval#PSA_ERROR_NOT_SUPPORTED\p alg。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。
 */
psa_status_t mbedtls_psa_mac_sign_setup(
    mbedtls_psa_mac_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg);

/** 使用Mbed TLS设置多部分MAC验证操作。
 *
 * \注意：此函数的签名是PSA驱动程序mac_verify_setup入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的mac_verify_setup入口点。
 *
 * \param[in，out]operation要设置的操作对象。它必须已初始化，但尚未使用。\param[in]attributes用于操作的键的属性。\param[in]key_buffer包含用于计算MAC的密钥的缓冲区。此缓冲区包含psa_export_key（）定义的导出表示中的密钥（即原始密钥字节）。\param key_buffer_size \p key_bbuffer缓冲区的大小（以字节为单位）。\param alg要使用的MAC算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_MAC（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\不支持retval#PSA_ERROR_NOT_SUPPORTED\p alg。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。
 */
psa_status_t mbedtls_psa_mac_verify_setup(
    mbedtls_psa_mac_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg);

/** 使用Mbed TLS向多部分MAC操作添加消息片段。
 *
 * \注意：此函数的签名是PSA驱动程序mac_update入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的mac_update入口点。
 *
 * PSA核心在调用此函数之前调用mbedtls_PSA_mac_sign_setup（）或mbedtls_prsa_mac_verify_setup）。
 *
 * 如果此函数返回错误状态，PSA核心将通过调用mbedtls_PSA_mac_abort（）中止操作。
 *
 * \param[in，out]操作活动MAC操作。\param[in]输入缓冲区，包含要添加到MAC计算中的消息片段。\param input_length输入缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为活动状态）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA错误_错误_已测试
 */
psa_status_t mbedtls_psa_mac_update(
    mbedtls_psa_mac_operation_t *operation,
    const uint8_t *input,
    size_t input_length );

/** 使用Mbed TLS完成消息MAC的计算。
 *
 * \注意：此函数的签名是PSA驱动程序mac_sign_finish入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的mac_sign_finish入口点。
 *
 * PSA核心在调用此函数之前调用mbedtls_PSA_mac_sign_setup（）。此函数计算通过将传递给前面调用的输入连接到mbedtls_psa_MAC_update（）而形成的消息的MAC。
 *
 * 无论该函数是否成功返回，PSA核心都会通过调用mbedtls_PSA_mac_abort（）来中止操作。
 *
 * \param[in，out]操作活动MAC操作。\param[out]mac要写入mac值的缓冲区。\param mac_size为mac算法请求的输出大小。PSA核心保证这是传递给mbedtls_PSA_MAC_sign_setup（）的算法和密钥组合的有效MAC长度。它还保证\p mac缓冲区足够大，可以容纳请求的输出大小。\param[out]mac_length成功时，输出到缓冲区\p mac的字节数，将等于请求的长度\p mac_size。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须是活动的mac符号操作）。\retval#PSA_ERROR_BUFFER_TOO_SMALL mac缓冲区的大小太小。可以通过调用PSA_MAC_LENGTH（）来确定足够的缓冲区大小。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA错误_错误_已测试
 */
psa_status_t mbedtls_psa_mac_sign_finish(
    mbedtls_psa_mac_operation_t *operation,
    uint8_t *mac,
    size_t mac_size,
    size_t *mac_length );

/** 完成消息MAC的计算，并使用Mbed TLS将其与预期值进行比较。
 *
 * \注意：此函数的签名是PSA驱动程序mac_verify_finish入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的mac_verify_finish入口点。
 *
 * PSA核心在调用此函数之前调用mbedtls_PSA_mac_verify_setup（）。此函数计算通过将传递给前面调用的输入连接到mbedtls_psa_MAC_update（）而形成的消息的MAC。然后，它将计算的MAC与作为参数传递给该函数的预期MAC进行比较。
 *
 * 无论该函数是否成功返回，PSA核心都会通过调用mbedtls_PSA_mac_abort（）来中止操作。
 *
 * \param[in，out]操作活动MAC操作。\param[in]mac缓冲区，包含预期的mac值。\param mac_length预期mac值的长度（字节）。PSA核心保证该长度是传递给mbedtls_PSA_MAC_verify_setup（）的算法和密钥组合的有效MAC长度。
 *
 * \retval#PSA_SUCCESS预期MAC与消息的实际MAC相同。\retval#PSA_ERROR_INVALID_SIGNATURE已成功计算消息的MAC，但它与预期的MAC不同。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须是活动的mac验证操作）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA错误_错误_已测试
 */
psa_status_t mbedtls_psa_mac_verify_finish(
    mbedtls_psa_mac_operation_t *operation,
    const uint8_t *mac,
    size_t mac_length );

/** 使用Mbed TLS中止MAC操作。
 *
 * 中止操作将释放所有相关资源，但操作结构本身除外。一旦中止，可以通过再次调用mbedtls_psa_mac_sign_setup（）或mbedtls_prsa_mac_verify_setup）将操作对象重新用于另一个操作。
 *
 * PSA核心可以在通过#mbedtls_PSA_mac_operation_t中描述的方法之一初始化操作对象之后的任何时间调用此函数。
 *
 * 特别是，在操作被调用mbedtls_psa_mac_abort（）、mbedtls_ssa_mac_sign_finish（）或mbedtls_prsa_mac_verify_finish）终止后调用mbedtls _psa_mac_abort（。
 *
 * \param[in，out]操作已初始化MAC操作。
 *
 * \retval#PSA_SUCCESS\retval#PSA错误_CORRUPTION_DETECTED
 */
psa_status_t mbedtls_psa_mac_abort(
    mbedtls_psa_mac_operation_t *operation );

#endif /* PSA_CRYPTO_MAC_H */

