// 版权所有2016-2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#pragma once

#include <stdint.h>
#include <stdbool.h>

// 此文件包含在unity中。h通过unity_internals。h通过unity_config.h
// 它位于#ifdef__cplusplus/extern“C”块内，因此我们可以
// 此处仅使用C功能

// 定义帮助程序以从多个文件注册测试用例
#define UNITY_EXPAND2(a, b) a ## b
#define UNITY_EXPAND(a, b) UNITY_EXPAND2(a, b)
#define UNITY_TEST_UID(what) UNITY_EXPAND(what, __LINE__)

#define UNITY_TEST_REG_HELPER reg_helper ## UNITY_TEST_UID
#define UNITY_TEST_DESC_UID desc ## UNITY_TEST_UID


// 获取__VA_ARGS的计数__
#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define PP_RSEQ_N() 9,8,7,6,5,4,3,2,1,0

// 现在支持最多5个测试功能
#define FN_NAME_SET_1(a)                {#a}
#define FN_NAME_SET_2(a, b)             {#a, #b}
#define FN_NAME_SET_3(a, b, c)          {#a, #b, #c}
#define FN_NAME_SET_4(a, b, c, d)       {#a, #b, #c, #d}
#define FN_NAME_SET_5(a, b, c, d, e)    {#a, #b, #c, #d, #e}

#define FN_NAME_SET2(n) FN_NAME_SET_##n
#define FN_NAME_SET(n, ...) FN_NAME_SET2(n)(__VA_ARGS__)

#define UNITY_TEST_FN_SET(...)  \
    static test_func UNITY_TEST_UID(test_functions)[] = {__VA_ARGS__}; \
    static const char* UNITY_TEST_UID(test_fn_name)[] = FN_NAME_SET(PP_NARG(__VA_ARGS__), __VA_ARGS__)


typedef void (* test_func)(void);

typedef struct test_desc_t
{
    const char* name;
    const char* desc;
    test_func* fn;
    const char* file;
    int line;
    uint8_t test_fn_count;
    const char ** test_fn_name;
    struct test_desc_t* next;
} test_desc_t;

void unity_testcase_register(test_desc_t* desc);


/*  测试用例宏，a-la CATCH框架。第一个参数是自由形式的描述，第二个参数是（按照惯例）标识符列表，每个标识符都在方括号中。标识符用于对相关测试或具有特定属性的测试进行分组。使用方式：

    TEST_CASE（“Frobnicator forbonates”，“[Frobnicator][rom]”）｛//测试到这里｝
*/

#define TEST_CASE(name_, desc_) \
    static void UNITY_TEST_UID(test_func_) (void); \
    static void __attribute__((constructor)) UNITY_TEST_UID(test_reg_helper_) (void) \
    { \
        static test_func test_fn_[] = {&UNITY_TEST_UID(test_func_)}; \
        static test_desc_t UNITY_TEST_UID(test_desc_) = { \
            .name = name_, \
            .desc = desc_, \
            .fn = test_fn_, \
            .file = __FILE__, \
            .line = __LINE__, \
            .test_fn_count = 1, \
            .test_fn_name = NULL, \
            .next = NULL \
        }; \
        unity_testcase_register( & UNITY_TEST_UID(test_desc_) ); \
    }\
    static void UNITY_TEST_UID(test_func_) (void)


/*
 * 多阶段测试用例将处理测试步骤被DUT重置分开的情况。e、 g：我们想在SW重置、WDT重置或深度睡眠重置后验证某些功能。
 *
 * 第一个参数是自由形式的描述，第二个参数是（按照惯例）标识符列表，每个标识符都在方括号中。随后的参数是由reset分隔的测试函数名称。e、 g:TEST_CASE_MULTIPLE_STAGES（“在深度睡眠后运行浅睡眠”，“[sleep]”，goto_deepsleep，light_sleep_after_deep_sleep_wakeup）；
 * */

#define TEST_CASE_MULTIPLE_STAGES(name_, desc_, ...) \
    UNITY_TEST_FN_SET(__VA_ARGS__); \
    static void __attribute__((constructor)) UNITY_TEST_UID(test_reg_helper_) (void) \
    { \
        static test_desc_t UNITY_TEST_UID(test_desc_) = { \
            .name = name_, \
            .desc = desc_"[multi_stage]", \
            .fn = UNITY_TEST_UID(test_functions), \
            .file = __FILE__, \
            .line = __LINE__, \
            .test_fn_count = PP_NARG(__VA_ARGS__), \
            .test_fn_name = UNITY_TEST_UID(test_fn_name), \
            .next = NULL \
        }; \
        unity_testcase_register( & UNITY_TEST_UID(test_desc_) ); \
    }



/*
 * 第一个参数是自由形式的描述，第二个参数是（按照惯例）标识符列表，每个标识符都在方括号中。随后的参数是不同DUT的测试函数名称，例如：test_CASE_MULTIPLE_DEVICES（“master and slave spi”，“[spi][test_env=UT_T2_1]”，master_test，slave_test）；
 * */

#define TEST_CASE_MULTIPLE_DEVICES(name_, desc_, ...) \
    UNITY_TEST_FN_SET(__VA_ARGS__); \
    static void __attribute__((constructor)) UNITY_TEST_UID(test_reg_helper_) (void) \
    { \
        static test_desc_t UNITY_TEST_UID(test_desc_) = { \
            .name = name_, \
            .desc = desc_"[multi_device]", \
            .fn = UNITY_TEST_UID(test_functions), \
            .file = __FILE__, \
            .line = __LINE__, \
            .test_fn_count = PP_NARG(__VA_ARGS__), \
            .test_fn_name = UNITY_TEST_UID(test_fn_name), \
            .next = NULL \
        }; \
        unity_testcase_register( & UNITY_TEST_UID(test_desc_) ); \
    }

/**
 * 注意：上述test_desc_t字段的初始化必须按照与结构中声明字段的顺序完全相同的顺序进行。否则，初始化器在C++中无效（它不支持指定的初始化器）。G++可以解析语法，但字段名被视为注释，不影响初始化顺序。还要确保所有字段都已初始化。
 */

void unity_run_test_by_name(const char *name);

void unity_run_tests_by_tag(const char *tag, bool invert);

void unity_run_all_tests(void);

void unity_run_menu(void);

#include "sdkconfig.h" //获取IDF_TARGET_xxx

#define CONFIG_IDF_TARGET_NA   0

/*
 * 此宏用于禁用那些暂时无法构建或运行（需要更新或运行）的测试及其被调用方。
 *
 * 用法：```#if！TEMPORARY_DISABLED_FOR_TARGETS（ESP32S2，ESP32S2）TEST_CASE（“仅适用于esp32”，“”）｛｝#endif```
 */
#define TEMPORARY_DISABLED_FOR_TARGETS(...)    (_UNITY_DFT_10(__VA_ARGS__, NA, NA, NA, NA, NA, NA, NA, NA, NA))

/*
 * 此宏用于禁用那些完全不可能在特定目标上运行的测试及其被调用方。用法与TEMPORARY_DISABLED_FOR_TARGETS相同。
 */
#define DISABLED_FOR_TARGETS(...)    TEMPORARY_DISABLED_FOR_TARGETS(__VA_ARGS__)

#define _UNITY_DFT_10(TARGET, ...)  (CONFIG_IDF_TARGET_##TARGET || _UNITY_DFT_9(__VA_ARGS__))
#define _UNITY_DFT_9(TARGET, ...)   (CONFIG_IDF_TARGET_##TARGET || _UNITY_DFT_8(__VA_ARGS__))
#define _UNITY_DFT_8(TARGET, ...)   (CONFIG_IDF_TARGET_##TARGET || _UNITY_DFT_7(__VA_ARGS__))
#define _UNITY_DFT_7(TARGET, ...)   (CONFIG_IDF_TARGET_##TARGET || _UNITY_DFT_6(__VA_ARGS__))
#define _UNITY_DFT_6(TARGET, ...)   (CONFIG_IDF_TARGET_##TARGET || _UNITY_DFT_5(__VA_ARGS__))
#define _UNITY_DFT_5(TARGET, ...)   (CONFIG_IDF_TARGET_##TARGET || _UNITY_DFT_4(__VA_ARGS__))
#define _UNITY_DFT_4(TARGET, ...)   (CONFIG_IDF_TARGET_##TARGET || _UNITY_DFT_3(__VA_ARGS__))
#define _UNITY_DFT_3(TARGET, ...)   (CONFIG_IDF_TARGET_##TARGET || _UNITY_DFT_2(__VA_ARGS__))
#define _UNITY_DFT_2(TARGET, ...)   (CONFIG_IDF_TARGET_##TARGET || _UNITY_DFT_1(__VA_ARGS__))
#define _UNITY_DFT_1(TARGET, ...)   (CONFIG_IDF_TARGET_##TARGET)

