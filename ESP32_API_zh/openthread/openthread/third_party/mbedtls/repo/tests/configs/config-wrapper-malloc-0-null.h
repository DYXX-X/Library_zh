/* 配置。h包装器，强制calloc（0）返回NULL。用于测试。
 */
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef MBEDTLS_CONFIG_H
/* 不要#define MBEDTLS_CONFIG_H，让CONFIG。我做了。*/

#include "mbedtls/config.h"

#include <stdlib.h>
static inline void *custom_calloc( size_t nmemb, size_t size )
{
    if( nmemb == 0 || size == 0 )
        return( NULL );
    return( calloc( nmemb, size ) );
}

#define MBEDTLS_PLATFORM_MEMORY
#define MBEDTLS_PLATFORM_STD_CALLOC custom_calloc

#endif /* MBEDTLS_CONFIG_H */

