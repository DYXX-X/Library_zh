/*
                            ____ __ ___ \\/__ __ __ | | _/_ \\/|'_ \/_ ` | __ | | __//\ | | _）|（_ | | | _ \ ___//\ \.__/\ __，_ | \ __ | | | | __ | XML解析器

   版权所有（c）1997-2000 Thai Open Source Software Center Ltd版权所有（c）2000 Clark Cooper<coopercc@users.sourceforge.net>版权所有（c）2002 Fred L.Drake，Jr<fdrake@users.sourceforge.net>版权所有（c）2016-2017 Sebastian Pipping<sebastian@pipping.org>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <limits.h> /* INT_MAX */
#include <stddef.h>

/* 以下限制（针对XML_Parse的int len）源自xmparse.c中的此循环：
 *
 *    do｛bufferSize=（int）（2U（无符号）bufferSize）；｝而（bufferSize<neededSize&&bufferSize>0）；
 */
#define XML_MAX_CHUNK_LEN (INT_MAX / 2 + 1)

#ifdef XML_UNICODE
int filemap(const wchar_t *name,
            void (*processor)(const void *, size_t, const wchar_t *, void *arg),
            void *arg);
#else
int filemap(const char *name,
            void (*processor)(const void *, size_t, const char *, void *arg),
            void *arg);
#endif

