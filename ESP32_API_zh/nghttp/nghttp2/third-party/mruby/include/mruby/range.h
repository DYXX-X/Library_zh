/*
** mruby/范围。h-量程等级
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_RANGE_H
#define MRUBY_RANGE_H

#include "common.h"

/**
 * 范围类别
 */
MRB_BEGIN_DECL

#if defined(MRB_NAN_BOXING) || defined(MRB_WORD_BOXING)
# define MRB_RANGE_EMBED
#endif

#ifdef MRB_RANGE_EMBED
struct RRange {
  MRB_OBJECT_HEADER;
  mrb_value beg;
  mrb_value end;
  mrb_bool excl;
};
# define mrb_gc_free_range(mrb, p) ((void)0)
# define RANGE_BEG(p) ((p)->beg)
# define RANGE_END(p) ((p)->end)
#else
typedef struct mrb_range_edges {
  mrb_value beg;
  mrb_value end;
} mrb_range_edges;
struct RRange {
  MRB_OBJECT_HEADER;
  mrb_range_edges *edges;
  mrb_bool excl;
};
# define mrb_gc_free_range(mrb, p) mrb_free(mrb, (p)->edges)
# define RANGE_BEG(p) ((p)->edges->beg)
# define RANGE_END(p) ((p)->edges->end)
#endif

#define mrb_range_beg(mrb, r) RANGE_BEG(mrb_range_ptr(mrb, r))
#define mrb_range_end(mrb, r) RANGE_END(mrb_range_ptr(mrb, r))
#define mrb_range_excl_p(mrb, r) RANGE_EXCL(mrb_range_ptr(mrb, r))
#define mrb_range_raw_ptr(r) ((struct RRange*)mrb_ptr(r))
#define mrb_range_value(p) mrb_obj_value((void*)(p))
#define RANGE_EXCL(p) ((p)->excl)

MRB_API struct RRange* mrb_range_ptr(mrb_state *mrb, mrb_value range);

/*
 * 初始化范围。
 *
 * 如果第三个参数为FALSE，则包含范围中的最后一个值。如果第三个参数为TRUE，则排除范围内的最后一个值。
 *
 * @param start 开始值。
 * @param end 结束值。
 * @param exclude 表示包含或排除最后一个值。
 */
MRB_API mrb_value mrb_range_new(mrb_state *mrb, mrb_value start, mrb_value end, mrb_bool exclude);

MRB_API mrb_int mrb_range_beg_len(mrb_state *mrb, mrb_value range, mrb_int *begp, mrb_int *lenp, mrb_int len, mrb_bool trunc);
mrb_value mrb_get_values_at(mrb_state *mrb, mrb_value obj, mrb_int olen, mrb_int argc, const mrb_value *argv, mrb_value (*func)(mrb_state*, mrb_value, mrb_int));
void mrb_gc_mark_range(mrb_state *mrb, struct RRange *r);

MRB_END_DECL

#endif  /* MRUBY_RANGE_H */

