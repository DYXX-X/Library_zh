/*----------------------------------------------------------------------------/
/FatFs-通用FAT文件系统模块R0.13c//------------------------------------------------------------------------------///版权所有（C）2018，ChaN，保留所有权利。//FatFs模块是一个开源软件。在满足以下条件的情况下，允许以/源和二进制形式重新分发和使用FatFs，无论是否进行修改：

/1.源代码的重新分发必须保留上述版权声明、/本条件和以下免责声明。//本软件由版权所有者和贡献者“按原样”提供，与本软件相关的任何保证均不承担。/版权所有者或贡献者对使用本软件造成的任何损害不承担责任/
/----------------------------------------------------------------------------*/


#ifndef FF_DEFINED
#define FF_DEFINED	86604	/* 修订ID*/

#ifdef __cplusplus
extern "C" {
#endif

#include "ffconf.h"		/* FatFs配置选项*/

#if FF_DEFINED != FFCONF_DEF
#error Wrong configuration file (ffconf.h).
#endif


/* 用于FatFs API的整数类型*/

#if defined(_WIN32)	/* 主要开发平台*/
#define FF_INTDEF 2
#include <windows.h>
typedef unsigned __int64 QWORD;
#elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__cplusplus)	/* C99或更高版本*/
#define FF_INTDEF 2
#include <stdint.h>
typedef unsigned int	UINT;	/* int必须是16位或32位*/
typedef unsigned char	BYTE;	/* 字符必须为8位*/
typedef uint16_t		WORD;	/* 16位无符号整数*/
typedef uint16_t		WCHAR;	/* 16位无符号整数*/
typedef uint32_t		DWORD;	/* 32位无符号整数*/
typedef uint64_t		QWORD;	/* 64位无符号整数*/
#else  	/* 早于C99*/
#define FF_INTDEF 1
typedef unsigned int	UINT;	/* int必须是16位或32位*/
typedef unsigned char	BYTE;	/* 字符必须为8位*/
typedef unsigned short	WORD;	/* 16位无符号整数*/
typedef unsigned short	WCHAR;	/* 16位无符号整数*/
typedef unsigned long	DWORD;	/* 32位无符号整数*/
#endif


/* 卷管理的定义*/

#if FF_MULTI_PARTITION		/* 多分区配置*/
typedef struct {
	BYTE pd;	/* 物理驱动器编号*/
	BYTE pt;	/* 分区：0：自动检测，1-4：强制分区）*/
} PARTITION;
extern PARTITION VolToPart[];	/* 卷-分区解析表*/
#endif

#if FF_STR_VOLUME_ID
#ifndef FF_VOLUME_STRS
extern const char* VolumeStr[FF_VOLUMES];	/* 用户拒绝卷ID*/
#endif
#endif



/* FatFs API上的路径名字符串类型*/

#ifndef _INC_TCHAR
#define _INC_TCHAR

#if FF_USE_LFN && FF_LFN_UNICODE == 1 	/* UTF-16编码中的Unicode*/
typedef WCHAR TCHAR;
#define _T(x) L ## x
#define _TEXT(x) L ## x
#elif FF_USE_LFN && FF_LFN_UNICODE == 2	/* UTF-8编码中的Unicode*/
typedef char TCHAR;
#define _T(x) u8 ## x
#define _TEXT(x) u8 ## x
#elif FF_USE_LFN && FF_LFN_UNICODE == 3	/* UTF-32编码中的Unicode*/
typedef DWORD TCHAR;
#define _T(x) U ## x
#define _TEXT(x) U ## x
#elif FF_USE_LFN && (FF_LFN_UNICODE < 0 || FF_LFN_UNICODE > 3)
#error Wrong FF_LFN_UNICODE setting
#else									/* SBCS/DBCS中的ANSI/OEM代码*/
typedef char TCHAR;
#define _T(x) x
#define _TEXT(x) x
#endif

#endif



/* 文件大小变量的类型*/

#if FF_FS_EXFAT
#if FF_INTDEF != 2
#error exFAT feature wants C99 or later
#endif
typedef QWORD FSIZE_t;
#else
typedef DWORD FSIZE_t;
#endif



/* 文件系统对象结构（FATFS）*/

typedef struct {
	BYTE	fs_type;		/* 文件系统类型（0:未装入）*/
	BYTE	pdrv;			/* 关联的物理驱动器*/
	BYTE	n_fats;			/* FAT数量（1或2）*/
	BYTE	wflag;			/* win[]标志（b0:脏）*/
	BYTE	fsi_flag;		/* FSINFO标志（b7：禁用，b0：脏）*/
	WORD	id;				/* 卷装载ID*/
	WORD	n_rootdir;		/* 根目录条目数（FAT12/16）*/
	WORD	csize;			/* 集群大小[扇区]*/
#if FF_MAX_SS != FF_MIN_SS
	WORD	ssize;			/* 扇区大小（512、1024、2048或4096）*/
#endif
#if FF_USE_LFN
	WCHAR*	lfnbuf;			/* LFN工作缓冲器*/
#endif
#if FF_FS_EXFAT
	BYTE*	dirbuf;			/* exFAT的目录条目块草稿行缓冲区*/
#endif
#if FF_FS_REENTRANT
	FF_SYNC_t	sobj;		/* 同步对象的标识符*/
#endif
#if !FF_FS_READONLY
	DWORD	last_clst;		/* 上次分配的群集*/
	DWORD	free_clst;		/* 可用群集数*/
#endif
#if FF_FS_RPATH
	DWORD	cdir;			/* 当前目录启动群集（0:root）*/
#if FF_FS_EXFAT
	DWORD	cdc_scl;		/* 包含目录启动群集（当cdir为0时无效）*/
	DWORD	cdc_size;		/* b31-b8：包含目录的大小，b7-b0：链状态*/
	DWORD	cdc_ofs;		/* 包含目录中的偏移量（当cdir为0时无效）*/
#endif
#endif
	DWORD	n_fatent;		/* FAT条目数（簇数+2）*/
	DWORD	fsize;			/* FAT的大小[扇区]*/
	DWORD	volbase;		/* 卷基础扇区*/
	DWORD	fatbase;		/* FAT基础扇区*/
	DWORD	dirbase;		/* 根目录基本扇区/群集*/
	DWORD	database;		/* 数据库部门*/
#if FF_FS_EXFAT
	DWORD	bitbase;		/* 分配位图基本扇区*/
#endif
	DWORD	winsect;		/* 获胜的当前行业[]*/
	BYTE	win[FF_MAX_SS];	/* 目录、FAT（和文件数据位于微型cfg）的磁盘访问窗口*/
} FATFS;



/* 对象ID和分配信息（FFOBJID）*/

typedef struct {
	FATFS*	fs;				/* 指向此对象的宿主卷的指针*/
	WORD	id;				/* 宿主卷装载ID*/
	BYTE	attr;			/* 对象属性*/
	BYTE	stat;			/* 对象链状态（b1-0：=0：不连续，=2：连续，=3：在此会话中碎片化，b2：子目录已拉伸）*/
	DWORD	sclust;			/* 对象数据启动群集（0:没有群集或根目录）*/
	FSIZE_t	objsize;		/* 对象大小（当sclust！=0时有效）*/
#if FF_FS_EXFAT
	DWORD	n_cont;			/* 第一个片段的大小-1（当stat==3时有效）*/
	DWORD	n_frag;			/* 最后一个片段的大小需要写入FAT（不为零时有效）*/
	DWORD	c_scl;			/* 包含目录启动群集（当sclust！=0时有效）*/
	DWORD	c_size;			/* b31-b8：包含目录的大小，b7-b0：链状态（当c_scl！=0时有效）*/
	DWORD	c_ofs;			/* 包含目录中的偏移量（当file对象和sclust！=0时有效）*/
#endif
#if FF_FS_LOCK
	UINT	lockid;			/* 文件锁ID源于1（文件信号量表的索引文件[]）*/
#endif
} FFOBJID;



/* 文件对象结构（FIL）*/

typedef struct {
	FFOBJID	obj;			/* 对象标识符（必须是检测无效对象指针的第一个成员）*/
	BYTE	flag;			/* 文件状态标志*/
	BYTE	err;			/* 中止标志（错误代码）*/
	FSIZE_t	fptr;			/* 文件读/写指针（文件打开时归零）*/
	DWORD	clust;			/* fpter的当前集群（fptr为0时无效）*/
	DWORD	sect;			/* buf[]中出现的扇区号（0:无效）*/
#if !FF_FS_READONLY
	DWORD	dir_sect;		/* 包含目录项的扇区号（exFAT中未使用）*/
	BYTE*	dir_ptr;		/* 指向win[]中目录项的指针（不在exFAT中使用）*/
#endif
#if FF_USE_FASTSEEK
	DWORD*	cltbl;			/* 指向群集链接映射表的指针（打开时为空，由应用程序设置）*/
#endif
#if !FF_FS_TINY
	BYTE	buf[FF_MAX_SS];	/* 文件专用数据读/写窗口*/
#endif
} FIL;



/* 目录对象结构（FF_DIR）*/

typedef struct {
	FFOBJID	obj;			/* 对象标识符*/
	DWORD	dptr;			/* 当前读/写偏移*/
	DWORD	clust;			/* 当前群集*/
	DWORD	sect;			/* 当前扇区（0:读取操作已终止）*/
	BYTE*	dir;			/* 指向win[]中目录项的指针*/
	BYTE	fn[12];			/* SFN（输入/输出）｛body[8]，ext[3]，status[1]｝*/
#if FF_USE_LFN
	DWORD	blk_ofs;		/* 正在处理的当前条目块的偏移量（0xFFFFFFFF：无效）*/
#endif
#if FF_USE_FIND
	const TCHAR* pat;		/* 指向名称匹配模式的指针*/
#endif
} FF_DIR;



/* 文件信息结构（FILINFO）*/

typedef struct {
	FSIZE_t	fsize;			/* 文件大小*/
	WORD	fdate;			/* 修改日期*/
	WORD	ftime;			/* 修改时间*/
	BYTE	fattrib;		/* 文件属性*/
#if FF_USE_LFN
	TCHAR	altname[FF_SFN_BUF + 1];/* 替代文件名*/
	TCHAR	fname[FF_LFN_BUF + 1];	/* 主文件名*/
#else
	TCHAR	fname[12 + 1];	/* 文件名*/
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
	FR_MKFS_ABORTED,		/* （14） f_mkfs（）因任何问题而中止*/
	FR_TIMEOUT,				/* （15） 无法在定义的时间段内获得访问卷的权限*/
	FR_LOCKED,				/* （16） 根据文件共享策略，操作被拒绝*/
	FR_NOT_ENOUGH_CORE,		/* （17） 无法分配LFN工作缓冲区*/
	FR_TOO_MANY_OPEN_FILES,	/* （18） 打开的文件数>FF_FS_LOCK*/
	FR_INVALID_PARAMETER	/* （19） 给定的参数无效*/
} FRESULT;



/*--------------------------------------------------------------*/
/* FatFs模块应用程序接口*/

FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				/* 打开或创建文件*/
FRESULT f_close (FIL* fp);											/* 关闭打开的文件对象*/
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			/* 从文件中读取数据*/
FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	/* 将数据写入文件*/
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);								/* 移动文件对象的文件指针*/
FRESULT f_truncate (FIL* fp);										/* 截断文件*/
FRESULT f_sync (FIL* fp);											/* 刷新写入文件的缓存数据*/
FRESULT f_opendir (FF_DIR* dp, const TCHAR* path);						/* 打开目录*/
FRESULT f_closedir (FF_DIR* dp);										/* 关闭打开的目录*/
FRESULT f_readdir (FF_DIR* dp, FILINFO* fno);							/* 读取目录项*/
FRESULT f_findfirst (FF_DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);	/* 查找第一个文件*/
FRESULT f_findnext (FF_DIR* dp, FILINFO* fno);							/* 查找下一个文件*/
FRESULT f_mkdir (const TCHAR* path);								/* 创建子目录*/
FRESULT f_unlink (const TCHAR* path);								/* 删除现有文件或目录*/
FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);	/* 重命名/移动文件或目录*/
FRESULT f_stat (const TCHAR* path, FILINFO* fno);					/* 获取文件状态*/
FRESULT f_chmod (const TCHAR* path, BYTE attr, BYTE mask);			/* 更改文件/dir的属性*/
FRESULT f_utime (const TCHAR* path, const FILINFO* fno);			/* 更改文件/dir的时间戳*/
FRESULT f_chdir (const TCHAR* path);								/* 更改当前目录*/
FRESULT f_chdrive (const TCHAR* path);								/* 更改当前驱动器*/
FRESULT f_getcwd (TCHAR* buff, UINT len);							/* 获取当前目录*/
FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);	/* 获取驱动器上可用群集的数量*/
FRESULT f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);	/* 获取卷标*/
FRESULT f_setlabel (const TCHAR* label);							/* 设置卷标*/
FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);	/* 将数据转发到流*/
FRESULT f_expand (FIL* fp, FSIZE_t fsz, BYTE opt);					/* 为文件分配一个连续块*/
FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);			/* 装载/卸载逻辑驱动器*/
FRESULT f_mkfs (const TCHAR* path, BYTE opt, DWORD au, void* work, UINT len);	/* 创建FAT卷*/
FRESULT f_fdisk (BYTE pdrv, const DWORD* szt, void* work);			/* 将物理驱动器划分为若干分区*/
FRESULT f_setcp (WORD cp);											/* 设置当前代码页*/
int f_putc (TCHAR c, FIL* fp);										/* 将字符放入文件*/
int f_puts (const TCHAR* str, FIL* cp);								/* 将字符串放入文件*/
int f_printf (FIL* fp, const TCHAR* str, ...);						/* 将格式化字符串放入文件*/
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);						/* 从文件中获取字符串*/

#define f_eof(fp) ((int)((fp)->fptr == (fp)->obj.objsize))
#define f_error(fp) ((fp)->err)
#define f_tell(fp) ((fp)->fptr)
#define f_size(fp) ((fp)->obj.objsize)
#define f_rewind(fp) f_lseek((fp), 0)
#define f_rewinddir(dp) f_readdir((dp), 0)
#define f_rmdir(path) f_unlink(path)
#define f_unmount(path) f_mount(0, path, 0)

#ifndef EOF
#define EOF (-1)
#endif




/*--------------------------------------------------------------*/
/* 其他用户定义的功能*/

/* RTC功能*/
#if !FF_FS_READONLY && !FF_FS_NORTC
DWORD get_fattime (void);
#endif

/* LFN支持功能*/
#if FF_USE_LFN >= 1						/* 代码转换（在unicode.c中定义）*/
WCHAR ff_oem2uni (WCHAR oem, WORD cp);	/* OEM代码到Unicode的转换*/
WCHAR ff_uni2oem (DWORD uni, WORD cp);	/* Unicode到OEM代码转换*/
DWORD ff_wtoupper (DWORD uni);			/* Unicode大写转换*/
#endif
#if FF_USE_LFN == 3						/* 动态内存分配*/
void* ff_memalloc (UINT msize);			/* 分配内存块*/
void ff_memfree (void* mblock);			/* 可用内存块*/
#endif

/* 同步功能*/
#if FF_FS_REENTRANT
int ff_cre_syncobj (BYTE vol, FF_SYNC_t* sobj);	/* 创建同步对象*/
int ff_req_grant (FF_SYNC_t sobj);		/* 锁定同步对象*/
void ff_rel_grant (FF_SYNC_t sobj);		/* 解锁同步对象*/
int ff_del_syncobj (FF_SYNC_t sobj);	/* 删除同步对象*/
#endif




/*--------------------------------------------------------------*/
/* 标志和偏移地址*/


/* 文件访问模式和打开方法标志（f_open的第三个参数）*/
#define	FA_READ				0x01
#define	FA_WRITE			0x02
#define	FA_OPEN_EXISTING	0x00
#define	FA_CREATE_NEW		0x04
#define	FA_CREATE_ALWAYS	0x08
#define	FA_OPEN_ALWAYS		0x10
#define	FA_OPEN_APPEND		0x30

/* 快速寻道控制（f_lsek的第二个参数）*/
#define CREATE_LINKMAP	((FSIZE_t)0 - 1)

/* 格式选项（f_mkfs的第二个参数）*/
#define FM_FAT		0x01
#define FM_FAT32	0x02
#define FM_EXFAT	0x04
#define FM_ANY		0x07
#define FM_SFD		0x08

/* 文件系统类型（FATFS.fs_type）*/
#define FS_FAT12	1
#define FS_FAT16	2
#define FS_FAT32	3
#define FS_EXFAT	4

/* 目录项的文件属性位（FILINFO.fattrib）*/
#define	AM_RDO	0x01	/* 只读*/
#define	AM_HID	0x02	/* 隐藏的*/
#define	AM_SYS	0x04	/* 系统*/
#define AM_DIR	0x10	/* 目录*/
#define AM_ARC	0x20	/* 档案文件*/


#ifdef __cplusplus
}
#endif

#endif /* FF_DEFINED */

