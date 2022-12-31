/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

/* 蓝牙：Mesh Generic OnOff、Generic Level、照明和供应商型号
 *
 * 版权所有（c）2018 Vikrant More
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _DEVICE_COMPOSITION_H
#define _DEVICE_COMPOSITION_H

#define CID_RUNTIME 0x05C3

#define STATE_OFF	0x00
#define STATE_ON	0x01
#define STATE_DEFAULT	0x01
#define STATE_RESTORE	0x02

/* 以下4个值符合网格模型规范*/
#define LIGHTNESS_MIN	0x0001
#define LIGHTNESS_MAX	0xFFFF
#define TEMP_MIN	0x0320
#define TEMP_MAX	0x4E20

/* 参考网格模型规范7.2*/
#define RANGE_SUCCESSFULLY_UPDATED	0x00
#define CANNOT_SET_RANGE_MIN		0x01
#define CANNOT_SET_RANGE_MAX		0x02

struct generic_onoff_state {
	u8_t onoff;
	u8_t target_onoff;

	u8_t last_tid;
	u16_t last_src_addr;
	u16_t last_dst_addr;
	s64_t last_msg_timestamp;

	s32_t tt_delta;

	struct transition *transition;
};

struct generic_level_state {
	s16_t level;
	s16_t target_level;

	s16_t last_level;
	s32_t last_delta;

	u8_t last_tid;
	u16_t last_src_addr;
	u16_t last_dst_addr;
	s64_t last_msg_timestamp;

	s32_t tt_delta;

	struct transition *transition;
};

struct generic_onpowerup_state {
	u8_t onpowerup;
};

struct gen_def_trans_time_state {
	u8_t tt;
};

struct vendor_state {
	int current;
	u32_t response;
	u8_t last_tid;
	u16_t last_src_addr;
	u16_t last_dst_addr;
	s64_t last_msg_timestamp;
};

struct light_lightness_state {
	u16_t linear;
	u16_t target_linear;

	u16_t actual;
	u16_t target_actual;

	u16_t last;
	u16_t def;

	u8_t status_code;
	u16_t light_range_min;
	u16_t light_range_max;
	u32_t lightness_range;

	u8_t last_tid;
	u16_t last_src_addr;
	u16_t last_dst_addr;
	s64_t last_msg_timestamp;

	s32_t tt_delta_actual;
	s32_t tt_delta_linear;

	struct transition *transition;
};

struct light_ctl_state {
	u16_t lightness;
	u16_t target_lightness;

	u16_t temp;
	u16_t target_temp;

	s16_t delta_uv;
	s16_t target_delta_uv;

	u8_t status_code;
	u16_t temp_range_min;
	u16_t temp_range_max;
	u32_t temperature_range;

	u16_t lightness_def;
	u16_t temp_def;
	u32_t lightness_temp_def;
	s16_t delta_uv_def;

	u32_t lightness_temp_last;

	u8_t last_tid;
	u16_t last_src_addr;
	u16_t last_dst_addr;
	s64_t last_msg_timestamp;

	s32_t tt_delta_lightness;
	s32_t tt_delta_temp;
	s32_t tt_delta_duv;

	struct transition *transition;
};

extern struct generic_onoff_state gen_onoff_srv_root_user_data;
extern struct generic_level_state gen_level_srv_root_user_data;
extern struct gen_def_trans_time_state gen_def_trans_time_srv_user_data;
extern struct generic_onpowerup_state gen_power_onoff_srv_user_data;
extern struct light_lightness_state light_lightness_srv_user_data;
extern struct light_ctl_state light_ctl_srv_user_data;
extern struct generic_level_state gen_level_srv_s0_user_data;

extern struct bt_mesh_model root_models[];
extern struct bt_mesh_model vnd_models[];
extern struct bt_mesh_model s0_models[];

extern const struct bt_mesh_comp comp;

void gen_onoff_publish(struct bt_mesh_model *model);
void gen_level_publish(struct bt_mesh_model *model);
void light_lightness_publish(struct bt_mesh_model *model);
void light_lightness_linear_publish(struct bt_mesh_model *model);
void light_ctl_publish(struct bt_mesh_model *model);
void light_ctl_temp_publish(struct bt_mesh_model *model);

#endif

