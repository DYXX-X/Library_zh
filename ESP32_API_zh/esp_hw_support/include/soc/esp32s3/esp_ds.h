/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include <stdbool.h>

#include "esp_hmac.h"
#include "esp_err.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP32S3_ERR_HW_CRYPTO_DS_HMAC_FAIL           ESP_ERR_HW_CRYPTO_BASE + 0x1 /*!< HMAC外围问题*/
#define ESP32S3_ERR_HW_CRYPTO_DS_INVALID_KEY         ESP_ERR_HW_CRYPTO_BASE + 0x2 /*!< 给定HMAC密钥不正确，HMAC外围问题*/
#define ESP32S3_ERR_HW_CRYPTO_DS_INVALID_DIGEST      ESP_ERR_HW_CRYPTO_BASE + 0x4 /*!< 消息摘要检查失败，结果无效*/
#define ESP32S3_ERR_HW_CRYPTO_DS_INVALID_PADDING     ESP_ERR_HW_CRYPTO_BASE + 0x5 /*!< 填充检查失败，但仍会生成结果，并且可以读取*/

#define ESP_DS_IV_LEN 16

/* 闪存中存储的参数“C”的长度*/
#define ESP_DS_C_LEN (12672 / 8)

typedef struct esp_ds_context esp_ds_context_t;

typedef enum {
    ESP_DS_RSA_1024 = (1024 / 32) - 1,
    ESP_DS_RSA_2048 = (2048 / 32) - 1,
    ESP_DS_RSA_3072 = (3072 / 32) - 1,
    ESP_DS_RSA_4096 = (4096 / 32) - 1
} esp_digital_signature_length_t;

/**
 * 加密的私钥数据。建议以这种格式存储在闪存中。
 *
 * @note 此结构必须与ROM代码中的结构匹配！本文档主要来自那里。
 */
typedef struct esp_digital_signature_data {
    /**
     * RSA LENGTH寄存器参数（RSA密钥和操作数中的字数减1）。
     *
     * 最大值127（对于RSA 4096）。
     *
     * 此值必须与加密并存储在“c”中的长度字段匹配，否则将返回无效结果。（DS外围设备将始终使用“c”中的值，而不是此值，因此攻击者无法以这种方式更改DS外围设备结果，它只会在软件中截断或扩展消息和生成的签名。）
     *
     * @note 在IDF中，枚举类型长度与unsigned类型长度相同，因此可以互换使用。有关struct\c ets_ds_ds_data_t的原始声明，请参阅ROM代码。
     */
    esp_digital_signature_length_t rsa_length;

    /**
     * 用于加密“c”的IV值
     */
    uint8_t iv[ESP_DS_IV_LEN];

    /**
     * 加密数字签名参数。明文值的AES-CBC加密结果。包括加密邮件摘要。
     */
    uint8_t c[ESP_DS_C_LEN];
} esp_ds_data_t;

/** 数字签名使用的明文参数。
 *
 * 不用于与DS外设进行签名，但可以通过调用esp_DS_encrypt_params（）在设备中进行加密
 *
 * @note 本文档主要取自ROM代码。
 */
typedef struct {
    uint32_t Y[SOC_RSA_MAX_BIT_LEN / 32];   //!< RSA指数
    uint32_t M[SOC_RSA_MAX_BIT_LEN / 32];   //!< RSA模数
    uint32_t Rb[SOC_RSA_MAX_BIT_LEN / 32];  //!< RSA r反操作数
    uint32_t M_prime;                                //!< RSA M素数操作数
    esp_digital_signature_length_t length;           //!< RSA长度
} esp_ds_p_data_t;

/**
 * 在邮件上签名。
 *
 * 此函数是\c esp_ds_finish_sign（）和\c esp_ds_start_sign）的包装器，因此不要并行使用它们。它将阻塞，直到签名完成，然后返回签名。
 *
 * @note 此函数在整个执行期间锁定HMAC、SHA、AES和RSA组件。
 *
 * @param message 要签名的消息；其长度由data->rsa_length决定
 * @param data 加密的签名密钥数据（AES加密的RSA密钥+IV）
 * @param key_id HMAC密钥ID确定将用于解密签名密钥数据的HMAC的HMAC密钥
 * @param signature 签名的目的地应为（data->rsa\ulength+1）*4字节长
 *
 * @return
 *      -如果成功，则将签名写入参数签名。
 *      -如果其中一个参数为NULL或data->rsa\ulength过长或为0，则返回ESP_ERR_INVALID_ARG
 *      -如果在检索解密密钥期间存在HMAC故障，则ESP_ERR_HW_CRYPTO_DS_HMAC_FAIL
 *      -如果没有足够的内存来分配上下文对象，则返回ESP_ERR_NO_MEM
 *      -如果将HMAC密钥传递到DS组件时出现问题，则ESP_ERR_HW_CRYPTO_DS_INVALID_KEY
 *      -如果消息摘要不匹配，则为ESP_ERR_HW_CRYPTO_DS_INVALID_DIGEST；签名无效。
 *      -如果消息填充不正确，则可以读取签名，因为消息摘要匹配。
 */
esp_err_t esp_ds_sign(const void *message,
                      const esp_ds_data_t *data,
                      hmac_key_id_t key_id,
                      void *signature);

/**
 * 启动签名过程。
 *
 * 此函数生成一个上下文对象，该对象需要传递给\c esp_ds_finish_sign（）以完成签名过程。
 *
 * @note 此函数锁定HMAC、SHA、AES和RSA组件，因此用户必须确保及时调用\c esp_ds_finish_sign（）。
 *
 * @param message 要签名的消息；其长度由data->rsa_length决定
 * @param data 加密的签名密钥数据（AES加密的RSA密钥+IV）
 * @param key_id HMAC密钥ID确定将用于解密签名密钥数据的HMAC的HMAC密钥
 * @param esp_ds_ctx 稍后完成签名过程所需的上下文对象
 *
 * @return
 *      -ESP_OK如果成功，则ds操作现在开始，必须使用\c ESP_ds_finish_sign（）完成
 *      -如果其中一个参数为NULL或data->rsa\ulength过长或为0，则返回ESP_ERR_INVALID_ARG
 *      -如果在检索解密密钥期间存在HMAC故障，则ESP_ERR_HW_CRYPTO_DS_HMAC_FAIL
 *      -如果没有足够的内存来分配上下文对象，则返回ESP_ERR_NO_MEM
 *      -如果将HMAC密钥传递到DS组件时出现问题，则ESP_ERR_HW_CRYPTO_DS_INVALID_KEY
 */
esp_err_t esp_ds_start_sign(const void *message,
                            const esp_ds_data_t *data,
                            hmac_key_id_t key_id,
                            esp_ds_context_t **esp_ds_ctx);

/**
 * 如果DS外设忙，则返回true，否则返回false。
 *
 * @note 仅当之前调用了\c esp_ds_start_sign（）时有效。
 */
bool esp_ds_is_busy(void);

/**
 * 完成签名过程。
 *
 * @param signature 签名的目的地应为（data->rsa\ulength+1）*4字节长
 * @param esp_ds_ctx 由\c esp_ds_start_sign（）检索的上下文对象
 *
 * @return
 *      -如果成功，则ESP_OK表示ds操作已完成，结果将写入签名。
 *      -如果其中一个参数为NULL，则为ESP_ERR_INVALID_ARG
 *      -如果消息摘要不匹配，则为ESP_ERR_HW_CRYPTO_DS_INVALID_DIGEST；签名无效。
 *      -如果消息填充不正确，则可以读取签名，因为消息摘要匹配。
 */
esp_err_t esp_ds_finish_sign(void *signature, esp_ds_context_t *esp_ds_ctx);

/**
 * 加密私钥参数。
 *
 * @param data 用于存储加密数据的输出缓冲区，适用于以后生成签名。分配的内存必须在内部内存中，并且字对齐，因为它由DMA填充。两者都在运行时断言。
 * @param iv 指向16字节IV缓冲区的指针将复制到“数据”中。每次应随机生成字节。
 * @param p_data 指向输入明文密钥数据的指针。期望在完成此过程并存储“数据”后删除此数据。
 * @param key 指向32字节密钥数据的指针。由key_Type参数确定的类型。预期相应的HMAC密钥将存储到efuse，然后永久擦除。
 *
 * @return
 *      -如果成功，则ESP_OK表示ds操作已完成，结果将写入签名。
 *      -如果参数之一为NULL或p_data->rsa\ulength过长，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t esp_ds_encrypt_params(esp_ds_data_t *data,
                                const void *iv,
                                const esp_ds_p_data_t *p_data,
                                const void *key);

#ifdef __cplusplus
}
#endif

