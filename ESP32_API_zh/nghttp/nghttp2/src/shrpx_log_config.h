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
#ifndef SHRPX_LOG_CONFIG_H
#define SHRPX_LOG_CONFIG_H

#include "shrpx.h"

#include <sys/types.h>

#include <chrono>

#include "template.h"

using namespace nghttp2;

namespace shrpx {

struct Timestamp {
  Timestamp(const std::chrono::system_clock::time_point &tp);

  std::array<char, sizeof("03/Jul/2014:00:19:38 +0900")> time_local_buf;
  std::array<char, sizeof("2014-11-15T12:58:24.741+09:00")> time_iso8601_buf;
  std::array<char, sizeof("Mon, 10 Oct 2016 10:25:58 GMT")> time_http_buf;
  StringRef time_local;
  StringRef time_iso8601;
  StringRef time_http;
};

struct LogConfig {
  std::chrono::system_clock::time_point time_str_updated;
  std::shared_ptr<Timestamp> tstamp;
  std::string thread_id;
  pid_t pid;
  int accesslog_fd;
  int errorlog_fd;
  // 如果errorlog_fd是指终端，则为true。
  bool errorlog_tty;

  LogConfig();
  // 如果time_str_updated和now之间存在差异，则更新时间戳
  // 为1毫秒或更长。
  void update_tstamp_millis(const std::chrono::system_clock::time_point &now);
  // 如果time_str_updated和
  // 现在，转换为timet是1秒或更多秒。
  void update_tstamp(const std::chrono::system_clock::time_point &now);
};

// 我们需要每个线程的LogConfig，以避免打开文件时的数据竞争
// 日志文件的描述符。
LogConfig *log_config();

// 删除log_config
void delete_log_config();

} // 命名空间shrpx

#endif // SHRPX_LOG_CONFIG_H

