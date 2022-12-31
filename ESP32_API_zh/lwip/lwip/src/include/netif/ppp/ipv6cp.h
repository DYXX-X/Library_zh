/*
 * ipv6cp。h-PPP IPV6控制协议。
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
 */

/*  原始版本，基于RFC2023：

    版权所有（c）1995、1996、1997Francis.Dupont@inria.fr，INRIA Roccquiourt，Alain.Durand@imag.fr，IMAG，Jean-Luc.Richier@imag.fr，IMAG-LSR。

    版权所有（c）1998、1999Francis.Dupont@inria.fr，吉迪迪，Alain.Durand@imag.fr，IMAG，Jean-Luc.Richier@imag.fr，IMAG-LSR。

    Ce travail aétéfait au sein du GIE DYADE（国际经济集团，BULL S.a.和INRIA）。

    逻辑信息是一种可处理的特殊条件，通常用于再利用、复制、修改和分发逻辑信息的原始文件。

    国家信息与自动化研究所（INRIA）、国际图像研究所（IMAG）的名称，是一个人的士气、体格和参与逻辑和物理实验的能力，没有明确的协议。

    我的逻辑是四个电话号码，支持你的责任。版权来源“加州大学伯克利分校”和“数字设备公司”拥有版权。

    格勒诺布尔信息与数学应用研究所（IMAG）是CNRS研究所、格勒诺波尔国家理工学院和约瑟夫·傅里叶大学（Joseph Fourier University）的混合实验室。

    这项工作是在GIE DYADE（BULL S.A.和INRIA的联合研发企业）的背景下完成的。

    该软件具有通常的“研究”条款，目的是保留软件的学分。特此授予出于任何目的免费使用、复制、修改和分发本软件的许可，前提是上述版权声明和本许可声明出现在所有副本中，并且未经事先明确许可，INRIA、IMAG或任何贡献者的名称不得用于与本材料相关的广告或宣传。软件按“原样”提供，无任何担保、支持或责任。该软件源于受版权保护的“加州大学伯克利分校”和“数字设备公司”的源代码。

    格勒诺布尔计算机科学与应用数学研究所（IMAG）是由七个研究单位组成的联合会，由CNRS、格勒诺波尔国家理工学院和约瑟夫·傅里叶大学资助。软件、系统、网络（LSR）的研究单位是IMAG的成员。
*/

/*
 * 来源：
 *
 * ipcp。h-IP控制协议定义。
 *
 * 版权所有（c）1984-2000卡内基梅隆大学。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用“卡耐基梅隆大学”的名称来支持或推广源自本软件的产品。如需获得许可或任何法律详情，请联系卡内基梅隆大学技术转让办公室，地址：宾夕法尼亚州匹兹堡福布斯大道5000号，邮编：15213-3890（412）268-4387，传真：（412）268-7395tech-transfer@andrew.cmu.edu
 *
 * 4.任何形式的再分发都必须保留以下确认：“本产品包括由卡内基梅隆大学计算服务部开发的软件(http://www.cmu.edu/computing/)."
 *
 * CARNEGIE MELLON UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $Id:ipv6cp。h、 v 1.7 2002/12/04 23:03:32 paulus展览$
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && PPP_IPV6_SUPPORT  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef IPV6CP_H
#define	IPV6CP_H

#include "eui64.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 选项。
 */
#define CI_IFACEID	1	/* 接口标识符*/
#ifdef IPV6CP_COMP
#define CI_COMPRESSTYPE	2	/* 压缩类型*/
#endif /* IPV6CP_COMP */

/* 尚未定义压缩类型#定义IPV6CP_COMP 0x004f
 */
typedef struct ipv6cp_options {
    unsigned int neg_ifaceid    :1;  /* 协商接口标识符？*/
    unsigned int req_ifaceid    :1;  /* 要求对等方发送接口标识符？*/
    unsigned int accept_local   :1;  /* 接受同行的iface id值？*/
    unsigned int opt_local      :1;  /* 由选项设置的ourtoken*/
    unsigned int opt_remote     :1;  /* 按选项设置的历史记录*/
    unsigned int use_ip         :1;  /* 使用IP作为接口标识符*/
#if 0
    unsigned int use_persistent :1;  /* 对地址使用唯一持久值*/
#endif
#ifdef IPV6CP_COMP
    unsigned int neg_vj         :1;  /* Van Jacobson压缩？*/
#endif /* IPV6CP_COMP */

#ifdef IPV6CP_COMP
    u_short vj_protocol;        /* 要在VJ选项中使用的协议值*/
#endif /* IPV6CP_COMP */
    eui64_t ourid, hisid;       /* 接口标识符*/
} ipv6cp_options;

extern const struct protent ipv6cp_protent;

#ifdef __cplusplus
}
#endif

#endif /* IPV6CP_H */
#endif /* PPP_SUPPORT && PPP_IPV6_SUPPORT */

