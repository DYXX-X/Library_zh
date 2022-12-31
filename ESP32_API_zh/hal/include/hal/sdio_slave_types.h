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

#include "soc/soc.h"

///发送到主机的中断掩码。
typedef enum {
    SDIO_SLAVE_HOSTINT_BIT0 = BIT(0),   ///<通用中断位0。
    SDIO_SLAVE_HOSTINT_BIT1 = BIT(1),
    SDIO_SLAVE_HOSTINT_BIT2 = BIT(2),
    SDIO_SLAVE_HOSTINT_BIT3 = BIT(3),
    SDIO_SLAVE_HOSTINT_BIT4 = BIT(4),
    SDIO_SLAVE_HOSTINT_BIT5 = BIT(5),
    SDIO_SLAVE_HOSTINT_BIT6 = BIT(6),
    SDIO_SLAVE_HOSTINT_BIT7 = BIT(7),
    SDIO_SLAVE_HOSTINT_SEND_NEW_PACKET = BIT(23), ///<新数据包可用
} sdio_slave_hostint_t;


///SDIO从机的定时
typedef enum {
    SDIO_SLAVE_TIMING_PSEND_PSAMPLE = 0,/**< 发送到posedge，并在posedge采样。HS模式的默认值。通常情况下，在DS模式下使用它是没有问题的。
                                         */
    SDIO_SLAVE_TIMING_NSEND_PSAMPLE    ,///<在负边缘发送，在偏旁采样。DS模式及其以下的默认值。
    SDIO_SLAVE_TIMING_PSEND_NSAMPLE,    ///<在偏旁发送，在负边采样
    SDIO_SLAVE_TIMING_NSEND_NSAMPLE,    ///<在负边缘发送，在负边缘采样
} sdio_slave_timing_t;

///SDIO从模式配置
typedef enum {
    SDIO_SLAVE_SEND_STREAM = 0, ///＜流模式，如果可能，所有要发送的数据包将合并为一个
    SDIO_SLAVE_SEND_PACKET = 1, ///<包模式，一个包将被相继发送（如果最后一个包被发送，则只增加Packet_len）。
} sdio_slave_sending_mode_t;

