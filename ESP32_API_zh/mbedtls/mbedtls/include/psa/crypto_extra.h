/**
 * \psa/crypto_extra.h文件
 *
 * \简短的PSA加密模块：Mbed TLS供应商扩展
 *
 * \注意：此文件可能不直接包含。应用程序必须包括psa/crypto.h。
 *
 * 此文件保留用于特定于供应商的定义。
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

#ifndef PSA_CRYPTO_EXTRA_H
#define PSA_CRYPTO_EXTRA_H

#include "mbedtls/platform_util.h"

#include "crypto_types.h"
#include "crypto_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 安全存储种子的UID*/
#define PSA_CRYPTO_ITS_RANDOM_SEED_UID 0xFFFFFF52

/* 请参阅配置。h用于定义*/
#if !defined(MBEDTLS_PSA_KEY_SLOT_COUNT)
#define MBEDTLS_PSA_KEY_SLOT_COUNT 32
#endif

/** \addtogroup属性@{
 */

/** \brief声明密钥的注册算法。
 *
 * 对键的操作可以分别使用与psa_set_key_algorithm（）或此函数一起设置的算法。
 *
 * \param[out]attributes要写入的属性结构。\param alg2除了使用psa_set_key_algorithm（）设置的算法之外，还可以使用密钥的第二个算法。
 *
 * \警告不建议设置注册算法，因为使用相同的密钥和不同的算法可能会允许基于使用相同密钥进行的不同计算之间的算术关系的某些攻击，或者可能会将无害的侧信道升级为可利用的侧信道。仅当需要支持协议时，才使用此功能，该协议已验证密钥与多个算法的使用是安全的。
 */
static inline void psa_set_key_enrollment_algorithm(
    psa_key_attributes_t *attributes,
    psa_algorithm_t alg2)
{
    attributes->core.policy.alg2 = alg2;
}

/** 从关键属性检索注册算法策略。
 *
 * \param[in]attributes要查询的键属性结构。
 *
 * \return存储在属性结构中的注册算法。
 */
static inline psa_algorithm_t psa_get_key_enrollment_algorithm(
    const psa_key_attributes_t *attributes)
{
    return( attributes->core.policy.alg2 );
}

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)

/** 检索存储密钥的插槽编号。
 *
 * 插槽编号仅为存储在安全元素中的密钥定义。
 *
 * 仅当安全元素未完全通过PSA Cryptography API管理时，此信息才有用。由安全元件驱动程序决定PSA插槽号如何映射到安全元件可能具有的任何其他接口。
 *
 * \param[in]attributes要查询的键属性结构。\param[out]slot_number成功时，包含密钥的插槽号。
 *
 * \retval#PSA_SUCCESS密钥位于安全元素中，\p slot_number表示包含它的插槽号。\retval#PSA_ERROR_NOT_PERMITTED不允许呼叫者查询槽号。Mbed Crypto当前未返回此错误。\retval#PSA_ERROR_INVALID_ARGUMENT密钥不在安全元素中。
 */
psa_status_t psa_get_key_slot_number(
    const psa_key_attributes_t *attributes,
    psa_key_slot_number_t *slot_number );

/** 选择存储密钥的插槽编号。
 *
 * 此函数在指定的属性结构中声明槽号。
 *
 * 插槽编号仅对存储在安全元素中的密钥有意义。由安全元件驱动程序决定PSA插槽号如何映射到安全元件可能具有的任何其他接口。
 *
 * \注意：在创建密钥时，在密钥属性中设置插槽编号可能会导致以下错误：
 *       -#PSA_ERROR_NOT_SUPPORTED（如果所选安全元件不支持选择特定插槽编号）。
 *       -#PSA_ERROR_NOT_PERMITTED，如果呼叫者一般不允许选择插槽号或选择此特定插槽。
 *       -#PSA_ERROR_INVALID_ARGUMENT，如果所选插槽号通常无效或对该特定密钥无效。
 *       -#PSA_ERROR_ALREADY_EXISTS（如果所选插槽中已存在密钥）。
 *
 * \param[out]attributes要写入的属性结构。\param slot_number要设置的插槽编号。
 */
static inline void psa_set_key_slot_number(
    psa_key_attributes_t *attributes,
    psa_key_slot_number_t slot_number )
{
    attributes->core.flags |= MBEDTLS_PSA_KA_FLAG_HAS_SLOT_NUMBER;
    attributes->slot_number = slot_number;
}

/** 从键属性结构中删除插槽编号属性。
 *
 * 此函数撤消psa_set_key_slot_number（）的操作。
 *
 * \param[out]attributes要写入的属性结构。
 */
static inline void psa_clear_key_slot_number(
    psa_key_attributes_t *attributes )
{
    attributes->core.flags &= ~MBEDTLS_PSA_KA_FLAG_HAS_SLOT_NUMBER;
}

/** 注册安全元素中已存在的密钥。
 *
 * 密钥必须位于由\p属性中的生存期字段指定的安全元素中，位于属性结构中使用psa_set_key_slot_number（）设置的槽中。此函数通过\p属性中指定的密钥标识符使密钥可用。
 *
 * \param[in]attributes现有密钥的属性。
 *
 * \retval#PSA_SUCCESS密钥已成功注册。注意，根据驱动程序的设计，这可能会也可能不会保证密钥实际上存在于指定的插槽中，并且与指定的属性兼容。\retval#PSA_ERROR_ALREADY_EXISTS已存在一个标识符在\p属性中指定的密钥。\retval#PSA_ERROR_NOT_SUPPORTED指定生存期的安全元素驱动程序不支持注册密钥。\retval#PSA_ERROR_INVALID_ARGUMENT \p属性中的标识符无效，即标识符不在用户范围内。\retval#PSA_ERROR_INVALID_ARGUMENT\p属性指定不在安全元素中的生存期。\retval#PSA_ERROR_INVALID_ARGUMENT没有在\p属性中指定插槽号，或者指定的插槽号无效。\retval#PSA_ERROR_NOT_PERMITTED呼叫者无权注册指定的密钥槽。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA _ERROR_INSUFFICE_STORAGE\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_DATA_INVALID\retval＃PSA_ERROR_DATA_CORRUPT\retval#PSA_RROR_CORRUPTION_DETECTED\retval#1PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t mbedtls_psa_register_se_key(
    const psa_key_attributes_t *attributes);

#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

/**@}*/

/**
 * \简短的库取消初始化。
 *
 * 此函数清除与PSA层相关的所有数据，包括整个密钥存储。
 *
 * 这是一个Mbed TLS扩展。
 */
void mbedtls_psa_crypto_free( void );

/** \与PSA密钥库相关的资源消耗的简要统计信息。
 *
 * \注意：此结构的内容不是Mbed Crypto的稳定API和ABI的一部分，可能会因版本而异。
 */
typedef struct mbedtls_psa_stats_s
{
    /**包含易失性密钥的密钥材料的插槽数。*/
    size_t volatile_slots;
    /**包含内部持久存储中密钥的密钥材料的插槽数。*/
    size_t persistent_slots;
    /**包含对安全元素中密钥的引用的插槽数。*/
    size_t external_slots;
    /**已占用但尚未包含关键材料的插槽数。*/
    size_t half_filled_slots;
    /**包含缓存数据的插槽数。*/
    size_t cache_slots;
    /**不用于任何操作的插槽数。*/
    size_t empty_slots;
    /**锁定的插槽数。*/
    size_t locked_slots;
    /**内部持久存储中打开的密钥中最大的密钥id值。*/
    psa_key_id_t max_open_internal_key_id;
    /**安全元素中打开的密钥中最大的密钥id值。*/
    psa_key_id_t max_open_external_key_id;
} mbedtls_psa_stats_t;

/** \brief获取与PSA密钥库相关的资源消耗统计信息。
 *
 * \注意：当Mbed Crypto作为服务的一部分构建时，在应用程序和密钥库之间进行隔离，服务可能会或可能不会公开此功能。
 */
void mbedtls_psa_get_stats( mbedtls_psa_stats_t *stats );

/**
 * \brief将随机生成器的初始熵种子注入安全存储。
 *
 * 此函数注入数据，用作PSA Crypto实现使用的随机生成器的种子。在缺乏可信熵源（最好是硬件随机数生成器）的设备上，Mbed PSA Crypto实现使用该值来生成其随机数生成器。
 *
 * 在没有可信熵源的设备上，该函数必须在设备的生命周期内精确调用一次。在具有可信熵源的设备上，调用此函数是可选的。在所有情况下，只能在调用PSA Crypto API中的任何其他函数（包括PSA_Crypto_init（））之前调用此函数。
 *
 * 当此函数成功返回时，它将在持久存储中填充文件。创建文件后，此功能将无法再成功。
 *
 * 如果发生任何错误，此功能不会更改系统状态。如果可能，可以在更正错误原因后再次调用此函数。
 *
 * \警告此函数**可能**失败！呼叫者必须检查返回状态。
 *
 * \警告如果使用此功能，则应将其作为工厂配置过程的一部分。注入种子的价值对设备的安全至关重要。它必须是秘密的，不可预测的，并且（在统计上）每个设备都是唯一的。您应该使用加密安全的随机生成器从可信熵源中随机生成它。您应该将其安全地传输到设备，并确保其值不会泄漏或存储在任何超出从生成点到调用该函数的传输需要的地方，并在该函数返回后擦除该值的所有副本。
 *
 * 这是一个Mbed TLS扩展。
 *
 * \注意：此函数仅在以下平台上可用：如果启用了编译时选项MBEDTLS_PSA_INJECT_ENTROPY。注意，必须提供mbedtls_nv_seed_read和mbedtls_nv_seed_write的兼容实现。在PSA Cryptography的客户端-服务器集成中，在客户端，如果服务器支持此功能。\param[in]seed缓冲区，包含要注入的种子值。\param[in]seed_size \p种子缓冲区的大小。种子的大小（以字节为单位）必须大于或等于#MBEDTLS_ENTROPRY_MIN_PLATFORM和#MBEDRLS_ENTROPY_BLOCK_size。它必须小于或等于#MBEDTLS_ENTROPY_MAX_SEED_SIZE。
 *
 * \retval#PSA_SUCCESS已成功注入种子值。PSA Crypto实现的随机生成器现在可以使用了。现在可以调用psa_crypto_init（）并使用psa crypto实现。\retval#PSA_ERROR_INVALID_ARGUMENT\p种子大小超出范围。\retval#PSA_ERROR_STORAGE_FAILURE读取或写入存储时出错。\retval#PSA_ERROR_NOT_PERMITTED库已初始化。无法再调用此函数。
 */
psa_status_t mbedtls_psa_inject_entropy(const uint8_t *seed,
                                        size_t seed_size);

/** \添加组密码类型@{
 */

/** DSA公钥。
 *
 * 导入和导出格式是将公钥“y=g^xMod p”表示为大端字节字符串。字节字符串的长度是以字节为单位的基素数“p”的长度。
 */
#define PSA_KEY_TYPE_DSA_PUBLIC_KEY                 ((psa_key_type_t)0x4002)

/** DSA密钥对（私钥和公钥）。
 *
 * 导入和导出格式是将私钥“x”表示为大端字节字符串。字节字符串的长度是以字节为单位的私钥大小（前导零不被去除）。
 *
 * 根据FIPS 186-4&sect；B、 1.2：将字节字符串解释为大端顺序的整数。如果它不在[0，N-2]范围内，其中N是私钥域的边界（Diffie-Hellman的素数p，DSA的次q，或ECC的曲线基点的顺序），则放弃它。将所得整数加1，并将其用作私钥x。
 *
 */
#define PSA_KEY_TYPE_DSA_KEY_PAIR                    ((psa_key_type_t)0x7002)

/**密钥类型是否为DSA密钥（成对或仅公共）。*/
#define PSA_KEY_TYPE_IS_DSA(type)                                       \
    (PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type) == PSA_KEY_TYPE_DSA_PUBLIC_KEY)

#define PSA_ALG_DSA_BASE                        ((psa_algorithm_t)0x06000400)
/** 带有哈希的DSA签名。
 *
 * 这是FIPS 186-4定义的签名方案，具有随机的每条消息秘密编号（k）。
 *
 * \param hash_alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。当在使用策略中指定算法时，这包括#PSA_ALG_ANY_HASH。
 *
 * \return相应的DSA签名算法。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_DSA(hash_alg)                             \
    (PSA_ALG_DSA_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
#define PSA_ALG_DETERMINISTIC_DSA_BASE          ((psa_algorithm_t)0x06000500)
#define PSA_ALG_DSA_DETERMINISTIC_FLAG PSA_ALG_ECDSA_DETERMINISTIC_FLAG
/** 带有哈希的确定性DSA签名。
 *
 * 这是由FIPS 186-4定义的签名方案的RFC 6979定义的确定性变体。
 *
 * \param hash_alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。当在使用策略中指定算法时，这包括#PSA_ALG_ANY_HASH。
 *
 * \return相应的DSA签名算法。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_DETERMINISTIC_DSA(hash_alg)                             \
    (PSA_ALG_DETERMINISTIC_DSA_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
#define PSA_ALG_IS_DSA(alg)                                             \
    (((alg) & ~PSA_ALG_HASH_MASK & ~PSA_ALG_DSA_DETERMINISTIC_FLAG) ==  \
     PSA_ALG_DSA_BASE)
#define PSA_ALG_DSA_IS_DETERMINISTIC(alg)               \
    (((alg) & PSA_ALG_DSA_DETERMINISTIC_FLAG) != 0)
#define PSA_ALG_IS_DETERMINISTIC_DSA(alg)                       \
    (PSA_ALG_IS_DSA(alg) && PSA_ALG_DSA_IS_DETERMINISTIC(alg))
#define PSA_ALG_IS_RANDOMIZED_DSA(alg)                          \
    (PSA_ALG_IS_DSA(alg) && !PSA_ALG_DSA_IS_DETERMINISTIC(alg))


/* 我们需要从API定义扩展此宏的示例定义。*/
#undef PSA_ALG_IS_VENDOR_HASH_AND_SIGN
#define PSA_ALG_IS_VENDOR_HASH_AND_SIGN(alg)    \
    PSA_ALG_IS_DSA(alg)

/**@}*/

/** \addtogroup属性@{
 */

/** 自定义Diffie Hellman组。
 *
 * 对于#PSA_KEY_type_DH_PUBLIC_KEY（#PSA_DH_FAMILY_CUSTOM）或#PSA_KEY _type_DL_KEY_PAIR（#PSD_DH_FAMMILY_CUSTOM）类型的密钥，组数据来自由PSA_set_KEY_domain_parameters（）设置的域参数。
 */
#define PSA_DH_FAMILY_CUSTOM             ((psa_dh_family_t) 0x7e)


/**
 * \brief设置密钥的域参数。
 *
 * 除了密钥类型标识符和密钥大小之外，某些密钥类型还需要其他域参数。当需要指定域参数时，请使用此函数而不是psa_set_key_type（）。
 *
 * 所需域参数的格式因密钥类型而异。
 *
 * -对于RSA密钥（#PSA_KEY_TYPE_RSA_PUBLIC_KEY或#PSA_KEY _TYPE_RSA_KEY_PAIR），域参数数据由公共指数组成，表示为无前导零的大端整数。生成RSA密钥对时使用此信息。导入密钥时，将从导入的密钥数据中读取公共指数，并忽略属性结构中记录的指数。作为例外，公共指数65537由空字节字符串表示。
 * -对于DSA密钥（#PSA_KEY_TYPE_DSA_PUBLIC_KEY或#PSA_KEY _TYPE_DSA _KEY_PAIR），RFC 3279&sect；2.3.2.``Dss-Parms:：=序列{p整数，q整数，g整数}```
 * -对于Diffie-Hellman密钥交换密钥（#PSA_key_TYPE_DH_PUBLIC_key（#PSD_DH_FAMILY_CUSTOM）或#PSA_key _TYPE_DL_key_PAIR（#PS_DH_FAMILY_CUSTOM）），RFC 3279&sect；2.3.3.```域参数：：=序列{p整数，--奇数素数，p=jq+1 g整数，--generator，g q整数，--p-1 j整数的因子可选，--subgroup factor validationParms validationParms OPTIONAL}validationParms:：=序列｛种子位字符串，pgenCounter整数｝```
 *
 * \注意：此功能可分配内存或其他资源。在属性结构上调用此函数后，必须调用psa_reset_key_attributes（）来释放这些资源。
 *
 * \注意：这是对接口的实验性扩展。它可能会在库的未来版本中更改。
 *
 * \param[in，out]attributes将存储指定域参数的属性结构。如果此函数失败，则不会修改\p属性的内容。\param type键类型（a \c PSA_Key_type_XXX值）。\param[in]包含关键域参数的数据缓冲区。此缓冲区的内容根据上述类型进行解释。\param data_length数据缓冲区的大小（字节）。
 *
 * \retval#PSA_SUCCESS\retval#PSA错误_INVALID_ARGUMENT\retval#PSA_ERROR_NOT_SUPPORTED\retval＃PSA_ERROR_INSUFFIE_MEMORY
 */
psa_status_t psa_set_key_domain_parameters(psa_key_attributes_t *attributes,
                                           psa_key_type_t type,
                                           const uint8_t *data,
                                           size_t data_length);

/**
 * \brief获取密钥的域参数。
 *
 * 使用此函数获取密钥的域参数（如果有）。写入数据的域参数的格式在psa_set_key_domain_parameters（）的文档中指定。
 *
 * \注意：这是对接口的实验性扩展。它可能会在库的未来版本中更改。
 *
 * \param[in]attributes要查询的键属性结构。\param[out]data成功时，关键域参数。\param data_size数据缓冲区的大小（字节）。如果缓冲区的字节大小至少为PSA_KEY_DOMAIN_PARAMETERS_size（）给定的值，则保证缓冲区足够大。\param[out]data_length成功时，构成关键域参数数据的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSA错误_BUFFER_TOO_SMALL
 */
psa_status_t psa_get_key_domain_parameters(
    const psa_key_attributes_t *attributes,
    uint8_t *data,
    size_t data_size,
    size_t *data_length);

/** psa_get_key_domain_parameters（）的安全输出缓冲区大小。
 *
 * 如果此宏的参数是编译时常量，则返回编译时常量。
 *
 * \警告此函数可能多次或零次调用其参数，因此不应传递包含副作用的参数。
 *
 * \注意：这是对接口的实验性扩展。它可能会在库的未来版本中更改。
 *
 * \param key_type支持的密钥类型。\param key_bits密钥的大小（以位为单位）。
 *
 * \return如果参数有效且受支持，则返回以字节为单位的缓冲区大小，以确保psa_get_key_domain_parameters（）不会因#psa_ERROR_buffer_TOO_SMALL而失败。如果参数是实现不支持的有效组合，则此宏应返回合理大小或0。如果参数无效，则返回值未指定。
 */
#define PSA_KEY_DOMAIN_PARAMETERS_SIZE(key_type, key_bits)              \
    (PSA_KEY_TYPE_IS_RSA(key_type) ? sizeof(int) :                      \
     PSA_KEY_TYPE_IS_DH(key_type) ? PSA_DH_KEY_DOMAIN_PARAMETERS_SIZE(key_bits) : \
     PSA_KEY_TYPE_IS_DSA(key_type) ? PSA_DSA_KEY_DOMAIN_PARAMETERS_SIZE(key_bits) : \
     0)
#define PSA_DH_KEY_DOMAIN_PARAMETERS_SIZE(key_bits)     \
    (4 + (PSA_BITS_TO_BYTES(key_bits) + 5) * 3 /*无可选部件*/)
#define PSA_DSA_KEY_DOMAIN_PARAMETERS_SIZE(key_bits)    \
    (4 + (PSA_BITS_TO_BYTES(key_bits) + 5) * 2 /*p、 克*/ + 34 /*q*/)

/**@}*/

/** \defgroup psa_tls_helpers tls助手函数@{
 */

#if defined(MBEDTLS_ECP_C)
#include <mbedtls/ecp.h>

/** 将ECC曲线标识符从Mbed TLS编码转换为PSA。
 *
 * \注意：此功能仅为方便Mbed TLS而提供，可随时删除，恕不另行通知。
 *
 * \param grpid一个Mbed TLS椭圆曲线标识符（`MBEDTLS_EP_DP_xxx`）。\param[out]bits成功时，曲线的位大小。
 *
 * \return对应的PSA椭圆曲线标识符（`PSA_ECC_FAMILY_xxx`）。\失败时返回\c 0（无法识别\p grpid）。
 */
static inline psa_ecc_family_t mbedtls_ecc_group_to_psa( mbedtls_ecp_group_id grpid,
                                                        size_t *bits )
{
    switch( grpid )
    {
        case MBEDTLS_ECP_DP_SECP192R1:
            *bits = 192;
            return( PSA_ECC_FAMILY_SECP_R1 );
        case MBEDTLS_ECP_DP_SECP224R1:
            *bits = 224;
            return( PSA_ECC_FAMILY_SECP_R1 );
        case MBEDTLS_ECP_DP_SECP256R1:
            *bits = 256;
            return( PSA_ECC_FAMILY_SECP_R1 );
        case MBEDTLS_ECP_DP_SECP384R1:
            *bits = 384;
            return( PSA_ECC_FAMILY_SECP_R1 );
        case MBEDTLS_ECP_DP_SECP521R1:
            *bits = 521;
            return( PSA_ECC_FAMILY_SECP_R1 );
        case MBEDTLS_ECP_DP_BP256R1:
            *bits = 256;
            return( PSA_ECC_FAMILY_BRAINPOOL_P_R1 );
        case MBEDTLS_ECP_DP_BP384R1:
            *bits = 384;
            return( PSA_ECC_FAMILY_BRAINPOOL_P_R1 );
        case MBEDTLS_ECP_DP_BP512R1:
            *bits = 512;
            return( PSA_ECC_FAMILY_BRAINPOOL_P_R1 );
        case MBEDTLS_ECP_DP_CURVE25519:
            *bits = 255;
            return( PSA_ECC_FAMILY_MONTGOMERY );
        case MBEDTLS_ECP_DP_SECP192K1:
            *bits = 192;
            return( PSA_ECC_FAMILY_SECP_K1 );
        case MBEDTLS_ECP_DP_SECP224K1:
            *bits = 224;
            return( PSA_ECC_FAMILY_SECP_K1 );
        case MBEDTLS_ECP_DP_SECP256K1:
            *bits = 256;
            return( PSA_ECC_FAMILY_SECP_K1 );
        case MBEDTLS_ECP_DP_CURVE448:
            *bits = 448;
            return( PSA_ECC_FAMILY_MONTGOMERY );
        default:
            *bits = 0;
            return( 0 );
    }
}

/** 将PSA编码中的ECC曲线标识符转换为Mbed TLS。
 *
 * \注意：此功能仅为方便Mbed TLS而提供，可随时删除，恕不另行通知。
 *
 * \param curve A PSA椭圆曲线标识符（`PSA_ECC_FAMILY_xxx`）。\param bits曲线上私钥的位长度。\param bits_is_sloppy如果为真，\p位可以是位长度，四舍五入到最接近的8的倍数。这允许调用者根据以字节字符串形式提供的密钥的长度推断出精确的曲线。
 *
 * \return对应的Mbed TLS椭圆曲线标识符（`MBEDTLS_EP_DP_xxx`）。\如果未识别\c曲线，则返回#MBEDTLS_ECP_DP_NONE。\如果\p位对于\p曲线不正确，则返回#MBEDTLS_EP_DP_NONE。
 */
mbedtls_ecp_group_id mbedtls_ecc_group_of_psa( psa_ecc_family_t curve,
                                               size_t bits,
                                               int bits_is_sloppy );
#endif /* MBEDTLS_ECP_C */

/**@}*/

/** \defgroup psa_external_rng外部随机生成器@{
 */

#if defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)
/** 外部随机生成器功能，由平台实现。
 *
 * 当启用编译时选项#MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG时，此函数将替换通过PSA加密接口触发的所有随机生成的Mbed TLS熵和DRBG模块。
 *
 * \注意：此随机生成器必须提供具有加密质量和高性能的随机数。它必须提供均匀分布的不可预测的数字。该函数的实现负责确保随机生成器被播种有足够的熵。如果硬件TRNG速度慢或输出不均匀，请使用mbedtls_entropy_add_source（）将其声明为熵源，而不是启用此选项。
 *
 * \param[in，out]context指向随机生成器上下文的指针。这是第一次调用时的所有零位，并在连续调用之间保留。\param[out]输出输出缓冲区。成功后，此缓冲区包含均匀分布的随机数据。\param output_size输出缓冲区的大小（以字节为单位）。\param[out]output_length成功后，将此值设置为\p output_size。
 *
 * \retval#PSA_SUCCESS成功。输出缓冲区包含\p output_size字节的加密质量随机数据，并且\c output_length设置为\p outut_size。\retval#PSA_ERROR_INSUFFIE_ENTROPY随机生成器需要额外的熵，在当前环境条件下无法获得熵。在正常情况下不应该发生这种错误，因为该函数负责获得所需的熵。然而，如果无法在不无限期阻塞的情况下获得熵，则此函数的实现可能返回#PSA_ERROR_INSUFFIE_ENTROPY。\retval#PSA_ERROR_HARDWARE_FAILURE#PSA_ERROR_INSUFFIE_ENTROPY未涵盖的随机生成器硬件故障。
 */
psa_status_t mbedtls_psa_external_get_random(
    mbedtls_psa_external_random_context_t *context,
    uint8_t *output, size_t output_size, size_t *output_length );
#endif /* MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG */

/**@}*/

/** \defgroup psa_iltin_keys内置密钥@{
 */

/** 内置于实现中的密钥标识符的最小值。
 *
 * 在#PSA_key_ID_VENDOR_MIN和#PSA_key _ID_VENTOR_MAX的范围内，从#MBEDTLS_PSA_key-ID_BUILTIN_MIN到#MBEDTLS_PSA_key-ID_BUMILTIN_MAX的密钥标识符范围，并且不得与任何其他实现选择的密钥标识符集相交。
 *
 * 该值是库ABI的一部分，因为更改它会使应用程序中内置键标识符的值无效。
 */
#define MBEDTLS_PSA_KEY_ID_BUILTIN_MIN          ((psa_key_id_t)0x7fff0000)

/** 内置于实现中的密钥标识符的最大值。
 *
 * 有关详细信息，请参阅#MBEDTLS_PSA_KEY_ID_BUILTIN_MIN。
 */
#define MBEDTLS_PSA_KEY_ID_BUILTIN_MAX          ((psa_key_id_t)0x7fffefff)

/** 标识驱动程序中密钥的插槽号。
 *
 * 此类型的值用于标识内置键。
 */
typedef uint64_t psa_drv_slot_number_t;

#if defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
/** 测试密钥标识符是否属于内置密钥范围。
 *
 * \param key_id要测试的密钥标识符。
 *
 * \retval 1密钥标识符是内置密钥标识符。\retval 0密钥标识符不是内置密钥标识符。
 */
static inline int psa_key_id_is_builtin( psa_key_id_t key_id )
{
    return( ( key_id >= MBEDTLS_PSA_KEY_ID_BUILTIN_MIN ) &&
            ( key_id <= MBEDTLS_PSA_KEY_ID_BUILTIN_MAX ) );
}

/** 获取内置密钥的位置和插槽号的平台函数。
 *
 * 如果启用了#MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS，则必须提供此函数的特定于应用程序的实现。这通常作为平台系统映像的一部分提供。
 *
 * #MBEDTLS_SVC_KEY_ID_GET_KEY_ID（\p KEY_ID）必须在#MBEDTLS_PSA_KEY_ID_BUILTIN_MIN到#MBEDLLS_PSA_KEY-ID_BUILDIN_MAX的范围内。
 *
 * 在多应用程序配置中（定义了MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER），此函数应检查是否允许#MBEDTLS_SVC_KEY_ID_GET_OWNER_ID（\p KEY_ID）使用给定密钥。
 *
 * \param key_id要检索其位置和插槽属性的密钥id。\param[out]lifetime成功时，与对应于\p key_id的密钥关联的生存期。生存期是哪个驱动程序包含密钥，以及密钥打算使用的持久性级别的组合。如果平台实现不包含有关预期密钥持久性级别的特定信息，则持久性级别可以报告为#PSA_key_persistence_DEFAULT。\param[out]slot_number成功时，驱动程序在通过\p生存期报告的生存期位置注册的已知插槽号，该位置对应于请求的内置密钥。
 *
 * \retval#PSA_SUCCESS请求的密钥标识符指定内置密钥。在多应用程序配置中，允许请求的所有者访问它。\retval#PSA_ERROR_DOES_NOT_EXIST请求的密钥标识符不是此函数已知的内置密钥。如果密钥存储中存在具有此标识符的密钥，则将使用存储中的数据。\return（任何其他错误）任何其他错误都会传播到请求密钥的函数。常见错误包括：
 *         -#PSA_ERROR_NOT_PERMITTED：密钥存在，但不允许请求的所有者访问它。
 */
psa_status_t mbedtls_psa_platform_get_builtin_key(
    mbedtls_svc_key_id_t key_id,
    psa_key_lifetime_t *lifetime,
    psa_drv_slot_number_t *slot_number );
#endif /* MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_EXTRA_H */

