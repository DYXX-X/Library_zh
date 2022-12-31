/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2016 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SHRPX_API_DOWNSTREAM_CONNECTION_H
#define SHRPX_API_DOWNSTREAM_CONNECTION_H

#include "shrpx_downstream_connection.h"
#include "template.h"

using namespace nghttp2;

namespace shrpx {

class Worker;

// 如果添加了新方法，请不要忘记将API_method_STRING更新为
// 好
enum APIMethod {
  API_METHOD_GET,
  API_METHOD_POST,
  API_METHOD_PUT,
  API_METHOD_MAX,
};

// API状态代码，它独立于HTTP状态代码。但是
// 通常，2xx代码表示SUCCESS，否则表示FAILURE。
enum class APIStatusCode {
  SUCCESS,
  FAILURE,
};

class APIDownstreamConnection;

struct APIEndpoint {
  // 终结点路径。它必须以“/api/”开头。
  StringRef path;
  // 如果我们评估请求主体，则为true。
  bool require_body;
  // 允许的方法。这是（1）中的一个或多个的位或<<
  // APIMethod值）。
  uint8_t allowed_methods;
  std::function<int(APIDownstreamConnection &)> handler;
};

class APIDownstreamConnection : public DownstreamConnection {
public:
  APIDownstreamConnection(Worker *worker);
  virtual ~APIDownstreamConnection();
  virtual int attach_downstream(Downstream *downstream);
  virtual void detach_downstream(Downstream *downstream);

  virtual int push_request_headers();
  virtual int push_upload_data_chunk(const uint8_t *data, size_t datalen);
  virtual int end_upload_data();

  virtual void pause_read(IOCtrlReason reason);
  virtual int resume_read(IOCtrlReason reason, size_t consumed);
  virtual void force_resume_read();

  virtual int on_read();
  virtual int on_write();

  virtual void on_upstream_change(Upstream *uptream);

  // 如果此对象可池化，则为true。
  virtual bool poolable() const;

  virtual const std::shared_ptr<DownstreamAddrGroup> &
  get_downstream_addr_group() const;
  virtual DownstreamAddr *get_addr() const;

  int send_reply(unsigned int http_status, APIStatusCode api_status,
                 const StringRef &data = StringRef{});
  int error_method_not_allowed();

  // 处理backendconfig API请求。
  int handle_backendconfig();
  // 处理configrevision API请求。
  int handle_configrevision();

private:
  Worker *worker_;
  // 这指向请求的APIEndpoint结构。
  const APIEndpoint *api_;
  // 用于存储请求主体的临时文件的文件描述符。
  int fd_;
  // 如果我们停止阅读请求正文，则为true。
  bool shutdown_read_;
};

} // 命名空间shrpx

#endif // SHRPX_API_DOWNSTREAM_CONNECTION_H

