/* 版权所有2018 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _MB_CONTROLLER_MASTER_H
#define _MB_CONTROLLER_MASTER_H

#include <sys/queue.h>              // for列表
#include "freertos/FreeRTOS.h"      // 用于任务创建和队列访问
#include "freertos/task.h"          // 用于任务api访问
#include "freertos/event_groups.h"  // 对于事件组
#include "driver/uart.h"            // 对于UART类型
#include "errno.h"                  // 用于errno
#include "esp_log.h"                // 用于日志写入
#include "string.h"                 // 用于strerr（）
#include "esp_modbus_common.h"      // 对于常见类型
#include "esp_modbus_master.h"      // 对于公共主控类型
#include "esp_modbus_callbacks.h"

/* -----------------------定义------------------------------------------*/

/**
 * @brief 要在数据字典中使用的参数的请求模式
 */
typedef enum {
    MB_PARAM_READ, /*!< 读取参数值。*/
    MB_PARAM_WRITE /*!< 写入参数值。*/
} mb_param_mode_t;

/**
 * @brief 主机的设备通信参数
 */
typedef struct {
    mb_mode_type_t mode;                    /*!< Modbus通信模式*/
    uint8_t dummy;                          /*!< 虚拟字段*/
    uart_port_t port;                       /*!< Modbus通信端口（UART）编号*/
    uint32_t baudrate;                      /*!< Modbus波特率*/
    uart_parity_t parity;                   /*!< Modbus UART奇偶校验设置*/
} mb_master_comm_info_t;

#if MB_MASTER_TCP_ENABLED
/**
 * @brief 主设备的Modbus从属地址列表项
 */
typedef struct mb_slave_addr_entry_s{
    uint16_t index;                             /*!< 从属地址的索引*/
    const char* ip_address;                     /*!< 从设备的IP地址字符串*/
    uint8_t slave_addr;                         /*!< 短从属地址*/
    void* p_data;                               /*!< 指向数据结构的指针*/
    LIST_ENTRY(mb_slave_addr_entry_s) entries;  /*!< 从属地址条目*/
} mb_slave_addr_entry_t;
#endif

/**
 * @brief Modbus控制器处理器结构
 */
typedef struct {
    mb_port_type_t port_type;                           /*!< Modbus端口类型*/
    mb_communication_info_t mbm_comm;                   /*!< Modbus通信信息*/
    uint8_t* mbm_reg_buffer_ptr;                        /*!< Modbus数据缓冲指针*/
    uint16_t mbm_reg_buffer_size;                       /*!< Modbus数据缓冲区大小*/
    TaskHandle_t mbm_task_handle;                       /*!< Modbus任务句柄*/
    EventGroupHandle_t mbm_event_group;                 /*!< Modbus控制器事件组*/
    const mb_parameter_descriptor_t* mbm_param_descriptor_table; /*!< Modbus控制器参数描述表*/
    size_t mbm_param_descriptor_size;                   /*!< Modbus控制器参数描述表大小*/
#if MB_MASTER_TCP_ENABLED
    LIST_HEAD(mbm_slave_addr_info_, mb_slave_addr_entry_s) mbm_slave_list; /*!< 从属地址信息列表*/
    uint16_t mbm_slave_list_count;
#endif
} mb_master_options_t;

typedef esp_err_t (*iface_get_cid_info)(uint16_t, const mb_parameter_descriptor_t**); /*!< 接口get_cid_info方法*/
typedef esp_err_t (*iface_get_parameter)(uint16_t, char*, uint8_t*, uint8_t*);        /*!< 接口get_parameter方法*/
typedef esp_err_t (*iface_send_request)(mb_param_request_t*, void*);                  /*!< 接口send_request方法*/
typedef esp_err_t (*iface_set_descriptor)(const mb_parameter_descriptor_t*, const uint16_t); /*!< 接口set_descriptor方法*/
typedef esp_err_t (*iface_set_parameter)(uint16_t, char*, uint8_t*, uint8_t*);        /*!< 接口set_parameter方法*/

/**
 * @brief Modbus控制器接口结构
 */
typedef struct {
    // 主对象界面选项
    mb_master_options_t opts;

    // 公共接口方法
    iface_init init;                        /*!< 接口方法init*/
    iface_destroy destroy;                  /*!< 接口方法销毁*/
    iface_setup setup;                      /*!< 接口方法设置*/
    iface_start start;                      /*!< 接口方法启动*/
    iface_get_cid_info get_cid_info;        /*!< 接口get_cid_info方法*/
    iface_get_parameter get_parameter;      /*!< 接口get_parameter方法*/
    iface_send_request send_request;        /*!< 接口send_request方法*/
    iface_set_descriptor set_descriptor;    /*!< 接口set_descriptor方法*/
    iface_set_parameter set_parameter;      /*!< 接口set_parameter方法*/
    // Modbus寄存器回调函数指针
    reg_discrete_cb master_reg_cb_discrete; /*!< 堆栈回调离散rw方法*/
    reg_input_cb master_reg_cb_input;       /*!< 堆栈回调输入rw方法*/
    reg_holding_cb master_reg_cb_holding;   /*!< 堆栈回调保持rw方法*/
    reg_coils_cb master_reg_cb_coils;       /*!< 堆栈回调线圈rw方法*/
} mb_master_interface_t;

#endif //_MB_CONTROLLER_MASTER_H

