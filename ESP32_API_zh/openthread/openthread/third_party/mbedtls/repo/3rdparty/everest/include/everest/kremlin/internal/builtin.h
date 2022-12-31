/* 版权所有（c）INRIA和Microsoft Corporation。保留所有权利。根据Apache 2.0许可证许可。*/

#ifndef __KREMLIN_BUILTIN_H
#define __KREMLIN_BUILTIN_H

/* 对于alloca，当使用KreMLin的-floca时*/
#if (defined(_WIN32) || defined(_WIN64))
#  include <malloc.h>
#endif

/* 如果某些全局变量需要在main之前初始化，则kremlin将生成并尝试链接最后一个具有此类型的函数：*/
void kremlinit_globals(void);

#endif

