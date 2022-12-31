/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/** @file
 *  @brief 蓝牙网格模型通用API。
 */

#ifndef _BLE_MESH_COMMON_H_
#define _BLE_MESH_COMMON_H_

#include <stddef.h>
#include <stdlib.h>

#include "esp_attr.h"
#include "esp_heap_caps.h"

#include "mesh_byteorder.h"
#include "mesh_ffs.h"
#include "mesh_trace.h"
#include "mesh_mutex.h"
#include "mesh_access.h"

#ifdef __cplusplus
extern "C" {
#endif

IRAM_ATTR void *bt_mesh_malloc(size_t size);

IRAM_ATTR void *bt_mesh_calloc(size_t size);

IRAM_ATTR void bt_mesh_free(void *ptr);

/**
 * @brief 此函数分配内存以存储传出消息。
 *
 * @param[in] size: 分配用于存储消息值的内存长度
 *
 * @return NULL失败，net_buf_simple结构的指针成功
 */
struct net_buf_simple *bt_mesh_alloc_buf(uint16_t size);

/**
 * @brief 此函数释放为传出消息分配的内存。
 *
 * @param[in] buf: 指向要释放的net_buf_simple结构的指针
 *
 * @return 没有一个
 */
void bt_mesh_free_buf(struct net_buf_simple *buf);

/**
 * @brief 此函数获取堆栈内部使用的设备角色。
 *
 * @Note  目前Provisioner仅支持客户端模型，Node支持客户端模型和服务器模型。因此，如果srv_send设置为TRUE，那么将返回角色NODE。
 *
 * @param[in] model:    指向模型结构的指针
 * @param[in] srv_send: 指示消息是否由服务器模型发送
 *
 * @return 0-节点，1-配置器
 */
uint8_t bt_mesh_get_device_role(struct bt_mesh_model *model, bool srv_send);

int bt_mesh_rand(void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_COMMON_H_ */

