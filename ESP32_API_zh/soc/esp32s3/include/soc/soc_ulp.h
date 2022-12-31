// 版权所有2010-2020 Espressif Systems（上海）私人有限公司
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

// 此文件包含ULP程序中使用的各种方便宏。

// 使用预处理器从掩码计算位字段宽度的助手宏。
// 稍后在READ_RTC_FIELD和WRITE_RTC_FFIELD中使用。
#define IS_BIT_SET(m, i) (((m) >> (i)) & 1)
#define MASK_TO_WIDTH_HELPER1(m, i)  IS_BIT_SET(m, i)
#define MASK_TO_WIDTH_HELPER2(m, i)  (MASK_TO_WIDTH_HELPER1(m, i)  + MASK_TO_WIDTH_HELPER1(m, i + 1))
#define MASK_TO_WIDTH_HELPER4(m, i)  (MASK_TO_WIDTH_HELPER2(m, i)  + MASK_TO_WIDTH_HELPER2(m, i + 2))
#define MASK_TO_WIDTH_HELPER8(m, i)  (MASK_TO_WIDTH_HELPER4(m, i)  + MASK_TO_WIDTH_HELPER4(m, i + 4))
#define MASK_TO_WIDTH_HELPER16(m, i) (MASK_TO_WIDTH_HELPER8(m, i)  + MASK_TO_WIDTH_HELPER8(m, i + 8))
#define MASK_TO_WIDTH_HELPER32(m, i) (MASK_TO_WIDTH_HELPER16(m, i) + MASK_TO_WIDTH_HELPER16(m, i + 16))

// 外围寄存器访问宏，围绕REG_RD和REG_WR指令构建。
// rtc_cntl_reg中定义的寄存器。h、 rtc_io_reg。h、 传感器_ reg。h、 和rtc_i2c_reg。h可用于这些宏。

// 从rtc_reg[low_bit+bit_width-1:low_bit]读取到R0，bit_width<=16
#define READ_RTC_REG(rtc_reg, low_bit, bit_width) \
    REG_RD (((rtc_reg) - DR_REG_RTCCNTL_BASE) / 4), ((low_bit) + (bit_width) - 1), (low_bit)

// 将立即值写入rtc_reg[low_bit+bit_width-1:low_bit]，bit_width<=8
#define WRITE_RTC_REG(rtc_reg, low_bit, bit_width, value) \
    REG_WR (((rtc_reg) - DR_REG_RTCCNTL_BASE) / 4), ((low_bit) + (bit_width) - 1), (low_bit), ((value) & 0xff)

// 从rtc_reg中的字段读取R0，最多16位
#define READ_RTC_FIELD(rtc_reg, field) \
    READ_RTC_REG(rtc_reg, field ## _S, MASK_TO_WIDTH_HELPER16(field ## _V, 0))

// 将即时值写入rtc_reg中的字段，最多8位
#define WRITE_RTC_FIELD(rtc_reg, field, value) \
    WRITE_RTC_REG(rtc_reg, field ## _S, MASK_TO_WIDTH_HELPER8(field ## _V, 0), ((value) & field ## _V))

