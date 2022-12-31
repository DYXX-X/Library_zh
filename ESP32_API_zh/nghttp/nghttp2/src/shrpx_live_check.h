/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2016 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SHRPX_LIVE_CHECK_H
#define SHRPX_LIVE_CHECK_H

#include "shrpx.h"

#include <functional>
#include <random>

#include <openssl/ssl.h>

#include <ev.h>

#include <nghttp2/nghttp2.h>

#include "shrpx_connection.h"

namespace shrpx {

class Worker;
struct DownstreamAddr;
struct DNSQuery;

class LiveCheck {
public:
  LiveCheck(struct ev_loop *loop, SSL_CTX *ssl_ctx, Worker *worker,
            DownstreamAddr *addr, std::mt19937 &gen);
  ~LiveCheck();

  void disconnect();

  void on_success();
  void on_failure();

  int initiate_connection();

  // 计划下次连接尝试
  void schedule();

  // 低级I/O操作回调；它们是从do_read（）调用的
  // 或do_write（）。
  int noop();
  int connected();
  int tls_handshake();
  int read_tls();
  int write_tls();
  int read_clear();
  int write_clear();

  int do_read();
  int do_write();

  // 这些函数用于向
  // nghttp2_session对象。
  int on_read(const uint8_t *data, size_t len);
  int on_write();

  // 在建立HTTP/2连接时调用此函数。我们
  // 现在不要为HTTP/1调用此函数。
  int connection_made();

  void start_settings_timer();
  void stop_settings_timer();

  // 当从服务器接收到SETTINGS ACK时，调用此函数。
  void settings_ack_received();

  void signal_write();

private:
  Connection conn_;
  DefaultMemchunks wb_;
  std::mt19937 &gen_;
  ev_timer backoff_timer_;
  ev_timer settings_timer_;
  std::function<int(LiveCheck &)> read_, write_;
  Worker *worker_;
  // 如果未配置TLS，则为nullptr
  SSL_CTX *ssl_ctx_;
  // 远程终结点的地址
  DownstreamAddr *addr_;
  nghttp2_session *session_;
  // 用于联系后端的实际远程地址。这最初是
  // nullptr，并且可以指向&addr->addr，或
  // resolved_addr.get（）。
  const Address *raddr_;
  // 如果使用dns参数，则解析IP地址
  std::unique_ptr<Address> resolved_addr_;
  std::unique_ptr<DNSQuery> dns_query_;
  // 一行中成功连接尝试的次数。
  size_t success_count_;
  // 一行中连接尝试失败的次数。
  size_t fail_count_;
  // 当从服务器接收到SETTINGS ACK时为true。
  bool settings_ack_received_;
  // 当GOAWAY已排队时为true。
  bool session_closing_;
};

} // 命名空间shrpx

#endif // SHRPX_LIVE_CHECK_H

