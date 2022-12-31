/* 版权所有2018 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#ifndef _MB_CONTROLLER_SLAVE_H
#define _MB_CONTROLLER_SLAVE_H

#include "driver/uart.h"    // 用于uart定义
#include "errno.h"          // 用于errno
#include "sys/queue.h"      // for列表
#include "esp_log.h"        // 用于日志写入
#include "string.h"         // 用于strerr（）

#include "esp_modbus_slave.h"    // 对于公共类型定义
#include "esp_modbus_callbacks.h"   // 用于回调函数

/* -----------------------定义------------------------------------------*/
#define MB_INST_MIN_SIZE                    (2) // Modbus寄存器区域的最小大小（字节）
#define MB_INST_MAX_SIZE                    (65535 * 2) // Modbus区域的最大大小（字节）

#define MB_CONTROLLER_NOTIFY_QUEUE_SIZE     (CONFIG_FMB_CONTROLLER_NOTIFY_QUEUE_SIZE) // 参数通知队列中的消息数
#define MB_CONTROLLER_NOTIFY_TIMEOUT        (pdMS_TO_TICKS(CONFIG_FMB_CONTROLLER_NOTIFY_TIMEOUT)) // 通知超时

/**
 * @brief 主机的设备通信参数
 */
typedef struct {
    mb_mode_type_t mode;                    /*!< Modbus通信模式*/
    uint8_t slave_addr;                     /*!< 从属地址字段*/
    uart_port_t port;                       /*!< Modbus通信端口（UART）编号*/
    uint32_t baudrate;                      /*!< Modbus波特率*/
    uart_parity_t parity;                   /*!< Modbus UART奇偶校验设置*/
} mb_slave_comm_info_t;

/**
 * @brief Modbus区域描述符列表项
 */
typedef struct mb_descr_entry_s{
    uint16_t start_offset;                  /*!< 区域描述符的Modbus起始地址*/
    mb_param_type_t type;                   /*!< 存储区域描述符的类型*/
    void* p_data;                           /*!< 存储区域描述符的实例地址*/
    size_t size;                            /*!< 区域描述符的实例大小（字节）*/
    LIST_ENTRY(mb_descr_entry_s) entries;    /*!< Modbus区域描述符条目*/
} mb_descr_entry_t;

/**
 * @brief Modbus控制器处理器结构
 */
typedef struct {
    mb_port_type_t port_type;                           /*!< 端口类型*/
    mb_communication_info_t mbs_comm;                   /*!< 通信信息*/
    TaskHandle_t mbs_task_handle;                       /*!< 任务句柄*/
    EventGroupHandle_t mbs_event_group;                 /*!< 控制器事件组*/
    QueueHandle_t mbs_notification_queue_handle;        /*!< 控制器通知队列*/
    LIST_HEAD(mbs_area_descriptors_, mb_descr_entry_s) mbs_area_descriptors[MB_PARAM_COUNT]; /*!< 寄存器区域描述符*/
} mb_slave_options_t;

typedef mb_event_group_t (*iface_check_event)(mb_event_group_t);          /*!< 接口方法check_event*/
typedef esp_err_t (*iface_get_param_info)(mb_param_info_t*, uint32_t);    /*!< 接口方法get_param_info*/
typedef esp_err_t (*iface_set_descriptor)(mb_register_area_descriptor_t); /*!< 接口方法set_descriptor*/

/**
 * @brief 要在数据字典中使用的参数的请求模式
 */
typedef struct
{
    mb_slave_options_t opts;                                    /*!< Modbus从站选项*/

    // 指向实现的内部静态函数的函数指针（公共接口方法）
    iface_init init;                        /*!< 接口方法init*/
    iface_destroy destroy;                  /*!< 接口方法销毁*/
    iface_setup setup;                      /*!< 接口方法设置*/
    iface_start start;                      /*!< 接口方法启动*/
    iface_check_event check_event;          /*!< 接口方法check_event*/
    iface_get_param_info get_param_info;    /*!< 接口方法get_param_info*/
    iface_set_descriptor set_descriptor;    /*!< 接口方法set_descriptor*/

    // Modbus寄存器回调函数指针
    reg_discrete_cb slave_reg_cb_discrete;  /*!< 堆栈回调离散rw方法*/
    reg_input_cb slave_reg_cb_input;        /*!< 堆栈回调输入rw方法*/
    reg_holding_cb slave_reg_cb_holding;    /*!< 堆栈回调保持rw方法*/
    reg_coils_cb slave_reg_cb_coils;        /*!< 堆栈回调线圈rw方法*/
} mb_slave_interface_t;

#endif

