/**
 * \文件配置.h
 *
 * \简要配置选项（一组定义）
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

#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
#define _CRT_SECURE_NO_DEPRECATE 1
#endif

/**
 * \name SECTION:系统支持
 *
 * 本节设置系统特定设置\{
 */

/**
 * \定义MBEDTLS_HAVE_ASM
 *
 * 编译器支持asm（）。
 *
 * 需要在编译器中支持asm（）。
 *
 * 用于：library/aria.c library/titiming.c include/mbedtls/bn_mul.h
 *
 * 要求者：MBEDTLS_AESNI_C MBEDTLS_PARDLOCK_C
 *
 * 注释以禁用程序集代码的使用。
 */
#define MBEDTLS_HAVE_ASM

/**
 * \定义MBEDTLS_NO_UDBL_DIVISION
 *
 * 该平台不支持双倍宽度整数除法（32位平台上的64位除法，64位平台上128位除法）。
 *
 * 用于：include/mbedtls/bignum.h library/bignum.c
 *
 * bignum代码使用双倍宽度除法来加快某些操作。双幅分割通常在需要与程序链接的软件中实现。双宽整数类型的存在通常通过预处理器宏自动检测，但自动检测无法知道代码是否需要并可以与该类型的除法实现相关联。默认情况下，如果存在该类型，则假定可以使用除法。取消注释此选项以防止使用双倍宽度分割。
 *
 * 请注意，本机整数类型总是需要除法。此外，即使在32位平台上，也始终需要64位类型，但它不需要支持乘法或除法。在某些情况下，还需要禁用一些双倍宽度操作。例如，如果在软件中实现了双宽度分割，禁用它可以减少某些嵌入目标中的代码大小。
 */
//#定义MBEDTLS_NO_UDBL_DIVISION

/**
 * \定义MBEDTLS_NO-64BIT_MULTIFICATION
 *
 * 该平台不支持32x32->64位乘法。
 *
 * 用于：library/poly1305.c
 *
 * 库的某些部分可以使用两个无符号32位操作数与64位结果的乘法，以加快计算速度。在某些平台上，这在硬件中不可用，必须在软件中实现，通常在工具链提供的库中实现。
 *
 * 有时不需要链接到该库。该选项通过在Mbed TLS中嵌入软件实现，消除了该库对缺少硬件64位乘法器的平台的依赖性。
 *
 * 注意，根据编译器的不同，与使用工具链提供的库函数相比，这可能会降低性能。
 */
//#定义MBEDTLS_NO_64BIT_MULTIPLICATION

/**
 * \定义MBEDTLS_HAVE_SSE2
 *
 * CPU支持SSE2指令集。
 *
 * 如果CPU支持SSE2（IA-32特定），则取消注释。
 */
//#定义MBEDTLS_HAVE_SSE2

/**
 * \定义MBEDTLS_HAVE_TIME
 *
 * 系统有time.h和time（）。与MBEDTLS_HAVE_time_DATE相比，时间不需要正确，只使用时间差
 *
 * 通过定义MBEDTLS_HAVE_TIME，您可以指定MBEDTLS_PLATFORM_TIME_ALT、MBEDTLC_PLATFORM_MIMEMACRO、MBEDTLS_PLATFFORM_TIME_TYPE_MACRO和MBEDTLP_PLATFORM_STD_TIME。
 *
 * 如果您的系统不支持时间函数，请说明
 */
#define MBEDTLS_HAVE_TIME

/**
 * \定义MBEDTLS_HAVE_TIME_DATE
 *
 * 系统有time.h、time（）和mbedtls_platform_gmtime_r（）的实现（见下文）。时间需要正确（不一定非常准确，但至少日期应该正确）。这用于验证X.509证书的有效期。
 *
 * 如果您的系统没有正确的时钟，请进行注释。
 *
 * \注意mbedtls_platform_gmtime_r（）是platform_util.h中的一个抽象，其行为类似于C标准中的gmtime_r函数。有关详细信息，请参阅mbedtls_platform_gmtime_r（）的文档。
 *
 * \注意：可以在编译时使用宏mbedtls_platform_gmtime_r_ALT为mbedtls_platform_gmtime_r（）配置实现。
 */
#define MBEDTLS_HAVE_TIME_DATE

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
//#定义MBEDTLS_PLATFORM_MEMORY

/**
 * \定义MBEDTLS_PLATFORM_NO_STD_FUNCTIONS
 *
 * 不要在平台层中分配标准函数（例如，calloc（）到MBEDTLS_platform_STD_calloc，printf（）到MBEDTLS_platform_STD_printf）
 *
 * 这可以确保在不支持这些功能的平台上没有链接错误。您必须在运行时通过platform_set_xxx（）函数或在编译时通过设置MBEDTLS_platform_STD_xxx定义或启用MBEDTLS_platform_XXXMACRO来提供替代方案。
 *
 * 需要：MBEDTLS_PLATFORM_C
 *
 * 取消注释以防止在平台层中默认分配标准函数。
 */
//#定义MBEDTLS_PLATFORM_NO_STD_FUNCTIONS

/**
 * \定义MBEDTLS_PLATFORM_EXIT_ALT
 *
 * MBEDTLS_PLATFORM_XXX_ALT：取消注释宏，以使mbed TLS支持平台抽象层中的功能。
 *
 * 示例：如果取消注释MBEDTLS_PLATFORM_PRINTF_ALT，mbed TLS将提供一个函数“MBEDTLS_PLATFORM_set_PRINTF（）”，允许您设置另一个PRINTF函数指针。
 *
 * 所有这些定义都需要定义MBEDTLS_PLATFORM_C！
 *
 * \注意：Windows上需要MBEDTLS_PLATFORM_SNPRINTF_ALT；它将通过check_config.h自动启用
 *
 * \警告MBEDTLS_PLATFORM_XXX_ALT不能与MBEDTLS_PLATFORM_6XX_MCRO同时定义！
 *
 * 需要：MBEDTLS_PLATFORM_TIME_ALT需要MBEDTLS_HAVE_TIME
 *
 * 取消注释宏以启用特定基础平台功能的替代实现
 */
//#定义MBEDTLS_PLATFORM_EXIT_ALT
//#定义MBEDTLS_PLATFORM_TIME_ALT
//#定义MBEDTLS_PLATFORM_FPRINTF_ALT
//#定义MBEDTLS_PLATFORM_PRINTF_ALT
//#定义MBEDTLS_PLATFORM_SNPRINTF_ALT
//#定义MBEDTLS_PLATFORM_VSNPRINTF_ALT
//#定义MBEDTLS_PLATFORM_NV_SEED_ALT
//#定义MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT

/**
 * \def MBEDTLS_DEPRECATED_WARNING
 *
 * 标记已弃用的函数，以便在使用时生成警告。在一个版本中弃用的函数通常在下一个版本中将被删除。通过确保代码不使用这些函数，您可以启用此功能来帮助您准备向新的主要版本的过渡。
 *
 * 这只适用于GCC和Clang。对于其他编译器，您可能需要使用MBEDTLS_DEPRECATED_REMOVED
 *
 * 取消注释以获取有关使用已弃用函数的警告。
 */
//#定义MBEDTLS_DEPRECATED_WARNING

/**
 * \def MBEDTLS_DEPRECATED_REMOVED（定义MBEDTLS_DEPRECATED已删除）
 *
 * 删除已弃用的函数，以便在使用时生成错误。在一个版本中弃用的函数通常在下一个版本中将被删除。通过确保代码不使用这些函数，您可以启用此功能来帮助您准备向新的主要版本的过渡。
 *
 * 取消注释以获取有关使用已弃用函数的错误。
 */
//#定义MBEDTLS_DEPRECATED_REMOVED

/**
 * \定义MBEDTLS_CHECK_PARAMS
 *
 * 此配置选项控制库是否验证传递给它的更多参数。
 *
 * 如果未定义此标志，则库仅在以下情况下尝试验证输入参数：（1）输入参数可能来自外部世界（如网络、文件系统等），或（2）不验证输入参数可能导致内部内存错误，如库控制的缓冲区溢出。另一方面，它不尝试验证其值完全由应用程序控制的参数（例如指针）。
 *
 * 定义此标志后，库还会尝试验证由应用程序完全控制的参数，如果应用程序代码完全正确且可信，则这些参数应始终有效。
 *
 * 例如，当函数接受指向可能包含不可信数据的缓冲区的指针作为输入，并且其文档中提到该指针不能为NULL时：
 * -仅当启用此选项时，才会检查指针是否为非NULL
 * -缓冲区的内容始终有效
 *
 * 定义此标志后，如果库函数接收到无效的参数，它将：
 * -调用宏MBEDTLS_PARAM_FAILED（），该宏默认扩展为对函数MBEDTLS_PARAM_FAILED（）的调用
 * -立即返回（带有特定的错误代码，除非函数返回void并且无法传递错误）。
 *
 * 定义此标志时，还需要：
 * -在库调用函数时，在应用程序中提供函数mbedtls_param_failed（）的定义（请参见platform_util.h了解其原型），但不提供默认定义，
 * -如果上述机制不够灵活，无法满足您的需要，请在下面提供宏MBEDTLS_PARAM_FAILED（）的不同定义。请参阅本文件后面的宏文档。
 *
 * 取消注释以启用应用程序控制参数的验证。
 */
//#定义MBEDTLS_CHECK_PARAMS

/* \}name SECTION:系统支持*/

/**
 * \name SECTION:mbed TLS功能支持
 *
 * 本节设置对启用的模块中需要或不需要的功能的支持\{
 */

/**
 * \定义MBEDTLS_TIMING_ALT
 *
 * 取消注释以提供您自己的mbedtls_timing_hardclock（）、mbedtls_timing_get_timer（）、embedtls_set_alarm（）和mbedtls_set/get_delay（）的替代实现
 *
 * 仅当启用了MBEDTLS_IMING_C时才有效。
 *
 * 您需要在编译时提供一个标题“timing_alt.h”和一个实现。
 */
//#定义MBEDTLS_TIMING_ALT

/**
 * \定义MBEDTLS_AES_ALT
 *
 * MBEDTLS_MODULE_NAME__ALT：取消对宏的注释，以允许mbed TLS使用对称加密、算术或哈希模块的替代核心实现（例如，特定于平台的程序集优化实现）。请记住，功能原型应该保持不变。
 *
 * 这将替换整个模块。如果只想替换其中一个函数，请使用MBEDTLS_FUNCTION_NAME__ALT标志之一。
 *
 * 示例：如果取消注释MBEDTLS_AES_ALT，mbed TLS将不再提供“struct MBEDTLS_AES_context”定义，并省略基函数声明和实现。“aes_alt.h”将包含在“aes.h”中，以包含新的函数定义。
 *
 * 取消注释宏以启用相应模块的替代实现。
 *
 * \警告MD2、MD4、MD5、ARC4、DES和SHA-1被认为是脆弱的，它们的使用构成了安全风险。如果可能的话，我们建议避免对它们的依赖，而是考虑更强的消息摘要和密码。
 *
 */
//#定义MBEDTLS_AES_ALT
//#定义MBEDTLS_ARC4_ALT
//#定义MBEDTLS_ARIA_ALT
//#定义MBEDTLS_BLOWFISH_ALT
//#定义MBEDTLS_CAMELLIA_ALT
//#定义MBEDTLS_CCM_ALT
//#定义MBEDTLS_CHACHA20_ALT
//#定义MBEDTLS_CHACHAPOLY_ALT
//#定义MBEDTLS_MAC_ALT
//#定义MBEDTLS_DES_ALT
//#定义MBEDTLS_DHM_ALT
//#定义MBEDTLS_ECJPAKE_ALT
//#定义MBEDTLS_GCM_ALT
//#定义MBEDTLS_NIST_KW_ALT
//#定义MBEDTLS_MD2_ALT
//#定义MBEDTLS_MD4_ALT
//#定义MBEDTLS_MD5_ALT
//#定义MBEDTLS_POLY1305_ALT
//#定义MBEDTLS_RIPEMD160_ALT
//#定义MBEDTLS_RSA_ALT
//#定义MBEDTLS_SHA1_ALT
//#定义MBEDTLS_SHA256_ALT
//#定义MBEDTLS_SHA512_ALT
//#定义MBEDTLS_XTEA_ALT

/*
 * 在替换椭圆曲线模块时，请考虑它是用两个.c文件实现的：
 *      -欧洲药典
 *      -ecp_曲线。c您可以像上述所有其他MBEDTLS_MODULE_NAME__ALT宏一样替换它们。唯一的区别是必须确保为两个.c文件提供功能。
 */
//#定义MBEDTLS_ECP_ALT

/**
 * \定义MBEDTLS_MD2_PROCESS_ALT
 *
 * MBEDTLS_FUNCTION_NAME__ALT：取消对宏的注释，以便让mbed TLS使用对称加密或哈希函数的替代核心实现。请记住，功能原型应该保持不变。
 *
 * 这仅替换一个函数。与MBEDTLS_MODULE_NAME__ALT标志不同，mbed TLS的头文件仍在使用。
 *
 * 示例：如果取消注释MBEDTLS_SHA256_PROCESS_ALT，mbed TLS将不再提供MBEDTLS_sha1_PROCESS（）函数，但它仍将提供其他函数（使用MBEDTLS_sha1_PROCESS（）函数）和MBEDTLS-sha1_context的定义，因此mbedtlss_sha1_PROCESS的实现必须与此定义兼容。
 *
 * \注意：由于签名更改，核心AES加密和解密例程当前分别命名为mbedtls_AES_internal_encrypt和mbedtls_AES_internal-decrypt。设置替代实现时，应重写这些函数，但包装函数mbedtls_aes_decrypt和mbedtls_aes_encrypt必须保持不变。
 *
 * \注意：如果使用AES_xxx_ALT宏，则建议同时设置MBEDTLS_AES_ROM_TABLES，以帮助链接器垃圾收集AES表。
 *
 * 取消注释宏以启用相应函数的替代实现。
 *
 * \警告MD2、MD4、MD5、DES和SHA-1被认为是脆弱的，它们的使用构成了安全风险。如果可能的话，我们建议避免对它们的依赖，而是考虑更强的消息摘要和密码。
 *
 */
//#定义MBEDTLS_MD2_PROCESS_ALT
//#定义MBEDTLS_MD4_PROCESS_ALT
//#定义MBEDTLS_MD5_PROCESS_ALT
//#定义MBEDTLS_RIPEMD160_PROCESS_ALT
//#定义MBEDTLS_SHA1_PROCESS_ALT
//#定义MBEDTLS_SHA256_PROCESS_ALT
//#定义MBEDTLS_SHA512_PROCESS_ALT
//#定义MBEDTLS_DES_SETKEY_ALT
//#定义MBEDTLS_DES_CRYPT_ECB_ALT
//#定义MBEDTLS_DES3_CRYPT_ECB_ALT
//#定义MBEDTLS_AES_SETKEY_ENC_ALT
//#定义MBEDTLS_AES_SETKEY_DEC_ALT
//#定义MBEDTLS_AES_ENCRYPT_ALT
//#定义MBEDTLS_AES_DECRYPT_ALT
//#定义MBEDTLS_ECDH_GEN_PUBLIC_ALT
//#定义MBEDTLS_ECDH_COMPUTE_SHARED_ALT
//#定义MBEDTLS_ECDSA_VERIFY_ALT
//#定义MBEDTLS_ECDSA_SIGN_ALT
//#定义MBEDTLS_ECDSA_GENKEY_ALT

/**
 * \定义MBEDTLS_ECP_INTERNAL_ALT
 *
 * 暴露椭圆曲线点模块内部接口的一部分。
 *
 * MBEDTLS_ECP__FUNCTION_NAME__ALT：取消对宏的注释，让mbed TLS使用椭圆曲线算法的替代核心实现。请记住，功能原型应该保持不变。
 *
 * 这部分取代了一个功能。与MBEDTLS_ECP_ALT标志不同，mbed TLS的头文件仍在使用。原始实现仍然存在，它用于替代方案不支持的组结构。
 *
 * 通过定义MBEDTLS_ECP_INTERNAL_ALT并实现以下函数，这些选项中的任何一个都可用：无符号字符MBEDTLS_INTERNAL_ECP_grp_able（const MBEDTLS_ECP_group grp）int MBEDTLS.INTERNAL_eccp_init（const embedtls_ECP_group）void MBEDTLS-INTERNAL_ec_free（const mbdtls_ECP _group group grp）如果替换函数实现给定组的算术运算，否则为0。在每个点操作之前和之后调用函数mbedtls_internal_ecp_init和mbedtls.internal_ecb_free，并提供了实现优化设置和拆卸指令的机会。
 *
 * 示例：如果取消注释MBEDTLS_ECP_INTERNAL_ALT和MBEDTLS-ECP_DOUBLE_JAC_ALT，则mbed TLS仍将提供ECP_DOUBLE_JAC函数，但如果组受支持，则将使用MBEDTLS_INTERNAL_ECP_DOUBLE_JAC（当MBEDTLS.INTERNAL_ec_grp_able函数将其作为参数接收时，返回1）。如果不支持该组，则使用原始实现。其他函数以及mbedtls_ecp_group和mbedtls-ecp_point的定义不会改变，因此mbedtls_internal_ecp_double_jac和mbedtls_internal-ecp_grp_able的实现必须与此定义兼容。
 *
 * 取消注释宏以启用相应函数的替代实现。
 */
/* 本节中的所有功能都需要*/
//#定义MBEDTLS_ECP_INTERNAL_ALT
/* 支持具有Jacobi表示的Weierstrass曲线*/
//#定义MBEDTLS_ECP_RANDOMIZE_JAC_ALT
//#定义MBEDTLS_ECP_ADD_MIXED_ALT
//#定义MBEDTLS_ECP_DOUBLE_JAC_ALT
//#定义MBEDTLS_ECP_NORMALIZE_JAC_MANY_ALT
//#定义MBEDTLS_ECP_NORMALIZE_JAC_ALT
/* 蒙哥马利算法支持曲线*/
//#定义MBEDTLS_ECP_DOUBLE_ADD_MXZ_ALT
//#定义MBEDTLS_ECP_RANDOMIZE_MXZ_ALT
//#定义MBEDTLS_ECP_NORMALIZE_MXZ_ALT

/**
 * \定义MBEDTLS_TEST_NULL_ENTROPY
 *
 * 允许在没有任何配置的熵源的情况下测试和使用mbed TLS。这允许在集成熵源之前在平台上使用库（例如，请参见MBEDTLS_ENTROPRY_HARDWARE_ALT或MBEDTLS_ENTROPRY_NV_SED开关）。
 *
 * 警告！此开关必须在生产版本中禁用，并且仅适用于开发。启用该开关将否定库提供的任何安全性。
 *
 * 需要MBEDTLS_ENTROPY_C、MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES
 *
 */
//#定义MBEDTLS_TEST_NULL_ENTROPRY

/**
 * \定义MBEDTLS_ENTROPY_HARDWARE_ALT
 *
 * 取消注释此宏以使mbed TLS使用您自己的硬件熵收集器实现。
 *
 * 您的函数必须名为\c mbedtls_hardware_poll（），具有与entropy_poll中声明的原型相同的原型。h、 并接受NULL作为第一个参数。
 *
 * 取消注释以使用您自己的硬件熵收集器。
 */
//#定义MBEDTLS_ENTROPY_HARDWARE_ALT

/**
 * \定义MBEDTLS_AES_ROM_TABLES
 *
 * 使用存储在ROM中的预计算AES表。
 *
 * 取消注释此宏以使用存储在ROM中的预计算AES表。注释此宏可在运行时在RAM中生成AES表。
 *
 * 权衡：使用预先计算的ROM表可减少约8kb的RAM使用量（如果使用了MBEDTLS_AES_FEWER_tables，则可减少约2kb），并减少执行第一次AES操作之前的初始化时间。其代价是额外使用约8kb的ROM（如果使用下面的MBEDTLS_AES_EWER_TABLES，则为约2kb），如果ROM访问速度比RAM访问速度慢，则性能可能会降低。
 *
 * 此选项独立于\c MBEDTLS_AES_EWER_TABLES。
 *
 */
//#定义MBEDTLS_AES_ROM_TABLES

/**
 * \定义MBEDTLS_AES_FEWER_TABLES
 *
 * AES表使用更少的ROM/RAM。
 *
 * 通过在操作过程中动态计算AES表的值（这些表是彼此的逐项旋转），取消对该宏的编码将从ROM/RAM中删除75%的AES表（取决于MBEDTLS_AES_ROM_tables的值）。
 *
 * 权衡：不执行此操作可将RAM/ROM占用空间减少约6kb，但代价是在运行时进行更多的算术运算。具体地说，必须将不同表中的4次访问与同一表中具有附加算术运算的4次存取进行比较。性能增益/损失取决于系统和内存细节。
 *
 * 此选项独立于\c MBEDTLS_AES_ROM_TABLES。
 *
 */
//#定义MBEDTLS_AES_FEWER_TABLES

/**
 * \定义MBEDTLS_AMELLIA_SSMALL_MEMORY
 *
 * Camellia实现使用更少的ROM（节省约768字节）。
 *
 * 取消注释此宏以减少Camellia的内存。
 */
//#定义MBEDTLS_CAMELLIA_SMALL_MEMORY

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
 * \定义MBEDTLS_CIPHER_NULL_CIPHER
 *
 * 启用NULL密码。警告：只有当你知道自己在做什么时才这样做。这允许在没有任何安全性的情况下进行加密或信道！
 *
 * 还需要MBEDTLS_ENABLEE_WEAK_CIPHERSUITES来启用以下密码套件：MBEDTLS_TLS_ECDH_ECDSA_WITH_NULL_SHA MBEDTL_TLS_ECDH_RSA_WITH_NULL-SHA MBEDLLS_TLS_ELS_ECDHE_ECDSA_WITH_2NULL_SHA MBEDTLSTLS_ECDHE_RSA_WITH-NULL_SHAMBEDTLS-TLS_CLS_ECDHE_PSK_WITH_NULL _SHA384 HE_PSK_WITH_NULL_SHA384具有完整性的256个MBEDTLS_TLS_DHE_PSK_WITH_NULL_SHA MBEDTLS_TLS_RSA_WITH_nul_SHA256个mbedt ls_TLS_RSA-WITH_NULL_MD5 MBEDTLS_RSA_PSK_wwith_NULL_SHA384个MBEDTLS _TLS_RSA sk_WITH-NULL_SHA ls_TLS_PSK_WITH_NULL_SHA
 *
 * 取消注释此宏以启用NULL密码和密码套件
 */
//#定义MBEDTLS_CIPHER_NULL_CIPHER

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
 * \定义MBEDTLS_ENABLE_WEAK_CIPHERSUITES
 *
 * 在SSL/TLS中启用弱密码套件。警告：只有当你知道自己在做什么时才这样做。这允许几乎没有安全性的信道！
 *
 * 这将启用以下密码套件：MBEDTLS_TLS_RSA_WITH_DES_CBC_SHA MBEDTLS_TLS_DHE_RSA_WITH_DES_BC_SHA
 *
 * 取消注释此宏以启用弱密码套件
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
//#定义MBEDTLS_ENABLE_WEAK_CIPHERSUITES

/**
 * \定义MBEDTLS_REMOVE_ARC4_CIPHERSUITES
 *
 * 默认情况下，在SSL/TLS中删除RC4密码套件。此标志从mbedtls_ssl_list_ciphersuites（）返回的默认列表中删除基于RC4的密码套件。但是，通过显式包含它们，仍然可以使用mbedtls_ssl_conf_cciphersuites（）启用（其中一些）。
 *
 * 默认情况下，取消注释此宏以删除RC4密码套件。
 */
#define MBEDTLS_REMOVE_ARC4_CIPHERSUITES

/**
 * \定义MBEDTLS_ECP_DP_SECP192R1_ENABLED
 *
 * MBEDTLS_ECP_XXXX_ENABLED：启用椭圆曲线模块中的特定曲线。默认情况下，启用所有支持的曲线。
 *
 * 注释宏以禁用曲线及其函数
 */
#define MBEDTLS_ECP_DP_SECP192R1_ENABLED
#define MBEDTLS_ECP_DP_SECP224R1_ENABLED
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
#define MBEDTLS_ECP_DP_SECP521R1_ENABLED
#define MBEDTLS_ECP_DP_SECP192K1_ENABLED
#define MBEDTLS_ECP_DP_SECP224K1_ENABLED
#define MBEDTLS_ECP_DP_SECP256K1_ENABLED
#define MBEDTLS_ECP_DP_BP256R1_ENABLED
#define MBEDTLS_ECP_DP_BP384R1_ENABLED
#define MBEDTLS_ECP_DP_BP512R1_ENABLED
#define MBEDTLS_ECP_DP_CURVE25519_ENABLED
#define MBEDTLS_ECP_DP_CURVE448_ENABLED

/**
 * \定义MBEDTLS_ECP_NIST_OPTIM
 *
 * 为每个NIST素数启用特定的“模p”例程。根据素数和架构，使相应曲线上的操作速度提高4到8倍。
 *
 * 注释此宏以禁用NIST曲线优化。
 */
#define MBEDTLS_ECP_NIST_OPTIM

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
 * \注意：此选项仅适用于椭圆曲线功能的默认软件实现。它与MBEDTLS_ECP_ALT、MBEDTLS_ECDH_XXX_ALT和MBEDTLS_ECDSA_XXX_ALT不兼容。
 */
//#定义MBEDTLS_ECP_RESTARTABLE

/**
 * \定义MBEDTLS_ECDSA_DETERMINISTIC
 *
 * 启用确定性ECDSA（RFC 6979）。标准ECDSA是“脆弱的”，因为在签名时缺乏熵可能会导致长期签名密钥的妥协。确定性变量可以避免这种情况。
 *
 * 需要：MBEDTLS_MAC_DRBG_C
 *
 * 注释此宏以禁用确定性ECDSA。
 */
#define MBEDTLS_ECDSA_DETERMINISTIC

/**
 * \定义MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
 *
 * 在SSL/TLS中启用基于PSK的密码套件模式。
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_PSK_WITH_ACE_256_GCM_SHA384 MBEDTLS_TLS_PSK-WITH_AAES_256_CBC_SHA384 EMBEDTLS_TSK_WSK_WITH-ACE_256_CBC _SHAMBEDTL_TLS_PSK_WITH_CAMELLIA_256_GBC_SHA284 MBEDTLC_TSK_WITH_CAMELLIA_2256_CBC_SHAD84 MBEDTLS-TLS_PSC_WITH_AES_128_GCM_SHAD256MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA MBEDTLS_TLS_PSK-WITH_cmellia_128_GCM_SHA256 MBEDTLS.TLS_PSK/WITH_cmellian_128_CBC _SHA256 mbdtls_TLS _PSK_wwith_3DES_EDE_CBC_shambedtls_ssk_WITH_RC4_128_SHA
 */
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED

/**
 * \定义MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED
 *
 * 在SSL/TLS中启用基于DHE-PSK的密码套件模式。
 *
 * 需要：MBEDTLS_DHM_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_DHE_PSK_WITH_ACE_256_GCM_SHA384 MBEDTLS_TLS_DHE_PSK_WICH_ACE_256-BC_SHA384 MBEDTLS_TLS_DHE_PSK_WITH_AES_256_CBC_SHA MBEDTLS-TLS_TLS_DLS_PH_PSK_WITH_CAMELLIA_256_GBC_SHA284 MBEDTL_TLS_DLS_PHE_PSK-WITH_CAMELLEA_256_CCM_SHA284 H_AES_128_CBC_SHA256MBEDTLS_TLS_DHE_PSK_WITH_AES_128_CBC_SHA MBEDTLS_dls_DHE_ssk_WITH_cmellia_128_GCM_SHA256 MBEDTLS_TLS_DHE-PSK_WITH_Cmellia_128 _CBC_SHA256 mbdtls_TLS _DHE_PSK _WITH_3DES_EDE_CBC_shar
 *
 * \警告使用DHE构成安全风险，因为无法验证自定义DH参数。如果可能，建议用户考虑使用其他密钥交换方法。见dhm。h了解更多详情。
 *
 */
#define MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED
 *
 * 在SSL/TLS中启用基于ECDHE-PSK的密码套件模式。
 *
 * 需要：MBEDTLS_ECDH_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384 MBEDTLS_TLS_ECDHE_PSK_WITH_AES_256-BC_SHA MBEDTL_TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC _SHA384 MBEDTLS_TLS_ECD HE_PSK-WITH_AES_128_CBC_SHAD256 MBEDTLSTLS_TLS_ECDHE_PSK _WITH_AE_128_CBC _SHA MBEDTLS_TLS-ECDHE_PSK_WITH_CAMELIA_128_CBC_SHA256MBEDTLS_TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA MBEDTLS_TLS_ECDHE _PSK-WITH_RC4_128_SHA
 */
#define MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED

/**
 * \定义MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED
 *
 * 在SSL/TLS中启用基于RSA-PSK的密码套件模式。
 *
 * 需要：MBEDTLS_RSA_C、MBEDTLS_PKCS1_V15、MBEDTLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_RSA_PSK_WITH_ACE_256_GCM_SHA384 MBEDTLS_TLS_RSE_PSK_WICH_ACE_256-BC_SHA384 EMBEDTLS_RLS_RSA_SK_WITH_AES_256_CBC_SHA MBEDTL_TLS_RSA_PSK_WITH-CAMELLIA256_GCM_SHAD84 MBEDTLS-TLS_RS_RSA_PSK _WITH_CAMELLIA256 _CBC_SHAD84 H_AES_128_CBC_SHA256MBEDTLS_TLS_RSA_PSK_WITH_AES_128_CBC_SHA MBEDTLS_TLS_RSA_ssk_WITH_cmellia_128_GCM_SHA256 MBEDTLS_RSA_prsk_WITH_Cmellia_128 _CBC_SHA256 mbdtls_TLS _RSA_PSK _WITH_3DES_EDE_CBC_shar MBEDTLS_RSA_PSK-WITH_RC4_128_SHA
 */
#define MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED

/**
 * \定义MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
 *
 * 在SSL/TLS中启用仅基于RSA的密码套件模式。
 *
 * 需要：MBEDTLS_RSA_C、MBEDTLS_PKCS1_V15、MBEDTLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_RSA_WITH_ACE_256_GCM_SHA384 MBEDTLS_TLS_RS_WITH_AES_256_CBC_SHA256 MBEDTL_TLS_RSA_WITH_AES_256_CBC_SHA MBEDTLS-TLS_RLS_WITH_ASE_256_CBC _SHA384MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA256 MBEDTLS_RSA-WITH_AES_1 28_CBC-SHA MBEDTLS_TLS_RSA/WITH_cmellia_128_GCM_SHA256 embedtls_TLS _RSA-wwith_cmellia 128_CBC_SHA MBEDTLS _TLS_RSA WITH_3DES_EDE_CBC_saha MBEDTLS_lsa-WITH_cc4_128_MD5
 */
#define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED

/**
 * \定义MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED
 *
 * 在SSL/TLS中启用基于DHE-RSA的密码套件模式。
 *
 * 需要：MBEDTLS_DHM_C、MBEDTLS_RSA_C、MBEDTLS_PKCS1_V15、MBEDDLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_DHE_RSA_WITH_ACE_256_GCM_SHA384 MBEDTLS_TLS_DHS_RSA_WIITH_AES_256_CBC_SHA256 MBEDTL_TLS_DHE_RSA_WITH_AES_2 56_CBC.SHA MBEDTLS-TLS_TLS_DHE_RS_WITH_CAMELLIA256_GCM_SHAR384 MBEDLLS_TLS_TLS-TH_DHE_RSA _WITH_CamELLIA256_CBC_SHAR256 MBEDLS_TLS_DHE _RSA_WITEH_CAMELLIA H_AES_128_GCM_SHA256MBEDTLS_TLS_DHE_RSA-WITH_AES_128_CBC_SHA256 MBEDTLS_TLS_DHE_RSA-WITH-AES_128_CBC_SHA MBEDTLS_dls_DHE-RSA-WITH_cmellia_128_GCM_SHA256 embedtls_TLS _DHE_RSA-WITH_camelia_128_CBC _SHA256
 *
 * \警告使用DHE构成安全风险，因为无法验证自定义DH参数。如果可能，建议用户考虑使用其他密钥交换方法。见dhm。h了解更多详情。
 *
 */
#define MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
 *
 * 在SSL/TLS中启用基于ECDHE-RSA的密码套件模式。
 *
 * 需要：MBEDTLS_ECDH_C、MBEDTLS_RSA_C、MBEDTLS _PKCS1_V15、MBEDTLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256-BC_SHA384 EMBEDTLS_ELS_ECDHE_RSA_WITH_AES_2 56_CBC_SHA MBEDTL_TLS_ECDHE-RSA_WITH-CAMELLIA_2256_GCM_SHAD84MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 MBEDTLS_TLS_ECDHE _RSA_WITH _AES_128 _CBC_SHA MBEDTLS_ecdthe_RSA_wwith_cmellia_128_GCM_SHA256 embedtls_TLS _ECDHE_RSA_WITH_cmellia 128_CBC_saha256 MBEDTLS _TLS_ecd he_RSA-WITH_3DES_EDE_CBC_shar
 */
#define MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
 *
 * 在SSL/TLS中启用基于ECDHE-ECDSA的密码套件模式。
 *
 * 需要：MBEDTLS_ECDH_C、MBEDTLS-ECDSA_C、MBEDTLS_X509_CRT_PARSE_C、，
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_2 56_CBC_SHA384 EMBEDTLS_ELS_ECDHE_ECDSE_WITH_AES_256_CBC_SHAD84 MBEDLS_TLS_ECDHE-ECDSA_WITH_CAMELLIA256_GCM_SHAD84 56个MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 MBEDTLS_ecdthe_ECDSA-WITH_AES_1 28_CBC-SHA MBEDTLS_TLS_ECDHE _ECDSA/WITH_cmellia_128_GCM_SHA256 embedtls_TLS _ECDHE-ECDSA-wwith_cmellia 128_CBC_SHA
 */
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED
 *
 * 在SSL/TLS中启用基于ECDH-ECDSA的密码套件模式。
 *
 * 需要：MBEDTLS_ECDH_C、MBEDTLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_ECDSA_WITH_RC4_128_SHA MBEDTLS_TLS_ECDH_2ECDSA_WITCH_3DES_EDE_CBC_SHA MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA MBEDTL_TLS_ECD H_ECDSA-WITH_AES_256_CBC_SHAMBEDTLSTLS_TLS-ECDH_ECDSA_WITH_AES_1 28_CBC-SHA256 MBEDLS_TLS.ECDH_ECDAS_WITH_AES_256 ITH_AES_128_GCM_SHA256MBEDTLS_TLS_ECDH_edcsa_WITH_AES_256_GCM_SHA384 MBEDTLS_ECDH-ecsa_WITH_camelia_128_CBC_SHA256 MBEDTLS_TLS_ECDH-edcsa_wwith_camelia_256_CBC_sha 384 MBEDTLS _ECDH-edcsa-WITH_camella_128_GCM_sha 256
 */
#define MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED

/**
 * \定义MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED
 *
 * 在SSL/TLS中启用基于ECDH-RSA的密码套件模式。
 *
 * 需要：MBEDTLS_ECDH_C、MBEDTLS_X509_CRT_PARSE_C
 *
 * 这将启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_RSA_WITH_RC4_128_SHA MBEDTLS_TLS_ECD_RSA_WITH_3DES_EDE_CBC_SHA MBEDTLS_TLS_ECDH_RSA_WITH_2AES_128_CBC_SHA MBEDTL_TLS_ECD H_RSA_ WITH_AES_256_CBC_SHAMBEDTLS-TLS_ELS_ECDH_RS A_WITH_AES_128-CBC_SHA256 MBEDLS_TLS-ECDH_RSAA_WITH_AES_226_CBC_SHAR上海256MBEDTLS_TLS_ECDH_ras_WITH_AES_256_GCM_SHA384 MBEDTLS_ECDH-rsas_WITH_camelia_128_CBC_SHA256 MBEDTLS_TLS_ECDH/rsas_wwith_camelia_256_CBC_sha 384 MBEDTLS _TLS_ecd h_ras-WITH_CAMELLIA_228_GCM_sha 256
 */
#define MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED

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
//#定义MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED

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
 * \定义MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES
 *
 * 不要添加默认熵源。这些是特定于平台的、基于mbedtls_timing_hardclock和HAVEGE的轮询函数。
 *
 * 这对于在应用程序中对添加的熵源进行更多控制非常有用。
 *
 * 取消注释此宏以防止加载默认熵函数。
 */
//#定义MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES

/**
 * \定义MBEDTLS_NO_PLATFORM_ENTROPY
 *
 * 不要使用内置的平台熵函数。如果您的平台不支持/dev/urandom或Windows CryptoAPI等标准，这将非常有用。
 *
 * 取消注释此宏以禁用内置平台熵函数。
 */
//#定义MBEDTLS_NO_PLATFORM_ENTROPY

/**
 * \定义MBEDTLS_ENTROPY_FORCE_SHA256
 *
 * 强制熵累加器使用SHA-256累加器，而不是默认的基于SHA-512的累加器（如果两者都可用）。
 *
 * 需要：MBEDTLS_SHA256_C
 *
 * 在32位系统上，SHA-256可以比SHA-512快得多。如果您有性能问题，请使用此选项。
 *
 * 仅当定义了MBEDTLS_SHA256_C和MBEDTL_SHA512_C时，此选项才有用。否则将使用可用的哈希模块。
 */
//#定义MBEDTLS_ENTROPY_FORCE_SHA256

/**
 * \定义MBEDTLS_ENTROPY_NV_SEED
 *
 * 启用基于非易失性（NV）种子文件的熵源。（同时启用平台层的NV种子读/写功能）
 *
 * 这对于没有可用的密码熵源（在硬件或内核中）的系统至关重要（如果不需要）。
 *
 * 需要：MBEDTLS_ENTROPY_C、MBEDTLS_PLATFORM_C
 *
 * \注：熵源使用的读/写函数是在平台层中确定的，可以在运行时和/或编译时根据使用的标志（MBEDTLS_platform_NV_SEED_）进行修改。
 *
 * \注意：如果您使用的默认实现函数使用常规fopen（）读取种子文件，请确保您创建的种子文件具有正确的名称（在MBEDTLS_PLATFORM_STD_NV_SEED_FILE中定义），并且大小至少为MBEDTLS_ENTROPY_BLOCK_SIZE字节，可以读取和写入，否则将出现熵源错误！默认实现将仅使用文件中的第一个MBEDTLS_ENTROPY_BLOCK_SIZE字节。
 *
 * \注意，熵收集器将在熵提供给外部源之前写入种子文件，以更新它。
 */
//#定义MBEDTLS_ENTROPY_NV_SEED

/* MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
 *
 * 启用对密钥所有者标识符进行编码的密钥标识符。
 *
 * 这仅在将库构建为多客户端服务的一部分时才有意义。激活此选项时，必须在所有希望支持的存储后端中提供mbedtls_key_owner_id_t类型的实现以及从mbedtls_svc_key_id_t到文件名的转换。
 *
 * 请注意，此选项仅供内部使用，可在不另行通知的情况下删除。
 */
//#定义MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER

/**
 * \定义MBEDTLS_MEMORY_DEBUG
 *
 * 启用缓冲区分配器内存问题的调试。自动打印（到stderr）有关内存分配问题的所有（致命）消息。启用已分配内存的“调试输出”功能。
 *
 * 需要：MBEDTLS_MEMORY_BUFFER_ALLOC_C
 *
 * 取消注释此宏，以便缓冲区分配器打印出错误消息。
 */
//#定义MBEDTLS_MEMORY_DEBUG

/**
 * \定义MBEDTLS_MEMORY_BACKTRACE
 *
 * 包括每个分配块的回溯信息。
 *
 * 需要：MBEDTLS_MEMORY_BUFFER_ALLOC_C GLIBC兼容backtrace（）和backtrace_symbols（）支持
 *
 * 取消注释此宏以包含回溯信息
 */
//#定义MBEDTLS_MEMORY_BACKTRACE

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
 * \定义MBEDTLS_PSA_CRYPTO_SPM
 *
 * 当定义MBEDTLS_PSA_CRYPTO_SPM时，代码是为SPM（安全分区管理器）集成而构建的，该集成将代码分为两个部分：NSPE（非安全进程环境）和SPE（安全过程环境）。
 *
 * 模块：library/psa_crypto。c需要：MBEDTLS_PSA_CRYPTO_c
 *
 */
//#定义MBEDTLS_PSA_CRYPTO_SPM

/**
 * \定义MBEDTLS_PSA_INJECT_ENTROPY
 *
 * 在首次启动时启用对熵注入的支持。在没有内置熵源（TRNG）的系统上需要此功能。具有内置熵源的系统当前不支持此功能。
 *
 * 需要：MBEDTLS_PSA_CRYPTO_STORAGE_C、MBEDTLS_ENTROPY_NV_SEED
 *
 */
//#定义MBEDTLS_PSA_INJECT_ENTROPY

/**
 * \定义MBEDTLS_RSA_NO_CRT
 *
 * 不要将中国剩余定理用于RSA私有运算。
 *
 * 取消注释此宏以禁用在RSA中使用CRT。
 *
 */
//#定义MBEDTLS_RSA_NO_CRT

/**
 * \定义MBEDTLS_SELF_TEST
 *
 * 启用检查功能（*_self_test）。
 */
#define MBEDTLS_SELF_TEST

/**
 * \定义MBEDTLS_SHA256_SMALLER
 *
 * 启用具有较低ROM占用空间但性能较低的SHA-256实现。
 *
 * 默认实现意味着性能和大小之间的合理妥协。该版本以牺牲性能为代价，更积极地优化尺寸。例如，在Cortex-M4上，它将mbedtls_sha256_process（）的大小从约2KB减小到约0.5KB，性能命中率约为30%。
 *
 * 取消注释以启用SHA256的较小实现。
 */
//#定义MBEDTLS_SHA256_SMALLER

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
 * \定义MBEDTLS_SL_ASYNC_PRIVATE
 *
 * 在SSL中启用异步外部私钥操作。这允许您配置SSL连接以调用外部加密模块来执行私钥操作，而不是在库中执行操作。
 *
 */
//#定义MBEDTLS_SL_ASYNC_PRIVATE

/**
 * \定义MBEDTLS_SL_DEBUG_ALL
 *
 * 为所有问题启用SSL模块中的调试消息。某些地方禁用了调试消息，以防止由于（不平衡的）调试函数调用而造成的定时攻击。
 *
 * 如果需要所有错误报告，则应在调试期间启用此功能，但也应为生产服务器删除此功能。
 *
 * 取消对此宏的注释，以报告有关引入计时侧通道的错误的所有调试消息。
 *
 */
//#定义MBEDTLS_SL_DEBUG_ALL

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
#define MBEDTLS_SSL_ENCRYPT_THEN_MAC

/** \定义MBEDTLS_SL_EXTENDED_MASTER_SECRET
 *
 * 启用对扩展主密钥（即会话哈希）的支持（draft-ietf-tls-Session-Hash-02）。
 *
 * 这被介绍为对三重握手系列攻击的“正确修复”，但建议始终使用它（即使您禁用重新协商），因为它实际上修复了原始SSL/TLS设计中的一个更基本的问题，并且具有超出三重握手的含义。
 *
 * 需要：MBEDTLS_SL_PROTO_TLS1或MBEDTLS_SL_PROTO-TLS1_1或MBETTLS_SLPROTO_TLS1_2
 *
 * 注释此宏以禁用对扩展主密钥的支持。
 */
#define MBEDTLS_SSL_EXTENDED_MASTER_SECRET

/**
 * \定义MBEDTLS_SL_FALLBACK_SCSV
 *
 * 启用对FALLBACK_SCSV（draft-ietf-tls-downstance-csv-00）的支持。
 *
 * 对于服务器，建议始终启用此选项，除非您只支持一个版本的TLS，或者确定您的客户端都没有实现回退策略。
 *
 * 对于客户端，只有在使用回退策略时才需要此选项，这在一开始是不建议的，除非您绝对需要它与有问题（版本不兼容）的服务器进行互操作。
 *
 * 注释此宏以禁用对FALLBACK_SCSV的支持
 */
#define MBEDTLS_SSL_FALLBACK_SCSV

/**
 * \定义MBEDTLS_SL_HW_RECORD_ACCEL
 *
 * 在SSL模块中启用挂钩功能，以实现单个记录的硬件加速。
 *
 * 取消注释此宏以启用挂钩函数。
 */
//#定义MBEDTLS_SL_HW_RECORD_ACCEL

/**
 * \定义MBEDTLS_SL_CBC_RECORD_SPLITTING
 *
 * 在SSLv3和TLS 1.0中为CBC模式启用1/n-1记录拆分。
 *
 * 这是对BEAST攻击的一种对策，与发送0长度记录相比，这也将互操作性问题的风险降至最低。
 *
 * 注释此宏以禁用1/n-1记录拆分。
 */
#define MBEDTLS_SSL_CBC_RECORD_SPLITTING

/**
 * \定义MBEDTLS_SL_RENEGOTIATION
 *
 * 启用TLS重新协商支持。
 *
 * 重新协商的两个主要用途是（1）长时间连接上的刷新密钥和（2）初始握手后的客户端身份验证。如果您不需要重新协商，那么最好禁用它，因为它过去与安全问题有关，很容易被误用/误解。
 *
 * 对此进行注释以禁用对重新协商的支持。
 *
 * \注意：即使禁用此选项，客户端和服务器都知道用于防止SSL重新协商攻击的重新协商指示扩展（RFC 5746第1节）。（有关此扩展的配置，请参见\c mbedtls_ssl_conf_legacy_renegotiation）。
 *
 */
#define MBEDTLS_SSL_RENEGOTIATION

/**
 * \定义MBEDTLS_SL_SRV_SUPPORT_SSLV2_CLIENT_HELLO
 *
 * 支持接收和解析SSL服务器模块（MBEDTLS_SL_SRV_C）的SSLv2客户端Hello消息。
 *
 * 取消注释此宏以启用对SSLv2客户端Hello消息的支持。
 */
//#定义MBEDTLS_SL_SRV_SUPPORT_SSLV2_CLIENT_HELLO

/**
 * \定义MBEDTLS_SL_SRV_RESPECT_CLIENT_PREFERENCE
 *
 * 在SSL服务器模块（MBEDTLS_SL_SRV_C）中，根据客户的偏好而不是我们的偏好选择密码套件。
 *
 * 取消注释此宏以尊重客户端的密码套件顺序
 */
//#定义MBEDTLS_SL_SRV_RESPECT_CLIENT_PREFERENCE

/**
 * \定义MBEDTLS_SL_MAX_FRAGMENT_LENGTH
 *
 * 启用SSL中对RFC 6066 max_fragment_length扩展的支持。
 *
 * 注释此宏以禁用对max_fragment_length扩展的支持
 */
#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH

/**
 * \定义MBEDTLS_SL_PROTO_SSL3
 *
 * 启用对SSL 3.0的支持。
 *
 * 需要：MBEDTLS_MD5_C MBEDTLS_SHA1_C
 *
 * 注释此宏以禁用对SSL 3.0的支持
 */
//#定义MBEDTLS_SL_PROTO_SSL3

/**
 * \定义MBEDTLS_SL_PROTO_TLS1
 *
 * 启用对TLS 1.0的支持。
 *
 * 需要：MBEDTLS_MD5_C MBEDTLS_SHA1_C
 *
 * 注释此宏以禁用对TLS 1.0的支持
 */
#define MBEDTLS_SSL_PROTO_TLS1

/**
 * \定义MBEDTLS_SL_PROTO_TLS1_1
 *
 * 启用对TLS 1.1的支持（如果启用了DTLS，则启用DTLS 1.0）。
 *
 * 需要：MBEDTLS_MD5_C MBEDTLS_SHA1_C
 *
 * 注释此宏以禁用对TLS 1.1/DTLS 1.0的支持
 */
#define MBEDTLS_SSL_PROTO_TLS1_1

/**
 * \定义MBEDTLS_SL_PROTO_TLS1_2
 *
 * 启用TLS 1.2支持（如果启用了DTLS，则启用DTLS 1.2）。
 *
 * 需要：MBEDTLS_SHA1_C或MBEDTL_SHA256_C或MBEDLLS_SHA512_C（取决于密码套件）
 *
 * 注释此宏以禁用对TLS 1.2/DTLS 1.2的支持
 */
#define MBEDTLS_SSL_PROTO_TLS1_2

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
#define MBEDTLS_SSL_PROTO_DTLS

/**
 * \定义MBEDTLS_SL_ALPN
 *
 * 启用对RFC 7301应用层协议协商的支持。
 *
 * 注释此宏以禁用对ALPN的支持。
 */
#define MBEDTLS_SSL_ALPN

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
#define MBEDTLS_SSL_DTLS_ANTI_REPLAY

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
#define MBEDTLS_SSL_DTLS_HELLO_VERIFY

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
#define MBEDTLS_SSL_DTLS_CLIENT_PORT_REUSE

/**
 * \定义MBEDTLS_SL_DTLS_BADMAC_LIMIT
 *
 * 启用对具有坏MAC的记录的限制支持。
 *
 * 请参见mbedtls_ssl_conf_dtls_baadmac_limit（）。
 *
 * 需要：MBEDTLS_SL_PROTO_DTLS
 */
#define MBEDTLS_SSL_DTLS_BADMAC_LIMIT

/**
 * \定义MBEDTLS_SL_SESSION_TICKETS
 *
 * 启用SSL中对RFC 5077会话票证的支持。客户端为会话票证提供了全面支持（但会话存储的维护仍然由应用程序负责）。在服务器端，您还需要提供写和解析票据的回调，包括经过身份验证的加密和密钥管理。MBEDTLS_SL_TICKET_C提供了示例回调。
 *
 * 注释此宏以禁用对SSL会话票证的支持
 */
#define MBEDTLS_SSL_SESSION_TICKETS

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
 * \定义MBEDTLS_SL_TRUNCATED_HMAC_COMPAT
 *
 * 回退到旧的（2.7之前的版本），截断HMAC扩展的不一致实现，也截断HMAC密钥。请注意，此选项仅适用于短暂的升级期，可能会在库的未来版本中删除。
 *
 * \警告旧的实现不兼容，并且存在安全漏洞（对用于单个不间断连接的HMAC密钥进行2^80暴力攻击）。只有当（1）为了节省带宽，必须使用截断的HMAC，以及（2）对等方是一个尚未使用固定实现的Mbed TLS堆栈（2.7之前）时，才应暂时启用此功能。
 *
 * \已弃用此选项已弃用，可能会在未来版本的Mbed TLS中删除。
 *
 * 取消注释以回退到旧的、不兼容的截断HMAC实现。
 *
 * 需要：MBEDTLS_SL_TRUNCATED_HMAC
 */
//#定义MBEDTLS_SL_TRUNCATED_HMAC_COMPAT

/**
 * \定义MBEDTLS_THREADING_ALT
 *
 * 提供您自己的替代线程实现。
 *
 * 需要：MBEDTLS_THREADING_C
 *
 * 取消对此的注释，以允许您自己的替代线程实现。
 */
//#定义MBEDTLS_THREADING_ALT

/**
 * \定义MBEDTLS_THREADING_PTHREAD
 *
 * 为线程层启用pthread包装层。
 *
 * 需要：MBEDTLS_THREADING_C
 *
 * 取消注释以启用pthread互斥锁。
 */
//#定义MBEDTLS_THREADING_PTHREAD

/**
 * \定义MBEDTLS_USE_PSA_CRYPTO
 *
 * 使X.509和TLS库使用PSA进行加密操作，请参阅#MBEDTLS_PSA_CRYPTO_C。
 *
 * 注意：此选项仍在进行中，完整的X.509和TLS模块尚未涵盖，但尚未移植到PSA的部分仍将照常工作，因此启用此选项不会破坏向后兼容性。
 *
 * \警告支持PSA仍然是一个实验特性。在删除此警告之前，依赖于此选项的任何公共API都可能随时更改。
 *
 * 需要：MBEDTLS_PSA_CRYPTO_C。
 */
//#定义MBEDTLS_USE_PSA_CRYPTO

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
 * \定义MBEDTLS_X509_ALLOW_EXTENSIONS_NON_V3
 *
 * 如果设置，X509解析器在解析X509证书并遇到v1或v2证书中的扩展时不会中断。
 *
 * 取消注释以防止错误。
 */
//#定义MBEDTLS_X509_ALLOW_EXTENSIONS_NON_V3

/**
 * \定义MBEDTLS_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION
 *
 * 如果设置，X509解析器在解析X509证书并遇到未知的关键扩展时不会中断。
 *
 * \警告根据您的PKI使用情况，启用此功能可能存在安全风险！
 *
 * 取消注释以防止错误。
 */
//#定义MBEDTLS_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION

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
#define MBEDTLS_X509_CHECK_KEY_USAGE

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
#define MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE

/**
 * \定义MBEDTLS_X509_RSASSA_PSS_SUPPORT
 *
 * 启用使用RSASSA-PSS（又名PKCS#1 v2.1）签名的X.509证书、CRL和CSRS的解析和验证。
 *
 * 注释此宏以禁止在证书中使用RSASSA-PSS。
 */
#define MBEDTLS_X509_RSASSA_PSS_SUPPORT

/**
 * \定义MBEDTLS_ZLIB_SUPPORT
 *
 * 如果已设置，SSL/TLS模块将使用ZLIB支持数据包数据的压缩和解压缩。
 *
 * \警告TLS级别压缩可能会降低安全性！例如，请参见CRIME攻击。在启用此选项之前，您应该仔细检查CRIME或类似漏洞是否适用于您的用例。
 *
 * \注意：当前压缩不能用于DTLS。
 *
 * \已弃用此功能已弃用，将在库的下一个主要版本中删除。
 *
 * 用于：library/ssl_tls。c库/ssl_cli。c库/ssl_srv.c
 *
 * 此功能要求提供zlib库和标头。
 *
 * 取消注释以启用ZLIB
 */
//#定义MBEDTLS_ZLIB_SUPPORT
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
 * 模块：library/aesni。c调用方：library/aes.c
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
 * 模块：library/aes。c调用方：库/密码。c库/pem。c库/ctr_drbg.c
 *
 * 此模块启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA MBEDTLS_TLS_ECDS_WITH_AES_256_CBC_SHA MBEDTL_TLS_ECDH_RSA_WITH_AES_128 _CBC_SHAMBEDTLS-TLS_ELS_ECDH_LSA_WITH_AES_128_CBC_SHAN MBEDTLSTLS_TLS_ECD H_ECDSA-WITH_AES_228_CBC-SHA256 MBEDLS_TLS-ECDH_ECDSA.WITH_AES_2 56_CBC_SHA384MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256 MBEDTLS_ECDH _RSA_wwith_AES_256_CBC_sha 384 MBEDTLS_TLS_ECDH-ECDSA _WITH_AES _128_GCM_SHA256 mbdtls_TLS _ECDH_edcdsa _wwith_AES _256_GCM_sha 384 mbdtls_esdh_RSA-WITH_AES_228_GCM-SHA256使用256厘米的沙384MBEDTLS_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384 MBEDTLS_ECDHE_ECDSA_WITH-AES_256_CBC_SHA384 mbdtls_TLS _ECDHE_RSA-WITH_AES_2 56_CBC-SHA384 mbedt ls_TLS-DHE_rsawith_AES_2256_CBC_SHA 256 MBEDTLS-ECDHE _ECDSA-WITH-AES_2 56_CBC_SHA具有128个字符的字符256带ES_128_GCM_SHA256 MBEDTLS_TLS_DHE_RSA_WITH_AES_128_GCM_sha256mbedtls_ECDHE_ECDSA_WITH-AES_128_CBC_SHA256 embedtls_TLS _ECDHE_RSA-WITH_AES_128_CBC _SHA256 mbdtls_DHE_RSA-WITH-AES_128_CBC_sha256mbdtls_tles_ECDHE_SHA256 ls_DHE_RSA_WITH_AES_128_CBC_SHAMBEDTLS_TLS_DHE_PSK_WITH_AES_256_GCM_SHA384 MBEDTLS_TLS_ECDHE_PSK-WITH_AES_2 56_CBC_SHA384 mbdtls_TLS _DHE_PSK _WITH_AES _256_CBC-SHA384 mbedt ls_TLS_ECDHE _PSK-wwith_AES_256-CBC_SHA384 MBEDTLS _TLS_ecd he_PSK/WITH_AES_128_GCM_SHA 256 MBEDTLS_ecd he _PSK_wwith_AES_128 mbc_SHA256 MBEDTLS _ecd he-PSK带ES_128_CBC_SHA256 MBEDTLS_TLS_ECDHE_PSK带ES_128 _CBC_SHAMBEDTLS_TLS_DHE_PSK_WITH_AES_128_CBC_SHA MBEDTLS_TLS_RSA-WITH_AES_256_GCM_SHA384 MBEDTLS_nls_RSA_WITH_AES _256_CBC_SHA256 MBEDTLS_RSA/WITH_AES_2 56_CBC-SHA MBEDTLS _TLS_rsaw ith_AES_1 28_GCM_SHA 256 MBEDTLS _RSA-wwith_AES_128 MBEDTLS_SHA256 embedtls_TLS _RSA_wwith_AES_228_CBC-SHA256 mbeds_TLS_RSA ls_RSA_PSK_WITH_AES_256_CBC_SHA384MBEDTLS_TLS_RSA_PSK_WITH_AES_256_CBC_SHA MBEDTLS_TLS_RSA-PSK_WITH-AES_128_GCM_SHA256 MBEDTLS_RSA_ssk_WITH_AES_128_CBC_SHA256 mbdtls_TLS _RSA_PSK _WITH_AES _128_CBC _SHA mbedt ls_TLS_PSK_wwith-AES_256_GCM_SHA 384 MBEDTLS_SHA384 MBEDTLS _TLS_ssk_wwith_AES_128_GCM_sha128 MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA256MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA
 *
 * PEM_PARSE使用AES对加密密钥进行解密。
 */
#define MBEDTLS_AES_C

/**
 * \定义MBEDTLS_ARC4_C
 *
 * 启用ARCFOUR流密码。
 *
 * 模块：library/arc4.c调用方：library/cypher.c
 *
 * 此模块启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_ECDSA_WITH_RC4_128_SHA MBEDTLS_TLS_ECDS_RSA_WITH_RC4_128 _SHA MBEDTLS_TLS_ECDHE_ECDSA_WITH_2RC4_128_SHA MBEDLS_TLS-ECDHE_RSA_WITH-RC4_128.SHA MBEDLLS_TLS_ECTHE_PSK_WITH_RC4_128_SHA H_RC4_128_MD5MBEDTLS_TLS_RSA_PSK_WITH_RC4_128_SHA MBEDTLS_TLS_PSK_wwith_RC4_128 _SHA
 *
 * \警告ARC4被认为是弱密码，其使用构成安全风险。如果可能的话，我们建议避免对它的依赖，而是考虑更强的密码。
 *
 */
#define MBEDTLS_ARC4_C

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
 * 模块：library/asn1write。c调用方：library/edsa。c库/pkwrite。c库/x509_create。c库/x509write_crt。c库/x509 write_csr.c
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
 * 模块：library/bignum。c呼叫者：library/dhm。c库/ecp。c库/edsa。c库/rsa。c库/rsa_internal。c库/ssl_tls.c
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
#define MBEDTLS_BLOWFISH_C

/**
 * \定义MBEDTLS_CAMELLIA_C
 *
 * 启用Camellia分组密码。
 *
 * 模块：图书馆/茶花。c调用方：library/cypher.c
 *
 * 此模块启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256 MBEDTLS_TLS_ECDS_ECDSA_WITH_CAMELLEA_256_CBC_SHAD84 MBEDTL_TLS_ECDH_RSA_WITH_CAMELLAA_128_CBC _SHA256 MBEDTLS_TLS_ECD H_RSA_ WITH_CAMELIA_256_CBC _SHAD84MBEDTLS_TLS_ECDH_RSA_WITH_camelia_128_GCM_SHA256 MBEDTLS_ECDH _RSA_wwith_camelia_256_GCM_sha 384 MBEDTLS_TLS_ECDHE_ECDSA-WITH_CAMELLIA_256_GCM-SHA384 MBEDTLS _ECDHE_RSA-WITH-CAMELLIA_256_GCM_saha384 mbedtles_TLS_ecd he_RSA_WITH _camelia_2 56_GCM_SHA384 bc_SHA384年带梅利亚_256_CBC_SHA256 MBEDTLS_TLS_DHE_RSA_WITH_camelia_256_CBC _SHA256个MBEDTLS_ECDHE_ECDSA_WITH-camelia_128_GCM_SHA256 MBdtls_TLS _ECDHE_RSA-WITH_CAMELLIA_128_GCM-SHA256个_夏256MBEDTLS_TLS_DHE_rsawith_camelia_128_CBC_SHA256 MBEDTLS_TLS_DHE_ssawith_cmellia_128_CBC_SHA384 MBEDTLS_ECDHE_pskwith_CAMELLIA_256_GCM_SHA384 mbdtls_TLS _DHE_pskWith_camelia_256_CBC_SHA 384 MBEDTLS _TLS_DHE _sskwith_cmellian_128_CBC _SHA384 ls_TLS_ECDHE_PSK_WITH_camelia_128_CBC_SHA256MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384 MBEDTLS_TLS_RSA-WITH_camelia_256_CBC_SHA256 MBEDTLS_RSA/WITH_camella_256_CBC_SHA MBEDTLS_lsa_WITH-CAMELLIA_128_GCM_SHA 256 MBEDTLS _TLS_RSA WITH_camelia_128_CBC_SHA 256 embedtls_TLS _RSA-wwith_camella_128_CBC_SHA256 _CBC_SHA384MBEDTLS_TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256 MBEDTLS_TLS_RSA_ssk_WITH_CAMELLIA_228_CBC_SHA256 mbdtls_t尔斯_PSK_wwith_camellion_256_GCM_sha 384 MBEDTLS_ssk_wwith_Camellion_128_GCM _SHA256
 */
#define MBEDTLS_CAMELLIA_C

/**
 * \定义MBEDTLS_ARIA_C
 *
 * 启用ARIA分组密码。
 *
 * 模块：library/aria。c调用方：library/cypher.c
 *
 * 此模块启用以下密码套件（如果还启用了其他必要条件）：
 *
 *      MBEDTLS_TLS_RSA_WITH_ARIA_128_CBC_SHA256 MBEDTLS_TLS_RSA_WITH_ARIA_256_CBC_SHA384 MBEDTLS_TLS_DHE_RSA_WITH_ARIA_128_CBC_SHA256 MBEDTLS_TLS_DHE_RSA_WITH_ARIA_256_CBC_SHA384 MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_128_CBC_SHA256 MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_256_CBC_SHA384 MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_128_CBC_SHA256 MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_256_CBC_SHA384 MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_128_CBC_SHA256 MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_256_CBC_SHA384 MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_128_CBC_SHA256 MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_256_CBC_SHA384 MBEDTLS_TLS_RSA_WITH_ARIA_128_GCM_SHA256 MBEDTLS_TLS_RSA_WITH_ARIA_256_GCM_SHA384 MBEDTLS_TLS_DHE_RSA_WITH_ARIA_128_GCM_SHA256 MBEDTLS_TLS_DHE_RSA_WITH_ARIA_256_GCM_SHA384 MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_128_GCM_SHA256 MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_256_GCM_SHA384 MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_128_GCM_SHA256 MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_256_GCM_SHA384 MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_128_GCM_SHA256 MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_256_GCM_SHA384 MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_128_GCM_SHA256 MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_256_GCM_SHA384 MBEDTLS_TLS_PSK_WITH_ARIA_128_CBC_SHA256 MBEDTLS_TLS_PSK_WITH_ARIA_256_CBC_SHA384 MBEDTLS_TLS_DHE_PSK_WITH_ARIA_128_CBC_SHA256 MBEDTLS_TLS_DHE_PSK_WITH_ARIA_256_CBC_SHA384 MBEDTLS_TLS_RSA_PSK_WITH_ARIA_128_CBC_SHA256 MBEDTLS_TLS_RSA_PSK_WITH_ARIA_256_CBC_SHA384 MBEDTLS_TLS_PSK_WITH_ARIA_128_GCM_SHA256 MBEDTLS_TLS_PSK_WITH_ARIA_256_GCM_SHA384 MBEDTLS_TLS_DHE_PSK_WITH_ARIA_128_GCM_SHA256 MBEDTLS_TLS_DHE_PSK_WITH_ARIA_256_GCM_SHA384 MBEDTLS_TLS_RSA_PSK_WITH_ARIA_128_GCM_SHA256 MBEDTLS_TLS_RSA_PSK_WITH_ARIA_256_GCM_SHA384 MBEDTLS_TLS_ECDHE_PSK_WITH_ARIA_128_CBC_SHA256 MBEDTLS_TLS_ECDHE_PSK_WITH_ARIA_256_CBC_SHA384
 */
//#定义MBEDTLS_ARIA_C

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
#define MBEDTLS_CCM_C

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
#define MBEDTLS_CHACHA20_C

/**
 * \定义MBEDTLS_CHACHAPOLY_C
 *
 * 启用ChaCha20-Poly1305 AEAD算法。
 *
 * 模块：library/cachapaly.c
 *
 * 此模块需要：MBEDTLS_CHACHA20_C、MBEDTLS_POLY1305_C
 */
#define MBEDTLS_CHACHAPOLY_C

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
 * \定义MBEDTLS_MAC_C
 *
 * 为分组密码启用CMAC（基于密码的消息验证码）模式。
 *
 * 模块：library/cmac.c
 *
 * 需要：MBEDTLS_AES_C或MBEDTLS_DES_C
 *
 */
#define MBEDTLS_CMAC_C

/**
 * \定义MBEDTLS_CTR_DRBG_C
 *
 * 启用基于CTR_DRBG AES的随机生成器。默认情况下，CTR_DRBG生成器使用AES-256。要改用AES-128，请启用下面的MBEDTLS_CTR_DRBG_use_128_BIT_KEY。
 *
 * 模块：library/ctr_drbg。c呼叫者：
 *
 * 需要：MBEDTLS_AES_C
 *
 * 此模块提供CTR_DRBG AES随机数生成器。
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
#define MBEDTLS_DEBUG_C

/**
 * \定义MBEDTLS_DES_C
 *
 * 启用DES分组密码。
 *
 * 模块：library/des。c调用方：library/pem。c库/密码.c
 *
 * 此模块启用以下密码套件（如果还启用了其他必要条件）：MBEDTLS_TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA MBEDTLS_TLS_ECDH_2RSA_WITH_3DES-EDE_CBC_SHA MBEDLLS_TLS_ECTHE_ECDSA_WITH_23DES_EDE _CBC_SHAMBEDTL_TLS_ECDHE_RSA_WITH-3DES_EBC_SHA HE_PSK_WITH_3DES_EDE_CBC_SHAMBEDTLS_TLS_RSA_WITH_3DES_EDE_CBC_SHA MBEDTLS_TLS_RSA_PSK_WITH_3DES _EDE_CBC _SHA
 *
 * PEM_PARSE使用DES/3DES对加密密钥进行解密。
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
#define MBEDTLS_DES_C

/**
 * \定义MBEDTLS_DHM_C
 *
 * 启用Diffie-Hellman-Merkle模块。
 *
 * 模块：library/dhm。c呼叫者：library/ssl_cli。c库/ssl_srv.c
 *
 * 该模块用于以下密钥交换：DHE-RSA、DHE-PSK
 *
 * \警告使用DHE构成安全风险，因为无法验证自定义DH参数。如果可能，建议用户考虑使用其他密钥交换方法。见dhm。h了解更多详情。
 *
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
#define MBEDTLS_ECDH_C

/**
 * \定义MBEDTLS_ECDSA_C
 *
 * 启用椭圆曲线DSA库。
 *
 * 模块：library/edsa。c呼叫者：
 *
 * 该模块用于以下密钥交换：ECDHE-ECDSA
 *
 * 需要：MBEDTLS_ECP_C、MBEDTLS_ASN1_WRITE-C、MBEDTLS_ASN1_PARSE_C
 */
#define MBEDTLS_ECDSA_C

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
//#定义MBEDTLS_ECJPAKE_C

/**
 * \定义MBEDTLS_ECP_C
 *
 * 启用GF（p）库上的椭圆曲线。
 *
 * 模块：library/ecp。c调用方：library/edh。c库/edsa。c库/ecjpake.c
 *
 * 需要：MBEDTLS_BIGNUM_C和至少一个MBEDTL_ECP_DP_XXX_ENABLED
 */
#define MBEDTLS_ECP_C

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
 * 启用AES的伽罗瓦/计数器模式（GCM）。
 *
 * 模块：library/gcm.c
 *
 * 需要：MBEDTLS_AES_C或MBEDTLS_CAMELLIA_C
 *
 * 如果还启用了其他必要条件，则该模块启用AES-GCM和CAMELLIA-GCM密码套件。
 */
#define MBEDTLS_GCM_C

/**
 * \定义MBEDTLS_HAVEGE_C
 *
 * 启用HAVEGE随机生成器。
 *
 * 警告：HAVEGE随机生成器不适用于虚拟化环境
 *
 * 警告：HAVEGE随机生成器取决于时间和特定的处理器特性。因此，不建议将HAVEGE用作应用程序的主要随机生成器或主要熵池输入。作为熵池的辅助输入，它可以添加它提供的（有限的）额外熵。
 *
 * 模块：图书馆/图书馆。c呼叫者：
 *
 * 需要：MBEDTLS_TIMING_C
 *
 * 取消注释以启用HAVEGE随机生成器。
 */
//#定义MBEDTLS_HAVEGE_C

/**
 * \定义MBEDTLS_HKDF_C
 *
 * 启用HKDF算法（RFC 5869）。
 *
 * 模块：library/hkdf。c呼叫者：
 *
 * 需要：MBEDTLS_MD_C
 *
 * 该模块增加了对基于哈希消息认证码（HMAC）的密钥派生函数（HKDF）的支持。
 */
#define MBEDTLS_HKDF_C

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
 * \定义MBEDTLS_NIST_KW_C
 *
 * 按照NIST SP 800-38F的定义，为128位分组密码启用密钥包装模式。仅支持KW和KWP模式。目前，NIST只批准AES。
 *
 * 模块：library/nist_kw.c
 *
 * 需要：MBEDTLS_AES_C和MBEDTLS_CIPHER_C
 */
//#定义MBEDTLS_NIST_KW_C

/**
 * \定义MBEDTLS_MD_C
 *
 * 启用通用消息摘要层。
 *
 * 模块：library/md。c呼叫者：
 *
 * 取消注释以启用通用消息摘要包装器。
 */
#define MBEDTLS_MD_C

/**
 * \定义MBEDTLS_MD2_C
 *
 * 启用MD2哈希算法。
 *
 * 模块：library/md2.c调用方：
 *
 * 取消注释以启用对（罕见）MD2签名的X.509证书的支持。
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。如果可能的话，我们建议避免对它的依赖，而是考虑更强大的消息摘要。
 *
 */
//#定义MBEDTLS_MD2_C

/**
 * \定义MBEDTLS_MD4_C
 *
 * 启用MD4哈希算法。
 *
 * 模块：library/md4.c调用方：
 *
 * 取消注释以启用对（罕见）MD4签名的X.509证书的支持。
 *
 * \警告MD4被认为是弱消息摘要，其使用构成安全风险。如果可能的话，我们建议避免对它的依赖，而是考虑更强大的消息摘要。
 *
 */
//#定义MBEDTLS_MD4_C

/**
 * \定义MBEDTLS_MD5_C
 *
 * 启用MD5哈希算法。
 *
 * 模块：library/md5.c调用方：library.md。c库/pem。c库/ssl_tls.c
 *
 * 根据握手参数，SSL/TLS版本1.1和TLS 1.2都需要此模块。此外，它还用于检查MD5签名证书，以及在解密PEM编码的加密密钥时用于PBKDF1。
 *
 * \警告MD5被认为是一个弱消息摘要，其使用构成了安全风险。如果可能的话，我们建议避免对它的依赖，而是考虑更强大的消息摘要。
 *
 */
#define MBEDTLS_MD5_C

/**
 * \定义MBEDTLS_MEMORY_BUFFER_ALLOC_C
 *
 * 启用缓冲区分配器实现，该实现利用基于（堆栈）的缓冲区来“分配”动态内存。（替换calloc（）和free（）调用）
 *
 * 模块：library/memory_buffer_alloc.c
 *
 * 需要：MBEDTLS_PLATFORM_C MBEDTLS_PLATFORM_MEMORY（在mbed TLS中使用）
 *
 * 启用此模块以启用缓冲内存分配器。
 */
//#定义MBEDTLS_MEMORY_BUFFER_ALLOC_C

/**
 * \定义MBEDTLS_NET_C
 *
 * 启用IPv6/IPv4上的TCP和UDP网络例程。
 *
 * \注意：此模块仅适用于POSIX/Unix（包括Linux、BSD和OS X）和Windows。对于其他平台，您需要禁用它，并编写自己的网络回调以传递给\c mbedtls_ssl_set_bio（）。
 *
 * \注意：另请参阅我们的知识库文章，了解如何移植到新环境：https://tls.mbed.org/kb/how-to/how-do-i-port-mbed-tls-to-a-new-environment-OS
 *
 * 模块：library/net_sockets.c
 *
 * 本模块提供网络例程。
 */
#define MBEDTLS_NET_C

/**
 * \定义MBEDTLS_OID_C
 *
 * 启用OID数据库。
 *
 * 模块：library/oid。c调用方：library/asn1write。c库/pkcs5.c库/pkparse。c库/pkwrite。c库/rsa。c库/x509.c库/x509_create。c库/x509_crl。c库/x509_crt。c库/x509_csr。c库/x509write_crt。c库/x509 write_csr.c
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
 * 模块：库/pem。c呼叫者：library/dhm。c库/pkparse。c库/x509_crl。c库/x509_crt。c库/x509_csr.c
 *
 * 需要：MBEDTLS_BASEE64_C
 *
 * 该模块增加了对PEM文件解码/解析的支持。
 */
#define MBEDTLS_PEM_PARSE_C

/**
 * \定义MBEDTLS_MEM_WRITE_C
 *
 * 启用PEM编码/写入。
 *
 * 模块：库/pem。c调用方：library/pkwrite。c库/x509write_crt。c库/x509 write_csr.c
 *
 * 需要：MBEDTLS_BASEE64_C
 *
 * 本模块增加了对PEM文件编码/写入的支持。
 */
#define MBEDTLS_PEM_WRITE_C

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
 * 模块：library/pkparse。c调用方：library/x509_crt。c库/x509_csr.c
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
 * \定义MBEDTLS_PKCS11_C
 *
 * 为PKCS#11智能卡支持启用包装器。
 *
 * 模块：library/pkcs11.c调用方：library/pk.c
 *
 * 需要：MBEDTLS_PK_C
 *
 * 此模块启用SSL/TLS PKCS#11智能卡支持。需要PKCS#11助手库（libpkcs11助手）
 */
//#定义MBEDTLS_PKCS11_C

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
#define MBEDTLS_POLY1305_C

/**
 * \定义MBEDTLS_PSA_CRYPTO_C
 *
 * 启用平台安全体系结构加密API。
 *
 * 模块：library/psa_crypto.c
 *
 * 需要：MBEDTLS_CTR_DRBG_C、MBEDTLS_ENTROPY_C
 *
 */
#define MBEDTLS_PSA_CRYPTO_C

/**
 * \定义MBEDTLS_PSA_CRYPTO_STORAGE_C
 *
 * 启用平台安全体系结构持久密钥存储。
 *
 * 模块：library/psa_crypto_storage.c
 *
 * 需要：MBEDTLS_PSA_CRYPTO_C、MBEDTLS_PSA_ITS_FILE_C或PSA ITS接口的本地实现
 */
#define MBEDTLS_PSA_CRYPTO_STORAGE_C

/**
 * \定义MBEDTLS_PSA_ITS_FILE_C
 *
 * 启用对文件的平台安全体系结构内部可信存储（PSA ITS）仿真。
 *
 * 模块：library/psa_its_file.c
 *
 * 需要：MBEDTLS_FS_IO
 */
#define MBEDTLS_PSA_ITS_FILE_C

/**
 * \定义MBEDTLS_RIPEMD160_C
 *
 * 启用RIPEMD-160哈希算法。
 *
 * 模块：library/ripmd160.c调用方：library/md.c
 *
 */
#define MBEDTLS_RIPEMD160_C

/**
 * \定义MBEDTLS_RSA_C
 *
 * 启用RSA公钥密码系统。
 *
 * 模块：library/rsa。c库/rsa_internal。c呼叫者：library/ssl_cli。c库/ssl_srv。c库/ssl_tls。c库/x509.c
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
 * 模块：library/sha1.c调用方：library.md。c库/ssl_cli。c库/ssl_srv。c库/ssl_tls。c库/x509 write_crt.c
 *
 * 此模块适用于1.1版以下的SSL/TLS、取决于握手参数的TLS 1.2以及SHA1签名证书。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。如果可能的话，我们建议避免对它的依赖，而是考虑更强大的消息摘要。
 *
 */
#define MBEDTLS_SHA1_C

/**
 * \定义MBEDTLS_SHA256_C
 *
 * 启用SHA-224和SHA-256加密哈希算法。
 *
 * 模块：library/sa256.c调用方：library/entropy。c库/md。c库/ssl_cli。c库/ssl_srv。c库/ssl_tls.c
 *
 * 此模块增加了对SHA-224和SHA-256的支持。SSL/TLS 1.2 PRF功能需要此模块。
 */
#define MBEDTLS_SHA256_C

/**
 * \定义MBEDTLS_SHA512_C
 *
 * 启用SHA-384和SHA-512加密哈希算法。
 *
 * 模块：library/sha512.c调用方：library/entropy。c库/md。c库/ssl_cli。c库/ssl_srv.c
 *
 * 该模块增加了对SHA-384和SHA-512的支持。
 */
#define MBEDTLS_SHA512_C

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
#define MBEDTLS_SSL_TICKET_C

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
#define MBEDTLS_SSL_CLI_C

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
#define MBEDTLS_SSL_SRV_C

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
#define MBEDTLS_SSL_TLS_C

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
//#定义MBEDTLS_THREADING_C

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
#define MBEDTLS_TIMING_C

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
 * 模块：library/x509.c调用方：library/x509_crl。c库/x509_crt。c库/x509_csr.c
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
 * 模块：library/x509_crt。c呼叫者：library/ssl_cli。c库/ssl_srv。c库/ssl_tls.c
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
 * 模块：library/x509_crl。c调用方：library/x509_crt.c
 *
 * 需要：MBEDTLS_X509_USE_C
 *
 * X.509 CRL分析需要此模块。
 */
#define MBEDTLS_X509_CRL_PARSE_C

/**
 * \定义MBEDTLS_X509_CSR_PARSE_C
 *
 * 启用X.509证书签名请求（CSR）分析。
 *
 * 模块：library/x509_csr。c调用方：library/x509_crt_write.c
 *
 * 需要：MBEDTLS_X509_USE_C
 *
 * 此模块用于读取X.509证书请求。
 */
#define MBEDTLS_X509_CSR_PARSE_C

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
#define MBEDTLS_XTEA_C

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

/* MPI/BIGNUM选项*/
//#define MBEDTLS_MPI_WINDOW_SIZE            6 /**<使用的最大窗口大小。*/
//#define MBEDTLS_MPI_MAX_SIZE            1024 /**<可用MPIs的最大字节数。*/

/* CTR_DRBG选项*/
//#define MBEDTLS_CTR_DRBG_ENTROPY_LEN               48 /**<默认情况下每个种子使用的熵量（SHA-512为48，SHA-256为32）*/
//#define MBEDTLS_CTR_DRBG_RESEED_INTERVAL        10000 /**<默认情况下执行重新设定种子前的间隔*/
//#define MBEDTLS_CTR_DRBG_MAX_INPUT                256 /**<附加输入字节的最大数量*/
//#define MBEDTLS_CTR_DRBG_MAX_REQUEST             1024 /**<每次调用请求的最大字节数*/
//#define MBEDTLS_CTR_DRBG_MAX_SEED_INPUT           384 /**<（重新）种子缓冲区的最大大小*/
//#define MBEDTLS_CTR_DRBG_USE_128_BIT_KEY              /**<对CTR_DRBG使用128位密钥-可能会降低安全性（请参见CTR_DRBG.h）*/

/* HMAC_DRBG选项*/
//#define MBEDTLS_HMAC_DRBG_RESEED_INTERVAL   10000 /**<默认情况下执行重新设定种子前的间隔*/
//#define MBEDTLS_HMAC_DRBG_MAX_INPUT           256 /**<附加输入字节的最大数量*/
//#define MBEDTLS_HMAC_DRBG_MAX_REQUEST        1024 /**<每次调用请求的最大字节数*/
//#define MBEDTLS_HMAC_DRBG_MAX_SEED_INPUT      384 /**<（重新）种子缓冲区的最大大小*/

/* ECP选项*/
//#define MBEDTLS_ECP_MAX_BITS             521 /**<组的最大位大小*/
//#define MBEDTLS_ECP_WINDOW_SIZE            6 /**<使用的最大窗口大小*/
//#define MBEDTLS_ECP_FIXED_POINT_OPTIM      1 /**<启用定点加速*/

/* 熵选项*/
//#define MBEDTLS_ENTROPY_MAX_SOURCES                20 /**<支持的最大源数*/
//#define MBEDTLS_ENTROPY_MAX_GATHER                128 /**<从熵源请求的最大数量*/
//#define MBEDTLS_ENTROPY_MIN_HARDWARE               32 /**<释放熵之前硬件熵源mbedtls_hardware_poll（）所需的默认最小字节数*/

/* 内存缓冲区分配器选项*/
//#define MBEDTLS_MEMORY_ALIGN_MULTIPLE      4 /**<按此值的倍数对齐*/

/* 平台选项*/
//#define MBEDTLS_PLATFORM_STD_MEM_HDR   <stdlib.h> /**<如果定义了MBEDTLS_PLATFORM_NO_STD_FUNCTIONS，则包含标题。不定义是否不需要标头。*/
//#define MBEDTLS_PLATFORM_STD_CALLOC        calloc /**<要使用的默认分配器，可以是未定义的*/
//#define MBEDTLS_PLATFORM_STD_FREE            free /**<默认自由使用，可以未定义*/
//#define MBEDTLS_PLATFORM_STD_EXIT            exit /**<要使用的默认出口，可以是未定义的*/
//#define MBEDTLS_PLATFORM_STD_TIME            time /**<默认使用时间，可以未定义。必须启用MBEDTLS_HAVE_TIME*/
//#define MBEDTLS_PLATFORM_STD_FPRINTF      fprintf /**<要使用的默认fprintf，可以是未定义的*/
//#define MBEDTLS_PLATFORM_STD_PRINTF        printf /**<要使用的默认printf，可以是未定义的*/
/* 注意：snprintf必须正确零终止缓冲区！*/
//#define MBEDTLS_PLATFORM_STD_SNPRINTF    snprintf /**<要使用的默认snprintf，可以是未定义的*/
//#define MBEDTLS_PLATFORM_STD_EXIT_SUCCESS       0 /**<要使用的默认退出值，可以是未定义的*/
//#define MBEDTLS_PLATFORM_STD_EXIT_FAILURE       1 /**<要使用的默认退出值，可以是未定义的*/
//#define MBEDTLS_PLATFORM_STD_NV_SEED_READ   mbedtls_platform_std_nv_seed_read /**<要使用的默认nv_seed_read函数，可以是未定义的*/
//#define MBEDTLS_PLATFORM_STD_NV_SEED_WRITE  mbedtls_platform_std_nv_seed_write /**<要使用的默认nv_sed_write函数，可以是未定义的*/
//#define MBEDTLS_PLATFORM_STD_NV_SEED_FILE  "seedfile" /**<Seed file to read/write with default implementation*/

/* 要使用函数宏，必须启用MBEDTLS_PLATFORM_C*/
/* MBEDTLS_PLATFORM_XXXMACRO和MBEDTLS_PLATFORM_6XX_ALT不能同时定义*/
//#define MBEDTLS_PLATFORM_CALLOC_MACRO        calloc /**<要使用的默认分配器宏，可以是未定义的*/
//#define MBEDTLS_PLATFORM_FREE_MACRO            free /**<要使用的默认自由宏，可以是未定义的*/
//#define MBEDTLS_PLATFORM_EXIT_MACRO            exit /**<要使用的默认退出宏，可以未定义*/
//#define MBEDTLS_PLATFORM_TIME_MACRO            time /**<要使用的默认时间宏，可以未定义。必须启用MBEDTLS_HAVE_TIME*/
//#define MBEDTLS_PLATFORM_TIME_TYPE_MACRO       time_t /**<要使用的默认时间宏，可以未定义。必须启用MBEDTLS_HAVE_TIME*/
//#define MBEDTLS_PLATFORM_FPRINTF_MACRO      fprintf /**<要使用的默认fprintf宏，可以是未定义的*/
//#define MBEDTLS_PLATFORM_PRINTF_MACRO        printf /**<要使用的默认printf宏，可以是未定义的*/
/* 注意：snprintf必须正确零终止缓冲区！*/
//#define MBEDTLS_PLATFORM_SNPRINTF_MACRO    snprintf /**<要使用的默认snprintf宏，可以是未定义的*/
//#define MBEDTLS_PLATFORM_VSNPRINTF_MACRO    vsnprintf /**<要使用的默认vsnprintf宏，可以是未定义的*/
//#define MBEDTLS_PLATFORM_NV_SEED_READ_MACRO   mbedtls_platform_std_nv_seed_read /**<要使用的默认nv_seed_read函数，可以是未定义的*/
//#define MBEDTLS_PLATFORM_NV_SEED_WRITE_MACRO  mbedtls_platform_std_nv_seed_write /**<要使用的默认nv_sed_write函数，可以是未定义的*/

/**
 * \brief当检测到仅使用MBEDTLS_CHECK_PARAMS检查的无效参数时，库将调用此宏（有关上下文，请参阅该选项的文档）。
 *
 *              当您在此处未定义此项时，将提供一个默认定义，用于调用函数mbedtls_param_failed（），该函数在platform_util中声明。h的好处，但您需要在应用程序中定义。
 *
 *              当您在此处定义它时，它将替换platform_util中的默认定义。h（不再声明函数mbedtls_param_failed（）），您有责任确保此宏扩展到合适的位置（特别是，所有必要的声明都在库中可见-您可以通过在宏定义旁边的文件中提供它们来确保）。
 *
 *              请注意，您可以将此宏定义为无扩展，在这种情况下，您不必担心声明或定义。然而，只有在非void函数中才会通知您无效的参数，而void函数只会在无效参数的早期默默返回，这部分否定了最初启用#MBEDTLS_CHECK_PARAMS的好处，因此不鼓励这样做。
 *
 * \param cond应计算为true但未计算为true的表达式。
 */
//#定义MBEDTLS_PARAM_FAILED（cond）断言（cond

/* SSL缓存选项*/
//#define MBEDTLS_SSL_CACHE_DEFAULT_TIMEOUT       86400 /**<1天*/
//#define MBEDTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES      50 /**<缓存中的最大条目数*/

/* SSL选项*/

/** \定义MBEDTLS_SL_MAX_CONTENT_LEN
 *
 * 传入和传出明文片段的最大长度（字节）。
 *
 * 这决定了传入和传出TLS I/O缓冲区的大小，使得两者都能够保存指定数量的明文数据，而不考虑使用的保护机制。
 *
 * 要分别配置传入和传出I/O缓冲区，请使用#MBEDTLS_SL_IN_CONTENT_LEN和#MBEDLLS_SL_OUT_CONTENT.LEN，它们将覆盖此选项设置的值。
 *
 * \注意：当在客户端上使用小于默认值16KB的值时，建议使用最大片段长度（MFL）扩展来通知服务器此限制。在服务器上，没有受支持的标准化方式来通知客户端有关传入消息最大大小的限制，除非通过其他方式传达了限制，否则建议只更改传出缓冲区大小#MBEDTLS_SL_OUT_CONTENT_LEN，同时保留传入缓冲区的默认值16KB。
 *
 * 取消注释以设置传入和传出I/O缓冲区的最大明文大小。
 */
//#定义MBEDTLS_SL_MAX_CONTENT_LEN 16384

/** \定义MBEDTLS_SL_IN_CONTENT_LEN
 *
 * 传入明文片段的最大长度（字节）。
 *
 * 这决定了传入TLS I/O缓冲区的大小，使其能够保存指定数量的明文数据，而不考虑所使用的保护机制。
 *
 * 如果未定义此选项，它将从#MBEDTLS_SL_MAX_CONTENT_LEN继承其值。
 *
 * \注意：当在客户端上使用小于默认值16KB的值时，建议使用最大片段长度（MFL）扩展来通知服务器此限制。在服务器上，没有受支持的标准化方式来通知客户端有关传入消息最大大小的限制，除非通过其他方式传达了限制，否则建议只更改传出缓冲区大小#MBEDTLS_SL_OUT_CONTENT_LEN，同时保留传入缓冲区的默认值16KB。
 *
 * 取消注释以独立于传出I/O缓冲区设置传入I/O缓冲区的最大明文大小。
 */
//#定义MBEDTLS_SL_IN_CONTENT_LEN 16384

/** \定义MBEDTLS_SL_OUT_CONTENT_LEN
 *
 * 传出明文片段的最大长度（字节）。
 *
 * 这决定了传出TLS I/O缓冲区的大小，使其能够保存指定数量的明文数据，而不考虑使用的保护机制。
 *
 * 如果未定义此选项，它将从#MBEDTLS_SL_MAX_CONTENT_LEN继承其值。
 *
 * 可以通过设置较小的向外缓冲区来节省RAM，同时保持默认的向内16384字节缓冲区以符合TLS规范。
 *
 * 所需的最小向外缓冲区大小由握手协议的使用情况决定。如果向外缓冲区太小，握手将失败。具体的大小要求取决于配置的密码和握手期间发送的任何证书数据。
 *
 * 取消注释以独立于传入I/O缓冲区设置传出I/O缓冲区的最大明文大小。
 */
//#定义MBEDTLS_SL_OUT_CONTENT_LEN 16384

/** \定义MBEDTLS_SL_DTLS_MAX_BUFFERING
 *
 * 用于DTLS握手消息重组和未来消息缓冲的最大堆分配字节数。
 *
 * 这至少应为9/8*MBEDTLSLSLS_IN_CONTENT_LEN，以说明最大大小的重新组合握手消息及其重新组合位图。
 *
 * 对于所有实际情况，2*MBEDTLS_SL_IN_CONTENT_LEN（默认值为32768）的值应该足够，因为它允许在缓冲多个较小握手消息的同时重新组合大握手消息（例如证书）。
 *
 */
//#定义MBEDTLS_SL_DTLS_MAX_BUFFERING 32768

//#define MBEDTLS_SSL_DEFAULT_TICKET_LIFETIME     86400 /**<会话票证的生存期（如果启用）*/
//#define MBEDTLS_PSK_MAX_LEN               32 /**<TLS预共享密钥的最大大小，以字节为单位（默认256位）*/
//#define MBEDTLS_SSL_COOKIE_TIMEOUT        60 /**＜DTLS cookie的默认过期延迟，如果是HAVE_TIME，则以秒为单位，或者以发出的cookie数量为单位*/

/**
 * 按优先顺序列出要使用的密码套件的完整列表。
 *
 * \警告：未对该字段进行相关性检查！此选项只能用于限制可用密码套件集。您有责任确保所需的模块处于活动状态。
 *
 * 使用此选项可以节省几百字节的ROM（所有可用密码套件的默认排序）和几百到几百字节的RAM。
 *
 * 下面的值只是一个示例，不是默认值。
 */
//#定义MBEDTLS_SL_CIPHERSUITES MBEDTL_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384、MBEDTLS_TLS_ECDHE_ECDSA _WITH_AES _128_GCM_SHAD56

/* X509选项*/
//#define MBEDTLS_X509_MAX_INTERMEDIATE_CA   8   /**<验证链中中间CA的最大数量。*/
//#define MBEDTLS_X509_MAX_FILE_PATH_LEN     512 /**<路径/文件名字符串的最大长度（字节），包括空终止符（“\0”）。*/

/**
 * 在证书签名的默认TLS配置中允许SHA-1。如果没有此构建时选项，则必须通过mbedtls_ssl_conf_cert_profile显式激活SHA-1支持。不建议启用此选项，因为可能会生成SHA-1冲突，但这对于应用附加控制的传统基础设施可能是安全的。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。如果可能的话，我们建议避免对它的依赖，而是考虑更强大的消息摘要。
 *
 */
// #定义MBEDTLS_TLS_DEFAULT_ALLOW_SHA1_IN_CERTIFICATES

/**
 * 在TLS 1.2握手签名和密码套件选择的默认TLS配置中允许SHA-1。如果没有此构建时选项，则必须通过mbedtls_ssl_conf_sig_hashe显式激活SHA-1支持。默认情况下，始终允许在TLS<=1.1和HMAC-SHA-1中使用SHA-1。在撰写本文时，没有针对握手签名中使用SHA-1的实际攻击，因此默认情况下启用此选项以保持与现有对等体的兼容性，但一般警告仍然适用：
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。如果可能的话，我们建议避免对它的依赖，而是考虑更强大的消息摘要。
 *
 */
#define MBEDTLS_TLS_DEFAULT_ALLOW_SHA1_IN_KEY_EXCHANGE

/**
 * 取消对宏的注释，以便让mbed-TLS使用mbedtls_platform_zerozize（）的替代实现。这将替换platform_util.c中的默认实现。
 *
 * mbedtls_platform_zeroze（）是库中广泛使用的一个函数，用于将内存块归零。该实现应该是安全的，因为它是为了防止编译器在冗余代码消除优化过程中删除对mbedtls_platform_zerozize（）的调用而编写的。然而，很难保证对mbedtls_platform_zerozize（）的调用不会被编译器优化，因为C语言标准的旧版本不提供memset（）的安全实现。因此，MBEDTLS_PLATFORM_ZERIZE_ALT使用户能够配置自己的MBEDTLS_PLATFORM_ZERIze（）实现，例如，通过使用特定于编译器的指令、来自较新C标准的特性（例如，在C11中使用memset_s（））或从系统调用安全memset（）（例如，BSD中的explicit_bezero（））。
 */
//#定义MBEDTLS_PLATFORM_ZERIZE_ALT

/**
 * 取消对宏的注释，以便让Mbed TLS使用mbedtls_platform_gmtime_r（）的替代实现。这将替换platform_util.c中的默认实现。
 *
 * gmtime（）不是C标准中定义的线程安全函数。库将尝试使用此函数的更安全的实现，如gmtime_r（）（如果可用）。但是，如果Mbed TLS无法识别目标系统，则mbedtls_platform_gmtime_r（）的实现将默认使用标准gmtime（）。在这种情况下，如果启用了mbedtls_threading_C，则从库到gmtime（）的调用将由全局互斥体mbedtls_threading_gmtime_mutex保护。我们建议使用这个互斥锁来保护库外部的调用，以避免竞争条件。但是，如果定义了宏MBEDTLS_PLATFORM_GMTIME_R_ALT，则Mbed TLS将无条件地使用编译时提供的MBEDTLS_PLATFORM_GMTIME_R（）的实现。
 */
//#定义MBEDTLS_PLATFORM_GMTIME_R_ALT

/* \}name SECTION:自定义配置选项*/

/* 目标和应用程序特定的配置
 *
 * 允许用户覆盖以前的任何默认值。
 *
 */
#if defined(MBEDTLS_USER_CONFIG_FILE)
#include MBEDTLS_USER_CONFIG_FILE
#endif

#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */

