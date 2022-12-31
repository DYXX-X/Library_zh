/**
 * @file 执行代理连接的应用程序分层TCP连接API。
 *
 * 该文件提供了一个执行代理连接的起始层，例如通过http代理建立TLS连接。
 */

/*
 * 版权所有（c）2018 Simon Goldschmidt保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Simon Goldschmidt<goldsimon@gmx.de>
 *
 */

#ifndef LWIP_HDR_APPS_ALTCP_PROXYCONNECT_H
#define LWIP_HDR_APPS_ALTCP_PROXYCONNECT_H

#include "lwip/opt.h"

#if LWIP_ALTCP /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#include "lwip/ip_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

struct altcp_proxyconnect_config {
  ip_addr_t proxy_addr;
  u16_t proxy_port;
};


struct altcp_pcb *altcp_proxyconnect_new(struct altcp_proxyconnect_config *config, struct altcp_pcb *inner_pcb);
struct altcp_pcb *altcp_proxyconnect_new_tcp(struct altcp_proxyconnect_config *config, u8_t ip_type);

struct altcp_pcb *altcp_proxyconnect_alloc(void *arg, u8_t ip_type);

#if LWIP_ALTCP_TLS
struct altcp_proxyconnect_tls_config {
  struct altcp_proxyconnect_config proxy;
  struct altcp_tls_config *tls_config;
};

struct altcp_pcb *altcp_proxyconnect_tls_alloc(void *arg, u8_t ip_type);
#endif /* LWIP_ALTCP_TLS */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_ALTCP */
#endif /* LWIP_HDR_APPS_ALTCP_PROXYCONNECT_H */

