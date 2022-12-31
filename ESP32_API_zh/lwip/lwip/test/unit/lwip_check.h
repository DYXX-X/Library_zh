#ifndef LWIP_HDR_LWIP_CHECK_H
#define LWIP_HDR_LWIP_CHECK_H

/* 使用检查框架的lwIP单元测试的公共头文件*/

#include <config.h>
#include <check.h>
#include <stdlib.h>

#define FAIL_RET() do { fail(); return; } while(0)
#define EXPECT(x) fail_unless(x)
#define EXPECT_RET(x) do { fail_unless(x); if(!(x)) { return; }} while(0)
#define EXPECT_RETX(x, y) do { fail_unless(x); if(!(x)) { return y; }} while(0)
#define EXPECT_RETNULL(x) EXPECT_RETX(x, NULL)

typedef struct {
  TFun func;
  const char *name;
} testfunc;

#define TESTFUNC(x) {(x), "" # x "" }

/* 检查中修改的函数。h、 提供函数名*/
#define tcase_add_named_test(tc,tf) \
   _tcase_add_test((tc),(tf).func,(tf).name,0, 0, 0, 1)

/**返回测试套件的函数的typedef*/
typedef Suite* (suite_getter_fn)(void);

/**创建测试套件*/
Suite* create_suite(const char* name, testfunc *tests, size_t num_tests, SFun setup, SFun teardown);

#ifdef LWIP_UNITTESTS_LIB
int lwip_unittests_run(void)
#endif

/* 帮助函数*/
#define SKIP_POOL(x) (1 << x)
#define SKIP_HEAP    (1 << MEMP_MAX)
void lwip_check_ensure_no_alloc(unsigned int skip);

#endif /* LWIP_HDR_LWIP_CHECK_H */

