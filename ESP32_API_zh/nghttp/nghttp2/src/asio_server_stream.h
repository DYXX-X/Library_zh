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
#ifndef ASIO_SERVER_STREAM_H
#define ASIO_SERVER_STREAM_H

#include "nghttp2_config.h"

#include <nghttp2/asio_http2_server.h>

namespace nghttp2 {
namespace asio_http2 {
namespace server {

class http2_handler;

class stream {
public:
  stream(http2_handler *h, int32_t stream_id);

  int32_t get_stream_id() const;
  class request &request();
  class response &response();

  http2_handler *handler() const;

private:
  http2_handler *handler_;
  class request request_;
  class response response_;
  int32_t stream_id_;
};

} // 命名空间服务器
} // 命名空间asio_http2
} // 命名空间nghttp2

#endif // ASIO_SERVER_STREAM_H

