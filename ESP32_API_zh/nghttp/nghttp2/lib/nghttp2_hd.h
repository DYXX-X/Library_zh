/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2013 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef NGHTTP2_HD_H
#define NGHTTP2_HD_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>

#include "nghttp2_hd_huffman.h"
#include "nghttp2_buf.h"
#include "nghttp2_mem.h"
#include "nghttp2_rcbuf.h"

#define NGHTTP2_HD_DEFAULT_MAX_BUFFER_SIZE NGHTTP2_DEFAULT_HEADER_TABLE_SIZE
#define NGHTTP2_HD_ENTRY_OVERHEAD 32

/* 一个名称/值对的最大长度。这是名称和值的长度之和。这不是由规范指定的。我们只是选择了任意大小*/
#define NGHTTP2_HD_MAX_NV 65536

/* 编码器的最大表缓冲区大小的默认大小。即使远程解码器为其解码通知更大的缓冲区大小，编码器也只使用该值之前的内存。*/
#define NGHTTP2_HD_DEFAULT_MAX_DEFLATE_BUFFER_SIZE (1 << 12)

/* 导出用于单元测试*/
#define NGHTTP2_STATIC_TABLE_LENGTH 61

/* 由genlibtokenlookup生成。皮，皮*/
typedef enum {
  NGHTTP2_TOKEN__AUTHORITY = 0,
  NGHTTP2_TOKEN__METHOD = 1,
  NGHTTP2_TOKEN__PATH = 3,
  NGHTTP2_TOKEN__SCHEME = 5,
  NGHTTP2_TOKEN__STATUS = 7,
  NGHTTP2_TOKEN_ACCEPT_CHARSET = 14,
  NGHTTP2_TOKEN_ACCEPT_ENCODING = 15,
  NGHTTP2_TOKEN_ACCEPT_LANGUAGE = 16,
  NGHTTP2_TOKEN_ACCEPT_RANGES = 17,
  NGHTTP2_TOKEN_ACCEPT = 18,
  NGHTTP2_TOKEN_ACCESS_CONTROL_ALLOW_ORIGIN = 19,
  NGHTTP2_TOKEN_AGE = 20,
  NGHTTP2_TOKEN_ALLOW = 21,
  NGHTTP2_TOKEN_AUTHORIZATION = 22,
  NGHTTP2_TOKEN_CACHE_CONTROL = 23,
  NGHTTP2_TOKEN_CONTENT_DISPOSITION = 24,
  NGHTTP2_TOKEN_CONTENT_ENCODING = 25,
  NGHTTP2_TOKEN_CONTENT_LANGUAGE = 26,
  NGHTTP2_TOKEN_CONTENT_LENGTH = 27,
  NGHTTP2_TOKEN_CONTENT_LOCATION = 28,
  NGHTTP2_TOKEN_CONTENT_RANGE = 29,
  NGHTTP2_TOKEN_CONTENT_TYPE = 30,
  NGHTTP2_TOKEN_COOKIE = 31,
  NGHTTP2_TOKEN_DATE = 32,
  NGHTTP2_TOKEN_ETAG = 33,
  NGHTTP2_TOKEN_EXPECT = 34,
  NGHTTP2_TOKEN_EXPIRES = 35,
  NGHTTP2_TOKEN_FROM = 36,
  NGHTTP2_TOKEN_HOST = 37,
  NGHTTP2_TOKEN_IF_MATCH = 38,
  NGHTTP2_TOKEN_IF_MODIFIED_SINCE = 39,
  NGHTTP2_TOKEN_IF_NONE_MATCH = 40,
  NGHTTP2_TOKEN_IF_RANGE = 41,
  NGHTTP2_TOKEN_IF_UNMODIFIED_SINCE = 42,
  NGHTTP2_TOKEN_LAST_MODIFIED = 43,
  NGHTTP2_TOKEN_LINK = 44,
  NGHTTP2_TOKEN_LOCATION = 45,
  NGHTTP2_TOKEN_MAX_FORWARDS = 46,
  NGHTTP2_TOKEN_PROXY_AUTHENTICATE = 47,
  NGHTTP2_TOKEN_PROXY_AUTHORIZATION = 48,
  NGHTTP2_TOKEN_RANGE = 49,
  NGHTTP2_TOKEN_REFERER = 50,
  NGHTTP2_TOKEN_REFRESH = 51,
  NGHTTP2_TOKEN_RETRY_AFTER = 52,
  NGHTTP2_TOKEN_SERVER = 53,
  NGHTTP2_TOKEN_SET_COOKIE = 54,
  NGHTTP2_TOKEN_STRICT_TRANSPORT_SECURITY = 55,
  NGHTTP2_TOKEN_TRANSFER_ENCODING = 56,
  NGHTTP2_TOKEN_USER_AGENT = 57,
  NGHTTP2_TOKEN_VARY = 58,
  NGHTTP2_TOKEN_VIA = 59,
  NGHTTP2_TOKEN_WWW_AUTHENTICATE = 60,
  NGHTTP2_TOKEN_TE,
  NGHTTP2_TOKEN_CONNECTION,
  NGHTTP2_TOKEN_KEEP_ALIVE,
  NGHTTP2_TOKEN_PROXY_CONNECTION,
  NGHTTP2_TOKEN_UPGRADE,
  NGHTTP2_TOKEN__PROTOCOL,
} nghttp2_token;

struct nghttp2_hd_entry;
typedef struct nghttp2_hd_entry nghttp2_hd_entry;

typedef struct {
  /* 包含标头字段名的缓冲区。保证NULL终止。*/
  nghttp2_rcbuf *name;
  /* 包含标头字段值的缓冲区。保证NULL终止。*/
  nghttp2_rcbuf *value;
  /* 名称的nghttp2_token值。如果没有标头字段名的标记，则可能为-1。*/
  int32_t token;
  /* 一个或多个nghttp2_nv_flag的位或。*/
  uint8_t flags;
} nghttp2_hd_nv;

struct nghttp2_hd_entry {
  /* 标头字段名称/值对*/
  nghttp2_hd_nv nv;
  /* 这仅适用于nghttp2_hd_{deflate，inflate}_get_table_entry API，以保持向后兼容性。*/
  nghttp2_nv cnv;
  /* 哈希表中共享同一存储桶的下一个条目。*/
  nghttp2_hd_entry *next;
  /* 序列号。每当我们将nghttp2_hd_entry存储到动态头表时，我们都会将其递增一。*/
  uint32_t seq;
  /* 标头名称（nv.name）的哈希值。*/
  uint32_t hash;
};

/* 用于静态头表的条目。*/
typedef struct {
  nghttp2_rcbuf name;
  nghttp2_rcbuf value;
  nghttp2_nv cnv;
  int32_t token;
  uint32_t hash;
} nghttp2_hd_static_entry;

typedef struct {
  nghttp2_hd_entry **buffer;
  size_t mask;
  size_t first;
  size_t len;
} nghttp2_hd_ringbuf;

typedef enum {
  NGHTTP2_HD_OPCODE_NONE,
  NGHTTP2_HD_OPCODE_INDEXED,
  NGHTTP2_HD_OPCODE_NEWNAME,
  NGHTTP2_HD_OPCODE_INDNAME
} nghttp2_hd_opcode;

typedef enum {
  NGHTTP2_HD_STATE_EXPECT_TABLE_SIZE,
  NGHTTP2_HD_STATE_INFLATE_START,
  NGHTTP2_HD_STATE_OPCODE,
  NGHTTP2_HD_STATE_READ_TABLE_SIZE,
  NGHTTP2_HD_STATE_READ_INDEX,
  NGHTTP2_HD_STATE_NEWNAME_CHECK_NAMELEN,
  NGHTTP2_HD_STATE_NEWNAME_READ_NAMELEN,
  NGHTTP2_HD_STATE_NEWNAME_READ_NAMEHUFF,
  NGHTTP2_HD_STATE_NEWNAME_READ_NAME,
  NGHTTP2_HD_STATE_CHECK_VALUELEN,
  NGHTTP2_HD_STATE_READ_VALUELEN,
  NGHTTP2_HD_STATE_READ_VALUEHUFF,
  NGHTTP2_HD_STATE_READ_VALUE
} nghttp2_hd_inflate_state;

typedef enum {
  NGHTTP2_HD_WITH_INDEXING,
  NGHTTP2_HD_WITHOUT_INDEXING,
  NGHTTP2_HD_NEVER_INDEXING
} nghttp2_hd_indexing_mode;

typedef struct {
  /* 动态标题表*/
  nghttp2_hd_ringbuf hd_table;
  /* 内存分配器*/
  nghttp2_mem *mem;
  /* 规范中描述的hd_table的抽象缓冲区大小。这是每个条目的hd_table+NGHTTP2_hd_ENTRY_OVERHEAD字节开销中名称/值的长度总和。*/
  size_t hd_table_bufsize;
  /* 有效标头表大小。*/
  size_t hd_table_bufsize_max;
  /* nghttp2_hd_entry的下一个序列号*/
  uint32_t next_seq;
  /* 如果发生充气/放气错误，此值将设置为1，进一步调用充气/放气将失败，并显示NGHTTP2_ERR_HEADER_COMP。*/
  uint8_t bad;
} nghttp2_hd_context;

#define HD_MAP_SIZE 128

typedef struct {
  nghttp2_hd_entry *table[HD_MAP_SIZE];
} nghttp2_hd_map;

struct nghttp2_hd_deflater {
  nghttp2_hd_context ctx;
  nghttp2_hd_map map;
  /* 放气器接受的标题表大小上限。*/
  size_t deflate_hd_table_bufsize_max;
  /* 下一次上下文更新中通知的最小标头表大小*/
  size_t min_hd_table_bufsize_max;
  /* 如果非零，则在下一个deflate过程中使用编码上下文更新发送头表大小*/
  uint8_t notify_table_size_change;
};

struct nghttp2_hd_inflater {
  nghttp2_hd_context ctx;
  /* 存储霍夫曼解码的当前状态*/
  nghttp2_hd_huff_decode_context huff_decode_ctx;
  /* 标头缓冲区*/
  nghttp2_buf namebuf, valuebuf;
  nghttp2_rcbuf *namercbuf, *valuercbuf;
  /* 指向当前标头发射中使用的名称/值对的指针。*/
  nghttp2_rcbuf *nv_name_keep, *nv_value_keep;
  /* 要读取的字节数*/
  size_t left;
  /* 索引代表或索引名称中的索引*/
  size_t index;
  /* 充气机支持的最大收割台尺寸。这与SETTINGS_HEADER_TABLE_SIZE中传输的值相同*/
  size_t settings_hd_table_bufsize_max;
  /* nghttp2_hd_inflate_change_table_size设置的最小头表大小*/
  size_t min_hd_table_bufsize_max;
  /* 要解码整数的下一个移位数*/
  size_t shift;
  nghttp2_hd_opcode opcode;
  nghttp2_hd_inflate_state state;
  /* 如果字符串是霍夫曼编码的，则为非零*/
  uint8_t huffman_encoded;
  /* 如果deflater要求索引当前条目，则为非零*/
  uint8_t index_required;
  /* 如果deflater要求当前条目不能被索引，则为非零*/
  uint8_t no_index;
};

/*
 * 初始化|ent|成员。nv->name和nv->value的引用计数分别增加一个。
 */
void nghttp2_hd_entry_init(nghttp2_hd_entry *ent, nghttp2_hd_nv *nv);

/*
 * 此函数减少nv->name和nv->value的引用计数。
 */
void nghttp2_hd_entry_free(nghttp2_hd_entry *ent);

/*
 * 为收缩名称/值对初始化|deflater|。
 *
 * 即使稍后在NGHTTP2_HD_change_table_SIZE（）中指定了更大的值，编码器也只使用最多NGHTTP2_HD_DEFAULT_MAX_DEFLATE_BUFFER_SIZE字节作为头表。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_hd_deflate_init(nghttp2_hd_deflater *deflater, nghttp2_mem *mem);

/*
 * 为收缩名称/值对初始化|deflater|。
 *
 * 即使稍后在nghttp2_hd_change_table_size（）中指定了更大的值，编码器也只使用|max_deflate_dynamic_table_size |字节作为头表。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_hd_deflate_init2(nghttp2_hd_deflater *deflater,
                             size_t max_deflate_dynamic_table_size,
                             nghttp2_mem *mem);

/*
 * 取消分配给|deflater|的所有资源。
 */
void nghttp2_hd_deflate_free(nghttp2_hd_deflater *deflater);

/*
 * 将具有|nvlen|名称/值对的|nva|压缩为|bufs|。
 *
 * 此函数根据需要展开|bufs|以存储结果。如果缓冲区已满且进程仍需要更多空间，则此函数将失败并返回NGHTTP2_ERR_HEADER_COMP。
 *
 * 此函数返回后，可以安全地删除|nva|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_HEADER_COMP放气过程失败。NGHTTP2_ERR_BUFFER_ERROR缓冲区空间不足。
 */
int nghttp2_hd_deflate_hd_bufs(nghttp2_hd_deflater *deflater,
                               nghttp2_bufs *bufs, const nghttp2_nv *nva,
                               size_t nvlen);

/*
 * 为膨胀名称/值对初始化|inflater |。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * ：enum:`NGHTTP2_ERR_NOMEM`内存不足。
 */
int nghttp2_hd_inflate_init(nghttp2_hd_inflater *inflater, nghttp2_mem *mem);

/*
 * 取消分配给|inflater|的所有资源。
 */
void nghttp2_hd_inflate_free(nghttp2_hd_inflater *inflater);

/*
 * 与nghttp2_hd_inflate_hd（）类似，但这采用nghttp2_hd_nv而不是nghttp2_nv作为输出参数|nv_out|。除此之外，返回值和语义与nghttp2_hd_inflate_hd（）相同。
 */
ssize_t nghttp2_hd_inflate_hd_nv(nghttp2_hd_inflater *inflater,
                                 nghttp2_hd_nv *nv_out, int *inflate_flags,
                                 const uint8_t *in, size_t inlen, int in_final);

/* 用于单元测试*/
int nghttp2_hd_emit_indname_block(nghttp2_bufs *bufs, size_t index,
                                  nghttp2_nv *nv, int indexing_mode);

/* 用于单元测试*/
int nghttp2_hd_emit_newname_block(nghttp2_bufs *bufs, nghttp2_nv *nv,
                                  int indexing_mode);

/* 用于单元测试*/
int nghttp2_hd_emit_table_size(nghttp2_bufs *bufs, size_t table_size);

/* 用于单元测试*/
nghttp2_hd_nv nghttp2_hd_table_get(nghttp2_hd_context *context, size_t index);

/* 用于单元测试*/
ssize_t nghttp2_hd_decode_length(uint32_t *res, size_t *shift_ptr, int *fin,
                                 uint32_t initial, size_t shift, uint8_t *in,
                                 uint8_t *last, size_t prefix);

/* 霍夫曼编码/解码功能*/

/*
 * 统计编码|src|所需的字节，长度|len|。
 *
 * 此函数返回编码给定数据所需的字节数，包括终端符号代码前缀的填充。此函数始终成功。
 */
size_t nghttp2_hd_huff_encode_count(const uint8_t *src, size_t len);

/*
 * 将长度为|srclen|的给定数据|src|编码为|bufs|。如果需要，此函数将扩展|bufs|中的额外缓冲区。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_BUFFER_ERROR缓冲区空间不足。
 */
int nghttp2_hd_huff_encode(nghttp2_bufs *bufs, const uint8_t *src,
                           size_t srclen);

void nghttp2_hd_huff_decode_context_init(nghttp2_hd_huff_decode_context *ctx);

/*
 * 解码长度为|srclen|的给定数据|src|。|ctx|必须由nghttp2_hd_huff_edecode_context_init（）初始化。结果将写入|buf|。此函数假定|buf|有足够的空间存储解码的字节字符串。
 *
 * 如果给定的输入是最后一个块，则调用者必须将|fin|设置为非零。
 *
 * 此函数返回从|中读取的字节数。
 *
 * 如果此函数失败，则返回以下负返回代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_HEADER_COMP解码过程失败。
 */
ssize_t nghttp2_hd_huff_decode(nghttp2_hd_huff_decode_context *ctx,
                               nghttp2_buf *buf, const uint8_t *src,
                               size_t srclen, int fin);

/*
 * 如果|ctx|指示huffman解码上下文处于失败状态，nghttp2_hd_huff_edecode_failure_state返回非零。
 */
int nghttp2_hd_huff_decode_failure_state(nghttp2_hd_huff_decode_context *ctx);

#endif /* NGHTTP2_HD_H */

