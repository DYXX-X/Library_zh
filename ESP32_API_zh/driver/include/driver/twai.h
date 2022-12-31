/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "soc/soc_caps.h"
#if SOC_TWAI_SUPPORTED

#include "freertos/FreeRTOS.h"
#include "esp_types.h"
#include "esp_intr_alloc.h"
#include "esp_err.h"
#include "gpio.h"
#include "hal/twai_types.h"

/* --------------------默认初始值设定项和标志-----------------------*/
/**@秒*/    //Doxy命令从文档中隐藏预处理器定义
/**
 * @brief 常规配置结构的初始化器宏。
 *
 * 该初始化器宏允许配置TX GPIO、RX GPIO和操作模式。为常规配置结构的其他成员分配默认值。
 */
#define TWAI_GENERAL_CONFIG_DEFAULT(tx_io_num, rx_io_num, op_mode) {.mode = op_mode, .tx_io = tx_io_num, .rx_io = rx_io_num,        \
                                                                    .clkout_io = TWAI_IO_UNUSED, .bus_off_io = TWAI_IO_UNUSED,      \
                                                                    .tx_queue_len = 5, .rx_queue_len = 5,                           \
                                                                    .alerts_enabled = TWAI_ALERT_NONE,  .clkout_divider = 0,        \
                                                                    .intr_flags = ESP_INTR_FLAG_LEVEL1}

/**
 * @brief   警报标志
 *
 * 以下标志表示TWAI驱动程序中可用的各种警报。这些标志可以在配置/重新配置警报或调用twai_read_alerts（）时使用。
 *
 * @note    TWAI_ALERT_AND_LOG标志不是实际警报，但会将TWAI驱动程序配置为在启用警报发生时登录到UART。
 */
#define TWAI_ALERT_TX_IDLE                  0x00000001  /**<警报（1）：没有更多消息要发送*/
#define TWAI_ALERT_TX_SUCCESS               0x00000002  /**<警报（2）：上次传输成功*/
#define TWAI_ALERT_RX_DATA                  0x00000004  /**<警报（4）：已接收帧并将其添加到RX队列*/
#define TWAI_ALERT_BELOW_ERR_WARN           0x00000008  /**<警报（8）：两个错误计数器都已降至错误警告限制以下*/
#define TWAI_ALERT_ERR_ACTIVE               0x00000010  /**<警报（16）：TWAI控制器已激活错误*/
#define TWAI_ALERT_RECOVERY_IN_PROGRESS     0x00000020  /**<警报（32）：TWAI控制器正在进行总线恢复*/
#define TWAI_ALERT_BUS_RECOVERED            0x00000040  /**<Alert（64）：TWAI控制器已成功完成总线恢复*/
#define TWAI_ALERT_ARB_LOST                 0x00000080  /**<Alert（128）：上一次传输丢失仲裁*/
#define TWAI_ALERT_ABOVE_ERR_WARN           0x00000100  /**<Alert（256）：一个错误计数器已超过错误警告限制*/
#define TWAI_ALERT_BUS_ERROR                0x00000200  /**<Alert（512）：总线上发生了（Bit、Stuff、CRC、Form、ACK）错误*/
#define TWAI_ALERT_TX_FAILED                0x00000400  /**<警报（1024）：上一次传输失败（对于单次传输）*/
#define TWAI_ALERT_RX_QUEUE_FULL            0x00000800  /**<警报（2048）：RX队列已满，导致帧丢失*/
#define TWAI_ALERT_ERR_PASS                 0x00001000  /**<警报（4096）：TWAI控制器已变为被动错误*/
#define TWAI_ALERT_BUS_OFF                  0x00002000  /**<警报（8192）：发生总线关闭情况。TWAI控制器不能再影响总线*/
#define TWAI_ALERT_RX_FIFO_OVERRUN          0x00004000  /**<警报（16384）：发生RX FIFO超限*/
#define TWAI_ALERT_TX_RETRIED               0x00008000  /**<警报（32768）：由于错误的解决方法，消息传输被取消并重试*/
#define TWAI_ALERT_PERIPH_RESET             0x00010000  /**<警报（65536）：TWAI控制器已重置*/
#define TWAI_ALERT_ALL                      0x0001FFFF  /**＜位掩码，用于在配置期间启用所有警报*/
#define TWAI_ALERT_NONE                     0x00000000  /**＜配置期间禁用所有警报的位掩码*/
#define TWAI_ALERT_AND_LOG                  0x00020000  /**＜Bit mask（位掩码），以便在警报发生时也记录警报。请注意，如果启用了CONFIG_TWAI_ISR_IN_IRAM，则禁用ISR日志记录（请参阅文档）。*/

/**@结束秒*/

#define TWAI_IO_UNUSED                   ((gpio_num_t) -1)   /**<将GPIO标记为TWAI配置中未使用*/

/* -----------------------枚举和结构定义---------------------*/

/**
 * @brief   TWAI驱动程序状态
 */
typedef enum {
    TWAI_STATE_STOPPED,             /**<停止状态。TWAI控制器不会参与任何TWAI总线活动*/
    TWAI_STATE_RUNNING,             /**<运行状态。TWAI控制器可以发送和接收消息*/
    TWAI_STATE_BUS_OFF,             /**<总线关闭状态。TWAI控制器在恢复之前无法参与总线活动*/
    TWAI_STATE_RECOVERING,          /**<恢复状态。TWAI控制器正在进行总线恢复*/
} twai_state_t;

/**
 * @brief   TWAI驱动程序的一般配置结构
 *
 * @note    宏初始化器可用于此结构
 */
typedef struct {
    twai_mode_t mode;               /**<TWAI控制器模式*/
    gpio_num_t tx_io;               /**<发送GPIO编号*/
    gpio_num_t rx_io;               /**<接收GPIO编号*/
    gpio_num_t clkout_io;           /**<CLKOUT GPIO编号（可选，如果未使用，则设置为-1）*/
    gpio_num_t bus_off_io;          /**<总线关闭指示器GPIO编号（可选，如果未使用，则设置为-1）*/
    uint32_t tx_queue_len;          /**<TX队列可容纳的消息数（设置为0以禁用TX队列）*/
    uint32_t rx_queue_len;          /**<RX队列可容纳的消息数*/
    uint32_t alerts_enabled;        /**<要启用的警报位字段（请参阅文档）*/
    uint32_t clkout_divider;        /**<CLKOUT除法器。可以是1或2到14之间的任何偶数（可选，如果未使用，则设置为0）*/
    int intr_flags;                 /**<中断标志，用于设置驱动程序ISR的优先级。请注意，要使用ESP_INTR_FLAG_IRAM，应首先启用CONFIG_TWAI_IR_IN_IRAM选项。*/
} twai_general_config_t;

/**
 * @brief   存储TWAI驱动程序状态信息的结构
 */
typedef struct {
    twai_state_t state;             /**<TWAI控制器的当前状态（停止/运行/总线关闭/恢复）*/
    uint32_t msgs_to_tx;            /**<排队等待传输或等待传输完成的消息数*/
    uint32_t msgs_to_rx;            /**<RX队列中等待读取的消息数*/
    uint32_t tx_error_counter;      /**<传输错误计数器的当前值*/
    uint32_t rx_error_counter;      /**<接收错误计数器的当前值*/
    uint32_t tx_failed_count;       /**<传输失败的消息数*/
    uint32_t rx_missed_count;       /**<由于RX队列已满而丢失的消息数（或错误解决方法，如果启用）*/
    uint32_t rx_overrun_count;      /**<由于RX FIFO超限而丢失的消息数*/
    uint32_t arb_lost_count;        /**<仲裁丢失的实例数*/
    uint32_t bus_error_count;       /**<发生总线错误的实例数*/
} twai_status_info_t;

/* ------------------------------公共API------------------------------*/

/**
 * @brief   安装TWAI驱动程序
 *
 * 此功能使用三种配置结构安装TWAI驱动程序。运行此功能后，将分配所需的内存，并将TWAI驱动程序置于停止状态。
 *
 * @param[in]   g_config    一般配置结构
 * @param[in]   t_config    定时配置结构
 * @param[in]   f_config    过滤器配置结构
 *
 * @note    宏初始化器可用于配置结构（请参阅文档）
 *
 * @note    要重新安装TWAI驱动程序，请首先调用TWAI_driver_uninstall（）
 *
 * @return
 *      -ESP_OK:已成功安装TWAI驱动程序
 *      -ESP_ERR_INVALID_ARG:参数无效
 *      -ESP_ERR_NO_MEM:内存不足
 *      -ESP_ERR_INVALID_STATE:驱动程序已安装
 */
esp_err_t twai_driver_install(const twai_general_config_t *g_config, const twai_timing_config_t *t_config, const twai_filter_config_t *f_config);

/**
 * @brief   卸载TWAI驱动程序
 *
 * 此函数卸载TWAI驱动程序，释放驱动程序使用的内存。只有当驾驶员处于停止状态或总线关闭状态时，才能调用此功能。
 *
 * @warning 应用程序必须确保在调用此功能时，TX/RX队列或警报上没有任务被阻止。
 *
 * @return
 *      -ESP_OK:已成功卸载TWAI驱动程序
 *      -ESP_ERR_INVALID_STATE:驱动程序未处于停止/总线关闭状态，或未安装
 */
esp_err_t twai_driver_uninstall(void);

/**
 * @brief   启动TWAI驱动程序
 *
 * 此功能启动TWAI驱动程序，使TWAI驱动处于运行状态。这允许TWAI驱动程序参与TWAI总线活动，例如发送/接收消息。TX和RX队列在此功能中重置，清除任何未读或待传输的消息。只有当TWAI驱动程序处于停止状态时，才能调用此函数。
 *
 * @return
 *      -ESP_OK:TWAI驱动程序现在正在运行
 *      -ESP_ERR_INVALID_STATE:驱动程序未处于停止状态或未安装
 */
esp_err_t twai_start(void);

/**
 * @brief   停止TWAI驱动程序
 *
 * 此函数将停止TWAI驱动程序，在调用TWAI_start（）之前，阻止发送或接收任何进一步的消息。TX队列中的任何消息都将被清除。调用此函数后，应用程序应读取RX队列中的任何消息。只有当TWAI驱动程序处于运行状态时，才能调用此函数。
 *
 * @warning 当前在TWAI总线上发送/接收的消息将立即停止。这可能会导致其他TWAI节点将未完成的消息解释为错误。
 *
 * @return
 *      -ESP_OK:TWAI驱动程序现在已停止
 *      -ESP_ERR_INVALID_STATE:驱动程序未处于运行状态或未安装
 */
esp_err_t twai_stop(void);

/**
 * @brief   发送TWAI消息
 *
 * 此功能将TWAI消息排队以进行传输。如果没有其他消息排队等待传输，传输将立即开始。如果TX队列已满，此函数将阻塞，直到有更多空间可用或超时。如果TX队列被禁用（TX队列长度在配置中为0），如果另一条消息正在传输，则此函数将立即返回。只有当TWAI驱动程序处于运行状态时才能调用此函数，并且不能在“仅侦听模式”下调用此函数。
 *
 * @param[in]   message         要发送的消息
 * @param[in]   ticks_to_wait   TX队列上要阻止的FreeRTOS节拍数
 *
 * @note    此功能不能保证传输成功。TX_SUCCESS/TX_FAILED警报可用于在传输成功/失败时向应用程序发出警报。
 *
 * @note    TX_IDLE警报可用于在没有其他消息等待传输时向应用程序发出警报。
 *
 * @return
 *      -ESP_OK:传输已成功排队/启动
 *      -ESP_ERR_INVALID_ARG:参数无效
 *      -ESP_ERR_TIMEOUT：等待TX队列上的空间超时
 *      -ESP_FAIL:TX队列已禁用，当前正在发送另一条消息
 *      -ESP_ERR_INVALID_STATE:TWAI驱动程序未处于运行状态或未安装
 *      -ESP_ERR_NOT_SUPPORTED：仅侦听模式不支持传输
 */
esp_err_t twai_transmit(const twai_message_t *message, TickType_t ticks_to_wait);

/**
 * @brief   接收TWAI消息
 *
 * 此函数从RX队列接收消息。消息结构的标志字段将指示接收的消息类型。如果RX队列中没有消息，此函数将阻止
 *
 * @param[out]  message         收到的消息
 * @param[in]   ticks_to_wait   RX队列上要阻止的FreeRTOS节拍数
 *
 * @warning 应检查接收消息的标志字段，以确定接收消息是否包含任何数据字节。
 *
 * @return
 *      -ESP_OK:从RX队列成功接收到消息
 *      -ESP_ERR_TIMEOUT:等待消息超时
 *      -ESP_ERR_INVALID_ARG:参数无效
 *      -ESP_ERR_INVALID_STATE:未安装TWAI驱动程序
 */
esp_err_t twai_receive(twai_message_t *message, TickType_t ticks_to_wait);

/**
 * @brief   读取TWAI驱动程序警报
 *
 * 此功能将读取TWAI驱动程序发出的警报。如果调用此函数时未发出警报，则此函数将一直阻塞，直到警报发生或超时。
 *
 * @param[out]  alerts          引发警报的位字段（有关警报标志，请参阅文档）
 * @param[in]   ticks_to_wait   要阻止警报的FreeRTOS节拍数
 *
 * @note    可以同时发出多个警报。应用程序应检查已启用的所有警报。
 *
 * @return
 *      -ESP_OK：警报已读取
 *      -ESP_ERR_TIMEOUT:等待警报超时
 *      -ESP_ERR_INVALID_ARG:参数无效
 *      -ESP_ERR_INVALID_STATE:未安装TWAI驱动程序
 */
esp_err_t twai_read_alerts(uint32_t *alerts, TickType_t ticks_to_wait);

/**
 * @brief   重新配置已启用的警报
 *
 * 此功能可重新配置启用的警报。如果在重新配置时存在尚未读取的警报，则此功能可以读取这些警报。
 *
 * @param[in]   alerts_enabled  要启用的警报位字段（有关警报标志，请参阅文档）
 * @param[out]  current_alerts  当前引发警报的位字段。如果未使用，则设置为NULL
 *
 * @return
 *      -ESP_OK：警报已重新配置
 *      -ESP_ERR_INVALID_STATE:未安装TWAI驱动程序
 */
esp_err_t twai_reconfigure_alerts(uint32_t alerts_enabled, uint32_t *current_alerts);

/**
 * @brief   启动总线恢复过程
 *
 * 当TWAI驱动程序处于总线关闭状态时，此功能启动总线恢复过程。一旦启动，TWAI驱动程序将进入恢复状态，并等待TWAI总线上出现128次总线空闲信号，然后返回停止状态。此功能将重置TX队列，清除所有等待传输的消息。
 *
 * @note    可以启用BUS_RECOVERED警报，以便在总线恢复过程完成时向应用程序发出警报。
 *
 * @return
 *      -ESP_OK:总线恢复已启动
 *      -ESP_ERR_INVALID_STATE:TWAI驱动程序未处于总线关闭状态，或未安装
 */
esp_err_t twai_initiate_recovery(void);

/**
 * @brief   获取TWAI驱动程序的当前状态信息
 *
 * @param[out]  status_info     状态信息
 *
 * @return
 *      -ESP_OK：检索到状态信息
 *      -ESP_ERR_INVALID_ARG:参数无效
 *      -ESP_ERR_INVALID_STATE:未安装TWAI驱动程序
 */
esp_err_t twai_get_status_info(twai_status_info_t *status_info);

/**
 * @brief   清除传输队列
 *
 * 此功能将清除所有消息的传输队列。
 *
 * @note    当调用twai_stop（）或twai_initiate_recovery（）时，传输队列将自动清除。
 *
 * @return
 *      -ESP_OK：传输队列已清除
 *      -ESP_ERR_INVALID_STATE:TWAI驱动程序未安装或TX队列已禁用
 */
esp_err_t twai_clear_transmit_queue(void);

/**
 * @brief   清除接收队列
 *
 * 此函数将清除所有消息的接收队列。
 *
 * @note    当调用twai_start（）时，接收队列将自动清除。
 *
 * @return
 *      -ESP_OK：传输队列已清除
 *      -ESP_ERR_INVALID_STATE:未安装TWAI驱动程序
 */
esp_err_t twai_clear_receive_queue(void);

#ifdef __cplusplus
}
#endif

#endif //SOC_TWAI_SUPPORTED

