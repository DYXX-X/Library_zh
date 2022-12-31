/* 分配函数的接口，用于跟踪已释放或未释放的内容。__ __ __ __ ___ \\/__ __ __ | | __/__ \\/|'__ \/_ ` | __ | __//\ |）|（_||_\___/__/__/\.__/\__，_|\__|_|XML解析器

   版权所有（c）2017 Rhodori James<rhodri@wildebeest.org.uk>版权所有（c）2017 Sebastian Pipping<sebastian@pipping.org>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef XML_MEMCHECK_H
#  define XML_MEMCHECK_H 1

/* 分配声明*/

void *tracking_malloc(size_t size);
void tracking_free(void *ptr);
void *tracking_realloc(void *ptr, size_t size);

/* 测试结束时，检查是否仍有未解冻的分配。如果没有，则返回TRUE（1），否则打印剩余分配的报告并返回FALSE（0）。
 */
int tracking_report(void);

#endif /* XML_MEMCHECK_H */

#ifdef __cplusplus
}
#endif

