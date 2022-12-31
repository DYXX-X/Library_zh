/* 版权所有2015，Kenneth MacKay。根据BSD 2条款许可证进行许可。*/

#ifndef _UECC_VLI_H_
#define _UECC_VLI_H_

#include "uECC.h"
#include "types.h"

/* 用于原始大整数操作的函数。这些仅在uECC时可用。c是用定义为1的uECC_ENABLE_VLI_API编译的。*/
#ifndef uECC_ENABLE_VLI_API
    #define uECC_ENABLE_VLI_API 0
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#if uECC_ENABLE_VLI_API

void uECC_vli_clear(uECC_word_t *vli, wordcount_t num_words);

/* 恒定时间比较到零-比较长整数的安全方法*/
/* 如果vli==0，则返回1，否则返回0。*/
uECC_word_t uECC_vli_isZero(const uECC_word_t *vli, wordcount_t num_words);

/* 如果设置了vli的位“bit”，则返回非零。*/
uECC_word_t uECC_vli_testBit(const uECC_word_t *vli, bitcount_t bit);

/* 统计表示vli所需的位数。*/
bitcount_t uECC_vli_numBits(const uECC_word_t *vli, const wordcount_t max_words);

/* 设置dest=src。*/
void uECC_vli_set(uECC_word_t *dest, const uECC_word_t *src, wordcount_t num_words);

/* 恒定时间比较函数-比较长整数的安全方法*/
/* 如果左==右，则返回1，否则返回0*/
uECC_word_t uECC_vli_equal(const uECC_word_t *left,
                           const uECC_word_t *right,
                           wordcount_t num_words);

/* 恒定时间比较函数-比较长整数的安全方法*/
/* 返回常量时间内的左-右符号。*/
cmpresult_t uECC_vli_cmp(const uECC_word_t *left, const uECC_word_t *right, wordcount_t num_words);

/* 计算vli=vli>>1。*/
void uECC_vli_rshift1(uECC_word_t *vli, wordcount_t num_words);

/* 计算结果=左+右，返回进位。可以就地修改。*/
uECC_word_t uECC_vli_add(uECC_word_t *result,
                         const uECC_word_t *left,
                         const uECC_word_t *right,
                         wordcount_t num_words);

/* 计算结果=左-右，返回借用。可以就地修改。*/
uECC_word_t uECC_vli_sub(uECC_word_t *result,
                         const uECC_word_t *left,
                         const uECC_word_t *right,
                         wordcount_t num_words);

/* 计算结果=左*右。结果长度必须为2*num_words。*/
void uECC_vli_mult(uECC_word_t *result,
                   const uECC_word_t *left,
                   const uECC_word_t *right,
                   wordcount_t num_words);

/* 计算结果=左^2。结果长度必须为2*num_words。*/
void uECC_vli_square(uECC_word_t *result, const uECC_word_t *left, wordcount_t num_words);

/* 计算结果=（左+右）%mod。假设左<mod和右<mod，并且结果不与mod重叠。*/
void uECC_vli_modAdd(uECC_word_t *result,
                     const uECC_word_t *left,
                     const uECC_word_t *right,
                     const uECC_word_t *mod,
                     wordcount_t num_words);

/* 计算结果=（左-右）%mod。假设左<mod和右<mod，并且结果不与mod重叠。*/
void uECC_vli_modSub(uECC_word_t *result,
                     const uECC_word_t *left,
                     const uECC_word_t *right,
                     const uECC_word_t *mod,
                     wordcount_t num_words);

/* 计算结果=产品%mod，其中产品长度为2N个单词。当前仅设计用于mod==curve->p或curve_n。*/
void uECC_vli_mmod(uECC_word_t *result,
                   uECC_word_t *product,
                   const uECC_word_t *mod,
                   wordcount_t num_words);

/* 计算结果=乘积（mod曲线->p），其中乘积最多为2条曲线->num_word。*/
void uECC_vli_mmod_fast(uECC_word_t *result, uECC_word_t *product, uECC_Curve curve);

/* 计算结果=（左*右）%mod。当前仅设计用于mod==curve->p或curve_n。*/
void uECC_vli_modMult(uECC_word_t *result,
                      const uECC_word_t *left,
                      const uECC_word_t *right,
                      const uECC_word_t *mod,
                      wordcount_t num_words);

/* 计算结果=（左*右）%曲线->p。*/
void uECC_vli_modMult_fast(uECC_word_t *result,
                           const uECC_word_t *left,
                           const uECC_word_t *right,
                           uECC_Curve curve);

/* 计算结果=左^2%模。当前仅设计用于mod==curve->p或curve_n。*/
void uECC_vli_modSquare(uECC_word_t *result,
                        const uECC_word_t *left,
                        const uECC_word_t *mod,
                        wordcount_t num_words);

/* 计算结果=左^2%曲线->p。*/
void uECC_vli_modSquare_fast(uECC_word_t *result, const uECC_word_t *left, uECC_Curve curve);

/* 计算结果=（1/输入）%mod。*/
void uECC_vli_modInv(uECC_word_t *result,
                     const uECC_word_t *input,
                     const uECC_word_t *mod,
                     wordcount_t num_words);

#if uECC_SUPPORT_COMPRESSED_POINT
/* 计算a=sqrt（a）（mod曲线->p）*/
void uECC_vli_mod_sqrt(uECC_word_t *a, uECC_Curve curve);
#endif

/* 将uECC本机格式的整数转换为大端字节。*/
void uECC_vli_nativeToBytes(uint8_t *bytes, int num_bytes, const uECC_word_t *native);
/* 将大端字节转换为uECC本机格式的整数。*/
void uECC_vli_bytesToNative(uECC_word_t *native, const uint8_t *bytes, int num_bytes);

unsigned uECC_curve_num_words(uECC_Curve curve);
unsigned uECC_curve_num_bytes(uECC_Curve curve);
unsigned uECC_curve_num_bits(uECC_Curve curve);
unsigned uECC_curve_num_n_words(uECC_Curve curve);
unsigned uECC_curve_num_n_bytes(uECC_Curve curve);
unsigned uECC_curve_num_n_bits(uECC_Curve curve);

const uECC_word_t *uECC_curve_p(uECC_Curve curve);
const uECC_word_t *uECC_curve_n(uECC_Curve curve);
const uECC_word_t *uECC_curve_G(uECC_Curve curve);
const uECC_word_t *uECC_curve_b(uECC_Curve curve);

int uECC_valid_point(const uECC_word_t *point, uECC_Curve curve);

/* 将点乘以标量。点由同一阵列中的X坐标和Y坐标表示，两个坐标都是曲线->num_words长。注意，标量必须是曲线->num_n_words长（非曲线->num_words）。*/
void uECC_point_mult(uECC_word_t *result,
                     const uECC_word_t *point,
                     const uECC_word_t *scalar,
                     uECC_Curve curve);

/* 生成范围0<random<top的随机整数。随机和顶部都有num_word单词。*/
int uECC_generate_random_int(uECC_word_t *random,
                             const uECC_word_t *top,
                             wordcount_t num_words);

#endif /* uECC_ENABLE_VLI_API*/

#ifdef __cplusplus
} /* 外部“C”结尾*/
#endif

#endif /* _UECC_VLI_H_ */

