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
#ifndef NGHTTP2_PRIORITY_SPEC_H
#define NGHTTP2_PRIORITY_SPEC_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>

/*
 * 如果pri_spec->weight超出范围，此函数将其标准化。如果pri_spec->weight小于NGHTTP2_MIN_weight，则将其设置为NGHTTP2_MIN_weight。如果pri_spec->weight大于NGHTTP2_MAX_weight，则将其设置为NGHTTP2_MAX_weight。
 */
void nghttp2_priority_spec_normalize_weight(nghttp2_priority_spec *pri_spec);

#endif /* NGHTTP2_PRIORITY_SPEC_H */

