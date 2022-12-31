/*---------------------------------------------------------------------------/
/FatFs-FAT文件系统模块配置文件R0.09b（C）ChaN，2013/-----------------------------------------------------------------------------///注意！不要忘记在对/配置选项进行任何更改后清理项目/
/----------------------------------------------------------------------------*/
#ifndef _FFCONF
#define _FFCONF 82786	/* 修订ID*/

#include "tusb_config.h"

/*---------------------------------------------------------------------------/
/功能和缓冲区配置
/----------------------------------------------------------------------------*/

#define	_FS_TINY		0	/* 0：正常或1：微小*/
/* 当_FS_TINY设置为1时，FatFs使用文件系统/对象中的扇区缓冲区，而不是单个文件对象中用于文件/数据传输的扇区缓冲。这减少了每个文件对象512字节的内存消耗。*/


#define _FS_READONLY	0	/* 0：读/写或1：只读*/
/* 将_FS_READONLY设置为1定义只读配置。这将删除/写入函数、f_write、f_sync、f_unlink、f_mkdir、f_chmod、f-reame、/f_trupt和无用的f_getfree。*/


#define _FS_MINIMIZE	0	/* 0到3*/
/* _FS_MINIMIZE选项定义最小化级别以删除某些函数。//0：全功能。/1： f_stat、fgetfree、funlink、fmkdir、fchmod、ftruncate和frename/被删除。/2： 除了1之外，f_opendir和f_readdir也被删除。/3：除了2之外，f_lsek被删除。*/


#define	_USE_STRFUNC	0	/* 0：禁用或1-2：启用*/
/* 要启用字符串函数，请将_USE_STRFUNC设置为1或2。*/


#define	_USE_MKFS		0	/* 0：禁用或1：启用*/
/* 要启用f_mkfs功能，请将_USE_mkfs设置为1，并将_FS_READONLY设置为0*/


#define	_USE_FASTSEEK	0	/* 0：禁用或1：启用*/
/* 要启用快速寻道功能，请将_USE_FASTSEEK设置为1。*/


#define _USE_LABEL		1	/* 0：禁用或1：启用*/
/* 要启用卷标功能，请将_USE_LAVEL设置为1*/


#define	_USE_FORWARD	0	/* 0：禁用或1：启用*/
/* 要启用f_forward功能，请将_USE_forward设置为1，并将_FS_TINY设置为1。*/


/*---------------------------------------------------------------------------/
/区域设置和命名空间配置
/----------------------------------------------------------------------------*/

#define _CODE_PAGE	437
/* _CODE_PAGE指定要在目标系统上使用的OEM代码页。/代码页设置不正确可能导致文件打开失败。//932-日语Shift JIS（DBCS，OEM，Windows）/936-简体中文GBK（DBCS、OEM，Windows1258-越南（OEM，Windows）/437-美国（OEM）/720-阿拉伯语（OEM）/737-希腊语（OEM）/875-波罗的海语（OEM
*/


#define	_USE_LFN	1		/* 0到3*/
#define	_MAX_LFN	255		/* 处理的最大LFN长度（12到255）*/
/* _USE_LFN选项切换LFN支持。//0：禁用LFN功能_MAX_LFN和_LFN_UNICODE无效。/1： 使用BSS上的静态工作缓冲区启用LFN。始终不可重入。/2： 使用STACK上的动态工作缓冲区启用LFN。/3： 在HEAP上启用具有动态工作缓冲区的LFN。//LFN工作缓冲区占用（_MAX_LFN+1）2字节。要启用LFN，必须将/Unicode处理函数ff_convert（）和ff_wtoupper（）添加到项目中。当启用使用堆时，必须将内存控制函数/ff_memalloc（）和ff_memfree（）添加到项目中。*/


#define	_LFN_UNICODE	0	/* 0:ANSI/OEM或1:Unicode*/
/* 要将FatFsAPI上的字符代码集切换为Unicode，请启用LFN功能并将_LFN_Unicode设置为1。*/


#define _FS_RPATH		2	/* 0到2*/
/* _FS_RPATH选项配置相对路径功能。//0：禁用相对路径功能并删除相关功能。/1： 启用相对路径。f_chdrive（）和f_chdir（）可用。/2： f_getcwd（）除了1之外还可用。//请注意，f_readdir函数的输出受此选项的影响。*/


/*---------------------------------------------------------------------------/
/物理驱动器配置
/----------------------------------------------------------------------------*/

#define _VOLUMES	CFG_TUSB_HOST_DEVICE_MAX
/* 要使用的卷（逻辑驱动器）数。*/


#define	_MAX_SS		512		/* 512、1024、2048或4096*/
/* 要处理的最大扇区大小。/始终为存储卡和硬盘设置512，但板载闪存、软盘和光盘可能需要更大的值。/当_MAX_SS大于512时，它将FatFs配置为可变扇区大小/，并且必须将GET_sector_size命令实现到disk_ioctl函数。*/


#define	_MULTI_PARTITION	0	/* 0：单个分区，1：启用多个分区*/
/* 设置为0时，每个卷都绑定到相同的物理驱动器号，并且/它只能装载第一个主分区。当它设置为1时，每个卷/都绑定到VolToPart[]中列出的分区。*/


#define	_USE_ERASE	0	/* 0：禁用或1：启用*/
/* 要启用扇区擦除功能，请将_USE_erase设置为1。CTRL_erase_sector命令/应添加到disk_ioctl函数中。*/



/*---------------------------------------------------------------------------/
/系统配置
/----------------------------------------------------------------------------*/

#define _WORD_ACCESS	0	/* 0或1*/
/* 首先设置0，它始终与所有平台兼容。_WORD_ACCESS/选项定义用于FAT卷上的单词数据的访问方法。//0：逐字节访问。/1： Word访问。除非满足以下条件，否则不要选择此选项。//当内存上的字节顺序为大端或地址未对齐字/访问导致错误行为时，_word_access必须设置为0。/如果不是这样，也可以将该值设置为1以提高/性能和代码大小。
*/


/* 定义O/S上同步对象类型的头文件，如/windows。h、 ucos-ii。h和semphr。h、 必须在ff.h之前包含。*/

#define _FS_REENTRANT	0		/* 0：禁用或1：启用*/
#define _FS_TIMEOUT		1000	/* 超时周期（以时间刻度为单位）*/
#define	_SYNC_t			HANDLE	/* 同步对象的O/S相关类型。e、 g.手柄、OS_EVENT*、ID等。。*/

/* _FS_REENTRANT选项切换FatFs模块的可重入性（线程安全）。//0：禁用可重入性_SYNC_t和_FS_TIMEOUT无效。/1： 启用可重入性。此外，必须将用户提供的同步处理程序/ff_req_grant、ff_rel_grant、ff_del_syncobj和ff_cre_synccobj/function添加到项目中。*/


#define	_FS_LOCK	0	/* 0：禁用或>=1：启用*/
/* 要启用文件锁定控制功能，请将_FS_lock设置为1或更大。该值定义可以同时打开的文件数。*/


#endif /* _FFCONFIG */

