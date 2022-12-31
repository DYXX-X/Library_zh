
/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _UART_SELECT_H_
#define _UART_SELECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/uart.h"

typedef enum {
    UART_SELECT_READ_NOTIF,
    UART_SELECT_WRITE_NOTIF,
    UART_SELECT_ERROR_NOTIF,
} uart_select_notif_t;

typedef void (*uart_select_notif_callback_t)(uart_port_t uart_num, uart_select_notif_t uart_select_notif, BaseType_t *task_woken);

/**
 * @brief 为select（）事件设置通知回调函数
 * @param uart_num UART端口号
 * @param uart_select_notif_callback 回调函数
 */
void uart_set_select_notif_callback(uart_port_t uart_num, uart_select_notif_callback_t uart_select_notif_callback);

/**
 * @brief 获取互斥保护select（）通知
 */
portMUX_TYPE *uart_get_selectlock(void);

#ifdef __cplusplus
}
#endif

#endif //_UART_SELECT_H_

