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

#ifndef ROM_CRC_H
#define ROM_CRC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup crc_apis、uart配置和通信相关api
  * @brief crc api
  */

/** @addtogroup crc_apis公司@{
  */


/* 标准CRC8/16/32算法。*/
// CRC-8 x8+x2+x1+1 0x07
// CRC16-CCITT x16+x12+x5+1 1021 ISO HDLC，ITU X.25，V.34/V.41/V。42，PPP-FCS
// CRC32:
//G（x）=x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x1+1
//如果buf不连续，可以使用第一个结果作为第二个参数。

/**
  * @brief 以小端为单位的Crc32值。
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
  * @brief 以大端为单位的Crc32值。
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
  * @brief 以小端为单位的Crc16值。
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
  * @brief Crc16值，以大端为单位。
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
  * @brief 以小端为单位的Crc8值。
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
  * @brief 以大端为单位的Crc8值。
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

