/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _CLIENT_COMMON_H_
#define _CLIENT_COMMON_H_

#include "mesh_access.h"

#ifdef __cplusplus
extern "C" {
#endif

/**客户端模型操作码对表*/
typedef struct {
    uint32_t cli_op;    /* 客户端消息操作码*/
    uint32_t status_op; /* 对应的状态消息操作码*/
} bt_mesh_client_op_pair_t;

/**客户端模型用户数据上下文*/
typedef struct {
    /**指向客户端模型的指针*/
    struct bt_mesh_model *model;

    /**操作码对表的大小*/
    int op_pair_size;

    /**指向操作码对表的指针*/
    const bt_mesh_client_op_pair_t *op_pair;

    /**
     * @brief 此函数是一个回调函数，用于将收到的未经请求的消息推送到应用程序层。
     *
     * @param[in]  opcode: 接收状态消息的操作码
     * @param[in]  model:  与状态消息关联的模型
     * @param[in]  ctx:    状态消息的上下文信息
     * @param[in]  buf:    缓冲区包含状态消息值
     *
     * @return 没有一个
     */
    void (*publish_status)(uint32_t opcode, struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx, struct net_buf_simple *buf);

    /**指向客户端模型内部数据的指针*/
    void *internal_data;

    /**客户端模型所属设备的角色*/
    uint8_t msg_role;
} bt_mesh_client_user_data_t;

/**客户端模型内部数据上下文*/
typedef struct  {
    sys_slist_t queue;
} bt_mesh_client_internal_data_t;

/**客户端模型发送消息相关上下文*/
typedef struct {
    sys_snode_t client_node;
    struct bt_mesh_msg_ctx ctx;     /* 消息上下文*/
    uint32_t opcode;                /* 消息操作码*/
    uint32_t op_pending;            /* 预期的状态消息操作码*/
    int32_t  timeout;               /* 计算的消息超时值*/
    struct k_delayed_work timer;    /* 用于获得响应的时间。仅供内部使用。*/
} bt_mesh_client_node_t;

/**客户端模型发送消息参数*/
typedef struct {
    uint32_t opcode;                    /* 消息操作码*/
    struct bt_mesh_model *model;        /* 指向客户端模型的指针*/
    struct bt_mesh_msg_ctx ctx;         /* 消息上下文*/
    int32_t msg_timeout;                /* 获得相应响应的时间*/
    uint8_t msg_role;                   /* 设备的角色（节点/配置器）*/
    const struct bt_mesh_send_cb *cb;   /* 用户定义的回调函数*/
    void *cb_data;                      /* 用户定义的回调值*/
} bt_mesh_client_common_param_t;

void bt_mesh_client_model_lock(void);

void bt_mesh_client_model_unlock(void);

int bt_mesh_client_init(struct bt_mesh_model *model);

int bt_mesh_client_deinit(struct bt_mesh_model *model);

/**
 * @brief 检查客户端模型收到的消息是否为发布消息
 *
 * @param model     消息所属的网格（客户端）模型。
 * @param ctx       消息上下文，包括密钥、TTL等。
 * @param buf       消息缓冲区
 * @param need_pub  指示消息是否作为发布消息发送到应用层
 * @return 成功时为0，失败时为（负）错误代码。
 */
bt_mesh_client_node_t *bt_mesh_is_client_recv_publish_msg(struct bt_mesh_model *model,
                                                          struct bt_mesh_msg_ctx *ctx,
                                                          struct net_buf_simple *buf, bool need_pub);

int bt_mesh_client_send_msg(bt_mesh_client_common_param_t *param,
                            struct net_buf_simple *msg, bool need_ack,
                            k_work_handler_t timer_handler);

int bt_mesh_client_free_node(bt_mesh_client_node_t *node);

int bt_mesh_client_clear_list(void *data);

/**
 * @brief 设置供内部使用的客户端模型的角色。
 *
 * @param[in] model: 指向客户端模型的指针
 * @param[in] role:  设备的作用
 *
 * @return 零-成功，否则-失败
 */
int bt_mesh_set_client_model_role(struct bt_mesh_model *model, uint8_t role);

#ifdef __cplusplus
}
#endif

#endif /* _CLIENT_COMMON_H_ */

