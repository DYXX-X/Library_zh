// 版权所有2021浓缩咖啡系统（上海）有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制

#pragma once

#include "hal/uart_types.h"
#include "sys/_stdint.h"
#include "sys/select.h"
#include "esp_event_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief OpenThread事件声明
*
*/
typedef enum {
    OPENTHREAD_EVENT_START,                 /*!< OpenThread堆栈启动*/
    OPENTHREAD_EVENT_STOP,                  /*!< OpenThread堆栈停止*/
    OPENTHREAD_EVENT_IF_UP,                 /*!< OpenThread网络接口启动*/
    OPENTHREAD_EVENT_IF_DOWN,               /*!< OpenThread网络接口关闭*/
    OPENTHREAD_EVENT_GOT_IP6,               /*!< OpenThread堆栈添加了IPv6地址*/
    OPENTHREAD_EVENT_LOST_IP6,              /*!< OpenThread堆栈已删除IPv6地址*/
    OPENTHREAD_EVENT_MULTICAST_GROUP_JOIN,  /*!< OpenThread堆栈已加入IPv6多播组*/
    OPENTHREAD_EVENT_MULTICAST_GROUP_LEAVE, /*!< OpenThread堆栈离开IPv6多播组*/
} esp_openthread_event_t;

/**
* @brief OpenThread事件基声明
*
*/
ESP_EVENT_DECLARE_BASE(OPENTHREAD_EVENT);

/**
 * 此结构表示基于select（）的主循环的上下文。
 *
 */
typedef struct {
    fd_set         read_fds;    /*!< 读取文件描述符*/
    fd_set         write_fds;   /*!< 写入文件描述符*/
    fd_set         error_fds;   /*!< 错误文件描述符*/
    int            max_fd;      /*!< 最大文件描述符*/
    struct timeval timeout;     /*!< 超时时间*/
} esp_openthread_mainloop_context_t;

/**
 * @brief OpenThread的uart端口配置。
 *
 */
typedef struct {
    uart_port_t port;               /*!< UART端口号*/
    uart_config_t uart_config;      /*!< UART配置，请参阅UART_config_t文档*/
    int rx_pin;                     /*!< UART RX引脚*/
    int tx_pin;                     /*!< UART TX引脚*/
} esp_openthread_uart_config_t;

/**
 * @brief OpenThread的无线电模式。
 *
 */
typedef enum {
    RADIO_MODE_NATIVE   = 0x0,      /*!< 使用本机15.4收音机*/
    RADIO_MODE_UART_RCP = 0x1,      /*!< UART连接到具有15.4功能的无线电协处理器（RCP）*/
    RADIO_MODE_SPI_RCP  = 0x2,      /*!< 与具有15.4功能的无线电协处理器（RCP）的SPI连接*/
} esp_openthread_radio_mode_t;

/**
 * @brief OpenThread如何连接到主机。
 *
 */
typedef enum {
    HOST_CONNECTION_MODE_NONE     = 0x0, /*!< 禁用主机连接*/
    HOST_CONNECTION_MODE_CLI_UART = 0x1, /*!< 到主机的CLI UART连接*/
    HOST_CONNECTION_MODE_RCP_UART = 0x2, /*!< RCP UART与主机的连接*/
} esp_openthread_host_connection_mode_t;

/**
 * @brief OpenThread无线电配置
 *
 */
typedef struct {
    esp_openthread_radio_mode_t     radio_mode;         /*!< 收音机模式*/
    esp_openthread_uart_config_t    radio_uart_config;  /*!< RCP的uart配置*/
} esp_openthread_radio_config_t;

/**
 * @brief OpenThread主机连接配置
 *
 */
typedef struct {
    esp_openthread_host_connection_mode_t   host_connection_mode;   /*!< 主机连接模式*/
    esp_openthread_uart_config_t            host_uart_config;       /*!< 主机的uart配置*/
} esp_openthread_host_connection_config_t;

/**
 * @brief OpenThread端口特定配置
 *
 */
typedef struct {
    const char *storage_partition_name; /*!< 用于存储OpenThread数据集的分区*/
    uint8_t     netif_queue_size;       /*!< 网络接口的数据包队列大小*/
    uint8_t     task_queue_size;        /*!< 任务队列大小*/
} esp_openthread_port_config_t;

/**
 * @brief OpenThread平台配置
 *
 */
typedef struct {
    esp_openthread_radio_config_t               radio_config;   /*!< 无线电配置*/
    esp_openthread_host_connection_config_t     host_config;    /*!< 主机连接配置*/
    esp_openthread_port_config_t                port_config;    /*!< 端口配置*/
} esp_openthread_platform_config_t;

#ifdef __cplusplus
}
#endif

