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
// 我们基于原始代码编写了此代码，该代码具有
// 以下许可证：
//
// io_服务_工具.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// 版权所有（c）2003-2013 Christopher M.Kohlhoff（chris at Kohlhoff.com）
//
// 根据Boost软件许可证1.0版发行。（请参阅随附的
// 文件LICENSE_1_0.txt或复制到http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_IO_SERVICE_POOL_H
#define ASIO_IO_SERVICE_POOL_H

#include "nghttp2_config.h"

#include <vector>
#include <memory>
#include <future>

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#include <nghttp2/asio_http2.h>

namespace nghttp2 {

namespace asio_http2 {

///io_service对象池。
class io_service_pool : private boost::noncopyable {
public:
  ///构造io_service池。
  explicit io_service_pool(std::size_t pool_size);

  ///运行池中的所有io_service对象。
  void run(bool asynchronous = false);

  ///停止池中的所有io_service对象。
  void force_stop();

  ///销毁所有工作对象以发出工作结束的信号
  void stop();

  ///加入池中的所有io_service对象。
  void join();

  ///获取要使用的io_service。
  boost::asio::io_service &get_io_service();

  ///访问所有io_service对象。
  const std::vector<std::shared_ptr<boost::asio::io_service>> &
  io_services() const;

private:
  ///io_services池。
  std::vector<std::shared_ptr<boost::asio::io_service>> io_services_;

  ///保持io_services运行的工作。
  std::vector<std::shared_ptr<boost::asio::io_service::work>> work_;

  ///用于连接的下一个io_service。
  std::size_t next_io_service_;

  ///转发到所有io_service对象
  std::vector<std::future<std::size_t>> futures_;
};

} // 命名空间asio_http2

} // 命名空间nghttp2

#endif // ASIO_IO_SERVICE_POOL_H

