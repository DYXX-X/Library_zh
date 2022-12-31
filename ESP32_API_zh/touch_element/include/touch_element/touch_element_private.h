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

#include "touch_element/touch_element.h"
#include "touch_element/touch_button.h"
#include "touch_element/touch_slider.h"
#include "touch_element/touch_matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TE_TAG "Touch Element"
#define TE_DEBUG_TAG "Touch Element Debug"
#define TE_UNUSED(arg)            (void)arg

#define TE_CHECK(cond, ret_val) ({                                            \
    if (!(cond)) {                                                            \
        ESP_LOGE(TE_TAG, "%s(%d)", __FUNCTION__, __LINE__);     \
        return (ret_val);                                                     \
    }                                                                         \
})

#define TE_CHECK_GOTO(cond, label) ({                                         \
    if (!(cond)) {                                                            \
        goto label;                                                           \
    }                                                                         \
})

#define TE_FREE_AND_NULL(ptr) ({                                              \
    free(ptr);                                                                \
    (ptr) = NULL;                                                             \
})

#define TE_DEFAULT_THRESHOLD_DIVIDER(obj)       ((obj)->global_config->threshold_divider)
#define TE_DEFAULT_LONGPRESS_TIME(obj)          ((obj)->global_config->default_lp_time)

typedef enum {
    TE_STATE_IDLE = 0,
    TE_STATE_PRESS,
    TE_STATE_RELEASE,
} te_state_t;

typedef te_state_t te_dev_state_t;
typedef touch_elem_type_t te_dev_type_t;

typedef struct {
    float sens;                   //!< 触摸通道灵敏度
    touch_pad_t channel;          //!< 触摸通道编号（索引）
    te_dev_type_t type;           //!< 触摸通道类型TODO:需要重构为te_class_type_t
    te_dev_state_t state;         //!< 触摸通道当前状态
} te_dev_t;

typedef enum {
    TE_CLS_TYPE_BUTTON = 0,
    TE_CLS_TYPE_SLIDER,
    TE_CLS_TYPE_MATRIX,
    TE_CLS_TYPE_MAX  //TODO:添加防水类
} te_class_type_t;

typedef struct  {
    touch_elem_handle_t handle;
    bool (*check_channel) (touch_pad_t);
    esp_err_t (*set_threshold) (void);
    void (*process_state) (void);
    void (*update_state) (touch_pad_t, te_state_t);
} te_object_methods_t;

/* --------------------------------------------防水基本类型--------------------------------------------*/
struct te_waterproof_s {
    te_dev_t *guard_device;                     //防水防护通道装置
    touch_elem_handle_t *mask_handle;           //防水面罩手柄阵列
    touch_pad_t shield_channel;                 //防水屏蔽通道
    bool is_shield_level_set;                   //防水屏蔽水平设置钻头
};
typedef struct te_waterproof_s* te_waterproof_handle_t;
/* --------------------------------------------按钮基本类型--------------------------------------------*/
typedef struct {
    touch_elem_dispatch_t dispatch_method;      //按钮调度方法
    touch_button_callback_t callback;           //按钮回调例程
    uint32_t event_mask;                        //按钮订阅事件掩码
    void *arg;                                  //用户输入参数
} te_button_handle_config_t;

typedef te_state_t te_button_state_t;           //TODO:添加长按状态

struct te_button_s {
    te_button_handle_config_t *config;          //按钮配置
    te_dev_t *device;                           //基本设备信息
    te_button_state_t current_state;            //按钮当前状态
    te_button_state_t last_state;               //按钮最后状态
    touch_button_event_t event;                 //按钮外部状态（用于应用层）
    uint32_t trigger_cnt;                       //按钮长时间触发计数器
    uint32_t trigger_thr;                       //按钮长时间触发计数器阈值
};

typedef struct te_button_s* te_button_handle_t;
/* --------------------------------------------滑块基本类型--------------------------------------------*/
typedef struct {
    touch_elem_dispatch_t dispatch_method;      //滑块调度方法
    touch_slider_callback_t callback;           //滑块回调例程
    uint32_t event_mask;                        //滑块订阅事件掩码
    void *arg;                                  //用户输入参数
} te_slider_handle_config_t;

typedef te_state_t te_slider_state_t;

struct te_slider_s {
    te_slider_handle_config_t *config;          //滑块配置
    te_dev_t **device;                          //基本设备信息集
    te_slider_state_t current_state;            //滑块当前状态
    te_slider_state_t last_state;               //滑块最后状态
    touch_slider_event_t event;                 //滑块外部状态（用于应用层）
    float position_scale;                       //滑块位置比例（步长）
    float *quantify_signal_array;               //滑块重新量化阵列
    uint32_t *channel_bcm;                      //通道基准阵列
    uint32_t channel_bcm_update_cnt;            //通道基准更新计数器
    uint32_t filter_reset_cnt;                  //滑块复位计数器
    uint32_t last_position;                     //滑块最后位置
    touch_slider_position_t position;           //滑块位置
    uint8_t position_range;                     //滑块位置范围（[0，position_range]）
    uint8_t channel_sum;                        //滑块通道和
    uint8_t *pos_filter_window;                 //滑块位置移动平均过滤器窗口
    uint8_t pos_window_idx;                     //滑块位置移动平均过滤器窗口索引
    bool is_first_sample;                       //滑块第一次采样记录位
};

typedef struct te_slider_s* te_slider_handle_t;
/* --------------------------------------------矩阵基本类型--------------------------------------------*/
typedef struct {
    touch_elem_dispatch_t dispatch_method;      //矩阵按钮调度方法
    touch_matrix_callback_t callback;           //矩阵按钮回调例程
    uint32_t event_mask;                        //矩阵按钮订阅事件掩码
    void *arg;                                  //用户输入参数
} te_matrix_handle_config_t;

typedef te_state_t te_matrix_state_t;           //TODO:添加长按状态

struct te_matrix_s {
    te_matrix_handle_config_t *config;          //矩阵按钮配置
    te_dev_t **device;                          //基本设备信息
    te_matrix_state_t current_state;            //矩阵按钮当前状态
    te_matrix_state_t last_state;               //矩阵按钮当前状态
    touch_matrix_event_t event;                 //矩阵按钮处于外部状态（用于应用层）
    uint32_t trigger_cnt;                       //矩阵按钮长时间触发计数器
    uint32_t trigger_thr;                       //矩阵按钮长时间触发计数器阈值
    touch_matrix_position_t position;           //矩阵按钮位置
    uint8_t x_channel_num;                      //x轴上触摸传感器通道的数量
    uint8_t y_channel_num;                      //y轴上触摸传感器通道的数量
};

typedef struct te_matrix_s* te_matrix_handle_t;
/* ------------------------------------------------------------------------------------------------------------------ */

/* ---------------------------------------------全局系统方法----------------------------------------------*/
uint32_t te_read_smooth_signal(touch_pad_t channel_num);
bool te_system_check_state(void);
//TODO:使用函数重载重构此函数
esp_err_t te_dev_init(te_dev_t **device, uint8_t device_num, te_dev_type_t type, const touch_pad_t *channel, const float *sens, float divider);
void te_dev_deinit(te_dev_t **device, uint8_t device_num);
esp_err_t te_dev_set_threshold(te_dev_t *device);
esp_err_t te_event_give(touch_elem_message_t te_message);
uint8_t te_get_timer_period(void);
void te_object_method_register(te_object_methods_t *object_methods, te_class_type_t object_type);
void te_object_method_unregister(te_class_type_t object_type);
bool te_object_check_channel(const touch_pad_t *channel_array, uint8_t channel_sum);
bool waterproof_check_mask_handle(touch_elem_handle_t te_handle);
/* ------------------------------------------------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

