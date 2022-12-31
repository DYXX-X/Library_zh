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
#ifndef ASIO_CLIENT_SESSION_IMPL_H
#define ASIO_CLIENT_SESSION_IMPL_H

#include "nghttp2_config.h"

#include <boost/array.hpp>

#include <nghttp2/asio_http2_client.h>

#include "template.h"

namespace nghttp2 {
namespace asio_http2 {
namespace client {

class stream;

using boost::asio::ip::tcp;

class session_impl : public std::enable_shared_from_this<session_impl> {
public:
  session_impl(boost::asio::io_service &io_service,
               const boost::posix_time::time_duration &connect_timeout);
  virtual ~session_impl();

  void start_resolve(const std::string &host, const std::string &service);

  void connected(tcp::resolver::iterator endpoint_it);
  void not_connected(const boost::system::error_code &ec);

  void on_connect(connect_cb cb);
  void on_error(error_cb cb);

  const connect_cb &on_connect() const;
  const error_cb &on_error() const;

  int write_trailer(stream &strm, header_map h);

  void cancel(stream &strm, uint32_t error_code);
  void resume(stream &strm);

  std::unique_ptr<stream> create_stream();
  std::unique_ptr<stream> pop_stream(int32_t stream_id);
  stream *create_push_stream(int32_t stream_id);
  stream *find_stream(int32_t stream_id);

  const request *submit(boost::system::error_code &ec,
                        const std::string &method, const std::string &uri,
                        generator_cb cb, header_map h, priority_spec spec);

  virtual void start_connect(tcp::resolver::iterator endpoint_it) = 0;
  virtual tcp::socket &socket() = 0;
  virtual void read_socket(
      std::function<void(const boost::system::error_code &ec, std::size_t n)>
          h) = 0;
  virtual void write_socket(
      std::function<void(const boost::system::error_code &ec, std::size_t n)>
          h) = 0;
  virtual void shutdown_socket() = 0;

  void shutdown();

  boost::asio::io_service &io_service();

  void signal_write();

  void enter_callback();
  void leave_callback();

  void do_read();
  void do_write();

  void read_timeout(const boost::posix_time::time_duration &t);

  void stop();
  bool stopped() const;

protected:
  boost::array<uint8_t, 8_k> rb_;
  boost::array<uint8_t, 64_k> wb_;
  std::size_t wblen_;

private:
  bool should_stop() const;
  bool setup_session();
  void call_error_cb(const boost::system::error_code &ec);
  void handle_deadline();
  void start_ping();
  void handle_ping(const boost::system::error_code &ec);

  boost::asio::io_service &io_service_;
  tcp::resolver resolver_;

  std::map<int32_t, std::unique_ptr<stream>> streams_;

  connect_cb connect_cb_;
  error_cb error_cb_;

  boost::asio::deadline_timer deadline_;
  boost::posix_time::time_duration connect_timeout_;
  boost::posix_time::time_duration read_timeout_;

  boost::asio::deadline_timer ping_;

  nghttp2_session *session_;

  const uint8_t *data_pending_;
  std::size_t data_pendinglen_;

  bool writing_;
  bool inside_callback_;
  bool stopped_;
};

} // 命名空间客户端
} // 命名空间asio_http2
} // 命名空间nghttp2

#endif // ASIO_CLIENT_SESSION_IMPL_H

