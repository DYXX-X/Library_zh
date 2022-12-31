/** @file
 *  @brief 蓝牙UUID处理
 */

/*
 * SPDX文件版权文本：2015-2016 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _BLE_MESH_UUID_H_
#define _BLE_MESH_UUID_H_

/**
 * @brief UUID
 * @defgroup bt_uuid uuid
 * @ingroup 蓝牙@{
 */

#include "mesh_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 蓝牙UUID类型*/
enum {
    BLE_MESH_UUID_TYPE_16,
    BLE_MESH_UUID_TYPE_32,
    BLE_MESH_UUID_TYPE_128,
};

/** @brief 这是一种“暂定”类型，只能用作指针*/
struct bt_mesh_uuid {
    uint8_t type;
};

struct bt_mesh_uuid_16 {
    struct bt_mesh_uuid uuid;
    uint16_t val;
};

struct bt_mesh_uuid_32 {
    struct bt_mesh_uuid uuid;
    uint32_t val;
};

struct bt_mesh_uuid_128 {
    struct bt_mesh_uuid uuid;
    uint8_t val[16];
};

#define BLE_MESH_UUID_INIT_16(value)        \
{                                           \
    .uuid.type = BLE_MESH_UUID_TYPE_16,     \
    .val = (value),                         \
}

#define BLE_MESH_UUID_INIT_32(value)        \
{                                           \
    .uuid.type = BLE_MESH_UUID_TYPE_32,     \
    .val = (value),                         \
}

#define BLE_MESH_UUID_INIT_128(value...)    \
{                                           \
    .uuid.type = BLE_MESH_UUID_TYPE_128,    \
    .val = { value },                       \
}

#define BLE_MESH_UUID_DECLARE_16(value)     \
        ((struct bt_mesh_uuid *) (&(struct bt_mesh_uuid_16) BLE_MESH_UUID_INIT_16(value)))

#define BLE_MESH_UUID_DECLARE_32(value)     \
        ((struct bt_mesh_uuid *) (&(struct bt_mesh_uuid_32) BLE_MESH_UUID_INIT_32(value)))

#define BLE_MESH_UUID_DECLARE_128(value...) \
        ((struct bt_mesh_uuid *) (&(struct bt_mesh_uuid_128) BLE_MESH_UUID_INIT_128(value)))

#define BLE_MESH_UUID_16(__u)  CONTAINER_OF(__u, struct bt_mesh_uuid_16, uuid)
#define BLE_MESH_UUID_32(__u)  CONTAINER_OF(__u, struct bt_mesh_uuid_32, uuid)
#define BLE_MESH_UUID_128(__u) CONTAINER_OF(__u, struct bt_mesh_uuid_128, uuid)

/** @def BLE_MESH_UUID_GAP
 *  @brief 通用访问
 */
#define BLE_MESH_UUID_GAP                       BLE_MESH_UUID_DECLARE_16(0x1800)
#define BLE_MESH_UUID_GAP_VAL                   0x1800
/** @def BLE_MESH_UUID_GATT
 *  @brief 泛型属性
 */
#define BLE_MESH_UUID_GATT                      BLE_MESH_UUID_DECLARE_16(0x1801)
#define BLE_MESH_UUID_GATT_VAL                  0x1801
/** @def BLE_MESH_UUID_CTS
 *  @brief 当前时间服务
 */
#define BLE_MESH_UUID_CTS                       BLE_MESH_UUID_DECLARE_16(0x1805)
#define BLE_MESH_UUID_CTS_VAL                   0x1805
/** @def BLE_MESH_UUID_DIS
 *  @brief 设备信息服务
 */
#define BLE_MESH_UUID_DIS                       BLE_MESH_UUID_DECLARE_16(0x180a)
#define BLE_MESH_UUID_DIS_VAL                   0x180a
/** @def BLE_MESH_UUID_HRS
 *  @brief 心率服务
 */
#define BLE_MESH_UUID_HRS                       BLE_MESH_UUID_DECLARE_16(0x180d)
#define BLE_MESH_UUID_HRS_VAL                   0x180d
/** @def BLE_MESH_UUID_BAS
 *  @brief 电池服务
 */
#define BLE_MESH_UUID_BAS                       BLE_MESH_UUID_DECLARE_16(0x180f)
#define BLE_MESH_UUID_BAS_VAL                   0x180f
/** @def BLE_MESH_UUID_HIDS
 *  @brief HID服务
 */
#define BLE_MESH_UUID_HIDS                      BLE_MESH_UUID_DECLARE_16(0x1812)
#define BLE_MESH_UUID_HIDS_VAL                  0x1812
/** @def BLE_MESH_UUID_CSC
 *  @brief 自行车速度和Cadence服务
 */
#define BLE_MESH_UUID_CSC                       BLE_MESH_UUID_DECLARE_16(0x1816)
#define BLE_MESH_UUID_CSC_VAL                   0x1816
/** @def BLE_MESH_UUID_ESS
 *  @brief 环境传感服务
 */
#define BLE_MESH_UUID_ESS                       BLE_MESH_UUID_DECLARE_16(0x181a)
#define BLE_MESH_UUID_ESS_VAL                   0x181a
/** @def BLE_MESH_UUID_IPSS
 *  @brief IP支持服务
 */
#define BLE_MESH_UUID_IPSS                      BLE_MESH_UUID_DECLARE_16(0x1820)
#define BLE_MESH_UUID_IPSS_VAL                  0x1820
/** @def BLE_MESH_UUID_MESH_PROV
 *  @brief 网格配置服务
 */
#define BLE_MESH_UUID_MESH_PROV                 BLE_MESH_UUID_DECLARE_16(0x1827)
#define BLE_MESH_UUID_MESH_PROV_VAL             0x1827
/** @def BLE_MESH_UUID_MESH_PROXY
 *  @brief 网格代理服务
 */
#define BLE_MESH_UUID_MESH_PROXY                BLE_MESH_UUID_DECLARE_16(0x1828)
#define BLE_MESH_UUID_MESH_PROXY_VAL            0x1828
/** @def BLE_MESH_UUID_GATT_PRIMARY
 *  @brief GATT初级服务
 */
#define BLE_MESH_UUID_GATT_PRIMARY              BLE_MESH_UUID_DECLARE_16(0x2800)
#define BLE_MESH_UUID_GATT_PRIMARY_VAL          0x2800
/** @def BLE_MESH_UUID_GATT_SECONDARY
 *  @brief GATT二级服务
 */
#define BLE_MESH_UUID_GATT_SECONDARY            BLE_MESH_UUID_DECLARE_16(0x2801)
#define BLE_MESH_UUID_GATT_SECONDARY_VAL        0x2801
/** @def BLE_MESH_UUID_GATT_INCLUDE
 *  @brief GATT包括服务
 */
#define BLE_MESH_UUID_GATT_INCLUDE              BLE_MESH_UUID_DECLARE_16(0x2802)
#define BLE_MESH_UUID_GATT_INCLUDE_VAL          0x2802
/** @def BLE_MESH_UUID_GATT_CHRC
 *  @brief GATT特征
 */
#define BLE_MESH_UUID_GATT_CHRC                 BLE_MESH_UUID_DECLARE_16(0x2803)
#define BLE_MESH_UUID_GATT_CHRC_VAL             0x2803
/** @def BLE_MESH_UUID_GATT_CEP
 *  @brief GATT特征扩展属性
 */
#define BLE_MESH_UUID_GATT_CEP                  BLE_MESH_UUID_DECLARE_16(0x2900)
#define BLE_MESH_UUID_GATT_CEP_VAL              0x2900
/** @def BLE_MESH_UUID_GATT_CUD
 *  @brief GATT特征用户描述
 */
#define BLE_MESH_UUID_GATT_CUD                  BLE_MESH_UUID_DECLARE_16(0x2901)
#define BLE_MESH_UUID_GATT_CUD_VAL              0x2901
/** @def BLE_MESH_UUID_GATT_CCC
 *  @brief GATT客户端特征配置
 */
#define BLE_MESH_UUID_GATT_CCC                  BLE_MESH_UUID_DECLARE_16(0x2902)
#define BLE_MESH_UUID_GATT_CCC_VAL              0x2902
/** @def BLE_MESH_UUID_GATT_SCC
 *  @brief GATT服务器特征配置
 */
#define BLE_MESH_UUID_GATT_SCC                  BLE_MESH_UUID_DECLARE_16(0x2903)
#define BLE_MESH_UUID_GATT_SCC_VAL              0x2903
/** @def BLE_MESH_UUID_GATT_CPF
 *  @brief GATT特征表示格式
 */
#define BLE_MESH_UUID_GATT_CPF                  BLE_MESH_UUID_DECLARE_16(0x2904)
#define BLE_MESH_UUID_GATT_CPF_VAL              0x2904
/** @def BLE_MESH_UUID_VALID_RANGE
 *  @brief 有效范围描述符
 */
#define BLE_MESH_UUID_VALID_RANGE               BLE_MESH_UUID_DECLARE_16(0x2906)
#define BLE_MESH_UUID_VALID_RANGE_VAL           0x2906
/** @def BLE_MESH_UUID_HIDS_EXT_REPORT
 *  @brief HID外部报告描述符
 */
#define BLE_MESH_UUID_HIDS_EXT_REPORT           BLE_MESH_UUID_DECLARE_16(0x2907)
#define BLE_MESH_UUID_HIDS_EXT_REPORT_VAL       0x2907
/** @def BLE_MESH_UUID_HIDS_REPORT_REF
 *  @brief HID报告引用描述符
 */
#define BLE_MESH_UUID_HIDS_REPORT_REF           BLE_MESH_UUID_DECLARE_16(0x2908)
#define BLE_MESH_UUID_HIDS_REPORT_REF_VAL       0x2908
/** @def BLE_MESH_UUID_ES_CONFIGURATION
 *  @brief 环境传感配置描述符
 */
#define BLE_MESH_UUID_ES_CONFIGURATION          BLE_MESH_UUID_DECLARE_16(0x290b)
#define BLE_MESH_UUID_ES_CONFIGURATION_VAL      0x290b
/** @def BLE_MESH_UUID_ES_MEASUREMENT
 *  @brief 环境传感测量描述符
 */
#define BLE_MESH_UUID_ES_MEASUREMENT            BLE_MESH_UUID_DECLARE_16(0x290c)
#define BLE_MESH_UUID_ES_MEASUREMENT_VAL        0x290c
/** @def BLE_MESH_UUID_ES_TRIGGER_SETTING
 *  @brief 环境感应触发设置描述符
 */
#define BLE_MESH_UUID_ES_TRIGGER_SETTING        BLE_MESH_UUID_DECLARE_16(0x290d)
#define BLE_MESH_UUID_ES_TRIGGER_SETTING_VAL    0x290d
/** @def BLE_MESH_UUID_GAP_DEVICE_NAME
 *  @brief GAP特征设备名称
 */
#define BLE_MESH_UUID_GAP_DEVICE_NAME           BLE_MESH_UUID_DECLARE_16(0x2a00)
#define BLE_MESH_UUID_GAP_DEVICE_NAME_VAL       0x2a00
/** @def BLE_MESH_UUID_GAP_APPEARANCE
 *  @brief GAP特征外观
 */
#define BLE_MESH_UUID_GAP_APPEARANCE            BLE_MESH_UUID_DECLARE_16(0x2a01)
#define BLE_MESH_UUID_GAP_APPEARANCE_VAL        0x2a01
/** @def BLE_MESH_UUID_GAP_PPCP
 *  @brief GAP特征外围设备首选连接参数
 */
#define BLE_MESH_UUID_GAP_PPCP                  BLE_MESH_UUID_DECLARE_16(0x2a04)
#define BLE_MESH_UUID_GAP_PPCP_VAL              0x2a04
/** @def BLE_MESH_UUID_GATT_SC
 *  @brief GATT特色服务变更
 */
#define BLE_MESH_UUID_GATT_SC                   BLE_MESH_UUID_DECLARE_16(0x2a05)
#define BLE_MESH_UUID_GATT_SC_VAL               0x2a05
/** @def BLE_MESH_UUID_BAS_BATTERY_LEVEL
 *  @brief BAS特征电池电量
 */
#define BLE_MESH_UUID_BAS_BATTERY_LEVEL         BLE_MESH_UUID_DECLARE_16(0x2a19)
#define BLE_MESH_UUID_BAS_BATTERY_LEVEL_VAL     0x2a19
/** @def BLE_MESH_UUID_DIS_SYSTEM_ID
 *  @brief DIS特征系统ID
 */
#define BLE_MESH_UUID_DIS_SYSTEM_ID             BLE_MESH_UUID_DECLARE_16(0x2a23)
#define BLE_MESH_UUID_DIS_SYSTEM_ID_VAL         0x2a23
/** @def BLE_MESH_UUID_DIS_MODEL_NUMBER
 *  @brief DIS特征型号字符串
 */
#define BLE_MESH_UUID_DIS_MODEL_NUMBER          BLE_MESH_UUID_DECLARE_16(0x2a24)
#define BLE_MESH_UUID_DIS_MODEL_NUMBER_VAL      0x2a24
/** @def BLE_MESH_UUID_DIS_SERIAL_NUMBER
 *  @brief DIS特征序列号字符串
 */
#define BLE_MESH_UUID_DIS_SERIAL_NUMBER         BLE_MESH_UUID_DECLARE_16(0x2a25)
#define BLE_MESH_UUID_DIS_SERIAL_NUMBER_VAL     0x2a25
/** @def BLE_MESH_UUID_DIS_FIRMWARE_REVISION
 *  @brief DIS特征固件修订字符串
 */
#define BLE_MESH_UUID_DIS_FIRMWARE_REVISION     BLE_MESH_UUID_DECLARE_16(0x2a26)
#define BLE_MESH_UUID_DIS_FIRMWARE_REVISION_VAL 0x2a26
/** @def BLE_MESH_UUID_DIS_HARDWARE_REVISION
 *  @brief DIS特征硬件修订字符串
 */
#define BLE_MESH_UUID_DIS_HARDWARE_REVISION     BLE_MESH_UUID_DECLARE_16(0x2a27)
#define BLE_MESH_UUID_DIS_HARDWARE_REVISION_VAL 0x2a27
/** @def BLE_MESH_UUID_DIS_SOFTWARE_REVISION
 *  @brief DIS特征软件修订字符串
 */
#define BLE_MESH_UUID_DIS_SOFTWARE_REVISION     BLE_MESH_UUID_DECLARE_16(0x2a28)
#define BLE_MESH_UUID_DIS_SOFTWARE_REVISION_VAL 0x2a28
/** @def BLE_MESH_UUID_DIS_MANUFACTURER_NAME
 *  @brief DIS特征制造商名称字符串
 */
#define BLE_MESH_UUID_DIS_MANUFACTURER_NAME     BLE_MESH_UUID_DECLARE_16(0x2a29)
#define BLE_MESH_UUID_DIS_MANUFACTURER_NAME_VAL 0x2a29
/** @def BLE_MESH_UUID_DIS_PNP_ID
 *  @brief DIS特征PnP ID
 */
#define BLE_MESH_UUID_DIS_PNP_ID                BLE_MESH_UUID_DECLARE_16(0x2a50)
#define BLE_MESH_UUID_DIS_PNP_ID_VAL            0x2a50
/** @def BLE_MESH_UUID_CTS_CURRENT_TIME
 *  @brief CTS特征电流时间
 */
#define BLE_MESH_UUID_CTS_CURRENT_TIME          BLE_MESH_UUID_DECLARE_16(0x2a2b)
#define BLE_MESH_UUID_CTS_CURRENT_TIME_VAL      0x2a2b
/** @def BLE_MESH_UUID_MAGN_DECLINATION
 *  @brief 磁偏转特性
 */
#define BLE_MESH_UUID_MAGN_DECLINATION          BLE_MESH_UUID_DECLARE_16(0x2a2c)
#define BLE_MESH_UUID_MAGN_DECLINATION_VAL      0x2a2c
/** @def BLE_MESH_UUID_HRS_MEASUREMENT
 *  @brief HRS特性测量间隔
 */
#define BLE_MESH_UUID_HRS_MEASUREMENT           BLE_MESH_UUID_DECLARE_16(0x2a37)
#define BLE_MESH_UUID_HRS_MEASUREMENT_VAL       0x2a37
/** @def BLE_MESH_UUID_HRS_BODY_SENSOR
 *  @brief HRS特征车身传感器位置
 */
#define BLE_MESH_UUID_HRS_BODY_SENSOR           BLE_MESH_UUID_DECLARE_16(0x2a38)
#define BLE_MESH_UUID_HRS_BODY_SENSOR_VAL       0x2a38
/** @def BLE_MESH_UUID_HRS_CONTROL_POINT
 *  @brief HRS特性控制点
 */
#define BLE_MESH_UUID_HRS_CONTROL_POINT         BLE_MESH_UUID_DECLARE_16(0x2a39)
#define BLE_MESH_UUID_HRS_CONTROL_POINT_VAL     0x2a39
/** @def BLE_MESH_UUID_HIDS_INFO
 *  @brief HID信息特征
 */
#define BLE_MESH_UUID_HIDS_INFO                 BLE_MESH_UUID_DECLARE_16(0x2a4a)
#define BLE_MESH_UUID_HIDS_INFO_VAL             0x2a4a
/** @def BLE_MESH_UUID_HIDS_REPORT_MAP
 *  @brief HID报告映射特征
 */
#define BLE_MESH_UUID_HIDS_REPORT_MAP           BLE_MESH_UUID_DECLARE_16(0x2a4b)
#define BLE_MESH_UUID_HIDS_REPORT_MAP_VAL       0x2a4b
/** @def BLE_MESH_UUID_HIDS_CTRL_POINT
 *  @brief HID控制点特性
 */
#define BLE_MESH_UUID_HIDS_CTRL_POINT           BLE_MESH_UUID_DECLARE_16(0x2a4c)
#define BLE_MESH_UUID_HIDS_CTRL_POINT_VAL       0x2a4c
/** @def BLE_MESH_UUID_HIDS_REPORT
 *  @brief HID报告特征
 */
#define BLE_MESH_UUID_HIDS_REPORT               BLE_MESH_UUID_DECLARE_16(0x2a4d)
#define BLE_MESH_UUID_HIDS_REPORT_VAL           0x2a4d
/** @def BLE_MESH_UUID_CSC_MEASUREMENT
 *  @brief CSC测量特性
 */
#define BLE_MESH_UUID_CSC_MEASUREMENT           BLE_MESH_UUID_DECLARE_16(0x2a5b)
#define BLE_MESH_UUID_CSC_MEASUREMENT_VAL       0x2a5b
/** @def BLE_MESH_UUID_CSC_FEATURE
 *  @brief CSC特性
 */
#define BLE_MESH_UUID_CSC_FEATURE               BLE_MESH_UUID_DECLARE_16(0x2a5c)
#define BLE_MESH_UUID_CSC_FEATURE_VAL           0x2a5c
/** @def BLE_MESH_UUID_SENSOR_LOCATION
 *  @brief 传感器位置特性
 */
#define BLE_MESH_UUID_SENSOR_LOCATION           BLE_MESH_UUID_DECLARE_16(0x2a5d)
#define BLE_MESH_UUID_SENSOR_LOCATION_VAL       0x2a5d
/** @def BLE_MESH_UUID_SC_CONTROL_POINT
 *  @brief SC控制点特性
 */
#define BLE_MESH_UUID_SC_CONTROL_POINT          BLE_MESH_UUID_DECLARE_16(0x2a55)
#define BLE_MESH_UUID_SC_CONTROL_POINT_VAl      0x2a55
/** @def BLE_MESH_UUID_ELEVATION
 *  @brief 高程特征
 */
#define BLE_MESH_UUID_ELEVATION                 BLE_MESH_UUID_DECLARE_16(0x2a6c)
#define BLE_MESH_UUID_ELEVATION_VAL             0x2a6c
/** @def BLE_MESH_UUID_PRESSURE
 *  @brief 压力特性
 */
#define BLE_MESH_UUID_PRESSURE                  BLE_MESH_UUID_DECLARE_16(0x2a6d)
#define BLE_MESH_UUID_PRESSURE_VAL              0x2a6d
/** @def BLE_MESH_UUID_TEMPERATURE
 *  @brief 温度特性
 */
#define BLE_MESH_UUID_TEMPERATURE               BLE_MESH_UUID_DECLARE_16(0x2a6e)
#define BLE_MESH_UUID_TEMPERATURE_VAL           0x2a6e
/** @def BLE_MESH_UUID_HUMIDITY
 *  @brief 湿度特性
 */
#define BLE_MESH_UUID_HUMIDITY                  BLE_MESH_UUID_DECLARE_16(0x2a6f)
#define BLE_MESH_UUID_HUMIDITY_VAL              0x2a6f
/** @def BLE_MESH_UUID_TRUE_WIND_SPEED
 *  @brief 真实风速特性
 */
#define BLE_MESH_UUID_TRUE_WIND_SPEED           BLE_MESH_UUID_DECLARE_16(0x2a70)
#define BLE_MESH_UUID_TRUE_WIND_SPEED_VAL       0x2a70
/** @def BLE_MESH_UUID_TRUE_WIND_DIR
 *  @brief 真实风向特征
 */
#define BLE_MESH_UUID_TRUE_WIND_DIR             BLE_MESH_UUID_DECLARE_16(0x2a71)
#define BLE_MESH_UUID_TRUE_WIND_DIR_VAL         0x2a71
/** @def BLE_MESH_UUID_APPARENT_WIND_SPEED
 *  @brief 表观风速特性
 */
#define BLE_MESH_UUID_APPARENT_WIND_SPEED       BLE_MESH_UUID_DECLARE_16(0x2a72)
#define BLE_MESH_UUID_APPARENT_WIND_SPEED_VAL   0x2a72
/** @def BLE_MESH_UUID_APPARENT_WIND_DIR
 *  @brief 视风向特征
 */
#define BLE_MESH_UUID_APPARENT_WIND_DIR         BLE_MESH_UUID_DECLARE_16(0x2a73)
#define BLE_MESH_UUID_APPARENT_WIND_DIR_VAL     0x2a73
/** @def BLE_MESH_UUID_GUST_FACTOR
 *  @brief 阵风因子特性
 */
#define BLE_MESH_UUID_GUST_FACTOR               BLE_MESH_UUID_DECLARE_16(0x2a74)
#define BLE_MESH_UUID_GUST_FACTOR_VAL           0x2a74
/** @def BLE_MESH_UUID_POLLEN_CONCENTRATION
 *  @brief 花粉浓度特征
 */
#define BLE_MESH_UUID_POLLEN_CONCENTRATION      BLE_MESH_UUID_DECLARE_16(0x2a75)
#define BLE_MESH_UUID_POLLEN_CONCENTRATION_VAL  0x2a75
/** @def BLE_MESH_UUID_UV_INDEX
 *  @brief 紫外线指数特性
 */
#define BLE_MESH_UUID_UV_INDEX                  BLE_MESH_UUID_DECLARE_16(0x2a76)
#define BLE_MESH_UUID_UV_INDEX_VAL              0x2a76
/** @def BLE_MESH_UUID_IRRADIANCE
 *  @brief 辐照度特性
 */
#define BLE_MESH_UUID_IRRADIANCE                BLE_MESH_UUID_DECLARE_16(0x2a77)
#define BLE_MESH_UUID_IRRADIANCE_VAL            0x2a77
/** @def BLE_MESH_UUID_RAINFALL
 *  @brief 降雨特征
 */
#define BLE_MESH_UUID_RAINFALL                  BLE_MESH_UUID_DECLARE_16(0x2a78)
#define BLE_MESH_UUID_RAINFALL_VAL              0x2a78
/** @def BLE_MESH_UUID_WIND_CHILL
 *  @brief 风寒特性
 */
#define BLE_MESH_UUID_WIND_CHILL                BLE_MESH_UUID_DECLARE_16(0x2a79)
#define BLE_MESH_UUID_WIND_CHILL_VAL            0x2a79
/** @def BLE_MESH_UUID_HEAT_INDEX
 *  @brief 热指数特性
 */
#define BLE_MESH_UUID_HEAT_INDEX                BLE_MESH_UUID_DECLARE_16(0x2a7a)
#define BLE_MESH_UUID_HEAT_INDEX_VAL            0x2a7a
/** @def BLE_MESH_UUID_DEW_POINT
 *  @brief 露点特性
 */
#define BLE_MESH_UUID_DEW_POINT                 BLE_MESH_UUID_DECLARE_16(0x2a7b)
#define BLE_MESH_UUID_DEW_POINT_VAL             0x2a7b
/** @def BLE_MESH_UUID_DESC_VALUE_CHANGED
 *  @brief 描述符值已更改特征
 */
#define BLE_MESH_UUID_DESC_VALUE_CHANGED        BLE_MESH_UUID_DECLARE_16(0x2a7d)
#define BLE_MESH_UUID_DESC_VALUE_CHANGED_VAL    0x2a7d
/** @def BLE_MESH_UUID_MAGN_FLUX_DENSITY_2D
 *  @brief 磁通密度-2D特性
 */
#define BLE_MESH_UUID_MAGN_FLUX_DENSITY_2D      BLE_MESH_UUID_DECLARE_16(0x2aa0)
#define BLE_MESH_UUID_MAGN_FLUX_DENSITY_2D_VAL  0x2aa0
/** @def BLE_MESH_UUID_MAGN_FLUX_DENSITY_3D
 *  @brief 磁通密度-3D特性
 */
#define BLE_MESH_UUID_MAGN_FLUX_DENSITY_3D      BLE_MESH_UUID_DECLARE_16(0x2aa1)
#define BLE_MESH_UUID_MAGN_FLUX_DENSITY_3D_VAL  0x2aa1
/** @def BLE_MESH_UUID_BAR_PRESSURE_TREND
 *  @brief 大气压力趋势特征
 */
#define BLE_MESH_UUID_BAR_PRESSURE_TREND        BLE_MESH_UUID_DECLARE_16(0x2aa3)
#define BLE_MESH_UUID_BAR_PRESSURE_TREND_VAL    0x2aa3
/** @def BLE_MESH_UUID_MESH_PROV_DATA_IN
 *  @brief 网格资源调配数据输入
 */
#define BLE_MESH_UUID_MESH_PROV_DATA_IN         BLE_MESH_UUID_DECLARE_16(0x2adb)
#define BLE_MESH_UUID_MESH_PROV_DATA_IN_VAL     0x2adb
/** @def BLE_MESH_UUID_MESH_PROV_DATA_OUT
 *  @brief 网格资源调配数据输出
 */
#define BLE_MESH_UUID_MESH_PROV_DATA_OUT        BLE_MESH_UUID_DECLARE_16(0x2adc)
#define BLE_MESH_UUID_MESH_PROV_DATA_OUT_VAL    0x2adc
/** @def BLE_MESH_UUID_MESH_PROXY_DATA_IN
 *  @brief 网格代理数据输入
 */
#define BLE_MESH_UUID_MESH_PROXY_DATA_IN        BLE_MESH_UUID_DECLARE_16(0x2add)
#define BLE_MESH_UUID_MESH_PROXY_DATA_IN_VAL    0x2add
/** @def BLE_MESH_UUID_MESH_PROXY_DATA_OUT
 *  @brief 网格代理数据输出
 */
#define BLE_MESH_UUID_MESH_PROXY_DATA_OUT       BLE_MESH_UUID_DECLARE_16(0x2ade)
#define BLE_MESH_UUID_MESH_PROXY_DATA_OUT_VAL   0x2ade

/*
 * 协议UUID
 */
#define BLE_MESH_UUID_SDP                       BLE_MESH_UUID_DECLARE_16(0x0001)
#define BLE_MESH_UUID_SDP_VAL                   0x0001
#define BLE_MESH_UUID_UDP                       BLE_MESH_UUID_DECLARE_16(0x0002)
#define BLE_MESH_UUID_UDP_VAL                   0x0002
#define BLE_MESH_UUID_RFCOMM                    BLE_MESH_UUID_DECLARE_16(0x0003)
#define BLE_MESH_UUID_RFCOMM_VAL                0x0003
#define BLE_MESH_UUID_TCP                       BLE_MESH_UUID_DECLARE_16(0x0004)
#define BLE_MESH_UUID_TCP_VAL                   0x0004
#define BLE_MESH_UUID_TCS_BIN                   BLE_MESH_UUID_DECLARE_16(0x0005)
#define BLE_MESH_UUID_TCS_BIN_VAL               0x0005
#define BLE_MESH_UUID_TCS_AT                    BLE_MESH_UUID_DECLARE_16(0x0006)
#define BLE_MESH_UUID_TCS_AT_VAL                0x0006
#define BLE_MESH_UUID_ATT                       BLE_MESH_UUID_DECLARE_16(0x0007)
#define BLE_MESH_UUID_ATT_VAL                   0x0007
#define BLE_MESH_UUID_OBEX                      BLE_MESH_UUID_DECLARE_16(0x0008)
#define BLE_MESH_UUID_OBEX_VAL                  0x0008
#define BLE_MESH_UUID_IP                        BLE_MESH_UUID_DECLARE_16(0x0009)
#define BLE_MESH_UUID_IP_VAL                    0x0009
#define BLE_MESH_UUID_FTP                       BLE_MESH_UUID_DECLARE_16(0x000a)
#define BLE_MESH_UUID_FTP_VAL                   0x000a
#define BLE_MESH_UUID_HTTP                      BLE_MESH_UUID_DECLARE_16(0x000c)
#define BLE_MESH_UUID_HTTP_VAL                  0x000c
#define BLE_MESH_UUID_BNEP                      BLE_MESH_UUID_DECLARE_16(0x000f)
#define BLE_MESH_UUID_BNEP_VAL                  0x000f
#define BLE_MESH_UUID_UPNP                      BLE_MESH_UUID_DECLARE_16(0x0010)
#define BLE_MESH_UUID_UPNP_VAL                  0x0010
#define BLE_MESH_UUID_HIDP                      BLE_MESH_UUID_DECLARE_16(0x0011)
#define BLE_MESH_UUID_HIDP_VAL                  0x0011
#define BLE_MESH_UUID_HCRP_CTRL                 BLE_MESH_UUID_DECLARE_16(0x0012)
#define BLE_MESH_UUID_HCRP_CTRL_VAL             0x0012
#define BLE_MESH_UUID_HCRP_DATA                 BLE_MESH_UUID_DECLARE_16(0x0014)
#define BLE_MESH_UUID_HCRP_DATA_VAL             0x0014
#define BLE_MESH_UUID_HCRP_NOTE                 BLE_MESH_UUID_DECLARE_16(0x0016)
#define BLE_MESH_UUID_HCRP_NOTE_VAL             0x0016
#define BLE_MESH_UUID_AVCTP                     BLE_MESH_UUID_DECLARE_16(0x0017)
#define BLE_MESH_UUID_AVCTP_VAL                 0x0017
#define BLE_MESH_UUID_AVDTP                     BLE_MESH_UUID_DECLARE_16(0x0019)
#define BLE_MESH_UUID_AVDTP_VAL                 0x0019
#define BLE_MESH_UUID_CMTP                      BLE_MESH_UUID_DECLARE_16(0x001b)
#define BLE_MESH_UUID_CMTP_VAL                  0x001b
#define BLE_MESH_UUID_UDI                       BLE_MESH_UUID_DECLARE_16(0x001d)
#define BLE_MESH_UUID_UDI_VAL                   0x001d
#define BLE_MESH_UUID_MCAP_CTRL                 BLE_MESH_UUID_DECLARE_16(0x001e)
#define BLE_MESH_UUID_MCAP_CTRL_VAL             0x001e
#define BLE_MESH_UUID_MCAP_DATA                 BLE_MESH_UUID_DECLARE_16(0x001f)
#define BLE_MESH_UUID_MCAP_DATA_VAL             0x001f
#define BLE_MESH_UUID_L2CAP                     BLE_MESH_UUID_DECLARE_16(0x0100)
#define BLE_MESH_UUID_L2CAP_VAL                 0x0100

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _BLE_MESH_UUID_H_ */

