/*
 * ESP32平台的libcoap配置实现。
 *
 * 在使用并发配置操作时，使用libcoap软件实现进行故障切换。
 *
 * 围板。h——libcoap的CoAP堆栈的主头文件
 *
 * 版权所有（C）2010-20122015-2016 Olaf Bergmann<bergmann@tzi.org>2015年Carsten Schoenert<c.schoenert@t-online.de>
 *
 * 版权所有2015-2016 Espressif Systems（上海）私人有限公司
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_CONFIG_POSIX_H_
#define COAP_CONFIG_POSIX_H_

#ifdef WITH_POSIX

#include <sys/socket.h>
#include <net/if.h>

#define HAVE_SYS_SOCKET_H
#define HAVE_MALLOC
#define HAVE_ARPA_INET_H
#define HAVE_TIME_H
#define HAVE_NETDB_H
#define HAVE_NETINET_IN_H
#define HAVE_STRUCT_CMSGHDR
#define COAP_DISABLE_TCP 0

#define ipi_spec_dst ipi_addr
struct in6_pktinfo {
  struct in6_addr ipi6_addr;        /* src/dst IPv6地址*/
  unsigned int ipi6_ifindex;        /* 发送/接收接口索引*/
};
#define IN6_IS_ADDR_V4MAPPED(a) \
        ((((__const uint32_t *) (a))[0] == 0)                                 \
         && (((__const uint32_t *) (a))[1] == 0)                              \
         && (((__const uint32_t *) (a))[2] == htonl (0xffff)))

/* 如未定义，只需定义为无害的东西*/
#define IPV6_PKTINFO IPV6_CHECKSUM

#define PACKAGE_NAME "libcoap-posix"
#define PACKAGE_VERSION "?"

#ifdef CONFIG_MBEDTLS_TLS_ENABLED
#define HAVE_MBEDTLS
#endif /* CONFIG_MBEDTLS_TLS_ENABLED */
#define COAP_CONSTRAINED_STACK 1
#define ESPIDF_VERSION

#define gai_strerror(x) "gai_strerror() not supported"

#endif /* WITH_POSIX */
#endif /* COAP_CONFIG_POSIX_H_ */

