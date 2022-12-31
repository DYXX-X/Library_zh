/*
 * chap-md5.h-新的chap/md5实现。
 *
 * 版权所有（c）2003 Paul Mackerras。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.未经事先书面许可，不得使用本软件作者的姓名来背书或推广源自本软件的产品。
 *
 * 3.任何形式的再发行都必须保留以下确认：“本产品包括Paul Mackerras开发的软件<paulus@samba.org>".
 *
 * THE AUTHORS OF THIS SOFTWARE DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && CHAP_SUPPORT  /* 如果未配置为在lwipopts.h中使用，则不要构建*/

extern const struct chap_digest_type md5_digest;

#endif /* PPP_SUPPORT && CHAP_SUPPORT */

