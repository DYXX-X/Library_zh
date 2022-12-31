/*
 *  版权所有（c）2021，The OpenThread Authors。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief 该文件包括Crypto操作的平台抽象。
 */

#ifndef OPENTHREAD_PLATFORM_CRYPTO_H_
#define OPENTHREAD_PLATFORM_CRYPTO_H_

#include <stdint.h>
#include <stdlib.h>

#include <openthread/error.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 平板密码
 *
 * @brief 该模块包括Crypto的平台抽象。
 *
 * @{
 *
 */

/**
 * 此枚举定义键类型。
 *
 */
typedef enum
{
    OT_CRYPTO_KEY_TYPE_RAW,  ///<密钥类型：原始数据。
    OT_CRYPTO_KEY_TYPE_AES,  ///<密钥类型：AES。
    OT_CRYPTO_KEY_TYPE_HMAC, ///<密钥类型：HMAC。
} otCryptoKeyType;

/**
 * 此枚举定义了关键算法。
 *
 */
typedef enum
{
    OT_CRYPTO_KEY_ALG_VENDOR,       ///<关键算法：供应商定义。
    OT_CRYPTO_KEY_ALG_AES_ECB,      ///<关键算法：AES ECB。
    OT_CRYPTO_KEY_ALG_HMAC_SHA_256, ///<关键算法：HMAC SHA-256。
} otCryptoKeyAlgorithm;

/**
 * 此枚举定义密钥使用标志。
 *
 */
enum
{
    OT_CRYPTO_KEY_USAGE_NONE      = 0,      ///<密钥用法：密钥用法为空。
    OT_CRYPTO_KEY_USAGE_EXPORT    = 1 << 0, ///<密钥用法：可以导出密钥。
    OT_CRYPTO_KEY_USAGE_ENCRYPT   = 1 << 1, ///<密钥用法：加密（供应商定义）。
    OT_CRYPTO_KEY_USAGE_DECRYPT   = 1 << 2, ///<密钥用法：AES ECB。
    OT_CRYPTO_KEY_USAGE_SIGN_HASH = 1 << 3, ///<密钥用法：HMAC SHA-256。
};

/**
 * 此枚举定义密钥存储类型。
 *
 */
typedef enum
{
    OT_CRYPTO_KEY_STORAGE_VOLATILE,   ///<密钥持久性：密钥是易失的。
    OT_CRYPTO_KEY_STORAGE_PERSISTENT, ///<密钥持久性：密钥是持久的。
} otCryptoKeyStorage;

/**
 * 此数据类型表示密钥引用。
 *
 */
typedef uint32_t otCryptoKeyRef;

/**
 * @struct otCryptoKey
 *
 * 此结构表示加密操作所需的密钥材料。
 *
 */
typedef struct otCryptoKey
{
    const uint8_t *mKey;       ///<指向包含密钥的缓冲区的指针。NULL表示使用“mKeyRef”。
    uint16_t       mKeyLength; ///<密钥长度（以字节为单位）（当“mKey”不为NULL时适用）。
    uint32_t       mKeyRef;    ///<PSA密钥引用（要求“mKey”为NULL）。
} otCryptoKey;

/**
 * @struct otCryptoContext
 *
 * 此结构存储平台API的上下文对象。
 *
 */
typedef struct otCryptoContext
{
    void *   mContext;     ///<指向上下文的指针。
    uint16_t mContextSize; ///<以字节为单位的上下文长度。
} otCryptoContext;

/**
 * 初始化Crypto模块。
 *
 * @retval OT_ERROR_NONE已成功初始化加密模块。
 * @retval OT_ERROR_FAILED未能初始化加密模块。
 *
 */
otError otPlatCryptoInit(void);

/**
 * 将密钥导入PSA ITS。
 *
 * @param[inout] aKeyRef           指向用于加密操作的密钥引用的指针。
 * @param[in]    aKeyType          密钥的密钥类型编码。
 * @param[in]    aKeyAlgorithm     密钥的密钥算法编码。
 * @param[in]    aKeyUsage         密钥的密钥用法编码（`OT_CRYPTO_Key_Usage_*`的组合）。
 * @param[in]    aKeyPersistence   此密钥的密钥持久性
 * @param[in]    aKey              要导入的实际密钥。
 * @param[in]    aKeyLen           要导入的密钥的长度。
 *
 * @retval OT_ERROR_NONE已成功导入密钥。
 * @retval OT_ERROR_FAILED无法导入密钥。
 * @retval OT_ERROR_INVALID_ARGS@p aKey设置为NULL。
 *
 * @note 如果为aKeyPersistence传递OT_CRYPTO_KEY_STORAGE_PERSISTENT，则输入@p aKeyRef，平台应使用给定的aKeyRef，且不得更改。
 *
 *       If OT_CRYPTO_KEY_STORAGE_VOLATILE is passed for aKeyPersistence then @p aKeyRef是输出的，初始值无关紧要，平台API必须更新它以返回新的key ref。
 *
 *       此API仅在启用`OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE`时由OT核心使用。
 *
 */
otError otPlatCryptoImportKey(otCryptoKeyRef *     aKeyRef,
                              otCryptoKeyType      aKeyType,
                              otCryptoKeyAlgorithm aKeyAlgorithm,
                              int                  aKeyUsage,
                              otCryptoKeyStorage   aKeyPersistence,
                              const uint8_t *      aKey,
                              size_t               aKeyLen);

/**
 * 导出PSA ITS中存储的密钥。
 *
 * @param[in]   aKeyRef           用于加密操作的密钥引用。
 * @param[out]  aBuffer           指向需要导出密钥的缓冲区的指针。
 * @param[in]   aBufferLen        传递用于存储导出密钥的缓冲区长度。
 * @param[out]  aKeyLen           返回导出密钥长度的指针。
 *
 * @retval OT_ERROR_NONE成功导出@p aKeyRef。
 * @retval OT_ERROR_FAILED无法导出@p aKeyRef。
 * @retval OT_ERROR_INVALID_ARGS@p缓冲区为空
 *
 * @note 此API仅在启用`OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE`时由OT核心使用。
 *
 */
otError otPlatCryptoExportKey(otCryptoKeyRef aKeyRef, uint8_t *aBuffer, size_t aBufferLen, size_t *aKeyLen);

/**
 * 销毁PSA ITS中存储的钥匙。
 *
 * @param[in]   aKeyRef          要销毁的密钥引用
 *
 * @retval OT_ERROR_NONE已成功销毁密钥。
 * @retval OT_ERROR_FAILED无法销毁密钥。
 *
 * @note 此API仅在启用`OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE`时由OT核心使用。
 *
 */
otError otPlatCryptoDestroyKey(otCryptoKeyRef aKeyRef);

/**
 * 检查传递的钥匙参考是否具有PSA ITS中的相关钥匙。
 *
 * @param[in]  aKeyRef          要检查的关键参考。
 *
 * @retval TRUE有一个与@p aKeyRef关联的键。
 * @retval FALSE没有与@p aKeyRef关联的键。
 *
 * @note 此API仅在启用`OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE`时由OT核心使用。
 *
 */
bool otPlatCryptoHasKey(otCryptoKeyRef aKeyRef);

/**
 * 初始化HMAC操作。
 *
 * @param[in]  aContext          HMAC操作的上下文。
 *
 * @retval OT_ERROR_NONE已成功初始化HMAC操作。
 * @retval OT_ERROR_FAILED无法初始化HMAC操作。
 * @retval OT_ERROR_INVALID_ARGS@p a上下文为空
 *
 * @note 平台驱动程序应将上下文指向正确的对象，如psa_mac_operation_t或mbedtls_md_context_t。
 *
 */
otError otPlatCryptoHmacSha256Init(otCryptoContext *aContext);

/**
 * 取消初始化HMAC操作。
 *
 * @param[in]  aContext          HMAC操作的上下文。
 *
 * @retval OT_ERROR_NONE已成功取消初始化HMAC操作。
 * @retval OT_ERROR_FAILED无法取消初始化HMAC操作。
 * @retval OT_ERROR_INVALID_ARGS@p a上下文为空
 *
 */
otError otPlatCryptoHmacSha256Deinit(otCryptoContext *aContext);

/**
 * 启动HMAC操作。
 *
 * @param[in]  aContext           HMAC操作的上下文。
 * @param[in]  aKey               用于HMAC操作的关键材料。
 *
 * @retval OT_ERROR_NONE已成功启动HMAC操作。
 * @retval OT_ERROR_FAILED无法启动HMAC操作。
 * @retval OT_ERROR_INVALID_ARGS@p aContext或@p aKey为空
 *
 */
otError otPlatCryptoHmacSha256Start(otCryptoContext *aContext, const otCryptoKey *aKey);

/**
 * 使用新输入更新HMAC操作。
 *
 * @param[in]  aContext           HMAC操作的上下文。
 * @param[in]  aBuf               指向输入缓冲区的指针。
 * @param[in]  aBufLength         @p aBuf的长度（以字节为单位）。
 *
 * @retval OT_ERROR_NONE使用新的输入操作成功更新HMAC。
 * @retval OT_ERROR_FAILED无法更新HMAC操作。
 * @retval OT_ERROR_INVALID_ARGS@p aContext或@p aBuf为空
 *
 */
otError otPlatCryptoHmacSha256Update(otCryptoContext *aContext, const void *aBuf, uint16_t aBufLength);

/**
 * 完成HMAC操作。
 *
 * @param[in]  aContext           HMAC操作的上下文。
 * @param[out] aBuf               指向输出缓冲区的指针。
 * @param[in]  aBufLength         @p aBuf的长度（以字节为单位）。
 *
 * @retval OT_ERROR_NONE已成功完成HMAC操作。
 * @retval OT_ERROR_FAILED无法完成HMAC操作。
 * @retval OT_ERROR_INVALID_ARGS@p aContext或@p aBuf为空
 *
 */
otError otPlatCryptoHmacSha256Finish(otCryptoContext *aContext, uint8_t *aBuf, size_t aBufLength);

/**
 * 初始化AES操作。
 *
 * @param[in]  aContext           AES操作的上下文。
 *
 * @retval OT_ERROR_NONE已成功初始化AES操作。
 * @retval OT_ERROR_FAILED无法初始化AES操作。
 * @retval OT_ERROR_INVALID_ARGS@p a上下文为空
 * @retval OT_ERROR_NO_BUFS无法分配上下文。
 *
 * @note 平台驱动程序应将上下文指向正确的对象，如psa_key_id或mbedtls_aes_context_t。
 *
 */
otError otPlatCryptoAesInit(otCryptoContext *aContext);

/**
 * 设置AES操作的密钥。
 *
 * @param[in]  aContext           AES操作的上下文。
 * @param[out] aKey               用于AES操作的密钥。
 *
 * @retval OT_ERROR_NONE已成功设置AES操作的密钥。
 * @retval OT_ERROR_FAILED无法设置AES操作的密钥。
 * @retval OT_ERROR_INVALID_ARGS@p aContext或@p aKey为空
 *
 */
otError otPlatCryptoAesSetKey(otCryptoContext *aContext, const otCryptoKey *aKey);

/**
 * 加密给定数据。
 *
 * @param[in]  aContext           AES操作的上下文。
 * @param[in]  aInput             指向输入缓冲区的指针。
 * @param[in]  aOutput            指向输出缓冲区的指针。
 *
 * @retval OT_ERROR_NONE已成功加密@p aInput。
 * @retval OT_ERROR_FAILED无法加密@p aInput。
 * @retval OT_ERROR_INVALID_ARGS@p aContext或@p aKey或@p a Output为空
 *
 */
otError otPlatCryptoAesEncrypt(otCryptoContext *aContext, const uint8_t *aInput, uint8_t *aOutput);

/**
 * 释放AES上下文。
 *
 * @param[in]  aContext           AES操作的上下文。
 *
 * @retval OT_ERROR_NONE已成功释放AES上下文。
 * @retval OT_ERROR_FAILED无法释放AES上下文。
 * @retval OT_ERROR_INVALID_ARGS@p a上下文为空
 *
 */
otError otPlatCryptoAesFree(otCryptoContext *aContext);

/**
 * 初始化HKDF上下文。
 *
 * @param[in]  aContext           香港发展基金运作的背景。
 *
 * @retval OT_ERROR_NONE已成功初始化AES操作。
 * @retval OT_ERROR_FAILED无法初始化AES操作。
 * @retval OT_ERROR_INVALID_ARGS@p a上下文为空
 *
 * @note 平台驱动程序应将上下文指向正确的对象，如psa_key_derivation_operation_t或HmacSha256:：Hash
 *
 */
otError otPlatCryptoHkdfInit(otCryptoContext *aContext);

/**
 * 执行HKDF扩展步骤。
 *
 * @param[in]  aContext           HKDF操作的操作上下文。
 * @param[in]  aInfo              指向Info序列的指针。
 * @param[in]  aInfoLength        信息序列的长度。
 * @param[out] aOutputKey         指向输出密钥的指针。
 * @param[in]  aOutputKeyLength   输出密钥缓冲区的大小。
 *
 * @retval OT_ERROR_NONE HKDF扩展成功。
 * @retval OT_ERROR_FAILED HKDF扩展失败。
 * @retval OT_ERROR_INVALID_ARGS@p a上下文为空
 *
 */
otError otPlatCryptoHkdfExpand(otCryptoContext *aContext,
                               const uint8_t *  aInfo,
                               uint16_t         aInfoLength,
                               uint8_t *        aOutputKey,
                               uint16_t         aOutputKeyLength);

/**
 * 执行HKDF提取步骤。
 *
 * @param[in]  aContext           HKDF操作的操作上下文。
 * @param[in]  aSalt              指向HKDF盐的指针。
 * @param[in]  aInfoLength        盐的长度。
 * @param[in]  aInputKey          指向输入键的指针。
 *
 * @retval OT_ERROR_NONE HKDF提取成功。
 * @retval OT_ERROR_FAILED HKDF提取失败。
 *
 */
otError otPlatCryptoHkdfExtract(otCryptoContext *  aContext,
                                const uint8_t *    aSalt,
                                uint16_t           aSaltLength,
                                const otCryptoKey *aInputKey);

/**
 * 取消HKDF上下文的初始化。
 *
 * @param[in]  aContext           香港发展基金运作的背景。
 *
 * @retval OT_ERROR_NONE成功取消初始化HKDF操作。
 * @retval OT_ERROR_FAILED无法取消初始化HKDF操作。
 * @retval OT_ERROR_INVALID_ARGS@p a上下文为空
 *
 */
otError otPlatCryptoHkdfDeinit(otCryptoContext *aContext);

/**
 * 初始化SHA-256操作。
 *
 * @param[in]  aContext           SHA-256操作的上下文。
 *
 * @retval OT_ERROR_NONE已成功初始化SHA-256操作。
 * @retval OT_ERROR_FAILED无法初始化SHA-256操作。
 * @retval OT_ERROR_INVALID_ARGS@p a上下文为空
 *
 *
 * @note 平台驱动程序应将上下文指向正确的对象，例如psa_hash_operation_t或mbedtls_sha256_context。
 */
otError otPlatCryptoSha256Init(otCryptoContext *aContext);

/**
 * 取消初始化SHA-256操作。
 *
 * @param[in]  aContext           SHA-256操作的上下文。
 *
 * @retval OT_ERROR_NONE已成功取消初始化SHA-256操作。
 * @retval OT_ERROR_FAILED无法取消初始化SHA-256操作。
 * @retval OT_ERROR_INVALID_ARGS@p a上下文为空
 *
 */
otError otPlatCryptoSha256Deinit(otCryptoContext *aContext);

/**
 * 启动SHA-256操作。
 *
 * @param[in]  aContext           SHA-256操作的上下文。
 *
 * @retval OT_ERROR_NONE已成功启动SHA-256操作。
 * @retval OT_ERROR_FAILED无法启动SHA-256操作。
 * @retval OT_ERROR_INVALID_ARGS@p a上下文为空
 *
 */
otError otPlatCryptoSha256Start(otCryptoContext *aContext);

/**
 * 使用新输入更新SHA-256操作。
 *
 * @param[in]  aContext           SHA-256操作的上下文。
 * @param[in]  aBuf               指向输入缓冲区的指针。
 * @param[in]  aBufLength         @p aBuf的长度（以字节为单位）。
 *
 * @retval OT_ERROR_NONE使用新的输入操作成功更新了SHA-256。
 * @retval OT_ERROR_FAILED无法更新SHA-256操作。
 * @retval OT_ERROR_INVALID_ARGS@p aContext或@p aBuf为空
 *
 */
otError otPlatCryptoSha256Update(otCryptoContext *aContext, const void *aBuf, uint16_t aBufLength);

/**
 * 完成SHA-256操作。
 *
 * @param[in]  aContext           SHA-256操作的上下文。
 * @param[in]  aContextSize       上下文大小SHA-256操作。
 * @param[in]  aHash              指向需要存储哈希的输出缓冲区的指针。
 * @param[in]  aHashSize          @p aHash的长度（以字节为单位）。
 *
 * @retval OT_ERROR_NONE已成功完成SHA-256操作。
 * @retval OT_ERROR_FAILED无法完成SHA-256操作。
 * @retval OT_ERROR_INVALID_ARGS@p aContext或@p aHash为空
 *
 */
otError otPlatCryptoSha256Finish(otCryptoContext *aContext, uint8_t *aHash, uint16_t aHashSize);

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”结尾
#endif
#endif // OPENTHREAD_PLATFORM_CRYPTO_H_

