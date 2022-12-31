/*
 * wpa_suppliant/hostapd-默认包含文件版权所有（c）2005-2006，Jouni Malinen<j@w1.fi>
 *
 * 该程序是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证第2版的条款重新分发和/或修改它。
 *
 * 或者，此软件可以根据BSD许可证条款进行分发。
 *
 * 有关详细信息，请参阅自述和复制。
 *
 * 此头文件包含在所有C文件中，因此可以在一个位置使用特定于OS的ifdef块来选择常用的头文件，而不必在许多文件中使用特定于OS/C库的选择。
 */

#ifndef INCLUDES_H
#define INCLUDES_H

#include "supplicant_opt.h"

#define AES_SMALL_TABLES
#define CONFIG_NO_RANDOM_POOL
#define CONFIG_INTERNAL_LIBTOMMATH

/* 在包含其他内容之前包含可能的构建时配置*/
#ifndef __ets__
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#ifndef _WIN32_WCE
#ifndef CONFIG_TI_COMPILER
#include <signal.h>
#include <sys/types.h>
#endif /* CONFIG_TI_COMPILER */
#include <errno.h>
#endif /* _WIN32_WCE */
#include <ctype.h>
#include <time.h>

#ifndef CONFIG_TI_COMPILER
#ifndef _MSC_VER
#include <unistd.h>
#endif /* _MSC_VER */
#endif /* CONFIG_TI_COMPILER */

#ifndef CONFIG_NATIVE_WINDOWS
#ifndef CONFIG_TI_COMPILER
#ifndef __vxworks
#ifndef __SYMBIAN32__
#endif /* __SYMBIAN32__ */
#include <sys/time.h>
#endif /* __vxworks公司*/
#endif /* CONFIG_TI_COMPILER */
#endif /* CONFIG_NATIVE_WINDOWS */

#else
#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/ets_sys.h" // 将在idf v5.0中删除
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/ets_sys.h"
#endif

#endif /* !__电子交易系统__*/

#endif /* INCLUDES_H */

