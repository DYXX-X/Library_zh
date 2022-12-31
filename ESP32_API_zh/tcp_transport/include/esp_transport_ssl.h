// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
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
// 许可证下的限制。

#ifndef _ESP_TRANSPORT_SSL_H_
#define _ESP_TRANSPORT_SSL_H_

#include "esp_transport.h"
#include "esp_tls.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief       创建新的SSL传输，传输句柄必须是release esp_transport_destroy回调
 *
 * @return      分配的esp_transport_handle_t，如果无法分配句柄，则为NULL
 */
esp_transport_handle_t esp_transport_ssl_init(void);

/**
 * @brief      设置SSL证书数据（PEM格式）。请注意，此函数存储指向数据的指针，而不是创建副本。因此，该数据必须保持有效，直到清除连接
 *
 * @param      t     ssl传输
 * @param[in]  data  pem数据
 * @param[in]  len   长度
 */
void esp_transport_ssl_set_cert_data(esp_transport_handle_t t, const char *data, int len);

/**
 * @brief      设置SSL证书数据（DER格式）。请注意，此函数存储指向数据的指针，而不是创建副本。因此，该数据必须保持有效，直到清除连接
 *
 * @param      t     ssl传输
 * @param[in]  data  订单数据
 * @param[in]  len   长度
 */
void esp_transport_ssl_set_cert_data_der(esp_transport_handle_t t, const char *data, int len);

/**
 * @brief      允许使用证书捆绑包对SSL连接进行服务器验证。它必须首先在menuconfig中启用。
 *
 * @param      t    ssl传输
 * @param[in]  crt_bundle_attach    指向esp_crt_bundle_attach的函数指针
 */
void esp_transport_ssl_crt_bundle_attach(esp_transport_handle_t t, esp_err_t ((*crt_bundle_attach)(void *conf)));

/**
 * @brief      为SSL连接启用全局CA存储
 *
 * @param      t    ssl传输
 */
void esp_transport_ssl_enable_global_ca_store(esp_transport_handle_t t);

/**
 * @brief      为相互身份验证设置SSL客户端证书数据（PEM格式）。请注意，此函数存储指向数据的指针，而不是创建副本。因此，该数据必须保持有效，直到清除连接
 *
 * @param      t     ssl传输
 * @param[in]  data  pem数据
 * @param[in]  len   长度
 */
void esp_transport_ssl_set_client_cert_data(esp_transport_handle_t t, const char *data, int len);

/**
 * @brief      为相互身份验证设置SSL客户端证书数据（采用DER格式）。请注意，此函数存储指向数据的指针，而不是创建副本。因此，该数据必须保持有效，直到清除连接
 *
 * @param      t     ssl传输
 * @param[in]  data  订单数据
 * @param[in]  len   长度
 */
void esp_transport_ssl_set_client_cert_data_der(esp_transport_handle_t t, const char *data, int len);

/**
 * @brief      为相互身份验证设置SSL客户端密钥数据（PEM格式）。请注意，此函数存储指向数据的指针，而不是创建副本。因此，该数据必须保持有效，直到清除连接
 *
 * @param      t     ssl传输
 * @param[in]  data  pem数据
 * @param[in]  len   长度
 */
void esp_transport_ssl_set_client_key_data(esp_transport_handle_t t, const char *data, int len);

/**
 * @brief      如果密钥受密码保护，请设置SSL客户端密钥密码。将配置的密码传递到基础TLS堆栈以解密客户端密钥
 *
 * @param      t     ssl传输
 * @param[in]  password  指向密码的指针
 * @param[in]  password_len   密码长度
 */
void esp_transport_ssl_set_client_key_password(esp_transport_handle_t t, const char *password, int password_len);

/**
 * @brief      为相互身份验证设置SSL客户端密钥数据（采用DER格式）。请注意，此函数存储指向数据的指针，而不是创建副本。因此，该数据必须保持有效，直到清除连接
 *
 * @param      t     ssl传输
 * @param[in]  data  订单数据
 * @param[in]  len   长度
 */
void esp_transport_ssl_set_client_key_data_der(esp_transport_handle_t t, const char *data, int len);

/**
 * @brief      设置要与ALPN一起使用的受支持的应用程序协议列表。请注意，此函数存储指向数据的指针，而不是创建副本。因此，该数据必须保持有效，直到清除连接
 *
 * @param      t            ssl传输
 * @param[in]  alpn_porot   ALPN协议列表，最后一项必须为NULL
 */
void esp_transport_ssl_set_alpn_protocol(esp_transport_handle_t t, const char **alpn_protos);

/**
 * @brief      跳过证书公用名称字段的验证
 *
 * @note       不建议跳过CN验证
 *
 * @param      t     ssl传输
 */
void esp_transport_ssl_skip_common_name_check(esp_transport_handle_t t);

/**
 * @brief      将ssl上下文设置为对客户端（设备）私钥和证书使用安全元素（atecc608a）
 *
 * @note       建议与ESP32-WROOM-32SE（内置ATECC608A，也称为安全元件）一起使用
 *
 * @param      t     ssl传输
 */
void esp_transport_ssl_use_secure_element(esp_transport_handle_t t);

/**
 * @brief      在ssl上下文中设置ds_data句柄。（用于数字签名操作）
 *
 * @param      t        ssl传输dsdata ds数据参数的句柄
 */
void esp_transport_ssl_set_ds_data(esp_transport_handle_t t, void *ds_data);

/**
 * @brief      为esp-tls组件中的PSK服务器/客户端验证设置PSK密钥和提示。重要注意事项：
 *             -此函数存储指向数据的指针，而不是创建副本。因此，该数据必须保持有效，直到清除连接
 *             -必须在menuconfig中启用ESP_TLS_PSK_VERIFICATION配置选项
 *             -证书验证具有优先级，因此不能将其配置为启用PSK方法。
 *
 * @param      t             ssl传输
 * @param[in]  psk_hint_key  esptls.h中定义的psk键和提示结构
 */
void esp_transport_ssl_set_psk_key_hint(esp_transport_handle_t t, const psk_hint_key_t* psk_hint_key);

/**
 * @brief      在当前ssl上下文中设置保持活动状态
 *
 * @param[in]  t               ssl传输
 * @param[in]  keep_alive_cfg  保持活动配置的句柄
 */
void esp_transport_ssl_set_keep_alive(esp_transport_handle_t t, esp_transport_keep_alive_t *keep_alive_cfg);

/**
 * @brief      设置套接字可以绑定的接口的名称，以便数据可以在此接口上传输
 *
 * @param[in]  t        运输手柄
 * @param[in]  if_name  接口名称
 */
void esp_transport_ssl_set_interface_name(esp_transport_handle_t t, struct ifreq *if_name);

#ifdef __cplusplus
}
#endif
#endif /* _ESP_TRANSPORT_SSL_H_ */

