/**
 * \简短的AES GCM分组密码，ESP硬件加速版本基于mbedTLS FIPS-197兼容版本。
 *
 *  版权所有（C）2006-2015，ARM Limited，保留所有权利添加版权所有（C）2019-2020，Espressif Systems（Shanghai）PTE Ltd SPDX License Identifier:Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 *
 */

#pragma once

#include "aes/esp_aes.h"
#include "mbedtls/cipher.h"
#include "soc/lldesc.h"

#ifdef __cplusplus
extern "C" {
#endif


#define MBEDTLS_ERR_GCM_AUTH_FAILED      -0x0012  /**<经过身份验证的解密失败。*/
#define MBEDTLS_ERR_GCM_BAD_INPUT        -0x0014  /**<功能输入参数错误。*/

typedef enum {
    ESP_AES_GCM_STATE_INIT,
    ESP_AES_GCM_STATE_START,
    ESP_AES_GCM_STATE_UPDATE,
    ESP_AES_GCM_STATE_FINISH
} esp_aes_gcm_state;
/**
 * \GCM上下文结构简介。
 */
typedef struct {
    uint8_t H[16];                        /*!< 初始哈希值*/
    uint8_t ghash[16];                    /*!< GHASH值。*/
    uint8_t J0[16];
    uint64_t HL[16];                      /*!< 预先计算的HTable低。*/
    uint64_t HH[16];                      /*!< 预先计算的HTable高。*/
    uint8_t ori_j0[16];                   /*!< J0来自第一次迭代。*/
    const uint8_t *iv;
    size_t iv_len;                       /*!< IV的长度。*/
    uint64_t aad_len;                     /*!< 附加数据的总长度。*/
    size_t data_len;
    int mode;
    const unsigned char *aad;             /*!< 附加数据。*/
    esp_aes_context aes_ctx;
    esp_aes_gcm_state gcm_state;
} esp_gcm_context;


/**
 * \brief此函数初始化指定的GCM上下文
 *
 * \param ctx要初始化的GCM上下文。
 */
void esp_aes_gcm_init( esp_gcm_context *ctx);

/**
 * \brief此函数将GCM上下文与密钥关联。
 *
 * \param ctx要初始化的GCM上下文。\param cipher要使用的128位分组密码。\param key加密密钥。\param keybits以位为单位的密钥大小。有效选项为：＜ul＞＜li＞128位＜/li＞＜li＜192位＜/li>＜li＞256位＜/li＞＜/ul＞
 *
 * \成功时返回\c 0。\return失败时的密码特定错误代码。
 */
int esp_aes_gcm_setkey( esp_gcm_context *ctx,
                        mbedtls_cipher_id_t cipher,
                        const unsigned char *key,
                        unsigned int keybits );

/**
 * \brief此函数启动GCM加密或解密操作。
 *
 * \param ctx GCM上下文。\param mode要执行的操作：#MBEDTLS_GCM_ENCRYPT或#MBEDTLS _GCM_DECRYPT。\param iv初始化向量。\param iv_len iv的长度。\param add保存附加数据的缓冲区，如果\p aad_len为0，则为NULL。\pram aad_lenn附加数据的长度。如果为0，\p add为NULL。
 *
 * \成功时返回\c 0。
 */
int esp_aes_gcm_starts( esp_gcm_context *ctx,
                        int mode,
                        const unsigned char *iv,
                        size_t iv_len,
                        const unsigned char *aad,
                        size_t aad_len );

/**
 * \brief此函数将输入缓冲区送入正在进行的GCM加密或解密操作。
 *
 *    `该函数要求输入为16字节的倍数。只有在调用mbedtls_gcm_finish（）之前的最后一次调用才能小于16字节。
 *
 * \注意：对于解密，输出缓冲区不能与输入缓冲区相同。如果缓冲区重叠，则输出缓冲区必须落后于输入缓冲区至少8个字节。
 *
 * \param ctx GCM上下文。\param length输入数据的长度。这必须是16的倍数，除了在mbedtls_gcm_finish（）之前的最后一次调用中。\param input保存输入数据的缓冲区。\param output用于保存输出数据的缓冲区。
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_GCM_BAD_INPUT。
 */
int esp_aes_gcm_update( esp_gcm_context *ctx,
                        size_t length,
                        const unsigned char *input,
                        unsigned char *output );

/**
 * \brief此函数完成GCM操作并生成身份验证标签。
 *
 *                  它包装GCM流，并生成标记。标记的最大长度为16字节。
 *
 * \param ctx GCM上下文。\param tag用于保存标记的缓冲区。\param tag_len要生成的标记的长度。必须至少有四个。
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_GCM_BAD_INPUT。
 */
int esp_aes_gcm_finish( esp_gcm_context *ctx,
                        unsigned char *tag,
                        size_t tag_len );

/**
 * \brief此函数清除GCM上下文
 *
 * \param ctx要清除的GCM上下文。
 */
void esp_aes_gcm_free( esp_gcm_context *ctx);

/**
 * \brief此函数执行缓冲区的GCM加密或解密。
 *
 * \注意：对于加密，输出缓冲区可以与输入缓冲区相同。对于解密，输出缓冲区不能与输入缓冲区相同。如果缓冲区重叠，则输出缓冲区必须落后于输入缓冲区至少8个字节。
 *
 * \param ctx用于加密或解密的GCM上下文。\param mode要执行的操作：#MBEDTLS_GCM_ENCRYPT或#MBEDTLS _GCM_DECRYPT。\param length输入数据的长度。这必须是16的倍数，除了在mbedtls_gcm_finish（）之前的最后一次调用中。\param iv初始化向量。\param iv_len iv的长度。\param add保存附加数据的缓冲区。\param aad_len附加数据的长度。\param input保存输入数据的缓冲区。\param output用于保存输出数据的缓冲区。\param tag_len要生成的标记的长度。\param tag用于保存标记的缓冲区。
 *
 * \成功时返回\c 0。
 */
int esp_aes_gcm_crypt_and_tag( esp_gcm_context *ctx,
                               int mode,
                               size_t length,
                               const unsigned char *iv,
                               size_t iv_len,
                               const unsigned char *add,
                               size_t aad_len,
                               const unsigned char *input,
                               unsigned char *output,
                               size_t tag_len,
                               unsigned char *tag );


/**
 * \brief此函数执行缓冲区的GCM认证解密。
 *
 * \注意：对于解密，输出缓冲区不能与输入缓冲区相同。如果缓冲区重叠，则输出缓冲区必须落后于输入缓冲区至少8个字节。
 *
 * \param ctx GCM上下文。\param length输入数据的长度。这必须是16的倍数，除了在mbedtls_gcm_finish（）之前的最后一次调用中。\param iv初始化向量。\param iv_len iv的长度。\param add保存附加数据的缓冲区。\param aad_len附加数据的长度。\param tag保存标记的缓冲区。\param tag_len标记的长度。\param input保存输入数据的缓冲区。\param output用于保存输出数据的缓冲区。
 *
 * \如果成功并经过身份验证，则返回0。\如果标记不匹配，则返回#MBEDTLS_ERROR_GCM_AUTH_FAILED。
 */
int esp_aes_gcm_auth_decrypt( esp_gcm_context *ctx,
                              size_t length,
                              const unsigned char *iv,
                              size_t iv_len,
                              const unsigned char *add,
                              size_t aad_len,
                              const unsigned char *tag,
                              size_t tag_len,
                              const unsigned char *input,
                              unsigned char *output );

#ifdef __cplusplus
}
#endif

