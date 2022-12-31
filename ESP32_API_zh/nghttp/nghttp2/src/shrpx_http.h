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
#ifndef SHRPX_HTTP_H
#define SHRPX_HTTP_H

#include "shrpx.h"

#include <string>

#include <nghttp2/nghttp2.h>

#include "shrpx_config.h"
#include "util.h"
#include "allocator.h"

using namespace nghttp2;

namespace shrpx {

namespace http {

StringRef create_error_html(BlockAllocator &balloc, unsigned int status_code);

template <typename OutputIt>
OutputIt create_via_header_value(OutputIt dst, int major, int minor) {
  *dst++ = static_cast<char>(major + '0');
  if (major < 2) {
    *dst++ = '.';
    *dst++ = static_cast<char>(minor + '0');
  }
  return util::copy_lit(dst, " nghttpx");
}

// 返回生成的RFC 7239转发的标头字段值。这个
// |params |是shrpx_forwarded_param的0或更多的位或
// 在shrpx_config.h中定义。
StringRef create_forwarded(BlockAllocator &balloc, int params,
                           const StringRef &node_by, const StringRef &node_for,
                           const StringRef &host, const StringRef &proto);

// 将ANSI颜色代码添加到HTTP标头|hdrs|。
std::string colorizeHeaders(const char *hdrs);

ssize_t select_padding_callback(nghttp2_session *session,
                                const nghttp2_frame *frame, size_t max_payload,
                                void *user_data);

// 为基于cookie的相关性创建集合cookie字符串。如果|路径|是
// 不为空，则添加“；<path>”。如果|secure|为true，则“；secure”为
// 补充。
StringRef create_affinity_cookie(BlockAllocator &balloc, const StringRef &name,
                                 uint32_t affinity_cookie,
                                 const StringRef &path, bool secure);

// 如果|secure|指示secure属性应为
// 设置
bool require_cookie_secure_attribute(SessionAffinityCookieSecure secure,
                                     const StringRef &scheme);

} // 命名空间http

} // 命名空间shrpx

#endif // SHRPX_HTTP_H

