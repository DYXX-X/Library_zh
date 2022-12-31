// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _DISKIO_WL_DEFINED
#define _DISKIO_WL_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

#include "wear_levelling.h"


/**
 * 寄存器spi闪存分区
 *
 * @param pdrv  驱动器编号
 * @param flash_handle  磨损调平隔板的手柄。
 */
esp_err_t ff_diskio_register_wl_partition(unsigned char pdrv, wl_handle_t flash_handle);
unsigned char ff_diskio_get_pdrv_wl(wl_handle_t flash_handle);
void ff_diskio_clear_pdrv_wl(wl_handle_t flash_handle);

#ifdef __cplusplus
}
#endif

#endif // _DISKIO_WL_DEFINED

