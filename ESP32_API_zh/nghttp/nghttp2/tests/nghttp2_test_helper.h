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
#ifndef NGHTTP2_TEST_HELPER_H
#define NGHTTP2_TEST_HELPER_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include "nghttp2_frame.h"
#include "nghttp2_hd.h"
#include "nghttp2_session.h"

#define MAKE_NV(NAME, VALUE)                                                   \
  {                                                                            \
    (uint8_t *)(NAME), (uint8_t *)(VALUE), sizeof((NAME)) - 1,                 \
        sizeof((VALUE)) - 1, NGHTTP2_NV_FLAG_NONE                              \
  }
#define ARRLEN(ARR) (sizeof(ARR) / sizeof(ARR[0]))

#define assert_nv_equal(A, B, len, mem)                                        \
  do {                                                                         \
    size_t alloclen = sizeof(nghttp2_nv) * len;                                \
    const nghttp2_nv *sa = A, *sb = B;                                         \
    nghttp2_nv *a = mem->malloc(alloclen, NULL);                               \
    nghttp2_nv *b = mem->malloc(alloclen, NULL);                               \
    ssize_t i_;                                                                \
    memcpy(a, sa, alloclen);                                                   \
    memcpy(b, sb, alloclen);                                                   \
    nghttp2_nv_array_sort(a, len);                                             \
    nghttp2_nv_array_sort(b, len);                                             \
    for (i_ = 0; i_ < (ssize_t)len; ++i_) {                                    \
      CU_ASSERT(nghttp2_nv_equal(&a[i_], &b[i_]));                             \
    }                                                                          \
    mem->free(b, NULL);                                                        \
    mem->free(a, NULL);                                                        \
  } while (0);

int unpack_framebuf(nghttp2_frame *frame, nghttp2_bufs *bufs);

int unpack_frame(nghttp2_frame *frame, const uint8_t *in, size_t len);

int strmemeq(const char *a, const uint8_t *b, size_t bn);

int nvnameeq(const char *a, nghttp2_nv *nv);

int nvvalueeq(const char *a, nghttp2_nv *nv);

typedef struct {
  nghttp2_nv nva[256];
  size_t nvlen;
} nva_out;

void nva_out_init(nva_out *out);
void nva_out_reset(nva_out *out, nghttp2_mem *mem);

void add_out(nva_out *out, nghttp2_nv *nv, nghttp2_mem *mem);

ssize_t inflate_hd(nghttp2_hd_inflater *inflater, nva_out *out,
                   nghttp2_bufs *bufs, size_t offset, nghttp2_mem *mem);

int pack_headers(nghttp2_bufs *bufs, nghttp2_hd_deflater *deflater,
                 int32_t stream_id, uint8_t flags, const nghttp2_nv *nva,
                 size_t nvlen, nghttp2_mem *mem);

int pack_push_promise(nghttp2_bufs *bufs, nghttp2_hd_deflater *deflater,
                      int32_t stream_id, uint8_t flags,
                      int32_t promised_stream_id, const nghttp2_nv *nva,
                      size_t nvlen, nghttp2_mem *mem);

int frame_pack_bufs_init(nghttp2_bufs *bufs);

void bufs_large_init(nghttp2_bufs *bufs, size_t chunk_size);

nghttp2_stream *open_stream(nghttp2_session *session, int32_t stream_id);

nghttp2_stream *open_stream_with_dep(nghttp2_session *session,
                                     int32_t stream_id,
                                     nghttp2_stream *dep_stream);

nghttp2_stream *open_stream_with_dep_weight(nghttp2_session *session,
                                            int32_t stream_id, int32_t weight,
                                            nghttp2_stream *dep_stream);

nghttp2_stream *open_stream_with_dep_excl(nghttp2_session *session,
                                          int32_t stream_id,
                                          nghttp2_stream *dep_stream);

nghttp2_outbound_item *create_data_ob_item(nghttp2_mem *mem);

/* 打开流。假设此流是从|session|发送的，session->last_sent_stream_id和session->next_stream__id将相应调整。*/
nghttp2_stream *open_sent_stream(nghttp2_session *session, int32_t stream_id);

nghttp2_stream *open_sent_stream2(nghttp2_session *session, int32_t stream_id,
                                  nghttp2_stream_state initial_state);

nghttp2_stream *open_sent_stream3(nghttp2_session *session, int32_t stream_id,
                                  uint8_t flags,
                                  nghttp2_priority_spec *pri_spec_in,
                                  nghttp2_stream_state initial_state,
                                  void *stream_user_data);

nghttp2_stream *open_sent_stream_with_dep(nghttp2_session *session,
                                          int32_t stream_id,
                                          nghttp2_stream *dep_stream);

nghttp2_stream *open_sent_stream_with_dep_weight(nghttp2_session *session,
                                                 int32_t stream_id,
                                                 int32_t weight,
                                                 nghttp2_stream *dep_stream);

/* 打开流。假设此流由|session|接收，session->last_recv_stream_id将相应调整。*/
nghttp2_stream *open_recv_stream(nghttp2_session *session, int32_t stream_id);

nghttp2_stream *open_recv_stream2(nghttp2_session *session, int32_t stream_id,
                                  nghttp2_stream_state initial_state);

nghttp2_stream *open_recv_stream3(nghttp2_session *session, int32_t stream_id,
                                  uint8_t flags,
                                  nghttp2_priority_spec *pri_spec_in,
                                  nghttp2_stream_state initial_state,
                                  void *stream_user_data);

nghttp2_stream *open_recv_stream_with_dep(nghttp2_session *session,
                                          int32_t stream_id,
                                          nghttp2_stream *dep_stream);

nghttp2_stream *open_recv_stream_with_dep_weight(nghttp2_session *session,
                                                 int32_t stream_id,
                                                 int32_t weight,
                                                 nghttp2_stream *dep_stream);

#endif /* NGHTTP2_TEST_HELPER_H */

