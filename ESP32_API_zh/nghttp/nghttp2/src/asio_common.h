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
#ifndef ASIO_COMMON_H
#define ASIO_COMMON_H

#include "nghttp2_config.h"

#include <string>

#include <nghttp2/asio_http2.h>

#include "util.h"

namespace nghttp2 {

namespace asio_http2 {

boost::system::error_code make_error_code(nghttp2_error ev);

boost::system::error_code make_error_code(nghttp2_asio_error ev);

generator_cb string_generator(std::string data);

// 返回generator_cb，它只返回NGHTTP2_ERR_DEFERRED
generator_cb deferred_generator();

template <typename InputIt>
void split_path(uri_ref &dst, InputIt first, InputIt last) {
  auto path_last = std::find(first, last, '?');
  InputIt query_first;
  if (path_last == last) {
    query_first = path_last = last;
  } else {
    query_first = path_last + 1;
  }
  dst.path = util::percent_decode(first, path_last);
  dst.raw_path.assign(first, path_last);
  dst.raw_query.assign(query_first, last);
}

using boost::asio::ip::tcp;

using ssl_socket = boost::asio::ssl::stream<tcp::socket>;

bool tls_h2_negotiated(ssl_socket &socket);

} // 命名空间asio_http2

} // 命名空间nghttp2

#endif // ASIO_COMMON_H

