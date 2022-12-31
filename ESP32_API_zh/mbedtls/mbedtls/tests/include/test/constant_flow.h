/**
 * \文件常量_flow.h
 *
 * \brief这个文件包含了确保测试代码具有恒定流的工具。
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

#ifndef TEST_CONSTANT_FLOW_H
#define TEST_CONSTANT_FLOW_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

/*
 * 此文件定义了两个宏
 *
 *  #define TEST_CF_SECRET（ptr，size）#define TEST-CF_PUBLIC（ptr、size）
 *
 * 可以在测试中将内存区域标记为secret（没有分支或内存访问应该依赖于它）或public（默认情况下，仅当它从secret数据派生时才需要显式标记）。
 *
 * 论据：
 * -ptr：指向要标记的内存区域的指针
 * -size：内存区域的字节大小
 *
 * 实施：基本思想是ctgrind<https://github.com/agl/ctgrind>：我们可以重用为检查未初始化内存使用情况而设计的工具。该文件包含两个实现：一个基于MemoryAnitizer，另一个基于valgrind的memcheck。如果它们都未启用，则为方便起见，将定义不执行任何操作的虚拟宏。
 */

#if defined(MBEDTLS_TEST_CONSTANT_FLOW_MEMSAN)
#include <sanitizer/msan_interface.h>

/* 使用宏避免干扰原点跟踪*/
#define TEST_CF_SECRET  __msan_allocated_memory
// void __msan_allocated_memory（常量易失性void*数据，size_t大小）；
#define TEST_CF_PUBLIC  __msan_unpoison
// void __msan_unpoison（常量volatile void*a，size_t size）；

#elif defined(MBEDTLS_TEST_CONSTANT_FLOW_VALGRIND)
#include <valgrind/memcheck.h>

#define TEST_CF_SECRET  VALGRIND_MAKE_MEM_UNDEFINED
// VALGRIND_MAKE_MEM_UNDFINED（_qzz_addr，_qzz_len）
#define TEST_CF_PUBLIC  VALGRIND_MAKE_MEM_DEFINED
// VALGRIND_MAKE_MEM_DEFINED（_qzz_addr，_qzz_len）

#else /* MBEDTLS_TEST_CONSTANT_FLOW_MEMSAN || MBEDTLS_TEST_CONSTANT_FLOW_VALGRIND */

#define TEST_CF_SECRET(ptr, size)
#define TEST_CF_PUBLIC(ptr, size)

#endif /* MBEDTLS_TEST_CONSTANT_FLOW_MEMSAN || MBEDTLS_TEST_CONSTANT_FLOW_VALGRIND */

#endif /* TEST_CONSTANT_FLOW_H */

