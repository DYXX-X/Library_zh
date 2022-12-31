/**
 * @file 接口标识API来自：RFC 3493:IPv6的基本套接字接口扩展第4节：接口标识
 */

/*
 * 版权所有（c）2017 Joel Cunningham，Garmin International，Inc<joel.cunningham@garmin.com>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：乔尔·坎宁安<joel.cunningham@me.com>
 *
 */
#ifndef LWIP_HDR_IF_H
#define LWIP_HDR_IF_H

#include "lwip/opt.h"

#if LWIP_SOCKET /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IF_NAMESIZE NETIF_NAMESIZE

char * lwip_if_indextoname(unsigned int ifindex, char *ifname);
unsigned int lwip_if_nametoindex(const char *ifname);

#if LWIP_COMPAT_SOCKETS
#define if_indextoname(ifindex, ifname)  lwip_if_indextoname(ifindex,ifname)
#define if_nametoindex(ifname)           lwip_if_nametoindex(ifname)
#endif /* LWIP_COMPAT_SOCKETS */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_SOCKET */

#endif /* LWIP_HDR_IF_H */

