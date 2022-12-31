/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

// 长期计划是拥有一个单一的soc_caps。h表示所有外围设备。
// 在重构和多芯片支持开发过程中，我们
// 将这些信息分离为peripher_caps。每个外围设备和
// 将它们包括在这里，以避免产生冲突。

#pragma once

/*-------------------------- COMMON CAPS ---------------------------------------*/
#define SOC_ADC_SUPPORTED               1
#define SOC_PCNT_SUPPORTED              1
#define SOC_TWAI_SUPPORTED              1
#define SOC_GDMA_SUPPORTED              1
#define SOC_LCDCAM_SUPPORTED            1
#define SOC_MCPWM_SUPPORTED             1
#define SOC_DEDICATED_GPIO_SUPPORTED    1
#define SOC_CPU_CORES_NUM               2
#define SOC_CACHE_SUPPORT_WRAP          1
#define SOC_ULP_SUPPORTED               1
#define SOC_BT_SUPPORTED                1
#define SOC_USB_OTG_SUPPORTED           1
#define SOC_USB_SERIAL_JTAG_SUPPORTED   1
#define SOC_RTC_SLOW_MEM_SUPPORTED      1
#define SOC_CCOMP_TIMER_SUPPORTED       1
#define SOC_DIG_SIGN_SUPPORTED          1
#define SOC_HMAC_SUPPORTED              1
#define SOC_ASYNC_MEMCPY_SUPPORTED      1
#define SOC_SUPPORTS_SECURE_DL_MODE     1
#define SOC_EFUSE_SECURE_BOOT_KEY_DIGESTS 3
#define SOC_EFUSE_REVOKE_BOOT_KEY_DIGESTS 1
#define SOC_SDMMC_HOST_SUPPORTED        1
#define SOC_FLASH_ENCRYPTION_XTS_AES      1
#define SOC_FLASH_ENCRYPTION_XTS_AES_256 1
#define SOC_PSRAM_DMA_CAPABLE           1
#define SOC_XT_WDT_SUPPORTED            1

/*-------------------------- SOC CAPS ----------------------------------------*/
#define SOC_APPCPU_HAS_CLOCK_GATING_BUG (1)

/*-------------------------- ADC CAPS ----------------------------------------*/
/*!< SAR ADC模块*/
#define SOC_ADC_RTC_CTRL_SUPPORTED              1
#define SOC_ADC_DIG_CTRL_SUPPORTED              1
#define SOC_ADC_ARBITER_SUPPORTED               1
#define SOC_ADC_FILTER_SUPPORTED                1
#define SOC_ADC_MONITOR_SUPPORTED               1
#define SOC_ADC_PERIPH_NUM                      (2)
#define SOC_ADC_CHANNEL_NUM(PERIPH_NUM)         (10)
#define SOC_ADC_MAX_CHANNEL_NUM                 (10)

/*!< 数字的*/
#define SOC_ADC_DIGI_CONTROLLER_NUM             (2)
#define SOC_ADC_PATT_LEN_MAX                    (24)    //两个模式表，每个包含12项。每个项目占用1个字节
#define SOC_ADC_DIGI_MAX_BITWIDTH               (13)
/*!< F_sample=F_digi_con/2/间隔。F_digi_con=5M。30<=间隔<=4095*/
#define SOC_ADC_SAMPLE_FREQ_THRES_HIGH          83333
#define SOC_ADC_SAMPLE_FREQ_THRES_LOW           611

/*!< RTC */
#define SOC_ADC_MAX_BITWIDTH                    (12)

/*!< 标定*/
#define SOC_ADC_CALIBRATION_V1_SUPPORTED        (1) /*!< 支持HW偏移校准版本1*/


/*-------------------------- APB BACKUP DMA CAPS -------------------------------*/
#define SOC_APB_BACKUP_DMA              (1)

/*-------------------------- BROWNOUT CAPS -----------------------------------*/
#include "brownout_caps.h"

/*-------------------------- CPU CAPS ----------------------------------------*/
#include "cpu_caps.h"

/*-------------------------- DIGITAL SIGNATURE CAPS ----------------------------------------*/
/**数字签名的最大长度（以位为单位）。*/
#define SOC_DS_SIGNATURE_MAX_BIT_LEN (4096)

/**RSA密钥参数消息摘要（MD）的初始化向量（IV）长度（字节）。*/
#define SOC_DS_KEY_PARAM_MD_IV_LENGTH (16)

/**DS参数解密密钥的最长等待时间。如果过期，则键入错误。详见TRM DS章节*/
#define SOC_DS_KEY_CHECK_MAX_WAIT_US (1100)

/*-------------------------- GDMA CAPS ---------------------------------------*/
#define SOC_GDMA_GROUPS            (1)  // GDMA组数
#define SOC_GDMA_PAIRS_PER_GROUP   (5)  // 每组GDMA对数
#define SOC_GDMA_SUPPORT_PSRAM     (1)  // GDMA可以访问外部PSRAM
#define SOC_GDMA_PSRAM_MIN_ALIGN   (16) // PSRAM事务的最小对齐

/*-------------------------- GPIO CAPS ---------------------------------------*/
#include "gpio_caps.h"

/*--------------------------专用GPIO CAPS-----------------------------*/
#define SOC_DEDIC_GPIO_OUT_CHANNELS_NUM (8) /*!< 每个CPU核心上有8个向外通道*/
#define SOC_DEDIC_GPIO_IN_CHANNELS_NUM  (8) /*!< 每个CPU核心上有8个向内通道*/
#define SOC_DEDIC_GPIO_OUT_AUTO_ENABLE  (1) /*!< 自动启用专用GPIO输出属性*/

/*-------------------------- I2C CAPS ----------------------------------------*/
#include "i2c_caps.h"

/*-------------------------- I2S CAPS ----------------------------------------*/
#define SOC_I2S_NUM                 (2)
#define SOC_I2S_SUPPORTS_PCM        (1)
#define SOC_I2S_SUPPORTS_PDM_TX     (1)
#define SOC_I2S_SUPPORTS_PDM_RX     (1)
#define SOC_I2S_SUPPORTS_PDM_CODEC  (1)
#define SOC_I2S_SUPPORTS_TDM        (1)

/*-------------------------- LEDC CAPS ---------------------------------------*/
#include "ledc_caps.h"

/*-------------------------- MCPWM CAPS --------------------------------------*/
#define SOC_MCPWM_GROUPS                     (2)    ///芯片上<2个MCPWM组（即独立MCPWM外围设备的数量）
#define SOC_MCPWM_TIMERS_PER_GROUP           (3)    ///<每组的计时器数量
#define SOC_MCPWM_OPERATORS_PER_GROUP        (3)    ///<每个组拥有的操作员数量
#define SOC_MCPWM_COMPARATORS_PER_OPERATOR   (2)    ///<每个操作员拥有的比较器数量
#define SOC_MCPWM_GENERATORS_PER_OPERATOR    (2)    ///<每个操作员拥有的发电机数量
#define SOC_MCPWM_TRIGGERS_PER_OPERATOR      (2)    ///<每个操作员拥有的触发器数量
#define SOC_MCPWM_GPIO_FAULTS_PER_GROUP      (3)    ///<每组故障信号检测器的数量
#define SOC_MCPWM_CAPTURE_TIMERS_PER_GROUP   (1)    ///<每个组具有的捕获计时器的数量
#define SOC_MCPWM_CAPTURE_CHANNELS_PER_TIMER (3)    ///<每个捕获计时器具有的捕获通道数
#define SOC_MCPWM_GPIO_SYNCHROS_PER_GROUP    (3)    ///<每组具有的GPIO同步器数量
#define SOC_MCPWM_SWSYNC_CAN_PROPAGATE       (1)    ///<软件同步事件可以路由到其输出
#define SOC_MCPWM_BASE_CLK_HZ       (160000000ULL)  ///<160MHz的基本时钟频率

/*-------------------------- MPU CAPS ----------------------------------------*/
#include "mpu_caps.h"

/*-------------------------- PCNT CAPS ---------------------------------------*/
#define SOC_PCNT_GROUPS               (1)
#define SOC_PCNT_UNITS_PER_GROUP      (4)
#define SOC_PCNT_CHANNELS_PER_UNIT    (2)
#define SOC_PCNT_THRES_POINT_PER_UNIT (2)

/*-------------------------- RMT CAPS ----------------------------------------*/
#define SOC_RMT_GROUPS                    (1)  /*!< 一个RMT组*/
#define SOC_RMT_TX_CANDIDATES_PER_GROUP   (4)  /*!< 每组中能够传输的信道数*/
#define SOC_RMT_RX_CANDIDATES_PER_GROUP   (4)  /*!< 每组中能够接收的信道数*/
#define SOC_RMT_CHANNELS_PER_GROUP        (8)  /*!< 共8个通道*/
#define SOC_RMT_MEM_WORDS_PER_CHANNEL     (48) /*!< 每个通道拥有48个字的内存（1个字=4字节）*/
#define SOC_RMT_SUPPORT_RX_PINGPONG       (1)  /*!< 支持RX路径上的Ping Pong模式*/
#define SOC_RMT_SUPPORT_RX_DEMODULATION   (1)  /*!< 支持RX路径上的信号解调（即去除载波）*/
#define SOC_RMT_SUPPORT_TX_LOOP_COUNT     (1)  /*!< 支持在循环模式下传输指定的循环数*/
#define SOC_RMT_SUPPORT_TX_LOOP_AUTOSTOP  (1)  /*!< 环路模式下自动停止的硬件支持*/
#define SOC_RMT_SUPPORT_TX_SYNCHRO        (1)  /*!< 支持协调一组TX信道同时启动*/
#define SOC_RMT_SUPPORT_XTAL              (1)  /*!< 支持将XTAL时钟设置为RMT时钟源*/


/*-------------------------- LCD CAPS ----------------------------------------*/
/* 注意：在esp32-s3上，I80总线和RGB定时发生器不能同时工作*/
#define SOC_LCD_I80_SUPPORTED           (1)  /*!< 支持Intel 8080 LCD*/
#define SOC_LCD_RGB_SUPPORTED           (1)  /*!< 支持RGB LCD*/
#define SOC_LCD_I80_BUSES               (1)  /*!< 有一个LCD Intel 8080总线*/
#define SOC_LCD_RGB_PANELS              (1)  /*!< 支持一个RGB LCD面板*/
#define SOC_LCD_I80_BUS_WIDTH           (16) /*!< Intel 8080总线宽度*/
#define SOC_LCD_RGB_DATA_WIDTH          (16) /*!< LCD数据线数量*/

/*-------------------------- RTC CAPS --------------------------------------*/
#define SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH       (128)
#define SOC_RTC_CNTL_CPU_PD_REG_FILE_NUM        (549)
#define SOC_RTC_CNTL_CPU_PD_DMA_ADDR_ALIGN      (SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH >> 3)
#define SOC_RTC_CNTL_CPU_PD_DMA_BLOCK_SIZE      (SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH >> 3)

#define SOC_RTC_CNTL_CPU_PD_RETENTION_MEM_SIZE  (SOC_RTC_CNTL_CPU_PD_REG_FILE_NUM * (SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH >> 3))

/* I/O缓存标记内存保留硬件参数*/
#define SOC_RTC_CNTL_TAGMEM_PD_DMA_BUS_WIDTH    (128)
#define SOC_RTC_CNTL_TAGMEM_PD_DMA_ADDR_ALIGN   (SOC_RTC_CNTL_TAGMEM_PD_DMA_BUS_WIDTH >> 3)

/*-------------------------- RTCIO CAPS --------------------------------------*/
#include "rtc_io_caps.h"

/*-------------------------- SIGMA DELTA CAPS --------------------------------*/
#define SOC_SIGMADELTA_NUM         (1) // 1 sigma delta外围
#define SOC_SIGMADELTA_CHANNEL_NUM (8) // 8个通道

/*-------------------------- SPI CAPS ----------------------------------------*/
#define SOC_SPI_PERIPH_NUM                  3
#define SOC_SPI_DMA_CHAN_NUM                3
#define SOC_SPI_PERIPH_CS_NUM(i)            3
#define SOC_SPI_MAXIMUM_BUFFER_SIZE         64
#define SOC_SPI_SUPPORT_DDRCLK              1
#define SOC_SPI_SLAVE_SUPPORT_SEG_TRANS     1
#define SOC_SPI_SUPPORT_CD_SIG              1
#define SOC_SPI_SUPPORT_CONTINUOUS_TRANS    1
#define SOC_SPI_SUPPORT_SLAVE_HD_VER2       1

// 外围设备支持DIO、DOUT、QIO或QOUT
#define SOC_SPI_PERIPH_SUPPORT_MULTILINE_MODE(host_id)  ({(void)host_id; 1;})

// 外围设备在其“虚拟阶段”支持输出给定电平
#define SOC_SPI_PERIPH_SUPPORT_CONTROL_DUMMY_OUTPUT 1
#define SOC_MEMSPI_IS_INDEPENDENT                   1
#define SOC_SPI_MAX_PRE_DIVIDER                     16
#define SOC_SPI_SUPPORT_OCT                         1

/*-------------------------- SPIRAM CAPS ----------------------------------------*/
#define SOC_SPIRAM_SUPPORTED            1

/*-------------------------- SYS TIMER CAPS ----------------------------------*/
#define SOC_TOUCH_VERSION_2                (1)  // 触摸传感器的硬件版本
#define SOC_SYSTIMER_COUNTER_NUM           (2)  // 计数器单元数量
#define SOC_SYSTIMER_ALARM_NUM             (3)  // 报警单元数量
#define SOC_SYSTIMER_BIT_WIDTH_LO          (32) // 系统下部钻头宽度
#define SOC_SYSTIMER_BIT_WIDTH_HI          (20) // 系统高位部分的位宽
#define SOC_SYSTIMER_FIXED_TICKS_US        (16) // 每微秒的滴答数是固定的
#define SOC_SYSTIMER_INT_LEVEL             (1)  // Systimer外围设备使用级别
#define SOC_SYSTIMER_ALARM_MISS_COMPENSATE (1)  // 如果t（目标）>t（当前），Systimer外设可以立即生成中断

/*-------------------------- TIMER GROUP CAPS --------------------------------*/
#define SOC_TIMER_GROUPS                  (2)
#define SOC_TIMER_GROUP_TIMERS_PER_GROUP  (2)
#define SOC_TIMER_GROUP_COUNTER_BIT_WIDTH (54)
#define SOC_TIMER_GROUP_SUPPORT_XTAL      (1)
#define SOC_TIMER_GROUP_TOTAL_TIMERS (SOC_TIMER_GROUPS * SOC_TIMER_GROUP_TIMERS_PER_GROUP)

/*-------------------------- TOUCH SENSOR CAPS -------------------------------*/
#define SOC_TOUCH_SENSOR_NUM                (15) /*! 15个触摸通道*/
#define SOC_TOUCH_PROXIMITY_CHANNEL_NUM     (3)  /* Sopport触摸接近通道编号。*/
#define SOC_TOUCH_PROXIMITY_MEAS_DONE_SUPPORTED (1) /*Sopport触摸接近通道测量完成中断类型。*/

#define SOC_TOUCH_PAD_THRESHOLD_MAX         (0x1FFFFF)  /*!<如果设置了触摸阈值最大值，则触摸传感器不能处于触摸状态*/
#define SOC_TOUCH_PAD_MEASURE_WAIT_MAX      (0xFF)  /*!<定时器频率为8Mhz，最大值为0xff*/

/*-------------------------- TWAI CAPS ---------------------------------------*/
#include "twai_caps.h"

/*-------------------------- UART CAPS ---------------------------------------*/
#include "uart_caps.h"

#define SOC_UART_SUPPORT_RTC_CLK    (1)     /*!< 支持RTC时钟作为时钟源*/
#define SOC_UART_SUPPORT_XTAL_CLK   (1)     /*!< 支持XTAL时钟作为时钟源*/
#define SOC_UART_REQUIRE_CORE_RESET (1)

/*-------------------------- USB CAPS ----------------------------------------*/
#define SOC_USB_PERIPH_NUM 1


/*--------------------------- SHA CAPS ---------------------------------------*/
/* 单个DMA操作中的最大字节数为4095，对于SHA，这意味着最大的安全字节数为31个128字节的块=3968
*/
#define SOC_SHA_DMA_MAX_BUFFER_SIZE     (3968)
#define SOC_SHA_SUPPORT_DMA             (1)

/* SHA引擎能够从用户提供的上下文恢复哈希*/
#define SOC_SHA_SUPPORT_RESUME          (1)

/* 具有与所有外围设备共享的集中式DMA*/
#define SOC_SHA_GDMA             (1)

/* 支持的硬件算法*/
#define SOC_SHA_SUPPORT_SHA1            (1)
#define SOC_SHA_SUPPORT_SHA224          (1)
#define SOC_SHA_SUPPORT_SHA256          (1)
#define SOC_SHA_SUPPORT_SHA384          (1)
#define SOC_SHA_SUPPORT_SHA256          (1)
#define SOC_SHA_SUPPORT_SHA512          (1)
#define SOC_SHA_SUPPORT_SHA512_224      (1)
#define SOC_SHA_SUPPORT_SHA512_256      (1)
#define SOC_SHA_SUPPORT_SHA512_T        (1)


/*--------------------------- RSA CAPS ---------------------------------------*/
#define SOC_RSA_MAX_BIT_LEN    (4096)


/*-------------------------- AES CAPS -----------------------------------------*/
#define SOC_AES_SUPPORT_DMA     (1)

/* 具有与所有外围设备共享的集中式DMA*/
#define SOC_AES_GDMA            (1)

#define SOC_AES_SUPPORT_AES_128 (1)
#define SOC_AES_SUPPORT_AES_256 (1)


/*--------------------------电源管理CAPS---------------------------*/
#define SOC_PM_SUPPORT_EXT_WAKEUP       (1)

#define SOC_PM_SUPPORT_WIFI_WAKEUP      (1)

#define SOC_PM_SUPPORT_BT_WAKEUP        (1)

#define SOC_PM_SUPPORT_CPU_PD           (1)

#define SOC_PM_SUPPORT_TAGMEM_PD        (1)

#define SOC_PM_SUPPORT_TOUCH_SENSOR_WAKEUP    (1)     /*!<支持从触摸板触发唤醒*/

#define SOC_PM_SUPPORT_DEEPSLEEP_VERIFY_STUB_ONLY   (1)


/*--------------------------闪存加密CAPS----------------------------*/
#define SOC_FLASH_ENCRYPTED_XTS_AES_BLOCK_MAX   (64)


/*-------------------------- WI-FI HARDWARE TSF CAPS -------------------------------*/
#define SOC_WIFI_HW_TSF                 (1)

/*--------------- PHY REGISTER AND MEMORY SIZE CAPS --------------------------*/
#define SOC_PHY_DIG_REGS_MEM_SIZE       (21*4)
#define SOC_MAC_BB_PD_MEM_SIZE          (192*4)

/*--------------- WIFI LIGHT SLEEP CLOCK WIDTH CAPS --------------------------*/
#define SOC_WIFI_LIGHT_SLEEP_CLK_WIDTH  (12)

/*-------------------------- SPI MEM CAPS ---------------------------------------*/
#define SOC_SPI_MEM_SUPPORT_AUTO_WAIT_IDLE                (1)
#define SOC_SPI_MEM_SUPPORT_AUTO_SUSPEND                  (1)
#define SOC_SPI_MEM_SUPPORT_AUTO_RESUME                   (1)
#define SOC_SPI_MEM_SUPPORT_SW_SUSPEND                    (1)
#define SOC_SPI_MEM_SUPPORT_OPI_MODE                      (1)
#define SOC_SPI_MEM_SUPPORT_TIME_TUNING                   (1)

/*-------------------------- COEXISTENCE HARDWARE PTI CAPS -------------------------------*/
#define SOC_COEX_HW_PTI                 (1)

/*-------------------------- SDMMC CAPS -----------------------------------------*/

/* 卡检测、写保护、中断在所有芯片上使用GPIO矩阵。在ESP32-S3上，时钟/命令/数据引脚也使用GPIO矩阵。
 */
#define SOC_SDMMC_USE_GPIO_MATRIX  1
#define SOC_SDMMC_NUM_SLOTS        2
/* 表示SDMMC可以选择使用XTAL时钟而不是PLL*/
#define SOC_SDMMC_SUPPORT_XTAL_CLOCK    1

