/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2015 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SHRPX_CONNECTION_H
#define SHRPX_CONNECTION_H

#include "shrpx_config.h"

#include <sys/uio.h>

#include <ev.h>

#include <openssl/ssl.h>

#include "shrpx_rate_limit.h"
#include "shrpx_error.h"
#include "memchunk.h"

namespace shrpx {

struct MemcachedRequest;

namespace tls {
struct TLSSessionCache;
} // 命名空间tls

enum class TLSHandshakeState {
  NORMAL,
  WAIT_FOR_SESSION_CACHE,
  GOT_SESSION_CACHE,
  CANCEL_SESSION_CACHE,
  WRITE_STARTED,
};

struct TLSConnection {
  DefaultMemchunks wbuf;
  DefaultPeekMemchunks rbuf;
  // 存储TLSv1.3早期数据。
  DefaultMemchunks earlybuf;
  SSL *ssl;
  SSL_SESSION *cached_session;
  MemcachedRequest *cached_session_lookup_req;
  tls::TLSSessionCache *client_session_cache;
  ev_tstamp last_write_idle;
  size_t warmup_writelen;
  // 上次传递给SSL_ write和SSL_ read的长度。这是
  // 因为这些函数需要完全相同的参数
  // 在非阻塞I/O上。
  size_t last_writelen, last_readlen;
  TLSHandshakeState handshake_state;
  bool initial_handshake_done;
  bool reneg_started;
  // 如果ssl准备作为服务器进行握手，则为true。
  bool server_handshake;
  // 如果ssl初始化为服务器，并且请求客户端，则为true
  // signed_certificate_timestamp扩展名。
  bool sct_requested;
  // 如果TLSv1.3早期数据已被完全接收，则为true。自从
  // SSL_read_early_data的行为类似于SSL_do_handshake，该字段可以是
  // 即使协商的TLS版本是TLSv1.2或更早版本，也是如此。
  // 如果这是的客户端连接，则该值也为true
  // 方便
  bool early_data_finish;
};

struct TCPHint {
  size_t write_buffer_size;
  uint32_t rwin;
};

template <typename T> using EVCb = void (*)(struct ev_loop *, T *, int);

using IOCb = EVCb<ev_io>;
using TimerCb = EVCb<ev_timer>;

struct Connection {
  Connection(struct ev_loop *loop, int fd, SSL *ssl, MemchunkPool *mcpool,
             ev_tstamp write_timeout, ev_tstamp read_timeout,
             const RateLimitConfig &write_limit,
             const RateLimitConfig &read_limit, IOCb writecb, IOCb readcb,
             TimerCb timeoutcb, void *data, size_t tls_dyn_rec_warmup_threshold,
             ev_tstamp tls_dyn_rec_idle_timeout, Proto proto);
  ~Connection();

  void disconnect();

  void prepare_client_handshake();
  void prepare_server_handshake();

  int tls_handshake();
  int write_tls_pending_handshake();

  int check_http2_requirement();

  // 所有write_*和writev_clear函数都返回字节数
  // 书面的如果无法写入任何内容（例如，没有
  // RateLimit或基础连接块中的容差），返回
  // 0。如果出现错误，则返回SHRPX_ERR_NETWORK。
  //
  // 所有read_*函数都返回读取的字节数。如果没有
  // 无法读取（例如，Ratelimit或
  // 基础连接块），返回0。SHRPX_ERR_EOF为
  // 在EOF的情况下返回，未读取任何数据。否则
  // 如果出现错误，则返回SHRPX_ERR_NETWORK。
  ssize_t write_tls(const void *data, size_t len);
  ssize_t read_tls(void *data, size_t len);

  size_t get_tls_write_limit();
  // 更新预热期间写入的字节数。
  void update_tls_warmup_writelen(size_t n);
  // 说明现在没有立即写入。这将触发计时器
  // 确定回退到短记录大小模式。
  void start_tls_write_idle();

  ssize_t write_clear(const void *data, size_t len);
  ssize_t writev_clear(struct iovec *iov, int iovcnt);
  ssize_t read_clear(void *data, size_t len);

  void handle_tls_pending_read();

  void set_ssl(SSL *ssl);

  int get_tcp_hint(TCPHint *hint) const;

  // 这些功能为读取计时器提供
  // 重新启动。我们做了一个技巧，使效率比
  // 调用ev_timer_again（）。

  // 使用超时值|t|重新启动读取计时器。
  void again_rt(ev_tstamp t);
  // 重新启动读取计时器，无链接超时。
  void again_rt();
  // 如果读取计时器过期，则返回true。
  bool expired_rt();

  TLSConnection tls;
  ev_io wev;
  ev_io rev;
  ev_timer wt;
  ev_timer rt;
  RateLimit wlimit;
  RateLimit rlimit;
  struct ev_loop *loop;
  void *data;
  int fd;
  size_t tls_dyn_rec_warmup_threshold;
  ev_tstamp tls_dyn_rec_idle_timeout;
  // 连接上使用的应用程序协议。此字段不是
  // 当前用于此对象。程序的其余部分可能
  // 在有用时使用此值。
  Proto proto;
  // 观察到上次读取的时间点。注意：由于我们使用
  // |rt |作为空闲计时器，活动不限于读取。
  ev_tstamp last_read;
  // 读取计时器|rt|超时。
  ev_tstamp read_timeout;
};

// 创建所有SSL对象共享的BIO_method。
BIO_METHOD *create_bio_method();

} // 命名空间shrpx

#endif // SHRPX_CONNECTION_H

