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
#ifndef SHRPX_DOWNSTREAM_H
#define SHRPX_DOWNSTREAM_H

#include "shrpx.h"

#include <cinttypes>
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <algorithm>

#include <ev.h>

#include <nghttp2/nghttp2.h>

#include "llhttp.h"

#include "shrpx_io_control.h"
#include "shrpx_log_config.h"
#include "http2.h"
#include "memchunk.h"
#include "allocator.h"

using namespace nghttp2;

namespace shrpx {

class Upstream;
class DownstreamConnection;
struct BlockedLink;
struct DownstreamAddrGroup;
struct DownstreamAddr;

class FieldStore {
public:
  FieldStore(BlockAllocator &balloc, size_t headers_initial_capacity)
      : content_length(-1),
        balloc_(balloc),
        buffer_size_(0),
        header_key_prev_(false),
        trailer_key_prev_(false) {
    headers_.reserve(headers_initial_capacity);
  }

  const HeaderRefs &headers() const { return headers_; }
  const HeaderRefs &trailers() const { return trailers_; }

  HeaderRefs &headers() { return headers_; }

  const void add_extra_buffer_size(size_t n) { buffer_size_ += n; }
  size_t buffer_size() const { return buffer_size_; }

  size_t num_fields() const { return headers_.size() + trailers_.size(); }

  // 返回指向名为|name|的标头字段的指针。如果
  // 多个标头的名称为|name|，返回最后一次出现的位置
  // 开始。如果未找到此类标头，则返回nullptr。
  const HeaderRefs::value_type *header(int32_t token) const;
  HeaderRefs::value_type *header(int32_t token);
  // 返回指向名为|name|的标头字段的指针。如果没有
  // 如果找到此类标头，则返回nullptr。
  const HeaderRefs::value_type *header(const StringRef &name) const;

  void add_header_token(const StringRef &name, const StringRef &value,
                        bool no_index, int32_t token);

  // 添加标题字段名称|名称|。首先，标题字段的副本
  // name由name指向。长度名称的c_str（）。size（），并且
  // 存储。
  void alloc_add_header_name(const StringRef &name);

  void append_last_header_key(const char *data, size_t len);
  void append_last_header_value(const char *data, size_t len);

  bool header_key_prev() const { return header_key_prev_; }

  // 分析内容长度，并将其记录在字段中。如果有
  // 多重内容长度，返回-1。
  int parse_content_length();

  // 清空标题。
  void clear_headers();

  void add_trailer_token(const StringRef &name, const StringRef &value,
                         bool no_index, int32_t token);

  // 添加尾部字段名|name|。首先，拖车字段的副本
  // name由name指向。长度名称的c_str（）。size（），并且
  // 存储。
  void alloc_add_trailer_name(const StringRef &name);

  void append_last_trailer_key(const char *data, size_t len);
  void append_last_trailer_value(const char *data, size_t len);

  bool trailer_key_prev() const { return trailer_key_prev_; }

  // erase_content_length_and_transfer_encoding擦除内容长度
  // 以及传输编码报头字段。
  void erase_content_length_and_transfer_encoding();

  // 内容长度，如果未知，则为-1。
  int64_t content_length;

private:
  BlockAllocator &balloc_;
  HeaderRefs headers_;
  // 拖车字段。对于HTTP/1.1，仅包含尾部字段
  // 使用分块编码。对于HTTP/2，没有这样的限制。
  HeaderRefs trailers_;
  // headers_和trailers_中名称和值的长度之和。
  // 这也可以通过add_extra_buffer_size（）来增加
  // 在HTTP/1.x请求的情况下，考虑请求URI。
  size_t buffer_size_;
  bool header_key_prev_;
  bool trailer_key_prev_;
};

// HTTP/2中允许的协议：协议头字段。
enum class ConnectProto {
  NONE,
  WEBSOCKET,
};

struct Request {
  Request(BlockAllocator &balloc)
      : fs(balloc, 16),
        recv_body_length(0),
        unconsumed_body_length(0),
        method(-1),
        http_major(1),
        http_minor(1),
        connect_proto(ConnectProto::NONE),
        upgrade_request(false),
        http2_upgrade_seen(false),
        connection_close(false),
        http2_expect_body(false),
        no_authority(false),
        forwarded_once(false) {}

  void consume(size_t len) {
    assert(unconsumed_body_length >= len);
    unconsumed_body_length -= len;
  }

  bool regular_connect_method() const {
    return method == HTTP_CONNECT && connect_proto == ConnectProto::NONE;
  }

  bool extended_connect_method() const {
    return connect_proto != ConnectProto::NONE;
  }

  FieldStore fs;
  // 收到所有请求标头字段时的时间戳。
  std::shared_ptr<Timestamp> tstamp;
  // 请求方案。对于HTTP/2，这是：scheme头字段值。
  // 对于HTTP/1.1，这是从URI或连接推导出来的。
  StringRef scheme;
  // 请求权限。这是HTTP/2:authority头字段值
  // 或主机标头字段值。我们可以从绝对形式推导出来
  // HTTP/1请求。我们还存储HTTP/1请求的权限。
  // 如果请求来自HTTP/1.0而没有主机，则此字段可能为空
  // 标题字段和原始表单。
  StringRef authority;
  // 请求路径，包括查询组件。对于HTTP/1.1，这是
  // 请求目标。对于HTTP/2，这是：路径头字段值。
  // 对于CONNECT请求，这是空的。
  StringRef path;
  // 这是原始权限，不能按模式更改
  // mruby脚本。
  StringRef orig_authority;
  // 这是每个模式无法更改的原始路径
  // mruby脚本。
  StringRef orig_path;
  // 到目前为止收到的请求体的长度
  int64_t recv_body_length;
  // 应用程序尚未使用的字节数。
  size_t unconsumed_body_length;
  int method;
  // HTTP主要和次要版本
  int http_major, http_minor;
  // connect_proto在HTTP/2中指定：协议伪头字段
  // 这实现了扩展的CONNECT方法。如果
  // 为了方便起见，在h1前端请求WebSocket升级。
  ConnectProto connect_proto;
  // 如果请求是HTTP升级（HTTP升级或
  // CONNECT方法）。不包括升级到HTTP/2。对于HTTP/2
  // 升级，检查get_http2_Upgrade_request（）。
  bool upgrade_request;
  // 如果在升级头字段中看到h2c，则为true。
  bool http2_upgrade_seen;
  bool connection_close;
  // 如果这是HTTP/2，则为true，并且需要请求体。请注意
  // 我们这里不考虑HTTP方法。
  bool http2_expect_body;
  // 如果请求没有任何有关权限的信息，则为true。
  // 当：对于HTTP/2请求，缺少：authority时会发生这种情况。
  // 对于HTTP/1请求，使用原点或星号形式。
  bool no_authority;
  // 如果对请求执行了一次后端选择，则为true。
  // orig_authority和orig_path具有以下权限和路径
  // 用于第一后端选择。
  bool forwarded_once;
};

struct Response {
  Response(BlockAllocator &balloc)
      : fs(balloc, 32),
        recv_body_length(0),
        unconsumed_body_length(0),
        http_status(0),
        http_major(1),
        http_minor(1),
        connection_close(false),
        headers_only(false) {}

  void consume(size_t len) {
    assert(unconsumed_body_length >= len);
    unconsumed_body_length -= len;
  }

  // 如果资源由方案、权限和路径表示，则返回true
  // 已被推送。
  bool is_resource_pushed(const StringRef &scheme, const StringRef &authority,
                          const StringRef &path) const {
    if (!pushed_resources) {
      return false;
    }
    return std::find(std::begin(*pushed_resources), std::end(*pushed_resources),
                     std::make_tuple(scheme, authority, path)) !=
           std::end(*pushed_resources);
  }

  // 记住，由方案、权限和路径表示的资源
  // 按下。
  void resource_pushed(const StringRef &scheme, const StringRef &authority,
                       const StringRef &path) {
    if (!pushed_resources) {
      pushed_resources = std::make_unique<
          std::vector<std::tuple<StringRef, StringRef, StringRef>>>();
    }
    pushed_resources->emplace_back(scheme, authority, path);
  }

  FieldStore fs;
  // 推送的方案、权限和路径的元组数组
  // 资源这是必需的，因为RFC 8297指出服务器
  // 通常包括出现在非最终响应中的头字段
  // 最终响应头字段中的头字段。不检查
  // 无论是否已经推送了特定资源，我们
  // 最终推送同一资源至少两次。这是未知的
  // 我们应该使用更复杂的数据结构（例如std:：set）
  // 以更快地找到资源。
  std::unique_ptr<std::vector<std::tuple<StringRef, StringRef, StringRef>>>
      pushed_resources;
  // 到目前为止收到的响应体长度
  int64_t recv_body_length;
  // 应用程序尚未使用的字节数。这是
  // 主要用于HTTP/2后端。
  size_t unconsumed_body_length;
  // HTTP状态代码
  unsigned int http_status;
  int http_major, http_minor;
  bool connection_close;
  // 如果响应仅包含HEADERS，并且
  // END_STREAM。这用于告诉Http2Upstream它可以发送
  // 仅具有END_STREAM标志的单个HEADER响应。
  bool headers_only;
};

enum class DownstreamState {
  INITIAL,
  HEADER_COMPLETE,
  MSG_COMPLETE,
  STREAM_CLOSED,
  CONNECT_FAIL,
  MSG_RESET,
  // 标头包含无效的标头字段。我们可以安全地发送错误
  // 对客户端的响应（502）。
  MSG_BAD_HEADER,
  // HTTP/1请求中的头字段超过了配置限制。
  // 此状态仅从INITIAL状态转换
  // 用于向客户端发送431状态码。
  HTTP1_REQUEST_HEADER_TOO_LARGE,
};

enum class DispatchState {
  NONE,
  PENDING,
  BLOCKED,
  ACTIVE,
  FAILURE,
};

class Downstream {
public:
  Downstream(Upstream *upstream, MemchunkPool *mcpool, int32_t stream_id);
  ~Downstream();
  void reset_upstream(Upstream *upstream);
  Upstream *get_upstream() const;
  void set_stream_id(int32_t stream_id);
  int32_t get_stream_id() const;
  void set_assoc_stream_id(int32_t stream_id);
  int32_t get_assoc_stream_id() const;
  void pause_read(IOCtrlReason reason);
  int resume_read(IOCtrlReason reason, size_t consumed);
  void force_resume_read();
  // 设置下游HTTP2连接的流ID。
  void set_downstream_stream_id(int32_t stream_id);
  int32_t get_downstream_stream_id() const;

  int attach_downstream_connection(std::unique_ptr<DownstreamConnection> dconn);
  void detach_downstream_connection();
  DownstreamConnection *get_downstream_connection();
  // 返回dconnen_并使dconnen_。
  std::unique_ptr<DownstreamConnection> pop_downstream_connection();

  // 如果输出缓冲区已满，则返回true。如果基础dconnen_是
  // NULL，此函数始终返回false。
  bool request_buf_full();
  // 如果在中成功升级（HTTP升级或CONNECT），则返回true
  // h1后端。这不应取决于inspect_http1_response（）。
  void check_upgrade_fulfilled_http1();
  // 如果在中成功升级（HTTP升级或CONNECT），则返回true
  // h2后端。
  void check_upgrade_fulfilled_http2();
  // 如果调用导致升级成功，则返回true
  // check_upgrade_finished_http*（）。HTTP/2升级被排除。
  bool get_upgraded() const;
  // 检查HTTP/2请求。
  void inspect_http2_request();
  // 检查HTTP/1请求。这将检查请求是否
  // 升级请求和传输编码等。
  void inspect_http1_request();
  // 如果请求为HTTP/2的HTTP升级，则返回true
  bool get_http2_upgrade_request() const;
  // 返回HTTP2设置请求头字段的值。
  StringRef get_http2_settings() const;

  // 下游请求API
  const Request &request() const { return req_; }
  Request &request() { return req_; }

  // 计算碎饼干的数量
  size_t count_crumble_request_cookie();
  // 磕磕绊绊（用“；”分隔饼干）并添加它们
  // 在|nva|中。标头：：no_index被继承。
  void crumble_request_cookie(std::vector<nghttp2_nv> &nva);
  // 汇编请求cookie。与之相反的操作
  // crush_request_cookie（）。
  StringRef assemble_request_cookie();

  void
  set_request_start_time(std::chrono::high_resolution_clock::time_point time);
  const std::chrono::high_resolution_clock::time_point &
  get_request_start_time() const;
  int push_request_headers();
  bool get_chunked_request() const;
  void set_chunked_request(bool f);
  int push_upload_data_chunk(const uint8_t *data, size_t datalen);
  int end_upload_data();
  // 验证收到的请求正文长度和内容长度
  // 比赛。
  bool validate_request_recv_body_length() const;
  void set_request_downstream_host(const StringRef &host);
  bool expect_response_body() const;
  bool expect_response_trailer() const;
  void set_request_state(DownstreamState state);
  DownstreamState get_request_state() const;
  DefaultMemchunks *get_request_buf();
  void set_request_pending(bool f);
  bool get_request_pending() const;
  void set_request_header_sent(bool f);
  bool get_request_header_sent() const;
  // 如果请求已准备好提交给下游，则返回true。
  // 发送挂起请求时，get_request_pending（）应为
  // 也选中了，因为当
  // get_request_pending（）返回false。
  bool request_submission_ready() const;

  DefaultMemchunks *get_blocked_request_buf();
  bool get_blocked_request_data_eof() const;
  void set_blocked_request_data_eof(bool f);

  // 下游响应API
  const Response &response() const { return resp_; }
  Response &response() { return resp_; }

  // 重写位置响应标头字段。
  void rewrite_location_response_header(const StringRef &upstream_scheme);

  bool get_chunked_response() const;
  void set_chunked_response(bool f);

  void set_response_state(DownstreamState state);
  DownstreamState get_response_state() const;
  DefaultMemchunks *get_response_buf();
  bool response_buf_full();
  // 验证收到的响应正文长度和内容长度
  // 比赛。
  bool validate_response_recv_body_length() const;
  uint32_t get_response_rst_stream_error_code() const;
  void set_response_rst_stream_error_code(uint32_t error_code);
  // 检查HTTP/1响应。这将检查传输编码等。
  void inspect_http1_response();
  // 为响应清除一些成员变量。
  void reset_response();
  // 如果响应是非最终的（1xx状态代码），则为True。请注意
  // 如果连接已升级，101状态代码将被视为最终状态。
  bool get_non_final_response() const;
  // 如果客户端使用的协议版本支持非最终版本，则为True
  // 回答只有HTTP/1.1和HTTP/2客户端支持它。
  bool supports_non_final_response() const;
  void set_expect_final_response(bool f);
  bool get_expect_final_response() const;

  // 当下游有传入数据时调用此方法
  // 联系
  int on_read();

  // 重置上游读取计时器。如果它处于活动状态，则超时值为
  // 重置。如果未激活，计时器将启动。
  void reset_upstream_rtimer();
  // 重置上游写入计时器。如果它处于活动状态，则超时值为
  // 重置。如果未激活，计时器将启动。这
  // 如果已启动，该函数还会重置读取计时器。
  void reset_upstream_wtimer();
  // 确保上游写入计时器已启动。如果是的话
  // 开始，什么都不做。否则，将启动写入计时器。
  void ensure_upstream_wtimer();
  // 禁用上游读取计时器。
  void disable_upstream_rtimer();
  // 禁用上游写入计时器。
  void disable_upstream_wtimer();

  // 下游计时器功能。它们以类似的方式工作
  // 类似于上游计时器功能。
  void reset_downstream_rtimer();
  void reset_downstream_wtimer();
  void ensure_downstream_wtimer();
  void disable_downstream_rtimer();
  void disable_downstream_wtimer();

  // 如果可以为此下游写入accesslog，则返回true。
  bool accesslog_ready() const;

  // 增量重试计数
  void add_retry();
  // 如果不应进行重试尝试，则为true。
  bool no_more_retry() const;

  DispatchState get_dispatch_state() const;
  void set_dispatch_state(DispatchState s);

  void attach_blocked_link(BlockedLink *l);
  BlockedLink *detach_blocked_link();

  // 如果下游连接可以分离和重用，则返回true。
  bool can_detach_downstream_connection() const;

  DefaultMemchunks pop_response_buf();

  BlockAllocator &get_block_allocator();

  void add_rcbuf(nghttp2_rcbuf *rcbuf);

  void
  set_downstream_addr_group(const std::shared_ptr<DownstreamAddrGroup> &group);
  void set_addr(const DownstreamAddr *addr);

  const DownstreamAddr *get_addr() const;

  void set_accesslog_written(bool f);

  // 从请求标头字段中查找相关性cookie。的名称
  // cookie以|name|给出。如果找到相关性cookie，则为
  // 分配给成员函数并返回。如果不是
  // 找到或格式不正确，返回0。
  uint32_t find_affinity_cookie(const StringRef &name);
  // 将|h|设置为相关性cookie。
  void renew_affinity_cookie(uint32_t h);
  // 返回要发送的相关性cookie。如果不需要发送，
  // 例如，因为值是从请求头中检索的
  // 字段，返回0。
  uint32_t get_affinity_cookie_to_send() const;

  void set_ws_key(const StringRef &key);

  bool get_expect_100_continue() const;

  enum {
    EVENT_ERROR = 0x1,
    EVENT_TIMEOUT = 0x2,
  };

  Downstream *dlnext, *dlprev;

  // 发送到上游客户端的响应体的长度
  int64_t response_sent_body_length;

private:
  BlockAllocator balloc_;

  std::vector<nghttp2_rcbuf *> rcbufs_;

  Request req_;
  Response resp_;

  std::chrono::high_resolution_clock::time_point request_start_time_;

  // 我们请求下游的主机。这用于重写
  // 位置头字段，用于决定应该重写的位置
  // 或者不。
  StringRef request_downstream_host_;

  // 在将头字段发送到后端之前，数据已到达前端
  // 存储在该缓冲器中。
  DefaultMemchunks blocked_request_buf_;
  DefaultMemchunks request_buf_;
  DefaultMemchunks response_buf_;

  // 发送给对等方的Sec WebSocket Key字段。使用此字段
  // 如果前端通过HTTP/2使用RFC 8441 WebSocket引导。
  StringRef ws_key_;

  ev_timer upstream_rtimer_;
  ev_timer upstream_wtimer_;

  ev_timer downstream_rtimer_;
  ev_timer downstream_wtimer_;

  Upstream *upstream_;
  std::unique_ptr<DownstreamConnection> dconn_;

  // 仅由HTTP/2上游使用
  BlockedLink *blocked_link_;
  // 用于完成此请求的后端地址。这些是为了
  // 记录目的。
  std::shared_ptr<DownstreamAddrGroup> group_;
  const DownstreamAddr *addr_;
  // 我们在后端连接中尝试了多少次
  size_t num_retry_;
  // 前端连接中的流ID
  int32_t stream_id_;
  // 如果推送，则前端连接中的关联流ID
  // 流动
  int32_t assoc_stream_id_;
  // 后端连接中的流ID
  int32_t downstream_stream_id_;
  // 来自下游HTTP2连接的RST_STREAM错误代码
  uint32_t response_rst_stream_error_code_;
  // 相关性cookie值。
  uint32_t affinity_cookie_;
  // 请求状态
  DownstreamState request_state_;
  // 响应状态
  DownstreamState response_state_;
  // 仅由HTTP/2上游使用
  DispatchState dispatch_state_;
  // 如果连接升级（HTTP升级或CONNECT），则为true，
  // 不包括升级到HTTP/2。
  bool upgraded_;
  // 如果后端请求使用分块传输编码，则为true
  bool chunked_request_;
  // 如果对客户端的响应使用分块传输编码，则为true
  bool chunked_response_;
  // 如果我们没有最终的响应代码，则为true
  bool expect_final_response_;
  // 如果下游请求由于后端连接而挂起，则为true
  // 尚未建立或应在使用前进行检查；
  // 当前仅用于HTTP/2连接。
  bool request_pending_;
  // 如果认为发送了下游请求标头，则为true。
  bool request_header_sent_;
  // 如果访问，则为true。日志已写入。
  bool accesslog_written_;
  // 如果为此请求生成了相关性cookie，则为true。
  bool new_affinity_cookie_;
  // 如果在发送头字段之前从客户端接收到eof，则为true
  // 到后端。
  bool blocked_request_data_eof_;
  // 如果请求包含“expect:100 continue”头字段，则为true。
  bool expect_100_continue_;
};

} // 命名空间shrpx

#endif // SHRPX_DOWNSTREAM_H

