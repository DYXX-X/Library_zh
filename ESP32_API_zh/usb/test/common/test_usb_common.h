/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#include <stdbool.h>
#include "freertos/FreeRTOS.h"

/**
 * @brief 初始化内部USB PHY和USB控制器以进行USB主机测试
 */
void test_usb_init_phy(void);

/**
 * @brief 在USB主机测试后取消内部USB PHY和USB控制器的卫生
 */
void test_usb_deinit_phy(void);

/**
 * @brief USB PHY处于连接或断开状态
 *
 * @param connected 如果为true，则进入连接状态，如果为false，则断开连接
 * @param delay_ticks 强制状态前的计时延迟
 */
void test_usb_set_phy_state(bool connected, TickType_t delay_ticks);

