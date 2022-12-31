/* “检查”库的微型重新实现。

   这是为了支持足够的检查来运行Expat测试。此界面完全基于所使用的检查库部分。

   This is *source* 兼容，但不需要*链接*兼容。__ __ __ __ ___ \\//__ __ __ | | __/__ \\/|'__ \/_ ` | __ | __//\ |）|（_||_\___/__/__/\.__/\__，_|\__|_|XML解析器

   版权所有（c）2004-2006 Fred L.Drake，Jr<fdrake@users.sourceforge.net>版权所有（c）2006-2012 Karl Waclawek<karl@waclawek.net>版权所有（c）2016-2017 Sebastian Pipping<sebastian@pipping.org>根据MIT许可证获得许可：

   特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：

   上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。

   THE  SOFTWARE  IS  PROVIDED  "AS  IS",  WITHOUT  WARRANTY  OF  ANY  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifdef __cplusplus
extern "C" {
#endif

#define CK_NOFORK 0
#define CK_FORK 1

#define CK_SILENT 0
#define CK_NORMAL 1
#define CK_VERBOSE 2

/* 针对Microsoft编译器和Tru64 Unix系统的解决方案，其中C编译器有一个工作__func_，但C++编译器只有一个工作的__FUNCTION_。这可以在configure中修复。但现在不值得。*/
#if defined(_MSC_VER) || (defined(__osf__) && defined(__cplusplus))
#  define __func__ __FUNCTION__
#endif

#define START_TEST(testname)                                                   \
  static void testname(void) {                                                 \
    _check_set_test_info(__func__, __FILE__, __LINE__);                        \
    {
#define END_TEST                                                               \
  }                                                                            \
  }

#define fail(msg) _fail_unless(0, __FILE__, __LINE__, msg)

typedef void (*tcase_setup_function)(void);
typedef void (*tcase_teardown_function)(void);
typedef void (*tcase_test_function)(void);

typedef struct SRunner SRunner;
typedef struct Suite Suite;
typedef struct TCase TCase;

struct SRunner {
  Suite *suite;
  int nchecks;
  int nfailures;
};

struct Suite {
  const char *name;
  TCase *tests;
};

struct TCase {
  const char *name;
  tcase_setup_function setup;
  tcase_teardown_function teardown;
  tcase_test_function *tests;
  int ntests;
  int allocated;
  TCase *next_tcase;
};

/* 内部助手。*/
void _check_set_test_info(char const *function, char const *filename,
                          int lineno);

/*
 * 实际实现的原型。
 */

void _fail_unless(int condition, const char *file, int line, const char *msg);
Suite *suite_create(const char *name);
TCase *tcase_create(const char *name);
void suite_add_tcase(Suite *suite, TCase *tc);
void tcase_add_checked_fixture(TCase *, tcase_setup_function,
                               tcase_teardown_function);
void tcase_add_test(TCase *tc, tcase_test_function test);
SRunner *srunner_create(Suite *suite);
void srunner_run_all(SRunner *runner, int verbosity);
int srunner_ntests_failed(SRunner *runner);
void srunner_free(SRunner *runner);

#ifdef __cplusplus
}
#endif

