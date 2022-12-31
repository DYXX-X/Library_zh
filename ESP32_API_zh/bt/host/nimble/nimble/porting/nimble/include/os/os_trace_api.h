/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef OS_TRACE_API_H
#define OS_TRACE_API_H

#include <stdint.h>

#define OS_TRACE_ID_EVENTQ_PUT                  (40)
#define OS_TRACE_ID_EVENTQ_GET_NO_WAIT          (41)
#define OS_TRACE_ID_EVENTQ_GET                  (42)
#define OS_TRACE_ID_EVENTQ_REMOVE               (43)
#define OS_TRACE_ID_EVENTQ_POLL_0TIMO           (44)
#define OS_TRACE_ID_EVENTQ_POLL                 (45)
#define OS_TRACE_ID_MUTEX_INIT                  (50)
#define OS_TRACE_ID_MUTEX_RELEASE               (51)
#define OS_TRACE_ID_MUTEX_PEND                  (52)
#define OS_TRACE_ID_SEM_INIT                    (60)
#define OS_TRACE_ID_SEM_RELEASE                 (61)
#define OS_TRACE_ID_SEM_PEND                    (62)

static inline void
os_trace_isr_enter(void)
{
}

static inline void
os_trace_isr_exit(void)
{
}

static inline void
os_trace_idle(void)
{
}

static inline void
os_trace_api_void(unsigned id)
{
}

static inline void
os_trace_api_u32(unsigned id, uint32_t p0)
{
}

static inline void
os_trace_api_u32x2(unsigned id, uint32_t p0, uint32_t p1)
{
}

static inline void
os_trace_api_u32x3(unsigned id, uint32_t p0, uint32_t p1, uint32_t p2)
{
}

static inline void
os_trace_api_ret(unsigned id)
{
}

static inline void
os_trace_api_ret_u32(unsigned id, uint32_t return_value)
{
}

#endif

