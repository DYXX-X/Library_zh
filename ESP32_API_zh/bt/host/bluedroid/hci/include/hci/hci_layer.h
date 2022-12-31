/******************************************************************************
 * 版权所有（C）2014谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _HCI_LAYER_H_
#define _HCI_LAYER_H_

#include "stack/bt_types.h"
#include "osi/allocator.h"
#include "osi/osi.h"
#include "osi/future.h"
#include "osi/thread.h"

///// LEGACY DEFINITIONS /////

/* 跨主机/控制器库和堆栈的消息事件掩码*/
#define MSG_EVT_MASK                    0xFF00 /* 等式BT_EVT_MASK*/
#define MSG_SUB_EVT_MASK                0x00FF /* 等式BT_SUB_EVT_MASK*/

/* 从主机/控制器库传递到堆栈的消息事件ID*/
#define MSG_HC_TO_STACK_HCI_ERR        0x1300 /* 等式BT_EVT_TO_BTU_HCIT_ERR*/
#define MSG_HC_TO_STACK_HCI_ACL        0x1100 /* 等式BT_EVT_TO_BTU_HCI_ACL*/
#define MSG_HC_TO_STACK_HCI_SCO        0x1200 /* 等式BT_EVT_TO_BTU_HCI_SCO*/
#define MSG_HC_TO_STACK_HCI_EVT        0x1000 /* 等式BT_EVT_TO_BTU_HCI_EVT*/
#define MSG_HC_TO_STACK_L2C_SEG_XMIT   0x1900 /* 等式BT_EVT_TO_BTU_L2C_SEG_XMIT*/

/* 消息事件ID从堆栈传递到供应商库*/
#define MSG_STACK_TO_HC_HCI_ACL        0x2100 /* 等式BT_EVT_TO_LM_HCI_ACL*/
#define MSG_STACK_TO_HC_HCI_SCO        0x2200 /* 等式BT_EVT_TO_LM_HCI_SCO*/
#define MSG_STACK_TO_HC_HCI_CMD        0x2000 /* 等式BT_EVT_TO_LM_HCI_CMD*/

/* BR/EDR的本地蓝牙控制器ID*/
#define LOCAL_BR_EDR_CONTROLLER_ID      0

///// END LEGACY DEFINITIONS /////

typedef struct hci_hal_t hci_hal_t;
//typedef结构btsnoop_t btsnoop_ t；
typedef struct controller_t controller_t;
//typedef结构hci_inject_t hci_inject；
typedef struct packet_fragmenter_t packet_fragmenter_t;
//typedef结构vendor_t vendor_t；
//typedef结构low_power_manager_t low_poweer_manager_t；

//typedef无符号字符*bdaddr_t；
typedef uint16_t command_opcode_t;

/*
typedef enum｛LPM_DISABLE、LPM_ENABLE、LPM-WAKE_ASSERT、LPM_WAKE_DEASSERT｝low_power_command_t；
*/

typedef void (*command_complete_cb)(BT_HDR *response, void *context);
typedef void (*command_status_cb)(uint8_t status, BT_HDR *command, void *context);

typedef struct hci_t {
    // 发送低功率命令（如果支持），并且低功率管理器已启用。
    //void（*send_low_power_command）（low_power_command_t命令）；

    // 执行后加载序列（在BT堆栈的其余部分初始化后调用）。
    void (*do_postload)(void);

    // 通过HCI层发送命令
    void (*transmit_command)(
        BT_HDR *command,
        command_complete_cb complete_callback,
        command_status_cb status_cb,
        void *context
    );

    future_t *(*transmit_command_futured)(BT_HDR *command);

    // 通过HCI层向下发送一些数据
    void (*transmit_downward)(uint16_t type, void *data);
} hci_t;

const hci_t *hci_layer_get_interface(void);

int hci_start_up(void);
void hci_shut_down(void);

bool hci_host_task_post(uint32_t timeout);

#endif /* _HCI_LAYER_H_ */

