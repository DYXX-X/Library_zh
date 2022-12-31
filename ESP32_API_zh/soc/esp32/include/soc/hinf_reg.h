// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
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
#ifndef _SOC_HINF_REG_H_
#define _SOC_HINF_REG_H_


#include "soc.h"
#define HINF_CFG_DATA0_REG          (DR_REG_HINF_BASE + 0x0)
/* HINF_DEVICE_ID_FN1：R/W；比特位置：[31:16]；默认值：16'h2222；*/
/*说明：*/
#define HINF_DEVICE_ID_FN1  0x0000FFFF
#define HINF_DEVICE_ID_FN1_M  ((HINF_DEVICE_ID_FN1_V)<<(HINF_DEVICE_ID_FN1_S))
#define HINF_DEVICE_ID_FN1_V  0xFFFF
#define HINF_DEVICE_ID_FN1_S  16
/* HINF_USER_ID_FN1：R/W；比特位置：[15:0]；默认值：16'6666；*/
/*说明：*/
#define HINF_USER_ID_FN1  0x0000FFFF
#define HINF_USER_ID_FN1_M  ((HINF_USER_ID_FN1_V)<<(HINF_USER_ID_FN1_S))
#define HINF_USER_ID_FN1_V  0xFFFF
#define HINF_USER_ID_FN1_S  0

#define HINF_CFG_DATA1_REG          (DR_REG_HINF_BASE + 0x4)
/* HINF_SDIO20_CONF1:R/W；位位置：[31:29]；默认值：3'h0；*/
/*说明：*/
#define HINF_SDIO20_CONF1  0x00000007
#define HINF_SDIO20_CONF1_M  ((HINF_SDIO20_CONF1_V)<<(HINF_SDIO20_CONF1_S))
#define HINF_SDIO20_CONF1_V  0x7
#define HINF_SDIO20_CONF1_S  29
/* HINF_FUNC2_EPS:RO；位位置：[28]；默认值：1’b0；*/
/*说明：*/
#define HINF_FUNC2_EPS  (BIT(28))
#define HINF_FUNC2_EPS_M  (BIT(28))
#define HINF_FUNC2_EPS_V  0x1
#define HINF_FUNC2_EPS_S  28
/* HINF_SDIO_VER:R/W；比特位置：[27:16]；默认值：12'h111；*/
/*说明：*/
#define HINF_SDIO_VER  0x00000FFF
#define HINF_SDIO_VER_M  ((HINF_SDIO_VER_V)<<(HINF_SDIO_VER_S))
#define HINF_SDIO_VER_V  0xFFF
#define HINF_SDIO_VER_S  16
/* HINF_SDIO20_CONF0:R/W；比特位置：[15:12]；默认值：4'b0；*/
/*说明：*/
#define HINF_SDIO20_CONF0  0x0000000F
#define HINF_SDIO20_CONF0_M  ((HINF_SDIO20_CONF0_V)<<(HINF_SDIO20_CONF0_S))
#define HINF_SDIO20_CONF0_V  0xF
#define HINF_SDIO20_CONF0_S  12
/* HINF_IOENABLE1:RO；位位置：[11]；默认值：1’b0；*/
/*说明：*/
#define HINF_IOENABLE1  (BIT(11))
#define HINF_IOENABLE1_M  (BIT(11))
#define HINF_IOENABLE1_V  0x1
#define HINF_IOENABLE1_S  11
/* HINF_EMP:RO；位位置：[10]；默认值：1’b0；*/
/*说明：*/
#define HINF_EMP  (BIT(10))
#define HINF_EMP_M  (BIT(10))
#define HINF_EMP_V  0x1
#define HINF_EMP_S  10
/* HINF_FUNC1_EPS:RO；位位置：[9]；默认值：1’b0；*/
/*说明：*/
#define HINF_FUNC1_EPS  (BIT(9))
#define HINF_FUNC1_EPS_M  (BIT(9))
#define HINF_FUNC1_EPS_V  0x1
#define HINF_FUNC1_EPS_S  9
/* HINF_CD_isable:RO；位位置：[8]；默认值：1’b0；*/
/*说明：*/
#define HINF_CD_DISABLE  (BIT(8))
#define HINF_CD_DISABLE_M  (BIT(8))
#define HINF_CD_DISABLE_V  0x1
#define HINF_CD_DISABLE_S  8
/* HINF_IOENABLE2:RO；位位置：[7]；默认值：1’b0；*/
/*说明：*/
#define HINF_IOENABLE2  (BIT(7))
#define HINF_IOENABLE2_M  (BIT(7))
#define HINF_IOENABLE2_V  0x1
#define HINF_IOENABLE2_S  7
/* HINF_SDIO_INT_smask：R/W；位位置：[6]；默认值：1’b0；*/
/*说明：*/
#define HINF_SDIO_INT_MASK  (BIT(6))
#define HINF_SDIO_INT_MASK_M  (BIT(6))
#define HINF_SDIO_INT_MASK_V  0x1
#define HINF_SDIO_INT_MASK_S  6
/* HINF_SDIO_IOREADY2:R/W；位位置：[5]；默认值：1’b0；*/
/*说明：*/
#define HINF_SDIO_IOREADY2  (BIT(5))
#define HINF_SDIO_IOREADY2_M  (BIT(5))
#define HINF_SDIO_IOREADY2_V  0x1
#define HINF_SDIO_IOREADY2_S  5
/* HINF_SDIO_CD_ENABLE:R/W；位位置：[4]；默认值：1’b1；*/
/*说明：*/
#define HINF_SDIO_CD_ENABLE  (BIT(4))
#define HINF_SDIO_CD_ENABLE_M  (BIT(4))
#define HINF_SDIO_CD_ENABLE_V  0x1
#define HINF_SDIO_CD_ENABLE_S  4
/* 高速模式：RO；位位置：[3]；默认值：1’b0；*/
/*说明：*/
#define HINF_HIGHSPEED_MODE  (BIT(3))
#define HINF_HIGHSPEED_MODE_M  (BIT(3))
#define HINF_HIGHSPEED_MODE_V  0x1
#define HINF_HIGHSPEED_MODE_S  3
/* HINF_高速启用：R/W；位位置：[2]；默认值：1’b0；*/
/*说明：*/
#define HINF_HIGHSPEED_ENABLE  (BIT(2))
#define HINF_HIGHSPEED_ENABLE_M  (BIT(2))
#define HINF_HIGHSPEED_ENABLE_V  0x1
#define HINF_HIGHSPEED_ENABLE_S  2
/* HINF_SDIO_IOREADY1:R/W；位位置：[1]；默认值：1’b0；*/
/*说明：*/
#define HINF_SDIO_IOREADY1  (BIT(1))
#define HINF_SDIO_IOREADY1_M  (BIT(1))
#define HINF_SDIO_IOREADY1_V  0x1
#define HINF_SDIO_IOREADY1_S  1
/* HINF_SDIO_ENABLE:R/W；位位置：[0]；默认值：1’b1；*/
/*说明：*/
#define HINF_SDIO_ENABLE  (BIT(0))
#define HINF_SDIO_ENABLE_M  (BIT(0))
#define HINF_SDIO_ENABLE_V  0x1
#define HINF_SDIO_ENABLE_S  0

#define HINF_CFG_DATA7_REG          (DR_REG_HINF_BASE + 0x1C)
/* HINF_SDIO_IOREADY0:R/W；位位置：[17]；默认值：1’b1；*/
/*说明：*/
#define HINF_SDIO_IOREADY0  (BIT(17))
#define HINF_SDIO_IOREADY0_M  (BIT(17))
#define HINF_SDIO_IOREADY0_V  0x1
#define HINF_SDIO_IOREADY0_S  17
/* HINF_SDIO_RST:R/W；位位置：[16]；默认值：1’b0；*/
/*说明：*/
#define HINF_SDIO_RST  (BIT(16))
#define HINF_SDIO_RST_M  (BIT(16))
#define HINF_SDIO_RST_V  0x1
#define HINF_SDIO_RST_S  16
/* HINF_CHIP_STATE:R/W；比特位置：[15:8]；默认值：8'b0；*/
/*说明：*/
#define HINF_CHIP_STATE  0x000000FF
#define HINF_CHIP_STATE_M  ((HINF_CHIP_STATE_V)<<(HINF_CHIP_STATE_S))
#define HINF_CHIP_STATE_V  0xFF
#define HINF_CHIP_STATE_S  8
/* HINF_PIN_STATE:R/W；位位置：[7:0]；默认值：8'b0；*/
/*说明：*/
#define HINF_PIN_STATE  0x000000FF
#define HINF_PIN_STATE_M  ((HINF_PIN_STATE_V)<<(HINF_PIN_STATE_S))
#define HINF_PIN_STATE_V  0xFF
#define HINF_PIN_STATE_S  0

#define HINF_CIS_CONF0_REG          (DR_REG_HINF_BASE + 0x20)
/* HINF_CIS_CONF_W0:R/W；位位置：[31:0]；默认值：32'ffffffff；*/
/*说明：*/
#define HINF_CIS_CONF_W0  0xFFFFFFFF
#define HINF_CIS_CONF_W0_M  ((HINF_CIS_CONF_W0_V)<<(HINF_CIS_CONF_W0_S))
#define HINF_CIS_CONF_W0_V  0xFFFFFFFF
#define HINF_CIS_CONF_W0_S  0

#define HINF_CIS_CONF1_REG          (DR_REG_HINF_BASE + 0x24)
/* HINF_CIS_CONF_W1:R/W；位位置：[31:0]；默认值：32'ffffffff；*/
/*说明：*/
#define HINF_CIS_CONF_W1  0xFFFFFFFF
#define HINF_CIS_CONF_W1_M  ((HINF_CIS_CONF_W1_V)<<(HINF_CIS_CONF_W1_S))
#define HINF_CIS_CONF_W1_V  0xFFFFFFFF
#define HINF_CIS_CONF_W1_S  0

#define HINF_CIS_CONF2_REG          (DR_REG_HINF_BASE + 0x28)
/* HINF_CIS_CONF_W2:R/W；位位置：[31:0]；默认值：32'ffffffff；*/
/*说明：*/
#define HINF_CIS_CONF_W2  0xFFFFFFFF
#define HINF_CIS_CONF_W2_M  ((HINF_CIS_CONF_W2_V)<<(HINF_CIS_CONF_W2_S))
#define HINF_CIS_CONF_W2_V  0xFFFFFFFF
#define HINF_CIS_CONF_W2_S  0

#define HINF_CIS_CONF3_REG          (DR_REG_HINF_BASE + 0x2C)
/* HINF_CIS_CONF_W3：R/W；位位置：[31:0]；默认值：32'ffffffff；*/
/*说明：*/
#define HINF_CIS_CONF_W3  0xFFFFFFFF
#define HINF_CIS_CONF_W3_M  ((HINF_CIS_CONF_W3_V)<<(HINF_CIS_CONF_W3_S))
#define HINF_CIS_CONF_W3_V  0xFFFFFFFF
#define HINF_CIS_CONF_W3_S  0

#define HINF_CIS_CONF4_REG          (DR_REG_HINF_BASE + 0x30)
/* HINF_CIS_CONF_W4:R/W；位位置：[31:0]；默认值：32'ffffffff；*/
/*说明：*/
#define HINF_CIS_CONF_W4  0xFFFFFFFF
#define HINF_CIS_CONF_W4_M  ((HINF_CIS_CONF_W4_V)<<(HINF_CIS_CONF_W4_S))
#define HINF_CIS_CONF_W4_V  0xFFFFFFFF
#define HINF_CIS_CONF_W4_S  0

#define HINF_CIS_CONF5_REG          (DR_REG_HINF_BASE + 0x34)
/* HINF_CIS_CONF_W5:R/W；位位置：[31:0]；默认值：32'ffffffff；*/
/*说明：*/
#define HINF_CIS_CONF_W5  0xFFFFFFFF
#define HINF_CIS_CONF_W5_M  ((HINF_CIS_CONF_W5_V)<<(HINF_CIS_CONF_W5_S))
#define HINF_CIS_CONF_W5_V  0xFFFFFFFF
#define HINF_CIS_CONF_W5_S  0

#define HINF_CIS_CONF6_REG          (DR_REG_HINF_BASE + 0x38)
/* HINF_CIS_CONF_W6:R/W；位位置：[31:0]；默认值：32'ffffffff；*/
/*说明：*/
#define HINF_CIS_CONF_W6  0xFFFFFFFF
#define HINF_CIS_CONF_W6_M  ((HINF_CIS_CONF_W6_V)<<(HINF_CIS_CONF_W6_S))
#define HINF_CIS_CONF_W6_V  0xFFFFFFFF
#define HINF_CIS_CONF_W6_S  0

#define HINF_CIS_CONF7_REG          (DR_REG_HINF_BASE + 0x3C)
/* HINF_CIS_CONF_W7:R/W；位位置：[31:0]；默认值：32'ffffffff；*/
/*说明：*/
#define HINF_CIS_CONF_W7  0xFFFFFFFF
#define HINF_CIS_CONF_W7_M  ((HINF_CIS_CONF_W7_V)<<(HINF_CIS_CONF_W7_S))
#define HINF_CIS_CONF_W7_V  0xFFFFFFFF
#define HINF_CIS_CONF_W7_S  0

#define HINF_CFG_DATA16_REG          (DR_REG_HINF_BASE + 0x40)
/* HINF_DEVICE_ID_FN2:R/W；比特位置：[31:16]；默认值：16'h3333；*/
/*说明：*/
#define HINF_DEVICE_ID_FN2  0x0000FFFF
#define HINF_DEVICE_ID_FN2_M  ((HINF_DEVICE_ID_FN2_V)<<(HINF_DEVICE_ID_FN2_S))
#define HINF_DEVICE_ID_FN2_V  0xFFFF
#define HINF_DEVICE_ID_FN2_S  16
/* HINF_USER_ID_FN2:R/W；比特位置：[15:0]；默认值：16'6666；*/
/*说明：*/
#define HINF_USER_ID_FN2  0x0000FFFF
#define HINF_USER_ID_FN2_M  ((HINF_USER_ID_FN2_V)<<(HINF_USER_ID_FN2_S))
#define HINF_USER_ID_FN2_V  0xFFFF
#define HINF_USER_ID_FN2_S  0

#define HINF_DATE_REG          (DR_REG_HINF_BASE + 0xFC)
/* HINF_SDIO_DATE:R/W；位位置：[31:0]；默认值：32'h15030200；*/
/*说明：*/
#define HINF_SDIO_DATE  0xFFFFFFFF
#define HINF_SDIO_DATE_M  ((HINF_SDIO_DATE_V)<<(HINF_SDIO_DATE_S))
#define HINF_SDIO_DATE_V  0xFFFFFFFF
#define HINF_SDIO_DATE_S  0




#endif /*_SOC_HINF_REG_H_ */

