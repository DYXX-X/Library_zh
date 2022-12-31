// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
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

#ifndef _ESP_TRANSPORT_TCP_H_
#define _ESP_TRANSPORT_TCP_H_

#include "esp_transport.h"
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      设置TCP保持活动配置
 *
 * @param[in]  t               运输手柄
 * @param[in]  keep_alive_cfg  keep-alive配置
 *
 */
void esp_transport_tcp_set_keep_alive(esp_transport_handle_t t, esp_transport_keep_alive_t *keep_alive_cfg);

/**
 * @brief      设置套接字可以绑定的接口的名称，以便数据可以在此接口上传输
 *
 * @param[in]  t        运输手柄
 * @param[in]  if_name  接口名称
 */
void esp_transport_tcp_set_interface_name(esp_transport_handle_t t, struct ifreq *if_name);

/**
 * @brief      创建TCP传输，传输句柄必须是release esp_transport_destroy回调
 *
 * @return  分配的esp_transport_handle_t，如果无法分配句柄，则为NULL
 */
esp_transport_handle_t esp_transport_tcp_init(void);


#ifdef __cplusplus
}
#endif

#endif /* _ESP_TRANSPORT_TCP_H_ */

