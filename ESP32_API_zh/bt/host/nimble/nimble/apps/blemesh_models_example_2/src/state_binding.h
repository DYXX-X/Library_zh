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

#ifndef _STATE_BINDING_H
#define _STATE_BINDING_H

enum state_binding {
	ONPOWERUP = 0x01,
	ONOFF,
	LEVEL,
	DELTA_LEVEL,
	ACTUAL,
	LINEAR,
	CTL,
	IGNORE,

	ONOFF_TEMP,
	LEVEL_TEMP,
	CTL_TEMP,
	IGNORE_TEMP
};

extern u16_t lightness, target_lightness;
extern s16_t temperature, target_temperature;

void state_binding(u8_t lightness, u8_t temperature);
void calculate_lightness_target_values(u8_t type);
void calculate_temp_target_values(u8_t type);

#endif

