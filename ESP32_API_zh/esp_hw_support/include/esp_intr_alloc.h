/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup Intr_Alloc公司@{
  */


/** @brief 中断分配标志
 *
 * 这些标志可用于指定调用esp_intr_alloc的代码需要哪些中断质量。
 *
 */

//保持LEVELx值不变；它们符合（1<<级别）
#define ESP_INTR_FLAG_LEVEL1        (1<<1)  ///<接受1级中断向量（最低优先级）
#define ESP_INTR_FLAG_LEVEL2        (1<<2)  ///<接受2级中断向量
#define ESP_INTR_FLAG_LEVEL3        (1<<3)  ///<接受3级中断向量
#define ESP_INTR_FLAG_LEVEL4        (1<<4)  ///<接受4级中断向量
#define ESP_INTR_FLAG_LEVEL5        (1<<5)  ///<接受5级中断向量
#define ESP_INTR_FLAG_LEVEL6        (1<<6)  ///<接受6级中断向量
#define ESP_INTR_FLAG_NMI           (1<<7)  ///<接受7级中断向量（最高优先级）
#define ESP_INTR_FLAG_SHARED        (1<<8)  ///<中断可以在ISR之间共享
#define ESP_INTR_FLAG_EDGE          (1<<9)  ///<边缘触发中断
#define ESP_INTR_FLAG_IRAM          (1<<10) ///<如果禁用缓存，则可以调用ISR
#define ESP_INTR_FLAG_INTRDISABLED  (1<<11) ///<禁用此中断时返回

#define ESP_INTR_FLAG_LOWMED    (ESP_INTR_FLAG_LEVEL1|ESP_INTR_FLAG_LEVEL2|ESP_INTR_FLAG_LEVEL3) ///<中低优先级中断。这些可以在C中处理。
#define ESP_INTR_FLAG_HIGH      (ESP_INTR_FLAG_LEVEL4|ESP_INTR_FLAG_LEVEL5|ESP_INTR_FLAG_LEVEL6|ESP_INTR_FLAG_NMI) ///<高级中断。需要在组装时处理。

#define ESP_INTR_FLAG_LEVELMASK (ESP_INTR_FLAG_LEVEL1|ESP_INTR_FLAG_LEVEL2|ESP_INTR_FLAG_LEVEL3| \
                                 ESP_INTR_FLAG_LEVEL4|ESP_INTR_FLAG_LEVEL5|ESP_INTR_FLAG_LEVEL6| \
                                 ESP_INTR_FLAG_NMI) ///<所有级别标志的掩码


/** @addtogroup Intr_Alloc_Pseudo_Src@{
  */

/**
 * esp_intr_alloc*函数可以为通过中断多路复用器路由的所有ETS_*_intr_SOURCE中断源分配一个int。除了这些源之外，每个内核还有一些不通过中断多路复用器的内部源。要为这些源分配中断，请将这些伪源传递给函数。
 */
#define ETS_INTERNAL_TIMER0_INTR_SOURCE     -1 ///<平台计时器0中断源
#define ETS_INTERNAL_TIMER1_INTR_SOURCE     -2 ///<平台计时器1中断源
#define ETS_INTERNAL_TIMER2_INTR_SOURCE     -3 ///<平台计时器2中断源
#define ETS_INTERNAL_SW0_INTR_SOURCE        -4 ///<软件int源1
#define ETS_INTERNAL_SW1_INTR_SOURCE        -5 ///<软件int源2
#define ETS_INTERNAL_PROFILING_INTR_SOURCE  -6 ///＜用于分析的Int源

/**@}*/

/** 为SystemView提供正IRQ ID，否则无法正确显示调度程序事件
 */
#define ETS_INTERNAL_INTR_SOURCE_OFF        (-ETS_INTERNAL_PROFILING_INTR_SOURCE)

/**按中断号启用中断*/
#define ESP_INTR_ENABLE(inum)  esp_intr_enable_source(inum)

/**按中断号禁用中断*/
#define ESP_INTR_DISABLE(inum) esp_intr_disable_source(inum)

/**中断处理程序函数的函数原型*/
typedef void (*intr_handler_t)(void *arg);

/**中断处理程序关联的数据结构*/
typedef struct intr_handle_data_t intr_handle_data_t;

/**中断处理程序的句柄*/
typedef intr_handle_data_t *intr_handle_t ;

/**
 * @brief 将中断标记为共享中断
 *
 * 这会将指定CPU上的某个中断标记为可用于挂接共享中断处理程序的中断。
 *
 * @param intno 中断编号（0-31）
 * @param cpu 中断应标记为共享的CPU（0或1）
 * @param is_in_iram 共享中断用于驻留在IRAM中的处理程序，当禁用闪存缓存时，int可以保持启用状态。
 *
 * @return 如果cpu或intno无效，则为ESP_ERR_INVALID_ARG，否则为ESP_OK
 */
esp_err_t esp_intr_mark_shared(int intno, int cpu, bool is_in_iram);

/**
 * @brief 保留要在此框架之外使用的中断
 *
 * 这会将指定CPU上的某个中断标记为保留，不会因任何原因分配。
 *
 * @param intno 中断编号（0-31）
 * @param cpu 中断应标记为共享的CPU（0或1）
 *
 * @return 如果cpu或intno无效，则为ESP_ERR_INVALID_ARG，否则为ESP_OK
 */
esp_err_t esp_intr_reserve(int intno, int cpu);

/**
 * @brief 使用给定参数分配中断。
 *
 * 这会找到一个与flags参数中给定的限制相匹配的中断，将给定的中断源映射到它，并连接到给定的中断处理程序（带有可选参数）。如果需要，它还可以返回中断的句柄。
 *
 * 中断将始终分配给运行此功能的内核。
 *
 * 如果使用了ESP_INTR_FLAG_RAM标志，并且处理程序地址不在IRAM或RTC_FAST_MEM中，则返回ESP_ERR_INVALID_ARG。
 *
 * @param source 中断源。ETS_*_INTR_SOURCE中断多路复用器源之一，如soc/soc中所定义。h、 或此标头中定义的内部ETS_internal_INTR_SOURCE源之一。
 * @param flags ESP_INTR_FLAG_*定义的“或”掩码。这些限制了该例程可以选择的中断的选择。如果此值为0，则默认为分配1、2或3级的非共享中断。如果这是ESP_INTR_FLAG_shared，则将分配1级的共享中断。设置ESP_INTR-FLAG_INTRDISABLED将从该函数返回，中断被禁用。
 * @param handler 中断处理程序。当请求级别>3的中断时，必须为NULL，因为这些类型的中断不可C调用。
 * @param arg    传递给中断处理程序的可选参数
 * @param ret_handle 指向intr_handle_t的指针，用于存储稍后可用于请求详细信息或释放中断的句柄。如果不需要句柄，则可以为NULL。
 *
 * @return 如果参数组合无效，则返回ESP_ERR_INVALID_ARG。ESP_ERR_NOT_FOUND未找到具有指定标志ESP_OK的空闲中断，否则
 */
esp_err_t esp_intr_alloc(int source, int flags, intr_handler_t handler, void *arg, intr_handle_t *ret_handle);


/**
 * @brief 使用给定参数分配中断。
 *
 * 这基本上与esp_intr_alloc相同，但允许指定寄存器和掩码组合。对于共享中断，只有当从指定寄存器读取的值（与掩码进行AND运算）返回非零时，才会调用处理程序。通过传递中断状态寄存器地址和匹配掩码，这可以用于在触发共享中断的情况下加速中断处理；通过首先检查中断状态，代码可以决定哪些ISR可以跳过
 *
 * @param source 中断源。ETS_*_INTR_SOURCE中断多路复用器源之一，如soc/soc中所定义。h、 或此标头中定义的内部ETS_internal_INTR_SOURCE源之一。
 * @param flags ESP_INTR_FLAG_*定义的“或”掩码。这些限制了该例程可以选择的中断的选择。如果此值为0，则默认为分配1、2或3级的非共享中断。如果这是ESP_INTR_FLAG_shared，则将分配1级的共享中断。设置ESP_INTR-FLAG_INTRDISABLED将从该函数返回，中断被禁用。
 * @param intrstatusreg 中断状态寄存器的地址
 * @param intrstatusmask 一个面具。如果地址intrstatusrg的读取具有掩码集合中的任何1位，则将调用ISR。如果没有，它将被跳过。
 * @param handler 中断处理程序。当请求级别>3的中断时，必须为NULL，因为这些类型的中断不可C调用。
 * @param arg    传递给中断处理程序的可选参数
 * @param ret_handle 指向intr_handle_t的指针，用于存储稍后可用于请求详细信息或释放中断的句柄。如果不需要句柄，则可以为NULL。
 *
 * @return 如果参数组合无效，则返回ESP_ERR_INVALID_ARG。ESP_ERR_NOT_FOUND未找到具有指定标志ESP_OK的空闲中断，否则
 */
esp_err_t esp_intr_alloc_intrstatus(int source, int flags, uint32_t intrstatusreg, uint32_t intrstatusmask, intr_handler_t handler, void *arg, intr_handle_t *ret_handle);


/**
 * @brief 禁用并释放中断。
 *
 * 使用中断句柄禁用中断并释放与其相关的资源。如果当前内核不是注册此中断的内核，则此例程将分配给分配此中断的核心，阻塞并等待资源成功释放。
 *
 * @note 当处理程序与其他处理程序共享其源时，应在释放它之前正确管理它所负责的中断状态位。有关详细信息，请参见“esp_intr_disable”。请不要在“esp_ipc_call_blocking”中调用此函数。
 *
 * @param handle 由esp_intr_alloc或esp_intr_alloc_intrstatus获得的句柄
 *
 * @return ESP_ERR_INVALID_ARG句柄为空ESP_FAIL未能释放此句柄ESP_OK，否则
 */
esp_err_t esp_intr_free(intr_handle_t handle);


/**
 * @brief 获取中断绑定到的CPU号
 *
 * @param handle 由esp_intr_alloc或esp_intr_alloc_intrstatus获得的句柄
 *
 * @return 分配中断的核心号
 */
int esp_intr_get_cpu(intr_handle_t handle);

/**
 * @brief 获取特定句柄的分配中断
 *
 * @param handle 由esp_intr_alloc或esp_intr_alloc_intrstatus获得的句柄
 *
 * @return 中断编号
 */
int esp_intr_get_intno(intr_handle_t handle);

/**
 * @brief 禁用与句柄相关的中断
 *
 * @note 1.对于本地中断（ESP_INTERNAL_sources），必须在分配中断的CPU上调用此函数。其他中断没有此限制。2.当多个处理程序共享同一中断源时，应在禁用前屏蔽在处理程序中处理的中断状态位，或在其他已启用中断中正确处理。中断状态处理失败将导致无限中断调用，最终导致系统崩溃。
 *
 * @param handle 由esp_intr_alloc或esp_intr_alloc_intrstatus获得的句柄
 *
 * @return 如果参数组合无效，则返回ESP_ERR_INVALID_ARG。否则ESP_OK
 */
esp_err_t esp_intr_disable(intr_handle_t handle);

/**
 * @brief 启用与句柄相关的中断
 *
 * @note 对于本地中断（ESP_INTERNAL_*源），必须在分配中断的CPU上调用此函数。其他中断没有此限制。
 *
 * @param handle 由esp_intr_alloc或esp_intr_alloc_intrstatus获得的句柄
 *
 * @return 如果参数组合无效，则返回ESP_ERR_INVALID_ARG。否则ESP_OK
 */
esp_err_t esp_intr_enable(intr_handle_t handle);

/**
 * @brief 设置处理程序的“在IRAM”状态。
 *
 * @note 不适用于共享中断。
 *
 * @param handle 由esp_intr_alloc或esp_intr_alloc_intrstatus获得的句柄
 * @param is_in_iram 与此句柄关联的处理程序是否驻留在IRAM中。当缓存被禁用时，可以调用驻留在IRAM中的处理程序。
 *
 * @return 如果参数组合无效，则返回ESP_ERR_INVALID_ARG。否则ESP_OK
 */
esp_err_t esp_intr_set_in_iram(intr_handle_t handle, bool is_in_iram);

/**
 * @brief 禁用未明确标记为从IRAM运行的中断
 */
void esp_intr_noniram_disable(void);

/**
 * @brief 重新启用esp_intr_noniram_disable禁用的中断
 */
void esp_intr_noniram_enable(void);

/**
 * @brief 根据中断源的编号启用中断源
 * @param inum 从0到31的中断号
 */
void esp_intr_enable_source(int inum);

/**
 * @brief 根据中断源的编号禁用中断源
 * @param inum 从0到31的中断号
 */
void esp_intr_disable_source(int inum);

/**
 * @brief 从标志中获取最低中断级别
 * @param flags 传递给`esp_intr_alloc_intrstatus`API的标志相同
 */
static inline int esp_intr_flags_to_level(int flags)
{
    return __builtin_ffs((flags & ESP_INTR_FLAG_LEVELMASK) >> 1) + 1;
}

/**@}*/


#ifdef __cplusplus
}
#endif

