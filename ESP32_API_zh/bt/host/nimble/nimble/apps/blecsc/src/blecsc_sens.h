/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLECSC_SENSOR_
#define H_BLECSC_SENSOR_

#include "modlog/modlog.h"
#include "nimble/ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 自行车速度和Cadence配置*/
#define GATT_CSC_UUID                           0x1816
#define GATT_CSC_MEASUREMENT_UUID               0x2A5B
#define GATT_CSC_FEATURE_UUID                   0x2A5C
#define GATT_SENSOR_LOCATION_UUID               0x2A5D
#define GATT_SC_CONTROL_POINT_UUID              0x2A55
/* 设备信息配置*/
#define GATT_DEVICE_INFO_UUID                   0x180A
#define GATT_MANUFACTURER_NAME_UUID             0x2A29
#define GATT_MODEL_NUMBER_UUID                  0x2A24

/*CSC测量标志*/
#define CSC_MEASUREMENT_WHEEL_REV_PRESENT       0x01
#define CSC_MEASUREMENT_CRANK_REV_PRESENT       0x02

/* CSC功能标志*/
#define CSC_FEATURE_WHEEL_REV_DATA              0x01
#define CSC_FEATURE_CRANK_REV_DATA              0x02
#define CSC_FEATURE_MULTIPLE_SENSOR_LOC         0x04

/* 传感器位置枚举*/
#define SENSOR_LOCATION_OTHER                   0
#define SENSOR_LOCATION_TOP_OF_SHOE             1
#define SENSOR_LOCATION_IN_SHOE                 2
#define SENSOR_LOCATION_HIP                     3
#define SENSOR_LOCATION_FRONT_WHEEL             4
#define SENSOR_LOCATION_LEFT_CRANK              5
#define SENSOR_LOCATION_RIGHT_CRANK             6
#define SENSOR_LOCATION_LEFT_PEDAL              7
#define SENSOR_LOCATION_RIGHT_PEDAL             8
#define SENSOR_LOCATION_FROT_HUB                9
#define SENSOR_LOCATION_REAR_DROPOUT            10
#define SENSOR_LOCATION_CHAINSTAY               11
#define SENSOR_LOCATION_REAR_WHEEL              12
#define SENSOR_LOCATION_REAR_HUB                13
#define SENSOR_LOCATION_CHEST                   14
#define SENSOR_LOCATION_SPIDER                  15
#define SENSOR_LOCATION_CHAIN_RING              16

/* SC控制点操作代码*/
#define SC_CP_OP_SET_CUMULATIVE_VALUE           1
#define SC_CP_OP_START_SENSOR_CALIBRATION       2
#define SC_CP_OP_UPDATE_SENSOR_LOCATION         3
#define SC_CP_OP_REQ_SUPPORTED_SENSOR_LOCATIONS 4
#define SC_CP_OP_RESPONSE                       16

/*SC控制点响应值*/
#define SC_CP_RESPONSE_SUCCESS                  1
#define SC_CP_RESPONSE_OP_NOT_SUPPORTED         2
#define SC_CP_RESPONSE_INVALID_PARAM            3
#define SC_CP_RESPONSE_OP_FAILED                4

/* CSC模拟配置*/
#define CSC_FEATURES                         (CSC_FEATURE_WHEEL_REV_DATA | \
                                              CSC_FEATURE_CRANK_REV_DATA |\
                                              CSC_FEATURE_MULTIPLE_SENSOR_LOC)

struct ble_csc_measurement_state {
    uint32_t cumulative_wheel_rev;
    uint16_t last_wheel_evt_time;
    uint16_t cumulative_crank_rev;
    uint16_t last_crank_evt_time;
};

extern uint16_t csc_measurement_handle;
extern uint16_t csc_control_point_handle;

int gatt_svr_init(struct ble_csc_measurement_state * csc_measurement_state);
int gatt_svr_chr_notify_csc_measurement(uint16_t conn_handle);
void gatt_svr_set_cp_indicate(uint8_t indication_status);

#ifdef __cplusplus
}
#endif

#endif

