/* libcoap单元测试
 *
 * 版权所有（C）2012 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#include <CUnit/CUnit.h>

/** 断言常量指针实际==应为。报告失败，无其他操作。
 */
#define CU_ASSERT_PTR_EQUAL_C(actual, expected) \
  { CU_assertImplementation(((const void*)(actual) == (const void*)(expected)), __LINE__, ("CU_ASSERT_PTR_EQUAL(" #actual "," #expected ")"), __FILE__, "", CU_FALSE); }

CU_pSuite t_init_option_tests(void);

