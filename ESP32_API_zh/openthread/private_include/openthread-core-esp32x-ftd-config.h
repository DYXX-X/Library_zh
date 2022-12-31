/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "sdkconfig.h"

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_INFO
 *
 * 要插入OpenThread版本字符串的平台特定字符串。
 *
 */
#define OPENTHREAD_CONFIG_PLATFORM_INFO CONFIG_IDF_TARGET

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_ASSERT_MANAGEMENT
 *
 * 当设置此标志时，断言由平台定义的逻辑管理。
 *
 */
#define OPENTHREAD_CONFIG_PLATFORM_ASSERT_MANAGEMENT 1

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_FLASH_API_ENABLE
 *
 * 定义为1以启用otPlatFlash*API以支持非易失性存储。
 *
 * 当定义为1时，平台必须实现otPlatFlash*API，而不是otPlatSettings*API。
 *
 */
#define OPENTHREAD_CONFIG_PLATFORM_FLASH_API_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_LOG_OUTPUT
 *
 * ESP-IDF平台提供了otPlatLog（）函数。
 */
#define OPENTHREAD_CONFIG_LOG_OUTPUT OPENTHREAD_CONFIG_LOG_OUTPUT_PLATFORM_DEFINED

/**
 * @def OPENTHREAD_CONFIG_LOG_LEVEL
 *
 * 日志级别（在编译时使用）。如果设置了`OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE`，则定义了可能的最详细日志级别。请参阅“OPENTHREAD_CONFIG_LOG_LEVEL_INIT”以设置初始日志级别。
 *
 */
#define OPENTHREAD_CONFIG_LOG_LEVEL OT_LOG_LEVEL_DEBG

/**
 * @def OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE
 *
 * 定义为1以启用动态日志级别控制。
 *
 */
#define OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE 1

#define OPENTHREAD_CONFIG_LOG_API 1
#define OPENTHREAD_CONFIG_LOG_ARP 1
#define OPENTHREAD_CONFIG_LOG_BBR 1
#define OPENTHREAD_CONFIG_LOG_CLI 1
#define OPENTHREAD_CONFIG_LOG_COAP 1
#define OPENTHREAD_CONFIG_LOG_DUA 1
#define OPENTHREAD_CONFIG_LOG_ICMP 1
#define OPENTHREAD_CONFIG_LOG_IP6 1
#define OPENTHREAD_CONFIG_LOG_MAC 1
#define OPENTHREAD_CONFIG_LOG_MEM 1
#define OPENTHREAD_CONFIG_LOG_MESHCOP 1
#define OPENTHREAD_CONFIG_LOG_MLE 1
#define OPENTHREAD_CONFIG_LOG_MLR 1
#define OPENTHREAD_CONFIG_LOG_NETDATA 1
#define OPENTHREAD_CONFIG_LOG_NETDIAG 1
#define OPENTHREAD_CONFIG_LOG_PKT_DUMP 1
#define OPENTHREAD_CONFIG_LOG_PLATFORM 1

/**
 * @def OPENTHREAD_CONFIG_NUM_MESSAGE_BUFFERS
 *
 * 缓冲池中的消息缓冲区数
 */
#define OPENTHREAD_CONFIG_NUM_MESSAGE_BUFFERS CONFIG_OPENTHREAD_NUM_MESSAGE_BUFFERS

/**
 * @def OPENTHREAD_CONFIG_COAP_API_ENABLE
 *
 * 定义为1以启用CoAP API。
 *
 */
#define OPENTHREAD_CONFIG_COAP_API_ENABLE 1


/**
 * @def OPENTHREAD_CONFIG_PLATFORM_NETIF_ENABLE
 *
 * 定义为1以启用平台NETIF支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_NETIF_ENABLE
#define OPENTHREAD_CONFIG_PLATFORM_NETIF_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_HEAP_EXTERNAL_ENABLE
 *
 * 启用外部堆。
 *
 */
#ifndef OPENTHREAD_CONFIG_HEAP_EXTERNAL_ENABLE
#define OPENTHREAD_CONFIG_HEAP_EXTERNAL_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_TCP_ENABLE
 *
 * 定义为0以禁用TCP
 *
 */
#ifndef OPENTHREAD_CONFIG_TCP_ENABLE
#define OPENTHREAD_CONFIG_TCP_ENABLE 0
#endif

#if CONFIG_OPENTHREAD_BORDER_ROUTER

/**
 * @def OPENTHREAD_CONFIG_BORDER_AGENT_ENABLE
 *
 * 定义为1以启用边界代理支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_BORDER_AGENT_ENABLE
#define OPENTHREAD_CONFIG_BORDER_AGENT_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
 *
 * 定义为1以启用边界路由器支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
#define OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_BORDER_ROUTING_ENABLE
 *
 * 定义为1以启用边界路由支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_BORDER_ROUTING_ENABLE
#define OPENTHREAD_CONFIG_BORDER_ROUTING_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_UDP_ENABLE
 *
 * 定义为1以启用平台UDP支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_UDP_ENABLE
#define OPENTHREAD_CONFIG_PLATFORM_UDP_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_ECDSA_ENABLE
 *
 * 定义为1以启用ECDSA支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_ECDSA_ENABLE
#define OPENTHREAD_CONFIG_ECDSA_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_SRP_SERVER_ENABLE
 *
 * 定义为1以启用SRP服务器支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_SRP_SERVER_ENABLE
#define OPENTHREAD_CONFIG_SRP_SERVER_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_DNSSD_SERVER_ENABLE
 *
 * 定义为1以启用DNS-SD服务器支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_DNSSD_SERVER_ENABLE
#define OPENTHREAD_CONFIG_DNSSD_SERVER_ENABLE 1
#endif

#endif // CONFIG_OPENTHREAD_BORDER_ROUTER

/**
 * @def OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE
 *
 * 定义为1以启用螺纹测试线束参考设备支持。
 *
 */
#define OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_CHILD_SUPERVISION_ENABLE
 *
 * 定义为1以启用儿童监督支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_CHILD_SUPERVISION_ENABLE
#define OPENTHREAD_CONFIG_CHILD_SUPERVISION_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_DHCP6_CLIENT_ENABLE
 *
 * 定义为1以启用DHCPv6客户端支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_DHCP6_CLIENT_ENABLE
#define OPENTHREAD_CONFIG_DHCP6_CLIENT_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_DHCP6_SERVER_ENABLE
 *
 * 定义为1以启用DHCPv6服务器支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_DHCP6_SERVER_ENABLE
#define OPENTHREAD_CONFIG_DHCP6_SERVER_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_DNS_CLIENT_ENABLE
 *
 * 定义为1以启用DNS客户端支持。
 *
 */
#ifndef OPENTHREAD_CONFIG_DNS_CLIENT_ENABLE
#define OPENTHREAD_CONFIG_DNS_CLIENT_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_SPI_ENABLE
 *
 * 定义为1以启用NCP SPI支持。
 *
 */
#define OPENTHREAD_CONFIG_NCP_SPI_ENABLE 0

/**
 * @def OPENTHREAD_ENABLE_NCP_SPINEL_ENCRYPTER
 *
 * 定义为1以启用NCP Spinel加密器。
 *
 */
#define OPENTHREAD_ENABLE_NCP_SPINEL_ENCRYPTER 0

/**
 * @def OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
 *
 * 定义为1以启用NCP HDLC支持。
 *
 */
#define OPENTHREAD_CONFIG_NCP_HDLC_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE
 *
 * 定义为1以支持将服务条目注入线程网络数据。
 *
 */
#define OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE 1

/**
 * @def PACKAGE_NAME
 *
 * 定义为此包的全名。
 *
 */
#define PACKAGE_NAME "openthread-esp32"

/**
 * @def PACKAGE_STRING
 *
 * 定义此包的全名和版本。
 *
 */
#define PACKAGE_STRING (PACKAGE_NAME " - " PACKAGE_VERSION)

/**
 * @def OPENTHREAD_CONFIG_ENABLE_BUILTIN_MBEDTLS
 *
 * 定义为1以启用bultin mbedtls。
 *
 * 请注意，OPENTHREAD_COONFIG_ENABLE_BUILTIN_MBEDTLS决定是否使用bultin MBEDTLS以及是否在内部管理MBEDTLS，例如内存分配和调试。
 *
 */
#define OPENTHREAD_CONFIG_ENABLE_BUILTIN_MBEDTLS 0

/**
 * @def OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE
 *
 * 定义为1，以支持OpenThread添加自动配置的SLAC地址。
 *
 */
#define OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_MAX_STATECHANGE_HANDLERS
 *
 * 状态更改回调处理程序的最大数量（使用“otSetStateChangedCallback（）”设置）。
 *
 */
#define OPENTHREAD_CONFIG_MAX_STATECHANGE_HANDLERS 3

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_RADIO_SPINEL_RX_FRAME_BUFFER_SIZE
 *
 * 指定RCP主机代码中“SpinelInterface”使用的rx帧缓冲区大小。这在使用“RadioSpinel”平台时适用/使用。
 *
 */
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_SPINEL_RX_FRAME_BUFFER_SIZE 1024

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_USEC_TIMER_ENABLE
 *
 * 定义为1以启用微秒计时器。
 *
 */
#define OPENTHREAD_CONFIG_PLATFORM_USEC_TIMER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_PING_SENDER_ENABLE
 *
 * 定义为1以启用ping发送器模块。
 *
 * Ping发送方模块实现发送ICMPv6回显请求消息和处理ICMPv6回复消息。
 *
 */
#define OPENTHREAD_CONFIG_PING_SENDER_ENABLE 1

/**
 * @def OPENTHREAD_CONFIG_DTLS_MAX_CONTENT_LEN
 *
 * OpenThread dtls内容缓冲区的最大长度。
 *
 */
#ifndef OPENTHREAD_CONFIG_DTLS_MAX_CONTENT_LEN
#define OPENTHREAD_CONFIG_DTLS_MAX_CONTENT_LEN 768
#endif

/**
 * 通过Kconfig的可配置定义
 */
#if CONFIG_OPENTHREAD_COMMISSIONER
#define OPENTHREAD_CONFIG_COMMISSIONER_ENABLE 1
#endif

#if CONFIG_OPENTHREAD_JOINER
#define OPENTHREAD_CONFIG_JOINER_ENABLE 1
#endif

#if CONFIG_OPENTHREAD_DIAG
#define OPENTHREAD_CONFIG_DIAG_ENABLE 1
#endif

#if CONFIG_OPENTHREAD_SRP_CLIENT
#ifndef OPENTHREAD_CONFIG_ECDSA_ENABLE
#define OPENTHREAD_CONFIG_ECDSA_ENABLE 1
#endif

#ifndef OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE
#define OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE 1
#endif
#endif

#if CONFIG_OPENTHREAD_FTD
#define OPENTHREAD_FTD 1
#elif CONFIG_OPENTHREAD_MTD
#define OPENTHREAD_MTD 1
#elif CONFIG_OPENTHREAD_RADIO
#define OPENTHREAD_RADIO 1
#endif
