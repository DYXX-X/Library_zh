/*
** mruby/gc。h-mruby的垃圾收集器
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_GC_H
#define MRUBY_GC_H

#include "common.h"

/**
 * 不常见的内存管理工具。
 */
MRB_BEGIN_DECL


struct mrb_state;

#define MRB_EACH_OBJ_OK 0
#define MRB_EACH_OBJ_BREAK 1
typedef int (mrb_each_object_callback)(struct mrb_state *mrb, struct RBasic *obj, void *data);
void mrb_objspace_each_objects(struct mrb_state *mrb, mrb_each_object_callback *callback, void *data);
MRB_API void mrb_free_context(struct mrb_state *mrb, struct mrb_context *c);

#ifndef MRB_GC_ARENA_SIZE
#define MRB_GC_ARENA_SIZE 100
#endif

typedef enum {
  MRB_GC_STATE_ROOT = 0,
  MRB_GC_STATE_MARK,
  MRB_GC_STATE_SWEEP
} mrb_gc_state;

/* 在C++模式下禁用MSVC警告“C4200:使用了非标准扩展：结构/联合中的零大小数组”*/
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4200)
#endif

typedef struct mrb_heap_page {
  struct RBasic *freelist;
  struct mrb_heap_page *prev;
  struct mrb_heap_page *next;
  struct mrb_heap_page *free_next;
  struct mrb_heap_page *free_prev;
  mrb_bool old:1;
  void *objects[];
} mrb_heap_page;

#ifdef _MSC_VER
#pragma warning(pop)
#endif

typedef struct mrb_gc {
  mrb_heap_page *heaps;                /* GC堆*/
  mrb_heap_page *sweeps;
  mrb_heap_page *free_heaps;
  size_t live; /* 活动对象计数*/
#ifdef MRB_GC_FIXED_ARENA
  struct RBasic *arena[MRB_GC_ARENA_SIZE]; /* GC保护阵列*/
#else
  struct RBasic **arena;                   /* GC保护阵列*/
  int arena_capa;
#endif
  int arena_idx;

  mrb_gc_state state; /* 气相色谱状态*/
  int current_white_part; /* 通过white_part生成白色对象*/
  struct RBasic *gray_list; /* 要增量遍历的灰色对象列表*/
  struct RBasic *atomic_gray_list; /* 要自动遍历的对象列表*/
  size_t live_after_mark;
  size_t threshold;
  int interval_ratio;
  int step_ratio;
  mrb_bool iterating     :1;
  mrb_bool disabled      :1;
  mrb_bool full          :1;
  mrb_bool generational  :1;
  mrb_bool out_of_memory :1;
  size_t majorgc_old_threshold;
} mrb_gc;

MRB_API mrb_bool
mrb_object_dead_p(struct mrb_state *mrb, struct RBasic *object);

MRB_END_DECL

#endif  /* MRUBY_GC_H */

