/**
 * @file DHCP客户端API
 */

/*
 * Copyright (c) 2001-2004 Leon Woestenberg <leon.woestenberg@gmx.net> 版权所有（c）2001-2004 Axon Digital Design B.V.，荷兰。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Leon Woestenberg<leon.woestenberg@gmx.net>
 *
 */
#ifndef LWIP_HDR_DHCP_H
#define LWIP_HDR_DHCP_H

#include "lwip/opt.h"

#if LWIP_DHCP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/netif.h"
#include "lwip/udp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**应用程序调用dhcp_parse_tmr（）的周期（秒）*/
#if ESP_DHCP
#define DHCP_COARSE_TIMER_SECS 1
#else
#define DHCP_COARSE_TIMER_SECS 60
#endif
/**应用程序调用dhcp_parse_tmr（）的周期（毫秒）*/
#define DHCP_COARSE_TIMER_MSECS (DHCP_COARSE_TIMER_SECS * 1000UL)
/**应用程序调用dhcp_fine_tmr（）的周期（毫秒）*/
#define DHCP_FINE_TIMER_MSECS   500

#define DHCP_BOOT_FILE_LEN      128U

/* AutoIP协作标志（struct dhcp.AutoIP_coop_state）*/
typedef enum {
  DHCP_AUTOIP_COOP_STATE_OFF  = 0,
  DHCP_AUTOIP_COOP_STATE_ON   = 1
} dhcp_autoip_coop_state_enum_t;

struct dhcp
{
  /**上次发送请求的事务标识符*/
  u32_t xid;
  /**轨道PCB分配状态*/
  u8_t pcb_allocated;
  /**当前DHCP状态机状态*/
  u8_t state;
  /**当前请求的重试次数*/
  u8_t tries;
#if LWIP_DHCP_AUTOIP_COOP
  u8_t autoip_coop_state;
#endif
  u8_t subnet_mask_given;

  u16_t request_timeout; /* #请求超时的时间间隔为DHCP_FINE_TIMER_SECS*/
#if ESP_DHCP
  u32_t t1_timeout;  /* #以DHCP_COARSE_TIMER_SECS为周期标记续订时间*/
  u32_t t2_timeout;  /* #重新绑定时间的周期为DHCP_COARSE_TIMER_SECS*/
  u32_t t1_renew_time;  /* #在下次续订尝试之前，以DHCP_COARSE_TIMER_SECS为周期*/
  u32_t t2_rebind_time; /* #以DHCP_COARSE_TIMER_SECS为周期计时，直到下一次重新绑定尝试*/
  u32_t lease_used; /* #自上次收到DHCP ack以来，周期为DHCP_COARSE_TIMER_SECS的滴答声*/
  u32_t t0_timeout; /* #租赁时间的周期为DHCP_COARSE_TIMER_SECS*/
#else
  u16_t t1_timeout;  /* #以DHCP_COARSE_TIMER_SECS为周期标记续订时间*/
  u16_t t2_timeout;  /* #重新绑定时间的周期为DHCP_COARSE_TIMER_SECS*/
  u16_t t1_renew_time;  /* #在下次续订尝试之前，以DHCP_COARSE_TIMER_SECS为周期*/
  u16_t t2_rebind_time; /* #以DHCP_COARSE_TIMER_SECS为周期计时，直到下一次重新绑定尝试*/
  u16_t lease_used; /* #自上次收到DHCP ack以来，周期为DHCP_COARSE_TIMER_SECS的滴答声*/
  u16_t t0_timeout; /* #租赁时间的周期为DHCP_COARSE_TIMER_SECS*/
#endif
  ip_addr_t server_ip_addr; /* 提供此租约的dhcp服务器地址（ip_addr_t，因为已传递给UDP）*/
  ip4_addr_t offered_ip_addr;
  ip4_addr_t offered_sn_mask;
  ip4_addr_t offered_gw_addr;

  u32_t offered_t0_lease; /* 租赁期（秒）*/
  u32_t offered_t1_renew; /* 建议续订时间（通常为租赁期的50%）*/
  u32_t offered_t2_rebind; /* 建议重新绑定时间（通常为租赁期的87.5）*/
#if LWIP_DHCP_BOOTP_FILE
  ip4_addr_t offered_si_addr;
  char boot_file_name[DHCP_BOOT_FILE_LEN];
#endif /* LWIP_DHCP_BOOTPFILE */

  /* Espressif添加开始。*/
#ifdef ESP_DHCP
  void (*cb)(struct netif*); /* 回调dhcp，如果需要，添加一个参数来显示dhcp状态*/
#else
  void (*cb)(void); /* 回调dhcp，如果需要，添加一个参数来显示dhcp状态*/
#endif
  /* Espressif添加结束。*/
};


void dhcp_set_struct(struct netif *netif, struct dhcp *dhcp);
/**使用dhcp_set_struct（）删除先前设置为netif的结构dhcp*/
#define dhcp_remove_struct(netif) netif_set_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP, NULL)
void dhcp_cleanup(struct netif *netif);
err_t dhcp_start(struct netif *netif);
err_t dhcp_renew(struct netif *netif);
err_t dhcp_release(struct netif *netif);
void dhcp_stop(struct netif *netif);
void dhcp_release_and_stop(struct netif *netif);
void dhcp_inform(struct netif *netif);
void dhcp_network_changed(struct netif *netif);

/* Espressif添加开始。*/
/**为DHCP设置回调*/
#ifdef ESP_DHCP
void dhcp_set_cb(struct netif *netif, void (*cb)(struct netif*));
#else
void dhcp_set_cb(struct netif *netif, void (*cb)(void));
#endif
/* Espressif添加结束。*/

#if DHCP_DOES_ARP_CHECK
void dhcp_arp_reply(struct netif *netif, const ip4_addr_t *addr);
#endif
u8_t dhcp_supplied_address(const struct netif *netif);
/* 每分钟都有人打电话*/
void dhcp_coarse_tmr(void);
/* 每半秒被呼叫一次*/
void dhcp_fine_tmr(void);

#if LWIP_DHCP_GET_NTP_SRV
/**除此之外，必须存在此功能才能将提供的NTP服务器添加到NTP（或SNTP）引擎。请参阅LWIP_DHCP_MAX_NTP_SERVERS*/
extern void dhcp_set_ntp_servers(u8_t num_ntp_servers, const ip4_addr_t* ntp_server_addrs);
#endif /* LWIP_DHCP_GET_NTP_SRV */

#if ESP_DHCP && !ESP_DHCP_DISABLE_VENDOR_CLASS_IDENTIFIER
err_t dhcp_set_vendor_class_identifier(u8_t len, char *str);
err_t dhcp_get_vendor_specific_information(u8_t len, char *str);
#endif /* ESP_DHCP && !ESP_DHCP_DISABLE_VENDOR_CLASS_IDENTIFIER */

#define netif_dhcp_data(netif) ((struct dhcp*)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP))

#ifdef __cplusplus
}
#endif

#endif /* LWIP_DHCP */

#endif /*LWIP_HDR_DHCP_H*/

