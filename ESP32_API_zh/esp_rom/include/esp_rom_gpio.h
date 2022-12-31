// 版权所有2010-2020 Espressif Systems（上海）私人有限公司
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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "soc/gpio_pins.h"  //对于GPIO_MATRIX_CONST_ONE_INPUT，GPIO_MATRIX_CONST_ZERO_INPUT

/**
 * @brief 将IO Pad配置为通用IO，以便它可以连接到内部矩阵，然后与一个或多个外围信号组合。
 *
 * @param iopad_num IO极板编号
 */
void esp_rom_gpio_pad_select_gpio(uint32_t iopad_num);

/**
 * @brief 启用内部上拉，禁用内部下拉。
 *
 * @param iopad_num IO极板编号
 */
void esp_rom_gpio_pad_pullup_only(uint32_t iopad_num);

/**
 * @brief 松开IO板。
 * @note 当Pad设置为保持时，该状态在该时刻被锁定，不会被更改。
 *
 * @param iopad_num IP极板编号
 */
void esp_rom_gpio_pad_unhold(uint32_t gpio_num);

/**
 * @brief 设置IO板电流驱动能力。
 *
 * @param iopad_num IO极板编号
 * @param drv 数字表示当前驱动器的能力
 *      -0:5毫安
 *      -1:10mA
 *      -2：20mA
 *      -3:40毫安
 */
void esp_rom_gpio_pad_set_drv(uint32_t iopad_num, uint32_t drv);

/**
 * @brief 将GPIO输入与标记为输入属性的外围信号组合。
 *
 * @note GPIO可以结合的信号数量没有限制。
 *
 * @param gpio_num GPIO编号，特别是“GPIO_MATRIX_CONST_ZERO_INPUT”表示将逻辑0连接到信号“GPIO_MATRIX_CONSTR_ONE_INPUT”意味着将逻辑1连接到信号
 * @param signal_idx 外围信号索引（标记为输入属性）
 * @param inv  GPIO输入是否反相
 */
void esp_rom_gpio_connect_in_signal(uint32_t gpio_num, uint32_t signal_idx, bool inv);

/**
 * @brief 将标记为输出属性的外围信号与GPIO组合。
 *
 * @note GPIO可以结合的信号数量没有限制。
 *
 * @param gpio_num GPIO编号
 * @param signal_idx 外围信号索引（标记为输出属性）
 * @param out_inv 是否发出反转信号
 * @param oen_inv 输出使能控制是否反转
 */
void esp_rom_gpio_connect_out_signal(uint32_t gpio_num, uint32_t signal_idx, bool out_inv, bool oen_inv);

#ifdef __cplusplus
}
#endif

