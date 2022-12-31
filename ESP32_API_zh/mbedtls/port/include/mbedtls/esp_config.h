/**
 * \ESP-IDF的简要默认mbedTLS配置选项
 *
 *  这组编译时选项可用于选择性地启用或禁用功能，并减少全局内存占用。
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

#ifndef ESP_CONFIG_H
#define ESP_CONFIG_H

#include "sdkconfig.h"
#include "mbedtls/config.h"
#include "soc/soc_caps.h"

/**
 * \name SECTION:系统支持
 *
 * 本节设置系统特定设置\{
 */

/**
 * \定义MBEDTLS_HAVE_TIME
 *
 * 系统有时间。h和time（）。与MBEDTLS_HAVE_time_DATE相比，时间不需要正确，只使用时间差
 *
 * 如果您的系统不支持时间函数，请说明
 */
#ifdef CONFIG_MBEDTLS_HAVE_TIME
#define MBEDTLS_HAVE_TIME
#else
#undef MBEDTLS_HAVE_TIME
#endif

/**
 * \定义MBEDTLS_HAVE_TIME_DATE
 *
 * 系统有时间。h和time（），gmtime（）和时钟是正确的。时间需要正确（不一定非常准确，但至少日期应该正确）。这用于验证X.509证书的有效期。
 *
 * 如果您的系统没有正确的时钟，请进行注释。
 */
#ifdef CONFIG_MBEDTLS_HAVE_TIME_DATE
#define MBEDTLS_HAVE_TIME_DATE
#else
#undef MBEDTLS_HAVE_TIME_DATE
#endif

/**
 * \定义MBEDTLS_PLATFORM_MEMORY
 *
 * 启用内存分配层。
 *
 * 默认情况下，mbed TLS使用系统提供的calloc（）和free（）。这允许向平台抽象层提供不同的分配器（自行实现或提供）。
 *
 * 启用MBEDTLS_PLATFORM_MEMORY而不使用MBEDTLS_PLATFORM_{FREE，CALLOC}MACROs将提供“MBEDTLS_PLATFORM_set_CALLOC_FREE（）”，允许您在运行时设置可选的CALLOC（）和FREE（）函数指针。
 *
 * 启用MBEDTLS_PLATFORM_MEMORY并指定MBEDTLS_PLATFORM_{CALLOC，FREE}MACROs将允许您在编译时指定备用函数。
 *
 * 需要：MBEDTLS_PLATFORM_C
 *
 * 启用此层以允许使用其他内存分配器。
 */
#define MBEDTLS_PLATFORM_MEMORY

/**重写calloc（）、free（），除非内存分配方案未设置为自定义*/
#ifndef CONFIG_MBEDTLS_CUSTOM_MEM_ALLOC
#include "esp_mem.h"
#define MBEDTLS_PLATFORM_STD_CALLOC		esp_mbedtls_mem_calloc
#define MBEDTLS_PLATFORM_STD_FREE		esp_mbedtls_mem_free
#endif

/* \}name SECTION:系统支持*/

/**
 * \name SECTION:mbed TLS功能支持
 *
 * 本节设置对启用的模块中需要或不需要的功能的支持\{
 */

/* 以下单元具有ESP32硬件支持，取消注释每个_ALT宏将使用硬件加速实现。*/
#ifdef CONFIG_MBEDTLS_HARDWARE_AES
#define MBEDTLS_AES_ALT
#else
#undef MBEDTLS_AES_ALT
#endif

#ifdef CONFIG_MBEDTLS_HARDWARE_GCM
#define MBEDTLS_GCM_ALT
#else
#undef MBEDTLS_GCM_ALT
#endif

/* MBEDTLS_SHAX_ALT以启用硬件SHA支持和软件回退。
*/
#ifdef CONFIG_MBEDTLS_HARDWARE_SHA
#define MBEDTLS_SHA1_ALT
#define MBEDTLS_SHA256_ALT

#if SOC_SHA_SUPPORT_SHA512
#define MBEDTLS_SHA512_ALT
#else
#undef MBEDTLS_SHA512_ALT
#endif

#else
#undef MBEDTLS_SHA1_ALT
#undef MBEDTLS_SHA256_ALT
#undef MBEDTLS_SHA512_ALT
#endif

/* MBEDTLS_MDx_ALT启用ROM MD支持和软件回退。
*/
#ifdef CONFIG_MBEDTLS_ROM_MD5
#define MBEDTLS_MD5_ALT
#else
#undef MBEDTLS_MD5_ALT
#endif

/* 以下MPI（bignum）函数具有硬件支持。解压缩这些宏将使用硬件加速实现。
 */
#ifdef CONFIG_MBEDTLS_HARDWARE_MPI
#ifdef CONFIG_MBEDTLS_LARGE_KEY_SOFTWARE_MPI
    /* 首选硬件并回退到软件*/
    #define MBEDTLS_MPI_EXP_MOD_ALT_FALLBACK
#else
    /* 仅硬件模式*/
    #define MBEDTLS_MPI_EXP_MOD_ALT
#endif
#define MBEDTLS_MPI_MUL_MPI_ALT
#else
#undef MBEDTLS_MPI_EXP_MOD_ALT_FALLBACK
#undef MBEDTLS_MPI_EXP_MOD_ALT
#undef MBEDTLS_MPI_MUL_MPI_ALT
#endif

#ifdef CONFIG_MBEDTLS_ATCA_HW_ECDSA_SIGN
#define MBEDTLS_ECDSA_SIGN_ALT
#endif

#ifdef CONFIG_MBEDTLS_ATCA_HW_ECDSA_VERIFY
#define MBEDTLS_ECDSA_VERIFY_ALT
#endif

/**
 * \定义MBEDTLS_ENTROPY_HARDWARE_ALT
 *
 * 取消注释此宏以使mbed TLS使用您自己的硬件熵收集器实现。
 *
 * 您的函数必须名为\c mbedtls_hardware_poll（），具有与entropy_poll中声明的原型相同的原型。h、 并接受NULL作为第一个参数。
 *
 * 取消注释以使用您自己的硬件熵收集器。
 */
#define MBEDTLS_ENTROPY_HARDWARE_ALT

/**
 * \定义MBEDTLS_AES_ROM_TABLES
 *
 * 将AES表存储在ROM中。
 *
 * 取消注释此宏以将AES表存储在ROM中。
 */
#define MBEDTLS_AES_ROM_TABLES

/**
 * \定义MBEDTLS_CIPHER_MODE_CBC
 *
 * 为对称密码启用密码块链接模式（CBC）。
 */
#define MBEDTLS_CIPHER_MODE_CBC

/**
 * \定义MBEDTLS_CIPHER_MODE_CFB
 *
 * 为对称密码启用密码反馈模式（CFB）。
 */
#define MBEDTLS_CIPHER_MODE_CFB

/**
 * \定义MBEDTLS_CIPHER_MODE_CTR
 *
 * 为对称密码启用计数器块密码模式（CTR）。
 */
#define MBEDTLS_CIPHER_MODE_CTR

/**
 * \定义MBEDTLS_CIPHER_MODE_OFB
 *
 * 为对称密码启用输出反馈模式（OFB）。
 */
#define MBEDTLS_CIPHER_MODE_OFB

/**
 * \定义MBEDTLS_CIPHER_MODE_XTS
 *
 * 为AES启用X或使用密文窃取模式（XTS）加密Xor。
 */
#define MBEDTLS_CIPHER_MODE_XTS

/**
 * \定义MBEDTLS_CIPHER_PADDING_PKCS7
 *
 * MBEDTLS_CIPHER_PADDING_XXX：取消注释或注释宏，以添加对密码层中特定填充模式的支持，其中密码模式支持填充（例如CBC）
 *
 * 如果禁用所有填充模式，CBC只能使用完整块。
 *
 * 在密码层中启用填充模式。
 */
#define MBEDTLS_CIPHER_PADDING_PKCS7
#define MBEDTLS_CIPHER_PADDING_ONE_AND_ZEROS
#define MBEDTLS_CIPHER_PADDING_ZEROS_AND_LEN
#define MBEDTLS_CIPHER_PADDING_ZEROS

/**
 * \定义MBEDTLS_REMOVE_ARC4_CIPHERSUITES和MBEDTLS_ARC4_C
 *
 * MBEDTLS_ARC4_C启用ARCFOUR流密码。
 *
 * 此模块启用/禁用以下密码套件MBEDTLS_TLS_ECDH_ECDSA_WITH_RC4_128_SHA MBEDLS_TLS_ECDH_RSA_WITH_RC4_128 _SHA MBEDTLS_TLS-ECDHE_ECDSA_WITS_RC4_128_SHA MBEDTLS_TLS_ECDHE_RSA_WITH_2RC4_128.SHA MBEDLLS_TLS_CDHE_PSK_WITH_RC4_128_SHA MBEDLS_RLS_RSA_WIT H_RC4_ 128_SHA LS_TLS_RSA_PSK_WITH_RC4_128_SHAMBEDTLS_TLS_PSK_WITH_RC4_128_SHA
 *
 * MBEDTLS_REMOVE_ARC4_CIPHERSUITES此标志从MBEDTLS_ssl_list_CIPHERSUITES（）返回的默认列表中删除基于RC4的密码套件。但是，通过显式包含它们，仍然可以使用mbedtls_ssl_conf_cciphersuites（）启用（其中一些）。
 *
 * 默认情况下，取消注释此宏以删除RC4密码套件。
 */
#ifdef CONFIG_MBEDTLS_RC4_ENABLED
#define MBEDTLS_ARC4_C
#undef MBEDTLS_REMOVE_ARC4_CIPHERSUITES
#elif defined CONFIG_MBEDTLS_RC4_ENABLED_NO_DEFAULT
#define MBEDTLS_ARC4_C
#define MBEDTLS_REMOVE_ARC4_CIPHERSUITES
#else
#undef MBEDTLS_ARC4_C
#define MBEDTLS_REMOVE_ARC4_CIPHERSUITES
#endif

/**
 * \定义MBEDTLS_ECP_RESTARTABLE
 *
 * 启用“非阻塞”ECC操作，这些操作可以提前返回并恢复。
 *
 * 这允许通过返回#MBEDTLS_ERROR_ECP_IN_PROGRESS（或者，对于SSL模块中的函数，#MBEDLLS_ERROR_SSL_CRYPTO_IN_PROGRESS）暂停各种函数，然后稍后再次调用这些函数，以便进一步进一步并最终完成其操作。这是通过mbedtls_ecp_set_max_ops（）控制的，它限制了函数在暂停前可以执行的最大ECC操作数；有关详细信息，请参阅mbedtls_ecp_set_max_ops（）。
 *
 * 如果您希望避免在ECC（以及X.509或SSL/TLS）操作上阻塞太长时间，这在非线程环境中非常有用。
 *
 * 取消注释此宏以启用可重新启动的ECC计算。
 *
 * \注意：此选项仅适用于椭圆曲线功能的默认软件实现。它与MBEDTLS_ECP_ALT、MBETLS_ECDH_XXX_ALT、MBEDTLS_ECDSA_XXX_ALT和MBETLS_ECDH_LEGACY_CONTEXT不兼容。
 */
#ifdef CONFIG_MBEDTLS_ECP_RESTARTABLE
#define MBEDTLS_ECP_RESTARTABLE
#endif

/**
 * \定义MBEDTLS_ECDH_LEGACY_CONTEXT
 *
 * 使用向后兼容的ECDH上下文。
 *
 * Mbed TLS支持ECDH上下文的两种格式（在“ECDH.h”中定义的#mbedtls_ECDH_context）。对于大多数应用程序，格式的选择没有什么区别，因为所有库函数都可以使用其中一种格式，除了新格式与mbedtls_ECP_RESTABLE不兼容。

 * 禁用此选项时使用的新格式较小（32位平台上为56字节）。在未来版本的库中，它将支持ECDH操作的替代实现。新格式与直接访问上下文字段的应用程序以及可重新启动的ECP操作不兼容。
 *
 * 如果启用MBEDTLS_ECP_RESTARTABLE或要直接访问ECDH上下文字段，请定义此宏。否则，应注释掉此宏定义。
 *
 * 如果未启用#MBEDTLS_ECDH_C，则此选项无效。
 *
 * \注意：此配置选项是实验性的。库的未来版本可以修改ECDH上下文布局的配置方式，并且可以修改新上下文类型的布局。
 */
#ifdef CONFIG_MBEDTLS_ECDH_LEGACY_CONTEXT
#define MBEDTLS_ECDH_LEGACY_CONTEXT
#endif

/**
 * \定义MBEDTLS_MAC_C
 *
 * 为分组密码启用CMAC（基于密码的消息验证码）模式。
 *
 * \注意：当#MBEDTLS_MAC_ALT激活时，意味着CMAC算法的底层实现由替代实现提供，该替代实现可以选择不支持AES-192或3DES作为CMAC操作的底层块密码。
 *
 * 模块：library/cmac.c
 *
 * 需要：MBEDTLS_AES_C或MBEDTLS_DES_C
 *
 */
#ifdef CONFIG_MBEDTLS_CMAC_C
#define MBEDTLS_CMAC_C
#endif

/**
 * \定义MBEDTLS_ECP_DP_SECP192R1_ENABLED
 *
 * MBEDTLS_ECP_XXXX_ENABLED：启用椭圆曲线模块中的特定曲线。默认情况下，启用所有支持的曲线。
 *
 * 注释宏以禁用曲线及其函数
 */
/* 短Weierstrass曲线（支持ECP、ECDH、ECDSA）*/
#ifdef CONFIG_MBEDTLS_ECP_DP_SECP192R1_ENABLED
#define MBEDTLS_ECP_DP_SECP192R1_ENABLED
#else
#undef MBEDTLS_ECP_DP_SECP192R1_ENABLED
#endif
#ifdef CONFIG_MBEDTLS_ECP_DP_SECP224R1_ENABLED
#define MBEDTLS_ECP_DP_SECP224R1_ENABLED
#else
#undef MBEDTLS_ECP_DP_SECP224R1_ENABLED
#endif
#ifdef CONFIG_MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#else
#undef MBEDTLS_ECP_DP_SECP256R1_ENABLED
#endif
#ifdef CONFIG_MBEDTLS_ECP_DP_SECP384R1_ENABLED
#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
#else
#undef MBEDTLS_ECP_DP_SECP384R1_ENABLED
#endif
#ifdef CONFIG_MBEDTLS_ECP_DP_SECP521R1_ENABLED
#define MBEDTLS_ECP_DP_SECP521R1_ENABLED
#else
#undef MBEDTLS_ECP_DP_SECP521R1_ENABLED
#endif
#ifdef CONFIG_MBEDTLS_ECP_DP_SECP192K1_ENABLED
#define MBEDTLS_ECP_DP_SECP192K1_ENABLED
#else
#undef MBEDTLS_ECP_DP_SECP192K1_ENABLED
#endif
#ifdef CONFIG_MBEDTLS_ECP_DP_SECP224K1_ENABLED
#define MBEDTLS_ECP_DP_SECP224K1_ENABLED
#else
#undef MBEDTLS_ECP_DP_SECP224K1_ENABLED
#endif
#ifdef CONFIG_MBEDTLS_ECP_DP_SECP256K1_ENABLED
#define MBEDTLS_ECP_DP_SECP256K1_ENABLED
#else
#undef MBEDTLS_ECP_DP_SECP256K1_ENABLED
#endif
#ifdef CONFIG_MBEDTLS_ECP_DP_BP256R1_ENABLED
#define MBEDTLS_ECP_DP_BP256R1_ENABLED
#else
#undef MBEDTLS_ECP_DP_BP256R1_ENABLED
#endif
#ifdef CONFIG_MBEDTLS_ECP_DP_BP384R1_ENABLED
#define MBEDTLS_ECP_DP_BP384R1_ENABLED
#else
#undef MBEDTLS_ECP_DP_BP384R1_ENABLED
#endif
#ifdef CONFIG_MBEDTLS_ECP_DP_BP512R1_ENABLED
#define MBEDTLS_ECP_DP_BP512R1_ENABLED
#else
#undef MBEDTLS_ECP_DP_BP512R1_ENABLED
#endif
/* 蒙哥马利曲线（支持ECP）*/
#ifdef CONFIG_MBEDTLS_ECP_DP_CURVE25519_ENABLED
#define MBEDTLS_ECP_DP_CURVE25519_ENABLED
#else
#undef MBEDTLS_ECP_DP_CURVE25519_ENABLED
#endif
#ifdef MBEDTLS_ECP_DP_CURVE448_ENABLED
#undef MBEDTLS_ECP_DP_CURVE448_ENABLED
#endif

/**
 * \定义MBEDTLS_ECP_NIST_OPTIM
 *
 * 为每个NIST素数启用特定的“模p”例程。根据素数和架构，使相应曲线上的操作速度提高4到8倍。
 *
 * 注释此宏以禁用NIST曲线优化。
 */
#ifdef CONFIG_MBEDTLS_ECP_NIST_OPTIM
#define MBEDTLS_ECP_NIST_OPTIM
#else
#undef MBEDTLS_ECP_NIST_OPTIM
#endif

/**
 * \定义MBEDTLS_ECDSA_DETERMINISTIC
 *
 * 启用确定性ECDSA（RFC 6979）。标准ECDSA是“脆弱的”，因为在签名时缺乏熵可能会导致长期签名密钥的妥协。确定性变量可以避免这种情况。
 *
 * 需要：MBEDTLS_MAC_DRBG_C、MBEDTLS_ECDSA_C
 *
 * 注释此宏以禁用确定性ECDSA。
 */
#ifdef CONFIG_MBEDTLS_ECDSA_DETERMINISTIC
#define MBEDTLS_ECDSA_DETERMINISTIC
#else
#undef MBEDTLS_ECDSA_DETERMINISTIC
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
 *
 * 在SSL/TLS中启用基于PSK的密码套件模式。
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_PSK_WITH_ACE_256_GCM_SHA384 MBEDTLS_TLS_PSK-WITH_AAES_256_CBC_SHA384 EMBEDTLS_TSK_WSK_WITH-ACE_256_CBC _SHAMBEDTL_TLS_PSK_WITH_CAMELLIA_256_GBC_SHA284 MBEDTLC_TSK_WITH_CAMELLIA_2256_CBC_SHAD84 MBEDTLS-TLS_PSC_WITH_AES_128_GCM_SHAD256MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA MBEDTLS_TLS_PSK-WITH_cmellia_128_GCM_SHA256 MBEDTLS.TLS_PSK/WITH_cmellian_128_CBC _SHA256 mbdtls_TLS _PSK_wwith_3DES_EDE_CBC_shambedtls_ssk_WITH_RC4_128_SHA
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_PSK
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED
 *
 * 在SSL/TLS中启用基于DHE-PSK的密码套件模式。
 *
 * 需要：MBEDTLS_DHM_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_DHE_PSK_WITH_ACE_256_GCM_SHA384 MBEDTLS_TLS_DHE_PSK_WICH_ACE_256-BC_SHA384 MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CBC_SHA MBEDTLS-TLS_TLS_DLS_PH_PSK_WITH_CAMELLIA_256_GBC_SHA284 MBEDTL_TLS_DLS_PHE_PSK-WITH_CAMELLEA_256_CCM_SHA284 H_AES_128_CBC_SHA256MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CBC_SHA MBEDTLS_dls_DHE_ssk_WITH_cmellia_128_GCM_SHA256 MBEDTLS_TLS_DHE-PSK_WITH_Cmellia_128 _CBC_SHA256 mbdtls_TLS _DHE_PSK _WITH_3DES_EDE_CBC_shar
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_DHE_PSK
#define MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED
 *
 * 在SSL/TLS中启用基于ECDHE-PSK的密码套件模式。
 *
 * 需要：MBEDTLS_ECDH_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384 MBEDTLS_TLS_ECDHE_PSK_WITH_AES_256-BC_SHA MBEDTL_TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC _SHA384 MBEDTLS_TLS_ECD HE_PSK-WITH_AES_128_CBC_SHAD256 MBEDTLSTLS_TLS_ECDHE_PSK _WITH_AE_128_CBC _SHA MBEDTLS_TLS-ECDHE_PSK_WITH_CAMELIA_128_CBC_SHA256MBEDTLS_TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA MBEDTLS_TLS_ECDHE _PSK-WITH_RC4_128_SHA
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_ECDHE_PSK
#define MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED
 *
 * 在SSL/TLS中启用基于RSA-PSK的密码套件模式。
 *
 * 需要：MBEDTLS_RSA_C、MBEDTLS_PKCS1_V15、MBEDTLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_RSA_PSK_WITH_ACE_256_GCM_SHA384 MBEDTLS_TLS_RSE_PSK_WICH_ACE_256-BC_SHA384 EMBEDTLS_RLS_RSA_SK_WITH_AES_256_CBC_SHA MBEDTL_TLS_RSA_PSK_WITH-CAMELLIA256_GCM_SHAD84 MBEDTLS-TLS_RS_RSA_PSK _WITH_CAMELLIA256 _CBC_SHAD84 H_AES_128_CBC_SHA256MBEDTLS_TLS_RSA_PSK_WITH_AES_128_CBC_SHA MBEDTLS_TLS_RSA_ssk_WITH_cmellia_128_GCM_SHA256 MBEDTLS_RSA_prsk_WITH_Cmellia_128 _CBC_SHA256 mbdtls_TLS _RSA_PSK _WITH_3DES_EDE_CBC_shar MBEDTLS_RSA_PSK-WITH_RC4_128_SHA
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_RSA_PSK
#define MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
 *
 * 在SSL/TLS中启用仅基于RSA的密码套件模式。
 *
 * 需要：MBEDTLS_RSA_C、MBEDTLS_PKCS1_V15、MBEDTLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_RSA_WITH_ACE_256_GCM_SHA384 MBEDTLS_TLS_RS_WITH_AES_256_CBC_SHA256 MBEDTL_TLS_RSA_WITH_AES_256_CBC_SHA MBEDTLS-TLS_RLS_WITH_ASE_256_CBC _SHA384MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA256 MBEDTLS_RSA-WITH_AES_1 28_CBC-SHA MBEDTLS_TLS_RSA/WITH_cmellia_128_GCM_SHA256 embedtls_TLS _RSA-wwith_cmellia 128_CBC_SHA MBEDTLS _TLS_RSA WITH_3DES_EDE_CBC_saha MBEDTLS_lsa-WITH_cc4_128_MD5
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_RSA
#define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED
 *
 * 在SSL/TLS中启用基于DHE-RSA的密码套件模式。
 *
 * 需要：MBEDTLS_DHM_C、MBEDTLS_RSA_C、MBEDTLS_PKCS1_V15、MBEDDLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_DHE_RSA_WITH_ACE_256_GCM_SHA384 MBEDTLS_TLS_DHS_RSA_WIITH_AES_256_CBC_SHA256 MBEDTL_TLS_DHE_RSA_WITH_AES_2 56_CBC.SHA MBEDTLS-TLS_TLS_DHE_RS_WITH_CAMELLIA256_GCM_SHAR384 MBEDLLS_TLS_TLS-TH_DHE_RSA _WITH_CamELLIA256_CBC_SHAR256 MBEDLS_TLS_DHE _RSA_WITEH_CAMELLIA H_AES_128_GCM_SHA256MBEDTLS_TLS_DHE_RSA-WITH_AES_128_CBC_SHA256 MBEDTLS_TLS_DHE_RSA-WITH-AES_128_CBC_SHA MBEDTLS_dls_DHE-RSA-WITH_cmellia_128_GCM_SHA256 embedtls_TLS _DHE_RSA-WITH_camelia_128_CBC _SHA256
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_DHE_RSA
#define MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
 *
 * 在SSL/TLS中启用基于ECDHE-RSA的密码套件模式。
 *
 * 需要：MBEDTLS_ECDH_C、MBEDTLS_RSA_C、MBEDTLS _PKCS1_V15、MBEDTLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256-BC_SHA384 EMBEDTLS_ELS_ECDHE_RSA_WITH_AES_2 56_CBC_SHA MBEDTL_TLS_ECDHE-RSA_WITH-CAMELLIA_2256_GCM_SHAD84MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 MBEDTLS_TLS_ECDHE _RSA_WITH _AES_128 _CBC_SHA MBEDTLS_ecdthe_RSA_wwith_cmellia_128_GCM_SHA256 embedtls_TLS _ECDHE_RSA_WITH_cmellia 128_CBC_saha256 MBEDTLS _TLS_ecd he_RSA-WITH_3DES_EDE_CBC_shar
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_ECDHE_RSA
#define MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
 *
 * 在SSL/TLS中启用基于ECDHE-ECDSA的密码套件模式。
 *
 * 需要：MBEDTLS_ECDH_C、MBEDTLS-ECDSA_C、MBEDTLS_X509_CRT_PARSE_C、，
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_2 56_CBC_SHA384 EMBEDTLS_ELS_ECDHE_ECDSE_WITH_AES_256_CBC_SHAD84 MBEDLS_TLS_ECDHE-ECDSA_WITH_CAMELLIA256_GCM_SHAD84 56个MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 MBEDTLS_ecdthe_ECDSA-WITH_AES_1 28_CBC-SHA MBEDTLS_TLS_ECDHE _ECDSA/WITH_cmellia_128_GCM_SHA256 embedtls_TLS _ECDHE-ECDSA-wwith_cmellia 128_CBC_SHA
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED
 *
 * 在SSL/TLS中启用基于ECDH-ECDSA的密码套件模式。
 *
 * 需要：MBEDTLS_CDH_C、MBEDTLS_CDSA_C、MBEDRLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_ECDSA_WITH_RC4_128_SHA MBEDTLS_TLS_ECDH_2ECDSA_WITCH_3DES_EDE_CBC_SHA MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA MBEDTL_TLS_ECD H_ECDSA-WITH_AES_256_CBC_SHAMBEDTLSTLS_TLS-ECDH_ECDSA_WITH_AES_1 28_CBC-SHA256 MBEDLS_TLS.ECDH_ECDAS_WITH_AES_256 ITH_AES_128_GCM_SHA256MBEDTLS_TLS_ECDH_edcsa_WITH_AES_256_GCM_SHA384 MBEDTLS_ECDH-ecsa_WITH_camelia_128_CBC_SHA256 MBEDTLS_TLS_ECDH-edcsa_wwith_camelia_256_CBC_sha 384 MBEDTLS _ECDH-edcsa-WITH_camella_128_GCM_sha 256
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA
#define MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED
 *
 * 在SSL/TLS中启用基于ECDH-RSA的密码套件模式。
 *
 * 需要：MBEDTLS_ECDH_C、MBEDTLS_RSA_C、MBEDTLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_RSA_WITH_RC4_128_SHA MBEDTLS_TLS_ECD_RSA_WITH_3DES_EDE_CBC_SHA MBEDTLS_TLS_ECDH_RSA_WITH_2AES_128_CBC_SHA MBEDTL_TLS_ECD H_RSA_ WITH_AES_256_CBC_SHAMBEDTLS-TLS_ELS_ECDH_RS A_WITH_AES_128-CBC_SHA256 MBEDLS_TLS-ECDH_RSAA_WITH_AES_226_CBC_SHAR上海256MBEDTLS_TLS_ECDH_ras_WITH_AES_256_GCM_SHA384 MBEDTLS_ECDH-rsas_WITH_camelia_128_CBC_SHA256 MBEDTLS_TLS_ECDH/rsas_wwith_camelia_256_CBC_sha 384 MBEDTLS _TLS_ecd h_ras-WITH_CAMELLIA_228_GCM_sha 256
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_ECDH_RSA
#define MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED
#endif

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED
 *
 * 在SSL/TLS中启用基于ECJPAKE的密码套件模式。
 *
 * \警告这目前是实验性的。EC J-PAKE支持基于Thread v1.0.0规范；对规范的不兼容更改仍可能发生。因此，默认情况下禁用此功能。
 *
 * 需要：MBEDTLS_ECJPAKE_C MBEDTLS_SHA256_C MBEDTLS_EP_DP_SECP256R1_ENABLED
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECYPAKE_WITH_AES_128_CCM_8
 */
#ifdef CONFIG_MBEDTLS_KEY_EXCHANGE_ECJPAKE
#define MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED
#else
#undef MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED
#endif

/**
 * \定义MBEDTLS_PK_PARSE_EC_EXTEND
 *
 * 增强对使用RFC 5915和RFC 5480不允许的SEC1变体读取EC密钥的支持。
 *
 * 目前，这意味着解析EC参数的SpecifiedECDomain选择（只支持已知组，不支持任意域，以避免验证问题）。
 *
 * 如果只需要支持RFC 5915+5480密钥格式，则禁用。
 */
#define MBEDTLS_PK_PARSE_EC_EXTENDED

/**
 * \定义MBEDTLS_ERROR_STRERROR_DUMMY
 *
 * 当禁用mbedtls_error_C时（启用mbedtls_error_C后无效），启用伪错误函数以更容易地在第三方库中使用mbedtls_strerror（）。
 *
 * 如果启用了MBEDTLS_ERROR_C，或者没有在应用程序中使用MBEDTLS_strerror（）或ERROR_strerror（），则可以安全地禁用此功能。
 *
 * 如果遇到名称冲突并希望真正删除mbedtls_strerror（），则禁用
 */
#define MBEDTLS_ERROR_STRERROR_DUMMY

/**
 * \定义MBEDTLS_GENPRIME
 *
 * 启用素数生成代码。
 *
 * 需要：MBEDTLS_BIGNUM_C
 */
#define MBEDTLS_GENPRIME

/**
 * \定义MBEDTLS_FS_IO
 *
 * 启用使用文件系统的功能。
 */
#define MBEDTLS_FS_IO

/**
 * \定义MBEDTLS_NO_PLATFORM_ENTROPY
 *
 * 不要使用内置的平台熵函数。如果您的平台不支持/dev/urandom或Windows CryptoAPI等标准，这将非常有用。
 *
 * 取消注释此宏以禁用内置平台熵函数。
 */
#define MBEDTLS_NO_PLATFORM_ENTROPY

/**
 * \定义MBEDTLS_PK_RSA_ALT_SUPPORT
 *
 * 在PK层中支持外部私有RSA密钥（例如来自HSM）。
 *
 * 注释此宏以禁用对外部专用RSA密钥的支持。
 */
#define MBEDTLS_PK_RSA_ALT_SUPPORT

/**
 * \定义MBEDTLS_PKCS1_V15
 *
 * 启用对PKCS#1 v1.5编码的支持。
 *
 * 需要：MBEDTLS_RSA_C
 *
 * 这支持PKCS#1 v1.5操作。
 */
#define MBEDTLS_PKCS1_V15

/**
 * \定义MBEDTLS_PKCS1_V21
 *
 * 启用对PKCS#1 v2.1编码的支持。
 *
 * 需要：MBEDTLS_MD_C、MBEDTLS_RSA_C
 *
 * 这支持RSAES-OAEP和RSASSA-PSS操作。
 */
#define MBEDTLS_PKCS1_V21

/**
 * \定义MBEDTLS_SELF_TEST
 *
 * 启用检查功能（*_self_test）。
 */
#define MBEDTLS_SELF_TEST

/**
 * \定义MBEDTLS_SL_ALL_ALERT_MESSAGES
 *
 * 根据RFC，在遇到错误时启用警报消息的发送。如果您选择不发送警报消息，mbed-TLS仍然可以与其他服务器通信，只有故障调试更困难。
 *
 * 不发送警报消息的好处是，不会提供有关失败原因的信息，从而阻止对手获取情报。
 *
 * 启用发送所有警报消息
 */
#define MBEDTLS_SSL_ALL_ALERT_MESSAGES

/**
 * \定义MBEDTLS_SL_DTLS_CONNECTION_ID
 *
 * 启用对DTLS连接ID扩展的支持（版本draft-ietf-tls-DTLS-Connection-ID-05，https://tools.ietf.org/html/draft-ietf-tls-dtls-connection-id-05)这允许跨基础传输中的变化识别DTLS连接。
 *
 * 设置此选项将启用SSL API `mbedtls_SSL_set_cid（）`、`mbedtls _SSL_get_peer_cid（）`和`mbedtls _SSL_conf_cid（（）`。有关详细信息，请参阅相应的文档。
 *
 * \警告连接ID扩展仍处于草稿状态。我们对由该选项控制的API的可用性或形状不作稳定性承诺。
 *
 * 可以通过选项配置传出和传入CID的最大长度
 * - MBEDTLS_SSL_CID_OUT_LEN_MAX
 * - MBEDTLS_SSL_CID_IN_LEN_MAX.
 *
 * 需要：MBEDTLS_SL_PROTO_DTLS
 *
 * 取消注释以启用连接ID扩展。
 */
#ifdef CONFIG_MBEDTLS_SSL_DTLS_CONNECTION_ID
#define MBEDTLS_SSL_DTLS_CONNECTION_ID
#else
#undef MBEDTLS_SSL_DTLS_CONNECTION_ID
#endif

/**
 * \定义MBEDTLS_SL_CONTEXT_SERIALIZATION
 *
 * 通过使用函数mbedtls_ssl_context_save（）和mbedtls_ssl_context_load（），启用TLS上下文结构的序列化。
 *
 * 这对函数允许连接的一端序列化与连接关联的上下文，然后在序列化状态保存在其他位置时释放或重用该上下文，最后将该状态反序列化为活动上下文，以恢复连接上的读/写操作。从协议的角度来看，连接的状态是不受影响的，特别是这对对等端是完全透明的。
 *
 * 注意：这与TLS会话恢复不同，TLS会话恢复是协议的一部分，对端完全可见。TLS会话恢复允许使用更短、更轻的握手建立与保存的会话相关联的新连接，而上下文序列化是处理单个、可能长寿命连接的本地优化。
 *
 * 启用这些API会使某些SSL结构更大，因为握手后会额外保存64个字节，以实现更高效的串行化，因此如果您不需要此功能，则可以通过禁用它来节省RAM。
 *
 * 用于禁用上下文序列化API的注释。
 */
#ifdef CONFIG_MBEDTLS_SSL_CONTEXT_SERIALIZATION
#define MBEDTLS_SSL_CONTEXT_SERIALIZATION
#else
#undef MBEDTLS_SSL_CONTEXT_SERIALIZATION
#endif

/** \定义MBEDTLS_SL_ENCRYPT_THEN_MAC
 *
 * 启用对加密然后MAC的支持，RFC 7366。
 *
 * 这允许支持它的对等方使用CBC对密码套件使用更强大的保护，从而对填充或底层密码的定时攻击提供了强大的抵抗力。
 *
 * 这只会影响CBC密码套件，如果没有定义，则毫无用处。
 *
 * 需要：MBEDTLS_SL_PROTO_TLS1或MBEDTLS_SL_PROTO-TLS1_1或MBETTLS_SLPROTO_TLS1_2
 *
 * 注释此宏以禁用对先加密后MAC的支持
 */
#ifdef CONFIG_MBEDTLS_TLS_ENABLED
#define MBEDTLS_SSL_ENCRYPT_THEN_MAC
#else
#undef MBEDTLS_SSL_ENCRYPT_THEN_MAC
#endif

/** \定义MBEDTLS_SL_EXTENDED_MASTER_SECRET
 *
 * 启用对RFC 7627:会话哈希和扩展主密钥扩展的支持。
 *
 * 这被介绍为对三重握手系列攻击的“正确修复”，但建议始终使用它（即使您禁用重新协商），因为它实际上修复了原始SSL/TLS设计中的一个更基本的问题，并且具有超出三重握手的含义。
 *
 * 需要：MBEDTLS_SL_PROTO_TLS1或MBEDTLS_SL_PROTO-TLS1_1或MBETTLS_SLPROTO_TLS1_2
 *
 * 注释此宏以禁用对扩展主密钥的支持。
 */
#ifdef CONFIG_MBEDTLS_TLS_ENABLED
#define MBEDTLS_SSL_EXTENDED_MASTER_SECRET
#else
#undef MBEDTLS_SSL_EXTENDED_MASTER_SECRET
#endif

/**
 * \定义MBEDTLS_SL_FALLBACK_SCSV
 *
 * 启用对RFC 7507的支持：用于防止协议降级攻击的回退信令密码套件值（SCSV）。
 *
 * 对于服务器，建议始终启用此选项，除非您只支持一个版本的TLS，或者确定您的客户端都没有实现回退策略。
 *
 * 对于客户端，只有在使用回退策略时才需要此选项，这在一开始是不建议的，除非您绝对需要它与有问题（版本不兼容）的服务器进行互操作。
 *
 * 注释此宏以禁用对FALLBACK_SCSV的支持
 */
#define MBEDTLS_SSL_FALLBACK_SCSV

/**
 * \定义MBEDTLS_SL_KEEP_PEER_CERTIFICATE
 *
 * 此选项控制API mbedtls_ssl_get_peer_cert（）的可用性，该API在握手完成后可以访问对等方的证书。
 *
 * 除非应用程序中需要mbedtls_ssl_peer_cert（），否则建议禁用此选项以减少RAM使用。
 *
 * \注意：如果禁用此选项，则仍定义mbedtls_ssl_get_peer_cert（），但始终返回\c NULL。
 *
 * \注意：此选项对防止三次握手攻击没有影响。即使它被禁用，Mbed TLS仍将确保证书在重新协商期间不发生更改，例如通过保存对等方证书的哈希值。
 *
 * 注释此宏以禁用在握手后存储对等方的证书。
 */
#ifdef CONFIG_MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
#define MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
#else
#undef MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
#endif

/**
 * \定义MBEDTLS_SL_PROTO_TLS1
 *
 * 启用对TLS 1.0的支持。
 *
 * 需要：MBEDTLS_MD5_C MBEDTLS_SHA1_C
 *
 * 注释此宏以禁用对TLS 1.0的支持
 */
#ifdef CONFIG_MBEDTLS_SSL_PROTO_TLS1
#define MBEDTLS_SSL_PROTO_TLS1
#else
#undef MBEDTLS_SSL_PROTO_TLS1
#endif

/**
 * \定义MBEDTLS_SL_PROTO_SSL3
 *
 * 启用对SSL 3.0的支持。
 *
 * 需要：MBEDTLS_MD5_C MBEDTLS_SHA1_C
 *
 * \已弃用此选项已弃用，将在未来版本的Mbed TLS中删除。
 *
 * 注释此宏以禁用对SSL 3.0的支持
 */
#ifdef CONFIG_MBEDTLS_SSL_PROTO_SSL3
#define MBEDTLS_SSL_PROTO_SSL3
#else
#undef MBEDTLS_SSL_PROTO_SSL3
#endif

/**
 * \定义MBEDTLS_SL_CBC_RECORD_SPLITTING
 *
 * 在SSLv3和TLS 1.0中为CBC模式启用1/n-1记录拆分。
 *
 * 这是对BEAST攻击的一种对策，与发送0长度记录相比，这也将互操作性问题的风险降至最低。
 *
 * 注释此宏以禁用1/n-1记录拆分。
 */
#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1)
#define MBEDTLS_SSL_CBC_RECORD_SPLITTING
#else
#undef MBEDTLS_SSL_CBC_RECORD_SPLITTING
#endif

/**
 * \定义MBEDTLS_SL_RENEGOTIATION
 *
 * 禁用对TLS重新协商的支持。
 *
 * 重新协商的两个主要用途是（1）长时间连接上的刷新密钥和（2）初始握手后的客户端身份验证。如果您不需要重新协商，那么最好禁用它，因为它过去与安全问题有关，很容易被误用/误解。
 *
 * 对此进行注释以禁用对重新协商的支持。
 */
#ifdef CONFIG_MBEDTLS_SSL_RENEGOTIATION
#define MBEDTLS_SSL_RENEGOTIATION
#else
#undef MBEDTLS_SSL_RENEGOTIATION
#endif

/**
 * \定义MBEDTLS_SL_MAX_FRAGMENT_LENGTH
 *
 * 启用SSL中对RFC 6066 max_fragment_length扩展的支持。
 *
 * 注释此宏以禁用对max_fragment_length扩展的支持
 */
#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH

/**
 * \定义MBEDTLS_SL_PROTO_TLS1_1
 *
 * 启用对TLS 1.1的支持（如果启用了DTLS，则启用DTLS 1.0）。
 *
 * 需要：MBEDTLS_MD5_C MBEDTLS_SHA1_C
 *
 * 注释此宏以禁用对TLS 1.1/DTLS 1.0的支持
 */
#ifdef CONFIG_MBEDTLS_SSL_PROTO_TLS1_1
#define MBEDTLS_SSL_PROTO_TLS1_1
#else
#undef MBEDTLS_SSL_PROTO_TLS1_1
#endif

/**
 * \定义MBEDTLS_SL_PROTO_TLS1_2
 *
 * 启用TLS 1.2支持（如果启用了DTLS，则启用DTLS 1.2）。
 *
 * 需要：MBEDTLS_SHA1_C或MBEDTL_SHA256_C或MBEDLLS_SHA512_C（取决于密码套件）
 *
 * 注释此宏以禁用对TLS 1.2/DTLS 1.2的支持
 */
#ifdef CONFIG_MBEDTLS_SSL_PROTO_TLS1_2
#define MBEDTLS_SSL_PROTO_TLS1_2
#else
#undef MBEDTLS_SSL_PROTO_TLS1_2
#endif

/**
 * \定义MBEDTLS_SL_PROTO_DTLS
 *
 * 启用对DTLS的支持（所有可用版本）。
 *
 * 启用此和MBEDTLS_SL_PROTO_TLS1_1以启用DTLS 1.0，和/或启用此和MBEDTLS_SSL_PROTO_TLS1_2以启用DTLS1.2。
 *
 * 需要：MBEDTLS_SL_PROTO_TLS1_1或MBEDTLS_SL_PROTO-TLS1_2
 *
 * 注释此宏以禁用对DTLS的支持
 */
#ifdef CONFIG_MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_PROTO_DTLS
#else
#undef MBEDTLS_SSL_PROTO_DTLS
#endif

/**
 * \定义MBEDTLS_SL_ALPN
 *
 * 启用对RFC 7301应用层协议协商的支持。
 *
 * 注释此宏以禁用对ALPN的支持。
 */
#ifdef CONFIG_MBEDTLS_SSL_ALPN
#define MBEDTLS_SSL_ALPN
#else
#undef MBEDTLS_SSL_ALPN
#endif

/**
 * \定义MBEDTLS_SL_DTLS_ANTI_REPLAY
 *
 * 启用对DTLS中的反重放机制的支持。
 *
 * 需要：MBEDTLS_SL_TLS_C MBEDTLS_SL_PROTO_DTLS
 *
 * \警告禁用此功能通常存在安全风险！有关详细信息，请参见mbedtls_ssl_conf_dtls_anti_replay（）。
 *
 * 对此进行注释以禁用DTLS中的反重放。
 */
#ifdef CONFIG_MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_DTLS_ANTI_REPLAY
#else
#undef MBEDTLS_SSL_DTLS_ANTI_REPLAY
#endif

/**
 * \定义MBEDTLS_SL_DTLS_HELLO_VERIFY
 *
 * 在DTLS服务器上启用对HelloVerifyRequest的支持。
 *
 * 强烈建议使用此功能以防止DTLS服务器在针对其他主机的DoS攻击中用作放大器。除非您确定放大在服务器运行的环境中不会出现问题，否则应始终启用它。
 *
 * \警告禁用此功能可能会带来安全风险！（见上文）
 *
 * 需要：MBEDTLS_SL_PROTO_DTLS
 *
 * 对此进行注释以禁用对HelloVerifyRequest的支持。
 */
#ifdef CONFIG_MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_DTLS_HELLO_VERIFY
#else
#undef MBEDTLS_SSL_DTLS_HELLO_VERIFY
#endif

/**
 * \定义MBEDTLS_SL_DTLS_SRTP
 *
 * 通过use_SRTP扩展启用对DTLS-SRTP（RFC 5764）协商的支持。
 *
 * \注意：此功能提供协商DTLS-SRTP的使用以及允许导出相关SRTP数据包保护密钥材料所需的最低功能。特别是，SRTP数据包保护本身，以及数据报层的RTP和DTLS数据包的解复用（参见RFC 5764的第5节），不受此功能的处理。相反，在成功完成协商DTLS-SRTP使用的握手后，应使用扩展密钥导出器API mbedtls_ssl_conf_export_keys_ext_cb（）来实现RFC 5764和RFC 5705第4.2节中描述的密钥导出器（这在ssl示例程序中实现）。然后将生成的密钥传递给SRTP堆栈。
 *
 * 设置此选项将启用运行时API mbedtls_ssl_conf_dtls_sportp_protection_profles（），通过该API可以配置支持的dtls-srtp保护配置文件。如果希望协商DTLS-SRTP的使用，则必须在运行时调用此API。
 *
 * 需要：MBEDTLS_SL_PROTO_DTLS
 *
 * 取消注释以启用对use_srtp扩展的支持。
 */
#ifdef CONFIG_MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_DTLS_SRTP
#else
#undef MBEDTLS_SSL_DTLS_SRTP
#endif

/**
 * \定义MBEDTLS_SL_DTLS_CLIENT_PORT_REUSE
 *
 * 为从同一端口重新连接的客户端启用服务器端支持。
 *
 * 一些客户端意外地关闭了连接，并尝试使用相同的源端口重新连接。这需要服务器的特殊支持才能安全地处理新连接，如RFC 6347第4.2.8节所述。此标志启用了该支持。
 *
 * 需要：MBEDTLS_SL_DTLS_HELLO_VERIFY
 *
 * 对此进行注释以禁用对客户端重用源端口的支持。
 */
#ifdef CONFIG_MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_DTLS_CLIENT_PORT_REUSE
#else
#undef MBEDTLS_SSL_DTLS_CLIENT_PORT_REUSE
#endif

/**
 * \定义MBEDTLS_SL_DTLS_BADMAC_LIMIT
 *
 * 启用对具有坏MAC的记录的限制支持。
 *
 * 请参见mbedtls_ssl_conf_dtls_baadmac_limit（）。
 *
 * 需要：MBEDTLS_SL_PROTO_DTLS
 */
#ifdef CONFIG_MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_DTLS_BADMAC_LIMIT
#else
#undef MBEDTLS_SSL_DTLS_BADMAC_LIMIT
#endif

/**
 * \定义MBEDTLS_SL_SESSION_TICKETS
 *
 * 启用SSL中对RFC 5077会话票证的支持。客户端为会话票证提供完全支持（但会话存储的维护仍然由应用程序负责）。在服务器端，您还需要提供写和解析票据的回调，包括经过身份验证的加密和密钥管理。MBEDTLS_SL_TICKET_C提供了示例回调。
 *
 * 注释此宏以禁用对SSL会话票证的支持
 */
#ifdef CONFIG_MBEDTLS_CLIENT_SSL_SESSION_TICKETS
#define MBEDTLS_SSL_SESSION_TICKETS
#else
#undef MBEDTLS_SSL_SESSION_TICKETS
#endif

/**
 * \定义MBEDTLS_SL_EXPORT_KEYS
 *
 * 支持导出密钥块和主密钥。这对于TLS的某些用户是必需的，例如EAP-TLS。
 *
 * 注释此宏以禁用对密钥导出的支持
 */
#define MBEDTLS_SSL_EXPORT_KEYS

/**
 * \定义MBEDTLS_SL_SERVER_NAME_INDICATION
 *
 * 启用SSL中对RFC 6066服务器名称指示（SNI）的支持。
 *
 * 需要：MBEDTLS_X509_CRT_PARSE_C
 *
 * 注释此宏以禁用对SSL中服务器名称指示的支持
 */
#define MBEDTLS_SSL_SERVER_NAME_INDICATION

/**
 * \定义MBEDTLS_SL_TRUNCATED_HMAC
 *
 * 在SSL中启用对RFC 6066截断HMAC的支持。
 *
 * 注释此宏以禁用对SSL中截断HMAC的支持
 */
#define MBEDTLS_SSL_TRUNCATED_HMAC

/**
 * \定义MBEDTLS_SL_VARIABLE_BUFFER_LENGTH
 *
 * 启用此选项后，SSL缓冲区将根据每个方向上协商的最大片段长度自动调整大小。
 *
 * 需要：MBEDTLS_SL_MAX_FRAGMENT_LENGTH
 */
#if defined MBEDTLS_SSL_MAX_FRAGMENT_LENGTH && CONFIG_MBEDTLS_SSL_VARIABLE_BUFFER_LENGTH
#define MBEDTLS_SSL_VARIABLE_BUFFER_LENGTH
#else
#undef MBEDTLS_SSL_VARIABLE_BUFFER_LENGTH
#endif

/**
 * \定义MBEDTLS_VERSION_FEATURES
 *
 * 允许对启用编译时功能的运行时检查。因此，允许用户在运行时通过mbedtls_version_check_feature（）检查库是否在线程支持下编译。
 *
 * 需要：MBEDTLS_VERSION_C
 *
 * 对此进行注释以禁用运行时检查并节省ROM空间
 */
#define MBEDTLS_VERSION_FEATURES

/**
 * \定义MBEDTLS_X509_CHECK_KEY_USAGE
 *
 * 启用keyUsage扩展（CA和叶证书）的验证。
 *
 * 禁用此选项可避免错误颁发和/或误用（中间）CA和叶证书的问题。
 *
 * \警告根据您的PKI使用情况，禁用此功能可能存在安全风险！
 *
 * 跳过CA和叶证书的keyUsage检查的注释。
 */
#ifdef CONFIG_MBEDTLS_X509_CHECK_KEY_USAGE
#define MBEDTLS_X509_CHECK_KEY_USAGE
#else
#undef MBEDTLS_X509_CHECK_KEY_USAGE
#endif

/**
 * \定义MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
 *
 * 启用extendedKeyUsage扩展（叶证书）的验证。
 *
 * 禁用此功能可避免错误颁发和/或误用证书的问题。
 *
 * \警告根据您的PKI使用情况，禁用此功能可能存在安全风险！
 *
 * 跳过证书的extendedKeyUsage检查的注释。
 */
#ifdef CONFIG_MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
#define MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
#else
#undef MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
#endif

/**
 * \定义MBEDTLS_X509_RSASSA_PSS_SUPPORT
 *
 * 启用使用RSASSA-PSS（又名PKCS#1 v2.1）签名的X.509证书、CRL和CSRS的解析和验证。
 *
 * 注释此宏以禁止在证书中使用RSASSA-PSS。
 */
#define MBEDTLS_X509_RSASSA_PSS_SUPPORT


/* \}name SECTION:mbed TLS功能支持*/

/**
 * \name SECTION:mbed TLS模块
 *
 * 本节启用或禁用mbed TLS中的整个模块\{
 */

/**
 * \定义MBEDTLS_AESNI_C
 *
 * 在x86-64上启用AES-NI支持。
 *
 * 模块：library/aesni.c调用方：library/eas.c
 *
 * 需要：MBEDTLS_HAVE_ASM
 *
 * 此模块增加了对x86-64上AES-NI指令的支持
 */
#define MBEDTLS_AESNI_C

/**
 * \定义MBEDTLS_AES_C
 *
 * 启用AES块密码。
 *
 * 模块：library/aes。c调用方：library/ssl_tls。c库/pem。c库/ctr_drbg.c
 *
 * 此模块启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA MBEDTLS_TLS_ECDS_WITH_AES_256_CBC_SHA MBEDTL_TLS_ECDH_RSA_WITH_AES_128 _CBC_SHAMBEDTLS-TLS_ELS_ECDH_LSA_WITH_AES_128_CBC_SHAN MBEDTLSTLS_TLS_ECD H_ECDSA-WITH_AES_228_CBC-SHA256 MBEDLS_TLS-ECDH_ECDSA.WITH_AES_2 56_CBC_SHA384MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256 MBEDTLS_ECDH _RSA_wwith_AES_256_CBC_sha 384 MBEDTLS_TLS_ECDH-ECDSA _WITH_AES _128_GCM_SHA256 mbdtls_TLS _ECDH_edcdsa _wwith_AES _256_GCM_sha 384 mbdtls_esdh_RSA-WITH_AES_228_GCM-SHA256使用256厘米的沙384MBEDTLS_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384 MBEDTLS_ECDHE_ECDSA_WITH-AES_256_CBC_SHA384 mbdtls_TLS _ECDHE_RSA-WITH_AES_2 56_CBC-SHA384 mbedt ls_TLS-DHE_rsawith_AES_2256_CBC_SHA 256 MBEDTLS-ECDHE _ECDSA-WITH-AES_2 56_CBC_SHA具有128个字符的字符256带ES_128_GCM_SHA256 MBEDTLS_TLS_DHE_RSA_WITH_AES_128_GCM_sha256mbedtls_ECDHE_ECDSA_WITH-AES_128_CBC_SHA256 embedtls_TLS _ECDHE_RSA-WITH_AES_128_CBC _SHA256 mbdtls_DHE_RSA-WITH-AES_128_CBC_sha256mbdtls_tles_ECDHE_SHA256 ls_DHE_RSA_WITH_AES_128_CBC_SHAMBEDTLS_TLS_DHE_PSK_WITH_AES_256_GCM_SHA384 MBEDTLS_TLS_ECDHE_PSK-WITH_AES_2 56_CBC_SHA384 mbdtls_TLS _DHE_PSK _WITH_AES _256_CBC-SHA384 mbedt ls_TLS_ECDHE _PSK-wwith_AES_256-CBC_SHA384 MBEDTLS _TLS_ecd he_PSK/WITH_AES_128_GCM_SHA 256 MBEDTLS_ecd he _PSK_wwith_AES_128 mbc_SHA256 MBEDTLS _ecd he-PSK带ES_128_CBC_SHA256 MBEDTLS_TLS_ECDHE_PSK带ES_128 _CBC_SHAMBEDTLS_TLS_DHE_PSK_WITH_AES_128_CBC_SHA MBEDTLS_TLS_RSA-WITH_AES_256_GCM_SHA384 MBEDTLS_nls_RSA_WITH_AES _256_CBC_SHA256 MBEDTLS_RSA/WITH_AES_2 56_CBC-SHA MBEDTLS _TLS_rsaw ith_AES_1 28_GCM_SHA 256 MBEDTLS _RSA-wwith_AES_128 MBEDTLS_SHA256 embedtls_TLS _RSA_wwith_AES_228_CBC-SHA256 mbeds_TLS_RSA ls_RSA_PSK_WITH_AES_256_CBC_SHA384MBEDTLS_TLS_RSA_PSK_WITH_AES_256_CBC_SHA MBEDTLS_TLS_RSA-PSK_WITH-AES_128_GCM_SHA256 MBEDTLS_RSA_ssk_WITH_AES_128_CBC_SHA256 mbdtls_TLS _RSA_PSK _WITH_AES _128_CBC _SHA mbedt ls_TLS_PSK_wwith-AES_256_GCM_SHA 384 MBEDTLS_SHA384 MBEDTLS _TLS_ssk_wwith_AES_128_GCM_sha128 MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA256MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA
 *
 * PEM_PARSE使用AES对加密密钥进行解密。
 */
#ifdef CONFIG_MBEDTLS_AES_C
#define MBEDTLS_AES_C
#else
#undef MBEDTLS_AES_C
#endif

/**
 * \定义MBEDTLS_ASN1_PARSE_C
 *
 * 启用通用ASN1解析器。
 *
 * 模块：library/asn1.c调用方：library/x509.c library/dhm。c库/pkcs12.c库/pqcs5.c库/pkpparse.c
 */
#define MBEDTLS_ASN1_PARSE_C

/**
 * \定义MBEDTLS_ASN1_WRITE_C
 *
 * 启用通用ASN1编写器。
 *
 * 模块：library/asn1write。c调用方：library/edsa。c库/pkwrite。c库/x509_create。c库/x509write_crt。c库/mbedtls_x509write_csr.c
 */
#define MBEDTLS_ASN1_WRITE_C

/**
 * \定义MBEDTLS_BASE64_C
 *
 * 启用Base64模块。
 *
 * 模块：library/base64.c调用方：library/pem.c
 *
 * PEM支持需要此模块（X.509要求）。
 */
#define MBEDTLS_BASE64_C

/**
 * \定义MBEDTLS_BIGNUM_C
 *
 * 启用多精度整数库。
 *
 * 模块：library/bignum。c呼叫者：library/dhm。c库/ecp。c库/edsa。c库/rsa。c库/ssl_tls.c
 *
 * RSA、DHM和ECC（ECDH、ECDSA）支持需要此模块。
 */
#define MBEDTLS_BIGNUM_C

/**
 * \定义MBEDTLS_BLOWFISH_C
 *
 * 启用Blowfish块密码。
 *
 * 模块：library/bloofish.c
 */
#ifdef CONFIG_MBEDTLS_BLOWFISH_C
#define MBEDTLS_BLOWFISH_C
#else
#undef MBEDTLS_BLOWFISH_C
#endif

/**
 * \定义MBEDTLS_CAMELLIA_C
 *
 * 启用Camellia分组密码。
 *
 * 模块：图书馆/茶花。c调用方：library/ssl_tls.c
 *
 * 此模块启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256 MBEDTLS_TLS_ECDS_ECDSA_WITH_CAMELLEA_256_CBC_SHAD84 MBEDTL_TLS_ECDH_RSA_WITH_CAMELLAA_128_CBC _SHA256 MBEDTLS_TLS_ECD H_RSA_ WITH_CAMELIA_256_CBC _SHAD84MBEDTLS_TLS_ECDH_RSA_WITH_camelia_128_GCM_SHA256 MBEDTLS_ECDH _RSA_wwith_camelia_256_GCM_sha 384 MBEDTLS_TLS_ECDHE_ECDSA-WITH_CAMELLIA_256_GCM-SHA384 MBEDTLS _ECDHE_RSA-WITH-CAMELLIA_256_GCM_saha384 mbedtles_TLS_ecd he_RSA_WITH _camelia_2 56_GCM_SHA384 bc_SHA384年带梅利亚_256_CBC_SHA256 MBEDTLS_TLS_DHE_RSA_WITH_camelia_256_CBC _SHA256个MBEDTLS_ECDHE_ECDSA_WITH-camelia_128_GCM_SHA256 MBdtls_TLS _ECDHE_RSA-WITH_CAMELLIA_128_GCM-SHA256个_夏256MBEDTLS_TLS_DHE_rsawith_camelia_128_CBC_SHA256 MBEDTLS_TLS_DHE_ssawith_cmellia_128_CBC_SHA384 MBEDTLS_ECDHE_pskwith_CAMELLIA_256_GCM_SHA384 mbdtls_TLS _DHE_pskWith_camelia_256_CBC_SHA 384 MBEDTLS _TLS_DHE _sskwith_cmellian_128_CBC _SHA384 ls_TLS_ECDHE_PSK_WITH_camelia_128_CBC_SHA256MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384 MBEDTLS_TLS_RSA-WITH_camelia_256_CBC_SHA256 MBEDTLS_RSA/WITH_camella_256_CBC_SHA MBEDTLS_lsa_WITH-CAMELLIA_128_GCM_SHA 256 MBEDTLS _TLS_RSA WITH_camelia_128_CBC_SHA 256 embedtls_TLS _RSA-wwith_camella_128_CBC_SHA256 _CBC_SHA384MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256 MBEDTLS_TLS_RSA_ssk_WITH_CAMELLIA_228_CBC_SHA256 mbdtls_t尔斯_PSK_wwith_camellion_256_GCM_sha 384 MBEDTLS_ssk_wwith_Camellion_128_GCM _SHA256
 */
#ifdef CONFIG_MBEDTLS_CAMELLIA_C
#define MBEDTLS_CAMELLIA_C
#else
#undef MBEDTLS_CAMELLIA_C
#endif

/**
 * \定义MBEDTLS_CCM_C
 *
 * 使用CBC-MAC（CCM）模式启用128位分组密码的计数器。
 *
 * 模块：library/ccm.c
 *
 * 需要：MBEDTLS_AES_C或MBEDTLS_CAMELLIA_C
 *
 * 如果还启用了其他必要条件，则此模块启用AES-CCM密码套件。
 */
#ifdef CONFIG_MBEDTLS_CCM_C
#define MBEDTLS_CCM_C
#else
#undef MBEDTLS_CCM_C
#endif

/**
 * \定义MBEDTLS_CERTS_C
 *
 * 启用测试证书。
 *
 * 模块：库/证书。c呼叫者：
 *
 * 此模块用于测试（ssl_client/server）。
 */
#define MBEDTLS_CERTS_C

/**
 * \定义MBEDTLS_CHACHA20_C
 *
 * 启用ChaCha20流密码。
 *
 * 模块：library/cacha20.c
 */
#ifdef CONFIG_MBEDTLS_CHACHA20_C
#define MBEDTLS_CHACHA20_C
#else
#undef MBEDTLS_CHACHA20_C
#endif

/**
 * \定义MBEDTLS_CHACHAPOLY_C
 *
 * 启用ChaCha20-Poly1305 AEAD算法。
 *
 * 模块：library/cachapaly.c
 *
 * 此模块需要：MBEDTLS_CHACHA20_C、MBEDTLS_POLY1305_C
 */
#ifdef CONFIG_MBEDTLS_CHACHAPOLY_C
#define MBEDTLS_CHACHAPOLY_C
#else
#undef MBEDTLS_CHACHAPOLY_C
#endif

/**
 * \定义MBEDTLS_CIPHER_C
 *
 * 启用通用密码层。
 *
 * 模块：库/密码。c调用方：library/ssl_tls.c
 *
 * 取消注释以启用通用密码包装器。
 */
#define MBEDTLS_CIPHER_C

/**
 * \定义MBEDTLS_CTR_DRBG_C
 *
 * 启用基于CTR_DRBG AES-256的随机生成器。
 *
 * 模块：library/ctr_drbg。c呼叫者：
 *
 * 需要：MBEDTLS_AES_C
 *
 * 该模块提供CTR_DRBG AES-256随机数发生器。
 */
#define MBEDTLS_CTR_DRBG_C

/**
 * \定义MBEDTLS_DEBUG_C
 *
 * 启用调试功能。
 *
 * 模块：库/调试。c呼叫者：library/ssl_cli。c库/ssl_srv。c库/ssl_tls.c
 *
 * 此模块提供调试功能。
 */
#if CONFIG_MBEDTLS_DEBUG
#define MBEDTLS_DEBUG_C
#else
#undef MBEDTLS_DEBUG_C
#endif

/**
 * \定义MBEDTLS_DES_C
 *
 * 启用DES分组密码。
 *
 * 模块：library/des。c调用方：library/pem。c库/ssl_tls.c
 *
 * 此模块启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA MBEDTLS_TLS_ECDH_2RSA_WITH_3DES-EDE_CBC_SHA MBEDLLS_TLS_ECTHE_ECDSA_WITH_23DES_EDE _CBC_SHAMBEDTL_TLS_ECDHE_RSA_WITH-3DES_EBC_SHA HE_PSK_WITH_3DES_EDE_CBC_SHAMBEDTLS_TLS_RSA_WITH_3DES_EDE_CBC_SHA MBEDTLS_TLS_RSA_PSK_WITH_3DES _EDE_CBC _SHA
 *
 * PEM_PARSE使用DES/3DES对加密密钥进行解密。
 */
#ifdef CONFIG_MBEDTLS_DES_C
#define MBEDTLS_DES_C
#else
#undef MBEDTLS_DES_C
#endif

/**
 * \定义MBEDTLS_DHM_C
 *
 * 启用Diffie-Hellman-Merkle模块。
 *
 * 模块：library/dhm。c呼叫者：library/ssl_cli。c库/ssl_srv.c
 *
 * 该模块用于以下密钥交换：DHE-RSA、DHE-PSK
 */
#define MBEDTLS_DHM_C

/**
 * \定义MBEDTLS_ECDH_C
 *
 * 启用椭圆曲线Diffie-Hellman库。
 *
 * 模块：library/edh。c呼叫者：library/ssl_cli。c库/ssl_srv.c
 *
 * 该模块用于以下密钥交换：ECDHE-ECDSA、ECDHE-RSA、DHE-PSK
 *
 * 需要：MBEDTLS_ECP_C
 */
#ifdef CONFIG_MBEDTLS_ECDH_C
#define MBEDTLS_ECDH_C
#else
#undef MBEDTLS_ECDH_C
#endif

/**
 * \定义MBEDTLS_ECDSA_C
 *
 * 启用椭圆曲线DSA库。
 *
 * 模块：library/edsa。c呼叫者：
 *
 * 该模块用于以下密钥交换：ECDHE-ECDSA
 *
 * 对于短Weierstrass曲线，需要：MBEDTLS_ECP_C、MBEDTLS_ASN1_WRITE_C、MBEDTLS_ASN1_PARSE_C和至少一个MBEDTLS-ECP_XXX_ENABLED。
 */
#ifdef CONFIG_MBEDTLS_ECDSA_C
#define MBEDTLS_ECDSA_C
#else
#undef MBEDTLS_ECDSA_C
#endif

/**
 * \定义MBEDTLS_ECJPAKE_C
 *
 * 启用椭圆曲线J-PAKE库。
 *
 * \警告这目前是实验性的。EC J-PAKE支持基于Thread v1.0.0规范；对规范的不兼容更改仍可能发生。因此，默认情况下禁用此功能。
 *
 * 模块：library/ecjpake。c呼叫者：
 *
 * 此模块由以下密钥交换使用：ECJPAKE
 *
 * 需要：MBEDTLS_ECP_C、MBEDTLS_MD_C
 */
#ifdef CONFIG_MBEDTLS_ECJPAKE_C
#define MBEDTLS_ECJPAKE_C
#else
#undef MBEDTLS_ECJPAKE_C
#endif

/**
 * \定义MBEDTLS_ECP_C
 *
 * 启用GF（p）库上的椭圆曲线。
 *
 * 模块：library/ecp。c调用方：library/edh。c库/edsa。c库/ecjpake.c
 *
 * 需要：MBEDTLS_BIGNUM_C和至少一个MBEDTL_ECP_DP_XXX_ENABLED
 */
#ifdef CONFIG_MBEDTLS_ECP_C
#define MBEDTLS_ECP_C
#else
#undef MBEDTLS_ECP_C
#endif

/**
 * \定义MBEDTLS_ENTROPY_C
 *
 * 启用特定于平台的熵代码。
 *
 * 模块：库/熵。c呼叫者：
 *
 * 需要：MBEDTLS_HA512_C或MBEDTL_SHA256_C
 *
 * 本模块提供通用熵池
 */
#define MBEDTLS_ENTROPY_C

/**
 * \定义MBEDTLS_ERROR_C
 *
 * 启用错误代码到错误字符串的转换。
 *
 * 模块：库/错误。c呼叫者：
 *
 * 此模块启用mbedtls_strerror（）。
 */
#define MBEDTLS_ERROR_C

/**
 * \定义MBEDTLS_GCM_C
 *
 * 启用伽罗瓦/计数器模式（GCM）。
 *
 * 模块：library/gcm.c
 *
 * 需要：MBEDTLS_AES_C或MBEDTLS_CAMELLIA-C或MBEDTLS_ARIA_C
 *
 * 如果还启用了其他必要条件，则该模块启用AES-GCM和CAMELLIA-GCM密码套件。
 */
#ifdef CONFIG_MBEDTLS_GCM_C
#define MBEDTLS_GCM_C
#else
#undef MBEDTLS_GCM_C
#endif

/**
 * \定义MBEDTLS_HKDF_C
 *
 * 启用HKDF算法（RFC 5869）。
 *
 * 模块：library/hkdf。c呼叫者：
 *
 * 需要：MBEDTLS_MD_C
 *
 * 该模块支持基于哈希消息认证码（HMAC）的密钥派生功能（HKDF）。
 */
#ifdef CONFIG_MBEDTLS_HKDF_C
#define MBEDTLS_HKDF_C
#else
#undef MBEDTLS_HKDF_C
#endif

/**
 * \定义MBEDTLS_MAC_DRBG_C
 *
 * 启用HMAC_DRBG随机生成器。
 *
 * 模块：library/hmac_drbg。c呼叫者：
 *
 * 需要：MBEDTLS_MD_C
 *
 * 取消注释以启用HMAC_DRBG随机数生成器。
 */
#define MBEDTLS_HMAC_DRBG_C

/**
 * \定义MBEDTLS_MD_C
 *
 * 启用通用消息摘要层。
 *
 * 模块：library/mbedtls_md。c呼叫者：
 *
 * 取消注释以启用通用消息摘要包装器。
 */
#define MBEDTLS_MD_C

/**
 * \定义MBEDTLS_MD5_C
 *
 * 启用MD5哈希算法。
 *
 * 模块：library/mbedtls_md5.c调用方：library/embedtls_md。c库/pem。c库/ssl_tls.c
 *
 * SSL/TLS和X.509需要此模块。PEM_PARSE使用MD5解密加密密钥。
 */
#define MBEDTLS_MD5_C

/**
 * \定义MBEDTLS_NET_C
 *
 * 启用TCP/IP网络例程。
 *
 * 模块：library/net.c
 *
 * 此模块提供TCP/IP网络例程。
 */
#ifdef MBEDTLS_NET_C
#undef MBEDTLS_NET_C
#endif

/**
 * \定义MBEDTLS_OID_C
 *
 * 启用OID数据库。
 *
 * 模块：library/oid。c调用方：library/asn1write。c库/pkcs5.c库/pkparse。c库/pkwrite。c库/rsa。c库/x509.c库/x509_create。c库/mbedtls_x509_crl。c库/mbedtls_x509_crt。c库/mbedtls_x509_csr。c库/x509write_crt。c库/mbedtls_x509write_csr.c
 *
 * 该模块在OID和内部值之间转换。
 */
#define MBEDTLS_OID_C

/**
 * \定义MBEDTLS_PADLOCK_C
 *
 * 在x86上启用VIA挂锁支持。
 *
 * 模块：库/挂锁。c调用方：library/aes.c
 *
 * 需要：MBEDTLS_HAVE_ASM
 *
 * 此模块增加了对x86上VIA挂锁的支持。
 */
#define MBEDTLS_PADLOCK_C

/**
 * \定义MBEDTLS_PEM_PARSE_C
 *
 * 启用PEM解码/解析。
 *
 * 模块：库/pem。c呼叫者：library/dhm。c库/pkparse。c库/mbedtls_x509_crl。c库/mbedtls_x509_crt。c库/mbedtls_x509_csr.c
 *
 * 需要：MBEDTLS_BASEE64_C
 *
 * 该模块增加了对PEM文件解码/解析的支持。
 */
#ifdef CONFIG_MBEDTLS_PEM_PARSE_C
#define MBEDTLS_PEM_PARSE_C
#else
#undef MBEDTLS_PEM_PARSE_C
#endif

/**
 * \定义MBEDTLS_MEM_WRITE_C
 *
 * 启用PEM编码/写入。
 *
 * 模块：库/pem。c调用方：library/pkwrite。c库/x509write_crt。c库/mbedtls_x509write_csr.c
 *
 * 需要：MBEDTLS_BASEE64_C
 *
 * 本模块增加了对PEM文件编码/写入的支持。
 */
#ifdef CONFIG_MBEDTLS_PEM_WRITE_C
#define MBEDTLS_PEM_WRITE_C
#else
#undef MBEDTLS_PEM_WRITE_C
#endif

/**
 * \定义MBEDTLS_PK_C
 *
 * 启用通用公共（异步）密钥层。
 *
 * 模块：library/pk。c调用方：library/ssl_tls。c库/ssl_cli。c库/ssl_srv.c
 *
 * 需要：MBEDTLS_RSA_C或MBEDTLS_ECP_C
 *
 * 取消注释以启用通用公钥包装器。
 */
#define MBEDTLS_PK_C

/**
 * \定义MBEDTLS_PK_PARSE_C
 *
 * 启用通用公共（异步）密钥分析器。
 *
 * 模块：library/pkparse。c调用方：library/mbedtls_x509_crt。c库/mbedtls_x509_csr.c
 *
 * 需要：MBEDTLS_PK_C
 *
 * 取消注释以启用通用公钥解析函数。
 */
#define MBEDTLS_PK_PARSE_C

/**
 * \定义MBEDTLS_PK_WRITE_C
 *
 * 启用通用公共（异步）密钥编写器。
 *
 * 模块：library/pkwrite。c调用方：library/x509write.c
 *
 * 需要：MBEDTLS_PK_C
 *
 * 取消注释以启用通用公钥写入函数。
 */
#define MBEDTLS_PK_WRITE_C

/**
 * \定义MBEDTLS_PKCS5_C
 *
 * 启用PKCS#5功能。
 *
 * 模块：library/pkcs5.c
 *
 * 需要：MBEDTLS_MD_C
 *
 * 此模块添加了对PKCS#5函数的支持。
 */
#define MBEDTLS_PKCS5_C

/**
 * \定义MBEDTLS_PKCS12_C
 *
 * 启用PKCS#12 PBE功能。添加用于解析PKCS#8加密私钥的算法
 *
 * 模块：library/pkcs12.c调用方：library/pkparse.c
 *
 * 需要：MBEDTLS_ASN1_PARSE_C、MBEDTLS_CIPHER_C和MBEDTLS_MD_C可以使用：MBEDTLS_ARC4_C
 *
 * 此模块启用PKCS#12功能。
 */
#define MBEDTLS_PKCS12_C

/**
 * \定义MBEDTLS_PLATFORM_C
 *
 * 启用平台抽象层，允许您重新分配calloc（）、free（）、snprintf（）、printf（（）、fprintf（）、exit（）等函数。
 *
 * 启用MBEDTLS_PLATFORM_C可以使用MBEDTLS_PLATFORM_XXX_ALT或MBEDTLC_PLATFORM_6XX_MARO指令，允许分别在运行时或编译时指定上述函数。
 *
 * \注意：这个抽象层必须在Windows（包括MSYS2）上启用，因为其他模块依赖它来实现固定的snprintf。
 *
 * 模块：库/平台。c调用方：大多数其他.c文件
 *
 * 该模块支持公共（libc）函数的抽象。
 */
#define MBEDTLS_PLATFORM_C

/**
 * \定义MBEDTLS_POLY1305_C
 *
 * 启用Poly1305 MAC算法。
 *
 * 模块：library/poly1305.c调用方：library/cachapaly.c
 */
#ifdef CONFIG_MBEDTLS_POLY1305_C
#define MBEDTLS_POLY1305_C
#else
#undef MBEDTLS_POLY1305_C
#endif

/**
 * \定义MBEDTLS_RIPEMD160_C
 *
 * 启用RIPEMD-160哈希算法。
 *
 * 模块：library/mbedtls_ripemd160.c调用方：library/embedtls_md.c
 *
 */
#ifdef CONFIG_MBEDTLS_RIPEMD160_C
#define MBEDTLS_RIPEMD160_C
#else
#undef MBEDTLS_RIPEMD160_C
#endif

/**
 * \定义MBEDTLS_RSA_C
 *
 * 启用RSA公钥密码系统。
 *
 * 模块：library/rsa。c呼叫者：library/ssl_cli。c库/ssl_srv。c库/ssl_tls。c库/x509.c
 *
 * 该模块用于以下密钥交换：RSA、DHE-RSA、ECDHE-RSA、RSA-PSK
 *
 * 需要：MBEDTLS_BIGNUM_C、MBEDTLS_OID_C
 */
#define MBEDTLS_RSA_C

/**
 * \定义MBEDTLS_SHA1_C
 *
 * 启用SHA1加密哈希算法。
 *
 * 模块：library/mbedtls_sha1.c调用方：library/embedtls_md。c库/ssl_cli。c库/ssl_srv。c库/ssl_tls。c库/x509 write_crt.c
 *
 * SSL/TLS和SHA1签名证书需要此模块。
 */
#define MBEDTLS_SHA1_C

/**
 * \定义MBEDTLS_SHA256_C
 *
 * 启用SHA-224和SHA-256加密哈希算法。
 *
 * 模块：library/mbedtls_sha256.c调用方：library/engency。c库/mbedtls_md。c库/ssl_cli。c库/ssl_srv。c库/ssl_tls.c
 *
 * 此模块增加了对SHA-224和SHA-256的支持。SSL/TLS 1.2 PRF功能需要此模块。
 */
#define MBEDTLS_SHA256_C

/**
 * \定义MBEDTLS_SHA512_C
 *
 * 启用SHA-384和SHA-512加密哈希算法。
 *
 * 模块：library/mbedtls_sha512.c调用方：library/engency。c库/mbedtls_md。c库/ssl_cli。c库/ssl_srv.c
 *
 * 该模块增加了对SHA-384和SHA-512的支持。
 */
#ifdef CONFIG_MBEDTLS_SHA512_C
#define MBEDTLS_SHA512_C
#else
#undef MBEDTLS_SHA512_C
#endif

/**
 * \定义MBEDTLS_SL_CACHE_C
 *
 * 启用简单的SSL缓存实现。
 *
 * 模块：library/ssl_cache。c呼叫者：
 *
 * 需要：MBEDTLS_SL_CACHE_C
 */
#define MBEDTLS_SSL_CACHE_C

/**
 * \定义MBEDTLS_SL_COOKIE_C
 *
 * 为hello验证启用DTLS cookie的基本实现。
 *
 * 模块：library/ssl_cookie。c呼叫者：
 */
#define MBEDTLS_SSL_COOKIE_C

/**
 * \定义MBEDTLS_SL_TICKET_C
 *
 * 为会话票证启用TLS服务器端回调的实现。
 *
 * 模块：library/ssl_ticket。c呼叫者：
 *
 * 需要：MBEDTLS_CIPHER_C
 */
#ifdef CONFIG_MBEDTLS_SERVER_SSL_SESSION_TICKETS
#define MBEDTLS_SSL_TICKET_C
#else
#undef MBEDTLS_SSL_TICKET_C
#endif

/**
 * \定义MBEDTLS_SL_CLI_C
 *
 * 启用SSL/TLS客户端代码。
 *
 * 模块：library/ssl_cli。c呼叫者：
 *
 * 需要：MBEDTLS_SL_TLS_C
 *
 * SSL/TLS客户端支持需要此模块。
 */
#ifdef CONFIG_MBEDTLS_TLS_CLIENT
#define MBEDTLS_SSL_CLI_C
#else
#undef MBEDTLS_SSL_CLI_C
#endif

/**
 * \定义MBEDTLS_SL_SRV_C
 *
 * 启用SSL/TLS服务器代码。
 *
 * 模块：library/ssl_srv。c呼叫者：
 *
 * 需要：MBEDTLS_SL_TLS_C
 *
 * SSL/TLS服务器支持需要此模块。
 */
#ifdef CONFIG_MBEDTLS_TLS_SERVER
#define MBEDTLS_SSL_SRV_C
#else
#undef MBEDTLS_SSL_SRV_C
#endif

/**
 * \定义MBEDTLS_SL_TLS_C
 *
 * 启用通用SSL/TLS代码。
 *
 * 模块：library/ssl_tls。c呼叫者：library/ssl_cli。c库/ssl_srv.c
 *
 * 需要：MBEDTLS_CIPHER_C、MBEDTLS_MD_C和至少一个MBEDTL_SSL_PROTO_XXX定义
 *
 * SSL/TLS需要此模块。
 */
#ifdef CONFIG_MBEDTLS_TLS_ENABLED
#define MBEDTLS_SSL_TLS_C
#else
#undef MBEDTLS_SSL_TLS_C
#endif

/**
 * \定义MBEDTLS_IMING_C
 *
 * 启用半便携式定时接口。
 *
 * \注意：提供的实现仅适用于POSIX/Unix（包括Linux、BSD和OS X）和Windows。在其他平台上，您可以禁用该模块，并为DTLS提供\c mbedtls_ssl_set_timer_cb（）所需的回调的自己实现，也可以通过在当前文件中设置\c mbedtls_TIMING_ALT，使其处于启用状态，并提供整个模块的自己实现。
 *
 * \注意：另请参阅我们的知识库文章，了解如何移植到新环境：https://tls.mbed.org/kb/how-to/how-do-i-port-mbed-tls-to-a-new-environment-OS
 *
 * 模块：库/计时。c调用方：library/havege.c
 *
 * HAVEGE随机数生成器使用此模块。
 */
#ifdef MBEDTLS_TIMING_C
#undef MBEDTLS_TIMING_C
#endif

/**
 * \定义MBEDTLS_VERSION_C
 *
 * 启用运行时版本信息。
 *
 * 模块：library/version.c
 *
 * 此模块提供运行时版本信息。
 */
#define MBEDTLS_VERSION_C

/**
 * \定义MBEDTLS_X509_USE_C
 *
 * 启用X.509核心以使用证书。
 *
 * 模块：library/x509.c调用方：library/mbedtls_x509_crl。c库/mbedtls_x509_crt。c库/mbedtls_x509_csr.c
 *
 * 需要：MBEDTLS_ASN1_PARSE_C、MBEDTLS_BIGNUM_C、EMBEDTLS_OID_C、MBEDTLS_PK_PARSE_C
 *
 * X.509解析模块需要此模块。
 */
#define MBEDTLS_X509_USE_C

/**
 * \定义MBEDTLS_X509_CRT_PARSE_C
 *
 * 启用X.509证书分析。
 *
 * 模块：library/mbedtls_x509_crt。c呼叫者：library/ssl_cli。c库/ssl_srv。c库/ssl_tls.c
 *
 * 需要：MBEDTLS_X509_USE_C
 *
 * X.509证书分析需要此模块。
 */
#define MBEDTLS_X509_CRT_PARSE_C

/**
 * \定义MBEDTLS_X509_CRL_PARSE_C
 *
 * 启用X.509 CRL分析。
 *
 * 模块：library/mbedtls_x509_crl。c调用方：library/mbedtls_x509_crt.c
 *
 * 需要：MBEDTLS_X509_USE_C
 *
 * X.509 CRL分析需要此模块。
 */
#ifdef CONFIG_MBEDTLS_X509_CRL_PARSE_C
#define MBEDTLS_X509_CRL_PARSE_C
#else
#undef MBEDTLS_X509_CRL_PARSE_C
#endif

/**
 * \定义MBEDTLS_X509_CSR_PARSE_C
 *
 * 启用X.509证书签名请求（CSR）分析。
 *
 * 模块：library/mbedtls_x509_csr。c调用方：library/x509_crt_write.c
 *
 * 需要：MBEDTLS_X509_USE_C
 *
 * 此模块用于读取X.509证书请求。
 */
#ifdef CONFIG_MBEDTLS_X509_CSR_PARSE_C
#define MBEDTLS_X509_CSR_PARSE_C
#else
#undef MBEDTLS_X509_CSR_PARSE_C
#endif

/**
 * \定义MBEDTLS_X509_CREATE_C
 *
 * 启用X.509核心以创建证书。
 *
 * 模块：library/x509_create.c
 *
 * 需要：MBEDTLS_BIGNUM_C、MBEDTLS_OID_C、MBEDRLS_PK_WRITE_C
 *
 * 该模块是创建X.509证书和CSR的基础。
 */
#define MBEDTLS_X509_CREATE_C

/**
 * \定义MBEDTLS_X509_CRT_WRITE_C
 *
 * 启用创建X.509证书。
 *
 * 模块：library/x509_crt_write.c
 *
 * 需要：MBEDTLS_X509_CREATE_C
 *
 * 创建X.509证书需要此模块。
 */
#define MBEDTLS_X509_CRT_WRITE_C

/**
 * \定义MBEDTLS_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION
 *
  * 提醒X509解析器在解析X509证书并遇到未知的关键扩展时不要中断。
 *
 * 模块：library/x509_crt.c
 *
 * 需要：MBEDTLS_X509_CRT_PARSE_C
 *
 * 此模块支持加载具有mbedtls可能不支持的扩展名的证书。
 */
#ifdef CONFIG_MBEDTLS_ALLOW_UNSUPPORTED_CRITICAL_EXT
#define MBEDTLS_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION
#else
#undef MBEDTLS_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION
#endif

/**
 * \定义MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK
 *
 * 如果已设置，则启用X.509 API“mbedtls_x509_crt_verify_with_ca_ccb（）”和SSL API“mbedtls_SSL_conf_ca_cb（）”，允许用户通过回调而不是链接列表配置受信任证书集。
 *
 * 例如，在存在大量受信任证书且将其存储在链接列表中效率不够的环境中，或者在受信任证书集频繁更改的情况下，这非常有用。
 *
 * 有关详细信息，请参阅“mbedtls_x509_crt_verify_with_ca_ccb（）”和“mbedtls _ssl_conf_ca_cb（）”的文档。
 *
 * 取消注释以启用受信任的证书回调。
 */
#ifdef CONFIG_MBEDTLS_X509_TRUSTED_CERT_CALLBACK
#define MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK
#else
#undef MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK
#endif

/**
 * \定义MBEDTLS_X509_CSR_WRITE_C
 *
 * 启用创建X.509证书签名请求（CSR）。
 *
 * 模块：library/x509_csr_write.c
 *
 * 需要：MBEDTLS_X509_CREATE_C
 *
 * 写入X.509证书请求需要此模块。
 */
#define MBEDTLS_X509_CSR_WRITE_C

/**
 * \定义MBEDTLS_XTEA_C
 *
 * 启用XTEA块密码。
 *
 * 模块：library/xta。c呼叫者：
 */
#ifdef CONFIG_MBEDTLS_XTEA_C
#define MBEDTLS_XTEA_C
#else
#undef MBEDTLS_XTEA_C
#endif

/* \}name SECTION:mbed TLS模块*/

/**
 * \name SECTION：模块配置选项
 *
 * 本节允许设置模块特定大小和配置选项。默认值已经存在于相关的头文件中，应该足以满足常规用例的需要。
 *
 * 我们的建议是，只有在你有充分的理由并知道后果的情况下，才能启用选项并改变其价值观。
 *
 * 请检查相应的头文件以获取有关这些参数的文档（以防止重复文档）\{
 */

/* SSL选项*/
#ifndef CONFIG_MBEDTLS_ASYMMETRIC_CONTENT_LEN

#define MBEDTLS_SSL_MAX_CONTENT_LEN             CONFIG_MBEDTLS_SSL_MAX_CONTENT_LEN /**<以字节为单位的最大片段长度，确定两个内部I/O缓冲区的大小*/

#else

/** \定义MBEDTLS_SL_IN_CONTENT_LEN
 *
 * 最大传入片段长度（字节）。
 *
 * 取消注释以独立于外部缓冲区设置内部TLS缓冲区的大小。
 */
#define MBEDTLS_SSL_IN_CONTENT_LEN              CONFIG_MBEDTLS_SSL_IN_CONTENT_LEN

/** \定义MBEDTLS_SL_CID_IN_LEN_MAX
 *
 * 用于传入DTLS消息的CID的最大长度。
 *
 */
#ifdef CONFIG_MBEDTLS_SSL_DTLS_CONNECTION_ID
#define MBEDTLS_SSL_CID_IN_LEN_MAX              CONFIG_MBEDTLS_SSL_CID_IN_LEN_MAX
#else
#undef MBEDTLS_SSL_CID_IN_LEN_MAX
#endif


/** \定义MBEDTLS_SL_CID_OUT_LEN_MAX
 *
 * 用于传出DTLS消息的CID的最大长度。
 *
 */
#ifdef CONFIG_MBEDTLS_SSL_DTLS_CONNECTION_ID
#define MBEDTLS_SSL_CID_OUT_LEN_MAX            CONFIG_MBEDTLS_SSL_CID_OUT_LEN_MAX
#else
#undef MBEDTLS_SSL_CID_OUT_LEN_MAX
#endif

/** \定义MBEDTLS_SL_CID_PADDING_GRANULARITY
 *
 * 此选项控制在DTLS 1.2中使用连接ID扩展时记录明文填充的使用。
 *
 * 将始终选择填充，以便填充的明文的长度是此选项值的倍数。
 *
 * 注意：值\c 1表示传出记录不使用填充。
 *
 * 注：在缺少除法指令的系统上，应首选二次幂。
 *
 */
#ifdef CONFIG_MBEDTLS_SSL_DTLS_CONNECTION_ID
#define MBEDTLS_SSL_CID_PADDING_GRANULARITY    CONFIG_MBEDTLS_SSL_CID_PADDING_GRANULARITY
#else
#undef MBEDTLS_SSL_CID_PADDING_GRANULARITY
#endif


/** \定义MBEDTLS_SL_OUT_CONTENT_LEN
 *
 * 最大传出片段长度（字节）。
 *
 * 取消注释以独立于向内缓冲区设置向外TLS缓冲区的大小。
 *
 * 可以通过设置较小的向外缓冲区来节省RAM，同时保持默认的向内16384字节缓冲区以符合TLS规范。
 *
 * 所需的最小向外缓冲区大小由握手协议的使用情况决定。如果向外缓冲区太小，握手将失败。具体的大小要求取决于配置的密码和握手期间发送的任何证书数据。
 *
 * 对于绝对最小的RAM使用量，最好启用MBEDTLS_SL_MAX_FRAGMENT_LENGTH并减少MBEDTL_SSL_MAX_CONTENT_LEN。这减少了传入和传出缓冲区的大小。但是，只有当连接的另一端也支持TLS max_fragment_len扩展时，才能保证这一点。否则，连接可能会失败。
 */
#define MBEDTLS_SSL_OUT_CONTENT_LEN             CONFIG_MBEDTLS_SSL_OUT_CONTENT_LEN

#endif /* !CONFIG_MBEDTLS_ASYMMETRIC_CONTENT_LEN */

/**
 * 在TLS 1.2握手签名和密码套件选择的默认TLS配置中允许SHA-1。如果没有此构建时选项，则必须通过mbedtls_ssl_conf_sig_hashe显式激活SHA-1支持。默认情况下，始终允许在TLS<=1.1和HMAC-SHA-1中使用SHA-1。在撰写本文时，没有针对握手签名中使用SHA-1的实际攻击，因此默认情况下，该选项处于启用状态，以与现有对等体兼容。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。如果可能的话，我们建议避免对它的依赖，而是考虑更强大的消息摘要。
 */
#define MBEDTLS_TLS_DEFAULT_ALLOW_SHA1_IN_KEY_EXCHANGE

/**
 * \定义MBEDTLS_THREADING_C
 *
 * 启用线程抽象层。默认情况下，mbed-TLS假设它在非线程环境中使用，或者上下文在线程之间不共享。如果确实要在线程之间使用上下文，则需要启用此层以防止竞争条件。另请参阅我们关于线程的知识库文章：https://tls.mbed.org/kb/development/thread-safety-and-multi-threading
 *
 * 模块：library/threading.c
 *
 * 这允许不同的线程实现（自行实现或提供）。
 *
 * 您必须启用MBEDTLS_THREADING_ALT或MBEDTLS_THREADING_PTHREAD。
 *
 * 启用此层以允许在mbed TLS中使用互斥锁
 */
#ifdef CONFIG_MBEDTLS_THREADING_C
#define MBEDTLS_THREADING_C
#else
#undef MBEDTLS_THREADING_C
#endif

/**
 * \定义MBEDTLS_THREADING_ALT
 *
 * 提供您自己的替代线程实现。
 *
 * 需要：MBEDTLS_THREADING_C
 *
 * 取消对此的注释，以允许您自己的替代线程实现。
 */
#ifdef CONFIG_MBEDTLS_THREADING_ALT
#define MBEDTLS_THREADING_ALT
#else
#undef MBEDTLS_THREADING_ALT
#endif

/**
 * \定义MBEDTLS_THREADING_PTHREAD
 *
 * 为线程层启用pthread包装层。
 *
 * 需要：MBEDTLS_THREADING_C
 *
 * 取消注释以启用pthread互斥锁。
 */
#ifdef CONFIG_MBEDTLS_THREADING_PTHREAD
#define MBEDTLS_THREADING_PTHREAD
#else
#undef MBEDTLS_THREADING_PTHREAD
#endif

/**
 * \定义MBEDTLS_NIST_KW_C
 *
 * 根据NIST启用AES密钥包装
 *
 * 需要：MBEDTLS_AES_C
 *
 * 取消注释以启用aes密钥包装。
 */
#ifdef CONFIG_MBEDTLS_NIST_KW_C
#define MBEDTLS_NIST_KW_C
#else
#undef MBEDTLS_NIST_KW_C
#endif

/* \}name SECTION：模块配置选项*/

#if defined(TARGET_LIKE_MBED)
#include "mbedtls/target_config.h"
#endif

/*
 * 允许用户覆盖以前的任何默认值。
 *
 * 为此使用两个宏名称，如：
 * -对于yotta，前缀yotta_CFG_是强制的
 * -没有yotta前缀看起来很奇怪。
 */
#if defined(YOTTA_CFG_MBEDTLS_USER_CONFIG_FILE)
#include YOTTA_CFG_MBEDTLS_USER_CONFIG_FILE
#elif defined(MBEDTLS_USER_CONFIG_FILE)
#include MBEDTLS_USER_CONFIG_FILE
#endif

#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */

