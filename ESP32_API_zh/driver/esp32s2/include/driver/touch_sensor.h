/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "driver/touch_sensor_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 设置触摸传感器FSM启动
 * @note  设置触摸传感器FSM模式后启动FSM。
 * @note  调用此功能将重置所有触摸通道的基准。
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_fsm_start(void);

/**
 * @brief 停止触摸传感器FSM。
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_fsm_stop(void);

/**
 * @brief 触发触摸传感器测量，仅支持FSM的SW模式
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_sw_start(void);

/**
 * @brief 设置触摸传感器的充电和放电时间以及睡眠时间。总时间过长会减慢触摸响应。太小的测量时间将无法进行足够的采样，从而导致测量不准确。
 *
 * @note 测量时间的占空比越大，消耗的系统功率越大。
 * @param sleep_cycle 每次测量后，触摸传感器将休眠。sleep_cycle决定每次测量之间的间隔。t_sleep=sleep_cycle/（RTC_SLOW_CLK频率）。RTC_SLOW_CLK的近似频率值可以使用RTC_CLK_SLOW_freq_get_hz函数获得。
 * @param meas_times 触摸通道的每个测量过程中的充电和放电时间。定时器频率为8Mhz。范围：0~0xffff。建议的典型值：修改此值，使测量时间约为1ms。
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_set_meas_time(uint16_t sleep_cycle, uint16_t meas_times);

/**
 * @brief 获取触摸传感器的充电和放电时间以及睡眠时间
 * @param sleep_cycle  用于接受睡眠周期号的指针
 * @param meas_times 用于接受测量次数计数的指针。
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_get_meas_time(uint16_t *sleep_cycle, uint16_t *meas_times);

/**
 * @brief 将触摸通道的连接类型设置为空闲状态。当信道处于测量模式时，其他初始化信道处于空闲模式。触摸通道通常与迹线相邻，因此空闲通道的连接状态影响测试通道的稳定性和灵敏度。“CONN_HIGHZ”（高电阻）设置增加了触摸通道的灵敏度。“CONN_GND”（接地）设置提高了触摸通道的稳定性。
 * @param type  选择空闲通道连接到高电阻状态或接地。
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_set_idle_channel_connect(touch_pad_conn_type_t type);

/**
 * @brief 将触摸通道的连接类型设置为空闲状态。当信道处于测量模式时，其他初始化信道处于空闲模式。触摸通道通常与迹线相邻，因此空闲通道的连接状态影响测试通道的稳定性和灵敏度。“CONN_HIGHZ”（高电阻）设置增加了触摸通道的灵敏度。“CONN_GND”（接地）设置提高了触摸通道的稳定性。
 * @param type  指向连接类型的指针。
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_get_idle_channel_connect(touch_pad_conn_type_t *type);

/**
 * @brief 设置触摸传感器的触发阈值。阈值确定触摸传感器的灵敏度。阈值是触发状态的原始值减去基准值。
 * @note  如果设置为“TOUCH_PAD_THRESHOLD_MAX”，则不会触发触摸。
 * @param touch_num 触摸板索引
 * @param threshold 触摸传感器的阈值。应小于触摸的最大变化值。
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_set_thresh(touch_pad_t touch_num, uint32_t threshold);

/**
 * @brief 获取触摸传感器触发阈值
 * @param touch_num 触摸板索引
 * @param threshold 接受阈值的指针
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_get_thresh(touch_pad_t touch_num, uint32_t *threshold);

/**
 * @brief 将触摸通道注册到触摸传感器扫描组中。循环扫描触摸传感器的工作模式。此函数将根据给定的位掩码设置扫描位。
 * @note  如果设置此掩码，则应首先停止FSM计时器。
 * @note  扫描图中的触摸传感器应首先通过“touch_pad_io_init”取消GPIO功能。
 * @param enable_mask 触摸传感器扫描组的位掩码。e、 g.TOUCH_PAD_NUM14->位（14）
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_set_channel_mask(uint16_t enable_mask);

/**
 * @brief 获取触摸传感器扫描组位掩码。
 * @param enable_mask 指向触摸传感器扫描组位掩码的指针。e、 g.TOUCH_PAD_NUM14->位（14）
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_get_channel_mask(uint16_t *enable_mask);

/**
 * @brief 从触摸传感器扫描组中清除触摸通道。循环扫描触摸传感器的工作模式。此函数将根据给定的位掩码清除扫描位。
 * @note  如果清除所有掩码，则应首先停止FSM计时器。
 * @param enable_mask 触摸传感器扫描组的位掩码。e、 g.TOUCH_PAD_NUM14->位（14）
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_clear_channel_mask(uint16_t enable_mask);

/**
 * @brief 为每个触摸通道配置参数。
 * @note  触摸num 0是降噪通道，请使用“Touch_pad_denoise_enable”设置降噪功能
 * @param touch_num 触摸板索引
 * @return
 *     -ESP_OK成功
 *     -如果参数错误，则为ESP_ERR_INVALID_ARG
 *     -如果触摸板未初始化，则为ESP_FAIL
 */
esp_err_t touch_pad_config(touch_pad_t touch_num);

/**
 * @brief 重置触摸模块的FSM。
 * @note  在“touch_pad_fsm_stop”之后调用此函数。
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_reset(void);

/**
 * @brief 获取当前测量通道。
 * @note  当触摸传感器测量处于循环扫描模式时，应调用。
 * @return
 *      -触摸通道编号
 */
touch_pad_t touch_pad_get_current_meas_channel(void);

/**
 * @brief 获取触摸传感器中断状态掩码。
 * @return
 *      -触摸中断位
 */
uint32_t touch_pad_read_intr_status_mask(void);

/**
 * @brief 通过位掩码启用触摸传感器中断。
 * @note  可以在ISR处理程序中调用此API。
 * @param int_mask 启用中断的填充掩码
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_intr_enable(touch_pad_intr_mask_t int_mask);

/**
 * @brief 通过位掩码禁用触摸传感器中断。
 * @note  可以在ISR处理程序中调用此API。
 * @param int_mask 用于禁用中断的填充掩码
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_intr_disable(touch_pad_intr_mask_t int_mask);

/**
 * @brief 通过位掩码清除触摸传感器中断。
 * @param int_mask 清除中断的键盘掩码
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_intr_clear(touch_pad_intr_mask_t int_mask);

/**
 * @brief   注册触摸板ISR。处理程序将连接到运行此函数的同一CPU内核。
 * @param fn  指向ISR处理程序的指针
 * @param arg  ISR参数
 * @param intr_mask 通过位掩码启用触摸传感器中断处理程序。
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM无内存
 */
esp_err_t touch_pad_isr_register(intr_handler_t fn, void *arg, touch_pad_intr_mask_t intr_mask);

/**
 * @brief 启用/禁用超时检查，并为所有触摸传感器通道测量设置超时阈值。如果启用：当触摸通道的触摸读数超过测量阈值时，将产生超时中断。如果禁用：FSM不检查被测信道是否超时。
 *
 * @note 阈值与触摸读数相比较。
 * @note 为了避免某些触摸通道的异常短路。应打开此功能。确保其他触摸通道正常工作。
 *
 * @param enable true（默认）：启用超时检查；false：禁用超时检查。
 * @param threshold 对于所有通道，在正常操作期间不会超过的最大值。
 *
* @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_timeout_set(bool enable, uint32_t threshold);

/**
 * @brief 超时后调用此接口，使触摸通道恢复正常工作。指向要测量的下一个通道。如果未调用此API，触摸FSM将在超时中断后停止测量。
 *
 * @note  在用户完成异常处理后调用此API。
 *
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_timeout_resume(void);

/**
 * @brief 获取触摸传感器的原始数据。
 * @note 初始化完成后，“raw_data”为最大值。您需要等待一个测量周期，然后才能读取正确的触摸值。
 * @param touch_num 触摸板索引
 * @param raw_data 接受触摸传感器值的指针
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL触摸频道0没有此参数。
 */

esp_err_t touch_pad_read_raw_data(touch_pad_t touch_num, uint32_t *raw_data);

/**
 * @brief 获取触摸传感器的基准。
 * @note 初始化后，基准值为第一个测量周期内的最大值。
 * @param touch_num 触摸板索引
 * @param benchmark 接受触摸传感器基准值的指针
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG触摸通道0没有此参数。
 */
esp_err_t touch_pad_read_benchmark(touch_pad_t touch_num, uint32_t *benchmark);

/**
 * @brief 获取通过过滤原始数据获得的平滑数据。
 *
 * @param touch_num 触摸板索引
 * @param smooth 平滑数据指针
 */
esp_err_t touch_pad_filter_read_smooth(touch_pad_t touch_num, uint32_t *smooth);

/**
 * @brief 强制将基准重置为触摸传感器的原始数据。
 * @param touch_num 触摸板索引
 *                  -TOUCH_PAD_MAX重置所有通道的基线
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_reset_benchmark(touch_pad_t touch_num);

/**
 * @brief 设置触摸传感器滤波器的参数和检测算法。有关检测算法的更多详细信息，请参阅应用程序文档。
 * @param filter_info 检测算法的滤波器类型和阈值选择
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_filter_set_config(const touch_filter_config_t *filter_info);

/**
 * @brief 获取触摸传感器滤波器的参数和检测算法。有关检测算法的更多详细信息，请参阅应用程序文档。
 * @param filter_info 检测算法的滤波器类型和阈值选择
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_filter_get_config(touch_filter_config_t *filter_info);

/**
 * @brief 启用用于检测算法的触摸传感器滤波器。有关检测算法的更多详细信息，请参阅应用程序文档。
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_filter_enable(void);

/**
 * @brief 禁用检测算法的触摸传感器过滤器。有关检测算法的更多详细信息，请参阅应用程序文档。
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_filter_disable(void);

/**
 * @brief 设置降噪垫的参数（TOUCH_pad_NUM0）。T0是不具有相应外部GPIO的内部通道。T0将与测量的信道Tn同时工作。最后，Tn的实际测量值是减去T0的低位后的值。降噪功能过滤掉所有信道上同时引入的干扰，例如电源和外部EMI引入的噪声。
 * @param denoise 去噪参数
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_denoise_set_config(const touch_pad_denoise_t *denoise);

/**
 * @brief 获取降噪垫的参数（TOUCH_pad_NUM0）。
 * @param denoise 指向降噪参数的指针
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_denoise_get_config(touch_pad_denoise_t *denoise);

/**
 * @brief 启用去噪功能。T0是不具有相应外部GPIO的内部通道。T0将与测量的信道Tn同时工作。最后，Tn的实际测量值是减去T0的低位后的值。降噪功能过滤掉所有信道上同时引入的干扰，例如电源和外部EMI引入的噪声。
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_denoise_enable(void);

/**
 * @brief 禁用降噪功能。
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_denoise_disable(void);

/**
 * @brief 获取降噪测量值（TOUCH_PAD_NUM0）。
 * @param data 用于接收降噪值的指针
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_denoise_read_data(uint32_t *data);

/**
 * @brief 设置防水功能参数。
 *
 *        防水功能包括屏蔽信道（TOUCH_PAD_NUM14）和保护信道。保护垫用于检测覆盖触摸面板的大面积水。屏蔽垫用于屏蔽覆盖触摸面板的水滴的影响。它通常设计为网格，并放置在触摸按钮周围。
 *
 * @param waterproof 防水参数
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_waterproof_set_config(const touch_pad_waterproof_t *waterproof);

/**
 * @brief 获取防水功能参数。
 * @param waterproof 防水参数
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_waterproof_get_config(touch_pad_waterproof_t *waterproof);

/**
 * @brief 启用防水功能参数。应在函数``touch_pad_waterproof_set_config``之后调用。
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_waterproof_enable(void);

/**
 * @brief 禁用防水功能参数。
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_waterproof_disable(void);

/**
 * @brief 启用/禁用触摸通道的接近功能。接近传感器测量是触摸通道测量的累积。
 *
 * @note 支持最多三个配置为接近传感器的触摸通道。
 * @param touch_num 触摸板索引
 * @param enabled true：启用接近功能；false：禁用接近功能
 * @return
 *     -ESP_OK：配置正确。
 *     -ESP_ERR_INVALID_ARG：触摸通道编号错误。
 *     -ESP_ERR_NOT_SUPPORTED：不支持已配置。
 */
esp_err_t touch_pad_proximity_enable(touch_pad_t touch_num, bool enabled);

/**
 * @brief 设置接近通道的测量计数。接近传感器测量是触摸通道测量的累积。
 *
 * @note 所有邻近通道使用相同的“计数”值。因此，请传递参数`TOUCH_PAD_MAX`。
 * @param touch_num 触摸板索引。在此版本中，传递参数`TOUCH_PAD_MAX`。
 * @param count 接近焊盘的累计测量次数。范围：0~255。
 * @return
 *     -ESP_OK：配置正确。
 *     -ESP_ERR_INVALID_ARG：触摸通道编号错误。
 */
esp_err_t touch_pad_proximity_set_count(touch_pad_t touch_num, uint32_t count);

/**
 * @brief 获取接近通道的测量计数。接近传感器测量是触摸通道测量的累积。
 *
 * @note 所有邻近通道使用相同的“计数”值。因此，请传递参数`TOUCH_PAD_MAX`。
 * @param touch_num 触摸板索引。在此版本中，传递参数`TOUCH_PAD_MAX`。
 * @param count 接近焊盘的累计测量次数。范围：0~255。
 * @return
 *     -ESP_OK：配置正确。
 *     -ESP_ERR_INVALID_ARG：触摸通道编号错误。
 */
esp_err_t touch_pad_proximity_get_count(touch_pad_t touch_num, uint32_t *count);

/**
 * @brief 获取接近传感器的累计测量值。接近传感器测量是触摸通道测量的累积。
 * @param touch_num 触摸板索引
 * @param measure_out 如果累积过程没有结束，则“measure_out”是过程值。
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG触摸数不接近
 */
esp_err_t touch_pad_proximity_get_data(touch_pad_t touch_num, uint32_t *measure_out);

/**
 * @brief 获取触摸传感器睡眠通道参数。触摸传感器可以在睡眠模式下工作以唤醒睡眠。
 *
 * @note  配置睡眠通道后，请使用睡眠通道的特殊功能。e、 g.用户应该使用“touch_pad_sleep_channel_read_data”而不是“touch-pad_read_raw_data”来获得睡眠信道读数。
 *
 * @param slp_config 触摸睡眠板配置。
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_sleep_channel_get_info(touch_pad_sleep_channel_t *slp_config);

/**
 * @brief 启用/禁用触摸传感器的睡眠通道功能。触摸传感器可以在睡眠模式下工作以唤醒睡眠。
 *
 * @note  ESP32S2仅支持一个睡眠信道。
 * @note  配置睡眠通道后，请使用睡眠通道的特殊功能。e、 g.用户应该使用“touch_pad_sleep_channel_read_data”而不是“touch-pad_read_raw_data”来获得睡眠信道读数。
 *
 * @param pad_num 设置睡眠板的触摸通道编号。深度睡眠模式下仅支持一个触摸传感器通道。
 * @param enable true：为触摸传感器启用睡眠垫；false：禁用触摸传感器的睡眠板；
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_sleep_channel_enable(touch_pad_t pad_num, bool enable);

/**
 * @brief 启用/禁用睡眠通道的接近功能。触摸传感器可以在睡眠模式下工作以唤醒睡眠。
 *
 * @note  ESP32S2仅支持一个睡眠信道。
 *
 * @param pad_num 设置睡眠板的触摸通道编号。深度睡眠模式下仅支持一个触摸传感器通道。
 * @param enable true：启用休眠通道的接近；false：禁用休眠通道的接近；
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_sleep_channel_enable_proximity(touch_pad_t pad_num, bool enable);

/**
 * @brief 设置深度睡眠中触摸传感器的触发阈值。阈值确定触摸传感器的灵敏度。
 *
 * @note  通常，睡眠期间的触摸阈值可以使用睡眠之前的阈值参数参数。
 *
 * @param pad_num 设置睡眠板的触摸通道编号。深度睡眠模式下仅支持一个触摸传感器通道。
 * @param touch_thres 触摸睡眠板阈值
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_sleep_set_threshold(touch_pad_t pad_num, uint32_t touch_thres);

/**
 * @brief 获取深度睡眠中触摸传感器的触发阈值。阈值确定触摸传感器的灵敏度。
 *
 * @note 通常，睡眠期间的触摸阈值可以使用睡眠之前的阈值参数参数。
 *
 * @param pad_num 设置睡眠板的触摸通道编号。深度睡眠模式下仅支持一个触摸传感器通道。
 * @param touch_thres 触摸睡眠板阈值
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_sleep_get_threshold(touch_pad_t pad_num, uint32_t *touch_thres);

/**
 * @brief 读取触摸传感器睡眠通道的基准。
 * @param pad_num 设置睡眠板的触摸通道编号。深度睡眠模式下仅支持一个触摸传感器通道。
 * @param benchmark 接受触摸传感器基准值的指针
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数为空
 */
esp_err_t touch_pad_sleep_channel_read_benchmark(touch_pad_t pad_num, uint32_t *benchmark);

/**
 * @brief 读取触摸传感器睡眠通道的平滑数据。从原始数据中过滤平滑数据。
 * @param pad_num 设置睡眠板的触摸通道编号。深度睡眠模式下仅支持一个触摸传感器通道。
 * @param smooth_data 接受触摸传感器平滑数据的指针
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数为空
 */
esp_err_t touch_pad_sleep_channel_read_smooth(touch_pad_t pad_num, uint32_t *smooth_data);

/**
 * @brief 读取触摸传感器睡眠通道的原始数据。
 * @param pad_num 设置睡眠板的触摸通道编号。深度睡眠模式下仅支持一个触摸传感器通道。
 * @param raw_data 接受触摸传感器原始数据的指针
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数为空
 */
esp_err_t touch_pad_sleep_channel_read_data(touch_pad_t pad_num, uint32_t *raw_data);

/**
 * @brief 重置触摸传感器睡眠通道的基准。
 *
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_sleep_channel_reset_benchmark(void);

/**
 * @brief 读取触摸传感器睡眠通道的接近计数。
 * @param pad_num 设置睡眠板的触摸通道编号。深度睡眠模式下仅支持一个触摸传感器通道。
 * @param proximity_cnt 接受触摸传感器接近计数值的指针
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数为空
 */
esp_err_t touch_pad_sleep_channel_read_proximity_cnt(touch_pad_t pad_num, uint32_t *proximity_cnt);

/**
 * @brief 在深度睡眠状态下更改触摸板的工作频率。降低工作频率可以有效地降低功耗。如果未调用此功能，则深度睡眠状态下的触摸工作频率与唤醒状态下的相同。
 *
 * @param sleep_cycle 每次测量后，触摸传感器将休眠。sleep_cycle决定每次测量之间的间隔。t_sleep=sleep_cycle/（RTC_SLOW_CLK频率）。RTC_SLOW_CLK的近似频率值可以使用RTC_CLK_SLOW_freq_get_hz函数获得。
 * @param meas_times 触摸通道的每个测量过程中的充电和放电时间。定时器频率为8Mhz。范围：0~0xffff。建议的典型值：修改此值，使测量时间约为1ms。
 * @return
 *     -ESP_OK成功
 */
esp_err_t touch_pad_sleep_channel_set_work_time(uint16_t sleep_cycle, uint16_t meas_times);

#ifdef __cplusplus
}
#endif

