/*
** 经理/经理。h-内联结构
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_ISTRUCT_H
#define MRUBY_ISTRUCT_H

#include "common.h"
#include <string.h>

/**
 * 适合RVALUE的内联结构
 *
 * 它们不能有终结器，也不能有实例变量。
 */
MRB_BEGIN_DECL

#define ISTRUCT_DATA_SIZE (sizeof(void*) * 3)

struct RIstruct {
  MRB_OBJECT_HEADER;
  char inline_data[ISTRUCT_DATA_SIZE];
};

#define RISTRUCT(obj)         ((struct RIstruct*)(mrb_ptr(obj)))
#define ISTRUCT_PTR(obj)      (RISTRUCT(obj)->inline_data)

MRB_INLINE mrb_int mrb_istruct_size()
{
  return ISTRUCT_DATA_SIZE;
}

MRB_INLINE void* mrb_istruct_ptr(mrb_value object)
{
  return ISTRUCT_PTR(object);
}

MRB_INLINE void mrb_istruct_copy(mrb_value dest, mrb_value src)
{
  memcpy(ISTRUCT_PTR(dest), ISTRUCT_PTR(src), ISTRUCT_DATA_SIZE);
}

MRB_END_DECL

#endif /* MRUBY_ISTRUCT_H */

