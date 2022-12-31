/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


#ifndef _HTTPD_PRIV_H_
#define _HTTPD_PRIV_H_

#include <stdbool.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <esp_log.h>
#include <esp_err.h>

#include <esp_http_server.h>
#include "osal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 在解析过程的一个回合中接收和解析的请求数据块/块的大小（不要与分块编码数据混淆）。这不应超过临时缓冲区大小，并且至少应为8字节*/
#define PARSER_BLOCK_SIZE  128

/* 计算暂存缓冲区所需的最大大小*/
#define HTTPD_SCRATCH_BUF  MAX(HTTPD_MAX_REQ_HDR_LEN, HTTPD_MAX_URI_LEN)

/* 格式化日志字符串以在上下文函数名称前加上前缀*/
#define LOG_FMT(x)      "%s: " x, __func__

/**
 * @brief 供内部使用的线程相关数据
 */
struct thread_data {
    othread_t handle;   /*!< 线程/任务句柄*/
    enum {
        THREAD_IDLE = 0,
        THREAD_RUNNING,
        THREAD_STOPPING,
        THREAD_STOPPED,
    } status;           /*!< 线程的状态*/
};

/**
 * @brief 系统中所有打开套接字的数据库。
 */
struct sock_db {
    int fd;                                 /*!< 此套接字的文件描述符*/
    void *ctx;                              /*!< 此套接字的自定义上下文*/
    bool ignore_sess_ctx_changes;           /*!< 指示是否应忽略会话上下文更改的标志*/
    void *transport_ctx;                    /*!< 此套接字的自定义“传输”上下文，供send/recv/pending使用*/
    httpd_handle_t handle;                  /*!< 服务器句柄*/
    httpd_free_ctx_fn_t free_ctx;      /*!< 释放上下文的函数*/
    httpd_free_ctx_fn_t free_transport_ctx; /*!< 释放“传输”上下文的函数*/
    httpd_send_func_t send_fn;              /*!< 此套接字的发送函数*/
    httpd_recv_func_t recv_fn;              /*!< 此套接字的接收函数*/
    httpd_pending_func_t pending_fn;        /*!< 此套接字的挂起函数*/
    uint64_t lru_counter;                   /*!< LRU计数器，指示插座上次使用的时间*/
    bool lru_socket;                        /*!< 指示LRU插座的标志*/
    char pending_data[PARSER_BLOCK_SIZE];   /*!< 待接收数据的缓冲区*/
    size_t pending_len;                     /*!< 待接收的待处理数据的长度*/
#ifdef CONFIG_HTTPD_WS_SUPPORT
    bool ws_handshake_done;                 /*!< 如果已完成WebSocket握手，则为True（如果此套接字是有效的WS）*/
    bool ws_close;                          /*!< 设置为true以稍后关闭套接字（当收到WS-close帧时）*/
    esp_err_t (*ws_handler)(httpd_req_t *r);   /*!< WebSocket处理程序，如果不是WebSocket，则保留为空*/
    bool ws_control_frames;                         /*!< WebSocket标志，指示应将控制帧传递给用户处理程序*/
    void *ws_user_ctx;                         /*!< 指向可用于websocket处理程序的用户上下文数据的指针*/
#endif
};

/**
 * @brief   用于接收和处理请求以及临时保存响应的辅助数据结构
 */
struct httpd_req_aux {
    struct sock_db *sd;                             /*!< 指向套接字数据库的指针*/
    char            scratch[HTTPD_SCRATCH_BUF + 1]; /*!< 我们的操作的临时缓冲区（空终止额外1字节）*/
    size_t          remaining_len;                  /*!< 要提取的剩余数据量*/
    char           *status;                         /*!< HTTP响应的状态代码*/
    char           *content_type;                   /*!< HTTP响应的内容类型*/
    bool            first_chunk_sent;               /*!< 用于指示是否发送了第一个块*/
    unsigned        req_hdrs_count;                 /*!< 请求数据包中的标头总数*/
    unsigned        resp_hdrs_count;                /*!< 响应数据包中其他标头的计数*/
    struct resp_hdr {
        const char *field;
        const char *value;
    } *resp_hdrs;                                   /*!< 响应包中的其他标头*/
    struct http_parser_url url_parse_res;           /*!< URL分析结果，用于检索URL元素*/
#ifdef CONFIG_HTTPD_WS_SUPPORT
    bool ws_handshake_detect;                       /*!< WebSocket握手检测标志*/
    httpd_ws_type_t ws_type;                        /*!< WebSocket框架类型*/
    bool ws_final;                                  /*!< WebSocket FIN位（是否为最终帧）*/
    uint8_t mask_key[4];                            /*!< 此负载的WebSocket掩码密钥*/
#endif
};

/**
 * @brief   每个实例的服务器数据。它公开为httpd_handle_t，但内部结构/成员保持私有。
 */
struct httpd_data {
    httpd_config_t config;                  /*!< HTTPD服务器配置*/
    int listen_fd;                          /*!< 服务器侦听器FD*/
    int ctrl_fd;                            /*!< Ctrl消息接收器FD*/
    int msg_fd;                             /*!< Ctrl消息发送器FD*/
    struct thread_data hd_td;               /*!< HTTPD线程的信息*/
    struct sock_db *hd_sd;                  /*!< 套接字数据库*/
    int hd_sd_active_count;                 /*!< 活动套接字的数量*/
    httpd_uri_t **hd_calls;                 /*!< 已注册的URI处理程序*/
    struct httpd_req hd_req;                /*!< 当前HTTPD请求*/
    struct httpd_req_aux hd_req_aux;        /*!< 关于HTTPD请求的其他数据未公开*/
    uint64_t lru_counter;                   /*!< LRU计数器*/

    /* 已注册错误处理程序函数的数组*/
    httpd_err_handler_func_t *err_handler_fns;
};

/*******************组：会话管理********************/
/** @name 与HTTP会话管理相关的会话管理功能@{
 */

// 将为每个会话调用的枚举函数
typedef int (*httpd_session_enum_function)(struct sock_db *session, void *context);

/**
 * @brief  枚举所有会话
 *
 * @param[in] hd            服务器实例数据
 * @param[in] enum_function 枚举函数，将为每个会话调用
 * @param[in] context       将传递给枚举函数的上下文
 */
void httpd_sess_enum(struct httpd_data *hd, httpd_session_enum_function enum_function, void *context);

/**
 * @brief   返回下一个空闲会话槽（fd＜0）
 *
 * @param[in] hd    服务器实例数据
 *
 * @return
 *  -+VE：空闲会话槽
 *  -NULL：迭代结束
 */
struct sock_db *httpd_sess_get_free(struct httpd_data *hd);

/**
 * @brief 按会话描述符检索会话
 *
 * @param[in] hd     服务器实例数据
 * @param[in] sockfd 插座FD
 * @return 指向套接字DB的指针，如果找不到，则返回NULL
 */
struct sock_db *httpd_sess_get(struct httpd_data *hd, int sockfd);

/**
 * @brief 删除FD无效的会话。这是一种恢复策略，例如在select（）失败后。
 *
 * @param[in] hd    服务器实例数据
 */
void httpd_sess_delete_invalid(struct httpd_data *hd);

/**
 * @brief   通过重置套接字数据库初始化http会话。
 *
 * @param[in] hd    服务器实例数据
 */
void httpd_sess_init(struct httpd_data *hd);

/**
 * @brief   为请求连接的客户端启动新会话，并将其描述符添加到套接字数据库。
 *
 * @param[in] hd    服务器实例数据
 * @param[in] newfd 要添加到会话的新客户端的描述符。
 *
 * @return
 *  -ESP_OK:成功排队工作
 *  -ESP_FAIL：发送时发生控制套接字错误
 */
esp_err_t httpd_sess_new(struct httpd_data *hd, int newfd);

/**
 * @brief   处理传入的HTTP请求
 *
 * @param[in] hd      服务器实例数据
 * @param[in] session 一场
 *
 * @return
 *  -ESP_OK：成功接收、解析和响应请求
 *  -ESP_FAIL：在任何处理阶段出现故障的情况下
 */
esp_err_t httpd_sess_process(struct httpd_data *hd, struct sock_db *session);

/**
 * @brief   从会话/套接字数据库中删除客户端描述符，并关闭此客户端的连接。
 *
 * @param[in] hd      服务器实例数据
 * @param[in] session 一场
 */
void httpd_sess_delete(struct httpd_data *hd, struct sock_db *session);

/**
 * @brief   自由会话上下文
 *
 * @param[in] ctx     指向会话上下文的指针
 * @param[in] free_fn 调用会话上下文的自由函数
 */
void httpd_sess_free_ctx(void **ctx, httpd_free_ctx_fn_t free_fn);

/**
 * @brief   将套接字数据库中的描述符添加到fdset，并更新maxfd的值，select函数需要该值来查找所有可用的套接字以获取传入数据。
 *
 * @param[in]  hd    服务器实例数据
 * @param[out] fdset 要更新的文件描述符集。
 * @param[out] maxfd 所有文件描述符中的最大值。
 */
void httpd_sess_set_descriptors(struct httpd_data *hd, fd_set *fdset, int *maxfd);

/**
 * @brief   检查会话是否可以接受来自新客户端的其他连接。如果套接字数据库已满，则返回false。
 *
 * @param[in] hd  服务器实例数据
 *
 * @return 如果会话可以接受新客户端，则为True
 */
bool httpd_is_sess_available(struct httpd_data *hd);

/**
 * @brief   检查会话是否有任何待处理的数据/数据包
 *
 * 这是需要的，因为httpd_unrecv可能无法接收流中的下一个数据包。如果只接收到部分数据包，则select（）将标记fd进行处理，因为数据包的剩余部分仍在套接字recv队列中。但是如果一个完整的数据包没有被接收到，那么它将不会被处理，直到在套接字上接收到更多的数据。这是该函数开始使用的时候，因为它检查套接字的挂起数据缓冲区。
 *
 * @param[in] hd      服务器实例数据
 * @param[in] session 一场
 *
 * @return 如果有任何待定数据，则为True
 */
bool httpd_sess_pending(struct httpd_data *hd, struct sock_db *session);

/**
 * @brief   从会话中删除最近最少使用的客户端
 *
 * 如果新客户端正在请求连接，但已达到最大连接数，则这可能很有用，在这种情况下，将从会话中删除最长时间处于非活动状态的客户端。
 *
 * @param[in] hd  服务器实例数据
 *
 * @return
 *  -ESP_OK：如果会话关闭成功启动
 *  -ESP_FAIL：如果失败
 */
esp_err_t httpd_sess_close_lru(struct httpd_data *hd);

/**
 * @brief   关闭所有会话
 *
 * @param[in] hd  服务器实例数据
 *
 */
void httpd_sess_close_all(struct httpd_data *hd);

/** 组结束：会话管理@}
 */

/******************组：URI处理********************/
/** @name 用于访问URI处理程序的URI处理方法@{
 */

/**
 * @brief   对于HTTP请求，搜索所有注册的URI处理程序，如果找到，则调用相应的处理程序
 *
 * @param[in] hd  需要为其调用处理程序的服务器实例数据
 *
 * @return
 *  -ESP_OK：如果成功找到并执行了处理程序
 *  -ESP_FAIL：否则
 */
esp_err_t httpd_uri(struct httpd_data *hd);

/**
 * @brief   注销所有URI处理程序
 *
 * @param[in] hd  服务器实例数据
 */
void httpd_unregister_all_uri_handlers(struct httpd_data *hd);

/**
 * @brief   验证请求以防止用户调用API，这些API只能在URI处理程序内部或处理程序上下文外部调用
 *
 * @param[in] req 指向需要验证的HTTP请求的指针
 *
 * @return
 *  -true：如果请求有效
 *  -false：否则
 */
bool httpd_validate_req_ptr(httpd_req_t *r);

/* httpd_validate_req_ptr（）为常用的API增加了一些开销，并且主要用于调试，因此最好在默认情况下禁用检查，并仅在必要时启用它*/
#ifdef CONFIG_HTTPD_VALIDATE_REQ
#define httpd_valid_req(r)  httpd_validate_req_ptr(r)
#else
#define httpd_valid_req(r)  true
#endif

/** 组结尾：URI处理@}
 */

/******************组：处理********************/
/** @name 处理HTTP请求的处理方法@{
 */

/**
 * @brief   启动HTTP请求的处理
 *
 * 在套接字上接收传入的TCP数据包，然后将该数据包解析为HTTP请求，并用提取的URI填充httpd_req_t数据结构，头准备好从暂存缓冲区中提取，并在读取请求主体后调用HTTP_recv（）。
 *
 * @param[in] hd  服务器实例数据
 * @param[in] sd  指向接收TCP数据包所需的套接字的指针。
 *
 * @return
 *  -ESP_OK：如果请求包有效
 *  -ESP_FAIL：否则
 */
esp_err_t httpd_req_new(struct httpd_data *hd, struct sock_db *sd);

/**
 * @brief   对于HTTP请求，重置为其分配的资源，并清除剩余的待接收数据
 *
 * @param[in] hd  服务器实例数据
 *
 * @return
 *  -ESP_OK：如果请求包已删除且资源已清理。
 *  -ESP_FAIL：否则。
 */
esp_err_t httpd_req_delete(struct httpd_data *hd);

/**
 * @brief   用于通过调用注册的错误处理程序函数来处理HTTP错误
 *
 * @param[in] req     指向发生错误的HTTP请求的指针
 * @param[in] error   错误类型
 *
 * @return
 *  -ESP_OK：错误处理成功
 *  -ESP_FAIL：失败表示需要关闭基础套接字
 */
esp_err_t httpd_req_handle_err(httpd_req_t *req, httpd_err_code_t error);

/** 组结尾：正在分析@｝
 */

/******************组：发送/接收********************/
/** @name 发送和接收HTTP请求和响应的方法@{
 */

/**
 * @brief   用于响应HTTP请求发送数据。
 *
 * @param[in] req     指向需要发送响应的HTTP请求的指针
 * @param[in] buf     指向从中获取响应主体的缓冲区的指针
 * @param[in] buf_len 缓冲区长度
 *
 * @return
 *  -数据长度：如果成功
 *  -ESP_FAIL：如果失败
 */
int httpd_send(httpd_req_t *req, const char *buf, size_t buf_len);

/**
 * @brief   用于接收HTTP请求数据
 *
 * @note    公开的API httpd_recv（）只是最后一个参数设置为false的函数。此功能在接收和处理新请求时在内部使用。在接收到挂起数据后停止的选项防止服务器请求比完成数据包所需的更多数据，以防数据包的所有剩余部分都在挂起缓冲区中。
 *
 * @param[in]  req    指向仅具有套接字描述符的新HTTP请求的指针
 * @param[out] buf    指向将填充接收数据的缓冲区的指针
 * @param[in] buf_len 缓冲区长度
 * @param[in] halt_after_pending 设置为true时，从挂起缓冲区接收后立即停止
 *
 * @return
 *  -数据长度：如果成功
 *  -ESP_FAIL：如果失败
 */
int httpd_recv_with_opt(httpd_req_t *r, char *buf, size_t buf_len, bool halt_after_pending);

/**
 * @brief   用于取消接收HTTP请求数据
 *
 * 此函数将数据复制到内部缓冲区pending_data中，以便在调用httpd_recv时，首先获取该挂起数据，然后仅开始从套接字接收
 *
 * @note    如果数据对于内部缓冲区来说太大，则只有部分数据未被接收，反映在返回的长度中。确保检查并正确处理此类截断。
 *
 * @param[in] req     指向仅具有套接字描述符的新HTTP请求的指针
 * @param[in] buf     指向需要从中取消接收数据的缓冲区的指针
 * @param[in] buf_len 缓冲区长度
 *
 * @return  复制到挂起缓冲区的数据长度
 */
size_t httpd_unrecv(struct httpd_req *r, const char *buf, size_t buf_len);

/**
 * @brief   这是HTTPD的低级默认发送功能。不得直接调用。其语义与BSD套接字API的send（）完全相似。
 *
 * @param[in] hd      服务器实例数据
 * @param[in] sockfd  用于发送数据的套接字描述符
 * @param[in] buf     指向从中获取响应主体的缓冲区的指针
 * @param[in] buf_len 缓冲区长度
 * @param[in] flags   模式选择标志
 *
 * @return
 *  -数据长度：如果成功
 *  --1：如果失败（设置了相应的错误号）
 */
int httpd_default_send(httpd_handle_t hd, int sockfd, const char *buf, size_t buf_len, int flags);

/**
 * @brief   这是HTTPD的低级别默认recv函数。不得直接调用。其语义与BSD套接字API的recv（）完全相似。
 *
 * @param[in] hd      服务器实例数据
 * @param[in] sockfd  用于发送数据的套接字描述符
 * @param[out] buf    指向将填充接收数据的缓冲区的指针
 * @param[in] buf_len 缓冲区长度
 * @param[in] flags   模式选择标志
 *
 * @return
 *  -数据长度：如果成功
 *  --1：如果失败（设置了相应的错误号）
 */
int httpd_default_recv(httpd_handle_t hd, int sockfd, char *buf, size_t buf_len, int flags);

/** 组结束：发送和接收@}
 */

/* **************组：WebSocket***************/
/** @name 用于WebSocket头解析的WebSocket函数@{
 */


/**
 * @brief   此函数用于响应WebSocket握手
 *
 * @param[in] req                       指向将处理的握手请求的指针
 * @param[in] supported_subprotocol     指向此URI支持的子协议的指针
 * @return
 *  -ESP_OK：握手成功时
 *  -ESP_ERR_NOT_FOUND：未找到某些标头（Sec WebSocket-*）时
 *  -ESP_ERR_INVALID_VERSION:WebSocket版本不是“13”
 *  -ESP_ERR_INVALID_STATE:握手已提前完成
 *  -ESP_ERR_INVALID_ARG:参数无效（null或非WebSocket）
 *  -ESP_FAIL:套接字故障
 */
esp_err_t httpd_ws_respond_server_handshake(httpd_req_t *req, const char *supported_subprotocol);

/**
 * @brief   此函数用于获取帧类型并自动响应WebSocket控制帧
 *
 * @param[in] req    指向将处理的握手请求的指针
 * @return
 *  -ESP_OK：握手成功时
 *  -ESP_ERR_INVALID_ARG:参数无效（null或非WebSocket）
 *  -ESP_ERR_INVALID_STATE：仅接收控制帧的某些部分
 *  -ESP_FAIL:套接字故障
 */
esp_err_t httpd_ws_get_frame_type(httpd_req_t *req);

/**
 * @brief   从外部触发httpd会话关闭
 *
 * @note    只有在某些应用程序需要异步关闭httpd客户端会话的特殊情况下，才需要调用此API。
 *
 * @param[in] handle    httpd_start返回的服务器句柄
 * @param[in] session   要关闭的会话
 *
 * @return
 *  -ESP_OK：成功启动关闭时
 *  -ESP_FAIL：无法对工作进行排队
 *  -ESP_ERR_NOT_FOUND：找不到套接字fd
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t httpd_sess_trigger_close_(httpd_handle_t handle, struct sock_db *session);

/** WebSocket相关函数@}的结尾
 */

#ifdef __cplusplus
}
#endif

#endif /* ! _HTTPD_PRIV_H_ */

