
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
#ifndef _ESP_PLATFORM_ERRNO_H_
#define _ESP_PLATFORM_ERRNO_H_

#include_next "errno.h"

//
// 可能定义了一些缺失的错误
//
#ifndef ESHUTDOWN
#define ESHUTDOWN      108  /* 传输终结点关闭后无法发送*/
#endif

#ifndef EAI_SOCKTYPE
#define	EAI_SOCKTYPE	10	/* 不支持ai_socktype*/
#endif

#ifndef EAI_AGAIN
#define	EAI_AGAIN	     2   /* 名称解析暂时失败*/
#endif

#ifndef EAI_BADFLAGS
#define	EAI_BADFLAGS	 3	 /* ai_flags的值无效*/
#endif

#endif // _ESP_PLATFORM_ERRNO_H_

