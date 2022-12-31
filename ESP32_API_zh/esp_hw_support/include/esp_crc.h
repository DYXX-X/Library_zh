/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// 此标头只是ROM CRC API的包装器
#include "esp_rom_crc.h"

/**
* @brief CRC32值（小端）。
*
* @param crc: 初始CRC值（上次计算的结果或首次为0）
* @param buf: 用于计算CRC值的数据缓冲区
* @param len: 数据缓冲区的长度
* @return CRC32值
*/
static inline uint32_t esp_crc32_le(uint32_t crc, uint8_t const *buf, uint32_t len)
{
    return esp_rom_crc32_le(crc, buf, len);
}

/**
* @brief CRC32值（大端）。
*
* @param crc: 初始CRC值（上次计算的结果或首次为0）
* @param buf: 用于计算CRC值的数据缓冲区
* @param len: 数据缓冲区的长度
* @return CRC32值
*/
static inline uint32_t esp_crc32_be(uint32_t crc, uint8_t const *buf, uint32_t len)
{
    return esp_rom_crc32_be(crc, buf, len);
}

/**
* @brief 小端字节中的CRC16值。
*
* @param crc: 初始CRC值（上次计算的结果或首次为0）
* @param buf: 用于计算CRC值的数据缓冲区
* @param len: 数据缓冲区的长度
* @return CRC16值
*/
static inline uint16_t esp_crc16_le(uint16_t crc, uint8_t const *buf, uint32_t len)
{
    return esp_rom_crc16_le(crc, buf, len);
}

/**
* @brief CRC16值（大端）。
*
* @param crc: 初始CRC值（上次计算的结果或首次为0）
* @param buf: 用于计算CRC值的数据缓冲区
* @param len: 数据缓冲区的长度
* @return CRC16值
*/
static inline uint16_t esp_crc16_be(uint16_t crc, uint8_t const *buf, uint32_t len)
{
    return esp_rom_crc16_be(crc, buf, len);
}

/**
* @brief 小端字节中的CRC8值。
*
* @param crc: 初始CRC值（上次计算的结果或首次为0）
* @param buf: 用于计算CRC值的数据缓冲区
* @param len: 数据缓冲区的长度
* @return CRC8值
*/
static inline uint8_t esp_crc8_le(uint8_t crc, uint8_t const *buf, uint32_t len)
{
    return esp_rom_crc8_le(crc, buf, len);
}

/**
* @brief 以大端为单位的CRC8值。
*
* @param crc: 初始CRC值（上次计算的结果或首次为0）
* @param buf: 用于计算CRC值的数据缓冲区
* @param len: 数据缓冲区的长度
* @return CRC8值
*/
static inline uint8_t esp_crc8_be(uint8_t crc, uint8_t const *buf, uint32_t len)
{
    return esp_rom_crc8_be(crc, buf, len);
}

#ifdef __cplusplus
}
#endif

