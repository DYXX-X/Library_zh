// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ESP32-S3具有1个SIGMADELTA外围设备。
#define SIGMADELTA_PORT_0             (0) /*!< SIGMADELTA端口0*/
#define SIGMADELTA_PORT_MAX           (1) /*!< SIGMADELTA端口最大值*/
#define SOC_SIGMADELTA_NUM            (SIGMADELTA_PORT_MAX)

#define SIGMADELTA_CHANNEL_0   (0)    /*!< Sigma delta通道0*/
#define SIGMADELTA_CHANNEL_1   (1)    /*!< Sigma delta通道1*/
#define SIGMADELTA_CHANNEL_2   (2)    /*!< Sigma delta通道2*/
#define SIGMADELTA_CHANNEL_3   (3)    /*!< Sigma delta通道3*/
#define SIGMADELTA_CHANNEL_4   (4)    /*!< Sigma delta通道4*/
#define SIGMADELTA_CHANNEL_5   (5)    /*!< Sigma delta通道5*/
#define SIGMADELTA_CHANNEL_6   (6)    /*!< 西格玛-德尔塔通道6*/
#define SIGMADELTA_CHANNEL_7   (7)    /*!< Sigma delta通道7*/
#define SIGMADELTA_CHANNEL_MAX (8)

#ifdef __cplusplus
}
#endif

