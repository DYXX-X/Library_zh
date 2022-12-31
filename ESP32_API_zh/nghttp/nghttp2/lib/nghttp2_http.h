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
#ifndef NGHTTP2_HTTP_H
#define NGHTTP2_HTTP_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>
#include "nghttp2_session.h"
#include "nghttp2_stream.h"

/*
 * 当为|stream|接收到|frame |中的HTTP头字段|nv|时，调用此函数。此函数将根据流的当前状态验证|nv|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_HTTP_HEADER接收到无效的HTTP标头字段。NGHTTP2_ERR_IGN_HTTP_HEADER接收到无效的HTTP标头字段，但由于兼容性原因，可以将其视为未接收到。
 */
int nghttp2_http_on_header(nghttp2_session *session, nghttp2_stream *stream,
                           nghttp2_frame *frame, nghttp2_hd_nv *nv,
                           int trailer);

/*
 * 当接收到请求标头时调用此函数。此函数执行验证，如果成功则返回0，或-1。
 */
int nghttp2_http_on_request_headers(nghttp2_stream *stream,
                                    nghttp2_frame *frame);

/*
 * 收到响应标头时调用此函数。此函数执行验证，如果成功则返回0，或-1。
 */
int nghttp2_http_on_response_headers(nghttp2_stream *stream);

/*
 * 此函数称为尾部标头（用于请求和响应）。此函数执行验证，如果成功则返回0，或-1。
 */
int nghttp2_http_on_trailer_headers(nghttp2_stream *stream,
                                    nghttp2_frame *frame);

/*
 * 当传入帧中出现END_STREAM标志时，调用此函数。此函数执行验证，如果成功则返回0，或-1。
 */
int nghttp2_http_on_remote_end_stream(nghttp2_stream *stream);

/*
 * 当接收到数据块时调用此函数。此函数执行验证，如果成功则返回0，或-1。
 */
int nghttp2_http_on_data_chunk(nghttp2_stream *stream, size_t n);

/*
 * 此函数检查|frame |中的头字段，并将其方法记录在stream->http_flags中。如果帧->hd。类型既不是NGHTTP2_HEADERS也不是NGHTTP2_PUSH_PROMISE，此函数不执行任何操作。
 */
void nghttp2_http_record_request_method(nghttp2_stream *stream,
                                        nghttp2_frame *frame);

#endif /* NGHTTP2_HTTP_H */

