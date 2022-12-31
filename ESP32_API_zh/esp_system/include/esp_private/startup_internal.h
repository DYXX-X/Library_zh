// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
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

#pragma once

#include "esp_attr.h"

#include "soc/soc_caps.h"
#include "hal/cpu_hal.h"

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

extern bool g_spiram_ok; // [重构todo]从端口层到通用启动代码的更好沟通方式

// 端口层定义入口点。然后，它将控制权转移到“sys_startup_fn_t”，存储在
// 阵列，每个核心一个。
typedef void (*sys_startup_fn_t)(void);

/* 此每CPU系统层启动函数数组在esp_system的非端口部分初始化*/
#if !CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
extern sys_startup_fn_t const g_startup_fn[SOC_CPU_CORES_NUM];
#else
extern sys_startup_fn_t const g_startup_fn[1];
#endif

// 用于为当前内核执行“sys_startup_fn_t”的实用程序。
#define SYS_STARTUP_FN()  ((*g_startup_fn[(cpu_hal_get_core_id())])())

#if !CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE
void startup_resume_other_cores(void);
#endif

typedef struct {
  void (*fn)(void);
  uint32_t cores;
} esp_system_init_fn_t;

/*
 * 声明将在指定内核上执行的组件初始化函数（例如，如果BIT0==1，将在CORE0上执行，如果BIT1，则在CORE1上执行等等）。
 *
 * @note 初始化函数应放置在编译单元中，其中至少一个其他符号在另一个编译单元中被“有意义地”引用，否则在链接过程中会被丢弃。（“有意义”是指引用本身不应该被编译器优化/被链接器丢弃）。
 */
#define ESP_SYSTEM_INIT_FN(f, c, ...) \
static void  __attribute__((used)) __VA_ARGS__ __esp_system_init_fn_##f(void); \
static __attribute__((used)) esp_system_init_fn_t _SECTION_ATTR_IMPL(".esp_system_init_fn", f) \
                    esp_system_init_fn_##f = { .fn = ( __esp_system_init_fn_##f), .cores = (c) }; \
static __attribute__((used)) __VA_ARGS__ void __esp_system_init_fn_##f(void) // [重构todo]如果我们允许组件声明init函数，
                                                                             // 而不是显式调用它们

extern uint64_t g_startup_time;   // 作为系统时间起点的启动时间。应由条目设置
                                  // 功能。如果没有持久计数器支持，也可以为0，在这种情况下
                                  // 在入口函数设置此变量时，启动时间=系统时间=0。

#ifdef __cplusplus
}
#endif

