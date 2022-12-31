/*-----------------------------------------------------------------------
/低级磁盘接口模块包括文件（C）ChaN，2013
/-----------------------------------------------------------------------*/

#ifndef _DISKIO_DEFINED
#define _DISKIO_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

#define _USE_WRITE	1	/* 1： 启用disk_write功能*/
#define _USE_IOCTL	1	/* 1： 启用disk_ioctl功能*/

#include "integer.h"
#include <stdbool.h>

/* 磁盘功能状态*/
typedef BYTE	DSTATUS;

/* 磁盘功能结果*/
typedef enum {
	RES_OK = 0,		/* 0:成功*/
	RES_ERROR,		/* 1： R/W错误*/
	RES_WRPRT,		/* 2： 写保护*/
	RES_NOTRDY,		/* 3： 未准备就绪*/
	RES_PARERR		/* 4： 无效参数*/
} DRESULT;


/* 磁盘状态位（DSTATUS）*/
#define STA_NOINIT		0x01	/* 驱动器未初始化*/
#define STA_NODISK		0x02	/* 驱动器中没有介质*/
#define STA_PROTECT		0x04	/* 写保护*/


/* disk_ioctrl函数的命令代码*/

/* 通用命令（由FatFs使用）*/
#define CTRL_SYNC			0	/* 刷新磁盘缓存（用于写入功能）*/
#define GET_SECTOR_COUNT	1	/* 获取媒体大小（仅适用于f_mkfs（））*/
#define GET_SECTOR_SIZE		2	/* 获取扇区大小（对于多个扇区大小（_MAX_SS>=1024））*/
#define GET_BLOCK_SIZE		3	/* 获取擦除块大小（仅适用于f_mkfs（））*/
#define CTRL_ERASE_SECTOR	4	/* 强制擦除扇区块（仅限_USE_ERASE）*/

/* 通用命令（FatFs不使用）*/
#define CTRL_POWER			5	/* 获取/设置电源状态*/
#define CTRL_LOCK			6	/* 锁定/解锁介质移除*/
#define CTRL_EJECT			7	/* 弹出媒体*/
#define CTRL_FORMAT			8	/* 在媒体上创建物理格式*/

/* MMC/SDC特定ioctl命令*/
#define MMC_GET_TYPE		10	/* 获取卡类型*/
#define MMC_GET_CSD			11	/* 获取CSD*/
#define MMC_GET_CID			12	/* 获取CID*/
#define MMC_GET_OCR			13	/* 获取OCR*/
#define MMC_GET_SDSTAT		14	/* 获取SD状态*/

/* ATA/CF特定ioctl命令*/
#define ATA_GET_REV			20	/* 获取F/W版本*/
#define ATA_GET_MODEL		21	/* 获取型号名称*/
#define ATA_GET_SN			22	/* 获取序列号*/


/* MMC卡类型标志（MMC_GET_type）*/
#define CT_MMC		0x01		/* MMC第3版*/
#define CT_SD1		0x02		/* SD版本1*/
#define CT_SD2		0x04		/* SD版本2*/
#define CT_SDC		(CT_SD1|CT_SD2)	/* SD */
#define CT_BLOCK	0x08		/* 块寻址*/

/*---------------------------------------*/
/* 磁盘控制功能的原型*/

void diskio_init(void);
void disk_deinitialize ( BYTE pdrv );
DSTATUS disk_initialize (BYTE pdrv);
DSTATUS disk_status (BYTE pdrv);
DRESULT disk_read (BYTE pdrv, BYTE*buff, DWORD sector, BYTE count);
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, BYTE count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);

static inline bool disk_is_ready(BYTE pdrv);
static inline bool disk_is_ready(BYTE pdrv)
{
  return (pdrv < CFG_TUSB_HOST_DEVICE_MAX) &&
         ( (disk_status(pdrv) & (STA_NOINIT | STA_NODISK)) == 0 );
}


#ifdef __cplusplus
}
#endif

#endif

