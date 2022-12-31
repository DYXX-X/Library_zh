// 2020浓缩咖啡系统（上海）有限公司版权所有。
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/ringbuf.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "tusb.h"
#include "tinyusb_types.h"

/* CDC分类
   ********************************************************************* */
typedef enum {
    TINYUSB_CDC_DATA =          0x00,
} cdc_data_sublcass_type_t; // CDC120规格

/* 注意：其他分类在文件components\tinyusb\tinyusb\src\class\cdc\cdc中表示。小时*/

/***********************************************************************CDC分类*/
/* 结构体
   ********************************************************************* */
typedef struct {
    tinyusb_usbdev_t usb_dev;                           /*!< 要设置的USB设备*/
    tusb_class_code_t cdc_class;                 /*!< CDC设备类别：通信或数据设备*/
    union {
        cdc_comm_sublcass_type_t comm_subclass; /*!< 通信设备子类：AMC、ECM等。*/
        cdc_data_sublcass_type_t data_subclass; /*!< 数据设备只有一个子类。*/
    } cdc_subclass;                                     /*!< CDC设备子类，根据CDC v.1.20通信设备类定义*/
} tinyusb_config_cdc_t;                                 /*!< CDC设备的主要配置结构*/

typedef struct {
    tinyusb_usbdev_t usb_dev;                           /*!< 用于实例的USB设备*/
    tusb_class_code_t type;
    union {
        cdc_comm_sublcass_type_t comm_subclass; /*!< 通信设备子类：AMC、ECM等。*/
        cdc_data_sublcass_type_t data_subclass; /*!< 数据设备只有一个子类。*/
    } cdc_subclass;                                     /*!< CDC设备子类，根据CDC v.1.20通信设备类定义*/
    void *subclass_obj;  /*!< 动态分配的子类特定对象*/
} esp_tusb_cdc_t;
/***********************************************************************结构*/
/* 功能
   ********************************************************************* */
/**
 * @brief 正在初始化CDC基本对象
 * @param itf -CDC对象的编号
 * @param cfg -CDC配置结构
 *
 * @return esp_err_t esp_OK或esp_FAIL
 */
esp_err_t tinyusb_cdc_init(int itf, const tinyusb_config_cdc_t *cfg);


/**
 * @brief 正在取消初始化CDC。清理其对象
 * @param itf -CDC对象的编号
 * @return esp_err_t esp_OK、esp_err_INVALID_ARG、esp_err _INVALID_STATE
 *
 */
esp_err_t tinyusb_cdc_deinit(int itf);


/**
 * @brief 检查CDC是否已初始化并准备好进行交互
 *
 * @return 真或假
 */
bool tinyusb_cdc_initialized(int itf);


/**
 * @brief CDC设备的返回接口
 *
 * @param itf_num
 * @return esp_tusb_cdc_t*指向接口的指针或（NULL）错误
 */
esp_tusb_cdc_t *tinyusb_cdc_get_intf(int itf_num);
/***********************************************************************功能*/

#ifdef __cplusplus
}
#endif

