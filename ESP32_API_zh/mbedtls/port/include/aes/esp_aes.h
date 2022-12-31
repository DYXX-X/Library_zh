/**
 * \简单AES分组密码，ESP硬件加速版本基于mbedTLS FIPS-197兼容版本。
 *
 *  版权所有（C）2006-2015，ARM Limited，保留所有权利添加版权所有（C）2016，Espressif Systems（Shanghai）PTE Ltd SPDX License Identifier:Apache-2.0
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

#include "esp_types.h"
#include "hal/aes_types.h"

#ifdef __cplusplus
extern "C" {
#endif



#define ERR_ESP_AES_INVALID_KEY_LENGTH                -0x0020  /**<密钥长度无效。*/
#define ERR_ESP_AES_INVALID_INPUT_LENGTH              -0x0022  /**<数据输入长度无效。*/

/**
 * \简要AES上下文结构
 *
 */
typedef struct {
    uint8_t key_bytes;
    volatile uint8_t key_in_hardware; /* 此变量用于故障注入检查，因此标记为易失性，以避免优化*/
    uint8_t key[32];
} esp_aes_context;

/**
 * \简要AES XTS上下文类型定义。
 */
typedef struct
{
    esp_aes_context crypt; /*!< 用于AES块加密或解密的AES上下文。*/
    esp_aes_context tweak; /*!< 用于调整计算的AES上下文。*/
} esp_aes_xts_context;




/**
 * \对AES硬件单元的短暂锁定访问
 *
 * AES硬件单元一次只能由一个用户使用。
 *
 * esp_aes_xxx API调用自动管理硬件的锁定和解锁，仅当您想直接调用ets_aes_xx函数时才需要此函数。
 */
void esp_aes_acquire_hardware( void );

/**
 * \对AES硬件单元的短暂解锁访问
 *
 * esp_aes_xxx API调用自动管理硬件的锁定和解锁，仅当您想直接调用ets_aes_xx函数时才需要此函数。
 */
void esp_aes_release_hardware( void );

/**
 * \brief初始化AES上下文
 *
 * \param ctx要初始化的AES上下文
 */
void esp_aes_init( esp_aes_context *ctx );

/**
 * \简要清除AES上下文
 *
 * \param ctx要清除的AES上下文
 */
void esp_aes_free( esp_aes_context *ctx );

/**
 * \brief此函数初始化指定的AES XTS上下文。
 *
 *                 它必须是在使用上下文之前调用的第一个API。
 *
 * \param ctx要初始化的AES XTS上下文。
 */
void esp_aes_xts_init( esp_aes_xts_context *ctx );

/**
 * \brief此函数释放并清除指定的AESXTS上下文。
 *
 * \param ctx要清除的AES XTS上下文。
 */
void esp_aes_xts_free( esp_aes_xts_context *ctx );

/**
 * \简要AES设置密钥计划（加密或解密）
 *
 * \param ctx要初始化的AES上下文\param密钥加密密钥\param keybits必须是128、192或256
 *
 * \如果成功，则返回0，或ERR_AES_INVALID_KEY_LENGTH
 */
int esp_aes_setkey( esp_aes_context *ctx, const unsigned char *key, unsigned int keybits );

/**
 * \简要AES-ECB块加密/解密
 *
 * \param ctx AES上下文\param模式AES_ENCRYPT或AES_DECRYPT \param输入16字节输入块\param输出16字节输出块
 *
 * \如果成功，则返回0
 */
int esp_aes_crypt_ecb( esp_aes_context *ctx, int mode, const unsigned char input[16], unsigned char output[16] );

/**
 * \简短的AES-CBC缓冲区加密/解密长度应为块大小（16字节）的倍数
 *
 * \注意：退出后，IV的内容将被更新，以便您可以再次对以下数据块调用相同的函数，并获得与在一次调用中加密的结果相同的结果。这允许“流式”使用。另一方面，如果您需要保留IV的内容，则应手动保存或使用密码模块。
 *
 * \param ctx AES上下文\param模式AES_ENCRYPT或AES_DECRYPT \param输入数据的长度\param iv初始化向量（使用后更新）\param保存输入数据的输入缓冲区\param保持输出数据的输出缓冲区
 *
 * \如果成功，则返回0，或ERR_AES_INVALID_INPUT_LENGTH
 */
int esp_aes_crypt_cbc( esp_aes_context *ctx,
                       int mode,
                       size_t length,
                       unsigned char iv[16],
                       const unsigned char *input,
                       unsigned char *output );


/**
 * \简单的AES-CFB128缓冲区加密/解密。
 *
 * 注意：由于CFB的性质，您应该使用相同的密钥计划进行加密和解密。因此，使用aes_ENCRYPT和aes_DECRYPT的esp_aes_setkey_enc（）初始化了上下文。
 *
 * \注意：退出后，IV的内容将被更新，以便您可以再次对以下数据块调用相同的函数，并获得与在一次调用中加密的结果相同的结果。这允许“流式”使用。另一方面，如果您需要保留IV的内容，则应手动保存或使用密码模块。
 *
 * \param ctx AES上下文\param模式AES_ENCRYPT或AES_DECRYPT \param输入数据的长度\param iv中的iv_off偏移量（使用后更新）\param iv初始化矢量（使用后升级）\pram保存输入数据的输入缓冲区\param保存输出数据的输出缓冲区
 *
 * \如果成功，则返回0
 */
int esp_aes_crypt_cfb128( esp_aes_context *ctx,
                          int mode,
                          size_t length,
                          size_t *iv_off,
                          unsigned char iv[16],
                          const unsigned char *input,
                          unsigned char *output );

/**
 * \简单的AES-CFB8缓冲区加密/解密。
 *
 * 注意：由于CFB的性质，您应该使用相同的密钥计划进行加密和解密。因此，使用aes_ENCRYPT和aes_DECRYPT的esp_aes_setkey_enc（）初始化了上下文。
 *
 * \注意：退出后，IV的内容将被更新，以便您可以再次对以下数据块调用相同的函数，并获得与在一次调用中加密的结果相同的结果。这允许“流式”使用。另一方面，如果您需要保留IV的内容，则应手动保存或使用密码模块。
 *
 * \param ctx AES上下文\param模式AES_ENCRYPT或AES_DECRYPT \param输入数据的长度\param iv初始化向量（使用后更新）\param保存输入数据的输入缓冲区\param保持输出数据的输出缓冲区
 *
 * \如果成功，则返回0
 */
int esp_aes_crypt_cfb8( esp_aes_context *ctx,
                        int mode,
                        size_t length,
                        unsigned char iv[16],
                        const unsigned char *input,
                        unsigned char *output );

/**
 * \简要AES-CTR缓冲区加密/解密
 *
 * 警告：您必须记住计数器的最大使用量！
 *
 * 注意：由于CTR的性质，您应该使用相同的密钥计划进行加密和解密。因此，使用aes_ENCRYPT和aes_DECRYPT的esp_aes_setkey_enc（）初始化了上下文。
 *
 * \param ctx AES context\param length数据长度\param nc_off当前stream_block中的偏移量（用于在当前密码流中恢复）。指向的偏移指针在流的开头应为0。\param nonce_counter 128位的nonce和计数器。\param stream_block用于恢复的已保存流块。被函数覆盖。\param input输入数据流\param output输出数据流
 *
 * \如果成功，则返回0
 */
int esp_aes_crypt_ctr( esp_aes_context *ctx,
                       size_t length,
                       size_t *nc_off,
                       unsigned char nonce_counter[16],
                       unsigned char stream_block[16],
                       const unsigned char *input,
                       unsigned char *output );

/**
 * \brief此函数执行AES-OFB（输出反馈模式）加密或解密操作。
 *
 * \param ctx用于加密或解密的AES上下文。它必须初始化并绑定到密钥。\param length输入数据的长度。\param iv_off iv中的偏移量（使用后更新）。它必须指向有效的\c size_t。\param iv初始化向量（使用后更新）。它必须是一个16字节的可读写缓冲区。\param input保存输入数据的缓冲区。它必须是可读的，长度为字节。\param output保存输出数据的缓冲区。它必须是可写的，长度为字节。
 *
 * \成功时返回\c 0。
 */
int esp_aes_crypt_ofb( esp_aes_context *ctx,
                       size_t length,
                       size_t *iv_off,
                       unsigned char iv[16],
                       const unsigned char *input,
                       unsigned char *output );

/**
 * \brief此函数为加密准备XTS上下文并设置加密密钥。
 *
 * \param ctx密钥应绑定到的AES XTS上下文。\param key加密密钥。这包括与XTS密钥2连接的XTS密钥1。\param keybits以位为单位传递的\p密钥的大小。有效选项为：＜ul＞＜li＞256位（key1和key2中的每一个都是128位密钥）＜/li＞＜li＜512位（key 1和key 2中的每个都是256位密钥）
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_AES_INVALID_KEY_LENGTH。
 */
int esp_aes_xts_setkey_enc( esp_aes_xts_context *ctx,
                                const unsigned char *key,
                                unsigned int keybits );

/**
 * \brief此函数为解密准备XTS上下文并设置解密密钥。
 *
 * \param ctx密钥应绑定到的AES XTS上下文。\param key解密密钥。这包括与XTS密钥2连接的XTS密钥1。\param keybits以位为单位传递的\p密钥的大小。有效选项为：＜ul＞＜li＞256位（key1和key2中的每一个都是128位密钥）＜/li＞＜li＜512位（key 1和key 2中的每个都是256位密钥）
 *
 * \成功时返回\c 0。\失败时返回#MBEDTLS_ERROR_AES_INVALID_KEY_LENGTH。
 */
int esp_aes_xts_setkey_dec( esp_aes_xts_context *ctx,
                                const unsigned char *key,
                                unsigned int keybits );


/**
 * \简短的内部AES块加密功能（仅公开以允许覆盖它，请参阅AES_ENCRYPT_ALT）
 *
 * \param ctx AES上下文\param输入明文块\param输出输出（密文）块
 */
int esp_internal_aes_encrypt( esp_aes_context *ctx, const unsigned char input[16], unsigned char output[16] );

/**
 * \简短的内部AES块解密函数（仅公开以允许重写，请参阅AES_DECRYPT_ALT）
 *
 * \param ctx AES上下文\param输入密文块\param输出输出（明文）块
 */
int esp_internal_aes_decrypt( esp_aes_context *ctx, const unsigned char input[16], unsigned char output[16] );

/**AES-XTS缓冲区加密/解密*/
int esp_aes_crypt_xts( esp_aes_xts_context *ctx, int mode, size_t length, const unsigned char data_unit[16], const unsigned char *input, unsigned char *output );

/**已弃用，请参见esp_aes_internal_decrypt*/
void esp_aes_decrypt( esp_aes_context *ctx, const unsigned char input[16], unsigned char output[16] ) __attribute__((deprecated));

/**已弃用，请参见esp_aes_internal_encrypt*/
void esp_aes_encrypt( esp_aes_context *ctx, const unsigned char input[16], unsigned char output[16] ) __attribute__((deprecated));

#ifdef __cplusplus
}
#endif

