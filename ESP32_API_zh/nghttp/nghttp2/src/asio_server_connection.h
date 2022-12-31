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
// 我们基于原始代码编写了此代码，该代码具有
// 以下许可证：
//
// 连接.hpp
// ~~~~~~~~~~~~~~
//
// 版权所有（c）2003-2013 Christopher M.Kohlhoff（chris at Kohlhoff.com）
//
// 根据Boost软件许可证1.0版发行。（请参阅随附的
// 文件LICENSE_1_0.txt或复制到http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_SERVER_CONNECTION_H
#define ASIO_SERVER_CONNECTION_H

#include "nghttp2_config.h"

#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/array.hpp>

#include <nghttp2/asio_http2_server.h>

#include "asio_server_http2_handler.h"
#include "asio_server_serve_mux.h"
#include "util.h"
#include "template.h"

#if BOOST_VERSION >= 107000
#  define GET_IO_SERVICE(s)                                                    \
    ((boost::asio::io_context &)(s).get_executor().context())
#else
#  define GET_IO_SERVICE(s) ((s).get_io_service())
#endif

namespace nghttp2 {

namespace asio_http2 {

namespace server {

///表示来自客户端的单个连接。
template <typename socket_type>
class connection : public std::enable_shared_from_this<connection<socket_type>>,
                   private boost::noncopyable {
public:
  ///构造与给定io_service的连接。
  template <typename... SocketArgs>
  explicit connection(
      serve_mux &mux,
      const boost::posix_time::time_duration &tls_handshake_timeout,
      const boost::posix_time::time_duration &read_timeout,
      SocketArgs &&... args)
      : socket_(std::forward<SocketArgs>(args)...),
        mux_(mux),
        deadline_(GET_IO_SERVICE(socket_)),
        tls_handshake_timeout_(tls_handshake_timeout),
        read_timeout_(read_timeout),
        writing_(false),
        stopped_(false) {}

  ///启动连接的第一个异步操作。
  void start() {
    boost::system::error_code ec;

    handler_ = std::make_shared<http2_handler>(
        GET_IO_SERVICE(socket_), socket_.lowest_layer().remote_endpoint(ec),
        [this]() { do_write(); }, mux_);
    if (handler_->start() != 0) {
      stop();
      return;
    }
    do_read();
  }

  socket_type &socket() { return socket_; }

  void start_tls_handshake_deadline() {
    deadline_.expires_from_now(tls_handshake_timeout_);
    deadline_.async_wait(
        std::bind(&connection::handle_deadline, this->shared_from_this()));
  }

  void start_read_deadline() {
    deadline_.expires_from_now(read_timeout_);
    deadline_.async_wait(
        std::bind(&connection::handle_deadline, this->shared_from_this()));
  }

  void handle_deadline() {
    if (stopped_) {
      return;
    }

    if (deadline_.expires_at() <=
        boost::asio::deadline_timer::traits_type::now()) {
      stop();
      deadline_.expires_at(boost::posix_time::pos_infin);
      return;
    }

    deadline_.async_wait(
        std::bind(&connection::handle_deadline, this->shared_from_this()));
  }

  void do_read() {
    auto self = this->shared_from_this();

    deadline_.expires_from_now(read_timeout_);

    socket_.async_read_some(
        boost::asio::buffer(buffer_),
        [this, self](const boost::system::error_code &e,
                     std::size_t bytes_transferred) {
          if (e) {
            stop();
            return;
          }

          if (handler_->on_read(buffer_, bytes_transferred) != 0) {
            stop();
            return;
          }

          do_write();

          if (!writing_ && handler_->should_stop()) {
            stop();
            return;
          }

          do_read();

          // 如果发生错误，则没有新的异步操作
          // 起动。这意味着对
          // 连接对象将消失
          // 此处理程序返回后自动销毁。这个
          // 连接类的析构函数关闭套接字。
        });
  }

  void do_write() {
    auto self = this->shared_from_this();

    if (writing_) {
      return;
    }

    int rv;
    std::size_t nwrite;

    rv = handler_->on_write(outbuf_, nwrite);

    if (rv != 0) {
      stop();
      return;
    }

    if (nwrite == 0) {
      if (handler_->should_stop()) {
        stop();
      }
      return;
    }

    writing_ = true;

    // 此处重置读取截止日期，因为通常客户端正在发送
    // 有些东西，它在做的时候不需要超时。
    deadline_.expires_from_now(read_timeout_);

    boost::asio::async_write(
        socket_, boost::asio::buffer(outbuf_, nwrite),
        [this, self](const boost::system::error_code &e, std::size_t) {
          if (e) {
            stop();
            return;
          }

          writing_ = false;

          do_write();
        });

    // 未启动新的异步操作。这意味着所有
    // 对连接对象的shared_ptr引用将消失
    // 该对象将在此处理程序之后自动销毁
    // 返回。连接类的析构函数关闭套接字。
  }

  void stop() {
    if (stopped_) {
      return;
    }

    stopped_ = true;
    boost::system::error_code ignored_ec;
    socket_.lowest_layer().close(ignored_ec);
    deadline_.cancel();
  }

private:
  socket_type socket_;

  serve_mux &mux_;

  std::shared_ptr<http2_handler> handler_;

  ///传入数据的缓冲区。
  boost::array<uint8_t, 8_k> buffer_;

  boost::array<uint8_t, 64_k> outbuf_;

  boost::asio::deadline_timer deadline_;
  boost::posix_time::time_duration tls_handshake_timeout_;
  boost::posix_time::time_duration read_timeout_;

  bool writing_;
  bool stopped_;
};

} // 命名空间服务器

} // 命名空间asio_http2

} // 命名空间nghttp2

#endif // ASIO_SERVER_CONNECTION_H

