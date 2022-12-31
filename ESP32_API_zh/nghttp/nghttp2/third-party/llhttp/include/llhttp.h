#ifndef INCLUDE_LLHTTP_H_
#define INCLUDE_LLHTTP_H_

#define LLHTTP_VERSION_MAJOR 2
#define LLHTTP_VERSION_MINOR 0
#define LLHTTP_VERSION_PATCH 4

#ifndef INCLUDE_LLHTTP_ITSELF_H_
#define INCLUDE_LLHTTP_ITSELF_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct llhttp__internal_s llhttp__internal_t;
struct llhttp__internal_s {
  int32_t _index;
  void* _span_pos0;
  void* _span_cb0;
  int32_t error;
  const char* reason;
  const char* error_pos;
  void* data;
  void* _current;
  uint64_t content_length;
  uint8_t type;
  uint8_t method;
  uint8_t http_major;
  uint8_t http_minor;
  uint8_t header_state;
  uint16_t flags;
  uint8_t upgrade;
  uint16_t status_code;
  uint8_t finish;
  void* settings;
};

int llhttp__internal_init(llhttp__internal_t* s);
int llhttp__internal_execute(llhttp__internal_t* s, const char* p, const char* endp);

#ifdef __cplusplus
}  /* 外部“C”*/
#endif
#endif  /* INCLUDE_LLHTTP_ITSELF_H_ */

#ifndef LLLLHTTP_C_HEADERS_
#define LLLLHTTP_C_HEADERS_
#ifdef __cplusplus
extern "C" {
#endif

enum llhttp_errno {
  HPE_OK = 0,
  HPE_INTERNAL = 1,
  HPE_STRICT = 2,
  HPE_LF_EXPECTED = 3,
  HPE_UNEXPECTED_CONTENT_LENGTH = 4,
  HPE_CLOSED_CONNECTION = 5,
  HPE_INVALID_METHOD = 6,
  HPE_INVALID_URL = 7,
  HPE_INVALID_CONSTANT = 8,
  HPE_INVALID_VERSION = 9,
  HPE_INVALID_HEADER_TOKEN = 10,
  HPE_INVALID_CONTENT_LENGTH = 11,
  HPE_INVALID_CHUNK_SIZE = 12,
  HPE_INVALID_STATUS = 13,
  HPE_INVALID_EOF_STATE = 14,
  HPE_INVALID_TRANSFER_ENCODING = 15,
  HPE_CB_MESSAGE_BEGIN = 16,
  HPE_CB_HEADERS_COMPLETE = 17,
  HPE_CB_MESSAGE_COMPLETE = 18,
  HPE_CB_CHUNK_HEADER = 19,
  HPE_CB_CHUNK_COMPLETE = 20,
  HPE_PAUSED = 21,
  HPE_PAUSED_UPGRADE = 22,
  HPE_USER = 23
};
typedef enum llhttp_errno llhttp_errno_t;

enum llhttp_flags {
  F_CONNECTION_KEEP_ALIVE = 0x1,
  F_CONNECTION_CLOSE = 0x2,
  F_CONNECTION_UPGRADE = 0x4,
  F_CHUNKED = 0x8,
  F_UPGRADE = 0x10,
  F_CONTENT_LENGTH = 0x20,
  F_SKIPBODY = 0x40,
  F_TRAILING = 0x80,
  F_LENIENT = 0x100,
  F_TRANSFER_ENCODING = 0x200
};
typedef enum llhttp_flags llhttp_flags_t;

enum llhttp_type {
  HTTP_BOTH = 0,
  HTTP_REQUEST = 1,
  HTTP_RESPONSE = 2
};
typedef enum llhttp_type llhttp_type_t;

enum llhttp_finish {
  HTTP_FINISH_SAFE = 0,
  HTTP_FINISH_SAFE_WITH_CB = 1,
  HTTP_FINISH_UNSAFE = 2
};
typedef enum llhttp_finish llhttp_finish_t;

enum llhttp_method {
  HTTP_DELETE = 0,
  HTTP_GET = 1,
  HTTP_HEAD = 2,
  HTTP_POST = 3,
  HTTP_PUT = 4,
  HTTP_CONNECT = 5,
  HTTP_OPTIONS = 6,
  HTTP_TRACE = 7,
  HTTP_COPY = 8,
  HTTP_LOCK = 9,
  HTTP_MKCOL = 10,
  HTTP_MOVE = 11,
  HTTP_PROPFIND = 12,
  HTTP_PROPPATCH = 13,
  HTTP_SEARCH = 14,
  HTTP_UNLOCK = 15,
  HTTP_BIND = 16,
  HTTP_REBIND = 17,
  HTTP_UNBIND = 18,
  HTTP_ACL = 19,
  HTTP_REPORT = 20,
  HTTP_MKACTIVITY = 21,
  HTTP_CHECKOUT = 22,
  HTTP_MERGE = 23,
  HTTP_MSEARCH = 24,
  HTTP_NOTIFY = 25,
  HTTP_SUBSCRIBE = 26,
  HTTP_UNSUBSCRIBE = 27,
  HTTP_PATCH = 28,
  HTTP_PURGE = 29,
  HTTP_MKCALENDAR = 30,
  HTTP_LINK = 31,
  HTTP_UNLINK = 32,
  HTTP_SOURCE = 33
};
typedef enum llhttp_method llhttp_method_t;

#define HTTP_ERRNO_MAP(XX) \
  XX(0, OK, OK) \
  XX(1, INTERNAL, INTERNAL) \
  XX(2, STRICT, STRICT) \
  XX(3, LF_EXPECTED, LF_EXPECTED) \
  XX(4, UNEXPECTED_CONTENT_LENGTH, UNEXPECTED_CONTENT_LENGTH) \
  XX(5, CLOSED_CONNECTION, CLOSED_CONNECTION) \
  XX(6, INVALID_METHOD, INVALID_METHOD) \
  XX(7, INVALID_URL, INVALID_URL) \
  XX(8, INVALID_CONSTANT, INVALID_CONSTANT) \
  XX(9, INVALID_VERSION, INVALID_VERSION) \
  XX(10, INVALID_HEADER_TOKEN, INVALID_HEADER_TOKEN) \
  XX(11, INVALID_CONTENT_LENGTH, INVALID_CONTENT_LENGTH) \
  XX(12, INVALID_CHUNK_SIZE, INVALID_CHUNK_SIZE) \
  XX(13, INVALID_STATUS, INVALID_STATUS) \
  XX(14, INVALID_EOF_STATE, INVALID_EOF_STATE) \
  XX(15, INVALID_TRANSFER_ENCODING, INVALID_TRANSFER_ENCODING) \
  XX(16, CB_MESSAGE_BEGIN, CB_MESSAGE_BEGIN) \
  XX(17, CB_HEADERS_COMPLETE, CB_HEADERS_COMPLETE) \
  XX(18, CB_MESSAGE_COMPLETE, CB_MESSAGE_COMPLETE) \
  XX(19, CB_CHUNK_HEADER, CB_CHUNK_HEADER) \
  XX(20, CB_CHUNK_COMPLETE, CB_CHUNK_COMPLETE) \
  XX(21, PAUSED, PAUSED) \
  XX(22, PAUSED_UPGRADE, PAUSED_UPGRADE) \
  XX(23, USER, USER) \


#define HTTP_METHOD_MAP(XX) \
  XX(0, DELETE, DELETE) \
  XX(1, GET, GET) \
  XX(2, HEAD, HEAD) \
  XX(3, POST, POST) \
  XX(4, PUT, PUT) \
  XX(5, CONNECT, CONNECT) \
  XX(6, OPTIONS, OPTIONS) \
  XX(7, TRACE, TRACE) \
  XX(8, COPY, COPY) \
  XX(9, LOCK, LOCK) \
  XX(10, MKCOL, MKCOL) \
  XX(11, MOVE, MOVE) \
  XX(12, PROPFIND, PROPFIND) \
  XX(13, PROPPATCH, PROPPATCH) \
  XX(14, SEARCH, SEARCH) \
  XX(15, UNLOCK, UNLOCK) \
  XX(16, BIND, BIND) \
  XX(17, REBIND, REBIND) \
  XX(18, UNBIND, UNBIND) \
  XX(19, ACL, ACL) \
  XX(20, REPORT, REPORT) \
  XX(21, MKACTIVITY, MKACTIVITY) \
  XX(22, CHECKOUT, CHECKOUT) \
  XX(23, MERGE, MERGE) \
  XX(24, MSEARCH, M-SEARCH) \
  XX(25, NOTIFY, NOTIFY) \
  XX(26, SUBSCRIBE, SUBSCRIBE) \
  XX(27, UNSUBSCRIBE, UNSUBSCRIBE) \
  XX(28, PATCH, PATCH) \
  XX(29, PURGE, PURGE) \
  XX(30, MKCALENDAR, MKCALENDAR) \
  XX(31, LINK, LINK) \
  XX(32, UNLINK, UNLINK) \
  XX(33, SOURCE, SOURCE) \



#ifdef __cplusplus
}  /* 外部“C”*/
#endif
#endif  /* LLLLHTTP_C_HEADERS_ */

#ifndef INCLUDE_LLHTTP_API_H_
#define INCLUDE_LLHTTP_API_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

typedef llhttp__internal_t llhttp_t;
typedef struct llhttp_settings_s llhttp_settings_t;

typedef int (*llhttp_data_cb)(llhttp_t*, const char *at, size_t length);
typedef int (*llhttp_cb)(llhttp_t*);

struct llhttp_settings_s {
  /* 可能的返回值0，-1，`HPE_PAUSED`*/
  llhttp_cb      on_message_begin;

  llhttp_data_cb on_url;
  llhttp_data_cb on_status;
  llhttp_data_cb on_header_field;
  llhttp_data_cb on_header_value;

  /* 可能的返回值：0-正常进行1-假设请求/响应没有正文，然后继续分析下一条消息2-假设没有正文（如上所述）并使`llhttp_execute（）`return `HPE_PAUSED_UPGRADE`
   * -1-错误`HPE_PAUSED`
   */
  llhttp_cb      on_headers_complete;

  llhttp_data_cb on_body;

  /* 可能的返回值0，-1，`HPE_PAUSED`*/
  llhttp_cb      on_message_complete;

  /* 当调用on_cchunk_header时，当前块长度存储在parser->content_length中。可能的返回值0，-1，`HPE_PAUSED`
   */
  llhttp_cb      on_chunk_header;
  llhttp_cb      on_chunk_complete;
};

/* 使用特定类型和用户设置初始化解析器*/
void llhttp_init(llhttp_t* parser, llhttp_type_t type,
                 const llhttp_settings_t* settings);

/* 初始化设置对象*/
void llhttp_settings_init(llhttp_settings_t* settings);

/* 分析完整或部分请求/响应，同时调用用户回调。
 *
 * 如果“llhttp_data_cb”中的任何一个返回的errno不等于“HPE_OK”，则分析将中断，这样的errno将从“llhttp_execute（）”返回。如果“HPE_PAUSED”用作错误号，则可以通过调用“llhttp_resume（）”继续执行。
 *
 * 在CONNECT/Upgrade请求/响应的特殊情况下，在完全解析请求/响应后返回“HPE_PAUSED_Upgrade”。如果用户希望继续解析，则需要调用`llhttp_resume_after_upgrade（）`。
 *
 * 注意：如果此函数返回非暂停类型错误，则在每次连续调用时将继续返回相同的错误，直到调用“llhttp_init（）”。
 */
llhttp_errno_t llhttp_execute(llhttp_t* parser, const char* data, size_t len);

/* 当另一方没有更多字节要发送时（例如，关闭TCP连接的可读端），应调用此方法
 *
 * 没有“内容长度”和其他消息的请求可能需要将所有传入字节视为正文的一部分，直到连接的最后一个字节。如果请求已安全终止，则此方法将调用“on_message_complete（）”回调。否则将返回错误代码。
 */
llhttp_errno_t llhttp_finish(llhttp_t* parser);

/* 如果传入消息被解析到最后一个字节，则返回“1”，并且必须通过在EOF上调用“llhttp_finish（）”来完成
 */
int llhttp_message_needs_eof(const llhttp_t* parser);

/* 如果最后一条成功解析的消息之后可能有任何其他消息，则返回“1”。
 */
int llhttp_should_keep_alive(const llhttp_t* parser);

/* 进一步调用`llhttp_execute（）`return `HPE_PAUSED`并设置适当的错误原因。
 *
 * 重要提示：不要从用户回调中调用此项！如果需要暂停，则用户回调必须返回“HPE_PAUSED”。
 */
void llhttp_pause(llhttp_t* parser);

/* 可以在用户回调暂停后调用以恢复执行。有关详细信息，请参见上面的`llhttp_execute（）`。
 *
 * 仅当`llhttp_execute（）`返回`HPE_PAUSED`时调用此选项。
 */
void llhttp_resume(llhttp_t* parser);

/* 可以在用户回调暂停后调用以恢复执行。有关详细信息，请参见上面的`llhttp_execute（）`。
 *
 * 仅当`llhttp_execute（）`返回`HPE_PAUSED_UPGRADE时调用此选项`
 */
void llhttp_resume_after_upgrade(llhttp_t* parser);

/* 返回最新的返回错误*/
llhttp_errno_t llhttp_get_errno(const llhttp_t* parser);

/* 返回最近返回错误的口头解释。
 *
 * 注意：用户回调应在返回错误时设置错误原因。有关详细信息，请参见`llhttp_set_error_reason（）`。
 */
const char* llhttp_get_error_reason(const llhttp_t* parser);

/* 为返回的错误指定口头描述。必须在返回错误号之前立即在用户回调中调用。
 *
 * 注意：“HPE_USER”错误代码可能在用户回调中有用。
 */
void llhttp_set_error_reason(llhttp_t* parser, const char* reason);

/* 返回返回错误之前最后一个解析字节的指针。指针与`llhttp_execute（）`的`data`参数相关。
 *
 * 注意：此方法可能对计算已解析字节数有用。
 */
const char* llhttp_get_error_pos(const llhttp_t* parser);

/* 返回错误代码的文本名称*/
const char* llhttp_errno_name(llhttp_errno_t err);

/* 返回HTTP方法的文本名称*/
const char* llhttp_method_name(llhttp_method_t method);


/* 启用/禁用宽松的标头值分析（默认情况下禁用）。
 *
 * Lenent解析禁用头值令牌检查，从而将llhttp的协议支持扩展到高度不兼容的客户端/服务器。当宽松分析为“打开”时，不会为不正确的标头值引发`HPE_INVALID_HEADER_TOKEN`。
 *
 * **(USE AT YOUR OWN RISK)**
 */
void llhttp_set_lenient(llhttp_t* parser, int enabled);

#ifdef __cplusplus
}  /* 外部“C”*/
#endif
#endif  /* INCLUDE_LLHTTP_API_H_ */

#endif  /* INCLUDE_LLHTTP_H_ */

