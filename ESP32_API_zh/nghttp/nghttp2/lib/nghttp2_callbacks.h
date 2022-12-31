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
#ifndef NGHTTP2_CALLBACKS_H
#define NGHTTP2_CALLBACKS_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>

/*
 * 回调函数。
 */
struct nghttp2_session_callbacks {
  /**
   * 当会话希望向远程对等方发送数据时调用回调函数。如果应用程序仅使用“nghttp2_session_mmem_send（）”来序列化要传输的数据，则不需要此回调。
   */
  nghttp2_send_callback send_callback;
  /**
   * 当会话希望从远程对等端接收数据时调用回调函数。如果应用程序仅使用“nghttp2_session_mem_recv（）”来处理接收的数据，则不需要此回调。
   */
  nghttp2_recv_callback recv_callback;
  /**
   * 当接收到帧时，“nghttp2_session_recv（）”调用回调函数。
   */
  nghttp2_on_frame_recv_callback on_frame_recv_callback;
  /**
   * 当接收到无效的非DATA帧时，“nghttp2_session_recv（）”调用回调函数。
   */
  nghttp2_on_invalid_frame_recv_callback on_invalid_frame_recv_callback;
  /**
   * 收到data帧中的数据块时调用回调函数。
   */
  nghttp2_on_data_chunk_recv_callback on_data_chunk_recv_callback;
  /**
   * 在发送非DATA帧之前调用回调函数。
   */
  nghttp2_before_frame_send_callback before_frame_send_callback;
  /**
   * 发送帧后调用回调函数。
   */
  nghttp2_on_frame_send_callback on_frame_send_callback;
  /**
   * 由于错误而未发送非DATA帧时调用的回调函数。
   */
  nghttp2_on_frame_not_send_callback on_frame_not_send_callback;
  /**
   * 当流关闭时调用回调函数。
   */
  nghttp2_on_stream_close_callback on_stream_close_callback;
  /**
   * 在HEADERS或PUSH_PROMISE中开始接收头块时调用回调函数。
   */
  nghttp2_on_begin_headers_callback on_begin_headers_callback;
  /**
   * 收到头名称/值对时调用回调函数。
   */
  nghttp2_on_header_callback on_header_callback;
  nghttp2_on_header_callback2 on_header_callback2;
  /**
   * 当接收到无效的头名称/值对时调用回调函数，如果未设置这些回调，则会自动忽略该函数。
   */
  nghttp2_on_invalid_header_callback on_invalid_header_callback;
  nghttp2_on_invalid_header_callback2 on_invalid_header_callback2;
  /**
   * 当库询问应用程序传输给定帧需要多少填充字节时调用回调函数。
   */
  nghttp2_select_padding_callback select_padding_callback;
  /**
   * 用于确定`nghttp2_data_source_read_callback（）中允许的长度的回调函数`
   */
  nghttp2_data_source_read_length_callback read_length_callback;
  /**
   * 设置收到帧头时调用的回调函数。
   */
  nghttp2_on_begin_frame_callback on_begin_frame_callback;
  nghttp2_send_data_callback send_data_callback;
  nghttp2_pack_extension_callback pack_extension_callback;
  nghttp2_unpack_extension_callback unpack_extension_callback;
  nghttp2_on_extension_chunk_recv_callback on_extension_chunk_recv_callback;
  nghttp2_error_callback error_callback;
  nghttp2_error_callback2 error_callback2;
};

#endif /* NGHTTP2_CALLBACKS_H */

