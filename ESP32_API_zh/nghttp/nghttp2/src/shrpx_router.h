/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2015 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SHRPX_ROUTER_H
#define SHRPX_ROUTER_H

#include "shrpx.h"

#include <vector>
#include <memory>

#include "allocator.h"

using namespace nghttp2;

namespace shrpx {

struct RNode {
  RNode();
  RNode(const char *s, size_t len, ssize_t index, ssize_t wildcard_index);
  RNode(RNode &&) = default;
  RNode(const RNode &) = delete;
  RNode &operator=(RNode &&) = default;
  RNode &operator=(const RNode &) = delete;

  // 下一个RNode，按s[0]排序。
  std::vector<std::unique_ptr<RNode>> next;
  // 存储指向此节点表示的字符串的指针。不
  // NULL终止。
  const char *s;
  // %s的长度|
  size_t len;
  // 如果匹配在此节点中结束，则为模式索引。注意，我们没有
  // 存储重复模式。
  ssize_t index;
  // 如果查询包含此节点作为前缀，则为通配符模式的索引
  // 它仍然有后缀要匹配。注意，我们不存储
  // 复制模式。
  ssize_t wildcard_index;
};

class Router {
public:
  Router();
  ~Router();
  Router(Router &&) = default;
  Router(const Router &) = delete;
  Router &operator=(Router &&) = default;
  Router &operator=(const Router &) = delete;

  // 添加路由|模式|及其|索引|。如果相同的模式
  // 已添加，则返回现有索引。如果
  // |通配符|为真，|pattern|被认为是通配符模式，
  // 以及所有以|pattern|为前缀且严格
  // 长于|pattern|匹配。通配符模式只起作用
  // 具有匹配项（const StringRef&，const StringRef&）。
  size_t add_route(const StringRef &pattern, size_t index,
                   bool wildcard = false);
  // 返回匹配的模式索引-如果不匹配，则为1。
  ssize_t match(const StringRef &host, const StringRef &path) const;
  // 返回模式|s|的匹配索引-如果没有，则为1
  // 火柴
  ssize_t match(const StringRef &s) const;
  // 如果模式是的后缀，则返回匹配的模式索引
  // |s|，否则为-1。如果|*last_node|不是nullptr，则指定
  // 第一个开始匹配的节点。如果它是nullptr，则匹配将
  // 从头开始。找到匹配项时（返回值
  // 不是-1），|*nrread|具有|s|中匹配的字节数，并且
  // |*last_node |具有最后匹配的节点。人们可以继续
  // 使用返回的|*last_node|匹配较长的模式
  // 再次调用此函数，直到返回-1。
  ssize_t match_prefix(size_t *nread, const RNode **last_node,
                       const StringRef &s) const;

  void add_node(RNode *node, const char *pattern, size_t patlen, ssize_t index,
                ssize_t wildcard_index);

  void dump() const;

private:
  BlockAllocator balloc_;
  // Patricia树的根节点。这是一个特殊的节点及其
  // 字段为nulptr，len字段为0。
  RNode root_;
};

} // 命名空间shrpx

#endif // SHRPX_ROUTER_H

