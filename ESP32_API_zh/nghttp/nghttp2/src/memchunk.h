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
#ifndef MEMCHUNK_H
#define MEMCHUNK_H

#include "nghttp2_config.h"

#include <limits.h>
#ifdef _WIN32
/* 分散/聚集I/O的结构。*/
struct iovec {
  void *iov_base; /* 指向数据的指针。*/
  size_t iov_len; /* 数据长度。*/
};
#else // !_WIN32
#  include <sys/uio.h>
#endif // !_WIN32

#include <cassert>
#include <cstring>
#include <memory>
#include <array>
#include <algorithm>
#include <string>
#include <utility>

#include "template.h"

namespace nghttp2 {

#define DEFAULT_WR_IOVCNT 16

#if defined(IOV_MAX) && IOV_MAX < DEFAULT_WR_IOVCNT
#  define MAX_WR_IOVCNT IOV_MAX
#else // !已定义（IOV_MAX）||IOV_MAX>=DEFAULT_WR_IOVCNT
#  define MAX_WR_IOVCNT DEFAULT_WR_IOVCNT
#endif // !已定义（IOV_MAX）||IOV_MAX>=DEFAULT_WR_IOVCNT

template <size_t N> struct Memchunk {
  Memchunk(Memchunk *next_chunk)
      : pos(std::begin(buf)), last(pos), knext(next_chunk), next(nullptr) {}
  size_t len() const { return last - pos; }
  size_t left() const { return std::end(buf) - last; }
  void reset() { pos = last = std::begin(buf); }
  std::array<uint8_t, N> buf;
  uint8_t *pos, *last;
  Memchunk *knext;
  Memchunk *next;
  static const size_t size = N;
};

template <typename T> struct Pool {
  Pool() : pool(nullptr), freelist(nullptr), poolsize(0) {}
  ~Pool() { clear(); }
  T *get() {
    if (freelist) {
      auto m = freelist;
      freelist = freelist->next;
      m->next = nullptr;
      m->reset();
      return m;
    }

    pool = new T{pool};
    poolsize += T::size;
    return pool;
  }
  void recycle(T *m) {
    m->next = freelist;
    freelist = m;
  }
  void clear() {
    freelist = nullptr;
    for (auto p = pool; p;) {
      auto knext = p->knext;
      delete p;
      p = knext;
    }
    pool = nullptr;
    poolsize = 0;
  }
  using value_type = T;
  T *pool;
  T *freelist;
  size_t poolsize;
};

template <typename Memchunk> struct Memchunks {
  Memchunks(Pool<Memchunk> *pool)
      : pool(pool), head(nullptr), tail(nullptr), len(0) {}
  Memchunks(const Memchunks &) = delete;
  Memchunks(Memchunks &&other) noexcept
      : pool{other.pool}, // 保留其他.pool
        head{std::exchange(other.head, nullptr)},
        tail{std::exchange(other.tail, nullptr)},
        len{std::exchange(other.len, 0)} {}
  Memchunks &operator=(const Memchunks &) = delete;
  Memchunks &operator=(Memchunks &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    reset();

    pool = other.pool;
    head = std::exchange(other.head, nullptr);
    tail = std::exchange(other.tail, nullptr);
    len = std::exchange(other.len, 0);

    return *this;
  }
  ~Memchunks() {
    if (!pool) {
      return;
    }
    for (auto m = head; m;) {
      auto next = m->next;
      pool->recycle(m);
      m = next;
    }
  }
  size_t append(char c) {
    if (!tail) {
      head = tail = pool->get();
    } else if (tail->left() == 0) {
      tail->next = pool->get();
      tail = tail->next;
    }
    *tail->last++ = c;
    ++len;
    return 1;
  }
  size_t append(const void *src, size_t count) {
    if (count == 0) {
      return 0;
    }

    auto first = static_cast<const uint8_t *>(src);
    auto last = first + count;

    if (!tail) {
      head = tail = pool->get();
    }

    for (;;) {
      auto n = std::min(static_cast<size_t>(last - first), tail->left());
      tail->last = std::copy_n(first, n, tail->last);
      first += n;
      len += n;
      if (first == last) {
        break;
      }

      tail->next = pool->get();
      tail = tail->next;
    }

    return count;
  }
  template <size_t N> size_t append(const char (&s)[N]) {
    return append(s, N - 1);
  }
  size_t append(const std::string &s) { return append(s.c_str(), s.size()); }
  size_t append(const StringRef &s) { return append(s.c_str(), s.size()); }
  size_t append(const ImmutableString &s) {
    return append(s.c_str(), s.size());
  }
  size_t copy(Memchunks &dest) {
    auto m = head;
    while (m) {
      dest.append(m->pos, m->len());
      m = m->next;
    }
    return len;
  }
  size_t remove(void *dest, size_t count) {
    if (!tail || count == 0) {
      return 0;
    }

    auto first = static_cast<uint8_t *>(dest);
    auto last = first + count;

    auto m = head;

    while (m) {
      auto next = m->next;
      auto n = std::min(static_cast<size_t>(last - first), m->len());

      assert(m->len());
      first = std::copy_n(m->pos, n, first);
      m->pos += n;
      len -= n;
      if (m->len() > 0) {
        break;
      }
      pool->recycle(m);
      m = next;
    }
    head = m;
    if (head == nullptr) {
      tail = nullptr;
    }

    return first - static_cast<uint8_t *>(dest);
  }
  size_t remove(Memchunks &dest, size_t count) {
    if (!tail || count == 0) {
      return 0;
    }

    auto left = count;
    auto m = head;

    while (m) {
      auto next = m->next;
      auto n = std::min(left, m->len());

      assert(m->len());
      dest.append(m->pos, n);
      m->pos += n;
      len -= n;
      left -= n;
      if (m->len() > 0) {
        break;
      }
      pool->recycle(m);
      m = next;
    }
    head = m;
    if (head == nullptr) {
      tail = nullptr;
    }

    return count - left;
  }
  size_t remove(Memchunks &dest) {
    assert(pool == dest.pool);

    if (head == nullptr) {
      return 0;
    }

    auto n = len;

    if (dest.tail == nullptr) {
      dest.head = head;
    } else {
      dest.tail->next = head;
    }

    dest.tail = tail;
    dest.len += len;

    head = tail = nullptr;
    len = 0;

    return n;
  }
  size_t drain(size_t count) {
    auto ndata = count;
    auto m = head;
    while (m) {
      auto next = m->next;
      auto n = std::min(count, m->len());
      m->pos += n;
      count -= n;
      len -= n;
      if (m->len() > 0) {
        break;
      }

      pool->recycle(m);
      m = next;
    }
    head = m;
    if (head == nullptr) {
      tail = nullptr;
    }
    return ndata - count;
  }
  int riovec(struct iovec *iov, int iovcnt) const {
    if (!head) {
      return 0;
    }
    auto m = head;
    int i;
    for (i = 0; i < iovcnt && m; ++i, m = m->next) {
      iov[i].iov_base = m->pos;
      iov[i].iov_len = m->len();
    }
    return i;
  }
  size_t rleft() const { return len; }
  void reset() {
    for (auto m = head; m;) {
      auto next = m->next;
      pool->recycle(m);
      m = next;
    }
    len = 0;
    head = tail = nullptr;
  }

  Pool<Memchunk> *pool;
  Memchunk *head, *tail;
  size_t len;
};

// 包装Memchunk以提供“偷看”功能。
template <typename Memchunk> struct PeekMemchunks {
  PeekMemchunks(Pool<Memchunk> *pool)
      : memchunks(pool),
        cur(nullptr),
        cur_pos(nullptr),
        cur_last(nullptr),
        len(0),
        peeking(true) {}
  PeekMemchunks(const PeekMemchunks &) = delete;
  PeekMemchunks(PeekMemchunks &&other) noexcept
      : memchunks{std::move(other.memchunks)},
        cur{std::exchange(other.cur, nullptr)},
        cur_pos{std::exchange(other.cur_pos, nullptr)},
        cur_last{std::exchange(other.cur_last, nullptr)},
        len{std::exchange(other.len, 0)},
        peeking{std::exchange(other.peeking, true)} {}
  PeekMemchunks &operator=(const PeekMemchunks &) = delete;
  PeekMemchunks &operator=(PeekMemchunks &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    memchunks = std::move(other.memchunks);
    cur = std::exchange(other.cur, nullptr);
    cur_pos = std::exchange(other.cur_pos, nullptr);
    cur_last = std::exchange(other.cur_last, nullptr);
    len = std::exchange(other.len, 0);
    peeking = std::exchange(other.peeking, true);

    return *this;
  }
  size_t append(const void *src, size_t count) {
    count = memchunks.append(src, count);
    len += count;
    return count;
  }
  size_t remove(void *dest, size_t count) {
    if (!peeking) {
      count = memchunks.remove(dest, count);
      len -= count;
      return count;
    }

    if (count == 0 || len == 0) {
      return 0;
    }

    if (!cur) {
      cur = memchunks.head;
      cur_pos = cur->pos;
    }

    // cur_last可以在追加中更新
    cur_last = cur->last;

    if (cur_pos == cur_last) {
      assert(cur->next);
      cur = cur->next;
    }

    auto first = static_cast<uint8_t *>(dest);
    auto last = first + count;

    for (;;) {
      auto n = std::min(last - first, cur_last - cur_pos);

      first = std::copy_n(cur_pos, n, first);
      cur_pos += n;
      len -= n;

      if (first == last) {
        break;
      }
      assert(cur_pos == cur_last);
      if (!cur->next) {
        break;
      }
      cur = cur->next;
      cur_pos = cur->pos;
      cur_last = cur->last;
    }
    return first - static_cast<uint8_t *>(dest);
  }
  size_t rleft() const { return len; }
  size_t rleft_buffered() const { return memchunks.rleft(); }
  void disable_peek(bool drain) {
    if (!peeking) {
      return;
    }
    if (drain) {
      auto n = rleft_buffered() - rleft();
      memchunks.drain(n);
      assert(len == memchunks.rleft());
    } else {
      len = memchunks.rleft();
    }
    cur = nullptr;
    cur_pos = cur_last = nullptr;
    peeking = false;
  }
  void reset() {
    memchunks.reset();
    cur = nullptr;
    cur_pos = cur_last = nullptr;
    len = 0;
    peeking = true;
  }
  Memchunks<Memchunk> memchunks;
  // 指向当前正在读/写的Memchunk的指针。
  Memchunk *cur;
  // cur内的区域，我们已处理为cur_pos。
  uint8_t *cur_pos, *cur_last;
  // 这是我们未处理的长度。伦<=
  // 内存块。rleft（）必须保持。
  size_t len;
  // 如果启用了偷看，则为true。最初这是真的。
  bool peeking;
};

using Memchunk16K = Memchunk<16_k>;
using MemchunkPool = Pool<Memchunk16K>;
using DefaultMemchunks = Memchunks<Memchunk16K>;
using DefaultPeekMemchunks = PeekMemchunks<Memchunk16K>;

inline int limit_iovec(struct iovec *iov, int iovcnt, size_t max) {
  if (max == 0) {
    return 0;
  }
  for (int i = 0; i < iovcnt; ++i) {
    auto d = std::min(max, iov[i].iov_len);
    iov[i].iov_len = d;
    max -= d;
    if (max == 0) {
      return i + 1;
    }
  }
  return iovcnt;
}

// MemchunkBuffer与Buffer类似，但它使用池Memchunk
// 用于其底层缓冲区。
template <typename Memchunk> struct MemchunkBuffer {
  MemchunkBuffer(Pool<Memchunk> *pool) : pool(pool), chunk(nullptr) {}
  MemchunkBuffer(const MemchunkBuffer &) = delete;
  MemchunkBuffer(MemchunkBuffer &&other) noexcept
      : pool(other.pool), chunk(other.chunk) {
    other.chunk = nullptr;
  }
  MemchunkBuffer &operator=(const MemchunkBuffer &) = delete;
  MemchunkBuffer &operator=(MemchunkBuffer &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    pool = other.pool;
    chunk = other.chunk;

    other.chunk = nullptr;

    return *this;
  }

  ~MemchunkBuffer() {
    if (!pool || !chunk) {
      return;
    }
    pool->recycle(chunk);
  }

  // 确保分配了基础缓冲区。
  void ensure_chunk() {
    if (chunk) {
      return;
    }
    chunk = pool->get();
  }

  // 释放基础缓冲区。
  void release_chunk() {
    if (!chunk) {
      return;
    }
    pool->recycle(chunk);
    chunk = nullptr;
  }

  // 如果分配了基础缓冲区，则返回true。
  bool chunk_avail() const { return chunk != nullptr; }

  // 必须在基础缓冲区
  // allocated（使用ensure_chunk）。

  // MemchunkBuffer提供了与Buffer相同的接口函数。
  // 由于我们有chunk作为成员变量，pos和last是
  // 实现为包装器函数。

  uint8_t *pos() const { return chunk->pos; }
  uint8_t *last() const { return chunk->last; }

  size_t rleft() const { return chunk->len(); }
  size_t wleft() const { return chunk->left(); }
  size_t write(const void *src, size_t count) {
    count = std::min(count, wleft());
    auto p = static_cast<const uint8_t *>(src);
    chunk->last = std::copy_n(p, count, chunk->last);
    return count;
  }
  size_t write(size_t count) {
    count = std::min(count, wleft());
    chunk->last += count;
    return count;
  }
  size_t drain(size_t count) {
    count = std::min(count, rleft());
    chunk->pos += count;
    return count;
  }
  size_t drain_reset(size_t count) {
    count = std::min(count, rleft());
    std::copy(chunk->pos + count, chunk->last, std::begin(chunk->buf));
    chunk->last = std::begin(chunk->buf) + (chunk->last - (chunk->pos + count));
    chunk->pos = std::begin(chunk->buf);
    return count;
  }
  void reset() { chunk->reset(); }
  uint8_t *begin() { return std::begin(chunk->buf); }
  uint8_t &operator[](size_t n) { return chunk->buf[n]; }
  const uint8_t &operator[](size_t n) const { return chunk->buf[n]; }

  Pool<Memchunk> *pool;
  Memchunk *chunk;
};

using DefaultMemchunkBuffer = MemchunkBuffer<Memchunk16K>;

} // 命名空间nghttp2

#endif // MEMCHUNK_H

