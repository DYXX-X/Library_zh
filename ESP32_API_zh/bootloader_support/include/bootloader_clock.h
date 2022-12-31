/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 为早期启动配置时钟
 *
 * 由引导加载程序调用，如果引导加载程序版本较旧（v2.1之前），则由应用程序调用。
 */
void bootloader_clock_configure(void);

/** @brief 返回此芯片的额定最大频率
 */
int bootloader_clock_get_rated_freq_mhz(void);

#ifdef __cplusplus
}
#endif

