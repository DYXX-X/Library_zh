// 版权所有2010-2016 Espressif Systems（上海）私人有限公司
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

#ifndef _SOC_BB_REG_H_
#define _SOC_BB_REG_H_

/* 一些基带控制寄存器。此处定义的PU/PD字段用于睡眠相关函数。
 */

#define BBPD_CTRL (DR_REG_BB_BASE + 0x0054)
#define BB_FFT_FORCE_PU (BIT(3))
#define BB_FFT_FORCE_PU_M (BIT(3))
#define BB_FFT_FORCE_PU_V 1
#define BB_FFT_FORCE_PU_S 3
#define BB_FFT_FORCE_PD (BIT(2))
#define BB_FFT_FORCE_PD_M (BIT(2))
#define BB_FFT_FORCE_PD_V 1
#define BB_FFT_FORCE_PD_S 2
#define BB_DC_EST_FORCE_PU (BIT(1))
#define BB_DC_EST_FORCE_PU_M (BIT(1))
#define BB_DC_EST_FORCE_PU_V 1
#define BB_DC_EST_FORCE_PU_S 1
#define BB_DC_EST_FORCE_PD (BIT(0))
#define BB_DC_EST_FORCE_PD_M (BIT(0))
#define BB_DC_EST_FORCE_PD_V 1
#define BB_DC_EST_FORCE_PD_S 0


#endif /* _SOC_BB_REG_H_ */

