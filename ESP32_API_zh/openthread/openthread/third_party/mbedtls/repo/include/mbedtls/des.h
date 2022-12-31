/**
 * \文件des.h
 *
 * \简短DES分组密码
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 */
#ifndef MBEDTLS_DES_H
#define MBEDTLS_DES_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#define MBEDTLS_DES_ENCRYPT     1
#define MBEDTLS_DES_DECRYPT     0

#define MBEDTLS_ERR_DES_INVALID_INPUT_LENGTH              -0x0032  /**<数据输入的长度无效。*/

/* MBEDTLS_ERROR_DES_HW_ACCEL_FAILED已弃用，不应使用。*/
#define MBEDTLS_ERR_DES_HW_ACCEL_FAILED                   -0x0033  /**<DES硬件加速器失败。*/

#define MBEDTLS_DES_KEY_SIZE    8

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_DES_ALT)
// 定期实施
//

/**
 * \简要DES上下文结构
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
typedef struct mbedtls_des_context
{
    uint32_t sk[32];            /*!<  DES子密钥*/
}
mbedtls_des_context;

/**
 * \简短的三重DES上下文结构
 */
typedef struct mbedtls_des3_context
{
    uint32_t sk[96];            /*!<  3DES子键*/
}
mbedtls_des3_context;

#else  /* MBEDTLS_DES_ALT */
#include "des_alt.h"
#endif /* MBEDTLS_DES_ALT */

/**
 * \brief初始化DES上下文
 *
 * \param ctx要初始化的DES上下文
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
void mbedtls_des_init( mbedtls_des_context *ctx );

/**
 * \简要清除DES上下文
 *
 * \param ctx要清除的DES上下文
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
void mbedtls_des_free( mbedtls_des_context *ctx );

/**
 * \brief初始化三重DES上下文
 *
 * \param ctx DES3上下文要初始化
 */
void mbedtls_des3_init( mbedtls_des3_context *ctx );

/**
 * \简短的清除三重DES上下文
 *
 * \要清除的param ctx DES3上下文
 */
void mbedtls_des3_free( mbedtls_des3_context *ctx );

/**
 * \brief将给定密钥上的密钥奇偶性设置为奇数。
 *
 *                 DES密钥长56位，但每个字节都填充了一个奇偶校验位，以允许验证。
 *
 * \param键8字节密钥
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
void mbedtls_des_key_set_parity( unsigned char key[MBEDTLS_DES_KEY_SIZE] );

/**
 * \简要检查给定密钥上的密钥奇偶校验是否为奇数。
 *
 *                 DES密钥长56位，但每个字节都填充了一个奇偶校验位，以允许验证。
 *
 * \param键8字节密钥
 *
 * \如果奇偶校验正确，返回0；如果奇偶校验不正确，返回1。
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
int mbedtls_des_key_check_key_parity( const unsigned char key[MBEDTLS_DES_KEY_SIZE] );

/**
 * \简要检查密钥是否不是弱或半弱DES密钥
 *
 * \param键8字节密钥
 *
 * \如果未找到弱密钥，则返回0；如果识别出弱密钥，返回1。
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
int mbedtls_des_key_check_weak( const unsigned char key[MBEDTLS_DES_KEY_SIZE] );

/**
 * \简短的DES密钥计划（56位，加密）
 *
 * \param ctx要初始化的DES上下文\param key 8字节密钥
 *
 * \返回0
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
int mbedtls_des_setkey_enc( mbedtls_des_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE] );

/**
 * \简短的DES密钥调度（56位，解密）
 *
 * \param ctx要初始化的DES上下文\param key 8字节密钥
 *
 * \返回0
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
int mbedtls_des_setkey_dec( mbedtls_des_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE] );

/**
 * \简短的三重DES密钥计划（112位，加密）
 *
 * \param ctx要初始化的3DES上下文\param key 16字节密钥
 *
 * \返回0
 */
int mbedtls_des3_set2key_enc( mbedtls_des3_context *ctx,
                      const unsigned char key[MBEDTLS_DES_KEY_SIZE * 2] );

/**
 * \简短的三重DES密钥调度（112位，解密）
 *
 * \param ctx要初始化的3DES上下文\param key 16字节密钥
 *
 * \返回0
 */
int mbedtls_des3_set2key_dec( mbedtls_des3_context *ctx,
                      const unsigned char key[MBEDTLS_DES_KEY_SIZE * 2] );

/**
 * \简短的三重DES密钥计划（168位，加密）
 *
 * \param ctx要初始化的3DES上下文\param key 24字节密钥
 *
 * \返回0
 */
int mbedtls_des3_set3key_enc( mbedtls_des3_context *ctx,
                      const unsigned char key[MBEDTLS_DES_KEY_SIZE * 3] );

/**
 * \简短的三重DES密钥调度（168位，解密）
 *
 * \param ctx要初始化的3DES上下文\param key 24字节密钥
 *
 * \返回0
 */
int mbedtls_des3_set3key_dec( mbedtls_des3_context *ctx,
                      const unsigned char key[MBEDTLS_DES_KEY_SIZE * 3] );

/**
 * \简要DES-ECB块加密/解密
 *
 * \param ctx DES上下文\param输入64位输入块\param输出64位输出块
 *
 * \如果成功，则返回0
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
int mbedtls_des_crypt_ecb( mbedtls_des_context *ctx,
                    const unsigned char input[8],
                    unsigned char output[8] );

#if defined(MBEDTLS_CIPHER_MODE_CBC)
/**
 * \简要DES-CBC缓冲区加密/解密
 *
 * \注意：退出后，IV的内容将被更新，以便您可以再次对以下数据块调用相同的函数，并获得与在一次调用中加密的结果相同的结果。这允许“流式”使用。另一方面，如果您需要保留IV的内容，则应手动保存或使用密码模块。
 *
 * \param ctx DES上下文\param mode MBEDTLS_DES_ENCRYPT或MBEDTLS_DES_DECRYPT \param输入数据的长度\param iv初始化向量（使用后更新）\param保存输入数据的输入缓冲区\param保持输出数据的输出缓冲区
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
int mbedtls_des_crypt_cbc( mbedtls_des_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[8],
                    const unsigned char *input,
                    unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CBC */

/**
 * \简要3DES-ECB块加密/解密
 *
 * \param ctx 3DES上下文\param输入64位输入块\param输出64位输出块
 *
 * \如果成功，则返回0
 */
int mbedtls_des3_crypt_ecb( mbedtls_des3_context *ctx,
                     const unsigned char input[8],
                     unsigned char output[8] );

#if defined(MBEDTLS_CIPHER_MODE_CBC)
/**
 * \简要3DES-CBC缓冲区加密/解密
 *
 * \注意：退出后，IV的内容将被更新，以便您可以再次对以下数据块调用相同的函数，并获得与在一次调用中加密的结果相同的结果。这允许“流式”使用。另一方面，如果您需要保留IV的内容，则应手动保存或使用密码模块。
 *
 * \param ctx 3DES上下文\param mode MBEDTLS_DES_ENCRYPT或MBEDTLS_DES_DECRYPT \param输入数据的长度\param iv初始化向量（使用后更新）\param保存输入数据的输入缓冲区\param保持输出数据的输出缓冲区
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_DES_INVALID_INPUT_LENGTH
 */
int mbedtls_des3_crypt_cbc( mbedtls_des3_context *ctx,
                     int mode,
                     size_t length,
                     unsigned char iv[8],
                     const unsigned char *input,
                     unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CBC */

/**
 * \键扩展的简要内部功能。（仅公开以允许覆盖它，请参见MBEDTLS_DES_SETKEY_ALT）
 *
 * \param SK圆键\param key基本键
 *
 * \警告DES被认为是一种弱密码，其使用构成了安全风险。我们建议改用更强的密码。
 */
void mbedtls_des_setkey( uint32_t SK[32],
                         const unsigned char key[MBEDTLS_DES_KEY_SIZE] );

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_des_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* 得时*/

