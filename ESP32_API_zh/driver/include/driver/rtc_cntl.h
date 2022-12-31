/*
 * SPDX文件版权文本：2016-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "esp_err.h"
#include "esp_intr_alloc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 为特定RTC_CNTL中断注册处理程序
 *
 * 可以使用此函数注册多个处理程序。每当发生RTC中断时，将调用所有具有匹配RTC_intr_mask值的处理程序。
 *
 * @param handler  要调用的处理程序函数
 * @param handler_arg  要传递给处理程序的参数
 * @param rtc_intr_mask  RTC_CNTL_*_INT_ENA位的组合，指示要调用处理程序的源
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_NO_MEM内存不足，无法分配处理程序结构
 *      -esp_intr_alloc返回的其他错误
 */
esp_err_t rtc_isr_register(intr_handler_t handler, void* handler_arg,
                            uint32_t rtc_intr_mask);
/**
 * @brief 取消注册以前使用rtc_isr_register注册的处理程序
 * @param handler  要调用的处理程序函数（传递给rtc_isr_register）
 * @param handler_arg  处理程序的参数（传递给rtc_isr_register）
 * @return
 *      -成功时ESP_OK
 *      -如果未注册同时匹配handler和handler_arg的处理程序，则返回ESP_ERR_INVALID_STATE
 */
esp_err_t rtc_isr_deregister(intr_handler_t handler, void* handler_arg);

#ifdef __cplusplus
}
#endif

