/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdbool.h>
#include "esp_attr.h"
#include "soc/soc.h"
#include "soc/soc_caps.h"
#include "sdkconfig.h"

/**触摸板通道*/
typedef enum {
    TOUCH_PAD_NUM0 = 0, /*!< 触摸板通道0为GPIO4（ESP32）*/
    TOUCH_PAD_NUM1,     /*!< 触摸板通道1为GPIO0（ESP32）/GPIO1（ESP32-S2）*/
    TOUCH_PAD_NUM2,     /*!< 触摸板通道2为GPIO2（ESP32）/GPIO2（ESP32-S2）*/
    TOUCH_PAD_NUM3,     /*!< 触摸板通道3为GPIO15（ESP32）/GPIO3（ESP32-S2）*/
    TOUCH_PAD_NUM4,     /*!< 触摸板通道4为GPIO13（ESP32）/GPIO4（ESP32-S2）*/
    TOUCH_PAD_NUM5,     /*!< 触摸板通道5为GPIO12（ESP32）/GPIO5（ESP32-S2）*/
    TOUCH_PAD_NUM6,     /*!< 触摸板通道6为GPIO14（ESP32）/GPIO6（ESP32-S2）*/
    TOUCH_PAD_NUM7,     /*!< 触摸板通道7为GPIO27（ESP32）/GPIO7（ESP32-S2）*/
    TOUCH_PAD_NUM8,     /*!< 触摸板通道8为GPIO33（ESP32）/GPIO8（ESP32-S2）*/
    TOUCH_PAD_NUM9,     /*!< 触摸板通道9为GPIO32（ESP32）/GPIO9（ESP32-S2）*/
#if SOC_TOUCH_SENSOR_NUM > 10
    TOUCH_PAD_NUM10,    /*!< 触摸通道10为GPIO10（ESP32-S2）*/
    TOUCH_PAD_NUM11,    /*!< 触摸通道11为GPIO11（ESP32-S2）*/
    TOUCH_PAD_NUM12,    /*!< 触摸通道12为GPIO12（ESP32-S2）*/
    TOUCH_PAD_NUM13,    /*!< 触摸通道13为GPIO13（ESP32-S2）*/
    TOUCH_PAD_NUM14,    /*!< 触摸通道14为GPIO14（ESP32-S2）*/
#endif
    TOUCH_PAD_MAX,
} touch_pad_t;

/**触摸传感器高参考电压*/
typedef enum {
    TOUCH_HVOLT_KEEP = -1, /*!<触摸传感器高参考电压，无变化*/
    TOUCH_HVOLT_2V4 = 0,   /*!<触摸传感器高参考电压，2.4V*/
    TOUCH_HVOLT_2V5,       /*!<触摸传感器高参考电压，2.5V*/
    TOUCH_HVOLT_2V6,       /*!<触摸传感器高参考电压，2.6V*/
    TOUCH_HVOLT_2V7,       /*!<触摸传感器高参考电压，2.7V*/
    TOUCH_HVOLT_MAX,
} touch_high_volt_t;

/**触摸传感器低参考电压*/
typedef enum {
    TOUCH_LVOLT_KEEP = -1, /*!<触摸传感器低参考电压，无变化*/
    TOUCH_LVOLT_0V5 = 0,   /*!<触摸传感器低参考电压，0.5V*/
    TOUCH_LVOLT_0V6,       /*!<触摸传感器低参考电压，0.6V*/
    TOUCH_LVOLT_0V7,       /*!<触摸传感器低参考电压，0.7V*/
    TOUCH_LVOLT_0V8,       /*!<触摸传感器低参考电压，0.8V*/
    TOUCH_LVOLT_MAX,
} touch_low_volt_t;

/**触摸传感器高参考电压衰减*/
typedef enum {
    TOUCH_HVOLT_ATTEN_KEEP = -1,  /*!<触摸传感器高参考电压衰减，无变化*/
    TOUCH_HVOLT_ATTEN_1V5 = 0,    /*!<触摸传感器高参考电压衰减，1.5V衰减*/
    TOUCH_HVOLT_ATTEN_1V,         /*!<触摸传感器高参考电压衰减，1.0V衰减*/
    TOUCH_HVOLT_ATTEN_0V5,        /*!<触摸传感器高参考电压衰减，0.5V衰减*/
    TOUCH_HVOLT_ATTEN_0V,         /*!<触摸传感器高参考电压衰减，0V衰减*/
    TOUCH_HVOLT_ATTEN_MAX,
} touch_volt_atten_t;

/**触摸传感器充电/放电速度*/
typedef enum {
    TOUCH_PAD_SLOPE_0 = 0,       /*!<触摸传感器充电/放电速度，始终为零*/
    TOUCH_PAD_SLOPE_1 = 1,       /*!<触摸传感器充电/放电速度，最慢*/
    TOUCH_PAD_SLOPE_2 = 2,       /*!<触摸传感器充电/放电速度*/
    TOUCH_PAD_SLOPE_3 = 3,       /*!<触摸传感器充电/放电速度*/
    TOUCH_PAD_SLOPE_4 = 4,       /*!<触摸传感器充电/放电速度*/
    TOUCH_PAD_SLOPE_5 = 5,       /*!<触摸传感器充电/放电速度*/
    TOUCH_PAD_SLOPE_6 = 6,       /*!<触摸传感器充电/放电速度*/
    TOUCH_PAD_SLOPE_7 = 7,       /*!<触摸传感器充电/放电速度快*/
    TOUCH_PAD_SLOPE_MAX,
} touch_cnt_slope_t;

/**触摸传感器初始充电水平*/
typedef enum {
    TOUCH_PAD_TIE_OPT_LOW = 0,    /*!<充电电压初始电平，低电平*/
    TOUCH_PAD_TIE_OPT_HIGH = 1,   /*!<充电电压初始电平，高电平*/
    TOUCH_PAD_TIE_OPT_MAX,
} touch_tie_opt_t;

/**触摸传感器FSM模式*/
typedef enum {
    TOUCH_FSM_MODE_TIMER = 0,   /*!<通过计时器启动触摸FSM*/
    TOUCH_FSM_MODE_SW,          /*!<通过软件触发启动触摸FSM*/
    TOUCH_FSM_MODE_MAX,
} touch_fsm_mode_t;

/****仅限ESP32*****/

typedef enum {
    TOUCH_TRIGGER_BELOW = 0,   /*!<如果计数器值小于阈值，将发生触摸中断。*/
    TOUCH_TRIGGER_ABOVE = 1,   /*!<如果计数器值大于阈值，将发生触摸中断。*/
    TOUCH_TRIGGER_MAX,
} touch_trigger_mode_t;

typedef enum {
    TOUCH_TRIGGER_SOURCE_BOTH = 0,  /*!< 如果SET1和SET2都被“触摸”，则产生唤醒中断*/
    TOUCH_TRIGGER_SOURCE_SET1 = 1,  /*!< 如果SET1被“触摸”，则产生唤醒中断*/
    TOUCH_TRIGGER_SOURCE_MAX,
} touch_trigger_src_t;

/********************************/
#define TOUCH_PAD_BIT_MASK_ALL              ((1<<SOC_TOUCH_SENSOR_NUM)-1)
#define TOUCH_PAD_SLOPE_DEFAULT             (TOUCH_PAD_SLOPE_7)
#define TOUCH_PAD_TIE_OPT_DEFAULT           (TOUCH_PAD_TIE_OPT_LOW)
#define TOUCH_PAD_BIT_MASK_MAX              (TOUCH_PAD_BIT_MASK_ALL)
#define TOUCH_PAD_HIGH_VOLTAGE_THRESHOLD    (TOUCH_HVOLT_2V7)
#define TOUCH_PAD_LOW_VOLTAGE_THRESHOLD     (TOUCH_LVOLT_0V5)
#define TOUCH_PAD_ATTEN_VOLTAGE_THRESHOLD   (TOUCH_HVOLT_ATTEN_0V5)
#define TOUCH_PAD_IDLE_CH_CONNECT_DEFAULT   (TOUCH_PAD_CONN_GND)
#define TOUCH_PAD_THRESHOLD_MAX             (SOC_TOUCH_PAD_THRESHOLD_MAX) /*!<如果设置了触摸阈值最大值，则触摸传感器不能处于触摸状态*/

#ifdef CONFIG_IDF_TARGET_ESP32

#define TOUCH_PAD_SLEEP_CYCLE_DEFAULT   (0x1000)  /*!<计时器频率为RTC_SLOW_CLK（可为150k或32k，取决于选项），最大值为0xffff*/
#define TOUCH_PAD_MEASURE_CYCLE_DEFAULT (0x7fff)  /*!<定时器频率为8Mhz，最大值为0x7fff*/
#define TOUCH_FSM_MODE_DEFAULT          (TOUCH_FSM_MODE_SW)  /*!<触摸FSM可由软件或计时器启动*/
#define TOUCH_TRIGGER_MODE_DEFAULT      (TOUCH_TRIGGER_BELOW)   /*!<如果传感器值低于或高于阈值，则会触发中断*/
#define TOUCH_TRIGGER_SOURCE_DEFAULT    (TOUCH_TRIGGER_SOURCE_SET1)  /*!<唤醒触发源可以是SET1或SET1和SET2*/

#endif // CONFIG_IDF_TARGET ESP32

#if !CONFIG_IDF_TARGET_ESP32
/**
 * 总时间过长会减慢触摸响应。太小的测量时间将无法进行足够的采样，从而导致测量不准确。
 *
 * @note 测量时间的占空比越大，消耗的系统功率越大。
 */
#define TOUCH_PAD_SLEEP_CYCLE_DEFAULT   (0xf)   /*!<触摸通道的每个测量过程中的睡眠周期数。计时器频率为RTC_SLOW_CLK（取决于选项，可以为150k或32k）。范围：0~0xffff*/
#define TOUCH_PAD_MEASURE_CYCLE_DEFAULT (500)   /*!<触摸通道的每个测量过程中的充电和放电时间。定时器频率为8Mhz。建议的典型值：修改此值，使测量时间约为1ms。范围：0~0xffff*/

typedef enum {
    TOUCH_PAD_INTR_MASK_DONE = BIT(0),      /*!<为其中一个启用的通道完成测量。*/
    TOUCH_PAD_INTR_MASK_ACTIVE = BIT(1),    /*!<对其中一个已启用的通道激活。*/
    TOUCH_PAD_INTR_MASK_INACTIVE = BIT(2),  /*!<其中一个已启用通道处于非活动状态。*/
    TOUCH_PAD_INTR_MASK_SCAN_DONE = BIT(3), /*!<对所有启用的通道进行测量。*/
    TOUCH_PAD_INTR_MASK_TIMEOUT = BIT(4),   /*!<其中一个已启用通道的超时。*/
#if SOC_TOUCH_PROXIMITY_MEAS_DONE_SUPPORTED
    TOUCH_PAD_INTR_MASK_PROXI_MEAS_DONE = BIT(5),   /*!<对于接近传感器，当测量次数达到设置的测量次数时，将产生中断。*/
    TOUCH_PAD_INTR_MASK_MAX
#define TOUCH_PAD_INTR_MASK_ALL (TOUCH_PAD_INTR_MASK_TIMEOUT    \
                                | TOUCH_PAD_INTR_MASK_SCAN_DONE \
                                | TOUCH_PAD_INTR_MASK_INACTIVE  \
                                | TOUCH_PAD_INTR_MASK_ACTIVE    \
                                | TOUCH_PAD_INTR_MASK_DONE      \
                                | TOUCH_PAD_INTR_MASK_PROXI_MEAS_DONE) /*!<所有触摸中断类型启用。*/
#else
    TOUCH_PAD_INTR_MASK_MAX
#define TOUCH_PAD_INTR_MASK_ALL (TOUCH_PAD_INTR_MASK_TIMEOUT    \
                                | TOUCH_PAD_INTR_MASK_SCAN_DONE \
                                | TOUCH_PAD_INTR_MASK_INACTIVE  \
                                | TOUCH_PAD_INTR_MASK_ACTIVE    \
                                | TOUCH_PAD_INTR_MASK_DONE) /*!<所有触摸中断类型启用。*/
#endif
} touch_pad_intr_mask_t;
FLAG_ATTR(touch_pad_intr_mask_t)

typedef enum {
    TOUCH_PAD_DENOISE_BIT12 = 0,    /*!<去噪范围为12位*/
    TOUCH_PAD_DENOISE_BIT10 = 1,    /*!<去噪范围为10位*/
    TOUCH_PAD_DENOISE_BIT8 = 2,     /*!<去噪范围为8位*/
    TOUCH_PAD_DENOISE_BIT4 = 3,     /*!<去噪范围为4位*/
    TOUCH_PAD_DENOISE_MAX
} touch_pad_denoise_grade_t;

typedef enum {
    TOUCH_PAD_DENOISE_CAP_L0 = 0,   /*!<去噪通道内部参考电容为5pf*/
    TOUCH_PAD_DENOISE_CAP_L1 = 1,   /*!<去噪通道内部参考电容为6.4pf*/
    TOUCH_PAD_DENOISE_CAP_L2 = 2,   /*!<去噪通道内部参考电容为7.8pf*/
    TOUCH_PAD_DENOISE_CAP_L3 = 3,   /*!<去噪通道内部参考电容为9.2pf*/
    TOUCH_PAD_DENOISE_CAP_L4 = 4,   /*!<去噪通道内部参考电容为10.6pf*/
    TOUCH_PAD_DENOISE_CAP_L5 = 5,   /*!<去噪通道内部参考电容为12.0pf*/
    TOUCH_PAD_DENOISE_CAP_L6 = 6,   /*!<去噪通道内部参考电容为13.4pf*/
    TOUCH_PAD_DENOISE_CAP_L7 = 7,   /*!<去噪通道内部参考电容为14.8pf*/
    TOUCH_PAD_DENOISE_CAP_MAX = 8
} touch_pad_denoise_cap_t;

/**触摸传感器降噪配置*/
typedef struct touch_pad_denoise {
    touch_pad_denoise_grade_t grade;    /*!<选择去噪通道的去噪范围。通过测量去噪信道的噪声幅度来确定。*/
    touch_pad_denoise_cap_t cap_level;  /*!<选择降噪通道的内部参考电容。确保降噪读数最接近被测通道的读数。使用`touch_pad_denoise_read_data`获取去噪通道的读数。屏蔽通道的等效电容可以从去噪通道的读数中计算出来。*/
} touch_pad_denoise_t;

/**触摸传感器屏蔽通道驱动能力级别*/
typedef enum {
    TOUCH_PAD_SHIELD_DRV_L0 = 0,/*!<屏蔽通道中的最大等效电容为40pf*/
    TOUCH_PAD_SHIELD_DRV_L1,    /*!<屏蔽通道中的最大等效电容为80pf*/
    TOUCH_PAD_SHIELD_DRV_L2,    /*!<屏蔽通道中的最大等效电容为120pf*/
    TOUCH_PAD_SHIELD_DRV_L3,    /*!<屏蔽通道中的最大等效电容为160pf*/
    TOUCH_PAD_SHIELD_DRV_L4,    /*!<屏蔽通道中的最大等效电容为200pf*/
    TOUCH_PAD_SHIELD_DRV_L5,    /*!<屏蔽通道中的最大等效电容为240pf*/
    TOUCH_PAD_SHIELD_DRV_L6,    /*!<屏蔽通道中的最大等效电容为280pf*/
    TOUCH_PAD_SHIELD_DRV_L7,    /*!<屏蔽通道中的最大等效电容为320pf*/
    TOUCH_PAD_SHIELD_DRV_MAX
} touch_pad_shield_driver_t;

/**触摸传感器防水配置*/
typedef struct touch_pad_waterproof {
    touch_pad_t guard_ring_pad;             /*!<不透水的选择用于保护板的触摸通道。保护垫用于检测覆盖触摸面板的大面积水。*/
    touch_pad_shield_driver_t shield_driver;/*!<不透水的屏蔽通道驱动能力配置。屏蔽垫用于屏蔽覆盖触摸面板的水滴的影响。启用防水功能时，默认情况下，Touch14设置为屏蔽通道。屏蔽通道上的寄生电容越大，需要设置的驱动能力越高。屏蔽通道的等效电容可以通过去噪通道的读数（Touch0）来估计。*/
} touch_pad_waterproof_t;

/**触摸传感器接近检测配置*/
#define TOUCH_PROXIMITY_MEAS_NUM_MAX (0xFF)

/**触摸通道空闲状态配置*/
typedef enum {
    TOUCH_PAD_CONN_HIGHZ = 0,   /*!<触摸通道空闲状态为高电阻状态*/
    TOUCH_PAD_CONN_GND = 1,     /*!<触摸通道空闲状态为接地*/
    TOUCH_PAD_CONN_MAX
} touch_pad_conn_type_t;

/**
 * @brief 触摸通道IIR滤波器系数配置。
 * @note 在ESP32S2上。IIR计算中存在错误。误差的大小是滤波器系数的两倍。因此，请在满足过滤要求的基础上选择较小的过滤系数。建议滤波器系数选择“IIR_16”。
 */
typedef enum {
    TOUCH_PAD_FILTER_IIR_4 = 0, /*!<滤波器模式为一阶IIR滤波器。系数为4。*/
    TOUCH_PAD_FILTER_IIR_8,     /*!<滤波器模式为一阶IIR滤波器。系数为8。*/
    TOUCH_PAD_FILTER_IIR_16,    /*!<滤波器模式为一阶IIR滤波器。系数为16（典型值）。*/
    TOUCH_PAD_FILTER_IIR_32,    /*!<滤波器模式为一阶IIR滤波器。系数为32。*/
    TOUCH_PAD_FILTER_IIR_64,    /*!<滤波器模式为一阶IIR滤波器。系数为64。*/
    TOUCH_PAD_FILTER_IIR_128,   /*!<滤波器模式为一阶IIR滤波器。系数为128。*/
    TOUCH_PAD_FILTER_IIR_256,   /*!<滤波器模式为一阶IIR滤波器。系数为256。*/
    TOUCH_PAD_FILTER_JITTER,    /*!<滤波方式为抖动滤波*/
    TOUCH_PAD_FILTER_MAX
} touch_filter_mode_t;

/**
 * @brief 针对大噪声干扰对原始数据应用的滤波器级别。
 * @note 在ESP32S2上。IIR计算中存在错误。误差的大小是滤波器系数的两倍。因此，请在满足过滤要求的基础上选择较小的过滤系数。建议滤波器系数选择“IIR_2”。
 */
typedef enum {
    TOUCH_PAD_SMOOTH_OFF   = 0, /*!<不过滤原始数据。*/
    TOUCH_PAD_SMOOTH_IIR_2 = 1, /*!<过滤原始数据。系数为2（典型值）。*/
    TOUCH_PAD_SMOOTH_IIR_4 = 2, /*!<过滤原始数据。系数为4。*/
    TOUCH_PAD_SMOOTH_IIR_8 = 3, /*!<过滤原始数据。系数为8。*/
    TOUCH_PAD_SMOOTH_MAX,
} touch_smooth_mode_t;

/**触摸传感器过滤器配置*/
typedef struct touch_filter_config {
    touch_filter_mode_t mode;   /*!<设置过滤器模式。滤波器的输入是触摸读数的原始值，滤波器的输出涉及触摸状态的判断。*/
    uint32_t debounce_cnt;      /*!<设置反跳计数，如“n”。如果测量值持续超过阈值“n+1”次，则触摸传感器状态改变。范围：0~7*/
    uint32_t noise_thr;         /*!<噪声阈值系数。更高=抗噪音能力更强。实际噪声应小于（噪声系数触摸阈值）。范围：0~3。系数为0:4/8；1: 3/8; 2: 2/8; 3: 1; */
    uint32_t jitter_step;       /*!<设置抖动滤波器步长。范围：0~15*/
    touch_smooth_mode_t smh_lvl;/*!<针对大噪声干扰对原始数据应用的滤波器级别。*/
#define TOUCH_DEBOUNCE_CNT_MAX      (7)
#define TOUCH_NOISE_THR_MAX         (3)
#define TOUCH_JITTER_STEP_MAX       (15)
} touch_filter_config_t;

/**触摸传感器通道睡眠配置*/
typedef struct {
    touch_pad_t touch_num;          /*!<设置睡眠板的触摸通道编号。深度睡眠模式下仅支持一个触摸传感器通道。如果清除休眠通道，请将此极板指向`TOUCH_pad_NUM0`*/
    bool en_proximity;              /*!<启用睡眠垫的接近功能*/
} touch_pad_sleep_channel_t;

#endif // !CONFIG_IDF_TARGET_ESP32

