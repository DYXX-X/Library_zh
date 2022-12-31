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
#ifndef UTIL_H
#define UTIL_H

#include "nghttp2_config.h"

#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif // HAVE_UNISTD_H
#include <getopt.h>
#ifdef HAVE_NETDB_H
#  include <netdb.h>
#endif // HAVE_NETDB_H

#include <cmath>
#include <cstring>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <memory>
#include <chrono>
#include <map>
#include <random>

#include "url-parser/url_parser.h"

#include "template.h"
#include "network.h"
#include "allocator.h"

namespace nghttp2 {

constexpr auto NGHTTP2_H2_ALPN = StringRef::from_lit("\x2h2");
constexpr auto NGHTTP2_H2 = StringRef::from_lit("h2");

// 我们还提供了额外的HTTP/2协议ALPN协议标识符
// 支持我们的应用程序顺利迁移到final
// h2 ALPN ID。
constexpr auto NGHTTP2_H2_16_ALPN = StringRef::from_lit("\x5h2-16");
constexpr auto NGHTTP2_H2_16 = StringRef::from_lit("h2-16");

constexpr auto NGHTTP2_H2_14_ALPN = StringRef::from_lit("\x5h2-14");
constexpr auto NGHTTP2_H2_14 = StringRef::from_lit("h2-14");

constexpr auto NGHTTP2_H1_1_ALPN = StringRef::from_lit("\x8http/1.1");
constexpr auto NGHTTP2_H1_1 = StringRef::from_lit("http/1.1");

constexpr size_t NGHTTP2_MAX_UINT64_DIGITS = str_size("18446744073709551615");

namespace util {

inline bool is_alpha(const char c) {
  return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

inline bool is_digit(const char c) { return '0' <= c && c <= '9'; }

inline bool is_hex_digit(const char c) {
  return is_digit(c) || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f');
}

// 如果|s|是十六进制字符串，则返回true。
bool is_hex_string(const StringRef &s);

bool in_rfc3986_unreserved_chars(const char c);

bool in_rfc3986_sub_delims(const char c);

// 如果|c|在令牌中，则返回true（HTTP-p1，第3.2.6节）
bool in_token(char c);

bool in_attr_char(char c);

// 返回与十六进制符号|c|对应的整数。如果
// is_hex_digit（c）为false，返回256。
uint32_t hex_to_uint(char c);

std::string percent_encode(const unsigned char *target, size_t len);

std::string percent_encode(const std::string &target);

// URI |s|的百分比编码路径组件。
std::string percent_encode_path(const std::string &s);

template <typename InputIt>
std::string percent_decode(InputIt first, InputIt last) {
  std::string result;
  result.resize(last - first);
  auto p = std::begin(result);
  for (; first != last; ++first) {
    if (*first != '%') {
      *p++ = *first;
      continue;
    }

    if (first + 1 != last && first + 2 != last && is_hex_digit(*(first + 1)) &&
        is_hex_digit(*(first + 2))) {
      *p++ = (hex_to_uint(*(first + 1)) << 4) + hex_to_uint(*(first + 2));
      first += 2;
      continue;
    }

    *p++ = *first;
  }
  result.resize(p - std::begin(result));
  return result;
}

StringRef percent_decode(BlockAllocator &balloc, const StringRef &src);

// 如果字符不在标记或“%”中，则百分比编码|目标|。
StringRef percent_encode_token(BlockAllocator &balloc, const StringRef &target);

// 返回|target|的quotedString版本。目前，此功能
// 只需将“”替换为“\”。
StringRef quote_string(BlockAllocator &balloc, const StringRef &target);

std::string format_hex(const unsigned char *s, size_t len);

template <size_t N> std::string format_hex(const unsigned char (&s)[N]) {
  return format_hex(s, N);
}

template <size_t N> std::string format_hex(const std::array<uint8_t, N> &s) {
  return format_hex(s.data(), s.size());
}

StringRef format_hex(BlockAllocator &balloc, const StringRef &s);

static constexpr char LOWER_XDIGITS[] = "0123456789abcdef";

template <typename OutputIt>
OutputIt format_hex(OutputIt it, const StringRef &s) {
  for (auto cc : s) {
    uint8_t c = cc;
    *it++ = LOWER_XDIGITS[c >> 4];
    *it++ = LOWER_XDIGITS[c & 0xf];
  }

  return it;
}

// decode_hex解码十六进制字符串|s|，返回解码的字节字符串。
// 此函数假定|s|是十六进制字符串，即is_hex_string（s）
// ==真。
StringRef decode_hex(BlockAllocator &balloc, const StringRef &s);

// 以HTTP日期格式（例如，
// 2016年10月10日10:25:58 GMT）。
std::string http_date(time_t t);
// 将给定时间|t|以HTTP日期格式从epoch写入
// 缓冲区由|res|指向。缓冲区必须至少为29字节
// 长的此函数返回超出最后位置的值。
char *http_date(char *res, time_t t);

// 以公共日志格式（例如。，
// 2014年7月3日:00:19:38+0900）
std::string common_log_date(time_t t);
// 将给定时间|t|以公共日志格式从epoch写入
// 缓冲区由|res|指向。缓冲区必须至少为26字节
// 长的此函数返回超出最后位置的值。
char *common_log_date(char *res, time_t t);

// 以ISO 8601格式（例如。，
// 2014-11-15T12:58:24.741+09:00）
std::string iso8601_date(int64_t ms);
// 将给定时间|t|以ISO 8601格式从epoch写入缓冲区
// 由|res|指向。缓冲区长度必须至少为29字节。这
// 函数返回超出最后位置的值。
char *iso8601_date(char *res, int64_t ms);

time_t parse_http_date(const StringRef &s);

// 分析格式为“MMM DD HH:MM:SS YYYY[GMT]”的时间（例如，2月3日
// 00:55:52 2015 GMT），这是OpenSSL专门使用的
// ASN1_TIME_print（）。
time_t parse_openssl_asn1_time_print(const StringRef &s);

char upcase(char c);

inline char lowcase(char c) {
  constexpr static unsigned char tbl[] = {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
      15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
      30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
      45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
      60,  61,  62,  63,  64,  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
      'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
      'z', 91,  92,  93,  94,  95,  96,  97,  98,  99,  100, 101, 102, 103, 104,
      105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
      120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
      135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
      150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
      165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
      180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
      195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
      210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
      225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
      240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
      255,
  };
  return tbl[static_cast<unsigned char>(c)];
}

template <typename InputIterator1, typename InputIterator2>
bool starts_with(InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2, InputIterator2 last2) {
  if (last1 - first1 < last2 - first2) {
    return false;
  }
  return std::equal(first2, last2, first1);
}

template <typename S, typename T> bool starts_with(const S &a, const T &b) {
  return starts_with(a.begin(), a.end(), b.begin(), b.end());
}

struct CaseCmp {
  bool operator()(char lhs, char rhs) const {
    return lowcase(lhs) == lowcase(rhs);
  }
};

template <typename InputIterator1, typename InputIterator2>
bool istarts_with(InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2, InputIterator2 last2) {
  if (last1 - first1 < last2 - first2) {
    return false;
  }
  return std::equal(first2, last2, first1, CaseCmp());
}

template <typename S, typename T> bool istarts_with(const S &a, const T &b) {
  return istarts_with(a.begin(), a.end(), b.begin(), b.end());
}

template <typename T, typename CharT, size_t N>
bool istarts_with_l(const T &a, const CharT (&b)[N]) {
  return istarts_with(a.begin(), a.end(), b, b + N - 1);
}

template <typename InputIterator1, typename InputIterator2>
bool ends_with(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, InputIterator2 last2) {
  if (last1 - first1 < last2 - first2) {
    return false;
  }
  return std::equal(first2, last2, last1 - (last2 - first2));
}

template <typename T, typename S> bool ends_with(const T &a, const S &b) {
  return ends_with(a.begin(), a.end(), b.begin(), b.end());
}

template <typename T, typename CharT, size_t N>
bool ends_with_l(const T &a, const CharT (&b)[N]) {
  return ends_with(a.begin(), a.end(), b, b + N - 1);
}

template <typename InputIterator1, typename InputIterator2>
bool iends_with(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, InputIterator2 last2) {
  if (last1 - first1 < last2 - first2) {
    return false;
  }
  return std::equal(first2, last2, last1 - (last2 - first2), CaseCmp());
}

template <typename T, typename S> bool iends_with(const T &a, const S &b) {
  return iends_with(a.begin(), a.end(), b.begin(), b.end());
}

template <typename T, typename CharT, size_t N>
bool iends_with_l(const T &a, const CharT (&b)[N]) {
  return iends_with(a.begin(), a.end(), b, b + N - 1);
}

template <typename InputIt1, typename InputIt2>
bool strieq(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
  if (std::distance(first1, last1) != std::distance(first2, last2)) {
    return false;
  }

  return std::equal(first1, last1, first2, CaseCmp());
}

template <typename T, typename S> bool strieq(const T &a, const S &b) {
  return strieq(a.begin(), a.end(), b.begin(), b.end());
}

template <typename CharT, typename InputIt, size_t N>
bool strieq_l(const CharT (&a)[N], InputIt b, size_t blen) {
  return strieq(a, a + (N - 1), b, b + blen);
}

template <typename CharT, size_t N, typename T>
bool strieq_l(const CharT (&a)[N], const T &b) {
  return strieq(a, a + (N - 1), b.begin(), b.end());
}

template <typename InputIt1, typename InputIt2>
bool streq(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
  if (std::distance(first1, last1) != std::distance(first2, last2)) {
    return false;
  }
  return std::equal(first1, last1, first2);
}

template <typename T, typename S> bool streq(const T &a, const S &b) {
  return streq(a.begin(), a.end(), b.begin(), b.end());
}

template <typename CharT, typename InputIt, size_t N>
bool streq_l(const CharT (&a)[N], InputIt b, size_t blen) {
  return streq(a, a + (N - 1), b, b + blen);
}

template <typename CharT, size_t N, typename T>
bool streq_l(const CharT (&a)[N], const T &b) {
  return streq(a, a + (N - 1), b.begin(), b.end());
}

// 如果|a|包含|b|，则返回true。如果|a|和|b|都为空，
// 此函数返回false。
template <typename S, typename T> bool strifind(const S &a, const T &b) {
  return std::search(a.begin(), a.end(), b.begin(), b.end(), CaseCmp()) !=
         a.end();
}

template <typename InputIt> void inp_strlower(InputIt first, InputIt last) {
  std::transform(first, last, first, lowcase);
}

// 小写|s|到位。
inline void inp_strlower(std::string &s) {
  inp_strlower(std::begin(s), std::end(s));
}

// 返回带有2个小数的|n|的字符串表示形式。
std::string dtos(double n);

template <typename T> std::string utos(T n) {
  std::string res;
  if (n == 0) {
    res = "0";
    return res;
  }
  size_t nlen = 0;
  for (auto t = n; t; t /= 10, ++nlen)
    ;
  res.resize(nlen);
  for (; n; n /= 10) {
    res[--nlen] = (n % 10) + '0';
  }
  return res;
}

template <typename T, typename OutputIt> OutputIt utos(OutputIt dst, T n) {
  if (n == 0) {
    *dst++ = '0';
    return dst;
  }
  size_t nlen = 0;
  for (auto t = n; t; t /= 10, ++nlen)
    ;
  auto p = dst + nlen;
  auto res = p;
  for (; n; n /= 10) {
    *--p = (n % 10) + '0';
  }
  return res;
}

template <typename T>
StringRef make_string_ref_uint(BlockAllocator &balloc, T n) {
  auto iov = make_byte_ref(balloc, NGHTTP2_MAX_UINT64_DIGITS + 1);
  auto p = iov.base;
  p = util::utos(p, n);
  *p = '\0';
  return StringRef{iov.base, p};
}

template <typename T> std::string utos_unit(T n) {
  char u = 0;
  if (n >= (1 << 30)) {
    u = 'G';
    n /= (1 << 30);
  } else if (n >= (1 << 20)) {
    u = 'M';
    n /= (1 << 20);
  } else if (n >= (1 << 10)) {
    u = 'K';
    n /= (1 << 10);
  }
  if (u == 0) {
    return utos(n);
  }
  return utos(n) + u;
}

// 类似于utos_unit（），但后面跟着2位小数部分。
template <typename T> std::string utos_funit(T n) {
  char u = 0;
  int b = 0;
  if (n >= (1 << 30)) {
    u = 'G';
    b = 30;
  } else if (n >= (1 << 20)) {
    u = 'M';
    b = 20;
  } else if (n >= (1 << 10)) {
    u = 'K';
    b = 10;
  }
  if (b == 0) {
    return utos(n);
  }
  return dtos(static_cast<double>(n) / (1 << b)) + u;
}

extern const char UPPER_XDIGITS[];

template <typename T> std::string utox(T n) {
  std::string res;
  if (n == 0) {
    res = "0";
    return res;
  }
  int i = 0;
  T t = n;
  for (; t; t /= 16, ++i)
    ;
  res.resize(i);
  --i;
  for (; n; --i, n /= 16) {
    res[i] = UPPER_XDIGITS[(n & 0x0f)];
  }
  return res;
}

void to_token68(std::string &base64str);

StringRef to_base64(BlockAllocator &balloc, const StringRef &token68str);

void show_candidates(const char *unkopt, const option *options);

bool has_uri_field(const http_parser_url &u, http_parser_url_fields field);

bool fieldeq(const char *uri1, const http_parser_url &u1, const char *uri2,
             const http_parser_url &u2, http_parser_url_fields field);

bool fieldeq(const char *uri, const http_parser_url &u,
             http_parser_url_fields field, const char *t);

bool fieldeq(const char *uri, const http_parser_url &u,
             http_parser_url_fields field, const StringRef &t);

StringRef get_uri_field(const char *uri, const http_parser_url &u,
                        http_parser_url_fields field);

uint16_t get_default_port(const char *uri, const http_parser_url &u);

bool porteq(const char *uri1, const http_parser_url &u1, const char *uri2,
            const http_parser_url &u2);

void write_uri_field(std::ostream &o, const char *uri, const http_parser_url &u,
                     http_parser_url_fields field);

bool numeric_host(const char *hostname);

bool numeric_host(const char *hostname, int family);

// 返回|addr|的数字地址字符串。如果getnameinfo（）为
// 失败，返回“未知”。
std::string numeric_name(const struct sockaddr *sa, socklen_t salen);

// 返回的数字地址和端口的字符串表示形式
// |地址|。如果地址系列是AF_UNIX，则返回UNIX的路径
// 域套接字。否则，格式类似于＜HOST＞：＜PORT＞。对于
// IPv6地址，地址用方括号（[]）括起来。
std::string to_numeric_addr(const Address *addr);

// 将|port|设置为|addr|。
void set_port(Address &addr, uint16_t port);

// 返回长度为|len|的|data|的ASCII转储。仅ASCII可打印
// 保留字符。其他字符替换为“.”。
std::string ascii_dump(const uint8_t *data, size_t len);

// 返回可执行路径的绝对路径。如果argc==0或|cwd|为
// nullptr，此函数返回nullpter。如果argv[0]以开头
// “/”，此函数返回argv[0]。Oterwise返回cwd+“/”+
// 参数[0]。如果返回非null，则为以null结尾的字符串，并且
// 由malloc动态分配。呼叫者有责任免费
// 它
char *get_exec_path(int argc, char **const argv, const char *cwd);

// 验证路径，使其不包含目录遍历
// 矢量。如果路径安全，则返回true。|路径|必须以开头
// “/”否则返回false。此函数应在
// 执行了百分比解码。
bool check_path(const std::string &path);

// 使用微秒作为
// 单元
int64_t to_time64(const timeval &tv);

// 如果支持HTTP/2协议，则返回true
// 标识符。
bool check_h2_is_selected(const StringRef &proto);

// 如果支持的h2版本之一为
// 存在于长度inlen中。如果h2版本为
// 挑选出来的。
bool select_h2(const unsigned char **out, unsigned char *outlen,
               const unsigned char *in, unsigned int inlen);

// 如果|protolist|中包含的标识符之一为
// 存在于长度inlen中。如果标识符为
// 挑选出来的。
bool select_protocol(const unsigned char **out, unsigned char *outlen,
                     const unsigned char *in, unsigned int inlen,
                     std::vector<std::string> proto_list);

// 返回默认ALPN协议列表，该列表仅包含受支持的
// HTTP/2协议标识符。
std::vector<unsigned char> get_default_alpn();

// 分析|s|中的分隔字符串并返回子字符串数组，
// 由|delim|分隔。子字符串周围的任何空格都是
// 作为子字符串的一部分。
std::vector<std::string> parse_config_str_list(const StringRef &s,
                                               char delim = ',');

// 分析|s|中的分隔字符串并返回|s中的子字符串|
// 由|delim|分隔。子字符串周围的任何空格都是
// 作为子字符串的一部分。
std::vector<StringRef> split_str(const StringRef &s, char delim);

// 以公共日志格式（例如。，
// 2014年7月3日:00:19:38+0900）在|out|指向的缓冲区中。缓冲区
// 必须至少为27个字节，包括终端NULL字节。预期
// |tp|的类型是std:：chrono:：time_point。此函数返回
// StringRef包装|out|指向的缓冲区，此字符串为
// 以NULL结尾。
template <typename T> StringRef format_common_log(char *out, const T &tp) {
  auto t =
      std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
  auto p = common_log_date(out, t.count());
  *p = '\0';
  return StringRef{out, p};
}

// 以ISO 8601格式（例如。，
// 2014-11-15T12:58:24.741+09:00）。
// 预期的|tp|类型为std:：chrono:：time_point
template <typename T> std::string format_iso8601(const T &tp) {
  auto t = std::chrono::duration_cast<std::chrono::milliseconds>(
      tp.time_since_epoch());
  return iso8601_date(t.count());
}

// 以ISO 8601格式（例如。，
// 2014-11-15T12:58:24.741+09:00）中
// 缓冲区由|out|指向。缓冲器必须至少为30字节，
// 包括终端NULL字节。预期的|tp|类型为
// std:：chrono:：time_point。此函数返回StringRef包装
// 由|out|指向的缓冲区，此字符串以NULL结尾。
template <typename T> StringRef format_iso8601(char *out, const T &tp) {
  auto t = std::chrono::duration_cast<std::chrono::milliseconds>(
      tp.time_since_epoch());
  auto p = iso8601_date(out, t.count());
  *p = '\0';
  return StringRef{out, p};
}

// 以HTTP日期格式写入给定时间|tp|（例如，2016年10月10日星期一
// 10： 25:58 GMT）在|out|指向的缓冲区中。缓冲区必须位于
// 至少30个字节，包括终端NULL字节。预期的类型
// |tp|是std:：chrono:：time_point。此函数返回StringRef
// 包装|out|指向的缓冲区，此字符串将终止
// 按NULL。
template <typename T> StringRef format_http_date(char *out, const T &tp) {
  auto t =
      std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
  auto p = http_date(out, t.count());
  *p = '\0';
  return StringRef{out, p};
}

// 将模板参数|Clock|的系统精度返回为
// 类型为|Rep的纳秒值|
template <typename Clock, typename Rep> Rep clock_precision() {
  std::chrono::duration<Rep, std::nano> duration = typename Clock::duration(1);

  return duration.count();
}

int make_socket_closeonexec(int fd);
int make_socket_nonblocking(int fd);
int make_socket_nodelay(int fd);

int create_nonblock_socket(int family);

bool check_socket_connected(int fd);

// 通过检查给定的SO_error返回错误代码（errno）
// |fd|中。如果成功，此函数将返回错误代码，或-1。
// 返回0表示没有错误。
int get_socket_error(int fd);

// 如果|host|是IPv6数字地址（例如：：1），则返回true
bool ipv6_numeric_addr(const char *host);

// 将以NULL结尾的字符串|s|分析为无符号整数并返回
// 解析的整数。此外，如果|s|以“k”、“m”、“g”结尾
// 及其大写字符，将整数乘以1024，1024*
// 1024和1024*1024。如果出现错误，则返回
// -1.
int64_t parse_uint_with_unit(const char *s);
// 以下重载不要求|s|以NULL结尾。
int64_t parse_uint_with_unit(const uint8_t *s, size_t len);
int64_t parse_uint_with_unit(const StringRef &s);

// 将以NULL结尾的字符串|s|分析为无符号整数并返回
// 解析的整数。如果出现错误，则返回-1。
int64_t parse_uint(const char *s);
// 以下重载不要求|s|以NULL结尾。
int64_t parse_uint(const uint8_t *s, size_t len);
int64_t parse_uint(const std::string &s);
int64_t parse_uint(const StringRef &s);

// 将以NULL结尾的字符串|s|分析为无符号整数并返回
// 解析后的整数强制转换为double。如果|s|以“s”结尾
// 解析值的单位是秒。如果|s|以“ms”结尾，则单位
// 是毫秒。同样，它还支持“m”和“h”
// 分钟和小时。如果没有给出
// 单位为秒。此函数返回
// std:：numeric_limits＜double＞：：infinity（），如果发生错误。
double parse_duration_with_unit(const char *s);
// 以下重载不要求|s|以NULL结尾。
double parse_duration_with_unit(const uint8_t *s, size_t len);
double parse_duration_with_unit(const StringRef &s);

// 返回持续时间|t|的字符串表示形式。如果t有
// 分数部分（至少大于或等于1e-3），|t|为
// 乘以1000，并附加单位“ms”。否则，|t|
// 保持原样，并附加“s”。
std::string duration_str(double t);

// 返回持续时间|t|的字符串表示形式。它附加了
// 单位。可用的单位是s、ms和us。
// 使用等于或小于|t|的单位，2
// 随后是小数。
std::string format_duration(const std::chrono::microseconds &u);

// 就像上面一样，但这需要|t|秒。
std::string format_duration(double t);

// 使用给定的|host|和|port|创建“host:port”字符串。如果
// |host|是数字IPv6地址（例如：：1），用“[”括起来
// 和“]”。如果|port|为80或443，则省略端口部分。
StringRef make_http_hostport(BlockAllocator &balloc, const StringRef &host,
                             uint16_t port);

// 就像make_http_hostport（），但不处理80和443
// 特别是。
std::string make_hostport(const StringRef &host, uint16_t port);

StringRef make_hostport(BlockAllocator &balloc, const StringRef &host,
                        uint16_t port);

// 转储|src|，长度|len|，格式类似于`hexdump-C `。
void hexdump(FILE *out, const uint8_t *src, size_t len);

// 按主机字节顺序将2字节无符号整数|n|复制到中的|buf|
// 网络字节顺序。
void put_uint16be(uint8_t *buf, uint16_t n);

// 按主机字节顺序将4字节无符号整数|n|复制到|buf|中
// 网络字节顺序。
void put_uint32be(uint8_t *buf, uint32_t n);

// 检索存储在网络字节|data|中的2字节无符号整数
// 并以主机字节顺序返回。
uint16_t get_uint16(const uint8_t *data);

// 检索存储在网络字节|data|中的4字节无符号整数
// 并以主机字节顺序返回。
uint32_t get_uint32(const uint8_t *data);

// 检索存储在网络字节|data|中的8字节无符号整数
// 并以主机字节顺序返回。
uint64_t get_uint64(const uint8_t *data);

// 读取mime类型文件（请参见/etc/mime.types），并存储扩展名
// ->|res|中的MIME类型映射。如果成功，此函数返回0，
// 或-1。
int read_mime_types(std::map<std::string, std::string> &res,
                    const char *filename);

// 将随机字母和数字字节填充到范围[|first|，|last|）。
// 返回|last|之后的值。
template <typename OutputIt, typename Generator>
OutputIt random_alpha_digit(OutputIt first, OutputIt last, Generator &gen) {
  // 如果我们使用uint8_t而不是char，gcc 6.2.0会通过大喊
  // 从宽字符串初始化的char数组。
  static constexpr char s[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  std::uniform_int_distribution<> dis(0, 26 * 2 + 10 - 1);
  for (; first != last; ++first) {
    *first = s[dis(gen)];
  }
  return first;
}

// 将随机字节填充到范围[|first|，|last|）。
template <typename OutputIt, typename Generator>
void random_bytes(OutputIt first, OutputIt last, Generator &gen) {
  std::uniform_int_distribution<> dis(0, 255);
  std::generate(first, last, [&dis, &gen]() { return dis(gen); });
}

template <typename OutputIterator, typename CharT, size_t N>
OutputIterator copy_lit(OutputIterator it, CharT (&s)[N]) {
  return std::copy_n(s, N - 1, it);
}

// 返回x**y
double int_pow(double x, size_t y);

uint32_t hash32(const StringRef &s);

// 计算|s|的SHA-256，并将其存储在|buf|中。此函数
// 如果成功，则返回0，或-1。
int sha256(uint8_t *buf, const StringRef &s);

// 计算|s|的SHA-1，并将其存储在|buf|中。此函数
// 如果成功，则返回0，或-1。
int sha1(uint8_t *buf, const StringRef &s);

// 从|hostport|返回主机。如果在中找不到主机
// |hostport|，返回空字符串。返回的字符串可能不是
// NULL终止。
StringRef extract_host(const StringRef &hostport);

// split_hostport在|hostport|中拆分主机和端口。不像
// extract_host，去掉了包含主机名的方括号。如果
// 端口不可用，它在第二个
// 一串返回的字符串不能以NULL结尾。在任何
// 错误，它返回一对空字符串。
std::pair<StringRef, StringRef> split_hostport(const StringRef &hostport);

// 返回新的std:：mt19937对象。
std::mt19937 make_mt19937();

// 守护进程调用守护进程（3）。如果定义了__APPLE__，它将实现
// daemon（）使用fork（）。
int daemonize(int nochdir, int noclose);

} // 命名空间util

} // 命名空间nghttp2

#endif // UTIL_H

