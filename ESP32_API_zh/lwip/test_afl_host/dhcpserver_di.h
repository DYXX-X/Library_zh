/*
 * dhcpserver-dependency注入——预包含将接口测试函数注入静态变量
 *
 */
#include "no_warn_host.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "tcpip_adapter.h"

#ifndef BUILDING_DEF

static void handle_dhcp(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

void (*dhcp_test_static_handle_hdcp)(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port) = NULL;

void dhcp_test_init_di(void)
{
    dhcp_test_static_handle_hdcp = handle_dhcp;
}

void dhcp_test_handle_dhcp(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    dhcp_test_static_handle_hdcp(arg, pcb, p, addr, port);
}

#endif

