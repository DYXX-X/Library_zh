/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


#ifndef _HTTP_BASIC_AUTH_H_
#define _HTTP_BASIC_AUTH_H_

/**
 * HTTP摘要身份验证数据
 */
typedef struct {
    char *method;       /*!< 请求方法，例如：GET*/
    char *algorithm;    /*!< 身份验证算法*/
    char *uri;          /*!< 请求示例的URI：/path/to/file。html格式*/
    char *realm;        /*!< 身份验证领域*/
    char *nonce;        /*!< 身份验证随机数*/
    char *qop;          /*!< 身份验证qop*/
    char *opaque;       /*!< 身份验证不透明*/
    uint64_t cnonce;    /*!< 身份验证证书*/
    int nc;             /*!< 身份验证nc*/
} esp_http_auth_data_t;

/**
 * @brief      这用于Http摘要身份验证方法，创建用于摘要身份验证的Http头。返回的字符串在使用后需要释放
 *
 * @param[in]  username   用户名
 * @param[in]  password   密码
 * @param      auth_data  身份验证数据
 *
 * @return
 *     -授权的HTTP标头值，对摘要身份验证有效，必须在使用后释放
 *     - NULL
 */
char *http_auth_digest(const char *username, const char *password, esp_http_auth_data_t *auth_data);

/**
 * @brief      这用于Http基本身份验证方法，为基本Http身份验证创建头值使用后返回的字符串需要释放
 *
 * @param[in]  username  用户名
 * @param[in]  password  密码
 *
 * @return
 *     -授权的HTTP标头值，对基本身份验证有效，使用后必须是免费的
 *     - NULL
 */
char *http_auth_basic(const char *username, const char *password);
#endif

