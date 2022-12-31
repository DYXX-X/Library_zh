// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#ifndef _OPENSSL_ERR_H
#define _OPENSSL_ERR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @note 此文件包含OpenSSL的ESP API存根的错误堆栈的一个非常简单的实现
 */

#define OPENSSL_PUT_SYSTEM_ERROR() \
  ERR_put_error(ERR_LIB_SYS, 0, 0, __FILE__, __LINE__);

#define OPENSSL_PUT_LIB_ERROR(lib, code) \
  ERR_put_error(lib, 0, code, __FILE__, __LINE__);

#define ERR_GET_LIB(packed_error) ((int)(((packed_error) >> 24) & 0xff))
#define ERR_GET_REASON(packed_error) ((int)((packed_error) & 0xffff))
#define ERR_R_PEM_LIB ERR_LIB_PEM
/* 固有的openssl错误*/
# define ERR_R_FATAL                             64
# define ERR_R_MALLOC_FAILURE                    (1|ERR_R_FATAL)
# define ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED       (2|ERR_R_FATAL)
# define ERR_R_PASSED_NULL_PARAMETER             (3|ERR_R_FATAL)
# define ERR_R_INTERNAL_ERROR                    (4|ERR_R_FATAL)
# define ERR_R_DISABLED                          (5|ERR_R_FATAL)
# define ERR_R_INIT_FAIL                         (6|ERR_R_FATAL)
# define ERR_R_PASSED_INVALID_ARGUMENT           (7)
# define ERR_R_OPERATION_FAIL                    (8|ERR_R_FATAL)
# define ERR_R_INVALID_PROVIDER_FUNCTIONS        (9|ERR_R_FATAL)
# define ERR_R_INTERRUPTED_OR_CANCELLED          (10)

enum {
    ERR_LIB_NONE = 1,
    ERR_LIB_SYS,
    ERR_LIB_BN,
    ERR_LIB_RSA,
    ERR_LIB_DH,
    ERR_LIB_EVP,
    ERR_LIB_BUF,
    ERR_LIB_OBJ,
    ERR_LIB_PEM,
    ERR_LIB_DSA,
    ERR_LIB_X509,
    ERR_LIB_ASN1,
    ERR_LIB_CONF,
    ERR_LIB_CRYPTO,
    ERR_LIB_EC,
    ERR_LIB_SSL,
    ERR_LIB_BIO,
    ERR_LIB_PKCS7,
    ERR_LIB_PKCS8,
    ERR_LIB_X509V3,
    ERR_LIB_RAND,
    ERR_LIB_ENGINE,
    ERR_LIB_OCSP,
    ERR_LIB_UI,
    ERR_LIB_COMP,
    ERR_LIB_ECDSA,
    ERR_LIB_ECDH,
    ERR_LIB_HMAC,
    ERR_LIB_DIGEST,
    ERR_LIB_CIPHER,
    ERR_LIB_HKDF,
    ERR_LIB_USER,
    ERR_NUM_LIBS
};

/**
 * @brief 清除SSL错误代码
 *
 * @param none
 *
 * @return 没有一个
 */
void ERR_clear_error(void);

/**
 * @brief 获取当前SSL错误代码
 *
 * @param none
 *
 * @return 当前SSL错误号
 */
uint32_t ERR_get_error(void);

/**
 * @brief 查看当前SSL错误代码，而不是清除它
 *
 * @param none
 *
 * @return 当前SSL错误号
 */
uint32_t ERR_peek_error(void);

/**
 * @brief 查看最后一个SSL错误代码，而不是清除它
 *
 * @param none
 *
 * @return 当前SSL错误号
 */
uint32_t ERR_peek_last_error(void);

/**
 * @brief 注册SSL错误字符串
 *
 * @param none
 *
 * @return 没有一个
 */
void ERR_load_SSL_strings(void);

/**
 * @brief 清除SSL错误代码
 *
 * @param none
 *
 * @return 没有一个
 */
void ERR_clear_error(void);

/**
 * @brief 查看当前SSL错误代码，而不是清除它
 *
 * @param none
 *
 * @return 当前SSL错误号
 */
uint32_t ERR_peek_error(void);

/**
 * @brief 查看最后一个SSL错误代码，而不是清除它
 *
 * @param none
 *
 * @return 当前SSL错误号
 */
uint32_t ERR_peek_last_error(void);

/**
 * @brief 将当前错误捕获到错误结构
 *
 * @param library 相关库
 * @param unused 未使用（用于兼容功能原型）
 * @param reason 实际错误代码
 * @param file 错误报告的文件名
 * @param line 错误报告的行号
 *
 */
void ERR_put_error(int library, int unused, int reason, const char *file, unsigned line);

/**
 * @brief 查看当前SSL错误，不清除它
 *
 * @param file 报告错误的文件名
 * @param line 报告错误的行号
 * @param data 与报告的错误关联的数据
 * @param flags 与错误相关的标志
 *
 * @return 当前SSL错误号
 */
uint32_t ERR_peek_error_line_data(const char **file, int *line,
                                  const char **data, int *flags);

/**
 * @brief 获取当前SSL错误
 *
 * @param file 报告错误的文件名
 * @param line 报告错误的行号
 * @param data 与报告的错误关联的数据
 * @param flags 与错误相关的标志
 *
 * @return 当前SSL错误号
 */
uint32_t ERR_get_error_line_data(const char **file, int *line,
                                  const char **data, int *flags);

/**
 * @brief API仅作为声明提供
 *
 */
void SSL_load_error_strings(void);

/**
 * @brief API仅作为声明提供
 *
 */
void ERR_free_strings(void);

/**
 * @brief API仅作为声明提供
 *
 */
void ERR_remove_state(unsigned long pid);

/**
 * @brief 返回错误字符串--未实现
 *
 * @param packed_error 打包错误代码
 *
 * @return NULL
 */
const char *ERR_reason_error_string(uint32_t packed_error);

#ifdef __cplusplus
}
#endif

#endif // _OPENSSL_ERR_H

