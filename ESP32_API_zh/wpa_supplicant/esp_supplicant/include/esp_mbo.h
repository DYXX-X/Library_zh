/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_MBO_H
#define _ESP_MBO_H

#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
  * enum non_pref_chan_reason：通道不首选的原因
  */
enum non_pref_chan_reason {
	NON_PREF_CHAN_REASON_UNSPECIFIED = 0,
	NON_PREF_CHAN_REASON_RSSI = 1,
	NON_PREF_CHAN_REASON_EXT_INTERFERENCE = 2,
	NON_PREF_CHAN_REASON_INT_INTERFERENCE = 3,
};

/**
  * @brief  非首选通道的通道结构
  *
  * @param  reason: 枚举non_pref_chan_reason
  * @param  oper_class: 通道的操作等级
  * @param  chan: 通道编号
  * @param  preference: 频道偏好
  */
struct non_pref_chan {
	enum non_pref_chan_reason reason;
	uint8_t oper_class;
	uint8_t chan;
	uint8_t preference;
};

/**
  * @brief  非首选通道结构的数组结构
  *
  * @param  non_pref_chan_num: 信道计数
  * @param  chan: non_pref_chan类型的数组
  */
struct non_pref_chan_s {
	size_t non_pref_chan_num;
	struct non_pref_chan chan[];
};

/**
  * @brief  更新MBO IE的频道首选项
  *
  * @param  non_pref_chan: 非首选频道列表
  *
  * @return
  *    -0:成功，否则失败
  */
int esp_mbo_update_non_pref_chan(struct non_pref_chan_s *non_pref_chan);

#ifdef __cplusplus
}
#endif
#endif

