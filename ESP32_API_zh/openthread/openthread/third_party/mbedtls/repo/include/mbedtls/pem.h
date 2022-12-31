/**
 * \文件pem.h
 *
 * \简短的隐私增强邮件（PEM）解码
 */
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#ifndef MBEDTLS_PEM_H
#define MBEDTLS_PEM_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

/**
 * \name PEM错误代码这些错误代码在读取PEM数据时出错时返回\{
 */
#define MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT          -0x1080  /**<未找到PEM页眉或页脚。*/
#define MBEDTLS_ERR_PEM_INVALID_DATA                      -0x1100  /**<PEM字符串不符合预期。*/
#define MBEDTLS_ERR_PEM_ALLOC_FAILED                      -0x1180  /**<分配内存失败。*/
#define MBEDTLS_ERR_PEM_INVALID_ENC_IV                    -0x1200  /**<RSA IV不是十六进制格式。*/
#define MBEDTLS_ERR_PEM_UNKNOWN_ENC_ALG                   -0x1280  /**<不支持的密钥加密算法。*/
#define MBEDTLS_ERR_PEM_PASSWORD_REQUIRED                 -0x1300  /**<私钥密码不能为空。*/
#define MBEDTLS_ERR_PEM_PASSWORD_MISMATCH                 -0x1380  /**<给定的私钥密码不允许正确解密。*/
#define MBEDTLS_ERR_PEM_FEATURE_UNAVAILABLE               -0x1400  /**<不可用功能，例如哈希/加密组合。*/
#define MBEDTLS_ERR_PEM_BAD_INPUT_DATA                    -0x1480  /**<功能输入参数错误。*/
/* \}名称*/

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_PEM_PARSE_C)
/**
 * \PEM上下文结构简介
 */
typedef struct mbedtls_pem_context
{
    unsigned char *buf;     /*!< 解码数据缓冲区*/
    size_t buflen;          /*!< 缓冲区长度*/
    unsigned char *info;    /*!< 额外标题信息的缓冲区*/
}
mbedtls_pem_context;

/**
 * \简要PEM上下文设置
 *
 * \要初始化的param ctx上下文
 */
void mbedtls_pem_init( mbedtls_pem_context *ctx );

/**
 * \brief读取PEM信息的缓冲区，并将生成的数据存储到指定的上下文缓冲区中。
 *
 * \param ctx上下文将使用\param header header string查找并期望\param footer footer string查找并希望\param数据源数据查找（必须以nul结尾）\param pwd用于解密的密码（可以为NULL）\pparam pwdlen密码长度\param use_len destination用于使用的总长度（在正确读取标头后设置，因此除非获得MBEDTLS_ERROR_PEM_BAD_INPUT_DATA或MBEDTLS_ERROR_PEM_NO_header_FOUTER_PRESENT，否则use_len是要跳过的长度）
 *
 * \注意：尝试通过验证解密文本是否以适当长度的ASN.1序列开头来检查密码的正确性
 *
 * \成功时返回0，或特定PEM错误代码
 */
int mbedtls_pem_read_buffer( mbedtls_pem_context *ctx, const char *header, const char *footer,
                     const unsigned char *data,
                     const unsigned char *pwd,
                     size_t pwdlen, size_t *use_len );

/**
 * \简短的PEM上下文内存释放
 *
 * \要释放的参数ctx上下文
 */
void mbedtls_pem_free( mbedtls_pem_context *ctx );
#endif /* MBEDTLS_PEM_PARSE_C */

#if defined(MBEDTLS_PEM_WRITE_C)
/**
 * \brief从DER编码的缓冲区中写入PEM信息的缓冲区。
 *
 * \param header要写入的头字符串。\param footer要写入的页脚字符串。\param der_data要编码的der数据。\param der_len der数据的长度（字节）。\param buf要写入的缓冲区。\param buf_len输出缓冲区的长度（以字节为单位）。\param olen存储写入或需要的总长度的地址（如果\p buf_len不够）。
 *
 * \注意：您可以为\pbuf传递\c NULL，为\pbuf_len传递\c 0，以请求“olen”中生成的PEM缓冲区的长度。
 *
 * \注意：可以使用重叠的\p der_data和\p buf缓冲区调用此函数。
 *
 * \成功时返回\c 0。\如果缓冲区不够大，无法容纳PEM缓冲区，则返回#MBEDTLS_ERROR_BASE64_BUFFER_TOO_SMALL。在这种情况下，“olen”包含所需的最小大小。\返回其他类型故障的另一个PEM或BASE64错误代码。
 */
int mbedtls_pem_write_buffer( const char *header, const char *footer,
                      const unsigned char *der_data, size_t der_len,
                      unsigned char *buf, size_t buf_len, size_t *olen );
#endif /* MBEDTLS_PEM_WRITE_C */

#ifdef __cplusplus
}
#endif

#endif /* pem.小时*/

