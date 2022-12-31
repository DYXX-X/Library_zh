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
#ifndef SHRPX_CONNECTION_HANDLER_H
#define SHRPX_CONNECTION_HANDLER_H

#include "shrpx.h"

#include <sys/types.h>
#ifdef HAVE_SYS_SOCKET_H
#  include <sys/socket.h>
#endif // HAVE_SYS_SOCKET_H

#include <mutex>
#include <memory>
#include <vector>
#include <random>
#ifndef NOTHREADS
#  include <future>
#endif // NOTHREADS

#include <openssl/ssl.h>

#include <ev.h>

#ifdef HAVE_NEVERBLEED
#  include <neverbleed.h>
#endif // HAVE_NEVERBLEED

#include "shrpx_downstream_connection_pool.h"
#include "shrpx_config.h"
#include "shrpx_exec.h"

namespace shrpx {

class Http2Session;
class ConnectBlocker;
class AcceptHandler;
class Worker;
struct WorkerStat;
struct TicketKeys;
class MemcachedDispatcher;
struct UpstreamAddr;

namespace tls {

class CertLookupTree;

} // 命名空间tls

struct OCSPUpdateContext {
  // ocsp响应缓冲区
  std::vector<uint8_t> resp;
  // 进程正在运行fetch ocsp响应脚本
  Process proc;
  // ConnectionHandler:：all_ssl_ctx_的索引，指向next
  // SSL_CTX更新ocsp响应缓存。
  size_t next;
  ev_child chldev;
  ev_io rev;
  // 处理响应时遇到错误No
  int error;
};

// SerialEvent是从Worker线程发送的事件。
enum class SerialEventType {
  NONE,
  REPLACE_DOWNSTREAM,
};

struct SerialEvent {
  // 事件的ctor使用DownstreamConfig
  SerialEvent(SerialEventType type,
              const std::shared_ptr<DownstreamConfig> &downstreamconf)
      : type(type), downstreamconf(downstreamconf) {}

  SerialEventType type;
  std::shared_ptr<DownstreamConfig> downstreamconf;
};

class ConnectionHandler {
public:
  ConnectionHandler(struct ev_loop *loop, std::mt19937 &gen);
  ~ConnectionHandler();
  int handle_connection(int fd, sockaddr *addr, int addrlen,
                        const UpstreamAddr *faddr);
  // 为单线程配置创建Worker对象。
  int create_single_worker();
  // 为多线程配置创建|num|Worker对象。
  // |num|必须严格大于1。
  int create_worker_thread(size_t num);
  void
  set_ticket_keys_to_worker(const std::shared_ptr<TicketKeys> &ticket_keys);
  void worker_reopen_log_files();
  void set_ticket_keys(std::shared_ptr<TicketKeys> ticket_keys);
  const std::shared_ptr<TicketKeys> &get_ticket_keys() const;
  struct ev_loop *get_loop() const;
  Worker *get_single_worker() const;
  void add_acceptor(std::unique_ptr<AcceptHandler> h);
  void delete_acceptor();
  void enable_acceptor();
  void disable_acceptor();
  void sleep_acceptor(ev_tstamp t);
  void accept_pending_connection();
  void graceful_shutdown_worker();
  void set_graceful_shutdown(bool f);
  bool get_graceful_shutdown() const;
  void join_worker();

  // 取消ocsp更新过程
  void cancel_ocsp_update();
  // 启动证书|cert_file|的ocsp更新。
  int start_ocsp_update(const char *cert_file);
  // 从ocsp更新进程读取传入数据
  void read_ocsp_chunk();
  // 处理一个ocsp更新的完成
  void handle_ocsp_complete();
  // 重置ocsp_；
  void reset_ocsp();
  // 继续进行下一个证书的ocsp更新。如果全部
  // 证书的ocsp更新已完成，请安排下一个ocsp
  // 使现代化
  void proceed_next_cert_ocsp();

  void set_tls_ticket_key_memcached_dispatcher(
      std::unique_ptr<MemcachedDispatcher> dispatcher);

  MemcachedDispatcher *get_tls_ticket_key_memcached_dispatcher() const;
  void on_tls_ticket_key_network_error(ev_timer *w);
  void on_tls_ticket_key_not_found(ev_timer *w);
  void
  on_tls_ticket_key_get_success(const std::shared_ptr<TicketKeys> &ticket_keys,
                                ev_timer *w);
  void schedule_next_tls_ticket_key_memcached_get(ev_timer *w);
  SSL_CTX *create_tls_ticket_key_memcached_ssl_ctx();
  // 返回all_SSL_CTX_[idx]处的SSL_CTX。这不执行
  // 数组绑定检查。
  SSL_CTX *get_ssl_ctx(size_t idx) const;

  const std::vector<SSL_CTX *> &get_indexed_ssl_ctx(size_t idx) const;

#ifdef HAVE_NEVERBLEED
  void set_neverbleed(neverbleed_t *nb);
#endif // HAVE_NEVERBLEED

  // 将SerialEvent SerialEventType:：REPLACE_DOWNSTREAM发送到此
  // 对象
  void send_replace_downstream(
      const std::shared_ptr<DownstreamConfig> &downstreamconf);
  // 将|ev|发送到此对象的内部函数。
  void send_serial_event(SerialEvent ev);
  // 处理收到的SerialEvents。
  void handle_serial_event();
  // 发送WorkerEvent以使其在下游替换。
  void
  worker_replace_downstream(std::shared_ptr<DownstreamConfig> downstreamconf);

  void set_enable_acceptor_on_ocsp_completion(bool f);

private:
  // 存储所有SSL_CTX对象。
  std::vector<SSL_CTX *> all_ssl_ctx_;
  // 以存储其索引的方式存储所有SSL_CTX对象
  // 证书树。存储在同一索引中的SSL_CTX共享相同的
  // 主机名，但可以具有不同的签名算法。这个
  // 其中的选择由SNI呈现的主机名执行，
  // 以及客户端提出的签名算法。
  std::vector<std::vector<SSL_CTX *>> indexed_ssl_ctx_;
  OCSPUpdateContext ocsp_;
  std::mt19937 &gen_;
  // 每个工作人员的ev_lop
  std::vector<struct ev_loop *> worker_loops_;
  // 使用多线程模式（-nN，N>=2）时的工作线程实例。
  // 如果至少有一个前端启用API请求，我们将分配1
  // 专用于API请求的附加工作程序。
  std::vector<std::unique_ptr<Worker>> workers_;
  // 用于串行事件大小缓冲区处理的互斥锁
  std::mutex serial_event_mu_;
  // SerialEvent接收缓冲区
  std::vector<SerialEvent> serial_events_;
  // 使用单线程模式（-n1）时使用的工作线程实例。
  // 否则，nullptr和workers_具有Worker实例。
  std::unique_ptr<Worker> single_worker_;
  std::unique_ptr<tls::CertLookupTree> cert_tree_;
  std::unique_ptr<MemcachedDispatcher> tls_ticket_key_memcached_dispatcher_;
  // 当前TLS会话票证密钥。注意TLS连接
  // 不直接引用此字段。他们使用TicketKeys对象
  // Worker对象。
  std::shared_ptr<TicketKeys> ticket_keys_;
  struct ev_loop *loop_;
  std::vector<std::unique_ptr<AcceptHandler>> acceptors_;
#ifdef HAVE_NEVERBLEED
  neverbleed_t *nb_;
#endif // HAVE_NEVERBLEED
  ev_timer disable_acceptor_timer_;
  ev_timer ocsp_timer_;
  ev_async thread_join_asyncev_;
  ev_async serial_event_asyncev_;
#ifndef NOTHREADS
  std::future<void> thread_join_fut_;
#endif // NOTHREADS
  size_t tls_ticket_key_memcached_get_retry_count_;
  size_t tls_ticket_key_memcached_fail_count_;
  unsigned int worker_round_robin_cnt_;
  bool graceful_shutdown_;
  // 如果在初始ocsp更新后应启用接收器，则为true
  // 已完成。
  bool enable_acceptor_on_ocsp_completion_;
};

} // 命名空间shrpx

#endif // SHRPX_CONNECTION_HANDLER_H

