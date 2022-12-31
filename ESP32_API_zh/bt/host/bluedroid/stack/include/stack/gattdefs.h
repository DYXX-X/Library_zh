/******************************************************************************
 * 版权所有（C）1999-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 此文件包含内部使用的ATT定义
 *
 ******************************************************************************/

#ifndef  _GATTDEFS_H
#define  _GATTDEFS_H

#define GATT_ILLEGAL_UUID            0

/* GATT属性类型
*/
#define GATT_UUID_PRI_SERVICE           0x2800
#define GATT_UUID_SEC_SERVICE           0x2801
#define GATT_UUID_INCLUDE_SERVICE       0x2802
#define GATT_UUID_CHAR_DECLARE          0x2803      /*  特性声明*/

#define GATT_UUID_CHAR_EXT_PROP         0x2900      /*  特征扩展属性*/
#define GATT_UUID_CHAR_DESCRIPTION      0x2901      /*  特征用户描述*/
#define GATT_UUID_CHAR_CLIENT_CONFIG    0x2902      /*  客户端特征配置*/
#define GATT_UUID_CHAR_SRVR_CONFIG      0x2903      /*  服务器特征配置*/
#define GATT_UUID_CHAR_PRESENT_FORMAT   0x2904      /*  特色演示格式*/
#define GATT_UUID_CHAR_AGG_FORMAT       0x2905      /*  特征聚合格式*/
#define GATT_UUID_CHAR_VALID_RANGE       0x2906      /*  特征有效范围*/
#define GATT_UUID_EXT_RPT_REF_DESCR     0x2907
#define GATT_UUID_RPT_REF_DESCR         0x2908


/* GAP配置文件属性
*/
#define GATT_UUID_GAP_DEVICE_NAME        0x2A00
#define GATT_UUID_GAP_ICON               0x2A01
#define GATT_UUID_GAP_PREF_CONN_PARAM    0x2A04
#define GATT_UUID_GAP_CENTRAL_ADDR_RESOL 0x2AA6

/* 属性配置文件属性UUID*/
#define GATT_UUID_GATT_SRV_CHGD          0x2A05
/* 属性协议测试*/

/* 链路丢失服务*/
#define GATT_UUID_ALERT_LEVEL           0x2A06      /* 警报级别*/
#define GATT_UUID_TX_POWER_LEVEL        0x2A07      /* TX功率电平*/

/* 时间配置文件*/
/* 当前时间服务*/
#define GATT_UUID_CURRENT_TIME          0x2A2B      /* 当前时间*/
#define GATT_UUID_LOCAL_TIME_INFO       0x2A0F      /* 当地时间信息*/
#define GATT_UUID_REF_TIME_INFO         0x2A14      /* 参考时间信息*/

/* NwA配置文件*/
#define GATT_UUID_NW_STATUS             0x2A18      /* 网络可用性状态*/
#define GATT_UUID_NW_TRIGGER            0x2A1A      /* 网络可用性触发*/

/* 电话警报*/
#define GATT_UUID_ALERT_STATUS          0x2A3F    /* 警报状态*/
#define GATT_UUID_RINGER_CP             0x2A40    /* 振铃器控制点*/
#define GATT_UUID_RINGER_SETTING        0x2A41    /* 振铃器设置*/

/* 葡萄糖服务*/
#define GATT_UUID_GM_MEASUREMENT        0x2A18
#define GATT_UUID_GM_CONTEXT            0x2A34
#define GATT_UUID_GM_CONTROL_POINT      0x2A52
#define GATT_UUID_GM_FEATURE            0x2A51

/* 设备信息特性*/
#define GATT_UUID_SYSTEM_ID             0x2A23
#define GATT_UUID_MODEL_NUMBER_STR      0x2A24
#define GATT_UUID_SERIAL_NUMBER_STR     0x2A25
#define GATT_UUID_FW_VERSION_STR        0x2A26
#define GATT_UUID_HW_VERSION_STR        0x2A27
#define GATT_UUID_SW_VERSION_STR        0x2A28
#define GATT_UUID_MANU_NAME             0x2A29
#define GATT_UUID_IEEE_DATA             0x2A2A
#define GATT_UUID_PNP_ID                0x2A50

/* HID特性*/
#define GATT_UUID_HID_INFORMATION       0x2A4A
#define GATT_UUID_HID_REPORT_MAP        0x2A4B
#define GATT_UUID_HID_CONTROL_POINT     0x2A4C
#define GATT_UUID_HID_REPORT            0x2A4D
#define GATT_UUID_HID_PROTO_MODE        0x2A4E
#define GATT_UUID_HID_BT_KB_INPUT       0x2A22
#define GATT_UUID_HID_BT_KB_OUTPUT      0x2A32
#define GATT_UUID_HID_BT_MOUSE_INPUT    0x2A33

/* 电池服务字符*/
#define GATT_UUID_BATTERY_LEVEL         0x2A19

#define GATT_UUID_SC_CONTROL_POINT      0x2A55
#define GATT_UUID_SENSOR_LOCATION       0x2A5D

/* RUNNERS SPEED AND CADENCE SERVICE      */
#define GATT_UUID_RSC_MEASUREMENT       0x2A53
#define GATT_UUID_RSC_FEATURE           0x2A54

/* CYCLING SPEED AND CADENCE SERVICE      */
#define GATT_UUID_CSC_MEASUREMENT       0x2A5B
#define GATT_UUID_CSC_FEATURE           0x2A5C


/* 扫描参数特征*/
#define GATT_UUID_SCAN_INT_WINDOW       0x2A4F
#define GATT_UUID_SCAN_REFRESH          0x2A31

#endif

