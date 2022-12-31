/**
 * @file HTTP服务器
 */

/*
 * 版权所有（c）2001-2003瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 * 此版本的文件已由德州仪器公司修改，以提供简单的服务器端包括（SSI）和通用网关接口（CGI）功能。
 */

#ifndef LWIP_HDR_APPS_HTTPD_H
#define LWIP_HDR_APPS_HTTPD_H

#include "httpd_opts.h"
#include "lwip/err.h"
#include "lwip/pbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_HTTPD_CGI

/**
 * @ingroup CGI脚本处理程序的httpd函数指针。
 *
 * 每当HTTPD服务器被要求使用http_set_CGI_handlers调用先前注册为CGI函数的文件时，都会调用此函数。iIndex参数提供传递给http_set_CGI_handlers的cgis数组中CGI的索引。参数pcParam和pcValue提供对与URI一起提供的参数的访问。iNumParams提供pcParam和pcValue数组中的条目计数。pcParam数组中的每个条目都包含参数的名称，pcValue数组中的相应条目包含该参数的值。注意，如果例如在生成数据的表单中使用了多选列表控件，则pcParam可能包含多个同名元素。
 *
 * 该函数应返回一个指向字符串的指针，该字符串是要发送到连接的浏览器的响应的路径和文件名，例如“/sthanks.htm”或“/response/error.ssi”。
 *
 * 将通过iNumParams传递到此函数的最大参数数由LWIP_HTTPD_MAX_CGI_parameters定义。传入HTTP请求中超过此数字的任何参数都将被丢弃。
 *
 * 必须使用GET方法（对URI中的所有参数进行编码，而不是在请求后面的块中）发送此CGI机制使用的请求。尝试使用POST方法将导致请求被忽略。
 *
 */
typedef const char *(*tCGIHandler)(int iIndex, int iNumParams, char *pcParam[],
                             char *pcValue[]);

/**
 * @ingroup httpd结构，定义CGI的基本文件名（URL）以及请求该URL时要调用的相关函数。
 */
typedef struct
{
    const char *pcCGIName;
    tCGIHandler pfnCGIHandler;
} tCGI;

void http_set_cgi_handlers(const tCGI *pCGIs, int iNumHandlers);

#endif /* LWIP_HTTPD_CGI */

#if LWIP_HTTPD_CGI || LWIP_HTTPD_CGI_SSI

#if LWIP_HTTPD_CGI_SSI
/* 我们必须在此处对该结构进行原型化，以使其可用于处理程序*/
struct fs_file;

/** 在应用程序中定义此通用CGI处理程序。对于每个带参数的URI调用一次。参数可以存储到作为connection_state传递的对象，该对象通过fs_open（）或fs_open_custom（）中的fs_state_init（）分配给file->state。通过SSI或完整的动态文件创建内容可以从中检索CGI参数。
 */
extern void httpd_cgi_handler(struct fs_file *file, const char* uri, int iNumParams,
                              char **pcParam, char **pcValue
#if defined(LWIP_HTTPD_FILE_STATE) && LWIP_HTTPD_FILE_STATE
                                     , void *connection_state
#endif /* LWIP_HTTPD_FILE_STATE */
                                     );
#endif /* LWIP_HTTPD_CGI_SSI */

#endif /* LWIP_HTTPD_CGI || LWIP_HTTPD_CGI_SSI */

#if LWIP_HTTPD_SSI

/**
 * @ingroup SSI标记处理程序回调的httpd函数指针。
 *
 * 每当HTTPD服务器检测到格式为<--#name-->在具有g_pcSSIExtensions数组（当前为.shtml、.shtm、.ssi、.xml、.json）中提到的扩展名的文件中，其中“name”显示为标记数组中提供给http_set_ssi_handler的标记之一。返回的插入字符串（将附加在发送回客户端的文件中的字符串“<！--#name-->”之后）应写入指针pcInsert。iInsertLen包含pcInsert指向的缓冲区大小。iIndex参数提供标签数组中找到的标签的从零开始的索引，并标识要处理的标签。
 *
 * 当无法识别标记时，处理程序返回写入pcInsert的字符数，不包括任何终止NULL或HTTPD_SSI_TAG_UNKNOWN。
 *
 * 请注意，此SSI机制的行为与“正常”SSI处理有些不同，例如在Apache web服务器中。在这种情况下，插入的文本附加在SSI标记之后，而不是完全替换标记。这允许实现不需要对输出数据进行显著的额外缓冲，但仍将提供可用的SSI功能。这种方法的一个缺点是试图在JavaScript中使用SSI。SSI标记的结构类似于HTML注释，但这种语法不构成JavaScript中的注释，因此，在这些情况下，保留标记将导致问题。为了避免这些问题，请在LWIP选项文件中将LWIP_HTTPD_SI_INCLUDE_TAG定义为零，或使用/#name/形式的JavaScript样式块注释（不带空格）。
 */
typedef u16_t (*tSSIHandler)(
#if LWIP_HTTPD_SSI_RAW
                             const char* ssi_tag_name,
#else /* LWIP_HTTPD_SSI_RAW */
                             int iIndex,
#endif /* LWIP_HTTPD_SSI_RAW */
                             char *pcInsert, int iInsertLen
#if LWIP_HTTPD_SSI_MULTIPART
                             , u16_t current_tag_part, u16_t *next_tag_part
#endif /* LWIP_HTTPD_SSI_MULTIPART */
#if defined(LWIP_HTTPD_FILE_STATE) && LWIP_HTTPD_FILE_STATE
                             , void *connection_state
#endif /* LWIP_HTTPD_FILE_STATE */
                             );

/** 设置SSI处理程序函数（如果LWIP_HTTPD_SSI_RAW==1，则仅使用第一个参数）
 */
void http_set_ssi_handler(tSSIHandler pfnSSIHandler,
                          const char **ppcTags, int iNumTags);

/** 对于LWIP_HTTPD_SSI_RAW==1，返回此值表示标记未知。在这种情况下，Web服务器会在页面中写入警告。您也可以只返回0，不为未知标记写入任何内容。
 */
#define HTTPD_SSI_TAG_UNKNOWN 0xFFFF

#endif /* LWIP_HTTPD_SSI */

#if LWIP_HTTPD_SUPPORT_POST

/* 这些功能必须由应用程序实现*/

/**
 * @ingroup httpd收到POST请求时调用。应用程序可以决定是否接受它。
 *
 * @param connection 唯一的连接标识符，在调用httpd_post_end之前有效。
 * @param uri 接收POST请求的HTTP标头URI。
 * @param http_request 原始HTTP请求（通常是第一个数据包）。
 * @param http_request_len “http_request”的大小。
 * @param content_len HTTP标头的内容长度。
 * @param response_uri 拒绝请求时要填写的响应文件的文件名
 * @param response_uri_len “response_uri”缓冲区的大小。
 * @param post_auto_wnd 将此值设置为0，以便回调代码通过调用“httpd_post_data_recved”（以限制rx速度）来处理窗口更新。默认值为1（httpd自动处理窗口更新）
 * @return ERR_OK：接受POST请求，数据可能会传递到另一个错误_t：拒绝POST请求，发回“错误请求”。
 */
err_t httpd_post_begin(void *connection, const char *uri, const char *http_request,
                       u16_t http_request_len, int content_len, char *response_uri,
                       u16_t response_uri_len, u8_t *post_auto_wnd);

/**
 * @ingroup httpd为POST接收的每个pbuf数据调用。注意：应用程序负责释放传入的pbuf！
 *
 * @param connection 唯一连接标识符。
 * @param p 收到的数据。
 * @return ERR_OK：数据已接受。另一个错误_t：数据被拒绝，将调用http_post_get_response_uri。
 */
err_t httpd_post_receive_data(void *connection, struct pbuf *p);

/**
 * @ingroup httpd在收到所有数据或连接关闭时调用。应用程序必须返回响应此POST请求而发送的文件名/URI。如果response_uri缓冲区未被触动，则返回404响应。
 *
 * @param connection 唯一连接标识符。
 * @param response_uri 拒绝请求时要填写的响应文件的文件名
 * @param response_uri_len “response_uri”缓冲区的大小。
 */
void httpd_post_finished(void *connection, char *response_uri, u16_t response_uri_len);

#if LWIP_HTTPD_POST_MANUAL_WND
void httpd_post_data_recved(void *connection, u16_t recved_len);
#endif /* LWIP_HTTPD_POST_MANUAL_WND */

#endif /* LWIP_HTTPD_SUPPORT_POST */

void httpd_init(void);

#if HTTPD_ENABLE_HTTPS
struct altcp_tls_config;
void httpd_inits(struct altcp_tls_config *conf);
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_HTTPD_H */

