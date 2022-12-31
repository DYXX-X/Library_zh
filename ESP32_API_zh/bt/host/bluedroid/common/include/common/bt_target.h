/******************************************************************************
 * 版权所有（c）2014 Android开源项目版权所有（c）1999-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef BT_TARGET_H
#define BT_TARGET_H

#include <bt_common.h>
#include "soc/soc_caps.h"

#ifndef BUILDCFG
#define BUILDCFG
#endif

/*
#如果！已定义（HAS_BDROID_BUILDCFG）&&！defined（HAS_NO_BDROID_BUILDCFG）#error“Android.mk文件不包含BDROID_CFLAGS，可能不包含bdorid_C_include”#endif
*/

#ifdef HAS_BDROID_BUILDCFG
#include "bdroid_buildcfg.h"
#endif

#include "bluedroid_user_config.h"
#include "stack/bt_types.h"   /* 这必须在buildcfg之后定义。小时*/

#include "stack/dyn_mem.h"    /* 定义组件的静态和/或动态内存*/


/* 用户配置中的操作系统配置（例如：sdkconfig）*/
#define BT_BTU_TASK_STACK_SIZE      UC_BTU_TASK_STACK_SIZE

/******************************************************************************
** 经典BT功能
**
******************************************************************************/
#if (UC_BT_CLASSIC_ENABLED == TRUE)
#define CLASSIC_BT_INCLUDED         TRUE
#define BTC_SM_INCLUDED             TRUE
#define BTC_PRF_QUEUE_INCLUDED      TRUE
#define BTC_GAP_BT_INCLUDED         TRUE
#define BTA_SDP_INCLUDED            TRUE
#define BTA_DM_PM_INCLUDED          TRUE
#define BTC_DM_PM_INCLUDED          TRUE
#define SDP_INCLUDED                TRUE
#define BTA_DM_QOS_INCLUDED         TRUE

#if (UC_BT_A2DP_ENABLED == TRUE)
#define BTA_AR_INCLUDED             TRUE
#define BTA_AV_INCLUDED             TRUE
#define AVDT_INCLUDED               TRUE
#define A2D_INCLUDED                TRUE
#define AVCT_INCLUDED               TRUE
#define AVRC_INCLUDED               TRUE
#define BTC_AV_INCLUDED             TRUE
#define BTA_AV_SINK_INCLUDED        TRUE
#define BTC_AV_SINK_INCLUDED        TRUE
#define SBC_DEC_INCLUDED            TRUE
#define BTC_AV_SRC_INCLUDED         TRUE
#define SBC_ENC_INCLUDED            TRUE
#endif /* UC_BT_A2DP_ENABLED */

#if (UC_BT_SPP_ENABLED == TRUE)
#define RFCOMM_INCLUDED             TRUE
#define BTA_JV_INCLUDED             TRUE
#define BTC_SPP_INCLUDED            TRUE
#endif /* UC_BT_SPP_ENABLED */

#if (UC_BT_HFP_AG_ENABLED == TRUE)
#define BTC_HF_INCLUDED             TRUE
#define BTA_AG_INCLUDED             TRUE
#define PLC_INCLUDED                TRUE
#ifndef RFCOMM_INCLUDED
#define RFCOMM_INCLUDED             TRUE
#endif
#ifndef BTM_SCO_INCLUDED
#define BTM_SCO_INCLUDED            TRUE
#endif
#ifndef BTM_MAX_SCO_LINKS
#define BTM_MAX_SCO_LINKS           (1)
#endif
#ifndef SBC_DEC_INCLUDED
#define SBC_DEC_INCLUDED            TRUE
#endif
#ifndef SBC_ENC_INCLUDED
#define SBC_ENC_INCLUDED            TRUE
#endif
#endif  /* UC_BT_HFP_AG_ENABLED */

#if (UC_BT_HFP_CLIENT_ENABLED == TRUE)
#define BTC_HF_CLIENT_INCLUDED      TRUE
#define BTA_HF_INCLUDED             TRUE
#define PLC_INCLUDED                TRUE
#ifndef RFCOMM_INCLUDED
#define RFCOMM_INCLUDED             TRUE
#endif
#ifndef BTM_SCO_INCLUDED
#define BTM_SCO_INCLUDED            TRUE
#endif
#ifndef BTM_MAX_SCO_LINKS
#define BTM_MAX_SCO_LINKS           (1)
#endif

#ifndef SBC_DEC_INCLUDED
#define SBC_DEC_INCLUDED            TRUE
#endif
#ifndef SBC_ENC_INCLUDED
#define SBC_ENC_INCLUDED            TRUE
#endif
#endif  /* UC_BT_HFP_CLIENT_ENABLED */

#if UC_BT_SSP_ENABLED
#define BT_SSP_INCLUDED             TRUE
#endif /* UC_BT_SSP_ENABLED */

#if UC_BT_HID_ENABLED
#define BT_HID_INCLUDED             TRUE
#endif /* UC_BT_HID_ENABLED */

#if UC_BT_HID_HOST_ENABLED
#define HID_HOST_INCLUDED           TRUE
#define BTA_HH_INCLUDED             TRUE
#define BTC_HH_INCLUDED             TRUE
#endif /* UC_BT_HID_HOST_ENABLED */

#if UC_BT_HID_DEVICE_ENABLED
#define HID_DEV_INCLUDED            TRUE
#define BTA_HD_INCLUDED             TRUE
#define BTC_HD_INCLUDED             TRUE
#endif /* UC_BT_HID_DEVICE_ENABLED */

#endif /* UC_BT_CLASSIC_ENABLED */

/* 此设置用于启用GAP L2CAP连接。*/
#if (VND_BT_JV_BTA_L2CAP == TRUE)
#define BTA_JV_L2CAP_INCLUDED       TRUE
#define GAP_CONN_INCLUDED           TRUE
#endif /* VND_BT_JV_BTA_L2CAP */

#ifndef CLASSIC_BT_INCLUDED
#define CLASSIC_BT_INCLUDED         FALSE
#endif /* CLASSIC_BT_INCLUDED */

#ifndef CLASSIC_BT_GATT_INCLUDED
#define CLASSIC_BT_GATT_INCLUDED    FALSE
#endif /* CLASSIC_BT_GATT_INCLUDED */
/******************************************************************************
** BLE功能
**
******************************************************************************/
#if (UC_BT_BLE_ENABLED ==TRUE)
#define BLE_INCLUDED              TRUE
#else
#define BLE_INCLUDED              FALSE
#endif /* UC_BT_BLE_ENABLED */

#if (UC_BT_BLE_50_FEATURES_SUPPORTED == TRUE)
#define BLE_50_FEATURE_SUPPORT   TRUE
#else
#define BLE_50_FEATURE_SUPPORT   FALSE
#endif

#if (UC_BT_BLE_42_FEATURES_SUPPORTED == TRUE || BLE_50_FEATURE_SUPPORT == FALSE)
#define BLE_42_FEATURE_SUPPORT   TRUE
#else
#define BLE_42_FEATURE_SUPPORT   FALSE
#endif

#if (UC_BT_BLE_RPA_SUPPORTED  == TRUE)
#define CONTROLLER_RPA_LIST_ENABLE   TRUE
#else
#define CONTROLLER_RPA_LIST_ENABLE   FALSE
#endif

#if (UC_BT_GATTS_ENABLE)
#define GATTS_INCLUDED              TRUE
#else
#define GATTS_INCLUDED              FALSE
#endif /* UC_BT_GATTS_ENABLE */

#if (UC_BT_GATTC_ENABLE)
#define GATTC_INCLUDED              TRUE
#else
#define GATTC_INCLUDED              FALSE
#endif  /* UC_BT_GATTC_ENABLE */

#if (UC_BT_GATTC_ENABLE && UC_BT_GATTC_CACHE_NVS_FLASH_ENABLED)
#define GATTC_CACHE_NVS             TRUE
#else
#define GATTC_CACHE_NVS             FALSE
#endif  /* UC_BT_GATTC_ENABLE && UC_BT_GATTC_CACHE_NVS_FLASH_ENABLED */

#if (UC_BT_GATTC_ENABLE && UC_BT_GATTC_CONNECT_RETRY_COUNT)
#define GATTC_CONNECT_RETRY_COUNT             UC_BT_GATTC_CONNECT_RETRY_COUNT
#else
#define GATTC_CONNECT_RETRY_COUNT             0
#endif  /* UC_BT_GATTC_ENABLE && UC_BT_GATTC_CONNECT_RETRY_COUNT */

#if (GATTC_CONNECT_RETRY_COUNT > 0)
#define GATTC_CONNECT_RETRY_EN     TRUE
#else
#define GATTC_CONNECT_RETRY_EN     FALSE
#endif

#if (UC_BT_SMP_ENABLE)
#define SMP_INCLUDED                TRUE
#if (BLE_INCLUDED == TRUE)
#define BLE_PRIVACY_SPT             TRUE
#else
#define BLE_PRIVACY_SPT             FALSE
#endif  /*BLE_INCLUDED*/
#else
#define SMP_INCLUDED                FALSE
#define BLE_PRIVACY_SPT             FALSE
#endif  /* UC_BT_SMP_ENABLE */

#if(UC_BT_SMP_SLAVE_CON_PARAMS_UPD_ENABLE)
#define SMP_SLAVE_CON_PARAMS_UPD_ENABLE     TRUE
#else
#define SMP_SLAVE_CON_PARAMS_UPD_ENABLE     FALSE
#endif /* UC_BT_SMP_SLAVE_CON_PARAMS_UPD_ENABLE */

#ifdef UC_BTDM_BLE_ADV_REPORT_FLOW_CTRL_SUPP
#define BLE_ADV_REPORT_FLOW_CONTROL         (UC_BTDM_BLE_ADV_REPORT_FLOW_CTRL_SUPP && BLE_INCLUDED)
#endif /* UC_BTDM_BLE_ADV_REPORT_FLOW_CTRL_SUPP */

#ifdef UC_BTDM_BLE_ADV_REPORT_FLOW_CTRL_NUM
#define BLE_ADV_REPORT_FLOW_CONTROL_NUM     UC_BTDM_BLE_ADV_REPORT_FLOW_CTRL_NUM
#endif /* UC_BTDM_BLE_ADV_REPORT_FLOW_CTRL_NUM */

#ifdef UC_BTDM_BLE_ADV_REPORT_DISCARD_THRSHOLD
#define BLE_ADV_REPORT_DISCARD_THRSHOLD     UC_BTDM_BLE_ADV_REPORT_DISCARD_THRSHOLD
#endif /* UC_BTDM_BLE_ADV_REPORT_DISCARD_THRSHOLD */

#ifdef UC_BT_ACL_CONNECTIONS
#define MAX_ACL_CONNECTIONS         UC_BT_ACL_CONNECTIONS
#define GATT_MAX_PHY_CHANNEL        UC_BT_ACL_CONNECTIONS
#endif  /* UC_BT_ACL_CONNECTIONS */

#ifdef UC_BT_MULTI_CONNECTION_ENBALE
#define BT_MULTI_CONNECTION_ENBALE  UC_BT_MULTI_CONNECTION_ENBALE
#endif

#if(BT_MULTI_CONNECTION_ENBALE && (CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32S3))
#define BLE_CE_LEN_MIN           5
#else
#define BLE_CE_LEN_MIN           0
#endif

#ifdef UC_BT_BLE_ESTAB_LINK_CONN_TOUT
#define BLE_ESTABLISH_LINK_CONNECTION_TIMEOUT UC_BT_BLE_ESTAB_LINK_CONN_TOUT
#endif

#ifdef SOC_BLE_DONT_UPDATE_OWN_RPA
#define BLE_UPDATE_BLE_ADDR_TYPE_RPA FALSE
#else
#define BLE_UPDATE_BLE_ADDR_TYPE_RPA TRUE
#endif
//------------------从bdroid_buildcfg.h添加---------------------
#ifndef L2CAP_EXTFEA_SUPPORTED_MASK
#define L2CAP_EXTFEA_SUPPORTED_MASK (L2CAP_EXTFEA_ENH_RETRANS | L2CAP_EXTFEA_STREAM_MODE | L2CAP_EXTFEA_NO_CRC | L2CAP_EXTFEA_FIXED_CHNLS)
#endif

#ifndef BTUI_OPS_FORMATS
#define BTUI_OPS_FORMATS (BTA_OP_VCARD21_MASK | BTA_OP_ANY_MASK)
#endif

#ifndef BTA_RFC_MTU_SIZE
#define BTA_RFC_MTU_SIZE (L2CAP_MTU_SIZE-L2CAP_MIN_OFFSET-RFCOMM_DATA_OVERHEAD)
#endif

#ifndef SBC_NO_PCM_CPY_OPTION
#define SBC_NO_PCM_CPY_OPTION FALSE
#endif

#ifndef BT_APP_DEMO
#define BT_APP_DEMO TRUE
#endif

#ifndef BTIF_INCLUDED
#define BTIF_INCLUDED FALSE
#endif

/******************************************************************************
** BTC层组件
**
******************************************************************************/
#ifndef BTC_GAP_BT_INCLUDED
#define BTC_GAP_BT_INCLUDED FALSE
#endif

#ifndef BTC_PRF_QUEUE_INCLUDED
#define BTC_PRF_QUEUE_INCLUDED FALSE
#endif

#ifndef BTC_SM_INCLUDED
#define BTC_SM_INCLUDED FALSE
#endif

#ifndef BTC_AV_INCLUDED
#define BTC_AV_INCLUDED FALSE
#endif

#ifndef BTC_AV_SINK_INCLUDED
#define BTC_AV_SINK_INCLUDED FALSE
#endif

#ifndef BTC_AV_SRC_INCLUDED
#define BTC_AV_SRC_INCLUDED FALSE
#endif

#ifndef BTC_SPP_INCLUDED
#define BTC_SPP_INCLUDED FALSE
#endif

#ifndef BTC_HH_INCLUDED
#define BTC_HH_INCLUDED FALSE
#endif

#ifndef BTC_HD_INCLUDED
#define BTC_HD_INCLUDED FALSE
#endif

#ifndef SBC_DEC_INCLUDED
#define SBC_DEC_INCLUDED FALSE
#endif

#ifndef SBC_ENC_INCLUDED
#define SBC_ENC_INCLUDED FALSE
#endif

/******************************************************************************
** BTA层组件
**
******************************************************************************/
#ifndef BTA_INCLUDED
#define BTA_INCLUDED TRUE
#endif

#ifndef BTA_DM_PM_INCLUDED
#define BTA_DM_PM_INCLUDED FALSE
#endif

#ifndef BTA_DM_QOS_INCLUDED
#define BTA_DM_QOS_INCLUDED FALSE
#endif

#ifndef BTA_PAN_INCLUDED
#define BTA_PAN_INCLUDED FALSE
#endif

#ifndef BTA_HD_INCLUDED
#define BTA_HD_INCLUDED FALSE
#endif

#ifndef BTA_HH_INCLUDED
#define BTA_HH_INCLUDED FALSE
#endif

#ifndef BTA_HH_ROLE
#define BTA_HH_ROLE BTA_MASTER_ROLE_PREF
#endif

#ifndef BTA_HH_LE_INCLUDED
#define BTA_HH_LE_INCLUDED FALSE
#endif

#ifndef BTA_AR_INCLUDED
#define BTA_AR_INCLUDED FALSE
#endif

#ifndef BTA_AV_INCLUDED
#define BTA_AV_INCLUDED FALSE
#endif

#ifndef BTA_AV_SINK_INCLUDED
#define BTA_AV_SINK_INCLUDED FALSE
#endif

#ifndef BTA_JV_INCLUDED
#define BTA_JV_INCLUDED FALSE
#endif

#ifndef BTA_SDP_INCLUDED
#define BTA_SDP_INCLUDED FALSE
#endif

/* 此设置用于启用GAP L2CAP连接。*/
#ifndef VND_BT_JV_BTA_L2CAP
#define VND_BT_JV_BTA_L2CAP        FALSE
#endif

#ifndef BTA_JV_L2CAP_INCLUDED
#define BTA_JV_L2CAP_INCLUDED       FALSE
#endif

#ifndef GAP_CONN_INCLUDED
#define GAP_CONN_INCLUDED           FALSE
#endif

/******************************************************************************
** 堆栈层组件
**
******************************************************************************/
#ifndef AVCT_INCLUDED
#define AVCT_INCLUDED FALSE
#endif

#ifndef AVDT_INCLUDED
#define AVDT_INCLUDED FALSE
#endif

/******************************************************************************
** 组件的参数配置
**
******************************************************************************/
#ifndef BTA_DISABLE_DELAY
#define BTA_DISABLE_DELAY 200 /* 以毫秒为单位*/
#endif

#ifndef BTA_SYS_TIMER_PERIOD
#define BTA_SYS_TIMER_PERIOD  100
#endif

#ifndef SBC_FOR_EMBEDDED_LINUX
#define SBC_FOR_EMBEDDED_LINUX TRUE
#endif

#ifndef AVDT_VERSION
#define AVDT_VERSION  0x0102
#endif

#ifndef BTA_AG_AT_MAX_LEN
#define BTA_AG_AT_MAX_LEN  512
#endif

#ifndef BTA_AVRCP_FF_RW_SUPPORT
#define BTA_AVRCP_FF_RW_SUPPORT FALSE
#endif

#ifndef BTA_AG_SCO_PKT_TYPES
#define BTA_AG_SCO_PKT_TYPES  (BTM_SCO_LINK_ONLY_MASK | BTM_SCO_PKT_TYPES_MASK_EV3 |  BTM_SCO_PKT_TYPES_MASK_NO_3_EV3 | BTM_SCO_PKT_TYPES_MASK_NO_2_EV5 | BTM_SCO_PKT_TYPES_MASK_NO_3_EV5)
#endif

#ifndef BTA_AV_RET_TOUT
#define BTA_AV_RET_TOUT 15
#endif

#ifndef PORCHE_PAIRING_CONFLICT
#define PORCHE_PAIRING_CONFLICT  TRUE
#endif

#ifndef BTA_AV_CO_CP_SCMS_T
#define BTA_AV_CO_CP_SCMS_T  FALSE
#endif

#if UC_BT_BLE_HOST_QUEUE_CONGESTION_CHECK
#define SCAN_QUEUE_CONGEST_CHECK  TRUE
#else
#define SCAN_QUEUE_CONGEST_CHECK  FALSE
#endif

#ifdef UC_CONFIG_BT_GATTS_PPCP_CHAR_GAP
#define BTM_PERIPHERAL_ENABLED   UC_CONFIG_BT_GATTS_PPCP_CHAR_GAP
#endif

#ifdef UC_BT_GATTS_SEND_SERVICE_CHANGE_MODE
#define GATTS_SEND_SERVICE_CHANGE_MODE UC_BT_GATTS_SEND_SERVICE_CHANGE_MODE
#endif

#ifdef UC_BT_BLE_ACT_SCAN_REP_ADV_SCAN
#define BTM_BLE_ACTIVE_SCAN_REPORT_ADV_SCAN_RSP_INDIVIDUALLY    UC_BT_BLE_ACT_SCAN_REP_ADV_SCAN
#endif

/* 此功能用于扫描交错扫描*/
#ifndef BTA_HOST_INTERLEAVE_SEARCH
#define BTA_HOST_INTERLEAVE_SEARCH FALSE
#endif

#ifndef BT_USE_TRACES
#define BT_USE_TRACES  FALSE
#endif

#ifndef BT_TRACE_BTIF
#define BT_TRACE_BTIF  TRUE
#endif

#ifndef BT_TRACE_VERBOSE
#define BT_TRACE_VERBOSE  FALSE
#endif

#ifndef BTA_DM_SDP_DB_SIZE
#define BTA_DM_SDP_DB_SIZE  8000
#endif

#ifndef HL_INCLUDED
#define HL_INCLUDED  TRUE
#endif

#ifndef AG_VOICE_SETTINGS
#define AG_VOICE_SETTINGS  HCI_DEFAULT_VOICE_SETTINGS
#endif

#ifndef BTIF_DM_OOB_TEST
#define BTIF_DM_OOB_TEST  FALSE
#endif

// 进入
// FTS、OPS连接的空闲状态
#ifndef BTA_FTS_OPS_IDLE_TO_SNIFF_DELAY_MS
#define BTA_FTS_OPS_IDLE_TO_SNIFF_DELAY_MS 7000
#endif
#ifndef BTA_FTC_OPS_IDLE_TO_SNIFF_DELAY_MS
#define BTA_FTC_OPS_IDLE_TO_SNIFF_DELAY_MS 5000
#endif

//------------------从bdroid_buildcfg.h添加的结束---------------------


/******************************************************************************
** 缓冲区大小
**
******************************************************************************/

#ifndef BT_DEFAULT_BUFFER_SIZE
#define BT_DEFAULT_BUFFER_SIZE          (4096 + 16)
#endif

#ifndef BT_SMALL_BUFFER_SIZE
#define BT_SMALL_BUFFER_SIZE            660
#endif

/* 从下层接收HCI事件。*/
#ifndef HCI_CMD_BUF_SIZE
#define HCI_CMD_BUF_SIZE                BT_SMALL_BUFFER_SIZE
#endif

/* 发送SDP数据包。*/
#ifndef SDP_DATA_BUF_SIZE
#define SDP_DATA_BUF_SIZE               BT_DEFAULT_BUFFER_SIZE
#endif

/* 发送RFCOMM命令包。*/
#ifndef RFCOMM_CMD_BUF_SIZE
#define RFCOMM_CMD_BUF_SIZE             BT_SMALL_BUFFER_SIZE
#endif

/* 发送RFCOMM数据包。*/
#ifndef RFCOMM_DATA_BUF_SIZE
#define RFCOMM_DATA_BUF_SIZE            BT_DEFAULT_BUFFER_SIZE
#endif

/* 向对等端发送L2CAP数据包，向控制器发送HCI消息。*/
#ifndef L2CAP_CMD_BUF_SIZE
#define L2CAP_CMD_BUF_SIZE              BT_SMALL_BUFFER_SIZE
#endif

#ifndef L2CAP_USER_TX_BUF_SIZE
#define L2CAP_USER_TX_BUF_SIZE          BT_DEFAULT_BUFFER_SIZE
#endif

#ifndef L2CAP_USER_RX_BUF_SIZE
#define L2CAP_USER_RX_BUF_SIZE          BT_DEFAULT_BUFFER_SIZE
#endif

/* 以ERTM模式发送L2CAP分段数据包*/
#ifndef L2CAP_FCR_TX_BUF_SIZE
#define L2CAP_FCR_TX_BUF_SIZE           BT_DEFAULT_BUFFER_SIZE
#endif

/* 在ERTM模式下接收L2CAP分段数据包*/
#ifndef L2CAP_FCR_RX_BUF_SIZE
#define L2CAP_FCR_RX_BUF_SIZE           BT_DEFAULT_BUFFER_SIZE
#endif

#ifndef L2CAP_FCR_ERTM_BUF_SIZE
#define L2CAP_FCR_ERTM_BUF_SIZE         (10240 + 24)
#endif

/* 如果HCI缓冲池与BR/EDR共享，则要分配给LE的ACL缓冲区数*/
#ifndef L2C_DEF_NUM_BLE_BUF_SHARED
#define L2C_DEF_NUM_BLE_BUF_SHARED      1
#endif

/* BTM向控制器发送HCI命令时使用。*/
#ifndef BTM_CMD_BUF_SIZE
#define BTM_CMD_BUF_SIZE                BT_SMALL_BUFFER_SIZE
#endif

#ifndef OBX_LRG_DATA_BUF_SIZE
#define OBX_LRG_DATA_BUF_SIZE           (8080 + 26)
#endif

/* 用于向L2CAP发送数据。*/
#ifndef GAP_DATA_BUF_SIZE
#define GAP_DATA_BUF_SIZE               BT_DEFAULT_BUFFER_SIZE
#endif

/* BNEP数据和协议消息。*/
#ifndef BNEP_BUF_SIZE
#define BNEP_BUF_SIZE                   BT_DEFAULT_BUFFER_SIZE
#endif

/* 协议消息的AVDTP缓冲区大小*/
#ifndef AVDT_CMD_BUF_SIZE
#define AVDT_CMD_BUF_SIZE               BT_SMALL_BUFFER_SIZE
#endif

/* 碎片情况下媒体数据包的AVDTP缓冲区大小*/
#ifndef AVDT_DATA_BUF_SIZE
#define AVDT_DATA_BUF_SIZE              BT_DEFAULT_BUFFER_SIZE
#endif

#ifndef PAN_BUF_SIZE
#define PAN_BUF_SIZE                    BT_DEFAULT_BUFFER_SIZE
#endif

/* 为PAN分配的最大缓冲区数*/
#ifndef PAN_BUF_MAX
#define PAN_BUF_MAX                     100
#endif

/* 协议消息的AVCTP缓冲区大小*/
#ifndef AVCT_CMD_BUF_SIZE
#define AVCT_CMD_BUF_SIZE               288
#endif

/* 协议消息的AVRCP缓冲区大小*/
#ifndef AVRC_CMD_BUF_SIZE
#define AVRC_CMD_BUF_SIZE               288
#endif

/* 协议消息的AVRCP元数据缓冲区大小*/
#ifndef AVRC_META_CMD_BUF_SIZE
#define AVRC_META_CMD_BUF_SIZE          BT_SMALL_BUFFER_SIZE
#endif

#ifndef BTA_HL_LRG_DATA_BUF_SIZE
#define BTA_HL_LRG_DATA_BUF_SIZE        (10240 + 24)
#endif

/* GATT服务器数据库缓冲区大小*/
#ifndef GATT_DB_BUF_SIZE
#define GATT_DB_BUF_SIZE                128
#endif

/* GATT数据发送缓冲区大小*/
#ifndef GATT_DATA_BUF_SIZE
#define GATT_DATA_BUF_SIZE              BT_DEFAULT_BUFFER_SIZE
#endif

/******************************************************************************
** HCI服务（H4）
**
******************************************************************************/

/* 低分辨率系统使用2秒，高分辨率系统使用1秒*/
#ifndef BT_1SEC_TIMEOUT
#define BT_1SEC_TIMEOUT             (2)
#endif

/* 快速计时器*/
/* 如果L2CAP_FCR_INCLUDED为TRUE，则其分辨率应为100毫秒*/
/* 如果不包括任何一个，则QUICK_TIMER_TICKS_PER_SEC设置为0以排除快速计时器*/
#ifndef QUICK_TIMER_TICKS_PER_SEC
#define QUICK_TIMER_TICKS_PER_SEC   10       /* 100ms计时器*/
#endif

/******************************************************************************
** BTM
**
******************************************************************************/

/* 取消对传入SSP的查询*/
#ifndef BTM_NO_SSP_ON_INQUIRY
#define BTM_NO_SSP_ON_INQUIRY       FALSE
#endif

/* 如果为TRUE，则包括SCO*/
#ifndef BTM_SCO_INCLUDED
#define BTM_SCO_INCLUDED                FALSE       /* TRUE包括SCO代码*/
#endif

/* 如果为TRUE，则包括SCO*/
#ifndef BTM_SCO_HCI_INCLUDED
#if UC_BT_HFP_AUDIO_DATA_PATH_HCI
#define BTM_SCO_HCI_INCLUDED            TRUE       /* TRUE包括HCI代码上的SCO*/
#else
#define BTM_SCO_HCI_INCLUDED            FALSE
#endif /* UC_HFP_AUDIO_DATA_PATH_HCI */
#endif

/* 如果为TRUE，则包含WBS*/
#ifndef BTM_WBS_INCLUDED
#define BTM_WBS_INCLUDED                UC_BT_HFP_WBS_ENABLE    /* TRUE包括WBS代码*/
#endif

/*  这用于解决控制器错误，该错误不喜欢在角色切换过程中发出Disconnect
*/
#ifndef BTM_DISC_DURING_RS
#define BTM_DISC_DURING_RS TRUE
#endif

/**************************
** 初始SCO TX信用
*************************/
/* 最大TX SCO数据包大小*/
#ifndef BTM_SCO_DATA_SIZE_MAX
#define BTM_SCO_DATA_SIZE_MAX       120 //240
#endif

/* 最大TX eSCO数据包大小*/
#ifndef BTM_MSBC_FRAME_SIZE
#define BTM_MSBC_FRAME_SIZE      60
#endif

/* TX eSCO数据包大小*/
#ifndef BTM_MSBC_FRAME_DATA_SIZE
#define BTM_MSBC_FRAME_DATA_SIZE          57
#endif

/* BTM查询数据库的字节大小。5作为默认值*/
#ifndef BTM_INQ_DB_SIZE
#define BTM_INQ_DB_SIZE             5
#endif

/* 默认扫描模式*/
#ifndef BTM_DEFAULT_SCAN_TYPE
#define BTM_DEFAULT_SCAN_TYPE       BTM_SCAN_TYPE_INTERLACED
#endif

/* 当无法发现时，是否应允许连接到未知设备？*/
#ifndef BTM_ALLOW_CONN_IF_NONDISCOVER
#define BTM_ALLOW_CONN_IF_NONDISCOVER   TRUE
#endif

/* 设置Page_Scan_Window：设备执行页面扫描的时间长度。*/
#ifndef BTM_DEFAULT_CONN_WINDOW
#define BTM_DEFAULT_CONN_WINDOW     0x0012
#endif

/* 设置Page_Scan_Activity：两次连续页面扫描开始之间的间隔。*/
#ifndef BTM_DEFAULT_CONN_INTERVAL
#define BTM_DEFAULT_CONN_INTERVAL   0x0800
#endif

/* 启用自动查询扫描时，将设置查询扫描窗口。*/
#ifndef BTM_DEFAULT_DISC_WINDOW
#define BTM_DEFAULT_DISC_WINDOW     0x0012
#endif

/* 启用自动查询扫描时，将设置查询扫描间隔。*/
#ifndef BTM_DEFAULT_DISC_INTERVAL
#define BTM_DEFAULT_DISC_INTERVAL   0x0800
#endif

/*
* {SERVICE_CLASS, MAJOR_CLASS, MINOR_CLASS}
*
* 服务等级：0x5A（Bit17-网络，Bit19-捕获，Bit20-对象传输，Bit22-电话）主要等级：0x02-电话次要等级：0x0C-智能电话
*
*/
#define BTA_DM_COD_SMARTPHONE {0x5A, 0x02, 0x0C}

/*
* {SERVICE_CLASS, MAJOR_CLASS, MINOR_CLASS}
*
* 服务等级：0x2C（位21-音频，位19-捕获）主要等级：0x04-音频/视频次要等级：0x05-扬声器
*/
#define BTA_DM_COD_LOUDSPEAKER {0x2C, 0x04, 0x14}

/*
* {SERVICE_CLASS, MAJOR_CLASS, MINOR_CLASS}
*
* SERVICE_CLASS:0x0无MAJOR_CLASS:0x1f-未分类：未指定设备代码MINOR_CLASS:0x00-无
*/
#define BTA_DM_COD_UNCLASSIFIED {0x00, 0x1f, 0x00}

/* 设备的默认类别*/
#ifndef BTA_DM_COD
#define BTA_DM_COD BTA_DM_COD_UNCLASSIFIED
#endif

/* 上合组织链接的数量。*/
#ifndef BTM_MAX_SCO_LINKS
#define BTM_MAX_SCO_LINKS           0	//3
#endif

/* 首选类型的SCO链路（2-eSCO，0-SCO）。*/
#ifndef BTM_DEFAULT_SCO_MODE
#define BTM_DEFAULT_SCO_MODE        2
#endif

/* 对等设备的安全记录数。100 AS默认值*/
#ifndef BTM_SEC_MAX_DEVICE_RECORDS
#if SMP_INCLUDED == TRUE
#define BTM_SEC_MAX_DEVICE_RECORDS  15 // 100
#else
#define BTM_SEC_MAX_DEVICE_RECORDS  8
#endif /* SMP_INCLUDED == TRUE */
#endif

/* 服务的安全记录数。32 AS默认值*/
#ifndef BTM_SEC_MAX_SERVICE_RECORDS
#define BTM_SEC_MAX_SERVICE_RECORDS 8 // 32
#endif

/* 如果为True，则强制检索每个绑定的远程设备名称，以防发生更改*/
#ifndef BTM_SEC_FORCE_RNR_FOR_DBOND
#define BTM_SEC_FORCE_RNR_FOR_DBOND  FALSE
#endif

/* btm数据库中使用的最大设备名称长度。最高248*/
#ifndef BTM_MAX_REM_BD_NAME_LEN
#define BTM_MAX_REM_BD_NAME_LEN     64
#endif

/* btm数据库存储的最大本地设备名称长度。'“0”禁用BTM中本地名称的存储*/
#ifndef BTM_MAX_LOC_BD_NAME_LEN
#define BTM_MAX_LOC_BD_NAME_LEN     64
#endif

/* 固定默认字符串。如果将其定义为空字符串，则设备的产品型号名称将用作默认本地名称。
 */
#ifndef BTM_DEF_LOCAL_NAME
#define BTM_DEF_LOCAL_NAME      ""
#endif

/* 使用安全授权存储的最大服务名称（如果不需要，则为0）*/
#ifndef BTM_SEC_SERVICE_NAME_LEN
#define BTM_SEC_SERVICE_NAME_LEN    BT_MAX_SERVICE_NAME_LEN
#endif

/* 服务名称的最大长度。*/
#ifndef BT_MAX_SERVICE_NAME_LEN
#define BT_MAX_SERVICE_NAME_LEN     21
#endif

/* HCI主机缓冲区大小命令中的ACL缓冲区大小。*/
#ifndef BTM_ACL_BUF_SIZE
#define BTM_ACL_BUF_SIZE            0
#endif

/* 可以向电源管理器注册的最大客户端数。*/
#ifndef BTM_MAX_PM_RECORDS
#define BTM_MAX_PM_RECORDS          2
#endif

/* 此设置用于显示电源管理器的调试跟踪消息。*/
#ifndef BTM_PM_DEBUG
#define BTM_PM_DEBUG                FALSE
#endif

/* 如果由于BTM_CreateSCO API而取消标记链接，则此值设置为TRUE。*/
#ifndef BTM_SCO_WAKE_PARKED_LINK
#define BTM_SCO_WAKE_PARKED_LINK    FALSE
#endif

/* 如果用户在这几秒内没有响应安全进程请求，则会自动发送否定响应。30是LMP响应超时值*/
#ifndef BTM_SEC_TIMEOUT_VALUE
#define BTM_SEC_TIMEOUT_VALUE           35
#endif

/* 可以使用BTM_RegisterForVSEvents注册的最大回调数*/
#ifndef BTM_MAX_VSE_CALLBACKS
#define BTM_MAX_VSE_CALLBACKS           3
#endif

/******************************************
**    里斯本特色
*******************************************/
/* 如果EIR分组需要FEC，则设置为TRUE。*/
#ifndef BTM_EIR_DEFAULT_FEC_REQUIRED
#define BTM_EIR_DEFAULT_FEC_REQUIRED    TRUE
#endif

/* 本地设备的IO能力（用于简单配对）*/
#ifndef BTM_LOCAL_IO_CAPS
#define BTM_LOCAL_IO_CAPS               BTM_IO_CAP_NONE
#endif

#ifndef BTM_LOCAL_IO_CAPS_BLE
#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
#define BTM_LOCAL_IO_CAPS_BLE           BTM_IO_CAP_KBDISP
#else
#define BTM_LOCAL_IO_CAPS_BLE           4
#endif  ///BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
#endif

/* 默认MITM保护要求（用于简单配对）可能值为BTM_AUTH_SP_YES或BTM_AUTH_SP_NO*/
#ifndef BTM_DEFAULT_AUTH_REQ
#define BTM_DEFAULT_AUTH_REQ            BTM_AUTH_SP_NO
#endif

/* 使用简单配对的专用绑定的默认MITM保护要求可能值为BTM_AUTH_AP_YES或BTM_AUTH_AP_NO*/
#ifndef BTM_DEFAULT_DD_AUTH_REQ
#define BTM_DEFAULT_DD_AUTH_REQ            BTM_AUTH_AP_YES
#endif

/* 包括简单配对的带外实现*/
#ifndef BTM_OOB_INCLUDED
#define BTM_OOB_INCLUDED                TRUE
#endif

/* TRUE包含嗅探子速率*/
#if (BTA_DM_PM_INCLUDED == TRUE)
#ifndef BTM_SSR_INCLUDED
#define BTM_SSR_INCLUDED                FALSE
#endif
#endif /* BTA_DM_PM_INCLUDED */

/*************************
** 里斯本结束特色
**************************/

/* 4.1/4.2安全连接功能*/
#ifndef SC_MODE_INCLUDED
// 为BT Classic禁用AES-CCM（BT 4.1）以解决控制器AES问题。将使用E0加密（BT 4.0）。
#define SC_MODE_INCLUDED                FALSE
#endif

/* 仅用于一致性测试*/
#ifndef BTM_BLE_CONFORMANCE_TESTING
#define BTM_BLE_CONFORMANCE_TESTING           FALSE
#endif

/******************************************************************************
** CONTROLLER TO HOST FLOW CONTROL
**
******************************************************************************/

#define C2H_FLOW_CONTROL_INCLUDED TRUE

/******************************************************************************
** L2CAP
**
******************************************************************************/

#ifndef L2CAP_CLIENT_INCLUDED
#define L2CAP_CLIENT_INCLUDED FALSE
#endif

/* 可以向LE L2CAP注册的最大同时应用程序数。*/
#ifndef BLE_MAX_L2CAP_CLIENTS
#define BLE_MAX_L2CAP_CLIENTS           15
#endif


/* L2CAP可以支持的最大同时链接数。最多7个*/
#ifndef MAX_ACL_CONNECTIONS
#define MAX_L2CAP_LINKS             5
#else
#define MAX_L2CAP_LINKS             MAX_ACL_CONNECTIONS
#endif

/* L2CAP可以支持的最大同时通道数。最多16个*/
#ifndef MAX_L2CAP_CHANNELS
#if (CLASSIC_BT_INCLUDED == TRUE)
#define MAX_L2CAP_CHANNELS          16
#else
#if (SMP_INCLUDED == FALSE)
#define MAX_L2CAP_CHANNELS          MAX_ACL_CONNECTIONS  //当开始与对等设备连接时，在BLE客户端中使用
#else
#define MAX_L2CAP_CHANNELS          (MAX_ACL_CONNECTIONS * 2)  //当开始与对等设备连接时，在BLE客户端和SMP中使用
#endif   ///SMP_INCLUDED == FALSE
#endif   ///CLASSIC_BT_INCLUDED == TRUE
#endif   ///MAX_L2CAP_CHANNELS

/* 可以向L2CAP注册的最大同时应用程序数。*/
#ifndef MAX_L2CAP_CLIENTS
#if (CLASSIC_BT_INCLUDED == TRUE)
#define MAX_L2CAP_CLIENTS           8
#else
#define MAX_L2CAP_CLIENTS           1  //不支持在仅BLE模式下分配信道控制块
#endif  ///CLASSIC_BT_INCLUDED == TRUE
#endif

/* 断开链接之前链接不活动的秒数。*/
#ifndef L2CAP_LINK_INACTIVITY_TOUT
#define L2CAP_LINK_INACTIVITY_TOUT  4
#endif

/* 链接断开之前绑定后链接不活动的秒数。*/
#ifndef L2CAP_BONDING_TIMEOUT
#define L2CAP_BONDING_TIMEOUT       3
#endif

/* 如果没有建立通道，从HCI连接完成到断开连接的时间。*/
#ifndef L2CAP_LINK_STARTUP_TOUT
#define L2CAP_LINK_STARTUP_TOUT     60
#endif

/* L2CAP MTU；必须符合HCI ACL池大小。*/
#ifndef L2CAP_MTU_SIZE
#define L2CAP_MTU_SIZE              1691
#endif

/* 蓝牙L2CAP MPS；必须符合FCR tx池大小和ACL下行缓冲区大小。*/
#ifndef L2CAP_MPS_OVER_BR_EDR
#define L2CAP_MPS_OVER_BR_EDR       1010
#endif

/* 如果启用了主机流控制，则这是控制器可能未确认的缓冲区数。*/
#ifndef L2CAP_HOST_FC_ACL_BUFS
#define L2CAP_HOST_FC_ACL_BUFS      20
#endif

/* 此设置用于在发送ACL数据时使L2CAP使ACL链路脱离驻留模式。*/
#ifndef L2CAP_WAKE_PARKED_LINK
#define L2CAP_WAKE_PARKED_LINK      TRUE
#endif

/* 链接是想成为主还是从。*/
#ifndef L2CAP_DESIRED_LINK_ROLE
#define L2CAP_DESIRED_LINK_ROLE     HCI_ROLE_SLAVE
#endif

/* 包括里斯本的不可清洗包边界标志功能*/
#ifndef L2CAP_NON_FLUSHABLE_PB_INCLUDED
#define L2CAP_NON_FLUSHABLE_PB_INCLUDED     TRUE
#endif

/* 高优先级链路的ACL信用的最小数量*/
#ifndef L2CAP_HIGH_PRI_MIN_XMIT_QUOTA
#define L2CAP_HIGH_PRI_MIN_XMIT_QUOTA       5
#endif

/* 用于监控HCI ACL信用管理*/
#ifndef L2CAP_HCI_FLOW_CONTROL_DEBUG
#define L2CAP_HCI_FLOW_CONTROL_DEBUG        TRUE
#endif

/* 用于计算传输缓冲区*/
#ifndef L2CAP_NUM_XMIT_BUFFS
#define L2CAP_NUM_XMIT_BUFFS                HCI_ACL_BUF_MAX
#endif

/* 单播无连接数据*/
#ifndef L2CAP_UCD_INCLUDED
#define L2CAP_UCD_INCLUDED                  FALSE
#endif

/* 单播无连接数据MTU*/
#ifndef L2CAP_UCD_MTU
#define L2CAP_UCD_MTU                       L2CAP_MTU_SIZE
#endif

/* 单播无连接数据空闲超时*/
#ifndef L2CAP_UCD_IDLE_TIMEOUT
#define L2CAP_UCD_IDLE_TIMEOUT              2
#endif

/* 单播无连接数据空闲超时*/
#ifndef L2CAP_UCD_CH_PRIORITY
#define L2CAP_UCD_CH_PRIORITY               L2CAP_CHNL_PRIORITY_MEDIUM
#endif

/* 用于使用固定通道的功能；如果不支持固定通道（BLE等），则设置为零*/
/* 不包括L2CAP信令信道和UCD*/
#ifndef L2CAP_NUM_FIXED_CHNLS
#if (CLASSIC_BT_INCLUDED == TRUE)
#define L2CAP_NUM_FIXED_CHNLS               32
#else
#define L2CAP_NUM_FIXED_CHNLS               3   //仅BLE模式下只有三个固定通道（gatt、signal、smp）
#endif  ///CLASSIC_BT_INCLUDED == TRUE
#endif

/* 支持第一个固定通道*/
#ifndef L2CAP_FIRST_FIXED_CHNL
#define L2CAP_FIRST_FIXED_CHNL              4
#endif

#ifndef L2CAP_LAST_FIXED_CHNL
#define L2CAP_LAST_FIXED_CHNL           (L2CAP_FIRST_FIXED_CHNL + L2CAP_NUM_FIXED_CHNLS - 1)
#endif

/* 链路中的循环服务信道*/
#ifndef L2CAP_ROUND_ROBIN_CHANNEL_SERVICE
#define L2CAP_ROUND_ROBIN_CHANNEL_SERVICE   TRUE
#endif

/* 用于计算传输缓冲区*/
#ifndef L2CAP_NUM_XMIT_BUFFS
#define L2CAP_NUM_XMIT_BUFFS                HCI_ACL_BUF_MAX
#endif

/* 用于监视eL2CAP数据流*/
#ifndef L2CAP_ERTM_STATS
#define L2CAP_ERTM_STATS                    FALSE
#endif

/* 仅用于一致性测试：当TRUE允许scriptwrapper覆盖信息响应*/
#ifndef L2CAP_CONFORMANCE_TESTING
#define L2CAP_CONFORMANCE_TESTING           FALSE
#endif

/*
 * 如果本地客户端未接收到连接，则在断开连接之前，每个连接到本地缓冲区的最大字节数-默认值为1MB
 */
#ifndef L2CAP_MAX_RX_BUFFER
#define L2CAP_MAX_RX_BUFFER                 0x100000
#endif


#ifndef TIMER_PARAM_TYPE
#define TIMER_PARAM_TYPE    UINT32
#endif

/******************************************************************************
** BLE
**
******************************************************************************/

#ifndef BLE_INCLUDED
#define BLE_INCLUDED            FALSE
#endif

#ifndef BLE_ANDROID_CONTROLLER_SCAN_FILTER
#define BLE_ANDROID_CONTROLLER_SCAN_FILTER            TRUE
#endif

#ifndef LOCAL_BLE_CONTROLLER_ID
#define LOCAL_BLE_CONTROLLER_ID         (1)
#endif

/*
 * 切换对一般LE隐私功能的支持，如远程地址解析、本地地址轮换等。
 */
#ifndef BLE_PRIVACY_SPT
#define BLE_PRIVACY_SPT         FALSE
#endif

/*
 * 启用或禁用对本地隐私的支持（例如地址轮换）
 */
#ifndef BLE_LOCAL_PRIVACY_ENABLED
#define BLE_LOCAL_PRIVACY_ENABLED         TRUE
#endif

/*
 * 切换对供应商特定扩展的支持，如RPA卸载、功能发现、多adv等。
 */
#ifndef BLE_VND_INCLUDED
#define BLE_VND_INCLUDED        FALSE
#endif

#ifndef BTM_BLE_ADV_TX_POWER
#define BTM_BLE_ADV_TX_POWER {-12, -9, -6, -3, 0, 3, 6, 9}
#endif

#ifndef BTM_TX_POWER
#define BTM_TX_POWER {-12, -9, -6, -3, 0, 3, 6, 9}
#endif

#ifndef BTM_TX_POWER_LEVEL_MAX
#define BTM_TX_POWER_LEVEL_MAX 7
#endif


#ifndef BLE_BATCH_SCAN_INCLUDED
#define BLE_BATCH_SCAN_INCLUDED  TRUE
#endif

/******************************************************************************
** ATT/GTT协议/配置文件设置
**
******************************************************************************/
#ifndef GATT_INCLUDED
#if BLE_INCLUDED == TRUE
#define GATT_INCLUDED TRUE
#else
#define GATT_INCLUDED FALSE
#endif
#endif

#ifndef BTA_GATT_INCLUDED
#if BLE_INCLUDED == TRUE
#define BTA_GATT_INCLUDED TRUE
#else
#define BTA_GATT_INCLUDED FALSE
#endif
#endif

#if BTA_GATT_INCLUDED == TRUE && BLE_INCLUDED == FALSE
#error "can't have GATT without BLE"
#endif

#ifndef BLE_LLT_INCLUDED
#define BLE_LLT_INCLUDED    TRUE
#endif

/* 添加此marco以修复android 7.0将导致更新连接参数冲突，当从设备向控制器发送HCI_BLE_UPD_LL_CONN_PARAMS注释时，请求主设备直接更新连接参数。*/
#ifndef BLE_SLAVE_UPD_CONN_PARAMS
#define BLE_SLAVE_UPD_CONN_PARAMS FALSE
#endif

#ifndef ATT_INCLUDED
#define ATT_INCLUDED         TRUE
#endif

#ifndef ATT_DEBUG
#define ATT_DEBUG           FALSE
#endif

#ifndef BLE_PERIPHERAL_MODE_SUPPORT
#define BLE_PERIPHERAL_MODE_SUPPORT  TRUE
#endif

#ifndef BLE_DELAY_REQUEST_ENC
/* 此标志用于解决IPHONE问题，我们需要等待IPHONE准备就绪后再向IPHONE发送加密请求*/
#define BLE_DELAY_REQUEST_ENC        FALSE
#endif

#ifndef GAP_TRANSPORT_SUPPORTED
#define GAP_TRANSPORT_SUPPORTED      GATT_TRANSPORT_LE_BR_EDR
#endif

#ifndef GATTP_TRANSPORT_SUPPORTED
#define GATTP_TRANSPORT_SUPPORTED    GATT_TRANSPORT_LE_BR_EDR
#endif

#ifndef GATT_MAX_SR_PROFILES
#define GATT_MAX_SR_PROFILES        UC_CONFIG_BT_GATT_MAX_SR_PROFILES
#endif

#ifndef GATT_MAX_APPS
#define GATT_MAX_APPS            8 /* MAX是32注：GATT和GAP内部使用了2个应用程序*/
#endif

#ifndef GATT_MAX_PHY_CHANNEL
#define GATT_MAX_PHY_CHANNEL        7
#endif

/* 仅用于一致性测试*/
#ifndef GATT_CONFORMANCE_TESTING
#define GATT_CONFORMANCE_TESTING           FALSE
#endif

/* 背景连接设备允许数量，理想情况下与WL大小相同
*/
#ifndef GATT_MAX_BG_CONN_DEV
#define GATT_MAX_BG_CONN_DEV        8 /*最大值为32*/
#endif

/******************************************************************************
** GATT
**
******************************************************************************/
#ifndef GATTC_INCLUDED
#if BLE_INCLUDED == TRUE
#define GATTC_INCLUDED         FALSE
#else
#define GATTC_INCLUDED         FALSE
#endif
#endif

#ifndef GATTS_INCLUDED
#if BLE_INCLUDED == TRUE
#define GATTS_INCLUDED         TRUE
#else
#define GATTS_INCLUDED         FALSE
#endif
#endif

/******************************************************************************
** SMP
**
******************************************************************************/
#ifndef SMP_INCLUDED
#if BLE_INCLUDED == TRUE
#define SMP_INCLUDED         FALSE
#else
#define SMP_INCLUDED         FALSE
#endif
#endif

#ifndef SMP_DEBUG
#define SMP_DEBUG            FALSE
#endif

#ifndef SMP_DEFAULT_AUTH_REQ
#define SMP_DEFAULT_AUTH_REQ    SMP_AUTH_NB_ENC_ONLY
#endif

#ifndef SMP_MAX_ENC_KEY_SIZE
#define SMP_MAX_ENC_KEY_SIZE    16
#endif

#ifndef SMP_MIN_ENC_KEY_SIZE
#define SMP_MIN_ENC_KEY_SIZE    7
#endif

/* SMP配对完成后的最小链路超时，为以下服务连接留出密钥交换和竞速条件的空间。首选大于0秒，且不小于L2CAP中的默认非活动链路空闲计时器（L2CAP_link_inactivity_TOUT）*/
#ifndef SMP_LINK_TOUT_MIN
#if (L2CAP_LINK_INACTIVITY_TOUT > 0)
#define SMP_LINK_TOUT_MIN               L2CAP_LINK_INACTIVITY_TOUT
#else
#define SMP_LINK_TOUT_MIN               2
#endif
#endif

/******************************************************************************
** BT_SSP
**
******************************************************************************/
#ifndef BT_SSP_INCLUDED
#define BT_SSP_INCLUDED         FALSE
#endif

#if BT_SSP_INCLUDED == TRUE && CLASSIC_BT_INCLUDED == FALSE
#error "Can't have SSP without CLASSIC BT"
#endif

/******************************************************************************
** SDP
**
******************************************************************************/

#ifndef SDP_INCLUDED
#define SDP_INCLUDED                FALSE
#endif

/* 此设置用于启用SDP服务器功能。*/
#ifndef SDP_SERVER_ENABLED
#if SDP_INCLUDED == TRUE
#define SDP_SERVER_ENABLED          TRUE
#else
#define SDP_SERVER_ENABLED          FALSE
#endif
#endif

/* 这设置为启用SDP客户端功能。*/
#ifndef SDP_CLIENT_ENABLED
#if SDP_INCLUDED == TRUE
#define SDP_CLIENT_ENABLED          TRUE
#else
#define SDP_CLIENT_ENABLED          FALSE
#endif
#endif

/* 服务器可以支持的最大SDP记录数。*/
#ifndef SDP_MAX_RECORDS
#define SDP_MAX_RECORDS             6  /*最大值为30*/
#endif

/* 每个记录中的最大属性数。*/
#ifndef SDP_MAX_REC_ATTR
#if defined(HID_DEV_INCLUDED) && (HID_DEV_INCLUDED==TRUE)
#define SDP_MAX_REC_ATTR            25
#else
#define SDP_MAX_REC_ATTR            8
#endif /* 已定义（HID_DEV_INCLUDED）&&（HID_DEV-INCLUDED==TRUE）*/
#endif

#ifndef SDP_MAX_PAD_LEN
#define SDP_MAX_PAD_LEN             300
#endif

/* 属性的最大长度（字节）。*/
#ifndef SDP_MAX_ATTR_LEN
#define SDP_MAX_ATTR_LEN            400
#endif

/* SDP数据库支持的最大属性筛选器数。*/
#ifndef SDP_MAX_ATTR_FILTERS
#define SDP_MAX_ATTR_FILTERS        15
#endif

/* SDP数据库支持的UUID筛选器的最大数量。*/
#ifndef SDP_MAX_UUID_FILTERS
#define SDP_MAX_UUID_FILTERS        3
#endif

/* 搜索中检索的记录句柄的最大数量。*/
#ifndef SDP_MAX_DISC_SERVER_RECS
#define SDP_MAX_DISC_SERVER_RECS    21
#endif

/* 草稿行缓冲区的大小，以字节为单位，用于存储对属性请求的响应。*/
#ifndef SDP_MAX_LIST_BYTE_COUNT
#define SDP_MAX_LIST_BYTE_COUNT     4096
#endif

/* SDP协议元素中的最大参数数。*/
#ifndef SDP_MAX_PROTOCOL_PARAMS
#define SDP_MAX_PROTOCOL_PARAMS     2
#endif

/* 同时连接客户端和服务器的最大数量。*/
#ifndef SDP_MAX_CONNECTIONS
#define SDP_MAX_CONNECTIONS         2 // 4
#endif

/* L2CAP配置的MTU大小。*/
#ifndef SDP_MTU_SIZE
#define SDP_MTU_SIZE                672
#endif

/* L2CAP配置的刷新超时。*/
#ifndef SDP_FLUSH_TO
#define SDP_FLUSH_TO                0xFFFF
#endif

/* 安全授权的名称。*/
#ifndef SDP_SERVICE_NAME
#define SDP_SERVICE_NAME            "Service Discovery"
#endif

/* BTM的安全级别。*/
#ifndef SDP_SECURITY_LEVEL
#define SDP_SECURITY_LEVEL          BTM_SEC_NONE
#endif

/******************************************************************************
** RFCOMM
**
******************************************************************************/
#ifndef RFCOMM_INCLUDED
#define RFCOMM_INCLUDED             FALSE
#endif

/* 支持的最大端口数。*/
#ifndef MAX_RFC_PORTS
#define MAX_RFC_PORTS               8 /*最大值为30*/
#endif

/* 到不同设备的最大同时链接。*/
#ifndef MAX_ACL_CONNECTIONS
#define MAX_BD_CONNECTIONS          3 /*最大值为7*/
#else
#define MAX_BD_CONNECTIONS          MAX_ACL_CONNECTIONS
#endif

/* 端口接收队列低水位线级别（以字节为单位）。*/
#ifndef PORT_RX_LOW_WM
#define PORT_RX_LOW_WM              (BTA_RFC_MTU_SIZE * PORT_RX_BUF_LOW_WM)
#endif

/* 端口接收队列高水位线级别（以字节为单位）。*/
#ifndef PORT_RX_HIGH_WM
#define PORT_RX_HIGH_WM             (BTA_RFC_MTU_SIZE * PORT_RX_BUF_HIGH_WM)
#endif

/* 端口接收队列关键水印级别，以字节为单位。*/
#ifndef PORT_RX_CRITICAL_WM
#define PORT_RX_CRITICAL_WM         (BTA_RFC_MTU_SIZE * PORT_RX_BUF_CRITICAL_WM)
#endif

/* 端口接收队列的低水位线（以缓冲区数计）。*/
#ifndef PORT_RX_BUF_LOW_WM
#define PORT_RX_BUF_LOW_WM          4
#endif

/* 端口接收队列的高水位线（以缓冲区数计）。*/
#ifndef PORT_RX_BUF_HIGH_WM
#define PORT_RX_BUF_HIGH_WM         10
#endif

/* 端口接收队列关键水印级别，以缓冲区数表示。*/
#ifndef PORT_RX_BUF_CRITICAL_WM
#define PORT_RX_BUF_CRITICAL_WM     15
#endif

/* 端口传输队列高水位线级别，以字节为单位。*/
#ifndef PORT_TX_HIGH_WM
#define PORT_TX_HIGH_WM             (BTA_RFC_MTU_SIZE * PORT_TX_BUF_HIGH_WM)
#endif

/* 端口传输队列关键水印级别，以字节为单位。*/
#ifndef PORT_TX_CRITICAL_WM
#define PORT_TX_CRITICAL_WM         (BTA_RFC_MTU_SIZE * PORT_TX_BUF_CRITICAL_WM)
#endif

/* 端口传输队列的高水位线，以缓冲区的数量表示。*/
#ifndef PORT_TX_BUF_HIGH_WM
#define PORT_TX_BUF_HIGH_WM         10
#endif

/* 端口传输队列的高水位线，以缓冲区的数量表示。*/
#ifndef PORT_TX_BUF_CRITICAL_WM
#define PORT_TX_BUF_CRITICAL_WM     15
#endif

/* RFCOMM多路复用器首选流控制机制。*/
#ifndef PORT_FC_DEFAULT
#define PORT_FC_DEFAULT             PORT_FC_CREDIT
#endif

/* 当使用基于信用的流量控制时，接收方向对等方发送的信用的最大数量。*/
#ifndef PORT_CREDIT_RX_MAX
#define PORT_CREDIT_RX_MAX          16
#endif

/* 信用低水位线。*/
#ifndef PORT_CREDIT_RX_LOW
#define PORT_CREDIT_RX_LOW          8
#endif

/******************************************************************************
** OBEX
**
******************************************************************************/

/*
 * 重新组装SDU的缓冲区大小。它将允许使用大于L2CAP_MAX_MTU的缓冲区。
 */
#ifndef OBX_USER_RX_BUF_SIZE
#define OBX_USER_RX_BUF_SIZE    OBX_LRG_DATA_BUF_SIZE
#endif

/*
 * 保存SDU的缓冲区大小。它将允许使用大于L2CAP_MAX_MTU的缓冲区。
 */
#ifndef OBX_USER_TX_BUF_SIZE
#define OBX_USER_TX_BUF_SIZE    OBX_LRG_DATA_BUF_SIZE
#endif

/* 用于在SDU重新组装期间保持MPS段的缓冲区大小。*/
#ifndef OBX_FCR_RX_BUF_SIZE
#define OBX_FCR_RX_BUF_SIZE     BT_DEFAULT_BUFFER_SIZE
#endif

/*
 * 用于保存（重新）传输中使用的MPS段的缓冲区大小。每个缓冲区的大小必须能够容纳L2CA_SetFCROptions加上BT_HDR（8）+HCI前导码（4）+L2CAP_MIN_OFFSET（11-根据BT 2.1+EDR规范）中传递的最大MPS段大小。
 */
#ifndef OBX_FCR_TX_BUF_SIZE
#define OBX_FCR_TX_BUF_SIZE     BT_DEFAULT_BUFFER_SIZE
#endif

/* 当OBX_14_INCLUDED=使用增强重传模式时传输窗口的TRUESize时，此选项适用。不用于基本模式和流模式。范围：1-63
*/
#ifndef OBX_FCR_OPT_TX_WINDOW_SIZE_BR_EDR
#define OBX_FCR_OPT_TX_WINDOW_SIZE_BR_EDR       20
#endif

/* 当OBX_14_INCLUDED=断开连接前单个I帧的传输尝试的TRUENumber时，此选项适用。仅在ERTM模式下使用。在基本模式和流模式中忽略值。范围：0，1-0xFF0-无限重传1-单次传输
*/
#ifndef OBX_FCR_OPT_MAX_TX_B4_DISCNT
#define OBX_FCR_OPT_MAX_TX_B4_DISCNT    20
#endif

/* 当OBX_14_INCLUDED=TRUERetransmission TimeoutRange：支持PBF时，BR/EDR上的最小值为2000（2秒）时，此选项适用。
 */
#ifndef OBX_FCR_OPT_RETX_TOUT
#define OBX_FCR_OPT_RETX_TOUT           2000
#endif

/* 当OBX_14_INCLUDE=TRUEMonitor TimeoutRange：支持PBF时，BR/EDR上的最小值为12000（12秒）时，此选项适用。
*/
#ifndef OBX_FCR_OPT_MONITOR_TOUT
#define OBX_FCR_OPT_MONITOR_TOUT        12000
#endif

/* 当OBX_14_INCLUDED=TRUEM最大PDU有效负载大小时，此选项适用。建议：适合3-DH5数据包的最大数据量。范围：2个八位字节
*/
#ifndef OBX_FCR_OPT_MAX_PDU_SIZE
#define OBX_FCR_OPT_MAX_PDU_SIZE        L2CAP_MPS_OVER_BR_EDR
#endif


/******************************************************************************
** BNEP
**
******************************************************************************/

#ifndef BNEP_INCLUDED
#define BNEP_INCLUDED               FALSE
#endif

/* BNEP状态API调用主要用于获取L2CAP句柄*/
#ifndef BNEP_SUPPORTS_STATUS_API
#define BNEP_SUPPORTS_STATUS_API            FALSE
#endif

/*
** 当BNEP连接在连接建立后更改角色时，我们将再次对新角色进行身份验证检查
*/
#ifndef BNEP_DO_AUTH_FOR_ROLE_SWITCH
#define BNEP_DO_AUTH_FOR_ROLE_SWITCH        FALSE
#endif


/* 支持的最大协议筛选器数。*/
#ifndef BNEP_MAX_PROT_FILTERS
#define BNEP_MAX_PROT_FILTERS       5
#endif

/* 支持的最大多播筛选器数。*/
#ifndef BNEP_MAX_MULTI_FILTERS
#define BNEP_MAX_MULTI_FILTERS      5
#endif

/* 最小MTU尺寸。*/
#ifndef BNEP_MIN_MTU_SIZE
#define BNEP_MIN_MTU_SIZE           L2CAP_MTU_SIZE
#endif

/* 首选MTU尺寸。*/
#ifndef BNEP_MTU_SIZE
#define BNEP_MTU_SIZE               BNEP_MIN_MTU_SIZE
#endif

/* 传输数据队列中允许的最大缓冲区数。*/
#ifndef BNEP_MAX_XMITQ_DEPTH
#define BNEP_MAX_XMITQ_DEPTH        20
#endif

/* 支持的最大BNEP连接数。*/
#ifndef BNEP_MAX_CONNECTIONS
#define BNEP_MAX_CONNECTIONS        7
#endif


/******************************************************************************
** AVDTP
**
******************************************************************************/

#ifndef AVDT_INCLUDED
#define AVDT_INCLUDED               TRUE
#endif

/* 在AVDTP中包含报告功能*/
#ifndef AVDT_REPORTING
#define AVDT_REPORTING              TRUE
#endif

/* 在AVDTP中包含多路复用功能*/
#ifndef AVDT_MULTIPLEXING
#define AVDT_MULTIPLEXING           TRUE
#endif

/* 到不同对等设备的同时链接数。*/
#ifndef AVDT_NUM_LINKS
#define AVDT_NUM_LINKS              2
#endif

/* 同时流终结点的数量。*/
#ifndef AVDT_NUM_SEPS
#define AVDT_NUM_SEPS               3
#endif

/* 每个媒体流（音频或视频）设置的传输频道数*/
#ifndef AVDT_NUM_CHANNELS

#if AVDT_REPORTING == TRUE
/* 信号、媒体和报告渠道*/
#define AVDT_NUM_CHANNELS   3
#else
/* 信令和媒体频道*/
#define AVDT_NUM_CHANNELS   2
#endif  // AVDT_REPORTING

#endif  // AVDT_NUM_CHANNELS

/* AVDT为所有媒体流设置的传输信道数AVDT_NUM_channels同时流的数量。
 */
#ifndef AVDT_NUM_TC_TBL
#define AVDT_NUM_TC_TBL             6
#endif

/* 编解码器功能信息元素的最大字节大小。*/
#ifndef AVDT_CODEC_SIZE
#define AVDT_CODEC_SIZE             10
#endif

/* 内容保护信息元素的最大大小（字节）。*/
#ifndef AVDT_PROTECT_SIZE
#define AVDT_PROTECT_SIZE           90
#endif

/* 片段队列中GKI缓冲区的最大数量（用于视频帧）。必须小于大小为AVDT_DATA_pool_size的缓冲池中的缓冲区数*/
#ifndef AVDT_MAX_FRAG_COUNT
#define AVDT_MAX_FRAG_COUNT         15
#endif

/******************************************************************************
** PAN
**
******************************************************************************/

#ifndef PAN_INCLUDED
#define PAN_INCLUDED                     FALSE
#endif

/* 这将启用PANU角色*/
#ifndef PAN_SUPPORTS_ROLE_PANU
#define PAN_SUPPORTS_ROLE_PANU              FALSE
#endif

/* 这将启用GN角色*/
#ifndef PAN_SUPPORTS_ROLE_GN
#define PAN_SUPPORTS_ROLE_GN                FALSE
#endif

/* 这将启用NAP角色*/
#ifndef PAN_SUPPORTS_ROLE_NAP
#define PAN_SUPPORTS_ROLE_NAP               FALSE
#endif

/* 这只是为了调试目的*/
#ifndef PAN_SUPPORTS_DEBUG_DUMP
#define PAN_SUPPORTS_DEBUG_DUMP             FALSE
#endif

/* 允许的最大PAN连接数*/
#ifndef MAX_PAN_CONNS
#define MAX_PAN_CONNS                    7
#endif

/* NAP角色的默认服务名称*/
#ifndef PAN_NAP_DEFAULT_SERVICE_NAME
#define PAN_NAP_DEFAULT_SERVICE_NAME    "Network Access Point Service"
#endif

/* GN角色的默认服务名称*/
#ifndef PAN_GN_DEFAULT_SERVICE_NAME
#define PAN_GN_DEFAULT_SERVICE_NAME     "Group Network Service"
#endif

/* PANU角色的默认服务名称*/
#ifndef PAN_PANU_DEFAULT_SERVICE_NAME
#define PAN_PANU_DEFAULT_SERVICE_NAME   "PAN User Service"
#endif

/* NAP角色服务的默认描述*/
#ifndef PAN_NAP_DEFAULT_DESCRIPTION
#define PAN_NAP_DEFAULT_DESCRIPTION     "NAP"
#endif

/* GN角色服务的默认描述*/
#ifndef PAN_GN_DEFAULT_DESCRIPTION
#define PAN_GN_DEFAULT_DESCRIPTION      "GN"
#endif

/* PANU角色服务的默认描述*/
#ifndef PAN_PANU_DEFAULT_DESCRIPTION
#define PAN_PANU_DEFAULT_DESCRIPTION    "PANU"
#endif

/* PANU角色的默认安全级别。*/
#ifndef PAN_PANU_SECURITY_LEVEL
#define PAN_PANU_SECURITY_LEVEL          0
#endif

/* GN角色的默认安全级别。*/
#ifndef PAN_GN_SECURITY_LEVEL
#define PAN_GN_SECURITY_LEVEL            0
#endif

/* NAP角色的默认安全级别。*/
#ifndef PAN_NAP_SECURITY_LEVEL
#define PAN_NAP_SECURITY_LEVEL           0
#endif

/******************************************************************************
** GAP
**
******************************************************************************/

#ifndef GAP_INCLUDED
#define GAP_INCLUDED                TRUE
#endif

/* 此设置用于启用数据写入的过帐事件*/
#ifndef GAP_CONN_POST_EVT_INCLUDED
#define GAP_CONN_POST_EVT_INCLUDED  FALSE
#endif

/* 同时GAP L2CAP连接的最大数量。*/
#ifndef GAP_MAX_CONNECTIONS
#define GAP_MAX_CONNECTIONS         10 // 30
#endif

/* 将从SDP服务器接收的原始数据保存在数据库中。*/
#ifndef SDP_RAW_DATA_INCLUDED
#define SDP_RAW_DATA_INCLUDED       TRUE
#endif

/* 查询持续时间为1.28秒。*/
#ifndef SDP_DEBUG
#define SDP_DEBUG                   TRUE
#endif

/******************************************************************************
** HID
**
******************************************************************************/
#ifndef BT_HID_INCLUDED
#define BT_HID_INCLUDED         FALSE
#endif

/* 包括HID设备角色*/
#ifndef HID_DEV_INCLUDED
#define HID_DEV_INCLUDED   FALSE
#endif

#ifndef HID_DEV_SUBCLASS
#define HID_DEV_SUBCLASS   COD_MINOR_POINTING
#endif

#ifndef HID_CONTROL_BUF_SIZE
#define HID_CONTROL_BUF_SIZE            BT_DEFAULT_BUFFER_SIZE
#endif

#ifndef HID_INTERRUPT_BUF_SIZE
#define HID_INTERRUPT_BUF_SIZE          BT_DEFAULT_BUFFER_SIZE
#endif

#ifndef HID_DEV_MTU_SIZE
#define HID_DEV_MTU_SIZE 64
#endif

#ifndef HID_DEV_FLUSH_TO
#define HID_DEV_FLUSH_TO 0xffff
#endif

/*************************************************************************
** HID主机和设备的定义
*/
#ifndef HID_MAX_SVC_NAME_LEN
#define HID_MAX_SVC_NAME_LEN  32
#endif

#ifndef HID_MAX_SVC_DESCR_LEN
#define HID_MAX_SVC_DESCR_LEN 32
#endif

#ifndef HID_MAX_PROV_NAME_LEN
#define HID_MAX_PROV_NAME_LEN 32
#endif

/*************************************************************************
** HID主机的定义
*/
#ifndef  HID_HOST_INCLUDED
#define HID_HOST_INCLUDED           FALSE
#endif

#ifndef HID_HOST_MAX_DEVICES
#define HID_HOST_MAX_DEVICES        7
#endif

#ifndef HID_HOST_MTU
#define HID_HOST_MTU                640
#endif

#ifndef HID_HOST_FLUSH_TO
#define HID_HOST_FLUSH_TO                 0xffff
#endif

#ifndef HID_HOST_MAX_CONN_RETRY
#define HID_HOST_MAX_CONN_RETRY     (3)
#endif

#ifndef HID_HOST_REPAGE_WIN
#define HID_HOST_REPAGE_WIN          (2)
#endif

/*************************************************************************
 * A2DP定义
 */
#ifndef A2D_INCLUDED
#define A2D_INCLUDED            FALSE
#endif

/******************************************************************************
** AVCTP
**
******************************************************************************/

/* 到不同对等设备的同时ACL链接数。*/
#ifndef AVCT_NUM_LINKS
#define AVCT_NUM_LINKS              2
#endif

/* 同时AVCTP连接数。*/
#ifndef AVCT_NUM_CONN
#define AVCT_NUM_CONN               3
#endif

/******************************************************************************
** AVRCP
**
******************************************************************************/
#ifndef AVRC_INCLUDED
#define AVRC_INCLUDED               FALSE
#endif

#ifndef AVRC_METADATA_INCLUDED
#if AVRC_INCLUDED == TRUE
#define AVRC_METADATA_INCLUDED      TRUE
#else
#define AVRC_METADATA_INCLUDED      FALSE
#endif
#endif

#ifndef AVRC_ADV_CTRL_INCLUDED
#if AVRC_INCLUDED == TRUE
#define AVRC_ADV_CTRL_INCLUDED      TRUE
#else
#define AVRC_ADV_CTRL_INCLUDED      FALSE
#endif
#endif

#ifndef AVRC_CTLR_INCLUDED
#if AVRC_INCLUDED == TRUE
#define AVRC_CTLR_INCLUDED          TRUE
#else
#define AVRC_CTLR_INCLUDED          FALSE
#endif
#endif

/******************************************************************************
** MCAP
**
******************************************************************************/
#ifndef MCA_INCLUDED
#define MCA_INCLUDED                FALSE
#endif

/* 控制信道上L2CAP配置的MTU大小。48是最小值*/
#ifndef MCA_CTRL_MTU
#define MCA_CTRL_MTU    60
#endif

/* 已注册的MCAP实例的最大数量。*/
#ifndef MCA_NUM_REGS
#define MCA_NUM_REGS    12
#endif

/* 每个注册的MCAP实例的最大控制信道数（到不同设备）。*/
#ifndef MCA_NUM_LINKS
#define MCA_NUM_LINKS   3
#endif

/* 每个已注册的MCAP实例的MDEP（包括HDP回显）的最大数量。*/
#ifndef MCA_NUM_DEPS
#define MCA_NUM_DEPS    13
#endif

/* 每个控制信道的最大MDL链路数。*/
#ifndef MCA_NUM_MDLS
#define MCA_NUM_MDLS    4
#endif

/* 重新组装SDU的缓冲区大小。*/
#ifndef MCA_USER_RX_BUF_SIZE
#define MCA_USER_RX_BUF_SIZE    BT_DEFAULT_BUFFER_SIZE
#endif

/* 保存SDU的缓冲区大小。*/
#ifndef MCA_USER_TX_BUF_SIZE
#define MCA_USER_TX_BUF_SIZE    BT_DEFAULT_BUFFER_SIZE
#endif

/*
 * SDU重组期间用于容纳MPS段的缓冲区大小
 */
#ifndef MCA_FCR_RX_BUF_SIZE
#define MCA_FCR_RX_BUF_SIZE     BT_DEFAULT_BUFFER_SIZE
#endif

/*
 * 用于保存（重新）传输中使用的MPS段的默认缓冲区大小。每个缓冲区的大小必须能够容纳tL2CAP_FCR_OPTIONS加上BT_HDR（8）+HCI前导码（4）+L2CAP_MIN_OFFSET（11-从BT 2.1+EDR规范开始）中传递的最大MPS段大小。
 */
#ifndef MCA_FCR_TX_BUF_SIZE
#define MCA_FCR_TX_BUF_SIZE     BT_DEFAULT_BUFFER_SIZE
#endif

/* MCAP控制信道FCR选项：使用增强型重传模式时传输窗口的大小。1由控制信道的HDP规范定义。
*/
#ifndef MCA_FCR_OPT_TX_WINDOW_SIZE
#define MCA_FCR_OPT_TX_WINDOW_SIZE      1
#endif

/* MCAP控制信道FCR选项：在断开连接之前，单个I帧的传输尝试次数。仅在ERTM模式下使用。在基本模式和流模式中忽略值。范围：0，1-0xFF0-无限重传1-单次传输
*/
#ifndef MCA_FCR_OPT_MAX_TX_B4_DISCNT
#define MCA_FCR_OPT_MAX_TX_B4_DISCNT    20
#endif

/* MCAP控制信道FCR选项：重传超时AVRCP规范设置了300-2000毫秒超时（以毫秒为单位）范围内的值，以检测丢失的I帧。仅在增强重传模式下使用。范围：支持PBF时最小2000（2秒）。
 */
#ifndef MCA_FCR_OPT_RETX_TOUT
#define MCA_FCR_OPT_RETX_TOUT           2000
#endif

/* MCAP控制信道FCR选项：监视器超时AVRCP规范设置了300-2000毫秒超时（以毫秒为单位）范围内的值，以检测丢失的S帧。仅在增强重传模式下使用。范围：支持PBF时最小12000（12秒）。
*/
#ifndef MCA_FCR_OPT_MONITOR_TOUT
#define MCA_FCR_OPT_MONITOR_TOUT        12000
#endif

/* MCAP控制信道FCR选项：最大PDU负载大小。本地设备可以在单个PDU中接收的最大有效负载八位字节数。
*/
#ifndef MCA_FCR_OPT_MPS_SIZE
#define MCA_FCR_OPT_MPS_SIZE            1000
#endif

/* 共享交通工具*/
#ifndef NFC_SHARED_TRANSPORT_ENABLED
#define NFC_SHARED_TRANSPORT_ENABLED    FALSE
#endif

/******************************************************************************
** 睡眠模式（低功耗模式）
**
******************************************************************************/

#ifndef HCILP_INCLUDED
#define HCILP_INCLUDED                  FALSE
#endif

/******************************************************************************
** APPL-应用程序任务
**
******************************************************************************/

#define L2CAP_FEATURE_REQ_ID      73
#define L2CAP_FEATURE_RSP_ID     173

/******************************************************************************
** BTA
**
******************************************************************************/
/* BTA EIR屏蔽UUID列表（默认为动态）*/
#ifndef BTA_EIR_CANNED_UUID_LIST
#define BTA_EIR_CANNED_UUID_LIST FALSE
#endif

/* EIR中支持的客户UUID数量*/
#ifndef BTA_EIR_SERVER_NUM_CUSTOM_UUID
#define BTA_EIR_SERVER_NUM_CUSTOM_UUID     8
#endif

/* 蓝机器人CHLD超控*/
#ifndef BTA_AG_CHLD_VAL_ECC
#define BTA_AG_CHLD_VAL_ECC  "(0,1,1x,2,2x,3)"
#endif

#ifndef BTA_AG_CHLD_VAL
#define BTA_AG_CHLD_VAL  "(0,1,2,3)"
#endif

/* 设置CIND以匹配HFP 1.5*/
#ifndef BTA_AG_CIND_INFO
#define BTA_AG_CIND_INFO "(\"call\",(0,1)),(\"callsetup\",(0-3)),(\"service\",(0-1)),(\"signal\",(0-5)),(\"roam\",(0,1)),(\"battchg\",(0-5)),(\"callheld\",(0-2))"
#endif

#ifndef BTA_DM_AVOID_A2DP_ROLESWITCH_ON_INQUIRY
#define BTA_DM_AVOID_A2DP_ROLESWITCH_ON_INQUIRY FALSE
#endif

/******************************************************************************
** 跟踪：在此处包含跟踪头文件。
**
******************************************************************************/

/* 启用/禁用BTSnoop内存记录*/
#ifndef BTSNOOP_MEM
#define BTSNOOP_MEM FALSE
#endif

#if UC_BT_BLUEDROID_MEM_DEBUG
#define HEAP_MEMORY_DEBUG   TRUE
#else
#define HEAP_MEMORY_DEBUG   FALSE
#endif

#if UC_HEAP_ALLOCATION_FROM_SPIRAM_FIRST
#define HEAP_ALLOCATION_FROM_SPIRAM_FIRST TRUE
#else
#define HEAP_ALLOCATION_FROM_SPIRAM_FIRST FALSE
#endif

#include "common/bt_trace.h"

#endif /* BT_TARGET_H */

