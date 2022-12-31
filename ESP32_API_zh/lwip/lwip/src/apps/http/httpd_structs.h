#ifndef LWIP_HTTPD_STRUCTS_H
#define LWIP_HTTPD_STRUCTS_H

#include "lwip/apps/httpd.h"

#if LWIP_HTTPD_DYNAMIC_HEADERS
/**此结构用于各种文件扩展名的HTTP头字符串列表。*/
typedef struct {
  const char *extension;
  const char *content_type;
} tHTTPHeader;

/**HTTP标头中使用的字符串列表（有关标头字段定义，请参阅RFC 1945 HTTP/1.0和RFC 2616 HTTP/1.1）*/
static const char *const g_psHTTPHeaderStrings[] = {
  "HTTP/1.0 200 OK\r\n",
  "HTTP/1.0 404 File not found\r\n",
  "HTTP/1.0 400 Bad Request\r\n",
  "HTTP/1.0 501 Not Implemented\r\n",
  "HTTP/1.1 200 OK\r\n",
  "HTTP/1.1 404 File not found\r\n",
  "HTTP/1.1 400 Bad Request\r\n",
  "HTTP/1.1 501 Not Implemented\r\n",
  "Content-Length: ",
  "Connection: Close\r\n",
  "Connection: keep-alive\r\n",
  "Connection: keep-alive\r\nContent-Length: ",
  "Server: "HTTPD_SERVER_AGENT"\r\n",
  "\r\n<html><body><h2>404: The requested file cannot be found.</h2></body></html>\r\n"
#if LWIP_HTTPD_SUPPORT_11_KEEPALIVE
  , "Connection: keep-alive\r\nContent-Length: 77\r\n\r\n<html><body><h2>404: The requested file cannot be found.</h2></body></html>\r\n"
#endif
};

/* g_psHTTPHeaderStrings数组中的索引*/
#define HTTP_HDR_OK             0 /* 200 OK */
#define HTTP_HDR_NOT_FOUND      1 /* 404找不到文件*/
#define HTTP_HDR_BAD_REQUEST    2 /* 400错误请求*/
#define HTTP_HDR_NOT_IMPL       3 /* 501未实施*/
#define HTTP_HDR_OK_11          4 /* 200 OK */
#define HTTP_HDR_NOT_FOUND_11   5 /* 404找不到文件*/
#define HTTP_HDR_BAD_REQUEST_11 6 /* 400错误请求*/
#define HTTP_HDR_NOT_IMPL_11    7 /* 501未实施*/
#define HTTP_HDR_CONTENT_LENGTH 8 /* 内容长度：（HTTP 1.0）*/
#define HTTP_HDR_CONN_CLOSE     9 /* 连接：关闭（HTTP 1.1）*/
#define HTTP_HDR_CONN_KEEPALIVE 10 /* 连接：保持活动（HTTP 1.1）*/
#define HTTP_HDR_KEEPALIVE_LEN  11 /* 连接：保持活动+内容长度：（HTTP 1.1）*/
#define HTTP_HDR_SERVER         12 /* 服务器：HTTPD_Server_AGENT*/
#define DEFAULT_404_HTML        13 /* 默认404正文*/
#if LWIP_HTTPD_SUPPORT_11_KEEPALIVE
#define DEFAULT_404_HTML_PERSISTENT 14 /* 默认404主体，但包括连接：保持活动*/
#endif

#define HTTP_CONTENT_TYPE(contenttype) "Content-Type: "contenttype"\r\n\r\n"
#define HTTP_CONTENT_TYPE_ENCODING(contenttype, encoding) "Content-Type: "contenttype"\r\nContent-Encoding: "encoding"\r\n\r\n"

#define HTTP_HDR_HTML           HTTP_CONTENT_TYPE("text/html")
#define HTTP_HDR_SSI            HTTP_CONTENT_TYPE("text/html\r\nExpires: Fri, 10 Apr 2008 14:00:00 GMT\r\nPragma: no-cache")
#define HTTP_HDR_GIF            HTTP_CONTENT_TYPE("image/gif")
#define HTTP_HDR_PNG            HTTP_CONTENT_TYPE("image/png")
#define HTTP_HDR_JPG            HTTP_CONTENT_TYPE("image/jpeg")
#define HTTP_HDR_BMP            HTTP_CONTENT_TYPE("image/bmp")
#define HTTP_HDR_ICO            HTTP_CONTENT_TYPE("image/x-icon")
#define HTTP_HDR_APP            HTTP_CONTENT_TYPE("application/octet-stream")
#define HTTP_HDR_JS             HTTP_CONTENT_TYPE("application/javascript")
#define HTTP_HDR_RA             HTTP_CONTENT_TYPE("application/javascript")
#define HTTP_HDR_CSS            HTTP_CONTENT_TYPE("text/css")
#define HTTP_HDR_SWF            HTTP_CONTENT_TYPE("application/x-shockwave-flash")
#define HTTP_HDR_XML            HTTP_CONTENT_TYPE("text/xml")
#define HTTP_HDR_PDF            HTTP_CONTENT_TYPE("application/pdf")
#define HTTP_HDR_JSON           HTTP_CONTENT_TYPE("application/json")
#define HTTP_HDR_CSV            HTTP_CONTENT_TYPE("text/csv")
#define HTTP_HDR_TSV            HTTP_CONTENT_TYPE("text/tsv")
#define HTTP_HDR_SVG            HTTP_CONTENT_TYPE("image/svg+xml")
#define HTTP_HDR_SVGZ           HTTP_CONTENT_TYPE_ENCODING("image/svg+xml", "gzip")

#define HTTP_HDR_DEFAULT_TYPE   HTTP_CONTENT_TYPE("text/plain")

/**HTTP头字符串的扩展列表（参见过时的RFC 1700 MEDIA TYPES和http://www.iana.org/assignments/media-types对于已注册的内容类型和子类型）*/
static const tHTTPHeader g_psHTTPHeaders[] = {
  { "html", HTTP_HDR_HTML},
  { "htm",  HTTP_HDR_HTML},
  { "shtml", HTTP_HDR_SSI},
  { "shtm", HTTP_HDR_SSI},
  { "ssi",  HTTP_HDR_SSI},
  { "gif",  HTTP_HDR_GIF},
  { "png",  HTTP_HDR_PNG},
  { "jpg",  HTTP_HDR_JPG},
  { "bmp",  HTTP_HDR_BMP},
  { "ico",  HTTP_HDR_ICO},
  { "class", HTTP_HDR_APP},
  { "cls",  HTTP_HDR_APP},
  { "js",   HTTP_HDR_JS},
  { "ram",  HTTP_HDR_RA},
  { "css",  HTTP_HDR_CSS},
  { "swf",  HTTP_HDR_SWF},
  { "xml",  HTTP_HDR_XML},
  { "xsl",  HTTP_HDR_XML},
  { "pdf",  HTTP_HDR_PDF},
  { "json", HTTP_HDR_JSON}
#ifdef HTTPD_ADDITIONAL_CONTENT_TYPES
  /* 如果需要添加此处未列出的内容类型：#define HTTPD_ADDITIONAL_content_types｛“ct1”，HTTP_content-TYPE（“text/ct1”）｝，｛“exe”，HTTP_content_TYPE（“application.exe”）｝
   */
  , HTTPD_ADDITIONAL_CONTENT_TYPES
#endif
};

#define NUM_HTTP_HEADERS LWIP_ARRAYSIZE(g_psHTTPHeaders)

#endif /* LWIP_HTTPD_DYNAMIC_HEADERS */

#if LWIP_HTTPD_SSI
static const char *const g_pcSSIExtensions[] = {
  ".shtml", ".shtm", ".ssi", ".xml", ".json"
};
#define NUM_SHTML_EXTENSIONS LWIP_ARRAYSIZE(g_pcSSIExtensions)
#endif /* LWIP_HTTPD_SSI */

#endif /* LWIP_HTTPD_STRUCTS_H */

