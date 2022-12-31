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

#ifndef _SSL3_H_
#define _SSL3_H_

#ifdef __cplusplus
 extern "C" {
#endif

# define SSL3_AD_CLOSE_NOTIFY             0
# define SSL3_AD_UNEXPECTED_MESSAGE      10/* 致命的*/
# define SSL3_AD_BAD_RECORD_MAC          20/* 致命的*/
# define SSL3_AD_DECOMPRESSION_FAILURE   30/* 致命的*/
# define SSL3_AD_HANDSHAKE_FAILURE       40/* 致命的*/
# define SSL3_AD_NO_CERTIFICATE          41
# define SSL3_AD_BAD_CERTIFICATE         42
# define SSL3_AD_UNSUPPORTED_CERTIFICATE 43
# define SSL3_AD_CERTIFICATE_REVOKED     44
# define SSL3_AD_CERTIFICATE_EXPIRED     45
# define SSL3_AD_CERTIFICATE_UNKNOWN     46
# define SSL3_AD_ILLEGAL_PARAMETER       47/* 致命的*/

# define SSL3_AL_WARNING                  1
# define SSL3_AL_FATAL                    2

#define SSL3_VERSION                 0x0300

#ifdef __cplusplus
}
#endif

#endif

