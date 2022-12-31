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
#ifndef ASIO_SERVER_REQUEST_IMPL_H
#define ASIO_SERVER_REQUEST_IMPL_H

#include "nghttp2_config.h"

#include <nghttp2/asio_http2_server.h>
#include <boost/asio/ip/tcp.hpp>

namespace nghttp2 {
namespace asio_http2 {
namespace server {

class stream;

class request_impl {
public:
  request_impl();

  void header(header_map h);
  const header_map &header() const;
  header_map &header();

  void method(std::string method);
  const std::string &method() const;

  const uri_ref &uri() const;
  uri_ref &uri();

  void on_data(data_cb cb);

  void stream(class stream *s);
  void call_on_data(const uint8_t *data, std::size_t len);

  const boost::asio::ip::tcp::endpoint &remote_endpoint() const;
  void remote_endpoint(boost::asio::ip::tcp::endpoint ep);

  size_t header_buffer_size() const;
  void update_header_buffer_size(size_t len);

private:
  class stream *strm_;
  header_map header_;
  std::string method_;
  uri_ref uri_;
  data_cb on_data_cb_;
  boost::asio::ip::tcp::endpoint remote_ep_;
  size_t header_buffer_size_;
};

} // 命名空间服务器
} // 命名空间asio_http2
} // 命名空间nghttp2

#endif // ASIO_SERVER_REQUEST_IMPL_H

