/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __ESP_COEXIST_INTERNAL_H__
#define __ESP_COEXIST_INTERNAL_H__

#include <stdbool.h>
#include "esp_coexist.h"
#include "esp_coexist_adapter.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    COEX_PREFER_WIFI = 0,
    COEX_PREFER_BT,
    COEX_PREFER_BALANCE,
    COEX_PREFER_NUM,
} coex_prefer_t;

typedef void (* coex_func_cb_t)(uint32_t event, int sched_cnt);

/**
 * @brief Pre-Init软件共存外部功能供内部使用。
 *
 * @return 初始化正常或失败。
 */
esp_err_t coex_pre_init(void);

/**
 * @brief 初始化软件共存外部函数供内部使用。
 *
 * @return 初始化正常或失败。
 */
esp_err_t coex_init(void);

/**
 * @brief De-init软件共存外部函数供内部使用。
 */
void coex_deinit(void);

/**
 * @brief 启用内部使用的软件共存外部功能。
 *
 * @return 启用正常或失败。
 */
esp_err_t coex_enable(void);

/**
 * @brief 禁用内部使用的软件共存外部功能。
 */
void coex_disable(void);

/**
 * @brief 获取供内部使用的软件共存版本字符串外部函数。
 * @return ：版本字符串
 */
const char *coex_version_get(void);

/**
 * @brief 共存libbt中的性能首选项集。内部使用的外部函数。
 *
 *  @param prefer ：首选枚举值
 *  @return ：ESP_OK-成功，其他-失败
 */
esp_err_t coex_preference_set(coex_prefer_t prefer);

/**
 * @brief 获取软件共存状态。
 * @return ：软件共存状态
 */
uint32_t coex_status_get(void);

/**
 * @brief 设置软件共存条件。
 * @return ：软件共存条件
 */
void coex_condition_set(uint32_t type, bool dissatisfy);

/**
 * @brief WiFi请求共存。
 *
 *  @param event ：WiFi事件
 *  @param latency ：WiFi将在延迟后请求共存
 *  @param duration ：WiFi请求共存的持续时间
 *  @return ：0-成功，其他-失败
 */
int coex_wifi_request(uint32_t event, uint32_t latency, uint32_t duration);

/**
 * @brief WiFi释放共存。
 *
 *  @param event ：WiFi事件
 *  @return ：0-成功，其他-失败
 */
int coex_wifi_release(uint32_t event);

/**
 * @brief 将WiFi信道设置为共存模块。
 *
 *  @param primary ：WiFi主频道
 *  @param secondary ：WiFi次要频道
 *  @return ：0-成功，其他-失败
 */
int coex_wifi_channel_set(uint8_t primary, uint8_t secondary);

/**
 * @brief 获取共存事件持续时间。
 *
 *  @param event ：共存事件
 *  @param duration: 共存事件持续时间
 *  @return ：0-成功，其他-失败
 */
int coex_event_duration_get(uint32_t event, uint32_t *duration);

#if SOC_COEX_HW_PTI
/**
 * @brief 获取共存事件优先级。
 *
 *  @param event ：共存事件
 *  @param pti: 共存事件优先级
 *  @return ：0-成功，其他-失败
 */
int coex_pti_get(uint32_t event, uint8_t *pti);
#endif

/**
 * @brief 清除共存状态。
 *
 *  @param type ：共存状态类型
 *  @param status: 共存状态
 */
void coex_schm_status_bit_clear(uint32_t type, uint32_t status);

/**
 * @brief 设置共存状态。
 *
 *  @param type ：共存状态类型
 *  @param status: 共存状态
 */
void coex_schm_status_bit_set(uint32_t type, uint32_t status);

/**
 * @brief 设置共存方案间隔。
 *
 *  @param interval ：共存方案间隔
 *  @return ：0-成功，其他-失败
 */
int coex_schm_interval_set(uint32_t interval);

/**
 * @brief 获取共存方案间隔。
 *
 *  @return ：共存方案间隔
 */
uint32_t coex_schm_interval_get(void);

/**
 * @brief 获取当前共存方案周期。
 *
 *  @return ：共存方案周期
 */
uint8_t coex_schm_curr_period_get(void);

/**
 * @brief 获取当前共存方案阶段。
 *
 *  @return ：共存方案阶段
 */
void * coex_schm_curr_phase_get(void);

/**
 * @brief 设置当前共存方案相位索引。
 *
 *  @param interval ：共存方案相位指数
 *  @return ：0-成功，其他-失败
 */
int coex_schm_curr_phase_idx_set(int idx);

/**
 * @brief 获取当前共存方案相位索引。
 *
 *  @return ：共存方案相位指数
 */
int coex_schm_curr_phase_idx_get(void);

/**
 * @brief 注册共存适配器函数。
 *
 *  @param funcs ：共存适配器函数
 *  @return ：ESP_OK-成功，其他-失败
 */
esp_err_t esp_coex_adapter_register(coex_adapter_funcs_t *funcs);

#if CONFIG_EXTERNAL_COEX_ENABLE
/**
  * @brief     设置外部共存pti级别并启用它。
  *
  * @param     level1    外腔低pti
  * @param     level2    外腔中部pti
  * @param     level3    外腔高pti
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_coex_external_set(esp_coex_pti_level_t level1,
         esp_coex_pti_level_t level2, esp_coex_pti_level_t level3);

/**
  * @brief     禁用外部共存
  *
  * @return
  *    -ESP_OK：成功
  */
void esp_coex_external_stop(void);
#endif    /*外部系数*/

/**
  * @brief     检查IDF和WiFi库中共存适配器头文件的MD5值
  *
  * @attention 1.用于内部CI版本检查
  *
  * @return
  *     -ESP_OK：成功
  *     -ESP_WIFI_INVALID_ARG:MD5检查失败
  */
esp_err_t esp_coex_adapter_funcs_md5_check(const char *md5);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_COEXIST_INTERNAL_H__ */

