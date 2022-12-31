/*
** mruby/hash。h-哈希类
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_HASH_H
#define MRUBY_HASH_H

#include "common.h"

/**
 * 哈希类
 */
MRB_BEGIN_DECL

struct RHash {
  MRB_OBJECT_HEADER;
  struct iv_tbl *iv;
  struct htable *ht;
};

#define mrb_hash_ptr(v)    ((struct RHash*)(mrb_ptr(v)))
#define mrb_hash_value(p)  mrb_obj_value((void*)(p))

MRB_API mrb_value mrb_hash_new_capa(mrb_state*, mrb_int);
MRB_API mrb_value mrb_ensure_hash_type(mrb_state *mrb, mrb_value hash);
MRB_API mrb_value mrb_check_hash_type(mrb_state *mrb, mrb_value hash);

/*
 * 初始化新哈希。
 *
 * 相当于：
 *
 *      Hash.new（哈希新）
 *
 * @param mrb mruby状态引用。
 * @return 初始化的哈希。
 */
MRB_API mrb_value mrb_hash_new(mrb_state *mrb);

/*
 * 设置哈希的键和值。
 *
 * 相当于：
 *
 *      hash[key]=val
 *
 * @param mrb mruby状态引用。
 * @param hash 目标哈希。
 * @param key 要设置的键。
 * @param val 要设置的值。
 * @return 值。
 */
MRB_API void mrb_hash_set(mrb_state *mrb, mrb_value hash, mrb_value key, mrb_value val);

/*
 * 从键获取值。如果找不到密钥，则使用哈希的默认值。
 *
 * 相当于：
 *
 *     哈希[键]
 *
 * @param mrb mruby状态引用。
 * @param hash 目标哈希。
 * @param key 要获得的关键。
 * @return 找到的值。
 */
MRB_API mrb_value mrb_hash_get(mrb_state *mrb, mrb_value hash, mrb_value key);

/*
 * 从键获取值。如果找不到密钥，则使用默认参数。
 *
 * 相当于：
 *
 *     搞砸钥匙（键）？hash[key]：定义
 *
 * @param mrb mruby状态引用。
 * @param hash 目标哈希。
 * @param key 要获得的关键。
 * @param def 默认值。
 * @return 找到的值。
 */
MRB_API mrb_value mrb_hash_fetch(mrb_state *mrb, mrb_value hash, mrb_value key, mrb_value def);

/*
 * 删除哈希键和值对。
 *
 * 相当于：
 *
 *     hash.delete（键）
 *
 * @param mrb mruby状态引用。
 * @param hash 目标哈希。
 * @param key 要删除的密钥。
 * @return 删除的值。
 */
MRB_API mrb_value mrb_hash_delete_key(mrb_state *mrb, mrb_value hash, mrb_value key);

/*
 * 获取键的数组。
 *
 * 相当于：
 *
 *     哈希键
 *
 * @param mrb mruby状态引用。
 * @param hash 目标哈希。
 * @return 带有哈希键的数组。
 */
MRB_API mrb_value mrb_hash_keys(mrb_state *mrb, mrb_value hash);
/*
 * 检查哈希是否有密钥。
 *
 * 相当于：
 *
 *     hash.key？（键）
 *
 * @param mrb mruby状态引用。
 * @param hash 目标哈希。
 * @param key 检查是否存在的密钥。
 * @return 如果哈希具有密钥，则为True
 */
MRB_API mrb_bool mrb_hash_key_p(mrb_state *mrb, mrb_value hash, mrb_value key);

/*
 * 检查哈希值是否为空
 *
 * 相当于：
 *
 *     hash.empty？
 *
 * @param mrb mruby状态引用。
 * @param self 目标哈希。
 * @return 如果哈希为空，则为True，否则为false。
 */
MRB_API mrb_bool mrb_hash_empty_p(mrb_state *mrb, mrb_value self);

/*
 * 获取一个值数组。
 *
 * 相当于：
 *
 *     哈希值
 *
 * @param mrb mruby状态引用。
 * @param hash 目标哈希。
 * @return 具有哈希值的数组。
 */
MRB_API mrb_value mrb_hash_values(mrb_state *mrb, mrb_value hash);

/*
 * 清除哈希。
 *
 * 相当于：
 *
 *     哈希清除
 *
 * @param mrb mruby状态引用。
 * @param hash 目标哈希。
 * @return 哈希
 */
MRB_API mrb_value mrb_hash_clear(mrb_state *mrb, mrb_value hash);

/*
 * 获取哈希大小。
 *
 * 相当于：
 *
 *      哈希大小
 *
 * @param mrb mruby状态引用。
 * @param hash 目标哈希。
 * @return 哈希大小。
 */
MRB_API mrb_int mrb_hash_size(mrb_state *mrb, mrb_value hash);

/*
 * 复制哈希。
 *
 *
 * @param mrb mruby状态引用。
 * @param hash 目标哈希。
 * @return 哈希的副本
 */
MRB_API mrb_value mrb_hash_dup(mrb_state *mrb, mrb_value hash);

/*
 * 合并两个哈希。第一个哈希将被第二个哈希修改。
 *
 * @param mrb mruby状态引用。
 * @param hash1 目标哈希。
 * @param hash2 正在更新哈希
 */
MRB_API void mrb_hash_merge(mrb_state *mrb, mrb_value hash1, mrb_value hash2);

/* 结构mrb_hash_value的声明*/
/* 触摸内部时要小心*/
typedef struct {
  mrb_value v;
  mrb_int n;
} mrb_hash_value;

/* RHASH_TBL分配st_table（如果不可用）。*/
#define RHASH(obj)   ((struct RHash*)(mrb_ptr(obj)))
#define RHASH_TBL(h)          (RHASH(h)->ht)
#define RHASH_IFNONE(h)       mrb_iv_get(mrb, (h), mrb_intern_lit(mrb, "ifnone"))
#define RHASH_PROCDEFAULT(h)  RHASH_IFNONE(h)

#define MRB_HASH_DEFAULT      1
#define MRB_HASH_PROC_DEFAULT 2
#define MRB_RHASH_DEFAULT_P(h) (RHASH(h)->flags & MRB_HASH_DEFAULT)
#define MRB_RHASH_PROCDEFAULT_P(h) (RHASH(h)->flags & MRB_HASH_PROC_DEFAULT)

/* GC功能*/
void mrb_gc_mark_hash(mrb_state*, struct RHash*);
size_t mrb_gc_mark_hash_size(mrb_state*, struct RHash*);
void mrb_gc_free_hash(mrb_state*, struct RHash*);

/* 返回非零以中断循环*/
typedef int (mrb_hash_foreach_func)(mrb_state *mrb, mrb_value key, mrb_value val, void *data);
MRB_API void mrb_hash_foreach(mrb_state *mrb, struct RHash *hash, mrb_hash_foreach_func *func, void *p);

MRB_END_DECL

#endif  /* MRUBY_HASH_H */

