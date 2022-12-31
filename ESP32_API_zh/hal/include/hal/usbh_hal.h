/*
 * SPDX文件版权所有文本：2020-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
注：线程安全由HAL用户负责。除非另有规定，否则必须从关键部分调用所有USB主机HAL功能
*/

#include <stdlib.h>
#include <stddef.h>
#include "soc/usbh_struct.h"
#include "hal/usbh_ll.h"
#include "hal/usb_types_private.h"
#include "hal/assert.h"

// ------------------------------------------------宏和类型---------------------------------------------------

// ------------------常量/配置--------------------

#define USBH_HAL_DMA_MEM_ALIGN              512
#define USBH_HAL_FRAME_LIST_MEM_ALIGN       512     //帧列表需要512字节对齐（与数据簿相反）
#define USBH_HAL_NUM_CHAN                   8
#define USBH_HAL_XFER_DESC_SIZE             (sizeof(usbh_ll_dma_qtd_t))
#define USBH_HAL_FIFO_TOTAL_USABLE_LINES    200     //虽然我们有256行，但由于EPINFO_CTL，只有200行可用

/**
 * @brief FIFO大小配置结构
 */
typedef struct {
    uint32_t rx_fifo_lines;                 /**<RX FIFO的大小（以FIFO行数表示）*/
    uint32_t nptx_fifo_lines;               /**<按FIFO行数计算的非周期FIFO的大小*/
    uint32_t ptx_fifo_lines;                /**<以FIFO行数表示的周期FIFO的大小*/
} usbh_hal_fifo_config_t;

// ---------------------HAL事件------------------------

/**
 * @brief 主机端口HAL事件
 */
typedef enum {
    USBH_HAL_PORT_EVENT_NONE,               /**<未发生事件，或无法解码中断*/
    USBH_HAL_PORT_EVENT_CHAN,               /**<发生频道事件。改为调用通道事件处理程序*/
    USBH_HAL_PORT_EVENT_CONN,               /**<主机端口检测到连接*/
    USBH_HAL_PORT_EVENT_DISCONN,            /**<主机端口已断开连接*/
    USBH_HAL_PORT_EVENT_ENABLED,            /**<主机端口已启用（即，连接到已重置的设备。已开始发送SOF）*/
    USBH_HAL_PORT_EVENT_DISABLED,           /**<主机端口已禁用（没有更多SOF）。可能是由于禁用/重置请求或端口错误（例如，端口多路传输条件。请参阅USB2.0规范的11.8.1）*/
    USBH_HAL_PORT_EVENT_OVRCUR,             /**<主机端口遇到过电流情况*/
    USBH_HAL_PORT_EVENT_OVRCUR_CLR,         /**<主机端口已清除过电流条件*/
} usbh_hal_port_event_t;

/**
 * @brief 频道事件
 */
typedef enum {
    USBH_HAL_CHAN_EVENT_CPLT,               /**<通道已完成执行设置了USBH_HAL_XFER_DESC_FLAG_HOC标志的传输描述符。频道现在已停止*/
    USBH_HAL_CHAN_EVENT_ERROR,              /**<频道遇到错误。频道现在已停止。*/
    USBH_HAL_CHAN_EVENT_HALT_REQ,           /**<频道已按要求成功停止*/
    USBH_HAL_CHAN_EVENT_NONE,               /**<无事件（为内部处理运行中断）*/
} usbh_hal_chan_event_t;

// ---------------------HAL错误------------------------

/**
 * @brief 通道错误
 */
typedef enum {
    USBH_HAL_CHAN_ERROR_XCS_XACT = 0,       /**<过多（连续三次）事务错误（例如，无响应、CRC错误等*/
    USBH_HAL_CHAN_ERROR_BNA,                /**＜Buffer Not Available error（缓冲区不可用错误）（即，通道获取了非活动传输描述符）*/
    USBH_HAL_CHAN_ERROR_PKT_BBL,            /**<数据包多路转换器错误（数据包超过MPS）*/
    USBH_HAL_CHAN_ERROR_STALL,              /**<收到STALL响应*/
} usbh_hal_chan_error_t;

// -------------传输描述符相关---------------

/**
 * @brief 用于描述要填充的传输描述符类型的标志
 */
#define USBH_HAL_XFER_DESC_FLAG_IN          0x01    /**<表示此传输描述符为IN方向*/
#define USBH_HAL_XFER_DESC_FLAG_SETUP       0x02    /**<表示此传输描述符是OUT设置*/
#define USBH_HAL_XFER_DESC_FLAG_HOC         0x04    /**<表示此传输描述符完成后，通道将停止*/

/**
 * @brief 传输描述符的状态值
 *
 * 传输描述符的状态保持未执行状态，直到整个传输描述符完成（成功或错误）。因此，如果在传输描述符完成之前请求信道暂停，则传输描述符保持未执行状态。
 */
#define USBH_HAL_XFER_DESC_STS_SUCCESS      USBH_LL_QTD_STATUS_SUCCESS
#define USBH_HAL_XFER_DESC_STS_PKTERR       USBH_LL_QTD_STATUS_PKTERR
#define USBH_HAL_XFER_DESC_STS_BUFFER_ERR   USBH_LL_QTD_STATUS_BUFFER
#define USBH_HAL_XFER_DESC_STS_NOT_EXECUTED USBH_LL_QTD_STATUS_NOT_EXECUTED

// --------------------对象类型-----------------------

/**
 * @brief 端点特征结构
 */
typedef struct {
    union {
        struct {
            usb_priv_xfer_type_t type: 2;   /**<端点类型*/
            uint32_t bEndpointAddress: 8;   /**<端点地址（包含端点编号和方向）*/
            uint32_t mps: 11;               /**<最大数据包大小*/
            uint32_t dev_addr: 8;           /**<设备地址*/
            uint32_t ls_via_fs_hub: 1;      /**<端点位于通过FS集线器路由的LS设备上。设置此位将导致添加PREamble数据包*/
            uint32_t reserved2: 2;
        };
        uint32_t val;
    };
    struct {
        usb_hal_interval_t interval;        /**<终点的间隔*/
        uint32_t phase_offset_frames;       /**<帧数中的相位偏移*/
    } periodic;     /**<仅针对周期性（中断/同步）端点的特征*/
} usbh_hal_ep_char_t;

/**
 * @brief 通道对象
 */
typedef struct {
    //信道控制、状态和信息
    union {
        struct {
            uint32_t active: 1;             /**<调试位，指示信道是否已启用*/
            uint32_t halt_requested: 1;     /**<已请求暂停*/
            uint32_t reserved: 2;
            uint32_t chan_idx: 4;           /**<频道的索引编号*/
            uint32_t reserved24: 24;
        };
        uint32_t val;
    } flags;                                /**<关于频道状态和信息的标志*/
    usb_host_chan_regs_t *regs;             /**<指向通道寄存器集的指针*/
    usbh_hal_chan_error_t error;            /**<频道上发生的最后一个错误*/
    usb_priv_xfer_type_t type;              /**<通道的传输类型*/
    void *chan_ctx;                         /**<频道所有者的上下文变量*/
} usbh_hal_chan_t;

/**
 * @brief HAL上下文结构
 */
typedef struct {
    //上下文
    usbh_dev_t *dev;                            /**<指向DWC_OTG寄存器基址的指针*/
    //主机端口相关
    uint32_t *periodic_frame_list;              /**<指向调度帧列表的指针*/
    usb_hal_frame_list_len_t frame_list_len;    /**<定期调度帧列表的长度*/
    union {
        struct {
            uint32_t dbnc_lock_enabled: 1;      /**<已启用防抖锁定*/
            uint32_t fifo_sizes_set: 1;         /**<是否已设置FIFO大小*/
            uint32_t periodic_sched_enabled: 1; /**<启用定期调度（用于中断和同步传输）*/
            uint32_t reserved: 5;
            uint32_t reserved24: 24;
        };
        uint32_t val;
    } flags;
    //渠道相关
    struct {
        int num_allocd;                             /**<当前分配的频道数*/
        uint32_t chan_pend_intrs_msk;               /**<具有挂起中断的通道的位掩码*/
        usbh_hal_chan_t *hdls[USBH_HAL_NUM_CHAN];   /**<每个通道的句柄。如果尚未分配通道，则设置为NULL*/
    } channels;
} usbh_hal_context_t;

// --------------------------------------------------核心（全球）----------------------------------------------------

/**
 * @brief 初始化HAL上下文并检查DWC_OTG是否处于活动状态
 *
 * 条目：
 * -外围设备必须已重置且时钟未门控
 * -必须已配置USB PHY（内部或外部）和相关GPIO
 * -GPIO引脚已配置
 * -已分配中断但已禁用（在未知中断状态的情况下）退出：
 * -检查DWC_OTG是否处于活动状态，以及硬件版本/配置是否正确
 * -HAl上下文已初始化
 * -为某些全局和OTG寄存器（GAHBCFG和GUSBCFG）设置默认值
 * -单元掩码全局中断信号
 * -将DWC_OTG置于主机模式。要求延迟25ms才能生效。
 * -状态->USBH_HAL_PORT_State_OTG
 * -中断已清除。用户现在可以启用ISR
 *
 * @param[inout] hal HAL层的上下文
 */
void usbh_hal_init(usbh_hal_context_t *hal);

/**
 * @brief 取消初始化HAL上下文
 *
 * 条目：
 * -必须正确禁用所有通道，并处理所有未决事件退出：
 * -DWC_OTG全局中断已禁用
 * -HAL上下文已取消初始化
 *
 * @param hal HAL层的上下文
 */
void usbh_hal_deinit(usbh_hal_context_t *hal);

/**
 * @brief 向控制器发出软重置
 *
 * 当主机端口遇到错误事件或已断开连接时，应调用此命令。在调用此命令之前，用户负责安全释放所有通道，因为软重置将擦除所有主机端口和通道寄存器。此函数将导致主机端口恢复到调用usbh_hal_init（）后的状态。
 *
 * @note 这与USB总线重置无关。它只需重置外围设备
 *
 * @param hal HAL层的上下文
 */
void usbh_hal_core_soft_reset(usbh_hal_context_t *hal);

/**
 * @brief 设置FIFO大小
 *
 * 此函数将设置每个FIFO（RX FIFO、非周期性TX FIFO、周期性TX FIFOs）的大小，并且在分配信道之前必须至少调用一次。根据端点的类型（以及端点的MPS），可能需要再次调用此函数来调整FIFO的大小。如果动态调整FIFO的大小，则用户有责任确保调用此函数时没有活动通道。
 *
 * @note 所有FIFO的总大小必须小于或等于USBH_HAL_FIFO_TOTAL_USABLE_LINES
 * @note 端口重置后，FIFO大小寄存器将重置为其默认值，因此重置后必须再次调用此函数。
 *
 * @param hal HAL层的上下文
 * @param fifo_config FIFO配置
 */
void usbh_hal_set_fifo_size(usbh_hal_context_t *hal, const usbh_hal_fifo_config_t *fifo_config);

// ----------------------------------------------------主机端口------------------------------------------------------

// ------------------主机端口控制--------------------

/**
 * @brief 初始化主机端口
 *
 * -将启用主机端口的中断，允许发生端口和通道事件
 *
 * @param hal HAL层的上下文
 */
static inline void usbh_hal_port_init(usbh_hal_context_t *hal)
{
    //配置主机相关中断
    usbh_ll_haintmsk_dis_chan_intr(hal->dev, 0xFFFFFFFF);   //禁用所有通道的中断
    usb_ll_en_intrs(hal->dev, USB_LL_INTR_CORE_PRTINT | USB_LL_INTR_CORE_HCHINT);
}

/**
 * @brief 取消初始化主机端口
 *
 * -将禁用主机端口的中断，以防止发生进一步的端口和通道事件
 *
 * @param hal HAL层的上下文
 */
static inline void usbh_hal_port_deinit(usbh_hal_context_t *hal)
{
    //禁用主机端口和通道中断
    usb_ll_dis_intrs(hal->dev, USB_LL_INTR_CORE_PRTINT | USB_LL_INTR_CORE_HCHINT);
}

/**
 * @brief 切换主机端口的电源
 *
 * @param hal HAL层的上下文
 * @param power_on 是否打开或关闭端口
 */
static inline void usbh_hal_port_toggle_power(usbh_hal_context_t *hal, bool power_on)
{
    if (power_on) {
        usbh_ll_hprt_en_pwr(hal->dev);
    } else {
        usbh_ll_hprt_dis_pwr(hal->dev);
    }
}

/**
 * @brief 切换总线上的复位信号
 *
 * 复位信号应保持至少10ms进入：
 * -主机端口检测到设备连接或主机端口已启用退出：
 * -释放复位信号时，将生成USBH_HAL_PORT_EVENT_ENABLED
 *
 * @note 如果主机端口已启用，则发出重置将导致其禁用并生成USBH_HAL_port_EVENT_disabled事件。直到释放复位信号（从而生成USBH_HAL_port_EVENT_enabled事件），主机端口才会启用
 *
 * @param hal HAL层的上下文
 * @param enable 启用/禁用复位信号
 */
static inline void usbh_hal_port_toggle_reset(usbh_hal_context_t *hal, bool enable)
{
    HAL_ASSERT(hal->channels.num_allocd == 0);  //如果仍有分配的信道，则无法重置
    usbh_ll_hprt_set_port_reset(hal->dev, enable);
}

/**
 * @brief 启用主机端口
 *
 * 条目：
 * -重置退出后触发主机端口启用事件：
 * -主机端口已启用，可在分散/聚集DMA模式下运行
 * -DMA fifo大小已配置
 *
 * @param hal HAL层的上下文
 */
void usbh_hal_port_enable(usbh_hal_context_t *hal);

/**
 * @brief 禁用主机端口
 *
 * 出口：
 * -已触发主机端口禁用事件
 *
 * @param hal HAL层的上下文
 */
static inline void usbh_hal_port_disable(usbh_hal_context_t *hal)
{
    usbh_ll_hprt_port_dis(hal->dev);
}

/**
 * @brief 挂起主机端口
 *
 * @param hal HAL层的上下文
 */
static inline void usbh_hal_port_suspend(usbh_hal_context_t *hal)
{
    usbh_ll_hprt_set_port_suspend(hal->dev);
}

/**
 * @brief 切换总线上的恢复信号
 *
 * 主机应保持恢复信号至少20ms
 *
 * @note 如果发生远程唤醒事件，将自动驱动并清除恢复信号。
 *
 * @param hal HAL层的上下文
 * @param enable 启用/禁用恢复信号
 */
static inline void usbh_hal_port_toggle_resume(usbh_hal_context_t *hal, bool enable)
{
    if (enable) {
        usbh_ll_hprt_set_port_resume(hal->dev);
    } else {
        usbh_ll_hprt_clr_port_resume(hal->dev);
    }
}

/**
 * @brief 检查是否正在驱动恢复信号
 *
 * 如果发生远程唤醒事件，核心将在所需的时间内自动驱动并清除恢复信号。调用此函数以检查恢复信号是否已完成。
 *
 * @param hal HAL层的上下文
 * @return 真恢复信号仍在驱动
 * @return 假恢复信号不再被驱动
 */
static inline bool usbh_hal_port_check_resume(usbh_hal_context_t *hal)
{
    return usbh_ll_hprt_get_port_resume(hal->dev);
}

// ----------------主机端口调度-------------------

/**
 * @brief 设置定期调度帧列表
 *
 * @note 在尝试通过usbh_hal_chan_set_ep_char（）将任何通道配置为周期之前，必须调用此函数
 *
 * @param hal HAL层的上下文
 * @param frame_list 帧列表的基地址
 * @param frame_list_len 帧列表中的条目数（只能是8、16、32、64）
 */
static inline void usbh_hal_port_set_frame_list(usbh_hal_context_t *hal, uint32_t *frame_list, usb_hal_frame_list_len_t len)
{
    //清除并保存帧列表
    hal->periodic_frame_list = frame_list;
    hal->frame_list_len = len;
}

/**
 * @brief 获取定期调度帧列表的指针
 *
 * @param hal HAL层的上下文
 * @return uint32_t*周期调度帧列表的基地址
 */
static inline uint32_t *usbh_hal_port_get_frame_list(usbh_hal_context_t *hal)
{
    return hal->periodic_frame_list;
}

/**
 * @brief 启用定期计划
 *
 * @note 必须通过usbh_hal_port_set_frame_list（）设置周期帧列表。应在调用此函数之前设置
 * @note 激活任何周期性通道之前必须调用此函数
 *
 * @param hal HAL层的上下文
 */
static inline void usbh_hal_port_periodic_enable(usbh_hal_context_t *hal)
{
    HAL_ASSERT(hal->periodic_frame_list != NULL);
    usbh_ll_set_frame_list_base_addr(hal->dev, (uint32_t)hal->periodic_frame_list);
    usbh_ll_hcfg_set_num_frame_list_entries(hal->dev, hal->frame_list_len);
    usbh_ll_hcfg_en_perio_sched(hal->dev);
    hal->flags.periodic_sched_enabled = 1;
}

/**
 * @brief 禁用定期计划
 *
 * 禁用定期调度将节省一点DMA带宽（因为控制器将不再从帧列表中获取调度）。
 *
 * @note 在禁用周期性调度之前，用户有责任确保所有周期性频道都已安全停止。
 *
 * @param hal HAL层的上下文
 */
static inline void usbh_hal_port_periodic_disable(usbh_hal_context_t *hal)
{
    HAL_ASSERT(hal->flags.periodic_sched_enabled);
    usbh_ll_hcfg_dis_perio_sched(hal->dev);
    hal->flags.periodic_sched_enabled = 0;
}

static inline uint32_t usbh_hal_port_get_cur_frame_num(usbh_hal_context_t *hal)
{
    return usbh_ll_get_frm_num(hal->dev);
}

// ---------------主机端口状态/状态------------------

/**
 * @brief 检查设备当前是否连接到主机端口
 *
 * 该函数旨在在以下事件之一发生后调用，随后出现适当的反跳延迟
 * - USBH_HAL_PORT_EVENT_CONN
 * - USBH_HAL_PORT_EVENT_DISCONN
 *
 * @note 在通过usbh_hal_disable_debounce_lock（）禁用反跳锁之前，不会再次发生其他连接/断开事件
 *
 * @param hal HAL层的上下文
 * @return true设备已连接到主机端口
 * @return false设备未连接到主机端口
 */
static inline bool usbh_hal_port_check_if_connected(usbh_hal_context_t *hal)
{
    return usbh_ll_hprt_get_conn_status(hal->dev);
}

/**
 * @brief 检查连接到主机端口的设备的速度（LS/FS）
 *
 * @note 只有在确认设备已连接到主机端口后才能调用此函数
 *
 * @param hal HAL层的上下文
 * @return usb_priva_speed_t连接设备的速度（仅在esp32-s2和esp32-s3上为FS或LS）
 */
static inline usb_priv_speed_t usbh_hal_port_get_conn_speed(usbh_hal_context_t *hal)
{
    return usbh_ll_hprt_get_speed(hal->dev);
}

/**
 * @brief 禁用防抖锁
 *
 * 必须在调用usbh_hal_port_check_if_connected（）后调用此函数，并允许再次发生连接/断开事件。清除任何挂起的连接或断开中断。
 *
 * @param hal HAL层的上下文
 */
static inline void usbh_hal_disable_debounce_lock(usbh_hal_context_t *hal)
{
    hal->flags.dbnc_lock_enabled = 0;
    //清除连接和断开中断，以防再次触发
    usb_ll_intr_clear(hal->dev, USB_LL_INTR_CORE_DISCONNINT);
    usbh_ll_hprt_intr_clear(hal->dev, USBH_LL_INTR_HPRT_PRTCONNDET);
    //重新启用hprt（连接）和断开中断
    usb_ll_en_intrs(hal->dev, USB_LL_INTR_CORE_PRTINT | USB_LL_INTR_CORE_DISCONNINT);
}

// -----------------------------------------------------渠道-------------------------------------------------------

// -----------------渠道分配--------------------

/**
 * @brief 分配频道
 *
 * @param[in] hal HAL层的上下文
 * @param[inout] chan_obj 空通道对象
 * @param[in] chan_ctx 通道分配器的上下文变量
 * @return 真通道已成功分配
 * @return false分配通道失败
 */
bool usbh_hal_chan_alloc(usbh_hal_context_t *hal, usbh_hal_chan_t *chan_obj, void *chan_ctx);

/**
 * @brief 释放频道
 *
 * @param[in] hal HAL层的上下文
 * @param[in] chan_obj 通道对象
 */
void usbh_hal_chan_free(usbh_hal_context_t *hal, usbh_hal_chan_t *chan_obj);

// ----------------通道配置------------------

/**
 * @brief 获取通道的上下文变量
 *
 * @param[in] chan_obj 通道对象
 * @return void*通道的上下文变量
 */
static inline void *usbh_hal_chan_get_context(usbh_hal_chan_t *chan_obj)
{
    return chan_obj->chan_ctx;
}

/**
 * @brief 设置特定频道的端点信息
 *
 * 当通道将目标从一个EP切换到另一个EP时，应调用此命令
 *
 * @note 频道必须处于禁用状态才能更改其EP信息
 *
 * @param hal HAL层的上下文
 * @param chan_obj 通道对象
 * @param ep_char 端点特征
 */
void usbh_hal_chan_set_ep_char(usbh_hal_context_t *hal, usbh_hal_chan_t *chan_obj, usbh_hal_ep_char_t *ep_char);

/**
 * @brief 设置通道的方向
 *
 * 这是一个方便的功能，可以翻转频道的方向，而无需重新配置频道的所有EP信息。这主要用于控制传输。
 *
 * @note 仅当通道停止时才应调用此函数
 *
 * @param chan_obj 通道对象
 * @param is_in 方向是否为IN
 */
static inline void usbh_hal_chan_set_dir(usbh_hal_chan_t *chan_obj, bool is_in)
{
    //当通道仍处于活动状态或出错时，无法更改方向
    HAL_ASSERT(!chan_obj->flags.active);
    usbh_ll_chan_set_dir(chan_obj->regs, is_in);
}

/**
 * @brief 设置信道的下一个分组ID（例如，DATA0/DATA1）
 *
 * 当信道将目标从一个EP切换到另一个EP时，或者当改变控制转移的阶段时，应调用此命令
 *
 * @note 仅当通道处于停止状态时才应调用通道。
 *
 * @param chan_obj 通道对象
 * @param pid 下一个DATA数据包（DATA0或DATA1）的PID
 */
static inline void usbh_hal_chan_set_pid(usbh_hal_chan_t *chan_obj, int pid)
{
    //当通道仍处于活动状态或出错时，无法更改pid
    HAL_ASSERT(!chan_obj->flags.active);
    //更新通道对象并设置寄存器
    usbh_ll_chan_set_pid(chan_obj->regs, pid);
}

/**
 * @brief 获取通道的下一个PID
 *
 * 返回信道的下一个PID（DATA0或DATA1）。当需要保存管道的下一个PID时（例如，在通道上切换管道时），应使用此功能
 *
 * @param chan_obj 通道对象
 * @return uint32_t下一次传输的起始PID（DATA0或DATA1）
 */
static inline uint32_t usbh_hal_chan_get_pid(usbh_hal_chan_t *chan_obj)
{
    HAL_ASSERT(!chan_obj->flags.active);
    return usbh_ll_chan_get_pid(chan_obj->regs);
}

// -------------------通道控制---------------------

/**
 * @brief 激活频道
 *
 * 激活通道将导致通道开始执行传输描述符。
 *
 * @note 此函数只能在以前停止的通道上调用
 * @note 通道停止时将生成一个事件
 *
 * @param chan_obj 通道对象
 * @param xfer_desc_list 填充的传输描述符列表
 * @param desc_list_len 传输描述符列表长度
 * @param start_idx 列表中起始传输描述符的索引
 */
void usbh_hal_chan_activate(usbh_hal_chan_t *chan_obj, void *xfer_desc_list, int desc_list_len, int start_idx);

/**
 * @brief 获取当前传输描述符的索引
 *
 * @param chan_obj 通道对象
 * @return int描述符索引
 */
static inline int usbh_hal_chan_get_qtd_idx(usbh_hal_chan_t *chan_obj)
{
    return usbh_ll_chan_get_ctd(chan_obj->regs);
}

/**
 * @brief 请求暂停频道
 *
 * 应调用此函数以停止通道。如果通道已停止，则此函数将返回true。如果信道仍处于活动状态，此函数将返回false，用户必须等待USBH_HAL_CHAN_EVENT_HAL_REQ事件，然后才能将信道视为已停止。
 *
 * @note 当传输正在进行（即，信道处于活动状态）并且请求暂停时，在下一个USB数据包完成后，信道将停止。如果传输有更多待定数据包，则传输将仅标记为USBH_HAL_XFER_DESC_STS_NOT_EXECUTED。
 *
 * @param chan_obj 通道对象
 * @return true频道已停止
 * @return false请求暂停，等待USBH_HAL_CHAN_EVENT_HAL_REQ
 */
bool usbh_hal_chan_request_halt(usbh_hal_chan_t *chan_obj);

/**
 * @brief 指示端口错误后通道停止
 *
 * 当发生端口错误时（例如，磁盘连接、过电流）：
 * -任何先前激活的信道将保持激活状态（即，它们不会接收到信道中断）
 * -尝试使用usbh_hal_chan_request_halt（）禁用它们不会为ISOC通道生成中断（可能与定期调度有关）
 *
 * 然而，通道的启用位可以保留为1，因为在端口错误之后，无论如何都会进行软重置。此函数只需更新通道内部状态变量以指示其已停止（从而允许其释放）。
 *
 * @param chan_obj 通道对象
 */
static inline void usbh_hal_chan_mark_halted(usbh_hal_chan_t *chan_obj)
{
    chan_obj->flags.active = 0;
}

/**
 * @brief 获取频道错误
 *
 * @param chan_obj 通道对象
 * @return usbh_hal_chan_error_t通道遇到的错误类型
 */
static inline usbh_hal_chan_error_t usbh_hal_chan_get_error(usbh_hal_chan_t *chan_obj)
{
    return chan_obj->error;
}

// --------------------------------------------传输描述符列表-----------------------------------------------

/**
 * @brief 在传输描述符列表中填写单个条目
 *
 * -根据传输类型，单个传输描述符可能对应
 *      -传输的一个阶段（用于控制传输）
 *      -传输间隔的一帧（用于中断和等时）
 *      -整个传输（用于批量传输）
 * -检查各种USBH_HAL_XFER_DESC_FLAG_标志，以填充特定类型的描述符
 * -对于IN传输条目，设置USBH_HAL_XFER_DESC_FLAG_IN。传输大小也必须是端点MPS的整数倍
 *
 * @note 此功能不需要关键部分
 *
 * @param desc_list 传输描述符列表
 * @param desc_idx 传输描述符索引
 * @param xfer_data_buff 传输数据缓冲区
 * @param xfer_len 传输长度
 * @param flags 传输标志
 */
static inline void usbh_hal_xfer_desc_fill(void *desc_list, uint32_t desc_idx, uint8_t *xfer_data_buff, int xfer_len, uint32_t flags)
{
    usbh_ll_dma_qtd_t *qtd_list = (usbh_ll_dma_qtd_t *)desc_list;
    if (flags & USBH_HAL_XFER_DESC_FLAG_IN) {
        usbh_ll_set_qtd_in(&qtd_list[desc_idx],
                           xfer_data_buff, xfer_len,
                           flags & USBH_HAL_XFER_DESC_FLAG_HOC);
    } else {
        usbh_ll_set_qtd_out(&qtd_list[desc_idx],
                            xfer_data_buff,
                            xfer_len,
                            flags & USBH_HAL_XFER_DESC_FLAG_HOC,
                            flags & USBH_HAL_XFER_DESC_FLAG_SETUP);
    }
}

/**
 * @brief 清除传输描述符（将其所有字段设置为NULL）
 *
 * @param desc_list 传输描述符列表
 * @param desc_idx 传输描述符索引
 */
static inline void usbh_hal_xfer_desc_clear(void *desc_list, uint32_t desc_idx)
{
    usbh_ll_dma_qtd_t *qtd_list = (usbh_ll_dma_qtd_t *)desc_list;
    usbh_ll_set_qtd_null(&qtd_list[desc_idx]);
}

/**
 * @brief 分析传输描述符的结果
 *
 * @param desc_list 传输描述符列表
 * @param desc_idx 传输描述符索引
 * @param[out] xfer_rem_len 传输的剩余长度（字节）
 * @param[out] xfer_status 转移的状态
 *
 * @note 此功能不需要关键部分
 */
static inline void usbh_hal_xfer_desc_parse(void *desc_list, uint32_t desc_idx, int *xfer_rem_len, int *xfer_status)
{
    usbh_ll_dma_qtd_t *qtd_list = (usbh_ll_dma_qtd_t *)desc_list;
    usbh_ll_get_qtd_status(&qtd_list[desc_idx], xfer_rem_len, xfer_status);
    //清除QTD以防止再次读取
    usbh_ll_set_qtd_null(&qtd_list[desc_idx]);
}

// -------------------------------------------------事件处理----------------------------------------------------

/**
 * @brief 解码全局和主机端口中断
 *
 * -读取并清除全局和主机端口中断寄存器
 * -解码中断位以确定发生了什么主机端口事件
 *
 * @note 这应该是要运行的第一个中断解码功能
 *
 * @param hal HAL层的上下文
 * @return usbh_hal_port_event_t主机端口事件
 */
usbh_hal_port_event_t usbh_hal_decode_intr(usbh_hal_context_t *hal);

/**
 * @brief 获取具有挂起中断的下一个通道
 *
 * 如果没有通道挂起中断，此函数将返回NULL。如果一个或多个通道正在等待中断，此函数将返回通道的一个对象。重复调用此函数，直到返回NULL。
 *
 * @param hal HAL层的上下文
 * @return usbh_hal_chan_t*通道对象。如果没有通道挂起中断，则为NULL。
 */
usbh_hal_chan_t *usbh_hal_get_chan_pending_intr(usbh_hal_context_t *hal);

/**
 * @brief 解码特定频道的中断
 *
 * -读取并清除通道的中断寄存器
 * -返回该通道的相应事件
 *
 * @param chan_obj 通道对象
 * @note 如果主机端口出现错误（例如，突然断开连接或端口错误），任何活动通道都不会收到中断。必须手动停止每个活动通道。
 * @return usbh_hal_chan_event_t通道事件
 */
usbh_hal_chan_event_t usbh_hal_chan_decode_intr(usbh_hal_chan_t *chan_obj);

#ifdef __cplusplus
}
#endif

