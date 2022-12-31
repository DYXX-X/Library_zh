// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#ifndef _ESP_WIFI_NETIF_H
#define _ESP_WIFI_NETIF_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief WiFi netif抽象使用的WiFi接口数量
 */
#define MAX_WIFI_IFS (2)

/**
 * @brief WiFi接口句柄的转发声明
 */
typedef struct wifi_netif_driver* wifi_netif_driver_t;

/**
 * @brief 创建要与esp netif一起使用的wifi驱动程序实例
 *
 * @param wifi_if wifi接口类型（站、软AP）
 *
 * @return
 *  -成功时指向wifi接口句柄的指针
 *  -否则为NULL
 */
wifi_netif_driver_t esp_wifi_create_if_driver(wifi_interface_t wifi_if);

/**
 * @brief 销毁wifi驱动程序实例
 *
 * @param h 指向wifi接口句柄的指针
 *
 */
void esp_wifi_destroy_if_driver(wifi_netif_driver_t h);

/**
 * @brief 返回指定wifi驱动程序实例的mac
 *
 * @param[in] ifx 指向wifi接口句柄的指针
 * @param[out] mac 输出mac地址
 *
 * @return 成功时ESP_OK
 *
 */
esp_err_t esp_wifi_get_if_mac(wifi_netif_driver_t ifx, uint8_t mac[6]);

/**
 * @brief 如果提供的接口实例在启动后准备就绪，则返回true。通常在注册接收回调时使用，该回调应在AP启动时安装，但一旦STA连接。
 *
 * @param[in] ifx 指向wifi接口句柄的指针
 *
 * @return
 *      -如果在空间间启动后准备就绪（通常为接入点类型），则为true
 *      -如果空间间连接就绪，则为false（通常用于工作站类型）
 */
bool esp_wifi_is_if_ready_when_started(wifi_netif_driver_t ifx);

/**
 * @brief 使用参数注册接口接收回调函数
 *
 * @param[in] ifx 指向wifi接口句柄的指针
 * @param[in] fn  要注册的功能（通常为esp_netif_receive）
 * @param[in] arg 要提供给注册函数的参数（通常为esp_netif ptr）
 *
 * @return 成功时ESP_OK
 *
 */
esp_err_t esp_wifi_register_if_rxcb(wifi_netif_driver_t ifx, esp_netif_receive_t fn, void * arg);

#ifdef __cplusplus
}
#endif

#endif //_ESP_WIFI_NETIF_H

