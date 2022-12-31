/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_XCVR_
#define H_BLE_XCVR_

#ifdef __cplusplus
extern "C" {
#endif

/* 收发器特定定义*/
#define XCVR_RX_START_DELAY_USECS     (140)
#define XCVR_TX_START_DELAY_USECS     (140)
#define XCVR_PROC_DELAY_USECS         (100)
#define XCVR_TX_SCHED_DELAY_USECS     \
    (XCVR_TX_START_DELAY_USECS + XCVR_PROC_DELAY_USECS)
#define XCVR_RX_SCHED_DELAY_USECS     \
    (XCVR_RX_START_DELAY_USECS + XCVR_PROC_DELAY_USECS)

/*
 * 定义硬件白名单大小。这是可能的白名单总大小；不一定是将要使用的大小（可能更小）
 */
#define BLE_HW_WHITE_LIST_SIZE        (0)

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_XCVR_ */

