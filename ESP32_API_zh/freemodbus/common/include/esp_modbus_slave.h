/* 版权所有2018 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _ESP_MB_SLAVE_INTERFACE_H
#define _ESP_MB_SLAVE_INTERFACE_H

// 从属设备的公共接口标头
#include <stdint.h>                 // 用于标准int类型定义
#include <stddef.h>                 // 对于NULL和std定义
#include "soc/soc.h"                // 用于BITN定义
#include "freertos/FreeRTOS.h"      // 用于任务创建和队列访问
#include "freertos/event_groups.h"  // 对于事件组
#include "esp_modbus_common.h"      // 对于常见类型

#ifdef __cplusplus
extern "C" {
#endif

#define MB_SLAVE_CHECK(a, err_code, format, ...) MB_RETURN_ON_FALSE(a, err_code, TAG, format __VA_OPT__(,) __VA_ARGS__)

#define MB_SLAVE_ASSERT(con) do { \
        if (!(con)) { ESP_LOGE(TAG, "assert errno:%d, errno_str: !(%s)", errno, strerror(errno)); assert(0 && #con); } \
    } while (0)

/**
 * @brief 参数访问事件信息类型
 */
typedef struct {
    uint32_t time_stamp;                    /*!< Modbus事件的时间戳（uS）*/
    uint16_t mb_offset;                     /*!< Modbus寄存器偏移*/
    mb_event_group_t type;                  /*!< Modbus事件类型*/
    uint8_t* address;                       /*!< Modbus数据存储地址*/
    size_t size;                            /*!< Modbus事件寄存器大小（寄存器数量）*/
} mb_param_info_t;

/**
 * @brief 参数存储区域描述符
 */
typedef struct {
    uint16_t start_offset;                  /*!< 区域描述符的Modbus起始地址*/
    mb_param_type_t type;                   /*!< 存储区域描述符的类型*/
    void* address;                          /*!< 存储区域描述符的实例地址*/
    size_t size;                            /*!< 区域描述符的实例大小（字节）*/
} mb_register_area_descriptor_t;

/**
 * @brief 初始化Modbus从控制器和TCP端口堆栈
 *
 * @param[out] handler 主数据结构的处理程序（指针）
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_NO_MEM参数错误
 *     -不支持ESP_ERR_NOT_SUPPORTED端口类型
 *     -ESP_ERR_INVALID_STATE初始化失败
 */
esp_err_t mbc_slave_init_tcp(void** handler);

/**
 * @brief 初始化Modbus从控制器和串行端口堆栈
 *
 * @param[out] handler 主数据结构的处理程序（指针）
 * @param[in] port_type 港口类型
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_NO_MEM参数错误
 *     -不支持ESP_ERR_NOT_SUPPORTED端口类型
 *     -ESP_ERR_INVALID_STATE初始化失败
 */
esp_err_t mbc_slave_init(mb_port_type_t port_type, void** handler);

/**
 * @brief 初始化Modbus从控制器接口句柄
 *
 * @param[in] handler -从接口数据结构指针
 */
void mbc_slave_init_iface(void* handler);

/**
 * @brief 销毁Modbus控制器和堆栈
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE参数错误
 */
esp_err_t mbc_slave_destroy(void);

/**
 * @brief 启动Modbus通信堆栈
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG Modbus堆栈启动错误
 */
esp_err_t mbc_slave_start(void);

/**
 * @brief 设置控制器的Modbus通信参数
 *
 * @param comm_info 通信参数结构。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数数据不正确
 */
esp_err_t mbc_slave_setup(void* comm_info);

/**
 * @brief 等待参数更改的特定事件。
 *
 * @param group 组事件位掩码以等待更改
 *
 * @return
 *     -mb_event_group_t事件位已触发
 */
mb_event_group_t mbc_slave_check_event(mb_event_group_t group);

/**
 * @brief 获取参数信息
 *
 * @param[out] reg_info 参数信息结构
 * @param timeout 从参数队列读取信息超时（毫秒）
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_TIMEOUT无法从参数队列或队列溢出中获取数据
 */
esp_err_t mbc_slave_get_param_info(mb_param_info_t* reg_info, uint32_t timeout);

/**
 * @brief 设置Modbus区域描述符
 *
 * @param descr_data Modbus寄存器区域描述符结构
 *
 * @return
 *     -ESP_OK：设置了适当的描述符
 *     -ESP_ERR_INVALID_ARG：参数不正确
 */
esp_err_t mbc_slave_set_descriptor(mb_register_area_descriptor_t descr_data);

#ifdef __cplusplus
}
#endif

#endif

