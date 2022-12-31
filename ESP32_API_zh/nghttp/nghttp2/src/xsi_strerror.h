/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2016 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef XSI_STRERROR_H
#define XSI_STRERROR_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus公司*/

/* 看起来错误消息很小，但我们真的不知道它们会持续多久。*/
#define STRERROR_BUFSIZE 256

/*
 * 返回由|errnum|表示的错误说明。描述以|buf|形式编写，长度|buflen|，包括终端NULL。如果出现错误，包括缓冲区空间不足以包含错误消息，并且|buflen|>0，则将空字符串写入|buf|。此函数返回|buf|。
 */
char *xsi_strerror(int errnum, char *buf, size_t buflen);

#ifdef __cplusplus
}
#endif /* __cplusplus公司*/

#endif /* XSI_STRERROR_H */

