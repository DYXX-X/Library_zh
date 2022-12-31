/*
 * SPDX文件版权所有文本：2019-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_WPA2_H
#define _ESP_WPA2_H

#include <stdbool.h>

#include "esp_err.h"

typedef enum {
    ESP_EAP_TTLS_PHASE2_EAP,
    ESP_EAP_TTLS_PHASE2_MSCHAPV2,
    ESP_EAP_TTLS_PHASE2_MSCHAP,
    ESP_EAP_TTLS_PHASE2_PAP,
    ESP_EAP_TTLS_PHASE2_CHAP
} esp_eap_ttls_phase2_types;

typedef struct {
   int fast_provisioning;
   int fast_max_pac_list_len;
   bool fast_pac_format_binary;
} esp_eap_fast_config;

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  启用wpa2企业身份验证。
  *
  * @attention 1.wpa2企业身份验证只能在启用ESP32站时使用。
  * @attention 2.wpa2企业身份验证只能支持TLS、PEAP-MSCHAPv2和TTLS-MSCHAPv2方法。
  *
  * @return
  *    -ESP_OK：成功。
  *    -ESP_ERR_NO_MEM:失败（内部内存malloc失败）
  */
esp_err_t esp_wifi_sta_wpa2_ent_enable(void);

/**
  * @brief  禁用wpa2企业身份验证。
  *
  * @attention 1.wpa2企业身份验证只能在启用ESP32站时使用。
  * @attention 2.wpa2企业身份验证只能支持TLS、PEAP-MSCHAPv2和TTLS-MSCHAPv2方法。
  *
  * @return
  *    -ESP_OK：成功。
  */
esp_err_t esp_wifi_sta_wpa2_ent_disable(void);

/**
  * @brief  设置PEAP/TTLS方法的标识。
  *
  * @attention API只将参数标识传递给wpa2企业模块中的全局指针变量。
  *
  * @param  identity: 指向存储身份的地址；
  * @param  len: 身份长度，限制为1~127
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_INVALID_ARG：失败（len<=0或len>=128）
  *    -ESP_ERR_NO_MEM:失败（内部内存malloc失败）
  */
esp_err_t esp_wifi_sta_wpa2_ent_set_identity(const unsigned char *identity, int len);

/**
  * @brief  清除PEAP/TTLS方法的标识。
  */
void esp_wifi_sta_wpa2_ent_clear_identity(void);

/**
  * @brief  设置PEAP/TTLS方法的用户名。
  *
  * @attention API只将参数username传递给wpa2企业模块中的全局指针变量。
  *
  * @param  username: 指向存储用户名的地址；
  * @param  len: 用户名长度，限制为1~127
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_INVALID_ARG：失败（len<=0或len>=128）
  *    -ESP_ERR_NO_MEM:失败（内部内存malloc失败）
  */
esp_err_t esp_wifi_sta_wpa2_ent_set_username(const unsigned char *username, int len);

/**
  * @brief  清除PEAP/TTLS方法的用户名。
  */
void esp_wifi_sta_wpa2_ent_clear_username(void);

/**
  * @brief  设置PEAP/TTLS方法的密码。。
  *
  * @attention API只将参数密码传递给wpa2企业模块中的全局指针变量。
  *
  * @param  password: 指向存储密码的地址；
  * @param  len: 密码长度（长度>0）
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_INVALID_ARG：失败（长度<=0）
  *    -ESP_ERR_NO_MEM:失败（内部内存malloc失败）
  */
esp_err_t esp_wifi_sta_wpa2_ent_set_password(const unsigned char *password, int len);

/**
  * @brief  清除PEAP/TTLS方法的密码。。
  */
void esp_wifi_sta_wpa2_ent_clear_password(void);

/**
  * @brief  为MSCHAPv2方法设置新密码。。
  *
  * @attention 1.API只将参数密码传递给wpa2企业模块中的全局指针变量。
  * @attention 2.当收到错误代码为error_PASSWD_EXPIRED的eap-mschapv2失败请求消息时，使用新密码替换旧密码。
  *
  * @param  new_password: 指向存储密码的地址；
  * @param  len: 密码长度
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_INVALID_ARG：失败（长度<=0）
  *    -ESP_ERR_NO_MEM:失败（内部内存malloc失败）
  */

esp_err_t esp_wifi_sta_wpa2_ent_set_new_password(const unsigned char *new_password, int len);

/**
  * @brief  清除MSCHAPv2方法的新密码。。
  */
void esp_wifi_sta_wpa2_ent_clear_new_password(void);

/**
  * @brief  为PEAP/TTLS方法设置CA证书。
  *
  * @attention 1.API只将参数ca_cert传递给wpa2企业模块中的全局指针变量。
  * @attention 2.ca_cert应以零结尾。
  *
  * @param  ca_cert: 指向存储CA证书的地址；
  * @param  ca_cert_len: ca_证书长度
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_sta_wpa2_ent_set_ca_cert(const unsigned char *ca_cert, int ca_cert_len);

/**
  * @brief  清除PEAP/TTLS方法的CA证书。
  */
void esp_wifi_sta_wpa2_ent_clear_ca_cert(void);

/**
  * @brief  设置客户端证书和密钥。
  *
  * @attention 1.API只将参数client_cert、private_key和private_key_passwd传递给wpa2企业模块中的全局指针变量。
  * @attention 2.client_cert、private_key和private_key_passwd应以零结尾。
  *
  * @param  client_cert: 指向存储客户端证书的地址；
  * @param  client_cert_len: 客户证书的长度；
  * @param  private_key: 指向存储私钥的地址；
  * @param  private_key_len: 私钥长度，限制为1~2048；
  * @param  private_key_password: 指向存储私钥密码的地址；
  * @param  private_key_password_len: 私钥密码的长度；
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_sta_wpa2_ent_set_cert_key(const unsigned char *client_cert, int client_cert_len, const unsigned char *private_key, int private_key_len, const unsigned char *private_key_passwd, int private_key_passwd_len);

/**
  * @brief  清除客户端证书和密钥。
  */
void esp_wifi_sta_wpa2_ent_clear_cert_key(void);

/**
  * @brief  设置wpa2企业证书时间检查（禁用或不禁用）。
  *
  * @param  true: 禁用wpa2企业证书时间检查
  * @param  false: 启用wpa2企业证书时间检查
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_sta_wpa2_ent_set_disable_time_check(bool disable);

/**
  * @brief  获取wpa2企业证书时间检查（禁用或不禁用）。
  *
  * @param  disable: 存储禁用值
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_sta_wpa2_ent_get_disable_time_check(bool *disable);

/**
  * @brief  设置wpa2企业ttls阶段2方法
  *
  * @param  type: 要使用的第2阶段方法的类型
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_sta_wpa2_ent_set_ttls_phase2_method(esp_eap_ttls_phase2_types type);

/**
  * @brief  启用/禁用192位套件b认证检查
  *
  * @param  enable: bool以启用/禁用它。
  *
  * @return
  *    -ESP_OK：成功
  */
esp_err_t esp_wifi_sta_wpa2_set_suiteb_192bit_certification(bool enable);

/**
  * @brief  设置客户端pac文件
  *
  * @attention  1.对于从文件系统读取的文件，长度必须减少1字节。
  * @attention  2.需要禁用WPA_MBEDTLS_CRYPTO配置才能使用EAP-FAST。
  *
  * @param  pac_file: 指向pac文件pac_file_len的指针：pac文件的长度
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_NO_MEM:失败（内部内存malloc失败）
  */
esp_err_t esp_wifi_sta_wpa2_ent_set_pac_file(const unsigned char *pac_file, int pac_file_len);

/**
  * @brief  设置EAP-FAST的阶段1参数
  *
  * @attention  1.需要禁用WPA_MBEDTLS_CRYPTO配置才能使用EAP-FAST。
  *
  * @param  config: eap快速阶段1配置
  *
  * @return
  *    -ESP_OK：成功
  *    -ESP_ERR_INVALID_ARG：失败（参数超出界限）
  *    -ESP_ERR_NO_MEM:失败（内部内存malloc失败）
  */
esp_err_t esp_wifi_sta_wpa2_ent_set_fast_phase1_params(esp_eap_fast_config config);

#ifdef __cplusplus
}
#endif
#endif

