/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "soc/adc_periph.h"
#include "hal/adc_types.h"
#include "soc/rtc_io_struct.h"
#include "soc/sens_struct.h"
#include "soc/syscon_struct.h"
#include "soc/rtc_cntl_struct.h"
#include <stdbool.h>
#include "hal/misc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ADC_NUM_1 = 0,          /*!< SAR ADC 1 */
    ADC_NUM_2 = 1,          /*!< SAR ADC 2 */
    ADC_NUM_MAX,
} adc_ll_num_t;

typedef enum {
    ADC_POWER_BY_FSM,   /*!< ADC XPD由FSM控制。用于轮询模式*/
    ADC_POWER_SW_ON,    /*!< ADC XPD由SW控制。开机。用于DMA模式*/
    ADC_POWER_SW_OFF,   /*!< ADC XPD由SW控制。关闭电源。*/
    ADC_POWER_MAX,      /*!< 用于参数检查。*/
} adc_ll_power_t;

typedef enum {
    ADC_RTC_DATA_OK = 0,
} adc_ll_rtc_raw_data_t;

typedef enum {
    ADC_LL_CTRL_RTC   = 0,    ///<对于ADC1和ADC2。选择RTC控制器。
    ADC_LL_CTRL_ULP   = 1,    ///<对于ADC1和ADC2。选择ULP控制器。
    ADC_LL_CTRL_DIG   = 2,    ///<对于ADC1和ADC2。选择DIG控制器。
    ADC_LL_CTRL_PWDET = 3,    ///<对于ADC2。选择PWDET控制器。
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

//需要bit_width的单元测试
typedef struct {
    union {
        struct {
            uint8_t atten:       2;
            uint8_t bit_width:   2;  //ADC分辨率。0:9位；1： 10位；2： 11位；3： 12位
            uint8_t channel:     4;
        };
        uint8_t val;
    };
} __attribute__((packed)) adc_ll_digi_pattern_table_t;

typedef enum {
    ADC_HALL_CTRL_ULP = 0x0,/*!< ULP控制的霍尔传感器*/
    ADC_HALL_CTRL_RTC = 0x1 /*!< 由RTC控制的霍尔传感器*/
} adc_ll_hall_controller_t ;

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
    HAL_FORCE_MODIFY_U32_REG_FIELD(SYSCON.saradc_fsm, rstb_wait, rst_wait);
    // 内部FSM启动等待时间
    HAL_FORCE_MODIFY_U32_REG_FIELD(SYSCON.saradc_fsm, start_wait, start_wait);
    // 内部FSM待机等待时间
    HAL_FORCE_MODIFY_U32_REG_FIELD(SYSCON.saradc_fsm, standby_wait, standby_wait);
}

/**
 * 设置adc采样周期。
 *
 * @note 通常，请使用默认值。
 * @param sample_cycle ADC采样周期数。范围：1~7。
 */
static inline void adc_ll_set_sample_cycle(uint32_t sample_cycle)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(SYSCON.saradc_fsm, sample_cycle, sample_cycle);
}

/**
 * ADC模块时钟分频因子设置。ADC时钟与APB时钟分开。
 *
 * @param div 除法系数。
 */
static inline void adc_ll_digi_set_clk_div(uint32_t div)
{
    /* 从APB clk划分的ADC时钟，*/
    HAL_FORCE_MODIFY_U32_REG_FIELD(SYSCON.saradc_ctrl, sar_clk_div, div);
}

/**
 * 设置数字控制器的adc最大转换数。如果ADC转换次数等于最大值，则停止转换。
 *
 * @param meas_num 最大转换数。范围：0~255。
 */
static inline void adc_ll_digi_set_convert_limit_num(uint32_t meas_num)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(SYSCON.saradc_ctrl2, max_meas_num, meas_num);
}

/**
 * 启用数字控制器的最大转换数检测。如果ADC转换次数等于最大值，则停止转换。
 */
static inline void adc_ll_digi_convert_limit_enable(void)
{
    SYSCON.saradc_ctrl2.meas_num_limit = 1;
}

/**
 * 禁用数字控制器的最大转换数检测。如果ADC转换次数等于最大值，则停止转换。
 */
static inline void adc_ll_digi_convert_limit_disable(void)
{
    SYSCON.saradc_ctrl2.meas_num_limit = 0;
}

/**
 * 设置数字控制器的adc转换模式。
 *
 * @note ESP32仅支持ADC1单模式。
 * @note 对于“data_sar_sel”寄存器：1:[15]单元，[14:11]通道，[10:0]数据，最大11位宽度。仅在“ADC__LL_DIGI_CONV_BOTH_UNIT”或“ADC_LL_DIGI_CONV_ALTER_UNIT”模式下工作。0:[15:12]信道，[11:0]数据，最大12位宽度。仅在“ADC__LL_DIGI_CONV_Only_ADC1”或“ADC_LL_DIGI_CONV_Only_ACD2”模式下工作
 *
 * @param mode 转换模式选择。
 */
static inline void adc_ll_digi_set_convert_mode(adc_ll_digi_convert_mode_t mode)
{
    if (mode == ADC_LL_DIGI_CONV_ONLY_ADC1) {
        SYSCON.saradc_ctrl.work_mode = 0;
        SYSCON.saradc_ctrl.sar_sel = 0;
        SYSCON.saradc_ctrl.data_sar_sel = 0;
    } else if (mode == ADC_LL_DIGI_CONV_ONLY_ADC2) {
        SYSCON.saradc_ctrl.work_mode = 0;
        SYSCON.saradc_ctrl.sar_sel = 1;
        SYSCON.saradc_ctrl.data_sar_sel = 0;
    } else if (mode == ADC_LL_DIGI_CONV_BOTH_UNIT) {
        SYSCON.saradc_ctrl.work_mode = 1;
        SYSCON.saradc_ctrl.data_sar_sel = 1;
    } else if (mode == ADC_LL_DIGI_CONV_ALTER_UNIT) {
        SYSCON.saradc_ctrl.work_mode = 2;
        SYSCON.saradc_ctrl.data_sar_sel = 1;
    }
}

/**
 * ADC模块数字输出数据是否反转。
 *
 * @prarm adc_n adc单元。
 */
static inline void adc_ll_digi_output_invert(adc_ll_num_t adc_n, bool inv_en)
{
    if (adc_n == ADC_NUM_1) {
        SYSCON.saradc_ctrl2.sar1_inv = inv_en;   // 启用/禁用ADC数据反转
    } else { // adc_n==adc_NUM_2
        SYSCON.saradc_ctrl2.sar2_inv = inv_en;  // 启用/禁用ADC数据反转
    }
}

/**
 * 为数字控制器设置I2S DMA数据源。
 *
 * @param src 1： I2S输入数据来自SAR ADC（用于DMA）0:I2S输入信号来自GPIO矩阵
 */
static inline void adc_ll_digi_set_data_source(bool src)
{
    SYSCON.saradc_ctrl.data_to_i2s = src;
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
        SYSCON.saradc_ctrl.sar1_patt_len = patt_len - 1;
    } else { // adc_n==adc_NUM_2
        SYSCON.saradc_ctrl.sar2_patt_len = patt_len - 1;
    }
}

/**
 * 设置数字控制器的模式表长度。定义每个SAR ADC的转换规则的模式表。每个表有16个项目，其中存储了信道选择、分辨率和衰减。当转换开始时，控制器从模式表中逐个读取转换规则。对于每个控制器，扫描序列在重复之前具有最多16个不同的规则。
 *
 * @param adc_n ADC单元。
 * @param pattern_index 项目索引。范围：0~15。
 * @param pattern 存储的转换规则，请参见``adc_digi_pattern_table_t``。
 */
static inline void adc_ll_digi_set_pattern_table(adc_ll_num_t adc_n, uint32_t pattern_index, adc_digi_pattern_config_t table)
{
    uint32_t tab;
    uint8_t index = pattern_index / 4;
    uint8_t offset = (pattern_index % 4) * 8;
    adc_ll_digi_pattern_table_t pattern = {0};
    uint8_t bit_width;

    switch (table.bit_width) {
        case 9:
            bit_width = 0x0;
            break;
        case 10:
            bit_width = 0x1;
            break;
        case 11:
            bit_width = 0x2;
            break;
        case 12:
            bit_width = 0x3;
            break;
        default:
            bit_width = 0x3;
    }
    pattern.val = (table.atten & 0x3) | ((bit_width) << 2) | ((table.channel & 0xF) << 4);

    if (table.unit == ADC_NUM_1) {
        tab = SYSCON.saradc_sar1_patt_tab[index];   // 读取旧寄存器值
        tab &= (~(0xFF000000 >> offset));           // 清除旧数据
        tab |= ((uint32_t)pattern.val << 24) >> offset; // 填写新数据
        SYSCON.saradc_sar1_patt_tab[index] = tab;   // 回写
    } else { // adc_n==adc_NUM_2
        tab = SYSCON.saradc_sar2_patt_tab[index];   // 读取旧寄存器值
        tab &= (~(0xFF000000 >> offset));           // 清除旧数据
        tab |= ((uint32_t)pattern.val << 24) >> offset; // 填写新数据
        SYSCON.saradc_sar2_patt_tab[index] = tab;   // 回写
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
        SYSCON.saradc_ctrl.sar1_patt_p_clear = 1;
        SYSCON.saradc_ctrl.sar1_patt_p_clear = 0;
    } else { // adc_n==adc_NUM_2
        SYSCON.saradc_ctrl.sar2_patt_p_clear = 1;
        SYSCON.saradc_ctrl.sar2_patt_p_clear = 0;
    }
}

/**
 * 禁用ADC数字控制器的时钟。
 * @note 不用于esp32
 */
static inline void adc_ll_digi_controller_clk_disable(void)
{
    //保留此处以获得兼容性
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
    SENS.sar_start_force.sar2_pwdet_cct = cct;
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
    return SENS.sar_start_force.sar2_pwdet_cct;
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
        HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_read_ctrl, sar1_clk_div, div);
    } else { // adc_n==adc_NUM_2
        HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_read_ctrl2, sar2_clk_div, div);
    }
}

/**
 * 设置RTC控制器的adc输出数据格式。
 *
 * @param adc_n ADC单元。
 * @param bits 输出数据位宽度选项，请参见``adc_bits_width_t``。
 */
static inline void adc_ll_rtc_set_output_format(adc_ll_num_t adc_n, adc_bits_width_t bits)
{
    if (adc_n == ADC_NUM_1) {
        SENS.sar_start_force.sar1_bit_width = bits;
        SENS.sar_read_ctrl.sar1_sample_bit = bits;
    } else { // adc_n==adc_NUM_2
        SENS.sar_start_force.sar2_bit_width = bits;
        SENS.sar_read_ctrl2.sar2_sample_bit = bits;
    }
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
        SENS.sar_meas_start1.sar1_en_pad = (1 << channel); //仅选择一个频道。
    } else { // adc_n==adc_NUM_2
        SENS.sar_meas_start2.sar2_en_pad = (1 << channel); //仅选择一个频道。
    }
}

/**
 * 禁用adc通道以开始转换。
 *
 * @note 一次测量只能选择一个通道。
 *
 * @param adc_n ADC单元。
 */
static inline void adc_ll_rtc_disable_channel(adc_ll_num_t adc_n)
{
    if (adc_n == ADC_NUM_1) {
        SENS.sar_meas_start1.sar1_en_pad = 0; //仅选择一个频道。
    } else { // adc_n==adc_NUM_2
        SENS.sar_meas_start2.sar2_en_pad = 0; //仅选择一个频道。
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
        SENS.sar_meas_start1.meas1_start_sar = 0;
        SENS.sar_meas_start1.meas1_start_sar = 1;
    } else { // adc_n==adc_NUM_2
        SENS.sar_meas_start2.meas2_start_sar = 0; //启动力0
        SENS.sar_meas_start2.meas2_start_sar = 1; //启动力1
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
        ret = (bool)SENS.sar_meas_start1.meas1_done_sar;
    } else { // adc_n==adc_NUM_2
        ret = (bool)SENS.sar_meas_start2.meas2_done_sar;
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
        ret_val = HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_meas_start1, meas1_data_sar);
    } else { // adc_n==adc_NUM_2
        ret_val = HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_meas_start2, meas2_data_sar);
    }
    return ret_val;
}

/**
 * ADC模块RTC输出数据是否反转。
 *
 * @param adc_n ADC单元。
 */
static inline void adc_ll_rtc_output_invert(adc_ll_num_t adc_n, bool inv_en)
{
    if (adc_n == ADC_NUM_1) {
        SENS.sar_read_ctrl.sar1_data_inv = inv_en;   // 启用/禁用ADC数据反转
    } else { // adc_n==adc_NUM_2
        SENS.sar_read_ctrl2.sar2_data_inv = inv_en;  // 启用/禁用ADC数据反转
    }
}

/**
 * 分析获得的原始数据是否正确。
 *
 * @param adc_n ADC单元。
 * @param raw_data ADC原始数据输入（转换值）。
 * @return
 *      -0：数据使用正确。
 */
static inline adc_ll_rtc_raw_data_t adc_ll_rtc_analysis_raw_data(adc_ll_num_t adc_n, uint16_t raw_data)
{
    /* ADC1不需要检查数据*/
    return ADC_RTC_DATA_OK;
}

/**
 * 设置ADCn上特定信道的衰减。
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
        SENS.sar_meas_wait2.force_xpd_sar = SENS_FORCE_XPD_SAR_PU;
    } else if (manage == ADC_POWER_BY_FSM) {
        SENS.sar_meas_wait2.force_xpd_sar = SENS_FORCE_XPD_SAR_FSM;
    } else if (manage == ADC_POWER_SW_OFF) {
        SENS.sar_meas_wait2.force_xpd_sar = SENS_FORCE_XPD_SAR_PD;
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
        switch ( ctrl ) {
        case ADC_LL_CTRL_RTC:
            SENS.sar_read_ctrl.sar1_dig_force       = 0;    // 1： 选择数字控制；0：选择RTC控制。
            SENS.sar_meas_start1.meas1_start_force  = 1;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
            SENS.sar_meas_start1.sar1_en_pad_force  = 1;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
            SENS.sar_touch_ctrl1.xpd_hall_force     = 1;    // 1： SW控制HALL电源；0:ULP FSM控制HALL电源。
            SENS.sar_touch_ctrl1.hall_phase_force   = 1;    // 1： SW控制HALL阶段；0:ULP FSM控制HALL阶段。
            break;
        case ADC_LL_CTRL_ULP:
            SENS.sar_read_ctrl.sar1_dig_force       = 0;    // 1： 选择数字控制；0：选择RTC控制。
            SENS.sar_meas_start1.meas1_start_force  = 0;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
            SENS.sar_meas_start1.sar1_en_pad_force  = 0;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
            SENS.sar_touch_ctrl1.xpd_hall_force     = 0;    // 1： SW控制HALL电源；0:ULP FSM控制HALL电源。
            SENS.sar_touch_ctrl1.hall_phase_force   = 0;    // 1： SW控制HALL阶段；0:ULP FSM控制HALL阶段。
            break;
        case ADC_LL_CTRL_DIG:
            SENS.sar_read_ctrl.sar1_dig_force       = 1;    // 1： 选择数字控制；0：选择RTC控制。
            SENS.sar_meas_start1.meas1_start_force  = 1;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
            SENS.sar_meas_start1.sar1_en_pad_force  = 1;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
            SENS.sar_touch_ctrl1.xpd_hall_force     = 1;    // 1： SW控制HALL电源；0:ULP FSM控制HALL电源。
            SENS.sar_touch_ctrl1.hall_phase_force   = 1;    // 1： SW控制HALL阶段；0:ULP FSM控制HALL阶段。
            break;
        default:
            break;
        }
    } else { // adc_n==adc_NUM_2
        switch ( ctrl ) {
        case ADC_LL_CTRL_RTC:
            SENS.sar_meas_start2.meas2_start_force  = 1;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
            SENS.sar_meas_start2.sar2_en_pad_force  = 1;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
            SENS.sar_read_ctrl2.sar2_dig_force      = 0;    // 1： 选择数字控制；0：选择RTC控制。
            SENS.sar_read_ctrl2.sar2_pwdet_force    = 0;    // 1： 选择功率检测控制；0：选择RTC控制。
            SYSCON.saradc_ctrl.sar2_mux             = 1;    // 1： 选择数字控制；0：选择电源检测控制。
            break;
        case ADC_LL_CTRL_ULP:
            SENS.sar_meas_start2.meas2_start_force  = 0;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
            SENS.sar_meas_start2.sar2_en_pad_force  = 0;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
            SENS.sar_read_ctrl2.sar2_dig_force      = 0;    // 1： 选择数字控制；0：选择RTC控制。
            SENS.sar_read_ctrl2.sar2_pwdet_force    = 0;    // 1： 选择功率检测控制；0：选择RTC控制。
            SYSCON.saradc_ctrl.sar2_mux             = 1;    // 1： 选择数字控制；0：选择电源检测控制。
            break;
        case ADC_LL_CTRL_DIG:
            SENS.sar_meas_start2.meas2_start_force  = 1;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
            SENS.sar_meas_start2.sar2_en_pad_force  = 1;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
            SENS.sar_read_ctrl2.sar2_dig_force      = 1;    // 1： 选择数字控制；0：选择RTC控制。
            SENS.sar_read_ctrl2.sar2_pwdet_force    = 0;    // 1： 选择功率检测控制；0：选择RTC控制。
            SYSCON.saradc_ctrl.sar2_mux             = 1;    // 1： 选择数字控制；0：选择电源检测控制。
            break;
        case ADC_LL_CTRL_PWDET:   // 当前仅由Wi-Fi使用
            SENS.sar_meas_start2.meas2_start_force  = 1;    // 1： SW控制RTC ADC启动；0:ULP控制RTC ADC启动。
            SENS.sar_meas_start2.sar2_en_pad_force  = 1;    // 1： SW控制RTC ADC位图；0:ULP控制RTC ADC位图；
            SENS.sar_read_ctrl2.sar2_dig_force      = 0;    // 1： 选择数字控制；0：选择RTC控制。
            SENS.sar_read_ctrl2.sar2_pwdet_force    = 1;    // 1： 选择功率检测控制；0：选择RTC控制。
            SYSCON.saradc_ctrl.sar2_mux             = 0;    // 1： 选择数字控制；0：选择电源检测控制。
            break;
        default:
            break;
        }
    }
}

/**
 * 如果不使用ADC AMP模块进行节能，请关闭它。
 */
static inline void adc_ll_amp_disable(void)
{
    //通道在转换函数中设置
    SENS.sar_meas_wait2.force_xpd_amp = SENS_FORCE_XPD_AMP_PD;
    //禁用FSM，它仅由LNA使用。
    SENS.sar_meas_ctrl.amp_rst_fb_fsm = 0;
    SENS.sar_meas_ctrl.amp_short_ref_fsm = 0;
    SENS.sar_meas_ctrl.amp_short_ref_gnd_fsm = 0;
    HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_meas_wait1, sar_amp_wait1, 1);
    HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_meas_wait1, sar_amp_wait2, 1);
    HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_meas_wait2, sar_amp_wait3, 1);
}

/*---------------------------------------------------------------
                    霍尔传感器设置
---------------------------------------------------------------*/

/**
 * 启用霍尔传感器。
 */
static inline void adc_ll_hall_enable(void)
{
    RTCIO.hall_sens.xpd_hall = 1;
}

/**
 * 禁用霍尔传感器。
 */
static inline void adc_ll_hall_disable(void)
{
    RTCIO.hall_sens.xpd_hall = 0;
}

/**
 * 霍尔传感器反相。
 */
static inline void adc_ll_hall_phase_enable(void)
{
    RTCIO.hall_sens.hall_phase = 1;
}

/**
 * 不要使霍尔传感器反相。
 */
static inline void adc_ll_hall_phase_disable(void)
{
    RTCIO.hall_sens.hall_phase = 0;
}

/**
 * 设置霍尔传感器控制器。
 *
 * @param hall_ctrl 霍尔控制器。
 */
static inline void adc_ll_set_hall_controller(adc_ll_hall_controller_t hall_ctrl)
{
    SENS.sar_touch_ctrl1.xpd_hall_force = hall_ctrl;    // 1： SW控制HALL电源；0:ULP FSM控制HALL电源。
    SENS.sar_touch_ctrl1.hall_phase_force = hall_ctrl;  // 1： SW控制HALL阶段；0:ULP FSM控制HALL阶段。
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
    if (adc != ADC_NUM_2) return;

    if (en) {
        RTCCNTL.bias_conf.dbg_atten = 0;     //在睡眠模式外检查DBG效果
        //设置数据测试（MUX_SEL:0->RTC；1->vdd_sar2）
        RTCCNTL.test_mux.dtest_rtc = 1;      //配置测试多路复用器以将v_ref路由到ADC2信道
        //设置
        RTCCNTL.test_mux.ent_rtc = 1;
        //设置sar2_en_test
        SENS.sar_start_force.sar2_en_test = 1;
        //设置sar2 en力
        SENS.sar_meas_start2.sar2_en_pad_force = 1;      //由软件控制的填充位图
        //为通道7、8、9设置en_pad（位0x380）
        SENS.sar_meas_start2.sar2_en_pad = 1 << channel;
    } else {
        RTCCNTL.test_mux.dtest_rtc = 0;      //配置测试多路复用器以将v_ref路由到ADC2信道
        //设置
        RTCCNTL.test_mux.ent_rtc = 0;
        //设置sar2_en_test
        SENS.sar_start_force.sar2_en_test = 0;
        //设置sar2 en力
        SENS.sar_meas_start2.sar2_en_pad_force = 0;      //由软件控制的填充位图
        //为通道7、8、9设置en_pad（位0x380）
        SENS.sar_meas_start2.sar2_en_pad = 0;
    }
}

#ifdef __cplusplus
}
#endif

