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

#ifndef _SSL_CERT_H_
#define _SSL_CERT_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "ssl_types.h"

/**
 * @brief 根据输入证书创建证书对象include私钥对象
 *
 * @param ic -输入认证点
 *
 * @return 认证对象点
 */
CERT *__ssl_cert_new(CERT *ic);

/**
 * @brief 创建证书对象包含私钥对象
 *
 * @param none
 *
 * @return 认证对象点
 */
CERT* ssl_cert_new(void);

/**
 * @brief 释放证书对象
 *
 * @param cert -认证对象点
 *
 * @return 没有一个
 */
void ssl_cert_free(CERT *cert);

#ifdef __cplusplus
}
#endif

#endif

