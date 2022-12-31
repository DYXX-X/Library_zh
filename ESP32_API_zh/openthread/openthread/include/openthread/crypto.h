/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 此文件定义OpenThread加密C API。
 */

#ifndef OPENTHREAD_CRYPTO_H_
#define OPENTHREAD_CRYPTO_H_

#include <stdbool.h>
#include <stdint.h>

#include <openthread/error.h>
#include <openthread/platform/crypto.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup api加密
 *
 * @brief 该模块包括密码功能。
 *
 * @{
 *
 */

#define OT_CRYPTO_SHA256_HASH_SIZE 32 ///<SHA256哈希的长度（字节）。

/**
 * @struct otCryptoSha256Hash
 *
 * 此结构表示SHA-256哈希。
 *
 */
OT_TOOL_PACKED_BEGIN
struct otCryptoSha256Hash
{
    uint8_t m8[OT_CRYPTO_SHA256_HASH_SIZE]; ///<哈希字节。
} OT_TOOL_PACKED_END;

/**
 * 此结构表示SHA-256哈希。
 *
 */
typedef struct otCryptoSha256Hash otCryptoSha256Hash;

/**
 * 此函数执行HMAC计算。
 *
 * @param[in]     aKey           指向键的指针。
 * @param[in]     aBuf           指向输入缓冲区的指针。
 * @param[in]     aBufLength     @p aBuf的长度（以字节为单位）。
 * @param[out]    aHash          指向“otCryptoSha256Hash”结构以输出哈希值的指针。
 *
 */
void otCryptoHmacSha256(const otCryptoKey *aKey, const uint8_t *aBuf, uint16_t aBufLength, otCryptoSha256Hash *aHash);

/**
 * 此方法执行AES CCM计算。
 *
 * @param[in]     aKey           指向键的指针。
 * @param[in]     aTagLength     标记的长度（字节）。
 * @param[in]     aNonce         指向随机数的指针。
 * @param[in]     aNonceLength   随机数的长度（字节）。
 *
 * @param[in]     aHeader        指向标头的指针。
 * @param[in]     aHeaderLength  标头的长度（字节）。
 *
 * @param[inout]  aPlainText     指向明文的指针。
 * @param[inout]  aCipherText    指向密文的指针。
 * @param[in]     aLength        明文长度（字节）。
 * @param[in]     aEncrypt       `加密时为true，解密时为false。
 *
 * @param[out]    aTag           指向标记的指针。
 *
 */
void otCryptoAesCcm(const otCryptoKey *aKey,
                    uint8_t            aTagLength,
                    const void *       aNonce,
                    uint8_t            aNonceLength,
                    const void *       aHeader,
                    uint32_t           aHeaderLength,
                    void *             aPlainText,
                    void *             aCipherText,
                    uint32_t           aLength,
                    bool               aEncrypt,
                    void *             aTag);

/**
 * 此方法创建ECDSA符号。
 *
 * @param[out]    aOutput            应存储ECDSA符号的输出缓冲区。
 * @param[inout]  aOutputLength      @p aOutput缓冲区的长度。
 * @param[in]     aInputHash         输入哈希。
 * @param[in]     aInputHashLength   @p aInputHash缓冲区的长度。
 * @param[in]     aPrivateKey        PEM格式的私钥。
 * @param[in]     aPrivateKeyLength  @p aPrivateKey缓冲区的长度。
 *
 * @retval  OT_ERROR_NONE ECDSA标志已成功创建。
 * @retval  OT_ERROR_NO_BUFS输出缓冲区太小。
 * @retval  OT_ERROR_INVALID_ARGS私钥不是有效的EC私钥。
 * @retval  OT_ERROR_FAILED签名期间出错。
 */
otError otCryptoEcdsaSign(uint8_t *      aOutput,
                          uint16_t *     aOutputLength,
                          const uint8_t *aInputHash,
                          uint16_t       aInputHashLength,
                          const uint8_t *aPrivateKey,
                          uint16_t       aPrivateKeyLength);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_CRYPTO_H_

