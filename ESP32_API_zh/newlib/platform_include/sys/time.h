#pragma once
/* Newlib系统/时间。h定义__CYGWIN__和__rtems__的timerisset、timerclear、timercmp、timeradd和timersub宏。我们也希望在IDF中定义这些宏。由于我们希望在修补的newlib版本可用之前使用未修改的newlib标头，因此在包含sys/time之前，请在此处临时定义__rtems__。由于sys/time中没有其他检查，因此选择__rtems__而不是__CYGWIN__。h，取决于__rtems__。

   此外，__rtems__define不会影响sys/time中包含的其他标头。h、 我们将它们提前包括在这里（ansi.h和sys/types.h）。
 */

#include <_ansi.h>
#include <sys/types.h>
#define __rtems__
#include_next <sys/time.h>
#undef __rtems__

