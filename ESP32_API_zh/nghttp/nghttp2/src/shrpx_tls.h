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
#ifndef SHRPX_TLS_H
#define SHRPX_TLS_H

#include "shrpx.h"

#include <vector>
#include <mutex>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <ev.h>

#ifdef HAVE_NEVERBLEED
#  include <neverbleed.h>
#endif // HAVE_NEVERBLEED

#include "network.h"
#include "shrpx_config.h"
#include "shrpx_router.h"

namespace shrpx {

class ClientHandler;
class Worker;
class DownstreamConnectionPool;
struct DownstreamAddr;
struct UpstreamAddr;

namespace tls {

struct TLSSessionCache {
  // SSL_SSESSION对象的ASN1表示。看见
  // i2d_SSL_会话（3SSL）。
  std::vector<uint8_t> session_data;
  // 创建或更新此缓存项时的最后一个时间戳。
  ev_tstamp last_updated;
};

// 此结构存储每个SSL_CTX的附加信息。这是
// 使用SSL_CTX_set_app_data（）连接到SSL_CTX。
struct TLSContextData {
  // SCT数据格式化，以便可以直接发送为
  // 签名证书时间戳的扩展数据。
  std::vector<uint8_t> sct_data;
#ifndef HAVE_ATOMIC_STD_SHARED_PTR
  // 保护ocsp_data；
  std::mutex mu;
#endif // !HAVE_ATOMIC_STD_SHARED_PTR
  // OCSP响应
  std::shared_ptr<std::vector<uint8_t>> ocsp_data;

  // 证书文件的路径
  const char *cert_file;
};

// 创建服务器端SSL_CTX
SSL_CTX *create_ssl_context(const char *private_key_file, const char *cert_file,
                            const std::vector<uint8_t> &sct_data

#ifdef HAVE_NEVERBLEED
                            ,
                            neverbleed_t *nb
#endif // HAVE_NEVERBLEED
);

// 创建客户端SSL_CTX。这不会配置ALPN设置。
// |next_proto_select_cb|用于NPN。
SSL_CTX *create_ssl_client_context(
#ifdef HAVE_NEVERBLEED
    neverbleed_t *nb,
#endif // HAVE_NEVERBLEED
    const StringRef &cacert, const StringRef &cert_file,
    const StringRef &private_key_file,
    int (*next_proto_select_cb)(SSL *s, unsigned char **out,
                                unsigned char *outlen, const unsigned char *in,
                                unsigned int inlen, void *arg));

ClientHandler *accept_connection(Worker *worker, int fd, sockaddr *addr,
                                 int addrlen, const UpstreamAddr *faddr);

// 根据给定的|地址|和|主机|检查对等方的证书。
int check_cert(SSL *ssl, const Address *addr, const StringRef &host);
// 根据中描述的给定主机名检查对等方的证书
// |addr|和数字地址在|raddr|中。注意|raddr|可能不会
// 指向&addr->addr。
int check_cert(SSL *ssl, const DownstreamAddr *addr, const Address *raddr);

struct WildcardRevPrefix {
  WildcardRevPrefix(const StringRef &prefix, size_t idx)
      : prefix(std::begin(prefix), std::end(prefix)), idx(idx) {}

  // 通配符模式的“前缀”。它与原始形式相反。
  // 例如，如果原始通配符是“test*.nghttp2.org”，
  // 前缀将是“tset”。
  ImmutableString prefix;
  // SSL_CTX的索引。请参阅ConnectionHandler:：get_ssl_ctx（）。
  size_t idx;
};

struct WildcardPattern {
  // 通配符主机仅共享后缀可能很少见，所以我们只需要
  // 线性搜索。
  std::vector<WildcardRevPrefix> rev_prefix;
};

class CertLookupTree {
public:
  CertLookupTree();

  // 将主机名模式|主机名|添加到查找树，关联
  // 值|索引|。当被查询的主机匹配此模式时，
  // |返回索引|。我们支持通配符模式。最左边的
  // “*”被视为通配符，并且必须在
  // 至少一个字符。如果已经添加了相同的图案，
  // 此函数不会更改树，并返回现有的
  // 匹配索引。
  //
  // 调用者应该小写|hostname|，因为此函数
  // 这样做，查找函数执行区分大小写的匹配。
  //
  // TODO处理通配符模式，描述为RFC 6125。
  //
  // 此函数返回索引。如果失败，则返回-1
  // （例如，主机名过长）。如果返回的索引等于
  // |index|，然后将hostname添加到树中
  // |索引|。如果它不是-1，并且不等于|index|，则相同
  // 主机名已添加到树中。
  ssize_t add_cert(const StringRef &hostname, size_t index);

  // 使用给定的|hostname|查找索引。完全匹配需要
  // 优先于通配符匹配。对于通配符匹配，最长
  // match（以字节为单位的匹配后缀和前缀长度之和）为
  // 最好是用较长的后缀打平。
  //
  // 调用方应使用小写| hostname |，因为此函数
  // 执行区分大小写的匹配。
  ssize_t lookup(const StringRef &hostname);

  // 将此查找树的内容转储到stderr。
  void dump() const;

private:
  // 完全匹配
  Router router_;
  // 通配符反后缀匹配。返回的索引为
  // 通配符模式。
  Router rev_wildcard_router_;
  // 存储通配符后缀模式。
  std::vector<WildcardPattern> wildcard_patterns_;
};

// 将|ssl_ctx|中证书中的主机名添加到查找树|lt|。
// subjectAltNames和commonName被视为合格
// 主机名。如果subjectAltNames中至少有一个dNSName，
// 不考虑commonName|ssl_ctx|也添加到
// |indexed_ssl_ctx|。如果成功，此函数将返回0，或者返回-1。
int cert_lookup_tree_add_ssl_ctx(
    CertLookupTree *lt, std::vector<std::vector<SSL_CTX *>> &indexed_ssl_ctx,
    SSL_CTX *ssl_ctx);

// 如果|proto|包含在
// 协议列表|protos|。
bool in_proto_list(const std::vector<StringRef> &protos,
                   const StringRef &proto);

// 如果满足HTTP/2的安全要求，则返回true。
bool check_http2_requirement(SSL *ssl);

// 返回SSL/TLS选项掩码以禁用SSL/TLS协议版本
// 包含在|tls_proto_list|中。返回的掩码可以直接
// 传递给SSL_CTX_set_options（）。
long int create_tls_proto_mask(const std::vector<StringRef> &tls_proto_list);

int set_alpn_prefs(std::vector<unsigned char> &out,
                   const std::vector<StringRef> &protos);

// 设置服务器端SSL_CTX。此函数检查get_config（）
// 如果upstreamno_tls为true，则返回nullptr。否则
// 构造默认SSL_CTX。如果子证书可用
// （get_config（）->subcerts），调用者应提供CertLookupTree
// 对象作为|cert_tree|参数，否则SNI无法工作。全部的
// 创建的SSL_CTX存储到|all_SSL_CTX|中。它们也是
// 已添加到|indexed_ssl_ctx||cert_tree |使用其索引
// 将主机名与SSL_CTX关联。
SSL_CTX *
setup_server_ssl_context(std::vector<SSL_CTX *> &all_ssl_ctx,
                         std::vector<std::vector<SSL_CTX *>> &indexed_ssl_ctx,
                         CertLookupTree *cert_tree
#ifdef HAVE_NEVERBLEED
                         ,
                         neverbleed_t *nb
#endif // HAVE_NEVERBLEED
);

// 设置客户端SSL_CTX。
SSL_CTX *setup_downstream_client_ssl_context(
#ifdef HAVE_NEVERBLEED
    neverbleed_t *nb
#endif // HAVE_NEVERBLEED
);

// 在|SSL|中设置适合HTTP/2使用的ALPN设置。
void setup_downstream_http2_alpn(SSL *ssl);
// 在|SSL|中设置适合HTTP/1.1使用的ALPN设置。
void setup_downstream_http1_alpn(SSL *ssl);

// 创建CertLookupTree。如果前端被配置为不使用TLS，
// 此函数返回nullptr。
std::unique_ptr<CertLookupTree> create_cert_lookup_tree();

SSL *create_ssl(SSL_CTX *ssl_ctx);

// 如果在上游启用SSL/TLS，则返回true
bool upstream_tls_enabled(const ConnectionConfig &connconf);

// 执行TLS主机名匹配|模式|可以包含通配符
// 字符“*”，与目标主机名的前缀匹配。有
// 使通配符有效的几个限制。匹配算法
// 基于RFC 6125。
bool tls_hostname_match(const StringRef &pattern, const StringRef &hostname);

// 缓存|会话||会话|已序列化为ASN1
// 表示并存储|t|用作时间戳。
// 根据现有缓存的时间戳，|session|可能不会
// 缓存。
void try_cache_tls_session(TLSSessionCache *cache, SSL_SESSION *session,
                           ev_tstamp t);

// 返回缓存的会话关联|addr|。如果没有缓存条目
// 找到与|addr|关联的，将返回nullptr。
SSL_SESSION *reuse_tls_session(const TLSSessionCache &addr);

// 加载证书表单文件|filename|。呼叫方应删除
// 返回的对象使用X509_free（）。
X509 *load_certificate(const char *filename);

// 从|v|返回TLS版本。返回的值在中定义
// OpenSSL头文件。如果|v|无效，则此函数返回-1
// TLS版本字符串。
int proto_version_from_string(const StringRef &v);

// 验证长度为|OCSP_resplen|的OCSP响应|OCSP_resp|。这
// 如果函数成功，则返回0，或者返回-1。
int verify_ocsp_response(SSL_CTX *ssl_ctx, const uint8_t *ocsp_resp,
                         size_t ocsp_resplen);

// 存储长度|dstlen|的|dst|中|x|的指纹|md公司|
// 指定要使用的哈希函数，并且|dstlen|必须足够大
// 以包括哈希值（例如SHA-256的32字节）。此函数
// 返回写入|dst|或-1的字节数。
ssize_t get_x509_fingerprint(uint8_t *dst, size_t dstlen, const X509 *x,
                             const EVP_MD *md);

// 返回|x|的主题名称。如果此函数无法获取主题
// name，则返回一个空字符串。
StringRef get_x509_subject_name(BlockAllocator &balloc, X509 *x);

// 返回|x|的颁发者名称。如果此函数无法获取颁发者
// name，则返回一个空字符串。
StringRef get_x509_issuer_name(BlockAllocator &balloc, X509 *x);

// 返回|x|的序列号。如果此函数无法获取串行
// number，则返回空字符串。数字
StringRef get_x509_serial(BlockAllocator &balloc, X509 *x);

// 在|t|中填充|x|的NotBefore。如果
// 成功或-1。
int get_x509_not_before(time_t &t, X509 *x);

// 在|t|中填充|x|的NotAfter。如果
// 成功或-1。
int get_x509_not_after(time_t &t, X509 *x);

} // 命名空间tls

} // 命名空间shrpx

#endif // SHRPX_TLS_H

