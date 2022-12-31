#ifndef LWIP_HDR_APPS_SMTP_H
#define LWIP_HDR_APPS_SMTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lwip/apps/smtp_opts.h"
#include "lwip/err.h"
#include "lwip/prot/iana.h"

/**用于SMTP的默认TCP端口*/
#define SMTP_DEFAULT_PORT         LWIP_IANA_PORT_SMTP
/**用于SMTPS的默认TCP端口*/
#define SMTPS_DEFAULT_PORT        LWIP_IANA_PORT_SMTPS

/**电子邮件已成功发送*/
#define SMTP_RESULT_OK            0
/**未知错误*/
#define SMTP_RESULT_ERR_UNKNOWN   1
/**连接到服务器失败*/
#define SMTP_RESULT_ERR_CONNECT   2
/**无法解析服务器主机名*/
#define SMTP_RESULT_ERR_HOSTNAME  3
/**远程服务器意外关闭了连接*/
#define SMTP_RESULT_ERR_CLOSED    4
/**连接超时（服务器未及时响应）*/
#define SMTP_RESULT_ERR_TIMEOUT   5
/**服务器响应了未知的响应代码*/
#define SMTP_RESULT_ERR_SVR_RESP  6
/**本地资源不足*/
#define SMTP_RESULT_ERR_MEM       7

/** smtp回调函数的原型
 *
 * @param arg 启动电子邮件时指定的参数
 * @param smtp_result 邮件传输的结果（请参见定义SMTP_result_*）
 * @param srv_err 如果被服务器中止，则包含收到的错误代码
 * @param err 内部lwip函数返回的错误可以帮助指定错误的来源，但不一定是！=错误（_O）
 */
typedef void (*smtp_result_fn)(void *arg, u8_t smtp_result, u16_t srv_err, err_t err);

/** 此结构用作smtp_send_mail_int（）的参数，它又可以与tcpip_callback（）一起用于从中断上下文发送邮件，例如：struct smtp_send _request req；（待填充）tcpip_try_callback（smtp_send_mail_int，（void）req）；
 *
 * 有关成员描述，请参见smtp_send_mail（）的参数描述。与tcpip_callback一起使用时，此结构必须保持分配状态（例如使用mem_malloc/mem_free），直到调用其“callback_fn”。
 */
struct smtp_send_request {
  const char *from;
  const char* to;
  const char* subject;
  const char* body;
  smtp_result_fn callback_fn;
  void* callback_arg;
  /**如果是！=0，数据*未*复制到额外缓冲区中，而是从此结构中提供的指针中使用。这意味着更少的内存使用，但在调用回调函数之前，数据必须保持不变。*/
  u8_t static_data;
};


#if SMTP_BODYDH

#ifndef SMTP_BODYDH_BUFFER_SIZE
#define SMTP_BODYDH_BUFFER_SIZE 256
#endif /* SMTP_BODYDH_BUFFER_SIZE */

struct smtp_bodydh {
  u16_t state;
  u16_t length; /* 缓冲区中内容的长度*/
  char buffer[SMTP_BODYDH_BUFFER_SIZE]; /* 生成内容的缓冲区*/
#ifdef SMTP_BODYDH_USER_SIZE
  u8_t user[SMTP_BODYDH_USER_SIZE];
#endif /* SMTP_BODYDH_USER_SIZE */
};

enum bdh_retvals_e {
  BDH_DONE = 0,
  BDH_WORKING
};

/** smtp主体回调函数的原型它接收结构smtp_bodydh和用于写入数据的缓冲区，必须返回BDH_WORKING以再次调用，并且在完成处理后返回BDH_DONE。这一个尝试用数据填充一个TCP缓冲区，您的函数将被重复调用，直到发生这种情况；因此，如果你知道你需要很长时间来满足你的请求，那么就偶尔暂停一下，写length=0，以避免占用系统资源
 *
 * @param arg 启动电子邮件时指定的参数
 * @param smtp_bodydh 状态处理+缓冲结构
 */
typedef int (*smtp_bodycback_fn)(void *arg, struct smtp_bodydh *bodydh);

err_t smtp_send_mail_bodycback(const char *from, const char* to, const char* subject,
                     smtp_bodycback_fn bodycback_fn, smtp_result_fn callback_fn, void* callback_arg);

#endif /* SMTP_BODYDH */


err_t smtp_set_server_addr(const char* server);
void smtp_set_server_port(u16_t port);
#if LWIP_ALTCP && LWIP_ALTCP_TLS
struct altcp_tls_config;
void smtp_set_tls_config(struct altcp_tls_config *tls_config);
#endif
err_t smtp_set_auth(const char* username, const char* pass);
err_t smtp_send_mail(const char *from, const char* to, const char* subject, const char* body,
                     smtp_result_fn callback_fn, void* callback_arg);
err_t smtp_send_mail_static(const char *from, const char* to, const char* subject, const char* body,
                     smtp_result_fn callback_fn, void* callback_arg);
void smtp_send_mail_int(void *arg);
#ifdef LWIP_DEBUG
const char* smtp_result_str(u8_t smtp_result);
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_SMTP_H */

