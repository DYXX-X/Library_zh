/**
 * @file MDNS响应程序
 */

 /*
 * 版权所有（c）2015 Verisure Innovation AB保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Erik Ekman<erik@kryo.se>
 *
 */

#ifndef LWIP_HDR_APPS_MDNS_H
#define LWIP_HDR_APPS_MDNS_H

#include "lwip/apps/mdns_opts.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_MDNS_RESPONDER

enum mdns_sd_proto {
  DNSSD_PROTO_UDP = 0,
  DNSSD_PROTO_TCP = 1
};

#define MDNS_PROBING_CONFLICT   0
#define MDNS_PROBING_SUCCESSFUL 1

#define MDNS_LABEL_MAXLEN  63

struct mdns_host;
struct mdns_service;

/**回调函数，用于向回复添加文本，在生成回复时调用*/
typedef void (*service_get_txt_fn_t)(struct mdns_service *service, void *txt_userdata);

/**回调函数，用于让应用程序知道探测网络名称唯一性的结果，如果没有其他节点声明使用netif或服务的名称并且可以安全使用，则调用结果MDNS_probing_SUCCESSFUL；如果其他节点已经在使用它并且在此接口上禁用了MDNS，则调用MDNS_probing_CONFLICT*/
typedef void (*mdns_name_result_cb_t)(struct netif* netif, u8_t result);

void mdns_resp_init(void);

void mdns_resp_register_name_result_cb(mdns_name_result_cb_t cb);

err_t mdns_resp_add_netif(struct netif *netif, const char *hostname, u32_t dns_ttl);
err_t mdns_resp_remove_netif(struct netif *netif);
err_t mdns_resp_rename_netif(struct netif *netif, const char *hostname);

s8_t  mdns_resp_add_service(struct netif *netif, const char *name, const char *service, enum mdns_sd_proto proto, u16_t port, u32_t dns_ttl, service_get_txt_fn_t txt_fn, void *txt_userdata);
err_t mdns_resp_del_service(struct netif *netif, s8_t slot);
err_t mdns_resp_rename_service(struct netif *netif, s8_t slot, const char *name);

err_t mdns_resp_add_service_txtitem(struct mdns_service *service, const char *txt, u8_t txt_len);

void mdns_resp_restart(struct netif *netif);
void mdns_resp_announce(struct netif *netif);

/**
 * @ingroup mdns宣布netif上的IP设置已更改。在netif_set_status_callback（）注册的回调中调用此函数。当LWIP_NETIF_EXT_STATUS_CALLBACK==1时，无需调用此函数，这将自动为您处理。
 * @param netif 设置已更改的网络接口。
 */
#define mdns_resp_netif_settings_changed(netif) mdns_resp_announce(netif)

#endif /* LWIP_MDNS_RESPONDER */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_MDNS_H */

