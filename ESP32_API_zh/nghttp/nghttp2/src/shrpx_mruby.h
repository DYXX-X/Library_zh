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
#ifndef SHRPX_MRUBY_H
#define SHRPX_MRUBY_H

#include "shrpx.h"

#include <memory>

#include <mruby.h>
#include <mruby/proc.h>

#include "template.h"

using namespace nghttp2;

namespace shrpx {

class Downstream;

namespace mruby {

class MRubyContext {
public:
  MRubyContext(mrb_state *mrb, mrb_value app, mrb_value env);
  ~MRubyContext();

  int run_on_request_proc(Downstream *downstream);
  int run_on_response_proc(Downstream *downstream);

  int run_app(Downstream *downstream, int phase);

  void delete_downstream(Downstream *downstream);

private:
  mrb_state *mrb_;
  mrb_value app_;
  mrb_value env_;
};

enum {
  PHASE_NONE = 0,
  PHASE_REQUEST = 1,
  PHASE_RESPONSE = 1 << 1,
};

struct MRubyAssocData {
  Downstream *downstream;
  int phase;
};

RProc *compile(mrb_state *mrb, const StringRef &filename);

std::unique_ptr<MRubyContext> create_mruby_context(const StringRef &filename);

// 返回interned|ptr|。
mrb_sym intern_ptr(mrb_state *mrb, void *ptr);

// 检查|phase_mask|中是否设置了|phase|。如果未设置，则升高
// 例外
void check_phase(mrb_state *mrb, int phase, int phase_mask);

} // 命名空间mruby

} // 命名空间shrpx

#endif // SHRPX_MRUBY_H

