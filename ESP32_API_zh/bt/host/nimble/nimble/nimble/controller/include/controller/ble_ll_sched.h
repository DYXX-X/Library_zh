/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_SCHED_
#define H_BLE_LL_SCHED_

#ifdef __cplusplus
extern "C" {
#endif

/* 每个BLE调度程序插槽的时间*/
#define BLE_LL_SCHED_USECS_PER_SLOT         (1250)
#define BLE_LL_SCHED_32KHZ_TICKS_PER_SLOT   (41)    /* 1勾号=30.517 usecs*/

/*
 * 计划广告项目所需的最坏情况时间。这是接收扫描请求和发送扫描响应的最长时间（其间有适当的IFS时间）。此数字使用以下公式计算：IFS+SCAN_REQ+IFS+SAN_RSP=150+176+150+376。注意：tx-adv、rx-SCAN REQ和send-SCAN RSP的最坏情况时间为1228 usecs。这假定最大大小的广告PDU和扫描响应PDU。
 *
 * 对于可连接的广告事件，不允许扫描请求。在这种情况下，我们只需要接收一个连接请求PDU:IFS+connect_REQ=150+352。注意：最坏情况是376+150+352=878 usecs
 *
 * 注意：此处不包括广告PDU传输时间，因为我们知道需要多长时间（最坏情况是376次使用）。
 */
#define BLE_LL_SCHED_ADV_MAX_USECS          (852)
#define BLE_LL_SCHED_DIRECT_ADV_MAX_USECS   (502)
#define BLE_LL_SCHED_MAX_ADV_PDU_USECS      (376)

/*
 * 这是从计划项目开始到实际tx/rx发生的偏移量，单位为刻度。
 */
extern uint8_t g_ble_ll_sched_offset_ticks;

/*
 * 这是发送和接收最大大小PDU所需的时隙数，包括每个PDU之前的IFS时间。tx/rx的实际时间为2120 usecs，IFS=4540 usecs的实际时间是150 usecs。
 */
#define BLE_LL_SCHED_MAX_TXRX_SLOT  (4 * BLE_LL_SCHED_USECS_PER_SLOT)

/* BLE调度程序错误*/
#define BLE_LL_SCHED_ERR_OVERLAP    (1)

/* 调度程序事件的类型*/
#define BLE_LL_SCHED_TYPE_ADV       (1)
#define BLE_LL_SCHED_TYPE_SCAN      (2)
#define BLE_LL_SCHED_TYPE_CONN      (3)
#define BLE_LL_SCHED_TYPE_AUX_SCAN  (4)
#define BLE_LL_SCHED_TYPE_DTM       (5)
#define BLE_LL_SCHED_TYPE_PERIODIC  (6)
#define BLE_LL_SCHED_TYPE_SYNC      (7)

/* 返回计划回调的值。*/
#define BLE_LL_SCHED_STATE_RUNNING  (0)
#define BLE_LL_SCHED_STATE_DONE     (1)

/* 回调函数*/
struct ble_ll_sched_item;
typedef int (*sched_cb_func)(struct ble_ll_sched_item *sch);
typedef void (*sched_remove_cb_func)(struct ble_ll_sched_item *sch);
/*
 * 严格的连接调度（对于主机）与正常调度连接的方式不同。通过严格的连接调度，我们引入了“周期”的概念。周期是槽的集合。每个时隙的长度为1.25毫秒。一个周期中的插槽数由syscfg值BLE_LL_CONN_INIT_slots确定。周期的集合称为纪元。历元的长度由连接数（BLE_MAX_connections加上BLE_LL_ADD_STRICT_SCHED_PERIODS）确定。将在时段边界安排连接。如果可能，任何扫描/启动/广告将在未使用的时间段内完成。
 */
#if MYNEWT_VAL(BLE_LL_STRICT_CONN_SCHEDULING)
#define BLE_LL_SCHED_PERIODS    (MYNEWT_VAL(BLE_MAX_CONNECTIONS) + \
                                 MYNEWT_VAL(BLE_LL_ADD_STRICT_SCHED_PERIODS))

struct ble_ll_sched_obj
{
    uint8_t sch_num_occ_periods;
    uint32_t sch_occ_period_mask;
    uint32_t sch_ticks_per_period;
    uint32_t sch_ticks_per_epoch;
    uint32_t sch_epoch_start;
};

extern struct ble_ll_sched_obj g_ble_ll_sched_data;

/*
 * XXX: TODO:
 * ->我们如何知道大纪元的开始是最新的？没有包裹？
 * ->目前，仅在不超过32个连接的情况下执行此操作。
 * ->如果没有空的计划插槽，则不允许启动
 */
#endif

/*
 * 计划项目sched_type：这是计划项目的类型。enqueued：表示项目是否在调度程序列表中的标志。0：否，1：是余数：从偏移到tx/rx应发生的使用次数txrx_offset：从开始时间到tx/rx应发生为止的滴答数。
 *
 */
struct ble_ll_sched_item
{
    uint8_t         sched_type;
    uint8_t         enqueued;
    uint8_t         remainder;
    uint32_t        start_time;
    uint32_t        end_time;
    void            *cb_arg;
    sched_cb_func   sched_cb;
    TAILQ_ENTRY(ble_ll_sched_item) link;
};

/* 初始化调度程序*/
int ble_ll_sched_init(void);

/* 从计划中删除项目*/
int ble_ll_sched_rmv_elem(struct ble_ll_sched_item *sch);

void ble_ll_sched_rmv_elem_type(uint8_t type, sched_remove_cb_func remove_cb);

/* 计划新的主连接*/
struct ble_ll_conn_sm;
int ble_ll_sched_master_new(struct ble_ll_conn_sm *connsm,
                            struct ble_mbuf_hdr *ble_hdr, uint8_t pyld_len);

/* 计划新的从属连接*/
int ble_ll_sched_slave_new(struct ble_ll_conn_sm *connsm);

struct ble_ll_adv_sm;
typedef void ble_ll_sched_adv_new_cb(struct ble_ll_adv_sm *advsm,
                                     uint32_t sch_start, void *arg);

/* 安排新的广告活动*/
int ble_ll_sched_adv_new(struct ble_ll_sched_item *sch,
                         ble_ll_sched_adv_new_cb cb, void *arg);

/* 安排定期广告活动*/
int ble_ll_sched_periodic_adv(struct ble_ll_sched_item *sch, uint32_t *start,
                              bool after_overlap);

int ble_ll_sched_sync_reschedule(struct ble_ll_sched_item *sch,
                                 uint32_t anchor_point,
                                 uint8_t anchor_point_usecs,
                                 uint32_t window_widening, int8_t phy_mode);
int ble_ll_sched_sync(struct ble_ll_sched_item *sch,
                      uint32_t beg_cputime, uint32_t rem_usecs, uint32_t offset,
                      int8_t phy_mode);

/* 重新安排广告活动*/
int ble_ll_sched_adv_reschedule(struct ble_ll_sched_item *sch, uint32_t *start,
                                uint32_t max_delay_ticks);

/* 重新计划和广告pdu*/
int ble_ll_sched_adv_resched_pdu(struct ble_ll_sched_item *sch);

/* 重新计划以前已计划或已结束的连接*/
int ble_ll_sched_conn_reschedule(struct ble_ll_conn_sm * connsm);

/**
 * 调用以确定下一个计划事件的发生时间。
 *
 * 如果没有计划的事件，则此函数返回0；否则返回1，next_event_time设置为下一个事件的开始时间。
 *
 * @param next_event_time 下一个计划事件发生的cputime
 *
 * @return int 0:未安排任何事件1:有即将发生的事件
 */
int ble_ll_sched_next_time(uint32_t *next_event_time);

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_EXT_ADV)
struct ble_ll_scan_sm;
struct ble_ll_aux_data;
int ble_ll_sched_aux_scan(struct ble_mbuf_hdr *ble_hdr,
                          struct ble_ll_scan_sm *scansm,
                          struct ble_ll_aux_data *aux_scan);

int ble_ll_sched_scan_req_over_aux_ptr(uint32_t chan, uint8_t phy_mode);
#endif

/* 停止计划程序*/
void ble_ll_sched_stop(void);

#if MYNEWT_VAL(BLE_LL_DTM)
int ble_ll_sched_dtm(struct ble_ll_sched_item *sch);
#endif

#ifdef __cplusplus
}
#endif

#endif /* H_LL_SCHED_ */

