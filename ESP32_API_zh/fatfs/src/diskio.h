/*-----------------------------------------------------------------------/
/低级磁盘接口模型包括文件（C）ChaN，2014/
/-----------------------------------------------------------------------*/

#ifndef _DISKIO_DEFINED
#define _DISKIO_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

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


/*---------------------------------------*/
/* 磁盘控制功能的原型*/


DSTATUS disk_initialize (BYTE pdrv);
DSTATUS disk_status (BYTE pdrv);
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);


/* 磁盘状态位（DSTATUS）*/

#define STA_NOINIT		0x01	/* 驱动器未初始化*/
#define STA_NODISK		0x02	/* 驱动器中没有介质*/
#define STA_PROTECT		0x04	/* 写保护*/


/* disk_ioctrl函数的命令代码*/

/* 通用命令（由FatFs使用）*/
#define CTRL_SYNC			0	/* 完成挂起的写入过程（FF_FS_READONLY==0时需要）*/
#define GET_SECTOR_COUNT	1	/* 获取媒体大小（FF_USE_MKFS==1时需要）*/
#define GET_SECTOR_SIZE		2	/* 获取扇区大小（FF_MAX_SS！=FF_MIN_SS时需要）*/
#define GET_BLOCK_SIZE		3	/* 获取擦除块大小（FF_USE_MKFS==1时需要）*/
#define CTRL_TRIM			4	/* 通知设备扇区块上的数据不再使用（FF_USE_TRIM==1时需要）*/

/* 通用命令（FatF不使用）*/
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
#define ISDIO_READ			55	/* 从SD iSDIO寄存器读取数据*/
#define ISDIO_WRITE			56	/* 将数据写入SD iSDIO寄存器*/
#define ISDIO_MRITE			57	/* 屏蔽写入数据到SD iSDIO寄存器*/

/* ATA/CF特定ioctl命令*/
#define ATA_GET_REV			20	/* 获取F/W版本*/
#define ATA_GET_MODEL		21	/* 获取型号名称*/
#define ATA_GET_SN			22	/* 获取序列号*/

#ifdef __cplusplus
}
#endif

#endif

