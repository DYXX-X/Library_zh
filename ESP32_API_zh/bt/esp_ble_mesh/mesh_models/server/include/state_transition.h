/* 蓝牙：Mesh Generic OnOff、Generic Level、照明和供应商型号
 *
 * SPDX文件版权文本：2018 Vikrant More SPDX FileContributor:2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _STATE_TRANSITION_H_
#define _STATE_TRANSITION_H_

#include "server_common.h"
#include "generic_server.h"
#include "sensor_server.h"
#include "lighting_server.h"
#include "time_scene_server.h"

#ifdef __cplusplus
extern "C" {
#endif

void bt_mesh_server_calc_remain_time(struct bt_mesh_state_transition *transition);

/* 用于获取服务器模型转换时间值的API*/

void generic_onoff_tt_values(struct bt_mesh_gen_onoff_srv *srv,
                             uint8_t trans_time, uint8_t delay);

void generic_level_tt_values(struct bt_mesh_gen_level_srv *srv,
                             uint8_t trans_time, uint8_t delay);

void generic_power_level_tt_values(struct bt_mesh_gen_power_level_srv *srv,
                                   uint8_t trans_time, uint8_t delay);

void light_lightness_actual_tt_values(struct bt_mesh_light_lightness_srv *srv,
                                      uint8_t trans_time, uint8_t delay);

void light_lightness_linear_tt_values(struct bt_mesh_light_lightness_srv *srv,
                                      uint8_t trans_time, uint8_t delay);

void light_ctl_tt_values(struct bt_mesh_light_ctl_srv *srv,
                         uint8_t trans_time, uint8_t delay);

void light_ctl_temp_tt_values(struct bt_mesh_light_ctl_temp_srv *srv,
                              uint8_t trans_time, uint8_t delay);

void light_hsl_tt_values(struct bt_mesh_light_hsl_srv *srv,
                         uint8_t trans_time, uint8_t delay);

void light_hsl_hue_tt_values(struct bt_mesh_light_hsl_hue_srv *srv,
                             uint8_t trans_time, uint8_t delay);

void light_hsl_sat_tt_values(struct bt_mesh_light_hsl_sat_srv *srv,
                             uint8_t trans_time, uint8_t delay);

void light_xyl_tt_values(struct bt_mesh_light_xyl_srv *srv,
                         uint8_t trans_time, uint8_t delay);

void light_lc_tt_values(struct bt_mesh_light_lc_srv *srv,
                        uint8_t trans_time, uint8_t delay);

void scene_tt_values(struct bt_mesh_scene_srv *srv, uint8_t trans_time, uint8_t delay);

/* 服务器模型转换计时器处理程序*/

void generic_onoff_work_handler(struct k_work *work);

void generic_level_work_handler(struct k_work *work);

void generic_power_level_work_handler(struct k_work *work);

void light_lightness_actual_work_handler(struct k_work *work);

void light_lightness_linear_work_handler(struct k_work *work);

void light_ctl_work_handler(struct k_work *work);

void light_ctl_temp_work_handler(struct k_work *work);

void light_hsl_work_handler(struct k_work *work);

void light_hsl_hue_work_handler(struct k_work *work);

void light_hsl_sat_work_handler(struct k_work *work);

void light_xyl_work_handler(struct k_work *work);

void light_lc_work_handler(struct k_work *work);

void scene_recall_work_handler(struct k_work *work);

void bt_mesh_server_stop_transition(struct bt_mesh_state_transition *transition);

void bt_mesh_server_start_transition(struct bt_mesh_state_transition *transition);

#ifdef __cplusplus
}
#endif

#endif /* _STATE_TRANSITION_H_ */

