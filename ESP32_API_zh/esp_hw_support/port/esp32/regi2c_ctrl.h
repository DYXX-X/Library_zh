/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "regi2c_apll.h"
#include "regi2c_bbpll.h"

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

/* 读/写内部控制总线的ROM功能*/
uint8_t rom_i2c_readReg(uint8_t block, uint8_t host_id, uint8_t reg_add);
uint8_t rom_i2c_readReg_Mask(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t msb, uint8_t lsb);
void rom_i2c_writeReg(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t data);
void rom_i2c_writeReg_Mask(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t msb, uint8_t lsb, uint8_t data);

#ifdef BOOTLOADER_BUILD

/**
 * 如果为引导加载程序进行编译，则可以直接调用ROM函数，而不需要锁。
 */
#define regi2c_ctrl_read_reg         rom_i2c_readReg
#define regi2c_ctrl_read_reg_mask    rom_i2c_readReg_Mask
#define regi2c_ctrl_write_reg        rom_i2c_writeReg
#define regi2c_ctrl_write_reg_mask   rom_i2c_writeReg_Mask

#else

#define i2c_read_reg_raw        rom_i2c_readReg
#define i2c_read_reg_mask_raw   rom_i2c_readReg_Mask
#define i2c_write_reg_raw       rom_i2c_writeReg
#define i2c_write_reg_mask_raw  rom_i2c_writeReg_Mask

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


#ifdef __cplusplus
}
#endif

