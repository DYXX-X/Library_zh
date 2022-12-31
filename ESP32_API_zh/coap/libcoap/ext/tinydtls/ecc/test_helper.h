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

extern const uint32_t ecc_prime_m[8];
extern const uint32_t ecc_prime_r[8];

//用于打印长数字的调试函数
void ecc_printNumber(const uint32_t *x, int numberLength);
void ecc_setRandom(uint32_t *secret);

#ifdef CONTIKI
#undef assert
#define assert(e) ((e) ? (void)0 : test_assert(__FILE__, __LINE__))
void test_assert(const char *, int);
#endif

