/*---------------------------------------------------------------------------/
/FatFs-FAT文件系统模块包括文件R0.09b（C）ChaN，2013/-----------------------------------------------------------------------------//FatFs-module是用于小型嵌入式系统的通用FAT文件系统。/这是一款免费软件，根据以下条款的许可政策开放用于教育、研究和商业/开发。//版权所有（C）2013，ChaN，保留所有权利。//FatFs模块是一个免费软件，没有任何担保。/无使用限制。在您的责任范围内，您可以将其用于/个人、非营利或商业产品。/源代码的重新分发必须保留上述版权声明/
/----------------------------------------------------------------------------*/

#ifndef _FATFS
#define _FATFS	82786	/* 修订ID*/

#ifdef __cplusplus
extern "C" {
#endif

#include "integer.h"	/* 基本整数类型*/
#include "ffconf.h"		/* FatFs配置选项*/
#include "tusb_config.h"

#if _FATFS != _FFCONF
#error Wrong configuration file (ffconf.h).
#endif



/* 卷管理的定义*/

#if _MULTI_PARTITION		/* 多分区配置*/
typedef struct {
	BYTE pd;	/* 物理驱动器编号*/
	BYTE pt;	/* 分区：0：自动检测，1-4：强制分区）*/
} PARTITION;
extern PARTITION VolToPart[];	/* 卷-分区解析表*/
#define LD2PD(vol) (VolToPart[vol].pd)	/* 获取物理驱动器号*/
#define LD2PT(vol) (VolToPart[vol].pt)	/* 获取分区索引*/

#else							/* 单分区配置*/
#define LD2PD(vol) (BYTE)(vol)	/* 每个逻辑驱动器都绑定到相同的物理驱动器号*/
#define LD2PT(vol) 0			/* 始终安装第一个分区或SFD*/

#endif



/* FatFs API上的路径名字符串类型*/

#if _LFN_UNICODE			/* Unicode字符串*/
#if !_USE_LFN
#error _LFN_UNICODE must be 0 in non-LFN cfg.
#endif
#ifndef _INC_TCHAR
typedef WCHAR TCHAR;
#define _T(x) L ## x
#define _TEXT(x) L ## x
#endif

#else						/* ANSI/OEM字符串*/
#ifndef _INC_TCHAR
typedef char TCHAR;
#define _T(x) x
#define _TEXT(x) x
#endif

#endif



/* 文件系统对象结构（FATFS）*/

typedef struct {
	BYTE	fs_type;		/* FAT子类型（0：未安装）*/
	BYTE	drv;			/* 物理驱动器编号*/
	BYTE	csize;			/* 每个集群的扇区数（1,2,4…128）*/
	BYTE	n_fats;			/* FAT副本数量（1,2）*/
	BYTE	wflag;			/* win[]脏标志（1：必须写回）*/
	BYTE	fsi_flag;		/* fsinfo脏标志（1：必须写回）*/
	WORD	id;				/* 文件系统装载ID*/
	WORD	n_rootdir;		/* 根目录条目数（FAT12/16）*/
#if _MAX_SS != 512
	WORD	ssize;			/* 每个扇区的字节数（512、1024、2048或4096）*/
#endif
#if _FS_REENTRANT
	_SYNC_t	sobj;			/* 同步对象的标识符*/
#endif
#if !_FS_READONLY
	DWORD	last_clust;		/* 上次分配的群集*/
	DWORD	free_clust;		/* 可用群集数*/
	DWORD	fsi_sector;		/* fsinfo扇区（FAT32）*/
#endif
#if _FS_RPATH
	DWORD	cdir;			/* 当前目录启动群集（0:root）*/
#endif
	DWORD	n_fatent;		/* FAT条目数（=簇数+2）*/
	DWORD	fsize;			/* 每个FAT的扇区*/
	DWORD	volbase;		/* 卷起始扇区*/
	DWORD	fatbase;		/* FAT启动扇区*/
	DWORD	dirbase;		/* 根目录起始扇区（FAT32:Cluster#）*/
	DWORD	database;		/* 数据启动扇区*/
	DWORD	winsect;		/* 获胜的当前行业[]*/
	BYTE	win[_MAX_SS];	/* 目录、FAT（和微型cfg上的数据）的磁盘访问窗口*/
} FATFS;



/* 文件对象结构（FIL）*/

typedef struct {
	FATFS*	fs;				/* 指向相关文件系统对象的指针（**不更改顺序**）*/
	WORD	id;				/* 所有者文件系统装载ID（**不更改顺序**）*/
	BYTE	flag;			/* 文件状态标志*/
	BYTE	pad1;
	DWORD	fptr;			/* 文件读/写指针（文件打开时为0）*/
	DWORD	fsize;			/* 文件大小*/
	DWORD	sclust;			/* 文件数据启动群集（0：无数据群集，当fsize为0时始终为0）*/
	DWORD	clust;			/* 当前fpter集群*/
	DWORD	dsect;			/* fpter当前数据扇区*/
#if !_FS_READONLY
	DWORD	dir_sect;		/* 包含目录项的扇区*/
	BYTE*	dir_ptr;		/* 指向窗口中目录项的指针*/
#endif
#if _USE_FASTSEEK
	DWORD*	cltbl;			/* 指向群集链接映射表的指针（文件打开时为空）*/
#endif
#if _FS_LOCK
	UINT	lockid;			/* 文件锁ID（文件信号量表的索引文件[]）*/
#endif
#if !_FS_TINY
	BYTE	buf[_MAX_SS];	/* 文件数据读/写缓冲区*/
#endif
} FIL;



/* 目录对象结构（DIR）*/

typedef struct {
	FATFS*	fs;				/* 指向所有者文件系统对象的指针（**不更改顺序**）*/
	WORD	id;				/* 所有者文件系统装载ID（**不更改顺序**）*/
	WORD	index;			/* 当前读/写索引编号*/
	DWORD	sclust;			/* 表启动群集（0:根目录）*/
	DWORD	clust;			/* 当前群集*/
	DWORD	sect;			/* 当前部门*/
	BYTE*	dir;			/* 指向win[]中当前SFN项的指针*/
	BYTE*	fn;				/* 指向SFN（输入/输出）｛文件[8]，文本[3]，状态[1]｝的指针*/
#if _USE_LFN
	WCHAR*	lfn;			/* 指向LFN工作缓冲区的指针*/
	WORD	lfn_idx;		/* 最后匹配的LFN索引编号（0xFFFF:无LFN）*/
#endif
} DIR;



/* 文件状态结构（FILINFO）*/

typedef struct {
	DWORD	fsize;			/* 文件大小*/
	WORD	fdate;			/* 上次修改日期*/
	WORD	ftime;			/* 上次修改时间*/
	BYTE	fattrib;		/* 属性*/
	TCHAR	fname[13];		/* 短文件名（8.3格式）*/
#if _USE_LFN
	TCHAR*	lfname;			/* 指向LFN缓冲区的指针*/
	UINT 	lfsize;			/* TCHAR中LFN缓冲区的大小*/
#endif
} FILINFO;



/* 文件函数返回代码（FRESULT）*/

typedef enum {
	FR_OK = 0,				/* （0）成功*/
	FR_DISK_ERR,			/* （1） 低级磁盘I/O层中发生硬错误*/
	FR_INT_ERR,				/* （2） 断言失败*/
	FR_NOT_READY,			/* （3） 物理驱动器无法工作*/
	FR_NO_FILE,				/* （4） 找不到文件*/
	FR_NO_PATH,				/* （5） 找不到路径*/
	FR_INVALID_NAME,		/* （6） 路径名格式无效*/
	FR_DENIED,				/* （7） 由于禁止访问或目录已满，访问被拒绝*/
	FR_EXIST,				/* （8） 由于禁止访问，访问被拒绝*/
	FR_INVALID_OBJECT,		/* （9） 文件/目录对象无效*/
	FR_WRITE_PROTECTED,		/* （10） 物理驱动器受写保护*/
	FR_INVALID_DRIVE,		/* （11） 逻辑驱动器号无效*/
	FR_NOT_ENABLED,			/* （12） 卷没有工作区*/
	FR_NO_FILESYSTEM,		/* （13） 没有有效的FAT卷*/
	FR_MKFS_ABORTED,		/* （14） f_mkfs（）由于任何参数错误而中止*/
	FR_TIMEOUT,				/* （15） 无法在定义的时间段内获得访问卷的权限*/
	FR_LOCKED,				/* （16） 根据文件共享策略，操作被拒绝*/
	FR_NOT_ENOUGH_CORE,		/* （17） 无法分配LFN工作缓冲区*/
	FR_TOO_MANY_OPEN_FILES,	/* （18） 打开的文件数>_FS_SHARE*/
	FR_INVALID_PARAMETER	/* （19） 给定的参数无效*/
} FRESULT;



/*--------------------------------------------------------------*/
/* FatFs模块应用程序接口*/

FRESULT f_mount (BYTE vol, FATFS* fs);								/* 装载/卸载逻辑驱动器*/
FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				/* 打开或创建文件*/
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			/* 从文件读取数据*/
FRESULT f_lseek (FIL* fp, DWORD ofs);								/* 移动文件对象的文件指针*/
FRESULT f_close (FIL* fp);											/* 关闭打开的文件对象*/
FRESULT f_opendir (DIR* dj, const TCHAR* path);						/* 打开现有目录*/
FRESULT f_readdir (DIR* dj, FILINFO* fno);							/* 读取目录项*/
FRESULT f_stat (const TCHAR* path, FILINFO* fno);					/* 获取文件状态*/
FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	/* 将数据写入文件*/
FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);	/* 获取驱动器上可用群集的数量*/
FRESULT f_truncate (FIL* fp);										/* 截断文件*/
FRESULT f_sync (FIL* fp);											/* 刷新写入文件的缓存数据*/
FRESULT f_unlink (const TCHAR* path);								/* 删除现有文件或目录*/
FRESULT	f_mkdir (const TCHAR* path);								/* 创建新目录*/
FRESULT f_chmod (const TCHAR* path, BYTE value, BYTE mask);			/* 更改文件/dir的属性*/
FRESULT f_utime (const TCHAR* path, const FILINFO* fno);			/* 更改文件/dir的时间戳*/
FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);	/* 重命名/移动文件或目录*/
FRESULT f_chdrive (BYTE drv);										/* 更改当前驱动器*/
BYTE    f_get_current_drive(void);
FRESULT f_chdir (const TCHAR* path);								/* 更改当前目录*/
FRESULT f_getcwd (TCHAR* buff, UINT len);							/* 获取当前目录*/
FRESULT	f_getlabel (const TCHAR* path, TCHAR* label, DWORD* sn);	/* 获取卷标*/
FRESULT	f_setlabel (const TCHAR* label);							/* 设置卷标*/
FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);	/* 将数据转发到流*/
FRESULT f_mkfs (BYTE vol, BYTE sfd, UINT au);						/* 在驱动器上创建文件系统*/
FRESULT	f_fdisk (BYTE pdrv, const DWORD szt[], void* work);			/* 将物理驱动器划分为若干分区*/
int f_putc (TCHAR c, FIL* fp);										/* 将字符放入文件*/
int f_puts (const TCHAR* str, FIL* cp);								/* 将字符串放入文件*/
int f_printf (FIL* fp, const TCHAR* str, ...);						/* 将格式化字符串放入文件*/
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);						/* 从文件中获取字符串*/

#define f_eof(fp) (((fp)->fptr == (fp)->fsize) ? 1 : 0)
#define f_error(fp) (((fp)->flag & FA__ERROR) ? 1 : 0)
#define f_tell(fp) ((fp)->fptr)
#define f_size(fp) ((fp)->fsize)

#ifndef EOF
#define EOF (-1)
#endif




/*--------------------------------------------------------------*/
/* 其他用户定义的功能*/

/* RTC功能*/
#if !_FS_READONLY
DWORD get_fattime (void);
#endif

/* Unicode支持函数*/
#if _USE_LFN							/* Unicode-OEM代码转换*/
WCHAR ff_convert (WCHAR chr, UINT dir);	/* OEM Unicode双向转换*/
WCHAR ff_wtoupper (WCHAR chr);			/* Unicode大写转换*/
#if _USE_LFN == 3						/* 记忆功能*/
void* ff_memalloc (UINT msize);			/* 分配内存块*/
void ff_memfree (void* mblock);			/* 可用内存块*/
#endif
#endif

/* 同步功能*/
#if _FS_REENTRANT
int ff_cre_syncobj (BYTE vol, _SYNC_t* sobj);	/* 创建同步对象*/
int ff_req_grant (_SYNC_t sobj);				/* 锁定同步对象*/
void ff_rel_grant (_SYNC_t sobj);				/* 解锁同步对象*/
int ff_del_syncobj (_SYNC_t sobj);				/* 删除同步对象*/
#endif




/*--------------------------------------------------------------*/
/* 标志和偏移地址*/


/* 文件访问控制和文件状态标志（FIL.flag）*/

#define	FA_READ				0x01
#define	FA_OPEN_EXISTING	0x00
#define FA__ERROR			0x80

#if !_FS_READONLY
#define	FA_WRITE			0x02
#define	FA_CREATE_NEW		0x04
#define	FA_CREATE_ALWAYS	0x08
#define	FA_OPEN_ALWAYS		0x10
#define FA__WRITTEN			0x20
#define FA__DIRTY			0x40
#endif


/* FAT子类型（FATFS.fs_type）*/

#define FS_FAT12	1
#define FS_FAT16	2
#define FS_FAT32	3


/* 目录项的文件属性位*/

#define	AM_RDO	0x01	/* 只读*/
#define	AM_HID	0x02	/* 隐藏的*/
#define	AM_SYS	0x04	/* 系统*/
#define	AM_VOL	0x08	/* 卷标签*/
#define AM_LFN	0x0F	/* LFN条目*/
#define AM_DIR	0x10	/* 目录*/
#define AM_ARC	0x20	/* 档案文件*/
#define AM_MASK	0x3F	/* 定义位掩码*/


/* 快速寻道功能*/
#define CREATE_LINKMAP	0xFFFFFFFF



/*--------------------------------*/
/* 多字节字访问宏*/

#if _WORD_ACCESS == 1	/* 启用FAT结构的字访问*/
#define	LD_WORD(ptr)		(WORD)(*(WORD*)(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(*(DWORD*)(BYTE*)(ptr))
#define	ST_WORD(ptr,val)	*(WORD*)(BYTE*)(ptr)=(WORD)(val)
#define	ST_DWORD(ptr,val)	*(DWORD*)(BYTE*)(ptr)=(DWORD)(val)
#else					/* 使用对FAT结构的逐字节访问*/
#define	LD_WORD(ptr)		(WORD)(((WORD)*((BYTE*)(ptr)+1)<<8)|(WORD)*(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(((DWORD)*((BYTE*)(ptr)+3)<<24)|((DWORD)*((BYTE*)(ptr)+2)<<16)|((WORD)*((BYTE*)(ptr)+1)<<8)|*(BYTE*)(ptr))
#define	ST_WORD(ptr,val)	*(BYTE*)(ptr)=(BYTE)(val); *((BYTE*)(ptr)+1)=(BYTE)((WORD)(val)>>8)
#define	ST_DWORD(ptr,val)	*(BYTE*)(ptr)=(BYTE)(val); *((BYTE*)(ptr)+1)=(BYTE)((WORD)(val)>>8); *((BYTE*)(ptr)+2)=(BYTE)((DWORD)(val)>>16); *((BYTE*)(ptr)+3)=(BYTE)((DWORD)(val)>>24)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _FATFS */

