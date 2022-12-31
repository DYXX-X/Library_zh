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
#ifndef SHRPX_EXEC_H
#define SHRPX_EXEC_H

#include "unistd.h"

namespace shrpx {

struct Process {
  pid_t pid;
  // 要从进程读取的fd
  int rfd;
};

// 分叉当前进程后执行命令|argv|。命令
// 不应期望从stdin读取。父进程可以读取
// 使用proc.rfd从命令stdout。成功后，此功能
// 返回0，进程信息存储在|proc|中。否则
// 返回-1。
int exec_read_command(Process &proc, char *const argv[]);

} // 命名空间shrpx

#endif // SHRPX_EXEC_H

