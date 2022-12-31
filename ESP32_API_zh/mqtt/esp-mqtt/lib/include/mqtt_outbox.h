/*
 * 此文件受文件“LICENSE”中定义的条款和条件约束，该文件是源代码包的一部分。Tuan PM＜Tuan PM at live dot com＞
 */
#ifndef _MQTT_OUTOBX_H_
#define _MQTT_OUTOBX_H_
#include "platform.h"
#include "esp_err.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct outbox_item;

typedef struct outbox_list_t *outbox_handle_t;
typedef struct outbox_item *outbox_item_handle_t;
typedef struct outbox_message *outbox_message_handle_t;
typedef long long outbox_tick_t;

typedef struct outbox_message {
    uint8_t *data;
    int len;
    int msg_id;
    int msg_qos;
    int msg_type;
    uint8_t *remaining_data;
    int remaining_len;
} outbox_message_t;

typedef enum pending_state {
    QUEUED,
    TRANSMITTED,
    ACKNOWLEDGED,
    CONFIRMED
} pending_state_t;

outbox_handle_t outbox_init(void);
outbox_item_handle_t outbox_enqueue(outbox_handle_t outbox, outbox_message_handle_t message, outbox_tick_t tick);
outbox_item_handle_t outbox_dequeue(outbox_handle_t outbox, pending_state_t pending, outbox_tick_t *tick);
outbox_item_handle_t outbox_get(outbox_handle_t outbox, int msg_id);
uint8_t *outbox_item_get_data(outbox_item_handle_t item,  size_t *len, uint16_t *msg_id, int *msg_type, int *qos);
esp_err_t outbox_delete(outbox_handle_t outbox, int msg_id, int msg_type);
esp_err_t outbox_delete_msgid(outbox_handle_t outbox, int msg_id);
esp_err_t outbox_delete_msgtype(outbox_handle_t outbox, int msg_type);
esp_err_t outbox_delete_item(outbox_handle_t outbox, outbox_item_handle_t item);
int outbox_delete_expired(outbox_handle_t outbox, outbox_tick_t current_tick, outbox_tick_t timeout);
/**
 * @brief 删除返回其邮件id的单个过期邮件
 *
 * @return 已删除邮件的邮件id，如果发件箱中没有过期邮件，则为-1
 */
int outbox_delete_single_expired(outbox_handle_t outbox, outbox_tick_t current_tick, outbox_tick_t timeout);

esp_err_t outbox_set_pending(outbox_handle_t outbox, int msg_id, pending_state_t pending);
esp_err_t outbox_set_tick(outbox_handle_t outbox, int msg_id, outbox_tick_t tick);
int outbox_get_size(outbox_handle_t outbox);
void outbox_destroy(outbox_handle_t outbox);
void outbox_delete_all_items(outbox_handle_t outbox);

#ifdef  __cplusplus
}
#endif
#endif

