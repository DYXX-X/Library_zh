/**
 * \psa/crypto_accel_driver文件。简要PSA加密加速器驱动程序模块
 *
 * 此标头声明直接访问密钥材料的加密驱动程序的类型和函数签名。这是针对片上加密加速器的。
 *
 * 该文件是PSA Crypto驱动程序模型的一部分，包含驱动程序开发人员要实现的功能，以使PSA Cryptographic API实现能够以标准化的方式调用硬件。驱动程序作者实现的包含驱动程序模型的函数不打算由应用程序开发人员调用。
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
#ifndef PSA_CRYPTO_ACCEL_DRIVER_H
#define PSA_CRYPTO_ACCEL_DRIVER_H

#include "crypto_driver_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup driver_digest硬件加速消息摘要
 *
 * 消息摘要（又名哈希）的生成和认证必须按照以下顺序分部分完成：
 * -`psa_drv_hash_setup_t`
 * -`psa_drv_hash_update_t`
 * -`psa_drv_hash_update_t`
 * - ...
 * -`psa_drv_hash_finish_t`
 *
 * 如果需要在“psa_drv_hash_finish_t”操作完成之前终止先前启动的消息摘要操作，则应通过“psa_derv_hash_abort_t”中止该操作。否则，可能会导致分配的资源无法释放或出现其他未定义的行为。
 */
/**@{*/

/** \brief特定于硬件的哈希上下文结构
 *
 * 此结构的内容依赖于实现，因此此处不再描述
 */
typedef struct psa_drv_hash_context_s psa_drv_hash_context_t;

/** \brief哈希（消息摘要）操作的开始操作的函数原型
 *
 *  实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~-{.c}psa_drv_hash_<ALGO>_setup~~~~其中`ALGO`是基础哈希函数的名称
 *
 * \param[in，out]p_context包含硬件特定哈希上下文的结构
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_hash_setup_t)(psa_drv_hash_context_t *p_context);

/** \brief哈希（消息摘要）操作的更新操作的函数原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~-{.c}psa_drv_hash_<ALGO>_update~~~~其中`ALGO`是基础算法的名称
 *
 * \param[in，out]p_context要继续的先前建立的哈希操作的硬件特定结构\param[in]p_input包含要附加到哈希操作的消息的缓冲区\param[iin]input_length输入消息缓冲区的字节大小
 */
typedef psa_status_t (*psa_drv_hash_update_t)(psa_drv_hash_context_t *p_context,
                                              const uint8_t *p_input,
                                              size_t input_length);

/** \brief哈希（消息摘要）操作的完成操作的函数原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~{.c}psa_drv_hash_<ALGO>_finish~~~～~~~~其中`ALGO`是基础算法的名称
 *
 * \param[in，out]p_context要完成的先前启动的哈希操作的硬件特定结构\param[out]p_output将放置生成摘要的缓冲区\param[in]output_size已分配给“p_output”缓冲区的缓冲区大小（以字节为单位）\param[out]p_output_length成功后放置在“p_output”中的字节数
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_hash_finish_t)(psa_drv_hash_context_t *p_context,
                                              uint8_t *p_output,
                                              size_t output_size,
                                              size_t *p_output_length);

/** \brief哈希（消息摘要）操作的中止操作的函数原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~{.c}psa_drv_hash_<ALGO>_abort~~~～~~~~其中`ALGO`是基础算法的名称
 *
 * \param[in，out]p_context要中止的先前启动的哈希操作的硬件特定结构
 */
typedef void (*psa_drv_hash_abort_t)(psa_drv_hash_context_t *p_context);

/**@}*/

/** \defgroup accel_mac硬件加速消息验证代码使用加密加速器生成和验证消息验证代码（mac）可以作为单个函数调用（通过“psa_drv_accel_mac_generate_t”或“psa_rv_accel-mac_verify_t”函数）完成，也可以按以下顺序部分完成：
 * -`psa_drv_accel_mac_setup_t`
 * -`psa_drv_accel_mac_update_t`
 * -`psa_drv_accel_mac_update_t`
 * - ...
 * -`psa_drv_accel_mac_finish_t`或`psa_derv_accl_mac_finish_verify_t`
 *
 * 如果需要终止先前启动的MAC操作，则应通过“psa_drv_accel_MAC_abort_t”来完成。否则，可能会导致分配的资源无法释放或出现其他未定义的行为。
 *
 */
/**@{*/

/** \brief特定于硬件加速器的MAC上下文结构
 *
 * 此结构的内容依赖于实现，因此在此不再描述。
 */
typedef struct psa_drv_accel_mac_context_s psa_drv_accel_mac_context_t;

/** \brief硬件加速MAC操作设置操作的功能原型
 *
 *  实现此原型的函数应按以下约定命名：~~~~~~ ~~~~{.c}psa_drv_accel_mac_<ALGO>_<mac_VARIANT>_setup~~~～~~~~-其中，`ALGO'是底层原语的名称，`mac_VARIANT'是mac操作的特定变体（如HMAC或CMAC）
 *
 * \param[in，out]p_context将包含硬件特定MAC上下文的结构\param[in]p_key包含要在操作中使用的明文密钥材料的缓冲区\param[iin]key_length密钥材料的字节大小
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_accel_mac_setup_t)(psa_drv_accel_mac_context_t *p_context,
                                                  const uint8_t *p_key,
                                                  size_t key_length);

/** \硬件加速MAC操作的更新操作的功能原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~-{.c}psa_drv_accel_mac_<ALGO>_<mac_VARIANT>_update~~~~其中`ALGO'是底层算法的名称，`mac_VARIANT'是mac操作的特定变体（如HMAC或CMAC）
 *
 * \param[in，out]p_context要继续的先前建立的MAC操作的硬件特定结构\param[in]p_input包含要附加到MAC操作的消息的缓冲区\param[iin]input_length输入消息缓冲区的字节大小
 */
typedef psa_status_t (*psa_drv_accel_mac_update_t)(psa_drv_accel_mac_context_t *p_context,
                                                   const uint8_t *p_input,
                                                   size_t input_length);

/** \硬件加速MAC操作完成操作的功能原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~{.c}psa_drv_accel_mac_<ALGO>_<mac_VARIANT>_finish~~~～~~~~-其中，`ALGO'是底层算法的名称，`mac_VARIANT'是mac操作的特定变体（如HMAC或CMAC）
 *
 * \param[in，out]p_context要完成的先前启动的MAC操作的硬件特定结构\param[out]p_MAC将放置生成的MAC的缓冲区\param[in]MAC_length已分配给“p_MAC”缓冲区的缓冲区大小（字节）
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_accel_mac_finish_t)(psa_drv_accel_mac_context_t *p_context,
                                                   uint8_t *p_mac,
                                                   size_t mac_length);

/** \简要介绍硬件加速MAC操作的完成和验证操作的功能原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~-{.c}psa_drv_accel_mac_<ALGO>_<mac_VARIANT>_finish_verify ~~~~其中，`ALGO'是基础算法的名称，`mac_VARIANT'是mac操作的特定变体（如HMAC或CMAC）
 *
 * \param[in，out]p_context要验证和完成的先前启动的MAC操作的硬件特定结构\param[in]p_MAC包含将用于验证的MAC的缓冲区\param[iin]MAC_length“p_MAC”缓冲区中数据的字节大小
 *
 * \retval#PSA_SUCCESS操作成功完成，比较匹配
 */
typedef psa_status_t (*psa_drv_accel_mac_finish_verify_t)(psa_drv_accel_mac_context_t *p_context,
                                                          const uint8_t *p_mac,
                                                          size_t mac_length);

/** \brief先前启动的硬件加速MAC操作的中止操作的功能原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~{.c}psa_drv_accel_mac_<ALGO>_<mac_VARIANT>_abort~~~~其中`ALGO'是底层算法的名称，`mac_VARIANT'是mac操作的特定变体（如HMAC或CMAC）
 *
 * \param[in，out]p_context要中止的先前启动的MAC操作的硬件特定结构
 *
 */
typedef psa_status_t (*psa_drv_accel_mac_abort_t)(psa_drv_accel_mac_context_t *p_context);

/** \硬件加速MAC操作的一次操作功能原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~-{.c}psa_drv_accel_mac_<ALGO>_<mac_VARIANT>~~~~其中`ALGO'是底层算法的名称，`mac_VARIANT'是mac操作的特定变体（如HMAC或CMAC）
 *
 * \param[in]p_input包含要MAC化的数据的缓冲区\param[in]input_length“p_input”数据的字节长度\param[iin]p_key包含要用于MAC操作的密钥材料的缓冲区/param[in]key_length”p_key数据的字节长\param[in]alg要执行的算法\param[out]p_MAC生成MAC的缓冲区success\param[in]mac_length“p_mac”缓冲区的字节长度
 */
typedef psa_status_t (*psa_drv_accel_mac_t)(const uint8_t *p_input,
                                            size_t input_length,
                                            const uint8_t *p_key,
                                            size_t key_length,
                                            psa_algorithm_t alg,
                                            uint8_t *p_mac,
                                            size_t mac_length);

/** \简要介绍一次性硬件加速MAC验证操作的功能原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~{.c}psa_drv_accel_mac_<ALGO>_<mac_VARIANT>_verify ~~~～~~~~-其中，`ALGO'是底层算法的名称，`mac_VARIANT'是mac操作的特定变体（如HMAC或CMAC）
 *
 * \param[in]p_input包含要MAC化的数据的缓冲区\param[in]input_length“p_input”数据的字节长度\param[iin]p_key包含要用于MAC操作的密钥材料的缓冲区/param[in]key_length‘p_key’数据的字节长\param[in]alg要执行的算法\param[i]p_MAC要比较的MAC数据\param[iin]MAC_length“p_mac”缓冲区的字节长度
 *
 * \retval#PSA_SUCCESS操作成功完成，比较匹配
 */
typedef psa_status_t (*psa_drv_accel_mac_verify_t)(const uint8_t *p_input,
                                                   size_t input_length,
                                                   const uint8_t *p_key,
                                                   size_t key_length,
                                                   psa_algorithm_t alg,
                                                   const uint8_t *p_mac,
                                                   size_t mac_length);
/**@}*/

/** \defgroup accel_cipher硬件加速块密码在除ECB之外的块模式下使用硬件加速进行加密和解密必须使用以下流程分多个部分完成：
 * -`psa_drv_accel_ccipher设置_t`
 * -“psa_drv_accel_cherph_set_iv_t”（根据块模式可选）
 * -`psa_drv_accel_cipher_update_t`
 * -`psa_drv_accel_cipher_update_t`
 * - ...
 * -`psa_drv_accel_ccipher_finish_t`
 *
 * 如果需要终止先前启动的硬件加速密码操作，则应通过“psa_drv_accel_Cipher_abort_t”完成。否则，可能会导致分配的资源无法释放或出现其他未定义的行为。
 */
/**@{*/

/** \brief硬件加速器特定密码上下文结构
 *
 * 此结构的内容依赖于实现，因此在此不再描述。
 */
typedef struct psa_drv_accel_cipher_context_s psa_drv_accel_cipher_context_t;

/** \brief硬件加速分组密码操作设置操作的功能原型。实现此原型的函数应按以下约定命名：~~~~~~ ~~~~｛.c｝psa_drv_accel_cipher_setup_<cipher_NAME>_<MODE>~~~～~~~~-其中
 * -“CIPHER_NAME”是基础分组密码（即AES或DES）的名称
 * -“MODE”是密码操作的块模式（即CBC或CTR）
 *
 * 对于流密码：~~~~~~ ~~~~｛.c｝psa_drv_accel_cher_setup_<cipher_NAME>~~~~其中“cipher_NAME”是流密码的名称（即RC4）
 *
 * \param[in，out]p_context将包含硬件特定密码上下文的结构\param[in]方向指示操作是加密还是解密\param[iin]p_key_data包含要在操作中使用的明文密钥材料的缓冲区\param[in]key_data_size密钥材料的字节大小
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_accel_cipher_setup_t)(psa_drv_accel_cipher_context_t *p_context,
                                                     psa_encrypt_or_decrypt_t direction,
                                                     const uint8_t *p_key_data,
                                                     size_t key_data_size);

/** \brief硬件加速分组密码操作的集合初始化向量操作的函数原型实现此原型的函数应按以下约定命名：~~~~~~
 * -“CIPHER_NAME”是基础分组密码（即AES或DES）的名称
 * -“MODE”是密码操作的块模式（即CBC或CTR）
 *
 * \param[in，out]p_context包含先前设置的硬件特定密码上下文的结构\param[in]p_iv包含初始化向量的缓冲区\param[iin]iv_length“p_iv”内容的字节大小`
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_accel_cipher_set_iv_t)(psa_drv_accel_cipher_context_t *p_context,
                                                      const uint8_t *p_iv,
                                                      size_t iv_length);

/** \硬件加速分组密码操作的更新操作的功能原型。
 *
 *  实现此原型的函数应按以下约定命名：
 * -“CIPHER_NAME”是基础分组密码（即AES或DES）的名称
 * -“MODE”是密码操作的块模式（即CBC或CTR）
 *
 * \param[in，out]p_context先前启动的密码操作的硬件特定结构\param[in]p_input包含要加密或解密的数据的缓冲区\param[iin]input_size“p_input”缓冲区的大小（以字节为单位）\param[out]p_output将放置生成的输出的调用者分配缓冲区\pparam[in]output_sizebuffer\param[out]p_output_length完成后，将包含放置在“p_output”缓冲区中的字节数
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_accel_cipher_update_t)(psa_drv_accel_cipher_context_t *p_context,
                                                      const uint8_t *p_input,
                                                      size_t input_size,
                                                      uint8_t *p_output,
                                                      size_t output_size,
                                                      size_t *p_output_length);

/** \硬件加速分组密码操作完成操作的功能原型。
 *
 *  实现此原型的函数应按以下约定命名：~~~~~~ ~~~~｛.c｝psa_drv_accel_cipher_finish_<cipher_NAME>_<MODE>~~~~其中
 * -“CIPHER_NAME”是基础分组密码（即AES或DES）的名称
 * -“MODE”是密码操作的块模式（即CBC或CTR）
 *
 * \param[in，out]p_context先前启动的密码操作的硬件特定结构\param[out]p_output将放置生成的输出的调用方分配的缓冲区\param[in]output_size“p_output”缓冲区的字节大小\param[out]p_output_length完成后，将包含放置在“p_output”缓冲区中的字节数
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_accel_cipher_finish_t)(psa_drv_accel_cipher_context_t *p_context,
                                                      uint8_t *p_output,
                                                      size_t output_size,
                                                      size_t *p_output_length);

/** \硬件加速分组密码操作中止操作的功能原型。
 *
 *  实现以下原型的函数应按以下约定命名：
 * -“CIPHER_NAME”是基础分组密码（即AES或DES）的名称
 * -“MODE”是密码操作的块模式（即CBC或CTR）
 *
 * \param[in，out]p_context先前启动的密码操作的硬件特定结构
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_accel_cipher_abort_t)(psa_drv_accel_cipher_context_t *p_context);

/**@}*/

/** \defgroup accel_aead使用附加数据的硬件加速身份验证加密
 *
 * 硬件加速的附加数据身份验证加密（AEAD）操作必须在一个函数调用中完成。虽然这给实现者带来了负担，因为内存中必须有足够的空间来存储整个消息，但它阻止了在身份验证操作完成且数据是可信的之前将解密的数据提供给用户。
 */
/**@{*/

/** \brief硬件加速认证加密操作的功能原型。
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~-{.c}psa_drv_accel_aead_<ALGO>_encrypt~~~~其中`ALGO`是aead算法的名称
 *
 * \param[in]p_key指向密钥材料的指针\param[in]key_length密钥材料的字节大小\param[iin]alg要计算的AEAD算法（\c PSA_alg_XXX值，以使#PSA_alg_IS_AEAD（`alg`）为真）\param[in]nonce nonce或IV使用\param[i]nonce length“nonce”缓冲区的字节大小/param[in]additional_data将被MACed但未加密。\param[in]additional_data_length“additional_data”的大小（字节）\param[in]将进行MAC和加密的明文数据。\param[in]明文_length“明文”的大小（以字节为单位）\param[out]密文已验证和加密数据的输出缓冲区。附加数据不是此输出的一部分。对于加密数据和认证标签被定义为单独输出的算法，认证标签被附加到加密数据。\param[in]ciphertext_size“密文”缓冲区的大小（以字节为单位）这必须至少为#PSA_EAD_ENCRYPT_OUTPUT_size（`alg`，`plaintext_length`）。\param[out]ciphertext_length成功时，“密文”缓冲区中输出的大小
 *
 * \retval#PSA_SUCCESS
 *
 */
typedef psa_status_t (*psa_drv_accel_aead_encrypt_t)(const uint8_t *p_key,
                                                     size_t key_length,
                                                     psa_algorithm_t alg,
                                                     const uint8_t *nonce,
                                                     size_t nonce_length,
                                                     const uint8_t *additional_data,
                                                     size_t additional_data_length,
                                                     const uint8_t *plaintext,
                                                     size_t plaintext_length,
                                                     uint8_t *ciphertext,
                                                     size_t ciphertext_size,
                                                     size_t *ciphertext_length);

/** \硬件加速认证解密操作的功能原型。
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~-{.c｝psa_dv_accel_aead_<ALGO>_decrypt ~~~#~~~*~~~*其中`ALGO'是aead算法的名称\param[in]p_key指向密钥材料的指针\param[iin]key_length密钥材料的字节大小\param[in]alg要计算的aead算法（\c psa_alg_XXX值，以便#psa_alg_is_aead（“alg”）为真）\param[in]nonce nonce或IV使用\param[iin]nonce_length“nonce”缓冲区的大小（字节）\param[in]additional_data已MACed但未加密的附加数据\param[in]additional _data_length已MACed和加密的密文数据对于加密数据和身份验证标记为定义为单独的输入，缓冲区必须包含加密数据，后跟身份验证标记。\param[in]ciphertext_length“密文”的字节大小\param[out]明文解密数据的输出缓冲区\param[in]plaintext_Size“明文”缓冲区的字节大小这必须至少为#PSA_EAD_DECRYPT_Output_Size（`alg`，`ciphertext_length`）。\param[out]plaintext_length成功时，明文缓冲区中的输出大小
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_accel_aead_decrypt_t)(const uint8_t *p_key,
                                                     size_t key_length,
                                                     psa_algorithm_t alg,
                                                     const uint8_t *nonce,
                                                     size_t nonce_length,
                                                     const uint8_t *additional_data,
                                                     size_t additional_data_length,
                                                     const uint8_t *ciphertext,
                                                     size_t ciphertext_length,
                                                     uint8_t *plaintext,
                                                     size_t plaintext_size,
                                                     size_t *plaintext_length);

/**@}*/

/** \defgroup accel_非对称硬件加速非对称加密
 *
 * 由于可以（或应该）使用非对称密钥加密或签名的数据量受到密钥大小的限制，因此硬件加速的非对称密钥操作必须在单函数调用中完成。
 */
/**@{*/


/**
 * \硬件加速不对称符号操作的功能原型。
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~{.c}psa_drv_accel_assimetric_<ALGO>_sign ~~~~其中`ALGO`是签名算法的名称
 *
 * 此函数支持从psa_export_key（）输出的任何非对称密钥作为\pp_key中的缓冲区。有关格式，请参阅\ref psa_export_key（）的文档。
 *
 * \param[in]p_key包含私钥材料的缓冲区\param[in]key_size“p_key”数据的大小（以字节为单位）\param[iin]alg与“p_key`”类型兼容的签名算法\param[in]p_hash要签名的哈希或消息\param[i]hash_length“p_hash`缓冲区的大小（字节为单位[in]signature_size“p_signature”缓冲区的大小（以字节为单位）\param[out]p_signature_length成功时，构成返回签名值的字节数
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_accel_asymmetric_sign_t)(const uint8_t *p_key,
                                                        size_t key_size,
                                                        psa_algorithm_t alg,
                                                        psa_key_type_t key_type,
                                                        const uint8_t *p_hash,
                                                        size_t hash_length,
                                                        uint8_t *p_signature,
                                                        size_t signature_size,
                                                        size_t *p_signature_length);

/**
 * \硬件加速签名验证操作的功能原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~{.c}psa_drv_accel_accymmetric_<ALGO>_verify ~~~～~~~~-其中`ALGO`是签名算法的名称
 *
 * 此函数支持\ref psa_export_public_key（）中的任何输出作为\p p_key中的缓冲区。有关公钥的格式，请参阅\ref psa_export_public_key（）的文档，有关其他密钥类型的格式，可参阅\ref psa_export_key（。
 *
 * \param[in]p_key包含公钥材料的缓冲区\param[in]key_size“p_key”数据的字节大小\param[iin]alg与“key”类型兼容的签名算法\param[in]p_hash要验证其签名的哈希或消息\param[i]hash_length“p_hash”缓冲区的字节大小\param[in]p_signature包含签名的缓冲区verify \param[in]signature_length“p_signature”缓冲区的大小（字节）
 *
 * \retval#PSA_SUCCESS签名有效。
 */
typedef psa_status_t (*psa_drv_accel_asymmetric_verify_t)(const uint8_t *p_key,
                                                          size_t key_size,
                                                          psa_algorithm_t alg,
                                                          psa_key_type_t key_type,
                                                          const uint8_t *p_hash,
                                                          size_t hash_length,
                                                          const uint8_t *p_signature,
                                                          size_t signature_length);

/**
 * \硬件加速非对称加密操作的功能原型
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~{.c}psa_drv_accel_accymmetric_<ALGO>_encrypt~~~~+~~~~-其中`ALGO`是加密算法的名称
 *
 * 此函数支持\ref psa_export_public_key（）中的任何输出作为\p p_key中的缓冲区。有关公钥的格式，请参阅\ref psa_export_public_key（）的文档，有关其他密钥类型的格式，可参阅\ref psa_export_key（。
 *
 * \param[in]p_key包含公钥材料的缓冲区\param[in]key_size“p_key”数据的字节大小\param[iin]alg与“key”类型兼容的非对称加密算法\param[in]p_input要加密的消息\param[i]input_length“p_input”缓冲区的字节大小\param[in]p_salt盐或标签，如果加密算法支持，则传递“NULL”如果算法不支持salt，则传递‘NULL’如果算法支持可选salt，而您不希望传递salt，请传递‘NULL”。对于#PSA_LG_RSA_PKCS1V15_CRYPT，不支持盐。\param[in]salt_length“p_salt”缓冲区的大小（以字节为单位）如果“p_salte”为“NULL”，则传递0。\param[out]p_output要写入加密消息的缓冲区\param[in]output_Size“p_output_Size'缓冲区的尺寸（以字节计）\param[ut]p_output_length成功时，构成返回输出的字节数
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_accel_asymmetric_encrypt_t)(const uint8_t *p_key,
                                                           size_t key_size,
                                                           psa_algorithm_t alg,
                                                           psa_key_type_t key_type,
                                                           const uint8_t *p_input,
                                                           size_t input_length,
                                                           const uint8_t *p_salt,
                                                           size_t salt_length,
                                                           uint8_t *p_output,
                                                           size_t output_size,
                                                           size_t *p_output_length);

/**
 * \brief硬件的功能原型=acce；重复非对称解密操作
 *
 * 实现此原型的函数应按以下约定命名：~~~~~~ ~~~~ ~~~-{.c}psa_drv_accel_accymmetric_<ALGO>_decrypt ~~~~其中`ALGO`是加密算法的名称
 *
 * 此函数支持从psa_export_key（）输出的任何非对称密钥作为\pp_key中的缓冲区。有关格式，请参阅\ref psa_export_key（）的文档。
 *
 * \param[in]p_key包含私钥材料的缓冲区\param[in]key_size“p_key”数据的字节大小\param[iin]alg与“key”类型兼容的非对称加密算法\param[in]p_input要解密的消息\param[i]input_length“p_input”缓冲区的字节大小\param[in]p_salt盐或标签，如果加密算法支持，如果算法不支持salt，则传递“NULL”。如果算法支持可选的salt，并且您不想传递salt，请传递“NULL”。对于#PSA_LG_RSA_PKCS1V15_CRYPT，不支持salt \param[in]salt_length“p_salt”缓冲区的大小（以字节为单位）如果“p_salt'为“NULL”，则将0 \param[out]p_outputBuffer传递到要写入解密消息的位置\param[iin]output_Size“p_output”缓冲区大小（以字符为单位）\param[out]p_output_length成功时，返回输出的字节数
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_accel_asymmetric_decrypt_t)(const uint8_t *p_key,
                                                           size_t key_size,
                                                           psa_algorithm_t alg,
                                                           psa_key_type_t key_type,
                                                           const uint8_t *p_input,
                                                           size_t input_length,
                                                           const uint8_t *p_salt,
                                                           size_t salt_length,
                                                           uint8_t *p_output,
                                                           size_t output_size,
                                                           size_t *p_output_length);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_ACCEL_DRIVER_H */

