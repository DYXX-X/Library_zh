/**
 * @file NETBIOS名称服务响应程序选项
 */

/*
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 */
#ifndef LWIP_HDR_APPS_NETBIOS_OPTS_H
#define LWIP_HDR_APPS_NETBIOS_OPTS_H

#include "lwip/opt.h"

/**
 * @defgroup netbions_opts选项
 * @ingroup 网络生物@{
 */

/** lwip设备的NetBIOS名称在NetBIOS_STRCMP（）被定义为不区分大小写的字符串比较函数之前，此名称必须大写。如果要使用netif的主机名，请使用（与LWIP_netif_hostname一起使用）：（ip_current_nnetif（）！=无效的？ip_current_nitf（）->主机名！=无效的？ip_current_nitf（）->主机名：“”：“”）
 *
 * 如果未定义，则可以在运行时调用netbions_set_name（）来更改名称。
 */
#ifdef __DOXYGEN__
#define NETBIOS_LWIP_NAME "NETBIOSLWIPDEV"
#endif

/** 响应NetBIOS名称查询默认为禁用
 */
#if !defined LWIP_NETBIOS_RESPOND_NAME_QUERY || defined __DOXYGEN__
#define LWIP_NETBIOS_RESPOND_NAME_QUERY   0
#endif

/**
 * @}
 */

#endif /* LWIP_HDR_APPS_NETBIOS_OPTS_H */

