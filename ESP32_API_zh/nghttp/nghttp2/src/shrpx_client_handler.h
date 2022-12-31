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
#ifndef SHRPX_CLIENT_HANDLER_H
#define SHRPX_CLIENT_HANDLER_H

#include "shrpx.h"

#include <memory>

#include <ev.h>

#include <openssl/ssl.h>

#include "shrpx_rate_limit.h"
#include "shrpx_connection.h"
#include "buffer.h"
#include "memchunk.h"
#include "allocator.h"

using namespace nghttp2;

namespace shrpx {

class Upstream;
class DownstreamConnection;
class HttpsUpstream;
class ConnectBlocker;
class DownstreamConnectionPool;
class Worker;
class Downstream;
struct WorkerStat;
struct DownstreamAddrGroup;
struct DownstreamAddr;

class ClientHandler {
public:
  ClientHandler(Worker *worker, int fd, SSL *ssl, const StringRef &ipaddr,
                const StringRef &port, int family, const UpstreamAddr *faddr);
  ~ClientHandler();

  int noop();
  // 执行明文I/O
  int read_clear();
  int write_clear();
  // 执行TLS握手
  int tls_handshake();
  // 执行TLS I/O
  int read_tls();
  int write_tls();

  int upstream_noop();
  int upstream_read();
  int upstream_http2_connhd_read();
  int upstream_http1_connhd_read();
  int upstream_write();

  int proxy_protocol_read();
  int proxy_protocol_v2_read();
  int on_proxy_protocol_finish();

  // 执行I/O操作。内部调用on\read（）/o_write（）。
  int do_read();
  int do_write();

  // 处理缓冲区。不会执行底层I/O操作。
  int on_read();
  int on_write();

  struct ev_loop *get_loop() const;
  void reset_upstream_read_timeout(ev_tstamp t);
  void reset_upstream_write_timeout(ev_tstamp t);

  int validate_next_proto();
  const StringRef &get_ipaddr() const;
  bool get_should_close_after_write() const;
  void set_should_close_after_write(bool f);
  Upstream *get_upstream();

  void pool_downstream_connection(std::unique_ptr<DownstreamConnection> dconn);
  void remove_downstream_connection(DownstreamConnection *dconn);
  DownstreamAddr *get_downstream_addr(int &err, DownstreamAddrGroup *group,
                                      Downstream *downstream);
  // 基于请求路径返回DownstreamConnection对象。这
  // 函数返回非空的DownstreamConnection，并将0分配给
  // |err |如果成功，或返回nullptr，并赋值为负数
  // 错误代码为|err|。
  std::unique_ptr<DownstreamConnection>
  get_downstream_connection(int &err, Downstream *downstream);
  MemchunkPool *get_mcpool();
  SSL *get_ssl() const;
  // 在收到HTTP/2连接头时调用此函数
  // 连接的开始。
  void direct_http2_upgrade();
  // 从管理的连接执行HTTP/2升级
  // |http |。如果此功能失败，则连接必须
  // 结束。如果成功，此函数将返回0，或者返回-1。
  int perform_http2_upgrade(HttpsUpstream *http);
  bool get_http2_upgrade_allowed() const;
  // 返回上游方案，“http”或“https”
  StringRef get_upstream_scheme() const;
  void start_immediate_shutdown();

  // 使用|下游|写入上游访问日志。下游||
  // 不能为nullptr。
  void write_accesslog(Downstream *downstream);

  Worker *get_worker() const;

  // 初始化forwarded_for_。
  void init_forwarded_for(int family, const StringRef &ipaddr);

  using ReadBuf = DefaultMemchunkBuffer;

  ReadBuf *get_rb();

  RateLimit *get_rlimit();
  RateLimit *get_wlimit();

  void signal_write();
  ev_io *get_wev();

  void setup_upstream_io_callback();

  // 返回适合在Forwarded的“by”参数中使用的字符串
  // 标题字段。
  StringRef get_forwarded_by() const;
  // 返回适合在Forwarded的“for”参数中使用的字符串
  // 标题字段。
  StringRef get_forwarded_for() const;

  Http2Session *
  get_http2_session(const std::shared_ptr<DownstreamAddrGroup> &group,
                    DownstreamAddr *addr);

  // 返回|下游|的相关性cookie值|炊具名称|
  // 用于检查请求标头字段中的cookie标头字段。
  uint32_t get_affinity_cookie(Downstream *downstream,
                               const StringRef &cookie_name);

  const UpstreamAddr *get_upstream_addr() const;

  void repeat_read_timer();
  void stop_read_timer();

  Connection *get_connection();

  // 存储|sni|这是TLS sni扩展值客户端发送到此
  // 联系
  void set_tls_sni(const StringRef &sni);
  // 返回此连接中发送的TLS SNI扩展值客户端。
  StringRef get_tls_sni() const;

  // 返回在此连接中协商的ALPN。
  StringRef get_alpn() const;

  BlockAllocator &get_block_allocator();

private:
  // 为连接范围对象分配内存的分配器。制作
  // 确保分配必须是有界的，而不是成比例的
  // 请求的数量。
  BlockAllocator balloc_;
  DefaultMemchunkBuffer rb_;
  Connection conn_;
  ev_timer reneg_shutdown_timer_;
  std::unique_ptr<Upstream> upstream_;
  // 客户端的IP地址。如果使用UNIX域套接字，则为
  // “本地主机”。
  StringRef ipaddr_;
  StringRef port_;
  // 为此连接协商的ALPN标识符。
  StringRef alpn_;
  // Forwarded标头的“for”参数中使用的客户端地址
  // 领域
  StringRef forwarded_for_;
  // 客户端发送的低级TLS SNI。
  StringRef sni_;
  std::function<int(ClientHandler &)> read_, write_;
  std::function<int(ClientHandler &)> on_read_, on_write_;
  // 前端监听插座地址
  const UpstreamAddr *faddr_;
  Worker *worker_;
  // 要读取的HTTP/2客户端连接头的字节数
  size_t left_connhd_len_;
  // 使用客户端IP的会话关联哈希
  uint32_t affinity_hash_;
  bool should_close_after_write_;
  // 如果计算了affinity_hash_，则为true
  bool affinity_hash_computed_;
};

} // 命名空间shrpx

#endif // SHRPX_CLIENT_HANDLER_H

