/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

#ifndef _DTLS_DEBUG_H_
#define _DTLS_DEBUG_H_

#include <stdlib.h>

#include "tinydtls.h"
#include "global.h"
#include "session.h"

#ifdef WITH_CONTIKI
# ifndef DEBUG
#  define DEBUG DEBUG_PRINT
# endif /* DEBUG */
#include "net/ip/uip-debug.h"

#ifdef CONTIKI_TARGET_MBXXX
extern char __Stack_Init, _estack;

static inline void check_stack(void) {
  const char *p = &__Stack_Init;
  while (p < &_estack && *p == 0x38) {
    p++;
  }

  PRINTF("Stack: %d bytes used (%d free)\n", &_estack - p, p - &__Stack_Init);
}
#else /* CONTIKI_TARGET_MBXXX */
static inline void check_stack(void) {
}
#endif /* CONTIKI_TARGET_MBXXX */
#else /* WITH_CONTKI */
#define PRINTF(...)

static inline void check_stack(void) {
}
#endif

/**预定义的日志级别与syslog中使用的日志级别类似。*/
typedef enum { DTLS_LOG_EMERG=0, DTLS_LOG_ALERT, DTLS_LOG_CRIT, DTLS_LOG_WARN, 
       DTLS_LOG_NOTICE, DTLS_LOG_INFO, DTLS_LOG_DEBUG
} log_t;

/**返回带有此库名称的以零结尾的字符串。*/
const char *dtls_package_name(void);

/**返回带有库版本的以零结尾的字符串。*/
const char *dtls_package_version(void);

/**返回当前日志级别。*/
log_t dtls_get_log_level(void);

/**将日志级别设置为指定值。*/
void dtls_set_log_level(log_t level);

/** 
 * 将给定文本写入\c stdout。只有当\p级别低于或等于set_log_level（）设置的日志级别时，才会输出文本。*/
#ifdef HAVE_VPRINTF
#if (defined(__GNUC__))
void dsrv_log(log_t level, const char *format, ...) __attribute__ ((format(printf, 2, 3)));
#else /* !__GNUC__ */
void dsrv_log(log_t level, const char *format, ...);
#endif /* !__GNUC__ */
#else
#define dsrv_log(level, format, ...) PRINTF(format, ##__VA_ARGS__)
#endif

/**以通常的hexdump格式转储数据包*/
void hexdump(const unsigned char *packet, int length);

/**转储为十六进制数字的窄字符串*/
void dump(unsigned char *buf, size_t len);

void dtls_dsrv_hexdump_log(log_t level, const char *name, const unsigned char *buf, size_t length, int extend);

void dtls_dsrv_log_addr(log_t level, const char *name, const session_t *addr);

/* 一组通用日志级别的方便宏。*/
#define dtls_emerg(...) dsrv_log(DTLS_LOG_EMERG, __VA_ARGS__)
#define dtls_alert(...) dsrv_log(DTLS_LOG_ALERT, __VA_ARGS__)
#define dtls_crit(...) dsrv_log(DTLS_LOG_CRIT, __VA_ARGS__)
#define dtls_warn(...) dsrv_log(DTLS_LOG_WARN, __VA_ARGS__)
#define dtls_notice(...) dsrv_log(DTLS_LOG_NOTICE, __VA_ARGS__)
#define dtls_info(...) dsrv_log(DTLS_LOG_INFO, __VA_ARGS__)
#define dtls_debug(...) dsrv_log(DTLS_LOG_DEBUG, __VA_ARGS__)
#define dtls_debug_hexdump(name, buf, length) dtls_dsrv_hexdump_log(DTLS_LOG_DEBUG, name, buf, length, 1)
#define dtls_debug_dump(name, buf, length) dtls_dsrv_hexdump_log(DTLS_LOG_DEBUG, name, buf, length, 0)

#endif /* _DTLS_DEBUG_H_ */

