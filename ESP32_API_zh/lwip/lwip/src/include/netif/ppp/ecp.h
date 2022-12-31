/*
 * 欧洲药典。h-PPP加密控制协议的定义。
 *
 * 版权所有（c）2002谷歌公司。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用本软件作者的姓名来背书或推广源自本软件的产品。
 *
 * THE AUTHORS OF THIS SOFTWARE DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $Id:ecp。h、 v 1.2 2003/01/10 07:12:36 fcusack到期$
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && ECP_SUPPORT  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef ECP_H
#define ECP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ecp_options {
    bool required;		/* 是否需要ECP？*/
    unsigned enctype;		/* 加密类型*/
} ecp_options;

extern fsm ecp_fsm[];
extern ecp_options ecp_wantoptions[];
extern ecp_options ecp_gotoptions[];
extern ecp_options ecp_allowoptions[];
extern ecp_options ecp_hisoptions[];

extern const struct protent ecp_protent;

#ifdef __cplusplus
}
#endif

#endif /* ECP_H */
#endif /* PPP_SUPPORT && ECP_SUPPORT */

