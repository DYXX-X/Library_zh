/*
 * SPDX文件版权文本：2010-2017 Wind River Systems，Inc。
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _BLE_MESH_COMPILER_H_
#define _BLE_MESH_COMPILER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define ___in_section(a, b, c)

#define __in_section(a, b, c) ___in_section(a, b, c)

#define __in_section_unique(seg) ___in_section(seg, __FILE__, __COUNTER__)

#ifndef __packed
#define __packed        __attribute__((__packed__))
#endif

#ifndef __aligned
#define __aligned(x)    __attribute__((__aligned__(x)))
#endif

#ifndef __used
#define __used          __attribute__((__used__))
#endif

#ifndef ARG_UNUSED
#define ARG_UNUSED(x)   (void)(x)
#endif

#ifndef popcount
#define popcount(x)     __builtin_popcount(x)
#endif

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE inline __attribute__((always_inline))
#endif


/*
 * 这意味着与__in_section（）和类似的方法一起使用，其中分散的结构实例由链接器连接在一起，并在运行时由代码遍历，就像这样的结构的连续数组一样。
 *
 * 汇编器和链接器可以在默认情况下插入对齐填充，当将不同的节段聚集在一起时，对齐填充的大小大于这些结构的自然对齐，从而扰乱阵列行走。为了防止这种情况，我们需要提供一个明确的对齐方式，不依赖于默认值，这可能只是运气使然。
 *
 * 链接器脚本中的对齐语句是不够的，因为当在同一文件中的节之间切换时，即使汇编器最终将多个这样的节合并为一个节，汇编器也可能会自行向每个节添加填充。
 */
#ifndef Z_DECL_ALIGN
#define Z_DECL_ALIGN(type) __aligned(__alignof(type)) type
#endif

/*
 * 组合__in_section（）和Z_DECL_ALIGN（）的便利助手。节名是以下划线开头的结构类型。子部分是“静态”的，子部分是变量名。
 */
#ifndef Z_STRUCT_SECTION_ITERABLE
#define Z_STRUCT_SECTION_ITERABLE(struct_type, name) \
        Z_DECL_ALIGN(struct struct_type) name
#endif

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_COMPILER_H_ */

