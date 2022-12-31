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

#ifndef _TLS1_H_
#define _TLS1_H_

#ifdef __cplusplus
 extern "C" {
#endif

# define TLS1_AD_DECRYPTION_FAILED       21
# define TLS1_AD_RECORD_OVERFLOW         22
# define TLS1_AD_UNKNOWN_CA              48/* 致命的*/
# define TLS1_AD_ACCESS_DENIED           49/* 致命的*/
# define TLS1_AD_DECODE_ERROR            50/* 致命的*/
# define TLS1_AD_DECRYPT_ERROR           51
# define TLS1_AD_EXPORT_RESTRICTION      60/* 致命的*/
# define TLS1_AD_PROTOCOL_VERSION        70/* 致命的*/
# define TLS1_AD_INSUFFICIENT_SECURITY   71/* 致命的*/
# define TLS1_AD_INTERNAL_ERROR          80/* 致命的*/
# define TLS1_AD_INAPPROPRIATE_FALLBACK  86/* 致命的*/
# define TLS1_AD_USER_CANCELLED          90
# define TLS1_AD_NO_RENEGOTIATION        100
/* 代码110-114来自RFC3546*/
# define TLS1_AD_UNSUPPORTED_EXTENSION   110
# define TLS1_AD_CERTIFICATE_UNOBTAINABLE 111
# define TLS1_AD_UNRECOGNIZED_NAME       112
# define TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE 113
# define TLS1_AD_BAD_CERTIFICATE_HASH_VALUE 114
# define TLS1_AD_UNKNOWN_PSK_IDENTITY    115/* 致命的*/
# define TLS1_AD_NO_APPLICATION_PROTOCOL 120 /* 致命的*/

/* 支持多个版本的方法的特殊值*/
#define TLS_ANY_VERSION                 0x10000

#define TLS1_VERSION                    0x0301
#define TLS1_1_VERSION                  0x0302
#define TLS1_2_VERSION                  0x0303

#ifdef __cplusplus
}
#endif

#endif

