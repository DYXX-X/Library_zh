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
#ifndef SHRPX_WORKER_H
#define SHRPX_WORKER_H

#include "shrpx.h"

#include <mutex>
#include <vector>
#include <random>
#include <unordered_map>
#include <deque>
#include <thread>
#include <queue>
#ifndef NOTHREADS
#  include <future>
#endif // NOTHREADS

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <ev.h>

#include "shrpx_config.h"
#include "shrpx_downstream_connection_pool.h"
#include "memchunk.h"
#include "shrpx_tls.h"
#include "shrpx_live_check.h"
#include "shrpx_connect_blocker.h"
#include "shrpx_dns_tracker.h"
#include "allocator.h"

using namespace nghttp2;

namespace shrpx {

class Http2Session;
class ConnectBlocker;
class MemcachedDispatcher;
struct UpstreamAddr;
class ConnectionHandler;

#ifdef HAVE_MRUBY
namespace mruby {

class MRubyContext;

} // 命名空间mruby
#endif // HAVE_MRUBY

namespace tls {
class CertLookupTree;
} // 命名空间tls

struct WeightGroup;

struct DownstreamAddr {
  Address addr;
  // 后端地址。如果|host_unix|为true，则这是unix域
  // 套接字路径。
  StringRef host;
  StringRef hostport;
  // 如果|host_unix|为true，则为后端端口.0。
  uint16_t port;
  // 如果|host|包含UNIX域套接字路径，则为true。
  bool host_unix;

  // 如果启用TLS，则发送远程服务器的sni字段。
  StringRef sni;

  std::unique_ptr<ConnectBlocker> connect_blocker;
  std::unique_ptr<LiveCheck> live_check;
  // 如果会话关联，则此特定地址的连接池
  // 已启用
  std::unique_ptr<DownstreamConnectionPool> dconn_pool;
  size_t fall;
  size_t rise;
  // 客户端TLS会话缓存
  tls::TLSSessionCache tls_session_cache;
  // 未充分利用的Http2Session列表（即
  // 未达到服务器通告的最大并发性）。我们将
  // 在一个Http2Session中合并尽可能多的流
  // 利用TCP连接。
  DList<Http2Session> http2_extra_freelist;
  WeightGroup *wg;
  // 在HTTP/2连接中为此创建的流总数
  // 住址
  size_t num_dconn;
  // 该地址的序列号以随机化顺序访问
  // 线程。
  size_t seq;
  // 此后端中使用的应用程序协议
  Proto proto;
  // 循环用于确定此地址的优先级。取值较低
  // 更高优先级。
  uint32_t cycle;
  // 其被应用于下一循环计算。
  uint32_t pending_penalty;
  // 权重组中此地址的权重。其范围为[1，
  // 256]（含）。
  uint32_t weight;
  // 此地址所属组的名称。
  StringRef group;
  // 此地址所属权重组的权重。其
  // 范围为[1256]（含）。
  uint32_t group_weight;
  // 如果此后端使用TLS，则为true
  bool tls;
  // 如果启用了动态DNS，则为true
  bool dns;
  // true if：scheme伪标头字段应升级为安全
  // 将请求转发到后端时的变体（例如“https”）
  // 通过TLS连接连接。
  bool upgrade_scheme;
  // 如果此地址已排队，则为true。
  bool queued;
};

constexpr uint32_t MAX_DOWNSTREAM_ADDR_WEIGHT = 256;

struct DownstreamAddrEntry {
  DownstreamAddr *addr;
  size_t seq;
  uint32_t cycle;
};

struct DownstreamAddrEntryGreater {
  bool operator()(const DownstreamAddrEntry &lhs,
                  const DownstreamAddrEntry &rhs) const {
    auto d = lhs.cycle - rhs.cycle;
    if (d == 0) {
      return rhs.seq < lhs.seq;
    }
    return d <= MAX_DOWNSTREAM_ADDR_WEIGHT;
  }
};

struct WeightGroup {
  std::priority_queue<DownstreamAddrEntry, std::vector<DownstreamAddrEntry>,
                      DownstreamAddrEntryGreater>
      pq;
  size_t seq;
  uint32_t weight;
  uint32_t cycle;
  uint32_t pending_penalty;
  // 如果此对象已排队，则为true。
  bool queued;
};

struct WeightGroupEntry {
  WeightGroup *wg;
  size_t seq;
  uint32_t cycle;
};

struct WeightGroupEntryGreater {
  bool operator()(const WeightGroupEntry &lhs,
                  const WeightGroupEntry &rhs) const {
    auto d = lhs.cycle - rhs.cycle;
    if (d == 0) {
      return rhs.seq < lhs.seq;
    }
    return d <= MAX_DOWNSTREAM_ADDR_WEIGHT;
  }
};

struct SharedDownstreamAddr {
  SharedDownstreamAddr()
      : balloc(1024, 1024),
        affinity{SessionAffinity::NONE},
        redirect_if_not_tls{false},
        timeout{} {}

  SharedDownstreamAddr(const SharedDownstreamAddr &) = delete;
  SharedDownstreamAddr(SharedDownstreamAddr &&) = delete;
  SharedDownstreamAddr &operator=(const SharedDownstreamAddr &) = delete;
  SharedDownstreamAddr &operator=(SharedDownstreamAddr &&) = delete;

  BlockAllocator balloc;
  std::vector<DownstreamAddr> addrs;
  std::vector<WeightGroup> wgs;
  std::priority_queue<WeightGroupEntry, std::vector<WeightGroupEntry>,
                      WeightGroupEntryGreater>
      pq;
  // 一堆会话关联哈希。仅在关联时使用==
  // SessionAffinity:：IP。
  std::vector<AffinityHash> affinity_hash;
#ifdef HAVE_MRUBY
  std::shared_ptr<mruby::MRubyContext> mruby_ctx;
#endif // HAVE_MRUBY
  // 会话关联的配置
  AffinityConfig affinity;
  // 会话相关性
  // 如果该组要求客户端连接必须是TLS，
  // 并且请求必须重定向到https URI。
  bool redirect_if_not_tls;
  // 后端连接超时。
  struct {
    ev_tstamp read;
    ev_tstamp write;
  } timeout;
};

struct DownstreamAddrGroup {
  DownstreamAddrGroup();
  ~DownstreamAddrGroup();

  DownstreamAddrGroup(const DownstreamAddrGroup &) = delete;
  DownstreamAddrGroup(DownstreamAddrGroup &&) = delete;
  DownstreamAddrGroup &operator=(const DownstreamAddrGroup &) = delete;
  DownstreamAddrGroup &operator=(DownstreamAddrGroup &&) = delete;

  ImmutableString pattern;
  std::shared_ptr<SharedDownstreamAddr> shared_addr;
  // 如果此组不再用于新请求，则为true。如果这是
  // true，使用sharedAddr中的一个地址建立的连接
  // 不得合并。
  bool retired;
};

struct WorkerStat {
  size_t num_connections;
};

enum class WorkerEventType {
  NEW_CONNECTION = 0x01,
  REOPEN_LOG = 0x02,
  GRACEFUL_SHUTDOWN = 0x03,
  REPLACE_DOWNSTREAM = 0x04,
};

struct WorkerEvent {
  WorkerEventType type;
  struct {
    sockaddr_union client_addr;
    size_t client_addrlen;
    int client_fd;
    const UpstreamAddr *faddr;
  };
  std::shared_ptr<TicketKeys> ticket_keys;
  std::shared_ptr<DownstreamConfig> downstreamconf;
};

class Worker {
public:
  Worker(struct ev_loop *loop, SSL_CTX *sv_ssl_ctx, SSL_CTX *cl_ssl_ctx,
         SSL_CTX *tls_session_cache_memcached_ssl_ctx,
         tls::CertLookupTree *cert_tree,
         const std::shared_ptr<TicketKeys> &ticket_keys,
         ConnectionHandler *conn_handler,
         std::shared_ptr<DownstreamConfig> downstreamconf);
  ~Worker();
  void run_async();
  void wait();
  void process_events();
  void send(const WorkerEvent &event);

  tls::CertLookupTree *get_cert_lookup_tree() const;

  // 这两个函数生成一个锁m_以获取/设置票证密钥
  // 原子地。
  std::shared_ptr<TicketKeys> get_ticket_keys();
  void set_ticket_keys(std::shared_ptr<TicketKeys> ticket_keys);

  WorkerStat *get_worker_stat();
  struct ev_loop *get_loop() const;
  SSL_CTX *get_sv_ssl_ctx() const;
  SSL_CTX *get_cl_ssl_ctx() const;

  void set_graceful_shutdown(bool f);
  bool get_graceful_shutdown() const;

  MemchunkPool *get_mcpool();
  void schedule_clear_mcpool();

  MemcachedDispatcher *get_session_cache_memcached_dispatcher();

  std::mt19937 &get_randgen();

#ifdef HAVE_MRUBY
  int create_mruby_context();

  mruby::MRubyContext *get_mruby_context() const;
#endif // HAVE_MRUBY

  std::vector<std::shared_ptr<DownstreamAddrGroup>> &
  get_downstream_addr_groups();

  ConnectBlocker *get_connect_blocker() const;

  const DownstreamConfig *get_downstream_config() const;

  void
  replace_downstream_config(std::shared_ptr<DownstreamConfig> downstreamconf);

  ConnectionHandler *get_connection_handler() const;

  DNSTracker *get_dns_tracker();

private:
#ifndef NOTHREADS
  std::future<void> fut_;
#endif // NOTHREADS
  std::mutex m_;
  std::deque<WorkerEvent> q_;
  std::mt19937 randgen_;
  ev_async w_;
  ev_timer mcpool_clear_timer_;
  ev_timer proc_wev_timer_;
  MemchunkPool mcpool_;
  WorkerStat worker_stat_;
  DNSTracker dns_tracker_;

  std::shared_ptr<DownstreamConfig> downstreamconf_;
  std::unique_ptr<MemcachedDispatcher> session_cache_memcached_dispatcher_;
#ifdef HAVE_MRUBY
  std::unique_ptr<mruby::MRubyContext> mruby_ctx_;
#endif // HAVE_MRUBY
  struct ev_loop *loop_;

  // 如果
  // get_config（）->tls_ctx_per_worker==真。
  SSL_CTX *sv_ssl_ctx_;
  SSL_CTX *cl_ssl_ctx_;
  tls::CertLookupTree *cert_tree_;
  ConnectionHandler *conn_handler_;

#ifndef HAVE_ATOMIC_STD_SHARED_PTR
  std::mutex ticket_keys_m_;
#endif // !HAVE_ATOMIC_STD_SHARED_PTR
  std::shared_ptr<TicketKeys> ticket_keys_;
  std::vector<std::shared_ptr<DownstreamAddrGroup>> downstream_addr_groups_;
  // 用于下游连接的工作级阻止程序。例如
  // 当文件描述符用尽时使用此选项。
  std::unique_ptr<ConnectBlocker> connect_blocker_;

  bool graceful_shutdown_;
};

// 根据请求的|hostport|和|path|选择组|主机端口|
// 值取自：authority或host标头字段，可以
// 包含端口。|路径|可能包含查询部分。我们需要
// 捕获所有模式，因此此函数始终选择一个
// 组捕获所有组索引在|catch_all|中给出。全部的
// 模式在|组|中给出。
size_t match_downstream_addr_group(
    const RouterConfig &routerconfig, const StringRef &hostport,
    const StringRef &path,
    const std::vector<std::shared_ptr<DownstreamAddrGroup>> &groups,
    size_t catch_all, BlockAllocator &balloc);

// 如果连接到后端失败，则调用此函数|raddr|是
// 用于连接到后端的实际地址
// 空指针。此功能可安排实时检查。
void downstream_failure(DownstreamAddr *addr, const Address *raddr);

} // 命名空间shrpx

#endif // SHRPX_WORKER_H

