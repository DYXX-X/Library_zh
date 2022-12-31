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
#ifndef ASIO_CLIENT_SESSION_TLS_IMPL_H
#define ASIO_CLIENT_SESSION_TLS_IMPL_H

#include "asio_client_session_impl.h"

#include <nghttp2/asio_http2_client.h>

namespace nghttp2 {
namespace asio_http2 {
namespace client {

using boost::asio::ip::tcp;

using ssl_socket = boost::asio::ssl::stream<tcp::socket>;

class session_tls_impl : public session_impl {
public:
  session_tls_impl(boost::asio::io_service &io_service,
                   boost::asio::ssl::context &tls_ctx, const std::string &host,
                   const std::string &service,
                   const boost::posix_time::time_duration &connect_timeout);
  virtual ~session_tls_impl();

  virtual void start_connect(tcp::resolver::iterator endpoint_it);
  virtual tcp::socket &socket();
  virtual void read_socket(
      std::function<void(const boost::system::error_code &ec, std::size_t n)>
          h);
  virtual void write_socket(
      std::function<void(const boost::system::error_code &ec, std::size_t n)>
          h);
  virtual void shutdown_socket();

private:
  ssl_socket socket_;
};

} // 命名空间客户端
} // 命名空间asio_http2
} // 命名空间nghttp2

#endif // ASIO_CLIENT_SESSION_TLS_IMPL_H

