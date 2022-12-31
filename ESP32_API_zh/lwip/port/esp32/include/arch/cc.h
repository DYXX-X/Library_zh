/*
 * 版权所有（c）2001，瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用研究所的名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */
#ifndef __ARCH_CC_H__
#define __ARCH_CC_H__

#include <stdint.h>
#include <errno.h>
#include <assert.h>
#include <stdio.h>

#include "sdkconfig.h"
#include "arch/sys_arch.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif // BYTE_ORDER

#ifndef CONFIG_LWIP_ESP_LWIP_ASSERT
#define LWIP_NOASSERT 1
#endif

typedef uint8_t  u8_t;
typedef int8_t   s8_t;
typedef uint16_t u16_t;
typedef int16_t  s16_t;
typedef uint32_t u32_t;
typedef int32_t  s32_t;


typedef int sys_prot_t;

#define S16_F "d"
#define U16_F "d"
#define X16_F "x"

#define S32_F "d"
#define U32_F "u"
#define X32_F "x"

#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_STRUCT __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END

#include <stdio.h>

#define LWIP_PLATFORM_DIAG(x)   do {printf x;} while(0)

#ifdef NDEBUG

#define LWIP_NOASSERT 1

#else // 已启用断言

#if CONFIG_OPTIMIZATION_ASSERTIONS_SILENT
#define LWIP_PLATFORM_ASSERT(message) abort()
#else
// __assert_func是newlib中的断言失败处理程序，在assert.h中定义
#define LWIP_PLATFORM_ASSERT(message) __assert_func(__FILE__, __LINE__, __ASSERT_FUNC, message)
#endif

// 如果断言处于启用状态，则默认LWIP_ERROR处理程序行为为
// 断言失败时中止。不要这样做，只需打印错误（如果设置了LWIP_DEBUG）
// 并运行处理程序（如果设置了LWIP_NOASSERT，则与LWIP_ERROR行为相同）。
#ifdef LWIP_DEBUG
#define LWIP_ERROR(message, expression, handler) do { if (!(expression)) { \
  puts(message); handler;}} while(0)
#else
// 如果未设置LWIP_DEBUG，则以静默方式返回错误（默认LWIP行为也是如此）
#define LWIP_ERROR(message, expression, handler) do { if (!(expression)) { \
  handler;}} while(0)
#endif // LWIP_DEBUG

#endif /* NDEBUG */

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_CC_H__ */

