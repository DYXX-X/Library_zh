// 长期计划是拥有一个单一的soc_caps。h表示每个外围设备。
// 在重构和多芯片支持开发过程中，我们
// 将这些信息分离为peripher_caps。每个外围设备和
// 在这里包括它们。

#pragma once

#define SOC_CPU_CORES_NUM               1
#define SOC_ADC_SUPPORTED               1
#define SOC_DEDICATED_GPIO_SUPPORTED    1
#define SOC_GDMA_SUPPORTED              1
#define SOC_TWAI_SUPPORTED              1
#define SOC_BT_SUPPORTED                1
#define SOC_DIG_SIGN_SUPPORTED          1
#define SOC_HMAC_SUPPORTED              1
#define SOC_ASYNC_MEMCPY_SUPPORTED      1
#define SOC_USB_SERIAL_JTAG_SUPPORTED   1

/*-------------------------- COMMON CAPS ---------------------------------------*/
#define SOC_SUPPORTS_SECURE_DL_MODE         1
#define SOC_EFUSE_SECURE_BOOT_KEY_DIGESTS   3
#define SOC_TEMP_SENSOR_SUPPORTED           1


/*-------------------------- AES CAPS -----------------------------------------*/
#define SOC_AES_SUPPORT_DMA     (1)

/* 具有与所有外围设备共享的集中式DMA*/
#define SOC_AES_GDMA            (1)

#define SOC_AES_SUPPORT_AES_128 (1)
#define SOC_AES_SUPPORT_AES_256 (1)

/*-------------------------- ADC CAPS -------------------------------*/
/*!< SAR ADC模块*/
#define SOC_ADC_DIG_CTRL_SUPPORTED              1
#define SOC_ADC_ARBITER_SUPPORTED               1
#define SOC_ADC_FILTER_SUPPORTED                1
#define SOC_ADC_MONITOR_SUPPORTED               1
#define SOC_ADC_PERIPH_NUM                      (2)
#define SOC_ADC_CHANNEL_NUM(PERIPH_NUM)         ((PERIPH_NUM==0)? 5 : 1)
#define SOC_ADC_MAX_CHANNEL_NUM                 (5)

/*!< 数字的*/
#define SOC_ADC_DIGI_CONTROLLER_NUM             (1U)
#define SOC_ADC_PATT_LEN_MAX                    (8) /*!< 一个模式表，每个包含8项。每个项目占用1个字节*/
#define SOC_ADC_DIGI_MAX_BITWIDTH               (12)
#define SOC_ADC_DIGI_FILTER_NUM                 (2)
#define SOC_ADC_DIGI_MONITOR_NUM                (2)
/*!< F_sample=F_digi_con/2/间隔。F_digi_con=5M。30<=间隔<=4095*/
#define SOC_ADC_SAMPLE_FREQ_THRES_HIGH          83333
#define SOC_ADC_SAMPLE_FREQ_THRES_LOW           611

/*!< RTC */
#define SOC_ADC_MAX_BITWIDTH                    (12)


/*-------------------------- APB BACKUP DMA CAPS -------------------------------*/
#define SOC_APB_BACKUP_DMA              (1)

/*-------------------------- BROWNOUT CAPS -----------------------------------*/
#define SOC_BROWNOUT_RESET_SUPPORTED 1

/*-------------------------- CPU CAPS ----------------------------------------*/
#define SOC_CPU_BREAKPOINTS_NUM         8
#define SOC_CPU_WATCHPOINTS_NUM         8
#define SOC_CPU_HAS_FLEXIBLE_INTC       1

#define SOC_CPU_WATCHPOINT_SIZE         0x80000000 // 字节

/*-------------------------- DIGITAL SIGNATURE CAPS ----------------------------------------*/
/**数字签名的最大长度（以位为单位）。*/
#define SOC_DS_SIGNATURE_MAX_BIT_LEN (3072)

/**RSA密钥参数消息摘要（MD）的初始化向量（IV）长度（字节）。*/
#define SOC_DS_KEY_PARAM_MD_IV_LENGTH (16)

/**DS参数解密密钥的最长等待时间。如果过期，则键入错误。详见TRM DS章节*/
#define SOC_DS_KEY_CHECK_MAX_WAIT_US (1100)

/*-------------------------- GDMA CAPS -------------------------------------*/
#define SOC_GDMA_GROUPS                 (1) // GDMA组数
#define SOC_GDMA_PAIRS_PER_GROUP        (3) // 每组GDMA对数
#define SOC_GDMA_TX_RX_SHARE_INTERRUPT  (1) // 同一对中的TX和RX信道将共享相同的中断源编号

/*-------------------------- GPIO CAPS ---------------------------------------*/
// ESP32-C3具有1个GPIO外围设备
#define SOC_GPIO_PORT               (1)
#define SOC_GPIO_PIN_COUNT          (22)

// 目标没有完整的RTC IO子系统，因此GPIO 100%“独立”于RTC
// 在ESP32-C3上，数字IO有自己的寄存器来控制上拉/下拉功能，独立于RTC寄存器。
#define GPIO_SUPPORTS_RTC_INDEPENDENT       (1)
// 力保持是ESP32-C3的新功能
#define SOC_GPIO_SUPPORT_FORCE_HOLD         (1)
// ESP32C3上的GPIO0~5可支持芯片深度睡眠唤醒
#define SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP   (1)

#define SOC_GPIO_VALID_GPIO_MASK        ((1U<<SOC_GPIO_PIN_COUNT) - 1)
#define SOC_GPIO_VALID_OUTPUT_GPIO_MASK SOC_GPIO_VALID_GPIO_MASK
#define SOC_GPIO_DEEP_SLEEP_WAKEUP_VALID_GPIO_MASK        (0ULL | BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5)

// 支持配置睡眠状态
#define SOC_GPIO_SUPPORT_SLP_SWITCH  (1)

/*--------------------------专用GPIO CAPS-----------------------------*/
#define SOC_DEDIC_GPIO_OUT_CHANNELS_NUM (8) /*!< 每个CPU核心上有8个向外通道*/
#define SOC_DEDIC_GPIO_IN_CHANNELS_NUM  (8) /*!< 每个CPU核心上有8个向内通道*/
#define SOC_DEDIC_PERIPH_AUTO_ENABLE    (1) /*!< 专用GPIO外设自动启用*/

/*-------------------------- I2C CAPS ----------------------------------------*/
// ESP32-C3具有2个I2C。
#define SOC_I2C_NUM                 (1)

#define SOC_I2C_FIFO_LEN            (32) /*!< I2C硬件FIFO深度*/

#define SOC_I2C_SUPPORT_HW_FSM_RST  (1)
#define SOC_I2C_SUPPORT_HW_CLR_BUS  (1)

#define SOC_I2C_SUPPORT_XTAL        (1)
#define SOC_I2C_SUPPORT_RTC         (1)

/*-------------------------- I2S CAPS ----------------------------------------*/
#define SOC_I2S_NUM                 (1)
#define SOC_I2S_SUPPORTS_PCM        (1)
#define SOC_I2S_SUPPORTS_PDM_TX     (1)
#define SOC_I2S_SUPPORTS_PDM_CODEC  (1)
#define SOC_I2S_SUPPORTS_TDM        (1)

/*-------------------------- LEDC CAPS ---------------------------------------*/
#define SOC_LEDC_SUPPORT_XTAL_CLOCK  (1)
#define SOC_LEDC_CHANNEL_NUM         (6)
#define SOC_LEDC_TIMER_BIT_WIDE_NUM  (14)

/*-------------------------- MPU CAPS ----------------------------------------*/
#define SOC_MPU_CONFIGURABLE_REGIONS_SUPPORTED    0
#define SOC_MPU_MIN_REGION_SIZE                   0x20000000U
#define SOC_MPU_REGIONS_MAX_NUM                   8
#define SOC_MPU_REGION_RO_SUPPORTED               0
#define SOC_MPU_REGION_WO_SUPPORTED               0

/*--------------------------- RMT CAPS ---------------------------------------*/
#define SOC_RMT_GROUPS                  (1)  /*!< 一个RMT组*/
#define SOC_RMT_TX_CANDIDATES_PER_GROUP (2)  /*!< 能够传输的信道数*/
#define SOC_RMT_RX_CANDIDATES_PER_GROUP (2)  /*!< 能够接收的信道数*/
#define SOC_RMT_CHANNELS_PER_GROUP      (4)  /*!< 共4个通道*/
#define SOC_RMT_MEM_WORDS_PER_CHANNEL   (48) /*!< 每个通道拥有48个字的内存（1个字=4字节）*/
#define SOC_RMT_SUPPORT_RX_PINGPONG     (1)  /*!< 支持RX路径上的Ping Pong模式*/
#define SOC_RMT_SUPPORT_RX_DEMODULATION (1)  /*!< 支持RX路径上的信号解调（即去除载波）*/
#define SOC_RMT_SUPPORT_TX_LOOP_COUNT   (1)  /*!< 支持在循环模式下传输指定的循环数*/
#define SOC_RMT_SUPPORT_TX_SYNCHRO      (1)  /*!< 支持协调一组TX信道同时启动*/
#define SOC_RMT_SUPPORT_XTAL            (1)  /*!< 支持将XTAL时钟设置为RMT时钟源*/

/*-------------------------- RTC CAPS --------------------------------------*/
#define SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH       (128)
#define SOC_RTC_CNTL_CPU_PD_REG_FILE_NUM        (108)
#define SOC_RTC_CNTL_CPU_PD_DMA_ADDR_ALIGN      (SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH >> 3)
#define SOC_RTC_CNTL_CPU_PD_DMA_BLOCK_SIZE      (SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH >> 3)

#define SOC_RTC_CNTL_CPU_PD_RETENTION_MEM_SIZE  (SOC_RTC_CNTL_CPU_PD_REG_FILE_NUM * (SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH >> 3))

/*-------------------------- RTCIO CAPS --------------------------------------*/
/* ESP32-C3上没有专用的RTCIO子系统。保持、唤醒和32kHz晶体功能仍然支持RTC功能-通过RTC_cntl_reg*/
#define SOC_RTCIO_PIN_COUNT    (0U)

/*--------------------------- RSA CAPS ---------------------------------------*/
#define SOC_RSA_MAX_BIT_LEN    (3072)

/*--------------------------- SHA CAPS ---------------------------------------*/

/* 单个DMA操作中的最大字节数为4095，对于SHA，这意味着最大的安全字节数为31个128字节的块=3968
*/
#define SOC_SHA_DMA_MAX_BUFFER_SIZE     (3968)
#define SOC_SHA_SUPPORT_DMA             (1)

/* SHA引擎能够从用户恢复哈希*/
#define SOC_SHA_SUPPORT_RESUME          (1)

/* 具有与所有外围设备共享的集中式DMA*/
#define SOC_SHA_GDMA             (1)

/* 支持的硬件算法*/
#define SOC_SHA_SUPPORT_SHA1            (1)
#define SOC_SHA_SUPPORT_SHA224          (1)
#define SOC_SHA_SUPPORT_SHA256          (1)

/*-------------------------- SIGMA DELTA CAPS --------------------------------*/
#define SOC_SIGMADELTA_NUM         (1) // 1 sigma delta外围
#define SOC_SIGMADELTA_CHANNEL_NUM (4) // 4个通道

/*-------------------------- SPI CAPS ----------------------------------------*/
#define SOC_SPI_PERIPH_NUM          2
#define SOC_SPI_PERIPH_CS_NUM(i)    6

#define SOC_SPI_MAXIMUM_BUFFER_SIZE     64

#define SOC_SPI_SUPPORT_DDRCLK              1
#define SOC_SPI_SLAVE_SUPPORT_SEG_TRANS     1
#define SOC_SPI_SUPPORT_CD_SIG              1
#define SOC_SPI_SUPPORT_CONTINUOUS_TRANS    1
#define SOC_SPI_SUPPORT_SLAVE_HD_VER2       1

// 外围设备支持DIO、DOUT、QIO或QOUT
// host_id＝0->SPI0/SPI1、host_id=1->SPI2，
#define SOC_SPI_PERIPH_SUPPORT_MULTILINE_MODE(host_id)  ({(void)host_id; 1;})

// 外围设备在其“虚拟阶段”支持输出给定电平
#define SOC_SPI_PERIPH_SUPPORT_CONTROL_DUMMY_OUTPUT 1

#define SOC_MEMSPI_IS_INDEPENDENT 1
#define SOC_SPI_MAX_PRE_DIVIDER 16

/*-------------------------- SPI MEM CAPS ---------------------------------------*/
#define SOC_SPI_MEM_SUPPORT_AUTO_WAIT_IDLE                (1)
#define SOC_SPI_MEM_SUPPORT_AUTO_SUSPEND                  (1)
#define SOC_SPI_MEM_SUPPORT_AUTO_RESUME                   (1)
#define SOC_SPI_MEM_SUPPORT_IDLE_INTR                     (1)
#define SOC_SPI_MEM_SUPPORT_SW_SUSPEND                    (1)
#define SOC_SPI_MEM_SUPPORT_CHECK_SUS                     (1)


/*-------------------------- SYSTIMER CAPS ----------------------------------*/
#define SOC_SYSTIMER_COUNTER_NUM           (2)  // 计数器单元数量
#define SOC_SYSTIMER_ALARM_NUM             (3)  // 报警单元数量
#define SOC_SYSTIMER_BIT_WIDTH_LO          (32) // 系统下部钻头宽度
#define SOC_SYSTIMER_BIT_WIDTH_HI          (20) // 系统高位部分的位宽
#define SOC_SYSTIMER_FIXED_TICKS_US        (16) // 每微秒的滴答数是固定的
#define SOC_SYSTIMER_INT_LEVEL             (1)  // Systimer外设使用电平中断
#define SOC_SYSTIMER_ALARM_MISS_COMPENSATE (1)  // 如果t（目标）>t（当前），Systimer外设可以立即生成中断

/*--------------------------- TIMER GROUP CAPS ---------------------------------------*/
#define SOC_TIMER_GROUPS                  (2)
#define SOC_TIMER_GROUP_TIMERS_PER_GROUP  (1)
#define SOC_TIMER_GROUP_COUNTER_BIT_WIDTH (54)
#define SOC_TIMER_GROUP_SUPPORT_XTAL      (1)
#define SOC_TIMER_GROUP_TOTAL_TIMERS (SOC_TIMER_GROUPS * SOC_TIMER_GROUP_TIMERS_PER_GROUP)

/*-------------------------- TOUCH SENSOR CAPS -------------------------------*/
#define SOC_TOUCH_SENSOR_NUM            (0)    /*! ESP32-C3上无触摸传感器*/

/*-------------------------- TWAI CAPS ---------------------------------------*/
#define SOC_TWAI_BRP_MIN                2
#define SOC_TWAI_BRP_MAX                16384
#define SOC_TWAI_SUPPORTS_RX_STATUS     1

/*--------------------------闪存加密CAPS----------------------------*/
#define SOC_FLASH_ENCRYPTED_XTS_AES_BLOCK_MAX   (32)

/*-------------------------- UART CAPS ---------------------------------------*/
// ESP32-H2有2个UART
#define SOC_UART_NUM                (2)
#define SOC_UART_FIFO_LEN           (128)      /*!< UART硬件FIFO长度*/
#define SOC_UART_BITRATE_MAX        (5000000)  /*!< UART支持的最大比特率*/

#define SOC_UART_SUPPORT_RTC_CLK    (1)
#define SOC_UART_SUPPORT_XTAL_CLK   (1)

// 当FIFO不为空且启用XOFF时，UART具有额外的TX_WAIT_END状态
#define SOC_UART_SUPPORT_FSM_TX_WAIT_SEND   (1)

/*-------------------------- COEXISTENCE HARDWARE PTI CAPS -------------------------------*/
#define SOC_COEX_HW_PTI                 (1)

/*--------------- PHY REGISTER AND MEMORY SIZE CAPS --------------------------*/
#define SOC_PHY_DIG_REGS_MEM_SIZE       (21*4)
#define SOC_MAC_BB_PD_MEM_SIZE          (192*4)

/*--------------------------电源管理CAPS----------------------------*/

#define SOC_PM_SUPPORT_BT_WAKEUP        (1)

#define SOC_PM_SUPPORT_CPU_PD           (1)

#define SOC_PM_SUPPORT_BT_PD            (1)

