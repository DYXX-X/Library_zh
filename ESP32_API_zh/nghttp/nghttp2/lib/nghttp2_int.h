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
#ifndef NGHTTP2_INT_H
#define NGHTTP2_INT_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>

/* 内部使用的宏、类型和常量*/

/* “less”函数，如果|lhs|小于|rhs|，则返回非零。*/
typedef int (*nghttp2_less)(const void *lhs, const void *rhs);

/* 内部错误代码。它们必须在[-499，-100]的范围内（含）。*/
typedef enum {
  NGHTTP2_ERR_CREDENTIAL_PENDING = -101,
  NGHTTP2_ERR_IGN_HEADER_BLOCK = -103,
  NGHTTP2_ERR_IGN_PAYLOAD = -104,
  /*
   * 收到了无效的HTTP标头字段，但由于兼容性原因，可以将其视为未收到。
   */
  NGHTTP2_ERR_IGN_HTTP_HEADER = -105,
  /*
   * 接收到无效的HTTP标头字段，该字段被忽略。与NGHTTP2_ERR_IGN_HTTP_HEADER不同，这不会调用NGHTTP2_on_invalid_HEADER_callback。
   */
  NGHTTP2_ERR_REMOVE_HTTP_HEADER = -106
} nghttp2_internal_error;

#endif /* NGHTTP2_INT_H */

