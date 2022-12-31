/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_flash_partitions.h"
#include "esp32s3/rom/spi_flash.h"
#include "esp32s3/rom/opi_flash.h"
#include "mspi_timing_tuning_configs.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SPI_TIMING_CONFIG_NUM_DEFAULT               20  //这应该大于最大可用定时配置数
#define SPI_TIMING_TEST_DATA_LEN                    64
#define SPI_TIMING_PSRAM_TEST_DATA_ADDR             0
#define SPI_TIMING_FLASH_TEST_DATA_ADDR             ESP_BOOTLOADER_OFFSET
/**
 * @note BACKGOURND:
 *
 * SPI FLASH模块时钟和SPI PSRAM模块时钟来自SPI核心时钟，核心时钟来自系统时钟：
 *
 * PLL----||----FLASH模块时钟XTAL----|---->核心时钟---->|RTC8M----||----PSRAM模块时钟
 *
 * DDR代表双倍数据速率，MSPI采样在正边缘和负边缘。因此，实际spp将增加一倍。速度从高到低：120M DDR>80M DDR>120 SDR>80M SDR>。。。
 *
 * 速度低于120M SDR的模块无需调整
 *
 * @note 限制：如何确定728上的核心时钟。有两个限制。
 *
 * 1.MSPI FLASH和PSRAM共享核心时钟寄存器。因此：SPI_TIMING_FLASH_EXPECTED_CORE_CLK_MHZ==SPI_TIMING_PSRAM_EXPECTED_CORE _CLK_MHZ
 *
 * 2.DDR模式要求核心时钟分频器（core_clk/div=module_clk）为2的幂。
 */
//--------------------------------------FLASH采样模式--------------------------------------//
#define SPI_TIMING_FLASH_DTR_MODE                   CONFIG_ESPTOOLPY_FLASH_SAMPLE_MODE_DTR
#define SPI_TIMING_FLASH_STR_MODE                   CONFIG_ESPTOOLPY_FLASH_SAMPLE_MODE_STR
//--------------------------------------FLASH模块时钟--------------------------------------//
#if CONFIG_ESPTOOLPY_FLASHFREQ_20M
#define SPI_TIMING_FLASH_MODULE_CLOCK               20
#elif CONFIG_ESPTOOLPY_FLASHFREQ_40M
#define SPI_TIMING_FLASH_MODULE_CLOCK               40
#elif CONFIG_ESPTOOLPY_FLASHFREQ_80M
#define SPI_TIMING_FLASH_MODULE_CLOCK               80
#else //CONFIG_ESPTOOLPY_FLASHFREQ_120M
#define SPI_TIMING_FLASH_MODULE_CLOCK               120
#endif
//------------------------------------FLASH是否需要调整-------------------------------------//
#if SPI_TIMING_FLASH_DTR_MODE
#define SPI_TIMING_FLASH_NEEDS_TUNING               (SPI_TIMING_FLASH_MODULE_CLOCK > 40)
#elif SPI_TIMING_FLASH_STR_MODE
#define SPI_TIMING_FLASH_NEEDS_TUNING               (SPI_TIMING_FLASH_MODULE_CLOCK > 80)
#endif

//--------------------------------------PSRAM采样模式--------------------------------------//
#define SPI_TIMING_PSRAM_DTR_MODE                   CONFIG_SPIRAM_MODE_OCT
#define SPI_TIMING_PSRAM_STR_MODE                   !CONFIG_SPIRAM_MODE_OCT
//--------------------------------------PSRAM模块时钟--------------------------------------//
#if CONFIG_ESP32S3_SPIRAM_SUPPORT
#if CONFIG_SPIRAM_SPEED_40M
#define SPI_TIMING_PSRAM_MODULE_CLOCK               40
#elif CONFIG_SPIRAM_SPEED_80M
#define SPI_TIMING_PSRAM_MODULE_CLOCK               80
#else //CONFIG_SPIRAM_SPEED_120M
#define SPI_TIMING_PSRAM_MODULE_CLOCK               120
#endif
#else   //禁用PSRAM
#define SPI_TIMING_PSRAM_MODULE_CLOCK               10      //将其定义为10MHz，因为我们依赖“SPI_TIMING_PSRAM_MODULE_CLOCK”宏进行计算和检查，请参见“确定核心时钟”一章
#endif
//------------------------------------PSRAM是否需要调整-------------------------------------//
#if SPI_TIMING_PSRAM_DTR_MODE
#define SPI_TIMING_PSRAM_NEEDS_TUNING               (SPI_TIMING_PSRAM_MODULE_CLOCK > 40)
#elif SPI_TIMING_PSRAM_STR_MODE
#define SPI_TIMING_PSRAM_NEEDS_TUNING               (SPI_TIMING_PSRAM_MODULE_CLOCK > 80)
#endif


/**
 * @note 定义以下可行的核心时钟：SPI_TIMING_FLASH_EXPECTED_core_CLK_MHZ和SPI_TIMING_PSRAM_EXPECTED_core _CLK_MHZ
 */
/**
 * 由于MSPI闪存和PSRAM时钟都使用MSPI核心时钟，请在此处定义STR/DTR模式以选择核心时钟：
 * @note 如果Flash或PSRAM，或两者都设置为DTR模式，则使用DIV 2
 */
#if (SPI_TIMING_FLASH_DTR_MODE || SPI_TIMING_PSRAM_DTR_MODE)
#define SPI_TIMING_CORE_CLOCK_DIV                   2
#else  //#如果（SPI_TIMING_FLASH_STR_MODE&&（SPI_TIMING_PSRAM_STR_MODE||！CONFIG_ESP32S3_SPIRAM_SUPPORT））
#define SPI_TIMING_CORE_CLOCK_DIV                   1
#endif

///////////////////////////////////// FLASH CORE CLOCK /////////////////////////////////////
//FLASH 80M DTR
#if SPI_TIMING_FLASH_DTR_MODE && CONFIG_ESPTOOLPY_FLASHFREQ_80M
#define SPI_TIMING_FLASH_EXPECTED_CORE_CLK_MHZ      160
#endif

//FLASH 120M DTR
#if SPI_TIMING_FLASH_DTR_MODE && CONFIG_ESPTOOLPY_FLASHFREQ_120M
#define SPI_TIMING_FLASH_EXPECTED_CORE_CLK_MHZ      240
#endif

//FLASH 120M STR
#if SPI_TIMING_FLASH_STR_MODE && CONFIG_ESPTOOLPY_FLASHFREQ_120M
#if (SPI_TIMING_CORE_CLOCK_DIV == 2)
#define SPI_TIMING_FLASH_EXPECTED_CORE_CLK_MHZ      240
#elif (SPI_TIMING_CORE_CLOCK_DIV == 1)
#define SPI_TIMING_FLASH_EXPECTED_CORE_CLK_MHZ      120
#endif
#endif  //FLASH 120M STR

///////////////////////////////////// PSRAM CORE CLOCK /////////////////////////////////////
//PSRAM 80M DTR
#if SPI_TIMING_PSRAM_DTR_MODE && CONFIG_SPIRAM_SPEED_80M
#define SPI_TIMING_PSRAM_EXPECTED_CORE_CLK_MHZ      160
#endif

//PSRAM 120M STR
#if SPI_TIMING_PSRAM_STR_MODE && CONFIG_SPIRAM_SPEED_120M
#if (SPI_TIMING_CORE_CLOCK_DIV == 2)
#define SPI_TIMING_PSRAM_EXPECTED_CORE_CLK_MHZ      240
#elif (SPI_TIMING_CORE_CLOCK_DIV == 1)
#define SPI_TIMING_PSRAM_EXPECTED_CORE_CLK_MHZ      120
#endif
#endif  //PSRAM 120M STR


//------------------------------------------确定核心时钟-----------------------------------------------//
/**
 * @note 限制1：在728上，MSPI FLASH和PSRAM共享核心时钟寄存器。因此，预期的核心时钟频率应该相同。
 */
#if SPI_TIMING_FLASH_NEEDS_TUNING && SPI_TIMING_PSRAM_NEEDS_TUNING
_Static_assert(SPI_TIMING_FLASH_EXPECTED_CORE_CLK_MHZ == SPI_TIMING_PSRAM_EXPECTED_CORE_CLK_MHZ, "FLASH and PSRAM Mode configuration are not supported");
#define SPI_TIMING_CORE_CLOCK_MHZ                   SPI_TIMING_FLASH_EXPECTED_CORE_CLK_MHZ

//如果只有FLASH需要调整，核心时钟可能与FLASH预期的一样
#elif SPI_TIMING_FLASH_NEEDS_TUNING && !SPI_TIMING_PSRAM_NEEDS_TUNING
_Static_assert(SPI_TIMING_FLASH_EXPECTED_CORE_CLK_MHZ % SPI_TIMING_PSRAM_MODULE_CLOCK == 0, "FLASH and PSRAM Mode configuration are not supported");
#define SPI_TIMING_CORE_CLOCK_MHZ                   SPI_TIMING_FLASH_EXPECTED_CORE_CLK_MHZ

//如果只有PSRAM需要调整，核心时钟可能与PSRAM预期的一样
#elif !SPI_TIMING_FLASH_NEEDS_TUNING && SPI_TIMING_PSRAM_NEEDS_TUNING
_Static_assert(SPI_TIMING_PSRAM_EXPECTED_CORE_CLK_MHZ % SPI_TIMING_FLASH_MODULE_CLOCK == 0, "FLASH and PSRAM Mode configuration are not supported");
#define SPI_TIMING_CORE_CLOCK_MHZ                   SPI_TIMING_PSRAM_EXPECTED_CORE_CLK_MHZ

#else
#define SPI_TIMING_CORE_CLOCK_MHZ   80
#endif

/**
 * @note 限制2:DDR模式要求核心时钟分频器（core_clk/div=module_clk）为2的幂。
 */
#define CHECK_POWER_OF_2(n)                         ((((n) & ((~(n)) + 1))) == (n))

#if SPI_TIMING_FLASH_DTR_MODE
_Static_assert(CHECK_POWER_OF_2(SPI_TIMING_CORE_CLOCK_MHZ / SPI_TIMING_FLASH_MODULE_CLOCK), "FLASH and PSRAM Mode configuration are not supported");
#endif
#if SPI_TIMING_PSRAM_DTR_MODE
_Static_assert(CHECK_POWER_OF_2(SPI_TIMING_CORE_CLOCK_MHZ / SPI_TIMING_PSRAM_MODULE_CLOCK), "FLASH and PSRAM Mode configuration are not supported");
#endif


//------------------------------------------帮助程序宏获取FLASH/PSRAM调整配置-----------------------------------------------//
#define __GET_TUNING_CONFIG(type, core_clock, module_clock, mode) \
        (spi_timing_config_t) { .tuning_config_table = MSPI_TIMING_##type##_CONFIG_TABLE_CORE_CLK_##core_clock##M_MODULE_CLK_##module_clock##M_##mode, \
                                .available_config_num = MSPI_TIMING_##type##_CONFIG_NUM_CORE_CLK_##core_clock##M_MODULE_CLK_##module_clock##M_##mode, \
                                .default_config_id = MSPI_TIMING_##type##_DEFAULT_CONFIG_ID_CORE_CLK_##core_clock##M_MODULE_CLK_##module_clock##M_##mode }

#define _GET_TUNING_CONFIG(type, core_clock, module_clock, mode) __GET_TUNING_CONFIG(type, core_clock, module_clock, mode)

#define SPI_TIMING_FLASH_GET_TUNING_CONFIG(core_clock_mhz, module_clock_mhz, mode) _GET_TUNING_CONFIG(FLASH, core_clock_mhz, module_clock_mhz, mode)
#define SPI_TIMING_PSRAM_GET_TUNING_CONFIG(core_clock_mhz, module_clock_mhz, mode) _GET_TUNING_CONFIG(PSRAM, core_clock_mhz, module_clock_mhz, mode)


/**
 * SPI定时调整寄存器。下面的宏“SPI_TIMING_FLASH_CONFIG_TABLE”是相应的寄存器值表。上层依赖这3个寄存器来调整定时。
 */
typedef struct {
    uint8_t spi_din_mode;    /*!< 输入信号延迟模式*/
    uint8_t spi_din_num;     /*!< 输入信号延迟数*/
    uint8_t extra_dummy_len; /*!< 额外虚设长度*/
} spi_timing_tuning_param_t;

typedef struct {
    spi_timing_tuning_param_t tuning_config_table[SPI_TIMING_CONFIG_NUM_DEFAULT];   //可用的定时调整配置
    uint32_t available_config_num;
    uint32_t default_config_id; //如果调优失败，我们将使用此选项作为默认值
} spi_timing_config_t;

/**
 * SPI FLASH模块时钟和SPI PSRAM模块时钟来自SPI核心时钟，核心时钟来自系统时钟：
 *
 * PLL----||----FLASH模块时钟XTAL----|---->核心时钟---->|RTC8M----||----PSRAM模块时钟
 *
 */
typedef enum {
    SPI_TIMING_CONFIG_CORE_CLOCK_80M,
    SPI_TIMING_CONFIG_CORE_CLOCK_120M,
    SPI_TIMING_CONFIG_CORE_CLOCK_160M,
    SPI_TIMING_CONFIG_CORE_CLOCK_240M
} spi_timing_config_core_clock_t;


spi_timing_config_core_clock_t spi_timing_config_get_core_clock(void);
void spi_timing_config_set_core_clock(uint8_t spi_num, spi_timing_config_core_clock_t core_clock);

void spi_timing_config_set_flash_clock(uint8_t spi_num, uint32_t freqdiv);
void spi_timing_config_flash_set_din_mode_num(uint8_t spi_num, uint8_t din_mode, uint8_t din_num);
void spi_timing_config_flash_set_extra_dummy(uint8_t spi_num, uint8_t extra_dummy);
void spi_timing_config_flash_read_data(uint8_t spi_num, uint8_t *buf, uint32_t addr, uint32_t len);

void spi_timing_config_set_psram_clock(uint8_t spi_num, uint32_t freqdiv);
void spi_timing_config_psram_set_din_mode_num(uint8_t spi_num, uint8_t din_mode, uint8_t din_num);
void spi_timing_config_psram_set_extra_dummy(uint8_t spi_num, uint8_t extra_dummy);
void spi_timing_config_psram_write_data(uint8_t spi_num, uint8_t *buf, uint32_t addr, uint32_t len);
void spi_timing_config_psram_read_data(uint8_t spi_num,uint8_t *buf, uint32_t addr, uint32_t len);

/*-------------------------------------------------------------------------------------------------
 * SPI1定时调整API这些API仅用于`spi_flash_timeing_Tuning。c/sweep_for_success_sample_points（）用于配置SPI1定时调整相关寄存器以找到最佳调整参数
 *-------------------------------------------------------------------------------------------------*/
void spi_timing_config_flash_tune_din_num_mode(uint8_t din_mode, uint8_t din_num);
void spi_timing_config_flash_tune_dummy(uint8_t extra_dummy);
void spi_timing_config_psram_tune_din_num_mode(uint8_t din_mode, uint8_t din_num);
void spi_timing_config_psram_tune_dummy(uint8_t extra_dummy);

/**
 * SPI1注册信息获取API。这些API通知“spi_flash_timeing_tuning”。c’（驱动器层）。这样，其他组件（例如：esp_flash驱动程序）可以从中获取信息（“spi_flash_timeing_tuning.c”）。
 */
void spi_timing_config_get_cs_timing(uint8_t *setup_time, uint32_t *hold_time);
uint32_t spi_timing_config_get_flash_clock_reg(void);

#ifdef __cplusplus
}
#endif

