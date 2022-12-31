/** @file
 *  @brief 蓝牙网格代理API。
 */

/*
 * 版权所有（c）2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef __BT_MESH_PROXY_H
#define __BT_MESH_PROXY_H

/**
 * @brief 蓝牙网格代理
 * @defgroup bt_mesh_proxy蓝牙网格代理
 * @ingroup bt_网格@{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 使用节点标识启用广告。
 *
 * 此API要求已启用GATT代理支持。一旦被调用，每个子网将在接下来的60秒内使用节点标识开始广告。
 *
 * @return 成功时为0，失败时为（负）错误代码。
 */
int bt_mesh_proxy_identity_enable(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __BT_MESH_PROXY_H */

