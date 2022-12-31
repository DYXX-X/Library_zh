// 版权所有2020 Espressif Systems（上海）私人有限公司
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
 * 注意ll不是公共api，不要在应用程序代码中使用。请参阅soc/include/hal/readme.md中的自述文件
 ******************************************************************************/

// SPI闪存的低层

#pragma once

#include "gpspi_flash_ll.h"
#include "spimem_flash_ll.h"

#ifdef __cplusplus
extern "C" {
#endif

// 对于esp32s2，spimem等同于传统的spi外设
// 让spi闪存时钟寄存器定义反映这一点。
#define SPI_FLASH_LL_CLKREG_VAL_5MHZ   {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_5MHZ}
#define SPI_FLASH_LL_CLKREG_VAL_10MHZ  {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_10MHZ}
#define SPI_FLASH_LL_CLKREG_VAL_20MHZ  {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_20MHZ}
#define SPI_FLASH_LL_CLKREG_VAL_26MHZ  {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_26MHZ}
#define SPI_FLASH_LL_CLKREG_VAL_40MHZ  {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_40MHZ}
#define SPI_FLASH_LL_CLKREG_VAL_80MHZ  {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_80MHZ}

#define spi_flash_ll_get_hw(host_id)  (((host_id)<=SPI1_HOST ? (spi_dev_t*) spimem_flash_ll_get_hw(host_id) \
                                      : gpspi_flash_ll_get_hw(host_id)))

#define spi_flash_ll_hw_get_id(dev) ({int dev_id = spimem_flash_ll_hw_get_id(dev); \
                                     if (dev_id < 0) {\
                                        dev_id = gpspi_flash_ll_hw_get_id(dev);\
                                     }\
                                     dev_id; \
                                    })


typedef union  {
    gpspi_flash_ll_clock_reg_t gpspi;
    spimem_flash_ll_clock_reg_t spimem;
} spi_flash_ll_clock_reg_t;

#ifdef GPSPI_BUILD
#define spi_flash_ll_reset(dev)                              gpspi_flash_ll_reset((spi_dev_t*)dev)
#define spi_flash_ll_cmd_is_done(dev)                        gpspi_flash_ll_cmd_is_done((spi_dev_t*)dev)
#define spi_flash_ll_get_buffer_data(dev, buffer, read_len)  gpspi_flash_ll_get_buffer_data((spi_dev_t*)dev, buffer, read_len)
#define spi_flash_ll_set_buffer_data(dev, buffer, len)       gpspi_flash_ll_set_buffer_data((spi_dev_t*)dev, buffer, len)
#define spi_flash_ll_user_start(dev)                         gpspi_flash_ll_user_start((spi_dev_t*)dev)
#define spi_flash_ll_host_idle(dev)                          gpspi_flash_ll_host_idle((spi_dev_t*)dev)
#define spi_flash_ll_read_phase(dev)                         gpspi_flash_ll_read_phase((spi_dev_t*)dev)
#define spi_flash_ll_set_cs_pin(dev, pin)                    gpspi_flash_ll_set_cs_pin((spi_dev_t*)dev, pin)
#define spi_flash_ll_set_read_mode(dev, read_mode)           gpspi_flash_ll_set_read_mode((spi_dev_t*)dev, read_mode)
#define spi_flash_ll_set_clock(dev, clk)                     gpspi_flash_ll_set_clock((spi_dev_t*)dev, (gpspi_flash_ll_clock_reg_t*)clk)
#define spi_flash_ll_set_miso_bitlen(dev, bitlen)            gpspi_flash_ll_set_miso_bitlen((spi_dev_t*)dev, bitlen)
#define spi_flash_ll_set_mosi_bitlen(dev, bitlen)            gpspi_flash_ll_set_mosi_bitlen((spi_dev_t*)dev, bitlen)
#define spi_flash_ll_set_command(dev, cmd, bitlen)           gpspi_flash_ll_set_command((spi_dev_t*)dev, cmd, bitlen)
#define spi_flash_ll_set_addr_bitlen(dev, bitlen)            gpspi_flash_ll_set_addr_bitlen((spi_dev_t*)dev, bitlen)
#define spi_flash_ll_get_addr_bitlen(dev)                    gpspi_flash_ll_get_addr_bitlen((spi_dev_t*)dev)
#define spi_flash_ll_set_address(dev, addr)                  gpspi_flash_ll_set_address((spi_dev_t*)dev, addr)
#define spi_flash_ll_set_usr_address(dev, addr, bitlen)      gpspi_flash_ll_set_usr_address((spi_dev_t*)dev, addr, bitlen)
#define spi_flash_ll_set_dummy(dev, dummy)                   gpspi_flash_ll_set_dummy((spi_dev_t*)dev, dummy)
#define spi_flash_ll_set_dummy_out(dev, en, lev)             gpspi_flash_ll_set_dummy_out((spi_dev_t*)dev, en, lev)
#define spi_flash_ll_set_hold(dev, hold_n)                   gpspi_flash_ll_set_hold((spi_dev_t*)dev, hold_n)
#define spi_flash_ll_set_cs_setup(dev, cs_setup_time)        gpspi_flash_ll_set_cs_setup((spi_dev_t*)dev, cs_setup_time)
#else
#define spi_flash_ll_reset(dev)                              spimem_flash_ll_reset((spi_mem_dev_t*)dev)
#define spi_flash_ll_cmd_is_done(dev)                        spimem_flash_ll_cmd_is_done((spi_mem_dev_t*)dev)
#define spi_flash_ll_erase_chip(dev)                         spimem_flash_ll_erase_chip((spi_mem_dev_t*)dev)
#define spi_flash_ll_erase_sector(dev)                       spimem_flash_ll_erase_sector((spi_mem_dev_t*)dev)
#define spi_flash_ll_erase_block(dev)                        spimem_flash_ll_erase_block((spi_mem_dev_t*)dev)
#define spi_flash_ll_set_write_protect(dev, wp)              spimem_flash_ll_set_write_protect((spi_mem_dev_t*)dev, wp)
#define spi_flash_ll_get_buffer_data(dev, buffer, read_len)  spimem_flash_ll_get_buffer_data((spi_mem_dev_t*)dev, buffer, read_len)
#define spi_flash_ll_set_buffer_data(dev, buffer, len)       spimem_flash_ll_set_buffer_data((spi_mem_dev_t*)dev, buffer, len)
#define spi_flash_ll_program_page(dev, buffer, len)          spimem_flash_ll_program_page((spi_mem_dev_t*)dev, buffer, len)
#define spi_flash_ll_user_start(dev)                         spimem_flash_ll_user_start((spi_mem_dev_t*)dev)
#define spi_flash_ll_host_idle(dev)                          spimem_flash_ll_host_idle((spi_mem_dev_t*)dev)
#define spi_flash_ll_read_phase(dev)                         spimem_flash_ll_read_phase((spi_mem_dev_t*)dev)
#define spi_flash_ll_set_cs_pin(dev, pin)                    spimem_flash_ll_set_cs_pin((spi_mem_dev_t*)dev, pin)
#define spi_flash_ll_set_read_mode(dev, read_mode)           spimem_flash_ll_set_read_mode((spi_mem_dev_t*)dev, read_mode)
#define spi_flash_ll_set_clock(dev, clk)                     spimem_flash_ll_set_clock((spi_mem_dev_t*)dev, (spimem_flash_ll_clock_reg_t*)clk)
#define spi_flash_ll_set_miso_bitlen(dev, bitlen)            spimem_flash_ll_set_miso_bitlen((spi_mem_dev_t*)dev, bitlen)
#define spi_flash_ll_set_mosi_bitlen(dev, bitlen)            spimem_flash_ll_set_mosi_bitlen((spi_mem_dev_t*)dev, bitlen)
#define spi_flash_ll_set_command(dev, cmd, bitlen)           spimem_flash_ll_set_command((spi_mem_dev_t*)dev, cmd, bitlen)
#define spi_flash_ll_set_addr_bitlen(dev, bitlen)            spimem_flash_ll_set_addr_bitlen((spi_mem_dev_t*)dev, bitlen)
#define spi_flash_ll_get_addr_bitlen(dev)                    spimem_flash_ll_get_addr_bitlen((spi_mem_dev_t*) dev)
#define spi_flash_ll_set_address(dev, addr)                  spimem_flash_ll_set_address((spi_mem_dev_t*)dev, addr)
#define spi_flash_ll_set_usr_address(dev, addr, bitlen)      spimem_flash_ll_set_usr_address((spi_mem_dev_t*)dev, addr, bitlen)
#define spi_flash_ll_set_dummy(dev, dummy)                   spimem_flash_ll_set_dummy((spi_mem_dev_t*)dev, dummy)
#define spi_flash_ll_set_dummy_out(dev, en, lev)             spimem_flash_ll_set_dummy_out((spi_mem_dev_t*)dev, en, lev)
#define spi_flash_ll_set_hold(dev, hold_n)                   spimem_flash_ll_set_hold((spi_mem_dev_t*)dev, hold_n)
#define spi_flash_ll_set_cs_setup(dev, cs_setup_time)        spimem_flash_ll_set_cs_setup((spi_mem_dev_t*)dev, cs_setup_time)

#endif

#ifdef __cplusplus
}
#endif

