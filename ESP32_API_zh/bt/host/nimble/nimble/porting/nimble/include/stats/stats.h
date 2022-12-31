/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef __STATS_H__
#define __STATS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STATS_SECT_DECL(__name)         struct stats_ ## __name
#define STATS_SECT_END                  };

#define STATS_SECT_START(__name)        STATS_SECT_DECL(__name) {
#define STATS_SECT_VAR(__var)

#define STATS_HDR(__sectname)           NULL

#define STATS_SECT_ENTRY(__var)
#define STATS_SECT_ENTRY16(__var)
#define STATS_SECT_ENTRY32(__var)
#define STATS_SECT_ENTRY64(__var)
#define STATS_RESET(__var)

#define STATS_SIZE_INIT_PARMS(__sectvarname, __size) \
                                        0, 0

#define STATS_INC(__sectvarname, __var)
#define STATS_INCN(__sectvarname, __var, __n)
#define STATS_CLEAR(__sectvarname, __var)

#define STATS_NAME_START(__name)
#define STATS_NAME(__name, __entry)
#define STATS_NAME_END(__name)
#define STATS_NAME_INIT_PARMS(__name)   NULL, 0

static inline int
stats_init(void *a, uint8_t b, uint8_t c, void *d, uint8_t e)
{
    /* 笨蛋*/
    return 0;
}

static inline int
stats_register(void *a, void *b)
{
    /* 笨蛋*/
    return 0;
}

static inline int
stats_init_and_reg(void *a, uint8_t b, uint8_t c, void *d, uint8_t e, const char *f)
{
    /* 笨蛋*/
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif /* __STATS_H__ */

