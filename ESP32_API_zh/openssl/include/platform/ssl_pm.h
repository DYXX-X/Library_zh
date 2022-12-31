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

#ifndef _SSL_PM_H_
#define _SSL_PM_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <string.h>
#include "ssl_types.h"
#include "ssl_port.h"

#define LOCAL_ATRR

int ssl_pm_new(SSL *ssl);
void ssl_pm_free(SSL *ssl);

int ssl_pm_handshake(SSL *ssl);
int ssl_pm_shutdown(SSL *ssl);
int ssl_pm_clear(SSL *ssl);

int ssl_pm_read(SSL *ssl, void *buffer, int len);
int ssl_pm_send(SSL *ssl, const void *buffer, int len);
int ssl_pm_pending(const SSL *ssl);

void ssl_pm_set_fd(SSL *ssl, int fd, int mode);
int ssl_pm_get_fd(const SSL *ssl, int mode);

void ssl_pm_set_hostname(SSL *ssl, const char *hostname);

OSSL_HANDSHAKE_STATE ssl_pm_get_state(const SSL *ssl);

void ssl_pm_set_bufflen(SSL *ssl, int len);

int x509_pm_show_info(X509 *x);
int x509_pm_new(X509 *x, X509 *m_x);
void x509_pm_free(X509 *x);
int x509_pm_load(X509 *x, const unsigned char *buffer, int len);

int pkey_pm_new(EVP_PKEY *pk, EVP_PKEY *m_pk);
void pkey_pm_free(EVP_PKEY *pk);
int pkey_pm_load(EVP_PKEY *pk, const unsigned char *buffer, int len);

long ssl_pm_get_verify_result(const SSL *ssl);

#ifdef __cplusplus
 }
#endif

#endif

