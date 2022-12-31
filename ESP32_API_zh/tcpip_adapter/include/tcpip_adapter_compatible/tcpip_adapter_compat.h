// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#ifndef _TCPIP_ADAPTER_COMPAT_H_
#define _TCPIP_ADAPTER_COMPAT_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 从以太网驱动程序初始化代码调用此函数，以便于以向后兼容的tcpip_adapter方式自动启动驱动程序
 *
 * @note 这个api是在一个单独的头中提供的，它只包含在内部（来自wifi驱动程序），而不是用户初始化代码。
 *
 * @param[in] h 以太网驱动程序的句柄
 *
 * @return 成功时ESP_OK
 */
esp_err_t tcpip_adapter_compat_start_eth(void* h);

/**
 * @brief 此函数从wifi_init调用，以确保tcpip_adapter的向后兼容模式。在遗留使用的情况下，将创建ap和sta的默认实例并注册处理程序
 *
 * @note 这个API是在一个单独的头中提供的，它只包含在内部（来自wifi_init），而不是用户初始化代码。同时，该API也是前tcqpip_adapter的公共API，因此也在tcpip_adapter.h中提供
 *
 * @return 成功时ESP_OK
 */
esp_err_t tcpip_adapter_set_default_wifi_handlers(void);

/**
 * @brief 此函数从wifi_init调用，以确保tcpip_adapter的向后兼容模式。在遗留使用的情况下，ap和sta的默认实例将被销毁，处理程序将被注销
 *
 * @note 这个API是在一个单独的头中提供的，它只包含在内部（来自wifi_init），而不是用户初始化代码。同时，该API也是前tcqpip_adapter的公共API，因此也在tcpip_adapter.h中提供
 *
 * @return 成功时ESP_OK
 */
esp_err_t tcpip_adapter_clear_default_wifi_handlers(void);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif //_TCPIP_ADAPTER_COMPAT_H_

