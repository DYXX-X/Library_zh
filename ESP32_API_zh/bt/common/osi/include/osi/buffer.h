/******************************************************************************
 * 版权所有（C）2014谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct buffer_t buffer_t;

// 返回|size|字节的新缓冲区。如果缓冲区不能
// 分配|size|必须为非零。调用方必须使用
// |buffer_free|。
buffer_t *buffer_new(size_t size);

// 创建对缓冲区|buf|的新引用。引用无法区分
// 从原件：对原件的写入将反映在参考文件中
// 反之亦然。换句话说，此函数为|buf|创建别名。这个
// 调用者必须使用|buffer_free|释放返回的缓冲区。注意，释放
// 返回的缓冲区未释放|buf||buf|不能为NULL。
buffer_t *buffer_new_ref(const buffer_t *buf);

// 创建对|buf|的最后|slice_size|字节的新引用。看见
// |buffer_new_ref|获取引用的描述|slice_size|必须为
// 大于0，最多可以为|buffer_length|
// （0<slice_size<=缓冲区长度）|buf|不能为NULL。
buffer_t *buffer_new_slice(const buffer_t *buf, size_t slice_size);

// 释放缓冲区对象|buf|可以为NULL。
void buffer_free(buffer_t *buf);

// 返回指向|buf|的可写内存区域的指针。所有参考文献
// 共享重叠字节的切片也将在
// 写入返回的指针。呼叫者可以安全地向
// |buffer_length |从返回的地址开始的连续字节
// 此功能|buf|不能为NULL。
void *buffer_ptr(const buffer_t *buf);

// 返回|buf|引用的可写内存区域的长度。
// |buf|不能为NULL。
size_t buffer_length(const buffer_t *buf);

#endif /*_BUFFER_H_*/

