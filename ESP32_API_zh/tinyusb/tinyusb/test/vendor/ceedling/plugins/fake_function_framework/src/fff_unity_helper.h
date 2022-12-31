#ifndef fff_unity_helper_H
#define fff_unity_helper_H

/*
    Unity的FFF助手宏。
*/

/*
    如果未按预期次数调用函数，则失败。
*/
#define TEST_ASSERT_CALLED_TIMES(times_, function_)                         \
    TEST_ASSERT_EQUAL_MESSAGE(times_,                                       \
        function_ ## _fake.call_count,                                      \
        "Function " #function_ " called the incorrect number of times.")
/*
    如果函数未被精确调用一次，则失败。
*/
#define TEST_ASSERT_CALLED(function_) TEST_ASSERT_CALLED_TIMES(1, function_)

/*
    如果函数被调用1次或多次，则失败。
*/
#define TEST_ASSERT_NOT_CALLED(function_) TEST_ASSERT_CALLED_TIMES(0, function_)

/*
    如果未按此特定顺序调用函数，则失败。
*/
#define TEST_ASSERT_CALLED_IN_ORDER(order_, function_)                      \
    TEST_ASSERT_EQUAL_PTR_MESSAGE((void *) function_,                       \
        fff.call_history[order_],                                           \
        "Function " #function_ " not called in order " #order_ )

#endif
