/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*
此标头包含一些设备类的裸骨骼模拟实现，以便测试USBHost堆栈的各个层。
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "usb/usb_types_ch9.h"

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------- MSC SCSI -------------------------------------------------------

const char *MSC_CLIENT_TAG;

/*
注意：模拟MSC SCSI测试要求连接USB闪存驱动器。闪存驱动器应该。。。

-使用SCSI命令实现仅支持BULK传输的大容量存储类
-它的配置1应该具有以下端点

设备描述符：bLength 18 b描述符类型1 bcdUSB 2.00 b设备类别0 b设备子类0 b设备协议0 bMaxPacketSize0 64 idVendor 0x125f idProduct 0xc08a bcdDevice 1.00 iManufacturer 1 iProduct 2 iSerial 3 bNumConfigurations 1配置描述符：bLength9 b描述符类型2 wTotalLength 0x0020 bNumInterfaces 1 bConfiguration Value 1 iConfiguration 0 bmAttributes 0x80（总线供电）MaxPower 480mA接口描述符：bLength 9 bDescriptor Type 4 bInterfaceNumber 0 b AlternateSetting 0 bNumEndpoints 2 bInterfaceClass 8大容量存储bInterfaceSubClass 6 SCSI bInterfaceProtocol 80 Bulk Only iInterface 0端点描述符：bLength7 bDescriptor Type5 bEndpointAddress 0x01 EP 1 OUT bmAttributes 2传输类型Bulk Synch Type None使用类型数据wMaxPacketSize 0x0040 1x 64字节bInterval 1终结点描述符：bLength 7 bDescriptorType 5 bEndpointAddress 0x82 EP 2 IN bmAttributes 2传输类型批量同步类型无使用类型数据wMaxPacketSize 0x0040 1x 64字节bInterval1

如果您使用具有不同端点的闪存驱动程序，请修改以下端点描述符。
*/

//常量描述符
extern const uint8_t mock_msc_scsi_dev_desc[];
extern const uint8_t mock_msc_scsi_config_desc[];
extern const uint8_t mock_msc_scsi_str_desc_manu[];
extern const uint8_t mock_msc_scsi_str_desc_prod[];
extern const uint8_t mock_msc_scsi_str_desc_ser_num[];
extern const usb_ep_desc_t mock_msc_scsi_bulk_out_ep_desc;
extern const usb_ep_desc_t mock_msc_scsi_bulk_in_ep_desc;

#define MOCK_MSC_SCSI_DEV_ID_VENDOR     0x125F
#define MOCK_MSC_SCSI_DEV_ID_PRODUCT    0xc08A
#define MOCK_MSC_SCSI_DEV_DFLT_EP_MPS   64
#define MOCK_MSC_SCSI_SECTOR_SIZE       512
#define MOCK_MSC_SCSI_LUN               0
#define MOCK_MSC_SCSI_INTF_NUMBER       0
#define MOCK_MSC_SCSI_INTF_ALT_SETTING  0
#define MOCK_MSC_SCSI_BULK_OUT_EP_ADDR  0x01
#define MOCK_MSC_SCSI_BULK_IN_EP_ADDR   0x82
#define MOCK_MSC_SCSI_BULK_EP_MPS       64

#define MOCK_MSC_SCSI_REQ_INIT_RESET(setup_pkt_ptr, intf_num) ({  \
    (setup_pkt_ptr)->bmRequestType = USB_BM_REQUEST_TYPE_DIR_OUT | USB_BM_REQUEST_TYPE_TYPE_CLASS | USB_BM_REQUEST_TYPE_RECIP_INTERFACE; \
    (setup_pkt_ptr)->bRequest = 0xFF;    \
    (setup_pkt_ptr)->wValue = 0; \
    (setup_pkt_ptr)->wIndex = (intf_num);    \
    (setup_pkt_ptr)->wLength = 0;    \
})

typedef struct __attribute__((packed)) {
    uint8_t opcode; //0x28=读取（10），0x2A=写入（10）
    uint8_t flags;
    uint8_t lba_3;
    uint8_t lba_2;
    uint8_t lba_1;
    uint8_t lba_0;
    uint8_t group;
    uint8_t len_1;
    uint8_t len_0;
    uint8_t control;
} mock_scsi_cmd10_t;

typedef struct __attribute__((packed)) {
    uint32_t dCBWSignature;
    uint32_t dCBWTag;
    uint32_t dCBWDataTransferLength;
    uint8_t bmCBWFlags;
    uint8_t bCBWLUN;
    uint8_t bCBWCBLength;
    mock_scsi_cmd10_t CBWCB;
    uint8_t padding[6];
} mock_msc_bulk_cbw_t;

// USB批量传输命令状态包装器数据
typedef struct __attribute__((packed)) {
    uint32_t dCSWSignature;
    uint32_t dCSWTag;
    uint32_t dCSWDataResidue;
    uint8_t bCSWStatus;
} mock_msc_bulk_csw_t;

/**
 * @brief 将MSC命令块包装器（CBW）初始化为SCSI命令
 *
 * @param cbw CBW结构
 * @param is_read 是读取命令
 * @param offset 块偏移量
 * @param num_sectors 要读取的扇区数
 * @param tag 标记（这只是回显
 */
void mock_msc_scsi_init_cbw(mock_msc_bulk_cbw_t *cbw, bool is_read, int offset, int num_sectors, uint32_t tag);

/**
 * @brief 检查返回的命令状态包装器（CSW）是否有效
 *
 * @param csw CSW结构
 * @param tag_expect 应为标记
 * @return 真CSW有效
 * @return 假CSW无效
 */
bool mock_msc_scsi_check_csw(mock_msc_bulk_csw_t *csw, uint32_t tag_expect);

// ----------------------------------------------------HID鼠标------------------------------------------------------


/*
注意：模拟HID鼠标测试需要连接USB低速鼠标。鼠标应该。。。

-使用鼠标使用的标准报告格式实现HID
-它的配置1应该具有以下端点

设备描述符：bLength 18 b描述符类型1 bcdUSB 2.00 b设备类别0 b设备子类0 b设备协议0 bMaxPacketSize0 8 idVendor 0x413c Dell Computer Corp.idProduct 0x301a bcdDevice 1.00 iManufacturer 1 iProduct 2 iSerial 0 bNumConfigurations 1配置描述符：bLength9 b描述符类型2 wTotalLength 0x0022 bNumInterfaces 1 bConfiguration Value 1 iConfiguration 0 bmAttributes0xa0（总线供电）远程唤醒MaxPower 100mA接口描述符：bLength 9 bDescriptor Type 4 bInterfaceNumber 0 bAlternateSetting 0 bNumEndpoints 1 bInterfaceClass 3人机接口设备bInterfaceSubClass 1启动接口子类bInterfaceProtocol 2 Mouse iInterface 0 HID设备描述符：bLength9 b Descriptor Type 33 bcHID 1.11 b国家代码0不支持bNumDescriptor 1b描述符类型34报告wDescriptorLength 46报告描述符：不可用端点描述符：bLength 7 b描述符类型5 b端点地址0x81 EP 1 IN bmAttributes 3传输类型中断同步类型无使用类型数据wMaxPacketSize 0x0004 1x 4字节b间隔10

如果您使用另一个具有不同端点的鼠标，请修改下面的端点描述符
*/

extern  const usb_ep_desc_t mock_hid_mouse_in_ep_desc;

#define MOCK_HID_MOUSE_DEV_ID_VENDOR        0x413C
#define MOCK_HID_MOUSE_DEV_ID_PRODUCT       0x301A
#define MOCK_HID_MOUSE_DEV_DFLT_EP_MPS      8
#define MOCK_HID_MOUSE_INTF_NUMBER          0
#define MOCK_HID_MOUSE_INTF_ALT_SETTING     0
#define MOCK_HID_MOUSE_INTR_IN_EP_ADDR      0x81
#define MOCK_HID_MOUSE_INTR_IN_MPS          0x04

typedef union {
    struct {
        uint32_t left_button: 1;
        uint32_t right_button: 1;
        uint32_t middle_button: 1;
        uint32_t reserved5: 5;
        uint8_t x_movement;
        uint8_t y_movement;
    } __attribute__((packed));
    uint8_t val[3];
} mock_hid_mouse_report_t;
_Static_assert(sizeof(mock_hid_mouse_report_t) == 3, "Size of HID mouse report incorrect");

void mock_hid_process_report(mock_hid_mouse_report_t *report, int iter);

// ----------------------------------------------------模拟ISOC------------------------------------------------------

/*
注意：ISOC测试依赖于使用ISOC OUT传输与不存在的端点进行通信。由于没有为ISOC提供ACK，因此转移到不存在的端点应该是有效的。不存在的端点描述符描述如下：
*/

#define MOCK_ISOC_EP_NUM        2
#define MOCK_ISOC_EP_MPS        512


static const usb_ep_desc_t mock_isoc_out_ep_desc = {
    .bLength = sizeof(usb_ep_desc_t),
    .bDescriptorType = USB_B_DESCRIPTOR_TYPE_ENDPOINT,
    .bEndpointAddress = MOCK_ISOC_EP_NUM,
    .bmAttributes = USB_BM_ATTRIBUTES_XFER_ISOC,
    .wMaxPacketSize = MOCK_ISOC_EP_MPS,     //512字节的MPS
    .bInterval = 1,     //Isoc间隔为（2^（b间隔-1）），表示间隔为1ms
};


#ifdef __cplusplus
}
#endif

