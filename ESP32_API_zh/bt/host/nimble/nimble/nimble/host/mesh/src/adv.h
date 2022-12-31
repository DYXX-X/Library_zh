/*  蓝牙网格*/

/*
 * 版权所有（c）2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __ADV_H__
#define __ADV_H__

/* 单个数据类型的最大广告数据负载*/
#include "mesh/mesh.h"

#define BT_MESH_ADV(om) (*(struct bt_mesh_adv **) OS_MBUF_USRHDR(om))

#define BT_MESH_ADV_DATA_SIZE 31

/* 用户数据是指向结构bt_mesh_adv的指针（4字节）*/
#define BT_MESH_ADV_USER_DATA_SIZE (sizeof(struct bt_mesh_adv *))

#define BT_MESH_MBUF_HEADER_SIZE (sizeof(struct os_mbuf_pkthdr) + \
                                    BT_MESH_ADV_USER_DATA_SIZE +\
				    sizeof(struct os_mbuf))

enum bt_mesh_adv_type
{
	BT_MESH_ADV_PROV,
	BT_MESH_ADV_DATA,
	BT_MESH_ADV_BEACON,
	BT_MESH_ADV_URI,
};

typedef void (*bt_mesh_adv_func_t)(struct os_mbuf *buf, u16_t duration,
				   int err, void *user_data);

struct bt_mesh_adv {
	const struct bt_mesh_send_cb *cb;
	void *cb_data;

	u8_t      type:2,
		  busy:1;
	u8_t      xmit;

	/* 用于传输层段发送*/
	struct {
		u8_t attempts;
	} seg;

	u8_t flags;

	int ref_cnt;
	struct ble_npl_event ev;
};

typedef struct bt_mesh_adv *(*bt_mesh_adv_alloc_t)(int id);

/* xmit_count：重传次数，即0==1次传输*/
struct os_mbuf *bt_mesh_adv_create(enum bt_mesh_adv_type type, u8_t xmit,
				   s32_t timeout);

struct os_mbuf *bt_mesh_adv_create_from_pool(struct os_mbuf_pool *pool,
					     bt_mesh_adv_alloc_t get_id,
					     enum bt_mesh_adv_type type,
					     u8_t xmit, s32_t timeout);

void bt_mesh_adv_send(struct os_mbuf *buf, const struct bt_mesh_send_cb *cb,
		      void *cb_data);

void bt_mesh_adv_update(void);

void bt_mesh_adv_init(void);

int bt_mesh_scan_enable(void);

int bt_mesh_scan_disable(void);

int ble_adv_gap_mesh_cb(struct ble_gap_event *event, void *arg);
#endif

