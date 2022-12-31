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
#ifndef SHRPX_SIGNAL_H
#define SHRPX_SIGNAL_H

#include "shrpx.h"

#include <signal.h>

namespace shrpx {

constexpr int REOPEN_LOG_SIGNAL = SIGUSR1;
constexpr int EXEC_BINARY_SIGNAL = SIGUSR2;
constexpr int GRACEFUL_SHUTDOWN_SIGNAL = SIGQUIT;
constexpr int RELOAD_SIGNAL = SIGHUP;

// 阻止所有信号。先前的信号掩码存储在
// |oldset |如果它不是nullptr。如果
// 成功，或-1。错误号将指示错误。
int shrpx_signal_block_all(sigset_t *oldset);

// 取消阻止所有信号。如果成功，则此函数返回0，或者
// -1.错误号将指示错误。
int shrpx_signal_unblock_all();

// 设置信号掩码|set|。如果成功，则此函数返回0，或者
// -1.错误号将指示错误。
int shrpx_signal_set(sigset_t *set);

int shrpx_signal_set_master_proc_ign_handler();
int shrpx_signal_unset_master_proc_ign_handler();

int shrpx_signal_set_worker_proc_ign_handler();
int shrpx_signal_unset_worker_proc_ign_handler();

} // 命名空间shrpx

#endif // SHRPX_SIGNAL_H

