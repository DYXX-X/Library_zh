/******************************************************************************
 * 版权所有（C）1999-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 该文件包含主要的蓝牙上层定义。L2CAP RFCOMM、SDP和BTIf的Broadcom实现作为一个GKI任务运行。btu_task在它们之间切换。
 *
 ******************************************************************************/

#ifndef BTU_H
#define BTU_H

#include "common/bt_target.h"
#include "common/bt_defs.h"
#include "osi/thread.h"

// 哈克：暂时的黑暗魔法
#define BTU_POST_TO_TASK_NO_GOOD_HORRIBLE_HACK 0x1700 // 看起来在bt_types中没有使用…这里没有
typedef struct {
    void (*callback)(BT_HDR *);
} post_to_task_hack_t;

typedef struct {
    void (*callback)(BT_HDR *);
    BT_HDR *response;
    void *context;
} command_complete_hack_t;

typedef struct {
    void (*callback)(BT_HDR *);
    uint8_t status;
    BT_HDR *command;
    void *context;
} command_status_hack_t;

/* 回调
*/
typedef void (*tBTU_TIMER_CALLBACK)(TIMER_LIST_ENT *p_tle);
typedef void (*tBTU_EVENT_CALLBACK)(BT_HDR *p_hdr);


/* 定义BTU维护的计时器类型
*/
#define BTU_TTYPE_BTM_DEV_CTL       1
#define BTU_TTYPE_L2CAP_LINK        2
#define BTU_TTYPE_L2CAP_CHNL        3
#define BTU_TTYPE_L2CAP_HOLD        4
#define BTU_TTYPE_SDP               5
#define BTU_TTYPE_BTM_SCO           6
#define BTU_TTYPE_BTM_ACL           9
#define BTU_TTYPE_BTM_RMT_NAME      10
#define BTU_TTYPE_RFCOMM_MFC        11
#define BTU_TTYPE_RFCOMM_PORT       12
#define BTU_TTYPE_TCS_L2CAP         13
#define BTU_TTYPE_TCS_CALL          14
#define BTU_TTYPE_TCS_WUG           15
#define BTU_TTYPE_AUTO_SYNC         16
#define BTU_TTYPE_CTP_RECON         17
#define BTU_TTYPE_CTP_T100          18
#define BTU_TTYPE_CTP_GUARD         19
#define BTU_TTYPE_CTP_DETACH        20

#define BTU_TTYPE_SPP_CONN_RETRY    21
#define BTU_TTYPE_USER_FUNC         22

#define BTU_TTYPE_FTP_DISC          25
#define BTU_TTYPE_OPP_DISC          26

#define BTU_TTYPE_CTP_TL_DISCVY     28
#define BTU_TTYPE_IPFRAG_TIMER      29
#define BTU_TTYPE_HSP2_AT_CMD_TO    30
#define BTU_TTYPE_HSP2_REPEAT_RING  31

#define BTU_TTYPE_CTP_GW_INIT       32
#define BTU_TTYPE_CTP_GW_CONN       33
#define BTU_TTYPE_CTP_GW_IDLE       35

#define BTU_TTYPE_ICP_L2CAP         36
#define BTU_TTYPE_ICP_T100          37

#define BTU_TTYPE_HSP2_WAIT_OK      38

/* HCRP计时器*/
#define BTU_TTYPE_HCRP_NOTIF_REG    39
#define BTU_TTYPE_HCRP_PROTO_RSP    40
#define BTU_TTYPE_HCRP_CR_GRANT     41
#define BTU_TTYPE_HCRP_CR_CHECK     42
#define BTU_TTYPE_HCRP_W4_CLOSE     43

/* HCRPM计时器*/
#define BTU_TTYPE_HCRPM_NOTIF_REG   44
#define BTU_TTYPE_HCRPM_NOTIF_KEEP  45
#define BTU_TTYPE_HCRPM_API_RSP     46
#define BTU_TTYPE_HCRPM_W4_OPEN     47
#define BTU_TTYPE_HCRPM_W4_CLOSE    48

/* BNEP计时器*/
#define BTU_TTYPE_BNEP              50

#define BTU_TTYPE_HSP2_SDP_FAIL_TO  55
#define BTU_TTYPE_HSP2_SDP_RTRY_TO  56

/* BTU内部*/
/* 未使用的60*/

#define BTU_TTYPE_AVDT_CCB_RET      61
#define BTU_TTYPE_AVDT_CCB_RSP      62
#define BTU_TTYPE_AVDT_CCB_IDLE     63
#define BTU_TTYPE_AVDT_SCB_TC       64

#define BTU_TTYPE_HID_DEV_REPAGE_TO 65
#define BTU_TTYPE_HID_HOST_REPAGE_TO 66

#define BTU_TTYPE_HSP2_DELAY_CKPD_RCV 67

#define BTU_TTYPE_SAP_TO            68

/* BPP计时器*/
#define BTU_TTYPE_BPP_REF_CHNL     72

/* LP HC怠速定时器*/
#define BTU_TTYPE_LP_HC_IDLE_TO 74

/* 补丁RAM计时器*/
#define BTU_TTYPE_PATCHRAM_TO 75

/* eL2CAP信息请求和其他原型命令计时器*/
#define BTU_TTYPE_L2CAP_FCR_ACK     78
#define BTU_TTYPE_L2CAP_INFO        79
/* L2CAP更新连接参数计时器*/
#define BTU_TTYPE_L2CAP_UPDA_CONN_PARAMS            80

#define BTU_TTYPE_MCA_CCB_RSP                       98

/* BLE活动的BTU内部计时器*/
#define BTU_TTYPE_BLE_INQUIRY                       99
#define BTU_TTYPE_BLE_GAP_LIM_DISC                  100
#define BTU_TTYPE_ATT_WAIT_FOR_RSP                  101
#define BTU_TTYPE_SMP_PAIRING_CMD                   102
#define BTU_TTYPE_BLE_RANDOM_ADDR                   103
#define BTU_TTYPE_ATT_WAIT_FOR_APP_RSP              104
#define BTU_TTYPE_ATT_WAIT_FOR_IND_ACK              105

#define BTU_TTYPE_BLE_GAP_FAST_ADV                  106
#define BTU_TTYPE_BLE_OBSERVE                       107

#define BTU_TTYPE_UCD_TO                            108
#define BTU_TTYPE_BLE_SCAN                          109

/* 用于QOS的BTU内部计时器*/
#define BTU_TTYPE_BTM_QOS                           110

/* BTU任务信号*/
typedef enum {
    SIG_BTU_START_UP = 0,
    SIG_BTU_HCI_MSG,
    SIG_BTU_BTA_MSG,
    SIG_BTU_BTA_ALARM,
    SIG_BTU_GENERAL_ALARM,
    SIG_BTU_ONESHOT_ALARM,
    SIG_BTU_L2CAP_ALARM,
    SIG_BTU_NUM,
} SIG_BTU_t;

/* 这是BTU持有的查询响应信息，可供应用程序使用。
*/
typedef struct {
    BD_ADDR     remote_bd_addr;
    UINT8       page_scan_rep_mode;
    UINT8       page_scan_per_mode;
    UINT8       page_scan_mode;
    DEV_CLASS   dev_class;
    UINT16      clock_offset;
} tBTU_INQ_INFO;



#define BTU_MAX_REG_TIMER     (2)   /* max#可以注册的计时器回调*/
#define BTU_MAX_REG_EVENT     (6)   /* max#可以注册的事件回调*/
#define BTU_DEFAULT_DATA_SIZE (0x2a0)

#if (BLE_INCLUDED == TRUE)
#define BTU_DEFAULT_BLE_DATA_SIZE   (27)
#endif

/* 保存已注册计时器的结构*/
typedef struct {
    TIMER_LIST_ENT          *p_tle;      /* 计时器条目*/
    tBTU_TIMER_CALLBACK     timer_cb;    /* 计时器过期时触发的回调*/
} tBTU_TIMER_REG;

/* 用于保存已注册事件回调的结构*/
typedef struct {
    UINT16                  event_range;  /* 事件范围开始*/
    tBTU_EVENT_CALLBACK     event_cb;     /* 事件在范围内时触发的回调*/
} tBTU_EVENT_REG;

#define NFC_MAX_LOCAL_CTRLS     0

/* BTU命令队列数组的索引*/
#define NFC_CONTROLLER_ID       (1)
#define BTU_MAX_LOCAL_CTRLS     (1 + NFC_MAX_LOCAL_CTRLS) /* 仅BR/EDR*/

/* 定义持有BTU变量的结构
*/
typedef struct {
    tBTU_TIMER_REG   timer_reg[BTU_MAX_REG_TIMER];
    tBTU_EVENT_REG   event_reg[BTU_MAX_REG_EVENT];

    BOOLEAN     reset_complete;             /* 收到设备的第一次确认后为TRUE*/
    UINT8       trace_level;                /* HCI层的跟踪级别*/
} tBTU_CB;

/*
#ifdef__cplusplusextern“C”｛#endif
*/
/* 全球BTU数据*/
#if BTU_DYNAMIC_MEMORY == FALSE
extern tBTU_CB  btu_cb;
#else
extern tBTU_CB *btu_cb_ptr;
#define btu_cb (*btu_cb_ptr)
#endif

extern const BD_ADDR        BT_BD_ANY;

/* btu_task.c提供的函数
************************************
*/
void btu_start_timer (TIMER_LIST_ENT *p_tle, UINT16 type, UINT32 timeout);
void btu_stop_timer (TIMER_LIST_ENT *p_tle);
void btu_free_timer (TIMER_LIST_ENT *p_tle);
void btu_start_timer_oneshot(TIMER_LIST_ENT *p_tle, UINT16 type, UINT32 timeout);
void btu_stop_timer_oneshot(TIMER_LIST_ENT *p_tle);

void btu_uipc_rx_cback(BT_HDR *p_msg);

/*
** 快速计时器
*/
#if defined(QUICK_TIMER_TICKS_PER_SEC) && (QUICK_TIMER_TICKS_PER_SEC > 0)
void btu_start_quick_timer (TIMER_LIST_ENT *p_tle, UINT16 type, UINT32 timeout);
void btu_stop_quick_timer (TIMER_LIST_ENT *p_tle);
void btu_free_quick_timer (TIMER_LIST_ENT *p_tle);
void btu_process_quick_timer_evt (void);
#endif

#if (defined(HCILP_INCLUDED) && HCILP_INCLUDED == TRUE)
void btu_check_bt_sleep (void);
#endif

/* btu_hcif.c提供的函数
************************************
*/
void  btu_hcif_process_event (UINT8 controller_id, BT_HDR *p_buf);
void  btu_hcif_send_cmd (UINT8 controller_id, BT_HDR *p_msg);
#if (BLE_50_FEATURE_SUPPORT == TRUE)
UINT8  btu_hcif_send_cmd_sync (UINT8 controller_id, BT_HDR *p_buf);
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）
void  btu_hcif_send_host_rdy_for_data(void);
void  btu_hcif_cmd_timeout (UINT8 controller_id);

/* btu_core.c提供的函数
************************************
*/
void  btu_init_core(void);
void  btu_free_core(void);

void BTU_StartUp(void);
void BTU_ShutDown(void);

void btu_task_start_up(void *param);
void btu_task_shut_down(void);

UINT16 BTU_BleAclPktSize(void);

bool btu_task_post(uint32_t sig, void *param, uint32_t timeout);

int get_btu_work_queue_size(void);

/*
#ifdef__cplusplus｝#endif
*/

#endif

