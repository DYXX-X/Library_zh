/*
 *  版权所有（c）2019，The OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread加密随机数生成器API。
 */

#ifndef OPENTHREAD_RANDOM_CRYPTO_H_
#define OPENTHREAD_RANDOM_CRYPTO_H_

#include <stdint.h>

#include <mbedtls/ctr_drbg.h>
#include <openthread/error.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api随机密码
 *
 * @brief 此模块包括生成加密随机数的函数。
 *
 * @{
 *
 */

/**
 * 此函数使用加密安全的随机字节填充给定缓冲区。
 *
 * @param[out] aBuffer  指向要填充随机字节的缓冲区的指针。
 * @param[in]  aSize    缓冲区大小（要填充的字节数）。
 *
 */
otError otRandomCryptoFillBuffer(uint8_t *aBuffer, uint16_t aSize);

/**
 * 此函数返回初始化的mbedtls_ctr_drbg_context。
 *
 * @returns  指向已初始化的mbedtls_ctr_drbg_context的指针。
 */
mbedtls_ctr_drbg_context *otRandomCryptoMbedTlsContextGet(void);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_RANDOM_CRYPTO_H_

