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
#ifndef BUFFER_H
#define BUFFER_H

#include "nghttp2_config.h"

#include <cstring>
#include <algorithm>
#include <array>

namespace nghttp2 {

template <size_t N> struct Buffer {
  Buffer() : pos(std::begin(buf)), last(pos) {}
  // 返回要读取的字节数。
  size_t rleft() const { return last - pos; }
  // 返回此缓冲区可以存储的字节数。
  size_t wleft() const { return std::end(buf) - last; }
  // 从所指向的缓冲区中最多写入min（wleft（），|count|）字节
  // |src|。返回写入的字节数。
  size_t write(const void *src, size_t count) {
    count = std::min(count, wleft());
    auto p = static_cast<const uint8_t *>(src);
    last = std::copy_n(p, count, last);
    return count;
  }
  size_t write(size_t count) {
    count = std::min(count, wleft());
    last += count;
    return count;
  }
  // 从缓冲区开始排出最小（rleft（），|count|）字节。
  size_t drain(size_t count) {
    count = std::min(count, rleft());
    pos += count;
    return count;
  }
  size_t drain_reset(size_t count) {
    count = std::min(count, rleft());
    std::copy(pos + count, last, std::begin(buf));
    last = std::begin(buf) + (last - (pos + count));
    pos = std::begin(buf);
    return count;
  }
  void reset() { pos = last = std::begin(buf); }
  uint8_t *begin() { return std::begin(buf); }
  uint8_t &operator[](size_t n) { return buf[n]; }
  const uint8_t &operator[](size_t n) const { return buf[n]; }
  std::array<uint8_t, N> buf;
  uint8_t *pos, *last;
};

} // 命名空间nghttp2

#endif // BUFFER_H

