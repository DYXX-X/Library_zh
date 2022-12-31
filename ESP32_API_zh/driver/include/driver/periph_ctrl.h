/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _DRIVER_PERIPH_CTRL_H_
#define _DRIVER_PERIPH_CTRL_H_

#include "soc/periph_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      启用外围模块
 *
 * @param[in]  periph    ：外围模块名称
 *
 * 模块的时钟将被取消锁定，重置将被取消断言。
 *
 * @note 如果多次调用periph_module_enable，则必须调用相同次数的periph_mdule_disable才能将外围设备置于禁用状态。
 *
 * @return     NULL
 *
 */
void periph_module_enable(periph_module_t periph);

/**
 * @brief      禁用外围模块
 *
 * @param[in]  periph    ：外围模块名称
 *
 * 模块的时钟将被选通，复位生效。
 *
 * @note 如果多次调用periph_module_enable，则必须调用相同次数的periph_mdule_disable才能将外围设备置于禁用状态。
 *
 * @return     NULL
 *
 */
void periph_module_disable(periph_module_t periph);

/**
 * @brief      重置外围模块
 *
 * @param[in]  periph    ：外围模块名称
 *
 * 重置将被断言，然后对外围设备进行重置。
 *
 * 调用此函数不会启用或禁用模块的时钟。
 *
 * @return     NULL
 *
 */
void periph_module_reset(periph_module_t periph);

/**
 * @brief      启用wifi bt公共模块
 *
 * @note 如果多次调用wifi_bt_common_module_enable，则必须多次调用wiwi_bt_common_module_disable，才能将外围设备置于禁用状态。
 *
 * @return     NULL
 *
 */
void wifi_bt_common_module_enable(void);

/**
 * @brief      禁用wifi bt公共模块
 *
 * @note 如果多次调用wifi_bt_common_module_enable，则必须多次调用wiwi_bt_common_module_disable，才能将外围设备置于禁用状态。
 *
 * @return     NULL
 *
 */
void wifi_bt_common_module_disable(void);

/**
 * @brief      启用wifi模块
 *
 * @note 仅启用wifi模块。
 *
 * @return     NULL
 *
 */
void wifi_module_enable(void);

/**
 * @brief      禁用wifi模块
 *
 * @note 仅禁用wifi模块。
 *
 * @return     NULL
 *
 */
void wifi_module_disable(void);
#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_PERIPH_CTRL_H_ */

