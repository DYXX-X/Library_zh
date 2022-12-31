// 版权所有2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#ifndef _ESP_PLATFORM_NET_IF_H_
#define _ESP_PLATFORM_NET_IF_H_

#include "lwip/sockets.h"
#include "lwip/if_api.h"

#define	MSG_DONTROUTE   0x4     /* 不使用路由表发送*/
#define	SOCK_SEQPACKET  5       /* 顺序分组流*/
#define	MSG_EOR         0x8     /* 数据完成记录*/
#define	SOCK_SEQPACKET  5       /* 顺序分组流*/
#define	SOMAXCONN       128

#define	IPV6_UNICAST_HOPS   4  /* int；IP6跳*/

#define	NI_MAXHOST  1025
#define	NI_MAXSERV  32
#define	NI_NUMERICSERV  0x00000008
#define	NI_DGRAM        0x00000010

typedef u32_t socklen_t;


unsigned int if_nametoindex(const char *ifname);

char *if_indextoname(unsigned int ifindex, char *ifname);

#endif // _ESP_PLATFORM_NET_IF_H_

