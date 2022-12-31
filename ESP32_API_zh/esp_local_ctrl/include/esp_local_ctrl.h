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

#include <protocomm.h>

/**
 * @brief   属性描述数据结构，将填充并传递给“esp_local_ctrl_add_Property（）”函数
 *
 * 一旦添加了属性，它的结构就可以在`get_prop_values（）`和`set_prop_vvalues（）`handlers中进行只读访问。
 */
typedef struct esp_local_ctrl_prop {
    /**
     * 属性的唯一名称
     */
    char *name;

    /**
     * 属性类型。这可以设置为应用程序定义的枚举
     */
    uint32_t type;

    /**
     * 属性值的大小，其中：
     * -如果为零，则属性可以具有可变大小的值
     * -如果非零，则该属性只能具有固定大小的值，因此，在设置此类属性的值时，esp_local_ctrl会在内部执行检查
     */
    size_t size;

    /**
     * 为此属性设置的标志。这可能是一个小字段。标志可以指示属性行为，例如只读/常量
     */
    uint32_t flags;

    /**
     * 指向与此属性相关的某些上下文数据的指针。这将作为此属性结构的一部分在“get_prop_values”和“set_prop_vvalues”处理程序中使用。设置后，在属性的整个生命周期内都有效，直到删除该属性或停止esp_local_ctrl服务。
     */
    void *ctx;

    /**
     * 调用“esp_local_ctrl_remove_property（）”或“esp_local_ctrl_stop（）”时，esp_local_ctrl用于内部释放属性上下文的函数。
     */
    void (*ctx_free_fn)(void *ctx);
} esp_local_ctrl_prop_t;

/**
 * @brief   属性值数据结构。这将传递给`get_prop_values（）`和`set_prop_vvalues（）'处理程序，用于检索或设置属性的当前值。
 */
typedef struct esp_local_ctrl_prop_val {
    /**
     * 指向内存保持属性值的指针
     */
    void *data;

    /**
     * 属性值大小
     */
    size_t size;

    /**
     * 这可以由应用程序在“get_prop_values（）”处理程序中设置，以告诉“esp_local_ctrl”在上面的数据指针上调用此函数，以便在发送“get_prop_values”响应后释放其资源。
     */
    void (*free_fn)(void *data);
} esp_local_ctrl_prop_val_t;

/**
 * @brief   用于接收和响应本地控制命令以获取和设置属性的处理程序。
 */
typedef struct esp_local_ctrl_handlers {
    /**
     * @brief 要实现的用于检索属性的当前值的处理程序函数
     *
     * @note  如果任何属性具有固定大小，则需要设置“prop_values”中相应元素的大小字段
     *
     * @param[in]  props_count  道具数组中的元素总数
     * @param[in]  props        客户端请求的当前值的属性数组
     * @param[out] prop_values  空属性值数组，其元素需要用props参数指定的那些属性的当前值填充
     * @param[in]  usr_ctx      这提供了“esp_local_ctl_handlers_t”结构的“usr_ctx”字段的值
     *
     * @return 返回不同的错误代码将向客户端传达相应的协议级别错误：
     *         -ESP_OK：成功
     *         -ESP_ERR_INVALID_ARG：参数无效
     *         -ESP_ERR_INVALID_STATE:无效协议
     *         -所有其他错误代码：InternalError
     */
    esp_err_t (*get_prop_values)(size_t props_count,
                                 const esp_local_ctrl_prop_t props[],
                                 esp_local_ctrl_prop_val_t prop_values[],
                                 void *usr_ctx);

    /**
     * @brief 用于更改属性值的处理程序函数
     *
     * @note  如果任何属性具有可变大小，则在对大小进行任何假设之前，必须明确检查“prop_values”中对应元素的大小字段。
     *
     * @param[in]  props_count  道具数组中的元素总数
     * @param[in]  props        属性数组，客户端请求更改的值
     * @param[in]  prop_values  属性值数组，其元素需要用于更新props参数指定的属性
     * @param[in]  usr_ctx      这提供了“esp_local_ctl_handlers_t”结构的“usr_ctx”字段的值
     *
     * @return 返回不同的错误代码将向客户端传达相应的协议级别错误：
     *         -ESP_OK：成功
     *         -ESP_ERR_INVALID_ARG：参数无效
     *         -ESP_ERR_INVALID_STATE:无效协议
     *         -所有其他错误代码：InternalError
     */
    esp_err_t (*set_prop_values)(size_t props_count,
                                 const esp_local_ctrl_prop_t props[],
                                 const esp_local_ctrl_prop_val_t prop_values[],
                                 void *usr_ctx);

    /**
     * 调用时要传递给上述处理程序函数的上下文指针。这与属性级上下文不同，因为这在“esp_local_ctrl”服务的整个生命周期内都有效，并且只有在服务停止时才释放。
     */
    void *usr_ctx;

    /**
     * 指向函数的指针，当调用“esp_local_ctl_stop（）”时，将在“usr_ctx”上内部调用该函数以释放上下文资源。
     */
    void (*usr_ctx_free_fn)(void *usr_ctx);
} esp_local_ctrl_handlers_t;

/**
 * @brief   提供服务的传输模式（BLE/HTTPD）
 *
 * 这是私有结构的前向声明，由“esp_local_ctrl”在内部实现。
 */
typedef struct esp_local_ctrl_transport esp_local_ctrl_transport_t;

/**
 * @brief   获取BLE传输模式的功能
 */
const esp_local_ctrl_transport_t *esp_local_ctrl_get_transport_ble(void);

/**
 * @brief   获取HTTPD传输模式的功能
 */
const esp_local_ctrl_transport_t *esp_local_ctrl_get_transport_httpd(void);

#define ESP_LOCAL_CTRL_TRANSPORT_BLE   esp_local_ctrl_get_transport_ble()
#define ESP_LOCAL_CTRL_TRANSPORT_HTTPD esp_local_ctrl_get_transport_httpd()

/**
 * @brief   传输模式BLE的配置
 *
 * 这是“protocomm_ble_config_t”的前向声明。要使用此功能，应用程序必须设置CONFIG_BT_BLUEDROID_ENABLED并包含“protocomm_ble.h”。
 */
typedef struct protocomm_ble_config esp_local_ctrl_transport_config_ble_t;

/**
 * @brief   传输模式HTTPD的配置
 *
 * 这是“httpd_ssl_config_t”的转发声明。要使用此功能，应用程序必须设置CONFIG_ESP_HTTPS_SERVER_ENABLE并包含`ESP_HTTPS_SERVER.h`
 */
typedef struct httpd_ssl_config esp_local_ctrl_transport_config_httpd_t;

/**
 * @brief   传输模式（BLE/HTTPD）配置
 */
typedef union {
    /**
     * 这与“protocomm_ble_config_t”相同。请参见`protocomm_ble。h’表示可用的配置参数。
     */
    esp_local_ctrl_transport_config_ble_t *ble;

    /**
     * 这与“httpd_ssl_config_t”相同。请参见`esp_https_server。h’表示可用的配置参数。
     */
    esp_local_ctrl_transport_config_httpd_t *httpd;
} esp_local_ctrl_transport_config_t;

/**
 * @brief   esp_local_control的安全类型
 */
typedef enum esp_local_ctrl_proto_sec {
    PROTOCOM_SEC0 = 0,
    PROTOCOM_SEC1,
    PROTOCOM_SEC_CUSTOM,
} esp_local_ctrl_proto_sec_t;

/**
 * Protocom安全配置
 */
typedef struct esp_local_ctrl_proto_sec_cfg {
     /**
     * 这将设置协议安全版本sec0/sec1或自定义。如果自定义，用户必须通过下面的“proto_sec_custom_handle”提供句柄
     */
    esp_local_ctrl_proto_sec_t version;

    /**
     * 如果通过上面的“proto_sec”自定义安全设置，则自定义安全句柄。此句柄必须遵循“protocomm_security_t”签名
     */
    void *custom_handle;

    /**
     * 用于本地控制的占有证明。可能为NULL。
     */
    void *pop;
} esp_local_ctrl_proto_sec_cfg_t;

/**
 * @brief   要传递给`esp_local_ctrl_start（）的配置结构`
 */
typedef struct esp_local_ctrl_config {
    /**
     * 将在其上提供服务的传输层
     */
    const esp_local_ctrl_transport_t *transport;

    /**
     * 将在其上提供服务的传输层
     */
    esp_local_ctrl_transport_config_t transport_config;

    /**
     * 安全版本和POP
     */
    esp_local_ctrl_proto_sec_cfg_t proto_sec;

    /**
     * 注册处理程序以响应对属性的获取/设置请求
     */
    esp_local_ctrl_handlers_t handlers;

    /**
     * 这限制了一次可用的属性的数量
     */
    size_t max_properties;
} esp_local_ctrl_config_t;

/**
 * @brief   启动本地控制服务
 *
 * @param[in] config    指向配置结构的指针
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：故障
 */
esp_err_t esp_local_ctrl_start(const esp_local_ctrl_config_t *config);

/**
 * @brief   停止本地控制服务
 */
esp_err_t esp_local_ctrl_stop(void);

/**
 * @brief   添加新属性
 *
 * 这将添加一个新属性并为其分配内部资源。可以添加的属性总数受配置选项`max_properties的限制`
 *
 * @param[in] prop    属性描述结构
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：故障
 */
esp_err_t esp_local_ctrl_add_property(const esp_local_ctrl_prop_t *prop);

/**
 * @brief   删除属性
 *
 * 这将按名称查找属性，并释放与其关联的内部资源。
 *
 * @param[in] name    要删除的属性的名称
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_NOT_FOUND：故障
 */
esp_err_t esp_local_ctrl_remove_property(const char *name);

/**
 * @brief   按名称获取属性描述结构
 *
 * 当属性名称已知时，此API可用于获取属性的上下文结构“esp_local_ctrl_prop_t”
 *
 * @param[in] name    要查找的属性的名称
 *
 * @return
 *  -指向属性的指针
 *  -如果找不到，则为NULL
 */
const esp_local_ctrl_prop_t *esp_local_ctrl_get_property(const char *name);

/**
 * @brief   为自定义端点注册protocomm处理程序
 *
 * 本地控制服务启动后，应用程序可以调用此API为端点注册protocomm处理程序。
 *
 * @note 对于BLE传输，必须预先提供所有自定义端点的名称和uuid，作为“esp_local_ctl_config_t”中设置的“protocomm_BLE_config_t”结构的一部分，并传递给“esp_local_ctl_start（）”。
 *
 * @param[in] ep_name   端点的名称
 * @param[in] handler   终结点处理程序函数
 * @param[in] user_ctx  用户数据
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：故障
 */
esp_err_t esp_local_ctrl_set_handler(const char *ep_name,
                                     protocomm_req_handler_t handler,
                                     void *user_ctx);

#ifdef __cplusplus
}
#endif

