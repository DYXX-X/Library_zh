/* 用于累积和检查文本和属性内容的一些助手例程的接口（_||_\___/__/__/\.__/\__，_|\__|_|XML解析器

   版权所有（c）2002-2004 Fred L.Drake，Jr<fdrake@users.sourceforge.net>版权所有（c）2017 Rhodori James<rhodri@wildebeest.org.uk>版权所有（c）2017 Sebastian Pipping<sebastian@pipping.org>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef XML_CHARDATA_H
#  define XML_CHARDATA_H 1

#  ifndef XML_VERSION
#    include "expat.h" /* 需要XML_Char*/
#  endif

typedef struct {
  int count; /* #个字符，如果未设置，则<0*/
  XML_Char data[2048];
} CharData;

void CharData_Init(CharData *storage);

void CharData_AppendXMLChars(CharData *storage, const XML_Char *s, int len);

int CharData_CheckXMLChars(CharData *storage, const XML_Char *s);

#endif /* XML_CHARDATA_H */

#ifdef __cplusplus
}
#endif

