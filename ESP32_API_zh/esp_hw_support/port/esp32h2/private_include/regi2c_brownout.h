/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @file 区域2c_brownout.h
 * @brief 褐化检测器的寄存器定义
 *
 * 该文件列出了位于内部配置总线上的断电检测器的寄存器字段。这些定义通过regi2c_ctrl.h中定义的宏使用。
 */

#define I2C_BOD            0x61
#define I2C_BOD_HOSTID     0

#define I2C_BOD_THRESHOLD           0x5
#define I2C_BOD_THRESHOLD_MSB       2
#define I2C_BOD_THRESHOLD_LSB       0

