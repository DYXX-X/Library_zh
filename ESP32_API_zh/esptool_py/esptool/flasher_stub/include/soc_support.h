/*
 * SPDX文件版权所有文本：2016-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：GPL-2.0或
 */

/* 对ESP8266/ESP32的SoC级支持。
 *
 * 提供统一的寄存器级接口。
 *
 * 这与ESP8266非OS SDK和ESP-IDF soc组件的寄存器头中提供的信息相同，但此处仅包含闪光灯存根所需的值。
 *
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define READ_REG(REG) (*((volatile uint32_t *)(REG)))
#define WRITE_REG(REG, VAL) *((volatile uint32_t *)(REG)) = (VAL)
#define REG_SET_MASK(reg, mask) WRITE_REG((reg), (READ_REG(reg)|(mask)))
#define REG_CLR_MASK(reg, mask) WRITE_REG((reg), (READ_REG(reg)&(~(mask))))

#define ESP32_OR_LATER   !(ESP8266)
#define ESP32S2_OR_LATER !(ESP8266 || ESP32)
#define ESP32S3_OR_LATER !(ESP8266 || ESP32 || ESP32S2)

/**********************************************************
 * 每SOC能力
 */
#ifdef ESP32S2
#define WITH_USB_OTG 1
#endif // ESP32S2

#ifdef ESP32C3
#define WITH_USB_JTAG_SERIAL 1
#define IS_RISCV 1
#endif // ESP32C3

#ifdef ESP32S3
#define WITH_USB_JTAG_SERIAL 1
#define WITH_USB_OTG 1
#endif // ESP32S3

/**********************************************************
 * 基于SOC的外围寄存器基址
 */
#ifdef ESP8266
#define UART_BASE_REG       0x60000000 /* UART0 */
#define SPI_BASE_REG        0x60000200 /* SPI外围设备0*/
#endif

#ifdef ESP32
#define UART_BASE_REG       0x3ff40000 /* UART0 */
#define SPI_BASE_REG        0x3ff42000 /* SPI外设1，用于SPI闪存*/
#define SPI0_BASE_REG       0x3ff43000 /* SPI外设0，内部状态机*/
#define GPIO_BASE_REG       0x3ff44000 /* GPIO */
#endif

#ifdef ESP32S2
#define UART_BASE_REG       0x60000000 /* UART0 */
#define SPI_BASE_REG        0x3f402000 /* SPI外设1，用于SPI闪存*/
#define SPI0_BASE_REG       0x3f403000 /* SPI外设0，内部状态机*/
#define GPIO_BASE_REG       0x3f404000
#define USB_BASE_REG        0x60080000
#define RTCCNTL_BASE_REG    0x3f408000
#endif

#ifdef ESP32S3
#define UART_BASE_REG       0x60000000 /* UART0 */
#define SPI_BASE_REG        0x60002000 /* SPI外设1，用于SPI闪存*/
#define SPI0_BASE_REG       0x60003000 /* SPI外设0，内部状态机*/
#define GPIO_BASE_REG       0x60004000 /* GPIO */
#define USB_BASE_REG        0x60080000
#define RTCCNTL_BASE_REG    0x60008000 /* RTC控制*/
#define USB_DEVICE_BASE_REG 0x60038000
#endif

#ifdef ESP32C3
#define UART_BASE_REG       0x60000000 /* UART0 */
#define SPI_BASE_REG        0x60002000 /* SPI外设1，用于SPI闪存*/
#define SPI0_BASE_REG       0x60003000 /* SPI外设0，内部状态机*/
#define GPIO_BASE_REG       0x60004000
#define RTCCNTL_BASE_REG    0x60008000
#define USB_DEVICE_BASE_REG 0x60043000
#endif

#ifdef ESP32C6
#define UART_BASE_REG       0x60000000 /* UART0 */
#define SPI_BASE_REG        0x60002000 /* SPI外设1，用于SPI闪存*/
#define SPI0_BASE_REG       0x60003000 /* SPI外设0，内部状态机*/
#define GPIO_BASE_REG       0x60004000
#define RTCCNTL_BASE_REG    0x60008000
#endif

#ifdef ESP32H2
#define UART_BASE_REG       0x60000000 /* UART0 */
#define SPI_BASE_REG        0x60002000 /* SPI外设1，用于SPI闪存*/
#define SPI0_BASE_REG       0x60003000 /* SPI外设0，内部状态机*/
#define GPIO_BASE_REG       0x60004000
#define RTCCNTL_BASE_REG    0x60008000
#endif

#ifdef ESP32C2
#define UART_BASE_REG      0x60000000 /* UART0 */
#define SPI_BASE_REG       0x60002000 /* SPI外设1，用于SPI闪存*/
#define SPI0_BASE_REG      0x60003000 /* SPI外设0，内部状态机*/
#define GPIO_BASE_REG      0x60004000
#define RTCCNTL_BASE_REG   0x60008000
#endif
/**********************************************************
 * UART外围设备
 *
 * 我们在所有芯片上使用的功能基本相同
 *
 * 仅使用UART0
 */
#define UART_CLKDIV_REG(X) (UART_BASE_REG + 0x14)
#define UART_CLKDIV_M      (0x000FFFFF)

#if ESP32_OR_LATER
#define UART_CLKDIV_FRAG_S 20
#define UART_CLKDIV_FRAG_V 0xF
#endif

#define UART_FIFO(X)       (UART_BASE_REG + 0x00)
#define UART_INT_ST(X)     (UART_BASE_REG + 0x08)
#define UART_INT_ENA(X)    (UART_BASE_REG + 0x0C)
#define UART_INT_CLR(X)    (UART_BASE_REG + 0x10)
#define UART_STATUS(X)     (UART_BASE_REG + 0x1C)

#if ESP32S2_OR_LATER
#define UART_RXFIFO_CNT_M 0x3FF
#else
#define UART_RXFIFO_CNT_M 0xFF
#endif

#define UART_RXFIFO_FULL_INT_ENA            (1<<0)
#define UART_RXFIFO_TOUT_INT_ENA            (1<<8)

#define ETS_UART0_INUM 5


/**********************************************************
 * SPI外围设备
 *
 * 除了W0基地址和2字节状态命令选项外，我们在所有芯片上使用的功能基本相同
 *
 * 仅使用一个SPI外围设备（ESP8266上为0，ESP32上为1）。在ESP32S2和ESP32S3上，这称为SPI_MEM_xxx索引1
 */
#define SPI_CMD_REG       (SPI_BASE_REG + 0x00)
#define SPI_FLASH_WREN    (1<<30)
#define SPI_FLASH_RDSR    (1<<27)
#define SPI_FLASH_SE      (1<<24)
#define SPI_FLASH_BE      (1<<23)

#define SPI_ADDR_REG      (SPI_BASE_REG + 0x04)

#define SPI_CTRL_REG      (SPI_BASE_REG + 0x08)
#if ESP32_OR_LATER
#define SPI_WRSR_2B       (1<<22)
#endif

#if ESP32S2_OR_LATER
#define SPI_RD_STATUS_REG (SPI_BASE_REG + 0x2C)
#else
#define SPI_RD_STATUS_REG (SPI_BASE_REG + 0x10)
#endif

#ifdef ESP8266
#define SPI_W0_REG        (SPI_BASE_REG + 0x40)
#endif
#ifdef ESP32
#define SPI_W0_REG        (SPI_BASE_REG + 0x80)
#endif
#if ESP32S2_OR_LATER
#define SPI_W0_REG        (SPI_BASE_REG + 0x58)
#endif

#if ESP32S2_OR_LATER
#define SPI_EXT2_REG      (SPI_BASE_REG + 0x54) /* 重命名为SPI_MEM_FSM_REG*/
#else
#define SPI_EXT2_REG      (SPI_BASE_REG + 0xF8)
#endif

#define SPI_ST 0x7 /* 完成状态值*/

#ifdef ESP32
/* 在ESP32和更高版本上，SPI外设是分层闪存，这让我们可以检查SPI闪存控制器下的内部状态机的状态
 */
#define SPI0_EXT2_REG     (SPI0_BASE_REG + 0xF8)
#endif
#if ESP32S2_OR_LATER
#define SPI0_EXT2_REG     (SPI0_BASE_REG + 0x54)
#endif

/**********************************************************
 * GPIO外围设备
 *
 * 我们只需要读取ESP32或更高版本上的打包寄存器
 */
#define GPIO_STRAP_REG    (GPIO_BASE_REG + 0x38)

/**********************************************************
 * USB外围设备
 */

#ifdef ESP32S2
#define UART_USB_OTG  2

#define ETS_USB_INTR_SOURCE  48
#define ETS_USB_INUM  9  /* 任意1级中断*/
#endif // ESP32S2

#ifdef ESP32C3
#define UART_USB_JTAG_SERIAL  3

#define USB_DEVICE_INT_CLR_REG          (USB_DEVICE_BASE_REG + 0x014)
#define USB_DEVICE_EP1_CONF_REG         (USB_DEVICE_BASE_REG + 0x004)
#define USB_DEVICE_EP1_REG              (USB_DEVICE_BASE_REG + 0x000)
#define USB_DEVICE_SERIAL_OUT_RECV_PKT_INT_CLR  (1<<2)
#define USB_DEVICE_SERIAL_OUT_EP_DATA_AVAIL     (1<<2)

#define DR_REG_INTERRUPT_CORE0_BASE             0x600c2000
#define INTERRUPT_CORE0_USB_INTR_MAP_REG        (DR_REG_INTERRUPT_CORE0_BASE + 0x068) /* USB JTAG串行*/

#define USB_DEVICE_INT_ENA_REG                  (USB_DEVICE_BASE_REG + 0x010)
#define USB_DEVICE_SERIAL_OUT_RECV_PKT_INT_ENA  (1<<2)

#define ETS_USB_INUM 17  /* 任意1级中断*/
#endif

#ifdef ESP32S3
#define UART_USB_OTG  3
#define UART_USB_JTAG_SERIAL  4

#define USB_DEVICE_INT_CLR_REG          (USB_DEVICE_BASE_REG + 0x014)
#define USB_DEVICE_EP1_CONF_REG         (USB_DEVICE_BASE_REG + 0x004)
#define USB_DEVICE_EP1_REG              (USB_DEVICE_BASE_REG + 0x000)
#define USB_DEVICE_SERIAL_OUT_RECV_PKT_INT_CLR  (1<<2)
#define USB_DEVICE_SERIAL_OUT_EP_DATA_AVAIL     (1<<2)

#define DR_REG_INTERRUPT_CORE0_BASE             0x600c2000
#define INTERRUPT_CORE0_USB_INTR_MAP_REG        (DR_REG_INTERRUPT_CORE0_BASE + 0x098) /* DWC-OTG */
#define INTERRUPT_CORE0_USB_DEVICE_INT_MAP_REG  (DR_REG_INTERRUPT_CORE0_BASE + 0x180) /* USB JTAG串行*/

#define USB_DEVICE_INT_ENA_REG                  (USB_DEVICE_BASE_REG + 0x010)
#define USB_DEVICE_SERIAL_OUT_RECV_PKT_INT_ENA  (1<<2)

#define ETS_USB_INUM 17  /* 任意1级中断*/
#endif

#define USB_GAHBCFG_REG    (USB_BASE_REG + 0x8)
#define USB_GLBLLNTRMSK    (1 << 0)


/**********************************************************
 * RTC_CNTL外围设备
 */

#ifdef ESP32S2
#define RTC_CNTL_OPTION1_REG          (RTCCNTL_BASE_REG + 0x0128)
#endif

#ifdef ESP32S3
#define RTC_CNTL_OPTION1_REG          (RTCCNTL_BASE_REG + 0x012C)
#endif

#define RTC_CNTL_FORCE_DOWNLOAD_BOOT  (1 << 0)

/**********************************************************
 * 每个SOC安全信息缓冲区大小
 */

#ifdef ESP32S2
#define SECURITY_INFO_BYTES 12 /* 不包括chip_id和api_version*/
#endif // ESP32S2

#if ESP32S3_OR_LATER
#define SECURITY_INFO_BYTES 20
#endif // ESP32S3_OR_LATER

