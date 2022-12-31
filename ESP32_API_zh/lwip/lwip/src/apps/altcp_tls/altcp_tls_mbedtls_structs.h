/**
 * @file 应用程序分层TCP/TLS连接API（从TCPIP线程使用）
 *
 * 此文件包含使用mbedTLS的TLS层的结构定义。
 */

/*
 * 版权所有（c）2017 Simon Goldschmidt保留所有权利。
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
#ifndef LWIP_HDR_ALTCP_MBEDTLS_STRUCTS_H
#define LWIP_HDR_ALTCP_MBEDTLS_STRUCTS_H

#include "lwip/opt.h"

#if LWIP_ALTCP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/apps/altcp_tls_mbedtls_opts.h"

#if LWIP_ALTCP_TLS && LWIP_ALTCP_TLS_MBEDTLS

#include "lwip/altcp.h"
#include "lwip/pbuf.h"

#include "mbedtls/ssl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ALTCP_MBEDTLS_FLAGS_HANDSHAKE_DONE    0x01
#define ALTCP_MBEDTLS_FLAGS_UPPER_CALLED      0x02
#define ALTCP_MBEDTLS_FLAGS_RX_CLOSE_QUEUED   0x04
#define ALTCP_MBEDTLS_FLAGS_RX_CLOSED         0x08
#define ALTCP_MBEDTLS_FLAGS_APPLDATA_SENT     0x10

typedef struct altcp_mbedtls_state_s {
  void *conf;
  mbedtls_ssl_context ssl_context;
  /* rx-pbufs链（解密前）*/
  struct pbuf *rx;
  struct pbuf *rx_app;
  u8_t flags;
  int rx_passed_unrecved;
  int bio_bytes_read;
  int bio_bytes_appl;
} altcp_mbedtls_state_t;

#ifdef __cplusplus
}
#endif

#endif /* LWIP_ALTCP_TLS && LWIP_ALTCP_TLS_MBEDTLS */
#endif /* LWIP_ALTCP */
#endif /* LWIP_HDR_ALTCP_MBEDTLS_STRUCTS_H */

