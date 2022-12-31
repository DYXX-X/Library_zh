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
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "nghttp2_config.h"

#ifndef _WIN32
#  include <sys/uio.h>
#endif // !_WIN32

#include <cassert>
#include <utility>

#include "template.h"

namespace nghttp2 {

struct MemBlock {
  // 下一个MemBlock将它们链接起来。这是用来记账的
  // 目的是稍后释放他们。
  MemBlock *next;
  // begin是指向缓冲区开始的指针。最后是
  // 下一次写入的位置。结束是指
  // 缓冲器
  uint8_t *begin, *last, *end;
};

// BlockAllocator一次分配具有给定大小的内存块，并且
// 当请求分配时，从中删除区域。如果
// 请求的大小大于给定的阈值（加上较小的内部
// 开销），它将按需分配在不同的缓冲区中。
// |isolation_threshold|必须小于或等于
// |block_size |。
struct BlockAllocator {
  BlockAllocator(size_t block_size, size_t isolation_threshold)
      : retain(nullptr),
        head(nullptr),
        block_size(block_size),
        isolation_threshold(std::min(block_size, isolation_threshold)) {
    assert(isolation_threshold <= block_size);
  }

  ~BlockAllocator() { reset(); }

  BlockAllocator(BlockAllocator &&other) noexcept
      : retain{std::exchange(other.retain, nullptr)},
        head{std::exchange(other.head, nullptr)},
        block_size(other.block_size),
        isolation_threshold(other.isolation_threshold) {}

  BlockAllocator &operator=(BlockAllocator &&other) noexcept {
    reset();

    retain = std::exchange(other.retain, nullptr);
    head = std::exchange(other.head, nullptr);
    block_size = other.block_size;
    isolation_threshold = other.isolation_threshold;

    return *this;
  }

  BlockAllocator(const BlockAllocator &) = delete;
  BlockAllocator &operator=(const BlockAllocator &) = delete;

  void reset() {
    for (auto mb = retain; mb;) {
      auto next = mb->next;
      delete[] reinterpret_cast<uint8_t *>(mb);
      mb = next;
    }

    retain = nullptr;
    head = nullptr;
  }

  MemBlock *alloc_mem_block(size_t size) {
    auto block = new uint8_t[sizeof(MemBlock) + size];
    auto mb = reinterpret_cast<MemBlock *>(block);

    mb->next = retain;
    mb->begin = mb->last = block + sizeof(MemBlock);
    mb->end = mb->begin + size;
    retain = mb;
    return mb;
  }

  void *alloc(size_t size) {
    if (size + sizeof(size_t) >= isolation_threshold) {
      auto len = std::max(static_cast<size_t>(16), size);
      // 我们将在size_t字段中存储分配的大小。
      auto mb = alloc_mem_block(len + sizeof(size_t));
      auto sp = reinterpret_cast<size_t *>(mb->begin);
      *sp = len;
      mb->last = mb->end;
      return mb->begin + sizeof(size_t);
    }

    if (!head ||
        head->end - head->last < static_cast<ssize_t>(size + sizeof(size_t))) {
      head = alloc_mem_block(block_size);
    }

    // 我们将在size_t字段中存储分配的大小。
    auto res = head->last + sizeof(size_t);
    auto sp = reinterpret_cast<size_t *>(head->last);
    *sp = size;

    head->last = reinterpret_cast<uint8_t *>(
        (reinterpret_cast<intptr_t>(res + size) + 0xf) & ~0xf);

    return res;
  }

  // 返回|ptr|指向的内存分配大小。我们假设
  // |ptr|是从alloc（）或realloc（）返回的。
  size_t get_alloc_length(void *ptr) {
    return *reinterpret_cast<size_t *>(static_cast<uint8_t *>(ptr) -
                                       sizeof(size_t));
  }

  // 分配至少|size|字节的内存。如果|ptr|为nullptr，
  // 这相当于alloc（大小）。如果|ptr|不是nullptr，
  // 获取|ptr|的分配大小，假设|ptr|=
  // 从alloc（）或realloc（）返回。如果分配的大小为
  // 大于或等于size，则返回|ptr|。否则
  // 至少分配|size|字节的内存
  // ptr|指向的内容被复制到新分配的内存中。
  void *realloc(void *ptr, size_t size) {
    if (!ptr) {
      return alloc(size);
    }
    auto alloclen = get_alloc_length(ptr);
    auto p = reinterpret_cast<uint8_t *>(ptr);
    if (size <= alloclen) {
      return ptr;
    }

    auto nalloclen = std::max(size + 1, alloclen * 2);

    auto res = alloc(nalloclen);
    std::copy_n(p, alloclen, static_cast<uint8_t *>(res));

    return res;
  }

  // 这将保存实时内存块，以在dtor中释放它们。
  MemBlock *retain;
  // 要使用的当前内存块。
  MemBlock *head;
  // 单个存储块的大小
  size_t block_size;
  // 如果分配大于或等于隔离阈值字节
  // 请求，分配专用块。
  size_t isolation_threshold;
};

// 复制|src|。生成的字符串将是
// NULL终止。
template <typename BlockAllocator>
StringRef make_string_ref(BlockAllocator &alloc, const StringRef &src) {
  auto dst = static_cast<uint8_t *>(alloc.alloc(src.size() + 1));
  auto p = dst;
  p = std::copy(std::begin(src), std::end(src), p);
  *p = '\0';
  return StringRef{dst, src.size()};
}

// concat_string_ref中使用的私有函数。这是基地
// concat_string_ref_count（）函数。
inline size_t concat_string_ref_count(size_t acc) { return acc; }

// concat_string_ref中使用的私有函数。此函数计数
// 给定参数的长度总和。计算长度为
// 累积并传递给下一个函数。
template <typename... Args>
size_t concat_string_ref_count(size_t acc, const StringRef &value,
                               Args &&... args) {
  return concat_string_ref_count(acc + value.size(),
                                 std::forward<Args>(args)...);
}

// concat_string_ref中使用的私有函数。这是基地
// concat_string_ref_copy（）的函数。
inline uint8_t *concat_string_ref_copy(uint8_t *p) { return p; }

// concat_string_ref中使用的私有函数。此功能复制
// 将给定字符串转换为|p||p|增加复制的长度，
// 然后返回。最后，返回值指向位置1
// 超过写入的最后一个字节。
template <typename... Args>
uint8_t *concat_string_ref_copy(uint8_t *p, const StringRef &value,
                                Args &&... args) {
  p = std::copy(std::begin(value), std::end(value), p);
  return concat_string_ref_copy(p, std::forward<Args>(args)...);
}

// 返回字符串，该字符串是
// 给出命令。结果字符串将以NULL结尾。
template <typename BlockAllocator, typename... Args>
StringRef concat_string_ref(BlockAllocator &alloc, Args &&... args) {
  size_t len = concat_string_ref_count(0, std::forward<Args>(args)...);
  auto dst = static_cast<uint8_t *>(alloc.alloc(len + 1));
  auto p = dst;
  p = concat_string_ref_copy(p, std::forward<Args>(args)...);
  *p = '\0';
  return StringRef{dst, len};
}

// 返回字符串，该字符串是|value|和|args的串联|
// 按照给定的顺序。结果字符串将以NULL结尾。
// 此函数假定指针值为。c_str（）是
// 从alloc。alloc（）或alloc。realloc（），并尝试使用
// 未使用的内存区域。如果值为空，
// 然后只需调用concat_string_ref（）。
template <typename BlockAllocator, typename... Args>
StringRef realloc_concat_string_ref(BlockAllocator &alloc,
                                    const StringRef &value, Args &&... args) {
  if (value.empty()) {
    return concat_string_ref(alloc, std::forward<Args>(args)...);
  }

  auto len =
      value.size() + concat_string_ref_count(0, std::forward<Args>(args)...);
  auto dst = static_cast<uint8_t *>(
      alloc.realloc(const_cast<uint8_t *>(value.byte()), len + 1));
  auto p = dst + value.size();
  p = concat_string_ref_copy(p, std::forward<Args>(args)...);
  *p = '\0';

  return StringRef{dst, len};
}

struct ByteRef {
  // 指向缓冲区开头的指针。
  uint8_t *base;
  // 缓冲区的长度。
  size_t len;
};

// 生成具有给定大小的缓冲区。生成的字节字符串可能
// 不能以NULL结尾。
template <typename BlockAllocator>
ByteRef make_byte_ref(BlockAllocator &alloc, size_t size) {
  auto dst = static_cast<uint8_t *>(alloc.alloc(size));
  return {dst, size};
}

} // 命名空间nghttp2

#endif // ALLOCATOR_H

