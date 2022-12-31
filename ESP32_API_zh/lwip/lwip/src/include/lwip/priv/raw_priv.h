/**
 * @file 原始API内部实现（不在应用程序代码中使用）
 */

/*
 * 版权所有（c）2001-2004瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */
#ifndef LWIP_HDR_RAW_PRIV_H
#define LWIP_HDR_RAW_PRIV_H

#include "lwip/opt.h"

#if LWIP_RAW /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/raw.h"

#ifdef __cplusplus
extern "C" {
#endif

/**raw_input的返回代码*/
typedef enum raw_input_state
{
  RAW_INPUT_NONE = 0, /* pbuf与任何pcbs都不匹配*/
  RAW_INPUT_EATEN,    /* pbuf交付给pcb*/
  RAW_INPUT_DELIVERED /* pbuf仅交付给pcb（pbuf仍可参考）*/
} raw_input_state_t;

/* 以下功能是RAW的下层接口。*/
raw_input_state_t raw_input(struct pbuf *p, struct netif *inp);

void raw_netif_ip_addr_changed(const ip_addr_t* old_addr, const ip_addr_t* new_addr);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_RAW */

#endif /* LWIP_HDR_RAW_PRIV_H */

