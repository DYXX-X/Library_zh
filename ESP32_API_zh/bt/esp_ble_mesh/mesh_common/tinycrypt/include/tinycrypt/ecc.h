/* ecc公司。h-TinyCrypt接口到通用ECC功能*/

/* 版权所有（c）2014，Kenneth MacKay保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * *源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * *二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  英特尔公司版权所有（C）2017，保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 *    -源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 *    -二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 *    -未经事先书面许可，不得使用“英特尔公司”的名称或其贡献者的名称来支持或推广源自此软件的产品。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief --通用ECC功能的接口。
 *
 *  概述：该软件是椭圆曲线密码术所需的常见功能的实现。该实施使用NIST p-256曲线。
 *
 *  安全性：NIST p-256曲线提供了大约128位的安全性。
 *
 */

#ifndef __BLE_MESH_TC_UECC_H__
#define __BLE_MESH_TC_UECC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 字大小（4字节，考虑32位架构）*/
#define uECC_WORD_SIZE 4

/* 设置prng的最大调用数：*/
#ifndef uECC_RNG_MAX_TRIES
#define uECC_RNG_MAX_TRIES 64
#endif

/* 定义数据类型以存储字和位计数：*/
typedef int8_t wordcount_t;
typedef int16_t bitcount_t;
/* 定义比较结果的数据类型：*/
typedef int8_t cmpresult_t;
/* 定义数据类型以存储32位字中的ECC坐标/点：*/
typedef unsigned int uECC_word_t;
/* 定义数据类型以存储64位字中的ECC坐标/点：*/
typedef uint64_t uECC_dword_t;

/* 定义用于ecc计算的掩码：*/
#define HIGH_BIT_SET 0x80000000
#define uECC_WORD_BITS 32
#define uECC_WORD_BITS_SHIFT 5
#define uECC_WORD_BITS_MASK 0x01F

/* 表示曲线p-256的元素的32位字数：*/
#define NUM_ECC_WORDS 8
/* 表示曲线p-256元素的字节数：*/
#define NUM_ECC_BYTES (uECC_WORD_SIZE*NUM_ECC_WORDS)

/* 表示椭圆曲线的结构（例如p256）：*/
struct uECC_Curve_t;
typedef const struct uECC_Curve_t *uECC_Curve;
struct uECC_Curve_t {
    wordcount_t num_words;
    wordcount_t num_bytes;
    bitcount_t num_n_bits;
    uECC_word_t p[NUM_ECC_WORDS];
    uECC_word_t n[NUM_ECC_WORDS];
    uECC_word_t G[NUM_ECC_WORDS * 2];
    uECC_word_t b[NUM_ECC_WORDS];
    void (*double_jacobian)(uECC_word_t *X1, uECC_word_t *Y1, uECC_word_t *Z1,
                            uECC_Curve curve);
    void (*x_side)(uECC_word_t *result, const uECC_word_t *x, uECC_Curve curve);
    void (*mmod_fast)(uECC_word_t *result, uECC_word_t *product);
};

/*
 * @brief 计算点离子jacobian坐标的加倍。
 * @param X1 IN/OUT--x坐标
 * @param Y1 IN/OUT--y坐标
 * @param Z1 IN/OUT--z坐标
 * @param curve IN——椭圆曲线
 */
void double_jacobian_default(uECC_word_t *X1, uECC_word_t *Y1,
                             uECC_word_t *Z1, uECC_Curve curve);

/*
 * @brief 计算x^3+ax+b。结果不能与x重叠。
 * @param result 输出--x^3+ax+b
 * @param x IN——x的值
 * @param curve IN——椭圆曲线
 */
void x_side_default(uECC_word_t *result, const uECC_word_t *x,
                    uECC_Curve curve);

/*
 * @brief 计算结果=来自的产品%curve_phttp://www.nsa.gov/ia/_files/nist-routines.pdf
 * @param result OUT——产品%曲线_ p
 * @param product IN——mod curve_p要减小的值
 */
void vli_mmod_fast_secp256r1(unsigned int *result, unsigned int *product);

/* 字节到单词排序：*/
#define BYTES_TO_WORDS_8(a, b, c, d, e, f, g, h) 0x##d##c##b##a, 0x##h##g##f##e
#define BYTES_TO_WORDS_4(a, b, c, d) 0x##d##c##b##a
#define BITS_TO_WORDS(num_bits) \
    ((num_bits + ((uECC_WORD_SIZE * 8) - 1)) / (uECC_WORD_SIZE * 8))
#define BITS_TO_BYTES(num_bits) ((num_bits + 7) / 8)

/* NIST p-256曲线的定义：*/
static const struct uECC_Curve_t curve_secp256r1 = {
    NUM_ECC_WORDS,
    NUM_ECC_BYTES,
    256, /* 数字_位*/ {
        BYTES_TO_WORDS_8(FF, FF, FF, FF, FF, FF, FF, FF),
        BYTES_TO_WORDS_8(FF, FF, FF, FF, 00, 00, 00, 00),
        BYTES_TO_WORDS_8(00, 00, 00, 00, 00, 00, 00, 00),
        BYTES_TO_WORDS_8(01, 00, 00, 00, FF, FF, FF, FF)
    }, {
        BYTES_TO_WORDS_8(51, 25, 63, FC, C2, CA, B9, F3),
        BYTES_TO_WORDS_8(84, 9E, 17, A7, AD, FA, E6, BC),
        BYTES_TO_WORDS_8(FF, FF, FF, FF, FF, FF, FF, FF),
        BYTES_TO_WORDS_8(00, 00, 00, 00, FF, FF, FF, FF)
    }, {
        BYTES_TO_WORDS_8(96, C2, 98, D8, 45, 39, A1, F4),
        BYTES_TO_WORDS_8(A0, 33, EB, 2D, 81, 7D, 03, 77),
        BYTES_TO_WORDS_8(F2, 40, A4, 63, E5, E6, BC, F8),
        BYTES_TO_WORDS_8(47, 42, 2C, E1, F2, D1, 17, 6B),

        BYTES_TO_WORDS_8(F5, 51, BF, 37, 68, 40, B6, CB),
        BYTES_TO_WORDS_8(CE, 5E, 31, 6B, 57, 33, CE, 2B),
        BYTES_TO_WORDS_8(16, 9E, 0F, 7C, 4A, EB, E7, 8E),
        BYTES_TO_WORDS_8(9B, 7F, 1A, FE, E2, 42, E3, 4F)
    }, {
        BYTES_TO_WORDS_8(4B, 60, D2, 27, 3E, 3C, CE, 3B),
        BYTES_TO_WORDS_8(F6, B0, 53, CC, B0, 06, 1D, 65),
        BYTES_TO_WORDS_8(BC, 86, 98, 76, 55, BD, EB, B3),
        BYTES_TO_WORDS_8(E7, 93, 3A, AA, D8, 35, C6, 5A)
    },
    &double_jacobian_default,
    &x_side_default,
    &vli_mmod_fast_secp256r1
};

uECC_Curve uECC_secp256r1(void);

/*
 * @brief 生成范围0<random<top的随机整数。随机和顶部都有num_word单词。
 * @param random OUT—0<随机<顶部范围内的随机整数
 * @param top IN——上限
 * @param num_words IN——字数
 * @return 0<随机<顶部范围内的随机整数
 */
int uECC_generate_random_int(uECC_word_t *random, const uECC_word_t *top,
                             wordcount_t num_words);


/* uECC_RNG_Function type RNG函数应将“size”随机字节填充到“dest”中。如果“dest”中填充了随机数据，则应返回1；如果无法生成随机数据，应返回0。填写的值应该是真正随机的，或者来自加密安全的PRNG。
 *
 * 在调用uECC_make_key（）或uECC_sign（）之前，必须设置（使用uECC_set_RNG（））功能正常的RNG函数。
 *
 * 设置正确运行的RNG函数可以提高uECC_shared_secret（）对侧信道攻击的抵抗力。
 *
 * 默认设置正确的RNG功能。如果您正在构建另一个支持/dev/random或/dev/urandom的符合POSIX的系统，则可以定义uECC_POSIX以使用预定义的RNG。
 */
typedef int(*uECC_RNG_Function)(uint8_t *dest, unsigned int size);

/*
 * @brief 设置将用于生成随机字节的函数。如果生成了随机数据，RNG函数应返回1，如果无法生成随机数据，则返回0。
 *
 * @note 在没有预定义RNG函数的平台上，必须在使用uECC_make_key（）或uECC_sign（）之前调用此函数。
 *
 * @param rng_function IN—将用于生成随机字节的函数
 */
void uECC_set_rng(uECC_RNG_Function rng_function);

/*
 * @brief 提供当前uECC_RNG_Function。
 * @return 返回将用于生成随机字节的函数。
 */
uECC_RNG_Function uECC_get_rng(void);

/*
 * @brief 以字节为单位计算曲线的私钥大小。
 * @param curve IN——椭圆曲线
 * @return 曲线的私钥大小（字节）。
 */
int uECC_curve_private_key_size(uECC_Curve curve);

/*
 * @brief 以字节为单位计算曲线的公钥大小。
 * @param curve IN——椭圆曲线
 * @return 曲线的公钥大小（字节）。
 */
int uECC_curve_public_key_size(uECC_Curve curve);

/*
 * @brief 计算私钥的对应公钥。
 * @param private_key IN—要为其计算公钥的私钥
 * @param public_key OUT——将用相应的公钥填充
 * @param curve
 * @return 如果密钥计算成功，则返回1；如果发生错误，则返回0。
 */
int uECC_compute_public_key(const uint8_t *private_key,
                            uint8_t *public_key, uECC_Curve curve);

/*
 * @brief 计算公钥。
 * @return 对应的公钥。
 * @param result OUT--公钥
 * @param private_key IN--私钥
 * @param curve IN——椭圆曲线
 */
uECC_word_t EccPoint_compute_public_key(uECC_word_t *result,
                                        uECC_word_t *private_key, uECC_Curve curve);

/*
 * @brief 正则化私钥的位数，以便攻击者无法使用侧信道攻击来了解前导零的数量。
 * @return 正则化k
 * @param k IN--私钥
 * @param k0 IN/OUT—正则化k
 * @param k1 IN/OUT—正则化k
 * @param curve IN——椭圆曲线
 */
uECC_word_t regularize_k(const uECC_word_t *const k, uECC_word_t *k0,
                         uECC_word_t *k1, uECC_Curve curve);

/*
 * @brief 使用带有co-Z坐标的蒙哥马利阶梯的点乘法算法。看见http://eprint.iacr.org/2011/338.pdf.
 * @note 结果可能重叠点。
 * @param result OUT—返回标量*点
 * @param point IN——椭圆曲线点
 * @param scalar IN—标量
 * @param initial_Z IN——z的初始值
 * @param num_bits IN—标量中的位数
 * @param curve IN——椭圆曲线
 */
void EccPoint_mult(uECC_word_t *result, const uECC_word_t *point,
                   const uECC_word_t *scalar, const uECC_word_t *initial_Z,
                   bitcount_t num_bits, uECC_Curve curve);

/*
 * @brief 恒定时间比较到零-比较长整数的安全方法
 * @param vli IN—非常长的整数
 * @param num_words IN——vli中的单词数
 * @return 如果vli==0，则为1，否则为0。
 */
uECC_word_t uECC_vli_isZero(const uECC_word_t *vli, wordcount_t num_words);

/*
 * @brief 检查“点”是否为无穷远处的点
 * @param point IN——椭圆曲线点
 * @param curve IN——椭圆曲线
 * @return 如果“点”是无穷远处的点，则为0。
 */
uECC_word_t EccPoint_isZero(const uECC_word_t *point, uECC_Curve curve);

/*
 * @brief 在恒定时间内计算左-右的符号。
 * @param left IN—要比较的左项
 * @param right IN——要比较的右项
 * @param num_words IN——字数
 * @return 左右标志
 */
cmpresult_t uECC_vli_cmp(const uECC_word_t *left, const uECC_word_t *right,
                         wordcount_t num_words);

/*
 * @brief 计算左-右符号，而不是在恒定时间内。
 * @note 如果输入是机密的一部分，则不应使用
 * @param left IN—要比较的左项
 * @param right IN——要比较的右项
 * @param num_words IN——字数
 * @return 左右标志
 */
cmpresult_t uECC_vli_cmp_unsafe(const uECC_word_t *left, const uECC_word_t *right,
                                wordcount_t num_words);

/*
 * @brief 计算结果=（左-右）%mod。
 * @note 假设（左<模）和（右<模），结果不与模重叠。
 * @param result OUT--（左-右）%mod
 * @param left IN——模减法中的左右项
 * @param right IN——模减法中的右项
 * @param mod IN--模
 * @param num_words IN——字数
 */
void uECC_vli_modSub(uECC_word_t *result, const uECC_word_t *left,
                     const uECC_word_t *right, const uECC_word_t *mod,
                     wordcount_t num_words);

/*
 * @brief 计算P'=（x1'，y1'，Z3），P+Q=（x3，y3，Z3，或P=>P'，Q=>P+Q
 * @note 假设输入P=（x1，y1，Z），Q=（x2，y2，Z
 * @param X1 IN——P的x坐标
 * @param Y1 IN——P的y坐标
 * @param X2 IN——Q的x坐标
 * @param Y2 IN——Q的y坐标
 * @param curve IN——椭圆曲线
 */
void XYcZ_add(uECC_word_t *X1, uECC_word_t *Y1, uECC_word_t *X2,
              uECC_word_t *Y2, uECC_Curve curve);

/*
 * @brief 计算（x1*z^2，y1*z^3）
 * @param X1 IN——上一个x1坐标
 * @param Y1 IN——上一个y1坐标
 * @param Z IN--z值
 * @param curve IN——椭圆曲线
 */
void apply_z(uECC_word_t *X1, uECC_word_t *Y1, const uECC_word_t *const Z,
             uECC_Curve curve);

/*
 * @brief 检查是否设置了位。
 * @return 如果设置了vli的位“bit”，则返回非零。
 * @warning 假设“bit”中提供的值在字数组“vli”的边界内。
 * @note 对于由4个uECC_word_t元素组成的vli，假设vli的位排序布局为：{31，30，…，0}，{63，62，…，32}，{95，94，…，64}，{127，126，…，96}。
 */
uECC_word_t uECC_vli_testBit(const uECC_word_t *vli, bitcount_t bit);

/*
 * @brief 计算结果=产品%mod，其中产品长度为2N个单词。
 * @param result OUT--产品%mod
 * @param mod IN——模块
 * @param num_words IN——字数
 * @warning 当前仅设计用于curve_p或curve_n。
 */
void uECC_vli_mmod(uECC_word_t *result, uECC_word_t *product,
                   const uECC_word_t *mod, wordcount_t num_words);

/*
 * @brief 计算模块化产品（使用曲线->mmod_fast）
 * @param result OUT--（左*右）mod%curve_p
 * @param left IN——产品中的左项
 * @param right IN——产品中的正确术语
 * @param curve IN——椭圆曲线
 */
void uECC_vli_modMult_fast(uECC_word_t *result, const uECC_word_t *left,
                           const uECC_word_t *right, uECC_Curve curve);

/*
 * @brief 计算结果=左-右。
 * @note 可以就地修改。
 * @param result OUT--左-右
 * @param left IN—减法中的左项
 * @param right IN——减法中的右项
 * @param num_words IN——字数
 * @return 借
 */
uECC_word_t uECC_vli_sub(uECC_word_t *result, const uECC_word_t *left,
                         const uECC_word_t *right, wordcount_t num_words);

/*
 * @brief 恒定时间比较功能（比较长整数的安全方法）
 * @param left IN—比较中的左项
 * @param right IN——比较中的右项
 * @param num_words IN——字数
 * @return 如果左==右，则返回0，否则返回1。
 */
uECC_word_t uECC_vli_equal(const uECC_word_t *left, const uECC_word_t *right,
                           wordcount_t num_words);

/*
 * @brief 计算（左*右）%mod
 * @param result OUT--（左*右）%mod
 * @param left IN——产品中的左项
 * @param right IN——产品中的正确术语
 * @param mod IN--模
 * @param num_words IN——字数
 */
void uECC_vli_modMult(uECC_word_t *result, const uECC_word_t *left,
                      const uECC_word_t *right, const uECC_word_t *mod,
                      wordcount_t num_words);

/*
 * @brief 计算（1/输入）%mod
 * @note 所有VLI大小相同。
 * @note 参见“欧几里德的GCD到蒙哥马利的大除法乘法”
 * @param result OUT--（1/输入）%mod
 * @param input IN——模块化反转值
 * @param mod IN--模
 * @param num_words --字数
 */
void uECC_vli_modInv(uECC_word_t *result, const uECC_word_t *input,
                     const uECC_word_t *mod, wordcount_t num_words);

/*
 * @brief 设置dest=src。
 * @param dest OUT—目标缓冲区
 * @param src IN——原始缓冲区
 * @param num_words IN——字数
 */
void uECC_vli_set(uECC_word_t *dest, const uECC_word_t *src,
                  wordcount_t num_words);

/*
 * @brief 计算（左+右）%mod。
 * @note 假设（左<模）和右<模），结果不与模重叠。
 * @param result OUT--（左+右）%模。
 * @param left IN——加上左项
 * @param right IN——加上右项
 * @param mod IN--模
 * @param num_words IN——字数
 */
void uECC_vli_modAdd(uECC_word_t *result,  const uECC_word_t *left,
                     const uECC_word_t *right, const uECC_word_t *mod,
                     wordcount_t num_words);

/*
 * @brief 统计表示vli所需的位数。
 * @param vli IN—非常长的整数
 * @param max_words IN——字数
 * @return 给定vli中的位数
 */
bitcount_t uECC_vli_numBits(const uECC_word_t *vli,
                            const wordcount_t max_words);

/*
 * @brief 擦除（设置为0）vli
 * @param vli IN—非常长的整数
 * @param num_words IN——字数
 */
void uECC_vli_clear(uECC_word_t *vli, wordcount_t num_words);

/*
 * @brief 检查它是否是曲线中的有效点
 * @param point IN——待检查点
 * @param curve IN——椭圆曲线
 * @return 如果点有效，则为0
 * @exception 如果是无穷远处的点，则返回-1
 * @exception 如果x或y小于p，则返回-2，
 * @exception 如果y^2！=，则返回-3x ^3+ax+b。
 */
int uECC_valid_point(const uECC_word_t *point, uECC_Curve curve);

/*
 * @brief 检查公钥是否有效。
 * @param public_key IN——要检查的公钥。
 * @return 如果公钥有效，则返回0
 * @exception 如果是无穷远处的点，则返回-1
 * @exception 如果x或y小于p，则返回-2，
 * @exception 如果y^2！=，则返回-3x ^3+ax+b。
 * @exception 如果公钥是组生成器，则返回-4。
 *
 * @note 请注意，在使用任何其他uECC函数之前，不需要检查有效的公钥。但是，您可能希望避免花费CPU时间计算共享密钥或使用无效公钥验证签名。
 */
int uECC_valid_public_key(const uint8_t *public_key, uECC_Curve curve);

/*
 * @brief 将uECC本机格式的整数转换为大端字节。
 * @param bytes OUT—字节表示
 * @param num_bytes IN—字节数
 * @param native IN—uECC本机表示
 */
void uECC_vli_nativeToBytes(uint8_t *bytes, int num_bytes,
                            const unsigned int *native);

/*
 * @brief 将大端字节转换为uECC本机格式的整数。
 * @param native OUT—uECC本机表示
 * @param bytes IN—字节表示
 * @param num_bytes IN—字节数
 */
void uECC_vli_bytesToNative(unsigned int *native, const uint8_t *bytes,
                            int num_bytes);

#ifdef __cplusplus
}
#endif

#endif /* __BLE_MESH_TC_UECC_H__ */

