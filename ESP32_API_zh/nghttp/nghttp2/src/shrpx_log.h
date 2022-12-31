/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2012 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SHRPX_LOG_H
#define SHRPX_LOG_H

#include "shrpx.h"

#include <sys/types.h>

#include <memory>
#include <vector>
#include <chrono>

#include "shrpx_config.h"
#include "shrpx_log_config.h"
#include "tls.h"
#include "template.h"
#include "util.h"

using namespace nghttp2;

#define ENABLE_LOG 1

#define LOG_ENABLED(SEVERITY) (ENABLE_LOG && shrpx::Log::log_enabled(SEVERITY))

#define LOG(SEVERITY) shrpx::Log(SEVERITY, __FILE__, __LINE__)

// 侦听器日志
#define LLOG(SEVERITY, LISTEN)                                                 \
  (shrpx::Log(SEVERITY, __FILE__, __LINE__) << "[LISTEN:" << LISTEN << "] ")

// Worker日志
#define WLOG(SEVERITY, WORKER)                                                 \
  (shrpx::Log(SEVERITY, __FILE__, __LINE__) << "[WORKER:" << WORKER << "] ")

// ClientHandler日志
#define CLOG(SEVERITY, CLIENT_HANDLER)                                         \
  (shrpx::Log(SEVERITY, __FILE__, __LINE__)                                    \
   << "[CLIENT_HANDLER:" << CLIENT_HANDLER << "] ")

// 上游测井
#define ULOG(SEVERITY, UPSTREAM)                                               \
  (shrpx::Log(SEVERITY, __FILE__, __LINE__) << "[UPSTREAM:" << UPSTREAM        \
                                            << "]"                             \
                                               " ")

// 下游日志
#define DLOG(SEVERITY, DOWNSTREAM)                                             \
  (shrpx::Log(SEVERITY, __FILE__, __LINE__)                                    \
   << "[DOWNSTREAM:" << DOWNSTREAM << "] ")

// 下游连接日志
#define DCLOG(SEVERITY, DCONN)                                                 \
  (shrpx::Log(SEVERITY, __FILE__, __LINE__) << "[DCONN:" << DCONN << "] ")

// 下游HTTP2会话日志
#define SSLOG(SEVERITY, HTTP2)                                                 \
  (shrpx::Log(SEVERITY, __FILE__, __LINE__) << "[DHTTP2:" << HTTP2 << "] ")

// Memcached连接日志
#define MCLOG(SEVERITY, MCONN)                                                 \
  (shrpx::Log(SEVERITY, __FILE__, __LINE__) << "[MCONN:" << MCONN << "] ")

namespace shrpx {

class Downstream;
struct DownstreamAddr;

enum SeverityLevel { INFO, NOTICE, WARN, ERROR, FATAL };

using LogBuffer = std::array<uint8_t, 4_k>;

class Log {
public:
  Log(int severity, const char *filename, int linenum);
  ~Log();
  Log &operator<<(const std::string &s);
  Log &operator<<(const char *s);
  Log &operator<<(const StringRef &s);
  Log &operator<<(const ImmutableString &s);
  Log &operator<<(short n) { return *this << static_cast<long long>(n); }
  Log &operator<<(int n) { return *this << static_cast<long long>(n); }
  Log &operator<<(long n) { return *this << static_cast<long long>(n); }
  Log &operator<<(long long n);
  Log &operator<<(unsigned short n) {
    return *this << static_cast<unsigned long long>(n);
  }
  Log &operator<<(unsigned int n) {
    return *this << static_cast<unsigned long long>(n);
  }
  Log &operator<<(unsigned long n) {
    return *this << static_cast<unsigned long long>(n);
  }
  Log &operator<<(unsigned long long n);
  Log &operator<<(float n) { return *this << static_cast<double>(n); }
  Log &operator<<(double n);
  Log &operator<<(long double n);
  Log &operator<<(bool n);
  Log &operator<<(const void *p);
  template <typename T> Log &operator<<(const std::shared_ptr<T> &ptr) {
    return *this << ptr.get();
  }
  Log &operator<<(void (*func)(Log &log)) {
    func(*this);
    return *this;
  }
  template <typename InputIt> void write_seq(InputIt first, InputIt last) {
    if (full_) {
      return;
    }

    auto d = std::distance(first, last);
    auto n = std::min(wleft(), static_cast<size_t>(d));
    last_ = std::copy(first, first + n, last_);
    update_full();
  }

  template <typename T> void write_hex(T n) {
    if (full_) {
      return;
    }

    if (n == 0) {
      if (wleft() < 4 /* 对于“0x00”*/) {
        full_ = true;
        return;
      }
      *last_++ = '0';
      *last_++ = 'x';
      *last_++ = '0';
      *last_++ = '0';
      update_full();
      return;
    }

    size_t nlen = 0;
    for (auto t = n; t; t >>= 8, ++nlen)
      ;

    nlen *= 2;

    if (wleft() < 2 /* 对于“0x”*/ + nlen) {
      full_ = true;
      return;
    }

    *last_++ = '0';
    *last_++ = 'x';

    last_ += nlen;
    update_full();

    auto p = last_ - 1;
    for (; n; n >>= 8) {
      uint8_t b = n & 0xff;
      *p-- = util::LOWER_XDIGITS[b & 0xf];
      *p-- = util::LOWER_XDIGITS[b >> 4];
    }
  }
  static void set_severity_level(int severity);
  // 按|name|返回严重级别。如果|name|为，则返回-1
  // 未知的
  static int get_severity_level_by_name(const StringRef &name);
  static bool log_enabled(int severity) { return severity >= severity_thres_; }

  enum {
    fmt_dec = 0x00,
    fmt_hex = 0x01,
  };

  void set_flags(int flags) { flags_ = flags; }

private:
  size_t rleft() { return last_ - begin_; }
  size_t wleft() { return end_ - last_; }
  void update_full() { full_ = last_ == end_; }

  LogBuffer &buf_;
  uint8_t *begin_;
  uint8_t *end_;
  uint8_t *last_;
  const char *filename_;
  uint32_t flags_;
  int severity_;
  int linenum_;
  bool full_;
  static int severity_thres_;
};

namespace log {
void hex(Log &log);
void dec(Log &log);
} // 命名空间日志

#define TTY_HTTP_HD (log_config()->errorlog_tty ? "\033[1;34m" : "")
#define TTY_RST (log_config()->errorlog_tty ? "\033[0m" : "")

enum class LogFragmentType {
  NONE,
  LITERAL,
  REMOTE_ADDR,
  TIME_LOCAL,
  TIME_ISO8601,
  REQUEST,
  STATUS,
  BODY_BYTES_SENT,
  HTTP,
  AUTHORITY,
  REMOTE_PORT,
  SERVER_PORT,
  REQUEST_TIME,
  PID,
  ALPN,
  TLS_CIPHER,
  SSL_CIPHER = TLS_CIPHER,
  TLS_PROTOCOL,
  SSL_PROTOCOL = TLS_PROTOCOL,
  TLS_SESSION_ID,
  SSL_SESSION_ID = TLS_SESSION_ID,
  TLS_SESSION_REUSED,
  SSL_SESSION_REUSED = TLS_SESSION_REUSED,
  TLS_SNI,
  TLS_CLIENT_FINGERPRINT_SHA1,
  TLS_CLIENT_FINGERPRINT_SHA256,
  TLS_CLIENT_ISSUER_NAME,
  TLS_CLIENT_SERIAL,
  TLS_CLIENT_SUBJECT_NAME,
  BACKEND_HOST,
  BACKEND_PORT,
};

struct LogFragment {
  LogFragment(LogFragmentType type, StringRef value = StringRef::from_lit(""))
      : type(type), value(std::move(value)) {}
  LogFragmentType type;
  StringRef value;
};

struct LogSpec {
  Downstream *downstream;
  StringRef remote_addr;
  StringRef alpn;
  StringRef sni;
  SSL *ssl;
  std::chrono::high_resolution_clock::time_point request_end_time;
  StringRef remote_port;
  uint16_t server_port;
  pid_t pid;
};

void upstream_accesslog(const std::vector<LogFragment> &lf,
                        const LogSpec &lgsp);

int reopen_log_files(const LoggingConfig &loggingconf);

// 当进程的pid为|pid|且存在状态为
// |rstatus|已退出。|msg|在日志消息前面。
void log_chld(pid_t pid, int rstatus, const char *msg);

void redirect_stderr_to_errorlog(const LoggingConfig &loggingconf);

// 生成stderr（以及将来可能的stdout）的内部副本，
// 然后将其用作指向/dev/stderr或/proc/self/fd/2的指针
void store_original_fds();

// 还原与copy_original_fds一起存储的原始stderr
// 仅在execv之前使用
void restore_original_fds();

// 关闭open_log_file返回的|fd|（见下文）
// 并将其设置为-1。在|fd|指向stdout或
// stderr，或为-1，则描述符未关闭（但仍设置为-1）。
void close_log_file(int &fd);

// 打开启用O_APPEND的|路径|。如果文件不存在，则为
// 首先创建。此函数返回引用
// 如果成功，则打开文件，或-1。
int open_log_file(const char *path);

} // 命名空间shrpx

#endif // SHRPX_LOG_H

