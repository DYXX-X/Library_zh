/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2016 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef NGHTTP2_RCBUF_H
#define NGHTTP2_RCBUF_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nghttp2/nghttp2.h>

struct nghttp2_rcbuf {
  /* 在创建此对象时，自定义内存分配器属于mem参数。*/
  void *mem_user_data;
  nghttp2_free free;
  /* 指向基础缓冲区的指针*/
  uint8_t *base;
  /* |base|指向的缓冲区大小。*/
  size_t len;
  /* 引用计数*/
  int32_t ref;
};

/*
 * 使用|size|作为初始缓冲区大小分配nghttp2_rcbuf对象。当函数成功时，引用计数变为1。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM：内存不足。
 */
int nghttp2_rcbuf_new(nghttp2_rcbuf **rcbuf_ptr, size_t size, nghttp2_mem *mem);

/*
 * 与nghttp2_rcbuf_new（）类似，但使用长度为|srclen|的|src|初始化缓冲区。此函数在末尾分配额外的字节，并将“\0”放入其中，以便生成的缓冲区可以用作以NULL结尾的字符串。仍然（rcbuf_ptr）->len等于|srclen|。
 *
 * 如果成功，此函数将返回0，或者返回以下负错误代码之一：
 *
 * NGHTTP2_ERR_NOMEM：内存不足。
 */
int nghttp2_rcbuf_new2(nghttp2_rcbuf **rcbuf_ptr, const uint8_t *src,
                       size_t srclen, nghttp2_mem *mem);

/*
 * 释放|rcbuf|自身，而不管其引用cout。
 */
void nghttp2_rcbuf_del(nghttp2_rcbuf *rcbuf);

#endif /* NGHTTP2_RCBUF_H */

