/******************************************************************************
 * 版权所有（C）2003-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是GATT调用函数的接口文件。
 *
 ******************************************************************************/
#ifndef BTA_GATTC_CI_H
#define BTA_GATTC_CI_H

#include "bta/bta_gatt_api.h"

/*****************************************************************************
**  常量和数据类型
*****************************************************************************/

/* 打开完成事件*/
typedef struct {
    BT_HDR            hdr;
    tBTA_GATT_STATUS  status;
} tBTA_GATTC_CI_EVT;

#define BTA_GATTC_NV_LOAD_MAX   100

/* 读取就绪事件*/
typedef struct {
    BT_HDR              hdr;
    tBTA_GATT_STATUS    status;
    UINT16              num_attr;
    tBTA_GATTC_NV_ATTR  attr[BTA_GATTC_NV_LOAD_MAX];
} tBTA_GATTC_CI_LOAD;


/*****************************************************************************
**  函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
** 函数bta_gatc_c_cache_open
**
** 说明此函数发送一个事件，指示服务器缓存打开完成。
**
** 参数server_bda-此缓存的服务器bda。状态-如果数据缓冲区已满，则为BTA_GATT_OK；如果发生错误，则为BTA_GATT_FAIL。
**
** 返回void
**
*******************************************************************************/
extern void bta_gattc_ci_cache_open(BD_ADDR server_bda, UINT16 evt,
                                    tBTA_GATT_STATUS status, UINT16 conn_id);

/*******************************************************************************
** 函数bta_gatc_c_cache_load
**
** 说明此函数向BTA发送一个事件，指示手机已加载服务器缓存并准备将其发送到堆栈。
**
** 参数server_bda-此缓存的服务器bda。num_bytes_read-读入read callout函数中指定的缓冲区的字节数。状态-如果数据缓冲区已满，则为BTA_GATT_OK；如果发生错误，则为BTA_GATT_FAIL。
**
** 返回void
**
*******************************************************************************/
extern void bta_gattc_ci_cache_load(BD_ADDR server_bda, UINT16 evt,
                                    UINT16 num_attr, tBTA_GATTC_NV_ATTR *p_atrr,
                                    tBTA_GATT_STATUS status, UINT16 conn_id);

/*******************************************************************************
** 函数bta_gatc_ci_save
**
** 说明此功能向BTA发送一个事件，指示手机已保存服务器缓存。
**
** 参数server_bda-此缓存的服务器bda。状态-如果数据缓冲区已满，则为BTA_GATT_OK；如果发生错误，则为BTA_GATT_FAIL。
**
** 返回void
**
*******************************************************************************/
extern void bta_gattc_ci_cache_save(BD_ADDR server_bda, UINT16 evt,
                                    tBTA_GATT_STATUS status, UINT16 conn_id);


#ifdef __cplusplus
}
#endif

#endif /* BTA_GATTC_CI_H */

