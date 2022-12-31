/* coap_session。h——libcoap的会话管理
*
* 版权所有（C）2017 Jean-Claue Michelou<jcm@spinetix.com>
*
 * SPDX许可证标识符：BSD-2-Clause
 *
* 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
*/

/**
 * @file coap_session.h
 * @brief 定义应用程序可见的会话信息
 */

#ifndef COAP_SESSION_H_
#define COAP_SESSION_H_

/**
 * @defgroup CoAP会话的会话会话API函数@{
 */

/**
* 对固定点数的抽象，可以在必要时使用，而不是浮点数。1000个分数位等于一个整数
*/
typedef struct coap_fixed_point_t {
  uint16_t integer_part;    /**<定点变量的整数部分*/
  uint16_t fractional_part; /**<定点变量1/1000（3点）精度的小数部分*/
} coap_fixed_point_t;

#define COAP_PROTO_NOT_RELIABLE(p) ((p)==COAP_PROTO_UDP || (p)==COAP_PROTO_DTLS)
#define COAP_PROTO_RELIABLE(p) ((p)==COAP_PROTO_TCP || (p)==COAP_PROTO_TLS)

/**
 * coap_session_type_t值
 */
typedef enum coap_session_type_t {
  COAP_SESSION_TYPE_NONE = 0, /**<未定义*/
  COAP_SESSION_TYPE_CLIENT,   /**<客户端*/
  COAP_SESSION_TYPE_SERVER,   /**<服务器端*/
  COAP_SESSION_TYPE_HELLO,    /**<响应客户端hello的服务器端临时会话*/
} coap_session_type_t;

/**
 * coap_session_state_t值
 */
typedef enum coap_session_state_t {
  COAP_SESSION_STATE_NONE = 0,
  COAP_SESSION_STATE_CONNECTING,
  COAP_SESSION_STATE_HANDSHAKE,
  COAP_SESSION_STATE_CSM,
  COAP_SESSION_STATE_ESTABLISHED,
} coap_session_state_t;

/**
 * 会话上的增量引用计数器。
 *
 * @param session CoAP会话。
 * @return 与会话相同
 */
coap_session_t *coap_session_reference(coap_session_t *session);

/**
 * 会话上的递减引用计数器。请注意，会话可能会因此而被删除，并且不应在此调用后使用。
 *
 * @param session CoAP会话。
 */
void coap_session_release(coap_session_t *session);

/**
 * 通知会话它已失败。这将清除所有未完成/排队的传输、观察等。。
 *
 * @param session CoAP会话。
 * @param reason 会话断开连接的原因。
 */
void coap_session_disconnected(coap_session_t *session,
                               coap_nack_reason_t reason);

/**
 * Stores @p 给定会话的数据。此函数覆盖以前用@p会话存储的任何值。
 *
 * @param session CoAP会话。
 * @param data 指向要存储的数据的指针。
 */
void coap_session_set_app_data(coap_session_t *session, void *data);

/**
 * Returns any application-specific data that has been stored with @p 会话，使用函数coap_session_set_app_data（）。此功能将
 * return @c 如果未存储数据，则为NULL。
 *
 * @param session CoAP会话。
 *
 * @return 指向存储数据的指针或@c NULL。
 */
void *coap_session_get_app_data(const coap_session_t *session);

/**
 * 从会话中获取远程IP地址。
 *
 * @param session CoAP会话。
 *
 * @return 会话的远程地址或失败时的@c NULL。
 */
const coap_address_t *coap_session_get_addr_remote(
                                               const coap_session_t *session);

/**
 * 从会话中获取本地IP地址。
 *
 * @param session CoAP会话。
 *
 * @return 会话的本地地址或失败时的@c NULL。
 */
const coap_address_t *coap_session_get_addr_local(
                                               const coap_session_t *session);

/**
 * 获取会话协议类型
 *
 * @param session CoAP会话。
 *
 * @return 会话的协议类型
 */
coap_proto_t coap_session_get_proto(const coap_session_t *session);

/**
 * 获取会话类型
 *
 * @param session CoAP会话。
 *
 * @return 会话的类型
 */
coap_session_type_t coap_session_get_type(const coap_session_t *session);

/**
 * 获取会话状态
 *
 * @param session CoAP会话。
 *
 * @return 会话的状态
 */
coap_session_state_t coap_session_get_state(const coap_session_t *session);

/**
 * 获取会话if索引
 *
 * @param session CoAP会话。
 *
 * @return 会话的if索引或@c-1出错。
 */
int coap_session_get_ifindex(const coap_session_t *session);

/**
 * 获取会话TLS安全指针（取决于TLS类型）
 *
 * OpenSSL:SSL*GnuTLS:GnuTLS_session_t（隐式）Mbed TLS:mbedtls_SSL_context TinyDTLS:struct dtls_context
 *
 * @param session CoAP会话。
 * @param tls_lib 已更新库类型。
 *
 * @return 如果未设置会话TLS ptr或@c NULL
 */
void *coap_session_get_tls(const coap_session_t *session,
                           coap_tls_library_t *tls_lib);

/**
 * 获取会话上下文
 *
 * @param session CoAP会话。
 *
 * @return 会话的上下文
 */
coap_context_t *coap_session_get_context(const coap_session_t *session);

/**
 * 将会话类型设置为客户端。通常用于呼叫总部服务器。会话的类型必须为COAP_SESESSION_type_SERVER。注意：如果此函数成功，则会话引用计数将递增，并且后续的coap_session_release（）将引用计数设置为0将导致会话被释放。
 *
 * @param session CoAP会话。
 *
 * @return @c 1（如果更新），失败时@c 0。
 */
int coap_session_set_type_client(coap_session_t *session);

/**
 * 设置会话MTU。这是可以发送的最大消息大小，不包括IP和UDP开销。
 *
 * @param session CoAP会话。
 * @param mtu 最大邮件大小
 */
void coap_session_set_mtu(coap_session_t *session, unsigned mtu);

/**
 * 获取最大可接受PDU大小
 *
 * @param session CoAP会话。
 * @return 最大PDU大小，不包括报头（但包括令牌）。
 */
size_t coap_session_max_pdu_size(const coap_session_t *session);

/**
* 创建到指定服务器的新客户端会话。
* @param ctx CoAP上下文。
* @param local_if 本地接口的地址。建议使用NULL让操作系统选择合适的本地接口。如果指定了地址，则端口号应为零，这意味着将自动选择空闲端口。
* @param server 服务器的地址。如果端口号为零，则将使用协议的默认端口。
* @param proto 协议
*
* @return 新的CoAP会话或NULL（如果失败）。调用coap_session_release释放。
*/
coap_session_t *coap_new_client_session(
  coap_context_t *ctx,
  const coap_address_t *local_if,
  const coap_address_t *server,
  coap_proto_t proto
);

/**
* 使用PSK凭据创建到指定服务器的新客户端会话
* @param ctx CoAP上下文。
* @param local_if 本地接口的地址。建议使用NULL让操作系统选择合适的本地接口。如果指定了地址，则端口号应为零，这意味着将自动选择空闲端口。
* @param server 服务器的地址。如果端口号为零，则将使用协议的默认端口。
* @param proto 协议
* @param identity PSK客户端身份
* @param key PSK共享密钥
* @param key_len PSK共享密钥长度
*
* @return 新的CoAP会话或NULL（如果失败）。调用coap_session_release释放。
*/
coap_session_t *coap_new_client_session_psk(
  coap_context_t *ctx,
  const coap_address_t *local_if,
  const coap_address_t *server,
  coap_proto_t proto,
  const char *identity,
  const uint8_t *key,
  unsigned key_len
);

/**
* 使用PSK凭据创建到指定服务器的新客户端会话
* @param ctx CoAP上下文。
* @param local_if 本地接口的地址。建议使用NULL让操作系统选择合适的本地接口。如果指定了地址，则端口号应为零，这意味着将自动选择空闲端口。
* @param server 服务器的地址。如果端口号为零，则将使用协议的默认端口。
* @param proto CoAP协议。
* @param setup_data PSK参数。
*
* @return 新的CoAP会话或NULL（如果失败）。调用coap_session_release（）释放。
*/
coap_session_t *coap_new_client_session_psk2(
  coap_context_t *ctx,
  const coap_address_t *local_if,
  const coap_address_t *server,
  coap_proto_t proto,
  coap_dtls_cpsk_t *setup_data
);

/**
 * 获取服务器会话的当前身份提示（PSK）。
 *
 * @param session  当前coap_session_t对象。
 *
 * @return @c提示如果成功，否则@c为NULL。
 */
const coap_bin_const_t * coap_session_get_psk_hint(
                                               const coap_session_t *session);

/**
 * 获取会话的当前预共享密钥（PSK）。
 *
 * @param session  当前coap_session_t对象。
 *
 * @return @如果成功，则为c psk_key，否则为@c NULL。
 */
const coap_bin_const_t * coap_session_get_psk_key(
                                               const coap_session_t *session);

/**
* 使用PKI凭据创建到指定服务器的新客户端会话
* @param ctx CoAP上下文。
* @param local_if 本地接口的地址。建议使用NULL让操作系统选择合适的本地接口。如果指定了地址，则端口号应为零，这意味着将自动选择空闲端口。
* @param server 服务器的地址。如果端口号为零，则将使用协议的默认端口。
* @param proto CoAP协议。
* @param setup_data PKI参数。
*
* @return 新的CoAP会话或NULL（如果失败）。调用coap_session_release（）释放。
*/
coap_session_t *coap_new_client_session_pki(
  coap_context_t *ctx,
  const coap_address_t *local_if,
  const coap_address_t *server,
  coap_proto_t proto,
  coap_dtls_pki_t *setup_data
);

/**
 * 初始化标记值以用作起点。
 *
 * @param session 当前coap_session_t对象。
 * @param length  令牌的长度（0-8字节）。
 * @param token   令牌数据。
 *
 */
void coap_session_init_token(coap_session_t *session, size_t length,
                             const uint8_t *token);

/**
 * 创建新令牌以供使用。
 *
 * @param session 当前coap_session_t对象。
 * @param length  更新了新令牌的长度。
 * @param token   使用新令牌数据更新（必须为8字节长）。
 *
 */
void coap_session_new_token(coap_session_t *session, size_t *length,
                                      uint8_t *token);

/**
 * @ingroup logging获取会话描述。
 *
 * @param session  CoAP会话。
 * @return 描述字符串。
 */
const char *coap_session_str(const coap_session_t *session);

/**
* 创建用于与对等方通信的新端点。
*
* @param context        将拥有新端点的coap上下文
* @param listen_addr    地址端点将侦听传入请求或从中发出传出请求。使用NULL指定不接受传入请求，并使用随机端点。
* @param proto          此终结点上使用的协议
*/

coap_endpoint_t *coap_new_endpoint(coap_context_t *context, const coap_address_t *listen_addr, coap_proto_t proto);

/**
* 设置端点的默认MTU。这是可以发送的最大消息大小，不包括IP和UDP开销。
*
* @param endpoint CoAP端点。
* @param mtu 最大邮件大小
*/
void coap_endpoint_set_default_mtu(coap_endpoint_t *endpoint, unsigned mtu);

void coap_free_endpoint(coap_endpoint_t *ep);

/** @} */

/**
 * @ingroup logging获取端点描述。
*
* @param endpoint  CoAP端点。
* @return 描述字符串。
*/
const char *coap_endpoint_str(const coap_endpoint_t *endpoint);

coap_session_t *coap_session_get_by_peer(const coap_context_t *ctx,
  const coap_address_t *remote_addr, int ifindex);

 /**
  * @defgroup cc速率控制CoAP速率控制（面向流的协议中的“拥塞控制”）的传输参数在https://tools.ietf.org/html/rfc7252#section-4.8 @{
  */

  /**
   * 等待ACK或对未完成CON消息的响应的秒数。RFC 7252，第4.8节ACK_TIMEOUT的默认值为2
   *
   * 可使用coap_session_set_ack_timeout（）进行配置
   */
#define COAP_DEFAULT_ACK_TIMEOUT ((coap_fixed_point_t){2,0})

  /**
   * 用于在重传消息之前随机化等待时间以防止同步效应的一种因素。RFC 7252，第4.8节ACK_RANDOM_FACTOR的默认值为1.5
   *
   * 可使用coap_session_set_ack_random_factor（）进行配置
   */
#define COAP_DEFAULT_ACK_RANDOM_FACTOR ((coap_fixed_point_t){1,500})

  /**
   * 消息发送停止前的消息重传次数RFC 7252，第4.8节MAX_RETRANSMIT的默认值为4
   *
   * 可使用coap_session_set_max_restt（）进行配置
   */
#define COAP_DEFAULT_MAX_RETRANSMIT  4

  /**
   * 客户端与给定服务器同时保持的未完成交互数。RFC 7252，第4.8节NSTART的默认值为1
   */
#define COAP_DEFAULT_NSTART 1

  /**
   * 发送回对多播请求的响应之前的最大秒数。RFC 7252第4.8节DEFAULT_LEISURE为5。
   */
#ifndef COAP_DEFAULT_LEISURE
#define COAP_DEFAULT_LEISURE (5U)
#endif /* COAP_DEFAULT_LEISURE */

  /**
   * 会话的MAX_TRANSMIT_SPAN定义。
   *
   * RFC 7252，第4.8.2节最大RAMSMIT_SPAN ACK_TIMEOUT（（2（MAX_RETRANSMIT））的计算-1）ACK_RANDOM_FACTOR
   */
#define COAP_MAX_TRANSMIT_SPAN(s) \
 ((s->ack_timeout.integer_part * 1000 + s->ack_timeout.fractional_part) * \
  ((1 << (s->max_retransmit)) -1) * \
  (s->ack_random_factor.integer_part * 1000 + \
   s->ack_random_factor.fractional_part) \
  / 1000000)

  /**
   * 会话的MAX_TRANSMIT_WAIT定义。
   *
   * RFC 7252，第4.8.2节“MAX_TRAMSMIT_WAIT ACK_TIMEOUT（（2（MAX_RETRANSMIT+1））-1）ACK_RANDOM_FACTOR的计算”
   */
#define COAP_MAX_TRANSMIT_WAIT(s) \
 ((s->ack_timeout.integer_part * 1000 + s->ack_timeout.fractional_part) * \
  ((1 << (s->max_retransmit + 1)) -1) * \
  (s->ack_random_factor.integer_part * 1000 + \
   s->ack_random_factor.fractional_part) \
  / 1000000)

  /**
   * MAX_LATENCY定义。RFC 7252，第4.8.2节，MAX_LATENCY为100。
   */
#define COAP_MAX_LATENCY 100

  /**
   * 会话的PROCESSING_DELAY定义。
   *
   * RFC 7252，第4.8.2节PROCESSING_DELAY PROCESSINGDELAY的计算设置为ACK_TIMEOUT
   */
#define COAP_PROCESSING_DELAY(s) \
 ((s->ack_timeout.integer_part * 1000 + s->ack_timeout.fractional_part + 500) \
  / 1000)

  /**
   * 会话的MAX_RTT定义。
   *
   * RFC 7252，第4.8.2节MAX_RTT（2 MAX_LATENCY）+PROCESSING_DELAY的计算
   */
#define COAP_MAX_RTT(s) \
 ((2 * COAP_MAX_LATENCY) + COAP_PROCESSING_DELAY(s))

  /**
   * 会话的EXCHANGE_LIFIME定义。
   *
   * RFC 7252，第4.8.2节EXCHANGE_LIFIME MAX_TRANSMIT_SPAN+（2 MAX_LATENCY）+PROCESSING_DELAY的计算
   */
#define COAP_EXCHANGE_LIFETIME(s) \
 (COAP_MAX_TRANSMIT_SPAN(s) + (2 * COAP_MAX_LATENCY) + COAP_PROCESSING_DELAY(s))

  /**
   * 会话的NON_LISTIME定义。
   *
   * RFC 7252，第4.8.2节NON_LEFETIME MAX_TRANSMIT_SPAN+MAX_LATENCY的计算
   */
#define COAP_NON_LIFETIME(s) \
 (COAP_MAX_TRANSMIT_SPAN(s) + COAP_MAX_LATENCY)

      /** @} */

/**
* 设置失败前CoAP最大重传计数
*
* 停止消息发送之前的消息重传次数
*
* @param session CoAP会话。
* @param value 要设置为的值。默认值为4，通常不应更改。
*/
void coap_session_set_max_retransmit(coap_session_t *session,
                                     unsigned int value);

/**
* 在下一次重新发送之前设置CoAP初始确认响应超时
*
* 等待ACK或对未完成CON消息的响应的秒数。
*
* @param session CoAP会话。
* @param value 要设置为的值。默认值为2，通常不应更改。
*/
void coap_session_set_ack_timeout(coap_session_t *session,
                                  coap_fixed_point_t value);

/**
* 设置CoAP ack随机化因子
*
* 用于在重传消息之前随机化等待时间以防止同步效应的一种因素。
*
* @param session CoAP会话。
* @param value 要设置为的值。默认值为1.5，通常不应更改。
*/
void coap_session_set_ack_random_factor(coap_session_t *session,
                                        coap_fixed_point_t value);

/**
* 获取失败前CoAP最大重发次数
*
* 停止消息发送之前的消息重传次数
*
* @param session CoAP会话。
*
* @return 当前最大重传值
*/
unsigned int coap_session_get_max_retransmit(const coap_session_t *session);

/**
* 在下一次重新发送之前获取CoAP初始确认响应超时
*
* 等待ACK或对未完成CON消息的响应的秒数。
*
* @param session CoAP会话。
*
* @return 当前确认响应超时值
*/
coap_fixed_point_t coap_session_get_ack_timeout(const coap_session_t *session);

/**
* 获取CoAP ack随机化因子
*
* 用于在重传消息之前随机化等待时间以防止同步效应的一种因素。
*
* @param session CoAP会话。
*
* @return 当前ack随机化值
*/
coap_fixed_point_t coap_session_get_ack_random_factor(
                                               const coap_session_t *session);

/**
 * 为会话发送ping消息。
 * @param session CoAP会话。
 *
 * @return COAP_INVALID_MID（如果有错误）
 */
coap_mid_t coap_session_send_ping(coap_session_t *session);

#endif  /* COAP_SESSION_H */

