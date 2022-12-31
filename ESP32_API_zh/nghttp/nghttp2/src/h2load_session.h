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
#ifndef H2LOAD_SESSION_H
#define H2LOAD_SESSION_H

#include "nghttp2_config.h"

#include <sys/types.h>

#include <cinttypes>

#include "h2load.h"

namespace h2load {

class Session {
public:
  virtual ~Session() {}
  // 在建立连接时调用。
  virtual void on_connect() = 0;
  // 当必须发出一个请求时调用。
  virtual int submit_request() = 0;
  // 当传入字节可用时调用。子类必须
  // 返回读取的字节数。
  virtual int on_read(const uint8_t *data, size_t len) = 0;
  // 当写入可用时调用。成功时返回0，否则
  // 返回-1。
  virtual int on_write() = 0;
  // 在必须终止基础会话时调用。
  virtual void terminate() = 0;
  // 返回每个连接的最大并发数
  virtual size_t max_concurrent_streams() = 0;
};

} // 命名空间h2load

#endif // H2LOAD_SESSION_H

