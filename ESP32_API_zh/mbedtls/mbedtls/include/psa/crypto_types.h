/**
 * \psa/crypto_types.h文件
 *
 * \PSA密码模块简介：类型别名。
 *
 * \注意：此文件可能不直接包含。应用程序必须包含psa/crypto.h。驱动程序必须包含相应的驱动程序头文件。
 *
 * 此文件包含加密密钥属性、加密算法名称和库返回的错误代码的整数类型的可移植定义。
 *
 * 此头文件未声明任何函数。
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

#ifndef PSA_CRYPTO_TYPES_H
#define PSA_CRYPTO_TYPES_H

#include "crypto_platform.h"

/* 如果定义了MBEDTLS_PSA_CRYPTO_C，请确保也定义了MBEDTLS_PSA_CRYPTO_CLIENT，以包括所有PSA代码。
 */
#if defined(MBEDTLS_PSA_CRYPTO_C)
#define MBEDTLS_PSA_CRYPTO_CLIENT
#endif /* MBEDTLS_PSA_CRYPTO_C */

#include <stdint.h>

/** \defgroup错误错误代码@{
 */

/**
 * \简短的函数返回状态。
 *
 * 这要么是#PSA_SUCCESS（为零），表示成功，要么是一个小负值，表示发生了错误。错误编码为此处定义的\c PSA_ERROR_xxx值之一。*/
/* 如果#PSA_SUCCESS已经定义，则意味着#PSA_status_t也在外部标头中定义，因此请避免其多重定义。
 */
#ifndef PSA_SUCCESS
typedef int32_t psa_status_t;
#endif

/**@}*/

/** \defgroup crypto_types密钥和算法类型@{
 */

/** \密钥类型的简短编码。
 */
typedef uint16_t psa_key_type_t;

/** PSA椭圆曲线族标识符的类型。
 *
 * 使用PSA_key_TYPE_ECC_key_PAIR（）或PSA_key_TYPE_ECC_PUBLIC_key（）宏创建ECC密钥需要曲线标识符。
 *
 * 本标准定义的值永远不会在0x80-0xff范围内。定义其他系列的供应商必须使用此范围内的编码。
 */
typedef uint8_t psa_ecc_family_t;

/** PSA Diffie-Hellman组族标识符的类型。
 *
 * 使用PSA_key_TYPE_DH_key_PAIR（）或PSA_key_TYPE_DH_PUBLIC_key（）宏创建Diffie-Hellman密钥需要组标识符。
 *
 * 本标准定义的值永远不会在0x80-0xff范围内。定义其他系列的供应商必须使用此范围内的编码。
 */
typedef uint8_t psa_dh_family_t;

/** \密码算法的简短编码。
 *
 * 对于可以应用于多个密钥类型的算法，此类型不编码密钥类型。例如，对于基于分组密码的对称密码，#psa_calgorithm_t对分组密码模式和填充模式进行编码，而分组密码本身通过#psa_key_type_t进行编码。
 */
typedef uint32_t psa_algorithm_t;

/**@}*/

/** \defgroup key_lifetimes密钥生存期@{
 */

/** 密钥生存期的编码。
 *
 * 密钥的生命周期指示密钥存储的位置以及系统操作可能创建和销毁密钥。
 *
 * 寿命值具有以下结构：
 * -位0-7（#PSA_KEY_LIFETIME_GET_PERSISTENCE（\c生存期））：持久性级别。此值指示哪些设备管理操作可能导致其被销毁。特别地，它指示密钥是_volable_还是_persistent_。有关详细信息，请参见：：psa_key_persistence_t。
 * -位8-31（#PSA_KEY_LEIFETIME_GET_LOCATION（\c生存期））：位置指示符。该值指示系统的哪个部分可以访问密钥材料，并且可以使用密钥执行操作。有关详细信息，请参阅：：psa_key_location_t。
 *
 * 当应用程序实例终止或设备电源重置时，易失性密钥会自动销毁。持久密钥将保留，直到应用程序显式销毁它们或发生特定于集成的设备管理事件（例如，工厂重置）。
 *
 * 持久密钥的密钥标识符类型为#mbedtls_svc_key_id_t。即使创建密钥的应用程序实例终止，该标识符在密钥的整个生命周期内仍然有效。应用程序可以调用psa_open_key（）来打开之前创建的持久密钥。
 *
 * 密钥的默认生存期为#PSA_key_lifetime_VOLATILE。如果持久存储可用，则支持生存期#PSA_KEY_LIFIME_PERSISTENT。根据库配置，可能支持其他生存期值。
 */
typedef uint32_t psa_key_lifetime_t;

/** 关键持久性级别的编码。
 *
 * 不同持久性级别的区别在于设备管理事件可能导致密钥被销毁_Volatile_键被电源重置破坏。永久密钥可能会被所有权转移或工厂重置等事件破坏。什么管理事件实际上会影响不同级别的持久密钥，这超出了PSA Cryptography规范的范围。
 *
 * PSA Cryptography规范定义了以下持久性级别值：
 * -\c 0=#PSA_KEY_PERSISTENCE_VOLATILE：易失性密钥。当应用程序实例终止时，实现会自动销毁易失性密钥。特别是，易失性密钥在设备电源复位时自动销毁。
 * -\c 1=#PSA_KEY_PERSISTENCE_DEFAULT：具有默认生存期的持久密钥。
 * -\c 2-254:Mbed TLS当前不支持。
 * -\c 255=#PSA_KEY_PERSISTENCE_READ_ONLY：只读或一次写入密钥。无法销毁具有此持久性级别的密钥。Mbed TLS目前没有提供创建此类密钥的方法，但Mbed TLS的集成可以将其用于应用程序无法修改的内置密钥（例如，硬件唯一密钥（HUK））。
 *
 * \注：密钥持久性级别为8位值。密钥管理接口在生存期（类型：：psa_Key_lifetime_t）上运行，将持久性编码为32位值的低8位。
 */
typedef uint8_t psa_key_persistence_t;

/** 关键位置指示器的编码。
 *
 * 如果Mbed TLS的集成可以调用外部密码处理器（如安全元件），则密钥的位置指示哪个安全元件对密钥执行操作。取决于安全元件的设计，密钥材料可以存储在安全元件中，或者以包裹（加密）形式与密钥元数据一起存储在主本地存储器中。
 *
 * PSA加密API规范定义了以下位置指示符值：
 * -\c 0：主本地存储。此位置始终可用。主本地存储通常是包含密钥元数据的同一存储区域。
 * -\c 1：主要安全元素。如果操作环境附加了安全元素，则Mbed TLS的集成应支持此值。作为指导原则，安全元件可以提供比主本地存储更高的抗侧信道和物理攻击的能力，但可能对支持的密钥类型、大小、策略和操作有限制，并且可能具有不同的性能特征。
 * -\c 2-0x7fffff：PSA规范定义的其他位置。PSA Cryptography API目前没有为这些位置指定任何含义，但该规范或其他PSA规范的未来版本可能会这样做。
 * -\c 0x800000-0xffffff：供应商定义的位置。没有PSA规范将为该范围内的位置赋予意义。
 *
 * \注：关键位置指示器为24位值。密钥管理接口对生存期（类型：：psa_Key_lifetime_t）进行操作，将位置编码为32位值的高位24位。
 */
typedef uint32_t psa_key_location_t;

/** 持久密钥标识符的编码。
 *
 * -应用程序可以自由选择#PSA_key_ID_USER_MIN到#PSA_key _ID_USER-MAX范围内的密钥标识符。
 * -该实现可以在#PSA_key_ID_VENDOR_MIN到#PSA_key _ID_VENDOR_MAX的范围内定义额外的密钥标识符。
 * -0被保留为无效的密钥标识符。
 * -这些范围之外的密钥标识符保留供将来使用。
 */
typedef uint32_t psa_key_id_t;

#if !defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)
typedef psa_key_id_t mbedtls_svc_key_id_t;

#else /* MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER */
/* 特定于实现：Mbed Cryptography库可以构建为多客户端服务的一部分，该服务在每个客户端中公开PSA Cryptograpy API，并在函数（如PSA_open_key（））的密钥标识符参数中编码客户端身份。
 */
typedef struct
{
    psa_key_id_t key_id;
    mbedtls_key_owner_id_t owner;
} mbedtls_svc_key_id_t;

#endif /* !MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER */

/**@}*/

/** \defgroup策略关键策略@{
 */

/**\brief密钥上允许使用的编码。*/
typedef uint32_t psa_key_usage_t;

/**@}*/

/** \defgroup属性关键点属性@{
 */

/** 包含键属性的结构的类型。
 *
 * 这是一个不透明的结构，可以表示关键对象的元数据。可以存储在属性中的元数据包括：
 * -密钥在存储器中的位置，由其密钥标识符及其生存期表示。
 * -密钥的策略，包括使用标志和允许算法的规范。
 * -有关密钥本身的信息：密钥类型及其大小。
 * -其他实现定义的属性。
 *
 * 实际的键材质不被视为键的属性。关键属性不包含通常被视为高度机密的信息。
 *
 * 属性结构的工作方式类似于简单的数据结构，其中每个函数“psa_set_key_xxx”设置一个字段，而相应的函数“psaquet_key_xx”检索相应字段的值。但是，库的未来版本可能会报告与原始版本相同但编码不同的值。无效值可能映射到不同的值，也可能是无效值。
 *
 * 属性结构可以包含对辅助资源的引用，例如对已分配内存的指针或对预计算值的间接引用。为了释放这些资源，应用程序必须调用psa_reset_key_attributes（）。作为一个例外，如果属性结构自初始化或上次使用psa_reset_key_attributes（）重置后仅被以下函数修改，则对该结构调用psa_reet_key_aattributes（（）是可选的：
 * -psa_set_key_id（）
 * -psa_set_key_lifetime（）
 * -psa_set_key_type（）
 * -psa_set_key_bits（）
 * -psa_set_key_usage_flags（）
 * -psa_set_key_algorithm（）
 *
 * 在调用键属性结构上的任何函数之前，应用程序必须通过以下任一方式对其进行初始化：
 * -将结构设置为所有位为零，例如：\code psa_key_attributes_t attributes；memset（&attributes，0，sizeof（attributes））；\结束代码
 * -将结构初始化为逻辑零值，例如：\code psa_key_attributes_t attributes={0}；\结束代码
 * -将结构初始化为初始值设定项#PSA_KEY_ATTRIBUTES_INIT，例如：\code PSA_KEY_ATTRIBUTES_t ATTRIBUTES=PSA_KEY_ATTRIBUTES_INIT；\结束代码
 * -将函数psa_key_attributes_init（）的结果赋给结构，例如：\code psa_kkey_attributes _t attributes；attributes=psa_key_attributes_init（）；\结束代码
 *
 * 新初始化的属性结构包含以下值：
 *
 * -生存期：#PSA_KEY_LIFIME_VOLATILE。
 * -密钥标识符：0（不是有效的密钥标识符）。
 * -type:\c 0（表示未指定类型）。
 * -密钥大小：\c 0（表示未指定大小）。
 * -用法标志：\c 0（除了导出公钥外，不允许使用）。
 * -算法：\c 0（不允许加密使用，但允许导出）。
 *
 * 创建密钥的典型顺序如下：
 * -#创建并初始化属性结构。
 * -#如果密钥是持久的，请调用psa_set_key_id（）。还可以调用psa_set_key_lifetime（）将密钥放置在非默认位置。
 * -#使用psa_Set_key_usage_flags（）和psa_se_key_algorithm（）设置密钥策略。
 * -#使用psa_Set_key_type（）设置密钥类型。如果使用psa_copy_key（）复制现有密钥，请跳过此步骤。
 * -#使用psa_generate_key（）生成随机密钥或使用psa_key_derivation_output_key（（）派生密钥时，请使用psa_set_key_bits（）设置所需的密钥大小。
 * -#调用密钥创建函数：psa_import_key（）、psa_generate_key（、psa_key_derivation_output_key（或psa_copy_key）。此函数读取属性结构，使用这些属性创建密钥，并向新创建的密钥输出密钥标识符。
 * -#现在不再需要属性结构。您可以调用psa_reset_key_attributes（），尽管这对于此处提供的工作流是可选的，因为本规范中当前定义的属性不需要结构本身以外的任何额外资源。
 *
 * 查询键属性的典型顺序如下：
 * -#调用psa_get_key_attributes（）。
 * -#调用“psa_get_key_xxx”函数以检索您感兴趣的属性。
 * -#调用psa_reset_key_attributes（）释放属性结构可能使用的任何资源。
 *
 * 一旦创建了密钥，就不可能更改其属性。
 */
typedef struct psa_key_attributes_s psa_key_attributes_t;


#ifndef __DOXYGEN_ONLY__
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
/* Mbed Crypto在Crypto_types中定义了此类型。h，因为它也通过特定于实现的扩展对应用程序可见。对于PSA Cryptography规范，此类型仅通过crypto_se_driver.h可见。*/
typedef uint64_t psa_key_slot_number_t;
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */
#endif /* !__DOXYGEN_ONLY__ */

/**@}*/

/** \defgroup派生密钥派生@{
 */

/**\密钥派生步骤的编码。*/
typedef uint16_t psa_key_derivation_step_t;

/**@}*/

#endif /* PSA_CRYPTO_TYPES_H */

