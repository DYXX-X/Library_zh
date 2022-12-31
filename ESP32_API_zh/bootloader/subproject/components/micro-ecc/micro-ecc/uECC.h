/* 版权所有2014，Kenneth MacKay。根据BSD 2条款许可证进行许可。*/

#ifndef _UECC_H_
#define _UECC_H_

#include <stdint.h>

/* 平台选择选项。如果未定义uECC_PLATFORM，代码将尝试根据编译器宏猜测它。uECC_PLATFORM的可能值定义如下：*/
#define uECC_arch_other 0
#define uECC_x86        1
#define uECC_x86_64     2
#define uECC_arm        3
#define uECC_arm_thumb  4
#define uECC_arm_thumb2 5
#define uECC_arm64      6
#define uECC_avr        7

/* 如果需要，可以根据您的平台定义uECC_WORD_SIZE（1、4或8字节）。如果未明确定义uECC_WORD_SIZE，则将根据您的平台自动设置它。*/

/* 优化水平；以代码大小换取速度。值越大，生成的代码越快，但越大。当前支持的值为0-4；0对于大多数应用程序来说都非常慢。优化级别4目前仅对启用了多条曲线的ARM平台产生影响。*/
#ifndef uECC_OPTIMIZATION_LEVEL
    #define uECC_OPTIMIZATION_LEVEL 2
#endif

/* uECC_SQUARE_FUNC-如果启用（定义为非零），这将导致特定函数用于（标量）平方，而不是通用乘法函数。这可以使事情变得更快，但会增加代码大小。*/
#ifndef uECC_SQUARE_FUNC
    #define uECC_SQUARE_FUNC 0
#endif

/* uECC_VLI_NATIVE_LITLE_ENDIAN-如果启用（定义为非零），则将为传入和传出公共API的所有数组切换为本机小端格式。这包括公钥和私钥、共享密钥、签名和消息散列。使用此开关可以减少uECC使用的调用堆栈内存量，因为需要较少的中间转换。请注意，这只适用于本机小端处理器，它将把传递到公共API的uint8_tarrays作为字数组，因此要求提供的字节数组在不支持未对齐访问的体系结构上进行字对齐。重要提示：使用uECC_VLI_NATIVE_LITLE_ENDIAN=1生成的密钥和签名与使用uECC_VLI_NATIVA_LITLE_ENDIAN=0生成的密钥与签名不兼容；各方必须使用相同的结尾。*/
#ifndef uECC_VLI_NATIVE_LITTLE_ENDIAN
    #define uECC_VLI_NATIVE_LITTLE_ENDIAN 0
#endif

/* 曲线支撑选择。设置为0以删除该曲线。*/
#ifndef uECC_SUPPORTS_secp160r1
    #define uECC_SUPPORTS_secp160r1 1
#endif
#ifndef uECC_SUPPORTS_secp192r1
    #define uECC_SUPPORTS_secp192r1 1
#endif
#ifndef uECC_SUPPORTS_secp224r1
    #define uECC_SUPPORTS_secp224r1 1
#endif
#ifndef uECC_SUPPORTS_secp256r1
    #define uECC_SUPPORTS_secp256r1 1
#endif
#ifndef uECC_SUPPORTS_secp256k1
    #define uECC_SUPPORTS_secp256k1 1
#endif

/* 指定是否支持压缩点格式。设置为0可禁用点压缩/解压缩功能。*/
#ifndef uECC_SUPPORT_COMPRESSED_POINT
    #define uECC_SUPPORT_COMPRESSED_POINT 1
#endif

struct uECC_Curve_t;
typedef const struct uECC_Curve_t * uECC_Curve;

#ifdef __cplusplus
extern "C"
{
#endif

#if uECC_SUPPORTS_secp160r1
uECC_Curve uECC_secp160r1(void);
#endif
#if uECC_SUPPORTS_secp192r1
uECC_Curve uECC_secp192r1(void);
#endif
#if uECC_SUPPORTS_secp224r1
uECC_Curve uECC_secp224r1(void);
#endif
#if uECC_SUPPORTS_secp256r1
uECC_Curve uECC_secp256r1(void);
#endif
#if uECC_SUPPORTS_secp256k1
uECC_Curve uECC_secp256k1(void);
#endif

/* uECC_RNG_Function type RNG函数应将“size”随机字节填充到“dest”中。如果“测试”中填充了随机数据，则应返回1；如果无法生成随机数据，应返回0。填写的值应该是真正随机的，或者来自加密安全的PRNG。

在调用uECC_make_key（）或uECC_sign（）之前，必须设置（使用uECC_set_RNG（））功能正常的RNG函数。

设置正确运行的RNG函数可以提高uECC_shared_secret（）和uECC_sign_determistic（）对侧信道攻击的抵抗力。

在为Windows、Linux或OS X构建时，默认情况下会设置正确的RNG函数。如果您在另一个支持/dev/random或/dev/urandom的POSIX兼容系统上构建，则可以定义uECC_POSIX以使用预定义的RNG。对于嵌入式平台，没有预定义的NG功能；你必须提供你自己的。
*/
typedef int (*uECC_RNG_Function)(uint8_t *dest, unsigned size);

/* uECC_set_rng（）函数。设置将用于生成随机字节的函数。如果生成了随机数据，RNG函数应返回1，如果无法生成随机数据，则返回0。

在没有预定义RNG函数的平台（如嵌入式平台）上，必须在使用uECC_make_key（）或uECC_sign（）之前调用此函数。

输入：rng_function-将用于生成随机字节的函数。
*/
void uECC_set_rng(uECC_RNG_Function rng_function);

/* uECC_get_rng（）函数。

返回将用于生成随机字节的函数。
*/
uECC_RNG_Function uECC_get_rng(void);

/* uECC_curve_private_key_size（）函数。

返回曲线的私钥大小（以字节为单位）。
*/
int uECC_curve_private_key_size(uECC_Curve curve);

/* uECC_curve_public_key_size（）函数。

返回曲线的公钥大小（以字节为单位）。
*/
int uECC_curve_public_key_size(uECC_Curve curve);

/* uECC_make_key（）函数。创建公钥/私钥对。

输出：public_key-将用公钥填充。长度必须至少为曲线大小（字节）的2倍。例如，如果曲线是secp256r1，则public_key的长度必须为64字节。private_key-将用私钥填充。必须与曲线顺序一样长；这通常与曲线大小相同，但secp160r1除外。例如，如果曲线为secp256r1，private_key必须为32字节长。

                  对于secp160r1，private_key的长度必须为21字节！请注意，第一个字节几乎总是0（大约有1/2^80的概率为非零）。

如果成功生成密钥对，则返回1；如果发生错误，则返回0。
*/
int uECC_make_key(uint8_t *public_key, uint8_t *private_key, uECC_Curve curve);

/* uECC_shared_secret（）函数。根据您的密钥和其他人的公钥计算共享密钥。注意：建议在将uECC_shared_secret（）的结果用于对称加密或HMAC之前对其进行哈希。

输入：public_key-远程方的公钥。private_key-您的私钥。

输出：secret-将用共享的secret值填充。必须与曲线大小相同；例如，如果曲线是secp256r1，则secret必须为32字节长。

如果成功生成共享密钥，则返回1；如果发生错误，则返回0。
*/
int uECC_shared_secret(const uint8_t *public_key,
                       const uint8_t *private_key,
                       uint8_t *secret,
                       uECC_Curve curve);

#if uECC_SUPPORT_COMPRESSED_POINT
/* uECC_compress（）函数。压缩公钥。

输入：public_key-要压缩的公钥。

输出：压缩-将用压缩的公钥填充。长度必须至少为（曲线大小+1）字节；例如，如果曲线是secp256r1，则压缩长度必须为33字节。
*/
void uECC_compress(const uint8_t *public_key, uint8_t *compressed, uECC_Curve curve);

/* uECC_decompress（）函数。解压缩压缩的公钥。

输入：压缩-压缩的公钥。

输出：public_key-将用解压缩的公钥填充。
*/
void uECC_decompress(const uint8_t *compressed, uint8_t *public_key, uECC_Curve curve);
#endif /* uECC_SUPPORT_COMPRESSED_点*/

/* uECC_valid_public_key（）函数。检查公钥是否有效。

请注意，在使用任何其他uECC函数之前，不需要检查有效的公钥。但是，您可能希望避免花费CPU时间计算共享密钥或使用无效公钥验证签名。

输入：public_key-要检查的公钥。

如果公钥有效，则返回1；如果公钥无效，则返回0。
*/
int uECC_valid_public_key(const uint8_t *public_key, uECC_Curve curve);

/* uECC_compute_public_key（）函数。计算私钥的对应公钥。

输入：private_key-要为其计算公钥的私钥

输出：public_key-将用相应的公钥填充

如果密钥计算成功，则返回1；如果发生错误，则返回0。
*/
int uECC_compute_public_key(const uint8_t *private_key, uint8_t *public_key, uECC_Curve curve);

/* uECC_sign（）函数。为给定哈希值生成ECDSA签名。

用法：计算要签名的数据的哈希（建议使用SHA-2），并将其与私钥一起传递给该函数。

输入：private_key-您的私钥。message_hash-要签名的消息的哈希值。hash_size-消息_hash的大小（以字节为单位）。

输出：签名-将用签名值填充。曲线长度必须至少为2个。例如，如果曲线为secp256r1，则签名长度必须为64字节。

如果签名生成成功，则返回1；如果发生错误，则返回0。
*/
int uECC_sign(const uint8_t *private_key,
              const uint8_t *message_hash,
              unsigned hash_size,
              uint8_t *signature,
              uECC_Curve curve);

/* uECC_HashContext结构。这用于将任意哈希函数传递给uECC_sign_deterministic（）。该结构将用于多个哈希计算；每次计算新的哈希时，都会调用inithash（），然后调用一个或多个toupdatehash（（），最后调用finishash（）生成生成的哈希。

目的是创建一个包含uECC_HashContext的结构，后跟任何哈希特定数据。例如：

typedef结构SHA256_HashContext｛uECC_HashContext uECC；SHA256_CTX CTX；｝SHA256_HashContext；

void init_SHA256(uECC_HashContext *base) ｛SHA256_HashContext context=（SHA256_HashContext）base；SHA256_Init（&context->ctx）；｝

void update_SHA256(uECC_HashContext *base, const uint8_t message，unsigned message_size）｛SHA256_HashContext context=（SHA256_HashContext）base；SHA256_Update（&context->ctx，message，message_size；｝

void finish_SHA256(uECC_HashContext *base, uint8_t*hash_result）｛SHA256_HashContext context=（SHA256_HashContext）base；SHA256_Final（hash_resull，&context->ctx）；｝

…签名时…｛uint8_t tmp[32+32+64]；SHA256_HashContext ctx=｛｛&init_SHA256，&update_SHA256、&finish_SHA256；64，32，tmp｝｝；uECC_sign_determinic（密钥、消息哈希、&ctx.uECC、签名）；}
*/
typedef struct uECC_HashContext {
    void (*init_hash)(const struct uECC_HashContext *context);
    void (*update_hash)(const struct uECC_HashContext *context,
                        const uint8_t *message,
                        unsigned message_size);
    void (*finish_hash)(const struct uECC_HashContext *context, uint8_t *hash_result);
    unsigned block_size; /* 哈希函数块大小（字节），例如SHA-256的64。*/
    unsigned result_size; /* 哈希函数结果大小（字节），例如SHA-256的32。*/
    uint8_t *tmp; /* 必须指向至少（2*result_size+block_size）字节的缓冲区。*/
} uECC_HashContext;

/* uECC_sign_determistic（）函数。使用确定性算法为给定哈希值生成ECDSA签名（参见RFC 6979）。在调用此函数之前，无需使用uECC_set_RNG（）设置RNG；然而，如果定义了RNG，它将提高对侧信道攻击的抵抗力。

用法：计算要签名的数据的哈希（建议使用SHA-2），并将其与私钥和哈希上下文一起传递给该函数。注意，message_hash不需要使用hash_context使用的相同哈希函数来计算。

输入：private_key-您的私钥。message_hash-要签名的消息的哈希值。hash_size-消息_hash的大小（以字节为单位）。hash_context-要使用的哈希上下文。

输出：签名-将用签名值填充。

如果签名生成成功，则返回1；如果发生错误，则返回0。
*/
int uECC_sign_deterministic(const uint8_t *private_key,
                            const uint8_t *message_hash,
                            unsigned hash_size,
                            const uECC_HashContext *hash_context,
                            uint8_t *signature,
                            uECC_Curve curve);

/* uECC_verify（）函数。验证ECDSA签名。

用法：使用与签名者相同的哈希值计算签名数据的哈希值，并将其与签名者的公钥和签名值（r和s）一起传递给此函数。

输入：public_key-签名者的公钥。message_hash-签名数据的哈希。hash_size-message_hash的大小（以字节为单位）。signature—签名值。

如果签名有效，则返回1；如果签名无效，则返回0。
*/
int uECC_verify(const uint8_t *public_key,
                const uint8_t *message_hash,
                unsigned hash_size,
                const uint8_t *signature,
                uECC_Curve curve);

#ifdef __cplusplus
} /* 外部“C”结尾*/
#endif

#endif /* _UECC_H_ */

