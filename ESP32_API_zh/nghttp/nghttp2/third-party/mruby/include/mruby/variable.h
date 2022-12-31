/*
** mruby/变量。h-mruby变量
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_VARIABLE_H
#define MRUBY_VARIABLE_H

#include "common.h"

/**
 * 用于访问mruby变量的函数。
 */
MRB_BEGIN_DECL

typedef struct global_variable {
  int   counter;
  mrb_value *data;
  mrb_value (*getter)(void);
  void  (*setter)(void);
  /* 无效（*标记）（）；*/
  /* int块跟踪；*/
  /* 结构trace_var*跟踪；*/
} global_variable;

struct global_entry {
  global_variable *var;
  mrb_sym id;
};

mrb_value mrb_vm_special_get(mrb_state*, mrb_sym);
void mrb_vm_special_set(mrb_state*, mrb_sym, mrb_value);
mrb_value mrb_vm_cv_get(mrb_state*, mrb_sym);
void mrb_vm_cv_set(mrb_state*, mrb_sym, mrb_value);
mrb_value mrb_vm_const_get(mrb_state*, mrb_sym);
void mrb_vm_const_set(mrb_state*, mrb_sym, mrb_value);
MRB_API mrb_value mrb_const_get(mrb_state*, mrb_value, mrb_sym);
MRB_API void mrb_const_set(mrb_state*, mrb_value, mrb_sym, mrb_value);
MRB_API mrb_bool mrb_const_defined(mrb_state*, mrb_value, mrb_sym);
MRB_API void mrb_const_remove(mrb_state*, mrb_value, mrb_sym);

MRB_API mrb_bool mrb_iv_name_sym_p(mrb_state *mrb, mrb_sym sym);
MRB_API void mrb_iv_name_sym_check(mrb_state *mrb, mrb_sym sym);
MRB_API mrb_value mrb_obj_iv_get(mrb_state *mrb, struct RObject *obj, mrb_sym sym);
MRB_API void mrb_obj_iv_set(mrb_state *mrb, struct RObject *obj, mrb_sym sym, mrb_value v);
MRB_API mrb_bool mrb_obj_iv_defined(mrb_state *mrb, struct RObject *obj, mrb_sym sym);
MRB_API mrb_value mrb_iv_get(mrb_state *mrb, mrb_value obj, mrb_sym sym);
MRB_API void mrb_iv_set(mrb_state *mrb, mrb_value obj, mrb_sym sym, mrb_value v);
MRB_API mrb_bool mrb_iv_defined(mrb_state*, mrb_value, mrb_sym);
MRB_API mrb_value mrb_iv_remove(mrb_state *mrb, mrb_value obj, mrb_sym sym);
MRB_API void mrb_iv_copy(mrb_state *mrb, mrb_value dst, mrb_value src);
MRB_API mrb_bool mrb_const_defined_at(mrb_state *mrb, mrb_value mod, mrb_sym id);

/**
 * 获取全局变量。如果变量不存在，将返回nil
 *
 * 例子：
 *
 *     !!!ruby#ruby风格var=$value
 *
 *     !!!c//c样式mrb_sym sym=mrb_intern_list（mrb，“$value”）；mrb_value var=mrb_gv_get（mrb，sym）；
 *
 * @param mrb mruby状态引用
 * @param sym 全局变量的名称
 * @return 该全局变量的值。可能为零
 */
MRB_API mrb_value mrb_gv_get(mrb_state *mrb, mrb_sym sym);

/**
 * 设置全局变量
 *
 * 例子：
 *
 *     !!!ruby#ruby style$value=“foo”
 *
 *     !!!c//c样式mrb_sym sym=mrb_intern_list（mrb，“$value”）；mrb_gv_set（mrb，sym，mrb_str_new_lit（“foo”））；
 *
 * @param mrb mruby状态引用
 * @param sym 全局变量的名称
 * @param val 全局变量的值
 */
MRB_API void mrb_gv_set(mrb_state *mrb, mrb_sym sym, mrb_value val);

/**
 * 删除全局变量。
 *
 * 例子：
 *
 *     !!!ruby#ruby style$value=nil
 *
 *     !!!c//c样式mrb_sym sym=mrb_intern_list（mrb，“$value”）；mrb_gv_remove（mrb，sym）；
 *
 * @param mrb mruby状态引用
 * @param sym 全局变量的名称
 * @param val 全局变量的值
 */
MRB_API void mrb_gv_remove(mrb_state *mrb, mrb_sym sym);

MRB_API mrb_value mrb_cv_get(mrb_state *mrb, mrb_value mod, mrb_sym sym);
MRB_API void mrb_mod_cv_set(mrb_state *mrb, struct RClass * c, mrb_sym sym, mrb_value v);
MRB_API void mrb_cv_set(mrb_state *mrb, mrb_value mod, mrb_sym sym, mrb_value v);
MRB_API mrb_bool mrb_cv_defined(mrb_state *mrb, mrb_value mod, mrb_sym sym);
mrb_value mrb_obj_iv_inspect(mrb_state*, struct RObject*);
mrb_value mrb_mod_constants(mrb_state *mrb, mrb_value mod);
mrb_value mrb_f_global_variables(mrb_state *mrb, mrb_value self);
mrb_value mrb_obj_instance_variables(mrb_state*, mrb_value);
mrb_value mrb_mod_class_variables(mrb_state*, mrb_value);
mrb_value mrb_mod_cv_get(mrb_state *mrb, struct RClass * c, mrb_sym sym);
mrb_bool mrb_mod_cv_defined(mrb_state *mrb, struct RClass * c, mrb_sym sym);
mrb_bool mrb_ident_p(const char *s, mrb_int len);

/* GC功能*/
void mrb_gc_mark_gv(mrb_state*);
void mrb_gc_free_gv(mrb_state*);
void mrb_gc_mark_iv(mrb_state*, struct RObject*);
size_t mrb_gc_mark_iv_size(mrb_state*, struct RObject*);
void mrb_gc_free_iv(mrb_state*, struct RObject*);

/* 返回非零以中断循环*/
typedef int (mrb_iv_foreach_func)(mrb_state*,mrb_sym,mrb_value,void*);
MRB_API void mrb_iv_foreach(mrb_state *mrb, mrb_value obj, mrb_iv_foreach_func *func, void *p);

MRB_END_DECL

#endif  /* MRUBY_VARIABLE_H */

