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
#ifndef ASIO_CLIENT_REQUEST_IMPL_H
#define ASIO_CLIENT_REQUEST_IMPL_H

#include "nghttp2_config.h"

#include <nghttp2/asio_http2_client.h>

namespace nghttp2 {
namespace asio_http2 {
namespace client {

class response;
class stream;

class request_impl {
public:
  request_impl();

  request_impl(const request_impl &) = delete;
  request_impl &operator=(const request_impl &) = delete;

  void write_trailer(header_map h);

  void cancel(uint32_t error_code);

  void on_response(response_cb cb);
  void call_on_response(response &res);

  void on_push(request_cb cb);
  void call_on_push(request &push_req);

  void on_close(close_cb cb);
  void call_on_close(uint32_t error_code);

  void on_read(generator_cb cb);
  generator_cb::result_type call_on_read(uint8_t *buf, std::size_t len,
                                         uint32_t *data_flags);

  void resume();

  void header(header_map h);
  header_map &header();
  const header_map &header() const;

  void stream(class stream *strm);

  void uri(uri_ref uri);
  const uri_ref &uri() const;
  uri_ref &uri();

  void method(std::string s);
  const std::string &method() const;

  size_t header_buffer_size() const;
  void update_header_buffer_size(size_t len);

private:
  header_map header_;
  response_cb response_cb_;
  request_cb push_request_cb_;
  close_cb close_cb_;
  generator_cb generator_cb_;
  class stream *strm_;
  uri_ref uri_;
  std::string method_;
  size_t header_buffer_size_;
};

} // 命名空间客户端
} // 命名空间asio_http2
} // 命名空间nghttp2

#endif // ASIO_CLIENT_REQUEST_IMPL_H

