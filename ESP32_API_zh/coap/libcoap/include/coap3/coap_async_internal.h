/*
 * coap_async_内部。h—异步消息的状态管理
 *
 * 版权所有（C）2010-2021 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_async_内部.h
 * @brief CoAP异步内部信息
 */

#ifndef COAP_ASYNC_INTERNAL_H_
#define COAP_ASYNC_INTERNAL_H_

#include "coap3/net.h"

#ifndef WITHOUT_ASYNC

/**
 * @defgroup coap_async_internal异步消息传递（内部）@{coap异步结构、枚举和函数，它们不向应用程序公开。coap_context_t对象包含coap_assync_t对象的列表，在请求的结果无法立即传递的情况下，这些对象可用于生成单独的响应。
 */
struct coap_async_t {
  struct coap_async_t *next; /**<内部用于链接*/
  coap_tick_t delay;    /**<何时在触发响应之前延迟到0表示从不触发*/
  coap_session_t *session;         /**<交易会话*/
  coap_pdu_t *pdu;                 /**<请求pdu的副本*/
  void* appdata;                   /**用户可定义的数据指针*/
};

/**
 * 检查是否有任何挂起的异步请求-如果有，将其发送出去。否则返回下一个异步触发的剩余时间，如果无需执行，则返回0。
 *
 * @param context 当前上下文。
 * @param now     当前时间（以刻度为单位）。
 *
 * @return 需要执行下一个异步之前的滴答时间，如果无需执行，则为0。
 */
coap_tick_t coap_check_async(coap_context_t *context, coap_tick_t now);

/**
 * 删除并释放给定上下文的所有异步条目。
 *
 * @param context 要从中删除所有异步项的上下文。
 */
void
coap_delete_all_async(coap_context_t *context);

/** @} */

#endif /*  WITHOUT_ASYNC */

#endif /* COAP_ASYNC_INTERNAL_H_ */

