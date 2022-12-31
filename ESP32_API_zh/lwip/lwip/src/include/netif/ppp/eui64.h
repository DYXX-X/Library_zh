/*
 * eui64.h-IPv6CP的eui64例程。
 *
 * 版权所有（c）1999 Tommi Komulainen。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用本软件作者的姓名来背书或推广源自本软件的产品。
 *
 * 4.任何形式的再分发都必须保留以下确认：“本产品包括Tommi Komulainen开发的软件<Tommi.Komulainen@iki.fi>".
 *
 * THE AUTHORS OF THIS SOFTWARE DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $Id:eui64.h，v 1.6 2002/12/04 23:03:32 paulus Exp$
*/

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && PPP_IPV6_SUPPORT  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef EUI64_H
#define EUI64_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @todo:
 *
 * 也许这应该通过直接处理结构in6_addr来完成。。。
 */
typedef union
{
    u8_t e8[8];
    u16_t e16[4];
    u32_t e32[2];
} eui64_t;

#define eui64_iszero(e)		(((e).e32[0] | (e).e32[1]) == 0)
#define eui64_equals(e, o)	(((e).e32[0] == (o).e32[0]) && \
				((e).e32[1] == (o).e32[1]))
#define eui64_zero(e)		(e).e32[0] = (e).e32[1] = 0;

#define eui64_copy(s, d)	memcpy(&(d), &(s), sizeof(eui64_t))

#define eui64_magic(e)		do {			\
				(e).e32[0] = magic();	\
				(e).e32[1] = magic();	\
				(e).e8[0] &= ~2;	\
				} while (0)
#define eui64_magic_nz(x)	do {				\
				eui64_magic(x);			\
				} while (eui64_iszero(x))
#define eui64_magic_ne(x, y)	do {				\
				eui64_magic(x);			\
				} while (eui64_equals(x, y))

#define eui64_get(ll, cp)	do {				\
				eui64_copy((*cp), (ll));	\
				(cp) += sizeof(eui64_t);	\
				} while (0)

#define eui64_put(ll, cp)	do {				\
				eui64_copy((ll), (*cp));	\
				(cp) += sizeof(eui64_t);	\
				} while (0)

#define eui64_set32(e, l)	do {			\
				(e).e32[0] = 0;		\
				(e).e32[1] = lwip_htonl(l);	\
				} while (0)
#define eui64_setlo32(e, l)	eui64_set32(e, l)

char *eui64_ntoa(eui64_t);	/* 返回id的ascii表示形式*/

#ifdef __cplusplus
}
#endif

#endif /* EUI64_H */
#endif /* PPP_SUPPORT && PPP_IPV6_SUPPORT */

