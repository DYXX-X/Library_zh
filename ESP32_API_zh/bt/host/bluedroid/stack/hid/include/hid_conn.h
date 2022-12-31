/******************************************************************************
 * 版权所有（C）2002-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 此文件包含HID连接内部定义
 *
 ******************************************************************************/

#ifndef HID_CONN_H
#define HID_CONN_H

#include "common/bt_defs.h"

#if (BT_HID_INCLUDED == TRUE)

/* 定义HID连接块
*/
typedef struct hid_conn {
#define HID_CONN_STATE_UNUSED               (0)
#define HID_CONN_STATE_CONNECTING_CTRL      (1)
#define HID_CONN_STATE_CONNECTING_INTR      (2)
#define HID_CONN_STATE_CONFIG               (3)
#define HID_CONN_STATE_CONNECTED            (4)
#define HID_CONN_STATE_DISCONNECTING        (5)
#define HID_CONN_STATE_SECURITY             (6)
#define HID_CONN_STATE_DISCONNECTING_CTRL   (7)
#define HID_CONN_STATE_DISCONNECTING_INTR   (8)

    UINT8             conn_state;

#define HID_CONN_FLAGS_IS_ORIG              (0x01)
#define HID_CONN_FLAGS_HIS_CTRL_CFG_DONE    (0x02)
#define HID_CONN_FLAGS_MY_CTRL_CFG_DONE     (0x04)
#define HID_CONN_FLAGS_HIS_INTR_CFG_DONE    (0x08)
#define HID_CONN_FLAGS_MY_INTR_CFG_DONE     (0x10)
#define HID_CONN_FLAGS_ALL_CONFIGURED       (0x1E)        /* 所有的配置都完成了*/
#define HID_CONN_FLAGS_CONGESTED            (0x20)
#define HID_CONN_FLAGS_INACTIVE             (0x40)

    UINT8             conn_flags;

    UINT8             ctrl_id;
    UINT16            ctrl_cid;
    UINT16            intr_cid;
    UINT16            rem_mtu_size;
    UINT16            disc_reason;                       /* 断开连接的原因（对于HID_HDEV_EVT_CLOSE）*/
    TIMER_LIST_ENT    timer_entry;
} tHID_CONN;

#define HID_SEC_CHN   1
#define HID_NOSEC_CHN 2
#define HIDD_SEC_CHN 3
#define HIDD_NOSEC_CHN 4

#endif  ///BT_HID_INCLUDED == TRUE
#endif

