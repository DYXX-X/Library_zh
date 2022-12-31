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
#ifndef NGHTTP2_OPTION_H
#define NGHTTP2_OPTION_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>

/**
 * 配置选项
 */
typedef enum {
  /**
   * 此选项阻止库自动发送连接的WINDOW_UPDATE。如果此选项设置为非零，则在应用程序调用nghttp2_session_customer（）以指示消耗的DATA量之前，库不会发送WINDOW_UPDATE for DATA。默认情况下，此选项设置为零。
   */
  NGHTTP2_OPT_NO_AUTO_WINDOW_UPDATE = 1,
  /**
   * 此选项设置远程端点的SETTINGS_MAX_CONCURRENT_STREAMS值，就像在SETTINGS帧中接收到一样。如果不指定此选项，则在本地端点从远程端点接收SETTINGS帧中的SETTINGS_MAX_CONCURRENT_STREAMS之前，SETTINGS_VAX_CONCCURRENT_STRAMS是不受限制的。如果本地端点最初提交了大量请求，并且立即将它们发送到远程对等端可能会导致某些请求被拒绝，这可能会导致问题。将此选项指定为合理值（例如100）可以避免此类问题。如果本地端点从远程端点接收SETTINGS_MAX_CONCURRENT_STREAMS，则将覆盖此值。
   */
  NGHTTP2_OPT_PEER_MAX_CONCURRENT_STREAMS = 1 << 1,
  NGHTTP2_OPT_NO_RECV_CLIENT_MAGIC = 1 << 2,
  NGHTTP2_OPT_NO_HTTP_MESSAGING = 1 << 3,
  NGHTTP2_OPT_MAX_RESERVED_REMOTE_STREAMS = 1 << 4,
  NGHTTP2_OPT_USER_RECV_EXT_TYPES = 1 << 5,
  NGHTTP2_OPT_NO_AUTO_PING_ACK = 1 << 6,
  NGHTTP2_OPT_BUILTIN_RECV_EXT_TYPES = 1 << 7,
  NGHTTP2_OPT_MAX_SEND_HEADER_BLOCK_LENGTH = 1 << 8,
  NGHTTP2_OPT_MAX_DEFLATE_DYNAMIC_TABLE_SIZE = 1 << 9,
  NGHTTP2_OPT_NO_CLOSED_STREAMS = 1 << 10,
  NGHTTP2_OPT_MAX_OUTBOUND_ACK = 1 << 11,
  NGHTTP2_OPT_MAX_SETTINGS = 1 << 12,
} nghttp2_option_flag;

/**
 * 用于存储nghttp2_session的选项值的结构。
 */
struct nghttp2_option {
  /**
   * NGHTTP2_OPT_MAX_SEND_HEADER_BLOCK_LENGTH
   */
  size_t max_send_header_block_length;
  /**
   * NGHTTP2_OPT_MAX_DEFLATE_DYNAMIC_TABLE_SIZE
   */
  size_t max_deflate_dynamic_table_size;
  /**
   * NGHTTP2_OPT_MAX_OUTBOUND_ACK
   */
  size_t max_outbound_ack;
  /**
   * NGHTTP2_OPT_MAX_SETTINGS
   */
  size_t max_settings;
  /**
   * nghttp2_option_flag的逐位OR，以确定指定了哪些字段。
   */
  uint32_t opt_set_mask;
  /**
   * NGHTTP2_OPT_PEER_MAX_CONCURRENT_STREAMS
   */
  uint32_t peer_max_concurrent_streams;
  /**
   * NGHTTP2_OPT_MAX_RESERVED_REMOTE_STREAMS
   */
  uint32_t max_reserved_remote_streams;
  /**
   * NGHTTP2_OPT_BUILTIN_RECV_EXT_TYPES
   */
  uint32_t builtin_recv_ext_types;
  /**
   * NGHTTP2_OPT_NO_AUTO_WINDOW_UPDATE
   */
  int no_auto_window_update;
  /**
   * NGHTTP2_OPT_NO_RECV_CLIENT_MAGIC
   */
  int no_recv_client_magic;
  /**
   * NGHTTP2_OPT_NO_HTTP_MESSAGING
   */
  int no_http_messaging;
  /**
   * NGHTTP2_OPT_NO_AUTO_PING_ACK
   */
  int no_auto_ping_ack;
  /**
   * NGHTTP2_OPT_NO_CLOSED_STREAMS
   */
  int no_closed_streams;
  /**
   * NGHTTP2_OPT_USER_RECV_EXT_TYPES
   */
  uint8_t user_recv_ext_types[32];
};

#endif /* NGHTTP2_OPTION_H */

