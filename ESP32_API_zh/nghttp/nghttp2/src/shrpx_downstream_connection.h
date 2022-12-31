/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2012 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SHRPX_DOWNSTREAM_CONNECTION_H
#define SHRPX_DOWNSTREAM_CONNECTION_H

#include "shrpx.h"

#include <memory>

#include "shrpx_io_control.h"

namespace shrpx {

class ClientHandler;
class Upstream;
class Downstream;
struct DownstreamAddrGroup;
struct DownstreamAddr;

class DownstreamConnection {
public:
  DownstreamConnection();
  virtual ~DownstreamConnection();
  virtual int attach_downstream(Downstream *downstream) = 0;
  virtual void detach_downstream(Downstream *downstream) = 0;

  virtual int push_request_headers() = 0;
  virtual int push_upload_data_chunk(const uint8_t *data, size_t datalen) = 0;
  virtual int end_upload_data() = 0;

  virtual void pause_read(IOCtrlReason reason) = 0;
  virtual int resume_read(IOCtrlReason reason, size_t consumed) = 0;
  virtual void force_resume_read() = 0;

  virtual int on_read() = 0;
  virtual int on_write() = 0;
  virtual int on_timeout() { return 0; }

  virtual void on_upstream_change(Upstream *uptream) = 0;

  // 如果此对象可池化，则为true。
  virtual bool poolable() const = 0;

  virtual const std::shared_ptr<DownstreamAddrGroup> &
  get_downstream_addr_group() const = 0;
  virtual DownstreamAddr *get_addr() const = 0;

  void set_client_handler(ClientHandler *client_handler);
  ClientHandler *get_client_handler();
  Downstream *get_downstream();

protected:
  ClientHandler *client_handler_;
  Downstream *downstream_;
};

} // 命名空间shrpx

#endif // SHRPX_DOWNSTREAM_CONNECTION_H

