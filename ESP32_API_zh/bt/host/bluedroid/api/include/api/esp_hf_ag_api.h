// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#ifndef __ESP_HF_AG_API_H__
#define __ESP_HF_AG_API_H__

#include "esp_err.h"
#include "esp_bt_defs.h"
#include "esp_hf_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 具有HF AG掩模*/
#define ESP_HF_PEER_FEAT_3WAY       0x01        /* 三向呼叫*/
#define ESP_HF_PEER_FEAT_ECNR       0x02        /* 回声消除和/或降噪*/
#define ESP_HF_PEER_FEAT_VREC       0x04        /* 语音识别*/
#define ESP_HF_PEER_FEAT_INBAND     0x08        /* 带内铃声*/
#define ESP_HF_PEER_FEAT_VTAG       0x10        /* 将电话号码附加到声控标签*/
#define ESP_HF_PEER_FEAT_REJECT     0x20        /* 拒绝来电的能力*/
#define ESP_HF_PEER_FEAT_ECS        0x40        /* 增强的呼叫状态*/
#define ESP_HF_PEER_FEAT_ECC        0x80        /* 增强的呼叫控制*/
#define ESP_HF_PEER_FEAT_EXTERR    0x100        /* 扩展错误代码*/
#define ESP_HF_PEER_FEAT_CODEC     0x200        /* 编解码器协商*/

/* HF AG的CHLD特征掩模*/
#define ESP_HF_CHLD_FEAT_REL           0x01       /* 0释放等待呼叫或保留呼叫*/
#define ESP_HF_CHLD_FEAT_REL_ACC       0x02       /* 1释放激活的呼叫并接受其他等待或保持的呼叫*/
#define ESP_HF_CHLD_FEAT_REL_X         0x04       /* 1x仅释放指定的活动呼叫*/
#define ESP_HF_CHLD_FEAT_HOLD_ACC      0x08       /* 2个挂起的活动呼叫，并接受其他等待或挂起的呼叫*/
#define ESP_HF_CHLD_FEAT_PRIV_X        0x10       /* 2x使用指定的呼叫请求私人模式（将其余呼叫保持）*/
#define ESP_HF_CHLD_FEAT_MERGE         0x20       /* 3将保留呼叫添加到多方*/
#define ESP_HF_CHLD_FEAT_MERGE_DETACH  0x40       /* 4接通两个电话并离开（断开多方通话）*/

///HF回调事件
typedef enum
{
    ESP_HF_CONNECTION_STATE_EVT = 0,          /*!< 连接状态已更改事件*/
    ESP_HF_AUDIO_STATE_EVT,                   /*!< 音频连接状态更改事件*/
    ESP_HF_BVRA_RESPONSE_EVT,                 /*!< 语音识别状态更改事件*/
    ESP_HF_VOLUME_CONTROL_EVT,                /*!< 来自HF客户端的音频音量控制命令，由+VGM或+VGS消息提供*/

    ESP_HF_UNAT_RESPONSE_EVT,                 /*!< 未知AT cmd响应*/
    ESP_HF_IND_UPDATE_EVT,                    /*!< 指示器更新事件*/
    ESP_HF_CIND_RESPONSE_EVT,                 /*!< 呼叫和设备指示器响应*/
    ESP_HF_COPS_RESPONSE_EVT,                 /*!< 当前操作员信息*/
    ESP_HF_CLCC_RESPONSE_EVT,                 /*!< 当前通话通知列表*/
    ESP_HF_CNUM_RESPONSE_EVT,                 /*!< HF客户端的用户信息响应*/
    ESP_HF_VTS_RESPONSE_EVT,                  /*!< 是否启用DTMF*/
    ESP_HF_NREC_RESPONSE_EVT,                 /*!< 是否启用NREC*/

    ESP_HF_ATA_RESPONSE_EVT,                  /*!< 接听来电*/
    ESP_HF_CHUP_RESPONSE_EVT,                 /*!< 拒绝来电*/
    ESP_HF_DIAL_EVT,                          /*!< 使用特定号码拨打呼出电话或拨打最后一个号码*/
    ESP_HF_WBS_RESPONSE_EVT,                  /*!< 编解码器状态*/
    ESP_HF_BCS_RESPONSE_EVT,                  /*!< 最终编解码器选择*/
} esp_hf_cb_event_t;

///HFP AG回调参数
typedef union
{
    /**
     * @brief  ESP_HS_CONNECTION_STATE_EVT
     */
    struct hf_conn_stat_param {
        esp_bd_addr_t remote_bda;                 /*!< 远程蓝牙设备地址*/
        esp_hf_connection_state_t state;          /*!< 连接状态*/
        uint32_t peer_feat;                       /*!< HF支持的功能*/
        uint32_t chld_feat;                       /*!< AG支持呼叫保持和多方服务功能*/
    } conn_stat;                                  /*!< ESP_HF_CONNECTION_STATE_EVT的AG回调参数*/

    /**
     * @brief ESP_HF_AUDIO_STATE_EVT
     */
    struct hf_audio_stat_param {
        esp_bd_addr_t remote_addr;                /*!< 远程蓝牙设备地址*/
        esp_hf_audio_state_t state;               /*!< 音频连接状态*/
    } audio_stat;                                 /*!< ESP_HF_AUDIO_STATE_VT的AG回调参数*/

    /**
     * @brief ESP_HF_BVRA_RESPONSE_EVT
     */
    struct hf_vra_rep_param {
        esp_bd_addr_t     remote_addr;            /*!< 远程蓝牙设备地址*/
        esp_hf_vr_state_t value;                  /*!< 语音识别状态*/
    } vra_rep;                                    /*!< ESP_HF_BVRA_RESPONSE_EVT的AG回调参数*/

    /**
     * @brief ESP_HF_VOLUME_CONTROL_EVT
     */
    struct hf_volume_control_param {
        esp_hf_volume_type_t type;                /*!< 音量控制目标、扬声器或麦克风*/
        int volume;                               /*!< 增益，范围从0到15*/
    } volume_control;                             /*!< ESP_HF_VOLUME_CONTROL_EVT的AG回调参数*/

    /**
     * @brief ESP_HF_UNAT_RESPOSNE_EVT
     */
    struct hf_unat_rep_param {
        char *unat;                               /*!< 未知AT命令字符串*/
    }unat_rep;                                    /*!< ESP_HF_UNAT_REPONSE_EVT的AG回调参数*/

    /**
     * @brief ESP_HF_CIND_RESPONSE_EVT
     */
    struct hf_cind_param {
        esp_hf_call_status_t       call_status;         /*!< 呼叫状态指示器*/
        esp_hf_call_setup_status_t call_setup_status;   /*!< 呼叫设置状态指示器*/
        esp_hf_network_state_t svc;                     /*!< 蓝牙专有呼叫保持状态指示器*/
        int signal_strength;                            /*!< 蓝牙专有呼叫保持状态指示器*/
        esp_hf_roaming_status_t roam;                   /*!< 蓝牙专有呼叫保持状态指示器*/
        int battery_level;                              /*!< 电池充电值，范围从0到5*/
        esp_hf_call_held_status_t  call_held_status;    /*!< 蓝牙专有呼叫保持状态指示器*/
    } cind;                                             /*!< ESP_HF_CIND_REPONSE_EVT的AG回调参数*/

    /**
     * @brief ESP_HF_DIAL_EVT
     */
    struct hf_out_call_param {
        esp_bd_addr_t remote_addr;                /*!< 远程蓝牙设备地址*/
        char *num_or_loc;                         /*!< 手机存储器中的位置*/
    } out_call;                                   /*!< ESP_HF_DIAL_EVT的AG回调参数*/

    /**
     * @brief ESP_HF_VTS_RESPOSNE_EVT
     */
    struct hf_vts_rep_param {
        char *code;                               /*!< 来自HF客户端的MTF代码*/
    }vts_rep;                                     /*!< ESP_HF_VTS_RESPONSE_EVT的AG回调参数*/

    /**
     * @brief ESP_HF_NREC_RESPOSNE_EVT
     */
    struct hf_nrec_param {
       esp_hf_nrec_t state;                       /*!< NREC已启用或已禁用*/
    } nrec;                                       /*!< ESP_HF_NREC_RESPONSE_EVT的AG回调参数*/

    /**
     * @brief ESP_HF_WBS_RESPONSE_EVT
     */
    struct hf_wbs_rep_param {
        esp_hf_wbs_config_t codec;                /*!< 编解码器模式CVSD或mSBC*/
    } wbs_rep;                                    /*!< ESP_HF_WBS_RESPONSE_EVT的AG回调参数*/

    /**
     * @brief ESP_HF_BCS_RESPONSE_EVT
     */
    struct hf_bcs_rep_param {
        esp_hf_wbs_config_t mode;                 /*!< 编解码器模式CVSD或mSBC*/
    } bcs_rep;                                    /*!< ESP_HF_BCS_RESPONSE_EVT的AG回调参数*/

} esp_hf_cb_param_t;                              /*!< HFP AG回调参数复合*/

/**
 * @brief           AG传入数据回调函数，回调在Voice Over HCI的情况下非常有用。
 *
 * @param[in]       buf ：指向传入数据的指针（HCI同步数据包的有效负载），缓冲区分配在蓝牙协议栈中，并将在回调调用完成后释放。
 *
 * @param[in]       len ：buf中的大小（字节）
 */
typedef void (* esp_hf_incoming_data_cb_t)(const uint8_t *buf, uint32_t len);

/**
 * @brief           AG传出数据回调函数，回调在Voice Over HCI的情况下非常有用。一旦建立了音频连接，并且应用层已经准备好要发送的数据，下层将调用此函数读取数据，然后发送。此回调应该以非阻塞方式实现，如果数据不足，则应该返回值0。
 *
 * @param[in]       buf ：指向传入数据的指针（HCI同步数据包的有效负载），缓冲区分配在蓝牙协议栈中，并将在回调调用完成后释放。
 *
 * @param[in]       len ：buf中的大小（字节）
 *
 * @return          成功读取的数据长度
 */
typedef uint32_t (* esp_hf_outgoing_data_cb_t) (uint8_t *buf, uint32_t len);

/**
 * @brief           HF AG回调函数类型
 *
 * @param           event ：事件类型
 *
 * @param           param ：指向回调参数的指针
 */
typedef void (* esp_hf_cb_t) (esp_hf_cb_event_t event, esp_hf_cb_param_t *param);

/************************************************************************************
**  ESP HF API
************************************************************************************/
/**
 * @brief           向HFP AG模块注册应用程序回调函数。只有在esp_bluedroid_enable（）成功完成后才能调用此函数。
 *
 * @param[in]       callback: HFP AG事件回调函数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：如果回调是NULL函数指针
 *
 */
esp_err_t esp_bt_hf_register_callback(esp_hf_cb_t callback);

/**
 *
 * @brief           初始化蓝牙HF AG模块。应在esp_bluedroid_enable（）成功完成后调用此函数。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 *
 * @return
 *                  -ESP_OK：如果初始化请求发送成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_init(esp_bd_addr_t remote_addr);

/**
 *
 * @brief           取消HF AG模块的初始化。只有在esp_bluedroid_enable（）成功完成后才能调用此函数。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_deinit(esp_bd_addr_t remote_addr);

/**
 *
 * @brief           建立到远程蓝牙HFP客户端设备的服务级别连接。必须在esp_bt_hf_init（）之后和esp_bt_hf_deinit（）之前调用此函数。
 *
 * @param[in]       remote_bda: 远程蓝牙HFP客户端设备地址
 *
 * @return
 *                  -ESP_OK：连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_connect(esp_bd_addr_t remote_bda);

/**
 *
 * @brief           断开与远程HFP客户端的连接。必须在esp_bt_hf_init（）之后和esp_bt_hf_deinit（）之前调用此函数。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_disconnect(esp_bd_addr_t remote_bda);

/**
 *
 * @brief           创建与远程HFP客户端的音频连接。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_connect_audio(esp_bd_addr_t remote_bda);

/**
 *
 * @brief           释放与远程HFP客户端建立的音频连接。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_disconnect_audio(esp_bd_addr_t remote_bda);

/**
 *
 * @brief           HFP客户端的音量识别命令（AT+VRA）响应。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_bda: 语音识别发起者的设备地址
 *
 * @param[in]       value: 0-禁用语音识别，1-启用语音识别
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_vra(esp_bd_addr_t remote_bda, esp_hf_vr_state_t value);

/**
 *
 * @brief           与HFP客户端的卷同步。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 *
 * @param[in]       type: 音量控制目标、扬声器或麦克风
 *
 * @param[in]       volume: 麦克风扬声器的增益，范围为0到15
 *
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_volume_control(esp_bd_addr_t remote_bda, esp_hf_volume_control_target_t type, int volume);

 /**
 *
 * @brief           处理来自HFP客户端的未知AT命令。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 *
 * @param[in]       unat: 用户AT对HF客户端的命令响应。如果unat为NULL，默认情况下它将响应“ERROR”。
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_hf_unat_response(esp_bd_addr_t remote_addr, char *unat);

 /**
 *
 * @brief           未经请求向HFP客户端发送扩展AT错误代码。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_bda: 远程蓝牙设备地址
 * @param[in]       response_code: AT命令响应代码
 * @param[in]       error_code: CME错误代码
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_cmee_response(esp_bd_addr_t remote_bda, esp_hf_at_response_code_t response_code, esp_hf_cme_err_t error_code);

 /**
 *
 * @brief           我们主动向HFP客户端发送设备状态通知。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 * @param[in]       call_state: 呼叫状态
 * @param[in]       call_setup_state: 呼叫设置状态
 * @param[in]       ntk_state: 网络服务状态
 * @param[in]       signal: 信号强度从0到5
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_indchange_notification(esp_bd_addr_t remote_addr, esp_hf_call_status_t call_state,
                                            esp_hf_call_setup_status_t call_setup_state,
                                            esp_hf_network_state_t ntk_state, int signal);

 /**
 *
 * @brief           对HFP客户的设备个体指标的响应。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 * @param[in]       call_state: 呼叫状态
 * @param[in]       call_setup_state: 呼叫设置状态
 * @param[in]       ntk_state: 网络服务状态
 * @param[in]       signal: 信号强度从0到5
 * @param[in]       roam: 漫游状态
 * @param[in]       batt_lev: 电池电平从0到5
 * @param[in]       call_held_status: 呼叫保持状态
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_cind_response(esp_bd_addr_t remote_addr,
                                esp_hf_call_status_t call_state,
                                esp_hf_call_setup_status_t call_setup_state,
                                esp_hf_network_state_t ntk_state, int signal, esp_hf_roaming_status_t roam, int batt_lev,
                                esp_hf_call_held_status_t call_held_status);

/**
 *
 * @brief           HF客户端对AT+COPS命令的响应。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 * @param[in]       name: 当前操作员名称
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_cops_response(esp_bd_addr_t remote_addr, char *name);

/**
 *
 * @brief           HFP客户端对AT+CLCC命令的响应。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 * @param[in]       index: 当前调用的索引
 * @param[in]       dir: 呼叫方向（传入/传出）
 * @param[in]       current_call_state: 当前呼叫状态
 * @param[in]       mode: 当前通话模式（语音/数据/传真）
 * @param[in]       mpty: 单一或多类型
 * @param[in]       number: 当前呼叫号码
 * @param[in]       type: 国际类型或未知
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_clcc_response(esp_bd_addr_t remote_addr, int index, esp_hf_current_call_direction_t dir,
                                 esp_hf_current_call_status_t current_call_state, esp_hf_current_call_mode_t mode,
                                 esp_hf_current_call_mpty_type_t mpty, char *number, esp_hf_call_addr_type_t type);

/**
 *
 * @brief           HF客户端对AT+CNUM命令的响应。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 * @param[in]       number: 登记号码
 * @param[in]       type: 服务类型（未知/语音/传真）
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_cnum_response(esp_bd_addr_t remote_addr, char *number, esp_hf_subscriber_service_type_t type);

/**
 *
 * @brief           通知HF客户AG是否提供带内铃声。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 * @param[in]       state: 带内铃声状态
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_bsir(esp_bd_addr_t remote_addr, esp_hf_in_band_ring_state_t state);

/**
 *
 * @brief           接听来自AG的来电。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 * @param[in]       num_active: 活动呼叫数
 * @param[in]       num_held: 保持通话的次数
 * @param[in]       call_state: 呼叫状态
 * @param[in]       call_setup_state: 呼叫设置状态
 * @param[in]       number: 来电号码
 * @param[in]       call_addr_type: 呼叫地址类型
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_answer_call(esp_bd_addr_t remote_addr, int num_active, int num_held,
                                esp_hf_call_status_t call_state,  esp_hf_call_setup_status_t call_setup_state,
                                char *number, esp_hf_call_addr_type_t call_addr_type);

/**
 *
 * @brief           拒绝来自AG的来电。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 * @param[in]       num_active: 活动呼叫数
 * @param[in]       num_held: 保持通话的次数
 * @param[in]       call_state: 呼叫状态
 * @param[in]       call_setup_state: 呼叫设置状态
 * @param[in]       number: 来电号码
 * @param[in]       call_addr_type: 呼叫地址类型
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_reject_call(esp_bd_addr_t remote_addr, int num_active, int num_held,
                                esp_hf_call_status_t call_state,  esp_hf_call_setup_status_t call_setup_state,
                                char *number, esp_hf_call_addr_type_t call_addr_type);

/**
 *
 * @brief           从AG发起呼叫。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 * @param[in]       num_active: 活动呼叫数
 * @param[in]       num_held: 保持通话的次数
 * @param[in]       call_state: 呼叫状态
 * @param[in]       call_setup_state: 呼叫设置状态
 * @param[in]       number: 呼出电话号码
 * @param[in]       call_addr_type: 呼叫地址类型
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_out_call(esp_bd_addr_t remote_addr, int num_active, int num_held,
                            esp_hf_call_status_t call_state,  esp_hf_call_setup_status_t call_setup_state,
                            char *number, esp_hf_call_addr_type_t call_addr_type);

/**
 *
 * @brief           结束正在进行的通话。作为使用此API的前提条件，HFP客户端应存在服务级别连接。
 *
 * @param[in]       remote_addr: 远程蓝牙设备地址
 * @param[in]       num_active: 活动呼叫数
 * @param[in]       num_held: 保持通话的次数
 * @param[in]       call_state: 呼叫状态
 * @param[in]       call_setup_state: 呼叫设置状态
 * @param[in]       number: 电话号码
 * @param[in]       call_addr_type: 呼叫地址类型
 * @return
 *                  -ESP_OK：断开连接请求发送到下层
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_bt_hf_end_call(esp_bd_addr_t remote_addr, int num_active, int num_held,
                            esp_hf_call_status_t call_state,  esp_hf_call_setup_status_t call_setup_state,
                            char *number, esp_hf_call_addr_type_t call_addr_type);

/**
 * @brief           寄存器AG数据输出功能。回调仅在启用了Voice Over HCI的情况下使用。
 *
 * @param[in]       recv: HFP客户端传入数据回调函数
 * @param[in]       send: HFP客户端传出数据回调函数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：如果回调是NULL函数指针
 *
 */
esp_err_t esp_bt_hf_register_data_callback(esp_hf_incoming_data_cb_t recv, esp_hf_outgoing_data_cb_t send);


/**
 * @brief           触发下层以获取和发送音频数据。
 *
 *                  此功能仅在启用了Voice Over HCI的情况下使用。作为使用此API的前提条件，HFP客户端应存在服务级别连接。调用此函数后，下层将调用esp_hf_client_outgoing_data_cb_t来获取数据
 *
 */
void esp_hf_outgoing_data_ready(void);

#ifdef __cplusplus
}
#endif

#endif //__ESP_HF_AG_API_H__

