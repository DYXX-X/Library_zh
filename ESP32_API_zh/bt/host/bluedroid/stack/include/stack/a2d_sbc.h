/******************************************************************************
 * 版权所有（C）2000-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 接口到低复杂度子带编解码器（SBC）
 *
 ******************************************************************************/
#ifndef A2D_SBC_H
#define A2D_SBC_H
#if (A2D_INCLUDED == TRUE)
/*****************************************************************************
**  常量
*****************************************************************************/
/* SBC媒体有效载荷报头的长度。*/
#define A2D_SBC_MPL_HDR_LEN         1

/* SBC媒体编解码器功能的LOSC*/
#define A2D_SBC_INFO_LEN            6

/* 用于Codec特定信息元素*/
#define A2D_SBC_IE_SAMP_FREQ_MSK    0xF0    /* b7-b4采样频率*/
#define A2D_SBC_IE_SAMP_FREQ_16     0x80    /* b7:16千赫*/
#define A2D_SBC_IE_SAMP_FREQ_32     0x40    /* b6:32千赫*/
#define A2D_SBC_IE_SAMP_FREQ_44     0x20    /* b5:44.1kHz*/
#define A2D_SBC_IE_SAMP_FREQ_48     0x10    /* b4:48千赫*/

#define A2D_SBC_IE_CH_MD_MSK        0x0F    /* b3-b0信道模式*/
#define A2D_SBC_IE_CH_MD_MONO       0x08    /* b3：单声道*/
#define A2D_SBC_IE_CH_MD_DUAL       0x04    /* b2：双重*/
#define A2D_SBC_IE_CH_MD_STEREO     0x02    /* b1：立体声*/
#define A2D_SBC_IE_CH_MD_JOINT      0x01    /* b0：联合立体声*/

#define A2D_SBC_IE_BLOCKS_MSK       0xF0    /* b7-b4块数*/
#define A2D_SBC_IE_BLOCKS_4         0x80    /* 4块*/
#define A2D_SBC_IE_BLOCKS_8         0x40    /* 8块*/
#define A2D_SBC_IE_BLOCKS_12        0x20    /* 12块*/
#define A2D_SBC_IE_BLOCKS_16        0x10    /* 16块*/

#define A2D_SBC_IE_SUBBAND_MSK      0x0C    /* b3-b2子带数*/
#define A2D_SBC_IE_SUBBAND_4        0x08    /* b3:4*/
#define A2D_SBC_IE_SUBBAND_8        0x04    /* b2：8*/

#define A2D_SBC_IE_ALLOC_MD_MSK     0x03    /* b1-b0分配模式*/
#define A2D_SBC_IE_ALLOC_MD_S       0x02    /* b1：信噪比*/
#define A2D_SBC_IE_ALLOC_MD_L       0x01    /* b0：白炽灯*/

#define A2D_SBC_IE_MIN_BITPOOL      2
#define A2D_SBC_IE_MAX_BITPOOL      250

/* 用于媒体负载标头*/
#define A2D_SBC_HDR_F_MSK           0x80
#define A2D_SBC_HDR_S_MSK           0x40
#define A2D_SBC_HDR_L_MSK           0x20
#define A2D_SBC_HDR_NUM_MSK         0x0F

/*****************************************************************************
**  类型定义
*****************************************************************************/

/* SBC编解码器信息元素的数据类型*/
typedef struct {
    UINT8   samp_freq;      /* 采样频率*/
    UINT8   ch_mode;        /* 通道模式*/
    UINT8   block_len;      /* 块体长度*/
    UINT8   num_subbands;   /* 子带数量*/
    UINT8   alloc_mthd;     /* 分配方法*/
    UINT8   max_bitpool;    /* 最大位池*/
    UINT8   min_bitpool;    /* 最小位池*/
} tA2D_SBC_CIE;


/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************
** 函数A2D_BldSbcInfo
**
** 说明应用程序调用此函数以构建从LOSC八位字节开始的SBC媒体编解码器能力字节序列。输入参数：media_type：表示音频或多媒体。
**
**                      p_ie：SBC编解码器信息元素信息。
**
**                  输出参数：p_result：生成的编解码器信息字节序列。
**
** 如果函数执行成功，则返回A2D_SUCCESS。错误状态代码，否则。
******************************************************************************/
extern tA2D_STATUS A2D_BldSbcInfo(UINT8 media_type, tA2D_SBC_CIE *p_ie,
                                  UINT8 *p_result);

/******************************************************************************
** 函数A2D_ParsSbcInfo
**
** 说明应用程序调用此函数以解析从LOSC八位字节开始的SBC媒体编解码器能力字节序列。输入参数：p_info：要解析的字节序列。
**
**                      for_caps：如果字节序列用于获取能力响应，则为TRUE。
**
**                  输出参数：p_ie：SBC编解码器信息元素信息。
**
** 如果函数执行成功，则返回A2D_SUCCESS。错误状态代码，否则。
******************************************************************************/
extern tA2D_STATUS A2D_ParsSbcInfo(tA2D_SBC_CIE *p_ie, UINT8 *p_info,
                                   BOOLEAN for_caps);

/******************************************************************************
** 函数A2D_BldSbcMplHdr
**
** 说明应用程序调用此函数以解析SBC媒体有效载荷标头。输入参数：frag:1，如果是碎片。否则为0。
**
**                      start：1，如果是分段帧的起始包。
**
**                      last:1，如果是分段帧的最后一个数据包。
**
**                      num：如果frag为1，则这是此帧的剩余片段数（包括此片段）。如果frag为0，则这是此数据包中的帧数。
**
**                  输出参数：p_dst：生成的媒体负载标头字节序列。
**
** 返回void。
******************************************************************************/
extern void A2D_BldSbcMplHdr(UINT8 *p_dst, BOOLEAN frag, BOOLEAN start,
                             BOOLEAN last, UINT8 num);

/******************************************************************************
** 函数A2D_ParsSbcMplHdr
**
** 说明应用程序调用此函数以解析SBC媒体有效载荷标头。输入参数：p_src：要解析的字节序列。。
**
**                  输出参数：frag:1，如果已分段。否则为0。
**
**                      start：1，如果是分段帧的起始包。
**
**                      last:1，如果是分段帧的最后一个数据包。
**
**                      num：如果frag为1，则这是此帧的剩余片段数（包括此片段）。如果frag为0，则这是此数据包中的帧数。
**
** 返回void。
******************************************************************************/
extern void A2D_ParsSbcMplHdr(UINT8 *p_src, BOOLEAN *p_frag,
                              BOOLEAN *p_start, BOOLEAN *p_last,
                              UINT8 *p_num);
#ifdef __cplusplus
}
#endif

#endif  ///A2D_INCLUDED == TRUE

#endif /* A2D_SBC_H */

