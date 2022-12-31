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
#ifndef NGHTTP2_HELPER_H
#define NGHTTP2_HELPER_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <string.h>
#include <stddef.h>

#include <nghttp2/nghttp2.h>
#include "nghttp2_mem.h"

#define nghttp2_min(A, B) ((A) < (B) ? (A) : (B))
#define nghttp2_max(A, B) ((A) > (B) ? (A) : (B))

#define lstreq(A, B, N) ((sizeof((A)) - 1) == (N) && memcmp((A), (B), (N)) == 0)

#define nghttp2_struct_of(ptr, type, member)                                   \
  ((type *)(void *)((char *)(ptr)-offsetof(type, member)))

/*
 * 将主机字节顺序的2字节无符号整数|n|复制到网络字节顺序的|buf|。
 */
void nghttp2_put_uint16be(uint8_t *buf, uint16_t n);

/*
 * 将主机字节顺序的4字节无符号整数|n|复制到网络字节顺序的|buf|。
 */
void nghttp2_put_uint32be(uint8_t *buf, uint32_t n);

/*
 * 检索以网络字节顺序存储在|data|中的2字节无符号整数，并以主机字节顺序返回它。
 */
uint16_t nghttp2_get_uint16(const uint8_t *data);

/*
 * 检索以网络字节顺序存储在|data|中的4字节无符号整数，并以主机字节顺序返回它。
 */
uint32_t nghttp2_get_uint32(const uint8_t *data);

void nghttp2_downcase(uint8_t *s, size_t len);

/*
 * 使用|delta_ptr|调整|*local_window_size_ptr|、|*recv_window_size _ptr|，|recv_reduction_ptr|（这是从本地发送的window_UPDATE的window_size_increment）。如果|delta|严格大于|recv_window_size_ptr|，则|local_window_sze_ptr|将增加delta-recv_window_size _ptr。如果|delta|为负，|local_window_size_ptr|将减少delta。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_FLOW_CONTROL local_window_size溢出或为负值。
 */
int nghttp2_adjust_local_window_size(int32_t *local_window_size_ptr,
                                     int32_t *recv_window_size_ptr,
                                     int32_t *recv_reduction_ptr,
                                     int32_t *delta_ptr);

/*
 * 此函数的工作方式类似于nghttp2_adjust_local_window_size（）。不同之处在于，此函数假定delta_ptr>=0，并且recv_window_size_ptr不会减少delta_ptr。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_FLOW_CONTROL local_window_size溢出或为负值。
 */
int nghttp2_increase_local_window_size(int32_t *local_window_size_ptr,
                                       int32_t *recv_window_size_ptr,
                                       int32_t *recv_reduction_ptr,
                                       int32_t *delta_ptr);

/*
 * 如果函数决定发送WINDOW_UPDATE，则返回非零。
 */
int nghttp2_should_send_window_update(int32_t local_window_size,
                                      int32_t recv_window_size);

/*
 * 将长度为|len|的缓冲区|src|复制到|dest|指向的目标，假设|dest|至少为|len |字节长。返回dest+len。
 */
uint8_t *nghttp2_cpymem(uint8_t *dest, const void *src, size_t len);

#endif /* NGHTTP2_HELPER_H */

