/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <sys/queue.h>
#include "esp_err.h"
#include "usb_private.h"
#include "usb/usb_types_ch9.h"

// -------------------------------------------------宏类型（&T）----------------------------------------------------

// -----------------------州--------------------------

/**
 * @brief HCD端口的状态
 *
 * @note 端口可以被认为是包含单个端口的根集线器的抽象。
 * @note 这些状态大致符合USB2.0规范11.5.1中概述的端口状态。
 */
typedef enum {
    HCD_PORT_STATE_NOT_POWERED,     /**<端口未通电*/
    HCD_PORT_STATE_DISCONNECTED,    /**<端口已通电，但未连接任何设备*/
    HCD_PORT_STATE_DISABLED,        /**<设备已连接到端口，但尚未重置。未发送SOF/保活*/
    HCD_PORT_STATE_RESETTING,       /**<端口正在发出重置条件*/
    HCD_PORT_STATE_SUSPENDED,       /**<端口已挂起。*/
    HCD_PORT_STATE_RESUMING,        /**<端口正在发出恢复条件*/
    HCD_PORT_STATE_ENABLED,         /**<端口已启用。正在发送SOF/保活*/
    HCD_PORT_STATE_RECOVERY,        /**<端口需要从致命错误（端口错误、过电流或突然断开）中恢复*/
} hcd_port_state_t;

/**
 * @brief HCD管道的状态
 *
 * 活动：
 *  -管道能够传输数据。URB可以排队。
 *  -即使管道没有URB排队，它仍然可以处于活动状态。暂停：
 *  -管道上发生错误。URB将不再执行。
 *  -应使用HCD_PIPE_CMD_CLEAR命令清除暂停
 */
typedef enum {
    HCD_PIPE_STATE_ACTIVE,          /**<管道处于活动状态*/
    HCD_PIPE_STATE_HALTED,          /**<管道停止*/
} hcd_pipe_state_t;

// -----------------------事件--------------------------

/**
 * @brief HCD端口事件
 *
 * 在接收到端口事件时，应调用hcd_port_handle_event（）来处理该事件
 */
typedef enum {
    HCD_PORT_EVENT_NONE,            /**<未发生任何事件。或者上一事件不再有效*/
    HCD_PORT_EVENT_CONNECTION,      /**<设备已连接到端口*/
    HCD_PORT_EVENT_DISCONNECTION,   /**<检测到设备断开*/
    HCD_PORT_EVENT_ERROR,           /**<检测到端口错误。端口现在为HCD_Port_STATE_RECOVERY*/
    HCD_PORT_EVENT_OVERCURRENT,     /**<在端口上检测到过电流。端口现在为HCD_port_STATE_RECOVERY*/
} hcd_port_event_t;

/**
 * @brief HCD管道事件
 *
 * @note 管道错误事件将使管道进入HCD_Pipe_STATE_HALTED状态
 */
typedef enum {
    HCD_PIPE_EVENT_NONE,                    /**<管道没有事件（用于指示轮询时没有事件）*/
    HCD_PIPE_EVENT_URB_DONE,                /**<管道已完成URB。URB可以退出队列*/
    HCD_PIPE_EVENT_ERROR_XFER,              /**<过多（连续三次）事务错误（例如，无ACK、CRC错误等）*/
    HCD_PIPE_EVENT_ERROR_URB_NOT_AVAIL,     /**<URB不可用*/
    HCD_PIPE_EVENT_ERROR_OVERFLOW,          /**<收到的数据比请求的多。通常是数据包混淆错误（即，IN数据包已超过端点的MPS）*/
    HCD_PIPE_EVENT_ERROR_STALL,             /**<管道收到STALL响应*/
} hcd_pipe_event_t;

// ----------------------命令-------------------------

/**
 * @brief HCD端口命令
 */
typedef enum {
    HCD_PORT_CMD_POWER_ON,          /**<打开端口电源*/
    HCD_PORT_CMD_POWER_OFF,         /**<关闭端口电源。如果端口已启用，这将导致HCD_port_EVENT_UDDEN_DISCONN事件。如果端口被禁用，这将导致HCD_port_EVENT_DISCONNECTION事件。*/
    HCD_PORT_CMD_RESET,             /**<在端口上发出重置*/
    HCD_PORT_CMD_SUSPEND,           /**<暂停端口。必须停止所有管道*/
    HCD_PORT_CMD_RESUME,            /**<恢复端口*/
    HCD_PORT_CMD_DISABLE,           /**<禁用端口（停止SOF或保持活动）。所有管道必须停止。*/
} hcd_port_cmd_t;

/**
 * @brief HCD管道命令
 *
 * 管道命令表示USB2.0规范10.5.2.2.中概述的管道操作列表。
 */
typedef enum {
    HCD_PIPE_CMD_HALT,              /**<停止活动管道。当前正在执行的URB将被取消。排队的URB保持不变*/
    HCD_PIPE_CMD_FLUSH,             /**<只能在暂停时调用。将导致取消所有排队的URB*/
    HCD_PIPE_CMD_CLEAR,             /**<使暂停的管道再次激活。将执行任何排队的URB。*/
} hcd_pipe_cmd_t;

// --------------------对象类型-----------------------

/**
 * @brief 端口手柄类型
 */
typedef void * hcd_port_handle_t;

/**
 * @brief 管道手柄类型
 */
typedef void * hcd_pipe_handle_t;

/**
 * @brief 端口事件回调类型
 *
 * 此回调在发生端口事件时运行
 */
typedef bool (*hcd_port_callback_t)(hcd_port_handle_t port_hdl, hcd_port_event_t port_event, void *user_arg, bool in_isr);

/**
 * @brief 管道事件回调
 *
 * 此回调在管道事件发生时运行
 */
typedef bool (*hcd_pipe_callback_t)(hcd_pipe_handle_t pipe_hdl, hcd_pipe_event_t pipe_event, void *user_arg, bool in_isr);

typedef enum {
    HCD_PORT_FIFO_BIAS_BALANCED,    /**<RX、非周期性TX和周期性TX的平衡FIFO大小*/
    HCD_PORT_FIFO_BIAS_RX,          /**<偏向大型RX FIFO*/
    HCD_PORT_FIFO_BIAS_PTX,         /**<对周期性TX FIFO的偏差*/
} hcd_port_fifo_bias_t;

/**
 * @brief HCD配置结构
 */
typedef struct {
    int intr_flags;                         /**<HCD中断的中断标志*/
} hcd_config_t;

/**
 * @brief 端口配置结构
 */
typedef struct {
    hcd_port_fifo_bias_t fifo_bias;         /**<HCD端口内部FIFO偏置*/
    hcd_port_callback_t callback;           /**<HCD端口事件回调*/
    void *callback_arg;                     /**<HCD端口回调的用户参数*/
    void *context;                          /**<用于将端口与上层对象关联的上下文变量*/
} hcd_port_config_t;

/**
 * @brief 管道配置结构
 *
 * @note 如果不需要回调（例如，以轮询方式使用HCD），则可以将回调设置为NULL。
 */
typedef struct {
    hcd_pipe_callback_t callback;           /**<HCD管道事件ISR回调*/
    void *callback_arg;                     /**<HCD管道回调的用户参数*/
    void *context;                          /**<用于将管道与上层对象关联的上下文变量*/
    const usb_ep_desc_t *ep_desc;           /**<指向管道端点描述符的指针*/
    usb_speed_t dev_speed;                  /**<设备速度*/
    uint8_t dev_addr;                       /**<管道的设备地址*/
} hcd_pipe_config_t;

// ---------------------------------------------主机控制器驱动程序------------------------------------------------

/**
 * @brief 安装主机控制器驱动程序
 *
 * -为HCD和基础端口分配内存和中断资源
 *
 * @note 必须在调用任何其他HCD函数之前调用此函数
 * @note 在调用此功能之前，主机控制器必须已取消时钟门控并重置。必须已配置USB PHY（内部或外部以及相关GPIO）。
 *
 * @param config HCD配置
 * @retval ESP_OK:HCD已成功安装
 * @retval ESP_ERR_NO_MEM:内存不足
 * @retval ESP_ERR_INVALID_STATE:HCD已安装
 * @retval ESP_ERR_NOT_FOUND:HCD无法分配中断
 * @retval ESP_ERR_INVALID_ARG:参数无效
 */
esp_err_t hcd_install(const hcd_config_t *config);

/**
 * @brief 卸载HCD
 *
 * 卸载HCD之前，应满足以下条件：
 * -必须取消初始化所有端口，释放所有管道
 *
 * @note 此功能只会释放HCD使用的资源。不会禁用基础主机控制器和USB PHY。
 *
 * @retval ESP_OK:HCD已成功卸载
 * @retval ESP_ERR_INVALID_STATE:HCD未处于要卸载的正确状态
 */
esp_err_t hcd_uninstall(void);

// ----------------------------------------------------HCD端口-------------------------------------------------------

/**
 * @brief 初始化HCD的特定端口
 *
 * 端口初始化后，将进入HCD_port_STATE_NOT_POWERED状态。
 *
 * @note 主机控制器只有一个端口，因此唯一有效的端口号为1
 *
 * @param[in] port_number 端口号
 * @param[in] port_config 端口配置
 * @param[out] port_hdl 端口手柄
 * @retval ESP_OK：端口已启用
 * @retval ESP_ERR_NO_MEM:内存不足
 * @retval ESP_ERR_INVALID_STATE:端口已启用
 * @retval ESP_ERR_NOT_FOUND：未找到端口号
 * @retval ESP_ERR_INVALID_ARG:参数无效
 */
esp_err_t hcd_port_init(int port_number, const hcd_port_config_t *port_config, hcd_port_handle_t *port_hdl);

/**
 * @brief 取消初始化特定端口
 *
 * 必须将端口置于HCD_port_STATE_NOT_POWERED或HCD_port_STATE_RECOVERY状态，才能对其进行去初始化。
 *
 * @param port_hdl 端口手柄
 * @retval ESP_OK：端口已禁用
 * @retval ESP_ERR_INVALID_STATE:端口未处于禁用状态（未通电）
 */
esp_err_t hcd_port_deinit(hcd_port_handle_t port_hdl);

/**
 * @brief 执行端口命令
 *
 * 调用此函数来操作端口（例如，打开端口、发送重置等）。调用此函数时必须满足以下条件：
 * -端口处于命令的正确状态（例如，必须挂起端口才能使用恢复命令）
 * -端口没有任何挂起的事件
 *
 * @note 此函数在内部受到互斥锁的保护。如果多个线程调用此函数，则此函数将被阻塞。
 * @note 该功能可以阻止
 * @note 对于一些涉及阻塞延迟的命令（例如，重置和恢复），如果端口的状态发生意外变化（例如，恢复期间的断开连接），此函数将返回ESP_ERR_INVALID_RESPONSE。
 *
 * @param port_hdl 端口手柄
 * @param command HCD端口命令
 * @retval ESP_OK：命令成功执行
 * @retval ESP_ERR_INVALID_STATE:尚未满足调用此函数的条件
 * @retval ESP_ERR_INVALID_RESPONSE：由于端口状态更改，命令不再有效
 */
esp_err_t hcd_port_command(hcd_port_handle_t port_hdl, hcd_port_cmd_t command);

/**
 * @brief 获取端口的当前状态
 *
 * @param port_hdl 端口手柄
 * @return hcd_port_state_t当前端口状态
 */
hcd_port_state_t hcd_port_get_state(hcd_port_handle_t port_hdl);

/**
 * @brief 获取端口的速度
 *
 * 端口的速度由连接到它的设备的速度决定。
 *
 * @note 此功能仅在设备直接连接到端口并已重置后才有效
 *
 * @param[in port_hdl 端口手柄
 * @param[out] speed 端口的速度
 * @retval 获得ESP_OK设备速度
 * @retval ESP_ERR_INVALID_STATE:没有有效的设备连接到端口
 * @retval ESP_ERR_INVALID_ARG:参数无效
 */
esp_err_t hcd_port_get_speed(hcd_port_handle_t port_hdl, usb_speed_t *speed);

/**
 * @brief 处理端口事件
 *
 * 当发生端口事件（如回调所示）时，应调用此函数来处理此事件。在尝试执行端口命令之前，应始终处理端口的事件。注意，实际处理的事件可能与回调中反映的事件不同。
 *
 * 如果端口没有事件，则此函数将返回HCD_port_EVENT_NONE。
 *
 * @note 如果不使用回调，也可以以轮询方式使用此函数来重复检查和处理端口的事件。
 * @note 此函数在内部受到互斥锁的保护。如果多个线程调用此函数，则此函数将被阻塞。
 *
 * @param port_hdl 端口手柄
 * @return hcd_port_event_t已处理的端口事件
 */
hcd_port_event_t hcd_port_handle_event(hcd_port_handle_t port_hdl);

/**
 * @brief 在发生严重错误后恢复端口
 *
 * 端口必须处于HCD_port_STATE_RECOVERY状态才能被调用。恢复端口将涉及在基础USB控制器上发出软重置。端口将返回到HCD_port_STATE_NOT_POWERED状态。
 *
 * @param port_hdl 端口手柄
 * @retval ESP_OK端口已成功恢复
 * @retval ESP_ERR_INVALID_STATE端口未处于HCD_Port_STATE_RECOVERY状态
 */
esp_err_t hcd_port_recover(hcd_port_handle_t port_hdl);

/**
 * @brief 获取端口的上下文变量
 *
 * @param port_hdl 端口手柄
 * @return void*上下文变量
 */
void *hcd_port_get_context(hcd_port_handle_t port_hdl);

/**
 * @brief 设置HCD端口内部FIFO的偏差
 *
 * @note 只有满足以下条件时才能调用此函数：
 *  -端口已初始化
 *  -端口没有任何挂起的事件
 *  -端口没有任何分配的管道
 *
 * @param port_hdl 端口手柄
 * @param bias Fifo偏差
 * @retval 成功设置ESP_OK FIFO大小
 * @retval ESP_ERR_INVALID_STATE要设置的FIFO大小的状态不正确
 */
esp_err_t hcd_port_set_fifo_bias(hcd_port_handle_t port_hdl, hcd_port_fifo_bias_t bias);

// ---------------------------------------------------HCD管道-------------------------------------------------------

/**
 * @brief 分配管道
 *
 * 分配管道时，HCD将评估是否有足够的资源（即总线时间和控制器通道）。如果足够，将分配管道。
 *
 * @note 在分配管道之前，主机端口必须处于启用状态
 *
 * @param[in] port_hdl 该管道将通过的端口的手柄
 * @param[in] pipe_config 管道配置
 * @param[out] pipe_hdl 管道手柄
 *
 * @retval ESP_OK:已成功分配管道
 * @retval ESP_ERR_NO_MEM:内存不足
 * @retval ESP_ERR_INVALID_ARG:参数无效
 * @retval ESP_ERR_INVALID_STATE:主机端口的状态不正确，无法分配管道
 * @retval ESP_ERR_NOT_SUPPORTED:无法支持管道的配置
 */
esp_err_t hcd_pipe_alloc(hcd_port_handle_t port_hdl, const hcd_pipe_config_t *pipe_config, hcd_pipe_handle_t *pipe_hdl);

/**
 * @brief 释放管道
 *
 * 释放HCD管道使用的资源。调用此函数后应丢弃管道的句柄。在释放管道之前，管道必须处于以下状态：
 * -所有URB已退出队列
 *
 * @param pipe_hdl 管道手柄
 *
 * @retval ESP_OK:成功释放管道
 * @retval ESP_ERR_INVALID_STATE:管道未处于要释放的状态
 */
esp_err_t hcd_pipe_free(hcd_pipe_handle_t pipe_hdl);

/**
 * @brief 更新管道的最大数据包大小
 *
 * 此函数旨在在枚举期间在默认管道上调用，以更新管道的最大数据包大小。只能在满足以下条件的管道上调用此函数：
 * -管道当前未处理命令
 * -管道没有任何排队的URB
 * -无法重置端口
 *
 * @param pipe_hdl 管道手柄
 * @param mps 新的最大数据包大小
 *
 * @retval ESP_OK:管道已成功更新
 * @retval ESP_ERR_INVALID_STATE:管道未处于要更新的状态
 */
esp_err_t hcd_pipe_update_mps(hcd_pipe_handle_t pipe_hdl, int mps);

/**
 * @brief 更新管道的设备地址
 *
 * 此函数旨在在枚举期间在默认管道上调用，以更新管道的设备地址。只能在满足以下条件的管道上调用此函数：
 * -管道当前未处理命令
 * -管道没有任何排队的URB
 * -无法重置端口
 *
 * @param pipe_hdl 管道手柄
 * @param dev_addr 新设备地址
 *
 * @retval ESP_OK:管道已成功更新
 * @retval ESP_ERR_INVALID_STATE:管道未处于要更新的状态
 */
esp_err_t hcd_pipe_update_dev_addr(hcd_pipe_handle_t pipe_hdl, uint8_t dev_addr);

/**
 * @brief 更新管道的回调
 *
 * 此函数旨在在枚举结束时在默认管道上调用，以切换到处理常规控制传输完成的回调。
 * -管道当前未处理命令
 * -管道没有任何排队的URB
 * -无法重置端口
 *
 * @param pipe_hdl 管道手柄
 * @param callback 回调
 * @param user_arg 回调参数
 * @return 电子邮箱地址
 */
esp_err_t hcd_pipe_update_callback(hcd_pipe_handle_t pipe_hdl, hcd_pipe_callback_t callback, void *user_arg);

/**
 * @brief 通过运行时重置使管道持久
 *
 * 通常，当调用HCD_PORT_CMD_RESET时，所有管道都应该已被释放。但是，在某些情况下（例如在枚举期间），管道必须通过重置保持。此函数将管道标记为持久性，使其能够在重置后继续运行。当调用HCD_PORT_CMD_RESET时，管道可以在重置后继续使用。
 *
 * @param pipe_hdl 管道手柄
 * @retval ESP_OK:管道已成功标记为永久性
 * @retval ESP_ERR_INVALID_STATE:管道未处于永久状态
 */
esp_err_t hcd_pipe_set_persist_reset(hcd_pipe_handle_t pipe_hdl);

/**
 * @brief 从管道的句柄获取管道的上下文变量
 *
 * @param pipe_hdl 管道手柄
 * @return void*上下文变量
 */
void *hcd_pipe_get_context(hcd_pipe_handle_t pipe_hdl);

/**
 * @brief 获取管道的当前状态
 *
 * @param pipe_hdl 管道手柄
 * @return hcd_pipe_state_t管道的当前状态
 */
hcd_pipe_state_t hcd_pipe_get_state(hcd_pipe_handle_t pipe_hdl);

/**
 * @brief 在特定管道上执行命令
 *
 * 管道命令允许操作管道（例如清除暂停、退出所有URB等）
 *
 * @note 此功能可以阻止
 *
 * @param pipe_hdl 管道手柄
 * @param command “管道”命令
 * @retval ESP_OK：命令成功执行
 * @retval ESP_ERR_INVALID_STATE:管道的状态/条件不正确，无法执行命令
 */
esp_err_t hcd_pipe_command(hcd_pipe_handle_t pipe_hdl, hcd_pipe_cmd_t command);

/**
 * @brief 获取管道上发生的最后一个事件
 *
 * 此函数允许管道轮询事件（即不使用回调时）。获取事件后，此函数将管道的最后一个事件重置为HCD_pipe_event_NONE。
 *
 * @param pipe_hdl 管道手柄
 * @return hcd_pipe_event_t发生的最后一个管道事件
 */
hcd_pipe_event_t hcd_pipe_get_event(hcd_pipe_handle_t pipe_hdl);

// ----------------------------------------------------HCD市区-------------------------------------------------------

/**
 * @brief 将URB排队到特定管道
 *
 * 必须满足以下条件，URB才能入队：
 * -URB已正确初始化（数据缓冲区和传输长度已设置）
 * -URB必须尚未入队
 * -管道必须处于HCD_pipe_STATE_ACTIVE状态
 * -管道无法执行命令
 *
 * @param pipe_hdl 管道手柄
 * @param urb 要排队的URB
 * @retval ESP_OK:URB成功入队
 * @retval ESP_ERR_INVALID_STATE:未满足将URB入队的条件
 */
esp_err_t hcd_urb_enqueue(hcd_pipe_handle_t pipe_hdl, urb_t *urb);

/**
 * @brief 将URB从特定管道中取消排队
 *
 * 管道收到HCD_pipe_EVENT_URB_DONE事件后，应在管道上调用此函数。如果一个管道有多个可以出列的URB，则应重复调用此函数，直到所有URB都出列。如果管道没有更多的URB要出列，则此函数将返回NULL。
 *
 * @param pipe_hdl 管道手柄
 * @return urb_t*已出列的urb，如果没有更多的urb要出列，则为NULL
 */
urb_t *hcd_urb_dequeue(hcd_pipe_handle_t pipe_hdl);

/**
 * @brief 中止排队的URB
 *
 * 此函数将尝试中止已排队的URB。如果URB尚未执行，它将被“取消”，然后可以退出队列。如果URB当前正在飞行或已经完成，则URB将不受此功能的影响。
 *
 * @param urb URB中止
 * @retval ESP_OK:URB成功中止，或未受此函数影响
 * @retval ESP_ERR_INVALID_STATE:URB从未入队
 */
esp_err_t hcd_urb_abort(urb_t *urb);

#ifdef __cplusplus
}
#endif

