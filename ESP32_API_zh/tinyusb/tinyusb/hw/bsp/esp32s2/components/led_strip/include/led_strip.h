// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"

/**
* @brief LED条类型
*
*/
typedef struct led_strip_s led_strip_t;

/**
* @brief LED条带装置类型
*
*/
typedef void *led_strip_dev_t;

/**
* @brief LED条类型声明
*
*/
struct led_strip_s {
    /**
    * @brief 为特定像素设置RGB
    *
    * @param strip: LED灯带
    * @param index: 要设置的像素索引
    * @param red: 颜色的红色部分
    * @param green: 颜色的绿色部分
    * @param blue: 颜色的蓝色部分
    *
    * @return
    *      -ESP_OK：成功设置特定像素的RGB
    *      -ESP_ERR_INVALID_ARG：由于参数无效，为特定像素设置RGB失败
    *      -ESP_FAIL:为特定像素设置RGB失败，因为发生了其他错误
    */
    esp_err_t (*set_pixel)(led_strip_t *strip, uint32_t index, uint32_t red, uint32_t green, uint32_t blue);

    /**
    * @brief 将内存颜色刷新为LED
    *
    * @param strip: LED灯带
    * @param timeout_ms: 刷新任务的超时值
    *
    * @return
    *      -ESP_OK:刷新成功
    *      -ESP_ERR_TIMEOUT:由于超时，刷新失败
    *      -ESP_FAIL:刷新失败，因为发生了其他错误
    *
    * @note: 在更新内存中的LED颜色后，需要调用此API来刷新要剥离的颜色。
    */
    esp_err_t (*refresh)(led_strip_t *strip, uint32_t timeout_ms);

    /**
    * @brief 透明LED条（关闭所有LED）
    *
    * @param strip: LED灯带
    * @param timeout_ms: 清除任务的超时值
    *
    * @return
    *      -ESP_OK：成功清除LED
    *      -ESP_ERR_TIMEOUT:由于超时，清除LED失败
    *      -ESP_FAIL:由于发生其他错误，清除LED失败
    */
    esp_err_t (*clear)(led_strip_t *strip, uint32_t timeout_ms);

    /**
    * @brief 免费LED灯带资源
    *
    * @param strip: LED灯带
    *
    * @return
    *      -ESP_OK：成功释放资源
    *      -ESP_FAIL:由于发生错误，释放资源失败
    */
    esp_err_t (*del)(led_strip_t *strip);
};

/**
* @brief LED条配置类型
*
*/
typedef struct {
    uint32_t max_leds;   /*!< 单个条带中的最大LED*/
    led_strip_dev_t dev; /*!< LED条形装置（例如RMT通道、PWM通道等）*/
} led_strip_config_t;

/**
 * @brief LED条的默认配置
 *
 */
#define LED_STRIP_DEFAULT_CONFIG(number, dev_hdl) \
    {                                             \
        .max_leds = number,                       \
        .dev = dev_hdl,                           \
    }

/**
* @brief 安装新的ws2812驱动程序（基于RMT外围设备）
*
* @param config: LED条配置
* @return LED条实例或NULL
*/
led_strip_t *led_strip_new_rmt_ws2812(const led_strip_config_t *config);

#ifdef __cplusplus
}
#endif

