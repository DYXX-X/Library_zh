/* 内部.h

   Expat使用的内部定义。编译客户端代码时不需要这样做。

   为经常调用的函数定义了以下调用约定宏：

   FASTCALL-用于具有简单主体和少量参数和局部变量的内部函数。

   PTRCALL-用于通过函数指针调用的函数。

   PTRFASTCALL-与PTRCALL类似，但参数数量较少。

   内联-用于选定的内部函数，内联可以提高某些平台上的性能。

   注意：这些宏的使用是基于判断，而不是硬性规则，因此可能会发生变化（_||_\___/__/__/\.__/\__，_|\__|_|XML解析器

   版权所有（c）2002-2003 Fred L.Drake，Jr<fdrake@users.sourceforge.net>版权所有（c）2002-2006 Karl Waclawek<karl@waclawek.net>版权所有（c）2003 Greg Stein<gstein@users.sourceforge.net>版权所有（c）2016-2021 Sebastian Pipping<sebastian@pipping.org>版权所有（c）2018 Yury Gribov<tetra2005@gmail.com>版权所有（c）2019 David Loffredo<loffredo@steptools.com>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#if defined(__GNUC__) && defined(__i386__) && ! defined(__MINGW32__)
/* 默认情况下，我们将仅在我们知道它有帮助的地方使用此版本。

   regparm（）在Solaris设备上生成警告。参见SF错误#692878。

   RedHat Linux 7.3上egcs报告的不稳定性。让我们评论一下：#define FASTCALL __attribute__（（stdcall，regparm（3）），让我们尝试一下：
*/
#  define FASTCALL __attribute__((regparm(3)))
#  define PTRFASTCALL __attribute__((regparm(3)))
#endif

/* 在MS VC++下，使用__fastcall似乎会产生意想不到的负面影响，尤其是对于函数指针，因此我们现在不会在该平台上使用它。如果它能变得更有效，可能会重新考虑在未来发布。可能的原因：Windows上的__fastcall类似于stdcall，因此编译器无法对调用集群执行堆栈优化。
*/

/* 如果尚未定义，请确保所有这些都已定义。*/

#ifndef FASTCALL
#  define FASTCALL
#endif

#ifndef PTRCALL
#  define PTRCALL
#endif

#ifndef PTRFASTCALL
#  define PTRFASTCALL
#endif

#ifndef XML_MIN_SIZE
#  if ! defined(__cplusplus) && ! defined(inline)
#    ifdef __GNUC__
#      define inline __inline
#    endif /* __GNUC__ */
#  endif
#endif /* XML_MIN_SIZE */

#ifdef __cplusplus
#  define inline inline
#else
#  ifndef inline
#    define inline
#  endif
#endif

#include <limits.h> // ULONG_MAX

#if defined(_WIN32) && ! defined(__USE_MINGW_ANSI_STDIO)
#  define EXPAT_FMT_ULL(midpart) "%" midpart "I64u"
#  if defined(_WIN64) // 注：修饰符“td”和“zu”不适用于MinGW
#    define EXPAT_FMT_PTRDIFF_T(midpart) "%" midpart "I64d"
#    define EXPAT_FMT_SIZE_T(midpart) "%" midpart "I64u"
#  else
#    define EXPAT_FMT_PTRDIFF_T(midpart) "%" midpart "d"
#    define EXPAT_FMT_SIZE_T(midpart) "%" midpart "u"
#  endif
#else
#  define EXPAT_FMT_ULL(midpart) "%" midpart "llu"
#  if ! defined(ULONG_MAX)
#    error Compiler did not define ULONG_MAX for us
#  elif ULONG_MAX == 18446744073709551615u // 2^64-1
#    define EXPAT_FMT_PTRDIFF_T(midpart) "%" midpart "ld"
#    define EXPAT_FMT_SIZE_T(midpart) "%" midpart "lu"
#  else
#    define EXPAT_FMT_PTRDIFF_T(midpart) "%" midpart "d"
#    define EXPAT_FMT_SIZE_T(midpart) "%" midpart "u"
#  endif
#endif

#ifndef UNUSED_P
#  define UNUSED_P(p) (void)p
#endif

/* 注意：开始如果您在您的环境中将这些默认值修补为更大的非攻击XML负载值，请使用libexpat提交错误报告。非常感谢。
*/
#define EXPAT_BILLION_LAUGHS_ATTACK_PROTECTION_MAXIMUM_AMPLIFICATION_DEFAULT   \
  100.0f
#define EXPAT_BILLION_LAUGHS_ATTACK_PROTECTION_ACTIVATION_THRESHOLD_DEFAULT    \
  8388608 // 8米B，2^23
/* NOTE END */

#include "expat.h" // 所以我们可以使用下面的XML_Parser类型

#ifdef __cplusplus
extern "C" {
#endif

void _INTERNAL_trim_to_complete_utf8_characters(const char *from,
                                                const char **fromLimRef);

#if defined(XML_DTD)
unsigned long long testingAccountingGetCountBytesDirect(XML_Parser parser);
unsigned long long testingAccountingGetCountBytesIndirect(XML_Parser parser);
const char *unsignedCharToPrintable(unsigned char c);
#endif

#ifdef __cplusplus
}
#endif

