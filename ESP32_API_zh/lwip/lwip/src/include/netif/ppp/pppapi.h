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

#ifndef LWIP_PPPAPI_H
#define LWIP_PPPAPI_H

#include "netif/ppp/ppp_opts.h"

#if LWIP_PPP_API /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/sys.h"
#include "lwip/netif.h"
#include "lwip/priv/tcpip_priv.h"
#include "netif/ppp/ppp.h"
#if PPPOS_SUPPORT
#include "netif/ppp/pppos.h"
#endif /* PPPOS_SUPPORT */

#ifdef __cplusplus
extern "C" {
#endif

struct pppapi_msg_msg {
  ppp_pcb *ppp;
  union {
#if ESP_PPP && PPP_AUTH_SUPPORT
    struct {
      u8_t authtype;
      const char *user;
      const char *passwd;
    } setauth;
#endif
#if PPP_NOTIFY_PHASE
    struct {
      ppp_notify_phase_cb_fn notify_phase_cb;
    } setnotifyphasecb;
#endif /* PPP_NOTIFY_PHASE */
#if PPPOS_SUPPORT
    struct {
      struct netif *pppif;
      pppos_output_cb_fn output_cb;
      ppp_link_status_cb_fn link_status_cb;
      void *ctx_cb;
    } serialcreate;
#endif /* PPPOS_SUPPORT */
#if PPPOE_SUPPORT
    struct {
      struct netif *pppif;
      struct netif *ethif;
      const char *service_name;
      const char *concentrator_name;
      ppp_link_status_cb_fn link_status_cb;
      void *ctx_cb;
    } ethernetcreate;
#endif /* PPPOE_SUPPORT */
#if PPPOL2TP_SUPPORT
    struct {
      struct netif *pppif;
      struct netif *netif;
      API_MSG_M_DEF_C(ip_addr_t, ipaddr);
      u16_t port;
#if PPPOL2TP_AUTH_SUPPORT
      const u8_t *secret;
      u8_t secret_len;
#endif /* PPPOL2TP_AUTH_SUPPORT */
      ppp_link_status_cb_fn link_status_cb;
      void *ctx_cb;
    } l2tpcreate;
#endif /* PPPOL2TP_SUPPORT */
    struct {
      u16_t holdoff;
    } connect;
    struct {
      u8_t nocarrier;
    } close;
    struct {
      u8_t cmd;
      void *arg;
    } ioctl;
  } msg;
};

struct pppapi_msg {
  struct tcpip_api_call_data call;
  struct pppapi_msg_msg msg;
};

/* 应用程序API*/
err_t pppapi_set_default(ppp_pcb *pcb);
#if ESP_PPP && PPP_AUTH_SUPPORT
void pppapi_set_auth(ppp_pcb *pcb, u8_t authtype, const char *user, const char *passwd);
#endif
#if PPP_NOTIFY_PHASE
err_t pppapi_set_notify_phase_callback(ppp_pcb *pcb, ppp_notify_phase_cb_fn notify_phase_cb);
#endif /* PPP_NOTIFY_PHASE */
#if PPPOS_SUPPORT
ppp_pcb *pppapi_pppos_create(struct netif *pppif, pppos_output_cb_fn output_cb, ppp_link_status_cb_fn link_status_cb, void *ctx_cb);
#endif /* PPPOS_SUPPORT */
#if PPPOE_SUPPORT
ppp_pcb *pppapi_pppoe_create(struct netif *pppif, struct netif *ethif, const char *service_name,
                                const char *concentrator_name, ppp_link_status_cb_fn link_status_cb,
                                void *ctx_cb);
#endif /* PPPOE_SUPPORT */
#if PPPOL2TP_SUPPORT
ppp_pcb *pppapi_pppol2tp_create(struct netif *pppif, struct netif *netif, ip_addr_t *ipaddr, u16_t port,
                            const u8_t *secret, u8_t secret_len,
                            ppp_link_status_cb_fn link_status_cb, void *ctx_cb);
#endif /* PPPOL2TP_SUPPORT */
err_t pppapi_connect(ppp_pcb *pcb, u16_t holdoff);
#if PPP_SERVER
err_t pppapi_listen(ppp_pcb *pcb);
#endif /* PPP_SERVER */
err_t pppapi_close(ppp_pcb *pcb, u8_t nocarrier);
err_t pppapi_free(ppp_pcb *pcb);
err_t pppapi_ioctl(ppp_pcb *pcb, u8_t cmd, void *arg);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_PPP_API */

#endif /* LWIP_PPPAPI_H */

