// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#pragma once

#include "esp_eth.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief netif胶水手柄-netif和以太网驱动程序之间的中间层
 *
 */
typedef struct esp_eth_netif_glue_t* esp_eth_netif_glue_handle_t;

/**
 * @brief 为以太网驱动程序创建netif胶水
 * @note netif胶用于将io驱动程序连接到TCP/IP netif
 *
 * @param eth_hdl 以太网驱动程序句柄
 * @return glue对象，继承esp_netif_driver_baset
 */
esp_eth_netif_glue_handle_t esp_eth_new_netif_glue(esp_eth_handle_t eth_hdl);

/**
 * @brief 删除以太网驱动程序的netif胶
 *
 * @param eth_netif_glue netif胶
 * @return -ESP_OK:成功删除netif胶水
 */
esp_err_t esp_eth_del_netif_glue(esp_eth_netif_glue_handle_t eth_netif_glue);

/**
 * @brief 注册以太网的默认IP层处理程序
 *
 * @note: 设置这些默认处理程序时，以太网句柄可能尚未正确初始化
 * @warning: 此函数已弃用，仅出于兼容性原因保留在此处。以太网默认IP层处理程序的注册现在是自动处理的。如果要一次使用多个以太网实例，请不要调用此函数。
 *
 * @param[in] esp_netif 为以太网驱动程序创建的esp网络接口句柄
 * @return
 *      -ESP_ERR_INVALID_ARG：参数无效（ESP_netif为NULL）
 *      -ESP_OK：成功设置默认IP层处理程序
 *      -其他：注册esp_event处理程序期间发生其他错误
 */
esp_err_t esp_eth_set_default_handlers(void *esp_netif)  __attribute__ ((deprecated));

/**
 * @brief 注销以太网的默认IP层处理程序
 *
 * @warning: 此函数已弃用，仅出于兼容性原因保留在此处。现在，如果未通过调用esp_eth_set_default_handlers注册，则会自动处理以太网默认IP层处理程序的注销。
 *
 * @param[in] esp_netif 为以太网驱动程序创建的esp网络接口句柄
 * @return
 *      -ESP_ERR_INVALID_ARG：参数无效（ESP_netif为NULL）
 *      -ESP_OK：成功清除默认IP层处理程序
 *      -其他：注销esp_event处理程序时发生其他错误
 */
esp_err_t esp_eth_clear_default_handlers(void *esp_netif);

#ifdef __cplusplus
}
#endif

