/*
 * SPDX文件版权所有文本：2020-2022 Espressif Systems（上海）有限公司
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

/*-------------------------- COMMON CAPS ---------------------------------------*/
#define SOC_ADC_SUPPORTED               1
#define SOC_DAC_SUPPORTED               1
#define SOC_TWAI_SUPPORTED              1
#define SOC_CP_DMA_SUPPORTED            1
#define SOC_CPU_CORES_NUM               1
#define SOC_DEDICATED_GPIO_SUPPORTED    1
#define SOC_SUPPORTS_SECURE_DL_MODE     1
#define SOC_RISCV_COPROC_SUPPORTED      1
#define SOC_USB_OTG_SUPPORTED           1
#define SOC_PCNT_SUPPORTED              1
#define SOC_ULP_SUPPORTED               1
#define SOC_RTC_SLOW_MEM_SUPPORTED      1
#define SOC_CCOMP_TIMER_SUPPORTED       1
#define SOC_DIG_SIGN_SUPPORTED          1
#define SOC_HMAC_SUPPORTED              1
#define SOC_ASYNC_MEMCPY_SUPPORTED      1
#define SOC_EFUSE_SECURE_BOOT_KEY_DIGESTS 3
#define SOC_EFUSE_REVOKE_BOOT_KEY_DIGESTS 1
#define SOC_TEMP_SENSOR_SUPPORTED       1
#define SOC_CACHE_SUPPORT_WRAP          1
#define SOC_FLASH_ENCRYPTION_XTS_AES      1
#define SOC_FLASH_ENCRYPTION_XTS_AES_256 1
#define SOC_PSRAM_DMA_CAPABLE           1
#define SOC_XT_WDT_SUPPORTED            1

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
#define SOC_ADC_PATT_LEN_MAX                    (32) /*!< 两个模式表，每个包含16项。每个项目占用1个字节*/
#define SOC_ADC_DIGI_MAX_BITWIDTH               (12)
/*!< F_sample=F_digi_con/2/间隔。F_digi_con=5M。30<=间隔<=4095*/
#define SOC_ADC_SAMPLE_FREQ_THRES_HIGH          83333
#define SOC_ADC_SAMPLE_FREQ_THRES_LOW           611

/*!< RTC */
#define SOC_ADC_MAX_BITWIDTH                    (13)

/*!< 标定*/
#define SOC_ADC_CALIBRATION_V1_SUPPORTED        (1) /*!< 支持HW偏移校准版本1*/

/*-------------------------- BROWNOUT CAPS -----------------------------------*/
#define SOC_BROWNOUT_RESET_SUPPORTED 1

/*-------------------------- CP-DMA CAPS -------------------------------------*/
#define SOC_CP_DMA_MAX_BUFFER_SIZE (4095) /*!< 可附加到描述符的缓冲区的最大大小*/

/*-------------------------- CPU CAPS ----------------------------------------*/
#define SOC_CPU_BREAKPOINTS_NUM         2
#define SOC_CPU_WATCHPOINTS_NUM         2

#define SOC_CPU_WATCHPOINT_SIZE         64 // 字节

/*-------------------------- DAC CAPS ----------------------------------------*/
#define SOC_DAC_PERIPH_NUM      2
#define SOC_DAC_RESOLUTION      8 // DAC分辨率8位

/*-------------------------- GPIO CAPS ---------------------------------------*/
// ESP32-S2具有1个GPIO外围设备
#define SOC_GPIO_PORT           (1)
#define SOC_GPIO_PIN_COUNT      (47)

// 在ESP32-S2上，具有RTC功能的PAD必须通过RTC寄存器设置上拉/下拉/功能。
// 在ESP32-S2上，数字IO有自己的寄存器来控制上拉/下拉/功能，独立于RTC寄存器。
#define SOC_GPIO_SUPPORT_RTC_INDEPENDENT (1)
// 强制保持是ESP32-S2的新功能
#define SOC_GPIO_SUPPORT_FORCE_HOLD      (1)

// 0~46（22~25除外）有效
#define SOC_GPIO_VALID_GPIO_MASK             (0x7FFFFFFFFFFFULL & ~(0ULL | BIT22 | BIT23 | BIT24 | BIT25))
// GPIO 46仅为输入
#define SOC_GPIO_VALID_OUTPUT_GPIO_MASK     (SOC_GPIO_VALID_GPIO_MASK & ~(0ULL | BIT46))

// 支持配置休眠状态
#define SOC_GPIO_SUPPORT_SLP_SWITCH  (1)

/*--------------------------专用GPIO CAPS---------------------------------------*/
#define SOC_DEDIC_GPIO_OUT_CHANNELS_NUM (8) /*!< 每个CPU核心上有8个向外通道*/
#define SOC_DEDIC_GPIO_IN_CHANNELS_NUM  (8) /*!< 每个CPU核心上有8个向内通道*/
#define SOC_DEDIC_GPIO_ALLOW_REG_ACCESS (1) /*!< 允许通过寄存器访问专用GPIO通道*/
#define SOC_DEDIC_GPIO_HAS_INTERRUPT    (1) /*!< 专用GPIO有自己的中断源*/
#define SOC_DEDIC_GPIO_OUT_AUTO_ENABLE  (1) /*!< 自动启用专用GPIO输出属性*/

/*-------------------------- I2C CAPS ----------------------------------------*/
// ESP32-S2具有2个I2C。
#define SOC_I2C_NUM            (2)

#define SOC_I2C_FIFO_LEN       (32) /*!< I2C硬件FIFO深度*/

//ESP32-S2支持硬件FSM重置
#define SOC_I2C_SUPPORT_HW_FSM_RST  (1)
//ESP32-S2支持硬件清除总线
#define SOC_I2C_SUPPORT_HW_CLR_BUS  (1)

#define SOC_I2C_SUPPORT_REF_TICK   (1)
#define SOC_I2C_SUPPORT_APB        (1)

/*-------------------------- APLL CAPS ----------------------------------------*/
#define SOC_CLK_APLL_SUPPORTED       (1)
// apl_multiplier_out=xtal_freq*（4+sdm2+sdm1/256+sdm0/65536）
#define SOC_APLL_MULTIPLIER_OUT_MIN_HZ (350000000) // 350兆赫
#define SOC_APLL_MULTIPLIER_OUT_MAX_HZ (500000000) // 500兆赫
#define SOC_APLL_MIN_HZ    (5303031)   // 5.303031兆赫
#define SOC_APLL_MAX_HZ    (125000000) // 125兆赫

/*-------------------------- I2S CAPS ----------------------------------------*/
// ESP32-S2具有1个I2S
#define SOC_I2S_NUM                (1)
#define SOC_I2S_SUPPORTS_APLL      (1)// ESP32-S2支持APLL
#define SOC_I2S_SUPPORTS_DMA_EQUAL (1)
#define SOC_I2S_LCD_I80_VARIANT    (1)

/*-------------------------- LCD CAPS ----------------------------------------*/
/* 注：在esp32-s2上，LCD intel 8080定时由I2S外围设备生成*/
#define SOC_LCD_I80_SUPPORTED      (1)  /*!< 支持Intel 8080 LCD*/
#define SOC_LCD_I80_BUSES          (1)  /*!< 只有I2S0具有LCD模式*/
#define SOC_LCD_I80_BUS_WIDTH      (24) /*!< Intel 8080总线宽度*/

/*-------------------------- LEDC CAPS ---------------------------------------*/
#define SOC_LEDC_SUPPORT_XTAL_CLOCK  (1)
#define SOC_LEDC_CHANNEL_NUM         (8)
#define SOC_LEDC_TIMER_BIT_WIDE_NUM  (14)

/*-------------------------- MPU CAPS ----------------------------------------*/
//TODO:更正调用者并删除不支持的行
#define SOC_MPU_CONFIGURABLE_REGIONS_SUPPORTED    0
#define SOC_MPU_MIN_REGION_SIZE                   0x20000000U
#define SOC_MPU_REGIONS_MAX_NUM                   8
#define SOC_MPU_REGION_RO_SUPPORTED               0
#define SOC_MPU_REGION_WO_SUPPORTED               0

/*-------------------------- PCNT CAPS ---------------------------------------*/
#define SOC_PCNT_GROUPS               (1)
#define SOC_PCNT_UNITS_PER_GROUP      (4)
#define SOC_PCNT_CHANNELS_PER_UNIT    (2)
#define SOC_PCNT_THRES_POINT_PER_UNIT (2)

/*-------------------------- RMT CAPS ----------------------------------------*/
#define SOC_RMT_GROUPS                  (1)  /*!< 一个RMT组*/
#define SOC_RMT_TX_CANDIDATES_PER_GROUP (4)  /*!< 每组中能够传输的信道数*/
#define SOC_RMT_RX_CANDIDATES_PER_GROUP (4)  /*!< 每组中能够接收的信道数*/
#define SOC_RMT_CHANNELS_PER_GROUP      (4)  /*!< 共4个通道*/
#define SOC_RMT_MEM_WORDS_PER_CHANNEL   (64) /*!< 每个通道拥有64个字的内存（1个字=4字节）*/
#define SOC_RMT_SUPPORT_RX_DEMODULATION (1)  /*!< 支持RX路径上的信号解调（即去除载波）*/
#define SOC_RMT_SUPPORT_TX_LOOP_COUNT   (1)  /*!< 支持在循环模式下传输指定的循环数*/
#define SOC_RMT_SUPPORT_TX_SYNCHRO      (1)  /*!< 支持协调一组TX信道同时启动*/
#define SOC_RMT_SUPPORT_REF_TICK        (1)  /*!< 支持将REF_TICK设置为RMT时钟源*/
#define SOC_RMT_CHANNEL_CLK_INDEPENDENT (1)  /*!< 可以为每个通道选择不同的源时钟*/

/*-------------------------- RTCIO CAPS --------------------------------------*/
#define SOC_RTCIO_PIN_COUNT   22
#define SOC_RTCIO_INPUT_OUTPUT_SUPPORTED 1
#define SOC_RTCIO_HOLD_SUPPORTED 1
#define SOC_RTCIO_WAKE_SUPPORTED 1


/*-------------------------- SIGMA DELTA CAPS --------------------------------*/
#define SOC_SIGMADELTA_NUM            1
#define SOC_SIGMADELTA_CHANNEL_NUM (8) // 8个通道

/*-------------------------- SPI CAPS ----------------------------------------*/
#define SOC_SPI_PERIPH_NUM      3
#define SOC_SPI_DMA_CHAN_NUM    3
#define SOC_SPI_PERIPH_CS_NUM(i)    (((i)==0)? 2: (((i)==1)? 6: 3))

#define SOC_SPI_MAXIMUM_BUFFER_SIZE     72
#define SOC_SPI_MAX_PRE_DIVIDER         8192

//#定义SOC_SPI_SUPPORT_AS_CS//不支持在时钟切换时切换CS
#define SOC_SPI_SUPPORT_DDRCLK              1
#define SOC_SPI_SLAVE_SUPPORT_SEG_TRANS     1
#define SOC_SPI_SUPPORT_CD_SIG              1
#define SOC_SPI_SUPPORT_CONTINUOUS_TRANS    1
///ESP32-S2中的SPI从站半双工模式已进行了大幅更新
#define SOC_SPI_SUPPORT_SLAVE_HD_VER2       1

// 外围设备支持DIO、DOUT、QIO或QOUT
// VSPI（SPI3）仅支持1位模式
#define SOC_SPI_PERIPH_SUPPORT_MULTILINE_MODE(host_id)          ((host_id) != 2)

// 外围设备在其“虚拟阶段”支持输出给定电平
// 只有SPI1支持此功能
#define SOC_SPI_PERIPH_SUPPORT_CONTROL_DUMMY_OUTPUT             1

#define SOC_MEMSPI_IS_INDEPENDENT 1
#define SOC_SPI_SUPPORT_OCT 1

/*-------------------------- SYSTIMER CAPS ----------------------------------*/
#define SOC_SYSTIMER_COUNTER_NUM  (1)  // 计数器单元数量
#define SOC_SYSTIMER_ALARM_NUM    (3)  // 报警单元数量
#define SOC_SYSTIMER_BIT_WIDTH_LO (32) // 系统下部钻头宽度
#define SOC_SYSTIMER_BIT_WIDTH_HI (32) // 系统高位部分的位宽

/*-------------------------- TIMER GROUP CAPS --------------------------------*/
#define SOC_TIMER_GROUP_COUNTER_BIT_WIDTH (64)
#define SOC_TIMER_GROUPS                  (2)
#define SOC_TIMER_GROUP_TIMERS_PER_GROUP  (2)
#define SOC_TIMER_GROUP_SUPPORT_XTAL      (1)
#define SOC_TIMER_GROUP_TOTAL_TIMERS (SOC_TIMER_GROUPS * SOC_TIMER_GROUP_TIMERS_PER_GROUP)

/*-------------------------- TOUCH SENSOR CAPS -------------------------------*/
#define SOC_TOUCH_VERSION_2                 (1)     /*!<触摸传感器的硬件版本*/
#define SOC_TOUCH_SENSOR_NUM                (15)    /*!<15个触摸通道*/
#define SOC_TOUCH_PROXIMITY_CHANNEL_NUM     (3)     /* Sopport触摸接近通道编号。*/

#define SOC_TOUCH_PAD_THRESHOLD_MAX         (0x1FFFFF)  /*!<如果设置了触摸阈值最大值，则触摸传感器不能处于触摸状态*/
#define SOC_TOUCH_PAD_MEASURE_WAIT_MAX      (0xFF)  /*!<定时器频率为8Mhz，最大值为0xff*/

/*-------------------------- TWAI CAPS ---------------------------------------*/
#define SOC_TWAI_BRP_MIN                2
#define SOC_TWAI_BRP_MAX                32768
#define SOC_TWAI_SUPPORTS_RX_STATUS     1

/*-------------------------- UART CAPS ---------------------------------------*/
// ESP32-S2具有2个UART。
#define SOC_UART_NUM                (2)
#define SOC_UART_SUPPORT_REF_TICK   (1)         /*!< 支持REF_TICK作为时钟源*/
#define SOC_UART_FIFO_LEN           (128)       /*!< UART硬件FIFO长度*/
#define SOC_UART_BITRATE_MAX        (5000000)   /*!< UART支持的最大比特率*/

/*-------------------------- SPIRAM CAPS -------------------------------------*/
#define SOC_SPIRAM_SUPPORTED    1

/*-------------------------- USB CAPS ----------------------------------------*/
#define SOC_USB_PERIPH_NUM 1


/*--------------------------- SHA CAPS ---------------------------------------*/
/* 单个DMA操作中的最大字节数为4095，对于SHA，这意味着最大的安全字节数为31个128字节的块=3968
*/
#define SOC_SHA_DMA_MAX_BUFFER_SIZE     (3968)
#define SOC_SHA_SUPPORT_DMA             (1)

/* SHA引擎能够从用户提供的上下文恢复哈希*/
#define SOC_SHA_SUPPORT_RESUME          (1)

/* 具有与AES共享的“加密DMA”*/
#define SOC_SHA_CRYPTO_DMA              (1)

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

/* 支持的硬件算法*/
#define SOC_SHA_SUPPORT_SHA1            (1)
#define SOC_SHA_SUPPORT_SHA256          (1)
#define SOC_SHA_SUPPORT_SHA384          (1)
#define SOC_SHA_SUPPORT_SHA512          (1)


/*--------------------------- RSA CAPS ---------------------------------------*/
#define SOC_RSA_MAX_BIT_LEN    (4096)


/*-------------------------- AES CAPS -----------------------------------------*/
#define SOC_AES_SUPPORT_DMA     (1)
#define SOC_AES_SUPPORT_GCM     (1)

/*--------------------------闪存加密CAPS----------------------------*/
#define SOC_FLASH_ENCRYPTED_XTS_AES_BLOCK_MAX   (64)

/* 具有与SHA共享的“加密DMA”*/
#define SOC_AES_CRYPTO_DMA      (1)

#define SOC_AES_SUPPORT_AES_128 (1)
#define SOC_AES_SUPPORT_AES_192 (1)
#define SOC_AES_SUPPORT_AES_256 (1)

/*-------------------------- WI-FI HARDWARE TSF CAPS -------------------------------*/
#define SOC_WIFI_HW_TSF                 (1)

/*--------------- PHY REGISTER AND MEMORY SIZE CAPS --------------------------*/
#define SOC_PHY_DIG_REGS_MEM_SIZE       (21*4)

/*--------------- WIFI LIGHT SLEEP CLOCK WIDTH CAPS --------------------------*/
#define SOC_WIFI_LIGHT_SLEEP_CLK_WIDTH  (12)

/*-------------------------- SPI MEM CAPS ---------------------------------------*/
#define SOC_SPI_MEM_SUPPORT_AUTO_WAIT_IDLE                (1)
#define SOC_SPI_MEM_SUPPORT_AUTO_SUSPEND                  (1)
#define SOC_SPI_MEM_SUPPORT_SW_SUSPEND                    (1)
/*--------------------------电源管理CAPS---------------------------*/
#define SOC_PM_SUPPORT_EXT_WAKEUP       (1)

#define SOC_PM_SUPPORT_WIFI_WAKEUP      (1)

#define SOC_PM_SUPPORT_WIFI_PD          (1)

#define SOC_PM_SUPPORT_TOUCH_SENSOR_WAKEUP        (1)     /*!<支持从触摸板触发唤醒*/

/*-------------------------- COEXISTENCE HARDWARE PTI CAPS -------------------------------*/
#define SOC_COEX_HW_PTI                 (1)
/* ----------------------------兼容性------------------------------*/
// 无内容

