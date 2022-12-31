// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
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

/*******************************************************************************
 * 注意ll不是公共api，不要在应用程序代码中使用。参见hal/include/hal/readme.md中的自述文件
 ******************************************************************************/

// SPI闪存的低层

#pragma once

#include <stdlib.h>
#include "soc/spi_periph.h"
#include "soc/spi_struct.h"
#include "hal/spi_types.h"
#include "hal/spi_flash_types.h"
#include <sys/param.h> // 对于最小值/最大值
#include <stdbool.h>
#include <string.h>
#include "hal/misc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define gpspi_flash_ll_get_hw(host_id)  (((host_id)==SPI2_HOST ? &GPSPI2 \
                                                : ((host_id)==SPI3_HOST ? &GPSPI3 \
                                                : ({abort();(spi_dev_t*)0;}))))

#define gpspi_flash_ll_hw_get_id(dev)   ( ((dev) == (void*)&GPSPI2) ? SPI2_HOST : (\
                                          ((dev) == (void*)&GPSPI3) ? SPI3_HOST : (\
                                          -1 \
                                        )) )

typedef typeof(GPSPI2.clock) gpspi_flash_ll_clock_reg_t;

//支持的时钟寄存器值
#define GPSPI_FLASH_LL_CLKREG_VAL_5MHZ   ((gpspi_flash_ll_clock_reg_t){.val=0x0000F1CF})   ///<时钟设置为5 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_10MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x000070C7})   ///<时钟设置为10 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_20MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00003043})   ///<时钟设置为20 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_26MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00002002})   ///<时钟设置为26 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_40MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00001001})   ///<时钟设置为40 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_80MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x80000000})   ///<时钟设置为80 MHz

/*------------------------------------------------------------------------------
 * 控制
 *----------------------------------------------------------------------------*/
/**
 * 在配置和启动控制之前重置外围寄存器。
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void gpspi_flash_ll_reset(spi_dev_t *dev)
{
    dev->user.val = 0;
    dev->ctrl.val = 0;

    dev->clk_gate.clk_en = 1;
    dev->clk_gate.mst_clk_active = 1;
    dev->clk_gate.mst_clk_sel = 1;

    dev->dma_conf.val = 0;
    dev->dma_conf.tx_seg_trans_clr_en = 1;
    dev->dma_conf.rx_seg_trans_clr_en = 1;
    dev->dma_conf.dma_seg_trans_en = 0;
}

/**
 * 检查前一操作是否完成。
 *
 * @param dev 外围寄存器的起始地址。
 *
 * @return 如果执行了最后一个命令，则为true，否则为false。
 */
static inline bool gpspi_flash_ll_cmd_is_done(const spi_dev_t *dev)
{
    return (dev->cmd.usr == 0);
}

/**
 * 完成`gpspi_flash_ll_read``后，从缓冲区获取读取数据。
 *
 * @param dev 外围寄存器的起始地址。
 * @param buffer 保存输出数据的缓冲区
 * @param read_len 离开缓冲区的长度
 */
static inline void gpspi_flash_ll_get_buffer_data(spi_dev_t *dev, void *buffer, uint32_t read_len)
{
    if (((intptr_t)buffer % 4 == 0) && (read_len % 4 == 0)) {
        // 如果所有内容都是单词对齐的，请执行更快的记忆
        memcpy(buffer, (void *)dev->data_buf, read_len);
    } else {
        // 否则，慢速（er）路径会逐字复制
        int copy_len = read_len;
        for (uint32_t i = 0; i < (read_len + 3) / 4; i++) {
            int word_len = MIN(sizeof(uint32_t), copy_len);
            uint32_t word = dev->data_buf[i];
            memcpy(buffer, &word, word_len);
            buffer = (void *)((intptr_t)buffer + word_len);
            copy_len -= word_len;
        }
    }
}

/**
 * 将一个字写入数据缓冲区。
 *
 * @param dev 外围寄存器的起始地址。
 * @param word 要写入地址0的数据。
 */
static inline void gpspi_flash_ll_write_word(spi_dev_t *dev, uint32_t word)
{
    dev->data_buf[0] = word;
}

/**
 * 设置要写入数据缓冲区的数据。
 *
 * @param dev 外围寄存器的起始地址。
 * @param buffer 保存数据的缓冲区
 * @param length 数据长度（字节）。
 */
static inline void gpspi_flash_ll_set_buffer_data(spi_dev_t *dev, const void *buffer, uint32_t length)
{
    // 加载数据寄存器，一次一个字
    int num_words = (length + 3) / 4;
    for (int i = 0; i < num_words; i++) {
        uint32_t word = 0;
        uint32_t word_len = MIN(length, sizeof(word));
        memcpy(&word, buffer, word_len);
        dev->data_buf[i] = word;
        length -= word_len;
        buffer = (void *)((intptr_t)buffer + word_len);
    }
}

/**
 * 触发用户定义的事务。在调用之前，应配置所有阶段，包括命令、地址、虚拟和数据阶段。
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void gpspi_flash_ll_user_start(spi_dev_t *dev)
{
    dev->cmd.update = 1;
    while (dev->cmd.update);
    dev->cmd.usr = 1;
}

/**
 * 当闪光灯在spi模式下工作时，将HD引脚设置为高。
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void gpspi_flash_ll_set_hold_pol(spi_dev_t *dev, uint32_t pol_val)
{
    dev->ctrl.hold_pol = pol_val;
}

/**
 * 检查主机是否空闲以执行新命令。
 *
 * @param dev 外围寄存器的起始地址。
 *
 * @return 如果主机空闲，则为true，否则为false
 */
static inline bool gpspi_flash_ll_host_idle(const spi_dev_t *dev)
{
    return dev->cmd.usr == 0;
}

/**
 * 设置要读取的用户定义事务的阶段
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void gpspi_flash_ll_read_phase(spi_dev_t *dev)
{
    typeof (dev->user) user = {
        .usr_command = 1,
        .usr_mosi = 0,
        .usr_miso = 1,
        .usr_addr = 1,
    };
    dev->user = user;
}
/*------------------------------------------------------------------------------
 * 配置
 *----------------------------------------------------------------------------*/
/**
 * 选择用于闪光灯的引脚
 *
 * @param dev 外围寄存器的起始地址。
 * @param pin 要使用的引脚ID，0-2。设置为其他值可禁用所有CS引脚。
 */
static inline void gpspi_flash_ll_set_cs_pin(spi_dev_t *dev, int pin)
{
    dev->misc.cs0_dis = (pin == 0) ? 0 : 1;
    dev->misc.cs1_dis = (pin == 1) ? 0 : 1;
}

/**
 * 设置读io模式。
 *
 * @param dev 外围寄存器的起始地址。
 * @param read_mode 用于以下事务的I/O模式。
 */
static inline void gpspi_flash_ll_set_read_mode(spi_dev_t *dev, esp_flash_io_mode_t read_mode)
{
    typeof (dev->ctrl) ctrl = dev->ctrl;
    typeof (dev->user) user = dev->user;

    ctrl.val &= ~(SPI_FCMD_QUAD_M | SPI_FADDR_QUAD_M | SPI_FREAD_QUAD_M | SPI_FCMD_DUAL_M | SPI_FADDR_DUAL_M | SPI_FREAD_DUAL_M);
    user.val &= ~(SPI_FWRITE_QUAD_M | SPI_FWRITE_DUAL_M);

    switch (read_mode) {
    case SPI_FLASH_FASTRD:
        //默认选项
    case SPI_FLASH_SLOWRD:
        break;
    case SPI_FLASH_QIO:
        ctrl.fread_quad = 1;
        ctrl.faddr_quad = 1;
        user.fwrite_quad = 1;
        break;
    case SPI_FLASH_QOUT:
        ctrl.fread_quad = 1;
        user.fwrite_quad = 1;
        break;
    case SPI_FLASH_DIO:
        ctrl.fread_dual = 1;
        ctrl.faddr_dual = 1;
        user.fwrite_dual = 1;
        break;
    case SPI_FLASH_DOUT:
        ctrl.fread_dual = 1;
        user.fwrite_dual = 1;
        break;
    default:
        abort();
    }

    dev->ctrl = ctrl;
    dev->user = user;
}

/**
 * 设置工作的时钟频率。
 *
 * @param dev 外围寄存器的起始地址。
 * @param clock_val 指向要设置的时钟值的指针
 */
static inline void gpspi_flash_ll_set_clock(spi_dev_t *dev, gpspi_flash_ll_clock_reg_t *clock_val)
{
    dev->clock = *clock_val;
}

/**
 * 以位为单位设置输入长度。
 *
 * @param dev 外围寄存器的起始地址。
 * @param bitlen 输入长度，以位为单位。
 */
static inline void gpspi_flash_ll_set_miso_bitlen(spi_dev_t *dev, uint32_t bitlen)
{
    dev->user.usr_miso = bitlen > 0;
    if (bitlen) {
        dev->ms_dlen.ms_data_bitlen = bitlen - 1;
    }
}

/**
 * 以位为单位设置输出长度（不包括命令、地址和伪相位）
 *
 * @param dev 外围寄存器的起始地址。
 * @param bitlen 输出长度，以位为单位。
 */
static inline void gpspi_flash_ll_set_mosi_bitlen(spi_dev_t *dev, uint32_t bitlen)
{
    dev->user.usr_mosi = bitlen > 0;
    if (bitlen) {
        dev->ms_dlen.ms_data_bitlen = bitlen - 1;
    }
}

/**
 * 设置命令。
 *
 * @param dev 外围寄存器的起始地址。
 * @param command 要发送的命令
 * @param bitlen 命令的长度
 */
static inline void gpspi_flash_ll_set_command(spi_dev_t *dev, uint8_t command, uint32_t bitlen)
{
    dev->user.usr_command = 1;
    typeof(dev->user2) user2 = {
        .usr_command_value = command,
        .usr_command_bitlen = (bitlen - 1),
    };
    dev->user2 = user2;
}

/**
 * 获取寄存器中设置的地址长度（以位为单位）。
 *
 * @param dev 外围寄存器的起始地址。
 *
 */
static inline int gpspi_flash_ll_get_addr_bitlen(spi_dev_t *dev)
{
    return dev->user.usr_addr ? dev->user1.usr_addr_bitlen + 1 : 0;
}

/**
 * 设置要发送的地址长度（以位为单位）。应在需要地址的命令之前调用，例如擦除扇区、读取、写入。。。
 *
 * @param dev 外围寄存器的起始地址。
 * @param bitlen 地址长度，以位为单位
 */
static inline void gpspi_flash_ll_set_addr_bitlen(spi_dev_t *dev, uint32_t bitlen)
{
    dev->user1.usr_addr_bitlen = (bitlen - 1);
    dev->user.usr_addr = bitlen ? 1 : 0;
}

/**
 * 设置以用户模式发送的地址。应在需要地址的命令之前调用，例如擦除扇区、读取、写入。。。
 *
 * @param dev 外围寄存器的起始地址。
 * @param addr 要发送的地址
 */
static inline void gpspi_flash_ll_set_usr_address(spi_dev_t *dev, uint32_t addr, uint32_t bitlen)
{
    // 空白区域应全部为1
    uint32_t padding_ones = (bitlen == 32? 0 : UINT32_MAX >> bitlen);
    dev->addr = (addr << (32 - bitlen)) | padding_ones;
}


/**
 * 设置要发送的地址。应在需要地址的命令之前调用，例如擦除扇区、读取、写入。。。
 *
 * @param dev 外围寄存器的起始地址。
 * @param addr 要发送的地址
 */
static inline void gpspi_flash_ll_set_address(spi_dev_t *dev, uint32_t addr)
{
    dev->addr = addr;
}

/**
 * 设置虚拟循环的长度。
 *
 * @param dev 外围寄存器的起始地址。
 * @param dummy_n 虚拟相位周期
 */
static inline void gpspi_flash_ll_set_dummy(spi_dev_t *dev, uint32_t dummy_n)
{
    dev->user.usr_dummy = dummy_n ? 1 : 0;
    HAL_FORCE_MODIFY_U32_REG_FIELD(dev->user1, usr_dummy_cyclelen, dummy_n - 1)
}

/**
 * 在虚拟阶段设置D/Q输出电平
 *
 * @param dev 外围寄存器的起始地址。
 * @param out_en 是否为虚拟相位启用IO输出
 * @param out_level 虚输出电平
 */
static inline void gpspi_flash_ll_set_dummy_out(spi_dev_t *dev, uint32_t out_en, uint32_t out_lev)
{
    dev->ctrl.dummy_out = out_en;
    dev->ctrl.q_pol = out_lev;
    dev->ctrl.d_pol = out_lev;
}

/**
 * 设置时钟后CS的额外保持时间。
 *
 * @param dev 外围寄存器的起始地址。
 * @param hold_n CS未激活前的时钟周期
 */
static inline void gpspi_flash_ll_set_hold(spi_dev_t *dev, uint32_t hold_n)
{
    dev->user1.cs_hold_time = hold_n - 1;
    dev->user.cs_hold = (hold_n > 0? 1: 0);
}

static inline void gpspi_flash_ll_set_cs_setup(spi_dev_t *dev, uint32_t cs_setup_time)
{
    dev->user.cs_setup = (cs_setup_time > 0 ? 1 : 0);
    dev->user1.cs_setup_time = cs_setup_time - 1;
}

#ifdef __cplusplus
}
#endif

