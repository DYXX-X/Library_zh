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
#ifndef _ESP_NETIF_SUPPRESS_LEGACY_WARNING_
#warning "This header is deprecated, please use new network related API in esp_netif.h"
#include "esp_netif.h"
#endif

#ifndef _TCPIP_ADAPTER_H_
#define _TCPIP_ADAPTER_H_

#include "esp_netif.h"

#include "tcpip_adapter_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief tcpip适配器旧版初始化。它仅用于设置esp netif的兼容模式，这将启用esp netif的向后兼容。
 */
void tcpip_adapter_init(void)  __attribute__ ((deprecated));

/**
 * @brief 兼容模式：将esp netif句柄转换为tcpip_adapter遗留接口枚举
 *
 * @param esp_netif
 *
 * @return 如果提供了有效或已知的esp_netif，则对应的接口，否则为TCPIP_ADAPTER_if_MAX
 */
tcpip_adapter_if_t tcpip_adapter_if_from_esp_netif(esp_netif_t *esp_netif);

/**
 * @brief 转换为esp_netif_get_ip_info
 *
 * @param tcpip_if 与esp netif的适当实例对应的接口类型
 * @param ip_info 参见esp_netif_get_ip_info
 * @return 参见esp_netif_get_ip_info
 */
esp_err_t tcpip_adapter_get_ip_info(tcpip_adapter_if_t tcpip_if, tcpip_adapter_ip_info_t *ip_info);

#if CONFIG_LWIP_IPV6
/**
 * @brief 转换为esp_netif_get_ip6_linklocal
 *
 * @param tcpip_if  与esp netif的适当实例对应的接口类型
 * @param if_ip6 参见esp_netif_get_ip6_linklocal
 * @return 参见esp_netif_get_ip6_linklocal
 */
esp_err_t tcpip_adapter_get_ip6_linklocal(tcpip_adapter_if_t tcpip_if, ip6_addr_t *if_ip6);

/**
 * @brief 转换为esp_netif_get_ip6_global
 *
 * @param tcpip_if  与esp netif的适当实例对应的接口类型
 * @param if_ip6 请参见esp_netif_get_ip6_global
 * @return 请参见esp_netif_get_ip6_global
 */
esp_err_t tcpip_adapter_get_ip6_global(tcpip_adapter_if_t tcpip_if, ip6_addr_t *if_ip6);
#endif

/**
 * @brief`Translates 至esp_netif_dhcpc_get_status
 * @param tcpip_if 与esp netif的适当实例对应的接口类型
 * @param status
 * @return 请参见esp_netif_dhcpc_get_status
 */
esp_err_t tcpip_adapter_dhcpc_get_status(tcpip_adapter_if_t tcpip_if, tcpip_adapter_dhcp_status_t *status);

/**
 * @brief 转换为esp_netif_is_netif_up
 * @param tcpip_if 与esp netif的适当实例对应的接口类型
 * @return 参见esp_netif_is_netif_up
 */
bool tcpip_adapter_is_netif_up(tcpip_adapter_if_t tcpip_if);

/**
 * @brief 转换为esp_netif_get_netif
 * @param tcpip_if 与esp netif的适当实例对应的接口类型
 * @param netif
 * @return 参见esp_netif_get_netif
 */
esp_err_t tcpip_adapter_get_netif(tcpip_adapter_if_t tcpip_if, void ** netif);

#if CONFIG_LWIP_IPV6
/**
 * @brief 转换为esp_netif_create_ip6_linklocal
 * @param tcpip_if 与esp netif的适当实例对应的接口类型
 * @return 参见esp_netif_create_ip6_linklocal
 */
esp_err_t tcpip_adapter_create_ip6_linklocal(tcpip_adapter_if_t tcpip_if);
#endif

/**
 * @brief 设置以太网默认处理程序的兼容版本
 * @note 兼容版本的wifi处理程序在一个单独的头中提供，因为它以前是从wifi_init（）中私下调用的
 * @return 成功时ESP_OK
 */
esp_err_t tcpip_adapter_set_default_eth_handlers(void);

/**
 * @brief 网络堆栈输入功能的兼容版本。转换为esp_netif_receive（）
 */
esp_err_t tcpip_adapter_eth_input(void *buffer, uint16_t len, void *eb);

/**
 * @brief 网络堆栈输入功能的兼容版本。转换为esp_netif_receive（）
 */
esp_err_t tcpip_adapter_sta_input(void *buffer, uint16_t len, void *eb);

/**
 * @brief 网络堆栈输入功能的兼容版本。转换为esp_netif_receive（）
 */
esp_err_t tcpip_adapter_ap_input(void *buffer, uint16_t len, void *eb);

/**
 * @brief 以前的tcpip_adapter API的兼容版本，用于清除默认WIFI处理程序
 * @return 成功时ESP_OK
 */
esp_err_t tcpip_adapter_clear_default_wifi_handlers(void);

/**
 * @brief 以前的tcpip_adapter API的兼容版本，用于清除默认以太网处理程序
 * @return 成功时ESP_OK
 */
esp_err_t tcpip_adapter_clear_default_eth_handlers(void);

/**
 * @brief esp_netif_dhcps_stop以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_dhcps_stop(tcpip_adapter_if_t tcpip_if);

/**
 * @brief esp_netif_dhcpc_stop以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_dhcpc_stop(tcpip_adapter_if_t tcpip_if);

/**
 * @brief esp_netif_dhcps_start以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_dhcps_start(tcpip_adapter_if_t tcpip_if);

/**
 * @brief esp_netif_dhcpc_start以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_dhcpc_start(tcpip_adapter_if_t tcpip_if);

/**
 * @brief esp_netif_dhcps_get_status以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_dhcps_get_status(tcpip_adapter_if_t tcpip_if, tcpip_adapter_dhcp_status_t *status);

/**
 * @brief esp_netif_dhcps_option以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_dhcps_option(tcpip_adapter_dhcp_option_mode_t opt_op, tcpip_adapter_dhcp_option_id_t opt_id, void *opt_val, uint32_t opt_len);

/**
 * @brief esp_netif_dhcpc_option以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_dhcpc_option(tcpip_adapter_dhcp_option_mode_t opt_op, tcpip_adapter_dhcp_option_id_t opt_id, void *opt_val, uint32_t opt_len);

/**
 * @brief esp_netif_set_ip_info以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_set_ip_info(tcpip_adapter_if_t tcpip_if, const tcpip_adapter_ip_info_t *ip_info);

/**
 * @brief esp_netif_get_dns_info以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_get_dns_info(tcpip_adapter_if_t tcpip_if, tcpip_adapter_dns_type_t type, tcpip_adapter_dns_info_t *dns);

/**
 * @brief esp_netif_set_dns_info的前tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_set_dns_info(tcpip_adapter_if_t tcpip_if, tcpip_adapter_dns_type_t type, tcpip_adapter_dns_info_t *dns);

/**
 * @brief esp_netif_get_netif_inmpl_index以前的tcpip_adapter API的兼容版本
*/
int tcpip_adapter_get_netif_index(tcpip_adapter_if_t tcpip_if);

/**
 * @brief esp_netif_get_sta_list以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_get_sta_list(const wifi_sta_list_t *wifi_sta_list, tcpip_adapter_sta_list_t *tcpip_sta_list);

/**
 * @brief esp_netif_action_start的前tcpip_adapter API的兼容版本，用于默认以太网
*/
esp_err_t tcpip_adapter_eth_start(uint8_t *mac, tcpip_adapter_ip_info_t *ip_info, void *args);

/**
 * @brief esp_netif_action_start的前tcpip_adapter API的兼容版本，适用于默认工作站
*/
esp_err_t tcpip_adapter_sta_start(uint8_t *mac, tcpip_adapter_ip_info_t *ip_info);

/**
 * @brief esp_netif_action_start的前tcpip_adapter API的兼容版本，用于默认软AP
*/
esp_err_t tcpip_adapter_ap_start(uint8_t *mac, tcpip_adapter_ip_info_t *ip_info);

/**
 * @brief esp_netif_action_stop以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_stop(tcpip_adapter_if_t tcpip_if);

/**
 * @brief esp_netif_up以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_up(tcpip_adapter_if_t tcpip_if);

/**
 * @brief esp_netif_down以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_down(tcpip_adapter_if_t tcpip_if);

/**
 * @brief esp_netif_get_old_ip_info以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_get_old_ip_info(tcpip_adapter_if_t tcpip_if, tcpip_adapter_ip_info_t *ip_info);

/**
 * @brief esp_netif_set_old_ip_info以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_set_old_ip_info(tcpip_adapter_if_t tcpip_if, const tcpip_adapter_ip_info_t *ip_info);

/**
 * @brief esp_netif_get_handle_from_netif_inmpl的前tcpip_adapter API的兼容版本
*/
esp_interface_t tcpip_adapter_get_esp_if(void *dev);

/**
 * @brief esp_netif_set_hostname以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_set_hostname(tcpip_adapter_if_t tcpip_if, const char *hostname);

/**
 * @brief esp_netif_get_hostname以前的tcpip_adapter API的兼容版本
*/
esp_err_t tcpip_adapter_get_hostname(tcpip_adapter_if_t tcpip_if, const char **hostname);

/**
 * @brief 此函数从wifi_init调用，以确保tcpip_adapter的向后兼容模式。在遗留使用的情况下，将创建ap和sta的默认实例并注册处理程序
 *
 * @return 成功时ESP_OK
 */
esp_err_t tcpip_adapter_set_default_wifi_handlers(void);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif //_TCPIP_ADAPTER_H_

