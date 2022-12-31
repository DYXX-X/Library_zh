/*
 * coap_session_内部。h——不暴露于应用程序编程的结构、枚举和函数
 *
 * 版权所有（C）2010-2019 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/**
 * @file coap_session_内部.h
 * @brief COAP会议内部信息
 */

#ifndef COAP_SESSION_INTERNAL_H_
#define COAP_SESSION_INTERNAL_H_

#include "coap_io_internal.h"

#define COAP_DEFAULT_SESSION_TIMEOUT 300
#define COAP_PARTIAL_SESSION_TIMEOUT_TICKS (30 * COAP_TICKS_PER_SECOND)
#define COAP_DEFAULT_MAX_HANDSHAKE_SESSIONS 100

/**
 * @defgroup session_internal会话（内部）不向应用程序公开的CoAP会话结构、枚举和函数@{
 */

/**
 * 仅用于哈希传入数据包的服务器。不能具有本地IP地址，因为这可能是初始多播和后续单播地址
 */
struct coap_addr_hash_t {
  coap_address_t remote;       /**<远程地址和端口*/
  uint16_t lport;              /**<本地端口*/
  coap_proto_t proto;          /**<CoAP协议*/
};

/**
 * 可以附加到coap_context_t（客户端）或coap_endpoint_t（服务器）的虚拟会话的抽象。
 */
struct coap_session_t {
  coap_proto_t proto;               /**<使用的协议*/
  coap_session_type_t type;         /**<客户端或服务器端套接字*/
  coap_session_state_t state;       /**<当前与同行的关系状态*/
  unsigned ref;                     /**<来自队列的引用计数*/
  size_t tls_overhead;              /**<TLS层的开销*/
  size_t mtu;                       /**<路径或CSM mtu*/
  coap_addr_hash_t addr_hash;  /**<服务器传入数据包的地址哈希*/
  UT_hash_handle hh;
  coap_addr_tuple_t addr_info;      /**<key:远程/本地地址信息*/
  int ifindex;                      /**<接口索引*/
  coap_socket_t sock;               /**<会话的套接字对象（如果有）*/
  coap_endpoint_t *endpoint;        /**<会话的终结点*/
  coap_context_t *context;          /**<会话上下文*/
  void *tls;                        /**<安全参数*/
  uint16_t tx_mid;                  /**<此会话中使用的最后一个消息id*/
  uint8_t con_active;               /**<主动CON请求已发送*/
  uint8_t csm_block_supported;      /**<支持CSM TCP块*/
  coap_mid_t last_ping_mid;         /**<此会话中使用的最后一个保活消息id*/
  coap_queue_t *delayqueue;         /**<等待发送的延迟消息列表*/
  coap_lg_xmit_t *lg_xmit;          /**<大型变速器列表*/
  coap_lg_crcv_t *lg_crcv;       /**<预期大接收的客户端列表*/
  coap_lg_srcv_t *lg_srcv;       /**<预期大型接收的服务器列表*/
  size_t partial_write;             /**＜if＞0表示已从发送队列开头的pdu写入的字节数*/
  uint8_t read_header[8];           /**<传入消息标头的标头存储空间*/
  size_t partial_read;              /**＜if＞0表示已为传入消息读取的字节数*/
  coap_pdu_t *partial_pdu;          /**<不完整的传入pdu*/
  coap_tick_t last_rx_tx;
  coap_tick_t last_tx_rst;
  coap_tick_t last_ping;
  coap_tick_t last_pong;
  coap_tick_t csm_tx;
  coap_dtls_cpsk_t cpsk_setup_data; /**<客户端提供的PSK初始设置数据*/
  coap_bin_const_t *psk_identity;   /**< 如果是客户端，则此字段包含服务器的当前标识；当此字段为NULL时，当前标识包含在cpsk_setup_data中

                                      如果是服务器，则此字段包含客户端提供的标识。

                                      内部维护的价值*/
  coap_bin_const_t *psk_key;        /**< 如果是客户端，则此字段包含服务器的当前预共享密钥；当该字段为NULL时，当前密钥包含在cpsk_setup_data中

                                      如果是服务器，则此字段包含客户端的当前密钥。

                                      内部维护的价值*/
  coap_bin_const_t *psk_hint;       /**< 如果是客户端，则此字段包含服务器提供的标识提示。

                                      如果是服务器，则此字段包含客户端的当前提示；当此字段为NULL时，当前提示包含在上下文->spsk_setup_data中

                                      内部维护的价值*/
  void *app;                        /**<应用程序特定数据*/
  unsigned int max_retransmit;      /**< 最大重发次数（默认值
                                         4) */
  coap_fixed_point_t ack_timeout;   /**<等待确认超时（默认为2秒）*/
  coap_fixed_point_t ack_random_factor; /**< ack随机因子回退（默认值
                                             1.5) */
  unsigned int dtls_timeout_count;      /**<dtls安装重试计数器*/
  int dtls_event;                       /**<跟踪此服务器上的任何（D）TLS事件*/
  uint8_t block_mode;             /**<零个或多个COAP_BLOCK_或'd选项*/
  uint64_t tx_token;              /**<要使用的下一个令牌编号*/
};

/**
 * 可以附加到coap_context_t的虚拟端点的抽象。密钥（端口、bind_addr）必须唯一标识此端点。
 */
struct coap_endpoint_t {
  struct coap_endpoint_t *next;
  coap_context_t *context;        /**<端点的上下文*/
  coap_proto_t proto;             /**<此接口上使用的协议*/
  uint16_t default_mtu;           /**<此接口的默认mtu*/
  coap_socket_t sock;             /**<接口的套接字对象（如果有）*/
  coap_address_t bind_addr;       /**<本地接口地址*/
  coap_session_t *sessions;       /**<哈希表或活动会话列表*/
};

/**
 * 通知会话传输刚刚连接，CSM交换现在可以启动。
 *
 * @param session CoAP会话。
 */
void coap_session_send_csm(coap_session_t *session);

/**
 * 通知会话它刚刚连接或重新连接。
 *
 * @param session CoAP会话。
 */
void coap_session_connected(coap_session_t *session);

/**
 * 刷新会话的当前身份提示（PSK）。
 * Note: A copy of @p pskhint由libcoap在会话中维护。
 *
 * @param session  当前coap_session_t对象。
 * @param psk_hint 如果为NULL，标识提示将恢复为会话设置时使用的初始标识提示。
 *
 * @return @c 1如果成功，否则@c 0。
 */
int coap_session_refresh_psk_hint(coap_session_t *session,
                                  const coap_bin_const_t *psk_hint);

/**
 * 刷新会话的当前预共享密钥（PSK）。
 * Note: A copy of @p pskkey由libcoap在会话中维护。
 *
 * @param session  当前coap_session_t对象。
 * @param psk_key  如果为NULL，则预共享密钥将恢复为用作会话设置的初始预共享密钥。
 *
 * @return @c 1如果成功，否则@c 0。
 */
int coap_session_refresh_psk_key(coap_session_t *session,
                                 const coap_bin_const_t *psk_key);

/**
 * 为指定的终结点创建新的服务器会话。
 * @param ctx CoAP上下文。
 * @param ep 传入连接请求挂起的端点。
 *
 * @return 新的CoAP会话或NULL（如果失败）。调用coap_session_release添加到未使用的队列。
 */
coap_session_t *coap_new_server_session(
  coap_context_t *ctx,
  coap_endpoint_t *ep
);

/**
 * 数据报数据传输的功能接口。此函数返回已传输的字节数，或错误时返回小于零的值。
 *
 * @param session          要发送数据的会话。
 * @param data             要发送的数据。
 * @param datalen          @p数据的实际长度。
 *
 * @return                 成功时写入的字节数，或错误时小于零的值。
 */
ssize_t coap_session_send(coap_session_t *session,
  const uint8_t *data, size_t datalen);

/**
 * 流数据传输的功能接口。此函数返回已传输的字节数，或错误时返回小于零的值。由于拥塞控制，写入的字节数可能小于数据线。
 *
 * @param session          要发送数据的会话。
 * @param data             要发送的数据。
 * @param datalen          @p数据的实际长度。
 *
 * @return                 成功时写入的字节数，或错误时小于零的值。
 */
ssize_t coap_session_write(coap_session_t *session,
  const uint8_t *data, size_t datalen);

/**
 * 根据会话的协议发送pdu。此函数返回已传输的字节数，或错误时返回小于零的值。
 *
 * @param session          要发送pdu的会话。
 * @param pdu              要发送的pdu。
 *
 * @return                 成功时写入的字节数，或错误时小于零的值。
 */
ssize_t coap_session_send_pdu(coap_session_t *session, coap_pdu_t *pdu);

ssize_t
coap_session_delay_pdu(coap_session_t *session, coap_pdu_t *pdu,
                       coap_queue_t *node);

/**
 * 在服务器会话中查找在端点上接收的数据包，或创建一个新的数据包。
 *
 * @param endpoint 接收数据包的活动终结点。
 * @param packet 收到数据包。
 * @param now 当前时间（以刻度为单位）。
 * @return CoAP会话或@c NULL（如果错误）。
 */
coap_session_t *coap_endpoint_get_session(coap_endpoint_t *endpoint,
  const coap_packet_t *packet, coap_tick_t now);

/**
 * 为@p会话创建新的DTLS会话。
 * Note: the @p 如果无法创建DTLS服务器会话，则释放会话。
 *
 * @ingroup dtls_内部
 *
 * @param session   要添加DTLS会话的会话
 * @param now       当前时间（以刻度为单位）。
 *
 * @return CoAP会话或@c NULL（如果错误）。
 */
coap_session_t *coap_session_new_dtls_session(coap_session_t *session,
  coap_tick_t now);

void coap_session_free(coap_session_t *session);
void coap_session_mfree(coap_session_t *session);

/** @} */

#define SESSIONS_ADD(e, obj) \
  HASH_ADD(hh, (e), addr_hash, sizeof((obj)->addr_hash), (obj))

#define SESSIONS_DELETE(e, obj) \
  HASH_DELETE(hh, (e), (obj))

#define SESSIONS_ITER(e, el, rtmp)  \
  HASH_ITER(hh, (e), el, rtmp)

#define SESSIONS_ITER_SAFE(e, el, rtmp) \
for ((el) = (e); (el) && ((rtmp) = (el)->hh.next, 1); (el) = (rtmp))

#define SESSIONS_FIND(e, k, res) {                     \
    HASH_FIND(hh, (e), &(k), sizeof(k), (res)); \
  }

#endif /* COAP_SESSION_INTERNAL_H_ */

