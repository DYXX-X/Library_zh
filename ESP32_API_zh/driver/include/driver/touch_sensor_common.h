/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "hal/touch_sensor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化触摸模块。
 * @note  如果默认参数与使用场景不匹配，则可以在该函数之后更改。
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_NO_MEM触摸板初始化错误
 *     -ESP_ERR_NOT_SUPPORTED触摸板向外部XTAL提供电流
 */
esp_err_t touch_pad_init(void);

/**
 * @brief 取消安装触摸板驱动程序。
 * @note  调用此功能后，禁止调用其他触摸功能。
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL触摸板驱动程序未初始化
 */
esp_err_t touch_pad_deinit(void);

/**
 * @brief 初始化触摸板GPIO
 * @param touch_num 触摸板索引
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_io_init(touch_pad_t touch_num);

/**
 * @brief 设置通道的触摸传感器高电压阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，高阈值应该小于电源电压。
 * @param refh DREFH的价值
 * @param refl DREFL的值
 * @param atten DREFH上的衰减
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_set_voltage(touch_high_volt_t refh, touch_low_volt_t refl, touch_volt_atten_t atten);

/**
 * @brief 获取触摸传感器参考电压，
 * @param refh 接受DREFH值的指针
 * @param refl 接受DREFL值的指针
 * @param atten 指针接受DREFH上的衰减
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_get_voltage(touch_high_volt_t *refh, touch_low_volt_t *refl, touch_volt_atten_t *atten);

/**
 * @brief 为每个极板设置触摸传感器充电/放电速度。如果斜率为0，计数器将始终为零。如果斜率为1，则充电和放电将相应地缓慢。如果斜率设置为最大值7，则充电和放电将很快。
 * @note 充电和放电电流越高，触摸通道的抗扰度越高，但会增加系统功耗。
 * @param touch_num 触摸板索引
 * @param slope 触摸板充电/放电速度
 * @param opt 初始电压
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_set_cnt_mode(touch_pad_t touch_num, touch_cnt_slope_t slope, touch_tie_opt_t opt);

/**
 * @brief 获取每个极板的触摸传感器充电/放电速度
 * @param touch_num 触摸板索引
 * @param slope 接受触摸板充电/放电斜率的指针
 * @param opt 接受初始电压的指针
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_get_cnt_mode(touch_pad_t touch_num, touch_cnt_slope_t *slope, touch_tie_opt_t *opt);

/**
 * @brief 取消注册以前使用touch_pad_isr_handler_register注册的处理程序
 * @param fn  要调用的处理程序函数（传递给touch_pad_isr_handler_register）
 * @param arg  处理程序的参数（传递给touch_pad_isr_handler_register）
 * @return
 *      -成功时ESP_OK
 *      -如果未注册同时匹配fn和arg的处理程序，则返回ESP_ERR_INVALID_STATE
 */
esp_err_t touch_pad_isr_deregister(void(*fn)(void *), void *arg);

/**
 * @brief 获取导致从深度睡眠中醒来的触摸板。
 * @param pad_num 指向导致唤醒的触摸板的指针
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_ARG参数为空
 */
esp_err_t touch_pad_get_wakeup_status(touch_pad_t *pad_num);

/**
 * @brief 设置触摸传感器FSM模式，测试动作可由计时器和软件触发。
 * @param mode FSM模式
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_set_fsm_mode(touch_fsm_mode_t mode);

/**
 * @brief 获取触摸传感器FSM模式
 * @param mode 接受FSM模式的指针
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_get_fsm_mode(touch_fsm_mode_t *mode);


/**
 * @brief 清除触摸传感器通道激活状态。
 *
 * @note FSM自动更新触摸传感器状态。通常不需要调用此API来清除状态。
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_clear_status(void);

/**
 * @brief 获取触摸传感器通道活动状态掩码。位位置表示通道编号。位的0/1状态表示触发状态。
 *
 * @return
 *      -触摸传感器状态。e、 g.触摸1触发状态为“status_mask&（BIT1）”。
 */
uint32_t touch_pad_get_status(void);

/**
 * @brief 检查触摸传感器测量状态。
 *
 * @return
 *      -正在进行真正的测量
 *      -错误测量完成
 */
bool touch_pad_meas_is_done(void);

#ifdef __cplusplus
}
#endif

