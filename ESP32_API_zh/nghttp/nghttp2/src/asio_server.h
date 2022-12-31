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
// 服务器.hpp
// ~~~~~~~~~~
//
// 版权所有（c）2003-2013 Christopher M.Kohlhoff（chris at Kohlhoff.com）
//
// 根据Boost软件许可证1.0版发行。（请参阅随附的
// 文件LICENSE_1_0.txt或复制到http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_SERVER_H
#define ASIO_SERVER_H

#include "nghttp2_config.h"

#include <string>
#include <vector>
#include <memory>

#include <boost/noncopyable.hpp>

#include <nghttp2/asio_http2_server.h>

#include "asio_io_service_pool.h"

namespace nghttp2 {

namespace asio_http2 {

namespace server {

class serve_mux;

using boost::asio::ip::tcp;

using ssl_socket = boost::asio::ssl::stream<tcp::socket>;

class server : private boost::noncopyable {
public:
  explicit server(std::size_t io_service_pool_size,
                  const boost::posix_time::time_duration &tls_handshake_timeout,
                  const boost::posix_time::time_duration &read_timeout);

  boost::system::error_code
  listen_and_serve(boost::system::error_code &ec,
                   boost::asio::ssl::context *tls_context,
                   const std::string &address, const std::string &port,
                   int backlog, serve_mux &mux, bool asynchronous = false);
  void join();
  void stop();

  ///访问所有io_service对象。
  const std::vector<std::shared_ptr<boost::asio::io_service>> &
  io_services() const;

  ///返回一个向量，其中包含正在使用的所有接收器端口。
  const std::vector<int> ports() const;

private:
  ///启动异步接受操作。
  void start_accept(tcp::acceptor &acceptor, serve_mux &mux);
  ///同上，但使用tls_context
  void start_accept(boost::asio::ssl::context &tls_context,
                    tcp::acceptor &acceptor, serve_mux &mux);

  ///解析地址并将套接字绑定到解析的地址。
  boost::system::error_code bind_and_listen(boost::system::error_code &ec,
                                            const std::string &address,
                                            const std::string &port,
                                            int backlog);

  ///用于执行异步的io_service对象池
  ///操作。
  io_service_pool io_service_pool_;

  ///接收器用于侦听传入连接。
  std::vector<tcp::acceptor> acceptors_;

  std::unique_ptr<boost::asio::ssl::context> ssl_ctx_;

  boost::posix_time::time_duration tls_handshake_timeout_;
  boost::posix_time::time_duration read_timeout_;
};

} // 命名空间服务器

} // 命名空间asio_http2

} // 命名空间nghttp2

#endif // ASIO_SERVER_H

