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

/******************************************************************************
 * 这是BTA GATT客户端调用函数的接口文件。
 *
 ******************************************************************************/
#ifndef BTA_GATTC_CO_H
#define BTA_GATTC_CO_H

#include "bta/bta_gatt_api.h"
#include "osi/hash_functions.h"

/*******************************************************************************
** 函数bta_gatc_c_ache_open
**
** 说明当GATT服务器缓存准备好发送时，GATTC执行此调出功能。
**
** 参数server_bda：此缓存的服务器bd地址属于evt:在缓存打开完成时传入的调用事件。conn_id：此缓存操作附加到的连接id。to_save：打开要保存或加载的缓存。
**
** 返回void。
**
*******************************************************************************/
extern tBTA_GATT_STATUS bta_gattc_co_cache_open(BD_ADDR server_bda, BOOLEAN to_save, UINT8 *index);

/*******************************************************************************
** 函数bta_gatc_c_ache_close
**
** 说明当GATT服务器缓存完全写入时，GATTC将执行此调出函数。
**
** 参数server_bda：此缓存的服务器bd地址属于conn_id：此缓存操作附加到的连接id。
**
** 返回void。
**
*******************************************************************************/
extern void bta_gattc_co_cache_close(BD_ADDR server_bda, UINT16 conn_id);

/*******************************************************************************
** 函数bta_gatc_c_ache_save
**
** 说明当服务器缓存可用于保存时，GATT将执行此调出功能。
**
** 参数server_bda：此缓存的服务器bd地址属于evt：在缓存保存完成时传入的调用事件。num_attr：要保存的属性数。p_attr：指向要保存的属性列表的指针。attr_index：开始保存操作的属性索引。conn_id：此缓存操作附加到的连接id。返回
**
*******************************************************************************/
extern void bta_gattc_co_cache_save (BD_ADDR server_bda, UINT16 num_attr,
                              tBTA_GATTC_NV_ATTR *p_attr_list);

/*******************************************************************************
** 函数bta_gatc_c_ache_load
**
** 说明当需要加载服务器缓存时，GATT执行此调出函数。
**
** 参数server_bda：此缓存的服务器bd地址属于evt：在缓存保存完成时传入的调用事件。num_attr：要保存的属性数。attr_index：开始保存操作的属性索引。conn_id：此缓存操作附加到的连接id。返回
**
*******************************************************************************/
extern tBTA_GATT_STATUS bta_gattc_co_cache_load(tBTA_GATTC_NV_ATTR *attr, UINT8 index);

/*******************************************************************************
** 函数bta_gatc_c_ache_reset
**
** 说明此调出函数由GATTC执行，以重置应用程序中的缓存
**
** 参数server_bda：此缓存的服务器bd地址属于
**
** 返回void。
**
*******************************************************************************/
extern void bta_gattc_co_cache_reset(BD_ADDR server_bda);

extern size_t bta_gattc_get_cache_attr_length(UINT8 index);

extern void bta_gattc_co_cache_addr_init(void);

extern void bta_gattc_co_cache_addr_deinit(void);

extern BOOLEAN bta_gattc_co_addr_in_cache(BD_ADDR bda);

extern uint8_t bta_gattc_co_find_addr_in_cache(BD_ADDR bda);

extern uint8_t bta_gattc_co_find_hash_in_cache(hash_key_t hash_key);

extern UINT8 bta_gattc_co_get_addr_num(void);

extern void bta_gattc_co_get_addr_list(BD_ADDR *addr_list);

extern void bta_gattc_co_cache_addr_save(BD_ADDR bd_addr, hash_key_t hash_key);

extern BOOLEAN bta_gattc_co_cache_new_assoc_list(BD_ADDR src_addr, uint8_t index);

extern BOOLEAN bta_gattc_co_cache_append_assoc_addr(BD_ADDR src_addr, BD_ADDR assoc_addr);

extern BOOLEAN bta_gattc_co_cache_remove_assoc_addr(BD_ADDR src_addr, BD_ADDR assoc_addr);

uint8_t* bta_gattc_co_cache_find_src_addr(BD_ADDR assoc_addr, uint8_t *index);

extern BOOLEAN bta_gattc_co_cache_clear_assoc_addr(BD_ADDR src_addr);

#endif /* BTA_GATT_CO_H */

