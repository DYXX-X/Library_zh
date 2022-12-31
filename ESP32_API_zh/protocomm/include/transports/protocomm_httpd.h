// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#include <protocomm.h>

#define PROTOCOMM_HTTPD_DEFAULT_CONFIG() {   \
    .port           = 80,                    \
    .stack_size     = 4096,                  \
    .task_priority  = tskIDLE_PRIORITY + 5,  \
}

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   protocomm HTTP服务器的配置参数
 */
typedef struct {

    uint16_t port;          /*!< HTTP服务器将侦听的端口*/

    /**
     * 服务器任务的堆栈大小，根据端点处理程序的堆栈使用情况进行调整
     */
    size_t   stack_size;
    unsigned task_priority; /*!< 服务器任务的优先级*/
} protocomm_http_server_config_t; /*!< HTTP服务器配置，如果尚未启动HTTP服务器*/

/** Protocomm HTTPD配置数据
 */
typedef union {
    /** HTTP服务器句柄，如果ext_Handle_provided设置为true
     */
    void *handle;

    /** HTTP服务器配置（如果服务器尚未处于活动状态）
     */
    protocomm_http_server_config_t config;
} protocomm_httpd_config_data_t;

/**
 * @brief   protocomm HTTP服务器的配置参数
 */
typedef struct {
    /** 指示已提供外部HTTP服务器句柄的标志。在这种情况下，protocomm将使用相同的HTTP服务器，而不会在内部启动新的服务器。
     */
    bool ext_handle_provided;
    /**Protocomm HTTPD配置数据*/
    protocomm_httpd_config_data_t data;
} protocomm_httpd_config_t;

/**
 * @brief   启动HTTPD协议命令传输
 *
 * 该API在内部创建了一个框架，允许端点注册和协议通信的安全配置。
 *
 * @note    这是一个单例。即Protocomm可以有多个实例，但只有一个实例可以绑定到HTTP传输层。
 *
 * @param[in] pc        从Protocomm_new（）获取的Protocomm实例指针
 * @param[in] config    指向用于初始化HTTP服务器的配置结构的指针
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG:空参数
 *  -ESP_ERR_NOT_SUPPORTED：传输层绑定到另一个协议命令实例
 *  -ESP_ERR_INVALID_STATE:传输层已绑定到此协议命令实例
 *  -ESP_ERR_NO_MEM:服务器资源的内存分配失败
 *  -ESP_ERR_HTTPD_*：启动时出现HTTP服务器错误
 */
esp_err_t protocomm_httpd_start(protocomm_t *pc, const protocomm_httpd_config_t *config);

/**
 * @brief   停止HTTPD协议命令传输
 *
 * 此API清理HTTPD传输协议命令，并释放所有注册到协议命令的处理程序。
 *
 * @param[in] pc    传递给protocomm_httpd_start（）的相同protocomm实例
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG:空/不正确的协议命令实例指针
 */
esp_err_t protocomm_httpd_stop(protocomm_t *pc);

#ifdef __cplusplus
}
#endif

