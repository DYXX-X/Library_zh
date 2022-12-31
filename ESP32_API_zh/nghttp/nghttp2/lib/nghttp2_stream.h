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
#ifndef NGHTTP2_STREAM_H
#define NGHTTP2_STREAM_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>
#include "nghttp2_outbound_item.h"
#include "nghttp2_map.h"
#include "nghttp2_pq.h"
#include "nghttp2_int.h"

/*
 * 如果本地对等方是流发起方：NGHTTP2_stream_OPENING：发送请求HEADERS时NGHTTP2_stream_OPENED：接收响应HEADERS后NGHTTP2_stream_CLOSING：排队RST_stream时
 *
 * 如果远程对等方是流发起方：NGHTTP2_stream_OPENING：在接收请求HEADERS时NGHTTP2_stream_OPENED：在发送响应HEADERS后NGHTTP2_stream_CLOSING：在排队RST_stream时
 */
typedef enum {
  /* 初始状态*/
  NGHTTP2_STREAM_INITIAL,
  /* 对于流启动器：已发送请求HEADERS，但尚未收到响应HEADERS。对于接收方：请求HEADERS已收到，但尚未发送响应HEADERS。*/
  NGHTTP2_STREAM_OPENING,
  /* 对于流启动器：收到响应HEADERS。对于接收方：发送响应HEADERS。*/
  NGHTTP2_STREAM_OPENED,
  /* 接收到RST_STREAM，但不知何故，我们需要将流保存在内存中。*/
  NGHTTP2_STREAM_CLOSING,
  /* 接收或发送PUSH_PROMISE*/
  NGHTTP2_STREAM_RESERVED,
  /* 如果流用作依赖关系树中的锚点，则在该状态下创建该流。*/
  NGHTTP2_STREAM_IDLE
} nghttp2_stream_state;

typedef enum {
  NGHTTP2_SHUT_NONE = 0,
  /* 表示不允许进一步接收。*/
  NGHTTP2_SHUT_RD = 0x01,
  /* 表示将禁止进一步传输。*/
  NGHTTP2_SHUT_WR = 0x02,
  /* 表示将禁止进一步的接收和传输。*/
  NGHTTP2_SHUT_RDWR = NGHTTP2_SHUT_RD | NGHTTP2_SHUT_WR
} nghttp2_shut_flag;

typedef enum {
  NGHTTP2_STREAM_FLAG_NONE = 0,
  /* 指示此流是推送流，尚未打开。*/
  NGHTTP2_STREAM_FLAG_PUSH = 0x01,
  /* 指示此流已关闭*/
  NGHTTP2_STREAM_FLAG_CLOSED = 0x02,
  /* 指示由于流控制而延迟该项。*/
  NGHTTP2_STREAM_FLAG_DEFERRED_FLOW_CONTROL = 0x04,
  /* 指示项目被用户回调延迟*/
  NGHTTP2_STREAM_FLAG_DEFERRED_USER = 0x08,
  /* NGHTTP2_STREAM_FLAG_DEFERRED_FLOW_CONTROL和NGHTTP2_ STREAM_FRAG_DEFERED_USER的位或。*/
  NGHTTP2_STREAM_FLAG_DEFERRED_ALL = 0x0c

} nghttp2_stream_flag;

/* 用于强制HTTP语义的HTTP相关标志*/
typedef enum {
  NGHTTP2_HTTP_FLAG_NONE = 0,
  /* 到目前为止看到的标题字段*/
  NGHTTP2_HTTP_FLAG__AUTHORITY = 1,
  NGHTTP2_HTTP_FLAG__PATH = 1 << 1,
  NGHTTP2_HTTP_FLAG__METHOD = 1 << 2,
  NGHTTP2_HTTP_FLAG__SCHEME = 1 << 3,
  /* host不是伪标头，但我们需要host或：authority*/
  NGHTTP2_HTTP_FLAG_HOST = 1 << 4,
  NGHTTP2_HTTP_FLAG__STATUS = 1 << 5,
  /* HTTP请求的必需标头字段，CONNECT方法除外。*/
  NGHTTP2_HTTP_FLAG_REQ_HEADERS = NGHTTP2_HTTP_FLAG__METHOD |
                                  NGHTTP2_HTTP_FLAG__PATH |
                                  NGHTTP2_HTTP_FLAG__SCHEME,
  NGHTTP2_HTTP_FLAG_PSEUDO_HEADER_DISALLOWED = 1 << 6,
  /* HTTP方法标志*/
  NGHTTP2_HTTP_FLAG_METH_CONNECT = 1 << 7,
  NGHTTP2_HTTP_FLAG_METH_HEAD = 1 << 8,
  NGHTTP2_HTTP_FLAG_METH_OPTIONS = 1 << 9,
  NGHTTP2_HTTP_FLAG_METH_UPGRADE_WORKAROUND = 1 << 10,
  NGHTTP2_HTTP_FLAG_METH_ALL = NGHTTP2_HTTP_FLAG_METH_CONNECT |
                               NGHTTP2_HTTP_FLAG_METH_HEAD |
                               NGHTTP2_HTTP_FLAG_METH_OPTIONS |
                               NGHTTP2_HTTP_FLAG_METH_UPGRADE_WORKAROUND,
  /* ：路径类别*/
  /* 路径以“/”开头*/
  NGHTTP2_HTTP_FLAG_PATH_REGULAR = 1 << 11,
  /* 路径“*”*/
  NGHTTP2_HTTP_FLAG_PATH_ASTERISK = 1 << 12,
  /* 计划*/
  /* “http”或“https”方案*/
  NGHTTP2_HTTP_FLAG_SCHEME_HTTP = 1 << 13,
  /* 如果预期最终响应，则设置*/
  NGHTTP2_HTTP_FLAG_EXPECT_FINAL_RESPONSE = 1 << 14,
  NGHTTP2_HTTP_FLAG__PROTOCOL = 1 << 15,
} nghttp2_http_flag;

struct nghttp2_stream {
  /* 侵入性地图*/
  nghttp2_map_entry map_entry;
  /* dep_prev->obq的条目*/
  nghttp2_pq_entry pq_entry;
  /* 存储直接后代（nghttp2_stream）的优先级队列。只有流本身有一些数据要发送，或者流的后代有一些数据需要发送。*/
  nghttp2_pq obq;
  /* 请求/响应主体的内容长度-如果未知，则为1。*/
  int64_t content_length;
  /* 到目前为止接收到的尸体*/
  int64_t recv_content_length;
  /* 直接派生流的基本last_cycle。*/
  uint64_t descendant_last_cycle;
  /* 发送项目的下一个计划时间*/
  uint64_t cycle;
  /* 用于直接后代流的下一个seq*/
  uint64_t descendant_next_seq;
  /* 用于优先级排序的辅助键，以打破循环的平局。对于单亲流，该值单调增加。*/
  uint64_t seq;
  /* 指向形成依赖关系树的指针。如果多个流依赖于一个流，则只有一个流（最左边）具有非NULL dep_prev，该dep_prev指向它所依赖的流。其余流使用sib_prev和sib_next链接。具有非空dep_prev的流总是空sib_prev。最右边的流具有NULL sib_next。如果此流是依赖关系树的根，dep_prev和sib_prev为NULL。*/
  nghttp2_stream *dep_prev, *dep_next;
  nghttp2_stream *sib_prev, *sib_next;
  /* 当流在关闭后被保存时，它可能被保存在nghttp2_session closed_stream_head指向的双链接列表中。closed_next指向下一个流对象（如果它是列表的元素）。*/
  nghttp2_stream *closed_prev, *closed_next;
  /* 用户为此流提供的任意数据。*/
  void *stream_user_data;
  /* 要发送的项目*/
  nghttp2_outbound_item *item;
  /* 帧有效负载的最后写入长度*/
  size_t last_writelen;
  /* 流ID*/
  int32_t stream_id;
  /* 当前远程窗口大小。该值是根据远程端点的当前初始窗口大小计算的。*/
  int32_t remote_window_size;
  /* 跟踪在没有WINDOW_UPDATE的情况下接收的字节数。在向WINDOW_UPDATE提交负值后，该值可能为负值*/
  int32_t recv_window_size;
  /* 应用程序消耗的字节数，现在取决于WINDOW_UPDATE。这仅在关闭自动WINDOW_UPDATE时使用。*/
  int32_t consumed_size;
  /* 使用向window_UPDATE提交负值的recv_window_size剪切量*/
  int32_t recv_reduction;
  /* 本地流量控制的窗口大小。它最初设置为NGHTTP2_INITIAL_WINDW_SIZE，可以通过提交WINDOW_UPDATE来增加/减少。请参见nghttp2_submit_window_update（）。*/
  int32_t local_window_size;
  /* 这条河流的重量*/
  int32_t weight;
  /* 计算周期时，这是未支付的罚款（抵消）。*/
  uint32_t pending_penalty;
  /* 直系后代的权重总和*/
  int32_t sum_dep_weight;
  nghttp2_stream_state state;
  /* 来自远程服务器的状态代码*/
  int16_t status_code;
  /* 零个或多个nghttp2_http_flag值的位或*/
  uint16_t http_flags;
  /* 这是nghttp2_stream_flag的0或更多的位或。*/
  uint8_t flags;
  /* 零个或多个nghttp2_shut_flag值的位或*/
  uint8_t shut_flags;
  /* 如果此流已排队到dep_prev指向的流，则为非零。我们保持不变，即如果一个流被排队，那么它的祖先（除了根之外）也被排队。此不变量可能在致命错误条件下中断。*/
  uint8_t queued;
  /* 此标志用于减少WINDOW_UPDATE对此流的过度排队。非零不一定意味着WINDOW_UPDATE未排队。*/
  uint8_t window_update_queued;
};

void nghttp2_stream_init(nghttp2_stream *stream, int32_t stream_id,
                         uint8_t flags, nghttp2_stream_state initial_state,
                         int32_t weight, int32_t remote_initial_window_size,
                         int32_t local_initial_window_size,
                         void *stream_user_data, nghttp2_mem *mem);

void nghttp2_stream_free(nghttp2_stream *stream);

/*
 * 禁止进一步的接收或传输，或两者都禁止|flag|是nghttp2_shut_flag中的一个或多个的位或。
 */
void nghttp2_stream_shutdown(nghttp2_stream *stream, nghttp2_shut_flag flag);

/*
 * 延迟|stream->item|。在|stream->item|==NULL的情况下，我们不会调用此函数。|flags |是NGHTTP2_STREAM_FLAG_DEFERRED_USER和NGHTTP2_STEAM_FLAG-DEFERRED_FLOW_CONTROL中的零或多个的位或。|标志|表示此操作的原因。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_stream_defer_item(nghttp2_stream *stream, uint8_t flags);

/*
 * 将此流中的延迟数据恢复为活动状态。|标志|是以下值的一个或多个按位“或”：NGHTTP2_STREAM_FLAG_DEFERRED_USER和NGHTTP2_STEAM_FLAG-DEFERRED_FLOW_CONTROL，如果设置了给定的掩码，则清除它们。因此，即使调用了此函数，如果其中一个标志仍然设置，数据也不会变为活动状态。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_stream_resume_deferred_item(nghttp2_stream *stream, uint8_t flags);

/*
 * 如果项目因任何原因延迟，则返回非零。
 */
int nghttp2_stream_check_deferred_item(nghttp2_stream *stream);

/*
 * 如果项被流控制延迟，则返回非零。
 */
int nghttp2_stream_check_deferred_by_flow_control(nghttp2_stream *stream);

/*
 * 使用新值|new_initial_window_size|更新远程窗口大小。|old_initial_window_size|用于计算当前窗口大小。
 *
 * 如果此函数成功，则返回0或-1。失败是由于溢出。
 */
int nghttp2_stream_update_remote_initial_window_size(
    nghttp2_stream *stream, int32_t new_initial_window_size,
    int32_t old_initial_window_size);

/*
 * 使用新值|new_initial_window_size|更新本地窗口大小。|old_initial_window_size|用于计算当前窗口大小。
 *
 * 如果此函数成功，则返回0或-1。失败是由于溢出。
 */
int nghttp2_stream_update_local_initial_window_size(
    nghttp2_stream *stream, int32_t new_initial_window_size,
    int32_t old_initial_window_size);

/*
 * 如果承诺的流|stream|被HEADERS回复，则调用此函数。此函数将|stream|的状态设置为NGHTTP2_stream_OPENED。
 */
void nghttp2_stream_promise_fulfilled(nghttp2_stream *stream);

/*
 * 如果|target|是|stream|的祖先，则返回非零。
 */
int nghttp2_stream_dep_find_ancestor(nghttp2_stream *stream,
                                     nghttp2_stream *target);

/*
 * 如果从依赖关系树中删除了|stream|，则计算|stream|下|weight|的流的分布权重。
 */
int32_t nghttp2_stream_dep_distributed_weight(nghttp2_stream *stream,
                                              int32_t weight);

/*
 * 使|stream|依赖于|dep_stream|。此依赖项是独占的。|dep_stream|的所有现有直接后代都将成为|stream|的后代。此函数假定|stream->item|为NULL。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_stream_dep_insert(nghttp2_stream *dep_stream,
                              nghttp2_stream *stream);

/*
 * 使|stream|依赖于|dep_stream|。此依赖关系不是排他性的。此函数假定|stream->item|为NULL。
 */
void nghttp2_stream_dep_add(nghttp2_stream *dep_stream, nghttp2_stream *stream);

/*
 * 从当前依赖关系树中删除|stream|。此函数假定|stream->item|为NULL。
 */
int nghttp2_stream_dep_remove(nghttp2_stream *stream);

/*
 * 将|item|附加到|stream|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_stream_attach_item(nghttp2_stream *stream,
                               nghttp2_outbound_item *item);

/*
 * 分离|stream->item|。此函数不释放|stream->item|。呼叫者必须释放它。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_stream_detach_item(nghttp2_stream *stream);

/*
 * 使|stream|依赖于|dep_stream|。此依赖项是独占的。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_stream_dep_insert_subtree(nghttp2_stream *dep_stream,
                                      nghttp2_stream *stream);

/*
 * 使|stream|依赖于|dep_stream|。此依赖关系不是排他性的。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_stream_dep_add_subtree(nghttp2_stream *dep_stream,
                                   nghttp2_stream *stream);

/*
 * 删除根流为|stream|的子树。删除的子树中流的有效权重不会更新。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
void nghttp2_stream_dep_remove_subtree(nghttp2_stream *stream);

/*
 * 如果|stream|在任何依赖关系树中，则返回非零。
 */
int nghttp2_stream_in_dep_tree(nghttp2_stream *stream);

/*
 * 计划|stream|的项的传输，假设stream->item已附加，stream->last_writelen已更新。
 */
void nghttp2_stream_reschedule(nghttp2_stream *stream);

/*
 * 将|stream|的权重更改为|weight|。如果|stream|已排队，将根据新的权重重新安排。
 */
void nghttp2_stream_change_weight(nghttp2_stream *stream, int32_t weight);

/*
 * 返回具有最高优先级的流，更新所选流的祖先的descendant_last_cycle。
 */
nghttp2_outbound_item *
nghttp2_stream_next_outbound_item(nghttp2_stream *stream);

#endif /* NGHTTP2_STREAM */

