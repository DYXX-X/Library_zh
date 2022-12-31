// 版权所有2017-2019 Espressif Systems（上海）私人有限公司
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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef uint32_t DWORD;

#define FF_DRV_NOT_USED 0xFF

#include "diskio.h"
#include "esp_err.h"

/**
 * 指向磁盘IO驱动程序函数的指针结构。
 *
 * 有关这些函数的详细信息，请参阅FatFs文档
 */
typedef struct {
    DSTATUS (*init) (unsigned char pdrv);    /*!< 磁盘初始化功能*/
    DSTATUS (*status) (unsigned char pdrv);  /*!< 磁盘状态检查功能*/
    DRESULT (*read) (unsigned char pdrv, unsigned char* buff, uint32_t sector, unsigned count);  /*!< 扇区读取功能*/
    DRESULT (*write) (unsigned char pdrv, const unsigned char* buff, uint32_t sector, unsigned count);   /*!< 扇区写入功能*/
    DRESULT (*ioctl) (unsigned char pdrv, unsigned char cmd, void* buff); /*!< 函数获取有关磁盘的信息并执行一些其他操作*/
} ff_diskio_impl_t;

/**
 * 为给定的驱动器号注册或注销diskio驱动程序。
 *
 * 当FATFS库为驱动程序编号pdrv调用disk_xxx函数之一时，将调用给定pdrv的discio_impl中的相应函数。
 *
 * @param pdrv 驱动器编号
 * @param discio_impl   指向带有diskio函数的ff_diskio_impl_t结构的指针，或NULL以注销并释放以前注册的驱动器
 */
void ff_diskio_register(BYTE pdrv, const ff_diskio_impl_t* discio_impl);

#define ff_diskio_unregister(pdrv_) ff_diskio_register(pdrv_, NULL)


/**
 * 获取下一个可用的驱动器号
 *
 * @param   out_pdrv            指向成功时要设置的字节的指针
 *
 * @return  成功时ESP_OK ESP_ERR_NOT_FOUND（如果连接了所有驱动器）
 */
esp_err_t ff_diskio_get_drive(BYTE* out_pdrv);


#ifdef __cplusplus
}
#endif

