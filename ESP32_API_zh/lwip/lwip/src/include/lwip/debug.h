/**
 * @file 调试消息基础结构
 */

/*
 * 版权所有（c）2001-2004瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */
#ifndef LWIP_HDR_DEBUG_H
#define LWIP_HDR_DEBUG_H

#include "lwip/arch.h"
#include "lwip/opt.h"

/**
 * @defgroup 调试级别LWIP_DBG_MIN_LEVEL和LWIP_DBGP_TYPES_ON值
 * @ingroup lwip_opts_debugmsg@{
 */

/** @name 调试级别（LWIP_DBG_MIN_level）@{
 */
/**调试级别：所有消息*/
#define LWIP_DBG_LEVEL_ALL     0x00
/**调试级别：警告。错误的校验和、丢失的数据包。。。*/
#define LWIP_DBG_LEVEL_WARNING 0x01
/**调试级别：严重。内存分配失败。。。*/
#define LWIP_DBG_LEVEL_SERIOUS 0x02
/**调试级别：严重*/
#define LWIP_DBG_LEVEL_SEVERE  0x03
/**
 * @}
 */

#define LWIP_DBG_MASK_LEVEL    0x03
/* 兼容性仅定义*/
#define LWIP_DBG_LEVEL_OFF     LWIP_DBG_LEVEL_ALL

/** @name 完全启用/禁用调试消息（LWIP_DBG_TYPES_ON）@{
 */
/**LWIP_DEBUGF的标志以启用该调试消息*/
#define LWIP_DBG_ON            0x80U
/**LWIP_DEBUGF禁用该调试消息的标志*/
#define LWIP_DBG_OFF           0x00U
/**
 * @}
 */

/** @name 调试消息类型（LWIP_DBG_types_ON）@{
 */
/**LWIP_DEBUGF的标志，指示跟踪消息（遵循程序流）*/
#define LWIP_DBG_TRACE         0x40U
/**LWIP_DEBUGF的标志，指示状态调试消息（跟踪模块状态）*/
#define LWIP_DBG_STATE         0x20U
/**LWIP_DEBUGF的标志，指示新添加的代码，尚未完全测试*/
#define LWIP_DBG_FRESH         0x10U
/**打印此调试消息后LWIP_DEBUGF停止的标志*/
#define LWIP_DBG_HALT          0x08U
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup lwip_assertions断言处理
 * @ingroup lwip_opts_debug@{
 */
/**
 * LWIP_NOASSERT：禁用LWIP_ASSERT检查：若要禁用断言，请在arch/cc.h中定义LWIP_NOASSERT。
 */
#ifdef __DOXYGEN__
#define LWIP_NOASSERT
#undef LWIP_NOASSERT
#endif
/**
 * @}
 */

#ifndef LWIP_NOASSERT
#define LWIP_ASSERT(message, assertion) do { if (!(assertion)) { \
  LWIP_PLATFORM_ASSERT(message); }} while(0)
#else  /* LWIP_NOASSERT */
#define LWIP_ASSERT(message, assertion)
#endif /* LWIP_NOASSERT */

#ifndef LWIP_ERROR
#ifdef LWIP_DEBUG
#define LWIP_PLATFORM_ERROR(message) LWIP_PLATFORM_DIAG((message))
#else
#define LWIP_PLATFORM_ERROR(message)
#endif

/* 如果“expression”不为真，则打印“message”并执行“handler”表达式*/
#define LWIP_ERROR(message, expression, handler) do { if (!(expression)) { \
  LWIP_PLATFORM_ERROR(message); handler;}} while(0)
#endif /* LWIP_ERROR */

/** 启用调试消息打印，但前提是调试消息类型已启用且类型正确且至少为LWIP_DBG_LEVEL。
 */
#ifdef __DOXYGEN__
#define LWIP_DEBUG
#undef LWIP_DEBUG
#endif

#ifdef LWIP_DEBUG
#define LWIP_DEBUGF(debug, message) do { \
                               if ( \
                                   ((debug) & LWIP_DBG_ON) && \
                                   ((debug) & LWIP_DBG_TYPES_ON) && \
                                   ((s16_t)((debug) & LWIP_DBG_MASK_LEVEL) >= LWIP_DBG_MIN_LEVEL)) { \
                                 LWIP_PLATFORM_DIAG(message); \
                                 if ((debug) & LWIP_DBG_HALT) { \
                                   while(1); \
                                 } \
                               } \
                             } while(0)

#else  /* LWIP_DEBUG */
#define LWIP_DEBUGF(debug, message)
#endif /* LWIP_DEBUG */

#endif /* LWIP_HDR_DEBUG_H */

