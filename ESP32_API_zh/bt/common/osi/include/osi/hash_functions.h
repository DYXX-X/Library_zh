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

#ifndef _HASH_FUNCTIONS_H_
#define _HASH_FUNCTIONS_H_

#include "osi/hash_map.h"

typedef unsigned char hash_key_t[4];

hash_index_t hash_function_naive(const void *key);

hash_index_t hash_function_integer(const void *key);

// 仅基于指针的地址值对指针进行哈希
hash_index_t hash_function_pointer(const void *key);

hash_index_t hash_function_string(const void *key);

void hash_function_blob(const unsigned char *s, unsigned int len, hash_key_t h);

#endif /* _HASH_FUNCTIONS_H_ */

