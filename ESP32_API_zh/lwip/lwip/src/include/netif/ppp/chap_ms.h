/*
 * chap_ms。h-质询握手认证协议定义。
 *
 * 版权所有（c）1995 Eric Rosenquist。保留所有权利。
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
 * $Id:chap_ms。h、 v 1.13 2004/11/15 22:13:26 paulus Exp$
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && MSCHAP_SUPPORT  /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#ifndef CHAPMS_INCLUDE
#define CHAPMS_INCLUDE

extern const struct chap_digest_type chapms_digest;
extern const struct chap_digest_type chapms2_digest;

#endif /* CHAPMS_INCLUDE */

#endif /* PPP_SUPPORT && MSCHAP_SUPPORT */

