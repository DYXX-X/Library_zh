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
}  /* å¤é¨âCâ*/
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
}  /* å¤é¨âCâ*/
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
  /* å¯è½çè¿åå¼0ï¼-1ï¼`HPE_PAUSED`*/
  llhttp_cb      on_message_begin;

  llhttp_data_cb on_url;
  llhttp_data_cb on_status;
  llhttp_data_cb on_header_field;
  llhttp_data_cb on_header_value;

  /* å¯è½çè¿åå¼ï¼0-æ­£å¸¸è¿è¡1-åè®¾è¯·æ±/ååºæ²¡ææ­£æï¼ç¶åç»§ç»­åæä¸ä¸æ¡æ¶æ¯2-åè®¾æ²¡ææ­£æï¼å¦ä¸æè¿°ï¼å¹¶ä½¿`llhttp_executeï¼ï¼`return `HPE_PAUSED_UPGRADE`
   * -1-éè¯¯`HPE_PAUSED`
   */
  llhttp_cb      on_headers_complete;

  llhttp_data_cb on_body;

  /* å¯è½çè¿åå¼0ï¼-1ï¼`HPE_PAUSED`*/
  llhttp_cb      on_message_complete;

  /* å½è°ç¨on_cchunk_headeræ¶ï¼å½ååé¿åº¦å­å¨å¨parser->content_lengthä¸­ãå¯è½çè¿åå¼0ï¼-1ï¼`HPE_PAUSED`
   */
  llhttp_cb      on_chunk_header;
  llhttp_cb      on_chunk_complete;
};

/* ä½¿ç¨ç¹å®ç±»ååç¨æ·è®¾ç½®åå§åè§£æå¨*/
void llhttp_init(llhttp_t* parser, llhttp_type_t type,
                 const llhttp_settings_t* settings);

/* åå§åè®¾ç½®å¯¹è±¡*/
void llhttp_settings_init(llhttp_settings_t* settings);

/* åæå®æ´æé¨åè¯·æ±/ååºï¼åæ¶è°ç¨ç¨æ·åè°ã
 *
 * å¦æâllhttp_data_cbâä¸­çä»»ä½ä¸ä¸ªè¿åçerrnoä¸ç­äºâHPE_OKâï¼ååæå°ä¸­æ­ï¼è¿æ ·çerrnoå°ä»âllhttp_executeï¼ï¼âè¿åãå¦æâHPE_PAUSEDâç¨ä½éè¯¯å·ï¼åå¯ä»¥éè¿è°ç¨âllhttp_resumeï¼ï¼âç»§ç»­æ§è¡ã
 *
 * å¨CONNECT/Upgradeè¯·æ±/ååºçç¹æ®æåµä¸ï¼å¨å®å¨è§£æè¯·æ±/ååºåè¿åâHPE_PAUSED_Upgradeâãå¦æç¨æ·å¸æç»§ç»­è§£æï¼åéè¦è°ç¨`llhttp_resume_after_upgradeï¼ï¼`ã
 *
 * æ³¨æï¼å¦ææ­¤å½æ°è¿åéæåç±»åéè¯¯ï¼åå¨æ¯æ¬¡è¿ç»­è°ç¨æ¶å°ç»§ç»­è¿åç¸åçéè¯¯ï¼ç´å°è°ç¨âllhttp_initï¼ï¼âã
 */
llhttp_errno_t llhttp_execute(llhttp_t* parser, const char* data, size_t len);

/* å½å¦ä¸æ¹æ²¡ææ´å¤å­èè¦åéæ¶ï¼ä¾å¦ï¼å³é­TCPè¿æ¥çå¯è¯»ç«¯ï¼ï¼åºè°ç¨æ­¤æ¹æ³
 *
 * æ²¡æâåå®¹é¿åº¦âåå¶ä»æ¶æ¯çè¯·æ±å¯è½éè¦å°ææä¼ å¥å­èè§ä¸ºæ­£æçä¸é¨åï¼ç´å°è¿æ¥çæåä¸ä¸ªå­èãå¦æè¯·æ±å·²å®å¨ç»æ­¢ï¼åæ­¤æ¹æ³å°è°ç¨âon_message_completeï¼ï¼âåè°ãå¦åå°è¿åéè¯¯ä»£ç ã
 */
llhttp_errno_t llhttp_finish(llhttp_t* parser);

/* å¦æä¼ å¥æ¶æ¯è¢«è§£æå°æåä¸ä¸ªå­èï¼åè¿åâ1âï¼å¹¶ä¸å¿é¡»éè¿å¨EOFä¸è°ç¨âllhttp_finishï¼ï¼âæ¥å®æ
 */
int llhttp_message_needs_eof(const llhttp_t* parser);

/* å¦ææåä¸æ¡æåè§£æçæ¶æ¯ä¹åå¯è½æä»»ä½å¶ä»æ¶æ¯ï¼åè¿åâ1âã
 */
int llhttp_should_keep_alive(const llhttp_t* parser);

/* è¿ä¸æ­¥è°ç¨`llhttp_executeï¼ï¼`return `HPE_PAUSED`å¹¶è®¾ç½®éå½çéè¯¯åå ã
 *
 * éè¦æç¤ºï¼ä¸è¦ä»ç¨æ·åè°ä¸­è°ç¨æ­¤é¡¹ï¼å¦æéè¦æåï¼åç¨æ·åè°å¿é¡»è¿åâHPE_PAUSEDâã
 */
void llhttp_pause(llhttp_t* parser);

/* å¯ä»¥å¨ç¨æ·åè°æååè°ç¨ä»¥æ¢å¤æ§è¡ãæå³è¯¦ç»ä¿¡æ¯ï¼è¯·åè§ä¸é¢ç`llhttp_executeï¼ï¼`ã
 *
 * ä»å½`llhttp_executeï¼ï¼`è¿å`HPE_PAUSED`æ¶è°ç¨æ­¤éé¡¹ã
 */
void llhttp_resume(llhttp_t* parser);

/* å¯ä»¥å¨ç¨æ·åè°æååè°ç¨ä»¥æ¢å¤æ§è¡ãæå³è¯¦ç»ä¿¡æ¯ï¼è¯·åè§ä¸é¢ç`llhttp_executeï¼ï¼`ã
 *
 * ä»å½`llhttp_executeï¼ï¼`è¿å`HPE_PAUSED_UPGRADEæ¶è°ç¨æ­¤éé¡¹`
 */
void llhttp_resume_after_upgrade(llhttp_t* parser);

/* è¿åææ°çè¿åéè¯¯*/
llhttp_errno_t llhttp_get_errno(const llhttp_t* parser);

/* è¿åæè¿è¿åéè¯¯çå£å¤´è§£éã
 *
 * æ³¨æï¼ç¨æ·åè°åºå¨è¿åéè¯¯æ¶è®¾ç½®éè¯¯åå ãæå³è¯¦ç»ä¿¡æ¯ï¼è¯·åè§`llhttp_set_error_reasonï¼ï¼`ã
 */
const char* llhttp_get_error_reason(const llhttp_t* parser);

/* ä¸ºè¿åçéè¯¯æå®å£å¤´æè¿°ãå¿é¡»å¨è¿åéè¯¯å·ä¹åç«å³å¨ç¨æ·åè°ä¸­è°ç¨ã
 *
 * æ³¨æï¼âHPE_USERâéè¯¯ä»£ç å¯è½å¨ç¨æ·åè°ä¸­æç¨ã
 */
void llhttp_set_error_reason(llhttp_t* parser, const char* reason);

/* è¿åè¿åéè¯¯ä¹åæåä¸ä¸ªè§£æå­èçæéãæéä¸`llhttp_executeï¼ï¼`ç`data`åæ°ç¸å³ã
 *
 * æ³¨æï¼æ­¤æ¹æ³å¯è½å¯¹è®¡ç®å·²è§£æå­èæ°æç¨ã
 */
const char* llhttp_get_error_pos(const llhttp_t* parser);

/* è¿åéè¯¯ä»£ç çææ¬åç§°*/
const char* llhttp_errno_name(llhttp_errno_t err);

/* è¿åHTTPæ¹æ³çææ¬åç§°*/
const char* llhttp_method_name(llhttp_method_t method);


/* å¯ç¨/ç¦ç¨å®½æ¾çæ å¤´å¼åæï¼é»è®¤æåµä¸ç¦ç¨ï¼ã
 *
 * Lenentè§£æç¦ç¨å¤´å¼ä»¤çæ£æ¥ï¼ä»èå°llhttpçåè®®æ¯ææ©å±å°é«åº¦ä¸å¼å®¹çå®¢æ·ç«¯/æå¡å¨ãå½å®½æ¾åæä¸ºâæå¼âæ¶ï¼ä¸ä¼ä¸ºä¸æ­£ç¡®çæ å¤´å¼å¼å`HPE_INVALID_HEADER_TOKEN`ã
 *
 * **(USE AT YOUR OWN RISK)**
 */
void llhttp_set_lenient(llhttp_t* parser, int enabled);

#ifdef __cplusplus
}  /* å¤é¨âCâ*/
#endif
#endif  /* INCLUDE_LLHTTP_API_H_ */

#endif  /* INCLUDE_LLHTTP_H_ */

