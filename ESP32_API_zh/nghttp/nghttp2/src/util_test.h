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
#ifndef UTIL_TEST_H
#define UTIL_TEST_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif // HAVE_CONFIG_H

namespace shrpx {

void test_util_streq(void);
void test_util_strieq(void);
void test_util_inp_strlower(void);
void test_util_to_base64(void);
void test_util_to_token68(void);
void test_util_percent_encode_token(void);
void test_util_percent_encode_path(void);
void test_util_percent_decode(void);
void test_util_quote_string(void);
void test_util_utox(void);
void test_util_http_date(void);
void test_util_select_h2(void);
void test_util_ipv6_numeric_addr(void);
void test_util_utos(void);
void test_util_make_string_ref_uint(void);
void test_util_utos_unit(void);
void test_util_utos_funit(void);
void test_util_parse_uint_with_unit(void);
void test_util_parse_uint(void);
void test_util_parse_duration_with_unit(void);
void test_util_duration_str(void);
void test_util_format_duration(void);
void test_util_starts_with(void);
void test_util_ends_with(void);
void test_util_parse_http_date(void);
void test_util_localtime_date(void);
void test_util_get_uint64(void);
void test_util_parse_config_str_list(void);
void test_util_make_http_hostport(void);
void test_util_make_hostport(void);
void test_util_strifind(void);
void test_util_random_alpha_digit(void);
void test_util_format_hex(void);
void test_util_is_hex_string(void);
void test_util_decode_hex(void);
void test_util_extract_host(void);
void test_util_split_hostport(void);

} // 命名空间shrpx

#endif // UTIL_TEST_H

