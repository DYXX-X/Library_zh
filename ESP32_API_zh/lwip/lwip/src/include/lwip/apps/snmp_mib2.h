/**
 * @file SNMP MIB2 API
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
 * 作者：Dirk Ziegelmeier<dziegel@gmx.de>
 *
 */
#ifndef LWIP_HDR_APPS_SNMP_MIB2_H
#define LWIP_HDR_APPS_SNMP_MIB2_H

#include "lwip/apps/snmp_opts.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_SNMP /* 如果未配置为在lwipots中使用，请不要构建。小时*/
#if SNMP_LWIP_MIB2

#include "lwip/apps/snmp_core.h"

extern const struct snmp_mib mib2;

#if SNMP_USE_NETCONN
#include "lwip/apps/snmp_threadsync.h"
void snmp_mib2_lwip_synchronizer(snmp_threadsync_called_fn fn, void* arg);
extern struct snmp_threadsync_instance snmp_mib2_lwip_locks;
#endif

#ifndef SNMP_SYSSERVICES
#define SNMP_SYSSERVICES ((1 << 6) | (1 << 3) | ((IP_FORWARD) << 2))
#endif

void snmp_mib2_set_sysdescr(const u8_t* str, const u16_t* len); /* 只读be定义*/
void snmp_mib2_set_syscontact(u8_t *ocstr, u16_t *ocstrlen, u16_t bufsize);
void snmp_mib2_set_syscontact_readonly(const u8_t *ocstr, const u16_t *ocstrlen);
void snmp_mib2_set_sysname(u8_t *ocstr, u16_t *ocstrlen, u16_t bufsize);
void snmp_mib2_set_sysname_readonly(const u8_t *ocstr, const u16_t *ocstrlen);
void snmp_mib2_set_syslocation(u8_t *ocstr, u16_t *ocstrlen, u16_t bufsize);
void snmp_mib2_set_syslocation_readonly(const u8_t *ocstr, const u16_t *ocstrlen);

#endif /* SNMP_LWIP_MIB2 */
#endif /* LWIP_SNMP */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_SNMP_MIB2_H */

