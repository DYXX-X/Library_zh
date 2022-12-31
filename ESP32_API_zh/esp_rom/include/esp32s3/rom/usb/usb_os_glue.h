// 版权所有2019-2020 Espressif Systems（上海）私人有限公司
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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef void(*usb_osglue_intdisena_routine_t)(void);
typedef int(*usb_osglue_wait_routine_t)(int delay_us);

typedef struct {
    /* 禁用USB中断*/
    usb_osglue_intdisena_routine_t int_dis_proc;
    /* 启用USB中断*/
    usb_osglue_intdisena_routine_t int_ena_proc;
    /* 等待设定量的uS。返回实际等待的金额。如果delay_us为0，只需屈服。*/
    usb_osglue_wait_routine_t wait_proc;
} usb_osglue_data_t;

extern usb_osglue_data_t s_usb_osglue;

#ifdef __cplusplus
}
#endif

