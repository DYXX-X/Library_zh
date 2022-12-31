/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "soc/soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file 实时
 * @brief 低电平RTC电源、时钟和睡眠功能。
 *
 * 此文件中的功能有助于配置ESP32的RTC_CNTL外围设备。RTC_CNTL外围设备处理许多功能：
 * -启用/禁用芯片各个部分的时钟和电源；这是通过使用直接寄存器访问（强制加电或断电）或允许状态机自动控制电源和时钟来实现的
 * -处理睡眠和唤醒功能
 * -保持48位计数器，可用于计时
 *
 * 这些函数不是线程安全的，不应被视为高级API。例如，虽然该文件提供了一个可以切换CPU频率的功能，但该功能本身不足以在ESP-IDF上下文中实现频率切换：还需要与RTOS、外围驱动程序和WiFi/BT堆栈进行一些协调。
 *
 * 这些功能通常不会直接用于应用程序。ESP-IDF提供或将提供使用RTC子系统功能的驱动程序和其他设施。
 *
 * 这些功能大致分为以下几组：
 * -rtc_clk：时钟切换，校准
 * -rtc_time：读取rtc计数器，计数器值与时间之间的转换
 * -rtc_sleep：进入睡眠模式
 * -rtc_init:初始化
 */

#define MHZ (1000000)

#define RTC_SLOW_CLK_X32K_CAL_TIMEOUT_THRES(cycles)  (cycles << 12)
#define RTC_SLOW_CLK_8MD256_CAL_TIMEOUT_THRES(cycles)  (cycles << 12)
#define RTC_SLOW_CLK_150K_CAL_TIMEOUT_THRES(cycles)  (cycles << 10)

#define RTC_SLOW_CLK_FREQ_150K      150000
#define RTC_SLOW_CLK_FREQ_8MD256    (RTC_FAST_CLK_FREQ_APPROX / 256)
#define RTC_SLOW_CLK_FREQ_32K       32768

#define OTHER_BLOCKS_POWERUP        1
#define OTHER_BLOCKS_WAIT           1

/* 电压与RTC_CNTL_DBIAS_WAK、RTC_CNTL_DBIAS_SLP、RTC_CNTL_DIG_BIAS_WAK值的近似映射。如果RTC_CNTL_DBG_ATTEN为0，则有效。
 */
#define RTC_CNTL_DBIAS_SLP  0   ///<sleep dig_dbias&rtc_dbias
#define RTC_CNTL_DBIAS_0V90 13  ///<数字电压
#define RTC_CNTL_DBIAS_0V95 16
#define RTC_CNTL_DBIAS_1V00 18
#define RTC_CNTL_DBIAS_1V05 20
#define RTC_CNTL_DBIAS_1V10 23
#define RTC_CNTL_DBIAS_1V15 25
#define RTC_CNTL_DBIAS_1V20 28
#define RTC_CNTL_DBIAS_1V25 30
#define RTC_CNTL_DBIAS_1V30 31 ///<电压实际上约为1.34v

#define DELAY_FAST_CLK_SWITCH           3
#define DELAY_SLOW_CLK_SWITCH           300
#define DELAY_8M_ENABLE                 50

/* 用于XTAL频率估计的8M/256时钟周期数。10个周期大约需要300微秒。
 */
#define XTAL_FREQ_EST_CYCLES            10

/* 在两种情况下需要增加芯电压：1.以240MHz运行2.以80MHz闪存频率运行
 */
#if CONFIG_ESPTOOLPY_FLASHFREQ_80M || CONFIG_ESPTOOLPY_FLASHFREQ_120M
#define DIG_DBIAS_80M_160M  RTC_CNTL_DBIAS_1V25
#else
#define DIG_DBIAS_80M_160M  RTC_CNTL_DBIAS_1V10
#endif
#define DIG_DBIAS_240M      RTC_CNTL_DBIAS_1V25
#define DIG_DBIAS_XTAL      RTC_CNTL_DBIAS_1V10
#define DIG_DBIAS_2M        RTC_CNTL_DBIAS_1V00

#define RTC_CNTL_PLL_BUF_WAIT_DEFAULT  20
#define RTC_CNTL_XTL_BUF_WAIT_DEFAULT  100
#define RTC_CNTL_CK8M_WAIT_DEFAULT  20
#define RTC_CK8M_ENABLE_WAIT_DEFAULT 5

/* 要编程到功率控制状态机中的各种延迟*/
#define RTC_CNTL_XTL_BUF_WAIT_SLP_US        (250)
#define RTC_CNTL_PLL_BUF_WAIT_SLP_CYCLES    (1)
#define RTC_CNTL_CK8M_WAIT_SLP_CYCLES       (4)
#define RTC_CNTL_WAKEUP_DELAY_CYCLES        (4)

#define RTC_CNTL_CK8M_DFREQ_DEFAULT 100
#define RTC_CNTL_SCK_DCAP_DEFAULT   255

#define RTC_CNTL_ULPCP_TOUCH_START_WAIT_IN_SLEEP    (0xFF)
#define RTC_CNTL_ULPCP_TOUCH_START_WAIT_DEFAULT     (0x10)

/*
设置sleep_init默认参数
*/
#define RTC_CNTL_DBG_ATTEN_LIGHTSLEEP_DEFAULT  5
#define RTC_CNTL_DBG_ATTEN_LIGHTSLEEP_NODROP  0
#define RTC_CNTL_DBG_ATTEN_DEEPSLEEP_DEFAULT  15
#define RTC_CNTL_DBG_ATTEN_MONITOR_DEFAULT  0
#define RTC_CNTL_BIASSLP_MONITOR_DEFAULT  0
#define RTC_CNTL_BIASSLP_SLEEP_ON  0
#define RTC_CNTL_BIASSLP_SLEEP_DEFAULT  1
#define RTC_CNTL_PD_CUR_MONITOR_DEFAULT  1
#define RTC_CNTL_PD_CUR_SLEEP_ON  0
#define RTC_CNTL_PD_CUR_SLEEP_DEFAULT  1
#define RTC_CNTL_DG_VDD_DRV_B_SLP_DEFAULT 0xf

/**
 * @brief 可能的主要XTAL频率值。
 *
 * 枚举值应等于频率（MHz）。
 */
typedef enum {
    RTC_XTAL_FREQ_32M = 32,
    RTC_XTAL_FREQ_40M = 40,     //!< 40 MHz XTAL
} rtc_xtal_freq_t;

/**
 * @brief CPU频率值
 */
typedef enum {
    RTC_CPU_FREQ_XTAL = 0,      //!< 主XTAL频率
    RTC_CPU_FREQ_80M = 1,       //!< 80兆赫
    RTC_CPU_FREQ_160M = 2,      //!< 160兆赫
    RTC_CPU_FREQ_240M = 3,      //!< 240兆赫
    RTC_CPU_FREQ_2M = 4,        //!< 2兆赫
    RTC_CPU_320M_80M = 5,       //!< 用于测试
    RTC_CPU_320M_160M = 6,      //!< 用于测试
    RTC_CPU_FREQ_XTAL_DIV2 = 7, //!< 复位后XTAL/2
} rtc_cpu_freq_t;

/**
 * @brief CPU时钟源
 */
typedef enum {
    RTC_CPU_FREQ_SRC_XTAL,  //!< XTAL
    RTC_CPU_FREQ_SRC_PLL,   //!< 锁相环（480M或320M）
    RTC_CPU_FREQ_SRC_8M,    //!< 内置8M RTC振荡器
    RTC_CPU_FREQ_SRC_APLL   //!< APLL
} rtc_cpu_freq_src_t;

/**
 * @brief CPU时钟配置结构
 */
typedef struct rtc_cpu_freq_config_s {
    rtc_cpu_freq_src_t source;      //!< 从中导出CPU时钟的时钟
    uint32_t source_freq_mhz;       //!< 源时钟频率
    uint32_t div;                   //!< 分频器，freq_mhz=source_freq_mhz/div
    uint32_t freq_mhz;              //!< CPU时钟频率
} rtc_cpu_freq_config_t;

/**
 * @brief RTC SLOW_CLK频率值
 */
typedef enum {
    RTC_SLOW_FREQ_RTC = 0,      //!< 内部150 kHz RC振荡器
    RTC_SLOW_FREQ_32K_XTAL = 1, //!< 外部32 kHz XTAL
    RTC_SLOW_FREQ_8MD256 = 2,   //!< 内部8MHz RC振荡器，除以256
} rtc_slow_freq_t;

/**
 * @brief RTC FAST_CLK频率值
 */
typedef enum {
    RTC_FAST_FREQ_XTALD4 = 0,   //!< 主XTAL，除以4
    RTC_FAST_FREQ_8M = 1,       //!< 内部8MHz RC振荡器
} rtc_fast_freq_t;

/* 默认值为CK8M_DFREQ时，8M时钟频率为8.5 MHz+/-7%*/
#define RTC_FAST_CLK_FREQ_APPROX 8500000

#define RTC_CLK_CAL_FRACT  19  //!< rtc_clk_cal返回的值中的小数位数

#define RTC_VDDSDIO_TIEH_1_8V 0 //!< 1.8V VDDSDIO的TIEH字段值
#define RTC_VDDSDIO_TIEH_3_3V 1 //!< 3.3V VDDSDIO的TIEH字段值

/**
 * @brief 使用rtc_clk_cal函数校准时钟源
 */
typedef enum {
    RTC_CAL_RTC_MUX = 0,       //!< 当前选择的RTC SLOW_CLK
    RTC_CAL_8MD256 = 1,        //!< 内部8MHz RC振荡器，除以256
    RTC_CAL_32K_XTAL = 2,      //!< 外部32 kHz XTAL
    RTC_CAL_INTERNAL_OSC = 3   //!< 内部150 kHz振荡器
} rtc_cal_sel_t;

/**
 * rtc_clk_init的初始化参数
 */
typedef struct {
    rtc_xtal_freq_t xtal_freq : 8;  //!< 主XTAL频率
    uint32_t cpu_freq_mhz : 10;    //!< 要设置的CPU频率（MHz）
    rtc_fast_freq_t fast_freq : 1;  //!< RTC_FAST_CLK频率设置
    rtc_slow_freq_t slow_freq : 2;  //!< RTC_SLOW_CLK频率设置
    uint32_t clk_rtc_clk_div : 8;
    uint32_t clk_8m_clk_div : 3;        //!< RTC 8M时钟分频器（分频为clk_8M_div+1，即0表示8MHz频率）
    uint32_t slow_clk_dcap : 8;     //!< RTC 150k时钟调整参数（值越高频率越低）
    uint32_t clk_8m_dfreq : 8;      //!< RTC 8m时钟调整参数（值越高，频率越高）
} rtc_clk_config_t;

/**
 * rtc_clk_config_t的默认初始值设定项
 */
#define RTC_CLK_CONFIG_DEFAULT() { \
    .xtal_freq = RTC_XTAL_FREQ_40M, \
    .cpu_freq_mhz = 80, \
    .fast_freq = RTC_FAST_FREQ_8M, \
    .slow_freq = RTC_SLOW_FREQ_RTC, \
    .clk_rtc_clk_div = 0, \
    .clk_8m_clk_div = 0, \
    .slow_clk_dcap = RTC_CNTL_SCK_DCAP_DEFAULT, \
    .clk_8m_dfreq = RTC_CNTL_CK8M_DFREQ_DEFAULT, \
}

typedef struct {
    uint32_t dac : 6;
    uint32_t dres : 3;
    uint32_t dgm : 3;
    uint32_t dbuf: 1;
} x32k_config_t;

#define X32K_CONFIG_DEFAULT() { \
    .dac = 3, \
    .dres = 3, \
    .dgm = 3, \
    .dbuf = 1, \
}

typedef struct {
    uint16_t wifi_powerup_cycles : 7;
    uint16_t wifi_wait_cycles : 9;
    uint16_t bt_powerup_cycles : 7;
    uint16_t bt_wait_cycles : 9;
    uint16_t rtc_powerup_cycles : 7;
    uint16_t rtc_wait_cycles : 9;
    uint16_t cpu_top_powerup_cycles : 7;
    uint16_t cpu_top_wait_cycles : 9;
    uint16_t dg_wrap_powerup_cycles : 7;
    uint16_t dg_wrap_wait_cycles : 9;
    uint16_t dg_peri_powerup_cycles : 7;
    uint16_t dg_peri_wait_cycles : 9;
    uint16_t rtc_mem_powerup_cycles : 7;
    uint16_t rtc_mem_wait_cycles : 9;
} rtc_init_config_t;

#define RTC_INIT_CONFIG_DEFAULT() { \
    .wifi_powerup_cycles = OTHER_BLOCKS_POWERUP, \
    .wifi_wait_cycles = OTHER_BLOCKS_WAIT, \
    .bt_powerup_cycles = OTHER_BLOCKS_POWERUP, \
    .bt_wait_cycles = OTHER_BLOCKS_WAIT, \
    .rtc_powerup_cycles = OTHER_BLOCKS_POWERUP, \
    .rtc_wait_cycles = OTHER_BLOCKS_WAIT, \
    .cpu_top_powerup_cycles = OTHER_BLOCKS_POWERUP, \
    .cpu_top_wait_cycles = OTHER_BLOCKS_WAIT, \
    .dg_wrap_powerup_cycles = OTHER_BLOCKS_POWERUP, \
    .dg_wrap_wait_cycles = OTHER_BLOCKS_WAIT, \
    .dg_peri_powerup_cycles = OTHER_BLOCKS_POWERUP, \
    .dg_peri_wait_cycles = OTHER_BLOCKS_WAIT, \
    .rtc_mem_powerup_cycles = OTHER_BLOCKS_POWERUP, \
    .rtc_mem_wait_cycles = OTHER_BLOCKS_WAIT, \
}

void rtc_clk_divider_set(uint32_t div);

void rtc_clk_8m_divider_set(uint32_t div);

/**
 * 初始化时钟并设置CPU频率
 *
 * @param cfg 时钟配置为rtc_clk_config_t
 */
void rtc_clk_init(rtc_clk_config_t cfg);

/**
 * @brief 获取主XTAL频率
 *
 * 这是引导加载程序存储在RTC寄存器RTC_XTAL_FREQ_REG中的值。传递给rtc_clk_init函数
 *
 * @return XTAL频率，rtc_XTAL_freq_t之一
 */
rtc_xtal_freq_t rtc_clk_xtal_freq_get(void);

/**
 * @brief 更新XTAL频率
 *
 * 更新RTC_XTAL_FREQ_REG中存储的XTAL值。通常在启动后忽略此值。
 *
 * @param xtal_freq 新频率值
 */
void rtc_clk_xtal_freq_update(rtc_xtal_freq_t xtal_freq);

/**
 * @brief 启用或禁用32 kHz XTAL振荡器
 * @param en  true表示启用，false表示禁用
 */
void rtc_clk_32k_enable(bool en);

/**
 * @brief 配置32 kHz XTAL振荡器以接受外部时钟信号
 */
void rtc_clk_32k_enable_external(void);

/**
 * @brief 获取32k XTAL振荡器的状态
 * @return 如果启用了32k XTAL振荡器，则为true
 */
bool rtc_clk_32k_enabled(void);

/**
 * @brief 启用32k振荡器，将其配置为快速启动时间。注意：为了获得更高的频率稳定性，必须在32k XTAL振荡器启动时调用rtc_clk_32k_enable函数。此函数最初将禁用32k XTAL振荡器，因此当系统将32k XTL用作RTC_SLOW_CLK时，不应调用此函数。
 *
 * @param cycle 引导外部晶体的32kHz周期数。如果为0，则不会使用方波来自举晶体振荡。
 */
void rtc_clk_32k_bootstrap(uint32_t cycle);

/**
 * @brief 启用或禁用8 MHz内部振荡器
 *
 * 8 MHz内部振荡器的输出被传送到可配置分频器，默认情况下，该分频器将输入时钟频率除以256。分频器的输出可用作RTC_SLOW_CLK源。除法器的输出在寄存器描述和代码中称为8md256或简称为d256。除256以外的除法器值可以配置，但当前不需要此功能，因此代码中未公开。
 *
 * 当不需要8MHz/256分频输出时，应禁用分频器以降低功耗。
 *
 * @param clk_8m_en 启用8MHz发电机
 * @param d256_en 真以启用/256除法器
 */
void rtc_clk_8m_enable(bool clk_8m_en, bool d256_en);

/**
 * @brief 获取8MHz内部振荡器的状态
 * @return 如果振荡器已启用，则为true
 */
bool rtc_clk_8m_enabled(void);

/**
 * @brief 获取应用于8MHz时钟的/256分频器的状态
 * @return 如果启用了分割输出，则为true
 */
bool rtc_clk_8md256_enabled(void);

/**
 * @brief 启用或禁用APLL
 *
 * 输出频率由公式给出：apll_freq=xtal_freq（4+sdm2+sdm1/256+sdm0/65536）/（（o_div+2）2）
 *
 * 此表达式中的被除数应在240-600MHz的范围内。
 *
 * 在ESP32的版本0中，sdm0和sdm1未使用，始终设置为0。
 *
 * @param enable  true表示启用，false表示禁用
 * @param sdm0  频率调整参数，0..255
 * @param sdm1  频率调整参数，0..255
 * @param sdm2  频率调整参数，0..63
 * @param o_div  分频器，0..31
 */
void rtc_clk_apll_enable(bool enable, uint32_t sdm0, uint32_t sdm1, uint32_t sdm2, uint32_t o_div);

/**
 * @brief 选择RTC_SLOW_CLK的源
 * @param slow_freq 时钟源（rtc_slow_freq_t值之一）
 */
void rtc_clk_slow_freq_set(rtc_slow_freq_t slow_freq);

/**
 * @brief 获取RTC_SLOW_CLK源
 * @return 当前选择的时钟源（rtc_slow_freq_t值之一）
 */
rtc_slow_freq_t rtc_clk_slow_freq_get(void);

/**
 * @brief 获取RTC_SLOW_CLK的近似频率（Hz）
 *
 * -如果选择RTC_SLOW_FREQ_RTC，则返回~150000
 * -如果选择RTC_SLOW_FREQ_32K_XTAL，则返回32768
 * -如果选择RTC_SLOW_FREQ_8MD256，则返回约33000
 *
 * 通过将rtc_SLOW_clk频率与主XTAL的频率进行比较，可以使用rtc_clk_cal函数来获得更精确的值。
 *
 * @return RTC_SLOW_CLK频率（Hz）
 */
uint32_t rtc_clk_slow_freq_get_hz(void);

/**
 * @brief 选择RTC_FAST_CLK的源
 * @param fast_freq 时钟源（rtc_fast_freq_t值之一）
 */
void rtc_clk_fast_freq_set(rtc_fast_freq_t fast_freq);

/**
 * @brief 获取RTC_FAST_CLK源
 * @return 当前选择的时钟源（rtc_fast_freq_t值之一）
 */
rtc_fast_freq_t rtc_clk_fast_freq_get(void);

/**
 * @brief 获取给定频率的CPU频率配置
 * @param freq_mhz  频率（MHz）
 * @param[out] out_config 输出，CPU频率配置结构
 * @return 如果可以获得频率，则为true，否则为false
 */
bool rtc_clk_cpu_freq_mhz_to_config(uint32_t freq_mhz, rtc_cpu_freq_config_t *out_config);

/**
 * @brief 切换CPU频率
 *
 * 此函数根据给定的配置结构设置CPU频率。如果需要，它启用PLL。
 *
 * @note FreeRTOS环境中的应用程序不会调用此函数。这是因为它不会根据新的CPU频率调整各种计时器。
 *
 * @param config  CPU频率配置结构
 */
void rtc_clk_cpu_freq_set_config(const rtc_cpu_freq_config_t *config);

/**
 * @brief 切换CPU频率（针对速度进行了优化）
 *
 * 此函数与rtc_clk_cpu_freq_set_config等效，速度更快。它工作得更快，因为它在从PLL切换到XTAL时不会禁用PLL，而在切换回来时不会启用PLL。如果在调用此函数从XTAL切换到PLL频率时尚未启用PLL，或者启用的PLL错误，则此函数将返回到调用rtc_clk_cpu_freq_set_config。
 *
 * 与rtc_clk_cpu_freq_set_config不同，该函数依赖于静态数据，因此从紧急处理程序（当内存可能损坏时）使用它不太安全。
 *
 * @note FreeRTOS环境中的应用程序不会调用此函数。这是因为它不会根据新的CPU频率调整各种计时器。
 *
 * @param config  CPU频率配置结构
 */
void rtc_clk_cpu_freq_set_config_fast(const rtc_cpu_freq_config_t *config);

/**
 * @brief 获取当前使用的CPU频率配置
 * @param[out] out_config  输出，CPU频率配置结构
 */
void rtc_clk_cpu_freq_get_config(rtc_cpu_freq_config_t *out_config);

/**
 * @brief 将CPU时钟源切换到XTAL
 *
 * 缩写，用于在需要切换到XTAL时填写rtc_cpu_freq_config_t结构并调用rtc_clk_cpu_freq_set_config。假设XTAL频率已确定-不要调用启动代码。
 */
void rtc_clk_cpu_freq_set_xtal(void);

/**
 * @brief 在RAM中存储新的APB频率值
 *
 * 此功能不会更改任何硬件时钟。
 *
 * 执行频率切换和更改APB频率的功能调用此功能以更新存储在RAM中的APB频率值。（这通常不应从应用程序代码中调用。）
 *
 * @param apb_freq  新APB频率，Hz
 */
void rtc_clk_apb_freq_update(uint32_t apb_freq);

/**
 * @brief 获取当前存储的APB频率。
 * @return 最后通过rtc_clk_APB_freq_update（）设置的APB频率值，单位为Hz。
 */
uint32_t rtc_clk_apb_freq_get(void);

uint32_t rtc_clk_cal_internal(rtc_cal_sel_t cal_clk, uint32_t slowclk_cycles);

/**
 * @brief 基于主XTAL频率测量RTC慢时钟的周期
 *
 * 如果要计数的给定循环数的时间超过预期时间两次，则此函数将超时并返回0。如果正在校准32k XTAL，但振荡器尚未启动（由于加载电容不正确、电路板设计问题或电路板上缺少32 XTAL），则可能会发生这种情况。
 *
 * @param cal_clk  待测时钟
 * @param slow_clk_cycles  平均慢时钟周期数
 * @return Q13.19固定点格式的平均慢时钟周期（以微秒为单位），如果校准超时，则为0
 */
uint32_t rtc_clk_cal(rtc_cal_sel_t cal_clk, uint32_t slow_clk_cycles);

/**
 * @brief 测量XTAL频率和RTC慢时钟频率之间的比率
 * @param cal_clk 待测慢时钟
 * @param slow_clk_cycles 平均慢时钟周期数
 * @return XTAL频率和慢时钟频率之间的平均比率，Q13.19定点格式，如果校准超时，则为0。
 */
uint32_t rtc_clk_cal_ratio(rtc_cal_sel_t cal_clk, uint32_t slow_clk_cycles);

/**
 * @brief 将时间间隔从微秒转换为RTC_SLOW_CLK周期
 * @param time_in_us 时间间隔（微秒）
 * @param slow_clk_period  以微秒为单位的慢时钟周期，Q13.19定点格式（由rtc_sloock_cali返回）。
 * @return 慢时钟周期数
 */
uint64_t rtc_time_us_to_slowclk(uint64_t time_in_us, uint32_t period);

/**
 * @brief 将时间间隔从RTC_SLOW_CLK转换为微秒
 * @param time_in_us RTC_SLOW_CLK周期中的时间间隔
 * @param slow_clk_period  以微秒为单位的慢时钟周期，Q13.19定点格式（由rtc_sloock_cali返回）。
 * @return 时间间隔（微秒）
 */
uint64_t rtc_time_slowclk_to_us(uint64_t rtc_cycles, uint32_t period);

/**
 * @brief 获取RTC计数器的当前值
 *
 * RTC具有48位计数器，每2个RTC_SLOW_CLK周期递增2。计数器值不可由软件写入。切换到不同的RTC_SLOW_CLK源时，不会调整该值。
 *
 * 注意：执行此功能可能需要1个RTC_SLOW_CLK周期
 *
 * @return RTC计数器的当前值
 */
uint64_t rtc_time_get(void);

uint64_t rtc_light_slp_time_get(void);

uint64_t rtc_deep_slp_time_get(void);

/**
 * @brief 忙循环直到下一个RTC_SLOW_CLK周期
 *
 * 此函数不早于下一个RTC_SLOW_CLK时钟周期返回。在某些情况下（例如，当RTC_SLOW_CLK周期非常接近时），它可能稍后返回一个RTC_SLOW-CLK周期。
 */
void rtc_clk_wait_for_slow_cycle(void);

/**
 * @brief 启用rtc数字8M时钟
 *
 * 此功能用于启用数字rtc 8M时钟以支持外围设备。要启用模拟8M时钟，请使用上面的“rtc_clk_8M_enable”函数。
 */
void rtc_dig_clk8m_enable(void);

/**
 * @brief 禁用rtc数字8M时钟
 *
 * 此功能用于禁用数字rtc 8M时钟，该时钟仅用于支持外围设备。
 */
void rtc_dig_clk8m_disable(void);

/**
 * @brief 时钟校准后计算实际时钟值
 *
 * @param cal_val 以微秒为单位的平均慢时钟周期，从`rtc_clk_cal返回的固定点值`
 * @return 时钟频率（Hz）
 */
uint32_t rtc_clk_freq_cal(uint32_t cal_val);

/**
 * @brief rtc_sleep_pd函数的通电标志
 */
typedef struct {
    uint32_t dig_fpu : 1;    //!< 设置为1以在睡眠中为数字部件供电
    uint32_t rtc_fpu : 1;    //!< 设置为1可在睡眠状态下为RTC内存供电
    uint32_t cpu_fpu : 1;    //!< 设置为1可为休眠状态下的数字存储器和CPU供电
    uint32_t i2s_fpu : 1;    //!< 设置为1以在睡眠状态下为I2S供电
    uint32_t bb_fpu : 1;     //!< 设置为1可在睡眠中启动WiFi
    uint32_t nrx_fpu : 1;    //!< 设置为1可在睡眠中启动WiFi
    uint32_t fe_fpu : 1;     //!< 设置为1可在睡眠中启动WiFi
    uint32_t sram_fpu : 1;    //!< 设置为1以在休眠状态下为SRAM供电
    uint32_t rom_ram_fpu : 1; //!< 设置为1以在休眠状态下为ROM/IRAM0_DRAM0通电
} rtc_sleep_pu_config_t;

/**
 * rtc_sleep_pu_config_t的初始化器，它将所有标志设置为相同的值
 */
#define RTC_SLEEP_PU_CONFIG_ALL(val) {\
    .dig_fpu = (val), \
    .rtc_fpu = (val), \
    .cpu_fpu = (val), \
    .i2s_fpu = (val), \
    .bb_fpu = (val), \
    .nrx_fpu = (val), \
    .fe_fpu = (val), \
    .sram_fpu = (val), \
    .rom_ram_fpu = (val), \
}

void rtc_sleep_pu(rtc_sleep_pu_config_t cfg);

/**
 * @brief rtcsleepinit函数的休眠配置
 */
typedef struct {
    uint32_t lslp_mem_inf_fpu : 1;      //!< 强制睡眠模式下的正常电压（数字域存储器）
    uint32_t rtc_mem_inf_follow_cpu : 1;//!< 在睡眠模式下保持低电压（即使使用ULP/touch）
    uint32_t rtc_fastmem_pd_en : 1;     //!< 掉电RTC快速存储器
    uint32_t rtc_slowmem_pd_en : 1;     //!< 关闭RTC慢速内存
    uint32_t rtc_peri_pd_en : 1;        //!< 关闭RTC外围设备
    uint32_t wifi_pd_en : 1;            //!< 关闭WiFi
    uint32_t bt_pd_en : 1;              //!< 断电BT
    uint32_t cpu_pd_en : 1;             //!< 关闭CPU电源，但在轻睡眠时不会重新启动。
    uint32_t int_8m_pd_en : 1;          //!< 断电内部8M振荡器
    uint32_t dig_peri_pd_en : 1;        //!< 关闭数字外围设备的电源
    uint32_t deep_slp : 1;              //!< 断电数字域
    uint32_t wdt_flashboot_mod_en : 1;  //!< 启用WDT闪存启动模式
    uint32_t dig_dbias_wak : 5;         //!< 设置数字域的偏置，处于活动模式
    uint32_t dig_dbias_slp : 5;         //!< 在休眠模式下为数字域设置偏置
    uint32_t rtc_dbias_wak : 5;         //!< 设置RTC域的偏置，处于活动模式
    uint32_t rtc_dbias_slp : 5;         //!< 设置RTC域的偏置，处于睡眠模式
    uint32_t vddsdio_pd_en : 1;         //!< 断电VDDSDIO调节器
    uint32_t xtal_fpu : 1;              //!< 保持主XTAL处于睡眠状态
    uint32_t deep_slp_reject : 1;
    uint32_t light_slp_reject : 1;
} rtc_sleep_config_t;

/**
 * rtc_sleep_config_t的默认初始值设定项
 *
 * 该初始值设定项基于RTC_SLEEP_PD_x标志的组合将所有字段设置为“合理”值（例如建议用于生产）。
 *
 * @param RTC_SLEEP_PD_x 使用位OR组合的标志
 */
#define is_dslp(pd_flags)   ((pd_flags) & RTC_SLEEP_PD_DIG)
#define RTC_SLEEP_CONFIG_DEFAULT(sleep_flags) { \
    .lslp_mem_inf_fpu = 0, \
    .rtc_mem_inf_follow_cpu = ((sleep_flags) & RTC_SLEEP_PD_RTC_MEM_FOLLOW_CPU) ? 1 : 0, \
    .rtc_fastmem_pd_en = ((sleep_flags) & RTC_SLEEP_PD_RTC_FAST_MEM) ? 1 : 0, \
    .rtc_slowmem_pd_en = ((sleep_flags) & RTC_SLEEP_PD_RTC_SLOW_MEM) ? 1 : 0, \
    .rtc_peri_pd_en = ((sleep_flags) & RTC_SLEEP_PD_RTC_PERIPH) ? 1 : 0, \
    .wifi_pd_en = ((sleep_flags) & RTC_SLEEP_PD_WIFI) ? 1 : 0, \
    .bt_pd_en = ((sleep_flags) & RTC_SLEEP_PD_BT) ? 1 : 0, \
    .cpu_pd_en = ((sleep_flags) & RTC_SLEEP_PD_CPU) ? 1 : 0, \
    .int_8m_pd_en = is_dslp(sleep_flags) ? 1 : ((sleep_flags) & RTC_SLEEP_PD_INT_8M) ? 1 : 0, \
    .dig_peri_pd_en = ((sleep_flags) & RTC_SLEEP_PD_DIG_PERIPH) ? 1 : 0, \
    .deep_slp = ((sleep_flags) & RTC_SLEEP_PD_DIG) ? 1 : 0, \
    .wdt_flashboot_mod_en = 0, \
    .dig_dbias_wak = RTC_CNTL_DBIAS_1V10, \
    .dig_dbias_slp = is_dslp(sleep_flags)                   ? RTC_CNTL_DBIAS_SLP  \
                   : !((sleep_flags) & RTC_SLEEP_PD_INT_8M) ? RTC_CNTL_DBIAS_1V10 \
                   : RTC_CNTL_DBIAS_SLP, \
    .rtc_dbias_wak = RTC_CNTL_DBIAS_1V10, \
    .rtc_dbias_slp = is_dslp(sleep_flags)                   ? RTC_CNTL_DBIAS_SLP  \
                   : !((sleep_flags) & RTC_SLEEP_PD_INT_8M) ? RTC_CNTL_DBIAS_1V10 \
                   : RTC_CNTL_DBIAS_SLP, \
    .vddsdio_pd_en = ((sleep_flags) & RTC_SLEEP_PD_VDDSDIO) ? 1 : 0, \
    .xtal_fpu = is_dslp(sleep_flags) ? 0 : ((sleep_flags) & RTC_SLEEP_PD_XTAL) ? 0 : 1, \
    .deep_slp_reject = 1, \
    .light_slp_reject = 1 \
};

#define RTC_SLEEP_PD_DIG                BIT(0)  //!< 深度睡眠（数字域断电）
#define RTC_SLEEP_PD_RTC_PERIPH         BIT(1)  //!< 关闭RTC外围设备
#define RTC_SLEEP_PD_RTC_SLOW_MEM       BIT(2)  //!< 关闭RTC SLOW内存
#define RTC_SLEEP_PD_RTC_FAST_MEM       BIT(3)  //!< 关闭RTC FAST内存
#define RTC_SLEEP_PD_RTC_MEM_FOLLOW_CPU BIT(4)  //!< RTC FAST和SLOW存储器与CPU一起自动上下电
#define RTC_SLEEP_PD_VDDSDIO            BIT(5)  //!< VDDSDIO稳压器断电
#define RTC_SLEEP_PD_WIFI               BIT(6)  //!< 关闭WIFI
#define RTC_SLEEP_PD_BT                 BIT(7)  //!< 断电BT
#define RTC_SLEEP_PD_CPU                BIT(8)  //!< 当处于睡眠状态时，关闭CPU电源，但不重新启动
#define RTC_SLEEP_PD_DIG_PERIPH         BIT(9)  //!< 关闭DIG外围设备
#define RTC_SLEEP_PD_INT_8M             BIT(10) //!< 断电内部8M振荡器
#define RTC_SLEEP_PD_XTAL               BIT(11) //!< 关闭主XTAL电源

/**
 * @brief 准备芯片进入休眠模式
 *
 * 此功能配置各种电源控制状态机以处理进入浅睡眠或深睡眠模式，切换APB和CPU时钟源（通常为XTAL），并设置数字和RTC电源域的偏置电压。
 *
 * 该功能实际上不会进入睡眠模式；这是使用rtcsleep_start函数完成的。软件可以在rtc_sleep_init和rtc_sleep _start之间执行一些其他操作，例如设置唤醒计时器和配置唤醒源。
 * @param cfg 睡眠模式配置
 */
void rtc_sleep_init(rtc_sleep_config_t cfg);

/**
 * @brief 唤醒后rtc状态机等待周期的低级别初始化
 *
 * 此功能配置芯片等待内部8MHz振荡器和外部40MHz晶体所需的周期。当我们为等待晶体配置固定时间时，我们需要通过周期来计算周期。现在，此功能仅在轻睡眠模式下使用。
 *
 * @param slowclk_period 重新校准的慢时钟周期
 */
void rtc_sleep_low_init(uint32_t slowclk_period);

/**
 * @brief 设置RTC_TIMER_TRIG_EN唤醒源的RTC计数器目标值
 * @param t 将从睡眠中唤醒的RTC计数器的值；仅使用较低的48位
 */
void rtc_sleep_set_wakeup_time(uint64_t t);


#define RTC_EXT0_TRIG_EN    BIT(0)  //!< EXT0 GPIO唤醒
#define RTC_EXT1_TRIG_EN    BIT(1)  //!< EXT1 GPIO唤醒
#define RTC_GPIO_TRIG_EN    BIT(2)  //!< GPIO唤醒（仅限浅睡眠）
#define RTC_TIMER_TRIG_EN   BIT(3)  //!< 计时器唤醒
#define RTC_SDIO_TRIG_EN    BIT(4)  //!< SDIO唤醒（仅限浅睡眠）
#define RTC_WIFI_TRIG_EN    BIT(5)  //!< WIFI唤醒（仅限轻度睡眠）
#define RTC_UART0_TRIG_EN   BIT(6)  //!< UART0唤醒（仅限轻度睡眠）
#define RTC_UART1_TRIG_EN   BIT(7)  //!< UART1唤醒（仅限轻度睡眠）
#define RTC_TOUCH_TRIG_EN   BIT(8)  //!< 触摸唤醒
#define RTC_ULP_TRIG_EN     BIT(9)  //!< ULP唤醒
#define RTC_BT_TRIG_EN      BIT(10) //!< BT唤醒（仅限轻度睡眠）
#define RTC_COCPU_TRIG_EN   BIT(11)
#define RTC_XTAL32K_DEAD_TRIG_EN    BIT(12)
#define RTC_COCPU_TRAP_TRIG_EN      BIT(13)
#define RTC_USB_TRIG_EN             BIT(14)

/**
 * @brief 进入深睡眠或浅睡眠模式
 *
 * 此函数进入先前使用rtc_sleep_init函数配置的睡眠模式。在进入睡眠状态之前，软件应适当配置唤醒源（设置GPIO唤醒寄存器、定时器唤醒寄存器等）。
 *
 * 如果使用rtc_sleep_init配置了深度睡眠模式，并且硬件不拒绝睡眠（基于拒绝opt标志），则此函数永远不会返回。当芯片从深度睡眠中醒来时，CPU复位，并从ROM引导加载程序开始执行。
 *
 * 如果使用rtc_sleep_init配置了轻睡眠模式，则该函数在唤醒时返回，或者如果硬件拒绝睡眠。
 *
 * @param wakeup_opt  启用位掩码唤醒原因（RTC_xxx_TRIG_EN标志与OR组合）
 * @param reject_opt  睡眠拒绝原因的位掩码：
 *                      - RTC_CNTL_GPIO_REJECT_EN
 *                      -RTC_CNTL_SDIO_REJECT_EN这些标志用于防止外部主机通过SDIO从机进行通信时进入休眠状态
 * @param lslp_mem_inf_fpu 如果非零，则在唤醒时立即恢复低功率配置。建议用于浅睡眠，如果系统进入深度睡眠，则无影响。
 *
 * @return 如果硬件拒绝睡眠，则为非零
 */
uint32_t rtc_sleep_start(uint32_t wakeup_opt, uint32_t reject_opt, uint32_t lslp_mem_inf_fpu);

/**
 * @brief 进入深度睡眠模式
 *
 * 类似于rtc_sleep_start（），但另外使用硬件计算rtc FAST内存的CRC值。在唤醒时，该CRC用于确定深度睡眠唤醒存根是否有效执行（如果设置了唤醒地址）。
 *
 * 在计算CRC并进入深度睡眠时，不会访问RAM，这使得即使调用方的堆栈位于RTC FAST内存中，也可以安全使用此函数。
 *
 * @note 如果未设置深度睡眠唤醒存根地址，则调用rtc_sleep_start（）将具有相同的效果，并且所需时间更短，因为跳过了CRC计算。
 *
 * @note 只有在调用了rtc_sleep_init（）以配置系统进行深度睡眠后，才能调用此函数。
 *
 * @param wakeup_opt -与rtc_sleep_start相同
 * @param reject_opt -与rtc_sleep_start相同
 *
 * @return 如果硬件拒绝睡眠，则为非零
 */
uint32_t rtc_deep_sleep_start(uint32_t wakeup_opt, uint32_t reject_opt);

/**
 * RTC电源和时钟控制初始化设置
 */
typedef struct {
    uint32_t ck8m_wait : 8;         //!< 等待8M时钟就绪的rtc_fast_clk周期数
    uint32_t xtal_wait : 8;         //!< 等待XTAL时钟就绪的rtc_fast_clk周期数
    uint32_t pll_wait : 8;          //!< 等待PLL就绪的rtc_fast_clk周期数
    uint32_t clkctl_init : 1;       //!< 执行时钟控制相关初始化
    uint32_t pwrctl_init : 1;       //!< 执行与电源控制相关的初始化
    uint32_t rtc_dboost_fpd : 1;    //!< 强制断电RTC_DBOOST
    uint32_t xtal_fpu : 1;
    uint32_t bbpll_fpu : 1;
    uint32_t cpu_waiti_clk_gate : 1;
    uint32_t cali_ocode : 1;        //!< 校准Ocode以使bangap电压更精确。
} rtc_config_t;

/**
 * rtc_config_t的默认初始值设定项。
 *
 * 此初始值设定项将所有字段设置为“合理”值（例如建议用于生产）。
 */
#define RTC_CONFIG_DEFAULT() {\
    .ck8m_wait = RTC_CNTL_CK8M_WAIT_DEFAULT, \
    .xtal_wait = RTC_CNTL_XTL_BUF_WAIT_DEFAULT, \
    .pll_wait  = RTC_CNTL_PLL_BUF_WAIT_DEFAULT, \
    .clkctl_init = 1, \
    .pwrctl_init = 1, \
    .rtc_dboost_fpd = 1, \
    .xtal_fpu = 0, \
    .bbpll_fpu = 0, \
    .cpu_waiti_clk_gate = 1, \
    .cali_ocode = 0 \
}

/**
 * 初始化RTC时钟和电源控制相关功能
 * @param cfg 配置选项为rtc_config_t
 */
void rtc_init(rtc_config_t cfg);

/**
 * 描述vddsdio配置的结构
 */
typedef struct {
    uint32_t force : 1;     //!< 如果为1，则使用RTC寄存器的配置；如果为0，则使用EFUSE/引导引脚。
    uint32_t enable : 1;    //!< 启用VDDSDIO调节器
    uint32_t tieh  : 1;     //!< 选择VDDSDIO电压。RTC_VDDSDIO_TIEH_1_8V、RTC_VDDSDIO_TIEH3_3V之一
    uint32_t drefh : 2;     //!< VDDSDIO调节器的调谐参数
    uint32_t drefm : 2;     //!< VDDSDIO调节器的调谐参数
    uint32_t drefl : 2;     //!< VDDSDIO调节器的调谐参数
} rtc_vddsdio_config_t;

/**
 * 获取当前VDDSDIO配置如果VDDSDIO配置被RTC覆盖，则从RTC获取值。否则，如果VDDSDIO由EFUSE配置，则从EFUSE获取值。
 * @return 当前使用的VDDSDIO配置
 */
rtc_vddsdio_config_t rtc_vddsdio_get_config(void);

/**
 * 使用RTC寄存器设置新的VDDSDIO配置。如果配置。force==1，这将覆盖使用引导引脚和EFUSE完成的配置。
 *
 * @param config 新VDDSDIO配置
 */
void rtc_vddsdio_set_config(rtc_vddsdio_config_t config);

#ifdef __cplusplus
}
#endif

