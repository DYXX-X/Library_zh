// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef __ESP_A2DP_API_H__
#define __ESP_A2DP_API_H__

#include "esp_err.h"
#include "esp_bt_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

///A2DP支持的媒体编解码器类型
#define ESP_A2D_MCT_SBC         (0)             /*!< SBC */
#define ESP_A2D_MCT_M12         (0x01)          /*!< MPEG-1，2音频*/
#define ESP_A2D_MCT_M24         (0x02)          /*!< MPEG-2, 4 AAC */
#define ESP_A2D_MCT_ATRAC       (0x04)          /*!< ATRAC系列*/
#define ESP_A2D_MCT_NON_A2DP    (0xff)

typedef uint8_t esp_a2d_mct_t;

/** A2DP媒体编解码器功能联盟
 */
typedef struct {
    esp_a2d_mct_t type;                        /*!< A2DP媒体编解码器类型*/
#define ESP_A2D_CIE_LEN_SBC          (4)
#define ESP_A2D_CIE_LEN_M12          (4)
#define ESP_A2D_CIE_LEN_M24          (6)
#define ESP_A2D_CIE_LEN_ATRAC        (7)
    union {
        uint8_t sbc[ESP_A2D_CIE_LEN_SBC];      /*!< SBC编解码器功能*/
        uint8_t m12[ESP_A2D_CIE_LEN_M12];      /*!< MPEG-1,2音频编解码器功能*/
        uint8_t m24[ESP_A2D_CIE_LEN_M24];      /*!< MPEG-2、4 AAC音频编解码器功能*/
        uint8_t atrac[ESP_A2D_CIE_LEN_ATRAC];  /*!< ATRAC系列编解码器功能*/
    } cie;                                     /*!< A2DP编解码器信息元素*/
} __attribute__((packed)) esp_a2d_mcc_t;

///蓝牙A2DP连接状态
typedef enum {
    ESP_A2D_CONNECTION_STATE_DISCONNECTED = 0, /*!< 连接已释放*/
    ESP_A2D_CONNECTION_STATE_CONNECTING,       /*!< 连接远程设备*/
    ESP_A2D_CONNECTION_STATE_CONNECTED,        /*!< 已建立连接*/
    ESP_A2D_CONNECTION_STATE_DISCONNECTING     /*!< 断开远程设备*/
} esp_a2d_connection_state_t;

///蓝牙A2DP断开原因
typedef enum {
    ESP_A2D_DISC_RSN_NORMAL = 0,               /*!< 已完成由本地或远程设备启动的断开连接*/
    ESP_A2D_DISC_RSN_ABNORMAL                  /*!< 信号丢失导致的异常断开*/
} esp_a2d_disc_rsn_t;

///蓝牙A2DP数据路径状态
typedef enum {
    ESP_A2D_AUDIO_STATE_REMOTE_SUSPEND = 0,    /*!< 音频流数据路径被远程设备挂起*/
    ESP_A2D_AUDIO_STATE_STOPPED,               /*!< 音频流数据路径已停止*/
    ESP_A2D_AUDIO_STATE_STARTED,               /*!< 音频流数据路径已启动*/
} esp_a2d_audio_state_t;

///A2DP媒体控制命令确认码
typedef enum {
    ESP_A2D_MEDIA_CTRL_ACK_SUCCESS = 0,        /*!< 媒体控制命令确认成功*/
    ESP_A2D_MEDIA_CTRL_ACK_FAILURE,            /*!< 媒体控制命令确认失败*/
    ESP_A2D_MEDIA_CTRL_ACK_BUSY,               /*!< 媒体控制命令被拒绝，因为之前的命令尚未确认*/
} esp_a2d_media_ctrl_ack_t;

///A2DP媒体控制命令
typedef enum {
    ESP_A2D_MEDIA_CTRL_NONE = 0,               /*!< 不用于应用程序，仅用于堆栈内部。*/
    ESP_A2D_MEDIA_CTRL_CHECK_SRC_RDY,          /*!< 检查AVDTP是否已连接，仅用于A2DP源*/
    ESP_A2D_MEDIA_CTRL_START,                  /*!< 设置媒体传输通道的命令*/
    ESP_A2D_MEDIA_CTRL_STOP,                   /*!< 停止媒体传输的命令*/
    ESP_A2D_MEDIA_CTRL_SUSPEND,                /*!< 暂停媒体传输的命令*/
} esp_a2d_media_ctrl_t;

///蓝牙A2DP启动状态
typedef enum {
    ESP_A2D_DEINIT_SUCCESS = 0,                /*!< A2DP配置文件卸载成功事件*/
    ESP_A2D_INIT_SUCCESS                       /*!< A2DP配置文件卸载成功事件*/
} esp_a2d_init_state_t;

///A2DP回调事件
typedef enum {
    ESP_A2D_CONNECTION_STATE_EVT = 0,          /*!< 连接状态更改事件*/
    ESP_A2D_AUDIO_STATE_EVT,                   /*!< 音频流传输状态更改事件*/
    ESP_A2D_AUDIO_CFG_EVT,                     /*!< 音频编解码器已配置，仅用于A2DP SINK*/
    ESP_A2D_MEDIA_CTRL_ACK_EVT,                /*!< 响应媒体控制命令的确认事件*/
    ESP_A2D_PROF_STATE_EVT,                    /*!< 指示a2dp初始化和卸载完成*/
} esp_a2d_cb_event_t;

///A2DP状态回调参数
typedef union {
    /**
     * @brief  ESP_A2D_CONNECTION_STATE_EVT
     */
    struct a2d_conn_stat_param {
        esp_a2d_connection_state_t state;      /*!< esp_a2d_connection_statet中的一个值*/
        esp_bd_addr_t remote_bda;              /*!< 远程蓝牙设备地址*/
        esp_a2d_disc_rsn_t disc_rsn;           /*!< “已断开”的断开原因*/
    } conn_stat;                               /*!< A2DP连接状态*/

    /**
     * @brief ESP_A2D_AUDIO_STATE_EVT
     */
    struct a2d_audio_stat_param {
        esp_a2d_audio_state_t state;           /*!< espa2d_audio_statet中的一个值*/
        esp_bd_addr_t remote_bda;              /*!< 远程蓝牙设备地址*/
    } audio_stat;                              /*!< 音频流播放状态*/

    /**
     * @brief ESP_A2D_AUDIO_CFG_EVT
     */
    struct a2d_audio_cfg_param {
        esp_bd_addr_t remote_bda;              /*!< 远程蓝牙设备地址*/
        esp_a2d_mcc_t mcc;                     /*!< A2DP媒体编解码器功能信息*/
    } audio_cfg;                               /*!< 媒体编解码器配置信息*/

    /**
     * @brief ESP_A2D_MEDIA_CTRL_ACK_EVT
     */
    struct media_ctrl_stat_param {
        esp_a2d_media_ctrl_t cmd;              /*!< 要确认的媒体控制命令*/
        esp_a2d_media_ctrl_ack_t status;       /*!< 对媒体控制命令的确认*/
    } media_ctrl_stat;                         /*!< 确认媒体控制命令的状态*/
    /**
     * @brief ESP_A2D_PROF_STATE_EVT
     */
    struct a2d_prof_stat_param {
        esp_a2d_init_state_t init_state;       /*!< a2dp配置文件状态参数*/
    } a2d_prof_stat;                           /*!< 指示a2d prof init或deinit的状态*/
} esp_a2d_cb_param_t;

/**
 * @brief           A2DP配置文件回调函数类型
 *
 * @param           event ：事件类型
 *
 * @param           param ：指向回调参数的指针
 */
typedef void (* esp_a2d_cb_t)(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param);

/**
 * @brief           A2DP信宿数据回调函数
 *
 * @param[in]       buf ：指向从A2DP源设备接收的数据的指针，并且是从SBC解码器解码的PCM格式；buf引用静态内存块，并且可以被即将到来的数据覆盖
 *
 * @param[in]       len ：buf中的大小（字节）
 */
typedef void (* esp_a2d_sink_data_cb_t)(const uint8_t *buf, uint32_t len);

/**
 * @brief           A2DP源数据读取回调函数
 *
 * @param[in]       buf ：缓冲区将填充来自更高层的PCM数据流
 *
 * @param[in]       len ：要复制到buf的数据块的大小（字节）-1表示用户应刷新数据缓冲区
 *
 * @return          成功读取的字节大小，如果参数len为-1，则忽略此值。
 *
 */
typedef int32_t (* esp_a2d_source_data_cb_t)(uint8_t *buf, int32_t len);

/**
 * @brief           向A2DP模块注册应用程序回调函数。只有在esp_bluedroid_enable（）成功完成后，才能调用该函数，A2DP源和接收器都使用该函数。
 *
 * @param[in]       callback: A2DP事件回调函数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：如果回调是NULL函数指针
 *
 */
esp_err_t esp_a2d_register_callback(esp_a2d_cb_t callback);


/**
 * @brief           寄存器A2DP信宿数据输出功能；目前，输出是从SBC格式解码的PCM数据流。只有在esp_bluedroid_enable（）成功完成（仅由A2DP接收器使用）后才能调用此函数。回调在A2DP接收任务的上下文中调用，该任务的堆栈大小可通过menuconfig配置。
 *
 * @param[in]       callback: A2DP信宿数据回调函数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：如果回调是NULL函数指针
 *
 */
esp_err_t esp_a2d_sink_register_data_callback(esp_a2d_sink_data_cb_t callback);


/**
 *
 * @brief           初始化蓝牙A2DP接收器模块。应在esp_bluedroid_enable（）成功完成后调用此函数，并且esp_A2D_PROF_STATE_EVT和esp_A2D_INIT_SUCCESS将报告给APP层。注：A2DP可以独立工作。如果你想一起使用AVRC，你应该首先启动AVRC。应在esp_bluedroid_enable（）成功完成后调用此函数。
 *
 * @return
 *                  -ESP_OK：如果初始化请求发送成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_a2d_sink_init(void);


/**
 *
 * @brief           取消A2DP接收器模块的初始化。只有在esp_bluedroid_enable（）成功完成，并且具有esp_A2D_DEINIT_SUCCESS的esp_A2D_PROF_STATE_EVT将报告给APP层后，才能调用此函数。
 *
 * @return
 *                  -ESP_OK：如果成功发送了去初始化请求
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_a2d_sink_deinit(void);


/**
 *
 * @brief           连接到远程蓝牙A2DP源设备。必须在esp_a2d_sink_init（）之后和esp_a2d_sink_deinit（）之前调用此API。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 *
 * @return
 *                  -ESP_OK：连接请求已成功发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_a2d_sink_connect(esp_bd_addr_t remote_bda);


/**
 *
 * @brief           断开与远程A2DP源设备的连接。必须在esp_a2d_sink_init（）之后和esp_a2d_sink_deinit（）之前调用此API。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 *
 * @return
 *                  -ESP_OK：断开连接请求已成功发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_a2d_sink_disconnect(esp_bd_addr_t remote_bda);


/**
 *
 * @brief           媒体控制命令。此API可用于A2DP接收器和源，必须在esp_a2d_sink_init（）之后和esp_a2d_sink_deinit（）之前调用。
 *
 * @param[in]       ctrl: A2DP数据通道的控制命令
 *
 * @return
 *                  -ESP_OK：控制命令成功发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_a2d_media_ctrl(esp_a2d_media_ctrl_t ctrl);


/**
 *
 * @brief           初始化蓝牙A2DP源模块。A2DP可以独立工作。如果你想一起使用AVRC，你应该首先启动AVRC。应在esp_bluedroid_enable（）成功完成后调用此函数，并且esp_A2D_PROF_STATE_EVT和esp_A2D_INIT_SUCCESS将报告给APP层。注：A2DP可以独立工作。如果你想一起使用AVRC，你应该首先启动AVRC。
 *
 * @return
 *                  -ESP_OK：如果初始化请求成功发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_a2d_source_init(void);


/**
 *
 * @brief           取消A2DP源模块的初始化。只有在esp_bluedroid_enable（）成功完成，并且具有esp_A2D_DEINIT_SUCCESS的esp_A2D_PROF_STATE_EVT将报告给APP层后，才能调用此函数。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_a2d_source_deinit(void);


/**
 * @brief           寄存器A2DP源数据输入功能。目前，输入应该是PCM数据流。只有在esp_bluedroid_enable（）成功完成后才能调用此函数。回调在A2DP源任务的上下文中调用，其堆栈大小可通过menuconfig配置。
 *
 * @param[in]       callback: A2DP源数据回调函数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：如果回调是NULL函数指针
 *
 */
esp_err_t esp_a2d_source_register_data_callback(esp_a2d_source_data_cb_t callback);


/**
 *
 * @brief           连接到远程A2DP接收器设备。必须在esp_a2d_source_init（）之后和esp_a2d_source_deinit（）之前调用此API。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 *
 * @return
 *                  -ESP_OK：连接请求已成功发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_a2d_source_connect(esp_bd_addr_t remote_bda);


/**
 *
 * @brief           断开与远程A2DP接收器设备的连接。必须在esp_a2d_source_init（）之后和esp_a2d_source_deinit（）之前调用此API。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_a2d_source_disconnect(esp_bd_addr_t remote_bda);

#ifdef __cplusplus
}
#endif


#endif /* __ESP_A2DP_API_H__ */

