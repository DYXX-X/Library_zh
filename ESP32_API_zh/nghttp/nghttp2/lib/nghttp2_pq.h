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
#ifndef NGHTTP2_PQ_H
#define NGHTTP2_PQ_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>
#include "nghttp2_int.h"
#include "nghttp2_mem.h"

/* 优先级队列的实现*/

typedef struct {
  size_t index;
} nghttp2_pq_entry;

typedef struct {
  /* 指向指向存储项的指针的指针*/
  nghttp2_pq_entry **q;
  /* 内存分配器*/
  nghttp2_mem *mem;
  /* 存储的项目数*/
  size_t length;
  /* 此pq可以存储的最大项目数。当长度达到此值时，将自动延长。*/
  size_t capacity;
  /* 项目之间的函数较少*/
  nghttp2_less less;
} nghttp2_pq;

/*
 * 使用比较函数|cmp|初始化优先级队列|pq|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_pq_init(nghttp2_pq *pq, nghttp2_less less, nghttp2_mem *mem);

/*
 * 取消分配给|pq|的所有资源。此函数不会释放存储的项目。
 */
void nghttp2_pq_free(nghttp2_pq *pq);

/*
 * 将|item|添加到优先级队列|pq|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM内存不足。
 */
int nghttp2_pq_push(nghttp2_pq *pq, nghttp2_pq_entry *item);

/*
 * 返回队列顶部的项目|pq|。如果队列为空，则此函数返回NULL。
 */
nghttp2_pq_entry *nghttp2_pq_top(nghttp2_pq *pq);

/*
 * 弹出队列顶部的项目|pq|。此函数不会释放弹出的项。
 */
void nghttp2_pq_pop(nghttp2_pq *pq);

/*
 * 如果队列|pq|为空，则返回非零。
 */
int nghttp2_pq_empty(nghttp2_pq *pq);

/*
 * 返回队列|pq|中的项数。
 */
size_t nghttp2_pq_size(nghttp2_pq *pq);

typedef int (*nghttp2_pq_item_cb)(nghttp2_pq_entry *item, void *arg);

/*
 * 使用函数|fun|更新|pq|中的每个项，并重新构造优先级队列。如果|fun|修改项目的方式影响优先级队列中的排序，则它必须返回非零。|arg|传递给|fun|的第二个参数。
 */
void nghttp2_pq_update(nghttp2_pq *pq, nghttp2_pq_item_cb fun, void *arg);

/*
 * 对|pq|中的每个项目应用|fun|。|arg|作为arg参数传递给回调函数。此功能不得更改订购键。如果回调的返回值为非零，则此函数立即返回1，而不重复剩余的项。否则，此函数返回0。
 */
int nghttp2_pq_each(nghttp2_pq *pq, nghttp2_pq_item_cb fun, void *arg);

/*
 * 从优先级队列中删除|item|。
 */
void nghttp2_pq_remove(nghttp2_pq *pq, nghttp2_pq_entry *item);

#endif /* NGHTTP2_PQ_H */

