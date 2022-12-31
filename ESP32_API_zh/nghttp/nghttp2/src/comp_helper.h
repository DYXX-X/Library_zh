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
#ifndef NGHTTP2_COMP_HELPER_H
#define NGHTTP2_COMP_HELPER_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <jansson.h>

#include <nghttp2/nghttp2.h>

#ifdef __cplusplus
extern "C" {
#endif

json_t *dump_deflate_header_table(nghttp2_hd_deflater *deflater);

json_t *dump_inflate_header_table(nghttp2_hd_inflater *inflater);

json_t *dump_header(const uint8_t *name, size_t namelen, const uint8_t *value,
                    size_t vlauelen);

json_t *dump_headers(const nghttp2_nv *nva, size_t nvlen);

void output_json_header(void);

void output_json_footer(void);

#ifdef __cplusplus
}
#endif

#endif /* NGHTTP2_COMP_HELPER_H */

