/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef ESP_HOSTAP_H
#define ESP_HOSTAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sdkconfig.h"
#ifdef CONFIG_ESP_WIFI_SOFTAP_SUPPORT
void *hostap_init(void);
bool hostap_deinit(void *data);
#endif

#ifdef __cplusplus
}
#endif

#endif /* ESP_HOSTAP_H */

