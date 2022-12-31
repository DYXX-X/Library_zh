/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#include "soc/rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 此功能用于启用数字8米rtc时钟，以支持外围设备。
 *
 * @note 如果多次调用此函数，则需要同时调用`periph_rtc_dig_clk8m_disable`函数才能禁用。
 *
 * @return true：启用rtc 8M时钟成功，false：启用rtc8M时钟失败
 */
bool periph_rtc_dig_clk8m_enable(void);

/**
 * @brief 此函数用于禁用rtc数字时钟，该时钟应与“peripher_rc_dig_clk8m_enable”成对调用
 *
 * @note 如果多次调用此函数，则需要同时调用`periph_rtc_dig_clk8m_disable`函数才能禁用。
 */
void periph_rtc_dig_clk8m_disable(void);

/**
 * @brief 此函数用于获取rtc时钟的实际时钟频率值
 *
 * @return 实际时钟值
 */
uint32_t periph_rtc_dig_clk8m_get_freq(void);

#ifdef __cplusplus
}
#endif

