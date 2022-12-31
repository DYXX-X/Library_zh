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
#ifndef SHRPX_DUAL_DNS_RESOLVER_H
#define SHRPX_DUAL_DNS_RESOLVER_H

#include "shrpx.h"

#include <ev.h>

#include "shrpx_dns_resolver.h"

using namespace nghttp2;

namespace shrpx {

// DualDNSResolver执行A和AAAA的名称解析
// 同时记录。第一次成功返回（或如果我们
// 具有两个成功的结果，优选AAAA）。这是
// 包装内2个DNSResolver。resolve（）、get_status（）和
// CompleteCb的调用方式与DNSResolver具有相同的语义。
class DualDNSResolver {
public:
  DualDNSResolver(struct ev_loop *loop);

  // 解析|host||host|必须是以NULL结尾的字符串。
  int resolve(const StringRef &host);
  CompleteCb get_complete_cb() const;
  void set_complete_cb(CompleteCb cb);
  DNSResolverStatus get_status(Address *result) const;

private:
  // 对于A记录
  DNSResolver resolv4_;
  // AAAA记录
  DNSResolver resolv6_;
  CompleteCb complete_cb_;
};

} // 命名空间shrpx

#endif // SHRPX_DUAL_DNS_RESOLVER_H

