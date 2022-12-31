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
#ifndef SHRPX_DNS_RESOLVER_H
#define SHRPX_DNS_RESOLVER_H

#include "shrpx.h"

#include <sys/socket.h>
#include <netinet/in.h>

#include <vector>

#include <ev.h>
#include <ares.h>

#include "template.h"
#include "network.h"

using namespace nghttp2;

namespace shrpx {

enum class DNSResolverStatus {
  // 解析器处于初始状态
  IDLE,
  // 解析器当前正在解析主机名
  RUNNING,
  // 解析程序已成功解析主机名
  OK,
  // 解析程序无法解析主机名
  ERROR,
};

// 主机名查找完成时调用回调函数。
// |status |是DNSResolverStatus:：OK，或
// DNSResolverStatus：：错误。如果|status |是DNSResolverStatus:：OK，
// |result|指向解析的地址。注意，的端口部分
// |result|未定义，必须由应用程序初始化。
// 如果名称查找在
// DNSResolver:：resolve（）已完成。在这种情况下，应用程序
// 应调用DNSResolver:：get_status（）以获取当前状态和
// 后果换句话说，如果get_status（）返回
// DNSResolverStatus：：正在运行。
using CompleteCb =
    std::function<void(DNSResolverStatus status, const Address *result)>;

// DNSResolver是由c-ares支持的异步名称解析器
// 图书馆
class DNSResolver {
public:
  DNSResolver(struct ev_loop *loop);
  ~DNSResolver();

  // 开始解析主机名|name|。
  int resolve(const StringRef &name, int family);
  // 返回状态。如果status_为DNSResolverStatus:：SUCCESS&&
  // |result|不是nullptr，|*result|已填充。
  DNSResolverStatus get_status(Address *result) const;
  // 设置名称查找完成时的回调函数。回调
  // 函数的调用方式可以破坏此DNSResolver。
  void set_complete_cb(CompleteCb cb);
  CompleteCb get_complete_cb() const;

  // 分别在发生读/写事件时调用这些函数。
  int on_read(int fd);
  int on_write(int fd);
  int on_timeout();
  // DNS查询完成时调用此函数。
  void on_result(int staus, hostent *hostent);
  void reset_timeout();

  void start_rev(int fd);
  void stop_rev(int fd);
  void start_wev(int fd);
  void stop_wev(int fd);

private:
  int handle_event(int rfd, int wfd);

  std::vector<std::unique_ptr<ev_io>> revs_, wevs_;
  Address result_;
  CompleteCb completeCb_;
  ev_timer timer_;
  StringRef name_;
  struct ev_loop *loop_;
  // ares_channel是指针类型
  ares_channel channel_;
  // AF_INET或AF_INET6.AF_INET用于记录查找，AF_INET6
  // 用于AAAA记录查找。
  int family_;
  DNSResolverStatus status_;
};

} // 命名空间shrpx

#endif // SHRPX_DNS_RESOLVER_H

