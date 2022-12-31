// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef __CONFIG_H__
#define __CONFIG_H__

// 此模块实现配置解析器。客户端可以查询
// 通过此处提供的界面，配置文件的内容。
// 当前实现是只读的；突变只保留在
// 记忆力此解析器支持INI文件格式。

// 实施说明：
// -假设不在节内的键/值对位于
//   |CONFIG_DEFAULT_SECTION|部分。
// -具有相同名称的多个节将被合并，就像它们位于
//   单个部分。
// -没有键/值对的空部分将被视为
//   不存在。换句话说，|config_has_section |将返回false
//   空部分。
// -节中的重复键将覆盖以前的值。
// -所有字符串都区分大小写。

#include <stdbool.h>

// 如果未在中定义键/值对，则使用的默认节名称
// 一节。
#define CONFIG_DEFAULT_SECTION "Global"

typedef struct config_t config_t;
typedef struct config_section_node_t config_section_node_t;

// 创建一个没有条目（即没有文件支持）的新配置对象。
// 此函数在出现错误时返回配置对象或NULL。客户必须致电
// |config_free |在不再需要时返回句柄。
config_t *config_new_empty(void);

// 加载指定的文件并向配置文件返回句柄。如果有
// 加载文件或分配内存时出现问题，此函数返回
// 无效的。当返回的句柄为否时，客户端必须对其调用|config_free |
// 需要更长的时间|filename|不能为NULL，并且必须指向可读的
// 文件系统上的文件。
config_t *config_new(const char *filename);

// 释放与配置文件关联的资源。不得进一步操作
// 在调用此函数后对|config|对象执行|配置|
// 可以为NULL。
void config_free(config_t *config);

// 如果配置文件包含名为|section|的节，则返回true。如果
// 该节中没有键/值对，此函数将返回false。
// |config|和|section|不能为NULL。
bool config_has_section(const config_t *config, const char *section);

// 如果配置文件在|section|下有一个名为|key|的键，则返回true。
// 否则返回false|config|、|section|和|key|不能为NULL。
bool config_has_key(const config_t *config, const char *section, const char *key);

// 如果配置文件具有名为|key|的键和key_value，则返回true。
// 否则返回false|config|、|key|和|key_value|不能为NULL。
bool config_has_key_in_section(config_t *config, const char *key, char *key_value);

// 返回|节|中给定|键|的整数值。If |部分|
// 或|key|不存在，或该值不能完全转换为整数，
// 此函数返回|def_value||config|、|section|和|key|不能
// 为空。
int config_get_int(const config_t *config, const char *section, const char *key, int def_value);

// 返回|节|中给定|键|的布尔值。If |部分|
// 或|key|不存在，或值无法转换为布尔值，此
// 函数返回|def_value||config|、|section|和|key|不能为NULL。
bool config_get_bool(const config_t *config, const char *section, const char *key, bool def_value);

// 返回|节|中给定|键|的字符串值。如果|节|或
// |键|不存在，此函数返回|def_value|。返回的字符串
// 属于配置模块，不得释放|config|，|节|，
// 并且|key|不能为NULL|def_value|可以为NULL。
const char *config_get_string(const config_t *config, const char *section, const char *key, const char *def_value);

// 为|节|中的|键|设置一个整数值。如果|key|或|section| do
// 不存在，此函数将创建它们|config|、|section|和|key|
// 不能为NULL。
void config_set_int(config_t *config, const char *section, const char *key, int value);

// 为|节|中的|键|设置布尔值。如果|key|或|section| do
// 不存在，此函数将创建它们|config|、|section|和|key|
// 不能为NULL。
void config_set_bool(config_t *config, const char *section, const char *key, bool value);

// 为|节|中的|键|设置字符串值。如果|key|或|section| do
// 不存在，此函数将创建它们|config|，|section|，|key|，和
// |值|不能为NULL。
void config_set_string(config_t *config, const char *section, const char *key, const char *value, bool insert_back);

// 从|config|中删除|section|（并因此删除该节中的所有键）。
// 如果找到|section|并从|config|中删除，则返回true，否则返回false。
// |config|或|section|都不能为NULL。
bool config_remove_section(config_t *config, const char *section);

// 删除|config|的|部分|中的一个特定|键|。返回true
// 如果找到了节和键并且键被移除，则为false。
// |config|、|section|或|key|都不能为NULL。
bool config_remove_key(config_t *config, const char *section, const char *key);

// 返回配置文件中第一节的迭代器。如果没有
// 节，迭代器将等于|config_section_end|的返回值。
// 返回的指针必须被视为不透明句柄，不能被释放。
// 迭代器在任何配置变异操作中都无效|config|不能
// 为空。
const config_section_node_t *config_section_begin(const config_t *config);

// 将迭代器返回到配置文件中最后一节之后的迭代器。它没有
// 表示有效节，但可用于确定是否所有节都已
// 重复。返回的指针必须被视为不透明句柄，并且必须
// 不能被释放并且不能在上迭代（不能在上调用|config_section_next
// 它）|config|不能为NULL。
const config_section_node_t *config_section_end(const config_t *config);

// 将|iter|移到下一节。如果没有更多节，|iter|将
// 等于|config_section_end|的值|iter|不能为NULL，必须为
// 由|config_section_begin|或|config_section _next |返回的指针。
const config_section_node_t *config_section_next(const config_section_node_t *iter);

// 返回|iter|引用的节的名称。返回的指针为
// 由配置模块拥有，并且不能由调用方释放。指针将
// 在调用|config_free |之前保持有效|iter|不能为NULL，也不能为
// 等于|config_section_end|返回的值。
const char *config_section_name(const config_section_node_t *iter);

// 将|config|保存到|filename|指定的文件中。注意，这可能是一个破坏性的
// 操作：如果|filename|已经存在，它将被覆盖。配置
// 模块不保留注释或格式，因此如果打开了配置文件
// 使用|config_new|，然后使用|config_save|覆盖所有注释
// 并且原始文件中的特殊格式将丢失。既不|config|也不
// |filename|可能为NULL。
bool config_save(const config_t *config, const char *filename);

#endif /* #如果名称__CONFIG_H__*/

