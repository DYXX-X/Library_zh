/**
 * @file HTTP服务器选项列表
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

#ifndef LWIP_HDR_APPS_HTTPD_OPTS_H
#define LWIP_HDR_APPS_HTTPD_OPTS_H

#include "lwip/opt.h"
#include "lwip/prot/iana.h"

/**
 * @defgroup httpd_opts选项
 * @ingroup http地址@{
 */

/** 将此值设置为1以支持CGI（旧式）。
 *
 * This old style CGI support works by registering an array of URLs and associated CGI handler functions (@ref http_set_cgi_handlers）。在从请求处理调用fs_open之前，将扫描此列表。处理程序可以返回一个新的URL，httpd内部使用该URL加载返回的页面（传递给fs_open）。
 *
 * 使用此CGI类型，例如执行特定操作并返回不依赖于CGI参数的页面。
 */
#if !defined LWIP_HTTPD_CGI || defined __DOXYGEN__
#define LWIP_HTTPD_CGI            0
#endif

/** 将此值设置为1以支持CGI（新样式）。
 *
 * 这种新样式的CGI支持通过调用全局函数来工作
 * (@ref tCGIHandler）。首先调用fs_open，CGI处理程序无法写入URL。相反，此处理程序会传递http文件状态，该对象可以存储从CGI URL或参数派生的信息。此文件状态稍后传递给SSI，因此SSI代码可以根据CGI输入返回数据。
 *
 * 如果您希望将CGI信息传递给SSI，请使用此CGI处理程序。
 */
#if !defined LWIP_HTTPD_CGI_SSI || defined __DOXYGEN__
#define LWIP_HTTPD_CGI_SSI        0
#endif

/** 将此值设置为1以支持SSI（包括服务器端）
 *
 * 与其他http服务器不同，它只调用预先注册的回调
 * function (@see http_set_ssi_handler）（格式为<！--#tag-->）。启用SSI的页面必须具有预定义的启用SSI文件扩展名之一。所有具有这些扩展名之一的文件在发送时都会被解析。
 *
 * 当前SSI实现的一个缺点是持久连接不起作用，因为文件长度事先不知道（httpd当前依赖于Content-length头来实现持久连接）。
 *
 * To save memory, the maximum tag length is limited (@see LWIP_HTTPD_MAX_TAG_NAME_LEN）。为了节省内存，最大插入字符串长度受到限制（请参阅LWIP_HTTPD_MAX_TAG_INSERT_LEN）。如果这还不够，可以使用@ref LWIP_HTTPD_SSI_MULTIPART。
 */
#if !defined LWIP_HTTPD_SSI || defined __DOXYGEN__
#define LWIP_HTTPD_SSI            0
#endif

/** 将此值设置为1以实现SSI标记处理程序回调，该回调将获取标记的常量char*（而不是预先注册的已知标记数组的索引）。如果此值为0，则SSI处理程序回调函数仅称为预先注册的标记。
 */
#if !defined LWIP_HTTPD_SSI_RAW || defined __DOXYGEN__
#define LWIP_HTTPD_SSI_RAW        0
#endif

/** 将此值设置为0，以防止在运行时分析文件扩展名以决定是否应扫描文件以查找SSI标记。默认值为1（使用g_pcSSIExtensions数组检查文件扩展名）设置为2以覆盖此运行时测试函数。
 *
 * 默认情况下，这是启用的，但如果您只使用支持“-si”选项的更新版本的makefsdata，则此信息已存在于
 */
#if !defined LWIP_HTTPD_SSI_BY_FILE_EXTENSION || defined __DOXYGEN__
#define LWIP_HTTPD_SSI_BY_FILE_EXTENSION  1
#endif

/**将此值设置为1以支持HTTP POST*/
#if !defined LWIP_HTTPD_SUPPORT_POST || defined __DOXYGEN__
#define LWIP_HTTPD_SUPPORT_POST   0
#endif

/* CGI处理程序可以发送的最大参数数。*/
#if !defined LWIP_HTTPD_MAX_CGI_PARAMETERS || defined __DOXYGEN__
#define LWIP_HTTPD_MAX_CGI_PARAMETERS 16
#endif

/**LWIP_HTTPD_SSI_MULTIPART==1:调用SSI处理程序函数时，多了两个参数，指示插入字符串的计数器太长，无法立即插入：然后SSI处理函数必须设置“next_tag_part”，该值将在下一次调用中返回给它。*/
#if !defined LWIP_HTTPD_SSI_MULTIPART || defined __DOXYGEN__
#define LWIP_HTTPD_SSI_MULTIPART    0
#endif

/* 包含SSI标记名的字符串的最大长度注意：超过此长度的标记将被忽略，而不会被截断！
 */
#if !defined LWIP_HTTPD_MAX_TAG_NAME_LEN || defined __DOXYGEN__
#define LWIP_HTTPD_MAX_TAG_NAME_LEN 8
#endif

/* 可以返回以替换任何给定标记的字符串的最大长度如果此缓冲区不够长，请使用LWIP_HTTPD_SI_MULTIPART。
 */
#if !defined LWIP_HTTPD_MAX_TAG_INSERT_LEN || defined __DOXYGEN__
#define LWIP_HTTPD_MAX_TAG_INSERT_LEN 192
#endif

#if !defined LWIP_HTTPD_POST_MANUAL_WND || defined __DOXYGEN__
#define LWIP_HTTPD_POST_MANUAL_WND  0
#endif

/**此字符串在HTTP标头中作为“服务器：”传递*/
#if !defined HTTPD_SERVER_AGENT || defined __DOXYGEN__
#define HTTPD_SERVER_AGENT "lwIP/" LWIP_VERSION_STRING " (http://稀树草原.nongnu.org/projects/lwip）“
#endif

/**如果要包含在运行时创建HTTP头的代码，请将其设置为1。默认设置为关闭：然后通过makefsdata工具静态创建HTTP头。静态头意味着更小的代码大小，但由于每个文件都包含HTTP头，所以（只读）fsdata会增长一点。*/
#if !defined LWIP_HTTPD_DYNAMIC_HEADERS || defined __DOXYGEN__
#define LWIP_HTTPD_DYNAMIC_HEADERS 0
#endif

#if !defined HTTPD_DEBUG || defined __DOXYGEN__
#define HTTPD_DEBUG         LWIP_DBG_OFF
#endif

/** 将此值设置为1，以使用memp池来分配结构http_state，而不是堆。如果启用，则需要定义MEMP_NUM_PARALLEL_HTTPD_CONNS（以及SSI的MEMP_NUM-PARALLEL/HTTPD_SSI_CONNS）以设置池的大小。
 */
#if !defined HTTPD_USE_MEM_POOL || defined __DOXYGEN__
#define HTTPD_USE_MEM_POOL  0
#endif

/**HTTPD要使用的服务器端口*/
#if !defined HTTPD_SERVER_PORT || defined __DOXYGEN__
#define HTTPD_SERVER_PORT                   LWIP_IANA_PORT_HTTP
#endif

/**HTTPD要使用的https服务器端口*/
#if !defined HTTPD_SERVER_PORT_HTTPS || defined __DOXYGEN__
#define HTTPD_SERVER_PORT_HTTPS             LWIP_IANA_PORT_HTTPS
#endif

/**是否启用https支持？*/
#if !defined HTTPD_ENABLE_HTTPS || defined __DOXYGEN__
#define HTTPD_ENABLE_HTTPS                  0
#endif

/** 连接中止/关闭前的最大重试次数。
 * -调用pcb->轮询的次数->默认值为4*500ms=2s；
 * -调用pcb->send时重置
 */
#if !defined HTTPD_MAX_RETRIES || defined __DOXYGEN__
#define HTTPD_MAX_RETRIES                   4
#endif

/**轮询延迟为X*500ms*/
#if !defined HTTPD_POLL_INTERVAL || defined __DOXYGEN__
#define HTTPD_POLL_INTERVAL                 4
#endif

/** HTTPD创建的tcp pcbs的优先级（默认情况下非常低）。当内存耗尽时，优先级较低的优先级会首先被终止。
 */
#if !defined HTTPD_TCP_PRIO || defined __DOXYGEN__
#define HTTPD_TCP_PRIO                      TCP_PRIO_MIN
#endif

/**将此值设置为1，以便对发送的每个文件进行计时*/
#if !defined LWIP_HTTPD_TIMING || defined __DOXYGEN__
#define LWIP_HTTPD_TIMING                   0
#endif
/**将此值设置为1，以便对发送的每个文件进行计时*/
#if !defined HTTPD_DEBUG_TIMING || defined __DOXYGEN__
#define HTTPD_DEBUG_TIMING                  LWIP_DBG_OFF
#endif

/**将此值设置为1，以在解析请求失败时显示错误页面，而不是简单地关闭连接。*/
#if !defined LWIP_HTTPD_SUPPORT_EXTSTATUS || defined __DOXYGEN__
#define LWIP_HTTPD_SUPPORT_EXTSTATUS        0
#endif

/**将此值设置为0以删除对HTTP/0.9客户端的支持（以节省一些字节）*/
#if !defined LWIP_HTTPD_SUPPORT_V09 || defined __DOXYGEN__
#define LWIP_HTTPD_SUPPORT_V09              1
#endif

/** 将此值设置为1以启用HTTP/1.1持久连接。注意：如果生成的文件系统包含HTTP标头，则这些标头必须包含“Connection:keep-alive”标头（将参数“-11”传递给makefsdata）。
 */
#if !defined LWIP_HTTPD_SUPPORT_11_KEEPALIVE || defined __DOXYGEN__
#define LWIP_HTTPD_SUPPORT_11_KEEPALIVE     0
#endif

/**将此值设置为1以支持以多个数据包/pbufs形式传入的HTTP请求*/
#if !defined LWIP_HTTPD_SUPPORT_REQUESTLIST || defined __DOXYGEN__
#define LWIP_HTTPD_SUPPORT_REQUESTLIST      1
#endif

#if LWIP_HTTPD_SUPPORT_REQUESTLIST
/**要排队以解析传入请求的rx pbuf数（最多到第一个换行符）*/
#if !defined LWIP_HTTPD_REQ_QUEUELEN || defined __DOXYGEN__
#define LWIP_HTTPD_REQ_QUEUELEN             5
#endif

/**要排队分析和传入请求的（TCP有效负载-）字节数（以pbufs为单位）（最多为第一个双换行）*/
#if !defined LWIP_HTTPD_REQ_BUFSIZE || defined __DOXYGEN__
#define LWIP_HTTPD_REQ_BUFSIZE              LWIP_HTTPD_MAX_REQ_LENGTH
#endif

/**定义HTTP请求行的最大长度（直到第一个CRLF，当接收到pbuf或数据包队列时，从pbuf复制到全局缓冲区中，否则直接使用输入pbuf）*/
#if !defined LWIP_HTTPD_MAX_REQ_LENGTH || defined __DOXYGEN__
#define LWIP_HTTPD_MAX_REQ_LENGTH           LWIP_MIN(1023, (LWIP_HTTPD_REQ_QUEUELEN * PBUF_POOL_BUFSIZE))
#endif
#endif /* LWIP_HTTPD_SUPPORT_REQUESTLIST */

/** 这是URI以“/”结尾时使用的静态缓冲区的大小。在此缓冲区中，请求的目录与所有配置的默认文件名连接在一起。设置为0可禁用检查非根目录上的默认文件名。
 */
#if !defined LWIP_HTTPD_MAX_REQUEST_URI_LEN || defined __DOXYGEN__
#define LWIP_HTTPD_MAX_REQUEST_URI_LEN      63
#endif

/** 作为POST请求响应发送的文件名的最大长度，在POST完成时由应用程序填写。
 */
#if !defined LWIP_HTTPD_POST_MAX_RESPONSE_URI_LEN || defined __DOXYGEN__
#define LWIP_HTTPD_POST_MAX_RESPONSE_URI_LEN 63
#endif

/**将此值设置为0以不发送SSI标记（默认值为启用，因此标记将在HTML页面中发送*/
#if !defined LWIP_HTTPD_SSI_INCLUDE_TAG || defined __DOXYGEN__
#define LWIP_HTTPD_SSI_INCLUDE_TAG           1
#endif

/**当tcp_close因内存错误而失败时，将其设置为1以调用tcp_art。这可用于防止在HTTP服务器与其他通信相比优先级较低的情况下消耗所有内存。*/
#if !defined LWIP_HTTPD_ABORT_ON_CLOSE_MEM_ERROR || defined __DOXYGEN__
#define LWIP_HTTPD_ABORT_ON_CLOSE_MEM_ERROR  0
#endif

/** 将此值设置为1，以在“struct http_state”或“struct https_ssi_state”内存不足时终止最旧的连接。注意：这会将所有连接放在一个链接列表中，因此可能会有点慢。
 */
#if !defined LWIP_HTTPD_KILL_OLD_ON_CONNECTIONS_EXCEEDED || defined __DOXYGEN__
#define LWIP_HTTPD_KILL_OLD_ON_CONNECTIONS_EXCEEDED 0
#endif

/**将此值设置为1以发送不带扩展名且不带标头的URI（谁使用此值？？）*/
#if !defined LWIP_HTTPD_OMIT_HEADER_FOR_EXTENSIONLESS_URI || defined __DOXYGEN__
#define LWIP_HTTPD_OMIT_HEADER_FOR_EXTENSIONLESS_URI 0
#endif

/**默认值：标记从结构http_state发送，因此不稳定*/
#if !defined HTTP_IS_TAG_VOLATILE || defined __DOXYGEN__
#define HTTP_IS_TAG_VOLATILE(ptr) TCP_WRITE_FLAG_COPY
#endif

/* 默认情况下，当http不是设备中的重要协议时，httpd被限制为发送2*pcb->mss以保持资源使用率低。*/
#if !defined HTTPD_LIMIT_SENDING_TO_2MSS || defined __DOXYGEN__
#define HTTPD_LIMIT_SENDING_TO_2MSS 1
#endif

/* 将其定义为返回要排队的最大数据量的函数。函数具有以下签名：u16_t fn（struct altcp_pcb pcb）；最好的定义位置是hooks文件（@参见LWIP_HOOK_FILENAME）*/
#if !defined HTTPD_MAX_WRITE_LEN || defined __DOXYGEN__
#if HTTPD_LIMIT_SENDING_TO_2MSS
#define HTTPD_MAX_WRITE_LEN(pcb)    ((u16_t)(2 * altcp_mss(pcb)))
#endif
#endif

/*------------------- FS OPTIONS -------------------*/

/** 将其设置为1并提供以下功能：
 * -“int fs_open_custom（struct fs_file*file，const char*name）”首先为每个打开的文件调用，以允许打开不包含在fsdata（_custom）.c中的文件
 * -“void fs_close_custom（struct fs_file*file）”调用以释放由fs_open_custom（）分配的资源。
 */
#if !defined LWIP_HTTPD_CUSTOM_FILES || defined __DOXYGEN__
#define LWIP_HTTPD_CUSTOM_FILES       0
#endif

/** 将此值设置为1，以支持fs_read（）动态读取文件数据。如果没有此选项（默认设置为关闭），则只支持一个块文件，并且必须在fs_open（）之后准备好内容。
 */
#if !defined LWIP_HTTPD_DYNAMIC_FILE_READ || defined __DOXYGEN__
#define LWIP_HTTPD_DYNAMIC_FILE_READ  0
#endif

/** 将此值设置为1，以便为打开的每个文件包含一个应用程序状态参数。这允许保持每个连接/文件的状态。
 */
#if !defined LWIP_HTTPD_FILE_STATE || defined __DOXYGEN__
#define LWIP_HTTPD_FILE_STATE         0
#endif

/**HTTPD_PRECALCULATED_CHECKSUM==1：包括预定义（MSS大小）文件块的预编译校验和，以避免在运行时计算校验和。*/
#if !defined HTTPD_PRECALCULATED_CHECKSUM || defined __DOXYGEN__
#define HTTPD_PRECALCULATED_CHECKSUM  0
#endif

/** LWIP_HTTPD_FS_ASYNC_READ==1：支持异步读取操作（FS_READ_ASYNC返回FS_READ_DELAYED，并在完成时调用回调）。
 */
#if !defined LWIP_HTTPD_FS_ASYNC_READ || defined __DOXYGEN__
#define LWIP_HTTPD_FS_ASYNC_READ      0
#endif

/**用作FS数据文件的文件名（包括路径）*/
#if !defined HTTPD_FSDATA_FILE || defined __DOXYGEN__
/* HTTPD_USE_CUSTOM_FSDATA：与已弃用的lwIP选项兼容*/
#if defined(HTTPD_USE_CUSTOM_FSDATA) && (HTTPD_USE_CUSTOM_FSDATA != 0)
#define HTTPD_FSDATA_FILE "fsdata_custom.c"
#else
#define HTTPD_FSDATA_FILE "fsdata.c"
#endif
#endif

/**
 * @}
 */

#endif /* LWIP_HDR_APPS_HTTPD_OPTS_H */

