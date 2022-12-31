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
#ifndef NGHTTP2_NET_H
#define NGHTTP2_NET_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_ARPA_INET_H
#  include <arpa/inet.h>
#endif /* HAVE_ARPA_INET_H */

#ifdef HAVE_NETINET_IN_H
#  include <netinet/in.h>
#endif /* HAVE_NETINET_IN_H */

#include <nghttp2/nghttp2.h>

#if defined(WIN32)
/* Windows需要用于ntonl系列函数的ws2_32库。我们为这些函数定义内联函数，这样我们就不会依赖于该库。*/

#  ifdef _MSC_VER
#    define STIN static __inline
#  else
#    define STIN static inline
#  endif

STIN uint32_t htonl(uint32_t hostlong) {
  uint32_t res;
  unsigned char *p = (unsigned char *)&res;
  *p++ = hostlong >> 24;
  *p++ = (hostlong >> 16) & 0xffu;
  *p++ = (hostlong >> 8) & 0xffu;
  *p = hostlong & 0xffu;
  return res;
}

STIN uint16_t htons(uint16_t hostshort) {
  uint16_t res;
  unsigned char *p = (unsigned char *)&res;
  *p++ = hostshort >> 8;
  *p = hostshort & 0xffu;
  return res;
}

STIN uint32_t ntohl(uint32_t netlong) {
  uint32_t res;
  unsigned char *p = (unsigned char *)&netlong;
  res = *p++ << 24;
  res += *p++ << 16;
  res += *p++ << 8;
  res += *p;
  return res;
}

STIN uint16_t ntohs(uint16_t netshort) {
  uint16_t res;
  unsigned char *p = (unsigned char *)&netshort;
  res = *p++ << 8;
  res += *p;
  return res;
}

#endif /* WIN32 */

#endif /* NGHTTP2_NET_H */

