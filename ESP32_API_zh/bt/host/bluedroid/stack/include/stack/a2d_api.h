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
 * A2DP应用程序编程接口
 *
 ******************************************************************************/
#ifndef A2D_API_H
#define A2D_API_H
#include "common/bt_defs.h"
#include "stack/sdp_api.h"
#if (A2D_INCLUDED == TRUE)
/*****************************************************************************
**  常量
*****************************************************************************/

/* 配置文件支持的功能*/
#define A2D_SUPF_PLAYER     0x0001
#define A2D_SUPF_MIC        0x0002
#define A2D_SUPF_TUNER      0x0004
#define A2D_SUPF_MIXER      0x0008

#define A2D_SUPF_HEADPHONE  0x0001
#define A2D_SUPF_SPEAKER    0x0002
#define A2D_SUPF_RECORDER   0x0004
#define A2D_SUPF_AMP        0x0008

/* AV媒体类型*/
#define A2D_MEDIA_TYPE_AUDIO    0x00    /* 音频媒体类型+RFA*/
#define A2D_MEDIA_TYPE_VIDEO    0x10    /* 视频媒体类型+RFA*/
#define A2D_MEDIA_TYPE_MULTI    0x20    /* 多媒体媒体类型+RFA*/

/* AV媒体编解码器类型（音频编解码器ID）*/
#define A2D_MEDIA_CT_SBC        0x00    /* SBC媒体编解码器类型*/
#define A2D_MEDIA_CT_M12        0x01    /* MPEG-1，2音频媒体编解码器类型*/
#define A2D_MEDIA_CT_M24        0x02    /* MPEG-2，4 AAC媒体编解码器类型*/
#define A2D_MEDIA_CT_ATRAC      0x04    /* ATRAC系列媒体编解码器类型*/

#define A2D_SUCCESS           0     /* 成功*/
#define A2D_FAIL              0x0A  /* 失败*/
#define A2D_BUSY              0x0B  /* A2D_FindService已在进行中*/
#define A2D_INVALID_PARAMS    0x0C  /* 错误的参数*/
#define A2D_WRONG_CODEC       0x0D  /* 错误的编解码器信息*/
#define A2D_BAD_CODEC_TYPE    0xC1  /* 媒体编解码器类型无效*/
#define A2D_NS_CODEC_TYPE     0xC2  /* 不支持媒体编解码器类型*/
#define A2D_BAD_SAMP_FREQ     0xC3  /* 采样频率无效或已选择多个值*/
#define A2D_NS_SAMP_FREQ      0xC4  /* 不支持采样频率*/
#define A2D_BAD_CH_MODE       0xC5  /* 通道模式无效或已选择多个值*/
#define A2D_NS_CH_MODE        0xC6  /* 不支持频道模式*/
#define A2D_BAD_SUBBANDS      0xC7  /* 未为“子带数”选择任何值或多个值*/
#define A2D_NS_SUBBANDS       0xC8  /* 不支持子带数*/
#define A2D_BAD_ALLOC_MTHD    0xC9  /* 未为分配方法选择任何值或多个值*/
#define A2D_NS_ALLOC_MTHD     0xCA  /* 不支持分配方法*/
#define A2D_BAD_MIN_BITPOOL   0xCB  /* 最小位池值无效*/
#define A2D_NS_MIN_BITPOOL    0xCC  /* 不支持最小位池值*/
#define A2D_BAD_MAX_BITPOOL   0xCD  /* 最大位池值无效*/
#define A2D_NS_MAX_BITPOOL    0xCE  /* 不支持最大位池值*/
#define A2D_BAD_LAYER         0xCF  /* 未为图层选择任何值或多个值*/
#define A2D_NS_LAYER          0xD0  /* 不支持层*/
#define A2D_NS_CRC            0xD1  /* 不支持CRC*/
#define A2D_NS_MPF            0xD2  /* 不支持MPF-2*/
#define A2D_NS_VBR            0xD3  /* 不支持VBR*/
#define A2D_BAD_BIT_RATE      0xD4  /* 未为比特率选择任何值或多个值*/
#define A2D_NS_BIT_RATE       0xD5  /* 不支持比特率*/
#define A2D_BAD_OBJ_TYPE      0xD6  /* 1）对象类型无效（b3-b0）或2）未为对象类型选择任何值或多个值*/
#define A2D_NS_OBJ_TYPE       0xD7  /* 不支持对象类型*/
#define A2D_BAD_CHANNEL       0xD8  /* 未为频道选择任何值或多个值*/
#define A2D_NS_CHANNEL        0xD9  /* 不支持频道*/
#define A2D_BAD_BLOCK_LEN     0xDD  /* 未为块长度选择任何值或多个值*/
#define A2D_BAD_CP_TYPE       0xE0  /* 不支持请求的CP类型。*/
#define A2D_BAD_CP_FORMAT     0xE1  /* 内容保护服务能力/内容保护方案相关数据的格式不正确。*/

typedef UINT8 tA2D_STATUS;

/* A2D_BitsSet（）的返回值*/
#define A2D_SET_ONE_BIT         1   /* 仅设置一位*/
#define A2D_SET_ZERO_BIT        0   /* 所有位清除*/
#define A2D_SET_MULTL_BIT       2   /* 设置多个位*/

/*****************************************************************************
**  类型定义
*****************************************************************************/

/* 此数据类型在A2D_FindService（）中用于初始化SDP数据库以保存结果服务搜索。*/
typedef struct {
    UINT32              db_len;  /* 发现数据库的长度（字节）*/
    UINT16              num_attr;/* p_attrs中的属性数*/
    tSDP_DISCOVERY_DB  *p_db;    /* 指向发现数据库的指针*/
    UINT16             *p_attrs; /* 属性过滤器。如果为NULL，A2DP API将属性筛选器设置为ATTR_ID_SERVICE_CLASS_ID_LIST、ATTR_ID_BT_PROFILE_DESC_LIST，ATTR_ID_SUPPORTED_FEATURES、ATTR_ID _SERVICE_NAME和ATTR_ID_PROVIDER_NAME。如果不为NULL，则将输入作为过滤器。*/
} tA2D_SDP_DB_PARAMS;

/* 该数据类型在tA2D_FIND_CBACK中用于报告SDP发现过程的结果。*/
typedef struct {
    UINT16  service_len;    /* 服务名称的长度（字节）*/
    UINT16  provider_len;   /* 提供程序名称的长度（字节）*/
    char   *p_service_name; /* 指向服务名称的指针。此字符串不能以空结尾。使用service_len参数安全复制此字符串*/
    char   *p_provider_name;/* 指向提供程序名称的指针。此字符串不能以空结尾。使用provider_len参数安全地复制此字符串*/
    UINT16  features;       /* 配置文件支持的功能*/
    UINT16  avdt_version;   /* AVDTP协议版本*/
} tA2D_Service;

/* 这是通知SDP发现过程结果的回调。*/
typedef void (tA2D_FIND_CBACK)(BOOLEAN found, tA2D_Service *p_service);


/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************
** 函数A2D_AddRecord
**
** 描述此函数由服务器应用程序调用，以将SRC或SNK信息添加到SDP记录中。在调用此函数之前，应用程序必须调用SDP_CreateRecord（）来创建SDP记录。
**
**                  输入参数：service_uuid：表示SRC或SNK。
**
**                      p_service_name：指向包含服务名称的以空结尾的字符串的指针。
**
**                      p_provider_name：指向包含提供程序名称的以空结尾的字符串的指针。
**
**                      功能：配置文件支持的功能。
**
**                      sdp_handle:sdp_CreateRecord（）返回的sdp句柄。
**
**                  输出参数：无。
**
** 如果函数执行成功，则返回A2D_SUCCESS；如果给定了错误的参数，返回A2D_INVALID_PARAMS。如果函数执行失败，则为A2D_FAIL。
**
******************************************************************************/
extern tA2D_STATUS A2D_AddRecord(UINT16 service_uuid, char *p_service_name, char *p_provider_name,
                                 UINT16 features, UINT32 sdp_handle);

/******************************************************************************
** 函数A2D_FindService
**
** 描述此功能由客户端应用程序调用，以执行服务发现并从服务器检索SRC或SNK SDP记录信息。返回在服务器上找到的与服务UUID匹配的第一个服务记录的信息。回调函数将在服务发现完成时执行。一次只能有一个对A2D_FindService（）的未完成调用；应用程序在再次调用函数之前必须等待回调。
**
**                  输入参数：service_uuid：表示SRC或SNK。
**
**                      bd_addr:对等设备的bd地址。
**
**                      p_db：指向初始化发现数据库的信息的指针。
**
**                      p_cback：指向A2D_FindService（）回调函数的指针。
**
**                  输出参数：无。
**
** 如果函数执行成功，则返回A2D_SUCCESS；如果给定了错误的参数，返回A2D_INVALID_PARAMS。A2D_BUSY（如果发现已在进行中）。如果函数执行失败，则为A2D_FAIL。
**
******************************************************************************/
extern tA2D_STATUS A2D_FindService(UINT16 service_uuid, BD_ADDR bd_addr,
                                   tA2D_SDP_DB_PARAMS *p_db, tA2D_FIND_CBACK *p_cback);

/******************************************************************************
** 函数A2D_SetTraceLevel
**
** 说明设置A2D的跟踪级别。如果传递了0xff，则返回当前跟踪级别。
**
**                  输入参数：new_level：将A2D跟踪设置为：0xff的级别返回当前设置。0—关闭跟踪。>=1-错误。>=2-警告。>=3-API。>=4-事件。>=5-调试。
**
** 如果输入参数为0xff，则返回新跟踪级别或当前跟踪级别。
**
******************************************************************************/
extern UINT8 A2D_SetTraceLevel (UINT8 new_level);

/******************************************************************************
** 函数A2D_BitsSet
**
** 说明检查设置的位数的给定数字。如果设置了一个且只有一个位，则返回A2D_set_ONE_BIT；如果所有位都清除A2D_set_MULTL_BIT；如果设置了多个位
******************************************************************************/
extern UINT8 A2D_BitsSet(UINT8 num);

/*******************************************************************************
** 函数A2D_Init
**
** 说明在堆栈启动时调用此函数以分配控制块（如果使用动态内存），并初始化控制块和跟踪级别。
**
** 返回void
**
*******************************************************************************/
extern bt_status_t A2D_Init(void);

/*******************************************************************************
** 函数A2D_Deinit
**
** 说明在堆栈启动时调用此函数以释放控制块（如果使用动态内存），并释放控制块和跟踪级别。
**
** 返回void
**
*******************************************************************************/
extern void A2D_Deinit(void);

#ifdef __cplusplus
}
#endif

#endif  ///A2D_INCLUDED
#endif /* A2D_API_H */

