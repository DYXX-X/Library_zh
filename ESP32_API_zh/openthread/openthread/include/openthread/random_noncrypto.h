/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread非加密随机数生成器API。
 */

#ifndef OPENTHREAD_RANDOM_H_
#define OPENTHREAD_RANDOM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api随机非加密
 *
 * @brief 此模块包括生成非加密随机数的函数。
 *
 * @{
 *
 */

/**
 * 此函数生成并返回随机“uint32_t”值。
 *
 * @returns    随机“uint32_t”值。
 *
 */
uint32_t otRandomNonCryptoGetUint32(void);

/**
 * 此函数生成并返回一个随机字节。
 *
 * @returns 随机“uint8_t”值。
 *
 */
uint8_t otRandomNonCryptoGetUint8(void);

/**
 * 此函数生成并返回随机“uint16_t”值。
 *
 * @returns 随机“uint16_t”值。
 *
 */
uint16_t otRandomNonCryptoGetUint16(void);

/**
 * 此函数生成并返回给定范围“[aMin，aMax）”内的随机“uint8_t”值。
 *
 * @param[in]  aMin  最小值（此值可以包含在返回的随机结果中）。
 * @param[in]  aMax  最大值（此值从返回的随机结果中排除）。
 *
 * @returns    给定范围内的随机“uint8_t”值（即aMin<=随机值<aMax）。
 */
uint8_t otRandomNonCryptoGetUint8InRange(uint8_t aMin, uint8_t aMax);

/**
 * 此函数生成并返回给定范围“[aMin，aMax）”内的随机“uint16_t”值。
 *
 * @note 返回的随机值可以包含@p aMin值，但不包括@p aMax。
 *
 * @param[in]  aMin  最小值（此值可以包含在返回的随机结果中）。
 * @param[in]  aMax  最大值（此值从返回的随机结果中排除）。
 *
 * @returns    给定范围内的随机“uint16_t”值（即，aMin<=随机值<aMax）。
 */
uint16_t otRandomNonCryptoGetUint16InRange(uint16_t aMin, uint16_t aMax);

/**
 * 此函数生成并返回给定范围“[aMin，aMax）”内的随机“uint32_t”值。
 *
 * @note 返回的随机值可以包含@p aMin值，但不包括@p aMax。
 *
 * @param[in]  aMin  最小值（此值可以包含在返回的随机结果中）。
 * @param[in]  aMax  最大值（此值从返回的随机结果中排除）。
 *
 * @returns    给定范围内的随机“uint32_t”值（即，aMin<=随机值<aMax）。
 *
 */
uint32_t otRandomNonCryptoGetUint32InRange(uint32_t aMin, uint32_t aMax);

/**
 * 此函数用随机字节填充给定的缓冲区。
 *
 * @param[out] aBuffer  指向要填充随机字节的缓冲区的指针。
 * @param[in]  aSize    缓冲区大小（要填充的字节数）。
 *
 */
void otRandomNonCryptoFillBuffer(uint8_t *aBuffer, uint16_t aSize);

/**
 * 此函数将给定范围内的随机抖动添加到给定值。
 *
 * @param[in]  aValue     添加随机抖动的值。
 * @param[in]  aJitter    最大抖动。从范围“[-aJitter，aJitter]”中选择随机抖动。
 *
 * @returns    具有附加随机抖动的给定值。
 *
 */
uint32_t otRandomNonCryptoAddJitter(uint32_t aValue, uint16_t aJitter);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_RANDOM_H_

