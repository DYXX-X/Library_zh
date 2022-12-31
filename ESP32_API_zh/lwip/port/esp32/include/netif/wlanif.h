// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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


#ifndef _WLAN_LWIP_IF_H_
#define _WLAN_LWIP_IF_H_

#include "esp_wifi.h"

#include "lwip/err.h"

#ifdef __cplusplus
extern "C" {
#endif

err_t wlanif_init_ap(struct netif *netif);
err_t wlanif_init_sta(struct netif *netif);

void wlanif_input(void *netif, void *buffer, size_t len, void* eb);
err_t wlanif_init(struct netif *netif);

wifi_interface_t wifi_get_interface(void *dev);

void netif_reg_addr_change_cb(void* cb);

#ifdef __cplusplus
}
#endif

#endif /*  _WLAN_LWIP_IF_H_ */

