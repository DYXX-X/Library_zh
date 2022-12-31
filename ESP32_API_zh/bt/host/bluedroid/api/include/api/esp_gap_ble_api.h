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

#ifndef __ESP_GAP_BLE_API_H__
#define __ESP_GAP_BLE_API_H__

#include <stdint.h>
#include <stdbool.h>

#include "esp_err.h"
#include "esp_bt_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@{
 * 用于广告数据标志的BLE_ADV_DATA_FLAG数据标志位定义
 */
#define ESP_BLE_ADV_FLAG_LIMIT_DISC         (0x01 << 0)
#define ESP_BLE_ADV_FLAG_GEN_DISC           (0x01 << 1)
#define ESP_BLE_ADV_FLAG_BREDR_NOT_SPT      (0x01 << 2)
#define ESP_BLE_ADV_FLAG_DMT_CONTROLLER_SPT (0x01 << 3)
#define ESP_BLE_ADV_FLAG_DMT_HOST_SPT       (0x01 << 4)
#define ESP_BLE_ADV_FLAG_NON_LIMIT_DISC     (0x00 )
/**
 * @}
 */

/* 与堆栈/BTM_api中的BTM_LE_KEY_xxx相关。小时*/
#define ESP_LE_KEY_NONE                    0                                                                         /* 与堆栈/BTM_api中的BTM_LE_KEY_NONE相关。小时*/
#define ESP_LE_KEY_PENC                    (1 << 0)   /*!< 加密密钥、对等设备的加密信息*/  /* 与堆栈/BTM_api中的BTM_LE_KEY_PENC相关。小时*/
#define ESP_LE_KEY_PID                     (1 << 1)   /*!< 对等设备的身份密钥*/                        /* 与堆栈/BTM_api中的BTM_LE_KEY_PID相关。小时*/
#define ESP_LE_KEY_PCSRK                   (1 << 2)   /*!< 对等SRK*/                                               /* 与堆栈/BTM_api中的BTM_LE_KEY_PCSRK相关。小时*/
#define ESP_LE_KEY_PLK                     (1 << 3)   /*!< 链接键*/                                                /* 与堆栈/BTM_api中的BTM_LE_KEY_PLK相关。小时*/
#define ESP_LE_KEY_LLK                     (ESP_LE_KEY_PLK << 4)                                                     /* 与堆栈/BTM_api中的BTM_LE_KEY_LLK相关。小时*/
#define ESP_LE_KEY_LENC                    (ESP_LE_KEY_PENC << 4)   /*!< 主角色安全信息：div*/     /* 与堆栈/BTM_api中的BTM_LE_KEY_LENC相关。小时*/
#define ESP_LE_KEY_LID                     (ESP_LE_KEY_PID << 4)    /*!< 主设备ID密钥*/                     /* 与堆栈/BTM_api中的BTM_LE_KEY_LID相关。小时*/
#define ESP_LE_KEY_LCSRK                   (ESP_LE_KEY_PCSRK << 4)  /*!< 本地CSRK已交付给同行*/      /* 与堆栈/BTM_api中的BTM_LE_KEY_LCSRK相关。小时*/
typedef uint8_t esp_ble_key_type_t;

/* 与堆栈/BTM_api中的BTM_LE_AUTH_xxx相关。小时*/
#define ESP_LE_AUTH_NO_BOND                 0x00                                     /*!< 0*/                     /* 与堆栈/BTM_api中的BTM_LE_AUTH_NO_BOND相关。小时*/
#define ESP_LE_AUTH_BOND                    0x01                                     /*!< 1 << 0 */               /* 与堆栈/BTM_api中的BTM_LE_AUTH_BOND相关。小时*/
#define ESP_LE_AUTH_REQ_MITM                (1 << 2)                                 /*!< 1 << 2 */               /* 与堆栈/BTM_api中的BTM_LE_AUTH_REQ_MITM相关。小时*/
#define ESP_LE_AUTH_REQ_BOND_MITM           (ESP_LE_AUTH_BOND | ESP_LE_AUTH_REQ_MITM)/*!< 0101*/
#define ESP_LE_AUTH_REQ_SC_ONLY             (1 << 3)                                 /*!< 1 << 3 */               /* 与堆栈/BTM_api中的BTM_LE_AUTH_REQ_SC_ONLY相关。小时*/
#define ESP_LE_AUTH_REQ_SC_BOND             (ESP_LE_AUTH_BOND | ESP_LE_AUTH_REQ_SC_ONLY)            /*!< 1001 */  /* 与堆栈/BTM_api中的BTM_LE_AUTH_REQ_SC_BOND相关。小时*/
#define ESP_LE_AUTH_REQ_SC_MITM             (ESP_LE_AUTH_REQ_MITM | ESP_LE_AUTH_REQ_SC_ONLY)        /*!< 1100 */  /* 与堆栈/BTM_api中的BTM_LE_AUTH_REQ_SC_MITM相关。小时*/
#define ESP_LE_AUTH_REQ_SC_MITM_BOND        (ESP_LE_AUTH_REQ_MITM | ESP_LE_AUTH_REQ_SC_ONLY | ESP_LE_AUTH_BOND)   /*!< 1101 */  /* 与堆栈/BTM_api中的BTM_LE_AUTH_REQ_SC_MITM_BOND相关。小时*/
typedef uint8_t   esp_ble_auth_req_t;         /*!< 上述位模式的组合*/

#define ESP_BLE_ONLY_ACCEPT_SPECIFIED_AUTH_DISABLE 0
#define ESP_BLE_ONLY_ACCEPT_SPECIFIED_AUTH_ENABLE  1

#define ESP_BLE_OOB_DISABLE 0
#define ESP_BLE_OOB_ENABLE  1

/* 与堆栈/BTM_api中的BTM_IO_CAP_xxx相关。小时*/
#define ESP_IO_CAP_OUT                      0   /*!< 仅显示*/         /* 与堆栈/BTM_api中的BTM_IO_CAP_OUT相关。小时*/
#define ESP_IO_CAP_IO                       1   /*!< 显示是否*/        /* 与堆栈/BTM_api中的BTM_IO_CAP_IO相关。小时*/
#define ESP_IO_CAP_IN                       2   /*!< 仅键盘*/        /* 与堆栈/BTM_api中的BTM_IO_CAP_IN相关。小时*/
#define ESP_IO_CAP_NONE                     3   /*!< 无输入无输出*/     /* 与堆栈/BTM_api中的BTM_IO_CAP_NONE相关。小时*/
#define ESP_IO_CAP_KBDISP                   4   /*!< 键盘显示器*/    /* 与堆栈/BTM_api中的BTM_IO_CAP_KBDISP相关。小时*/

#define ESP_BLE_APPEARANCE_UNKNOWN                 0x0000 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_UNKNOWN相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_PHONE           0x0040 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_PHONE相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_COMPUTER        0x0080 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_COMPUTER相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_WATCH           0x00C0 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_WATCH相关。小时*/
#define ESP_BLE_APPEARANCE_SPORTS_WATCH            0x00C1 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_SPORTS_WATCH相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_CLOCK           0x0100 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_CLOCK相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_DISPLAY         0x0140 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_DISPLAY相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_REMOTE          0x0180 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_REMOTE相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_EYEGLASSES      0x01C0 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_EYEGLASSES相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_TAG             0x0200 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_TAG相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_KEYRING         0x0240 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_KEYRING相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_MEDIA_PLAYER    0x0280 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_MEDIA_PLAYER相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_BARCODE_SCANNER 0x02C0 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_BARCODE_SCANNER相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_THERMOMETER     0x0300 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_THERMOMETER相关。小时*/
#define ESP_BLE_APPEARANCE_THERMOMETER_EAR         0x0301 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_THERMOMETER_EAR相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_HEART_RATE      0x0340 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_HEART_RATE相关。小时*/
#define ESP_BLE_APPEARANCE_HEART_RATE_BELT         0x0341 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_HEART_RATE_BELT相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_BLOOD_PRESSURE  0x0380 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_BLOOD_PRESSURE相关。小时*/
#define ESP_BLE_APPEARANCE_BLOOD_PRESSURE_ARM      0x0381 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_BLOOD_PRESSURE_ARM相关。小时*/
#define ESP_BLE_APPEARANCE_BLOOD_PRESSURE_WRIST    0x0382 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_BLOOD_PRESSURE_RIST相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_HID             0x03C0 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_HID相关。小时*/
#define ESP_BLE_APPEARANCE_HID_KEYBOARD            0x03C1 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_HID_KEYBOARD相关。小时*/
#define ESP_BLE_APPEARANCE_HID_MOUSE               0x03C2 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_HID_MOUSE相关。小时*/
#define ESP_BLE_APPEARANCE_HID_JOYSTICK            0x03C3 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_HID_JOYSTICK相关。小时*/
#define ESP_BLE_APPEARANCE_HID_GAMEPAD             0x03C4 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_HID_GAMEPAD相关。小时*/
#define ESP_BLE_APPEARANCE_HID_DIGITIZER_TABLET    0x03C5 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_HID_DIGITIZER_TABLET相关。小时*/
#define ESP_BLE_APPEARANCE_HID_CARD_READER         0x03C6 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_HID_CARD_READER相关。小时*/
#define ESP_BLE_APPEARANCE_HID_DIGITAL_PEN         0x03C7 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_HID_DIGITAL_PEN相关。小时*/
#define ESP_BLE_APPEARANCE_HID_BARCODE_SCANNER     0x03C8 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_HID_BARCODE_SCANNER相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_GLUCOSE         0x0400 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_GLUCOSE相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_WALKING         0x0440 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_WALKING相关。小时*/
#define ESP_BLE_APPEARANCE_WALKING_IN_SHOE         0x0441 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_WALKING_IN_SHOE相关。小时*/
#define ESP_BLE_APPEARANCE_WALKING_ON_SHOE         0x0442 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_WALKING_ON_SHOE相关。小时*/
#define ESP_BLE_APPEARANCE_WALKING_ON_HIP          0x0443 /* 与堆栈/BTM_BLE_api.h中的BTM_BLE_APPERANCE_WALKING_ON_HIP相关*/
#define ESP_BLE_APPEARANCE_GENERIC_CYCLING         0x0480 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_CYCLING相关。小时*/
#define ESP_BLE_APPEARANCE_CYCLING_COMPUTER        0x0481 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_CYCLING_COMPUTER相关。小时*/
#define ESP_BLE_APPEARANCE_CYCLING_SPEED           0x0482 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_CYCLING_SPEED相关。小时*/
#define ESP_BLE_APPEARANCE_CYCLING_CADENCE         0x0483 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_CYCLING_CADENCE相关。小时*/
#define ESP_BLE_APPEARANCE_CYCLING_POWER           0x0484 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_CYCLING_POWER相关。小时*/
#define ESP_BLE_APPEARANCE_CYCLING_SPEED_CADENCE   0x0485 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_CYCLING_SPEED_CADENCE相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_PULSE_OXIMETER  0x0C40 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_PULSE_OXIIMETER相关。小时*/
#define ESP_BLE_APPEARANCE_PULSE_OXIMETER_FINGERTIP 0x0C41 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_PULSE_OXIMETER_FINGERTIP相关。小时*/
#define ESP_BLE_APPEARANCE_PULSE_OXIMETER_WRIST    0x0C42 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_PULSE_OXIIMETER_WRIST相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_WEIGHT          0x0C80 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_WEIGHT相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_PERSONAL_MOBILITY_DEVICE    0x0CC0 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_PERSONAL_MOBILITY_DEVICE相关。小时*/
#define ESP_BLE_APPEARANCE_POWERED_WHEELCHAIR                  0x0CC1 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_POWERED_WHEECHAIR相关。小时*/
#define ESP_BLE_APPEARANCE_MOBILITY_SCOOTER                    0x0CC2 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_MOBILITY_SCOOTER相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_CONTINUOUS_GLUCOSE_MONITOR  0x0D00 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPEARANCE_GENERIC_CONTINUOUS_GLUCOSE_MONITOR相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_INSULIN_PUMP                0x0D40 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_INSULIN_PUMP相关。小时*/
#define ESP_BLE_APPEARANCE_INSULIN_PUMP_DURABLE_PUMP           0x0D41 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_INSULIN_PUMP_DURABLE_PUMP相关。小时*/
#define ESP_BLE_APPEARANCE_INSULIN_PUMP_PATCH_PUMP             0x0D44 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_INSULIN_PUMP_PATCH_PUMP相关。小时*/
#define ESP_BLE_APPEARANCE_INSULIN_PEN                         0x0D48 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_INSULIN_PEN相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_MEDICATION_DELIVERY         0x0D80 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_MEDICATION_DELIVERY相关。小时*/
#define ESP_BLE_APPEARANCE_GENERIC_OUTDOOR_SPORTS  0x1440             /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_GENERIC_OUTDOOR_SPORTS相关。小时*/
#define ESP_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION 0x1441             /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_OUTDOOR_SPORTS_LOCATION相关。小时*/
#define ESP_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION_AND_NAV     0x1442 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_OUTDOOR_SPORTS_LOCATION_AND_NAV相关。小时*/
#define ESP_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION_POD         0x1443 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_OUTDOOR_SPORTS_LOCATION_POD相关。小时*/
#define ESP_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION_POD_AND_NAV 0x1444 /* 与堆栈/BTM_BLE_api中的BTM_BLE_APPERANCE_OUTDOOR_SPORTS_LOCATION_POD_AND_NAV相关。小时*/

typedef uint8_t esp_ble_io_cap_t;               /*!< io能力的组合*/

///GAP BLE回调事件类型
typedef enum {
#if (BLE_42_FEATURE_SUPPORT == TRUE)
    ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT        = 0,       /*!< 当广告数据集完成时，事件发生*/
    ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT,             /*!< 当扫描响应数据集完成时，事件发生*/
    ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT,                /*!< 当扫描参数设置完成时，事件发生*/
    ESP_GAP_BLE_SCAN_RESULT_EVT,                            /*!< 当一个扫描结果就绪时，每次都会出现事件*/
    ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT,              /*!< 当原始广告数据集完成时，事件发生*/
    ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT,         /*!< 当原始广告数据集完成时，事件发生*/
    ESP_GAP_BLE_ADV_START_COMPLETE_EVT,                     /*!< 当开始广告完成时，事件发生*/
    ESP_GAP_BLE_SCAN_START_COMPLETE_EVT,                    /*!< 当开始扫描完成时，事件发生*/
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）
    ESP_GAP_BLE_AUTH_CMPL_EVT = 8,                          /* 认证完成指示。*/
    ESP_GAP_BLE_KEY_EVT,                                    /* 对等设备密钥的BLE密钥事件*/
    ESP_GAP_BLE_SEC_REQ_EVT,                                /* BLE安全请求*/
    ESP_GAP_BLE_PASSKEY_NOTIF_EVT,                          /* 密钥通知事件*/
    ESP_GAP_BLE_PASSKEY_REQ_EVT,                            /* 密钥请求事件*/
    ESP_GAP_BLE_OOB_REQ_EVT,                                /* OOB请求事件*/
    ESP_GAP_BLE_LOCAL_IR_EVT,                               /* BLE本地IR事件*/
    ESP_GAP_BLE_LOCAL_ER_EVT,                               /* BLE本地ER事件*/
    ESP_GAP_BLE_NC_REQ_EVT,                                 /* 数字比较请求事件*/
#if (BLE_42_FEATURE_SUPPORT == TRUE)
    ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT,                      /*!< 当stop adv完成时，事件发生*/
    ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT,                     /*!< 停止扫描完成后，事件发生*/
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）
    ESP_GAP_BLE_SET_STATIC_RAND_ADDR_EVT = 19,              /*!< 当设置静态rand地址完成时，事件发生*/
    ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT,                     /*!< 当更新连接参数完成时，事件发生*/
    ESP_GAP_BLE_SET_PKT_LENGTH_COMPLETE_EVT,                /*!< 当设置pkt长度完成时，事件发生*/
    ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT,             /*!< 在本地设备上启用/禁用隐私时，事件发生*/
    ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT,               /*!< 当移除键合装置完成时，事件发生*/
    ESP_GAP_BLE_CLEAR_BOND_DEV_COMPLETE_EVT,                /*!< 当清除键合装置清除完成时，事件发生*/
    ESP_GAP_BLE_GET_BOND_DEV_COMPLETE_EVT,                  /*!< 当绑定设备列表完成时，事件发生*/
    ESP_GAP_BLE_READ_RSSI_COMPLETE_EVT,                     /*!< 当读取rssi完成时，事件发生*/
    ESP_GAP_BLE_UPDATE_WHITELIST_COMPLETE_EVT,              /*!< 添加或删除白名单完成后，事件发生*/
#if (BLE_42_FEATURE_SUPPORT == TRUE)
    ESP_GAP_BLE_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_COMPLETE_EVT,  /*!< 当更新重复异常列表完成时，事件发生*/
#endif //#如果（BLE_42_FEATURE_SUPPORT==真）
    ESP_GAP_BLE_SET_CHANNELS_EVT = 29,                           /*!< 当BLE通道设置完成时，事件发生*/
#if (BLE_50_FEATURE_SUPPORT == TRUE)
    ESP_GAP_BLE_READ_PHY_COMPLETE_EVT,
    ESP_GAP_BLE_SET_PREFERED_DEFAULT_PHY_COMPLETE_EVT,
    ESP_GAP_BLE_SET_PREFERED_PHY_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_ADV_SET_RAND_ADDR_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_ADV_SET_PARAMS_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_ADV_DATA_SET_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_SCAN_RSP_DATA_SET_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_ADV_START_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_ADV_STOP_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_ADV_SET_REMOVE_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_ADV_SET_CLEAR_COMPLETE_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_SET_PARAMS_COMPLETE_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_DATA_SET_COMPLETE_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_START_COMPLETE_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_STOP_COMPLETE_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_CREATE_SYNC_COMPLETE_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_SYNC_CANCEL_COMPLETE_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_SYNC_TERMINATE_COMPLETE_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_ADD_DEV_COMPLETE_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_REMOVE_DEV_COMPLETE_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_CLEAR_DEV_COMPLETE_EVT,
    ESP_GAP_BLE_SET_EXT_SCAN_PARAMS_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_SCAN_START_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_SCAN_STOP_COMPLETE_EVT,
    ESP_GAP_BLE_PREFER_EXT_CONN_PARAMS_SET_COMPLETE_EVT,
    ESP_GAP_BLE_PHY_UPDATE_COMPLETE_EVT,
    ESP_GAP_BLE_EXT_ADV_REPORT_EVT,
    ESP_GAP_BLE_SCAN_TIMEOUT_EVT,
    ESP_GAP_BLE_ADV_TERMINATED_EVT,
    ESP_GAP_BLE_SCAN_REQ_RECEIVED_EVT,
    ESP_GAP_BLE_CHANNEL_SELETE_ALGORITHM_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_REPORT_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_SYNC_LOST_EVT,
    ESP_GAP_BLE_PERIODIC_ADV_SYNC_ESTAB_EVT,
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）
    ESP_GAP_BLE_EVT_MAX,
} esp_gap_ble_cb_event_t;

#define ESP_GAP_BLE_CHANNELS_LEN     5
typedef uint8_t esp_gap_ble_channels[ESP_GAP_BLE_CHANNELS_LEN];

///这是旧名称，只是为了向后兼容
#define ESP_GAP_BLE_ADD_WHITELIST_COMPLETE_EVT ESP_GAP_BLE_UPDATE_WHITELIST_COMPLETE_EVT

///广告数据最大长度
#define ESP_BLE_ADV_DATA_LEN_MAX               31
///扫描响应数据最大长度
#define ESP_BLE_SCAN_RSP_DATA_LEN_MAX          31

/* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_xxx相关。小时*/
///广告数据的类型（不是adv_type）
typedef enum {
    ESP_BLE_AD_TYPE_FLAG                     = 0x01,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_FLAG相关。小时*/
    ESP_BLE_AD_TYPE_16SRV_PART               = 0x02,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_16SRV_PART相关。小时*/
    ESP_BLE_AD_TYPE_16SRV_CMPL               = 0x03,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_16SRV_CMPL相关。小时*/
    ESP_BLE_AD_TYPE_32SRV_PART               = 0x04,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_32SRV_PART相关。小时*/
    ESP_BLE_AD_TYPE_32SRV_CMPL               = 0x05,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_32SRV_CMPL相关。小时*/
    ESP_BLE_AD_TYPE_128SRV_PART              = 0x06,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_128SRV_PART相关。小时*/
    ESP_BLE_AD_TYPE_128SRV_CMPL              = 0x07,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_128SRV_CMPL相关。小时*/
    ESP_BLE_AD_TYPE_NAME_SHORT               = 0x08,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_NAME_SHORT相关。小时*/
    ESP_BLE_AD_TYPE_NAME_CMPL                = 0x09,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_NAME_CMPL相关。小时*/
    ESP_BLE_AD_TYPE_TX_PWR                   = 0x0A,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_TX_PWR相关。小时*/
    ESP_BLE_AD_TYPE_DEV_CLASS                = 0x0D,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_DEV_CLASS相关。小时*/
    ESP_BLE_AD_TYPE_SM_TK                    = 0x10,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_SM_TK相关。小时*/
    ESP_BLE_AD_TYPE_SM_OOB_FLAG              = 0x11,    /* 与堆栈/BTM_BLE_api.h中的BTM_BLE_AD_TYPE_SM_OOB_FLAG相关*/
    ESP_BLE_AD_TYPE_INT_RANGE                = 0x12,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_INT_RANGE相关。小时*/
    ESP_BLE_AD_TYPE_SOL_SRV_UUID             = 0x14,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_SOL_SRV_UUID相关。小时*/
    ESP_BLE_AD_TYPE_128SOL_SRV_UUID          = 0x15,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_128SOL_SRV_UUID相关。小时*/
    ESP_BLE_AD_TYPE_SERVICE_DATA             = 0x16,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_SERVICE_DATA相关。小时*/
    ESP_BLE_AD_TYPE_PUBLIC_TARGET            = 0x17,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_PUBLIC_TARGET相关。小时*/
    ESP_BLE_AD_TYPE_RANDOM_TARGET            = 0x18,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_RANDOM_TARGET相关。小时*/
    ESP_BLE_AD_TYPE_APPEARANCE               = 0x19,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_APPARANCE相关。小时*/
    ESP_BLE_AD_TYPE_ADV_INT                  = 0x1A,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_ADV_INT相关。小时*/
    ESP_BLE_AD_TYPE_LE_DEV_ADDR              = 0x1b,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_LE_DEV_ADDR相关。小时*/
    ESP_BLE_AD_TYPE_LE_ROLE                  = 0x1c,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_LE_ROLE相关。小时*/
    ESP_BLE_AD_TYPE_SPAIR_C256               = 0x1d,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_SPAIR_C256相关。小时*/
    ESP_BLE_AD_TYPE_SPAIR_R256               = 0x1e,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_SPAIR_R256相关。小时*/
    ESP_BLE_AD_TYPE_32SOL_SRV_UUID           = 0x1f,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_32SOL_SRV_UUID相关。小时*/
    ESP_BLE_AD_TYPE_32SERVICE_DATA           = 0x20,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_32SERVICE_DATA相关。小时*/
    ESP_BLE_AD_TYPE_128SERVICE_DATA          = 0x21,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_128SERVICE_DATA相关。小时*/
    ESP_BLE_AD_TYPE_LE_SECURE_CONFIRM        = 0x22,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_LE_SECURE_CONFIRM相关。小时*/
    ESP_BLE_AD_TYPE_LE_SECURE_RANDOM         = 0x23,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_LE_SECURE_RANDOM相关。小时*/
    ESP_BLE_AD_TYPE_URI                      = 0x24,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_URI相关。小时*/
    ESP_BLE_AD_TYPE_INDOOR_POSITION          = 0x25,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_INDOR_POSITION相关。小时*/
    ESP_BLE_AD_TYPE_TRANS_DISC_DATA          = 0x26,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_TRANS_DISC_DATA相关。小时*/
    ESP_BLE_AD_TYPE_LE_SUPPORT_FEATURE       = 0x27,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_LE_SUPPORT_FEATURE相关。小时*/
    ESP_BLE_AD_TYPE_CHAN_MAP_UPDATE          = 0x28,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_TYPE_CHAN_MAP_UPDATE相关。小时*/
    ESP_BLE_AD_MANUFACTURER_SPECIFIC_TYPE    = 0xFF,    /* 与堆栈/BTM_BLE_api中的BTM_BLE_AD_MANUFACTURER_SPECIFIC_TYPE相关。小时*/
} esp_ble_adv_data_type;

///广告模式
typedef enum {
    ADV_TYPE_IND                = 0x00,
    ADV_TYPE_DIRECT_IND_HIGH    = 0x01,
    ADV_TYPE_SCAN_IND           = 0x02,
    ADV_TYPE_NONCONN_IND        = 0x03,
    ADV_TYPE_DIRECT_IND_LOW     = 0x04,
} esp_ble_adv_type_t;

///广告频道掩码
typedef enum {
    ADV_CHNL_37     = 0x01,
    ADV_CHNL_38     = 0x02,
    ADV_CHNL_39     = 0x04,
    ADV_CHNL_ALL    = 0x07,
} esp_ble_adv_channel_t;

typedef enum {
    ///允许来自任何人的扫描和连接请求
    ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY  = 0x00,
    ///仅允许来自白名单设备的扫描请求和来自任何人的连接请求
    ADV_FILTER_ALLOW_SCAN_WLST_CON_ANY,
    ///仅允许任何人的扫描请求和白名单设备的连接请求
    ADV_FILTER_ALLOW_SCAN_ANY_CON_WLST,
    ///仅允许来自白名单设备的扫描和连接请求
    ADV_FILTER_ALLOW_SCAN_WLST_CON_WLST,
    ///广告筛选器策略值检查的枚举结束值
} esp_ble_adv_filter_t;


/* 与BTA/BTA_api中的BTA_DM_BLE_SEC_xxx相关。小时*/
typedef enum {
    ESP_BLE_SEC_ENCRYPT = 1,            /* 与BTA/BTA_api.h中的BTA_DM_BLE_SEC_ENCRYPT相关。如果设备已经绑定，堆栈将使用LTK直接与远程设备进行加密。否则，如果设备未绑定，堆栈将使用用户设置的esp_ble_gap_set_security_param函数的默认身份验证请求。*/
    ESP_BLE_SEC_ENCRYPT_NO_MITM,        /* 与BTA/BTA_api.h中的BTA_DM_BLE_SEC_ENCRYPT_NO_MITM相关。如果设备已绑定，则堆栈将检查LTK是否满足验证请求，如果满足，则使用LTK直接与远程设备加密，否则与远程设备重新配对。否则，如果设备未绑定，堆栈将在当前链接中使用NO MITM身份验证请求，而不是在用户设置的esp_ble_gap_set_security_param函数中使用authreq。*/
    ESP_BLE_SEC_ENCRYPT_MITM,           /* 与BTA/BTA_api.h中的BTA_DM_BLE_SEC_ENCRYPT_MITM相关。如果设备已绑定，则堆栈将检查LTK是否满足验证请求，如果满足，则使用LTK直接与远程设备加密，否则与远程设备重新配对。否则，如果设备尚未绑定，堆栈将在当前链接中使用MITM身份验证请求，而不是在用户设置的esp_ble_gap_set_security_param函数中使用authreq。*/
}esp_ble_sec_act_t;

typedef enum {
    ESP_BLE_SM_PASSKEY = 0,
    /* 本地设备的认证要求*/
    ESP_BLE_SM_AUTHEN_REQ_MODE,
    /* 本地设备的IO能力*/
    ESP_BLE_SM_IOCAP_MODE,
    /* 启动器密钥分发/生成*/
    ESP_BLE_SM_SET_INIT_KEY,
    /* 响应程序密钥分发/生成*/
    ESP_BLE_SM_SET_RSP_KEY,
    /* 要支持的最大加密密钥大小*/
    ESP_BLE_SM_MAX_KEY_SIZE,
    /* 对等方的最小加密密钥大小要求*/
    ESP_BLE_SM_MIN_KEY_SIZE,
    /* 设置静态密钥*/
    ESP_BLE_SM_SET_STATIC_PASSKEY,
    /* 重置静态密钥*/
    ESP_BLE_SM_CLEAR_STATIC_PASSKEY,
    /* 仅接受指定的SMP身份验证要求*/
    ESP_BLE_SM_ONLY_ACCEPT_SPECIFIED_SEC_AUTH,
    /* 启用/禁用OOB支持*/
    ESP_BLE_SM_OOB_SUPPORT,
    /* 应用加密密钥大小*/
    ESP_BLE_APP_ENC_KEY_SIZE,
    ESP_BLE_SM_MAX_PARAM,
} esp_ble_sm_param_t;

#if (BLE_42_FEATURE_SUPPORT == TRUE)
///广告参数
typedef struct {
    uint16_t                adv_int_min;        /*!< 无定向和低占空比定向广告的最小广告间隔。范围：0x0020到0x4000默认值：N=0x0800（1.28秒）时间=N*0.625毫秒时间范围：20毫秒到10.24秒*/
    uint16_t                adv_int_max;        /*!< 无定向和低占空比定向广告的最大广告间隔。范围：0x0020到0x4000默认值：N=0x0800（1.28秒）时间=N 0.625毫秒时间范围：20毫秒到10.24秒广告最大间隔*/
    esp_ble_adv_type_t      adv_type;           /*!< 广告类型*/
    esp_ble_addr_type_t     own_addr_type;      /*!< 所有者蓝牙设备地址类型*/
    esp_bd_addr_t           peer_addr;          /*!< 对等设备蓝牙设备地址*/
    esp_ble_addr_type_t     peer_addr_type;     /*!< 对等设备蓝牙设备地址类型，仅支持公共地址类型和随机地址类型*/
    esp_ble_adv_channel_t   channel_map;        /*!< 广告渠道图*/
    esp_ble_adv_filter_t    adv_filter_policy;  /*!< 广告筛选策略*/
} esp_ble_adv_params_t;

///广告数据内容，根据“蓝牙核心规范补充”
typedef struct {
    bool                    set_scan_rsp;           /*!< 是否将此广告数据设置为扫描响应*/
    bool                    include_name;           /*!< 广告数据是否包含设备名称*/
    bool                    include_txpower;        /*!< 广告数据包括TX功率*/
    int                     min_interval;           /*!< 广告数据显示从属首选连接最小间隔。连接间隔如下：connIntervalmin=Conn_interval_Min 1.25 ms Conn_interval _Min范围：0x0006到0x0C80 0xFFFF值表示没有特定的最小值。以上未定义的值保留供将来使用。*/

    int                     max_interval;           /*!< 广告数据显示从属首选连接最大间隔。以下方式的连接间隔：connIntervalmax=Conn_interval_Max 1.25 ms Conn_interval _Max范围：0x0006至0x0C80 Conn_interval_Max应等于或大于Conn_interval_Min。值0xFFFF表示没有特定的最大值。以上未定义的值保留供将来使用。*/

    int                     appearance;             /*!< 设备外观*/
    uint16_t                manufacturer_len;       /*!< 制造商数据长度*/
    uint8_t                 *p_manufacturer_data;   /*!< 制造商数据点*/
    uint16_t                service_data_len;       /*!< 服务数据长度*/
    uint8_t                 *p_service_data;        /*!< 服务数据点*/
    uint16_t                service_uuid_len;       /*!< 服务uuid长度*/
    uint8_t                 *p_service_uuid;        /*!< 服务uuid阵列点*/
    uint8_t                 flag;                   /*!< 发现模式的广告标志，请参阅BLE_ADV_DATA_flag详细信息*/
} esp_ble_adv_data_t;

#endif // #如果（BLE_42_FEATURE_SUPPORT==真）

///Ble扫描类型
typedef enum {
    BLE_SCAN_TYPE_PASSIVE   =   0x0,            /*!< 被动扫描*/
    BLE_SCAN_TYPE_ACTIVE    =   0x1,            /*!< 活动扫描*/
} esp_ble_scan_type_t;

///Ble扫描过滤器类型
typedef enum {
    BLE_SCAN_FILTER_ALLOW_ALL           = 0x0,  /*!< 接受所有：1.广告数据包，但定向广告数据包除外，不寻址到此设备（默认）。*/
    BLE_SCAN_FILTER_ALLOW_ONLY_WLST     = 0x1,  /*!< 仅接受：1.来自广告主地址在白名单中的设备的广告包。2.应忽略未针对该设备寻址的定向广告包。*/
    BLE_SCAN_FILTER_ALLOW_UND_RPA_DIR   = 0x2,  /*!< 接受所有：1.无定向广告包，2.定向广告包（其中启动器地址是可解析的私有地址），3.定向广告包寻址到此设备。*/
    BLE_SCAN_FILTER_ALLOW_WLIST_RPA_DIR = 0x3,  /*!< 接受所有：1.来自广告商地址在白名单中的设备的广告包，2.定向广告包，其中发起者地址是可解析的私有地址，以及3.定向广告包。*/
} esp_ble_scan_filter_t;

///Ble扫描重复类型
typedef enum {
    BLE_SCAN_DUPLICATE_DISABLE           = 0x0,  /*!< 链路层应为接收到的每个数据包向主机生成广告报告*/
    BLE_SCAN_DUPLICATE_ENABLE            = 0x1,  /*!< 链接层应过滤出向主机发送的重复广告报告*/
    BLE_SCAN_DUPLICATE_MAX               = 0x2,  /*!< 0x02–0xFF，保留以备将来使用*/
} esp_ble_scan_duplicate_t;
#if (BLE_42_FEATURE_SUPPORT == TRUE)
///Ble扫描参数
typedef struct {
    esp_ble_scan_type_t     scan_type;              /*!< 扫描类型*/
    esp_ble_addr_type_t     own_addr_type;          /*!< 所有者地址类型*/
    esp_ble_scan_filter_t   scan_filter_policy;     /*!< 扫描筛选器策略*/
    uint16_t                scan_interval;          /*!< 扫描间隔。这被定义为从控制器开始其最后一次LE扫描到开始后续LE扫描的时间间隔。范围：0x0004到0x4000默认值：0x0010（10毫秒）时间=N 0.625毫秒时间范围：2.5毫秒到10.24秒*/
    uint16_t                scan_window;            /*!< 扫描窗口。LE扫描的持续时间。LE_Scan_Window应小于或等于LE_Scan_Interval Range：0x0004至0x4000默认值：0x0010（10毫秒）时间=N 0.625毫秒时间范围：2.5毫秒至10240毫秒*/
    esp_ble_scan_duplicate_t  scan_duplicate;       /*!< Scan_Duplicates参数控制链路层是否应过滤出主机的重复广告报告（BLE_Scan_duplicate_ENABLE），或者链路层是否应该为接收到的每个数据包生成广告报告*/
} esp_ble_scan_params_t;
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）
///连接参数信息
typedef struct {
    uint16_t             interval;                  /*!< 连接间隔*/
    uint16_t             latency;                   /*!< 连接的从属延迟（以连接事件数表示）。范围：0x0000到0x01F3*/
    uint16_t             timeout;                   /*!< LE链路的监控超时。范围：0x000A到0x0C80。强制范围：0x000A-0x0C80时间=N 10毫秒时间范围：100毫秒到32秒*/
} esp_gap_conn_params_t;

///连接更新参数
typedef struct {
    esp_bd_addr_t bda;                              /*!< 蓝牙设备地址*/
    uint16_t min_int;                               /*!< 最小连接间隔*/
    uint16_t max_int;                               /*!< 最大连接间隔*/
    uint16_t latency;                               /*!< 连接的从属延迟（以连接事件数表示）。范围：0x0000到0x01F3*/
    uint16_t timeout;                               /*!< LE链路的监控超时。范围：0x000A到0x0C80。强制范围：0x000A-0x0C80时间=N 10毫秒时间范围：100毫秒到32秒*/
} esp_ble_conn_update_params_t;

/**
* @brief BLE pkt日期长度键
*/
typedef struct
{
    uint16_t rx_len;                   /*!< pkt rx数据长度值*/
    uint16_t tx_len;                   /*!< pkt tx数据长度值*/
} esp_ble_pkt_data_length_params_t;

/**
* @brief BLE加密密钥
*/
typedef struct
{
    esp_bt_octet16_t     ltk;          /*!< 长期关键*/
    esp_bt_octet8_t      rand;         /*!< 随机数*/
    uint16_t             ediv;         /*!< ediv值*/
    uint8_t              sec_level;    /*!< 安全链接的安全级别*/
    uint8_t              key_size;     /*!< 安全链接的密钥大小（7~16）*/
} esp_ble_penc_keys_t;                 /*!< 密钥类型*/

/**
* @brief  BLE CSRK键
*/
typedef struct
{
    uint32_t            counter;      /*!< 计数器*/
    esp_bt_octet16_t    csrk;         /*!< csrk键*/
    uint8_t             sec_level;    /*!< 安全级别*/
} esp_ble_pcsrk_keys_t;               /*!< pcsrk密钥类型*/

/**
* @brief  BLE pid键
*/
typedef struct
{
    esp_bt_octet16_t          irk;           /*!< irk值*/
    esp_ble_addr_type_t       addr_type;     /*!< 地址类型*/
    esp_bd_addr_t             static_addr;   /*!< 静态地址*/
} esp_ble_pid_keys_t;                        /*!< pid键类型*/

/**
* @brief  BLE加密再现密钥
*/
typedef struct
{
    esp_bt_octet16_t  ltk;                  /*!< 长期关键*/
    uint16_t          div;                  /*!< div值*/
    uint8_t           key_size;             /*!< 安全链接的密钥大小*/
    uint8_t           sec_level;            /*!< 安全链接的安全级别*/
} esp_ble_lenc_keys_t;                      /*!< 密钥类型*/

/**
* @brief  BLE SRK键
*/
typedef struct
{
    uint32_t          counter;              /*!< 计数器值*/
    uint16_t          div;                  /*!< div值*/
    uint8_t           sec_level;            /*!< 安全链接的安全级别*/
    esp_bt_octet16_t  csrk;                 /*!< csrk键值*/
} esp_ble_lcsrk_keys;                       /*!< csrk密钥类型*/

/**
* @brief  与ESP_KEY_NOTIF_EVT关联的结构
*/
typedef struct
{
    esp_bd_addr_t  bd_addr;        /*!< 对等地址*/
    uint32_t       passkey;        /*!< 用于比较的数值。如果just_works，则不向UI显示此数字*/
} esp_ble_sec_key_notif_t;         /*!< BLE密钥通知类型*/

/**
* @brief  安全请求的结构
*/
typedef struct
{
    esp_bd_addr_t  bd_addr;        /*!< 对等地址*/
} esp_ble_sec_req_t;               /*!< BLE安全请求类型*/

/**
* @brief  安全密钥值的联合类型
*/
typedef union
{
    esp_ble_penc_keys_t   penc_key;       /*!< 收到的对等加密密钥*/
    esp_ble_pcsrk_keys_t  pcsrk_key;      /*!< 接收的对等设备SRK*/
    esp_ble_pid_keys_t    pid_key;        /*!< 对等设备ID密钥*/
    esp_ble_lenc_keys_t   lenc_key;       /*!< 本地加密再现密钥LTK==d1（ER，DIV，0）*/
    esp_ble_lcsrk_keys    lcsrk_key;      /*!< 本地设备CSRK=d1（ER，DIV，1）*/
} esp_ble_key_value_t;                    /*!< ble键值类型*/

/**
* @brief  键信息值的结构类型
*/
typedef struct
{
    esp_ble_key_mask_t    key_mask;       /*!< 指示开关钥匙存在的钥匙掩码*/
    esp_ble_penc_keys_t   penc_key;       /*!< 收到的对等加密密钥*/
    esp_ble_pcsrk_keys_t  pcsrk_key;      /*!< 接收的对等设备SRK*/
    esp_ble_pid_keys_t    pid_key;        /*!< 对等设备ID密钥*/
} esp_ble_bond_key_info_t;                /*!< ble键信息值类型*/

/**
* @brief  绑定设备值的结构类型
*/
typedef struct
{
    esp_bd_addr_t  bd_addr;               /*!< 对等地址*/
    esp_ble_bond_key_info_t bond_key;     /*!< 债券密钥信息*/
} esp_ble_bond_dev_t;                     /*!< ble键合器件类型*/


/**
* @brief  安全密钥值的联合类型
*/
typedef struct
{
    esp_bd_addr_t               bd_addr;        /*!< 对等地址*/
    esp_ble_key_type_t          key_type;       /*!< 安全链接的密钥类型*/
    esp_ble_key_value_t         p_key_value;    /*!< 指向键值的指针*/
} esp_ble_key_t;                                /*!< 布尔键值类型的并集*/

/**
* @brief  ble本地id键值的结构类型
*/
typedef struct {
    esp_bt_octet16_t       ir;                  /*!< ir值的16位*/
    esp_bt_octet16_t       irk;                 /*!< ir键值的16位*/
    esp_bt_octet16_t       dhk;                 /*!< dh键值的16位*/
} esp_ble_local_id_keys_t;                      /*!< ble本地id键值类型的结构*/


/**
  * @brief 与ESP_AUTH_CMPL_EVT相关的结构
  */
typedef struct
{
    esp_bd_addr_t         bd_addr;               /*!< BD地址对等设备。*/
    bool                  key_present;           /*!< 键元素中的有效链接键值*/
    esp_link_key          key;                   /*!< 与对等设备关联的链接密钥。*/
    uint8_t               key_type;              /*!< 链接密钥的类型*/
    bool                  success;               /*!< 验证成功为TRUE，失败为FALSE。*/
    uint8_t               fail_reason;           /*!< 成功=FALSE时的HCI原因/错误代码*/
    esp_ble_addr_type_t   addr_type;             /*!< 对等设备地址类型*/
    esp_bt_dev_type_t     dev_type;              /*!< 设备类型*/
    esp_ble_auth_req_t    auth_mode;             /*!< 身份验证模式*/
} esp_ble_auth_cmpl_t;                           /*!< ble身份验证完成cb类型*/

/**
  * @brief 与ble安全相关联的联合
  */
typedef union
{
    esp_ble_sec_key_notif_t    key_notif;      /*!< 密钥通知*/
    esp_ble_sec_req_t          ble_req;        /*!< BLE SMP相关请求*/
    esp_ble_key_t              ble_key;        /*!< 配对时使用的BLE SMP密钥*/
    esp_ble_local_id_keys_t    ble_id_keys;    /*!< BLE IR事件*/
    esp_ble_auth_cmpl_t        auth_cmpl;      /*!< 认证完成指示。*/
} esp_ble_sec_t;                               /*!< BLE安全类型*/
#if (BLE_42_FEATURE_SUPPORT == TRUE)
///ESP_GAP_BLE_SCAN_RESULT_EVT的子事件
typedef enum {
    ESP_GAP_SEARCH_INQ_RES_EVT             = 0,      /*!< 对等设备的查询结果。*/
    ESP_GAP_SEARCH_INQ_CMPL_EVT            = 1,      /*!< 查询完成。*/
    ESP_GAP_SEARCH_DISC_RES_EVT            = 2,      /*!< 对等设备的发现结果。*/
    ESP_GAP_SEARCH_DISC_BLE_RES_EVT        = 3,      /*!< 对等设备上基于BLE GATT的服务的发现结果。*/
    ESP_GAP_SEARCH_DISC_CMPL_EVT           = 4,      /*!< 发现完成。*/
    ESP_GAP_SEARCH_DI_DISC_CMPL_EVT        = 5,      /*!< 发现完成。*/
    ESP_GAP_SEARCH_SEARCH_CANCEL_CMPL_EVT  = 6,      /*!< 搜索已取消*/
    ESP_GAP_SEARCH_INQ_DISCARD_NUM_EVT     = 7,      /*!< 流控制丢弃的pkt数*/
} esp_gap_search_evt_t;
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）
/**
 * @brief Ble扫描结果事件类型，表示结果是扫描响应或广告数据或其他
 */
typedef enum {
    ESP_BLE_EVT_CONN_ADV         = 0x00,        /*!< 可连接无定向广告（ADV_IND）*/
    ESP_BLE_EVT_CONN_DIR_ADV     = 0x01,        /*!< 可连接定向广告（ADV_DIRECT_IND）*/
    ESP_BLE_EVT_DISC_ADV         = 0x02,        /*!< 可扫描的无方向广告（ADV_SCAN_IND）*/
    ESP_BLE_EVT_NON_CONN_ADV     = 0x03,        /*!< 不可连接的无定向广告（ADV_NOCONN_IND）*/
    ESP_BLE_EVT_SCAN_RSP         = 0x04,        /*!< 扫描响应（Scan_RSP）*/
} esp_ble_evt_type_t;

typedef enum{
    ESP_BLE_WHITELIST_REMOVE     = 0X00,    /*!< 从白名单中删除mac*/
    ESP_BLE_WHITELIST_ADD        = 0X01,    /*!< 将地址添加到白名单*/
} esp_ble_wl_opration_t;
#if (BLE_42_FEATURE_SUPPORT == TRUE)
typedef enum {
    ESP_BLE_DUPLICATE_EXCEPTIONAL_LIST_ADD      = 0,  /*!< 将设备信息添加到重复扫描例外列表中*/
    ESP_BLE_DUPLICATE_EXCEPTIONAL_LIST_REMOVE,        /*!< 从重复扫描例外列表中删除设备信息*/
    ESP_BLE_DUPLICATE_EXCEPTIONAL_LIST_CLEAN,         /*!< 清除重复扫描例外列表*/
} esp_bt_duplicate_exceptional_subcode_type_t;
#endif //#如果（BLE_42_FEATURE_SUPPORT==真）

#define BLE_BIT(n) (1UL<<(n))
#if (BLE_42_FEATURE_SUPPORT == TRUE)
typedef enum {
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_INFO_ADV_ADDR       = 0,  /*!< BLE广告地址、设备信息将添加到ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_ADDR_LIST*/
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_INFO_MESH_LINK_ID,        /*!< BLE网格链接ID，用于BLE网格，设备信息将添加到ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_mesh_link_ID_LIST*/
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_INFO_MESH_BEACON_TYPE,    /*!< BLE网状信标AD类型，格式为|Len|0x2B|信标类型|信标数据|*/
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_INFO_MESH_PROV_SRV_ADV,   /*!< BLE网格配置服务uuid，格式为|0x02|0x01|标志|0x03|0x03| 0x1827|….|`*/
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_INFO_MESH_PROXY_SRV_ADV,  /*!< BLE mesh adv与代理服务uuid，格式为|0x02|0x01|标志|0x03|0x03| 0x1828|……|`*/
} esp_ble_duplicate_exceptional_info_type_t;

typedef enum {
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_ADDR_LIST                  = BLE_BIT(0),             /*!< 重复扫描异常地址列表*/
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_MESH_LINK_ID_LIST          = BLE_BIT(1),             /*!< 重复扫描例外网格链接ID列表*/
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_MESH_BEACON_TYPE_LIST      = BLE_BIT(2),             /*!< 重复扫描例外网格信标类型列表*/
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_MESH_PROV_SRV_ADV_LIST     = BLE_BIT(3),             /*!< 使用配置服务uuid重复扫描例外网格adv*/
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_MESH_PROXY_SRV_ADV_LIST    = BLE_BIT(4),             /*!< 使用配置服务uuid重复扫描例外网格adv*/
    ESP_BLE_DUPLICATE_SCAN_EXCEPTIONAL_ALL_LIST                   = 0xFFFF,                 /*!< 重复扫描例外所有列表*/
} esp_duplicate_scan_exceptional_list_type_t;

typedef uint8_t esp_duplicate_info_t[ESP_BD_ADDR_LEN];

#endif //#如果（BLE_42_FEATURE_SUPPORT==真）

#if (BLE_50_FEATURE_SUPPORT == TRUE)
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_NONCONN_NONSCANNABLE_UNDIRECTED      (0 << 0) // 不可连接和不可扫描的无定向广告
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE                          (1 << 0) // 可连接广告
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_SCANNABLE                            (1 << 1) // 不堪入目的广告
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_DIRECTED                             (1 << 2) // 定向广告
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_HD_DIRECTED                          (1 << 3) // 高占空比定向可连接广告（<=3.75 ms广告间隔）
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY                               (1 << 4) // 使用传统广告PDU
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_ANON_ADV                             (1 << 5) // 从所有PDU中省略广告客户的地址（“匿名广告”）
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_INCLUDE_TX_PWR                       (1 << 6) // 在广告PDU的扩展标头中包含TxPower
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_MASK                                 (0x7F)   // 保留供将来使用

/*  如果正在使用扩展的广告PDU类型（位4=0），则：广告不能既可连接又可扫描。不得使用高占空比定向可连接广告（<=3.75 ms广告间隔）（位3=0）
*/
// ADV_IND
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_IND        (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_SCANNABLE)
// ADV_DIRECT_IND（低占空比）
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_LD_DIR     (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_DIRECTED)
// ADV_DIRECT_IND（高占空比）
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_HD_DIR     (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_CONNECTABLE |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_HD_DIRECTED)
// ADV_SCAN_IND
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_SCAN       (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY |\
                                                        ESP_BLE_GAP_SET_EXT_ADV_PROP_SCANNABLE)
// ADV_NONCONN_IND
#define ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY_NONCONN    (ESP_BLE_GAP_SET_EXT_ADV_PROP_LEGACY)
typedef uint16_t esp_ble_ext_adv_type_mask_t;

#define ESP_BLE_GAP_PHY_1M                             1
#define ESP_BLE_GAP_PHY_2M                             2
#define ESP_BLE_GAP_PHY_CODED                          3
typedef uint8_t esp_ble_gap_phy_t;

#define ESP_BLE_GAP_NO_PREFER_TRANSMIT_PHY     (1<<0)
#define ESP_BLE_GAP_NO_PREFER_RECEIVE_PHY      (1<<1)
typedef uint8_t esp_ble_gap_all_phys_t;

// 主phy仅支持1M和LE编码phy
#define ESP_BLE_GAP_PRI_PHY_1M     ESP_BLE_GAP_PHY_1M
#define ESP_BLE_GAP_PRI_PHY_CODED  ESP_BLE_GAP_PHY_CODED
typedef uint8_t esp_ble_gap_pri_phy_t; // 初级phy

#define ESP_BLE_GAP_PHY_1M_PREF_MASK                   (1 << 0)
#define ESP_BLE_GAP_PHY_2M_PREF_MASK                   (1 << 1)
#define ESP_BLE_GAP_PHY_CODED_PREF_MASK                (1 << 2)
typedef uint8_t esp_ble_gap_phy_mask_t;

#define ESP_BLE_GAP_PHY_OPTIONS_NO_PREF                  0 // 主机在LE编码PHY上传输时没有首选编码
#define ESP_BLE_GAP_PHY_OPTIONS_PREF_S2_CODING           1 // 当在LE编码PHY上传输时，主机优选使用S=2编码
#define ESP_BLE_GAP_PHY_OPTIONS_PREF_S8_CODING           2 // 当在LE编码PHY上传输时，主机优选使用S=8编码
typedef uint16_t esp_ble_gap_prefer_phy_options_t;

#define ESP_BLE_GAP_EXT_SCAN_CFG_UNCODE_MASK           0x01
#define ESP_BLE_GAP_EXT_SCAN_CFG_CODE_MASK             0x02
typedef uint8_t esp_ble_ext_scan_cfg_mask_t;

#define ESP_BLE_GAP_EXT_ADV_DATA_COMPLETE              0x00
#define ESP_BLE_GAP_EXT_ADV_DATA_INCOMPLETE            0x01
#define ESP_BLE_GAP_EXT_ADV_DATA_TRUNCATED             0x02
typedef uint8_t esp_ble_gap_ext_adv_data_status_t;

#define ESP_BLE_GAP_SYNC_POLICY_BY_ADV_INFO       0
#define ESP_BLE_GAP_SYNC_POLICY_BY_PERIODIC_LIST  1
typedef uint8_t esp_ble_gap_sync_t;

/* 广告报道*/
#define ESP_BLE_ADV_REPORT_EXT_ADV_IND                    (1<<0)
#define ESP_BLE_ADV_REPORT_EXT_SCAN_IND                   (1<<1)
#define ESP_BLE_ADV_REPORT_EXT_DIRECT_ADV                 (1<<2)
#define ESP_BLE_ADV_REPORT_EXT_SCAN_RSP                   (1<<3)
/* 蓝牙5.0，第2卷，E部分，7.7.65.13*/
#define ESP_BLE_LEGACY_ADV_TYPE_IND                       (0x13)
#define ESP_BLE_LEGACY_ADV_TYPE_DIRECT_IND                (0x15)
#define ESP_BLE_LEGACY_ADV_TYPE_SCAN_IND                  (0x12)
#define ESP_BLE_LEGACY_ADV_TYPE_NONCON_IND                (0x10)
#define ESP_BLE_LEGACY_ADV_TYPE_SCAN_RSP_TO_ADV_IND       (0x1b)
#define ESP_BLE_LEGACY_ADV_TYPE_SCAN_RSP_TO_ADV_SCAN_IND  (0x1a)
typedef uint8_t esp_ble_gap_adv_type_t;

/**
* @brief ext adv参数
*/
typedef struct {
    esp_ble_ext_adv_type_mask_t type;   /*!< ext-adv类型*/
    uint32_t interval_min;              /*!< ext-adv最小间隔*/
    uint32_t interval_max;              /*!< ext-adv最大间隔*/
    esp_ble_adv_channel_t channel_map;  /*!< ext-adv频道图*/
    esp_ble_addr_type_t own_addr_type;  /*!< ext adv自己的地址类型*/
    esp_ble_addr_type_t peer_addr_type; /*!< ext-adv对等地址类型*/
    esp_bd_addr_t peer_addr;            /*!< ext adv对等地址*/
    esp_ble_adv_filter_t filter_policy; /*!< ext adv筛选器策略*/
    int8_t tx_power;                    /*!< ext adv tx电源*/
    esp_ble_gap_pri_phy_t primary_phy;  /*!< ext-adv基本物理*/
    uint8_t max_skip;                   /*!< ext adv最大跳过*/
    esp_ble_gap_phy_t secondary_phy;    /*!< ext-adv辅助物理*/
    uint8_t sid;                        /*!< ext-adv-sid*/
    bool scan_req_notif;                /*!< ext adv sacn请求事件通知*/
} esp_ble_gap_ext_adv_params_t;

/**
* @brief ext扫描配置
*/
typedef struct {
    esp_ble_scan_type_t scan_type; /*!< ext扫描类型*/
    uint16_t scan_interval;        /*!< ext扫描间隔*/
    uint16_t scan_window;          /*!< ext扫描窗口*/
} esp_ble_ext_scan_cfg_t;

/**
* @brief ext扫描参数
*/
typedef struct {
    esp_ble_addr_type_t own_addr_type;        /*!< ext扫描自己的地址类型*/
    esp_ble_scan_filter_t filter_policy;      /*!< ext扫描筛选器策略*/
    esp_ble_scan_duplicate_t  scan_duplicate; /*!< ext扫描重复扫描*/
    esp_ble_ext_scan_cfg_mask_t cfg_mask;     /*!< ext扫描配置掩码*/
    esp_ble_ext_scan_cfg_t uncoded_cfg;       /*!< ext扫描未编码配置参数*/
    esp_ble_ext_scan_cfg_t coded_cfg;         /*!< ext扫描编码的配置参数*/
} esp_ble_ext_scan_params_t;

/**
* @brief 创建延伸连接参数
*/
typedef struct {
    uint16_t scan_interval;       /*!< 初始化扫描间隔*/
    uint16_t scan_window;         /*!< 初始化扫描窗口*/
    uint16_t interval_min;        /*!< 最小间隔*/
    uint16_t interval_max;        /*!< 最大间隔*/
    uint16_t latency;             /*!< ext扫描类型*/
    uint16_t supervision_timeout; /*!< 连接监视超时*/
    uint16_t min_ce_len;          /*!< 最小ce长度*/
    uint16_t max_ce_len;          /*!< 最大ce长度*/
} esp_ble_gap_conn_params_t;

/**
* @brief 扩展adv启用参数
*/
typedef struct {
    uint8_t instance;        /*!< 广告手柄*/
    int duration;            /*!< 广告持续时间*/
    int max_events;          /*!< 扩展广告事件的最大数量*/
} esp_ble_gap_ext_adv_t;

/**
* @brief 周期性adv参数
*/
typedef struct {
    uint16_t interval_min;     /*!< 周期性广告最小间隔*/
    uint16_t interval_max;     /*!< 周期性广告最大间隔*/
    uint8_t  properties;       /*!< 周期性广告属性*/
} esp_ble_gap_periodic_adv_params_t;

/**
* @brief 周期性adv同步参数
*/
typedef struct {
    esp_ble_gap_sync_t filter_policy;   /*!< 定期广告同步筛选器策略*/
    uint8_t sid;                        /*!< 周期性广告sid*/
    esp_ble_addr_type_t addr_type;      /*!< 周期性广告地址类型*/
    esp_bd_addr_t addr;                 /*!< 定期广告地址*/
    uint16_t skip;                      /*!< 可跳过的周期性广告事件的最大数量*/
    uint16_t sync_timeout;              /*!< 同步超时*/
} esp_ble_gap_periodic_adv_sync_params_t;

/**
* @brief 扩展adv报表参数
*/
typedef struct {
    // uint8_t道具；
    // uint8_t legacy_event_type；
    esp_ble_gap_adv_type_t event_type;              /*!< 扩展广告类型*/
    uint8_t addr_type;                              /*!< 扩展广告地址类型*/
    esp_bd_addr_t addr;                             /*!< 扩展广告地址*/
    esp_ble_gap_pri_phy_t primary_phy;              /*!< 扩展广告主phy*/
    esp_ble_gap_phy_t secondly_phy;                 /*!< 扩展广告辅助phy*/
    uint8_t sid;                                    /*!< 扩展广告sid*/
    uint8_t tx_power;                               /*!< 扩展广告发送功率*/
    int8_t rssi;                                    /*!< 扩展广告rssi*/
    uint16_t per_adv_interval;                      /*!< 周期性广告间隔*/
    uint8_t dir_addr_type;                          /*!< 直接地址类型*/
    esp_bd_addr_t dir_addr;                         /*!< 直接地址*/
    esp_ble_gap_ext_adv_data_status_t data_status;  /*!< 数据类型*/
    uint8_t adv_data_len;                           /*!< 扩展广告数据长度*/
    uint8_t adv_data[251];                          /*!< 扩展广告数据*/
} esp_ble_gap_ext_adv_reprot_t;

/**
* @brief 定期adv报告参数
*/
typedef struct {
    uint16_t sync_handle;                          /*!< 定期广告列车把手*/
    uint8_t tx_power;                              /*!< 周期性广告发送功率*/
    int8_t rssi;                                   /*!< 定期广告rssi*/
    esp_ble_gap_ext_adv_data_status_t data_status; /*!< 定期广告数据类型*/
    uint8_t data_length;                           /*!< 周期性广告数据长度*/
    uint8_t data[251];                             /*!< 定期广告数据*/
} esp_ble_gap_periodic_adv_report_t;

/**
* @brief 周期adv同步建立参数
*/
typedef struct {
    uint8_t status;                               /*!< 定期广告同步状态*/
    uint16_t sync_handle;                         /*!< 定期广告列车把手*/
    uint8_t sid;                                  /*!< 周期性广告sid*/
    esp_ble_addr_type_t addr_type;                /*!< 周期性广告地址类型*/
    esp_bd_addr_t adv_addr;                       /*!< 定期广告地址*/
    esp_ble_gap_phy_t adv_phy;                    /*!< 定期广告类型*/
    uint16_t period_adv_interval;                 /*!< 周期性广告间隔*/
    uint8_t adv_clk_accuracy;                     /*!< 周期性广告时钟精度*/
} esp_ble_gap_periodic_adv_sync_estab_t;

#endif //#如果（BLE_50_FFEATURE_SUPPORT==真）

/**
 * @brief 间隙回调参数联合
 */
typedef union {
#if (BLE_42_FEATURE_SUPPORT == TRUE)
    /**
     * @brief ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT
     */
    struct ble_adv_data_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示设置的广告数据操作成功状态*/
    } adv_data_cmpl;                                /*!< ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT
     */
    struct ble_scan_rsp_data_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示设置的扫描响应数据操作成功状态*/
    } scan_rsp_data_cmpl;                           /*!< ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT
     */
    struct ble_scan_param_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示设置的扫描参数操作成功状态*/
    } scan_param_cmpl;                              /*!< ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SCAN_RESULT_EVT
     */
    struct ble_scan_result_evt_param {
        esp_gap_search_evt_t search_evt;            /*!< 搜索事件类型*/
        esp_bd_addr_t bda;                          /*!< 已搜索的蓝牙设备地址*/
        esp_bt_dev_type_t dev_type;                 /*!< 设备类型*/
        esp_ble_addr_type_t ble_addr_type;          /*!< Ble设备地址类型*/
        esp_ble_evt_type_t ble_evt_type;            /*!< Ble扫描结果事件类型*/
        int rssi;                                   /*!< 搜索设备的RSSI*/
        uint8_t  ble_adv[ESP_BLE_ADV_DATA_LEN_MAX + ESP_BLE_SCAN_RSP_DATA_LEN_MAX];     /*!< 收到EIR*/
        int flag;                                   /*!< 广告数据标志位*/
        int num_resps;                              /*!< 扫描结果编号*/
        uint8_t adv_data_len;                       /*!< 高级数据长度*/
        uint8_t scan_rsp_len;                       /*!< 扫描响应长度*/
        uint32_t num_dis;                          /*!< 丢弃数据包的数量*/
    } scan_rst;                                     /*!< ESP_GAP_BLE_SCAN_RESULT_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT
     */
    struct ble_adv_data_raw_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示设置的原始广告数据操作成功状态*/
    } adv_data_raw_cmpl;                            /*!< ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT
     */
    struct ble_scan_rsp_data_raw_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示设置的原始广告数据操作成功状态*/
    } scan_rsp_data_raw_cmpl;                       /*!< ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_ADV_START_COMPLETE_EVT
     */
    struct ble_adv_start_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示广告启动操作成功状态*/
    } adv_start_cmpl;                               /*!< ESP_GAP_BLE_ADV_START_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SCAN_START_COMPLETE_EVT
     */
    struct ble_scan_start_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示扫描启动操作成功状态*/
    } scan_start_cmpl;                              /*!< ESP_GAP_BLE_SCAN_START_COMPLETE_EVT的事件参数*/
#endif //#如果（BLE_42_FEATURE_SUPPORT==真）
    esp_ble_sec_t ble_security;                     /*!< 弹性间隙安全接头类型*/
#if (BLE_42_FEATURE_SUPPORT == TRUE)
    /**
     * @brief ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT
     */
    struct ble_scan_stop_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示扫描停止操作成功状态*/
    } scan_stop_cmpl;                               /*!< ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT
     */
    struct ble_adv_stop_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示adv停止操作成功状态*/
    } adv_stop_cmpl;                                /*!< ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT的事件参数*/
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）
    /**
     * @brief ESP_GAP_BLE_SET_STATIC_RAND_ADDR_EVT
     */
    struct ble_set_rand_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示设置静态rand地址操作成功状态*/
    } set_rand_addr_cmpl;                           /*!< ESP_GAP_BLE_SET_STATIC_RAND_ADDR_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT
     */
    struct ble_update_conn_params_evt_param {
        esp_bt_status_t status;                    /*!< 指示更新连接参数的成功状态*/
        esp_bd_addr_t bda;                         /*!< 蓝牙设备地址*/
        uint16_t min_int;                          /*!< 最小连接间隔*/
        uint16_t max_int;                          /*!< 最大连接间隔*/
        uint16_t latency;                          /*!< 连接的从属延迟（以连接事件数表示）。范围：0x0000到0x01F3*/
        uint16_t conn_int;                         /*!< 当前连接间隔*/
        uint16_t timeout;                          /*!< LE链路的监控超时。范围：0x000A到0x0C80。强制范围：0x000A-0x0C80时间=N*10毫秒*/
    } update_conn_params;                          /*!< ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SET_PKT_LENGTH_COMPLETE_EVT
     */
    struct ble_pkt_data_length_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示设置pkt数据长度操作成功状态*/
        esp_ble_pkt_data_length_params_t params;    /*!<  pkt数据长度值*/
    } pkt_data_lenth_cmpl;                          /*!< ESP_GAP_BLE_SET_PKT_LENGTH_COLELETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT
     */
    struct ble_local_privacy_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示设置的本地隐私操作成功状态*/
    } local_privacy_cmpl;                           /*!< ESP_GAP_BLE_SET_LOCAL_PRIVACY_COLELETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT
     */
    struct ble_remove_bond_dev_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示移除键合设备操作成功状态*/
        esp_bd_addr_t bd_addr;                      /*!< 已从绑定列表中删除的设备地址*/
    } remove_bond_dev_cmpl;                         /*!< ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_CLEAR_BOND_DEV_COMPLETE_EVT
     */
    struct ble_clear_bond_dev_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示透明键合装置操作成功状态*/
    } clear_bond_dev_cmpl;                          /*!< ESP_GAP_BLE_CLEAR_BOND_DEV_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_GET_BOND_DEV_COMPLETE_EVT
     */
    struct ble_get_bond_dev_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示获取绑定设备操作成功状态*/
        uint8_t dev_num;                            /*!< 在债券列表中指明获取号码设备*/
        esp_ble_bond_dev_t *bond_dev;               /*!< 指向键合设备结构的指针*/
    } get_bond_dev_cmpl;                            /*!< ESP_GAP_BLE_GET_BOND_DEV_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_READ_RSSI_COMPLETE_EVT
     */
    struct ble_read_rssi_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示读取的adv tx电源操作成功状态*/
        int8_t rssi;                                /*!< ble远程设备rssi值，范围为-127至20，单位为dbm，如果无法读取rssi，则rssi度量应设置为127。*/
        esp_bd_addr_t remote_addr;                  /*!< 远程设备地址*/
    } read_rssi_cmpl;                               /*!< ESP_GAP_BLE_READ_RSSI_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_UPDATE_WHITELIST_COMPLETE_EVT
     */
    struct ble_update_whitelist_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示添加或删除白名单操作成功状态*/
        esp_ble_wl_opration_t wl_opration;          /*!< 如果将地址添加到白名单操作成功，则值为ESP_BLE_WHITELIST_ADD；如果从白名单操作中删除地址成功，则为ESP_BLE _WHITELEST_REMOVE*/
    } update_whitelist_cmpl;                        /*!< ESP_GAP_BLE_UPDATE_WHITELIST_COMPLETE_EVT的事件参数*/
#if (BLE_42_FEATURE_SUPPORT == TRUE)
    /**
     * @brief ESP_GAP_BLE_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_COMPLETE_EVT
     */
    struct ble_update_duplicate_exceptional_list_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示更新重复扫描异常列表操作成功状态*/
        uint8_t         subcode;                    /*!< 在esp_bt_duplicate_exceptional_subcode_type_t中定义*/
        uint16_t         length;                     /*!< device_info的长度*/
        esp_duplicate_info_t device_info;           /*!< 设备信息，当子代码为ESP_BLE_DUPLICATE_EXCEPTIONAL_LIST_CLEAN时，该值无效*/
    } update_duplicate_exceptional_list_cmpl;       /*!< ESP_GAP_BLE_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_COMPLETE_EVT的事件参数*/
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）
    /**
     * @brief ESP_GAP_BLE_SET_CHANNELS_EVT
      */
    struct ble_set_channels_evt_param {
        esp_bt_status_t stat;                       /*!< BLE设置通道状态*/
    } ble_set_channels;                             /*!< ESP_GAP_BLE_SET_CHANNELS_EVT的事件参数*/

#if (BLE_50_FEATURE_SUPPORT == TRUE)
    /**
     * @brief ESP_GAP_BLE_READ_PHY_COMPLETE_EVT
     */
    struct ble_read_phy_cmpl_evt_param {
        esp_bt_status_t status;                   /*!< 读取phy完成状态*/
        esp_bd_addr_t bda;                        /*!< 读取phy地址*/
        esp_ble_gap_phy_t tx_phy;                 /*!< tx phy类型*/
        esp_ble_gap_phy_t rx_phy;                 /*!< rx phy类型*/
    } read_phy;                                   /*!< ESP_GAP_BLE_READ_PHY_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SET_PREFERED_DEFAULT_PHY_COMPLETE_EVT
     */
    struct ble_set_perf_def_phy_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示性能默认物理集状态*/
    } set_perf_def_phy;                             /*!< ESP_GAP_BLE_SET_PREFERED_DEFAULT_PHY_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SET_PREFERED_PHY_COMPLETE_EVT
     */
    struct ble_set_perf_phy_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示性能集状态*/
    } set_perf_phy;                                  /*!< ESP_GAP_BLE_SET_PREFERED_PHY_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_ADV_SET_RAND_ADDR_COMPLETE_EVT
     */
    struct ble_ext_adv_set_rand_addr_cmpl_evt_param {
        esp_bt_status_t status;                      /*!< 指示扩展广告随机地址集状态*/
    } ext_adv_set_rand_addr;                         /*!< ESP_GAP_BLE_EXT_ADV_SET_RAND_ADDR_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_ADV_SET_PARAMS_COMPLETE_EVT
     */
    struct ble_ext_adv_set_params_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示扩展广告参数集状态*/
    } ext_adv_set_params;                           /*!< ESP_GAP_BLE_EXT_ADV_SET_PARAMS_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_ADV_DATA_SET_COMPLETE_EVT
     */
     struct ble_ext_adv_data_set_cmpl_evt_param {
        esp_bt_status_t status;                      /*!< 指示扩展广告数据集状态*/
    } ext_adv_data_set;                              /*!< ESP_GAP_BLE_EXT_ADV_DATA_SET_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_SCAN_RSP_DATA_SET_COMPLETE_EVT
     */
    struct ble_ext_adv_scan_rsp_set_cmpl_evt_param {
        esp_bt_status_t status;                      /*!< 指示扩展广告sacn响应数据集状态*/
    } scan_rsp_set;                                  /*!< ESP_GAP_BLE_EXT_SCAN_RSP_DATA_SET_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_ADV_START_COMPLETE_EVT
     */
    struct ble_ext_adv_start_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示广告启动操作成功状态*/
    } ext_adv_start;                                /*!< ESP_GAP_BLE_EXT_ADV_START_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_ADV_STOP_COMPLETE_EVT
     */
    struct ble_ext_adv_stop_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示广告停止操作成功状态*/
    } ext_adv_stop;                                 /*!< ESP_GAP_BLE_EXT_ADV_STOP_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_ADV_SET_REMOVE_COMPLETE_EVT
     */
    struct ble_ext_adv_set_remove_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示广告停止操作成功状态*/
    } ext_adv_remove;                               /*!< ESP_GAP_BLE_EXT_ADV_SET_REMOVE_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_ADV_SET_CLEAR_COMPLETE_EVT
     */
    struct ble_ext_adv_set_clear_cmpl_evt_param {
        esp_bt_status_t status;                     /*!< 指示广告停止操作成功状态*/
    } ext_adv_clear;                                /*!< ESP_GAP_BLE_EXT_ADV_SET_CLEAR_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_SET_PARAMS_COMPLETE_EVT
     */
    struct ble_periodic_adv_set_params_cmpl_param {
        esp_bt_status_t status;                    /*!< 指示定期播发参数集状态*/
    } peroid_adv_set_params;                       /*!< ESP_GAP_BLE_PERIODIC_ADV_SET_PARAMS_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_DATA_SET_COMPLETE_EVT
     */
    struct ble_periodic_adv_data_set_cmpl_param {
        esp_bt_status_t status;                    /*!< 指示定期广告数据集状态*/
    } period_adv_data_set;                         /*!< ESP_GAP_BLE_PERIODIC_ADV_DATA_SET_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_START_COMPLETE_EVT
     */
    struct ble_periodic_adv_start_cmpl_param {
        esp_bt_status_t status;                   /*!< 指示定期广告开始状态*/
    } period_adv_start;                           /*!< ESP_GAP_BLE_PERIODIC_ADV_START_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_STOP_COMPLETE_EVT
     */
    struct ble_periodic_adv_stop_cmpl_param {
        esp_bt_status_t status;                  /*!< 指示定期广告停止状态*/
    } period_adv_stop;                           /*!< ESP_GAP_BLE_PERIODIC_ADV_STOP_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_CREATE_SYNC_COMPLETE_EVT
     */
    struct ble_period_adv_create_sync_cmpl_param {
        esp_bt_status_t status;                  /*!< 指示定期广告创建同步状态*/
    } period_adv_create_sync;                    /*!< ESP_GAP_BLE_PERIODIC_ADV_CREATE_SYNC_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_SYNC_CANCEL_COMPLETE_EVT
     */
    struct ble_period_adv_sync_cancel_cmpl_param {
        esp_bt_status_t status;                  /*!< 指示定期广告同步取消状态*/
    } period_adv_sync_cancel;                    /*!< ESP_GAP_BLE_PERIODIC_ADV_SYNC_CANCEL_COMPLETE_EVT的事件参数*/
     /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_SYNC_TERMINATE_COMPLETE_EVT
     */
    struct ble_period_adv_sync_terminate_cmpl_param {
        esp_bt_status_t status;                  /*!< 指示定期广告同步终止状态*/
    } period_adv_sync_term;                      /*!< ESP_GAP_BLE_PERIODIC_ADV_SYNC_TERMINATE_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_ADD_DEV_COMPLETE_EVT
     */
    struct ble_period_adv_add_dev_cmpl_param {
        esp_bt_status_t status;                 /*!< 指示定期广告设备列表添加状态*/
    } period_adv_add_dev;                       /*!< ESP_GAP_BLE_PERIODIC_ADD_DEV_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_REMOVE_DEV_COMPLETE_EVT
     */
    struct ble_period_adv_remove_dev_cmpl_param {
        esp_bt_status_t status;                /*!< 指示定期广告设备列表删除状态*/
    } period_adv_remove_dev;                   /*!< ESP_GAP_BLE_PERIODIC_ADV_REMOVE_DEV_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_CLEAR_DEV_COMPLETE_EVT
     */
    struct ble_period_adv_clear_dev_cmpl_param {
        esp_bt_status_t status;               /*!< 指示定期广告设备列表清理状态*/
    } period_adv_clear_dev;                   /*!< ESP_GAP_BLE_PERIODIC_ADV_CLEAR_DEV_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SET_EXT_SCAN_PARAMS_COMPLETE_EVT
     */
    struct ble_set_ext_scan_params_cmpl_param {
        esp_bt_status_t status;              /*!< 指示扩展广告参数集状态*/
    } set_ext_scan_params;                   /*!< ESP_GAP_BLE_SET_EXT_SCAN_PARAMS_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_SCAN_START_COMPLETE_EVT
     */
    struct ble_ext_scan_start_cmpl_param {
        esp_bt_status_t status;             /*!< 指示扩展广告开始状态*/
    } ext_scan_start;                       /*!< ESP_GAP_BLE_EXT_SCAN_START_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_SCAN_STOP_COMPLETE_EVT
     */
    struct ble_ext_scan_stop_cmpl_param {
        esp_bt_status_t status;            /*!< 指示扩展广告停止状态*/
    } ext_scan_stop;                       /*!< ESP_GAP_BLE_EXT_SCAN_STOP_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PREFER_EXT_CONN_PARAMS_SET_COMPLETE_EVT
     */
    struct ble_ext_conn_params_set_cmpl_param {
        esp_bt_status_t status;            /*!< 指示扩展连接参数设置状态*/
    } ext_conn_params_set;                 /*!< ESP_GAP_BLE_PREFER_EXT_CONN_PARAMS_SET_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_ADV_TERMINATED_EVT
     */
    struct ble_adv_terminate_param {
        uint8_t status;                   /*!< 指示adv终止状态*/
        /*  状态0x3c指示固定持续时间的广告已完成，或者对于定向广告，广告已完成而未创建连接；状态0x00表示广告已成功结束，并且正在创建连接。
        */
        uint8_t adv_instance;           /*!< 扩展广告句柄*/
        uint16_t conn_idx;              /*!< 连接索引*/
        uint8_t completed_event;        /*!< 已完成的扩展广告事件数*/
    } adv_terminate;                    /*!< ESP_GAP_BLE_ADV_TERMINATED_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_SCAN_REQ_RECEIVED_EVT
     */
    struct ble_scan_req_received_param {
        uint8_t adv_instance;                /*!< 扩展广告句柄*/
        esp_ble_addr_type_t scan_addr_type;  /*!< 扫描器地址类型*/
        esp_bd_addr_t scan_addr;             /*!< 扫描器地址*/
    } scan_req_received;                     /*!< ESP_GAP_BLE_SCAN_REQ_RECEIVED_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_CHANNEL_SELETE_ALGORITHM_EVT
     */
    struct ble_channel_sel_alg_param {
        uint16_t conn_handle;              /*!< 连接手柄*/
        uint8_t channel_sel_alg;           /*!< 信道选择算法*/
    } channel_sel_alg;                     /*!< ESP_GAP_BLE_CHANNEL_SELETE_ALGORITHM_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_SYNC_LOST_EVT
     */
    struct ble_periodic_adv_sync_lost_param {
        uint16_t sync_handle;                 /*!< 同步句柄*/
    } periodic_adv_sync_lost;                 /*!< ESP_GAP_BLE_PERIODIC_ADV_SYNC_LOST_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_SYNC_ESTAB_EVT
     */
    struct ble_periodic_adv_sync_estab_param {
        uint8_t status;                      /*!< 定期广告同步状态*/
        uint16_t sync_handle;                /*!< 定期广告同步句柄*/
        uint8_t sid;                         /*!< 周期性广告sid*/
        esp_ble_addr_type_t adv_addr_type;   /*!< 周期性广告地址类型*/
        esp_bd_addr_t adv_addr;              /*!< 定期广告地址*/
        esp_ble_gap_phy_t adv_phy;           /*!< 周期性广告phy类型*/
        uint16_t period_adv_interval;        /*!< 周期性广告间隔*/
        uint8_t adv_clk_accuracy;            /*!< 周期性广告时钟精度*/
    } periodic_adv_sync_estab;               /*!< ESP_GAP_BLE_PERIODIC_ADV_SYNC_ESTAB_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PHY_UPDATE_COMPLETE_EVT
     */
    struct ble_phy_update_cmpl_param {
        esp_bt_status_t status;             /*!< phy更新状态*/
        esp_bd_addr_t bda;                  /*!< 住址*/
        esp_ble_gap_phy_t tx_phy;           /*!< tx phy类型*/
        esp_ble_gap_phy_t rx_phy;           /*!< rx phy类型*/
    } phy_update;                           /*!< ESP_GAP_BLE_PHY_UPDATE_COMPLETE_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_EXT_ADV_REPORT_EVT
     */
    struct ble_ext_adv_report_param {
        esp_ble_gap_ext_adv_reprot_t params;   /*!< 扩展广告报告参数*/
    } ext_adv_report;                          /*!< ESP_GAP_BLE_EXT_ADV_REPORT_EVT的事件参数*/
    /**
     * @brief ESP_GAP_BLE_PERIODIC_ADV_REPORT_EVT
     */
    struct ble_periodic_adv_report_param {
        esp_ble_gap_periodic_adv_report_t params; /*!< 定期广告报告参数*/
    } period_adv_report;                          /*!< ESP_GAP_BLE_PERIODIC_ADV_REPORT_EVT的事件参数*/
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）
} esp_ble_gap_cb_param_t;

/**
 * @brief GAP回调函数类型
 * @param event ：事件类型
 * @param param ：指向回调参数，当前为联合类型
 */
typedef void (* esp_gap_ble_cb_t)(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);

/**
 * @brief           调用此函数以发生间隙事件，如扫描结果
 *
 * @param[in]       callback: 回调函数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_register_callback(esp_gap_ble_cb_t callback);

#if (BLE_42_FEATURE_SUPPORT == TRUE)
/**
 * @brief           调用此函数以覆盖BTA默认ADV参数。
 *
 * @param[in]       adv_data: 指向用户定义ADV数据结构的指针。在收到config_adv_data的回调之前，无法释放此内存空间。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_config_adv_data (esp_ble_adv_data_t *adv_data);



/**
 * @brief           调用此函数以设置扫描参数
 *
 * @param[in]       scan_params: 指向用户定义的scan_param数据结构的指针。在回调set_scan_param之前，无法释放此内存空间
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_set_scan_params(esp_ble_scan_params_t *scan_params);


/**
 * @brief           此过程使设备扫描在空中播放广告的对等设备
 *
 * @param[in]       duration: 保持扫描时间，单位为秒。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_start_scanning(uint32_t duration);


/**
 * @brief          此函数调用以停止设备扫描正在播放广告的对等设备
 * @return
 *                 -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_stop_scanning(void);

/**
 * @brief           调用此函数以启动广告。
 *
 * @param[in]       adv_params: 指向用户定义的adv_param数据结构的指针。

 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_start_advertising (esp_ble_adv_params_t *adv_params);



/**
 * @brief           调用此函数以停止广告。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_stop_advertising(void);
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）


/**
 * @brief           更新连接参数，只能在连接启动时使用。
 *
 * @param[in]       params   -连接更新参数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_update_conn_params(esp_ble_conn_update_params_t *params);


/**
 * @brief           此函数用于设置最大LE数据包大小
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_set_pkt_data_len(esp_bd_addr_t remote_device, uint16_t tx_data_length);

/**
 * @brief           此函数设置应用程序的静态随机地址和非解析专用地址
 *
 * @param[in]       rand_addr: 应设置的随机地址
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_set_rand_addr(esp_bd_addr_t rand_addr);

/**
 * @brief           此函数用于清除应用程序的随机地址
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_clear_rand_addr(void);



/**
 * @brief           在本地设备上启用/禁用隐私
 *
 * @param[in]       privacy_enable   -启用/禁用远程设备上的隐私。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_config_local_privacy (bool privacy_enable);

/**
 * @brief           设置局部间隙外观图标
 *
 *
 * @param[in]       icon   -外部外观值，这些值由蓝牙SIG定义，请参阅https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.gap.appearance.xml
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_config_local_icon (uint16_t icon);

/**
* @brief            从白名单中添加或删除设备
*
* @param[in]        add_remove: 如果将ble设备添加到白名单中，则该值为true，如果将false移除到白名单，则该为false。
* @param[in]        remote_bda: 远程设备地址从白名单中添加/删除。
* @param[in]        wl_addr_type: 白名单地址类型
* @return
*                     -ESP_OK：成功
*                     -其他：失败
*
*/
esp_err_t esp_ble_gap_update_whitelist(bool add_remove, esp_bd_addr_t remote_bda, esp_ble_wl_addr_type_t wl_addr_type);

/**
* @brief            清除所有白名单
*
* @return
*                     -ESP_OK：成功
*                     -其他：失败
*
*/
esp_err_t esp_ble_gap_clear_whitelist(void);

/**
* @brief            获取控制器中的白名单大小
*
* @param[out]       length: 白名单长度。
* @return
*                     -ESP_OK：成功
*                     -其他：失败
*
*/
esp_err_t esp_ble_gap_get_whitelist_size(uint16_t *length);
#if (BLE_42_FEATURE_SUPPORT == TRUE)
/**
* @brief            当连接前不需要默认连接参数时，调用此函数以设置首选连接参数。此API只能在主角色中使用。
*
* @param[in]        bd_addr: 外围设备的BD地址
* @param[in]        min_conn_int: 最小优选连接间隔
* @param[in]        max_conn_int: 最大优选连接间隔
* @param[in]        slave_latency: 首选从属延迟
* @param[in]        supervision_tout: 首选监视超时
*
* @return
*                   -ESP_OK：成功
*                   -其他：失败
*
*/
esp_err_t esp_ble_gap_set_prefer_conn_params(esp_bd_addr_t bd_addr,
                                                                 uint16_t min_conn_int, uint16_t max_conn_int,
                                                                 uint16_t slave_latency, uint16_t supervision_tout);
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）
/**
 * @brief           将设备名称设置为本地设备
 *
 * @param[in]       name   -设备名称。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_set_device_name(const char *name);

/**
 * @brief          调用此函数以获取本地使用的地址和地址类型。uint8_t esp_bt_dev_get_address（void）获取公共地址
 *
 * @param[in]       local_used_addr -当前本地可用地址（六字节）
 * @param[in]       addr_type   -ble地址类型
 *
 * @return          -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_get_local_used_addr(esp_bd_addr_t local_used_addr, uint8_t * addr_type);
/**
 * @brief          调用此函数以获取特定类型的ADV数据。
 *
 * @param[in]       adv_data -要解析的ADV数据指针
 * @param[in]       type   -查找ADV数据类型
 * @param[out]      length -返回不包括类型的ADV数据的长度
 *
 * @return          ADV数据指针
 *
 */
uint8_t *esp_ble_resolve_adv_data(uint8_t *adv_data, uint8_t type, uint8_t *length);
#if (BLE_42_FEATURE_SUPPORT == TRUE)
/**
 * @brief           调用此函数以设置原始广告数据。用户需要自行填写ADV数据。
 *
 * @param[in]       raw_data ：原始广告数据
 * @param[in]       raw_data_len ：原始广告数据长度，小于31字节
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_ble_gap_config_adv_data_raw(uint8_t *raw_data, uint32_t raw_data_len);

/**
 * @brief           调用此函数以设置原始扫描响应数据。用户需要自行填写扫描响应数据。
 *
 * @param[in]       raw_data ：原始扫描响应数据
 * @param[in]       raw_data_len ：原始扫描响应数据长度，小于31字节
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 */
esp_err_t esp_ble_gap_config_scan_rsp_data_raw(uint8_t *raw_data, uint32_t raw_data_len);
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）

/**
 * @brief           调用此函数读取远程设备的RSSI。链接策略结果的地址将通过ESP_gap_BLE_READ_RSSI_COMPLETE_EVT事件在间隙回调函数中返回。
 *
 * @param[in]       remote_addr ：远程连接设备地址。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 */
esp_err_t esp_ble_gap_read_rssi(esp_bd_addr_t remote_addr);
#if (BLE_42_FEATURE_SUPPORT == TRUE)
/**
 * @brief           调用此函数将设备信息添加到重复扫描例外列表中。
 *
 *
 * @param[in]       type: 设备信息类型，当类型为MESH_BEACON_type、MESH_PROV_SRV_ADV或MESH_PROXY_SRV_ADV时，在esp_ble_duplicate_exceptional_info_type_t中定义，设备信息无效。
 * @param[in]       device_info: 设备信息。
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 */
esp_err_t esp_ble_gap_add_duplicate_scan_exceptional_device(esp_ble_duplicate_exceptional_info_type_t type, esp_duplicate_info_t device_info);

/**
 * @brief           调用此函数以从重复扫描例外列表中删除设备信息。
 *
 *
 * @param[in]       type: 设备信息类型，当类型为MESH_BEACON_type、MESH_PROV_SRV_ADV或MESH_PROXY_SRV_ADV时，在esp_ble_duplicate_exceptional_info_type_t中定义，设备信息无效。
 * @param[in]       device_info: 设备信息。
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 */
esp_err_t esp_ble_gap_remove_duplicate_scan_exceptional_device(esp_ble_duplicate_exceptional_info_type_t type, esp_duplicate_info_t device_info);

/**
 * @brief           调用此函数以清除重复扫描异常列表。此API将删除重复扫描例外列表中的所有设备信息。
 *
 *
 * @param[in]       list_type: 重复扫描异常列表类型，该值可以是espduplicate_scan_exceptional_list_typet中的一个或多个。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 */
esp_err_t esp_ble_gap_clean_duplicate_scan_exceptional_list(esp_duplicate_scan_exceptional_list_type_t list_type);
#endif // #如果（BLE_42_FEATURE_SUPPORT==真）

#if (SMP_INCLUDED == TRUE)
/**
* @brief             设置GAP安全参数值。替代默认值。
*
*                    强烈建议安全连接以避免一些主要漏洞，如“引脚配对协议中的模拟”（CVE-2020-26555）和“LE传统配对协议的验证”。
*
*                    要仅接受“安全连接模式”，必须执行以下操作：
*
*                    1.根据需要，设置位“ESP_LE_AUTH_REQ_SC_ONLY”（“param_type”为“ESP_BLE_SM_AUTHEN_REQ_MODE”）、位“ESP-LE_AUTH_BOND”和位“ESP.LE_AUTH/REQ_MITM”是可选的。
*
*                    2.设置为“ESP_BLE_ONLY_ACCEPT_SPECIFIED_AUTH_ENABLE”（“param_type”为“ESP-BLE_SM_ONLY_ACCEPT_SPECIFIED_SEC_AUTH”）。
*
* @param[in]       param_type ：要设置的参数的类型
* @param[in]       value  ：参数值
* @param[in]       len ：参数值的长度
*
* @return            -ESP_OK：成功
*                       -其他：失败
*
*/
esp_err_t esp_ble_gap_set_security_param(esp_ble_sm_param_t param_type,
                                         void *value, uint8_t len);

/**
* @brief             授予安全请求访问权限。
*
* @param[in]       bd_addr ：对等方的BD地址
* @param[in]       accept  ：是否接受安全请求
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_security_rsp(esp_bd_addr_t bd_addr,  bool accept);


/**
* @brief             设置间隙参数值。使用此功能更改默认GAP参数值。
*
* @param[in]       bd_addr ：需要加密的对等设备的地址
* @param[in]       sec_act  ：这是一个安全操作，用于指示BLE链接所需的BLE安全级别（如果支持BLE）
*
* @return            -ESP_OK：成功
*                       -其他：失败
*
*/
esp_err_t esp_ble_set_encryption(esp_bd_addr_t bd_addr, esp_ble_sec_act_t sec_act);

/**
* @brief          在传统连接阶段向对等设备回复密钥值。
*
* @param[in]      bd_addr ：对等方的BD地址
* @param[in]      accept ：密钥输入成功或被拒绝。
* @param[in]      passkey ：密钥值，必须是6位数字，可以以0开头。
*
* @return            -ESP_OK：成功
*                  -其他：失败
*
*/
esp_err_t esp_ble_passkey_reply(esp_bd_addr_t bd_addr, bool accept, uint32_t passkey);


/**
* @brief           在安全连接阶段向对等设备回复确认值。
*
* @param[in]       bd_addr ：对等设备的BD地址
* @param[in]       accept ：要比较的数字相同或不同。
*
* @return            -ESP_OK：成功
*                       -其他：失败
*
*/
esp_err_t esp_ble_confirm_reply(esp_bd_addr_t bd_addr, bool accept);

/**
* @brief           从对等设备的安全数据库列表中删除设备。它在连接时管理断开连接事件。
*
* @param[in]       bd_addr ：对等设备的BD地址
*
* @return            -ESP_OK：成功
*                       -其他：失败
*
*/
esp_err_t esp_ble_remove_bond_device(esp_bd_addr_t bd_addr);

/**
* @brief           从对等设备的安全数据库列表中获取设备编号。它将立即返回设备绑定编号。
*
* @return          ->=0：键合设备编号。
*                  -ESP_FAIL:失败
*
*/
int esp_ble_get_bond_device_num(void);


/**
* @brief           从对等设备的安全数据库列表中获取设备。它将立即返回设备绑定信息。
* @param[inout]    dev_num: 指示dev_list数组（缓冲区）大小作为输入。如果dev_num足够大，则表示输出的实际数量。建议dev_num值等于esp_ble_get_bond_device_num（）。
*
* @param[out]      dev_list: “esp_ble_bond_dev_t”类型的数组（缓冲区）。用于存储绑定的设备地址。dev_list应由调用此API的人分配。
* @return          -ESP_OK：成功
*                  -其他：失败
*
*/
esp_err_t esp_ble_get_bond_device_list(int *dev_num, esp_ble_bond_dev_t *dev_list);

/**
* @brief           调用此函数以响应ESP_GAP_BLE_OOB_REQ_EVT为SMP提供OOB数据
*
* @param[in]       bd_addr: 对等设备的BD地址。
* @param[in]       TK: TK值，TK值应为128位随机数
* @param[in]       len: tk的长度应始终为128位
*
* @return          -ESP_OK：成功
*                  -其他：失败
*
*/
esp_err_t esp_ble_oob_req_reply(esp_bd_addr_t bd_addr, uint8_t *TK, uint8_t len);

#endif /* #如果（SMP_INCLUDED==TRUE）*/

/**
* @brief           此功能用于在注册多个app_id时断开对等设备gattc可能具有多个虚拟GATT服务器连接的物理连接。esp_ble_gattc_close（esp_gatt_if_t gattc_if，uint16_t conn_id）仅关闭一个虚拟gatt服务器连接。如果存在其他虚拟GATT服务器连接，则不会断开物理连接。esp_ble_gap_disconnect（esp_bd_addr_tremote_device）直接断开物理连接。
*
*
*
* @param[in]       remote_device ：对等设备的BD地址
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_disconnect(esp_bd_addr_t remote_device);

/**
* @brief           调用此函数以读取设备的连接参数信息
*
* @param[in]       bd_addr: 对等设备的BD地址。
* @param[out]      conn_params: 连接参数信息
*
* @return          -ESP_OK：成功
*                  -其他：失败
*
*/
esp_err_t esp_ble_get_current_conn_params(esp_bd_addr_t bd_addr, esp_gap_conn_params_t *conn_params);

/**
* @brief            BLE设置通道
*
* @param[in]        channels ：第n个这样的字段（在0到36的范围内）包含链路层信道索引n的值。0表示信道n是坏的。1表示信道n未知。保留最高有效位，并将其设置为0。至少一个信道应标记为未知。
*
* @return           -ESP_OK：成功
*                   -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
*                   -其他：失败
*
*/
esp_err_t esp_gap_ble_set_channels(esp_gap_ble_channels channels);

/**
* @brief           在认证后调用此函数以授权链接（MITM保护）
*
* @param[in]       bd_addr: 对等设备的BD地址。
* @param[out]      authorize: 是否已授权链接。
*
* @return          -ESP_OK：成功
*                  -其他：失败
*
*/
esp_err_t esp_gap_ble_set_authorization(esp_bd_addr_t bd_addr, bool authorize);

#if (BLE_50_FEATURE_SUPPORT == TRUE)

/**
* @brief           此功能用于读取远程地址标识的连接上的当前发射机PHY和接收机PHY。
*
* @param[in]       bd_addr ：对等设备的BD地址
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_read_phy(esp_bd_addr_t bd_addr);

/**
* @brief           此功能用于允许主机指定发射机PHY和接收机PHY的首选值，以用于LE传输上的所有后续连接。
*
* @param[in]       tx_phy_mask ：表示主机希望控制器使用的发射机PHY
* @param[in]       rx_phy_mask ：表示主机希望控制器使用的接收器PHY
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_set_prefered_default_phy(esp_ble_gap_phy_mask_t tx_phy_mask, esp_ble_gap_phy_mask_t rx_phy_mask);
/**
* @brief           此功能用于设置由远程地址标识的连接的PHY首选项。控制器可能无法进行改变（例如，因为对等体不支持所请求的PHY）或可能决定当前PHY是优选的。
*
* @param[in]       bd_addr ：远程地址
* @param[in]       all_phys_mask ：允许主机指定的位字段
* @param[in]       tx_phy_mask ：一个位字段，指示主机希望控制器使用的发射机PHY
* @param[in]       rx_phy_mask ：一个位字段，指示主机希望控制器使用的接收器PHY
* @param[in]       phy_options ：允许主机为PHY指定选项的位字段
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_set_prefered_phy(esp_bd_addr_t bd_addr,
                                       esp_ble_gap_all_phys_t all_phys_mask,
                                       esp_ble_gap_phy_mask_t tx_phy_mask,
                                       esp_ble_gap_phy_mask_t rx_phy_mask,
                                       esp_ble_gap_prefer_phy_options_t phy_options);

/**
* @brief           主机使用此函数设置random_address参数指定的随机设备地址。
*
* @param[in]       instance  ：用于标识广告集
* @param[in]       rand_addr ：随机设备地址
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_ext_adv_set_rand_addr(uint8_t instance, esp_bd_addr_t rand_addr);

/**
* @brief           主机使用此功能设置广告参数。
*
* @param[in]       instance ：标识正在配置其参数的广告集。
* @param[in]       params   ：广告参数
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_ext_adv_set_params(uint8_t instance, const esp_ble_gap_ext_adv_params_t *params);

/**
* @brief           此功能用于设置具有数据字段的广告PDU中使用的数据
*
* @param[in]       instance ：标识正在配置其数据的广告集
* @param[in]       length   ：数据长度
* @param[in]       data     ：数据信息
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_config_ext_adv_data_raw(uint8_t instance, uint16_t length, const uint8_t *data);

/**
* @brief           此功能用于提供扫描响应PDU中使用的扫描响应数据
*
* @param[in]       instance ：标识正在配置其响应数据的广告集。
* @param[in]       length ：响应长度
* @param[in]       scan_rsp_data ：响应数据信息
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_config_ext_scan_rsp_data_raw(uint8_t instance, uint16_t length,
                                                                   const uint8_t *scan_rsp_data);
/**
* @brief           此函数用于请求控制器使用实例参数标识的广告集启用一个或多个广告集。
*
* @param[in]       num_adv ：要启用或禁用的广告集数
* @param[in]       ext_adv ：adv参数
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_ext_adv_start(uint8_t num_adv, const esp_ble_gap_ext_adv_t *ext_adv);

/**
* @brief           此函数用于请求控制器使用实例参数标识的广告集禁用一个或多个广告集。
*
* @param[in]       num_adv ：要启用或禁用的广告集数
* @param[in]       ext_adv_inst ：ext adv实例
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_ext_adv_stop(uint8_t num_adv, const uint8_t *ext_adv_inst);

/**
* @brief           此功能用于从控制器中删除广告集。
*
* @param[in]       instance ：用于标识广告集
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_ext_adv_set_remove(uint8_t instance);

/**
* @brief           此功能用于从控制器中删除所有现有广告集。
*
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_ext_adv_set_clear(void);

/**
* @brief           主机使用此功能设置定期广告的参数。
*
* @param[in]       instance ：标识正在配置其定期广告参数的广告集。
* @param[in]       params ：周期性adv参数
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_periodic_adv_set_params(uint8_t instance, const esp_ble_gap_periodic_adv_params_t *params);

/**
* @brief           此功能用于设置定期广告PDU中使用的数据。
*
* @param[in]       instance ：标识正在配置其定期广告参数的广告集。
* @param[in]       length ：周期数据的长度
* @param[in]       data ：周期性数据信息
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_config_periodic_adv_data_raw(uint8_t instance, uint16_t length,
                                                                           const uint8_t *data);
/**
* @brief           此功能用于请求控制器启用指定广告集的定期广告
*
* @param[in]       instance ：用于标识广告集
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_periodic_adv_start(uint8_t instance);

/**
* @brief           此功能用于请求控制器禁用指定广告集的定期广告
*
* @param[in]       instance ：用于标识广告集
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_periodic_adv_stop(uint8_t instance);

/**
* @brief           此功能用于设置要在广告频道上使用的扩展扫描参数。
*
* @param[in]       params ：扫描参数
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_set_ext_scan_params(const esp_ble_ext_scan_params_t *params);

/**
* @brief           此功能用于启用扫描。
*
* @param[in]       duration ：扫描持续时间
* @param[in]       period  ：从控制器开始上次扫描持续时间到开始后续扫描持续时间的时间间隔。
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_start_ext_scan(uint32_t duration, uint16_t period);

/**
* @brief           此功能用于禁用扫描。
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_stop_ext_scan(void);

/**
* @brief           此功能用于与广告商的定期广告同步，并开始接收定期广告包。
*
* @param[in]       params ：同步参数
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_periodic_adv_create_sync(const esp_ble_gap_periodic_adv_sync_params_t *params);

/**
* @brief           此函数用于在LE_Periodic_Advertising_Create_Sync命令挂起时取消该命令。
*
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_periodic_adv_sync_cancel(void);

/**
* @brief           此函数用于停止接收由同步句柄参数标识的定期广告。
*
* @param[in]       sync_handle ：标识定期广告客户
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_periodic_adv_sync_terminate(uint16_t sync_handle);

/**
* @brief           此功能用于将单个设备添加到控制器中存储的定期广告客户列表
*
* @param[in]       addr_type ：地址类型
* @param[in]       addr ：设备地址
* @param[in]       sid ：ADI字段中用于标识定期广告的广告SID子字段
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_periodic_adv_add_dev_to_list(esp_ble_addr_type_t addr_type,
                                                                         esp_bd_addr_t addr,
                                                                         uint8_t sid);

/**
* @brief           此功能用于从控制器中存储的定期播发列表中删除一个设备。从定期广告客户列表中删除立即生效。
*
* @param[in]       addr_type ：地址类型
* @param[in]       addr ：设备地址
* @param[in]       sid ：ADI字段中用于标识定期广告的广告SID子字段
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_periodic_adv_remove_dev_from_list(esp_ble_addr_type_t addr_type,
                                                                         esp_bd_addr_t addr,
                                                                         uint8_t sid);
/**
* @brief           此功能用于从控制器中的定期播发列表中删除所有设备。
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_periodic_adv_clear_dev(void);

/**
* @brief           此功能用于设置辅助连接参数
*
* @param[in]       addr ：设备地址
* @param[in]       phy_mask ：指示应在主广告信道上接收广告分组的PHY以及已指定连接参数的PHY。
* @param[in]       phy_1m_conn_params ：扫描LE 1M PHY上的可连接广告。提供了LE 1M PHY的连接参数。
* @param[in]       phy_2m_conn_params ：提供了LE 2M PHY的连接参数。
* @param[in]       phy_coded_conn_params ：扫描LE编码PHY上的可连接广告。提供了LE编码PHY的连接参数。
*
* @return            -ESP_OK：成功
*                    -其他：失败
*
*/
esp_err_t esp_ble_gap_prefer_ext_connect_params_set(esp_bd_addr_t addr,
                                                    esp_ble_gap_phy_mask_t phy_mask,
                                                    const esp_ble_gap_conn_params_t *phy_1m_conn_params,
                                                    const esp_ble_gap_conn_params_t *phy_2m_conn_params,
                                                    const esp_ble_gap_conn_params_t *phy_coded_conn_params);

#endif //#如果（BLE_50_FFEATURE_SUPPORT==真）

#ifdef __cplusplus
}
#endif

#endif /* __ESP_GAP_BLE_API_H__ */

