/*
 * nghttp2-HTTP/2 C库
 *
 * 版权所有（c）2013 Tatsuhiro Tsujikawa
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef HTTP2_H
#define HTTP2_H

#include "nghttp2_config.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <array>

#include <nghttp2/nghttp2.h>

#include "url-parser/url_parser.h"

#include "util.h"
#include "memchunk.h"
#include "template.h"
#include "allocator.h"
#include "base64.h"

namespace nghttp2 {

struct Header {
  Header(std::string name, std::string value, bool no_index = false,
         int32_t token = -1)
      : name(std::move(name)),
        value(std::move(value)),
        token(token),
        no_index(no_index) {}

  Header() : token(-1), no_index(false) {}

  bool operator==(const Header &other) const {
    return name == other.name && value == other.value;
  }

  bool operator<(const Header &rhs) const {
    return name < rhs.name || (name == rhs.name && value < rhs.value);
  }

  std::string name;
  std::string value;
  int32_t token;
  bool no_index;
};

struct HeaderRef {
  HeaderRef(const StringRef &name, const StringRef &value,
            bool no_index = false, int32_t token = -1)
      : name(name), value(value), token(token), no_index(no_index) {}

  HeaderRef() : token(-1), no_index(false) {}

  bool operator==(const HeaderRef &other) const {
    return name == other.name && value == other.value;
  }

  bool operator<(const HeaderRef &rhs) const {
    return name < rhs.name || (name == rhs.name && value < rhs.value);
  }

  StringRef name;
  StringRef value;
  int32_t token;
  bool no_index;
};

using Headers = std::vector<Header>;
using HeaderRefs = std::vector<HeaderRef>;

namespace http2 {

// 返回给定|状态代码|的原因短语。如果没有
// 给定代码的已知原因短语返回空字符串。
StringRef get_reason_phrase(unsigned int status_code);

// 返回|status_code|的字符串版本。（例如，“404”）
StringRef stringify_status(BlockAllocator &balloc, unsigned int status_code);

void capitalize(DefaultMemchunks *buf, const StringRef &s);

// 如果|value|为LWS，则返回true
bool lws(const char *value);

// 将|field|组件值从|u|和|url|复制到
// |目标|。如果|u|没有|field|，则此函数会
// 没有什么
void copy_url_component(std::string &dest, const http_parser_url *u, int field,
                        const char *url);

Headers::value_type to_header(const uint8_t *name, size_t namelen,
                              const uint8_t *value, size_t valuelen,
                              bool no_index, int32_t token);

// 将名称/值对添加到|nva|。如果|no_index|为真，则此
// 名称/值对在转发到下一个时不会被索引
// 单足蹦跳此函数在|value|周围删除空格。
void add_header(Headers &nva, const uint8_t *name, size_t namelen,
                const uint8_t *value, size_t valuelen, bool no_index,
                int32_t token);

// 返回指向|nva|中名为|name|的项的指针。如果
// 多个名称为|name|的条目，最后一次出现
// 返回in|nva|。如果不存在这样的条目，则返回nullptr。
const Headers::value_type *get_header(const Headers &nva, const char *name);

// 如果|nv|的值不为空，则返回true。
bool non_empty_value(const HeaderRefs::value_type *nv);

// 使用|name|和|value|创建nghttp2_nv并返回它。这个
// 返回的值仅引用指向name的数据指针。c_str（）和
// value.c_str（）。如果|no_index|为true，则nghttp2_nv标志成员具有
// NGHTTP2_NV_FLAG_NO_INDEX标志已设置。
nghttp2_nv make_nv(const std::string &name, const std::string &value,
                   bool no_index = false);

nghttp2_nv make_nv(const StringRef &name, const StringRef &value,
                   bool no_index = false);

nghttp2_nv make_nv_nocopy(const std::string &name, const std::string &value,
                          bool no_index = false);

nghttp2_nv make_nv_nocopy(const StringRef &name, const StringRef &value,
                          bool no_index = false);

// 从字符串文字|name|和|value|创建nghttp2_nv。
template <size_t N, size_t M>
constexpr nghttp2_nv make_nv_ll(const char (&name)[N], const char (&value)[M]) {
  return {(uint8_t *)name, (uint8_t *)value, N - 1, M - 1,
          NGHTTP2_NV_FLAG_NO_COPY_NAME | NGHTTP2_NV_FLAG_NO_COPY_VALUE};
}

// 从字符串文字|name|和c-string|value|创建nghttp2_nv。
template <size_t N>
nghttp2_nv make_nv_lc(const char (&name)[N], const char *value) {
  return {(uint8_t *)name, (uint8_t *)value, N - 1, strlen(value),
          NGHTTP2_NV_FLAG_NO_COPY_NAME};
}

template <size_t N>
nghttp2_nv make_nv_lc_nocopy(const char (&name)[N], const char *value) {
  return {(uint8_t *)name, (uint8_t *)value, N - 1, strlen(value),
          NGHTTP2_NV_FLAG_NO_COPY_NAME | NGHTTP2_NV_FLAG_NO_COPY_VALUE};
}

// 从string literal | name |和std:：string创建nghttp2_nv
// |值|。
template <size_t N>
nghttp2_nv make_nv_ls(const char (&name)[N], const std::string &value) {
  return {(uint8_t *)name, (uint8_t *)value.c_str(), N - 1, value.size(),
          NGHTTP2_NV_FLAG_NO_COPY_NAME};
}

template <size_t N>
nghttp2_nv make_nv_ls_nocopy(const char (&name)[N], const std::string &value) {
  return {(uint8_t *)name, (uint8_t *)value.c_str(), N - 1, value.size(),
          NGHTTP2_NV_FLAG_NO_COPY_NAME | NGHTTP2_NV_FLAG_NO_COPY_VALUE};
}

template <size_t N>
nghttp2_nv make_nv_ls_nocopy(const char (&name)[N], const StringRef &value) {
  return {(uint8_t *)name, (uint8_t *)value.c_str(), N - 1, value.size(),
          NGHTTP2_NV_FLAG_NO_COPY_NAME | NGHTTP2_NV_FLAG_NO_COPY_VALUE};
}

enum HeaderBuildOp {
  HDOP_NONE,
  // 必须剥离转发的标头字段。如果此标志不是
  // 设置，将添加除最后一个字段之外的所有转发的标头字段。
  HDOP_STRIP_FORWARDED = 1,
  // 必须剥离X-Forwarded-For标头字段。如果此标志为
  // 未设置，除最后一个字段之外的所有X-Forwarded-For标头字段
  // 添加。
  HDOP_STRIP_X_FORWARDED_FOR = 1 << 1,
  // 必须剥离X-Forwarded-Proto标头字段。如果此标志
  // 未设置，除last以外的所有X-Forwarded-Proto标头字段
  // 添加一个。
  HDOP_STRIP_X_FORWARDED_PROTO = 1 << 2,
  // 必须剥离Via标头字段。如果未设置此标志，则所有
  // 将添加除最后一个字段以外的其他标题字段。
  HDOP_STRIP_VIA = 1 << 3,
  // 必须剥离早期数据标题字段。如果此标志不是
  // 设置时，将添加所有早期数据标题字段。
  HDOP_STRIP_EARLY_DATA = 1 << 4,
  // 在所有标题字段上方删除。
  HDOP_STRIP_ALL = HDOP_STRIP_FORWARDED | HDOP_STRIP_X_FORWARDED_FOR |
                   HDOP_STRIP_X_FORWARDED_PROTO | HDOP_STRIP_VIA |
                   HDOP_STRIP_EARLY_DATA,
  // 必须剥离Sec WebSocket Accept标头字段。如果此标志
  // 未设置，将添加所有Sec WebSocket Accept标头字段。
  HDOP_STRIP_SEC_WEBSOCKET_ACCEPT = 1 << 5,
  // 必须剥离Sec WebSocket Key标头字段。如果此标志为
  // 如果未设置，则添加所有Sec WebSocket Key头字段。
  HDOP_STRIP_SEC_WEBSOCKET_KEY = 1 << 6,
  // 必须去除传输编码头字段。如果此标志为
  // 如果未设置，则添加所有传输编码头字段。
  HDOP_STRIP_TRANSFER_ENCODING = 1 << 7,
};

// 将|headers|中的标头追加到|nv||标头|必须编入索引
// 在此调用之前（其元素的令牌字段已分配）。某些
// 标头，包括HTTP/2规范和标头中不允许的标头
// 不复制需要特殊处理（即|标志|
// 是一个或多个HeaderBuildOp标志。他们告诉函数
// 不应添加某些标头字段。
void copy_headers_to_nva(std::vector<nghttp2_nv> &nva,
                         const HeaderRefs &headers, uint32_t flags);

// 就像copy_headers_to_nva（）一样，但这增加了
// NGHTTP2_NV_FLAG_NO_COPY_NAME和NGHTTP2_ NV_FLAG_NO_COPY_VALUE。
void copy_headers_to_nva_nocopy(std::vector<nghttp2_nv> &nva,
                                const HeaderRefs &headers, uint32_t flags);

// 将HTTP/1.1样式的标题行追加到
// |标题||headers |必须在此调用（其
// 元素的令牌字段被分配）。某些收割台
// 需要特殊处理（即via和cookie）。
// |flags |是一个或多个HeaderBuildOp标志。它们告诉我们功能
// 不应添加某些标头字段。
void build_http1_headers_from_headers(DefaultMemchunks *buf,
                                      const HeaderRefs &headers,
                                      uint32_t flags);

// 如果window_UPDATE应为
// 为流|stream_id|发送。如果|stream_id |==0，则此函数
// 确定连接是否需要WINDOW_UPDATE。
//
// 如果函数确定在
// 瞬间，它返回-1。
int32_t determine_window_update_transmission(nghttp2_session *session,
                                             int32_t stream_id);

// 将|nv|中的名称/值对转储到|out|。|nv|必须为
// 以nullptr终止。
void dump_nv(FILE *out, const char **nv);

// 将|nva|中的名称/值对转储到|out|。
void dump_nv(FILE *out, const nghttp2_nv *nva, size_t nvlen);

// 将|nva|中的名称/值对转储到|out|。
void dump_nv(FILE *out, const Headers &nva);

void dump_nv(FILE *out, const HeaderRefs &nva);

// 将页眉放在|hd|中。
void erase_header(HeaderRef *hd);

// 重写通常出现在位置标头中的重定向URI
// 领域|uri |是位置标头字段中的uri。|u|
// 存储解析的|uri |的结果。|request_authority|是
// 请求中的host或：authority标头字段值。这个
// |upstream_scheme|在上游是“https”或“http”
// 界面仅当位置标头字段值
// 包含|match_host|作为主机排除端口。|match_host|和
// |request_authority|可能不同。如果|request_authority|是
// 空的，剥夺权力。
//
// 此函数在成功时返回新的重写URI。如果
// 位置URI不受重写影响，此函数返回
// 空字符串。
StringRef rewrite_location_uri(BlockAllocator &balloc, const StringRef &uri,
                               const http_parser_url &u,
                               const StringRef &match_host,
                               const StringRef &request_authority,
                               const StringRef &upstream_scheme);

// 使用nghttp2_check_header_name（）检查标头名称/值对
// 和nghttp2_check_header_value（）。如果两个函数都返回非零，
// 此函数返回非零。
int check_nv(const uint8_t *name, size_t namelen, const uint8_t *value,
             size_t valuelen);

// 返回解析的HTTP状态代码。失败时返回-1。
int parse_http_status_code(const StringRef &src);

// 要索引的标题字段，但HD_MAXIDX方便
// 成员以获取最大值。
//
// 由genheaderfunc.py生成
enum {
  HD__AUTHORITY,
  HD__HOST,
  HD__METHOD,
  HD__PATH,
  HD__PROTOCOL,
  HD__SCHEME,
  HD__STATUS,
  HD_ACCEPT_ENCODING,
  HD_ACCEPT_LANGUAGE,
  HD_ALT_SVC,
  HD_CACHE_CONTROL,
  HD_CONNECTION,
  HD_CONTENT_LENGTH,
  HD_CONTENT_TYPE,
  HD_COOKIE,
  HD_DATE,
  HD_EARLY_DATA,
  HD_EXPECT,
  HD_FORWARDED,
  HD_HOST,
  HD_HTTP2_SETTINGS,
  HD_IF_MODIFIED_SINCE,
  HD_KEEP_ALIVE,
  HD_LINK,
  HD_LOCATION,
  HD_PROXY_CONNECTION,
  HD_SEC_WEBSOCKET_ACCEPT,
  HD_SEC_WEBSOCKET_KEY,
  HD_SERVER,
  HD_TE,
  HD_TRAILER,
  HD_TRANSFER_ENCODING,
  HD_UPGRADE,
  HD_USER_AGENT,
  HD_VIA,
  HD_X_FORWARDED_FOR,
  HD_X_FORWARDED_PROTO,
  HD_MAXIDX,
};

using HeaderIndex = std::array<int16_t, HD_MAXIDX>;

// 查找长度为|nameen|的标头名称|name|的标头标记。
// 只有我们感兴趣的头被标记化。如果标题名称
// 无法标记，返回-1。
int lookup_token(const uint8_t *name, size_t namelen);
int lookup_token(const StringRef &name);

// 初始化|hdidx|，头索引。|hdidx|必须指向
// 至少包含HD_MAXIDX元素的数组。
void init_hdidx(HeaderIndex &hdidx);
// 使用索引|idx|索引标头|token|。
void index_header(HeaderIndex &hdidx, int32_t token, size_t idx);

// 使用索引|hdidx|返回由|token|表示的标头。
const Headers::value_type *get_header(const HeaderIndex &hdidx, int32_t token,
                                      const Headers &nva);

Headers::value_type *get_header(const HeaderIndex &hdidx, int32_t token,
                                Headers &nva);

struct LinkHeader {
  // URI的区域。这可能不是以NULL结尾的。
  StringRef uri;
};

// 返回链接头字段值|src|中的下一个URI引用。如果没有
// 搜索所有输入后找到URI引用，返回URI字段
// 为空。这意味着在
// 解析。
std::vector<LinkHeader> parse_link_header(const StringRef &src);

// 通过将基本路径|base_path|与另一个路径组合来构造路径
// 路径| rel_path |。基本路径和另一个路径可以具有可选
// 查询组件。此函数假定|base_path|已规范化。
// 换句话说，它不包含“..”或“.”路径组件
// 如果不为空，则以“/”开头。
std::string path_join(const StringRef &base, const StringRef &base_query,
                      const StringRef &rel_path, const StringRef &rel_query);

StringRef path_join(BlockAllocator &balloc, const StringRef &base_path,
                    const StringRef &base_query, const StringRef &rel_path,
                    const StringRef &rel_query);

// 如果响应具有主体，则为true，同时考虑请求方法
// 和状态代码。
bool expect_response_body(const std::string &method, int status_code);
bool expect_response_body(int method_token, int status_code);

// 如果响应具有正文，则为true，仅考虑状态代码。
bool expect_response_body(int status_code);

// 查找长度为|nameen|的方法名|name|的方法标记。
// 仅llhttp中定义的方法。h（llhttp_method）被标记化。如果
// 方法名不能标记化，返回-1。
int lookup_method_token(const uint8_t *name, size_t namelen);
int lookup_method_token(const StringRef &name);

// 返回|method_token|的字符串表示形式。这是包装器
// 围绕llhttp中的llhttp_method_name。如果|method_token|为
// 未知，程序中止。返回的StringRef保证
// 以NULL结尾。
StringRef to_method_string(int method_token);

StringRef normalize_path(BlockAllocator &balloc, const StringRef &path,
                         const StringRef &query);

std::string normalize_path(const StringRef &path, const StringRef &query);

StringRef rewrite_clean_path(BlockAllocator &balloc, const StringRef &src);

// 返回|uri|的路径组件。返回的路径不
// 包含查询组件。如果
// 失败。
StringRef get_pure_path_component(const StringRef &uri);

// 从给定的|uri|中推断方案、权限和路径，并存储
// 它们分别位于|scheme|、|authority|和|path|中。如果|uri|
// 是相对路径，路径解析使用
// |基底|长度|基线|。如果
// 成功或-1。
int construct_push_component(BlockAllocator &balloc, StringRef &scheme,
                             StringRef &authority, StringRef &path,
                             const StringRef &base, const StringRef &uri);

// 复制|src|并返回其小写版本。
StringRef copy_lower(BlockAllocator &balloc, const StringRef &src);

// 如果te标头字段值|s|包含“尾部”，则返回true。
bool contains_trailers(const StringRef &s);

// 为|key|创建Sec WebSocket Accept值。容量
// |dest|指向的缓冲区必须至少有24个字节（base64
// 16字节数据的编码长度）。它返回空字符串
// 错误。
StringRef make_websocket_accept_token(uint8_t *dest, const StringRef &key);

// 如果HTTP版本表示预HTTP/1.1（例如。，
// HTTP/0.9或HTTP/1.0）。
bool legacy_http1(int major, int minor);

} // 命名空间http2

} // 命名空间nghttp2

#endif // HTTP2_H

