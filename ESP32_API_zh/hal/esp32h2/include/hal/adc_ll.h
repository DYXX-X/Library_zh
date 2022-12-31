/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "regi2c_ctrl.h"
#include "esp_attr.h"

#include "soc/adc_periph.h"
#include "hal/adc_types.h"
#include "soc/apb_saradc_struct.h"
#include "soc/apb_saradc_reg.h"
#include "soc/rtc_cntl_struct.h"
#include "soc/rtc_cntl_reg.h"
#include "hal/misc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_LL_CLKM_DIV_NUM_DEFAULT 15
#define ADC_LL_CLKM_DIV_B_DEFAULT   1
#define ADC_LL_CLKM_DIV_A_DEFAULT   0

typedef enum {
    ADC_NUM_1 = 0,          /*!< SAR ADC 1 */
    ADC_NUM_2 = 1,          /*!< SAR ADC 2 */
    ADC_NUM_MAX,
} adc_ll_num_t;

typedef enum {
    ADC_POWER_BY_FSM,   /*!< 由FSM控制的ADC XPD。用于轮询模式*/
    ADC_POWER_SW_ON,    /*!< ADC XPD由软件控制。开机。用于DMA模式*/
    ADC_POWER_SW_OFF,   /*!< ADC XPD由软件控制。关闭电源。*/
    ADC_POWER_MAX,      /*!< 用于参数检查。*/
} adc_ll_power_t;

typedef enum {
    ADC_RTC_DATA_OK = 0,
    ADC_RTC_CTRL_UNSELECTED = 1,
    ADC_RTC_CTRL_BREAK = 2,
    ADC_RTC_DATA_FAIL = -1,
} adc_ll_rtc_raw_data_t;

typedef enum {
    ADC_LL_CTRL_DIG = 0,    ///<对于ADC1。选择DIG控制器。
    ADC_LL_CTRL_ARB = 1,    ///<对于ADC2。控制器由仲裁器选择。
} adc_ll_controller_t;

/**
 * @brief ADC数字控制器（DMA模式）工作模式。
 *
 * @note  转换模式影响采样频率：ESP32H2仅支持ALTER_UNIT模式ALTER_UINIT：触发测量时，ADC1或ADC2交替采样。
 */
typedef enum {
    ADC_LL_DIGI_CONV_ALTER_UNIT = 0,     // 依次使用ADC1和ADC2进行转换。e、 g.ADC1->ADC2->ADC1->ADC 2。。。。。
} adc_ll_digi_convert_mode_t;

//这些值应根据硬件设置
typedef enum {
    ADC_LL_INTR_THRES1_LOW  = BIT(26),
    ADC_LL_INTR_THRES0_LOW  = BIT(27),
    ADC_LL_INTR_THRES1_HIGH = BIT(28),
    ADC_LL_INTR_THRES0_HIGH = BIT(29),
    ADC_LL_INTR_ADC2_DONE   = BIT(30),
    ADC_LL_INTR_ADC1_DONE   = BIT(31),
} adc_ll_intr_t;
FLAG_ATTR(adc_ll_intr_t)

typedef struct  {
    union {
        struct {
            uint8_t atten:      2;
            uint8_t channel:    3;
            uint8_t unit:       1;
            uint8_t reserved:   2;
        };
        uint8_t val;
    };
} __attribute__((packed)) adc_ll_digi_pattern_table_t;

/*---------------------------------------------------------------
                    数字控制器设置
---------------------------------------------------------------*/

/**
 * 设置数字控制器的adc fsm间隔参数。对于相同的平台，这些值是固定的。
 *
 * @param rst_wait DIG ADC控制器重置ADC传感器和启动ADC传感器之间的周期。
 * @param start_wait 打开xpd后的延迟时间。
 * @param standby_wait 关闭xpd的延迟时间。
 */
static inline void adc_ll_digi_set_fsm_time(uint32_t rst_wait, uint32_t start_wait, uint32_t standby_wait)
{
    // 内部FSM重置等待时间
    HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC.fsm_wait, rstb_wait, rst_wait);
    // 内部FSM启动等待时间
    HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC.fsm_wait, xpd_wait, start_wait);
    // 内部FSM待机等待时间
    HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC.fsm_wait, standby_wait, standby_wait);
}

/**
 * 设置数字控制器的adc采样周期。
 *
 * @note 通常，请使用默认值。
 * @param sample_cycle DIG ADC控制器启动ADC传感器和开始从传感器接收数据之间的周期。范围：2~0xFF。
 */
static inline void adc_ll_set_sample_cycle(uint32_t sample_cycle)
{
    /* 应在写入I2C寄存器之前调用。*/
    SET_PERI_REG_MASK(RTC_CNTL_ANA_CONF_REG, RTC_CNTL_SAR_I2C_PU);
    REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_SAMPLE_CYCLE_ADDR, sample_cycle);
}

/**
 * 设置SAR ADC模块时钟分频因子。SAR ADC时钟与数字控制器时钟分开。
 *
 * @param div 除法系数。
 */
static inline void adc_ll_digi_set_clk_div(uint32_t div)
{
    /* 与数字控制器时钟clk分开的ADC时钟*/
    HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC.ctrl, sar_clk_div, div);
}

/**
 * 设置数字控制器的adc最大转换数。如果ADC转换次数等于最大值，则停止转换。
 *
 * @param meas_num 最大转换数。范围：0~255。
 */
static inline void adc_ll_digi_set_convert_limit_num(uint32_t meas_num)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC.ctrl2, max_meas_num, meas_num);
}

/**
 * 启用数字控制器的最大转换数检测。如果ADC转换次数等于最大值，则停止转换。
 */
static inline void adc_ll_digi_convert_limit_enable(void)
{
    APB_SARADC.ctrl2.meas_num_limit = 1;
}

/**
 * 禁用数字控制器的最大转换数检测。如果ADC转换次数等于最大值，则停止转换。
 */
static inline void adc_ll_digi_convert_limit_disable(void)
{
    APB_SARADC.ctrl2.meas_num_limit = 0;
}

/**
 * 设置数字控制器的adc转换模式。
 *
 * @note ESP32H2仅支持ADC1单模。
 *
 * @param mode 转换模式选择。
 */
static inline void adc_ll_digi_set_convert_mode(adc_ll_digi_convert_mode_t mode)
{
    //ESP32H2仅支持ADC_CONV_ALTER_UNIT模式
}

/**
 * 设置数字控制器的模式表长度。定义每个SAR ADC的转换规则的模式表。每个表有8个项目，其中存储了信道选择和衰减。当转换开始时，控制器从模式表中逐个读取转换规则。对于每个控制器，扫描序列在重复之前最多有8个不同的规则。
 *
 * @param adc_n ADC单元。
 * @param patt_len 项目范围：1~8。
 */
static inline void adc_ll_digi_set_pattern_table_len(adc_ll_num_t adc_n, uint32_t patt_len)
{
    APB_SARADC.ctrl.sar_patt_len = patt_len - 1;
}

/**
 * 设置数字控制器的模式表。定义每个SAR ADC的转换规则的模式表。每个表有8项，其中存储了信道选择、分辨率和衰减。当转换开始时，控制器从模式表中逐个读取转换规则。对于每个控制器，扫描序列在重复之前最多有8个不同的规则。
 *
 * @param adc_n ADC单元。
 * @param pattern_index 项目索引。范围：0~7。
 * @param pattern 存储的转换规则。
 */
static inline void adc_ll_digi_set_pattern_table(adc_ll_num_t adc_n, uint32_t pattern_index, adc_digi_pattern_config_t table)
{
    uint32_t tab;
    uint8_t index = pattern_index / 4;
    uint8_t offset = (pattern_index % 4) * 6;
    adc_ll_digi_pattern_table_t pattern = {0};

    pattern.val = (table.atten & 0x3) | ((table.channel & 0x7) << 2) | ((table.unit & 0x1) << 5);
    tab = APB_SARADC.sar_patt_tab[index].sar_patt_tab1;         // 读取旧寄存器值
    tab &= (~(0xFC0000 >> offset));                             // 清除旧数据
    tab |= ((uint32_t)(pattern.val & 0x3F) << 18) >> offset;    // 填写新数据
    APB_SARADC.sar_patt_tab[index].sar_patt_tab1 = tab;         // 回写
}

/**
 * 重置模式表指针，然后在下一次测量中从表头获取测量规则。
 *
 * @param adc_n ADC单元。
 */
static inline void adc_ll_digi_clear_pattern_table(adc_ll_num_t adc_n)
{
    APB_SARADC.ctrl.sar_patt_p_clear = 1;
    APB_SARADC.ctrl.sar_patt_p_clear = 0;
}

/**
 * 设置转换完成并等待仲裁器稳定所需的周期数。
 *
 * @note 只有ADC2具有仲裁器功能。
 * @param cycle 范围：0~4。
 */
static inline void adc_ll_digi_set_arbiter_stable_cycle(uint32_t cycle)
{
    APB_SARADC.ctrl.wait_arb_cycle = cycle;
}

/**
 * ADC数字控制器输出数据是否反转。
 *
 * @param adc_n ADC单元。
 * @param inv_en 数据是否反转。
 */
static inline void adc_ll_digi_output_invert(adc_ll_num_t adc_n, bool inv_en)
{
    if (adc_n == ADC_NUM_1) {
        APB_SARADC.ctrl2.sar1_inv = inv_en;   // 启用/禁用ADC数据反转
    } else { // adc_n==adc_NUM_2
        APB_SARADC.ctrl2.sar2_inv = inv_en;   // 启用/禁用ADC数据反转
    }
}

/**
 * 设置数字控制器触发测量的间隔时钟周期。表达式：`trigger_meas_freq`=`controller_clk`/2/interval。
 *
 * @note 触发间隔不应小于SAR ADC的采样时间。
 * @param cycle 测量的时钟周期（触发间隔）。范围：30~4095。
 */
static inline void adc_ll_digi_set_trigger_interval(uint32_t cycle)
{
    APB_SARADC.ctrl2.timer_target = cycle;
}

/**
 * 启用数字控制器计时器以触发测量。
 */
static inline void adc_ll_digi_trigger_enable(void)
{
    APB_SARADC.ctrl2.timer_en = 1;
}

/**
 * 禁用数字控制器计时器以触发测量。
 */
static inline void adc_ll_digi_trigger_disable(void)
{
    APB_SARADC.ctrl2.timer_en = 0;
}

/**
 * 设置ADC数字控制器时钟分频因子。从“APLL”或“APB”时钟分频的时钟。表达式：controller_clk=（APLL或APB）/（div_num+div_a/div_b+1）。
 *
 * @param div_num 除法系数。范围：0~255。
 * @param div_b 除法系数。范围：1~63。
 * @param div_a 除法系数。范围：0~63。
 */
static inline void adc_ll_digi_controller_clk_div(uint32_t div_num, uint32_t div_b, uint32_t div_a)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC.apb_adc_clkm_conf, clkm_div_num, div_num);
    APB_SARADC.apb_adc_clkm_conf.clkm_div_b = div_b;
    APB_SARADC.apb_adc_clkm_conf.clkm_div_a = div_a;
}

/**
 * 启用时钟并为ADC数字控制器选择时钟源。
 *
 * @param use_apll true：使用APLL时钟；false：使用APB时钟。
 */
static inline void adc_ll_digi_clk_sel(bool use_apll)
{
    if (use_apll) {
        APB_SARADC.apb_adc_clkm_conf.clk_sel = 1;   // APLL时钟
    } else {
        APB_SARADC.apb_adc_clkm_conf.clk_sel = 2;   // APB时钟
    }
    APB_SARADC.ctrl.sar_clk_gated = 1;
}

/**
 * 禁用ADC数字控制器的时钟。
 */
static inline void adc_ll_digi_controller_clk_disable(void)
{
    APB_SARADC.ctrl.sar_clk_gated = 0;
}

/**
 * 重置adc数字控制器滤波器。
 *
 * @param adc_n ADC单元。
 */
static inline void adc_ll_digi_filter_reset(adc_ll_num_t adc_n)
{
    APB_SARADC.filter_ctrl0.filter_reset = 1;
}

/**
 * 设置adc数字控制器滤波器系数。
 *
 * @note 如果不支持频道信息，则不会启用过滤功能。
 * @param idx ADC滤波器单元。
 * @param filter 过滤器配置。表达式：filter_data=（k-1）/k*last_data+new_data/k。设置值：（2、4、8、16、64）。
 */
static inline void adc_ll_digi_filter_set_factor(adc_digi_filter_idx_t idx, adc_digi_filter_t *filter)
{
    if (idx == ADC_DIGI_FILTER_IDX0) {
        APB_SARADC.filter_ctrl0.filter_channel0 = (filter->adc_unit << 3) | (filter->channel & 0x7);
        APB_SARADC.filter_ctrl1.filter_factor0 = filter->mode;
    } else if (idx == ADC_DIGI_FILTER_IDX1) {
        APB_SARADC.filter_ctrl0.filter_channel1 = (filter->adc_unit << 3) | (filter->channel & 0x7);
        APB_SARADC.filter_ctrl1.filter_factor1 = filter->mode;
    }
}

/**
 * 获取adc数字控制器滤波器系数。
 *
 * @param adc_n ADC单元。
 * @param factor 表达式：filter_data=（k-1）/k*last_data+new_data/k。设置值：（2、4、8、16、64）。
 */
static inline void adc_ll_digi_filter_get_factor(adc_digi_filter_idx_t idx, adc_digi_filter_t *filter)
{
    if (idx == ADC_DIGI_FILTER_IDX0) {
        filter->adc_unit = (APB_SARADC.filter_ctrl0.filter_channel0 >> 3) & 0x1;
        filter->channel = APB_SARADC.filter_ctrl0.filter_channel0 & 0x7;
        filter->mode = APB_SARADC.filter_ctrl1.filter_factor0;
    } else if (idx == ADC_DIGI_FILTER_IDX1) {
        filter->adc_unit = (APB_SARADC.filter_ctrl0.filter_channel1 >> 3) & 0x1;
        filter->channel = APB_SARADC.filter_ctrl0.filter_channel1 & 0x7;
        filter->mode = APB_SARADC.filter_ctrl1.filter_factor1;
    }
}

/**
 * 禁用adc数字控制器滤波器。对ADC数据进行滤波，以获得更高采样率的平滑数据。
 *
 * @note 如果不支持频道信息，则不会启用过滤功能。
 * @param adc_n ADC单元。
 */
static inline void adc_ll_digi_filter_disable(adc_digi_filter_idx_t idx)
{
    if (idx == ADC_DIGI_FILTER_IDX0) {
        APB_SARADC.filter_ctrl0.filter_channel0 = 0xF;
        APB_SARADC.filter_ctrl1.filter_factor0 = 0;
    } else if (idx == ADC_DIGI_FILTER_IDX1) {
        APB_SARADC.filter_ctrl0.filter_channel1 = 0xF;
        APB_SARADC.filter_ctrl1.filter_factor1 = 0;
    }
}

/**
 * 设置adc数字控制器的监控模式。
 *
 * @note 如果不支持频道信息，则不会启用监视器功能。
 * @param adc_n ADC单元。
 * @param is_larger true：如果ADC_OUT>阈值，则生成监视器中断。false：如果ADC_OUT<阈值，则生成监视器中断。
 */
static inline void adc_ll_digi_monitor_set_mode(adc_digi_monitor_idx_t idx, adc_digi_monitor_t *cfg)
{
    if (idx == ADC_DIGI_MONITOR_IDX0) {
        APB_SARADC.thres0_ctrl.thres0_channel = (cfg->adc_unit << 3) | (cfg->channel & 0x7);
        APB_SARADC.thres0_ctrl.thres0_high = cfg->h_threshold;
        APB_SARADC.thres0_ctrl.thres0_low = cfg->l_threshold;
    } else { // ADC_DIGI_MONITOR_IDX1
        APB_SARADC.thres1_ctrl.thres1_channel = (cfg->adc_unit << 3) | (cfg->channel & 0x7);
        APB_SARADC.thres1_ctrl.thres1_high = cfg->h_threshold;
        APB_SARADC.thres1_ctrl.thres1_low = cfg->l_threshold;
    }
}

/**
 * 启用/禁用adc数字控制器的监视器。
 *
 * @note 如果不支持频道信息，则不会启用监视器功能。
 * @param adc_n ADC单元。
 */
static inline void adc_ll_digi_monitor_disable(adc_digi_monitor_idx_t idx)
{
    if (idx == ADC_DIGI_MONITOR_IDX0) {
        APB_SARADC.thres0_ctrl.thres0_channel = 0xF;
    } else { // ADC_DIGI_MONITOR_IDX1
        APB_SARADC.thres1_ctrl.thres1_channel = 0xF;
    }
}

/**
 * 设置adc数字控制器的DMA of num。如果测量次数达到“dma_eof_num”，则生成“dma_in_suc_eof”信号。
 *
 * @param num DMA的数量。
 */
static inline void adc_ll_digi_dma_set_eof_num(uint32_t num)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(APB_SARADC.dma_conf, apb_adc_eof_num, num);
}

/**
 * 启用从adc数字控制器到DMA的输出数据。
 */
static inline void adc_ll_digi_dma_enable(void)
{
    APB_SARADC.dma_conf.apb_adc_trans = 1;
}

/**
 * 禁用从adc数字控制器到DMA的输出数据。
 */
static inline void adc_ll_digi_dma_disable(void)
{
    APB_SARADC.dma_conf.apb_adc_trans = 0;
}

/**
 * 重置adc数字控制器。
 */
static inline void adc_ll_digi_reset(void)
{
    APB_SARADC.dma_conf.apb_adc_reset_fsm = 1;
    APB_SARADC.dma_conf.apb_adc_reset_fsm = 0;
}

/*---------------------------------------------------------------
                    PWDET（功率检测）控制器设置
---------------------------------------------------------------*/
/**
 * 为PWDET控制器设置adc cct。
 *
 * @note PA功率监视器的电容器调谐。cct设置为与PHY相同的值。
 * @param cct 范围：0~7。
 */
static inline void adc_ll_pwdet_set_cct(uint32_t cct)
{
    /* PA功率监视器的电容器调谐。cct设置为与PHY相同的值。*/
    abort();
}

/**
 * 获取PWDET控制器的adc cct。
 *
 * @note PA功率监视器的电容器调谐。cct设置为与PHY相同的值。
 * @return cct范围：0~7。
 */
static inline uint32_t adc_ll_pwdet_get_cct(void)
{
    /* PA功率监视器的电容器调谐。cct设置为与PHY相同的值。*/
    abort();
}

/**
 * 分析获得的原始数据是否正确。ADC2可以使用仲裁器。仲裁结果被存储在返回数据的信道信息中。
 *
 * @param adc_n ADC单元。
 * @param raw_data ADC原始数据输入（转换值）。
 * @return
 *        -0：数据使用正确。
 *        --1：数据无效。
 */
static inline adc_ll_rtc_raw_data_t adc_ll_analysis_raw_data(adc_ll_num_t adc_n, int raw_data)
{
    if (adc_n == ADC_NUM_1) {
        return ADC_RTC_DATA_OK;
    }

    //原始数据API返回的值没有通道信息。直接从寄存器读取值
    if (((APB_SARADC.apb_saradc2_data_status.adc2_data >> 13) & 0xF) > 9) {
        return ADC_RTC_DATA_FAIL;
    }

    return ADC_RTC_DATA_OK;
}

/*---------------------------------------------------------------
                    常用设置
---------------------------------------------------------------*/
/**
 * 设置ADC模块电源管理。
 *
 * @param manage 设置ADC电源状态。
 */
static inline void adc_ll_set_power_manage(adc_ll_power_t manage)
{
    /* Bit1 0:Fsm 1:SW模式Bit0 0:SW模式断电1:SW模式通电*/
    if (manage == ADC_POWER_SW_ON) {
        APB_SARADC.ctrl.sar_clk_gated = 1;
        APB_SARADC.ctrl.xpd_sar_force = 3;
    } else if (manage == ADC_POWER_BY_FSM) {
        APB_SARADC.ctrl.sar_clk_gated = 1;
        APB_SARADC.ctrl.xpd_sar_force = 0;
    } else if (manage == ADC_POWER_SW_OFF) {
        APB_SARADC.ctrl.sar_clk_gated = 0;
        APB_SARADC.ctrl.xpd_sar_force = 2;
    }
}

static inline void adc_ll_set_controller(adc_ll_num_t adc_n, adc_ll_controller_t ctrl)
{
    //未在ESP32H2上使用
}

/**
 * 设置ADC2模块仲裁器工作模式。仲裁器是为了提高ADC2的使用效率，在控制权被高优先级抢走后，低优先级控制器将读取无效的ADC数据，数据的有效性可以通过数据中的标志位来判断。
 *
 * @note 只有ADC2支持仲裁器。
 * @note 仲裁器的工作时钟为APB_CLK。当APB_CLK时钟低于8MHz时，仲裁器必须处于屏蔽模式。
 *
 * @param mode 请参阅“adc_arbiter_mode_t”。
 */
static inline void adc_ll_set_arbiter_work_mode(adc_arbiter_mode_t mode)
{
    if (mode == ADC_ARB_MODE_FIX) {
        APB_SARADC.apb_adc_arb_ctrl.adc_arb_grant_force = 0;
        APB_SARADC.apb_adc_arb_ctrl.adc_arb_fix_priority = 1;
    } else if (mode == ADC_ARB_MODE_LOOP) {
        APB_SARADC.apb_adc_arb_ctrl.adc_arb_grant_force = 0;
        APB_SARADC.apb_adc_arb_ctrl.adc_arb_fix_priority = 0;
    } else {
        APB_SARADC.apb_adc_arb_ctrl.adc_arb_grant_force = 1;    // 屏蔽仲裁器。
    }
}

/**
 * 在仲裁器中设置ADC2模块控制器优先级。仲裁器是为了提高ADC2的使用效率，在控制权被高优先级抢走后，低优先级控制器将读取无效的ADC数据，数据的有效性可以通过数据中的标志位来判断。
 *
 * @note 只有ADC2支持仲裁器。
 * @note 仲裁器的工作时钟为APB_CLK。当APB_CLK时钟低于8MHz时，仲裁器必须处于屏蔽模式。
 * @note 默认优先级：Wi-Fi（2）>RTC（1）>数字（0）；
 *
 * @param pri_rtc RTC控制器优先级。范围：0~2。
 * @param pri_dig 数字控制器优先级。范围：0~2。
 * @param pri_pwdet Wi-Fi控制器优先级。范围：0~2。
 */
static inline void adc_ll_set_arbiter_priority(uint8_t pri_rtc, uint8_t pri_dig, uint8_t pri_pwdet)
{
    if (pri_rtc != pri_dig && pri_rtc != pri_pwdet && pri_dig != pri_pwdet) {
        APB_SARADC.apb_adc_arb_ctrl.adc_arb_rtc_priority = pri_rtc;
        APB_SARADC.apb_adc_arb_ctrl.adc_arb_apb_priority = pri_dig;
        APB_SARADC.apb_adc_arb_ctrl.adc_arb_wifi_priority = pri_pwdet;
    }
    /* 应选择最高优先级控制器。*/
    if (pri_rtc > pri_dig) {
        if (pri_rtc > pri_pwdet) {
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_apb_force = 0;
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_rtc_force = 1;
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_wifi_force = 0;
        } else {
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_apb_force = 0;
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_rtc_force = 0;
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_wifi_force = 1;
        }
    } else {
        if (pri_dig > pri_pwdet) {
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_apb_force = 1;
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_rtc_force = 0;
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_wifi_force = 0;
        } else {
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_apb_force = 0;
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_rtc_force = 0;
            APB_SARADC.apb_adc_arb_ctrl.adc_arb_wifi_force = 1;
        }
    }
}

/* ADC校准代码。*/
/**
 * @brief 设置常用校准配置。应与其他部分共享（PWDET）。
 */
static inline void adc_ll_calibration_init(adc_ll_num_t adc_n)
{
    if (adc_n == ADC_NUM_1) {
        REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_DREF_ADDR, 1);
    } else {
        REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_DREF_ADDR, 1);
    }
}

/**
 * 配置ADC校准寄存器。您需要调用``adc_ll_calibration_finish``接口以在校准后继续。
 *
 * @note  不同的ADC单元和不同的衰减选项使用不同的校准数据（初始数据）。
 *
 * @param adc_n ADC索引编号。
 * @param channel adc通道编号。
 * @param internal_gnd true：从IO端口断开连接，并使用内部GND作为校准电压。false：使用IO外部电压作为校准电压。
 */
static inline void adc_ll_calibration_prepare(adc_ll_num_t adc_n, adc_channel_t channel, bool internal_gnd)
{
    /* 启用/禁用内部连接GND（用于校准）。*/
    if (adc_n == ADC_NUM_1) {
        if (internal_gnd) {
            REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_ENCAL_GND_ADDR, 1);
        } else {
            REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_ENCAL_GND_ADDR, 0);
        }
    } else {
        if (internal_gnd) {
            REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_ENCAL_GND_ADDR, 1);
        } else {
            REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_ENCAL_GND_ADDR, 0);
        }
    }
}

/**
 * 校准后恢复寄存器状态。
 *
 * @param adc_n ADC索引编号。
 */
static inline void adc_ll_calibration_finish(adc_ll_num_t adc_n)
{
    if (adc_n == ADC_NUM_1) {
        REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_ENCAL_GND_ADDR, 0);
    } else {
        REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_ENCAL_GND_ADDR, 0);
    }
}

/**
 * 将校准结果设置为ADC。
 *
 * @note  不同的ADC单元和不同的衰减选项使用不同的校准数据（初始数据）。
 *
 * @param adc_n ADC索引编号。
 */
static inline void adc_ll_set_calibration_param(adc_ll_num_t adc_n, uint32_t param)
{
    uint8_t msb = param >> 8;
    uint8_t lsb = param & 0xFF;
    if (adc_n == ADC_NUM_1) {
        REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_INITIAL_CODE_HIGH_ADDR, msb);
        REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_INITIAL_CODE_LOW_ADDR, lsb);
    } else {
        REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_INITIAL_CODE_HIGH_ADDR, msb);
        REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_INITIAL_CODE_LOW_ADDR, lsb);
    }
}
/* 温度代码结束。*/

/**
 *  向ADC2通道输出ADCn间参考电压。
 *
 *  此函数将ADCn的内部参考电压路由到ADC1的一个通道。然后，可以手动测量该参考电压以进行校准。
 *
 *  @param[in]  adc ADC单元选择
 *  @param[in]  channel ADC1通道编号
 *  @param[in]  en 启用/禁用参考电压输出
 */
static inline void adc_ll_vref_output(adc_ll_num_t adc, adc_channel_t channel, bool en)
{
    abort();
}

/*---------------------------------------------------------------
                    单次读取
---------------------------------------------------------------*/
/**
 * 触发单次读取
 *
 * @param val 用法：设置为1以启动ADC转换。阶跃信号应至少保持3个ADC数字控制器时钟周期，否则当阶跃信号的频率较低时，ADC数字控制器可能无法捕获阶跃信号。此硬件限制将在未来版本中删除。
 */
static inline void adc_ll_onetime_start(bool val)
{
    APB_SARADC.onetime_sample.onetime_start = val;
}

static inline void adc_ll_onetime_set_channel(adc_ll_num_t unit, adc_channel_t channel)
{
    APB_SARADC.onetime_sample.onetime_channel = ((unit << 3) | channel);
}

static inline void adc_ll_onetime_set_atten(adc_atten_t atten)
{
    APB_SARADC.onetime_sample.onetime_atten = atten;
}

static inline void adc_ll_intr_enable(adc_ll_intr_t mask)
{
    APB_SARADC.int_ena.val |= mask;
}

static inline void adc_ll_intr_disable(adc_ll_intr_t mask)
{
    APB_SARADC.int_ena.val &= ~mask;
}

static inline void adc_ll_intr_clear(adc_ll_intr_t mask)
{
    APB_SARADC.int_clr.val |= mask;
}

static inline bool adc_ll_intr_get_raw(adc_ll_intr_t mask)
{
    return (APB_SARADC.int_raw.val & mask);
}

static inline bool adc_ll_intr_get_status(adc_ll_intr_t mask)
{
    return (APB_SARADC.int_st.val & mask);
}

static inline void adc_ll_onetime_sample_enable(adc_ll_num_t adc_n, bool enable)
{
    if (adc_n == ADC_NUM_1) {
        APB_SARADC.onetime_sample.adc1_onetime_sample = enable;
    } else {
        APB_SARADC.onetime_sample.adc2_onetime_sample = enable;
    }
}

static inline uint32_t adc_ll_adc1_read(void)
{
    //在ESP32H2上，有效数据宽度为12位
    return (APB_SARADC.apb_saradc1_data_status.adc1_data & 0xfff);
}

static inline uint32_t adc_ll_adc2_read(void)
{
    //在ESP32H2上，有效数据宽度为12位
    return (APB_SARADC.apb_saradc2_data_status.adc2_data & 0xfff);
}

#ifdef __cplusplus
}
#endif

