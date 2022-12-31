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
#ifndef NGHTTP2_BUF_H
#define NGHTTP2_BUF_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>

#include "nghttp2_int.h"
#include "nghttp2_mem.h"

typedef struct {
  /* 这指向缓冲区的开始。缓冲区的有效范围为[开始，结束]。*/
  uint8_t *begin;
  /* 这将指向超出缓冲区末尾一个字节的内存。*/
  uint8_t *end;
  /* 缓冲区有效启动的位置指示器。pos<=最后一个必须保持。*/
  uint8_t *pos;
  /* 缓冲区末端以外有效一个的位置指示器。last<=end必须保持。*/
  uint8_t *last;
  /* 标记缓冲区中的任意位置[开始，结束）*/
  uint8_t *mark;
} nghttp2_buf;

#define nghttp2_buf_len(BUF) ((size_t)((BUF)->last - (BUF)->pos))
#define nghttp2_buf_avail(BUF) ((size_t)((BUF)->end - (BUF)->last))
#define nghttp2_buf_mark_avail(BUF) ((size_t)((BUF)->mark - (BUF)->last))
#define nghttp2_buf_cap(BUF) ((size_t)((BUF)->end - (BUF)->begin))

#define nghttp2_buf_pos_offset(BUF) ((size_t)((BUF)->pos - (BUF)->begin))
#define nghttp2_buf_last_offset(BUF) ((size_t)((BUF)->last - (BUF)->begin))

#define nghttp2_buf_shift_right(BUF, AMT)                                      \
  do {                                                                         \
    (BUF)->pos += AMT;                                                         \
    (BUF)->last += AMT;                                                        \
  } while (0)

#define nghttp2_buf_shift_left(BUF, AMT)                                       \
  do {                                                                         \
    (BUF)->pos -= AMT;                                                         \
    (BUF)->last -= AMT;                                                        \
  } while (0)

/*
 * 初始化|buf|。此函数中未分配内存。使用nghttp2_buf_reserve（）分配内存。
 */
void nghttp2_buf_init(nghttp2_buf *buf);

/*
 * 初始化|buf|并至少分配|initial|字节的内存。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_buf_init2(nghttp2_buf *buf, size_t initial, nghttp2_mem *mem);

/*
 * 释放|buf|中的缓冲区。
 */
void nghttp2_buf_free(nghttp2_buf *buf, nghttp2_mem *mem);

/*
 * 扩展缓冲区，使nghttp2_buf_cap（）至少返回|new_cap |。如果发生扩展，|buf|中的缓冲区指针将更改。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_buf_reserve(nghttp2_buf *buf, size_t new_cap, nghttp2_mem *mem);

/*
 * 将|buf|的pos，last，mark成员重置为buf->begin。
 */
void nghttp2_buf_reset(nghttp2_buf *buf);

/*
 * 使用提供的长度为|len|的缓冲区|begin|初始化|buf|。从语义上讲，应用程序不应为|buf|调用_reserve（）或nghttp2_free（）函数。
 */
void nghttp2_buf_wrap_init(nghttp2_buf *buf, uint8_t *begin, size_t len);

struct nghttp2_buf_chain;

typedef struct nghttp2_buf_chain nghttp2_buf_chain;

/* 链条2缓冲器*/
struct nghttp2_buf_chain {
  /* 指向后续缓冲区。如果没有这样的缓冲区，则为NULL。*/
  nghttp2_buf_chain *next;
  nghttp2_buf buf;
};

typedef struct {
  /* 指向第一个缓冲区*/
  nghttp2_buf_chain *head;
  /* 发生写入的缓冲区指针。*/
  nghttp2_buf_chain *cur;
  /* 内存分配器*/
  nghttp2_mem *mem;
  /* 每个缓冲区的缓冲容量。如果nghttp2_bufs由nghttp2_bufs_wrap_init系列函数初始化，则此字段可能为0。*/
  size_t chunk_length;
  /* nghttp2_buf_chain的最大数量*/
  size_t max_chunk;
  /* 已分配的nghttp2_buf_chain的数量*/
  size_t chunk_used;
  /* 要保持重置的nghttp2_buf_chain的数量*/
  size_t chunk_keep;
  /* 从每个缓冲区的开始位置偏移。在初始化和重置时，buf->pos和buf->last位于buf->begin+offset。*/
  size_t offset;
} nghttp2_bufs;

/*
 * 这与使用给定参数和offset=0调用nghttp2_bufs_init2相同。
 */
int nghttp2_bufs_init(nghttp2_bufs *bufs, size_t chunk_length, size_t max_chunk,
                      nghttp2_mem *mem);

/*
 * 这与使用给定参数和chunk_keep=max_chunk调用nghttp2_bufs_init3相同。
 */
int nghttp2_bufs_init2(nghttp2_bufs *bufs, size_t chunk_length,
                       size_t max_chunk, size_t offset, nghttp2_mem *mem);

/*
 * 初始化|bufs|。每个缓冲区大小在|chunk_length|中给出。缓冲区的最大数量在|max_chunk|中给出。重置时，保留第一个|chunk_keep|缓冲区，删除剩余的缓冲区。每个缓冲区将有bufs->pos和bufs->last在创建和重置时向左偏移|offset|字节。
 *
 * 此函数分配第一个缓冲区。bufs->head和bufs->cur将指向调用后的第一个缓冲区。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_INVALID_ARGUMENT chunk_keep为0；或max_chunk<chunk_keep；或偏移太长。
 */
int nghttp2_bufs_init3(nghttp2_bufs *bufs, size_t chunk_length,
                       size_t max_chunk, size_t chunk_keep, size_t offset,
                       nghttp2_mem *mem);

/*
 * 将所有相关资源释放到|bufs|。
 */
void nghttp2_bufs_free(nghttp2_bufs *bufs);

/*
 * 使用提供的长度为|len|的缓冲区|begin|初始化|bufs|。第一个缓冲区bufs->head使用buffer|begin|。缓冲区大小是固定的，没有分配额外的块缓冲区。换句话说，max_chunk=chunk_keep=1。要释放为|bufs|分配的资源，请使用nghttp2_bufs_wrap_free（）。
 *
 * 不要使用执行分配的函数，例如nghttp2_bufs_realloc（）。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_bufs_wrap_init(nghttp2_bufs *bufs, uint8_t *begin, size_t len,
                           nghttp2_mem *mem);

/*
 * 使用提供的|veclen| buf vector|vec|大小初始化|bufs|。缓冲区的数量是固定的，没有分配额外的块缓冲区。换句话说，max_chunk=chunk_keep=|In_len|。要释放为|bufs|分配的资源，请使用nghttp2_bufs_wrap_free（）。
 *
 * 不要使用执行分配的函数，例如nghttp2_bufs_realloc（）。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_bufs_wrap_init2(nghttp2_bufs *bufs, const nghttp2_vec *vec,
                            size_t veclen, nghttp2_mem *mem);

/*
 * 将所有相关资源释放给|bufs|。此函数不会释放nghttp2_bufs_wrap_init（）中提供的缓冲区。
 */
void nghttp2_bufs_wrap_free(nghttp2_bufs *bufs);

/*
 * 使用|chunk_length|重新分配内部缓冲区。max_chunk、chunk_keep和offset不变。成功分配新缓冲区后，将释放以前的缓冲区，而不将任何内容复制到新缓冲区中。chunk_used重置为1。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_INVALID_ARGUMENT chunk_length<偏移量
 */
int nghttp2_bufs_realloc(nghttp2_bufs *bufs, size_t chunk_length);

/*
 * 将长度为|len|的|data|追加到|bufs|。写入从bufs->cur->buf.last开始。将分配一个新的缓冲区来存储所有数据。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_BUFFER_ERROR缓冲区空间不足。
 */
int nghttp2_bufs_add(nghttp2_bufs *bufs, const void *data, size_t len);

/*
 * 将单个字节|b|追加到|bufs|。写入从bufs->cur->buf.last开始。将分配一个新的缓冲区来存储所有数据。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_BUFFER_ERROR缓冲区空间不足。
 */
int nghttp2_bufs_addb(nghttp2_bufs *bufs, uint8_t b);

/*
 * 行为类似于nghttp2_bufs_add（），但这不会更新buf->最后一个指针。
 */
int nghttp2_bufs_addb_hold(nghttp2_bufs *bufs, uint8_t b);

#define nghttp2_bufs_fast_addb(BUFS, B)                                        \
  do {                                                                         \
    *(BUFS)->cur->buf.last++ = B;                                              \
  } while (0)

#define nghttp2_bufs_fast_addb_hold(BUFS, B)                                   \
  do {                                                                         \
    *(BUFS)->cur->buf.last = B;                                                \
  } while (0)

/*
 * 对bufs->cur->buf.last处的|b|执行位或。如有必要，将分配新的缓冲区。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_BUFFER_ERROR缓冲区空间不足。
 */
int nghttp2_bufs_orb(nghttp2_bufs *bufs, uint8_t b);

/*
 * 行为类似于nghttp2_bufs_orb（），但不更新buf->最后一个指针。
 */
int nghttp2_bufs_orb_hold(nghttp2_bufs *bufs, uint8_t b);

#define nghttp2_bufs_fast_orb(BUFS, B)                                         \
  do {                                                                         \
    uint8_t **p = &(BUFS)->cur->buf.last;                                      \
    **p = (uint8_t)(**p | (B));                                                \
    ++(*p);                                                                    \
  } while (0)

#define nghttp2_bufs_fast_orb_hold(BUFS, B)                                    \
  do {                                                                         \
    uint8_t *p = (BUFS)->cur->buf.last;                                        \
    *p = (uint8_t)(*p | (B));                                                  \
  } while (0)

/*
 * 将|bufs|中存储的所有数据复制到连续缓冲区。此函数分配连续内存以将所有数据存储在|bufs|中，并将其分配给|out|。
 *
 * |bufs|的内容保持不变。
 *
 * 此函数返回复制数据的长度，如果成功，则将指向复制数据的指针分配给|out|，或以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
ssize_t nghttp2_bufs_remove(nghttp2_bufs *bufs, uint8_t **out);

/*
 * 将|bufs|中存储的所有数据复制到|out|。此函数假定|out|指向的缓冲区空间至少有nghttp2_bufs（bufs）字节。
 *
 * |bufs|的内容保持不变。
 *
 * 此函数返回复制数据的长度。
 */
size_t nghttp2_bufs_remove_copy(nghttp2_bufs *bufs, uint8_t *out);

/*
 * 重置|bufs|并使缓冲区为空。
 */
void nghttp2_bufs_reset(nghttp2_bufs *bufs);

/*
 * 将bufs->cur移动到bufs->cur->next。如果生成的bufs->cur为NULL，则此函数将分配新的缓冲区，并且bufs->cur指向它。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足NGHTTP2_ERROR_BUFFER_ERROR缓冲区空间不足。
 */
int nghttp2_bufs_advance(nghttp2_bufs *bufs);

/* 将bufs->cur设置为bufs->head*/
#define nghttp2_bufs_rewind(BUFS)                                              \
  do {                                                                         \
    (BUFS)->cur = (BUFS)->head;                                                \
  } while (0)

/*
 * 使用next成员将bufs->cur从当前位置移动到nghttp2_buf_len（buf）>0的最后一个buf，而不会看到满足nghttp2_buf_len的buf（buf）==0。如果nghttp 2_buf_len（&bufs->cur->buf）==0或bufs->cur->next为NULL，则bufs->cur将保持不变。
 */
void nghttp2_bufs_seek_last_present(nghttp2_bufs *bufs);

/*
 * 如果bufs->cur->next不为空，则返回非零。
 */
int nghttp2_bufs_next_present(nghttp2_bufs *bufs);

#define nghttp2_bufs_cur_avail(BUFS) nghttp2_buf_avail(&(BUFS)->cur->buf)

/*
 * 返回|bufs|的总缓冲区长度。
 */
size_t nghttp2_bufs_len(nghttp2_bufs *bufs);

#endif /* NGHTTP2_BUF_H */

