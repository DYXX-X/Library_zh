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

#ifndef __ESP_AVRC_API_H__
#define __ESP_AVRC_API_H__

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_bt_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_AVRC_TRANS_LABEL_MAX        15       /*!< 最大事务标签*/

///AVRC特征位掩码
typedef enum {
    ESP_AVRC_FEAT_RCTG = 0x0001,                 /*!< 遥控目标*/
    ESP_AVRC_FEAT_RCCT = 0x0002,                 /*!< 遥控控制器*/
    ESP_AVRC_FEAT_VENDOR = 0x0008,               /*!< 远程控制供应商相关命令*/
    ESP_AVRC_FEAT_BROWSE = 0x0010,               /*!< 使用浏览频道*/
    ESP_AVRC_FEAT_META_DATA = 0x0040,            /*!< 远程控制元数据传输命令/响应*/
    ESP_AVRC_FEAT_ADV_CTRL = 0x0200,             /*!< 远程控制高级控制命令/响应*/
} esp_avrc_features_t;

///SDP记录中检索到AVRC支持的功能标志
typedef enum {
    ESP_AVRC_FEAT_FLAG_CAT1 = 0x0001,                             /*!< 类别1*/
    ESP_AVRC_FEAT_FLAG_CAT2 = 0x0002,                             /*!< 第2类*/
    ESP_AVRC_FEAT_FLAG_CAT3 = 0x0004,                             /*!< 第3类*/
    ESP_AVRC_FEAT_FLAG_CAT4 = 0x0008,                             /*!< 第4类*/
    ESP_AVRC_FEAT_FLAG_BROWSING = 0x0040,                         /*!< 浏览*/
    ESP_AVRC_FEAT_FLAG_COVER_ART_GET_IMAGE_PROP = 0x0080,         /*!< 封面艺术GetImageProperties*/
    ESP_AVRC_FEAT_FLAG_COVER_ART_GET_IMAGE = 0x0100,              /*!< 封面艺术获取图像*/
    ESP_AVRC_FEAT_FLAG_COVER_ART_GET_LINKED_THUMBNAIL = 0x0200,   /*!< 封面艺术获取链接缩略图*/
} esp_avrc_feature_flag_t;

///AVRC直通命令代码
typedef enum {
    ESP_AVRC_PT_CMD_SELECT         =   0x00,    /*!< 选择*/
    ESP_AVRC_PT_CMD_UP             =   0x01,    /*!< 向上的*/
    ESP_AVRC_PT_CMD_DOWN           =   0x02,    /*!< 向下*/
    ESP_AVRC_PT_CMD_LEFT           =   0x03,    /*!< 左边*/
    ESP_AVRC_PT_CMD_RIGHT          =   0x04,    /*!< 正确的*/
    ESP_AVRC_PT_CMD_RIGHT_UP       =   0x05,    /*!< 向上*/
    ESP_AVRC_PT_CMD_RIGHT_DOWN     =   0x06,    /*!< 向右向下*/
    ESP_AVRC_PT_CMD_LEFT_UP        =   0x07,    /*!< 左上*/
    ESP_AVRC_PT_CMD_LEFT_DOWN      =   0x08,    /*!< 左下*/
    ESP_AVRC_PT_CMD_ROOT_MENU      =   0x09,    /*!< 根菜单*/
    ESP_AVRC_PT_CMD_SETUP_MENU     =   0x0A,    /*!< 设置菜单*/
    ESP_AVRC_PT_CMD_CONT_MENU      =   0x0B,    /*!< 目录菜单*/
    ESP_AVRC_PT_CMD_FAV_MENU       =   0x0C,    /*!< 收藏夹菜单*/
    ESP_AVRC_PT_CMD_EXIT           =   0x0D,    /*!< 出口*/
    ESP_AVRC_PT_CMD_0              =   0x20,    /*!< 0 */
    ESP_AVRC_PT_CMD_1              =   0x21,    /*!< 1 */
    ESP_AVRC_PT_CMD_2              =   0x22,    /*!< 2 */
    ESP_AVRC_PT_CMD_3              =   0x23,    /*!< 3 */
    ESP_AVRC_PT_CMD_4              =   0x24,    /*!< 4 */
    ESP_AVRC_PT_CMD_5              =   0x25,    /*!< 5 */
    ESP_AVRC_PT_CMD_6              =   0x26,    /*!< 6 */
    ESP_AVRC_PT_CMD_7              =   0x27,    /*!< 7 */
    ESP_AVRC_PT_CMD_8              =   0x28,    /*!< 8 */
    ESP_AVRC_PT_CMD_9              =   0x29,    /*!< 9 */
    ESP_AVRC_PT_CMD_DOT            =   0x2A,    /*!< 点*/
    ESP_AVRC_PT_CMD_ENTER          =   0x2B,    /*!< 进来*/
    ESP_AVRC_PT_CMD_CLEAR          =   0x2C,    /*!< 清楚的*/
    ESP_AVRC_PT_CMD_CHAN_UP        =   0x30,    /*!< 通道向上*/
    ESP_AVRC_PT_CMD_CHAN_DOWN      =   0x31,    /*!< 通道关闭*/
    ESP_AVRC_PT_CMD_PREV_CHAN      =   0x32,    /*!< 前一频道*/
    ESP_AVRC_PT_CMD_SOUND_SEL      =   0x33,    /*!< 声音选择*/
    ESP_AVRC_PT_CMD_INPUT_SEL      =   0x34,    /*!< 输入选择*/
    ESP_AVRC_PT_CMD_DISP_INFO      =   0x35,    /*!< 显示信息*/
    ESP_AVRC_PT_CMD_HELP           =   0x36,    /*!< 帮助*/
    ESP_AVRC_PT_CMD_PAGE_UP        =   0x37,    /*!< 向上翻页*/
    ESP_AVRC_PT_CMD_PAGE_DOWN      =   0x38,    /*!< 向下翻页*/
    ESP_AVRC_PT_CMD_POWER          =   0x40,    /*!< 权力*/
    ESP_AVRC_PT_CMD_VOL_UP         =   0x41,    /*!< 音量增大*/
    ESP_AVRC_PT_CMD_VOL_DOWN       =   0x42,    /*!< 音量降低*/
    ESP_AVRC_PT_CMD_MUTE           =   0x43,    /*!< 沉默的*/
    ESP_AVRC_PT_CMD_PLAY           =   0x44,    /*!< 玩*/
    ESP_AVRC_PT_CMD_STOP           =   0x45,    /*!< 停止*/
    ESP_AVRC_PT_CMD_PAUSE          =   0x46,    /*!< 暂停*/
    ESP_AVRC_PT_CMD_RECORD         =   0x47,    /*!< 记录*/
    ESP_AVRC_PT_CMD_REWIND         =   0x48,    /*!< 重绕*/
    ESP_AVRC_PT_CMD_FAST_FORWARD   =   0x49,    /*!< 快进*/
    ESP_AVRC_PT_CMD_EJECT          =   0x4A,    /*!< 弹出*/
    ESP_AVRC_PT_CMD_FORWARD        =   0x4B,    /*!< 向前地*/
    ESP_AVRC_PT_CMD_BACKWARD       =   0x4C,    /*!< 向后的*/
    ESP_AVRC_PT_CMD_ANGLE          =   0x50,    /*!< 角*/
    ESP_AVRC_PT_CMD_SUBPICT        =   0x51,    /*!< 子画面*/
    ESP_AVRC_PT_CMD_F1             =   0x71,    /*!< F1 */
    ESP_AVRC_PT_CMD_F2             =   0x72,    /*!< F2 */
    ESP_AVRC_PT_CMD_F3             =   0x73,    /*!< F3 */
    ESP_AVRC_PT_CMD_F4             =   0x74,    /*!< F4 */
    ESP_AVRC_PT_CMD_F5             =   0x75,    /*!< F5 */
    ESP_AVRC_PT_CMD_VENDOR         =   0x7E,    /*!< 供应商独有*/
} esp_avrc_pt_cmd_t;

///AVRC直通命令筛选器
typedef enum {
    ESP_AVRC_PSTH_FILTER_ALLOWED_CMD = 0,       /*!< 所有可以使用的PASSTHROUGH命令都是不可修改的*/
    ESP_AVRC_PSTH_FILTER_SUPPORTED_CMD = 1,     /*!< 根据当前配置有选择地支持PASSTHROUGH命令*/
    ESP_AVRC_PSTH_FILTER_SUPPORT_MAX,
} esp_avrc_psth_filter_t;

///AVRC直通命令位掩码
typedef struct {
    uint16_t bits[8];                           /*!< PASSTHROUGH命令的位掩码表示*/
} esp_avrc_psth_bit_mask_t;

typedef enum {
    ESP_AVRC_BIT_MASK_OP_TEST = 0,      /*!< 测试特定位的操作代码*/
    ESP_AVRC_BIT_MASK_OP_SET = 1,       /*!< 设置特定位的操作代码*/
    ESP_AVRC_BIT_MASK_OP_CLEAR = 2,     /*!< 清除特定位的操作代码*/
} esp_avrc_bit_mask_op_t;

///AVRC直通命令状态
typedef enum {
    ESP_AVRC_PT_CMD_STATE_PRESSED = 0,           /*!< 按键已按下*/
    ESP_AVRC_PT_CMD_STATE_RELEASED = 1           /*!< 密钥已释放*/
} esp_avrc_pt_cmd_state_t;

///AVRC控制器回调事件
typedef enum {
    ESP_AVRC_CT_CONNECTION_STATE_EVT = 0,        /*!< 连接状态更改事件*/
    ESP_AVRC_CT_PASSTHROUGH_RSP_EVT = 1,         /*!< 传递响应事件*/
    ESP_AVRC_CT_METADATA_RSP_EVT = 2,            /*!< 元数据响应事件*/
    ESP_AVRC_CT_PLAY_STATUS_RSP_EVT = 3,         /*!< 播放状态响应事件*/
    ESP_AVRC_CT_CHANGE_NOTIFY_EVT = 4,           /*!< 通知事件*/
    ESP_AVRC_CT_REMOTE_FEATURES_EVT = 5,         /*!< 远程设备指示事件的特征*/
    ESP_AVRC_CT_GET_RN_CAPABILITIES_RSP_EVT = 6,     /*!< 对等设备支持的通知事件功能*/
    ESP_AVRC_CT_SET_ABSOLUTE_VOLUME_RSP_EVT = 7, /*!< 设置绝对音量响应事件*/
} esp_avrc_ct_cb_event_t;

///AVRC目标回调事件
typedef enum {
    ESP_AVRC_TG_CONNECTION_STATE_EVT = 0,          /*!< 连接状态更改事件*/
    ESP_AVRC_TG_REMOTE_FEATURES_EVT = 1,           /*!< 远程设备指示事件的特征*/
    ESP_AVRC_TG_PASSTHROUGH_CMD_EVT = 2,           /*!< passthrough命令事件*/
    ESP_AVRC_TG_SET_ABSOLUTE_VOLUME_CMD_EVT = 3,   /*!< 从远程设备设置绝对音量命令*/
    ESP_AVRC_TG_REGISTER_NOTIFICATION_EVT = 4,     /*!< 注册通知事件*/
    ESP_AVRC_TG_SET_PLAYER_APP_VALUE_EVT = 5,      /*!< 设置应用程序属性值，属性参考esp_avrc_ps_attr_ids_t*/
} esp_avrc_tg_cb_event_t;

///AVRC元数据属性掩码
typedef enum {
    ESP_AVRC_MD_ATTR_TITLE = 0x1,                 /*!< 播放曲目的标题*/
    ESP_AVRC_MD_ATTR_ARTIST = 0x2,                /*!< 曲目艺术家*/
    ESP_AVRC_MD_ATTR_ALBUM = 0x4,                 /*!< 唱片集名称*/
    ESP_AVRC_MD_ATTR_TRACK_NUM = 0x8,             /*!< 专辑中的曲目位置*/
    ESP_AVRC_MD_ATTR_NUM_TRACKS = 0x10,           /*!< 专辑中的曲目数*/
    ESP_AVRC_MD_ATTR_GENRE = 0x20,                /*!< 曲目类型*/
    ESP_AVRC_MD_ATTR_PLAYING_TIME = 0x40          /*!< 总专辑播放时间（毫秒）*/
} esp_avrc_md_attr_mask_t;

///AVRC事件通知ID
typedef enum {
    ESP_AVRC_RN_PLAY_STATUS_CHANGE = 0x01,        /*!< 曲目状态更改，例如从播放到暂停*/
    ESP_AVRC_RN_TRACK_CHANGE = 0x02,              /*!< 新曲目已加载*/
    ESP_AVRC_RN_TRACK_REACHED_END = 0x03,         /*!< 当前轨道到达终点*/
    ESP_AVRC_RN_TRACK_REACHED_START = 0x04,       /*!< 当前轨道到达起始位置*/
    ESP_AVRC_RN_PLAY_POS_CHANGED = 0x05,          /*!< 曲目播放位置已更改*/
    ESP_AVRC_RN_BATTERY_STATUS_CHANGE = 0x06,     /*!< 电池状态已更改*/
    ESP_AVRC_RN_SYSTEM_STATUS_CHANGE = 0x07,      /*!< 系统状态已更改*/
    ESP_AVRC_RN_APP_SETTING_CHANGE = 0x08,        /*!< 应用程序设置已更改*/
    ESP_AVRC_RN_NOW_PLAYING_CHANGE = 0x09,        /*!< 现在播放内容已更改*/
    ESP_AVRC_RN_AVAILABLE_PLAYERS_CHANGE = 0x0a,  /*!< 可用玩家已更改*/
    ESP_AVRC_RN_ADDRESSED_PLAYER_CHANGE = 0x0b,   /*!< 被寻址的播放器已更改*/
    ESP_AVRC_RN_UIDS_CHANGE = 0x0c,               /*!< UID已更改*/
    ESP_AVRC_RN_VOLUME_CHANGE = 0x0d,             /*!< TG上的体积局部改变*/
    ESP_AVRC_RN_MAX_EVT
} esp_avrc_rn_event_ids_t;

///AVRC目标通知事件通知功能
typedef enum {
    ESP_AVRC_RN_CAP_ALLOWED_EVT = 0,              /*!< 所有可能支持的、不可变的通知事件*/
    ESP_AVRC_RN_CAP_SUPPORTED_EVT = 1,            /*!< 根据当前配置选择性地支持通知事件*/
    ESP_AVRC_RN_CAP_MAX,
} esp_avrc_rn_evt_cap_t;

///AVRC目标通知事件能力位掩码
typedef struct {
    uint16_t bits;                                /*!< PASSTHROUGH命令的位掩码表示*/
} esp_avrc_rn_evt_cap_mask_t;

///AVRC通知响应类型
typedef enum {
    ESP_AVRC_RN_RSP_INTERIM = 13,     /*!< 对RegisterNotification的初始响应应在收到命令后发送T_mtp（1000ms）*/
    ESP_AVRC_RN_RSP_CHANGED = 15,     /*!< RegisterNotification命令的最终响应*/
} esp_avrc_rn_rsp_t;

///AVRC播放器设置ID
typedef enum {
    ESP_AVRC_PS_EQUALIZER = 0x01,                 /*!< 均衡器，打开或关闭*/
    ESP_AVRC_PS_REPEAT_MODE = 0x02,               /*!< 重复模式*/
    ESP_AVRC_PS_SHUFFLE_MODE = 0x03,              /*!< 混洗模式*/
    ESP_AVRC_PS_SCAN_MODE = 0x04,                 /*!< 扫描模式打开或关闭*/
    ESP_AVRC_PS_MAX_ATTR
} esp_avrc_ps_attr_ids_t;

///AVRC均衡器模式
typedef enum {
    ESP_AVRC_PS_EQUALIZER_OFF = 0x1,              /*!< 均衡器关闭*/
    ESP_AVRC_PS_EQUALIZER_ON = 0x2                /*!< 均衡器开启*/
} esp_avrc_ps_eq_value_ids_t;

///AVRC重复模式
typedef enum {
    ESP_AVRC_PS_REPEAT_OFF = 0x1,                 /*!< 重复模式关闭*/
    ESP_AVRC_PS_REPEAT_SINGLE = 0x2,              /*!< 单线重复*/
    ESP_AVRC_PS_REPEAT_GROUP = 0x3                /*!< 组重复*/
} esp_avrc_ps_rpt_value_ids_t;


///AVRC混洗模式
typedef enum {
    ESP_AVRC_PS_SHUFFLE_OFF = 0x1,                /*<! 洗牌*/
    ESP_AVRC_PS_SHUFFLE_ALL = 0x2,                /*<! 随机播放所有曲目*/
    ESP_AVRC_PS_SHUFFLE_GROUP = 0x3               /*<! 组洗牌*/
} esp_avrc_ps_shf_value_ids_t;

///AVRC扫描模式
typedef enum {
    ESP_AVRC_PS_SCAN_OFF = 0x1,                   /*!< 扫描关闭*/
    ESP_AVRC_PS_SCAN_ALL = 0x2,                   /*!< 所有磁道扫描*/
    ESP_AVRC_PS_SCAN_GROUP = 0x3                  /*!< 组扫描*/
} esp_avrc_ps_scn_value_ids_t;

///AVCTP响应代码
typedef enum {
    ESP_AVRC_RSP_NOT_IMPL   = 8,                  /*!< 未实施*/
    ESP_AVRC_RSP_ACCEPT     = 9,                  /*!< 接受*/
    ESP_AVRC_RSP_REJECT     = 10,                 /*!< 拒绝*/
    ESP_AVRC_RSP_IN_TRANS   = 11,                 /*!< 处于过渡状态*/
    ESP_AVRC_RSP_IMPL_STBL  = 12,                 /*!< 已实施/稳定*/
    ESP_AVRC_RSP_CHANGED    = 13,                 /*!< 改变*/
    ESP_AVRC_RSP_INTERIM    = 15,                 /*!< 临时的*/
} esp_avrc_rsp_t;

///AVRCP电池状态
typedef enum {
    ESP_AVRC_BATT_NORMAL       = 0,               /*!< 正常状态，正常状态*/
    ESP_AVRC_BATT_WARNING      = 1,               /*!< 无法很快操作*/
    ESP_AVRC_BATT_CRITICAL     = 2,               /*!< 不能再操作了*/
    ESP_AVRC_BATT_EXTERNAL     = 3,               /*!< 插入外部电源*/
    ESP_AVRC_BATT_FULL_CHARGE  = 4,               /*!< 从外部电源完全充电时*/
} esp_avrc_batt_stat_t;

///AVRCP当前播放状态
typedef enum {
    ESP_AVRC_PLAYBACK_STOPPED = 0,                /*!< 停止*/
    ESP_AVRC_PLAYBACK_PLAYING = 1,                /*!< 玩*/
    ESP_AVRC_PLAYBACK_PAUSED = 2,                 /*!< 暂停*/
    ESP_AVRC_PLAYBACK_FWD_SEEK = 3,               /*!< 正向搜索*/
    ESP_AVRC_PLAYBACK_REV_SEEK = 4,               /*!< 反向搜索*/
    ESP_AVRC_PLAYBACK_ERROR = 0xFF,               /*!< 错误*/
} esp_avrc_playback_stat_t;

///AVRCP通知参数
typedef union
{
    uint8_t volume;                          /*!< ESP_AVRC_RN_VOLUME_CHANGE的响应数据，范围0..127*/
    esp_avrc_playback_stat_t playback;       /*!< ESP_AVRC_RN_PLAY_STATUS_CHANGE的响应数据*/
    uint8_t elm_id[8];                       /*!< ESP_AVRC_RN_TRACK_CHANGE的响应数据*/
    uint32_t play_pos;                       /*!< ESP_AVRC_RN_PLAY_POS_CHANGED的响应数据（毫秒）*/
    esp_avrc_batt_stat_t batt;               /*!< ESP_AVRC_RN_BATTERY_STATUS_CHANGE的响应数据*/
} esp_avrc_rn_param_t;

///AVRCP设置应用程序值参数
typedef struct {
    uint8_t   attr_id;                       /*!< 播放器应用程序属性id*/
    uint8_t   attr_val;                      /*!< 播放器应用程序属性值*/
} esp_avrc_set_app_value_param_t;

///AVRC控制器回调参数
typedef union {
    /**
     * @brief ESP_AVRC_CT_CONNECTION_STATE_EVT
     */
    struct avrc_ct_conn_stat_param {
        bool connected;                          /*!< 是否设置AVRC连接*/
        esp_bd_addr_t remote_bda;                /*!< 远程蓝牙设备地址*/
    } conn_stat;                                 /*!< AVRC连接状态*/

    /**
     * @brief ESP_AVRC_CT_PASSTHROUGH_RSP_EVT
     */
    struct avrc_ct_psth_rsp_param {
        uint8_t tl;                              /*!< 事务标签，0到15*/
        uint8_t key_code;                        /*!< 传递命令代码*/
        uint8_t key_state;                       /*!< 0表示已按下，1表示已释放*/
    } psth_rsp;                                  /*!< 传递命令响应*/

    /**
     * @brief ESP_AVRC_CT_METADATA_RSP_EVT
     */
    struct avrc_ct_meta_rsp_param {
        uint8_t attr_id;                         /*!< 元数据属性的id*/
        uint8_t *attr_text;                      /*!< 属性本身*/
        int attr_length;                         /*!< 属性字符长度*/
    } meta_rsp;                                  /*!< 元数据属性响应*/

    /**
     * @brief ESP_AVRC_CT_CHANGE_NOTIFY_EVT
     */
    struct avrc_ct_change_notify_param {
        uint8_t event_id;                        /*!< AVRC事件通知的id*/
        esp_avrc_rn_param_t event_parameter;     /*!< 事件通知参数*/
    } change_ntf;                                /*!< 通知*/

    /**
     * @brief ESP_AVRC_CT_REMOTE_FEATURES_EVT
     */
    struct avrc_ct_rmt_feats_param {
        uint32_t feat_mask;                      /*!< 远程设备的AVRC功能掩码*/
        uint16_t tg_feat_flag;                   /*!< 远程设备的功能标志为TG*/
        esp_bd_addr_t remote_bda;                /*!< 远程蓝牙设备地址*/
    } rmt_feats;                                 /*!< 从远程SDP服务器发现的AVRC功能*/

    /**
     * @brief ESP_AVRC_CT_GET_RN_CAPABILITIES_RSP_EVT
     */
    struct avrc_ct_get_rn_caps_rsp_param {
        uint8_t cap_count;                       /*!< 根据使用的cap_id，事件或company_id中提供的项目数*/
        esp_avrc_rn_evt_cap_mask_t evt_set;      /*!< 位掩码中表示的受支持事件id*/
    } get_rn_caps_rsp;                           /*!< 从AVRCP目标获得支持的事件能力响应*/

    /**
     * @brief ESP_AVRC_CT_SET_ABSOLUTE_VOLUME_RSP_EVT
     */
    struct avrc_ct_set_volume_rsp_param {
        uint8_t volume;                          /*!< 实际设置的音量，范围为0到0x7f，表示0%到100%*/
    } set_volume_rsp;                            /*!< 设置绝对音量响应事件*/
} esp_avrc_ct_cb_param_t;

///AVRC目标回调参数
typedef union {
    /**
     * @brief ESP_AVRC_TG_CONNECTION_STATE_EVT
     */
    struct avrc_tg_conn_stat_param {
        bool connected;                          /*!< 是否设置AVRC连接*/
        esp_bd_addr_t remote_bda;                /*!< 远程蓝牙设备地址*/
    } conn_stat;                                 /*!< AVRC连接状态*/

    /**
     * @brief ESP_AVRC_TG_REMOTE_FEATURES_EVT
     */
    struct avrc_tg_rmt_feats_param {
        uint32_t feat_mask;                      /*!< 远程设备的AVRC功能掩码*/
        uint16_t ct_feat_flag;                   /*!< 远程设备的特征标志为CT*/
        esp_bd_addr_t remote_bda;                /*!< 远程蓝牙设备地址*/
    } rmt_feats;                                 /*!< 通过SDP发现的AVRC功能*/

    /**
     * @brief ESP_AVRC_TG_PASSTHROUGH_CMD_EVT
     */
    struct avrc_tg_psth_cmd_param {
        uint8_t key_code;                        /*!< 传递命令代码*/
        uint8_t key_state;                       /*!< 0表示已按下，1表示已释放*/
    } psth_cmd;                                  /*!< passthrough命令*/

    /**
     * @brief ESP_AVRC_TG_SET_ABSOLUTE_VOLUME_CMD_EVT
     */
    struct avrc_tg_set_abs_vol_param {
        uint8_t volume;                          /*!< 音量范围从0到127*/
    } set_abs_vol;                               /*!< 设置音频接收器上的绝对音量命令*/

    /**
     * @brief ESP_AVRC_TG_REGISTER_NOTIFICATION_EVT
     */
    struct avrc_tg_reg_ntf_param {
        uint8_t event_id;                        /*!< AVRC RegisterNotification的事件id*/
        uint32_t event_parameter;                /*!< 事件通知参数*/
    } reg_ntf;                                   /*!< 注册通知*/

    /**
     * @brief ESP_AVRC_TG_SET_PLAYER_APP_VALUE_EVT
     */
    struct avrc_tg_set_app_value_param {
        uint8_t num_val;                        /*!< 属性num*/
        esp_avrc_set_app_value_param_t *p_vals; /*!< 指向播放器应用程序属性的id和值*/
    } set_app_value;                            /*!< 设置播放器应用程序值*/

} esp_avrc_tg_cb_param_t;

/**
 * @brief           AVRCP控制器回调函数类型
 *
 * @param           event ：事件类型
 *
 * @param           param ：指向回调参数联合的指针
 */
typedef void (* esp_avrc_ct_cb_t)(esp_avrc_ct_cb_event_t event, esp_avrc_ct_cb_param_t *param);

/**
 * @brief           AVRCP目标回调函数类型
 *
 * @param           event ：事件类型
 *
 * @param           param ：指向回调参数联合的指针
 */
typedef void (* esp_avrc_tg_cb_t)(esp_avrc_tg_cb_event_t event, esp_avrc_tg_cb_param_t *param);


/**
 * @brief           向AVRCP模块注册应用程序回调。应在esp_bluedroid_enable（）成功完成后调用此函数。
 *
 * @param[in]       callback: AVRCP控制器回调功能
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_avrc_ct_register_callback(esp_avrc_ct_cb_t callback);

/**
 *
 * @brief           初始化蓝牙AVRCP控制器模块。应在esp_bluedroid_enable（）成功完成后调用此函数。注意：AVRC不能独立工作，AVRC应与A2DP一起使用，并且AVRC应在A2DP之前初始化。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_avrc_ct_init(void);

/**
 *
 * @brief           取消初始化AVRCP控制器模块。应在esp_bluedroid_enable（）成功完成后调用此函数。注意：AVRC不能独立工作，AVRC应与A2DP一起使用，并且AVRC应在A2DP之前解除初始化。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_avrc_ct_deinit(void);

/**
 *
 * @brief           向AVRCP目标发送播放器应用程序设置命令。应在收到ESP_AVRC_CT_CONNECTION_STATE_EVT并建立AVRCP连接后调用此函数。
 *
 * @param[in]       tl ：事务标签，0到15，连续命令应使用不同的值
 *
 * @param[in]       attr_id ：玩家应用程序设置esp_avrc_ps_attr_IDs_t之一的属性ID
 *
 * @param[in]       value_id ：为特定玩家应用程序设置属性定义的属性值
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_avrc_ct_send_set_player_value_cmd(uint8_t tl, uint8_t attr_id, uint8_t value_id);

/**
 * @brief           向AVRCP目标发送GetCapabilities PDU以检索远程设备支持的通知事件ID。应在收到ESP_AVRC_CT_CONNECTION_STATE_EVT并建立AVRCP连接后调用此函数。
 *
 * @param[in]       tl ：事务标签，0到15，连续命令应使用不同的值
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_avrc_ct_send_get_rn_capabilities_cmd(uint8_t tl);

/**
 * @brief           向AVRCP目标发送注册通知命令。应在收到ESP_AVRC_CT_CONNECTION_STATE_EVT并建立AVRCP连接后调用此函数。
 *
 * @param[in]       tl ：事务标签，0到15，连续命令应使用不同的值。
 *
 * @param[in]       event_id ：事件id，例如ESP_AVRC_RN_PLAY_STATUS_CHANGE、ESP_AVRC_RN_TRACK_CHANGE等。
 *
 * @param[in]       event_parameter ：ESP_AVRC_RN_PLAY_POS_CHANGED的播放间隔；对于其他事件，将忽略此参数的值。
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_ERR_NOT_SUPPORTED：如果当前实现中不支持event_id
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_avrc_ct_send_register_notification_cmd(uint8_t tl, uint8_t event_id, uint32_t event_parameter);

/**
 * @brief           向AVRCP目标发送设置绝对音量命令。应在收到ESP_AVRC_CT_CONNECTION_STATE_EVT并建立AVRCP连接后调用此函数。
 *
 * @param[in]       tl ：事务标签，0到15，连续命令应使用不同的值
 *
 * @param[in]       volume ：卷，0到0x7f，表示0%到100%
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_ERR_NOT_SUPPORTED：如果当前实现中不支持event_id
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_avrc_ct_send_set_absolute_volume_cmd(uint8_t tl, uint8_t volume);

/**
 * @brief           向AVRCP目标发送元数据命令。应在收到ESP_AVRC_CT_CONNECTION_STATE_EVT并建立AVRCP连接后调用此函数。
 *
 * @param[in]       tl ：事务标签，0到15，连续命令应使用不同的值。
 *
 * @param[in]       attr_mask ：属性掩码，例如ESP_AVRC_MD_ATTR_ID_TITLE | ESP_AVRC_MD_ATTR_ID_ARTIST。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_avrc_ct_send_metadata_cmd(uint8_t tl, uint8_t attr_mask);


/**
 * @brief           向AVRCP目标发送直通命令。应在收到ESP_AVRC_CT_CONNECTION_STATE_EVT并建立AVRCP连接后调用此函数。
 *
 * @param[in]       tl ：事务标签，0到15，连续命令应使用不同的值。
 *
 * @param[in]       key_code ：直通命令代码，例如ESP_AVRC_PT_CMD_PLAY、ESP_AVRC_PT_CMD_STOP等。
 *
 * @param[in]       key_state ：passthrough命令键状态，ESP_AVRC_PT_CMD_state_PRESSED或ESP_AVRC_PT_CMD_state_RELEASED
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_avrc_ct_send_passthrough_cmd(uint8_t tl, uint8_t key_code, uint8_t key_state);


/**
 * @brief           向AVRCP目标模块注册应用程序回调。应在esp_bluedroid_enable（）成功完成后调用此函数。
 *
 * @param[in]       callback: AVRCP目标回调函数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_avrc_tg_register_callback(esp_avrc_tg_cb_t callback);

/**
 *
 * @brief           初始化蓝牙AVRCP目标模块。应在esp_bluedroid_enable（）成功完成后调用此函数。注意：AVRC不能独立工作，AVRC应与A2DP一起使用，并且AVRC应在A2DP之前初始化。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 *
 */
esp_err_t esp_avrc_tg_init(void);

/**
 *
 * @brief           取消初始化AVRCP目标模块。应在esp_bluedroid_enable（）成功完成后调用此函数。注意：AVRC不能独立工作，AVRC应与A2DP一起使用，并且AVRC应在A2DP之前解除初始化。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈尚未启用
 *                  -ESP_FAIL：其他
 */
esp_err_t esp_avrc_tg_deinit(void);

/**
 *
 * @brief           获取AVRC目标上远程传递命令的当前筛选器。筛选器由传递命令的筛选器类型和位掩码提供。应在esp_avrc_tg_init（）之后调用此函数。对于过滤器类型ESP_AVRC_PSTH_filter_ALLOWED_CMD，检索到的命令集是常量，它涵盖了可能支持的所有传递命令。对于过滤器类型ESP_AVRC_PSTH_filter_SUPPORT_COMMANDS，检索到的命令集包含根据当前配置选择支持的直通命令。可以使用esp_avrc_tg_set_psth_cmd_filter（）更改配置。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈未启用或AVRC TG未初始化
 *                  -ESP_ERR_INVALID_ARG：如果筛选器类型无效或cmd_set为NULL
 *                  -ESP_FAIL：否则
 */
esp_err_t esp_avrc_tg_get_psth_cmd_filter(esp_avrc_psth_filter_t filter, esp_avrc_psth_bit_mask_t *cmd_set);

/**
 *
 * @brief           在AVRC目标上设置远程传递命令的筛选器。筛选器由传递命令的筛选器类型和位掩码提供。应在esp_avrc_tg_init（）之后调用此函数。
 *
 *                  如果过滤器类型为ESP_AVRC_PSTH_filter_SUPPORT_CMD，则CMD_set中设置为“1”的直通命令将生成ESP_AVRC_CT_passthrough_RSP_EVT回调事件，并在协议堆栈中自动接受，其他命令将以响应类型“NOT IMPLEMENTED”（未实现）进行回复（8）。支持的命令集应该是允许的命令集的子集。可以使用过滤器类型为“esp_avrc_psth_filter_allowed_cmd”的esp_avrc_tg_get_psth_cmd_filter（）检索允许的命令集。
 *
 *                  过滤器类型“ESP_AVRC_PSTH_Filter_ALLOWED_CMD”不适用于此功能。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果未启用蓝牙堆栈
 *                  -ESP_ERR_INVALID_ARG：如果筛选器类型无效或cmd_set为NULL
 *                  -ESP_ERR_NOT_SUPPORTED：：如果筛选器类型为ESP_AVRC_PSTH_filter_ALLOWED_CMD，或CMD_set包含不允许的命令
 *
 */
esp_err_t esp_avrc_tg_set_psth_cmd_filter(esp_avrc_psth_filter_t filter, const esp_avrc_psth_bit_mask_t *cmd_set);

/**
 * @brief           针对特定PASSTHROUGH命令，对类型esp_avrc_psth_bit_mask_t进行操作。
 *
 * @param[in]       op: 位掩码字段上请求的操作
 *
 * @param[in]       psth: 指向直通命令位掩码结构的指针
 *
 * @param[in]       cmd: 传递命令代码
 *
 * @return          对于操作ESP_AVRC_BIT_MASK_OP_SET或ESP_AVRC_BIT_MASK-OP_CLEAR，如果操作成功，则返回true，否则返回false。对于操作ESP_AVRC_BIT_MASK_OP_TEST，如果设置了相应的位，则返回true，否则返回false。
 *
 */
bool esp_avrc_psth_bit_mask_operation(esp_avrc_bit_mask_op_t op, esp_avrc_psth_bit_mask_t *psth, esp_avrc_pt_cmd_t cmd);

/**
 *
 * @brief           获取本地AVRC目标上请求的事件通知功能。该能力以evt_set中的位掩码表示形式返回。应在esp_avrc_tg_init（）之后调用此函数。
 *
 *                  对于能力类型“ESP_AVRC_RN_CAP_ALLOWED_EVT”，检索到的事件集是常量，它涵盖了当前实现可能支持的所有通知事件。
 *
 *                  对于功能类型ESP_AVRC_RN_CAP_SUPPORTED_EVT，事件集包含当前配置下选择支持的通知事件。可以使用ESP_AVRC_tg_set_RN_EVT_CAP（）更改配置。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈未启用或AVRC TG未初始化
 *                  -ESP_ERR_INVALID_ARG：如果cap无效或evt_set为NULL
 *                  -ESP_FAIL：否则
 */
esp_err_t esp_avrc_tg_get_rn_evt_cap(esp_avrc_rn_evt_cap_t cap, esp_avrc_rn_evt_cap_mask_t *evt_set);

/**
 *
 * @brief           在本地AVRCP目标上设置事件通知功能。该功能在evt_set中的位掩码表示中给出，并且必须是当前实现中允许的事件ID的子集。应在esp_avrc_tg_init（）之后调用此函数。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果未启用蓝牙堆栈
 *                  -ESP_ERR_INVALID_ARG：如果evt_set为空
 *
 */
esp_err_t esp_avrc_tg_set_rn_evt_cap(const esp_avrc_rn_evt_cap_mask_t *evt_set);

/**
 * @brief           针对特定事件对类型esp_avrc_rn_evt_cap_mask_t进行操作。
 *
 * @param[in]       op: 位掩码字段上请求的操作
 *
 * @param[in]       events: 指向事件通知能力位掩码结构的指针
 *
 * @param[in]       event_id: 通知事件代码
 *
 * @return          对于操作ESP_AVRC_BIT_MASK_OP_SET或ESP_AVRC_BIT_MASK-OP_CLEAR，如果操作成功，则返回true，否则返回false。
 *
 *                  对于操作ESP_AVRC_BIT_MASK_OP_TEST，如果设置了相应的位，则返回true，否则返回false。
 *
 */
bool esp_avrc_rn_evt_bit_mask_operation(esp_avrc_bit_mask_op_t op, esp_avrc_rn_evt_cap_mask_t *events,
                                        esp_avrc_rn_event_ids_t event_id);

/**
 *
 * @brief           向远程AVRCP控制器发送RegisterNotification响应。可以使用esp_avrc_tg_set_rn_evt_cap（）在evt_set中的位掩码表示中设置本地事件通知功能。应在esp_avrc_tg_init（）之后调用此函数。
 *
 * @param[in]       event_id: 远程AVRCP CT注册的通知事件ID
 *
 * @param[in]       rsp: 通知响应代码
 *
 * @param[in]       param: 特定通知中包含的参数
 *
 * @return
 *                  -ESP_OK：成功
 *                  -ESP_ERR_INVALID_STATE：如果蓝牙堆栈未启用或AVRC TG未初始化
 *                  -ESP_ERR_INVALID_ARG：如果evt_set为空
 *
 */
esp_err_t esp_avrc_tg_send_rn_rsp(esp_avrc_rn_event_ids_t event_id, esp_avrc_rn_rsp_t rsp,
                                  esp_avrc_rn_param_t *param);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_AVRC_API_H__ */

