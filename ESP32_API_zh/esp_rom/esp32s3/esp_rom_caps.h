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

#pragma once

#define ESP_ROM_HAS_CRC_LE                  (1) // ROM CRC库支持Little Endian
#define ESP_ROM_HAS_CRC_BE                  (1) // ROM CRC库支持Big Endian
#define ESP_ROM_HAS_JPEG_DECODE             (1) // ROM具有JPEG解码库
#define ESP_ROM_SUPPORT_MULTIPLE_UART       (1) // ROM有多个UART可用于日志记录
#define ESP_ROM_UART_CLK_IS_XTAL            (1) // UART时钟源选择到ROM中的XTAL
#define ESP_ROM_HAS_RETARGETABLE_LOCKING    (1) // ROM是用可重定目标锁定构建的
#define ESP_ROM_USB_SERIAL_DEVICE_NUM       (4) // ROM中USB_serial_JTAG的串行端口ID（UART、USB…）。
#define ESP_ROM_HAS_ERASE_0_REGION_BUG      (1) // ROM存在esp_flash_ease_region（大小=0）错误

