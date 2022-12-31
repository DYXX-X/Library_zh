/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "regi2c_apll.h"
#include "regi2c_bbpll.h"
#include "regi2c_ulp.h"
#include "regi2c_saradc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 模拟功能控制寄存器*/
#define ANA_CONFIG_REG  0x6000E044
#define ANA_CONFIG_S    (8)
#define ANA_CONFIG_M    (0x3FF)
/* 清除以启用APLL*/
#define I2C_APLL_M      (BIT(14))
/* 清除以启用BBPLL*/
#define I2C_BBPLL_M     (BIT(17))
/* 清除以启用SAR*/
#define I2C_SAR_M       (BIT(18))

#define ANA_CONFIG2_REG 0x6000E048
#define ANA_SAR_CFG2_M  (BIT(16))

/* 读/写内部控制总线*/
uint8_t i2c_rtc_read_reg(uint8_t block, uint8_t host_id, uint8_t reg_add);
uint8_t i2c_rtc_read_reg_mask(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t msb, uint8_t lsb);
void i2c_rtc_write_reg(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t data);
void i2c_rtc_write_reg_mask(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t msb, uint8_t lsb, uint8_t data);
void i2c_rtc_init(void);

#ifdef BOOTLOADER_BUILD

/**
 * 如果为引导加载程序编译，则可以直接调用内部函数，而不需要锁。
 */
#define regi2c_ctrl_read_reg         i2c_rtc_read_reg
#define regi2c_ctrl_read_reg_mask    i2c_rtc_read_reg_mask
#define regi2c_ctrl_write_reg        i2c_rtc_write_reg
#define regi2c_ctrl_write_reg_mask   i2c_rtc_write_reg_mask

#else

#define i2c_read_reg_raw        i2c_rtc_read_reg
#define i2c_read_reg_mask_raw   i2c_rtc_read_reg_mask
#define i2c_write_reg_raw       i2c_rtc_write_reg
#define i2c_write_reg_mask_raw  i2c_rtc_write_reg_mask

uint8_t regi2c_ctrl_read_reg(uint8_t block, uint8_t host_id, uint8_t reg_add);
uint8_t regi2c_ctrl_read_reg_mask(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t msb, uint8_t lsb);
void regi2c_ctrl_write_reg(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t data);
void regi2c_ctrl_write_reg_mask(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t msb, uint8_t lsb, uint8_t data);

/* 输入保护内部寄存器的关键部分。不要在SDK中使用它。使用上述功能。*/
void regi2c_enter_critical(void);
void regi2c_exit_critical(void);

#endif // BOOTLOADER_BUILD

/* 上述函数的方便宏使用regi2c_apll.h/regi2c_bbpll中的寄存器定义。h头文件。
 */
#define REGI2C_WRITE_MASK(block, reg_add, indata) \
      regi2c_ctrl_write_reg_mask(block, block##_HOSTID,  reg_add,  reg_add##_MSB,  reg_add##_LSB,  indata)

#define REGI2C_READ_MASK(block, reg_add) \
      regi2c_ctrl_read_reg_mask(block, block##_HOSTID,  reg_add,  reg_add##_MSB,  reg_add##_LSB)

#define REGI2C_WRITE(block, reg_add, indata) \
      regi2c_ctrl_write_reg(block, block##_HOSTID,  reg_add, indata)

#define REGI2C_READ(block, reg_add) \
      regi2c_ctrl_read_reg(block, block##_HOSTID,  reg_add)


/**
 * 恢复regi2c模拟校准相关配置寄存器。这是一种变通方法，并在以后的芯片上修复
 */
#if REGI2C_ANA_CALI_PD_WORKAROUND
void regi2c_analog_cali_reg_read(void);
void regi2c_analog_cali_reg_write(void);
#endif   //#如果ADC_CALI_PD_WORKAROUND

#ifdef __cplusplus
}
#endif

