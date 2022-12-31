/* 用于累积和检查结构化内容的一些助手例程的接口（_||_\___/__/__/\.__/\__，_|\__|_|XML解析器

   版权所有（c）2017 Rhodori James<rhodri@wildebeest.org.uk>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef XML_STRUCTDATA_H
#  define XML_STRUCTDATA_H 1

#  include "expat.h"

typedef struct {
  const XML_Char *str;
  int data0;
  int data1;
  int data2;
} StructDataEntry;

typedef struct {
  int count;     /* 使用的条目数*/
  int max_count; /* `entries中StructDataEntry项的数量`*/
  StructDataEntry *entries;
} StructData;

void StructData_Init(StructData *storage);

void StructData_AddItem(StructData *storage, const XML_Char *s, int data0,
                        int data1, int data2);

void StructData_CheckItems(StructData *storage, const StructDataEntry *expected,
                           int count);

void StructData_Dispose(StructData *storage);

#endif /* XML_STRUCTDATA_H */

#ifdef __cplusplus
}
#endif

