/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _SIMPLE_BLE_
#define _SIMPLE_BLE_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <esp_gap_ble_api.h>
#include <esp_gatts_api.h>

typedef void (simple_ble_cb_t)(esp_gatts_cb_event_t event, esp_gatt_if_t p_gatts_if, esp_ble_gatts_cb_param_t *param);

/**
 * 该结构填充了创建BLE实例所需的详细信息。它需要函数指针、广告参数和gatt描述表
 */
typedef struct {
    /**要显示给扫描ESP32的设备的名称*/
    const char *device_name;
    /**原始广告数据*/
    uint8_t *raw_adv_data_p;
    uint8_t raw_adv_data_len;
    /**原始扫描响应数据*/
    uint8_t *raw_scan_rsp_data_p;
    uint8_t raw_scan_rsp_data_len;
    /**用于配置广告性质的参数*/
    esp_ble_adv_params_t adv_params;
    /**由服务和特征所需的配置组成的描述符表*/
    esp_gatts_attr_db_t *gatt_db;
    /**gatt_db描述符表中的条目数*/
    ssize_t gatt_db_count;
    /**BLE读取回调*/
    simple_ble_cb_t *read_fn;
    /**BLE写入回调*/
    simple_ble_cb_t *write_fn;
    /**BLE exec写入回调*/
    simple_ble_cb_t *exec_write_fn;
    /**客户端断开连接回调*/
    simple_ble_cb_t *disconnect_fn;
    /**客户端连接回调*/
    simple_ble_cb_t *connect_fn;
    /**MTU集合回调*/
    simple_ble_cb_t *set_mtu_fn;
    /* BLE键合*/
     unsigned ble_bonding:1;
} simple_ble_cfg_t;


/** 初始化一个简单的ble连接
 *
 * 此函数分配内存并返回指向配置结构的指针。
 *
 * @return simple_ble_cfg_t*指向配置结构的指针
 */
simple_ble_cfg_t *simple_ble_init(void);

/** 取消分配内存
 *
 * 此函数用于释放配置结构的内存。
 *
 * @return ESP_OK
 */
esp_err_t simple_ble_deinit(void);

/** 启动BLE服务
 *
 * 此函数调用GATT和GAP API，根据配置结构中存储的参数初始化BLE服务。在该功能结束时，应能够使用BLE扫描并连接到ESP32设备。此API将MTU大小设置为500（这不是配置结构的一部分）
 *
 * @return 成功时为ESP_OK，失败时为相应的错误代码
 */
esp_err_t simple_ble_start(simple_ble_cfg_t *cfg);

/** 停止BLE服务
 *
 * 调用此API以停止BLE服务。这包括禁用和卸载bluedroid和bt控制器的调用。
 *
 * @return 成功时为ESP_OK，失败时为相应的错误代码
 */
esp_err_t simple_ble_stop(void);

/** 将句柄转换为特征的128位UUID
 *
 * 此函数可以很容易地用于获取已创建的特性的相应UUID，以及我们只有其句柄的特性。
 *
 * @return 在句柄无效的情况下，指向特性为NULL的UUID的指针
 */
const uint8_t *simple_ble_get_uuid128(uint16_t handle);

#endif /* _SIMPLE_BLE_ */

