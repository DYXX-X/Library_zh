/*
 * coap_context_internal。h——不暴露于应用程序编程的结构、枚举和函数
 *
 * 版权所有（C）2010-2021 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_net_内部.h
 * @brief COAP净内部信息
 */

#ifndef COAP_NET_INTERNAL_H_
#define COAP_NET_INTERNAL_H_

/**
 * @defgroup context_internal上下文处理（内部）未向应用程序公开的CoAP上下文结构、枚举和函数@{
 */

/**
 * 队列条目
 */
struct coap_queue_t {
  struct coap_queue_t *next;
  coap_tick_t t;                /**<下次发送PDU的时间*/
  unsigned char retransmit_cnt; /**<重传计数器，将在为零时删除**/
  unsigned int timeout;         /**<随机化超时值*/
  coap_session_t *session;      /**<CoAP会话*/
  coap_mid_t id;                /**<CoAP消息id*/
  coap_pdu_t *pdu;              /**<要发送的CoAP PDU*/
};

/**
 * CoAP堆栈的全局状态存储在CoAP_context_t对象中。
 */
struct coap_context_t {
  coap_opt_filter_t known_options;
  coap_resource_t *resources; /**<哈希表或已知资源列表*/
  coap_resource_t *unknown_resource; /**<可用于处理未知资源*/
  coap_resource_t *proxy_uri_resource; /**<可用于处理代理URI资源*/
  coap_resource_release_userdata_handler_t release_userdata;
                                        /**<删除资源时释放user_data的函数*/

#ifndef WITHOUT_ASYNC
  /**异步消息ID列表*/
  coap_async_t *async_state;
#endif /* WITHOUT_ASYNC */

  /**
   * sendque的第一个元素中的时间戳与sendqueue_basetime相关。*/
  coap_tick_t sendqueue_basetime;
  coap_queue_t *sendqueue;
  coap_endpoint_t *endpoint;      /**<用于侦听的端点*/
  coap_session_t *sessions;       /**<客户端会话*/

#ifdef WITH_CONTIKI
  struct uip_udp_conn *conn;      /**<uIP连接对象*/
  struct etimer retransmit_timer; /**<必须发送下一个数据包时激发*/
  struct etimer notify_timer;     /**<用于定期检查资源*/
#endif /* WITH_CONTIKI */

#ifdef WITH_LWIP
  uint8_t timer_configured;       /**<当使用lwIP计时器为此*上下文调度重传时，设置为1，否则为0。*/
#endif /* WITH_LWIP */

  coap_response_handler_t response_handler;
  coap_nack_handler_t nack_handler;
  coap_ping_handler_t ping_handler;
  coap_pong_handler_t pong_handler;

  /**
   * 回调函数，用于向应用程序发送事件信号。此字段由coap_set_event_handler（）设置。
   */
  coap_event_handler_t handle_event;

  ssize_t (*network_send)(coap_socket_t *sock, const coap_session_t *session,
                          const uint8_t *data, size_t datalen);

  ssize_t (*network_read)(coap_socket_t *sock, coap_packet_t *packet);

  size_t(*get_client_psk)(const coap_session_t *session, const uint8_t *hint,
                          size_t hint_len, uint8_t *identity,
                          size_t *identity_len, size_t max_identity_len,
                          uint8_t *psk, size_t max_psk_len);
  size_t(*get_server_psk)(const coap_session_t *session,
                          const uint8_t *identity, size_t identity_len,
                          uint8_t *psk, size_t max_psk_len);
  size_t(*get_server_hint)(const coap_session_t *session, uint8_t *hint,
                          size_t max_hint_len);

  void *dtls_context;

  coap_dtls_spsk_t spsk_setup_data;  /**<包含初始PSK服务器设置数据*/

  unsigned int session_timeout;    /**<关闭未使用会话的非活动秒数。0表示使用默认值。*/
  unsigned int max_idle_sessions;  /**<每个端点同时未使用的会话的最大数量。0表示没有最大值。*/
  unsigned int max_handshake_sessions; /**<每个端点同时反向会话的最大数量。0表示使用默认值。*/
  unsigned int ping_timeout;           /**<发送ping消息之前的最短非活动时间。0表示禁用。*/
  unsigned int csm_timeout;           /**<等待远程CSM超时。0表示禁用。*/
  uint8_t observe_pending;         /**<观察响应待定*/
  uint8_t block_mode;              /**<零个或多个COAP_BLOCK_或'd选项*/
  uint64_t etag;                   /**<下一个要使用的ETag*/

  coap_cache_entry_t *cache;       /**<CoAP缓存条目缓存*/
  uint16_t *cache_ignore_options;  /**<创建缓存密钥时要忽略的CoAP选项*/
  size_t cache_ignore_count;       /**<创建缓存密钥时要忽略的CoAP选项数*/
  void *app;                       /**<应用程序特定数据*/
#ifdef COAP_EPOLL_SUPPORT
  int epfd;                        /**<epoll的外部FD*/
  int eptimerfd;                   /**<内部FD超时*/
  coap_tick_t next_timeout;        /**<下次超时时间*/
#endif /* COAP_EPOLL_SUPPORT */
};

/**
 * Adds @p 节点到给定的@p队列，按@p节点中的变量t排序。
 *
 * @param queue 要添加到的队列。
 * @param node 要添加到队列的节点条目。
 *
 * @return @c 1已添加到队列，@c 0失败。
 */
int coap_insert_node(coap_queue_t **queue, coap_queue_t *node);

/**
 * 销毁指定的@p节点。
 *
 * @param node 要删除的节点条目。
 *
 * @return @c 1节点从队列中删除，@c 0失败。
 */
int coap_delete_node(coap_queue_t *node);

/**
 * Removes all items from given @p 排队并释放分配的存储。
 *
 * 内部功能。
 *
 * @param queue 要删除的队列。
 */
void coap_delete_all(coap_queue_t *queue);

/**
 * 创建适合添加到CoAP发送队列的新节点。
 *
 * @return 新节点条目，如果失败，则@c NULL。
 */
coap_queue_t *coap_new_node(void);

/**
 * Set sendqueue_basetime in the given context object @p ctx到@p现在。此函数返回队列头中超时的元素数。
 */
unsigned int coap_adjust_basetime(coap_context_t *ctx, coap_tick_t now);

/**
 * 返回要发送的下一个pdu，而不从sendque中删除。
 */
coap_queue_t *coap_peek_next( coap_context_t *context );

/**
 * 返回要发送的下一个pdu并将其从sendque中删除。
 */
coap_queue_t *coap_pop_next( coap_context_t *context );

/**
 * 处理可确认消息的重传
 *
 * @param context      CoAP上下文。
 * @param node         要重新传输的节点。
 *
 * @return             发送消息的消息id或出错时的@c COAP_INVALID_MID。
 */
coap_mid_t coap_retransmit(coap_context_t *context, coap_queue_t *node);

/**
 * 使用上下文@p ctx分析和解释CoAP数据报。此函数
 * returns @c 如果数据报已处理，则为0，或错误时为小于零的值。
 *
 * @param ctx    当前CoAP上下文。
 * @param session 当前CoAP会话。
 * @param data 接收到的数据包。
 * @param data_len 接收到的数据包的数据长度。
 *
 * @return       @如果消息处理成功，则为c 0，或出错时小于0。
 */
int coap_handle_dgram(coap_context_t *ctx, coap_session_t *session, uint8_t *data, size_t data_len);

/**
 * 此函数从列表给定列表中删除具有给定@p id的元素。
 * If @p 找到了id，@p节点被更新为指向已删除的元素。笔记
 * that the storage allocated by @p 节点@b未释放。调用者必须使用coap_delete_node（）手动执行此操作。如果
 * element with id @p 找到id，否则为@c 0。对于@c 0的返回值，
 * the contents of @p 节点未定义。
 *
 * @param queue 要搜索@p id的队列。
 * @param session 要查找的会话。
 * @param id    要查找的邮件id。
 * @param node  如果找到，将更新@p节点以指向已删除的节点。必须手动释放@p节点指向的存储。
 *
 * @return      @如果找到@p id，则为c 1，否则为@c 0。
 */
int coap_remove_from_queue(coap_queue_t **queue,
                           coap_session_t *session,
                           coap_mid_t id,
                           coap_queue_t **node);

coap_mid_t
coap_wait_ack( coap_context_t *context, coap_session_t *session,
               coap_queue_t *node);

/**
 * 取消具有指定令牌的会话@p会话的所有未完成消息。
 *
 * @param context      正在使用的上下文。
 * @param session      要删除的邮件会话。
 * @param token        消息令牌。
 * @param token_length @p标记的实际长度。
 */
void coap_cancel_all_messages(coap_context_t *context,
                              coap_session_t *session,
                              const uint8_t *token,
                              size_t token_length);

/**
* 取消会话@p会话的所有未完成消息。
*
* @param context      正在使用的上下文。
* @param session      要删除的邮件会话。
* @param reason       会话取消的原因
*/
void
coap_cancel_session_messages(coap_context_t *context,
                             coap_session_t *session,
                             coap_nack_reason_t reason);

/**
 * 在给定上下文中从接收队列中调度PDU。
 */
void coap_dispatch(coap_context_t *context, coap_session_t *session,
                   coap_pdu_t *pdu);

/**
 * Verifies that @p pdu不包含未知的关键选项。选项必须为
 * registered at @p ctx，使用函数coap_register_option（）。coap_new_context（）自动注册一组基本选项。此函数
 * returns @c 如果@p pdu正常，则为1，否则为@c 0。将使用未知选项更新给定的筛选器对象@p unknown。由于只有@c COAP_MAX_OPT选项可以通过这种方式发出信号，因此必须手动检查其余选项。
 *
 * @code
  coap_opt_filter_t f=coap_opt_NONE；
  coap_opt_iterator_topt_iter；

  如果（coap_option_check_ccritical（ctx，pdu，f）==0）{
    coap_option_iterator_init（pdu，&opt_iter，f）；

    while（coap_option_next（&opt_iter））{
      如果（opt_iter.type&0x01）{
        …处理opt_iter中的未知关键选项。。。
      }
    }
  }
   @结束代码
 *
 * @param ctx      注册所有已知选项的上下文。
 * @param pdu      要检查的PDU。
 * @param unknown  将更新的输出筛选器，以指示在@p pdu中找到的未知关键选项。
 *
 * @return         @c 1如果一切正常，@c 0否则。
 */
int coap_option_check_critical(coap_context_t *ctx,
                               coap_pdu_t *pdu,
                               coap_opt_filter_t *unknown);

/**
 * Creates a new response for given @p 请求的内容为@c.knowledge/core。错误时的结果为NULL，或新分配的PDU必须使用coap_sent（）发送或由coap_delete_PDU（）释放。
 *
 * @param context 要使用的当前coap上下文。
 * @param session CoAP会话。
 * @param request 对@c.knowledge/core的请求。
 *
 * @return        @c.knowledge/core的新2.05响应或出错时为NULL。
 */
coap_pdu_t *coap_wellknown_response(coap_context_t *context,
                                    coap_session_t *session,
                                    coap_pdu_t *request);

/**
 * 根据会话CoAP传输参数“ack_timeout”、“ack_random_factor”和CoAP_TICKS_PER_SECOND计算初始超时。计算要求“ack_timeout”和“ack_random_factor”为Qx。FRAC_BITS定点表示法，而传递的参数@p r被解释为Q0.MAX_BITS随机值的小数部分。
 *
 * @param session 会话超时与
 * @param r  作为Q0.MAX_BITS固定点值的小数部分的随机值
 * @return   COAP_TICKS_PER_SECOND*“确认超时”*（1+（“确认随机因子”-1）r）
 */
unsigned int coap_calc_timeout(coap_session_t *session, unsigned char r);

/**
 * 向给定对等方发送CoAP消息。分配给pdu的内存将由coap_send_internal（）释放。调用coap_send_internal（）后，调用者不能使用pdu。
 *
 * 如果使用块将响应体拆分为多个有效载荷，libcoap将处理后续块的请求以及所需的任何必要恢复。
 *
 * @param session   CoAP会话。
 * @param pdu       要发送的CoAP PDU。
 *
 * @return          发送消息的消息id或出错时的@c COAP_INVALID_MID。
 */
coap_mid_t coap_send_internal(coap_session_t *session, coap_pdu_t *pdu);

/** @} */

#endif /* COAP_NET_INTERNAL_H_ */


