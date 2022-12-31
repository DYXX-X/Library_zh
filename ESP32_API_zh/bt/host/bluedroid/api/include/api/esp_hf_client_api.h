// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#ifndef __ESP_HF_CLIENT_API_H__
#define __ESP_HF_CLIENT_API_H__

#include "esp_err.h"
#include "esp_bt_defs.h"
#include "esp_hf_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_BT_HF_CLIENT_NUMBER_LEN           (32)
#define ESP_BT_HF_CLIENT_OPERATOR_NAME_LEN    (16)

///蓝牙HFP RFCOMM连接和服务级别连接状态
typedef enum {
    ESP_HF_CLIENT_CONNECTION_STATE_DISCONNECTED = 0,     /*!< RFCOMM数据链路通道已释放*/
    ESP_HF_CLIENT_CONNECTION_STATE_CONNECTING,           /*!< 在RFCOMM数据链路上连接远程设备*/
    ESP_HF_CLIENT_CONNECTION_STATE_CONNECTED,            /*!< RFCOMM连接已建立*/
    ESP_HF_CLIENT_CONNECTION_STATE_SLC_CONNECTED,        /*!< 服务级别连接已建立*/
    ESP_HF_CLIENT_CONNECTION_STATE_DISCONNECTING,        /*!< 在RFCOMM数据链路上断开与远程设备的连接*/
} esp_hf_client_connection_state_t;

///蓝牙HFP音频连接状态
typedef enum {
    ESP_HF_CLIENT_AUDIO_STATE_DISCONNECTED = 0,          /*!< 音频连接已释放*/
    ESP_HF_CLIENT_AUDIO_STATE_CONNECTING,                /*!< 音频连接已启动*/
    ESP_HF_CLIENT_AUDIO_STATE_CONNECTED,                 /*!< 音频连接已建立*/
    ESP_HF_CLIENT_AUDIO_STATE_CONNECTED_MSBC,            /*!< mSBC音频连接已建立*/
} esp_hf_client_audio_state_t;

///带内铃声状态
typedef enum {
    ESP_HF_CLIENT_IN_BAND_RINGTONE_NOT_PROVIDED = 0,
    ESP_HF_CLIENT_IN_BAND_RINGTONE_PROVIDED,
} esp_hf_client_in_band_ring_state_t;

/* 具有AG掩模*/
#define ESP_HF_CLIENT_PEER_FEAT_3WAY       0x01        /* 三向呼叫*/
#define ESP_HF_CLIENT_PEER_FEAT_ECNR       0x02        /* 回声消除和/或降噪*/
#define ESP_HF_CLIENT_PEER_FEAT_VREC       0x04        /* 语音识别*/
#define ESP_HF_CLIENT_PEER_FEAT_INBAND     0x08        /* 带内铃声*/
#define ESP_HF_CLIENT_PEER_FEAT_VTAG       0x10        /* 将电话号码附加到声控标签*/
#define ESP_HF_CLIENT_PEER_FEAT_REJECT     0x20        /* 拒绝来电的能力*/
#define ESP_HF_CLIENT_PEER_FEAT_ECS        0x40        /* 增强的呼叫状态*/
#define ESP_HF_CLIENT_PEER_FEAT_ECC        0x80        /* 增强的呼叫控制*/
#define ESP_HF_CLIENT_PEER_FEAT_EXTERR    0x100        /* 扩展错误代码*/
#define ESP_HF_CLIENT_PEER_FEAT_CODEC     0x200        /* 编解码器协商*/
/* HFP 1.7+ */
#define ESP_HF_CLIENT_PEER_FEAT_HF_IND    0x400        /* 高频指示器*/
#define ESP_HF_CLIENT_PEER_FEAT_ESCO_S4   0x800        /* 支持eSCO S4设置*/

/* AG的CHLD特征掩模*/
#define ESP_HF_CLIENT_CHLD_FEAT_REL           0x01       /* 0释放等待呼叫或保留呼叫*/
#define ESP_HF_CLIENT_CHLD_FEAT_REL_ACC       0x02       /* 1释放激活的呼叫并接受其他等待或保持的呼叫*/
#define ESP_HF_CLIENT_CHLD_FEAT_REL_X         0x04       /* 1x仅释放指定的活动呼叫*/
#define ESP_HF_CLIENT_CHLD_FEAT_HOLD_ACC      0x08       /* 2个挂起的活动呼叫，并接受其他等待或挂起的呼叫*/
#define ESP_HF_CLIENT_CHLD_FEAT_PRIV_X        0x10       /* 2x使用指定的呼叫请求私人模式（将其余呼叫保持）*/
#define ESP_HF_CLIENT_CHLD_FEAT_MERGE         0x20       /* 3将保留呼叫添加到多方*/
#define ESP_HF_CLIENT_CHLD_FEAT_MERGE_DETACH  0x40       /* 4接通两个电话并离开（断开多方通话）*/

///HF CLIENT回调事件
typedef enum {
    ESP_HF_CLIENT_CONNECTION_STATE_EVT = 0,          /*!< 连接状态更改事件*/
    ESP_HF_CLIENT_AUDIO_STATE_EVT,                   /*!< 音频连接状态更改事件*/
    ESP_HF_CLIENT_BVRA_EVT,                          /*!< 语音识别状态更改事件*/
    ESP_HF_CLIENT_CIND_CALL_EVT,                     /*!< 呼叫指示*/
    ESP_HF_CLIENT_CIND_CALL_SETUP_EVT,               /*!< 呼叫建立指示*/
    ESP_HF_CLIENT_CIND_CALL_HELD_EVT,                /*!< 呼叫保持指示*/
    ESP_HF_CLIENT_CIND_SERVICE_AVAILABILITY_EVT,     /*!< 网络服务可用性指示*/
    ESP_HF_CLIENT_CIND_SIGNAL_STRENGTH_EVT,          /*!< 信号强度指示*/
    ESP_HF_CLIENT_CIND_ROAMING_STATUS_EVT,           /*!< 漫游状态指示*/
    ESP_HF_CLIENT_CIND_BATTERY_LEVEL_EVT,            /*!< 电池电量指示*/
    ESP_HF_CLIENT_COPS_CURRENT_OPERATOR_EVT,         /*!< 当前操作员信息*/
    ESP_HF_CLIENT_BTRH_EVT,                          /*!< 呼叫响应和保持事件*/
    ESP_HF_CLIENT_CLIP_EVT,                          /*!< 呼叫线路标识通知*/
    ESP_HF_CLIENT_CCWA_EVT,                          /*!< 呼叫等待通知*/
    ESP_HF_CLIENT_CLCC_EVT,                          /*!< 当前通话通知列表*/
    ESP_HF_CLIENT_VOLUME_CONTROL_EVT,                /*!< 来自AG的音频音量控制命令，由+VGM或+VGS消息提供*/
    ESP_HF_CLIENT_AT_RESPONSE_EVT,                   /*!< AT命令响应事件*/
    ESP_HF_CLIENT_CNUM_EVT,                          /*!< 来自AG的用户信息响应*/
    ESP_HF_CLIENT_BSIR_EVT,                          /*!< 带内铃声设置*/
    ESP_HF_CLIENT_BINP_EVT,                          /*!< 从AG请求的最后一个语音标签编号*/
    ESP_HF_CLIENT_RING_IND_EVT,                      /*!< 环形指示事件*/
} esp_hf_client_cb_event_t;

///HFP客户端回调参数
typedef union {
    /**
     * @brief  ESP_HF_CLIENT_CONNECTION_STATE_EVT
     */
    struct hf_client_conn_stat_param {
        esp_hf_client_connection_state_t state;  /*!< 高频连接状态*/
        uint32_t peer_feat;                      /*!< AG支持的功能*/
        uint32_t chld_feat;                      /*!< AG支持呼叫保持和多方服务功能*/
        esp_bd_addr_t remote_bda;                /*!< 远程蓝牙设备地址*/
    } conn_stat;                                 /*!< ESP_HF_CLIENT_CONNECTION_STATE_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_AUDIO_STATE_EVT
     */
    struct hf_client_audio_stat_param {
        esp_hf_client_audio_state_t state;       /*!< 音频连接状态*/
        esp_bd_addr_t remote_bda;                /*!< 远程蓝牙设备地址*/
    } audio_stat;                                /*!< ESP_HF_CLIENT_AUDIO_STATE_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_BVRA_EVT
     */
    struct hf_client_bvra_param {
        esp_hf_vr_state_t value;                 /*!< 语音识别状态*/
    } bvra;                                      /*!< ESP_HF_CLIENT_BVRA_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CIND_SERVICE_AVAILABILITY_EVT
     */
    struct hf_client_service_availability_param {
        esp_hf_network_state_t status;           /*!< 服务可用性状态*/
    } service_availability;                      /*!< ESP_HF_CLIENT_CIND_SERVICE_AVAILABILITY_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CIND_ROAMING_STATUS_EVT
     */
    struct hf_client_network_roaming_param {
        esp_hf_roaming_status_t status;          /*!< 漫游状态*/
    } roaming;                                   /*!< ESP_HF_CLIENT_CIND_ROAMING_STATUS_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CIND_SIGNAL_STRENGTH_EVT
     */
    struct hf_client_signal_strength_ind_param {
        int value;                               /*!< 信号强度值，范围从0到5*/
    } signal_strength;                           /*!< ESP_HF_CLIENT_CIND_SIGNAL_STRENGTH_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CIND_BATTERY_LEVEL_EVT
     */
    struct hf_client_battery_level_ind_param {
        int value;                               /*!< 电池充电值，范围从0到5*/
    } battery_level;                             /*!< ESP_HF_CLIENT_CIND_BATTERY_LEVEL_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_COPS_CURRENT_OPERATOR_EVT
     */
    struct hf_client_current_operator_param {
        const char *name;                        /*!< 网络运营商的名称*/
    } cops;                                      /*!< ESP_HF_CLIENT_COPS_CURRENT_OPERATOR_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CIND_CALL_EVT
     */
    struct hf_client_call_ind_param {
        esp_hf_call_status_t status;             /*!< 呼叫状态指示器*/
    } call;                                      /*!< ESP_HF_CLIENT_CIND_CALL_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CIND_CALL_SETUP_EVT
     */
    struct hf_client_call_setup_ind_param {
        esp_hf_call_setup_status_t status;       /*!< 呼叫设置状态指示器*/
    } call_setup;                                /*!< ESP_HF_CLIENT_BVRA_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CIND_CALL_HELD_EVT
     */
    struct hf_client_call_held_ind_param {
        esp_hf_call_held_status_t status;        /*!< 蓝牙专有呼叫保持状态指示器*/
    } call_held;                                 /*!< ESP_HF_CLIENT_CIND_CALL_HELD_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_BTRH_EVT
     */
    struct hf_client_btrh_param {
        esp_hf_btrh_status_t status;             /*!< 呼叫保持和响应状态结果代码*/
    } btrh;                                      /*!< ESP_HF_CLIENT_BRTH_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CLIP_EVT
     */
    struct hf_client_clip_param {
        const char *number;                      /*!< 通话的电话号码字符串*/
    } clip;                                      /*!< ESP_HF_CLIENT_CLIP_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CCWA_EVT
     */
    struct hf_client_ccwa_param {
        const char *number;                      /*!< 等待呼叫的电话号码字符串*/
    } ccwa;                                      /*!< ESP_HF_CLIENT_BVRA_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CLCC_EVT
     */
    struct hf_client_clcc_param {
        int idx;                                 /*!< 呼叫的编号（从1开始）*/
        esp_hf_current_call_direction_t dir;     /*!< 呼叫的方向*/
        esp_hf_current_call_status_t status;     /*!< 通话状态*/
        esp_hf_current_call_mpty_type_t mpty;    /*!< 多党制旗帜*/
        char *number;                            /*!< 电话号码（可选）*/
    } clcc;                                      /*!< ESP_HF_CLIENT_CLCC_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_VOLUME_CONTROL_EVT
     */
    struct hf_client_volume_control_param {
        esp_hf_volume_control_target_t type;     /*!< 音量控制目标、扬声器或麦克风*/
        int volume;                              /*!< 增益，范围从0到15*/
    } volume_control;                            /*!< ESP_HF_CLIENT_VOLUME_CONTROL_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_AT_RESPONSE_EVT
     */
    struct hf_client_at_response_param {
        esp_hf_at_response_code_t code;          /*!< AT响应代码*/
        esp_hf_cme_err_t cme;                    /*!< 扩展音频网关错误结果代码*/
    } at_response;                               /*!< ESP_HF_CLIENT_AT_RESPONSE_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_CNUM_EVT
     */
    struct hf_client_cnum_param {
        const char *number;                      /*!< 电话号码字符串*/
        esp_hf_subscriber_service_type_t type;   /*!< 与电话号码相关的服务类型*/
    } cnum;                                      /*!< ESP_HF_CLIENT_CNUM_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_BSIR_EVT
     */
    struct hf_client_bsirparam {
        esp_hf_client_in_band_ring_state_t state;  /*!< 带内铃声设置状态*/
    } bsir;                                        /*!< ESP_HF_CLIENT_BSIR_EVT的HF回调参数*/

    /**
     * @brief ESP_HF_CLIENT_BINP_EVT
     */
    struct hf_client_binp_param {
        const char *number;                      /*!< 与HF中最后一个语音标签对应的电话号码*/
    } binp;                                      /*!< ESP_HF_CLIENT_BINP_EVT的HF回调参数*/

} esp_hf_client_cb_param_t;                      /*!< HFP客户端回调参数*/

/**
 * @brief           HFP客户端传入数据回调函数，回调在使用HCI语音时非常有用。
 * @param[in]       buf ：指向传入数据的指针（HCI同步数据包的有效负载），缓冲区分配在蓝牙协议栈中，并将在回调调用完成后释放。
 * @param[in]       len ：buf中的大小（字节）
 */
typedef void (* esp_hf_client_incoming_data_cb_t)(const uint8_t *buf, uint32_t len);

/**
 * @brief           HFP客户端传出数据回调函数，回调在使用HCI语音时非常有用。一旦建立了音频连接，并且应用层已经准备好要发送的数据，下层将调用此函数读取数据，然后发送。此回调应该以非阻塞方式实现，如果数据不足，则应该返回值0。
 *
 * @param[in]       buf ：指向传入数据的指针（HCI同步数据包的有效负载），缓冲区分配在蓝牙协议栈中，并将在回调调用完成后释放。
 *
 * @param[in]       len ：buf中的大小（字节）
 *
 * @return          成功读取的数据长度
 *
 */
typedef uint32_t (* esp_hf_client_outgoing_data_cb_t)(uint8_t *buf, uint32_t len);

/**
 * @brief           HFP客户端回调函数类型
 *
 * @param           event ：事件类型
 *
 * @param           param ：指向回调参数的指针
 */
typedef void (* esp_hf_client_cb_t)(esp_hf_client_cb_event_t event, esp_hf_client_cb_param_t *param);

/**
 * @brief           向HFP客户端模块注册应用程序回调函数。只有在esp_bluedroid_enable（）成功完成后才能调用此函数。
 *
 * @param[in]       callback: HFP客户端事件回调函数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：如果回调是NULL函数指针
 *
 */
esp_err_t esp_hf_client_register_callback(esp_hf_client_cb_t callback);

/**
 *
 * @brief           初始化蓝牙HFP客户端模块。应在esp_bluedroid_enable（）成功完成后调用此函数。
 *
 * @return
 *                  -ESP_OK：如果初始化请求发送成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_init(void);

/**
 *
 * @brief           取消HFP客户端模块的初始化。只有在esp_bluedroid_enable（）成功完成后才能调用此函数。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_deinit(void);

/**
 *
 * @brief           建立到远程蓝牙HFP音频网关（AG）设备的服务级别连接。必须在esp_hf_client_init（）之后和esp_hf_client_deinit（）之前调用此函数。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 *
 * @return
 *                  -ESP_OK：连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_connect(esp_bd_addr_t remote_bda);

/**
 *
 * @brief           断开与远程HFP音频网关的连接。必须在esp_hf_client_init（）之后和esp_hf_client_deinit（）之前调用此函数。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_disconnect(esp_bd_addr_t remote_bda);

/**
 *
 * @brief           与远程HFP AG建立音频连接。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_connect_audio(esp_bd_addr_t remote_bda);

/**
 *
 * @brief           释放与远程HFP AG建立的音频连接。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_disconnect_audio(esp_bd_addr_t remote_bda);

/**
 *
 * @brief           在AG中启用语音识别。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_start_voice_recognition(void);

/**
 *
 * @brief           禁用AG中的语音识别。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_stop_voice_recognition(void);

/**
 *
 * @brief           与AG的卷同步。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @param[in]       type: 音量控制目标、扬声器或麦克风
 * @param[in]       volume: 麦克风扬声器的增益，范围为0到15
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_volume_update(esp_hf_volume_control_target_t type, int volume);

/**
 *
 * @brief           使用指定的号码进行呼叫，如果号码为NULL，则调用最后一个呼叫的号码。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @param[in]       number: 呼叫的数字字符串。如果为NULL，则调用最后一个号码（即重新拨号）
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_dial(const char *number);

/**
 *
 * @brief           拨打按位置指定的号码（快速拨号）。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @param[in]       location: 数字在存储器中的位置
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */

esp_err_t esp_hf_client_dial_memory(int location);

/**
 *
 * @brief           发送呼叫保持和多方通话命令，或增强型呼叫控制命令（使用AT+CHLD）。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @param[in]       chld: AT+CHLD呼叫保持和多方处理AT命令。
 * @param[in]       idx: 用于增强呼叫控制机制，如果chld是ESP_HF_chld_TYPE_REL_X或ESP_HF_chld_TYPE_PRIV_X，则使用
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_send_chld_cmd(esp_hf_chld_type_t chld, int idx);

/**
 *
 * @brief           发送响应和保持动作命令（发送AT+BTRH命令）作为使用此API的前提条件，AG应存在服务级别连接。
 *
 * @param[in]       btrh: 要发送的响应和保持操作
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_send_btrh_cmd(esp_hf_btrh_cmd_t btrh);

/**
 *
 * @brief           接听来电（发送ATA命令）。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_answer_call(void);

/**
 *
 * @brief           拒绝来电（发送AT+CHUP命令）。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_reject_call(void);

/**
 *
 * @brief           查询AG中当前呼叫的列表（发送AT+CLCC命令）。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_query_current_calls(void);

/**
 *
 * @brief           查询AG中当前所选网络运营商的名称（使用AT+COPS命令）。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_query_current_operator_name(void);

/**
 *
 * @brief           从AG获取用户信息号码（发送AT+CNUM命令）作为使用此API的前提条件，AG应存在服务级别连接
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_retrieve_subscriber_info(void);

/**
 *
 * @brief           在正在进行的呼叫期间传输DTMF代码（使用AT+VTS命令）作为使用此API的前提条件，AG应存在服务级别连接。
 *
 * @param[in]       code: dtmf代码，集合0-9、#、*、A-D中的单个ascii字符
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_send_dtmf(char code);

/**
 *
 * @brief           向AG请求与记录的最后一个语音标签对应的电话号码（发送AT+BINP命令）。作为使用此API的前提条件，AG应具有服务级别连接。
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_request_last_voice_tag_number(void);

/**
 *
 * @brief           禁用AG中的回声消除和降噪（使用AT+NREC=0命令）。作为使用此API的前提条件，AG应存在服务级别连接
 *
 * @return
 *                  -ESP_OK:NREC=0请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_client_send_nrec(void);


/**
 * @brief           注册HFP客户端数据输出功能；回调仅在启用了Voice Over HCI的情况下使用。
 *
 * @param[in]       recv: HFP客户端传入数据回调函数
 *
 * @param[in]       send: HFP客户端传出数据回调函数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：如果回调是NULL函数指针
 *
 */
esp_err_t esp_hf_client_register_data_callback(esp_hf_client_incoming_data_cb_t recv,
                                               esp_hf_client_outgoing_data_cb_t send);

/**
 * @brief           触发下层以获取和发送音频数据。此功能仅在启用了Voice Over HCI的情况下使用。调用此函数后，下层将调用esp_hf_client_outgoing_data_cb_t来获取数据。
 *
 *                  作为使用此API的前提条件，AG应具有服务级别连接。
 *
 */
void esp_hf_client_outgoing_data_ready(void);


/**
 * @brief           初始化下采样转换器。这是一个实用功能，仅在启用了Voice Over HCI的情况下才能使用。
 *
 * @param[in]       src_sps: 每秒原始采样数（源音频数据，即48000、32000、16000、44100、22050、11025）
 * @param[in]       bits: 每个pcm样本的位数（16）
 *
 * @param[in]       channels: 频道数（即单声道（1）、立体声（2）…）
 */
void esp_hf_client_pcm_resample_init(uint32_t src_sps, uint32_t bits, uint32_t channels);

/**
 * @brief           取消初始化下采样转换器。
 */
void esp_hf_client_pcm_resample_deinit(void);

/**
 * @brief           下采样实用程序，用于将高采样率转换为8K/16位单通道模式PCM采样。这只能在启用了HCI语音的情况下使用。
 *
 * @param[in]       src: 指向存储原始采样PCM的缓冲区的指针
 *
 * @param[in]       in_bytes: 输入PCM采样缓冲区的长度（字节）
 *
 * @param[in]       dst: 指向用于存储转换PCM样本的缓冲区的指针
 *
 * @return          转换的样本数
 */
int32_t esp_hf_client_pcm_resample(void *src, uint32_t in_bytes, void *dst);

#ifdef __cplusplus
}
#endif


#endif /* __ESP_HF_CLIENT_API_H__ */

