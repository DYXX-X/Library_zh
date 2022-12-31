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

#include <esp_err.h>
#include <protocomm.h>
#include <esp_local_ctrl.h>

/**
 * @brief   `esp_local_ctrl`传输特定结构
 *
 * 每个受支持的传输层都应该实现以下功能，用于启动、停止和配置protocomm服务
 */
struct esp_local_ctrl_transport {
    /**
     * 根据指定配置启动protocomm服务的处理程序
     */
    esp_err_t (*start_service) (protocomm_t *pc,
                                const esp_local_ctrl_transport_config_t *config);

    /**
     * 用于停止protocomm服务的处理程序
     */
    void (*stop_service) (protocomm_t *pc);

    /**
     * 用于创建传输特定配置副本的处理程序
     */
    esp_err_t (*copy_config) (esp_local_ctrl_transport_config_t *dest_config,
                              const esp_local_ctrl_transport_config_t *src_config);

    /**
     * 用于分配对应于协议命令端点的资源的处理程序。通常，在添加新端点时，会使用“protocomm_endpoint_add（）”API，但在启动protocomm实例之前，传输层可能需要为每个端点执行资源分配。在这种情况下，这个处理程序很有用，因为它是在“start_service（）”之前调用的。
     */
    esp_err_t (*declare_ep) (esp_local_ctrl_transport_config_t *config,
                             const char *ep_name, uint16_t ep_uuid);

    /**
     * 用于释放传输特定配置的处理程序
     */
    void (*free_config) (esp_local_ctrl_transport_config_t *config);
};

/**
 * @brief   `esp_local_ctrl的Protocom处理程序`
 *
 * 这是一个处理程序，负责通过protocomm通道处理传入请求，然后根据请求类型调用以下函数之一：
 * -`esp_local_ctrl_get_prop_count（）`
 * -`esp_local_ctrl_get_prop_values（）`
 * -`esp_local_ctrl_set_prop_values（）`上述函数的输出用于形成对应于请求类型的响应消息。形成的响应消息被打包并通过protocomm通道发送回。
 *
 * @param[in]  session_id   用于标识设备和客户端之间正在进行的会话的数字
 * @param[in]  inbuf        保存序列化/打包请求数据的缓冲区
 * @param[in]  inlen        输入缓冲区长度
 * @param[out] outbuf       保存序列化/打包响应数据的缓冲区
 * @param[out] outlen       输出缓冲区长度
 * @param[in]  priv_data    与“esp_local_ctrl”端点关联的专用数据
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：故障
 */
esp_err_t esp_local_ctrl_data_handler(uint32_t session_id, const uint8_t *inbuf, ssize_t inlen,
                                      uint8_t **outbuf, ssize_t *outlen, void *priv_data);

/**
 * @brief   使用此选项可获取向“esp_local_ctrl”服务注册的属性总数
 *
 * @param[out] count   指向要存储结果的变量的指针
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：故障
 */
esp_err_t esp_local_ctrl_get_prop_count(size_t *count);

/**
 * @brief   同时获取多个属性的描述和值。属性由索引请求。这在内部调用在“esp_local_ctrl_handlers_t”结构中指定的“get_prop_values”处理程序。由于“get_prop_values”接受属性结构，索引首先在内部转换为相应的“esp_local_ctrl_prop_t”。
 *
 * @param[in]  total_indices   “indexes”数组参数中的元素数
 * @param[in]  indices         一个索引数组，指定要获取的属性
 * @param[out] props           一个预先分配的空属性结构数组，其中的元素将填充与所提供索引对应的属性的名称、类型和标志
 * @param[out] values          一个预先分配的空值结构数组，其中的元素将填充与所提供的索引对应的那些属性的值和大小
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：故障
 */
esp_err_t esp_local_ctrl_get_prop_values(size_t total_indices, uint32_t *indices,
                                         esp_local_ctrl_prop_t *props,
                                         esp_local_ctrl_prop_val_t *values);

/**
 * @brief   同时设置多个属性的值。要设置的属性由索引指定。这在内部调用“esp_local_ctrl_handlers_t”结构中指定的“set_prop_values”处理程序。由于“set_prop_values”接受属性结构，索引首先在内部转换为相应的“esp_local_ctrl_prop_t”。
 *
 * @param[in] total_indices   “indexes”数组参数中的元素数
 * @param[in] indices         一个索引数组，用于指定要设置的属性
 * @param[in] values          值的数组。每个值都应该具有正确的大小，如果它用于设置固定大小的属性，否则将生成错误，并且所有属性都不会设置为任何给定值
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：故障
 */
esp_err_t esp_local_ctrl_set_prop_values(size_t total_indices, uint32_t *indices,
                                         const esp_local_ctrl_prop_val_t *values);

#ifdef __cplusplus
}
#endif

