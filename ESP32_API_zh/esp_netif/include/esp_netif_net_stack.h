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

#ifndef _ESP_NETIF_NET_STACK_H_
#define _ESP_NETIF_NET_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

//
// 网络堆栈API：该ESP-NETIF API只能从TCP/IP堆栈内部调用
//

/** @addtogroup ESP_NETIF_CONVERT @{
 */

/**
 * @brief 返回esp netif句柄
 *
 * @param[in] dev 特定TCP/IP堆栈的不透明ptr到网络接口
 *
 * @return    相关esp-netif实例的句柄
 */
esp_netif_t* esp_netif_get_handle_from_netif_impl(void *dev);

/**
 * @brief 返回网络堆栈特定的实现句柄（如果支持）
 *
 * 注意，不支持获取PPP netif impl指针，对于配置为PPP模式的esp_netif实例，此函数将返回NULL
 *
 * @param[in]  esp_netif esp netif实例的句柄
 *
 * @return    相关网络堆栈的句柄netif句柄
 */
void* esp_netif_get_netif_impl(esp_netif_t *esp_netif);

/**
 * @}
 */

/** @addtogroup ESP_NETIF_DATA_IO_API @{
 */

/**
  * @brief  将TCP/IP堆栈中的数据包输出到要传输的媒体
  *
  * 从网络堆栈调用此函数以将数据包输出到IO驱动程序。
  *
  * @param[in]  esp_netif esp netif实例的句柄
  * @param[in]  data 待传输数据
  * @param[in]  len 数据帧的长度
  *
  * @return   成功时ESP_OK，否则从I/O驱动程序传递错误
  */
esp_err_t esp_netif_transmit(esp_netif_t *esp_netif, void* data, size_t len);

/**
  * @brief  将TCP/IP堆栈中的数据包输出到要传输的媒体
  *
  * 从网络堆栈调用此函数以将数据包输出到IO驱动程序。
  *
  * @param[in]  esp_netif esp netif实例的句柄
  * @param[in]  data 待传输数据
  * @param[in]  len 数据帧的长度
  * @param[in]  netstack_buf 网络堆栈缓冲区
  *
  * @return   成功时ESP_OK，否则从I/O驱动程序传递错误
  */
esp_err_t esp_netif_transmit_wrap(esp_netif_t *esp_netif, void *data, size_t len, void *netstack_buf);

/**
  * @brief  释放媒体驱动程序分配的rx缓冲区
  *
  * 当在IO驱动程序上下文中释放rx缓冲区时，即释放IO驱动程序拥有的缓冲区时（当数据包被传递到更高级别以避免复制时），从网络堆栈调用此函数
  *
  * @param[in]  esp_netif esp netif实例的句柄
  * @param[in]  buffer Rx缓冲指针
  */
void esp_netif_free_rx_buffer(void *esp_netif, void* buffer);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif //_ESP_NETIF_NET_STACK_H_

