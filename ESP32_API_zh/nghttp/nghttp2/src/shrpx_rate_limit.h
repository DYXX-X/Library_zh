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
#ifndef SHRPX_RATE_LIMIT_H
#define SHRPX_RATE_LIMIT_H

#include "shrpx.h"

#include <ev.h>

#include <openssl/ssl.h>

namespace shrpx {

struct Connection;

class RateLimit {
public:
  // 我们需要|conn|对象来检查它是否有TLS的未读字节
  // 联系
  RateLimit(struct ev_loop *loop, ev_io *w, size_t rate, size_t burst,
            Connection *conn = nullptr);
  ~RateLimit();
  size_t avail() const;
  void drain(size_t n);
  void regen();
  void startw();
  void stopw();
  // 如果conn_->tls对象包含未读字节，则返回事件。这是
  // 需要，因为它缓冲在conn->tls对象中，io事件是
  // 除非接收到新的输入数据，否则不生成。
  void handle_tls_pending_read();

private:
  ev_timer t_;
  ev_io *w_;
  struct ev_loop *loop_;
  Connection *conn_;
  size_t rate_;
  size_t burst_;
  size_t avail_;
  bool startw_req_;
};

} // 命名空间shrpx

#endif // SHRPX_RATE_LIMIT_H

