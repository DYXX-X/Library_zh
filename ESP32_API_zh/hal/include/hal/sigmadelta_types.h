// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SIGMADELTA端口号，最大端口号为（SIGMADELTA_NUM_max-1）。
 */
typedef enum {
    SIGMADELTA_PORT_0,      /*!< SIGMADELTA端口0*/
    SIGMADELTA_PORT_MAX,    /*!< SIGMADELTA端口最大值*/
} sigmadelta_port_t;

_Static_assert(SIGMADELTA_PORT_MAX == SOC_SIGMADELTA_NUM, "Sigma-delta port num incorrect.");

/**
 * @brief Sigma delta信道列表
 */
typedef enum {
    SIGMADELTA_CHANNEL_0,   /*!< Sigma delta通道0*/
    SIGMADELTA_CHANNEL_1,   /*!< Sigma delta通道1*/
    SIGMADELTA_CHANNEL_2,   /*!< Sigma delta通道2*/
    SIGMADELTA_CHANNEL_3,   /*!< Sigma delta通道3*/
#if SOC_SIGMADELTA_CHANNEL_NUM > 4
    SIGMADELTA_CHANNEL_4,   /*!< Sigma delta通道4*/
    SIGMADELTA_CHANNEL_5,   /*!< Sigma delta通道5*/
    SIGMADELTA_CHANNEL_6,   /*!< 西格玛-德尔塔通道6*/
    SIGMADELTA_CHANNEL_7,   /*!< Sigma delta通道7*/
#endif
    SIGMADELTA_CHANNEL_MAX, /*!< Sigma delta通道最大值*/
} sigmadelta_channel_t;

/**
 * @brief Sigma delta配置结构
 */
typedef struct {
    sigmadelta_channel_t channel;    /*!< Sigma-delta通道编号*/
    int8_t sigmadelta_duty;          /*!< Sigma-delta占空比，占空比范围为-128至127。*/
    uint8_t sigmadelta_prescale;     /*!< 西格玛-德尔塔预缩放，预缩放范围从0到255。*/
    uint8_t  sigmadelta_gpio;        /*!< Sigma-delta输出io编号，参考gpio。h了解更多详情。*/
} sigmadelta_config_t;

#ifdef __cplusplus
}
#endif

