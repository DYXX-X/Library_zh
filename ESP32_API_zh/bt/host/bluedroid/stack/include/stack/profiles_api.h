/******************************************************************************
 * 版权所有（C）2009-2013 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef PROFILES_API_H
#define PROFILES_API_H

#include "common/bt_target.h"
#include "stack/btm_api.h"

/*****************************************************************************
**  常量
*****************************************************************************/
#define BT_PASS         0   /* 用于一般成功的函数返回*/

/***端口实体传回8位错误；将使用高位字节偏移***/
#define PORT_ERR_GRP    0x0000          /* 端口实体的基本偏移量*/
#define GAP_ERR_GRP     0x0100          /* GAP剖面的基准偏移*/
#define SPP_ERR_GRP     0x0200          /* 串行端口配置文件的基本偏移量*/
#define HCRP_ERR_GRP    0x0300          /* HCRP的基本偏移*/
#define HCRPM_ERR_GRP   0x0400          /* HCRPM的基本偏移*/

/* #定义HSP2_ERR_GRP 0x0F00*/

/* 安全级别定义（tBT_security）*/
#define BT_USE_DEF_SECURITY         0
#define BT_SEC_MODE_NONE            BTM_SEC_MODE_NONE
#define BT_SEC_MODE_SERVICE         BTM_SEC_MODE_SERVICE
#define BT_SEC_MODE_LINK            BTM_SEC_MODE_LINK

/* 安全掩码定义（tBT_security）*/
/* 将以下定义合并在一起形成安全要求*/
#define BT_SEC_IN_AUTHORIZE         BTM_SEC_IN_AUTHORIZE         /* 入站呼叫需要授权*/
#define BT_SEC_IN_AUTHENTICATE      BTM_SEC_IN_AUTHENTICATE      /* 入站呼叫需要身份验证*/
#define BT_SEC_IN_ENCRYPT           BTM_SEC_IN_ENCRYPT           /* 入站呼叫需要加密*/
#define BT_SEC_OUT_AUTHORIZE        BTM_SEC_OUT_AUTHORIZE        /* 出站呼叫需要授权*/
#define BT_SEC_OUT_AUTHENTICATE     BTM_SEC_OUT_AUTHENTICATE     /* 出站呼叫需要身份验证*/
#define BT_SEC_OUT_ENCRYPT          BTM_SEC_OUT_ENCRYPT          /* 出站呼叫需要加密*/


/*****************************************************************************
**  类型定义
*****************************************************************************/

/*
** 安全定义以下定义用于指示服务的安全要求。
*/
typedef struct {
    UINT8   level;
    UINT8   mask;
} tBT_SECURITY;

#endif  /* PROFILES_API_H */

