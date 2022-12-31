/**
 * @file AutoIP协议定义
 */

/*
 * 版权所有（c）2007 Dominik Spies<kontakt@dspies.de>保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 作者：Dominik Spies<kontakt@dspies.de>
 *
 * 这是lwIP TCP/IP堆栈的AutoIP实现。它旨在符合RFC 3927。
 *
 */

#ifndef LWIP_HDR_PROT_AUTOIP_H
#define LWIP_HDR_PROT_AUTOIP_H

#ifdef __cplusplus
extern "C" {
#endif

/* 169.254.0.0 */
#define AUTOIP_NET              0xA9FE0000
/* 169.254.1.0 */
#define AUTOIP_RANGE_START      (AUTOIP_NET | 0x0100)
/* 169.254.254.255 */
#define AUTOIP_RANGE_END        (AUTOIP_NET | 0xFEFF)

/* RFC 3927常量*/
#define PROBE_WAIT              1   /* 秒（初始随机延迟）*/
#define PROBE_MIN               1   /* 秒（重复探测前的最小延迟）*/
#define PROBE_MAX               2   /* 秒（重复探测前的最大延迟）*/
#define PROBE_NUM               3   /*          （探测包的数量）*/
#define ANNOUNCE_NUM            2   /*          （通告数据包的数量）*/
#define ANNOUNCE_INTERVAL       2   /* 秒（通告数据包之间的时间）*/
#define ANNOUNCE_WAIT           2   /* 秒（宣布前的延迟）*/
#if ESP_LWIP
#define MAX_CONFLICTS           LWIP_AUTOIP_MAX_CONFLICTS        /*          （速率限制前的最大冲突数）*/
#define RATE_LIMIT_INTERVAL     LWIP_AUTOIP_RATE_LIMIT_INTERVAL  /* 秒（连续尝试之间的延迟）*/
#else
#define MAX_CONFLICTS           10  /*          （速率限制前的最大冲突数）*/
#define RATE_LIMIT_INTERVAL     60  /* 秒（连续尝试之间的延迟）*/
#endif
#define DEFEND_INTERVAL         10  /* 秒（防御ARPs之间的最小等待时间）*/

/* AutoIP客户端状态*/
typedef enum {
  AUTOIP_STATE_OFF        = 0,
  AUTOIP_STATE_PROBING    = 1,
  AUTOIP_STATE_ANNOUNCING = 2,
  AUTOIP_STATE_BOUND      = 3
} autoip_state_enum_t;

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_AUTOIP_H */

