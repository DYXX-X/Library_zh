/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*
警告：USB主机库API仍然是测试版，可能会更改
*/

#pragma once

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "esp_err.h"
#include "esp_intr_alloc.h"
//还包括其他USB主机库标头
#include "usb/usb_helpers.h"
#include "usb/usb_types_ch9.h"
#include "usb/usb_types_stack.h"

#ifdef __cplusplus
extern "C" {
#endif

// -------------------------------------------------宏和类型--------------------------------------------------

// -----------------------手柄-------------------------

/**
 * @brief USB主机库异步客户端的句柄
 *
 * 可以使用usb_host_client_register（）注册异步客户端
 *
 * @note 异步API
 */
typedef struct usb_host_client_handle_s * usb_host_client_handle_t;

// -----------------------事件--------------------------

#define USB_HOST_LIB_EVENT_FLAGS_NO_CLIENTS     0x01    /**<所有客户端都已从USB主机库注销*/
#define USB_HOST_LIB_EVENT_FLAGS_ALL_FREE       0x02    /**<USB主机库已释放所有设备*/

/**
 * @brief 客户端事件消息中的类型事件
 */
typedef enum {
    USB_HOST_CLIENT_EVENT_NEW_DEV,                  /**<已枚举新设备并将其添加到USB主机库*/
    USB_HOST_CLIENT_EVENT_DEV_GONE,                 /**<客户端打开的设备现在不存在*/
} usb_host_client_event_t;

/**
 * @brief 客户端事件消息
 *
 * 客户端事件消息被发送到USB主机库的每个客户端，以便通知它们各种USB主机库事件，例如：
 * -添加新设备
 * -移除现有设备
 *
 * @note 事件消息结构具有与每个特定事件对应的成员的联合。根据事件类型，只能访问相关的成员字段。
 */
typedef struct {
    usb_host_client_event_t event;              /**<事件类型*/
    union {
        struct {
            uint8_t address;                    /**<新设备的地址*/
        } new_dev;
        struct {
            usb_device_handle_t dev_hdl;        /**<不见的设备手柄*/
        } dev_gone;
    };
} usb_host_client_event_msg_t;

// ------------------------信息---------------------------

/**
 * @brief 通过USB_Host_lib_info（）获取的USB主机库的当前信息
 */
typedef struct {
    int num_devices;    /**<当前连接（和枚举）设备的数量*/
    int num_clients;    /**<当前注册客户端数*/
} usb_host_lib_info_t;

// ----------------------回调------------------------

/**
 * @brief 客户端事件回调
 *
 * -USB主机库的每个客户端都必须注册一个事件回调，以从USB主机库接收事件消息。
 * -客户端事件回调从客户端usb_host_client_handle_events（）函数的上下文中运行
 */
typedef void (*usb_host_client_event_cb_t)(const usb_host_client_event_msg_t *event_msg, void *arg);

// --------------------配置---------------------

/**
 * @brief USB主机库配置
 *
 * USB主机库的配置结构。在usb_host_install（）函数中提供
 */
typedef struct {
    bool skip_phy_setup;        /**<如果设置，则USB主机库将不会配置USB PHY，因此允许用户在调用USB_Host_install（）之前手动配置USB PHY。如果用户想要使用外部USB PHY，则应设置此选项。否则，USB主机库将自动配置内部USB PHY*/
    int intr_flags;             /**<USB主机堆栈使用的底层ISR的中断标志*/
} usb_host_config_t;

/**
 * @brief USB主机库客户端配置
 *
 * USB主机库客户端的配置结构。在usb_host_client_register（）中提供
 */
typedef struct {
    bool is_synchronous;        /**<客户端是否异步或同步。暂时设置为false。*/
    int max_num_event_msg;      /**<可存储的最大事件消息数（例如，3）*/
    union {     //注：制成联合体或未来扩展
        struct {
            usb_host_client_event_cb_t client_event_callback;   /**<客户端的事件回调函数*/
            void *callback_arg;                                 /**<事件回调函数参数*/
        } async;
    };
} usb_host_client_config_t;

// ------------------------------------------------库函数--------------------------------------------------

/**
 * @brief 安装USB主机库
 *
 * -此功能只能安装一次USB主机库
 * -应在调用任何其他USB主机库函数之前调用此函数
 *
 * @note 如果在安装配置中设置了skip_phy_setup，则用户负责确保底层主机控制器已启用，并且在调用此功能之前USB phy（内部或外部）已设置。
 * @param[in] config USB主机库配置
 * @return 电子邮箱地址
 */
esp_err_t usb_host_install(const usb_host_config_t *config);

/**
 * @brief 卸载USB主机库
 *
 * -应调用此函数卸载USB主机库，从而释放其资源
 * -在调用此函数之前，必须注销所有客户端
 * -必须通过调用usb_host_device_free_All（）并接收usb_host_LB_EVENT_FLAGS_All_free事件标志来释放所有设备
 *
 * @note 如果在安装主机库时设置了skip_phy_setup，则用户负责禁用基础主机控制器和USB phy（内部或外部）。
 * @return 电子邮箱地址
 */
esp_err_t usb_host_uninstall(void);

/**
 * @brief 处理USB主机库事件
 *
 * -此函数处理USB主机库的所有处理，应在循环中重复调用
 * -检查event_flags_ret，查看是否设置了指示特定USB主机库事件的标志
 * -多个线程不应同时调用此函数
 *
 * @note 此功能可以阻止
 * @param[in] timeout_ticks 等待事件发生的超时（以滴答为单位）
 * @param[out] event_flags_ret 指示发生USB主机库事件的事件标志。
 * @return 电子邮箱地址
 */
esp_err_t usb_host_lib_handle_events(TickType_t timeout_ticks, uint32_t *event_flags_ret);

/**
 * @brief 取消阻止USB主机库处理程序
 *
 * -此函数只需取消阻止USB主机库事件处理函数（USB_Host_lib_handle_events（））
 *
 * @return 电子邮箱地址
 */
esp_err_t usb_host_lib_unblock(void);

/**
 * @brief 获取有关USB主机库的最新信息
 *
 * @param[out] info_ret USB主机库信息
 * @return 电子邮箱地址
 */
esp_err_t usb_host_lib_info(usb_host_lib_info_t *info_ret);

// ------------------------------------------------客户端功能---------------------------------------------------

/**
 * @brief 注册USB主机库的客户端
 *
 * -此函数用于注册USB主机库的客户端
 * -注册客户端后，应重复调用其处理函数usb_host_client_handle_events（）
 *
 * @param[in] client_config 客户端配置
 * @param[out] client_hdl_ret 客户端句柄
 * @return 电子邮箱地址
 */
esp_err_t usb_host_client_register(const usb_host_client_config_t *client_config, usb_host_client_handle_t *client_hdl_ret);

/**
 * @brief 取消注册USB主机库客户端
 *
 * -此函数用于注销USB主机库的客户端
 * -客户端必须在尝试注销之前关闭所有以前打开的设备
 *
 * @param[in] client_hdl 客户端句柄
 * @return 电子邮箱地址
 */
esp_err_t usb_host_client_deregister(usb_host_client_handle_t client_hdl);

/**
 * @brief USB主机库客户端处理功能
 *
 * -此函数处理客户端的所有处理，并且应在循环中重复调用
 * -对于特定客户端，多个线程不应同时调用此函数
 *
 * @note 此功能可以阻止
 * @param[in] client_hdl 客户端句柄
 * @param[in] timeout_ticks 等待事件发生的超时（以滴答为单位）
 * @return 电子邮箱地址
 */
esp_err_t usb_host_client_handle_events(usb_host_client_handle_t client_hdl, TickType_t timeout_ticks);

/**
 * @brief 取消阻止客户端
 *
 * -如果客户机在usb_host_client_handle_events（）函数上被阻止，则该函数只需解除阻止。
 * -当需要解除阻止客户端以取消注册时，此功能非常有用。
 *
 * @param[in] client_hdl 客户端句柄
 * @return 电子邮箱地址
 */
esp_err_t usb_host_client_unblock(usb_host_client_handle_t client_hdl);

// -------------------------------------------------设备处理---------------------------------------------------

/**
 * @brief 打开设备
 *
 * -此功能允许客户端打开设备
 * -客户端在尝试使用设备之前必须先打开设备（例如，发送传输、设备请求等）
 *
 * @param[in] client_hdl 客户端句柄
 * @param[in] dev_addr 设备的地址
 * @param[out] dev_hdl_ret 设备的手柄
 * @return 电子邮箱地址
 */
esp_err_t usb_host_device_open(usb_host_client_handle_t client_hdl, uint8_t dev_addr, usb_device_handle_t *dev_hdl_ret);

/**
 * @brief 关闭设备
 *
 * -此功能允许客户端关闭设备
 * -客户端必须在设备使用完毕后关闭该设备（声明的接口也必须释放）
 * -客户端在注销之前必须关闭其打开的所有设备
 *
 * @note 此功能可以阻止
 * @param[in] client_hdl 客户端句柄
 * @param[in] dev_hdl 设备手柄
 * @return 电子邮箱地址
 */
esp_err_t usb_host_device_close(usb_host_client_handle_t client_hdl, usb_device_handle_t dev_hdl);

/**
 * @brief 指示在可能的情况下可以释放所有设备
 *
 * -此函数将所有设备标记为等待释放
 * -如果设备未被任何客户端打开，它将立即被释放
 * -如果至少有一个客户端打开了设备，则当最后一个客户端关闭该设备时，该设备将处于空闲状态。
 * -等待USB_HOST_LIB_handle_events（）设置USB_HOST_LB_EVENT_FLAGS_ALL_FREE标志，以便知道何时释放了所有设备
 * -在卸载USB主机库之前清理设备时，此功能非常有用
 *
 * @return
 *  -ESP_ERR_NOT_FINISHED：仍有一个或多个设备需要释放。等待USB_HOST_LB_EVENT_FLAGS_ALL_FREE事件
 *  -ESP_OK：所有设备都已释放（即，没有设备）
 *  -其他：错误
 */
esp_err_t usb_host_device_free_all(void);

/**
 * @brief 填写设备地址列表
 *
 * -此函数用连接设备的地址填充空列表
 * -然后可以在usb_host_Device_open（）中使用设备地址
 * -如果设备多于list_len，则此函数将只填充list_len个设备。
 *
 * @param[in] list_len 空列表的长度
 * @param[inout] dev_addr_list 要填写的空列表
 * @param[out] num_dev_ret 设备数量
 * @return 电子邮箱地址
 */
esp_err_t usb_host_device_addr_list_fill(int list_len, uint8_t *dev_addr_list, int *num_dev_ret);

// -------------------------------------------------设备请求---------------------------------------------------

// -------------------缓存的请求---------------------

/**
 * @brief 获取设备信息
 *
 * -此函数获取设备的一些基本信息
 * -在尝试获取其信息之前，必须先打开设备
 *
 * @note 此功能可以阻止
 * @param[in] dev_hdl 设备手柄
 * @param[out] dev_info 设备信息
 * @return 电子邮箱地址
 */
esp_err_t usb_host_device_info(usb_device_handle_t dev_hdl, usb_device_info_t *dev_info);

// -----------------------------------------------描述符请求-------------------------------------------------

// -----------------缓存描述符--------------------

/**
 * @brief 获取设备的设备描述符
 *
 * -客户端必须首先调用usb_host_device_open（）
 * -未发送控制传输。枚举时缓存设备的描述符
 * -此函数简单地返回指向缓存描述符的指针
 *
 * @note 未发送控制传输。枚举时缓存设备的描述符
 * @param[in] dev_hdl 设备手柄
 * @param[out] device_desc 设备描述符
 * @return 电子邮箱地址
 */
esp_err_t usb_host_get_device_descriptor(usb_device_handle_t dev_hdl, const usb_device_desc_t **device_desc);

/**
 * @brief 获取设备的活动配置描述符
 *
 * -客户端必须首先调用usb_host_device_open（）
 * -未发送控制传输。设备的活动配置描述符缓存在枚举上
 * -此函数简单地返回指向缓存描述符的指针
 *
 * @note 此功能可以阻止
 * @note 未发送控制传输。设备的活动配置描述符缓存在枚举上
 * @param[in] dev_hdl 设备手柄
 * @param[out] config_desc 配置描述符
 * @return 电子邮箱地址
 */
esp_err_t usb_host_get_active_config_descriptor(usb_device_handle_t dev_hdl, const usb_config_desc_t **config_desc);

// -----------------------------------------------接口功能-------------------------------------------------

/**
 * @brief 客户端声明设备接口的功能
 *
 * -客户端在尝试与其任何端点通信之前必须声明设备的接口
 * -一旦客户机声明了接口，任何其他客户机都不能声明该接口。
 *
 * @note 此功能可以阻止
 * @param[in] client_hdl 客户端句柄
 * @param[in] dev_hdl 设备手柄
 * @param[in] bInterfaceNumber 接口编号
 * @param[in] bAlternateSetting 接口备用设置编号
 * @return 电子邮箱地址
 */
esp_err_t usb_host_interface_claim(usb_host_client_handle_t client_hdl, usb_device_handle_t dev_hdl, uint8_t bInterfaceNumber, uint8_t bAlternateSetting);

/**
 * @brief 客户端释放先前声明的接口的函数
 *
 * -客户端应在不再需要与接口通信后释放设备的接口
 * -客户端必须释放其声称的设备的所有接口，然后才能关闭该设备
 *
 * @note 此功能可以阻止
 * @param[in] client_hdl 客户端句柄
 * @param[in] dev_hdl 设备手柄
 * @param[in] bInterfaceNumber 接口编号
 * @return 电子邮箱地址
 */
esp_err_t usb_host_interface_release(usb_host_client_handle_t client_hdl, usb_device_handle_t dev_hdl, uint8_t bInterfaceNumber);

/**
 * @brief 停止特定端点
 *
 * -设备必须已由客户端打开
 * -端点必须是客户端声明的接口的一部分
 * -一旦停止，必须使用usb_host_endpoint_clear（）清除端点，然后才能再次通信
 *
 * @note 此功能可以阻止
 * @param dev_hdl 设备手柄
 * @param bEndpointAddress 终结点地址
 * @return 电子邮箱地址
 */
esp_err_t usb_host_endpoint_halt(usb_device_handle_t dev_hdl, uint8_t bEndpointAddress);

/**
 * @brief 刷新特定端点
 *
 * -设备必须已由客户端打开
 * -端点必须是客户端声明的接口的一部分
 * -终结点必须已停止（可能是由于传输错误，或是usb_host_endpoint_halt（））
 * -刷新端点将导致取消排队的传输
 *
 * @note 此功能可以阻止
 * @param dev_hdl 设备手柄
 * @param bEndpointAddress 终结点地址
 * @return 电子邮箱地址
 */
esp_err_t usb_host_endpoint_flush(usb_device_handle_t dev_hdl, uint8_t bEndpointAddress);

/**
 * @brief 清除特定端点上的暂停
 *
 * -设备必须已由客户端打开
 * -端点必须是客户端声明的接口的一部分
 * -终结点必须已停止（可能是由于传输错误，或是usb_host_endpoint_halt（））
 * -如果端点有任何排队的传输，清除暂停将继续执行
 *
 * @note 此功能可以阻止
 * @param dev_hdl 设备手柄
 * @param bEndpointAddress 终结点地址
 * @return 电子邮箱地址
 */
esp_err_t usb_host_endpoint_clear(usb_device_handle_t dev_hdl, uint8_t bEndpointAddress);

// ------------------------------------------------异步I/O---------------------------------------------------

/**
 * @brief 分配转移对象
 *
 * -此函数用于分配传输对象
 * -每个传输对象在分配时都指定了固定大小的缓冲区
 * -传输对象可以无限期重复使用
 * -可以使用usb_host_transfer_submit（）或usb_host_transfer_subsmit_control（）提交传输
 *
 * @param[in] data_buffer_size 传输数据缓冲区的大小
 * @param[in] num_isoc_packets 传输中的同步数据包数（对于非同步传输，设置为0）
 * @param[out] transfer 传输对象
 * @return 电子邮箱地址
 */
esp_err_t usb_host_transfer_alloc(size_t data_buffer_size, int num_isoc_packets, usb_transfer_t **transfer);

/**
 * @brief 释放传输对象
 *
 * -释放以前使用usb_host_transfer_alloc（）分配的传输对象
 * -尝试释放时，传输不得在飞行中
 * -如果传递了NULL指针，该函数将只返回ESP_OK
 *
 * @param[in] transfer 传输对象
 * @return 电子邮箱地址
 */
esp_err_t usb_host_transfer_free(usb_transfer_t *transfer);

/**
 * @brief 提交非控制转让
 *
 * -向特定端点提交传输。设备和端点编号在传输中指定
 * -提交前必须正确初始化传输
 * -完成后，将从客户端的usb_host_client_handle_events（）函数调用传输的回调。
 *
 * @param[in] transfer 已初始化传输对象
 * @return 电子邮箱地址
 */
esp_err_t usb_host_transfer_submit(usb_transfer_t *transfer);

/**
 * @brief 提交控制转移
 *
 * -向特定设备提交控制传输。客户端必须先打开设备
 * -提交前必须正确初始化传输。传输数据缓冲区的前8个字节应包含控制传输设置包
 * -完成后，将从客户端的usb_host_client_handle_events（）函数调用传输的回调。
 *
 * @param[in] client_hdl 客户端句柄
 * @param[in] transfer 已初始化传输对象
 * @return 电子邮箱地址
 */
esp_err_t usb_host_transfer_submit_control(usb_host_client_handle_t client_hdl, usb_transfer_t *transfer);

#ifdef __cplusplus
}
#endif

