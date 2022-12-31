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

#ifndef _TRANSITION_H
#define _TRANSITION_H

#define UNKNOWN_VALUE 0x3F
#define DEVICE_SPECIFIC_RESOLUTION 10

enum level_transition_types {
	LEVEL_TT,
	LEVEL_TT_DELTA,
	LEVEL_TT_MOVE,

	LEVEL_TEMP_TT,
	LEVEL_TEMP_TT_DELTA,
	LEVEL_TEMP_TT_MOVE,
};

struct transition {
	bool just_started;
	u8_t tt;
	u8_t rt;
	u8_t delay;
	u32_t quo_tt;
	u32_t counter;
	u32_t total_duration;
	s64_t start_timestamp;

	struct os_callout timer;
};

extern u8_t transition_type, default_tt;
extern u32_t *ptr_counter;
extern struct os_callout *ptr_timer;

extern struct transition lightness_transition, temp_transition;

extern struct os_callout dummy_timer;

void calculate_rt(struct transition *transition);


void onoff_tt_values(struct generic_onoff_state *state, u8_t tt, u8_t delay);
void level_tt_values(struct generic_level_state *state, u8_t tt, u8_t delay);
void light_lightness_actual_tt_values(struct light_lightness_state *state,
				      u8_t tt, u8_t delay);
void light_lightness_linear_tt_values(struct light_lightness_state *state,
				      u8_t tt, u8_t delay);
void light_ctl_tt_values(struct light_ctl_state *state, u8_t tt, u8_t delay);
void light_ctl_temp_tt_values(struct light_ctl_state *state,
			      u8_t tt, u8_t delay);

void onoff_handler(struct generic_onoff_state *state);
void level_lightness_handler(struct generic_level_state *state);
void level_temp_handler(struct generic_level_state *state);
void light_lightness_actual_handler(struct light_lightness_state *state);
void light_lightness_linear_handler(struct light_lightness_state *state);
void light_ctl_handler(struct light_ctl_state *state);
void light_ctl_temp_handler(struct light_ctl_state *state);

void transition_timers_init(void);

#endif

