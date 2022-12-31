/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include <stdint.h>
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file sleep_mac_bb.h睡眠时间
 *
 * 此文件包含轻睡眠模式下MAC和基带功耗相关功能的声明。
 */

#if CONFIG_MAC_BB_PD

/**
 * @brief 回调函数完成MAC和基带断电操作
 *
 * 在轻睡眠模式下，执行Wi-Fi和蓝牙模块MAC和基带断电以及备份寄存器配置信息操作。
 */
void mac_bb_power_down_cb_execute(void);

/**
 * @brief 回调函数完成MAC和基带加电操作
 *
 * 在轻睡眠模式下，执行Wi-Fi和蓝牙模块MAC和基带通电并恢复寄存器配置信息操作。
 */
void mac_bb_power_up_cb_execute(void);

#endif // CONFIG_MAC_BB_PD

#ifdef __cplusplus
}
#endif

