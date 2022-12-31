#include_next <setjmp.h>
#include "esp_debug_helpers.h"

/*
 * 这是与unity一起使用的setjmp的中间层。
 */

/** 在longjmp（TEST_ABORT）之前插入回溯。
 *
 * 目前，我们只在测试被忽略或失败之前进行跳远。如果这在测试通过时也被调用，我们可能需要在调用回溯之前添加一些检查。
 */
#define longjmp(buf, val) do {esp_backtrace_print(100); longjmp(buf, val);} while(0)

