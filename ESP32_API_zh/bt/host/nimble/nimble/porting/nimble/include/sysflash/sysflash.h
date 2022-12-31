/**
 * 此文件由Apache newt版本1.8.0-dev生成
 */

#ifndef H_MYNEWT_SYSFLASH_
#define H_MYNEWT_SYSFLASH_

#include "flash_map/flash_map.h"

/**
 * 此flash地图定义用于两个目的：1.定位包含真实flash地图定义的元区域。2.在无法从闪存读取元区域的情况下作为备用。
 */
extern const struct flash_area sysflash_map_dflt[6];

#define FLASH_AREA_BOOTLOADER                    0
#define FLASH_AREA_IMAGE_0                       1
#define FLASH_AREA_IMAGE_1                       2
#define FLASH_AREA_IMAGE_SCRATCH                 3
#define FLASH_AREA_REBOOT_LOG                    16
#define FLASH_AREA_NFFS                          17

#endif

