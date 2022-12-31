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
#ifndef SHRPX_DOWNSTREAM_QUEUE_H
#define SHRPX_DOWNSTREAM_QUEUE_H

#include "shrpx.h"

#include <cinttypes>
#include <map>
#include <set>
#include <memory>

#include "template.h"

using namespace nghttp2;

namespace shrpx {

class Downstream;

// HostEntry中的链接条目。下游堵塞，因为下游
// 可以随时在中删除，我们希望在中找到下游
// O（1）。下游具有要链接回此对象的字段。
struct BlockedLink {
  Downstream *downstream;
  BlockedLink *dlnext, *dlprev;
};

class DownstreamQueue {
public:
  struct HostEntry {
    HostEntry(ImmutableString &&key);

    HostEntry(HostEntry &&) = default;
    HostEntry &operator=(HostEntry &&) = default;

    HostEntry(const HostEntry &) = delete;
    HostEntry &operator=(const HostEntry &) = delete;

    // 关联此对象的键
    ImmutableString key;
    // conn_max_per_host_阻止的流ID集。
    DList<BlockedLink> blocked;
    // 当前与此主机的连接数。
    size_t num_active;
  };

  using HostEntryMap = std::map<StringRef, HostEntry>;

  // conn_max_per_host==0表示下游连接没有限制。
  DownstreamQueue(size_t conn_max_per_host = 0, bool unified_host = true);
  ~DownstreamQueue();
  // 将|下游|添加到此队列。这是的入口点
  // 下游对象。
  void add_pending(std::unique_ptr<Downstream> downstream);
  // 将|下游|设置为故障状态，这意味着下游
  // 无法连接到后端。
  void mark_failure(Downstream *downstream);
  // 将|下游|设置为活动状态，这意味着下游
  // 连接已启动。
  void mark_active(Downstream *downstream);
  // 将|下游|设置为阻止状态，这意味着下载
  // 连接被阻止，因为conn_max_per_host限制。
  void mark_blocked(Downstream *downstream);
  // 如果我们可以与给定的
  // |主机|。
  bool can_activate(const StringRef &host) const;
  // 删除并释放|下游|对象。如果|下游|在
  // DispatchState:：ACTIVE，并且|next_blocked|为true，则此函数
  // 可以返回具有相同目标主机的下游对象
  // DispatchState:：BLOCKED，如果其连接现在未被阻止
  // conn_max per_host_限制。
  Downstream *remove_and_get_blocked(Downstream *downstream,
                                     bool next_blocked = true);
  Downstream *get_downstreams() const;
  HostEntry &find_host_entry(const StringRef &host);
  StringRef make_host_key(const StringRef &host) const;
  StringRef make_host_key(Downstream *downstream) const;

private:
  // 按目标主机结构跟踪
  // 连接到同一主机。
  HostEntryMap host_entries_;
  DList<Downstream> downstreams_;
  // 到同一主机的最大并发连接数。
  size_t conn_max_per_host_;
  // 如果下游主机被视为相同的主机，则为true。用于倒车
  // 代理。
  bool unified_host_;
};

} // 命名空间shrpx

#endif // SHRPX_DOWNSTREAM_QUEUE_H

