// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
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

#ifndef _DISKIO_RAWFLASH_DEFINED
#define _DISKIO_RAWFLASH_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_partition.h"

/**
 * 寄存器spi闪存分区
 *
 * @param pdrv  驱动器编号
 * @param part_handle  指向原始闪存分区的指针。
 */
esp_err_t ff_diskio_register_raw_partition(unsigned char pdrv, const esp_partition_t* part_handle);
unsigned char ff_diskio_get_pdrv_raw(const esp_partition_t* part_handle);

#ifdef __cplusplus
}
#endif

#endif // _DISKIO_RAWFLASH_DEFINED

