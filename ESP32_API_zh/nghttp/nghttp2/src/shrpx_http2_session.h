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
#ifndef SHRPX_HTTP2_SESSION_H
#define SHRPX_HTTP2_SESSION_H

#include "shrpx.h"

#include <unordered_set>
#include <memory>

#include <openssl/ssl.h>

#include <ev.h>

#include <nghttp2/nghttp2.h>

#include "llhttp.h"

#include "shrpx_connection.h"
#include "buffer.h"
#include "template.h"

using namespace nghttp2;

namespace shrpx {

class Http2DownstreamConnection;
class Worker;
class Downstream;
struct DownstreamAddrGroup;
struct DownstreamAddr;
struct DNSQuery;

struct StreamData {
  StreamData *dlnext, *dlprev;
  Http2DownstreamConnection *dconn;
};

enum class FreelistZone {
  // Http2Session对象未链接到任何自由列表中。
  NONE,
  // Http2Session对象在地址范围中链接
  // http2_extra_freelist。
  EXTRA,
  // Http2Session对象即将被删除，但它没有
  // 属于任何链接列表。
  GONE
};

enum class Http2SessionState {
  // 断开的
  DISCONNECTED,
  // 连接代理并发出CONNECT请求
  PROXY_CONNECTING,
  // 通过代理建立隧道
  PROXY_CONNECTED,
  // 建立隧道失败
  PROXY_FAILED,
  // 连接到下游和/或执行SSL/TLS握手
  CONNECTING,
  // 连接至下游
  CONNECTED,
  // 连接开始失败
  CONNECT_FAILING,
  // 正在解析主机名
  RESOLVING_NAME,
};

enum class ConnectionCheck {
  // 不需要连接检查
  NONE,
  // 需要进行连接检查
  REQUIRED,
  // 已开始连接检查
  STARTED,
};

class Http2Session {
public:
  Http2Session(struct ev_loop *loop, SSL_CTX *ssl_ctx, Worker *worker,
               const std::shared_ptr<DownstreamAddrGroup> &group,
               DownstreamAddr *addr);
  ~Http2Session();

  // 如果hard为true，则放弃所有未决请求
  // 将删除关联的ClientHandlers。
  int disconnect(bool hard = false);
  int initiate_connection();
  int resolve_name();

  void add_downstream_connection(Http2DownstreamConnection *dconn);
  void remove_downstream_connection(Http2DownstreamConnection *dconn);

  void remove_stream_data(StreamData *sd);

  int submit_request(Http2DownstreamConnection *dconn, const nghttp2_nv *nva,
                     size_t nvlen, const nghttp2_data_provider *data_prd);

  int submit_rst_stream(int32_t stream_id, uint32_t error_code);

  int terminate_session(uint32_t error_code);

  nghttp2_session *get_session() const;

  int resume_data(Http2DownstreamConnection *dconn);

  int connection_made();

  int do_read();
  int do_write();

  int on_read(const uint8_t *data, size_t datalen);
  int on_write();

  int connected();
  int read_clear();
  int write_clear();
  int tls_handshake();
  int read_tls();
  int write_tls();
  // 这是一个特殊的写函数，它只是停止写事件
  // 观察者。
  int write_void();

  int downstream_read_proxy(const uint8_t *data, size_t datalen);
  int downstream_connect_proxy();

  int downstream_read(const uint8_t *data, size_t datalen);
  int downstream_write();

  int noop();
  int read_noop(const uint8_t *data, size_t datalen);
  int write_noop();

  void signal_write();

  struct ev_loop *get_loop() const;

  ev_io *get_wev();

  Http2SessionState get_state() const;
  void set_state(Http2SessionState state);

  void start_settings_timer();
  void stop_settings_timer();

  SSL *get_ssl() const;

  int consume(int32_t stream_id, size_t len);

  // 如果可以在下游连接上发出请求，则返回true。
  bool can_push_request(const Downstream *downstream) const;
  // 启动连接检查下游连接是否具有
  // 并且需要连接检查。
  void start_checking_connection();
  // 将连接检查计时器重置为超时|t|。超时后，我们
  // 需要连接检查。如果已进行连接检查
  // 启用，此超时用于PING ACK超时。
  void reset_connection_check_timer(ev_tstamp t);
  void reset_connection_check_timer_if_not_checking();
  // 表示连接处于活动状态。内部
  // 调用reset_connection_check_timer（）。
  void connection_alive();
  // 更改连接检查状态。
  void set_connection_check_state(ConnectionCheck state);
  ConnectionCheck get_connection_check_state() const;

  bool should_hard_fail() const;

  void submit_pending_requests();

  DownstreamAddr *get_addr() const;

  const std::shared_ptr<DownstreamAddrGroup> &get_downstream_addr_group() const;

  int handle_downstream_push_promise(Downstream *downstream,
                                     int32_t promised_stream_id);
  int handle_downstream_push_promise_complete(Downstream *downstream,
                                              Downstream *promised_downstream);

  // 返回下游连接数，包括推送
  // 流。
  size_t get_num_dconns() const;

  // 添加到组范围http2_avail_freelist。
  void add_to_avail_freelist();
  // 添加到地址范围http2_extra_freelist。
  void add_to_extra_freelist();

  // 从任何自由列表中删除此对象。如果此对象不是
  // 从任何自由列表链接，此函数不起作用。
  void remove_from_freelist();

  // 从任何自由列表中删除此对象，并将此对象标记为
  // 不可调度。
  void exclude_from_scheduling();

  // 如果达到最大并发，则返回true。在其他方面
  // 单词，当前参与的流的数量
  // 会话等于或大于最大并发流限制
  // 由服务器播发。如果|extra|为非零，则将其添加到
  // 比较时当前并发流的数量
  // 服务器发起的并发限制。
  bool max_concurrency_reached(size_t extra = 0) const;

  DefaultMemchunks *get_request_buf();

  void on_timeout();

  // 这是使用ev_prepare监视程序定期调用的，如果
  // group_已失效（后端已被替换），请将GOAWAY发送到
  // 关闭连接。
  void check_retire();

  // 返回用于连接到后端的地址。可能是nullptr。
  const Address *get_raddr() const;

  // 当未设置ACK标志的SETTINGS帧为
  // 收到。
  void on_settings_received(const nghttp2_frame *frame);

  bool get_allow_connect_proto() const;

  using ReadBuf = Buffer<8_k>;

  Http2Session *dlnext, *dlprev;

private:
  Connection conn_;
  DefaultMemchunks wb_;
  ev_timer settings_timer_;
  // 此计时器有两个用途：当它第一次超时时，设置
  // connection_check_state_=连接检查：：必需。之后
  // 连接检查已启动，此计时器将再次启动
  // 陷阱PING ACK超时。
  ev_timer connchk_timer_;
  // 计时器启动连接。通常，这会立即启动。
  ev_timer initiate_connection_timer_;
  ev_prepare prep_;
  DList<Http2DownstreamConnection> dconns_;
  DList<StreamData> streams_;
  std::function<int(Http2Session &)> read_, write_;
  std::function<int(Http2Session &, const uint8_t *, size_t)> on_read_;
  std::function<int(Http2Session &)> on_write_;
  // 用于解析来自HTTP代理的响应
  std::unique_ptr<llhttp_t> proxy_htp_;
  Worker *worker_;
  // 如果未配置TLS，则为NULL
  SSL_CTX *ssl_ctx_;
  std::shared_ptr<DownstreamAddrGroup> group_;
  // 远程终结点的地址
  DownstreamAddr *addr_;
  nghttp2_session *session_;
  // 用于联系后端的实际远程地址。这最初是
  // 并且可以指向&addr->addr，
  // 已解决地址。get（）或HTTP代理的地址结构。
  const Address *raddr_;
  // 如果使用dns参数，则解析IP地址
  std::unique_ptr<Address> resolved_addr_;
  std::unique_ptr<DNSQuery> dns_query_;
  Http2SessionState state_;
  ConnectionCheck connection_check_state_;
  FreelistZone freelist_zone_;
  // 如果从对等端接收到没有ACK的设置，则为true。
  bool settings_recved_;
  // 如果对等方启用RFC 8441 CONNECT协议，则为true。
  bool allow_connect_proto_;
};

nghttp2_session_callbacks *create_http2_downstream_callbacks();

} // 命名空间shrpx

#endif // SHRPX_HTTP2_SESSION_H

