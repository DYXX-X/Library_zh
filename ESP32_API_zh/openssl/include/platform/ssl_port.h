// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#ifndef _SSL_PORT_H_
#define _SSL_PORT_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "esp_types.h"
#include "esp_log.h"
#include "string.h"
#include "malloc.h"

void *ssl_mem_zalloc(size_t size);

#define ssl_mem_malloc malloc
#define ssl_mem_free   free

#define ssl_memcpy     memcpy
#define ssl_strlen     strlen

#define ssl_speed_up_enter()
#define ssl_speed_up_exit()

#define SSL_DEBUG_FL
#define SSL_DEBUG_LOG(fmt, ...) ESP_LOGI("openssl", fmt, ##__VA_ARGS__)

#ifdef __cplusplus
 }
#endif

#endif

