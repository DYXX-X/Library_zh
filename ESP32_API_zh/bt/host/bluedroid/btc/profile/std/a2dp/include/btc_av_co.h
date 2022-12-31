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

#ifndef __BTC_AV_CO_H__
#define __BTC_AV_CO_H__

#include "btc_a2dp.h"
#include "bta/bta_av_co.h"

#if (BTA_AV_INCLUDED == TRUE)
/*******************************************************************************
**  常量和宏
********************************************************************************/

enum {
    BTC_SV_AV_AA_SBC_INDEX = 0,
    BTC_SV_AV_AA_SBC_SINK_INDEX,
    BTC_SV_AV_AA_SEP_INDEX  /* 最后一个索引*/
};

/*****************************************************************************
**  本地数据
*****************************************************************************/
typedef struct {
    UINT8 sep_info_idx;                 /* 本地SEP索引（在BTA表中）*/
    UINT8 seid;                         /* 对等SEP索引（在对等表中）*/
    UINT8 codec_type;                   /* 对等SEP编解码器类型*/
    UINT8 codec_caps[AVDT_CODEC_SIZE];  /* 对等SEP编解码器功能*/
    UINT8 num_protect;                  /* CP元素的对等SEP数量*/
    UINT8 protect_info[BTA_AV_CP_INFO_LEN];  /* 对等SEP内容保护信息*/
} tBTA_AV_CO_SINK;

typedef struct {
    BD_ADDR         addr;               /* 音频/视频对等体地址*/
    tBTA_AV_CO_SINK snks[BTC_SV_AV_AA_SEP_INDEX]; /* 支撑水槽阵列*/
    tBTA_AV_CO_SINK srcs[BTC_SV_AV_AA_SEP_INDEX]; /* 支持的src阵列*/
    UINT8           num_snks;           /* 对等端的汇总数*/
    UINT8           num_srcs;           /* 对等端的src总数*/
    UINT8           num_seps;           /* 对等端的seid总数*/
    UINT8           num_rx_snks;        /* 接收的接收器数量*/
    UINT8           num_rx_srcs;        /* 接收的src数量*/
    UINT8           num_sup_snks;       /* snks阵列中支持的接收器数*/
    UINT8           num_sup_srcs;       /* srcs阵列中支持的srcs数量*/
    tBTA_AV_CO_SINK *p_snk;             /* 当前选定的接收器*/
    tBTA_AV_CO_SINK *p_src;             /* 当前选定的src*/
    UINT8           codec_cfg[AVDT_CODEC_SIZE]; /* 当前编解码器配置*/
    BOOLEAN         cp_active;          /* 当前CP配置*/
    BOOLEAN         acp;                /* 承兑人*/
    BOOLEAN         recfg_needed;       /* 需要重新配置*/
    BOOLEAN         opened;             /* 开的*/
    UINT16          mtu;                /* 最大发射单元尺寸*/
    UINT16          uuid_to_connect;    /* 对等设备的uuid*/
} tBTA_AV_CO_PEER;

typedef struct {
    BOOLEAN active;
    UINT8 flag;
} tBTA_AV_CO_CP;

typedef struct {
    /* 连接的对等信息*/
    tBTA_AV_CO_PEER peers[BTA_AV_NUM_STRS];
    /* 当前编解码器配置-必须保护对此变量的访问*/
    tBTC_AV_CODEC_INFO codec_cfg;
    tBTC_AV_CODEC_INFO codec_cfg_setconfig; /* 远程对等setconfig首选项*/

    tBTA_AV_CO_CP cp;
} tBTA_AV_CO_CB;

/* 控制块实例*/
#if AVRC_DYNAMIC_MEMORY == FALSE
extern tBTA_AV_CO_CB bta_av_co_cb;
#else
extern tBTA_AV_CO_CB *bta_av_co_cb_ptr;
#define bta_av_co_cb (*bta_av_co_cb_ptr)
#endif
/*******************************************************************************
**  功能
********************************************************************************/

/*******************************************************************************
 ** 函数bta_av_co_cp_is_active
 **
 ** 说明获取内容保护的当前配置
 **
 ** 如果当前流具有CP，则返回TRUE，否则返回FALSE
 **
 *******************************************************************************/
BOOLEAN bta_av_co_cp_is_active(void);

/*******************************************************************************
 ** 函数bta_av_co_cp_get_flag
 **
 ** 说明获取内容保护标志BTA_AV_CP_SCMS_COPY_NEVER
 **
 ** 返回当前标志值
 **
 *******************************************************************************/
UINT8 bta_av_co_cp_get_flag(void);

/*******************************************************************************
 ** 函数bta_av_co_cp_set_flag
 **
 ** 说明设置内容保护标志BTA_AV_CP_SCMS_COPY_NEVER
 **
 ** 如果支持设置SCMS标志，则返回TRUE，否则返回FALSE
 **
 *******************************************************************************/
BOOLEAN bta_av_co_cp_set_flag(UINT8 cp_flag);

/*******************************************************************************
 ** 函数bta_av_co_audio_codec_reset
 **
 ** 说明重置当前编解码器配置
 **
 ** 返回void
 **
 *******************************************************************************/
void bta_av_co_audio_codec_reset(void);

/*******************************************************************************
 ** 函数bta_av_co_audio_codec_supported
 **
 ** 说明检查所有打开的连接是否与编解码器配置兼容
 **
 ** 如果所有打开的设备都支持此编解码器，则返回TRUE，否则返回FALSE
 **
 *******************************************************************************/
BOOLEAN bta_av_co_audio_codec_supported(tBTC_AV_STATUS *p_status);

/*******************************************************************************
 ** 函数bta_av_co_audio_set_codec
 **
 ** 说明从馈送类型设置当前编解码器配置。此功能正在开始修改配置，应予以保护。
 **
 ** 如果成功，则返回TRUE，否则返回FALSE
 **
 *******************************************************************************/
BOOLEAN bta_av_co_audio_set_codec(const tBTC_AV_MEDIA_FEEDINGS *p_feeding, tBTC_AV_STATUS *p_status);

/*******************************************************************************
 ** 函数bta_av_co_audio_get_sbc_config
 **
 ** 描述检索SBC编解码器配置。如果使用的编解码器不是SBC，则返回默认的SBC编解码器配置。
 **
 ** 如果编解码器为SBC，则返回TRUE，否则返回FALSE
 **
 *******************************************************************************/
BOOLEAN bta_av_co_audio_get_sbc_config(tA2D_SBC_CIE *p_sbc_config, UINT16 *p_minmtu);

/*******************************************************************************
 ** 函数bta_av_co_audio_discard_config
 **
 ** 说明放弃连接的编解码器配置
 **
 ** 不返回任何内容
 **
 *******************************************************************************/
void bta_av_co_audio_discard_config(tBTA_AV_HNDL hndl);

/*******************************************************************************
 ** 函数bta_av_co_init
 **
 ** 说明初始化
 **
 ** 不返回任何内容
 **
 *******************************************************************************/
void bta_av_co_init(void);


/*******************************************************************************
 ** 函数bta_av_co_peer_cp_supported
 **
 ** 说明检查对等方是否支持CP
 **
 ** 如果对等方支持CP，则返回TRUE
 **
 *******************************************************************************/
BOOLEAN bta_av_co_peer_cp_supported(tBTA_AV_HNDL hndl);

/*******************************************************************************
 ** 函数bta_av_co_get_remote_bitpool_pref
 **
 ** 说明检查远程端是否在导出的位池范围内执行了setconfig。如果设置，我们将设置远程首选项。
 **
 ** 如果设置了配置，则返回TRUE，否则返回FALSE
 **
 *******************************************************************************/
BOOLEAN bta_av_co_get_remote_bitpool_pref(UINT8 *min, UINT8 *max);

#endif  ///BTA_AV_INCLUDED == TRUE

#endif

