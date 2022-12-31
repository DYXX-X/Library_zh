/**
 * @file
 *
 * SLIP netif API
 */

/*
 * 版权所有（c）2001，瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用研究所的名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */
#ifndef LWIP_HDR_NETIF_SLIPIF_H
#define LWIP_HDR_NETIF_SLIPIF_H

#include "lwip/opt.h"
#include "lwip/netif.h"

/** 将此值设置为1以启动一个线程，该线程阻止串行线上的读取（使用sio_read（））。
 */
#ifndef SLIP_USE_RX_THREAD
#define SLIP_USE_RX_THREAD !NO_SYS
#endif

/** 将此值设置为1，以使函数能够从ISR上下文传入RX字节。如果启用，slipif_received_byte[s]（）将处理传入的字节，并将组装好的数据包放入队列，该队列将从slipif_poll（）馈送到lwIP。如果禁用，slipif_poll（）将轮询串行线（使用sio_tryread（））。
 */
#ifndef SLIP_RX_FROM_ISR
#define SLIP_RX_FROM_ISR 0
#endif

/** 将此值设置为1（SLIP_RX_FROM_ISR的默认值），以便在PBUF_POOL pbufs可用的情况下，对slipif_received_byte[s]（）接收的传入数据包进行排队。如果禁用，如果接收到多个数据包，数据包将被丢弃。
 */
#ifndef SLIP_RX_QUEUE
#define SLIP_RX_QUEUE SLIP_RX_FROM_ISR
#endif

#ifdef __cplusplus
extern "C" {
#endif

err_t slipif_init(struct netif * netif);
void slipif_poll(struct netif *netif);
#if SLIP_RX_FROM_ISR
void slipif_process_rxqueue(struct netif *netif);
void slipif_received_byte(struct netif *netif, u8_t data);
void slipif_received_bytes(struct netif *netif, u8_t *data, u8_t len);
#endif /* SLIP_RX_FROM_ISR */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_NETIF_SLIPIF_H */


