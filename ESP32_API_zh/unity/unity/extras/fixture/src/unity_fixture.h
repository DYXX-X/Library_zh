/* 版权所有（c）2010 James Grenning和对Unity项目的贡献===================================Unity项目-c测试框架版权所有（c）2007 Mike Karlesky，Mark VanderVoord，Greg Williams[根据MIT许可证发布。请参阅License.txt了解详细信息]
 * ========================================== */

#ifndef UNITY_FIXTURE_H_
#define UNITY_FIXTURE_H_

#include "unity.h"
#include "unity_internals.h"
#include "unity_fixture_malloc_overrides.h"
#include "unity_fixture_internals.h"

int UnityMain(int argc, const char* argv[], void (*runAllTests)(void));


#define TEST_GROUP(group)\
    static const char* TEST_GROUP_##group = #group

#define TEST_SETUP(group) void TEST_##group##_SETUP(void);\
    void TEST_##group##_SETUP(void)

#define TEST_TEAR_DOWN(group) void TEST_##group##_TEAR_DOWN(void);\
    void TEST_##group##_TEAR_DOWN(void)


#define TEST(group, name) \
    void TEST_##group##_##name##_(void);\
    void TEST_##group##_##name##_run(void);\
    void TEST_##group##_##name##_run(void)\
    {\
        UnityTestRunner(TEST_##group##_SETUP,\
            TEST_##group##_##name##_,\
            TEST_##group##_TEAR_DOWN,\
            "TEST(" #group ", " #name ")",\
            TEST_GROUP_##group, #name,\
            __FILE__, __LINE__);\
    }\
    void  TEST_##group##_##name##_(void)

#define IGNORE_TEST(group, name) \
    void TEST_##group##_##name##_(void);\
    void TEST_##group##_##name##_run(void);\
    void TEST_##group##_##name##_run(void)\
    {\
        UnityIgnoreTest("IGNORE_TEST(" #group ", " #name ")", TEST_GROUP_##group, #name);\
    }\
    void TEST_##group##_##name##_(void)

/* 每次测试都叫这个，了解小组跑步者*/
#define RUN_TEST_CASE(group, name) \
    { void TEST_##group##_##name##_run(void);\
      TEST_##group##_##name##_run(); }

/* 这位于每个测试文件的底部或单独的c文件中*/
#define TEST_GROUP_RUNNER(group)\
    void TEST_##group##_GROUP_RUNNER(void);\
    void TEST_##group##_GROUP_RUNNER(void)

/* 从main调用此*/
#define RUN_TEST_GROUP(group)\
    { void TEST_##group##_GROUP_RUNNER(void);\
      TEST_##group##_GROUP_RUNNER(); }

/* CppUT测试兼容性宏*/
#ifndef UNITY_EXCLUDE_CPPUTEST_ASSERTS
/* 设置指针，并在拆除后自动将其恢复为原来的值*/
#define UT_PTR_SET(ptr, newPointerValue)               UnityPointer_Set((void**)&(ptr), (void*)(newPointerValue), __LINE__)
#define TEST_ASSERT_POINTERS_EQUAL(expected, actual)   TEST_ASSERT_EQUAL_PTR((expected), (actual))
#define TEST_ASSERT_BYTES_EQUAL(expected, actual)      TEST_ASSERT_EQUAL_HEX8(0xff & (expected), 0xff & (actual))
#define FAIL(message)                                  TEST_FAIL_MESSAGE((message))
#define CHECK(condition)                               TEST_ASSERT_TRUE((condition))
#define LONGS_EQUAL(expected, actual)                  TEST_ASSERT_EQUAL_INT((expected), (actual))
#define STRCMP_EQUAL(expected, actual)                 TEST_ASSERT_EQUAL_STRING((expected), (actual))
#define DOUBLES_EQUAL(expected, actual, delta)         TEST_ASSERT_DOUBLE_WITHIN((delta), (expected), (actual))
#endif

/* 必须按照unity_fixture_malloc_overrides.h中的定义使用malloc替换进行编译*/
void UnityMalloc_MakeMallocFailAfterCount(int countdown);

#endif /* UNITY_FIXTURE_H_ */

