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

#ifndef _HASH_MAP_H_
#define _HASH_MAP_H_

#include <stdbool.h>
#include <stdint.h>

struct hash_map_t;
typedef struct hash_map_t hash_map_t;

typedef struct hash_map_entry_t {
    const void *key;
    void *data;
    const hash_map_t *hash_map;
} hash_map_entry_t;

typedef size_t hash_index_t;

// 采用键结构并返回哈希值。
typedef hash_index_t (*hash_index_fn)(const void *key);
typedef bool (*hash_map_iter_cb)(hash_map_entry_t *hash_entry, void *context);

typedef bool (*key_equality_fn)(const void *x, const void *y);

typedef void (*key_free_fn)(void *data);
typedef void (*data_free_fn)(void *data);

// 返回一个新的空hash_map。如果无法分配足够的内存，则返回NULL
// 对于hash_map结构。必须使用|hash_map_free|释放返回的hash_map。
// |num_bucket|指定映射的可散列桶数，不能
// 为零。|hash_fn|指定要使用的哈希函数，并且不能为NULL。
// 每当从中移除hash_map元素时，都会调用|key_fn|和|data_fn|
// hash_map。它们可以用于释放hash_ map元素所持有的资源，
// e、 g.内存或文件描述符|如果没有清理，key_fn|和|data_fn|可能为NULL
// 在拆除元件时必须使用|equity_fn|用于检查密钥相等性。
// 如果|equity_fn|为NULL，则使用默认指针相等。
hash_map_t *hash_map_new(
    size_t size,
    hash_index_fn hash_fn,
    key_free_fn key_fn,
    data_free_fn data_fn,
    key_equality_fn equality_fn);

// 释放hash_map。此函数接受NULL作为参数，在这种情况下
// 表现得像个傻瓜。
void hash_map_free(hash_map_t *hash_map);

// 如果hash_map为空（没有元素），则返回true，否则返回false。
// 请注意，NULL |hash_map|与空|hash_map |不同。此函数
// 不接受NULL |hash_map|。
//bool hash_map_is_empty（常量hash_map_t*hash_map）；

// 返回哈希映射中的元素数。此函数不接受
// NULL | hash_map|。
//size_t hash_map_size（常量hash_map_t*hash_map）；

// 返回哈希映射中的桶数。此函数不接受
// NULL | hash_map|。
//size_t hash_map_num_buckets（常量hash_map_t*hash_map）；

// 如果hash_map具有所呈现密钥的有效条目，则返回true。
// 此函数不接受NULL |hash_map|。
bool hash_map_has_key(const hash_map_t *hash_map, const void *key);

// 返回hash_map中由|key|索引的元素，而不删除它。|hash_map|
// 不能为NULL。如果没有按|key|索引的条目，则返回NULL。
void *hash_map_get(const hash_map_t *hash_map, const void *key);

// 将|key|索引的值|data|设置为|hash_map|。既不是|data|也不是
// |hash_map|可以为NULL。此函数不复制|data|或|key|
// 因此指针必须至少在元素从
// hash_map或hash_map被释放。如果无法设置|data|，则返回true，false
// 否则（例如内存不足）。
bool hash_map_set(hash_map_t *hash_map, const void *key, void *data);

// 从hash_map中删除按|key|索引的数据|hash_map|不能为NULL。
// 如果在|hash_map_new|中指定了|key_fn|或|data_fn|函数，则它们
// 将分别用|key|或|data|调用。此函数返回true
// 如果在hashmap中找到|key|并将其删除，则为false。
bool hash_map_erase(hash_map_t *hash_map, const void *key);

// 删除hash_map中的所有元素。调用此函数将返回hash_map
// 恢复到|hash_map_new|之后的状态|hash_map|不能为NULL。
void hash_map_clear(hash_map_t *hash_map);

// 遍历整个|hash_map|并为每个数据调用|callback |
// 元素，并传递|context|参数。如果hash_map为
// 空，则永远不会调用|回调|。变异
// 回调内的hash_map。|hash_map|或|callback |都不能为NULL。
// 如果|callback |返回false，迭代循环将立即退出。
void hash_map_foreach(hash_map_t *hash_map, hash_map_iter_cb callback, void *context);

#endif /* _HASH_MAP_H_ */

