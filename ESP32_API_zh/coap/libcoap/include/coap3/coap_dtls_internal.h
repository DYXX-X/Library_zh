/*
 * coap_dtls_内部。h——libcoap的（数据报）传输层支持
 *
 * Copyright (C) 2016 Olaf Bergmann <bergmann@tzi.org> 版权所有（C）2017 Jean-Claude Michelou<jcm@spinetix.com>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_DTLS_INTERNAL_H_
#define COAP_DTLS_INTERNAL_H_

/**
 * @defgroup dtls_internal dtls支持（内部）CoAP dtls结构、枚举和不向应用程序公开的函数@{
 */

/* https://tools.ietf.org/html/rfc6347#section-4.2.4.1 */
#ifndef COAP_DTLS_RETRANSMIT_MS
#define COAP_DTLS_RETRANSMIT_MS 1000
#endif
#ifndef COAP_DTLS_RETRANSMIT_TOTAL_MS
#define COAP_DTLS_RETRANSMIT_TOTAL_MS 60000
#endif

#define COAP_DTLS_RETRANSMIT_COAP_TICKS (COAP_DTLS_RETRANSMIT_MS * COAP_TICKS_PER_SECOND / 1000)

/**
 * Creates a new DTLS context for the given @p coap_context。此函数返回指向新的DTLS上下文对象的指针，或出错时返回@c NULL。
 *
 * @param coap_context 应使用DTLS对象的CoAP上下文。
 *
 * @return 出现错误时，DTLS上下文对象或@c NULL。
 */
void *
coap_dtls_new_context(coap_context_t *coap_context);

/**
 * 设置DTLS上下文的默认服务器PSK信息。这将在coap_dtls_new_context（）之后执行PSK细节。
 *
 * @param coap_context CoAP上下文。
 * @param setup_data 包含最初传递到coap_context_set_psk2（）中的设置数据的结构。
 *
 * @return @c 1如果成功，否则@c 0。
 */

int
coap_dtls_context_set_spsk(coap_context_t *coap_context,
                          coap_dtls_spsk_t *setup_data);

/**
 * 设置DTLS上下文的默认客户端PSK信息。这将在coap_dtls_new_context（）之后执行PSK细节。
 *
 * @param coap_context CoAP上下文。
 * @param setup_data 包含最初传递到coap_new_client_session_psk2（）中的设置数据的结构。
 *
 * @return @c 1如果成功，否则@c 0。
 */

int
coap_dtls_context_set_cpsk(coap_context_t *coap_context,
                          coap_dtls_cpsk_t *setup_data);

/**
 * 设置DTLS上下文的默认服务器PKI信息。这完成了coap_dtls_new_context（）之后的PKI细节。
 * If @p COAP_DTLS_ROLE_SERVER，则信息将被放入TLS库的上下文中（会话是从中派生的）。
 * If @p COAP_DTLS_ROLE_CLIENT，则信息将被放入TLS库的会话中。
 *
 * @param coap_context CoAP上下文。
 * @param setup_data     定义如何设置PKI的设置信息。必需参数。如果@p为NULL，则不会设置PKI。
 * @param role  @p COAP_DTLS_ROLE_CLIENT或@p COUP_DTLS_OLE_SERVER之一
 *
 * @return @c 1如果成功，否则@c 0。
 */

int
coap_dtls_context_set_pki(coap_context_t *coap_context,
                          const coap_dtls_pki_t *setup_data,
                          const coap_dtls_role_t role);

/**
 * 为客户端或服务器设置dtls上下文的默认根CA信息。
 *
 * @param coap_context   当前coap_context_t对象。
 * @param ca_file        如果不是@p NULL，则是包含要使用的所有根CA的PEM编码文件的完整路径名。
 * @param ca_dir         如果不是@p NULL，则指向包含PEM编码文件的目录，其中包含要使用的所有根CA。
 *
 * @return @c 1如果成功，否则@c 0。
 */

int
coap_dtls_context_set_pki_root_cas(coap_context_t *coap_context,
                                   const char *ca_file,
                                   const char *ca_dir);

/**
 * 检查是否调用了coap_dtls_context_set_{psk|pki}（）函数之一。
 *
 * @param coap_context 当前coap_context_t对象。
 *
 * @return @c 1如果调用了coap_dtls_context_set_{psk|pki}（），否则@c 0。
 */

int coap_dtls_context_check_keys_enabled(coap_context_t *coap_context);

/**
 * 释放为@p dtls_context分配的存储。
 *
 * @param dtls_context coap_DTLS_new_context（）返回的DTLS上下文。
 */
void coap_dtls_free_context(void *dtls_context);

/**
 * 创建新的客户端会话。这将向服务器发送HELLO。
 *
 * @param coap_session   CoAP会话。
 *
 * @return 包含会话安全参数的基础TLS库对象的不透明句柄。
*/
void *coap_dtls_new_client_session(coap_session_t *coap_session);

/**
 * Create a new DTLS server-side session. Called after coap_dtls_hello() has returned @c 1，用信号通知从客户端接收到经验证的HELLO。这将向服务器发送HELLO。
 *
 * @param coap_session   CoAP会话。
 *
 * @return 包含DTLS会话安全参数的底层TLS库对象的不透明句柄。
 */
void *coap_dtls_new_server_session(coap_session_t *coap_session);

/**
 * 终止DTLS会话（如果需要，可以发送ALERT），然后释放包含会话安全参数的底层TLS库对象。
 *
 * @param coap_session   CoAP会话。
 */
void coap_dtls_free_session(coap_session_t *coap_session);

/**
 * 通知CoAP会话的MTU发生变化，例如在PMTU更新之后。
 *
 * @param coap_session   CoAP会话。
 */
void coap_dtls_session_update_mtu(coap_session_t *coap_session);

/**
 * 向DTLS对等端发送数据。
 *
 * @param coap_session CoAP会话。
 * @param data      指向数据的指针。
 * @param data_len  要发送的字节数。
 *
 * @return @如果这是阻塞，则为c0；如果有错误或发送的明文字节数，则为@c-1。
 */
int coap_dtls_send(coap_session_t *coap_session,
                   const uint8_t *data,
                   size_t data_len);

/**
 * 检查是否按CoAP会话或CoAP上下文处理超时。
 *
 * @return @超时和重传的c1是每个上下文，如果是每个会话，则为@c 0。
 */
int coap_dtls_is_context_timeout(void);

/**
 * 执行所有挂起的重传并获得下一个超时
 *
 * @param dtls_context DTLS上下文。
 *
 * @return @c 0，如果没有未决事件或下一次重传的日期。
 */
coap_tick_t coap_dtls_get_context_timeout(void *dtls_context);

/**
 * 获取此会话的下一个超时。
 *
 * @param coap_session CoAP会话。
 * @param now 当前时间（以刻度为单位）。
 *
 * @return @c 0如果没有事件挂起或标记下一次重新传输的时间。
 */
coap_tick_t coap_dtls_get_timeout(coap_session_t *coap_session,
                                  coap_tick_t now);

/**
 * 处理DTLS超时过期。
 *
 * @param coap_session CoAP会话。
 */
void coap_dtls_handle_timeout(coap_session_t *coap_session);

/**
 * 处理来自DTLS对等端的传入数据。
 *
 * @param coap_session CoAP会话。
 * @param data      加密数据报。
 * @param data_len  加密数据报大小。
 *
 * @return 已解密coap PDU上coap_handle_dgram的结果
 *         or @c -1表示错误。
 */
int coap_dtls_receive(coap_session_t *coap_session,
                      const uint8_t *data,
                      size_t data_len);

/**
 * 处理来自新candiate对等体的客户端HELLO消息。请注意，session->tls为空。
 *
 * @param coap_session CoAP会话。
 * @param data      加密数据报。
 * @param data_len  加密数据报大小。
 *
 * @return @c 0如果已发送cookie验证消息，@c 1如果HELLO包含有效cookie并且应创建服务器会话，
 *        @c -如果消息无效，则返回1。
 */
int coap_dtls_hello(coap_session_t *coap_session,
                    const uint8_t *data,
                    size_t data_len);

/**
 * 通过明文PDU获取DTLS开销。
 *
 * @param coap_session CoAP会话。
 *
 * @return DTLS层添加的最大字节数。
 */
unsigned int coap_dtls_get_overhead(coap_session_t *coap_session);

/**
 * 创建新的TLS客户端会话。
 *
 * @param coap_session CoAP会话。
 * @param connected 更新连接是否已连接。
 *                  @c 0未连接，@c 1已连接。
 *
 * @return 包含会话安全参数的基础TLS库对象的不透明句柄。
*/
void *coap_tls_new_client_session(coap_session_t *coap_session, int *connected);

/**
 * 创建TLS新的服务器端会话。
 *
 * @param coap_session CoAP会话。
 * @param connected 更新连接是否已连接。
 *                  @c 0未连接，@c 1已连接。
 *
 * @return 包含会话安全参数的基础TLS库对象的不透明句柄。
 */
void *coap_tls_new_server_session(coap_session_t *coap_session, int *connected);

/**
 * 终止TLS会话（必要时可发送警报），然后释放包含会话安全参数的底层TLS库对象。
 *
 * @param coap_session CoAP会话。
 */
void coap_tls_free_session( coap_session_t *coap_session );

/**
 * 使用隐式刷新将数据发送到TLS对等端。
 *
 * @param coap_session CoAP会话。
 * @param data      指向数据的指针。
 * @param data_len  要发送的字节数。
 *
 * @return          @c 0如果应该重试，@c-1如果有错误或发送的明文字节数。
 */
ssize_t coap_tls_write(coap_session_t *coap_session,
                       const uint8_t *data,
                       size_t data_len
                       );

/**
 * 从TLS对等端读取一些数据。
 *
 * @param coap_session CoAP会话。
 * @param data      指向数据的指针。
 * @param data_len  要读取的最大字节数。
 *
 * @return          @c 0如果应该重试，@c-1如果有错误或读取的明文字节数。
 */
ssize_t coap_tls_read(coap_session_t *coap_session,
                      uint8_t *data,
                      size_t data_len
                      );

/**
 * 初始化底层（D）TLS库层。
 *
 */
void coap_dtls_startup(void);

/**
 * 关闭底层（D）TLS库层。
 *
 */
void coap_dtls_shutdown(void);

/**
 * 获取会话的实际（D）TLS对象。
 *
 * @param session 会议。
 * @param tls_lib 已更新库类型。
 *
 * @return TLS信息。
 */
void *coap_dtls_get_tls(const coap_session_t *session,
                        coap_tls_library_t *tls_lib);

/** @} */

#endif /* COAP_DTLS_INTERNAL_H */

