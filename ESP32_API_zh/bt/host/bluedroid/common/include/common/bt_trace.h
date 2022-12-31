/******************************************************************************
 * 版权所有（C）1999-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _BT_TRACE_H_
#define _BT_TRACE_H_

#include <assert.h>
#include <stdio.h>
#include "bluedroid_user_config.h"
#include "stack/bt_types.h"
#include "bt_common.h"

static inline void trc_dump_buffer(const char *prefix, uint8_t *data, uint16_t len)
{
    uint16_t i;

    if (!data || !len) {
        return;
    }

    if (prefix) {
        printf("%s: len %d\r\n", prefix, len);
    }

    for (i = 0; i < len; i+=16) {
        printf("%02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x\r\n",
                *(data + i), *(data + i + 1), *(data + i + 2), *(data + i + 3), *(data + i + 4), *(data + i + 5), *(data + i + 6), *(data + i + 7),
                *(data + i + 8), *(data + i + 9), *(data + i + 10), *(data + i + 11), *(data + i + 12), *(data + i + 13), *(data + i + 14), *(data + i + 15));
    }
    printf("\r\n");
}

#ifdef BTTRC_DUMP_BUFFER
#define BTTRC_DUMP_BUFFER(_prefix, _data, _len) trc_dump_buffer(_prefix, _data, _len)
#else
#define BTTRC_DUMP_BUFFER(_prefix, _data, _len)
#endif

//静态常量字符BTE_LOGMSG_MODULE[]=“BTE_LOGMSG_MODULE”；

/* BTrgs）；E用于调试的跟踪ID*/
/* 堆栈的LayerID*/
#define BTTRC_ID_STK_GKI                   1
#define BTTRC_ID_STK_BTU                   2
#define BTTRC_ID_STK_HCI                   3
#define BTTRC_ID_STK_L2CAP                 4
#define BTTRC_ID_STK_RFCM_MX               5
#define BTTRC_ID_STK_RFCM_PRT              6
#define BTTRC_ID_STK_OBEX_C                7
#define BTTRC_ID_STK_OBEX_S                8
#define BTTRC_ID_STK_AVCT                  9
#define BTTRC_ID_STK_AVDT                  10
#define BTTRC_ID_STK_AVRC                  11
#define BTTRC_ID_STK_BIC                   12
#define BTTRC_ID_STK_BIS                   13
#define BTTRC_ID_STK_BNEP                  14
#define BTTRC_ID_STK_BPP                   15
#define BTTRC_ID_STK_BTM_ACL               16
#define BTTRC_ID_STK_BTM_PM                17
#define BTTRC_ID_STK_BTM_DEV_CTRL          18
#define BTTRC_ID_STK_BTM_SVC_DSC           19
#define BTTRC_ID_STK_BTM_INQ               20
#define BTTRC_ID_STK_BTM_SCO               21
#define BTTRC_ID_STK_BTM_SEC               22
#define BTTRC_ID_STK_HID                   24
#define BTTRC_ID_STK_HSP2                  25
#define BTTRC_ID_STK_CTP                   26
#define BTTRC_ID_STK_FTC                   27
#define BTTRC_ID_STK_FTS                   28
#define BTTRC_ID_STK_GAP                   29
#define BTTRC_ID_STK_HCRP                  31
#define BTTRC_ID_STK_ICP                   32
#define BTTRC_ID_STK_OPC                   33
#define BTTRC_ID_STK_OPS                   34
#define BTTRC_ID_STK_PAN                   35
#define BTTRC_ID_STK_SAP                   36
#define BTTRC_ID_STK_SDP                   37
#define BTTRC_ID_STK_SLIP                  38
#define BTTRC_ID_STK_SPP                   39
#define BTTRC_ID_STK_TCS                   40
#define BTTRC_ID_STK_VDP                   41
#define BTTRC_ID_STK_MCAP                  42
#define BTTRC_ID_STK_GATT                  43
#define BTTRC_ID_STK_SMP                   44
#define BTTRC_ID_STK_NFC                   45
#define BTTRC_ID_STK_NCI                   46
#define BTTRC_ID_STK_IDEP                  47
#define BTTRC_ID_STK_NDEP                  48
#define BTTRC_ID_STK_LLCP                  49
#define BTTRC_ID_STK_RW                    50
#define BTTRC_ID_STK_CE                    51
#define BTTRC_ID_STK_SNEP                  52
#define BTTRC_ID_STK_NDEF                  53
#define BTTRC_ID_STK_HIDD                  54

/* BTA的层ID*/
#define BTTRC_ID_BTA_ACC                   55         /* 高级照相机客户端*/
#define BTTRC_ID_BTA_AG                    56         /* 音频网关*/
#define BTTRC_ID_BTA_AV                    57         /* 高级音频*/
#define BTTRC_ID_BTA_BIC                   58         /* 基本图像客户端*/
#define BTTRC_ID_BTA_BIS                   59         /* 基本成像服务器*/
#define BTTRC_ID_BTA_BP                    60         /* 基本打印客户端*/
#define BTTRC_ID_BTA_CG                    61
#define BTTRC_ID_BTA_CT                    62         /* 无绳电话终端*/
#define BTTRC_ID_BTA_DG                    63         /* 数据网关*/
#define BTTRC_ID_BTA_DM                    64         /* 设备管理器*/
#define BTTRC_ID_BTA_DM_SRCH               65         /* 设备管理器搜索*/
#define BTTRC_ID_BTA_DM_SEC                66         /* 设备管理器安全*/
#define BTTRC_ID_BTA_FM                    67
#define BTTRC_ID_BTA_FTC                   68         /* 文件传输客户端*/
#define BTTRC_ID_BTA_FTS                   69         /* 文件传输服务器*/
#define BTTRC_ID_BTA_HIDH                  70
#define BTTRC_ID_BTA_HIDD                  71
#define BTTRC_ID_BTA_JV                    72
#define BTTRC_ID_BTA_OPC                   73         /* 对象推送客户端*/
#define BTTRC_ID_BTA_OPS                   74         /* 对象推送服务器*/
#define BTTRC_ID_BTA_PAN                   75         /* 个人区域网络*/
#define BTTRC_ID_BTA_PR                    76         /* 打印机客户端*/
#define BTTRC_ID_BTA_SC                    77         /* SIM卡访问服务器*/
#define BTTRC_ID_BTA_SS                    78         /* 同步服务器*/
#define BTTRC_ID_BTA_SYS                   79         /* 系统管理员*/
#define BTTRC_ID_AVDT_SCB                  80         /* avdt scb公司*/
#define BTTRC_ID_AVDT_CCB                  81         /* 平均日ccb*/

// btla特定++
/* 为BTL-A添加的层ID。可能应该修改bte_logmsg。c未来。*/
#define BTTRC_ID_STK_RFCOMM                82
#define BTTRC_ID_STK_RFCOMM_DATA           83
#define BTTRC_ID_STK_OBEX                  84
#define BTTRC_ID_STK_A2D                   85
#define BTTRC_ID_STK_BIP                   86

/* BT应用程序的层ID*/
#define BTTRC_ID_BTAPP                     87
#define BTTRC_ID_BT_PROTOCOL               88         /* 这是允许动态启用/禁用BT_PROTOCOL_TRACE的临时解决方案*/
#define BTTRC_ID_MAX_ID                    BTTRC_ID_BT_PROTOCOL
// btla特定--
#define BTTRC_ID_ALL_LAYERS                0xFF       /* 所有跟踪层*/
/* 跟踪API中使用的参数数据类型*/
#define BTTRC_PARAM_UINT8                  1
#define BTTRC_PARAM_UINT16                 2
#define BTTRC_PARAM_UINT32                 3

/* 启用或禁用详细跟踪信息。*/
#ifndef BT_TRACE_VERBOSE
#define BT_TRACE_VERBOSE    FALSE
#endif

/* 启用或禁用所有跟踪消息。*/
#ifndef BT_USE_TRACES
#define BT_USE_TRACES       FALSE
#endif

#ifndef BT_TRACE_APPL
#define BT_TRACE_APPL   BT_USE_TRACES
#endif

/******************************************************************************
** 跟踪级别
**
** 以下值可用于不同的级别：BT_TRACE_LEVEL_NONE 0不生成跟踪消息BT_TRACE_LEVEL_ERROR 1错误条件跟踪消息BT_TRACE_LEVEL _WARNING 2警告条件跟踪消息BT_TRACE_EVEL_API 3 API跟踪BT_TRACE-LEVEL_EVENT 4事件的调试消息BT_TRACE_LEVEL_Debug 5调试消息（常规）
******************************************************************************/

// btla特定++
/* 核心堆栈默认跟踪级别*/
#define HCI_INITIAL_TRACE_LEVEL             UC_BT_LOG_HCI_TRACE_LEVEL
#define BTM_INITIAL_TRACE_LEVEL             UC_BT_LOG_BTM_TRACE_LEVEL
#define L2CAP_INITIAL_TRACE_LEVEL           UC_BT_LOG_L2CAP_TRACE_LEVEL
#define RFCOMM_INITIAL_TRACE_LEVEL          UC_BT_LOG_RFCOMM_TRACE_LEVEL
#define SDP_INITIAL_TRACE_LEVEL             UC_BT_LOG_SDP_TRACE_LEVEL
#define GAP_INITIAL_TRACE_LEVEL             UC_BT_LOG_GAP_TRACE_LEVEL
#define BNEP_INITIAL_TRACE_LEVEL            UC_BT_LOG_BNEP_TRACE_LEVEL
#define PAN_INITIAL_TRACE_LEVEL             UC_BT_LOG_PAN_TRACE_LEVEL
#define A2D_INITIAL_TRACE_LEVEL             UC_BT_LOG_A2D_TRACE_LEVEL
#define AVDT_INITIAL_TRACE_LEVEL            UC_BT_LOG_AVDT_TRACE_LEVEL
#define AVCT_INITIAL_TRACE_LEVEL            UC_BT_LOG_AVCT_TRACE_LEVEL
#define AVRC_INITIAL_TRACE_LEVEL            UC_BT_LOG_AVRC_TRACE_LEVEL
#define MCA_INITIAL_TRACE_LEVEL             UC_BT_LOG_MCA_TRACE_LEVEL
#define HIDH_INITIAL_TRACE_LEVEL            UC_BT_LOG_HIDH_TRACE_LEVEL
#define HIDD_INITIAL_TRACE_LEVEL            UC_BT_LOG_HIDD_TRACE_LEVEL
#define APPL_INITIAL_TRACE_LEVEL            UC_BT_LOG_APPL_TRACE_LEVEL
#define GATT_INITIAL_TRACE_LEVEL            UC_BT_LOG_GATT_TRACE_LEVEL
#define SMP_INITIAL_TRACE_LEVEL             UC_BT_LOG_SMP_TRACE_LEVEL
#define BTIF_INITIAL_TRACE_LEVEL            UC_BT_LOG_BTIF_TRACE_LEVEL

// btla特定--

#if !UC_BT_STACK_NO_LOG
#define LOG_ERROR(format, ... )             {if (LOG_LOCAL_LEVEL >= ESP_LOG_ERROR)    esp_log_write(ESP_LOG_ERROR,   "BT_LOG", LOG_FORMAT(E, format), esp_log_timestamp(), "BT_LOG", ##__VA_ARGS__); }
#define LOG_WARN(format, ... )              {if (LOG_LOCAL_LEVEL >= ESP_LOG_WARN)     esp_log_write(ESP_LOG_WARN,    "BT_LOG", LOG_FORMAT(W, format), esp_log_timestamp(), "BT_LOG", ##__VA_ARGS__); }
#define LOG_INFO(format, ... )              {if (LOG_LOCAL_LEVEL >= ESP_LOG_INFO)     esp_log_write(ESP_LOG_INFO,    "BT_LOG", LOG_FORMAT(I, format), esp_log_timestamp(), "BT_LOG", ##__VA_ARGS__); }
#define LOG_DEBUG(format, ... )             {if (LOG_LOCAL_LEVEL >= ESP_LOG_DEBUG)    esp_log_write(ESP_LOG_DEBUG,   "BT_LOG", LOG_FORMAT(D, format), esp_log_timestamp(), "BT_LOG", ##__VA_ARGS__); }
#define LOG_VERBOSE(format, ... )           {if (LOG_LOCAL_LEVEL >= ESP_LOG_VERBOSE)  esp_log_write(ESP_LOG_VERBOSE, "BT_LOG", LOG_FORMAT(V, format), esp_log_timestamp(), "BT_LOG", ##__VA_ARGS__); }

/* 定义BTM跟踪
*/
#define BTM_TRACE_ERROR(fmt, args...)       {if (btm_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(BTM, ERROR)) BT_PRINT_E("BT_BTM", fmt, ## args);}
#define BTM_TRACE_WARNING(fmt, args...)     {if (btm_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(BTM, WARNING)) BT_PRINT_W("BT_BTM", fmt, ## args);}
#define BTM_TRACE_API(fmt, args...)         {if (btm_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(BTM,API)) BT_PRINT_I("BT_BTM", fmt, ## args);}
#define BTM_TRACE_EVENT(fmt, args...)       {if (btm_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(BTM,EVENT)) BT_PRINT_D("BT_BTM", fmt, ## args);}
#define BTM_TRACE_DEBUG(fmt, args...)       {if (btm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(BTM,DEBUG)) BT_PRINT_D("BT_BTM", fmt, ## args);}

/* 定义L2CAP单元的跟踪
*/
#define L2CAP_TRACE_ERROR(fmt, args...)     {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(L2CAP, ERROR)) BT_PRINT_E("BT_L2CAP", fmt, ## args);}
#define L2CAP_TRACE_WARNING(fmt, args...)   {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(L2CAP, WARNING)) BT_PRINT_W("BT_L2CAP", fmt, ## args);}
#define L2CAP_TRACE_API(fmt, args...)       {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(L2CAP,API)) BT_PRINT_I("BT_L2CAP", fmt, ## args);}
#define L2CAP_TRACE_EVENT(fmt, args...)     {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(L2CAP,EVENT)) BT_PRINT_D("BT_L2CAP", fmt, ## args);}
#define L2CAP_TRACE_DEBUG(fmt, args...)     {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(L2CAP,DEBUG)) BT_PRINT_D("BT_L2CAP", fmt, ## args);}

/* 定义SDP单元的跟踪
*/
#define SDP_TRACE_ERROR(fmt, args...)       {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(SDP, ERROR)) BT_PRINT_E("BT_SDP", fmt, ## args);}
#define SDP_TRACE_WARNING(fmt, args...)     {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(SDP, WARNING)) BT_PRINT_W("BT_SDP", fmt, ## args);}
#define SDP_TRACE_API(fmt, args...)         {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(SDP,API)) BT_PRINT_I("BT_SDP", fmt, ## args);}
#define SDP_TRACE_EVENT(fmt, args...)       {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(SDP,EVENT)) BT_PRINT_D("BT_SDP", fmt, ## args);}
#define SDP_TRACE_DEBUG(fmt, args...)       {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(SDP,DEBUG)) BT_PRINT_D("BT_SDP", fmt, ## args);}

/* 定义RFCOMM单元的跟踪
*/
#define RFCOMM_TRACE_ERROR(fmt, args...)    {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(RFCOMM, ERROR)) BT_PRINT_E("BT_RFCOMM", fmt, ## args);}
#define RFCOMM_TRACE_WARNING(fmt, args...)  {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(RFCOMM, WARNING)) BT_PRINT_W("BT_RFCOMM", fmt, ## args);}
#define RFCOMM_TRACE_API(fmt, args...)      {if (rfc_cb.trace_level >=BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(RFCOMM,API)) BT_PRINT_I("BT_RFCOMM", fmt, ## args);}
#define RFCOMM_TRACE_EVENT(fmt, args...)    {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(RFCOMM,EVENT)) BT_PRINT_D("BT_RFCOMM", fmt, ## args);}
#define RFCOMM_TRACE_DEBUG(fmt, args...)    {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(RFCOMM,DEBUG)) BT_PRINT_D("BT_RFCOMM", fmt, ## args);}

/* 通用访问配置文件跟踪*/
#define GAP_TRACE_ERROR(fmt, args...)       {if (gap_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(GAP, ERROR)) BT_PRINT_E("BT_GAP", fmt, ## args);}
#define GAP_TRACE_API(fmt, args...)         {if (gap_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(GAP,API)) BT_PRINT_I("BT_GAP", fmt, ## args);}
#define GAP_TRACE_EVENT(fmt, args...)       {if (gap_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(GAP,EVENT)) BT_PRINT_D("BT_GAP", fmt, ## args);}
#define GAP_TRACE_WARNING(fmt, args...)     {if (gap_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(GAP, WARNING)) BT_PRINT_W("BT_GAP", fmt, ## args);}

/* 定义HID主机的跟踪*/
#define HIDH_TRACE_ERROR(fmt, args...)      {if (hh_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(HIDH, ERROR)) BT_PRINT_E("BT_HIDH", fmt, ## args);}
#define HIDH_TRACE_WARNING(fmt, args...)    {if (hh_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(HIDH, WARNING)) BT_PRINT_W("BT_HIDH", fmt, ## args);}
#define HIDH_TRACE_API(fmt, args...)        {if (hh_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(HIDH,API)) BT_PRINT_I("BT_HIDH", fmt, ## args);}
#define HIDH_TRACE_EVENT(fmt, args...)      {if (hh_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(HIDH,EVENT)) BT_PRINT_D("BT_HIDH", fmt, ## args);}
#define HIDH_TRACE_DEBUG(fmt, args...)      {if (hh_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(HIDH,DEBUG)) BT_PRINT_D("BT_HIDH", fmt, ## args);}

/* 定义HID设备的跟踪*/
#define HIDD_TRACE_ERROR(fmt, args...)      {if (hd_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(HIDD, ERROR)) BT_PRINT_E("BT_HIDD", fmt, ## args);}
#define HIDD_TRACE_WARNING(fmt, args...)    {if (hd_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(HIDD, WARNING)) BT_PRINT_W("BT_HIDD", fmt, ## args);}
#define HIDD_TRACE_API(fmt, args...)        {if (hd_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(HIDD,API)) BT_PRINT_I("BT_HIDD", fmt, ## args);}
#define HIDD_TRACE_EVENT(fmt, args...)      {if (hd_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(HIDD,EVENT)) BT_PRINT_D("BT_HIDD", fmt, ## args);}
#define HIDD_TRACE_DEBUG(fmt, args...)      {if (hd_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(HIDD,DEBUG)) BT_PRINT_D("BT_HIDD", fmt, ## args);}
#define HIDD_TRACE_VERBOSE(fmt, args...)    {if (hd_cb.trace_level >= BT_TRACE_LEVEL_VERBOSE && BT_LOG_LEVEL_CHECK(HIDD,VERBOSE)) BT_PRINT_D("BT_HIDD", fmt, ## args);}

/* 定义BNEP的轨迹*/

#define BNEP_TRACE_ERROR(fmt, args...)      {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(BNEP, ERROR)) BT_PRINT_E("BT_BNEP", fmt, ## args);}
#define BNEP_TRACE_WARNING(fmt, args...)    {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(BNEP, WARNING)) BT_PRINT_W("BT_BNEP", fmt, ## args);}
#define BNEP_TRACE_API(fmt, args...)        {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(BNEP,API)) BT_PRINT_I("BT_BNEP", fmt, ## args);}
#define BNEP_TRACE_EVENT(fmt, args...)      {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(BNEP,EVENT)) BT_PRINT_D("BT_BNEP", fmt, ## args);}
#define BNEP_TRACE_DEBUG(fmt, args...)      {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(BNEP,DEBUG)) BT_PRINT_D("BT_BNEP", fmt, ## args);}

/* 定义PAN的跟踪*/

#define PAN_TRACE_ERROR(fmt, args...)       {if (pan_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(PAN, ERROR)) BT_PRINT_E("BT_PAN", fmt, ## args);}
#define PAN_TRACE_WARNING(fmt, args...)     {if (pan_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(PAN, WARNING)) BT_PRINT_W("BT_PAN", fmt, ## args);}
#define PAN_TRACE_API(fmt, args...)         {if (pan_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(PAN,API)) BT_PRINT_I("BT_PAN", fmt, ## args);}
#define PAN_TRACE_EVENT(fmt, args...)       {if (pan_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(PAN,EVENT)) BT_PRINT_D("BT_PAN", fmt, ## args);}
#define PAN_TRACE_DEBUG(fmt, args...)       {if (pan_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(PAN,DEBUG)) BT_PRINT_D("BT_PAN", fmt, ## args);}

/* 定义A2DP配置文件的跟踪
*/
#define A2D_TRACE_ERROR(fmt, args...)       {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(A2D, ERROR)) BT_PRINT_E("BT_A2D", fmt, ## args);}
#define A2D_TRACE_WARNING(fmt, args...)     {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(A2D, WARNING)) BT_PRINT_W("BT_A2D", fmt, ## args);}
#define A2D_TRACE_API(fmt, args...)         {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(A2D,API)) BT_PRINT_I("BT_A2D", fmt, ## args);}
#define A2D_TRACE_EVENT(fmt, args...)       {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(A2D,EVENT)) BT_PRINT_D("BT_A2D", fmt, ## args);}
#define A2D_TRACE_DEBUG(fmt, args...)       {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(A2D,DEBUG)) BT_PRINT_D("BT_A2D", fmt, ## args);}

/* AVDTP
*/
#define AVDT_TRACE_ERROR(fmt, args...)      {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(AVDT, ERROR)) BT_PRINT_E("BT_AVDT", fmt, ## args);}
#define AVDT_TRACE_WARNING(fmt, args...)    {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(AVDT, WARNING)) BT_PRINT_W("BT_AVDT", fmt, ## args);}
#define AVDT_TRACE_API(fmt, args...)        {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(AVDT,API)) BT_PRINT_I("BT_AVDT", fmt, ## args);}
#define AVDT_TRACE_EVENT(fmt, args...)      {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(AVDT,EVENT)) BT_PRINT_D("BT_AVDT", fmt, ## args);}
#define AVDT_TRACE_DEBUG(fmt, args...)      {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(AVDT,DEBUG)) BT_PRINT_D("BT_AVDT", fmt, ## args);}

/* 定义AVCTP协议的跟踪
*/
#define AVCT_TRACE_ERROR(fmt, args...)      {if (avct_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(AVCT, ERROR)) BT_PRINT_E("BT_AVCT", fmt, ## args);}
#define AVCT_TRACE_WARNING(fmt, args...)    {if (avct_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(AVCT, WARNING)) BT_PRINT_W("BT_AVCT", fmt, ## args);}
#define AVCT_TRACE_API(fmt, args...)        {if (avct_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(AVCT,API)) BT_PRINT_I("BT_AVCT", fmt, ## args);}
#define AVCT_TRACE_EVENT(fmt, args...)      {if (avct_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(AVCT,EVENT)) BT_PRINT_D("BT_AVCT", fmt, ## args);}
#define AVCT_TRACE_DEBUG(fmt, args...)      {if (avct_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(AVCT,DEBUG)) BT_PRINT_D("BT_AVCT", fmt, ## args);}

/* 定义AVRCP配置文件的跟踪
*/
#define AVRC_TRACE_ERROR(fmt, args...)      {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(AVRC, ERROR)) BT_PRINT_E("BT_AVRC", fmt, ## args);}
#define AVRC_TRACE_WARNING(fmt, args...)    {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(AVRC, WARNING)) BT_PRINT_W("BT_AVRC", fmt, ## args);}
#define AVRC_TRACE_API(fmt, args...)        {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(AVRC,API)) BT_PRINT_I("BT_AVRC", fmt, ## args);}
#define AVRC_TRACE_EVENT(fmt, args...)      {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(AVRC,EVENT)) BT_PRINT_D("BT_AVRC", fmt, ## args);}
#define AVRC_TRACE_DEBUG(fmt, args...)      {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(AVRC,DEBUG)) BT_PRINT_D("BT_AVRC", fmt, ## args);}

/* MCAP
*/
#define MCA_TRACE_ERROR(fmt, args...)       {if (mca_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(MCA, ERROR)) BT_PRINT_E("BT_MCA", fmt, ## args);}
#define MCA_TRACE_WARNING(fmt, args...)     {if (mca_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(MCA, WARNING)) BT_PRINT_W("BT_MCA", fmt, ## args);}
#define MCA_TRACE_API(fmt, args...)         {if (mca_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(MCA,API)) BT_PRINT_I("BT_MCA", fmt, ## args);}
#define MCA_TRACE_EVENT(fmt, args...)       {if (mca_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(MCA,EVENT)) BT_PRINT_D("BT_MCA", fmt, ## args);}
#define MCA_TRACE_DEBUG(fmt, args...)       {if (mca_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(MCA,DEBUG)) BT_PRINT_D("BT_MCA", fmt, ## args);}

/* 定义ATT/GTT单位的跟踪
*/
#define GATT_TRACE_ERROR(fmt, args...)      {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(GATT, ERROR)) BT_PRINT_E("BT_GATT", fmt, ## args);}
#define GATT_TRACE_WARNING(fmt, args...)    {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(GATT, WARNING)) BT_PRINT_W("BT_GATT", fmt, ## args);}
#define GATT_TRACE_API(fmt, args...)        {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(GATT,API)) BT_PRINT_I("BT_GATT", fmt, ## args);}
#define GATT_TRACE_EVENT(fmt, args...)      {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(GATT,EVENT)) BT_PRINT_D("BT_GATT", fmt, ## args);}
#define GATT_TRACE_DEBUG(fmt, args...)      {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(GATT,DEBUG)) BT_PRINT_D("BT_GATT", fmt, ## args);}

/* 定义SMP单元的跟踪
*/
#define SMP_TRACE_ERROR(fmt, args...)       {if (smp_cb.trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(SMP, ERROR)) BT_PRINT_E("BT_SMP", fmt, ## args);}
#define SMP_TRACE_WARNING(fmt, args...)     {if (smp_cb.trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(SMP, WARNING)) BT_PRINT_W("BT_SMP", fmt, ## args);}
#define SMP_TRACE_API(fmt, args...)         {if (smp_cb.trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(SMP,API)) BT_PRINT_I("BT_SMP", fmt, ## args);}
#define SMP_TRACE_EVENT(fmt, args...)       {if (smp_cb.trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(SMP,EVENT)) BT_PRINT_D("BT_SMP", fmt, ## args);}
#define SMP_TRACE_DEBUG(fmt, args...)       {if (smp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(SMP,DEBUG)) BT_PRINT_D("BT_SMP", fmt, ## args);}


extern UINT8 btif_trace_level;

// 定义应用程序的跟踪
#define BTIF_TRACE_ERROR(fmt, args...)      {if (btif_trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(BTIF, ERROR)) BT_PRINT_E("BT_BTIF", fmt, ## args);}
#define BTIF_TRACE_WARNING(fmt, args...)    {if (btif_trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(BTIF, WARNING)) BT_PRINT_W("BT_BTIF", fmt, ## args);}
#define BTIF_TRACE_API(fmt, args...)        {if (btif_trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(BTIF,API)) BT_PRINT_I("BT_BTIF", fmt, ## args);}
#define BTIF_TRACE_EVENT(fmt, args...)      {if (btif_trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(BTIF,EVENT)) BT_PRINT_D("BT_BTIF", fmt, ## args);}
#define BTIF_TRACE_DEBUG(fmt, args...)      {if (btif_trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(BTIF,DEBUG)) BT_PRINT_D("BT_BTIF", fmt, ## args);}
#define BTIF_TRACE_VERBOSE(fmt, args...)    {if (btif_trace_level >= BT_TRACE_LEVEL_VERBOSE && BT_LOG_LEVEL_CHECK(BTIF,VERBOSE)) BT_PRINT_V("BT_BTIF", fmt, ## args);}

/* 定义应用程序的跟踪*/

#define APPL_TRACE_ERROR(fmt, args...)      {if (appl_trace_level >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(APPL, ERROR)) BT_PRINT_E("BT_APPL", fmt, ## args);}
#define APPL_TRACE_WARNING(fmt, args...)    {if (appl_trace_level >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(APPL, WARNING)) BT_PRINT_W("BT_APPL", fmt, ## args);}
#define APPL_TRACE_API(fmt, args...)        {if (appl_trace_level >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(APPL,API)) BT_PRINT_I("BT_APPL", fmt, ## args);}
#define APPL_TRACE_EVENT(fmt, args...)      {if (appl_trace_level >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(APPL,EVENT)) BT_PRINT_D("BT_APPL", fmt, ## args);}
#define APPL_TRACE_DEBUG(fmt, args...)      {if (appl_trace_level >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(APPL,DEBUG)) BT_PRINT_D("BT_APPL", fmt, ## args);}
#define APPL_TRACE_VERBOSE(fmt, args...)    {if (appl_trace_level >= BT_TRACE_LEVEL_VERBOSE && BT_LOG_LEVEL_CHECK(APPL,VERBOSE)) BT_PRINT_V("BT_APPL", fmt, ## args);}

/* 定义从`btu_cb修改的HCI单元的跟踪。trace_level”设置为“HCI_INITIAL_trace_level”，以在HCI_layer中使用HCI_trace_XXXX。c不包括`btu.h`
*/
#define HCI_TRACE_ERROR(fmt, args...)       {if (HCI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(HCI, ERROR)) BT_PRINT_E("BT_HCI", fmt,## args);}
#define HCI_TRACE_WARNING(fmt, args...)     {if (HCI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(HCI, WARNING)) BT_PRINT_W("BT_HCI", fmt,## args);}
#define HCI_TRACE_EVENT(fmt, args...)       {if (HCI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(HCI,EVENT)) BT_PRINT_D("BT_HCI", fmt,## args);}
#define HCI_TRACE_DEBUG(fmt, args...)       {if (HCI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(HCI,DEBUG)) BT_PRINT_D("BT_HCI", fmt,## args);}

#else
#define LOG_ERROR(fmt, args...)
#define LOG_WARN(fmt, args...)
#define LOG_INFO(fmt, args...)
#define LOG_DEBUG(fmt, args...)
#define LOG_VERBOSE(fmt, args...)

/* 定义HCI装置的跟踪
*/
#define HCI_TRACE_ERROR(fmt, args...)
#define HCI_TRACE_WARNING(fmt, args...)
#define HCI_TRACE_EVENT(fmt, args...)
#define HCI_TRACE_DEBUG(fmt, args...)

/* 定义BTM跟踪
*/
#define BTM_TRACE_ERROR(fmt, args...)
#define BTM_TRACE_WARNING(fmt, args...)
#define BTM_TRACE_API(fmt, args...)
#define BTM_TRACE_EVENT(fmt, args...)
#define BTM_TRACE_DEBUG(fmt, args...)

/* 定义L2CAP单元的跟踪
*/
#define L2CAP_TRACE_ERROR(fmt, args...)
#define L2CAP_TRACE_WARNING(fmt, args...)
#define L2CAP_TRACE_API(fmt, args...)
#define L2CAP_TRACE_EVENT(fmt, args...)
#define L2CAP_TRACE_DEBUG(fmt, args...)

/* 定义SDP单元的跟踪
*/
#define SDP_TRACE_ERROR(fmt, args...)
#define SDP_TRACE_WARNING(fmt, args...)
#define SDP_TRACE_API(fmt, args...)
#define SDP_TRACE_EVENT(fmt, args...)
#define SDP_TRACE_DEBUG(fmt, args...)

/* 定义RFCOMM单元的跟踪
*/
#define RFCOMM_TRACE_ERROR(fmt, args...)
#define RFCOMM_TRACE_WARNING(fmt, args...)
#define RFCOMM_TRACE_API(fmt, args...)
#define RFCOMM_TRACE_EVENT(fmt, args...)
#define RFCOMM_TRACE_DEBUG(fmt, args...)

/* 通用访问配置文件跟踪*/
#define GAP_TRACE_ERROR(fmt, args...)
#define GAP_TRACE_EVENT(fmt, args...)
#define GAP_TRACE_API(fmt, args...)
#define GAP_TRACE_WARNING(fmt, args...)

/* 定义HID主机的跟踪*/
#define HIDH_TRACE_ERROR(fmt, args...)
#define HIDH_TRACE_WARNING(fmt, args...)
#define HIDH_TRACE_API(fmt, args...)
#define HIDH_TRACE_EVENT(fmt, args...)
#define HIDH_TRACE_DEBUG(fmt, args...)

/* 定义HID设备的跟踪*/
#define HIDD_TRACE_ERROR(fmt, args...)
#define HIDD_TRACE_WARNING(fmt, args...)
#define HIDD_TRACE_API(fmt, args...)
#define HIDD_TRACE_EVENT(fmt, args...)
#define HIDD_TRACE_DEBUG(fmt, args...)
#define HIDD_TRACE_VERBOSE(fmt, args...)

/* 定义BNEP的轨迹*/

#define BNEP_TRACE_ERROR(fmt, args...)
#define BNEP_TRACE_WARNING(fmt, args...)
#define BNEP_TRACE_API(fmt, args...)
#define BNEP_TRACE_EVENT(fmt, args...)
#define BNEP_TRACE_DEBUG(fmt, args...)

/* 定义PAN的跟踪*/

#define PAN_TRACE_ERROR(fmt, args...)
#define PAN_TRACE_WARNING(fmt, args...)
#define PAN_TRACE_API(fmt, args...)
#define PAN_TRACE_EVENT(fmt, args...)
#define PAN_TRACE_DEBUG(fmt, args...)

/* 定义A2DP配置文件的跟踪
*/
#define A2D_TRACE_ERROR(fmt, args...)
#define A2D_TRACE_WARNING(fmt, args...)
#define A2D_TRACE_EVENT(fmt, args...)
#define A2D_TRACE_DEBUG(fmt, args...)
#define A2D_TRACE_API(fmt, args...)

/* AVDTP
*/
#define AVDT_TRACE_ERROR(fmt, args...)
#define AVDT_TRACE_WARNING(fmt, args...)
#define AVDT_TRACE_EVENT(fmt, args...)
#define AVDT_TRACE_DEBUG(fmt, args...)
#define AVDT_TRACE_API(fmt, args...)

/* 定义AVCTP协议的跟踪
*/
#define AVCT_TRACE_ERROR(fmt, args...)
#define AVCT_TRACE_WARNING(fmt, args...)
#define AVCT_TRACE_EVENT(fmt, args...)
#define AVCT_TRACE_DEBUG(fmt, args...)
#define AVCT_TRACE_API(fmt, args...)

/* 定义AVRCP配置文件的跟踪
*/
#define AVRC_TRACE_ERROR(fmt, args...)
#define AVRC_TRACE_WARNING(fmt, args...)
#define AVRC_TRACE_EVENT(fmt, args...)
#define AVRC_TRACE_DEBUG(fmt, args...)
#define AVRC_TRACE_API(fmt, args...)

/* MCAP
*/
#define MCA_TRACE_ERROR(fmt, args...)
#define MCA_TRACE_WARNING(fmt, args...)
#define MCA_TRACE_EVENT(fmt, args...)
#define MCA_TRACE_DEBUG(fmt, args...)
#define MCA_TRACE_API(fmt, args...)

/* 定义ATT/GTT单位的跟踪
*/
#define GATT_TRACE_ERROR(fmt, args...)
#define GATT_TRACE_WARNING(fmt, args...)
#define GATT_TRACE_API(fmt, args...)
#define GATT_TRACE_EVENT(fmt, args...)
#define GATT_TRACE_DEBUG(fmt, args...)

/* 定义SMP单元的跟踪
*/
#define SMP_TRACE_ERROR(fmt, args...)
#define SMP_TRACE_WARNING(fmt, args...)
#define SMP_TRACE_API(fmt, args...)
#define SMP_TRACE_EVENT(fmt, args...)
#define SMP_TRACE_DEBUG(fmt, args...)

extern UINT8 btif_trace_level;

// 定义应用程序的跟踪
#define BTIF_TRACE_ERROR(fmt, args...)
#define BTIF_TRACE_WARNING(fmt, args...)
#define BTIF_TRACE_API(fmt, args...)
#define BTIF_TRACE_EVENT(fmt, args...)
#define BTIF_TRACE_DEBUG(fmt, args...)
#define BTIF_TRACE_VERBOSE(fmt, args...)

/* 定义应用程序的跟踪*/

#define APPL_TRACE_ERROR(fmt, args...)
#define APPL_TRACE_WARNING(fmt, args...)
#define APPL_TRACE_API(fmt, args...)
#define APPL_TRACE_EVENT(fmt, args...)
#define APPL_TRACE_DEBUG(fmt, args...)
#define APPL_TRACE_VERBOSE(fmt, args...)

#endif  ///!UC_BT_STACK_NO_LOG


/* 简化的跟踪助手宏
*/
#define bdld(fmt, args...) \
    do{\
        if((MY_LOG_LEVEL) >= BT_TRACE_LEVEL_DEBUG) \
        BT_PRINT_D(fmt, ## args);        \
    }while(0)

#define bdlw(fmt, args...) \
    do{\
        if((MY_LOG_LEVEL) >= BT_TRACE_LEVEL_WARNING) \
        BT_PRINT_W(fmt, ## args);        \
    }while(0)

#define bdle(fmt, args...) \
    do{\
        if((MY_LOG_LEVEL) >= BT_TRACE_LEVEL_ERROR) \
        BT_PRINT_E(fmt, ## args);        \
    }while(0)

#define bdla(assert_if) \
    do{\
        if(((MY_LOG_LEVEL) >= BT_TRACE_LEVEL_ERROR) && !(assert_if)) \
        BT_PRINT_E("%s: assert failed\n", #assert_if);       \
    }while(0)

typedef UINT8 tBTTRC_PARAM_TYPE;
typedef UINT8 tBTTRC_LAYER_ID;
typedef UINT8 tBTTRC_TYPE;

typedef struct {
    tBTTRC_LAYER_ID layer_id;
    tBTTRC_TYPE     type;      /* TODO:使用tBTTRC_TYPE而不是“经典级别0-5”*/
} tBTTRC_LEVEL;

typedef UINT8 (tBTTRC_SET_TRACE_LEVEL)( UINT8 );

typedef struct {
    const tBTTRC_LAYER_ID         layer_id_start;
    const tBTTRC_LAYER_ID         layer_id_end;
    tBTTRC_SET_TRACE_LEVEL        *p_f;
    const char                    *trc_name;
    UINT8                         trace_level;
} tBTTRC_FUNC_MAP;

/* 此处为appl_trace_level的外部声明，以避免使用appl_TRACExxx宏在所有文件中添加声明*/
extern UINT8 appl_trace_level;

#endif /*_BT_TRACE_H_*/

