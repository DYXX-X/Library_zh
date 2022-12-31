/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TSENS_DAC_L0 = 0, /*!< 偏移量=-2，测量范围：50℃~125℃，误差<3℃。*/
    TSENS_DAC_L1,     /*!< 偏移量=-1，测量范围：20℃~100℃，误差<2℃。*/
    TSENS_DAC_L2,     /*!< 偏移=0，测量范围：-10℃~80℃，误差<1℃。*/
    TSENS_DAC_L3,     /*!< 偏移量=1，测量范围：-30℃~50℃，误差<2℃。*/
    TSENS_DAC_L4,     /*!< 偏移量=2，测量范围：-40℃~20℃，误差<3℃。*/
    TSENS_DAC_MAX,
    TSENS_DAC_DEFAULT = TSENS_DAC_L2,
} temp_sensor_dac_offset_t;

/**
 * @brief 温度传感器读数配置
 */
typedef struct {
    temp_sensor_dac_offset_t dac_offset;    /*!< 温度测量范围配置有内置温度偏移DAC。*/
    uint8_t clk_div;                        /*!< 默认值：6*/
} temp_sensor_config_t;

#define TSENS_CONFIG_DEFAULT() {.dac_offset = TSENS_DAC_L2, \
                                .clk_div = 6}

/**
 * @brief 设置温度传感器的参数。
 * @param tsens
 * @return
 *     -ESP_OK成功
 */
esp_err_t temp_sensor_set_config(temp_sensor_config_t tsens);

/**
 * @brief 获取温度传感器参数。
 * @param tsens
 * @return
 *     -ESP_OK成功
 */
esp_err_t temp_sensor_get_config(temp_sensor_config_t *tsens);

/**
 * @brief 开始温度传感器测量。
 * @return
 *     -ESP_OK成功
 *     -如果温度传感器已启动，则为ESP_ERR_INVALID_STATE。
 */
esp_err_t temp_sensor_start(void);

/**
 * @brief 停止温度传感器测量。
 * @return
 *     -ESP_OK成功
 *     -如果温度传感器已停止，则为ESP_ERR_INVALID_STATE。
 */
esp_err_t temp_sensor_stop(void);

/**
 * @brief 读取温度传感器原始数据。
 * @param tsens_out 指向原始数据的指针，范围：0~255
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG`tsens_out`为空
 *     -ESP_ERR_INVALID_STATE温度传感器无法启动
 */
esp_err_t temp_sensor_read_raw(uint32_t *tsens_out);

/**
 * @brief 读取转换为摄氏度的温度传感器数据。
 * @note  不应从中断调用。
 * @param celsius 测量输出值。
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG ARG为空。
 *     -ESP_ERR_INVALID_STATE环境温度超出范围。
 */
esp_err_t temp_sensor_read_celsius(float *celsius);

#ifdef __cplusplus
}
#endif

