/******************************************************************************
 * 版权所有（C）1999-2013 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef SRVC_DIS_API_H
#define SRVC_DIS_API_H

#include "common/bt_target.h"
#include "stack/gatt_api.h"
#include "stack/gattdefs.h"

#define DIS_SUCCESS             GATT_SUCCESS
#define DIS_ILLEGAL_PARAM       GATT_ILLEGAL_PARAMETER
#define DIS_NO_RESOURCES        GATT_NO_RESOURCES
typedef UINT8 tDIS_STATUS;


/*****************************************************************************
**  DIS的数据结构
*****************************************************************************/

#define DIS_ATTR_SYS_ID_BIT         0x0001
#define DIS_ATTR_MODEL_NUM_BIT      0x0002
#define DIS_ATTR_SERIAL_NUM_BIT     0x0004
#define DIS_ATTR_FW_NUM_BIT         0x0008
#define DIS_ATTR_HW_NUM_BIT         0x0010
#define DIS_ATTR_SW_NUM_BIT         0x0020
#define DIS_ATTR_MANU_NAME_BIT      0x0040
#define DIS_ATTR_IEEE_DATA_BIT      0x0080
#define DIS_ATTR_PNP_ID_BIT         0x0100
typedef UINT16  tDIS_ATTR_MASK;

#define DIS_ATTR_ALL_MASK           0xffff

typedef tDIS_ATTR_MASK tDIS_ATTR_BIT ;

typedef struct {
    UINT16      len;
    UINT8       *p_data;
} tDIS_STRING;

typedef struct {
    UINT16       vendor_id;
    UINT16       product_id;
    UINT16       product_version;
    UINT8        vendor_id_src;

} tDIS_PNP_ID;

typedef union {
    UINT64              system_id;
    tDIS_PNP_ID         pnp_id;
    tDIS_STRING         data_str;
} tDIS_ATTR;

#define DIS_MAX_STRING_DATA     7

typedef struct {
    UINT16                  attr_mask;
    UINT64                  system_id;
    tDIS_PNP_ID             pnp_id;
    UINT8                   *data_string[DIS_MAX_STRING_DATA];
} tDIS_VALUE;


typedef void (tDIS_READ_CBACK)(BD_ADDR addr, tDIS_VALUE *p_dis_value);

/*****************************************************************************
**  电池服务使用的数据结构
*****************************************************************************/
typedef struct {
    BD_ADDR remote_bda;
    BOOLEAN need_rsp;
    UINT16  clt_cfg;
} tBA_WRITE_DATA;

#define BA_READ_CLT_CFG_REQ     1
#define BA_READ_PRE_FMT_REQ     2
#define BA_READ_RPT_REF_REQ     3
#define BA_READ_LEVEL_REQ       4
#define BA_WRITE_CLT_CFG_REQ    5

typedef void (tBA_CBACK)(UINT8 app_id, UINT8 event, tBA_WRITE_DATA *p_data);

#define BA_LEVEL_NOTIFY         0x01
#define BA_LEVEL_PRE_FMT        0x02
#define BA_LEVEL_RPT_REF        0x04
typedef UINT8   tBA_LEVEL_DESCR;

typedef struct {
    BOOLEAN         is_pri;
    tBA_LEVEL_DESCR     ba_level_descr;
    tGATT_TRANSPORT transport;
    tBA_CBACK       *p_cback;

} tBA_REG_INFO;

typedef union {
    UINT8       ba_level;
    UINT16      clt_cfg;
    tGATT_CHAR_RPT_REF  rpt_ref;
    tGATT_CHAR_PRES     pres_fmt;
} tBA_RSP_DATA;

/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
/*****************************************************************************
**  服务引擎API
*****************************************************************************/
/*******************************************************************************
** 函数srvc_eng_init
**
** 说明初始化GATT服务引擎，注册GATT应用程序作为中央服务管理。
**
*******************************************************************************/
extern tGATT_STATUS srvc_eng_init (void);


/*****************************************************************************
**  DIS服务器功能
*****************************************************************************/

/*******************************************************************************
** 函数DIS_SrInit
**
** 说明初始化设备信息服务服务器。
**
*******************************************************************************/
extern tDIS_STATUS DIS_SrInit (tDIS_ATTR_MASK dis_attr_mask);
/*******************************************************************************
** 函数DIS_SrUpdate
**
** 说明更新DIS服务器属性值
**
*******************************************************************************/
extern tDIS_STATUS DIS_SrUpdate(tDIS_ATTR_BIT dis_attr_bit, tDIS_ATTR *p_info);
/*****************************************************************************
**  DIS客户端功能
*****************************************************************************/
/*******************************************************************************
** 函数DIS_ReadDISInfo
**
** 说明读取远程设备DIS信息。
**
** 返回void
**
*******************************************************************************/
extern BOOLEAN DIS_ReadDISInfo(BD_ADDR peer_bda, tDIS_READ_CBACK *p_cback,
                               tDIS_ATTR_MASK mask);

/*******************************************************************************
**      BATTERY SERVICE API
*******************************************************************************/
/*******************************************************************************
** 函数电池_实例化
**
** 描述实例化电池服务
**
*******************************************************************************/
extern UINT16 Battery_Instantiate (UINT8 app_id, tBA_REG_INFO *p_reg_info);

/*******************************************************************************
** 功能电池_Rsp
**
** 说明响应电池服务请求
**
*******************************************************************************/
extern void Battery_Rsp (UINT8 app_id, tGATT_STATUS st, UINT8 event, tBA_RSP_DATA *p_rsp);
/*******************************************************************************
** 函数Battery_Notify
**
** 说明发送电池电量通知
**
*******************************************************************************/
extern void Battery_Notify (UINT8 app_id, BD_ADDR remote_bda, UINT8 battery_level);


#ifdef __cplusplus

}
#endif

#endif

