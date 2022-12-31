/*
 * 操作系统特定功能版权所有（c）2005-2009，Jouni Malinen<j@w1.fi>
 *
 * 该程序是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证第2版的条款重新分发和/或修改它。
 *
 * 或者，此软件可以根据BSD许可证条款进行分发。
 *
 * 有关详细信息，请参阅自述和复制。
 */

#ifndef OS_H
#define OS_H
#include "esp_types.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "esp_err.h"
#include "supplicant_opt.h"

typedef time_t os_time_t;

/**
 * os_sleep-睡眠（秒，usec）
 * @sec: 睡眠秒数
 * @usec: 休眠微秒数
 */
void os_sleep(os_time_t sec, os_time_t usec);

struct os_time {
	os_time_t sec;
	suseconds_t usec;
};

#define os_reltime os_time

struct os_tm {
    int sec; /* 0..59或60表示闰秒*/
    int min; /* 0..59 */
    int hour; /* 0..23 */
    int day; /* 1..31 */
    int month; /* 1..12 */
    int year; /* 四位数年份*/
};

/**
 * os_get_time-获取当前时间（秒，usec）
 * @t: 指向时间缓冲区的指针返回：成功时返回0，失败时返回-1
 */
int os_get_time(struct os_time *t);
#define os_get_reltime os_get_time

/* 用于处理结构os_time的帮助程序宏*/

#define os_time_before(a, b) \
	((a)->sec < (b)->sec || \
	 ((a)->sec == (b)->sec && (a)->usec < (b)->usec))

#define os_reltime_before os_time_before
#define os_time_sub(a, b, res) do { \
	(res)->sec = (a)->sec - (b)->sec; \
	(res)->usec = (a)->usec - (b)->usec; \
	if ((res)->usec < 0) { \
		(res)->sec--; \
		(res)->usec += 1000000; \
	} \
} while (0)
#define os_reltime_sub os_time_sub

/**
 * os_mktime-将自1970-01-01以来的故障时间转换为秒
 * @year: 四位数年份
 * @month: 月份（1..12）
 * @day: 月日（1..31）
 * @hour: 小时（0..23）
 * @min: 分钟（0..59）
 * @sec: 秒（0..60）
 * @t: 用于返回日历时间表示的缓冲区（自1970-01-01 00:00:00以来的秒）返回：成功时为0，失败时为-1
 *
 * 注意：结果以Epoch的秒为单位，即UTC，而不是POSIX mktime（）使用的本地时间。
 */
int os_mktime(int year, int month, int day, int hour, int min, int sec,
	      os_time_t *t);

int os_gmtime(os_time_t t, struct os_tm *tm);

/**
 * os_daemonize-在后台运行（与控制终端分离）
 * @pid_file: 要将进程ID写入的文件名或要跳过此操作的%NULL返回：成功时返回0，失败时返回-1
 */
int os_daemonize(const char *pid_file);

/**
 * os_daemonize_terminate-停止在后台运行（删除pid文件）
 * @pid_file: 要将进程ID写入的文件名，或使用%NULL跳过此操作
 */
void os_daemonize_terminate(const char *pid_file);

/**
 * os_get_random-获取加密强伪随机数据
 * @buf: 伪随机数据缓冲区
 * @len: 缓冲区长度：成功时返回0，失败时返回-1
 */
int os_get_random(unsigned char *buf, size_t len);

/**
 * os_random-获取伪随机值（不一定很强）返回：伪随机值
 */
unsigned long os_random(void);

/**
 * os_rel2abs_path-获取文件的绝对路径
 * @rel_path: 文件的相对路径返回：文件的绝对路径或失败时的%NULL
 *
 * 此函数尝试将文件的相对路径转换为绝对路径，以便即使当前工作目录已更改，也能找到文件。返回的值被分配，调用者负责释放它。可以只在分配的缓冲区中返回相同的路径，例如，返回strdup（rel_path）。此函数仅用于在os_daemonize（）可能已更改当前工作目录且相对路径指向不同位置时查找配置文件。
 */
char * os_rel2abs_path(const char *rel_path);

/**
 * os_program_init-程序初始化（在开始时调用）返回：成功时返回0，失败时返回-1
 *
 * 程序启动时调用此函数。如果需要任何特定于操作系统的处理，可以将其放置在此处。如果不需要特殊处理，也可以只返回0。
 */
int os_program_init(void);

/**
 * os_program_deinit-程序去初始化（在退出前调用）
 *
 * 在程序存在之前调用此函数。如果有任何特定于操作系统的处理，例如释放在OS_program_init（）中分配的资源，应该在这里完成。此函数不执行任何操作也是可以接受的。
 */
void os_program_deinit(void);

/**
 * os_setenv-设置环境变量
 * @name: 变量的名称
 * @value: 要设置到变量的值
 * @overwrite: 是否应覆盖现有变量返回：成功时返回0，错误时返回-1
 *
 * 此函数仅用于wpa_cli操作脚本。如果不需要这样的功能，OS包装器不需要实现这一点。
 */
int os_setenv(const char *name, const char *value, int overwrite);

/**
 * os_unsetenv-删除环境变量
 * @name: 变量名称：成功时返回0，错误时返回-1
 *
 * 此函数仅用于wpa_cli操作脚本。如果不需要这样的功能，OS包装器不需要实现这一点。
 */
int os_unsetenv(const char *name);

/**
 * os_readfile-将文件读取到分配的内存缓冲区
 * @name: 要读取的文件的名称
 * @len: 用于返回已分配缓冲区的长度返回：指向已分配缓冲的指针或失败时的%NULL
 *
 * 此函数分配内存并将给定文件读取到此缓冲区。使用此函数可以读取二进制文件和文本文件。调用者负责使用os_free（）释放返回的缓冲区。
 */
char * os_readfile(const char *name, size_t *len);

/*
 * 以下函数是标准ANSI C或POSIX函数的包装器。默认情况下，它们只定义为使用标准函数名，而不使用os_。c需要对它们进行实施。这通过允许C预处理器处理函数名映射来避免额外的函数调用。
 *
 * 如果目标系统使用不提供这些函数的C库，请build_config。h可以用于定义包装器以使用不同的函数名。这可以在逐个函数的基础上完成，因为这里的定义仅在build_config时使用。h没有定义os名称。如果需要，os_。c文件可用于实现目标系统上c库中未包含的函数。或者，可以将OS_NO_C_LIB_DEFINES定义为跳过此处的所有定义，在这种情况下，这些函数需要在OS_中实现。目标系统的c文件。
 */

#ifndef os_malloc
#define os_malloc(s) malloc((s))
#endif
#ifndef os_realloc
#define os_realloc(p, s) realloc((p), (s))
#endif
#ifndef os_zalloc
#define os_zalloc(s) calloc(1, (s))
#endif
#ifndef os_calloc
#define os_calloc(p, s) calloc((p), (s))
#endif

#ifndef os_free
#define os_free(p) free((p))
#endif

#ifndef os_bzero
#define os_bzero(s, n) bzero(s, n)
#endif


#ifndef os_strdup
#ifdef _MSC_VER
#define os_strdup(s) _strdup(s)
#else
#define os_strdup(s) strdup(s)
#endif
#endif
char * ets_strdup(const char *s);

#ifndef os_memcpy
#define os_memcpy(d, s, n) memcpy((d), (s), (n))
#endif
#ifndef os_memmove
#define os_memmove(d, s, n) memmove((d), (s), (n))
#endif
#ifndef os_memset
#define os_memset(s, c, n) memset(s, c, n)
#endif
#ifndef os_memcmp
#define os_memcmp(s1, s2, n) memcmp((s1), (s2), (n))
#endif
#ifndef os_memcmp_const
#define os_memcmp_const(s1, s2, n) memcmp((s1), (s2), (n))
#endif


#ifndef os_strlen
#define os_strlen(s) strlen(s)
#endif
#ifndef os_strcasecmp
#ifdef _MSC_VER
#define os_strcasecmp(s1, s2) _stricmp((s1), (s2))
#else
#define os_strcasecmp(s1, s2) strcasecmp((s1), (s2))
#endif
#endif
#ifndef os_strncasecmp
#ifdef _MSC_VER
#define os_strncasecmp(s1, s2, n) _strnicmp((s1), (s2), (n))
#else
#define os_strncasecmp(s1, s2, n) strncasecmp((s1), (s2), (n))
#endif
#endif
#ifndef os_strchr
#define os_strchr(s, c) strchr((s), (c))
#endif
#ifndef os_strcmp
#define os_strcmp(s1, s2) strcmp((s1), (s2))
#endif
#ifndef os_strncmp
#define os_strncmp(s1, s2, n) strncmp((s1), (s2), (n))
#endif
#ifndef os_strncpy
#define os_strncpy(d, s, n) strncpy((d), (s), (n))
#endif
#ifndef os_strrchr
#define os_strrchr(s, c)  strrchr((s), (c))
#endif
#ifndef os_strstr
#define os_strstr(h, n) strstr((h), (n))
#endif
#ifndef os_strlcpy
#define os_strlcpy(d, s, n) strlcpy((d), (s), (n))
#endif
#ifndef os_strcat
#define os_strcat(d, s) strcat((d), (s))
#endif

#ifndef os_snprintf
#ifdef _MSC_VER
#define os_snprintf _snprintf
#else
#define os_snprintf snprintf
#endif
#endif
#ifndef os_sprintf
#define os_sprintf sprintf
#endif

static inline int os_snprintf_error(size_t size, int res)
{
        return res < 0 || (unsigned int) res >= size;
}

static inline void * os_realloc_array(void *ptr, size_t nmemb, size_t size)
{
	if (size && nmemb > (~(size_t) 0) / size)
		return NULL;
	return os_realloc(ptr, nmemb * size);
}

#ifdef USE_MBEDTLS_CRYPTO
void forced_memzero(void *ptr, size_t len);
#else
/* 尽量避免大多数编译器优化清除在调用此函数后变得不可访问的内存。这主要是在函数末尾清除局部堆栈变量的情况。这并不完全完美，也就是说，有人可能会想出一个编译器，找出指针指向内存集，然后最终优化调用，所以尝试进一步存储第一个八位字节（现在为零），使其更难优化。一旦memset_s（）可用，就可以在这里使用它。*/
static void * (* const volatile memset_func)(void *, int, size_t) = memset;
static uint8_t forced_memzero_val;

static inline void forced_memzero(void *ptr, size_t len)
{
	memset_func(ptr, 0, len);
	if (len) {
		forced_memzero_val = ((uint8_t *) ptr)[0];
	}
}
#endif
#endif /* OS_H */

