/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_attr.h"
#include "soc/soc_caps.h"

#if SOC_DEDICATED_GPIO_SUPPORTED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 专用GPIO捆绑包类型
 */
typedef struct dedic_gpio_bundle_t *dedic_gpio_bundle_handle_t;

/**
 * @brief 专用GPIO捆绑配置类型
 */
typedef struct {
    const int *gpio_array; /*!< GPIO编号数组，GPIO_Array[0]~GPIO_aArray[size-1]<=>low_dedic_channel_num~high_dedic_cannel_num*/
    size_t array_size;     /*!< gpio_array中的gpio数量*/
    struct {
        unsigned int in_en: 1;      /*!< 启用输入*/
        unsigned int in_invert: 1;  /*!< 反转输入信号*/
        unsigned int out_en: 1;     /*!< 启用输出*/
        unsigned int out_invert: 1; /*!< 反相输出信号*/
    } flags; /*!< 控制GPIO捆绑包特定行为的标志*/
} dedic_gpio_bundle_config_t;

/**
 * @brief 创建GPIO捆绑包并返回句柄
 *
 * @param[in] config GPIO捆绑包的配置
 * @param[out] ret_bundle 新创建的GPIO包的返回句柄
 * @return
 *      -ESP_OK:成功创建GPIO捆绑包
 *      -ESP_ERR_INVALID_ARG:创建GPIO捆绑包失败，因为参数无效
 *      -ESP_ERR_NO_MEM:创建GPIO捆绑包失败，因为没有可用的内存
 *      -ESP_ERR_NOT_FOUND：创建GPIO捆绑包失败，因为没有足够的连续专用通道
 *      -ESP_FAIL:由于其他错误，创建GPIO捆绑包失败
 *
 * @note 必须在“config”参数中至少启用输入或输出模式。
 */
esp_err_t dedic_gpio_new_bundle(const dedic_gpio_bundle_config_t *config, dedic_gpio_bundle_handle_t *ret_bundle);

/**
 * @brief Destory GPIO捆绑包
 *
 * @param[in] bundle 从“dedic_GPIO_new_bundle”返回的GPIO捆绑包的句柄
 * @return
 *      -ESP_OK:Destory GPIO捆绑包成功
 *      -ESP_ERR_INVALID_ARG:由于参数无效，Destory GPIO捆绑包失败
 *      -ESP_FAIL:由于其他错误，Destory GPIO捆绑包失败
 */
esp_err_t dedic_gpio_del_bundle(dedic_gpio_bundle_handle_t bundle);

/**@{*/
/**
 * @brief 获取分配的频道掩码
 *
 * @param[in] bundle 从“dedic_GPIO_new_bundle”返回的GPIO捆绑包的句柄
 * @param[out] mask 返回特定方向（向内或向外）的掩码值
 * @return
 *      -ESP_OK:成功获取频道掩码
 *      -ESP_ERR_INVALID_ARG:获取通道掩码失败，因为参数无效
 *      -ESP_FAIL:由于其他错误，获取频道掩码失败
 *
 * @note 根据捆绑包配置，每个捆绑包至少应有一个掩码（输入或输出）。
 * @note 使用返回的掩码，用户可以直接调用LL函数，如“cpu_LL_write_dedic_gpio_mask”或使用专用gpio指令编写汇编代码，以获得更好的gpio操作性能。
 */
esp_err_t dedic_gpio_get_out_mask(dedic_gpio_bundle_handle_t bundle, uint32_t *mask);
esp_err_t dedic_gpio_get_in_mask(dedic_gpio_bundle_handle_t bundle, uint32_t *mask);
/**@}*/

/**
 * @brief 将值写入GPIO捆绑包
 *
 * @param[in] bundle 从“dedic_GPIO_new_bundle”返回的GPIO捆绑包的句柄
 * @param[in] mask 要写入给定捆绑包中的GPIO掩码
 * @param[in] value 要写入给定GPIO包的值，低位表示包中的低位成员
 *
 * @note 从GPIO束的视图中可以看到遮罩。例如，bundleA包含[GPIO10，GPIO12，GPIO17]，要单独设置GPIO17，掩码应为0x04。
 * @note 出于性能原因，此函数不检查任何参数的有效性，而是放在IRAM中。
 */
void dedic_gpio_bundle_write(dedic_gpio_bundle_handle_t bundle, uint32_t mask, uint32_t value) IRAM_ATTR;

/**
 * @brief 读取从给定GPIO包输出的值
 *
 * @param[in] bundle 从“dedic_GPIO_new_bundle”返回的GPIO捆绑包的句柄
 * @return GPIO捆绑包输出的值，低位表示捆绑包中的低位成员
 *
 * @note 出于性能原因，此函数不检查任何参数的有效性，而是放在IRAM中。
 */
uint32_t dedic_gpio_bundle_read_out(dedic_gpio_bundle_handle_t bundle) IRAM_ATTR;

/**
 * @brief 读取输入到给定GPIO包的值
 *
 * @param[in] bundle 从“dedic_GPIO_new_bundle”返回的GPIO捆绑包的句柄
 * @return 输入到GPIO捆绑包的值，低位表示捆绑包中的低位成员
 *
 * @note 出于性能原因，此函数不检查任何参数的有效性，而是放在IRAM中。
 */
uint32_t dedic_gpio_bundle_read_in(dedic_gpio_bundle_handle_t bundle) IRAM_ATTR;

#if SOC_DEDIC_GPIO_HAS_INTERRUPT

/**
 * @brief 支持的专用GPIO中断类型
 */
typedef enum {
    DEDIC_GPIO_INTR_NONE,          /*!< 无中断*/
    DEDIC_GPIO_INTR_LOW_LEVEL = 2, /*!< 低电平中断*/
    DEDIC_GPIO_INTR_HIGH_LEVEL,    /*!< 高电平中断*/
    DEDIC_GPIO_INTR_NEG_EDGE,      /*!< 负边缘中断*/
    DEDIC_GPIO_INTR_POS_EDGE,      /*!< posedge上的中断*/
    DEDIC_GPIO_INTR_BOTH_EDGE      /*!< 负边和偏边都中断*/
} dedic_gpio_intr_type_t;

/**
 * @brief 专用GPIO ISR回调函数的类型
 *
 * @param bundle 从“dedic_GPIO_new_bundle”返回的GPIO捆绑包的句柄
 * @param index GPIO在其相应包中的索引（从0开始计数）
 * @param args 回调函数的用户定义参数。它通过`dedic_gpio_bandle_set_interrupt_and_callback传递`
 * @return 如果回调函数唤醒了高优先级任务
 */
typedef bool (*dedic_gpio_isr_callback_t)(dedic_gpio_bundle_handle_t bundle, uint32_t index, void *args);

/**
 * @brief 设置GPIO捆绑包的中断和回调功能
 *
 * @param[in] bundle 从“dedic_GPIO_new_bundle”返回的GPIO捆绑包的句柄
 * @param[in] mask 给定捆绑包中GPIO的掩码
 * @param[in] intr_type 中断类型，设置为DEDIC_GPIO_INTR_NONE可禁用中断
 * @param[in] cb_isr 在ISR上下文中调用的回调函数。此处的NULL指针将绕过回调
 * @param[in] cb_args 要传递给回调函数的用户定义参数
 *
 * @note 此函数仅对启用输入模式的捆绑包有效。请参阅“dedic_gpio_bandle_config_t”
 * @note 从GPIO捆绑包的视图中可以看到遮罩。例如，bundleA包含[GPIO10，GPIO12，GPIO17]，要单独设置GPIO17，掩码应为0x04。
 *
 * @return
 *      -ESP_OK：成功设置GPIO中断和回调函数
 *      -ESP_ERR_INVALID_ARG：由于参数无效，设置GPIO中断和回调函数失败
 *      -ESP_FAIL:由于其他错误，设置GPIO中断和回调函数失败
 */
esp_err_t dedic_gpio_bundle_set_interrupt_and_callback(dedic_gpio_bundle_handle_t bundle, uint32_t mask, dedic_gpio_intr_type_t intr_type, dedic_gpio_isr_callback_t cb_isr, void *cb_args);

#endif // SOC_DEDIC_GPIO_HAS_INTERRUPT

#ifdef __cplusplus
}
#endif

#endif //SOC_DEDICATED_GPIO_SUPPORTED

