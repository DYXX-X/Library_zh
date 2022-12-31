/* usb_cdc。h-USB CDC-ACM和CDC-ECM公共标头*/

/*
 * 版权所有（c）2017 PHYTEC Messtechnik GmbH
 *
 * SPDX许可证标识符：Apache-2.0
 */


/**
 * @file
 * @brief USB通信设备类（CDC）公共标头
 *
 * 标题遵循通信设备规范（CDC120-20101103-track.pdf）、PSTN设备规范（PSTN12.pdf）和以太网控制模型设备规范（ECM120.pdf）的类别定义。标题仅限于ACM和ECM子类。
 */

#pragma once

#include <stdint.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**BCD格式的CDC规范版本号*/
#define CDC_SRN_1_20            0x0120

/**通信类子类代码*/
#define ACM_SUBCLASS            0x02
#define ECM_SUBCLASS            0x06
#define EEM_SUBCLASS            0x0c

/**通信类协议代码*/
#define AT_CMD_V250_PROTOCOL        0x01
#define EEM_PROTOCOL            0x07

/**
 * @brief 数据类接口代码
 * @note CDC120-20101103轨道。pdf，4.5，表6
 */
#define DATA_INTERFACE_CLASS        0x0A

/**
 * @brief bDescriptorType字段的值
 * @note CDC120-20101103轨道。pdf，5.2.3，表12
 */
#define CS_INTERFACE            0x24
#define CS_ENDPOINT         0x25

/**
 * @brief b通信类函数描述符的描述符子类型
 * @note CDC120-20101103轨道。pdf，5.2.3，表13
 */
#define HEADER_FUNC_DESC        0x00
#define CALL_MANAGEMENT_FUNC_DESC   0x01
#define ACM_FUNC_DESC           0x02
#define UNION_FUNC_DESC         0x06
#define ETHERNET_FUNC_DESC      0x0F

/**
 * @brief ACM设备的PSTN子类特定请求
 * @note PSTN120.pdf，6.3，表13
 */
#define CDC_SEND_ENC_CMD        0x00
#define CDC_GET_ENC_RSP         0x01
#define SET_LINE_CODING         0x20
#define GET_LINE_CODING         0x21
#define SET_CONTROL_LINE_STATE      0x22

/**SetControlLineState的控制信号位图值*/
#define SET_CONTROL_LINE_STATE_RTS  0x02
#define SET_CONTROL_LINE_STATE_DTR  0x01

/**UART状态位图值*/
#define SERIAL_STATE_OVERRUN        0x40
#define SERIAL_STATE_PARITY     0x20
#define SERIAL_STATE_FRAMING        0x10
#define SERIAL_STATE_RING       0x08
#define SERIAL_STATE_BREAK      0x04
#define SERIAL_STATE_TX_CARRIER     0x02
#define SERIAL_STATE_RX_CARRIER     0x01

/**
 * @brief 以太网子类的类特定请求代码
 * @note ECM120.pdf，6.2，表6
 */
#define SET_ETHERNET_MULTICAST_FILTERS  0x40
#define SET_ETHERNET_PM_FILTER      0x41
#define GET_ETHERNET_PM_FILTER      0x42
#define SET_ETHERNET_PACKET_FILTER  0x43
#define GET_ETHERNET_STATISTIC      0x44

/**以太网数据包过滤器位图*/
#define PACKET_TYPE_MULTICAST       0x10
#define PACKET_TYPE_BROADCAST       0x08
#define PACKET_TYPE_DIRECTED        0x04
#define PACKET_TYPE_ALL_MULTICAST   0x02
#define PACKET_TYPE_PROMISCUOUS     0x01

/**标题功能描述符*/
struct cdc_header_descriptor {
    uint8_t bFunctionLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint16_t bcdCDC;
} __packed;

/**联合接口功能描述符*/
struct cdc_union_descriptor {
    uint8_t bFunctionLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bControlInterface;
    uint8_t bSubordinateInterface0;
} __packed;

/**呼叫管理功能描述符*/
struct cdc_cm_descriptor {
    uint8_t bFunctionLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bmCapabilities;
    uint8_t bDataInterface;
} __packed;

/**抽象控制管理功能描述符*/
struct cdc_acm_descriptor {
    uint8_t bFunctionLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bmCapabilities;
} __packed;


/**GET_LINE_CODING/SET_LINE_CODING类请求的数据结构*/
struct cdc_acm_line_coding {
    uint32_t dwDTERate;
    uint8_t bCharFormat;
    uint8_t bParityType;
    uint8_t bDataBits;
} __packed;

/**关于SerialState的通知的数据结构*/
struct cdc_acm_notification {
    uint8_t bmRequestType;
    uint8_t bNotificationType;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
    uint16_t data;
} __packed;

/**以太网网络功能描述符*/
struct cdc_ecm_descriptor {
    uint8_t bFunctionLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t iMACAddress;
    uint32_t bmEthernetStatistics;
    uint16_t wMaxSegmentSize;
    uint16_t wNumberMCFilters;
    uint8_t bNumberPowerFilters;
} __packed;

#ifdef __cplusplus
}
#endif

