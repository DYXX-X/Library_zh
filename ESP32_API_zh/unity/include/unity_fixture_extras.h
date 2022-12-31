// 版权所有2016-2021 Espressif Systems（Shanghai）Co.Ltd。
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

/* IDF对“Unity夹具”的特定添加。这个文件不需要直接包含，它被包含在unity中。h到unity_config.h。
 */

#pragma once

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(CONFIG_IDF_TARGET) || defined(CONFIG_IDF_TARGET_LINUX)
#define UNITY_MAYBE_EXIT(rc)  do { exit(rc); } while(0)
#else
#define UNITY_MAYBE_EXIT(rc)  do { (void) rc; } while(0)
#endif

/* 运行从app_main函数的一个函数“func_”调用的所有测试的简写。当有多个测试组时使用此选项。
 *
 * 例子：
 *
 *    #include“unity.h”#include“unity_fixture.h”
 *
 *    static_void run_all_tests（void）｛run_TEST_GROUP（group1）；//在另一个文件中定义的测试组，例如TEST_group1.c run_TEST-GROUP（GROUP 2）；//其他文件中定义了测试组，如TEST_group2.c｝
 *
 *    void app_main（void）｛UNITY_main_FUNC（run_all_tests）；｝
 */
#define UNITY_MAIN_FUNC(func_) do { \
    const char* argv[] = { "test", "-v" }; \
    const int argc = sizeof(argv)/sizeof(argv[0]); \
    int rc = UnityMain(argc, argv, func_); \
    printf("\nTests finished, rc=%d\n", rc); \
    UNITY_MAYBE_EXIT(rc); \
} while(0)

/* 当只有一个测试组并且在同一文件中定义时，从app_main函数运行测试组的简写。
 *
 * 例子：
 *
 *    #include“unity.h”#include“unity_fixture.h”
 *
 *    测试组（my_feature）；//还定义TEST_SETUP、TEST_TEARDOWN、TESTs、TEST_GROUP_RUNNER
 *
 *    void app_main（void）｛UNITY_main（my_feature）；｝
 */
#define UNITY_MAIN(group_) UNITY_MAIN_FUNC(TEST_ ## group_ ## _GROUP_RUNNER)

#ifdef __cplusplus
}
#endif

