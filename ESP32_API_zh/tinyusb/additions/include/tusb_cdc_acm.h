// 2020浓缩咖啡系统（上海）有限公司版权所有。
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

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/ringbuf.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "tusb.h"
#include "tinyusb.h"

/**
 * @brief CDC端口可用于安装
 */
typedef enum{
    TINYUSB_CDC_ACM_0 = 0x0
}tinyusb_cdcacm_itf_t;

/* 回调和事件
   ********************************************************************* */

/**
 * @brief 提供给“callback_rx_wanted_char”回调输入的数据
 */
typedef struct {
    char wanted_char; /*!< 需要的字符*/
} cdcacm_event_rx_wanted_char_data_t;

/**
 * @brief 提供给“callback_line_state_changed”回调输入的数据
 */
typedef struct {
    bool dtr; /*!< 数据终端就绪（DTR）线路状态*/
    bool rts; /*!< 请求发送（RTS）线路状态*/
} cdcacm_event_line_state_changed_data_t;

/**
 * @brief 提供给“line_coding_changed”回调输入的数据
 */
typedef struct {
    cdc_line_coding_t const *p_line_coding; /*!< 新行编码值*/
} cdcacm_event_line_coding_changed_data_t;

/**
 * @brief CDC ACM事件的类型
 */
typedef enum {
    CDC_EVENT_RX,
    CDC_EVENT_RX_WANTED_CHAR,
    CDC_EVENT_LINE_STATE_CHANGED,
    CDC_EVENT_LINE_CODING_CHANGED
} cdcacm_event_type_t;

/**
 * @brief 描述传递给回调输入的事件
 */
typedef struct {
    cdcacm_event_type_t type; /*!< 事件类型*/
    union {
        cdcacm_event_rx_wanted_char_data_t rx_wanted_char_data; /*!< “callback_rx_wanted_char”回调的数据输入*/
        cdcacm_event_line_state_changed_data_t line_state_changed_data; /*!< “callback_line_state_changed”回调的数据输入*/
        cdcacm_event_line_coding_changed_data_t line_coding_changed_data; /*!< “line_coding_changed”回调的数据输入*/
    };
} cdcacm_event_t;

/**
 * @brief CDC-ACM回调类型
 */
typedef void(*tusb_cdcacm_callback_t)(int itf, cdcacm_event_t *event);

/***********************************************************************回调和事件*/
/* 其他结构
   ********************************************************************* */

/**
 * @brief CDC-ACM的配置结构
 */
typedef struct {
    tinyusb_usbdev_t usb_dev; /*!< 要设置的Usb设备*/
    tinyusb_cdcacm_itf_t cdc_port;  /*!< CDC端口*/
    size_t rx_unread_buf_sz; /*!< 一次可以传递给AMC的数据量*/
    tusb_cdcacm_callback_t callback_rx;  /*!< 指向将作为回调处理的“tusb_cdcacm_callback_t”类型函数的指针*/
    tusb_cdcacm_callback_t callback_rx_wanted_char; /*!< 指向将作为回调处理的“tusb_cdcacm_callback_t”类型函数的指针*/
    tusb_cdcacm_callback_t callback_line_state_changed; /*!< 指向将作为回调处理的“tusb_cdcacm_callback_t”类型函数的指针*/
    tusb_cdcacm_callback_t callback_line_coding_changed; /*!< 指向将作为回调处理的“tusb_cdcacm_callback_t”类型函数的指针*/
} tinyusb_config_cdcacm_t;

/***********************************************************************其他结构*/
/* 公共职能
   ********************************************************************* */
/**
 * @brief 初始化CDC ACM。初始化将通过`tud_cdc_line_state_cb`回调完成
 *
 * @param cfg -init配置结构
 * @return 电子邮箱地址
 */
esp_err_t tusb_cdc_acm_init(const tinyusb_config_cdcacm_t *cfg);


/**
 * @brief 注册CDC事件的回调调用。如果回调已注册，则将覆盖它
 *
 * @param itf -CDC对象的编号
 * @param event_type -回调的注册事件类型
 * @param callback  -回调函数
 * @return esp_err_t-esp_OK或esp_err_INVALID_ARG
 */
esp_err_t tinyusb_cdcacm_register_callback(tinyusb_cdcacm_itf_t itf,
        cdcacm_event_type_t event_type,
        tusb_cdcacm_callback_t callback);


/**
 * @brief 注销CDC事件的回调调用。
 *
 * @param itf -CDC对象的编号
 * @param event_type -回调的注册事件类型
 * @return esp_err_t-esp_OK或esp_err_INVALID_ARG
 */
esp_err_t tinyusb_cdcacm_unregister_callback(tinyusb_cdcacm_itf_t itf, cdcacm_event_type_t event_type);


/**
 * @brief 将一个字符发送到写入缓冲区
 *
 * @param itf -CDC对象的编号
 * @param ch -要发送的字符
 * @return size_t-排队字节数
 */
size_t tinyusb_cdcacm_write_queue_char(tinyusb_cdcacm_itf_t itf, char ch);


/**
 * @brief 从字节数组将数据写入写入缓冲区
 *
 * @param itf -CDC对象的编号
 * @param in_buf -源阵列
 * @param in_size -从arr_src写入的大小
 * @return size_t-排队字节数
 */
size_t tinyusb_cdcacm_write_queue(tinyusb_cdcacm_itf_t itf, const uint8_t *in_buf, size_t in_size);

/**
 * @brief 从写入缓冲区发送所有数据。使用“tinyusb_cdcam_write_queue”将数据添加到缓冲区。
 *
 *        警告！TinyUSB可以阻止多个RX回调的输出端点，之后将在每次传输后进行额外刷新。这可能会导致您请求刷新时的情况，但在下一次回调结束之前，它将失败。因此，不建议在回调中使用带超时的刷新-您可以获得超时锁定
 *
 * @param itf -CDC对象的编号
 * @param timeout_ticks -等待刷新将被视为失败
 * @return esp_err_t-如果（timeout_ticks>0）和刷新成功，则esp_OK；如果发生超时3，则esp_err_timeout；如果刷新失败，则esp_FAIL
 */
esp_err_t tinyusb_cdcacm_write_flush(tinyusb_cdcacm_itf_t itf, uint32_t timeout_ticks);

/**
 * @brief 读取数组的内容，并将其大小定义为sz_store
 *
 * @param itf -CDC对象的编号
 * @param out_buf -该数组将存储CDC缓冲区中的对象
 * @param out_buf_sz -结果缓冲区大小
 * @param rx_data_size -该地址将存储对象的大小
 * @return esp_err_t esp_OK、esp_FAIL或esp_err_INVALID_STATE
 */
esp_err_t tinyusb_cdcacm_read(tinyusb_cdcacm_itf_t itf, uint8_t *out_buf, size_t out_buf_sz, size_t *rx_data_size);


/**
 * @brief 检查ACM是否已初始化
 *
 * @param itf -CDC对象的编号
 * @return 真或假
 */
bool tusb_cdc_acm_initialized(tinyusb_cdcacm_itf_t itf);

/***********************************************************************公共职能*/

#ifdef __cplusplus
}
#endif

