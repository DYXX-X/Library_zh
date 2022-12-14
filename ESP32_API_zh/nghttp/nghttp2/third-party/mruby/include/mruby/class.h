/*
** mruby/类。h-等级
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_CLASS_H
#define MRUBY_CLASS_H

#include "common.h"

/**
 * 班级类别
 */
MRB_BEGIN_DECL

struct RClass {
  MRB_OBJECT_HEADER;
  struct iv_tbl *iv;
  struct kh_mt *mt;
  struct RClass *super;
};

#define mrb_class_ptr(v)    ((struct RClass*)(mrb_ptr(v)))

static inline struct RClass*
mrb_class(mrb_state *mrb, mrb_value v)
{
  switch (mrb_type(v)) {
  case MRB_TT_FALSE:
    if (mrb_fixnum(v))
      return mrb->false_class;
    return mrb->nil_class;
  case MRB_TT_TRUE:
    return mrb->true_class;
  case MRB_TT_SYMBOL:
    return mrb->symbol_class;
  case MRB_TT_FIXNUM:
    return mrb->fixnum_class;
#ifndef MRB_WITHOUT_FLOAT
  case MRB_TT_FLOAT:
    return mrb->float_class;
#endif
  case MRB_TT_CPTR:
    return mrb->object_class;
  case MRB_TT_ENV:
    return NULL;
  default:
    return mrb_obj_ptr(v)->c;
  }
}

/* 标志：20：冻结19：is_prepeded 18：is_origin 17：is_inherited（由方法缓存使用）16：未使用0-15：实例类型
*/
#define MRB_FL_CLASS_IS_PREPENDED (1 << 19)
#define MRB_FL_CLASS_IS_ORIGIN (1 << 18)
#define MRB_CLASS_ORIGIN(c) do {\
  if ((c)->flags & MRB_FL_CLASS_IS_PREPENDED) {\
    (c) = (c)->super;\
    while (!((c)->flags & MRB_FL_CLASS_IS_ORIGIN)) {\
      (c) = (c)->super;\
    }\
  }\
} while (0)
#define MRB_FL_CLASS_IS_INHERITED (1 << 17)
#define MRB_INSTANCE_TT_MASK (0xFF)
#define MRB_SET_INSTANCE_TT(c, tt) ((c)->flags = (((c)->flags & ~MRB_INSTANCE_TT_MASK) | (char)(tt)))
#define MRB_INSTANCE_TT(c) (enum mrb_vtype)((c)->flags & MRB_INSTANCE_TT_MASK)

MRB_API struct RClass* mrb_define_class_id(mrb_state*, mrb_sym, struct RClass*);
MRB_API struct RClass* mrb_define_module_id(mrb_state*, mrb_sym);
MRB_API struct RClass *mrb_vm_define_class(mrb_state*, mrb_value, mrb_value, mrb_sym);
MRB_API struct RClass *mrb_vm_define_module(mrb_state*, mrb_value, mrb_sym);
MRB_API void mrb_define_method_raw(mrb_state*, struct RClass*, mrb_sym, mrb_method_t);
MRB_API void mrb_define_method_id(mrb_state *mrb, struct RClass *c, mrb_sym mid, mrb_func_t func, mrb_aspec aspec);
MRB_API void mrb_alias_method(mrb_state*, struct RClass *c, mrb_sym a, mrb_sym b);

MRB_API mrb_method_t mrb_method_search_vm(mrb_state*, struct RClass**, mrb_sym);
MRB_API mrb_method_t mrb_method_search(mrb_state*, struct RClass*, mrb_sym);

MRB_API struct RClass* mrb_class_real(struct RClass* cl);

void mrb_class_name_class(mrb_state*, struct RClass*, struct RClass*, mrb_sym);
mrb_value mrb_class_find_path(mrb_state*, struct RClass*);
void mrb_gc_mark_mt(mrb_state*, struct RClass*);
size_t mrb_gc_mark_mt_size(mrb_state*, struct RClass*);
void mrb_gc_free_mt(mrb_state*, struct RClass*);

MRB_END_DECL

#endif  /* MRUBY_CLASS_H */

