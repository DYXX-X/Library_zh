/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "esp_types.h"
#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "driver/gpio.h"
#include "soc/soc_caps.h"
#include "hal/pcnt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PCNT_PIN_NOT_USED     (-1)  /*!< 当为管脚选择时，将不使用此管脚*/

typedef intr_handle_t pcnt_isr_handle_t;

/**
 * @brief PCNT端口号，最大端口号为（PCNT_port_max-1）。
 */
typedef enum {
    PCNT_PORT_0,   /*!< PCNT端口0*/
    PCNT_PORT_MAX, /*!< PCNT端口最大值*/
} pcnt_port_t;

/**
 * @brief 选择所有可用的PCNT单元
 */
typedef enum {
    PCNT_UNIT_0, /*!< PCNT单元0*/
    PCNT_UNIT_1, /*!< PCNT第一单元*/
    PCNT_UNIT_2, /*!< PCNT第二单元*/
    PCNT_UNIT_3, /*!< PCNT第三单元*/
#if SOC_PCNT_UNITS_PER_GROUP > 4
    PCNT_UNIT_4, /*!< PCNT第四单元*/
    PCNT_UNIT_5, /*!< PCNT第五单元*/
    PCNT_UNIT_6, /*!< PCNT第六单元*/
    PCNT_UNIT_7, /*!< PCNT第七单元*/
#endif
    PCNT_UNIT_MAX,
} pcnt_unit_t;

/**
 * @brief 单个PCNT单元可用的信道选择
 */
typedef enum {
    PCNT_CHANNEL_0, /*!< PCNT通道0*/
    PCNT_CHANNEL_1, /*!< PCNT通道1*/
    PCNT_CHANNEL_MAX,
} pcnt_channel_t;

/**
 * @brief 计数器事件的选择可能会触发中断
 */
typedef enum {
    PCNT_EVT_THRES_1 = 1 << 2, /*!< PCNT观察点事件：threshold1值事件*/
    PCNT_EVT_THRES_0 = 1 << 3, /*!< PCNT观察点事件：阈值0值事件*/
    PCNT_EVT_L_LIM = 1 << 4,   /*!< PCNT观察点事件：最小计数器值*/
    PCNT_EVT_H_LIM = 1 << 5,   /*!< PCNT观察点事件：最大计数器值*/
    PCNT_EVT_ZERO = 1 << 6,    /*!< PCNT观察点事件：计数器值零事件*/
    PCNT_EVT_MAX
} pcnt_evt_type_t;

/**
 * @brief 根据控制信号输入GPIO的状态选择确定计数器动作的可用模式
 * @note  配置包括两个动作，一个用于控制输入的高电平，另一个用于低电平
 */
typedef pcnt_channel_level_action_t pcnt_ctrl_mode_t;
#define PCNT_MODE_KEEP    PCNT_CHANNEL_LEVEL_ACTION_KEEP    /*!< 控制模式：不会改变计数器模式*/
#define PCNT_MODE_REVERSE PCNT_CHANNEL_LEVEL_ACTION_INVERSE /*!< 控制模式：反转计数器模式（增加->减少，减少->增加）*/
#define PCNT_MODE_DISABLE PCNT_CHANNEL_LEVEL_ACTION_HOLD    /*!< 控制模式：禁止计数器（在此情况下计数器值不会改变）*/
#define PCNT_MODE_MAX     3

/**
 * @brief 选择确定计数器在脉冲信号输入GPIO边缘上动作的可用模式
 * @note  配置包括两个动作，一个用于脉冲输入的正边缘，另一个用于负边缘
 */
typedef pcnt_channel_edge_action_t pcnt_count_mode_t;
#define PCNT_COUNT_DIS PCNT_CHANNEL_EDGE_ACTION_HOLD     /*!< 计数器模式：禁止计数器（在此情况下计数器值不会改变）*/
#define PCNT_COUNT_INC PCNT_CHANNEL_EDGE_ACTION_INCREASE /*!< 计数器模式：增加计数器值*/
#define PCNT_COUNT_DEC PCNT_CHANNEL_EDGE_ACTION_DECREASE /*!< 计数器模式：减小计数器值*/
#define PCNT_COUNT_MAX 3

/**
 * @brief 单通道脉冲计数器配置
 */
typedef struct {
    int pulse_gpio_num;          /*!< 脉冲输入GPIO编号，如果要使用GPIO16，请输入Pulse_GPIO_num=16，负值将被忽略*/
    int ctrl_gpio_num;           /*!< 控制信号输入GPIO编号，负值将被忽略*/
    pcnt_ctrl_mode_t lctrl_mode; /*!< PCNT低控制模式*/
    pcnt_ctrl_mode_t hctrl_mode; /*!< PCNT高控制模式*/
    pcnt_count_mode_t pos_mode;  /*!< PCNT正边缘计数模式*/
    pcnt_count_mode_t neg_mode;  /*!< PCNT负边缘计数模式*/
    int16_t counter_h_lim;       /*!< 最大计数器值*/
    int16_t counter_l_lim;       /*!< 最小计数器值*/
    pcnt_unit_t unit;            /*!< PCNT单元编号*/
    pcnt_channel_t channel;      /*!< PCNT通道*/
} pcnt_config_t;

/**
 * @brief 配置脉冲计数器单元@注意：此功能将禁用三个事件：PCNT_EVT_L_LIM、PCNT_EVT.H_LIM、PC-T_EVT_ZERO。
 *
 * @param pcnt_config 脉冲计数器单元配置参数指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序已初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_unit_config(const pcnt_config_t *pcnt_config);

/**
 * @brief 获取脉冲计数器值
 *
 * @param pcnt_unit  脉冲计数器单元编号
 * @param count 用于接受计数器值的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_get_counter_value(pcnt_unit_t pcnt_unit, int16_t *count);

/**
 * @brief 暂停PCNT单元的PCNT计数器
 *
 * @param pcnt_unit PCNT单元编号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_counter_pause(pcnt_unit_t pcnt_unit);

/**
 * @brief PCNT计数器的恢复计数
 *
 * @param pcnt_unit PCNT单元编号，从PCNT_unit_t中选择
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_counter_resume(pcnt_unit_t pcnt_unit);

/**
 * @brief 清除并将PCNT计数器值重置为零
 *
 * @param  pcnt_unit PCNT单元编号，从PCNT_unit_t中选择
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_counter_clear(pcnt_unit_t pcnt_unit);

/**
 * @brief 为PCNT单元启用PCNT中断@注意：每个脉冲计数器单元有五个共享相同中断的观察点事件。使用pcnt_event_enable（）和pcnt_eevent_disable（）配置事件
 *
 * @param pcnt_unit PCNT单元编号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_intr_enable(pcnt_unit_t pcnt_unit);

/**
 * @brief 禁用PCNT单元的PCNT中断
 *
 * @param pcnt_unit PCNT单元编号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_intr_disable(pcnt_unit_t pcnt_unit);

/**
 * @brief 启用PCNT单元的PCNT事件
 *
 * @param unit PCNT单元编号
 * @param evt_type 观察点事件类型。所有启用的事件共享相同的中断（每个脉冲计数器单元一个中断）。
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_event_enable(pcnt_unit_t unit, pcnt_evt_type_t evt_type);

/**
 * @brief 禁用PCNT单元的PCNT事件
 *
 * @param unit PCNT单元编号
 * @param evt_type 观察点事件类型。所有启用的事件共享相同的中断（每个脉冲计数器单元一个中断）。
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_event_disable(pcnt_unit_t unit, pcnt_evt_type_t evt_type);

/**
 * @brief 设置PCNT单元的PCNT事件值
 *
 * @param unit PCNT单元编号
 * @param evt_type 观察点事件类型。所有启用的事件共享相同的中断（每个脉冲计数器单元一个中断）。
 *
 * @param value PCNT事件的计数器值
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_set_event_value(pcnt_unit_t unit, pcnt_evt_type_t evt_type, int16_t value);

/**
 * @brief 获取PCNT单元的PCNT事件值
 *
 * @param unit PCNT单元编号
 * @param evt_type 观察点事件类型。所有启用的事件共享相同的中断（每个脉冲计数器单元一个中断）。
 * @param value 用于接受PCNT事件计数器值的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_get_event_value(pcnt_unit_t unit, pcnt_evt_type_t evt_type, int16_t *value);

/**
 * @brief 获取PCNT单元的PCNT事件状态
 *
 * @param unit PCNT单元编号
 * @param status 用于接受事件状态字的指针
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *      -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_get_event_status(pcnt_unit_t unit, uint32_t *status);

/**
 * @brief 注销PCNT中断处理程序（由PCNT_isr_register注册），该处理程序是isr。处理程序将连接到运行此函数的同一CPU内核。如果中断服务由pcnt_isr_service_install注册，请改为调用pcnt_isr _service_uninstall
 *
 * @param handle 注销ISR服务的句柄。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_NOT_FOUND找不到与标志匹配的中断。
 *     -ESP_ERR_INVALID_ARG函数指针错误。
 */
esp_err_t pcnt_isr_unregister(pcnt_isr_handle_t handle);

/**
 * @brief 注册PCNT中断处理程序，该处理程序是ISR。处理程序将附加到运行此函数的同一CPU内核。如果调用了此函数，请不要使用pcnt_isr_service_install。
 *
 * @param fn 中断处理程序函数。
 * @param arg 处理程序函数的参数
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
 * @param handle 指向返回句柄的指针。如果非NULL，将在此处返回中断的句柄。如果需要，但仅当句柄不为NULL时，调用pcnt_isr_unregister注销此isr服务。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_NOT_FOUND找不到与标志匹配的中断。
 *     -ESP_ERR_INVALID_ARG函数指针错误。
 */
esp_err_t pcnt_isr_register(void (*fn)(void *), void *arg, int intr_alloc_flags, pcnt_isr_handle_t *handle);

/**
 * @brief 配置PCNT脉冲信号输入引脚和控制输入引脚
 *
 * @param unit PCNT单元编号
 * @param channel PCNT通道编号
 * @param pulse_io 脉冲信号输入GPIO
 * @param ctrl_io 控制信号输入GPIO
 *
 * @note  如果未使用，将信号输入设置为PCNT_PIN_NOT_USED。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_set_pin(pcnt_unit_t unit, pcnt_channel_t channel, int pulse_io, int ctrl_io);

/**
 * @brief 启用PCNT输入筛选器
 *
 * @param unit PCNT单元编号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_filter_enable(pcnt_unit_t unit);

/**
 * @brief 禁用PCNT输入筛选器
 *
 * @param unit PCNT单元编号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_filter_disable(pcnt_unit_t unit);

/**
 * @brief 设置PCNT筛选器值
 *
 * @param unit PCNT单元编号
 * @param filter_val PCNT信号滤波器值，APB_CLK周期中的计数器。启用滤波器时，任何持续时间短于此的脉冲将被忽略@注意filter_val是一个10位的值，因此最大filter_val应限制为1023。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_set_filter_value(pcnt_unit_t unit, uint16_t filter_val);

/**
 * @brief 获取PCNT筛选器值
 *
 * @param unit PCNT单元编号
 * @param filter_val 用于接受PCNT筛选器值的指针。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_get_filter_value(pcnt_unit_t unit, uint16_t *filter_val);

/**
 * @brief 设置PCNT计数器模式
 *
 * @param unit PCNT单元编号
 * @param channel PCNT通道编号
 * @param pos_mode 检测正边缘时的计数器模式
 * @param neg_mode 检测负边缘时的计数器模式
 * @param hctrl_mode 控制信号为高电平时的计数器模式
 * @param lctrl_mode 控制信号为低电平时的计数器模式
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_set_mode(pcnt_unit_t unit, pcnt_channel_t channel,
                        pcnt_count_mode_t pos_mode, pcnt_count_mode_t neg_mode,
                        pcnt_ctrl_mode_t hctrl_mode, pcnt_ctrl_mode_t lctrl_mode);

/**
 * @brief 为指定单位添加ISR处理程序。
 *
 * 使用pcnt_isr_service_install（）安装pcnt驱动程序的isr处理程序服务后，调用此函数。
 *
 * ISR处理程序不需要用IRAM_ATTR声明，除非在pcnt_ISR_service_install（）中分配ISR时传递ESP_INTR_FLAG_IRAM标志。
 *
 * 将从ISR调用此ISR处理程序。因此存在堆栈大小限制（在menuconfig中可配置为“ISR堆栈大小”）。与全局PCNT中断处理程序相比，由于附加的间接级别，此限制更小。
 *
 * @param unit PCNT单元编号
 * @param isr_handler 中断处理程序函数。
 * @param args 处理程序函数的参数
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_isr_handler_add(pcnt_unit_t unit, void(*isr_handler)(void *), void *args);

/**
 * @brief 安装PCNT ISR服务。
 * @note 我们可以为每个单元管理不同的中断服务。此函数将使用默认ISR句柄服务，如果需要，调用pcnt_ISR_service_uninstall卸载默认服务。如果调用了此函数，请不要使用pcnt_isr_register。
 *
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_NO_MEM没有内存安装此服务
 *     -ESP_ERR_INVALID_STATE ISR服务已安装
 */
esp_err_t pcnt_isr_service_install(int intr_alloc_flags);

/**
 * @brief 卸载PCNT ISR服务，释放相关资源。
 */
void pcnt_isr_service_uninstall(void);

/**
 * @brief 删除指定单位的ISR处理程序。
 *
 * @param unit PCNT单元编号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE pcnt驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t pcnt_isr_handler_remove(pcnt_unit_t unit);

#ifdef __cplusplus
}
#endif

