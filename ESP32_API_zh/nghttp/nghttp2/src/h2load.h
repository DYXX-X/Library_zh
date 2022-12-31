/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2014 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef H2LOAD_H
#define H2LOAD_H

#include "nghttp2_config.h"

#include <sys/types.h>
#ifdef HAVE_SYS_SOCKET_H
#  include <sys/socket.h>
#endif // HAVE_SYS_SOCKET_H
#ifdef HAVE_NETDB_H
#  include <netdb.h>
#endif // HAVE_NETDB_H
#include <sys/un.h>

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <array>

#include <nghttp2/nghttp2.h>

#include <ev.h>

#include <openssl/ssl.h>

#include "http2.h"
#include "memchunk.h"
#include "template.h"

using namespace nghttp2;

namespace h2load {

constexpr auto BACKOFF_WRITE_BUFFER_THRES = 16_k;

class Session;
struct Worker;

struct Config {
  std::vector<std::vector<nghttp2_nv>> nva;
  std::vector<std::string> h1reqs;
  std::vector<ev_tstamp> timings;
  nghttp2::Headers custom_headers;
  std::string scheme;
  std::string host;
  std::string connect_to_host;
  std::string ifile;
  std::string ciphers;
  // 上传数据长度
  int64_t data_length;
  addrinfo *addrs;
  size_t nreqs;
  size_t nclients;
  size_t nthreads;
  // 每个会话的最大并发流数。
  ssize_t max_concurrent_streams;
  size_t window_bits;
  size_t connection_window_bits;
  // 连接的速率
  size_t rate;
  ev_tstamp rate_period;
  // 计时测试中主要测量的时间量
  ev_tstamp duration;
  // 在基于计时的测试中开始测量之前等待的时间量
  ev_tstamp warm_up_time;
  // 在给定连接上等待活动的时间量
  ev_tstamp conn_active_timeout;
  // 在连接上发出最后一个请求后等待的时间
  ev_tstamp conn_inactivity_timeout;
  enum { PROTO_HTTP2, PROTO_HTTP1_1 } no_tls_proto;
  uint32_t header_table_size;
  uint32_t encoder_header_table_size;
  // 上载数据的文件描述符
  int data_fd;
  // 每个请求统计信息要写入的文件描述符。
  int log_fd;
  uint16_t port;
  uint16_t default_port;
  uint16_t connect_to_port;
  bool verbose;
  bool timing_script;
  std::string base_uri;
  // 如果使用UNIX域套接字，则为true。在本例中，base_uri为
  // 不以通常方式使用。
  bool base_uri_unix;
  // 使用UNIX域套接字时使用（base_uri_UNIX为true）。
  sockaddr_un unix_addr;
  // 支持的NPN/ALPN协议字符串列表，顺序为
  // 偏爱
  std::vector<std::string> npn_list;

  Config();
  ~Config();

  bool is_rate_mode() const;
  bool is_timing_based_mode() const;
  bool has_base_uri() const;
};

struct RequestStat {
  // 发送请求的时间点
  std::chrono::steady_clock::time_point request_time;
  // 相同，但在墙上的时钟参考框架中
  std::chrono::system_clock::time_point request_wall_time;
  // 流关闭的时间点
  std::chrono::steady_clock::time_point stream_close_time;
  // 上传到目前为止发送的数据长度
  int64_t data_offset;
  // HTTP状态代码
  int status;
  // 如果流成功关闭，则为true。这意味着流是
  // 但这并不意味着HTTP级别错误（例如404）。
  bool completed;
};

struct ClientStat {
  // 客户端启动的时间（即，第一次连接开始）
  std::chrono::steady_clock::time_point client_start_time;
  // 客户端结束时间（即，客户端以某种方式处理了它的所有请求
  // 负责并断开连接）
  std::chrono::steady_clock::time_point client_end_time;
  // 成功完成的请求数，但不一定
  // 表示成功的HTTP状态代码。
  size_t req_success;

  // 每次连接时都会覆盖以下3个数字
  // 制作。

  // 连接开始时间
  std::chrono::steady_clock::time_point connect_start_time;
  // 连接时间
  std::chrono::steady_clock::time_point connect_time;
  // 到达第一字节的时间（TTFB）
  std::chrono::steady_clock::time_point ttfb;
};

struct SDStat {
  // 最小值、最大值、平均值和标准差
  double min, max, mean, sd;
  // 平均值内样本百分比-/+sd
  double within_sd;
};

struct SDStats {
  // 请求时间
  SDStat request;
  // 连接时间
  SDStat connect;
  // 到达第一字节的时间（TTFB）
  SDStat ttfb;
  // 每个客户端每秒的请求数
  SDStat rps;
};

struct Stats {
  Stats(size_t req_todo, size_t nclients);
  // 请求总数
  size_t req_todo;
  // 到目前为止发出的请求数
  size_t req_started;
  // 完成的请求数
  size_t req_done;
  // 成功完成的请求数，但不一定
  // 表示成功的HTTP状态代码。
  size_t req_success;
  // 标记为成功的请求数。HTTP状态代码为
  // 也被视为成功。这是req_done的子集。
  size_t req_status_success;
  // 失败的请求数。这是req_done的子集。
  size_t req_failed;
  // 由于网络错误而失败的请求数。这是
  // req_failed的子集。
  size_t req_error;
  // 由于超时而失败的请求数。
  size_t req_timedout;
  // “连线”上接收的字节数。如果使用SSL/TLS，
  // 这是应用程序接收的解密字节数。
  int64_t bytes_total;
  // 标头字段接收的字节数。这是
  // 压缩版本。
  int64_t bytes_head;
  // 标头字段在
  // 解压缩。
  int64_t bytes_head_decomp;
  // DATA帧中接收的字节数。
  int64_t bytes_body;
  // 每个HTTP状态类别的编号，状态[i]是状态代码
  // 在[i*100、（i+1）*100的范围内）。
  std::array<size_t, 6> status;
  // 每个请求的统计信息
  std::vector<RequestStat> req_stats;
  // 每个客户端的统计信息
  std::vector<ClientStat> client_stats;
};

enum ClientState { CLIENT_IDLE, CLIENT_CONNECTED };

// 此类型告诉客户端是否处于预热阶段或已结束
enum class Phase {
  INITIAL_IDLE,  // 预热阶段前的初始怠速状态
  WARM_UP,       // 未进行测量时的预热阶段
  MAIN_DURATION, // 主要测量阶段；如果基于定时
                 // 测试未运行，这是默认阶段
  DURATION_OVER  // 该阶段发生在测量结束后
};

struct Client;

// 我们使用储层取样方法
struct Sampling {
  // 最大样本数
  size_t max_samples;
  // 看到的样本数量，包括丢弃的样本。
  size_t n;
};

struct Worker {
  MemchunkPool mcpool;
  Stats stats;
  Sampling request_times_smp;
  Sampling client_smp;
  struct ev_loop *loop;
  SSL_CTX *ssl_ctx;
  Config *config;
  size_t progress_interval;
  uint32_t id;
  bool tls_info_report_done;
  bool app_info_report_done;
  size_t nconns_made;
  // 此工作程序处理的客户端数
  size_t nclients;
  // 每个客户端发出的请求数
  size_t nreqs_per_client;
  // 最多nreqsrm客户端会收到一个额外的请求
  size_t nreqs_rem;
  size_t rate;
  // 此工作线程中的最大样本数
  size_t max_samples;
  ev_timer timeout_watcher;
  // 此工作人员分配的下一个客户端ID
  uint32_t next_client_id;
  // 跟踪当前阶段（用于基于时间的实验）
  // 工人
  Phase current_phase;
  // 我们需要跟踪客户，以便在需要时阻止他们
  std::vector<Client *> clients;
  // 仅当请求数量不受限制时，此选项才处于活动状态
  // 明确规定
  ev_timer duration_watcher;
  ev_timer warmup_watcher;

  Worker(uint32_t id, SSL_CTX *ssl_ctx, size_t nreq_todo, size_t nclients,
         size_t rate, size_t max_samples, Config *config);
  ~Worker();
  Worker(Worker &&o) = default;
  void run();
  void sample_req_stat(RequestStat *req_stat);
  void sample_client_stat(ClientStat *cstat);
  void report_progress();
  void report_rate_progress();
  // 此函数调用所有客户端的析构函数。
  void stop_all_clients();
  // 此函数将客户端从该Worker的客户端列表中释放出来。
  void free_client(Client *);
};

struct Stream {
  RequestStat req_stat;
  int status_success;
  Stream();
};

struct Client {
  DefaultMemchunks wb;
  std::unordered_map<int32_t, Stream> streams;
  ClientStat cstat;
  std::unique_ptr<Session> session;
  ev_io wev;
  ev_io rev;
  std::function<int(Client &)> readfn, writefn;
  Worker *worker;
  SSL *ssl;
  ev_timer request_timeout_watcher;
  addrinfo *next_addr;
  // 当前地址的地址。当try_new_connection（）为
  // used，current_addr不是nullptr，而是使用
  // 通过next_addr尝试下一个地址。要尝试新地址，请设置
  // 在调用connect（）之前将nullptr设置为current_addr。
  addrinfo *current_addr;
  size_t reqidx;
  ClientState state;
  // 此客户端必须发出的请求数。
  size_t req_todo;
  // 要发出的请求数
  size_t req_left;
  // 当前已启动但尚未放弃的请求数
  // 或完成。
  size_t req_inflight;
  // 此客户端迄今发出的请求数。
  size_t req_started;
  // 此客户端到目前为止完成的请求数。
  size_t req_done;
  // 每个工作人员的客户端id
  uint32_t id;
  int fd;
  ev_timer conn_active_watcher;
  ev_timer conn_inactivity_watcher;
  std::string selected_proto;
  bool new_connection_requested;
  // 如果当前连接将关闭，则为true，并且不再有新连接
  // 无法处理请求。
  bool final;

  enum { ERR_CONNECT_FAIL = -100 };

  Client(uint32_t id, Worker *worker, size_t req_todo);
  ~Client();
  int make_socket(addrinfo *addr);
  int connect();
  void disconnect();
  void fail();
  // 当do_read（）返回-1时调用此函数。此函数
  // 如果请求，尝试再次连接到远程主机。如果
  // 因此，此函数返回0，应该保留此对象。
  // 否则，此函数将返回-1，此对象应为
  // 删除。
  int try_again_or_fail();
  void timeout();
  void restart_timeout();
  int submit_request();
  void process_request_failure();
  void process_timedout_streams();
  void process_abandoned_streams();
  void report_tls_info();
  void report_app_info();
  void terminate_session();
  // 要求客户端创建新连接，而不是失败。
  void try_new_connection();

  int do_read();
  int do_write();

  // do_read/do_write调用的低级I/O回调函数
  int connected();
  int read_clear();
  int write_clear();
  int tls_handshake();
  int read_tls();
  int write_tls();

  int on_read(const uint8_t *data, size_t len);
  int on_write();

  int connection_made();

  void on_request(int32_t stream_id);
  void on_header(int32_t stream_id, const uint8_t *name, size_t namelen,
                 const uint8_t *value, size_t valuelen);
  void on_status_code(int32_t stream_id, uint16_t status);
  // |成功|==true表示交换了请求/响应
  // |成功，但这并不意味着响应成功
  // |HTTP状态代码。
  void on_stream_close(int32_t stream_id, bool success, bool final = false);
  // 返回|stream_id|的RequestStat。此函数必须为
  // 在onrequest（stream_id）之后和之前调用
  // on_stream_close（stream_id，…）。否则，这将返回
  // 空指针。
  RequestStat *get_req_stat(int32_t stream_id);

  void record_request_time(RequestStat *req_stat);
  void record_connect_start_time();
  void record_connect_time();
  void record_ttfb();
  void clear_connect_times();
  void record_client_start_time();
  void record_client_end_time();

  void signal_write();
};

} // 命名空间h2load

#endif // H2LOAD_H

