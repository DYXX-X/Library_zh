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
#ifndef NGHTTP2_FRAME_H
#define NGHTTP2_FRAME_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>
#include "nghttp2_hd.h"
#include "nghttp2_buf.h"

#define NGHTTP2_STREAM_ID_MASK ((1u << 31) - 1)
#define NGHTTP2_PRI_GROUP_ID_MASK ((1u << 31) - 1)
#define NGHTTP2_PRIORITY_MASK ((1u << 31) - 1)
#define NGHTTP2_WINDOW_SIZE_INCREMENT_MASK ((1u << 31) - 1)
#define NGHTTP2_SETTINGS_ID_MASK ((1 << 24) - 1)

/* 帧标头的字节数。*/
#define NGHTTP2_FRAME_HDLEN 9

#define NGHTTP2_MAX_FRAME_SIZE_MAX ((1 << 24) - 1)
#define NGHTTP2_MAX_FRAME_SIZE_MIN (1 << 14)

#define NGHTTP2_MAX_PAYLOADLEN 16384
/* 传输的一帧缓冲区长度。我们可以使用其中的几个来支持CONTINUATION。为了说明“填充长度”字段，我们分配了额外的1个字节，这节省了额外的内存复制。*/
#define NGHTTP2_FRAMEBUF_CHUNKLEN                                              \
  (NGHTTP2_FRAME_HDLEN + 1 + NGHTTP2_MAX_PAYLOADLEN)

/* DATA帧有效载荷的默认长度。*/
#define NGHTTP2_DATA_PAYLOADLEN NGHTTP2_MAX_FRAME_SIZE_MIN

/* 要发送的最大标头块大小，使用nghttp2_hd_deflate_bound（）计算。这是默认值，可以被nghttp2_option_set_max_send_header_block_size（）覆盖。*/
#define NGHTTP2_MAX_HEADERSLEN 65536

/* 每个SETTINGS条目的字节数*/
#define NGHTTP2_FRAME_SETTINGS_ENTRY_LENGTH 6

/* HEADERS/priority帧中优先级相关字段的长度*/
#define NGHTTP2_PRIORITY_SPECLEN 5

/* 填充的最大长度（字节）。*/
#define NGHTTP2_MAX_PADLEN 256

/* 扩展架有效载荷的联合*/
typedef union {
  nghttp2_ext_altsvc altsvc;
  nghttp2_ext_origin origin;
} nghttp2_ext_frame_payload;

void nghttp2_frame_pack_frame_hd(uint8_t *buf, const nghttp2_frame_hd *hd);

void nghttp2_frame_unpack_frame_hd(nghttp2_frame_hd *hd, const uint8_t *buf);

/**
 * 使用给定参数初始化帧头|hd|。保留位设置为0。
 */
void nghttp2_frame_hd_init(nghttp2_frame_hd *hd, size_t length, uint8_t type,
                           uint8_t flags, int32_t stream_id);

/**
 * 根据|标志|返回优先级字段的数量。如果|flags |既没有设置NGHTTP2_FLAG_PRIORITY_GROUP，也没有设置NGHTTP2_FLAG_PRIORITY_DEPENDENCY，则返回0。
 */
size_t nghttp2_frame_priority_len(uint8_t flags);

/**
 * 将|pri_spec|打包到|buf|中。此函数假定|buf|有足够的空间进行序列化。
 */
void nghttp2_frame_pack_priority_spec(uint8_t *buf,
                                      const nghttp2_priority_spec *pri_spec);

/**
 * 将优先级规范从长度为|payloadlen|的payload | payload |解包为|pri_spec|。|flags |用于确定|payload |中的优先级规范。此函数假定|payload |包含整个优先级规范。
 */
void nghttp2_frame_unpack_priority_spec(nghttp2_priority_spec *pri_spec,
                                        const uint8_t *payload);

/*
 * 返回压缩头块开始处HEADERS帧有效负载的偏移量。帧有效负载不包括帧标头。
 */
size_t nghttp2_frame_headers_payload_nv_offset(nghttp2_headers *frame);

/*
 * 以wire格式打包HEADERS帧|frame |，并将其存储在|bufs|中。此函数根据需要展开|bufs|以存储帧。
 *
 * 调用方必须确保在调用此函数之前调用了nghttp2_bufs_reset（bufs）。
 *
 * 框架->高清。长度在包装过程中确定后分配。连续帧也在该函数中序列化。此函数不处理填充。
 *
 * 如果成功，此函数将返回0，或返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_HEADER_COMP放气操作失败。NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_frame_pack_headers(nghttp2_bufs *bufs, nghttp2_headers *frame,
                               nghttp2_hd_deflater *deflater);

/*
 * 将HEADERS帧字节序列解压缩为|frame |。此函数仅取消名称/值标题块之前和可能的填充长度字段之后的字节。
 *
 * 此函数始终成功并返回0。
 */
int nghttp2_frame_unpack_headers_payload(nghttp2_headers *frame,
                                         const uint8_t *payload);

/*
 * 将PRIORITY frame | frame |打包为wire格式，并将其存储在|bufs|中。
 *
 * 调用方必须确保在调用此函数之前调用了nghttp2_bufs_reset（bufs）。
 *
 * 此函数始终成功并返回0。
 */
int nghttp2_frame_pack_priority(nghttp2_bufs *bufs, nghttp2_priority *frame);

/*
 * 将PRIORITY导线格式解压缩为|frame |。
 */
void nghttp2_frame_unpack_priority_payload(nghttp2_priority *frame,
                                           const uint8_t *payload);

/*
 * 将RST_STREAM帧|帧|打包为线框格式，并将其存储在|bufs|中。
 *
 * 调用方必须确保在调用此函数之前调用了nghttp2_bufs_reset（bufs）。
 *
 * 此函数始终成功并返回0。
 */
int nghttp2_frame_pack_rst_stream(nghttp2_bufs *bufs,
                                  nghttp2_rst_stream *frame);

/*
 * 将RST_STREAM帧字节序列解压缩为|frame |。
 */
void nghttp2_frame_unpack_rst_stream_payload(nghttp2_rst_stream *frame,
                                             const uint8_t *payload);

/*
 * 将SETTINGS frame | frame |打包为wire格式，并将其存储在|bufs|中。
 *
 * 调用方必须确保在调用此函数之前调用了nghttp2_bufs_reset（bufs）。
 *
 * 如果成功，此函数将返回0，或返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_FRAME_SIZE_ERROR帧的长度太大。
 */
int nghttp2_frame_pack_settings(nghttp2_bufs *bufs, nghttp2_settings *frame);

/*
 * 假设|buf|至少有8个|niv|字节，则将包含|niv|items的|iv|打包到|buf|中。
 *
 * 返回写入|buf|的字节数。
 */
size_t nghttp2_frame_pack_settings_payload(uint8_t *buf,
                                           const nghttp2_settings_entry *iv,
                                           size_t niv);

void nghttp2_frame_unpack_settings_entry(nghttp2_settings_entry *iv,
                                         const uint8_t *payload);

/*
 * 初始化帧->设置的有效负载。|frame|拥有|iv|的所有权。
 */
void nghttp2_frame_unpack_settings_payload(nghttp2_settings *frame,
                                           nghttp2_settings_entry *iv,
                                           size_t niv);

/*
 * 将SETTINGS负载解压缩到|*iv_ptr|中。条目数分配给|niv_ptr|。此函数分配足够的内存以将结果存储在|iv_ptr|中。调用方负责在使用后释放|iv_ptr|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_frame_unpack_settings_payload2(nghttp2_settings_entry **iv_ptr,
                                           size_t *niv_ptr,
                                           const uint8_t *payload,
                                           size_t payloadlen, nghttp2_mem *mem);

/*
 * 将PUSH_PROMISE帧|frame |打包为wire格式，并将其存储在|bufs|中。此函数根据需要展开|bufs|以存储帧。
 *
 * 调用方必须确保在调用此函数之前调用了nghttp2_bufs_reset（bufs）。
 *
 * 框架->高清。长度在包装过程中确定后分配。连续帧也在该函数中序列化。此函数不处理填充。
 *
 * 如果成功，此函数将返回0，或返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_HEADER_COMP放气操作失败。NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_frame_pack_push_promise(nghttp2_bufs *bufs,
                                    nghttp2_push_promise *frame,
                                    nghttp2_hd_deflater *deflater);

/*
 * 将PUSH_PROMISE帧字节序列解压缩到|frame |中。此函数仅取消名称/值标题块之前和可能的填充长度字段之后的字节。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_PROTO TODO END_HEADERS标志未设置
 */
int nghttp2_frame_unpack_push_promise_payload(nghttp2_push_promise *frame,
                                              const uint8_t *payload);

/*
 * 将PING帧|frame |打包为wire格式，并将其存储在|bufs|中。
 *
 * 调用方必须确保在调用此函数之前调用了nghttp2_bufs_reset（bufs）。
 *
 * 此函数始终成功并返回0。
 */
int nghttp2_frame_pack_ping(nghttp2_bufs *bufs, nghttp2_ping *frame);

/*
 * 将PING线格式解压缩为|frame |。
 */
void nghttp2_frame_unpack_ping_payload(nghttp2_ping *frame,
                                       const uint8_t *payload);

/*
 * 将GOAWAY frame | frame |打包为wire格式，并将其存储在|bufs|中。此函数根据需要展开|bufs|以存储帧。
 *
 * 调用方必须确保在调用此函数之前调用了nghttp2_bufs_reset（bufs）。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_FRAME_SIZE_ERROR帧的长度太大。
 */
int nghttp2_frame_pack_goaway(nghttp2_bufs *bufs, nghttp2_goaway *frame);

/*
 * 将GOAWAY wire格式解压缩为|frame |。长度为|payloadlen|的|payload |包含前8个字节的负载。长度为|var_gift_paiload|的|var_glift_paiload |包含剩余的有效载荷，其缓冲区被分配给函数，然后是|frame |。必须通过nghttp2_frame_goaway_free（）释放|var_gift_pailoadlen|。
 */
void nghttp2_frame_unpack_goaway_payload(nghttp2_goaway *frame,
                                         const uint8_t *payload,
                                         uint8_t *var_gift_payload,
                                         size_t var_gift_payloadlen);

/*
 * 将GOAWAY wire格式解压缩为|frame |。此功能仅适用于单元测试。为调试数据分配缓冲区后，此函数在内部调用nghttp2_frame_unpack_goaway_payload（）。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_frame_unpack_goaway_payload2(nghttp2_goaway *frame,
                                         const uint8_t *payload,
                                         size_t payloadlen, nghttp2_mem *mem);

/*
 * 将WINDOW_UPDATE帧|frame|打包为线框格式，并将其存储在|bufs|中。
 *
 * 调用方必须确保在调用此函数之前调用了nghttp2_bufs_reset（bufs）。
 *
 * 此函数始终成功并返回0。
 */
int nghttp2_frame_pack_window_update(nghttp2_bufs *bufs,
                                     nghttp2_window_update *frame);

/*
 * 将WINDOW_UPDATE帧字节序列解压缩为|frame |。
 */
void nghttp2_frame_unpack_window_update_payload(nghttp2_window_update *frame,
                                                const uint8_t *payload);

/*
 * 将ALTSVC帧|帧|打包为线帧格式，并将其存储在|bufs|中。
 *
 * 调用方必须确保在调用此函数之前调用了nghttp2_bufs_reset（bufs）。
 *
 * 此函数始终成功并返回0。
 */
int nghttp2_frame_pack_altsvc(nghttp2_bufs *bufs, nghttp2_extension *ext);

/*
 * 将ALTSVC导线格式解压缩为|frame |。|payloadlen|字节的|payload |包含帧负载。此函数假定frame->payload指向nghttp2_ext_altsvc对象。
 *
 * 此函数始终成功并返回0。
 */
void nghttp2_frame_unpack_altsvc_payload(nghttp2_extension *frame,
                                         size_t origin_len, uint8_t *payload,
                                         size_t payloadlen);

/*
 * 将ALTSVC导线格式解压缩为|frame |。此功能仅适用于单元测试。为字段分配缓冲区后，此函数在内部调用nghttp2_frame_unpack_altsvc_payload（）。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_FRAME_SIZE_ERROR有效负载太小。
 */
int nghttp2_frame_unpack_altsvc_payload2(nghttp2_extension *frame,
                                         const uint8_t *payload,
                                         size_t payloadlen, nghttp2_mem *mem);

/*
 * 将ORIGIN frame | frame |打包为wire frame格式，并将其存储在|bufs|中。
 *
 * 调用方必须确保在调用此函数之前调用了nghttp2_bufs_reset（bufs）。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_FRAME_SIZE_ERROR帧的长度太大。
 */
int nghttp2_frame_pack_origin(nghttp2_bufs *bufs, nghttp2_extension *ext);

/*
 * 将ORIGIN wire格式解压缩为|frame |。长度为|payloadlen|的|payload |包含帧负载。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_FRAME_SIZE_ERROR有效负载太小。
 */
int nghttp2_frame_unpack_origin_payload(nghttp2_extension *frame,
                                        const uint8_t *payload,
                                        size_t payloadlen, nghttp2_mem *mem);
/*
 * 使用给定值初始化HEADERS帧|frame ||frame|拥有|nva|的所有权，所以调用者不能释放它。如果尚未分配|stream_id|，则必须为-1。
 */
void nghttp2_frame_headers_init(nghttp2_headers *frame, uint8_t flags,
                                int32_t stream_id, nghttp2_headers_category cat,
                                const nghttp2_priority_spec *pri_spec,
                                nghttp2_nv *nva, size_t nvlen);

void nghttp2_frame_headers_free(nghttp2_headers *frame, nghttp2_mem *mem);

void nghttp2_frame_priority_init(nghttp2_priority *frame, int32_t stream_id,
                                 const nghttp2_priority_spec *pri_spec);

void nghttp2_frame_priority_free(nghttp2_priority *frame);

void nghttp2_frame_rst_stream_init(nghttp2_rst_stream *frame, int32_t stream_id,
                                   uint32_t error_code);

void nghttp2_frame_rst_stream_free(nghttp2_rst_stream *frame);

/*
 * 使用给定值初始化PUSH_PROMISE帧|frame ||frame|拥有|nva|的所有权，所以调用者不能释放它。
 */
void nghttp2_frame_push_promise_init(nghttp2_push_promise *frame, uint8_t flags,
                                     int32_t stream_id,
                                     int32_t promised_stream_id,
                                     nghttp2_nv *nva, size_t nvlen);

void nghttp2_frame_push_promise_free(nghttp2_push_promise *frame,
                                     nghttp2_mem *mem);

/*
 * 使用给定值初始化SETTINGS帧|frame ||帧|拥有|iv|的所有权，所以调用者不能释放它。|flags |是一个或多个nghttp2_settings_flag的位或。
 */
void nghttp2_frame_settings_init(nghttp2_settings *frame, uint8_t flags,
                                 nghttp2_settings_entry *iv, size_t niv);

void nghttp2_frame_settings_free(nghttp2_settings *frame, nghttp2_mem *mem);

/*
 * 使用给定值初始化PING帧|frame |。如果|opque_data|不为NULL，则它必须指向8字节的数据内存区域。复制|opaque_data|所指向的数据。它可以为NULL。在这种情况下，使用8字节NULL。
 */
void nghttp2_frame_ping_init(nghttp2_ping *frame, uint8_t flags,
                             const uint8_t *opque_data);

void nghttp2_frame_ping_free(nghttp2_ping *frame);

/*
 * 使用给定值初始化GOAWAY帧|frame |。一旦成功，此函数将获得|opaque_data|的所有权，所以调用者不能释放它。如果|opaque_data_len|为0，则opaque_data可能为NULL。
 */
void nghttp2_frame_goaway_init(nghttp2_goaway *frame, int32_t last_stream_id,
                               uint32_t error_code, uint8_t *opaque_data,
                               size_t opaque_data_len);

void nghttp2_frame_goaway_free(nghttp2_goaway *frame, nghttp2_mem *mem);

void nghttp2_frame_window_update_init(nghttp2_window_update *frame,
                                      uint8_t flags, int32_t stream_id,
                                      int32_t window_size_increment);

void nghttp2_frame_window_update_free(nghttp2_window_update *frame);

void nghttp2_frame_extension_init(nghttp2_extension *frame, uint8_t type,
                                  uint8_t flags, int32_t stream_id,
                                  void *payload);

void nghttp2_frame_extension_free(nghttp2_extension *frame);

/*
 * 使用给定值初始化ALTSVC帧|帧|。此函数假定frame->payload指向nghttp2_ext_altsvc对象。此外，|origin|和|field_value|在单个缓冲区中分配，从|origin|。一旦成功，此函数将获得|origin|的所有权，所以调用者不能释放它。
 */
void nghttp2_frame_altsvc_init(nghttp2_extension *frame, int32_t stream_id,
                               uint8_t *origin, size_t origin_len,
                               uint8_t *field_value, size_t field_value_len);

/*
 * 释放|frame |下的资源。此函数不会释放frame->payload指向的nghttp2_ext_altsvc对象。此函数仅释放nghttp2_ext_altsvc.origin指向的原点。因此，其他字段必须与原始字段分配在同一缓冲区中。
 */
void nghttp2_frame_altsvc_free(nghttp2_extension *frame, nghttp2_mem *mem);

/*
 * 使用给定值初始化ORIGIN帧|frame |。此函数假定frame->payload指向nghttp2_ext_origin对象。此外，|ov|及其元素字段所指向的内存分配在单个缓冲区中，从|ov|开始。一旦成功，此函数将获得|ov|的所有权，所以调用者不能释放它。
 */
void nghttp2_frame_origin_init(nghttp2_extension *frame,
                               nghttp2_origin_entry *ov, size_t nov);

/*
 * 释放|frame |下的资源。此函数不会释放frame->payload指向的nghttp2_ext_origin对象。此函数仅释放nghttp2_ext_origin.ov。因此，必须在与ov相同的缓冲区中分配其他字段。
 */
void nghttp2_frame_origin_free(nghttp2_extension *frame, nghttp2_mem *mem);

/*
 * 返回有效负载后的填充字节数。总填充长度在|padlen|中给出。返回的值不包括“焊盘长度”字段。如果|padlen|为0，则无论frame->hd.flags如何，此函数都返回0。
 */
size_t nghttp2_frame_trail_padlen(nghttp2_frame *frame, size_t padlen);

void nghttp2_frame_data_init(nghttp2_data *frame, uint8_t flags,
                             int32_t stream_id);

void nghttp2_frame_data_free(nghttp2_data *frame);

/*
 * 复制|iv|并返回副本。|niv|是|iv|中的条目数。如果复制成功，此函数将返回指向复制的指针，或返回NULL。
 */
nghttp2_settings_entry *nghttp2_frame_iv_copy(const nghttp2_settings_entry *iv,
                                              size_t niv, nghttp2_mem *mem);

/*
 * 按名称和值的升序对|nva|排序。如果名称等效，请按值对其排序。
 */
void nghttp2_nv_array_sort(nghttp2_nv *nva, size_t nvlen);

/*
 * 将名称/值对从包含|nvlen|对的|nva|复制到动态分配的|nva_ptr|，以便存储所有项。nghttp2_nv中的结果名称和值保证以NULL结尾，即使输入不是以NULL结尾。
 *
 * 必须使用nghttp2_nv_array_dl（）释放|*nva_ptr|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_nv_array_copy(nghttp2_nv **nva_ptr, const nghttp2_nv *nva,
                          size_t nvlen, nghttp2_mem *mem);

/*
 * 如果名称/值对|a|等于|b|，则返回非零。该名称区分大小写，因为我们确保在名称小写后调用此函数。
 */
int nghttp2_nv_equal(const nghttp2_nv *a, const nghttp2_nv *b);

/*
 * 释放|nva|。
 */
void nghttp2_nv_array_del(nghttp2_nv *nva, nghttp2_mem *mem);

/*
 * 检查包含|niv|项的|iv|是否没有无效值。
 *
 * 如果此函数成功，则返回非零，或者返回0。
 */
int nghttp2_iv_check(const nghttp2_settings_entry *iv, size_t niv);

/*
 * 设置填充长度字段和标志，并调整|bufs|中每个缓冲区的帧头位置。填充数在|padlen|包括填充长度字段中给出。|hd|是序列化数据的帧头。除非framehd_only为非零，否则此函数将填充零填充区域。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。NGHTTP2_ERR_FRAME_SIZE_ERROR结果帧的长度太大。
 */
int nghttp2_frame_add_pad(nghttp2_bufs *bufs, nghttp2_frame_hd *hd,
                          size_t padlen, int framehd_only);

#endif /* NGHTTP2_FRAME_H */

