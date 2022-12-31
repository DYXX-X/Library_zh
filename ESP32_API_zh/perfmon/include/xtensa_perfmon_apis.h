// 版权所有2018-2019 Espressif Systems（Shanghai）PTE LTD
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _xtensa_perfmon_apis_H_
#define _xtensa_perfmon_apis_H_
#include "xtensa_perfmon_access.h"
#include "xtensa_perfmon_masks.h"

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @brief 性能监视器配置结构
 *
 * 配置性能计数器以测量专用功能的结构
 */
typedef struct xtensa_perfmon_config {
    int repeat_count;       /*!< 在回调被重复之前，函数将被调用多少次*/
    float max_deviation;    /*!<  最小和最大计数器编号0..1之间的差异，0-无差异，1-未使用*/
    void *call_params;      /*!<  此指针将作为参数传递给call_function*/
    void (*call_function)(void *params); /*!< 指向必须调用的函数的指针*/
    void (*callback)(void *params, uint32_t select, uint32_t mask, uint32_t value); /*!< 指向将使用结果参数调用的函数的指针*/
    void *callback_params;  /*!<  将传递给回调的参数*/
    int tracelevel;         /*!<  所有计数器的跟踪级别。如果为负值，将忽略过滤器。如果它>=0，那么只有当中断级别>跟踪级别时，perfmon才会计数。监视中断很有用。*/
    uint32_t  counters_size;/*!<  列表中计数器的数量*/
    const uint32_t *select_mask;  /*!<  选择/掩码参数列表*/
} xtensa_perfmon_config_t;


/**
 * @brief      执行PM
 *
 * 使用定义的参数执行专用功能的性能计数器
 *
 * @param[in] config: 指向配置结构的指针
 *
 * @return
 *      -ESP_OK（如果没有错误）
 *      -ESP_ERR_INVALID_ARG（如果未定义所需参数之一）
 *      -ESP_FAIL-计数器溢出
 */
esp_err_t xtensa_perfmon_exec(const xtensa_perfmon_config_t *config);

/**
 * @brief      转储PM结果
 *
 * 回调以将perfmon结果转储到perfmon_config_t:：Callback_params中指定的FILE*流。如果callback_params设置为NULL，将打印到标准输出
 *
 * @param[in] params:   使用了从配置传递的参数（callback_params）。此参数应为FILE hanle，数据将存储在其中。如果此参数为NULL，则数据将存储到标准输出。
 * @param[in] select:   选择当前计数器的值
 * @param[in] mask:     当前计数器的掩码值
 * @param[in] value:    当前计数器的计数器值
 *
 */
void xtensa_perfmon_view_cb(void *params, uint32_t select, uint32_t mask, uint32_t value);

#ifdef __cplusplus
}
#endif

#endif // _扩展_性能_ pis_H_

