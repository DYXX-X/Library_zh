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
#ifndef MALLOC_WRAPPER_H
#define MALLOC_WRAPPER_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdlib.h>

#include "nghttp2_mem.h"

/* 控制malloc（）行为的全局变量*/

/* 如果非零，malloc故障模式将启用*/
extern int nghttp2_failmalloc;
/* 如果nghttp2_failstart<=nghttp2_nmalloc且nghttp2_failmalloc为非零，malloc（）将失败。*/
extern int nghttp2_failstart;
/* 如果非零，如果malloc（）成功，nghttp2_nmalloc将递增。*/
extern int nghttp2_countmalloc;
/* 成功调用malloc（）的次数。仅当nghttp2_nmalloc为非零时，此值才递增。*/
extern int nghttp2_nmalloc;

/* 返回指向nghttp2_mem的指针，当取消引用时，该指针包含专门用于故障检测的内存分配器。*/
nghttp2_mem *nghttp2_mem_fm(void);

/* 将nghttp2_failmalloc和nghttp2_countmalloc复制到静态分配的空间，并将其设置为0。这将有效地使malloc（）像正常malloc）一样工作。当您想暂时禁用malloc（）失败模式时，这很有用。*/
void nghttp2_failmalloc_pause(void);

/* 将nghttp2_failmalloc和nghttp2_countmalloc的值恢复为上一个nghttp2_failmalloc_pause（）保存的值。*/
void nghttp2_failmalloc_unpause(void);

#endif /* MALLOC_WRAPPER_H */

