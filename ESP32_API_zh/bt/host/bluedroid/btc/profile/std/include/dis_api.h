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

/*******************************************************************************
** 配置文件文件夹的头文件。
**
********************************************************************************/

#ifndef SRVC_DIS_API_H
#define SRVC_DIS_API_H

#include "common/bt_target.h"
#include "stack/gatt_api.h"
#include "stack/gattdefs.h"
#include "esp_gatts_api.h"

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

#define DIS_MAX_NUM_INC_SVR         0
#define DIS_MAX_CHAR_NUM            9
#define DIS_MAX_ATTR_NUM            (DIS_MAX_CHAR_NUM * 2 + DIS_MAX_NUM_INC_SVR + 1)

#ifndef DIS_ATTR_DB_SIZE
#define DIS_ATTR_DB_SIZE            GATT_DB_MEM_SIZE(DIS_MAX_NUM_INC_SVR, DIS_MAX_CHAR_NUM, 0)
#endif

#define DIS_SYSTEM_ID_SIZE          8
#define DIS_PNP_ID_SIZE             7


typedef struct {
    UINT16      uuid;
    UINT16      handle;
} tDIS_DB_ENTRY;

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

//typedef void（tDIS_READ_CBACK）（BD_ADDR地址，tDIS_VALUE*p_dis_VALUE）；

typedef struct {
    tDIS_DB_ENTRY           dis_attr[DIS_MAX_CHAR_NUM];
    tDIS_VALUE              dis_value;

//    tDIS_READ_CBACK*p_READ_dis_CBACK；

    UINT16                  service_handle;
    UINT16                  max_handle;

    bool                    enabled;

    //  UINT8 dis_read_uuid_idx；
    //  tDIS_ATTR_MASK请求_任务；
} tDIS_CB;

/*****************************************************************************
**  电池服务使用的数据结构
*****************************************************************************/

#ifndef BA_MAX_INT_NUM
#define BA_MAX_INT_NUM  4
#endif

#define BATTERY_LEVEL_SIZE   1

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

typedef void (tBA_CBACK)(UINT32 trans_id, UINT16 conn_id, UINT8 app_id, UINT8 event, tBA_WRITE_DATA *p_data);

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

typedef struct {
    UINT8       app_id;
    UINT16      ba_level_hdl;
    UINT16      clt_cfg_hdl;
    UINT16      rpt_ref_hdl;
    UINT16      pres_fmt_hdl;

    tBA_CBACK   *p_cback;

    UINT16      pending_handle;
    //UINT8挂起_ clcb_idx；
    UINT8       pending_evt;
} tBA_INST;

typedef struct {
    tBA_INST        battery_inst[BA_MAX_INT_NUM];
    UINT8           inst_id;
    bool            enabled;
} tBATTERY_CB;
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
//外部tGATT_STATUS srvc_eng_init（无效）；


/*****************************************************************************
**  DIS服务器功能
*****************************************************************************/

extern bool dis_valid_handle_range(UINT16 handle);
/*******************************************************************************
** 功能DIS_Init
**
** 说明初始化设备信息服务服务器。
**
*******************************************************************************/
extern void DIS_Init (tBTA_GATTS_IF gatt_if, tDIS_ATTR_MASK dis_attr_mask);
/*******************************************************************************
** 函数DIS_SrUpdate
**
** 说明更新DIS服务器属性值
**
*******************************************************************************/
extern tDIS_STATUS DIS_SrUpdate(tDIS_ATTR_BIT dis_attr_bit, tDIS_ATTR *p_info);
/*******************************************************************************
** 函数dis_AddChar
**
** 描述为数据添加特性
**
*******************************************************************************/
extern void dis_AddChar(UINT16 service_id);
/*******************************************************************************
**   读取属性值
**
**   处理读取DIS属性请求。
*******************************************************************************/

extern void dis_s_read_attr_value (tGATTS_DATA *p_data, tGATT_VALUE *p_value,
                                   UINT32 trans_id, UINT16 conn_id);
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
//外部BOOLEAN DIS_ReadDISInfo（BD_ADDR peer_bda，tDIS_READ_CBACK*p_CBACK，
//                              tDIS_ATTR_MASK掩码）；

/*******************************************************************************
**      BATTERY SERVICE API
*******************************************************************************/
/***************************************************************
** 函数bas_register
**
** 电池服务的描述注册应用程序
**
****************************************************************/
extern void bas_register(void);
/***************************************************************
** 函数bas_init
**
** 描述寄存器电池服务
**
****************************************************************/
extern void bas_init(tBTA_GATTS_IF gatt_if, UINT16 app_id);

/***************************************************************
** 函数bas_AddChar
**
** 蓄电池服务的描述和添加特性
**
****************************************************************/
extern void bas_AddChar(UINT16 service_id, tBT_UUID *char_uuid);
/***************************************************************
** 函数bas_AddCharDescr
**
** 描述如果需要，为电池服务添加描述符
**
****************************************************************/
extern void bas_AddCharDescr(UINT16 service_id, UINT16 attr_id);
/***************************************************************
** 函数bas_service_cmpl
**
** 描述创建电池服务完成
**
****************************************************************/
extern void bas_service_cmpl(UINT16 service_id, tBTA_GATT_STATUS status);
/*******************************************************************************
** 功能电池_Rsp
**
** 说明响应电池服务请求
**
*******************************************************************************/
extern void Battery_Rsp (UINT32 trans_id, UINT16 conn_id, UINT8 app_id,
                         tGATT_STATUS st, UINT8 event, tBA_RSP_DATA *p_rsp);
/*******************************************************************************
** 函数Battery_Notify
**
** 说明发送电池电量通知
**
*******************************************************************************/
extern void Battery_Notify (UINT16 conn_id, UINT8 app_id, BD_ADDR remote_bda, UINT8 battery_level);

/*****************************************************************************
** 函数bas_s_read_attr_value
**
** 描述客户端发送读取请求时将调用它
******************************************************************************/
extern void bas_s_read_attr_value(tGATTS_DATA *p_data, UINT32 trans_id, UINT16 conn_id);
/*****************************************************************************
** 函数bas_s_write_attr_value
**
** 描述客户端发送写请求时将调用它
******************************************************************************/
extern void bas_s_write_attr_value(tGATTS_DATA *p_data, UINT32 trans_id,
                                   UINT16 conn_id, BD_ADDR bd_addr);

extern void gatts_server_test(void);
#ifdef __cplusplus

}
#endif

#endif

