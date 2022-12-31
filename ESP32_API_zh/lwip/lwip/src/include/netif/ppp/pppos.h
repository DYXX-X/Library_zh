/**
 * @file 串行头文件上的网络点对点协议。
 *
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

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && PPPOS_SUPPORT /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#ifndef PPPOS_H
#define PPPOS_H

#include "lwip/sys.h"

#include "ppp.h"
#include "vj.h"

#ifdef __cplusplus
extern "C" {
#endif

/* PPP数据包解析器状态。当前状态表示操作尚未完成。*/
enum {
  PDIDLE = 0,  /* 空闲状态—正在等待。*/
  PDSTART,     /* 进程启动标志。*/
  PDADDRESS,   /* 进程地址字段。*/
  PDCONTROL,   /* 过程控制字段。*/
  PDPROTOCOL1, /* 过程协议字段1。*/
  PDPROTOCOL2, /* 过程协议字段2。*/
  PDDATA       /* 处理数据字节。*/
};

/* PPPoS串行输出回调函数原型*/
typedef u32_t (*pppos_output_cb_fn)(ppp_pcb *pcb, u8_t *data, u32_t len, void *ctx);

/*
 * 扩展异步映射-允许转义任何字符。
 */
typedef u8_t ext_accm[32];

/*
 * PPPoS接口控制块。
 */
typedef struct pppos_pcb_s pppos_pcb;
struct pppos_pcb_s {
  /* --以下是两个会话之间无法清除的数据*/
  ppp_pcb *ppp;                    /* PPP PCB */
  pppos_output_cb_fn output_cb;    /* PPP串行输出回调*/

  /* --以下是将在两个会话之间清除的数据
   *
   * lastxmmit必须是已清除成员中的第一个成员，因为它用于知道哪些部分不能被清除。
   */
  u32_t last_xmit;                 /* 上次传输时间。*/
  ext_accm out_accm;               /* 输出的异步Ctl字符映射。*/

  /* 旗帜*/
  unsigned int open            :1; /* 设置PPPoS是否打开*/
  unsigned int pcomp           :1; /* 对等方是否接受协议压缩？*/
  unsigned int accomp          :1; /* 对等方是否接受addr/ctl压缩？*/

  /* PPPoS rx*/
  ext_accm in_accm;                /* 输入的异步Ctl字符映射。*/
  struct pbuf *in_head, *in_tail;  /* 输入数据包。*/
  u16_t in_protocol;               /* 输入协议代码。*/
  u16_t in_fcs;                    /* 输入帧检查序列值。*/
  u8_t in_state;                   /* 输入进程状态。*/
  u8_t in_escaped;                 /* 转义下一个字符。*/
};

/* 创建新的PPPoS会话。*/
ppp_pcb *pppos_create(struct netif *pppif, pppos_output_cb_fn output_cb,
       ppp_link_status_cb_fn link_status_cb, void *ctx_cb);

#if !NO_SYS && !PPP_INPROC_IRQ_SAFE
/* 将接收到的原始字符传递给PPPoS，以便通过lwIP TCPIP线程进行解码。*/
err_t pppos_input_tcpip(ppp_pcb *ppp, u8_t *s, int l);
#endif /* !NO_SYS && !PPP_INPROC_IRQ_SAFE */

/* PPP over Serial：这是为接收数据调用的输入函数。*/
void pppos_input(ppp_pcb *ppp, u8_t* data, int len);


/*
 * 从lwIP调用的函数不能从lwIP用户应用程序调用。
 */
#if !NO_SYS && !PPP_INPROC_IRQ_SAFE
err_t pppos_input_sys(struct pbuf *p, struct netif *inp);
#endif /* !NO_SYS && !PPP_INPROC_IRQ_SAFE */

#ifdef __cplusplus
}
#endif

#endif /* PPPOS_H */
#endif /* PPP_SUPPORT && PPPOL2TP_SUPPORT */

