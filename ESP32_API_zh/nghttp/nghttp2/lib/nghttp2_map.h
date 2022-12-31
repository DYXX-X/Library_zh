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
#ifndef NGHTTP2_MAP_H
#define NGHTTP2_MAP_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>
#include "nghttp2_int.h"
#include "nghttp2_mem.h"

/* 无序映射的实现*/

typedef int32_t key_type;

typedef struct nghttp2_map_entry {
  struct nghttp2_map_entry *next;
  key_type key;
#if SIZEOF_INT_P == 4
  /* 我们需要8字节对齐*/
  int64_t pad;
#endif
} nghttp2_map_entry;

typedef struct {
  nghttp2_map_entry **table;
  nghttp2_mem *mem;
  size_t size;
  uint32_t tablelen;
} nghttp2_map;

/*
 * 初始化map|map|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_map_init(nghttp2_map *map, nghttp2_mem *mem);

/*
 * 取消分配分配给|map|的所有资源。此函数不会释放存储的条目。使用nghttp2_map_each_free（）释放每个条目。
 */
void nghttp2_map_free(nghttp2_map *map);

/*
 * 使用|func|函数和为|map|分配的所有资源来取消分配每个条目。|func|函数负责释放给定的|entry|对象。|ptr|将作为send参数传递给|func|。将忽略|func|的返回值。
 */
void nghttp2_map_each_free(nghttp2_map *map,
                           int (*func)(nghttp2_map_entry *entry, void *ptr),
                           void *ptr);

/*
 * 使用|键|初始化|条目|。必须使用此函数初始化要插入到映射中的所有条目。
 */
void nghttp2_map_entry_init(nghttp2_map_entry *entry, key_type key);

/*
 * 使用键|entry->key|将新的|entry|插入到map|map|中。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_INVALID_ARGUMENT与|key|关联的项已存在。NGHTTP2_ERR_NOMEM内存不足
 */
int nghttp2_map_insert(nghttp2_map *map, nghttp2_map_entry *entry);

/*
 * 返回键|key|关联的条目。如果没有这样的条目，则此函数返回NULL。
 */
nghttp2_map_entry *nghttp2_map_find(nghttp2_map *map, key_type key);

/*
 * 从|map|中删除键|key|关联的条目。此函数不会释放删除的条目。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_INVALID_ARGUMENT与|key|关联的条目不存在。
 */
int nghttp2_map_remove(nghttp2_map *map, key_type key);

/*
 * 返回映射|map|中存储的项数。
 */
size_t nghttp2_map_size(nghttp2_map *map);

/*
 * 使用可选的用户提供的指针|ptr|将函数|func|应用于|map|中的每个条目。
 *
 * 如果|func|返回0，则此函数使用下一个条目调用|func|。如果|func|返回非零，它将不会调用|func|for进一步的条目，并立即返回|func||的返回值。因此，如果|func|的所有调用都返回0或上次调用|func|返回的非零值，则此函数返回0。
 *
 * 不要使用此函数释放每个条目。请改用nghttp2_map_each_free（）。
 */
int nghttp2_map_each(nghttp2_map *map,
                     int (*func)(nghttp2_map_entry *entry, void *ptr),
                     void *ptr);

#endif /* NGHTTP2_MAP_H */

