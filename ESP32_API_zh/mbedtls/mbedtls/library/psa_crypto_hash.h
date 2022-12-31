/*
 *  基于Mbed TLS软件加密的PSA哈希层
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

#ifndef PSA_CRYPTO_HASH_H
#define PSA_CRYPTO_HASH_H

#include <psa/crypto.h>

#include <mbedtls/md_internal.h>

/** 获取给定PSA标识符的哈希算法的Mbed TLS MD信息
 *
 * \param[in]alg-PSA哈希算法标识符
 *
 * \返回哈希算法的Mbed TLS MD信息。\c如果不支持PSA哈希算法，则为NULL。
 */
const mbedtls_md_info_t *mbedtls_md_info_from_psa( psa_algorithm_t alg );

/** 使用Mbed TLS例程计算消息的哈希（摘要）。
 *
 * \注意：此函数的签名是PSA驱动程序hash_compute入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的hash_compute入口点。
 *
 * \param alg要计算的哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p alg）为真）。\param[in]输入缓冲区，包含要哈希的消息。\param input_length输入缓冲区的大小（字节）。\param[out]hash要写入哈希的缓冲区。\param hash_size \p哈希缓冲区的大小（字节）。\param[out]hash_length成功时，构成哈希值的字节数。这始终是#PSA_HAH_LENGTH（\p alg）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_NOT_SUPPORTED\p不支持alg \retval#PSA _ERROR_BUFFER_TOO_SMALL\p hash_size太小\retval#PSA_ERROR_INSUFFIE_MEMORY\retval＃PSA_ERROR_CORRUPTION_DETECTED
 */
psa_status_t mbedtls_psa_hash_compute(
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length);

/** 使用Mbed TLS例程设置多部分哈希操作。
 *
 * \注意：此函数的签名是PSA驱动程序hash_setup入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的hash_setup入口点。
 *
 * 如果在调用mbedtls_psa_hash_setup（）之后的任何步骤发生错误，则需要通过调用mbedtls _psa_hsh_abort（）来重置操作。内核可以在操作初始化后的任何时候调用mbedtls_psa_hash_abort（）。
 *
 * 成功调用mbedtls_psa_hash_setup（）后，内核必须最终终止操作。以下事件将终止操作：
 * -成功调用了mbedtls_psa_hash_finish（）或mbedtls_prsa_hash_verify（）。
 * -对mbedtls_psa_hash_abort（）的调用。
 *
 * \param[in，out]operation要设置的操作对象。它必须已初始化为全零，并且尚未使用。\param alg要计算的哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA错误_错误_已测试
 */
psa_status_t mbedtls_psa_hash_setup(
    mbedtls_psa_hash_operation_t *operation,
    psa_algorithm_t alg );

/** 克隆Mbed TLS哈希操作。
 *
 * \注意：此函数的签名是PSA驱动程序hash_clone入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的hash_clone入口点。
 *
 * 此函数将正在进行的哈希操作的状态复制到新的操作对象。换句话说，此函数相当于使用与设置source_operation相同的算法在target_operation上调用mbedtls_psa_hash_setup（），然后使用传递给source_operaction的相同输入在target_oper上调用mbedtls_psa_hash_update（）。此函数返回后，两个对象是独立的，即涉及其中一个对象的后续调用不会影响另一个对象。
 *
 * \param[in]source_operation要克隆的活动哈希操作。\param[in，out]target_operation要设置的操作对象。它必须初始化，但不是活动的。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_BAD_STATE源操作状态无效（必须为活动状态）。\retval#PSA_ERROR_BAD_STATE \p target_operation状态无效（必须为非活动状态）。\retval#PSA_ERROR_CORRUPTION_DETECTED \retval#PSA错误_不足_内存
 */
psa_status_t mbedtls_psa_hash_clone(
    const mbedtls_psa_hash_operation_t *source_operation,
    mbedtls_psa_hash_operation_t *target_operation );

/** 向多部分Mbed TLS哈希操作添加消息片段。
 *
 * \注意：此函数的签名是PSA驱动程序hash_update入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的hash_update入口点。
 *
 * 应用程序必须在调用此函数之前调用mbedtls_psa_hash_setup（）。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用mbedtls_psa_hash_abort（）中止。
 *
 * \param[in，out]操作活动哈希操作。\param[in]输入缓冲区，包含要哈希的消息片段。\param input_length输入缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为活动状态）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA错误_错误_已测试
 */
psa_status_t mbedtls_psa_hash_update(
    mbedtls_psa_hash_operation_t *operation,
    const uint8_t *input,
    size_t input_length );

/** 完成消息的Mbed TLS计算哈希的计算。
 *
 * \注意：此函数的签名是PSA驱动程序hash_finish入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的hash_finish入口点。
 *
 * 应用程序必须在调用此函数之前调用mbedtls_psa_hash_setup（）。此函数计算通过将传递给前面的mbedtls_psa_hash_update（）调用的输入串联起来形成的消息的哈希值。
 *
 * 当此函数成功返回时，操作将变为非活动状态。如果此函数返回错误状态，则操作将进入错误状态，必须通过调用mbedtls_psa_hash_abort（）中止。
 *
 * \param[in，out]操作活动哈希操作。\param[out]hash要写入哈希的缓冲区。\param hash_size \p哈希缓冲区的大小（字节）。\param[out]hash_length成功时，构成哈希值的字节数。这始终是#PSA_HAH_LENGTH（\c alg），其中\c alg是计算的哈希算法。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为活动状态）。\retval#PSA_ERROR_BUFFER_TOO_SMALL哈希缓冲区的大小太小。您可以通过调用#PSA_HASH_LENGTH（\c alg）来确定足够的缓冲区大小，其中\c alh是计算的哈希算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA错误_错误_已测试
 */
psa_status_t mbedtls_psa_hash_finish(
    mbedtls_psa_hash_operation_t *operation,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length );

/** 中止Mbed TLS哈希操作。
 *
 * \注意：此函数的签名是PSA驱动程序hash_abort入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的hash_abort入口点。
 *
 * 中止操作将释放所有相关资源，但操作结构本身除外。一旦中止，可以通过再次调用mbedtls_psa_hash_setup（）将操作对象重新用于另一个操作。
 *
 * 在通过#psa_hash_operation_t中描述的方法之一初始化操作对象之后，可以随时调用此函数。
 *
 * 特别是，在通过调用mbedtls_psa_hash_abort（）、mbedtls_prsa_hash_finish（）或mbedtls.prsa_hash_verify（）终止操作后调用mbedtls _psa_hsh_abort）是安全的，不会产生任何影响。
 *
 * \param[in，out]操作已初始化哈希操作。
 *
 * \retval#PSA_SUCCESS\retval#PSA错误_CORRUPTION_DETECTED
 */
psa_status_t mbedtls_psa_hash_abort(
    mbedtls_psa_hash_operation_t *operation );

#endif /* PSA_CRYPTO_HASH_H */

