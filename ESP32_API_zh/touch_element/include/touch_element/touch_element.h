// 版权所有2016-2020 Espressif Systems（上海）私人有限公司
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

#include "driver/touch_sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------常规硬件和系统默认配置------------------------------*/
/* 由于这些是重要的硬件和算法参数，用户在了解所有细节之前不应更改它们*/
/* ------------------------------------------------------------------------------------------------------------------ */
#define TOUCH_ELEM_GLOBAL_DEFAULT_CONFIG()                                    \
{                                                                             \
    .hardware = {                                                             \
        .upper_voltage = TOUCH_HVOLT_2V7,                                     \
        .voltage_attenuation = TOUCH_HVOLT_ATTEN_0V5,                         \
        .lower_voltage = TOUCH_LVOLT_0V5,                                     \
        .suspend_channel_polarity = TOUCH_PAD_CONN_HIGHZ,                     \
        .denoise_level = TOUCH_PAD_DENOISE_BIT4,                              \
        .denoise_equivalent_cap = TOUCH_PAD_DENOISE_CAP_L0,                   \
        .smooth_filter_mode = TOUCH_PAD_SMOOTH_IIR_2,                         \
        .benchmark_filter_mode = TOUCH_PAD_FILTER_IIR_16,                     \
        .sample_count = 500,                                                  \
        .sleep_cycle = 0xf,                                                   \
        .benchmark_debounce_count = 2,                                        \
        .benchmark_calibration_threshold = 2,                                 \
        .benchmark_jitter_step = 5                                            \
    },                                                                        \
    .software = {                                                             \
        .waterproof_threshold_divider = 0.8,                                  \
        .processing_period = 10,                                              \
        .intr_message_size = 14,                                              \
        .event_message_size = 20                                              \
    }                                                                         \
}
/* ------------------------------------------------------------------------------------------------------------------ */

/* ----------------------------------------------事件订阅----------------------------------------------*/
#define TOUCH_ELEM_EVENT_NONE                       BIT(0)      //!< 无事件
#define TOUCH_ELEM_EVENT_ON_PRESS                   BIT(1)      //!< On Press事件
#define TOUCH_ELEM_EVENT_ON_RELEASE                 BIT(2)      //!< 发布时事件
#define TOUCH_ELEM_EVENT_ON_LONGPRESS               BIT(3)      //!< LongPress事件
#define TOUCH_ELEM_EVENT_ON_CALCULATION             BIT(4)      //!< 计算时事件
/* ------------------------------------------------------------------------------------------------------------------ */
#define TOUCH_WATERPROOF_GUARD_NOUSE       (0)         //!< 防水不使用防护传感器
/* --------------------------------全局硬件和软件配置结构------------------------------*/
/**
 * @brief   触摸元件软件配置
 */
typedef struct {
    float waterproof_threshold_divider;        //!< 防水防护通道门槛分隔器
    uint8_t processing_period;                 //!< 处理周期（ms）
    uint8_t intr_message_size;                 //!< 中断消息队列大小
    uint8_t event_message_size;                //!< 事件消息队列大小
} touch_elem_sw_config_t;

/**
 * @brief   触摸元件硬件配置
 */
typedef struct {
    touch_high_volt_t upper_voltage;                  //!< 触摸传感器通道上充电电压
    touch_volt_atten_t voltage_attenuation;           //!< 触摸传感器通道充电电压上限衰减（Diff电压上限-衰减-下限）
    touch_low_volt_t lower_voltage;                   //!< 触摸传感器通道较低充电电压
    touch_pad_conn_type_t suspend_channel_polarity;   //!< 暂停通道极性（高阻抗状态或GND）
    touch_pad_denoise_grade_t denoise_level;          //!< 内部降噪水平
    touch_pad_denoise_cap_t denoise_equivalent_cap;   //!< 内部降噪通道（触摸通道0）等效电容
    touch_smooth_mode_t smooth_filter_mode;           //!< 平滑值过滤器模式（仅适用于touch_pad_filter_read_Smooth（））
    touch_filter_mode_t benchmark_filter_mode;        //!< 基准过滤器模式
    uint16_t sample_count;                            //!< 触摸传感器每次测量的样本计数
    uint16_t sleep_cycle;                             //!< 睡眠周期（RTC慢时钟）
    uint8_t benchmark_debounce_count;                 //!< 基准反跳计数
    uint8_t benchmark_calibration_threshold;          //!< 基准校准阈值
    uint8_t benchmark_jitter_step;                    //!< 基准抖动滤波器步长（仅在基准滤波器模式为抖动滤波器时有效）
} touch_elem_hw_config_t;

/**
 * @brief   触摸元件全局配置传递给Touch_element_install
 */
typedef struct {
    touch_elem_hw_config_t hardware;         //!< 硬件配置
    touch_elem_sw_config_t software;         //!< 软件配置
} touch_elem_global_config_t;

/**
 * @brief   触摸元件防水配置传递给Touch_element_waterproof_install
 */
typedef struct {
    touch_pad_t guard_channel;     //!< 防水防护传感器通道编号（索引）
    float guard_sensitivity;       //!< 防水防护传感器灵敏度
} touch_elem_waterproof_config_t;
/* ------------------------------------------------------------------------------------------------------------------ */
typedef void *touch_elem_handle_t;        //!< 触摸元件手柄类型
typedef uint32_t touch_elem_event_t;      //!< 触摸元件事件类型

/**
 * @brief   触摸元件手柄类型
 */
typedef enum {
    TOUCH_ELEM_TYPE_BUTTON,         //!< 触摸元件按钮
    TOUCH_ELEM_TYPE_SLIDER,         //!< 触摸元件滑块
    TOUCH_ELEM_TYPE_MATRIX,         //!< 触摸元件矩阵按钮
} touch_elem_type_t;

/**
 * @brief   触摸元素事件分派方法（事件队列/回调）
 */
typedef enum {
    TOUCH_ELEM_DISP_EVENT,           //!< 事件队列调度
    TOUCH_ELEM_DISP_CALLBACK,        //!< 回调调度
    TOUCH_ELEM_DISP_MAX
} touch_elem_dispatch_t;

/**
 * @brief   来自Touch_element_message_receive（）的触摸元素事件消息类型
 */
typedef struct {
    touch_elem_handle_t handle;             //!< 触摸元件手柄
    touch_elem_type_t element_type;         //!< 触摸元件类型
    void *arg;                              //!< 用户输入参数
    uint8_t child_msg[8];                   //!< 编码的消息
} touch_elem_message_t;
/* ------------------------------------------------------------------------------------------------------------------ */

/**
 * @brief   触摸元件处理初始化
 *
 * @param[in]   global_config   全局初始化配置结构
 *
 * @note    要重新初始化触摸元素对象，请首先调用touch_element_uninstall（）
 *
 * @return
 *      -ESP_OK:已成功初始化
 *      -ESP_ERR_INVALID_ARG:参数无效
 *      -ESP_ERR_NO_MEM:内存不足
 *      -ESP_ERR_INVALID_STATE:触摸元件已初始化
 *      -其他：未知触摸驱动层或下层错误
 */
esp_err_t touch_element_install(const touch_elem_global_config_t *global_config);

/**
 * @brief   触摸元件处理开始
 *
 * 此功能启动触摸元件处理系统
 *
 * @note    只有在所有触摸元素实例完成创建后才能调用此函数
 *
 * @return
 *      -ESP_OK:已成功开始处理
 *      -其他：未知触摸驱动层或下层错误
 */
esp_err_t touch_element_start(void);

/**
 * @brief   触摸元件处理停止
 *
 * 此功能可停止触摸元件处理系统
 *
 * @note    在更改系统（硬件、软件）参数之前，必须调用此功能
 *
 * @return
 *      -ESP_OK:已成功停止处理
 *      -其他：未知触摸驱动层或下层错误
 */
esp_err_t touch_element_stop(void);

/**
 * @brief   释放使用touch_element_install分配的资源
 *
 * @return
 *      -ESP_OK：已成功释放触摸元素对象
 *      -ESP_ERR_INVALID_STATE:触摸元素对象未初始化
 *      -其他：未知触摸驱动层或下层错误
 */
void touch_element_uninstall(void);

/**
 * @brief   获取触摸元素实例的当前事件消息
 *
 * 此函数将从te_event_give（）接收触摸元素消息（句柄、事件类型等）。它将阻止，直到发生触摸元件事件或超时。
 *
 * @param[out]  element_message          触摸元件事件消息结构
 * @param[in]   ticks_to_wait   等待事件要阻止的FreeRTOS节拍数
 * @return
 *      -ESP_OK：成功接收触摸元素事件
 *      -ESP_ERR_INVALID_STATE:触摸元件库未初始化
 *      -ESP_ERR_INVALID_ARG:element_message为空
 *      -ESP_ERR_TIMEOUT:等待事件超时
 */
esp_err_t touch_element_message_receive(touch_elem_message_t *element_message, uint32_t ticks_to_wait);

/**
 * @brief   触摸元件防水初始化
 *
 * 该功能使硬件防水，然后触摸元件系统使用屏蔽传感器和防护传感器来减轻水滴和水流的影响。
 *
 * @param[in] waterproof_config     防水配置
 *
 * @note    如果使用防水功能，屏蔽传感器不能被禁用，它将使用通道14作为其内部通道。因此，用户不能将信道14用于另一提议。由于防护传感器是可选的，因此不需要防护传感器。
 *
 * @note    屏蔽传感器：它始终使用通道14作为屏蔽通道，因此用户必须连接通道14和PCB中的屏蔽层，因为它将自动生成同步信号
 *
 * @note    防护传感器：此功能是可选的。如果使用，用户必须连接PCB中的保护通道和保护环。用户想要保护的任何通道都应该添加到PCB的保护环中。
 *
 * @return
 *      -ESP_OK:已成功初始化
 *      -ESP_ERR_INVALID_STATE:触摸元件库未初始化
 *      -ESP_ERR_INVALID_ARG:防水配置为空或防护传感器通道无效
 *      -ESP_ERR_NO_MEM:内存不足
 */
esp_err_t touch_element_waterproof_install(const touch_elem_waterproof_config_t *waterproof_config);

/**
 * @brief   释放使用touch_element_waterproof_install（）分配的资源
 */
void touch_element_waterproof_uninstall(void);

/**
 * @brief   在触发保护传感器时，添加一个屏蔽手柄以进行保护
 *
 * 此函数将添加应用程序句柄（按钮、滑块等）作为掩码句柄。当防护传感器被触发时，防水功能将开始工作并锁定应用程序内部状态。当水的影响降低时，应用程序将解锁并重置为IDLE状态。
 *
 * @param[in] element_handle     触摸元件实例手柄
 *
 * @note    防水保护逻辑必须遵循PCB中的实际电路，这意味着输入手柄内的所有通道必须位于实际电路中的保护环内。
 *
 * @return
 *      -ESP_OK:已成功添加掩码句柄
 *      -ESP_ERR_INVALID_STATE:防水未初始化
 *      -ESP_ERR_INVALID_ARG:element_handle为空
 */
esp_err_t touch_element_waterproof_add(touch_elem_handle_t element_handle);

/**
 * @brief   拆下带面罩的手柄以保护
 *
 * 此函数将从掩码句柄表中删除应用程序句柄。
 *
 * @param[in] element_handle     触摸元件实例手柄
 *
 * @return
 *      -ESP_OK:已成功删除掩码句柄
 *      -ESP_ERR_INVALID_STATE:防水未初始化
 *      -ESP_ERR_INVALID_ARG:element_handle为空
 *      -ESP_ERR_NOT_FOUND：无法从防水mask_handle列表中搜索element_handle
 */
esp_err_t touch_element_waterproof_remove(touch_elem_handle_t element_handle);

#ifdef __cplusplus
}
#endif

