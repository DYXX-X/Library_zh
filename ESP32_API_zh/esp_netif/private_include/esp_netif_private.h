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

#ifndef _ESP_NETIF_PRIVATE_H_
#define _ESP_NETIF_PRIVATE_H_

#define ESP_NETIF_CALL_CHECK(info, api_call, ret) \
do{\
    esp_err_t __err = (api_call);\
    if ((ret) != __err) {\
        ESP_LOGE(TAG, "%s %d %s ret=0x%X", __FUNCTION__, __LINE__, (info), __err);\
        return;\
    }\
} while(0)

/**
 * @brief  使TCP/IP堆栈启动ESP-NETIF实例接口
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *         - ESP_ERR_NO_MEM
 */
esp_err_t esp_netif_start(esp_netif_t *esp_netif);

/**
 * @brief  使TCP/IP堆栈停止定义为ESP-NETIF实例的网络接口
 *
 * 使TCP/IP堆栈清理此接口。这包括停止DHCP服务器或客户端（如果已启动）。
 *
 * @note 要停止应用程序代码中的接口，应调用特定于媒体驱动程序的API（esp_wifi_stop（）或esp_eth_stop（）），然后驱动程序层将发送停止事件，事件处理程序应调用此API。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *         - ESP_ERR_ESP_NETIF_IF_NOT_READY
 */
esp_err_t esp_netif_stop(esp_netif_t *esp_netif);

/**
 * @brief  使TCP/IP堆栈打开一个接口。默认情况下，从事件处理程序/操作中自动调用此函数
 *
 * @note 此功能通常不用于Wi-Fi AP接口。如果AP接口已启动，则它已启动。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_IF_NOT_READY
 */
esp_err_t esp_netif_up(esp_netif_t *esp_netif);

/**
 * @brief 导致TCP/IP堆栈关闭接口此函数默认情况下自动从事件处理程序/操作调用
 *
 * @note 此功能通常不用于Wi-Fi AP接口。如果AP接口停止，则表示它已关闭。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return
 *         - ESP_OK
 *         -ESP_ERR_ESP_NETIF_INVALID_PARAMS-参数错误
 */
esp_err_t esp_netif_down(esp_netif_t *esp_netif);

/**
 * @brief 如果基础TCP/IP堆栈将IP_info作为有效的静态地址，则返回true
 *
 * @param[in] ip_info
 * @return 如果地址假定为有效的静态IP地址，则为true
 */
bool esp_netif_is_valid_static_ip(esp_netif_ip_info_t *ip_info);

/**
 * @brief 将创建的接口添加到netifs列表
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return
 *         -ESP_OK—成功
 *         -ESP_ERR_NO_MEM—由于内存分配失败，无法添加
 */
esp_err_t esp_netif_add_to_list(esp_netif_t* netif);

/**
 * @brief 从netifs列表中删除要销毁的接口
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return
 *         -ESP_OK—成功
 *         -ESP_ERR_NOT_FOUND--在netif列表中找不到此netif
 */
esp_err_t esp_netif_remove_from_list(esp_netif_t* netif);

/**
 * @brief 在没有列表锁定的情况下遍历接口列表。如果参数为NULL，则返回第一个netif
 *
 * 用于批量搜索循环，以避免每次迭代都锁定和解锁。esp_netif_list_lock和esp_netifslist_unlock必须用于保护搜索循环
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return 如果提供的参数为NULL，则列表中的第一个netif，否则下一个netif
 */
esp_netif_t* esp_netif_next_unsafe(esp_netif_t* netif);

/**
 * @brief 锁定网络接口列表。仅与esp_netif_next_safe一起使用
 *
 * @return 成功时ESP_OK，锁定失败时出现特定互斥错误
 */
esp_err_t esp_netif_list_lock(void);

/**
 * @brief 正在解锁网络接口列表。仅与esp_netif_next_safe一起使用
 *
 */
void esp_netif_list_unlock(void);

/**
 * @brief 遍历注册接口列表，检查是否列出了提供的netif
 *
 * @param esp_netif 要检查的网络接口
 *
 * @return 如果列出了提供的接口，则为true
 */
bool esp_netif_is_netif_listed(esp_netif_t *esp_netif);

/**
 * @brief  使TCP/IP堆栈加入多播组
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  addr      要加入的多播组
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *         - ESP_ERR_ESP_NETIF_MLD6_FAILED
 *         - ESP_ERR_NO_MEM
 */
esp_err_t esp_netif_join_ip6_multicast_group(esp_netif_t *esp_netif, const esp_ip6_addr_t *addr);

/**
 * @brief  使TCP/IP堆栈离开多播组
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  addr      要离开的多播组
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *         - ESP_ERR_ESP_NETIF_MLD6_FAILED
 *         - ESP_ERR_NO_MEM
 */
esp_err_t esp_netif_leave_ip6_multicast_group(esp_netif_t *esp_netif, const esp_ip6_addr_t *addr);

/**
 * @brief  使TCP/IP堆栈向接口添加IPv6地址
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  addr      要添加的地址
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *         - ESP_ERR_ESP_NETIF_IP6_ADDR_FAILED
 *         - ESP_ERR_NO_MEM
 */
esp_err_t esp_netif_add_ip6_address(esp_netif_t *esp_netif, const ip_event_add_ip6_t *addr);

/**
 * @brief  使TCP/IP堆栈从接口中删除IPv6地址
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  addr      要删除的地址
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *         - ESP_ERR_ESP_NETIF_IP6_ADDR_FAILED
 *         - ESP_ERR_NO_MEM
 */
esp_err_t esp_netif_remove_ip6_address(esp_netif_t *esp_netif, const esp_ip6_addr_t *addr);

#endif //_ESP_NETIF_PRIVATE_H_

