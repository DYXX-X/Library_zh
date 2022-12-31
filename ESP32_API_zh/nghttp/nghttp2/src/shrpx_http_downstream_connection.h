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
#ifndef SHRPX_HTTP_DOWNSTREAM_CONNECTION_H
#define SHRPX_HTTP_DOWNSTREAM_CONNECTION_H

#include "shrpx.h"

#include "llhttp.h"

#include "shrpx_downstream_connection.h"
#include "shrpx_io_control.h"
#include "shrpx_connection.h"

namespace shrpx {

class DownstreamConnectionPool;
class Worker;
struct DownstreamAddrGroup;
struct DownstreamAddr;
struct DNSQuery;

class HttpDownstreamConnection : public DownstreamConnection {
public:
  HttpDownstreamConnection(const std::shared_ptr<DownstreamAddrGroup> &group,
                           DownstreamAddr *addr, struct ev_loop *loop,
                           Worker *worker);
  virtual ~HttpDownstreamConnection();
  virtual int attach_downstream(Downstream *downstream);
  virtual void detach_downstream(Downstream *downstream);

  virtual int push_request_headers();
  virtual int push_upload_data_chunk(const uint8_t *data, size_t datalen);
  virtual int end_upload_data();
  void end_upload_data_chunk();

  virtual void pause_read(IOCtrlReason reason);
  virtual int resume_read(IOCtrlReason reason, size_t consumed);
  virtual void force_resume_read();

  virtual int on_read();
  virtual int on_write();

  virtual void on_upstream_change(Upstream *upstream);

  virtual bool poolable() const;

  virtual const std::shared_ptr<DownstreamAddrGroup> &
  get_downstream_addr_group() const;
  virtual DownstreamAddr *get_addr() const;

  int initiate_connection();

  int write_first();
  int read_clear();
  int write_clear();
  int read_tls();
  int write_tls();

  int process_input(const uint8_t *data, size_t datalen);
  int tls_handshake();

  int connected();
  void signal_write();
  int actual_signal_write();

  // 返回用于连接到后端的地址。可能是nullptr。
  const Address *get_raddr() const;

  int noop();

  int process_blocked_request_buf();

private:
  Connection conn_;
  std::function<int(HttpDownstreamConnection &)> on_read_, on_write_,
      signal_write_;
  Worker *worker_;
  // 如果未使用TLS，则为nullptr。
  SSL_CTX *ssl_ctx_;
  std::shared_ptr<DownstreamAddrGroup> group_;
  // 远程终结点的地址
  DownstreamAddr *addr_;
  // 用于联系后端的实际远程地址。这最初是
  // nullptr，并且可以指向&addr->addr，或
  // resolved_addr.get（）。
  const Address *raddr_;
  // 如果使用dns参数，则解析IP地址
  std::unique_ptr<Address> resolved_addr_;
  std::unique_ptr<DNSQuery> dns_query_;
  IOControl ioctrl_;
  llhttp_t response_htp_;
  // 如果第一次写入成功，则为true。
  bool first_write_done_;
  // 如果可以重用此对象，则为true
  bool reusable_;
  // 如果请求头被写入请求缓冲区，则为true。
  bool request_header_written_;
};

} // 命名空间shrpx

#endif // SHRPX_HTTP_DOWNSTREAM_CONNECTION_H

