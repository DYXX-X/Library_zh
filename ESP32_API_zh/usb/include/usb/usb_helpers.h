/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*
警告：USB主机库API仍然是测试版，可能会更改
*/

#pragma once

#include <stdint.h>
#include "esp_err.h"
#include "usb/usb_types_stack.h"
#include "usb/usb_types_ch9.h"

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------配置描述符分析-------------------------------------------

/**
 * @brief 获取下一个描述符
 *
 * 给定完整配置描述符中的特定描述符，在配置描述符中获取下一个描述符。这是一个方便的函数，可用于在完整配置描述符中遍历每个单独的描述符。
 *
 * @param[in] cur_desc 当前描述符
 * @param[in] wTotalLength 配置描述符的总长度
 * @param[inout] offset 相对于配置描述符开头的字节偏移量。在输入时，它是当前描述符的偏移量。在输出时，它是返回描述符的偏移量。
 * @return usb_standard_desc_t*下一个描述符，如果达到配置描述符的结尾，则为NULL
 */
const usb_standard_desc_t *usb_parse_next_descriptor(const usb_standard_desc_t *cur_desc, uint16_t wTotalLength, int *offset);

/**
 * @brief 获取特定类型的下一个描述符
 *
 * 给定完整配置描述符中的特定描述符，获取配置描述符中特定类型的下一个描述符（即，使用bDescriptorType值）。
 *
 * @param[in] cur_desc 当前描述符
 * @param[in] wTotalLength 配置描述符的总长度
 * @param[in] bDescriptorType 要获取的下一个描述符的类型
 * @param[inout] offset 相对于配置描述符开头的字节偏移量。在输入时，它是当前描述符的偏移量。在输出时，它是返回描述符的偏移量。
 * @return usb_standard_desc_t*下一个描述符，如果未找到结束描述符或达到配置描述符，则为NULL
 */
const usb_standard_desc_t *usb_parse_next_descriptor_of_type(const usb_standard_desc_t *cur_desc, uint16_t wTotalLength, uint8_t bDescriptorType, int *offset);

/**
 * @brief 获取bInterfaceNumber的备用设置数
 *
 * 给定特定的配置描述符，对于特定的bInterfaceNumber，获取该接口可用的备用设置的数量（即，该bInterfaceNumber的bAlternateSetting的最大可能值）。
 *
 * @param[in] config_desc 指向完整配置描述符开头的指针
 * @param[in] bInterfaceNumber 接口编号
 * @return int接口具有的备用设置数，如果找不到bInterfaceNumber，则为-1
 */
int usb_parse_interface_number_of_alternate(const usb_config_desc_t *config_desc, uint8_t bInterfaceNumber);

/**
 * @brief 获取特定的接口描述符（使用bInterfaceNumber和bAlternateSetting）
 *
 * 给定完整的配置描述符，获取特定的接口描述符。
 *
 * @note 要获取特定bInterfaceNumber的备用设置数，请调用usb_parse_interface_number_of_alternate（）
 *
 * @param[in] config_desc 指向完整配置描述符开头的指针
 * @param[in] bInterfaceNumber 接口编号
 * @param[in] bAlternateSetting 备用设置编号
 * @param[out] offset 接口描述符相对于配置描述符开头的字节偏移量。可以为NULL。
 * @return const usb_intf_desc_t*指向接口描述符的指针，如果找不到则为NULL。
 */
const usb_intf_desc_t *usb_parse_interface_descriptor(const usb_config_desc_t *config_desc, uint8_t bInterfaceNumber, uint8_t bAlternateSetting, int *offset);

/**
 * @brief 在接口描述符中获取端点描述符
 *
 * 给定接口描述符，获取接口的第N个端点描述符。接口描述符的bNumEndpoints字段指示接口中端点的数量。
 *
 * @note 如果bNumEndpoints为0，则表示接口仅使用默认端点
 *
 * @param[in] intf_desc 指向接口描述符开头的指针
 * @param[in] index 终结点索引
 * @param[in] wTotalLength 包含配置描述符的总长度
 * @param[inout] offset 相对于配置描述符开头的字节偏移量。在输入时，它是接口描述符的偏移量。在输出时，它是端点描述符的偏移量。
 * @return const usb_ep_desc_t*指向端点描述符的指针，如果找不到，则为NULL。
 */
const usb_ep_desc_t *usb_parse_endpoint_descriptor_by_index(const usb_intf_desc_t *intf_desc, int index, uint16_t wTotalLength, int *offset);

/**
 * @brief 根据端点地址获取端点描述符
 *
 * 给定配置描述符，根据其bEndpointAddress、bAlternateSetting和bInterfaceNumber获取端点描述符。
 *
 * @param[in] config_desc 指向完整配置描述符开头的指针
 * @param[in] bInterfaceNumber 接口编号
 * @param[in] bAlternateSetting 备用设置编号
 * @param[in] bEndpointAddress 终结点地址
 * @param[out] offset 端点描述符相对于配置描述符开头的字节偏移量。可以为NULL
 * @return const usb_ep_desc_t*指向端点描述符的指针，如果找不到，则为NULL。
 */
const usb_ep_desc_t *usb_parse_endpoint_descriptor_by_address(const usb_config_desc_t *config_desc, uint8_t bInterfaceNumber, uint8_t bAlternateSetting, uint8_t bEndpointAddress, int *offset);

// -----------------------------------------------描述符打印-------------------------------------------------

/**
 * @brief 打印特定于类的描述符回调
 *
 * 要提供给usb_print_config_descriptor（）函数的可选回调。遇到非标准描述符时调用回调。回调应在打印描述符时对其进行解码。
 */
typedef void (*print_class_descriptor_cb)(const usb_standard_desc_t *);

/**
 * @brief 打印设备描述符
 *
 * @param devc_desc 设备描述符
 */
void usb_print_device_descriptor(const usb_device_desc_t *devc_desc);

/**
 * @brief 打印配置描述符
 *
 * -此函数打印配置描述符的全部内容（包括接口和端点描述符）
 * -当遇到非标准描述符时，该函数将调用class_specific_cb（如果提供了）
 *
 * @param cfg_desc 配置描述符
 * @param class_specific_cb 类特定的描述符回调。可以为NULL
 */
void usb_print_config_descriptor(const usb_config_desc_t *cfg_desc, print_class_descriptor_cb class_specific_cb);

/**
 * @brief 打印字符串描述符
 *
 * 此函数仅打印UTF-16编码字符串的ASCII字符
 *
 * @param str_desc 字符串描述符
 */
void usb_print_string_descriptor(const usb_str_desc_t *str_desc);

// ------------------------------------------------------其他---------------------------------------------------------

/**
 * @brief 舍入为端点MPS的整数倍
 *
 * 这是一个方便的函数，用于将大小/长度舍入为端点的MPS（最大数据包大小）。这在计算IN端点的传输或缓冲区长度时非常有用。
 * -如果MPS<=0，此函数将返回0
 * -如果num_bytes<=0，则此函数将返回0
 *
 * @param[in] num_bytes 字节数
 * @param[in] mps MPS
 * @return int MPS的整数倍舍入
 */
static inline int usb_round_up_to_mps(int num_bytes, int mps)
{
    if (num_bytes <= 0 || mps <= 0) {    //MPS永远不能为零
        return 0;
    }
    return ((num_bytes + mps - 1) / mps) * mps;
}

#ifdef __cplusplus
}
#endif

