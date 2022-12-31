/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）20132014 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef NGHTTP2_H
#define NGHTTP2_H

/* 当构建目标是WIN32 API时定义WIN32（借用libcurl）*/
#if (defined(_WIN32) || defined(__WIN32__)) && !defined(WIN32)
#  define WIN32
#endif

/* 非Clang编译器的兼容性*/
#ifndef __has_declspec_attribute
#  define __has_declspec_attribute(x) 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#if defined(_MSC_VER) && (_MSC_VER < 1800)
/* MSVC<2013没有inttypes.h，因为它不符合C99。请参见中的编译器宏和版本号https://sourceforge.net/p/predef/wiki/Compilers/ */
#  include <stdint.h>
#else /* !定义（_MSC_VER）||（_MSC_VER>=1800）*/
#  include <inttypes.h>
#endif /* !定义（_MSC_VER）||（_MSC_VER>=1800）*/
#include <sys/types.h>
#include <stdarg.h>

#include <nghttp2/nghttp2ver.h>

#ifdef NGHTTP2_STATICLIB
#  define NGHTTP2_EXTERN
#elif defined(WIN32) || (__has_declspec_attribute(dllexport) &&                \
                         __has_declspec_attribute(dllimport))
#  ifdef BUILDING_NGHTTP2
#    define NGHTTP2_EXTERN __declspec(dllexport)
#  else /* !BUILDING_NGHTTP2 */
#    define NGHTTP2_EXTERN __declspec(dllimport)
#  endif /* !BUILDING_NGHTTP2 */
#else    /* !定义（WIN32）*/
#  ifdef BUILDING_NGHTTP2
#    define NGHTTP2_EXTERN __attribute__((visibility("default")))
#  else /* !BUILDING_NGHTTP2 */
#    define NGHTTP2_EXTERN
#  endif /* !BUILDING_NGHTTP2 */
#endif   /* !定义（WIN32）*/

/**
 * @macro
 *
 * 此库支持的协议版本标识字符串。如果通过TLS使用HTTP/2，则使用此标识符。
 */
#define NGHTTP2_PROTO_VERSION_ID "h2"
/**
 * @macro
 *
 * 宏的长度：`NGHTTP2_PROTO_VERSION_ID`。
 */
#define NGHTTP2_PROTO_VERSION_ID_LEN 2

/**
 * @macro
 *
 * 此库支持的ALPN协议标识符的序列化形式。注意，第一个字节是以下协议标识符的长度。这与`TLS ALPN扩展的有线格式相同<https://tools.ietf.org/html/rfc7301>`_. 这对于处理有线格式的传入ALPN令牌非常有用。
 */
#define NGHTTP2_PROTO_ALPN "\x2h2"

/**
 * @macro
 *
 * 宏的长度：`NGHTTP2_PROTO_ALPN`。
 */
#define NGHTTP2_PROTO_ALPN_LEN (sizeof(NGHTTP2_PROTO_ALPN) - 1)

/**
 * @macro
 *
 * 此库支持的协议版本标识字符串。如果在明文TCP上使用HTTP/2，则使用此标识符。
 */
#define NGHTTP2_CLEARTEXT_PROTO_VERSION_ID "h2c"

/**
 * @macro
 *
 * 宏的长度：`NGHTTP2_CLEARTEXT_PROTO_VERSION_ID`。
 */
#define NGHTTP2_CLEARTEXT_PROTO_VERSION_ID_LEN 3

struct nghttp2_session;
/**
 * @struct
 *
 * 用于保存HTTP/2会话所需资源的主要结构。此结构的详细信息有意隐藏在公共API中。
 */
typedef struct nghttp2_session nghttp2_session;

/**
 * @macro
 *
 * 年龄：type:`nghttp2_info`
 */
#define NGHTTP2_VERSION_AGE 1

/**
 * @struct
 *
 * 此结构是“nghttp2_version（）”返回的。它保存有关特定nghttp2版本的信息。
 */
typedef struct {
  /**
   * 此结构的年龄。nghttp2的此实例将其设置为：macro:`nghttp2_VERSION_AGE`，但将来的版本可能会对其进行升级，并在底部添加更多结构字段
   */
  int age;
  /**
   * ：macro:`NGHTTP2_VERSION_NUM`编号（自年龄==1起）
   */
  int version_num;
  /**
   * 指向：macro:`NGHTTP2_VERSION`字符串（因为年龄==1）
   */
  const char *version_str;
  /**
   * 指向此实例实现的：macro:`NGHTTP2_PROTO_VERSION_ID`字符串（因为年龄==1）
   */
  const char *proto_str;
  /* --------当年龄==1时，上述字段都存在*/
} nghttp2_info;

/**
 * @macro
 *
 * 流依赖项的默认权重。
 */
#define NGHTTP2_DEFAULT_WEIGHT 16

/**
 * @macro
 *
 * 流依赖项的最大权重。
 */
#define NGHTTP2_MAX_WEIGHT 256

/**
 * @macro
 *
 * 流相关性的最小权重。
 */
#define NGHTTP2_MIN_WEIGHT 1

/**
 * @macro
 *
 * 最大窗口大小
 */
#define NGHTTP2_MAX_WINDOW_SIZE ((int32_t)((1U << 31) - 1))

/**
 * @macro
 *
 * 流级流控制的初始窗口大小。
 */
#define NGHTTP2_INITIAL_WINDOW_SIZE ((1 << 16) - 1)
/**
 * @macro
 *
 * 连接级别流控制的初始窗口大小。
 */
#define NGHTTP2_INITIAL_CONNECTION_WINDOW_SIZE ((1 << 16) - 1)

/**
 * @macro
 *
 * 默认标题表大小。
 */
#define NGHTTP2_DEFAULT_HEADER_TABLE_SIZE (1 << 12)

/**
 * @macro
 *
 * 客户端魔术字符串，它是客户端连接序的第一个24字节字节字符串。
 */
#define NGHTTP2_CLIENT_MAGIC "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n"

/**
 * @macro
 *
 * 宏的长度：`NGHTTP2_CLIENT_MAGIC`。
 */
#define NGHTTP2_CLIENT_MAGIC_LEN 24

/**
 * @macro
 *
 * 每个settings帧的默认最大设置数
 */
#define NGHTTP2_DEFAULT_MAX_SETTINGS 32

/**
 * @enum
 *
 * 此库中使用的错误代码。代码范围为[-999，-500]（含）。定义了以下值：
 */
typedef enum {
  /**
   * 传递的参数无效。
   */
  NGHTTP2_ERR_INVALID_ARGUMENT = -501,
  /**
   * 缓冲区空间不足。
   */
  NGHTTP2_ERR_BUFFER_ERROR = -502,
  /**
   * 不支持指定的协议版本。
   */
  NGHTTP2_ERR_UNSUPPORTED_VERSION = -503,
  /**
   * 用作：type:`nghttp2_send_callback`、：type:` nghttp2_recv_callback'和：type:'nghttp2_send_data_callback`的返回值，以指示操作将阻塞。
   */
  NGHTTP2_ERR_WOULDBLOCK = -504,
  /**
   * 常规协议错误
   */
  NGHTTP2_ERR_PROTO = -505,
  /**
   * 帧无效。
   */
  NGHTTP2_ERR_INVALID_FRAME = -506,
  /**
   * 对等方对连接执行了关闭。
   */
  NGHTTP2_ERR_EOF = -507,
  /**
   * 用作：func:`nghttp2_data_source_read_callback`的返回值，表示数据传输被延迟。有关详细信息，请参见：func:`nghttp2_data_source_read_callback`。
   */
  NGHTTP2_ERR_DEFERRED = -508,
  /**
   * 流ID已达到最大值。因此，没有可用的流ID。
   */
  NGHTTP2_ERR_STREAM_ID_NOT_AVAILABLE = -509,
  /**
   * 流已关闭；或者流ID无效。
   */
  NGHTTP2_ERR_STREAM_CLOSED = -510,
  /**
   * RST_STREAM已添加到出站队列。流处于关闭状态。
   */
  NGHTTP2_ERR_STREAM_CLOSING = -511,
  /**
   * 此流不允许传输（例如，已发送设置了END_stream标志的帧）。
   */
  NGHTTP2_ERR_STREAM_SHUT_WR = -512,
  /**
   * 流ID无效。
   */
  NGHTTP2_ERR_INVALID_STREAM_ID = -513,
  /**
   * 流的状态无效（例如，如果未发送响应HEADERS，则无法将DATA发送到流）。
   */
  NGHTTP2_ERR_INVALID_STREAM_STATE = -514,
  /**
   * 另一个DATA帧已延迟。
   */
  NGHTTP2_ERR_DEFERRED_DATA_EXIST = -515,
  /**
   * 不允许启动新流（例如，已发送和/或接收GOAWAY）。
   */
  NGHTTP2_ERR_START_STREAM_NOT_ALLOWED = -516,
  /**
   * GOAWAY已发送。
   */
  NGHTTP2_ERR_GOAWAY_ALREADY_SENT = -517,
  /**
   * 接收到的帧包含无效的标头块（例如，有重复的标头名称；或标头名称未以US-ASCII字符集编码，且未使用小写；或标头名为零长度字符串；或标头值包含多个顺序NUL字节）。
   */
  NGHTTP2_ERR_INVALID_HEADER_BLOCK = -518,
  /**
   * 指示上下文不适合执行请求的操作。
   */
  NGHTTP2_ERR_INVALID_STATE = -519,
  /**
   * 由于时间错误，用户回调函数失败。
   */
  NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE = -521,
  /**
   * 帧的长度无效，要么太大，要么太小。
   */
  NGHTTP2_ERR_FRAME_SIZE_ERROR = -522,
  /**
   * 收割台模块充气/放气错误。
   */
  NGHTTP2_ERR_HEADER_COMP = -523,
  /**
   * 流量控制错误
   */
  NGHTTP2_ERR_FLOW_CONTROL = -524,
  /**
   * 给函数的缓冲区大小不足。
   */
  NGHTTP2_ERR_INSUFF_BUFSIZE = -525,
  /**
   * 应用程序已暂停回调
   */
  NGHTTP2_ERR_PAUSE = -526,
  /**
   * 飞行中设置帧太多，不允许再传输设置。
   */
  NGHTTP2_ERR_TOO_MANY_INFLIGHT_SETTINGS = -527,
  /**
   * 服务器推送已禁用。
   */
  NGHTTP2_ERR_PUSH_DISABLED = -528,
  /**
   * 给定流的DATA或HEADERS帧已提交，尚未完全处理。应用程序应在提交另一帧之前等待先前提交的帧的传输。
   */
  NGHTTP2_ERR_DATA_EXIST = -529,
  /**
   * 由于连接错误或调用了“nghttp2_session_terminate_session（）”，当前会话正在关闭。
   */
  NGHTTP2_ERR_SESSION_CLOSING = -530,
  /**
   * 接收到无效的HTTP标头字段，流将被关闭。
   */
  NGHTTP2_ERR_HTTP_HEADER = -531,
  /**
   * 违反HTTP消息传递规则。
   */
  NGHTTP2_ERR_HTTP_MESSAGING = -532,
  /**
   * 流被拒绝。
   */
  NGHTTP2_ERR_REFUSED_STREAM = -533,
  /**
   * 意外的内部错误，但已恢复。
   */
  NGHTTP2_ERR_INTERNAL = -534,
  /**
   * 指示处理已取消。
   */
  NGHTTP2_ERR_CANCEL = -535,
  /**
   * 当本地端点希望接收SETTINGS帧时，它会接收其他类型的帧。
   */
  NGHTTP2_ERR_SETTINGS_EXPECTED = -536,
  /**
   * 当本地端点在单个settings帧中接收到太多设置条目时。
   */
  NGHTTP2_ERR_TOO_MANY_SETTINGS = -537,
  /**
   * 错误<：enum:`NGHTTP2_ERR_FATAL`表示库处于意外状态，处理已终止（例如，内存不足）。若应用程序收到此错误代码，它必须停止使用该：type:`nghttp2_session`对象，并且该对象的唯一允许操作是使用`nghttp 2_session_del（）`解除分配该对象。
   */
  NGHTTP2_ERR_FATAL = -900,
  /**
   * 内存不足。这是一个致命错误。
   */
  NGHTTP2_ERR_NOMEM = -901,
  /**
   * 用户回调函数失败。这是一个致命错误。
   */
  NGHTTP2_ERR_CALLBACK_FAILURE = -902,
  /**
   * 接收到无效的客户端魔术（请参阅：宏：`NGHTTP2_client_magic`），无法进行进一步处理。
   */
  NGHTTP2_ERR_BAD_CLIENT_MAGIC = -903,
  /**
   * 在此HTTP/2会话中检测到对等方可能发生洪水。泛洪是通过设置了ACK标志的PING和SETTINGS帧排队等待传输来衡量的。这些帧是对等方发起的帧的响应，对等方可能会导致服务器端内存耗尽，从而永久发送这些帧，并且不读取网络。
   */
  NGHTTP2_ERR_FLOODED = -904
} nghttp2_error;

/**
 * @struct
 *
 * 表示单个连续缓冲区的对象。
 */
typedef struct {
  /**
   * 指向缓冲区的指针。
   */
  uint8_t *base;
  /**
   * 缓冲区的长度。
   */
  size_t len;
} nghttp2_vec;

struct nghttp2_rcbuf;

/**
 * @struct
 *
 * 表示引用计数缓冲区的对象。此结构的详细信息有意隐藏在公共API中。
 */
typedef struct nghttp2_rcbuf nghttp2_rcbuf;

/**
 * @function
 *
 * 将|rcbuf|的引用计数增加1。
 */
NGHTTP2_EXTERN void nghttp2_rcbuf_incref(nghttp2_rcbuf *rcbuf);

/**
 * @function
 *
 * 将|rcbuf|的引用计数减1。如果引用计数变为零，则|rcbuf |指向的对象将被释放。在这种情况下，应用程序不能再次使用|rcbuf|。
 */
NGHTTP2_EXTERN void nghttp2_rcbuf_decref(nghttp2_rcbuf *rcbuf);

/**
 * @function
 *
 * 返回由|rcbuf|管理的基础缓冲区。
 */
NGHTTP2_EXTERN nghttp2_vec nghttp2_rcbuf_get_buf(nghttp2_rcbuf *rcbuf);

/**
 * @function
 *
 * 如果基础缓冲区是静态分配的，则返回非零，否则返回0。这对于希望避免为这些缓冲区创建重复字符串的语言绑定非常有用。
 */
NGHTTP2_EXTERN int nghttp2_rcbuf_is_static(const nghttp2_rcbuf *rcbuf);

/**
 * @enum
 *
 * 标头字段名称/值对的标志。
 */
typedef enum {
  /**
   * 未设置标志。
   */
  NGHTTP2_NV_FLAG_NONE = 0,
  /**
   * 指示此名称/值对不能被索引（HPACK编码中必须使用“Literal Header Field never indexed”表示）。其他实现将此位称为“敏感”。
   */
  NGHTTP2_NV_FLAG_NO_INDEX = 0x01,
  /**
   * 此标志仅由应用程序设置。如果设置了此标志，则库不会复制头字段名。这可以提高性能。
   */
  NGHTTP2_NV_FLAG_NO_COPY_NAME = 0x02,
  /**
   * 此标志仅由应用程序设置。如果设置了此标志，则库不会复制头字段值。这可以提高性能。
   */
  NGHTTP2_NV_FLAG_NO_COPY_VALUE = 0x04
} nghttp2_nv_flag;

/**
 * @struct
 *
 * 名称/值对，主要用于表示头字段。
 */
typedef struct {
  /**
   * |name|字节字符串。如果此结构是从库中呈现的（例如：type:`nghttp2_on_frame_recv_callback`），则保证|name|以NULL结尾。对于某些回调（：type:`nghttp2_before_frame_send_callback`、：type:` nghttp2_on_frame_send_callback`和：type:'nghttp2_on_frame_not_send_cllback`），如果从应用程序传递带有标志：enum:`nghttp2_NV_flag_NO_COPY_NAME`的头字段，则它可能不会以NULL结尾）。当应用程序构造此结构时，|name|不需要以NULL结尾。
   */
  uint8_t *name;
  /**
   * |value|字节字符串。如果此结构是从库中呈现的（例如：type:`nghttp2_on_frame_recv_callback`），则保证|value|以NULL结尾。对于某些回调（：type:`nghttp2_before_frame_send_callback`、：type:` nghttp2_on_frame_send_callback`和：type:'nghttp2_on_frame_not_send_cllback`），如果从应用程序传递带有标志：enum:`nghttp2_NV_flag_NO_COPY_VALUE`的头字段，则它可能不会以NULL结尾）。当应用程序构造此结构时，|value|不需要以NULL结尾。
   */
  uint8_t *value;
  /**
   * |name|的长度，不包括终止NULL。
   */
  size_t namelen;
  /**
   * |值|的长度，不包括终止NULL。
   */
  size_t valuelen;
  /**
   * 类型：“nghttp2_nv_flag”中的一个或多个的逐位OR。
   */
  uint8_t flags;
} nghttp2_nv;

/**
 * @enum
 *
 * HTTP/2规范中的帧类型。
 */
typedef enum {
  /**
   * DATA帧。
   */
  NGHTTP2_DATA = 0,
  /**
   * HEADERS框架。
   */
  NGHTTP2_HEADERS = 0x01,
  /**
   * PRIORITY框架。
   */
  NGHTTP2_PRIORITY = 0x02,
  /**
   * RST_STREAM帧。
   */
  NGHTTP2_RST_STREAM = 0x03,
  /**
   * SETTINGS（设置）框。
   */
  NGHTTP2_SETTINGS = 0x04,
  /**
   * PUSH_PROMISE帧。
   */
  NGHTTP2_PUSH_PROMISE = 0x05,
  /**
   * PING帧。
   */
  NGHTTP2_PING = 0x06,
  /**
   * GOAWAY框架。
   */
  NGHTTP2_GOAWAY = 0x07,
  /**
   * WINDOW_UPDATE框架。
   */
  NGHTTP2_WINDOW_UPDATE = 0x08,
  /**
   * 连续帧。此帧类型不会传递给任何回调，因为库将此帧类型及其前面的HEADERS/PUSH_PROMISE作为单个帧进行处理。
   */
  NGHTTP2_CONTINUATION = 0x09,
  /**
   * ALTSVC帧，在`RFC 7383中定义<https://tools.ietf.org/html/rfc7838#section-4>`_.
   */
  NGHTTP2_ALTSVC = 0x0a,
  /**
   * ORIGIN帧，由`RFC 8336定义<https://tools.ietf.org/html/rfc8336>`_.
   */
  NGHTTP2_ORIGIN = 0x0c
} nghttp2_frame_type;

/**
 * @enum
 *
 * HTTP/2帧的标志。此枚举定义所有帧的所有标志。
 */
typedef enum {
  /**
   * 未设置标志。
   */
  NGHTTP2_FLAG_NONE = 0,
  /**
   * END_STREAM标志。
   */
  NGHTTP2_FLAG_END_STREAM = 0x01,
  /**
   * END_HEADERS标志。
   */
  NGHTTP2_FLAG_END_HEADERS = 0x04,
  /**
   * ACK标志。
   */
  NGHTTP2_FLAG_ACK = 0x01,
  /**
   * PADDED标志。
   */
  NGHTTP2_FLAG_PADDED = 0x08,
  /**
   * PRIORITY标志。
   */
  NGHTTP2_FLAG_PRIORITY = 0x20
} nghttp2_flag;

/**
 * @enum 设置ID。
 */
typedef enum {
  /**
   * SETTINGS_HEADER_TABLE_SIZE
   */
  NGHTTP2_SETTINGS_HEADER_TABLE_SIZE = 0x01,
  /**
   * SETTINGS_ENABLE_PUSH
   */
  NGHTTP2_SETTINGS_ENABLE_PUSH = 0x02,
  /**
   * SETTINGS_MAX_CONCURRENT_STREAMS
   */
  NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS = 0x03,
  /**
   * SETTINGS_INITIAL_WINDOW_SIZE
   */
  NGHTTP2_SETTINGS_INITIAL_WINDOW_SIZE = 0x04,
  /**
   * SETTINGS_MAX_FRAME_SIZE
   */
  NGHTTP2_SETTINGS_MAX_FRAME_SIZE = 0x05,
  /**
   * SETTINGS_MAX_HEADER_LIST_SIZE
   */
  NGHTTP2_SETTINGS_MAX_HEADER_LIST_SIZE = 0x06,
  /**
   * 设置启用连接协议（`RFC 8441<https://tools.ietf.org/html/rfc8441>`_)
   */
  NGHTTP2_SETTINGS_ENABLE_CONNECT_PROTOCOL = 0x08
} nghttp2_settings_id;
/* 注意：如果我们添加SETTINGS（设置），请同时更新NGHTTP2_INBOUND_NUM_IV的容量*/

/**
 * @macro
 *
 * ..警告：：
 *
 *   已弃用。初始最大并发流为0xffffffffu。
 *
 * 默认最大传入并发流数。将“nghttp2_submit_settings（）”与：enum:`nghttp2_settings_MAX_CONCURRENT_STREAMS`一起使用可更改传入并发流的最大数量。
 *
 * ..注：
 *
 *   默认情况下，传出并发流的最大数量为100。
 */
#define NGHTTP2_INITIAL_MAX_CONCURRENT_STREAMS ((1U << 31) - 1)

/**
 * @enum RST_STREAM和GOAWAY帧的状态代码。
 */
typedef enum {
  /**
   * 没有错误。
   */
  NGHTTP2_NO_ERROR = 0x00,
  /**
   * PROTOCOL_ERROR
   */
  NGHTTP2_PROTOCOL_ERROR = 0x01,
  /**
   * INTERNAL_ERROR
   */
  NGHTTP2_INTERNAL_ERROR = 0x02,
  /**
   * FLOW_CONTROL_ERROR
   */
  NGHTTP2_FLOW_CONTROL_ERROR = 0x03,
  /**
   * SETTINGS_TIMEOUT
   */
  NGHTTP2_SETTINGS_TIMEOUT = 0x04,
  /**
   * STREAM_CLOSED
   */
  NGHTTP2_STREAM_CLOSED = 0x05,
  /**
   * FRAME_SIZE_ERROR
   */
  NGHTTP2_FRAME_SIZE_ERROR = 0x06,
  /**
   * REFUSED_STREAM
   */
  NGHTTP2_REFUSED_STREAM = 0x07,
  /**
   * CANCEL
   */
  NGHTTP2_CANCEL = 0x08,
  /**
   * COMPRESSION_ERROR
   */
  NGHTTP2_COMPRESSION_ERROR = 0x09,
  /**
   * CONNECT_ERROR
   */
  NGHTTP2_CONNECT_ERROR = 0x0a,
  /**
   * ENHANCE_YOUR_CALM
   */
  NGHTTP2_ENHANCE_YOUR_CALM = 0x0b,
  /**
   * INADEQUATE_SECURITY
   */
  NGHTTP2_INADEQUATE_SECURITY = 0x0c,
  /**
   * HTTP_1_1_REQUIRED
   */
  NGHTTP2_HTTP_1_1_REQUIRED = 0x0d
} nghttp2_error_code;

/**
 * @struct 帧标头。
 */
typedef struct {
  /**
   * 此帧的长度字段，不包括帧标头。
   */
  size_t length;
  /**
   * 流标识符（也称为流ID）
   */
  int32_t stream_id;
  /**
   * 此框架的类型。请参见`nghttp2_frame_type`。
   */
  uint8_t type;
  /**
   * 旗帜。
   */
  uint8_t flags;
  /**
   * 帧标头中的保留位。目前，该值始终设置为0，应用程序不应该期望在这里有什么有用的东西。
   */
  uint8_t reserved;
} nghttp2_frame_hd;

/**
 * @union
 *
 * 此联合表示传递给以下类型的某种数据源：“nghttp2_data_source_read_callback”。
 */
typedef union {
  /**
   * 整数字段，适用于文件描述符。
   */
  int fd;
  /**
   * 指向任意对象的指针。
   */
  void *ptr;
} nghttp2_data_source;

/**
 * @enum
 *
 * 用于在|data_flags|输出参数中设置的标志：type:`nghttp2_data_source_read_callback`。
 */
typedef enum {
  /**
   * 未设置标志。
   */
  NGHTTP2_DATA_FLAG_NONE = 0,
  /**
   * 表示检测到EOF。
   */
  NGHTTP2_DATA_FLAG_EOF = 0x01,
  /**
   * 指示即使设置了NGHTTP2_DATA_flag_EOF，也不能设置END_STREAM标志。通常，此标志用于发送带有“nghttp2_submit_request（）”或“nghttp2-submit_response（））”的尾部字段。
   */
  NGHTTP2_DATA_FLAG_NO_END_STREAM = 0x02,
  /**
   * 指示应用程序将在以下类型中发送完整的DATA帧：“nghttp2_send_DATA_callback”。
   */
  NGHTTP2_DATA_FLAG_NO_COPY = 0x04
} nghttp2_data_flag;

/**
 * @functypedef
 *
 * 当库希望从|source|读取数据时调用回调函数。读取的数据在流|stream_id|中发送。此函数的实现必须从|source|（或可能的其他位置）读取最多|length|字节的数据，并将其存储在|buf|中，并返回存储在|buf|中的数据数。如果达到EOF，请在|DATA_flags|中设置：enum:`NGHTTP2_DATA_FLAG_EOF`标志。
 *
 * 有时需要避免将数据复制到|buf|中，让应用程序直接发送数据。要实现这一点，请将：enum:`NGHTTP2_DATA_FLAG_NO_COOPY`设置为|DATA_flags|（可能还有其他标志，就像我们复制时一样），并返回在不将数据复制到|buf|的情况下要发送的字节数。库（参见：enum:`NGHTTP2_DATA_FLAG_NO_COOPY`）将调用：type:`NGHTTP2_send_DATA_callback`。应用程序必须在该回调中发送完整的DATA帧。
 *
 * 如果此回调由设置了标志参数：enum:`nghttp2_flag_END_STREAM`的`nghttp2_submit_request（）`、`ngHTTP_2_submit_response（）'或`nghttp2_submit_headers（）`和`nghttp 2_submit_data（）`设置，并且：enum:` nghttp2_data_flag_EOF`标志设置为|data_flags|，则data帧将设置END_STREAM标志。通常，这是预期的行为，一切都很好。一个例外是发送尾部字段。发送设置了END_STREAM的帧后，无法发送尾部字段。为了避免此问题，可以将：enum:`NGHTTP2_DATA_FLAG_NO_END_STREAM`与：enum:` NGHTTP2_DATA _FLAG_EOF`一起设置，以通知库不要在DATA帧中设置END_STREAM。然后应用程序可以使用“nghttp2_submit_trailer（）”发送尾部字段`nghttp2_submit_trailer（）`可以在此回调中调用。
 *
 * 如果应用程序希望延迟DATA帧（例如，异步I/O或长时间读取数据块），可以通过返回：enum:`NGHTTP2_ERR_DEFERRED`而不读取此调用中的任何数据来实现。库暂时从传出队列中删除DATA帧。要将延迟的DATA帧移回传出队列，请调用“nghttp2_session_resume_DATA（）”。
 *
 * 默认情况下，|length|最大限制为16KiB。若对等体允许更大的帧，应用程序可以扩大传输缓冲区的大小。有关详细信息，请参阅：type:`nghttp2_data_source_read_length_callback`。
 *
 * 如果应用程序只想从“nghttp2_session_send（）”或“nghttp2-session_mm_send（）”返回而不发送任何内容，则返回：enum:`nghttp2_ERR_PAUSE`。
 *
 * 如果出现错误，有两种选择。返回：enum:`NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE`将通过发出带有：enum:` NGHTTP2_INTERNAL_ERROR`的RST_stream来关闭流。如果需要不同的错误代码，请将“nghttp2_submit_rst_stream（）”与所需的错误代码一起使用，然后返回：enum:`nghttp2_ERR_TEMPORAL_CALLBACK_FAILURE`。返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`将发出整个会话失败的信号。
 */
typedef ssize_t (*nghttp2_data_source_read_callback)(
    nghttp2_session *session, int32_t stream_id, uint8_t *buf, size_t length,
    uint32_t *data_flags, nghttp2_data_source *source, void *user_data);

/**
 * @struct
 *
 * 此结构表示数据源以及从中读取数据块的方式。
 */
typedef struct {
  /**
   * 数据源。
   */
  nghttp2_data_source source;
  /**
   * 从|source|读取数据块的回调函数。
   */
  nghttp2_data_source_read_callback read_callback;
} nghttp2_data_provider;

/**
 * @struct
 *
 * DATA帧。接收到的数据通过：type:`nghttp2_on_data_chunk_recv_callback`传递。
 */
typedef struct {
  nghttp2_frame_hd hd;
  /**
   * 此框架中填充的长度。这包括PAD_HIGH和PAD_LOW。
   */
  size_t padlen;
} nghttp2_data;

/**
 * @enum
 *
 * HEADERS的类别，表示框架的作用。在HTTP/2规范中，请求、响应、推送响应和其他任意标头（例如，尾部字段）都称为HEADER。为了赋予应用程序传入HEADERS帧的角色，我们定义了几个类别。
 */
typedef enum {
  /**
   * HEADERS帧正在打开新的流，这类似于SPDY中的SYN_stream。
   */
  NGHTTP2_HCAT_REQUEST = 0,
  /**
   * HEADERS帧是第一个响应报头，类似于SPDY中的SYN_REPLY。
   */
  NGHTTP2_HCAT_RESPONSE = 1,
  /**
   * HEADERS帧是针对保留流发送的第一个报头。
   */
  NGHTTP2_HCAT_PUSH_RESPONSE = 2,
  /**
   * HEADERS框架不适用于上述类别，类似于SPDY中的HEADERS。如果使用非最终响应（例如，状态1xx），则此处将对最终响应HEADERS帧进行分类。
   */
  NGHTTP2_HCAT_HEADERS = 3
} nghttp2_headers_category;

/**
 * @struct
 *
 * 用于指定流依赖项的结构。
 */
typedef struct {
  /**
   * 要依赖的流的流ID。指定0使流不依赖任何其他流。
   */
  int32_t stream_id;
  /**
   * 此依赖项的权重。
   */
  int32_t weight;
  /**
   * 非零表示互斥依赖
   */
  uint8_t exclusive;
} nghttp2_priority_spec;

/**
 * @struct
 *
 * HEADERS框架。它有以下成员：
 */
typedef struct {
  /**
   * 帧标头。
   */
  nghttp2_frame_hd hd;
  /**
   * 此框架中填充的长度。这包括PAD_HIGH和PAD_LOW。
   */
  size_t padlen;
  /**
   * 优先级规范
   */
  nghttp2_priority_spec pri_spec;
  /**
   * 名称/值对。
   */
  nghttp2_nv *nva;
  /**
   * |nva|中的名称/值对数。
   */
  size_t nvlen;
  /**
   * 此HEADERS框架的类别。
   */
  nghttp2_headers_category cat;
} nghttp2_headers;

/**
 * @struct
 *
 * PRIORITY框架。它有以下成员：
 */
typedef struct {
  /**
   * 帧标头。
   */
  nghttp2_frame_hd hd;
  /**
   * 优先级规范。
   */
  nghttp2_priority_spec pri_spec;
} nghttp2_priority;

/**
 * @struct
 *
 * RST_STREAM帧。它有以下成员：
 */
typedef struct {
  /**
   * 帧标头。
   */
  nghttp2_frame_hd hd;
  /**
   * 错误代码。请参见：type:`nghttp2_error_code`。
   */
  uint32_t error_code;
} nghttp2_rst_stream;

/**
 * @struct
 *
 * SETTINGS ID/Value对。它有以下成员：
 */
typedef struct {
  /**
   * 设置ID。请参阅：type:`nghttp2_SETTINGS_ID`。
   */
  int32_t settings_id;
  /**
   * 此条目的值。
   */
  uint32_t value;
} nghttp2_settings_entry;

/**
 * @struct
 *
 * SETTINGS（设置）框。它有以下成员：
 */
typedef struct {
  /**
   * 帧标头。
   */
  nghttp2_frame_hd hd;
  /**
   * |iv|中SETTINGS ID/Value对的数量。
   */
  size_t niv;
  /**
   * 指向SETTINGS ID/Value对数组的指针。
   */
  nghttp2_settings_entry *iv;
} nghttp2_settings;

/**
 * @struct
 *
 * PUSH_PROMISE帧。它有以下成员：
 */
typedef struct {
  /**
   * 帧标头。
   */
  nghttp2_frame_hd hd;
  /**
   * 此框架中填充的长度。这包括PAD_HIGH和PAD_LOW。
   */
  size_t padlen;
  /**
   * 名称/值对。
   */
  nghttp2_nv *nva;
  /**
   * |nva|中的名称/值对数。
   */
  size_t nvlen;
  /**
   * 承诺的流ID
   */
  int32_t promised_stream_id;
  /**
   * 保留位。目前，此值始终设置为0，应用程序不应期望在此处有有用的内容。
   */
  uint8_t reserved;
} nghttp2_push_promise;

/**
 * @struct
 *
 * PING帧。它有以下成员：
 */
typedef struct {
  /**
   * 帧标头。
   */
  nghttp2_frame_hd hd;
  /**
   * 不透明的数据
   */
  uint8_t opaque_data[8];
} nghttp2_ping;

/**
 * @struct
 *
 * GOAWAY框架。它有以下成员：
 */
typedef struct {
  /**
   * 帧标头。
   */
  nghttp2_frame_hd hd;
  /**
   * 最后一个流ID。
   */
  int32_t last_stream_id;
  /**
   * 错误代码。请参见：type:`nghttp2_error_code`。
   */
  uint32_t error_code;
  /**
   * 附加调试数据
   */
  uint8_t *opaque_data;
  /**
   * |opaque_data|成员的长度。
   */
  size_t opaque_data_len;
  /**
   * 保留位。目前，此值始终设置为0，应用程序不应期望在此处有有用的内容。
   */
  uint8_t reserved;
} nghttp2_goaway;

/**
 * @struct
 *
 * WINDOW_UPDATE框架。它有以下成员：
 */
typedef struct {
  /**
   * 帧标头。
   */
  nghttp2_frame_hd hd;
  /**
   * 窗口大小增量。
   */
  int32_t window_size_increment;
  /**
   * 保留位。目前，此值始终设置为0，应用程序不应期望在此处有有用的内容。
   */
  uint8_t reserved;
} nghttp2_window_update;

/**
 * @struct
 *
 * 扩展框架。它有以下成员：
 */
typedef struct {
  /**
   * 帧标头。
   */
  nghttp2_frame_hd hd;
  /**
   * 指向扩展负载的指针。确切的指针类型由hd.type决定。
   *
   * 当前不支持扩展。这是未来扩展的占位符。
   */
  void *payload;
} nghttp2_extension;

/**
 * @union
 *
 * 此联合包括所有帧，以将它们作为nghttp2_frame类型传递给各种函数调用。此处省略了CONTINUATION框架，因为库在内部处理它。
 */
typedef union {
  /**
   * 帧头，便于检查帧头。
   */
  nghttp2_frame_hd hd;
  /**
   * DATA帧。
   */
  nghttp2_data data;
  /**
   * HEADERS框架。
   */
  nghttp2_headers headers;
  /**
   * PRIORITY框架。
   */
  nghttp2_priority priority;
  /**
   * RST_STREAM帧。
   */
  nghttp2_rst_stream rst_stream;
  /**
   * SETTINGS（设置）框。
   */
  nghttp2_settings settings;
  /**
   * PUSH_PROMISE帧。
   */
  nghttp2_push_promise push_promise;
  /**
   * PING帧。
   */
  nghttp2_ping ping;
  /**
   * GOAWAY框架。
   */
  nghttp2_goaway goaway;
  /**
   * WINDOW_UPDATE框架。
   */
  nghttp2_window_update window_update;
  /**
   * 扩展框架。
   */
  nghttp2_extension ext;
} nghttp2_frame;

/**
 * @functypedef
 *
 * 当|session|希望向远程对等方发送数据时调用回调函数。此函数的实现最多只能发送|data|中存储的|length|字节的数据。|标志|当前未使用，始终为0。如果成功，则必须返回发送的字节数。如果它无法在不阻塞的情况下发送任何单个字节，则必须返回：enum:`NGHTTP2_ERR_WOULDBLOCK`。对于其他错误，它必须返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。|user_data|指针是传递给调用“nghttp2_session_client_new（）”或“nghttp 2_session_server_new（（）”的第三个参数。
 *
 * 如果应用程序使用“nghttp2_session_send（）”向远程端点发送数据，则需要此回调。如果应用程序仅使用“nghttp2_session_mmem_send（）”，则不需要此回调函数。
 *
 * 要将此回调设置为：键入：`nghttp2_session_callbacks'，请使用`nghttp_2_session_callback_set_send_callback（）`。
 *
 * ..注：
 *
 *   |长度|可能很小。如果是这种情况，并且应用程序禁用Nagle算法（“TCP_NODELAY”），那么仅仅将|数据|写入网络堆栈就会导致非常小的数据包，而且效率非常低。应用程序应负责在必要时缓冲小数据块，以避免这种情况。
 */
typedef ssize_t (*nghttp2_send_callback)(nghttp2_session *session,
                                         const uint8_t *data, size_t length,
                                         int flags, void *user_data);

/**
 * @functypedef
 *
 * 当：enum:`NGHTTP2_DATA_FLAG_NO_COOPY`用于：type:`NGHTTP2_DATA_source_read_Callback`以发送完整的DATA帧时调用回调函数。
 *
 * |帧|是要发送的DATA帧。|framehd|是序列化的帧头（9字节）。|length|是要发送的应用程序数据的长度（不包括填充）。|source|与传递给：type:`nghttp2_data_source_read_callback`的指针相同。
 *
 * 应用程序首先必须发送长度为9字节的帧头|framehd|。如果``frame->data.padlen>0``，则发送值为``frame->data.padlen-1``的1字节。然后精确发送|length|字节的应用程序数据。最后，如果``frame->data.padlen>1``，则发送``frame->data.padlen-1``零字节作为填充。
 *
 * 应用程序必须在此回调中发送完整的DATA帧。如果已成功写入所有数据，则返回0。
 *
 * 如果它根本无法发送任何数据，只需返回：enum:`NGHTTP2_ERR_WOULDBLOCK`；库稍后将使用相同的参数调用此回调（建议在该函数中立即发送完整的DATA帧以处理错误；如果部分帧数据已经发送，则不可能在该状态下发送另一个数据，我们所能做的就是拆除连接）。当数据被完全处理时，但应用程序希望立即返回“nghttp2_session_me_send（）”或“nghttp 2_session_send（）”而不处理下一帧时，返回：enum:`nghttp2_ERR_PAUSE`。如果应用程序决定重置此流，返回：enum:`NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE`，则库将发送带有INTERNAL_ERROR作为错误代码的RST_stream。应用程序还可以返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`，这将导致连接关闭。返回任何其他值将被视为：enum:返回`NGHTTP2_ERR_CALLBACK_FAILURE`。
 */
typedef int (*nghttp2_send_data_callback)(nghttp2_session *session,
                                          nghttp2_frame *frame,
                                          const uint8_t *framehd, size_t length,
                                          nghttp2_data_source *source,
                                          void *user_data);

/**
 * @functypedef
 *
 * 当|session|希望从远程对等方接收数据时调用回调函数。此函数的实现必须读取最多|length|字节的数据，并将其存储在|buf|中。|标志|当前未使用，始终为0。如果成功，它必须返回写入|buf|的字节数。如果它无法在不阻塞的情况下读取任何单个字节，则必须返回：enum:`NGHTTP2_ERR_WOULDBLOCK`。如果它在读取任何单个字节之前获得EOF，则必须返回：enum:`NGHTTP2_ERR_EOF`。对于其他错误，它必须返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。返回0被视为：enum:`NGHTTP2_ERR_WOULDBLOCK`。|user_data|指针是传递给调用“nghttp2_session_client_new（）”或“nghttp 2_session_server_new（（）”的第三个参数。
 *
 * 如果应用程序使用“nghttp2_session_recv（）”从远程端点接收数据，则需要此回调。如果应用程序仅使用“nghttp2_session_mem_recv（）”，则不需要此回调函数。
 *
 * 若要将此回调设置为：键入：`nghttp2_session_callbacks'，请使用`nghttp 2_session_ccallback_set_recv_callback（）`。
 */
typedef ssize_t (*nghttp2_recv_callback)(nghttp2_session *session, uint8_t *buf,
                                         size_t length, int flags,
                                         void *user_data);

/**
 * @functypedef
 *
 * 当接收到帧时，由“nghttp2_session_recv（）”和“nghttp 2_session_me_recv（）”调用的回调函数。|user_data|指针是传递给调用“nghttp2_session_client_new（）”或“nghttp 2_session_server_new（（）”的第三个参数。
 *
 * 如果帧是HEADERS或PUSH_PROMISE，则其数据结构的“nva”和“nvlen”成员始终分别为“NULL”和“0”。标头名称/值对通过：type:`nghttp2_on_header_callback `发出。
 *
 * 对于HEADERS、PUSH_PROMISE和DATA帧，可以在流关闭后调用此回调（请参阅：类型：`nghttp2_on_stream_close_callback`）。应用程序应该使用自己的流管理或：func:`nghttp2_session_get_stream_user_data（）`来检查流是否仍处于活动状态。
 *
 * 只有HEADERS和DATA帧可以发出输入数据结束的信号。如果``frame->hd。flags&NGHTTP2_FLAG_END_STREAM“”为非零，|frame |是此流中远程对等端的最后一帧。
 *
 * 对于CONTINIUATION帧，不会调用此回调。HEADERS/PUSH_PROMISE+CONTINUATIONs被视为单帧。
 *
 * 如果成功，此函数的实现必须返回0。如果返回非零值，则将其视为致命错误，并且“nghttp2_session_recv（）”和“nghttp 2_session_me_recv（）”函数立即返回：enum:`nghttp2_ERR_CALLBACK_FAILURE`。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp_2_session_callbacks_set_onframe_recv_callback（）”。
 */
typedef int (*nghttp2_on_frame_recv_callback)(nghttp2_session *session,
                                              const nghttp2_frame *frame,
                                              void *user_data);

/**
 * @functypedef
 *
 * 当接收到无效的非DATA帧时，由“nghttp2_session_recv（）”和“nghttp 2_session_me_recv（）”调用的回调函数。该错误由|lib_error_code|表示，它是在：type:`nghttp2_error`中定义的值之一。调用此回调函数时，库将自动提交RST_STREAM或GOAWAY帧。|user_data|指针是传递给调用“nghttp2_session_client_new（）”或“nghttp 2_session_server_new（（）”的第三个参数。
 *
 * 如果帧是HEADERS或PUSH_PROMISE，则其数据结构的“nva”和“nvlen”成员始终分别为“NULL”和“0”。
 *
 * 如果成功，此函数的实现必须返回0。如果返回非零，则将其视为致命错误，并且“nghttp2_session_recv（）”和“nghttp 2_session_me_recv（）”函数立即返回：enum:`nghttp2_ERR_CALLBACK_FAILURE`。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp_2_session_callbacks_set_on_invalid_frame_recv_callback（）”。
 */
typedef int (*nghttp2_on_invalid_frame_recv_callback)(
    nghttp2_session *session, const nghttp2_frame *frame, int lib_error_code,
    void *user_data);

/**
 * @functypedef
 *
 * 收到data帧中的数据块时调用回调函数。|stream_id|是此DATA帧所属的流id。|flags |是包含此数据块的DATA帧的标志``（标志&NGHTTP2_FLAG_END_STREAM）！=0“”不一定意味着该数据块是流中的最后一个数据块。您应该使用：type:`nghttp2_on_frame_recv_callback`来了解接收到的所有数据帧。|user_data|指针是传递给调用“nghttp2_session_client_new（）”或“nghttp 2_session_server_new（（）”的第三个参数。
 *
 * 如果应用程序使用“nghttp2_session_me_recv（）”，则它可以返回：enum:“nghttp2_ERR_PAUSE”以使“nghttp 2_session_mm_recv（（）”返回，而不处理进一步的输入字节。由|data|指向的内存将被保留，直到调用“nghttp2_session_mem_recv（）”或“nghttp 2_session_recv）”。应用程序必须保留用于生成|data|参数的输入字节，因为它可能指的是输入字节中包含的内存区域。
 *
 * 如果成功，此函数的实现必须返回0。如果返回非零，则将其视为致命错误，并且“nghttp2_session_recv（）”和“nghttp 2_session_me_recv（）”函数将立即返回：enum:`nghttp2_ERR_CALLBACK_FAILURE`。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp_2_session_callbacks_set_on_data_chunk_recv_callback（）”。
 */
typedef int (*nghttp2_on_data_chunk_recv_callback)(nghttp2_session *session,
                                                   uint8_t flags,
                                                   int32_t stream_id,
                                                   const uint8_t *data,
                                                   size_t len, void *user_data);

/**
 * @functypedef
 *
 * 在发送非DATA帧|帧|之前调用回调函数。|user_data|指针是传递给调用“nghttp2_session_client_new（）”或“nghttp 2_session_server_new（（）”的第三个参数。
 *
 * 如果成功，此函数的实现必须返回0。它还可以返回：enum:`NGHTTP2_ERR_CANCEL`以取消给定帧的传输。
 *
 * 如果在执行此回调时出现致命错误，则实现应返回：enum:`NGHTTP2_ERR_callback_FAILURE`，这将使`NGHTTP2_session_send（）`和`NGHTTP2_session_me_send（）`函数立即返回：enum:`NGHTTP2_ERR_CALL BACK_FAILORE`。
 *
 * 如果返回另一个值，则视为返回了：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。但是实现不应该依赖于此，因为库可以定义新的返回值来扩展其功能。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp2-session_callback _set_before_frame_send_callback（）”。
 */
typedef int (*nghttp2_before_frame_send_callback)(nghttp2_session *session,
                                                  const nghttp2_frame *frame,
                                                  void *user_data);

/**
 * @functypedef
 *
 * 在发送帧|frame |后调用回调函数。|user_data|指针是传递给调用“nghttp2_session_client_new（）”或“nghttp 2_session_server_new（（）”的第三个参数。
 *
 * 如果成功，此函数的实现必须返回0。如果返回非零，则将其视为致命错误，并且“nghttp2_session_send（）”和“nghttp 2_session_me_send（）”函数立即返回：enum:`nghttp2_ERR_CALLBACK_FAILURE`。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp_2_session_callbacks_set_onframe_send_callback（）”。
 */
typedef int (*nghttp2_on_frame_send_callback)(nghttp2_session *session,
                                              const nghttp2_frame *frame,
                                              void *user_data);

/**
 * @functypedef
 *
 * 由于错误，未发送非DATA帧|frame |后调用的回调函数。该错误由|lib_error_code|表示，它是在：type:`nghttp2_error`中定义的值之一。|user_data|指针是传递给调用“nghttp2_session_client_new（）”或“nghttp 2_session_server_new（（）”的第三个参数。
 *
 * 如果成功，此函数的实现必须返回0。如果返回非零，则将其视为致命错误，并且“nghttp2_session_send（）”和“nghttp 2_session_me_send（）”函数立即返回：enum:`nghttp2_ERR_CALLBACK_FAILURE`。
 *
 * `nghttp2_session_get_stream_user_data（）可用于获取相关数据。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp2-session_callback _set_on_frame_not_send_callback（）”。
 */
typedef int (*nghttp2_on_frame_not_send_callback)(nghttp2_session *session,
                                                  const nghttp2_frame *frame,
                                                  int lib_error_code,
                                                  void *user_data);

/**
 * @functypedef
 *
 * 当流|stream_id|关闭时调用回调函数。关闭的原因由|error_code|表示。|error_code|通常是：enum:`nghttp2_error_code`中的一个，但这不能保证。在“nghttp2_submit_request（）”或“nghttp 2_submit_headers（）”中指定的stream_user_data在该函数中仍然可用。|user_data|指针是传递给调用“nghttp2_session_client_new（）”或“nghttp 2_session_server_new（（）”的第三个参数。
 *
 * 对于处于保留状态的流，也会调用此函数。
 *
 * 如果成功，此函数的实现必须返回0。如果返回非零，则会将其视为致命错误，并且“nghttp2_session_recv（）”、“nghttp 2_session_me_recv（）”和“nghttp p_session_send（）”函数会立即返回：enum:`nghttp2_ERR_CALLBACK_FAILURE`。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp_2_session_callbacks_set_on_stream_close_callback（）”。
 */
typedef int (*nghttp2_on_stream_close_callback)(nghttp2_session *session,
                                                int32_t stream_id,
                                                uint32_t error_code,
                                                void *user_data);

/**
 * @functypedef
 *
 * 在HEADERS或PUSH_PROMISE中开始接收头块时调用回调函数。每个头名称/值对将由：type:`nghttp2_on_header_callback `发出。
 *
 * ``frame->hd.flags``可能没有设置：enum:`NGHTTP2_FLAG_END_HEADERS`标志，这表示涉及一个或多个连续帧。但是应用程序不需要关心这一点，因为无论CONTINIUATION帧如何，头名称/值对都是透明的。
 *
 * 如果“frame->hd.type==NGHTTP2_HEADERS`”和“frame->HEADERS.cat==NGHTTP2-HCAT_REQUEST”，服务器应用程序可能会创建一个对象来存储有关新流的信息。如果将|session|配置为服务器端，则``frame->headers.cat``是包含请求头的``NGHTTP2_HCAT_REQUEST``或包含尾部字段的```NGHTTP2_HCAT_headers``，并且在此回调中永远不会得到PUSH_PROMISE。
 *
 * 对于客户端应用程序，`frame->hd.type``是``NGHTTP2_HEADERS``或``NGHTTP2_PUSH_PROMISE``。在``NGHTTP2_HEADERS``的情况下，``frame->HEADERS.cat==NGHTTP2_HCAT_RESPONSE``表示它是第一个响应报头，但它可能是由1xx状态码指示的非最终响应。在这种情况下，可能有零个或多个HEADERS帧，其“帧->头端。cat==NGHTTP2_HCAT_HEADERS”具有非最终响应代码，最终客户端只得到一个HEADERS帧，“帧->头部。cat==NGHTTP2_HCCT_HEADERS”包含最终响应头端（非1xx状态代码）。尾部字段还具有不包含任何状态代码的``frame->headers.cat==NGHTTP2_HCAT_headers``。
 *
 * 返回：enum:`NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE`将通过发出带有：enum:`NGHTTP2_INTERNAL_ERROR`的RST_stream来关闭流（如果帧为PUSH_PROMISE，则为承诺流）。在这种情况下，不会调用：type:`nghttp2_on_header_callback`和：type:` nghttp2_on_frame_recv_callback`。如果需要不同的错误代码，请将“nghttp2_submit_rst_stream（）”与所需的错误代码一起使用，然后返回：enum:`nghttp2_ERR_TEMPORAL_CALLBACK_FAILURE`。再次使用``frame->push_promise。promised_stream_id``作为`nghttp2_submit_rst_stream（）`中的stream_id参数，如果帧是PUSH_PROMISE。
 *
 * 如果成功，此函数的实现必须返回0。它可以返回：enum:`NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE`以重置流（如果帧为PUSH_PROMISE，则为承诺流）。对于严重错误，它必须返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。如果返回另一个值，则视为返回了：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。如果返回了：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`，则`NGHTTP2_session_mem_recv（）`函数将立即返回：enum:` NGHTTP2_ERROR_CALLBACK_FAILURE'。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp_2_session_callbacks_set_on_begin_headers_callback（）”。
 */
typedef int (*nghttp2_on_begin_headers_callback)(nghttp2_session *session,
                                                 const nghttp2_frame *frame,
                                                 void *user_data);

/**
 * @functypedef
 *
 * 收到|frame |的标头名称/值对时调用回调函数。长度为|nameen|的|name|是标头名称。长度|valuelen|的|value|是标头值。|flags |是一个或多个类型的位或：“nghttp2_nv_flag”。
 *
 * 如果在|flags|中设置了：enum:`NGHTTP2_NV_FLAG_NO_INDEX`，则在将其转发到下一跳时，接收器不得对该名称/值对进行索引。更具体地说，在HPACK编码中必须使用“Literal Header Field never Indexed”表示。
 *
 * 调用此回调时，``frame->hd。类型“”是：enum:`NGHTTP2_HEADERS`或：enum:` NGHTTP2_PUSH_PROMISE`。使用此回调处理所有标头名称/值对，并且未检测到错误后，将调用：type:`nghttp2_on_frame_recv_callback`。如果解压缩时出错，则不会调用|frame|的：type:`nghttp2_on_frame_recv_callback`。
 *
 * |name|和|value|都保证以NULL结尾。|namelen|和|valuelen|不包含终端NULL。如果“nghttp2_option_set_no_http_messaging（）”与非零值一起使用，则在终止NULL之前，|name|或|value|中可能包含NULL字符。
 *
 * 请注意，除非使用“nghttp2_option_set_no_http_messaging（）”，否则nghttp2库会使用“nghttp 2_check_header_name（）”和“nghttp p_check_header.value（）”对|name|和|value|执行验证。除此之外，nghttp2还基于HTTP消息传递规则执行验证，这在：ref:`HTTP消息传递'部分中进行了简要解释。
 *
 * 如果应用程序使用“nghttp2_session_me_recv（）”，则它可以返回：enum:“nghttp2_ERR_PAUSE”以使“nghttp 2_session_mm_recv（（）”返回，而不处理进一步的输入字节。由|frame|、|name|和|value|参数指向的内存将保留，直到调用“nghttp2_session_mem_recv（）”或“nghttp 2_session_recv）”。应用程序必须保留用于生成这些参数的输入字节，因为它可能指的是输入字节中包含的内存区域。
 *
 * 返回：enum:`NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE`将通过发出带有：enum:`NGHTTP2_INTERNAL_ERROR`的RST_stream来关闭流（如果帧为PUSH_PROMISE，则为承诺流）。在这种情况下，不会调用：type:`nghttp2_on_header_callback`和：type:` nghttp2_on_frame_recv_callback`。如果需要不同的错误代码，请将“nghttp2_submit_rst_stream（）”与所需的错误代码一起使用，然后返回：enum:`nghttp2_ERR_TEMPORAL_CALLBACK_FAILURE`。再次使用``frame->push_promise。promised_stream_id``作为`nghttp2_submit_rst_stream（）`中的stream_id参数，如果帧是PUSH_PROMISE。
 *
 * 如果成功，此函数的实现必须返回0。它可以返回：enum:`NGHTTP2_ERR_PAUSE`或：enum:` NGHTTP2_ERROR_TEMPORAL_CALLBACK_FAILURE`。对于其他严重故障，它必须返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。如果返回其他非零值，则将其视为：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。如果返回了：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`，则`NGHTTP2_session_recv（）`和`NGHTTP2_session_me_recv（）`函数立即返回：enum:` NGHTTP2_ERROR_CALLBACK_FAILURE'。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp_2_session_callbacks_set_on_header_callback（）”。
 *
 * ..警告：：
 *
 *   应用程序应适当限制总缓冲区大小以存储传入的标头字段。如果没有它，对等端可能会发送大量的头字段或大型头字段，从而导致本地端点内存不足。由于HPACK的工作方式，对等方可以有效地做到这一点，而不需要自己使用太多内存。
 */
typedef int (*nghttp2_on_header_callback)(nghttp2_session *session,
                                          const nghttp2_frame *frame,
                                          const uint8_t *name, size_t namelen,
                                          const uint8_t *value, size_t valuelen,
                                          uint8_t flags, void *user_data);

/**
 * @functypedef
 *
 * 收到|frame |的标头名称/值对时调用回调函数。|name|是标头名称。|value|是标头值。|flags |是一个或多个类型的位或：“nghttp2_nv_flag”。
 *
 * 此回调的行为类似于：type:`nghttp2_on_header_callback `，只是|name|和|value|存储在引用计数缓冲区中。如果应用程序希望保留这些引用而不复制它们，请使用“nghttp2_rcbuf_increff（）”来增加它们的引用计数。如果应用程序调用了“nghttp2_rcbuf_encref（）”，则应用程序有责任调用“nghttp_2_rcbuf_deff（）”以避免内存泄漏。如果|session|是由“nghttp2_session_server_new3（）”或“nghttp 2_session_client_new3）”创建的，则释放内存的函数是属于mem参数的函数。只要这个自由函数还活着，|name|和|value|就可以在|session|被破坏后继续存在。
 */
typedef int (*nghttp2_on_header_callback2)(nghttp2_session *session,
                                           const nghttp2_frame *frame,
                                           nghttp2_rcbuf *name,
                                           nghttp2_rcbuf *value, uint8_t flags,
                                           void *user_data);

/**
 * @functypedef
 *
 * 收到|frame |的无效标头名称/值对时调用回调函数。
 *
 * 参数和行为类似于：type:`nghttp2_on_header_callback `。不同之处在于，只有在接收到无效的头名称/值对时才会调用此回调，如果未设置此回调，则将其视为流错误。只有无效的常规标头字段被传递到此回调。换句话说，无效的伪标头字段不会传递到此回调。同样，包含大写字母的头字段也会被视为错误，而不会将其传递给此回调。
 *
 * 仅当启用HTTP消息传递验证（默认情况下为启用状态，请参见“nghttp2_option_set_no_HTTP_messaging（）”）时，才会考虑此回调。
 *
 * 使用此回调，应用程序检查传入的无效字段，并且还可以通过返回：enum:`NGHTTP2_ERR_TEMPORAL_callback_FAILURE`来重置来自此回调的流。默认情况下，错误代码为：enum:`NGHTTP2_PROTOCOL_error`。要更改错误代码，除了返回：enum:`nghttp2_ERR_TEMPORAL_CALLBACK_FAILURE`之外，还可以使用所选错误代码调用`nghttp2_submit_rst_stream（）`。
 *
 * 如果返回0，则忽略标头字段，并且不重置流。
 */
typedef int (*nghttp2_on_invalid_header_callback)(
    nghttp2_session *session, const nghttp2_frame *frame, const uint8_t *name,
    size_t namelen, const uint8_t *value, size_t valuelen, uint8_t flags,
    void *user_data);

/**
 * @functypedef
 *
 * 收到|frame |的无效标头名称/值对时调用回调函数。
 *
 * 参数和行为类似于：type:`nghttp2_on_header_callback2`。不同之处在于，只有当接收到无效的头名称/值对时，才会调用此回调，如果未设置此回调，则会自动忽略此对。只有无效的常规标头字段被传递到此回调。换句话说，无效的伪标头字段不会传递到此回调。同样，包含大写字母的头字段也会被视为错误，而不会将其传递给此回调。
 *
 * 仅当启用HTTP消息传递验证（默认情况下为启用状态，请参见“nghttp2_option_set_no_HTTP_messaging（）”）时，才会考虑此回调。
 *
 * 使用此回调，应用程序检查传入的无效字段，并且还可以通过返回：enum:`NGHTTP2_ERR_TEMPORAL_callback_FAILURE`来重置来自此回调的流。默认情况下，错误代码为：enum:`NGHTTP2_INTERNAL_error`。要更改错误代码，除了返回：enum:`nghttp2_ERR_TEMPORAL_CALLBACK_FAILURE`之外，还可以使用所选错误代码调用`nghttp2_submit_rst_stream（）`。
 */
typedef int (*nghttp2_on_invalid_header_callback2)(
    nghttp2_session *session, const nghttp2_frame *frame, nghttp2_rcbuf *name,
    nghttp2_rcbuf *value, uint8_t flags, void *user_data);

/**
 * @functypedef
 *
 * 当库询问应用程序传输|frame |需要多少填充字节时调用回调函数。应用程序必须选择有效负载的总长度，包括[frame->hd.length，max_payloadlen]范围内的填充字节，包括在内。选择不在此范围内的数字将被视为：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。返回``frame->hd。长度“”表示不添加填充。返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`将使`NGHTTP2_session_send（）`和`NGHTTP2-session_me_send（）`函数立即返回：enum:`NGHTTP2-ERR_CALLBACK_FAILURE `。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp_2_session_callbacks_set_select_padding_callback（）”。
 */
typedef ssize_t (*nghttp2_select_padding_callback)(nghttp2_session *session,
                                                   const nghttp2_frame *frame,
                                                   size_t max_payloadlen,
                                                   void *user_data);

/**
 * @functypedef
 *
 * 当库希望获取最大数据长度以将数据发送到远程对等端时调用回调函数。此函数的实现应返回以下范围内的值。[1，min（|session_remote_window_size|，|stream_remote_windowssize|，|remote_max_frame_size|）]。如果返回的值大于此范围，则将使用最大允许值。返回小于此范围的值被视为：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。|frame_type|是为将来的扩展性而提供的，它标识要获取其长度的帧类型（请参见：type:`nghttp2_frame_type`）。当前支持的帧类型为：enum:`NGHTTP2_DATA`。
 *
 * 此回调可用于控制允许向远程端点发送的字节长度：type:`nghttp2_data_source_read_callback`。此回调是可选的。返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`将发出整个会话失败的信号。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp_2_session_callbacks_set_data_source_read_length_callback（）”。
 */
typedef ssize_t (*nghttp2_data_source_read_length_callback)(
    nghttp2_session *session, uint8_t frame_type, int32_t stream_id,
    int32_t session_remote_window_size, int32_t stream_remote_window_size,
    uint32_t remote_max_frame_size, void *user_data);

/**
 * @functypedef
 *
 * 收到帧头时调用回调函数。|hd|指向接收到的帧标头。
 *
 * 与：type:`nghttp2_on_frame_recv_callback`不同，当接收到CONTINUATION帧的帧头时，也将调用此回调。
 *
 * 如果同时设置了：type:`nghttp2_on_begin_frame_callback`和：type:'nghttp2_on_begin_headers_callback'，并且接收到headers或PUSH_PROMISE，则将首先调用：type:` nghttp2_on-begin_frame_callback`。
 *
 * 如果成功，此函数的实现必须返回0。如果返回非零值，则将其视为致命错误，并且“nghttp2_session_recv（）”和“nghttp 2_session_me_recv（）”函数立即返回：enum:`nghttp2_ERR_CALLBACK_FAILURE`。
 *
 * 要将此回调设置为：键入：“nghttp2_session_callbacks”，请使用“nghttp_2_session_callbacks_set_on_begin_frame_callback（）”。
 */
typedef int (*nghttp2_on_begin_frame_callback)(nghttp2_session *session,
                                               const nghttp2_frame_hd *hd,
                                               void *user_data);

/**
 * @functypedef
 *
 * 当接收到扩展帧有效载荷块时调用回调函数。|hd|指向帧标头。接收的块是长度为|len|的|data|。
 *
 * 如果成功，此函数的实现必须返回0。
 *
 * 要中止处理此扩展帧，请返回：enum:`NGHTTP2_ERR_CANCEL`。
 *
 * 如果发生致命错误，应用程序应返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。在这种情况下，“nghttp2_session_recv（）”和“nghttp2-session_me_recv（）”函数立即返回：enum:`nghttp2_ERR_CALLBACK_FAILURE`。如果返回其他值，则当前将它们视为：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。
 */
typedef int (*nghttp2_on_extension_chunk_recv_callback)(
    nghttp2_session *session, const nghttp2_frame_hd *hd, const uint8_t *data,
    size_t len, void *user_data);

/**
 * @functypedef
 *
 * 当库要求应用程序将扩展负载从其有线格式解包时调用回调函数。扩展负载已通过以下方式传递给应用程序：type:`nghttp2_on_extension_chunk_recv_callback`。帧标头已由库解包，并作为|hd|提供。
 *
 * 要接收扩展帧，应用程序必须使用“nghttp2_option_set_user_recv_extension_type（）”将所需的扩展帧类型告知库。
 *
 * 此函数的实现可能会在|payload |中存储解包后创建的对象的指针，并返回0。存储在|payload|中的指针对库是不透明的，并且库不拥有其指针|有效负载|初始化为“NULL”。|payload |可用作``frame->ext。有效负载``in:type:`nghttp2_on_frame_recv_callback`。所以，如果应用程序可以释放内存：键入：`nghttp2_on_frame_recv_callback`回调。当然，应用程序可以不使用|payload |，并使用自己的机制来处理扩展帧。
 *
 * 要中止处理此扩展帧，请返回：enum:`NGHTTP2_ERR_CANCEL`。
 *
 * 如果发生致命错误，应用程序应返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。在这种情况下，“nghttp2_session_recv（）”和“nghttp2-session_me_recv（）”函数立即返回：enum:`nghttp2_ERR_CALLBACK_FAILURE`。如果返回其他值，则当前将它们视为：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。
 */
typedef int (*nghttp2_unpack_extension_callback)(nghttp2_session *session,
                                                 void **payload,
                                                 const nghttp2_frame_hd *hd,
                                                 void *user_data);

/**
 * @functypedef
 *
 * 当库要求应用程序以其有线格式打包扩展负载时调用回调函数。帧标头将按库打包。应用程序必须仅打包有效负载``帧->扩展。有效载荷“”是作为有效载荷参数传递给“nghttp2_submit_extension（）”的对象。应用程序必须将扩展负载打包到其容量|len|字节的|buf|。|len|至少为16KiB。
 *
 * 此函数的实现应在成功时返回写入|buf|的字节数。
 *
 * 要中止处理此扩展帧，请返回：enum:`NGHTTP2_ERR_CANCEL`，并调用：type:`NGHTTP2_on_frame_not_send_callback`。
 *
 * 如果发生致命错误，应用程序应返回：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。在这种情况下，“nghttp2_session_send（）”和“nghttp2-session_me_send（）”函数立即返回：enum:`nghttp2_ERR_CALLBACK_FAILURE`。如果返回其他值，则当前将它们视为：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。如果返回值严格大于|len|，则将其视为：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。
 */
typedef ssize_t (*nghttp2_pack_extension_callback)(nghttp2_session *session,
                                                   uint8_t *buf, size_t len,
                                                   const nghttp2_frame *frame,
                                                   void *user_data);

/**
 * @functypedef
 *
 * 当库提供供人类使用的错误消息时调用回调函数。此回调仅用于调试目的。|msg|通常是长度为|len|的以NULL结尾的字符串|len|不包含sentinel NULL字符。
 *
 * 此函数已弃用。新应用程序应使用：type:`nghttp2_error_callback2`。
 *
 * 错误消息的格式可能在nghttp2库版本之间发生变化。应用程序不应依赖于特定的格式。
 *
 * 通常，应用程序应该从此回调返回0。如果在此回调中执行某些操作时发生致命错误，应用程序应返回：enum:`NGHTTP2_ERR_callback_FAILURE`。在这种情况下，库将立即返回返回值：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。当前，若此回调返回非零值，则它们将被视为：enum:`NGHTTP2_ERR_callback_FAILURE`，但应用程序不应依赖此详细信息。
 */
typedef int (*nghttp2_error_callback)(nghttp2_session *session, const char *msg,
                                      size_t len, void *user_data);

/**
 * @functypedef
 *
 * 当库提供错误代码和消息时调用回调函数。此回调仅用于调试目的|lib_error_code|是enum:`nghttp2_error`中定义的错误代码之一。|msg|通常是以NULL结尾的字符串，长度为|len|，供人使用|len|不包含sentinel NULL字符。
 *
 * 错误消息的格式可能在nghttp2库版本之间发生变化。应用程序不应依赖于特定的格式。
 *
 * 通常，应用程序应该从此回调返回0。如果在此回调中执行某些操作时发生致命错误，应用程序应返回：enum:`NGHTTP2_ERR_callback_FAILURE`。在这种情况下，库将立即返回返回值：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`。当前，若此回调返回非零值，则它们将被视为：enum:`NGHTTP2_ERR_callback_FAILURE`，但应用程序不应依赖此详细信息。
 */
typedef int (*nghttp2_error_callback2)(nghttp2_session *session,
                                       int lib_error_code, const char *msg,
                                       size_t len, void *user_data);

struct nghttp2_session_callbacks;

/**
 * @struct
 *
 * 类型：“nghttp2_session”的回调函数。此结构的详细信息有意隐藏在公共API中。
 */
typedef struct nghttp2_session_callbacks nghttp2_session_callbacks;

/**
 * @function
 *
 * 使用NULL值初始化|*callback_ptr|。
 *
 * 初始化多个：type:`nghttp2_session`对象时，可以使用已初始化的对象。
 *
 * 应用程序使用完此对象后，可以使用“nghttp2_session_callbacks_dl（）”释放内存。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int
nghttp2_session_callbacks_new(nghttp2_session_callbacks **callbacks_ptr);

/**
 * @function
 *
 * 释放为|回调|分配的所有资源。如果|callbacks|为“NULL”，则此函数不执行任何操作。
 */
NGHTTP2_EXTERN void
nghttp2_session_callbacks_del(nghttp2_session_callbacks *callbacks);

/**
 * @function
 *
 * 设置会话要向远程对等方发送数据时调用的回调函数。如果应用程序仅使用“nghttp2_session_mmem_send（）”来序列化要传输的数据，则不需要此回调。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_send_callback(
    nghttp2_session_callbacks *cbs, nghttp2_send_callback send_callback);

/**
 * @function
 *
 * 设置会话希望从远程对等方接收数据时调用的回调函数。如果应用程序仅使用“nghttp2_session_mem_recv（）”来处理接收的数据，则不需要此回调。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_recv_callback(
    nghttp2_session_callbacks *cbs, nghttp2_recv_callback recv_callback);

/**
 * @function
 *
 * 设置接收到帧时由“nghttp2_session_recv（）”和“nghttp 2_session_me_recv（）”调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_frame_recv_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_frame_recv_callback on_frame_recv_callback);

/**
 * @function
 *
 * 设置当接收到无效的非DATA帧时，由“nghttp2_session_recv（）”和“nghttp 2_session_me_recv（）”调用的回调函数。
 */
NGHTTP2_EXTERN void
nghttp2_session_callbacks_set_on_invalid_frame_recv_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_invalid_frame_recv_callback on_invalid_frame_recv_callback);

/**
 * @function
 *
 * 设置接收data帧中的数据块时调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_data_chunk_recv_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_data_chunk_recv_callback on_data_chunk_recv_callback);

/**
 * @function
 *
 * 设置在发送非DATA帧之前调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_before_frame_send_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_before_frame_send_callback before_frame_send_callback);

/**
 * @function
 *
 * 设置发送帧后调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_frame_send_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_frame_send_callback on_frame_send_callback);

/**
 * @function
 *
 * 设置由于错误而未发送非DATA帧时调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_frame_not_send_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_frame_not_send_callback on_frame_not_send_callback);

/**
 * @function
 *
 * 设置流关闭时调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_stream_close_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_stream_close_callback on_stream_close_callback);

/**
 * @function
 *
 * 设置在HEADERS或PUSH_PROMISE中开始接收头块时调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_begin_headers_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_begin_headers_callback on_begin_headers_callback);

/**
 * @function
 *
 * 设置接收到标头名称/值对时调用的回调函数。如果“nghttp2_session_callback_set_on_header_callback（）”和“nghttp 2_session_ccallback_set_on_header_callback2（）”都用于设置回调，则后者具有优先权。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_header_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_header_callback on_header_callback);

/**
 * @function
 *
 * 设置接收到标头名称/值对时调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_header_callback2(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_header_callback2 on_header_callback2);

/**
 * @function
 *
 * 设置接收到无效标头名称/值对时调用的回调函数。如果“nghttp2_session_callbacks_set_on_invalid_header_callback（）”和“nghttp 2_session_ccallbacks_set_on_invalid_header_callback2（）”都用于设置回调，则后者优先。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_invalid_header_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_invalid_header_callback on_invalid_header_callback);

/**
 * @function
 *
 * 设置接收到无效标头名称/值对时调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_invalid_header_callback2(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_invalid_header_callback2 on_invalid_header_callback2);

/**
 * @function
 *
 * 设置当库询问应用程序传输给定帧需要多少填充字节时调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_select_padding_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_select_padding_callback select_padding_callback);

/**
 * @function
 *
 * 设置回调函数以确定：type:`nghttp2_data_source_read_callback`中允许的长度。
 */
NGHTTP2_EXTERN void
nghttp2_session_callbacks_set_data_source_read_length_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_data_source_read_length_callback data_source_read_length_callback);

/**
 * @function
 *
 * 设置收到帧头时调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_on_begin_frame_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_begin_frame_callback on_begin_frame_callback);

/**
 * @function
 *
 * 设置在：type:`NGHTTP2_DATA_source_read_callback`中使用：enum:`NGHTTP2_DATA_FLAG_NO_COOPY`时调用的回调函数，以避免数据复制。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_send_data_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_send_data_callback send_data_callback);

/**
 * @function
 *
 * 设置当库要求应用程序以有线格式打包扩展帧负载时调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_pack_extension_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_pack_extension_callback pack_extension_callback);

/**
 * @function
 *
 * 设置当库要求应用程序从wire格式解包扩展帧负载时调用的回调函数。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_unpack_extension_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_unpack_extension_callback unpack_extension_callback);

/**
 * @function
 *
 * 设置接收到扩展帧负载块时调用的回调函数。
 */
NGHTTP2_EXTERN void
nghttp2_session_callbacks_set_on_extension_chunk_recv_callback(
    nghttp2_session_callbacks *cbs,
    nghttp2_on_extension_chunk_recv_callback on_extension_chunk_recv_callback);

/**
 * @function
 *
 * 设置当库向应用程序通知错误消息时调用的回调函数。
 *
 * 此函数已弃用。新应用程序应使用“nghttp2_session_callback_set_error_callback2（）”。
 *
 * 如果同时设置了：type:`nghttp2_error_callback`和：type:'nghttp2_error _callback2'，则后者优先。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_error_callback(
    nghttp2_session_callbacks *cbs, nghttp2_error_callback error_callback);

/**
 * @function
 *
 * 设置当库告诉应用程序错误代码和消息时调用的回调函数。
 *
 * 如果同时设置了：type:`nghttp2_error_callback`和：type:'nghttp2_error _callback2'，则后者优先。
 */
NGHTTP2_EXTERN void nghttp2_session_callbacks_set_error_callback2(
    nghttp2_session_callbacks *cbs, nghttp2_error_callback2 error_callback2);

/**
 * @functypedef
 *
 * 自定义内存分配器以替换malloc（）。|mem_user_data|是：type:`nghttp2_mem`结构的mem_user_data成员。
 */
typedef void *(*nghttp2_malloc)(size_t size, void *mem_user_data);

/**
 * @functypedef
 *
 * 要替换free（）的自定义内存分配器。|mem_user_data|是：type:`nghttp2_mem`结构的mem_user_data成员。
 */
typedef void (*nghttp2_free)(void *ptr, void *mem_user_data);

/**
 * @functypedef
 *
 * 自定义内存分配器以替换calloc（）。|mem_user_data|是：type:`nghttp2_mem`结构的mem_user_data成员。
 */
typedef void *(*nghttp2_calloc)(size_t nmemb, size_t size, void *mem_user_data);

/**
 * @functypedef
 *
 * 替换realloc（）的自定义内存分配器。|mem_user_data|是：type:`nghttp2_mem`结构的mem_user_data成员。
 */
typedef void *(*nghttp2_realloc)(void *ptr, size_t size, void *mem_user_data);

/**
 * @struct
 *
 * 自定义内存分配器函数和用户定义的指针。|mem_user_data|成员被传递给每个分配器函数。例如，这可以用于实现每个会话的内存池。
 *
 * 在下面的示例代码中，`my_malloc``、`my_free ``、` my_calloc``和`my_realloc```分别替换了标准分配器`malloc`、`free`、`calloc `和`realloc`：
 *
 *     void*my_malloc_cb（size_t大小，void*mem_user_data）{return my_malloc（大小）；}
 *
 *     void my_free_cb（void*ptr，void*mem_user_data）｛my_free（ptr）；｝
 *
 *     void*my_calloc_cb（size_t nmemb，size_t size，void*mem_user_data）｛return my_calloc（nmemb、size）；｝
 *
 *     void*my_realloc_cb（void*ptr，size_t size，void*mem_user_data）{return my_realloc（ptr，size）；}
 *
 *     void session_new（）｛nghttp2_session session；nghttp2_session_callbacks callbacks；nghttp 2_mem mem＝｛NULL，my_malloc_cb，my_free_cb，my_calloc_cb和my_realloc_cb｝；
 *
 *       ...
 *
 *       nghttp2_session_client_new3（&session，回调，NULL，NULL，&mem）；
 *
 *       ... }
 */
typedef struct {
  /**
   * 任意用户提供的数据。这将传递给每个分配器函数。
   */
  void *mem_user_data;
  /**
   * 替换malloc（）的自定义分配器函数。
   */
  nghttp2_malloc malloc;
  /**
   * 替换free（）的自定义分配器函数。
   */
  nghttp2_free free;
  /**
   * 替换calloc（）的自定义分配器函数。
   */
  nghttp2_calloc calloc;
  /**
   * 替换realloc（）的自定义分配器函数。
   */
  nghttp2_realloc realloc;
} nghttp2_mem;

struct nghttp2_option;

/**
 * @struct
 *
 * 配置选项：类型：`nghttp2_session`。此结构的详细信息有意隐藏在公共API中。
 */
typedef struct nghttp2_option nghttp2_option;

/**
 * @function
 *
 * 使用默认值初始化|*option_ptr|。
 *
 * 应用程序使用完此对象后，可以使用“nghttp2_option_del（）”释放内存。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int nghttp2_option_new(nghttp2_option **option_ptr);

/**
 * @function
 *
 * 释放为|选项|分配的所有资源。如果|option|为``NULL ``，则此函数不执行任何操作。
 */
NGHTTP2_EXTERN void nghttp2_option_del(nghttp2_option *option);

/**
 * @function
 *
 * 此选项阻止库自动发送连接的WINDOW_UPDATE。如果此选项设置为非零，则在应用程序调用“nghttp2_session_customer（）”以指示消耗的数据量之前，库不会发送WINDOW_UPDATE for DATA。不要为此使用“nghttp2_submit_window_update（）”。默认情况下，此选项设置为零。
 */
NGHTTP2_EXTERN void
nghttp2_option_set_no_auto_window_update(nghttp2_option *option, int val);

/**
 * @function
 *
 * 此选项设置远程端点的SETTINGS_MAX_CONCURRENT_STREAMS值，就像在SETTINGS帧中接收到一样。如果不指定此选项，则传出并发流的最大数量最初限制为100，以避免本地端点在从远程端点接收初始SETTINGS帧之前提交大量请求时出现问题，因为立即将它们发送到远程端点可能会导致拒绝某些请求。当本地端点从远程端点接收到初始SETTINGS帧时，该值将被覆盖，或者被覆盖为SETTINGS_MAX_CONCURRENT_STREAMS中通告的值，或者如果没有通告，则被覆盖为默认值（无限制）。
 */
NGHTTP2_EXTERN void
nghttp2_option_set_peer_max_concurrent_streams(nghttp2_option *option,
                                               uint32_t val);

/**
 * @function
 *
 * 默认情况下，nghttp2库（如果配置为服务器）需要前24个字节的客户端魔法字节字符串（magic）。在大多数情况下，这将简化服务器的实现。但有时服务器可能希望基于明文通信的前几个字节来检测应用程序协议。
 *
 * 如果此选项与非零|val|一起使用，nghttp2库不处理MAGIC。它仍然检查以下SETTINGS（设置）帧。这意味着应用程序应该自己处理MAGIC。
 *
 * 如果未使用此选项或使用零值，则如果MAGIC不匹配：macro:`NGHTTP2_CLIENT_MAGIC`、`NGHTTP2_session_recv（）`和`NGHTTP2_session_member_recv（）`将返回错误：enum:`NGHTTP2_ERR_BAD_CLIENT_MAGIC `，这是致命错误。
 */
NGHTTP2_EXTERN void
nghttp2_option_set_no_recv_client_magic(nghttp2_option *option, int val);

/**
 * @function
 *
 * 默认情况下，nghttp2库强制执行“HTTP/2规范”第8节中描述的HTTP消息传递规则的子集<https://tools.ietf.org/html/rfc7540#section-8>`_. 有关详细信息，请参阅：ref:`http messaging`部分。对于使用nghttp2库作为非HTTP用途的应用程序，请将|val|设为非零以禁用此强制。请注意，禁用此功能不会改变HTTP的基本客户端和服务器模型。也就是说，即使禁用了验证，也只有客户端可以发送请求。
 */
NGHTTP2_EXTERN void nghttp2_option_set_no_http_messaging(nghttp2_option *option,
                                                         int val);

/**
 * @function
 *
 * RFC 7540没有对传入的保留流的数量实施任何限制（在RFC 7540术语中，流处于保留（远程）状态）。这只影响客户端，因为只有服务器才能推送流。恶意服务器可以推送任意数量的流，并使客户端的内存耗尽。此选项可以设置此类传入流的最大数量，以避免可能的内存耗尽。如果设置了此选项，并且推送的流在接收时自动关闭，如果超过给定的限制，则不调用用户提供的回调。默认值为200。如果会话配置为服务器端，则此选项无效。服务器可以控制要推送的流的数量。
 */
NGHTTP2_EXTERN void
nghttp2_option_set_max_reserved_remote_streams(nghttp2_option *option,
                                               uint32_t val);

/**
 * @function
 *
 * 设置应用程序愿意使用用户定义的回调处理的扩展帧类型（请参见：type:`nghttp2_on_extension_chun_recv_callback`和：type:` nghttp2_unpack_extension_callback`）。|类型|是扩展帧类型，必须严格大于0x9。否则，此函数不执行任何操作。应用程序可以多次调用此函数来设置要接收的多个帧类型。如果应用程序只发送扩展帧，则不必调用此函数。
 */
NGHTTP2_EXTERN void
nghttp2_option_set_user_recv_extension_type(nghttp2_option *option,
                                            uint8_t type);

/**
 * @function
 *
 * 使用内置处理程序设置应用程序愿意接收的扩展帧类型。|类型|是要接收的扩展帧类型，必须严格大于0x9。否则，此函数将不执行任何操作。应用程序可以多次调用此函数来设置要接收的多个帧类型。如果应用程序只发送扩展帧，则不必调用此函数。
 *
 * 如果将同一帧类型传递给`nghttp2_option_set_builting_recv_extension_type（）`和`nghttp2-option_set_user_recv_extension_type（）'，则后者优先。
 */
NGHTTP2_EXTERN void
nghttp2_option_set_builtin_recv_extension_type(nghttp2_option *option,
                                               uint8_t type);

/**
 * @function
 *
 * 当接收到未设置ACK标志的PING帧时，此选项阻止库自动发送设置了ACK标志的PING帧。如果此选项设置为非零，则库将不会发送PING帧，并在传入PING帧的响应中设置ACK标志。应用程序可以使用“nghttp2_submit_PING（）”和：enum:“nghttp2_flag_ACK”作为标志参数发送设置了ACK标志的PING帧。
 */
NGHTTP2_EXTERN void nghttp2_option_set_no_auto_ping_ack(nghttp2_option *option,
                                                        int val);

/**
 * @function
 *
 * 此选项设置要发送的标头块的最大长度（每一HEADERS帧一组标头字段）。使用“nghttp2_hd_deflate_bound（）”计算给定标头字段集的长度。默认值为64KiB。如果应用程序试图发送大于此限制的标头字段，则帧传输失败，错误代码为：enum:`NGHTTP2_ERR_frame_SIZE_error`。
 */
NGHTTP2_EXTERN void
nghttp2_option_set_max_send_header_block_length(nghttp2_option *option,
                                                size_t val);

/**
 * @function
 *
 * 此选项设置缩小标题字段的最大动态表大小。默认值为4KiB。在HTTP/2中，收缩头块的接收方可以指定最大动态表大小。实际最大大小是指定的接收器大小和此选项值的最小值。
 */
NGHTTP2_EXTERN void
nghttp2_option_set_max_deflate_dynamic_table_size(nghttp2_option *option,
                                                  size_t val);

/**
 * @function
 *
 * 此选项可防止库保留关闭的流以维护优先级树。如果此选项设置为非零，应用程序可以完全丢弃关闭的流以节省内存。
 */
NGHTTP2_EXTERN void nghttp2_option_set_no_closed_streams(nghttp2_option *option,
                                                         int val);

/**
 * @function
 *
 * 此函数设置：type:`nghttp2_session`对象中保留的传出SETTINGS ACK和PING ACK帧的最大数量。如果保留了超过这些帧，则认为对等方行为不端，会话将关闭。默认值为1000。
 */
NGHTTP2_EXTERN void nghttp2_option_set_max_outbound_ack(nghttp2_option *option,
                                                        size_t val);

/**
 * @function
 *
 * 此函数设置每个SETTINGS帧可接受的最大SETTINGS条目数。如果收到的条目多于这些，则认为该对等方行为不端，会话将关闭。默认值为32。
 */
NGHTTP2_EXTERN void nghttp2_option_set_max_settings(nghttp2_option *option,
                                                    size_t val);

/**
 * @function
 *
 * 初始化|*session_ptr|以供客户端使用。|callbacks|的所有成员都复制到|session_ptr|。因此，|session_ptr|不存储|callbacks|。|user_data|是用户提供的任意数据，将传递给回调函数。
 *
 * 必须指定：type:`nghttp2_send_callback`。如果应用程序代码使用“nghttp2_session_recv（）”，则必须指定：type:`nghttp2_recv_callback”。|callbacks|的其他成员可以是“NULL”。
 *
 * 如果此函数失败，|*session_ptr|将保持不变。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int
nghttp2_session_client_new(nghttp2_session **session_ptr,
                           const nghttp2_session_callbacks *callbacks,
                           void *user_data);

/**
 * @function
 *
 * 初始化|*session_ptr|以供服务器使用。|callbacks|的所有成员都复制到|session_ptr|。因此，|session_ptr|不存储|callbacks|。|user_data|是用户提供的任意数据，将传递给回调函数。
 *
 * 必须指定：type:`nghttp2_send_callback`。如果应用程序代码使用“nghttp2_session_recv（）”，则必须指定：type:`nghttp2_recv_callback”。|callbacks|的其他成员可以是“NULL”。
 *
 * 如果此函数失败，|*session_ptr|将保持不变。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int
nghttp2_session_server_new(nghttp2_session **session_ptr,
                           const nghttp2_session_callbacks *callbacks,
                           void *user_data);

/**
 * @function
 *
 * 类似于“nghttp2_session_client_new（）”，但在|选项|中指定了其他选项。
 *
 * |选项|可以是“NULL”，调用等效于“nghttp2_session_client_new（）”。
 *
 * 此函数不具有所有权|选项|。应用程序负责在使用完对象后释放|选项|。
 *
 * 此函数返回后，库代码未引用|option|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int
nghttp2_session_client_new2(nghttp2_session **session_ptr,
                            const nghttp2_session_callbacks *callbacks,
                            void *user_data, const nghttp2_option *option);

/**
 * @function
 *
 * 类似于“nghttp2_session_server_new（）”，但在|选项|中指定了其他选项。
 *
 * |选项|可以是“NULL”，调用等效于“nghttp2_session_server_new（）”。
 *
 * 此函数不具有所有权|选项|。应用程序负责在使用完对象后释放|选项|。
 *
 * 此函数返回后，库代码未引用|option|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int
nghttp2_session_server_new2(nghttp2_session **session_ptr,
                            const nghttp2_session_callbacks *callbacks,
                            void *user_data, const nghttp2_option *option);

/**
 * @function
 *
 * 类似于“nghttp2_session_client_new2（）”，但在|mem|中指定了其他自定义内存分配器。
 *
 * |mem|可以是“NULL”，调用等效于“nghttp2_session_client_new2（）”。
 *
 * 此函数不具有所有权|mem|。应用程序负责释放|mem|。
 *
 * 此函数返回后，库代码不引用|mem|指针，因此应用程序可以安全地释放它。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int nghttp2_session_client_new3(
    nghttp2_session **session_ptr, const nghttp2_session_callbacks *callbacks,
    void *user_data, const nghttp2_option *option, nghttp2_mem *mem);

/**
 * @function
 *
 * 类似于“nghttp2_session_server_new2（）”，但在|mem|中指定了其他自定义内存分配器。
 *
 * |mem|可以是“NULL”，调用等效于“nghttp2_session_server_new2（）”。
 *
 * 此函数不具有所有权|mem|。应用程序负责释放|mem|。
 *
 * 此函数返回后，库代码不引用|mem|指针，因此应用程序可以安全地释放它。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int nghttp2_session_server_new3(
    nghttp2_session **session_ptr, const nghttp2_session_callbacks *callbacks,
    void *user_data, const nghttp2_option *option, nghttp2_mem *mem);

/**
 * @function
 *
 * 释放为|会话|分配的所有资源。如果|session|为“NULL”，则此函数不执行任何操作。
 */
NGHTTP2_EXTERN void nghttp2_session_del(nghttp2_session *session);

/**
 * @function
 *
 * 向远程对等端发送挂起的帧。
 *
 * 此函数从出站队列中检索优先级最高的帧，并将其发送到远程对等端。它会尽可能多地执行此操作，直到用户回调：type:`nghttp2_send_callback`返回：enum:`nghttp2_ERR_WOULDBLOCK`或出站队列变为空。此函数调用在初始化|session|时传递的几个回调函数。下面是一个简单的时间图，它告诉调用每个回调的时间：
 *
 * 1.从出站队列获取要发送的下一帧。
 *
 * 2.准备传输帧。
 *
 * 3.如果由于某些先决条件不满足而无法发送控制帧（例如，在GOAWAY之后无法发送请求HEADERS），则调用：type:`nghttp2_on_frame_not_send_callback`。中止以下步骤。
 *
 * 4.如果帧是HEADERS、PUSH_PROMISE或DATA，则调用：type:`nghttp2_select_padding_callback`。
 *
 * 5.如果帧是请求HEADERS，则在此处打开流。
 *
 * 6.：类型：调用“nghttp2_before_frame_send_callback”。
 *
 * 7.如果：enum:`NGHTTP2_ERR_CANCEL`从：type:`NGHTTP2_before_frame_send_callback`返回，则取消当前帧传输，并调用：type:` NGHTTP2_on_frame_not_send_cllback`。中止以下步骤。
 *
 * 8.：类型：“nghttp2_send_callback”被调用一次或多次以发送帧。
 *
 * 9.：类型：调用“nghttp2_on_frame_send_callback”。
 *
 * 10.如果帧的传输触发了流的关闭，则流被关闭，并调用：type:`nghttp2_on_stream_close_callback `。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`回调函数失败。
 */
NGHTTP2_EXTERN int nghttp2_session_send(nghttp2_session *session);

/**
 * @function
 *
 * 返回要发送的序列化数据。
 *
 * 此函数的行为类似于“nghttp2_session_send（）”，只是它不使用：type:`nghttp2_send_callback`来传输数据。相反，它将指向序列化数据的指针分配给|data_ptr|并返回其长度。其他回调的调用方式与“nghttp2_session_send（）”中的调用方式相同。
 *
 * 如果没有可发送的数据，则此函数返回0。
 *
 * 此函数不能在一次调用中返回所有序列化数据。要获取所有数据，请重复调用此函数，直到它返回0或一个负错误代码。
 *
 * 分配的|*data_ptr|在下一次调用“nghttp2_session_member_send（）”或“nghttp 2_session_send（）”之前有效。
 *
 * 调用者必须在发送下一个数据块之前发送所有数据。
 *
 * 如果成功，此函数将返回|data_ptr|所指向的数据长度，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 *
 * ..注：
 *
 *   此函数可能产生非常小的字节字符串。如果是这种情况，并且应用程序禁用了Nagle算法（`TCP_NODELAY`），那么写这个小块会导致非常小的数据包，而且效率非常低。应用程序应负责在必要时缓冲小数据块，以避免这种情况。
 */
NGHTTP2_EXTERN ssize_t nghttp2_session_mem_send(nghttp2_session *session,
                                                const uint8_t **data_ptr);

/**
 * @function
 *
 * 从远程对等端接收帧。
 *
 * 此函数接收尽可能多的帧，直到用户回调：type:`nghttp2_recv_callback `返回：enum:`nghttp2_ERR_WOULDBLOCK`。此函数调用在初始化|session|时传递的几个回调函数。下面是一个简单的时间图，它告诉调用每个回调的时间：
 *
 * 1.：类型：“nghttp2_recv_callback”被调用一次或多次以接收帧头。
 *
 * 2.当接收到帧头时，调用：type:`nghttp2_on_begin_frame_callback`。
 *
 * 3.如果帧是DATA帧：
 *
 *    1.：类型：调用“nghttp2_recv_callback”以接收DATA负载。对于每个数据块，调用：type:`nghttp2_on_data_chunk_recv_callback`。
 *
 *    2.如果完全接收到一个DATA帧，则调用：type:`nghttp2_on_frame_recv_callback`。如果帧的接收触发流的关闭，则调用：type:`nghttp2_on_stream_close_callback `。
 *
 * 4.如果帧是控制帧：
 *
 *    1.：类型：“nghttp2_recv_callback”被调用一次或多次以接收整个帧。
 *
 *    2.如果接收到的帧有效，则采取以下动作。如果帧是HEADERS或PUSH_PROMISE，则调用：type:`nghttp2_on_begin_HEADERS_callback`。然后：为每个头名称/值对调用类型：“nghttp2_on_header_callback”。对于无效的头字段，调用：type:`nghttp2_on_invalid_header_callback `。成功发出所有名称/值对后，将调用：type:`nghttp2_on_frame_recv_callback`。对于其他帧，将调用：type:`nghttp2_on_frame_recv_callback`。如果帧的接收触发流的关闭，则调用：type:`nghttp2_on_stream_close_callback `。
 *
 *    3.如果接收到的帧被解包但被解释为无效，则调用：type:`nghttp2_on_invalid_frame_recv_callback`。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_EOF`远程对等端确实在连接上关闭。：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`回调函数失败。：enum:`NGHTTP2_ERR_BAD_CLIENT_MAGIC`检测到无效的客户端魔法。仅当|session|被配置为服务器并且“nghttp2_option_set_no_recv_client_magic（）”未与非零值一起使用时，才会返回此错误。：enum:`NGHTTP2_ERR_FLOODED`在此HTTP/2会话中检测到溢出，必须关闭它。这很可能是由于同伴的不当行为造成的。
 */
NGHTTP2_EXTERN int nghttp2_session_recv(nghttp2_session *session);

/**
 * @function
 *
 * 将数据|in|作为远程端点的输入进行处理。|inlen|表示|in|中的字节数。
 *
 * 此函数的行为类似于“nghttp2_session_recv（）”，只是它不使用：type:`nghttp2_recv_callback `来接收数据；|in|是调用此函数的唯一数据。如果处理了所有字节，则此函数返回。其他回调的调用方式与“nghttp2_session_recv（）”中的调用方式相同。
 *
 * 在当前实现中，此函数始终尝试处理所有输入数据，除非发生错误或：enum:`NGHTTP2_ERR_PAUSE`从：type:`NGHTTP2_on_header_callback`或：type:` NGHTTP2_on_data_chunk_recv_callback`返回。如果使用：enum:`NGHTTP2_ERR_PAUSE`，则返回值包括用于为回调生成数据或帧的字节数。
 *
 * 此函数返回已处理的字节数或以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_CALLBACK_FAILURE`回调函数失败。：enum:`NGHTTP2_ERR_BAD_CLIENT_MAGIC`检测到无效的客户端魔法。仅当|session|被配置为服务器并且“nghttp2_option_set_no_recv_client_magic（）”未与非零值一起使用时，才会返回此错误。：enum:`NGHTTP2_ERR_FLOODED`在此HTTP/2会话中检测到溢出，必须关闭它。这很可能是由于同伴的不当行为造成的。
 */
NGHTTP2_EXTERN ssize_t nghttp2_session_mem_recv(nghttp2_session *session,
                                                const uint8_t *in,
                                                size_t inlen);

/**
 * @function
 *
 * 将流|stream_id|中先前延迟的DATA帧放回出站队列。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_INVALID_ARGUMENT`流不存在；或不存在延迟数据。：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int nghttp2_session_resume_data(nghttp2_session *session,
                                               int32_t stream_id);

/**
 * @function
 *
 * 如果|session|希望从远程对等方接收数据，则返回非零值。
 *
 * 如果`nghttp2_session_want_read（）`和`nghttp2-session_want_write（）`都返回0，则应用程序应断开连接。
 */
NGHTTP2_EXTERN int nghttp2_session_want_read(nghttp2_session *session);

/**
 * @function
 *
 * 如果|session|要向远程对等方发送数据，则返回非零值。
 *
 * 如果`nghttp2_session_want_read（）`和`nghttp2-session_want_write（）`都返回0，则应用程序应断开连接。
 */
NGHTTP2_EXTERN int nghttp2_session_want_write(nghttp2_session *session);

/**
 * @function
 *
 * 返回流|stream_id|的stream_user_data。stream_user_data由“nghttp2_submit_request（）”、“nghttp 2_submit_headers（）”或“nghttp 2-session_set_stream_user_data（）”提供。除非使用“nghttp2_session_set_stream_user_data（）”进行设置，否则如果流由远程端点启动，则stream_user_data始终为“NULL”。如果流不存在，则此函数返回“NULL”。
 */
NGHTTP2_EXTERN void *
nghttp2_session_get_stream_user_data(nghttp2_session *session,
                                     int32_t stream_id);

/**
 * @function
 *
 * 将|stream_user_data|设置为|stream_id|表示的流。如果流用户数据已设置为流，则将其替换为|stream_user_data|。在|stream_user_data|中指定“NULL”是有效的，这会使关联的数据指针无效。
 *
 * 将|stream_user_data|设置为PUSH_PROMISE帧保留的流是有效的。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_INVALID_ARGUMENT`流不存在
 */
NGHTTP2_EXTERN int
nghttp2_session_set_stream_user_data(nghttp2_session *session,
                                     int32_t stream_id, void *stream_user_data);

/**
 * @function
 *
 * 将|user_data|设置为|session|，覆盖在“nghttp2_session_client_new（）”或“nghttp 2_session_server_new（”中指定的现有用户数据。
 */
NGHTTP2_EXTERN void nghttp2_session_set_user_data(nghttp2_session *session,
                                                  void *user_data);

/**
 * @function
 *
 * 返回出站队列中的帧数。这不包括延迟的DATA帧。
 */
NGHTTP2_EXTERN size_t
nghttp2_session_get_outbound_queue_size(nghttp2_session *session);

/**
 * @function
 *
 * 返回流|stream_id|在没有WINDOW_UPDATE传输的情况下接收的DATA有效负载的字节数。可以通过“nghttp2_submit_window_update（）”调整本地（接收）窗口大小。此函数考虑到这一点并返回有效数据长度。特别是，如果通过提交带有“nghttp2_submit_window_update（）”的负window_size_increment来减小本地窗口大小，则此函数返回的字节数小于实际接收的字节数。
 *
 * 如果失败，此函数将返回-1。
 */
NGHTTP2_EXTERN int32_t nghttp2_session_get_stream_effective_recv_data_length(
    nghttp2_session *session, int32_t stream_id);

/**
 * @function
 *
 * 返回流|stream_id|的本地（接收）窗口大小。本地窗口大小可以通过“nghttp2_submit_window_update（）”进行调整。此函数考虑到这一点并返回有效窗口大小。
 *
 * 此函数不考虑从远程端点接收的数据量。使用“nghttp2_session_get_stream_cal_window_size（）”了解远程端点在不接收流级window_UPDATE帧的情况下可以发送的数据量。注意，每个流仍然受连接级别流控制。
 *
 * 如果失败，此函数将返回-1。
 */
NGHTTP2_EXTERN int32_t nghttp2_session_get_stream_effective_local_window_size(
    nghttp2_session *session, int32_t stream_id);

/**
 * @function
 *
 * 返回远程端点可以在不接收流级WINDOW_UPDATE帧的情况下发送的流控制有效负载（例如DATA）的数量。它还受连接级别流量控制的影响。因此，要发送的实际数据量为min（`nghttp2_session_get_stream_ocal_window_size（）`，`nghttp2-session_get_local_window_size（）'）。
 *
 * 如果失败，此函数将返回-1。
 */
NGHTTP2_EXTERN int32_t nghttp2_session_get_stream_local_window_size(
    nghttp2_session *session, int32_t stream_id);

/**
 * @function
 *
 * 返回连接在未进行WINDOW_UPDATE传输的情况下接收的DATA有效负载的字节数。可以通过“nghttp2_submit_window_update（）”调整本地（接收）窗口大小。此函数考虑到这一点并返回有效数据长度。特别是，如果通过提交带有“nghttp2_submit_window_update（）”的负window_size_increment来减小本地窗口大小，则此函数返回的字节数小于实际接收的字节数。
 *
 * 如果失败，此函数将返回-1。
 */
NGHTTP2_EXTERN int32_t
nghttp2_session_get_effective_recv_data_length(nghttp2_session *session);

/**
 * @function
 *
 * 返回连接的本地（接收）窗口大小。本地窗口大小可以通过“nghttp2_submit_window_update（）”进行调整。此函数考虑到这一点并返回有效窗口大小。
 *
 * 此函数不考虑从远程端点接收的数据量。使用“nghttp2_session_get_local_window_size（）”了解远程端点在不接收连接级别window_UPDATE帧的情况下可以发送的数据量。注意，每个流仍受流级流量控制。
 *
 * 如果失败，此函数将返回-1。
 */
NGHTTP2_EXTERN int32_t
nghttp2_session_get_effective_local_window_size(nghttp2_session *session);

/**
 * @function
 *
 * 返回远程端点在不接收连接级别WINDOW_UPDATE帧的情况下可以发送的流控制有效负载（例如DATA）的数量。请注意，每个流仍受流级流控制（请参见“nghttp2_session_get_stream_local_window_size（）”）。
 *
 * 如果失败，此函数将返回-1。
 */
NGHTTP2_EXTERN int32_t
nghttp2_session_get_local_window_size(nghttp2_session *session);

/**
 * @function
 *
 * 返回给定流|stream_id|的远程窗口大小。
 *
 * 这是本地端点在没有流级别WINDOW_UPDATE的情况下可以发送的流控制有效载荷（例如DATA）的量。还有连接级别的流控制，因此本地端点可以实际发送的有效负载大小为最小值（`nghttp2_session_get_stream_remote_window_size（）`，`nghttp 2_session_get-remote_window_size（）'）。
 *
 * 如果失败，此函数将返回-1。
 */
NGHTTP2_EXTERN int32_t nghttp2_session_get_stream_remote_window_size(
    nghttp2_session *session, int32_t stream_id);

/**
 * @function
 *
 * 返回连接的远程窗口大小。
 *
 * 此函数始终成功。
 */
NGHTTP2_EXTERN int32_t
nghttp2_session_get_remote_window_size(nghttp2_session *session);

/**
 * @function
 *
 * 如果本地对等端半关闭了给定流|stream_id|，则返回1。如果没有，则返回0。如果不存在此类流，则返回-1。
 */
NGHTTP2_EXTERN int
nghttp2_session_get_stream_local_close(nghttp2_session *session,
                                       int32_t stream_id);

/**
 * @function
 *
 * 如果远程对等端半关闭了给定流|stream_id|，则返回1。如果没有，则返回0。如果不存在此类流，则返回-1。
 */
NGHTTP2_EXTERN int
nghttp2_session_get_stream_remote_close(nghttp2_session *session,
                                        int32_t stream_id);

/**
 * @function
 *
 * 返回HPACK充气机的当前动态表大小，包括RFC 7541中描述的每个条目的开销32字节。
 */
NGHTTP2_EXTERN size_t
nghttp2_session_get_hd_inflate_dynamic_table_size(nghttp2_session *session);

/**
 * @function
 *
 * 返回HPACK deflater的当前动态表大小，包括RFC 7541中描述的每个条目32字节的开销。
 */
NGHTTP2_EXTERN size_t
nghttp2_session_get_hd_deflate_dynamic_table_size(nghttp2_session *session);

/**
 * @function
 *
 * 发出会话信号，以便终止连接。
 *
 * 最后一个流ID是最近调用了：type:`nghttp2_on_frame_recv_callback`的流的流ID与之前发送给对等方的最后一个ID之间的最小值。
 *
 * |error_code|是此GOAWAY帧的错误代码。预定义的错误代码是：enum:`nghttp2_error_code`之一。
 *
 * 传输后，`nghttp2_session_want_read（）`和`nghttp2-session_want_write（）`都返回0。
 *
 * 当发送GOAWAY后应终止连接时，应调用此函数。如果剩余的流应该在GOAWAY之后处理，请改用“nghttp2_submit_GOAWAY（）”。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int nghttp2_session_terminate_session(nghttp2_session *session,
                                                     uint32_t error_code);

/**
 * @function
 *
 * 发出会话信号，以便终止连接。
 *
 * 此函数的行为类似于“nghttp2_session_terminate_session（）”，但最后一个流ID可以由应用程序指定，以便对流进行细粒度控制。HTTP/2规范不允许增加last_stream_id。因此，作为last_stream_id发送的实际值是给定的|last_stream.id|和我们先前发送给对等方的last_strean_id之间的最小值。
 *
 * |last_stream_id|是对等方的流id或0。因此，如果将|session|初始化为客户端，则|last_sttream_id|必须为偶数或0。如果将|session|初始化为服务器，则|last_stream_id |必须为奇数或0。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |last_stream_id|无效。
 */
NGHTTP2_EXTERN int nghttp2_session_terminate_session2(nghttp2_session *session,
                                                      int32_t last_stream_id,
                                                      uint32_t error_code);

/**
 * @function
 *
 * 向客户端发出信号，表明服务器已开始正常关闭过程。
 *
 * 此功能仅适用于服务器。如果使用客户端会话调用此函数，则此函数返回：enum:`NGHTTP2_ERR_INVALID_STATE`。
 *
 * 要优雅地关闭HTTP/2会话，服务器应调用此函数以发送带有last_stream_id（1u<<31）-1的GOAWAY。在一段延迟后（例如，1 RTT），使用“nghttp2_submit_GOAWAY（）”发送另一个带有服务器已处理的流id的GOAWAY。另请参见“nghttp2_session_get_last_proc_stream_id（）”。
 *
 * 与“nghttp2_submit_goaway（）”不同，此函数只发送goaway，不做任何其他操作。这只是向客户端表明会话即将关闭。应用程序应在调用后使用适当的last_stream_id调用“nghttp2_submit_goaway（）”。
 *
 * 如果“nghttp2_submit_GOAWAY（）”或“nghttp 2_session_terminate_session（）”已经发送了一个或多个GOAWAY帧，则此函数无效。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_STATE`将|会话|初始化为客户端。
 */
NGHTTP2_EXTERN int nghttp2_submit_shutdown_notice(nghttp2_session *session);

/**
 * @function
 *
 * 返回远程终结点通知的SETTING|id|值。|id|必须是enum:`nghttp2_settings_id`中定义的值之一。
 */
NGHTTP2_EXTERN uint32_t nghttp2_session_get_remote_settings(
    nghttp2_session *session, nghttp2_settings_id id);

/**
 * @function
 *
 * 返回远程终结点确认的本地终结点的SETTING|id|值。|id|必须是enum:`nghttp2_settings_id`中定义的值之一。
 */
NGHTTP2_EXTERN uint32_t nghttp2_session_get_local_settings(
    nghttp2_session *session, nghttp2_settings_id id);

/**
 * @function
 *
 * 告诉|session|下一个流ID是|next_stream_ID|。|next_stream_id|必须等于或大于`nghttp2_session_get_next_stream_id（）`返回的值。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |next_stream_id|严格小于返回的值`NGHTTP2_session_get_next_stream_id（）`；或|next_stream_id|无效（例如，客户端为偶数，服务器为奇数）。
 */
NGHTTP2_EXTERN int nghttp2_session_set_next_stream_id(nghttp2_session *session,
                                                      int32_t next_stream_id);

/**
 * @function
 *
 * 返回下一个传出流ID。请注意，返回类型为uint32_t。如果此会话的流ID用完，则此函数返回1<<31。
 */
NGHTTP2_EXTERN uint32_t
nghttp2_session_get_next_stream_id(nghttp2_session *session);

/**
 * @function
 *
 * 告诉|session|由|stream_id|表示的流的|size|字节已被应用程序使用，并准备好WINDOW_UPDATE。消耗的字节将计入连接级和流级WINDOW_UPDATE（请参见“nghttp2_session_consumer_connection（）”和“nghttp 2_session_cconsumer_stream（）”以独立更新消耗）。此函数旨在在没有自动窗口更新的情况下使用（请参见“nghttp2_option_set_no_auto_window_update（）”）。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |stream_id|为0。示例：enum:`NGHTTP2_ERR_INVALID_STATE`未禁用自动WINDOW_UPDATE。
 */
NGHTTP2_EXTERN int nghttp2_session_consume(nghttp2_session *session,
                                           int32_t stream_id, size_t size);

/**
 * @function
 *
 * 类似于“nghttp2_session_consumer（）”，但这只告诉库|size|字节仅用于连接级别。注意，HTTP/2独立维护连接和流级流控制窗口。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_STATE`未禁用自动WINDOW_UPDATE。
 */
NGHTTP2_EXTERN int nghttp2_session_consume_connection(nghttp2_session *session,
                                                      size_t size);

/**
 * @function
 *
 * 类似于“nghttp2_session_consumer（）”，但这只告诉库，|size|字节仅用于|stream_id|表示的流。注意，HTTP/2独立维护连接和流级流控制窗口。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |stream_id|为0。示例：enum:`NGHTTP2_ERR_INVALID_STATE`未禁用自动WINDOW_UPDATE。
 */
NGHTTP2_EXTERN int nghttp2_session_consume_stream(nghttp2_session *session,
                                                  int32_t stream_id,
                                                  size_t size);

/**
 * @function
 *
 * 更改由|stream_id|表示的现有流的优先级。新的优先级规范是|pri_spec|。
 *
 * 优先级会立即无声地更改，并且不会发送priority帧来通知对等方此更改。此功能可能有助于服务器更改推送流的优先级。
 *
 * 如果|session|被初始化为服务器，并且``pri_spec->stream_id``指向空闲流，则在空闲流不存在的情况下创建它。创建的空闲流将取决于权重为16的根流（流0）。
 *
 * 否则，如果找不到由“pri_spec->stream_id”表示的流，我们将使用默认优先级而不是给定的|pri_spec|。也就是说，使流取决于具有权重16的根流。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT`试图依赖自身；或者对于给定的|stream_id|不存在流；或|stream_id|为0
 */
NGHTTP2_EXTERN int
nghttp2_session_change_stream_priority(nghttp2_session *session,
                                       int32_t stream_id,
                                       const nghttp2_priority_spec *pri_spec);

/**
 * @function
 *
 * 创建具有给定|stream_id|和优先级|pri_spec|的空闲流。
 *
 * 流创建是在不发送PRIORITY帧的情况下完成的，这意味着对等方不知道本地端点中存在此空闲流。
 *
 * RFC 7540不允许创建具有奇数或偶数流ID的空闲流，无论客户端或服务器如何。因此，无论客户端或服务器如何，此函数都可以创建奇数或偶数流ID。但使用本地端点可以发起的流ID（换句话说，为客户端使用奇数流ID，为服务器使用偶数流ID）可能会更安全一些，以避免来自对等方指令的潜在冲突。此外，如果遵循此建议，我们还可以使用“nghttp2_session_set_next_stream_id（）”来避免意外打开创建的空闲流。
 *
 * 如果|session|被初始化为服务器，并且``pri_spec->stream_id``指向空闲流，则在空闲流不存在的情况下创建它。创建的空闲流将取决于权重为16的根流（流0）。
 *
 * 否则，如果找不到由“pri_spec->stream_id”表示的流，我们将使用默认优先级而不是给定的|pri_spec|。也就是说，使流取决于具有权重16的根流。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT`试图依赖自身；或者由|stream_id|表示的流已经存在；或|stream_id|不能用于创建空闲流（换句话说，本地端点已打开大于或等于给定流id的流id；或|streamid|为0
 */
NGHTTP2_EXTERN int
nghttp2_session_create_idle_stream(nghttp2_session *session, int32_t stream_id,
                                   const nghttp2_priority_spec *pri_spec);

/**
 * @function
 *
 * 执行HTTP升级请求的后处理。该函数可以从客户端和服务器调用，但彼此的行为非常不同。
 *
 * ..警告：：
 *
 *   该函数不推荐使用“nghttp2_session_upgrade2（）”，因为该函数缺少告诉库原始HTTP请求中使用的请求方法的参数。客户端需要此信息才能根据内容长度标头字段验证实际响应体长度（请参见“nghttp2_option_set_no_http_messaging（）”）。如果在请求中使用HEAD，则响应体的长度必须为0，而不管内容长度头字段中包含的值如何。
 *
 * 如果从客户端调用，则|settings_epayload |必须是“HTTP2设置”标头字段中发送的值，并且必须由base64url解码器解码。|settings_bayloadlen|是|settings_hayload|的长度。将解压缩|settings_epayload |，并使用“nghttp2_submit_settings（）”提交其设置值。这意味着客户端应用程序代码不需要自己提交SETTINGS。流ID=1的流被打开，|stream_user_data|用于其stream_user_data。打开的流变为半关闭（局部）状态。
 *
 * 如果从服务器端调用，则|settings_depayload |必须是“HTTP2设置”标头字段中接收的值，并且必须由base64url解码器解码。|settings_bayloadlen|是|settings_hayload|的长度。它被视为接收到具有该有效载荷的SETTINGS帧。因此，将调用用于接收SETTINGS帧的回调函数。流ID为1的流被打开。忽略|stream_user_data|。打开的流变为半关闭（远程）。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |settings_boadload |格式不正确。：enum:`NGHTTP2_ERR_PROTO`流ID 1已被使用或关闭；或不可用。
 */
NGHTTP2_EXTERN int nghttp2_session_upgrade(nghttp2_session *session,
                                           const uint8_t *settings_payload,
                                           size_t settings_payloadlen,
                                           void *stream_user_data);

/**
 * @function
 *
 * 执行HTTP升级请求的后处理。该函数可以从客户端和服务器调用，但彼此的行为非常不同。
 *
 * 如果从客户端调用，则|settings_epayload |必须是“HTTP2设置”标头字段中发送的值，并且必须由base64url解码器解码。|settings_bayloadlen|是|settings_hayload|的长度。将解压缩|settings_epayload |，并使用“nghttp2_submit_settings（）”提交其设置值。这意味着客户端应用程序代码不需要自己提交SETTINGS。流ID=1的流被打开，|stream_user_data|用于其stream_user_data。打开的流变为半关闭（局部）状态。
 *
 * 如果从服务器端调用，则|settings_depayload |必须是“HTTP2设置”标头字段中接收的值，并且必须由base64url解码器解码。|settings_bayloadlen|是|settings_hayload|的长度。它被视为接收到具有该有效载荷的SETTINGS帧。因此，将调用用于接收SETTINGS帧的回调函数。流ID为1的流被打开。忽略|stream_user_data|。打开的流变为半关闭（远程）。
 *
 * 如果请求方法是HEAD，则将非零值传递给|HEAD_request|。否则，传递0。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |settings_boadload |格式不正确。：enum:`NGHTTP2_ERR_PROTO`流ID 1已被使用或关闭；或不可用。
 */
NGHTTP2_EXTERN int nghttp2_session_upgrade2(nghttp2_session *session,
                                            const uint8_t *settings_payload,
                                            size_t settings_payloadlen,
                                            int head_request,
                                            void *stream_user_data);

/**
 * @function
 *
 * 序列化|buf|中的SETTINGS值|iv|。|buf|的大小由|buflen|指定。|iv|数组中的条目数由|niv|给出。|buf|中|niv|项所需的空间为“6niv”字节，如果给定的缓冲区太小，则返回错误。此函数主要用于创建要在HTTP升级请求中使用“HTTP2设置”标头字段发送的SETTINGS有效负载。写入|buf|的数据不是base64url编码的，应用程序负责编码。
 *
 * 此函数返回写入|buf|的字节数，或以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |iv|包含重复的设置ID或无效值。
 *
 * ：enum:`NGHTTP2_ERR_INSUFF_BUFSIZE`提供的|buflen|大小太小，无法容纳输出。
 */
NGHTTP2_EXTERN ssize_t nghttp2_pack_settings_payload(
    uint8_t *buf, size_t buflen, const nghttp2_settings_entry *iv, size_t niv);

/**
 * @function
 *
 * 返回描述|lib_error_code|的字符串。|lib_error_code|必须是：enum:`nghttp2_error`之一。
 */
NGHTTP2_EXTERN const char *nghttp2_strerror(int lib_error_code);

/**
 * @function
 *
 * 返回HTTP/2错误代码|error_code|的字符串表示形式（例如，如果``error_code==NGHTTP2_PROTOCOL_error``，则返回``PROTOCOLE_error``）。如果给定|error_code|的字符串表示形式未知，则此函数返回字符串“未知”。
 */
NGHTTP2_EXTERN const char *nghttp2_http2_strerror(uint32_t error_code);

/**
 * @function
 *
 * 使用要依赖的流的|stream_id|和|weight|及其互斥标志初始化|pri_spec|。如果|exclusive|为非零，则设置exclusive标志。
 *
 * |weight|必须在[：enum:`NGHTTP2_MIN_weight`，：enum:` NGHTTP2_MAX_weight`]（包括）中。
 */
NGHTTP2_EXTERN void nghttp2_priority_spec_init(nghttp2_priority_spec *pri_spec,
                                               int32_t stream_id,
                                               int32_t weight, int exclusive);

/**
 * @function
 *
 * 使用默认值初始化|pri_spec|。默认值为：stream_id=0，weight=：macro:`NGHTTP2_default_weight`和exclusive=0。
 */
NGHTTP2_EXTERN void
nghttp2_priority_spec_default_init(nghttp2_priority_spec *pri_spec);

/**
 * @function
 *
 * 如果|pri_spec|用默认值填充，则返回非零。
 */
NGHTTP2_EXTERN int
nghttp2_priority_spec_check_default(const nghttp2_priority_spec *pri_spec);

/**
 * @function
 *
 * 提交HEADERS帧和可选的一个或多个DATA帧。
 *
 * |pri_spec|是此请求的优先级规范``NULL“”表示默认优先级（请参见“nghttp2_priority_spec_default_init（）”）。要指定优先级，请使用“nghttp2_priority_spec_init（）”。如果|pri_spec|不是“NULL”，则此函数将复制其数据成员。
 *
 * `pri_spec->weight``必须在[：enum:`NGHTTP2_MIN_weight `，：enum:` NGHTTP2_MAX_weight `]（包括）中。如果`pri_spec->weight``严格小于：enum:`NGHTTP2_MIN_weight`，则它将变为：enum:` NGHTTP2_MIN_weight`。如果它严格大于：enum:`NGHTTP2_MAX_WEIGHT `，则它将变为：enum:` NGHTTP2_MAX_WEIGHT'。
 *
 * |nva|是具有|nvlen|元素的名称/值对数组：type:`nghttp2_nv`。应用程序负责在|nva|中包含所需的伪标头字段（名称以“：”开头的标头字段），并且必须将伪标头放在常规标头字段之前。
 *
 * 此函数创建|nva|中所有名称/值对的副本。它还降低了|nva|中所有名称的大小写。保留|nva|中元素的顺序。对于设置了：enum:`NGHTTP2_NV_FLAG_NO_COPY_NAME`和：enum:` NGHTTP2-NV_FLAG_NO_COPY_VALUE`的头字段，不会分别复制头字段名称和值。使用：enum:`NGHTTP2_NV_FLAG_NO_COPY_NAME`，应用程序负责以小写形式传递头字段名。应用程序应保持对它们的引用，直到调用：type:`nghttp2_on_frame_send_callback`或：type:'nghttp2_on_frame_not_send_cllback`。
 *
 * HTTP/2规范对请求HEADERS中的头字段有要求。有关详细信息，请参阅规范。
 *
 * 如果|data_prd|不是“NULL”，则它提供将在后续data帧中发送的数据。在这种情况下，允许请求消息体的方法(https://tools.ietf.org/html/rfc7231#section-4） 必须在|nva|中使用“：method”键指定（例如“POST”）。此函数不拥有|data_prd|的所有权。该函数复制|data_prd|的成员。如果|data_prd|为“NULL”，HEADER将设置END_STREAM。|stream_user_data|是与此请求打开的流关联的数据，可以是任意指针，稍后可以通过“nghttp2_session_get_stream_user_data（）”检索。
 *
 * 如果成功，此函数将返回分配的流ID，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_STREAM_ID_NOT_AVAILABLE`没有可用的流ID，因为已达到最大流ID。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT`尝试依赖于自身（新流ID等于``pri_spec->stream_ID``）。：enum:`NGHTTP2_ERR_PROTO` |session|是服务器会话。
 *
 * ..警告：：
 *
 *   如果成功，此函数将返回分配的流ID。但该流尚未创建。在为此帧调用类型：“nghttp2_before_frame_send_callback”之前，应用程序不能向该流ID提交帧。这意味着“nghttp2_session_get_stream_user_data（）”在回调之前不起作用。但是`nghttp2_session_set_stream_user_data（）`专门处理这种情况，它可以在此期间将数据设置为流。
 *
 */
NGHTTP2_EXTERN int32_t nghttp2_submit_request(
    nghttp2_session *session, const nghttp2_priority_spec *pri_spec,
    const nghttp2_nv *nva, size_t nvlen, const nghttp2_data_provider *data_prd,
    void *stream_user_data);

/**
 * @function
 *
 * 针对流|stream_id|提交响应HEADERS帧和可选的一个或多个DATA帧。
 *
 * |nva|是具有|nvlen|元素的名称/值对数组：type:`nghttp2_nv`。应用程序负责在|nva|中包含所需的伪标头字段（名称以“：”开头的标头字段），并且必须将伪标头放在常规标头字段之前。
 *
 * 此函数创建|nva|中所有名称/值对的副本。它还降低了|nva|中所有名称的大小写。保留|nva|中元素的顺序。对于设置了：enum:`NGHTTP2_NV_FLAG_NO_COPY_NAME`和：enum:` NGHTTP2-NV_FLAG_NO_COPY_VALUE`的头字段，不会分别复制头字段名称和值。使用：enum:`NGHTTP2_NV_FLAG_NO_COPY_NAME`，应用程序负责以小写形式传递头字段名。应用程序应保持对它们的引用，直到调用：type:`nghttp2_on_frame_send_callback`或：type:'nghttp2_on_frame_not_send_cllback`。
 *
 * HTTP/2规范对响应HEADERS中的头字段有要求。有关详细信息，请参阅规范。
 *
 * 如果|data_prd|不是“NULL”，则它提供将在后续data帧中发送的数据。此函数不拥有|data_prd|的所有权。该函数复制|data_prd|的成员。如果|data_prd|为“NULL”，HEADER将设置END_STREAM标志。
 *
 * 此方法可以用作正常的HTTP响应和推送响应。使用此函数推送资源时，必须使用“nghttp2_session_server_new（）”或其变体配置|session|，并且必须使用“nhttp2_submit_push_promise（）”保留|stream_id|表示的目标流。
 *
 * 要发送非最终响应标头（例如，HTTP状态101），请不要使用此函数，因为此函数会半关闭出站流。为此，请使用“nghttp2_submit_headers（）”。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |stream_id|为0。：enum:`NGHTTP2_ERR_DATA_EXIST`数据或HEADER已提交，尚未完全处理。通常情况下，这不会发生，但当应用程序错误地调用“nghttp2_submit_response（）”两次时，可能会发生这种情况。：enum:`NGHTTP2_ERR_PROTO` |session|是客户端会话。
 *
 * ..警告：：
 *
 *   对于同一个流ID调用此函数两次可能会导致程序崩溃。提交两次响应通常被认为是编程错误。
 */
NGHTTP2_EXTERN int
nghttp2_submit_response(nghttp2_session *session, int32_t stream_id,
                        const nghttp2_nv *nva, size_t nvlen,
                        const nghttp2_data_provider *data_prd);

/**
 * @function
 *
 * 针对流|stream_id|提交尾部字段HEADERS。
 *
 * |nva|是具有|nvlen|元素的名称/值对数组：type:`nghttp2_nv`。应用程序不能在|nva|中包含伪标头字段（名称以“：”开头的标头）。
 *
 * 此函数创建|nva|中所有名称/值对的副本。它还降低了|nva|中所有名称的大小写。保留|nva|中元素的顺序。对于设置了：enum:`NGHTTP2_NV_FLAG_NO_COPY_NAME`和：enum:` NGHTTP2-NV_FLAG_NO_COPY_VALUE`的头字段，不会分别复制头字段名称和值。使用：enum:`NGHTTP2_NV_FLAG_NO_COPY_NAME`，应用程序负责以小写形式传递头字段名。应用程序应保持对它们的引用，直到调用：type:`nghttp2_on_frame_send_callback`或：type:'nghttp2_on_frame_not_send_cllback`。
 *
 * 对于服务器，尾部字段必须跟在响应HEADERS或响应DATA之后，而不带END_STREAM平面集。库不强制执行此要求，应用程序应自行执行。如果在提交任何响应HEADER之前调用了“nghttp2_submit_trailer（）”（通常是通过“nghttp 2_submit_response（）”），则|nva|的内容将作为响应标头发送，这将导致错误。
 *
 * 此函数与“nghttp2_submit_headers（）”具有相同的效果，flags=：enum:`nghttp2_FLAG_END_STREAM`，pri_spec和STREAM_user_data均为NULL。
 *
 * 若要在调用“nghttp2_submit_response（）”后提交尾部字段，应用程序必须指定：type:`nghttp2_data_provider`To`nghttp2-submit_reresponse（）`。在：type:`nghttp2_data_source_read_callback`的内部，当设置：enum:`nghttp2_data_FLAG_EOF`时，还设置：enum:`NGHTTP_2_data_FLAG_NO_END_STREAM`。之后，应用程序可以使用“nghttp2_submit_trailer（）”发送尾部字段`nghttp2_submit_trailer（）`可以在内部使用：type:`nghttp2_data_source_read_callback`。
 *
 * 如果此函数成功且|stream_id|为-1，则返回0。否则，如果成功，则此函数返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |stream_id|为0。
 */
NGHTTP2_EXTERN int nghttp2_submit_trailer(nghttp2_session *session,
                                          int32_t stream_id,
                                          const nghttp2_nv *nva, size_t nvlen);

/**
 * @function
 *
 * 提交HEADERS帧。|标志|是以下值的位或：
 *
 * *：enum:`NGHTTP2_FLAG_END_STREAM`
 *
 * 如果|flags |包含：enum:`NGHTTP2_FLAG_END_STREAM`，则此帧已设置END_STREAM标志。
 *
 * 库在内部处理CONTINUATION帧，并将END_HEADERS正确设置为PUSH_PROMISE或CONTINUATION帧的最后一个序列。
 *
 * 如果|stream_id|为-1，则将此帧假定为请求（即，打开新流的请求HEADERS帧）。在这种情况下，将返回分配的流ID。否则，请在|stream_ID|中指定流ID。
 *
 * |pri_spec|是此请求的优先级规范``NULL“”表示默认优先级（请参见“nghttp2_priority_spec_default_init（）”）。要指定优先级，请使用“nghttp2_priority_spec_init（）”。如果|pri_spec|不是“NULL”，则此函数将复制其数据成员。
 *
 * `pri_spec->weight``必须在[：enum:`NGHTTP2_MIN_weight `，：enum:` NGHTTP2_MAX_weight `]（包括）中。如果`pri_spec->weight``严格小于：enum:`NGHTTP2_MIN_weight`，则它将变为：enum:` NGHTTP2_MIN_weight`。如果它严格大于：enum:`NGHTTP2_MAX_WEIGHT `，则它将变为：enum:` NGHTTP2_MAX_WEIGHT'。
 *
 * |nva|是具有|nvlen|元素的名称/值对数组：type:`nghttp2_nv`。应用程序负责在|nva|中包含所需的伪标头字段（名称以“：”开头的标头字段），并且必须将伪标头放在常规标头字段之前。
 *
 * 此函数创建|nva|中所有名称/值对的副本。它还降低了|nva|中所有名称的大小写。保留|nva|中元素的顺序。对于设置了：enum:`NGHTTP2_NV_FLAG_NO_COPY_NAME`和：enum:` NGHTTP2-NV_FLAG_NO_COPY_VALUE`的头字段，不会分别复制头字段名称和值。使用：enum:`NGHTTP2_NV_FLAG_NO_COPY_NAME`，应用程序负责以小写形式传递头字段名。应用程序应保持对它们的引用，直到调用：type:`nghttp2_on_frame_send_callback`或：type:'nghttp2_on_frame_not_send_cllback`。
 *
 * |stream_user_data|是指向与此帧将打开的流相关联的任意数据的指针。因此，它仅在该帧打开流时使用，换句话说，它将流状态从空闲或保留更改为打开。
 *
 * 这个函数是低级的，因为应用程序代码可以直接指定标志。对于通常的HTTP请求，“nghttp2_submit_request（）”很有用。同样，对于HTTP响应，首选“nghttp2_submit_response（）”。
 *
 * 如果此函数成功且|stream_ID|为-1，则返回新分配的流ID。否则，如果成功，则此函数返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_STREAM_ID_NOT_AVAILABLE`没有可用的流ID，因为已达到最大流ID。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |stream_id|为0；或试图依赖于自身（流ID等于`pri_spec->stream_ID``）enum:`NGHTTP2_ERR_DATA_EXIST`DATA或HEADER已提交，尚未完全处理。如果|stream_id|表示的流处于保留状态，则会发生这种情况。：enum:`NGHTTP2_ERR_PROTO` |stream_id|为-1，|session|为服务器会话。
 *
 * ..警告：：
 *
 *   如果该函数成功并且|stream_ID|为-1，则返回分配的流ID。但该流尚未打开。在为此帧调用类型：“nghttp2_before_frame_send_callback”之前，应用程序不能向该流ID提交帧。
 *
 */
NGHTTP2_EXTERN int32_t nghttp2_submit_headers(
    nghttp2_session *session, uint8_t flags, int32_t stream_id,
    const nghttp2_priority_spec *pri_spec, const nghttp2_nv *nva, size_t nvlen,
    void *stream_user_data);

/**
 * @function
 *
 * 向流|stream_id|提交一个或多个DATA帧。要发送的数据由|data_prd|提供。如果|flags|包含：enum:`NGHTTP2_FLAG_END_STREAM`，则最后一个DATA帧设置了END_STREAM标志。
 *
 * 此函数不拥有|data_prd|的所有权。该函数复制|data_prd|的成员。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_DATA_EXIST`DATA或HEADER已提交，尚未完全处理。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |stream_id|为0。示例enum:`NGCHTTP2_ERR_stream_CLOSED`流已关闭；或者|stream_id|无效。
 *
 * ..注：
 *
 *   目前，一次只允许流使用一个DATA或HEADER。在第一个DATA或HEADERS完成之前多次提交这些帧会导致：enum:`NGHTTP2_ERR_DATA_EXIST`错误代码。通知上一帧已完成的最早回调是：type:`nghttp2_on_frame_send_callback`。在回调中，可以使用“nghttp2_submit_data（）”提交新数据。当然，除最后一个数据外，所有数据都不能在|flags|中设置：enum:`NGHTTP2_FLAG_END_STREAM`标志。这听起来有点复杂，我们建议使用“nghttp2_submit_request（）”和“nghttp2-submit_response（））”来避免这种级联问题。经验表明，对于HTTP使用，这两个函数足以实现客户端和服务器。
 */
NGHTTP2_EXTERN int nghttp2_submit_data(nghttp2_session *session, uint8_t flags,
                                       int32_t stream_id,
                                       const nghttp2_data_provider *data_prd);

/**
 * @function
 *
 * 提交PRIORITY帧以将流|stream_id|的优先级更改为优先级规范|pri_spec|。
 *
 * |标志|当前被忽略，应为：enum:`NGHTTP2_FLAG_NONE`。
 *
 * |pri_spec|是此请求的优先级规范``此函数不允许NULL ``。要指定优先级，请使用“nghttp2_priority_spec_init（）”。此函数将复制其数据成员。
 *
 * `pri_spec->weight``必须在[：enum:`NGHTTP2_MIN_weight `，：enum:` NGHTTP2_MAX_weight `]（包括）中。如果`pri_spec->weight``严格小于：enum:`NGHTTP2_MIN_weight`，则它将变为：enum:` NGHTTP2_MIN_weight`。如果它严格大于：enum:`NGHTTP2_MAX_WEIGHT `，则它将变为：enum:` NGHTTP2_MAX_WEIGHT'。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |stream_id|为0；或者|pri_spec|为NULL；或者试图依靠自己。
 */
NGHTTP2_EXTERN int
nghttp2_submit_priority(nghttp2_session *session, uint8_t flags,
                        int32_t stream_id,
                        const nghttp2_priority_spec *pri_spec);

/**
 * @function
 *
 * 提交RST_STREAM帧以取消/拒绝流|STREAM_id|，错误代码为|error_code|。
 *
 * 预定义的错误代码是：enum:`nghttp2_error_code`之一。
 *
 * |标志|当前被忽略，应为：enum:`NGHTTP2_FLAG_NONE`。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |stream_id|为0。
 */
NGHTTP2_EXTERN int nghttp2_submit_rst_stream(nghttp2_session *session,
                                             uint8_t flags, int32_t stream_id,
                                             uint32_t error_code);

/**
 * @function
 *
 * 存储本地设置并提交settings帧。|iv|是指向数组：type:`nghttp2_settings_entry`的指针。|niv|表示：type:`nghttp2_settings_entry`的编号。
 *
 * |标志|当前被忽略，应为：enum:`NGHTTP2_FLAG_NONE`。
 *
 * 此函数不拥有|iv|的所有权。此函数复制|iv|中的所有元素。
 *
 * 在更新单个流的本地窗口大小时，如果窗口大小严格大于NGHTTP2_MAX_window_size，则针对此类流发出RST_stream。
 *
 * 带有：enum:`NGHTTP2_FLAG_ACK`的设置由库自动提交，应用程序无法随意发送。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |iv|包含无效值（例如，初始窗口大小严格大于（1<<31）-1）。：enum:` NGHTTP2_ERROR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int nghttp2_submit_settings(nghttp2_session *session,
                                           uint8_t flags,
                                           const nghttp2_settings_entry *iv,
                                           size_t niv);

/**
 * @function
 *
 * 提交PUSH_PROMISE帧。
 *
 * |标志|当前被忽略。库在内部处理CONTINUATION帧，并将END_HEADERS正确设置为PUSH_PROMISE或CONTINUATION帧的最后一个序列。
 *
 * |stream_id|必须是客户端启动的流id。
 *
 * |nva|是具有|nvlen|元素的名称/值对数组：type:`nghttp2_nv`。应用程序负责在|nva|中包含所需的伪标头字段（名称以“：”开头的标头字段），并且必须将伪标头放在常规标头字段之前。
 *
 * 此函数创建|nva|中所有名称/值对的副本。它还降低了|nva|中所有名称的大小写。保留|nva|中元素的顺序。对于设置了：enum:`NGHTTP2_NV_FLAG_NO_COPY_NAME`和：enum:` NGHTTP2-NV_FLAG_NO_COPY_VALUE`的头字段，不会分别复制头字段名称和值。使用：enum:`NGHTTP2_NV_FLAG_NO_COPY_NAME`，应用程序负责以小写形式传递头字段名。应用程序应保持对它们的引用，直到调用：type:`nghttp2_on_frame_send_callback`或：type:'nghttp2_on_frame_not_send_cllback`。
 *
 * |promised_stream_user_data|是指向与此帧将打开并使其处于保留状态的承诺流相关联的任意数据的指针。它可以使用“nghttp2_session_get_stream_user_data（）”获得。应用程序可以在该帧的：type:`nghttp2_before_frame_send_callback`和：type:'nghttp2_on_frame_send_callback`中访问它。
 *
 * 客户端不允许使用此功能。
 *
 * 要提交响应标头和数据，请使用“nghttp2_submit_response（）”。
 *
 * 如果成功，此函数将返回分配的承诺流ID，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_PROTO`当|session|初始化为客户端时调用了此函数。：enum:`NGHTTP2_ERR_STREAM_ID_NOT_AVAILABLE`没有可用的流ID，因为已达到最大流ID。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |stream_id|为0；|stream_id|未指定对等方启动的流。：enum:`NGHTTP2_ERR_STREAM_CLOSED`流已关闭；或者|stream_id|无效。
 *
 * ..警告：：
 *
 *   如果成功，此函数将返回分配的承诺流ID。从1.16.0开始，当此函数成功时，将创建推送资源的流对象。在这种情况下，应用程序可以提交承诺帧的推送响应。
 *
 *   在1.15.0或更早版本中，当此函数成功时，推送流尚未打开。在为此帧调用类型：“nghttp2_before_frame_send_callback”之前，应用程序不能向该流ID提交帧。
 *
 */
NGHTTP2_EXTERN int32_t nghttp2_submit_push_promise(
    nghttp2_session *session, uint8_t flags, int32_t stream_id,
    const nghttp2_nv *nva, size_t nvlen, void *promised_stream_user_data);

/**
 * @function
 *
 * 提交PING帧。当您收到PING帧时，您不必发送PING。在这种情况下，库自动提交PING帧。
 *
 * |flags|是以下值的0或更多的位或。
 *
 * *：enum:`NGHTTP2_FLAG_ACK`
 *
 * 除非使用“nghttp2_option_set_no_auto_ping_ack（）”，否则|标志|应为：enum:`nghttp2_FLAG_NONE`。
 *
 * 如果|opaque_data|不是“NULL”，那么它应该指向8字节的内存数组，以指定用PING帧发送的不透明数据。如果|opaque_data|为“NULL”，则清零的8个字节将作为不透明数据发送。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int nghttp2_submit_ping(nghttp2_session *session, uint8_t flags,
                                       const uint8_t *opaque_data);

/**
 * @function
 *
 * 提交具有最后一个流ID |last_stream_ID|和错误代码|error_code|的GOAWAY帧。
 *
 * 预定义的错误代码是：enum:`nghttp2_error_code`之一。
 *
 * |标志|当前被忽略，应为：enum:`NGHTTP2_FLAG_NONE`。
 *
 * |last_stream_id|是对等方的流id或0。因此，如果将|session|初始化为客户端，则|last_sttream_id|必须为偶数或0。如果将|session|初始化为服务器，则|last_stream_id |必须为奇数或0。
 *
 * HTTP/2规范表示last_stream_id不能从先前发送的值增加。因此，作为last_stream_id发送的实际值是给定的|last_strean_id|和先前发送给对等方的last_streab_id之间的最小值。
 *
 * 如果|opaque_data|不是“NULL”，并且|opaque_data_len|不是零，则这些数据将作为其他调试数据发送。库使用长度|opaque_data_len|复制|opaque_data|指向的内存区域，因此调用方在返回此函数后不需要保留此内存。如果|opaque_data_len|为0，则|opaque_data|可能为“NULL”。
 *
 * 在GOAWAY成功传输后，发生了以下情况。所有严格大于|last_stream_id|的传入流都将关闭。所有启动新流的传入HEADER都会被忽略。处理完所有活动流后，`nghttp2_session_want_read（）`和`nghttp 2_session_went_write（）`都返回0，应用程序可以关闭会话。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |opaque_data_len|太大；|last_stream_id|无效。
 */
NGHTTP2_EXTERN int nghttp2_submit_goaway(nghttp2_session *session,
                                         uint8_t flags, int32_t last_stream_id,
                                         uint32_t error_code,
                                         const uint8_t *opaque_data,
                                         size_t opaque_data_len);

/**
 * @function
 *
 * 返回最近调用的流的最后一个流ID：type:`nghttp2_on_frame_recv_callback`。返回的值可以用作“nghttp2_submit_goaway（）”和“nghttp 2_session_terminate_session2（）”的last_stream_id参数。
 *
 * 此函数始终成功。
 */
NGHTTP2_EXTERN int32_t
nghttp2_session_get_last_proc_stream_id(nghttp2_session *session);

/**
 * @function
 *
 * 如果可以从本地端点发送新请求，则返回非零。
 *
 * 如果此会话不允许请求，则此函数返回0。不允许请求的原因有几个。其中一些原因是：会话是服务器；流ID已用完；GOAWAY已发送或接收。
 *
 * 应用程序可以调用“nghttp2_submit_request（）”，而无需咨询此函数。在这种情况下，“nghttp2_submit_request（）”可能会返回错误。或者，请求发送失败，并调用：type:`nghttp2_on_stream_close_callback `。
 */
NGHTTP2_EXTERN int
nghttp2_session_check_request_allowed(nghttp2_session *session);

/**
 * @function
 *
 * 如果|session|初始化为服务器端会话，则返回非零。
 */
NGHTTP2_EXTERN int
nghttp2_session_check_server_session(nghttp2_session *session);

/**
 * @function
 *
 * 提交WINDOW_UPDATE帧。
 *
 * |标志|当前被忽略，应为：enum:`NGHTTP2_FLAG_NONE`。
 *
 * |stream_id|是发送此WINDOW_UPDATE的流id。要发送连接级别WINDOW_UPDATE，请将0指定为|stream_id|。
 *
 * 如果|window_size_increment|为正，则将该值为window_size.increment的window_UPDATE排入队列。如果|window_size_increment|大于从远程端点接收的字节，则本地窗口大小将增加该差值。如果唯一的目的是增加本地窗口大小，请考虑使用“nghttp2_session_set_local_window_size（）”。
 *
 * 如果|window_size_increment|为负，则本地窗口大小将减小-|window_size _increment|。如果启用了自动WINDOW_UPDATE（`nghttp2_option_set_no_auto_WINDOW_UPDATE（）`），并且库决定应提交WINDOW_UPDATE，则WINDOW_UPDTE将与当前接收的字节计数一起排队。如果唯一的目的是减小本地窗口大小，请考虑使用“nghttp2_session_set_local_window_size（）”。
 *
 * 如果|window_size_increment|为0，则函数不执行任何操作并返回0。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_FLOW_CONTROL`本地窗口大小溢出或为负值。：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int nghttp2_submit_window_update(nghttp2_session *session,
                                                uint8_t flags,
                                                int32_t stream_id,
                                                int32_t window_size_increment);

/**
 * @function
 *
 * 对于由|stream_id|表示的给定流，将本地窗口大小（本地端点的窗口大小）设置为给定的|window_size|。要更改连接级别窗口大小，请将0指定为|stream_id|。为了增加窗口大小，此函数可以将window_UPDATE帧提交到传输队列。
 *
 * |标志|当前被忽略，应为：enum:`NGHTTP2_FLAG_NONE`。
 *
 * 这听起来类似于“nghttp2_submit_window_update（）”，但有两个不同之处。第一个区别是，该函数采用窗口大小的绝对值来设置，而不是增量。要更改窗口大小，这可能更容易使用，因为应用程序只是声明了预期的窗口大小，而不是计算增量。第二个区别是“nghttp2_submit_window_update（）”会影响尚未确认的接收字节数。根据“nghttp2_submit_window_update（）”的规范，为了严格增加本地窗口大小，我们必须提交包含所有接收字节计数的增量，这在某些情况下可能是不可取的。另一方面，此函数不影响接收的字节计数。它只是将本地窗口大小设置为给定值。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |stream_id|为负。：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int
nghttp2_session_set_local_window_size(nghttp2_session *session, uint8_t flags,
                                      int32_t stream_id, int32_t window_size);

/**
 * @function
 *
 * 提交扩展框架。
 *
 * 应用程序可以分别在|flags|和|stream_ID|中传递任意帧标志和流ID。|payload |是一个不透明的指针，可以通过type:`nghttp2_pack_extension_callback`中的``frame->ext.payload``进行访问。库将不拥有传递的|payload |指针。
 *
 * 应用程序必须使用“nghttp2_session_callback_set_pack_extension_callback（）”设置：类型：“nghttp_2_pack_extension_callback”。
 *
 * 应用程序应保留|payload |所指的内存，直到完成扩展帧的传输（由：类型：“nghttp2_on_frame_send_callback”表示），或传输失败（由：“nghttp 2_on_fframe_not_send_cllback”表示。若应用程序在将该内存区域打包为有线格式后并没有触及该内存区域，则应用程序可以在内部释放该内存区域：type:`nghttp2_pack_extension_callback`。
 *
 * 无法使用此函数发送标准HTTP/2帧，因此|type|必须严格大于0x9。否则，此函数将失败，错误代码为enum:`NGHTTP2_ERR_INVALID_ARGUMENT`。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_INVALID_STATE`如果未设置：类型：`NGHTTP2_pack_extension_callback`。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT`If | type |指定标准HTTP/2帧类型。范围[0x0，0x9]中的帧类型（包括两者）是标准HTTP/2帧类型，无法使用此函数发送。：enum:`NGHTTP2_ERR_NOMEM`内存不足
 */
NGHTTP2_EXTERN int nghttp2_submit_extension(nghttp2_session *session,
                                            uint8_t type, uint8_t flags,
                                            int32_t stream_id, void *payload);

/**
 * @struct
 *
 * ALTSVC帧的有效载荷。ALTSVC帧是HTTP/2的非关键扩展。如果接收到此帧，并且未设置“nghttp2_option_set_user_recv_extension_type（）”，并且为enum:`nghttp2_ALTSVC`设置了“ngHTTP_2_option\uset_builtin_recv_expansion_type`”，则`nghttp2_extension.payload ``将指向此结构。
 *
 * 它有以下成员：
 */
typedef struct {
  /**
   * 指向与此替代服务关联的源的指针。这不一定以NULL结尾。
   */
  uint8_t *origin;
  /**
   * |原点|的长度。
   */
  size_t origin_len;
  /**
   * 指向ALTSVC帧中包含的Alt-Svc字段值的指针。这不一定以NULL结尾。
   */
  uint8_t *field_value;
  /**
   * |field_value|的长度。
   */
  size_t field_value_len;
} nghttp2_ext_altsvc;

/**
 * @function
 *
 * 提交ALTSVC帧。
 *
 * ALTSVC帧是HTTP/2的非关键扩展，在`RFC 7383中定义<https://tools.ietf.org/html/rfc7838#section-4>`_.
 *
 * |标志|当前被忽略，应为：enum:`NGHTTP2_FLAG_NONE`。
 *
 * |origin|指向此替代服务关联的源。|origin_len|是原点的长度。如果|stream_id|为0，则必须指定原点。如果|stream_id|不为零，则原点必须为空（换句话说，|origin_len|必须为0）。
 *
 * ALTSVC帧仅可从服务器端使用。如果使用客户端会话调用此函数，则此函数返回：enum:`NGHTTP2_ERR_INVALID_STATE`。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足：enum:` NGHTTP2_ERROR_INVALID_STATE`从客户端会话调用该函数：enum:`NGHTTP2_ERR_INVALID_ARGUMENT` |origin_len|和|field_value_len|之和大于16382；或|origin_len|为0，而|stream_id|为0；或|origin_len|不为0，而|stream_id|不为零。
 */
NGHTTP2_EXTERN int nghttp2_submit_altsvc(nghttp2_session *session,
                                         uint8_t flags, int32_t stream_id,
                                         const uint8_t *origin,
                                         size_t origin_len,
                                         const uint8_t *field_value,
                                         size_t field_value_len);

/**
 * @struct
 *
 * 原点的单个条目。
 */
typedef struct {
  /**
   * 指向原点的指针。库未对此字段进行验证。这不一定以NULL结尾。
   */
  uint8_t *origin;
  /**
   * |原点|的长度。
   */
  size_t origin_len;
} nghttp2_origin_entry;

/**
 * @struct
 *
 * ORIGIN帧的有效载荷。ORIGIN帧是HTTP/2的非关键扩展，由`RFC 8336定义<https://tools.ietf.org/html/rfc8336>`_.
 *
 * 如果接收到此帧，并且未设置“nghttp2_option_set_user_recv_extension_type（）”，并且为enum:`nghttp2_ORIGIN`，``nghttp2_extension设置了“ngHTTP1_option_set_built_recv_expansion_type（）”。有效负载“”将指向此结构。
 *
 * 它有以下成员：
 */
typedef struct {
  /**
   * |ov|中包含的原点数。
   */
  size_t nov;
  /**
   * 指向ORIGIN框架中包含的原点数组的指针。
   */
  nghttp2_origin_entry *ov;
} nghttp2_ext_origin;

/**
 * @function
 *
 * 提交ORIGIN框架。
 *
 * ORIGIN帧是HTTP/2的非关键扩展，由`RFC 8336定义<https://tools.ietf.org/html/rfc8336>`_.
 *
 * |标志|当前被忽略，应为：enum:`NGHTTP2_FLAG_NONE`。
 *
 * |ov|指向原点数组。|nov|指定|ov|中包含的原点数。此函数创建|ov|中所有元素的副本。
 *
 * ORIGIN框架仅可由服务器使用。如果使用客户端会话调用此函数，则此函数返回：enum:`NGHTTP2_ERR_INVALID_STATE`。
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足：enum:` NGHTTP2_ERROR_INVALID_STATE`从客户端会话调用函数。：enum:`NGHTTP2_ERR_INVALID_ARGUMENT`原点太多，或者原点太大，无法容纳默认帧负载。
 */
NGHTTP2_EXTERN int nghttp2_submit_origin(nghttp2_session *session,
                                         uint8_t flags,
                                         const nghttp2_origin_entry *ov,
                                         size_t nov);

/**
 * @function
 *
 * 比较长度为`lhs->name``字节的`lhs->名称``和长度为`rhs->name`字节的` rhs->名称`。如果发现``lhs->name``小于``rhs->name`，则返回负整数；如果发现`lhs->name``大于`rhs->name`，则返回正整数；否则返回0。
 */
NGHTTP2_EXTERN int nghttp2_nv_compare_name(const nghttp2_nv *lhs,
                                           const nghttp2_nv *rhs);

/**
 * @function
 *
 * 用于处理客户端NPN或服务器端ALPN的助手函数。|in|按优先顺序包含对等方的协议列表。|中|的格式以长度为前缀，而不是以空结尾。例如，“h2”和“http/1.1”存储在|in|中，如下所示：
 *
 *     in[0]=2 in[1..2]=“h2”in[3]=8 in[4..11]=“http/1.1”inlen=12
 *
 * 选择算法如下：
 *
 * 1.如果对等方列表包含库支持的HTTP/2协议，则选中该列表并返回1。不执行以下步骤。
 *
 * 2.如果对等方的列表包含“http/1.1”，则此函数选择“http/11.1”并返回0。不执行以下步骤。
 *
 * 3.此函数不选择任何内容并返回-1（所谓的非重叠情况）。在这种情况下，|out|和|outline|保持不变。
 *
 * 选择“h2”意味着“h2”被写入|*out|，其长度（2）被分配给|outlen|。
 *
 * 有关ALPN，请参阅https://tools.ietf.org/html/rfc7301
 *
 * 看见http://technotes.googlecode.com/git/nextprotoneg.html有关NPN的更多详细信息。
 *
 * 对于NPN，要使用此方法，您应该执行以下操作：
 *
 *     静态int select_next_proto_cb（SSL*SSL，无符号字符输出，无符号字符串输出，常量无符号字符输入，无符号整数输入，无效参数）｛int rv；rv=nghttp2_select_next _protocol（输出，输出，输入）；if（rv==-1）｛return SSL_TLSEXT_ERR_NOACK；｝如果（rv==1）｛（（MyType）arg）->http2_selected=1；｝返回SSL_TLSEXT_ERR_OK；｝。。。SSL_CTX_set_ext_proto_select_cb（SSL_CTX，select_next_proto_cb，my_obj）；
 *
 */
NGHTTP2_EXTERN int nghttp2_select_next_protocol(unsigned char **out,
                                                unsigned char *outlen,
                                                const unsigned char *in,
                                                unsigned int inlen);

/**
 * @function
 *
 * 返回指向nghttp2_info结构的指针，其中包含有关正在使用的运行时库的版本信息。对于最低接受版本号，|least_version|参数可以设置为24位数值，如果不满足该条件，则此函数将返回“NULL”。传入0以跳过版本检查。
 */
NGHTTP2_EXTERN nghttp2_info *nghttp2_version(int least_version);

/**
 * @function
 *
 * 如果：type:`nghttp2_error`库错误代码|lib_error|是致命的，则返回非零。
 */
NGHTTP2_EXTERN int nghttp2_is_fatal(int lib_error_code);

/**
 * @function
 *
 * 如果长度为|len|的HTTP标头字段名|name|根据http://tools.ietf.org/html/rfc7230#section-3.2
 *
 * 因为这是HTTP2中的头字段名，所以大写字母表被视为错误。
 */
NGHTTP2_EXTERN int nghttp2_check_header_name(const uint8_t *name, size_t len);

/**
 * @function
 *
 * 如果长度|len|的HTTP头字段值|value|根据http://tools.ietf.org/html/rfc7230#section-3.2
 */
NGHTTP2_EXTERN int nghttp2_check_header_value(const uint8_t *value, size_t len);

/**
 * @function
 *
 * 如果假定值为：authority或host标头字段的|value|根据https://tools.ietf.org/html/rfc3986#section-3.2
 *
 * |如果值|仅包含允许的字符，则该值有效。特别是，它不会检查|value|是否遵循authority的语法。
 */
NGHTTP2_EXTERN int nghttp2_check_authority(const uint8_t *value, size_t len);

/* HPACK API */

struct nghttp2_hd_deflater;

/**
 * @struct
 *
 * HPACK放气器对象。
 */
typedef struct nghttp2_hd_deflater nghttp2_hd_deflater;

/**
 * @function
 *
 * 为收缩名称/值对初始化|*deflater_ptr|。
 *
 * |max_deflate_dynamic_table_size|是deflater将使用的头表大小的上限。
 *
 * 如果此函数失败，|*deflater_ptr|将保持不变。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int
nghttp2_hd_deflate_new(nghttp2_hd_deflater **deflater_ptr,
                       size_t max_deflate_dynamic_table_size);

/**
 * @function
 *
 * 类似于“nghttp2_hd_deflate_new（）”，但在|mem|中指定了额外的自定义内存分配器。
 *
 * |mem|可以是“NULL”，调用等效于“nghttp2_hd_deflate_new（）”。
 *
 * 此函数不具有所有权|mem|。应用程序负责释放|mem|。
 *
 * 此函数返回后，库代码不引用|mem|指针，因此应用程序可以安全地释放它。
 */
NGHTTP2_EXTERN int
nghttp2_hd_deflate_new2(nghttp2_hd_deflater **deflater_ptr,
                        size_t max_deflate_dynamic_table_size,
                        nghttp2_mem *mem);

/**
 * @function
 *
 * 取消分配给|deflater|的所有资源。
 */
NGHTTP2_EXTERN void nghttp2_hd_deflate_del(nghttp2_hd_deflater *deflater);

/**
 * @function
 *
 * 将|deflater|的头表大小更改为|settings_max_dymic_table_size|字节。这可能会触发动态表中的逐出。
 *
 * |settings_max_dynamic_table_size |应为settings_HEADER_table_size中接收的值。
 *
 * deflater使用的内存永远不会超过“nghttp2_hd_deflate_new（）”中指定的“max_deflate_dynamic_table_size”字节。因此，如果|settings_max_dynamic_table_size |>``max_deflate_dynamic_table_size ``，则生成的最大表大小将变为`` max_deflae_dynamic_table_size``。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int
nghttp2_hd_deflate_change_table_size(nghttp2_hd_deflater *deflater,
                                     size_t settings_max_dynamic_table_size);

/**
 * @function
 *
 * 将具有|nvlen|名称/值对的|nva|压缩为长度|buflen|的|buf|。
 *
 * 如果|buf|不够大，无法存储收缩的标头块，则此函数将失败，并返回：enum:`NGHTTP2_ERR_INSUFF_BUFSIZE`。调用方应使用“nghttp2_hd_deflate_bound（）”来了解压缩给定标头名称/值对所需的缓冲区大小上限。
 *
 * 一旦此函数失败，此函数的后续调用始终返回：enum:`NGHTTP2_ERR_HEADER_COMP`。
 *
 * 此函数返回后，可以安全地删除|nva|。
 *
 * 如果成功，此函数将返回写入|buf|的字节数，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_HEADER_COMP`放气过程失败。：enum:`NGHTTP2_ERR_INSUFF_BUFSIZE`提供的|buflen|大小太小，无法容纳输出。
 */
NGHTTP2_EXTERN ssize_t nghttp2_hd_deflate_hd(nghttp2_hd_deflater *deflater,
                                             uint8_t *buf, size_t buflen,
                                             const nghttp2_nv *nva,
                                             size_t nvlen);

/**
 * @function
 *
 * 将具有|nvlen|名称/值对的|nva|压缩为buf vector|vec|的|veclen|大小。缓冲区的每个大小都必须在：type:`nghttp2_vec`的len字段中设置。若且仅当一个区块被完全填满时，将使用下一个区块。如果|vec|不够大，无法存储收缩的标头块，则此函数将失败，并返回：enum:`NGHTTP2_ERR_INSUFF_BUFSIZE`。调用方应使用“nghttp2_hd_deflate_bound（）”来了解压缩给定标头名称/值对所需的缓冲区大小上限。
 *
 * 一旦此函数失败，此函数的后续调用始终返回：enum:`NGHTTP2_ERR_HEADER_COMP`。
 *
 * 此函数返回后，可以安全地删除|nva|。
 *
 * 如果成功，此函数将返回写入|vec|的字节数，或返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_HEADER_COMP`放气过程失败。：enum:`NGHTTP2_ERR_INSUFF_BUFSIZE`提供的|buflen|大小太小，无法容纳输出。
 */
NGHTTP2_EXTERN ssize_t nghttp2_hd_deflate_hd_vec(nghttp2_hd_deflater *deflater,
                                                 const nghttp2_vec *vec,
                                                 size_t veclen,
                                                 const nghttp2_nv *nva,
                                                 size_t nvlen);

/**
 * @function
 *
 * 返回长度为|nvlen|的|nva|收缩后压缩大小的上限。
 */
NGHTTP2_EXTERN size_t nghttp2_hd_deflate_bound(nghttp2_hd_deflater *deflater,
                                               const nghttp2_nv *nva,
                                               size_t nvlen);

/**
 * @function
 *
 * 返回|deflater|的头表包含的项数。这是静态表和动态表的数量之和，因此返回值至少为61。
 */
NGHTTP2_EXTERN
size_t nghttp2_hd_deflate_get_num_table_entries(nghttp2_hd_deflater *deflater);

/**
 * @function
 *
 * 从|deflater|的头表中返回由|idx|表示的表项。|idx|从1开始，idx=1返回静态表的第一个条目。idx=62返回动态表的第一个条目（如果存在）。指定idx=0是错误的，此函数返回NULL。如果|idx|严格大于表包含的条目数，则此函数返回NULL。
 */
NGHTTP2_EXTERN
const nghttp2_nv *
nghttp2_hd_deflate_get_table_entry(nghttp2_hd_deflater *deflater, size_t idx);

/**
 * @function
 *
 * 返回使用的动态表大小，包括RFC 7541中描述的每个条目32字节的开销。
 */
NGHTTP2_EXTERN
size_t nghttp2_hd_deflate_get_dynamic_table_size(nghttp2_hd_deflater *deflater);

/**
 * @function
 *
 * 返回最大动态表大小。
 */
NGHTTP2_EXTERN
size_t
nghttp2_hd_deflate_get_max_dynamic_table_size(nghttp2_hd_deflater *deflater);

struct nghttp2_hd_inflater;

/**
 * @struct
 *
 * HPACK充气机对象。
 */
typedef struct nghttp2_hd_inflater nghttp2_hd_inflater;

/**
 * @function
 *
 * 为扩展名称/值对初始化|*inflater_ptr|。
 *
 * 如果此函数失败，|*inflater_ptr|将保持不变。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
NGHTTP2_EXTERN int nghttp2_hd_inflate_new(nghttp2_hd_inflater **inflater_ptr);

/**
 * @function
 *
 * 类似于“nghttp2_hd_inflate_new（）”，但在|mem|中指定了额外的自定义内存分配器。
 *
 * |mem|可以是“NULL”，调用等效于“nghttp2_hd_inflate_new（）”。
 *
 * 此函数不具有所有权|mem|。应用程序负责释放|mem|。
 *
 * 此函数返回后，库代码不引用|mem|指针，因此应用程序可以安全地释放它。
 */
NGHTTP2_EXTERN int nghttp2_hd_inflate_new2(nghttp2_hd_inflater **inflater_ptr,
                                           nghttp2_mem *mem);

/**
 * @function
 *
 * 取消分配给|inflater|的所有资源。
 */
NGHTTP2_EXTERN void nghttp2_hd_inflate_del(nghttp2_hd_inflater *inflater);

/**
 * @function
 *
 * 更改|充气机|中的标题表格大小。这可能会触发动态表中的逐出。
 *
 * |settings_max_dynamic_table_size|应为settings_HEADER_table_size中传输的值。
 *
 * 当标题块膨胀时，不能调用此函数。换句话说，此函数必须在初始化|inflater |之后，但必须在调用“nghttp2_hd_inflate_hd2（）”之前，或在“nghttp 2_hd_inflate_end_headers（）”之后调用。否则，返回`NGHTTP2_ERR_INVALID_STATE`。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_INVALID_STATE`在标头块膨胀时调用该函数。很可能，应用程序未能调用“nghttp2_hd_inflate_end_headers（）”。
 */
NGHTTP2_EXTERN int
nghttp2_hd_inflate_change_table_size(nghttp2_hd_inflater *inflater,
                                     size_t settings_max_dynamic_table_size);

/**
 * @enum
 *
 * 收割台充气标志。
 */
typedef enum {
  /**
   * 未设置标志。
   */
  NGHTTP2_HD_INFLATE_NONE = 0,
  /**
   * 表示所有收割台均已充气。
   */
  NGHTTP2_HD_INFLATE_FINAL = 0x01,
  /**
   * 指示已发出标头。
   */
  NGHTTP2_HD_INFLATE_EMIT = 0x02
} nghttp2_hd_inflate_flag;

/**
 * @function
 *
 * ..警告：：
 *
 *   已弃用。请改用“nghttp2_hd_inflate_hd2（）”。
 *
 * 用长度|inlen|填充存储在|in|中的名称/值块。此函数执行解压缩。对于头名称/值对的每一次成功发射，：enum:`NGHTTP2_HD_INFLATE_EMIT `在|INFLATE_flags|中设置，名称/值配对被分配给|nv_out|，函数返回。调用者不能释放|nv_out|的成员。
 *
 * |nv_out|可以包括指向|in|中的内存区域的指针。使用|nv_out|时，调用者必须保留|in|。
 *
 * 应用程序应重复调用此函数，直到``（inflate_flags）&NGHTTP2_HD_inflate_FINAL`为非零且返回值为非负。这意味着所有输入值都已成功处理。然后，应用程序必须调用“nghttp2_hd_inflate_end_headers（）”以准备下一个头块输入。
 *
 * 调用者可以输入完整的压缩头块。它还可以分几块喂它。如果给定的输入是压缩头的最后一个块，则调用者必须将|in_final|设置为非零。
 *
 * 如果成功，此函数将返回处理的字节数，或返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_HEADER_COMP`通货膨胀过程失败。：enum:`NGHTTP2_ERR_BUFFER_ERROR`标头字段名或值太大。
 *
 * 示例如下：
 *
 *     int inflate_header_block（nghttp2_hd_inflater*hd_inflater，uint8_t in，size_t inlen，int final）{ssize_t rv；
 *
 *         用于（；；）{nghttp2_nv-nv；int inflate_flags=0；
 *
 *             rv=nghttp2_hd_inflate_hd（hd_inflater，&nv，&inflate_flags，in，inlen，final）；
 *
 *             如果（rv＜0）｛fprintf（stderr，“充气失败，错误代码%zd”，rv）；返回-1；｝
 *
 *             in+=rv；inlen-=rv；
 *
 *             if（inflate_flags&NGHTTP2_HD_inflate_EMIT）｛fwrite（nv.name，nv.namelen，1，stderr）；fprintf（stderr，“：”）；fwrite如果（充气标志&NGHTTP2_HD_inflate_FINAL）｛NGHTTP2_HD_inflate_end_headers（HD_inflater）；break；｝如果（（inflate_flags&NGHTTP2_HD_inflate_EMIT）==0&&inlen==0）{break；}}
 *
 *         返回0；｝
 *
 */
NGHTTP2_EXTERN ssize_t nghttp2_hd_inflate_hd(nghttp2_hd_inflater *inflater,
                                             nghttp2_nv *nv_out,
                                             int *inflate_flags, uint8_t *in,
                                             size_t inlen, int in_final);

/**
 * @function
 *
 * 用长度|inlen|填充存储在|in|中的名称/值块。此函数执行解压缩。对于头名称/值对的每一次成功发射，：enum:`NGHTTP2_HD_INFLATE_EMIT `在|INFLATE_flags|中设置，名称/值配对被分配给|nv_out|，函数返回。调用者不能释放|nv_out|的成员。
 *
 * |nv_out|可以包括指向|in|中的内存区域的指针。使用|nv_out|时，调用者必须保留|in|。
 *
 * 应用程序应重复调用此函数，直到``（inflate_flags）&NGHTTP2_HD_inflate_FINAL`为非零且返回值为非负。如果发生这种情况，所有给定的输入数据（|inlen|字节）都将被成功处理。然后，应用程序必须调用“nghttp2_hd_inflate_end_headers（）”以准备下一个头块输入。
 *
 * 换句话说，如果|In_final|为非零，并且此函数返回|inlen|，则可以断言：enum:`NGHTTP2_HD_INFLATE_final`在|INFLATE_flags|中设置。
 *
 * 调用者可以输入完整的压缩头块。它还可以分几块喂它。如果给定的输入是压缩头的最后一个块，则调用者必须将|in_final|设置为非零。
 *
 * 如果成功，此函数将返回处理的字节数，或返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。：enum:`NGHTTP2_ERR_HEADER_COMP`通货膨胀过程失败。：enum:`NGHTTP2_ERR_BUFFER_ERROR`标头字段名或值太大。
 *
 * 示例如下：
 *
 *     int inflate_header_block（nghttp2_hd_inflater*hd_inflater，uint8_t in，size_t inlen，int final）{ssize_t rv；
 *
 *         用于（；；）{nghttp2_nv-nv；int inflate_flags=0；
 *
 *             rv=nghttp2_hd_inflate_hd2（hd_inflater，&nv，&inflate_flags，in，inlen，final）；
 *
 *             如果（rv＜0）｛fprintf（stderr，“充气失败，错误代码%zd”，rv）；返回-1；｝
 *
 *             in+=rv；inlen-=rv；
 *
 *             if（inflate_flags&NGHTTP2_HD_inflate_EMIT）｛fwrite（nv.name，nv.namelen，1，stderr）；fprintf（stderr，“：”）；fwrite如果（充气标志&NGHTTP2_HD_inflate_FINAL）｛NGHTTP2_HD_inflate_end_headers（HD_inflater）；break；｝如果（（inflate_flags&NGHTTP2_HD_inflate_EMIT）==0&&inlen==0）{break；}}
 *
 *         返回0；｝
 *
 */
NGHTTP2_EXTERN ssize_t nghttp2_hd_inflate_hd2(nghttp2_hd_inflater *inflater,
                                              nghttp2_nv *nv_out,
                                              int *inflate_flags,
                                              const uint8_t *in, size_t inlen,
                                              int in_final);

/**
 * @function
 *
 * 发出一个标题块解压缩结束的信号。
 *
 * 如果成功，此函数将返回0。目前，此功能始终成功。
 */
NGHTTP2_EXTERN int
nghttp2_hd_inflate_end_headers(nghttp2_hd_inflater *inflater);

/**
 * @function
 *
 * 返回|inflater|的标题表包含的项数。这是静态表和动态表的数量之和，因此返回值至少为61。
 */
NGHTTP2_EXTERN
size_t nghttp2_hd_inflate_get_num_table_entries(nghttp2_hd_inflater *inflater);

/**
 * @function
 *
 * 从|inflater|的头表中返回由|idx|表示的表项。|idx|从1开始，idx=1返回静态表的第一个条目。idx=62返回动态表的第一个条目（如果存在）。指定idx=0是错误的，此函数返回NULL。如果|idx|严格大于表包含的条目数，则此函数返回NULL。
 */
NGHTTP2_EXTERN
const nghttp2_nv *
nghttp2_hd_inflate_get_table_entry(nghttp2_hd_inflater *inflater, size_t idx);

/**
 * @function
 *
 * 返回使用的动态表大小，包括RFC 7541中描述的每个条目32字节的开销。
 */
NGHTTP2_EXTERN
size_t nghttp2_hd_inflate_get_dynamic_table_size(nghttp2_hd_inflater *inflater);

/**
 * @function
 *
 * 返回最大动态表大小。
 */
NGHTTP2_EXTERN
size_t
nghttp2_hd_inflate_get_max_dynamic_table_size(nghttp2_hd_inflater *inflater);

struct nghttp2_stream;

/**
 * @struct
 *
 * 表示HTTP/2流的结构。此结构的详细信息有意隐藏在公共API中。
 */
typedef struct nghttp2_stream nghttp2_stream;

/**
 * @function
 *
 * 返回指向：type:`nghttp2_stream`对象的指针，该对象由|stream_id|表示。如果未找到流，则返回NULL。
 *
 * 如果在|stream_id|中给定0，则返回虚根流（请参见“nghttp2_session_get_root_stream（）”）。
 *
 * 除非|stream_id |==0，否则返回的指针在下一次调用“nghttp2_session_send（）”、“nghttp 2_session_me_send（）”和“nghttp 2-session_me_recv（）”之前有效。
 */
NGHTTP2_EXTERN nghttp2_stream *
nghttp2_session_find_stream(nghttp2_session *session, int32_t stream_id);

/**
 * @enum
 *
 * RFC 7540中描述的流状态。
 */
typedef enum {
  /**
   * 空闲状态。
   */
  NGHTTP2_STREAM_STATE_IDLE = 1,
  /**
   * 打开状态。
   */
  NGHTTP2_STREAM_STATE_OPEN,
  /**
   * 保留（本地）状态。
   */
  NGHTTP2_STREAM_STATE_RESERVED_LOCAL,
  /**
   * 保留（远程）状态。
   */
  NGHTTP2_STREAM_STATE_RESERVED_REMOTE,
  /**
   * 半关闭（局部）状态。
   */
  NGHTTP2_STREAM_STATE_HALF_CLOSED_LOCAL,
  /**
   * 半关闭（远程）状态。
   */
  NGHTTP2_STREAM_STATE_HALF_CLOSED_REMOTE,
  /**
   * 关闭状态。
   */
  NGHTTP2_STREAM_STATE_CLOSED
} nghttp2_stream_proto_state;

/**
 * @function
 *
 * 返回|stream|的状态。“nghttp2_session_get_root_stream（）”检索的根流将具有流状态：enum:`nghttp2_stream_state_IDLE`。
 */
NGHTTP2_EXTERN nghttp2_stream_proto_state
nghttp2_stream_get_state(nghttp2_stream *stream);

/**
 * @function
 *
 * 返回依赖关系树的根，它是流ID为0的虚拟流。返回的指针在|session|被`nghttp2_session_del（）`释放之前有效。
 */
NGHTTP2_EXTERN nghttp2_stream *
nghttp2_session_get_root_stream(nghttp2_session *session);

/**
 * @function
 *
 * 返回依赖关系树中|stream|的父流。如果没有这样的流，则返回NULL。
 */
NGHTTP2_EXTERN nghttp2_stream *
nghttp2_stream_get_parent(nghttp2_stream *stream);

NGHTTP2_EXTERN int32_t nghttp2_stream_get_stream_id(nghttp2_stream *stream);

/**
 * @function
 *
 * 返回依赖关系树中|stream|的下一个同级流。如果没有这样的流，则返回NULL。
 */
NGHTTP2_EXTERN nghttp2_stream *
nghttp2_stream_get_next_sibling(nghttp2_stream *stream);

/**
 * @function
 *
 * 返回依赖关系树中|stream|的上一个同级流。如果没有这样的流，则返回NULL。
 */
NGHTTP2_EXTERN nghttp2_stream *
nghttp2_stream_get_previous_sibling(nghttp2_stream *stream);

/**
 * @function
 *
 * 返回依赖关系树中|stream|的第一个子流。如果没有这样的流，则返回NULL。
 */
NGHTTP2_EXTERN nghttp2_stream *
nghttp2_stream_get_first_child(nghttp2_stream *stream);

/**
 * @function
 *
 * 返回|stream|的父流的依赖权重。
 */
NGHTTP2_EXTERN int32_t nghttp2_stream_get_weight(nghttp2_stream *stream);

/**
 * @function
 *
 * 返回|stream|的子项的权重之和。
 */
NGHTTP2_EXTERN int32_t
nghttp2_stream_get_sum_dependency_weight(nghttp2_stream *stream);

/**
 * @functypedef
 *
 * 当库输出调试日志时调用回调函数。使用适用于“”vfprintf（3）的参数调用该函数``
 *
 * 只有在使用定义的“DEBUGBILD”宏构建库时，才会启用调试输出。
 */
typedef void (*nghttp2_debug_vprintf_callback)(const char *format,
                                               va_list args);

/**
 * @function
 *
 * 当使用定义的“DEBUGBILD”宏生成时，设置库调用的调试输出回调。如果未使用此选项，调试日志将写入标准错误输出。
 *
 * 对于未定义“DEBUGBILD”宏的生成，此函数为noop。
 *
 * 注意，由于额外的处理，使用“DEBUGBILD”进行构建可能会对libnghttp2造成严重的性能损失。它只能用于调试目的。
 *
 * ..警告：：
 *
 *   由于额外的处理，使用“DEBUGBILD”生成可能会对libnghttp 2造成严重的性能损失。它只能用于调试目的。我们写了两次，因为这很重要。
 */
NGHTTP2_EXTERN void nghttp2_set_debug_vprintf_callback(
    nghttp2_debug_vprintf_callback debug_vprintf_callback);

#ifdef __cplusplus
}
#endif

#endif /* NGHTTP2_H */

