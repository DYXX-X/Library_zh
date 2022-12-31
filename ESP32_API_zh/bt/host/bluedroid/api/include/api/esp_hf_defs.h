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

#ifndef __ESP_HF_DEFS_H__
#define __ESP_HF_DEFS_H__

#include "esp_bt_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_BT_HF_NUMBER_LEN           (32)
#define ESP_BT_HF_OPERATOR_NAME_LEN    (16)

#ifndef BTC_HSAG_SERVICE_NAME
#define BTC_HSAG_SERVICE_NAME ("Headset Gateway")
#endif

#ifndef BTC_HFAG_SERVICE_NAME
#define BTC_HFAG_SERVICE_NAME ("Handsfree Gateway")
#endif

#ifndef BTC_HF_SERVICES
#define BTC_HF_SERVICES    (BTA_HSP_SERVICE_MASK | BTA_HFP_SERVICE_MASK )
#endif

#ifndef BTC_HF_SERVICE_NAMES
#define BTC_HF_SERVICE_NAMES {BTC_HSAG_SERVICE_NAME , BTC_HFAG_SERVICE_NAME}
#endif

#ifndef BTC_HF_SECURITY
#define BTC_HF_SECURITY    (BTA_SEC_AUTHENTICATE | BTA_SEC_ENCRYPT)
#endif

#define BTC_HF_CALL_END_TIMEOUT       6

#define BTC_HF_INVALID_IDX       -1

///带内铃声状态
typedef enum {
    ESP_HF_IN_BAND_RINGTONE_NOT_PROVIDED = 0,
    ESP_HF_IN_BAND_RINGTONE_PROVIDED,
} esp_hf_in_band_ring_state_t;

///语音识别状态
typedef enum {
    ESP_HF_VR_STATE_DISABLED = 0,           /*!< 语音识别已禁用*/
    ESP_HF_VR_STATE_ENABLED,                /*!< 语音识别已启用*/
} esp_hf_vr_state_t;

///蓝牙HFP音频音量控制目标
typedef enum {
    ESP_HF_VOLUME_CONTROL_TARGET_SPK = 0,             /*!< 发言者*/
    ESP_HF_VOLUME_CONTROL_TARGET_MIC,                 /*!< 麦克风*/
} esp_hf_volume_control_target_t;

///蓝牙HFP音频连接状态
typedef enum {
    ESP_HF_AUDIO_STATE_DISCONNECTED = 0,          /*!< 音频连接已释放*/
    ESP_HF_AUDIO_STATE_CONNECTING,                /*!< 音频连接已启动*/
    ESP_HF_AUDIO_STATE_CONNECTED,                 /*!< 音频连接已建立*/
    ESP_HF_AUDIO_STATE_CONNECTED_MSBC,            /*!< mSBC音频连接已建立*/
} esp_hf_audio_state_t;

typedef enum {
    ESP_HF_VOLUME_TYPE_SPK = 0,
    ESP_HF_VOLUME_TYPE_MIC
} esp_hf_volume_type_t;

///+CIND网络服务可用性状态
typedef enum
{
    ESP_HF_NETWORK_STATE_NOT_AVAILABLE = 0,
    ESP_HF_NETWORK_STATE_AVAILABLE
} esp_hf_network_state_t;

/**+CIEV服务类型*/
typedef enum
{
    ESP_HF_SERVICE_TYPE_HOME = 0,
    ESP_HF_SERVICE_TYPE_ROAMING
} esp_hf_service_type_t;

///+CIND呼叫状态指示值
typedef enum {
    ESP_HF_CALL_STATUS_NO_CALLS = 0,                  /*!< 没有正在进行的呼叫*/
    ESP_HF_CALL_STATUS_CALL_IN_PROGRESS = 1,          /*!< 呼叫存在（激活或保持）*/
} esp_hf_call_status_t;

///+CIND呼叫设置状态指示值
typedef enum {
    ESP_HF_CALL_SETUP_STATUS_IDLE = 0,                /*!< 没有正在进行的呼叫设置*/
    ESP_HF_CALL_SETUP_STATUS_INCOMING = 1,            /*!< 正在进行来电设置*/
    ESP_HF_CALL_SETUP_STATUS_OUTGOING_DIALING = 2,    /*!< 拨号状态下的呼出设置*/
    ESP_HF_CALL_SETUP_STATUS_OUTGOING_ALERTING = 3,   /*!< 处于报警状态的呼出设置*/
} esp_hf_call_setup_status_t;

///+CIND漫游状态指示符值
typedef enum {
    ESP_HF_ROAMING_STATUS_INACTIVE = 0,               /*!< 漫游未激活*/
    ESP_HF_ROAMING_STATUS_ACTIVE,                     /*!< 漫游处于活动状态*/
} esp_hf_roaming_status_t;

///+CIND呼叫保持指示值
typedef enum {
    ESP_HF_CALL_HELD_STATUS_NONE = 0,                 /*!< 未保留呼叫*/
    ESP_HF_CALL_HELD_STATUS_HELD_AND_ACTIVE = 1,      /*!< 激活和保留通话*/
    ESP_HF_CALL_HELD_STATUS_HELD = 2,                 /*!< 呼叫保持，无活动呼叫*/
} esp_hf_call_held_status_t;

///+呼叫的CLCC状态
typedef enum {
    ESP_HF_CURRENT_CALL_STATUS_ACTIVE = 0,            /*!< 忙碌的*/
    ESP_HF_CURRENT_CALL_STATUS_HELD = 1,              /*!< 持有*/
    ESP_HF_CURRENT_CALL_STATUS_DIALING = 2,           /*!< 拨号（仅限拨出电话）*/
    ESP_HF_CURRENT_CALL_STATUS_ALERTING = 3,          /*!< 报警（仅限呼出）*/
    ESP_HF_CURRENT_CALL_STATUS_INCOMING = 4,          /*!< 传入（仅传入呼叫）*/
    ESP_HF_CURRENT_CALL_STATUS_WAITING = 5,           /*!< 等待（仅限来电）*/
    ESP_HF_CURRENT_CALL_STATUS_HELD_BY_RESP_HOLD = 6, /*!< 通过响应和保持呼叫*/
} esp_hf_current_call_status_t;

///+呼叫的CLCC方向
typedef enum {
    ESP_HF_CURRENT_CALL_DIRECTION_OUTGOING = 0,       /*!< 爱交际的*/
    ESP_HF_CURRENT_CALL_DIRECTION_INCOMING = 1,       /*!< 新当选的*/
} esp_hf_current_call_direction_t;

///+CLCC多方呼叫标志
typedef enum {
    ESP_HF_CURRENT_CALL_MPTY_TYPE_SINGLE = 0,         /*!< 不是多方通话的成员*/
    ESP_HF_CURRENT_CALL_MPTY_TYPE_MULTI = 1,          /*!< 多方通话成员*/
} esp_hf_current_call_mpty_type_t;

///+CLCC呼叫模式
typedef enum {
    ESP_HF_CURRENT_CALL_MODE_VOICE = 0,
    ESP_HF_CURRENT_CALL_MODE_DATA = 1,
    ESP_HF_CURRENT_CALL_MODE_FAX = 2,
} esp_hf_current_call_mode_t;

///+CLCC地址类型
typedef enum {
    ESP_HF_CALL_ADDR_TYPE_UNKNOWN = 0x81,            /*!< 未知地址类型*/
    ESP_HF_CALL_ADDR_TYPE_INTERNATIONAL = 0x91,      /*!< 国际地址*/
} esp_hf_call_addr_type_t;

///+电话号码的CNUM服务类型
typedef enum {
    ESP_HF_SUBSCRIBER_SERVICE_TYPE_UNKNOWN = 0,      /*!< 未知的*/
    ESP_HF_SUBSCRIBER_SERVICE_TYPE_VOICE,            /*!< 语音服务*/
    ESP_HF_SUBSCRIBER_SERVICE_TYPE_FAX,              /*!< 传真服务*/
} esp_hf_subscriber_service_type_t;

///+BTRH响应和保持结果代码
typedef enum {
    ESP_HF_BTRH_STATUS_HELD = 0,       /*!< 传入呼叫在AG保留*/
    ESP_HF_BTRH_STATUS_ACCEPTED,       /*!< AG接受保留的来电*/
    ESP_HF_BTRH_STATUS_REJECTED,       /*!< AG拒绝保留的来电*/
} esp_hf_btrh_status_t;

///AT+BTRH响应和保持动作代码
typedef enum {
    ESP_HF_BTRH_CMD_HOLD = 0,          /*!< 保持来电*/
    ESP_HF_BTRH_CMD_ACCEPT = 1,        /*!< 接受保留的来电*/
    ESP_HF_BTRH_CMD_REJECT = 2,        /*!< 拒绝保持的来电*/
} esp_hf_btrh_cmd_t;

/* +NREC */
typedef enum
{
    ESP_HF_NREC_STOP = 0,
    ESP_HF_NREC_START
} esp_hf_nrec_t;

///+CCWA响应状态
typedef enum {
    ESP_HF_CALL_WAITING_INACTIVE,
    ESP_HF_CALL_WAITING_ACTIVE,
} esp_hf_call_waiting_status_t;

/* WBS编解码器设置*/
typedef enum
{
   ESP_HF_WBS_NONE,
   ESP_HF_WBS_NO,
   ESP_HF_WBS_YES
}esp_hf_wbs_config_t;

///蓝牙HFP RFCOMM连接和服务级别连接状态
typedef enum {
    ESP_HF_CONNECTION_STATE_DISCONNECTED = 0,     /*!< RFCOMM数据链路通道已释放*/
    ESP_HF_CONNECTION_STATE_CONNECTING,           /*!< 在RFCOMM数据链路上连接远程设备*/
    ESP_HF_CONNECTION_STATE_CONNECTED,            /*!< RFCOMM连接已建立*/
    ESP_HF_CONNECTION_STATE_SLC_CONNECTED,        /*!< 服务级别连接已建立*/
    ESP_HF_CONNECTION_STATE_DISCONNECTING,        /*!< 断开与RFCOMM数据链路上的远程设备的连接*/
} esp_hf_connection_state_t;

///AT+CHLD命令值
typedef enum {
    ESP_HF_CHLD_TYPE_REL = 0,               /*!< <0>，终止所有保持的呼叫或将UDUB（“忙”）设置为等待呼叫*/
    ESP_HF_CHLD_TYPE_REL_ACC,               /*!< <1> ，终止所有活动呼叫并接受等待/保持的呼叫*/
    ESP_HF_CHLD_TYPE_HOLD_ACC,              /*!< <2> ，保持所有活动通话并接受等待/保持通话*/
    ESP_HF_CHLD_TYPE_MERGE,                 /*!< <3> ，将所有挂起的呼叫添加到会议*/
    ESP_HF_CHLD_TYPE_MERGE_DETACH,          /*!< <4> ，连接两个呼叫并断开用户与两个呼叫的连接*/
    ESP_HF_CHLD_TYPE_REL_X,                 /*!< <1x>，仅释放指定呼叫*/
    ESP_HF_CHLD_TYPE_PRIV_X,                /*!< <2x>，使用指定呼叫请求私人咨询模式*/
} esp_hf_chld_type_t;

/* AT响应代码-正常/错误*/
typedef enum {
    ESP_HF_AT_RESPONSE_CODE_OK = 0,         /*!< 确认命令行的执行*/
    ESP_HF_AT_RESPONSE_CODE_ERR,            /*!< 命令未被接受*/
    ESP_HF_AT_RESPONSE_CODE_NO_CARRIER,     /*!< 连接已终止*/
    ESP_HF_AT_RESPONSE_CODE_BUSY,           /*!< 检测到忙信号*/
    ESP_HF_AT_RESPONSE_CODE_NO_ANSWER,      /*!< 连接完成超时*/
    ESP_HF_AT_RESPONSE_CODE_DELAYED,        /*!< 延迟*/
    ESP_HF_AT_RESPONSE_CODE_BLACKLISTED,    /*!< 列入黑名单的*/
    ESP_HF_AT_RESPONSE_CODE_CME,            /*!< CME错误*/
} esp_hf_at_response_code_t;

/* AT响应代码-正常/错误*/
typedef enum {
    ESP_HF_AT_RESPONSE_ERROR = 0,
    ESP_HF_AT_RESPONSE_OK
} esp_hf_at_response_t;

///扩展音频网关错误结果代码响应
typedef enum {
    ESP_HF_CME_AG_FAILURE = 0,                    /*!< ag失效*/
    ESP_HF_CME_NO_CONNECTION_TO_PHONE = 1,        /*!< 无法连接到电话*/
    ESP_HF_CME_OPERATION_NOT_ALLOWED = 3,         /*!< 不允许操作*/
    ESP_HF_CME_OPERATION_NOT_SUPPORTED = 4,       /*!< 不支持操作*/
    ESP_HF_CME_PH_SIM_PIN_REQUIRED = 5,           /*!< 需要PH-SIM PIN*/
    ESP_HF_CME_SIM_NOT_INSERTED = 10,             /*!< SIM卡未插入*/
    ESP_HF_CME_SIM_PIN_REQUIRED = 11,             /*!< 需要SIM卡PIN*/
    ESP_HF_CME_SIM_PUK_REQUIRED = 12,             /*!< 需要SIM PUK*/
    ESP_HF_CME_SIM_FAILURE = 13,                  /*!< SIM卡故障*/
    ESP_HF_CME_SIM_BUSY = 14,                     /*!< SIM卡忙*/
    ESP_HF_CME_INCORRECT_PASSWORD = 16,           /*!< 密码不正确*/
    ESP_HF_CME_SIM_PIN2_REQUIRED = 17,            /*!< 需要SIM卡PIN2*/
    ESP_HF_CME_SIM_PUK2_REQUIRED = 18,            /*!< 需要SIM PUK2*/
    ESP_HF_CME_MEMEORY_FULL = 20,                 /*!< 内存已满*/
    ESP_HF_CME_INVALID_INDEX = 21,                /*!< 无效索引*/
    ESP_HF_CME_MEMEORY_FAILURE = 23,              /*!< 存储器故障*/
    ESP_HF_CME_TEXT_STRING_TOO_LONG = 24,         /*!< 测试字符串过长*/
    ESP_HF_CME_INVALID_CHARACTERS_IN_TEXT_STRING = 25,  /*!< 文本字符串中的无效字符*/
    ESP_HF_CME_DIAL_STRING_TOO_LONG = 26,         /*!< 拨号字符串过长*/
    ESP_HF_CME_INVALID_CHARACTERS_IN_DIAL_STRING = 27,  /*!< 拨号字符串中的无效字符*/
    ESP_HF_CME_NO_NETWORK_SERVICE = 30,           /*!< 无网络服务*/
    ESP_HF_CME_NETWORK_TIMEOUT = 31,              /*!< 网络超时*/
    ESP_HF_CME_NETWORK_NOT_ALLOWED = 32,          /*!< 不允许网络--仅限紧急呼叫*/
} esp_hf_cme_err_t;

/** 连接状态更改的回调。state将具有BtHfConnectionState中的一个值
 */
typedef void (* esp_hf_connection_state_callback)(esp_hf_connection_state_t state, esp_bd_addr_t *bd_addr);

/** 音频连接状态更改的回调。state将具有BtHfAudioState中的一个值
 */
typedef void (* esp_hf_audio_state_callback)(esp_hf_audio_state_t state, esp_bd_addr_t *bd_addr);

/** VR连接状态更改的回调。state将具有BtHfVRState中的一个值
 */
typedef void (* esp_hf_vr_cmd_callback)(esp_hf_vr_state_t state, esp_bd_addr_t *bd_addr);

/** 回拨接听来电（ATA）
 */
typedef void (* esp_hf_answer_call_cmd_callback)(esp_bd_addr_t *bd_addr);

/** 断开呼叫回拨（AT+CHUP）
 */
typedef void (* esp_hf_hangup_call_cmd_callback)(esp_bd_addr_t *bd_addr);

/** 断开呼叫（AT+CHUP）类型的回拨将表示扬声器/麦克风增益（BtHfVolumeControl）。
 */
typedef void (* esp_hf_volume_cmd_callback)(esp_hf_volume_control_target_t type, int volume, esp_bd_addr_t *bd_addr);

/** 拨出电话的回拨如果号码为空，则重拨
 */
typedef void (* esp_hf_dial_call_cmd_callback)(char *number, esp_bd_addr_t *bd_addr);

/** 用于发送DTMF音调的回调，音调包含要发送的DTMF字符
 */
typedef void (* esp_hf_dtmf_cmd_callback)(char tone, esp_bd_addr_t *bd_addr);

/** 启用/禁用降噪/回声消除的回调值将为1以启用，0以禁用
 */
typedef void (* esp_hf_nrec_cmd_callback)(esp_hf_nrec_t nrec, esp_bd_addr_t *bd_addr);

/** AT+BCS回调和BAC WBS事件启用，WBS禁用
 */
typedef void (* esp_hf_wbs_callback)(esp_hf_wbs_config_t wbs, esp_bd_addr_t *bd_addr);

/** 呼叫保持处理的回调（AT+CHLD）值将包含呼叫保持命令（0，1，2，3）
 */
typedef void (* esp_hf_chld_cmd_callback)(esp_hf_chld_type_t chld, esp_bd_addr_t *bd_addr);

/** CNUM回拨（用户号码）
 */
typedef void (* esp_hf_cnum_cmd_callback)(esp_bd_addr_t *bd_addr);

/** 指示器回调（CIND）
 */
typedef void (* esp_hf_cind_cmd_callback)(esp_bd_addr_t *bd_addr);

/** 操作员选择回调（COPS）
 */
typedef void (* esp_hf_cops_cmd_callback)(esp_bd_addr_t *bd_addr);

/** 呼叫列表回调（AT+CLCC）
 */
typedef void (* esp_hf_clcc_cmd_callback) (esp_bd_addr_t *bd_addr);

/** 来自AG AT_string的未知AT命令记录的回调将包含未分析的AT字符串
 */
typedef void (* esp_hf_unknown_at_cmd_callback)(char *at_string, esp_bd_addr_t *bd_addr);

/** 按键按压（HSP）事件的回调。
 */
typedef void (* esp_hf_key_pressed_cmd_callback)(esp_bd_addr_t *bd_addr);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_HF_DEFS_H__ */

