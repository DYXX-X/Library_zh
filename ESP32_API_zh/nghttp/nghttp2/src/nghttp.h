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
#ifndef NGHTTP_H
#define NGHTTP_H

#include "nghttp2_config.h"

#include <sys/types.h>
#ifdef HAVE_SYS_SOCKET_H
#  include <sys/socket.h>
#endif // HAVE_SYS_SOCKET_H
#ifdef HAVE_NETDB_H
#  include <netdb.h>
#endif // HAVE_NETDB_H

#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <memory>

#include <openssl/ssl.h>

#include <ev.h>

#include <nghttp2/nghttp2.h>

#include "llhttp.h"

#include "memchunk.h"
#include "http2.h"
#include "nghttp2_gzip.h"
#include "template.h"

namespace nghttp2 {

class HtmlParser;

struct Config {
  Config();
  ~Config();

  Headers headers;
  Headers trailer;
  std::vector<int32_t> weight;
  std::string certfile;
  std::string keyfile;
  std::string datafile;
  std::string harfile;
  std::string scheme_override;
  std::string host_override;
  nghttp2_option *http2_option;
  int64_t header_table_size;
  int64_t min_header_table_size;
  int64_t encoder_header_table_size;
  size_t padding;
  size_t max_concurrent_streams;
  ssize_t peer_max_concurrent_streams;
  int multiply;
  // 毫秒
  ev_tstamp timeout;
  int window_bits;
  int connection_window_bits;
  int verbose;
  uint16_t port_override;
  bool null_out;
  bool remote_name;
  bool get_assets;
  bool stat;
  bool upgrade;
  bool continuation;
  bool no_content_length;
  bool no_dep;
  bool hexdump;
  bool no_push;
  bool expect_continue;
  bool verify_peer;
};

enum class RequestState { INITIAL, ON_REQUEST, ON_RESPONSE, ON_COMPLETE };

struct RequestTiming {
  // 开始发送请求的时间点。
  // 对应于资源计时TR中的requestStart。
  std::chrono::steady_clock::time_point request_start_time;
  // 收到响应的第一个字节的时间点。
  // 对应于资源计时TR中的responseStart。
  std::chrono::steady_clock::time_point response_start_time;
  // 接收响应的最后一个字节的时间点。
  // 对应于资源定时TR中的responseEnd。
  std::chrono::steady_clock::time_point response_end_time;
  RequestState state;
  RequestTiming() : state(RequestState::INITIAL) {}
};

struct Request; // ContinueTimer的转发声明

struct ContinueTimer {
  ContinueTimer(struct ev_loop *loop, Request *req);
  ~ContinueTimer();

  void start();
  void stop();

  // 如果
  // 回调尚未运行
  void dispatch_continue();

  struct ev_loop *loop;
  ev_timer timer;
};

struct Request {
  // 对于推送请求，|uri|为空，|u|为零清除。
  Request(const std::string &uri, const http_parser_url &u,
          const nghttp2_data_provider *data_prd, int64_t data_length,
          const nghttp2_priority_spec &pri_spec, int level = 0);
  ~Request();

  void init_inflater();

  void init_html_parser();
  int update_html_parser(const uint8_t *data, size_t len, int fin);

  std::string make_reqpath() const;

  bool is_ipv6_literal_addr() const;

  Headers::value_type *get_res_header(int32_t token);
  Headers::value_type *get_req_header(int32_t token);

  void record_request_start_time();
  void record_response_start_time();
  void record_response_end_time();

  // 返回考虑重写方案的方案。
  StringRef get_real_scheme() const;
  // 返回请求主机，不带端口，考虑
  // 重写的主机。
  StringRef get_real_host() const;
  // 返回请求端口，
  // 和方案。
  uint16_t get_real_port() const;

  Headers res_nva;
  Headers req_nva;
  std::string method;
  // 不带片段的URI
  std::string uri;
  http_parser_url u;
  nghttp2_priority_spec pri_spec;
  RequestTiming timing;
  int64_t data_length;
  int64_t data_offset;
  // 从服务器接收的字节数
  int64_t response_len;
  nghttp2_gzip *inflater;
  std::unique_ptr<HtmlParser> html_parser;
  const nghttp2_data_provider *data_prd;
  size_t header_buffer_size;
  int32_t stream_id;
  int status;
  // 递归级别：0:第一个实体，1:从第一个实体链接的实体
  int level;
  http2::HeaderIndex res_hdidx;
  // 用于传入PUSH_PROMISE
  http2::HeaderIndex req_hdidx;
  bool expect_final_response;
  // 仅当此请求使用Expect/Continue时分配
  std::unique_ptr<ContinueTimer> continue_timer;
};

struct SessionTiming {
  // 开始操作的时间点。相对应
  // 资源定时TR中的startTime，但记录在系统时钟时间中。
  std::chrono::system_clock::time_point system_start_time;
  // 同上，但记录在稳定的时钟时间内。
  std::chrono::steady_clock::time_point start_time;
  // DNS解析完成的时间点。对应的
  // 到资源定时TR中的domainLookupEnd。
  std::chrono::steady_clock::time_point domain_lookup_end_time;
  // 建立连接或SSL/TLS的时间点
  // 握手已完成。对应于资源中的connectEnd
  // 定时TR。
  std::chrono::steady_clock::time_point connect_end_time;
};

enum class ClientState { IDLE, CONNECTED };

struct HttpClient {
  HttpClient(const nghttp2_session_callbacks *callbacks, struct ev_loop *loop,
             SSL_CTX *ssl_ctx);
  ~HttpClient();

  bool need_upgrade() const;
  int resolve_host(const std::string &host, uint16_t port);
  int initiate_connection();
  void disconnect();

  int noop();
  int read_clear();
  int write_clear();
  int connected();
  int tls_handshake();
  int read_tls();
  int write_tls();

  int do_read();
  int do_write();

  int on_upgrade_connect();
  int on_upgrade_read(const uint8_t *data, size_t len);
  int on_read(const uint8_t *data, size_t len);
  int on_write();

  int connection_made();
  void connect_fail();
  void request_done(Request *req);

  void signal_write();

  bool all_requests_processed() const;
  void update_hostport();
  bool add_request(const std::string &uri,
                   const nghttp2_data_provider *data_prd, int64_t data_length,
                   const nghttp2_priority_spec &pri_spec, int level = 0);

  void record_start_time();
  void record_domain_lookup_end_time();
  void record_connect_end_time();

#ifdef HAVE_JANSSON
  void output_har(FILE *outfile);
#endif // HAVE_JANSSON

  MemchunkPool mcpool;
  DefaultMemchunks wb;
  std::vector<std::unique_ptr<Request>> reqvec;
  // 插入已添加到reqvec中的路径以防止多次请求
  // 对于1个资源。
  std::set<std::string> path_cache;
  std::string scheme;
  std::string host;
  std::string hostport;
  // 用于解析服务器的HTTP升级响应
  std::unique_ptr<llhttp_t> htp;
  SessionTiming timing;
  ev_io wev;
  ev_io rev;
  ev_timer wt;
  ev_timer rt;
  ev_timer settings_timer;
  std::function<int(HttpClient &)> readfn, writefn;
  std::function<int(HttpClient &, const uint8_t *, size_t)> on_readfn;
  std::function<int(HttpClient &)> on_writefn;
  nghttp2_session *session;
  const nghttp2_session_callbacks *callbacks;
  struct ev_loop *loop;
  SSL_CTX *ssl_ctx;
  SSL *ssl;
  addrinfo *addrs;
  addrinfo *next_addr;
  addrinfo *cur_addr;
  // 已完成的请求数，包括失败的请求数。
  size_t complete;
  // 本地终结点接收END_STREAM的请求数
  // 来自同行。
  size_t success;
  // 设置的长度s_payload
  size_t settings_payloadlen;
  ClientState state;
  // HTTP升级响应消息的HTTP状态代码。
  unsigned int upgrade_response_status_code;
  int fd;
  // 如果HTTP升级请求的响应消息为完整，则为true
  // 收到。升级成功与否无关。
  bool upgrade_response_complete;
  // SETTINGS有效负载在HTTP升级中作为token68发送
  std::array<uint8_t, 128> settings_payload;

  enum { ERR_CONNECT_FAIL = -100 };
};

} // 命名空间nghttp2

#endif // NGHTTP_H

