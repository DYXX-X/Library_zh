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
#ifndef NGHTTP2_OUTBOUND_ITEM_H
#define NGHTTP2_OUTBOUND_ITEM_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>
#include "nghttp2_frame.h"
#include "nghttp2_mem.h"

/* 用于HEADERS和PUSH_PROMISE框架的结构*/
typedef struct {
  nghttp2_data_provider data_prd;
  void *stream_user_data;
  /* RST_STREAM在队列中取消请求HEADERS时的错误代码。*/
  uint32_t error_code;
  /* 如果取消请求HEADERS，则为非零。错误代码存储在|error_code|中。*/
  uint8_t canceled;
} nghttp2_headers_aux_data;

/* 用于DATA帧的结构*/
typedef struct {
  /**
   * 要为此data帧发送的数据。
   */
  nghttp2_data_provider data_prd;
  /**
   * DATA帧的标志。我们在这里使用单独的标志和nghttp2_data帧。后者包含实际发送给对等方的标志。此|标志|可以包含NGHTTP2_FLAG_END_STREAM，只有当|eof|变为非零时，NGHTTP2_data中的标志才会设置NGHTTP2_FLAG_END_STREAM。
   */
  uint8_t flags;
  /**
   * 指示是否达到EOF的标志。最初|eof|为0。读取所有数据后，它变为1。
   */
  uint8_t eof;
  /**
   * 指示使用NGHTTP2_DATA_flag_NO_COCOPY的标志。
   */
  uint8_t no_copy;
} nghttp2_data_aux_data;

typedef enum {
  NGHTTP2_GOAWAY_AUX_NONE = 0x0,
  /* 指示会话应该在传输该帧之后终止。*/
  NGHTTP2_GOAWAY_AUX_TERM_ON_SEND = 0x1,
  /* 表示此GOAWAY只是一个正常关机的通知。无nghttp2_session。应根据对该帧的反应更新goaway_flags。*/
  NGHTTP2_GOAWAY_AUX_SHUTDOWN_NOTICE = 0x2
} nghttp2_goaway_aux_flag;

/* 用于GOAWAY框架的结构*/
typedef struct {
  /* nghttp2_goaway_aux_flag中的一个或多个的位或。*/
  uint8_t flags;
} nghttp2_goaway_aux_data;

/* 用于扩展框架的结构*/
typedef struct {
  /* 如果此扩展框架是由库函数序列化的，而不是用户定义的回调，则为非零。*/
  uint8_t builtin;
} nghttp2_ext_aux_data;

/* 无法存储在nghttp2_frame结构中的其他数据*/
typedef union {
  nghttp2_data_aux_data data;
  nghttp2_headers_aux_data headers;
  nghttp2_goaway_aux_data goaway;
  nghttp2_ext_aux_data ext;
} nghttp2_aux_data;

struct nghttp2_outbound_item;
typedef struct nghttp2_outbound_item nghttp2_outbound_item;

struct nghttp2_outbound_item {
  nghttp2_frame frame;
  /* 扩展帧有效载荷的存储。帧->扩展。有效负载指向该结构以避免频繁的内存分配。*/
  nghttp2_ext_frame_payload ext_frame_payload;
  nghttp2_aux_data aux_data;
  /* 优先级比较中使用的优先级。较小的较早供应。对于PING，SETTINGS和非DATA帧（不包括响应HEADERS帧）具有上面定义的专用周期值。对于DATA帧，通过考虑有效权重和先前发送的帧有效载荷长度来计算周期，从而使传输量分布在与有效权重成比例的流上（在树内）。*/
  uint64_t cycle;
  nghttp2_outbound_item *qnext;
  /* 如果此对象已排队，则非零，但作为项附加到流的DATA或HEADER除外。*/
  uint8_t queued;
};

/*
 * 初始化|项|。此函数中不进行内存分配。在框架成员初始化之前，不要调用nghttp2_outbound_item_free（）。
 */
void nghttp2_outbound_item_init(nghttp2_outbound_item *item);

/*
 * 取消分配|item|的资源。如果|item|为NULL，则此函数不执行任何操作。
 */
void nghttp2_outbound_item_free(nghttp2_outbound_item *item, nghttp2_mem *mem);

/*
 * nghttp2_outbound_item的队列。
 */
typedef struct {
  nghttp2_outbound_item *head, *tail;
  /* 此队列中的项目数。*/
  size_t n;
} nghttp2_outbound_queue;

void nghttp2_outbound_queue_init(nghttp2_outbound_queue *q);

/* 将|item|推入|q|*/
void nghttp2_outbound_queue_push(nghttp2_outbound_queue *q,
                                 nghttp2_outbound_item *item);

/* 从|q|开始在顶部弹出|item|。如果|q|为空，则不会发生任何事情。*/
void nghttp2_outbound_queue_pop(nghttp2_outbound_queue *q);

/* 返回顶部项目。*/
#define nghttp2_outbound_queue_top(Q) ((Q)->head)

/* 返回队列的大小*/
#define nghttp2_outbound_queue_size(Q) ((Q)->n)

#endif /* NGHTTP2_OUTBOUND_ITEM_H */

