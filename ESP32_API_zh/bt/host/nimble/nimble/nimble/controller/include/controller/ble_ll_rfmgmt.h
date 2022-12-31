/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_RFMGMT_
#define H_BLE_LL_RFMGMT_

#ifdef __cplusplus
extern "C" {
#endif

void ble_ll_rfmgmt_init(void);

#if MYNEWT_VAL(BLE_LL_RFMGMT_ENABLE_TIME) > 0

void ble_ll_rfmgmt_reset(void);

/* 通知rfmgmt扫描窗口已更改（仅从ble_ll_scan调用）*/
void ble_ll_rfmgmt_scan_changed(bool enabled, uint32_t next_window);

/* 通知rfmgmt第一个计划项目已更改（仅从ble_ll_sched调用）*/
void ble_ll_rfmgmt_sched_changed(struct ble_ll_sched_item *first);

/* 通知rfmgmt当前事件不再需要RF*/
void ble_ll_rfmgmt_release(void);

/* 立即启用RF并返回将完全启用RF的刻度*/
uint32_t ble_ll_rfmgmt_enable_now(void);

/* 仅当RF当前已完全启用（即未关闭或启用）时返回真*/
bool ble_ll_rfmgmt_is_enabled(void);

#else

static inline void ble_ll_rfmgmt_reset(void) { }
static inline void ble_ll_rfmgmt_scan_changed(bool e, uint32_t n) { }
static inline void ble_ll_rfmgmt_sched_changed(struct ble_ll_sched_item *f) { }
static inline void ble_ll_rfmgmt_release(void) { }
static inline uint32_t ble_ll_rfmgmt_enable_now(void) { return 0; }
static inline bool ble_ll_rfmgmt_is_enabled(void) { return true; }

#endif

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_LL_RFMGMT_ */

