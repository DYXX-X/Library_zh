/*
 * 网h——CoAP网络接口
 *
 * 版权所有（C）2010-2021 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_NET_H_
#define COAP_NET_H_

#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <sys/select.h>
#include <sys/time.h>
#endif
#include <time.h>

#ifdef WITH_LWIP
#include <lwip/ip_addr.h>
#endif

#include "coap_io.h"
#include "coap_dtls.h"
#include "coap_event.h"
#include "pdu.h"
#include "coap_session.h"

/**
 * @defgroup 用于使用CoAP上下文处理PDU的上下文上下文处理API函数@{
 */

typedef enum coap_response_t {
  COAP_RESPONSE_FAIL, /**<响应不受欢迎-发送CoAP RST数据包*/
  COAP_RESPONSE_OK    /**<响应良好*/
} coap_response_t;

/**
 * 在coap_context_t中用作回调的响应处理程序。
 *
 * @param session CoAP会话。
 * @param sent 传输的PDU。
 * @param received 收到的PDU。
 * @param mid CoAP事务ID。

 * @return @如果成功，则返回c COAP_REPONSE_OK，否则返回触发发送RST数据包的@c COAP_RePONSE_FAIL。
 */
typedef coap_response_t (*coap_response_handler_t)(coap_session_t *session,
                                                   const coap_pdu_t *sent,
                                                   const coap_pdu_t *received,
                                                   const coap_mid_t mid);

/**
 * 在coap_context_t中用作回调的负Acknowedge处理程序。
 *
 * @param session CoAP会话。
 * @param sent 传输的PDU。
 * @param reason NACK的原因。
 * @param mid CoAP消息ID。
 */
typedef void (*coap_nack_handler_t)(coap_session_t *session,
                                    const coap_pdu_t *sent,
                                    const coap_nack_reason_t reason,
                                    const coap_mid_t mid);

/**
 * 接收到在coap_context_t中用作回调的Ping处理程序。
 *
 * @param session CoAP会话。
 * @param received 收到的PDU。
 * @param mid CoAP消息ID。
 */
typedef void (*coap_ping_handler_t)(coap_session_t *session,
                                    const coap_pdu_t *received,
                                    const coap_mid_t mid);

/**
 * 接收到用作coap_context_t中回调的Pong处理程序。
 *
 * @param session CoAP会话。
 * @param received 收到的PDU。
 * @param mid CoAP消息ID。
 */
typedef void (*coap_pong_handler_t)(coap_session_t *session,
                                    const coap_pdu_t *received,
                                    const coap_mid_t mid);

/**
 * 注册一个新的消息处理程序，每当收到响应时调用该处理程序。
 *
 * @param context 要为其注册处理程序的上下文。
 * @param handler 要注册的响应处理程序。
 */
void
coap_register_response_handler(coap_context_t *context,
                               coap_response_handler_t handler);

/**
 * 注册一个新的消息处理程序，每当在所有重试操作结束后丢弃可确认消息（请求或响应），或收到第一条消息，或收到网络或TLS级别的事件，表明无法传递消息时，就会调用该消息处理程序。
 *
 * @param context 要为其注册处理程序的上下文。
 * @param handler 要注册的nack处理程序。
 */
void
coap_register_nack_handler(coap_context_t *context,
                           coap_nack_handler_t handler);

/**
 * 注册一个新的消息处理程序，每当接收到CoAP Ping消息时调用该处理程序。
 *
 * @param context 要为其注册处理程序的上下文。
 * @param handler 要注册的ping处理程序。
 */
void
coap_register_ping_handler(coap_context_t *context,
                           coap_ping_handler_t handler);

/**
 * 注册一个新的消息处理程序，每当接收到CoAP Pong消息时调用该处理程序。
 *
 * @param context 要为其注册处理程序的上下文。
 * @param handler 要注册的pong处理程序。
 */
void
coap_register_pong_handler(coap_context_t *context,
                           coap_pong_handler_t handler);

/**
 * Registers the option type @p 使用给定的上下文对象@pctx键入。
 *
 * @param ctx  要使用的上下文。
 * @param type 要注册的选项类型。
 */
void
coap_register_option(coap_context_t *ctx, uint16_t type);

/**
 * 创建一个新的coap_context_t对象，该对象将保持coap堆栈状态。
 */
coap_context_t *coap_new_context(const coap_address_t *listen_addr);

/**
 * 为服务器设置上下文的默认PSK提示和/或密钥。
 *
 * @param context 当前coap_context_t对象。
 * @param hint    发送给客户端的默认PSK服务器提示。如果为NULL，则禁用PSK身份验证。空字符串是有效的提示。
 * @param key     默认PSK密钥。如果为NULL，则PSK身份验证将失败。
 * @param key_len 默认PSK密钥的长度。如果@p 0，PSK身份验证将失败。
 *
 * @return @c 1如果成功，否则@c 0。
 */
int coap_context_set_psk( coap_context_t *context, const char *hint,
                           const uint8_t *key, size_t key_len );

/**
 * 为服务器设置上下文的默认PSK提示和/或密钥。
 *
 * @param context    当前coap_context_t对象。
 * @param setup_data 如果为NULL，则PSK身份验证将失败。需要PSK信息。
 *
 * @return @c 1如果成功，否则@c 0。
 */
int coap_context_set_psk2(coap_context_t *context,
                          coap_dtls_spsk_t *setup_data);

/**
 * 为服务器设置上下文的默认PKI信息。
 *
 * @param context        当前coap_context_t对象。
 * @param setup_data     如果为NULL，PKI身份验证将失败。需要证书信息。
 *
 * @return @c 1如果成功，否则@c 0。
 */
int
coap_context_set_pki(coap_context_t *context,
                     const coap_dtls_pki_t *setup_data);

/**
 * 为客户端或服务器设置上下文的默认根CA信息。
 *
 * @param context        当前coap_context_t对象。
 * @param ca_file        如果不是NULL，则是包含要使用的所有根CA的PEM编码文件的完整路径名。
 * @param ca_dir         如果不是NULL，则指向包含PEM编码文件的目录，其中包含要使用的所有根CA。
 *
 * @return @c 1如果成功，否则@c 0。
 */
int
coap_context_set_pki_root_cas(coap_context_t *context,
                              const char *ca_file,
                              const char *ca_dir);

/**
 * 设置会话的上下文保持活动计时器。如果会话处于非活动状态，即在给定的秒数内没有发送或接收到数据包，则将发送保活消息。对于不可靠的协议，将发送CoAP空消息。如果未接收到CoAP RST，则CoAP空消息将根据可确认重试参数重新发送，直到出现故障超时，此时会话将被视为已断开。对于可靠的协议，将发送CoAP PING消息。如果在发送下一个PING之前还没有接收到CoAP PONG，则会话将被视为断开连接。
 *
 * @param context        coap_context_t对象。
 * @param seconds        非活动计时器的秒数，或为零以禁用CoAP级别的保活消息。
 */
void coap_context_set_keepalive(coap_context_t *context, unsigned int seconds);

/**
 * 获取libcoap内部文件描述符，以便在应用程序的select（）中使用，或作为应用程序的epoll_wait（）调用中的事件返回。
 *
 * @param context        coap_context_t对象。
 *
 * @return 如果epoll不可用，则使用libcoap文件描述符或@c-1。
 */
int coap_context_get_coap_fd(const coap_context_t *context);

/**
 * 设置最大空闲会话计数。当前未使用的服务器会话数。如果超过此数字，则将完全删除最近最少使用的服务器会话。0（默认值）表示不监视该号码。
 *
 * @param context           coap_context_t对象。
 * @param max_idle_sessions 最大空闲会话计数。
 */
void
coap_context_set_max_idle_sessions(coap_context_t *context,
                                   unsigned int max_idle_sessions);

/**
 * 获取最大空闲会话计数。
 *
 * @param context coap_context_t对象。
 *
 * @return 最大空闲会话数。
 */
unsigned int
coap_context_get_max_idle_sessions(const coap_context_t *context);

/**
 * 设置会话超时值。关闭未使用的服务器会话的非活动秒数。0表示使用默认值（300秒）。
 *
 * @param context         coap_context_t对象。
 * @param session_timeout 会话超时值。
 */
void
coap_context_set_session_timeout(coap_context_t *context,
                                   unsigned int session_timeout);

/**
 * 获取会话超时值
 *
 * @param context coap_context_t对象。
 *
 * @return 会话超时值。
 */
unsigned int
coap_context_get_session_timeout(const coap_context_t *context);

/**
 * 设置CSM超时值。等待对等方（TCP）CSM协商响应的秒数。0（默认值）表示永远等待。
 *
 * @param context    coap_context_t对象。
 * @param csm_tmeout CSM超时值。
 */
void
coap_context_set_csm_timeout(coap_context_t *context,
                             unsigned int csm_tmeout);

/**
 * 获取CSM超时值
 *
 * @param context coap_context_t对象。
 *
 * @return CSM超时值。
 */
unsigned int
coap_context_get_csm_timeout(const coap_context_t *context);

/**
 * 设置（D）TLS握手值中的最大会话数。如果超过这个数字，握手中最近最少使用的服务器会话将被完全删除。0（默认值）表示不监视该号码。
 *
 * @param context         coap_context_t对象。
 * @param max_handshake_sessions 握手中的最大会话数。
 */
void
coap_context_set_max_handshake_sessions(coap_context_t *context,
                                        unsigned int max_handshake_sessions);

/**
 * 获取会话超时值
 *
 * @param context coap_context_t对象。
 *
 * @return （D）TLS握手值中的最大会话数。
 */
unsigned int
coap_context_get_max_handshake_sessions(const coap_context_t *context);

/**
 * Returns a new message id and updates @p 会话->tx_mid。消息id以网络字节顺序返回，以便于在跟踪工具中读取。
 *
 * @param session 当前coap_session_t对象。
 *
 * @return        按网络字节顺序递增的消息id。
 */
uint16_t coap_new_message_id(coap_session_t *session);

/**
 * CoAP堆栈上下文必须使用CoAP_free_context（）释放。此函数清除接收队列和发送队列中的所有条目，并删除已在@p上下文中注册的资源，并释放附加的端点。
 *
 * @param context 要释放的当前coap_context_t对象。
 */
void coap_free_context(coap_context_t *context);

/**
 * Stores @p 具有给定CoAP上下文的数据。此函数覆盖以前用@p上下文存储的任何值。
 *
 * @param context CoAP上下文。
 * @param data 与上下文一起存储的数据。请注意，此数据必须在@p上下文的生存期内有效。
 */
void coap_set_app_data(coap_context_t *context, void *data);

/**
 * Returns any application-specific data that has been stored with @p 上下文使用函数coap_set_app_data（）。此功能将
 * return @c 如果未存储数据，则为NULL。
 *
 * @param context CoAP上下文。
 *
 * @return 先前存储的数据，如果未存储数据，则为@c NULL。
 */
void *coap_get_app_data(const coap_context_t *context);

/**
 * 使用指定的错误@p代码创建新的ACK PDU。由指定的选项
 * the filter expression @p opts将从原始请求中复制
 * contained in @p 要求除非在构建时定义了@c SHORT_ERROR_RESPONSE，否则将添加@p代码的文本原因短语作为有效负载，内容类型为@c 0。此函数返回指向新响应消息的指针，或在出现错误时返回@c NULL。必须使用coap_free（）释放为新消息分配的存储。
 *
 * @param request 收到（可确认）请求的说明。
 * @param code    要设置的错误代码。
 * @param opts    一个选项筛选器，指定要从@p节点中的原始请求复制哪些选项。
 *
 * @return        指向新消息的指针或出错时的@c NULL。
 */
coap_pdu_t *coap_new_error_response(const coap_pdu_t *request,
                                    coap_pdu_code_t code,
                                    coap_opt_filter_t *opts);

/**
 * Sends an error response with code @p 请求@p请求到@p dst的代码。
 * @p opts将传递给coap_new_error_response（），以从请求中复制标记的选项。如果消息是
 * sent, or @c 否则COAP_INVALID_MID。
 *
 * @param session         CoAP会话。
 * @param request         要响应的原始请求。
 * @param code            响应代码。
 * @param opts            指定要从@p请求复制的选项的筛选器。
 *
 * @return                如果消息已发送，则为消息id，否则为@c COAP_INVALID_MID。
 */
coap_mid_t coap_send_error(coap_session_t *session,
                           const coap_pdu_t *request,
                           coap_pdu_code_t code,
                           coap_opt_filter_t *opts);

/**
 * Helper函数，用于创建和发送带有@p类型的消息（通常为ACK或
 * RST). This function returns @c COAP_INVALID_MID（未发送消息时），否则为有效的事务id。
 *
 * @param session         CoAP会话。
 * @param request         应响应的请求。
 * @param type            要设置的类型。
 * @return                成功时的消息id，否则为@c COAP_INVALID_MID。
 */
coap_mid_t
coap_send_message_type(coap_session_t *session, const coap_pdu_t *request,
                       coap_pdu_type_t type);

/**
 * Sends an ACK message with code @c 0表示对@p dst的指定@p请求。如果消息是
 * sent or @c COAP_INVALID_MID出错。
 *
 * @param session         CoAP会话。
 * @param request         待确认的请求。
 *
 * @return                如果发送了ACK，则为消息id，如果出现错误，则为@c COAP_INVALID_MID。
 */
coap_mid_t coap_send_ack(coap_session_t *session, const coap_pdu_t *request);

/**
 * Sends an RST message with code @c 0表示对@p dst的指定@p请求。如果消息是
 * sent or @c COAP_INVALID_MID出错。
 *
 * @param session         CoAP会话。
 * @param request         要重置的请求。
 *
 * @return                如果RST已发送或@c COAP_INVALID_MID出错，则返回消息id。
 */
COAP_STATIC_INLINE coap_mid_t
coap_send_rst(coap_session_t *session, const coap_pdu_t *request) {
  return coap_send_message_type(session, request, COAP_MESSAGE_RST);
}

/**
* 向给定对等方发送CoAP消息。分配给pdu的内存将由coap_send（）释放。调用方在调用coap_send（）后不能使用pdu。
*
* @param session         CoAP会话。
* @param pdu             要发送的CoAP PDU。
*
* @return                发送消息的消息id或出错时的@c COAP_INVALID_MID。
*/
coap_mid_t coap_send( coap_session_t *session, coap_pdu_t *pdu );

#define coap_send_large(session, pdu) coap_send(session, pdu)

/**
 * Invokes the event handler of @p 给定@p事件的上下文和
 * @p 数据
 *
 * @param context 要调用其事件处理程序的CoAP上下文。
 * @param event   要交付的事件。
 * @param session 与@p事件相关的会话。
 * @return 关联事件处理程序的结果，如果未注册，则为0。
 */
int coap_handle_event(coap_context_t *context,
                      coap_event_t event,
                      coap_session_t *session);
/**
 * 如果上下文队列中没有要发送或分派的消息，则返回1。*/
int coap_can_exit(coap_context_t *context);

/**
 * 返回内部刻度计数器的当前值。计数器每秒计数\ c COAP_TICKS_PER_SECOND滴答声。
 */
void coap_ticks(coap_tick_t *);

/**
 * 用于加入多播组以侦听当前定义的UDP端点的函数接口。
 *
 * @param ctx       当前上下文。
 * @param groupname 要加入侦听的组的名称。
 * @param ifname    要加入组的网络接口，如果O/S要选择第一个合适的接口，则为NULL。
 *
 * @return       成功时为0，错误时为-1
 */
int
coap_join_mcast_group_intf(coap_context_t *ctx, const char *groupname,
                           const char *ifname);

#define coap_join_mcast_group(ctx, groupname) \
            (coap_join_mcast_group_intf(ctx, groupname, NULL))

/**
 * 用于定义发送多播流量的跳数（ttl）的函数接口
 *
 * @param session 当前上下文。
 * @param hops    在多播数据包过期之前要使用的跃点数（ttl）。
 *
 * @return       成功时为1，错误时为0
 */
int
coap_mcast_set_hops(coap_session_t *session, size_t hops);

/**@}*/

/**
 * @defgroup app_io应用程序I/O处理应用程序输入/输出的API函数@{
 */

#define COAP_IO_WAIT    0
#define COAP_IO_NO_WAIT ((uint32_t)-1)

/**
 * 主I/O处理功能。完成所有未决的网络I/O，然后可选地等待下一个输入数据包。
 *
 * 这会在内部调用coap_io_prepare_io（），然后为相应的套接字选择（），在适当的地方更新coap_SOCKET_CAN_xxx，然后在返回函数中花费的时间之前调用coap_io_do_io（）。
 *
 * 或者，如果libcoap是使用epoll支持编译的，那么它会在内部调用coap_io_prepare_epoll（），然后调用epoll_wait（）等待（内部）使用epoll_ctl（）设置的任何文件描述符，最后调用coap_io_do_epoll（）返回函数中花费的时间。
 *
 * @param ctx CoAP上下文
 * @param timeout_ms 在执行任何处理后返回之前等待新数据包的最小毫秒数。如果COAP_IO_WAIT，则呼叫将阻塞直到下一个内部动作（例如，数据包重传）（如果有），或者阻塞直到接收到下一个数据包（以较早者为准），并进行必要的处理。如果COAP_IO_NO_WAIT，该函数将在处理后立即返回，而无需等待任何新的输入数据包到达。
 *
 * @return 在函数或@c中花费的毫秒数-1（如果有错误）
 */
int coap_io_process(coap_context_t *ctx, uint32_t timeout_ms);

#ifndef RIOT_VERSION
/**
 * 主消息处理循环具有用于内部选择的附加fds。
 *
 * @param ctx CoAP上下文
 * @param timeout_ms 在执行任何处理后返回之前等待新数据包的最小毫秒数。如果COAP_IO_WAIT，则呼叫将阻塞直到下一个内部动作（例如，数据包重传）（如果有），或者阻塞直到接收到下一个数据包（以较早者为准），并进行必要的处理。如果COAP_IO_NO_WAIT，该函数将在处理后立即返回，而无需等待任何新的输入数据包到达。
 * @param nfds      在readfds、writefds或exceptfds中设置的最大FD加1，
 * @param readfds   读取FD以额外检查内部select（）或NULL（如果不需要）。
 * @param writefds  写入FD以额外检查内部select（）或NULL（如果不需要）。
 * @param exceptfds 除了要在内部select（）中额外检查的FD，如果不需要，则为NULL。
 *
 *
 * @return coap_io_process_with_fds中花费的毫秒数，如果出现错误，则为@c-1。如果已定义，readfds、writefds和exceptfds将根据内部select（）调用返回的值进行更新。
 */
int coap_io_process_with_fds(coap_context_t *ctx, uint32_t timeout_ms,
                             int nfds, fd_set *readfds, fd_set *writefds,
                             fd_set *exceptfds);
#endif /* !RIOT_VERSION */

/**@}*/

/**
 * @defgroup app_io_internal应用程序I/O处理（内部）应用程序输入/输出的内部API函数@{
 */

/**
* 遍历嵌入端点或
* sessions associated with the @p ctx以确定哪些需要任何读、写、接受或连接I/O（设置COAP_SOCKET_CANT_xx）。如果设置，coap_socket_t将添加到@p套接字。
*
* 发送任何现在超时的延迟包，以及与所请求的可观察响应相关联的任何包。
*
* 此外，当预期下一个预期I/O发生时（例如，数据包重传），它会返回。
*
* Prior to calling coap_io_do_io(), the @p 必须测试套接字，以查看是否有任何COAP_SOCKET_CAN_xxx具有适当的信息，如果有，则设置COAP_SSOCKET_CAN-xxx。这通常在使用select（）调用后完成。
*
* 注意：如果epoll支持被编译成libcoap，则必须使用coap_io_prepare_epoll（）而不是coap_io_pepare_io（）。
*
* 内部功能。
*
* @param ctx CoAP上下文
* @param sockets 套接字描述符数组，在输出时填充
* @param max_sockets 套接字数组的大小。
* @param num_sockets 指向输出时套接字数组中有效项数的指针。
* @param now 当前时间。
*
* @return timeout select（）可用于等待网络事件的最大毫秒数，如果等待应该是永久的，则为0。
*/
unsigned int
coap_io_prepare_io(coap_context_t *ctx,
  coap_socket_t *sockets[],
  unsigned int max_sockets,
  unsigned int *num_sockets,
  coap_tick_t now
);

/**
 * 处理与@p ctx相关联的端点或会话中嵌入的coap_socket_t结构（coap_socket_CAN_xxx集合）中指示的任何未完成的读、写、接受或连接I/O。
 *
 * 注意：如果epoll支持被编译成libcoap，则必须使用coap_io_do_epoll（）而不是coap_io_do_io（）。
 *
 * 内部功能。
 *
 * @param ctx CoAP上下文
 * @param now 当前时间
 */
void coap_io_do_io(coap_context_t *ctx, coap_tick_t now);

/**
 * 发送任何现在超时的延迟包，以及与所请求的可观察响应相关联的任何包。
 *
 * 此外，当预期下一个预期I/O发生时（例如，数据包重传），它会返回。
 *
 * 注意：如果epoll支持被编译成libcoap，则必须使用coap_io_prepare_epoll（）而不是coap_io_pepare_io（）。
 *
 * 内部功能。
 *
 * @param ctx CoAP上下文
 * @param now 当前时间。
 *
 * @return timeout epoll_wait（）可用于等待网络事件的最大毫秒数，如果等待应该是永久的，则为0。
 */
unsigned int
coap_io_prepare_epoll(coap_context_t *ctx, coap_tick_t now);

struct epoll_event;

/**
 * 处理所有epoll事件
 *
 * 注意：如果epoll支持被编译成libcoap，则必须使用coap_io_do_epoll（）而不是coap_io_do_io（）。
 *
 * 内部功能
 *
 * @param ctx    当前CoAP上下文。
 * @param events 从epoll_wait（）调用返回的事件列表。
 * @param nevents 事件的数量。
 *
 */
void coap_io_do_epoll(coap_context_t *ctx, struct epoll_event* events,
                      size_t nevents);

/**@}*/

/**
 * @deprecated 请改用coap_io_process（）。
 *
 * 此函数只调用coap_io_process（）。
 *
 * @param ctx CoAP上下文
 * @param timeout_ms 在执行任何处理后返回之前等待新数据包的最小毫秒数。如果COAP_IO_WAIT，则呼叫将阻塞直到下一个内部动作（例如，数据包重传）（如果有），或者阻塞直到接收到下一个数据包（以较早者为准），并进行必要的处理。如果COAP_IO_NO_WAIT，该函数将在处理后立即返回，而无需等待任何新的输入数据包到达。
 *
 * @return 在函数或@c中花费的毫秒数-1（如果有错误）
 */
COAP_STATIC_INLINE COAP_DEPRECATED int
coap_run_once(coap_context_t *ctx, uint32_t timeout_ms)
{
  return coap_io_process(ctx, timeout_ms);
}

/**
* @deprecated 请改用coap_io_prepare_io（）。
*
* 此函数只调用coap_io_prepare_io（）。
*
* 内部功能。
*
* @param ctx CoAP上下文
* @param sockets 套接字描述符数组，在输出时填充
* @param max_sockets 套接字数组的大小。
* @param num_sockets 指向输出时套接字数组中有效项数的指针。
* @param now 当前时间。
*
* @return timeout select（）可用于等待网络事件的最大毫秒数，如果等待应该是永久的，则为0。
*/
COAP_STATIC_INLINE COAP_DEPRECATED unsigned int
coap_write(coap_context_t *ctx,
  coap_socket_t *sockets[],
  unsigned int max_sockets,
  unsigned int *num_sockets,
  coap_tick_t now
) {
  return coap_io_prepare_io(ctx, sockets, max_sockets, num_sockets, now);
}

/**
 * @deprecated 请改用coap_io_do_io（）。
 *
 * 此函数只调用coap_io_do_io（）。
 *
 * 内部功能。
 *
 * @param ctx CoAP上下文
 * @param now 当前时间
 */
COAP_STATIC_INLINE COAP_DEPRECATED void
coap_read(coap_context_t *ctx, coap_tick_t now
) {
  coap_io_do_io(ctx, now);
}

/* 旧代码中可能存在的旧定义-很有用！*/
#define COAP_RUN_NONBLOCK COAP_RUN_NONBLOCK_deprecated_use_COAP_IO_NO_WAIT
#define COAP_RUN_BLOCK COAP_RUN_BLOCK_deprecated_use_COAP_IO_WAIT

#endif /* COAP_NET_H_ */

