/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <protocomm.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * BLE设备名称不能大于此值31字节（最大扫描响应大小）-1字节（长度）-1字节
 */
#define MAX_BLE_DEVNAME_LEN 29
#define BLE_UUID128_VAL_LENGTH  16
 /**
 * 理论上，最大制造商长度限制与BLE设备名称相同，即31字节（最大扫描响应大小）-1字节（长度）-1字节）=29字节。然而，制造商数据与扫描响应中的BLE设备名一致。因此，了解实际长度应小于（29-（BLE设备名称长度）-2）非常重要。*/
#define MAX_BLE_MANUFACTURER_DATA_LEN 29

/**
 * @brief   该结构将协议通信层所需的处理程序映射到UUID，UUID用于从智能手机或类似的客户端设备中唯一标识BLE特征。
 */
typedef struct name_uuid {
    /**
     * 传递到protocomm层的处理程序的名称
     */
    const char *name;

    /**
     * 要分配给映射到处理程序的BLE特性的UUID
     */
    uint16_t uuid;
} protocomm_ble_name_uuid_t;

/**
 * @brief   protocomm BLE服务的配置参数
 */
typedef struct protocomm_ble_config {
    /**
     * 配置时广播的BLE设备名称
     */
    char         device_name[MAX_BLE_DEVNAME_LEN];

    /**
     * 配置服务的128位UUID
     */
    uint8_t      service_uuid[BLE_UUID128_VAL_LENGTH];

    /**
     * 广告中的BLE设备制造商数据指针
     */
    uint8_t      *manufacturer_data;

    /**
     * BLE设备制造商在广告中的数据长度
     */
    ssize_t      manufacturer_data_len;

    /**
     * 名称UUID查找表中的条目数
     */
    ssize_t      nu_lookup_count;

    /**
     * 指向名称UUID查找表的指针
     */
    protocomm_ble_name_uuid_t *nu_lookup;

    /* BLE键合*/
    unsigned ble_bonding:1;

} protocomm_ble_config_t;

/**
 * @brief   启动基于蓝牙低能耗的传输层以进行资源调配
 *
 * 初始化并启动配置所需的BLE服务。这包括BLE特性/服务的初始化。
 *
 * @param[in] pc        从Protocomm_new（）获取的Protocomm实例指针
 * @param[in] config    指向用于初始化BLE的配置结构的指针
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：简单BLE启动错误
 *  -ESP_ERR_NO_MEM:为内部资源分配内存时出错
 *  -ESP_ERR_INVALID_STATE:表配置中出错
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t protocomm_ble_start(protocomm_t *pc, const protocomm_ble_config_t *config);

/**
 * @brief   停止基于蓝牙低能传输层的资源调配
 *
 * 停止负责基于BLE的交互的服务/任务
 *
 * @note    您可能希望选择性地从蓝牙中回收内存。在这种情况下，请参阅“esp_bt_mem_release”的文档。
 *
 * @param[in] pc    传递给protocomm_ble_start（）的相同protocomm实例
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：简单BLE停止错误
 *  -ESP_ERR_INVALID_ARG:协议命令实例为空/不正确
 */
esp_err_t protocomm_ble_stop(protocomm_t *pc);

#ifdef __cplusplus
}
#endif

