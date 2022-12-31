/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2014 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SHRPX_CONNECT_BLOCKER_H
#define SHRPX_CONNECT_BLOCKER_H

#include "shrpx.h"

#include <random>
#include <functional>

#include <ev.h>

namespace shrpx {

class ConnectBlocker {
public:
  ConnectBlocker(std::mt19937 &gen, struct ev_loop *loop,
                 std::function<void()> block_func,
                 std::function<void()> unblock_func);
  ~ConnectBlocker();

  // 如果不允许建立连接，则返回true。
  bool blocked() const;
  // 如果连接操作成功，请调用此函数。这将
  // 将sleep_重置为最小值。
  void on_success();
  // 如果连接操作失败，请调用此函数。这将开始
  // 定时器和块连接建立与指数
  // 后退。
  void on_failure();

  size_t get_fail_count() const;

  // 对等方现在被视为脱机。这实际上意味着
  // 连接被阻止，直到调用online（）。
  void offline();

  // 对等体现在被视为在线
  void online();

  // 如果对等方被视为脱机，则返回true。
  bool in_offline() const;

  void call_block_func();
  void call_unblock_func();

private:
  std::mt19937 &gen_;
  // 当阻塞开始时调用
  std::function<void()> block_func_;
  // 取消阻止时调用
  std::function<void()> unblock_func_;
  ev_timer timer_;
  struct ev_loop *loop_;
  // 连续连接失败的次数。重置为0
  // 成功
  size_t fail_count_;
  // 如果对等体被视为脱机，则为true。
  bool offline_;
};

} // 命名空间shrpx

#endif // SHRPX_CONNECT_BLOCKER_H

