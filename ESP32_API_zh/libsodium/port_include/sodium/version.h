/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef sodium_version_H
#define sodium_version_H

#include <sodium/export.h>

/* 重要提示：由于我们不使用自动工具，因此如果我们更改子模块，这些版本不会自动更新。它们需要手动更改。
*/

#define SODIUM_VERSION_STRING "1.0.12-idf"

/* 注意：这些宏与整体版本不同，有关相关宏，请参见config.ac*/
#define SODIUM_LIBRARY_VERSION_MAJOR 9
#define SODIUM_LIBRARY_VERSION_MINOR 4

#ifdef __cplusplus
extern "C" {
#endif

SODIUM_EXPORT
const char *sodium_version_string(void);

SODIUM_EXPORT
int         sodium_library_version_major(void);

SODIUM_EXPORT
int         sodium_library_version_minor(void);

#ifdef __cplusplus
}
#endif

#endif

