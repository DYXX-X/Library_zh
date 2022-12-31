/*
 * wpa_supplict/hostapd/Debug打印版权所有（c）2002-2007，Jouni Malinen<j@w1.fi>
 *
 * 该程序是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证第2版的条款重新分发和/或修改它。
 *
 * 或者，此软件可以根据BSD许可证条款进行分发。
 *
 * 有关详细信息，请参阅自述和复制。
 */

#ifndef WPA_DEBUG_H
#define WPA_DEBUG_H

#include "wpabuf.h"
#include "esp_log.h"
#include "supplicant_opt.h"

#ifdef ESPRESSIF_USE

#define TAG "wpa"

#define MSG_ERROR ESP_LOG_ERROR
#define MSG_WARNING ESP_LOG_WARN
#define MSG_INFO ESP_LOG_INFO
#define MSG_DEBUG ESP_LOG_DEBUG
#define MSG_MSGDUMP ESP_LOG_VERBOSE
#define MSG_EXCESSIVE ESP_LOG_VERBOSE

#else
enum { MSG_MSGDUMP, MSG_DEBUG, MSG_INFO, MSG_WARNING, MSG_ERROR };
#endif

/**EAP身份验证成功完成*/
#define WPA_EVENT_EAP_SUCCESS "CTRL-EVENT-EAP-SUCCESS "

int wpa_debug_open_file(const char *path);
void wpa_debug_close_file(void);

/**
 * wpa_dbug_printf_tstamp-打印调试输出的时间戳
 *
 * 如果调试输出已配置为在调试消息中包含时间戳，则此函数将以seconds_from_1970.microsoftends格式打印时间戳。
 */
void wpa_debug_print_timestamp(void);

#ifdef DEBUG_PRINT
/**
 * wpa_printf-条件打印
 * @level: 消息的优先级（MSG_*）
 * @fmt: printf格式字符串，后跟可选参数
 *
 * 此函数用于打印条件调试和错误消息。输出可以根据配置定向到stdout、stderr和/或syslog。
 *
 * 注意：当打印到标准输出时，新行“\n”将添加到文本末尾。
 */
#define wpa_printf(level,fmt, args...) ESP_LOG_LEVEL_LOCAL(level, TAG, fmt, ##args)
#define wpa_dbg(ctx, level, fmt, args...) wpa_printf(level, fmt, ##args)

void wpa_dump_mem(char* desc, uint8_t *addr, uint16_t len);
static inline void wpa_hexdump_ascii(int level, const char *title, const u8 *buf, size_t len)
{

}

static inline void wpa_hexdump_ascii_key(int level, const char *title, const u8 *buf, size_t len)
{
}

/**
 * wpa\hexdump-条件十六进制转储
 * @level: 消息的优先级（MSG_*）
 * @title: 邮件的标题
 * @buf: 要转储的数据缓冲区
 * @len: buf的长度
 *
 * 此函数用于打印条件调试和错误消息。输出可以根据配置定向到stdout、stderr和/或syslog。buf的内容被打印出来，具有十六进制转储。
 */
void wpa_hexdump(int level, const char *title, const u8 *buf, size_t len);

static inline void wpa_hexdump_buf(int level, const char *title,
				   const struct wpabuf *buf)
{
	wpa_hexdump(level, title, wpabuf_head(buf), wpabuf_len(buf));
}

/**
 * wpa\hexdump_key-条件十六进制转储，隐藏密钥
 * @level: 消息的优先级（MSG_*）
 * @title: 邮件的标题
 * @buf: 要转储的数据缓冲区
 * @len: buf的长度
 *
 * 此函数用于打印条件调试和错误消息。输出可以根据配置定向到stdout、stderr和/或syslog。buf的内容被打印出来，具有十六进制转储。这与wpa_exdump（）类似，但默认情况下，在调试输出中不包含密钥（密码等）。
 */
void wpa_hexdump_key(int level, const char *title, const u8 *buf, size_t len);


static inline void wpa_hexdump_buf_key(int level, const char *title,
				       const struct wpabuf *buf)
{
	wpa_hexdump_key(level, title, wpabuf_head(buf), wpabuf_len(buf));
}

/**
 * wpa\hexdump_ascii-条件十六进制转储
 * @level: 消息的优先级（MSG_*）
 * @title: 邮件的标题
 * @buf: 要转储的数据缓冲区
 * @len: buf的长度
 *
 * 此函数用于打印条件调试和错误消息。输出可以根据配置定向到stdout、stderr和/或syslog。buf的内容被打印出来。它具有十六进制转储，其中显示了十六进制数字和ASCII字符（用于可打印范围）。将显示每行16字节。
 */
void wpa_hexdump_ascii(int level, const char *title, const u8 *buf,
		       size_t len);

/**
 * wpa\hexdump_asci_key-条件十六进制转储，隐藏密钥
 * @level: 消息的优先级（MSG_*）
 * @title: 邮件的标题
 * @buf: 要转储的数据缓冲区
 * @len: buf的长度
 *
 * 此函数用于打印条件调试和错误消息。输出可以根据配置定向到stdout、stderr和/或syslog。buf的内容被打印出来。它具有十六进制转储，其中显示了十六进制数字和ASCII字符（用于可打印范围）。将显示每行16字节。这与wpa_exdump_ascii（）类似，但默认情况下，在调试输出中不包含密钥（密码等）。
 */
void wpa_hexdump_ascii_key(int level, const char *title, const u8 *buf,
			   size_t len);
#else
#define wpa_printf(level,fmt, args...) do {} while(0)
#define wpa_hexdump(...) do {} while(0)
#define wpa_dump_mem(...) do {} while(0)
#define wpa_hexdump_buf(...) do {} while(0)
#define wpa_hexdump_key(...) do {} while(0)
#define wpa_hexdump_buf_key(...) do {} while(0)
#define wpa_hexdump_ascii(...) do {} while(0)
#define wpa_hexdump_ascii_key(...) do {} while(0)
#define wpa_dbg(...) do {} while(0)
#endif

#define wpa_auth_logger
#define wpa_auth_vlogger

/**
 * wpa\msg-默认目标和ctrl_iface监视器的条件printf
 * @ctx: 指向上下文数据的指针；这是在结构wpa_driver_ops:：init（）中注册的ctx变量
 * @level: 消息的优先级（MSG_*）
 * @fmt: printf格式字符串，后跟可选参数
 *
 * 此函数用于打印条件调试和错误消息。输出可以根据配置定向到stdout、stderr和/或syslog。此函数类似于wpa\printf（），但它也向所有连接的ctrl_iface监视器发送相同的消息。
 *
 * 注意：当打印到标准输出时，新行“\n”将添加到文本末尾。
 */
#define wpa_msg(...) do {} while(0)

/**
 * wpa\msg_ctrl-ctrl_iface监视器的条件打印
 * @ctx: 指向上下文数据的指针；这是在结构wpa_driver_ops:：init（）中注册的ctx变量
 * @level: 消息的优先级（MSG_*）
 * @fmt: printf格式字符串，后跟可选参数
 *
 * 此函数用于打印条件调试和错误消息。此函数类似于wpa\msg（），但它只将输出发送给附加的ctrl_iface监视器。换句话说，它可以用于不需要发送到syslog的频繁事件。
 */
void wpa_msg_ctrl(void *ctx, int level, const char *fmt, ...)
PRINTF_FORMAT(3, 4);

typedef void (*wpa_msg_cb_func)(void *ctx, int level, const char *txt,
				size_t len);

typedef void (*eloop_timeout_handler)(void *eloop_data, void *user_ctx);

int eloop_cancel_timeout(eloop_timeout_handler handler,
			 void *eloop_data, void *user_data);

int eloop_register_timeout(unsigned int secs, unsigned int usecs,
			   eloop_timeout_handler handler,
			   void *eloop_data, void *user_data);


#endif /* WPA_DEBUG_H */

