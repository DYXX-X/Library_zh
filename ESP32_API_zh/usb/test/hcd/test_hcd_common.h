/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "hcd.h"
#include "usb_private.h"
#include "usb/usb_types_ch9.h"

#define URB_CONTEXT_VAL ((void *)0xDEADBEEF)

// -------------------------------------------------HCD事件测试----------------------------------------------------

/**
 * @brief 期待（等待）HCD端口事件
 *
 * @param port_hdl 预期事件的端口句柄
 * @param expected_event 预期的端口事件
 */
void test_hcd_expect_port_event(hcd_port_handle_t port_hdl, hcd_port_event_t expected_event);

/**
 * @brief 预期（等待）HCD管道事件
 *
 * @param pipe_hdl 预期事件的管道句柄
 * @param expected_event 预期的管道事件
 */
void test_hcd_expect_pipe_event(hcd_pipe_handle_t pipe_hdl, hcd_pipe_event_t expected_event);

/**
 * @brief 获取当前排队的端口事件数（使用test_hcd_expect_port_event（）退出队列）
 *
 * @param port_hdl 端口手柄
 * @return int当前排队的端口事件数
 */
int test_hcd_get_num_port_events(hcd_port_handle_t port_hdl);

/**
 * @brief 获取当前排队管道事件的数量（使用test_hcd_expect_pipe_event（）退出队列）
 *
 * @param pipe_hdl 管道手柄
 * @return int当前排队的管道事件数
 */
int test_hcd_get_num_pipe_events(hcd_pipe_handle_t pipe_hdl);

// -----------------------------------------------驱动程序/端口相关-------------------------------------------------

/**
 * @brief 设置HCD并初始化HCD端口。
 *
 * @return hcd_port_handle_t端口句柄
 */
hcd_port_handle_t test_hcd_setup(void);

/**
 * @brief 释放和HCD端口并卸载HCD
 *
 * @param port_hdl 端口手柄
 */
void test_hcd_teardown(hcd_port_handle_t port_hdl);

/**
 * @brief 等待HCD端口上的连接
 *
 * @note 此函数将在内部调用test_usb_set_phy_state（）以允许连接
 *
 * @param port_hdl 端口手柄
 * @return usb_speed_t连接设备的速度
 */
usb_speed_t test_hcd_wait_for_conn(hcd_port_handle_t port_hdl);

/**
 * @brief 等待HCD端口上的断开连接
 *
 * @note 此函数将在内部调用test_usb_set_phy_state（）以强制断开连接
 *
 * @param port_hdl 端口手柄
 * @param already_disabled HCD端口是否已处于禁用状态
 */
void test_hcd_wait_for_disconn(hcd_port_handle_t port_hdl, bool already_disabled);

// -------------------------------------------------管道分配/自由---------------------------------------------------

/**
 * @brief 测试管道的分配
 *
 * @param port_hdl 端口手柄
 * @param ep_desc 终结点描述符
 * @param dev_addr 管道的设备地址
 * @param dev_speed 管道的装置速度
 * @return hcd_pipe_handle_t管道句柄
 */
hcd_pipe_handle_t test_hcd_pipe_alloc(hcd_port_handle_t port_hdl, const usb_ep_desc_t *ep_desc, uint8_t dev_addr, usb_speed_t dev_speed);

/**
 * @brief 测试管道的释放
 *
 * @param pipe_hdl 管道手柄
 */
void test_hcd_pipe_free(hcd_pipe_handle_t pipe_hdl);

/**
 * @brief 分配URB
 *
 * @param num_isoc_packets 同步数据包的数量
 * @param data_buffer_size URB的数据缓冲区大小
 * @return urb_t*市区
 */
urb_t *test_hcd_alloc_urb(int num_isoc_packets, size_t data_buffer_size);

/**
 * @brief 释放URB
 *
 * @param urb URB
 */
void test_hcd_free_urb(urb_t *urb);

// ---------------------------------------------------枚举-----------------------------------------------------

/**
 * @brief 对设备进行一些基本枚举
 *
 * 对于需要枚举设备的测试（例如批量测试）。此函数将使用设备的默认管道枚举该设备。最小枚举将包括
 *
 * -获取设备的描述符并更新默认管道的MPS
 * -设置设备的地址并更新默认管道以使用该地址
 * -将设备设置为配置1（即找到的第一个配置
 *
 * @param default_pipe 连接设备的默认管道
 * @return uint8_t枚举后设备的地址
 */
uint8_t test_hcd_enum_device(hcd_pipe_handle_t default_pipe);

