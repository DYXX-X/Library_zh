/**
 * \psa/crypto_values.h文件
 *
 * \PSA密码模块简介：构建和分析整数值的宏。
 *
 * \注意：此文件可能不直接包含。应用程序必须包含psa/crypto.h。驱动程序必须包含相应的驱动程序头文件。
 *
 * 此文件包含宏的可移植定义，用于构建和分析整数类型的值，这些值编码加密密钥的属性、加密算法的指定以及库返回的错误代码。
 *
 * 此头文件仅定义预处理器宏。
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

#ifndef PSA_CRYPTO_VALUES_H
#define PSA_CRYPTO_VALUES_H

/** \defgroup错误错误代码@{
 */

/* PSA错误代码*/

/**操作已成功完成。*/
#define PSA_SUCCESS ((psa_status_t)0)

/** 发生的错误与任何定义的故障原因都不对应。
 *
 * 如果其他标准错误代码均不适用，则实施可能会使用此错误代码。*/
#define PSA_ERROR_GENERIC_ERROR         ((psa_status_t)-132)

/** 此实现不支持请求的操作或参数。
 *
 * 当无法识别枚举参数（如密钥类型、算法等）时，实现应返回此错误代码。如果参数组合被识别为无效，则返回#PSA_ERROR_INVALID_ARGUMENT。*/
#define PSA_ERROR_NOT_SUPPORTED         ((psa_status_t)-134)

/** 请求的操作被策略拒绝。
 *
 * 当参数被识别为有效且受支持，并且策略明确拒绝请求的操作时，实现应返回此错误代码。
 *
 * 如果函数调用的一个子集参数标识了禁止的操作，而另一个子集的参数无效或不受支持，则未指定函数是否返回#PSA_ERROR_not_PERMITTED、#PSA_ERROR_not_supported或#PSA_RROR_INVALID_ARGUMENT。*/
#define PSA_ERROR_NOT_PERMITTED         ((psa_status_t)-133)

/** 输出缓冲区太小。
 *
 * 应用程序可以调用函数描述中列出的\c PSA_xx_SIZE宏来确定足够的缓冲区大小。
 *
 * 只有在使用较大的输出缓冲区执行操作成功的情况下，实现才最好返回此错误代码。但是，如果函数除了确定必要的输出缓冲区大小的参数之外，还具有无效或不受支持的参数，则实现可能会返回此错误。*/
#define PSA_ERROR_BUFFER_TOO_SMALL      ((psa_status_t)-138)

/** 请求已存在的项目
 *
 * 当尝试写入已存在的项（如键）时，实现应返回此错误。*/
#define PSA_ERROR_ALREADY_EXISTS        ((psa_status_t)-139)

/** 请求不存在的项目
 *
 * 如果请求的项（如键）不存在，则实现应返回此错误。*/
#define PSA_ERROR_DOES_NOT_EXIST        ((psa_status_t)-140)

/** 无法在当前状态下执行请求的操作。
 *
 * 当其中一个函数被无序调用时，多部分操作返回此错误。有关允许的功能顺序，请参阅功能说明。
 *
 * 实现不应返回此错误代码以指示密钥是否存在，而是应返回#PSA_error_ALREADY_exists或#PSA_error_DOES_not_EXIST（如适用）。
 *
 * 实现不应返回此错误代码以指示密钥标识符无效，而是应返回#PSA_error_invalid_HANDLE。*/
#define PSA_ERROR_BAD_STATE             ((psa_status_t)-137)

/** 传递给函数的参数无效。
 *
 * 每当参数或参数组合被识别为无效时，实现都可能返回此错误。
 *
 * 实现不应返回此错误代码以指示密钥标识符无效，而是应返回#PSA_error_invalid_HANDLE。
 */
#define PSA_ERROR_INVALID_ARGUMENT      ((psa_status_t)-135)

/** 运行时内存不足。
 *
 * 如果该操作在多个安全领域中执行，则此错误可能涉及任何安全领域中的可用内存。*/
#define PSA_ERROR_INSUFFICIENT_MEMORY   ((psa_status_t)-141)

/** 持久性存储不足。
 *
 * 如果主机介质上的存储空间不足，则修改密钥存储的函数将返回此错误代码。此外，如果实现要求对请求的操作强制输入日志并且日志存储空间已满，则许多不访问存储的函数可能会返回此错误代码。*/
#define PSA_ERROR_INSUFFICIENT_STORAGE  ((psa_status_t)-142)

/** 实现内部存在通信故障。
 *
 * 这可以指示应用程序与外部密码处理器之间或密码处理器与外部易失性或持久性存储器之间的通信故障。通信故障可能是暂时性的，也可能是永久性的，具体取决于原因。
 *
 * \警告如果函数返回此错误，则无法确定请求的操作是否已完成。只要可能，实现应在成功完成时返回#PSA_SUCCESS，但如果请求的操作在外部密码处理器中成功完成，但在密码处理器向应用程序报告状态之前通信中断，则函数可能返回#PSE_ERROR_COMMUNICATION_FAILURE。
 */
#define PSA_ERROR_COMMUNICATION_FAILURE ((psa_status_t)-145)

/** 存储故障可能导致数据丢失。
 *
 * 此错误表示某些永久性存储已损坏。不应将其用于易失性内存损坏（使用#PSA_ERROR_corruption_DETECTED）、密码处理器与其外部存储之间的通信错误（使用#PSA _ERROR_communication_FAILURE）或存储处于有效状态但已满（使用#PS a_ERROR_INSUFFIE_storage）。
 *
 * 请注意，存储故障并不表示以前读取的任何数据都无效。然而，此先前读取的数据可能不再可从存储器读取。
 *
 * 当发生存储故障时，不再可能确保密钥库的全局完整性。根据实现提供的全局完整性保证，即使数据仍然可读，但无法保证其完整性，对其他数据的访问可能会失败，也可能不会失败。
 *
 * 实施应仅使用此错误代码报告永久存储损坏。但是，应用程序编写者应该记住，读取存储时可能会使用此错误代码报告暂时错误。*/
#define PSA_ERROR_STORAGE_FAILURE       ((psa_status_t)-146)

/** 检测到硬件故障。
 *
 * 硬件故障可能是暂时性或永久性的，具体取决于原因。*/
#define PSA_ERROR_HARDWARE_FAILURE      ((psa_status_t)-147)

/** 检测到篡改尝试。
 *
 * 如果应用程序收到此错误代码，则不能保证以前访问或计算的数据是正确的，并且是保密的。应用程序不应执行任何安全功能，应进入安全故障状态。
 *
 * 如果实现检测到在正常操作期间无法发生的无效状态，并且表示实现的安全保证不再有效，则可能返回此错误代码。根据实现架构及其安全和安全目标，实现可以强制终止应用程序。
 *
 * 当检测到安全漏洞并且不确定密钥库数据是否仍然受到保护时，此错误代码是最后的手段。实施应仅返回此错误代码，以报告来自篡改检测器的警报，指示存储数据的机密性无法再得到保证，或指示先前返回的数据的完整性现在被认为受到损害。实现不应使用此错误代码来指示仅使其无法执行所请求操作的硬件故障（改用#PSA_error_COMMUNICATION_failure、#PSA_error_STORAGE_FAILUE、#PSE_error_hardware_FAILULE、#PSA-error_INSUFFIE_ENTROPY或其他适用的错误代码）。
 *
 * 此错误表示应用程序受到攻击。实现不应因应用程序本身的行为而返回此错误代码。*/
#define PSA_ERROR_CORRUPTION_DETECTED    ((psa_status_t)-151)

/** 没有足够的熵来生成所请求的操作所需的随机数据。
 *
 * 此错误表示硬件随机生成器出现故障。应用程序编写者应注意，这种错误不仅可以由目的是生成随机数据的函数返回，例如密钥、IV或随机数生成，也可以由执行具有随机化结果的算法的函数以及使用中间计算的随机化作为对某些攻击的对策的函数返回。
 *
 * 实现应避免在psa_crypto_init（）成功后返回此错误。实现应该在初始化期间生成足够的熵，然后使用加密安全的伪随机生成器（PRNG）。但是，如果策略要求在正常操作期间重新设定PRNG种子，则实现可能随时返回此错误。*/
#define PSA_ERROR_INSUFFICIENT_ENTROPY  ((psa_status_t)-148)

/** 签名、MAC或哈希不正确。
 *
 * 如果验证计算成功完成，并且要验证的值被确定为不正确，验证函数将返回此错误。
 *
 * 如果要验证的值的大小无效，则实现可能返回#PSA_ERROR_invalid_ARGUMENT或#PSA_ERROR_invalid_SIGNATURE。*/
#define PSA_ERROR_INVALID_SIGNATURE     ((psa_status_t)-149)

/** 解密的填充不正确。
 *
 * \警告在某些协议中，当解密数据时，应用程序的行为不取决于填充是否正确，直到精确的定时。应用程序应该更喜欢使用经过身份验证的加密而不是普通加密的协议。如果应用程序必须对未经验证的数据进行解密，则应用程序编写者应注意不要泄露填充是否无效。
 *
 * 实现应该努力使有效和无效的填充尽可能接近外部观察者无法区分。特别地，解密操作的定时不应取决于填充的有效性。*/
#define PSA_ERROR_INVALID_PADDING       ((psa_status_t)-150)

/**尝试读取资源时，如果数据不足，则返回此错误。*/
#define PSA_ERROR_INSUFFICIENT_DATA     ((psa_status_t)-143)

/** 密钥标识符无效。另请参见：ref:\`key handles\`。
 */
#define PSA_ERROR_INVALID_HANDLE        ((psa_status_t)-136)

/**@}*/

/** \defgroup crypto_types密钥和算法类型@{
 */

/** 无效的键类型值。
 *
 * 零不是任何密钥类型的编码。
 */
#define PSA_KEY_TYPE_NONE                           ((psa_key_type_t)0x0000)

/** 供应商定义的密钥类型标志。
 *
 * 本标准定义的密钥类型永远不会设置#PSA_Key_TYPE_VENDOR_FLAG位。定义其他密钥类型的供应商必须使用带有#PSA_key_TYPE_VENDOR_FLAG位集的编码，并且应尽可能尊重标准编码所使用的按位结构。
 */
#define PSA_KEY_TYPE_VENDOR_FLAG                    ((psa_key_type_t)0x8000)

#define PSA_KEY_TYPE_CATEGORY_MASK                  ((psa_key_type_t)0x7000)
#define PSA_KEY_TYPE_CATEGORY_RAW                   ((psa_key_type_t)0x1000)
#define PSA_KEY_TYPE_CATEGORY_SYMMETRIC             ((psa_key_type_t)0x2000)
#define PSA_KEY_TYPE_CATEGORY_PUBLIC_KEY            ((psa_key_type_t)0x4000)
#define PSA_KEY_TYPE_CATEGORY_KEY_PAIR              ((psa_key_type_t)0x7000)

#define PSA_KEY_TYPE_CATEGORY_FLAG_PAIR             ((psa_key_type_t)0x3000)

/** 密钥类型是否由供应商定义。
 *
 * 另请参阅#PSA_KEY_TYPE_VENDOR_FLAG。
 */
#define PSA_KEY_TYPE_IS_VENDOR_DEFINED(type) \
    (((type) & PSA_KEY_TYPE_VENDOR_FLAG) != 0)

/** 密钥类型是否为非结构化字节数组。
 *
 * 这包括对称密钥和非密钥数据。
 */
#define PSA_KEY_TYPE_IS_UNSTRUCTURED(type) \
    (((type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_RAW || \
     ((type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_SYMMETRIC)

/**密钥类型是否不对称：密钥对或公钥。*/
#define PSA_KEY_TYPE_IS_ASYMMETRIC(type)                                \
    (((type) & PSA_KEY_TYPE_CATEGORY_MASK                               \
      & ~PSA_KEY_TYPE_CATEGORY_FLAG_PAIR) ==                            \
     PSA_KEY_TYPE_CATEGORY_PUBLIC_KEY)
/**密钥类型是否是密钥对的公共部分。*/
#define PSA_KEY_TYPE_IS_PUBLIC_KEY(type)                                \
    (((type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_PUBLIC_KEY)
/**密钥类型是否是包含私有部分和公共部分的密钥对。*/
#define PSA_KEY_TYPE_IS_KEY_PAIR(type)                                   \
    (((type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_KEY_PAIR)
/** 与公钥类型相对应的密钥对类型。
 *
 * 您也可以将密钥对类型作为\p类型传递，它将保持不变。
 *
 * \param type公钥类型或密钥对类型。
 *
 * \return对应的密钥对类型。如果\p类型不是公钥或密钥对，则返回值未定义。
 */
#define PSA_KEY_TYPE_KEY_PAIR_OF_PUBLIC_KEY(type)        \
    ((type) | PSA_KEY_TYPE_CATEGORY_FLAG_PAIR)
/** 与密钥对类型相对应的公钥类型。
 *
 * 您也可以将密钥对类型作为\p类型传递，它将保持不变。
 *
 * \param type公钥类型或密钥对类型。
 *
 * \return对应的公钥类型。如果\p类型不是公钥或密钥对，则返回值未定义。
 */
#define PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type)        \
    ((type) & ~PSA_KEY_TYPE_CATEGORY_FLAG_PAIR)

/** 原始数据。
 *
 * 此类型的“密钥”不能用于任何加密操作。应用程序可以使用此类型在密钥库中存储任意数据。*/
#define PSA_KEY_TYPE_RAW_DATA                       ((psa_key_type_t)0x1001)

/** HMAC键。
 *
 * 密钥策略决定密钥可以用于哪个底层哈希算法。
 *
 * HMAC密钥通常应具有与基础哈希相同的大小。此大小可以使用#PSA_HAH_size（\c alg）计算，其中\c alj是HMAC算法或基础哈希算法。*/
#define PSA_KEY_TYPE_HMAC                           ((psa_key_type_t)0x1100)

/** 密钥派生的秘密。
 *
 * 密钥策略确定密钥可以用于哪个密钥导出算法。
 */
#define PSA_KEY_TYPE_DERIVE                         ((psa_key_type_t)0x1200)

/** 基于AES分组密码的密码、AEAD或MAC算法的密钥。
 *
 * 密钥的大小可以是16字节（AES-128）、24字节（AES-192）或32字节（AES-256）。
 */
#define PSA_KEY_TYPE_AES                            ((psa_key_type_t)0x2400)

/** 基于DES或3DES（三重DES）的密码或MAC算法的密钥。
 *
 * 密钥的大小可以是8字节（单个DES）、16字节（2密钥3DES）或24字节（3密钥3DES。
 *
 * 请注意，单个DES和2密钥3DES是脆弱的，强烈反对使用，只应用于解密旧数据。3键3DES功能较弱，已被弃用，只能在传统协议中使用。
 */
#define PSA_KEY_TYPE_DES                            ((psa_key_type_t)0x2301)

/**基于Camellia分组密码的密码、AEAD或MAC算法的密钥。*/
#define PSA_KEY_TYPE_CAMELLIA                       ((psa_key_type_t)0x2403)

/** RC4流密码的密钥。
 *
 * 请注意，RC4很弱，不推荐使用，只应在遗留协议中使用。*/
#define PSA_KEY_TYPE_ARC4                           ((psa_key_type_t)0x2002)

/** ChaCha20流密码或ChaCha20-Poly1305 AEAD算法的密钥。
 *
 * ChaCha20和ChaCha20_Poly1305构造在RFC 7539中定义。
 *
 * 实现必须支持12字节随机数，可以支持8字节随机数并且应该拒绝其他大小。
 */
#define PSA_KEY_TYPE_CHACHA20                       ((psa_key_type_t)0x2004)

/**RSA公钥。*/
#define PSA_KEY_TYPE_RSA_PUBLIC_KEY                 ((psa_key_type_t)0x4001)
/**RSA密钥对（私钥和公钥）。*/
#define PSA_KEY_TYPE_RSA_KEY_PAIR                   ((psa_key_type_t)0x7001)
/**密钥类型是否为RSA密钥（成对或仅为公钥）。*/
#define PSA_KEY_TYPE_IS_RSA(type)                                       \
    (PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type) == PSA_KEY_TYPE_RSA_PUBLIC_KEY)

#define PSA_KEY_TYPE_ECC_PUBLIC_KEY_BASE            ((psa_key_type_t)0x4100)
#define PSA_KEY_TYPE_ECC_KEY_PAIR_BASE              ((psa_key_type_t)0x7100)
#define PSA_KEY_TYPE_ECC_CURVE_MASK                 ((psa_key_type_t)0x00ff)
/** 椭圆曲线密钥对。
 *
 * \param curve类型为：：psa_ecc_family_t的值，用于标识要使用的ecc曲线。
 */
#define PSA_KEY_TYPE_ECC_KEY_PAIR(curve)         \
    (PSA_KEY_TYPE_ECC_KEY_PAIR_BASE | (curve))
/** 椭圆曲线公钥。
 *
 * \param curve类型为：：psa_ecc_family_t的值，用于标识要使用的ecc曲线。
 */
#define PSA_KEY_TYPE_ECC_PUBLIC_KEY(curve)              \
    (PSA_KEY_TYPE_ECC_PUBLIC_KEY_BASE | (curve))

/**密钥类型是否为椭圆曲线密钥（成对或仅公开）。*/
#define PSA_KEY_TYPE_IS_ECC(type)                                       \
    ((PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type) &                        \
      ~PSA_KEY_TYPE_ECC_CURVE_MASK) == PSA_KEY_TYPE_ECC_PUBLIC_KEY_BASE)
/**密钥类型是否为椭圆曲线密钥对。*/
#define PSA_KEY_TYPE_IS_ECC_KEY_PAIR(type)                               \
    (((type) & ~PSA_KEY_TYPE_ECC_CURVE_MASK) ==                         \
     PSA_KEY_TYPE_ECC_KEY_PAIR_BASE)
/**密钥类型是否为椭圆曲线公钥。*/
#define PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(type)                            \
    (((type) & ~PSA_KEY_TYPE_ECC_CURVE_MASK) ==                         \
     PSA_KEY_TYPE_ECC_PUBLIC_KEY_BASE)

/**从椭圆曲线关键点类型中提取曲线。*/
#define PSA_KEY_TYPE_ECC_GET_FAMILY(type)                        \
    ((psa_ecc_family_t) (PSA_KEY_TYPE_IS_ECC(type) ?             \
                        ((type) & PSA_KEY_TYPE_ECC_CURVE_MASK) : \
                        0))

/** SEC Koblitz在素场上的曲线。
 *
 * 该系列包括以下曲线：secp192k1、secp224k1、secp256k1。它们在_高效密码标准_、_SEC 2：推荐椭圆曲线域参数_中定义。https://www.secg.org/sec2-v2.pdf
 */
#define PSA_ECC_FAMILY_SECP_K1           ((psa_ecc_family_t) 0x17)

/** 素场上的SEC随机曲线。
 *
 * 该系列包括以下曲线：secp192k1、secp224r1、secp256r1、secp384r1、secp521r1。它们在_高效密码标准_、_SEC 2：推荐椭圆曲线域参数_中定义。https://www.secg.org/sec2-v2.pdf
 */
#define PSA_ECC_FAMILY_SECP_R1           ((psa_ecc_family_t) 0x12)
/* SECP160R2（SEC2 v1，过时）*/
#define PSA_ECC_FAMILY_SECP_R2           ((psa_ecc_family_t) 0x1b)

/** SEC Koblitz在二进制字段上的曲线。
 *
 * 该系列由以下曲线组成：sect163k1、sect233k1、Sec239k1、sec283k1、ec409k1和Sec571k1。它们在_高效密码标准_、_SEC 2：推荐椭圆曲线域参数_中定义。https://www.secg.org/sec2-v2.pdf
 */
#define PSA_ECC_FAMILY_SECT_K1           ((psa_ecc_family_t) 0x27)

/** 二进制字段上的SEC随机曲线。
 *
 * 该系列包括以下曲线：sect163r1、sect233r1、sect283r1、sect409r1、sect571r1。它们在_高效加密标准_、_SEC 2：推荐椭圆曲线域参数_中定义。https://www.secg.org/sec2-v2.pdf
 */
#define PSA_ECC_FAMILY_SECT_R1           ((psa_ecc_family_t) 0x22)

/** SEC二进制字段上的附加随机曲线。
 *
 * 该系列包括以下曲线：sect163r2。它在_Standards for Efficient Cryptography_，_SEC 2:Recommended Elliptic curve Domain Parameters_中定义。https://www.secg.org/sec2-v2.pdf
 */
#define PSA_ECC_FAMILY_SECT_R2           ((psa_ecc_family_t) 0x2b)

/** Brainpool P随机曲线。
 *
 * 该系列包括以下曲线：脑池P160r1、脑池P192r1、脑池P224r1、脑水池P256r1、脑池子P320r1、脑汇集P384r1、脑汇聚P512r1。其定义见RFC 5639。
 */
#define PSA_ECC_FAMILY_BRAINPOOL_P_R1    ((psa_ecc_family_t) 0x30)

/** 曲线25519和曲线448。
 *
 * 该族包括以下蒙哥马利曲线：
 * -255位：Bernstein等人，_Curve25519：新的Diffie-Hellman速度记录，LNCS 39582006。当与此曲线一起使用时，#PSA_AG_ECDH算法执行X25519。
 * -448位：Hamburg，_Ed448-Goldlocks，一种新的椭圆曲线，NIST ECC研讨会，2015年。当与此曲线一起使用时，#PSA_ALG_ECDH算法执行X448。
 */
#define PSA_ECC_FAMILY_MONTGOMERY        ((psa_ecc_family_t) 0x41)

#define PSA_KEY_TYPE_DH_PUBLIC_KEY_BASE             ((psa_key_type_t)0x4200)
#define PSA_KEY_TYPE_DH_KEY_PAIR_BASE               ((psa_key_type_t)0x7200)
#define PSA_KEY_TYPE_DH_GROUP_MASK                  ((psa_key_type_t)0x00ff)
/** Diffie Hellman密钥对。
 *
 * \param group类型为：psa_dh_family_t的值，用于标识要使用的Diffie-Hellman组。
 */
#define PSA_KEY_TYPE_DH_KEY_PAIR(group)          \
    (PSA_KEY_TYPE_DH_KEY_PAIR_BASE | (group))
/** Diffie Hellman公钥。
 *
 * \param group类型为：psa_dh_family_t的值，用于标识要使用的Diffie-Hellman组。
 */
#define PSA_KEY_TYPE_DH_PUBLIC_KEY(group)               \
    (PSA_KEY_TYPE_DH_PUBLIC_KEY_BASE | (group))

/**密钥类型是否为Diffie-Hellman密钥（成对或仅公开）。*/
#define PSA_KEY_TYPE_IS_DH(type)                                        \
    ((PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type) &                        \
      ~PSA_KEY_TYPE_DH_GROUP_MASK) == PSA_KEY_TYPE_DH_PUBLIC_KEY_BASE)
/**密钥类型是否为Diffie-Hellman密钥对。*/
#define PSA_KEY_TYPE_IS_DH_KEY_PAIR(type)                               \
    (((type) & ~PSA_KEY_TYPE_DH_GROUP_MASK) ==                         \
     PSA_KEY_TYPE_DH_KEY_PAIR_BASE)
/**密钥类型是否为Diffie-Hellman公钥。*/
#define PSA_KEY_TYPE_IS_DH_PUBLIC_KEY(type)                            \
    (((type) & ~PSA_KEY_TYPE_DH_GROUP_MASK) ==                         \
     PSA_KEY_TYPE_DH_PUBLIC_KEY_BASE)

/**从Diffie-Hellman密钥类型中提取组。*/
#define PSA_KEY_TYPE_DH_GET_FAMILY(type)                        \
    ((psa_dh_family_t) (PSA_KEY_TYPE_IS_DH(type) ?              \
                       ((type) & PSA_KEY_TYPE_DH_GROUP_MASK) :  \
                       0))

/** RFC 7919附录A中定义的Diffie-Hellman组。
 *
 * 此系列包括具有以下密钥大小（以位为单位）的组：2048、3072、4096、6144、8192。给定的实现可能支持所有这些大小或仅支持一个子集。
 */
#define PSA_DH_FAMILY_RFC7919            ((psa_dh_family_t) 0x03)

#define PSA_GET_KEY_TYPE_BLOCK_SIZE_EXPONENT(type)      \
    (((type) >> 8) & 7)
/** 块密码的块大小。
 *
 * \param type密码密钥类型（类型#psa_key_type_t的值）。
 *
 * \return块密码的块大小，或流密码的1。如果\p类型不是受支持的密码密钥类型，则返回值未定义。
 *
 * \注：可以在分组密码的基础上构建流密码算法，例如CTR模式（#PSA_AG_CTR）。此宏只考虑密钥类型，因此不能用于确定#psa_cipher_update（）可能缓冲的数据大小，以供将来处理。
 *
 * \注意：如果此宏的参数为1，则返回编译时间常数。
 *
 * \警告此宏可能会多次计算其参数。
 */
#define PSA_BLOCK_CIPHER_BLOCK_SIZE(type)            \
    (((type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_SYMMETRIC ? \
     1u << PSA_GET_KEY_TYPE_BLOCK_SIZE_EXPONENT(type) :                 \
     0u)

/** 供应商定义的算法标志。
 *
 * 本标准定义的算法永远不会设置#PSA_ALG_VENDOR_FLAG位。定义其他算法的供应商必须使用带有#PSA_ALG_VENDOR_FLAG位集的编码，并且应尽可能尊重标准编码所使用的按位结构。
 */
#define PSA_ALG_VENDOR_FLAG                     ((psa_algorithm_t)0x80000000)

#define PSA_ALG_CATEGORY_MASK                   ((psa_algorithm_t)0x7f000000)
#define PSA_ALG_CATEGORY_HASH                   ((psa_algorithm_t)0x02000000)
#define PSA_ALG_CATEGORY_MAC                    ((psa_algorithm_t)0x03000000)
#define PSA_ALG_CATEGORY_CIPHER                 ((psa_algorithm_t)0x04000000)
#define PSA_ALG_CATEGORY_AEAD                   ((psa_algorithm_t)0x05000000)
#define PSA_ALG_CATEGORY_SIGN                   ((psa_algorithm_t)0x06000000)
#define PSA_ALG_CATEGORY_ASYMMETRIC_ENCRYPTION  ((psa_algorithm_t)0x07000000)
#define PSA_ALG_CATEGORY_KEY_DERIVATION         ((psa_algorithm_t)0x08000000)
#define PSA_ALG_CATEGORY_KEY_AGREEMENT          ((psa_algorithm_t)0x09000000)

/** 算法是否由供应商定义。
 *
 * 另请参见#PSA_ALG_VENDOR_FLAG。
 */
#define PSA_ALG_IS_VENDOR_DEFINED(alg)                                  \
    (((alg) & PSA_ALG_VENDOR_FLAG) != 0)

/** 指定的算法是否为哈希算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是哈希算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_HASH(alg)                                            \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_HASH)

/** 指定的算法是否为MAC算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是MAC算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_MAC(alg)                                             \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_MAC)

/** 指定的算法是否为对称密码算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是对称密码算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_CIPHER(alg)                                          \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_CIPHER)

/** 指定的算法是否是经验证的关联数据加密（AEAD）算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是AEAD算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_AEAD(alg)                                            \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_AEAD)

/** 指定的算法是否是非对称签名算法，也称为公钥签名算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是非对称签名算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_SIGN(alg)                                            \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_SIGN)

/** 指定的算法是否是非对称加密算法，也称为公钥加密算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是非对称加密算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_ASYMMETRIC_ENCRYPTION(alg)                           \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_ASYMMETRIC_ENCRYPTION)

/** 指定的算法是否为密钥协商算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是密钥协商算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_KEY_AGREEMENT(alg)                                   \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_KEY_AGREEMENT)

/** 指定的算法是否为密钥派生算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是密钥推导算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_KEY_DERIVATION(alg)                                  \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_KEY_DERIVATION)

#define PSA_ALG_HASH_MASK                       ((psa_algorithm_t)0x000000ff)
/** MD2 */
#define PSA_ALG_MD2                             ((psa_algorithm_t)0x02000001)
/** MD4 */
#define PSA_ALG_MD4                             ((psa_algorithm_t)0x02000002)
/** MD5 */
#define PSA_ALG_MD5                             ((psa_algorithm_t)0x02000003)
/** PSA_ALG_RIPEMD160 */
#define PSA_ALG_RIPEMD160                       ((psa_algorithm_t)0x02000004)
/** SHA1 */
#define PSA_ALG_SHA_1                           ((psa_algorithm_t)0x02000005)
/** SHA2-224 */
#define PSA_ALG_SHA_224                         ((psa_algorithm_t)0x02000008)
/** SHA2-256 */
#define PSA_ALG_SHA_256                         ((psa_algorithm_t)0x02000009)
/** SHA2-384 */
#define PSA_ALG_SHA_384                         ((psa_algorithm_t)0x0200000a)
/** SHA2-512 */
#define PSA_ALG_SHA_512                         ((psa_algorithm_t)0x0200000b)
/** SHA2-512/224 */
#define PSA_ALG_SHA_512_224                     ((psa_algorithm_t)0x0200000c)
/** SHA2-512/256 */
#define PSA_ALG_SHA_512_256                     ((psa_algorithm_t)0x0200000d)
/** SHA3-224 */
#define PSA_ALG_SHA3_224                        ((psa_algorithm_t)0x02000010)
/** SHA3-256 */
#define PSA_ALG_SHA3_256                        ((psa_algorithm_t)0x02000011)
/** SHA3-384 */
#define PSA_ALG_SHA3_384                        ((psa_algorithm_t)0x02000012)
/** SHA3-512 */
#define PSA_ALG_SHA3_512                        ((psa_algorithm_t)0x02000013)

/** 在哈希和签名算法策略中，允许任何哈希算法。
 *
 * 该值可用于形成由散列参数化的签名算法的策略的算法使用字段。然后可以使用密钥来使用与任何支持的散列参数化的相同签名算法来执行操作。
 *
 * 也就是说，假设“PSA_xx_SIGNATURE”是以下宏之一：
 * - #PSA_ALG_RSA_PKCS1V15_SIGN, #PSA_ALG_RSA_PSS,
 * -#PSA_ALG_ECDSA、#PSA_lag_determistic_ECDSA。然后，您可以按如下方式创建和使用密钥：
 * -使用#PSA_AG_ANY_HASH设置密钥用法字段，例如：``PSA_Set_key_usage_flags（&attributes，PSA_key_usage_SIGN_HASH）；//或验证psa_set_key_algorithm（&attributes，psa_xx_SIGNATURE（psa_ALG_ANY_HASH））```
 * -导入或生成关键材料。
 * -调用psa_sign_hash（）或psa_verify_hash），传递从“psa_xx_SIGNATURE”构建的算法和特定哈希。每个签名或验证消息的调用可能使用不同的哈希psa_sign_hash（密钥，psa_xx_SIGNATURE（psa_ALG_SHA_256），…）；psa_sign_hash（密钥，psa_xx_SIGNATURE（psa_ALG_SHA_512），…）；psa_sign_hash（密钥，psa_xx_SIGNATURE（psa_ALG_SHA_3_256），…）```
 *
 * 此值不能用于构建通过哈希参数化的其他算法。若要有效使用此宏来构建算法，#PSA_alg_IS_HASH_AND_SIGN（\c alg）为true。
 *
 * 此值不能用于构建执行操作的算法规范。它仅对生成策略有效。
 */
#define PSA_ALG_ANY_HASH                        ((psa_algorithm_t)0x020000ff)

#define PSA_ALG_MAC_SUBCATEGORY_MASK            ((psa_algorithm_t)0x00c00000)
#define PSA_ALG_HMAC_BASE                       ((psa_algorithm_t)0x03800000)
/** 宏来构建HMAC算法。
 *
 * 例如，#PSA_AG_HMAC（#PSA_ALG_SHA_256）是HMAC-SHA-256。
 *
 * \param hash_alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。
 *
 * \return对应的HMAC算法。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_HMAC(hash_alg)                                  \
    (PSA_ALG_HMAC_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))

#define PSA_ALG_HMAC_GET_HASH(hmac_alg)                             \
    (PSA_ALG_CATEGORY_HASH | ((hmac_alg) & PSA_ALG_HASH_MASK))

/** 指定的算法是否为HMAC算法。
 *
 * HMAC是一系列基于哈希函数的MAC算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是HMAC算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_HMAC(alg)                                            \
    (((alg) & (PSA_ALG_CATEGORY_MASK | PSA_ALG_MAC_SUBCATEGORY_MASK)) == \
     PSA_ALG_HMAC_BASE)

/* 在MAC算法的编码中，对应于PSA_ALG_MAC_TRUNCATION_MASK的比特编码MAC被截断的长度。作为一个例外，值0表示未压缩算法，无论其长度如何。长度以6位编码，因此可以达到63；最大的MAC是64字节，因此其对全长的平凡截断被正确编码为0。*/
#define PSA_ALG_MAC_TRUNCATION_MASK             ((psa_algorithm_t)0x003f0000)
#define PSA_MAC_TRUNCATION_OFFSET 16

/** 宏以生成截断的MAC算法。
 *
 * 截短的MAC算法与相应的MAC算法相同，只是截短算法的MAC值仅由未截短算法的第一个MAC值长度字节组成。
 *
 * \注意：此宏可能允许构造无效的算法标识符，原因是指定的长度大于未压缩的MAC，或者因为指定的长度小于实现所允许的长度。
 *
 * \注意，为了策略比较的目的，实现定义了被截断为与未截断算法的MAC相同长度的截断MAC是否被认为与未截断的算法相同。
 *
 * \param mac_alg mac算法标识符（#psa_algorithm_t类型的值，使得#psa_alg_IS_mac（\p alg）为真）。这可以是截断或未截断的MAC算法。\param mac_length截断mac的期望长度（字节）。这最多必须是MAC的完整长度，并且必须至少是指定的最小实现长度。执行规定的最小值不得为零。
 *
 * \return指定长度的对应MAC算法。\如果\p alg不是受支持的MAC算法，或者\p MAC_length对于指定的MAC算法太小或太大，则返回未指定。
 */
#define PSA_ALG_TRUNCATED_MAC(mac_alg, mac_length)                      \
    (((mac_alg) & ~PSA_ALG_MAC_TRUNCATION_MASK) |                       \
     ((mac_length) << PSA_MAC_TRUNCATION_OFFSET & PSA_ALG_MAC_TRUNCATION_MASK))

/** 宏来构建与截断的MAC算法相对应的基本MAC算法。
 *
 * \param mac_alg mac算法标识符（#psa_algorithm_t类型的值，使得#psa_alg_IS_mac（\p alg）为真）。这可以是截断或未截断的MAC算法。
 *
 * \return对应的基本MAC算法。\return如果\p alg不是受支持的MAC算法，则未指定。
 */
#define PSA_ALG_FULL_LENGTH_MAC(mac_alg)        \
    ((mac_alg) & ~PSA_ALG_MAC_TRUNCATION_MASK)

/** MAC算法被截断的长度。
 *
 * \param mac_alg mac算法标识符（#psa_algorithm_t类型的值，使得#psa_alg_IS_mac（\p alg）为真）。
 *
 * \return截断MAC的长度（字节）。\如果\p alg是非截断MAC算法，则返回0。\return如果\p alg不是受支持的MAC算法，则未指定。
 */
#define PSA_MAC_TRUNCATED_LENGTH(mac_alg)                               \
    (((mac_alg) & PSA_ALG_MAC_TRUNCATION_MASK) >> PSA_MAC_TRUNCATION_OFFSET)

#define PSA_ALG_CIPHER_MAC_BASE                 ((psa_algorithm_t)0x03c00000)
/** 分组密码的CBC-MAC构造
 *
 * \警告CBC-MAC在许多情况下是不安全的。建议使用更安全的模式，如#PSA_ALG_MAC。
 */
#define PSA_ALG_CBC_MAC                         ((psa_algorithm_t)0x03c00100)
/**分组密码的CMAC构造*/
#define PSA_ALG_CMAC                            ((psa_algorithm_t)0x03c00200)

/** 指定的算法是否是基于分组密码的MAC算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是基于块密码的MAC算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_BLOCK_CIPHER_MAC(alg)                                \
    (((alg) & (PSA_ALG_CATEGORY_MASK | PSA_ALG_MAC_SUBCATEGORY_MASK)) == \
     PSA_ALG_CIPHER_MAC_BASE)

#define PSA_ALG_CIPHER_STREAM_FLAG              ((psa_algorithm_t)0x00800000)
#define PSA_ALG_CIPHER_FROM_BLOCK_FLAG          ((psa_algorithm_t)0x00400000)

/** 指定的算法是否为流密码。
 *
 * 流密码是一种对称密码，通过对密钥生成的字节流应用逐位异或来加密或解密消息。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是流密码算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符或不是对称密码算法，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_STREAM_CIPHER(alg)            \
    (((alg) & (PSA_ALG_CATEGORY_MASK | PSA_ALG_CIPHER_STREAM_FLAG)) == \
        (PSA_ALG_CATEGORY_CIPHER | PSA_ALG_CIPHER_STREAM_FLAG))

/** 流密码算法的流密码模式。
 *
 * 基础流密码由密钥类型决定。
 * -要使用ChaCha20，请使用密钥类型#PSA_key_type_ChaCha20。
 * -要使用ARC4，请使用密钥类型#PSA_key_type_ARC4。
 */
#define PSA_ALG_STREAM_CIPHER                   ((psa_algorithm_t)0x04800100)

/** CTR流密码模式。
 *
 * CTR是由分组密码构建的流密码。基础分组密码由密钥类型决定。例如，要使用AES-128-CTR，请将此算法与#PSA_key_type_AES类型的密钥以及128位（16字节）的长度一起使用。
 */
#define PSA_ALG_CTR                             ((psa_algorithm_t)0x04c01000)

/** CFB流密码模式。
 *
 * 基础分组密码由密钥类型决定。
 */
#define PSA_ALG_CFB                             ((psa_algorithm_t)0x04c01100)

/** OFB流密码模式。
 *
 * 基础分组密码由密钥类型决定。
 */
#define PSA_ALG_OFB                             ((psa_algorithm_t)0x04c01200)

/** XTS密码模式。
 *
 * XTS是一种由分组密码构建的密码模式。它需要至少一个完整的输入块，但超过这个最小值，输入不需要是整数个块。
 */
#define PSA_ALG_XTS                             ((psa_algorithm_t)0x0440ff00)

/** 分组密码的电子密码簿（ECB）模式，无填充。
 *
 * \警告ECB模式不会保护加密数据的机密性，除非在极窄的情况下。建议应用程序仅在需要构建实施不提供的操作模式时使用ECB。鼓励实施提供应用程序所需的模式，而不是支持直接访问ECB。
 *
 * 基础分组密码由密钥类型决定。
 *
 * 此对称密码模式只能用于长度为所选分组密码的块大小的倍数的消息。
 *
 * ECB模式不接受初始化向量（IV）。对该算法使用多部分密码操作时，不得调用psa_cher_generate.iv（）和psa_cher _set_iv（）。
 */
#define PSA_ALG_ECB_NO_PADDING                  ((psa_algorithm_t)0x04404400)

/** CBC块密码链模式，无填充。
 *
 * 基础分组密码由密钥类型决定。
 *
 * 此对称密码模式只能用于长度为所选分组密码的整数块的消息。
 */
#define PSA_ALG_CBC_NO_PADDING                  ((psa_algorithm_t)0x04404000)

/** 带有PKCS#7填充的CBC块密码链模式。
 *
 * 基础分组密码由密钥类型决定。
 *
 * 这是PKCS#7（RFC 2315）定义的填充方法&sect；10.3.
 */
#define PSA_ALG_CBC_PKCS7                       ((psa_algorithm_t)0x04404100)

#define PSA_ALG_AEAD_FROM_BLOCK_FLAG            ((psa_algorithm_t)0x00400000)

/** 指定的算法是否为分组密码上的AEAD模式。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是基于分组密码的AEAD模式的AEAD算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_AEAD_ON_BLOCK_CIPHER(alg)    \
    (((alg) & (PSA_ALG_CATEGORY_MASK | PSA_ALG_AEAD_FROM_BLOCK_FLAG)) == \
     (PSA_ALG_CATEGORY_AEAD | PSA_ALG_AEAD_FROM_BLOCK_FLAG))

/** CCM认证的加密算法。
 *
 * 基础分组密码由密钥类型决定。
 */
#define PSA_ALG_CCM                             ((psa_algorithm_t)0x05500100)

/** GCM认证的加密算法。
 *
 * 基础分组密码由密钥类型决定。
 */
#define PSA_ALG_GCM                             ((psa_algorithm_t)0x05500200)

/** Chacha20-Poly1305 AEAD算法。
 *
 * RFC 7539中定义了ChaCha20_Poly1305构造。
 *
 * 实现必须支持12字节随机数，可以支持8字节随机数并且应该拒绝其他大小。
 *
 * 实现必须支持16字节标记，并应拒绝其他大小。
 */
#define PSA_ALG_CHACHA20_POLY1305               ((psa_algorithm_t)0x05100500)

/* 在AEAD算法的编码中，对应于PSA_ALG_EAD_TAG_LENGTH_MASK的位编码AEAD标签的长度。默认长度的常量遵循此编码。
 */
#define PSA_ALG_AEAD_TAG_LENGTH_MASK            ((psa_algorithm_t)0x003f0000)
#define PSA_AEAD_TAG_LENGTH_OFFSET 16

/** 宏以构建缩短的AEAD算法。
 *
 * 缩短的AEAD算法类似于相应的AEAD，但具有由更少字节组成的认证标签。根据算法，标签长度可能会影响密文的计算。
 *
 * \param aead_alg aead算法标识符（#psa_algorithm_t类型的值，使得#psa_alg_IS_aead（\p alg）为真）。\param tag_length身份验证标签的期望长度（字节）。
 *
 * \return指定长度的相应AEAD算法。\如果\p alg不是受支持的AEAD算法，或者如果\p tag_length对于指定的AEAD运算法则无效，则返回未指定。
 */
#define PSA_ALG_AEAD_WITH_TAG_LENGTH(aead_alg, tag_length)              \
    (((aead_alg) & ~PSA_ALG_AEAD_TAG_LENGTH_MASK) |                     \
     ((tag_length) << PSA_AEAD_TAG_LENGTH_OFFSET &                      \
      PSA_ALG_AEAD_TAG_LENGTH_MASK))

/** 使用默认标签长度计算相应的AEAD算法。
 *
 * \param aead_alg aead算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_aead（\p alg）为真）。
 *
 * \return具有该算法默认标记长度的相应AEAD算法。
 */
#define PSA_ALG_AEAD_WITH_DEFAULT_TAG_LENGTH(aead_alg)                   \
    (                                                                    \
        PSA_ALG_AEAD_WITH_DEFAULT_TAG_LENGTH_CASE(aead_alg, PSA_ALG_CCM) \
        PSA_ALG_AEAD_WITH_DEFAULT_TAG_LENGTH_CASE(aead_alg, PSA_ALG_GCM) \
        PSA_ALG_AEAD_WITH_DEFAULT_TAG_LENGTH_CASE(aead_alg, PSA_ALG_CHACHA20_POLY1305) \
        0)
#define PSA_ALG_AEAD_WITH_DEFAULT_TAG_LENGTH_CASE(aead_alg, ref)         \
    PSA_ALG_AEAD_WITH_TAG_LENGTH(aead_alg, 0) ==                         \
    PSA_ALG_AEAD_WITH_TAG_LENGTH(ref, 0) ?                               \
    ref :

#define PSA_ALG_RSA_PKCS1V15_SIGN_BASE          ((psa_algorithm_t)0x06000200)
/** 带有哈希的RSA PKCS#1 v1.5签名。
 *
 * 这是RFC 8017（PKCS#1:RSA加密规范）以名称RSASSA-PKCS1-v1_5定义的签名方案。
 *
 * \param hash_alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。当在使用策略中指定算法时，这包括#PSA_ALG_ANY_HASH。
 *
 * \return对应的RSA PKCS#1 v1.5签名算法。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_RSA_PKCS1V15_SIGN(hash_alg)                             \
    (PSA_ALG_RSA_PKCS1V15_SIGN_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
/** 原始PKCS#1 v1.5签名。
 *
 * 该算法的输入是RFC 8017（PKCS#1:RSA加密规范）使用的DigestInfo结构，&sect；9.2步骤3&ndash；6.
 */
#define PSA_ALG_RSA_PKCS1V15_SIGN_RAW PSA_ALG_RSA_PKCS1V15_SIGN_BASE
#define PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg)                               \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_RSA_PKCS1V15_SIGN_BASE)

#define PSA_ALG_RSA_PSS_BASE               ((psa_algorithm_t)0x06000300)
/** 带有哈希的RSA PSS签名。
 *
 * 这是RFC 8017（PKCS#1:RSA加密规范）定义的签名方案，名称为RSASSA-PSS，具有消息生成函数MGF1，盐长度等于哈希长度。指定的哈希算法用于对输入消息进行哈希，创建咸哈希，并用于生成掩码。
 *
 * \param hash_alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。当在使用策略中指定算法时，这包括#PSA_ALG_ANY_HASH。
 *
 * \return对应的RSA PSS签名算法。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_RSA_PSS(hash_alg)                               \
    (PSA_ALG_RSA_PSS_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
#define PSA_ALG_IS_RSA_PSS(alg)                                 \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_RSA_PSS_BASE)

#define PSA_ALG_ECDSA_BASE                      ((psa_algorithm_t)0x06000600)
/** ECDSA签名与哈希。
 *
 * 这是由ANSI X9.62定义的ECDSA签名方案，具有每个消息的随机密码（k）。
 *
 * 将签名表示为字节字符串包括签名值r和s的连接。r和s中的每一个都编码为N个八位字节字符串，其中N是以八位字节为单位的曲线基点的长度。每个值都以大端序表示（最重要的八位位组优先）。
 *
 * \param hash_alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。当在使用策略中指定算法时，这包括#PSA_ALG_ANY_HASH。
 *
 * \return对应的ECDSA签名算法。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_ECDSA(hash_alg)                                 \
    (PSA_ALG_ECDSA_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
/** ECDSA签名，无哈希。
 *
 * 这是与#PSA_AG_ECDSA（）相同的签名方案，但没有指定哈希算法。此算法只能用于签名或验证应该是已计算哈希的字节序列。请注意，根据需要，输入在左侧用零填充或在左侧截断，以适应曲线大小。
 */
#define PSA_ALG_ECDSA_ANY PSA_ALG_ECDSA_BASE
#define PSA_ALG_DETERMINISTIC_ECDSA_BASE        ((psa_algorithm_t)0x06000700)
/** 带有哈希的确定性ECDSA签名。
 *
 * 这是RFC 6979定义的确定性ECDSA签名方案。
 *
 * 签名的表示方式与#PSA_AG_ECDSA（）相同。
 *
 * 注意，当该算法用于验证时，接受使用具有相同私钥的随机化ECDSA（#PSA_ALG_ECDSA（\p hash_ALG））生成的签名。换句话说，#PSA_AG_DETERMINISTIC_CDSA（\p hash_ALG）与#PSA_ALG_CDSA（/p hash_ALG）的区别仅在于签名，而非验证。
 *
 * \param hash_alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。当在使用策略中指定算法时，这包括#PSA_ALG_ANY_HASH。
 *
 * \return对应的确定性ECDSA签名算法。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_DETERMINISTIC_ECDSA(hash_alg)                           \
    (PSA_ALG_DETERMINISTIC_ECDSA_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
#define PSA_ALG_ECDSA_DETERMINISTIC_FLAG        ((psa_algorithm_t)0x00000100)
#define PSA_ALG_IS_ECDSA(alg)                                           \
    (((alg) & ~PSA_ALG_HASH_MASK & ~PSA_ALG_ECDSA_DETERMINISTIC_FLAG) ==  \
     PSA_ALG_ECDSA_BASE)
#define PSA_ALG_ECDSA_IS_DETERMINISTIC(alg)             \
    (((alg) & PSA_ALG_ECDSA_DETERMINISTIC_FLAG) != 0)
#define PSA_ALG_IS_DETERMINISTIC_ECDSA(alg)                             \
    (PSA_ALG_IS_ECDSA(alg) && PSA_ALG_ECDSA_IS_DETERMINISTIC(alg))
#define PSA_ALG_IS_RANDOMIZED_ECDSA(alg)                                \
    (PSA_ALG_IS_ECDSA(alg) && !PSA_ALG_ECDSA_IS_DETERMINISTIC(alg))

/** 指定的算法是否为哈希和符号算法。
 *
 * 哈希和签名算法是由两部分组成的非对称（公钥）签名算法：首先以不依赖于密钥的方式计算哈希，然后根据哈希值和密钥计算签名。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是哈希和符号算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_HASH_AND_SIGN(alg)                                   \
    (PSA_ALG_IS_RSA_PSS(alg) || PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) ||    \
     PSA_ALG_IS_ECDSA(alg))

/** 获取哈希和签名算法使用的哈希。
 *
 * 哈希和签名算法是由两个阶段组成的签名算法：首先是不使用密钥并生成输入消息哈希的哈希阶段，然后是仅使用哈希和密钥而不使用消息本身的签名阶段。
 *
 * \param alg签名算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_SIGN（\p alg）为真）。
 *
 * \return如果\p alg是哈希和符号算法，则返回基础哈希算法。\如果\p alg是不遵循哈希和符号结构的签名算法，则返回0。\return如果\p alg不是签名算法或实现不支持，则未指定。
 */
#define PSA_ALG_SIGN_GET_HASH(alg)                                     \
    (PSA_ALG_IS_HASH_AND_SIGN(alg) ?                                   \
     ((alg) & PSA_ALG_HASH_MASK) == 0 ? /*“原始”算法*/ 0 :        \
     ((alg) & PSA_ALG_HASH_MASK) | PSA_ALG_CATEGORY_HASH :             \
     0)

/** RSA PKCS#1 v1.5加密。
 */
#define PSA_ALG_RSA_PKCS1V15_CRYPT              ((psa_algorithm_t)0x07000200)

#define PSA_ALG_RSA_OAEP_BASE                   ((psa_algorithm_t)0x07000300)
/** RSA OAEP加密。
 *
 * 这是由RFC 8017（PKCS#1:RSA加密规范）以名称RSAES-OAEP定义的加密方案，具有消息生成功能MGF1。
 *
 * \param hash_alg要用于MGF1的哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。
 *
 * \return对应的RSA OAEP加密算法。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_RSA_OAEP(hash_alg)                              \
    (PSA_ALG_RSA_OAEP_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
#define PSA_ALG_IS_RSA_OAEP(alg)                                \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_RSA_OAEP_BASE)
#define PSA_ALG_RSA_OAEP_GET_HASH(alg)                          \
    (PSA_ALG_IS_RSA_OAEP(alg) ?                                 \
     ((alg) & PSA_ALG_HASH_MASK) | PSA_ALG_CATEGORY_HASH :      \
     0)

#define PSA_ALG_HKDF_BASE                       ((psa_algorithm_t)0x08000100)
/** 宏来构建HKDF算法。
 *
 * 例如，“PSA_AG_HKDF（PSA_AG_SHA256）”是使用HMAC-SHA-256的HKDF。
 *
 * 该密钥推导算法使用以下输入：
 * -#PSA_KEY_DERIVATION_INPUT_SALT是“提取”步骤中使用的盐。它是可选的；如果省略，则派生使用空的盐。
 * -#PSA_KEY_DERIVATION_INPUT_SECRET是“提取”步骤中使用的密钥。
 * -#PSA_KEY_DERIVATION_INPUT_INFO是“展开”步骤中使用的信息字符串。必须在#PSA_KEY_DERIVATION_INPUT_SECRET之前传递#PSA_KEY _DERIVATION _INPUT_SALT。在steup之后和开始生成输出之前，您可以随时传递#PSA_KEY_DERIVATION_INPUT_INFO。
 *
 * \param hash_alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。
 *
 * \return对应的HKDF算法。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_HKDF(hash_alg)                                  \
    (PSA_ALG_HKDF_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
/** 指定的算法是否为HKDF算法。
 *
 * HKDF是一系列基于哈希函数和HMAC构造的密钥推导算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果算法是HKDF算法，则返回1，否则返回0。如果\c alg不是受支持的密钥派生算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_HKDF(alg)                            \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_HKDF_BASE)
#define PSA_ALG_HKDF_GET_HASH(hkdf_alg)                         \
    (PSA_ALG_CATEGORY_HASH | ((hkdf_alg) & PSA_ALG_HASH_MASK))

#define PSA_ALG_TLS12_PRF_BASE                  ((psa_algorithm_t)0x08000200)
/** 宏来构建TLS-1.2 PRF算法。
 *
 * TLS 1.2为密钥调度使用自定义伪随机函数（PRF），如RFC 5246第5节所述。它基于HMAC，可以与SHA-256或SHA-384一起使用。
 *
 * 此密钥推导算法使用以下输入，必须按照此处给出的顺序传递：
 * -#PSA_KEY_DERIVATION_INPUT_SEED是种子。
 * -#PSA_KEY_DERIVATION_INPUT_SECRET是密钥。
 * -#PSA_KEY_DERIVATION_INPUT_LABEL是标签。
 *
 * 对于TLS-1.2密钥扩展的应用程序，种子是ServerHello的级联。Random+客户您好。随机，标签为“密钥扩展”。
 *
 * 例如，“PSA_AG_TLS12_PRF（PSA_AG_SHA256）”表示使用HMAC-SHA-256的TLS 1.2 PRF。
 *
 * \param hash_alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。
 *
 * \return对应的TLS-1.2 PRF算法。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_TLS12_PRF(hash_alg)                                  \
    (PSA_ALG_TLS12_PRF_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))

/** 指定的算法是否为TLS-1.2 PRF算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果算法是TLS-1.2 PRF算法，则返回1，否则返回0。如果\c alg不是受支持的密钥派生算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_TLS12_PRF(alg)                                    \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_TLS12_PRF_BASE)
#define PSA_ALG_TLS12_PRF_GET_HASH(hkdf_alg)                         \
    (PSA_ALG_CATEGORY_HASH | ((hkdf_alg) & PSA_ALG_HASH_MASK))

#define PSA_ALG_TLS12_PSK_TO_MS_BASE            ((psa_algorithm_t)0x08000300)
/** 宏来构建TLS-1.2 PSK到MasterSecret算法。
 *
 * 在TLS 1.2中的纯PSK握手中，主密钥通过应用填充（RFC 4279，第2节）和TLS-1.2 PRF（RFC 5246，第5节）从PreSharedKey（PSK）导出。后者基于HMAC，可与SHA-256或SHA-384一起使用。
 *
 * 此密钥推导算法使用以下输入，必须按照此处给出的顺序传递：
 * -#PSA_KEY_DERIVATION_INPUT_SEED是种子。
 * -#PSA_KEY_DERIVATION_INPUT_SECRET是密钥。
 * -#PSA_KEY_DERIVATION_INPUT_LABEL是标签。
 *
 * 对于TLS-1.2的应用程序，种子（转发到TLS-1.2 PRF）是ClientHello的级联。Random+服务器您好。随机，标签为“主秘密”或“扩展主秘密”。
 *
 * 例如，“PSA_AG_TLS12_PSK_TO_MS（PSA_AG_SHA256）”表示使用HMAC-SHA-256的TLS-1.2 PSK到MasterSecret的推导PRF。
 *
 * \param hash_alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p hash_alk）为真）。
 *
 * \向MS算法返回相应的TLS-1.2 PSK。\return如果\p hash_alg不是受支持的哈希算法，则未指定。
 */
#define PSA_ALG_TLS12_PSK_TO_MS(hash_alg)                                  \
    (PSA_ALG_TLS12_PSK_TO_MS_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))

/** 指定的算法是否是TLS-1.2 PSK到MS算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果算法是TLS-1.2 PSK到MS算法，则返回1，否则返回0。如果\c alg不是受支持的密钥派生算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_TLS12_PSK_TO_MS(alg)                                    \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_TLS12_PSK_TO_MS_BASE)
#define PSA_ALG_TLS12_PSK_TO_MS_GET_HASH(hkdf_alg)                         \
    (PSA_ALG_CATEGORY_HASH | ((hkdf_alg) & PSA_ALG_HASH_MASK))

#define PSA_ALG_KEY_DERIVATION_MASK             ((psa_algorithm_t)0xfe00ffff)
#define PSA_ALG_KEY_AGREEMENT_MASK              ((psa_algorithm_t)0xffff0000)

/** 宏来构建一个组合算法，该算法将密钥协议与密钥派生链接起来。
 *
 * \param ka_alg密钥协商算法（\c PSA_AG_XXX值，使得#PSA_AG_IS_key_agreement（\p ka_alk）为真）。\param kdf_alg密钥推导算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_key_derivation（\p kdf.alg）为真）。
 *
 * \return对应的密钥协议和推导算法。\如果\p ka_alg不是受支持的密钥协商算法，或者\p kdf_alg是不受支持的键派生算法，则返回未指定。
 */
#define PSA_ALG_KEY_AGREEMENT(ka_alg, kdf_alg)  \
    ((ka_alg) | (kdf_alg))

#define PSA_ALG_KEY_AGREEMENT_GET_KDF(alg)                              \
    (((alg) & PSA_ALG_KEY_DERIVATION_MASK) | PSA_ALG_CATEGORY_KEY_DERIVATION)

#define PSA_ALG_KEY_AGREEMENT_GET_BASE(alg)                             \
    (((alg) & PSA_ALG_KEY_AGREEMENT_MASK) | PSA_ALG_CATEGORY_KEY_AGREEMENT)

/** 指定的算法是否为原始密钥协商算法。
 *
 * 原始密钥协商算法是不指定密钥派生函数的算法。通常，原始密钥协商算法直接使用\c PSA_AG_xxx宏构建，而非原始密钥协商协议算法则使用#PSA_AG_key_agreement（）构建。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\p alg是原始密钥协商算法，则返回1，否则返回0。如果\p alg不是受支持的算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_RAW_KEY_AGREEMENT(alg)                               \
    (PSA_ALG_IS_KEY_AGREEMENT(alg) &&                                   \
     PSA_ALG_KEY_AGREEMENT_GET_KDF(alg) == PSA_ALG_CATEGORY_KEY_DERIVATION)

#define PSA_ALG_IS_KEY_DERIVATION_OR_AGREEMENT(alg)     \
    ((PSA_ALG_IS_KEY_DERIVATION(alg) || PSA_ALG_IS_KEY_AGREEMENT(alg)))

/** 有限域Diffie-Hellman（DH）密钥协商算法。
 *
 * 密钥协议产生的共享密钥是big endian格式的“g^｛ab｝”。它是“上限（m/8）”字节长，其中“m”是以位为单位的素数“p”的大小。
 */
#define PSA_ALG_FFDH                            ((psa_algorithm_t)0x09010000)

/** 指定的算法是否是有限域Diffie-Hellman算法。
 *
 * 这包括原始有限域Diffie-Hellman算法以及有限域Diffie-Hellman，然后是任何支持密钥推导算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果代数是有限域Diffie-Hellman算法，则返回1，否则返回0。如果alg不是受支持的密钥协议算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_FFDH(alg) \
    (PSA_ALG_KEY_AGREEMENT_GET_BASE(alg) == PSA_ALG_FFDH)

/** 椭圆曲线Diffie-Hellman（ECDH）密钥协商算法。
 *
 * 密钥协商产生的共享秘密是共享秘密点的x坐标。它总是“上限（m/8）”字节长，其中“m”是与曲线相关联的比特大小，即曲线坐标字段顺序的比特大小。当“m”不是8的倍数时，包含共享密钥的最高有效位的字节用零位填充。字节顺序是小端或大端，具体取决于曲线类型。
 *
 * -对于Montgomery曲线（曲线类型为“PSA_ECC_FAMILY_CURVEXXX”），共享的秘密是“d_A Q_B=d_B Q_A”的x坐标，以小端字节顺序排列。Curve448的比特大小是448，Curve25519的比特大小为255。
 * -对于素域上的Weierstrass曲线（曲线类型为“PSA_ECC_FAMILY_SERCPXXX”和“PSA_ACC_FAMILY_BRAINPOOL_PXXX”），共享的秘密是“d_A Q_B=d_B Q_A”的x坐标，以大端字节顺序排列。字段“F_p”的位大小为“m=上限（log_2（p））”。
 * -对于二进制字段上的Weierstrass曲线（曲线类型为“PSA_ECC_FAMILY_SECTXXXX”），共享的秘密是“d_A Q_B=d_B Q_A”的x坐标，以大端字节顺序排列。字段“F_｛2^m｝”的位大小为“m”。
 */
#define PSA_ALG_ECDH                            ((psa_algorithm_t)0x09020000)

/** 指定的算法是否是椭圆曲线Diffie-Hellman算法。
 *
 * 这包括原始椭圆曲线Diffie-Hellman算法以及椭圆曲线Diffie-Hellman以及任何支持密钥推导算法。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果代数是椭圆曲线Diffie-Hellman算法，则返回1，否则返回0。如果alg不是受支持的密钥协议算法标识符，则此宏可能返回0或1。
 */
#define PSA_ALG_IS_ECDH(alg) \
    (PSA_ALG_KEY_AGREEMENT_GET_BASE(alg) == PSA_ALG_ECDH)

/** 指定的算法编码是否为通配符。
 *
 * 通配符值只能用于设置策略中的使用算法字段，而不能用于执行操作。
 *
 * \param alg算法标识符（#psa_algorithm_t类型的值）。
 *
 * \如果\c alg是通配符算法编码，则返回1。\如果\c alg是非通配符算法编码（适用于操作），则返回0。\return如果alg不是受支持的算法标识符，则此宏可以返回0或1。
 */
#define PSA_ALG_IS_WILDCARD(alg)                        \
    (PSA_ALG_IS_HASH_AND_SIGN(alg) ?                    \
     PSA_ALG_SIGN_GET_HASH(alg) == PSA_ALG_ANY_HASH :   \
     (alg) == PSA_ALG_ANY_HASH)

/**@}*/

/** \defgroup key_lifetimes密钥生存期@{
 */

/** 易失性密钥的默认生存期。
 *
 * 易失性密钥只有在其标识符未被销毁时才存在。钥匙材料保证在电源复位时被擦除。
 *
 * 具有此寿命的密钥通常存储在PSA Crypto子系统的RAM区域中。然而，这是一种实现选择。如果实现将关于密钥的数据存储在非易失性存储器中，则在调用应用程序终止时，它必须释放与密钥相关联的所有资源并擦除密钥材料。
 */
#define PSA_KEY_LIFETIME_VOLATILE               ((psa_key_lifetime_t)0x00000000)

/** 持久密钥的默认生存期。
 *
 * 持久密钥保留在存储中，直到它被明确销毁或相应的存储区域被擦除。本规范没有定义任何擦除存储区域的机制，但实施方式可以提供自己的机制（例如，执行工厂重置、准备设备翻新或卸载应用程序）。
 *
 * 此生存期值是调用应用程序的默认存储区域。实现可以提供由其他生命周期值指定的其他存储区域作为特定于实现的扩展。有关详细信息，请参见：：psa_key_lifetime_t。
 */
#define PSA_KEY_LIFETIME_PERSISTENT             ((psa_key_lifetime_t)0x00000001)

/** 易失性密钥的持久性级别。
 *
 * 有关详细信息，请参见：：psa_key_persistence_t。
 */
#define PSA_KEY_PERSISTENCE_VOLATILE            ((psa_key_persistence_t)0x00)

/** 持久密钥的默认持久级别。
 *
 * 有关详细信息，请参见：：psa_key_persistence_t。
 */
#define PSA_KEY_PERSISTENCE_DEFAULT             ((psa_key_persistence_t)0x01)

/** 一种持久性级别，表示密钥从未被销毁。
 *
 * 有关详细信息，请参见：：psa_key_persistence_t。
 */
#define PSA_KEY_PERSISTENCE_READ_ONLY           ((psa_key_persistence_t)0xff)

#define PSA_KEY_LIFETIME_GET_PERSISTENCE(lifetime)      \
    ((psa_key_persistence_t)((lifetime) & 0x000000ff))

#define PSA_KEY_LIFETIME_GET_LOCATION(lifetime)      \
    ((psa_key_location_t)((lifetime) >> 8))

/** 密钥生存期是否指示密钥是易失性的。
 *
 * 当应用程序实例终止时，实现会自动销毁易失性密钥。特别是，易失性密钥在设备电源复位时自动销毁。
 *
 * 不易失的密钥是持久的。持久密钥将被保留，直到应用程序显式销毁它们或发生特定于实现的设备管理事件（例如，工厂重置）。
 *
 * \param lifetime要查询的生存期值（类型为：psa_key_lifetime_t的值）。
 *
 * \如果密钥是易失的，则返回\c 1，否则返回\c 0。
 */
#define PSA_KEY_LIFETIME_IS_VOLATILE(lifetime)  \
    (PSA_KEY_LIFETIME_GET_PERSISTENCE(lifetime) == \
     PSA_KEY_PERSISTENCE_VOLATILE)

/** 从持久性级别和位置构造生命周期。
 *
 * \param persistence持久性级别（类型为：psa_key_persistence_t的值）。\param location位置指示符（类型为：psa_key_location_t的值）。
 *
 * \return构造的生存期值。
 */
#define PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(persistence, location) \
    ((location) << 8 | (persistence))

/** 持久密钥的本地存储区域。
 *
 * 此存储区域适用于所有可以存储持久密钥而无需将存储委派给第三方密码处理器的系统。
 *
 * 有关详细信息，请参阅：：psa_key_location_t。
 */
#define PSA_KEY_LOCATION_LOCAL_STORAGE          ((psa_key_location_t)0x000000)

#define PSA_KEY_LOCATION_VENDOR_FLAG            ((psa_key_location_t)0x800000)

/** 应用程序选择的密钥标识符的最小值。
 */
#define PSA_KEY_ID_USER_MIN                     ((psa_key_id_t)0x00000001)
/** 应用程序选择的密钥标识符的最大值。
 */
#define PSA_KEY_ID_USER_MAX                     ((psa_key_id_t)0x3fffffff)
/** 由实现选择的密钥标识符的最小值。
 */
#define PSA_KEY_ID_VENDOR_MIN                   ((psa_key_id_t)0x40000000)
/** 由实现选择的密钥标识符的最大值。
 */
#define PSA_KEY_ID_VENDOR_MAX                   ((psa_key_id_t)0x7fffffff)


#if !defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)

#define MBEDTLS_SVC_KEY_ID_INIT ( (psa_key_id_t)0 )
#define MBEDTLS_SVC_KEY_ID_GET_KEY_ID( id ) ( id )
#define MBEDTLS_SVC_KEY_ID_GET_OWNER_ID( id ) ( 0 )

/** 用于在运行时初始化密钥标识符的实用程序。
 *
 * \param未使用的未使用参数。\param key_id密钥的标识符。
 */
static inline mbedtls_svc_key_id_t mbedtls_svc_key_id_make(
    unsigned int unused, psa_key_id_t key_id )
{
    (void)unused;

    return( key_id );
}

/** 比较两个密钥标识符。
 *
 * \param id1第一个密钥标识符。\param id2第二个密钥标识符。
 *
 * \如果两个键标识符相等，则返回非零，否则返回零。
 */
static inline int mbedtls_svc_key_id_equal( mbedtls_svc_key_id_t id1,
                                            mbedtls_svc_key_id_t id2 )
{
    return( id1 == id2 );
}

/** 检查密钥标识符是否为空。
 *
 * \param key密钥标识符。
 *
 * \如果密钥标识符为空，则返回非零，否则返回零。
 */
static inline int mbedtls_svc_key_id_is_null( mbedtls_svc_key_id_t key )
{
    return( key == 0 );
}

#else /* MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER */

#define MBEDTLS_SVC_KEY_ID_INIT ( (mbedtls_svc_key_id_t){ 0, 0 } )
#define MBEDTLS_SVC_KEY_ID_GET_KEY_ID( id ) ( ( id ).key_id )
#define MBEDTLS_SVC_KEY_ID_GET_OWNER_ID( id ) ( ( id ).owner )

/** 用于在运行时初始化密钥标识符的实用程序。
 *
 * \param owner_id密钥所有者的标识符。\param key_id密钥的标识符。
 */
static inline mbedtls_svc_key_id_t mbedtls_svc_key_id_make(
    mbedtls_key_owner_id_t owner_id, psa_key_id_t key_id )
{
    return( (mbedtls_svc_key_id_t){ .key_id = key_id,
                                    .owner = owner_id } );
}

/** 比较两个密钥标识符。
 *
 * \param id1第一个密钥标识符。\param id2第二个密钥标识符。
 *
 * \如果两个键标识符相等，则返回非零，否则返回零。
 */
static inline int mbedtls_svc_key_id_equal( mbedtls_svc_key_id_t id1,
                                            mbedtls_svc_key_id_t id2 )
{
    return( ( id1.key_id == id2.key_id ) &&
            mbedtls_key_owner_id_equal( id1.owner, id2.owner ) );
}

/** 检查密钥标识符是否为空。
 *
 * \param key密钥标识符。
 *
 * \如果密钥标识符为空，则返回非零，否则返回零。
 */
static inline int mbedtls_svc_key_id_is_null( mbedtls_svc_key_id_t key )
{
    return( ( key.key_id == 0 ) && ( key.owner == 0 ) );
}

#endif /* !MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER */

/**@}*/

/** \defgroup策略关键策略@{
 */

/** 是否可以导出密钥。
 *
 * 无论此权限标志的值如何，都可以始终导出公钥或密钥对的公共部分。
 *
 * 如果密钥没有导出权限，则实现不允许密钥以明文形式从密码处理器导出，无论是通过psa_export_key（）还是通过专有接口。然而，密钥可以以包装形式导出，即以另一密钥加密的形式导出。
 */
#define PSA_KEY_USAGE_EXPORT                    ((psa_key_usage_t)0x00000001)

/** 是否可以复制密钥。
 *
 * 此标志允许使用psa_copy_key（）复制具有相同策略或更严格策略的密钥。
 *
 * 对于密钥位于强制密钥不可导出的安全元素中的生存期，将密钥复制到安全元素之外还需要使用标志#PSA_key_usage_EXPORT。如果安全元素支持，则只允许使用#PSA_key_USAGE_COPY复制安全元素内的密钥。对于生存期为#PSA_KEY_LIFIME_VOLATILE或#PSA_KEY _LIFIME_PERSISTENT的密钥，使用标志#PSA_EY_usage_COPY足以允许复制。
 */
#define PSA_KEY_USAGE_COPY                      ((psa_key_usage_t)0x00000002)

/** 密钥是否可用于加密消息。
 *
 * 此标志允许密钥用于对称加密操作、AEAD加密和身份验证操作或非对称加密操作（如果密钥类型和策略允许）。
 *
 * 对于密钥对，这涉及公钥。
 */
#define PSA_KEY_USAGE_ENCRYPT                   ((psa_key_usage_t)0x00000100)

/** 密钥是否可用于解密消息。
 *
 * 此标志允许密钥用于对称解密操作、AEAD解密和验证操作或非对称解密操作（如果密钥类型和策略允许）。
 *
 * 对于密钥对，这涉及私钥。
 */
#define PSA_KEY_USAGE_DECRYPT                   ((psa_key_usage_t)0x00000200)

/** 密钥是否可用于签署消息。
 *
 * 如果密钥的类型和策略允许，此标志允许密钥用于MAC计算操作或非对称签名操作。
 *
 * 对于密钥对，这涉及私钥。
 */
#define PSA_KEY_USAGE_SIGN_HASH                 ((psa_key_usage_t)0x00001000)

/** 密钥是否可用于验证消息签名。
 *
 * 此标志允许密钥用于MAC验证操作或非对称签名验证操作（如果密钥类型和策略允许）。
 *
 * 对于密钥对，这涉及公钥。
 */
#define PSA_KEY_USAGE_VERIFY_HASH               ((psa_key_usage_t)0x00002000)

/** 该密钥是否可以用于派生其他密钥。
 */
#define PSA_KEY_USAGE_DERIVE                    ((psa_key_usage_t)0x00004000)

/**@}*/

/** \defgroup派生密钥派生@{
 */

/** 密钥派生的秘密输入。
 *
 * 这应该是#PSA_key_type_DERIVE类型的密钥（传递给PSA_key_derivation_input_key（））或密钥协议产生的共享密钥（通过PSA_kkey_derivaton_key_agreement（）获得）。
 *
 * 秘密也可以是直接输入（传递给key_derivation_input_bytes（））。在这种情况下，派生操作可能不会用于派生密钥：该操作只允许psa_key_derivation_output_bytes（），而不允许psa_key_derivatation_output_key（）。
 */
#define PSA_KEY_DERIVATION_INPUT_SECRET     ((psa_key_derivation_step_t)0x0101)

/** 密钥派生的标签。
 *
 * 这应该是直接输入。它也可以是#PSA_key_type_RAW_DATA类型的密钥。
 */
#define PSA_KEY_DERIVATION_INPUT_LABEL      ((psa_key_derivation_step_t)0x0201)

/** 用于密钥派生的盐。
 *
 * 这应该是直接输入。它也可以是#PSA_key_type_RAW_DATA类型的密钥。
 */
#define PSA_KEY_DERIVATION_INPUT_SALT       ((psa_key_derivation_step_t)0x0202)

/** 用于密钥派生的信息字符串。
 *
 * 这应该是直接输入。它也可以是#PSA_key_type_RAW_DATA类型的密钥。
 */
#define PSA_KEY_DERIVATION_INPUT_INFO       ((psa_key_derivation_step_t)0x0203)

/** 密钥派生的种子。
 *
 * 这应该是直接输入。它也可以是#PSA_key_type_RAW_DATA类型的密钥。
 */
#define PSA_KEY_DERIVATION_INPUT_SEED       ((psa_key_derivation_step_t)0x0204)

/**@}*/

#endif /* PSA_CRYPTO_VALUES_H */

