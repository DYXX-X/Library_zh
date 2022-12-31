/**
 * \文件common.h
 *
 * \库中内部使用的简短实用程序宏
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

#ifndef MBEDTLS_LIBRARY_COMMON_H
#define MBEDTLS_LIBRARY_COMMON_H

#if defined(MBEDTLS_CONFIG_FILE)
#include MBEDTLS_CONFIG_FILE
#else
#include "mbedtls/config.h"
#endif

/** 帮助程序将函数定义为静态，除非在构建侵入性测试时。
 *
 * 如果函数仅在其自身的源文件中使用，并且应声明为“static”以允许编译器优化代码大小，但该函数具有单元测试，请使用“``MBEDTLS_static_TESTABLE int MBEDTLS_foo（…）｛…｝``”来定义它，并在“library/”目录的头中使用“``”（如果定义了（MBEDTL_TEST_HOOKS）int MBEDTLS _foo（.）来声明它#结束符```
 */
#if defined(MBEDTLS_TEST_HOOKS)
#define MBEDTLS_STATIC_TESTABLE
#else
#define MBEDTLS_STATIC_TESTABLE static
#endif

#endif /* MBEDTLS_LIBRARY_COMMON_H */

