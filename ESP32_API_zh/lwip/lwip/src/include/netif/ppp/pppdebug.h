/*****************************************************************************
* pppdebug。h-系统调试实用程序。
*
* 版权所有（c）2003 Marc Boucher，Services Informatiques（MBSI）inc.parts版权所有（c）1998 Global Election Systems inc.parts版权归（c）2001 Cognizant Pty Ltd.所有。
*
* 作者特此授予出于任何目的使用、复制、修改、分发和许可本软件及其文档的权利，前提是所有副本中保留现有版权声明，并且本声明和以下免责声明均包含在任何分发中。任何授权用途都不需要书面协议、许可证或版税。
*
* THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS *AS IS* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************** 修订历史（请不要使用标签！）
*
* 03-01-01马克·鲍彻<marc@mbsi.ca>移植到lwIP。
* 98-07-29 Guy Lancaster <lancasterg@acm.org>, Global Election Systems Inc.原件。
*
*****************************************************************************
*/

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef PPPDEBUG_H
#define PPPDEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/* 跟踪级别。*/
#define LOG_CRITICAL  (PPP_DEBUG | LWIP_DBG_LEVEL_SEVERE)
#define LOG_ERR       (PPP_DEBUG | LWIP_DBG_LEVEL_SEVERE)
#define LOG_NOTICE    (PPP_DEBUG | LWIP_DBG_LEVEL_WARNING)
#define LOG_WARNING   (PPP_DEBUG | LWIP_DBG_LEVEL_WARNING)
#define LOG_INFO      (PPP_DEBUG)
#define LOG_DETAIL    (PPP_DEBUG)
#define LOG_DEBUG     (PPP_DEBUG)

#if PPP_DEBUG

#define MAINDEBUG(a)    LWIP_DEBUGF(LWIP_DBG_LEVEL_WARNING, a)
#define SYSDEBUG(a)     LWIP_DEBUGF(LWIP_DBG_LEVEL_WARNING, a)
#define FSMDEBUG(a)     LWIP_DEBUGF(LWIP_DBG_LEVEL_WARNING, a)
#define LCPDEBUG(a)     LWIP_DEBUGF(LWIP_DBG_LEVEL_WARNING, a)
#define IPCPDEBUG(a)    LWIP_DEBUGF(LWIP_DBG_LEVEL_WARNING, a)
#define IPV6CPDEBUG(a)  LWIP_DEBUGF(LWIP_DBG_LEVEL_WARNING, a)
#define UPAPDEBUG(a)    LWIP_DEBUGF(LWIP_DBG_LEVEL_WARNING, a)
#define CHAPDEBUG(a)    LWIP_DEBUGF(LWIP_DBG_LEVEL_WARNING, a)
#define PPPDEBUG(a, b)  LWIP_DEBUGF(a, b)

#else /* PPP_DEBUG */

#define MAINDEBUG(a)
#define SYSDEBUG(a)
#define FSMDEBUG(a)
#define LCPDEBUG(a)
#define IPCPDEBUG(a)
#define IPV6CPDEBUG(a)
#define UPAPDEBUG(a)
#define CHAPDEBUG(a)
#define PPPDEBUG(a, b)

#endif /* PPP_DEBUG */

#ifdef __cplusplus
}
#endif

#endif /* PPPDEBUG_H */

#endif /* PPP_SUPPORT */

