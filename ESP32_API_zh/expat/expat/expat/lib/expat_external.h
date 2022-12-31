/*
                            ____ __ ___ \\/__ __ __ | | _/_ \\/|'_ \/_ ` | __ | | __//\ | | _）|（_ | | | _ \ ___//\ \.__/\ __，_ | \ __ | | | | __ | XML解析器

   版权所有（c）1997-2000 Thai Open Source Software Center Ltd版权所有（c）2000 Clark Cooper<coopercc@users.sourceforge.net>版权所有（c）2000-2004 Fred L.Drake，Jr<fdrake@users.sourceforge.net>版权所有（c）2001-2002 Greg Stein<gstein@users.sourceforge.net>版权所有（c）2002-2006 Karl Waclawek<karl@waclawek.net>版权所有（c）2016 Cristian Rodríguez<crrodriguez@opensuse.org>版权所有（c）2016-2019 Sebastian Pipping<sebastian@pipping.org>版权所有（c）2017 Rhodori James<rhodri@wildebeest.org.uk>版权所有（c）2018 Yury Gribov<tetra2005@gmail.com>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef Expat_External_INCLUDED
#define Expat_External_INCLUDED 1

/* 外部API定义*/

/* Expat非常努力地定义API边界。定义了两个宏来控制此边界；每一个都可以在包含这个头之前定义，以实现一些不同的行为，但这样做并不建议或经常测试。

   XMLCALL-用于“库边界”上所有调用的调用约定。这将默认为cdecl，并非常努力地告诉编译器这是我们想要的。

   XMLIMPORT-需要注意的是，函数要从动态加载的库（.dll、.so或.sl，取决于您的平台）导入。

   XMLCALL宏是在Expat 1.95.7中添加的。唯一期望在客户端代码中直接有用的是XMLCALL。

   注意，至少在某些Unix版本上，Expat库必须使用cdecl调用约定作为默认值进行编译，因为系统标头可能采用cdecl约定。
*/
#ifndef XMLCALL
#  if defined(_MSC_VER)
#    define XMLCALL __cdecl
#  elif defined(__GNUC__) && defined(__i386) && ! defined(__INTEL_COMPILER)
#    define XMLCALL __attribute__((cdecl))
#  else
/* 对于使用此定义并支持多个调用约定的任何平台，如果可能，我们需要扩展此定义以声明该平台上使用的约定。

   如果您的平台是这种情况，请提交一份错误报告，说明如何通过C预处理器识别您的平台，以及如何指定与平台的malloc（）实现相同的调用约定。
*/
#    define XMLCALL
#  endif
#endif /* 未定义XMLCALL*/

#if ! defined(XML_STATIC) && ! defined(XMLIMPORT)
#  ifndef XML_BUILDING_EXPAT
/* 从应用程序使用Expat*/

#    if defined(_MSC_EXTENSIONS) && ! defined(__BEOS__) && ! defined(__CYGWIN__)
#      define XMLIMPORT __declspec(dllimport)
#    endif

#  endif
#endif /* 未定义XML_STATIC*/

#ifndef XML_ENABLE_VISIBILITY
#  define XML_ENABLE_VISIBILITY 0
#endif

#if ! defined(XMLIMPORT) && XML_ENABLE_VISIBILITY
#  define XMLIMPORT __attribute__((visibility("default")))
#endif

/* 如果我们没有在上面定义它，请定义它：*/
#ifndef XMLIMPORT
#  define XMLIMPORT
#endif

#if defined(__GNUC__)                                                          \
    && (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 96))
#  define XML_ATTR_MALLOC __attribute__((__malloc__))
#else
#  define XML_ATTR_MALLOC
#endif

#if defined(__GNUC__)                                                          \
    && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
#  define XML_ATTR_ALLOC_SIZE(x) __attribute__((__alloc_size__(x)))
#else
#  define XML_ATTR_ALLOC_SIZE(x)
#endif

#define XMLPARSEAPI(type) XMLIMPORT type XMLCALL

#ifdef __cplusplus
extern "C" {
#endif

#ifdef XML_UNICODE_WCHAR_T
#  ifndef XML_UNICODE
#    define XML_UNICODE
#  endif
#  if defined(__SIZEOF_WCHAR_T__) && (__SIZEOF_WCHAR_T__ != 2)
#    error "sizeof(wchar_t) != 2; Need -fshort-wchar for both Expat and libc"
#  endif
#endif

#ifdef XML_UNICODE /* 信息采用UTF-16编码。*/
#  ifdef XML_UNICODE_WCHAR_T
typedef wchar_t XML_Char;
typedef wchar_t XML_LChar;
#  else
typedef unsigned short XML_Char;
typedef char XML_LChar;
#  endif /* XML_UNICODE_WCHAR_T */
#else    /* 信息是UTF-8编码的。*/
typedef char XML_Char;
typedef char XML_LChar;
#endif   /* XML_UNICODE */

#ifdef XML_LARGE_SIZE /* 文件/流位置使用大整数。*/
typedef long long XML_Index;
typedef unsigned long long XML_Size;
#else
typedef long XML_Index;
typedef unsigned long XML_Size;
#endif /* XML_LARGE_SIZE */

#ifdef __cplusplus
}
#endif

#endif /* 非Expat_External_INCLUDED*/

