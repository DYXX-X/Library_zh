// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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
#include <sys/param.h> // 对于最小值/最大值
#include <stdbool.h>
#include <string.h>

#include "soc/spi_periph.h"
#include "soc/spi_mem_struct.h"
#include "hal/spi_types.h"
#include "hal/spi_flash_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define spimem_flash_ll_get_hw(host_id)  (((host_id)==SPI1_HOST ?  &SPIMEM1 : NULL ))
#define spimem_flash_ll_hw_get_id(dev)  ((dev) == (void*)&SPIMEM1? SPI1_HOST: -1)

typedef typeof(SPIMEM1.clock) spimem_flash_ll_clock_reg_t;

//支持的时钟寄存器值
#define SPIMEM_FLASH_LL_CLKREG_VAL_5MHZ   ((spimem_flash_ll_clock_reg_t){.val=0x000F070F})   ///<时钟设置为5 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_10MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00070307})   ///<时钟设置为10 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_20MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00030103})   ///<时钟设置为20 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_26MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00020002})   ///<时钟设置为26 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_40MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00010001})   ///<时钟设置为40 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_80MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x80000000})   ///<时钟设置为80 MHz

/*------------------------------------------------------------------------------
 * 控制
 *----------------------------------------------------------------------------*/
/**
 * 在配置和启动控制之前重置外围寄存器
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void spimem_flash_ll_reset(spi_mem_dev_t *dev)
{
    dev->user.val = 0;
    dev->ctrl.val = 0;
}

/**
 * 检查前一操作是否完成。
 *
 * @param dev 外围寄存器的起始地址。
 *
 * @return 如果执行了最后一个命令，则为true，否则为false。
 */
static inline bool spimem_flash_ll_cmd_is_done(const spi_mem_dev_t *dev)
{
    return (dev->cmd.val == 0);
}

/**
 * 擦除闪存芯片。
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void spimem_flash_ll_erase_chip(spi_mem_dev_t *dev)
{
    dev->cmd.flash_ce = 1;
}

/**
 * 擦除扇区，地址应由spimem_flash_ll_set_address设置。
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void spimem_flash_ll_erase_sector(spi_mem_dev_t *dev)
{
    dev->ctrl.val = 0;
    dev->cmd.flash_se = 1;
}

/**
 * 擦除块，地址应通过spimem_flash_ll_set_address设置。
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void spimem_flash_ll_erase_block(spi_mem_dev_t *dev)
{
    dev->cmd.flash_be = 1;
}

/**
 * 暂停擦除/编程操作。
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void spimem_flash_ll_suspend(spi_mem_dev_t *dev)
{
    dev->flash_sus_cmd.flash_pes = 1;
}

/**
 * 恢复暂停的擦除/编程操作。
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void spimem_flash_ll_resume(spi_mem_dev_t *dev)
{
    dev->flash_sus_cmd.flash_per = 1;
}

/**
 * 初始化自动等待空闲模式
 *
 * @param dev 外围寄存器的起始地址。
 * @param auto_sus 启用/禁用闪存自动挂起。
 */
static inline void spimem_flash_ll_auto_suspend_init(spi_mem_dev_t *dev, bool auto_sus)
{
    dev->flash_sus_ctrl.flash_pes_en = auto_sus; // 启用Flash自动挂起。
}

/**
 * 初始化自动恢复模式
 *
 * @param dev 外围寄存器的起始地址。
 * @param auto_res 启用/禁用闪存自动恢复。
 *
 */
static inline void spimem_flash_ll_auto_resume_init(spi_mem_dev_t *dev, bool auto_res)
{
    dev->misc.auto_per = auto_res;
}

/**
 * 设置闪存暂停命令，可能因芯片而异。
 *
 * @param dev 外围寄存器的起始地址。
 * @param sus_cmd 闪存暂停命令。
 *
 */
static inline void spimem_flash_ll_suspend_cmd_setup(spi_mem_dev_t *dev, uint32_t sus_cmd)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(dev->flash_sus_ctrl, flash_pes_command, sus_cmd);
}

/**
 * 设置闪存恢复命令，可能因芯片而异。
 *
 * @param dev 外围寄存器的起始地址。
 * @param res_cmd 闪存恢复命令。
 *
 */
static inline void spimem_flash_ll_resume_cmd_setup(spi_mem_dev_t *dev, uint32_t res_cmd)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(dev->flash_sus_ctrl, flash_per_command, res_cmd);
}

/**
 * 设置闪存读取暂停状态命令，可能因芯片而异。
 *
 * @param dev 外围寄存器的起始地址。
 * @param pesr_cmd 闪存读取暂停状态命令。
 *
 */
static inline void spimem_flash_ll_rd_sus_cmd_setup(spi_mem_dev_t *dev, uint32_t pesr_cmd)
{
    abort(); //esp32s3不支持
}

/**
 * 设置以检查SUS/SUS1/SUS2，以确保闪光灯的暂停状态。
 *
 * @param dev 外围寄存器的起始地址。
 * @param sus_check_sus_en 1： 启用，0：禁用。
 *
 */
static inline void spimem_flash_ll_sus_check_sus_setup(spi_mem_dev_t *dev, bool sus_check_sus_en)
{
    abort(); //esp32s3不支持
}

/**
 * 设置以检查SUS/SUS1/SUS2，以确保闪光灯的恢复状态。
 *
 * @param dev 外围寄存器的起始地址。
 * @param sus_check_sus_en 1： 启用，0：禁用。
 *
 */
static inline void spimem_flash_ll_res_check_sus_setup(spi_mem_dev_t *dev, bool res_check_sus_en)
{
    abort(); //不支持ont esp32s3
}

/**
 * 设置8位命令以读取挂起状态
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void spimem_flash_ll_set_read_sus_status(spi_mem_dev_t *dev, uint32_t sus_mask)
{
    abort();// esp32s3不支持
}

/**
 * 初始化自动等待空闲模式
 *
 * @param dev 外围寄存器的起始地址。
 * @param auto_waiti 启用/禁用自动等待空闲功能
 */
static inline void spimem_flash_ll_auto_wait_idle_init(spi_mem_dev_t *dev, bool auto_waiti)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(dev->flash_waiti_ctrl, waiti_cmd, 0x05); // 设置要发送的命令，以获取闪存状态注册表值。
    dev->flash_waiti_ctrl.waiti_en = auto_waiti;  // 启用自动等待空闲功能。
}

/**
 * 返回擦除或编程操作的挂起状态。
 *
 * @param dev 外围寄存器的起始地址。
 *
 * @return 如果挂起，则为true，否则为false。
 */
static inline bool spimem_flash_ll_sus_status(spi_mem_dev_t *dev)
{
    return dev->sus_status.flash_sus;
}

/**
 * 启用/禁用闪存芯片的写入保护。
 *
 * @param dev 外围寄存器的起始地址。
 * @param wp true表示启用保护，false表示禁用（写启用）。
 */
static inline void spimem_flash_ll_set_write_protect(spi_mem_dev_t *dev, bool wp)
{
    if (wp) {
        dev->cmd.flash_wrdi = 1;
    } else {
        dev->cmd.flash_wren = 1;
    }
}

/**
 * 完成“spimem_flash_ll_read”后，从缓冲区获取读取数据。
 *
 * @param dev 外围寄存器的起始地址。
 * @param buffer 保存输出数据的缓冲区
 * @param read_len 离开缓冲区的长度
 */
static inline void spimem_flash_ll_get_buffer_data(spi_mem_dev_t *dev, void *buffer, uint32_t read_len)
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
 * 设置要写入数据缓冲区的数据。
 *
 * @param dev 外围寄存器的起始地址。
 * @param buffer 保存数据的缓冲区
 * @param length 数据长度（字节）。
 */
static inline void spimem_flash_ll_set_buffer_data(spi_mem_dev_t *dev, const void *buffer, uint32_t length)
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
 * 编程闪存芯片的一页。在此之前调用`` spimem_flash_ll_set_address` `，将地址设置为程序。
 *
 * @param dev 外围寄存器的起始地址。
 * @param buffer 保存要编程的数据的缓冲区
 * @param length 编程长度。
 */
static inline void spimem_flash_ll_program_page(spi_mem_dev_t *dev, const void *buffer, uint32_t length)
{
    dev->user.usr_dummy = 0;
    spimem_flash_ll_set_buffer_data(dev, buffer, length);
    dev->cmd.flash_pp = 1;
}

/**
 * 触发用户定义的事务。在调用之前，应配置所有阶段，包括命令、地址、虚拟和数据阶段。
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void spimem_flash_ll_user_start(spi_mem_dev_t *dev)
{
    dev->cmd.usr = 1;
}

/**
 * 检查主机是否空闲以执行新命令。
 *
 * @param dev 外围寄存器的起始地址。
 *
 * @return 如果主机空闲，则为true，否则为false
 */
static inline bool spimem_flash_ll_host_idle(const spi_mem_dev_t *dev)
{
    return dev->fsm.st == 0;
}

/**
 * 设置要读取的用户定义事务的阶段
 *
 * @param dev 外围寄存器的起始地址。
 */
static inline void spimem_flash_ll_read_phase(spi_mem_dev_t *dev)
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
static inline void spimem_flash_ll_set_cs_pin(spi_mem_dev_t *dev, int pin)
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
static inline void spimem_flash_ll_set_read_mode(spi_mem_dev_t *dev, esp_flash_io_mode_t read_mode)
{
    typeof (dev->ctrl) ctrl = dev->ctrl;
    ctrl.val &= ~(SPI_MEM_FREAD_QIO_M | SPI_MEM_FREAD_QUAD_M | SPI_MEM_FREAD_DIO_M | SPI_MEM_FREAD_DUAL_M | SPI_MEM_FCMD_OCT | SPI_MEM_FADDR_OCT | SPI_MEM_FDIN_OCT | SPI_MEM_FDOUT_OCT);
    dev->ddr.fmem_ddr_en = 0;
    ctrl.val |= SPI_MEM_FASTRD_MODE_M;
    switch (read_mode) {
    case SPI_FLASH_FASTRD:
        //默认选项
        break;
    case SPI_FLASH_QIO:
        ctrl.fread_qio = 1;
        break;
    case SPI_FLASH_QOUT:
        ctrl.fread_quad = 1;
        break;
    case SPI_FLASH_DIO:
        ctrl.fread_dio = 1;
        break;
    case SPI_FLASH_DOUT:
        ctrl.fread_dual = 1;
        break;
    case SPI_FLASH_SLOWRD:
        ctrl.fastrd_mode = 0;
        break;
    case SPI_FLASH_OPI_STR:
        ctrl.faddr_oct = 1;
        ctrl.fcmd_oct = 1;
        ctrl.fdin_oct = 1;
        ctrl.fdout_oct = 1;
        break;
    case SPI_FLASH_OPI_DTR:
        ctrl.faddr_oct = 1;
        ctrl.fcmd_oct = 1;
        ctrl.fdin_oct = 1;
        ctrl.fdout_oct = 1;
        dev->ddr.fmem_ddr_en = 1;
        break;
    default:
        abort();
    }
    dev->ctrl = ctrl;
}

/**
 * 设置工作的时钟频率。
 *
 * @param dev 外围寄存器的起始地址。
 * @param clock_val 指向要设置的时钟值的指针
 */
static inline void spimem_flash_ll_set_clock(spi_mem_dev_t *dev, spimem_flash_ll_clock_reg_t *clock_val)
{
    dev->clock = *clock_val;
}

/**
 * 以位为单位设置输入长度。
 *
 * @param dev 外围寄存器的起始地址。
 * @param bitlen 输入长度，以位为单位。
 */
static inline void spimem_flash_ll_set_miso_bitlen(spi_mem_dev_t *dev, uint32_t bitlen)
{
    dev->user.usr_miso = bitlen > 0;
    dev->miso_dlen.usr_miso_bit_len = bitlen ? (bitlen - 1) : 0;
}

/**
 * 以位为单位设置输出长度（不包括命令、地址和伪相位）
 *
 * @param dev 外围寄存器的起始地址。
 * @param bitlen 输出长度，以位为单位。
 */
static inline void spimem_flash_ll_set_mosi_bitlen(spi_mem_dev_t *dev, uint32_t bitlen)
{
    dev->user.usr_mosi = bitlen > 0;
    dev->mosi_dlen.usr_mosi_bit_len = bitlen ? (bitlen - 1) : 0;
}

/**
 * 设置命令。
 *
 * @param dev 外围寄存器的起始地址。
 * @param command 要发送的命令
 * @param bitlen 命令的长度
 */
static inline void spimem_flash_ll_set_command(spi_mem_dev_t *dev, uint32_t command, uint32_t bitlen)
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
static inline int spimem_flash_ll_get_addr_bitlen(spi_mem_dev_t *dev)
{
    return dev->user.usr_addr ? dev->user1.usr_addr_bitlen + 1 : 0;
}

/**
 * 设置要发送的地址长度（以位为单位）。应在需要地址的命令之前调用，例如擦除扇区、读取、写入。。。
 *
 * @param dev 外围寄存器的起始地址。
 * @param bitlen 地址长度，以位为单位
 */
static inline void spimem_flash_ll_set_addr_bitlen(spi_mem_dev_t *dev, uint32_t bitlen)
{
    dev->user1.usr_addr_bitlen = (bitlen - 1);
    dev->user.usr_addr = bitlen ? 1 : 0;
}

/**
 * 设置要发送的地址。应在需要地址的命令之前调用，例如擦除扇区、读取、写入。。。
 *
 * @param dev 外围寄存器的起始地址。
 * @param addr 要发送的地址
 */
static inline void spimem_flash_ll_set_address(spi_mem_dev_t *dev, uint32_t addr)
{
    dev->addr = addr;
}

/**
 * 设置以用户模式发送的地址。应在需要地址的命令之前调用，例如擦除扇区、读取、写入。。。
 *
 * @param dev 外围寄存器的起始地址。
 * @param addr 要发送的地址
 */
static inline void spimem_flash_ll_set_usr_address(spi_mem_dev_t *dev, uint32_t addr, uint32_t bitlen)
{
    (void)bitlen;
    spimem_flash_ll_set_address(dev, addr);
}

/**
 * 设置虚拟循环的长度。
 *
 * @param dev 外围寄存器的起始地址。
 * @param dummy_n 虚拟相位周期
 */
static inline void spimem_flash_ll_set_dummy(spi_mem_dev_t *dev, uint32_t dummy_n)
{
    dev->user.usr_dummy = dummy_n ? 1 : 0;
    dev->user1.usr_dummy_cyclelen = dummy_n - 1;
}

/**
 * 在虚拟阶段设置D/Q输出电平
 *
 * @param dev 外围寄存器的起始地址。
 * @param out_en 是否为虚拟相位启用IO输出
 * @param out_level 虚输出电平
 */
static inline void spimem_flash_ll_set_dummy_out(spi_mem_dev_t *dev, uint32_t out_en, uint32_t out_lev)
{
    dev->ctrl.fdummy_out = out_en;
    dev->ctrl.q_pol = out_lev;
    dev->ctrl.d_pol = out_lev;
}

static inline void spimem_flash_ll_set_hold(spi_mem_dev_t *dev, uint32_t hold_n)
{
    dev->ctrl2.cs_hold_time = hold_n - 1;
    dev->user.cs_hold = (hold_n > 0? 1: 0);
}

static inline void spimem_flash_ll_set_cs_setup(spi_mem_dev_t *dev, uint32_t cs_setup_time)
{
    dev->user.cs_setup = (cs_setup_time > 0 ? 1 : 0);
    dev->ctrl2.cs_setup_time = cs_setup_time - 1;
}

static inline void spimem_flash_ll_set_extra_dummy(spi_mem_dev_t *dev, uint32_t extra_dummy)
{
    dev->timing_cali.extra_dummy_cyclelen = extra_dummy;
}

#ifdef __cplusplus
}
#endif

