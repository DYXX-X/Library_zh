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
#ifndef ASIO_HTTP2_CLIENT_H
#define ASIO_HTTP2_CLIENT_H

#include <nghttp2/asio_http2.h>

namespace nghttp2 {

namespace asio_http2 {

namespace client {

class response_impl;

class response {
public:
  // 应用程序不能直接调用它。
  response();
  ~response();

  // 设置当响应体的块为
  // 收到。
  void on_data(data_cb cb) const;

  // 返回状态代码。
  int status_code() const;

  // 返回内容长度-如果未知，则为1。
  int64_t content_length() const;

  // 返回响应标头字段。pusedo报头字段，
  // 以冒号（：）开头的。
  const header_map &header() const;

  // 应用程序不能直接调用它。
  response_impl &impl() const;

private:
  std::unique_ptr<response_impl> impl_;
};

class request;

using response_cb = std::function<void(const response &)>;
using request_cb = std::function<void(const request &)>;
using connect_cb =
    std::function<void(boost::asio::ip::tcp::resolver::iterator)>;

class request_impl;

class request {
public:
  // 应用程序不能直接调用它。
  request();
  ~request();

  // 设置收到响应标头时调用的回调。
  void on_response(response_cb cb) const;

  // 设置推送请求标头为
  // 收到。
  void on_push(request_cb cb) const;

  // 设置当此请求和响应为
  // 完成。调用此回调后，应用程序
  // 不能访问请求和响应对象。
  void on_close(close_cb cb) const;

  // 编写拖车部分。必须在设置两个
  // NGHTTP2_DATA_FLAG_EOF和NGHTTP2_DATA _FLAG_NO_END_STREAM设置在
  // *generator_cb中的data_flag参数传递给会话：：submit（）
  // 作用
  void write_trailer(header_map h) const;

  // 使用给定的错误代码取消此请求和响应。
  void cancel(uint32_t error_code = NGHTTP2_INTERNAL_ERROR) const;

  // 继续延迟上载。
  void resume() const;

  // 返回方法（例如GET）。
  const std::string &method() const;

  // 返回请求URI，拆分为组件。
  const uri_ref &uri() const;

  // 返回请求标头字段。pusedo标头字段
  // 以冒号（：）开头，从列表中删除。
  const header_map &header() const;

  // 应用程序不能直接调用它。
  request_impl &impl() const;

private:
  std::unique_ptr<request_impl> impl_;
};

// 包装nghttp2_priority_spec。
class priority_spec {
public:
  // 默认的ctor仅由sentinel值使用。
  priority_spec() = default;

  // 使用给定的优先级设置创建优先级等级库。
  explicit priority_spec(const int32_t stream_id, const int32_t weight,
                         const bool exclusive = false);

  // 返回指向有效nghttp2优先级规范的指针，或返回null。
  const nghttp2_priority_spec *get() const;

  // 指示此规范是否有效（即使用
  // 值）。
  bool valid() const;

private:
  nghttp2_priority_spec spec_;
  bool valid_ = false;
};

class session_impl;

class session {
public:
  // 通过连接到|host|和|service启动HTTP/2会话|
  // （例如，“80”）使用带有连接超时的明文TCP连接
  // 60秒。
  session(boost::asio::io_service &io_service, const std::string &host,
          const std::string &service);

  // 与上一个相同，但具有固定的本地端点
  session(boost::asio::io_service &io_service,
          const boost::asio::ip::tcp::endpoint &local_endpoint,
          const std::string &host, const std::string &service);

  // 通过连接到|host|和|service启动HTTP/2会话|
  // （例如，“80”）使用带有给定连接的明文TCP连接
  // 超时。
  session(boost::asio::io_service &io_service, const std::string &host,
          const std::string &service,
          const boost::posix_time::time_duration &connect_timeout);

  // 与上一个相同，但具有固定的本地端点
  session(boost::asio::io_service &io_service,
          const boost::asio::ip::tcp::endpoint &local_endpoint,
          const std::string &host, const std::string &service,
          const boost::posix_time::time_duration &connect_timeout);

  // 通过连接到|host|和|service启动HTTP/2会话|
  // （例如，“443”）使用带有连接的加密SSL/TLS连接
  // 超时60秒。
  session(boost::asio::io_service &io_service,
          boost::asio::ssl::context &tls_context, const std::string &host,
          const std::string &service);

  // 通过连接到|host|和|service启动HTTP/2会话|
  // （例如，“443”）使用加密的SSL/TLS连接
  // 连接超时。
  session(boost::asio::io_service &io_service,
          boost::asio::ssl::context &tls_context, const std::string &host,
          const std::string &service,
          const boost::posix_time::time_duration &connect_timeout);

  ~session();

  session(session &&other) noexcept;
  session &operator=(session &&other) noexcept;

  // 设置连接建立后调用的回调。
  void on_connect(connect_cb cb) const;

  // 设置在连接级别错误时调用的回调
  // 并且会话被终止。
  void on_error(error_cb cb) const;

  // 设置读取超时，默认为60秒。
  void read_timeout(const boost::posix_time::time_duration &t);

  // 关闭连接。
  void shutdown() const;

  // 返回基础io_service对象。
  boost::asio::io_service &io_service() const;

  // 使用|method|（例如，“GET”），|uri向服务器提交请求|
  // （例如，“http://localhost/“）和可选的附加标题
  // 领域。如果请求对象
  // 成功，或nullptr和|ec|包含错误消息。
  const request *submit(boost::system::error_code &ec,
                        const std::string &method, const std::string &uri,
                        header_map h = header_map{},
                        priority_spec prio = priority_spec()) const;

  // 使用|method|（例如，“GET”），|uri向服务器提交请求|
  // （例如，“http://localhost/“）和可选的附加标题
  // 领域。|data|是请求正文。此函数返回
  // 如果成功，则指向请求对象的指针，或nullptr和|ec|
  // 包含错误消息。
  const request *submit(boost::system::error_code &ec,
                        const std::string &method, const std::string &uri,
                        std::string data, header_map h = header_map{},
                        priority_spec prio = priority_spec()) const;

  // 使用|method|（例如，“GET”），|uri向服务器提交请求|
  // （例如，“http://localhost/“）和可选的附加标题
  // 领域。|cb|用于生成请求体。这
  // 如果成功，函数将返回指向请求对象的指针，或者
  // nullptr和|ec|包含错误消息。
  const request *submit(boost::system::error_code &ec,
                        const std::string &method, const std::string &uri,
                        generator_cb cb, header_map h = header_map{},
                        priority_spec prio = priority_spec()) const;

private:
  std::shared_ptr<session_impl> impl_;
};

// 配置|tls_ctx|以供客户端使用。目前，我们刚刚设置NPN
// HTTP/2的回调。
boost::system::error_code
configure_tls_context(boost::system::error_code &ec,
                      boost::asio::ssl::context &tls_ctx);

} // 命名空间客户端

} // 命名空间asio_http2

} // 命名空间nghttp2

#endif // ASIO_HTTP2_CLIENT_H

