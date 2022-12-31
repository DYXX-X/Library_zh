/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "soc/soc_caps.h"
#if SOC_MCPWM_SUPPORTED
#include "esp_err.h"
#include "soc/soc.h"
#include "driver/gpio.h"
#include "esp_intr_alloc.h"
#include "hal/mcpwm_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MCPWM的IO信号
 *
 *        -产生PWM信号的6个MCPWM输出引脚
 *        -3个MCPWM故障输入引脚，用于检测过电流、过电压等故障。
 *        -3个MCPWM同步输入引脚，用于同步MCPWM输出信号
 *        -3个MCPWM捕获输入引脚，使用例如霍尔传感器从受控电机收集反馈
 */
typedef enum {
    MCPWM0A = 0,        /*!<PWM0A输出引脚*/
    MCPWM0B,            /*!<PWM0B输出引脚*/
    MCPWM1A,            /*!<PWM1A输出引脚*/
    MCPWM1B,            /*!<PWM1B输出引脚*/
    MCPWM2A,            /*!<PWM2A输出引脚*/
    MCPWM2B,            /*!<PWM2B输出引脚*/
    MCPWM_SYNC_0,       /*!<SYNC0输入引脚*/
    MCPWM_SYNC_1,       /*!<SYNC1输入引脚*/
    MCPWM_SYNC_2,       /*!<SYNC2输入引脚*/
    MCPWM_FAULT_0,      /*!<FAULT0输入引脚*/
    MCPWM_FAULT_1,      /*!<FAULT1输入引脚*/
    MCPWM_FAULT_2,      /*!<FAULT2输入引脚*/
    MCPWM_CAP_0 = 84,   /*!<CAP0输入引脚*/
    MCPWM_CAP_1,        /*!<CAP1输入引脚*/
    MCPWM_CAP_2,        /*!<CAP2输入引脚*/
} mcpwm_io_signals_t;

/**
 * @brief MCPWM的引脚号
 */
typedef struct {
    int mcpwm0a_out_num;       /*!<MCPWM0A输出引脚*/
    int mcpwm0b_out_num;       /*!<MCPWM0A输出引脚*/
    int mcpwm1a_out_num;       /*!<MCPWM0A输出引脚*/
    int mcpwm1b_out_num;       /*!<MCPWM0A输出引脚*/
    int mcpwm2a_out_num;       /*!<MCPWM0A输出引脚*/
    int mcpwm2b_out_num;       /*!<MCPWM0A输出引脚*/
    int mcpwm_sync0_in_num;    /*!<针脚中的SYNC0*/
    int mcpwm_sync1_in_num;    /*!<针脚中的SYNC1*/
    int mcpwm_sync2_in_num;    /*!<针脚中的SYNC2*/
    int mcpwm_fault0_in_num;   /*!<引脚中的故障0*/
    int mcpwm_fault1_in_num;   /*!<引脚中的故障1*/
    int mcpwm_fault2_in_num;   /*!<引脚中的故障2*/
    int mcpwm_cap0_in_num;     /*!<引脚中的CAP0*/
    int mcpwm_cap1_in_num;     /*!<引脚中的CAP1*/
    int mcpwm_cap2_in_num;     /*!<引脚中的CAP2*/
} mcpwm_pin_config_t;

/**
 * @brief 选择MCPWM单元
 */
typedef enum {
    MCPWM_UNIT_0,   /*!<已选择MCPWM单元0*/
    MCPWM_UNIT_1,   /*!<已选择MCPWM第一单元*/
    MCPWM_UNIT_MAX, /*!<MCPWM单元的最大数量*/
} mcpwm_unit_t;

_Static_assert(MCPWM_UNIT_MAX == SOC_MCPWM_GROUPS, "MCPWM unit number not equal to chip capabilities");

/**
 * @brief 选择MCPWM计时器
 */
typedef enum {
    MCPWM_TIMER_0,   /*!<选择MCPWM时间r0*/
    MCPWM_TIMER_1,   /*!<选择MCPWM计时器1*/
    MCPWM_TIMER_2,   /*!<选择MCPWM时间2*/
    MCPWM_TIMER_MAX, /*!<单位中的最大计时器数*/
} mcpwm_timer_t;

/**
 * @brief 选择MCPWM操作员
 */
typedef enum {
    MCPWM_GEN_A,   /*!<选择MCPWMXA，其中“X”是操作员编号*/
    MCPWM_GEN_B,   /*!<选择MCPWMXB，其中“X”是操作员编号*/
    MCPWM_GEN_MAX, /*!<MCPWM每个操作员的发电机数量*/
} mcpwm_generator_t;

//IDFv4.1之前要向后兼容的定义和宏
#define MCPWM_OPR_A     MCPWM_GEN_A         ///<@已弃用
#define MCPWM_OPR_B     MCPWM_GEN_B         ///<@已弃用
#define MCPWM_OPR_MAX   MCPWM_GEN_MAX       ///<@已弃用
typedef mcpwm_generator_t mcpwm_operator_t; ///<@已弃用

/**
 * @brief MCPWM载波单热模式，在此模式下，可以对载波的第一个脉冲的宽度进行编程
 */
typedef enum {
    MCPWM_ONESHOT_MODE_DIS, /*!<启用oneshot模式*/
    MCPWM_ONESHOT_MODE_EN,  /*!<禁用oneshot模式*/
} mcpwm_carrier_os_t;

/**
 * @brief MCPWM载波输出反相，高频载波信号激活，MCPWM信号高
 */
typedef enum {
    MCPWM_CARRIER_OUT_IVT_DIS, /*!<启用载波输出反转*/
    MCPWM_CARRIER_OUT_IVT_EN,  /*!<禁用载波输出反转*/
} mcpwm_carrier_out_ivt_t;

/**
 * @brief MCPWM选择故障信号输入
 */
typedef enum {
    MCPWM_SELECT_F0, /*!<选择F0作为输入*/
    MCPWM_SELECT_F1, /*!<选择F1作为输入*/
    MCPWM_SELECT_F2, /*!<选择F2作为输入*/
} mcpwm_fault_signal_t;

/**
 * @brief MCPWM选择同步信号输入
 */
typedef enum {
    MCPWM_SELECT_NO_INPUT,        /*!<未选择同步输入*/
    MCPWM_SELECT_TIMER0_SYNC,     /*!<选择来自timer0的软件同步信号作为输入*/
    MCPWM_SELECT_TIMER1_SYNC,     /*!<选择来自计时器1的软件同步信号作为输入*/
    MCPWM_SELECT_TIMER2_SYNC,     /*!<选择来自计时器2的软件同步信号作为输入*/
    MCPWM_SELECT_GPIO_SYNC0,      /*!<选择GPIO SYNC0作为输入*/
    MCPWM_SELECT_GPIO_SYNC1,      /*!<选择GPIO SYNC1作为输入*/
    MCPWM_SELECT_GPIO_SYNC2,      /*!<选择GPIO SYNC2作为输入*/
} mcpwm_sync_signal_t;

 // 向后兼容性
#define MCPWM_SELCT_SYNC0 MCPWM_SELCT_GPIO_SYNC0
#define MCPWM_SELCT_SYNC1 MCPWM_SELCT_GPIO_SYNC1
#define MCPWM_SELCT_SYNC2 MCPWM_SELCT_GPIO_SYNC2

/**
 * @brief MCPWM计时器同步事件触发器
 */
typedef enum {
    MCPWM_SWSYNC_SOURCE_SYNCIN,      /*!<输入同步信号将被路由到其同步输出路径*/
    MCPWM_SWSYNC_SOURCE_TEZ,         /*!<计时器计数为零时产生的同步信号*/
    MCPWM_SWSYNC_SOURCE_TEP,         /*!<计时器计数达到峰值时产生的同步信号*/
    MCPWM_SWSYNC_SOURCE_DISABLED,    /*!<计时器不产生同步信号*/
} mcpwm_timer_sync_trigger_t;

/**
 * @brief MCPWM选择故障信号触发电平
 */
typedef enum {
    MCPWM_LOW_LEVEL_TGR,  /*!<当故障输入信号从高变低时发生故障*/
    MCPWM_HIGH_LEVEL_TGR, /*!<当故障输入信号从低变高时出现故障*/
} mcpwm_fault_input_level_t;

/**
 * @brief MCPWM选择捕获从哪个边缘开始
 */
typedef enum {
    MCPWM_NEG_EDGE = BIT(0),           /*!<捕捉负边缘*/
    MCPWM_POS_EDGE = BIT(1),           /*!<捕捉正面边缘*/
    MCPWM_BOTH_EDGE = BIT(1) | BIT(0), /*!<捕获两条边*/
} mcpwm_capture_on_edge_t;

/**
 * @brief MCPWM捕获的中断掩码
 */
typedef enum {
    MCPWM_LL_INTR_CAP0 = BIT(27), ///<捕获0发生
    MCPWM_LL_INTR_CAP1 = BIT(28), ///<捕获1发生
    MCPWM_LL_INTR_CAP2 = BIT(29), ///<捕获2发生
} mcpwm_intr_t;

/**
 * @brief 选择MCPWM计数器的类型
 */
typedef enum {
    MCPWM_FREEZE_COUNTER,   /*!<计数器冻结*/
    MCPWM_UP_COUNTER,       /*!<对于不对称MCPWM*/
    MCPWM_DOWN_COUNTER,     /*!<对于不对称MCPWM*/
    MCPWM_UP_DOWN_COUNTER,  /*!<对于对称MCPWM，频率为MCPWM频率设置的一半*/
    MCPWM_COUNTER_MAX,      /*!<最大计数器模式*/
} mcpwm_counter_type_t;

/**
 * @brief 选择MCPWM占空比模式的类型
 */
typedef enum {
    MCPWM_DUTY_MODE_0 = 0, /*!<有源高占空比，即占空比与不对称MCPWM的高时间成比例*/
    MCPWM_DUTY_MODE_1,     /*!<有源低占空比，即占空比与不对称MCPWM、异相（反相）MCPWM的低时间成比例*/
    MCPWM_HAL_GENERATOR_MODE_FORCE_LOW,
    MCPWM_HAL_GENERATOR_MODE_FORCE_HIGH,
    MCPWM_DUTY_MODE_MAX,   /*!<占空比模式的数量*/
} mcpwm_duty_type_t;

/**
 * @brief MCPWM死区类型，用于生成死区时间，RED表示上升沿延迟，FED表示下降沿延迟
 */
typedef enum {
    MCPWM_DEADTIME_BYPASS = 0,          /*!<绕过停滞时间*/
    MCPWM_BYPASS_RED,                   /*!<MCPWMXA输出=无延迟的MCPWMXA-In，MCPWMXB输出=有下降沿延迟的MCPWMXA-In*/
    MCPWM_BYPASS_FED,                   /*!<MCPWMXA输出=具有上升沿延迟的MCPWMXA-In，MCPWMXB输出=无延迟的MCPWMXB-In*/
    MCPWM_ACTIVE_HIGH_MODE,             /*!<MCPWMXA输出=具有上升沿延迟的MCPWMXA-In，MCPWMXB输出=具有下降沿延迟的MCAWMXA-In*/
    MCPWM_ACTIVE_LOW_MODE,              /*!<MCPWMXA Out=MCPWMXA-In，伴随上升沿延迟，MCPWMXB Out=MCPWM MXA In，伴随下降沿延迟*/
    MCPWM_ACTIVE_HIGH_COMPLIMENT_MODE,  /*!<MCPWMXA Out=具有上升沿延迟的MCPWMXA-In，MCPWMXB=具有下降沿延迟的MCAWMXA In*/
    MCPWM_ACTIVE_LOW_COMPLIMENT_MODE,   /*!<MCPWMXA Out=MCPWMXA-In，具有上升沿延迟，MCPWMXB Out=MCPWM MXA In，具有下降沿延迟*/
    MCPWM_ACTIVE_RED_FED_FROM_PWMXA,    /*!<MCPWMXA输出=MCPWMXB输出=MCPWM MXA输入，具有上升沿延迟和下降沿延迟*/
    MCPWM_ACTIVE_RED_FED_FROM_PWMXB,    /*!<MCPWMXA输出=MCPWMXB输出=MCPWM MXB输入，具有上升沿延迟和下降沿延迟*/
    MCPWM_DEADTIME_TYPE_MAX,            /*!<支持的停滞时间模式的最大数量*/
} mcpwm_deadtime_type_t;

/**
 * @brief 事件发生时对输出采取的MCPWM选择动作
 */
typedef enum {
    MCPWM_ACTION_NO_CHANGE = 0,  /*!<输出无变化*/
    MCPWM_ACTION_FORCE_LOW,      /*!<使输出低*/
    MCPWM_ACTION_FORCE_HIGH,     /*!<使输出变高*/
    MCPWM_ACTION_TOGGLE,         /*!<使输出切换*/
} mcpwm_output_action_t;

///发生故障时，在MCPWMXA上执行@弃用的MCPWM选择操作
typedef mcpwm_output_action_t mcpwm_action_on_pwmxa_t;
#define MCPWM_NO_CHANGE_IN_MCPWMXA  MCPWM_ACTION_NO_CHANGE      /*!< @已弃用MCPWMXA输出无更改*/
#define MCPWM_FORCE_MCPWMXA_LOW     MCPWM_ACTION_FORCE_LOW      /*!< @已弃用使MCPWMXA输出低*/
#define MCPWM_FORCE_MCPWMXA_HIGH    MCPWM_ACTION_FORCE_HIGH     /*!< @已弃用使MCPWMXA输出变高*/
#define MCPWM_TOG_MCPWMXA           MCPWM_ACTION_TOGGLE         /*!< @已弃用使MCPWMXA输出切换*/

///发生故障时，在MCPWMXB上执行@弃用的MCPWM选择操作
typedef mcpwm_output_action_t mcpwm_action_on_pwmxb_t;
#define MCPWM_NO_CHANGE_IN_MCPWMXB  MCPWM_ACTION_NO_CHANGE      /*!< @已弃用MCPWMXB输出无更改*/
#define MCPWM_FORCE_MCPWMXB_LOW     MCPWM_ACTION_FORCE_LOW      /*!< @已弃用使MCPWMXB输出低*/
#define MCPWM_FORCE_MCPWMXB_HIGH    MCPWM_ACTION_FORCE_HIGH     /*!< @已弃用使MCPWMXB输出变高*/
#define MCPWM_TOG_MCPWMXB           MCPWM_ACTION_TOGGLE         /*!< @已弃用使MCPWMXB输出切换*/

/**
 * @brief MCPWM选择捕获信号输入
 */
typedef enum {
    MCPWM_SELECT_CAP0, /*!<选择CAP0作为输入*/
    MCPWM_SELECT_CAP1, /*!<选择CAP1作为输入*/
    MCPWM_SELECT_CAP2, /*!<选择CAP2作为输入*/
} mcpwm_capture_signal_t;

/**
 * @brief MCPWM捕获通道ID别名
 */
typedef mcpwm_capture_signal_t mcpwm_capture_channel_id_t;

/**
 * @brief 将传递到ISR回调的事件数据
 */
typedef struct {
    mcpwm_capture_on_edge_t cap_edge;   /*!<检测到哪个信号边缘*/
    uint32_t cap_value;                 /*!<事件发生时的相应时间戳。时钟速率=APB（通常为80M）*/
} cap_event_data_t;

/**
 * @brief 捕获事件回调的类型
 * @param mcpwm MCPWM单元（0-1）
 * @param cap_channel 捕获通道ID
 * @param edata 捕获事件数据，包含捕获边缘和捕获值，由驱动程序提供
 * @param user_data 用户注册数据，从`mcpwm_capture_config_t传递`
 *
 * @note 因为这是ISR回调，所以不要做任何可能阻塞和调用设计用于ISR的API的事情（通常带有“_ISR”后缀）
 *
 * @return 回调函数返回后是否需要任务切换，这通常是由于回调唤醒了一些高优先级任务。
 *
 */
typedef bool (*cap_isr_cb_t)(mcpwm_unit_t mcpwm, mcpwm_capture_channel_id_t cap_channel, const cap_event_data_t *edata,
                             void *user_data);

/**
 * @brief MCPWM配置结构
 */
typedef struct {
    uint32_t frequency;              /*!<设置MCPWM频率（Hz）*/
    float cmpr_a;                    /*!<为操作员a（MCPWMXA）设置%占空比，即62.3%占空比时，duty_a=62.3*/
    float cmpr_b;                    /*!<为操作员b（MCPWMXB）设置%占空比，即48%占空比时，duty_b=48.0*/
    mcpwm_duty_type_t duty_mode;     /*!<设置占空比类型*/
    mcpwm_counter_type_t counter_mode;  /*!<设置MCPWM计数器的类型*/
} mcpwm_config_t;

/**
 * @brief MCPWM载波配置结构
 */
typedef struct {
    uint8_t carrier_period;                    /*!<设置载波周期=（载波周期+1）*800ns，载波周期应小于16*/
    uint8_t carrier_duty;                      /*!<设置载波占空比，carrier_duty应小于8（每12.5%递增一次）*/
    uint8_t pulse_width_in_os;                 /*!<设置单触发模式下第一个脉冲的脉冲宽度=（载波周期）*（pulse_width_in_os+1），应小于16*/
    mcpwm_carrier_os_t carrier_os_mode;        /*!<启用或禁用载波单热模式*/
    mcpwm_carrier_out_ivt_t carrier_ivt_mode;  /*!<反转载波输出*/
} mcpwm_carrier_config_t;

/**
 * @brief MCPWM配置捕获结构
 */
typedef struct {
    mcpwm_capture_on_edge_t cap_edge;      /*!<设置捕获边缘*/
    uint32_t cap_prescale;                 /*!<捕获信号的预缩放，范围从1到256*/
    cap_isr_cb_t capture_cb;               /*!<用户定义的捕获事件回调，在中断上下文下运行*/
    void *user_data;                       /*!<用户定义的ISR回调函数参数*/
} mcpwm_capture_config_t;

/**
 * @brief MCPWM配置同步结构
 */
typedef struct {
    mcpwm_sync_signal_t sync_sig;              /*!<设置使计时器同步的同步输入信号*/
    uint32_t timer_val;                        /*!<同步后要设置的计数器值，单位为0~999，单位：1/1000*峰值*/
    mcpwm_timer_direction_t count_direction;   /*!<同步后设置的计数方向*/
} mcpwm_sync_config_t;

/**
 * @brief 此函数初始化MCPWM的每个gpio信号
 *
 * @note 此函数一次初始化一个gpio。
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param io_signal 设置MCPWM信号，每个MCPWM单元有6个输出（MCPWMXA、MCPWMXB）和9个输入（SYNC_X、FAULT_X、CAP_X）“X”是timer_num（0-2）
 * @param gpio_num 设置此项以为MCPWM配置gpio，如果要使用gpio16，gpio_num=16
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_gpio_init(mcpwm_unit_t mcpwm_num, mcpwm_io_signals_t io_signal, int gpio_num);

/**
 * @brief 初始化MCPWM gpio结构
 *
 * @note 此函数一次初始化一组MCPWM GPIO。
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param mcpwm_pin MCPWM引脚结构
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_set_pin(mcpwm_unit_t mcpwm_num, const mcpwm_pin_config_t *mcpwm_pin);

/**
 * @brief 初始化MCPWM参数
 * @note 为MCPWM组和计时器配置的默认分辨率为160M/16=10M和10M/10=1M。在调用此函数之前，可以通过调用MCPWM_group_set_resolution（）和MCPWM_timer_set_resolution（）来更改默认分辨率。
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器。
 * @param mcpwm_conf 配置结构mcpwm_config_t
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_init( mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, const mcpwm_config_t  *mcpwm_conf);

/**
 * @brief 设置MCPWM组的分辨率
 * @note 这将覆盖组的默认分辨率（=10000000）。这不会自动更新频率和占空比。手动调用mcpwm_set_frequency（）和mcpwm_set _duty（）将它们设置回原位。
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param resolution 设置预期频率分辨率
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_group_set_resolution(mcpwm_unit_t mcpwm_num, unsigned long int resolution);

/**
 * @brief 设置每个计时器的分辨率
 * @note 这将覆盖计时器的默认分辨率（=1000000）。这不会自动更新频率和占空比。手动调用mcpwm_set_frequency（）和mcpwm_set _duty（）将它们设置回原位。
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param resolution 设置预期频率分辨率
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_timer_set_resolution(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, unsigned long int resolution);

/**
 * @brief 设置MCPWM定时器的频率（Hz）
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param frequency 设置每个计时器的频率（Hz）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_set_frequency(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, uint32_t frequency);

/**
 * @brief 设置每个操作员的占空比（MCPWMXA/MCPWMXB）
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param gen 设置发电机（MCPWMXA/MCPWMXB），“X”是选定的操作员编号
 * @param duty 设置每个操作员的占空比（%）（即62.3%占空比，占空比=62.3）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_set_duty(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_generator_t gen, float duty);

/**
 * @brief 设置我们中每个操作员（MCPWMXA/MCPWMXB）的占空比
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param gen 设置发电机（MCPWMXA/MCPWMXB），“x”是选定的操作员编号
 * @param duty_in_us 设置每个操作员的占空值（以微秒为单位）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_set_duty_in_us(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_generator_t gen, uint32_t duty_in_us);

/**
 * @brief 设置高有效或低有效占空比（异相/反相）
 * @note 每次在mcpwm_set_signal_high或mcpwm_set _signal_low之后调用此函数，以恢复先前设置的占空比
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param gen 设置发电机（MCPWMXA/MCPWMXB），“x”是选定的操作员编号
 * @param duty_type 设置主动低或主动高负载类型
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_set_duty_type(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_generator_t gen, mcpwm_duty_type_t duty_type);

/**
* @brief 获取计时器频率
*
* @param mcpwm_num 设置MCPWM单元（0-1）
* @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
*
* @return
*     -计时器频率
*/
uint32_t mcpwm_get_frequency(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);

/**
 * @brief 获取每个操作员的工作循环
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param gen 设置发电机（MCPWMXA/MCPWMXB），“x”是选定的操作员编号
 *
 * @return
 *     -每个操作员的占空比（56.7表示占空比为56.7%）
 */
float mcpwm_get_duty(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_operator_t gen);

/**
 * @brief 获取我们每个操作员的工作循环
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param gen 设置发电机（MCPWMXA/MCPWMXB），“x”是选定的操作员编号
 *
 * @return
 *     -每个操作员的占空比
 */
uint32_t mcpwm_get_duty_in_us(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_operator_t gen);

/**
 * @brief 使用此功能将MCPWM信号设置为高
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param gen 设置操作员（MCPWMXA/MCPWMXB），“x”是选定的计时器编号

 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_set_signal_high(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_generator_t gen);

/**
 * @brief 使用此功能将MCPWM信号设置为低
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param gen 设置操作员（MCPWMXA/MCPWMXB），“x”是选定的计时器编号

 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_set_signal_low(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_generator_t gen);

/**
 * @brief 启动定时器“x”上的MCPWM信号
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_start(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);

/**
 * @brief 启动定时器“x”上的MCPWM信号
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_stop(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);

/**
 * @brief  初始化载波配置
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param carrier_conf 配置结构mcpwm_carrier_config_t
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_carrier_init(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, const mcpwm_carrier_config_t *carrier_conf);

/**
* @brief 启用各定时器的MCPWM载波子模块
*
* @param mcpwm_num 设置MCPWM单元（0-1）
* @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
*
* @return
*     -ESP_OK成功
*     -ESP_ERR_INVALID_ARG参数错误
*/
esp_err_t mcpwm_carrier_enable(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);

/**
 * @brief 禁用各定时器的MCPWM载波子模块
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_carrier_disable(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);

/**
 * @brief 设置载波周期
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param carrier_period 设置每个计时器的载波周期，载波周期=（载波周期+1）*800ns（载波周期<=15）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_carrier_set_period(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, uint8_t carrier_period);

/**
 * @brief 设置载波的duty_周期
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param carrier_duty 设置载波的占空比，载波占空比=载波占空*12.5%（chop_duty<=7）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_carrier_set_duty_cycle(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, uint8_t carrier_duty);

/**
 * @brief 启用并设置载波单热模式下的第一个脉冲宽度
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param pulse_width 设置单热模式下第一个脉冲的脉冲宽度，宽度=（载波周期）*（pulse_width+1）（pulse-width<=15）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_carrier_oneshot_mode_enable(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, uint8_t pulse_width);

/**
 * @brief 禁用单热模式，第一脉冲宽度=载波周期
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_carrier_oneshot_mode_disable(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);

/**
 * @brief 启用或禁用载波输出反转
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param carrier_ivt_mode 启用或禁用载波输出反转
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_carrier_output_invert(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num,
                                      mcpwm_carrier_out_ivt_t carrier_ivt_mode);

/**
 * @brief 启用并初始化每个MCPWM计时器的死区时间
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param dt_mode 设置停滞时间模式
 * @param red 设置上升沿延迟=红色*100ns
 * @param fed 设置上升沿延迟＝feed*100ns
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_deadtime_enable(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_deadtime_type_t dt_mode,
                                uint32_t red, uint32_t fed);

/**
 * @brief 禁用MCPWM计时器上的死区时间
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_deadtime_disable(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);

/**
 * @brief 初始化故障子模块，当前不支持低电平触发
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param intput_level 设置故障信号电平，这将导致故障发生
 * @param fault_sig 设置需要启用的故障引脚
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_fault_init(mcpwm_unit_t mcpwm_num, mcpwm_fault_input_level_t intput_level, mcpwm_fault_signal_t fault_sig);

/**
 * @brief 在故障检测时设置一热模式，一旦在一热模式下发生故障，则需要重置以恢复MCPWM信号
 * @note 当前不支持低级别触发
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param fault_sig 设置故障引脚，该引脚需要在单热模式下启用
 * @param action_on_pwmxa 故障发生时，MCPWMXA上采取的措施，无变化或高或低或切换
 * @param action_on_pwmxb 故障发生时，MCPWMXB上采取的措施，无变化或高或低或切换
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_fault_set_oneshot_mode(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_fault_signal_t fault_sig,
                                       mcpwm_output_action_t action_on_pwmxa, mcpwm_output_action_t action_on_pwmxb);

/**
 * @brief 在故障检测时设置逐周期模式，一旦故障在周期模式下发生，故障信号一旦失效，MCPWM信号就会恢复
 * @note 当前不支持低级别触发
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param fault_sig 设置故障引脚，需要为cyc模式启用
 * @param action_on_pwmxa 故障发生时，MCPWMXA上采取的措施，无变化或高或低或切换
 * @param action_on_pwmxb 故障发生时，MCPWMXB上采取的措施，无变化或高或低或切换
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_fault_set_cyc_mode(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_fault_signal_t fault_sig,
                                   mcpwm_output_action_t action_on_pwmxa, mcpwm_output_action_t action_on_pwmxb);

/**
 * @brief 禁用故障信号
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param fault_sig 故障引脚，需要禁用
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_fault_deinit(mcpwm_unit_t mcpwm_num, mcpwm_fault_signal_t fault_sig);

/**
 * @brief 初始化捕获子模块
 *
 * @note 启用捕获功能还将启用捕获中断事件，用户必须通过“mcpwm_isr_register”注册中断处理程序，并在其中查询捕获数据。
 * @note 捕获计时器使用APB_CLK（通常为80MHz）作为计数源。
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param cap_edge 设置捕获边缘，BIT（0）-负边缘，BIT（1）-正边缘
 * @param cap_sig 捕获针，需要启用
 * @param num_of_pulse 输入捕获信号预缩放，范围从0到255，表示从1到256的预缩放。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
__attribute__((deprecated("please use mcpwm_capture_enable_channel instead")))
esp_err_t mcpwm_capture_enable(mcpwm_unit_t mcpwm_num, mcpwm_capture_signal_t cap_sig, mcpwm_capture_on_edge_t cap_edge,
                               uint32_t num_of_pulse);

/**
 * @brief 禁用捕获信号
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param cap_sig 捕获针，需要禁用
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
__attribute__((deprecated("please use mcpwm_capture_disable_channel instead")))
esp_err_t mcpwm_capture_disable(mcpwm_unit_t mcpwm_num, mcpwm_capture_signal_t cap_sig);

/**
 * @brief 启用捕获通道
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param cap_channel 捕获通道，需要启用
 * @param cap_conf 捕获通道配置
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_capture_enable_channel(mcpwm_unit_t mcpwm_num, mcpwm_capture_channel_id_t cap_channel, const mcpwm_capture_config_t *cap_conf);

/**
 * @brief 禁用捕获通道
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param cap_channel 捕获通道，需要禁用
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_capture_disable_channel(mcpwm_unit_t mcpwm_num, mcpwm_capture_channel_id_t cap_channel);

/**
 * @brief 获取捕获值
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param cap_sig 要测量值的捕获通道
 *
 * @return 捕获的值
 */
uint32_t mcpwm_capture_signal_get_value(mcpwm_unit_t mcpwm_num, mcpwm_capture_signal_t cap_sig);

/**
 * @brief 获取捕获信号的边缘
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param cap_sig 要确定其边缘的捕获通道
 *
 * @return 捕获信号边缘：1-正边缘，2-负边缘
 */
uint32_t mcpwm_capture_signal_get_edge(mcpwm_unit_t mcpwm_num, mcpwm_capture_signal_t cap_sig);

/**
 * @brief 初始化同步子模块并设置将使计时器加载预定义值的信号
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param sync_sig 设置同步输入信号
 * @param phase_val 相位值为1/1000（对于86.7%，phase_val=867），计时器移动到同步信号
 *
 * @note 此API中未定义计数方向
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
__attribute__((deprecated("please use mcpwm_sync_configure() instead")))
esp_err_t mcpwm_sync_enable(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_sync_signal_t sync_sig,
                            uint32_t phase_val);

/**
 * @brief 初始化同步子模块并设置将使计时器加载预定义值的信号
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param sync_conf 此计时器上的同步配置
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_sync_configure(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, const mcpwm_sync_config_t *sync_conf);

/**
 * @brief 禁用给定计时器上的同步子模块
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_sync_disable(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);

/**
 * @brief 在给定计时器上设置同步输出配置触发MCPWM计时器输出同步信号的事件。
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 * @param trigger 设置将使计时器产生软件同步信号的触发器。具体而言，“MCPWM_SWSYNC_SOURCE_DISABLED”将禁止计时器生成同步信号。
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t mcpwm_set_timer_sync_output(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_timer_sync_trigger_t trigger);

/**
 * @brief 触发软件同步事件并将其发送到特定计时器。
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param timer_num 设置MCPWM的定时器编号（0-2），每个MCPWM单元有3个定时器
 *
 * @note 该软件同步事件将具有与硬件同步事件相同的效果，除了：
 *         -在esp32s3上，如果通过“MCPWM_set_timer_sync_output（）”选择了“MCPWM_SWSYNC_SOURCE_SYNCIN”，则可以将软同步事件路由到其输出端`
 *         -在esp32上没有这样的行为，软同步事件仅在该计时器上生效，不能传播给其他计时器。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG函数指针错误。
 */
esp_err_t mcpwm_timer_trigger_soft_sync(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);

/**
 * @brief 设置外部GPIO同步输入反相器
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param sync_sig 设置MCPWM的同步信号，仅支持GPIO同步信号
 * @param invert GPIO同步源输入是否反相（以获得负边缘触发）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG函数指针错误。
 */
esp_err_t mcpwm_sync_invert_gpio_synchro(mcpwm_unit_t mcpwm_num, mcpwm_sync_signal_t sync_sig, bool invert);

/**
 * @brief 注册MCPWM中断处理程序，该处理程序是ISR。处理程序将连接到运行此函数的同一CPU内核。
 *
 * @param mcpwm_num 设置MCPWM单元（0-1）
 * @param fn 中断处理程序函数。
 * @param arg 用户提供的参数传递给处理程序函数。
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。有关详细信息，请参阅esp_intr_alloc.h。
 * @param handle 返回句柄的指针。如果非NULL，将在此处返回中断的句柄。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG函数指针错误。
 */
esp_err_t mcpwm_isr_register(mcpwm_unit_t mcpwm_num, void (*fn)(void *), void *arg, int intr_alloc_flags,
                             intr_handle_t *handle);

#ifdef __cplusplus
}
#endif

#endif  //SOC_MCPWM_SUPPORTED

