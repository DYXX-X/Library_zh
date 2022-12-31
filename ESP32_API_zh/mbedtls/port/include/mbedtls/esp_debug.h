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
#ifndef _ESP_DEBUG_H_
#define _ESP_DEBUG_H_

#include "mbedtls/ssl.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "sdkconfig.h"
#ifdef CONFIG_MBEDTLS_DEBUG

/** @brief 通过esp_log机制启用mbedTLS调试日志记录。
 *
 * mbedTLS内部调试在运行时从指定的mbedTLS阈值级别过滤到esp_log级别：
 *
 * -1-警告
 * -2-信息
 * -3-调试
 * -4-详细
 *
 * （请注意，mbedTLS调试阈值并不总是一致使用。）
 *
 * 此函数将“mbedtls”的esp日志级别设置为匹配的指定mbedtls阈值级别。但是，必须在menuconfig中将总体最大ESP日志级别设置得足够高，否则可能会在编译时过滤某些消息。
 *
 * @param conf mbedtls_ssl_config结构
 * @param mbedTLS 调试阈值，0-4。消息在运行时过滤。
 */
void mbedtls_esp_enable_debug_log(mbedtls_ssl_config *conf, int threshold);

/** @brief 通过esp_log机制禁用mbedTLS调试日志记录。
 *
 */
void mbedtls_esp_disable_debug_log(mbedtls_ssl_config *conf);


#endif

#ifdef __cplusplus
}
#endif

#endif /* __ESP_DEBUG_H__ */

