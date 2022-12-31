/*
** mruby/array。h-数组类
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_ARRAY_H
#define MRUBY_ARRAY_H

#include "common.h"

/*
 * 数组类
 */
MRB_BEGIN_DECL


typedef struct mrb_shared_array {
  int refcnt;
  mrb_int len;
  mrb_value *ptr;
} mrb_shared_array;

#define MRB_ARY_EMBED_LEN_MAX ((mrb_int)(sizeof(void*)*3/sizeof(mrb_value)))
struct RArray {
  MRB_OBJECT_HEADER;
  union {
    struct {
      mrb_int len;
      union {
        mrb_int capa;
        mrb_shared_array *shared;
      } aux;
      mrb_value *ptr;
    } heap;
    mrb_value embed[MRB_ARY_EMBED_LEN_MAX];
  } as;
};

#define mrb_ary_ptr(v)    ((struct RArray*)(mrb_ptr(v)))
#define mrb_ary_value(p)  mrb_obj_value((void*)(p))
#define RARRAY(v)  ((struct RArray*)(mrb_ptr(v)))

#define MRB_ARY_EMBED_MASK  7
#define ARY_EMBED_P(a) ((a)->flags & MRB_ARY_EMBED_MASK)
#define ARY_UNSET_EMBED_FLAG(a) ((a)->flags &= ~(MRB_ARY_EMBED_MASK))
#define ARY_EMBED_LEN(a) ((mrb_int)(((a)->flags & MRB_ARY_EMBED_MASK) - 1))
#define ARY_SET_EMBED_LEN(a,len) ((a)->flags = ((a)->flags&~MRB_ARY_EMBED_MASK) | ((uint32_t)(len) + 1))
#define ARY_EMBED_PTR(a) (&((a)->as.embed[0]))

#define ARY_LEN(a) (ARY_EMBED_P(a)?ARY_EMBED_LEN(a):(a)->as.heap.len)
#define ARY_PTR(a) (ARY_EMBED_P(a)?ARY_EMBED_PTR(a):(a)->as.heap.ptr)
#define RARRAY_LEN(a) ARY_LEN(RARRAY(a))
#define RARRAY_PTR(a) ARY_PTR(RARRAY(a))
#define ARY_SET_LEN(a,n) do {\
  if (ARY_EMBED_P(a)) {\
    mrb_assert((n) <= MRB_ARY_EMBED_LEN_MAX); \
    ARY_SET_EMBED_LEN(a,n);\
  }\
  else\
    (a)->as.heap.len = (n);\
} while (0)
#define ARY_CAPA(a) (ARY_EMBED_P(a)?MRB_ARY_EMBED_LEN_MAX:(a)->as.heap.aux.capa)
#define MRB_ARY_SHARED      256
#define ARY_SHARED_P(a) ((a)->flags & MRB_ARY_SHARED)
#define ARY_SET_SHARED_FLAG(a) ((a)->flags |= MRB_ARY_SHARED)
#define ARY_UNSET_SHARED_FLAG(a) ((a)->flags &= ~MRB_ARY_SHARED)

void mrb_ary_decref(mrb_state*, mrb_shared_array*);
MRB_API void mrb_ary_modify(mrb_state*, struct RArray*);
MRB_API mrb_value mrb_ary_new_capa(mrb_state*, mrb_int);

/*
 * 初始化新数组。
 *
 * 相当于：
 *
 *      阵列.new
 *
 * @param mrb mruby状态引用。
 * @return 初始化的数组。
 */
MRB_API mrb_value mrb_ary_new(mrb_state *mrb);

/*
 * 使用初始值初始化新数组
 *
 * 相当于：
 *
 *      数组[value1，value2，…]
 *
 * @param mrb mruby状态引用。
 * @param size 值的数量。
 * @param vals 实际值。
 * @return 初始化的数组。
 */
MRB_API mrb_value mrb_ary_new_from_values(mrb_state *mrb, mrb_int size, const mrb_value *vals);

/*
 * 用两个初始值初始化新数组
 *
 * 相当于：
 *
 *      阵列[car，cdr]
 *
 * @param mrb mruby状态引用。
 * @param car 第一个值。
 * @param cdr 第二个值。
 * @return 初始化的数组。
 */
MRB_API mrb_value mrb_assoc_new(mrb_state *mrb, mrb_value car, mrb_value cdr);

/*
 * 连接两个数组。将修改目标阵列
 *
 * 相当于：ary.concat（其他）
 *
 * @param mrb mruby状态引用。
 * @param self 目标阵列。
 * @param other 将连接到自身的数组。
 */
MRB_API void mrb_ary_concat(mrb_state *mrb, mrb_value self, mrb_value other);

/*
 * 从输入创建数组。它尝试对值调用to_a。若该值并没有响应，它将创建一个仅具有该值的新数组。
 *
 * @param mrb mruby状态引用。
 * @param value 要更改为数组的值。
 * @return 值的数组表示。
 */
MRB_API mrb_value mrb_ary_splat(mrb_state *mrb, mrb_value value);

/*
 * 将值推入数组。
 *
 * 相当于：
 *
 *      ary<<值
 *
 * @param mrb mruby状态引用。
 * @param ary 将在其中推送值的数组
 * @param value 要推入数组的值
 */
MRB_API void mrb_ary_push(mrb_state *mrb, mrb_value array, mrb_value value);

/*
 * 弹出数组中的最后一个元素。
 *
 * 相当于：
 *
 *      ary.pop
 *
 * @param mrb mruby状态引用。
 * @param ary 将从中弹出值的数组。
 * @return 弹出的值。
 */
MRB_API mrb_value mrb_ary_pop(mrb_state *mrb, mrb_value ary);

/*
 * 返回对给定索引上数组元素的引用。
 *
 * 相当于：
 *
 *      辅助[n]
 *
 * @param mrb mruby状态引用。
 * @param ary 目标阵列。
 * @param n 正在引用的数组索引
 * @return 引用的值。
 */
MRB_API mrb_value mrb_ary_ref(mrb_state *mrb, mrb_value ary, mrb_int n);

/*
 * 在给定索引的数组上设置值
 *
 * 相当于：
 *
 *      ary[n]=值
 *
 * @param mrb mruby状态引用。
 * @param ary 目标阵列。
 * @param n 正在引用的数组索引。
 * @param val 正在设置的值。
 */
MRB_API void mrb_ary_set(mrb_state *mrb, mrb_value ary, mrb_int n, mrb_value val);

/*
 * 用另一个阵列替换该阵列
 *
 * 相当于：
 *
 *      ary替换（其他）
 *
 * @param mrb mruby状态引用
 * @param self 目标阵列。
 * @param other 要替换它的数组。
 */
MRB_API void mrb_ary_replace(mrb_state *mrb, mrb_value self, mrb_value other);
MRB_API mrb_value mrb_ensure_array_type(mrb_state *mrb, mrb_value self);
MRB_API mrb_value mrb_check_array_type(mrb_state *mrb, mrb_value self);

/*
 * 将元素取消移动到阵列中
 *
 * 相当于：
 *
 *     备用未装运（项）
 *
 * @param mrb mruby状态引用。
 * @param self 目标阵列。
 * @param item 要取消装运的项目。
 */
MRB_API mrb_value mrb_ary_unshift(mrb_state *mrb, mrb_value self, mrb_value item);

/*
 * 获取数组中的第n个元素
 *
 * 相当于：
 *
 *     ary[偏移量]
 *
 * @param ary 目标阵列。
 * @param offset 元素位置（从尾部开始的负计数）。
 */
MRB_API mrb_value mrb_ary_entry(mrb_value ary, mrb_int offset);

/*
 * 替换数组的子序列。
 *
 * 相当于：
 *
 *      芳基移位
 *
 * @param mrb mruby状态引用。
 * @param self 将从中移动值的数组。
 * @param head 替换子序列的开始位置。
 * @param len 替换子序列的长度。
 * @param rpl 替换元素的数组。
 * @return 接收器阵列。
 */
MRB_API mrb_value mrb_ary_splice(mrb_state *mrb, mrb_value self, mrb_int head, mrb_int len, mrb_value rpl);

/*
 * 从数组中移动第一个元素。
 *
 * 相当于：
 *
 *      芳基移位
 *
 * @param mrb mruby状态引用。
 * @param self 将从中移动值的数组。
 * @return 移位的值。
 */
MRB_API mrb_value mrb_ary_shift(mrb_state *mrb, mrb_value self);

/*
 * 从阵列中删除所有元素
 *
 * 相当于：
 *
 *      ary.清除
 *
 * @param mrb mruby状态引用。
 * @param self 目标阵列。
 * @return 自己
 */
MRB_API mrb_value mrb_ary_clear(mrb_state *mrb, mrb_value self);

/*
 * 将数组元素以字符串形式连接在一起
 *
 * 相当于：
 *
 *      ary.join（sep=“”）
 *
 * @param mrb mruby状态引用。
 * @param ary 目标阵列
 * @param sep 分隔符可以为空
 */
MRB_API mrb_value mrb_ary_join(mrb_state *mrb, mrb_value ary, mrb_value sep);

/*
 * 更新阵列的容量
 *
 * @param mrb mruby状态引用。
 * @param ary 目标阵列。
 * @param new_len 阵列的新容量
 */
MRB_API mrb_value mrb_ary_resize(mrb_state *mrb, mrb_value ary, mrb_int new_len);

MRB_END_DECL

#endif  /* MRUBY_ARRAY_H */

