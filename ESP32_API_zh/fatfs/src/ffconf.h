#include "sdkconfig.h"

/*---------------------------------------------------------------------------/
/FatFs功能配置
/---------------------------------------------------------------------------*/

#define FFCONF_DEF	86604	/* 修订ID*/

/*---------------------------------------------------------------------------/
/功能配置
/---------------------------------------------------------------------------*/

#define FF_FS_READONLY	0
/* 此选项切换只读配置。（0：读/写或1：只读）/只读配置也会删除编写API函数、f_Write（）、f_sync（）、/f_nunlink（）、f _mkdir（）、f-chmod（）、f=rename（）、fstruncate（）和f_getfree（）/以及可选的编写函数。*/


#define FF_FS_MINIMIZE	0
/* 此选项定义最小化级别以删除一些基本API函数。//0：基本功能已完全启用。/1： f_stat（）、f_getfree（）、f-unlink（）、f _mkdir（）、f=truncate（）和f_reame（）/被删除。/2： f_opendir（）、f_readdir（）和f_closedir（）除了1之外都被删除。/3:f_lsek（）函数除了2之外也被删除。*/


#define FF_USE_STRFUNC	0
/* 此选项切换字符串函数f_gets（）、f_putc（）、f _puts（）和f_printf（）。//0：禁用字符串函数。/1： 在不进行LF-CRLF转换的情况下启用。/2： 通过LF-CRLF转换启用。*/


#define FF_USE_FIND		0
/* 此选项切换过滤的目录读取函数f_findfirst（）和/f_findnext（）。（0:禁用，1:启用2:也使用匹配的altname[]启用）*/


#define FF_USE_MKFS		1
/* 此选项切换f_mkfs（）函数。（0：禁用或1：启用）*/


#define FF_USE_FASTSEEK	CONFIG_FATFS_USE_FASTSEEK
/* 此选项切换快速寻道功能。（0：禁用或1：启用）*/


#define FF_USE_EXPAND	0
/* 此选项切换f_expand函数。（0：禁用或1：启用）*/


#define FF_USE_CHMOD	1
/* 此选项切换属性操纵函数f_chmod（）和f_uime（）。/（0：禁用或1：启用）此外，FF_FS_READONLY需要为0才能启用此选项。*/


#define FF_USE_LABEL	0
/* 此选项切换卷标函数f_getlabel（）和f_setlabel（）。/（0：禁用或1：启用）*/


#define FF_USE_FORWARD	0
/* 此选项切换f_forward（）函数。（0：禁用或1：启用）*/


/*---------------------------------------------------------------------------/
/区域设置和命名空间配置
/---------------------------------------------------------------------------*/

#define FF_CODE_PAGE	CONFIG_FATFS_CODEPAGE
/* 此选项指定要在目标系统上使用的OEM代码页。/错误的代码页设置可能导致文件打开失败。//437-美国/720-阿拉伯语/737-希腊语/771-KBL/775-波罗的海/850-拉丁语1/852-拉丁语2/855-西里尔语/857-土耳其语/860-葡萄牙语/861-冰岛语/862-希伯来语/863-加拿大法语/864-阿拉伯语/865-北欧语/866-俄语/869-希腊语2/932-日语（DBCS）/936-简体中文（DBCS并由f_setcp（）配置
*/


#if defined(CONFIG_FATFS_LFN_STACK)
#define FF_USE_LFN    2
#elif defined(CONFIG_FATFS_LFN_HEAP)
#define FF_USE_LFN    3
#else /* CONFIG_FATFS_LFN_NONE */
#define FF_USE_LFN    0
#endif

#ifdef CONFIG_FATFS_MAX_LFN
#define FF_MAX_LFN    CONFIG_FATFS_MAX_LFN
#endif

/* FF_USE_LFN切换对LFN（长文件名）的支持。//0：禁用LFN。FF_MAX_LFN无效。/1： 使用BSS上的静态工作缓冲区启用LFN。始终不是线程安全的。/2： 使用STACK上的动态工作缓冲区启用LFN。/3： 在HEAP上启用具有动态工作缓冲区的LFN。//要启用LFN，请使用ffunicode。c需要添加到项目中。启用exFAT时，LFN功能/要求某些内部工作缓冲区占用（FF_MAX_LFN+1）2字节和/或额外（FF_MAX_LFN+44）/15 32字节。/FF_MAX_LFN以UTF-16代码单位定义工作缓冲区的大小，可以/范围在12到255之间。建议设置为255以完全支持LFN/规范。/当使用堆栈作为工作缓冲区时，请注意堆栈溢出。当为工作缓冲区使用堆/内存时，ffsystem中的内存管理函数ff_memalloc（）和/ff_memfree（）。c、 需要添加到项目中。*/


#ifdef CONFIG_FATFS_API_ENCODING_UTF_8
#define FF_LFN_UNICODE      2
#elif defined(CONFIG_FATFS_API_ENCODING_UTF_16)
#define FF_LFN_UNICODE      1
#else /* CONFIG_FATFS_API_ENCODING_ANSI_OEM */
#define FF_LFN_UNICODE      0
#endif
/* 当启用LFN时，此选项切换API上的字符编码。//0:当前CP中的ANSI/OEM（TCHAR=char）/1:UTF-16中的Unicode（TCHAR=WCHAR）/2:UTF-8中的Unicode未启用LFN时，此选项无效。*/


#define FF_LFN_BUF		255
#define FF_SFN_BUF		12
/* 这组选项定义FILINFO结构中文件名成员的大小，用于读取目录项。这些值应足以读取文件名。读取文件名的最大可能长度取决于字符编码。当未启用LFN时，这些选项无效。*/


#define FF_STRF_ENCODE      3
/* 当FF_LFN_UNICODE>=1且启用了LFN时，字符串I/O函数f_gets（）、/f_putc（）、f_puts和f_printf（）将转换其中的字符编码。/此选项选择通过这些函数对要读取/写入的文件进行字符编码的假设。//0:当前CP中的ANSI/OEM/1:UTF-16LE中的Unicode/2:UTF-16BE中的Unicode/3:UTF-8中的Unicode
*/


#define FF_FS_RPATH		0
/* 此选项配置对相对路径的支持。//0:禁用相对路径并删除相关函数。/1： 启用相对路径。f_chdir（）和f_chdrive（）可用。/2： f_getcwd（）函数除了1之外还可用。
*/


/*---------------------------------------------------------------------------/
/驱动器/卷配置
/---------------------------------------------------------------------------*/

#define FF_VOLUMES		2
/* 要使用的卷（逻辑驱动器）数。(1-10)*/


#define FF_STR_VOLUME_ID	0
#define FF_VOLUME_STRS		"RAM","NAND","CF","SD","SD2","USB","USB2","USB3"
/* FF_STR_VOLUME_ID开关支持任意字符串中的卷ID。/当FF_STR_VOLUME_ID设置为1或2时，可以将任意字符串用作路径名中的驱动器/编号。FF_VOLUME_STRS定义每个/逻辑驱动器的卷ID字符串。项目数量不得小于FF_VOLUMES。卷ID字符串的有效/字符为A-Z、A-Z和0-9，但它们不区分大小写。如果FF_STR_VOLUME_ID>=1且FF_VOLUME_STRS未定义，则需要将用户定义的卷字符串表定义为：//const char VolumeStr[FF_VOLUMES]={“ram”，“flash”，“sd”，“usb”，。。。
*/


#define FF_MULTI_PARTITION	1
/* 此选项切换对物理驱动器上多个卷的支持。/默认情况下（0），每个逻辑驱动器号都绑定到相同的物理驱动器/号，并且只有在物理驱动器上找到的FAT卷将被装载。/启用此功能时（1），每个逻辑驱动器号都可以绑定到VolToPart[]中列出的/任意物理驱动器和分区。f_fdisk（）/function也将可用。*/

/* SD卡扇区大小*/
#define FF_SS_SDCARD      512
/* wear_levelling库扇区大小*/
#define FF_SS_WL          CONFIG_WL_SECTOR_SIZE

#define FF_MIN_SS     MIN(FF_SS_SDCARD, FF_SS_WL)
#define FF_MAX_SS     MAX(FF_SS_SDCARD, FF_SS_WL)
/* 这组选项配置要支持的扇区大小范围。（512、/1024、2048或4096）对于大多数系统、通用存储卡和/硬盘，始终同时设置512。但板载闪存和某些/类型的光学介质可能需要更大的值。当FF_MAX_SS大于FF_MIN_SS时，FatFs配置为/用于可变扇区大小模式，disk_ioctl（）函数需要实现/GET_sector_size命令。*/


#define FF_USE_TRIM		0
/* 此选项切换对ATA-TRIM的支持。（0：禁用或1：启用）/要启用微调功能，还应将CTRL_Trim命令应用于/disk_ioctl（）函数。*/


#define FF_FS_NOFSINFO	0
/* 如果您需要知道FAT32卷上正确的可用空间，请设置此/选项的位0，并且在卷装载后的第一时间，f_getfree（）函数将强制执行/完整的FAT扫描。位1控制最后分配的簇号的使用。//bit0=0：使用FSINFO中的空闲群集计数（如果可用）。/bit0=1:不信任FSINFO中的可用群集计数。/bit1=0：使用FSINFO中最后分配的群集号（如果可用）。/bit1=1：不信任FSINFO中最后分配的群集号。
*/



/*---------------------------------------------------------------------------/
/系统配置
/---------------------------------------------------------------------------*/

#define FF_FS_TINY		(!CONFIG_FATFS_PER_FILE_CACHE)
/* 此选项切换微型缓冲区配置。（0：正常或1：微小）/在微小配置下，文件对象（FIL）的大小缩小FF_MAX_SS字节。/文件系统对象（FATFS）中的公共扇区/缓冲区用于文件数据传输，而不是从文件对象中删除私有扇区缓冲区。*/


#define FF_FS_EXFAT		0
/* 此选项切换对exFAT文件系统的支持。（0：禁用或1：启用）/要启用exFAT，还需要启用LFN。（FF_USE_LFN>=1）/请注意，启用exFAT会丢弃ANSI C（C89）兼容性。*/


#define FF_FS_NORTC		0
#define FF_NORTC_MON	1
#define FF_NORTC_MDAY	1
#define FF_NORTC_YEAR	2018
/* 选项FF_FS_NORTC切换时间戳函数。如果系统没有/任何RTC功能或不需要有效的时间戳，请设置FF_FS_NORTC=1以禁用/时间戳功能。由FatFs修改的每个对象都将具有固定的时间戳/由本地时间的FF_NORTC_MON、FF_NORTC_MDAY和FF_NORTC_YEAR定义。/要启用时间戳函数（FF_FS_NORTC=0），需要将get_fattime（）函数添加到项目中，以从实时时钟读取当前时间。FF_NORTC_MON、/FF_NORTC_MDAY和FF_NORTC_YEAR没有影响。/这些选项在只读配置时无效（FF_FS_READONLY=1）。*/


#define FF_FS_LOCK		CONFIG_FATFS_FS_LOCK
/* 选项FF_FS_LOCK切换文件锁定功能，以控制复制文件打开/和非法操作打开对象。当FF_FS_READONLY/为1时，此选项必须为0。//0：禁用文件锁定功能。为避免卷损坏，应用程序/应避免非法打开、删除和重命名打开的对象。/>0：启用文件锁定功能。该值定义在文件锁定控制下可以同时打开多少文件/子目录。请注意，文件/锁控件与重入无关。*/


#define FF_FS_REENTRANT	1
#define FF_FS_TIMEOUT	(CONFIG_FATFS_TIMEOUT_MS / portTICK_PERIOD_MS)
#define FF_SYNC_t		SemaphoreHandle_t
/* 选项FF_FS_REENTRANT切换FatFs/模块本身的重入（线程安全）。请注意，无论此选项如何，对不同/volume的文件访问始终是可重入的，而卷控制函数f_mount（）、f_mkfs（）/和f_fdisk（）函数始终不是可重入。此功能仅控制对同一卷的文件/目录访问。//0：禁用重入。FF_FS_TIMEOUT和FF_SYNC_t没有影响。/1： 启用重新进入。此外，必须将用户提供的同步处理程序/ff_req_grant（）、ff_rel_grant（）、ff_del_syncobj（）和ff_cre_synccobj（）/function添加到项目中。示例在/option/syscall.c.//FF_FS_TIMEOUT中可用。//FF_FS_TIMEOUT以时间刻度为单位定义超时时间。/FF_SYNC_t定义O/S相关同步对象类型。e、 g.HANDLE、ID、OS_EVENT、/SeaphoreHandle_t等。O/S定义的头文件需要包含在ff.h的范围内。*/

#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

/* 除了ff.h之外，这里还声明了一些内存分配函数，这样当LFN功能被禁用时，外部代码也可以使用它们。
 */
void* ff_memalloc (unsigned msize);
void ff_memfree(void*);


/*---配置结束选项---*/

/* 重新定义磁盘IO函数的名称以防止名称冲突*/
#define disk_initialize     ff_disk_initialize
#define disk_status         ff_disk_status
#define disk_read           ff_disk_read
#define disk_write          ff_disk_write
#define disk_ioctl          ff_disk_ioctl

