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
#ifndef SHRPX_UPSTREAM_H
#define SHRPX_UPSTREAM_H

#include "shrpx.h"
#include "shrpx_io_control.h"
#include "memchunk.h"

using namespace nghttp2;

namespace shrpx {

class ClientHandler;
class Downstream;
class DownstreamConnection;

class Upstream {
public:
  virtual ~Upstream() {}
  virtual int on_read() = 0;
  virtual int on_write() = 0;
  virtual int on_timeout(Downstream *downstream) { return 0; };
  virtual int on_downstream_abort_request(Downstream *downstream,
                                          unsigned int status_code) = 0;
  // 当当前请求被中止而不转发时调用
  // 到后端，并且应该重定向到https URI。
  virtual int
  on_downstream_abort_request_with_https_redirect(Downstream *downstream) = 0;
  virtual int downstream_read(DownstreamConnection *dconn) = 0;
  virtual int downstream_write(DownstreamConnection *dconn) = 0;
  virtual int downstream_eof(DownstreamConnection *dconn) = 0;
  virtual int downstream_error(DownstreamConnection *dconn, int events) = 0;
  virtual ClientHandler *get_client_handler() const = 0;

  virtual int on_downstream_header_complete(Downstream *downstream) = 0;
  virtual int on_downstream_body(Downstream *downstream, const uint8_t *data,
                                 size_t len, bool flush) = 0;
  virtual int on_downstream_body_complete(Downstream *downstream) = 0;

  virtual void on_handler_delete() = 0;
  // 在重置|downstream|的下游连接时调用。
  // 目前，这仅由Http2Session使用。如果|no_retry|为
  // true，另一次尝试使用新的DownstreamConnection
  // 不允许。
  virtual int on_downstream_reset(Downstream *downstream, bool no_retry) = 0;

  virtual void pause_read(IOCtrlReason reason) = 0;
  virtual int resume_read(IOCtrlReason reason, Downstream *downstream,
                          size_t consumed) = 0;
  virtual int send_reply(Downstream *downstream, const uint8_t *body,
                         size_t bodylen) = 0;

  // 启动服务器推送。|下游|是的关联流
  // 推送的资源。如果成功，此函数返回0，
  // 否则为-1。
  virtual int initiate_push(Downstream *downstream, const StringRef &uri) = 0;

  // 在容量为|iovcnt|的|iov|中填充响应数据。退换商品
  // 注入的iov数量。
  virtual int response_riovec(struct iovec *iov, int iovcnt) const = 0;
  virtual void response_drain(size_t n) = 0;
  virtual bool response_empty() const = 0;

  // 在下游启动PUSH_PROMISE时调用。这个
  // 关联的下游被给出为|downstream|。承诺的
  // 流ID为|promised_stream_ID|。如果上游支持
  // 服务器推送相应的上游连接，它应该
  // return推送流的下游对象。否则，返回
  // 空指针。
  virtual Downstream *
  on_downstream_push_promise(Downstream *downstream,
                             int32_t promised_stream_id) = 0;
  // 在中完全接收到PUSH_PROMISE帧时调用
  // 下游的关联的下游表示为|下游|。
  // 如果成功，此函数将返回0，或者返回-1。
  virtual int
  on_downstream_push_promise_complete(Downstream *downstream,
                                      Downstream *promised_downstream) = 0;
  // 如果在上游连接中启用了服务器推送，则返回true。
  virtual bool push_enabled() const = 0;
  // 下游承诺取消。当
  // |promised_downtown|的PUSH_PROMISE未提交给
  // 上游会话。
  virtual void cancel_premature_downstream(Downstream *promised_downstream) = 0;
};

} // 命名空间shrpx

#endif // SHRPX_UPSTREAM_H

