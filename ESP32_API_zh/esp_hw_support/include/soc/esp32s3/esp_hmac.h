/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * HMAC外围设备可能的efuse键
 */
typedef enum {
    HMAC_KEY0 = 0,
    HMAC_KEY1,
    HMAC_KEY2,
    HMAC_KEY3,
    HMAC_KEY4,
    HMAC_KEY5,
    HMAC_KEY_MAX
} hmac_key_id_t;

/**
 * @brief 计算给定消息的HMAC。
 *
 * 计算长度为message_len的给定消息的HMAC\chmac。SHA256用于计算（固定在ESP32S3上）。
 *
 * @note 在“上游”模式下使用HMAC外围设备。
 *
 * @param key_id 确定efuse中的6个关键块中的哪一个应用于HMAC计算。efuse中键块的相应目的字段必须设置为HMAC上游目的值。
 * @param message 要计算HMAC的消息
 * @param message_len 报文长度
 * @param [out] hmac——hmac结果；所提供指针后面的缓冲区必须为32字节长
 *
 * @return ESP_OK，如果计算成功，如果消息或hmac为空指针，或者如果key_id超出范围ESP_FAIL，如果hmac计算失败，则为ESP_ERR_INVALID_ARG
 */
esp_err_t esp_hmac_calculate(hmac_key_id_t key_id,
        const void *message,
        size_t message_len,
        uint8_t *hmac);

/**
 * @brief 如果硬件未永久禁用JTAG，则在下游模式下使用HMAC外围设备重新启用JTAG。在下游模式下，由外围设备执行的HMAC计算在内部使用，不提供给用户。
 *
 * @param key_id 确定efuse中的6个关键块中的哪一个应用于HMAC计算。efuse中键块的相应用途字段必须设置为HMAC下游用途。
 *
 * @param token 使用SHA-256和已知的专用HMAC密钥预先计算32字节0x00的HMAC值。钥匙已编程为eFuse钥匙块。键块编号作为此函数的第一个参数提供。
 *
 * @return ESP_OK，如果计算成功，如果计算的HMAC值与提供的令牌匹配，则JTAG将重新启用，否则JTAG将保持禁用状态。返回值不指示JTAG状态。如果hmac计算失败或JTAG被EFUSE_HARD_DIS_JTAG EFUSE参数永久禁用，则返回ESP_FAIL。ESP_ERR_INVALID_ARG，输入参数无效
 */
esp_err_t esp_hmac_jtag_enable(hmac_key_id_t key_id, const uint8_t *token);

/**
 *  @brief 禁用可能使用HMAC下游模式启用的JTAG。此函数仅清除通过调用esp_hmac_jtag_enable（）API生成的结果。
 *
 *  @return 在写入值为1的HMAC_SET_INVALIDATE_JTAG_REG后，ESP_OK返回ESP_OK。
 */
esp_err_t esp_hmac_jtag_disable(void);

#ifdef __cplusplus
}
#endif

