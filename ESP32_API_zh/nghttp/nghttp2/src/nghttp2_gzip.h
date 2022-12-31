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
#ifndef NGHTTP2_GZIP_H

#  ifdef HAVE_CONFIG_H
#    include <config.h>
#  endif /* HAVE_CONFIG_H */
#  include <zlib.h>

#  include <nghttp2/nghttp2.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * @struct
 *
 * 用于膨胀数据的gzip流。
 */
typedef struct {
  z_stream zst;
  int8_t finished;
} nghttp2_gzip;

/**
 * @function
 *
 * 一个助手函数，用于设置每个请求的gzip流以膨胀数据。
 *
 * 如果成功，此函数将返回0，或者返回-1。
 */
int nghttp2_gzip_inflate_new(nghttp2_gzip **inflater_ptr);

/**
 * @function
 *
 * 释放充气流。|充气机|可能为“NULL”。
 */
void nghttp2_gzip_inflate_del(nghttp2_gzip *inflater);

/**
 * @function
 *
 * 用长度|*inlen_ptr|对|in|中的数据进行膨胀，并将膨胀后的数据存储到|out|中，该数据至少分配了|outeen_ptr|的大小。返回时，|outlen_ptr|将更新为表示写入|out|的数据数。类似地，|inlen_ptr|更新为表示处理的输入字节数。
 *
 * 如果成功，此函数将返回0，或者返回-1。
 *
 * 示例如下：
 *
 *     void on_data_chunk_recv_callback（nghttp2_session*会话，uint8_t标志，int32_t stream_id，const uint8_t数据，size_t len，void user_data）{…req=nghttp2_session_get_stream_user_data（会话，stream_id）；nghttp2_gzip充气器=req->充气器；而（len>0）{uint8_ out[MAX_OUTLEN]；size_t OUTLEN=MAX_OUTLEN；size_tlen=len；int rv；rv=nghttp 2_gzip膨胀器（充气机，输出，输出，数据，输出）；如果（rv！=0）｛nghttp2_submit_rst_stream（session，stream_id，nghttp2_INTERNAL_ERROR）；break；｝。。。做些什么…data+=tlen；len-=tlen；｝…..｝
 */
int nghttp2_gzip_inflate(nghttp2_gzip *inflater, uint8_t *out,
                         size_t *outlen_ptr, const uint8_t *in,
                         size_t *inlen_ptr);

/**
 * @function
 *
 * 如果|充气器|看到放气流的结尾，则返回非零。此函数返回非零后，带有|inflater|的“nghttp2_gzip_ginflate（）”将返回错误。
 */
int nghttp2_gzip_inflate_finished(nghttp2_gzip *inflater);

#  ifdef __cplusplus
}
#  endif

#endif /* NGHTTP2_GZIP_H */

