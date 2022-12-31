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
#ifndef SHRPX_HTTP2_DOWNSTREAM_CONNECTION_H
#define SHRPX_HTTP2_DOWNSTREAM_CONNECTION_H

#include "shrpx.h"

#include <openssl/ssl.h>

#include <nghttp2/nghttp2.h>

#include "shrpx_downstream_connection.h"

namespace shrpx {

struct StreamData;
class Http2Session;
class DownstreamConnectionPool;

class Http2DownstreamConnection : public DownstreamConnection {
public:
  Http2DownstreamConnection(Http2Session *http2session);
  virtual ~Http2DownstreamConnection();
  virtual int attach_downstream(Downstream *downstream);
  virtual void detach_downstream(Downstream *downstream);

  virtual int push_request_headers();
  virtual int push_upload_data_chunk(const uint8_t *data, size_t datalen);
  virtual int end_upload_data();

  virtual void pause_read(IOCtrlReason reason) {}
  virtual int resume_read(IOCtrlReason reason, size_t consumed);
  virtual void force_resume_read() {}

  virtual int on_read();
  virtual int on_write();
  virtual int on_timeout();

  virtual void on_upstream_change(Upstream *upstream) {}

  // 此对象不可池化，因为我们没有设施
  // 迁移到另一个Http2Session对象。
  virtual bool poolable() const { return false; }

  virtual const std::shared_ptr<DownstreamAddrGroup> &
  get_downstream_addr_group() const;
  virtual DownstreamAddr *get_addr() const;

  int send();

  void attach_stream_data(StreamData *sd);
  StreamData *detach_stream_data();

  int submit_rst_stream(Downstream *downstream,
                        uint32_t error_code = NGHTTP2_INTERNAL_ERROR);

  Http2DownstreamConnection *dlnext, *dlprev;

private:
  Http2Session *http2session_;
  StreamData *sd_;
};

} // 命名空间shrpx

#endif // SHRPX_HTTP2_DOWNSTREAM_CONNECTION_H

