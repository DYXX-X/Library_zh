/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "regi2c_ctrl.h"

#include "soc/adc_periph.h"
#include "hal/adc_types.h"
#include "soc/apb_saradc_struct.h"
#include "soc/sens_struct.h"
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
    ADC_LL_CTRL_RTC = 0,    ///<对于ADC1。选择RTC控制器。
    ADC_LL_CTRL_ULP = 1,    ///<对于ADC1和ADC2。选择ULP控制器。
    ADC_LL_CTRL_DIG = 2,    ///<对于ADC1。选择DIG控制器。
    ADC_LL_CTRL_ARB = 3,    ///<对于ADC2。控制器由仲裁器选择。
} adc_ll_controller_t;

/**
 * @brief ADC数字控制器（DMA模式）工作模式。
 *
 * @note  转换模式影响采样频率：SINGLE_UNIT_1：触发测量时，仅对ADC1采样一次。SINGLE_UNIT_2：触发测量时，仅对ADC2采样一次。BOTH_UNIT：触发测量时，ADC1和ADC2同时采样。ALTER_UNIT：触发测量时，ADC1或ADC2交替采样。
 */
typedef enum {
    ADC_LL_DIGI_CONV_ONLY_ADC1  = 0,    // 仅使用ADC1进行转换
    ADC_LL_DIGI_CONV_ONLY_ADC2  = 1,    // 仅使用ADC2进行转换
    ADC_LL_DIGI_CONV_BOTH_UNIT  = 2,    // 同时使用ADC1和ADC2进行转换
    ADC_LL_DIGI_CONV_ALTER_UNIT = 3     // 依次使用ADC1和ADC2进行转换。e、 g.ADC1->ADC2->ADC1->ADC 2。。。。。
} adc_ll_digi_convert_mode_t;

typedef struct {
    union {
        struct {
            uint8_t atten:       2;
            uint8_t channel:     4;
            uint8_t reserved:    2;
        };
        uint8_t val;
    };
} __attribute__((packed)) adc_ll_digi_pattern_table_t;

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif /* _MSC_VER */

/**
 * @brief 分析获得的原始数据是否正确。ADC2默认使用仲裁器。仲裁结果可以通过原始数据中的标志位来判断。
 *
 */
typedef struct {
    union {
        struct {
            uint16_t data:     13;  /*!<ADC实际输出数据信息。分辨率：13位。*/
            uint16_t reserved:  1;  /*!<保留*/
            uint16_t flag:      2;  /*!<ADC数据标志信息。如果（flag==0），则数据有效。如果（标志>0），则数据无效。*/
        };
        uint16_t val;
    };
} adc_ll_rtc_output_data_t;

#ifdef _MSC_VER
#pragma pack(pop)
#endif /* _MSC_VER */


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
    SET_PERI_REG_MASK(RTC_CNTL_ANA_CONF_REG, RTC_CNTL_SAR_I2C_PU_M);
    CLEAR_PERI_REG_MASK(ANA_CONFIG_REG, I2C_SAR_M);
    SET_PERI_REG_MASK(ANA_CONFIG2_REG, ANA_SAR_CFG2_M);

    REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_SAMPLE_CYCLE_ADDR, sample_cycle);
}

/**
 * 设置SAR ADC模块时钟分频因子。SAR ADC时钟与数字控制器时钟分开。
 *
 * @param div 除法系数。
 */
static inline void adc_ll_digi_set_clk_div(uint32_t div)
{
    /* ADC时钟与数字控制器时钟clk分开*/
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
 * @param mode 转换模式选择。
 */
static inline void adc_ll_digi_set_convert_mode(adc_ll_digi_convert_mode_t mode)
{
    if (mode == ADC_LL_DIGI_CONV_ONLY_ADC1) {
        APB_SARADC.ctrl.work_mode = 0;
        APB_SARADC.ctrl.sar_sel = 0;
    } else if (mode == ADC_LL_DIGI_CONV_ONLY_ADC2) {
        APB_SARADC.ctrl.work_mode = 0;
        APB_SARADC.ctrl.sar_sel = 1;
    } else if (mode == ADC_LL_DIGI_CONV_BOTH_UNIT) {
        APB_SARADC.ctrl.work_mode = 1;
    } else if (mode == ADC_LL_DIGI_CONV_ALTER_UNIT) {
        APB_SARADC.ctrl.work_mode = 2;
    }
    APB_SARADC.ctrl.data_sar_sel = 1;
}

/**
 * 设置数字控制器的模式表长度。定义每个SAR ADC的转换规则的模式表。每个表有16个项目，其中存储了信道选择、分辨率和衰减。当转换开始时，控制器从模式表中逐个读取转换规则。对于每个控制器，扫描序列在重复之前具有最多16个不同的规则。
 *
 * @param adc_n ADC单元。
 * @param patt_len 项目范围：1~16。
 */
static inline void adc_ll_digi_set_pattern_table_len(adc_ll_num_t adc_n, uint32_t patt_len)
{
    if (adc_n == ADC_NUM_1) {
        APB_SARADC.ctrl.sar1_patt_len = patt_len - 1;
    } else { // adc_n==adc_NUM_2
        APB_SARADC.ctrl.sar2_patt_len = patt_len - 1;
    }
}

/**
 * 设置数字控制器的模式表。定义每个SAR ADC的转换规则的模式表。每个表有12项，其中存储了信道选择、分辨率和衰减。当转换开始时，控制器从模式表中逐个读取转换规则。对于每个控制器，扫描序列在重复之前具有最多12个不同的规则。
 *
 * @param adc_n ADC单元。
 * @param pattern_index 项目索引。范围：0~11。
 * @param pattern 存储的转换规则。
 */
static inline void adc_ll_digi_set_pattern_table(adc_ll_num_t adc_n, uint32_t pattern_index, adc_digi_pattern_config_t table)
{
    uint32_t tab;
    uint8_t index = pattern_index / 4;
    uint8_t offset = (pattern_index % 4) * 6;
    adc_ll_digi_pattern_table_t pattern = {0};

    pattern.val = (table.atten & 0x3) | ((table.channel & 0xF) << 2);
    if (table.unit == ADC_NUM_1){
        tab = APB_SARADC.sar1_patt_tab[index].sar1_patt_tab;            //读取旧寄存器值
        tab &= (~(0xFC0000 >> offset));                 //清除旧数据
        tab |= ((uint32_t)(pattern.val & 0x3F) << 18) >> offset;   //填写新数据
        APB_SARADC.sar1_patt_tab[index].sar1_patt_tab = tab;            //回写
    } else {
        tab = APB_SARADC.sar2_patt_tab[index].sar2_patt_tab;        //读取旧寄存器值
        tab &= (~(0xFC0000 >> offset));                             //清除旧数据
        tab |= ((uint32_t)(pattern.val & 0x3F) << 18) >> offset;    //填写新数据
        APB_SARADC.sar2_patt_tab[index].sar2_patt_tab = tab;        //回写
    }
}

/**
 * 重置模式表指针，然后在下一次测量中从表头获取测量规则。
 *
 * @param adc_n ADC单元。
 */
static inline void adc_ll_digi_clear_pattern_table(adc_ll_num_t adc_n)
{
    if (adc_n == ADC_NUM_1) {
        APB_SARADC.ctrl.sar1_patt_p_clear = 1;
        APB_SARADC.ctrl.sar1_patt_p_clear = 0;
    } else { // adc_n==adc_NUM_2
        APB_SARADC.ctrl.sar2_patt_p_clear = 1;
        APB_SARADC.ctrl.sar2_patt_p_clear = 0;
    }
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
    APB_SARADC.ctrl2.timer_sel = 1;
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
    APB_SARADC.apb_adc_clkm_conf.clk_sel = 0;
}

/**
 * 重置adc数字控制器滤波器。
 *
 * @param adc_n ADC单元。
 */
static inline void adc_ll_digi_filter_reset(adc_ll_num_t adc_n)
{
    abort();
}

/**
 * 设置adc数字控制器滤波器系数。
 *
 * @param adc_n ADC单元。
 * @param factor 表达式：filter_data=（k-1）/k*last_data+new_data/k。设置值：（2、4、8、16、64）。
 */
static inline void adc_ll_digi_filter_set_factor(adc_ll_num_t adc_n, adc_digi_filter_mode_t factor)
{
    abort();
}

/**
 * 获取adc数字控制器滤波器系数。
 *
 * @param adc_n ADC单元。
 * @param factor 表达式：filter_data=（k-1）/k*last_data+new_data/k。设置值：（2、4、8、16、64）。
 */
static inline void adc_ll_digi_filter_get_factor(adc_ll_num_t adc_n, adc_digi_filter_mode_t *factor)
{
    abort();
}

/**
 * 启用/禁用adc数字控制器滤波器。对ADC数据进行滤波，以获得更高采样率的平滑数据。
 *
 * @note 滤波器将同时过滤每个ADC单元的所有已启用信道数据。
 * @param adc_n ADC单元。
 */
static inline void adc_ll_digi_filter_enable(adc_ll_num_t adc_n, bool enable)
{
    abort();
}

/**
 * 获取adc数字控制器滤波器的滤波数据。每次测量和滤波后的数据由数字控制器更新到DMA。但也可以通过此API手动获取。
 *
 * @note 滤波器将同时过滤每个ADC单元的所有已启用信道数据。
 * @param adc_n ADC单元。
 * @return 筛选的数据。
 */
static inline uint32_t adc_ll_digi_filter_read_data(adc_ll_num_t adc_n)
{
    abort();
}

/**
 * 设置adc数字控制器的监控模式。
 *
 * @note 监视器将同时监视每个ADC单元的所有已启用通道数据。
 * @param adc_n ADC单元。
 * @param is_larger true：如果ADC_OUT>阈值，则生成监视器中断。false：如果ADC_OUT<阈值，则生成监视器中断。
 */
static inline void adc_ll_digi_monitor_set_mode(adc_ll_num_t adc_n, bool is_larger)
{
    abort();
}

/**
 * 设置adc数字控制器的监控阈值。
 *
 * @note 监视器将同时监视每个ADC单元的所有已启用通道数据。
 * @param adc_n ADC单元。
 * @param threshold 监控阈值。
 */
static inline void adc_ll_digi_monitor_set_thres(adc_ll_num_t adc_n, uint32_t threshold)
{
    abort();
}

/**
 * 启用/禁用adc数字控制器的监视器。
 *
 * @note 监视器将同时监视每个ADC单元的所有已启用通道数据。
 * @param adc_n ADC单元。
 */
static inline void adc_ll_digi_monitor_enable(adc_ll_num_t adc_n, bool enable)
{
    abort();
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
    SENS.sar_meas2_mux.sar2_pwdet_cct = cct;
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
    return SENS.sar_meas2_mux.sar2_pwdet_cct;
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
        SENS.sar_peri_clk_gate_conf.saradc_clk_en = 1;
        SENS.sar_power_xpd_sar.force_xpd_sar = 3; //SENS_FORCE_XPD_SAR_PU;
    } else if (manage == ADC_POWER_BY_FSM) {
        SENS.sar_peri_clk_gate_conf.saradc_clk_en = 1;
        SENS.sar_power_xpd_sar.force_xpd_sar = 0; //SENS_FORCE_XPD_SAR_FSM;
    } else if (manage == ADC_POWER_SW_OFF) {
        SENS.sar_power_xpd_sar.force_xpd_sar = 2; //SENS_FORCE_XPD_SAR_PD;
        SENS.sar_peri_clk_gate_conf.saradc_clk_en = 0;
    }
}

/**
 * 设置ADC模块控制器。有五个SAR ADC控制器：两个数字控制器：连续转换模式（DMA）。具有多通道扫描模式的高性能；两个RTC控制器：单转换模式（轮询）。用于在深度睡眠期间进行低功耗工作；另一个专用于功率检测（PWDET/PKDET），仅支持ADC2。
 *
 * @param adc_n ADC单元。
 * @param ctrl ADC控制器。
 */
static inline void adc_ll_set_controller(adc_ll_num_t adc_n, adc_ll_controller_t ctrl)
{
    if (adc_n == ADC_NUM_1) {
        switch (ctrl) {
            case ADC_LL_CTRL_RTC:
                SENS.sar_meas1_mux.sar1_dig_force       = 0;    // 1： 选择数字控制；0：选择RTC控制。
                SENS.sar_meas1_ctrl2.meas1_start_force  = 1;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
                SENS.sar_meas1_ctrl2.sar1_en_pad_force  = 1;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
                break;
            case ADC_LL_CTRL_ULP:
                SENS.sar_meas1_mux.sar1_dig_force       = 0;    // 1： 选择数字控制；0：选择RTC控制。
                SENS.sar_meas1_ctrl2.meas1_start_force  = 0;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
                SENS.sar_meas1_ctrl2.sar1_en_pad_force  = 0;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
                break;
            case ADC_LL_CTRL_DIG:
                SENS.sar_meas1_mux.sar1_dig_force       = 1;    // 1： 选择数字控制；0：选择RTC控制。
                SENS.sar_meas1_ctrl2.meas1_start_force  = 1;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
                SENS.sar_meas1_ctrl2.sar1_en_pad_force  = 1;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
                break;
            default:
                break;
        }
    } else { // adc_n==adc_NUM_2
        //如果ADC2不受ULP控制，则仲裁器将决定使用ADC2的控制器。
        switch (ctrl) {
            case ADC_LL_CTRL_ARB:
                SENS.sar_meas2_ctrl2.meas2_start_force  = 1;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
                SENS.sar_meas2_ctrl2.sar2_en_pad_force  = 1;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
                break;
            case ADC_LL_CTRL_ULP:
                SENS.sar_meas2_ctrl2.meas2_start_force  = 0;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
                SENS.sar_meas2_ctrl2.sar2_en_pad_force  = 0;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
                break;
            default:
                break;
        }
    }
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
    } else {  // 屏蔽仲裁器。
        APB_SARADC.apb_adc_arb_ctrl.adc_arb_grant_force = 1;
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

/**
 * 强制将ADC2切换到处于睡眠模式的RTC控制器。屏蔽仲裁器。在睡眠模式下，仲裁器处于断电模式。需要将控制器切换到RTC以屏蔽仲裁器的控制。醒来后，它需要切换到仲裁器控制。
 *
 * @note 硬件将自动执行此操作。在正常使用中，不需要调用此接口来手动切换控制器。
 * @note 仅支持ADC2。
 */
static inline void adc_ll_enable_sleep_controller(void)
{
    SENS.sar_meas2_mux.sar2_rtc_force = 1;
}

/**
 * 强制开关ADC2在唤醒模式下切换到仲裁器。在睡眠模式下，仲裁器处于断电模式。需要将控制器切换到RTC以屏蔽仲裁器的控制。醒来后，它需要切换到仲裁器控制。
 *
 * @note 硬件将自动执行此操作。在正常使用中，不需要调用此接口来手动切换控制器。
 * @note 仅支持ADC2。
 */
static inline void adc_ll_disable_sleep_controller(void)
{
    SENS.sar_meas2_mux.sar2_rtc_force = 0;
}

/**
 * @brief 设置常用校准配置。应与其他部分共享（PWDET）。
 */
static inline void adc_ll_calibration_init(adc_ll_num_t adc_n)
{
    if (adc_n == ADC_NUM_1) {
        REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_DREF_ADDR, 4);
    } else {
        REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR2_DREF_ADDR, 4);
    }
}

/**
 * 配置ADC校准寄存器。您需要调用``adc_ll_calibration_finish``接口以在校准后继续。
 *
 * @param adc_n ADC索引编号。
 * @param channel 未使用。
 * @param internal_gnd true：从IO端口断开连接，并使用内部GND作为校准电压。false：使用IO外部电压作为校准电压。
 */
static inline void adc_ll_calibration_prepare(adc_ll_num_t adc_n, adc_channel_t channel, bool internal_gnd)
{
    /* 应在写入I2C寄存器之前调用。*/
    SET_PERI_REG_MASK(RTC_CNTL_ANA_CONF_REG, RTC_CNTL_SAR_I2C_PU_M);
    CLEAR_PERI_REG_MASK(ANA_CONFIG_REG, I2C_SAR_M);
    SET_PERI_REG_MASK(ANA_CONFIG2_REG, ANA_SAR_CFG2_M);

    /* 启用/禁用内部连接GND（用于校准）。*/
    if (adc_n == ADC_NUM_1) {
        if (internal_gnd) {
            REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_ENCAL_GND_ADDR, 1);
        } else {
            REGI2C_WRITE_MASK(I2C_SAR_ADC, ADC_SAR1_ENCAL_GND_ADDR, 0);
        }
    } else {    //adc_n==adc_NUM_2
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
    } else {    //adc_n==adc_NUM_2
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

/**
 *  向通道输出ADC内部参考电压，仅适用于ESP32上的ADC2。
 *
 *  此函数将ADCn的内部参考电压路由到ADC2的一个通道。然后，可以手动测量该参考电压以进行校准。
 *
 *  @param[in]  adc ADC单元选择
 *  @param[in]  channel ADC2通道编号
 *  @param[in]  en 启用/禁用参考电压输出
 */
static inline void adc_ll_vref_output(adc_ll_num_t adc, adc_channel_t channel, bool en)
{
    abort();
}

/*---------------------------------------------------------------
                    RTC控制器设置
---------------------------------------------------------------*/
/**
 * ADC SAR时钟分频因子设置。ADC SAR时钟与“RTC_FAST_CLK”分开。
 *
 * @param div 除法系数。
 */
static inline void adc_ll_set_sar_clk_div(adc_ll_num_t adc_n, uint32_t div)
{
    if (adc_n == ADC_NUM_1) {
        HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_reader1_ctrl, sar1_clk_div, div);
    } else { // adc_n==adc_NUM_2
        HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_reader2_ctrl, sar2_clk_div, div);
    }
}

/**
 * 设置RTC控制器的adc输出数据格式。
 *
 * @note ESP32S3 RTC控制器仅支持13位。
 * @prarm adc_n adc单元。
 * @prarm bits输出数据位宽选项。
 */
static inline void adc_ll_rtc_set_output_format(adc_ll_num_t adc_n, adc_bits_width_t bits)
{

}

/**
 * 启用adc通道以开始转换。
 *
 * @note 一次测量只能选择一个通道。
 *
 * @param adc_n ADC单元。
 * @param channel 每个ADCn的ADC通道编号。
 */
static inline void adc_ll_rtc_enable_channel(adc_ll_num_t adc_n, int channel)
{
    if (adc_n == ADC_NUM_1) {
        SENS.sar_meas1_ctrl2.sar1_en_pad = (1 << channel); //仅选择一个频道。
    } else { // adc_n==adc_NUM_2
        SENS.sar_meas2_ctrl2.sar2_en_pad = (1 << channel); //仅选择一个频道。
    }
}

/**
 * 禁用adc通道以开始转换。
 *
 * @note 一次测量只能选择一个通道。
 *
 * @param adc_n ADC单元。
 * @param channel 每个ADCn的ADC通道编号。
 */
static inline void adc_ll_rtc_disable_channel(adc_ll_num_t adc_n)
{
    if (adc_n == ADC_NUM_1) {
        SENS.sar_meas1_ctrl2.sar1_en_pad = 0; //仅选择一个频道。
    } else { // adc_n==adc_NUM_2
        SENS.sar_meas2_ctrl2.sar2_en_pad = 0; //仅选择一个频道。
    }
}

/**
 * 通过RTC控制器的软件启动一次转换。
 *
 * @note 等待ADC1的转换空闲可能是块。
 *
 * @param adc_n ADC单元。
 * @param channel 每个ADCn的ADC通道编号。
 */
static inline void adc_ll_rtc_start_convert(adc_ll_num_t adc_n, int channel)
{
    if (adc_n == ADC_NUM_1) {
        while (HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_slave_addr1, meas_status) != 0) {}
        SENS.sar_meas1_ctrl2.meas1_start_sar = 0;
        SENS.sar_meas1_ctrl2.meas1_start_sar = 1;
    } else { // adc_n==adc_NUM_2
        SENS.sar_meas2_ctrl2.meas2_start_sar = 0; //启动力0
        SENS.sar_meas2_ctrl2.meas2_start_sar = 1; //启动力1
    }
}

/**
 * 检查RTC控制器的每个ADCn的转换完成标志。
 *
 * @param adc_n ADC单元。
 * @return
 *      -true：转换过程已完成。
 *      -false：转换过程未完成。
 */
static inline bool adc_ll_rtc_convert_is_done(adc_ll_num_t adc_n)
{
    bool ret = true;
    if (adc_n == ADC_NUM_1) {
        ret = (bool)SENS.sar_meas1_ctrl2.meas1_done_sar;
    } else { // adc_n==adc_NUM_2
        ret = (bool)SENS.sar_meas2_ctrl2.meas2_done_sar;
    }
    return ret;
}

/**
 * 获取RTC控制器的每个ADCn的转换值。
 *
 * @param adc_n ADC单元。
 * @return
 *      -转换值。
 */
static inline int adc_ll_rtc_get_convert_value(adc_ll_num_t adc_n)
{
    int ret_val = 0;
    if (adc_n == ADC_NUM_1) {
        ret_val = HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_meas1_ctrl2, meas1_data_sar);
    } else { // adc_n==adc_NUM_2
        ret_val = HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_meas2_ctrl2, meas2_data_sar);
    }
    return ret_val;
}

/**
 * ADC模块RTC输出数据是否反转。
 *
 * @param adc_n ADC单元。
 * @param inv_en 数据是否反转。
 */
static inline void adc_ll_rtc_output_invert(adc_ll_num_t adc_n, bool inv_en)
{
    if (adc_n == ADC_NUM_1) {
        SENS.sar_reader1_ctrl.sar1_data_inv = inv_en;   // 启用/禁用ADC数据反转
    } else { // adc_n==adc_NUM_2
        SENS.sar_reader2_ctrl.sar2_data_inv = inv_en;  // 启用/禁用ADC数据反转
    }
}

/**
 * 启用RTC控制器的ADCn转换完成中断。
 *
 * @param adc_n ADC单元。
 */
static inline void adc_ll_rtc_intr_enable(adc_ll_num_t adc_n)
{
    if (adc_n == ADC_NUM_1) {
        SENS.sar_reader1_ctrl.sar1_int_en = 1;
        RTCCNTL.int_ena.rtc_saradc1 = 1;
    } else { // adc_n==adc_NUM_2
        SENS.sar_reader2_ctrl.sar2_int_en = 1;
        RTCCNTL.int_ena.rtc_saradc2 = 1;
    }
}

/**
 * 禁用RTC控制器的ADCn转换完成中断。
 *
 * @param adc_n ADC单元。
 */
static inline void adc_ll_rtc_intr_disable(adc_ll_num_t adc_n)
{
    if (adc_n == ADC_NUM_1) {
        SENS.sar_reader1_ctrl.sar1_int_en = 0;
        RTCCNTL.int_ena.rtc_saradc1 = 0;
    } else { // adc_n==adc_NUM_2
        SENS.sar_reader2_ctrl.sar2_int_en = 0;
        RTCCNTL.int_ena.rtc_saradc2 = 0;
    }
}

/**
 * 重置RTC控制器FSM。
 */
static inline void adc_ll_rtc_reset(void)
{
    SENS.sar_peri_reset_conf.saradc_reset = 1;
    SENS.sar_peri_reset_conf.saradc_reset = 0;
}

/**
 * 设置转换完成并等待仲裁器稳定所需的周期数。
 *
 * @note 只有ADC2具有仲裁器功能。
 * @param cycle 范围：[0,4]。
 */
static inline void adc_ll_rtc_set_arbiter_stable_cycle(uint32_t cycle)
{
    SENS.sar_reader2_ctrl.sar2_wait_arb_cycle = cycle;
}

/**
 * 分析获得的原始数据是否正确。ADC2可以使用仲裁器。仲裁结果可以通过原始数据中的标志位来判断。
 *
 * @param adc_n ADC单元。
 * @param raw_data ADC原始数据输入（转换值）。
 * @return
 *      -0：数据使用正确。
 *      -1:数据无效。仲裁器未启用当前控制器。
 *      -2:数据无效。当前控制器进程被更高优先级的控制器中断。
 *      --1：数据错误。
 */
static inline adc_ll_rtc_raw_data_t adc_ll_rtc_analysis_raw_data(adc_ll_num_t adc_n, uint16_t raw_data)
{
    /* ADC1不需要检查数据*/
    if (adc_n == ADC_NUM_1) {
        return ADC_RTC_DATA_OK;
    }
    adc_ll_rtc_output_data_t *temp = (adc_ll_rtc_output_data_t *)&raw_data;
    if (temp->flag == 0) {
        return ADC_RTC_DATA_OK;
    } else if (temp->flag == 1) {
        return ADC_RTC_CTRL_UNSELECTED;
    } else if (temp->flag == 2) {
        return ADC_RTC_CTRL_BREAK;
    } else {
        return ADC_RTC_DATA_FAIL;
    }
}

/**
 * 设置ADCn上特定信道的衰减。
 *
 * @note 对于任何给定的通道，必须在第一次转换之前调用此函数。
 *
 * 默认ADC满量程电压为1.1V。要读取更高的电压（高达引脚最大电压，通常为3.3V），需要为该ADC通道设置>0dB的信号衰减。
 *
 * 当VDD_A为3.3V时：
 *
 * -0dB衰减（ADC_ATTEN_DB_0）给出满量程电压1.1V
 * -2.5dB衰减（ADC_ATTEN_DB_2O_5）给出满量程电压1.5V
 * -6dB衰减（ADC_ATTEN_DB_6）给出满量程电压2.2V
 * -11dB衰减（ADC_ATTEN_DB_11）给出全刻度电压3.9V（见下文注释）
 *
 * @note 满刻度电压是对应于最大读数的电压（取决于ADC1配置的位宽，该值为：12位为4095，11位为2047，10位为1023，9位为511）
 *
 * @note 在11dB衰减时，最大电压受VDD_A限制，而不是满量程电压。
 *
 * 由于ADC特性，在以下近似电压范围内可获得最准确的结果：
 *
 * -0dB衰减（ADC_ATTEN_DB_0）介于100和950mV之间
 * -100和1250mV之间的2.5dB衰减（ADC_ATTEN_DB_2O_5）
 * -150至1750mV之间的6dB衰减（ADC_ATTEN_DB_6）
 * -150至2450mV之间的11dB衰减（ADC_ATTEN_DB_11）
 *
 * 为了获得最大精度，请使用ADC校准API并在这些推荐范围内测量电压。
 *
 * @param adc_n ADC单元。
 * @param channel ADCn信道号。
 * @param atten 衰减选项。
 */
static inline void adc_ll_set_atten(adc_ll_num_t adc_n, adc_channel_t channel, adc_atten_t atten)
{
    if (adc_n == ADC_NUM_1) {
        SENS.sar_atten1 = ( SENS.sar_atten1 & ~(0x3 << (channel * 2)) ) | ((atten & 0x3) << (channel * 2));
    } else { // adc_n==adc_NUM_2
        SENS.sar_atten2 = ( SENS.sar_atten2 & ~(0x3 << (channel * 2)) ) | ((atten & 0x3) << (channel * 2));
    }
}

/**
 * 获取ADCn上特定信道的衰减。
 *
 * @param adc_n ADC单元。
 * @param channel ADCn信道号。
 * @return atten衰减选项。
 */
static inline adc_atten_t adc_ll_get_atten(adc_ll_num_t adc_n, adc_channel_t channel)
{
    if (adc_n == ADC_NUM_1) {
        return (adc_atten_t)((SENS.sar_atten1 >> (channel * 2)) & 0x3);
    } else {
        return (adc_atten_t)((SENS.sar_atten2 >> (channel * 2)) & 0x3);
    }
}

static inline uint32_t adc_ll_adc1_read(void)
{
    //在ESP32S3上，有效数据宽度为12位
    return (APB_SARADC.apb_saradc1_data_status.adc1_data & 0xfff);
}

static inline uint32_t adc_ll_adc2_read(void)
{
    //在ESP32S3上，有效数据宽度为12位
    return (APB_SARADC.apb_saradc2_data_status.adc2_data & 0xfff);
}

#ifdef __cplusplus
}
#endif

