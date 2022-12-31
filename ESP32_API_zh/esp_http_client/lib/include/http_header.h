/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _HTTP_HEADER_H_
#define _HTTP_HEADER_H_

#include "sys/queue.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http_header *http_header_handle_t;
typedef struct http_header_item *http_header_item_handle_t;

/**
 * @brief      初始化并分配头对象的内存
 *
 * @return
 *     -http_header_handle_t
 *     -如果有错误，则为NULL
 */
http_header_handle_t http_header_init(void);

/**
 * @brief      清理并释放所有http标头对
 *
 * @param[in]  header  收割台
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t http_header_clean(http_header_handle_t header);

/**
 * @brief      使用http_header_clean清理并销毁http标头句柄对象
 *
 * @param[in]  header  收割台
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t http_header_destroy(http_header_handle_t header);

/**
 * @brief      向列表中添加一对http头的键值，注意，如果值为NULL，此函数将删除列表中已存在“key”的头。
 *
 * @param[in]  header  收割台
 * @param[in]  key     钥匙
 * @param[in]  value   价值
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t http_header_set(http_header_handle_t header, const char *key, const char *value);

/**
 * @brief      示例为“http_header_set”，但该值可以格式化
 *
 * @param[in]  header     收割台
 * @param[in]  key        钥匙
 * @param[in]  format     格式
 * @param[in]  ...        格式参数
 *
 * @return     价值的总长度
 */
int http_header_set_format(http_header_handle_t header, const char *key, const char *format, ...);

/**
 * @brief      获取标头列表中标头的值。如果列表中不存在带有关键字的标头，则值的地址将被赋值为“value”参数或NULL
 *
 * @param[in]  header  收割台
 * @param[in]  key     钥匙
 * @param[out] value   价值
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t http_header_get(http_header_handle_t header, const char *key, char **value);

/**
 * @brief      从带有索引的头创建HTTP头字符串，将字符串输出到带有buffer_len的缓冲区。还返回生成的头的最后一个索引
 *
 * @param[in]  header      收割台
 * @param[in]  index       索引
 * @param      buffer      缓冲区
 * @param      buffer_len  缓冲区长度
 *
 * @return     已生成头的最后一个索引
 */
int http_header_generate_string(http_header_handle_t header, int index, char *buffer, int *buffer_len);

/**
 * @brief      从标题列表中删除带有关键字的标题
 *
 * @param[in]  header  收割台
 * @param[in]  key     钥匙
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t http_header_delete(http_header_handle_t header, const char *key);

#ifdef __cplusplus
}
#endif

#endif

