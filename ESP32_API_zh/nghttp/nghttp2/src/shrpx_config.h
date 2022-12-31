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
#ifndef SHRPX_CONFIG_H
#define SHRPX_CONFIG_H

#include "shrpx.h"

#include <sys/types.h>
#ifdef HAVE_SYS_SOCKET_H
#  include <sys/socket.h>
#endif // HAVE_SYS_SOCKET_H
#include <sys/un.h>
#ifdef HAVE_NETINET_IN_H
#  include <netinet/in.h>
#endif // HAVE_NETINET_IN_H
#ifdef HAVE_ARPA_INET_H
#  include <arpa/inet.h>
#endif // HAVE_ARPA_INET_H
#include <cinttypes>
#include <cstdio>
#include <vector>
#include <memory>
#include <set>

#include <openssl/ssl.h>

#include <ev.h>

#include <nghttp2/nghttp2.h>

#include "shrpx_router.h"
#include "template.h"
#include "http2.h"
#include "network.h"
#include "allocator.h"

using namespace nghttp2;

namespace shrpx {

struct LogFragment;
class ConnectBlocker;
class Http2Session;

namespace tls {

class CertLookupTree;

} // 命名空间tls

constexpr auto SHRPX_OPT_PRIVATE_KEY_FILE =
    StringRef::from_lit("private-key-file");
constexpr auto SHRPX_OPT_PRIVATE_KEY_PASSWD_FILE =
    StringRef::from_lit("private-key-passwd-file");
constexpr auto SHRPX_OPT_CERTIFICATE_FILE =
    StringRef::from_lit("certificate-file");
constexpr auto SHRPX_OPT_DH_PARAM_FILE = StringRef::from_lit("dh-param-file");
constexpr auto SHRPX_OPT_SUBCERT = StringRef::from_lit("subcert");
constexpr auto SHRPX_OPT_BACKEND = StringRef::from_lit("backend");
constexpr auto SHRPX_OPT_FRONTEND = StringRef::from_lit("frontend");
constexpr auto SHRPX_OPT_WORKERS = StringRef::from_lit("workers");
constexpr auto SHRPX_OPT_HTTP2_MAX_CONCURRENT_STREAMS =
    StringRef::from_lit("http2-max-concurrent-streams");
constexpr auto SHRPX_OPT_LOG_LEVEL = StringRef::from_lit("log-level");
constexpr auto SHRPX_OPT_DAEMON = StringRef::from_lit("daemon");
constexpr auto SHRPX_OPT_HTTP2_PROXY = StringRef::from_lit("http2-proxy");
constexpr auto SHRPX_OPT_HTTP2_BRIDGE = StringRef::from_lit("http2-bridge");
constexpr auto SHRPX_OPT_CLIENT_PROXY = StringRef::from_lit("client-proxy");
constexpr auto SHRPX_OPT_ADD_X_FORWARDED_FOR =
    StringRef::from_lit("add-x-forwarded-for");
constexpr auto SHRPX_OPT_STRIP_INCOMING_X_FORWARDED_FOR =
    StringRef::from_lit("strip-incoming-x-forwarded-for");
constexpr auto SHRPX_OPT_NO_VIA = StringRef::from_lit("no-via");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_READ_TIMEOUT =
    StringRef::from_lit("frontend-http2-read-timeout");
constexpr auto SHRPX_OPT_FRONTEND_READ_TIMEOUT =
    StringRef::from_lit("frontend-read-timeout");
constexpr auto SHRPX_OPT_FRONTEND_WRITE_TIMEOUT =
    StringRef::from_lit("frontend-write-timeout");
constexpr auto SHRPX_OPT_BACKEND_READ_TIMEOUT =
    StringRef::from_lit("backend-read-timeout");
constexpr auto SHRPX_OPT_BACKEND_WRITE_TIMEOUT =
    StringRef::from_lit("backend-write-timeout");
constexpr auto SHRPX_OPT_STREAM_READ_TIMEOUT =
    StringRef::from_lit("stream-read-timeout");
constexpr auto SHRPX_OPT_STREAM_WRITE_TIMEOUT =
    StringRef::from_lit("stream-write-timeout");
constexpr auto SHRPX_OPT_ACCESSLOG_FILE = StringRef::from_lit("accesslog-file");
constexpr auto SHRPX_OPT_ACCESSLOG_SYSLOG =
    StringRef::from_lit("accesslog-syslog");
constexpr auto SHRPX_OPT_ACCESSLOG_FORMAT =
    StringRef::from_lit("accesslog-format");
constexpr auto SHRPX_OPT_ERRORLOG_FILE = StringRef::from_lit("errorlog-file");
constexpr auto SHRPX_OPT_ERRORLOG_SYSLOG =
    StringRef::from_lit("errorlog-syslog");
constexpr auto SHRPX_OPT_BACKEND_KEEP_ALIVE_TIMEOUT =
    StringRef::from_lit("backend-keep-alive-timeout");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_WINDOW_BITS =
    StringRef::from_lit("frontend-http2-window-bits");
constexpr auto SHRPX_OPT_BACKEND_HTTP2_WINDOW_BITS =
    StringRef::from_lit("backend-http2-window-bits");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_CONNECTION_WINDOW_BITS =
    StringRef::from_lit("frontend-http2-connection-window-bits");
constexpr auto SHRPX_OPT_BACKEND_HTTP2_CONNECTION_WINDOW_BITS =
    StringRef::from_lit("backend-http2-connection-window-bits");
constexpr auto SHRPX_OPT_FRONTEND_NO_TLS =
    StringRef::from_lit("frontend-no-tls");
constexpr auto SHRPX_OPT_BACKEND_NO_TLS = StringRef::from_lit("backend-no-tls");
constexpr auto SHRPX_OPT_BACKEND_TLS_SNI_FIELD =
    StringRef::from_lit("backend-tls-sni-field");
constexpr auto SHRPX_OPT_PID_FILE = StringRef::from_lit("pid-file");
constexpr auto SHRPX_OPT_USER = StringRef::from_lit("user");
constexpr auto SHRPX_OPT_SYSLOG_FACILITY =
    StringRef::from_lit("syslog-facility");
constexpr auto SHRPX_OPT_BACKLOG = StringRef::from_lit("backlog");
constexpr auto SHRPX_OPT_CIPHERS = StringRef::from_lit("ciphers");
constexpr auto SHRPX_OPT_CLIENT = StringRef::from_lit("client");
constexpr auto SHRPX_OPT_INSECURE = StringRef::from_lit("insecure");
constexpr auto SHRPX_OPT_CACERT = StringRef::from_lit("cacert");
constexpr auto SHRPX_OPT_BACKEND_IPV4 = StringRef::from_lit("backend-ipv4");
constexpr auto SHRPX_OPT_BACKEND_IPV6 = StringRef::from_lit("backend-ipv6");
constexpr auto SHRPX_OPT_BACKEND_HTTP_PROXY_URI =
    StringRef::from_lit("backend-http-proxy-uri");
constexpr auto SHRPX_OPT_READ_RATE = StringRef::from_lit("read-rate");
constexpr auto SHRPX_OPT_READ_BURST = StringRef::from_lit("read-burst");
constexpr auto SHRPX_OPT_WRITE_RATE = StringRef::from_lit("write-rate");
constexpr auto SHRPX_OPT_WRITE_BURST = StringRef::from_lit("write-burst");
constexpr auto SHRPX_OPT_WORKER_READ_RATE =
    StringRef::from_lit("worker-read-rate");
constexpr auto SHRPX_OPT_WORKER_READ_BURST =
    StringRef::from_lit("worker-read-burst");
constexpr auto SHRPX_OPT_WORKER_WRITE_RATE =
    StringRef::from_lit("worker-write-rate");
constexpr auto SHRPX_OPT_WORKER_WRITE_BURST =
    StringRef::from_lit("worker-write-burst");
constexpr auto SHRPX_OPT_NPN_LIST = StringRef::from_lit("npn-list");
constexpr auto SHRPX_OPT_TLS_PROTO_LIST = StringRef::from_lit("tls-proto-list");
constexpr auto SHRPX_OPT_VERIFY_CLIENT = StringRef::from_lit("verify-client");
constexpr auto SHRPX_OPT_VERIFY_CLIENT_CACERT =
    StringRef::from_lit("verify-client-cacert");
constexpr auto SHRPX_OPT_CLIENT_PRIVATE_KEY_FILE =
    StringRef::from_lit("client-private-key-file");
constexpr auto SHRPX_OPT_CLIENT_CERT_FILE =
    StringRef::from_lit("client-cert-file");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_DUMP_REQUEST_HEADER =
    StringRef::from_lit("frontend-http2-dump-request-header");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_DUMP_RESPONSE_HEADER =
    StringRef::from_lit("frontend-http2-dump-response-header");
constexpr auto SHRPX_OPT_HTTP2_NO_COOKIE_CRUMBLING =
    StringRef::from_lit("http2-no-cookie-crumbling");
constexpr auto SHRPX_OPT_FRONTEND_FRAME_DEBUG =
    StringRef::from_lit("frontend-frame-debug");
constexpr auto SHRPX_OPT_PADDING = StringRef::from_lit("padding");
constexpr auto SHRPX_OPT_ALTSVC = StringRef::from_lit("altsvc");
constexpr auto SHRPX_OPT_ADD_REQUEST_HEADER =
    StringRef::from_lit("add-request-header");
constexpr auto SHRPX_OPT_ADD_RESPONSE_HEADER =
    StringRef::from_lit("add-response-header");
constexpr auto SHRPX_OPT_WORKER_FRONTEND_CONNECTIONS =
    StringRef::from_lit("worker-frontend-connections");
constexpr auto SHRPX_OPT_NO_LOCATION_REWRITE =
    StringRef::from_lit("no-location-rewrite");
constexpr auto SHRPX_OPT_NO_HOST_REWRITE =
    StringRef::from_lit("no-host-rewrite");
constexpr auto SHRPX_OPT_BACKEND_HTTP1_CONNECTIONS_PER_HOST =
    StringRef::from_lit("backend-http1-connections-per-host");
constexpr auto SHRPX_OPT_BACKEND_HTTP1_CONNECTIONS_PER_FRONTEND =
    StringRef::from_lit("backend-http1-connections-per-frontend");
constexpr auto SHRPX_OPT_LISTENER_DISABLE_TIMEOUT =
    StringRef::from_lit("listener-disable-timeout");
constexpr auto SHRPX_OPT_TLS_TICKET_KEY_FILE =
    StringRef::from_lit("tls-ticket-key-file");
constexpr auto SHRPX_OPT_RLIMIT_NOFILE = StringRef::from_lit("rlimit-nofile");
constexpr auto SHRPX_OPT_BACKEND_REQUEST_BUFFER =
    StringRef::from_lit("backend-request-buffer");
constexpr auto SHRPX_OPT_BACKEND_RESPONSE_BUFFER =
    StringRef::from_lit("backend-response-buffer");
constexpr auto SHRPX_OPT_NO_SERVER_PUSH = StringRef::from_lit("no-server-push");
constexpr auto SHRPX_OPT_BACKEND_HTTP2_CONNECTIONS_PER_WORKER =
    StringRef::from_lit("backend-http2-connections-per-worker");
constexpr auto SHRPX_OPT_FETCH_OCSP_RESPONSE_FILE =
    StringRef::from_lit("fetch-ocsp-response-file");
constexpr auto SHRPX_OPT_OCSP_UPDATE_INTERVAL =
    StringRef::from_lit("ocsp-update-interval");
constexpr auto SHRPX_OPT_NO_OCSP = StringRef::from_lit("no-ocsp");
constexpr auto SHRPX_OPT_HEADER_FIELD_BUFFER =
    StringRef::from_lit("header-field-buffer");
constexpr auto SHRPX_OPT_MAX_HEADER_FIELDS =
    StringRef::from_lit("max-header-fields");
constexpr auto SHRPX_OPT_INCLUDE = StringRef::from_lit("include");
constexpr auto SHRPX_OPT_TLS_TICKET_KEY_CIPHER =
    StringRef::from_lit("tls-ticket-key-cipher");
constexpr auto SHRPX_OPT_HOST_REWRITE = StringRef::from_lit("host-rewrite");
constexpr auto SHRPX_OPT_TLS_SESSION_CACHE_MEMCACHED =
    StringRef::from_lit("tls-session-cache-memcached");
constexpr auto SHRPX_OPT_TLS_TICKET_KEY_MEMCACHED =
    StringRef::from_lit("tls-ticket-key-memcached");
constexpr auto SHRPX_OPT_TLS_TICKET_KEY_MEMCACHED_INTERVAL =
    StringRef::from_lit("tls-ticket-key-memcached-interval");
constexpr auto SHRPX_OPT_TLS_TICKET_KEY_MEMCACHED_MAX_RETRY =
    StringRef::from_lit("tls-ticket-key-memcached-max-retry");
constexpr auto SHRPX_OPT_TLS_TICKET_KEY_MEMCACHED_MAX_FAIL =
    StringRef::from_lit("tls-ticket-key-memcached-max-fail");
constexpr auto SHRPX_OPT_MRUBY_FILE = StringRef::from_lit("mruby-file");
constexpr auto SHRPX_OPT_ACCEPT_PROXY_PROTOCOL =
    StringRef::from_lit("accept-proxy-protocol");
constexpr auto SHRPX_OPT_FASTOPEN = StringRef::from_lit("fastopen");
constexpr auto SHRPX_OPT_TLS_DYN_REC_WARMUP_THRESHOLD =
    StringRef::from_lit("tls-dyn-rec-warmup-threshold");
constexpr auto SHRPX_OPT_TLS_DYN_REC_IDLE_TIMEOUT =
    StringRef::from_lit("tls-dyn-rec-idle-timeout");
constexpr auto SHRPX_OPT_ADD_FORWARDED = StringRef::from_lit("add-forwarded");
constexpr auto SHRPX_OPT_STRIP_INCOMING_FORWARDED =
    StringRef::from_lit("strip-incoming-forwarded");
constexpr auto SHRPX_OPT_FORWARDED_BY = StringRef::from_lit("forwarded-by");
constexpr auto SHRPX_OPT_FORWARDED_FOR = StringRef::from_lit("forwarded-for");
constexpr auto SHRPX_OPT_REQUEST_HEADER_FIELD_BUFFER =
    StringRef::from_lit("request-header-field-buffer");
constexpr auto SHRPX_OPT_MAX_REQUEST_HEADER_FIELDS =
    StringRef::from_lit("max-request-header-fields");
constexpr auto SHRPX_OPT_RESPONSE_HEADER_FIELD_BUFFER =
    StringRef::from_lit("response-header-field-buffer");
constexpr auto SHRPX_OPT_MAX_RESPONSE_HEADER_FIELDS =
    StringRef::from_lit("max-response-header-fields");
constexpr auto SHRPX_OPT_NO_HTTP2_CIPHER_BLACK_LIST =
    StringRef::from_lit("no-http2-cipher-black-list");
constexpr auto SHRPX_OPT_BACKEND_HTTP1_TLS =
    StringRef::from_lit("backend-http1-tls");
constexpr auto SHRPX_OPT_TLS_SESSION_CACHE_MEMCACHED_TLS =
    StringRef::from_lit("tls-session-cache-memcached-tls");
constexpr auto SHRPX_OPT_TLS_SESSION_CACHE_MEMCACHED_CERT_FILE =
    StringRef::from_lit("tls-session-cache-memcached-cert-file");
constexpr auto SHRPX_OPT_TLS_SESSION_CACHE_MEMCACHED_PRIVATE_KEY_FILE =
    StringRef::from_lit("tls-session-cache-memcached-private-key-file");
constexpr auto SHRPX_OPT_TLS_SESSION_CACHE_MEMCACHED_ADDRESS_FAMILY =
    StringRef::from_lit("tls-session-cache-memcached-address-family");
constexpr auto SHRPX_OPT_TLS_TICKET_KEY_MEMCACHED_TLS =
    StringRef::from_lit("tls-ticket-key-memcached-tls");
constexpr auto SHRPX_OPT_TLS_TICKET_KEY_MEMCACHED_CERT_FILE =
    StringRef::from_lit("tls-ticket-key-memcached-cert-file");
constexpr auto SHRPX_OPT_TLS_TICKET_KEY_MEMCACHED_PRIVATE_KEY_FILE =
    StringRef::from_lit("tls-ticket-key-memcached-private-key-file");
constexpr auto SHRPX_OPT_TLS_TICKET_KEY_MEMCACHED_ADDRESS_FAMILY =
    StringRef::from_lit("tls-ticket-key-memcached-address-family");
constexpr auto SHRPX_OPT_BACKEND_ADDRESS_FAMILY =
    StringRef::from_lit("backend-address-family");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_MAX_CONCURRENT_STREAMS =
    StringRef::from_lit("frontend-http2-max-concurrent-streams");
constexpr auto SHRPX_OPT_BACKEND_HTTP2_MAX_CONCURRENT_STREAMS =
    StringRef::from_lit("backend-http2-max-concurrent-streams");
constexpr auto SHRPX_OPT_BACKEND_CONNECTIONS_PER_FRONTEND =
    StringRef::from_lit("backend-connections-per-frontend");
constexpr auto SHRPX_OPT_BACKEND_TLS = StringRef::from_lit("backend-tls");
constexpr auto SHRPX_OPT_BACKEND_CONNECTIONS_PER_HOST =
    StringRef::from_lit("backend-connections-per-host");
constexpr auto SHRPX_OPT_ERROR_PAGE = StringRef::from_lit("error-page");
constexpr auto SHRPX_OPT_NO_KQUEUE = StringRef::from_lit("no-kqueue");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_SETTINGS_TIMEOUT =
    StringRef::from_lit("frontend-http2-settings-timeout");
constexpr auto SHRPX_OPT_BACKEND_HTTP2_SETTINGS_TIMEOUT =
    StringRef::from_lit("backend-http2-settings-timeout");
constexpr auto SHRPX_OPT_API_MAX_REQUEST_BODY =
    StringRef::from_lit("api-max-request-body");
constexpr auto SHRPX_OPT_BACKEND_MAX_BACKOFF =
    StringRef::from_lit("backend-max-backoff");
constexpr auto SHRPX_OPT_SERVER_NAME = StringRef::from_lit("server-name");
constexpr auto SHRPX_OPT_NO_SERVER_REWRITE =
    StringRef::from_lit("no-server-rewrite");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_OPTIMIZE_WRITE_BUFFER_SIZE =
    StringRef::from_lit("frontend-http2-optimize-write-buffer-size");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_OPTIMIZE_WINDOW_SIZE =
    StringRef::from_lit("frontend-http2-optimize-window-size");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_WINDOW_SIZE =
    StringRef::from_lit("frontend-http2-window-size");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_CONNECTION_WINDOW_SIZE =
    StringRef::from_lit("frontend-http2-connection-window-size");
constexpr auto SHRPX_OPT_BACKEND_HTTP2_WINDOW_SIZE =
    StringRef::from_lit("backend-http2-window-size");
constexpr auto SHRPX_OPT_BACKEND_HTTP2_CONNECTION_WINDOW_SIZE =
    StringRef::from_lit("backend-http2-connection-window-size");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_ENCODER_DYNAMIC_TABLE_SIZE =
    StringRef::from_lit("frontend-http2-encoder-dynamic-table-size");
constexpr auto SHRPX_OPT_FRONTEND_HTTP2_DECODER_DYNAMIC_TABLE_SIZE =
    StringRef::from_lit("frontend-http2-decoder-dynamic-table-size");
constexpr auto SHRPX_OPT_BACKEND_HTTP2_ENCODER_DYNAMIC_TABLE_SIZE =
    StringRef::from_lit("backend-http2-encoder-dynamic-table-size");
constexpr auto SHRPX_OPT_BACKEND_HTTP2_DECODER_DYNAMIC_TABLE_SIZE =
    StringRef::from_lit("backend-http2-decoder-dynamic-table-size");
constexpr auto SHRPX_OPT_ECDH_CURVES = StringRef::from_lit("ecdh-curves");
constexpr auto SHRPX_OPT_TLS_SCT_DIR = StringRef::from_lit("tls-sct-dir");
constexpr auto SHRPX_OPT_BACKEND_CONNECT_TIMEOUT =
    StringRef::from_lit("backend-connect-timeout");
constexpr auto SHRPX_OPT_DNS_CACHE_TIMEOUT =
    StringRef::from_lit("dns-cache-timeout");
constexpr auto SHRPX_OPT_DNS_LOOKUP_TIMEOUT =
    StringRef::from_lit("dns-lookup-timeout");
constexpr auto SHRPX_OPT_DNS_MAX_TRY = StringRef::from_lit("dns-max-try");
constexpr auto SHRPX_OPT_FRONTEND_KEEP_ALIVE_TIMEOUT =
    StringRef::from_lit("frontend-keep-alive-timeout");
constexpr auto SHRPX_OPT_PSK_SECRETS = StringRef::from_lit("psk-secrets");
constexpr auto SHRPX_OPT_CLIENT_PSK_SECRETS =
    StringRef::from_lit("client-psk-secrets");
constexpr auto SHRPX_OPT_CLIENT_NO_HTTP2_CIPHER_BLACK_LIST =
    StringRef::from_lit("client-no-http2-cipher-black-list");
constexpr auto SHRPX_OPT_CLIENT_CIPHERS = StringRef::from_lit("client-ciphers");
constexpr auto SHRPX_OPT_ACCESSLOG_WRITE_EARLY =
    StringRef::from_lit("accesslog-write-early");
constexpr auto SHRPX_OPT_TLS_MIN_PROTO_VERSION =
    StringRef::from_lit("tls-min-proto-version");
constexpr auto SHRPX_OPT_TLS_MAX_PROTO_VERSION =
    StringRef::from_lit("tls-max-proto-version");
constexpr auto SHRPX_OPT_REDIRECT_HTTPS_PORT =
    StringRef::from_lit("redirect-https-port");
constexpr auto SHRPX_OPT_FRONTEND_MAX_REQUESTS =
    StringRef::from_lit("frontend-max-requests");
constexpr auto SHRPX_OPT_SINGLE_THREAD = StringRef::from_lit("single-thread");
constexpr auto SHRPX_OPT_SINGLE_PROCESS = StringRef::from_lit("single-process");
constexpr auto SHRPX_OPT_NO_ADD_X_FORWARDED_PROTO =
    StringRef::from_lit("no-add-x-forwarded-proto");
constexpr auto SHRPX_OPT_NO_STRIP_INCOMING_X_FORWARDED_PROTO =
    StringRef::from_lit("no-strip-incoming-x-forwarded-proto");
constexpr auto SHRPX_OPT_OCSP_STARTUP = StringRef::from_lit("ocsp-startup");
constexpr auto SHRPX_OPT_NO_VERIFY_OCSP = StringRef::from_lit("no-verify-ocsp");
constexpr auto SHRPX_OPT_VERIFY_CLIENT_TOLERATE_EXPIRED =
    StringRef::from_lit("verify-client-tolerate-expired");
constexpr auto SHRPX_OPT_IGNORE_PER_PATTERN_MRUBY_ERROR =
    StringRef::from_lit("ignore-per-pattern-mruby-error");
constexpr auto SHRPX_OPT_TLS_NO_POSTPONE_EARLY_DATA =
    StringRef::from_lit("tls-no-postpone-early-data");
constexpr auto SHRPX_OPT_TLS_MAX_EARLY_DATA =
    StringRef::from_lit("tls-max-early-data");
constexpr auto SHRPX_OPT_TLS13_CIPHERS = StringRef::from_lit("tls13-ciphers");
constexpr auto SHRPX_OPT_TLS13_CLIENT_CIPHERS =
    StringRef::from_lit("tls13-client-ciphers");
constexpr auto SHRPX_OPT_NO_STRIP_INCOMING_EARLY_DATA =
    StringRef::from_lit("no-strip-incoming-early-data");

constexpr size_t SHRPX_OBFUSCATED_NODE_LENGTH = 8;

constexpr char DEFAULT_DOWNSTREAM_HOST[] = "127.0.0.1";
constexpr int16_t DEFAULT_DOWNSTREAM_PORT = 80;

enum class Proto {
  NONE,
  HTTP1,
  HTTP2,
  MEMCACHED,
};

enum class SessionAffinity {
  // 无会话相关性
  NONE,
  // 客户端IP关联
  IP,
  // 基于Cookie的相关性
  COOKIE,
};

enum class SessionAffinityCookieSecure {
  // 会话相关性cookie的安全属性由
  // 请求方案。
  AUTO,
  // 始终设置会话相关性cookie的安全属性。
  YES,
  // 会话相关性cookie的安全属性始终未设置。
  NO,
};

struct AffinityConfig {
  // 会话关联的类型。
  SessionAffinity type;
  struct {
    // 要使用的cookie的名称。
    StringRef name;
    // 应用cookie的路径。
    StringRef path;
    // 安全属性
    SessionAffinityCookieSecure secure;
  } cookie;
};

enum shrpx_forwarded_param {
  FORWARDED_NONE = 0,
  FORWARDED_BY = 0x1,
  FORWARDED_FOR = 0x2,
  FORWARDED_HOST = 0x4,
  FORWARDED_PROTO = 0x8,
};

enum class ForwardedNode {
  OBFUSCATED,
  IP,
};

struct AltSvc {
  StringRef protocol_id, host, origin, service;

  uint16_t port;
};

enum class UpstreamAltMode {
  // 无替代模式
  NONE,
  // API处理模式
  API,
  // 健康监测模式
  HEALTHMON,
};

struct UpstreamAddr {
  // 前端地址（例如，FQDN、主机名、IP地址）。如果
  // |host_unix|为true，这是unix域套接字路径。这必须
  // 是以NULL结尾的字符串。
  StringRef host;
  // 对于TCP套接字，这是＜IP地址＞：＜端口＞。对于IPv6地址，
  // 地址用方括号括起来。如果套接字是UNIX
  // 域套接字，这是“localhost”。
  StringRef hostport;
  // 如果|host_unix|为true，则为前端端口.0。
  uint16_t port;
  // 对于TCP套接字，这是AF_INET或AF_INET6。对于UNIX
  // 域套接字，这是0。
  int family;
  // 备用模式
  UpstreamAltMode alt_mode;
  // 如果|host|包含UNIX域套接字路径，则为true。
  bool host_unix;
  // 如果启用TLS，则为true。
  bool tls;
  // 如果在选择后端时应将SNI主机用作主机，则为true
  // 服务器
  bool sni_fwd;
  // 如果客户端应该发送PROXY协议v1报头，则为true。
  bool accept_proxy_protocol;
  int fd;
};

struct DownstreamAddrConfig {
  // 如果|dns|为false，则解析地址
  Address addr;
  // 后端地址。如果|host_unix|为true，则这是unix域
  // 套接字路径。这必须是以NULL结尾的字符串。
  StringRef host;
  // <主机>：<端口>。这并不特别对待80和443。如果
  // |host_unix|为true，这是“localhost”。
  StringRef hostport;
  // 主机名作为SNI字段发送
  StringRef sni;
  // 此地址所属组的名称。
  StringRef group;
  size_t fall;
  size_t rise;
  // 权重组中此地址的权重。其范围为[1，
  // 256]（含）。
  uint32_t weight;
  // 重量组的重量。其范围为[1256]（含）。
  uint32_t group_weight;
  // 此组中使用的应用程序协议
  Proto proto;
  // 如果|host_unix|为true，则为后端端口.0。
  uint16_t port;
  // 如果|host|包含UNIX域套接字路径，则为true。
  bool host_unix;
  bool tls;
  // 如果启用了动态DNS，则为true
  bool dns;
  // true if：scheme伪标头字段应升级为安全
  // 将请求转发到后端时的变体（例如“https”）
  // 通过TLS连接连接。
  bool upgrade_scheme;
};

// 将哈希映射到idx，idx是
// 下游AddrGroupConfig:：addrs。
struct AffinityHash {
  AffinityHash(size_t idx, uint32_t hash) : idx(idx), hash(hash) {}

  size_t idx;
  uint32_t hash;
};

struct DownstreamAddrGroupConfig {
  DownstreamAddrGroupConfig(const StringRef &pattern)
      : pattern(pattern),
        affinity{SessionAffinity::NONE},
        redirect_if_not_tls(false),
        timeout{} {}

  StringRef pattern;
  StringRef mruby_file;
  std::vector<DownstreamAddrConfig> addrs;
  // 一堆会话关联哈希。仅在关联时使用==
  // SessionAffinity:：IP。
  std::vector<AffinityHash> affinity_hash;
  // 基于Cookie的会话相关性配置。
  AffinityConfig affinity;
  // 如果该组要求客户端连接必须是TLS，
  // 并且请求必须重定向到https URI。
  bool redirect_if_not_tls;
  // 后端连接超时。
  struct {
    ev_tstamp read;
    ev_tstamp write;
  } timeout;
};

struct TicketKey {
  const EVP_CIPHER *cipher;
  const EVP_MD *hmac;
  size_t hmac_keylen;
  struct {
    // 此票证配置的名称
    std::array<uint8_t, 16> name;
    // |密码的加密密钥|
    std::array<uint8_t, 32> enc_key;
    // | hmac的hmac键|
    std::array<uint8_t, 32> hmac_key;
  } data;
};

struct TicketKeys {
  ~TicketKeys();
  std::vector<TicketKey> keys;
};

struct TLSCertificate {
  TLSCertificate(StringRef private_key_file, StringRef cert_file,
                 std::vector<uint8_t> sct_data)
      : private_key_file(std::move(private_key_file)),
        cert_file(std::move(cert_file)),
        sct_data(std::move(sct_data)) {}

  StringRef private_key_file;
  StringRef cert_file;
  std::vector<uint8_t> sct_data;
};

struct HttpProxy {
  Address addr;
  // http代理URI中的主机
  StringRef host;
  // http代理URI中的userinfo，而不是百分比编码形式
  StringRef userinfo;
  // http代理URI中的端口
  uint16_t port;
};

struct TLSConfig {
  // RFC 5077会话票证相关配置
  struct {
    struct {
      Address addr;
      uint16_t port;
      // memcached服务器的主机名。这也用作SNI字段
      // 如果TLS已启用。
      StringRef host;
      // 用于身份验证的客户端私钥和证书
      StringRef private_key_file;
      StringRef cert_file;
      ev_tstamp interval;
      // 从获取TLS票证密钥时的最大重试次数
      // mamcached，由于网络错误。
      size_t max_retry;
      // 当发生以下情况时，memcached中的最大连续错误数
      // 已达到限制，TLS票证已禁用。
      size_t max_fail;
      // memcached连接的地址系列。其中之一
      // AF_INET、AF_INET6或AF_UNSPEC。
      int family;
      bool tls;
    } memcached;
    std::vector<StringRef> files;
    const EVP_CIPHER *cipher;
    // 如果使用了tls票证密钥密码，则为true
    bool cipher_given;
  } ticket;

  // 会话缓存相关配置
  struct {
    struct {
      Address addr;
      uint16_t port;
      // memcached服务器的主机名。这也用作SNI字段
      // 如果TLS已启用。
      StringRef host;
      // 用于身份验证的客户端私钥和证书
      StringRef private_key_file;
      StringRef cert_file;
      // memcached连接的地址系列。其中之一
      // AF_INET、AF_INET6或AF_UNSPEC。
      int family;
      bool tls;
    } memcached;
  } session_cache;

  // 动态记录大小调整配置
  struct {
    size_t warmup_threshold;
    ev_tstamp idle_timeout;
  } dyn_rec;

  // OCSP重新分配的配置
  struct {
    ev_tstamp update_interval;
    StringRef fetch_ocsp_response_file;
    bool disabled;
    bool startup;
    bool no_verify;
  } ocsp;

  // 客户端验证配置
  struct {
    // 包含仅用于客户端的CA证书的文件路径
    // 证书验证
    StringRef cacert;
    bool enabled;
    // 如果我们接受过期的客户端证书，则为true。
    bool tolerate_expired;
  } client_verify;

  // 客户端（后端连接）TLS配置。
  struct {
    // 客户端PSK配置
    struct {
      // 标识必须是以NULL结尾的字符串。
      StringRef identity;
      StringRef secret;
    } psk;
    StringRef private_key_file;
    StringRef cert_file;
    StringRef ciphers;
    StringRef tls13_ciphers;
    bool no_http2_cipher_black_list;
  } client;

  // PSK机密。密钥是identity，关联的值是
  // 它的秘密。
  std::map<StringRef, StringRef> psk_secrets;
  // 其他TLS证书对的列表
  std::vector<TLSCertificate> subcerts;
  std::vector<unsigned char> alpn_prefs;
  // 支持的NPN/ALPN协议字符串列表，顺序为
  // 偏爱
  std::vector<StringRef> npn_list;
  // 受支持的SSL/TLS协议字符串列表。
  std::vector<StringRef> tls_proto_list;
  std::vector<uint8_t> sct_data;
  BIO_METHOD *bio_method;
  // 用于禁用SSL/TLS协议版本的位掩码。这将是
  // 传递给SSL_CTX_set_options（）。
  long int tls_proto_mask;
  StringRef backend_sni_name;
  std::chrono::seconds session_timeout;
  StringRef private_key_file;
  StringRef private_key_passwd;
  StringRef cert_file;
  StringRef dh_param_file;
  StringRef ciphers;
  StringRef tls13_ciphers;
  StringRef ecdh_curves;
  StringRef cacert;
  // 服务器接受的最大0-RTT数据量。
  uint32_t max_early_data;
  // 最低和最高TLS版本。这些值在中定义
  // OpenSSL头文件。
  int min_proto_version;
  int max_proto_version;
  bool insecure;
  bool no_http2_cipher_black_list;
  // 如果TLS早期数据中包含的转发请求不应为true
  // 直到TLS握手完成。
  bool no_postpone_early_data;
};

// 自定义错误页
struct ErrorPage {
  // 非NULL终止
  std::vector<uint8_t> content;
  // 0是特殊值，它匹配所有HTTP状态代码。
  unsigned int http_status;
};

struct HttpConfig {
  struct {
    // Forwarded标头的“by”参数中使用的模糊值
    // 领域这仅在用户定义的静态混淆时使用
    // 提供字符串。
    StringRef by_obfuscated;
    // 一个或多个shrpx_forwarded_param值的逐位或。
    uint32_t params;
    // Forwarded标头的“by”参数中记录的值类型
    // 领域
    ForwardedNode by_node_type;
    // Forwarded标头的“for”参数中记录的值类型
    // 领域
    ForwardedNode for_node_type;
    bool strip_incoming;
  } forwarded;
  struct {
    bool add;
    bool strip_incoming;
  } xff;
  struct {
    bool add;
    bool strip_incoming;
  } xfp;
  struct {
    bool strip_incoming;
  } early_data;
  std::vector<AltSvc> altsvcs;
  std::vector<ErrorPage> error_pages;
  HeaderRefs add_request_headers;
  HeaderRefs add_response_headers;
  StringRef server_name;
  // https时出现在位置标头字段中的端口号
  // 进行重定向。
  StringRef redirect_https_port;
  size_t request_header_field_buffer;
  size_t max_request_header_fields;
  size_t response_header_field_buffer;
  size_t max_response_header_fields;
  size_t max_requests;
  bool no_via;
  bool no_location_rewrite;
  bool no_host_rewrite;
  bool no_server_rewrite;
};

struct Http2Config {
  struct {
    struct {
      struct {
        StringRef request_header_file;
        StringRef response_header_file;
        FILE *request_header;
        FILE *response_header;
      } dump;
      bool frame_debug;
    } debug;
    struct {
      ev_tstamp settings;
    } timeout;
    nghttp2_option *option;
    nghttp2_option *alt_mode_option;
    nghttp2_session_callbacks *callbacks;
    size_t max_concurrent_streams;
    size_t encoder_dynamic_table_size;
    size_t decoder_dynamic_table_size;
    int32_t window_size;
    int32_t connection_window_size;
    bool optimize_write_buffer_size;
    bool optimize_window_size;
  } upstream;
  struct {
    struct {
      ev_tstamp settings;
    } timeout;
    nghttp2_option *option;
    nghttp2_session_callbacks *callbacks;
    size_t encoder_dynamic_table_size;
    size_t decoder_dynamic_table_size;
    int32_t window_size;
    int32_t connection_window_size;
    size_t max_concurrent_streams;
  } downstream;
  struct {
    ev_tstamp stream_read;
    ev_tstamp stream_write;
  } timeout;
  bool no_cookie_crumbling;
  bool no_server_push;
};

struct LoggingConfig {
  struct {
    std::vector<LogFragment> format;
    StringRef file;
    // 将accesslog发送到syslog，忽略accesslog_file。
    bool syslog;
    // 从收到响应标头时写入accesslog
    // 而不是响应体。
    bool write_early;
  } access;
  struct {
    StringRef file;
    // 将errorlog发送到syslog，忽略errorlog_file。
    bool syslog;
  } error;
  int syslog_facility;
  int severity;
};

struct RateLimitConfig {
  size_t rate;
  size_t burst;
};

// 通配符主机模式路由。我们从主机上删除了最左边的“*”
// 领域路由器包括共享相同通配符的所有路径模式
// 主办
struct WildcardPattern {
  WildcardPattern(const StringRef &host) : host(host) {}

  // 这可能不是以NULL结尾的。目前仅用于
  // 比较
  StringRef host;
  Router router;
};

// 选择后端以转发请求的配置
struct RouterConfig {
  Router router;
  // 反向通配符主机的路由器。由于此路由器具有
  // 通配符主机在没有“*”的情况下反转，应调用match（）
  // 具有反转主机剥离最后一个字符的函数。这是
  // 因为我们要求至少有一个字符必须与“*”匹配。
  // 此路由器中存储的索引是通配符模式的索引。
  Router rev_wildcard_router;
  std::vector<WildcardPattern> wildcard_patterns;
};

struct DownstreamConfig {
  DownstreamConfig()
      : balloc(1024, 1024),
        timeout{},
        addr_group_catch_all{0},
        connections_per_host{0},
        connections_per_frontend{0},
        request_buffer_size{0},
        response_buffer_size{0},
        family{0} {}

  DownstreamConfig(const DownstreamConfig &) = delete;
  DownstreamConfig(DownstreamConfig &&) = delete;
  DownstreamConfig &operator=(const DownstreamConfig &) = delete;
  DownstreamConfig &operator=(DownstreamConfig &&) = delete;

  // 为下游配置分配内存的分配器。自从
  // 我们可以在任意时间使用API交换DownstreamConfig
  // 调用，我们应该使用它们自己的分配器，而不是每个Config
  // 分配器。
  BlockAllocator balloc;
  struct {
    ev_tstamp read;
    ev_tstamp write;
    ev_tstamp idle_read;
    ev_tstamp connect;
    // 检查脱机运行状况检查时的最大回退
    // 后端或从负载平衡分离失败的后端时
    // 临时组。
    ev_tstamp max_backoff;
  } timeout;
  RouterConfig router;
  std::vector<DownstreamAddrGroupConfig> addr_groups;
  // downstream_addr_groups中捕获所有组的索引。
  size_t addr_group_catch_all;
  size_t connections_per_host;
  size_t connections_per_frontend;
  size_t request_buffer_size;
  size_t response_buffer_size;
  // 后端连接的地址系列。AF_ NET，
  // AF_INET6或AF_UNSPEC。如果后端连接被忽略
  // 通过Unix域套接字进行。
  int family;
};

struct ConnectionConfig {
  struct {
    struct {
      ev_tstamp sleep;
    } timeout;
    // 前端接收方地址
    std::vector<UpstreamAddr> addrs;
    int backlog;
    // TCP快速打开。如果这是肯定的，则传递给
    // setsockopt（）以及TCP_FASTOPEN。
    int fastopen;
  } listener;

  struct {
    struct {
      ev_tstamp http2_read;
      ev_tstamp read;
      ev_tstamp write;
      ev_tstamp idle_read;
    } timeout;
    struct {
      RateLimitConfig read;
      RateLimitConfig write;
    } ratelimit;
    size_t worker_connections;
    // 已弃用。请参阅UpstreamAddr.accept_proxy_protocol。
    bool accept_proxy_protocol;
  } upstream;

  std::shared_ptr<DownstreamConfig> downstream;
};

struct APIConfig {
  // 一个API请求的最大请求体大小
  size_t max_request_body;
  // 如果至少有一个UpstreamAddr启用了api，则为true
  bool enabled;
};

struct DNSConfig {
  struct {
    ev_tstamp cache;
    ev_tstamp lookup;
  } timeout;
  // 名称解析程序放弃前的尝试次数
  // 要求
  size_t max_try;
};

struct Config {
  Config()
      : balloc(4096, 4096),
        downstream_http_proxy{},
        http{},
        http2{},
        tls{},
        logging{},
        conn{},
        api{},
        dns{},
        config_revision{0},
        num_worker{0},
        padding{0},
        rlimit_nofile{0},
        uid{0},
        gid{0},
        pid{0},
        verbose{false},
        daemon{false},
        http2_proxy{false},
        single_process{false},
        single_thread{false},
        ignore_per_pattern_mruby_error{false},
        ev_loop_flags{0} {}
  ~Config();

  Config(Config &&) = delete;
  Config(const Config &&) = delete;
  Config &operator=(Config &&) = delete;
  Config &operator=(const Config &&) = delete;

  // 为该对象分配内存的分配器
  // 下游配置。当前，它用于为
  // 串。
  BlockAllocator balloc;
  HttpProxy downstream_http_proxy;
  HttpConfig http;
  Http2Config http2;
  TLSConfig tls;
  LoggingConfig logging;
  ConnectionConfig conn;
  APIConfig api;
  DNSConfig dns;
  StringRef pid_file;
  StringRef conf_path;
  StringRef user;
  StringRef mruby_file;
  // 不透明字符串的配置修订，以及更改
  // 在每次重新加载配置时。这不会在
  // backendconfig API调用。此值在运行状况检查中返回
  // 作为“nghttpx conf rev”响应头字段。外部
  // 程序可以检查该值以了解重新加载是否具有
  // 是否完成。
  uint64_t config_revision;
  size_t num_worker;
  size_t padding;
  size_t rlimit_nofile;
  uid_t uid;
  gid_t gid;
  pid_t pid;
  bool verbose;
  bool daemon;
  bool http2_proxy;
  // 在单进程模式下运行nghttpx。在此模式下，信号
  // 省略了处理。
  bool single_process;
  bool single_thread;
  // 忽略每个模式mruby脚本的mruby编译错误。
  bool ignore_per_pattern_mruby_error;
  // 传递给ev_default_loop（）和ev_loop_new（）的标志
  int ev_loop_flags;
};

const Config *get_config();
Config *mod_config();
// 用给定的|new_config|替换当前配置。旧配置是
// 返回。
std::unique_ptr<Config> replace_config(std::unique_ptr<Config> new_config);
void create_config();

// 由gennghttpxfun.py生成
enum {
  SHRPX_OPTID_ACCEPT_PROXY_PROTOCOL,
  SHRPX_OPTID_ACCESSLOG_FILE,
  SHRPX_OPTID_ACCESSLOG_FORMAT,
  SHRPX_OPTID_ACCESSLOG_SYSLOG,
  SHRPX_OPTID_ACCESSLOG_WRITE_EARLY,
  SHRPX_OPTID_ADD_FORWARDED,
  SHRPX_OPTID_ADD_REQUEST_HEADER,
  SHRPX_OPTID_ADD_RESPONSE_HEADER,
  SHRPX_OPTID_ADD_X_FORWARDED_FOR,
  SHRPX_OPTID_ALTSVC,
  SHRPX_OPTID_API_MAX_REQUEST_BODY,
  SHRPX_OPTID_BACKEND,
  SHRPX_OPTID_BACKEND_ADDRESS_FAMILY,
  SHRPX_OPTID_BACKEND_CONNECT_TIMEOUT,
  SHRPX_OPTID_BACKEND_CONNECTIONS_PER_FRONTEND,
  SHRPX_OPTID_BACKEND_CONNECTIONS_PER_HOST,
  SHRPX_OPTID_BACKEND_HTTP_PROXY_URI,
  SHRPX_OPTID_BACKEND_HTTP1_CONNECTIONS_PER_FRONTEND,
  SHRPX_OPTID_BACKEND_HTTP1_CONNECTIONS_PER_HOST,
  SHRPX_OPTID_BACKEND_HTTP1_TLS,
  SHRPX_OPTID_BACKEND_HTTP2_CONNECTION_WINDOW_BITS,
  SHRPX_OPTID_BACKEND_HTTP2_CONNECTION_WINDOW_SIZE,
  SHRPX_OPTID_BACKEND_HTTP2_CONNECTIONS_PER_WORKER,
  SHRPX_OPTID_BACKEND_HTTP2_DECODER_DYNAMIC_TABLE_SIZE,
  SHRPX_OPTID_BACKEND_HTTP2_ENCODER_DYNAMIC_TABLE_SIZE,
  SHRPX_OPTID_BACKEND_HTTP2_MAX_CONCURRENT_STREAMS,
  SHRPX_OPTID_BACKEND_HTTP2_SETTINGS_TIMEOUT,
  SHRPX_OPTID_BACKEND_HTTP2_WINDOW_BITS,
  SHRPX_OPTID_BACKEND_HTTP2_WINDOW_SIZE,
  SHRPX_OPTID_BACKEND_IPV4,
  SHRPX_OPTID_BACKEND_IPV6,
  SHRPX_OPTID_BACKEND_KEEP_ALIVE_TIMEOUT,
  SHRPX_OPTID_BACKEND_MAX_BACKOFF,
  SHRPX_OPTID_BACKEND_NO_TLS,
  SHRPX_OPTID_BACKEND_READ_TIMEOUT,
  SHRPX_OPTID_BACKEND_REQUEST_BUFFER,
  SHRPX_OPTID_BACKEND_RESPONSE_BUFFER,
  SHRPX_OPTID_BACKEND_TLS,
  SHRPX_OPTID_BACKEND_TLS_SNI_FIELD,
  SHRPX_OPTID_BACKEND_WRITE_TIMEOUT,
  SHRPX_OPTID_BACKLOG,
  SHRPX_OPTID_CACERT,
  SHRPX_OPTID_CERTIFICATE_FILE,
  SHRPX_OPTID_CIPHERS,
  SHRPX_OPTID_CLIENT,
  SHRPX_OPTID_CLIENT_CERT_FILE,
  SHRPX_OPTID_CLIENT_CIPHERS,
  SHRPX_OPTID_CLIENT_NO_HTTP2_CIPHER_BLACK_LIST,
  SHRPX_OPTID_CLIENT_PRIVATE_KEY_FILE,
  SHRPX_OPTID_CLIENT_PROXY,
  SHRPX_OPTID_CLIENT_PSK_SECRETS,
  SHRPX_OPTID_CONF,
  SHRPX_OPTID_DAEMON,
  SHRPX_OPTID_DH_PARAM_FILE,
  SHRPX_OPTID_DNS_CACHE_TIMEOUT,
  SHRPX_OPTID_DNS_LOOKUP_TIMEOUT,
  SHRPX_OPTID_DNS_MAX_TRY,
  SHRPX_OPTID_ECDH_CURVES,
  SHRPX_OPTID_ERROR_PAGE,
  SHRPX_OPTID_ERRORLOG_FILE,
  SHRPX_OPTID_ERRORLOG_SYSLOG,
  SHRPX_OPTID_FASTOPEN,
  SHRPX_OPTID_FETCH_OCSP_RESPONSE_FILE,
  SHRPX_OPTID_FORWARDED_BY,
  SHRPX_OPTID_FORWARDED_FOR,
  SHRPX_OPTID_FRONTEND,
  SHRPX_OPTID_FRONTEND_FRAME_DEBUG,
  SHRPX_OPTID_FRONTEND_HTTP2_CONNECTION_WINDOW_BITS,
  SHRPX_OPTID_FRONTEND_HTTP2_CONNECTION_WINDOW_SIZE,
  SHRPX_OPTID_FRONTEND_HTTP2_DECODER_DYNAMIC_TABLE_SIZE,
  SHRPX_OPTID_FRONTEND_HTTP2_DUMP_REQUEST_HEADER,
  SHRPX_OPTID_FRONTEND_HTTP2_DUMP_RESPONSE_HEADER,
  SHRPX_OPTID_FRONTEND_HTTP2_ENCODER_DYNAMIC_TABLE_SIZE,
  SHRPX_OPTID_FRONTEND_HTTP2_MAX_CONCURRENT_STREAMS,
  SHRPX_OPTID_FRONTEND_HTTP2_OPTIMIZE_WINDOW_SIZE,
  SHRPX_OPTID_FRONTEND_HTTP2_OPTIMIZE_WRITE_BUFFER_SIZE,
  SHRPX_OPTID_FRONTEND_HTTP2_READ_TIMEOUT,
  SHRPX_OPTID_FRONTEND_HTTP2_SETTINGS_TIMEOUT,
  SHRPX_OPTID_FRONTEND_HTTP2_WINDOW_BITS,
  SHRPX_OPTID_FRONTEND_HTTP2_WINDOW_SIZE,
  SHRPX_OPTID_FRONTEND_KEEP_ALIVE_TIMEOUT,
  SHRPX_OPTID_FRONTEND_MAX_REQUESTS,
  SHRPX_OPTID_FRONTEND_NO_TLS,
  SHRPX_OPTID_FRONTEND_READ_TIMEOUT,
  SHRPX_OPTID_FRONTEND_WRITE_TIMEOUT,
  SHRPX_OPTID_HEADER_FIELD_BUFFER,
  SHRPX_OPTID_HOST_REWRITE,
  SHRPX_OPTID_HTTP2_BRIDGE,
  SHRPX_OPTID_HTTP2_MAX_CONCURRENT_STREAMS,
  SHRPX_OPTID_HTTP2_NO_COOKIE_CRUMBLING,
  SHRPX_OPTID_HTTP2_PROXY,
  SHRPX_OPTID_IGNORE_PER_PATTERN_MRUBY_ERROR,
  SHRPX_OPTID_INCLUDE,
  SHRPX_OPTID_INSECURE,
  SHRPX_OPTID_LISTENER_DISABLE_TIMEOUT,
  SHRPX_OPTID_LOG_LEVEL,
  SHRPX_OPTID_MAX_HEADER_FIELDS,
  SHRPX_OPTID_MAX_REQUEST_HEADER_FIELDS,
  SHRPX_OPTID_MAX_RESPONSE_HEADER_FIELDS,
  SHRPX_OPTID_MRUBY_FILE,
  SHRPX_OPTID_NO_ADD_X_FORWARDED_PROTO,
  SHRPX_OPTID_NO_HOST_REWRITE,
  SHRPX_OPTID_NO_HTTP2_CIPHER_BLACK_LIST,
  SHRPX_OPTID_NO_KQUEUE,
  SHRPX_OPTID_NO_LOCATION_REWRITE,
  SHRPX_OPTID_NO_OCSP,
  SHRPX_OPTID_NO_SERVER_PUSH,
  SHRPX_OPTID_NO_SERVER_REWRITE,
  SHRPX_OPTID_NO_STRIP_INCOMING_EARLY_DATA,
  SHRPX_OPTID_NO_STRIP_INCOMING_X_FORWARDED_PROTO,
  SHRPX_OPTID_NO_VERIFY_OCSP,
  SHRPX_OPTID_NO_VIA,
  SHRPX_OPTID_NPN_LIST,
  SHRPX_OPTID_OCSP_STARTUP,
  SHRPX_OPTID_OCSP_UPDATE_INTERVAL,
  SHRPX_OPTID_PADDING,
  SHRPX_OPTID_PID_FILE,
  SHRPX_OPTID_PRIVATE_KEY_FILE,
  SHRPX_OPTID_PRIVATE_KEY_PASSWD_FILE,
  SHRPX_OPTID_PSK_SECRETS,
  SHRPX_OPTID_READ_BURST,
  SHRPX_OPTID_READ_RATE,
  SHRPX_OPTID_REDIRECT_HTTPS_PORT,
  SHRPX_OPTID_REQUEST_HEADER_FIELD_BUFFER,
  SHRPX_OPTID_RESPONSE_HEADER_FIELD_BUFFER,
  SHRPX_OPTID_RLIMIT_NOFILE,
  SHRPX_OPTID_SERVER_NAME,
  SHRPX_OPTID_SINGLE_PROCESS,
  SHRPX_OPTID_SINGLE_THREAD,
  SHRPX_OPTID_STREAM_READ_TIMEOUT,
  SHRPX_OPTID_STREAM_WRITE_TIMEOUT,
  SHRPX_OPTID_STRIP_INCOMING_FORWARDED,
  SHRPX_OPTID_STRIP_INCOMING_X_FORWARDED_FOR,
  SHRPX_OPTID_SUBCERT,
  SHRPX_OPTID_SYSLOG_FACILITY,
  SHRPX_OPTID_TLS_DYN_REC_IDLE_TIMEOUT,
  SHRPX_OPTID_TLS_DYN_REC_WARMUP_THRESHOLD,
  SHRPX_OPTID_TLS_MAX_EARLY_DATA,
  SHRPX_OPTID_TLS_MAX_PROTO_VERSION,
  SHRPX_OPTID_TLS_MIN_PROTO_VERSION,
  SHRPX_OPTID_TLS_NO_POSTPONE_EARLY_DATA,
  SHRPX_OPTID_TLS_PROTO_LIST,
  SHRPX_OPTID_TLS_SCT_DIR,
  SHRPX_OPTID_TLS_SESSION_CACHE_MEMCACHED,
  SHRPX_OPTID_TLS_SESSION_CACHE_MEMCACHED_ADDRESS_FAMILY,
  SHRPX_OPTID_TLS_SESSION_CACHE_MEMCACHED_CERT_FILE,
  SHRPX_OPTID_TLS_SESSION_CACHE_MEMCACHED_PRIVATE_KEY_FILE,
  SHRPX_OPTID_TLS_SESSION_CACHE_MEMCACHED_TLS,
  SHRPX_OPTID_TLS_TICKET_KEY_CIPHER,
  SHRPX_OPTID_TLS_TICKET_KEY_FILE,
  SHRPX_OPTID_TLS_TICKET_KEY_MEMCACHED,
  SHRPX_OPTID_TLS_TICKET_KEY_MEMCACHED_ADDRESS_FAMILY,
  SHRPX_OPTID_TLS_TICKET_KEY_MEMCACHED_CERT_FILE,
  SHRPX_OPTID_TLS_TICKET_KEY_MEMCACHED_INTERVAL,
  SHRPX_OPTID_TLS_TICKET_KEY_MEMCACHED_MAX_FAIL,
  SHRPX_OPTID_TLS_TICKET_KEY_MEMCACHED_MAX_RETRY,
  SHRPX_OPTID_TLS_TICKET_KEY_MEMCACHED_PRIVATE_KEY_FILE,
  SHRPX_OPTID_TLS_TICKET_KEY_MEMCACHED_TLS,
  SHRPX_OPTID_TLS13_CIPHERS,
  SHRPX_OPTID_TLS13_CLIENT_CIPHERS,
  SHRPX_OPTID_USER,
  SHRPX_OPTID_VERIFY_CLIENT,
  SHRPX_OPTID_VERIFY_CLIENT_CACERT,
  SHRPX_OPTID_VERIFY_CLIENT_TOLERATE_EXPIRED,
  SHRPX_OPTID_WORKER_FRONTEND_CONNECTIONS,
  SHRPX_OPTID_WORKER_READ_BURST,
  SHRPX_OPTID_WORKER_READ_RATE,
  SHRPX_OPTID_WORKER_WRITE_BURST,
  SHRPX_OPTID_WORKER_WRITE_RATE,
  SHRPX_OPTID_WORKERS,
  SHRPX_OPTID_WRITE_BURST,
  SHRPX_OPTID_WRITE_RATE,
  SHRPX_OPTID_MAXIDX,
};

// 查找长度为|nameen|的给定选项名|name|的令牌。
int option_lookup_token(const char *name, size_t namelen);

// 分析选项名称|opt|和值|optarg|。结果是
// 存储到|config|指向的对象中。此函数返回0
// 如果成功，则返回-1。|included_set|包含所有路径
// 在处理此配置时已包含，以避免循环
// in--include选项。|pattern_addr_indexer|包含一对
// 后端模式及其在DownstreamConfig:：addr_groups中的索引。
// 它被引入以加速加载大量配置文件
// 后端。
int parse_config(Config *config, const StringRef &opt, const StringRef &optarg,
                 std::set<StringRef> &included_set,
                 std::map<StringRef, size_t> &pattern_addr_indexer);

// 类似于上面的parse_config（），但额外的|optid|
// 应该是option_lookup_token（opt）的返回值。
int parse_config(Config *config, int optid, const StringRef &opt,
                 const StringRef &optarg, std::set<StringRef> &included_set,
                 std::map<StringRef, size_t> &pattern_addr_indexer);

// 从|filename|加载配置并将其存储在|config|中。
// 如果成功，此函数返回0，或者返回-1。请参阅parse_config（）
// 对于|include_set|。
int load_config(Config *config, const char *filename,
                std::set<StringRef> &include_set,
                std::map<StringRef, size_t> &pattern_addr_indexer);

// 分析|optarg|中的头字段。我们希望标头字段已形成
// 如“名称：价值”。我们要求NAME是非空字符串。":"
// 允许在NAME开头，但NAME==“：”不允许
// 允许。此函数返回NAME和VALUE对。
HeaderRefs::value_type parse_header(BlockAllocator &balloc,
                                    const StringRef &optarg);

std::vector<LogFragment> parse_log_format(BlockAllocator &balloc,
                                          const StringRef &optarg);

// 返回syslog|facility|的字符串。
StringRef str_syslog_facility(int facility);

// 返回syslog|facility|string的整数值。
int int_syslog_facility(const StringRef &strfacility);

FILE *open_file_for_write(const char *filename);

// 读取|files|中的TLS票证密钥文件，并返回TicketKey
// 存储读取的密钥数据。给定的|cipher |和|hmac |决定
// 预期的文件大小。如果TicketKey
// success或nullptr。
std::unique_ptr<TicketKeys>
read_tls_ticket_key_file(const std::vector<StringRef> &files,
                         const EVP_CIPHER *cipher, const EVP_MD *hmac);

// 返回|proto|的字符串表示形式。
StringRef strproto(Proto proto);

int configure_downstream_group(Config *config, bool http2_proxy,
                               bool numeric_addr_only,
                               const TLSConfig &tlsconf);

int resolve_hostname(Address *addr, const char *hostname, uint16_t port,
                     int family, int additional_flags = 0);

} // 命名空间shrpx

#endif // SHRPX_CONFIG_H

