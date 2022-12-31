/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#include "esp_openthread.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 此函数用于初始化OpenThread命令行界面（CLI）。
 *
 */
void esp_openthread_cli_init(void);

/**
 * @brief 此函数向OpenThread CLI提供一行。
 *
 * @note 此函数是线程安全的，该行将被复制并发布到OpenThread任务队列。
 *
 * @param[in] line  输入行。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果分配失败，则为ESP_ERR_NO_MEM
 *
 */
esp_err_t esp_openthread_cli_input(const char *line);

/**
 * @brief 此函数启动OpenThread CLI的独占循环。
 *
 * @param[in] priority  创建的任务的优先级。
 *
 */
void esp_openthread_cli_create_task(void);


#ifdef __cplusplus
}
#endif

