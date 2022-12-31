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

#ifndef _ESP_NETIF_LWIP_PPP_H_
#define _ESP_NETIF_LWIP_PPP_H_

#if CONFIG_ESP_NETIF_TCPIP_LWIP

/**
 * @brief  创建新的PPP相关结构
 *
 * @param[in]     esp_netif 指针esp netif实例
 * @param[in]     stack_config TCP/IP堆栈配置结构
 *
 * @return
 *         -成功时指向ppp-netif对象的指针
 *         -否则为NULL
 */
netif_related_data_t * esp_netif_new_ppp(esp_netif_t *esp_netif, const esp_netif_netstack_config_t *esp_netif_stack_config);

/**
 * @brief  创建新的PPP相关结构
 *
 * @param[in]     esp_netif 指针esp netif实例
 *
 * @return
 *         -成功时ESP_OK
 */
esp_err_t esp_netif_start_ppp(esp_netif_t *esp_netif);

/**
 * @brief  将传入数据包输入PPP的数据路径API
 *
 * @param[in]    ppp 指向内部ppp上下文实例的指针
 * @param[in]    buffer 指向传入数据的指针
 * @param[in]    len 数据的长度
 * @param[in]    eb 此处未使用外部缓冲ptr（与输入函数原型内联）
 *
 * @return
 *         -成功时ESP_OK
 */
void esp_netif_lwip_ppp_input(void *ppp, void *buffer, size_t len, void *eb);

/**
 * @brief   销毁ppp netif对象
 *
 * @param[in]    netif_related 指向内部ppp上下文实例的指针
 */
void esp_netif_destroy_ppp(netif_related_data_t *netif_related);

/**
 * @brief  停止PPP接口
 *
 * @param[in]    netif_related 指向内部ppp上下文实例的指针
 *
 * @return
 *         -成功时ESP_OK
 */
esp_err_t esp_netif_stop_ppp(netif_related_data_t *netif_related);

/**
 * @brief  设置路由优先级配置的默认netif
 *
 * @note: 必须从lwip线程调用此函数
 *
 */
void esp_netif_ppp_set_default_netif(netif_related_data_t *netif_related);

#endif /* CONFIG_ESP_NETIF_TCPIP_LWIP */


#endif // _ESP_NETIF_LWIP_PPP_H_

