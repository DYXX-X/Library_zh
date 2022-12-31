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
#ifndef SHRPX_HTTPS_UPSTREAM_H
#define SHRPX_HTTPS_UPSTREAM_H

#include "shrpx.h"

#include <cinttypes>
#include <memory>

#include "llhttp.h"

#include "shrpx_upstream.h"
#include "memchunk.h"

using namespace nghttp2;

namespace shrpx {

class ClientHandler;

class HttpsUpstream : public Upstream {
public:
  HttpsUpstream(ClientHandler *handler);
  virtual ~HttpsUpstream();
  virtual int on_read();
  virtual int on_write();
  virtual int on_event();
  virtual int on_downstream_abort_request(Downstream *downstream,
                                          unsigned int status_code);
  virtual int
  on_downstream_abort_request_with_https_redirect(Downstream *downstream);
  virtual ClientHandler *get_client_handler() const;

  virtual int downstream_read(DownstreamConnection *dconn);
  virtual int downstream_write(DownstreamConnection *dconn);
  virtual int downstream_eof(DownstreamConnection *dconn);
  virtual int downstream_error(DownstreamConnection *dconn, int events);

  void attach_downstream(std::unique_ptr<Downstream> downstream);
  void delete_downstream();
  Downstream *get_downstream() const;
  std::unique_ptr<Downstream> pop_downstream();
  void error_reply(unsigned int status_code);

  virtual void pause_read(IOCtrlReason reason);
  virtual int resume_read(IOCtrlReason reason, Downstream *downstream,
                          size_t consumed);

  virtual int on_downstream_header_complete(Downstream *downstream);
  virtual int on_downstream_body(Downstream *downstream, const uint8_t *data,
                                 size_t len, bool flush);
  virtual int on_downstream_body_complete(Downstream *downstream);

  virtual void on_handler_delete();
  virtual int on_downstream_reset(Downstream *downstream, bool no_retry);
  virtual int send_reply(Downstream *downstream, const uint8_t *body,
                         size_t bodylen);
  virtual int initiate_push(Downstream *downstream, const StringRef &uri);
  virtual int response_riovec(struct iovec *iov, int iovcnt) const;
  virtual void response_drain(size_t n);
  virtual bool response_empty() const;

  virtual Downstream *on_downstream_push_promise(Downstream *downstream,
                                                 int32_t promised_stream_id);
  virtual int
  on_downstream_push_promise_complete(Downstream *downstream,
                                      Downstream *promised_downstream);
  virtual bool push_enabled() const;
  virtual void cancel_premature_downstream(Downstream *promised_downstream);

  void reset_current_header_length();
  void log_response_headers(DefaultMemchunks *buf) const;
  int redirect_to_https(Downstream *downstream);

  // 在新请求开始时调用。
  void on_start_request();

private:
  ClientHandler *handler_;
  llhttp_t htp_;
  size_t current_header_length_;
  std::unique_ptr<Downstream> downstream_;
  IOControl ioctrl_;
  // 到目前为止看到的请求数。
  size_t num_requests_;
};

} // 命名空间shrpx

#endif // SHRPX_HTTPS_UPSTREAM_H

