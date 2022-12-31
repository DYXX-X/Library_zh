/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @brief 以SD协议使用的格式返回CRC7数据
 * @param data 用于计算CRC的数据数组
 * @param size 数据大小（字节）
 * @return CRC7值
 */
uint8_t sdspi_crc7(const uint8_t *data, size_t size);

/**
 * @brief 以SD协议使用的格式返回CRC16数据
 * @param data 用于计算CRC的数据数组
 * @param size 数据大小（字节）
 * @return CRC16值
 */
uint16_t sdspi_crc16(const uint8_t* data, size_t size);


#ifdef __cplusplus
}
#endif

