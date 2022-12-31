/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

// DO NOT USE THESE APIS IN YOUR APPLICATIONS
// 以下API供内部使用，对其他IDF组件公开，但不适用于用户的应用程序。

#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 向平台注册I2S或I2S变体驱动程序对象
 *
 * @note 此专用API用于避免应用程序出于不同目的使用相同的I2S实例。
 * @note 此功能也将帮助启用外围APB时钟。
 *
 * @param driver_obj 驱动程序对象
 * @param port_id I2S端口号
 * @return
 *      -ESP_OK：特定I2S端口空闲，并成功注册新设备对象
 *      -ESP_ERR_INVALID_ARG：参数无效，例如port_id错误
 *      -ESP_ERR_NOT_FOUND：特定I2S端口不可用
 */
esp_err_t i2s_priv_register_object(void *driver_obj, int port_id);

/**
 * @brief 从平台注销I2S或I2S变体驱动程序对象
 *
 * @note 此功能也将帮助禁用外围APB时钟。
 *
 * @param port_id I2S端口号
 * @return
 *      -ESP_OK：成功注销I2S端口（即，此函数返回后，其他用户可以使用I2S端口）
 *      -ESP_ERR_INVALID_ARG：参数无效，例如port_id错误
 *      -ESP_ERR_INVALID_STATE:特定I2S端口已可用
 */
esp_err_t i2s_priv_deregister_object(int port_id);

#ifdef __cplusplus
}
#endif

