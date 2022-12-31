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

#ifndef _ESP_WIFI_DEFAULT_H
#define _ESP_WIFI_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 将wifi站接口连接到提供的netif
 *
 * @param esp_netif 要连接wifi站的实例
 *
 * @return
 *  -成功时ESP_OK
 *  -如果连接失败，则返回ESP_FAIL
 */
esp_err_t esp_netif_attach_wifi_station(esp_netif_t *esp_netif);

/**
 * @brief 将wifi软AP接口连接到提供的netif
 *
 * @param esp_netif 要连接wifi AP的实例
 *
 * @return
 *  -成功时ESP_OK
 *  -如果连接失败，则返回ESP_FAIL
 */
esp_err_t esp_netif_attach_wifi_ap(esp_netif_t *esp_netif);

/**
 * @brief 设置STA接口的默认wifi事件处理程序
 *
 * @return
 *  -成功时ESP_OK，失败时从ESP_event_handler_register返回错误
 */
esp_err_t esp_wifi_set_default_wifi_sta_handlers(void);

/**
 * @brief 设置AP接口的默认wifi事件处理程序
 *
 * @return
 *  -成功时ESP_OK，失败时从ESP_event_handler_register返回错误
 */
esp_err_t esp_wifi_set_default_wifi_ap_handlers(void);

/**
 * @brief 清除提供的网络接口的默认wifi事件处理程序
 *
 * @param esp_netif 对应if对象的实例
 *
 * @return
 *  -成功时ESP_OK，失败时从ESP_event_handler_register返回错误
 */
esp_err_t esp_wifi_clear_default_wifi_driver_and_handlers(void *esp_netif);

/**
 * @brief 创建默认WIFI AP。如果出现任何初始化错误，此API将中止。
 *
 * @note API使用默认的WiFi接入点配置创建esp_netif对象，将netif附加到WiFi并注册默认的WiFi处理程序。
 *
 * @return 指向esp netif实例的指针
 */
esp_netif_t* esp_netif_create_default_wifi_ap(void);

/**
 * @brief 创建默认WIFI STA。如果出现任何初始化错误，此API将中止。
 *
 * @note API使用默认的WiFi站点配置创建esp_netif对象，将netif附加到WiFi并注册默认的WiFi处理程序。
 *
 * @return 指向esp netif实例的指针
 */
esp_netif_t* esp_netif_create_default_wifi_sta(void);

/**
 * @brief 销毁使用esp_netif_create_default_WIFI_…（）API创建的默认WIFI netif。
 *
 * @param[in] esp_netif 要从WiFi分离并销毁的对象
 *
 * @note 此API注销wifi处理程序，并将创建的对象与wifi分离。（如果esp_netif为NULL，则此函数为no操作）
 */
void esp_netif_destroy_default_wifi(void *esp_netif);

/**
 * @brief 基于自定义配置创建esp_netif WiFi对象。
 *
 * @attention 此API不注册默认处理程序！
 *
 * @param[in] wifi_if wifi接口类型
 * @param[in] esp_netif_config 固有esp-nitif配置指针
 *
 * @return 指向esp netif实例的指针
 */
esp_netif_t* esp_netif_create_wifi(wifi_interface_t wifi_if, esp_netif_inherent_config_t *esp_netif_config);

/**
 * @brief 为esp网格创建默认STA和AP网络接口。
 *
 * 这两个netif几乎与默认站点和软AP相同，但禁用了DHCP客户端和服务器。请注意，DHCP客户端通常仅在设备升级为根节点时启用。
 *
 * 返回创建的接口，如果应用程序代码不需要保存接口实例以供进一步处理，则可以忽略将参数设置为NULL。
 *
 * @param[out] p_netif_sta 保存结果STA接口的指针（如果非NULL）
 * @param[out] p_netif_ap 保存结果AP接口的指针（如果非NULL）
 *
 * @return 成功时ESP_OK
 */
esp_err_t esp_netif_create_default_wifi_mesh_netifs(esp_netif_t **p_netif_sta, esp_netif_t **p_netif_ap);

#ifdef __cplusplus
}
#endif

#endif //_ESP_WIFI_DEFAULT_H

