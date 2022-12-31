/* 版权所有Joyent，Inc.和其他Node贡献者。保留所有权利。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef http_parser_h
#define http_parser_h
#ifdef __cplusplus
extern "C" {
#endif

/* 每当您更改这些时，还要更新Makefile中的SONAME。*/
#define HTTP_PARSER_VERSION_MAJOR 2
#define HTTP_PARSER_VERSION_MINOR 7
#define HTTP_PARSER_VERSION_PATCH 0

#include <sys/types.h>
#if defined(_WIN32) && !defined(__MINGW32__) && \
  (!defined(_MSC_VER) || _MSC_VER<1600) && !defined(__WINE__)
#include <BaseTsd.h>
#include <stddef.h>
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

/* 使用-DHTTP_PARTSER_STRICT=0进行编译以减少检查，但运行速度更快
 */
#ifndef HTTP_PARSER_STRICT
# define HTTP_PARSER_STRICT 1
#endif

/* 允许的最大标头大小。如果在包含此标头之前未定义宏，则使用默认值。要更改最大标头大小，请在构建环境中定义宏（例如-DHTTP_MAX_header_size=<value>）。要删除标头大小的有效限制，请将宏定义为非常大的数字（例如-DHTTP_MAX_header_size=0x7fffffff）
 */
#ifndef HTTP_MAX_HEADER_SIZE
# define HTTP_MAX_HEADER_SIZE (80*1024)
#endif

typedef struct http_parser http_parser;
typedef struct http_parser_settings http_parser_settings;


/* 回调应返回非零以指示错误。然后解析器将停止执行。
 *
 * 一个例外是on_headers_complete。在HTTP_RESPONSE解析器中，从on_headers_complete返回“1”将告诉解析器它不应该有正文。这在接收HEAD请求的响应时使用，HEAD请求可能包含“Content-Length”或“Transfer Encoding:chunked”标头，这些标头指示主体的存在。
 *
 * 从on_headers_complete返回“2”将告诉解析器，它不应该期望在这个连接上既没有正文也没有任何进一步的响应。这对于处理可能不包含“Upgrade”或“Connection:Upgrade”标头的CONNECT请求的响应非常有用。
 *
 * http_data_cb不返回数据块。对于每个字符串，它将被任意调用多次。E、 G.您可能会得到10个“on_url”回调，每个回调只提供几个字符的数据。
 */
typedef int (*http_data_cb) (http_parser*, const char *at, size_t length);
typedef int (*http_cb) (http_parser*);


/* 请求方法*/
#define HTTP_METHOD_MAP(XX)         \
  XX(0,  DELETE,      DELETE)       \
  XX(1,  GET,         GET)          \
  XX(2,  HEAD,        HEAD)         \
  XX(3,  POST,        POST)         \
  XX(4,  PUT,         PUT)          \
  /* 不理智的*/                \
  XX(5,  CONNECT,     CONNECT)      \
  XX(6,  OPTIONS,     OPTIONS)      \
  XX(7,  TRACE,       TRACE)        \
  /* 网络DAV*/                      \
  XX(8,  COPY,        COPY)         \
  XX(9,  LOCK,        LOCK)         \
  XX(10, MKCOL,       MKCOL)        \
  XX(11, MOVE,        MOVE)         \
  XX(12, PROPFIND,    PROPFIND)     \
  XX(13, PROPPATCH,   PROPPATCH)    \
  XX(14, SEARCH,      SEARCH)       \
  XX(15, UNLOCK,      UNLOCK)       \
  XX(16, BIND,        BIND)         \
  XX(17, REBIND,      REBIND)       \
  XX(18, UNBIND,      UNBIND)       \
  XX(19, ACL,         ACL)          \
  /* 颠覆，颠覆*/                  \
  XX(20, REPORT,      REPORT)       \
  XX(21, MKACTIVITY,  MKACTIVITY)   \
  XX(22, CHECKOUT,    CHECKOUT)     \
  XX(23, MERGE,       MERGE)        \
  /* upnp语言*/                        \
  XX(24, MSEARCH,     M-SEARCH)     \
  XX(25, NOTIFY,      NOTIFY)       \
  XX(26, SUBSCRIBE,   SUBSCRIBE)    \
  XX(27, UNSUBSCRIBE, UNSUBSCRIBE)  \
  /* RFC-5789 */                    \
  XX(28, PATCH,       PATCH)        \
  XX(29, PURGE,       PURGE)        \
  /* CalDAV公司*/                      \
  XX(30, MKCALENDAR,  MKCALENDAR)   \
  /* RFC-2068，第19.6.1.2节*/  \
  XX(31, LINK,        LINK)         \
  XX(32, UNLINK,      UNLINK)       \

enum http_method
  {
#define XX(num, name, string) HTTP_##name = num,
  HTTP_METHOD_MAP(XX)
#undef XX
  };


enum http_parser_type { HTTP_REQUEST, HTTP_RESPONSE, HTTP_BOTH };


/* http_parser的标志值。标志字段*/
enum flags
  { F_CHUNKED               = 1 << 0
  , F_CONNECTION_KEEP_ALIVE = 1 << 1
  , F_CONNECTION_CLOSE      = 1 << 2
  , F_CONNECTION_UPGRADE    = 1 << 3
  , F_TRAILING              = 1 << 4
  , F_UPGRADE               = 1 << 5
  , F_SKIPBODY              = 1 << 6
  , F_CONTENTLENGTH         = 1 << 7
  };


/* errno相关常量的映射
 *
 * 提供的参数应该是一个接受2个参数的宏。
 */
#define HTTP_ERRNO_MAP(XX)                                           \
  /* 无错误*/                                                     \
  XX(OK, "success")                                                  \
                                                                     \
  /* 回调相关错误*/                                      \
  XX(CB_message_begin, "the on_message_begin callback failed")       \
  XX(CB_url, "the on_url callback failed")                           \
  XX(CB_header_field, "the on_header_field callback failed")         \
  XX(CB_header_value, "the on_header_value callback failed")         \
  XX(CB_headers_complete, "the on_headers_complete callback failed") \
  XX(CB_body, "the on_body callback failed")                         \
  XX(CB_message_complete, "the on_message_complete callback failed") \
  XX(CB_status, "the on_status callback failed")                     \
  XX(CB_chunk_header, "the on_chunk_header callback failed")         \
  XX(CB_chunk_complete, "the on_chunk_complete callback failed")     \
                                                                     \
  /* 分析相关错误*/                                       \
  XX(INVALID_EOF_STATE, "stream ended at an unexpected time")        \
  XX(HEADER_OVERFLOW,                                                \
     "too many header bytes seen; overflow detected")                \
  XX(CLOSED_CONNECTION,                                              \
     "data received after completed connection: close message")      \
  XX(INVALID_VERSION, "invalid HTTP version")                        \
  XX(INVALID_STATUS, "invalid HTTP status code")                     \
  XX(INVALID_METHOD, "invalid HTTP method")                          \
  XX(INVALID_URL, "invalid URL")                                     \
  XX(INVALID_HOST, "invalid host")                                   \
  XX(INVALID_PORT, "invalid port")                                   \
  XX(INVALID_PATH, "invalid path")                                   \
  XX(INVALID_QUERY_STRING, "invalid query string")                   \
  XX(INVALID_FRAGMENT, "invalid fragment")                           \
  XX(LF_EXPECTED, "LF character expected")                           \
  XX(INVALID_HEADER_TOKEN, "invalid character in header")            \
  XX(INVALID_CONTENT_LENGTH,                                         \
     "invalid character in content-length header")                   \
  XX(UNEXPECTED_CONTENT_LENGTH,                                      \
     "unexpected content-length header")                             \
  XX(INVALID_CHUNK_SIZE,                                             \
     "invalid character in chunk size header")                       \
  XX(INVALID_CONSTANT, "invalid constant string")                    \
  XX(INVALID_INTERNAL_STATE, "encountered unexpected internal state")\
  XX(STRICT, "strict mode assertion failed")                         \
  XX(PAUSED, "parser is paused")                                     \
  XX(UNKNOWN, "an unknown error occurred")


/* 为上面的每个errno值定义HPE_*值*/
#define HTTP_ERRNO_GEN(n, s) HPE_##n,
enum http_errno {
  HTTP_ERRNO_MAP(HTTP_ERRNO_GEN)
};
#undef HTTP_ERRNO_GEN


/* 从http_parser获取http_errno值*/
#define HTTP_PARSER_ERRNO(p)            ((enum http_errno) (p)->http_errno)


struct http_parser {
  /** PRIVATE **/
  unsigned int type : 2;         /* 枚举http_parser_type*/
  unsigned int flags : 8;        /* “flags”枚举中的F_*值；半公开的*/
  unsigned int state : 7;        /* http_parser中的枚举状态。c*/
  unsigned int header_state : 7; /* http_parser中的enum header_state。c*/
  unsigned int index : 7;        /* 索引到当前匹配器*/
  unsigned int lenient_http_headers : 1;

  uint32_t nread;          /* #在各种情况下读取的字节数*/
  uint64_t content_length; /* #正文中的字节数（如果没有Content-Length标头，则为0）*/

  /** READ-ONLY **/
  unsigned short http_major;
  unsigned short http_minor;
  unsigned int status_code : 16; /* 仅响应*/
  unsigned int method : 8;       /* 仅限请求*/
  unsigned int http_errno : 7;

  /* 1=存在升级标头，因此解析器已退出。0=不存在升级标头。除了错误检查之外，当http_parser_execute（）返回时还应检查。
   */
  unsigned int upgrade : 1;

  /** PUBLIC **/
  void *data; /* 获取“连接”或“套接字”对象挂钩的指针*/
};


struct http_parser_settings {
  http_cb      on_message_begin;
  http_data_cb on_url;
  http_data_cb on_status;
  http_data_cb on_header_field;
  http_data_cb on_header_value;
  http_cb      on_headers_complete;
  http_data_cb on_body;
  http_cb      on_message_complete;
  /* 当调用on_cchunk_header时，当前块长度存储在parser->content_length中。
   */
  http_cb      on_chunk_header;
  http_cb      on_chunk_complete;
};


enum http_parser_url_fields
  { UF_SCHEMA           = 0
  , UF_HOST             = 1
  , UF_PORT             = 2
  , UF_PATH             = 3
  , UF_QUERY            = 4
  , UF_FRAGMENT         = 5
  , UF_USERINFO         = 6
  , UF_MAX              = 7
  };


/* http_parser_parse_url（）的结果结构。
 *
 * 如果field_set设置了相关（1<<UF_）位，则调用方应使用UF_*值索引field_data[]。作为对客户端的礼貌（并且因为我们可能还剩下填充），我们将任何端口转换为uint16_t。
 */
struct http_parser_url {
  uint16_t field_set;           /* （1<<UF_*）值的位掩码*/
  uint16_t port;                /* 转换的UF_PORT字符串*/

  struct {
    uint16_t off;               /* 字段开始的缓冲区偏移量*/
    uint16_t len;               /* 磨合缓冲区长度*/
  } field_data[UF_MAX];
};


/* 返回库版本。位16-23包含主要版本号，位8-15包含次要版本号，而位0-7包含补丁级别。用法示例：
 *
 *   无符号长版本=http_parser_version（）；无符号major=（版本>>16）&255；无符号小调=（版本>>8）&255；无符号补丁=版本&255；printf（“http_parser v%u.%u.%u\n”，主要，次要，修补程序）；
 */
unsigned long http_parser_version(void);

void http_parser_init(http_parser *parser, enum http_parser_type type);


/* 将http_parser_settings成员初始化为0
 */
void http_parser_settings_init(http_parser_settings *settings);


/* 执行分析器。返回已分析的字节数。错误时设置`parser->http_errno`。*/
size_t http_parser_execute(http_parser *parser,
                           const http_parser_settings *settings,
                           const char *data,
                           size_t len);


/* 如果on_headers_complete或on_message_complete回调中的http_sshould_keep_alive（）返回0，则这应该是连接上的最后一条消息。如果您是服务器，请使用“Connection:close”标头进行响应。如果您是客户端，请关闭连接。
 */
int http_should_keep_alive(const http_parser *parser);

/* 返回HTTP方法的字符串版本。*/
const char *http_method_str(enum http_method m);

/* 返回给定错误的字符串名称*/
const char *http_errno_name(enum http_errno err);

/* 返回给定错误的字符串描述*/
const char *http_errno_description(enum http_errno err);

/* 将所有http_parser_url成员初始化为0*/
void http_parser_url_init(struct http_parser_url *u);

/* 解析URL；失败时返回非零*/
int http_parser_parse_url(const char *buf, size_t buflen,
                          int is_connect,
                          struct http_parser_url *u);

/* 暂停或取消暂停解析器；非零值暂停*/
void http_parser_pause(http_parser *parser, int paused);

/* 检查这是否是身体的最后一块。*/
int http_body_is_final(const http_parser *parser);

#ifdef __cplusplus
}
#endif
#endif

