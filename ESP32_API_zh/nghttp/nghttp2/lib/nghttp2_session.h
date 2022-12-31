/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2012 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef NGHTTP2_SESSION_H
#define NGHTTP2_SESSION_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>
#include "nghttp2_map.h"
#include "nghttp2_frame.h"
#include "nghttp2_hd.h"
#include "nghttp2_stream.h"
#include "nghttp2_outbound_item.h"
#include "nghttp2_int.h"
#include "nghttp2_buf.h"
#include "nghttp2_callbacks.h"
#include "nghttp2_mem.h"

/* 测试的全局变量，我们希望禁用严格的前导处理。*/
extern int nghttp2_enable_strict_preface;

/*
 * 选项标志。
 */
typedef enum {
  NGHTTP2_OPTMASK_NO_AUTO_WINDOW_UPDATE = 1 << 0,
  NGHTTP2_OPTMASK_NO_RECV_CLIENT_MAGIC = 1 << 1,
  NGHTTP2_OPTMASK_NO_HTTP_MESSAGING = 1 << 2,
  NGHTTP2_OPTMASK_NO_AUTO_PING_ACK = 1 << 3,
  NGHTTP2_OPTMASK_NO_CLOSED_STREAMS = 1 << 4
} nghttp2_optmask;

/*
 * 内置类型的位掩码，以启用该类型帧的默认处理。
 */
typedef enum {
  NGHTTP2_TYPEMASK_NONE = 0,
  NGHTTP2_TYPEMASK_ALTSVC = 1 << 0,
  NGHTTP2_TYPEMASK_ORIGIN = 1 << 1
} nghttp2_typemask;

typedef enum {
  NGHTTP2_OB_POP_ITEM,
  NGHTTP2_OB_SEND_DATA,
  NGHTTP2_OB_SEND_NO_COPY,
  NGHTTP2_OB_SEND_CLIENT_MAGIC
} nghttp2_outbound_state;

typedef struct {
  nghttp2_outbound_item *item;
  nghttp2_bufs framebufs;
  nghttp2_outbound_state state;
} nghttp2_active_outbound_item;

/* nghttp2_session_recv（）中使用的入站原始字节流的缓冲区长度。*/
#define NGHTTP2_INBOUND_BUFFER_LENGTH 16384

/* 传入保留流的默认最大数量*/
#define NGHTTP2_MAX_INCOMING_RESERVED_STREAMS 200

/* 即使SETTINGS_MAX_CONCURRENT_STREAMS比这个数字少，我们也会将NGHTTP2_MIN_IDLE_STREAMS流保持在空闲状态*/
#define NGHTTP2_MIN_IDLE_STREAMS 16

/* 出站队列中的最大项目数，这被认为是由对等方造成的洪泛。此处不考虑所有框架。我们只考虑PING+ACK和SETTING+ACK。这是因为它们都是对对等方发起的帧的响应，并且对等方可以发送任意数量的帧。若对等端不读取网络，则响应帧会堆积起来，这会导致内存耗尽。这里选择的值是任意的，但是安全的值，如果我们在这个数字中有这些帧，则认为是可疑的。*/
#define NGHTTP2_DEFAULT_MAX_OBQ_FLOOD_ITEM 1000

/* 最大并发流数的默认值。*/
#define NGHTTP2_DEFAULT_MAX_CONCURRENT_STREAMS 0xffffffffu

/* 接收传入帧时的内部状态*/
typedef enum {
  /* 接收帧标头*/
  NGHTTP2_IB_READ_CLIENT_MAGIC,
  NGHTTP2_IB_READ_FIRST_SETTINGS,
  NGHTTP2_IB_READ_HEAD,
  NGHTTP2_IB_READ_NBYTE,
  NGHTTP2_IB_READ_HEADER_BLOCK,
  NGHTTP2_IB_IGN_HEADER_BLOCK,
  NGHTTP2_IB_IGN_PAYLOAD,
  NGHTTP2_IB_FRAME_SIZE_ERROR,
  NGHTTP2_IB_READ_SETTINGS,
  NGHTTP2_IB_READ_GOAWAY_DEBUG,
  NGHTTP2_IB_EXPECT_CONTINUATION,
  NGHTTP2_IB_IGN_CONTINUATION,
  NGHTTP2_IB_READ_PAD_DATA,
  NGHTTP2_IB_READ_DATA,
  NGHTTP2_IB_IGN_DATA,
  NGHTTP2_IB_IGN_ALL,
  NGHTTP2_IB_READ_ALTSVC_PAYLOAD,
  NGHTTP2_IB_READ_ORIGIN_PAYLOAD,
  NGHTTP2_IB_READ_EXTENSION_PAYLOAD
} nghttp2_inbound_state;

typedef struct {
  nghttp2_frame frame;
  /* 扩展帧有效载荷的存储。帧->扩展。有效负载指向该结构以避免频繁的内存分配。*/
  nghttp2_ext_frame_payload ext_frame_payload;
  /* 收到的SETTINGS条目。对于标准设置条目，我们只保留最后看到的值。对于SETTINGS_HEADER_TABLE_SIZE，我们还在最后一个索引中保留最小值。*/
  nghttp2_settings_entry *iv;
  /* 指向小缓冲区raw_sbuf的缓冲区指针*/
  nghttp2_buf sbuf;
  /* 指向大缓冲区raw_lbuf的缓冲区指针*/
  nghttp2_buf lbuf;
  /* 大缓冲区，按需分配*/
  uint8_t *raw_lbuf;
  /* 填写的条目数|iv|*/
  size_t niv;
  /* |iv|可以存储的条目数。*/
  size_t max_niv;
  /* 当前帧还需要接收多少字节*/
  size_t payloadleft;
  /* 当前帧的填充长度*/
  size_t padlen;
  nghttp2_inbound_state state;
  /* 小缓冲区。当前缓冲区最大的连续块是帧头。我们缓冲了部分有效载荷，但它们小于帧头。*/
  uint8_t raw_sbuf[NGHTTP2_FRAME_HDLEN];
} nghttp2_inbound_frame;

typedef struct {
  uint32_t header_table_size;
  uint32_t enable_push;
  uint32_t max_concurrent_streams;
  uint32_t initial_window_size;
  uint32_t max_frame_size;
  uint32_t max_header_list_size;
  uint32_t enable_connect_protocol;
} nghttp2_settings_storage;

typedef enum {
  NGHTTP2_GOAWAY_NONE = 0,
  /* 标志表示发送GOAWAY后应终止连接。*/
  NGHTTP2_GOAWAY_TERM_ON_SEND = 0x1,
  /* 标志表示已发送终止会话的GOAWAY*/
  NGHTTP2_GOAWAY_TERM_SENT = 0x2,
  /* 标志表示GOAWAY已发送*/
  NGHTTP2_GOAWAY_SENT = 0x4,
  /* 标志表示收到GOAWAY*/
  NGHTTP2_GOAWAY_RECV = 0x8
} nghttp2_goaway_flag;

/* nghttp2_inflight_settings存储本地端点已发送到远程端点但尚未收到ACK的settings条目。*/
struct nghttp2_inflight_settings {
  struct nghttp2_inflight_settings *next;
  nghttp2_settings_entry *iv;
  size_t niv;
};

typedef struct nghttp2_inflight_settings nghttp2_inflight_settings;

struct nghttp2_session {
  nghttp2_map /* <nghttp2_stream*>*/ streams;
  /* 依赖树的根*/
  nghttp2_stream root;
  /* 出站紧急帧队列（PING和SETTINGS）*/
  nghttp2_outbound_queue ob_urgent;
  /* 非DATA帧的队列*/
  nghttp2_outbound_queue ob_reg;
  /* 用于创建HEADERS（请求或推送响应）帧的出站流的队列，该帧受SETTINGS_MAX_CONCURRENT_STREAMS限制。*/
  nghttp2_outbound_queue ob_syn;
  nghttp2_active_outbound_item aob;
  nghttp2_inbound_frame iframe;
  nghttp2_hd_deflater hd_deflater;
  nghttp2_hd_inflater hd_inflater;
  nghttp2_session_callbacks callbacks;
  /* 内存分配器*/
  nghttp2_mem mem;
  void *user_data;
  /* 指向最近传入的封闭流。如果没有封闭流，则为NULL。仅当会话初始化为服务器时使用。*/
  nghttp2_stream *closed_stream_head;
  /* 指向最旧的传入封闭流。如果没有封闭流，则为NULL。仅当会话初始化为服务器时使用。*/
  nghttp2_stream *closed_stream_tail;
  /* 指向最新的空闲流。如果没有空闲流，则为NULL。仅当会话初始化为服务器时使用。*/
  nghttp2_stream *idle_stream_head;
  /* 指向最旧的空闲流。如果没有空闲流，则为NULL。仅在会话初始化为服务器时使用。*/
  nghttp2_stream *idle_stream_tail;
  /* 飞行中设置值队列。带有ACK的设置不视为飞行中。*/
  nghttp2_inflight_settings *inflight_settings_head;
  /* 传出流的数量。这将由remote_settings.max_concurrent_streams限制。*/
  size_t num_outgoing_streams;
  /* 传入流的数量。这将由local_settings.max_concurrent_streams限制。*/
  size_t num_incoming_streams;
  /* 传入保留流的数量。这是处于保留（远程）状态的流数。RFC 7540不限制此数字。nghttp2提供nghttp2_option_set_max_reserved_remote_streams（）来实现这一点。如果使用了它，num_incoming_streams的上限为max_incoming_reserved_streams。客户端应用程序应该考虑设置此选项，因为没有该选项，服务器可以发送任意数量的PUSH_PROMISE，并耗尽客户端的内存。*/
  size_t num_incoming_reserved_streams;
  /* 传入保留流的最大数量（保留（远程）状态）。对于超过此限制的推送流，将发送RST_STREAM。*/
  size_t max_incoming_reserved_streams;
  /* 仍保留在|streams|hash中的已关闭流的数量。可以通过单个链接列表|closed_stream_head|访问关闭的流。当前实现只保留传入流，会话初始化为服务器。*/
  size_t num_closed_streams;
  /* |streams|hash中保留的空闲流数。可以通过双链接列表|idle_stream_head|访问空闲流。当前实现仅在会话初始化为服务器时保持空闲流。*/
  size_t num_idle_streams;
  /* 为nvbuf分配的字节数*/
  size_t nvbuflen;
  /* 用于检测出站队列中溢出的计数器。如果超过max_outbound_ack，会话将关闭。*/
  size_t obq_flood_counter_;
  /* 出站队列中传出SETTINGS ACK和PING ACK的最大数量。*/
  size_t max_outbound_ack;
  /* 要发送的标头块的最大长度。计算方法与nghttp2_hd_deflate_bound（）相同。*/
  size_t max_send_header_block_length;
  /* 每个settings帧接受的最大设置数。*/
  size_t max_settings;
  /* 下一个流ID。生成无符号int以检测>=（1<<31）。*/
  uint32_t next_stream_id;
  /* 此会话启动的最后一个流ID。对于客户端会话，这是它发送的最后一个流ID。对于服务器会话，它是PUSH_PROMISE中发送的最后一个承诺的流ID。*/
  int32_t last_sent_stream_id;
  /* 迄今为止收到的最大流ID*/
  int32_t last_recv_stream_id;
  /* 以某种方式处理的最大流ID。发送GOAWAY帧时，此值将用作最后一个流id。*/
  int32_t last_proc_stream_id;
  /* PING唯一ID的计数器。超过NGHTTP2_MAX_UNIQUE_ID时换行*/
  uint32_t next_unique_id;
  /* 这是我们在GOAWAY发送的最后一个流ID*/
  int32_t local_last_stream_id;
  /* 这是从远程端点接收的GOAWAY帧中的值。*/
  int32_t remote_last_stream_id;
  /* 当前发件人窗口大小。该值是根据远程端点的当前初始窗口大小计算的。*/
  int32_t remote_window_size;
  /* 跟踪在没有WINDOW_UPDATE的情况下接收的字节数。在向WINDOW_UPDATE提交负值后，此值可能为负值。*/
  int32_t recv_window_size;
  /* 应用程序消耗的字节数，现在取决于WINDOW_UPDATE。这仅在关闭自动WINDOW_UPDATE时使用。*/
  int32_t consumed_size;
  /* 使用向window_UPDATE提交负值的recv_window_size剪切量*/
  int32_t recv_reduction;
  /* 本地流量控制的窗口大小。它最初设置为NGHTTP2_INITIAL_CONNECTION_WINDOW_SIZE，可以通过提交WINDOW_UPDATE来增加/减少。请参见nghttp2_submit_window_update（）。*/
  int32_t local_window_size;
  /* 此标志用于指示本地端点从远程端点接收到初始SETTINGS帧。*/
  uint8_t remote_settings_received;
  /* 从远程终结点接收的设置值。*/
  nghttp2_settings_storage remote_settings;
  /* 本地端点的设置值。*/
  nghttp2_settings_storage local_settings;
  /* 选项标志。这是nghttp2_optmask的0或更多的位或。*/
  uint32_t opt_flags;
  /* 未检查本地SETTINGS_MAX_CONCURRENT_STREAMS值。如果传入流超过此值，我们将使用此值拒绝传入流。*/
  uint32_t pending_local_max_concurrent_stream;
  /* nghttp2_typemask中零或更多的位OR，表示已启用扩展帧的默认处理。*/
  uint32_t builtin_recv_ext_types;
  /* 未检查本地ENABLE_PUSH值。在收到SETTINGS ACK之前，我们使用此拒绝PUSH PROMISE。*/
  uint8_t pending_enable_push;
  /* 未检查本地ENABLE_CONNECT_PROTOCOL值。在接收SETTINGS_ACK之前，我们使用它来接受：protocol头字段。*/
  uint8_t pending_enable_connect_protocol;
  /* 如果会话是服务器端，则为非零。*/
  uint8_t server;
  /* 发送和/或接收指示GOAWAY的标志。这些标志由nghttp2_goaway_flag按位“或”组成。*/
  uint8_t goaway_flags;
  /* 此标志用于减少WINDOW_UPDATE对此会话的过度排队。非零不一定意味着WINDOW_UPDATE未排队。*/
  uint8_t window_update_queued;
  /* 应用程序愿意接收的扩展帧类型的位字段。要指定给定帧类型i的位，请使用user_recv_ext_types[i/8]&（1<<（i&0x7））。前10种帧类型是标准帧类型，不用于此位字段。若位被设置，则表示具有该类型的传入帧被传递给用户定义的回调，否则将忽略它们。*/
  uint8_t user_recv_ext_types[32];
};

/* 更新每个活动流的初始窗口大小时使用的结构。*/
typedef struct {
  nghttp2_session *session;
  int32_t new_window_size, old_window_size;
} nghttp2_update_window_size_arg;

typedef struct {
  nghttp2_session *session;
  /* 要关闭的流的链接列表*/
  nghttp2_stream *head;
  int32_t last_stream_id;
  /* 如果GOAWAY被发送到对等端，则非零，这意味着我们将关闭传入流。如果从对等方接收到GOAWAY，则为零，并且我们将关闭传出流。*/
  int incoming;
} nghttp2_close_stream_on_goaway_arg;

/* TODO流超时等*/

/*
 * 如果|stream_id|由本地终结点启动，则返回非零值。
 */
int nghttp2_session_is_my_stream_id(nghttp2_session *session,
                                    int32_t stream_id);

/*
 * 将|item|添加到|session|中的出站队列。当此函数成功时，它将获得|item|的所有权。所以呼叫方不能在成功时释放它。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_STREAM_CLOSED流已关闭（仅限DATA和PUSH_PROMISE帧）
 */
int nghttp2_session_add_item(nghttp2_session *session,
                             nghttp2_outbound_item *item);

/*
 * 为流|STREAM_id|添加RST_STREAM帧，错误代码为|error_code|。这是一个构建在nghttp2_session_add_frame（）之上的方便函数，可以轻松添加RST_STREAM。
 *
 * 如果给定流处于NGHTTP2_STREAM_CLOSING状态，此函数只返回0，而不添加RST_STREAM帧，因为流的多个RST_STREA是冗余的。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_session_add_rst_stream(nghttp2_session *session, int32_t stream_id,
                                   uint32_t error_code);

/*
 * 添加PING帧。这是一个建立在nghttp2_session_add_frame（）之上的方便函数，可以方便地添加PING。
 *
 * 如果|opaque_data|不为NULL，则它必须指向8字节的数据存储区域。复制|opaque_data|所指向的数据。它可以为NULL。在这种情况下，使用8字节NULL。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_FLOODED出站队列中的项目太多；仅当NGHTTP2_FLAG_ACK设置在|标志中时才会发生这种情况|
 */
int nghttp2_session_add_ping(nghttp2_session *session, uint8_t flags,
                             const uint8_t *opaque_data);

/*
 * 添加具有最后一个流ID |last_stream_ID|和错误代码|error_code|的GOAWAY帧。这是一个构建在nghttp2_session_add_frame（）之上的方便函数，可以轻松添加GOAWAY。|aux_flags |是一个或多个nghttp2_goaway_aux_flag的位或。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_INVALID_ARGUMENT |opaque_data_len|太大。
 */
int nghttp2_session_add_goaway(nghttp2_session *session, int32_t last_stream_id,
                               uint32_t error_code, const uint8_t *opaque_data,
                               size_t opaque_data_len, uint8_t aux_flags);

/*
 * 添加具有流ID |stream_ID|和窗口大小增量|WINDOW_size_increment|的WINDOW_UPDATE帧。这是一个构建在nghttp2_session_add_frame（）之上的方便函数，可以轻松添加WINDOW_UPDATE。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_session_add_window_update(nghttp2_session *session, uint8_t flags,
                                      int32_t stream_id,
                                      int32_t window_size_increment);

/*
 * 添加SETTINGS（设置）帧。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_FLOODED出站队列中的项目太多；仅当NGHTTP2_FLAG_ACK设置在|标志中时才会发生这种情况|
 */
int nghttp2_session_add_settings(nghttp2_session *session, uint8_t flags,
                                 const nghttp2_settings_entry *iv, size_t niv);

/*
 * 在|session|中创建具有流ID |stream_ID|、优先级|pri_spec|和标志|flags|的新流。|flags |是nghttp2_stream_flag的位或。由于在发送或接收初始HEADERS时调用此函数，因此这些标志将从中获取。流的状态设置为|initial_state|。|stream_user_data|是指向要与此流关联的任意用户提供的数据的指针。
 *
 * 如果|initial_state|为NGHTTP2_STREAM_RESERVED，则此函数将设置NGHTTP2_STEAM_FLAG_PUSH标志集。
 *
 * 此函数返回指向创建的新流对象的指针，或NULL。
 *
 * 此函数既不调整关闭流的数量，也不调整空闲流的数量。调用者应分别手动调用nghttp2_session_adjust_closed_stream（）或nghttp2_session_adjust_idle_stream）。
 */
nghttp2_stream *nghttp2_session_open_stream(nghttp2_session *session,
                                            int32_t stream_id, uint8_t flags,
                                            nghttp2_priority_spec *pri_spec,
                                            nghttp2_stream_state initial_state,
                                            void *stream_user_data);

/*
 * 关闭流ID为|stream_ID|的流。关闭的原因由|error_code|表示。关闭流时，将调用on_ststream_close_callback。
 *
 * 如果会话初始化为服务器，而|stream|是传入流，则流将被标记为已关闭，此函数将使用|stream|调用nghttp2_session_keep_closed_stream（）。否则，|stream|将从内存中删除。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足NGHTTP2_ERROR_INVALID_ARGUMENT指定的流不存在。NGHTTP2_ERR_CALLBACK_FAILURE回调函数失败。
 */
int nghttp2_session_close_stream(nghttp2_session *session, int32_t stream_id,
                                 uint32_t error_code);

/*
 * 从内存中删除|stream|。此函数返回后，无法访问流。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_session_destroy_stream(nghttp2_session *session,
                                   nghttp2_stream *stream);

/*
 * 尝试保持传入的关闭流|stream|。由于内存中最大流数的限制，|stream|不会关闭，只是从内存中删除（请参阅nghttp2_session_destroy_stream）。
 */
void nghttp2_session_keep_closed_stream(nghttp2_session *session,
                                        nghttp2_stream *stream);

/*
 * 将|stream|追加到链接列表|session->idle_stream_head|。我们对列表大小应用固定限制。为了符合该限制，将根据需要从列表中删除一个或多个最旧的流。
 */
void nghttp2_session_keep_idle_stream(nghttp2_session *session,
                                      nghttp2_stream *stream);

/*
 * 从空闲流链接列表中分离|stream|。
 */
void nghttp2_session_detach_idle_stream(nghttp2_session *session,
                                        nghttp2_stream *stream);

/*
 * 删除已关闭的流，以确保包括活动流和已关闭流在内的传入流的数量在允许的最大流数内。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_session_adjust_closed_stream(nghttp2_session *session);

/*
 * 删除空闲流以确保空闲流的数量在一定限制内。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_session_adjust_idle_stream(nghttp2_session *session);

/*
 * 如果不允许通过流|stream_id|进行进一步的接收和传输，请使用错误代码NGHTTP2_NO_error关闭流。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_INVALID_ARGUMENT指定的流不存在。
 */
int nghttp2_session_close_stream_if_shut_rdwr(nghttp2_session *session,
                                              nghttp2_stream *stream);

int nghttp2_session_on_request_headers_received(nghttp2_session *session,
                                                nghttp2_frame *frame);

int nghttp2_session_on_response_headers_received(nghttp2_session *session,
                                                 nghttp2_frame *frame,
                                                 nghttp2_stream *stream);

int nghttp2_session_on_push_response_headers_received(nghttp2_session *session,
                                                      nghttp2_frame *frame,
                                                      nghttp2_stream *stream);

/*
 * 在收到HEADERS时调用，假设|frame |已正确初始化。此函数首先验证接收到的帧，然后打开流并调用回调函数。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_IGN_HEADER_BLOCK帧被拒绝，必须对标头块进行解码，但必须忽略结果。NGHTTP2_ERR_CALLBACK_FAILURE read_CALLBACK失败
 */
int nghttp2_session_on_headers_received(nghttp2_session *session,
                                        nghttp2_frame *frame,
                                        nghttp2_stream *stream);

/*
 * 在收到PRIORITY时调用，假设|frame |已正确初始化。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_CALLBACK_FAILURE read_CALLBACK失败
 */
int nghttp2_session_on_priority_received(nghttp2_session *session,
                                         nghttp2_frame *frame);

/*
 * 在收到RST_STREAM时调用，假设|frame |已正确初始化。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足NGHTTP2_ERROR_CALLBACK_FAILURE read_CALLBACK失败
 */
int nghttp2_session_on_rst_stream_received(nghttp2_session *session,
                                           nghttp2_frame *frame);

/*
 * 在收到SETTINGS时调用，假设|frame |已正确初始化。如果|noack|为非零，则不会提交带有ACK的设置。如果|frame |设置了NGHTTP2_FLAG_ACK标志，则无论|noack|如何，都不会提交带有ACK的设置。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足NGHTTP2_ERROR_CALLBACK_FAILURE read_CALLBACK失败NGHTTP2_ERR_FLOODED出站队列中的项目太多，这很可能是由于对等方的错误行为造成的。
 */
int nghttp2_session_on_settings_received(nghttp2_session *session,
                                         nghttp2_frame *frame, int noack);

/*
 * 在接收PUSH_PROMISE时调用，假设|frame |已正确初始化。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_IGN_HEADER_BLOCK帧被拒绝，必须对标头块进行解码，但必须忽略结果。NGHTTP2_ERR_CALLBACK_FAILURE read_CALLBACK失败
 */
int nghttp2_session_on_push_promise_received(nghttp2_session *session,
                                             nghttp2_frame *frame);

/*
 * 当接收到PING时调用，假设|frame |已正确初始化。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_CALLBACK_FAILURE回调函数失败。NGHTTP2_ERR_FLOODED出站队列中的项目太多，这很可能是由于对等方的不当行为造成的。
 */
int nghttp2_session_on_ping_received(nghttp2_session *session,
                                     nghttp2_frame *frame);

/*
 * 在收到GOAWAY时调用，假设|frame |已正确初始化。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_CALLBACK_FAILURE回调函数失败。
 */
int nghttp2_session_on_goaway_received(nghttp2_session *session,
                                       nghttp2_frame *frame);

/*
 * 当接收到WINDOW_UPDATE时调用，假设|frame |已正确初始化。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_CALLBACK_FAILURE回调函数失败。
 */
int nghttp2_session_on_window_update_received(nghttp2_session *session,
                                              nghttp2_frame *frame);

/*
 * 在收到ALTSVC时调用，假设|frame |已正确初始化。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_CALLBACK_FAILURE回调函数失败。
 */
int nghttp2_session_on_altsvc_received(nghttp2_session *session,
                                       nghttp2_frame *frame);

/*
 * 在收到ORIGIN时调用，假设|frame |已正确初始化。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_CALLBACK_FAILURE回调函数失败。
 */
int nghttp2_session_on_origin_received(nghttp2_session *session,
                                       nghttp2_frame *frame);

/*
 * 当收到DATA时调用，假设|frame |已正确初始化。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_CALLBACK_FAILURE回调函数失败。
 */
int nghttp2_session_on_data_received(nghttp2_session *session,
                                     nghttp2_frame *frame);

/*
 * 返回流ID为|stream_ID|的nghttp2_stream*对象。如果此类流不存在，则可能为NULL。如果流标记为关闭，则此函数返回NULL。
 */
nghttp2_stream *nghttp2_session_get_stream(nghttp2_session *session,
                                           int32_t stream_id);

/*
 * 此函数的行为类似于nghttp2_session_get_stream（），但它返回流对象，即使它被标记为已关闭或处于nghttp2_stream_IDLE状态。
 */
nghttp2_stream *nghttp2_session_get_stream_raw(nghttp2_session *session,
                                               int32_t stream_id);

/*
 * 以线框格式打包DATA帧|frame |，并将其存储在|bufs|中。将使用|aux_data->data_prd|读取有效载荷。有效负载的长度最多为|datamax|字节。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_DEFERRED数据帧被延迟。NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE read_CALLBACK失败（流错误）。NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_CALLBACK_FAILURE read_CALLBACK失败（会话错误）。
 */
int nghttp2_session_pack_data(nghttp2_session *session, nghttp2_bufs *bufs,
                              size_t datamax, nghttp2_frame *frame,
                              nghttp2_data_aux_data *aux_data,
                              nghttp2_stream *stream);

/*
 * 弹出并返回要发送的下一个项目。如果没有此项，则返回NULL。此函数考虑最大并发流。这意味着如果session->ob_syn具有项，并且达到了最大并发流，则即使其他队列包含项，该函数也返回NULL。
 */
nghttp2_outbound_item *
nghttp2_session_pop_next_ob_item(nghttp2_session *session);

/*
 * 返回要发送的下一项。如果没有此项，则此函数返回NULL。此函数考虑最大并发流。这意味着如果session->ob_syn具有项，并且达到了最大并发流，则即使其他队列包含项，该函数也返回NULL。
 */
nghttp2_outbound_item *
nghttp2_session_get_next_ob_item(nghttp2_session *session);

/*
 * 使用|iv|更新本地设置。|iv|所指向的数组中的元素数由|niv|给出。此函数假定|iv|中的所有settings_id成员都在范围1到NGHTTP2_settings_MAX（含）之间。
 *
 * 在更新单个流的本地窗口大小时，如果窗口大小严格大于NGHTTP2_MAX_window_size，则针对此类流发出RST_stream。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_session_update_local_settings(nghttp2_session *session,
                                          nghttp2_settings_entry *iv,
                                          size_t niv);

/*
 * 重新确定|流|的优先级。新的优先级规范是|pri_spec|。调用方必须确保stream->hd。stream_id！=pri_spec->stream_id。
 *
 * 此函数不调整空闲流的数量。调用者应该稍后调用nghttp2_session_adjust_idle_stream（）。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_session_reprioritize_stream(nghttp2_session *session,
                                        nghttp2_stream *stream,
                                        const nghttp2_priority_spec *pri_spec);

/*
 * 使用|error_code|终止当前|会话|。|reason|是以NULL结尾的调试字符串。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_INVALID_ARGUMENT |原因|太长。
 */
int nghttp2_session_terminate_session_with_reason(nghttp2_session *session,
                                                  uint32_t error_code,
                                                  const char *reason);

/*
 * 为连接级流控制累加接收的字节|delta_size|，并决定是否向连接发送WINDOW_UPDATE。如果设置了NGHTTP2_OPT_NO_AUTO_WINDOW_UPDATE，则不会发送WINDOW_UPDATE。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_session_update_recv_connection_window_size(nghttp2_session *session,
                                                       size_t delta_size);

/*
 * 累加流级流控制的接收字节|delta_size|，并决定是否向该流发送WINDOW_UPDATE。如果设置了NGHTTP2_OPT_NO_AUTO_WINDOW_UPDATE，则不会发送WINDOW_UPDATE。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_session_update_recv_stream_window_size(nghttp2_session *session,
                                                   nghttp2_stream *stream,
                                                   size_t delta_size,
                                                   int send_window_update);

#endif /* NGHTTP2_SESSION_H */

