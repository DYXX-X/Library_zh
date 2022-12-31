/*
 * 异步。h—异步消息的状态管理
 *
 * 版权所有（C）2010-2011 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file 异步.h
 * @brief 异步消息的状态管理
 */

#ifndef COAP_ASYNC_H_
#define COAP_ASYNC_H_

#include "net.h"

/**
 * @defgroup coap_asyncAsynchronous Messaging@｛异步“单独”消息的API函数。coap_context_t对象包含一个coap_assync_t对象列表，在请求的结果无法立即传递的情况下，该列表可用于生成单独的响应。
 */

/**
 * Returns @c 1如果libcoap是在启用单独消息的情况下构建的，
 * @c 否则为0。
 */
int coap_async_is_supported(void);

/**
 * 分配一个新的coap_async_t对象，并根据
 * the given @p 要求此函数返回一个指向已注册
 * coap_async_t object or @c 出现错误时为NULL。请注意，此功能将
 * return @c 如果已注册具有相同标识符的对象，则为NULL。
 *
 * When the delay expires, a copy of the @p 请求将被发送到适当的请求处理程序。
 *
 * @param session  用于异步传输的会话。
 * @param request  异步处理的请求。
 * @param delay    发送响应之前延迟的时间量，0表示永远等待。
 *
 * @return         指向已注册coap_async_t对象的指针，或在发生错误时指向@c NULL。
 */
coap_async_t *
coap_register_async(coap_session_t *session,
                    const coap_pdu_t *request,
                    coap_tick_t delay);

/**
 * 更新延迟超时，以便在注册的@p异步触发时进行更改。
 *
 * 当新的延迟到期时，原始请求的副本将被发送到适当的请求处理程序。
 *
 * @param async 要更新的对象。
 * @param delay    发送响应之前延迟的时间量，0表示永远等待。
 */
void
coap_async_set_delay(coap_async_t *async, coap_tick_t delay);

/**
 * 释放coap_register_async（）为对象@p-async分配的内存。
 *
 * @param session  要使用的会话。
 * @param async 要删除的对象。
 */
void
coap_free_async(coap_session_t *session, coap_async_t *async);

/**
 * Retrieves the object identified by @p 来自注册到@p上下文的异步事务列表的令牌。此函数返回指向该对象的指针，如果找不到则返回@c NULL。
 *
 * @param session 用于异步传输的会话。
 * @param token   要检索的对象的PDU令牌。
 *
 * @return        指向由@p标记标识的对象的指针，如果找不到，则为@c NULL。
 */
coap_async_t *coap_find_async(coap_session_t *session, coap_bin_const_t token);

/**
 * Set the application data pointer held in @p 异步。这将覆盖任何现有的数据指针。
 *
 * @param async 异步状态对象。
 * @param app_data 指向数据的指针。
 */
void coap_async_set_app_data(coap_async_t *async, void *app_data);

/**
 * 获取@p异步中保存的应用程序数据指针。
 *
 * @param async 异步状态对象。
 *
 * @return 应用程序数据指针。
 */
void *coap_async_get_app_data(const coap_async_t *async);

/** @} */

#endif /* COAP_ASYNC_H_ */

