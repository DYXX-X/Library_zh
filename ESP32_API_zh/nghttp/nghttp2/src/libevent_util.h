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
#ifndef LIBEVENT_UTIL_H
#define LIBEVENT_UTIL_H

#include "nghttp2_config.h"

#include <event2/buffer.h>
#include <event2/bufferevent.h>

namespace nghttp2 {

namespace util {

class EvbufferBuffer {
public:
  EvbufferBuffer();
  // 如果|limit |不是-1，则最多为min（limit，bufmax）大小字节
  // 添加到evbuffer_。
  EvbufferBuffer(evbuffer *evbuffer, uint8_t *buf, size_t bufmax,
                 ssize_t limit = -1);
  ~EvbufferBuffer();
  void reset(evbuffer *evbuffer, uint8_t *buf, size_t bufmax,
             ssize_t limit = -1);
  int flush();
  int add(const uint8_t *data, size_t datalen);
  size_t get_buflen() const;
  int write_buffer();
  // 返回到目前为止写入evbuffer_的字节数。重置（）
  // 将此值重置为0。
  size_t get_writelen() const;

private:
  evbuffer *evbuffer_;
  evbuffer *bucket_;
  uint8_t *buf_;
  size_t bufmax_;
  size_t buflen_;
  ssize_t limit_;
  size_t writelen_;
};

// 提供这些函数是为了减少epoll_ctl系统调用。避免
// 调用bufferevent_enable/disable（），除非
// 嗅探当前启用的事件。
void bev_enable_unless(bufferevent *bev, int events);
void bev_disable_unless(bufferevent *bev, int events);

} // 命名空间util

} // 命名空间nghttp2

#endif // LIBEVENT_UTIL_H

