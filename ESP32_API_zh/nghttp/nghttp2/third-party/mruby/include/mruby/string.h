/*
** mruby/string。h-字符串类
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_STRING_H
#define MRUBY_STRING_H

#include "common.h"

/**
 * 字符串类
 */
MRB_BEGIN_DECL

extern const char mrb_digitmap[];

#define RSTRING_EMBED_LEN_MAX ((mrb_int)(sizeof(void*) * 3 - 1))

struct RString {
  MRB_OBJECT_HEADER;
  union {
    struct {
      mrb_int len;
      union {
        mrb_int capa;
        struct mrb_shared_string *shared;
        struct RString *fshared;
      } aux;
      char *ptr;
    } heap;
    char ary[RSTRING_EMBED_LEN_MAX + 1];
  } as;
};

#define RSTR_EMBED_P(s) ((s)->flags & MRB_STR_EMBED)
#define RSTR_SET_EMBED_FLAG(s) ((s)->flags |= MRB_STR_EMBED)
#define RSTR_UNSET_EMBED_FLAG(s) ((s)->flags &= ~(MRB_STR_EMBED|MRB_STR_EMBED_LEN_MASK))
#define RSTR_SET_EMBED_LEN(s, n) do {\
  size_t tmp_n = (n);\
  (s)->flags &= ~MRB_STR_EMBED_LEN_MASK;\
  (s)->flags |= (tmp_n) << MRB_STR_EMBED_LEN_SHIFT;\
} while (0)
#define RSTR_SET_LEN(s, n) do {\
  if (RSTR_EMBED_P(s)) {\
    RSTR_SET_EMBED_LEN((s),(n));\
  }\
  else {\
    (s)->as.heap.len = (mrb_int)(n);\
  }\
} while (0)
#define RSTR_EMBED_LEN(s)\
  (mrb_int)(((s)->flags & MRB_STR_EMBED_LEN_MASK) >> MRB_STR_EMBED_LEN_SHIFT)
#define RSTR_PTR(s) ((RSTR_EMBED_P(s)) ? (s)->as.ary : (s)->as.heap.ptr)
#define RSTR_LEN(s) ((RSTR_EMBED_P(s)) ? RSTR_EMBED_LEN(s) : (s)->as.heap.len)
#define RSTR_CAPA(s) (RSTR_EMBED_P(s) ? RSTRING_EMBED_LEN_MAX : (s)->as.heap.aux.capa)

#define RSTR_SHARED_P(s) ((s)->flags & MRB_STR_SHARED)
#define RSTR_SET_SHARED_FLAG(s) ((s)->flags |= MRB_STR_SHARED)
#define RSTR_UNSET_SHARED_FLAG(s) ((s)->flags &= ~MRB_STR_SHARED)

#define RSTR_FSHARED_P(s) ((s)->flags & MRB_STR_FSHARED)
#define RSTR_SET_FSHARED_FLAG(s) ((s)->flags |= MRB_STR_FSHARED)
#define RSTR_UNSET_FSHARED_FLAG(s) ((s)->flags &= ~MRB_STR_FSHARED)

#define RSTR_NOFREE_P(s) ((s)->flags & MRB_STR_NOFREE)
#define RSTR_SET_NOFREE_FLAG(s) ((s)->flags |= MRB_STR_NOFREE)
#define RSTR_UNSET_NOFREE_FLAG(s) ((s)->flags &= ~MRB_STR_NOFREE)

#define RSTR_POOL_P(s) ((s)->flags & MRB_STR_POOL)
#define RSTR_SET_POOL_FLAG(s) ((s)->flags |= MRB_STR_POOL)

/*
 * 从Ruby字符串返回指针
 */
#define mrb_str_ptr(s)       ((struct RString*)(mrb_ptr(s)))
#define RSTRING(s)           mrb_str_ptr(s)
#define RSTRING_PTR(s)       RSTR_PTR(RSTRING(s))
#define RSTRING_EMBED_LEN(s) RSTR_EMBED_LEN(RSTRING(s))
#define RSTRING_LEN(s)       RSTR_LEN(RSTRING(s))
#define RSTRING_CAPA(s)      RSTR_CAPA(RSTRING(s))
#define RSTRING_END(s)       (RSTRING_PTR(s) + RSTRING_LEN(s))
MRB_API mrb_int mrb_str_strlen(mrb_state*, struct RString*);

#define MRB_STR_SHARED    1
#define MRB_STR_FSHARED   2
#define MRB_STR_NOFREE    4
#define MRB_STR_POOL      8
#define MRB_STR_NO_UTF   16
#define MRB_STR_EMBED    32
#define MRB_STR_EMBED_LEN_MASK 0x7c0
#define MRB_STR_EMBED_LEN_SHIFT 6

void mrb_gc_free_str(mrb_state*, struct RString*);
MRB_API void mrb_str_modify(mrb_state*, struct RString*);

/*
 * 查找字符串中子字符串的索引
 */
MRB_API mrb_int mrb_str_index(mrb_state*, mrb_value, const char*, mrb_int, mrb_int);
#define mrb_str_index_lit(mrb, str, lit, off) mrb_str_index(mrb, str, lit, mrb_strlen_lit(lit), off);

/*
 * 将自己附于他人。将self作为连接字符串返回。
 *
 * 例子：
 *
 *     !!!c int main（int argc，char argv）｛//变量声明。mrb_value str1；mrb_value str2；
 *
 *       mrb_state*mrb=mrb_open（）；if（！mrb）｛//句柄错误｝
 *
 *       //创建新的Ruby字符串。str1=mrb_str_new_lit（mrb，“abc”）；str2=mrb_str_new_lit（mrb，“def”）；
 *
 *       //将str2连接到str1.mrb_str_concat（mrb，str1，str2）；
 *
 *      //打印新的串联Ruby字符串。mrb_p（mrb，str1）；
 *
 *      mrb_close（mrb）；返回0；｝
 *
 * 结果：
 *
 *     =>“abcdef”
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] self要连接的字符串。
 * @param [mrb_value] 其他要附加到自身的字符串。
 * @return [mrb_value]返回将other附加到self的新字符串。
 */
MRB_API void mrb_str_concat(mrb_state*, mrb_value, mrb_value);

/*
 * 将两个字符串相加。
 *
 * 例子：
 *
 *     !!!c int main（int argc，char argv）｛//变量声明。mrb_value a；mrb_value b；mrb_valuec；
 *
 *       mrb_state*mrb=mrb_open（）；if（！mrb）｛//句柄错误｝
 *
 *       //从传入的C字符串创建两个Ruby字符串。a=mrb_str_new_lit（mrb，“abc”）；b=mrb_str_new_lit（mrb，“def”）；
 *
 *       //打印两个C字符串。mrb_p（mrb，a）；mrb_p（mrb，b）；
 *
 *       //连接两个Ruby字符串。c=mrb_str_plus（mrb，a，b）；
 *
 *      //打印新的串联Ruby字符串。mrb_p（mrb，c）；
 *
 *      mrb_close（mrb）；返回0；｝
 *
 * 结果：
 *
 *     =>“abc”#第一字符串=>“def”#第二字符串=>“abcdef”#第一个和第二个串联。
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] a要连接的第一个字符串。
 * @param [mrb_value] b要连接的第二个字符串。
 * @return [mrb_value]返回一个新字符串，其中包含连接到b的a。
 */
MRB_API mrb_value mrb_str_plus(mrb_state*, mrb_value, mrb_value);

/*
 * 将指针转换为Ruby字符串。
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [void*] p要转换为Ruby字符串的指针。
 * @return [mrb_value]返回一个新的Ruby字符串。
 */
MRB_API mrb_value mrb_ptr_to_str(mrb_state *, void*);

/*
 * 以Ruby字符串的形式返回对象。
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] obj作为Ruby字符串返回的对象。
 * @return [mrb_value]作为Ruby字符串的对象。
 */
MRB_API mrb_value mrb_obj_as_string(mrb_state *mrb, mrb_value obj);

/*
 * 调整字符串的长度。返回len指定的中的字符数。
 *
 * 例子：
 *
 *     !!!c int main（int argc，char argv）｛//变量声明.mrb_value str；
 *
 *         mrb_state*mrb=mrb_open（）；if（！mrb）｛//handle error｝//创建新字符串。str=mrb_str_new_lit（mrb，“你好，世界！”）；//返回mrb_str_resize的5个字符（mrb，str，5）；mrb_p（mrb，str）；
 *
 *         mrb_close（mrb）；返回0；｝
 *
 * 结果：
 *
 *     =>“你好”
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] str要调整大小的Ruby字符串。
 * @param [mrb_value] len长度。
 * @return [mrb_value]作为Ruby字符串的对象。
 */
MRB_API mrb_value mrb_str_resize(mrb_state *mrb, mrb_value str, mrb_int len);

/*
 * 返回子字符串。
 *
 *  例子：
 *
 *     !!!c int main（int argc，char const argv）｛//变量声明。mrb_value str1；mrb_value str2；
 *
 *       mrb_state*mrb=mrb_open（）；if（！mrb）｛//handle error｝//创建新字符串。str1=mrb_str_new_lit（mrb，“你好，世界！”）；//返回0..2 str2=mrb_str_substr（mrb，str1，0，2）范围内的子字符串；
 *
 *       //打印子字符串。mrb_p（mrb，str2）；
 *
 *       mrb_close（mrb）；返回0；｝
 *
 *  结果：
 *
 *     =>“他”
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] str Ruby字符串。
 * @param [mrb_int] beg子字符串的起点。
 * @param [mrb_int] len子字符串的终点。
 * @return [mrb_value]作为Ruby子字符串的对象。
 */
MRB_API mrb_value mrb_str_substr(mrb_state *mrb, mrb_value str, mrb_int beg, mrb_int len);

/*
 * 返回Ruby字符串类型。
 *
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] str Ruby字符串。
 * @return [mrb_value]Ruby字符串。
 */
MRB_API mrb_value mrb_ensure_string_type(mrb_state *mrb, mrb_value str);
MRB_API mrb_value mrb_check_string_type(mrb_state *mrb, mrb_value str);
/* 过时：改用mrb_ensure_string_type（）*/
MRB_API mrb_value mrb_string_type(mrb_state *mrb, mrb_value str);


MRB_API mrb_value mrb_str_new_capa(mrb_state *mrb, size_t capa);
MRB_API mrb_value mrb_str_buf_new(mrb_state *mrb, size_t capa);

MRB_API const char *mrb_string_value_cstr(mrb_state *mrb, mrb_value *ptr);
MRB_API const char *mrb_string_value_ptr(mrb_state *mrb, mrb_value str);
/*
 * 返回Ruby字符串的长度。
 *
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] str Ruby字符串。
 * @return [mrb_int]传入的Ruby字符串的长度。
 */
MRB_API mrb_int mrb_string_value_len(mrb_state *mrb, mrb_value str);

/*
 * 复制字符串对象。
 *
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] str Ruby字符串。
 * @return [mrb_value]重复的Ruby字符串。
 */
MRB_API mrb_value mrb_str_dup(mrb_state *mrb, mrb_value str);

/*
 * 从传入的Ruby字符串返回一个符号。
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] self-Ruby字符串。
 * @return [mrb_value]符号。
 */
MRB_API mrb_value mrb_str_intern(mrb_state *mrb, mrb_value self);

MRB_API mrb_value mrb_str_to_inum(mrb_state *mrb, mrb_value str, mrb_int base, mrb_bool badcheck);
MRB_API mrb_value mrb_cstr_to_inum(mrb_state *mrb, const char *s, mrb_int base, mrb_bool badcheck);
MRB_API double mrb_str_to_dbl(mrb_state *mrb, mrb_value str, mrb_bool badcheck);
MRB_API double mrb_cstr_to_dbl(mrb_state *mrb, const char *s, mrb_bool badcheck);

/*
 * 返回转换后的字符串类型。对于类型检查，建议不转换“mrb_to_str”。
 */
MRB_API mrb_value mrb_str_to_str(mrb_state *mrb, mrb_value str);

/*
 * 如果字符串匹配，返回true；如果字符串不匹配，返回false。
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] str1要比较的Ruby字符串。
 * @param [mrb_value] str2要比较的Ruby字符串。
 * @return [mrb_value]布尔值。
 */
MRB_API mrb_bool mrb_str_equal(mrb_state *mrb, mrb_value str1, mrb_value str2);

/*
 * 返回由Ruby字符串和C字符串组成的凹入字符串。
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] str Ruby字符串。
 * @param [const char*]ptr C字符串。
 * @param [size_t] C字符串的len长度。
 * @return [mrb_value]Ruby字符串。
 * @see mrb_str_cat_cstr
 */
MRB_API mrb_value mrb_str_cat(mrb_state *mrb, mrb_value str, const char *ptr, size_t len);

/*
 * 返回由Ruby字符串和C字符串组成的凹入字符串。
 *
 * @param [mrb_state] mrb当前mruby状态。
 * @param [mrb_value] str Ruby字符串。
 * @param [const char*]ptr C字符串。
 * @return [mrb_value]Ruby字符串。
 * @see mrb_str_cat
 */
MRB_API mrb_value mrb_str_cat_cstr(mrb_state *mrb, mrb_value str, const char *ptr);
MRB_API mrb_value mrb_str_cat_str(mrb_state *mrb, mrb_value str, mrb_value str2);
#define mrb_str_cat_lit(mrb, str, lit) mrb_str_cat(mrb, str, lit, mrb_strlen_lit(lit))

/*
 * 将str2添加到str1的末尾。
 */
MRB_API mrb_value mrb_str_append(mrb_state *mrb, mrb_value str, mrb_value str2);

/*
 * 如果两个Ruby字符串相等，则返回0。如果Ruby str1小于Ruby str2，则返回一个值＜0。如果Ruby str2大于Ruby str1，则返回值＞0。
 */
MRB_API int mrb_str_cmp(mrb_state *mrb, mrb_value str1, mrb_value str2);

/*
 * 从Ruby字符串中返回新分配的C字符串。这是一个将Ruby字符串传递给C库函数的实用函数。
 *
 * -返回的字符串不包含任何NUL字符（但包含终止符）。
 * -如果Ruby字符串包含NUL字符，则会引发ArgumentError异常。
 * -下一次GC时，将自动释放返回的字符串。
 * -调用者可以修改返回的字符串而不影响Ruby字符串（例如，它可以用于mkstemp（3））。
 *
 * @param [mrb_state *]mrb当前mruby状态。
 * @param [mrb_value] str Ruby字符串。必须是字符串的实例。
 * @return [char*]新分配的C字符串。
 */
MRB_API char *mrb_str_to_cstr(mrb_state *mrb, mrb_value str);

mrb_value mrb_str_pool(mrb_state *mrb, mrb_value str);
uint32_t mrb_str_hash(mrb_state *mrb, mrb_value str);
mrb_value mrb_str_dump(mrb_state *mrb, mrb_value str);

/*
 * 返回str的可打印版本，用引号括起来，并转义特殊字符。
 */
mrb_value mrb_str_inspect(mrb_state *mrb, mrb_value str);

void mrb_noregexp(mrb_state *mrb, mrb_value self);
void mrb_regexp_check(mrb_state *mrb, mrb_value obj);

/* 为了向后兼容*/
#define mrb_str_cat2(mrb, str, ptr) mrb_str_cat_cstr(mrb, str, ptr)
#define mrb_str_buf_cat(mrb, str, ptr, len) mrb_str_cat(mrb, str, ptr, len)
#define mrb_str_buf_append(mrb, str, str2) mrb_str_cat_str(mrb, str, str2)

#ifdef MRB_UTF8_STRING
mrb_int mrb_utf8_len(const char *str, mrb_int byte_len);
#endif

MRB_END_DECL

#endif  /* MRUBY_STRING_H */

