// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef __ESP_NEWLIB_H__
#define __ESP_NEWLIB_H__

#include <sys/reent.h>

/*
 * 初始化newlib时间函数
 */
void esp_newlib_time_init(void);

/**
 * 替换newlib的_REENT_INIT_PTR和__sinit。
 *
 * 从启动代码和FreeRTOS调用，而不是从应用程序代码调用。
 */
void esp_reent_init(struct _reent* r);

/**
 * 清理REENT结构中一些延迟分配的缓冲区。
 */
void esp_reent_cleanup(void);

/**
 * 在ROM中设置用于ESP-IDF的newlib的函数
 *
 * 包括定义系统调用表、设置任何公共锁等。
 *
 * 从启动代码调用，而不是从应用程序代码调用。
 */
void esp_newlib_init(void);

void esp_setup_syscall_table(void) __attribute__((deprecated("Please call esp_newlib_init() in newer code")));

/**
 * 从RTC更新当前微秒时间
 */
void esp_set_time_from_rtc(void);

/*
 * 同步计数器RTC和FRC。更新boot_time。
 */
void esp_sync_counters_rtc_and_frc(void);

/**
 * 初始化newlib静态锁
 */
void esp_newlib_locks_init(void);

#endif //__ESP_NEWLIB_H__

