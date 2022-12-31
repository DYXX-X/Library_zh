// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "soc/soc_caps.h"

/**
 * @brief I2C端口号可以是I2C_NUM_0~（I2C_NUM_MAX-1）。
 */
typedef int i2c_port_t;

typedef enum{
    I2C_MODE_SLAVE = 0,   /*!< I2C从属模式*/
    I2C_MODE_MASTER,      /*!< I2C主模式*/
    I2C_MODE_MAX,
} i2c_mode_t;

typedef enum {
    I2C_MASTER_WRITE = 0,   /*!< I2C写入数据*/
    I2C_MASTER_READ,        /*!< I2C读取数据*/
} i2c_rw_t;

typedef enum {
    I2C_DATA_MODE_MSB_FIRST = 0,  /*!< I2C数据msb优先*/
    I2C_DATA_MODE_LSB_FIRST = 1,  /*!< I2C数据lsb优先*/
    I2C_DATA_MODE_MAX
} i2c_trans_mode_t;

typedef enum {
    I2C_ADDR_BIT_7 = 0,    /*!< 从模式的I2C 7位地址*/
    I2C_ADDR_BIT_10,       /*!< 从模式的I2C 10位地址*/
    I2C_ADDR_BIT_MAX,
} i2c_addr_mode_t;

typedef enum {
    I2C_MASTER_ACK = 0x0,        /*!< 读取每个字节的I2C ack*/
    I2C_MASTER_NACK = 0x1,       /*!< 读取每个字节的I2C nack*/
    I2C_MASTER_LAST_NACK = 0x2,   /*!< 最后一个字节的I2C nack*/
    I2C_MASTER_ACK_MAX,
} i2c_ack_type_t;

/**
 * @brief I2C时钟源，从最小到最大排序，按顺序排列。这可以在将来的使用中扩展。
 */
typedef enum {
    I2C_SCLK_DEFAULT = 0,    /*!< 未选择I2C源时钟*/
#if SOC_I2C_SUPPORT_APB
    I2C_SCLK_APB,            /*!< 来自APB的I2C源时钟，80M*/
#endif
#if SOC_I2C_SUPPORT_XTAL
    I2C_SCLK_XTAL,           /*!< 来自XTAL的I2C源时钟，40M*/
#endif
#if SOC_I2C_SUPPORT_RTC
    I2C_SCLK_RTC,            /*!< 来自8M RTC、8M的I2C源时钟*/
#endif
#if SOC_I2C_SUPPORT_REF_TICK
    I2C_SCLK_REF_TICK,       /*!< 来自REF_TICK的I2C源时钟，1M*/
#endif
    I2C_SCLK_MAX,
} i2c_sclk_t;

///使用clk_flags选取的时钟源可用的最高速度
#define I2C_CLK_FREQ_MAX                  (-1)

#if CONFIG_IDF_TARGET_ESP32
typedef enum{
    I2C_CMD_RESTART = 0,   /*!<I2C重启命令*/
    I2C_CMD_WRITE,         /*!<I2C写入命令*/
    I2C_CMD_READ,          /*!<I2C读取命令*/
    I2C_CMD_STOP,          /*!<I2C停止命令*/
    I2C_CMD_END            /*!<I2C结束命令*/
} i2c_opmode_t __attribute__((deprecated));
#endif

#ifdef __cplusplus
}
#endif

