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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**           关于CRC API的说明ESP32 ROM包括一些CRC表和CRC API，以加快CRC计算。CRC API包括用于小端和大端模式的CRC8、CRC16和CRC32算法。以下是算法的多项式：CRC-8 x8+x2+x1+1 0x07 CRC16-CCITT x16+x12+x5+1 0x1021 CRC32 x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x1+1 0x04c11db7
 *
 * 这些CRC API组设计用于计算缓冲区中的数据，无论是否连续。为了方便起见，我们在函数的开头和结尾添加了一个“~”。要计算非连续缓冲区，我们可以编写如下代码：init=~init；crc=crc32_le（init，buf0，length0）；crc=crc32_le（crc，buf1，长度1）；crc=~crc；
 *
 * 然而，选择要使用的API并给出正确的参数并不容易。一个特定的CRC算法将包括以下参数：width、多项式、init、reff、驱回、xorout reff和驱回。这些参数显示算法的端序：如果这两个参数都为真，请使用小端序API。如果这两个都是假的，请使用big endian API。xorout是需要与原始结果进行异或运算的值。然而，这些API组在API前后需要一个“~”。
 *
 * 以下是CRC16/CCITT的一些示例：CRC-16/CCITT，poly=0x1021，init=0x000，reff=true，refret=true，xorout=0x000 CRC=~CRC16_le（（uint16_t）~0x0000，buf，length）；
 *
 * CRC-16/CCITT-FALSE，poly=0x021，init=0xfff，reff=FALSE，refret=FALSE，xorout=0x000 CRC=~crc16_be（（uint16_t）~0xffff，buf，长度）；
 *
 * CRC-16/X25，poly=0x1021，init=0xfff，refref=true，refret=true，xorout=0xfff CRC=（~crc16_le（（uint16_t）~（0xffff），buf，长度））^0xffff；
 *
 * CRC-16/XMODEM，poly=0x1021，init=0x000，refu=false，推回=false，xorout=0x000 CRC=~crc16_be（（uint16_t）~0x0000，buf，长度）；
 *
 */

/**
 * @brief CRC32值（小端）。
 *
 * @param crc: 初始CRC值（上次计算的结果或首次为0）
 * @param buf: 用于计算CRC值的数据缓冲区
 * @param len: 数据缓冲区的长度
 * @return CRC32值
 */
uint32_t esp_rom_crc32_le(uint32_t crc, uint8_t const *buf, uint32_t len);

/**
 * @brief CRC32值（大端）。
 *
 * @param crc: 初始CRC值（上次计算的结果或首次为0）
 * @param buf: 用于计算CRC值的数据缓冲区
 * @param len: 数据缓冲区的长度
 * @return CRC32值
 */
uint32_t esp_rom_crc32_be(uint32_t crc, uint8_t const *buf, uint32_t len);

/**
 * @brief 小端字节中的CRC16值。
 *
 * @param crc: 初始CRC值（上次计算的结果或首次为0）
 * @param buf: 用于计算CRC值的数据缓冲区
 * @param len: 数据缓冲区的长度
 * @return CRC16值
 */
uint16_t esp_rom_crc16_le(uint16_t crc, uint8_t const *buf, uint32_t len);

/**
 * @brief CRC16值（大端）。
 *
 * @param crc: 初始CRC值（上次计算的结果或首次为0）
 * @param buf: 用于计算CRC值的数据缓冲区
 * @param len: 数据缓冲区的长度
 * @return CRC16值
 */
uint16_t esp_rom_crc16_be(uint16_t crc, uint8_t const *buf, uint32_t len);

/**
 * @brief 小端字节中的CRC8值。
 *
 * @param crc: 初始CRC值（上次计算的结果或首次为0）
 * @param buf: 用于计算CRC值的数据缓冲区
 * @param len: 数据缓冲区的长度
 * @return CRC8值
 */
uint8_t esp_rom_crc8_le(uint8_t crc, uint8_t const *buf, uint32_t len);

/**
 * @brief 以大端为单位的CRC8值。
 *
 * @param crc: 初始CRC值（上次计算的结果或首次为0）
 * @param buf: 用于计算CRC值的数据缓冲区
 * @param len: 数据缓冲区的长度
 * @return CRC8值
 */
uint8_t esp_rom_crc8_be(uint8_t crc, uint8_t const *buf, uint32_t len);

#ifdef __cplusplus
}
#endif

