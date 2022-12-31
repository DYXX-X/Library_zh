/******************************************************************************
 * 版权所有（C）2006-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * AVRCP定义和数据类型
 *
 ******************************************************************************/
#ifndef _AVRC_DEFS_H
#define _AVRC_DEFS_H
#include "common/bt_target.h"

#if (AVRC_INCLUDED == TRUE)
/*****************************************************************************
**  常量
*****************************************************************************/

/* 纵断面修订号*/
#define AVRC_REV_1_0        0x0100
#define AVRC_REV_1_3        0x0103
#define AVRC_REV_1_4        0x0104

#define AVRC_PACKET_LEN             512 /* 根据规范，您必须支持512字节的RC数据包*/

#define AVRC_MIN_CONTROL_MTU        48  /* 根据规范，控制信道的最小MTU*/
#define AVRC_MIN_BROWSE_MTU         335 /* 根据规范，浏览频道的最小MTU*/

#define AVRC_META_PDU_OFFSET        4
#define AVRC_SUB_TYPE_LEN           4
#define AVRC_UID_SIZE               8
#define AVRC_FEATURE_MASK_SIZE      16

/* 命令类型代码*/
#define AVRC_CMD_CTRL       0   /* 指导目标执行操作*/
#define AVRC_CMD_STATUS     1   /* 检查设备的当前状态*/
#define AVRC_CMD_SPEC_INQ   2   /* 检查目标是否支持特定控制命令；包括所有操作数*/
#define AVRC_CMD_NOTIF      3   /* 用于接收设备状态更改的通知*/
#define AVRC_CMD_GEN_INQ    4   /* 检查目标是否支持特定控制命令；不包括操作数*/

/* 响应类型代码*/
#define AVRC_RSP_NOT_IMPL   8   /* 目标未实现操作码和操作数指定的命令，或未实现指定的子单元*/
#define AVRC_RSP_ACCEPT     9   /* 目标已执行或正在执行命令*/
#define AVRC_RSP_REJ        10  /* 目标实现了操作码指定的命令，但无法响应，因为目标的当前状态不允许它*/
#define AVRC_RSP_IN_TRANS   11  /* 目标执行状态命令，但处于转换状态；状态命令可以在将来重试*/
#define AVRC_RSP_IMPL_STBL  12  /* 对于特定查询或一般查询命令，目标执行命令；对于状态命令，目标返回稳定状态并包含状态结果*/
#define AVRC_RSP_CHANGED    13  /* 响应帧包含目标设备状态已更改的通知*/
#define AVRC_RSP_INTERIM    15  /* 对于控制命令，目标已接受请求，但无法在100毫秒内返回信息；对于通知命令，目标接受了命令，并将在将来通知控制器目标状态的变化*/

/* 亚单位类型*/
#define AVRC_SUB_MONITOR    0x00    /* 班长*/
#define AVRC_SUB_AUDIO      0x01    /* 音频*/
#define AVRC_SUB_PRINTER    0x02    /* 打印机*/
#define AVRC_SUB_DISC       0x03    /* 圆盘*/
#define AVRC_SUB_TAPE       0x04    /* 录音机/播放器*/
#define AVRC_SUB_TUNER      0x05    /* 调谐器*/
#define AVRC_SUB_CA         0x06    /* CA */
#define AVRC_SUB_CAMERA     0x07    /* 照相机*/
#define AVRC_SUB_PANEL      0x09    /* 面板*/
#define AVRC_SUB_BB         0x0A    /* 公告板*/
#define AVRC_SUB_CAM_STOR   0x0B    /* 摄像机存储*/
#define AVRC_SUB_VENDOR     0x1C    /* 供应商唯一*/
#define AVRC_SUB_EXT        0x1E    /* 扩展到下一字节的子单元类型*/
#define AVRC_SUB_UNIT       0x1F    /* 单元*/

/* 操作码-由1394ta定义*/
#define AVRC_OP_UNIT_INFO   0x30    /* 报告单位信息*/
#define AVRC_OP_SUB_INFO    0x31    /* 报告子单元信息*/
#define AVRC_OP_VENDOR      0x00    /* 供应商相关命令*/
#define AVRC_OP_PASS_THRU   0x7C    /* 面板子单元操作码*/
/* 1394ta不使用操作码80-9F和E0-FF。偷偷摸摸地浏览频道*/
#define AVRC_OP_BROWSE      0xFF    /* 浏览*/
#define AVRC_OP_INVALID     0xFE    /* 无效的*/

/* 公司ID
*/
#define AVRC_CO_BLUETOOTH_SIG   0x00FFFFFF
#define AVRC_CO_WIDCOMM         0x00000361
#define AVRC_CO_BROADCOM        0x00001018
#define AVRC_CO_METADATA        0x00001958  /* 元数据消息的唯一公司ID*/

/* Passthrough命令的状态标志
*/
#define AVRC_STATE_PRESS    0
#define AVRC_STATE_RELEASE  1

/* Passthrough命令的操作ID列表
*/
#define AVRC_ID_SELECT      0x00    /* 选择*/
#define AVRC_ID_UP          0x01    /* 向上的*/
#define AVRC_ID_DOWN        0x02    /* 向下*/
#define AVRC_ID_LEFT        0x03    /* 左边*/
#define AVRC_ID_RIGHT       0x04    /* 正确的*/
#define AVRC_ID_RIGHT_UP    0x05    /* 向上*/
#define AVRC_ID_RIGHT_DOWN  0x06    /* 向右向下*/
#define AVRC_ID_LEFT_UP     0x07    /* 左上*/
#define AVRC_ID_LEFT_DOWN   0x08    /* 左下*/
#define AVRC_ID_ROOT_MENU   0x09    /* 根菜单*/
#define AVRC_ID_SETUP_MENU  0x0A    /* 设置菜单*/
#define AVRC_ID_CONT_MENU   0x0B    /* 目录菜单*/
#define AVRC_ID_FAV_MENU    0x0C    /* 收藏夹菜单*/
#define AVRC_ID_EXIT        0x0D    /* 出口*/
#define AVRC_ID_0           0x20    /* 0 */
#define AVRC_ID_1           0x21    /* 1 */
#define AVRC_ID_2           0x22    /* 2 */
#define AVRC_ID_3           0x23    /* 3 */
#define AVRC_ID_4           0x24    /* 4 */
#define AVRC_ID_5           0x25    /* 5 */
#define AVRC_ID_6           0x26    /* 6 */
#define AVRC_ID_7           0x27    /* 7 */
#define AVRC_ID_8           0x28    /* 8 */
#define AVRC_ID_9           0x29    /* 9 */
#define AVRC_ID_DOT         0x2A    /* 点*/
#define AVRC_ID_ENTER       0x2B    /* 进来*/
#define AVRC_ID_CLEAR       0x2C    /* 清楚的*/
#define AVRC_ID_CHAN_UP     0x30    /* 通道向上*/
#define AVRC_ID_CHAN_DOWN   0x31    /* 通道关闭*/
#define AVRC_ID_PREV_CHAN   0x32    /* 前一频道*/
#define AVRC_ID_SOUND_SEL   0x33    /* 声音选择*/
#define AVRC_ID_INPUT_SEL   0x34    /* 输入选择*/
#define AVRC_ID_DISP_INFO   0x35    /* 显示信息*/
#define AVRC_ID_HELP        0x36    /* 帮助*/
#define AVRC_ID_PAGE_UP     0x37    /* 向上翻页*/
#define AVRC_ID_PAGE_DOWN   0x38    /* 向下翻页*/
#define AVRC_ID_POWER       0x40    /* 权力*/
#define AVRC_ID_VOL_UP      0x41    /* 音量增大*/
#define AVRC_ID_VOL_DOWN    0x42    /* 音量降低*/
#define AVRC_ID_MUTE        0x43    /* 沉默的*/
#define AVRC_ID_PLAY        0x44    /* 玩*/
#define AVRC_ID_STOP        0x45    /* 停止*/
#define AVRC_ID_PAUSE       0x46    /* 暂停*/
#define AVRC_ID_RECORD      0x47    /* 记录*/
#define AVRC_ID_REWIND      0x48    /* 重绕*/
#define AVRC_ID_FAST_FOR    0x49    /* 快进*/
#define AVRC_ID_EJECT       0x4A    /* 弹出*/
#define AVRC_ID_FORWARD     0x4B    /* 向前地*/
#define AVRC_ID_BACKWARD    0x4C    /* 向后的*/
#define AVRC_ID_ANGLE       0x50    /* 角*/
#define AVRC_ID_SUBPICT     0x51    /* 子画面*/
#define AVRC_ID_F1          0x71    /* F1 */
#define AVRC_ID_F2          0x72    /* F2 */
#define AVRC_ID_F3          0x73    /* F3 */
#define AVRC_ID_F4          0x74    /* F4 */
#define AVRC_ID_F5          0x75    /* F5 */
#define AVRC_ID_VENDOR      0x7E    /* 供应商独有*/
#define AVRC_KEYPRESSED_RELEASE 0x80

/*****************************************************************************
**  元数据传输定义
*****************************************************************************/

/* 定义元数据数据包类型
*/
#define AVRC_PKT_SINGLE           0
#define AVRC_PKT_START            1
#define AVRC_PKT_CONTINUE         2
#define AVRC_PKT_END              3
#define AVRC_PKT_TYPE_MASK        3

/* 定义供应商相关数据中携带的PDU
*/
#define AVRC_PDU_GET_CAPABILITIES               0x10
#define AVRC_PDU_LIST_PLAYER_APP_ATTR           0x11
#define AVRC_PDU_LIST_PLAYER_APP_VALUES         0x12
#define AVRC_PDU_GET_CUR_PLAYER_APP_VALUE       0x13
#define AVRC_PDU_SET_PLAYER_APP_VALUE           0x14
#define AVRC_PDU_GET_PLAYER_APP_ATTR_TEXT       0x15
#define AVRC_PDU_GET_PLAYER_APP_VALUE_TEXT      0x16
#define AVRC_PDU_INFORM_DISPLAY_CHARSET         0x17
#define AVRC_PDU_INFORM_BATTERY_STAT_OF_CT      0x18
#define AVRC_PDU_GET_ELEMENT_ATTR               0x20
#define AVRC_PDU_GET_PLAY_STATUS                0x30
#define AVRC_PDU_REGISTER_NOTIFICATION          0x31
#define AVRC_PDU_REQUEST_CONTINUATION_RSP       0x40
#define AVRC_PDU_ABORT_CONTINUATION_RSP         0x41
/* 添加到1.4*/
#define AVRC_PDU_SET_ABSOLUTE_VOLUME            0x50
#define AVRC_PDU_SET_ADDRESSED_PLAYER           0x60
#define AVRC_PDU_SET_BROWSED_PLAYER             0x70
#define AVRC_PDU_GET_FOLDER_ITEMS               0x71
#define AVRC_PDU_CHANGE_PATH                    0x72
#define AVRC_PDU_GET_ITEM_ATTRIBUTES            0x73
#define AVRC_PDU_PLAY_ITEM                      0x74
#define AVRC_PDU_SEARCH                         0x80
#define AVRC_PDU_ADD_TO_NOW_PLAYING             0x90
#define AVRC_PDU_GENERAL_REJECT                 0xA0

/* 定义传递数据中携带的供应商唯一id
*/
#define AVRC_PDU_NEXT_GROUP                     0x00
#define AVRC_PDU_PREV_GROUP                     0x01
/* AVRC定义的唯一通过供应商唯一命令是组导航命令。供应商唯一数据的长度为5*/
#define AVRC_PASS_THRU_GROUP_LEN                5

#define AVRC_PDU_INVALID                        0xff
/* 6.15.3一般拒收的错误状态代码*/
#define AVRC_STS_BAD_CMD        0x00    /* 无效命令，如果TG接收到它不理解的PDU，则发送该命令。*/
#define AVRC_STS_BAD_PARAM      0x01    /* 无效参数，如果TG接收到参数ID不正确的PDU，则发送该参数。如果PDU中只有一个参数ID，则发送。*/
#define AVRC_STS_NOT_FOUND      0x02    /* 找不到指定的参数。，如果参数ID被理解，但内容错误或损坏，则发送。*/
#define AVRC_STS_INTERNAL_ERR   0x03    /* 内部错误，如果存在更具体的错误代码未涵盖的错误条件，则发送。*/
#define AVRC_STS_NO_ERROR       0x04    /* 操作已完成，无错误。这是操作成功时应返回的状态。*/
#define AVRC_STS_UID_CHANGED    0x05    /* UID已更改-设备上的UID已更改*/
/* #define AVRC_STS_GEN_ERROR 0x06未知错误-此更改为“保留”*/
#define AVRC_STS_BAD_DIR        0x07    /* 方向无效-方向参数无效-更改路径*/
#define AVRC_STS_NOT_DIR        0x08    /* 不是目录-提供的UID未引用文件夹项更改路径*/
#define AVRC_STS_NOT_EXIST      0x09    /* 不存在-提供的UID未引用任何项Change Path、PlayItem、AddToNowPlaying、GetItemAttributes*/
#define AVRC_STS_BAD_SCOPE      0x0a    /* 无效作用域-作用域参数无效GetFolderItems、PlayItem、AddToNowPlayer、GetItemAttributes、，*/
#define AVRC_STS_BAD_RANGE      0x0b    /* 范围超出范围-提供的范围起始值不是有效的GetFolderItems*/
#define AVRC_STS_UID_IS_DIR     0x0c    /* UID是一个目录-提供的UID引用了一个目录，此媒体播放器PlayItem、AddToNowPlaying无法处理该目录*/
#define AVRC_STS_IN_USE         0x0d    /* 媒体正在使用-此时媒体无法用于此操作PlayItem、AddToNowPlaying*/
#define AVRC_STS_NOW_LIST_FULL  0x0e    /* 正在播放列表已满-无法将更多项目添加到正在播放列表AddToNowPlaying*/
#define AVRC_STS_SEARCH_NOT_SUP 0x0f    /* 不支持搜索-Browsed Media Player不支持搜索搜索*/
#define AVRC_STS_SEARCH_BUSY    0x10    /* 搜索正在进行-搜索操作已在进行搜索*/
#define AVRC_STS_BAD_PLAYER_ID  0x11    /* 无效的播放机Id-指定的播放机Id未引用有效的播放机SetAddressedPlayer、SetBrowsedPlayer*/
#define AVRC_STS_PLAYER_N_BR    0x12    /* 播放机不可浏览-提供的播放机Id是指不支持浏览的媒体播放机。设置浏览播放器*/
#define AVRC_STS_PLAYER_N_ADDR  0x13    /* 玩家未寻址。提供的玩家Id指的是当前未寻址的玩家，如果玩家未设置为寻址，则无法执行命令。搜索，SetBrowsedPlayer*/
#define AVRC_STS_BAD_SEARCH_RES 0x14    /* 没有有效的搜索结果-搜索结果列表不包含有效条目，例如，由于浏览的玩家GetFolderItems的更改而无效后*/
#define AVRC_STS_NO_AVAL_PLAYER 0x15    /* 无可用玩家全部*/
#define AVRC_STS_ADDR_PLAYER_CHG 0x16   /* 已更改地址的播放机-注册通知*/
typedef UINT8 tAVRC_STS;


/* 定义能力ID
*/
#define AVRC_CAP_COMPANY_ID                     0x02
#define AVRC_CAP_EVENTS_SUPPORTED               0x03
#define AVRC_COMPANY_ID_LEN                     3
#define AVRC_CAPABILITY_OFFSET                  2

/* 定义播放机应用程序设置ID
*/
#define AVRC_PLAYER_SETTING_EQUALIZER           0x01
#define AVRC_PLAYER_SETTING_REPEAT              0x02
#define AVRC_PLAYER_SETTING_SHUFFLE             0x03
#define AVRC_PLAYER_SETTING_SCAN                0x04
#define AVRC_PLAYER_SETTING_LOW_MENU_EXT        0x80
#define AVRC_PLAYER_SETTING_HIGH_MENU_EXT       0xff

/* 定义播放机应用程序设置的可能值
*/
#define AVRC_PLAYER_VAL_OFF                     0x01
#define AVRC_PLAYER_VAL_ON                      0x02
#define AVRC_PLAYER_VAL_SINGLE_REPEAT           0x02
#define AVRC_PLAYER_VAL_ALL_REPEAT              0x03
#define AVRC_PLAYER_VAL_GROUP_REPEAT            0x04
#define AVRC_PLAYER_VAL_ALL_SHUFFLE             0x02
#define AVRC_PLAYER_VAL_GROUP_SHUFFLE           0x03
#define AVRC_PLAYER_VAL_ALL_SCAN                0x02
#define AVRC_PLAYER_VAL_GROUP_SCAN              0x03

/* 定义电池状态PDU的可能值
*/
#define AVRC_BATTERY_STATUS_NORMAL              0x00
#define AVRC_BATTERY_STATUS_WARNING             0x01
#define AVRC_BATTERY_STATUS_CRITICAL            0x02
#define AVRC_BATTERY_STATUS_EXTERNAL            0x03
#define AVRC_BATTERY_STATUS_FULL_CHARGE         0x04
typedef UINT8 tAVRC_BATTERY_STATUS;

/* 定义字符集*/
#define AVRC_CHAR_SET_SIZE                      2

/* 定义媒体属性ID
*/
#define AVRC_MEDIA_ATTR_ID_TITLE                 0x00000001
#define AVRC_MEDIA_ATTR_ID_ARTIST                0x00000002
#define AVRC_MEDIA_ATTR_ID_ALBUM                 0x00000003
#define AVRC_MEDIA_ATTR_ID_TRACK_NUM             0x00000004
#define AVRC_MEDIA_ATTR_ID_NUM_TRACKS            0x00000005
#define AVRC_MEDIA_ATTR_ID_GENRE                 0x00000006
#define AVRC_MEDIA_ATTR_ID_PLAYING_TIME          0x00000007        /* 以毫秒为单位*/
#define AVRC_MAX_NUM_MEDIA_ATTR_ID               7

/* 定义播放状态的可能值
*/
#define AVRC_PLAYSTATE_RESP_MSG_SIZE            9
#define AVRC_PLAYSTATE_STOPPED                  0x00    /* 停止*/
#define AVRC_PLAYSTATE_PLAYING                  0x01    /* 玩*/
#define AVRC_PLAYSTATE_PAUSED                   0x02    /* 已暂停*/
#define AVRC_PLAYSTATE_FWD_SEEK                 0x03    /* 向前搜索*/
#define AVRC_PLAYSTATE_REV_SEEK                 0x04    /* 反向搜索*/
#define AVRC_PLAYSTATE_ERROR                    0xFF    /* 错误*/
typedef UINT8 tAVRC_PLAYSTATE;

/* 定义可以注册通知的事件
*/
#define AVRC_EVT_PLAY_STATUS_CHANGE             0x01
#define AVRC_EVT_TRACK_CHANGE                   0x02
#define AVRC_EVT_TRACK_REACHED_END              0x03
#define AVRC_EVT_TRACK_REACHED_START            0x04
#define AVRC_EVT_PLAY_POS_CHANGED               0x05
#define AVRC_EVT_BATTERY_STATUS_CHANGE          0x06
#define AVRC_EVT_SYSTEM_STATUS_CHANGE           0x07
#define AVRC_EVT_APP_SETTING_CHANGE             0x08
/* 添加在AVRCP 1.4中*/
#define AVRC_EVT_NOW_PLAYING_CHANGE             0x09
#define AVRC_EVT_AVAL_PLAYERS_CHANGE            0x0a
#define AVRC_EVT_ADDR_PLAYER_CHANGE             0x0b
#define AVRC_EVT_UIDS_CHANGE                    0x0c
#define AVRC_EVT_VOLUME_CHANGE                  0x0d

/* 可以注册通知的事件数*/
#define AVRC_NUM_NOTIF_EVENTS                   0x0d

#define AVRC_EVT_MSG_LEN_1                      0x01
#define AVRC_EVT_MSG_LEN_2                      0x02
#define AVRC_EVT_MSG_LEN_5                      0x05
#define AVRC_EVT_MSG_LEN_9                      0x09

#define AVRC_MAX_VOLUME                         0x7F

/* 定义系统状态的可能值
*/
#define AVRC_SYSTEMSTATE_PWR_ON                 0x00
#define AVRC_SYSTEMSTATE_PWR_OFF                0x01
#define AVRC_SYSTEMSTATE_PWR_UNPLUGGED          0x02
typedef UINT8 tAVRC_SYSTEMSTATE;

/* 常用的字符集id*/
#define AVRC_CHARSET_ID_ASCII                  ((UINT16) 0x0003) /* ASCII */
#define AVRC_CHARSET_ID_UTF8                   ((UINT16) 0x006a) /* UTF-8 */
#define AVRC_CHARSET_ID_UTF16                  ((UINT16) 0x03f7) /* 1015 */
#define AVRC_CHARSET_ID_UTF32                  ((UINT16) 0x03f9) /* 1017 */

/*****************************************************************************
**  高级控制
*****************************************************************************/
#define AVRC_ITEM_PLAYER            0x01
#define AVRC_ITEM_FOLDER            0x02
#define AVRC_ITEM_MEDIA             0x03

#define AVRC_SCOPE_PLAYER_LIST      0x00  /* 媒体播放器项目-包含所有可用的媒体播放器*/
#define AVRC_SCOPE_FILE_SYSTEM      0x01  /* 文件夹项、媒体元素项—包含所浏览播放器的媒体内容的虚拟文件系统*/
#define AVRC_SCOPE_SEARCH           0x02  /* 媒体元素项对浏览的播放器进行搜索操作的结果*/
#define AVRC_SCOPE_NOW_PLAYING      0x03  /* 媒体元素项目寻址播放器的“正在播放”列表（或队列）*/

#define AVRC_FOLDER_ITEM_COUNT_NONE 0xFF

/* 文件夹类型*/
#define AVRC_FOLDER_TYPE_MIXED      0x00
#define AVRC_FOLDER_TYPE_TITLES     0x01
#define AVRC_FOLDER_TYPE_ALNUMS     0x02
#define AVRC_FOLDER_TYPE_ARTISTS    0x03
#define AVRC_FOLDER_TYPE_GENRES     0x04
#define AVRC_FOLDER_TYPE_PLAYLISTS  0x05
#define AVRC_FOLDER_TYPE_YEARS      0x06

/* 主要玩家类型*/
#define AVRC_MJ_TYPE_AUDIO          0x01  /* 音频*/
#define AVRC_MJ_TYPE_VIDEO          0x02  /* 视频*/
#define AVRC_MJ_TYPE_BC_AUDIO       0x04  /* 广播音频*/
#define AVRC_MJ_TYPE_BC_VIDEO       0x08  /* 广播视频*/
#define AVRC_MJ_TYPE_INVALID        0xF0

/* 播放器子类型*/
#define AVRC_SUB_TYPE_NONE          0x00
#define AVRC_SUB_TYPE_AUDIO_BOOK    0x01  /* 有声读物*/
#define AVRC_SUB_TYPE_PODCAST       0x02  /* 播客*/
#define AVRC_SUB_TYPE_INVALID       0xFC

/* 媒体项-媒体类型*/
#define AVRC_MEDIA_TYPE_AUDIO       0x00
#define AVRC_MEDIA_TYPE_VIDEO       0x01

#define AVRC_DIR_UP                 0x00  /* 文件夹向上*/
#define AVRC_DIR_DOWN               0x01  /* 文件夹关闭*/

#define AVRC_UID_SIZE               8
typedef UINT8 tAVRC_UID[AVRC_UID_SIZE];

/*****************************************************************************
**  播放器属性-支持的功能
*****************************************************************************/
#define AVRC_PF_SELECT_BIT_NO           0
#define AVRC_PF_SELECT_MASK             0x01
#define AVRC_PF_SELECT_OFF              0
#define AVRC_PF_SELECT_SUPPORTED(x)     ((x)[AVRC_PF_SELECT_OFF] & AVRC_PF_SELECT_MASK)

#define AVRC_PF_UP_BIT_NO               1
#define AVRC_PF_UP_MASK                 0x02
#define AVRC_PF_UP_OFF                  0
#define AVRC_PF_UP_SUPPORTED(x)         ((x)[AVRC_PF_UP_OFF] & AVRC_PF_UP_MASK)

#define AVRC_PF_DOWN_BIT_NO             2
#define AVRC_PF_DOWN_MASK               0x04
#define AVRC_PF_DOWN_OFF                0
#define AVRC_PF_DOWN_SUPPORTED(x)       ((x)[AVRC_PF_DOWN_OFF] & AVRC_PF_DOWN_MASK)

#define AVRC_PF_LEFT_BIT_NO             3
#define AVRC_PF_LEFT_MASK               0x08
#define AVRC_PF_LEFT_OFF                0
#define AVRC_PF_LEFT_SUPPORTED(x)       ((x)[AVRC_PF_LEFT_OFF] & AVRC_PF_LEFT_MASK)

#define AVRC_PF_RIGHT_BIT_NO            4
#define AVRC_PF_RIGHT_MASK              0x10
#define AVRC_PF_RIGHT_OFF               0
#define AVRC_PF_RIGHT_SUPPORTED(x)      ((x)[AVRC_PF_RIGHT_OFF] & AVRC_PF_RIGHT_MASK)

#define AVRC_PF_RIGHTUP_BIT_NO          5
#define AVRC_PF_RIGHTUP_MASK            0x20
#define AVRC_PF_RIGHTUP_OFF             0
#define AVRC_PF_RIGHTUP_SUPPORTED(x)    ((x)[AVRC_PF_RIGHTUP_OFF] & AVRC_PF_RIGHTUP_MASK)

#define AVRC_PF_RIGHTDOWN_BIT_NO        6
#define AVRC_PF_RIGHTDOWN_MASK          0x40
#define AVRC_PF_RIGHTDOWN_OFF           0
#define AVRC_PF_RIGHTDOWN_SUPPORTED(x)  ((x)[AVRC_PF_RIGHTDOWN_OFF] & AVRC_PF_RIGHTDOWN_MASK)

#define AVRC_PF_LEFTUP_BIT_NO           7
#define AVRC_PF_LEFTUP_MASK             0x80
#define AVRC_PF_LEFTUP_OFF              0
#define AVRC_PF_LEFTUP_SUPPORTED(x)     ((x)[AVRC_PF_LEFTUP_OFF] & AVRC_PF_LEFTUP_MASK)

#define AVRC_PF_LEFTDOWN_BIT_NO         8
#define AVRC_PF_LEFTDOWN_MASK           0x01
#define AVRC_PF_LEFTDOWN_OFF            1
#define AVRC_PF_LEFTDOWN_SUPPORTED(x)   ((x)[AVRC_PF_LEFTDOWN_OFF] & AVRC_PF_LEFTDOWN_MASK)

#define AVRC_PF_ROOT_MENU_BIT_NO        9
#define AVRC_PF_ROOT_MENU_MASK          0x02
#define AVRC_PF_ROOT_MENU_OFF           1
#define AVRC_PF_ROOT_MENU_SUPPORTED(x)  ((x)[AVRC_PF_ROOT_MENU_OFF] & AVRC_PF_ROOT_MENU_MASK)

#define AVRC_PF_SETUP_MENU_BIT_NO       10
#define AVRC_PF_SETUP_MENU_MASK         0x04
#define AVRC_PF_SETUP_MENU_OFF          1
#define AVRC_PF_SETUP_MENU_SUPPORTED(x) ((x)[AVRC_PF_SETUP_MENU_OFF] & AVRC_PF_SETUP_MENU_MASK)

#define AVRC_PF_CONTENTS_MENU_BIT_NO    11
#define AVRC_PF_CONTENTS_MENU_MASK      0x08
#define AVRC_PF_CONTENTS_MENU_OFF       1
#define AVRC_PF_CONTENTS_MENU_SUPPORTED(x)  ((x)[AVRC_PF_CONTENTS_MENU_OFF] & AVRC_PF_CONTENTS_MENU_MASK)

#define AVRC_PF_FAVORITE_MENU_BIT_NO    12
#define AVRC_PF_FAVORITE_MENU_MASK      0x10
#define AVRC_PF_FAVORITE_MENU_OFF       1
#define AVRC_PF_FAVORITE_MENU_SUPPORTED(x)  ((x)[AVRC_PF_FAVORITE_MENU_OFF] & AVRC_PF_FAVORITE_MENU_MASK)

#define AVRC_PF_EXIT_BIT_NO             13
#define AVRC_PF_EXIT_MASK               0x20
#define AVRC_PF_EXIT_OFF                1
#define AVRC_PF_EXIT_SUPPORTED(x)       ((x)[AVRC_PF_EXIT_OFF] & AVRC_PF_EXIT_MASK)

#define AVRC_PF_0_BIT_NO                14
#define AVRC_PF_0_MASK                  0x40
#define AVRC_PF_0_OFF                   1
#define AVRC_PF_0_SUPPORTED(x)          ((x)[AVRC_PF_0_OFF] & AVRC_PF_0_MASK)

#define AVRC_PF_1_BIT_NO                15
#define AVRC_PF_1_MASK                  0x80
#define AVRC_PF_1_OFF                   1
#define AVRC_PF_1_SUPPORTED(x)          ((x)[AVRC_PF_1_OFF] & AVRC_PF_1_MASK)

#define AVRC_PF_2_BIT_NO                16
#define AVRC_PF_2_MASK                  0x01
#define AVRC_PF_2_OFF                   2
#define AVRC_PF_2_SUPPORTED(x)          ((x)[AVRC_PF_2_OFF] & AVRC_PF_2_MASK)

#define AVRC_PF_3_BIT_NO                17
#define AVRC_PF_3_MASK                  0x02
#define AVRC_PF_3_OFF                   2
#define AVRC_PF_3_SUPPORTED(x)          ((x)[AVRC_PF_3_OFF] & AVRC_PF_3_MASK)

#define AVRC_PF_4_BIT_NO                18
#define AVRC_PF_4_MASK                  0x04
#define AVRC_PF_4_OFF                   2
#define AVRC_PF_4_SUPPORTED(x)          ((x)[AVRC_PF_4_OFF] & AVRC_PF_4_MASK)

#define AVRC_PF_5_BIT_NO                19
#define AVRC_PF_5_MASK                  0x08
#define AVRC_PF_5_OFF                   2
#define AVRC_PF_5_SUPPORTED(x)          ((x)[AVRC_PF_5_OFF] & AVRC_PF_5_MASK)

#define AVRC_PF_6_BIT_NO                20
#define AVRC_PF_6_MASK                  0x10
#define AVRC_PF_6_OFF                   2
#define AVRC_PF_6_SUPPORTED(x)          ((x)[AVRC_PF_6_OFF] & AVRC_PF_6_MASK)

#define AVRC_PF_7_BIT_NO                21
#define AVRC_PF_7_MASK                  0x20
#define AVRC_PF_7_OFF                   2
#define AVRC_PF_7_SUPPORTED(x)          ((x)[AVRC_PF_7_OFF] & AVRC_PF_7_MASK)

#define AVRC_PF_8_BIT_NO                22
#define AVRC_PF_8_MASK                  0x40
#define AVRC_PF_8_OFF                   2
#define AVRC_PF_8_SUPPORTED(x)          ((x)[AVRC_PF_8_OFF] & AVRC_PF_8_MASK)

#define AVRC_PF_9_BIT_NO                23
#define AVRC_PF_9_MASK                  0x80
#define AVRC_PF_9_OFF                   2
#define AVRC_PF_9_SUPPORTED(x)          ((x)[AVRC_PF_9_OFF] & AVRC_PF_9_MASK)

#define AVRC_PF_DOT_BIT_NO              24
#define AVRC_PF_DOT_MASK                0x01
#define AVRC_PF_DOT_OFF                 3
#define AVRC_PF_DOT_SUPPORTED(x)        ((x)[AVRC_PF_DOT_OFF] & AVRC_PF_DOT_MASK)

#define AVRC_PF_ENTER_BIT_NO            25
#define AVRC_PF_ENTER_MASK              0x02
#define AVRC_PF_ENTER_OFF               3
#define AVRC_PF_ENTER_SUPPORTED(x)      ((x)[AVRC_PF_ENTER_OFF] & AVRC_PF_ENTER_MASK)

#define AVRC_PF_CLEAR_BIT_NO            26
#define AVRC_PF_CLEAR_MASK              0x04
#define AVRC_PF_CLEAR_OFF               3
#define AVRC_PF_CLEAR_SUPPORTED(x)      ((x)[AVRC_PF_CLEAR_OFF] & AVRC_PF_CLEAR_MASK)

#define AVRC_PF_CHNL_UP_BIT_NO          27
#define AVRC_PF_CHNL_UP_MASK            0x08
#define AVRC_PF_CHNL_UP_OFF             3
#define AVRC_PF_CHNL_UP_SUPPORTED(x)    ((x)[AVRC_PF_CHNL_UP_OFF] & AVRC_PF_CHNL_UP_MASK)

#define AVRC_PF_CHNL_DOWN_BIT_NO        28
#define AVRC_PF_CHNL_DOWN_MASK          0x10
#define AVRC_PF_CHNL_DOWN_OFF           3
#define AVRC_PF_CHNL_DOWN_SUPPORTED(x)  ((x)[AVRC_PF_CHNL_DOWN_OFF] & AVRC_PF_CHNL_DOWN_MASK)

#define AVRC_PF_PREV_CHNL_BIT_NO        29
#define AVRC_PF_PREV_CHNL_MASK          0x20
#define AVRC_PF_PREV_CHNL_OFF           3
#define AVRC_PF_PREV_CHNL_SUPPORTED(x)  ((x)[AVRC_PF_PREV_CHNL_OFF] & AVRC_PF_PREV_CHNL_MASK)

#define AVRC_PF_SOUND_SEL_BIT_NO        30
#define AVRC_PF_SOUND_SEL_MASK          0x40
#define AVRC_PF_SOUND_SEL_OFF           3
#define AVRC_PF_SOUND_SEL_SUPPORTED(x)  ((x)[AVRC_PF_SOUND_SEL_OFF] & AVRC_PF_SOUND_SEL_MASK)

#define AVRC_PF_INPUT_SEL_BIT_NO        31
#define AVRC_PF_INPUT_SEL_MASK          0x80
#define AVRC_PF_INPUT_SEL_OFF           3
#define AVRC_PF_INPUT_SEL_SUPPORTED(x)  ((x)[AVRC_PF_INPUT_SEL_OFF] & AVRC_PF_INPUT_SEL_MASK)

#define AVRC_PF_DISP_INFO_BIT_NO        32
#define AVRC_PF_DISP_INFO_MASK          0x01
#define AVRC_PF_DISP_INFO_OFF           4
#define AVRC_PF_DISP_INFO_SUPPORTED(x)  ((x)[AVRC_PF_DISP_INFO_OFF] & AVRC_PF_DISP_INFO_MASK)

#define AVRC_PF_HELP_BIT_NO             33
#define AVRC_PF_HELP_MASK               0x02
#define AVRC_PF_HELP_OFF                4
#define AVRC_PF_HELP_SUPPORTED(x)       ((x)[AVRC_PF_HELP_OFF] & AVRC_PF_HELP_MASK)

#define AVRC_PF_PAGE_UP_BIT_NO          34
#define AVRC_PF_PAGE_UP_MASK            0x04
#define AVRC_PF_PAGE_UP_OFF             4
#define AVRC_PF_PAGE_UP_SUPPORTED(x)    ((x)[AVRC_PF_PAGE_UP_OFF] & AVRC_PF_PAGE_UP_MASK)

#define AVRC_PF_PAGE_DOWN_BIT_NO        35
#define AVRC_PF_PAGE_DOWN_MASK          0x08
#define AVRC_PF_PAGE_DOWN_OFF           4
#define AVRC_PF_PAGE_DOWN_SUPPORTED(x)  ((x)[AVRC_PF_PAGE_DOWN_OFF] & AVRC_PF_PAGE_DOWN_MASK)

#define AVRC_PF_POWER_BIT_NO            36
#define AVRC_PF_POWER_MASK              0x10
#define AVRC_PF_POWER_OFF               4
#define AVRC_PF_POWER_SUPPORTED(x)      ((x)[AVRC_PF_POWER_OFF] & AVRC_PF_POWER_MASK)

#define AVRC_PF_VOL_UP_BIT_NO           37
#define AVRC_PF_VOL_UP_MASK             0x20
#define AVRC_PF_VOL_UP_OFF              4
#define AVRC_PF_VOL_UP_SUPPORTED(x)     ((x)[AVRC_PF_VOL_UP_OFF] & AVRC_PF_VOL_UP_MASK)

#define AVRC_PF_VOL_DOWN_BIT_NO         38
#define AVRC_PF_VOL_DOWN_MASK           0x40
#define AVRC_PF_VOL_DOWN_OFF            4
#define AVRC_PF_VOL_DOWN_SUPPORTED(x)   ((x)[AVRC_PF_VOL_DOWN_OFF] & AVRC_PF_VOL_DOWN_MASK)

#define AVRC_PF_MUTE_BIT_NO             39
#define AVRC_PF_MUTE_MASK               0x80
#define AVRC_PF_MUTE_OFF                4
#define AVRC_PF_MUTE_SUPPORTED(x)       ((x)[AVRC_PF_MUTE_OFF] & AVRC_PF_MUTE_MASK)

#define AVRC_PF_PLAY_BIT_NO             40
#define AVRC_PF_PLAY_MASK               0x01
#define AVRC_PF_PLAY_OFF                5
#define AVRC_PF_PLAY_SUPPORTED(x)       ((x)[AVRC_PF_PLAY_OFF] & AVRC_PF_PLAY_MASK)

#define AVRC_PF_STOP_BIT_NO             41
#define AVRC_PF_STOP_MASK               0x02
#define AVRC_PF_STOP_OFF                5
#define AVRC_PF_STOP_SUPPORTED(x)       ((x)[AVRC_PF_STOP_OFF] & AVRC_PF_STOP_MASK)

#define AVRC_PF_PAUSE_BIT_NO            42
#define AVRC_PF_PAUSE_MASK              0x04
#define AVRC_PF_PAUSE_OFF               5
#define AVRC_PF_PAUSE_SUPPORTED(x)      ((x)[AVRC_PF_PAUSE_OFF] & AVRC_PF_PAUSE_MASK)

#define AVRC_PF_RECORD_BIT_NO           43
#define AVRC_PF_RECORD_MASK             0x08
#define AVRC_PF_RECORD_OFF              5
#define AVRC_PF_RECORD_SUPPORTED(x)     ((x)[AVRC_PF_RECORD_OFF] & AVRC_PF_RECORD_MASK)

#define AVRC_PF_REWIND_BIT_NO           44
#define AVRC_PF_REWIND_MASK             0x10
#define AVRC_PF_REWIND_OFF              5
#define AVRC_PF_REWIND_SUPPORTED(x)     ((x)[AVRC_PF_REWIND_OFF] & AVRC_PF_REWIND_MASK)

#define AVRC_PF_FAST_FWD_BIT_NO         45
#define AVRC_PF_FAST_FWD_MASK           0x20
#define AVRC_PF_FAST_FWD_OFF            5
#define AVRC_PF_FAST_FWD_SUPPORTED(x)   ((x)[AVRC_PF_FAST_FWD_OFF] & AVRC_PF_FAST_FWD_MASK)

#define AVRC_PF_EJECT_BIT_NO            46
#define AVRC_PF_EJECT_MASK              0x40
#define AVRC_PF_EJECT_OFF               5
#define AVRC_PF_EJECT_SUPPORTED(x)      ((x)[AVRC_PF_EJECT_OFF] & AVRC_PF_EJECT_MASK)

#define AVRC_PF_FORWARD_BIT_NO          47
#define AVRC_PF_FORWARD_MASK            0x80
#define AVRC_PF_FORWARD_OFF             5
#define AVRC_PF_FORWARD_SUPPORTED(x)    ((x)[AVRC_PF_FORWARD_OFF] & AVRC_PF_FORWARD_MASK)

#define AVRC_PF_BACKWARD_BIT_NO         48
#define AVRC_PF_BACKWARD_MASK           0x01
#define AVRC_PF_BACKWARD_OFF            6
#define AVRC_PF_BACKWARD_SUPPORTED(x)   ((x)[AVRC_PF_BACKWARD_OFF] & AVRC_PF_BACKWARD_MASK)

#define AVRC_PF_ANGLE_BIT_NO            49
#define AVRC_PF_ANGLE_MASK              0x02
#define AVRC_PF_ANGLE_OFF               6
#define AVRC_PF_ANGLE_SUPPORTED(x)      ((x)[AVRC_PF_ANGLE_OFF] & AVRC_PF_ANGLE_MASK)

#define AVRC_PF_SUBPICTURE_BIT_NO       50
#define AVRC_PF_SUBPICTURE_MASK         0x04
#define AVRC_PF_SUBPICTURE_OFF          6
#define AVRC_PF_SUBPICTURE_SUPPORTED(x) ((x)[AVRC_PF_SUBPICTURE_OFF] & AVRC_PF_SUBPICTURE_MASK)

#define AVRC_PF_F1_BIT_NO               51
#define AVRC_PF_F1_MASK                 0x08
#define AVRC_PF_F1_OFF                  6
#define AVRC_PF_F1_SUPPORTED(x)         ((x)[AVRC_PF_F1_OFF] & AVRC_PF_F1_MASK)

#define AVRC_PF_F2_BIT_NO               52
#define AVRC_PF_F2_MASK                 0x10
#define AVRC_PF_F2_OFF                  6
#define AVRC_PF_F2_SUPPORTED(x)         ((x)[AVRC_PF_F2_OFF] & AVRC_PF_F2_MASK)

#define AVRC_PF_F3_BIT_NO               53
#define AVRC_PF_F3_MASK                 0x20
#define AVRC_PF_F3_OFF                  6
#define AVRC_PF_F3_SUPPORTED(x)         ((x)[AVRC_PF_F3_OFF] & AVRC_PF_F3_MASK)

#define AVRC_PF_F4_BIT_NO               54
#define AVRC_PF_F4_MASK                 0x40
#define AVRC_PF_F4_OFF                  6
#define AVRC_PF_F4_SUPPORTED(x)         ((x)[AVRC_PF_F4_OFF] & AVRC_PF_F4_MASK)

#define AVRC_PF_F5_BIT_NO               55
#define AVRC_PF_F5_MASK                 0x80
#define AVRC_PF_F5_OFF                  6
#define AVRC_PF_F5_SUPPORTED(x)         ((x)[AVRC_PF_F5_OFF] & AVRC_PF_F5_MASK)

/* 供应商唯一。支持此PASSTHROUGH命令。*/
#define AVRC_PF_VENDOR_BIT_NO           56
#define AVRC_PF_VENDOR_MASK             0x01
#define AVRC_PF_VENDOR_OFF              7
#define AVRC_PF_VENDOR_SUPPORTED(x)     ((x)[AVRC_PF_VENDOR_OFF] & AVRC_PF_VENDOR_MASK)

/* 基本组导航。这将覆盖SDP条目，因为它是按玩家设置的。7.*/
#define AVRC_PF_GROUP_NAVI_BIT_NO       57
#define AVRC_PF_GROUP_NAVI_MASK         0x02
#define AVRC_PF_GROUP_NAVI_OFF          7
#define AVRC_PF_GROUP_NAVI_SUPPORTED(x) ((x)[AVRC_PF_GROUP_NAVI_OFF] & AVRC_PF_GROUP_NAVI_MASK)

/* 高级控制播放器。如果播放器至少支持AVRCP 1.4，则设置该位。*/
#define AVRC_PF_ADV_CTRL_BIT_NO         58
#define AVRC_PF_ADV_CTRL_MASK           0x04
#define AVRC_PF_ADV_CTRL_OFF            7
#define AVRC_PF_ADV_CTRL_SUPPORTED(x)   ((x)[AVRC_PF_ADV_CTRL_OFF] & AVRC_PF_ADV_CTRL_MASK)

/* 浏览。如果播放器支持浏览，则设置此位。*/
#define AVRC_PF_BROWSE_BIT_NO           59
#define AVRC_PF_BROWSE_MASK             0x08
#define AVRC_PF_BROWSE_OFF              7
#define AVRC_PF_BROWSE_SUPPORTED(x)     ((x)[AVRC_PF_BROWSE_OFF] & AVRC_PF_BROWSE_MASK)

/* 搜索。如果玩家支持搜索，则设置此位。*/
#define AVRC_PF_SEARCH_BIT_NO           60
#define AVRC_PF_SEARCH_MASK             0x10
#define AVRC_PF_SEARCH_OFF              7
#define AVRC_PF_SEARCH_SUPPORTED(x)     ((x)[AVRC_PF_SEARCH_OFF] & AVRC_PF_SEARCH_MASK)

/* 添加到现在播放。如果播放器支持AddToNowPlaying命令，则设置此位。*/
#define AVRC_PF_ADD2NOWPLAY_BIT_NO      61
#define AVRC_PF_ADD2NOWPLAY_MASK        0x20
#define AVRC_PF_ADD2NOWPLAY_OFF         7
#define AVRC_PF_ADD2NOWPLAY_SUPPORTED(x) ((x)[AVRC_PF_ADD2NOWPLAY_OFF] & AVRC_PF_ADD2NOWPLAY_MASK)

/* 玩家浏览树中唯一的UID。如果玩家能够在玩家浏览树中维护唯一的UID，则设置该位。*/
#define AVRC_PF_UID_UNIQUE_BIT_NO       62
#define AVRC_PF_UID_UNIQUE_MASK         0x40
#define AVRC_PF_UID_UNIQUE_OFF          7
#define AVRC_PF_UID_UNIQUE_SUPPORTED(x) ((x)[AVRC_PF_UID_UNIQUE_OFF] & AVRC_PF_UID_UNIQUE_MASK)

/* 仅在添加时可浏览。如果该播放器仅在被设置为Addressed player时才能被浏览，则设置该位。*/
#define AVRC_PF_BR_WH_ADDR_BIT_NO       63
#define AVRC_PF_BR_WH_ADDR_MASK         0x80
#define AVRC_PF_BR_WH_ADDR_OFF          7
#define AVRC_PF_BR_WH_ADDR_SUPPORTED(x) ((x)[AVRC_PF_BR_WH_ADDR_OFF] & AVRC_PF_BR_WH_ADDR_MASK)

/* 仅可在添加时搜索。如果该玩家仅在被设置为“已寻址玩家”时才能被搜索，则设置该位。*/
#define AVRC_PF_SEARCH_WH_ADDR_BIT_NO   64
#define AVRC_PF_SEARCH_WH_ADDR_MASK     0x01
#define AVRC_PF_SEARCH_WH_ADDR_OFF      8
#define AVRC_PF_SEARCH_WH_ADDR_SUPPORTED(x) ((x)[AVRC_PF_SEARCH_WH_ADDR_OFF] & AVRC_PF_SEARCH_WH_ADDR_MASK)

/* 无播放。如果播放机支持NowPlaying文件夹，则设置此位。注意，对于所有支持浏览的播放器，应设置此位*/
#define AVRC_PF_NOW_PLAY_BIT_NO         65
#define AVRC_PF_NOW_PLAY_MASK           0x02
#define AVRC_PF_NOW_PLAY_OFF            8
#define AVRC_PF_NOW_PLAY_SUPPORTED(x)   ((x)[AVRC_PF_NOW_PLAY_OFF] & AVRC_PF_NOW_PLAY_MASK)

/* UID持久性。如果播放机能够在AVRCP浏览重新连接之间保持UID值，则设置此位*/
#define AVRC_PF_UID_PERSIST_BIT_NO      66
#define AVRC_PF_UID_PERSIST_MASK        0x04
#define AVRC_PF_UID_PERSIST_OFF         8
#define AVRC_PF_UID_PERSIST_SUPPORTED(x) ((x)[AVRC_PF_UID_PERSIST_OFF] & AVRC_PF_UID_PERSIST_MASK)

/*****************************************************************************
**  数据类型定义
*****************************************************************************/

/*
此结构包含AV/C消息的报头参数。
*/
typedef struct {
    UINT8   ctype;          /* 命令类型。*/
    UINT8   subunit_type;   /* 子单元类型。*/
    UINT8   subunit_id;     /* 子单元ID。此值通常在AVRCP中被忽略，除非该值依赖于供应商。值范围为0-7。*/
    UINT8   opcode;         /* 操作代码（传递、供应商等）*/
} tAVRC_HDR;

/* 此结构包含UNIT INFO消息。*/
typedef struct {
    tAVRC_HDR   hdr;        /* 消息头。*/
    UINT32      company_id; /* 公司标识符。*/
    UINT8       unit_type;  /* 单位类型。使用与子单元类型相同的值。*/
    UINT8       unit;       /* 该值取决于供应商，通常为零。*/
} tAVRC_MSG_UNIT;

/* 此结构包含SUBUNIT INFO消息。*/
typedef struct {
    tAVRC_HDR   hdr;        /* 消息头。*/
    UINT8       subunit_type[AVRC_SUB_TYPE_LEN];
    /* 包含子单元类型值的数组。*/
    BOOLEAN     panel;      /* 如果面板子单元类型在subunit_type数组中，则为TRUE，否则为FALSE。*/
    UINT8       page;       /* 指定返回子单元类型表的哪个部分。对于AVRCP，通常为零。*值范围为0-7。*/
} tAVRC_MSG_SUB;

/* 此结构包含供应商依赖消息。*/
typedef struct {
    tAVRC_HDR   hdr;        /* 消息头。*/
    UINT32      company_id; /* 公司标识符。*/
    UINT8      *p_vendor_data;/* 指向供应商相关数据的指针。*/
    UINT16      vendor_len; /* 供应商相关数据的字节长度。*/
} tAVRC_MSG_VENDOR;

/* 通过消息结构*/
typedef struct {
    tAVRC_HDR   hdr;        /* 硬盘驱动器。ctype未使用。硬盘驱动器。subunit_type未使用。*硬盘驱动器。subunit_id未使用。*/
    UINT8       op_id;      /* 操作ID。*/
    UINT8       state;      /* 按键状态。*/
    UINT8      *p_pass_data;/* 指向数据的指针。此参数仅在op_id为AVRC_id_VENDOR时有效。*/
    UINT8       pass_len;   /* 数据长度（字节）。此参数仅在op_id为AVRC_id_VENDOR时有效。*/
} tAVRC_MSG_PASS;

/* 命令/响应指示器。*/
#define AVRC_CMD            AVCT_CMD    /* 命令消息*/
#define AVRC_RSP            AVCT_RSP    /* 响应消息*/

/* 浏览频道消息结构*/
typedef struct {
    tAVRC_HDR   hdr;            /* 硬盘驱动器。ctype AVRC_CMD或AVRC_RSP。硬盘驱动器。subunit_type未使用。*硬盘驱动器。subunit_id未使用。*/
    UINT8      *p_browse_data;  /* 指向数据的指针。*/
    UINT16      browse_len;     /* 数据长度（字节）。*/
    BT_HDR     *p_browse_pkt;   /* 收到GKI缓冲区。如果回调函数希望保留缓冲区，则设置为NULL*/
} tAVRC_MSG_BROWSE;

/* 这是所有消息类型结构的联合。*/
typedef union {
    tAVRC_HDR           hdr;    /* 消息头。*/
    tAVRC_MSG_UNIT      unit;   /* UNIT INFO消息。*/
    tAVRC_MSG_SUB       sub;    /* SUBUNIT INFO消息。*/
    tAVRC_MSG_VENDOR    vendor; /* 供应商依赖信息。*/
    tAVRC_MSG_PASS      pass;   /* 通过消息。*/
    tAVRC_MSG_BROWSE    browse; /* 通过浏览频道发送消息*/
} tAVRC_MSG;

/* 宏*/
#define AVRC_IS_VALID_CAP_ID(a)           (((a == AVRC_CAP_COMPANY_ID) || (a == AVRC_CAP_EVENTS_SUPPORTED)) ? TRUE : FALSE)

#define AVRC_IS_VALID_EVENT_ID(a)           (((a >= AVRC_EVT_PLAY_STATUS_CHANGE) && \
                                              (a <= AVRC_EVT_VOLUME_CHANGE)) ? TRUE : FALSE)

#define AVRC_IS_VALID_ATTRIBUTE(a)          (((((a > 0) && a <= AVRC_PLAYER_SETTING_SCAN)) || \
                          (a >= AVRC_PLAYER_SETTING_LOW_MENU_EXT)) ? TRUE : FALSE)

#define AVRC_IS_VALID_MEDIA_ATTRIBUTE(a)    ((a >= AVRC_MEDIA_ATTR_ID_TITLE) && \
                                             (a <= AVRC_MEDIA_ATTR_ID_PLAYING_TIME) ? TRUE : FALSE)

#define AVRC_IS_VALID_BATTERY_STATUS(a)    ((a <= AVRC_BATTERY_STATUS_FULL_CHARGE) ? TRUE : FALSE)

#define AVRC_IS_VALID_SYSTEM_STATUS(a)    ((a <= AVRC_SYSTEMSTATE_PWR_UNPLUGGED) ? TRUE : FALSE)

#define AVRC_IS_VALID_GROUP(a)    ((a <= AVRC_PDU_PREV_GROUP) ? TRUE : FALSE)

/* 公司ID是24位整数。我们不能在stack/bt_types中使用宏。小时*/
#define AVRC_CO_ID_TO_BE_STREAM(p, u32) {*(p)++ = (UINT8)((u32) >> 16); *(p)++ = (UINT8)((u32) >> 8); *(p)++ = (UINT8)(u32); }
#define AVRC_BE_STREAM_TO_CO_ID(u32, p) {u32 = (((UINT32)(*((p) + 2))) + (((UINT32)(*((p) + 1))) << 8) + (((UINT32)(*(p))) << 16)); (p) += 3;}

/*****************************************************************************
**  数据类型定义
*****************************************************************************/
#define AVRC_MAX_APP_ATTR_SIZE      16
#define AVRC_MAX_CHARSET_SIZE       16
#define AVRC_MAX_ELEM_ATTR_SIZE     8


/*****************************************************************************
**  元数据传输生成/分析定义
*****************************************************************************/

typedef struct {
    UINT16              charset_id;
    UINT16              str_len;
    UINT8               *p_str;
} tAVRC_FULL_NAME;

typedef struct {
    UINT16              str_len;
    UINT8               *p_str;
} tAVRC_NAME;


#ifndef AVRC_CAP_MAX_NUM_COMP_ID
#define AVRC_CAP_MAX_NUM_COMP_ID    4
#endif

#ifndef AVRC_CAP_MAX_NUM_EVT_ID
#define AVRC_CAP_MAX_NUM_EVT_ID     16
#endif

typedef union {
    UINT32  company_id[AVRC_CAP_MAX_NUM_COMP_ID];
    UINT8   event_id[AVRC_CAP_MAX_NUM_EVT_ID];
} tAVRC_CAPS_PARAM;

typedef struct {
    UINT8   attr_id;
    UINT8   attr_val;
} tAVRC_APP_SETTING;

typedef struct {
    UINT8   attr_id;
    UINT16  charset_id;
    UINT8   str_len;
    UINT8   *p_str;
} tAVRC_APP_SETTING_TEXT;

typedef UINT8 tAVRC_FEATURE_MASK[AVRC_FEATURE_MASK_SIZE];

typedef struct {
    UINT16              player_id;      /* 此媒体播放器的唯一标识符。*/
    UINT8               major_type;     /* 使用AVRC_MJ_TYPE_AUDIO、AVRC_MW_TYPE_VIDEO、AVRC_MJ_TYPE_BC_AUDIO或AVRC_MJ_TYPE_BC_VIDEO。*/
    UINT32              sub_type;       /* 使用AVRC_SUB_TYPE_NONE、AVRC_SSUB_TYPE_AUDIO_BOOK或AVRC_SUB_TYPE_PODCAST*/
    UINT8               play_status;    /* 使用AVRC_PLAYSTATE_STOPED、AVRC_PLAYSTATE_PLAYING、AVRC-PLAYSTATE_PAUSED、AVRC_TLAYSTATE_WD_SEEK、AVRC-PLAYSTATE_REV_SEEK或AVRC_PAYSTATE_ERROR*/
    tAVRC_FEATURE_MASK  features;       /* 支持的功能位掩码*/
    tAVRC_FULL_NAME     name;           /* 玩家名称、名称长度和角色集id。*/
} tAVRC_ITEM_PLAYER;

typedef struct {
    tAVRC_UID           uid;            /* 此文件夹的uid*/
    UINT8               type;           /* 使用AVRC_FOLDER_TYPE_MIXED、AVRC_FLOLDER_TYPE_TITLES、AVRC/FOLDER_YPE_ALNUMS、AVRC-FOLDER_TYPE ARTISTS、AVRC-FOLDER_TTYPE_GENRES、AVRC-OLDER_TYE_PLAYLISTS或AVRC_FOL DER_TYPE-YEARS。*/
    BOOLEAN             playable;       /* 如果可以播放文件夹，则返回TRUE。*/
    tAVRC_FULL_NAME     name;           /* 文件夹名称、名称长度和字符集id。*/
} tAVRC_ITEM_FOLDER;

typedef struct {
    UINT32              attr_id;        /* 使用AVRC_MEDIA_ATTR_ID_TITLE、AVRC_MMEDIA_ATTR_ID_ARTIST、AVRC_MEDIA_ATTR.ID_ALBUM、AVRC_DEDIA_ATTR-ID_TRACK_NUM、AVRC-MEDIA_AATTR_ID_NUM_TRACKS、AVRC_AEDIA_ATTR_ID_GENRE、AVRC-MEDIA_ATTA_ID_PLAYING_TIME*/
    tAVRC_FULL_NAME     name;           /* 属性值、值长度和字符集id。*/
} tAVRC_ATTR_ENTRY;

typedef struct {
    tAVRC_UID           uid;            /* 此媒体元素项的uid*/
    UINT8               type;           /* 使用AVRC_MEDIA_TYPE_AUDIO或AVRC_MEDIA_TYPE_VIDEO。*/
    tAVRC_FULL_NAME     name;           /* 媒体名称、名称长度和字符集id。*/
    UINT8               attr_count;     /* p_attr_list中的属性数*/
    tAVRC_ATTR_ENTRY   *p_attr_list;    /* 属性条目列表。*/
} tAVRC_ITEM_MEDIA;

typedef struct {
    UINT8                   item_type;  /* AVRC_ITEM_PLAYER、AVRC_ITE M_FOLDER或AVRC_ITEM _MEDIA*/
    union {
        tAVRC_ITEM_PLAYER   player;     /* 媒体播放器项目的属性。*/
        tAVRC_ITEM_FOLDER   folder;     /* 文件夹项的属性。*/
        tAVRC_ITEM_MEDIA    media;      /* 媒体项的属性。*/
    } u;
} tAVRC_ITEM;

/* 获取能力*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       capability_id;
} tAVRC_GET_CAPS_CMD;

/* 列表播放器应用值*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       attr_id;
} tAVRC_LIST_APP_VALUES_CMD;

/* 获取当前应用值*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       num_attr;
    UINT8       attrs[AVRC_MAX_APP_ATTR_SIZE];
} tAVRC_GET_CUR_APP_VALUE_CMD;

/* 设置应用值*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       num_val;
    tAVRC_APP_SETTING   *p_vals;
} tAVRC_SET_APP_VALUE_CMD;

/* 获取应用程序属性文本*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       num_attr;
    UINT8       attrs[AVRC_MAX_APP_ATTR_SIZE];
} tAVRC_GET_APP_ATTR_TXT_CMD;

/* 获取应用值Txt*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       attr_id;
    UINT8       num_val;
    UINT8       vals[AVRC_MAX_APP_ATTR_SIZE];
} tAVRC_GET_APP_VAL_TXT_CMD;

/* 信息字符集*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       num_id;
    UINT16      charsets[AVRC_MAX_CHARSET_SIZE];
} tAVRC_INFORM_CHARSET_CMD;

/* 通知电池状态*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       battery_status;
} tAVRC_BATTERY_STATUS_CMD;

/* 获取元素属性*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       num_attr;
    UINT32      attrs[AVRC_MAX_ELEM_ATTR_SIZE];
} tAVRC_GET_ELEM_ATTRS_CMD;

/* RegNotify（注册通知）*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       event_id;
    UINT32      param;
} tAVRC_REG_NOTIF_CMD;

/* 设置AddrPlayer*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT16      player_id;
} tAVRC_SET_ADDR_PLAYER_CMD;

/* 设置浏览播放器*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT16      player_id;
} tAVRC_SET_BR_PLAYER_CMD;

/* 设置绝对体积*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       volume;
} tAVRC_SET_VOLUME_CMD;

/* 获取文件夹项*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       scope;
    UINT32      start_item;
    UINT32      end_item;
    UINT8       attr_count;
    UINT32      *p_attr_list;
} tAVRC_GET_ITEMS_CMD;

/* 更改路径*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT16      uid_counter;
    UINT8       direction;
    tAVRC_UID   folder_uid;
} tAVRC_CHG_PATH_CMD;

/* 获取项目属性*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       scope;
    tAVRC_UID   uid;
    UINT16      uid_counter;
    UINT8       attr_count;
    UINT32      *p_attr_list;
} tAVRC_GET_ATTRS_CMD;

/* 搜索*/
typedef struct {
    UINT8           pdu;
    tAVRC_STS       status;
    UINT8           opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    tAVRC_FULL_NAME string;
} tAVRC_SEARCH_CMD;

/* 播放项*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       scope;
    tAVRC_UID   uid;
    UINT16      uid_counter;
} tAVRC_PLAY_ITEM_CMD;

/* 添加到当前播放*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       scope;
    tAVRC_UID   uid;
    UINT16      uid_counter;
} tAVRC_ADD_TO_PLAY_CMD;

typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
} tAVRC_CMD;

/* 继续并中止*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由AVRC_BldCommand根据pdu分配）*/
    UINT8       target_pdu;
} tAVRC_NEXT_CMD;

typedef union {
    UINT8                       pdu;
    tAVRC_CMD                   cmd;
    tAVRC_GET_CAPS_CMD          get_caps;               /* 获取能力*/
    tAVRC_CMD                   list_app_attr;          /* ListPlayerAppAttr*/
    tAVRC_LIST_APP_VALUES_CMD   list_app_values;        /* 列表播放器应用值*/
    tAVRC_GET_CUR_APP_VALUE_CMD get_cur_app_val;        /* 获取当前应用值*/
    tAVRC_SET_APP_VALUE_CMD     set_app_val;            /* 设置应用值*/
    tAVRC_GET_APP_ATTR_TXT_CMD  get_app_attr_txt;       /* 获取应用程序属性文本*/
    tAVRC_GET_APP_VAL_TXT_CMD   get_app_val_txt;        /* 获取应用值Txt*/
    tAVRC_INFORM_CHARSET_CMD    inform_charset;         /* 信息字符集*/
    tAVRC_BATTERY_STATUS_CMD    inform_battery_status;  /* 通知电池状态*/
    tAVRC_GET_ELEM_ATTRS_CMD    get_elem_attrs;         /* 获取元素属性*/
    tAVRC_CMD                   get_play_status;        /* 获取播放状态*/
    tAVRC_REG_NOTIF_CMD         reg_notif;              /* RegNotify（注册通知）*/
    tAVRC_NEXT_CMD              continu;                /* 持续*/
    tAVRC_NEXT_CMD              abort;                  /* 中止*/

    tAVRC_SET_ADDR_PLAYER_CMD   addr_player;            /* 设置AddrPlayer*/
    tAVRC_SET_VOLUME_CMD        volume;                 /* 设置绝对体积*/
    tAVRC_SET_BR_PLAYER_CMD     br_player;              /* 设置浏览播放器*/
    tAVRC_GET_ITEMS_CMD         get_items;              /* 获取文件夹项*/
    tAVRC_CHG_PATH_CMD          chg_path;               /* 更改路径*/
    tAVRC_GET_ATTRS_CMD         get_attrs;              /* 获取项目属性*/
    tAVRC_SEARCH_CMD            search;                 /* 搜索*/
    tAVRC_PLAY_ITEM_CMD         play_item;              /* 播放项*/
    tAVRC_ADD_TO_PLAY_CMD       add_to_play;            /* 添加到当前播放*/
} tAVRC_COMMAND;

/* 获取能力*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT8       capability_id;
    UINT8       count;
    tAVRC_CAPS_PARAM param;
} tAVRC_GET_CAPS_RSP;

/* ListPlayerAppAttr*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT8       num_attr;
    UINT8       attrs[AVRC_MAX_APP_ATTR_SIZE];
} tAVRC_LIST_APP_ATTR_RSP;

/* 列表播放器应用值*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT8       num_val;
    UINT8       vals[AVRC_MAX_APP_ATTR_SIZE];
} tAVRC_LIST_APP_VALUES_RSP;

/* 获取当前应用值*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT8       num_val;
    tAVRC_APP_SETTING   *p_vals;
} tAVRC_GET_CUR_APP_VALUE_RSP;

/* 获取应用程序属性文本*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT8       num_attr;
    tAVRC_APP_SETTING_TEXT   *p_attrs;
} tAVRC_GET_APP_ATTR_TXT_RSP;

/* 获取元素属性*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT8       num_attr;
    tAVRC_ATTR_ENTRY   *p_attrs;
} tAVRC_GET_ELEM_ATTRS_RSP;

/* 获取播放状态*/
typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT32      song_len;
    UINT32      song_pos;
    UINT8       play_status;
} tAVRC_GET_PLAY_STATUS_RSP;

/* AddressedPlayer更改的通知事件参数*/
typedef struct {
    UINT16              player_id;
    UINT16              uid_counter;
} tAVRC_ADDR_PLAYER_PARAM;

#ifndef AVRC_MAX_APP_SETTINGS
#define AVRC_MAX_APP_SETTINGS    8
#endif

/* 播放机应用程序设置更改的通知事件参数*/
typedef struct {
    UINT8               num_attr;
    UINT8               attr_id[AVRC_MAX_APP_SETTINGS];
    UINT8               attr_value[AVRC_MAX_APP_SETTINGS];
} tAVRC_PLAYER_APP_PARAM;

typedef union {
    tAVRC_PLAYSTATE         play_status;
    tAVRC_UID               track;
    UINT32                  play_pos;
    tAVRC_BATTERY_STATUS    battery_status;
    tAVRC_SYSTEMSTATE       system_status;
    tAVRC_PLAYER_APP_PARAM  player_setting;
    tAVRC_ADDR_PLAYER_PARAM addr_player;
    UINT16                  uid_counter;
    UINT8                   volume;
} tAVRC_NOTIF_RSP_PARAM;

/* RegNotify（注册通知）*/
typedef struct {
    UINT8                   pdu;
    tAVRC_STS               status;
    UINT8                   opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT8                   event_id;
    tAVRC_NOTIF_RSP_PARAM   param;
} tAVRC_REG_NOTIF_RSP;

/* 设置绝对体积*/
typedef struct {
    UINT8               pdu;
    tAVRC_STS           status;
    UINT8               opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT8               volume;
} tAVRC_SET_VOLUME_RSP;

/* 设置浏览播放器*/
typedef struct {
    UINT8               pdu;
    tAVRC_STS           status;
    UINT8               opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT16              uid_counter;
    UINT32              num_items;
    UINT16              charset_id;
    UINT8               folder_depth;
    tAVRC_NAME          *p_folders;
} tAVRC_SET_BR_PLAYER_RSP;

/* 获取文件夹项*/
typedef struct {
    UINT8               pdu;
    tAVRC_STS           status;
    UINT8               opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT16              uid_counter;
    UINT16              item_count;
    tAVRC_ITEM          *p_item_list;
} tAVRC_GET_ITEMS_RSP;

/* 更改路径*/
typedef struct {
    UINT8               pdu;
    tAVRC_STS           status;
    UINT8               opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT32              num_items;
} tAVRC_CHG_PATH_RSP;

/* 获取项目属性*/
typedef struct {
    UINT8               pdu;
    tAVRC_STS           status;
    UINT8               opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT8               attr_count;
    tAVRC_ATTR_ENTRY    *p_attr_list;
} tAVRC_GET_ATTRS_RSP;

/* 搜索*/
typedef struct {
    UINT8               pdu;
    tAVRC_STS           status;
    UINT8               opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
    UINT16              uid_counter;
    UINT32              num_items;
} tAVRC_SEARCH_RSP;


typedef struct {
    UINT8       pdu;
    tAVRC_STS   status;
    UINT8       opcode;         /* 操作代码（由avrc_BldResponse用户从avrc_cmd.opcode复制。根据pdu生成的代码无效）*/
} tAVRC_RSP;

typedef union {
    UINT8                           pdu;
    tAVRC_RSP                       rsp;
    tAVRC_GET_CAPS_RSP              get_caps;               /* 获取能力*/
    tAVRC_LIST_APP_ATTR_RSP         list_app_attr;          /* ListPlayerAppAttr*/
    tAVRC_LIST_APP_VALUES_RSP       list_app_values;        /* 列表播放器应用值*/
    tAVRC_GET_CUR_APP_VALUE_RSP     get_cur_app_val;        /* 获取当前应用值*/
    tAVRC_RSP                       set_app_val;            /* 设置应用值*/
    tAVRC_GET_APP_ATTR_TXT_RSP      get_app_attr_txt;       /* 获取应用程序属性文本*/
    tAVRC_GET_APP_ATTR_TXT_RSP      get_app_val_txt;        /* 获取应用值Txt*/
    tAVRC_RSP                       inform_charset;         /* 信息字符集*/
    tAVRC_RSP                       inform_battery_status;  /* 通知电池状态*/
    tAVRC_GET_ELEM_ATTRS_RSP        get_elem_attrs;         /* 获取元素属性*/
    tAVRC_GET_PLAY_STATUS_RSP       get_play_status;        /* 获取播放状态*/
    tAVRC_REG_NOTIF_RSP             reg_notif;              /* RegNotify（注册通知）*/
    tAVRC_RSP                       continu;                /* 持续*/
    tAVRC_RSP                       abort;                  /* 中止*/

    tAVRC_RSP                       addr_player;            /* 设置AddrPlayer*/
    tAVRC_SET_VOLUME_RSP            volume;                 /* 设置绝对体积*/
    tAVRC_SET_BR_PLAYER_RSP         br_player;              /* 设置浏览播放器*/
    tAVRC_GET_ITEMS_RSP             get_items;              /* 获取文件夹项*/
    tAVRC_CHG_PATH_RSP              chg_path;               /* 更改路径*/
    tAVRC_GET_ATTRS_RSP             get_attrs;              /* 获取项目属性*/
    tAVRC_SEARCH_RSP                search;                 /* 搜索*/
    tAVRC_RSP                       play_item;              /* 播放项*/
    tAVRC_RSP                       add_to_play;            /* 添加到当前播放*/
} tAVRC_RESPONSE;

#endif  ///AVRC_INCLUDED == TRUE
#endif

