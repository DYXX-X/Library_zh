/*
 * 版权所有（c）2009 Chris K Cockrum<ckc@cockrum.net>
 *
 * Copyright (c) 2013 Jens Trillmann <jtrillma@tzi.de> 版权所有（c）2013 Marc Müller Weinhardt<muewei@tzi.de>版权所有（c）2013 Lars Schmertmann<lars@tzi.de>版权所有（c）2013 Hauke Mehrtens<hauke@hauke-m.de>
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 该实现部分基于Chris K Cockrum的论文《在8位微控制器上实现椭圆曲线密码系统》[0]<ckc@cockrum.net>.
 *
 * [0]: http://cockrum.net/Implementation_of_ECC_on_an_8-bit_microcontroller.pdf
 *
 * 这是32位CPU架构的secp256r1曲线上的有效ECC实现。它提供secp256r1曲线的基本操作，并支持ECDH和ECDSA。
 */
#include <inttypes.h>

#define keyLengthInBytes 32
#define arrayLength 8

extern const uint32_t ecc_g_point_x[8];
extern const uint32_t ecc_g_point_y[8];

//ec功能
void ecc_ec_mult(const uint32_t *px, const uint32_t *py, const uint32_t *secret, uint32_t *resultx, uint32_t *resulty);

static inline void ecc_ecdh(const uint32_t *px, const uint32_t *py, const uint32_t *secret, uint32_t *resultx, uint32_t *resulty) {
	ecc_ec_mult(px, py, secret, resultx, resulty);
}
int ecc_ecdsa_validate(const uint32_t *x, const uint32_t *y, const uint32_t *e, const uint32_t *r, const uint32_t *s);
int ecc_ecdsa_sign(const uint32_t *d, const uint32_t *e, const uint32_t *k, uint32_t *r, uint32_t *s);

int ecc_is_valid_key(const uint32_t * priv_key);
static inline void ecc_gen_pub_key(const uint32_t *priv_key, uint32_t *pub_x, uint32_t *pub_y)
{
	ecc_ec_mult(ecc_g_point_x, ecc_g_point_y, priv_key, pub_x, pub_y);
}

#ifdef TEST_INCLUDE
//ec功能
void ecc_ec_add(const uint32_t *px, const uint32_t *py, const uint32_t *qx, const uint32_t *qy, uint32_t *Sx, uint32_t *Sy);
void ecc_ec_double(const uint32_t *px, const uint32_t *py, uint32_t *Dx, uint32_t *Dy);

//大数加减的简单函数
uint32_t ecc_add( const uint32_t *x, const uint32_t *y, uint32_t *result, uint8_t length);
uint32_t ecc_sub( const uint32_t *x, const uint32_t *y, uint32_t *result, uint8_t length);

//大数的字段函数
int ecc_fieldAdd(const uint32_t *x, const uint32_t *y, const uint32_t *reducer, uint32_t *result);
int ecc_fieldSub(const uint32_t *x, const uint32_t *y, const uint32_t *modulus, uint32_t *result);
int ecc_fieldMult(const uint32_t *x, const uint32_t *y, uint32_t *result, uint8_t length);
void ecc_fieldModP(uint32_t *A, const uint32_t *B);
void ecc_fieldModO(const uint32_t *A, uint32_t *result, uint8_t length);
void ecc_fieldInv(const uint32_t *A, const uint32_t *modulus, const uint32_t *reducer, uint32_t *B);

//处理大数字的简单函数
void ecc_copy(const uint32_t *from, uint32_t *to, uint8_t length);
int ecc_isSame(const uint32_t *A, const uint32_t *B, uint8_t length);
void ecc_setZero(uint32_t *A, const int length);
int ecc_isOne(const uint32_t* A);
void ecc_rshift(uint32_t* A);
int ecc_isGreater(const uint32_t *A, const uint32_t *B, uint8_t length);

#endif /* TEST_INCLUDE */

