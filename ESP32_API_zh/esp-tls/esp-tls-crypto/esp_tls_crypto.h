/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _ESP_TLS_CRYPTO_H
#define _ESP_TLS_CRYPTO_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 计算sha1 sum esp tls crypto sha1 API的抽象，计算输入中提供的数据的sha1 sum（摘要），其大小为ilen，并返回20个字符的sha1总和
 * @param[in]   input   输入阵列
 * @param[in]   ilen    输入阵列的长度
 * @param[out]  output  计算的sha1总和
 *
 * @return mbedtls堆栈：-
 *              -错误输入时的MBEDTLS_ERROR_SHA1_BAD_INPUT_DATA。
 *              -成功时为0。wolfssl堆栈：-
 *              -故障时为-1。
 *              -成功时为0。
 */
int esp_crypto_sha1(const unsigned char *input,
                    size_t ilen,
                    unsigned char output[20]);

/**
 * @brief 对src数据进行Base64编码
 *
 * @param[in]   dst   目的地缓冲区
 * @param[in]   dlen  目标缓冲区长度
 * @param[out]  olen  写入的字节数
 * @param[in]   src   要编码的src缓冲区
 * @param[in]   slen  src缓冲长度
 *
 * @return mbedtls堆栈：-
 *               -如果缓冲区大小不足，则MBEDTLS_ERROR_BASE64_BUFFER_TOO_SMALL。
 *               -如果成功，则为0。wolfssl堆栈：-
 *               -失败时<0。
 *               -如果成功，则为0。
 */
int esp_crypto_base64_encode(unsigned char *dst, size_t dlen,
                             size_t *olen, const unsigned char *src,
                             size_t slen);

#ifdef __cplusplus
}
#endif
#endif /* _ESP_TLS_CRYPTO_H */

