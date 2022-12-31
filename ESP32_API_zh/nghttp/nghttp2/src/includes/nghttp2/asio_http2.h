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
#ifndef ASIO_HTTP2_H
#define ASIO_HTTP2_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <map>

#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <nghttp2/nghttp2.h>

namespace nghttp2 {

namespace asio_http2 {

struct header_value {
  // 标题字段值
  std::string value;
  // 如果头字段值是敏感信息，例如
  // 授权信息或短长度机密cookie。如果
  // 真的，这些头字段不会被HPACK索引（但仍然
  // huffman编码），这导致较小的压缩。
  bool sensitive;
};

// 标题字段。标头字段名称必须小写。
using header_map = std::multimap<std::string, header_value>;

const boost::system::error_category &nghttp2_category() noexcept;

struct uri_ref {
  std::string scheme;
  std::string host;
  // 解码百分比编码后的格式
  std::string path;
  // 原始路径，百分比编码
  std::string raw_path;
  // 原始查询，百分比编码
  std::string raw_query;
  std::string fragment;
};

// 数据到达时的回调函数。EOF表示为
// 将0传递给第二个参数。
typedef std::function<void(const uint8_t *, std::size_t)> data_cb;
typedef std::function<void(void)> void_cb;
typedef std::function<void(const boost::system::error_code &ec)> error_cb;
// 请求和响应完成时的回调函数。这个
// 参数表示关闭的原因。
typedef std::function<void(uint32_t)> close_cb;

// 用于生成响应体的回调函数。此函数具有
// 与nghttp2_data_source_read_callback的语义相同。只是来源
// 并且移除user_ data参数。
//
// 基本上，最多向|data|写入|len|字节，并返回
// 写入的字节数。如果没有要发送的数据，请设置
// NGHTTP2_DATA_FLAG_EOF到*数据标志（例如，*数据标志|=
// NGHTTP2_DATA_FLAG_EOF）。如果仍有数据要发送，但
// 当前不可用，请返回NGHTTP2_ERR_DEFERRED。万一
// 必须关闭请求/响应，返回
// NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE.
typedef std::function<ssize_t(uint8_t *buf, std::size_t len,
                              uint32_t *data_flags)>
    generator_cb;

// 方便的函数创建函数以读取由
// |路径|。这可以传递给response:：end（）。
generator_cb file_generator(const std::string &path);

// 类似于file_generator（conststd:：string&），但它需要打开的文件
// 描述符。返回时将关闭传递的描述符
// 函数对象被破坏。
generator_cb file_generator_from_fd(int fd);

// 验证路径，使其不包含目录遍历
// 矢量。如果路径安全，则返回true。|路径|必须以开头
// “/”否则返回false。此函数应在
// 执行了百分比解码。
bool check_path(const std::string &path);

// 对字符串|s|执行百分比解码。
std::string percent_decode(const std::string &s);

// 返回当前posix时间|t|的HTTP日期表示形式。
std::string http_date(int64_t t);

// 解析|uri |并提取方案、主机和服务。服务是
// URI的端口组件（例如“8443”）（如果可用），否则为
// 方案（例如“https”）。
boost::system::error_code host_service_from_uri(boost::system::error_code &ec,
                                                std::string &scheme,
                                                std::string &host,
                                                std::string &service,
                                                const std::string &uri);

enum nghttp2_asio_error {
  NGHTTP2_ASIO_ERR_NO_ERROR = 0,
  NGHTTP2_ASIO_ERR_TLS_NO_APP_PROTO_NEGOTIATED = 1,
};

} // 命名空间asio_http2

} // 命名空间nghttp2

namespace boost {

namespace system {

template <> struct is_error_code_enum<nghttp2_error> {
  BOOST_STATIC_CONSTANT(bool, value = true);
};

template <> struct is_error_code_enum<nghttp2::asio_http2::nghttp2_asio_error> {
  BOOST_STATIC_CONSTANT(bool, value = true);
};

} // 命名空间系统

} // 命名空间提升

#endif // ASIO_HTTP2_H

