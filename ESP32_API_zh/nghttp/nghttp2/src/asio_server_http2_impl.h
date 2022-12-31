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
#ifndef ASIO_SERVER_HTTP2_IMPL_H
#define ASIO_SERVER_HTTP2_IMPL_H

#include "nghttp2_config.h"

#include <nghttp2/asio_http2_server.h>

#include "asio_server_serve_mux.h"

namespace nghttp2 {

namespace asio_http2 {

namespace server {

class server;

class http2_impl {
public:
  http2_impl();
  boost::system::error_code listen_and_serve(
      boost::system::error_code &ec, boost::asio::ssl::context *tls_context,
      const std::string &address, const std::string &port, bool asynchronous);
  void num_threads(size_t num_threads);
  void backlog(int backlog);
  void tls_handshake_timeout(const boost::posix_time::time_duration &t);
  void read_timeout(const boost::posix_time::time_duration &t);
  bool handle(std::string pattern, request_cb cb);
  void stop();
  void join();
  const std::vector<std::shared_ptr<boost::asio::io_service>> &
  io_services() const;
  std::vector<int> ports() const;

private:
  std::unique_ptr<server> server_;
  std::size_t num_threads_;
  int backlog_;
  serve_mux mux_;
  boost::posix_time::time_duration tls_handshake_timeout_;
  boost::posix_time::time_duration read_timeout_;
};

} // 命名空间服务器

} // 命名空间asio_http2

} // 命名空间nghttp2

#endif // ASIO_SERVER_HTTP2_IMPL_H

