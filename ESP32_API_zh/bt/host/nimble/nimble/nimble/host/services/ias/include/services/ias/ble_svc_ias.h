/**
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_IAS_TPS_
#define H_BLE_IAS_TPS_

#define BLE_SVC_IAS_UUID16                                      0x1802
#define BLE_SVC_IAS_CHR_UUID16_ALERT_LEVEL                      0x2a06

/* 警报级别定义*/
#define BLE_SVC_IAS_ALERT_LEVEL_NO_ALERT                        0
#define BLE_SVC_IAS_ALERT_LEVEL_MILD_ALERT                      1
#define BLE_SVC_IAS_ALERT_LEVEL_HIGH_ALERT                      2

typedef int ble_svc_ias_event_fn(uint8_t alert_level);

void ble_svc_ias_set_cb(ble_svc_ias_event_fn *cb);
void ble_svc_ias_init(void);

#endif



