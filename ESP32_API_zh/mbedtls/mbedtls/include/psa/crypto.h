/**
 * \文件psa/crypto。平台安全架构加密模块
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

#ifndef PSA_CRYPTO_H
#define PSA_CRYPTO_H

#include "crypto_platform.h"

#include <stddef.h>

#ifdef __DOXYGEN_ONLY__
/* 此__DOXYGEN_ONLY__块包含必须在crypt_platform中定义的对象的模拟定义。h标题。为了方便生成包含这些定义的漂亮打印文档，本文件中提供了这些模拟定义。*/

/** \defgroup平台特定于实现的定义@{
 */

/**@}*/
#endif /* __DOXYGEN_ONLY__ */

#ifdef __cplusplus
extern "C" {
#endif

/* 文件“crypto_types.h”声明了编码错误、算法、密钥类型、策略等的类型。*/
#include "crypto_types.h"

/** \defgroup版本API版本@{
 */

/**
 * PSA Crypto API实现的主要版本
 */
#define PSA_CRYPTO_API_VERSION_MAJOR 1

/**
 * PSA Crypto API实现的次要版本
 */
#define PSA_CRYPTO_API_VERSION_MINOR 0

/**@}*/

/* 文件“crypto_values.h”声明宏来构建和分析“crypt_types.h”中定义的整数类型的值。*/
#include "crypto_values.h"

/** \defgroup初始化库初始化@{
 */

/**
 * \简短的库初始化。
 *
 * 应用程序必须在调用此模块中的任何其他函数之前调用此函数。
 *
 * 应用程序可以多次调用此函数。一旦呼叫成功，后续呼叫将保证成功。
 *
 * 如果应用程序在调用psa_crypto_init（）之前调用其他函数，则行为未定义。建议实现像初始化库一样执行操作，或者返回#PSA_ERROR_BAD_STATE或其他适用的错误。特别是，如果缺少初始化可能会产生安全影响，例如由于随机数生成器的不正确播种，则实现不应返回成功状态。
 *
 * \retval#PSA_SUCCESS\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_inSUFFIE_STORAGE\retval#8PSA_ERROR_COMMUNICATION_FAILURE\retval#1PSA_ERROR_HARDWARE_FAILUE\retval#PSTA_ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_INSUFFICE_ENTROPY\retval#2PSA_ERROR_STORAGE_FAILURE \retval#3PSA_ERROR_DATA_INVALID\retval#2PSA_ERROR _DATA_CORRUPT
 */
psa_status_t psa_crypto_init(void);

/**@}*/

/** \addtogroup属性@{
 */

/** \定义PSA_KEY_ATTRIBUTES_INIT
 *
 * 此宏为#psa_key_attributes_t类型的键属性结构返回合适的初始值设定项。
 */
#ifdef __DOXYGEN_ONLY__
/* 这是用于文档目的的示例定义。实现应在“crypt_struct.h”中定义适当的值。
 */
#define PSA_KEY_ATTRIBUTES_INIT {0}
#endif

/** 返回键属性结构的初始值。
 */
static psa_key_attributes_t psa_key_attributes_init(void);

/** 将密钥声明为持久性并设置其密钥标识符。
 *
 * 如果属性结构当前将密钥声明为volatile（这是属性结构的默认内容），则此函数将生存期属性设置为#PSA_key_lifetime_PERSISTENT。
 *
 * 此函数不访问存储，它只在结构中存储给定值。当属性结构传递给密钥创建函数（如psa_import_key（）、psa_generate_key（（）、psa_key_derivation_output_key（或psa_copy_key））时，持久密钥将被写入存储器。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似函数的宏提供，但在这种情况下，它必须对每个参数求值一次。
 *
 * \param[out]attributes要写入的属性结构。\param key键的持久标识符。
 */
static void psa_set_key_id( psa_key_attributes_t *attributes,
                            mbedtls_svc_key_id_t key );

#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
/** 设置密钥的所有者标识符。
 *
 * 当密钥标识符编码密钥所有者标识符时，psa_set_key_id（）不允许在密钥属性中定义易失性密钥的所有者，因为psa_se_key_id）强制密钥是持久的。
 *
 * 此函数允许在密钥属性中设置密钥的所有者标识符。它用于易失性密钥。对于持久密钥，建议使用PSA Cryptography API PSA_set_key_id（）来定义密钥的所有者。
 *
 * \param[out]attributes要写入的属性结构。\param owner密钥所有者标识符。
 */
static void mbedtls_set_key_owner_id( psa_key_attributes_t *attributes,
                                      mbedtls_key_owner_id_t owner );
#endif

/** 设置持久密钥的位置。
 *
 * 要使密钥持久化，必须使用psa_set_key_id（）为其提供持久密钥标识符。默认情况下，具有持久标识符的密钥通过#PSA_key_LIFETIME_persistent存储在默认存储区域标识符中。调用此函数以选择存储区域，或显式声明密钥为易失性。
 *
 * 此函数不访问存储，它只在结构中存储给定值。当属性结构传递给密钥创建函数（如psa_import_key（）、psa_generate_key（（）、psa_key_derivation_output_key（或psa_copy_key））时，持久密钥将被写入存储器。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似函数的宏提供，但在这种情况下，它必须对每个参数求值一次。
 *
 * \param[out]attributes要写入的属性结构。\param lifetime键的生存期。如果这是#PSA_KEY_LIFETIME_VOLATILE，则密钥将是易失性的，并且密钥标识符属性将重置为0。
 */
static void psa_set_key_lifetime(psa_key_attributes_t *attributes,
                                 psa_key_lifetime_t lifetime);

/** 从密钥属性中检索密钥标识符。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似宏的函数提供，但在这种情况下，它必须对其参数求值一次。
 *
 * \param[in]attributes要查询的键属性结构。
 *
 * \return存储在属性结构中的持久标识符。如果属性结构将键声明为volatile，则未指定此值。
 */
static mbedtls_svc_key_id_t psa_get_key_id(
    const psa_key_attributes_t *attributes);

/** 从关键属性检索生存期。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似宏的函数提供，但在这种情况下，它必须对其参数求值一次。
 *
 * \param[in]attributes要查询的键属性结构。
 *
 * \return存储在属性结构中的生存期值。
 */
static psa_key_lifetime_t psa_get_key_lifetime(
    const psa_key_attributes_t *attributes);

/** 声明密钥的用法标志。
 *
 * 使用标志是密钥使用策略的一部分。它们对密钥上允许的操作类型进行编码。有关更多详细信息，请参阅#psa_key_usage_t类型的文档。
 *
 * 此函数覆盖以前在\p属性中设置的所有用法标志。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似函数的宏提供，但在这种情况下，它必须对每个参数求值一次。
 *
 * \param[out]attributes要写入的属性结构。\param usage_flags要写入的用法标志。
 */
static void psa_set_key_usage_flags(psa_key_attributes_t *attributes,
                                    psa_key_usage_t usage_flags);

/** 从关键属性检索使用标志。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似宏的函数提供，但在这种情况下，它必须对其参数求值一次。
 *
 * \param[in]attributes要查询的键属性结构。
 *
 * \return存储在属性结构中的用法标志。
 */
static psa_key_usage_t psa_get_key_usage_flags(
    const psa_key_attributes_t *attributes);

/** 声明密钥的允许算法策略。
 *
 * 密钥的许可算法策略对允许与该密钥一起使用的一个或多个算法进行编码。支持以下算法策略：
 * -0不允许对密钥进行任何加密操作。密钥可用于非加密操作，如导出（如果使用标志允许）。
 * -算法值允许此特定算法。
 * -从#PSA_AG_ANY_HASH构建的算法通配符允许使用任何哈希算法指定签名方案。
 * -从#PSA_ALG_AT_LEAST_THIS_LENGTH_MAC构建的算法允许来自相同基类（例如CMAC）的任何MAC算法，其生成/验证大于或等于通配符算法中编码的长度的MAC长度。
 * -从#PSA_ALG_EAD_WITH_AT_LEAST_THIS_LENGTH_TAG构建的算法允许来自相同基类（例如CCM）的任何AEAD算法，该算法生成/验证大于或等于通配符算法中编码的长度的标签长度。
 *
 * 此函数覆盖以前在\p属性中设置的任何算法策略。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似函数的宏提供，但在这种情况下，它必须对每个参数求值一次。
 *
 * \param[out]attributes要写入的属性结构。\param alg允许写入的算法策略。
 */
static void psa_set_key_algorithm(psa_key_attributes_t *attributes,
                                  psa_algorithm_t alg);


/** 从关键属性检索算法策略。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似宏的函数提供，但在这种情况下，它必须对其参数求值一次。
 *
 * \param[in]attributes要查询的键属性结构。
 *
 * \return存储在属性结构中的算法。
 */
static psa_algorithm_t psa_get_key_algorithm(
    const psa_key_attributes_t *attributes);

/** 声明键的类型。
 *
 * 此函数覆盖以前在\p属性中设置的任何键类型。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似函数的宏提供，但在这种情况下，它必须对每个参数求值一次。
 *
 * \param[out]attributes要写入的属性结构。\param type要写入的键类型。如果该值为0，则\p属性中的键类型将未指定。
 */
static void psa_set_key_type(psa_key_attributes_t *attributes,
                             psa_key_type_t type);


/** 声明键的大小。
 *
 * 此函数覆盖以前在\p属性中设置的任何键大小。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似函数的宏提供，但在这种情况下，它必须对每个参数求值一次。
 *
 * \param[out]attributes要写入的属性结构。\param bits以位为单位的密钥大小。如果该值为0，则\p属性中的密钥大小将未指定。不支持大小为0的键。
 */
static void psa_set_key_bits(psa_key_attributes_t *attributes,
                             size_t bits);

/** 从键属性中检索键类型。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似宏的函数提供，但在这种情况下，它必须对其参数求值一次。
 *
 * \param[in]attributes要查询的键属性结构。
 *
 * \return存储在属性结构中的键类型。
 */
static psa_key_type_t psa_get_key_type(const psa_key_attributes_t *attributes);

/** 从密钥属性中检索密钥大小。
 *
 * 此函数可以声明为“静态”（即没有外部链接）。此函数可以作为类似宏的函数提供，但在这种情况下，它必须对其参数求值一次。
 *
 * \param[in]attributes要查询的键属性结构。
 *
 * \return存储在属性结构中的密钥大小，以位为单位。
 */
static size_t psa_get_key_bits(const psa_key_attributes_t *attributes);

/** 检索密钥的属性。
 *
 * 此函数首先重置属性结构，与psa_reset_key_attributes（）一样。然后，它将给定键的属性复制到给定的属性结构中。
 *
 * \注意：此功能可分配内存或其他资源。在属性结构上调用此函数后，必须调用psa_reset_key_attributes（）来释放这些资源。
 *
 * \param[in]key要查询的密钥的标识符。\param[in，out]attributes成功时，密钥的属性。失败时，相当于新初始化的结构。
 *
 * \retval#PSA_SUCCESS\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA _ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_CORRUPTION_DETECTED \retval#1PSA_ERROR_STORAGE_FAILURE \retval#2PSA_ERROR_DATA_CORRUPT\retval#3PSA_ERROR_BATA_INVALID\retval#8PSA_ERROR-BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_get_key_attributes(mbedtls_svc_key_id_t key,
                                    psa_key_attributes_t *attributes);

/** 将键属性结构重置为新初始化的状态。
 *
 * 在调用此函数之前，必须按照#psa_key_attributes_t类型的文档中的描述初始化属性结构。结构初始化后，您可以随时调用此函数。
 *
 * 此函数释放结构可能包含的任何辅助资源。
 *
 * \param[in，out]attributes要重置的属性结构。
 */
void psa_reset_key_attributes(psa_key_attributes_t *attributes);

/**@}*/

/** \defgroup key_management密钥管理@{
 */

/** 从记忆中删除关键材料的非必要副本。
 *
 * 如果密钥标识符指定了一个易失性密钥，则该函数不会执行任何操作并成功返回。
 *
 * 如果密钥标识符指定了持久密钥，则该函数将释放易失性内存中与密钥相关的所有资源。持久存储中的密钥数据不受影响，密钥仍可使用。
 *
 * \param key要清除的密钥的标识符。
 *
 * \retval#PSA_SUCCESS如果当前不需要密钥材料，则该密钥材料将从内存中删除。\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥不是有效的密钥标识符。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_purge_key(mbedtls_svc_key_id_t key);

/** 复制密钥。
 *
 * 将关键材料从一个位置复制到另一个位置。
 *
 * 此函数主要用于将密钥从一个位置复制到另一个位置，因为它使用另一个密钥的材质填充密钥，而另一个可能具有不同的寿命。
 *
 * 此功能可用于与另一方共享密钥，但受实施定义的密钥共享限制的限制。
 *
 * 源密钥上的策略必须设置用法标志#PSA_key_usage_COPY。如果密钥的生存期为#PSA_key_LFETIME_VOLATILE或#PSA_key _LFETIME_PERSISTENT，则此标志足以允许复制。一些安全元件不提供在不使密钥可从安全元件提取的情况下复制密钥的方法。如果密钥位于这样的安全元素中，则密钥必须同时具有使用标志#PSA_key_usage_COPY和#PSA_key _usage_EXPORT，以便在安全元素之外复制密钥。
 *
 * 生成的密钥只能以符合原始密钥的策略和\p attributes参数中指定的策略的方式使用：
 * -结果密钥上的用法标志是源策略上的用法标记和\p属性中的用法标记的位和。
 * -如果两者都允许相同的算法或基于通配符的算法策略，则生成的密钥具有相同的算法策略。
 * -如果其中一个策略允许一个算法，而另一个策略则允许包含此算法的基于通配符的算法策略，则生成的密钥允许相同的算法。
 * -如果策略不允许任何通用算法，则此函数将失败，状态为#PSA_ERROR_INVALID_ARGUMENT。
 *
 * 此函数对实现定义属性的影响由实现定义。
 *
 * \param source_key要复制的密钥。它必须允许使用#PSA_KEY_usage_COPY。如果在安全元素外部复制私钥或密钥，则还必须允许#PSA_key_USAGE_EXPORT。\param[in]attributes新密钥的属性。它们的使用方式如下：
 *                          -密钥类型和大小可以为0。如果其中之一为非零，则必须与源密钥的相应属性匹配。
 *                          -直接使用密钥位置（生存期以及持久密钥的密钥标识符）。
 *                          -策略约束（使用标志和算法策略）由源密钥和\p属性组合而成，因此这两组约束都适用，如本函数文档中所述。\param[out]target_key成功时，新创建的密钥的标识符。对于持久密钥，这是\p属性中定义的密钥标识符。\c 0失败。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_HANDLE\p source_key无效。\retval#PSA_ERROR_ALREADY_EXISTS这是一次创建持久密钥的尝试，并且已经存在具有给定标识符的持久密钥。\retval#PSA_ERROR_INVALID_ARGUMENT \p属性中的生存期或标识符无效。\retval#PSA_ERROR_INVALID_ARGUMENT源上的策略约束与\p属性中指定的策略约束不兼容。\retval#PSA_ERROR_INVALID_ARGUMENT\p attributes指定与源密钥的属性不匹配的密钥类型或密钥大小。\retval#PSA_ERROR_NOT_PERMITTED源密钥没有#PSA_key_USAGE_COPY用法标志。\retval#PSA_ERROR_NOT_PERMITTED源密钥不可导出，其生存期不允许将其复制到目标的生存期。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA _ERROR_INSUFFICE_STORAGE\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILUE\retval#PSA_RROR_DATA_INVALID\retval#1PSA_ERROR_DATA_CORRUPT\retval#3PSA_ERROR_STORAGE_FAILURE \retval#2PSA_ERROR_SERRUPTION_DETECTED \retval#8PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_copy_key(mbedtls_svc_key_id_t source_key,
                          const psa_key_attributes_t *attributes,
                          mbedtls_svc_key_id_t *target_key);


/**
 * \brief销毁一把钥匙。
 *
 * 此功能从易失性存储器和非易失性存储（如果适用）中销毁密钥。实施应尽最大努力确保关键材料无法回收。
 *
 * 此函数还清除任何元数据（如策略）并释放与密钥相关的资源。
 *
 * 如果密钥当前正在多部分操作中使用，那么销毁该密钥将导致多部分操作失败。
 *
 * \param key要擦除的密钥的标识符。如果这是\c 0，则不执行任何操作并返回#PSA_SUCCESS。
 *
 * \retval#PSA_SUCCESS\p密钥是一个有效标识符，它所指的密钥材料已被擦除。或者，\p键是\c 0。\retval#PSA_ERROR_NOT_PERMITTED由于策略或物理限制，无法擦除该键，因为它是只读的。\retval#PSA_ERROR_INVALID_HANDLE\p密钥不是有效标识符，也不是0。\retval#PSA _ERROR_COMMUNICATION_FAILURE与密码处理器通信失败。密钥材料可能仍然存在于密码处理器中。\retval#PSA_ERROR_DATA_INVALID此错误通常是由于明文存储后端上的存储损坏或试图读取由不兼容版本的库写入的数据而导致的。\retval#PSA_ERROR_STORAGE_FAILURE存储已损坏。即使在这个阶段，实施也应尽最大努力擦除关键材料，但应用程序应意识到，在这种情况下，可能无法保证关键材料不可恢复。\retval#PSA_ERROR_CORRUPTION_DETECTED发生了非存储损坏或通信故障的意外情况。密码处理器可能已被破坏。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_destroy_key(mbedtls_svc_key_id_t key);

/**@}*/

/** \defgroup import_export密钥导入和导出@{
 */

/**
 * \brief以二进制格式导入密钥。
 *
 * 此函数支持psa_export_key（）的任何输出。有关公钥的格式，请参阅psa_export_public_key（）的文档，有关其他密钥类型的格式，可参阅psa\uexport_key（。
 *
 * 密钥数据决定密钥大小。属性可以可选地指定密钥大小；在这种情况下，它必须匹配从密钥数据确定的大小。属性中的键大小为0表示键大小仅由键数据决定。
 *
 * 实现必须拒绝导入大小为0的密钥的尝试。
 *
 * 本规范支持每种密钥类型的单一格式。只要支持标准格式，实现可以支持其他格式。支持其他格式的实现应确保格式明确无误，以便将无效输入根据不同格式意外解释的风险降至最低。
 *
 * \param[in]attributes新密钥的属性。密钥大小始终由\p数据缓冲区确定。如果\p属性中的键大小为非零，则必须等于\p数据的大小。\param[out]key成功时，新创建的密钥的标识符。对于持久密钥，这是\p属性中定义的密钥标识符。\c 0失败。\param[in]data包含密钥数据的缓冲区。此缓冲区的内容根据\p属性中声明的类型进行解释。所有实现都必须至少支持所选类型的psa_export_key（）或psa_eexport_public_key（（）文档中描述的格式。实现可能允许其他格式，但应该是保守的：如果内容可能是错误的（例如错误的类型或截断的数据），实现应该在拒绝内容方面出错。\param data_length数据缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。如果密钥是持久的，则密钥材料和密钥的元数据已保存到持久存储中。\retval#PSA_ERROR_ALREADY_EXISTS这是一次创建持久密钥的尝试，并且已经存在具有给定标识符的持久密钥。\retval#PSA_ERROR_NOT_SUPPORTED一般实现或此特定持久位置不支持密钥类型或密钥大小。\retval#PSA_ERROR_INVALID_ARGUMENT键属性整体上无效。\retval#PSA_ERROR_INVALID_ARGUMENT密钥数据格式不正确。\retval#PSA_ERROR_INVALID_ARGUMENT \p属性中的大小为非零，与密钥数据的大小不匹配。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA _ERROR_INSUFFICE_STORAGE\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_DATA_CORRUPT\retval#PSA_RROR_DATA_INVALID\retval#1PSA_ERROR_STORAGE_FAILURE \retval#2PSA_ERROR_HARDWARE_FAILUE\retval#3PSA_ERROR_SERRUPTION_DETECTED \retval#8PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_import_key(const psa_key_attributes_t *attributes,
                            const uint8_t *data,
                            size_t data_length,
                            mbedtls_svc_key_id_t *key);



/**
 * \brief以二进制格式导出密钥。
 *
 * 此函数的输出可以传递给psa_import_key（）以创建等效对象。
 *
 * 如果psa_import_key（）的实现支持此处指定的格式之外的其他格式，则psa_ixport_key（（）的输出必须使用此处指定的表示，而不是原始表示。
 *
 * 对于标准密钥类型，输出格式如下：
 *
 * -对于对称密钥（包括MAC密钥），格式为密钥的原始字节。
 * -对于DES，密钥数据由8个字节组成。奇偶校验位必须正确。
 * -对于三重DES，格式是两个或三个DES密钥的级联。
 * -对于RSA密钥对（#PSA_key_TYPE_RSA_key_PAIR），格式是PKCS\#1（RFC 8017）定义为“RSAPrivateKey”的表示的非加密DER编码，版本0.``RSAPrivateKey:：=SEQUENCE｛版本INTEGER，--必须是0模INTEGER、--n publicExponent INTEGER和--e privateExponent INTEGER、--d prime 1 INTEGER或--p prime 2 INTEGER；--q exponent 1 INTEGGER、--d mod（p-1）exponent 2 INTEGR、--d mod（q-1）系数INTEGER以及--（q的倒数）mod p｝```
 * -对于椭圆曲线密钥对（#PSA_key_TYPE_IS_ECC_key_PAIR为真的密钥类型），格式是将私有值表示为“上限（m/8）”字节字符串，其中“m”是与曲线相关联的比特大小，即曲线坐标字段顺序的比特大小。对于Montgomery曲线（曲线类型“PSA_ECC_FAMILY_CURVEXXX”），此字节字符串的顺序为小端，对于Weierstrass曲线（曲线类别“PSA_ECC_FAMILY_SECTXXXX”、“PSA_ACC_FAMILY_SECPXXXX”和“PSA_CC_FAMIL_BRAINPOOL_PXXX”），则为大端。对于Weierstrass曲线，这是RFC 5915定义的“ECPrivateKey”格式的“privateKey”字段的内容。对于Montgomery曲线，格式由RFC 7748定义，输出根据§5进行屏蔽。对于扭曲的Edwards曲线，私钥由RFC 8032定义（Edwards25519为32字节字符串，Edwards448为57字节字符串）。
 * -对于Diffie-Hellman密钥交换密钥对（#PSA_key_TYPE_IS_DH_key_PAIR为真的密钥类型），格式是将私钥“x”表示为大端字节字符串。字节字符串的长度是以字节为单位的私钥大小（前导零不被去除）。
 * -对于公钥（#PSA_key_TYPE_IS_public_key为真的密钥类型），格式与PSA_export_public_key（）相同。
 *
 * 密钥上的策略必须设置用法标志#PSA_key_usage_EXPORT。
 *
 * \param key要导出的密钥的标识符。它必须允许使用#PSA_KEY_usage_EXPORT，除非它是公钥。\param[out]data要写入密钥数据的缓冲区。\param data_size数据缓冲区的大小（字节）。\param[out]data_length成功时，构成密钥数据的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED密钥没有#PSA_key_USAGE_EXPORT标志。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_BUFFER_TOO_SMALL数据缓冲区的大小太小。您可以通过调用#PSA_EXPORT_KEY_OUTPUT_size（\c类型，\c位）来确定足够的缓冲区大小，其中\c类型是密钥类型，而\c位是以位为单位的密钥大小。\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILUE\retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_STORAGE_FAILURE \retval#1PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_RROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_export_key(mbedtls_svc_key_id_t key,
                            uint8_t *data,
                            size_t data_size,
                            size_t *data_length);

/**
 * \brief以二进制格式导出公钥或密钥对的公共部分。
 *
 * 此函数的输出可以传递给psa_import_key（），以创建一个与公钥等效的对象。
 *
 * 本规范支持每种密钥类型的单一格式。只要支持标准格式，实现可以支持其他格式。支持其他格式的实现应确保格式明确无误，以便将无效输入根据不同格式意外解释的风险降至最低。
 *
 * 对于标准密钥类型，输出格式如下：
 * -对于RSA公钥（#PSA_KEY_TYPE_RSA_public_KEY），RFC 3279&sect；2.3.1作为`RSAPublicKey`.```RSAPublicKey:：=序列｛模整数，--n公共指数整数｝--e```
 * -对于扭曲Edwards曲线上的椭圆曲线密钥（密钥类型#PSA_key_TYPE_IS_ECC_PUBLIC_key为真，#PSA_key _TYPE_ECC_GET_FAMILY返回#PSA_EC_FAMILY_TWITED_Edwards），公钥由RFC 8032定义（Edwards25519为32字节字符串，Edwards448为57字节字符串）。
 * -对于其他椭圆曲线公钥（#PSA_key_TYPE_IS_ECC_public_key为真的密钥类型），格式为SEC1&sect；2.3.3作为ECPoint的内容。设“m”是与曲线相关联的比特大小，即“F_q”上的曲线的“q”的比特大小。该陈述包括：
 *      -字节0x04；
 *      -“x_P”作为“上限（m/8）”字节字符串，大端；
 *      -“y_P”作为“上限（m/8）”字节字符串，大端。
 * -对于Diffie-Hellman密钥交换公钥（#PSA_key_TYPE_IS_DH_public_key为真的密钥类型），格式为公钥“y=g^xMod p”的大端字节字符串表示。字节字符串的长度是以字节为单位的基素数“p”的长度。
 *
 * 始终允许导出公钥对象或密钥对的公共部分，而不考虑密钥的使用标志。
 *
 * \param key要导出的密钥的标识符。\param[out]data要写入密钥数据的缓冲区。\param data_size数据缓冲区的大小（字节）。\param[out]data_length成功时，构成密钥数据的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSA错误_INVALID_HANDLE\retval#PSA_ERROR_INVALID_ARGUMENT密钥既不是公钥也不是密钥对。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_BUFFER_TOO_SMALL数据缓冲区的大小太小。您可以通过调用#PSA_EXPORT_KEY_OUTPUT_size（#PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR（\c类型），\c位）来确定足够的缓冲区大小，其中\c类型是密钥类型，而\c位是以位为单位的密钥大小。\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILUE\retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_STORAGE_FAILURE \retval#1PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_RROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_export_public_key(mbedtls_svc_key_id_t key,
                                   uint8_t *data,
                                   size_t data_size,
                                   size_t *data_length);



/**@}*/

/** \defgroup哈希消息摘要@{
 */

/** 计算消息的哈希（摘要）。
 *
 * \注意：要根据预期值验证消息的哈希值，请改用psa_hash_compare（）。
 *
 * \param alg要计算的哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p alg）为真）。\param[in]输入缓冲区，包含要哈希的消息。\param input_length输入缓冲区的大小（字节）。\param[out]hash要写入哈希的缓冲区。\param hash_size \p哈希缓冲区的大小（字节）。\param[out]hash_length成功时，构成哈希值的字节数。这始终是#PSA_HAH_LENGTH（\p alg）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是哈希算法。\retval#PSA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_BUFFER_TOO_SMALL\p hash_size太小\retval#PSA _ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_RROR_HARDWARE_FAILURE \retval#1PSA _ERROR _CORRUPTION_DETECTED \retval#2SA _ERROR_inSUFFIEM_EMORY\ retval#PS _ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_hash_compute(psa_algorithm_t alg,
                              const uint8_t *input,
                              size_t input_length,
                              uint8_t *hash,
                              size_t hash_size,
                              size_t *hash_length);

/** 计算消息的哈希（摘要）并将其与参考值进行比较。
 *
 * \param alg要计算的哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p alg）为真）。\param[in]输入缓冲区，包含要哈希的消息。\param input_length输入缓冲区的大小（字节）。\param[out]包含预期哈希值的哈希缓冲区。\param hash_length哈希缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS预期的哈希值与输入的实际哈希值相同。\retval#PSA_ERROR_INVALID_SIGNATURE消息的哈希值计算成功，但与预期的哈希值不同。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是哈希算法。\retval#PSA_ERROR_INVALID_ARGUMENT\p input_length或\p hash_length与\p alg\p的哈希大小不匹配#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_RROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR _INSUFFICE_MEMORY\retval#1PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_hash_compare(psa_algorithm_t alg,
                              const uint8_t *input,
                              size_t input_length,
                              const uint8_t *hash,
                              size_t hash_length);

/** 多部分哈希操作的状态数据结构的类型。
 *
 * 在调用哈希操作对象上的任何函数之前，应用程序必须通过以下任何方式对其进行初始化：
 * -将结构设置为所有位零，例如：\code psa_hash_operation_t operation；memset（&operation，0，sizeof（operation））；\结束代码
 * -将结构初始化为逻辑零值，例如：\code psa_hash_operation_t operation={0}；\结束代码
 * -将结构初始化为初始值设定项#PSA_HASH_OPERATION_INIT，例如：\code PSA_HASH_OPERATION_t OPERATION=PSA_HAH_OPERATION_INIT；\结束代码
 * -将函数psa_hash_operation_init（）的结果分配给结构，例如：\code psa_hhash_operation_t operation；operation=psa_hash_operation_init（）；\结束代码
 *
 * 这是一个实现定义的\c结构。应用程序不应对该结构的内容进行任何假设，除非特定实现的文档有指示。*/
typedef struct psa_hash_operation_s psa_hash_operation_t;

/** \定义PSA_HAH_OPERATION_INIT
 *
 * 此宏为#psa_hash_operation_t类型的哈希操作对象返回合适的初始值设定项。
 */
#ifdef __DOXYGEN_ONLY__
/* 这是用于文档目的的示例定义。实现应在“crypt_struct.h”中定义适当的值。
 */
#define PSA_HASH_OPERATION_INIT {0}
#endif

/** 返回哈希操作对象的初始值。
 */
static psa_hash_operation_t psa_hash_operation_init(void);

/** 设置多部分哈希操作。
 *
 * 计算哈希（消息摘要）的操作顺序如下：
 * -#分配一个操作对象，该对象将传递给此处列出的所有函数。
 * -#使用#psa_hash_operation_t文档中描述的方法之一初始化操作对象，例如#psa_HAH_operation_INIT。
 * -#调用psa_hash_setup（）指定算法。
 * -#调用psa_hash_update（）零次，一次或多次，每次传递一个消息片段。计算的哈希值是这些消息按顺序串联的哈希值。
 * -#要计算哈希，请调用psa_hash_finish（）。要将哈希值与预期值进行比较，请调用psa_hash_verify（）。
 *
 * 如果在调用psa_hash_setup（）之后的任何步骤中发生错误，则需要通过调用psa\uhash_abort（）来重置操作。操作初始化后，应用程序可以随时调用psa_hash_abort（）。
 *
 * 成功调用psa_hash_setup（）后，应用程序必须最终终止操作。以下事件将终止操作：
 * -成功调用psa_hash_finish（）或psa_hhash_verify（）。
 * -对psa_hash_abort（）的调用。
 *
 * \param[in，out]operation要设置的操作对象。它必须已根据#psa_hash_operation_t文档进行初始化，但尚未使用。\param alg要计算的哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不是受支持的哈希算法。\retval#PSA_ERROR_INVALID_ARGUMENT\p alg不是哈希算法。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA_ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_hash_setup(psa_hash_operation_t *operation,
                            psa_algorithm_t alg);

/** 将消息片段添加到多部分哈希操作。
 *
 * 应用程序必须在调用此函数之前调用psa_hash_setup（）。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_hash_abort（）中止。
 *
 * \param[in，out]操作活动哈希操作。\param[in]输入缓冲区，包含要哈希的消息片段。\param input_length输入缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为活动状态）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA_ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_hash_update(psa_hash_operation_t *operation,
                             const uint8_t *input,
                             size_t input_length);

/** 完成消息哈希的计算。
 *
 * 应用程序必须在调用此函数之前调用psa_hash_setup（）。此函数计算通过将传递给前面调用psa_hash_update（）的输入串联起来形成的消息的哈希值。
 *
 * 当此函数成功返回时，操作将变为非活动状态。如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_hash_abort（）中止。
 *
 * \警告应用程序如果期望哈希值为特定值，则不应调用此函数。改为调用psa_hash_verify（）。请注意，将完整性或真实性数据（如哈希值）与函数（如\c memcmp）进行比较是有风险的，因为比较所花费的时间可能会泄漏有关哈希数据的信息，从而使攻击者能够猜测有效的哈希，从而绕过安全控制。
 *
 * \param[in，out]操作活动哈希操作。\param[out]hash要写入哈希的缓冲区。\param hash_size \p哈希缓冲区的大小（字节）。\param[out]hash_length成功时，构成哈希值的字节数。这始终是#PSA_HAH_LENGTH（\c alg），其中\c alg是计算的哈希算法。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为活动状态）。\retval#PSA_ERROR_BUFFER_TOO_SMALL哈希缓冲区的大小太小。您可以通过调用#PSA_HASH_LENGTH（\c alg）来确定足够的缓冲区大小，其中\c alh是计算的哈希算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA_ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_hash_finish(psa_hash_operation_t *operation,
                             uint8_t *hash,
                             size_t hash_size,
                             size_t *hash_length);

/** 完成消息哈希的计算，并将其与预期值进行比较。
 *
 * 应用程序必须在调用此函数之前调用psa_hash_setup（）。此函数计算通过将传递给前面调用psa_hash_update（）的输入串联起来形成的消息的哈希值。然后，它将计算的哈希值与作为参数传递给该函数的预期哈希值进行比较。
 *
 * 当此函数成功返回时，操作将变为非活动状态。如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_hash_abort（）中止。
 *
 * \注：实现应尽最大努力确保在恒定时间内执行实际哈希和预期哈希之间的比较。
 *
 * \param[in，out]操作活动哈希操作。\param[in]包含预期哈希值的哈希缓冲区。\param hash_length哈希缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS预期的哈希值与消息的实际哈希值相同。\retval#PSA_ERROR_INVALID_SIGNATURE消息的哈希值计算成功，但与预期的哈希值不同。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为活动状态）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA_ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_hash_verify(psa_hash_operation_t *operation,
                             const uint8_t *hash,
                             size_t hash_length);

/** 中止哈希操作。
 *
 * 中止操作将释放所有相关资源，但操作结构本身除外。一旦中止，可以通过再次调用psa_hash_setup（）将操作对象重新用于另一个操作。
 *
 * 在通过#psa_hash_operation_t中描述的方法之一初始化操作对象之后，可以随时调用此函数。
 *
 * 特别是，在通过调用psa_hash_abort（）、psa_hhash_finish（）或psa_has_verify（）终止操作后调用psa\uhash_abor（）是安全的，不会产生任何影响。
 *
 * \param[in，out]操作已初始化哈希操作。
 *
 * \retval#PSA_SUCCESS\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_hash_abort(psa_hash_operation_t *operation);

/** 克隆哈希操作。
 *
 * 此函数将正在进行的哈希操作的状态复制到新的操作对象。换句话说，此函数相当于使用与设置source_operation相同的算法在target_operation上调用psa_hash_setup（），然后使用传递给source_operaction的相同输入在target_ooperation上调用psa_hash_update（）。此函数返回后，两个对象是独立的，即涉及其中一个对象的后续调用不会影响另一个对象。
 *
 * \param[in]source_operation要克隆的活动哈希操作。\param[in，out]target_operation要设置的操作对象。它必须初始化，但不是活动的。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_BAD_STATE源操作状态无效（必须为活动状态）。\retval#PSA_ERROR_BAD_STATE \p target_operation状态无效（必须为非活动状态）。\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_RROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_hash_clone(const psa_hash_operation_t *source_operation,
                            psa_hash_operation_t *target_operation);

/**@}*/

/** \defgroup MAC消息认证码@{
 */

/** 计算消息的MAC（消息认证码）。
 *
 * \注意：要根据预期值验证消息的MAC，请改用psa_MAC_verify（）。请注意，将完整性或真实性数据（如MAC值）与函数（如\c memcmp）进行比较是有风险的，因为比较所花费的时间可能会泄露有关MAC值的信息，从而使攻击者能够猜测有效的MAC，从而绕过安全控制。
 *
 * \param key用于操作的密钥的标识符。它必须允许使用PSA_KEY_usage_SIGN_MESSAGE。\param alg要计算的MAC算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_MAC（\p alg）为真）。\param[in]包含输入消息的输入缓冲区。\param input_length输入缓冲区的大小（字节）。\param[out]mac要写入mac值的缓冲区。\param mac_size \p mac缓冲区的大小（字节）。\param[out]mac_length成功时，构成mac值的字节数。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是MAC算法。\retval#PSA_ERROR_BUFFER_TOO_SMALL\p mac_size太小\retval#PSA _ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILUE\retval#PSA_RROR_CORRUPTION_DETECTED\retval＃PSA_ERROR_STORAGE_FAILURE无法从存储中检索密钥。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_mac_compute(mbedtls_svc_key_id_t key,
                             psa_algorithm_t alg,
                             const uint8_t *input,
                             size_t input_length,
                             uint8_t *mac,
                             size_t mac_size,
                             size_t *mac_length);

/** 计算消息的MAC并将其与参考值进行比较。
 *
 * \param key用于操作的密钥的标识符。它必须允许使用PSA_KEY_usage_VERIFY_MESSAGE。\param alg要计算的MAC算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_MAC（\p alg）为真）。\param[in]包含输入消息的输入缓冲区。\param input_length输入缓冲区的大小（字节）。\param[out]mac缓冲区，包含预期的mac值。\param mac_length \p mac缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS预期MAC与输入的实际MAC相同。\retval#PSA_ERROR_INVALID_SIGNATURE消息的MAC已成功计算，但与预期值不同。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是MAC算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE无法从存储中检索密钥。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_mac_verify(mbedtls_svc_key_id_t key,
                            psa_algorithm_t alg,
                            const uint8_t *input,
                            size_t input_length,
                            const uint8_t *mac,
                            size_t mac_length);

/** 多部分MAC操作的状态数据结构的类型。
 *
 * 在调用MAC操作对象上的任何函数之前，应用程序必须通过以下任何方式对其进行初始化：
 * -将结构设置为所有位零，例如：\code psa_mac_operation_t operation；memset（&operation，0，sizeof（operation））；\结束代码
 * -将结构初始化为逻辑零值，例如：\code psa_mac_operation_t operation={0}；\结束代码
 * -将结构初始化为初始值设定项#PSA_MAC_OPERATION_INIT，例如：\code PSA_MAC_OPERATION_t OPERATION=PSA_MAC-OPERATION_INIT；\结束代码
 * -将函数psa_mac_operation_init（）的结果分配给结构，例如：\code psa_mac_operation_t operation；operation=psa_mac_operation_init（）；\结束代码
 *
 * 这是一个实现定义的\c结构。应用程序不应对该结构的内容进行任何假设，除非特定实现的文档有指示。*/
typedef struct psa_mac_operation_s psa_mac_operation_t;

/** \定义PSA_MAC_OPERATION_INIT
 *
 * 此宏为#psa_MAC_operation_t类型的MAC操作对象返回合适的初始值设定项。
 */
#ifdef __DOXYGEN_ONLY__
/* 这是用于文档目的的示例定义。实现应在“crypt_struct.h”中定义适当的值。
 */
#define PSA_MAC_OPERATION_INIT {0}
#endif

/** 返回MAC操作对象的初始值。
 */
static psa_mac_operation_t psa_mac_operation_init(void);

/** 设置多部分MAC计算操作。
 *
 * 此函数设置字节字符串的MAC（消息验证码）的计算。要根据预期值验证消息的MAC，请改用psa_MAC_verify_setup（）。
 *
 * 计算MAC的操作顺序如下：
 * -#分配一个操作对象，该对象将传递给此处列出的所有函数。
 * -#使用#psa_mac_operation_t文档中描述的方法之一初始化操作对象，例如#psa_mac_operation_INIT。
 * -#调用psa_mac_sign_setup（）指定算法和密钥。
 * -#调用psa_mac_update（）零次，一次或多次，每次传递一个消息片段。所计算的MAC是这些消息按顺序串联的MAC。
 * -#在消息末尾，调用psa_mac_sign_finish（）完成mac值的计算并检索它。
 *
 * 如果在调用psa_mac_sign_setup（）之后的任何步骤发生错误，则需要通过调用psa_amac_abort（）来重置操作。操作初始化后，应用程序可以随时调用psa_mac_abort（）。
 *
 * 成功调用psa_mac_sign_setup（）后，应用程序最终必须通过以下方法之一终止操作：
 * -成功调用psa_mac_sign_finish（）。
 * -对psa_mac_abort（）的调用。
 *
 * \param[in，out]operation要设置的操作对象。它必须已根据#psa_mac_operation_t文档进行初始化，但尚未使用。\param key用于操作的密钥的标识符。它必须保持有效，直到操作终止。它必须允许使用PSA_KEY_usage_SIGN_MESSAGE。\param alg要计算的MAC算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_MAC（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是MAC算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE无法从存储中检索密钥。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_mac_sign_setup(psa_mac_operation_t *operation,
                                mbedtls_svc_key_id_t key,
                                psa_algorithm_t alg);

/** 设置多部分MAC验证操作。
 *
 * 此函数根据预期值设置字节字符串的MAC（消息验证码）验证。
 *
 * 验证MAC的操作顺序如下：
 * -#分配一个操作对象，该对象将传递给此处列出的所有函数。
 * -#使用#psa_mac_operation_t文档中描述的方法之一初始化操作对象，例如#psa_mac_operation_INIT。
 * -#调用psa_mac_verify_setup（）指定算法和密钥。
 * -#调用psa_mac_update（）零次，一次或多次，每次传递一个消息片段。所计算的MAC是这些消息按顺序串联的MAC。
 * -#在消息结束时，调用psa_mac_verify_finish（）完成计算消息的实际mac，并根据预期值进行验证。
 *
 * 如果在调用psa_mac_verify_setup（）之后的任何步骤发生错误，则需要通过调用psa_amac_abort（）来重置操作。操作初始化后，应用程序可以随时调用psa_mac_abort（）。
 *
 * 成功调用psa_mac_verify_setup（）后，应用程序最终必须通过以下方法之一终止操作：
 * -成功调用psa_mac_verify_finish（）。
 * -对psa_mac_abort（）的调用。
 *
 * \param[in，out]operation要设置的操作对象。它必须已根据#psa_mac_operation_t文档进行初始化，但尚未使用。\param key用于操作的密钥的标识符。它必须保持有效，直到操作终止。它必须允许使用PSA_KEY_usage_VERIFY_MESSAGE。\param alg要计算的MAC算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_MAC（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\c密钥与\c alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\c alg不受支持或不是MAC算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE无法从存储中检索密钥\retval#8PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_mac_verify_setup(psa_mac_operation_t *operation,
                                  mbedtls_svc_key_id_t key,
                                  psa_algorithm_t alg);

/** 向多部分MAC操作添加消息片段。
 *
 * 在调用此函数之前，应用程序必须调用psa_mac_sign_setup（）或psa_mac_verify_setup）。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_mac_abort（）中止。
 *
 * \param[in，out]操作活动MAC操作。\param[in]输入缓冲区，包含要添加到MAC计算中的消息片段。\param input_length输入缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为活动状态）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_mac_update(psa_mac_operation_t *operation,
                            const uint8_t *input,
                            size_t input_length);

/** 完成消息MAC的计算。
 *
 * 应用程序必须在调用此函数之前调用psa_mac_sign_setup（）。此函数计算通过将传递给前面调用psa_MAC_update（）的输入串联起来形成的消息的MAC。
 *
 * 当此函数成功返回时，操作将变为非活动状态。如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_mac_abort（）中止。
 *
 * \警告应用程序如果期望MAC的特定值，则不应调用此函数。改为调用psa_mac_verify_finish（）。请注意，将完整性或真实性数据（如MAC值）与函数（如\c memcmp）进行比较是有风险的，因为比较所花费的时间可能会泄露有关MAC值的信息，从而使攻击者能够猜测有效的MAC，从而绕过安全控制。
 *
 * \param[in，out]操作活动MAC操作。\param[out]mac要写入mac值的缓冲区。\param mac_size \p mac缓冲区的大小（字节）。\param[out]mac_length成功时，构成mac值的字节数。这始终是#PSA_MAC_LENGTH（\c key_type，\c key_bits，\c alg），其中\c keytype和\c key_bits分别是密钥的类型和比特大小，\c alg是计算的MAC算法。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须是活动的mac符号操作）。\retval#PSA_ERROR_BUFFER_TOO_SMALL mac缓冲区的大小太小。您可以通过调用PSA_MAC_LENGTH（）来确定足够的缓冲区大小。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_mac_sign_finish(psa_mac_operation_t *operation,
                                 uint8_t *mac,
                                 size_t mac_size,
                                 size_t *mac_length);

/** 完成消息MAC的计算，并将其与预期值进行比较。
 *
 * 应用程序必须在调用此函数之前调用psa_mac_verify_setup（）。此函数计算通过将传递给前面调用psa_MAC_update（）的输入串联起来形成的消息的MAC。然后，它将计算的MAC与作为参数传递给该函数的预期MAC进行比较。
 *
 * 当此函数成功返回时，操作将变为非活动状态。如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_mac_abort（）中止。
 *
 * \注：实施应尽最大努力确保在恒定时间内进行实际MAC和预期MAC之间的比较。
 *
 * \param[in，out]操作活动MAC操作。\param[in]mac缓冲区，包含预期的mac值。\param mac_length \p mac缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS预期MAC与消息的实际MAC相同。\retval#PSA_ERROR_INVALID_SIGNATURE已成功计算消息的MAC，但它与预期的MAC不同。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须是活动的mac验证操作）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_mac_verify_finish(psa_mac_operation_t *operation,
                                   const uint8_t *mac,
                                   size_t mac_length);

/** 中止MAC操作。
 *
 * 中止操作将释放所有相关资源，但操作结构本身除外。一旦中止，可以通过再次调用psa_mac_sign_setup（）或psa_mac_verify_setup）将操作对象重新用于另一个操作。
 *
 * 在通过#psa_mac_operation_t中描述的方法之一初始化操作对象之后，可以随时调用此函数。
 *
 * 特别是，在通过调用psa_mac_abort（）、psa_mac_sign_finish（）或psa_max_verify_finish）终止操作后调用psa_amac_abort（）是安全的，不会产生任何影响。
 *
 * \param[in，out]操作已初始化MAC操作。
 *
 * \retval#PSA_SUCCESS\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_mac_abort(psa_mac_operation_t *operation);

/**@}*/

/** \解群密码对称密码@{
 */

/** 使用对称密码对消息进行加密。
 *
 * 此函数使用随机IV（初始化向量）加密消息。使用带有#psa_ccipher_operation_t对象的多部分操作接口来提供其他形式的IV。
 *
 * \param key用于操作的密钥的标识符。它必须允许使用#PSA_KEY_usage_ENCRYPT。\param alg要计算的密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。\param[in]输入缓冲区，包含要加密的消息。\param input_length输入缓冲区的大小（字节）。\param[out]输出要写入输出的缓冲区。输出包含IV，后跟正确的密文。\param output_size输出缓冲区的大小（字节）。\param[out]output_length成功时，构成输出的字节数。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是密码算法。\retval#PSA_ERROR_BUFFER_TOO_SMALL\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA _ERROR_HARDWARE_FAILURE \retval#PSA_RROR_CORRUPTION_DETECTED \retval#1PSA_ERROR_STORAGE_FAILULE\retval#2PSA_ERROR-BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_cipher_encrypt(mbedtls_svc_key_id_t key,
                                psa_algorithm_t alg,
                                const uint8_t *input,
                                size_t input_length,
                                uint8_t *output,
                                size_t output_size,
                                size_t *output_length);

/** 使用对称密码解密消息。
 *
 * 此函数用于解密使用对称密码加密的消息。
 *
 * \param key用于操作的密钥的标识符。它必须保持有效，直到操作终止。它必须允许使用#PSA_KEY_usage_DECRYPT。\param alg要计算的密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。\param[in]输入缓冲区，包含要解密的消息。这由IV和密文组成。\param input_length输入缓冲区的大小（字节）。\param[out]输出要写入明文的缓冲区。\param output_size输出缓冲区的大小（字节）。\param[out]output_length成功时，构成输出的字节数。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是密码算法。\retval#PSA_ERROR_BUFFER_TOO_SMALL\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA _ERROR_HARDWARE_FAILURE \retval#PSA_RROR_STORAGE_FAILUURE\retval#1PSA_ERROR_RERRUPTION_DETECTED \retval#2PSA_ERROR-BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_cipher_decrypt(mbedtls_svc_key_id_t key,
                                psa_algorithm_t alg,
                                const uint8_t *input,
                                size_t input_length,
                                uint8_t *output,
                                size_t output_size,
                                size_t *output_length);

/** 多部分密码操作的状态数据结构的类型。
 *
 * 在调用密码操作对象上的任何函数之前，应用程序必须通过以下任一方式对其进行初始化：
 * -将结构设置为所有位零，例如：\code psa_ccipher_operation_t operation；memset（&operation，0，sizeof（operation））；\结束代码
 * -将结构初始化为逻辑零值，例如：\code psa_ccipher_operation_t operation={0}；\结束代码
 * -将结构初始化为初始值设定项#PSA_CIPHER_OPERATION_INIT，例如：\code PSA_ccipher_OPERATION_t OPERATION=PSA_CIPER_OPERATIION_INIT；\结束代码
 * -将函数psa_cher_operation_init（）的结果分配给结构，例如：\code psa_cher _operation_t operation；operation=psa_cher_operation_init（）；\结束代码
 *
 * 这是一个实现定义的\c结构。应用程序不应对该结构的内容进行任何假设，除非特定实现的文档有指示。*/
typedef struct psa_cipher_operation_s psa_cipher_operation_t;

/** \定义PSA_CIPHER_OPERATION_INIT
 *
 * 此宏为#psa_cher_operation_t类型的密码操作对象返回合适的初始值设定项。
 */
#ifdef __DOXYGEN_ONLY__
/* 这是用于文档目的的示例定义。实现应在“crypt_struct.h”中定义适当的值。
 */
#define PSA_CIPHER_OPERATION_INIT {0}
#endif

/** 返回密码操作对象的初始值。
 */
static psa_cipher_operation_t psa_cipher_operation_init(void);

/** 设置多部分对称加密操作的密钥。
 *
 * 使用对称密码加密消息的操作顺序如下：
 * -#分配一个操作对象，该对象将传递给此处列出的所有函数。
 * -#使用#psa_cher_operation_t文档中描述的方法之一初始化操作对象，例如#psa_cipher_operation_INIT。
 * -#调用psa_cipher_encrypt_setup（）指定算法和密钥。
 * -#调用psa_cher_generate.iv（）或psa_cher _set_iv（）生成或设置iv（初始化向量）。除非正在实现的协议需要特定的iv值，否则应使用psa_cipher_generate.iv（）。
 * -#调用psa_cipher_update（）零次，一次或多次，每次传递一个消息片段。
 * -#调用psa_cipher_finish（）。
 *
 * 如果在调用psa_ccipher_encrypt_setup（）之后的任何步骤中发生错误，则需要通过调用psa\ycher_abort（）来重置操作。应用程序可以在操作初始化后的任何时间调用psa_ccipher_abort（）。
 *
 * 在成功调用psa_ccipher_encrypt_setup（）后，应用程序必须最终终止操作。以下事件将终止操作：
 * -成功调用psa_cipher_finish（）。
 * -对psa_icipher_abort（）的调用。
 *
 * \param[in，out]operation要设置的操作对象。它必须已根据#psa_ccipher_operation_t文档进行初始化，但尚未使用。\param key用于操作的密钥的标识符。它必须保持有效，直到操作终止。它必须允许使用#PSA_KEY_usage_ENCRYPT。\param alg要计算的密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是密码算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_STORAGE_FAILUE\retval＃PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_cipher_encrypt_setup(psa_cipher_operation_t *operation,
                                      mbedtls_svc_key_id_t key,
                                      psa_algorithm_t alg);

/** 为多部分对称解密操作设置密钥。
 *
 * 使用对称密码解密消息的操作顺序如下：
 * -#分配一个操作对象，该对象将传递给此处列出的所有函数。
 * -#使用#psa_cher_operation_t文档中描述的方法之一初始化操作对象，例如#psa_cipher_operation_INIT。
 * -#调用psa_ccipher_decrypt_setup（）指定算法和密钥。
 * -#使用iv（初始化向量）调用psa_cher_set_iv（）进行解密。如果IV是在密文前面加上的，那么可以在包含IV和消息开头的缓冲区上调用psa_cher_update（）。
 * -#调用psa_cipher_update（）零次，一次或多次，每次传递一个消息片段。
 * -#调用psa_cipher_finish（）。
 *
 * 如果在调用psa_ccipher_decrypt_setup（）之后的任何步骤中发生错误，则需要通过调用psa\ycher_abort（）来重置操作。应用程序可以在操作初始化后的任何时间调用psa_ccipher_abort（）。
 *
 * 成功调用psa_ccipher_decrypt_setup（）后，应用程序必须最终终止操作。以下事件将终止操作：
 * -成功调用psa_cipher_finish（）。
 * -对psa_icipher_abort（）的调用。
 *
 * \param[in，out]operation要设置的操作对象。它必须已根据#psa_ccipher_operation_t文档进行初始化，但尚未使用。\param key用于操作的密钥的标识符。它必须保持有效，直到操作终止。它必须允许使用#PSA_KEY_usage_DECRYPT。\param alg要计算的密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是密码算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_STORAGE_FAILUE\retval＃PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_cipher_decrypt_setup(psa_cipher_operation_t *operation,
                                      mbedtls_svc_key_id_t key,
                                      psa_algorithm_t alg);

/** 为对称加密操作生成IV。
 *
 * 此函数根据所选算法、密钥类型和密钥大小为加密操作生成随机IV（初始化向量）、随机数或初始计数器值。
 *
 * 在调用此函数之前，应用程序必须调用psa_cipher_encrypt_setup（）。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_ccipher_abort（）中止。
 *
 * \param[in，out]操作活动密码操作。\param[out]iv要写入生成的iv的缓冲区。\param iv_size \p iv缓冲区的大小（以字节为单位）。\param[out]iv_length成功时，生成的iv的字节数。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须是活动状态，且未设置IV）。\retval#PSA_ERROR_BUFFER_TOO_SMALL缓冲区的大小太小。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_cipher_generate_iv(psa_cipher_operation_t *operation,
                                    uint8_t *iv,
                                    size_t iv_size,
                                    size_t *iv_length);

/** 为对称加密或解密操作设置IV。
 *
 * 此函数设置加密或解密操作的IV（初始化向量）、随机数或初始计数器值。
 *
 * 在调用此函数之前，应用程序必须调用psa_cipher_encrypt_setup（）。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_ccipher_abort（）中止。
 *
 * \注意：加密时，应用程序应使用psa_ccipher_generate.iv（）而不是此函数，除非实现需要非随机iv的协议。
 *
 * \param[in，out]操作活动密码操作。\param[in]iv包含要使用的iv的缓冲区。\param iv_length iv的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（它必须是活动密码加密操作，没有设置IV）。\retval#PSA_ERROR_INVALID_ARGUMENT所选算法不接受\p iv的大小，或者所选算法不使用IV.\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA _ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA_ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_STORAGE_FAILUE\retval*PSA_ERROR_BAD_STATE该库以前未由PSA_cryto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_cipher_set_iv(psa_cipher_operation_t *operation,
                               const uint8_t *iv,
                               size_t iv_length);

/** 在活动密码操作中加密或解密消息片段。
 *
 * 在调用此函数之前，您必须：1.调用psa_cipher_encrypt_setup（）或psa_crypt_decrypt_setup（）。设置函数的选择决定了该函数是加密还是解密其输入。2.如果算法需要IV，请调用psa_ccipher_generate.IV（）（加密时建议使用）或psa_cher_set_IV（）。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_ccipher_abort（）中止。
 *
 * \param[in，out]操作活动密码操作。\param[in]输入缓冲区，包含要加密或解密的消息片段。\param input_length输入缓冲区的大小（字节）。\param[out]输出要写入输出的缓冲区。\param output_size输出缓冲区的大小（字节）。\param[out]output_length成功时，构成返回输出的字节数。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（它必须是活动的，如果算法需要，还必须设置IV）。\retval#PSA_ERROR_BUFFER_TOO_SMALL输出缓冲区的大小太小。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_cipher_update(psa_cipher_operation_t *operation,
                               const uint8_t *input,
                               size_t input_length,
                               uint8_t *output,
                               size_t output_size,
                               size_t *output_length);

/** 在密码操作中完成对消息的加密或解密。
 *
 * 在调用此函数之前，应用程序必须调用psa_cipher_encrypt_setup（）或psa_crypt_decrypt_setup（）。设置函数的选择决定了该函数是加密还是解密其输入。
 *
 * 此函数完成对消息的加密或解密，该消息是通过将传递给前面调用psa_cipher_update（）的输入串联起来而形成的。
 *
 * 当此函数成功返回时，操作将变为非活动状态。如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_ccipher_abort（）中止。
 *
 * \param[in，out]操作活动密码操作。\param[out]输出要写入输出的缓冲区。\param output_size输出缓冲区的大小（字节）。\param[out]output_length成功时，构成返回输出的字节数。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_ARGUMENT传递给此操作的总输入大小对于此特定算法无效。例如，该算法是基于分组密码的，需要整数个块，但总输入大小不是块大小的倍数。\retval#PSA_ERROR_INVALID_PADDING这是对包含填充的算法的解密操作，并且密文不包含有效填充。\retval#PSA_ERROR_BAD_STATE操作状态无效（它必须是活动的，如果算法需要，还必须设置IV）。\retval#PSA_ERROR_BUFFER_TOO_SMALL输出缓冲区的大小太小。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_cipher_finish(psa_cipher_operation_t *operation,
                               uint8_t *output,
                               size_t output_size,
                               size_t *output_length);

/** 中止密码操作。
 *
 * 中止操作将释放所有相关资源，但操作结构本身除外。一旦中止，可以通过再次调用psa_cipher_encrypt_setup（）或psa_crypt_decrypt_setup（），将操作对象重新用于另一个操作。
 *
 * 在操作对象初始化后，您可以随时调用此函数，如#psa_cher_operation_t中所述。
 *
 * 特别是，在通过调用psa_ccipher_abort（）或psa_cepher_finish（）终止操作后调用psa\ycher_abor（）是安全的，不会产生任何影响。
 *
 * \param[in，out]操作已初始化密码操作。
 *
 * \retval#PSA_SUCCESS\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_cipher_abort(psa_cipher_operation_t *operation);

/**@}*/

/** \defgroup aead使用关联数据进行身份验证的加密（aead）@{
 */

/** 处理经过身份验证的加密操作。
 *
 * \param key用于操作的密钥的标识符。它必须允许使用#PSA_KEY_usage_ENCRYPT。\param alg要计算的AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。\param[in]要使用的nonce或IV。\param nonce_length nonce缓冲区的大小（字节）。\param[in]additional_data将进行身份验证但未加密的其他数据。\param additional_data_length additional_data的大小（字节）。\param[in]明文将被验证和加密的数据。\param plaintext_length明文的大小（字节）。\param[out]密文已验证和加密数据的输出缓冲区。附加数据不是此输出的一部分。对于加密数据和认证标签被定义为单独输出的算法，认证标签被附加到加密数据。\param ciphertext_size密文缓冲区的大小（字节）。这必须适用于所选算法和密钥：
 *                                -足够的输出大小是#PSA_EAD_ENCRYPT_output_size（\c key_type，\p alg，\p明文_length），其中\c keytype是\p密钥的类型。
 *                                -#PSA_EAD_ENCRYPT_OUTPUT_MAX_SIZE（\p明文长度）计算为任何支持的AEAD加密的最大密文大小。\param[out]密文_length成功时，密文缓冲区中输出的大小。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是AEAD算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA错误_BUFFER_TOO_SMALL\p密文大小太小#PSA_EAD_ENCRYPT_OUTPUT_SIZE（\c key_type，\p alg，\p明文_length）或#PSA_EAD_ENCRYPT_OUTPUT_MAX_SIZE（\p明文_length）可用于确定所需的缓冲区大小。\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILUE\retval#PSA_ERROR_RERRUPTION_DETECTED\retval#PSA _ERROR_STORAGE_FAILURE \retval#PSA_RROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_encrypt(mbedtls_svc_key_id_t key,
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

/** 处理经过身份验证的解密操作。
 *
 * \param key用于操作的密钥的标识符。它必须允许使用#PSA_KEY_usage_DECRYPT。\param alg要计算的AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。\param[in]要使用的nonce或IV。\param nonce_length nonce缓冲区的大小（字节）。\param[in]additional_data已验证但未加密的其他数据。\param additional_data_length additional_data的大小（字节）。\param[in]密文已验证和加密的数据。对于加密数据和认证标签被定义为单独输入的算法，缓冲区必须包含加密数据，然后是认证标签。\param ciphertext_length密文的大小（字节）。\param[out]明文解密数据的输出缓冲区。\param plaintext_size明文缓冲区的大小（字节）。这必须适用于所选算法和密钥：
 *                                -足够的输出大小是#PSA_EAD_DECRYPT_output_size（\c key_type，\p alg，\p ciphertext_length），其中\c keytype是\p密钥的类型。
 *                                -#PSA_EAD_DECRYPT_OUTPUT_MAX_SIZE（\p密文长度）计算为任何支持的AEAD解密的最大明文大小。\param[out]plaintext_length成功时，\p明文缓冲区中输出的大小。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_INVALID_SIGNATURE密文不可信。\retval#PSA_ERROR_NOT_PERMITTED\retval#PSTA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是AEAD算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA错误_BUFFER_TOO_SMALL\p明文大小太小#PSA_EAD_DECRYPT_OUTPUT_SIZE（\c key_type，\p alg，\p密文_length）或#PSA_EAD_DECRYPT_OUTPUT_MAX_SIZE（\p密文_length）可用于确定所需的缓冲区大小。\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILUE\retval#PSA_ERROR_RERRUPTION_DETECTED\retval#PSA _ERROR_STORAGE_FAILURE \retval#PSA_RROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_decrypt(mbedtls_svc_key_id_t key,
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

/** 多部分AEAD操作的状态数据结构的类型。
 *
 * 在调用AEAD操作对象上的任何函数之前，应用程序必须通过以下任一方式对其进行初始化：
 * -将结构设置为所有位零，例如：\code psa_aead_operation_t operation；memset（&operation，0，sizeof（operation））；\结束代码
 * -将结构初始化为逻辑零值，例如：\code psa_aead_operation_t operation={0}；\结束代码
 * -将结构初始化为初始值设定项#PSA_EAD_OPERATION_INIT，例如：\code PSA_AEAD_OPERATION_t OPERATION=PSA_EAD_OPERATION_INIT；\结束代码
 * -将函数psa_aead_operation_init（）的结果分配给结构，例如：\code psa_adead_operation_t operation；operation=psa_aeaad_operation_init（）；\结束代码
 *
 * 这是一个实现定义的\c结构。应用程序不应对该结构的内容进行任何假设，除非特定实现的文档有指示。*/
typedef struct psa_aead_operation_s psa_aead_operation_t;

/** \定义PSA_EAD_OPERATION_INIT
 *
 * 此宏为#psa_AEAD_operation_t类型的AEAD操作对象返回合适的初始值设定项。
 */
#ifdef __DOXYGEN_ONLY__
/* 这是用于文档目的的示例定义。实现应在“crypt_struct.h”中定义适当的值。
 */
#define PSA_AEAD_OPERATION_INIT {0}
#endif

/** 返回AEAD操作对象的初始值。
 */
static psa_aead_operation_t psa_aead_operation_init(void);

/** 设置多部分身份验证加密操作的密钥。
 *
 * 使用身份验证加密消息的操作顺序如下：
 * -#分配一个操作对象，该对象将传递给此处列出的所有函数。
 * -#使用#psa_aead_operation_t文档中描述的方法之一初始化操作对象，例如#psa_EAD_operation_INIT。
 * -#调用psa_aeaad_encrypt_setup（）指定算法和密钥。
 * -#如果需要，请调用psa_aead_set_length（）来指定后续调用psa_ead_update_ad（）和psa_ead _update（）的输入长度。有关详细信息，请参阅psa_aeaad_set_length（）的文档。
 * -#调用psa_aeaad_generate_nonce（）或psa_aaead_set_nonce（）来生成或设置nonce。除非正在实现的协议需要特定的nonce值，否则应使用psa_aeaad_generate_nonce（）。
 * -#调用psa_aead_update_ad（）零次，一次或多次，每次传递一段未加密的附加认证数据。
 * -#调用psa_aeaad_update（）零次，一次或多次，每次传递一个消息片段进行加密。
 * -#调用psa_aeaad_finish（）。
 *
 * 如果在调用psa_aead_encrypt_setup（）之后的任何步骤中发生错误，则需要通过调用psa\uaeaad_abort（）来重置操作。操作初始化后，应用程序可以随时调用psa_aead_abort（）。
 *
 * 成功调用psa_aeaad_encrypt_setup（）后，应用程序必须最终终止操作。以下事件将终止操作：
 * -成功调用psa_aeaad_finish（）。
 * -对psa_aeaad_abort（）的调用。
 *
 * \param[in，out]operation要设置的操作对象。它必须已根据#psa_aead_operation_t文档进行初始化，但尚未使用。\param key用于操作的密钥的标识符。它必须保持有效，直到操作终止。它必须允许使用#PSA_KEY_usage_ENCRYPT。\param alg要计算的AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是AEAD算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_encrypt_setup(psa_aead_operation_t *operation,
                                    mbedtls_svc_key_id_t key,
                                    psa_algorithm_t alg);

/** 设置多部分身份验证解密操作的密钥。
 *
 * 使用身份验证对消息进行解密的操作顺序如下：
 * -#分配一个操作对象，该对象将传递给此处列出的所有函数。
 * -#使用#psa_aead_operation_t文档中描述的方法之一初始化操作对象，例如#psa_EAD_operation_INIT。
 * -#调用psa_aeaad_decrypt_setup（）指定算法和密钥。
 * -#如果需要，请调用psa_aead_set_length（）来指定后续调用psa_ead_update_ad（）和psa_ead _update（）的输入长度。有关详细信息，请参阅psa_aeaad_set_length（）的文档。
 * -#使用nonce调用psa_aeaad_set_nonce（）进行解密。
 * -#调用psa_aead_update_ad（）零次，一次或多次，每次传递一段未加密的附加认证数据。
 * -#调用psa_aeaad_update（）零次，一次或多次，每次传递一段密文进行解密。
 * -#调用psa_aead_verify（）。
 *
 * 如果在调用psa_aead_decrypt_setup（）之后的任何步骤中发生错误，则需要通过调用psa_ead_abort（）来重置操作。操作初始化后，应用程序可以随时调用psa_aead_abort（）。
 *
 * 成功调用psa_aeaad_decrypt_setup（）后，应用程序必须最终终止操作。以下事件将终止操作：
 * -成功调用psa_aead_verify（）。
 * -对psa_aeaad_abort（）的调用。
 *
 * \param[in，out]operation要设置的操作对象。它必须已根据#psa_aead_operation_t文档进行初始化，但尚未使用。\param key用于操作的密钥的标识符。它必须保持有效，直到操作终止。它必须允许使用#PSA_KEY_usage_DECRYPT。\param alg要计算的AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p密钥与\p alg不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\p alg不受支持或不是AEAD算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_decrypt_setup(psa_aead_operation_t *operation,
                                    mbedtls_svc_key_id_t key,
                                    psa_algorithm_t alg);

/** 为经过身份验证的加密操作生成随机随机数。
 *
 * 此函数为经过验证的加密操作生成一个随机随机数，该随机数具有所选算法、密钥类型和密钥大小的适当大小。
 *
 * 应用程序必须在调用此函数之前调用psa_aeaad_encrypt_setup（）。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_aead_abort（）中止。
 *
 * \param[in，out]操作激活AEAD操作。\param[out]nonce要写入生成的nonce的缓冲区。\param nonce_size nonce缓冲区的大小（字节）。\param[out]nonce_length成功时，生成的nonce的字节数。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（它必须是活动的aead加密操作，没有设置随机数）。\retval#PSA_ERROR_BUFFER_TOO_SMALL随机数缓冲区的大小太小。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_generate_nonce(psa_aead_operation_t *operation,
                                     uint8_t *nonce,
                                     size_t nonce_size,
                                     size_t *nonce_length);

/** 为经过身份验证的加密或解密操作设置随机数。
 *
 * 此函数设置经过身份验证的加密或解密操作的随机数。
 *
 * 在调用此函数之前，应用程序必须调用psa_aeaad_encrypt_setup（）或psa_aaead_decrypt_setup（）。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_aead_abort（）中止。
 *
 * \注意：加密时，应用程序应使用psa_aeaad_generate_nnonce（）而不是此函数，除非实现需要非随机IV的协议。
 *
 * \param[in，out]操作激活AEAD操作。\param[in]nonce包含要使用的nonce的缓冲区。\param nonce_length nonce的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（它必须是活动的，没有设置随机数）。\retval#PSA_ERROR_INVALID_ARGUMENT随机数的大小对于所选算法不可接受。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_set_nonce(psa_aead_operation_t *operation,
                                const uint8_t *nonce,
                                size_t nonce_length);

/** 声明AEAD的消息长度和附加数据。
 *
 * 如果操作的算法需要，应用程序必须在调用psa_aead_update_ad（）或psa_adead_update（）之前调用此函数。如果算法不需要，则调用此函数是可选的，但如果调用此函数，则实现必须强制执行长度。
 *
 * 您可以在使用psa_aead_set_nonce（）或psa_acad_generate_nonce（）设置nonce之前或之后调用此函数。
 *
 * -对于#PSA_LG_CCM，需要调用此函数。
 * -对于本规范中定义的其他AEAD算法，不需要调用此函数。
 * -有关供应商定义的算法，请参阅供应商文档。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_aead_abort（）中止。
 *
 * \param[in，out]操作激活AEAD操作。\param ad_length未加密的附加认证数据的大小（字节）。\param plaintext_length要加密的明文的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须是活动状态，并且必须尚未调用PSA_aead_update_ad（）和PSA_aaead_update（））。\retval#PSA_ERROR_INVALID_ARGUMENT对于所选算法，至少有一个长度是不可接受的。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA_ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_set_lengths(psa_aead_operation_t *operation,
                                  size_t ad_length,
                                  size_t plaintext_length);

/** 向激活的AEAD操作传递附加数据。
 *
 * 其他数据经过身份验证，但未加密。
 *
 * 您可以多次调用此函数来传递附加数据的连续片段。在传递数据以使用psa_aead_update（）进行加密或解密后，不能调用此函数。
 *
 * 在调用此函数之前，必须：1.调用psa_aead_encrypt_setup（）或psa_aaead_decrypt_setup（）。2.使用psa_aeaad_generate_nonce（）或psa_aaead_Set_nonce（）设置nonce。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_aead_abort（）中止。
 *
 * \警告解密时，在psa_aead_verify（）返回#psa_SUCCESS之前，无法保证输入有效。因此，在调用psa_aead_verify（）并返回#psa_SUCCESS之前，请将输入视为不可信，并准备在psa_aaead_verify（）返回错误状态时撤消依赖于输入的任何操作。
 *
 * \param[in，out]操作激活AEAD操作。\param[in]包含附加数据片段的输入缓冲区。\param input_length输入缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须是活动的，必须设置随机数，如果算法需要，必须设置长度，并且必须尚未调用PSA_aead_update（））。\retval#PSA_ERROR_INVALID_ARGUMENT总输入长度溢出先前使用PSA_aead_set_length（）指定的附加数据长度。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_update_ad(psa_aead_operation_t *operation,
                                const uint8_t *input,
                                size_t input_length);

/** 加密或解密活动AEAD操作中的消息片段。
 *
 * 在调用此函数之前，必须：1.调用psa_aead_encrypt_setup（）或psa_aaead_decrypt_setup（）。设置函数的选择决定了该函数是加密还是解密其输入。2.使用psa_aeaad_generate_nonce（）或psa_aaead_Set_nonce（）设置nonce。3.调用psa_aeaad_update_ad（）传递所有附加数据。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_aead_abort（）中止。
 *
 * \警告解密时，在psa_aead_verify（）返回#psa_SUCCESS之前，无法保证输入有效。因此，在调用psa_aead_verify（）并返回#psa_SUCCESS之前：
 *          -不要以任何方式使用输出，除非将其存储在机密位置。如果您执行任何依赖于临时解密数据的操作，那么如果输入结果无效，则需要撤消此操作。此外，如果对手可以观察到发生了此操作（例如通过计时），则他们可以将此事实用作预言机来解密使用相同密钥加密的任何消息。
 *          -特别是，不要将输出复制到任何位置，而是复制到您具有独占访问权限的内存或存储空间。
 *
 * 此函数不要求输入与任何特定块边界对齐。如果实现一次只能处理整个块，则它必须消耗提供的所有输入，但它可能会延迟相应输出的结束，直到后续调用psa_aeaad_update（）、psa_aaead_finish（）或psa_ayaad_verify（）提供足够的输入。可以通过这种方式延迟的数据量由#PSA_EAD_UPDATE_OUTPUT_SIZE限制。
 *
 * \param[in，out]操作激活AEAD操作。\param[in]输入缓冲区，包含要加密或解密的消息片段。\param input_length输入缓冲区的大小（字节）。\param[out]输出要写入输出的缓冲区。\param output_size输出缓冲区的大小（字节）。这必须适用于所选算法和密钥：
 *                                -足够的输出大小是#PSA_EAD_UPDATE_output_size（\c key_type，\c alg，\p input_length），其中\c keytype是键的类型，\c alg是用于设置操作的算法。
 *                                -#PSA_EAD_UPDATE_OUTPUT_MAX_SIZE（\p input_length）计算为任何支持的AEAD算法的最大输出大小。\param[out]output_length成功时，构成返回输出的字节数。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（它必须是活动的，必须设置随机数，如果算法需要，还必须设置长度）。\retval#PSA_ERROR_BUFFER_TOO_SMALL输出缓冲区的大小太小#PSA_EAD_UPDATE_OUTPUT_SIZE（\c key_type，\c alg，\p input_length）或#PSA_EAD_OPDATE_OUTPUT_MAX_SIZE（\p input_length）可用于确定所需的缓冲区大小。\retval#PSA_ERROR_INVALID_ARGUMENT到目前为止，PSA_aead_update_ad（）的输入总长度小于先前使用PSA_aeaad_set_length（）指定的附加数据长度。\retval#PSA_ERROR_INVALID_ARGUMENT总输入长度溢出先前使用PSA_aead_set_length（）指定的明文长度。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_update(psa_aead_operation_t *operation,
                             const uint8_t *input,
                             size_t input_length,
                             uint8_t *output,
                             size_t output_size,
                             size_t *output_length);

/** 完成AEAD操作中的消息加密。
 *
 * 必须使用psa_aead_encrypt_setup（）设置了该操作。
 *
 * 此函数通过将传递给psa_aead_update_ad（）的先前调用的输入与传递给psaquaead_update（）的之前调用的输入串联而成的明文，完成对附加数据的认证。
 *
 * 此函数有两个输出缓冲区：
 * -\p密文包含从前面对psa_aead_update（）的调用中缓冲的尾随密文。
 * -\p标记包含身份验证标记。
 *
 * 当此函数成功返回时，操作将变为非活动状态。如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_aead_abort（）中止。
 *
 * \param[in，out]操作激活AEAD操作。\param[out]密文缓冲区，其中要写入密文的最后一部分。\param ciphertext_size密文缓冲区的大小（字节）。这必须适用于所选算法和密钥：
 *                              -足够的输出大小是#PSA_EAD_FISH_output_size（\c key_type，\c alg），其中\c keytype是密钥类型，\c alg是用于设置操作的算法。
 *                              -#PSA_EAD_FINISH_OUTPUT_MAX_SIZE计算任何支持的AEAD算法的最大输出大小。\param[out]密文_length成功时，返回密文的字节数。\param[out]tag要写入身份验证标记的缓冲区。\param tag_size \p标记缓冲区的大小（字节）。这必须适用于所选算法和密钥：
 *                              -确切的标记大小为#PSA_EAD_tag_LENGTH（\c key_type，\c key_bits，\c alg），其中\c keytype和\c key_bits是密钥的类型和位大小，\c alg是调用PSA_aeaad_encrypt_setup（）时使用的算法。
 *                              -#PSA_EAD_TAG_MAX_SIZE计算为任何支持的AEAD算法的最大标记大小。\param[out]tag_length成功时，构成返回标记的字节数。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（它必须是设置了随机数的活动加密操作）。\retval#PSA_ERROR_BUFFER_TOO_SMALL密文或标记缓冲区的大小太小#PSA_EAD_FINISH_OUTPUT_SIZE（\c key_type，\c alg）或#PSA_EAD_VINISH_OUTPUT_MAX_SIZE可用于确定所需的密文缓冲区大小#PSA_EAD_TAG_LENGTH（\c key_type、\c key_bits、\c alg）或#PSA_EAD_DAG_MAX_SIZE可用于确定所需的标记缓冲区大小。\retval#PSA_ERROR_INVALID_ARGUMENT到目前为止，PSA_aead_update_ad（）的输入总长度小于先前使用PSA_aeaad_set_length（）指定的附加数据长度。\retval#PSA_ERROR_INVALID_ARGUMENT到目前为止，PSA_aed_update（）的输入总长度小于之前使用PSA_aad_set_length（）指定的明文长度。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_finish(psa_aead_operation_t *operation,
                             uint8_t *ciphertext,
                             size_t ciphertext_size,
                             size_t *ciphertext_length,
                             uint8_t *tag,
                             size_t tag_size,
                             size_t *tag_length);

/** 在AEAD操作中完成对消息的验证和解密。
 *
 * 该操作必须使用psa_aeaad_decrypt_setup（）设置。
 *
 * 此函数完成消息组件的身份验证解密：
 *
 * -由传递给psa_aead_update_ad（）的前面调用的输入串联组成的附加数据。
 * -由传递给psa_aead_update（）的前面调用的输入的串联组成的密文。
 * -传递给此函数调用的标记。
 *
 * 如果身份验证标记正确，此函数将输出所有剩余的明文并报告成功。如果身份验证标记不正确，则此函数返回#PSA_ERROR_INVALID_SIGNATURE。
 *
 * 当此函数成功返回时，操作将变为非活动状态。如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_aead_abort（）中止。
 *
 * \注：实施应尽最大努力确保在恒定时间内进行实际标记和预期标记之间的比较。
 *
 * \param[in，out]操作激活AEAD操作。\param[out]明文缓冲区，其中将写入明文的最后一部分。这是以前对psa_aead_update（）调用的剩余数据，在输入结束之前无法处理这些数据。\param plaintext_size明文缓冲区的大小（字节）。这必须适用于所选算法和密钥：
 *                              -足够的输出大小是#PSA_EAD_VERIFY_output_size（\c key_type，\c alg），其中\c keytype是密钥类型，\c alg是用于设置操作的算法。
 *                              -#PSA_EAD_VERIFY_OUTPUT_MAX_SIZE计算为任何支持的AEAD算法的最大输出大小。\param[out]plaintext_length成功时，返回的明文的字节数。\param[in]tag包含身份验证标记的缓冲区。\param tag_length标记缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_SIGNATURE计算成功，但身份验证标记不正确。\retval#PSA_ERROR_BAD_STATE操作状态无效（它必须是设置了随机数的活动解密操作）。\retval#PSA_ERROR_BUFFER_TOO_SMALL明文缓冲区的大小太小#PSA_EAD_VERIFY_OUTPUT_SIZE（\c key_type，\c alg）或#PSA_EAD_WERIFY_OUTPUT_MAX_SIZE可用于确定所需的缓冲区大小。\retval#PSA_ERROR_INVALID_ARGUMENT到目前为止，PSA_aead_update_ad（）的输入总长度小于先前使用PSA_aeaad_set_length（）指定的附加数据长度。\retval#PSA_ERROR_INVALID_ARGUMENT到目前为止，PSA_aed_update（）的输入总长度小于之前使用PSA_aad_set_length（）指定的明文长度。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_verify(psa_aead_operation_t *operation,
                             uint8_t *plaintext,
                             size_t plaintext_size,
                             size_t *plaintext_length,
                             const uint8_t *tag,
                             size_t tag_length);

/** 中止AEAD操作。
 *
 * 中止操作将释放所有相关资源，但操作结构本身除外。一旦中止，可以通过再次调用psa_aead_encrypt_setup（）或psa_aaead_decrypt_setup（）将操作对象重新用于另一个操作。
 *
 * 在操作对象初始化后，可以随时调用此函数，如#psa_aead_operation_t中所述。
 *
 * 特别是，在通过调用psa_aead_abort（）、psa_aad_finish（）或psa_aaead_verify（）终止操作后调用psa\uaeaad_abort（）是安全的，不会产生任何影响。
 *
 * \param[in，out]操作已初始化AEAD操作。
 *
 * \retval#PSA_SUCCESS\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_aead_abort(psa_aead_operation_t *operation);

/**@}*/

/** \非对称非对称密码@{
 */

/**
 * \用私钥签名。对于哈希和符号算法，这包括哈希步骤。
 *
 * \注意：要执行多部分哈希和签名算法，首先使用多部分哈希操作，然后将生成的哈希传递给psa_sign_hash（）。PSA_AG_GET_HASH（\p ALG）可用于确定要使用的哈希算法。
 *
 * \param[in]key用于操作的密钥的标识符。它必须是非对称密钥对。密钥必须允许使用#PSA_key_usage_SIGN_MESSAGE。\param[in]alg一种与密钥类型兼容的非对称签名算法（PSA_alg_XXX值，使得#PSA_alg_IS_SIGN_MESSAGE（\p alg）为真）。\param[in]input要签名的输入消息。\param[in]input_length输入缓冲区的大小（以字节为单位）。\param[out]signature要写入签名的缓冲区。\param[in]signature_size签名缓冲区的大小（字节）。这必须适用于所选算法和密钥：
 *                              -所需的签名大小为#PSA_SIGN_OUTPUT_size（\c key_type，\c key_bits，\p alg），其中\c keytype和\c key_bits分别是密钥的类型和位大小。
 *                              -#PSA_SIGNATURE_MAX_SIZE计算为任何支持的签名算法的最大签名大小。\param[out]signature_length成功时，构成返回签名值的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED密钥没有#PSA_key_USAGE_SIGN_MESSAGE标志，或者它不允许请求的算法。\retval#PSA_ERROR_BUFFER_TOO_SMALL签名缓冲区的大小太小。您可以通过调用#PSA_SIG_OUTPUT_size（\c key_type，\c key_bits，\p alg）来确定足够的缓冲区大小，其中\c keytype和\c key_bits分别是\p key的类型和位大小。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#1PSA_ERROR_HARDWARE_FAILUE\retval#8PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILURE \retval#3PSA_ERROR_DATA_CORRUPT\retval#xPSA_ERROR_SATA_INVALID\retval#5PSA_ERROR_ISUFFIE_ENTROPY\retval#0PSA_ERROR_BARRROR_BARDROR_BAILUREAD_STATE库以前未被psa_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_sign_message( mbedtls_svc_key_id_t key,
                               psa_algorithm_t alg,
                               const uint8_t * input,
                               size_t input_length,
                               uint8_t * signature,
                               size_t signature_size,
                               size_t * signature_length );

/** \brief使用哈希和签名验证算法，使用公钥验证消息的签名。
 *
 * \注意：要执行多部分哈希和签名验证算法，首先使用多部分哈希操作对消息进行哈希，然后将生成的哈希传递给psa_verify_hash（）。PSA_AG_GET_HASH（\p ALG）可用于确定要使用的哈希算法。
 *
 * \param[in]key用于操作的密钥的标识符。它必须是公钥或非对称密钥对。密钥必须允许使用#PSA_key_usage_VERIFY_MESSAGE。\param[in]alg一种与密钥类型兼容的非对称签名算法（PSA_alg_XXX值，使得#PSA_alg_IS_SIGN_MESSAGE（\p alg）为真）。\param[in]input要验证其签名的消息。\param[in]input_length输入缓冲区的大小（字节）。\param[out]signature包含要验证的签名的缓冲区。\param[in]signature_length签名缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED密钥没有#PSA_key_USAGE_SIGN_MESSAGE标志，或者它不允许请求的算法。\retval#PSA_ERROR_INVALID_SIGNATURE计算已成功执行，但传递的签名不是有效签名。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#8PSA_ERROR_COMMUNICATION_FAILURE\retval#1PSA_ERROR_HARDWARE_FAILUE\retval#PSA _ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILURE \retval#PSA_RROR_DATA_CORRUPT\retval#3PSA_ERROR_DATA_INVALID\retval#5PSA_ERROR_BAD_STATE库以前未初始化通过psa_crypto_init（）。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_verify_message( mbedtls_svc_key_id_t key,
                                 psa_algorithm_t alg,
                                 const uint8_t * input,
                                 size_t input_length,
                                 const uint8_t * signature,
                                 size_t signature_length );

/**
 * \brief使用私钥签名哈希或短消息。
 *
 * 请注意，要执行哈希和签名算法，必须首先通过调用psa_hash_setup（）、psa_hhash_update（）和psa_has_finish（）来计算哈希，或者调用psa\nhash_compute（）。然后将生成的哈希作为\p哈希参数传递给此函数。您可以使用#PSA_ALG_SIG_GET_HASH（\p ALG）来确定要使用的哈希算法。
 *
 * \param key用于操作的密钥的标识符。它必须是非对称密钥对。密钥必须允许使用#PSA_key_usage_SIGN_HASH。\param alg与密钥类型兼容的签名算法（PSA_alg_XXX值，使得#PSA_alg_IS_SIGN_HASH（\p alg）为真）。\param[in]hash要签名的哈希或消息。\param hash_length哈希缓冲区的大小（字节）。\param[out]signature要写入签名的缓冲区。\param signature_size签名缓冲区的大小（字节）。\param[out]signature_length成功时，构成返回签名值的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_BUFFER_TOO_SMALL签名缓冲区的大小太小。您可以通过调用#PSA_SIG_OUTPUT_size（\c key_type，\c key_bits，\p alg）来确定足够的缓冲区大小，其中\c keytype和\c key_bits分别是\p key的类型和位大小。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA _ERROR_COMMUNICATION_FAILURE\retval#PSA_RROR_HARDWAREE_FAILURE\ retval#PS A_ERROR_CORRUPTION_DETECTED \retval#1PSA_ERROR_STORAGE_FAILURE \retval#2PSA_ERROR_inSUFFIE_ENTROPY\retval#8PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_sign_hash(mbedtls_svc_key_id_t key,
                           psa_algorithm_t alg,
                           const uint8_t *hash,
                           size_t hash_length,
                           uint8_t *signature,
                           size_t signature_size,
                           size_t *signature_length);

/**
 * \brief使用公钥验证哈希或短消息的签名。
 *
 * 请注意，要执行哈希和签名算法，必须首先通过调用psa_hash_setup（）、psa_hhash_update（）和psa_has_finish（）来计算哈希，或者调用psa\nhash_compute（）。然后将生成的哈希作为\p哈希参数传递给此函数。您可以使用#PSA_ALG_SIG_GET_HASH（\p ALG）来确定要使用的哈希算法。
 *
 * \param key用于操作的密钥的标识符。它必须是公钥或非对称密钥对。密钥必须允许使用#PSA_key_usage_VERIFY_HASH。\param alg与密钥类型兼容的签名算法（PSA_alg_XXX值，使得#PSA_alg_IS_SIGN_HASH（\p alg）为真）。\param[in]hash要验证其签名的哈希或消息。\param hash_length哈希缓冲区的大小（字节）。\param[in]签名缓冲区，包含要验证的签名。\param signature_length签名缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS签名有效。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_SIGNATURE计算已成功执行，但传递的签名不是有效签名。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA _ERROR_COMMUNICATION_FAILURE\retval#PSA_RROR_HARDWAREE_FAILURE\ retval#PSA _ERROR _CORRUPTION_DETECTED \retval#1PSA_ERROR_STORAGE_FAILURE \retval#2PSA_ERROR_BAD_STATE此库以前未由PSA_cry_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_verify_hash(mbedtls_svc_key_id_t key,
                             psa_algorithm_t alg,
                             const uint8_t *hash,
                             size_t hash_length,
                             const uint8_t *signature,
                             size_t signature_length);

/**
 * \brief使用公钥加密短消息。
 *
 * \param key用于操作的密钥的标识。它必须是公钥或非对称密钥对。它必须允许使用#PSA_KEY_usage_ENCRYPT。\param alg与密钥类型兼容的非对称加密算法。\param[in]input要加密的消息。\param input_length输入缓冲区的大小（字节）。\param[in]salt一个盐或标签，如果加密算法支持。如果算法不支持salt，请传递\c NULL。如果算法支持可选的salt，并且您不想传递salt，请传递\c NULL。
 *
 *                              -对于#PSA_LG_RSA_PKCS1V15_CRYPT，不支持盐。\param salt_length盐缓冲区的大小（字节）。如果\p salt为\c NULL，则在要写入加密消息的位置传递0.\param[out]输出缓冲区。\param output_size输出缓冲区的大小（字节）。\param[out]output_length成功时，构成返回输出的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_BUFFER_TOO_SMALL输出缓冲区的大小太小。您可以通过调用#PSA_SYMMETRIC_ENCRYPT_OUTPUT_size（\c key_type，\c key_bits，\p alg）来确定足够的缓冲区大小，其中\c keytype和\c key_bits分别是\p key的类型和位大小。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA _ERROR_COMMUNICATION_FAILURE\retval#PSA_RROR_HARDWAREE_FAILURE\ retval#PS A_ERROR_CORRUPTION_DETECTED \retval#1PSA_ERROR_STORAGE_FAILURE \retval#2PSA_ERROR_inSUFFIE_ENTROPY\retval#8PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_asymmetric_encrypt(mbedtls_svc_key_id_t key,
                                    psa_algorithm_t alg,
                                    const uint8_t *input,
                                    size_t input_length,
                                    const uint8_t *salt,
                                    size_t salt_length,
                                    uint8_t *output,
                                    size_t output_size,
                                    size_t *output_length);

/**
 * \brief使用私钥解密短消息。
 *
 * \param key用于操作的密钥的标识符。它必须是非对称密钥对。它必须允许使用#PSA_KEY_usage_DECRYPT。\param alg与密钥类型兼容的非对称加密算法。\param[in]input要解密的消息。\param input_length输入缓冲区的大小（字节）。\param[in]salt一个盐或标签，如果加密算法支持。如果算法不支持salt，请传递\c NULL。如果算法支持可选的salt，并且您不想传递salt，请传递\c NULL。
 *
 *                              -对于#PSA_LG_RSA_PKCS1V15_CRYPT，不支持盐。\param salt_length盐缓冲区的大小（字节）。如果\p salt为\c NULL，则传递0.\param[out]输出缓冲区，将解密的消息写入该缓冲区。\param output_size \c输出缓冲区的大小（字节）。\param[out]output_length成功时，构成返回输出的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_BUFFER_TOO_SMALL输出缓冲区的大小太小。您可以通过调用#PSA_SYMMETRIC_DECRYPT_OUTPUT_size（\c key_type，\c key_bits，\p alg）来确定足够的缓冲区大小，其中\c key _type和\c key _bits分别是\p key的类型和位大小。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#8PSA_ERROR_COMMUNICATION_FAILURE\retval#1PSA_ERROR_HARDWARE_FAILUE\retval#PSA _ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILURE \retval#PSA_RROR_INSUFFICE_ENTROPY\retval#1PSA_ERROR _INVALID_PADDING\retval#3PSA_ERROR_BAD_STATE该库以前没有由psa_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_asymmetric_decrypt(mbedtls_svc_key_id_t key,
                                    psa_algorithm_t alg,
                                    const uint8_t *input,
                                    size_t input_length,
                                    const uint8_t *salt,
                                    size_t salt_length,
                                    uint8_t *output,
                                    size_t output_size,
                                    size_t *output_length);

/**@}*/

/** \defgroup key_derivation密钥推导和伪随机生成@{
 */

/** 密钥派生操作的状态数据结构的类型。
 *
 * 在调用密钥派生操作对象上的任何函数之前，应用程序必须通过以下任一方式对其进行初始化：
 * -将结构设置为所有位零，例如：\code psa_key_derivation_operation_t operation；memset（&operation，0，sizeof（operation））；\结束代码
 * -将结构初始化为逻辑零值，例如：\code psa_key_derivation_operation_t operation={0}；\结束代码
 * -将结构初始化为初始值设定项#PSA_KEY_DERIVATION_OPERATION_INIT，例如：\code PSA_KEY_DERIVATION_OPERATION_t OPERATION=PSA_KEYDERIVATIOn_OPERATION_INIT；\结束代码
 * -将函数psa_key_derivation_operation_init（）的结果分配给结构，例如：\code psa_key _derivatation_operation_t operation；operation=psa_key_derivation_operation_init（）；\结束代码
 *
 * 这是一个实现定义的\c结构。应用程序不应对该结构的内容进行任何假设，除非特定实现的文档有指示。
 */
typedef struct psa_key_derivation_s psa_key_derivation_operation_t;

/** \定义PSA_KEY_DERIVATION_OPERATION_INIT
 *
 * 此宏为#psa_key_derivation_operation_t类型的密钥派生操作对象返回合适的初始值设定项。
 */
#ifdef __DOXYGEN_ONLY__
/* 这是用于文档目的的示例定义。实现应在“crypt_struct.h”中定义适当的值。
 */
#define PSA_KEY_DERIVATION_OPERATION_INIT {0}
#endif

/** 返回键派生操作对象的初始值。
 */
static psa_key_derivation_operation_t psa_key_derivation_operation_init(void);

/** 设置密钥派生操作。
 *
 * 密钥推导算法接受一些输入，并使用它们以确定性的方式生成字节流。此字节流可用于生成密钥和其他加密材料。
 *
 * 要导出密钥，请执行以下操作：
 * -#从#psa_key_derivation_operation_t类型的初始化对象开始。
 * -#调用psa_key_derivation_setup（）选择算法。
 * -#根据需要，通过调用psa_key_derivation_input_bytes（）或psa_kkey_derivatation_input_key（）提供密钥派生的输入。需要哪些输入，按什么顺序，它们是否可能是键，如果是，则是什么类型，取决于算法。
 * -#（可选）使用psa_key_derivation_set_capacity（）设置操作的最大容量。您可以在提供输入之前、中间或之后执行此操作。对于某些算法，此步骤是强制性的，因为输出取决于最大容量。
 * -#要派生密钥，请调用psa_key_derivation_output_key（）。要导出用于不同目的的字节字符串，请调用psa_key_derivation_output_bytes（）。对这些函数的连续调用使用密钥推导算法计算的连续输出字节。
 * -#使用psa_key_derivation_abort（）清理密钥派生操作对象。
 *
 * 如果此函数返回错误，则不会更改密钥派生操作对象。
 *
 * 如果在调用psa_key_derivation_setup（）后的任何步骤发生错误，则需要通过调用psa_key_derivatation_abort（）来重置操作。
 *
 * 实现必须拒绝派生大小为0的密钥的尝试。
 *
 * \param[in，out]operation要设置的密钥派生操作对象。它必须已初始化，但尚未设置。\param alg要计算的密钥推导算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_key_derivation（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_ARGUMENT\c alg不是密钥推导算法。\retval#PSA_ERROR_NOT_SUPPORTED\c alg不受支持或不是密钥派生算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_STORAGE_FAILUE\retval＃PSA_ERROR_BAD_STATE操作状态无效（必须为非活动状态）。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_key_derivation_setup(
    psa_key_derivation_operation_t *operation,
    psa_algorithm_t alg);

/** 检索密钥派生操作的当前容量。
 *
 * 密钥派生的容量是它可以返回的最大字节数。当您从密钥派生操作获得N个字节的输出时，这会将其容量减少N。
 *
 * \param[in]operation要查询的操作。\param[out]capacity成功时，操作的容量。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为活动状态）。\retval#PSA_ERROR_HARDWARE_FAILURE\retval#PSA_ERROR_CORRUPTION_DETECTED\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_key_derivation_get_capacity(
    const psa_key_derivation_operation_t *operation,
    size_t *capacity);

/** 设置密钥派生操作的最大容量。
 *
 * 密钥派生操作的容量是密钥派生操作从此时起可以返回的最大字节数。
 *
 * \param[in，out]operation要修改的密钥派生操作对象。\param capacity操作的新容量。它必须小于或等于操作的当前容量。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_ARGUMENT\p容量大于操作的当前容量。在这种情况下，操作对象保持有效，其容量保持不变。\retval#PSA_ERROR_BAD_STATE操作状态无效（必须为活动状态）。\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_key_derivation_set_capacity(
    psa_key_derivation_operation_t *operation,
    size_t capacity);

/** 使用密钥派生操作的最大可能容量。
 *
 * 在设置密钥派生时，将此值用作容量参数，以指示操作应具有最大可能容量。最大可能容量的值取决于密钥推导算法。
 */
#define PSA_KEY_DERIVATION_UNLIMITED_CAPACITY ((size_t)(-1))

/** 为密钥派生或密钥协议提供输入。
 *
 * 需要哪些输入以及顺序取决于算法。有关信息，请参阅每个密钥推导或密钥协商算法的文档。
 *
 * 此函数传递直接输入，通常对于非秘密输入是正确的。要传递密钥对象中的秘密输入，请调用psa_key_derivation_input_key（）而不是此函数。有关详细信息，请参阅各个步骤类型的文档（类型为：PSA_KEY_DERIVATION_step_t的“PSA_KEY_DERIVATION_INPUT_xxx”值）。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_key_derivation_abort（）中止。
 *
 * \param[in，out]operation要使用的密钥派生操作对象。它必须是用psa_key_derivation_setup（）设置的，并且必须尚未生成任何输出。\param step输入数据用于哪个步骤。\param[in]data输入要使用的数据。\param data_length数据缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_ARGUMENT\c步骤与操作的算法不兼容。\retval#PSA_ERROR_INVALID_ARGUMENT\c步骤不允许直接输入。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_STORAGE_FAILUE\retval＃PSA_ERROR_BAD_STATE操作状态对于此输入步骤无效。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_key_derivation_input_bytes(
    psa_key_derivation_operation_t *operation,
    psa_key_derivation_step_t step,
    const uint8_t *data,
    size_t data_length);

/** 以密钥的形式为密钥派生提供输入。
 *
 * 需要哪些输入以及顺序取决于算法。有关信息，请参阅每个密钥推导或密钥协商算法的文档。
 *
 * 此函数从密钥对象获取输入，对于密钥存储中保存的秘密输入或非秘密个性化字符串来说，这通常是正确的。要传递不在密钥存储中的非机密参数，请调用psa_key_derivation_input_bytes（）而不是此函数。有关详细信息，请参阅各个步骤类型的文档（类型为：PSA_KEY_DERIVATION_step_t的“PSA_KEY_DERIVATION_INPUT_xxx”值）。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_key_derivation_abort（）中止。
 *
 * \param[in，out]operation要使用的密钥派生操作对象。它必须是用psa_key_derivation_setup（）设置的，并且必须尚未生成任何输出。\param step输入数据用于哪个步骤。\param key密钥的标识符。它必须具有适当的步骤类型，并且必须允许使用#PSA_KEY_usage_DERIVE。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSTA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\c步骤与操作的算法不兼容。\retval#PSA_ERROR_INVALID_ARGUMENT\c步骤不允许给定类型的键输入，或者根本不允许键输入。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_RROR_STORAGE_FAILUE\retval＃PSA_ERROR_BAD_STATE操作状态对于此输入步骤无效。\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_key_derivation_input_key(
    psa_key_derivation_operation_t *operation,
    psa_key_derivation_step_t step,
    mbedtls_svc_key_id_t key);

/** 执行密钥协商并将共享密钥用作密钥派生的输入。
 *
 * 密钥协商算法需要两个输入：私钥\p private_key和公钥\p peer_key。此函数的结果作为输入传递给密钥派生。该密钥导出的输出可以通过从生成的操作中读取来提取，以生成密钥和其他密码材料。
 *
 * 如果此函数返回错误状态，则操作将进入错误状态，必须通过调用psa_key_derivation_abort（）中止。
 *
 * \param[in，out]operation要使用的密钥派生操作对象。它必须是用psa_key_derivation_setup（）设置的，具有密钥协议和派生算法（\c alg）（\c psa_alg_XXX值，使得#psa_alg_IS_key_agreement（\c alg）为真，#psa_AG_IS_RAW_key_AGREMENT（\c alg）为假）。操作必须准备好接受\p step给定类型的输入。\param step输入数据用于哪个步骤。\param private_key要使用的私钥的标识符。它必须允许使用#PSA_KEY_usage_DERIVE。\param[in]peer_key对等方的公钥。对等密钥的格式必须与psa_import_key（）为对应于private_key类型的公钥类型接受的格式相同。也就是说，此函数执行#psa_import_key（…，`peer_key`，`peer_key_length`）的等效功能，其中key属性指示与`private_key`类型对应的公钥类型。例如，对于EC密钥，这意味着peer_key被解释为私钥所在曲线上的一个点。公钥的标准格式记录在psa_export_public_key（）的文档中。\param peer_key_length \p peer_key的大小（字节）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_BAD_STATE此密钥协议步骤的操作状态无效。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA _ERROR_INVALID_ARGUMENT\c private_key与\c alg不兼容，或者\p peer_key对\c alg无效或与\c private _key不兼容。\retval#PSA_ERROR_NOT_SUPPORTED\c alg不受支持或不是密钥派生算法。\retval#PSA_ERROR_INVALID_ARGUMENT\c步骤不允许由密钥协议产生的输入。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_key_derivation_key_agreement(
    psa_key_derivation_operation_t *operation,
    psa_key_derivation_step_t step,
    mbedtls_svc_key_id_t private_key,
    const uint8_t *peer_key,
    size_t peer_key_length);

/** 从密钥派生操作中读取一些数据。
 *
 * 此函数计算密钥派生算法的输出字节并返回这些字节。如果您将密钥派生的输出视为字节流，则此函数会破坏性地从流中读取请求的字节数。操作的容量随读取的字节数而减少。
 *
 * 如果此函数返回的错误状态不是#PSA_error_INSUFFIED_DATA，则操作将进入错误状态，必须通过调用PSA_key_derivation_abort（）中止。
 *
 * \param[in，out]operation要读取的密钥派生操作对象。\param[out]输出将写入输出的缓冲区。\param output_length要输出的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INSUFFIED_DATA操作的容量小于\p output_length字节。注意，在这种情况下，没有输出写入输出缓冲区。操作的容量设置为0，因此即使输出缓冲区较小，对该函数的后续调用也不会成功。\retval#PSA_ERROR_BAD_STATE操作状态无效（它必须处于活动状态并完成所有必需的输入步骤）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_key_derivation_output_bytes(
    psa_key_derivation_operation_t *operation,
    uint8_t *output,
    size_t output_length);

/** 从正在进行的密钥派生操作派生密钥。
 *
 * 此函数计算密钥导出算法的输出字节，并使用这些字节确定地生成密钥。密钥的位置、使用策略、类型和大小取自\p属性。
 *
 * 如果您将密钥派生的输出视为字节流，则此函数会破坏性地从流中读取所需的字节数。操作的容量随读取的字节数而减少。
 *
 * 如果此函数返回的错误状态不是#PSA_error_INSUFFIED_DATA，则操作将进入错误状态，必须通过调用PSA_key_derivation_abort（）中止。
 *
 * 操作产生和消耗了多少输出，以及如何导出密钥，取决于密钥类型和密钥大小（如下所示）：
 *
 * -对于密钥是给定大小的任意字节序列的密钥类型，此函数在功能上等同于调用#psa_key_derivation_output_bytes并将结果输出传递给#psa_import_key。然而，该函数具有安全性优势：如果实现提供了隔离边界，那么密钥材料不会暴露在隔离边界之外。因此，对于这些密钥类型，此函数总是从操作中精确消耗（\c bits/8）字节。本规范中定义的以下密钥类型遵循此方案：
 *
 *     - #PSA_KEY_TYPE_AES;
 *     - #PSA_KEY_TYPE_ARC4;
 *     - #PSA_KEY_TYPE_ARIA;
 *     - #PSA_KEY_TYPE_CAMELLIA;
 *     - #PSA_KEY_TYPE_DERIVE;
 *     - #PSA_KEY_TYPE_HMAC.
 *
 * -对于蒙哥马利椭圆曲线上的ECC密钥（#PSA_KEY_TYPE_ECC_KEY_PAIR（\c曲线），其中\c曲线表示蒙哥马利曲线），此函数始终绘制长度由曲线确定的字节字符串，并相应地设置强制位。即：
 *
 *     -Curve25519（#PSA_ECC_FAMILY_MONTGOMERY，255位）：绘制一个32字节的字符串，并按照RFC 7748&sect；5.
 *     -Curve448（#PSA_ECC_FAMILY_MONTGOMERY，448位）：绘制一个56字节的字符串，并按照RFC 7748&sect；5.
 *
 * -对于密钥由单个位序列表示的密钥类型，该位序列具有可接受位序列的限制，此函数绘制长度为（\c bits/8）字节的字节字符串，四舍五入到最接近的整数字节。如果生成的字节字符串是可接受的，则它将成为关键字，否则将丢弃绘制的字节。重复此过程，直到绘制出可接受的字节字符串。从操作中提取的字节字符串被解释为为psa_export_key（）生成的输出指定的字符串。本规范中定义的以下密钥类型遵循此方案：
 *
 *     -#PSA_KEY_TYPE_DES。强制设置奇偶校验位，但丢弃禁用的弱密钥。对于2密钥和3密钥三重DES，三个密钥是连续生成的（例如，对于3密钥三次DES，如果前8个字节指定了一个弱密钥，而后8个字节没有指定，则丢弃前8个字符，使用后8个字符作为第一个密钥，并继续读取操作输出以导出其他两个密钥）。
 *     -有限域Diffie-Hellman密钥（#PSA_KEY_TYPE_DH_KEY_PAIR（\c group），其中\c group指定任何Diffie-Hollman组）和Weierstrass椭圆曲线上的ECC密钥（#PSA _KEY_TYPE-ECC_KEY_PAIR（\c curve），其中/c curve指定Weierstras曲线）。对于这些键类型，将字节字符串解释为大端序的整数。如果它不在[0，N-2]范围内，其中N是私钥域的边界（Diffie-Hellman的素数p，DSA的次q，或ECC的曲线基点的顺序），则放弃它。将所得整数加1，并将其用作私钥x。该方法允许符合NIST标准，特别是NIST SP 800-56A&sect；5.6.1.1.4对于Diffie Hellman，FIPS 186-4&sect；B、 DSA为1.2，NIST SP 800-56A&sect；5.6.1.2.2或FIPS 186-4节；B、 4.2对于椭圆曲线键。
 *
 * -对于其他密钥类型，包括#PSA_key_TYPE_RSA_key_PAIR，操作输出的使用方式由实现定义。
 *
 * 在所有情况下，从操作中丢弃读取的数据。操作的容量会减少读取的字节数。
 *
 * 对于采用输入步骤#PSA_KEY_DERIVATION_input_SECRET的算法，必须为该步骤的输入提供PSA_KEY_DERIVATION_input_KEY（）。本规范的未来版本可能包括基于密钥的属性和强度对派生密钥的附加限制。
 *
 * \param[in]attributes新密钥的属性。\param[in，out]operation要读取的密钥派生操作对象。\param[out]key成功时，新创建的密钥的标识符。对于持久密钥，这是\p属性中定义的密钥标识符。\c 0失败。
 *
 * \retval#PSA_SUCCESS成功。如果密钥是持久的，则密钥材料和密钥的元数据已保存到持久存储中。\retval#PSA_ERROR_ALREADY_EXISTS这是一次创建持久密钥的尝试，并且已经存在具有给定标识符的持久密钥。\retval#PSA_ERROR_INSUFFIED_DATA没有足够的数据来创建所需的密钥。注意，在这种情况下，没有输出写入输出缓冲区。操作的容量设置为0，因此即使输出缓冲区较小，对该函数的后续调用也不会成功。\retval#PSA_ERROR_NOT_SUPPORTED一般情况下或在此特定位置的实现都不支持密钥类型或密钥大小。\retval#PSA_ERROR_INVALID_ARGUMENT提供的密钥属性对操作无效。\retval#PSA_ERROR_NOT_PERMITED未通过密钥提供#PSA_KEY_DERIVATION_INPUT_SECRET输入。\retval#PSA_ERROR_BAD_STATE操作状态无效（它必须处于活动状态并完成所有必需的输入步骤）。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA _ERROR_INSUFFICE_STORAGE\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA_RROR_CORRUPTION_DETECTED \retval#1PSA_ERROR_DATA_INVALID\retval#2PSA_ERROR_DATA_CORRUPT\retval#3PSA_ERROR_STORAGE_FAILULE\retval#8PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_key_derivation_output_key(
    const psa_key_attributes_t *attributes,
    psa_key_derivation_operation_t *operation,
    mbedtls_svc_key_id_t *key);

/** 中止密钥派生操作。
 *
 * 中止操作将释放除操作结构本身之外的所有相关资源。一旦中止，可以通过再次调用psa_key_derivation_setup（）将操作对象重新用于另一个操作。
 *
 * 如#psa_key_deviction_operation_t中所述，操作对象初始化后，可以随时调用此函数。
 *
 * 特别是，两次调用psa_key_derivation_abort（）或对尚未设置的操作调用psa_key_derivatation_abort）是有效的。
 *
 * \param[in，out]operation要中止的操作。
 *
 * \retval#PSA_SUCCESS\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_key_derivation_abort(
    psa_key_derivation_operation_t *operation);

/** 执行密钥协议并返回原始共享密钥。
 *
 * \警告：有限域Diffie-Hellman或椭圆曲线Diffie-Hillman等密钥一致算法的原始结果存在偏差，不应直接用作密钥材料。相反，它应该作为输入传递给密钥推导算法。要用密钥派生链接密钥协议，请使用psa_key_derivation_key_agreement（）和密钥派生接口中的其他函数。
 *
 * \param alg要计算的密钥协议算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_RAW_key_agreement（\p alg）为真）。\param private_key要使用的私钥的标识符。它必须允许使用#PSA_KEY_usage_DERIVE。\param[in]peer_key对等方的公钥。它的格式必须与psa_import_key（）接受的格式相同。公钥的标准格式记录在psa_export_public_key（）的文档中。\param peer_key_length \p peer_key的大小（字节）。\param[out]输出要写入解密消息的缓冲区。\param output_size \c输出缓冲区的大小（字节）。\param[out]output_length成功时，构成返回输出的字节数。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_HANDLE\retval#PSA_ERROR_NOT_PERMITTED\retval#PSA_ERROR_INVALID_ARGUMENT\p alg不是密钥协议算法\retval#PSA _ERROR_INVALID_AARGUMENT\p private_key与\p alg不兼容，或者\p peer_key对\p alk无效或与\p private _key不兼容。\retval#PSA_ERROR_BUFFER_TOO_SMALL\p output_size太小\retval#PSA _ERROR_NOT_SUPPORTED\p alg不是受支持的密钥协议算法。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSTA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_HARDWARE_FAILURE \retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_STORAGE_FAILUE\retval#8PSA_ERROR_BAD_STATE库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_raw_key_agreement(psa_algorithm_t alg,
                                   mbedtls_svc_key_id_t private_key,
                                   const uint8_t *peer_key,
                                   size_t peer_key_length,
                                   uint8_t *output,
                                   size_t output_size,
                                   size_t *output_length);

/**@}*/

/** \去分组随机生成@{
 */

/**
 * \brief生成随机字节。
 *
 * \警告此函数**可能**失败！调用方必须检查返回状态，如果返回状态不是#PSA_SUCCESS，则不得使用输出缓冲区的内容。
 *
 * \注意：要生成密钥，请改用psa_generate_key（）。
 *
 * \param[out]output生成数据的输出缓冲区。\param output_size要生成和输出的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_INSUFFIE_ENTROPY\retval#PSA_ERROR_INSUFFICE_MEMORY\retval#1 PSA_ERROR_COMMUNICATION_FAILURE\retval#2 PSA_ERROR_HARDWARE_FAILURE \retval#PSA _ERROR_CORRUPTION_DETECTED \retval#4 PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_generate_random(uint8_t *output,
                                 size_t output_size);

/**
 * \brief生成密钥或密钥对。
 *
 * 密钥是随机生成的。其位置、使用策略、类型和大小取自\p属性。
 *
 * 实现必须拒绝生成大小为0的密钥的尝试。
 *
 * 以下类型特定注意事项适用：
 * -对于RSA密钥（#PSA_KEY_TYPE_RSA_KEY_PAIR），公共指数为65537。模数是介于2^{n-1}和2^n之间的两个概率素数的乘积，其中n是属性中指定的比特大小。
 *
 * \param[in]attributes新密钥的属性。\param[out]key成功时，新创建的密钥的标识符。对于持久密钥，这是\p属性中定义的密钥标识符。\c 0失败。
 *
 * \retval#PSA_SUCCESS成功。如果密钥是持久的，则密钥材料和密钥的元数据已保存到持久存储中。\retval#PSA_ERROR_ALREADY_EXISTS这是一次创建持久密钥的尝试，并且已经存在具有给定标识符的持久密钥。\retval#PSA_ERROR_NOT_SUPPORTED\retval#PSTA_ERROR_INVALID_ARGUMENT\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#1PSA_ERROR_ISUFFIE_ENTROPY\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#8PSA_ERROR_HARDWARE_FAILUE\retval#2PSA_ERROR_CORRUPTION_DETECTED \retval#5PSA_ERROR/INSUFFIE_STORAGE\retval#3PSA_ERROR_DATA_INVALID\retval#xPSA_ERROR_SATA_CORRUPT\retval#PSA_ERROR_STORAGE_FAILURE\retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_generate_key(const psa_key_attributes_t *attributes,
                              mbedtls_svc_key_id_t *key);

/**@}*/

#ifdef __cplusplus
}
#endif

/* 文件“crypto_sizes.h”包含大小计算宏的定义，这些宏的定义是特定于实现的。*/
#include "crypto_sizes.h"

/* 文件“crypt_struct.h”包含上面声明的特定于实现的结构的定义。*/
#include "crypto_struct.h"

/* 文件“crypto_extra.h”包含供应商特定的定义。这可能包括供应商定义的算法、额外功能等。*/
#include "crypto_extra.h"

#endif /* PSA_CRYPTO_H */

