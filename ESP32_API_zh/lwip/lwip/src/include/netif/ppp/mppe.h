/*
 * mppe。h-MPPE的定义
 *
 * 版权所有（c）2008 Paul Mackerras。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用本软件作者的姓名来背书或推广源自本软件的产品。
 *
 * 4.任何形式的再发行都必须保留以下确认：“本产品包括Paul Mackerras开发的软件<paulus@samba.org>".
 *
 * THE AUTHORS OF THIS SOFTWARE DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && MPPE_SUPPORT  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef MPPE_H
#define MPPE_H

#include "netif/ppp/pppcrypt.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MPPE_PAD		4	/* 每帧MPPE增长*/
#define MPPE_MAX_KEY_LEN	16	/* 最大密钥长度（128位）*/

/* ccp_options的选项位。mppe公司*/
#define MPPE_OPT_40		0x01	/* 40位*/
#define MPPE_OPT_128		0x02	/* 128位*/
#define MPPE_OPT_STATEFUL	0x04	/* 有状态模式*/
/* 不支持的opts*/
#define MPPE_OPT_56		0x08	/* 56位*/
#define MPPE_OPT_MPPC		0x10	/* MPPC压缩*/
#define MPPE_OPT_D		0x20	/* 未知的*/
#define MPPE_OPT_UNSUPPORTED (MPPE_OPT_56|MPPE_OPT_MPPC|MPPE_OPT_D)
#define MPPE_OPT_UNKNOWN	0x40	/* 位！RFC 3078中定义的*/

/*
 * 这不太好……但另一种选择是位域结构。不幸的是，我们不能为上面的选项名称共享相同的位，因为C和H是相同的位。我们可以执行u_int32，但是我们必须始终执行lwip_htonl（），和/或我们仍然需要知道哪个八位位组是哪个。
 */
#define MPPE_C_BIT		0x01	/* MPPC */
#define MPPE_D_BIT		0x10	/* 已过时，用法未知*/
#define MPPE_L_BIT		0x20	/* 40位*/
#define MPPE_S_BIT		0x40	/* 128位*/
#define MPPE_M_BIT		0x80	/* 56位，不支持*/
#define MPPE_H_BIT		0x01	/* 无状态（在不同的字节中）*/

/* 不包括H位；仅用于最低有效八位字节。*/
#define MPPE_ALL_BITS (MPPE_D_BIT|MPPE_L_BIT|MPPE_S_BIT|MPPE_M_BIT|MPPE_H_BIT)

/* 从mppe opts构建CI（请参阅RFC 3078）*/
#define MPPE_OPTS_TO_CI(opts, ci)		\
    do {					\
	u_char *ptr = ci; /* u_字符[4]*/	\
						\
	/* H位*/				\
	if (opts & MPPE_OPT_STATEFUL)		\
	    *ptr++ = 0x0;			\
	else					\
	    *ptr++ = MPPE_H_BIT;		\
	*ptr++ = 0;				\
	*ptr++ = 0;				\
						\
	/* S、 L位*/				\
	*ptr = 0;				\
	if (opts & MPPE_OPT_128)		\
	    *ptr |= MPPE_S_BIT;			\
	if (opts & MPPE_OPT_40)			\
	    *ptr |= MPPE_L_BIT;			\
	/* M、 不支持D、C位*/		\
    } while (/* CONSTCOND */ 0)

/* 与上述相反*/
#define MPPE_CI_TO_OPTS(ci, opts)		\
    do {					\
	const u_char *ptr = ci; /* u_字符[4]*/	\
						\
	opts = 0;				\
						\
	/* H位*/				\
	if (!(ptr[0] & MPPE_H_BIT))		\
	    opts |= MPPE_OPT_STATEFUL;		\
						\
	/* S、 L位*/				\
	if (ptr[3] & MPPE_S_BIT)		\
	    opts |= MPPE_OPT_128;		\
	if (ptr[3] & MPPE_L_BIT)		\
	    opts |= MPPE_OPT_40;		\
						\
	/* M、 D、C位*/			\
	if (ptr[3] & MPPE_M_BIT)		\
	    opts |= MPPE_OPT_56;		\
	if (ptr[3] & MPPE_D_BIT)		\
	    opts |= MPPE_OPT_D;			\
	if (ptr[3] & MPPE_C_BIT)		\
	    opts |= MPPE_OPT_MPPC;		\
						\
	/* 其他位*/			\
	if (ptr[0] & ~MPPE_H_BIT)		\
	    opts |= MPPE_OPT_UNKNOWN;		\
	if (ptr[1] || ptr[2])			\
	    opts |= MPPE_OPT_UNKNOWN;		\
	if (ptr[3] & ~MPPE_ALL_BITS)		\
	    opts |= MPPE_OPT_UNKNOWN;		\
    } while (/* CONSTCOND */ 0)

/* MSCHAP和MPPE之间的共享MPPE填充*/
#define SHA1_PAD_SIZE 40

static const u8_t mppe_sha1_pad1[SHA1_PAD_SIZE] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const u8_t mppe_sha1_pad2[SHA1_PAD_SIZE] = {
  0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2,
  0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2,
  0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2,
  0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2
};

/*
 * MPPE（de）压缩机的状态。
 */
typedef struct ppp_mppe_state {
	lwip_arc4_context arc4;
	u8_t master_key[MPPE_MAX_KEY_LEN];
	u8_t session_key[MPPE_MAX_KEY_LEN];
	u8_t keylen;                /* 密钥长度（字节）*/
	/* 注意：128位==16，40位==8！如果我们想支持56位，则单元必须更改为位
	 */
	u8_t bits;                  /* MPPE控制位*/
	u16_t ccount;               /* 12位一致性计数（seqno）*/
	u16_t sanity_errors;        /* 如果LCP过多，取下LCP*/
	unsigned int stateful  :1;  /* 有状态模式标志*/
	unsigned int discard   :1;  /* 有状态模式数据包丢失标志*/
} ppp_mppe_state;

void mppe_set_key(ppp_pcb *pcb, ppp_mppe_state *state, u8_t *key);
void mppe_init(ppp_pcb *pcb, ppp_mppe_state *state, u8_t options);
void mppe_comp_reset(ppp_pcb *pcb, ppp_mppe_state *state);
err_t mppe_compress(ppp_pcb *pcb, ppp_mppe_state *state, struct pbuf **pb, u16_t protocol);
void mppe_decomp_reset(ppp_pcb *pcb, ppp_mppe_state *state);
err_t mppe_decompress(ppp_pcb *pcb, ppp_mppe_state *state, struct pbuf **pb);

#ifdef __cplusplus
}
#endif

#endif /* MPPE_H */
#endif /* PPP_SUPPORT && MPPE_SUPPORT */

