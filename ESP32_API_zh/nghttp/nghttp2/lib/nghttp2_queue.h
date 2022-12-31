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
#ifndef NGHTTP2_QUEUE_H
#define NGHTTP2_QUEUE_H

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>

typedef struct nghttp2_queue_cell {
  void *data;
  struct nghttp2_queue_cell *next;
} nghttp2_queue_cell;

typedef struct {
  nghttp2_queue_cell *front, *back;
} nghttp2_queue;

void nghttp2_queue_init(nghttp2_queue *queue);
void nghttp2_queue_free(nghttp2_queue *queue);
int nghttp2_queue_push(nghttp2_queue *queue, void *data);
void nghttp2_queue_pop(nghttp2_queue *queue);
void *nghttp2_queue_front(nghttp2_queue *queue);
void *nghttp2_queue_back(nghttp2_queue *queue);
int nghttp2_queue_empty(nghttp2_queue *queue);

#endif /* NGHTTP2_QUEUE_H */

