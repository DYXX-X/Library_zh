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

#ifndef __ESP_BT_DEFS_H__
#define __ESP_BT_DEFS_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_BLUEDROID_STATUS_CHECK(status)           \
    if (esp_bluedroid_get_status() != (status)) {    \
        return ESP_ERR_INVALID_STATE;                \
    }


/* 与BT_def中的BT_STATUS_xxx相关。小时*/
///状态返回值
typedef enum {
    ESP_BT_STATUS_SUCCESS       = 0,            /* 与BT_def中的BT_STATUS_SSUCCESS相关。小时*/
    ESP_BT_STATUS_FAIL,                         /* 与BT_def中的BT_STATUS_FAIL相关。小时*/
    ESP_BT_STATUS_NOT_READY,                    /* 与BT_def中的BT_STATUS_NOT_READY相关。小时*/
    ESP_BT_STATUS_NOMEM,                        /* 与BT_def中的BT_STATUS_NOMEM相关。小时*/
    ESP_BT_STATUS_BUSY,                         /* 与BT_def中的BT_STATUS_BUSY相关。小时*/
    ESP_BT_STATUS_DONE          = 5,            /* 与BT_def中的BT_STATUS_DONE相关。小时*/
    ESP_BT_STATUS_UNSUPPORTED,                  /* 与BT_def中的BT_STATUS_UNSUPPORTED相关。小时*/
    ESP_BT_STATUS_PARM_INVALID,                 /* 与BT_def中的BT_STATUS_PARM_INVALID相关。小时*/
    ESP_BT_STATUS_UNHANDLED,                    /* 与BT_def中的BT_STATUS_UNGHANDLED相关。小时*/
    ESP_BT_STATUS_AUTH_FAILURE,                 /* 与BT_def中的BT_STATUS_AUTH_FAILURE相关。小时*/
    ESP_BT_STATUS_RMT_DEV_DOWN  = 10,           /* 与BT_def中的BT_STATUS_RMT_DEV_DOWN相关。小时*/
    ESP_BT_STATUS_AUTH_REJECTED,                /* 与BT_def中的BT_STATUS_AUTH_REJECTED相关。小时*/
    ESP_BT_STATUS_INVALID_STATIC_RAND_ADDR,     /* 与BT_def中的BT_STATUS_INVALID_STATIC_RAND_ADDR相关。小时*/
    ESP_BT_STATUS_PENDING,                      /* 与BT_def中的BT_STATUS_PENDING相关。小时*/
    ESP_BT_STATUS_UNACCEPT_CONN_INTERVAL,       /* 与BT_def中的BT_UNACCEPT_CONN_INTERVAL相关。小时*/
    ESP_BT_STATUS_PARAM_OUT_OF_RANGE,           /* 与BT_def中的BT_PARAM_OUT_OF_RANGE相关。小时*/
    ESP_BT_STATUS_TIMEOUT,                      /* 与BT_def中的BT_STATUS_TIMEOUT相关。小时*/
    ESP_BT_STATUS_PEER_LE_DATA_LEN_UNSUPPORTED, /* 与堆栈/BTM_api中的BTM_PEER_LE_DATA_LEN_UNSUPPORTED相关。小时*/
    ESP_BT_STATUS_CONTROL_LE_DATA_LEN_UNSUPPORTED,/* 与堆栈/BTM_api中的BTM_CONTROL_LE_DATA_LEN_UNSUPPORTED相关。小时*/
    ESP_BT_STATUS_ERR_ILLEGAL_PARAMETER_FMT,    /* 与堆栈/hidefs中的HCI_ERR_ILLEGAL_PARAMETER_FMT相关。小时*/
    ESP_BT_STATUS_MEMORY_FULL   = 20,           /* 与BT_def中的BT_STATUS_MEMORY_FULL相关。小时*/
    ESP_BT_STATUS_EIR_TOO_LARGE,                /* 与BT_def中的BT_STATUS_EIR_TOO_LARGE相关。小时*/
} esp_bt_status_t;


/*定义bt八位字节16位大小*/
#define ESP_BT_OCTET16_LEN    16
typedef uint8_t esp_bt_octet16_t[ESP_BT_OCTET16_LEN];   /* 八位字节数组：大小16*/

#define ESP_BT_OCTET8_LEN    8
typedef uint8_t esp_bt_octet8_t[ESP_BT_OCTET8_LEN];   /* 八位字节数组：大小8*/

typedef uint8_t esp_link_key[ESP_BT_OCTET16_LEN];      /* 链接密钥*/

///默认GATT接口id
#define ESP_DEFAULT_GATT_IF             0xff

#define ESP_BLE_CONN_INT_MIN                0x0006       /*!< 与堆栈/BTM_BLE_api中的BTM_BLE_CONN_INT_MIN相关。小时*/
#define ESP_BLE_CONN_INT_MAX                0x0C80       /*!< 与堆栈/BTM_BLE_api中的BTM_BLE_CONN_INT_MAX相关。小时*/
#define ESP_BLE_CONN_LATENCY_MAX            499          /*!< 与堆栈/btm_BLE_api中的ESP_BLE_CONN_LATENCY_MAX相关。小时*/
#define ESP_BLE_CONN_SUP_TOUT_MIN           0x000A       /*!< 与堆栈/BTM_BLE_api中的BTM_BLE_CONN_SUP_TOUT_MIN相关。小时*/
#define ESP_BLE_CONN_SUP_TOUT_MAX           0x0C80       /*!< 与堆栈/btm_BLE_api中的ESP_BLE_CONN_SUP_TOUT_MAX相关。小时*/
#define ESP_BLE_CONN_PARAM_UNDEF            0xffff       /* 在不覆盖特定值时使用此值*/ /* 与堆栈/btm_BLE_api中的ESP_BLE_CONN_PARAM_UNDEF相关。小时*/
#define ESP_BLE_SCAN_PARAM_UNDEF            0xffffffff   /* 与堆栈/btm_BLE_api中的ESP_BLE_SCAN_PARAM_UNDEF相关。小时*/

///检查参数是否有效
#define ESP_BLE_IS_VALID_PARAM(x, min, max)  (((x) >= (min) && (x) <= (max)) || ((x) == ESP_BLE_CONN_PARAM_UNDEF))

///UUID类型
typedef struct {
#define ESP_UUID_LEN_16     2
#define ESP_UUID_LEN_32     4
#define ESP_UUID_LEN_128    16
    uint16_t len;							/*!< UUID长度，16位、32位或128位*/
    union {
        uint16_t    uuid16;                 /*!< 16位UUID*/
        uint32_t    uuid32;                 /*!< 32位UUID*/
        uint8_t     uuid128[ESP_UUID_LEN_128]; /*!< 128位UUID*/
    } uuid;									/*!< UUID */
} __attribute__((packed)) esp_bt_uuid_t;

///蓝牙设备类型
typedef enum {
    ESP_BT_DEVICE_TYPE_BREDR   = 0x01,
    ESP_BT_DEVICE_TYPE_BLE     = 0x02,
    ESP_BT_DEVICE_TYPE_DUMO    = 0x03,
} esp_bt_dev_type_t;

///蓝牙地址长度
#define ESP_BD_ADDR_LEN     6

///蓝牙设备地址
typedef uint8_t esp_bd_addr_t[ESP_BD_ADDR_LEN];

///BLE设备地址类型
typedef enum {
    BLE_ADDR_TYPE_PUBLIC        = 0x00,
    BLE_ADDR_TYPE_RANDOM        = 0x01,
    BLE_ADDR_TYPE_RPA_PUBLIC    = 0x02,
    BLE_ADDR_TYPE_RPA_RANDOM    = 0x03,
} esp_ble_addr_type_t;

///白名单地址类型
typedef enum {
    BLE_WL_ADDR_TYPE_PUBLIC        = 0x00,
    BLE_WL_ADDR_TYPE_RANDOM        = 0x01,
} esp_ble_wl_addr_type_t;

///用于交换初始化密钥和响应密钥中的加密密钥
#define ESP_BLE_ENC_KEY_MASK    (1 << 0)            /* 与堆栈/BTM_api中的BTM_BLE_ENC_KEY_MASK相关。小时*/
///用于交换初始化密钥和响应密钥中的IRK密钥
#define ESP_BLE_ID_KEY_MASK     (1 << 1)            /* 与堆栈/BTM_api中的BTM_BLE_ID_KEY_MASK相关。小时*/
///用于交换初始化密钥和响应密钥中的CSRK密钥
#define ESP_BLE_CSR_KEY_MASK    (1 << 2)            /* 与堆栈/BTM_api中的BTM_BLE_CSR_KEY_MASK相关。小时*/
///用于在初始化密钥和响应密钥中交换链接密钥（此密钥仅用于BLE&BR/EDR共存模式）
#define ESP_BLE_LINK_KEY_MASK   (1 << 3)            /* 与堆栈/BTM_api中的BTM_BLE_LINK_KEY_MASK相关。小时*/
typedef uint8_t esp_ble_key_mask_t;            /* 密钥掩码类型*/

///应用程序id的最小值
#define ESP_APP_ID_MIN  0x0000
///应用程序id的最大值
#define ESP_APP_ID_MAX  0x7fff

#define ESP_BD_ADDR_STR         "%02x:%02x:%02x:%02x:%02x:%02x"
#define ESP_BD_ADDR_HEX(addr)   addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]

#ifdef __cplusplus
}
#endif

#endif     /* __ESP_BT_DEFS_H__ */

