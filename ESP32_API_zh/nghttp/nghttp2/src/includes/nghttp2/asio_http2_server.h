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
#ifndef ASIO_HTTP2_SERVER_H
#define ASIO_HTTP2_SERVER_H

#include <nghttp2/asio_http2.h>

namespace nghttp2 {

namespace asio_http2 {

namespace server {

class request_impl;
class response_impl;

class request {
public:
  // 应用程序不能直接调用它。
  request();
  ~request();

  // 返回请求标头字段。pusedo标头字段
  // 以冒号（：）开头，从列表中删除。
  const header_map &header() const;

  // 返回方法（例如GET）。
  const std::string &method() const;

  // 返回请求URI，拆分为组件。
  const uri_ref &uri() const;

  // 设置当请求主体的块为
  // 收到。
  void on_data(data_cb cb) const;

  // 应用程序不能直接调用它。
  request_impl &impl() const;

  // 返回请求的远程终结点
  const boost::asio::ip::tcp::endpoint &remote_endpoint() const;

private:
  std::unique_ptr<request_impl> impl_;
};

class response {
public:
  // 应用程序不能直接调用它。
  response();
  ~response();

  // 使用|status_code|（例如200）和
  // |h|中的其他标头字段。
  void write_head(unsigned int status_code, header_map h = header_map{}) const;

  // 将|data|作为请求正文发送。不再调用end（）
  // 允许。
  void end(std::string data = "") const;

  // 将回调设置为响应体的生成器。不再
  // 允许调用end（）。
  void end(generator_cb cb) const;

  // 编写拖车部分。必须在设置两个
  // NGHTTP2_DATA_FLAG_EOF和NGHTTP2_DATA _FLAG_NO_END_STREAM设置在
  // *generator_cb中的data_flag参数传递给end（）函数。
  void write_trailer(header_map h) const;

  // 设置当此请求和响应为
  // 完成。调用此回调后，应用程序
  // 不能访问请求和响应对象。
  void on_close(close_cb cb) const;

  // 使用给定的错误代码取消此请求和响应。
  void cancel(uint32_t error_code = NGHTTP2_INTERNAL_ERROR) const;

  // 恢复延迟的响应。
  void resume() const;

  // 使用|method|推送由|raw_path_query|表示的资源。这个
  // 可以在|h|中提供其他标题字段。此函数
  // 返回承诺流的响应对象的指针，否则
  // nullptr，错误代码填入|ec|。请注意
  // |h|中给定的头字段名称必须小写。
  const response *push(boost::system::error_code &ec, std::string method,
                       std::string raw_path_query,
                       header_map h = header_map{}) const;

  // 返回状态代码。
  unsigned int status_code() const;

  // 返回运行此响应的boost:：asio:：io_service。
  boost::asio::io_service &io_service() const;

  // 应用程序不能直接调用它。
  response_impl &impl() const;

private:
  std::unique_ptr<response_impl> impl_;
};

// 这就是所谓的请求回调。每次请求时调用
// 收到。|request|和|response|对象的生存期结束
// 当调用response:：onclose（）设置的回调时。之后，
// 应用程序不能访问这些对象。
typedef std::function<void(const request &, const response &)> request_cb;

class http2_impl;

class http2 {
public:
  http2();
  ~http2();

  http2(http2 &&other) noexcept;
  http2 &operator=(http2 &&other) noexcept;

  // 在给定地址和端口上启动侦听连接并提供服务
  // 明文TCP连接中的传入请求。如果|异步|
  // 为false，除非出现错误，否则此函数将永远阻塞。
  // 如果为真，则在服务器启动后，此函数将返回
  // 立即，调用方应调用stop（）和join（）
  // 正常关闭服务器。
  boost::system::error_code listen_and_serve(boost::system::error_code &ec,
                                             const std::string &address,
                                             const std::string &port,
                                             bool asynchronous = false);

  // 在给定地址和端口上启动侦听连接并提供服务
  // SSL/TLS加密连接中的传入请求。对于
  // |异步|参数，请参阅cleartext版本
  // |listen_and_serve |。
  boost::system::error_code
  listen_and_serve(boost::system::error_code &ec,
                   boost::asio::ssl::context &tls_context,
                   const std::string &address, const std::string &port,
                   bool asynchronous = false);

  // 使用路径模式|pattern|注册请求处理程序|cb|。这
  // 函数将失败，如果相同的模式
  // 已注册或|pattern|为空字符串。否则
  // 返回true。模式匹配规则与
  // net/http/ServeMux在戈朗。引自《高尔夫手册》
  // (http://golang.org/pkg/net/http/#ServeMux):
  //
  //   模式名称固定，根路径，如“/favicon.ico”，或
  //   根子树，如“/images/”（注意后面
  //   斜线）。较长的图案优先于较短的图案，因此
  //   如果同时为“/images/”和
  //   “/images/缩略图/”，将调用后一个处理程序
  //   以“/images/缩略图/”开头的路径，前者将
  //   接收对“/images/”子树中任何其他路径的请求。
  //
  //   注意，由于以斜线结尾的模式将根命名为
  //   子树，模式“/”匹配其他路径不匹配的所有路径
  //   注册模式，而不仅仅是路径为“/”的URL。
  //
  //   模式可以选择以主机名开头，限制
  //   仅与该主机上的URL匹配。特定于主机的模式
  //   优先于常规模式，以便处理程序可以
  //   注册两种模式“/codesearch”和
  //   “codesearch.google.com/”，而不接收请求
  //   "http://www.google.com/".
  //
  // 就像golang中的ServeMux一样，URL请求路径被净化
  // 如果它们包含.或..元素，它们将被重定向到
  // 等效的.-和..-免费URL。
  bool handle(std::string pattern, request_cb cb);

  // 设置处理传入HTTP请求的本机线程数。
  // 默认值为1。
  void num_threads(size_t num_threads);

  // 设置挂起队列的最大长度
  // 连接。
  void backlog(int backlog);

  // 设置TLS握手超时，默认为60秒。
  void tls_handshake_timeout(const boost::posix_time::time_duration &t);

  // 设置读取超时，默认为60秒。
  void read_timeout(const boost::posix_time::time_duration &t);

  // 正常停止http2服务器
  void stop();

  // 在http2服务器上加入并等待其完全停止
  void join();

  // 访问io_service对象。
  const std::vector<std::shared_ptr<boost::asio::io_service>> &
  io_services() const;

  // 返回使用中端口的向量
  std::vector<int> ports() const;

private:
  std::unique_ptr<http2_impl> impl_;
};

// 配置|tls_context|以供服务器使用。此函数设置对
// OpenSSL选项（禁用SSLv2和SSLv3以及压缩）和
// 启用ECDHE密码。还配置了NPN回调。
boost::system::error_code
configure_tls_context_easy(boost::system::error_code &ec,
                           boost::asio::ssl::context &tls_context);

// 返回请求处理程序，使用
// |状态代码|。|uri|按原样显示在“位置”标头字段中。
request_cb redirect_handler(int status_code, std::string uri);

// 返回请求处理程序以答复给定的|status_code|和HTML
// 包括关于状态代码的消息。
request_cb status_handler(int status_code);

} // 命名空间服务器

} // 命名空间asio_http2

} // 命名空间nghttp2

#endif // ASIO_HTTP2_SERVER_H

