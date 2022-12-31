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
#ifndef APP_HELPER_H
#define APP_HELPER_H

#include "nghttp2_config.h"

#include <cinttypes>
#include <cstdlib>
#ifdef HAVE_SYS_TIME_H
#  include <sys/time.h>
#endif // HAVE_SYS_TIME_H
#include <poll.h>

#include <map>
#include <chrono>

#include <nghttp2/nghttp2.h>

namespace nghttp2 {

int verbose_on_header_callback(nghttp2_session *session,
                               const nghttp2_frame *frame, const uint8_t *name,
                               size_t namelen, const uint8_t *value,
                               size_t valuelen, uint8_t flags, void *user_data);

int verbose_on_frame_recv_callback(nghttp2_session *session,
                                   const nghttp2_frame *frame, void *user_data);

int verbose_on_invalid_frame_recv_callback(nghttp2_session *session,
                                           const nghttp2_frame *frame,
                                           int lib_error_code, void *user_data);

int verbose_on_frame_send_callback(nghttp2_session *session,
                                   const nghttp2_frame *frame, void *user_data);

int verbose_on_data_chunk_recv_callback(nghttp2_session *session, uint8_t flags,
                                        int32_t stream_id, const uint8_t *data,
                                        size_t len, void *user_data);

int verbose_error_callback(nghttp2_session *session, int lib_error_code,
                           const char *msg, size_t len, void *user_data);

// 返回|a|和|b|之间的差（以毫秒为单位），假设
// |a|比|b|更近。
template <typename TimePoint>
std::chrono::milliseconds time_delta(const TimePoint &a, const TimePoint &b) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(a - b);
}

// 重置计时器
void reset_timer();

// 返回计时器重置后的持续时间。
std::chrono::milliseconds get_timer();

// 返回当前时间点。
std::chrono::steady_clock::time_point get_time();

void print_timer();

// 设置为true将打印带有ANSI颜色转义码的字符
// 当打印HTTP2帧时。此函数更改静态
// 变量
void set_color_output(bool f);

// 打印HTTP2帧时设置输出文件。默认情况下，stdout为
// 习惯于
void set_output(FILE *file);

ssize_t deflate_data(uint8_t *out, size_t outlen, const uint8_t *in,
                     size_t inlen);

} // 命名空间nghttp2

#endif // APP_HELPER_H

