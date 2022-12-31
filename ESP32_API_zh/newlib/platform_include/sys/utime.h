// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#ifndef _UTIME_H_
#define _UTIME_H_

#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

struct utimbuf {
    time_t actime;       // 存取时间
    time_t modtime;      // 修改时间
};

int utime(const char *path, const struct utimbuf *times);

#ifdef __cplusplus
};
#endif

#endif /* _UTIME_H_ */

