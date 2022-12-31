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
#ifndef SHRPX_MEMCACHED_CONNECTION_H
#define SHRPX_MEMCACHED_CONNECTION_H

#include "shrpx.h"

#include <memory>
#include <deque>

#include <ev.h>

#include "shrpx_connection.h"
#include "shrpx_tls.h"
#include "shrpx_connect_blocker.h"
#include "buffer.h"
#include "network.h"

using namespace nghttp2;

namespace shrpx {

struct MemcachedRequest;
enum class MemcachedOp : uint8_t;
enum class MemcachedStatusCode : uint16_t;

enum class MemcachedParseState {
  HEADER24,
  EXTRA,
  VALUE,
};

// 分析memcached服务器的响应时存储状态
struct MemcachedParseContext {
  // 值的缓冲区，动态分配。
  std::vector<uint8_t> value;
  // cas响应
  uint64_t cas;
  // keylen响应
  size_t keylen;
  // 响应中的extralen
  size_t extralen;
  // 全身响应。值的长度为totalbody-
  // extralen-keylen。
  size_t totalbody;
  // 剩余读取可变长度字段的字节数。
  size_t read_left;
  // 解析器状态；参见上面的枚举
  MemcachedParseState state;
  // 响应状态代码
  MemcachedStatusCode status_code;
  // 操作响应
  MemcachedOp op;
};

struct MemcachedSendbuf {
  // 标头缓冲区+额外+键
  Buffer<512> headbuf;
  // 与此对象关联的MemcachedRequest
  MemcachedRequest *req;
  // 发送值时剩余的字节数
  size_t send_value_left;
  // 返回此对象传输的字节数。
  size_t left() const { return headbuf.rleft() + send_value_left; }
};

constexpr uint8_t MEMCACHED_REQ_MAGIC = 0x80;
constexpr uint8_t MEMCACHED_RES_MAGIC = 0x81;

// MemcachedConnection实现了memcached二进制协议的一部分。
// 这不是完整的棕色实现。我们需要的只是
// 实施。我们只使用GET和ADD。
//
// https://github.com/memcached/memcached/blob/master/doc/protocol-binary.xml
// https://code.google.com/p/memcached/wiki/MemcacheBinaryProtocol
class MemcachedConnection {
public:
  MemcachedConnection(const Address *addr, struct ev_loop *loop,
                      SSL_CTX *ssl_ctx, const StringRef &sni_name,
                      MemchunkPool *mcpool, std::mt19937 &gen);
  ~MemcachedConnection();

  void disconnect();

  int add_request(std::unique_ptr<MemcachedRequest> req);
  int initiate_connection();

  int connected();
  int on_write();
  int on_read();

  int write_clear();
  int read_clear();

  int tls_handshake();
  int write_tls();
  int read_tls();

  size_t fill_request_buffer(struct iovec *iov, size_t iovlen);
  void drain_send_queue(size_t nwrite);

  void make_request(MemcachedSendbuf *sendbuf, MemcachedRequest *req);
  int parse_packet();
  size_t serialized_size(MemcachedRequest *req);

  void signal_write();

  int noop();

  void reconnect_or_fail();

private:
  Connection conn_;
  std::deque<std::unique_ptr<MemcachedRequest>> recvq_;
  std::deque<std::unique_ptr<MemcachedRequest>> sendq_;
  std::deque<MemcachedSendbuf> sendbufv_;
  std::function<int(MemcachedConnection &)> do_read_, do_write_;
  StringRef sni_name_;
  tls::TLSSessionCache tls_session_cache_;
  ConnectBlocker connect_blocker_;
  MemcachedParseContext parse_state_;
  const Address *addr_;
  SSL_CTX *ssl_ctx_;
  // sendbufv_中要传输的字节总数。
  size_t sendsum_;
  size_t try_count_;
  bool connected_;
  Buffer<8_k> recvbuf_;
};

} // 命名空间shrpx

#endif // SHRPX_MEMCACHED_CONNECTION_H

