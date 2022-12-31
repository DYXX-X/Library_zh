/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stddef.h>
#include "soc/soc_caps.h"
#include "hal/dma_types.h"
#if SOC_LCDCAM_SUPPORTED
#include "hal/lcd_hal.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_PERIPH_CLOCK_PRE_SCALE (2) // 这是可应用于LCD外围设备的最小除法器

#if SOC_LCDCAM_SUPPORTED

typedef enum {
    LCD_COM_DEVICE_TYPE_I80,
    LCD_COM_DEVICE_TYPE_RGB
} lcd_com_device_type_t;

/**
 * @brief 向平台注册LCD设备
 *
 * @param device_type 设备类型，请参阅lcd_com_Device_type_t
 * @param device_obj 设备对象
 * @return >=0：member_id，<0：无可用的lcd总线/面板插槽
 */
int lcd_com_register_device(lcd_com_device_type_t device_type, void *device_obj);

/**
 * @brief 从平台上移除设备
 *
 * @param device_type 设备类型，请参阅lcd_com_Device_type_t
 * @param member_id 成员ID
 */
void lcd_com_remove_device(lcd_com_device_type_t device_type, int member_id);
#endif // SOC_LCDCAM_SUPPORTED

/**
 * @brief 将数据装载到DMA描述符
 *
 * @param desc_head 指向DMA描述符链的头部
 * @param buffer 数据缓冲区
 * @param len 数据缓冲区的大小（字节）
 */
void lcd_com_mount_dma_data(dma_descriptor_t *desc_head, const void *buffer, size_t len);

/**
 * @brief 反转缓冲区中的字节
 *
 * @note  LCD是大端的，例如发送命令0x1234，字节0x12应首先出现在总线上。然而，低级别外围设备（如i80、i2s）将首先发送0x34。此助手函数用于反转字节顺序
 *
 * @param buf 缓冲区地址
 * @param start 缓冲区的起始索引
 * @param end 缓冲区的结束索引
 */
static inline void lcd_com_reverse_buffer_bytes(uint8_t *buf, int start, int end)
{
    uint8_t temp = 0;
    while (start < end) {
        temp = buf[start];
        buf[start] = buf[end];
        buf[end] = temp;
        start++;
        end--;
    }
}

#ifdef __cplusplus
}
#endif

