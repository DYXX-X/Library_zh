/*
** mruby/debug。h-mruby调试信息
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_DEBUG_H
#define MRUBY_DEBUG_H

#include "common.h"

/**
 * MRuby调试。
 */
MRB_BEGIN_DECL

typedef enum mrb_debug_line_type {
  mrb_debug_line_ary = 0,
  mrb_debug_line_flat_map = 1
} mrb_debug_line_type;

typedef struct mrb_irep_debug_info_line {
  uint32_t start_pos;
  uint16_t line;
} mrb_irep_debug_info_line;

typedef struct mrb_irep_debug_info_file {
  uint32_t start_pos;
  mrb_sym filename_sym;
  uint32_t line_entry_count;
  mrb_debug_line_type line_type;
  union {
    void *ptr;
    mrb_irep_debug_info_line *flat_map;
    uint16_t *ary;
  } lines;
} mrb_irep_debug_info_file;

typedef struct mrb_irep_debug_info {
  uint32_t pc_count;
  uint16_t flen;
  mrb_irep_debug_info_file **files;
} mrb_irep_debug_info;

/*
 * 从irep的调试信息和程序计数器获取行
 * @return 如果找不到，则返回NULL
 */
MRB_API const char *mrb_debug_get_filename(mrb_state *mrb, mrb_irep *irep, ptrdiff_t pc);

/*
 * 从irep的调试信息和程序计数器获取行
 * @return 如果未找到，则返回-1
 */
MRB_API int32_t mrb_debug_get_line(mrb_state *mrb, mrb_irep *irep, ptrdiff_t pc);

MRB_API mrb_irep_debug_info *mrb_debug_info_alloc(mrb_state *mrb, mrb_irep *irep);
MRB_API mrb_irep_debug_info_file *mrb_debug_info_append_file(
    mrb_state *mrb, mrb_irep_debug_info *info,
    const char *filename, uint16_t *lines,
    uint32_t start_pos, uint32_t end_pos);
MRB_API void mrb_debug_info_free(mrb_state *mrb, mrb_irep_debug_info *d);

MRB_END_DECL

#endif /* MRUBY_DEBUG_H */

