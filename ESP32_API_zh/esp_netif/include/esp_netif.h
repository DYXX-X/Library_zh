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

#ifndef _ESP_NETIF_H_
#define _ESP_NETIF_H_

#include <stdint.h>
#include "sdkconfig.h"
#include "esp_wifi_types.h"
#include "esp_netif_ip_addr.h"
#include "esp_netif_types.h"
#include "esp_netif_defaults.h"

#if CONFIG_ETH_ENABLED
#include "esp_eth_netif_glue.h"
#endif

//
// 注意：默认情况下必须包含tcpip_adapter旧版API以提供完全兼容性
//  对于使用tcpip_adapter API但未显式包含tcpip_aapter.h的应用程序
//
#if CONFIG_ESP_NETIF_TCPIP_ADAPTER_COMPATIBLE_LAYER
#define _ESP_NETIF_SUPPRESS_LEGACY_WARNING_
#include "tcpip_adapter.h"
#undef _ESP_NETIF_SUPPRESS_LEGACY_WARNING_
#endif // CONFIG_ESP_NETIF_TCPIP_ADAPTER_COMPATIBLE_LAYER

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup ESP_NETIFINIT_API ESP-NETIF初始化API
 * @brief 底层TCP/IP堆栈和esp netif实例的初始化和去初始化
 *
 */

/** @addtogroup ESP_NETIF_INIT_API @{
 */

/**
 * @brief  初始化基础TCP/IP堆栈
 *
 * @return
 *         -成功时ESP_OK
 *         -如果初始化失败，则返回ESP_FAIL

 * @note 当应用程序启动时，应该从应用程序代码中调用该函数一次。
 */
esp_err_t esp_netif_init(void);

/**
 * @brief  取消初始化esp-nitif组件（和底层TCP/IP堆栈）
 *
 *          注意：尚不支持取消初始化
 *
 * @return
 *         -如果ESP_netif未初始化，则为ESP_ERR_INVALID_STATE
 *         -否则为ESP_ERR_NOT_SUPPORTED
 */
esp_err_t esp_netif_deinit(void);

/**
 * @brief   根据提供的配置创建新esp-netif对象的实例
 *
 * @param[in]     esp_netif_config 指针esp netif配置
 *
 * @return
 *         -成功时指向esp-nitf对象的指针
 *         -否则为NULL
 */
esp_netif_t *esp_netif_new(const esp_netif_config_t *esp_netif_config);

/**
 * @brief   销毁esp_netif对象
 *
 * @param[in]  esp_netif 指向要删除对象的指针
 */
void esp_netif_destroy(esp_netif_t *esp_netif);

/**
 * @brief   配置esp_netif对象的驱动程序相关选项
 *
 * @param[inout]  esp_netif 指向要配置的对象的指针
 * @param[in]     driver_config 指针esp netif io驱动程序相关配置
 * @return
 *         -成功时ESP_OK
 *         -如果提供的参数无效，则为ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *
 */
esp_err_t esp_netif_set_driver_config(esp_netif_t *esp_netif,
                                      const esp_netif_driver_ifconfig_t *driver_config);

/**
 * @brief   将esp_netif实例附加到io驱动程序句柄
 *
 * 调用此函数可以将特定的esp_netif对象与已初始化的io驱动程序连接起来，以使用驱动程序特定的配置更新esp_neti对象（即调用post_attach回调，通常将io驱动程序回调设置为esp_netiv实例并启动驱动程序）
 *
 * @param[inout]  esp_netif 指向要附加的esp_netif对象的指针
 * @param[in]  driver_handle 指向驱动器手柄的指针
 * @return
 *         -成功时ESP_OK
 *         -如果驱动程序的pot_ATTACH回调失败，则ESP_ERR_ESP_NETIF_DRIVER_ATTACH_FAILED
 */
esp_err_t esp_netif_attach(esp_netif_t *esp_netif, esp_netif_iodriver_handle driver_handle);

/**
 * @}
 */

/**
 * @defgroup ESP_NETIF_DATA_IO_API ESP-NETIF输入输出API
 * @brief 输入和输出功能用于将数据包从通信介质（IO驱动程序）传递到TCP/IP堆栈。
 *
 * 这些函数通常不会直接从用户代码中调用，而是在IO驱动程序或TCP/IP堆栈中安装或注册为回调。更具体地说，esp_netif_receive通常在接收回调时从io驱动程序调用，以将数据包输入到TCP/IP堆栈。类似地，每当包应该输出到通信媒体时，从TCP/IP堆栈调用esp_netif_transmit。
 *
 * @note 这些IO功能会自动注册（安装）默认接口（具有WIFI_STA_DEF、WIFI_AP_DEF、ETH_DEF等键的接口）。使用@ref esp_netif_new创建接口时，自定义接口必须注册这些IO函数
 *
 */

/** @addtogroup ESP_NETIF_DATA_IO_API @{
 */

/**
 * @brief  将原始数据包从通信介质传递到适当的TCP/IP堆栈
 *
 * 此函数从配置的（外围）驱动程序层调用。然后将数据作为帧转发到TCP/IP堆栈。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  buffer 收到的数据
 * @param[in]  len 数据帧的长度
 * @param[in]  eb 指向内部缓冲区的指针（用于Wi-Fi驱动程序）
 *
 * @return
 *         - ESP_OK
 */
esp_err_t esp_netif_receive(esp_netif_t *esp_netif, void *buffer, size_t len, void *eb);

/**
 * @}
 */

/**
 * @defgroup ESP_NETIF_LIFECYCLE ESP-NETIF生命周期控制
 * @brief 这些APIS定义了控制网络接口生命周期的基本构建块，即启动、停止、set_up或set_down。这些函数可以直接用作注册的事件处理程序，以跟踪来自通信媒体的事件。
 */

/** @addtogroup ESP_NETIF_LIFECYCLE @{
 */

/**
 * @brief IO驱动程序启动事件时网络接口操作的默认构建块创建网络接口，如果启用了AUTOUP，则打开接口，如果已启用DHCPS，则启动dhcp服务器
 *
 * @note 此API可以直接用作事件处理程序
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param base
 * @param event_id
 * @param data
 */
void esp_netif_action_start(void *esp_netif, esp_event_base_t base, int32_t event_id, void *data);

/**
 * @brief IO驱动程序停止事件时网络接口操作的默认构建块
 *
 * @note 此API可以直接用作事件处理程序
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param base
 * @param event_id
 * @param data
 */
void esp_netif_action_stop(void *esp_netif, esp_event_base_t base, int32_t event_id, void *data);

/**
 * @brief IO驱动程序连接事件时网络接口操作的默认构建块
 *
 * @note 此API可以直接用作事件处理程序
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param base
 * @param event_id
 * @param data
 */
void esp_netif_action_connected(void *esp_netif, esp_event_base_t base, int32_t event_id, void *data);

/**
 * @brief IO驱动程序断开连接事件时网络接口操作的默认构建块
 *
 * @note 此API可以直接用作事件处理程序
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param base
 * @param event_id
 * @param data
 */
void esp_netif_action_disconnected(void *esp_netif, esp_event_base_t base, int32_t event_id, void *data);

/**
 * @brief 网络获取IP事件时网络接口操作的默认构造块
 *
 * @note 此API可以直接用作事件处理程序
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param base
 * @param event_id
 * @param data
 */
void esp_netif_action_got_ip(void *esp_netif, esp_event_base_t base, int32_t event_id, void *data);

/**
 * @brief IPv6多播组加入时网络接口操作的默认构建块
 *
 * @note 此API可以直接用作事件处理程序
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param base
 * @param event_id
 * @param data
 */
void esp_netif_action_join_ip6_multicast_group(void *esp_netif, esp_event_base_t base, int32_t event_id, void *data);

/**
 * @brief IPv6多播组离开时网络接口操作的默认构建块
 *
 * @note 此API可以直接用作事件处理程序
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param base
 * @param event_id
 * @param data
 */
void esp_netif_action_leave_ip6_multicast_group(void *esp_netif, esp_event_base_t base, int32_t event_id, void *data);

/**
 * @brief 基础堆栈添加IPv6地址时网络接口操作的默认构建块
 *
 * @note 此API可以直接用作事件处理程序
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param base
 * @param event_id
 * @param data
 */
void esp_netif_action_add_ip6_address(void *esp_netif, esp_event_base_t base, int32_t event_id, void *data);

/**
 * @brief 基础堆栈删除IPv6地址时网络接口操作的默认构造块
 *
 * @note 此API可以直接用作事件处理程序
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param base
 * @param event_id
 * @param data
 */
void esp_netif_action_remove_ip6_address(void *esp_netif, esp_event_base_t base, int32_t event_id, void *data);

/**
 * @}
 */

/**
 * @defgroup ESP_NETIF_GET_SET ESP-NETIF运行时配置
 * @brief 各种TCP/IP相关参数的获取器和设置器
 */

/** @addtogroup ESP_NETIF_GET_SET @{
 */

/**
 * @brief 设置接口实例的mac地址

 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  mac 相关网络接口所需的mac地址
 * @return
 *         -ESP_OK-成功
 *         -ESP_ERR_ESP_NETIF_IF_NOT_READY—接口状态错误
 *         -ESP_ERR_NOT_SUPPORTED-此接口不支持mac
 */
esp_err_t esp_netif_set_mac(esp_netif_t *esp_netif, uint8_t mac[]);

/**
 * @brief 获取接口实例的mac地址

 * @param[in]  esp_netif esp netif实例的句柄
 * @param[out]  mac 相关网络接口的最终mac地址
 * @return
 *         -ESP_OK-成功
 *         -ESP_ERR_ESP_NETIF_IF_NOT_READY—接口状态错误
 *         -ESP_ERR_NOT_SUPPORTED-此接口不支持mac
 */
esp_err_t esp_netif_get_mac(esp_netif_t *esp_netif, uint8_t mac[]);

/**
 * @brief  设置接口的主机名
 *
 * 配置的主机名覆盖默认配置值CONFIG_LWIP_LOCAL_hostname。请注意，当在接口启动/连接后更改主机名时，只有在接口重新启动/重新连接后，更改才会反映出来
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]   hostname 接口的新主机名。最大长度32字节。
 *
 * @return
 *         -ESP_OK-成功
 *         -ESP_ERR_ESP_NETIF_IF_NOT_READY—接口状态错误
 *         -ESP_ERR_ESP_NETIF_INVALID_PARAMS-参数错误
 */
esp_err_t esp_netif_set_hostname(esp_netif_t *esp_netif, const char *hostname);

/**
 * @brief  获取接口主机名。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[out]   hostname 返回指向主机名的指针。如果未设置主机名，则可能为NULL。如果设置为非NULL，指针将保持有效（如果主机名更改，字符串可能会更改）。
 *
 * @return
 *         -ESP_OK-成功
 *         -ESP_ERR_ESP_NETIF_IF_NOT_READY—接口状态错误
 *         -ESP_ERR_ESP_NETIF_INVALID_PARAMS-参数错误
 */
esp_err_t esp_netif_get_hostname(esp_netif_t *esp_netif, const char **hostname);

/**
 * @brief  测试提供的接口是向上还是向下
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return
 *         -true-接口已启动
 *         -false-接口关闭
 */
bool esp_netif_is_netif_up(esp_netif_t *esp_netif);

/**
 * @brief  获取接口的IP地址信息
 *
 * 如果接口启动，则直接从TCP/IP堆栈读取IP信息。如果接口关闭，则从ESP-NETIF实例中保存的副本中读取IP信息
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[out]  ip_info 如果成功，IP信息将在此参数中返回。
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 */
esp_err_t esp_netif_get_ip_info(esp_netif_t *esp_netif, esp_netif_ip_info_t *ip_info);

/**
 * @brief  获取接口的旧IP信息
 *
 * 当有效IP更改时，返回以前为接口存储的“旧”IP地址。
 *
 * 如果IP丢失计时器已过期（意味着接口关闭的时间长于配置的时间间隔），则旧IP信息将为零。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[out]  ip_info 如果成功，IP信息将在此参数中返回。
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 */
esp_err_t esp_netif_get_old_ip_info(esp_netif_t *esp_netif, esp_netif_ip_info_t *ip_info);

/**
 * @brief  设置接口的IP地址信息
 *
 * 此功能主要用于在接口上设置静态IP。
 *
 * 如果接口已启动，则直接在TCP/IP堆栈中设置新的IP信息。
 *
 * 保存在ESP-NETIF实例中的IP信息副本也会更新（如果在接口仍然关闭时查询IP，则返回此副本）
 *
 * @note 在设置新的IP信息之前，必须停止DHCP客户端/服务器（如果为此接口启用）。
 *
 * @note 为调用此接口可能会生成SYSTEM_EVENT_STA_GOT_IP或SYSTEM_EVERT_ETH_GOT_IP事件。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in] ip_info 要在指定接口上设置的IP信息
 *
 * @return
 *      - ESP_OK
 *      - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *      -ESP_ERR_ESP_NETIF_DHCP_NOT_STOPPED如果DHCP服务器或客户端仍在运行
 */
esp_err_t esp_netif_set_ip_info(esp_netif_t *esp_netif, const esp_netif_ip_info_t *ip_info);

/**
 * @brief  设置接口旧IP信息
 *
 * 在设置新IP之前，从DHCP客户端（如果启用）调用此函数。它也从SYSTEM_EVENT_STA_CONNECTED和SYSTEM_EVENT_ETH_CONNECTED事件的默认处理程序调用。
 *
 * 调用此函数将存储先前配置的IP，该IP可用于确定将来IP是否更改。
 *
 * 如果接口断开或关闭时间过长，“IP丢失计时器”将过期（在配置的间隔之后），并将旧IP信息设置为零。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  ip_info 存储指定接口的旧IP信息
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 */
esp_err_t esp_netif_set_old_ip_info(esp_netif_t *esp_netif, const esp_netif_ip_info_t *ip_info);

/**
 * @brief  从网络堆栈实现中获取网络接口索引
 *
 * @note 此索引可以在“setsockopt（）”中用于将套接字绑定到多播接口
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return 用提供的espnetif表示的接口的特定实现索引
 */
int esp_netif_get_netif_impl_index(esp_netif_t *esp_netif);

/**
 * @brief  从网络堆栈实现中获取网络接口名称
 *
 * @note 此名称可以在“setsockopt（）”中使用，以将套接字绑定到适当的接口
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[out]  name 基础TCP/IP堆栈中指定的接口名称。请注意，实际名称将复制到指定的缓冲区，必须分配缓冲区以容纳最大接口名称大小（lwIP为6个字符）
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
*/
esp_err_t esp_netif_get_netif_impl_name(esp_netif_t *esp_netif, char* name);

/**
 * @}
 */

/**
 * @defgroup ESP_NETIF_NET_DHCP ESP-NETIF DHCP设置
 * @brief DHCP客户端和服务器的网络堆栈相关接口
 */

/** @addtogroup ESP_NETIF_NET_DHCP @{
 */

/**
 * @brief  设置或获取DHCP服务器选项
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in] opt_op ESP_NETIF_OP_SET设置选项，ESP_NETF_OP_GET获取选项。
 * @param[in] opt_id 要获取或设置的选项索引必须是受支持的枚举值之一。
 * @param[inout] opt_val 指向选项参数的指针。
 * @param[in] opt_len 选项参数的长度。
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *         - ESP_ERR_ESP_NETIF_DHCP_ALREADY_STOPPED
 *         - ESP_ERR_ESP_NETIF_DHCP_ALREADY_STARTED
 */
esp_err_t
esp_netif_dhcps_option(esp_netif_t *esp_netif, esp_netif_dhcp_option_mode_t opt_op, esp_netif_dhcp_option_id_t opt_id,
                       void *opt_val, uint32_t opt_len);

/**
 * @brief  设置或获取DHCP客户端选项
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in] opt_op ESP_NETIF_OP_SET设置选项，ESP_NETF_OP_GET获取选项。
 * @param[in] opt_id 要获取或设置的选项索引必须是受支持的枚举值之一。
 * @param[inout] opt_val 指向选项参数的指针。
 * @param[in] opt_len 选项参数的长度。
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *         - ESP_ERR_ESP_NETIF_DHCP_ALREADY_STOPPED
 *         - ESP_ERR_ESP_NETIF_DHCP_ALREADY_STARTED
 */
esp_err_t
esp_netif_dhcpc_option(esp_netif_t *esp_netif, esp_netif_dhcp_option_mode_t opt_op, esp_netif_dhcp_option_id_t opt_id,
                       void *opt_val, uint32_t opt_len);

/**
 * @brief 启动DHCP客户端（仅当在接口对象中启用时）
 *
 * @note SYSTEM_event_STA_CONNECTED和SYSTEM_EVERT_ETH_CONNECTED事件的默认事件处理程序调用此函数。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *         - ESP_ERR_ESP_NETIF_DHCP_ALREADY_STARTED
 *         - ESP_ERR_ESP_NETIF_DHCPC_START_FAILED
 */
esp_err_t esp_netif_dhcpc_start(esp_netif_t *esp_netif);

/**
 * @brief  停止DHCP客户端（仅当在接口对象中启用时）
 *
 * @note 如果DHCP客户端正在运行，则调用action_netif_stop（）也将停止该客户端。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return
 *      - ESP_OK
 *      - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *      - ESP_ERR_ESP_NETIF_DHCP_ALREADY_STOPPED
 *      - ESP_ERR_ESP_NETIF_IF_NOT_READY
 */
esp_err_t esp_netif_dhcpc_stop(esp_netif_t *esp_netif);

/**
 * @brief  获取DHCP客户端状态
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[out] status 如果成功，DHCP客户端的状态将在此参数中返回。
 *
 * @return
 *         - ESP_OK
 */
esp_err_t esp_netif_dhcpc_get_status(esp_netif_t *esp_netif, esp_netif_dhcp_status_t *status);

/**
 * @brief  获取DHCP服务器状态
 *
 * @param[in]   esp_netif esp netif实例的句柄
 * @param[out]  status 如果成功，DHCP服务器的状态将在此参数中返回。
 *
 * @return
 *         - ESP_OK
 */
esp_err_t esp_netif_dhcps_get_status(esp_netif_t *esp_netif, esp_netif_dhcp_status_t *status);

/**
 * @brief  启动DHCP服务器（仅当在接口对象中启用时）
 *
 * @param[in]   esp_netif esp netif实例的句柄
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *         - ESP_ERR_ESP_NETIF_DHCP_ALREADY_STARTED
 */
esp_err_t esp_netif_dhcps_start(esp_netif_t *esp_netif);

/**
 * @brief  停止DHCP服务器（仅当在接口对象中启用时）
 *
 * @param[in]   esp_netif esp netif实例的句柄
 *
 * @return
 *      - ESP_OK
 *      - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 *      - ESP_ERR_ESP_NETIF_DHCP_ALREADY_STOPPED
 *      - ESP_ERR_ESP_NETIF_IF_NOT_READY
 */
esp_err_t esp_netif_dhcps_stop(esp_netif_t *esp_netif);

/**
 * @}
 */

/**
 * @defgroup ESP_NETIF_NET_DNS ESP-NETIF DNS设置
 * @brief 与NDS相关的网络堆栈接口
 */

/** @addtogroup ESP_NETIF_NET_DNS @{
 */

/**
 * @brief  设置DNS服务器信息
 *
 * 如果启用DHCP服务器或客户端，则此函数的行为不同
 *
 *   如果启用了DHCP客户端，则如果设置了相关的DHCP选项，则将从DHCP租约自动更新主DNS服务器和备份DNS服务器。回退DNS服务器从未从DHCP租约中更新，并且设计为通过此API设置。如果禁用DHCP客户端，则只能通过此API设置所有DNS服务器类型。
 *
 *   如果启用了DHCP服务器，DHCP服务器将使用主DNS服务器设置为DHCP客户端（Wi-Fi站点）提供DNS服务器选项。
 *   -默认的主DNS服务器通常是Wi-Fi AP接口本身的IP。
 *   -此函数可以通过设置服务器类型ESP_NETIF_DNS_MAIN来覆盖它。
 *   -Wi-Fi AP接口不支持其他DNS服务器类型。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  type 要设置的DNS服务器类型：ESP_NETIF_DNS_MAIN、ESP_NETIF_DNS_BBACKUP、ESP_NOTIF_DNS_FALLBACK
 * @param[in]  dns  要设置的DNS服务器地址
 *
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_ESP_NETIF_INVALID_PARAMS无效参数
 */
esp_err_t esp_netif_set_dns_info(esp_netif_t *esp_netif, esp_netif_dns_type_t type, esp_netif_dns_info_t *dns);

/**
 * @brief  获取DNS服务器信息
 *
 * 返回指定接口和服务器类型的当前配置的DNS服务器地址。
 *
 * 这可能是先前调用esp_netif_set_dns_info（）的结果。如果接口的DHCP客户端已启用，则可以通过当前DHCP租约设置主DNS服务器或备份DNS服务器。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[in]  type 要获取的DNS服务器类型：ESP_NETIF_DNS_MAIN、ESP_NETIF_DNS_BBACKUP、ESP_NOTIF_DNS_FALLBACK
 * @param[out] dns  DNS服务器结果在成功时写入此处
 *
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_ESP_NETIF_INVALID_PARAMS无效参数
 */
esp_err_t esp_netif_get_dns_info(esp_netif_t *esp_netif, esp_netif_dns_type_t type, esp_netif_dns_info_t *dns);

/**
 * @}
 */

/**
 * @defgroup ESP_NETIF_NETI_IP ESP-NETIF IP地址相关接口
 * @brief 与网络堆栈相关的IP接口
 */

/** @addtogroup ESP_NETIF_NET_IP @{
 */
#if CONFIG_LWIP_IPV6
/**
 * @brief  创建接口链接本地IPv6地址
 *
 * 使TCP/IP堆栈为指定接口创建链接本地IPv6地址。
 *
 * 此函数还为指定接口注册回调，以便如果链接本地地址被验证为首选地址，则将发送SYSTEM_EVENT_GOT_IP6事件。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 */
esp_err_t esp_netif_create_ip6_linklocal(esp_netif_t *esp_netif);

/**
 * @brief  获取接口链接本地IPv6地址
 *
 * 如果指定的接口已启动，并且已为该接口创建了首选链接本地IPv6地址，请返回该地址的副本。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[out] if_ip6 如果成功，将在此参数中返回IPv6信息。
 *
 * @return
 *      - ESP_OK
 *      -ESP_FAIL如果接口关闭，没有链路本地IPv6地址，或者链路本地IPv6不是首选地址。
 */
esp_err_t esp_netif_get_ip6_linklocal(esp_netif_t *esp_netif, esp_ip6_addr_t *if_ip6);

/**
 * @brief  获取接口全局IPv6地址
 *
 * 如果指定的接口已启动，并且已为该接口创建了首选全局IPv6地址，请返回该地址的副本。
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[out] if_ip6 如果成功，将在此参数中返回IPv6信息。
 *
 * @return
 *      - ESP_OK
 *      -ESP_FAIL如果接口关闭，没有全局IPv6地址，或者全局IPv6地址不是首选地址。
 */
esp_err_t esp_netif_get_ip6_global(esp_netif_t *esp_netif, esp_ip6_addr_t *if_ip6);

/**
 * @brief  获取指定接口的所有IPv6地址
 *
 * @param[in]  esp_netif esp netif实例的句柄
 * @param[out] if_ip6 IPv6地址数组将复制到参数
 *
 * @return 返回的IPv6地址数
 */
int esp_netif_get_all_ip6(esp_netif_t *esp_netif, esp_ip6_addr_t if_ip6[]);
#endif

/**
 * @brief 将IPv4地址设置为指定的八位字节
 *
 * @param[out] addr 要设置的IP地址
 * @param a 第一个八位字节（127代表IP 127.0.0.1）
 * @param b
 * @param c
 * @param d
 */
void esp_netif_set_ip4_addr(esp_ip4_addr_t *addr, uint8_t a, uint8_t b, uint8_t c, uint8_t d);


/**
 * @brief 将数字IP地址转换为十进制虚线ASCII表示。
 *
 * @param addr 要转换的网络顺序中的ip地址
 * @param buf 存储字符串的目标缓冲区
 * @param buflen buf长度
 * @return 指向buf（现在保存addr的ASCII表示）的指针，如果buf太小，则返回NULL
 */
char *esp_ip4addr_ntoa(const esp_ip4_addr_t *addr, char *buf, int buflen);

/**
 * @brief Ascii互联网地址解释例程返回的值按网络顺序排列。
 *
 * @param addr ascii表示的IP地址（例如“127.0.0.1”）
 * @return 网络顺序中的ip地址
*/
uint32_t esp_ip4addr_aton(const char *addr);

/**
 * @brief 将Ascii internet IPv4地址转换为esp_ip4_addr_t
 *
 * @param[in] src ascii表示的IPv4地址（例如“127.0.0.1”）
 * @param[out] dst 要接收转换地址的目标esp_ip4_addr_t结构的地址
 * @return
 *         -成功时ESP_OK
 *         -如果转换失败，则返回ESP_FAIL
 *         -如果传入无效参数，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t esp_netif_str_to_ip4(const char *src, esp_ip4_addr_t *dst);

/**
 * @brief 将Ascii internet IPv6地址转换为esp_ip4_addr_t IP地址中的零可以被剥离或完全放弃：“2001:db8:85a3:0:0:2:1”或“2001:db8:：2:1”）
 *
 * @param[in] src ascii表示的IPv6地址（例如“2001:0db8:85a3:0000:0000:0002:0001”）
 * @param[out] dst 要接收转换地址的目标esp_ip6_addr_t结构的地址
 * @return
 *         -成功时ESP_OK
 *         -如果转换失败，则返回ESP_FAIL
 *         -如果传入无效参数，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t esp_netif_str_to_ip6(const char *src, esp_ip6_addr_t *dst);

/**
 * @}
 */

/**
 * @defgroup ESP_NETIF_COVERT ESP-NETIF转换实用程序
 * @brief  ESP-NETIF转换实用程序到相关键、标志、实现句柄
 */

/** @addtogroup ESP_NETIF_CONVERT @{
 */

/**
 * @brief 获取此esp netif实例的媒体驱动程序句柄
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return 相关IO驱动程序的不透明指针
 */
esp_netif_iodriver_handle esp_netif_get_io_driver(esp_netif_t *esp_netif);

/**
 * @brief 搜索已创建对象的列表以查找具有提供的if键的实例
 *
 * @param if_key 网络接口的文本描述
 *
 * @return esp netif实例的句柄
 */
esp_netif_t *esp_netif_get_handle_from_ifkey(const char *if_key);

/**
 * @brief 返回此接口的配置标志
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return 配置标志
 */
esp_netif_flags_t esp_netif_get_flags(esp_netif_t *esp_netif);

/**
 * @brief 返回此esp netif实例的配置接口密钥
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return 相关接口的文本描述
 */
const char *esp_netif_get_ifkey(esp_netif_t *esp_netif);

/**
 * @brief 返回此esp netif实例的配置接口类型
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return 此接口的枚举类型，如站、AP、以太网
 */
const char *esp_netif_get_desc(esp_netif_t *esp_netif);

/**
 * @brief 返回配置的路由优先级编号
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return 表示实例的路由优先级的整数，如果参数无效，则为-1
 */
int esp_netif_get_route_prio(esp_netif_t *esp_netif);

/**
 * @brief 返回此esp netif实例的配置事件和提供的事件类型
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @param event_type （获取或丢失IP）
 *
 * @return 配置为在接口丢失或获取IP地址时引发的特定事件id
 *         -如果提供的event_type未知，则为1
 */
int32_t esp_netif_get_event_id(esp_netif_t *esp_netif, esp_netif_ip_event_type_t event_type);

/**
 * @}
 */

/**
 * @defgroup ESP_NETIF_LIST ESP-NETIF接口列表
 * @brief  用于枚举所有已注册接口的API
 */

/** @addtogroup ESP_NETIF_LIST @{
 */

/**
 * @brief 遍历接口列表。如果参数为NULL，则返回第一个netif
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return 如果提供的参数为NULL，则列表中的第一个netif，否则下一个netif
 */
esp_netif_t *esp_netif_next(esp_netif_t *esp_netif);

/**
 * @brief 返回已注册的esp_netif对象数
 *
 * @return esp_netifs数
 */
size_t esp_netif_get_nr_of_ifs(void);

/**
 * @brief 增加网络堆栈缓冲区的引用计数器
 *
 * @param[in]  netstack_buf 网络堆栈缓冲区
 *
 */
void esp_netif_netstack_buf_ref(void *netstack_buf);

/**
 * @brief 释放netstack缓冲区
 *
 * @param[in]  netstack_buf 网络堆栈缓冲区
 *
 */
void esp_netif_netstack_buf_free(void *netstack_buf);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*  _ESP_NETIF_H_ */

