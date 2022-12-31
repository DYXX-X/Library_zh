/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_WNM_H
#define _ESP_WNM_H

#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
  * enum-btm_query_reason：发送btm查询的原因代码
  */
enum btm_query_reason {
	REASON_UNSPECIFIED = 0,
	REASON_FRAME_LOSS = 1,
	REASON_DELAY = 2,
	REASON_BANDWIDTH = 3,
	REASON_LOAD_BALANCE = 4,
	REASON_RSSI = 5,
	REASON_RETRANSMISSIONS = 6,
	REASON_INTERFERENCE = 7,
	REASON_GRAY_ZONE = 8,
	REASON_PREMIUM_AP = 9,
};

/**
  * @brief  向连接的AP发送bss转换查询
  *
  * @param  query_reason: 发送查询的原因
  * @param  btm_candidates: btm候选人列表（如果可用）
  * @param  cand_list: 是否从请求方缓存中可用的扫描结果中包括候选列表。
  *
  * @return
  *    -0:成功，否则失败
  */
int esp_wnm_send_bss_transition_mgmt_query(enum btm_query_reason query_reason,
					   const char *btm_candidates,
					   int cand_list);

#ifdef __cplusplus
}
#endif
#endif

