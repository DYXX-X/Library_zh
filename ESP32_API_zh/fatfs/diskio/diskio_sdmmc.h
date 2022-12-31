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

#include "sdmmc_cmd.h"
#include "driver/sdmmc_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 注册SD/MMC磁盘驱动程序
 *
 * @param pdrv  驱动器编号
 * @param card  指向描述卡的sdmmc_card_t结构的指针；应在调用f_mount之前初始化卡。
 */
void ff_diskio_register_sdmmc(unsigned char pdrv, sdmmc_card_t* card);

/**
 * @brief 获取卡对应的驾驶员号码
 *
 * @param card 获取驱动程序的卡
 * @return 卡上的驾驶员编号
 */
BYTE ff_diskio_get_pdrv_card(const sdmmc_card_t* card);

#ifdef __cplusplus
}
#endif

