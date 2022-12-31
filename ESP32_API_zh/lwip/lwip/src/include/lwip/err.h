/**
 * @file lwIP错误代码
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
#ifndef LWIP_HDR_ERR_H
#define LWIP_HDR_ERR_H

#include "lwip/opt.h"
#include "lwip/arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup infrastructure_errors错误代码
 * @ingroup 基础设施@{
 */

/**错误常数的定义。*/
typedef enum {
/**没有错误，一切正常。*/
  ERR_OK         = 0,
/**内存不足错误。*/
  ERR_MEM        = -1,
/**缓冲区错误。*/
  ERR_BUF        = -2,
/**超时。*/
  ERR_TIMEOUT    = -3,
/**路由问题。*/
  ERR_RTE        = -4,
/**正在进行操作*/
  ERR_INPROGRESS = -5,
/**非法值。*/
  ERR_VAL        = -6,
/**操作将受阻。*/
  ERR_WOULDBLOCK = -7,
/**使用中的地址。*/
  ERR_USE        = -8,
/**已连接。*/
  ERR_ALREADY    = -9,
/**康涅狄格州已经建立。*/
  ERR_ISCONN     = -10,
/**未连接。*/
  ERR_CONN       = -11,
/**低电平netif错误*/
  ERR_IF         = -12,

/**连接已中止。*/
  ERR_ABRT       = -13,
/**连接重置。*/
  ERR_RST        = -14,
/**连接已关闭。*/
  ERR_CLSD       = -15,
/**非法参数。*/
  ERR_ARG        = -16
} err_enum_t;

/**在cc中定义LWIP_ERR_T。h如果您想为平台使用不同的类型（必须签名）。*/
#ifdef LWIP_ERR_T
typedef LWIP_ERR_T err_t;
#else /* LWIP_ERR_T */
typedef s8_t err_t;
#endif /* LWIP_ERR_T*/

/**
 * @}
 */

#ifdef LWIP_DEBUG
extern const char *lwip_strerr(err_t err);
#else
#define lwip_strerr(x) ""
#endif /* LWIP_DEBUG */

#if !NO_SYS
int err_to_errno(err_t err);
#endif /* !NO_SYS */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_ERR_H */

