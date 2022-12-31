// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#ifndef _ESP_RSA_SIGN_ALT_H_
#define _ESP_RSA_SIGN_ALT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_ds.h"
#include "mbedtls/md.h"

/**
 * @brief      ESP-DS数据上下文
 *
 * @note       该结构包括加密的私钥参数，如密文_c、初始化向量、efuse_key_id、RSA密钥长度，这些参数是在配置DS外设时获得的。
 */

/* DS所需加密私钥数据的上下文*/
typedef struct esp_ds_data_ctx {
    esp_ds_data_t *esp_ds_data;
    uint8_t efuse_key_id; /* efuse存储DS_KEY的块id，例如0,1*/
    uint16_t rsa_length_bits; /* 以位为单位的RSA私钥长度，例如2048*/
} esp_ds_data_ctx_t;

/**
 * @brief       初始化内部DS数据上下文
 *
 * 此函数分配并初始化用于数字签名操作的内部ds数据上下文。
 *
 * @in          ds_data包含加密私钥参数的ds_data上下文
 * @return
 *              -如果成功，ESP_OK
 *              -ESP_ERR_NO_MEM如果无法分配内部上下文。
 *              -输入参数为空时的ESP_ERR_INVALID_ARG
 *
 */
esp_err_t esp_ds_init_data_ctx(esp_ds_data_ctx_t *ds_data);

/**
 *
 * @brief      释放为ds操作获取的ds锁（然后ds外围设备可以用于其他TLS连接）
 *
 */
void esp_ds_release_ds_lock(void);

/**
 *
 * @brief       mbedtls_rsa_rsasa_pkcs1_v15_sign的替代实现，内部使用DS模块执行硬件加速的rsa签名操作
 */
int esp_ds_rsa_sign( void *ctx,
                     int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
                     int mode, mbedtls_md_type_t md_alg, unsigned int hashlen,
                     const unsigned char *hash, unsigned char *sig );

/*
 * @brief       从内部DS上下文中获取RSA密钥长度（字节）
 *
 * @return      RSA密钥长度（字节）
 */
size_t esp_ds_get_keylen(void *ctx);

/*
 * @brief       设置超时（等于TLS会话超时），以便在使用DS模块的多个TLS连接的情况下可以同步DS模块的使用，
 */
void esp_ds_set_session_timeout(int timeout);
#ifdef __cplusplus
}
#endif

#endif /* _ESP_RSA_SIGN_ALT_H_ */

