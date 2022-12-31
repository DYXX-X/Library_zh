// 版权所有2019 Espressif Systems（上海）私人有限公司
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
#include "esp_err.h"
#include "lwip/ip_addr.h"

/**
* @brief “ping”会话句柄的类型
*
*/
typedef void *esp_ping_handle_t;

/**
* @brief “ping”回调函数的类型
*
*/
typedef struct {
    /**
    * @brief 回调函数的参数
    *
    */
    void *cb_args;

    /**
    * @brief 收到ICMP回显应答数据包时由内部ping线程调用
    *
    */
    void (*on_ping_success)(esp_ping_handle_t hdl, void *args);

    /**
    * @brief 接收ICMP回显应答数据包超时时由内部ping线程调用
    *
    */
    void (*on_ping_timeout)(esp_ping_handle_t hdl, void *args);

    /**
    * @brief 在ping会话完成时由内部ping线程调用
    *
    */
    void (*on_ping_end)(esp_ping_handle_t hdl, void *args);
} esp_ping_callbacks_t;

/**
* @brief “ping”配置类型
*
*/
typedef struct {
    uint32_t count;           /*!< “ping”会话包含计数过程*/
    uint32_t interval_ms;     /*!< 每个ping过程之间的毫秒数*/
    uint32_t timeout_ms;      /*!< 每个ping过程的超时值（毫秒）*/
    uint32_t data_size;       /*!< ICMP数据包标题旁边的数据大小*/
    uint8_t tos;              /*!< 服务类型，IP标头中指定的字段*/
    ip_addr_t target_addr;    /*!< 目标IP地址，IPv4或IPv6*/
    uint32_t task_stack_size; /*!< 内部ping任务的堆栈大小*/
    uint32_t task_prio;       /*!< 内部ping任务的优先级*/
    uint32_t interface;       /*!< Netif索引，接口=0表示Netif_NO_index*/
} esp_ping_config_t;

/**
 * @brief 默认ping配置
 *
 */
#define ESP_PING_DEFAULT_CONFIG()        \
    {                                    \
        .count = 5,                      \
        .interval_ms = 1000,             \
        .timeout_ms = 1000,              \
        .data_size = 64,                 \
        .tos = 0,                        \
        .target_addr = *(IP_ANY_TYPE),   \
        .task_stack_size = 2048,         \
        .task_prio = 2,                  \
        .interface = 0,\
    }

#define ESP_PING_COUNT_INFINITE (0) /*!< 将ping计数设置为零将无限ping目标*/

/**
* @brief ping会话的配置文件
*
*/
typedef enum {
    ESP_PING_PROF_SEQNO,   /*!< ping过程的序列号*/
    ESP_PING_PROF_TTL,     /*!< ping过程的生存时间*/
    ESP_PING_PROF_REQUEST, /*!< 发出的请求数据包数*/
    ESP_PING_PROF_REPLY,   /*!< 收到的回复数据包数*/
    ESP_PING_PROF_IPADDR,  /*!< 回复目标的IP地址*/
    ESP_PING_PROF_SIZE,    /*!< 接收数据包的大小*/
    ESP_PING_PROF_TIMEGAP, /*!< 请求和答复数据包之间的经过时间*/
    ESP_PING_PROF_DURATION /*!< 整个ping会话的运行时间*/
} esp_ping_profile_t;

/**
 * @brief 创建ping会话
 *
 * @param config ping配置
 * @param cbs 由内部ping任务调用的一组回调函数
 * @param hdl_out ping会话句柄
 * @return
 *      -ESP_ERR_INVALID_ARG：参数无效（例如配置为空等）
 *      -ESP_ERR_NO_MEM：内存不足
 *      -ESP_FAIL：其他内部错误（例如套接字错误）
 *      -ESP_OK：成功创建ping会话，用户可以使用ping句柄执行后续作业
 */
esp_err_t esp_ping_new_session(const esp_ping_config_t *config, const esp_ping_callbacks_t *cbs, esp_ping_handle_t *hdl_out);

/**
 * @brief 删除ping会话
 *
 * @param hdl ping会话句柄
 * @return
 *      -ESP_ERR_INVALID_ARG：参数无效（例如ping句柄为空等）
 *      -ESP_OK:成功删除ping会话
 */
esp_err_t esp_ping_delete_session(esp_ping_handle_t hdl);

/**
 * @brief 启动ping会话
 *
 * @param hdl ping会话句柄
 * @return
 *      -ESP_ERR_INVALID_ARG：参数无效（例如ping句柄为空等）
 *      -ESP_OK:成功启动ping会话
 */
esp_err_t esp_ping_start(esp_ping_handle_t hdl);

/**
 * @brief 停止ping会话
 *
 * @param hdl ping会话句柄
 * @return
 *      -ESP_ERR_INVALID_ARG：参数无效（例如ping句柄为空等）
 *      -ESP_OK:成功停止ping会话
 */
esp_err_t esp_ping_stop(esp_ping_handle_t hdl);

/**
 * @brief 获取ping会话的运行时配置文件
 *
 * @param hdl ping会话句柄
 * @param profile 剖面的类型
 * @param data 配置文件数据
 * @param size 配置文件数据大小
 * @return
 *      -ESP_ERR_INVALID_ARG：参数无效（例如ping句柄为空等）
 *      -ESP_ERR_INVALID_SIZE：实际配置文件数据大小与“大小”参数不匹配
 *      -ESP_OK：成功获取配置文件
 */
esp_err_t esp_ping_get_profile(esp_ping_handle_t hdl, esp_ping_profile_t profile, void *data, uint32_t size);

#ifdef __cplusplus
}
#endif

