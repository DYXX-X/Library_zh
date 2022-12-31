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

#include <protocomm.h>

#include "esp_event.h"
#include "wifi_provisioning/wifi_config.h"

#ifdef __cplusplus
extern "C" {
#endif

ESP_EVENT_DECLARE_BASE(WIFI_PROV_EVENT);

/**
 * @brief   经理生成的事件
 *
 * 这些事件按照声明的顺序生成，在管理器初始化和取消初始化之间的一段时间内，每个事件只发出一次信号
 */
typedef enum {
    /**
     * 初始化管理器时发出
     */
    WIFI_PROV_INIT,

    /**
     * 指示资源调配已启动
     */
    WIFI_PROV_START,

    /**
     * 通过“protocomm”端点“wifi_config”接收Wi-Fi AP凭据时发出。本例中的事件数据是指向相应“wifi_sta_config_t”结构的指针
     */
    WIFI_PROV_CRED_RECV,

    /**
     * 当设备无法连接到较早在事件“WIFI_PROV_CRED_RECV”上接收到凭据的AP时发出。在这种情况下，事件数据是指向断开原因代码的指针，类型为`wifi_prop_sta_fail_reason_t`
     */
    WIFI_PROV_CRED_FAIL,

    /**
     * 当设备成功连接到之前在事件`WIFI_PROV_CRED_RECV上收到凭据的AP时发出`
     */
    WIFI_PROV_CRED_SUCCESS,

    /**
     * 表示配置服务已停止
     */
    WIFI_PROV_END,

    /**
     * 表示管理器已取消初始化
     */
    WIFI_PROV_DEINIT,
} wifi_prov_cb_event_t;

typedef void (*wifi_prov_cb_func_t)(void *user_data, wifi_prov_cb_event_t event, void *event_data);

/**
 * @brief   配置服务处于活动状态时管理器使用的事件处理程序
 */
typedef struct {
    /**
     * 要在供应事件上执行的回调函数
     */
    wifi_prov_cb_func_t event_cb;

    /**
     * 作为参数传递给回调函数的用户上下文数据
     */
    void *user_data;
} wifi_prov_event_handler_t;

/**
 * @brief 如果不使用，事件处理程序可以设置为none
 */
#define WIFI_PROV_EVENT_HANDLER_NONE { \
    .event_cb  = NULL,                 \
    .user_data = NULL                  \
}

/**
 * @brief   用于指定管理员要遵循的配置方案的结构
 *
 * @note    现成的方案可用：
 *              -wifi_prov_scheme_ble：用于通过ble传输+GATT服务器进行配置
 *              -wifi_prov_scheme_softap：用于通过softap传输+HTTP服务器进行配置
 *              -wifi_prov_scheme_console：用于通过串行UART传输+控制台进行配置（用于调试）
 */
typedef struct wifi_prov_scheme {
    /**
     * 当管理器要启动与协议命令实例和方案特定配置相关联的供应服务时，要调用的函数
     */
    esp_err_t (*prov_start) (protocomm_t *pc, void *config);

    /**
     * 管理器将调用的函数，以停止先前与protocomm实例关联的供应服务
     */
    esp_err_t (*prov_stop) (protocomm_t *pc);

    /**
     * 管理器要调用的函数，以生成供应服务的新配置，该配置将传递给prov_start（）
     */
    void *(*new_config) (void);

    /**
     * 管理器要调用的函数，以删除使用new_config（）生成的配置
     */
    void (*delete_config) (void *config);

    /**
     * 管理器要调用的函数，以设置配置结构中的服务名称和键值
     */
    esp_err_t (*set_config_service) (void *config, const char *service_name, const char *service_key);

    /**
     * 管理器调用的函数，用于在配置结构中设置具有标识名称和UUID的协议命令端点
     */
    esp_err_t (*set_config_endpoint) (void *config, const char *endpoint_name, uint16_t uuid);

    /**
     * 设置设置期间Wi-Fi的操作模式此设置为：
     * -用于SoftAP传输的WIFI_MODE_APSTA
     * -BLE传输的WIFI_MODE_STA
     */
    wifi_mode_t wifi_mode;
} wifi_prov_scheme_t;

/**
 * @brief   用于指定管理器配置的结构
 */
typedef struct {
    /**
     * 要使用的配置方案。以下方案已经可用：
     *     -wifi_prov_scheme_ble：用于通过ble传输+GATT服务器进行配置
     *     -wifi_prov_scheme_softap：用于通过softap传输+HTTP服务器+mDNS（可选）进行配置
     *     -wifi_prov_scheme_console：用于通过串行UART传输+控制台进行配置（用于调试）
     */
    wifi_prov_scheme_t scheme;

    /**
     * 在配置管理器运行时，方案所需的事件处理程序用于合并特定于方案的行为。设置该字段的方案可以提供各种选项。未使用时使用WIFI_PROV_EVENT_HANDLER_NONE。使用方案wifi_prop_scheme_ble时，可以使用以下选项：
     *     - WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BTDM
     *     - WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BLE
     *     - WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BT
     */
    wifi_prov_event_handler_t scheme_event_handler;

    /**
     * 可以设置用于合并应用程序特定行为的事件处理程序。未使用时使用WIFI_PROV_EVENT_HANDLER_NONE。
     */
    wifi_prov_event_handler_t app_event_handler;
} wifi_prov_mgr_config_t;

/**
 * @brief   Provisioning Manager支持的安全模式。
 *
 * 这些模式与protocomm提供的安全模式相同
 */
typedef enum wifi_prov_security {
    /**
     * 无安全性（纯文本通信）
     */
    WIFI_PROV_SECURITY_0 = 0,

    /**
     * 这种安全通信模式包括X25519密钥交换+基于所有权证明（pop）的认证+AES-CTR加密
     */
    WIFI_PROV_SECURITY_1
} wifi_prov_security_t;

/**
 * @brief   初始化配置管理器实例
 *
 * 配置管理器并分配内部资源
 *
 * 配置指定配置方案（传输）和事件处理程序
 *
 * 初始化完成后立即发出事件WIFI_PROV_INIT
 *
 * @param[in] config 配置结构
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：失败
 */
esp_err_t wifi_prov_mgr_init(wifi_prov_mgr_config_t config);

/**
 * @brief   停止资源调配（如果正在运行）并释放经理使用的资源
 *
 * 取消初始化完成后立即发出事件WIFI_PROV_DEINIT
 *
 * 如果调用此API时供应服务仍处于活动状态，它将首先停止服务，从而发出WIFI_PROV_END，然后执行取消初始化
 */
void wifi_prov_mgr_deinit(void);

/**
 * @brief   检查设备是否已设置
 *
 * 这将检查NVS上是否存在Wi-Fi凭据
 *
 * 假设Wi-Fi凭据保存在esp_wifi组件使用的相同NVS命名空间中
 *
 * 如果直接调用esp_wifi_set_config（）而不是通过配置过程，则该函数仍将返回true（即设备将被配置）
 *
 * @note    调用wifi_prov_mgr_start_provision（）会自动重置配置状态，而不管在调用之前的状态如何。
 *
 * @param[out] provisioned  如果已设置，则为True，否则为false
 *
 * @return
 *  -ESP_OK:已成功检索到配置状态
 *  -ESP_FAIL:Wi-Fi未初始化
 *  -ESP_ERR_INVALID_ARG:提供了空参数
 *  -ESP_ERR_INVALID_STATE:管理器未初始化
 */
esp_err_t wifi_prov_mgr_is_provisioned(bool *provisioned);

/**
 * @brief   启动资源调配服务
 *
 * 这将根据初始化时配置的方案启动供应服务。对于方案：
 * -wifi_prov_scheme_ble：这将启动protocomm_ble，它在内部初始化ble传输并启动GATT服务器以处理供应请求
 * -wifi_prov_scheme_softap：这将激活Wi-Fi的softap模式并启动protocomm_httpd，后者在内部启动HTTP服务器以处理配置请求（如果mDNS处于活动状态，则还会启动类型为_esp_wifi_prove._tcp的广告服务）
 *
 * 事件WIFI_PROV_START在配置启动后立即发出，且无故障
 *
 * @note   即使发现设备已配置，此API也将启动配置服务，即wifi_prov_mgr_is_provisioned（）将产生true
 *
 * @param[in] security      指定要使用的协议通信安全方案：
 *                              -WIFI_PROV_SECURITY_0：无安全性
 *                              -WIFI_PROV_SECURITY_1:x25519用于会话建立的安全握手，然后对供应消息进行AES-CTR加密
 * @param[in] pop           指向占有证明字符串的指针（如果不需要，则为NULL）。这仅与protocomm安全1相关，在这种情况下，它用于验证安全会话
 * @param[in] service_name  服务的唯一名称。这意味着：
 *                              -配置模式为软AP时的Wi-Fi SSID
 *                              -配置模式为BLE时的设备名称
 * @param[in] service_key   客户端访问服务所需的密钥（如果不需要，则为NULL）。这意味着：
 *                              -配置模式为软AP时的Wi-Fi密码
 *                              -当配置模式为BLE时忽略
 *
 * @return
 *  -ESP_OK:设置已成功启动
 *  -ESP_FAIL:无法启动设置服务
 *  -ESP_ERR_INVALID_STATE:设置管理器未初始化或已启动
 */
esp_err_t wifi_prov_mgr_start_provisioning(wifi_prov_security_t security, const char *pop,
                                           const char *service_name, const char *service_key);

/**
 * @brief   停止设置服务
 *
 * 如果供应服务处于活动状态，此API将启动一个进程以停止服务并返回。一旦服务实际停止，将发出事件WIFI_PROV_END。
 *
 * 如果在未首先调用此API的情况下调用wifi_prov_mgr_deinit（），它将自动停止供应服务，并在返回之前发出wifi_prov_END和wifi_prov-deinit。
 *
 * 当主应用程序注册了自己的端点，并且希望仅在收到来自客户端应用程序的一些协议命令时停止供应服务时，该API通常会与wifi_prov_mgr_disable_auto_stop（）一起使用。
 *
 * 在端点处理程序内调用此API，并具有足够的cleanup_delay，将允许在停止基础protocomm服务之前成功发送响应/确认。
 *
 * 调用wifi_prov_mgr_disable_auto_stop（）时设置Cleaup_delay。如果未指定，则默认为1000ms。
 *
 * 对于简单的情况，通常不需要使用此API，因为一旦发出WIFI_PROV_CRED_SUCCESS，供应就会自动停止。停止被延迟（最多30秒），从而允许客户端应用程序查询Wi-Fi状态，即，在接收到第一个查询并发送“Wi-Fi状态已连接”响应之后，服务立即停止。
 */
void wifi_prov_mgr_stop_provisioning(void);

/**
 * @brief   等待设置服务完成
 *
 * 调用此API将阻止，直到停止供应服务，即直到发出事件WIFI_PROV_END。
 *
 * 如果未启动或未初始化配置，则不会阻止。
 */
void wifi_prov_mgr_wait(void);

/**
 * @brief   完成后禁用自动停止配置服务
 *
 * 默认情况下，配置完成后，配置服务将自动停止，所有端点（以及主应用程序注册的端点）都将停用。
 *
 * 当主应用程序仅在从客户端应用程序接收到一些protocomm命令后才希望关闭供应服务时，此API非常有用。例如，在连接到Wi-Fi之后，设备可能想要连接到云，并且只有成功连接后，设备才被称为完全配置。但是，当设备完全配置并且不再需要供应服务时，主应用程序将在稍后显式调用wifi_prop_mgr_stop_provision（）。
 *
 * @note    必须在执行wifi_prov_mgr_start_provision（）之前调用此函数
 *
 * @param[in] cleanup_delay 设置调用wifi_prop_mgr_stop_provision（）返回后，实际清理传输相关资源的延迟。最小允许值为100ms。如果未指定，则默认为1000ms。
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_STATE:管理器未初始化或设置服务已启动
 */
esp_err_t wifi_prov_mgr_disable_auto_stop(uint32_t cleanup_delay);

/**
 * @brief   在proto-ver端点返回的JSON数据中设置应用程序版本和功能
 *
 * 可以多次调用此函数，以指定有关设备上运行的各种应用程序特定服务的信息，这些服务由唯一标签标识。
 *
 * 供应服务本身通过标签“prov”在JSON数据中注册一个条目，仅包含供应服务版本和功能。应用程序服务应使用“prov”以外的标签，以免覆盖此标签。
 *
 * @note    必须在执行wifi_prov_mgr_start_provision（）之前调用此函数
 *
 * @param[in] label   指示应用程序名称的字符串。
 *
 * @param[in] version 指示应用程序版本的字符串。格式没有限制。
 *
 * @param[in] capabilities  具有功能的字符串数组。客户端应用程序可以使用这些信息来了解应用程序注册的端点功能
 *
 * @param[in] total_capabilities  功能阵列的大小
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_STATE:管理器未初始化或设置服务已启动
 *  -ESP_ERR_NO_MEM:无法为版本字符串分配内存
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t wifi_prov_mgr_set_app_info(const char *label, const char *version,
                                     const char**capabilities, size_t total_capabilities);

/**
 * @brief   创建其他端点并为其分配内部资源
 *
 * 如果应用程序希望创建其他端点，则该API将由应用程序调用。所有其他端点将按照执行顺序从0xFF54开始分配UUID，依此类推。
 *
 * 创建的端点的protocomm处理程序将在配置开始后使用wifi-provmgr_endpoint_register（）进行注册。
 *
 * @note    只能在开始设置之前调用此API
 *
 * @note    其他端点可用于配置除Wi-Fi凭据之外的客户端提供的参数，这些参数是主应用程序所必需的，因此必须在启动应用程序之前设置
 *
 * @note    会话建立后，在发送Wi-Fi配置之前，客户端应用程序必须首先将其他端点作为目标，因为一旦Wi-Fi配置完成，配置服务将停止，因此所有端点都将注销
 *
 * @param[in] ep_name  端点的唯一名称
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：故障
 */
esp_err_t wifi_prov_mgr_endpoint_create(const char *ep_name);

/**
 * @brief   为先前创建的端点注册处理程序
 *
 * 应用程序可以调用此API，将protocomm处理程序注册到使用wifi_prov_mgr_endpoint_create（）创建的任何端点。
 *
 * @note    只能在设置开始后调用此API
 *
 * @note    其他端点可用于配置除Wi-Fi凭据之外的客户端提供的参数，这些参数是主应用程序所必需的，因此必须在启动应用程序之前设置
 *
 * @note    会话建立后，在发送Wi-Fi配置之前，客户端应用程序必须首先将其他端点作为目标，因为一旦Wi-Fi配置完成，配置服务将停止，因此所有端点都将注销
 *
 * @param[in] ep_name   端点的名称
 * @param[in] handler   终结点处理程序函数
 * @param[in] user_ctx  用户数据
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：故障
 */
esp_err_t wifi_prov_mgr_endpoint_register(const char *ep_name,
                                          protocomm_req_handler_t handler,
                                          void *user_ctx);

/**
 * @brief   注销终结点的处理程序
 *
 * 如果应用程序希望在配置过程中选择性地注销端点的处理程序，则可以调用此API。
 *
 * 当配置停止时，将自动注销所有端点处理程序。
 *
 * @param[in] ep_name  端点的名称
 */
void wifi_prov_mgr_endpoint_unregister(const char *ep_name);

/**
 * @brief   配置管理器的事件处理程序
 *
 * 这是从主事件处理程序调用的，并根据传入的Wi-Fi事件控制调配管理器的内部状态机
 *
 * @note ：此函数已弃用，因为现在使用事件循环库esp_event在内部处理事件。调用此函数将不会执行任何操作，只需返回ESP_OK。
 *
 * @param[in] ctx   事件上下文数据
 * @param[in] event 事件信息
 *
 * @return
 *  -ESP_OK:事件处理成功
 */
esp_err_t wifi_prov_mgr_event_handler(void *ctx, system_event_t *event) __attribute__ ((deprecated));

/**
 * @brief   设置期间获取Wi-Fi站点的状态
 *
 * @param[out] state    指向要填充的wifi_prov_sta_state_t变量的指针
 *
 * @return
 *  -ESP_OK:已成功检索Wi-Fi状态
 *  -ESP_FAIL:设置应用程序未运行
 */
esp_err_t wifi_prov_mgr_get_wifi_state(wifi_prov_sta_state_t *state);

/**
 * @brief   获取原因代码，以防在设置期间Wi-Fi站点断开
 *
* @param[out] reason    指向要填充的wifi_prov_sta_fail_reason_t变量的指针
 *
 * @return
 *  -ESP_OK:已成功检索到Wi-Fi断开原因
 *  -ESP_FAIL:设置应用程序未运行
 */
esp_err_t wifi_prov_mgr_get_wifi_disconnect_reason(wifi_prov_sta_fail_reason_t *reason);

/**
 * @brief   使用提供的配置将Wi-Fi作为站点运行
 *
 * 将Wi-Fi站点模式配置为使用配置结构中指定的SSID和密码连接到AP，并将Wi-Fi设置为作为站点运行。
 *
 * 当接收到新凭据时，配置服务会自动调用此功能。
 *
 * 如果要通过除protocomm之外的其他模式向管理器提供凭据，则需要调用此API。
 *
 * 应用凭据并启动Wi-Fi站点后，将发出事件WIFI_PROV_CRED_RECV
 *
 * @param[in] wifi_cfg  指向Wi-Fi配置结构的指针
 *
 * @return
 *  -ESP_OK:Wi-Fi已成功配置并启动
 *  -ESP_FAIL:无法设置配置
 */
esp_err_t wifi_prov_mgr_configure_sta(wifi_config_t *wifi_cfg);

/**
 * @brief   重置Wi-Fi设置配置
 *
 * 调用此API将WiFi堆栈持久设置恢复为默认值。
 *
 * @return
 *  -ESP_OK:成功重置设置配置
 *  -ESP_FAIL:无法重置设置配置
 */
esp_err_t wifi_prov_mgr_reset_provisioning(void);

/**
 * @brief   重置内部状态机并清除设置的凭据。
 *
 * 此API可用于在输入无效凭据时重新启动配置。
 *
 * @return
 *  -ESP_OK:成功重置配置状态机
 *  -ESP_FAIL:未能重置设置状态机
 *  -ESP_ERR_INVALID_STATE:管理器未初始化
 */
esp_err_t wifi_prov_mgr_reset_sm_state_on_failure(void);

#ifdef __cplusplus
}
#endif

