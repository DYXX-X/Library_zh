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
#ifndef _ESP_PLATFORM_SYS_UN_H_
#define _ESP_PLATFORM_SYS_UN_H_

#define	AF_UNIX		1		/* 本地到主机（管道）*/

struct sockaddr_un {
            short                    sun_family;                /*AF_UNIX*/
            char                     sun_path[108];             /*路径名*/
};

#endif // _ESP_PLATFORM_SYS_UN_H_

