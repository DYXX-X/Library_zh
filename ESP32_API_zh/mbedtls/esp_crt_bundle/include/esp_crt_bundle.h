// 版权所有2017-2019 Espressif Systems（上海）私人有限公司
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


#ifndef _ESP_CRT_BUNDLE_H_
#define _ESP_CRT_BUNDLE_H_

#include "mbedtls/ssl.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief      附加并启用用于证书验证的捆绑包
 *
 * 通过验证回调附加并启用用于证书验证的捆绑包。如果没有通过esp_crt_bundle_set（）设置特定的捆绑包，它将默认为menuconfig中定义并嵌入二进制文件中的捆绑包。
 *
 * @param[in]  conf      SSL连接的配置结构。
 *
 * @return
 *             -如果添加证书成功，则返回ESP_OK。
 *             -如果发生错误或调用进程必须采取操作，则为其他。
 */
esp_err_t esp_crt_bundle_attach(void *conf);


/**
 * @brief      禁用和解除分配证书捆绑包
 *
 * 删除证书验证回调并释放已使用的资源
 *
 * @param[in]  conf      SSL连接的配置结构。
 */
void esp_crt_bundle_detach(mbedtls_ssl_config *conf);


/**
 * @brief      设置用于验证的默认证书包
 *
 * 覆盖默认证书捆绑包。在大多数情况下，应该通过menuconfig设置捆绑包。捆绑包需要按主题名称排序，因为二进制搜索用于查找证书。
 *
 * @param[in]  x509_bundle     指向证书捆绑包的指针。
 */
void esp_crt_bundle_set(const uint8_t *x509_bundle);


#ifdef __cplusplus
}
#endif

#endif //_ESP_CRT_BUNDLE_H_

