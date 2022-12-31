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

#ifndef _BDADDR_H_
#define _BDADDR_H_

#include <stdbool.h>
#include <stddef.h>

#include "common/bt_defs.h"
#include "osi/hash_map.h"

// 注意：bdaddr的字符串表示应具有以下格式
// xx:xx:xx.xx:xx:xx
// 其中每个“x”是十六进制数字。此标头中提供的API将接受
// 大写和小写数字，但只能产生小写
// 数字。

// 如果|addr|是空地址（00:00:00:00:00:00），则返回true。
// |addr|不能为NULL。
bool bdaddr_is_empty(const bt_bdaddr_t *addr);

// 如果|first|和|second|引用同一地址，则返回true。也不
// 可以为NULL。
bool bdaddr_equals(const bt_bdaddr_t *first, const bt_bdaddr_t *second);

// 将|src|复制到|dest|后，返回目标bdaddr|dest|。
// |dest|和|src|不能为NULL。
bt_bdaddr_t *bdaddr_copy(bt_bdaddr_t *dest, const bt_bdaddr_t *src);

// 生成|addr|的字符串表示形式，并将其放入|string|中|尺寸|
// 指|string|的缓冲区大小，必须大于等于18。如果成功
// 函数返回|string|，否则返回NULL。既不是|addr|也不是|string|
// 可以为NULL。
const char *bdaddr_to_string(const bt_bdaddr_t *addr, char *string, size_t size);

// 如果|string|表示蓝牙地址，则返回true|字符串|不能为NULL。
bool string_is_bdaddr(const char *string);

// 将|string|转换为bt_bdaddr_t并将其放在|addr|中。如果|string|没有
// 表示蓝牙地址，|addr|未被修改，此函数返回
// 错误。否则，返回true。|string|或|addr|都不能为NULL。
bool string_to_bdaddr(const char *string, bt_bdaddr_t *addr);

// 为bdaddrs定制的哈希函数。
hash_index_t hash_function_bdaddr(const void *key);

#endif

