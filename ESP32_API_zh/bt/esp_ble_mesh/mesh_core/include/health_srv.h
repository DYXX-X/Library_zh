/** @file
 *  @brief Bluetooth Mesh Health Server模型API。
 */

/*
 * SPDX文件版权文本：2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _BLE_MESH_HEALTH_SRV_H_
#define _BLE_MESH_HEALTH_SRV_H_

#include "mesh_access.h"

/**
 * @brief Bluetooth Mesh Health Server模型
 * @defgroup bt_mesh_health_srv Bluetooth mesh health Server型号
 * @ingroup bt_网格@{
 */

#ifdef __cplusplus
extern "C" {
#endif

struct bt_mesh_health_srv_cb {
    /* 清除已登记的故障*/
    void (*fault_clear)(struct bt_mesh_model *model, uint16_t company_id);

    /* 运行特定测试*/
    void (*fault_test)(struct bt_mesh_model *model, uint8_t test_id,
                       uint16_t company_id);

    /* 注意：*/
    void (*attn_on)(struct bt_mesh_model *model, uint8_t time);

    /* 注意事项关闭*/
    void (*attn_off)(struct bt_mesh_model *model);
};

/** @def BLE_MESH_HEALTH_PUB_DEFINE
 *
 *  用于定义健康发布上下文的帮助程序
 *
 *  @param _name 给发布上下文变量的名称。
 *  @param _max_faults 元素可能具有的最大故障数。
 */
#define BLE_MESH_HEALTH_PUB_DEFINE(_name, _max_faults) \
    BLE_MESH_MODEL_PUB_DEFINE(_name, NULL, (1 + 3 + (_max_faults)))

struct bt_mesh_health_test {
    uint8_t  id_count;         /* 健康自检ID的数量*/
    const uint8_t *test_ids;   /* 运行状况自检ID阵列*/
    uint16_t company_id;       /* 用于识别健康故障状态的公司ID*/
    uint8_t  prev_test_id;     /* 当前执行的测试id最多*/
    uint8_t  curr_faults[32];  /* 电流故障阵列*/
    uint8_t  reg_faults[32];   /* 记录的故障阵列*/
} __attribute__((packed));

/**Mesh Health Server模型上下文*/
struct bt_mesh_health_srv {
    struct bt_mesh_model *model;

    /* 可选回调结构*/
    struct bt_mesh_health_srv_cb cb;

    /* 注意计时器状态*/
    struct k_delayed_work attn_timer;

    /* 注意计时器启动标志*/
    bool attn_timer_start;

    /* 运行状况服务器故障测试*/
    struct bt_mesh_health_test test;
};

extern const struct bt_mesh_model_op bt_mesh_health_srv_op[];
extern const struct bt_mesh_model_cb bt_mesh_health_srv_cb;

/** @def BLE_MESH_MODEL_HEALTH_SRV
 *
 *  定义新的健康服务器模型。注意，对于应用程序希望在其上具有健康服务器模型的每个元素，需要重复此API。每个实例还需要唯一的bt_mesh_health_srv和bt_mesh_model_pub上下文。
 *
 *  @param srv 指向唯一结构bt_mesh_health_srv的指针。
 *  @param pub 指向唯一结构bt_mesh_model_pub的指针。
 *
 *  @return 新的网格模型实例。
 */
#define BLE_MESH_MODEL_HEALTH_SRV(srv, pub)             \
        BLE_MESH_MODEL_CB(BLE_MESH_MODEL_ID_HEALTH_SRV,    \
            bt_mesh_health_srv_op, pub, srv, &bt_mesh_health_srv_cb)

int bt_mesh_fault_update(struct bt_mesh_elem *elem);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __BLE_MESH_HEALTH_SRV_H */

