/*
  版权所有（c）2009-2017 Dave Gamble和cJSON贡献者

  特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

  上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef cJSON__h
#define cJSON__h

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
#define __WINDOWS__
#endif

#ifdef __WINDOWS__

/* 在为windows编译时，我们指定了一个特定的调用约定，以避免从具有不同默认调用约定的项目调用我们的问题。对于窗口，您有3个定义选项：

CJSON_HIDE_SYMBOLS-在您不想删除端口符号的情况下定义此符号CJSON_EXPORT_SYMBOLS-如果您想删除端口号（默认值），请在库构建时定义此符号

For *nix 支持可见性属性的构建，可以通过

通过添加将默认可见性设置为隐藏
-fvisibility=隐藏（对于gcc）或
-xldscope=隐藏（对于sun cc）到CFLAGS

然后使用CJSON_API_VISIILITY标志以CJSON_export_symbols的方式“导出”相同的符号

*/

#define CJSON_CDECL __cdecl
#define CJSON_STDCALL __stdcall

/* 默认情况下导出符号，这是复制粘贴C和头文件所必需的*/
#if !defined(CJSON_HIDE_SYMBOLS) && !defined(CJSON_IMPORT_SYMBOLS) && !defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_EXPORT_SYMBOLS
#endif

#if defined(CJSON_HIDE_SYMBOLS)
#define CJSON_PUBLIC(type)   type CJSON_STDCALL
#elif defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_PUBLIC(type)   __declspec(dllexport) type CJSON_STDCALL
#elif defined(CJSON_IMPORT_SYMBOLS)
#define CJSON_PUBLIC(type)   __declspec(dllimport) type CJSON_STDCALL
#endif
#else /* !__WINDOWS__ */
#define CJSON_CDECL
#define CJSON_STDCALL

#if (defined(__GNUC__) || defined(__SUNPRO_CC) || defined (__SUNPRO_C)) && defined(CJSON_API_VISIBILITY)
#define CJSON_PUBLIC(type)   __attribute__((visibility("default"))) type
#else
#define CJSON_PUBLIC(type) type
#endif
#endif

/* 项目版本*/
#define CJSON_VERSION_MAJOR 1
#define CJSON_VERSION_MINOR 7
#define CJSON_VERSION_PATCH 15

#include <stddef.h>

/* cJSON类型：*/
#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7) /* 原始json*/

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512

/* cJSON结构：*/
typedef struct cJSON
{
    /* next/prev允许您遍历数组/对象链。或者，使用GetArraySize/GetArrayItem/GetObjectItem*/
    struct cJSON *next;
    struct cJSON *prev;
    /* 数组或对象项将具有指向数组/对象中项链的子指针。*/
    struct cJSON *child;

    /* 项目的类型，如上所述。*/
    int type;

    /* 如果类型==cJSON_string，类型==c JSON_Raw，则为项的字符串*/
    char *valuestring;
    /* 写入valueint时已弃用，请改用cJSON_SetNumberValue*/
    int valueint;
    /* 项目编号，如果类型==cJSON_number*/
    double valuedouble;

    /* 项的名称字符串，如果此项是对象的子项或在对象的子项列表中。*/
    char *string;
} cJSON;

typedef struct cJSON_Hooks
{
      /* malloc/free是Windows上的CDECL，无论编译器的默认调用约定如何，因此确保钩子允许直接传递这些函数。*/
      void *(CJSON_CDECL *malloc_fn)(size_t sz);
      void (CJSON_CDECL *free_fn)(void *ptr);
} cJSON_Hooks;

typedef int cJSON_bool;

/* 限制在cJSON拒绝解析数组/对象之前嵌套的深度。这是为了防止堆栈溢出。*/
#ifndef CJSON_NESTING_LIMIT
#define CJSON_NESTING_LIMIT 1000
#endif

/* 以字符串形式返回cJSON的版本*/
CJSON_PUBLIC(const char*) cJSON_Version(void);

/* 向cJSON提供malloc、realloc和free函数*/
CJSON_PUBLIC(void) cJSON_InitHooks(cJSON_Hooks* hooks);

/* 内存管理：调用方始终负责从cJSON_Parse（使用cJSON_Delete）和cJSON_Print（使用stdlib free、cJSON_Hooks.free_fn或cJSON_free，视情况而定）的所有变体中释放结果。异常是cJSON_PrintPreallocated，调用方对缓冲区负有全部责任。*/
/* 提供一个JSON块，这将返回一个可以查询的cJSON对象。*/
CJSON_PUBLIC(cJSON *) cJSON_Parse(const char *value);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLength(const char *value, size_t buffer_length);
/* ParseWithOpts允许您要求（并检查）JSON是否以空结尾，并检索指向最终解析字节的指针。*/
/* 如果在return_parse_end中提供ptr并且解析失败，那么return_passe_end将包含指向错误的指针，因此将匹配cJSON_GetErrorPtr（）。*/
CJSON_PUBLIC(cJSON *) cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLengthOpts(const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated);

/* 将cJSON实体渲染为文本以进行传输/存储。*/
CJSON_PUBLIC(char *) cJSON_Print(const cJSON *item);
/* 将cJSON实体渲染为文本以进行传输/存储，无需任何格式化。*/
CJSON_PUBLIC(char *) cJSON_PrintUnformatted(const cJSON *item);
/* 使用缓冲策略将cJSON实体渲染为文本。prebuffer是对最终大小的猜测。猜对了可以减少再分配。fmt=0表示未格式化，=1表示格式化*/
CJSON_PUBLIC(char *) cJSON_PrintBuffered(const cJSON *item, int prebuffer, cJSON_bool fmt);
/* 使用已在内存中分配的给定长度的缓冲区将cJSON实体渲染为文本。成功时返回1，失败时返回0。*/
/* 注意：cJSON在估计它将使用多少内存时并不总是100%准确，因此为了安全起见，分配的内存比实际需要的多5个字节*/
CJSON_PUBLIC(cJSON_bool) cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format);
/* 删除cJSON实体和所有子实体。*/
CJSON_PUBLIC(void) cJSON_Delete(cJSON *item);

/* 返回数组（或对象）中的项数。*/
CJSON_PUBLIC(int) cJSON_GetArraySize(const cJSON *array);
/* 从数组“array”中检索项目编号“index”。如果失败，则返回NULL。*/
CJSON_PUBLIC(cJSON *) cJSON_GetArrayItem(const cJSON *array, int index);
/* 从对象中获取项“string”。不区分大小写。*/
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItem(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItemCaseSensitive(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON_bool) cJSON_HasObjectItem(const cJSON *object, const char *string);
/* 用于分析失败的解析。这将返回一个指向解析错误的指针。你可能需要回头看几个字符来理解它。当cJSON_Parse（）成功时，cJSON_ Parse（）返回0时定义。*/
CJSON_PUBLIC(const char *) cJSON_GetErrorPtr(void);

/* 检查项目类型并返回其值*/
CJSON_PUBLIC(char *) cJSON_GetStringValue(const cJSON * const item);
CJSON_PUBLIC(double) cJSON_GetNumberValue(const cJSON * const item);

/* 这些函数检查项目的类型*/
CJSON_PUBLIC(cJSON_bool) cJSON_IsInvalid(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsFalse(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsTrue(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsBool(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNull(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNumber(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsString(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsArray(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsObject(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsRaw(const cJSON * const item);

/* 这些调用创建了一个适当类型的cJSON项。*/
CJSON_PUBLIC(cJSON *) cJSON_CreateNull(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateTrue(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateFalse(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateBool(cJSON_bool boolean);
CJSON_PUBLIC(cJSON *) cJSON_CreateNumber(double num);
CJSON_PUBLIC(cJSON *) cJSON_CreateString(const char *string);
/* 原始json*/
CJSON_PUBLIC(cJSON *) cJSON_CreateRaw(const char *raw);
CJSON_PUBLIC(cJSON *) cJSON_CreateArray(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateObject(void);

/* 创建一个字符串，其中valuestring引用字符串，因此cJSON_Delete不会释放该字符串*/
CJSON_PUBLIC(cJSON *) cJSON_CreateStringReference(const char *string);
/* 创建仅引用其元素的对象/数组，以便cJSON_Delete不会释放这些元素*/
CJSON_PUBLIC(cJSON *) cJSON_CreateObjectReference(const cJSON *child);
CJSON_PUBLIC(cJSON *) cJSON_CreateArrayReference(const cJSON *child);

/* 这些实用程序创建计数项数组。参数计数不能大于数字数组中的元素数，否则数组访问将超出范围。*/
CJSON_PUBLIC(cJSON *) cJSON_CreateIntArray(const int *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateFloatArray(const float *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateDoubleArray(const double *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateStringArray(const char *const *strings, int count);

/* 将项附加到指定的数组/对象。*/
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
/* 当字符串肯定是常量（即，一个文本，或与），并且肯定会在cJSON对象中生存时，使用此选项。警告：使用此函数时，确保在写入“item->string”之前始终检查（item->type&cJSON_StringIsConst）为零*/
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item);
/* 将对项的引用附加到指定的数组/对象。当您想将现有cJSON添加到新的cJSON中，但不想损坏现有cJSON时，请使用此选项。*/
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);

/* 从阵列/对象中移除/分离项目。*/
CJSON_PUBLIC(cJSON *) cJSON_DetachItemViaPointer(cJSON *parent, cJSON * const item);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(void) cJSON_DeleteItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObjectCaseSensitive(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_DeleteItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const char *string);

/* 更新数组项。*/
CJSON_PUBLIC(cJSON_bool) cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem); /* 向右移动预先存在的项目。*/
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemViaPointer(cJSON * const parent, cJSON * const item, cJSON * replacement);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObject(cJSON *object,const char *string,cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object,const char *string,cJSON *newitem);

/* 复制cJSON项*/
CJSON_PUBLIC(cJSON *) cJSON_Duplicate(const cJSON *item, cJSON_bool recurse);
/* Duplicate将在需要释放的新内存中创建与您传递的cJSON项相同的新cJSON项。使用递归=0，它将复制连接到该项的所有子项。从Duplicate返回时，项->next和->prev指针始终为零。*/
/* 递归比较两个cJSON项是否相等。如果a或b为NULL或无效，则它们将被视为不相等。区分大小写确定对象键是区分大小写（1）还是不区分大小写*/
CJSON_PUBLIC(cJSON_bool) cJSON_Compare(const cJSON * const a, const cJSON * const b, const cJSON_bool case_sensitive);

/* 精简字符串，从字符串中删除空白字符（如“”、“\t”、“\r”、“\n”）。输入指针json不能指向只读地址区域，例如字符串常量，但应该指向可读写地址区域。*/
CJSON_PUBLIC(void) cJSON_Minify(char *json);

/* 用于同时创建项目和向对象添加项目的助手函数。失败时返回添加的项或NULL。*/
CJSON_PUBLIC(cJSON*) cJSON_AddNullToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddTrueToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddFalseToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddBoolToObject(cJSON * const object, const char * const name, const cJSON_bool boolean);
CJSON_PUBLIC(cJSON*) cJSON_AddNumberToObject(cJSON * const object, const char * const name, const double number);
CJSON_PUBLIC(cJSON*) cJSON_AddStringToObject(cJSON * const object, const char * const name, const char * const string);
CJSON_PUBLIC(cJSON*) cJSON_AddRawToObject(cJSON * const object, const char * const name, const char * const raw);
CJSON_PUBLIC(cJSON*) cJSON_AddObjectToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddArrayToObject(cJSON * const object, const char * const name);

/* 当分配整数值时，它也需要传播到valuedouble。*/
#define cJSON_SetIntValue(object, number) ((object) ? (object)->valueint = (object)->valuedouble = (number) : (number))
/* cJSON_SetNumberValue宏的助手*/
CJSON_PUBLIC(double) cJSON_SetNumberHelper(cJSON *object, double number);
#define cJSON_SetNumberValue(object, number) ((object != NULL) ? cJSON_SetNumberHelper(object, (double)number) : (number))
/* 更改cJSON_String对象的值字符串，仅当对象类型为cJSON_String时生效*/
CJSON_PUBLIC(char*) cJSON_SetValuestring(cJSON *object, const char *valuestring);

/* 用于迭代数组或对象的宏*/
#define cJSON_ArrayForEach(element, array) for(element = (array != NULL) ? (array)->child : NULL; element != NULL; element = element->next)

/* malloc/free对象，使用已使用cJSON_InitHooks设置的malloc/ffree函数*/
CJSON_PUBLIC(void *) cJSON_malloc(size_t size);
CJSON_PUBLIC(void) cJSON_free(void *object);

#ifdef __cplusplus
}
#endif

#endif

