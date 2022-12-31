/*
 * coap_subscribe_internal。h——不暴露于应用程序编程的结构、枚举和函数
 *
 * 版权所有（C）2010-2021 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_subscribe_internal.h
 * @brief COAP订阅内部信息
 */

#ifndef COAP_SUBSCRIBE_INTERNAL_H_
#define COAP_SUBSCRIBE_INTERNAL_H_

/**
 * @defgroup subscribe_internal Observe Subscription（内部）CoAP Observe未向应用程序公开的订阅结构、枚举和函数@{
 */

#ifndef COAP_OBS_MAX_NON
/**
 * 在发送可确认消息以检测观察者是否活动之前，可能发送的不可确认通知数。此处允许的最大值为@c 15。
 */
#define COAP_OBS_MAX_NON   5
#endif /* COAP_OBS_MAX_NON */

#ifndef COAP_OBS_MAX_FAIL
/**
 * 删除观察者之前可能失败（即超时而未确认）的可确认通知数。COAP_OBS_MAX_FAIL的最大值为@c 3。
 */
#define COAP_OBS_MAX_FAIL  3
#endif /* COAP_OBS_MAX_FAIL */

/**订阅者信息*/
struct coap_subscription_t {
  struct coap_subscription_t *next; /**<链接列表中的下一个元素*/
  struct coap_session_t *session;   /**<订户会话*/

  unsigned int non_cnt:4;  /**<最多允许15个不可确认的通知*/
  unsigned int fail_cnt:2; /**<最多3个可确认通知可能失败*/
  unsigned int dirty:1;    /**<set如果暂时无法发送通知（在这种情况下，也会设置资源的部分脏标志）*/
  coap_cache_key_t *cache_key; /**用于标识请求者的cache_key*/
  coap_pdu_t *pdu;         /**<用于其他请求的PDU*/
};

void coap_subscription_init(coap_subscription_t *);

/**
 * 处理失败的观察通知。
 *
 * @param context 保存资源的上下文。
 * @param session 观察通知失败的会话。
 * @param token 观察通知失败时使用的令牌。
 */
void
coap_handle_failed_notify(coap_context_t *context,
                          coap_session_t *session,
                          const coap_binary_t *token);

/**
 * 检查所有已知资源以查看它们是否已损坏，然后通知订阅的观察者。
 *
 * @param context 要检查脏资源的上下文。
 */
void coap_check_notify(coap_context_t *context);

/**
 * 将指定的对等方添加为@p资源的观察者。订阅是
 * identified by the given @p 代币此函数返回注册的
 * subscription information if the @p 已添加观察者，或出现错误时@c为NULL。
 *
 * @param resource        观察到的资源。
 * @param session         观察员会议
 * @param token           标识此订阅的令牌。
 * @param pdu             请求pdu。
 *
 * @return                指向添加/更新的订阅信息的指针，或出现错误时的@c NULL。
 */
coap_subscription_t *coap_add_observer(coap_resource_t *resource,
                                       coap_session_t *session,
                                       const coap_binary_t *token,
                                       const coap_pdu_t *pdu);

/**
 * 返回给定@p对等方的订阅对象。
 *
 * @param resource 观察到的资源。
 * @param session  观察员会议
 * @param token    标识此订阅的令牌或任何令牌的@c NULL。
 * @return         如果存在，则为有效订阅，否则为@c NULL。
 */
coap_subscription_t *coap_find_observer(coap_resource_t *resource,
                                        coap_session_t *session,
                                        const coap_binary_t *token);

/**
 * 标记数据已准备好发送给观察者。
 *
 * @param context  要使用的CoAP上下文。
 * @param session  观察员会议
 * @param token    已用于订阅的相应令牌。
 */
void coap_touch_observer(coap_context_t *context,
                         coap_session_t *session,
                         const coap_binary_t *token);

/**
 * Removes any subscription for @p 来自@p资源的观察者，并发布
 * allocated storage. The result is @c 1如果与@p存在观察关系
 * observer and @p 令牌存在，否则@c 0。
 *
 * @param resource 观察到的资源。
 * @param session  观察员会议。
 * @param token    标识此订阅的令牌或任何令牌的@c NULL。
 * @return         @如果观察者已被删除，则为c 1，否则为@c 0。
 */
int coap_delete_observer(coap_resource_t *resource,
                         coap_session_t *session,
                         const coap_binary_t *token);

/**
 * Removes any subscription for @p 会话并释放分配的存储。
 *
 * @param context  要使用的CoAP上下文。
 * @param session  观察员会议。
 */
void coap_delete_observers(coap_context_t *context, coap_session_t *session);

/** @} */

#endif /* COAP_SUBSCRIBE_INTERNAL_H_ */

