/*
 * 测试运行程序.h
 *
 *  创建日期：2013年6月19日作者：peter
 */

/*
文件mysuite.c:

套房（mysuite）

静态空隙设置（测试*t）｛｝

静态孔隙拆卸（测试*t）｛｝

TEST（mytest）｛printf（“mytest立即运行..\n”）；返回0；｝测试结束（_E）

套件测试（mysuite）地址测试（mytest）套件结束（mysuie）



文件mysuite2.c：

套房（我的套房2）

静态空隙设置（测试*t）｛｝

静态孔隙拆卸（测试*t）｛｝

TEST（mytest2a）｛printf（“mytest2a现在运行..\n”）；返回0；｝测试结束（_E）

TEST（mytest2b）｛printf（“mytest2b现在运行..\n”）；返回0；｝测试结束（_E）

套件测试（mysuite2）ADD_TEST（mytest2a）ADD_TEST（mytest2b）套件结束（mysuite 2）

其他文件.c:

void add_suites（）｛add_SUITE（mysuite）；add_SUITE（mysuite2）；｝
 */

#ifndef TESTRUNNER_H_
#define TESTRUNNER_H_

#define TEST_RES_OK   0
#define TEST_RES_FAIL -1
#define TEST_RES_ASSERT -2

#define ERREXIT() if (get_abort_on_error()) abort(); else inc_error_count()

struct test_s;

typedef int (*test_f)(struct test_s *t);

typedef struct test_s {
  test_f f;
  char name[256];
  void *data;
  void (*setup)(struct test_s *t);
  void (*teardown)(struct test_s *t);
  struct test_s *_next;
  unsigned char test_result;
} test;

typedef struct test_res_s {
  char name[256];
  struct test_res_s *_next;
} test_res;

#define TEST_CHECK(x) if (!(x)) { \
  printf("  TEST FAIL %s:%d\n", __FILE__, __LINE__); \
  goto __fail_stop; \
}
#define TEST_CHECK_EQ(x, y) if ((x) != (y)) { \
  printf("  TEST FAIL %s:%d, %d != %d\n", __FILE__, __LINE__, (int)(x), (int)(y)); \
  goto __fail_stop; \
}
#define TEST_CHECK_NEQ(x, y) if ((x) == (y)) { \
  printf("  TEST FAIL %s:%d, %d == %d\n", __FILE__, __LINE__, (int)(x), (int)(y)); \
  goto __fail_stop; \
}
#define TEST_CHECK_GT(x, y) if ((x) <= (y)) { \
  printf("  TEST FAIL %s:%d, %d <= %d\n", __FILE__, __LINE__, (int)(x), (int)(y)); \
  goto __fail_stop; \
}
#define TEST_CHECK_LT(x, y) if ((x) >= (y)) { \
  printf("  TEST FAIL %s:%d, %d >= %d\n", __FILE__, __LINE__, (int)(x), (int)(y)); \
  goto __fail_stop; \
}
#define TEST_CHECK_GE(x, y) if ((x) < (y)) { \
  printf("  TEST FAIL %s:%d, %d < %d\n", __FILE__, __LINE__, (int)(x), (int)(y)); \
  goto __fail_stop; \
}
#define TEST_CHECK_LE(x, y) if ((x) > (y)) { \
  printf("  TEST FAIL %s:%d, %d > %d\n", __FILE__, __LINE__, (int)(x), (int)(y)); \
  goto __fail_stop; \
}
#define TEST_ASSERT(x) if (!(x)) { \
  printf("  TEST ASSERT %s:%d\n", __FILE__, __LINE__); \
  goto __fail_assert; \
}

#define DBGT(...) printf(__VA_ARGS__)

#define str(s) #s

#define SUITE(sui)

#define SUITE_TESTS(sui) \
  void _add_suite_tests_##sui(void) {

#define SUITE_END(sui) \
  }

#define ADD_TEST(tf) \
  _add_test(__test_##tf, str(tf), setup, teardown, 0);

#define ADD_TEST_NON_DEFAULT(tf) \
  _add_test(__test_##tf, str(tf), setup, teardown, 1);

#define ADD_SUITE(sui) \
  extern void _add_suite_tests_##sui(void); \
  _add_suite_tests_##sui();

#define TEST(tf) \
  static int __test_##tf(struct test_s *t) { do

#define TEST_END \
  while(0); \
  __fail_stop: return TEST_RES_FAIL; \
  __fail_assert: return TEST_RES_ASSERT; \
  }

int set_abort_on_error(int val);
int get_abort_on_error(void);
int get_error_count(void);
void inc_error_count(void);

void add_suites(void);
void test_init(void (*on_stop)(test *t));
// 如果所有测试都正常，则返回0；如果任何测试都失败，则返回-1；如果不好，则返回-2
int run_tests(int argc, char **args);
void _add_suite(const char *suite_name);
void _add_test(test_f f, char *name, void (*setup)(test *t), void (*teardown)(test *t), int non_default);

#endif /* TESTRUNNER_H_ */

