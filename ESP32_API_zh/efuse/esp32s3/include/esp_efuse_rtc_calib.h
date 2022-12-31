/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#include <esp_types.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

//这是在efuse中烧毁的ADC校准值版本
#define ESP_EFUSE_ADC_CALIB_VER     1

/**
 * @brief 获取RTC校准有效版本
 *
 * @return 存储efuse的版本
 */
int esp_efuse_rtc_calib_get_ver(void);

/**
 * @brief 在efuse中获取相应衰减的init代码。
 *
 * @param version       存储efuse的版本
 * @param adc_unit      ADC单元
 * @param atten         初始化代码的衰减
 * @return efuse中存储的init代码
 */
uint32_t esp_efuse_rtc_calib_get_init_code(int version, uint32_t adc_unit, int atten);

/**
 * @brief 获取efuse中存储的校准数字和相应的电压。
 *
 * @param version       存储efuse的版本
 * @param adc_unit      ADC单元
 * @param atten         要使用的衰减
 * @param out_digi      数字输出缓冲区
 * @param out_vol_mv    电压输出，mV
 * @return
 *      -ESP_ERR_INVALID_ARG：如果efuse版本或衰减无效
 *      -ESP_OK：如果成功
 */
esp_err_t esp_efuse_rtc_calib_get_cal_voltage(int version, uint32_t adc_unit, int atten, uint32_t* out_digi, uint32_t* out_vol_mv);

/**
 * @brief 获取efuse中存储的温度传感器校准编号delta_T。
 *
 * @param version 存储efuse的版本
 *
 * @return efuse中温度传感器校准编号的规格。
 */
float esp_efuse_rtc_calib_get_cal_temp(int version);

#ifdef __cplusplus
}
#endif

