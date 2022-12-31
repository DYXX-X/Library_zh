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

#pragma once

#include <stdbool.h>

#include "eri.h"
#include "xtensa-debug-module.h"

// 低水平Xtensa TRAX实用程序

/**
 * @brief  以指令为延迟单位在当前CPU上启动Trax跟踪。如果需要，必须在调用此函数之前启用要用作Trax内存的内存块。
 */
void xt_trax_start_trace_instructions(void);

/**
 * @brief  在当前CPU上以单词为延迟单位启动Trax跟踪。如果需要，必须在调用此函数之前启用要用作Trax内存的内存块。
 */
void xt_trax_start_trace_words(void);

/**
 * @brief 检查当前CPU上的Trax跟踪是否处于活动状态。
 *
 * @return 嘘声。如果跟踪处于活动状态，则返回true。
 */
bool xt_trax_trace_is_active(void);

/**
 * @brief  在指定的延迟后触发Trax跟踪停止。如果之前调用了此函数，而上一个延迟尚未结束，则将使用新值覆盖该延迟。延迟将始终在调用函数时开始。
 *
 * @param  delay ：停止跟踪的延迟，单位为trax_start_trace。注意：跟踪内存有4K字可用。
 */
void xt_trax_trigger_traceend_after_delay(int delay);

