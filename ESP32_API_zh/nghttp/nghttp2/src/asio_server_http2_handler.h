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
#ifndef ASIO_SERVER_HTTP2_HANDLER_H
#define ASIO_SERVER_HTTP2_HANDLER_H

#include "nghttp2_config.h"

#include <map>
#include <functional>
#include <string>

#include <boost/array.hpp>

#include <nghttp2/asio_http2_server.h>

namespace nghttp2 {
namespace asio_http2 {
namespace server {

class http2_handler;
class stream;
class serve_mux;

struct callback_guard {
  callback_guard(http2_handler &h);
  ~callback_guard();
  http2_handler &handler;
};

using connection_write = std::function<void(void)>;

class http2_handler : public std::enable_shared_from_this<http2_handler> {
public:
  http2_handler(boost::asio::io_service &io_service,
                boost::asio::ip::tcp::endpoint ep, connection_write writefun,
                serve_mux &mux);

  ~http2_handler();

  int start();

  stream *create_stream(int32_t stream_id);
  void close_stream(int32_t stream_id);
  stream *find_stream(int32_t stream_id);

  void call_on_request(stream &s);

  bool should_stop() const;

  int start_response(stream &s);

  int submit_trailer(stream &s, header_map h);

  void stream_error(int32_t stream_id, uint32_t error_code);

  void initiate_write();

  void enter_callback();
  void leave_callback();

  void resume(stream &s);

  response *push_promise(boost::system::error_code &ec, stream &s,
                         std::string method, std::string raw_path_query,
                         header_map h);

  void signal_write();

  boost::asio::io_service &io_service();

  const boost::asio::ip::tcp::endpoint &remote_endpoint();

  const std::string &http_date();

  template <size_t N>
  int on_read(const boost::array<uint8_t, N> &buffer, std::size_t len) {
    callback_guard cg(*this);

    int rv;

    rv = nghttp2_session_mem_recv(session_, buffer.data(), len);

    if (rv < 0) {
      return -1;
    }

    return 0;
  }

  template <size_t N>
  int on_write(boost::array<uint8_t, N> &buffer, std::size_t &len) {
    callback_guard cg(*this);

    len = 0;

    if (buf_) {
      std::copy_n(buf_, buflen_, std::begin(buffer));

      len += buflen_;

      buf_ = nullptr;
      buflen_ = 0;
    }

    for (;;) {
      const uint8_t *data;
      auto nread = nghttp2_session_mem_send(session_, &data);
      if (nread < 0) {
        return -1;
      }

      if (nread == 0) {
        break;
      }

      if (len + nread > buffer.size()) {
        buf_ = data;
        buflen_ = nread;

        break;
      }

      std::copy_n(data, nread, std::begin(buffer) + len);

      len += nread;
    }

    return 0;
  }

private:
  std::map<int32_t, std::shared_ptr<stream>> streams_;
  connection_write writefun_;
  serve_mux &mux_;
  boost::asio::io_service &io_service_;
  boost::asio::ip::tcp::endpoint remote_ep_;
  nghttp2_session *session_;
  const uint8_t *buf_;
  std::size_t buflen_;
  bool inside_callback_;
  // 如果我们有挂起的onwrite调用，则为true。这样可以避免重复呼叫
  // io_service:：post的。
  bool write_signaled_;
  time_t tstamp_cached_;
  std::string formatted_date_;
};

} // 命名空间服务器
} // 命名空间asio_http2
} // 命名空间nghttp2

#endif // ASIO_SERVER_HTTP2_HANDLER_H

