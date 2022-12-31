/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_OS_UTIL_
#define H_OS_UTIL_

/* 帮助将整数作为指针传递，反之亦然*/
#define POINTER_TO_UINT(p) ((unsigned int) ((uintptr_t) (p)))
#define UINT_TO_POINTER(u) ((void *) ((uintptr_t) (u)))
#define POINTER_TO_INT(p) ((int) ((intptr_t) (p)))
#define INT_TO_POINTER(u) ((void *) ((intptr_t) (u)))

/* 帮助程序检索结构中“父”对象的指针*/
#define CONTAINER_OF(ptr, type, field) \
        ((type *)(((char *)(ptr)) - offsetof(type, field)))

/* 帮助程序计算数组中的元素数*/
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) \
        (sizeof(array) / sizeof((array)[0]))
#endif
#endif

