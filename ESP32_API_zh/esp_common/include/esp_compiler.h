// 版权所有2016-2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#ifndef __ESP_COMPILER_H
#define __ESP_COMPILER_H

/*
 * 可能的和不可能的宏对：当应用程序知道决策路径的大多数出现时，放置这些宏非常有用，放置其中一个宏可以提示编译器重新排序指令，生成更优化的代码。
 */
#if (CONFIG_COMPILER_OPTIMIZATION_PERF)
#ifndef likely
#define likely(x)      __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
#define unlikely(x)    __builtin_expect(!!(x), 0)
#endif
#else
#ifndef likely
#define likely(x)      (x)
#endif
#ifndef unlikely
#define unlikely(x)    (x)
#endif
#endif

/*
 * 用于指定初始化器的实用程序宏，这些宏在C99和C++标准中的工作方式不同，主要用于聚合类型。成员分隔符逗号已经是宏的一部分，请省略后面的逗号。用法示例：struct config_t｛char pchr；char arr[SIZE]；｝配置=｛ESP_COMPILER_DESIGNED_INIT_AGGREGATE_TYPE_EMPTY（pchr）ESP_COMPIILER_DESIGNTED_INIT_AGREGATE_TTYPE_STR（arr，“值”）｝；
 */
#ifdef __cplusplus
#define ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_STR(member, value)  { .member = value },
#define ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(member) .member = { },
#else
#define ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_STR(member, value)  .member = value,
#define ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(member)
#endif

#endif

