// 版权所有2021浓缩咖啡系统（上海）有限公司
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
// 许可证下的限制

#ifndef _OPENTHREAD_LWIP_IF_H_
#define _OPENTHREAD_LWIP_IF_H_

#include "lwip/netif.h"
#include "lwip/err.h"
#include "lwip/ip6.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 此函数初始化OpenThread lwIP网络接口。
 *
 * @param[in] netif     要初始化的lwIP接口
 *
 * @return
 *      - ERR_OK
 *
 */
err_t openthread_netif_init(struct netif *netif);

/**
 * @brief 此函数将缓冲区发送到lwIP网络接口
 *
 * @param[in] netif     要发送到的lwIP接口。
 * @param[in] buffer    要发送的数据包。
 * @param[in] len       缓冲区的长度。
 * @param[in] eb        未使用。
 *
 */
void openthread_netif_input(void *netif, void *buffer, size_t len, void *eb);

#ifdef __cplusplus
}
#endif

#endif /* _OPENTHREAD_LWIP_IF_H_ */

