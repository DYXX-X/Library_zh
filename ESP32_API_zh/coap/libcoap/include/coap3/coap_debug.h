/*
 * coap_debug。h—调试实用程序
 *
 * 版权所有（C）2010-20112014 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_DEBUG_H_
#define COAP_DEBUG_H_

/**
 * @defgroup 日志记录支持用于日志记录支持的API函数@{
 */

#ifndef COAP_DEBUG_FD
/**
 * Used for output for @c LOG_DEBUG到@c LOG_ERR。
 */
#define COAP_DEBUG_FD stdout
#endif

#ifndef COAP_ERR_FD
/**
 * Used for output for @c LOG_CRIT到@c LOG_EMERG。
 */
#define COAP_ERR_FD stderr
#endif

#ifdef HAVE_SYSLOG_H
#include <syslog.h>
/**
 * 日志记录类型。@b syslog中的LOG_*之一。
 */
typedef short coap_log_t;
/*
   LOG_DEBUG+2在GnuTLS中提供密码。使用COAP_LOG_ciphers在OpenSSL等中输出密码信息。
 */
#define COAP_LOG_CIPHERS (LOG_DEBUG+2)
#else /* !HAVE_SYSLOG_H */
/**预定义的日志级别类似于添加了log_CIPHERS的syslog中使用的日志级别。*/

#if !defined(RIOT_VERSION)
typedef enum {
  LOG_EMERG=0, /**<紧急情况*/
  LOG_ALERT,   /**<警报*/
  LOG_CRIT,    /**<关键*/
  LOG_ERR,     /**<错误*/
  LOG_WARNING, /**<警告*/
  LOG_NOTICE,  /**<通知*/
  LOG_INFO,    /**<信息*/
  LOG_DEBUG,   /**<调试*/
  COAP_LOG_CIPHERS=LOG_DEBUG+2 /**<密码信息*/
} coap_log_t;
#else /* RIOT_VERSION */
/* RIOT定义了日志中syslog级别的子集。h具有不同的数值。其余级别在此处定义。请注意，输出粒度与遵循syslog级别时的预期粒度不同。
 */
#include <log.h>
typedef short coap_log_t;
#define LOG_EMERG  (0)
#define LOG_ALERT  (1)
#define LOG_CRIT   (2)
#define LOG_ERR    (3)
/*  LOG_WARNING    (4) */
#define LOG_NOTICE (5)
/*  LOG_INFO       (6) */
/*  LOG_DEBUG      (7) */
#define COAP_LOG_CIPHERS (9)
#endif /* RIOT_VERSION */

#endif /* !HAVE_SYSLOG_H */

/**
 * 获取当前日志记录级别。
 *
 * @return LOG_*值之一。
 */
coap_log_t coap_get_log_level(void);

/**
 * 将日志级别设置为指定值。
 *
 * @param level LOG_*值之一。
 */
void coap_set_log_level(coap_log_t level);

/**
 * 记录回调处理程序定义。
 *
 * @param level LOG_*值之一。
 * @param message 要记录的以零结尾的字符串消息。
 */
typedef void (*coap_log_handler_t) (coap_log_t level, const char *message);

/**
 * 添加自定义日志回调处理程序。
 *
 * @param handler 要使用的日志处理程序，或使用默认处理程序的@p NULL。
 */
void coap_set_log_handler(coap_log_handler_t handler);

/**
 * 获取库包名称。
 *
 * @return 带有此库名称的以零结尾的字符串。
 */
const char *coap_package_name(void);

/**
 * 获取库包版本。
 *
 * @return 带有库版本的以零结尾的字符串。
 */
const char *coap_package_version(void);

/**
 * Writes the given text to @c COAP_ERR_FD（用于@p级别<=@c LOG_CRIT）或@c
 * COAP_DEBUG_FD (for @p level>=@c LOG_ERR）。文本仅在以下情况下输出
 * @p level低于或等于coap_set_log_level（）设置的日志级别。
 *
 * 内部功能。
 *
 * @param level LOG_*值之一。
 &@param format要使用的格式字符串。
 */
#if (defined(__GNUC__))
void coap_log_impl(coap_log_t level,
              const char *format, ...) __attribute__ ((format(printf, 2, 3)));
#else
void coap_log_impl(coap_log_t level, const char *format, ...);
#endif

#ifndef coap_log
/**
 * 日志记录功能。
 * Writes the given text to @c COAP_ERR_FD（用于@p级别<=@c LOG_CRIT）或@c
 * COAP_DEBUG_FD (for @p level>=@c LOG_ERR）。文本仅在以下情况下输出
 * @p level低于或等于coap_set_log_level（）设置的日志级别。
 *
 * @param level LOG_*值之一。
 */
#define coap_log(level, ...) do { \
  if ((int)((level))<=(int)coap_get_log_level()) \
     coap_log_impl((level), __VA_ARGS__); \
} while(0)
#endif

#include "pdu.h"

/**
 * 定义coap_show_pdu（）函数的输出模式。
 *
 * @param use_fprintf @p 1如果输出使用fprintf（）（默认值）
 *                    @p 如果输出要使用coap_log（），则为0。
 */
void coap_set_show_pdu_output(int use_fprintf);

/**
 * Display the contents of the specified @p pdu。注意：coap_show_pdu（）的输出方法取决于coap_set_show_pdu_output（）的设置。
 *
 * @param level 所需的最低日志记录级别。
 * @param pdu 要解码的PDU。
 */
void coap_show_pdu(coap_log_t level, const coap_pdu_t *pdu);

/**
 * 显示当前（D）TLS库，该库链接到并为版本构建。
 *
 * @param level 所需的最低日志记录级别。
 */
void coap_show_tls_version(coap_log_t level);

/**
 * 生成一个字符串，该字符串包含与链接并为版本生成的当前（D）TLS库。
 *
 * @param buffer 要将字符串放入的缓冲区。
 * @param bufsize 要放入字符串的缓冲区的大小。
 *
 * @return 指向所提供缓冲区的指针。
 */
char *coap_string_tls_version(char *buffer, size_t bufsize);

/**
 * 构建包含当前（D）TLS库支持的字符串
 *
 * @param buffer 要将字符串放入的缓冲区。
 * @param bufsize 要放入字符串的缓冲区的大小。
 *
 * @return 指向所提供缓冲区的指针。
 */
char *coap_string_tls_support(char *buffer, size_t bufsize);

/**
 * 将地址打印到定义的缓冲区中。
 *
 * 内部功能。
 *
 * @param address 要打印的地址。
 * @param buffer 要打印到的缓冲区。
 * @param size 要打印到的缓冲区的大小。
 *
 * @return 写入缓冲区的量。
 */
size_t coap_print_addr(const coap_address_t *address,
                       unsigned char *buffer, size_t size);

/** @} */

/**
 * 设置测试的数据包丢失级别。这可以是两种形式之一。
 *
 * 百分比：0%至100%。使用指定的概率。0%是发送所有数据包，100%是丢弃所有数据包。
 *
 * 列表：要丢弃的数据包的数字或数字范围的逗号分隔列表。
 *
 * @param loss_level 定义的损失水平（百分比或列表）。
 *
 * @return @c 1如果设置了损失级别，@c 0如果有错误。
 */
int coap_debug_set_packet_loss(const char *loss_level);

/**
 * 检查是否应发送数据包。
 *
 * 内部功能
 *
 * @return @c 1如果要发送数据包，@c 0如果要丢弃数据包。
 */
int coap_debug_send_packet(void);


#endif /* COAP_DEBUG_H_ */

