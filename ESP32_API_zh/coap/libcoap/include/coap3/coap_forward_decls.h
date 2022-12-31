/*
 * coap_forward_decls。h——转发对使用libcoap的应用程序编程不透明的结构声明。
 *
 * 版权所有（C）2019-2021 Jon Shallow<supjps-libcoap@jpshallow.com>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file 共同转发条款h
 * @brief COAP正向定义
 */

#ifndef COAP_FORWARD_DECLS_H_
#define COAP_FORWARD_DECLS_H_

/*
 * 定义结构的前向声明（甚至是非不透明的），以便应用程序（使用coap.h）和libcoap构建可以引用它们（并使.h文件依赖关系更简单）。
 */
struct coap_address_t;
struct coap_bin_const_t;
struct coap_dtls_pki_t;
struct coap_str_const_t;
struct coap_string_t;

/*
 * typedef coap_*_internal.h中定义的所有不透明结构
 */

/* *************coap_async_内部。小时******************/

/**
 * 异步条目信息。
 */
typedef struct coap_async_t coap_async_t;

/* *************coap_block_内部。小时******************/

/*
 * 块处理信息。
 */
typedef struct coap_lg_xmit_t coap_lg_xmit_t;
typedef struct coap_lg_crcv_t coap_lg_crcv_t;
typedef struct coap_lg_srcv_t coap_lg_srcv_t;

/* *************coap_cache_内部。小时******************/

/*
 * 缓存条目信息。
 */
typedef struct coap_cache_entry_t coap_cache_entry_t;
typedef struct coap_cache_key_t coap_cache_key_t;

/* *************coap_io_内部。小时******************/

/**
 * socket_ t和coap_packet_。
 */
typedef struct coap_packet_t coap_packet_t;
typedef struct coap_socket_t coap_socket_t;

/* *************coap_net_内部。小时******************/

/*
 * 净信息。
 */
typedef struct coap_context_t coap_context_t;
typedef struct coap_queue_t coap_queue_t;

/* *************coap_pdu_内部。小时******************/

/**
 * PDU信息。
 */
typedef struct coap_pdu_t coap_pdu_t;

/* *************coap_resource_internal。小时******************/

/*
 * 资源信息。
 */
typedef struct coap_attr_t coap_attr_t;
typedef struct coap_resource_t coap_resource_t;

/* *************coap_session_内部。小时******************/

/*
 * 会话信息。
 */
typedef struct coap_addr_hash_t coap_addr_hash_t;
typedef struct coap_endpoint_t coap_endpoint_t;
typedef struct coap_session_t coap_session_t;

/* *************coap_subscribe_internal。小时******************/

/*
 * 观察用户信息。
 */
typedef struct coap_subscription_t coap_subscription_t;

#endif /* COAP_FORWARD_DECLS_H_ */

