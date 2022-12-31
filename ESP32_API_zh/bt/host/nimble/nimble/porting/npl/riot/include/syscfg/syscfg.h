/**
 * 此文件由Apache newt版本1.8.0-dev生成
 */

#ifndef H_MYNEWT_SYSCFG_
#define H_MYNEWT_SYSCFG_

/**
 * 此宏的存在是为了确保代码在需要时包含此标头。如果代码通过ifdef直接检查设置是否存在，而不包含此标头，则设置宏将自动求值为0。相反，尝试使用这些宏而不包含该标头将导致编译器错误。
 */
#define MYNEWT_VAL(_name)                       MYNEWT_VAL_ ## _name
#define MYNEWT_VAL_CHOICE(_name, _val)          MYNEWT_VAL_ ## _name ## __ ## _val



/***@apachemynewt核心/编译器/arm-none-eabi-m4*/
#ifndef MYNEWT_VAL_HARDFLOAT
#define MYNEWT_VAL_HARDFLOAT (0)
#endif

/***@apache mynewt核心/hw/bsp/nordic_pca10056*/
#ifndef MYNEWT_VAL_BSP_NRF52840
#define MYNEWT_VAL_BSP_NRF52840 (1)
#endif

#ifndef MYNEWT_VAL_SOFT_PWM
#define MYNEWT_VAL_SOFT_PWM (0)
#endif

/***@apache mynewt核心/hw/hal*/
#ifndef MYNEWT_VAL_HAL_ENABLE_SOFTWARE_BREAKPOINTS
#define MYNEWT_VAL_HAL_ENABLE_SOFTWARE_BREAKPOINTS (1)
#endif

#ifndef MYNEWT_VAL_HAL_FLASH_VERIFY_BUF_SZ
#define MYNEWT_VAL_HAL_FLASH_VERIFY_BUF_SZ (16)
#endif

#ifndef MYNEWT_VAL_HAL_FLASH_VERIFY_ERASES
#define MYNEWT_VAL_HAL_FLASH_VERIFY_ERASES (0)
#endif

#ifndef MYNEWT_VAL_HAL_FLASH_VERIFY_WRITES
#define MYNEWT_VAL_HAL_FLASH_VERIFY_WRITES (0)
#endif

#ifndef MYNEWT_VAL_HAL_SYSTEM_RESET_CB
#define MYNEWT_VAL_HAL_SYSTEM_RESET_CB (0)
#endif

/***@apachemynewt核心/hw/mcu/nordic/nrf52xxx*/
#ifndef MYNEWT_VAL_ADC_0
#define MYNEWT_VAL_ADC_0 (0)
#endif

#ifndef MYNEWT_VAL_ADC_0_REFMV_0
#define MYNEWT_VAL_ADC_0_REFMV_0 (0)
#endif

#ifndef MYNEWT_VAL_CRYPTO
#define MYNEWT_VAL_CRYPTO (0)
#endif

#ifndef MYNEWT_VAL_GPIO_AS_PIN_RESET
#define MYNEWT_VAL_GPIO_AS_PIN_RESET (0)
#endif

#ifndef MYNEWT_VAL_I2C_0
#define MYNEWT_VAL_I2C_0 (0)
#endif

#ifndef MYNEWT_VAL_I2C_0_FREQ_KHZ
#define MYNEWT_VAL_I2C_0_FREQ_KHZ (100)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_I2C_0_PIN_SCL
#define MYNEWT_VAL_I2C_0_PIN_SCL (27)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_I2C_0_PIN_SDA
#define MYNEWT_VAL_I2C_0_PIN_SDA (26)
#endif

#ifndef MYNEWT_VAL_I2C_1
#define MYNEWT_VAL_I2C_1 (0)
#endif

#ifndef MYNEWT_VAL_I2C_1_FREQ_KHZ
#define MYNEWT_VAL_I2C_1_FREQ_KHZ (100)
#endif

#undef MYNEWT_VAL_I2C_1_PIN_SCL

#undef MYNEWT_VAL_I2C_1_PIN_SDA

#ifndef MYNEWT_VAL_MCU_BUS_DRIVER_I2C_USE_TWIM
#define MYNEWT_VAL_MCU_BUS_DRIVER_I2C_USE_TWIM (0)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_MCU_DCDC_ENABLED
#define MYNEWT_VAL_MCU_DCDC_ENABLED (1)
#endif

#ifndef MYNEWT_VAL_MCU_DEBUG_IGNORE_BKPT
#define MYNEWT_VAL_MCU_DEBUG_IGNORE_BKPT (0)
#endif

#ifndef MYNEWT_VAL_MCU_FLASH_MIN_WRITE_SIZE
#define MYNEWT_VAL_MCU_FLASH_MIN_WRITE_SIZE (1)
#endif

#ifndef MYNEWT_VAL_MCU_GPIO_USE_PORT_EVENT
#define MYNEWT_VAL_MCU_GPIO_USE_PORT_EVENT (0)
#endif

#ifndef MYNEWT_VAL_MCU_I2C_RECOVERY_DELAY_USEC
#define MYNEWT_VAL_MCU_I2C_RECOVERY_DELAY_USEC (100)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_MCU_LFCLK_SOURCE__LFRC
#define MYNEWT_VAL_MCU_LFCLK_SOURCE__LFRC (0)
#endif
#ifndef MYNEWT_VAL_MCU_LFCLK_SOURCE__LFSYNTH
#define MYNEWT_VAL_MCU_LFCLK_SOURCE__LFSYNTH (0)
#endif
#ifndef MYNEWT_VAL_MCU_LFCLK_SOURCE__LFXO
#define MYNEWT_VAL_MCU_LFCLK_SOURCE__LFXO (1)
#endif
#ifndef MYNEWT_VAL_MCU_LFCLK_SOURCE
#define MYNEWT_VAL_MCU_LFCLK_SOURCE (1)
#endif

#ifndef MYNEWT_VAL_MCU_NRF52832
#define MYNEWT_VAL_MCU_NRF52832 (0)
#endif

#ifndef MYNEWT_VAL_MCU_NRF52840
#define MYNEWT_VAL_MCU_NRF52840 (0)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_MCU_TARGET__nRF52810
#define MYNEWT_VAL_MCU_TARGET__nRF52810 (0)
#endif
#ifndef MYNEWT_VAL_MCU_TARGET__nRF52811
#define MYNEWT_VAL_MCU_TARGET__nRF52811 (0)
#endif
#ifndef MYNEWT_VAL_MCU_TARGET__nRF52832
#define MYNEWT_VAL_MCU_TARGET__nRF52832 (0)
#endif
#ifndef MYNEWT_VAL_MCU_TARGET__nRF52840
#define MYNEWT_VAL_MCU_TARGET__nRF52840 (1)
#endif
#ifndef MYNEWT_VAL_MCU_TARGET
#define MYNEWT_VAL_MCU_TARGET (1)
#endif

#ifndef MYNEWT_VAL_NFC_PINS_AS_GPIO
#define MYNEWT_VAL_NFC_PINS_AS_GPIO (1)
#endif

#ifndef MYNEWT_VAL_PWM_0
#define MYNEWT_VAL_PWM_0 (0)
#endif

#ifndef MYNEWT_VAL_PWM_1
#define MYNEWT_VAL_PWM_1 (0)
#endif

#ifndef MYNEWT_VAL_PWM_2
#define MYNEWT_VAL_PWM_2 (0)
#endif

#ifndef MYNEWT_VAL_PWM_3
#define MYNEWT_VAL_PWM_3 (0)
#endif

#ifndef MYNEWT_VAL_QSPI_ADDRMODE
#define MYNEWT_VAL_QSPI_ADDRMODE (0)
#endif

#ifndef MYNEWT_VAL_QSPI_DPMCONFIG
#define MYNEWT_VAL_QSPI_DPMCONFIG (0)
#endif

#ifndef MYNEWT_VAL_QSPI_ENABLE
#define MYNEWT_VAL_QSPI_ENABLE (0)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_QSPI_FLASH_PAGE_SIZE
#define MYNEWT_VAL_QSPI_FLASH_PAGE_SIZE (256)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_QSPI_FLASH_SECTOR_COUNT
#define MYNEWT_VAL_QSPI_FLASH_SECTOR_COUNT (4096)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_QSPI_FLASH_SECTOR_SIZE
#define MYNEWT_VAL_QSPI_FLASH_SECTOR_SIZE (4096)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_QSPI_PIN_CS
#define MYNEWT_VAL_QSPI_PIN_CS (17)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_QSPI_PIN_DIO0
#define MYNEWT_VAL_QSPI_PIN_DIO0 (20)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_QSPI_PIN_DIO1
#define MYNEWT_VAL_QSPI_PIN_DIO1 (21)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_QSPI_PIN_DIO2
#define MYNEWT_VAL_QSPI_PIN_DIO2 (22)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_QSPI_PIN_DIO3
#define MYNEWT_VAL_QSPI_PIN_DIO3 (23)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_QSPI_PIN_SCK
#define MYNEWT_VAL_QSPI_PIN_SCK (19)
#endif

#ifndef MYNEWT_VAL_QSPI_READOC
#define MYNEWT_VAL_QSPI_READOC (0)
#endif

#ifndef MYNEWT_VAL_QSPI_SCK_DELAY
#define MYNEWT_VAL_QSPI_SCK_DELAY (0)
#endif

#ifndef MYNEWT_VAL_QSPI_SCK_FREQ
#define MYNEWT_VAL_QSPI_SCK_FREQ (0)
#endif

#ifndef MYNEWT_VAL_QSPI_SPI_MODE
#define MYNEWT_VAL_QSPI_SPI_MODE (0)
#endif

#ifndef MYNEWT_VAL_QSPI_WRITEOC
#define MYNEWT_VAL_QSPI_WRITEOC (0)
#endif

#ifndef MYNEWT_VAL_SPI_0_MASTER
#define MYNEWT_VAL_SPI_0_MASTER (0)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_SPI_0_MASTER_PIN_MISO
#define MYNEWT_VAL_SPI_0_MASTER_PIN_MISO (47)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_SPI_0_MASTER_PIN_MOSI
#define MYNEWT_VAL_SPI_0_MASTER_PIN_MOSI (46)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_SPI_0_MASTER_PIN_SCK
#define MYNEWT_VAL_SPI_0_MASTER_PIN_SCK (45)
#endif

#ifndef MYNEWT_VAL_SPI_0_SLAVE
#define MYNEWT_VAL_SPI_0_SLAVE (0)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_SPI_0_SLAVE_PIN_MISO
#define MYNEWT_VAL_SPI_0_SLAVE_PIN_MISO (47)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_SPI_0_SLAVE_PIN_MOSI
#define MYNEWT_VAL_SPI_0_SLAVE_PIN_MOSI (46)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_SPI_0_SLAVE_PIN_SCK
#define MYNEWT_VAL_SPI_0_SLAVE_PIN_SCK (45)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_SPI_0_SLAVE_PIN_SS
#define MYNEWT_VAL_SPI_0_SLAVE_PIN_SS (44)
#endif

#ifndef MYNEWT_VAL_SPI_1_MASTER
#define MYNEWT_VAL_SPI_1_MASTER (0)
#endif

#undef MYNEWT_VAL_SPI_1_MASTER_PIN_MISO

#undef MYNEWT_VAL_SPI_1_MASTER_PIN_MOSI

#undef MYNEWT_VAL_SPI_1_MASTER_PIN_SCK

#ifndef MYNEWT_VAL_SPI_1_SLAVE
#define MYNEWT_VAL_SPI_1_SLAVE (0)
#endif

#undef MYNEWT_VAL_SPI_1_SLAVE_PIN_MISO

#undef MYNEWT_VAL_SPI_1_SLAVE_PIN_MOSI

#undef MYNEWT_VAL_SPI_1_SLAVE_PIN_SCK

#undef MYNEWT_VAL_SPI_1_SLAVE_PIN_SS

#ifndef MYNEWT_VAL_SPI_2_MASTER
#define MYNEWT_VAL_SPI_2_MASTER (0)
#endif

#undef MYNEWT_VAL_SPI_2_MASTER_PIN_MISO

#undef MYNEWT_VAL_SPI_2_MASTER_PIN_MOSI

#undef MYNEWT_VAL_SPI_2_MASTER_PIN_SCK

#ifndef MYNEWT_VAL_SPI_2_SLAVE
#define MYNEWT_VAL_SPI_2_SLAVE (0)
#endif

#undef MYNEWT_VAL_SPI_2_SLAVE_PIN_MISO

#undef MYNEWT_VAL_SPI_2_SLAVE_PIN_MOSI

#undef MYNEWT_VAL_SPI_2_SLAVE_PIN_SCK

#undef MYNEWT_VAL_SPI_2_SLAVE_PIN_SS

#ifndef MYNEWT_VAL_SPI_3_MASTER
#define MYNEWT_VAL_SPI_3_MASTER (0)
#endif

#undef MYNEWT_VAL_SPI_3_MASTER_PIN_MISO

#undef MYNEWT_VAL_SPI_3_MASTER_PIN_MOSI

#undef MYNEWT_VAL_SPI_3_MASTER_PIN_SCK

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_TIMER_0
#define MYNEWT_VAL_TIMER_0 (0)
#endif

#ifndef MYNEWT_VAL_TIMER_1
#define MYNEWT_VAL_TIMER_1 (0)
#endif

#ifndef MYNEWT_VAL_TIMER_2
#define MYNEWT_VAL_TIMER_2 (0)
#endif

#ifndef MYNEWT_VAL_TIMER_3
#define MYNEWT_VAL_TIMER_3 (0)
#endif

#ifndef MYNEWT_VAL_TIMER_4
#define MYNEWT_VAL_TIMER_4 (0)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_TIMER_5
#define MYNEWT_VAL_TIMER_5 (1)
#endif

#ifndef MYNEWT_VAL_TRNG
#define MYNEWT_VAL_TRNG (0)
#endif

#ifndef MYNEWT_VAL_UART_0
#define MYNEWT_VAL_UART_0 (1)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_UART_0_PIN_CTS
#define MYNEWT_VAL_UART_0_PIN_CTS (7)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_UART_0_PIN_RTS
#define MYNEWT_VAL_UART_0_PIN_RTS (5)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_UART_0_PIN_RX
#define MYNEWT_VAL_UART_0_PIN_RX (8)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt核心/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_UART_0_PIN_TX
#define MYNEWT_VAL_UART_0_PIN_TX (6)
#endif

#ifndef MYNEWT_VAL_UART_1
#define MYNEWT_VAL_UART_1 (0)
#endif

#ifndef MYNEWT_VAL_UART_1_PIN_CTS
#define MYNEWT_VAL_UART_1_PIN_CTS (-1)
#endif

#ifndef MYNEWT_VAL_UART_1_PIN_RTS
#define MYNEWT_VAL_UART_1_PIN_RTS (-1)
#endif

#undef MYNEWT_VAL_UART_1_PIN_RX

#undef MYNEWT_VAL_UART_1_PIN_TX

/* 被@apachemynewt flexim/targets/riot覆盖（由@apacheMynewt core/hw/mcu/nordic/nrf52xxx定义）*/
#ifndef MYNEWT_VAL_XTAL_32768
#define MYNEWT_VAL_XTAL_32768 (1)
#endif

#ifndef MYNEWT_VAL_XTAL_32768_SYNTH
#define MYNEWT_VAL_XTAL_32768_SYNTH (0)
#endif

#ifndef MYNEWT_VAL_XTAL_RC
#define MYNEWT_VAL_XTAL_RC (0)
#endif

/***@apachemynewt核心/内核/os*/
#ifndef MYNEWT_VAL_FLOAT_USER
#define MYNEWT_VAL_FLOAT_USER (0)
#endif

/* 被@apachemynewt-aging/targets/riot覆盖（由@apacheMynewt-core/kernel/os定义）*/
#ifndef MYNEWT_VAL_MSYS_1_BLOCK_COUNT
#define MYNEWT_VAL_MSYS_1_BLOCK_COUNT (5)
#endif

/* 被@apachemynewt-aging/targets/riot覆盖（由@apacheMynewt-core/kernel/os定义）*/
#ifndef MYNEWT_VAL_MSYS_1_BLOCK_SIZE
#define MYNEWT_VAL_MSYS_1_BLOCK_SIZE (88)
#endif

#ifndef MYNEWT_VAL_MSYS_1_SANITY_MIN_COUNT
#define MYNEWT_VAL_MSYS_1_SANITY_MIN_COUNT (0)
#endif

#ifndef MYNEWT_VAL_MSYS_2_BLOCK_COUNT
#define MYNEWT_VAL_MSYS_2_BLOCK_COUNT (0)
#endif

#ifndef MYNEWT_VAL_MSYS_2_BLOCK_SIZE
#define MYNEWT_VAL_MSYS_2_BLOCK_SIZE (0)
#endif

#ifndef MYNEWT_VAL_MSYS_2_SANITY_MIN_COUNT
#define MYNEWT_VAL_MSYS_2_SANITY_MIN_COUNT (0)
#endif

#ifndef MYNEWT_VAL_MSYS_SANITY_TIMEOUT
#define MYNEWT_VAL_MSYS_SANITY_TIMEOUT (60000)
#endif

#ifndef MYNEWT_VAL_OS_ASSERT_CB
#define MYNEWT_VAL_OS_ASSERT_CB (0)
#endif

#ifndef MYNEWT_VAL_OS_CLI
#define MYNEWT_VAL_OS_CLI (0)
#endif

#ifndef MYNEWT_VAL_OS_COREDUMP
#define MYNEWT_VAL_OS_COREDUMP (0)
#endif

/* 被@apachemynewt-core/hw/bsp/nordic_pca10056覆盖（由@apacheMynewt-core/kernel/os定义）*/
#ifndef MYNEWT_VAL_OS_CPUTIME_FREQ
#define MYNEWT_VAL_OS_CPUTIME_FREQ (32768)
#endif

/* 被@apachemynewt-core/hw/bsp/nordic_pca10056覆盖（由@apacheMynewt-core/kernel/os定义）*/
#ifndef MYNEWT_VAL_OS_CPUTIME_TIMER_NUM
#define MYNEWT_VAL_OS_CPUTIME_TIMER_NUM (5)
#endif

#ifndef MYNEWT_VAL_OS_CRASH_FILE_LINE
#define MYNEWT_VAL_OS_CRASH_FILE_LINE (0)
#endif

#ifndef MYNEWT_VAL_OS_CRASH_LOG
#define MYNEWT_VAL_OS_CRASH_LOG (0)
#endif

#ifndef MYNEWT_VAL_OS_CRASH_RESTORE_REGS
#define MYNEWT_VAL_OS_CRASH_RESTORE_REGS (0)
#endif

#ifndef MYNEWT_VAL_OS_CRASH_STACKTRACE
#define MYNEWT_VAL_OS_CRASH_STACKTRACE (0)
#endif

#ifndef MYNEWT_VAL_OS_CTX_SW_STACK_CHECK
#define MYNEWT_VAL_OS_CTX_SW_STACK_CHECK (0)
#endif

#ifndef MYNEWT_VAL_OS_CTX_SW_STACK_GUARD
#define MYNEWT_VAL_OS_CTX_SW_STACK_GUARD (4)
#endif

#ifndef MYNEWT_VAL_OS_DEBUG_MODE
#define MYNEWT_VAL_OS_DEBUG_MODE (0)
#endif

#ifndef MYNEWT_VAL_OS_EVENTQ_DEBUG
#define MYNEWT_VAL_OS_EVENTQ_DEBUG (0)
#endif

#ifndef MYNEWT_VAL_OS_EVENTQ_MONITOR
#define MYNEWT_VAL_OS_EVENTQ_MONITOR (0)
#endif

#ifndef MYNEWT_VAL_OS_IDLE_TICKLESS_MS_MAX
#define MYNEWT_VAL_OS_IDLE_TICKLESS_MS_MAX (600000)
#endif

#ifndef MYNEWT_VAL_OS_IDLE_TICKLESS_MS_MIN
#define MYNEWT_VAL_OS_IDLE_TICKLESS_MS_MIN (100)
#endif

#ifndef MYNEWT_VAL_OS_MAIN_STACK_SIZE
#define MYNEWT_VAL_OS_MAIN_STACK_SIZE (1024)
#endif

#ifndef MYNEWT_VAL_OS_MAIN_TASK_PRIO
#define MYNEWT_VAL_OS_MAIN_TASK_PRIO (127)
#endif

#ifndef MYNEWT_VAL_OS_MAIN_TASK_SANITY_ITVL_MS
#define MYNEWT_VAL_OS_MAIN_TASK_SANITY_ITVL_MS (0)
#endif

#ifndef MYNEWT_VAL_OS_MEMPOOL_CHECK
#define MYNEWT_VAL_OS_MEMPOOL_CHECK (0)
#endif

#ifndef MYNEWT_VAL_OS_MEMPOOL_GUARD
#define MYNEWT_VAL_OS_MEMPOOL_GUARD (0)
#endif

#ifndef MYNEWT_VAL_OS_MEMPOOL_POISON
#define MYNEWT_VAL_OS_MEMPOOL_POISON (0)
#endif

#ifndef MYNEWT_VAL_OS_SCHEDULING
#define MYNEWT_VAL_OS_SCHEDULING (1)
#endif

#ifndef MYNEWT_VAL_OS_SYSINIT_STAGE
#define MYNEWT_VAL_OS_SYSINIT_STAGE (0)
#endif

#ifndef MYNEWT_VAL_OS_SYSVIEW
#define MYNEWT_VAL_OS_SYSVIEW (0)
#endif

#ifndef MYNEWT_VAL_OS_SYSVIEW_TRACE_CALLOUT
#define MYNEWT_VAL_OS_SYSVIEW_TRACE_CALLOUT (1)
#endif

#ifndef MYNEWT_VAL_OS_SYSVIEW_TRACE_EVENTQ
#define MYNEWT_VAL_OS_SYSVIEW_TRACE_EVENTQ (1)
#endif

#ifndef MYNEWT_VAL_OS_SYSVIEW_TRACE_MBUF
#define MYNEWT_VAL_OS_SYSVIEW_TRACE_MBUF (0)
#endif

#ifndef MYNEWT_VAL_OS_SYSVIEW_TRACE_MEMPOOL
#define MYNEWT_VAL_OS_SYSVIEW_TRACE_MEMPOOL (0)
#endif

#ifndef MYNEWT_VAL_OS_SYSVIEW_TRACE_MUTEX
#define MYNEWT_VAL_OS_SYSVIEW_TRACE_MUTEX (1)
#endif

#ifndef MYNEWT_VAL_OS_SYSVIEW_TRACE_SEM
#define MYNEWT_VAL_OS_SYSVIEW_TRACE_SEM (1)
#endif

#ifndef MYNEWT_VAL_OS_TASK_RUN_TIME_CPUTIME
#define MYNEWT_VAL_OS_TASK_RUN_TIME_CPUTIME (0)
#endif

#ifndef MYNEWT_VAL_OS_TIME_DEBUG
#define MYNEWT_VAL_OS_TIME_DEBUG (0)
#endif

#ifndef MYNEWT_VAL_OS_WATCHDOG_MONITOR
#define MYNEWT_VAL_OS_WATCHDOG_MONITOR (0)
#endif

#ifndef MYNEWT_VAL_SANITY_INTERVAL
#define MYNEWT_VAL_SANITY_INTERVAL (15000)
#endif

#ifndef MYNEWT_VAL_WATCHDOG_INTERVAL
#define MYNEWT_VAL_WATCHDOG_INTERVAL (30000)
#endif

/***@apachemynewt核心/libc/baselibc*/
#ifndef MYNEWT_VAL_BASELIBC_ASSERT_FILE_LINE
#define MYNEWT_VAL_BASELIBC_ASSERT_FILE_LINE (0)
#endif

#ifndef MYNEWT_VAL_BASELIBC_PRESENT
#define MYNEWT_VAL_BASELIBC_PRESENT (1)
#endif

/***@apachemynewt核心/sys/console/stub*/
#ifndef MYNEWT_VAL_CONSOLE_UART_BAUD
#define MYNEWT_VAL_CONSOLE_UART_BAUD (115200)
#endif

#ifndef MYNEWT_VAL_CONSOLE_UART_DEV
#define MYNEWT_VAL_CONSOLE_UART_DEV ("uart0")
#endif

#ifndef MYNEWT_VAL_CONSOLE_UART_FLOW_CONTROL
#define MYNEWT_VAL_CONSOLE_UART_FLOW_CONTROL (UART_FLOW_CTL_NONE)
#endif

/***@apachemynewt核心/sys/flash_map*/
#ifndef MYNEWT_VAL_FLASH_MAP_MAX_AREAS
#define MYNEWT_VAL_FLASH_MAP_MAX_AREAS (10)
#endif

#ifndef MYNEWT_VAL_FLASH_MAP_SYSINIT_STAGE
#define MYNEWT_VAL_FLASH_MAP_SYSINIT_STAGE (2)
#endif

/***@apachemynewt核心/sys/log/common*/
#ifndef MYNEWT_VAL_DFLT_LOG_LVL
#define MYNEWT_VAL_DFLT_LOG_LVL (1)
#endif

#ifndef MYNEWT_VAL_DFLT_LOG_MOD
#define MYNEWT_VAL_DFLT_LOG_MOD (0)
#endif

#ifndef MYNEWT_VAL_LOG_GLOBAL_IDX
#define MYNEWT_VAL_LOG_GLOBAL_IDX (1)
#endif

/***@apachemynewt核心/sys/log/modlog*/
#ifndef MYNEWT_VAL_MODLOG_CONSOLE_DFLT
#define MYNEWT_VAL_MODLOG_CONSOLE_DFLT (1)
#endif

#ifndef MYNEWT_VAL_MODLOG_LOG_MACROS
#define MYNEWT_VAL_MODLOG_LOG_MACROS (0)
#endif

#ifndef MYNEWT_VAL_MODLOG_MAX_MAPPINGS
#define MYNEWT_VAL_MODLOG_MAX_MAPPINGS (16)
#endif

#ifndef MYNEWT_VAL_MODLOG_MAX_PRINTF_LEN
#define MYNEWT_VAL_MODLOG_MAX_PRINTF_LEN (128)
#endif

#ifndef MYNEWT_VAL_MODLOG_SYSINIT_STAGE
#define MYNEWT_VAL_MODLOG_SYSINIT_STAGE (100)
#endif

/***@apachemynewt核心/sys/log/stub*/
#ifndef MYNEWT_VAL_LOG_CONSOLE
#define MYNEWT_VAL_LOG_CONSOLE (1)
#endif

#ifndef MYNEWT_VAL_LOG_FCB
#define MYNEWT_VAL_LOG_FCB (0)
#endif

#ifndef MYNEWT_VAL_LOG_FCB_SLOT1
#define MYNEWT_VAL_LOG_FCB_SLOT1 (0)
#endif

#ifndef MYNEWT_VAL_LOG_LEVEL
#define MYNEWT_VAL_LOG_LEVEL (255)
#endif

/***@apachemynewt核心/sys/mfg*/
#ifndef MYNEWT_VAL_MFG_LOG_LVL
#define MYNEWT_VAL_MFG_LOG_LVL (15)
#endif

#ifndef MYNEWT_VAL_MFG_LOG_MODULE
#define MYNEWT_VAL_MFG_LOG_MODULE (128)
#endif

#ifndef MYNEWT_VAL_MFG_MAX_MMRS
#define MYNEWT_VAL_MFG_MAX_MMRS (2)
#endif

#ifndef MYNEWT_VAL_MFG_SYSINIT_STAGE
#define MYNEWT_VAL_MFG_SYSINIT_STAGE (100)
#endif

/***@apache mynewt核心/sys/sys*/
#ifndef MYNEWT_VAL_DEBUG_PANIC_ENABLED
#define MYNEWT_VAL_DEBUG_PANIC_ENABLED (1)
#endif

/***@apachemynewt核心/sys/sysdown*/
#ifndef MYNEWT_VAL_SYSDOWN_CONSTRAIN_DOWN
#define MYNEWT_VAL_SYSDOWN_CONSTRAIN_DOWN (1)
#endif

#ifndef MYNEWT_VAL_SYSDOWN_PANIC_FILE_LINE
#define MYNEWT_VAL_SYSDOWN_PANIC_FILE_LINE (0)
#endif

#ifndef MYNEWT_VAL_SYSDOWN_PANIC_MESSAGE
#define MYNEWT_VAL_SYSDOWN_PANIC_MESSAGE (0)
#endif

#ifndef MYNEWT_VAL_SYSDOWN_TIMEOUT_MS
#define MYNEWT_VAL_SYSDOWN_TIMEOUT_MS (10000)
#endif

/***@apachemynewt核心/sys/sysinit*/
#ifndef MYNEWT_VAL_SYSINIT_CONSTRAIN_INIT
#define MYNEWT_VAL_SYSINIT_CONSTRAIN_INIT (1)
#endif

#ifndef MYNEWT_VAL_SYSINIT_PANIC_FILE_LINE
#define MYNEWT_VAL_SYSINIT_PANIC_FILE_LINE (0)
#endif

#ifndef MYNEWT_VAL_SYSINIT_PANIC_MESSAGE
#define MYNEWT_VAL_SYSINIT_PANIC_MESSAGE (0)
#endif

/***@apache mynewt核心/util/rwblock*/
#ifndef MYNEWT_VAL_RWLOCK_DEBUG
#define MYNEWT_VAL_RWLOCK_DEBUG (0)
#endif

/***@apachemynewt敏捷/敏捷*/
#ifndef MYNEWT_VAL_BLE_EXT_ADV
#define MYNEWT_VAL_BLE_EXT_ADV (0)
#endif

#ifndef MYNEWT_VAL_BLE_EXT_ADV_MAX_SIZE
#define MYNEWT_VAL_BLE_EXT_ADV_MAX_SIZE (31)
#endif

#ifndef MYNEWT_VAL_BLE_MAX_CONNECTIONS
#define MYNEWT_VAL_BLE_MAX_CONNECTIONS (1)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animile定义）*/
#ifndef MYNEWT_VAL_BLE_MAX_PERIODIC_SYNCS
#define MYNEWT_VAL_BLE_MAX_PERIODIC_SYNCS (0)
#endif

#ifndef MYNEWT_VAL_BLE_MULTI_ADV_INSTANCES
#define MYNEWT_VAL_BLE_MULTI_ADV_INSTANCES (0)
#endif

#ifndef MYNEWT_VAL_BLE_PERIODIC_ADV
#define MYNEWT_VAL_BLE_PERIODIC_ADV (0)
#endif

#ifndef MYNEWT_VAL_BLE_PERIODIC_ADV_SYNC_TRANSFER
#define MYNEWT_VAL_BLE_PERIODIC_ADV_SYNC_TRANSFER (0)
#endif

#ifndef MYNEWT_VAL_BLE_ROLE_BROADCASTER
#define MYNEWT_VAL_BLE_ROLE_BROADCASTER (1)
#endif

#ifndef MYNEWT_VAL_BLE_ROLE_CENTRAL
#define MYNEWT_VAL_BLE_ROLE_CENTRAL (1)
#endif

#ifndef MYNEWT_VAL_BLE_ROLE_OBSERVER
#define MYNEWT_VAL_BLE_ROLE_OBSERVER (1)
#endif

#ifndef MYNEWT_VAL_BLE_ROLE_PERIPHERAL
#define MYNEWT_VAL_BLE_ROLE_PERIPHERAL (1)
#endif

#ifndef MYNEWT_VAL_BLE_VERSION
#define MYNEWT_VAL_BLE_VERSION (50)
#endif

#ifndef MYNEWT_VAL_BLE_WHITELIST
#define MYNEWT_VAL_BLE_WHITELIST (1)
#endif

/***@apachemynewt敏捷/敏捷/控制器*/
#ifndef MYNEWT_VAL_BLE_CONTROLLER
#define MYNEWT_VAL_BLE_CONTROLLER (1)
#endif

#ifndef MYNEWT_VAL_BLE_DEVICE
#define MYNEWT_VAL_BLE_DEVICE (1)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animic/controller定义）*/
#ifndef MYNEWT_VAL_BLE_HW_WHITELIST_ENABLE
#define MYNEWT_VAL_BLE_HW_WHITELIST_ENABLE (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_ADD_STRICT_SCHED_PERIODS
#define MYNEWT_VAL_BLE_LL_ADD_STRICT_SCHED_PERIODS (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_CONN_PARAM_REQ
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_CONN_PARAM_REQ (1)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animic/controller定义）*/
#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_DATA_LEN_EXT
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_DATA_LEN_EXT (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_2M_PHY
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_2M_PHY (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_CODED_PHY
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_CODED_PHY (0)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animic/controller定义）*/
#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_CSA2
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_CSA2 (1)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animic/controller定义）*/
#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_ENCRYPTION
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_ENCRYPTION (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_PING
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_PING (MYNEWT_VAL_BLE_LL_CFG_FEAT_LE_ENCRYPTION)
#endif

/* 从BLE_EXT_ADV复制的值*/
#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_EXT_ADV
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_EXT_ADV (0)
#endif

/* 从BLE_PERIODIC_ADV复制的值*/
#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_PERIODIC_ADV
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_PERIODIC_ADV (0)
#endif

/* 从BLE_MAX_PERIODIC_SYNCS复制的值*/
#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_PERIODIC_ADV_SYNC_CNT
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_PERIODIC_ADV_SYNC_CNT (0)
#endif

/* 从BLE_MAX_PERIODIC_SYNCS复制的值*/
#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_PERIODIC_ADV_SYNC_LIST_CNT
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_PERIODIC_ADV_SYNC_LIST_CNT (0)
#endif

/* 从BLE_PERIODIC_ADV_SYNC_TRANSFER复制的值*/
#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_PERIODIC_ADV_SYNC_TRANSFER
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_PERIODIC_ADV_SYNC_TRANSFER (0)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animic/controller定义）*/
#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_PRIVACY
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_LL_PRIVACY (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_CFG_FEAT_SLAVE_INIT_FEAT_XCHG
#define MYNEWT_VAL_BLE_LL_CFG_FEAT_SLAVE_INIT_FEAT_XCHG (1)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animic/controller定义）*/
#ifndef MYNEWT_VAL_BLE_LL_CONN_INIT_MAX_TX_BYTES
#define MYNEWT_VAL_BLE_LL_CONN_INIT_MAX_TX_BYTES (MYNEWT_VAL_BLE_LL_MAX_PKT_SIZE)
#endif

#ifndef MYNEWT_VAL_BLE_LL_CONN_INIT_MIN_WIN_OFFSET
#define MYNEWT_VAL_BLE_LL_CONN_INIT_MIN_WIN_OFFSET (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_CONN_INIT_SLOTS
#define MYNEWT_VAL_BLE_LL_CONN_INIT_SLOTS (4)
#endif

#ifndef MYNEWT_VAL_BLE_LL_DBG_HCI_CMD_PIN
#define MYNEWT_VAL_BLE_LL_DBG_HCI_CMD_PIN (-1)
#endif

#ifndef MYNEWT_VAL_BLE_LL_DBG_HCI_EV_PIN
#define MYNEWT_VAL_BLE_LL_DBG_HCI_EV_PIN (-1)
#endif

#ifndef MYNEWT_VAL_BLE_LL_DIRECT_TEST_MODE
#define MYNEWT_VAL_BLE_LL_DIRECT_TEST_MODE (0)
#endif

/* 从BLE_LL_DIRECT_TEST_MODE复制的值*/
#ifndef MYNEWT_VAL_BLE_LL_DTM
#define MYNEWT_VAL_BLE_LL_DTM (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_DTM_EXTENSIONS
#define MYNEWT_VAL_BLE_LL_DTM_EXTENSIONS (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_EXT_ADV_AUX_PTR_CNT
#define MYNEWT_VAL_BLE_LL_EXT_ADV_AUX_PTR_CNT (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_MASTER_SCA
#define MYNEWT_VAL_BLE_LL_MASTER_SCA (4)
#endif

#ifndef MYNEWT_VAL_BLE_LL_MAX_PKT_SIZE
#define MYNEWT_VAL_BLE_LL_MAX_PKT_SIZE (251)
#endif

#ifndef MYNEWT_VAL_BLE_LL_MFRG_ID
#define MYNEWT_VAL_BLE_LL_MFRG_ID (0xFFFF)
#endif

#ifndef MYNEWT_VAL_BLE_LL_NUM_COMP_PKT_ITVL_MS
#define MYNEWT_VAL_BLE_LL_NUM_COMP_PKT_ITVL_MS (2000)
#endif

#ifndef MYNEWT_VAL_BLE_LL_NUM_SCAN_DUP_ADVS
#define MYNEWT_VAL_BLE_LL_NUM_SCAN_DUP_ADVS (8)
#endif

#ifndef MYNEWT_VAL_BLE_LL_NUM_SCAN_RSP_ADVS
#define MYNEWT_VAL_BLE_LL_NUM_SCAN_RSP_ADVS (8)
#endif

#ifndef MYNEWT_VAL_BLE_LL_OUR_SCA
#define MYNEWT_VAL_BLE_LL_OUR_SCA (60)
#endif

#ifndef MYNEWT_VAL_BLE_LL_PRIO
#define MYNEWT_VAL_BLE_LL_PRIO (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_RESOLV_LIST_SIZE
#define MYNEWT_VAL_BLE_LL_RESOLV_LIST_SIZE (4)
#endif

/* 被@apache mynewt core/hw/bsp/nordic_pca10056覆盖（由@apache mynewt aging/animic/controller定义）*/
#ifndef MYNEWT_VAL_BLE_LL_RFMGMT_ENABLE_TIME
#define MYNEWT_VAL_BLE_LL_RFMGMT_ENABLE_TIME (1500)
#endif

#ifndef MYNEWT_VAL_BLE_LL_RNG_BUFSIZE
#define MYNEWT_VAL_BLE_LL_RNG_BUFSIZE (32)
#endif

#ifndef MYNEWT_VAL_BLE_LL_SCHED_AUX_CHAIN_MAFS_DELAY
#define MYNEWT_VAL_BLE_LL_SCHED_AUX_CHAIN_MAFS_DELAY (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_SCHED_AUX_MAFS_DELAY
#define MYNEWT_VAL_BLE_LL_SCHED_AUX_MAFS_DELAY (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_SCHED_SCAN_AUX_PDU_LEN
#define MYNEWT_VAL_BLE_LL_SCHED_SCAN_AUX_PDU_LEN (41)
#endif

#ifndef MYNEWT_VAL_BLE_LL_SCHED_SCAN_SYNC_PDU_LEN
#define MYNEWT_VAL_BLE_LL_SCHED_SCAN_SYNC_PDU_LEN (32)
#endif

#ifndef MYNEWT_VAL_BLE_LL_STRICT_CONN_SCHEDULING
#define MYNEWT_VAL_BLE_LL_STRICT_CONN_SCHEDULING (0)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animic/controller定义）*/
#ifndef MYNEWT_VAL_BLE_LL_SUPP_MAX_RX_BYTES
#define MYNEWT_VAL_BLE_LL_SUPP_MAX_RX_BYTES (MYNEWT_VAL_BLE_LL_MAX_PKT_SIZE)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animic/controller定义）*/
#ifndef MYNEWT_VAL_BLE_LL_SUPP_MAX_TX_BYTES
#define MYNEWT_VAL_BLE_LL_SUPP_MAX_TX_BYTES (MYNEWT_VAL_BLE_LL_MAX_PKT_SIZE)
#endif

#ifndef MYNEWT_VAL_BLE_LL_SYSINIT_STAGE
#define MYNEWT_VAL_BLE_LL_SYSINIT_STAGE (250)
#endif

#ifndef MYNEWT_VAL_BLE_LL_SYSVIEW
#define MYNEWT_VAL_BLE_LL_SYSVIEW (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_TX_PWR_DBM
#define MYNEWT_VAL_BLE_LL_TX_PWR_DBM (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_USECS_PER_PERIOD
#define MYNEWT_VAL_BLE_LL_USECS_PER_PERIOD (3250)
#endif

#ifndef MYNEWT_VAL_BLE_LL_VND_EVENT_ON_ASSERT
#define MYNEWT_VAL_BLE_LL_VND_EVENT_ON_ASSERT (0)
#endif

#ifndef MYNEWT_VAL_BLE_LL_WHITELIST_SIZE
#define MYNEWT_VAL_BLE_LL_WHITELIST_SIZE (8)
#endif

#ifndef MYNEWT_VAL_BLE_LP_CLOCK
#define MYNEWT_VAL_BLE_LP_CLOCK (1)
#endif

#ifndef MYNEWT_VAL_BLE_NUM_COMP_PKT_RATE
#define MYNEWT_VAL_BLE_NUM_COMP_PKT_RATE ((2 * OS_TICKS_PER_SEC))
#endif

#ifndef MYNEWT_VAL_BLE_PUBLIC_DEV_ADDR
#define MYNEWT_VAL_BLE_PUBLIC_DEV_ADDR ((uint8_t[6]){0x00, 0x00, 0x00, 0x00, 0x00, 0x00})
#endif

#ifndef MYNEWT_VAL_BLE_XTAL_SETTLE_TIME
#define MYNEWT_VAL_BLE_XTAL_SETTLE_TIME (0)
#endif

/***@apachemynewt敏捷/敏捷/驱动程序/nrf52*/
#ifndef MYNEWT_VAL_BLE_PHY_CODED_RX_IFS_EXTRA_MARGIN
#define MYNEWT_VAL_BLE_PHY_CODED_RX_IFS_EXTRA_MARGIN (0)
#endif

#ifndef MYNEWT_VAL_BLE_PHY_DBG_TIME_ADDRESS_END_PIN
#define MYNEWT_VAL_BLE_PHY_DBG_TIME_ADDRESS_END_PIN (-1)
#endif

#ifndef MYNEWT_VAL_BLE_PHY_DBG_TIME_TXRXEN_READY_PIN
#define MYNEWT_VAL_BLE_PHY_DBG_TIME_TXRXEN_READY_PIN (-1)
#endif

#ifndef MYNEWT_VAL_BLE_PHY_DBG_TIME_WFR_PIN
#define MYNEWT_VAL_BLE_PHY_DBG_TIME_WFR_PIN (-1)
#endif

#ifndef MYNEWT_VAL_BLE_PHY_NRF52840_ERRATA_164
#define MYNEWT_VAL_BLE_PHY_NRF52840_ERRATA_164 (0)
#endif

#ifndef MYNEWT_VAL_BLE_PHY_NRF52840_ERRATA_191
#define MYNEWT_VAL_BLE_PHY_NRF52840_ERRATA_191 (1)
#endif

#ifndef MYNEWT_VAL_BLE_PHY_SYSVIEW
#define MYNEWT_VAL_BLE_PHY_SYSVIEW (0)
#endif

/***@apachemynewt敏捷/敏捷/主机*/
#ifndef MYNEWT_VAL_BLE_ATT_PREFERRED_MTU
#define MYNEWT_VAL_BLE_ATT_PREFERRED_MTU (256)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_FIND_INFO
#define MYNEWT_VAL_BLE_ATT_SVR_FIND_INFO (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_FIND_TYPE
#define MYNEWT_VAL_BLE_ATT_SVR_FIND_TYPE (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_INDICATE
#define MYNEWT_VAL_BLE_ATT_SVR_INDICATE (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_MAX_PREP_ENTRIES
#define MYNEWT_VAL_BLE_ATT_SVR_MAX_PREP_ENTRIES (64)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_NOTIFY
#define MYNEWT_VAL_BLE_ATT_SVR_NOTIFY (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_QUEUED_WRITE
#define MYNEWT_VAL_BLE_ATT_SVR_QUEUED_WRITE (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_QUEUED_WRITE_TMO
#define MYNEWT_VAL_BLE_ATT_SVR_QUEUED_WRITE_TMO (30000)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_READ
#define MYNEWT_VAL_BLE_ATT_SVR_READ (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_READ_BLOB
#define MYNEWT_VAL_BLE_ATT_SVR_READ_BLOB (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_READ_GROUP_TYPE
#define MYNEWT_VAL_BLE_ATT_SVR_READ_GROUP_TYPE (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_READ_MULT
#define MYNEWT_VAL_BLE_ATT_SVR_READ_MULT (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_READ_TYPE
#define MYNEWT_VAL_BLE_ATT_SVR_READ_TYPE (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_SIGNED_WRITE
#define MYNEWT_VAL_BLE_ATT_SVR_SIGNED_WRITE (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_WRITE
#define MYNEWT_VAL_BLE_ATT_SVR_WRITE (1)
#endif

#ifndef MYNEWT_VAL_BLE_ATT_SVR_WRITE_NO_RSP
#define MYNEWT_VAL_BLE_ATT_SVR_WRITE_NO_RSP (1)
#endif

#ifndef MYNEWT_VAL_BLE_GAP_MAX_PENDING_CONN_PARAM_UPDATE
#define MYNEWT_VAL_BLE_GAP_MAX_PENDING_CONN_PARAM_UPDATE (1)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_DISC_ALL_CHRS
#define MYNEWT_VAL_BLE_GATT_DISC_ALL_CHRS (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_DISC_ALL_DSCS
#define MYNEWT_VAL_BLE_GATT_DISC_ALL_DSCS (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_DISC_ALL_SVCS
#define MYNEWT_VAL_BLE_GATT_DISC_ALL_SVCS (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_DISC_CHR_UUID
#define MYNEWT_VAL_BLE_GATT_DISC_CHR_UUID (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_DISC_SVC_UUID
#define MYNEWT_VAL_BLE_GATT_DISC_SVC_UUID (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_FIND_INC_SVCS
#define MYNEWT_VAL_BLE_GATT_FIND_INC_SVCS (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_INDICATE
#define MYNEWT_VAL_BLE_GATT_INDICATE (1)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_MAX_PROCS
#define MYNEWT_VAL_BLE_GATT_MAX_PROCS (4)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_NOTIFY
#define MYNEWT_VAL_BLE_GATT_NOTIFY (1)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_READ
#define MYNEWT_VAL_BLE_GATT_READ (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_READ_LONG
#define MYNEWT_VAL_BLE_GATT_READ_LONG (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_READ_MAX_ATTRS
#define MYNEWT_VAL_BLE_GATT_READ_MAX_ATTRS (8)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_READ_MULT
#define MYNEWT_VAL_BLE_GATT_READ_MULT (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_READ_UUID
#define MYNEWT_VAL_BLE_GATT_READ_UUID (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_RESUME_RATE
#define MYNEWT_VAL_BLE_GATT_RESUME_RATE (1000)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_SIGNED_WRITE
#define MYNEWT_VAL_BLE_GATT_SIGNED_WRITE (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_WRITE
#define MYNEWT_VAL_BLE_GATT_WRITE (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_WRITE_LONG
#define MYNEWT_VAL_BLE_GATT_WRITE_LONG (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_WRITE_MAX_ATTRS
#define MYNEWT_VAL_BLE_GATT_WRITE_MAX_ATTRS (4)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_WRITE_NO_RSP
#define MYNEWT_VAL_BLE_GATT_WRITE_NO_RSP (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_GATT_WRITE_RELIABLE
#define MYNEWT_VAL_BLE_GATT_WRITE_RELIABLE (MYNEWT_VAL_BLE_ROLE_CENTRAL)
#endif

#ifndef MYNEWT_VAL_BLE_HOST
#define MYNEWT_VAL_BLE_HOST (1)
#endif

#ifndef MYNEWT_VAL_BLE_HS_AUTO_START
#define MYNEWT_VAL_BLE_HS_AUTO_START (1)
#endif

#ifndef MYNEWT_VAL_BLE_HS_DEBUG
#define MYNEWT_VAL_BLE_HS_DEBUG (0)
#endif

#ifndef MYNEWT_VAL_BLE_HS_FLOW_CTRL
#define MYNEWT_VAL_BLE_HS_FLOW_CTRL (0)
#endif

#ifndef MYNEWT_VAL_BLE_HS_FLOW_CTRL_ITVL
#define MYNEWT_VAL_BLE_HS_FLOW_CTRL_ITVL (1000)
#endif

#ifndef MYNEWT_VAL_BLE_HS_FLOW_CTRL_THRESH
#define MYNEWT_VAL_BLE_HS_FLOW_CTRL_THRESH (2)
#endif

#ifndef MYNEWT_VAL_BLE_HS_FLOW_CTRL_TX_ON_DISCONNECT
#define MYNEWT_VAL_BLE_HS_FLOW_CTRL_TX_ON_DISCONNECT (0)
#endif

#ifndef MYNEWT_VAL_BLE_HS_LOG_LVL
#define MYNEWT_VAL_BLE_HS_LOG_LVL (1)
#endif

#ifndef MYNEWT_VAL_BLE_HS_LOG_MOD
#define MYNEWT_VAL_BLE_HS_LOG_MOD (4)
#endif

#ifndef MYNEWT_VAL_BLE_HS_PHONY_HCI_ACKS
#define MYNEWT_VAL_BLE_HS_PHONY_HCI_ACKS (0)
#endif

#ifndef MYNEWT_VAL_BLE_HS_REQUIRE_OS
#define MYNEWT_VAL_BLE_HS_REQUIRE_OS (1)
#endif

#ifndef MYNEWT_VAL_BLE_HS_STOP_ON_SHUTDOWN
#define MYNEWT_VAL_BLE_HS_STOP_ON_SHUTDOWN (1)
#endif

#ifndef MYNEWT_VAL_BLE_HS_STOP_ON_SHUTDOWN_TIMEOUT
#define MYNEWT_VAL_BLE_HS_STOP_ON_SHUTDOWN_TIMEOUT (2000)
#endif

#ifndef MYNEWT_VAL_BLE_HS_SYSINIT_STAGE
#define MYNEWT_VAL_BLE_HS_SYSINIT_STAGE (200)
#endif

#ifndef MYNEWT_VAL_BLE_L2CAP_COC_MAX_NUM
#define MYNEWT_VAL_BLE_L2CAP_COC_MAX_NUM (0)
#endif

#ifndef MYNEWT_VAL_BLE_L2CAP_COC_MPS
#define MYNEWT_VAL_BLE_L2CAP_COC_MPS (MYNEWT_VAL_MSYS_1_BLOCK_SIZE-8)
#endif

#ifndef MYNEWT_VAL_BLE_L2CAP_ENHANCED_COC
#define MYNEWT_VAL_BLE_L2CAP_ENHANCED_COC (0)
#endif

#ifndef MYNEWT_VAL_BLE_L2CAP_JOIN_RX_FRAGS
#define MYNEWT_VAL_BLE_L2CAP_JOIN_RX_FRAGS (1)
#endif

#ifndef MYNEWT_VAL_BLE_L2CAP_MAX_CHANS
#define MYNEWT_VAL_BLE_L2CAP_MAX_CHANS (3*MYNEWT_VAL_BLE_MAX_CONNECTIONS)
#endif

#ifndef MYNEWT_VAL_BLE_L2CAP_RX_FRAG_TIMEOUT
#define MYNEWT_VAL_BLE_L2CAP_RX_FRAG_TIMEOUT (30000)
#endif

#ifndef MYNEWT_VAL_BLE_L2CAP_SIG_MAX_PROCS
#define MYNEWT_VAL_BLE_L2CAP_SIG_MAX_PROCS (1)
#endif

#ifndef MYNEWT_VAL_BLE_MESH
#define MYNEWT_VAL_BLE_MESH (0)
#endif

#ifndef MYNEWT_VAL_BLE_MONITOR_CONSOLE_BUFFER_SIZE
#define MYNEWT_VAL_BLE_MONITOR_CONSOLE_BUFFER_SIZE (128)
#endif

#ifndef MYNEWT_VAL_BLE_MONITOR_RTT
#define MYNEWT_VAL_BLE_MONITOR_RTT (0)
#endif

#ifndef MYNEWT_VAL_BLE_MONITOR_RTT_BUFFERED
#define MYNEWT_VAL_BLE_MONITOR_RTT_BUFFERED (1)
#endif

#ifndef MYNEWT_VAL_BLE_MONITOR_RTT_BUFFER_NAME
#define MYNEWT_VAL_BLE_MONITOR_RTT_BUFFER_NAME ("btmonitor")
#endif

#ifndef MYNEWT_VAL_BLE_MONITOR_RTT_BUFFER_SIZE
#define MYNEWT_VAL_BLE_MONITOR_RTT_BUFFER_SIZE (256)
#endif

#ifndef MYNEWT_VAL_BLE_MONITOR_UART
#define MYNEWT_VAL_BLE_MONITOR_UART (0)
#endif

#ifndef MYNEWT_VAL_BLE_MONITOR_UART_BAUDRATE
#define MYNEWT_VAL_BLE_MONITOR_UART_BAUDRATE (1000000)
#endif

#ifndef MYNEWT_VAL_BLE_MONITOR_UART_BUFFER_SIZE
#define MYNEWT_VAL_BLE_MONITOR_UART_BUFFER_SIZE (64)
#endif

#ifndef MYNEWT_VAL_BLE_MONITOR_UART_DEV
#define MYNEWT_VAL_BLE_MONITOR_UART_DEV ("uart0")
#endif

#ifndef MYNEWT_VAL_BLE_RPA_TIMEOUT
#define MYNEWT_VAL_BLE_RPA_TIMEOUT (300)
#endif

#ifndef MYNEWT_VAL_BLE_SM_BONDING
#define MYNEWT_VAL_BLE_SM_BONDING (0)
#endif

#ifndef MYNEWT_VAL_BLE_SM_IO_CAP
#define MYNEWT_VAL_BLE_SM_IO_CAP (BLE_HS_IO_NO_INPUT_OUTPUT)
#endif

#ifndef MYNEWT_VAL_BLE_SM_KEYPRESS
#define MYNEWT_VAL_BLE_SM_KEYPRESS (0)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animal/host定义）*/
#ifndef MYNEWT_VAL_BLE_SM_LEGACY
#define MYNEWT_VAL_BLE_SM_LEGACY (0)
#endif

#ifndef MYNEWT_VAL_BLE_SM_MAX_PROCS
#define MYNEWT_VAL_BLE_SM_MAX_PROCS (1)
#endif

#ifndef MYNEWT_VAL_BLE_SM_MITM
#define MYNEWT_VAL_BLE_SM_MITM (0)
#endif

#ifndef MYNEWT_VAL_BLE_SM_OOB_DATA_FLAG
#define MYNEWT_VAL_BLE_SM_OOB_DATA_FLAG (0)
#endif

#ifndef MYNEWT_VAL_BLE_SM_OUR_KEY_DIST
#define MYNEWT_VAL_BLE_SM_OUR_KEY_DIST (0)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/animal/host定义）*/
#ifndef MYNEWT_VAL_BLE_SM_SC
#define MYNEWT_VAL_BLE_SM_SC (0)
#endif

#ifndef MYNEWT_VAL_BLE_SM_SC_DEBUG_KEYS
#define MYNEWT_VAL_BLE_SM_SC_DEBUG_KEYS (0)
#endif

#ifndef MYNEWT_VAL_BLE_SM_THEIR_KEY_DIST
#define MYNEWT_VAL_BLE_SM_THEIR_KEY_DIST (0)
#endif

#ifndef MYNEWT_VAL_BLE_STORE_MAX_BONDS
#define MYNEWT_VAL_BLE_STORE_MAX_BONDS (3)
#endif

#ifndef MYNEWT_VAL_BLE_STORE_MAX_CCCDS
#define MYNEWT_VAL_BLE_STORE_MAX_CCCDS (8)
#endif

/***@apachemynewt敏捷/敏捷/主机/服务/间隙*/
#ifndef MYNEWT_VAL_BLE_SVC_GAP_APPEARANCE
#define MYNEWT_VAL_BLE_SVC_GAP_APPEARANCE (0)
#endif

#ifndef MYNEWT_VAL_BLE_SVC_GAP_APPEARANCE_WRITE_PERM
#define MYNEWT_VAL_BLE_SVC_GAP_APPEARANCE_WRITE_PERM (-1)
#endif

#ifndef MYNEWT_VAL_BLE_SVC_GAP_CENTRAL_ADDRESS_RESOLUTION
#define MYNEWT_VAL_BLE_SVC_GAP_CENTRAL_ADDRESS_RESOLUTION (-1)
#endif

#ifndef MYNEWT_VAL_BLE_SVC_GAP_DEVICE_NAME
#define MYNEWT_VAL_BLE_SVC_GAP_DEVICE_NAME ("nimble")
#endif

#ifndef MYNEWT_VAL_BLE_SVC_GAP_DEVICE_NAME_MAX_LENGTH
#define MYNEWT_VAL_BLE_SVC_GAP_DEVICE_NAME_MAX_LENGTH (31)
#endif

#ifndef MYNEWT_VAL_BLE_SVC_GAP_DEVICE_NAME_WRITE_PERM
#define MYNEWT_VAL_BLE_SVC_GAP_DEVICE_NAME_WRITE_PERM (-1)
#endif

#ifndef MYNEWT_VAL_BLE_SVC_GAP_PPCP_MAX_CONN_INTERVAL
#define MYNEWT_VAL_BLE_SVC_GAP_PPCP_MAX_CONN_INTERVAL (0)
#endif

#ifndef MYNEWT_VAL_BLE_SVC_GAP_PPCP_MIN_CONN_INTERVAL
#define MYNEWT_VAL_BLE_SVC_GAP_PPCP_MIN_CONN_INTERVAL (0)
#endif

#ifndef MYNEWT_VAL_BLE_SVC_GAP_PPCP_SLAVE_LATENCY
#define MYNEWT_VAL_BLE_SVC_GAP_PPCP_SLAVE_LATENCY (0)
#endif

#ifndef MYNEWT_VAL_BLE_SVC_GAP_PPCP_SUPERVISION_TMO
#define MYNEWT_VAL_BLE_SVC_GAP_PPCP_SUPERVISION_TMO (0)
#endif

#ifndef MYNEWT_VAL_BLE_SVC_GAP_SYSINIT_STAGE
#define MYNEWT_VAL_BLE_SVC_GAP_SYSINIT_STAGE (301)
#endif

/***@apachemynewt敏捷/敏捷/主机/服务/gatt*/
#ifndef MYNEWT_VAL_BLE_SVC_GATT_SYSINIT_STAGE
#define MYNEWT_VAL_BLE_SVC_GATT_SYSINIT_STAGE (302)
#endif

/***@apachemynewt敏捷/敏捷/运输/ram*/
/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/taging/transport/ram定义）*/
#ifndef MYNEWT_VAL_BLE_ACL_BUF_COUNT
#define MYNEWT_VAL_BLE_ACL_BUF_COUNT (4)
#endif

#ifndef MYNEWT_VAL_BLE_ACL_BUF_SIZE
#define MYNEWT_VAL_BLE_ACL_BUF_SIZE (255)
#endif

#ifndef MYNEWT_VAL_BLE_HCI_EVT_BUF_SIZE
#define MYNEWT_VAL_BLE_HCI_EVT_BUF_SIZE (70)
#endif

/* 被@apachemynewt aging/targets/riot覆盖（由@apacheMynewt agick/taging/transport/ram定义）*/
#ifndef MYNEWT_VAL_BLE_HCI_EVT_HI_BUF_COUNT
#define MYNEWT_VAL_BLE_HCI_EVT_HI_BUF_COUNT (2)
#endif

#ifndef MYNEWT_VAL_BLE_HCI_EVT_LO_BUF_COUNT
#define MYNEWT_VAL_BLE_HCI_EVT_LO_BUF_COUNT (8)
#endif

#ifndef MYNEWT_VAL_BLE_TRANS_RAM_SYSINIT_STAGE
#define MYNEWT_VAL_BLE_TRANS_RAM_SYSINIT_STAGE (100)
#endif

/***蝾螈*/
#ifndef MYNEWT_VAL_APP_NAME
#define MYNEWT_VAL_APP_NAME ("dummy_app")
#endif

#ifndef MYNEWT_VAL_APP_dummy_app
#define MYNEWT_VAL_APP_dummy_app (1)
#endif

#ifndef MYNEWT_VAL_ARCH_NAME
#define MYNEWT_VAL_ARCH_NAME ("cortex_m4")
#endif

#ifndef MYNEWT_VAL_ARCH_cortex_m4
#define MYNEWT_VAL_ARCH_cortex_m4 (1)
#endif

#ifndef MYNEWT_VAL_BSP_NAME
#define MYNEWT_VAL_BSP_NAME ("nordic_pca10056")
#endif

#ifndef MYNEWT_VAL_BSP_nordic_pca10056
#define MYNEWT_VAL_BSP_nordic_pca10056 (1)
#endif

#ifndef MYNEWT_VAL_NEWT_FEATURE_LOGCFG
#define MYNEWT_VAL_NEWT_FEATURE_LOGCFG (1)
#endif

#ifndef MYNEWT_VAL_NEWT_FEATURE_SYSDOWN
#define MYNEWT_VAL_NEWT_FEATURE_SYSDOWN (1)
#endif

#ifndef MYNEWT_VAL_TARGET_NAME
#define MYNEWT_VAL_TARGET_NAME ("riot")
#endif

#ifndef MYNEWT_VAL_TARGET_riot
#define MYNEWT_VAL_TARGET_riot (1)
#endif

#endif

