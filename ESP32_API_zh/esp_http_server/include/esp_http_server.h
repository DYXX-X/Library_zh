/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_HTTP_SERVER_H_
#define _ESP_HTTP_SERVER_H_

#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <http_parser.h>
#include <sdkconfig.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
注意：esp_https_server。h包含应保持同步的此初始值设定项的自定义副本
*/
#define HTTPD_DEFAULT_CONFIG() {                        \
        .task_priority      = tskIDLE_PRIORITY+5,       \
        .stack_size         = 4096,                     \
        .core_id            = tskNO_AFFINITY,           \
        .server_port        = 80,                       \
        .ctrl_port          = 32768,                    \
        .max_open_sockets   = 7,                        \
        .max_uri_handlers   = 8,                        \
        .max_resp_headers   = 8,                        \
        .backlog_conn       = 5,                        \
        .lru_purge_enable   = false,                    \
        .recv_wait_timeout  = 5,                        \
        .send_wait_timeout  = 5,                        \
        .global_user_ctx = NULL,                        \
        .global_user_ctx_free_fn = NULL,                \
        .global_transport_ctx = NULL,                   \
        .global_transport_ctx_free_fn = NULL,           \
        .open_fn = NULL,                                \
        .close_fn = NULL,                               \
        .uri_match_fn = NULL                            \
}

#define ESP_ERR_HTTPD_BASE              (0xb000)                    /*!< HTTPD错误代码的起始数量*/
#define ESP_ERR_HTTPD_HANDLERS_FULL     (ESP_ERR_HTTPD_BASE +  1)   /*!< 用于注册URI处理程序的所有插槽都已用完*/
#define ESP_ERR_HTTPD_HANDLER_EXISTS    (ESP_ERR_HTTPD_BASE +  2)   /*!< 已注册具有相同方法和目标URI的URI处理程序*/
#define ESP_ERR_HTTPD_INVALID_REQ       (ESP_ERR_HTTPD_BASE +  3)   /*!< 请求指针无效*/
#define ESP_ERR_HTTPD_RESULT_TRUNC      (ESP_ERR_HTTPD_BASE +  4)   /*!< 结果字符串被截断*/
#define ESP_ERR_HTTPD_RESP_HDR          (ESP_ERR_HTTPD_BASE +  5)   /*!< 响应标头字段大于支持的值*/
#define ESP_ERR_HTTPD_RESP_SEND         (ESP_ERR_HTTPD_BASE +  6)   /*!< 发送响应数据包时出错*/
#define ESP_ERR_HTTPD_ALLOC_MEM         (ESP_ERR_HTTPD_BASE +  7)   /*!< 无法为资源动态分配内存*/
#define ESP_ERR_HTTPD_TASK              (ESP_ERR_HTTPD_BASE +  8)   /*!< 无法启动服务器任务/线程*/

/* 在httpd_resp_send API中用作长度参数的符号，用于将缓冲区长度设置为字符串长度*/
#define HTTPD_RESP_USE_STRLEN -1

/* **************组：初始化***************/
/** @name 与web服务器初始化相关的初始化API@{
 */

/**
 * @brief   HTTP服务器实例句柄
 *
 * 服务器的每个实例都有一个唯一的句柄。
 */
typedef void* httpd_handle_t;

/**
 * @brief   “HTTP_parser”库中提供的“enum HTTP_Method”上的HTTP方法类型包装器
 */
typedef enum http_method httpd_method_t;

/**
 * @brief  释放上下文数据的原型（如果有）
 * @param[in] ctx   要释放的对象
 */
typedef void (*httpd_free_ctx_fn_t)(void *ctx);

/**
 * @brief  用于打开会话的函数原型。
 *
 * 在套接字打开后立即调用，以设置套接字的send/recv函数和其他参数。
 *
 * @param[in] hd       服务器实例
 * @param[in] sockfd   会话套接字文件描述符
 * @return
 *  -ESP_OK：成功时
 *  -除ESP_OK以外的任何值都会通知服务器立即关闭套接字
 */
typedef esp_err_t (*httpd_open_func_t)(httpd_handle_t hd, int sockfd);

/**
 * @brief  用于关闭会话的函数原型。
 *
 * @note   此时套接字描述符可能无效，所有终止的会话都会调用该函数。确保正确处理返回代码。
 *
 * @param[in] hd   服务器实例
 * @param[in] sockfd   会话套接字文件描述符
 */
typedef void (*httpd_close_func_t)(httpd_handle_t hd, int sockfd);

/**
 * @brief  URI匹配的函数原型。
 *
 * @param[in] reference_uri   与其他URI匹配的URI/模板
 * @param[in] uri_to_match    URI/模板与引用URI/模板匹配
 * @param[in] match_upto      用于指定要应用匹配算法的“uri_to_match”的实际长度（最大值为“strlen（uri_to_batch）”，与“reference_uri”的长度无关）
 * @return 匹配时为true
 */
typedef bool (*httpd_uri_match_func_t)(const char *reference_uri,
                                       const char *uri_to_match,
                                       size_t match_upto);

/**
 * @brief   HTTP服务器配置结构
 *
 * @note    使用HTTPD_DEFAULT_CONFIG（）将配置初始化为默认值，然后仅修改由用例具体确定的字段。
 */
typedef struct httpd_config {
    unsigned    task_priority;      /*!< 运行服务器的FreeRTOS任务的优先级*/
    size_t      stack_size;         /*!< 服务器任务允许的最大堆栈大小*/
    BaseType_t  core_id;            /*!< HTTP服务器任务将在其上运行的核心*/

    /**
     * 用于接收和传输HTTP流量的TCP端口号
     */
    uint16_t    server_port;

    /**
     * UDP端口号，用于在服务器的各个组件之间异步交换控制信号
     */
    uint16_t    ctrl_port;

    uint16_t    max_open_sockets;   /*!< 任何时候连接的最大套接字/客户端数*/
    uint16_t    max_uri_handlers;   /*!< 允许的最大uri处理程序*/
    uint16_t    max_resp_headers;   /*!< HTTP响应中允许的最大附加标头数*/
    uint16_t    backlog_conn;       /*!< 积压连接数*/
    bool        lru_purge_enable;   /*!< 清除“最近最少使用”连接*/
    uint16_t    recv_wait_timeout;  /*!< recv功能超时（秒）*/
    uint16_t    send_wait_timeout;  /*!< 发送功能超时（秒）*/

    /**
     * 全局用户上下文。
     *
     * 此字段可用于在服务器上下文中存储任意用户数据。可以使用服务器句柄检索值，例如httpd_req_t结构。
     *
     * 关闭时，服务器通过在global_user_ctx字段上调用free（）来释放用户上下文。如果希望使用自定义函数释放全局用户上下文，请在此处指定。
     */
    void * global_user_ctx;

    /**
     * 全局用户上下文的自由函数
     */
    httpd_free_ctx_fn_t global_user_ctx_free_fn;

    /**
     * 全球运输环境。
     *
     * 类似于global_user_ctx，但用于会话编码或加密（例如保存SSL上下文）。除非指定了global_transport_ctx_free_fn，否则将使用free（）释放它。
     */
    void * global_transport_ctx;

    /**
     * 全球运输环境的自由功能
     */
    httpd_free_ctx_fn_t global_transport_ctx_free_fn;

    /**
     * 自定义会话打开回调。
     *
     * 在accept（）之后，但在读取任何数据之前，在新会话套接字上调用。
     *
     * 这是一个使用global_transport_ctx和send/recv/挂起会话覆盖设置SSL加密的机会。
     *
     * 如果需要在这些函数之间维护上下文，请使用httpd_sess_set_transport_ctx（）将其存储在会话中，稍后使用httpd_sess_get_transport_ctx（
     *
     * 返回ESP_OK以外的值将立即关闭新套接字。
     */
    httpd_open_func_t open_fn;

    /**
     * 自定义会话关闭回调。
     *
     * 在删除会话时、释放用户和传输上下文之前以及关闭套接字之前调用。这是所有套接字通用的自定义de init代码的地方。
     *
     * 如果在此处释放了用户或传输上下文，请将其设置为NULL，这样服务器就不会再次尝试释放它。
     *
     * 此函数用于所有终止的会话，包括套接字被网络堆栈关闭的会话，也就是说，文件描述符可能不再有效。
     */
    httpd_close_func_t close_fn;

    /**
     * URI匹配器函数。
     *
     * 在搜索匹配的URI时调用：1）其请求处理程序将在成功解析HTTP请求后立即执行2）以便在使用`httpd_register_URI_handler（）注册新的URI处理程序时防止重复`
     *
     * 可用选项有：1）NULL：内部使用“strncmp（）”进行基本匹配；2）“httpd_uri_match_wildcard（）”：uri通配符匹配器
     *
     * 用户可以实现自己的匹配函数（请参见“httpd_uri_match_func_t”函数原型的描述）
     */
    httpd_uri_match_func_t uri_match_fn;
} httpd_config_t;

/**
 * @brief 启动web服务器
 *
 * 创建一个HTTP服务器实例，并根据指定的配置为其分配内存/资源。
 *
 * 示例用法：
 * @code{c}
 *
 * //启动Web服务器的功能
 * httpd_handle_t start_webserver（无效）
 * {
 *      //生成默认配置
 *      httpd_config_t config=httpd_DEFAULT_config（）；
 *
 *      //http_server的空句柄
 *      httpd_handle_t服务器=空；
 *
 *      //启动httpd服务器
 *      如果（httpd_start（&server，&config）==ESP_OK）{
 *          //注册URI处理程序
 *          httpd_register_uri_handler（服务器，&uri_get）；
 *          httpd_register_uri_handler（服务器，&uri_post）；
 *      }
 *      //如果服务器启动失败，句柄将为NULL
 *      返回服务器；
 * }
 *
 * @endcode
 *
 * @param[in]  config   服务器新实例的配置
 * @param[out] handle   新创建的服务器实例的句柄。出现错误时为NULL
 * @return
 *  -ESP_OK:成功创建实例
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_ALLOC_MEM：无法为实例分配内存
 *  -ESP_ERR_HTTPD_TASK:无法启动服务器任务
 */
esp_err_t  httpd_start(httpd_handle_t *handle, const httpd_config_t *config);

/**
 * @brief 停止web服务器
 *
 * 取消分配HTTP服务器实例使用的内存/资源并将其删除。删除后，句柄将不再用于访问该实例。
 *
 * 示例用法：
 * @code{c}
 *
 * //停止Web服务器的功能
 * void stop_webserver（httpd_handle_t服务器）
 * {
 *      //确保句柄为非NULL
 *      if（服务器！=NULL）{
 *          //停止httpd服务器
 *          httpd_stop（服务器）；
 *      }
 * }
 *
 * @endcode
 *
 * @param[in] handle httpd_start返回的服务器句柄
 * @return
 *  -ESP_OK:服务器已成功停止
 *  -ESP_ERR_INVALID_ARG:句柄参数为空
 */
esp_err_t httpd_stop(httpd_handle_t handle);

/** 组初始化结束@}
 */

/* **************组：URI处理程序***************/
/** @name 与URI处理程序相关的URI处理程序API@{
 */

/* 支持的最大HTTP请求标头长度*/
#define HTTPD_MAX_REQ_HDR_LEN CONFIG_HTTPD_MAX_REQ_HDR_LEN

/* 支持的最大HTTP请求URI长度*/
#define HTTPD_MAX_URI_LEN CONFIG_HTTPD_MAX_URI_LEN

/**
 * @brief HTTP请求数据结构
 */
typedef struct httpd_req {
    httpd_handle_t  handle;                     /*!< 服务器实例句柄*/
    int             method;                     /*!< HTTP请求的类型，如果方法不受支持，则为-1*/
    const char      uri[HTTPD_MAX_URI_LEN + 1]; /*!< 此请求的URI（空终止额外1字节）*/
    size_t          content_len;                /*!< 请求正文的长度*/
    void           *aux;                        /*!< 内部使用的成员*/

    /**
     * URI注册期间传递了用户上下文指针。
     */
    void *user_ctx;

    /**
     * 会话上下文指针
     *
     * 会话上下文。为给定的开放TCP连接跨“会话”维护上下文。一个会话可以有多个请求响应。web服务器将确保上下文在所有这些请求和响应中保持不变。
     *
     * 默认情况下，该值为NULL。URI处理程序可以将其设置为任何有意义的值。
     *
     * 如果基础套接字关闭，并且该指针为非NULL，则web服务器将通过调用free（）释放上下文，除非设置了free_ctx函数。
     */
    void *sess_ctx;

    /**
     * 指向自由上下文挂钩的指针
     *
     * 释放会话上下文的函数
     *
     * 如果web服务器的套接字关闭，它将通过对sess_ctx成员调用free（）来释放会话上下文。如果希望使用自定义函数释放会话上下文，请在此处指定。
     */
    httpd_free_ctx_fn_t free_ctx;

    /**
     * 指示是否应忽略会话上下文更改的标志
     *
     * 默认情况下，如果在某个URI处理程序中更改sess_ctx，则在URI处理程序返回后，http服务器将在内部释放先前的上下文（如果非NULL）。如果您想自己管理sess_ctx的分配/重新分配/释放，请将此标志设置为true，以便服务器不会对其执行任何检查。只有当套接字关闭时，服务器才会清除上下文（通过调用free_ctx或free（））。
     */
    bool ignore_sess_ctx_changes;
} httpd_req_t;

/**
 * @brief URI处理程序的结构
 */
typedef struct httpd_uri {
    const char       *uri;    /*!< 要处理的URI*/
    httpd_method_t    method; /*!< URI支持的方法*/

    /**
     * 为支持的请求方法调用的处理程序。这必须返回ESP_OK，否则将关闭基础套接字。
     */
    esp_err_t (*handler)(httpd_req_t *r);

    /**
     * 指向可用于处理程序的用户上下文数据的指针
     */
    void *user_ctx;

#ifdef CONFIG_HTTPD_WS_SUPPORT
    /**
     * 用于指示WebSocket终结点的标志。如果此标志为真，则方法必须为HTTP_GET。否则将不会处理握手。
     */
    bool is_websocket;

    /**
     * 指示控制帧（PING、PONG、CLOSE）也传递给处理程序的标志。如果需要对控制帧进行自定义处理，则使用此标志
     */
    bool handle_ws_control_frames;

    /**
     * 指向URI支持的子协议的指针
     */
    const char *supported_subprotocol;
#endif
} httpd_uri_t;

/**
 * @brief   注册URI处理程序
 *
 * @note    只要服务器句柄有效，就可以实时注册URI处理程序。
 *
 * 示例用法：
 * @code{c}
 *
 * esp_err_t my_uri_handler（httpd_req_t*req）
 * {
 *     //接收、处理和发送
 *     ....
 *     ....
 *     ....
 *
 *     //故障条件
 *     如果（……）{
 *         //返回无法关闭会话//
 *         返回ESP_FAIL；
 *     }
 *
 *     //成功时
 *     返回ESP_OK；
 * }
 *
 * //URI处理程序结构
 * httpd_uri_t我的用户{
 *     .uri=“/my_uri/path/xyz”，
 *     .method=HTTPD_GET，
 *     .handler=my_uri_handler，
 *     .user_ctx=空
 * };
 *
 * //寄存器处理程序
 * 如果（httpd_register_uri_handler（server_handle，&my_uri）！=ESP_OK）{
 *    //如果注册处理程序失败
 *    ....
 * }
 *
 * @endcode
 *
 * @param[in] handle      HTTPD服务器实例句柄
 * @param[in] uri_handler 指向需要注册的处理程序的指针
 *
 * @return
 *  -ESP_OK:成功注册处理程序时
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_HANDLERS_FULL：如果没有新处理程序的插槽
 *  -ESP_ERR_HTTPD_HANDLER_EXISTS：如果已注册具有相同URI和方法的处理程序
 */
esp_err_t httpd_register_uri_handler(httpd_handle_t handle,
                                     const httpd_uri_t *uri_handler);

/**
 * @brief   注销URI处理程序
 *
 * @param[in] handle    HTTPD服务器实例句柄
 * @param[in] uri       URI字符串
 * @param[in] method    HTTP方法
 *
 * @return
 *  -ESP_OK:成功注销处理程序时
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_NOT_FOUND:找不到具有指定URI和方法的处理程序
 */
esp_err_t httpd_unregister_uri_handler(httpd_handle_t handle,
                                       const char *uri, httpd_method_t method);

/**
 * @brief   使用指定的URI字符串注销所有URI处理程序
 *
 * @param[in] handle   HTTPD服务器实例句柄
 * @param[in] uri      指定需要注销的所有处理程序的uri字符串
 *
 * @return
 *  -ESP_OK:成功注销所有此类处理程序
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_NOT_FOUND：没有使用指定的uri字符串注册处理程序
 */
esp_err_t httpd_unregister_uri(httpd_handle_t handle, const char* uri);

/** URI处理程序@}的结尾
 */

/* **************组：HTTP错误***************/
/** @name HTTP错误和错误处理函数的HTTP错误原型@{
 */

/**
 * @brief 在处理HTTP请求过程中遇到错误时作为HTTP响应发送的错误代码
 */
typedef enum {
    /* 对于分析过程中的任何意外错误，如意外状态转换或未处理的错误。
     */
    HTTPD_500_INTERNAL_SERVER_ERROR = 0,

    /* 对于http_parser不支持的方法。目前，当遇到此类方法时，http_parser会停止解析，因此服务器会响应400 Bad Request错误。
     */
    HTTPD_501_METHOD_NOT_IMPLEMENTED,

    /* 当HTTP版本不是1.1时*/
    HTTPD_505_VERSION_NOT_SUPPORTED,

    /* 当http_parser由于请求语法错误、请求URI中的方法不受支持或标头中存在分块编码/升级字段而停止分析时返回
     */
    HTTPD_400_BAD_REQUEST,

    /* 此响应意味着客户端必须对自己进行身份验证才能获得请求的响应。
     */
    HTTPD_401_UNAUTHORIZED,

    /* 客户端没有对内容的访问权限，因此服务器拒绝提供请求的资源。与401不同，服务器知道客户端的身份。
     */
    HTTPD_403_FORBIDDEN,

    /* 未找到请求的URI时*/
    HTTPD_404_NOT_FOUND,

    /* 找到URI，但方法未注册处理程序时*/
    HTTPD_405_METHOD_NOT_ALLOWED,

    /* 用于录制超时。目前，它也因其他记录错误而被发送。客户端应该希望服务器在响应此消息后立即关闭连接。
     */
    HTTPD_408_REQ_TIMEOUT,

    /* 用于响应当前不支持的分块编码。尽管未处理的分块请求的http_parser回调返回“400 Bad request”
     */
    HTTPD_411_LENGTH_REQUIRED,

    /* URI长度大于CONFIG_HTTPD_MAX_URI_LEN*/
    HTTPD_414_URI_TOO_LONG,

    /* 标题部分大于CONFIG_HTTPD_MAX_REQ_HDR_LEN*/
    HTTPD_431_REQ_HDR_FIELDS_TOO_LARGE,

    /* 内部用于检索错误总数*/
    HTTPD_ERR_CODE_MAX
} httpd_err_code_t;

/**
 * @brief  HTTP错误处理的函数原型。
 *
 * 此函数在HTTP请求的内部处理过程中生成HTTP错误时执行。这用于重写错误时的默认行为，即发送HTTP错误响应并关闭基础套接字。
 *
 * @note
 *  -如果实现，服务器将不会自动发送HTTP错误响应代码，因此，如果用户希望生成HTTP错误响应，则必须在此函数中调用httpd_resp_end_err（）。
 *  -调用时，httpd_req_t参数的“uri”、“method”、“content_len”和“user_ctx”字段的有效性无法保证，因为HTTP请求可能会被部分接收/解析。
 *  -如果基础套接字需要保持打开，则函数必须返回ESP_OK。任何其他值都将确保套接字关闭。当错误类型为`HTTPD_500_INTERNAL_SERVER_error`且套接字已关闭时，将忽略返回值。
 *
 * @param[in] req    需要处理错误的HTTP请求
 * @param[in] error  错误类型
 *
 * @return
 *  -ESP_OK：错误处理成功
 *  -ESP_FAIL：失败表示需要关闭基础套接字
 */
typedef esp_err_t (*httpd_err_handler_func_t)(httpd_req_t *req,
                                              httpd_err_code_t error);

/**
 * @brief  用于注册HTTP错误处理程序的函数
 *
 * 此函数将处理程序函数映射到“httpd_err_code_t”提供的任何支持的错误代码。有关详细信息，请参见上面的原型“httpd_err_handler_func_t”。
 *
 * @param[in] handle     HTTP服务器句柄
 * @param[in] error      错误类型
 * @param[in] handler_fn 用户实现的处理程序函数（传递NULL以取消设置任何先前设置的处理程序）
 *
 * @return
 *  -ESP_OK:处理程序注册成功
 *  -ESP_ERR_INVALID_ARG：错误代码或服务器句柄无效
 */
esp_err_t httpd_register_err_handler(httpd_handle_t handle,
                                     httpd_err_code_t error,
                                     httpd_err_handler_func_t handler_fn);

/** HTTP结束错误@}
 */

/* **************组：TX/RX***************/
/** @name HTTPD低级发送/接收功能的TX/RX原型@{
 */

#define HTTPD_SOCK_ERR_FAIL      -1
#define HTTPD_SOCK_ERR_INVALID   -2
#define HTTPD_SOCK_ERR_TIMEOUT   -3

/**
 * @brief  HTTPD低级发送函数的原型
 *
 * @note   用户指定的发送函数必须根据errno的设置值在内部处理错误，并返回特定的HTTPD_SOCK_ERR_代码，这些代码最终将作为HTTPD_send（）函数的返回值传递
 *
 * @param[in] hd        服务器实例
 * @param[in] sockfd    会话套接字文件描述符
 * @param[in] buf       带有要发送的字节的缓冲区
 * @param[in] buf_len   数据大小
 * @param[in] flags     send（）函数的标志
 * @return
 *  -Bytes：成功发送的字节数
 *  -HTTPD_SOCK_ERR_INVALID：参数无效
 *  -HTTPD_SOCK_ERR_TIMEOUT:调用套接字send（）时超时/中断
 *  -HTTPD_SOCK_ERR_FAIL：调用套接字send（）时发生不可恢复的错误
 */
typedef int (*httpd_send_func_t)(httpd_handle_t hd, int sockfd, const char *buf, size_t buf_len, int flags);

/**
 * @brief  HTTPD低级recv功能原型
 *
 * @note   用户指定的recv函数必须根据errno的设置值在内部处理错误，并返回特定的HTTPD_SOCK_ERR_代码，这些代码最终将作为HTTPD_req_recv（）函数的返回值传递
 *
 * @param[in] hd        服务器实例
 * @param[in] sockfd    会话套接字文件描述符
 * @param[in] buf       带有要发送的字节的缓冲区
 * @param[in] buf_len   数据大小
 * @param[in] flags     send（）函数的标志
 * @return
 *  -Bytes：成功接收的字节数
 *  -0:缓冲区长度参数为零/对等方关闭了连接
 *  -HTTPD_SOCK_ERR_INVALID：参数无效
 *  -HTTPD_SOCK_ERR_TIMEOUT:调用套接字recv（）时超时/中断
 *  -HTTPD_SOCK_ERR_FAIL：调用套接字recv（）时发生不可恢复的错误
 */
typedef int (*httpd_recv_func_t)(httpd_handle_t hd, int sockfd, char *buf, size_t buf_len, int flags);

/**
 * @brief  HTTPD低级“获取待定字节”函数的原型
 *
 * @note   用户指定的挂起函数必须根据errno的设置值在内部处理错误，并返回特定的HTTPD_SOCK_ERR_代码，这些代码将在服务器任务中相应处理。
 *
 * @param[in] hd       服务器实例
 * @param[in] sockfd   会话套接字文件描述符
 * @return
 *  -Bytes：等待接收的字节数
 *  -HTTPD_SOCK_ERR_INVALID：参数无效
 *  -HTTPD_SOCK_ERR_TIMEOUT:调用套接字挂起（）时超时/中断
 *  -HTTPD_SOCK_ERR_FAIL：调用套接字挂起（）时发生不可恢复的错误
 */
typedef int (*httpd_pending_func_t)(httpd_handle_t hd, int sockfd);

/** TX/RX@}结束
 */

/* **************组：请求/响应***************/
/** @name 与URI处理程序发送/接收数据相关的请求/响应API。这些API应该只能从httpd_req_t请求指针有效的URI处理程序的上下文中调用@{
 */

/**
 * @brief   覆盖web服务器的接收功能（通过会话FD）
 *
 * 此函数覆盖web服务器的接收函数。此函数用于读取HTTP请求数据包。
 *
 * @note    该API应该从
 *          -一个http会话API，其中sockd是一个有效参数
 *          -使用httpd_req_to_sockfd（）获取sockfd的URI处理程序
 *
 * @param[in] hd        HTTPD实例句柄
 * @param[in] sockfd    会话套接字FD
 * @param[in] recv_func 要为此会话设置的接收函数
 *
 * @return
 *  -ESP_OK：成功注册覆盖时
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t httpd_sess_set_recv_override(httpd_handle_t hd, int sockfd, httpd_recv_func_t recv_func);

/**
 * @brief   覆盖web服务器的发送功能（通过会话FD）
 *
 * 此函数覆盖web服务器的发送函数。该函数用于发送对任何HTTP请求的任何响应。
 *
 * @note    该API应该从
 *          -一个http会话API，其中sockd是一个有效参数
 *          -使用httpd_req_to_sockfd（）获取sockfd的URI处理程序
 *
 * @param[in] hd        HTTPD实例句柄
 * @param[in] sockfd    会话套接字FD
 * @param[in] send_func 要为此会话设置的发送函数
 *
 * @return
 *  -ESP_OK：成功注册覆盖时
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t httpd_sess_set_send_override(httpd_handle_t hd, int sockfd, httpd_send_func_t send_func);

/**
 * @brief   覆盖web服务器的挂起功能（通过会话FD）
 *
 * 此函数覆盖web服务器的挂起函数。此函数用于测试套接字中的挂起字节。
 *
 * @note    该API应该从
 *          -一个http会话API，其中sockd是一个有效参数
 *          -使用httpd_req_to_sockfd（）获取sockfd的URI处理程序
 *
 * @param[in] hd           HTTPD实例句柄
 * @param[in] sockfd       会话套接字FD
 * @param[in] pending_func 要为此会话设置的接收函数
 *
 * @return
 *  -ESP_OK：成功注册覆盖时
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t httpd_sess_set_pending_override(httpd_handle_t hd, int sockfd, httpd_pending_func_t pending_func);

/**
 * @brief   从HTTP请求中获取套接字描述符
 *
 * 此API将返回在接收HTTP请求时为其执行URI处理程序的会话的套接字描述符。当用户想要从URI处理程序中调用需要会话套接字fd的函数时，这非常有用，例如：httpd_sess_get_ctx（）、httpd_sesse_trigger_close（）、httpsd_sess_update_lru_counter（）。
 *
 * @note    该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *
 * @param[in] r 应找到其套接字描述符的请求
 *
 * @return
 *  -套接字描述符：此请求的套接字描述符
 *  --1：无效的NULL请求指针
 */
int httpd_req_to_sockfd(httpd_req_t *r);

/**
 * @brief   从HTTP请求读取内容数据的API
 *
 * 此API将从HTTP请求中读取HTTP内容数据到提供的缓冲区。使用httpd_req_t结构中提供的content_len来了解要获取的数据的长度。如果content_len对于缓冲区来说太大，则用户可能必须多次调用此函数，每次都获取“buf_len”字节数，而指向内容数据的指针在内部递增相同的数值。
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -如果返回错误，则URI处理程序必须进一步返回错误。这将确保web服务器关闭并清除错误的套接字。
 *  -当前不支持分块编码
 *
 * @param[in] r         正在响应的请求
 * @param[in] buf       指向数据将被读入的缓冲区的指针
 * @param[in] buf_len   缓冲区长度
 *
 * @return
 *  -Bytes：成功读入缓冲区的字节数
 *  -0:缓冲区长度参数为零/对等方关闭了连接
 *  -HTTPD_SOCK_ERR_INVALID：参数无效
 *  -HTTPD_SOCK_ERR_TIMEOUT:调用套接字recv（）时超时/中断
 *  -HTTPD_SOCK_ERR_FAIL：调用套接字recv（）时发生不可恢复的错误
 */
int httpd_req_recv(httpd_req_t *r, char *buf, size_t buf_len);

/**
 * @brief   在请求标头中搜索字段并返回其值的字符串长度
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -一旦httpd_resp_send（）API被调用，所有请求头都将被清除，因此如果稍后需要，请求头需要复制到单独的缓冲区中。
 *
 * @param[in]  r        正在响应的请求
 * @param[in]  field    请求中要搜索的标头字段
 *
 * @return
 *  -长度：如果在请求URL中找到字段
 *  -零：未找到字段/请求无效/参数为空
 */
size_t httpd_req_get_hdr_value_len(httpd_req_t *r, const char *field);

/**
 * @brief   从请求头中获取字段的值字符串
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -一旦httpd_resp_send（）API被调用，所有请求头都将被清除，因此如果稍后需要，请求头需要复制到单独的缓冲区中。
 *  -如果输出大小大于输入，则该值将被截断，并伴随截断错误作为返回值。
 *  -使用httpd_req_get_hdr_value_len（）了解正确的缓冲区长度
 *
 * @param[in]  r        正在响应的请求
 * @param[in]  field    标题中要搜索的字段
 * @param[out] val      指向缓冲区的指针，如果找到字段，则将值复制到该缓冲区
 * @param[in]  val_size 用户缓冲区“val”的大小
 *
 * @return
 *  -ESP_OK：在请求标头和复制的值字符串中找到字段
 *  -ESP_ERR_NOT_FOUND：找不到密钥
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_INVALID_REQ:HTTP请求指针无效
 *  -ESP_ERR_HTTPD_RESULT_TRUNC：值字符串被截断
 */
esp_err_t httpd_req_get_hdr_value_str(httpd_req_t *r, const char *field, char *val, size_t val_size);

/**
 * @brief   从请求URL获取查询字符串长度
 *
 * @note    应该只从httpd_req_t请求指针有效的URI处理程序上下文中调用此API
 *
 * @param[in]  r    正在响应的请求
 *
 * @return
 *  -长度：在请求URL中找到查询
 *  -零：未找到查询/空参数/无效请求
 */
size_t httpd_req_get_url_query_len(httpd_req_t *r);

/**
 * @brief   从请求URL获取查询字符串
 *
 * @note
 *  -目前，用户可以获取完整的URL查询字符串，但解码必须由用户执行。可以使用httpd_req_get_hdr_value_str（）读取请求标头，以了解“内容类型”（例如，内容类型：application/x-www-form-urlencoded），然后需要应用适当的解码算法。
 *  -应该只从httpd_req_t请求指针有效的URI处理程序上下文中调用此API
 *  -如果输出大小大于输入，则该值将被截断，并伴随截断错误作为返回值
 *  -在调用此函数之前，可以使用httpd_req_get_url_query_len（）预先知道查询字符串的长度，从而分配适当大小的缓冲区（通常为空终止的查询字符串长度+1）来存储查询字符串
 *
 * @param[in]  r         正在响应的请求
 * @param[out] buf       指向查询字符串将复制到的缓冲区的指针（如果找到）
 * @param[in]  buf_len   输出缓冲区长度
 *
 * @return
 *  -ESP_OK：在请求URL中找到查询并复制到缓冲区
 *  -ESP_ERR_NOT_FOUND：未找到查询
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_INVALID_REQ:HTTP请求指针无效
 *  -ESP_ERR_HTTPD_RESULT_TRUNC:查询字符串被截断
 */
esp_err_t httpd_req_get_url_query_str(httpd_req_t *r, char *buf, size_t buf_len);

/**
 * @brief   Helper函数，用于从param1=val1&param2=val2类型的查询字符串中获取URL查询标记
 *
 * @note
 *  -URL查询字符串的组件（键和值）未进行URL解码。用户必须检查请求标头中的“内容类型”字段，然后根据指定的编码（URLencoded或其他）应用适当的解码算法。
 *  -如果实际值大小大于val_size，则该值将被截断，并伴随截断错误作为返回值。
 *
 * @param[in]  qry       指向查询字符串的指针
 * @param[in]  key       要在查询字符串中搜索的关键字
 * @param[out] val       指向缓冲区的指针，如果找到键，则将值复制到该缓冲区
 * @param[in]  val_size  用户缓冲区“val”的大小
 *
 * @return
 *  -ESP_OK：在URL查询字符串中找到关键字并将其复制到缓冲区
 *  -ESP_ERR_NOT_FOUND：找不到密钥
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_RESULT_TRUNC：值字符串被截断
 */
esp_err_t httpd_query_key_value(const char *qry, const char *key, char *val, size_t val_size);

/**
 * @brief   按cookie名称从“cookie”请求头中获取cookie值的值字符串。
 *
 * @param[in]       req             指向HTTP请求的指针
 * @param[in]       cookie_name     请求中要搜索的cookie名称
 * @param[out]      val             指向缓冲区的指针，如果找到cookie，则将cookie值复制到该缓冲区
 * @param[inout]    val_size        指向用户缓冲区“val”大小的指针。如果返回ESP_OK，则此变量将包含cookie长度，如果返回ESP_ERR_HTTPD_RESULT_TRUNC，则此参数将包含所需的缓冲区长度。
 *
 * @return
 *  -ESP_OK：在cookie字符串中找到密钥并复制到缓冲区
 *  -ESP_ERR_NOT_FOUND：找不到密钥
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_RESULT_TRUNC：值字符串被截断
 *  -ESP_ERR_NO_MEM：内存分配失败
 */
esp_err_t httpd_req_get_cookie_val(httpd_req_t *req, const char *cookie_name, char *val, size_t *val_size);

/**
 * @brief 测试URI是否与给定的通配符模板匹配。
 *
 * 模板可能以“？”结尾使前一个字符可选（通常为斜线），“”表示通配符匹配，“？”使前一个字符可选，如果存在，则允许任何后续字符。
 *
 * 例子：
 *   -*匹配所有内容
 *   -/foo/？匹配/foo和/foo/
 *   -/foo/\*（无反斜杠）匹配/foo/和/foo/bar，但不匹配/foo或/fo
 *   -/foo/？*或/foo/\*？（无反斜杠）匹配/foo/、/foo/bar和/foo，但不匹配/fox或/fo
 *
 * 特殊字符“？”而模板中其他任何地方的“*”将按字面意思取。
 *
 * @param[in] uri_template   URI模板（模式）
 * @param[in] uri_to_match   要匹配的URI
 * @param[in] match_upto     要测试的URI缓冲区的字符数（可能有尾随查询字符串等）
 *
 * @return 如果找到匹配项，则为true
 */
bool httpd_uri_match_wildcard(const char *uri_template, const char *uri_to_match, size_t match_upto);

/**
 * @brief   用于发送完整HTTP响应的API。
 *
 * 此API将作为对请求的HTTP响应发送数据。这假设您在一个缓冲区中准备好了整个响应。如果希望以增量块发送响应，请改用httpd_resp_send_chunk（）。
 *
 * 如果未设置状态代码和内容类型，默认情况下，这将以text/html的形式发送200 OK状态代码和属性类型。您可以在此API之前调用以下函数来配置响应标头：httpd_resp_set_status（）-用于设置HTTP状态字符串，httpd_resp.set_type（）-设置内容类型，httpd_resp_set_hdr（）-在响应标头中附加任何其他字段值条目
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -一旦调用了此API，请求就会得到响应。
 *  -然后，无法为请求发送其他数据。
 *  -一旦调用了这个API，所有的请求头都会被清除，所以如果以后需要的话，需要将请求头复制到单独的缓冲区中。
 *
 * @param[in] r         正在响应的请求
 * @param[in] buf       从中提取内容的缓冲区
 * @param[in] buf_len   要使用STRLEN（）的缓冲区长度HTTPD_RESP_USE_STRLEN
 *
 * @return
 *  -ESP_OK：成功发送响应数据包时
 *  -ESP_ERR_INVALID_ARG:空请求指针
 *  -ESP_ERR_HTTPD_RESP_HDR:基本标头对于内部缓冲区太大
 *  -ESP_ERR_HTTPD_RESP_SEND：原始发送错误
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求无效
 */
esp_err_t httpd_resp_send(httpd_req_t *r, const char *buf, ssize_t buf_len);

/**
 * @brief   发送一个HTTP块的API
 *
 * 此API将作为对请求的HTTP响应发送数据。此API将使用分块编码并以分块的形式发送响应。如果整个响应包含在一个缓冲区中，请改用httpd_resp_send（）。
 *
 * 如果未设置状态代码和内容类型，默认情况下，这将以text/html的形式发送200 OK状态代码和属性类型。您可以在此API之前调用以下函数来配置响应标头httpd_resp_set_status（）-用于设置HTTP状态字符串httpd_resp.set_type（）-设置内容类型httpd_resp_set_hdr（）-在响应标头中附加任何其他字段值条目
 *
 * @note
 * -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 * -发送完所有块后，必须调用buf_len为0的函数。
 * -一旦调用了这个API，所有的请求头都会被清除，所以如果以后需要的话，需要将请求头复制到单独的缓冲区中。
 *
 * @param[in] r         正在响应的请求
 * @param[in] buf       指向存储数据的缓冲区的指针
 * @param[in] buf_len   要使用STRLEN（）的缓冲区长度HTTPD_RESP_USE_STRLEN
 *
 * @return
 *  -ESP_OK：成功发送响应数据包块时
 *  -ESP_ERR_INVALID_ARG:空请求指针
 *  -ESP_ERR_HTTPD_RESP_HDR:基本标头对于内部缓冲区太大
 *  -ESP_ERR_HTTPD_RESP_SEND：原始发送错误
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求指针无效
 */
esp_err_t httpd_resp_send_chunk(httpd_req_t *r, const char *buf, ssize_t buf_len);

/**
 * @brief   API将完整字符串作为HTTP响应发送。
 *
 * 此API只调用http_resp_send，并将缓冲区长度设置为字符串长度，假设缓冲区包含以空结尾的字符串
 *
 * @param[in] r         正在响应的请求
 * @param[in] str       要作为响应主体发送的字符串
 *
 * @return
 *  -ESP_OK：成功发送响应数据包时
 *  -ESP_ERR_INVALID_ARG:空请求指针
 *  -ESP_ERR_HTTPD_RESP_HDR:基本标头对于内部缓冲区太大
 *  -ESP_ERR_HTTPD_RESP_SEND：原始发送错误
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求无效
 */
static inline esp_err_t httpd_resp_sendstr(httpd_req_t *r, const char *str) {
    return httpd_resp_send(r, str, (str == NULL) ? 0 : HTTPD_RESP_USE_STRLEN);
}

/**
 * @brief   用于将字符串作为HTTP响应块发送的API。
 *
 * 此API只调用http_resp_send_chunk，并将缓冲区长度设置为字符串长度，假设缓冲区包含以空结尾的字符串
 *
 * @param[in] r    正在响应的请求
 * @param[in] str  要作为响应主体发送的字符串（NULL表示完成响应包）
 *
 * @return
 *  -ESP_OK：成功发送响应数据包时
 *  -ESP_ERR_INVALID_ARG:空请求指针
 *  -ESP_ERR_HTTPD_RESP_HDR:基本标头对于内部缓冲区太大
 *  -ESP_ERR_HTTPD_RESP_SEND：原始发送错误
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求无效
 */
static inline esp_err_t httpd_resp_sendstr_chunk(httpd_req_t *r, const char *str) {
    return httpd_resp_send_chunk(r, str, (str == NULL) ? 0 : HTTPD_RESP_USE_STRLEN);
}

/* 一些常用的状态代码*/
#define HTTPD_200      "200 OK"                     /*!< HTTP响应200*/
#define HTTPD_204      "204 No Content"             /*!< HTTP响应204*/
#define HTTPD_207      "207 Multi-Status"           /*!< HTTP响应207*/
#define HTTPD_400      "400 Bad Request"            /*!< HTTP响应400*/
#define HTTPD_404      "404 Not Found"              /*!< HTTP响应404*/
#define HTTPD_408      "408 Request Timeout"        /*!< HTTP响应408*/
#define HTTPD_500      "500 Internal Server Error"  /*!< HTTP响应500*/

/**
 * @brief   用于设置HTTP状态代码的API
 *
 * 此API将HTTP响应的状态设置为指定的值。默认情况下，“200 OK”响应作为响应发送。
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -此API仅将状态设置为此值。在执行任何发送API之前，都不会发送状态。
 *  -确保状态字符串的生存期在调用send函数之前有效。
 *
 * @param[in] r         正在响应的请求
 * @param[in] status    此响应的HTTP状态代码
 *
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求指针无效
 */
esp_err_t httpd_resp_set_status(httpd_req_t *r, const char *status);

/* 一些常用的内容类型*/
#define HTTPD_TYPE_JSON   "application/json"            /*!< HTTP内容类型JSON*/
#define HTTPD_TYPE_TEXT   "text/html"                   /*!< HTTP内容类型文本/HTML*/
#define HTTPD_TYPE_OCTET  "application/octet-stream"    /*!< HTTP内容类型八位文本流*/

/**
 * @brief   用于设置HTTP内容类型的API
 *
 * 此API设置响应的“内容类型”字段。默认内容类型为“text/html”。
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -此API仅将内容类型设置为此值。在执行任何发送API之前，都不会发送该类型。
 *  -确保在调用send函数之前，类型字符串的生存期有效。
 *
 * @param[in] r     正在响应的请求
 * @param[in] type  响应的内容类型
 *
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求指针无效
 */
esp_err_t httpd_resp_set_type(httpd_req_t *r, const char *type);

/**
 * @brief   附加任何附加头的API
 *
 * 此API设置需要在响应中发送的任何附加头字段。
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -在执行任何发送API之前，都不会发送标头。
 *  -允许的最大附加头数限制为配置结构中max_resp_headers的值。
 *  -确保字段值字符串的生存期在调用send函数之前有效。
 *
 * @param[in] r     正在响应的请求
 * @param[in] field HTTP标头的字段名
 * @param[in] value 此HTTP标头的值
 *
 * @return
 *  -ESP_OK:成功附加新标头时
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_RESP_HDR:附加标头总数超过允许的最大值
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求指针无效
 */
esp_err_t httpd_resp_set_hdr(httpd_req_t *r, const char *field, const char *value);

/**
 * @brief   用于响应HTTP请求发送错误代码。
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -一旦调用了这个API，所有的请求头都会被清除，所以如果以后需要的话，需要将请求头复制到单独的缓冲区中。
 *  -如果您希望在响应正文中发送其他数据，请直接使用较低级别的函数。
 *
 * @param[in] req     指向需要发送响应的HTTP请求的指针
 * @param[in] error   要发送的错误类型
 * @param[in] msg     错误消息字符串（默认消息传递NULL）
 *
 * @return
 *  -ESP_OK：成功发送响应数据包时
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_RESP_SEND：原始发送错误
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求指针无效
 */
esp_err_t httpd_resp_send_err(httpd_req_t *req, httpd_err_code_t error, const char *msg);

/**
 * @brief   HTTP 404的Helper函数
 *
 * 发送HTTP 404消息。如果您希望在响应正文中发送其他数据，请直接使用较低级别的函数。
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -一旦调用了这个API，所有的请求头都会被清除，所以如果以后需要的话，需要将请求头复制到单独的缓冲区中。
 *
 * @param[in] r 正在响应的请求
 *
 * @return
 *  -ESP_OK：成功发送响应数据包时
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_RESP_SEND：原始发送错误
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求指针无效
 */
static inline esp_err_t httpd_resp_send_404(httpd_req_t *r) {
    return httpd_resp_send_err(r, HTTPD_404_NOT_FOUND, NULL);
}

/**
 * @brief   HTTP 408的Helper函数
 *
 * 发送HTTP 408消息。如果您希望在响应正文中发送其他数据，请直接使用较低级别的函数。
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -一旦调用了这个API，所有的请求头都会被清除，所以如果以后需要的话，需要将请求头复制到单独的缓冲区中。
 *
 * @param[in] r 正在响应的请求
 *
 * @return
 *  -ESP_OK：成功发送响应数据包时
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_RESP_SEND：原始发送错误
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求指针无效
 */
static inline esp_err_t httpd_resp_send_408(httpd_req_t *r) {
    return httpd_resp_send_err(r, HTTPD_408_REQ_TIMEOUT, NULL);
}

/**
 * @brief   HTTP 500的Helper函数
 *
 * 发送HTTP 500消息。如果您希望在响应正文中发送其他数据，请直接使用较低级别的函数。
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -一旦调用了这个API，所有的请求头都会被清除，所以如果以后需要的话，需要将请求头复制到单独的缓冲区中。
 *
 * @param[in] r 正在响应的请求
 *
 * @return
 *  -ESP_OK：成功发送响应数据包时
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_HTTPD_RESP_SEND：原始发送错误
 *  -ESP_ERR_HTTPD_INVALID_REQ:请求指针无效
 */
static inline esp_err_t httpd_resp_send_500(httpd_req_t *r) {
    return httpd_resp_send_err(r, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
}

/**
 * @brief   原始HTTP发送
 *
 * 如果您希望构建自定义响应包，请调用此API。当使用此方法时，所有必要的标头，例如HTTP版本、状态代码、内容类型和长度、编码等，都必须手动构建，并且需要正确放置HTTP delimeter（CRLF），以分离HTTP响应包的子部分。
 *
 * 如果设置了sendoverride函数，该API最终将调用该函数发送数据。
 *
 * @note
 *  -该API应该仅从httpd_req_t请求指针有效的URI处理程序上下文中调用。
 *  -除非响应具有正确的HTTP结构（用户现在必须确保），否则不能保证客户端能够识别它。在大多数情况下，您不必调用此API，但您更希望使用以下任一项：httpd_resp_send（）、httpd_resp.send_chunk（）
 *
 * @param[in] r         正在响应的请求
 * @param[in] buf       从中读取完全构造的数据包的缓冲区
 * @param[in] buf_len   缓冲区长度
 *
 * @return
 *  -Bytes：成功发送的字节数
 *  -HTTPD_SOCK_ERR_INVALID：参数无效
 *  -HTTPD_SOCK_ERR_TIMEOUT:调用套接字send（）时超时/中断
 *  -HTTPD_SOCK_ERR_FAIL：调用套接字send（）时发生不可恢复的错误
 */
int httpd_send(httpd_req_t *r, const char *buf, size_t buf_len);

/**
 * 在给定套接字上发送数据的低级API
 *
 * @note 建议不要在任何请求处理程序中使用此API。仅在高级用例中使用此选项，其中一些异步数据将通过套接字发送。
 *
 * 这在内部调用默认的send函数，或httpd_sess_set_send_override（）注册的函数。
 *
 * @param[in] hd        服务器实例
 * @param[in] sockfd    会话套接字文件描述符
 * @param[in] buf       带有要发送的字节的缓冲区
 * @param[in] buf_len   数据大小
 * @param[in] flags     send（）函数的标志
 * @return
 *  -Bytes：成功发送的字节数
 *  -HTTPD_SOCK_ERR_INVALID：参数无效
 *  -HTTPD_SOCK_ERR_TIMEOUT:调用套接字send（）时超时/中断
 *  -HTTPD_SOCK_ERR_FAIL：调用套接字send（）时发生不可恢复的错误
 */
int httpd_socket_send(httpd_handle_t hd, int sockfd, const char *buf, size_t buf_len, int flags);

/**
 * 从给定套接字接收数据的低级API
 *
 * @note 建议不要在任何请求处理程序中使用此API。仅在需要某些异步通信的高级用例中使用此选项。
 *
 * 这在内部调用默认的recv函数，或httpd_sess_set_recv_override（）注册的函数。
 *
 * @param[in] hd        服务器实例
 * @param[in] sockfd    会话套接字文件描述符
 * @param[in] buf       带有要发送的字节的缓冲区
 * @param[in] buf_len   数据大小
 * @param[in] flags     send（）函数的标志
 * @return
 *  -Bytes：成功接收的字节数
 *  -0:缓冲区长度参数为零/对等方关闭了连接
 *  -HTTPD_SOCK_ERR_INVALID：参数无效
 *  -HTTPD_SOCK_ERR_TIMEOUT:调用套接字recv（）时超时/中断
 *  -HTTPD_SOCK_ERR_FAIL：调用套接字recv（）时发生不可恢复的错误
 */
int httpd_socket_recv(httpd_handle_t hd, int sockfd, char *buf, size_t buf_len, int flags);

/** 请求/响应结束@}
 */

/* **************组：会话***************/
/** @name 用于控制会话和访问上下文数据的会话函数@{
 */

/**
 * @brief   从套接字描述符获取会话上下文
 *
 * 通常，如果创建了会话上下文，则URI处理程序可以通过httpd_req_t结构使用该上下文。但是，在某些情况下，web服务器的发送/接收功能可能需要上下文（例如，用于访问密钥信息等）。由于发送/接收函数只能使用套接字描述符，因此该API为它们提供了检索会话上下文的方法。
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @param[in] sockfd    应该为其提取上下文的套接字描述符。
 *
 * @return
 *  -void*：指向与此会话关联的上下文的指针
 *  -NULL：空上下文/无效句柄/无效套接字fd
 */
void *httpd_sess_get_ctx(httpd_handle_t handle, int sockfd);

/**
 * @brief   通过套接字描述符设置会话上下文
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @param[in] sockfd    应该为其提取上下文的套接字描述符。
 * @param[in] ctx       要分配给会话的上下文对象
 * @param[in] free_fn   应调用以释放上下文的函数
 */
void httpd_sess_set_ctx(httpd_handle_t handle, int sockfd, void *ctx, httpd_free_ctx_fn_t free_fn);

/**
 * @brief   通过套接字描述符获取会话“传输”上下文
 * @see     httpd_sess_get_ctx（）
 *
 * 此上下文由发送/接收函数使用，例如用于管理SSL上下文。
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @param[in] sockfd    应该为其提取上下文的套接字描述符。
 * @return
 *  -void*：指向与此会话关联的传输上下文的指针
 *  -NULL：空上下文/无效句柄/无效套接字fd
 */
void *httpd_sess_get_transport_ctx(httpd_handle_t handle, int sockfd);

/**
 * @brief   通过套接字描述符设置会话“传输”上下文
 * @see     httpd_sess_set_ctx（）
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @param[in] sockfd    应该为其提取上下文的套接字描述符。
 * @param[in] ctx       要分配给会话的传输上下文对象
 * @param[in] free_fn   应调用以释放传输上下文的函数
 */
void httpd_sess_set_transport_ctx(httpd_handle_t handle, int sockfd, void *ctx, httpd_free_ctx_fn_t free_fn);

/**
 * @brief   获取HTTPD全局用户上下文（它是在服务器配置结构中设置的）
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @return 全局用户上下文
 */
void *httpd_get_global_user_ctx(httpd_handle_t handle);

/**
 * @brief   获取HTTPD全局传输上下文（它是在服务器配置结构中设置的）
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @return 全球运输环境
 */
void *httpd_get_global_transport_ctx(httpd_handle_t handle);

/**
 * @brief   从外部触发httpd会话关闭
 *
 * @note    只有在某些应用程序需要异步关闭httpd客户端会话的特殊情况下，才需要调用此API。
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @param[in] sockfd    要关闭的会话的套接字描述符
 *
 * @return
 *  -ESP_OK：成功启动关闭时
 *  -ESP_FAIL：无法对工作进行排队
 *  -ESP_ERR_NOT_FOUND：找不到套接字fd
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t httpd_sess_trigger_close(httpd_handle_t handle, int sockfd);

/**
 * @brief   更新给定插槽的LRU计数器
 *
 * LRU计数器与每个会话内部关联，以监控会话最近交换的通信量。当启用LRU清除时，如果客户端正在请求连接，但已达到套接字/会话的最大数量，则具有最早LRU计数器的会话将自动关闭。
 *
 * 手动更新LRU计数器可以防止套接字由于最近最少使用（LRU）逻辑而被清除，即使它可能有一段时间没有收到流量。当所有打开的套接字/会话都频繁地交换流量，但用户特别希望其中一个会话保持打开，而不管它上次交换数据包的时间是什么时候，这一点都很有用。
 *
 * @note    仅当LRU清除启用选项启用时，才需要调用此API。
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @param[in] sockfd    要更新LRU计数器的会话的套接字描述符
 *
 * @return
 *  -ESP_OK：找到套接字并更新LRU计数器
 *  -ESP_ERR_NOT_FOUND：找不到套接字
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t httpd_sess_update_lru_counter(httpd_handle_t handle, int sockfd);

/**
 * @brief   返回活动会话的当前套接字描述符列表
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @param[in,out] fds   In：提供的client_fds数组的大小Out：client_fds中返回的有效客户端fd的数量，
 * @param[out] client_fds  客户端fds阵列
 *
 * @note 所提供数组的大小必须等于或大于已打开套接字的最大数量，在初始化时使用httpd_config_t结构中的max_open_sockets字段进行配置。
 *
 * @return
 *  -ESP_OK:已成功检索会话列表
 *  -ESP_ERR_INVALID_ARG：错误的参数或列表比提供的数组长
 */
esp_err_t httpd_get_client_list(httpd_handle_t handle, size_t *fds, int *client_fds);

/** 会话结束@}
 */

/* **************组：工作队列***************/
/** @name 与HTTPD工作队列相关的工作队列API@{
 */

/**
 * @brief   HTTPD工作函数的原型有关详细信息，请参阅HTTPD_queue_work（）。
 * @param[in] arg   此工作函数的参数
 */
typedef void (*httpd_work_fn_t)(void *arg);

/**
 * @brief   HTTPD上下文中函数的队列执行
 *
 * 此API将工作函数排队以进行异步执行
 *
 * @note    某些协议要求web服务器生成一些异步数据并将其发送到持久打开的连接。该设施供此类协议使用。
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @param[in] work      指向要在HTTPD上下文中执行的函数的指针
 * @param[in] arg       指向应传递到此函数的参数的指针
 *
 * @return
 *  -ESP_OK：成功排队工作时
 *  -ESP_FAIL：ctrl套接字失败
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t httpd_queue_work(httpd_handle_t handle, httpd_work_fn_t work, void *arg);

/** 组工作队列结束@}
 */

/* **************组：WebSocket***************/
/** @name WebSocket服务器的WebSocket函数和结构@{
 */
#ifdef CONFIG_HTTPD_WS_SUPPORT
/**
 * @brief WebSocket数据包类型的枚举（标头中的操作码）
 * @note 有关详细信息，请参阅RFC6455第5.4节
 */
typedef enum {
    HTTPD_WS_TYPE_CONTINUE   = 0x0,
    HTTPD_WS_TYPE_TEXT       = 0x1,
    HTTPD_WS_TYPE_BINARY     = 0x2,
    HTTPD_WS_TYPE_CLOSE      = 0x8,
    HTTPD_WS_TYPE_PING       = 0x9,
    HTTPD_WS_TYPE_PONG       = 0xA
} httpd_ws_type_t;

/**
 * @brief 客户端信息描述的枚举
 */
typedef enum {
    HTTPD_WS_CLIENT_INVALID        = 0x0,
    HTTPD_WS_CLIENT_HTTP           = 0x1,
    HTTPD_WS_CLIENT_WEBSOCKET      = 0x2,
} httpd_ws_client_info_t;

/**
 * @brief WebSocket框架格式
 */
typedef struct httpd_ws_frame {
    bool final;                 /*!< 最终帧：对于接收的帧，此字段指示是否设置了“FIN”标志。对于要传输的帧，仅当同时设置了“分段”选项时，才使用此字段。如果“fragmented”为false，则默认设置“FIN”标志，将ws_frame标记为完整/未分段消息（esp_http_server不会自动分段消息）*/
    bool fragmented;            /*!< 指示分配用于传输的帧是消息片段，因此根据“final”选项手动设置“FIN”标志。从未为收到的邮件设置此标志*/
    httpd_ws_type_t type;       /*!< WebSocket框架类型*/
    uint8_t *payload;           /*!< 预分配的数据缓冲区*/
    size_t len;                 /*!< WebSocket数据的长度*/
} httpd_ws_frame_t;

/**
 * @brief 传输完成回调
 */
typedef void (*transfer_complete_cb)(esp_err_t err, int socket, void *arg);

/**
 * @brief 接收并解析WebSocket帧
 *
 * @note    调用max_len为0的httpd_ws_recv_frame（）将给出pkt->len中的实际帧大小。用户可以根据这个长度为pkt->负载动态分配空间，并再次调用httpd_ws_recv_frame（）以获取实际数据。请参考相应的示例了解用法。
 *
 * @param[in]   req         当前请求
 * @param[out]  pkt         WebSocket数据包
 * @param[in]   max_len     接收的最大长度
 * @return
 *  -ESP_OK：打开成功
 *  -ESP_FAIL:发生套接字错误
 *  -ESP_ERR_INVALID_STATE:握手已提前完成
 *  -ESP_ERR_INVALID_ARG:参数无效（null或非WebSocket）
 */
esp_err_t httpd_ws_recv_frame(httpd_req_t *req, httpd_ws_frame_t *pkt, size_t max_len);

/**
 * @brief 构造并发送WebSocket框架
 * @param[in]   req     当前请求
 * @param[in]   pkt     WebSocket框架
 * @return
 *  -ESP_OK：打开成功
 *  -ESP_FAIL：发生套接字错误时
 *  -ESP_ERR_INVALID_STATE:握手已提前完成
 *  -ESP_ERR_INVALID_ARG:参数无效（null或非WebSocket）
 */
esp_err_t httpd_ws_send_frame(httpd_req_t *req, httpd_ws_frame_t *pkt);

/**
 * @brief 使用内部配置的httpd-send函数将WebSocket帧发送到当前请求范围之外
 *
 * 除了使用httpd_queue_work异步发送之外，很少直接调用此API。
 *
 * @param[in] hd      服务器实例数据
 * @param[in] fd      用于发送数据的套接字描述符
 * @param[in] frame     WebSocket框架
 * @return
 *  -ESP_OK：打开成功
 *  -ESP_FAIL：发生套接字错误时
 *  -ESP_ERR_INVALID_STATE:握手已提前完成
 *  -ESP_ERR_INVALID_ARG:参数无效（null或非WebSocket）
 */
esp_err_t httpd_ws_send_frame_async(httpd_handle_t hd, int fd, httpd_ws_frame_t *frame);

/**
 * @brief 检查提供的套接字描述符是否属于此服务器实例的任何活动客户端，以及websocket协议是否处于活动状态
 *
 * @param[in] hd      服务器实例数据
 * @param[in] fd      套接字描述符
 * @return
 *  -HTTPD_WS_CLIENT_INVALID：此fd不是此HTTPD的客户端
 *  -HTTPD_WS_CLIENT_HTTP：此fd是活动客户端，协议不是WS
 *  -HTTPD_WS_CLIENT_WEBSOCKET:此fd是一个活动客户端，协议为WS
 */
httpd_ws_client_info_t httpd_ws_get_fd_info(httpd_handle_t hd, int fd);

/**
 * @brief 将数据同步发送到指定的websocket
 *
 * @param[in] handle  服务器实例数据
 * @param[in] socket  套接字描述符
 * @param[in] frame   Websocket框架
 * @return
 *  -ESP_OK：打开成功
 *  -ESP_FAIL：发生套接字错误时
 *  -ESP_ERR_NO_MEM:无法分配内存
 */
esp_err_t httpd_ws_send_data(httpd_handle_t handle, int socket, httpd_ws_frame_t *frame);

/**
 * @brief 将数据异步发送到指定的websocket
 *
 * @param[in] handle    服务器实例数据
 * @param[in] socket    套接字描述符
 * @param[in] frame     Websocket框架
 * @param[in] callback  发送数据后调用回调
 * @param[in] arg       传递给所提供回调的用户数据
 * @return
 *  -ESP_OK：打开成功
 *  -ESP_FAIL：发生套接字错误时
 *  -ESP_ERR_NO_MEM:无法分配内存
 */
esp_err_t httpd_ws_send_data_async(httpd_handle_t handle, int socket, httpd_ws_frame_t *frame,
                                   transfer_complete_cb callback, void *arg);

#endif /* CONFIG_HTTPD_WS_SUPPORT */
/** WebSocket相关内容的结尾@}
 */

#ifdef __cplusplus
}
#endif

#endif /* ! _ESP_HTTP_SERVER_H_ */

