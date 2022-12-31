/*
** mruby-一个可嵌入的Ruby实现
**
** 版权所有（c）mruby开发者2010-2019
**
** 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
**
** 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
** [MIT许可证：http://www.opensource.org/licenses/mit-license.php ]
*/

#ifndef MRUBY_H
#define MRUBY_H

#ifdef __cplusplus
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>

#ifdef __cplusplus
#ifndef SIZE_MAX
#ifdef __SIZE_MAX__
#define SIZE_MAX __SIZE_MAX__
#else
#define SIZE_MAX std::numeric_limits<size_t>::max()
#endif
#endif
#endif

#ifdef MRB_DEBUG
#include <assert.h>
#define mrb_assert(p) assert(p)
#define mrb_assert_int_fit(t1,n,t2,max) assert((n)>=0 && ((sizeof(n)<=sizeof(t2))||(n<=(t1)(max))))
#else
#define mrb_assert(p) ((void)0)
#define mrb_assert_int_fit(t1,n,t2,max) ((void)0)
#endif

#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 201112L
#define mrb_static_assert(exp, str) _Static_assert(exp, str)
#else
#define mrb_static_assert(exp, str) mrb_assert(exp)
#endif

#include "mrbconf.h"

#ifndef MRB_WITHOUT_FLOAT
#ifndef FLT_EPSILON
#define FLT_EPSILON (1.19209290e-07f)
#endif
#ifndef DBL_EPSILON
#define DBL_EPSILON ((double)2.22044604925031308085e-16L)
#endif
#ifndef LDBL_EPSILON
#define LDBL_EPSILON (1.08420217248550443401e-19L)
#endif

#ifdef MRB_USE_FLOAT
#define MRB_FLOAT_EPSILON FLT_EPSILON
#else
#define MRB_FLOAT_EPSILON DBL_EPSILON
#endif
#endif

#include "mruby/common.h"
#include <mruby/value.h>
#include <mruby/gc.h>
#include <mruby/version.h>

/**
 * MRuby C API入口点
 */
MRB_BEGIN_DECL

typedef uint8_t mrb_code;

/**
 * 必需的参数签名类型。
 */
typedef uint32_t mrb_aspec;


struct mrb_irep;
struct mrb_state;

/**
 * @see mrb_open_allocf中使用的自定义分配器的函数指针类型。
 *
 * 指向它的函数的行为必须与realloc类似，除了：
 * -如果ptr为空，则必须分配新空间。
 * -如果s为NULL，则必须释放ptr。
 *
 * See @see 默认实现的mrb_default_allocf。
 */
typedef void* (*mrb_allocf) (struct mrb_state *mrb, void*, size_t, void *ud);

#ifndef MRB_FIXED_STATE_ATEXIT_STACK_SIZE
#define MRB_FIXED_STATE_ATEXIT_STACK_SIZE 5
#endif

typedef struct {
  mrb_sym mid;
  struct RProc *proc;
  mrb_value *stackent;
  uint16_t ridx;
  uint16_t epos;
  struct REnv *env;
  mrb_code *pc;                 /* 返回地址*/
  mrb_code *err;                /* 错误位置*/
  int argc;
  int acc;
  struct RClass *target_class;
} mrb_callinfo;

enum mrb_fiber_state {
  MRB_FIBER_CREATED = 0,
  MRB_FIBER_RUNNING,
  MRB_FIBER_RESUMED,
  MRB_FIBER_SUSPENDED,
  MRB_FIBER_TRANSFERRED,
  MRB_FIBER_TERMINATED,
};

struct mrb_context {
  struct mrb_context *prev;

  mrb_value *stack;                       /* 虚拟机堆栈*/
  mrb_value *stbase, *stend;

  mrb_callinfo *ci;
  mrb_callinfo *cibase, *ciend;

  uint16_t *rescue;                       /* 异常处理程序堆栈*/
  uint16_t rsize;
  struct RProc **ensure;                  /* 确保处理程序堆栈*/
  uint16_t esize, eidx;

  enum mrb_fiber_state status;
  mrb_bool vmexec;
  struct RFiber *fib;
};

#ifdef MRB_METHOD_CACHE_SIZE
# define MRB_METHOD_CACHE
#else
/* 默认方法缓存大小：128*/
/* 缓存大小需要是2的幂*/
# define MRB_METHOD_CACHE_SIZE (1<<7)
#endif

typedef mrb_value (*mrb_func_t)(struct mrb_state *mrb, mrb_value);

#ifdef MRB_METHOD_TABLE_INLINE
typedef uintptr_t mrb_method_t;
#else
typedef struct {
  mrb_bool func_p;
  union {
    struct RProc *proc;
    mrb_func_t func;
  };
} mrb_method_t;
#endif

#ifdef MRB_METHOD_CACHE
struct mrb_cache_entry {
  struct RClass *c, *c0;
  mrb_sym mid;
  mrb_method_t m;
};
#endif

struct mrb_jmpbuf;

typedef void (*mrb_atexit_func)(struct mrb_state*);

#define MRB_STATE_NO_REGEXP 1
#define MRB_STATE_REGEXP    2

typedef struct mrb_state {
  struct mrb_jmpbuf *jmp;

  uint32_t flags;
  mrb_allocf allocf;                      /* 存储器分配函数*/
  void *allocf_ud;                        /* 分配的辅助数据*/

  struct mrb_context *c;
  struct mrb_context *root_c;
  struct iv_tbl *globals;                 /* 全局变量表*/

  struct RObject *exc;                    /* 例外*/

  struct RObject *top_self;
  struct RClass *object_class;            /* 对象类*/
  struct RClass *class_class;
  struct RClass *module_class;
  struct RClass *proc_class;
  struct RClass *string_class;
  struct RClass *array_class;
  struct RClass *hash_class;
  struct RClass *range_class;

#ifndef MRB_WITHOUT_FLOAT
  struct RClass *float_class;
#endif
  struct RClass *fixnum_class;
  struct RClass *true_class;
  struct RClass *false_class;
  struct RClass *nil_class;
  struct RClass *symbol_class;
  struct RClass *kernel_module;

  struct alloca_header *mems;
  mrb_gc gc;

#ifdef MRB_METHOD_CACHE
  struct mrb_cache_entry cache[MRB_METHOD_CACHE_SIZE];
#endif

  mrb_sym symidx;
  struct symbol_name *symtbl;   /* 符号表*/
  mrb_sym symhash[256];
  size_t symcapa;
#ifndef MRB_ENABLE_SYMBOLL_ALL
  char symbuf[8];               /* 小符号名称缓冲区*/
#endif

#ifdef MRB_ENABLE_DEBUG_HOOK
  void (*code_fetch_hook)(struct mrb_state* mrb, struct mrb_irep *irep, mrb_code *pc, mrb_value *regs);
  void (*debug_op_hook)(struct mrb_state* mrb, struct mrb_irep *irep, mrb_code *pc, mrb_value *regs);
#endif

#ifdef MRB_BYTECODE_DECODE_OPTION
  mrb_code (*bytecode_decoder)(struct mrb_state* mrb, mrb_code code);
#endif

  struct RClass *eException_class;
  struct RClass *eStandardError_class;
  struct RObject *nomem_err;              /* 预分配NoMemoryError*/
  struct RObject *stack_err;              /* 预分配SysStackError*/
#ifdef MRB_GC_FIXED_ARENA
  struct RObject *arena_err;              /* 预先分配的竞技场溢出错误*/
#endif

  void *ud; /* 辅助数据*/

#ifdef MRB_FIXED_STATE_ATEXIT_STACK
  mrb_atexit_func atexit_stack[MRB_FIXED_STATE_ATEXIT_STACK_SIZE];
#else
  mrb_atexit_func *atexit_stack;
#endif
  uint16_t atexit_stack_len;
  uint16_t ecall_nest;                    /* 防止无限递归ecall（）*/
} mrb_state;

/**
 * 定义新类。
 *
 * 如果你正在创建一个宝石，它可能看起来像这样：
 *
 *      !!!c void mrb_example_gem_init（mrb_state mrb）{struct RClass example_class；example_class=mrb_define_class（mrb，“example_class”，mrb->object_class）；}
 *
 *      void mrb_example_gem_final（mrb_state*mrb）{//free（TheAnimals）；}
 *
 * @param [mrb_state *]mrb当前mruby状态。
 * @param [const char*]name定义的类的名称。
 * @param [struct RClass*]super新的类父级。
 * @return [struct RClass*]对新定义的类的引用。
 * @see mrb_define_class_under
 */
MRB_API struct RClass *mrb_define_class(mrb_state *mrb, const char *name, struct RClass *super);

/**
 * 定义新模块。
 *
 * @param [mrb_state *]mrb_state*当前mruby状态。
 * @param [const char*]char*模块的名称。
 * @return [struct RClass*]对新定义的模块的引用。
 */
MRB_API struct RClass *mrb_define_module(mrb_state *, const char*);
MRB_API mrb_value mrb_singleton_class(mrb_state*, mrb_value);

/**
 * 在其他类或模块中包含模块。相当于：
 *
 *   模块B包括A端
 * @param [mrb_state *]mrb_state*当前mruby状态。
 * @param [struct RClass*]RClass*对模块或类的引用。
 * @param [struct RClass*]RClass*对要包含的模块的引用。
 */
MRB_API void mrb_include_module(mrb_state*, struct RClass*, struct RClass*);

/**
 * 在另一个类或模块中的模块前面加上前缀。
 *
 * 相当于：模块B前端A端
 * @param [mrb_state *]mrb_state*当前mruby状态。
 * @param [struct RClass*]RClass*对模块或类的引用。
 * @param [struct RClass*]RClass*对要预处理的模块的引用。
 */
MRB_API void mrb_prepend_module(mrb_state*, struct RClass*, struct RClass*);

/**
 * 在ruby中定义全局函数。
 *
 * 如果你正在创建一个宝石，它可能看起来像这样
 *
 * 例子：
 *
 *     !!!c mrb_value example_method（mrb_state mrb，mrb_value self）｛put（“正在执行示例命令！”）；返回自身；}
 *
 *     void mrb_example_gem_init（mrb_state*mrb）{mrb_define_method（mrb，mrb->kernel_module，“example_method”，example_methods，mrb_ARGS_NONE（））；}
 *
 * @param [mrb_state *]mrb MRuby状态引用。
 * @param [struct RClass*]cla将在其中定义方法的类指针。
 * @param [const char*]name正在定义的方法的名称。
 * @param [mrb_func_t] func指向方法定义的函数指针。
 * @param [mrb_aspec] aspec方法参数声明。
 */
MRB_API void mrb_define_method(mrb_state *mrb, struct RClass *cla, const char *name, mrb_func_t func, mrb_aspec aspec);

/**
 * 定义类方法。
 *
 * 例子：
 *
 *     #Ruby风格的类Foo-defFoo。bar end end//C style mrb_value bar_method（mrb_state mrb，mrb_value self）｛return mrb_nil_value（）；｝void mrb_example_gem_init（mrb_state mrb）{struct RClass foo；foo=mrb_define_class（mrb，“foo”，mrb->object_class）；mrb_define_class_method（mrb、foo，“bar”，bar_method，mrb_ARGS_NONE（））；}
 * @param [mrb_state *]mrb_state*MRuby状态引用。
 * @param [struct RClass*]RClass*将在其中定义类方法的类。
 * @param [const char*]char*正在定义的类方法的名称。
 * @param [mrb_func_t] mrb_func_t指向类方法定义的函数指针。
 * @param [mrb_aspec] mrb_aspec方法参数声明。
 */
MRB_API void mrb_define_class_method(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
MRB_API void mrb_define_singleton_method(mrb_state*, struct RObject*, const char*, mrb_func_t, mrb_aspec);

/**
 *  定义模块函数。
 *
 * 例子：
 *
 *        #Ruby风格模块Foo-defFoo。bar end end//C style mrb_value bar_method（mrb_state mrb，mrb_value self）｛return mrb_nil_value（）；｝void mrb_example_gem_init（mrb_state mrb）{struct RClass foo；foo=mrb_define_module（mrb，“foo”）；mrb_define_module _function（mrb、foo，“bar”，bar_method，mrb_ARGS_NONE（））；}
 *  @param [mrb_state *]mrb_state*MRuby状态引用。
 *  @param [struct RClass*]RClass*将定义模块函数的模块。
 *  @param [const char*]char*正在定义的模块函数的名称。
 *  @param [mrb_func_t] mrb_func_t指向模块函数定义的函数指针。
 *  @param [mrb_aspec] mrb_aspec方法参数声明。
 */
MRB_API void mrb_define_module_function(mrb_state*, struct RClass*, const char*, mrb_func_t, mrb_aspec);

/**
 *  定义常量。
 *
 * 例子：
 *
 *          #Ruby风格类ExampleClass AGE=22 end//C style#include<stdio。h> #包含<mruby.h>
 *
 *          无效mrb_example_gem_init（mrb_state mrb）{mrb_define_cast（mrb，mrb->kernel_module，“AGE”，mrb_fixnum_value（22））；}
 *
 *          mrb_value mrb_example_gem_final（mrb_state mrb）｛｝
 *  @param [mrb_state *]mrb_state*MRuby状态引用。
 *  @param [struct RClass*]RClass*定义常量的类或模块。
 *  @param [const char*]name定义的常量的名称。
 *  @param [mrb_value] mrb_value常量的值。
 */
MRB_API void mrb_define_const(mrb_state*, struct RClass*, const char *name, mrb_value);

/**
 * 取消定义方法。
 *
 * 例子：
 *
 *     #红宝石风格
 *
 *     class ExampleClassA def example_method“example”end end ExampleClassA.new。example_method#=>示例
 *
 *     类ExampleClassB＜ExampleClassA undefit_method:example_method end
 *
 *     示例ClassB.new。example_method#=>ExampleClassB的未定义方法“example_method”（NoMethodError）
 *
 *     //C style#include<stdio。h> #包含<mruby.h>
 *
 *     mrb_value mrb_example_method（mrb_state mrb）{return mrb_str_new_lit（mrb，“示例”）；}
 *
 *     void mrb_example_gem_init（mrb_state mrb）{struct RClass example_class_a；struct RCclass example_class_b；structRClass示例_class_c；
 *
 *       example_class_a=mrb_define_class（mrb，“ExampleClassA”，mrb->object_class）；mrb_define_method（mrb，example_class_a，“example_method”，mrb_example_methods，mrb_ARGS_NONE（））；example_class_b=mrb_define_class（mrb，“ExampleClassB”，example_class_a）；example_class_c=mrb_define_class（mrb，“ExampleClassC”，example_class_b）；mrb_undefit_method（mrb，example_class_c，“example_method”）；}
 *
 *     mrb_example_gem_final（mrb_state*mrb）｛｝
 * @param [mrb_state*] mrb_state*mruby状态引用。
 * @param [struct RClass*]RClass*将从中定义方法的类。
 * @param [const char*]constchar*要定义的方法的名称。
 */
MRB_API void mrb_undef_method(mrb_state*, struct RClass*, const char*);
MRB_API void mrb_undef_method_id(mrb_state*, struct RClass*, mrb_sym);

/**
 * 取消定义类方法。例子：
 *
 *      #Ruby风格的类ExampleClass def self。example_method“example”结束
 *
 *     示例类.example_method
 *
 *     //C style#include<stdio。h> #包含<mruby.h>
 *
 *     mrb_value mrb_example_method（mrb_state mrb）{return mrb_str_new_lit（mrb，“示例”）；}
 *
 *     void mrb_example_gem_init（mrb_state mrb）{struct RClass example_class；example_class=mrb_define_class（mrb，“ExampleClass”，mrb->object_class）；mrb_define_class_method（mrb、example_class，“example_method”，mrb_example_methodMRB_ARGS_NONE（））；mrb-undefine_class_method
 *
 *      无效mrb_example_gem_final（mrb_state mrb）｛｝
 * @param [mrb_state*] mrb_state*mruby状态引用。
 * @param [RClass*] RClass*类方法将从中定义的类。
 * @param [const char*]constchar*要定义的类方法的名称。
 */
MRB_API void mrb_undef_class_method(mrb_state*, struct RClass*, const char*);

/**
 * 初始化c类的新对象实例。
 *
 * 例子：
 *
 *     #Ruby风格类ExampleClass结束
 *
 *     p ExampleClass#=>#<ExampleClass:0x99558588>//C style#include<stdio。h> #包含<mruby.h>
 *
 *     void mrb_example_gem_init（mrb_state mrb）{struct RClass example_class；mrb_value obj；example_class=mrb_define_class（mrb，“ExampleClass”，mrb->object_class）；#=>class ExampleClass；end obj=mrb_obj_new（mrb、example_class，0，NULL）；#=>ExampleClass.new mrb_p（mrb），obj）；//=>内核#p}
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [RClass*] c对新对象的类的引用。
 * @param [mrb_int] argc argv中的参数数
 * @param [const mrb_value*]argv用于初始化对象的mrb_value数组
 * @return [mrb_value]新初始化的对象
 */
MRB_API mrb_value mrb_obj_new(mrb_state *mrb, struct RClass *c, mrb_int argc, const mrb_value *argv);

/**@参见mrb_obj_new*/
MRB_INLINE mrb_value mrb_class_new_instance(mrb_state *mrb, mrb_int argc, const mrb_value *argv, struct RClass *c)
{
  return mrb_obj_new(mrb,c,argc,argv);
}

MRB_API mrb_value mrb_instance_new(mrb_state *mrb, mrb_value cv);

/**
 * 创建类的新实例Class。
 *
 * 例子：
 *
 *      void mrb_example_gem_init（mrb_state mrb）{struct RClass example_class；
 *
 *        mrb_value对象；example_class=mrb_class_new（mrb，mrb->object_class）；obj=mrb_obj_new（mrb，example_class，0，NULL）；//=>#<#<类：0x9a945b8>：0x9a 94588>mrb_p（mrb，obj）；//=>内核#p｝
 *
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [struct RClass*]super超级类或父类。
 * @return [struct RClass*]对新类的引用。
 */
MRB_API struct RClass * mrb_class_new(mrb_state *mrb, struct RClass *super);

/**
 * 创建新模块module。
 *
 * 示例：void mrb_Example_gem_init（mrb_state mrb）{struct RClass Example_module；
 *
 *        example_module=mrb_module_new（mrb）；}
 *
 * @param [mrb_state*] mrb当前mruby状态。
 * @return [struct RClass*]对新模块的引用。
 */
MRB_API struct RClass * mrb_module_new(mrb_state *mrb);

/**
 * 返回mrb_bool。如果已定义类，则为True；如果未定义类，为false。
 *
 * 示例：void mrb_Example_gem_init（mrb_state mrb）{struct RClass Example_class；mrb_bool cd；
 *
 *       example_class=mrb_define_class（mrb，“ExampleClass”，mrb->object_class）；cd=mrb_class_defined（mrb，“ExampleClass”）；
 *
 *       //如果mrb_class_defined返回1，则置“True”//如果mrb_class_defined为0，则置为“False”，如果（cd==1）｛put（“True”）；｝否则｛put（“False”）；｝｝
 *
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [const char*]name表示类名称的字符串。
 * @return [mrb_bool]布尔值。
 */
MRB_API mrb_bool mrb_class_defined(mrb_state *mrb, const char *name);

/**
 * 获取类。
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [const char*]name类的名称。
 * @return [struct RClass*]对类的引用。
*/
MRB_API struct RClass * mrb_class_get(mrb_state *mrb, const char *name);

/**
 * 获取异常类。
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [const char*]name类的名称。
 * @return [struct RClass*]对类的引用。
*/
MRB_API struct RClass * mrb_exc_get(mrb_state *mrb, const char *name);

/**
 * 返回mrb_bool。如果已定义内部类，则为True；如果未定义内部类则为false。
 *
 * 示例：void mrb_Example_gem_init（mrb_state mrb）{struct RClass Example_outer，Example_inner；mrb_bool cd；
 *
 *       example_outr=mrb_define_module（mrb，“ExampleOuter”）；
 *
 *       example_inner=mrb_define_class_under（mrb，example_outer，“ExampleInner”，mrb->object_class）；cd=mrb_class_defined_bunder（mrb，example_outer，“ExampleInner”）；
 *
 *       //如果mrb_class_defined_bunder返回1，则置为“True”//如果mrb_class_defined_dunder返回0，则置“False”，如果（cd==1）｛put（“True”）；｝否则｛put（“False”）；｝｝
 *
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [struct RClass*]outer外部类的名称。
 * @param [const char*]name表示内部类名称的字符串。
 * @return [mrb_bool]布尔值。
 */
MRB_API mrb_bool mrb_class_defined_under(mrb_state *mrb, struct RClass *outer, const char *name);

/**
 * 获取子类。
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [struct RClass*]outer父类的名称。
 * @param [const char*]name类的名称。
 * @return [struct RClass*]对类的引用。
*/
MRB_API struct RClass * mrb_class_get_under(mrb_state *mrb, struct RClass *outer, const char *name);

/**
 * 获取模块。
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [const char*]name模块的名称。
 * @return [struct RClass*]对模块的引用。
*/
MRB_API struct RClass * mrb_module_get(mrb_state *mrb, const char *name);

/**
 * 获取在另一个模块下定义的模块。
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [struct RClass*]outer外部模块的名称。
 * @param [const char*]name模块的名称。
 * @return [struct RClass*]对模块的引用。
*/
MRB_API struct RClass * mrb_module_get_under(mrb_state *mrb, struct RClass *outer, const char *name);
/* 使用当前方法名引发NotImplementedError的函数*/
MRB_API void mrb_notimplement(mrb_state*);
/* 要替换未实现方法的函数*/
MRB_API mrb_value mrb_notimplement_m(mrb_state*, mrb_value);

/**
 * 复制对象。
 *
 * 等效于：对象#dup
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [mrb_value] obj对象要重复。
 * @return [mrb_value]新复制的对象。
 */
MRB_API mrb_value mrb_obj_dup(mrb_state *mrb, mrb_value obj);

/**
 * 如果obj响应给定方法，则返回true。如果该方法是为该类定义的，则返回true，否则返回false。
 *
 *      示例：#Ruby样式类ExampleClass def Example_method end end
 *
 *      示例Class.new。响应？（：example_method）#=>真
 *
 *      //C样式void mrb_example_gem_init（mrb_state mrb）{struct RClass example_class；mrb_sym-mid；mrb_bool obj_resp；
 *
 *        example_class=mrb_define_class（mrb，“ExampleClass”，mrb->object_class）；mrb_define_method（mrb，example_class，“example_method”，exampleMethod，mrb_ARGS_NONE（））；mid=mrb_inter_str（mrb，mrb_str_new_lit（mrb“示例方法”））；obj_resp=mrb_obj_respond_to（mrb，example_class，mid）；//=>1（在Ruby世界中为真）
 *
 *        //如果mrb_obj_respond_to返回1，则放入“True”//如果mrb_obj_respond _to返回0，则如果（obj_resp==1）｛put（“True”）；｝否则如果（obj_resp==0）｛put（“False”）；｝｝
 *
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [struct RClass*]c类的引用。
 * @param [mrb_sym] mid引用方法id的符号。
 * @return [mrb_bool]布尔值。
 */
MRB_API mrb_bool mrb_obj_respond_to(mrb_state *mrb, struct RClass* c, mrb_sym mid);

/**
 * 在给定模块下定义新类
 *
 * @param [mrb_state*] mrb当前mruby状态。
 * @param [struct RClass*]outer对将在其下定义新类的模块的引用
 * @param [const char*]name定义的类的名称
 * @param [struct RClass*]super新的类父级
 * @return [struct RClass*]对新定义的类的引用
 * @see mrb_define_类
 */
MRB_API struct RClass * mrb_define_class_under(mrb_state *mrb, struct RClass *outer, const char *name, struct RClass *super);

MRB_API struct RClass * mrb_define_module_under(mrb_state *mrb, struct RClass *outer, const char *name);

/**
 * 函数需要n个参数。
 *
 * @param n 所需参数的数量。
 */
#define MRB_ARGS_REQ(n)     ((mrb_aspec)((n)&0x1f) << 18)

/**
 * 函数接受n个可选参数
 *
 * @param n 可选参数的数量。
 */
#define MRB_ARGS_OPT(n)     ((mrb_aspec)((n)&0x1f) << 13)

/**
 * 函数接受n1个强制参数和n2个可选参数
 *
 * @param n1 所需参数的数量。
 * @param n2 可选参数的数量。
 */
#define MRB_ARGS_ARG(n1,n2)   (MRB_ARGS_REQ(n1)|MRB_ARGS_OPT(n2))

/**休息论点*/
#define MRB_ARGS_REST()     ((mrb_aspec)(1 << 12))

/**rest后的必需参数*/
#define MRB_ARGS_POST(n)    ((mrb_aspec)((n)&0x1f) << 7)

/**关键字参数（n个关键字，kdict）*/
#define MRB_ARGS_KEY(n1,n2) ((mrb_aspec)((((n1)&0x1f) << 2) | ((n2)?(1<<1):0)))

/**
 * 函数采用块参数
 */
#define MRB_ARGS_BLOCK()    ((mrb_aspec)1)

/**
 * 函数接受任意数量的参数
 */
#define MRB_ARGS_ANY()      MRB_ARGS_REST()

/**
 * 函数不接受参数
 */
#define MRB_ARGS_NONE()     ((mrb_aspec)0)

/**
 * ｛mrb_get_args｝函数的格式说明符
 *
 * 必须是由以下格式说明符组成的C字符串：
 *
 * |char | Ruby类型| C类型|注释| |：----：|----------------|----------------|--------------------------------------------------| | `o` |｛Object｝|｛mrb_value｝|可用于检索任何类型的参数| | `C` |{Class｝/｛Module｝|{mrb_value｝| | | |`S` |{String｝|在后面，值可以是“nil”| |“A”|｛Array｝|｛mrb_value｝| when“！”在下面，该值可以是“nil”| |“H”|｛Hash｝|｛mrb_value｝| when“！”下面，值可以是“nil”| |“s”|｛String｝| char，｛mrb_int｝|接收两个参数`s！`为以“nil”| |“z”|｛String｝| char |“NULL”结尾的字符串指定（“NULL”，“0”）`z！`为“nil”| |“a”提供“NULL”|｛Array｝|｛mrb_value｝，｛mrb_int｝|接收两个参数`a！`为“nil”| |“f”|｛Float｝|｛mrb_Float｝| | |‘i’|｛Integer｝|{mrb_int｝| ||`b` | boolean |｛mrb_bool｝| || |`n` |｛Symbol｝|｝mrb_sym｝|||`&` | block |｛mr b_value｝|&！如果没有给定块，则引发异常。||``|rest arguments |｛mrb_value｝，｛mrb_int｝|以数组形式接收其余参数！避免复制堆栈。||&垂直；|可选||在此规范之后，以下规范将是可选的。||`？`|如果给定了前面的参数，则给定|｛mrb_bool｝|“TRUE”是可选的。用于检查给定的可选参数|
 *
 * @see mrb_get_args
 */
typedef const char *mrb_args_format;

/**
 * 从mrb_state检索参数。
 *
 * @param mrb 当前MRuby状态。
 * @param format [mrb_args_format]是格式说明符列表
 * @param ... 传递的变量参数必须是检索类型的指针。
 * @return 检索的参数数。
 * @see mrb_args格式
 */
MRB_API mrb_int mrb_get_args(mrb_state *mrb, mrb_args_format format, ...);

static inline mrb_sym
mrb_get_mid(mrb_state *mrb) /* get方法符号*/
{
  return mrb->c->ci->mid;
}

/**
 * 从mrb_state中检索参数数。
 *
 * 正确处理*splat参数。
 */
MRB_API mrb_int mrb_get_argc(mrb_state *mrb);

MRB_API mrb_value* mrb_get_argv(mrb_state *mrb);

/* `字符串文字的strlen`（请谨慎使用或改用“strlen`”）相邻字符串文字在转换阶段6中在C/C++中连接。如果“lit”不是一个，编译器将报告语法错误：MSVC:“error C2143:syntax error:missing'）'before”string“”GCC:“error:expected”）'bebefore string constant“”
*/
#define mrb_strlen_lit(lit) (sizeof(lit "") - 1)

/**
 * 调用现有的ruby函数。
 *
 *      #包括<stdio。h> #include<mruby。h> #include“mruby/compile.h”
 *
 *      int main（）｛mrb_int i=99；mrb_state mrb=mrb_open（）；
 *
 *        如果（！mrb）｛｝FILE fp=fopen（“test.rb”，“r”）；mrb_value obj=mrb_load_file（mrb，fp）；mrb_funall（mrb，obj，“方法名”，1，mrb_fixnum_value（i））；fclose（fp）；mrb_close（mrb）；}
 * @param [mrb_state*] mrb_state*当前mruby状态。
 * @param [mrb_value] mrb_value对mruby值的引用。
 * @param [const char*]constchar*方法的名称。
 * @param [mrb_int] mrb_int方法的参数数。
 * @param [...] …变量值（不类型安全！）。
 * @return [mrb_value]mrb_value mruby函数值。
 */
MRB_API mrb_value mrb_funcall(mrb_state*, mrb_value, const char*, mrb_int,...);
/**
 * 调用现有的ruby函数。这基本上是mrb_funall的类型安全版本。
 *
 *      #包括<stdio。h> #include<mruby。h> #include“mruby/compile.h”int main（）｛mrb_int i=99；mrb_state mrb=mrb_open（）；
 *
 *        如果（！mrb）｛｝mrb_sym m_sym=mrb_inter_lit（mrb，“方法名”）；//方法的符号。
 *
 *        FILE*fp=fopen（“test.rb”，“r”）；mrb_value obj=mrb_load_file（mrb，fp）；mrb_funcall_argv（mrb，obj，m_sym，1，&obj）；//从test.rb调用ruby函数。fclose（fp）；mrb_close（mrb）；}
 * @param [mrb_state*] mrb_state*当前mruby状态。
 * @param [mrb_value] mrb_value对mruby值的引用。
 * @param [mrb_sym] mrb_sym表示方法的符号。
 * @param [mrb_int] mrb_int方法的参数数。
 * @param [const mrb_value*]mrb_value*指向对象的指针。
 * @return [mrb_value]mrb_value mruby函数值。
 * @see mrb函数
 */
MRB_API mrb_value mrb_funcall_argv(mrb_state*, mrb_value, mrb_sym, mrb_int, const mrb_value*);
/**
 * 用块调用现有的ruby函数。
 */
MRB_API mrb_value mrb_funcall_with_block(mrb_state*, mrb_value, mrb_sym, mrb_int, const mrb_value*, mrb_value);
/**
 * 创建符号
 *
 *     #红宝石风格：：pizza#=>：pizza
 *
 *     //C样式：mrb_sym m_sym=mrb_intern_list（mrb，“pizza”）；//=>：披萨
 * @param [mrb_state*] mrb_state*当前mruby状态。
 * @param [const char*]constchar*方法的名称。
 * @return [mrb_sym]mrb_sym符号。
 */
MRB_API mrb_sym mrb_intern_cstr(mrb_state*,const char*);
MRB_API mrb_sym mrb_intern(mrb_state*,const char*,size_t);
MRB_API mrb_sym mrb_intern_static(mrb_state*,const char*,size_t);
#define mrb_intern_lit(mrb, lit) mrb_intern_static(mrb, lit, mrb_strlen_lit(lit))
MRB_API mrb_sym mrb_intern_str(mrb_state*,mrb_value);
MRB_API mrb_value mrb_check_intern_cstr(mrb_state*,const char*);
MRB_API mrb_value mrb_check_intern(mrb_state*,const char*,size_t);
MRB_API mrb_value mrb_check_intern_str(mrb_state*,mrb_value);
MRB_API const char *mrb_sym2name(mrb_state*,mrb_sym);
MRB_API const char *mrb_sym2name_len(mrb_state*,mrb_sym,mrb_int*);
MRB_API mrb_value mrb_sym2str(mrb_state*,mrb_sym);

MRB_API void *mrb_malloc(mrb_state*, size_t);         /* 如果没有内存，则引发RuntimeError*/
MRB_API void *mrb_calloc(mrb_state*, size_t, size_t); /* 同上*/
MRB_API void *mrb_realloc(mrb_state*, void*, size_t); /* 同上*/
MRB_API void *mrb_realloc_simple(mrb_state*, void*, size_t); /* 如果没有可用内存，则返回NULL*/
MRB_API void *mrb_malloc_simple(mrb_state*, size_t);  /* 如果没有可用内存，则返回NULL*/
MRB_API struct RBasic *mrb_obj_alloc(mrb_state*, enum mrb_vtype, struct RClass*);
MRB_API void mrb_free(mrb_state*, void*);

MRB_API mrb_value mrb_str_new(mrb_state *mrb, const char *p, size_t len);

/**
 * 将C字符串转换为Ruby字符串值。
 */
MRB_API mrb_value mrb_str_new_cstr(mrb_state*, const char*);
MRB_API mrb_value mrb_str_new_static(mrb_state *mrb, const char *p, size_t len);
#define mrb_str_new_lit(mrb, lit) mrb_str_new_static(mrb, (lit), mrb_strlen_lit(lit))

#ifdef _WIN32
MRB_API char* mrb_utf8_from_locale(const char *p, int len);
MRB_API char* mrb_locale_from_utf8(const char *p, int len);
#define mrb_locale_free(p) free(p)
#define mrb_utf8_free(p) free(p)
#else
#define mrb_utf8_from_locale(p, l) ((char*)(p))
#define mrb_locale_from_utf8(p, l) ((char*)(p))
#define mrb_locale_free(p)
#define mrb_utf8_free(p)
#endif

/**
 * 创建新的mrb_state。
 *
 * @return 指向新创建的mrb_state的指针。
 */
MRB_API mrb_state* mrb_open(void);

/**
 * 使用自定义分配器创建新的mrb_state。
 *
 * @param f 对分配函数的引用。
 * @param ud 用户数据将传递给自定义分配器f。如果不需要用户数据，只需传递NULL。
 * @return 指向新创建的mrb_state的指针。
 */
MRB_API mrb_state* mrb_open_allocf(mrb_allocf f, void *ud);

/**
 * 仅使用MRuby核心创建新的mrb_state
 *
 * @param f 对分配函数的引用。使用mrb_default_allocf作为默认值
 * @param ud 用户数据将传递给自定义分配器f。如果不需要用户数据，只需传递NULL。
 * @return 指向新创建的mrb_state的指针。
 */
MRB_API mrb_state* mrb_open_core(mrb_allocf f, void *ud);

/**
 * 关闭并释放mrb_state。
 *
 * @param mrb 指向要关闭的mrb_state的指针。
 */
MRB_API void mrb_close(mrb_state *mrb);

/**
 * 默认分配函数。
 *
 * @see mrb分配
 */
MRB_API void* mrb_default_allocf(mrb_state*, void*, size_t, void*);

MRB_API mrb_value mrb_top_self(mrb_state *);
MRB_API mrb_value mrb_run(mrb_state*, struct RProc*, mrb_value);
MRB_API mrb_value mrb_top_run(mrb_state*, struct RProc*, mrb_value, unsigned int);
MRB_API mrb_value mrb_vm_run(mrb_state*, struct RProc*, mrb_value, unsigned int);
MRB_API mrb_value mrb_vm_exec(mrb_state*, struct RProc*, mrb_code*);
/* 兼容性宏*/
#define mrb_toplevel_run_keep(m,p,k) mrb_top_run((m),(p),mrb_top_self(m),(k))
#define mrb_toplevel_run(m,p) mrb_toplevel_run_keep((m),(p),0)
#define mrb_context_run(m,p,s,k) mrb_vm_run((m),(p),(s),(k))

MRB_API void mrb_p(mrb_state*, mrb_value);
MRB_API mrb_int mrb_obj_id(mrb_value obj);
MRB_API mrb_sym mrb_obj_to_sym(mrb_state *mrb, mrb_value name);

MRB_API mrb_bool mrb_obj_eq(mrb_state*, mrb_value, mrb_value);
MRB_API mrb_bool mrb_obj_equal(mrb_state*, mrb_value, mrb_value);
MRB_API mrb_bool mrb_equal(mrb_state *mrb, mrb_value obj1, mrb_value obj2);
MRB_API mrb_value mrb_convert_to_integer(mrb_state *mrb, mrb_value val, mrb_int base);
MRB_API mrb_value mrb_Integer(mrb_state *mrb, mrb_value val);
#ifndef MRB_WITHOUT_FLOAT
MRB_API mrb_value mrb_Float(mrb_state *mrb, mrb_value val);
#endif
MRB_API mrb_value mrb_inspect(mrb_state *mrb, mrb_value obj);
MRB_API mrb_bool mrb_eql(mrb_state *mrb, mrb_value obj1, mrb_value obj2);

static inline int mrb_gc_arena_save(mrb_state*);
static inline void mrb_gc_arena_restore(mrb_state*,int);

static inline int
mrb_gc_arena_save(mrb_state *mrb)
{
  return mrb->gc.arena_idx;
}

static inline void
mrb_gc_arena_restore(mrb_state *mrb, int idx)
{
  mrb->gc.arena_idx = idx;
}

MRB_API void mrb_garbage_collect(mrb_state*);
MRB_API void mrb_full_gc(mrb_state*);
MRB_API void mrb_incremental_gc(mrb_state *);
MRB_API void mrb_gc_mark(mrb_state*,struct RBasic*);
#define mrb_gc_mark_value(mrb,val) do {\
  if (!mrb_immediate_p(val)) mrb_gc_mark((mrb), mrb_basic_ptr(val)); \
} while (0)
MRB_API void mrb_field_write_barrier(mrb_state *, struct RBasic*, struct RBasic*);
#define mrb_field_write_barrier_value(mrb, obj, val) do{\
  if (!mrb_immediate_p(val)) mrb_field_write_barrier((mrb), (obj), mrb_basic_ptr(val)); \
} while (0)
MRB_API void mrb_write_barrier(mrb_state *, struct RBasic*);

MRB_API mrb_value mrb_check_convert_type(mrb_state *mrb, mrb_value val, enum mrb_vtype type, const char *tname, const char *method);
MRB_API mrb_value mrb_any_to_s(mrb_state *mrb, mrb_value obj);
MRB_API const char * mrb_obj_classname(mrb_state *mrb, mrb_value obj);
MRB_API struct RClass* mrb_obj_class(mrb_state *mrb, mrb_value obj);
MRB_API mrb_value mrb_class_path(mrb_state *mrb, struct RClass *c);
MRB_API mrb_value mrb_convert_type(mrb_state *mrb, mrb_value val, enum mrb_vtype type, const char *tname, const char *method);
MRB_API mrb_bool mrb_obj_is_kind_of(mrb_state *mrb, mrb_value obj, struct RClass *c);
MRB_API mrb_value mrb_obj_inspect(mrb_state *mrb, mrb_value self);
MRB_API mrb_value mrb_obj_clone(mrb_state *mrb, mrb_value self);

#ifndef ISPRINT
#define ISASCII(c) ((unsigned)(c) <= 0x7f)
#define ISPRINT(c) (((unsigned)(c) - 0x20) < 0x5f)
#define ISSPACE(c) ((c) == ' ' || (unsigned)(c) - '\t' < 5)
#define ISUPPER(c) (((unsigned)(c) - 'A') < 26)
#define ISLOWER(c) (((unsigned)(c) - 'a') < 26)
#define ISALPHA(c) ((((unsigned)(c) | 0x20) - 'a') < 26)
#define ISDIGIT(c) (((unsigned)(c) - '0') < 10)
#define ISXDIGIT(c) (ISDIGIT(c) || ((unsigned)(c) | 0x20) - 'a' < 6)
#define ISALNUM(c) (ISALPHA(c) || ISDIGIT(c))
#define ISBLANK(c) ((c) == ' ' || (c) == '\t')
#define ISCNTRL(c) ((unsigned)(c) < 0x20 || (c) == 0x7f)
#define TOUPPER(c) (ISLOWER(c) ? ((c) & 0x5f) : (c))
#define TOLOWER(c) (ISUPPER(c) ? ((c) | 0x20) : (c))
#endif

MRB_API mrb_value mrb_exc_new(mrb_state *mrb, struct RClass *c, const char *ptr, size_t len);
MRB_API mrb_noreturn void mrb_exc_raise(mrb_state *mrb, mrb_value exc);

MRB_API mrb_noreturn void mrb_raise(mrb_state *mrb, struct RClass *c, const char *msg);
MRB_API mrb_noreturn void mrb_raisef(mrb_state *mrb, struct RClass *c, const char *fmt, ...);
MRB_API mrb_noreturn void mrb_name_error(mrb_state *mrb, mrb_sym id, const char *fmt, ...);
MRB_API void mrb_warn(mrb_state *mrb, const char *fmt, ...);
MRB_API mrb_noreturn void mrb_bug(mrb_state *mrb, const char *fmt, ...);
MRB_API void mrb_print_backtrace(mrb_state *mrb);
MRB_API void mrb_print_error(mrb_state *mrb);
/* 用于“raisef”格式的函数*/
MRB_API mrb_value mrb_vformat(mrb_state *mrb, const char *format, va_list ap);

/* 获取典型异常对象的宏注意：+这些E_宏需要名为mrb的mrb_state变量。+从这些宏获得的异常对象是mrb本地的
*/
#define E_RUNTIME_ERROR             (mrb_exc_get(mrb, "RuntimeError"))
#define E_TYPE_ERROR                (mrb_exc_get(mrb, "TypeError"))
#define E_ARGUMENT_ERROR            (mrb_exc_get(mrb, "ArgumentError"))
#define E_INDEX_ERROR               (mrb_exc_get(mrb, "IndexError"))
#define E_RANGE_ERROR               (mrb_exc_get(mrb, "RangeError"))
#define E_NAME_ERROR                (mrb_exc_get(mrb, "NameError"))
#define E_NOMETHOD_ERROR            (mrb_exc_get(mrb, "NoMethodError"))
#define E_SCRIPT_ERROR              (mrb_exc_get(mrb, "ScriptError"))
#define E_SYNTAX_ERROR              (mrb_exc_get(mrb, "SyntaxError"))
#define E_LOCALJUMP_ERROR           (mrb_exc_get(mrb, "LocalJumpError"))
#define E_REGEXP_ERROR              (mrb_exc_get(mrb, "RegexpError"))
#define E_FROZEN_ERROR              (mrb_exc_get(mrb, "FrozenError"))

#define E_NOTIMP_ERROR              (mrb_exc_get(mrb, "NotImplementedError"))
#ifndef MRB_WITHOUT_FLOAT
#define E_FLOATDOMAIN_ERROR         (mrb_exc_get(mrb, "FloatDomainError"))
#endif

#define E_KEY_ERROR                 (mrb_exc_get(mrb, "KeyError"))

MRB_API mrb_value mrb_yield(mrb_state *mrb, mrb_value b, mrb_value arg);
MRB_API mrb_value mrb_yield_argv(mrb_state *mrb, mrb_value b, mrb_int argc, const mrb_value *argv);
MRB_API mrb_value mrb_yield_with_class(mrb_state *mrb, mrb_value b, mrb_int argc, const mrb_value *argv, mrb_value self, struct RClass *c);

/* 继续执行进程*/
/* 该函数应始终作为方法的最后一个函数调用*/
/* e、 g.返回mrb_yield_cont（mrb，proc，self，argc，argv）；*/
mrb_value mrb_yield_cont(mrb_state *mrb, mrb_value b, mrb_value self, mrb_int argc, const mrb_value *argv);

/* mrb_gc_proctect（）将对象留在竞技场中*/
MRB_API void mrb_gc_protect(mrb_state *mrb, mrb_value obj);
/* mrb_gc_register（）将对象从gc中删除。*/
MRB_API void mrb_gc_register(mrb_state *mrb, mrb_value obj);
/* mrb_gc_unregister（）从gc根目录中删除对象。*/
MRB_API void mrb_gc_unregister(mrb_state *mrb, mrb_value obj);

MRB_API mrb_value mrb_to_int(mrb_state *mrb, mrb_value val);
#define mrb_int(mrb, val) mrb_fixnum(mrb_to_int(mrb, val))
MRB_API mrb_value mrb_to_str(mrb_state *mrb, mrb_value val);
MRB_API void mrb_check_type(mrb_state *mrb, mrb_value x, enum mrb_vtype t);

typedef enum call_type {
  CALL_PUBLIC,
  CALL_FCALL,
  CALL_VCALL,
  CALL_TYPE_MAX
} call_type;

MRB_API void mrb_define_alias(mrb_state *mrb, struct RClass *c, const char *a, const char *b);
MRB_API const char *mrb_class_name(mrb_state *mrb, struct RClass* klass);
MRB_API void mrb_define_global_const(mrb_state *mrb, const char *name, mrb_value val);

MRB_API mrb_value mrb_attr_get(mrb_state *mrb, mrb_value obj, mrb_sym id);

MRB_API mrb_bool mrb_respond_to(mrb_state *mrb, mrb_value obj, mrb_sym mid);
MRB_API mrb_bool mrb_obj_is_instance_of(mrb_state *mrb, mrb_value obj, struct RClass* c);
MRB_API mrb_bool mrb_func_basic_p(mrb_state *mrb, mrb_value obj, mrb_sym mid, mrb_func_t func);


/*
 * 恢复光纤
 *
 * @mrbgem mruby光纤
 */
MRB_API mrb_value mrb_fiber_resume(mrb_state *mrb, mrb_value fib, mrb_int argc, const mrb_value *argv);

/*
 * 产生纤维
 *
 * @mrbgem mruby光纤
 */
MRB_API mrb_value mrb_fiber_yield(mrb_state *mrb, mrb_int argc, const mrb_value *argv);

/*
 * 检查光纤是否带电
 *
 * @mrbgem mruby光纤
 */
MRB_API mrb_value mrb_fiber_alive_p(mrb_state *mrb, mrb_value fib);

/*
 * FiberError参考
 *
 * @mrbgem mruby光纤
 */
#define E_FIBER_ERROR (mrb_exc_get(mrb, "FiberError"))
MRB_API void mrb_stack_extend(mrb_state*, mrb_int);

/* 内存池实现*/
typedef struct mrb_pool mrb_pool;
MRB_API struct mrb_pool* mrb_pool_open(mrb_state*);
MRB_API void mrb_pool_close(struct mrb_pool*);
MRB_API void* mrb_pool_alloc(struct mrb_pool*, size_t);
MRB_API void* mrb_pool_realloc(struct mrb_pool*, void*, size_t oldlen, size_t newlen);
MRB_API mrb_bool mrb_pool_can_realloc(struct mrb_pool*, void*, size_t);
MRB_API void* mrb_alloca(mrb_state *mrb, size_t);

MRB_API void mrb_state_atexit(mrb_state *mrb, mrb_atexit_func func);

MRB_API void mrb_show_version(mrb_state *mrb);
MRB_API void mrb_show_copyright(mrb_state *mrb);

MRB_API mrb_value mrb_format(mrb_state *mrb, const char *format, ...);

#if 0
/* memcpy和memset不适用于我的盒子上的gdb reverse next*/
/* 改用naive memcpy和memset*/
#undef memcpy
#undef memset
static void*
mrbmemcpy(void *dst, const void *src, size_t n)
{
  char *d = (char*)dst;
  const char *s = (const char*)src;
  while (n--)
    *d++ = *s++;
  return d;
}
#define memcpy(a,b,c) mrbmemcpy(a,b,c)

static void*
mrbmemset(void *s, int c, size_t n)
{
  char *t = (char*)s;
  while (n--)
    *t++ = c;
  return s;
}
#define memset(a,b,c) mrbmemset(a,b,c)
#endif

MRB_END_DECL

#endif  /* MRUBY_H */

