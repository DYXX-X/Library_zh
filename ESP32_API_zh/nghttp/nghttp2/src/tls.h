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
#ifndef TLS_H
#define TLS_H

#include "nghttp2_config.h"

#include <cinttypes>

#include <openssl/ssl.h>

#include "ssl_compat.h"

namespace nghttp2 {

namespace tls {

// 获取OpenSSL全局锁以在多个
// 线程。构造函数获取锁和析构函数解锁。
class LibsslGlobalLock {
public:
  LibsslGlobalLock();
  LibsslGlobalLock(const LibsslGlobalLock &) = delete;
  LibsslGlobalLock &operator=(const LibsslGlobalLock &) = delete;
};

// 推荐的通用“现代兼容性”密码套件
// 莫齐拉。
//
// https://wiki.mozilla.org/Security/Server_Side_TLS
constexpr char DEFAULT_CIPHER_LIST[] =
    "ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-"
    "CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-"
    "SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-"
    "AES256-SHA384:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256";

constexpr char DEFAULT_TLS13_CIPHER_LIST[] =
#if OPENSSL_1_1_1_API
    TLS_DEFAULT_CIPHERSUITES
#else  // !OPENSSL_1_1_1_API
    ""
#endif // !OPENSSL_1_1_1_API
    ;

constexpr auto NGHTTP2_TLS_MIN_VERSION = TLS1_VERSION;
#ifdef TLS1_3_VERSION
constexpr auto NGHTTP2_TLS_MAX_VERSION = TLS1_3_VERSION;
#else  // !TLS1_3_VERSION
constexpr auto NGHTTP2_TLS_MAX_VERSION = TLS1_2_VERSION;
#endif // !TLS1_3_VERSION

const char *get_tls_protocol(SSL *ssl);

struct TLSSessionInfo {
  const char *cipher;
  const char *protocol;
  const uint8_t *session_id;
  bool session_reused;
  size_t session_id_length;
};

TLSSessionInfo *get_tls_session_info(TLSSessionInfo *tls_info, SSL *ssl);

// 如果协商协议为TLSv1.2，则返回true。
bool check_http2_tls_version(SSL *ssl);

// 如果协商的密码套件为HTTP/2密码，则返回true
// 黑名单
bool check_http2_cipher_black_list(SSL *ssl);

// 如果满足HTTP/2的SSL/TLS要求，则返回true。
// 为满足要求，必须遵守以下两个条款：
//
// 1.协商协议必须是TLSv1.2。
// 2.协商的密码电路未列入黑名单
//    如RFC 7540所述。
bool check_http2_requirement(SSL *ssl);

// 初始化OpenSSL库
void libssl_init();

// 将TLS最小和最大版本设置为|ssl_ctx|。此函数返回
// 如果成功，则为0，或者为-1。
int ssl_ctx_set_proto_versions(SSL_CTX *ssl_ctx, int min, int max);

} // 命名空间tls

} // 命名空间nghttp2

#endif // TLS_H

