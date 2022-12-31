#ifndef __ESP_BLUFI_H__
#define __ESP_BLUFI_H__

#include "esp_blufi_api.h"
#include "esp_err.h"

#ifdef CONFIG_BT_NIMBLE_ENABLED
#include "nimble/ble.h"
#include "modlog/modlog.h"
#endif

#ifdef CONFIG_BT_BLUEDROID_ENABLED
#include "esp_gap_ble_api.h"
#endif

#define BLUFI_APP_UUID      0xFFFF
#define BLUFI_DEVICE_NAME            "BLUFI_DEVICE"

#ifdef CONFIG_BT_NIMBLE_ENABLED
struct ble_hs_cfg;
struct ble_gatt_register_ctxt;
struct gatt_value {
    struct os_mbuf *buf;
    uint16_t val_handle;
    uint8_t type;
    void *ptr;
};
#define SERVER_MAX_VALUES       3
#define MAX_VAL_SIZE            512
extern struct gatt_value gatt_values[SERVER_MAX_VALUES];
/* GATT服务器回调*/
void esp_blufi_gatt_svr_register_cb(struct ble_gatt_register_ctxt *ctxt, void *arg);

/* 初始化gatt服务器*/
int esp_blufi_gatt_svr_init(void);
void esp_blufi_btc_init(void);
#endif

#ifdef CONFIG_BT_BLUEDROID_ENABLED
/**
 * @brief           关闭远程设备的连接。
 *
 * @param[in]       gatts_if: GATT服务器访问接口
 * @param[in]       conn_id: 要关闭的连接ID。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
esp_err_t esp_blufi_close(uint8_t gatts_if, uint16_t conn_id);
void esp_blufi_gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
#endif

/* 初始化blufi配置文件*/
uint8_t esp_blufi_init(void);

/* 开始广告宣传*/
void bleprph_advertise(void);

/* 发送通知*/
void esp_blufi_send_notify(void *arg);

/* 对blufi进行去初始化*/
void esp_blufi_deinit(void);
/* 断开*/
void esp_blufi_disconnect(void);

/* 停止广告*/
void esp_blufi_adv_stop(void);

/* 启动广告*/
void esp_blufi_adv_start(void);

void esp_blufi_send_encap(void *arg);

#endif/* _ESP_BLUFI_ */

