/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*
 * Soc功能文件，描述以下芯片属性：
 * -是否支持外围设备或功能
 * -资源数量（外围设备、通道等）
 * -硬件的最大/最小值，包括：缓冲区/fifo大小、事务长度、支持的频率等。
 *
 * 对于布尔定义：
 * -如果为true：“#define MODULE_[SUBMODULE_]SUPPORT_FEATURE 1”。（通过“#if x”检查时，“#define”空白字符串会导致错误）
 * -如果为false：根本不定义任何内容。（即使之前定义了“#define 0”，“#ifdef x”也为真。）
 *
 * 取决于此文件的代码使用这些布尔定义作为“#if x”或“#if！x`。（“#ifdef/ifndef x”与“#define x 0”不兼容。虽然我们不建议使用“#defin x 0”，但仍有风险。）
 *
 * ECO异常（&E）：对于ECO ed布尔值，“#define x”Not determined“”。当“#if x”和“#if！x’，使这些缺失的定义更加明显。
 */

#pragma once

#ifdef __has_include
#  if __has_include("sdkconfig.h")
#    include "sdkconfig.h"
#    define SOC_CAPS_ECO_VER    CONFIG_ESP32_REV_MIN
#  endif
#endif

#if __DOXYGEN__ && !defined(SOC_CAPS_ECO_VER)
#define SOC_CAPS_ECO_VER    SOC_CAPS_ECO_VER_MAX
#endif

#ifndef SOC_CAPS_ECO_VER
#warning ECO version not determined. Some ECO related caps will not be available.
#warning Define SOC_CAPS_ECO_VER before including this header.

// 在此处定义ECO ed功能的警告字符串，以在未使用时显示错误
// 正确定义
#define SOC_BROWNOUT_RESET_SUPPORTED    "Not determined"
#define SOC_TWAI_BRP_DIV_SUPPORTED      "Not determined"
#endif

/*-------------------------- COMMON CAPS ---------------------------------------*/
#define SOC_CAPS_ECO_VER_MAX        3

#define SOC_ADC_SUPPORTED           1
#define SOC_DAC_SUPPORTED           1
#define SOC_MCPWM_SUPPORTED         1
#define SOC_SDMMC_HOST_SUPPORTED    1
#define SOC_BT_SUPPORTED            1
#define SOC_CLASSIC_BT_SUPPORTED    1
#define SOC_PCNT_SUPPORTED          1
#define SOC_SDIO_SLAVE_SUPPORTED    1
#define SOC_TWAI_SUPPORTED          1
#define SOC_EMAC_SUPPORTED          1
#define SOC_CPU_CORES_NUM           2
#define SOC_ULP_SUPPORTED           1
#define SOC_RTC_SLOW_MEM_SUPPORTED  1
#define SOC_CCOMP_TIMER_SUPPORTED   1
#define SOC_EFUSE_SECURE_BOOT_KEY_DIGESTS 1

/*-------------------------- ADC CAPS ----------------------------------------*/
/**
 * 待移除检查adc是否支持数字控制器（DMA）模式。
 * @value
 *      -1：支架；
 *      -0：不支持；
 */
#define SOC_ADC_SUPPORT_DMA_MODE(PERIPH_NUM) ((PERIPH_NUM==0)? 1: 0)

/*!< SAR ADC模块*/
#define SOC_ADC_RTC_CTRL_SUPPORTED              1
#define SOC_ADC_DIG_CTRL_SUPPORTED              1
#define SOC_ADC_PERIPH_NUM                      (2)
#define SOC_ADC_CHANNEL_NUM(PERIPH_NUM)         ((PERIPH_NUM==0)? 8: 10)
#define SOC_ADC_MAX_CHANNEL_NUM                 (10)

/*!< 数字的*/
#define SOC_ADC_DIGI_CONTROLLER_NUM             (2)
#define SOC_ADC_PATT_LEN_MAX                    (16) //两个模式表，每个包含16项。每个项目需要1个字节。但仅支持使用DMA模式的ADC1
#define SOC_ADC_DIGI_MIN_BITWIDTH               (9)
#define SOC_ADC_DIGI_MAX_BITWIDTH               (12)
/*!< F_sample=F_digi_con/2/间隔。F_digi_con=5M。30<=间隔<=4095*/
#define SOC_ADC_SAMPLE_FREQ_THRES_HIGH          (2*1000*1000)
#define SOC_ADC_SAMPLE_FREQ_THRES_LOW           (2000)

/*!< RTC */
#define SOC_ADC_MAX_BITWIDTH                    (12)


/*-------------------------- BROWNOUT CAPS -----------------------------------*/
#if SOC_CAPS_ECO_VER >= 1
#define SOC_BROWNOUT_RESET_SUPPORTED 1
#endif

/*-------------------------- CPU CAPS ----------------------------------------*/
#define SOC_CPU_BREAKPOINTS_NUM         2
#define SOC_CPU_WATCHPOINTS_NUM         2

#define SOC_CPU_WATCHPOINT_SIZE         64 // 字节

#define SOC_CPU_HAS_FPU             1

/*-------------------------- DAC CAPS ----------------------------------------*/
#define SOC_DAC_PERIPH_NUM      2
#define SOC_DAC_RESOLUTION      8 // DAC分辨率8位

/*-------------------------- GPIO CAPS ---------------------------------------*/
// ESP32具有1个GPIO外围设备
#define SOC_GPIO_PORT                   (1)
#define SOC_GPIO_PIN_COUNT              40

// 未定义SOC_GPIO_SUPPORT_RTC_INDEPENDENT。在ESP32上，具有RTC功能的PAD必须
// 通过RTC寄存器设置上拉/下拉/功能。在ESP32-S2上，数字IO有自己的寄存器
// 控制上拉/下拉/能力，独立于RTC寄存器。

// 0～39（24、28～31除外）有效
#define SOC_GPIO_VALID_GPIO_MASK        (0xFFFFFFFFFFULL & ~(0ULL | BIT24 | BIT28 | BIT29 | BIT30 | BIT31))
// GPIO>=34仅为输入
#define SOC_GPIO_VALID_OUTPUT_GPIO_MASK (SOC_GPIO_VALID_GPIO_MASK & ~(0ULL | BIT34 | BIT35 | BIT36 | BIT37 | BIT38 | BIT39))

// 支持配置休眠状态
#define SOC_GPIO_SUPPORT_SLP_SWITCH  (1)

/*-------------------------- I2C CAPS ----------------------------------------*/
// ESP32具有2个I2C。
#define SOC_I2C_NUM             (2)

#define SOC_I2C_FIFO_LEN        (32) /*!< I2C硬件FIFO深度*/

#define SOC_I2C_SUPPORT_APB     (1)

/*-------------------------- APLL CAPS ----------------------------------------*/
#define SOC_CLK_APLL_SUPPORTED       (1)
// apl_multiplier_out=xtal_freq*（4+sdm2+sdm1/256+sdm0/65536）
#define SOC_APLL_MULTIPLIER_OUT_MIN_HZ (350000000) // 350兆赫
#define SOC_APLL_MULTIPLIER_OUT_MAX_HZ (500000000) // 500兆赫
#define SOC_APLL_MIN_HZ    (5303031)   // 5.303031兆赫
#define SOC_APLL_MAX_HZ    (125000000) // 125兆赫

/*-------------------------- I2S CAPS ----------------------------------------*/
// ESP32有2个I2S
#define SOC_I2S_NUM                 (2U)
#define SOC_I2S_SUPPORTS_APLL       (1) // ESP32支持APLL
#define SOC_I2S_SUPPORTS_PDM_TX     (1)
#define SOC_I2S_SUPPORTS_PDM_RX     (1)
#define SOC_I2S_SUPPORTS_ADC        (1) // ESP32支持ADC和DAC
#define SOC_I2S_SUPPORTS_DAC        (1)

#define SOC_I2S_TRANS_SIZE_ALIGN_WORD (1) // I2S DMA传输大小必须与字对齐
#define SOC_I2S_LCD_I80_VARIANT       (1) // I2S具有特殊的LCD模式，可生成Intel 8080 TX定时

/*-------------------------- LCD CAPS ----------------------------------------*/
/* 注：在esp32上，LCD intel 8080计时由I2S外围设备生成*/
#define SOC_LCD_I80_SUPPORTED      (1)  /*!< 支持Intel 8080 LCD*/
#define SOC_LCD_I80_BUSES          (1)  /*!< 只有I2S0具有LCD模式*/
#define SOC_LCD_I80_BUS_WIDTH      (24) /*!< Intel 8080总线宽度*/

/*-------------------------- LEDC CAPS ---------------------------------------*/
#define SOC_LEDC_SUPPORT_HS_MODE  (1)
#define SOC_LEDC_SUPPORT_HS_MODE     (1)
#define SOC_LEDC_CHANNEL_NUM         (8)
#define SOC_LEDC_TIMER_BIT_WIDE_NUM  (20)

/*-------------------------- MCPWM CAPS --------------------------------------*/
#define SOC_MCPWM_GROUPS                     (2)    ///芯片上<2个MCPWM组（即独立MCPWM外围设备的数量）
#define SOC_MCPWM_TIMERS_PER_GROUP           (3)    ///<每组的计时器数量
#define SOC_MCPWM_OPERATORS_PER_GROUP        (3)    ///<每个组拥有的操作员数量
#define SOC_MCPWM_COMPARATORS_PER_OPERATOR   (2)    ///<每个操作员拥有的比较器数量
#define SOC_MCPWM_GENERATORS_PER_OPERATOR    (2)    ///<每个操作员拥有的发电机数量
#define SOC_MCPWM_TRIGGERS_PER_OPERATOR      (2)    ///<每个操作员拥有的触发器数量
#define SOC_MCPWM_GPIO_FAULTS_PER_GROUP      (3)    ///<每组具有的GPIO故障信号数量
#define SOC_MCPWM_CAPTURE_TIMERS_PER_GROUP   (1)    ///<每个组具有的捕获计时器的数量
#define SOC_MCPWM_CAPTURE_CHANNELS_PER_TIMER (3)    ///<每个捕获计时器具有的捕获通道数
#define SOC_MCPWM_GPIO_SYNCHROS_PER_GROUP    (3)    ///<每组具有的GPIO同步器数量
#define SOC_MCPWM_BASE_CLK_HZ       (160000000ULL)  ///<160MHz的基本时钟频率

/*-------------------------- MPU CAPS ----------------------------------------*/
//TODO:更正调用者并删除不支持的行
#define SOC_MPU_CONFIGURABLE_REGIONS_SUPPORTED    0
#define SOC_MPU_MIN_REGION_SIZE                   0x20000000U
#define SOC_MPU_REGIONS_MAX_NUM                   8
#define SOC_MPU_REGION_RO_SUPPORTED               0
#define SOC_MPU_REGION_WO_SUPPORTED               0

/*-------------------------- PCNT CAPS ---------------------------------------*/
#define SOC_PCNT_GROUPS                  (1)
#define SOC_PCNT_UNITS_PER_GROUP         (8)
#define SOC_PCNT_CHANNELS_PER_UNIT       (2)
#define SOC_PCNT_THRES_POINT_PER_UNIT    (2)

/*-------------------------- RMT CAPS ----------------------------------------*/
#define SOC_RMT_GROUPS                  (1)  /*!< 一个RMT组*/
#define SOC_RMT_TX_CANDIDATES_PER_GROUP (8)  /*!< 每组中能够传输的信道数*/
#define SOC_RMT_RX_CANDIDATES_PER_GROUP (8)  /*!< 每组中能够接收的信道数*/
#define SOC_RMT_CHANNELS_PER_GROUP      (8)  /*!< 共8个通道*/
#define SOC_RMT_MEM_WORDS_PER_CHANNEL   (64) /*!< 每个频道拥有64个字的内存*/
#define SOC_RMT_SUPPORT_REF_TICK        (1)  /*!< 支持将REF_TICK设置为RMT时钟源*/
#define SOC_RMT_CHANNEL_CLK_INDEPENDENT (1)  /*!< 可以为每个通道选择不同的源时钟*/

/*-------------------------- RTCIO CAPS --------------------------------------*/
#define SOC_RTCIO_PIN_COUNT 18
#define SOC_RTCIO_INPUT_OUTPUT_SUPPORTED 1
#define SOC_RTCIO_HOLD_SUPPORTED 1
#define SOC_RTCIO_WAKE_SUPPORTED 1

/*-------------------------- SIGMA DELTA CAPS --------------------------------*/
#define SOC_SIGMADELTA_NUM            1
#define SOC_SIGMADELTA_CHANNEL_NUM (8) // 8个通道

/*-------------------------- SPI CAPS ----------------------------------------*/
#define SOC_SPI_PERIPH_NUM          3
#define SOC_SPI_DMA_CHAN_NUM        2

#define SOC_SPI_PERIPH_CS_NUM(i)    3

#define SOC_SPI_MAXIMUM_BUFFER_SIZE 64
#define SOC_SPI_MAX_PRE_DIVIDER     8192

#define SOC_SPI_SUPPORT_AS_CS       1 //支持在时钟切换时切换CS

// 外围设备支持DIO、DOUT、QIO或QOUT
#define SOC_SPI_PERIPH_SUPPORT_MULTILINE_MODE(spi_host)         ({(void)spi_host; 1;})

/*-------------------------- TIMER GROUP CAPS --------------------------------*/
#define SOC_TIMER_GROUPS                  (2)
#define SOC_TIMER_GROUP_TIMERS_PER_GROUP  (2)
#define SOC_TIMER_GROUP_COUNTER_BIT_WIDTH (64)
#define SOC_TIMER_GROUP_TOTAL_TIMERS (SOC_TIMER_GROUPS * SOC_TIMER_GROUP_TIMERS_PER_GROUP)

/*-------------------------- TOUCH SENSOR CAPS -------------------------------*/
#define SOC_TOUCH_VERSION_1                 (1)     /*!<触摸传感器的硬件版本*/
#define SOC_TOUCH_SENSOR_NUM                (10)

#define SOC_TOUCH_PAD_MEASURE_WAIT_MAX      (0xFF)  /*!<定时器频率为8Mhz，最大值为0xff*/
#define SOC_TOUCH_PAD_THRESHOLD_MAX         (0)     /*!<如果设置了触摸阈值最大值，则触摸传感器不能处于触摸状态*/

/*-------------------------- TWAI CAPS ---------------------------------------*/
#define SOC_TWAI_BRP_MIN                        2
#if SOC_CAPS_ECO_VER >= 2
#  define SOC_TWAI_BRP_MAX              256
#  define SOC_TWAI_BRP_DIV_SUPPORTED    1
#  define SOC_TWAI_BRP_DIV_THRESH       128
#else
#  define SOC_TWAI_BRP_MAX              128
#endif
#define SOC_TWAI_SUPPORT_MULTI_ADDRESS_LAYOUT   1

/*-------------------------- UART CAPS ---------------------------------------*/
// ESP32有3个UART。
#define SOC_UART_NUM                (3)
#define SOC_UART_SUPPORT_REF_TICK   (1)         /*!< 支持REF_TICK作为时钟源*/
#define SOC_UART_FIFO_LEN           (128)       /*!< UART硬件FIFO长度*/
#define SOC_UART_BITRATE_MAX        (5000000)   /*!< UART支持的最大比特率*/


/*-------------------------- SPIRAM CAPS -------------------------------------*/
#define SOC_SPIRAM_SUPPORTED    1

/*--------------------------- SHA CAPS ---------------------------------------*/
/* ESP32型SHA引擎，可并行存储多个状态*/
#define SOC_SHA_SUPPORT_PARALLEL_ENG    (1)

/* 支持的硬件算法*/
#define SOC_SHA_SUPPORT_SHA1            (1)
#define SOC_SHA_SUPPORT_SHA256          (1)
#define SOC_SHA_SUPPORT_SHA384          (1)
#define SOC_SHA_SUPPORT_SHA512          (1)


/*--------------------------- RSA CAPS ---------------------------------------*/
#define SOC_RSA_MAX_BIT_LEN    (4096)


/*-------------------------- AES CAPS -----------------------------------------*/
#define SOC_AES_SUPPORT_AES_128 (1)
#define SOC_AES_SUPPORT_AES_192 (1)
#define SOC_AES_SUPPORT_AES_256 (1)

/*--------------------------闪存加密CAPS----------------------------*/
#define SOC_FLASH_ENCRYPTED_XTS_AES_BLOCK_MAX   (32)

/*--------------- PHY REGISTER AND MEMORY SIZE CAPS --------------------------*/
#define SOC_PHY_DIG_REGS_MEM_SIZE       (21*4)

/*--------------------------电源管理CAPS---------------------------*/
#define SOC_PM_SUPPORT_EXT_WAKEUP       (1)
#define SOC_PM_SUPPORT_TOUCH_SENSOR_WAKEUP        (1)     /*!<支持从触摸板触发唤醒*/

/* ----------------------------兼容性------------------------------*/
#define SOC_CAN_SUPPORTED                   SOC_TWAI_SUPPORTED
#define CAN_BRP_MIN                         SOC_TWAI_BRP_MIN
#define CAN_BRP_MAX                         SOC_TWAI_BRP_MAX
#define CAN_SUPPORT_MULTI_ADDRESS_LAYOUT    SOC_TWAI_SUPPORT_MULTI_ADDRESS_LAYOUT
#if SOC_CAPS_ECO_VER >= 2
#  define CAN_BRP_DIV_SUPPORTED             SOC_TWAI_BRP_DIV_SUPPORTED
#  define CAN_BRP_DIV_THRESH                SOC_TWAI_BRP_DIV_THRESH
#endif

/*-------------------------- SDMMC CAPS -----------------------------------------*/

/* 在ESP32上，时钟/命令/数据引脚使用IO MUX。卡检测、写保护、中断在所有芯片上使用GPIO矩阵。
 */
#define SOC_SDMMC_USE_IOMUX  1
#define SOC_SDMMC_NUM_SLOTS  2

/*------------------------------ BLE --------------------------------------------*/
#define SOC_BLE_DONT_UPDATE_OWN_RPA  (1)

