/***************************************************************************
 *
 *
 * 版权所有（c）20152016 Intel Corporation。版权所有（c）2017 PHYTEC Messtechnik GmbH
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * *源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。未经事先书面许可，不得使用“英特尔公司”的名称或其贡献者的名称来支持或推广源自此软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***************************************************************************/

/**
 * @file
 * @brief USB应用程序的有用常量和宏
 *
 * 此文件包含USB应用程序的有用常量和宏。
 */

#pragma once

#include <stdint.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BCD(x) ((((x) / 10) << 4) | ((x) / 10))

/* 描述符大小（字节）*/
#define USB_DEVICE_DESC_SIZE        18
#define USB_CONFIGURATION_DESC_SIZE 9
#define USB_INTERFACE_DESC_SIZE     9
#define USB_ENDPOINT_DESC_SIZE      7
#define USB_STRING_DESC_SIZE        4
#define USB_HID_DESC_SIZE       9
#define USB_DFU_DESC_SIZE       9
#define USB_DEVICE_QUAL_DESC_SIZE   10
#define USB_INTERFACE_ASSOC_DESC_SIZE   8

/* 描述符类型*/
#define USB_DEVICE_DESC         0x01
#define USB_CONFIGURATION_DESC      0x02
#define USB_STRING_DESC         0x03
#define USB_INTERFACE_DESC      0x04
#define USB_ENDPOINT_DESC       0x05
#define USB_DEVICE_QUAL_DESC        0x06
#define USB_INTERFACE_ASSOC_DESC    0x0B
#define USB_DEVICE_CAPABILITY_DESC  0x10
#define USB_HID_DESC            0x21
#define USB_HID_REPORT_DESC     0x22
#define USB_DFU_FUNCTIONAL_DESC     0x21
#define USB_ASSOCIATION_DESC        0x0B
#define USB_BINARY_OBJECT_STORE_DESC    0x0F

/* 有用的定义*/
#define USB_1_1             0x0110
#define USB_2_0             0x0200
/* 将USB版本设置为2.1，以便主机请求BOS描述符*/
#define USB_2_1             0x0210

#define BCDDEVICE_RELNUM        (BCD(KERNEL_VERSION_MAJOR) << 8 | \
                    BCD(KERNEL_VERSION_MINOR))

/* 100mA最大功率，每2mA机组*/
/* USB 1.1规格表示每单位负载100mA（最大值），最多5个负载*/
#define MAX_LOW_POWER           0x32
#define MAX_HIGH_POWER          0xFA

/* bmAttributes：D7：保留，始终为1，D6：自供电->1，D5：远程唤醒->0，D4…0：保留->0
 */
#define USB_CONFIGURATION_ATTRIBUTES    0xC0

/* 类别*/
#define COMMUNICATION_DEVICE_CLASS  0x02
#define COMMUNICATION_DEVICE_CLASS_DATA 0x0A
#define HID_CLASS           0x03
#define MASS_STORAGE_CLASS      0x08
#define WIRELESS_DEVICE_CLASS       0xE0
#define MISC_CLASS          0xEF
#define CUSTOM_CLASS            0xFF
#define DFU_DEVICE_CLASS        0xFE

/* 子类*/
#define CDC_NCM_SUBCLASS        0x0d
#define BOOT_INTERFACE_SUBCLASS     0x01
#define SCSI_TRANSPARENT_SUBCLASS   0x06
#define DFU_INTERFACE_SUBCLASS      0x01
#define RF_SUBCLASS         0x01
#define CUSTOM_SUBCLASS         0xFF
#define COMMON_SUBCLASS         0x02
/* 其他子类*/
#define MISC_RNDIS_SUBCLASS     0x04
#define CDC_ABSTRACT_CONTROL_MODEL 0x02

/* 协议*/
#define V25TER_PROTOCOL         0x01
#define MOUSE_PROTOCOL          0x02
#define BULK_ONLY_PROTOCOL      0x50
#define DFU_RUNTIME_PROTOCOL        0x01
#define DFU_MODE_PROTOCOL       0x02
#define BLUETOOTH_PROTOCOL      0x01
/* CDC ACM协议*/
#define ACM_VENDOR_PROTOCOL     0xFF
/* 其他协议*/
#define MISC_ETHERNET_PROTOCOL      0x01
#define IAD_PROTOCOL            0x01

/**标准设备描述符*/
struct usb_device_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
} __packed;

/**Unicode（UTF16LE）字符串描述符*/
struct usb_string_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bString;
} __packed;

/**关联描述符*/
struct usb_association_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bFirstInterface;
    uint8_t bInterfaceCount;
    uint8_t bFunctionClass;
    uint8_t bFunctionSubClass;
    uint8_t bFunctionProtocol;
    uint8_t iFunction;
} __packed;

/**标准配置描述符*/
struct usb_cfg_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t bMaxPower;
} __packed;

/**标准接口描述符*/
struct usb_if_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} __packed;

/**标准端点描述符*/
struct usb_ep_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
} __packed;

struct string_descriptor_zero {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wBcdLang[];
} __packed;

struct string_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bString[];
} __packed;

#define ROM_MAX_CFG_DESC_CNT 1

struct rom_usb_descriptors {
    const struct usb_device_descriptor *device_descr;
    const void *config_descr[ROM_MAX_CFG_DESC_CNT];
    int string_count; // 包括string_descriptor_zero
    const struct string_descriptor_zero *string0_descr;
    const struct string_descriptor *string_descrs[];
};

/* ROM中定义的描述符*/
extern struct usb_device_descriptor general_device_descr;
extern const void* acm_config_descr;
extern const void* dfu_config_descr;
extern const struct string_descriptor str_manu_descr;
extern const struct string_descriptor str_prod_descr;
extern const struct string_descriptor_zero string0_descr;
extern const struct rom_usb_descriptors acm_usb_descriptors;
extern const struct rom_usb_descriptors dfu_usb_descriptors;
extern const struct rom_usb_descriptors *rom_usb_curr_desc;

/* ROM补丁：使用正确的序列号设置ACM描述符。仅在ESP32-S2上需要，在以后的芯片上，ROM描述符是正确的。
 */
void rom_usb_cdc_set_descriptor_patch(void);


#ifdef __cplusplus
}
#endif

