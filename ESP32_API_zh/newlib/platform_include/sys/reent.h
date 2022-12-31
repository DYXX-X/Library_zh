// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#include_next<sys/reent.h>

/* 此函数不是newlib API的一部分，它是在libc/stdio/local中定义的。h在避免__sinit的同时，没有很好的方法填充__cleanup成员，因此这里使用了extern声明。
 */
extern void _cleanup_r(struct _reent* r);

