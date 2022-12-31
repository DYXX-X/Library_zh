/**
 * @file SNMP服务器主API-启动和基本配置
 */

/*
 * Copyright (c) 2001, 2002 Leon Woestenberg <leon.woestenberg@axon.tv> 版权所有（c）20012002荷兰Axon Digital Design B.V。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * Author: Leon Woestenberg <leon.woestenberg@axon.tv> 马丁·亨策尔<info@cl-soft.de>
 *
 */
#ifndef LWIP_HDR_APPS_SNMP_H
#define LWIP_HDR_APPS_SNMP_H

#include "lwip/apps/snmp_opts.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_SNMP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/err.h"
#include "lwip/apps/snmp_core.h"

/**SNMP变量绑定描述符（陷阱公开需要）*/
struct snmp_varbind
{
  /**指向下一个varbind的指针，列表中最后一个为NULL*/
  struct snmp_varbind *next;
  /**指向上一个varbind的指针，列表中第一个为NULL*/
  struct snmp_varbind *prev;

  /**对象标识符*/
  struct snmp_obj_id oid;

  /**值ASN1类型*/
  u8_t type;
  /**对象值长度*/
  u16_t value_len;
  /**目标值*/
  void *value;
};

/**
 * @ingroup snmp_core代理安装程序，开始侦听端口161。
 */
void snmp_init(void);
void snmp_set_mibs(const struct snmp_mib **mibs, u8_t num_mibs);

void snmp_set_device_enterprise_oid(const struct snmp_obj_id* device_enterprise_oid);
const struct snmp_obj_id* snmp_get_device_enterprise_oid(void);

void snmp_trap_dst_enable(u8_t dst_idx, u8_t enable);
void snmp_trap_dst_ip_set(u8_t dst_idx, const ip_addr_t *dst);

/**通用陷阱：冷启动*/
#define SNMP_GENTRAP_COLDSTART 0
/**通用陷阱：热启动*/
#define SNMP_GENTRAP_WARMSTART 1
/**通用陷阱：链接关闭*/
#define SNMP_GENTRAP_LINKDOWN 2
/**通用陷阱：链接*/
#define SNMP_GENTRAP_LINKUP 3
/**通用陷阱：身份验证失败*/
#define SNMP_GENTRAP_AUTH_FAILURE 4
/**通用陷阱：EGP邻居丢失*/
#define SNMP_GENTRAP_EGP_NEIGHBOR_LOSS 5
/**通用陷阱：企业特定*/
#define SNMP_GENTRAP_ENTERPRISE_SPECIFIC 6

err_t snmp_send_trap_generic(s32_t generic_trap);
err_t snmp_send_trap_specific(s32_t specific_trap, struct snmp_varbind *varbinds);
err_t snmp_send_trap(const struct snmp_obj_id* oid, s32_t generic_trap, s32_t specific_trap, struct snmp_varbind *varbinds);

#define SNMP_AUTH_TRAPS_DISABLED 0
#define SNMP_AUTH_TRAPS_ENABLED  1
void snmp_set_auth_traps_enabled(u8_t enable);
u8_t snmp_get_auth_traps_enabled(void);

u8_t snmp_v1_enabled(void);
u8_t snmp_v2c_enabled(void);
u8_t snmp_v3_enabled(void);
void snmp_v1_enable(u8_t enable);
void snmp_v2c_enable(u8_t enable);
void snmp_v3_enable(u8_t enable);

const char * snmp_get_community(void);
const char * snmp_get_community_write(void);
const char * snmp_get_community_trap(void);
void snmp_set_community(const char * const community);
void snmp_set_community_write(const char * const community);
void snmp_set_community_trap(const char * const community);

void snmp_coldstart_trap(void);
void snmp_authfail_trap(void);

typedef void (*snmp_write_callback_fct)(const u32_t* oid, u8_t oid_len, void* callback_arg);
void snmp_set_write_callback(snmp_write_callback_fct write_callback, void* callback_arg);

#endif /* LWIP_SNMP */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_SNMP_H */

