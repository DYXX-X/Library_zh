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
#ifndef ASIO_SERVER_RESPONSE_IMPL_H
#define ASIO_SERVER_RESPONSE_IMPL_H

#include "nghttp2_config.h"

#include <nghttp2/asio_http2_server.h>

namespace nghttp2 {
namespace asio_http2 {
namespace server {

class stream;

enum class response_state {
  INITIAL,
  // 已调用response_impl:：write_head（）
  HEADER_DONE,
  // 调用了response_impl:：end（）
  BODY_STARTED,
};

class response_impl {
public:
  response_impl();
  void write_head(unsigned int status_code, header_map h = header_map{});
  void end(std::string data = "");
  void end(generator_cb cb);
  void write_trailer(header_map h);
  void on_close(close_cb cb);
  void resume();

  void cancel(uint32_t error_code);

  response *push(boost::system::error_code &ec, std::string method,
                 std::string raw_path_query, header_map) const;

  boost::asio::io_service &io_service();

  void start_response();

  unsigned int status_code() const;
  const header_map &header() const;
  void pushed(bool f);
  void push_promise_sent();
  void stream(class stream *s);
  generator_cb::result_type call_read(uint8_t *data, std::size_t len,
                                      uint32_t *data_flags);
  void call_on_close(uint32_t error_code);

private:
  class stream *strm_;
  header_map header_;
  generator_cb generator_cb_;
  close_cb close_cb_;
  unsigned int status_code_;
  response_state state_;
  // 如果这是推送流的响应，则为true
  bool pushed_;
  // 如果PUSH_PROMISE是推送的响应，则为true
  // 流动
  bool push_promise_sent_;
};

} // 命名空间服务器
} // 命名空间asio_http2
} // 命名空间nghttp2

#endif // ASIO_SERVER_RESPONSE_IMPL_H

