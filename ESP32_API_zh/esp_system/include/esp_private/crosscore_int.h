// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#ifndef __ESP_CROSSCORE_INT_H
#define __ESP_CROSSCORE_INT_H

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 初始化此CPU的交叉核心中断系统。这需要在FreeRTOS使用的每个CPU上调用一次。
 *
 * 如果启用了多核FreeRTOS支持，则启动代码将自动调用该支持，不应手动调用。
 */
void esp_crosscore_int_init(void);


/**
 * 向CPU发送一个中断，指示它应该放弃当前正在运行的任务，而选择一个可能刚刚唤醒的更高优先级的任务。
 *
 * 这是FreeRTOS在多核模式下内部使用的，用户不应调用。
 *
 * @param core_id 应该进行屈服的核心
 */
void esp_crosscore_int_send_yield(int core_id);


/**
 * 向CPU发送一个中断，指示其应因频率切换而更新其CCOMPARE1值。
 *
 * 当启用动态频率切换时，这在内部使用，不应从应用程序代码调用。
 *
 * @param core_id 应更新其CCOMPARE1值的核心
 */
void esp_crosscore_int_send_freq_switch(int core_id);


#if !CONFIG_IDF_TARGET_ESP32C3 && !CONFIG_IDF_TARGET_ESP32H2
/**
 * 向CPU发送中断，指示其应打印当前回溯
 *
 * 这是任务监视程序在内部使用的，用于转储相反内核的回溯，不应从应用程序代码中调用。
 *
 * @param core_id 应打印其回溯轨迹的核心
 */
void esp_crosscore_int_send_print_backtrace(int core_id);
#endif

#ifdef __cplusplus
}
#endif

#endif

