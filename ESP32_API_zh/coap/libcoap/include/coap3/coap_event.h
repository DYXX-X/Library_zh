/*
 * coap_事件。h—libcoap事件API
 *
 * 版权所有（C）2016奥拉夫·伯格曼<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_EVENT_H_
#define COAP_EVENT_H_

#include "libcoap.h"

/**
 * @defgroup 事件事件API API函数，用于从较低层库函数传递事件@{
 */

/**
 * 表示不同事件的标量类型，例如DTLS事件或重传超时。
 */
typedef enum coap_event_t {
/**
 * （D） COAP_PROTO_DTLS和COAP_PPROTO_TLS的TLS事件
 */
  COAP_EVENT_DTLS_CLOSED       = 0x0000,
  COAP_EVENT_DTLS_CONNECTED    = 0x01DE,
  COAP_EVENT_DTLS_RENEGOTIATE  = 0x01DF,
  COAP_EVENT_DTLS_ERROR        = 0x0200,

/**
 * COAP_PROTO_TCP和COAP_PPROTO_TLS的TCP事件
 */
  COAP_EVENT_TCP_CONNECTED     = 0x1001,
  COAP_EVENT_TCP_CLOSED        = 0x1002,
  COAP_EVENT_TCP_FAILED        = 0x1003,

/**
 * CSM仅为可靠协议交换事件
 */
  COAP_EVENT_SESSION_CONNECTED = 0x2001,
  COAP_EVENT_SESSION_CLOSED    = 0x2002,
  COAP_EVENT_SESSION_FAILED    = 0x2003,

/**
 * （Q-）阻止接收错误
 */
  COAP_EVENT_PARTIAL_BLOCK     = 0x3001
} coap_event_t;

/**
 * 可以使用函数CoAP_set_event_handler（）向CoAP上下文注册的事件处理程序函数的类型。当库调用时，第一个参数将是与原始coap上下文关联的当前coap_session_t对象。第二个参数是事件类型。
 */
typedef int (*coap_event_handler_t)(coap_session_t *session,
                                    const coap_event_t event);

/**
 * Registers the function @p hnd作为给定事件的回调
 * CoAP context @p 上下文任何以前
 * registered with @p 此操作将覆盖上下文。
 *
 * @param context 要向其注册事件处理程序的CoAP上下文。
 * @param hnd     要注册的事件处理程序@c如果要取消注册，则为NULL。
 */
void coap_register_event_handler(coap_context_t *context,
                            coap_event_handler_t hnd);

/** @} */

/**
 * Registers the function @p hnd作为给定事件的回调
 * CoAP context @p 上下文任何以前
 * registered with @p 此操作将覆盖上下文。
 *
 * @deprecated 请改用coap_register_event_handler（）。
 *
 * @param context 要向其注册事件处理程序的CoAP上下文。
 * @param hnd     要注册的事件处理程序。
 */
COAP_DEPRECATED
void coap_set_event_handler(coap_context_t *context,
                            coap_event_handler_t hnd);

/**
 * 清除用@p上下文注册的事件处理程序。
 *
 * @deprecated 对hnd使用coap_register_event_handler（）代替NULL。
 *
 * @param context 要删除其事件处理程序的CoAP上下文。
 */
COAP_DEPRECATED
void coap_clear_event_handler(coap_context_t *context);

#endif /* COAP_EVENT_H */

