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

#ifndef _ESP_NETIF_LWIP_SLIP_H_
#define _ESP_NETIF_LWIP_SLIP_H_

/**
 * @brief  创建新的SLIP相关结构
 *
 * @param[in]     esp_netif 指针esp netif实例
 * @param[in]     stack_config TCP/IP堆栈配置结构
 *
 * @return
 *         -成功时滑动netif对象的指针
 *         -否则为NULL
 */
netif_related_data_t * esp_netif_new_slip(esp_netif_t *esp_netif, const esp_netif_netstack_config_t *esp_netif_stack_config);

/**
 * @brief   销毁slip netif对象
 *
 * @param[in]    slip 指向内部滑动上下文实例的指针
 */
void esp_netif_destroy_slip(netif_related_data_t *slip);

/**
 * @brief 停止esp打滑开关
 *
 * @param[in]    esp_netif 滑动把手（尤指netif实例）
 *
 * @return
 *         -成功时ESP_OK
 */
esp_err_t esp_netif_stop_slip(esp_netif_t *esp_netif);

/**
 * @brief 启动esp打滑开关
 *
 * @param[in]    esp_netif 滑动把手（尤指netif实例）
 *
 * @return
 *         -成功时ESP_OK
 */
esp_err_t esp_netif_start_slip(esp_netif_t *esp_netif);


#endif // _ESP_NETIF_LWIP_SLIP_H_

