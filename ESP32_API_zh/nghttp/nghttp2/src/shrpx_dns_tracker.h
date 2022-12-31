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
#ifndef SHRPX_DNS_TRACKER_H
#define SHRPX_DNS_TRACKER_H

#include "shrpx.h"

#include <map>

#include "shrpx_dual_dns_resolver.h"

using namespace nghttp2;

namespace shrpx {

struct DNSQuery {
  DNSQuery(StringRef host, CompleteCb cb)
      : host(std::move(host)),
        cb(std::move(cb)),
        dlnext(nullptr),
        dlprev(nullptr),
        status(DNSResolverStatus::IDLE),
        in_qlist(false) {}

  // 我们查找的主机名。
  StringRef host;
  // 名称查找完成时调用回调函数。这
  // 如果名称查找在
  // DNSTracker:：resolve（）。
  CompleteCb cb;
  DNSQuery *dlnext, *dlprev;
  DNSResolverStatus status;
  // 如果此对象位于链接列表ResolverEntry:：qlist中，则为true。
  bool in_qlist;
};

struct ResolverEntry {
  // 此条目查找的主机名。
  ImmutableString host;
  // DNS解析程序。仅当状态为
  // DNSResolverStatus：：正在运行。
  std::unique_ptr<DualDNSResolver> resolv;
  // DNSQuery对此名称查找结果感兴趣。结果是
  // 通知他们所有人。
  DList<DNSQuery> qlist;
  // 对DNSResolverStatus使用相同的枚举
  DNSResolverStatus status;
  // 结果及其有效期
  Address result;
  // 缓存结果过期的时间点。
  ev_tstamp expiry;
};

class DNSTracker {
public:
  DNSTracker(struct ev_loop *loop);
  ~DNSTracker();

  // 查找|dnsq|中描述的主机名。如果名称查找完成
  // 在这个函数中（它来自/etc/hosts，主机名
  // 是数字，查找结果被缓存等），则返回
  // DNSResolverStatus:：OK或DNSResolverStatus：：ERROR。如果查找是
  // 成功，返回DNSResolverStatus:：OK，并且|result|为
  // 填满。如果查找失败，则返回DNSResolverStatus:：ERROR。
  // 如果名称查找是在后台完成的，则返回
  // DNSResolverStatus：：正在运行。其完成由
  // 调用dnsq->cb。
  DNSResolverStatus resolve(Address *result, DNSQuery *dnsq);
  // 取消|dnsq|请求的名称查找。
  void cancel(DNSQuery *dnsq);
  // 从ents_中删除过期条目。
  void gc();
  // 启动GC计时器。
  void start_gc_timer();

private:
  ResolverEntry make_entry(std::unique_ptr<DualDNSResolver> resolv,
                           ImmutableString host, DNSResolverStatus status,
                           const Address *result);

  void update_entry(ResolverEntry &ent, std::unique_ptr<DualDNSResolver> resolv,
                    DNSResolverStatus status, const Address *result);

  void add_to_qlist(ResolverEntry &ent, DNSQuery *dnsq);

  std::map<StringRef, ResolverEntry> ents_;
  // 定期迭代ents_，并删除过期条目以避免
  // 过度使用内存。因为只有后端API可能
  // 增加内存消耗，间隔可能很长。
  ev_timer gc_timer_;
  struct ev_loop *loop_;
};

} // 命名空间shrpx

#endif // SHRPX_DNS_TRACKER_H

