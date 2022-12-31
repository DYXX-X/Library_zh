// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef ROM_CRC_H
#define ROM_CRC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup uart_api、uart配置和通信相关api
  * @brief uart api
  */

/** @addtogroup uart_api@{
  */


/*           关于CRC API使用的说明ESP32 ROM包括一些CRC表和CRC API，以加快CRC计算。CRC API包括用于小端和大端模式的CRC8、CRC16和CRC32算法。以下是算法的多项式：CRC-8 x8+x2+x1+1 0x07 CRC16-CCITT x16+x12+x5+1 0x1021 CRC32 x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x1+1 0x04c11db7
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
 *
 */

/**
  * @brief 以小端为单位的CRC32值。
  *
  * @param  uint32_t crc：初始化crc值，第一次使用时使用0。
  *
  * @param  uint8_t const*buf：开始计算crc的缓冲区。
  *
  * @param  uint32_t len：缓冲区长度（字节）。
  *
  * @return 没有一个
  */
uint32_t crc32_le(uint32_t crc, uint8_t const *buf, uint32_t len);

/**
  * @brief 以大端为单位的CRC32值。
  *
  * @param  uint32_t crc：初始化crc值，第一次使用时使用0。
  *
  * @param  uint8_t const*buf：开始计算crc的缓冲区。
  *
  * @param  uint32_t len：缓冲区长度（字节）。
  *
  * @return 没有一个
  */
uint32_t crc32_be(uint32_t crc, uint8_t const *buf, uint32_t len);

/**
  * @brief 以小端为单位的CRC16值。
  *
  * @param  uint16_t crc：初始化crc值，第一次使用时使用0。
  *
  * @param  uint8_t const*buf：开始计算crc的缓冲区。
  *
  * @param  uint32_t len：缓冲区长度（字节）。
  *
  * @return 没有一个
  */
uint16_t crc16_le(uint16_t crc, uint8_t const *buf, uint32_t len);

/**
  * @brief 以大端为单位的CRC16值。
  *
  * @param  uint16_t crc：初始化crc值，第一次使用时使用0。
  *
  * @param  uint8_t const*buf：开始计算crc的缓冲区。
  *
  * @param  uint32_t len：缓冲区长度（字节）。
  *
  * @return 没有一个
  */
uint16_t crc16_be(uint16_t crc, uint8_t const *buf, uint32_t len);

/**
  * @brief 以小端为单位的CRC8值。
  *
  * @param  uint8_t crc：初始化crc值，第一次使用时使用0。
  *
  * @param  uint8_t const*buf：开始计算crc的缓冲区。
  *
  * @param  uint32_t len：缓冲区长度（字节）。
  *
  * @return 没有一个
  */
uint8_t crc8_le(uint8_t crc, uint8_t const *buf, uint32_t len);

/**
  * @brief 以大端为单位的CRC8值。
  *
  * @param  uint32_t crc：初始化crc值，第一次使用时使用0。
  *
  * @param  uint8_t const*buf：开始计算crc的缓冲区。
  *
  * @param  uint32_t len：缓冲区长度（字节）。
  *
  * @return 没有一个
  */
uint8_t crc8_be(uint8_t crc, uint8_t const *buf, uint32_t len);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif

