/*
  版权所有（c）2009-2017 Dave Gamble和cJSON贡献者

  特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

  上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef cJSON_Utils__h
#define cJSON_Utils__h

#ifdef __cplusplus
extern "C"
{
#endif

#include "cJSON.h"

/* 实施RFC6901(https://tools.ietf.org/html/rfc6901)JSON指针规范。*/
CJSON_PUBLIC(cJSON *) cJSONUtils_GetPointer(cJSON * const object, const char *pointer);
CJSON_PUBLIC(cJSON *) cJSONUtils_GetPointerCaseSensitive(cJSON * const object, const char *pointer);

/* 实施RFC6902(https://tools.ietf.org/html/rfc6902)JSON修补程序规范。*/
/* 注意：这将通过按关键字对元素进行排序来修改“from”和“to”中的对象*/
CJSON_PUBLIC(cJSON *) cJSONUtils_GeneratePatches(cJSON * const from, cJSON * const to);
CJSON_PUBLIC(cJSON *) cJSONUtils_GeneratePatchesCaseSensitive(cJSON * const from, cJSON * const to);
/* 用于生成修补程序阵列条目的实用程序。*/
CJSON_PUBLIC(void) cJSONUtils_AddPatchToArray(cJSON * const array, const char * const operation, const char * const path, const cJSON * const value);
/* 返回0表示成功。*/
CJSON_PUBLIC(int) cJSONUtils_ApplyPatches(cJSON * const object, const cJSON * const patches);
CJSON_PUBLIC(int) cJSONUtils_ApplyPatchesCaseSensitive(cJSON * const object, const cJSON * const patches);

/*
//注意ApplyPatches在失败时不是原子的。为了实现原子ApplyPatches，use://intcJSONUtils_AtomicAppyPatches（cJSON对象，cJSON修补程序）//{//cJSON modme=cJSON_Dupplicate（对象，1）；//int error=cJSONtils_ApplyPatches代码没有添加到库中，因为此策略慢了很多。
*/

/* 实施RFC7386(https://tools.ietf.org/html/rfc7396)JSON合并修补程序规范。*/
/* 目标将通过补丁进行修改。返回值是目标的新ptr。*/
CJSON_PUBLIC(cJSON *) cJSONUtils_MergePatch(cJSON *target, const cJSON * const patch);
CJSON_PUBLIC(cJSON *) cJSONUtils_MergePatchCaseSensitive(cJSON *target, const cJSON * const patch);
/* 生成要从->移动到的修补程序*/
/* 注意：这将通过按关键字对元素进行排序来修改“from”和“to”中的对象*/
CJSON_PUBLIC(cJSON *) cJSONUtils_GenerateMergePatch(cJSON * const from, cJSON * const to);
CJSON_PUBLIC(cJSON *) cJSONUtils_GenerateMergePatchCaseSensitive(cJSON * const from, cJSON * const to);

/* 给定一个根对象和一个目标对象，构造一个从一个到另一个的指针。*/
CJSON_PUBLIC(char *) cJSONUtils_FindPointerFromObjectTo(const cJSON * const object, const cJSON * const target);

/* 将对象的成员按字母顺序排序。*/
CJSON_PUBLIC(void) cJSONUtils_SortObject(cJSON * const object);
CJSON_PUBLIC(void) cJSONUtils_SortObjectCaseSensitive(cJSON * const object);

#ifdef __cplusplus
}
#endif

#endif

