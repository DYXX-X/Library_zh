/**
 * \psa/crypto_se_driver文件。简要PSA外部密码处理器驱动程序模块
 *
 * 此标头声明通过不透明引用访问密钥材料的加密驱动程序的类型和函数签名。这意味着密码处理器具有与PSA Crypto实现运行的空间（通常是安全元素（SE））分开的密钥存储。
 *
 * 该文件是PSA Crypto驱动程序HAL（硬件抽象层）的一部分，包含驱动程序开发人员要实现的功能，以使PSA Cryptography API实现能够以标准化的方式调用硬件。驱动程序作者实现的包含驱动程序HAL的函数不打算由应用程序开发人员调用。
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
#ifndef PSA_CRYPTO_SE_DRIVER_H
#define PSA_CRYPTO_SE_DRIVER_H

#include "crypto_driver_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup se_init安全元素驱动程序初始化
 */
/**@{*/

/** \简要的驱动程序上下文结构
 *
 * 驱动程序函数接收指向此结构的指针。每个注册的驱动程序都有一个此结构的实例。
 *
 * 实现必须包括此处指定的字段，也可以包括其他字段。
 */
typedef struct {
    /** 指向驱动程序持久数据的只读指针。
     *
     * 驱动程序通常使用这些持久数据来跟踪可用的插槽号。这只是一个指导原则：驱动程序可以出于任何目的使用持久数据，同时要记住对持久数据保存到存储的时间的限制：只有在调用接收到持久数据的可写指针的某些函数后，才能保存持久数据。
     *
     * 核心为持久数据分配内存缓冲区。指针保证适合任何数据类型，如“malloc”返回的指针（但内核可以使用任何方法来分配缓冲区，不一定是“malloc”）。
     *
     * 此缓冲区的大小在此结构的\c persistent_data_size字段中。
     *
     * 在第一次初始化驱动程序之前，持久数据的内容都是零位。在驱动程序升级后，如果持久数据的大小增加了，则原始数据的右侧将用零填充；如果大小已减小，则将原始数据截断为新大小。
     *
     * 此指针指向只读数据。仅允许少数驱动程序函数修改持久数据。这些函数接收可写指针。这些功能包括：
     * -psa_drv_se_t:：p_init
     * -psa_drv_se_key_management_t:：p_allocate
     * -psa_drv_se_key_management_t:：p_destroy
     *
     * PSA Cryptography核心将持久数据从一个会话保存到下一个会话。它在从调用允许修改持久数据的驱动程序方法的API函数返回之前执行此操作，具体而言：
     * -psa_crypto_init（）导致调用psa_drv_set:：p_init，并可能调用psa_derv_se_key_management_t:：p_destroy以完成因电源故障而中断的操作。
     * -密钥创建函数会导致调用psa_drv_se_Key_management_t:：p_allocate，如果发生错误，则可能会导致调用psa_drv_se_Key_management_t:：p_destroy。
     * -psa_dispy_key（）导致调用psa_drv_se_key_management_t:：p_destroy。
     */
    const void *const persistent_data;

    /** \n persistent_data的大小（以字节为单位）。
     *
     * 注册驱动程序时，该值始终等于：：psa_drv_se_t结构的“persistent_data_size”字段的值。
     */
    const size_t persistent_data_size;

    /** 驾驶员瞬态数据。
     *
     * 内核将此值初始化为0，之后不会读取或修改它。驱动程序可以在该字段中存储它想要的任何内容。
     */
    uintptr_t transient_data;
} psa_drv_se_context_t;

/** \brief驱动程序初始化功能。
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in，out]persistent_data指向允许写入的持久数据的指针。\param location为其注册此驱动程序的位置值。将为其生存期在此位置的所有密钥调用驱动程序。
 *
 * \retval#PSA_SUCCESS驱动程序正在运行。核心将更新存储中的持久数据。\return任何其他返回值都将阻止在此会话中使用驱动程序。核心不会更新存储中的持久数据。
 */
typedef psa_status_t (*psa_drv_se_init_t)(psa_drv_se_context_t *drv_context,
                                          void *persistent_data,
                                          psa_key_location_t location);

#if defined(__DOXYGEN_ONLY__) || !defined(MBEDTLS_PSA_CRYPTO_SE_C)
/* 启用了安全元素支持的Mbed Crypto在Crypto_types中定义了此类型。h，因为它也通过特定于实现的扩展对应用程序可见。对于PSA Cryptography规范，此类型仅通过crypto_se_driver.h可见。*/
/**PSA Crypto实现的核心部分和驱动程序之间的密钥槽的内部指定。此值的含义取决于驱动程序。*/
typedef uint64_t psa_key_slot_number_t;
#endif /* __DOXYGEN_ONLY__ || !MBEDTLS_PSA_CRYPTO_SE_C */

/**@}*/

/** \defgroup se_mac安全元素消息验证代码使用安全元素生成和验证消息验证代码（mac）可以作为单个函数调用（通过“psa_drv_se_mac_generate_t”或“psa_derv_se_mac_verify_t”函数）完成，也可以按以下顺序部分完成：
 * -`psa_drv_se_mac_setup_t`
 * -`psa_drv_se_mac_update_t`
 * -`psa_drv_se_mac_update_t`
 * - ...
 * -“psa_drv_se_mac_finish_t”或“psa_derv_se_mac-finish_verify_t”`
 *
 * 如果需要终止先前启动的安全元素MAC操作，则应通过“psa_drv_se_MAC_abort_t”来完成。否则，可能会导致分配的资源无法释放或出现其他未定义的行为。
 */
/**@{*/
/** \brief为PSA加密驱动程序实现启动安全元素MAC操作的函数
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in，out]op_context将包含硬件特定MAC上下文的结构\param[in]key_slot用于操作的密钥槽\param[iin]算法用于MAC操作的算法
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_se_mac_setup_t)(psa_drv_se_context_t *drv_context,
                                               void *op_context,
                                               psa_key_slot_number_t key_slot,
                                               psa_algorithm_t algorithm);

/** \brief继续先前启动的安全元素MAC操作的功能
 *
 * \param[in，out]op_context要更新的先前建立的MAC操作的硬件特定结构\param[in]p_input包含要附加到MAC操作的消息的缓冲区\param[iin]input_length输入消息缓冲区的字节大小
 */
typedef psa_status_t (*psa_drv_se_mac_update_t)(void *op_context,
                                                const uint8_t *p_input,
                                                size_t input_length);

/** \简述通过返回结果MAC来完成先前启动的安全元素MAC操作的功能。
 *
 * \param[in，out]op_context要完成的先前启动的MAC操作的硬件特定结构\param[out]p_MAC将放置生成的MAC的缓冲区\param[in]MAC_size已分配给“输出”缓冲区的缓冲区大小（以字节为单位）\param[out]p_MAC_length完成后，将包含放置在“p_MAC”缓冲区中的字节数
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_se_mac_finish_t)(void *op_context,
                                                uint8_t *p_mac,
                                                size_t mac_size,
                                                size_t *p_mac_length);

/** \brief通过将生成的MAC与提供的值进行比较来完成先前启动的安全元素MAC操作的功能
 *
 * \param[in，out]op_context要完成的先前启动的MAC操作的硬件特定结构\param[in]p_MAC将生成的MAC与之进行比较的MAC值\param[iin]MAC_length存储在`p_MAC中的值的字节大小`
 *
 * \retval#PSA_SUCCESS操作成功完成，并且MAC彼此匹配\retval#PSTA_ERROR_INVALID_SIGNATURE操作已成功完成，但计算的MAC与提供的MAC不匹配
 */
typedef psa_status_t (*psa_drv_se_mac_finish_verify_t)(void *op_context,
                                                       const uint8_t *p_mac,
                                                       size_t mac_length);

/** \brief中止先前启动的安全元素MAC操作的函数
 *
 * \param[in，out]op_context要中止先前启动的MAC操作的硬件特定结构
 */
typedef psa_status_t (*psa_drv_se_mac_abort_t)(void *op_context);

/** \brief在一个命令中执行安全元素MAC操作并返回计算出的MAC的函数
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in]p_input包含要MAC化的消息的缓冲区\param[in]input_length“p_input”的大小（字节）\param[iin]key_slot要使用的密钥的槽\param[in]alg用于MAC操作基础的算法\param[out]p_MAC将放置生成的MAC的缓冲区/param[in]MAC_size“p_MAC”缓冲区的大小（以字节为单位）\param[out]p_MAC_length之后完成，将包含放置在“输出”缓冲区中的字节数
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_se_mac_generate_t)(psa_drv_se_context_t *drv_context,
                                                  const uint8_t *p_input,
                                                  size_t input_length,
                                                  psa_key_slot_number_t key_slot,
                                                  psa_algorithm_t alg,
                                                  uint8_t *p_mac,
                                                  size_t mac_size,
                                                  size_t *p_mac_length);

/** \brief在一个命令中执行安全元素MAC操作并将生成的MAC与提供的值进行比较的功能
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in]p_input包含要MACed的消息的缓冲区\param[in]input_length“input”的大小（字节）\param[iin]key_slot要使用的密钥的槽\param[in]alg用于MAC操作基础的算法\param[iin]p_MAC生成的MAC将与之进行比较的MAC值\param[in]MAC_length以字节为单位的“MAC”的大小`
 *
 * \retval#PSA_SUCCESS操作成功完成，并且MAC彼此匹配\retval#PSTA_ERROR_INVALID_SIGNATURE操作已成功完成，但计算的MAC与提供的MAC不匹配
 */
typedef psa_status_t (*psa_drv_se_mac_verify_t)(psa_drv_se_context_t *drv_context,
                                                const uint8_t *p_input,
                                                size_t input_length,
                                                psa_key_slot_number_t key_slot,
                                                psa_algorithm_t alg,
                                                const uint8_t *p_mac,
                                                size_t mac_length);

/** \brief包含执行安全元素MAC操作所需的所有函数指针的结构
 *
 * PSA Crypto API实现应在启动时适当填充表。
 *
 * 如果其中一个函数未实现（例如“psa_drv_se_mac_generate_t”），则应将其设置为NULL。
 *
 * 驱动程序实现者应确保他们实现对其硬件有意义的所有功能，并提供完整的解决方案（例如，如果他们支持“p_setup”，则还应支持“p_update”和“p_finish”或“p_finish_verify”中的至少一个）。
 *
 */
typedef struct {
    /**The 硬件特定安全元素MAC上下文结构的字节大小
    */
    size_t                    context_size;
    /** 执行MAC设置操作的功能
     */
    psa_drv_se_mac_setup_t          p_setup;
    /** 执行MAC更新操作的功能
     */
    psa_drv_se_mac_update_t         p_update;
    /** 完成MAC操作的函数
     */
    psa_drv_se_mac_finish_t         p_finish;
    /** 通过验证检查完成MAC操作的函数
     */
    psa_drv_se_mac_finish_verify_t  p_finish_verify;
    /** 中止先前启动的MAC操作的函数
     */
    psa_drv_se_mac_abort_t          p_abort;
    /** 在一次调用中执行MAC操作的函数
     */
    psa_drv_se_mac_generate_t       p_mac;
    /** 在一次调用中执行MAC和验证操作的函数
     */
    psa_drv_se_mac_verify_t         p_mac_verify;
} psa_drv_se_mac_t;
/**@}*/

/** \defgroup se_cipher安全元素对称密码
 *
 * 在除ECB之外的块模式中使用安全元素密钥的加密和解密必须使用以下流程分多个部分完成：
 * -`psa_drv_se_cipher_setup_t`
 * -“psa_drv_se_cipher_set_iv_t”（可选，取决于块模式）
 * -`psa_drv_se_cipher_update_t`
 * -`psa_drv_se_cipher_update_t`
 * - ...
 * -`psa_drv_se_cipher_finish_t`
 *
 * 如果需要终止先前启动的安全元素密码操作，则应通过“psa_drv_se_Cipher_abort_t”完成。否则，可能会导致分配的资源无法释放或出现其他未定义的行为。
 *
 * 在PSA Cryptographic API实现使用底层硬件或驱动程序不支持的块模式的情况下，它可以自己构造块模式，同时为密码操作调用“PSA_drv_se_cipher_ecb_t”函数。
 */
/**@{*/

/** \brief为安全元件驱动程序提供密码设置功能的函数
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in，out]op_context将包含硬件特定密码上下文的结构。\param[in]key_slot用于操作的密钥槽\param[in]算法用于密码操作的算法\param[iin]方向指示操作是加密还是解密
 *
 * \retval#PSA_SUCCESS\retval#PSA错误_不支持
 */
typedef psa_status_t (*psa_drv_se_cipher_setup_t)(psa_drv_se_context_t *drv_context,
                                                  void *op_context,
                                                  psa_key_slot_number_t key_slot,
                                                  psa_algorithm_t algorithm,
                                                  psa_encrypt_or_decrypt_t direction);

/** \brief为安全元素密码操作设置初始化向量（如果需要）的函数
 *
 * 理由：psa加密API中的“psa_se_cipher_*”操作有两个IV功能：一个用于设置IV，另一个用于在内部生成IV。驱动程序不需要实现生成功能，因为PSA Crypto实现可以使用其RNG特性进行生成。
 *
 * \param[in，out]op_context包含先前设置的硬件特定密码上下文的结构\param[in]p_iv包含初始化向量的缓冲区\param[iin]iv_length“p_iv”缓冲区的大小（以字节为单位）
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_se_cipher_set_iv_t)(void *op_context,
                                                   const uint8_t *p_iv,
                                                   size_t iv_length);

/** \brief继续先前启动的安全元素密码操作的函数
 *
 * \param[in，out]op_context先前启动的密码操作的硬件特定结构\param[in]p_input包含要加密/解密的数据的缓冲区\param[iin]input_size“p_input”指向的缓冲区的大小（以字节为单位）\param[out]p_output将放置输出的调用者分配的缓冲区/param[in]output_size`p_output`buffer\param[out]p_output_length完成后，将包含放置在“p_output`缓冲区中的字节数
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_se_cipher_update_t)(void *op_context,
                                                   const uint8_t *p_input,
                                                   size_t input_size,
                                                   uint8_t *p_output,
                                                   size_t output_size,
                                                   size_t *p_output_length);

/** \brief完成先前启动的安全元素密码操作的函数
 *
 * \param[in，out]op_context先前启动的密码操作的硬件特定结构\param[out]p_output将放置输出的调用者分配的缓冲区\param[in]output_size“p_output'缓冲区的分配大小（以字节为单位）\param[out]p_output_length完成后，将包含放置在“p_output”缓冲区中的字节数
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_se_cipher_finish_t)(void *op_context,
                                                   uint8_t *p_output,
                                                   size_t output_size,
                                                   size_t *p_output_length);

/** \brief中止先前启动的安全元素密码操作的函数
 *
 * \param[in，out]op_context先前启动的密码操作的硬件特定结构
 */
typedef psa_status_t (*psa_drv_se_cipher_abort_t)(void *op_context);

/** \brief为安全元素密码操作执行ECB块模式的函数
 *
 * 注意：此函数只能用于不提供所需的高级操作的实现。
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in]key_slot要用于操作的密钥槽\param[in]算法要用于密码操作的算法\param[iin]方向指示操作是加密还是解密\param[in]p_input包含要加密/解密的数据的缓冲区\param[i]input_size“p_input”指向的缓冲区的大小（以字节为单位）\param[out]p_output将放置输出的调用者分配缓冲区\param[in]output_size“p_output”缓冲区的分配大小（以字节为单位）
 *
 * \retval#PSA_SUCCESS\retval#PSA错误_不支持
 */
typedef psa_status_t (*psa_drv_se_cipher_ecb_t)(psa_drv_se_context_t *drv_context,
                                                psa_key_slot_number_t key_slot,
                                                psa_algorithm_t algorithm,
                                                psa_encrypt_or_decrypt_t direction,
                                                const uint8_t *p_input,
                                                size_t input_size,
                                                uint8_t *p_output,
                                                size_t output_size);

/**
 * \brief包含使用安全元素实现密码操作所需的所有函数指针的结构。
 *
 * PSA Crypto API实现应在启动时或构建时适当填充表的实例。
 *
 * 如果其中一个函数未实现（例如“psa_drv_se_cipher_ecb_t”），则应将其设置为NULL。
 */
typedef struct {
    /** 硬件特定安全元素密码上下文结构的字节大小
     */
    size_t               context_size;
    /**执行密码设置操作的函数*/
    psa_drv_se_cipher_setup_t  p_setup;
    /**设置密码IV的函数（如果需要）*/
    psa_drv_se_cipher_set_iv_t p_set_iv;
    /**执行密码更新操作的函数*/
    psa_drv_se_cipher_update_t p_update;
    /**完成密码操作的函数*/
    psa_drv_se_cipher_finish_t p_finish;
    /**中止密码操作的函数*/
    psa_drv_se_cipher_abort_t  p_abort;
    /** 执行加密操作的ECB模式的函数（危险：PSA加密客户端API的客户端不应直接使用ECB模式）
     */
    psa_drv_se_cipher_ecb_t    p_ecb;
} psa_drv_se_cipher_t;

/**@}*/

/** \defgroup se_asymmetric安全元素非对称加密
 *
 * 由于可以（或应该）使用非对称密钥加密或签名的数据量受到密钥大小的限制，因此必须在单个函数调用中使用安全元素中的密钥进行非对称密钥操作。
 */
/**@{*/

/**
 * \brief在安全元素中使用私钥签名哈希或短消息的函数
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in]key_slot非对称密钥对的密钥槽\param[in]alg与“key”类型兼容的签名算法\param[iin]p_hash要签名的哈希\param[in]hash_length“p_hash”缓冲区的大小（以字节为单位）\param[out]p_signature要写入签名的缓冲区\param[i]signature_Size“p_signature”缓冲区大小（以字符为单位）success，构成返回的签名值的字节数
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_se_asymmetric_sign_t)(psa_drv_se_context_t *drv_context,
                                                     psa_key_slot_number_t key_slot,
                                                     psa_algorithm_t alg,
                                                     const uint8_t *p_hash,
                                                     size_t hash_length,
                                                     uint8_t *p_signature,
                                                     size_t signature_size,
                                                     size_t *p_signature_length);

/**
 * \brief在安全元素中使用非对称公钥验证哈希或短消息签名的函数
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in]key_slot公钥或非对称密钥对的密钥槽\param[in]alg与“key”类型兼容的签名算法\param[iin]p_hash要验证其签名的哈希\param[in]hash_length“p_hash”缓冲区的大小（字节）\param[i]p_signature包含要验证的签名的缓冲区字节
 *
 * \retval#PSA_SUCCESS签名有效。
 */
typedef psa_status_t (*psa_drv_se_asymmetric_verify_t)(psa_drv_se_context_t *drv_context,
                                                       psa_key_slot_number_t key_slot,
                                                       psa_algorithm_t alg,
                                                       const uint8_t *p_hash,
                                                       size_t hash_length,
                                                       const uint8_t *p_signature,
                                                       size_t signature_length);

/**
 * \brief在安全元素中使用非对称公钥加密短消息的函数
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in]key_slot公钥或非对称密钥对的密钥槽\param[in]alg与“key”类型兼容的非对称加密算法/param[in]p_input要加密的消息\param[iin]input_length“p_input”缓冲区的大小（以字节为单位）\param[in]p_salt加密算法支持的盐或标签如果算法不支持盐，则传递“NULL”。如果算法支持可选的salt，并且您不想传递salt，请传递“NULL”。对于#PSA_LG_RSA_PKCS1V15_CRYPT，不支持盐。\param[in]salt_length“p_salt”缓冲区的大小（以字节为单位）如果“p_salte”为“NULL”，则传递0。\param[out]p_output要写入加密消息的缓冲区\param[in]output_Size“p_output_Size'缓冲区的尺寸（以字节计）\param[ut]p_output_length成功时，构成返回输出的字节数
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_se_asymmetric_encrypt_t)(psa_drv_se_context_t *drv_context,
                                                        psa_key_slot_number_t key_slot,
                                                        psa_algorithm_t alg,
                                                        const uint8_t *p_input,
                                                        size_t input_length,
                                                        const uint8_t *p_salt,
                                                        size_t salt_length,
                                                        uint8_t *p_output,
                                                        size_t output_size,
                                                        size_t *p_output_length);

/**
 * \brief在安全元素中使用非对称私钥解密短消息的函数。
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in]key_slot非对称密钥对的密钥槽\param[in]alg与“key”类型兼容的非对称加密算法\param[iin]p_input要解密的消息\param[in]input_length“p_input”缓冲区的大小（以字节为单位）\param[iin]p_salt如果加密算法支持，则返回“NULL”。如果算法支持可选的salt，并且您不想传递salt，请传递“NULL”。对于#PSA_LG_RSA_PKCS1V15_CRYPT，不支持盐。\param[in]salt_length“p_salt”缓冲区的大小（以字节为单位）如果“p_salte”为“NULL”，则传递0。\param[out]p_output要写入解密消息的缓冲区\param[in]output_Size“p_output”缓冲区大小（以秒为单位）\param[ut]p_output_length成功时，构成返回输出的字节数
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_se_asymmetric_decrypt_t)(psa_drv_se_context_t *drv_context,
                                                        psa_key_slot_number_t key_slot,
                                                        psa_algorithm_t alg,
                                                        const uint8_t *p_input,
                                                        size_t input_length,
                                                        const uint8_t *p_salt,
                                                        size_t salt_length,
                                                        uint8_t *p_output,
                                                        size_t output_size,
                                                        size_t *p_output_length);

/**
 * \brief包含使用安全元素实现非对称加密操作所需的所有函数指针的结构。
 *
 * PSA Crypto API实现应在启动时或构建时适当填充表的实例。
 *
 * 如果其中一个函数未实现，则应将其设置为NULL。
 */
typedef struct {
    /**执行非对称符号操作的函数*/
    psa_drv_se_asymmetric_sign_t    p_sign;
    /**执行非对称验证操作的函数*/
    psa_drv_se_asymmetric_verify_t  p_verify;
    /**执行非对称加密操作的函数*/
    psa_drv_se_asymmetric_encrypt_t p_encrypt;
    /**执行非对称解密操作的函数*/
    psa_drv_se_asymmetric_decrypt_t p_decrypt;
} psa_drv_se_asymmetric_t;

/**@}*/

/** \defgroup se_aead Secure Element Authenticated Encryption with Additional Data使用附加数据进行安全元素身份验证加密（aead）操作必须在一个函数调用中完成。虽然这给实现者带来了负担，因为内存中必须有足够的空间来存储整个消息，但它阻止了在身份验证操作完成且数据是可信的之前将解密的数据提供给用户。
 */
/**@{*/

/** \brief执行安全元素身份验证加密操作的函数
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in]key_slot包含要使用的密钥的插槽。\param[in]算法要计算的AEAD算法（\c PSA_ALG_XXX值，使得#PSA_ALG_IS_AEAD（`ALG`）为真）\param[in]p_nonce nonce或IV使用\param[iin]nonce_length“p_nonce”缓冲区的大小（以字节为单位）\param[in]p_additional_data将被验证但未加密的附加数据\param[in]additional_data_length将要验证和加密的数据\param[in]plaintext_length“p_plaintext”的大小（以字节为单位）\param[out]p_ciphertext已验证和加密数据的输出缓冲区。附加数据不是此输出的一部分。对于加密数据和认证标签被定义为单独输出的算法，认证标签被附加到加密数据。\param[in]ciphertext_size“p_ciphertext”缓冲区的大小（字节）\param[out]p_ciphertext_length成功时，“p_cipher text”缓冲中的输出大小
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_se_aead_encrypt_t)(psa_drv_se_context_t *drv_context,
                                                  psa_key_slot_number_t key_slot,
                                                  psa_algorithm_t algorithm,
                                                  const uint8_t *p_nonce,
                                                  size_t nonce_length,
                                                  const uint8_t *p_additional_data,
                                                  size_t additional_data_length,
                                                  const uint8_t *p_plaintext,
                                                  size_t plaintext_length,
                                                  uint8_t *p_ciphertext,
                                                  size_t ciphertext_size,
                                                  size_t *p_ciphertext_length);

/** 执行安全元素认证解密操作的函数
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in]key_slot包含要使用的密钥的插槽\param[in]algorithm要计算的AEAD算法（\c PSA_ALG_XXX值使得#PSA_ALG_IS_AEAD（`ALG`）为真）\param[iin]p_nonce nonce或IV要使用\param[in]nonce_length“p_nonce”缓冲区的大小（字节）\param[in]p_additional_data已验证但未加密的附加数据`p_additional_data`in bytes \param[in]p_ciphertext经过身份验证和加密的数据。对于加密数据和认证标签被定义为单独输入的算法，缓冲区必须包含加密数据，然后是认证标签。\param[in]ciphertext_length“p_ciphertext”的大小（以字节为单位）\param[out]p_plaintext解密数据的输出缓冲区\param[in]plaintext_Size“p_plainttext”缓冲区的大小（字节为单位
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_se_aead_decrypt_t)(psa_drv_se_context_t *drv_context,
                                                  psa_key_slot_number_t key_slot,
                                                  psa_algorithm_t algorithm,
                                                  const uint8_t *p_nonce,
                                                  size_t nonce_length,
                                                  const uint8_t *p_additional_data,
                                                  size_t additional_data_length,
                                                  const uint8_t *p_ciphertext,
                                                  size_t ciphertext_length,
                                                  uint8_t *p_plaintext,
                                                  size_t plaintext_size,
                                                  size_t *p_plaintext_length);

/**
 * \brief包含实现安全元素Authenticated Encryption with Additional Data操作所需的所有函数指针的结构
 *
 * PSA Crypto API实现应在启动时适当填充表的实例。
 *
 * 如果其中一个函数未实现，则应将其设置为NULL。
 */
typedef struct {
    /**执行AEAD加密操作的函数*/
    psa_drv_se_aead_encrypt_t p_encrypt;
    /**执行AEAD解密操作的函数*/
    psa_drv_se_aead_decrypt_t p_decrypt;
} psa_drv_se_aead_t;
/**@}*/

/** \defgroup se_key_management安全元素密钥管理当前，密钥管理仅限于在明文中导入密钥、销毁密钥和在明文中导出密钥。是否可以导出密钥取决于密钥槽上的密钥策略。
 */
/**@{*/

/** 指示如何创建密钥的枚举。
 */
typedef enum
{
    PSA_KEY_CREATION_IMPORT, /**<在psa_import_key（）期间*/
    PSA_KEY_CREATION_GENERATE, /**<在psa_generate_key（）期间*/
    PSA_KEY_CREATION_DERIVE, /**<在psa_key_derive_output_key（）期间*/
    PSA_KEY_CREATION_COPY, /**<在psa_copy_key（）期间*/

#ifndef __DOXYGEN_ONLY__
    /** 正在使用mbedtls_psa_register_se_key（）注册密钥。
     *
     * 内核仅将此值传递给psa_drv_se_key_management_t:：p_validate_slot_number，而不是传递给psaqudrv_see_key_management _t:：p_allocate。对“p_validate_slot_number”的调用之后没有对驱动程序的任何其他调用：如果对“p_validate_slot_number”的调用成功，或者“p_validate _slot_nnumber”为空，则密钥被视为已成功注册。
     *
     * 使用此创建方法，如果给定的属性与插槽中的现有密钥兼容，则驱动程序必须返回#PSA_SUCCESS；如果驱动程序可以确定没有具有指定插槽编号的密钥，则必须返回#PSA _ERROR_DOES_NOT_EXIST。
     *
     * 这是一个Mbed Crypto扩展。
     */
    PSA_KEY_CREATION_REGISTER,
#endif
} psa_key_creation_method_t;

/** \brief为键分配槽的函数。
 *
 * 要在安全元素的特定插槽中创建密钥，核心首先调用此函数以确定有效的插槽编号，然后调用一个函数以在该插槽中创建关键材料。在标称条件下（即，如果没有发生错误），调用PSA Cryptography API中的密钥创建函数的效果如下：
 * -#内核调用psa_drv_se_key_management_t:：p_allocate（或在某些实现中调用psa_derv_se_key_management_t:：p_validate_slot_number）。驱动程序根据密钥属性和安全元素的状态选择（或验证）合适的插槽号。
 * -#核心调用驱动程序中的密钥创建函数。
 *
 * PSA Cryptography API中的密钥创建功能包括：
 * -psa_import_key（），它使用\p method=#psa_key_CREATION_import调用“p_allocate”，然后调用psa_drv_se_key_management_t:：p_import。
 * -psa_generate_key（），它使用\p method=#psa_key_CREATION_generate调用“p_allocate”，然后调用psa_drv_se_key_management_t:：p_import。
 * -psa_key_derivation_output_key（），它会使用\p method=#psa_key_CREATION_DRIVE调用“p_allocate”，然后调用psa_drv_se_key_derivatation_t:：p_derival。
 * -psa_copy_key（），它使用\p method=#psa_key_CREATION_copy调用“p_allocate”，然后调用psa_drv_se_key_management_t:：p_export。
 *
 * 如果出现错误，其他行为也是可能的。
 * -如果PSA密码子系统在第一步之后死亡，例如因为设备突然断电，则第二步可能永远不会发生，或者可能在重置和重新初始化之后发生。或者，在重置和重新初始化之后，内核可以对分配（或验证）的插槽号调用psa_drv_se_key_management_t:：p_destroy，而不是调用密钥创建函数。
 * -如果发生错误，内核可能会对分配（或验证）的插槽号调用psa_drv_se_key_management_t:：p_destroy，而不是调用密钥创建函数。
 *
 * 错误和系统重置也会影响驱动程序的持久数据。如果重置发生在整个密钥创建过程完成之前（在上述第二步之前或之后），则无法确定重置之后的持久数据是否与调用“p_allocate”（或“p_validate_slot_number”）之前或之后的数据相同。
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in，out]persistent_data指向允许写入的持久数据的指针。\param[in]attributes键的属性。\param方法创建密钥的方式。\param[out]key_slot存储密钥的插槽。这必须是所选类型密钥的有效插槽。它肯定是空的。
 *
 * \retval#PSA_SUCCESS成功。核心将记录\c key_slot作为存储密钥的密钥槽，并更新存储中的持久数据。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INSUFFIED_STORAGE
 */
typedef psa_status_t (*psa_drv_se_allocate_key_t)(
    psa_drv_se_context_t *drv_context,
    void *persistent_data,
    const psa_key_attributes_t *attributes,
    psa_key_creation_method_t method,
    psa_key_slot_number_t *key_slot);

/** \brief确定插槽编号是否对密钥有效的函数。
 *
 * 要在安全元素的特定槽中创建密钥，核心首先调用此函数以验证槽号的选择，然后调用一个函数以在该槽中创建关键材料。有关详细信息，请参阅#psa_drv_se_allocate_key_t的文档。
 *
 * 从PSA Cryptography API规范1.0版开始，应用程序无法触发对此函数的调用。然而，一些实现提供了通过特定于实现的方式在特定插槽中创建或声明密钥的能力，通常是为了初始设备配置或登录。这种机制可以被添加到PSA加密API规范的未来版本中。
 *
 * 此函数可以通过\ppersistent_data更新驱动程序的持久数据。核心将在密钥创建过程结束时保存更新的持久数据。有关详细信息，请参阅：：psa_drv_se_allocate_key_t的描述。
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in，out]persistent_data指向允许写入的持久数据的指针。\param[in]attributes键的属性。\param方法创建密钥的方式。\param[in]key_slot要存储密钥的插槽。
 *
 * \retval#PSA_SUCCESS给定的插槽编号对于具有给定属性的密钥有效。\retval#PSA_ERROR_INVALID_ARGUMENT给定的插槽号对于具有给定属性的密钥无效。这包括插槽号根本无效的情况。\retval#PSA_ERROR_ALREADY_EXISTS已存在具有指定插槽号的密钥。驱动程序可以选择从密钥创建函数返回此错误。
 */
typedef psa_status_t (*psa_drv_se_validate_slot_number_t)(
    psa_drv_se_context_t *drv_context,
    void *persistent_data,
    const psa_key_attributes_t *attributes,
    psa_key_creation_method_t method,
    psa_key_slot_number_t key_slot);

/** \brief将密钥以二进制格式导入安全元素的函数
 *
 * 此函数可以支持psa_export_key（）的任何输出。有关每种密钥类型的格式，请参阅psa_export_key（）的文档。
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param key_slot存储密钥的插槽。这必须是所选类型密钥的有效插槽。它肯定是空的。\param[in]attributes密钥属性，包括生存期、密钥类型和使用策略。驱动程序不应访问存储在属性中的密钥大小：它可能与传递到\p数据中的数据不匹配。驱动程序可以调用psa_get_key_lifetime（）、psa_gget_key_type（）、psa_get_key_usage_flags（）和psa_get-key_algorithm（）来访问此信息。\param[in]data包含密钥数据的缓冲区。\param[in]data_length数据缓冲区的大小（字节）。\param[out]bits成功时，密钥大小（以位为单位）。驱动程序必须在根据密钥类型解析密钥后确定该值。如果函数失败，则不使用此值。
 *
 * \retval#PSA_SUCCESS成功。
 */
typedef psa_status_t (*psa_drv_se_import_key_t)(
    psa_drv_se_context_t *drv_context,
    psa_key_slot_number_t key_slot,
    const psa_key_attributes_t *attributes,
    const uint8_t *data,
    size_t data_length,
    size_t *bits);

/**
 * \brief销毁安全元素密钥并将插槽恢复到默认状态的函数
 *
 * 此函数从安全元素中销毁密钥的内容。实施应尽最大努力确保插槽的任何先前内容不可恢复。
 *
 * 此函数将指定的插槽返回到其默认状态。
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in，out]persistent_data指向允许写入的持久数据的指针。\param key_slot要擦除的密钥槽。
 *
 * \retval#PSA_SUCCESS插槽的内容（如果有）已被擦除。
 */
typedef psa_status_t (*psa_drv_se_destroy_key_t)(
    psa_drv_se_context_t *drv_context,
    void *persistent_data,
    psa_key_slot_number_t key_slot);

/**
 * \brief以二进制格式导出安全元素密钥的函数
 *
 * 此函数的输出可以传递给psa_import_key（）以创建等效对象。
 *
 * 如果使用“psa_import_key（）”创建密钥，然后使用此函数导出，则不能保证生成的数据是相同的：如果格式允许，实现可能会选择相同密钥的不同表示形式。
 *
 * 此函数应以与“psa_export_key（）”相同的格式生成输出。有关每种密钥类型的格式，请参阅“psa_export_key（）”文档。
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in]键要导出其内容的插槽。这必须是一个被占用的钥匙槽。\param[out]p_data要写入密钥数据的缓冲区。\param[in]data_size“p_data”缓冲区的大小（字节）。\param[out]p_data_length成功时，构成密钥数据的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSA_ERROR_DOES_NOT_EXIST\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_NOT_SUPPORTED\retval#1 PSA_ERROR_COMMUNICATION_FAILURE\retval#2 PSA_ERROR_HARDWARE_FAILURE
 */
typedef psa_status_t (*psa_drv_se_export_key_t)(psa_drv_se_context_t *drv_context,
                                                psa_key_slot_number_t key,
                                                uint8_t *p_data,
                                                size_t data_size,
                                                size_t *p_data_length);

/**
 * \brief在安全元素上生成对称或非对称密钥的函数
 *
 * 如果\p类型是非对称的（#PSA_KEY_type_is_asymmetric（\p类型）=1），则驱动程序可以在生成时以PSA_export_public_KEY（）记录的格式导出公钥，方法是将其写入\p公钥缓冲区。这是可选的，用于在生成时输出公钥并且以后无法导出公钥的安全元素。不需要此功能的驱动程序应将\p pubkey_length设置为0，并应实现psa_drv_key_management_t:：p_export_public函数。某些实现不支持此功能，在这种情况下，\p pubkey为\c NULL，\p publickey_size为0。
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param key_slot存储密钥的插槽。这必须是所选类型密钥的有效插槽。它肯定是空的。\param[in]attributes密钥属性，包括生存期、密钥类型和大小以及使用策略。驱动程序可以调用psa_get_key_lifetime（）、psa_gget_key_type（）、psa_get_key_bits（）、psa_get__key_usage_flags（）和psa_get-key_algorithm（）来访问此信息。\param[out]pubkey生成非对称密钥对时，驱动程序可以在其中写入公钥的缓冲区。生成对称密钥时，或者如果核心不支持在生成时导出公钥，则该值为空。\param pubkey_size“pubkey”缓冲区的大小（字节）。当生成对称密钥时，或者如果核心不支持在生成时导出公钥，则此值为0。\param[out]pubkey_length输入时，此值始终为0。成功时，写入\p pubkey的字节数。如果返回时该值为0或未更改，内核将不会读取\p pubkey缓冲区，而是调用驱动程序的psa_drv_key_management_t:：p_export_public函数在需要时导出公钥。
 */
typedef psa_status_t (*psa_drv_se_generate_key_t)(
    psa_drv_se_context_t *drv_context,
    psa_key_slot_number_t key_slot,
    const psa_key_attributes_t *attributes,
    uint8_t *pubkey, size_t pubkey_size, size_t *pubkey_length);

/**
 * \brief包含安全元素密钥管理所需的所有函数指针的结构
 *
 * PSA Crypto API实现应在启动时或构建时适当填充表的实例。
 *
 * 如果其中一个函数未实现，则应将其设置为NULL。
 */
typedef struct {
    /**为密钥分配插槽的函数。*/
    psa_drv_se_allocate_key_t   p_allocate;
    /**检查钥匙插槽有效性的函数。*/
    psa_drv_se_validate_slot_number_t p_validate_slot_number;
    /**执行密钥导入操作的函数*/
    psa_drv_se_import_key_t     p_import;
    /**执行生成的函数*/
    psa_drv_se_generate_key_t   p_generate;
    /**执行密钥销毁操作的函数*/
    psa_drv_se_destroy_key_t    p_destroy;
    /**执行密钥导出操作的函数*/
    psa_drv_se_export_key_t     p_export;
    /**执行公钥导出操作的函数*/
    psa_drv_se_export_key_t     p_export_public;
} psa_drv_se_key_management_t;

/**@}*/

/** \defgroup driver_deviation安全元素密钥派生和协议密钥派生是使用现有密钥和其他参数生成新密钥材料的过程，通过基本加密函数（如哈希）进行迭代。密钥协议是密码协议的一部分，允许双方就相同的密钥值达成一致，但从不同的原始密钥材料开始。这两个流是相似的，PSA Crypto驱动程序模型对两个流使用相同的函数。
 *
 * 流有两个不同的最终函数，“psa_drv_se_key_derive_derive”和“psa_derv_se_key _derive_export”`当密钥材料应放置在硬件上的插槽中而不暴露给调用者时，使用“psa_drv_se_key_derive_derive”`当密钥材料应返回到psa Cryptographic API实现时，使用“psa_drv_se_key_derivation_export”。
 *
 * 不同的密钥推导算法需要不同数量的输入。与将可变长度数组作为输入的API（这在嵌入式平台上可能很难管理）不同，输入通过一个函数“psa_drv_se_key_derivation_collateral”传递给驱动程序，该函数使用不同的“collad_id”多次调用。因此，对于需要3个参数输入的密钥派生算法，流将类似于：~~~~~~ ~~~{.c}psa_drv_se_key_derivation_setup（kdf_agorithm，source_key，dest_key_size_bytes）；psa_drv_se_key_derivation_collateral（kdf_algarith_collateral_id_0，p_collad_0，collad_0_size）；psa_drv_se_key_derivation_collateral（kdf_algarith_collateral_id_1，p_collad_1，collad_1_size）；psa_drv_se_key_derivation_collateral（kdf_algarith_collateral_id_2，p_collad_2，collad_2_size）；psa_drv_se_key_derive_derive（）~~~~~~~~~~~~~
 *
 * 密钥协议示例：~~~~~~{.c}psa_drv_se_key_derivation_setup（alg，source_key.dest_key_size_bytes）；psa_drv_se_key_derivation_collateral（DHE_PUBKEY，p_PUBKEY，PUBKEY_size）；psa_drv_se_key_derivation_export（p_session_key、session_key_size和session_key_length）~~~~~~~~~~~~~
 */
/**@{*/

/** \brief通过指定算法和源密钥sot来设置安全元素密钥派生操作的函数
 *
 * \param[in，out]drv_context驱动程序上下文结构。\param[in，out]op_context包含实现的任何上下文信息的硬件特定结构\param[in]kdf_alg用于密钥派生的算法\param[iin]source_key用作密钥派生的源材料的密钥
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_se_key_derivation_setup_t)(psa_drv_se_context_t *drv_context,
                                                          void *op_context,
                                                          psa_algorithm_t kdf_alg,
                                                          psa_key_slot_number_t source_key);

/** \brief提供安全元素密钥派生或密钥协议操作所需的辅助（参数）的函数
 *
 * 由于许多密钥推导算法需要多个参数，因此对于同一操作，可以多次调用该函数，每个函数都具有不同的算法特定的`CDOD_id`
 *
 * \param[in，out]op_context包含实现的任何上下文信息的硬件特定结构\param[in]collater_id提供的抵押品的id \param[iin]p_collater包含抵押品数据的缓冲区\param[in]collater_size抵押品的字节大小
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_se_key_derivation_collateral_t)(void *op_context,
                                                               uint32_t collateral_id,
                                                               const uint8_t *p_collateral,
                                                               size_t collateral_size);

/** \brief执行最后一个安全元素密钥导出步骤并将生成的密钥材料放入槽中的函数
 *
 * \param[in，out]op_context包含实现的任何上下文信息的硬件特定结构\param[in]dest_key应放置生成的密钥材料的插槽
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_se_key_derivation_derive_t)(void *op_context,
                                                          psa_key_slot_number_t dest_key);

/** \brief执行安全元素密钥协议的最后一步并将生成的密钥材料放入缓冲区的函数
 *
 * \param[out]p_outputBuffer用于放置生成的密钥材料的缓冲区\param[in]output_size“p_output`\param[out]p_output_length成功后，包含放置在“p_output”中的密钥材料字节数`
 *
 * \retval#PSA_SUCCESS
 */
typedef psa_status_t (*psa_drv_se_key_derivation_export_t)(void *op_context,
                                                           uint8_t *p_output,
                                                           size_t output_size,
                                                           size_t *p_output_length);

/**
 * \brief包含安全元素密钥派生和协议所需的所有函数指针的结构
 *
 * PSA Crypto API实现应在启动时适当填充表的实例。
 *
 * 如果其中一个函数未实现，则应将其设置为NULL。
 */
typedef struct {
    /**密钥派生上下文的驱动程序特定大小*/
    size_t                           context_size;
    /**执行密钥派生设置的函数*/
    psa_drv_se_key_derivation_setup_t      p_setup;
    /**设置密钥派生抵押品的函数*/
    psa_drv_se_key_derivation_collateral_t p_collateral;
    /**执行最终密钥导出步骤的函数*/
    psa_drv_se_key_derivation_derive_t     p_derive;
    /**执行最终密钥派生或协议并导出密钥的函数*/
    psa_drv_se_key_derivation_export_t     p_export;
} psa_drv_se_key_derivation_t;

/**@}*/

/** \defgroup se_registration安全元素驱动程序注册
 */
/**@{*/

/** 包含指向安全元素驱动程序的所有入口点的指针的结构。
 *
 * 本规范的未来版本可能会在该结构的末尾添加额外的子结构。
 */
typedef struct {
    /** 此驱动程序实现的驱动程序HAL的版本。这是针对加载根据本规范的不同版本构建的驱动程序二进制文件的保护。使用#PSA_DRV_SE_HAL_VERSION。
     */
    uint32_t hal_version;

    /** 驱动程序持久数据的大小（以字节为单位）。
     *
     * 如果驱动程序不需要持久数据，则此值可以为0。
     *
     * 请参阅psa_drv_se_context_t:：persistent_data的文档，了解有关驱动程序使用持久数据的原因和方式的更多信息。
     */
    size_t persistent_data_size;

    /** 驱动程序初始化功能。
     *
     * 在PSA加密子系统初始化期间，在调用驱动程序的任何其他功能之前，调用此函数一次。如果此功能返回故障状态，则驱动程序将不可用，至少在下一次系统重置之前。
     *
     * 如果此字段为空，则相当于不执行任何操作并返回#PSA_SUCCESS的函数。
     */
    psa_drv_se_init_t p_init;

    const psa_drv_se_key_management_t *key_management;
    const psa_drv_se_mac_t *mac;
    const psa_drv_se_cipher_t *cipher;
    const psa_drv_se_aead_t *aead;
    const psa_drv_se_asymmetric_t *asymmetric;
    const psa_drv_se_key_derivation_t *derivation;
} psa_drv_se_t;

/** 安全元件驱动程序HAL的当前版本。
 */
/* 0.0.0补丁级别5*/
#define PSA_DRV_SE_HAL_VERSION 0x00000005

/** 注册外部密码处理器（安全元件）驱动程序。
 *
 * 此功能仅用于驱动程序代码，而非应用程序代码。在PSA加密模块和应用程序之间分离的实现中，此函数应仅对在与加密模块相同的内存空间中运行的调用方可用，而不应向在不同内存空间中的应用程序公开。
 *
 * 此函数可以在psa_crypto_init（）之前调用。在psa_crypto_init（）之后是否可以调用此函数是由实现定义的。
 *
 * \注意：实现存储有关键的元数据，包括生存期值，该值包含驱动程序的位置指示符。因此，从PSA Cryptography库的一个实例到下一个实例，如果存储中存在具有特定生存期值的密钥，则必须始终使用相同的位置值注册相同的驱动程序（或与相同安全元素通信的更新版本）。
 *
 * \param location此驱动程序将通过其向应用程序公开的位置值。此驱动程序将用于所有密钥，例如“location==#PSA_KEY_LIFIME_GET_location（生存期）”。值#PSA_KEY_LOCATION_LOCAL_STORAGE是保留的，不能用于驱动程序。实现可能保留其他值。\param[in]methods驱动程序的方法表。只要加密模块继续运行，此结构就必须保持有效。它通常是一个全局常数。
 *
 * \return#PSA_SUCCESS驱动程序已成功注册。应用程序现在可以使用\p lifetime通过传递给此函数的方法访问密钥。\return#PSA_ERROR_BAD_STATE此函数是在加密模块初始化后调用的，此实现在此阶段不支持驱动程序注册。\return#PSA_ERROR_ALREADY_EXISTS此生存期值已经有一个已注册的驱动程序。\return#PSA_ERROR_INVALID_ARGUMENT\p lifetime是一个保留值。\return#PSA_ERROR_NOT_SUPPORTED`methods->hal_version`不支持此实现。\返回#PSA_ERROR_INSUFFIE_MEMORY\return#PSA_ERROR_NOT_PERMITTED
 */
psa_status_t psa_register_se_driver(
    psa_key_location_t location,
    const psa_drv_se_t *methods);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_SE_DRIVER_H */

