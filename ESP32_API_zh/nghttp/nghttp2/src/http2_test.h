/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2013 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SHRPX_HTTP2_TEST_H
#define SHRPX_HTTP2_TEST_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif // HAVE_CONFIG_H

namespace shrpx {

void test_http2_add_header(void);
void test_http2_get_header(void);
void test_http2_copy_headers_to_nva(void);
void test_http2_build_http1_headers_from_headers(void);
void test_http2_lws(void);
void test_http2_rewrite_location_uri(void);
void test_http2_parse_http_status_code(void);
void test_http2_index_header(void);
void test_http2_lookup_token(void);
void test_http2_parse_link_header(void);
void test_http2_path_join(void);
void test_http2_normalize_path(void);
void test_http2_rewrite_clean_path(void);
void test_http2_get_pure_path_component(void);
void test_http2_construct_push_component(void);
void test_http2_contains_trailers(void);

} // 命名空间shrpx

#endif // SHRPX_HTTP2_TEST_H

