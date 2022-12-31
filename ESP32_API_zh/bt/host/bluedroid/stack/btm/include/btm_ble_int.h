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
 * 该文件包含主要蓝牙管理器（BTM）内部定义。
 *
 ******************************************************************************/

#ifndef BTM_BLE_INT_H
#define BTM_BLE_INT_H

#include "common/bt_target.h"
#include "osi/fixed_queue.h"
#include "stack/hcidefs.h"
#include "stack/btm_ble_api.h"
#include "btm_int.h"

#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
#include "stack/smp_api.h"
#endif


/* 扫描启用状态*/
#define BTM_BLE_SCAN_ENABLE      0x01
#define BTM_BLE_SCAN_DISABLE     0x00

/* 广告启用状态*/
#define BTM_BLE_ADV_ENABLE     0x01
#define BTM_BLE_ADV_DISABLE    0x00

/* 使用查询模式未使用的高4位*/
#define BTM_BLE_SELECT_SCAN     0x20
#define BTM_BLE_NAME_REQUEST    0x40
#define BTM_BLE_OBSERVE         0x80

#define BTM_BLE_MAX_WL_ENTRY        1
#define BTM_BLE_AD_DATA_LEN         31

#define BTM_BLE_ENC_MASK    0x03

#define BTM_BLE_DUPLICATE_DISABLE       0
#define BTM_BLE_DUPLICATE_ENABLE        1
#define BTM_BLE_DUPLICATE_MAX           BTM_BLE_DUPLICATE_ENABLE

#define BTM_BLE_GAP_DISC_SCAN_INT      18         /* 间隔（scan_int）=11.25毫秒=0x0010*0.625毫秒*/
#define BTM_BLE_GAP_DISC_SCAN_WIN      18         /* 扫描窗口=11.25毫秒=0x0010*0.625毫秒*/
#define BTM_BLE_GAP_ADV_INT            512        /* Tgap（gen_disc）=1.28 s=512*0.625 ms*/
#define BTM_BLE_GAP_LIM_TOUT           180        /* Tgap（lim_timeout）=最大180s*/
#define BTM_BLE_LOW_LATENCY_SCAN_INT   8000       /* 间隔（scan_int）=5s=8000*0.625 ms*/
#define BTM_BLE_LOW_LATENCY_SCAN_WIN   8000       /* 扫描窗口=5s=8000*0.625毫秒*/


#define BTM_BLE_GAP_ADV_FAST_INT_1         48         /* TGAP（adv_fast_interval1）=30（已使用）~60毫秒=48*0.625*/
#define BTM_BLE_GAP_ADV_FAST_INT_2         160         /* TGAP（adv_fast_interval2）=100（已使用）~ 150 ms=160*0.625 ms*/
#define BTM_BLE_GAP_ADV_SLOW_INT           2048         /* Tgap（adv_slow_interval）=1.28 s=512*0.625 ms*/
#define BTM_BLE_GAP_ADV_DIR_MAX_INT        800         /* Tgap（dir_conn_adv_int_max）=500毫秒=800*0.625毫秒*/
#define BTM_BLE_GAP_ADV_DIR_MIN_INT        400         /* Tgap（dir_conn_adv_int_min）=250 ms=400*0.625 ms*/

#define BTM_BLE_GAP_FAST_ADV_TOUT          30

#define BTM_BLE_SEC_REQ_ACT_NONE           0
#define BTM_BLE_SEC_REQ_ACT_ENCRYPT        1 /* 使用当前密钥或密钥刷新加密链接*/
#define BTM_BLE_SEC_REQ_ACT_PAIR           2
#define BTM_BLE_SEC_REQ_ACT_DISCARD        3 /* 在加密开始但未完成时放弃sec请求*/
typedef UINT8   tBTM_BLE_SEC_REQ_ACT;

#define BLE_STATIC_PRIVATE_MSB_MASK          0x3f
#define BLE_RESOLVE_ADDR_MSB                 0x40   /*  最高有效位，位7，位6为01，可随机解析*/
#define BLE_RESOLVE_ADDR_MASK                0xc0   /* 位6和位7*/
#define BTM_BLE_IS_RESOLVE_BDA(x)           ((x[0] & BLE_RESOLVE_ADDR_MASK) == BLE_RESOLVE_ADDR_MSB)

/* LE扫描活动位掩码，继续LE查询位*/
#define BTM_LE_SELECT_CONN_ACTIVE      0x0040     /* 选择连接正在进行*/
#define BTM_LE_OBSERVE_ACTIVE          0x0080     /* 观察正在进行中*/
#define BTM_LE_DISCOVER_ACTIVE         0x0100     /* 扫描正在进行*/

/* BLE扫描活动掩码检查*/
#define BTM_BLE_IS_SCAN_ACTIVE(x)   ((x) & BTM_BLE_SCAN_ACTIVE_MASK)
#define BTM_BLE_IS_INQ_ACTIVE(x)   ((x) & BTM_BLE_INQUIRY_MASK)
#define BTM_BLE_IS_OBS_ACTIVE(x)   ((x) & BTM_LE_OBSERVE_ACTIVE)
#define BTM_BLE_IS_DISCO_ACTIVE(x)   ((x) & BTM_LE_DISCOVER_ACTIVE)
#define BTM_BLE_IS_SEL_CONN_ACTIVE(x)   ((x) & BTM_LE_SELECT_CONN_ACTIVE)

/* BLE ADDR类型ID位*/
#define BLE_ADDR_TYPE_ID_BIT 0x02

#define BTM_VSC_CHIP_CAPABILITY_L_VERSION 55
#define BTM_VSC_CHIP_CAPABILITY_M_VERSION 95

typedef enum {
    BTM_BLE_IDLE,
    BTM_BLE_SCANNING,
    BTM_BLE_SCAN_PENDING,
    BTM_BLE_STOP_SCAN,
    BTM_BLE_ADVERTISING,
    BTM_BLE_ADV_PENDING,
    BTM_BLE_STOP_ADV,
}tBTM_BLE_GAP_STATE;

typedef struct {
    UINT16              data_mask;
    UINT8               *p_flags;
    UINT8               ad_data[BTM_BLE_AD_DATA_LEN];
    UINT8               *p_pad;
} tBTM_BLE_LOCAL_ADV_DATA;

typedef struct {
    UINT32          inq_count;          /* 用于确定响应是否已*/
    /* 为当前查询操作接收。（我们没有*/
    /* 想让呼叫者收到来自*/
    /* 同一设备。*/
    BOOLEAN         scan_rsp;
    tBLE_BD_ADDR    le_bda;
} tINQ_LE_BDADDR;

#define BTM_BLE_ADV_DATA_LEN_MAX        31
#define BTM_BLE_CACHE_ADV_DATA_MAX      62
#if (BLE_50_FEATURE_SUPPORT == TRUE)
#define BTM_BLE_EXT_ADV_DATA_LEN_MAX    251
#define BTM_BLE_PERIODIC_ADV_DATA_LEN_MAX 252

#define BTM_BLE_ADV_DATA_OP_INTERMEDIATE_FRAG    0
#define BTM_BLE_ADV_DATA_OP_FIRST_FRAG           1
#define BTM_BLE_ADV_DATA_OP_LAST_FRAG            2
#define BTM_BLE_ADV_DATA_OP_COMPLETE             3
#define BTM_BLE_ADV_DATA_OP_UNCHANGED_DATA       4
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）

#define BTM_BLE_ISVALID_PARAM(x, min, max)  (((x) >= (min) && (x) <= (max)) || ((x) == BTM_BLE_CONN_PARAM_UNDEF))

#define BTM_BLE_PRIVATE_ADDR_INT    900  /* 随机地址刷新至少15分钟*/

typedef struct {
    UINT16 discoverable_mode;
    UINT16 connectable_mode;
    BOOLEAN scan_params_set;
    UINT32 scan_window;
    UINT32 scan_interval;
    UINT8 scan_type; /* 电流扫描类型：主动或被动*/
    UINT8 scan_duplicate_filter; /* 已为扫描启用重复筛选器*/
    UINT16 adv_interval_min;
    UINT16 adv_interval_max;
    tBTM_BLE_AFP afp; /* 广告筛选策略*/
    tBTM_BLE_SFP sfp; /* 扫描筛选器策略*/
    tBTM_START_ADV_CMPL_CBACK *p_adv_cb;
    tBTM_START_STOP_ADV_CMPL_CBACK *p_stop_adv_cb;
    tBLE_ADDR_TYPE adv_addr_type;
    UINT8 evt_type;
    UINT8 adv_mode;
    tBLE_BD_ADDR direct_bda;
    tBTM_BLE_EVT directed_conn;
    BOOLEAN fast_adv_on;
    TIMER_LIST_ENT fast_adv_timer;

    UINT8 adv_len;
    UINT8 adv_data_cache[BTM_BLE_CACHE_ADV_DATA_MAX];
    BD_ADDR adv_addr;
    /* 查询BD地址数据库*/
    UINT8 num_bd_entries;
    UINT8 max_bd_entries;
    tBTM_BLE_LOCAL_ADV_DATA adv_data;
    tBTM_BLE_ADV_CHNL_MAP adv_chnl_map;

    TIMER_LIST_ENT inq_timer_ent;
    BOOLEAN scan_rsp;
    tBTM_BLE_GAP_STATE state; /* 查询过程所处的当前状态*/
    INT8 tx_power;
} tBTM_BLE_INQ_CB;


/* 随机地址解析完成回调*/
typedef void (tBTM_BLE_RESOLVE_CBACK) (void *match_rec, void *p);

typedef void (tBTM_BLE_ADDR_CBACK) (BD_ADDR_PTR static_random, void *p);

#define BTM_BLE_GAP_ADDR_BIT_RANDOM      (1<<0)
#define BTM_BLE_GAP_ADDR_BIT_RESOLVABLE  (1<<1)

/* 随机地址管理控制块*/
typedef struct {
    tBLE_ADDR_TYPE              own_addr_type;         /* 本地设备LE地址类型*/
    UINT8                       exist_addr_bit;
    BD_ADDR                     static_rand_addr;
    BD_ADDR                     resolvale_addr;
    BD_ADDR                     private_addr;
    BD_ADDR                     random_bda;
    BOOLEAN                     busy;
    tBTM_SEC_DEV_REC            *p_dev_rec;
    tBTM_BLE_RESOLVE_CBACK      *p_resolve_cback;
    tBTM_BLE_ADDR_CBACK         *p_generate_cback;
    void                        *p;
    TIMER_LIST_ENT              raddr_timer_ent;
    tBTM_SET_LOCAL_PRIVACY_CBACK *set_local_privacy_cback;
} tBTM_LE_RANDOM_CB;

#define BTM_BLE_MAX_BG_CONN_DEV_NUM    10

typedef struct {
    UINT16              min_conn_int;
    UINT16              max_conn_int;
    UINT16              slave_latency;
    UINT16              supervision_tout;

} tBTM_LE_CONN_PRAMS;


typedef struct {
    BD_ADDR     bd_addr;
    UINT8       attr;
    BOOLEAN     is_connected;
    BOOLEAN     in_use;
} tBTM_LE_BG_CONN_DEV;

/* 使用状态作为位掩码的白名单*/
#define BTM_BLE_WL_IDLE         0
#define BTM_BLE_WL_INIT         1
#define BTM_BLE_WL_SCAN         2
#define BTM_BLE_WL_ADV          4
typedef UINT8 tBTM_BLE_WL_STATE;

/* 使用状态作为位掩码解析列表*/
#define BTM_BLE_RL_IDLE         0
#define BTM_BLE_RL_INIT         1
#define BTM_BLE_RL_SCAN         2
#define BTM_BLE_RL_ADV          4
typedef UINT8 tBTM_BLE_RL_STATE;

/* BLE连接状态*/
#define BLE_CONN_IDLE    0
#define BLE_DIR_CONN     1
#define BLE_BG_CONN      2
#define BLE_CONN_CANCEL  3
typedef UINT8 tBTM_BLE_CONN_ST;

typedef struct {
    void    *p_param;
} tBTM_BLE_CONN_REQ;

/* LE状态请求*/
#define BTM_BLE_STATE_INVALID               0
#define BTM_BLE_STATE_CONN_ADV              1
#define BTM_BLE_STATE_INIT                  2
#define BTM_BLE_STATE_MASTER                3
#define BTM_BLE_STATE_SLAVE                 4
#define BTM_BLE_STATE_LO_DUTY_DIR_ADV       5
#define BTM_BLE_STATE_HI_DUTY_DIR_ADV       6
#define BTM_BLE_STATE_NON_CONN_ADV          7
#define BTM_BLE_STATE_PASSIVE_SCAN          8
#define BTM_BLE_STATE_ACTIVE_SCAN           9
#define BTM_BLE_STATE_SCAN_ADV              10
#define BTM_BLE_STATE_MAX                   11
typedef UINT8 tBTM_BLE_STATE;

#define BTM_BLE_STATE_CONN_ADV_BIT          0x0001
#define BTM_BLE_STATE_INIT_BIT              0x0002
#define BTM_BLE_STATE_MASTER_BIT            0x0004
#define BTM_BLE_STATE_SLAVE_BIT             0x0008
#define BTM_BLE_STATE_LO_DUTY_DIR_ADV_BIT   0x0010
#define BTM_BLE_STATE_HI_DUTY_DIR_ADV_BIT   0x0020
#define BTM_BLE_STATE_NON_CONN_ADV_BIT      0x0040
#define BTM_BLE_STATE_PASSIVE_SCAN_BIT      0x0080
#define BTM_BLE_STATE_ACTIVE_SCAN_BIT       0x0100
#define BTM_BLE_STATE_SCAN_ADV_BIT          0x0200
typedef UINT16 tBTM_BLE_STATE_MASK;

#define BTM_BLE_STATE_ALL_MASK              0x03ff
#define BTM_BLE_STATE_ALL_ADV_MASK          (BTM_BLE_STATE_CONN_ADV_BIT|BTM_BLE_STATE_LO_DUTY_DIR_ADV_BIT|BTM_BLE_STATE_HI_DUTY_DIR_ADV_BIT|BTM_BLE_STATE_SCAN_ADV_BIT)
#define BTM_BLE_STATE_ALL_SCAN_MASK         (BTM_BLE_STATE_PASSIVE_SCAN_BIT|BTM_BLE_STATE_ACTIVE_SCAN_BIT)
#define BTM_BLE_STATE_ALL_CONN_MASK         (BTM_BLE_STATE_MASTER_BIT|BTM_BLE_STATE_SLAVE_BIT)

#ifndef BTM_LE_RESOLVING_LIST_MAX
#define BTM_LE_RESOLVING_LIST_MAX     0x20
#endif

#define BTM_DUPLICATE_SCAN_EXCEPTIONAL_INFO_ADV_ADDR             0
#define BTM_DUPLICATE_SCAN_EXCEPTIONAL_INFO_MESH_LINK_ID         1
#define BTM_DUPLICATE_SCAN_EXCEPTIONAL_INFO_MESH_BEACON_TYPE     2
#define BTM_DUPLICATE_SCAN_EXCEPTIONAL_INFO_MESH_PROV_SRV_ADV    3
#define BTM_DUPLICATE_SCAN_EXCEPTIONAL_INFO_MESH_PROXY_SRV_ADV   4

typedef struct {
    BD_ADDR         *resolve_q_random_pseudo;
    UINT8           *resolve_q_action;
    UINT8           q_next;
    UINT8           q_pending;
} tBTM_BLE_RESOLVE_Q;

typedef struct {
    BOOLEAN     in_use;
    BOOLEAN     to_add;
    BD_ADDR     bd_addr;
    tBLE_ADDR_TYPE addr_type;
    UINT8       attr;
} tBTM_BLE_WL_OP;

/* BLE隐私模式*/
#define BTM_PRIVACY_NONE    0              /* BLE无隐私*/
#define BTM_PRIVACY_1_1     1              /* BLE隐私1.1，不支持隐私1.0*/
#define BTM_PRIVACY_1_2     2              /* BLE隐私1.2*/
#define BTM_PRIVACY_MIXED   3              /* BLE隐私混合模式，广播专有模式*/
typedef UINT8 tBTM_PRIVACY_MODE;

/* 数据长度更改事件回调*/
typedef void (tBTM_DATA_LENGTH_CHANGE_CBACK) (UINT16 max_tx_length, UINT16 max_rx_length);

/* 定义BLE设备管理控制结构
*/
typedef struct {
    UINT16 scan_activity;         /* LE扫描活动掩码*/

    /*****************************************************
    **      BLE查询
    *****************************************************/
    tBTM_BLE_INQ_CB inq_var;

    /* 观察者回调和计时器*/
    tBTM_INQ_RESULTS_CB *p_obs_results_cb;
    tBTM_CMPL_CB *p_obs_cmpl_cb;
    tBTM_INQ_DIS_CB *p_obs_discard_cb;
    TIMER_LIST_ENT obs_timer_ent;

    /* 扫描回调和计时器*/
    tBTM_INQ_RESULTS_CB *p_scan_results_cb;
    tBTM_CMPL_CB *p_scan_cmpl_cb;
    TIMER_LIST_ENT scan_timer_ent;

    /* 后台连接程序cb值*/
    tBTM_BLE_CONN_TYPE bg_conn_type;
    UINT32 scan_int;
    UINT32 scan_win;
    tBTM_BLE_SEL_CBACK *p_select_cback;
    /* 白名单信息*/
    UINT8 white_list_avail_size;
    tBTM_ADD_WHITELIST_CBACK *add_wl_cb;
    tBTM_BLE_WL_STATE wl_state;

    fixed_queue_t *conn_pending_q;
    tBTM_BLE_CONN_ST conn_state;

    /* 随机地址管理控制块*/
    tBTM_LE_RANDOM_CB addr_mgnt_cb;

    BOOLEAN enabled;

#if BLE_PRIVACY_SPT == TRUE
    BOOLEAN mixed_mode; /* 隐私1.2混合模式是否打开*/
    tBTM_PRIVACY_MODE privacy_mode; /* 隐私模式*/
    UINT8 resolving_list_avail_size; /* 解析列表可用大小*/
    tBTM_BLE_RESOLVE_Q resolving_list_pend_q; /* 正在解析列表队列*/
    tBTM_BLE_RL_STATE suspended_rl_state; /* 挂起的解析列表状态*/
    UINT8 *irk_list_mask; /* IRK列表可用性掩码，最多可包含条目位*/
    tBTM_BLE_RL_STATE rl_state; /* 正在解析列表状态*/
#endif

    tBTM_BLE_WL_OP wl_op_q[BTM_BLE_MAX_BG_CONN_DEV_NUM];

    /* 当前BLE链路状态*/
    tBTM_BLE_STATE_MASK cur_states; /* tBTM_BLE_STATE的位掩码*/
    UINT8 link_count[2]; /* 主和从链路总数*/
    tBTM_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_CMPL_CBACK *update_exceptional_list_cmp_cb;
} tBTM_BLE_CB;

#ifdef __cplusplus
extern "C" {
#endif

void btm_ble_timeout(TIMER_LIST_ENT *p_tle);
void btm_ble_process_adv_pkt (UINT8 *p);
void btm_ble_process_adv_discard_evt(UINT8 *p);
void btm_ble_proc_scan_rsp_rpt (UINT8 *p);
tBTM_STATUS btm_ble_read_remote_name(BD_ADDR remote_bda, tBTM_INQ_INFO *p_cur, tBTM_CMPL_CB *p_cb);
BOOLEAN btm_ble_cancel_remote_name(BD_ADDR remote_bda);

tBTM_STATUS btm_ble_set_discoverability(UINT16 combined_mode);
tBTM_STATUS btm_ble_set_connectability(UINT16 combined_mode);
tBTM_STATUS btm_ble_start_inquiry (UINT8 mode, UINT8   duration);
void btm_ble_stop_scan(void);
void btm_clear_all_pending_le_entry(void);

BOOLEAN btm_ble_send_extended_scan_params(UINT8 scan_type, UINT32 scan_int, UINT32 scan_win, UINT8 addr_type_own, UINT8 scan_filter_policy);
void btm_ble_stop_inquiry(void);
void btm_ble_init (void);
void btm_ble_free (void);
void btm_ble_connected (UINT8 *bda, UINT16 handle, UINT8 enc_mode, UINT8 role, tBLE_ADDR_TYPE addr_type, BOOLEAN addr_matched);
void btm_ble_read_remote_features_complete(UINT8 *p);
void btm_ble_write_adv_enable_complete(UINT8 *p);
void btm_ble_conn_complete(UINT8 *p, UINT16 evt_len, BOOLEAN enhanced);
void btm_read_ble_local_supported_states_complete(UINT8 *p, UINT16 evt_len);
tBTM_BLE_CONN_ST btm_ble_get_conn_st(void);
void btm_ble_set_conn_st(tBTM_BLE_CONN_ST new_st);
UINT8 *btm_ble_build_adv_data(tBTM_BLE_AD_MASK *p_data_mask, UINT8 **p_dst, tBTM_BLE_ADV_DATA *p_data);
tBTM_STATUS btm_ble_start_adv(void);
tBTM_STATUS btm_ble_stop_adv(void);
tBTM_STATUS btm_ble_start_scan(void);
void btm_ble_create_ll_conn_complete (UINT8 status);
void btm_ble_create_conn_cancel_complete (UINT8 *p);

/* 来自btm_sec的LE安全功能。c*/
#if SMP_INCLUDED == TRUE
void btm_ble_link_sec_check(BD_ADDR bd_addr, tBTM_LE_AUTH_REQ auth_req, tBTM_BLE_SEC_REQ_ACT *p_sec_req_act);
void btm_ble_ltk_request_reply(BD_ADDR bda,  BOOLEAN use_stk, BT_OCTET16 stk);
UINT8 btm_proc_smp_cback(tSMP_EVT event, BD_ADDR bd_addr, tSMP_EVT_DATA *p_data);
tBTM_STATUS btm_ble_set_encryption (BD_ADDR bd_addr, void *p_ref_data, UINT8 link_role);
void btm_ble_ltk_request(UINT16 handle, UINT8 rand[8], UINT16 ediv);
tBTM_STATUS btm_ble_start_encrypt(BD_ADDR bda, BOOLEAN use_stk, BT_OCTET16 stk);
void btm_ble_link_encrypted(BD_ADDR bd_addr, UINT8 encr_enable);
#endif

/* LE设备管理功能*/
void btm_ble_reset_id( void );

/* 安全相关功能*/
void btm_ble_increment_sign_ctr(BD_ADDR bd_addr, BOOLEAN is_local );
BOOLEAN btm_get_local_div (BD_ADDR bd_addr, UINT16 *p_div);
BOOLEAN btm_ble_get_enc_key_type(BD_ADDR bd_addr, UINT8 *p_key_types);

void btm_ble_test_command_complete(UINT8 *p);
void btm_ble_rand_enc_complete (UINT8 *p, UINT16 op_code, tBTM_RAND_ENC_CB *p_enc_cplt_cback);

void btm_sec_save_le_key(BD_ADDR bd_addr, tBTM_LE_KEY_TYPE key_type, tBTM_LE_KEY_VALUE *p_keys, BOOLEAN pass_to_application);
void btm_ble_update_sec_key_size(BD_ADDR bd_addr, UINT8 enc_key_size);
UINT8 btm_ble_read_sec_key_size(BD_ADDR bd_addr);

/* 白名单函数*/
BOOLEAN btm_update_dev_to_white_list(BOOLEAN to_add, BD_ADDR bd_addr, tBLE_ADDR_TYPE addr_type, tBTM_ADD_WHITELIST_CBACK *add_wl_cb);
void btm_update_scanner_filter_policy(tBTM_BLE_SFP scan_policy);
void btm_update_adv_filter_policy(tBTM_BLE_AFP adv_policy);
void btm_ble_clear_white_list (void);
void btm_read_white_list_size_complete(UINT8 *p, UINT16 evt_len);
void btm_ble_add_2_white_list_complete(UINT8 status);
void btm_ble_remove_from_white_list_complete(UINT8 *p, UINT16 evt_len);
void btm_ble_clear_white_list_complete(UINT8 *p, UINT16 evt_len);
void btm_ble_white_list_init(UINT8 white_list_size);

/* 后台连接功能*/
BOOLEAN btm_ble_suspend_bg_conn(void);
BOOLEAN btm_ble_resume_bg_conn(void);
void btm_ble_initiate_select_conn(BD_ADDR bda);
BOOLEAN btm_ble_start_auto_conn(BOOLEAN start);
BOOLEAN btm_ble_start_select_conn(BOOLEAN start, tBTM_BLE_SEL_CBACK   *p_select_cback);
BOOLEAN btm_ble_renew_bg_conn_params(BOOLEAN add, BD_ADDR bd_addr);
void btm_write_dir_conn_wl(BD_ADDR target_addr);
BOOLEAN btm_ble_update_mode_operation(UINT8 link_role, BD_ADDR bda, UINT8 status);
BOOLEAN btm_execute_wl_dev_operation(void);
void btm_ble_update_link_topology_mask(UINT8 role, BOOLEAN increase);

/* 直接连接公用设施*/
BOOLEAN btm_send_pending_direct_conn(void);
void btm_ble_enqueue_direct_conn_req(void *p_param);

/* BLE地址管理*/
void btm_gen_resolvable_private_addr (void *p_cmd_cplt_cback);
void btm_gen_non_resolvable_private_addr (tBTM_BLE_ADDR_CBACK *p_cback, void *p);
void btm_ble_resolve_random_addr(BD_ADDR random_bda, tBTM_BLE_RESOLVE_CBACK *p_cback, void *p);
void btm_gen_resolve_paddr_low(tBTM_RAND_ENC *p);

/*  隐私功能*/
#if (defined BLE_PRIVACY_SPT && BLE_PRIVACY_SPT == TRUE)
/* 具有CS功能的BLE地址映射*/
BOOLEAN btm_identity_addr_to_random_pseudo(BD_ADDR bd_addr, UINT8 *p_addr_type, BOOLEAN refresh);
BOOLEAN btm_random_pseudo_to_identity_addr(BD_ADDR random_pseudo, UINT8 *p_static_addr_type);
void btm_ble_refresh_peer_resolvable_private_addr(BD_ADDR pseudo_bda, BD_ADDR rra, UINT8 rra_type);
void btm_ble_refresh_local_resolvable_private_addr(BD_ADDR pseudo_addr, BD_ADDR local_rpa);
void btm_ble_read_resolving_list_entry_complete(UINT8 *p, UINT16 evt_len) ;
void btm_ble_remove_resolving_list_entry_complete(UINT8 *p, UINT16 evt_len);
void btm_ble_add_resolving_list_entry_complete(UINT8 *p, UINT16 evt_len);
void btm_ble_clear_resolving_list_complete(UINT8 *p, UINT16 evt_len);
void btm_read_ble_resolving_list_size_complete (UINT8 *p, UINT16 evt_len);
void btm_ble_enable_resolving_list(UINT8);
BOOLEAN btm_ble_disable_resolving_list(UINT8 rl_mask, BOOLEAN to_resume);
void btm_ble_enable_resolving_list_for_platform (UINT8 rl_mask);
void btm_ble_resolving_list_init(UINT8 max_irk_list_sz);
void btm_ble_resolving_list_cleanup(void);
#endif

void btm_ble_multi_adv_configure_rpa (tBTM_BLE_MULTI_ADV_INST *p_inst);
void btm_ble_multi_adv_init(void);
void *btm_ble_multi_adv_get_ref(UINT8 inst_id);
void btm_ble_multi_adv_cleanup(void);
void btm_ble_multi_adv_reenable(UINT8 inst_id);
void btm_ble_multi_adv_enb_privacy(BOOLEAN enable);
char btm_ble_map_adv_tx_power(int tx_power_index);
void btm_ble_batchscan_init(void);
void btm_ble_batchscan_cleanup(void);
void btm_ble_adv_filter_init(void);
void btm_ble_adv_filter_cleanup(void);
BOOLEAN btm_ble_topology_check(tBTM_BLE_STATE_MASK request);
BOOLEAN btm_ble_clear_topology_mask(tBTM_BLE_STATE_MASK request_state);
BOOLEAN btm_ble_set_topology_mask(tBTM_BLE_STATE_MASK request_state);
tBTM_BLE_STATE_MASK btm_ble_get_topology_mask(void);

#if BTM_BLE_CONFORMANCE_TESTING == TRUE
void btm_ble_set_no_disc_if_pair_fail (BOOLEAN disble_disc);
void btm_ble_set_test_mac_value (BOOLEAN enable, UINT8 *p_test_mac_val);
void btm_ble_set_test_local_sign_cntr_value(BOOLEAN enable, UINT32 test_local_sign_cntr);
void btm_set_random_address(BD_ADDR random_bda);
void btm_ble_set_keep_rfu_in_auth_req(BOOLEAN keep_rfu);
#endif

BOOLEAN btm_get_current_conn_params(BD_ADDR bda, UINT16 *interval, UINT16 *latency, UINT16 *timeout);

#if (BLE_50_FEATURE_SUPPORT == TRUE)
void btm_ble_update_phy_evt(tBTM_BLE_UPDATE_PHY *params);
void btm_ble_scan_timeout_evt(void);
void btm_ble_adv_set_terminated_evt(tBTM_BLE_ADV_TERMINAT *params);
void btm_ble_ext_adv_report_evt(tBTM_BLE_EXT_ADV_REPORT *params);
void btm_ble_scan_req_received_evt(tBTM_BLE_SCAN_REQ_RECEIVED *params);
void btm_ble_channel_select_algorithm_evt(tBTM_BLE_CHANNEL_SEL_ALG *params);
void btm_ble_periodic_adv_report_evt(tBTM_PERIOD_ADV_REPORT *params);
void btm_ble_periodic_adv_sync_lost_evt(tBTM_BLE_PERIOD_ADV_SYNC_LOST *params);
void btm_ble_periodic_adv_sync_establish_evt(tBTM_BLE_PERIOD_ADV_SYNC_ESTAB *params);
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）

/*
#ifdef__cplusplus｝#endif
*/
#endif

