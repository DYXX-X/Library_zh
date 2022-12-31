/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <sys/queue.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hcd.h"
#include "usb/usb_types_ch9.h"
#include "usb/usb_types_stack.h"

#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------------------------------类型--------------------------------------------------------

// -----------------------事件--------------------------

typedef enum {
    USBH_EVENT_DEV_NEW,             /**<已枚举新设备并将其添加到设备池*/
    USBH_EVENT_DEV_GONE,            /**<设备不见了。客户端应关闭设备*/
    USBH_EVENT_DEV_ALL_FREE,        /**<所有设备都已释放*/
} usbh_event_t;

/**
 * @brief 集线器驱动程序请求
 *
 * USBH可以发出的集线器驱动程序的各种请求。
 */
typedef enum {
    USBH_HUB_REQ_PORT_DISABLE,      /**<请求集线器驱动程序禁用特定端口（在释放设备后发生）。集线器驱动程序应响应USBH_Hub_EVENT_PORT_DISABLED*/
    USBH_HUB_REQ_PORT_RECOVER,      /**<请求集线器驱动程序恢复某个特定端口（在释放已损坏的设备后发生）。*/
} usbh_hub_req_t;

/**
 * @brief USBH的集线器驱动程序事件
 *
 * Hub驱动程序通过USBH_Hub_pass_event（）将这些事件传递给USBH
 *
 * USBH_HUB_EVENT_PORT_ERROR:
 * -端口遇到错误（例如突然断开连接）。连接到该端口的设备不再有效。
 * -USBH应：
 *      -触发USBH_EVENT_DEV_GONE
 *      -防止进一步传输到设备
 *      -如果设备已关闭，则触发设备清理
 *      -当最后一个客户端通过usbh_dev_close（）关闭设备时，释放设备对象并发出usbh_HUB_REQ_PORT_RECOVER请求
 *
 * USBH_HUB_EVENT_PORT_DISABLED:
 * -先前的USBH_HUB_REQ_PORT_DISABLE已完成。
 * -USBH应释放设备对象
 */
typedef enum {
    USBH_HUB_EVENT_PORT_ERROR,      /**<端口遇到错误（例如突然断开连接）。连接到该端口的设备应该被标记为不存在。*/
    USBH_HUB_EVENT_PORT_DISABLED,   /**<上一个USBH_HUB_REQ_PORT_DISABLE请求已完成*/
} usbh_hub_event_t;

// ----------------------回调------------------------

/**
 * @brief 用于指示提交的控制传输完成的回调usbh_dev_submit_ctrl_urb（）
 * @note 此回调是从usbh_process（）中调用的
 */
typedef void (*usbh_ctrl_xfer_cb_t)(usb_device_handle_t dev_hdl, urb_t *urb, void *arg);

/**
 * @brief 用于指示USBH发生事件的回调
 *
 * @note 此回调是从usbh_process（）中调用的
 * @note 在USBH_EVENT_DEV_ALL_FREE事件中，DEV_hdl参数设置为NULL
 */
typedef void (*usbh_event_cb_t)(usb_device_handle_t dev_hdl, usbh_event_t usbh_event, void *arg);

/**
 * @brief USBH用于从集线器驱动程序请求操作的回调
 *
 * 集线器请求回调允许USBH请求特定端口上的集线器操作。相反，集线器驱动程序将通过USBH_Hub_event（）函数向USBH指示其中一些请求的完成。
 */
typedef void (*usbh_hub_req_cb_t)(hcd_port_handle_t port_hdl, usbh_hub_req_t hub_req, void *arg);

// -----------------------对象-------------------------

/**
 * @brief 使用usbh_ep_alloc（）分配的端点的配置
 */
typedef struct {
    const usb_ep_desc_t *ep_desc;           /**<端点描述符*/
    hcd_pipe_callback_t pipe_cb;            /**<端点的管道回调*/
    void *pipe_cb_arg;                      /**<管道回调参数*/
    void *context;                          /**<管道上下文*/
} usbh_ep_config_t;

/**
 * @brief USBH_install（）中使用的USBH配置
 */
typedef struct {
    usb_notif_cb_t notif_cb;                /**<通知回调*/
    void *notif_cb_arg;                     /**<通知回调参数*/
    usbh_ctrl_xfer_cb_t ctrl_xfer_cb;       /**<控制传输回调*/
    void *ctrl_xfer_cb_arg;                 /**<控制传输回调参数*/
    usbh_event_cb_t event_cb;               /**<USBH事件回调*/
    void *event_cb_arg;                     /**<USBH事件回调参数*/
    hcd_config_t hcd_config;                /**<HCD配置*/
} usbh_config_t;

// -------------------------------------------------USBH功能----------------------------------------------------

/**
 * @brief 安装USBH驱动程序
 *
 * -此功能将在内部安装HCD
 * -在调用任何Hub驱动程序函数之前必须调用此函数
 *
 * @note 在调用此功能之前，主机控制器必须已取消时钟门控并重置。必须已配置USB PHY（内部或外部以及相关GPIO）。
 * @param usbh_config USBH驱动程序配置
 * @return 电子邮箱地址
 */
esp_err_t usbh_install(const usbh_config_t *usbh_config);

/**
 * @brief 卸载USBH驱动程序
 *
 * -此功能将卸载HCD
 * -调用此函数之前必须卸载集线器驱动程序
 *
 * @note 此功能只需释放USBH使用的资源。不会禁用基础主机控制器和USB PHY。
 * @return 电子邮箱地址
 */
esp_err_t usbh_uninstall(void);

/**
 * @brief USBH处理功能
 *
 * -必须重复调用以处理USBH事件的USBH处理函数
 * -如果阻塞，调用方可以阻塞，直到在运行此函数之前收到USB_NOTIF_SOURCE_USBH通知
 *
 * @note 此功能可以阻止
 * @return 电子邮箱地址
 */
esp_err_t usbh_process(void);

/**
 * @brief 获取当前设备数
 *
 * @note 此功能可以阻止
 * @param[out] num_devs_ret 当前设备数量
 * @return 电子邮箱地址
 */
esp_err_t usbh_num_devs(int *num_devs_ret);

// ------------------------------------------------设备功能---------------------------------------------------

// ---------------------设备池-----------------------

/**
 * @brief 用当前连接设备的地址填充列表
 *
 * -此函数使用当前连接设备的地址填充提供的列表
 * -然后可以在usbh_dev_open（）中使用设备地址
 * -如果设备多于list_len，则此函数将只填充list_len个设备。
 *
 * @param[in] list_len 空列表的长度
 * @param[inout] dev_addr_list 要填写的空列表
 * @param[out] num_dev_ret 填入列表的设备数量
 * @return 电子邮箱地址
 */
esp_err_t usbh_dev_addr_list_fill(int list_len, uint8_t *dev_addr_list, int *num_dev_ret);

/**
 * @brief 按地址打开设备
 *
 * 必须打开设备才能使用
 *
 * @param[in] dev_addr 设备地址
 * @param[out] dev_hdl 设备手柄
 * @return 电子邮箱地址
 */
esp_err_t usbh_dev_open(uint8_t dev_addr, usb_device_handle_t *dev_hdl);

/**
 * @brief C关闭设备
 *
 * 可以通过调用usbh_dev_open（）打开设备
 *
 * @param[in] dev_hdl 设备手柄
 * @return 电子邮箱地址
 */
esp_err_t usbh_dev_close(usb_device_handle_t dev_hdl);

/**
 * @brief 标记应在下一次可能的机会释放所有设备
 *
 * 标记为空闲的设备将不会被释放，直到最后一个使用该设备的客户端调用了usbh_dev_close（）
 *
 * @return
 *  -ESP_OK：开始时没有可以释放的设备。当前状态为全部空闲
 *  -ESP_ERR_NOT_FINISHED：一个或多个设备仍需要释放（但已标记为“待释放”）
 */
esp_err_t usbh_dev_mark_all_free(void);

// -------------------单个设备----------------------

/**
 * @brief 获取设备的地址
 *
 * @note 无需打开设备即可调用
 *
 * @param[in] dev_hdl 设备手柄
 * @param[out] dev_addr 设备的地址
 * @return 电子邮箱地址
 */
esp_err_t usbh_dev_get_addr(usb_device_handle_t dev_hdl, uint8_t *dev_addr);

/**
 * @brief 获取设备信息
 *
 * @note 此功能可以阻止
 * @param[in] dev_hdl 设备手柄
 * @param[out] dev_info 设备信息
 * @return 电子邮箱地址
 */
esp_err_t usbh_dev_get_info(usb_device_handle_t dev_hdl, usb_device_info_t *dev_info);

/**
 * @brief 获取设备的设备描述符
 *
 * -设备描述符在集线器驱动程序创建设备时缓存
 *
 * @param[in] dev_hdl 设备手柄
 * @param[out] dev_desc_ret 设备描述符
 * @return 电子邮箱地址
 */
esp_err_t usbh_dev_get_desc(usb_device_handle_t dev_hdl, const usb_device_desc_t **dev_desc_ret);

/**
 * @brief 获取设备的活动配置描述符
 *
 * 只需返回对内部缓存的配置描述符的引用
 *
 * @note 此功能可以阻止
 * @param[in] dev_hdl 设备手柄
 * @param config_desc_ret
 * @return 电子邮箱地址
 */
esp_err_t usbh_dev_get_config_desc(usb_device_handle_t dev_hdl, const usb_config_desc_t **config_desc_ret);

/**
 * @brief 向设备提交控制传输（URB）
 *
 * @param[in] dev_hdl 设备手柄
 * @param[in] urb URB
 * @return 电子邮箱地址
 */
esp_err_t usbh_dev_submit_ctrl_urb(usb_device_handle_t dev_hdl, urb_t *urb);

// -----------------------------------------------端点函数-------------------------------------------------

/**
 * @brief 在设备上分配端点
 *
 * 已打开设备的客户端必须调用此函数来分配声明的接口中的所有端点。返回端点的管道句柄，以便客户端可以直接使用和控制管道。
 *
 * @note 此功能可以阻止
 * @note 默认管道由USBH拥有。对于控制传输，请改用usbh_dev_submit_ctrl_urb（）
 * @note 客户端必须首先打开设备
 *
 * @param[in] dev_hdl 设备手柄
 * @param[in] ep_config
 * @param[out] pipe_hdl_ret 管道手柄
 * @return 电子邮箱地址
 */
esp_err_t usbh_ep_alloc(usb_device_handle_t dev_hdl, usbh_ep_config_t *ep_config, hcd_pipe_handle_t *pipe_hdl_ret);

/**
 * @brief 设备上的空闲和终结点
 *
 * 释放之前由usbh_ep_alloc（）打开的端点
 *
 * @note 此功能可以阻止
 * @param[in] dev_hdl 设备手柄
 * @param[in] bEndpointAddress 终结点地址
 * @return 电子邮箱地址
 */
esp_err_t usbh_ep_free(usb_device_handle_t dev_hdl, uint8_t bEndpointAddress);

/**
 * @brief 获取端点的上下文
 *
 * 获取分配时分配给和端点的上下文变量。
 *
 * @note 此功能可以阻止
 * @param[in] dev_hdl 设备手柄
 * @param[in] bEndpointAddress 终结点地址
 * @param[out] context_ret 上下文变量
 * @return 电子邮箱地址
 */
esp_err_t usbh_ep_get_context(usb_device_handle_t dev_hdl, uint8_t bEndpointAddress, void **context_ret);

// --------------------------------------------------集线器功能----------------------------------------------------

// -------------------与设备相关----------------------

/**
 * @brief 向USBH指示已安装集线器驱动程序
 *
 * -集线器驱动程序必须在其安装中调用此函数，以指示已安装的USBH。
 * -只有在安装了USBH后才能调用
 *
 * @note 仅集线器驱动程序
 * @param[in] hub_req_callback 集线器请求回调
 * @param[in] callback_arg 回调参数
 * @return 电子邮箱地址
 */
esp_err_t usbh_hub_is_installed(usbh_hub_req_cb_t hub_req_callback, void *callback_arg);

/**
 * @brief 向USBH指示设备枚举的开始
 *
 * -集线器驱动程序在开始枚举新设备之前调用此函数。
 * -USBH将分配一个新设备，该设备将由集线器驱动程序使用剩余的集线器枚举功能初始化。
 * -新设备的默认管道句柄将返回到枚举期间要使用的所有集线器驱动程序。
 *
 * @note 仅集线器驱动程序
 * @param[in] port_hdl 设备连接到的端口的句柄
 * @param[in] dev_speed 设备的速度
 * @param[out] new_dev_hdl 设备的手柄
 * @param[out] default_pipe_hdl 设备的默认管道句柄
 * @return 电子邮箱地址
 */
esp_err_t usbh_hub_add_dev(hcd_port_handle_t port_hdl, usb_speed_t dev_speed, usb_device_handle_t *new_dev_hdl, hcd_pipe_handle_t *default_pipe_hdl);

/**
 * @brief 向USBH指示特定设备发生了集线器事件
 *
 * @param dev_hdl 设备手柄
 * @param hub_event 集线器事件
 * @return 电子邮箱地址
 */
esp_err_t usbh_hub_pass_event(usb_device_handle_t dev_hdl, usbh_hub_event_t hub_event);

// -----------------枚举相关-------------------

/**
 * @brief 分配枚举设备的地址
 *
 * @note 仅集线器驱动程序
 * @note 必须按顺序调用
 * @param[in] dev_hdl 设备手柄
 * @param dev_addr
 * @return 电子邮箱地址
 */
esp_err_t usbh_hub_enum_fill_dev_addr(usb_device_handle_t dev_hdl, uint8_t dev_addr);

/**
 * @brief 填充枚举设备的描述符
 *
 * @note 仅集线器驱动程序
 * @note 必须按顺序调用
 * @param[in] dev_hdl 设备手柄
 * @param device_desc
 * @return 电子邮箱地址
 */
esp_err_t usbh_hub_enum_fill_dev_desc(usb_device_handle_t dev_hdl, const usb_device_desc_t *device_desc);

/**
 * @brief 填充枚举设备的活动配置描述符
 *
 * @note 仅集线器驱动程序
 * @note 必须按顺序调用
 * @note 此功能可以阻止
 * @param[in] dev_hdl 设备手柄
 * @param config_desc_full
 * @return 电子邮箱地址
 */
esp_err_t usbh_hub_enum_fill_config_desc(usb_device_handle_t dev_hdl, const usb_config_desc_t *config_desc_full);

/**
 * @brief 填充枚举设备的字符串描述符之一
 *
 * @note 仅集线器驱动程序
 * @note 必须按顺序调用
 * @param dev_hdl 设备手柄
 * @param str_desc 指向字符串描述符的指针
 * @param select 选择字符串描述符。制造商/产品/序列号字符串描述符分别为0/1/2
 * @return 电子邮箱地址
 */
esp_err_t usbh_hub_enum_fill_str_desc(usb_device_handle_t dev_hdl, const usb_str_desc_t *str_desc, int select);

/**
 * @brief 指示设备枚举已完成
 *
 * 这将使客户端打开所有设备，并触发USBH_EVENT_DEV_NEW事件。
 *
 * @note 仅集线器驱动程序
 * @note 必须按顺序调用
 * @note 此功能可以阻止
 * @param[in] dev_hdl 设备手柄
 * @return 电子邮箱地址
 */
esp_err_t usbh_hub_enum_done(usb_device_handle_t dev_hdl);

/**
 * @brief 指示设备枚举失败
 *
 * 这将导致枚举设备的资源被清理。集线器驱动程序必须确保枚举设备的默认管道已停止、刷新和退出队列。
 *
 * @note 仅集线器驱动程序
 * @note 必须按顺序调用
 * @note 此功能可以阻止
 * @param[in] dev_hdl 设备手柄
 * @return 电子邮箱地址
 */
esp_err_t usbh_hub_enum_failed(usb_device_handle_t dev_hdl);

#ifdef __cplusplus
}
#endif

