/*
 * 溢出物.h
 *
 *  创建日期：2013年5月26日作者：peter
 */

#ifndef SPIFFS_H_
#define SPIFFS_H_
#if defined(__cplusplus)
extern "C" {
#endif

#include "spiffs_config.h"

#define SPIFFS_OK                       0
#define SPIFFS_ERR_NOT_MOUNTED          -10000
#define SPIFFS_ERR_FULL                 -10001
#define SPIFFS_ERR_NOT_FOUND            -10002
#define SPIFFS_ERR_END_OF_OBJECT        -10003
#define SPIFFS_ERR_DELETED              -10004
#define SPIFFS_ERR_NOT_FINALIZED        -10005
#define SPIFFS_ERR_NOT_INDEX            -10006
#define SPIFFS_ERR_OUT_OF_FILE_DESCS    -10007
#define SPIFFS_ERR_FILE_CLOSED          -10008
#define SPIFFS_ERR_FILE_DELETED         -10009
#define SPIFFS_ERR_BAD_DESCRIPTOR       -10010
#define SPIFFS_ERR_IS_INDEX             -10011
#define SPIFFS_ERR_IS_FREE              -10012
#define SPIFFS_ERR_INDEX_SPAN_MISMATCH  -10013
#define SPIFFS_ERR_DATA_SPAN_MISMATCH   -10014
#define SPIFFS_ERR_INDEX_REF_FREE       -10015
#define SPIFFS_ERR_INDEX_REF_LU         -10016
#define SPIFFS_ERR_INDEX_REF_INVALID    -10017
#define SPIFFS_ERR_INDEX_FREE           -10018
#define SPIFFS_ERR_INDEX_LU             -10019
#define SPIFFS_ERR_INDEX_INVALID        -10020
#define SPIFFS_ERR_NOT_WRITABLE         -10021
#define SPIFFS_ERR_NOT_READABLE         -10022
#define SPIFFS_ERR_CONFLICTING_NAME     -10023
#define SPIFFS_ERR_NOT_CONFIGURED       -10024

#define SPIFFS_ERR_NOT_A_FS             -10025
#define SPIFFS_ERR_MOUNTED              -10026
#define SPIFFS_ERR_ERASE_FAIL           -10027
#define SPIFFS_ERR_MAGIC_NOT_POSSIBLE   -10028

#define SPIFFS_ERR_NO_DELETED_BLOCKS    -10029

#define SPIFFS_ERR_FILE_EXISTS          -10030

#define SPIFFS_ERR_NOT_A_FILE           -10031
#define SPIFFS_ERR_RO_NOT_IMPL          -10032
#define SPIFFS_ERR_RO_ABORTED_OPERATION -10033
#define SPIFFS_ERR_PROBE_TOO_FEW_BLOCKS -10034
#define SPIFFS_ERR_PROBE_NOT_A_FS       -10035
#define SPIFFS_ERR_NAME_TOO_LONG        -10036

#define SPIFFS_ERR_IX_MAP_UNMAPPED      -10037
#define SPIFFS_ERR_IX_MAP_MAPPED        -10038
#define SPIFFS_ERR_IX_MAP_BAD_RANGE     -10039

#define SPIFFS_ERR_SEEK_BOUNDS          -10040


#define SPIFFS_ERR_INTERNAL             -10050

#define SPIFFS_ERR_TEST                 -10100


// spiffs文件描述符索引类型。必须签名
typedef s16_t spiffs_file;
// spiffs文件描述符标志
typedef u16_t spiffs_flags;
// spiffs文件模式
typedef u16_t spiffs_mode;
// 对象类型
typedef u8_t spiffs_obj_type;

struct spiffs_t;

#if SPIFFS_HAL_CALLBACK_EXTRA

/* spi读取调用函数类型*/
typedef s32_t (*spiffs_read)(struct spiffs_t *fs, u32_t addr, u32_t size, u8_t *dst);
/* spi写调用函数类型*/
typedef s32_t (*spiffs_write)(struct spiffs_t *fs, u32_t addr, u32_t size, u8_t *src);
/* spi擦除调用函数类型*/
typedef s32_t (*spiffs_erase)(struct spiffs_t *fs, u32_t addr, u32_t size);

#else // SPIFFS_HAL_CALLBACK_EXTRA

/* spi读取调用函数类型*/
typedef s32_t (*spiffs_read)(u32_t addr, u32_t size, u8_t *dst);
/* spi写调用函数类型*/
typedef s32_t (*spiffs_write)(u32_t addr, u32_t size, u8_t *src);
/* spi擦除调用函数类型*/
typedef s32_t (*spiffs_erase)(u32_t addr, u32_t size);
#endif // SPIFFS_HAL_CALLBACK_EXTRA

/* 文件系统检查回调报告操作*/
typedef enum {
  SPIFFS_CHECK_LOOKUP = 0,
  SPIFFS_CHECK_INDEX,
  SPIFFS_CHECK_PAGE
} spiffs_check_type;

/* 文件系统检查回调报告类型*/
typedef enum {
  SPIFFS_CHECK_PROGRESS = 0,
  SPIFFS_CHECK_ERROR,
  SPIFFS_CHECK_FIX_INDEX,
  SPIFFS_CHECK_FIX_LOOKUP,
  SPIFFS_CHECK_DELETE_ORPHANED_INDEX,
  SPIFFS_CHECK_DELETE_PAGE,
  SPIFFS_CHECK_DELETE_BAD_FILE
} spiffs_check_report;

/* 文件系统检查回调函数*/
#if SPIFFS_HAL_CALLBACK_EXTRA
typedef void (*spiffs_check_callback)(struct spiffs_t *fs, spiffs_check_type type, spiffs_check_report report,
    u32_t arg1, u32_t arg2);
#else // SPIFFS_HAL_CALLBACK_EXTRA
typedef void (*spiffs_check_callback)(spiffs_check_type type, spiffs_check_report report,
    u32_t arg1, u32_t arg2);
#endif // SPIFFS_HAL_CALLBACK_EXTRA

/* 文件系统侦听器回调操作*/
typedef enum {
  /* 文件已创建*/
  SPIFFS_CB_CREATED = 0,
  /* 文件已更新或移动到另一页*/
  SPIFFS_CB_UPDATED,
  /* 文件已被删除*/
  SPIFFS_CB_DELETED
} spiffs_fileop_type;

/* 文件系统侦听器回调函数*/
typedef void (*spiffs_file_callback)(struct spiffs_t *fs, spiffs_fileop_type op, spiffs_obj_id obj_id, spiffs_page_ix pix);

#ifndef SPIFFS_DBG
#define SPIFFS_DBG(...) \
    printf(__VA_ARGS__)
#endif
#ifndef SPIFFS_GC_DBG
#define SPIFFS_GC_DBG(...) printf(__VA_ARGS__)
#endif
#ifndef SPIFFS_CACHE_DBG
#define SPIFFS_CACHE_DBG(...) printf(__VA_ARGS__)
#endif
#ifndef SPIFFS_CHECK_DBG
#define SPIFFS_CHECK_DBG(...) printf(__VA_ARGS__)
#endif

/* 对文件句柄的任何写入都将附加到文件末尾*/
#define SPIFFS_APPEND                   (1<<0)
#define SPIFFS_O_APPEND                 SPIFFS_APPEND
/* 如果打开的文件存在，则在打开之前将其截断为零长度*/
#define SPIFFS_TRUNC                    (1<<1)
#define SPIFFS_O_TRUNC                  SPIFFS_TRUNC
/* 如果打开的文件不存在，将在打开之前创建该文件*/
#define SPIFFS_CREAT                    (1<<2)
#define SPIFFS_O_CREAT                  SPIFFS_CREAT
/* 只能读取打开的文件*/
#define SPIFFS_RDONLY                   (1<<3)
#define SPIFFS_O_RDONLY                 SPIFFS_RDONLY
/* 只能写入打开的文件*/
#define SPIFFS_WRONLY                   (1<<4)
#define SPIFFS_O_WRONLY                 SPIFFS_WRONLY
/* 打开的文件可以读写*/
#define SPIFFS_RDWR                     (SPIFFS_RDONLY | SPIFFS_WRONLY)
#define SPIFFS_O_RDWR                   SPIFFS_RDWR
/* 对文件句柄的任何写入都不会被缓存，而是直接刷新*/
#define SPIFFS_DIRECT                   (1<<5)
#define SPIFFS_O_DIRECT                 SPIFFS_DIRECT
/* 如果设置了SPIFFS_O_CREAT和SPIFFS__O_EXCL，则如果文件存在，SPIFFS_open（）将失败*/
#define SPIFFS_EXCL                     (1<<6)
#define SPIFFS_O_EXCL                   SPIFFS_EXCL

#define SPIFFS_SEEK_SET                 (0)
#define SPIFFS_SEEK_CUR                 (1)
#define SPIFFS_SEEK_END                 (2)

#define SPIFFS_TYPE_FILE                (1)
#define SPIFFS_TYPE_DIR                 (2)
#define SPIFFS_TYPE_HARD_LINK           (3)
#define SPIFFS_TYPE_SOFT_LINK           (4)

#ifndef SPIFFS_LOCK
#define SPIFFS_LOCK(fs)
#endif

#ifndef SPIFFS_UNLOCK
#define SPIFFS_UNLOCK(fs)
#endif

// 物理结构

// spiffs-spi配置结构
typedef struct {
  // 物理读取功能
  spiffs_read hal_read_f;
  // 物理写入功能
  spiffs_write hal_write_f;
  // 物理擦除功能
  spiffs_erase hal_erase_f;
#if SPIFFS_SINGLETON == 0
  // spi闪存的物理大小
  u32_t phys_size;
  // 用于溢出的spi闪存中的物理偏移，
  // 必须在块边界上
  u32_t phys_addr;
  // 擦除块时的物理大小
  u32_t phys_erase_block;

  // 块的逻辑大小，必须在物理上
  // 块大小边界，且不得小于
  // 物理块
  u32_t log_block_size;
  // 页面的逻辑大小，必须至少为
  // 日志块大小/8
  u32_t log_page_size;

#endif
#if SPIFFS_FILEHDL_OFFSET
  // 添加到每个文件句柄的整数偏移量
  u16_t fh_ix_offset;
#endif
} spiffs_config;

typedef struct spiffs_t {
  // 文件系统配置
  spiffs_config cfg;
  // 逻辑块数
  u32_t block_count;

  // 自由块光标，块索引
  spiffs_block_ix free_cursor_block_ix;
  // 自由块光标，条目索引
  int free_cursor_obj_lu_entry;
  // 搜索时的光标，块索引
  spiffs_block_ix cursor_block_ix;
  // 搜索时光标，条目索引
  int cursor_obj_lu_entry;

  // 主工作缓冲区，逻辑页的大小
  u8_t *lu_work;
  // 辅助工作缓冲区，逻辑页的大小
  u8_t *work;
  // 文件描述符存储区
  u8_t *fd_space;
  // 可用文件描述符
  u32_t fd_count;

  // 最后一个错误
  s32_t err_code;

  // 当前可用块数
  u32_t free_blocks;
  // 当前繁忙页面数
  u32_t stats_p_allocated;
  // 当前删除的页数
  u32_t stats_p_deleted;
  // 指示垃圾收集器正在清理的标志
  u8_t cleaning;
  // 所有块中的最大擦除计数
  spiffs_obj_id max_erase_count;

#if SPIFFS_GC_STATS
  u32_t stats_gc_runs;
#endif

#if SPIFFS_CACHE
  // 高速缓冲存储器
  void *cache;
  // 缓存大小
  u32_t cache_size;
#if SPIFFS_CACHE_STATS
  u32_t cache_hits;
  u32_t cache_misses;
#endif
#endif

  // 检查回调函数
  spiffs_check_callback check_cb_f;
  // 文件回调函数
  spiffs_file_callback file_cb_f;
  // 悬挂的旗帜
  u8_t mounted;
  // 用户数据
  void *user_data;
  // 配置魔术
  u32_t config_magic;
} spiffs;

/* spiffs文件状态结构*/
typedef struct {
  spiffs_obj_id obj_id;
  u32_t size;
  spiffs_obj_type type;
  spiffs_page_ix pix;
  u8_t name[SPIFFS_OBJ_NAME_LEN];
#if SPIFFS_OBJ_META_LEN
  u8_t meta[SPIFFS_OBJ_META_LEN];
#endif
} spiffs_stat;

struct spiffs_dirent {
  spiffs_obj_id obj_id;
  u8_t name[SPIFFS_OBJ_NAME_LEN];
  spiffs_obj_type type;
  u32_t size;
  spiffs_page_ix pix;
#if SPIFFS_OBJ_META_LEN
  u8_t meta[SPIFFS_OBJ_META_LEN];
#endif
};

typedef struct {
  spiffs *fs;
  spiffs_block_ix block;
  int entry;
} spiffs_DIR;

#if SPIFFS_IX_MAP

typedef struct {
  // 具有查找数据像素的缓冲区
  spiffs_page_ix *map_buf;
  // 精确文件字节偏移
  u32_t offset;
  // 查找缓冲区的起始数据跨度索引
  spiffs_span_ix start_spix;
  // 查找缓冲区的结束数据跨度索引
  spiffs_span_ix end_spix;
} spiffs_ix_map;

#endif

// 功能

#if SPIFFS_USE_MAGIC && SPIFFS_USE_MAGIC_LENGTH && SPIFFS_SINGLETON==0
/**
 * 特殊功能。这将获取一个spiffs配置结构，并返回此文件系统格式化时使用的块数。此函数依赖于在给定的配置结构中正确设置了以下信息：
 *
 * phys_addr、log_page_size和log_block_size。
 *
 * 此外，必须在配置结构中设置hal_read_f。
 *
 * 调用此函数时，必须确保被探测文件系统中的页面大小正确，并且物理地址正确。如果phys_addr实际上指向文件系统的开始，则不会进行检查，因此如果在块边界处的文件系统中间某处输入phys_aaddr，则可能会得到误报。此外，不检查页面大小是否正确。否则，将返回奇怪的文件系统大小。
 *
 * 如果此函数检测到文件系统，则返回假定的文件系统大小，该大小可用于设置phys_size。
 *
 * 否则，它将返回一个错误，指出为什么不将其视为文件系统。
 *
 * 注意：此函数不受SPIFFS_LOCK和SPIFFS_UNLOCK宏的保护。它直接返回错误代码，而不是由SPIFFS_errno读取。
 *
 * @param config        文件系统的物理和逻辑配置的基本部分。
 */
s32_t SPIFFS_probe_fs(spiffs_config *config);
#endif // SPIFFS_USE_MAGIC && SPIFFS_USE_MAGIC_LENGTH && SPIFFS_SINGLETON==0

/**
 * 初始化文件系统动态参数并装载文件系统。如果启用了SPIFFS_USE_MAGIC，则如果闪存不包含可识别的文件系统，则安装可能会失败，出现SPIFFS_ERROR_NOT_A_FS。在这种情况下，必须在重新安装之前调用SPIFFS_format。
 * @param fs            文件系统结构
 * @param config        文件系统的物理和逻辑配置
 * @param work          内存工作缓冲区，包括在所有文件系统操作中使用的2*config->log_page_size字节
 * @param fd_space      文件描述符内存
 * @param fd_space_size 文件描述符的内存大小
 * @param cache         缓存的内存，可以为空
 * @param cache_size    缓存的内存大小
 * @param check_cb_f    一致性检查期间报告的回调函数
 */
s32_t SPIFFS_mount(spiffs *fs, spiffs_config *config, u8_t *work,
    u8_t *fd_space, u32_t fd_space_size,
    void *cache, u32_t cache_size,
    spiffs_check_callback check_cb_f);

/**
 * 卸载文件系统。所有文件句柄都将刷新所有缓存的写入并关闭。
 * @param fs            文件系统结构
 */
void SPIFFS_unmount(spiffs *fs);

/**
 * 创建新文件。
 * @param fs            文件系统结构
 * @param path          新文件的路径
 * @param mode          忽略，符合posix
 */
s32_t SPIFFS_creat(spiffs *fs, const char *path, spiffs_mode mode);

/**
 * 打开/创建文件。
 * @param fs            文件系统结构
 * @param path          新文件的路径
 * @param flags         open命令的标志可以是SPIFFS_O_APPEND、SPIFFS__O_TRUNC、SPIFF_O_CREAT、SPIFFS_O_RDONLY、SPIFF_S_O_WRONLY、SPIOFFS_O_RDWR、SPIFFC_O_DIRECT、SPIFFS.O__EXCL的组合
 * @param mode          忽略，符合posix
 */
spiffs_file SPIFFS_open(spiffs *fs, const char *path, spiffs_flags flags, spiffs_mode mode);

/**
 * 按给定目录项打开文件。出于优化目的，当使用SPIFFS_adder遍历文件系统时，正常的SPIFFS_open需要再次遍历文件系统以查找文件，而SPIFFS_open_by_dirent已经知道文件所在的位置。
 * @param fs            文件系统结构
 * @param e             文件的dir项
 * @param flags         打开命令的标志可以是SPIFFS_APPEND、SPIFFS_TRUNC、SPIFFS_CREAT、SPIFF_RD_ONLY、SPIFFC_WR_ONLY、SPIFFR_RDWR、SPIFFP_DIRECT的组合。在这种情况下，SPIFFS_CREATE不起作用。
 * @param mode          忽略，符合posix
 */
spiffs_file SPIFFS_open_by_dirent(spiffs *fs, struct spiffs_dirent *e, spiffs_flags flags, spiffs_mode mode);

/**
 * 按给定的页面索引打开文件。出于优化目的，通过直接指向spi闪存中的页面索引来打开文件。如果页面索引未指向文件头，则返回SPIFFS_ERROR_not_a_file。
 * @param fs            文件系统结构
 * @param page_ix       页面索引
 * @param flags         打开命令的标志可以是SPIFFS_APPEND、SPIFFS_TRUNC、SPIFFS_CREAT、SPIFF_RD_ONLY、SPIFFC_WR_ONLY、SPIFFR_RDWR、SPIFFP_DIRECT的组合。在这种情况下，SPIFFS_CREATE不起作用。
 * @param mode          忽略，符合posix
 */
spiffs_file SPIFFS_open_by_page(spiffs *fs, spiffs_page_ix page_ix, spiffs_flags flags, spiffs_mode mode);

/**
 * 从给定文件句柄读取。
 * @param fs            文件系统结构
 * @param fh            文件句柄
 * @param buf           读取数据的位置
 * @param len           要读多少
 * @returns 读取的字节数，如果错误，则为-1
 */
s32_t SPIFFS_read(spiffs *fs, spiffs_file fh, void *buf, s32_t len);

/**
 * 写入给定的文件句柄。
 * @param fs            文件系统结构
 * @param fh            文件句柄
 * @param buf           要写入的数据
 * @param len           写多少
 * @returns 写入的字节数，如果错误，则为-1
 */
s32_t SPIFFS_write(spiffs *fs, spiffs_file fh, void *buf, s32_t len);

/**
 * 移动读/写文件偏移量。如果出现错误，则返回结果偏移量或为负值。lseek（fs，fd，0，SPIFFS_SEK_CUR）将返回电流偏移。
 * @param fs            文件系统结构
 * @param fh            文件句柄
 * @param offs          偏移量移动多少/移动到哪里
 * @param whence        如果是SPIFFS_SEK_SET，则文件偏移量应设置为偏移字节（如果是SPIOFFS_SEK_CUR），如果是SPIFFS_SEK_END，则文件的偏移量应设为其当前位置加上偏移量（如果是SPIFFS_SEK-END），文件的偏移应设为文件的大小加上偏移，该值应为负值
 */
s32_t SPIFFS_lseek(spiffs *fs, spiffs_file fh, s32_t offs, int whence);

/**
 * 按路径删除文件
 * @param fs            文件系统结构
 * @param path          要删除的文件的路径
 */
s32_t SPIFFS_remove(spiffs *fs, const char *path);

/**
 * 按文件句柄删除文件
 * @param fs            文件系统结构
 * @param fh            要删除的文件的文件句柄
 */
s32_t SPIFFS_fremove(spiffs *fs, spiffs_file fh);

/**
 * 按路径获取文件状态
 * @param fs            文件系统结构
 * @param path          要stat的文件路径
 * @param s             要填充的stat结构
 */
s32_t SPIFFS_stat(spiffs *fs, const char *path, spiffs_stat *s);

/**
 * 按文件句柄获取文件状态
 * @param fs            文件系统结构
 * @param fh            要stat的文件的文件句柄
 * @param s             要填充的stat结构
 */
s32_t SPIFFS_fstat(spiffs *fs, spiffs_file fh, spiffs_stat *s);

/**
 * 刷新给定文件的缓存中所有挂起的写入操作
 * @param fs            文件系统结构
 * @param fh            要刷新的文件的文件句柄
 */
s32_t SPIFFS_fflush(spiffs *fs, spiffs_file fh);

/**
 * 关闭文件句柄。如果存在挂起的写入操作，则在关闭之前完成这些操作。
 * @param fs            文件系统结构
 * @param fh            要关闭的文件的文件句柄
 */
s32_t SPIFFS_close(spiffs *fs, spiffs_file fh);

/**
 * 重命名文件
 * @param fs            文件系统结构
 * @param old           要重命名的文件路径
 * @param newPath       文件的新路径
 */
s32_t SPIFFS_rename(spiffs *fs, const char *old, const char *newPath);

#if SPIFFS_OBJ_META_LEN
/**
 * 更新文件的元数据
 * @param fs            文件系统结构
 * @param path          文件的路径
 * @param meta          新元数据。必须为SPIFFS_OBY_META_LEN字节长。
 */
s32_t SPIFFS_update_meta(spiffs *fs, const char *name, const void *meta);

/**
 * 更新文件的元数据
 * @param fs            文件系统结构
 * @param fh            文件的文件句柄
 * @param meta          新元数据。必须为SPIFFS_OBY_META_LEN字节长。
 */
s32_t SPIFFS_fupdate_meta(spiffs *fs, spiffs_file fh, const void *meta);
#endif

/**
 * 返回上次文件操作的最后一个错误。
 * @param fs            文件系统结构
 */
s32_t SPIFFS_errno(spiffs *fs);

/**
 * 清除上一个错误。
 * @param fs            文件系统结构
 */
void SPIFFS_clearerr(spiffs *fs);

/**
 * 打开与给定名称对应的目录流。流位于目录中的第一个条目处。在氢构建中，名称参数被忽略，因为氢构建总是对应于一个平面文件结构-没有目录。
 * @param fs            文件系统结构
 * @param name          目录的名称
 * @param d             指向要填充的目录流
 */
spiffs_DIR *SPIFFS_opendir(spiffs *fs, const char *name, spiffs_DIR *d);

/**
 * 关闭目录流
 * @param d             要关闭的目录流
 */
s32_t SPIFFS_closedir(spiffs_DIR *d);

/**
 * 将目录读取到给定的spifs_drent结构中。
 * @param d             指向目录流的指针
 * @param e             要填充的目录结构
 * @returns 如果错误或流结束，则返回null，否则返回给定的目录
 */
struct spiffs_dirent *SPIFFS_readdir(spiffs_DIR *d, struct spiffs_dirent *e);

/**
 * 对给定文件系统运行一致性检查。
 * @param fs            文件系统结构
 */
s32_t SPIFFS_check(spiffs *fs);

/**
 * 返回可用的总字节数和已使用的字节数。这是一个估计值，取决于是否有很多文件数据很少，或者有几个文件数据很多。注意：如果使用的字节数超过总字节数，则应运行SPIFFS_check。这表明在某些情况下会发生断电。在最坏的情况下（在修补或gc中重复断电），您可能需要删除一些文件。
 *
 * @param fs            文件系统结构
 * @param total         文件系统中的总字节数
 * @param used          文件系统中已使用的字节数
 */
s32_t SPIFFS_info(spiffs *fs, u32_t *total, u32_t *used);

/**
 * 格式化整个文件系统。所有数据都将丢失。调用此命令时，不得装入文件系统。
 *
 * 注意：格式化很尴尬。由于向后兼容，为了配置文件系统，必须在格式化之前调用SPIFFS_mount。如果SPIFFS_mount成功，则必须在调用SPIFFS_form之前调用SPIFFS_unmount。如果SPIFFS_mount失败，则可以直接调用SPIFFS_form，而无需先调用SPIFFS_unmount。
 *
 * @param fs            文件系统结构
 */
s32_t SPIFFS_format(spiffs *fs);

/**
 * 如果已装入spiffs，则返回非零，如果未装入，则返回零。
 * @param fs            文件系统结构
 */
u8_t SPIFFS_mounted(spiffs *fs);

/**
 * 尝试查找删除了大部分或所有页面的块，如果找到则删除该块。不注意磨损调平。不会四处移动页面。如果参数max_free_pages设置为0，则只选择仅删除页面的块。
 *
 * 注意：当spiffs需要空闲页面时，会自动调用垃圾收集器。此功能的原因是，当用户知道系统空闲时，可以进行后台整理。
 *
 * 小心使用。
 *
 * 如果将max_free_pages设置为任何大于零的值，最终会使flash磨损更多，因为可以擦除包含空闲页面的块。
 *
 * 如果找到并擦除了块，则将err_no设置为SPIFFS_OK；如果找不到匹配块，则设置为SPIOFFS_error_no_DELETED_block，或其他错误。
 *
 * @param fs             文件系统结构
 * @param max_free_pages 块中允许的最大可用页数
 */
s32_t SPIFFS_gc_quick(spiffs *fs, u16_t max_free_pages);

/**
 * 将尝试通过移动页面和擦除块来为文件系统中给定数量的字节腾出空间。如果在物理上不可能，err_no将设置为SPIFFS_ERROR_FULL。如果已经有这个数量（或更多）的可用空间，SPIFFS_gc将自动返回。建议在调用此方法之前调用SPIFFS_info，以确定要提供的字节数。
 *
 * 注意：当spiffs需要空闲页面时，会自动调用垃圾收集器。此功能的原因是，当用户知道系统空闲时，可以进行后台整理。
 *
 * 小心使用。
 *
 * @param fs            文件系统结构
 * @param size          应释放的字节数
 */
s32_t SPIFFS_gc(spiffs *fs, u32_t size);

/**
 * 检查是否达到EOF。
 * @param fs            文件系统结构
 * @param fh            要检查的文件的文件句柄
 */
s32_t SPIFFS_eof(spiffs *fs, spiffs_file fh);

/**
 * 获取文件中的位置。
 * @param fs            文件系统结构
 * @param fh            要检查的文件的文件句柄
 */
s32_t SPIFFS_tell(spiffs *fs, spiffs_file fh);

/**
 * 注册跟踪文件头操作的回调函数。请注意，此回调是从内部spiffs机制中调用的。在此回调中对实际文件系统进行回调的任何操作都会把事情弄得一团糟——不要这样做。这可以用来跟踪文件的位置，并在垃圾收集过程中四处移动，这反过来又可以用来在ram中构建位置表。与SPIFFS_open_by_page结合使用，这可能会在打开大量文件时提高性能。必须在装载后调用。
 *
 * @param fs            文件系统结构
 * @param cb_func       文件操作的回调
 */
s32_t SPIFFS_set_file_callback_func(spiffs *fs, spiffs_file_callback cb_func);

#if SPIFFS_IX_MAP

/**
 * 将第一级索引查找映射到给定的内存映射。这将使读取大文件更快，因为内存映射将用于查找数据页，而不是在物理介质上搜索索引。映射时，找到所有受影响的标记，并将信息复制到阵列中。可以映射整个文件或部分文件。索引映射将覆盖从参数offset到包含参数（offset+len）的文件内容。映射比当前文件大小更长的范围是有效的。当文件增长时，将填充映射。在垃圾收集和文件数据页移动时，映射数组将自动更新。不要篡改映射数组，因为它包含对数据页的引用。从外部修改它将损坏使用此文件描述符的任何未来读数。当文件描述符关闭或文件未映射时，将不再使用映射。在读取大型文件时，或者在文件中查找和读取大量内容时，这对于获得更快、更具确定性的定时非常有用。
 * @param fs      文件系统结构
 * @param fh      要映射的文件的文件句柄
 * @param map     spiffs_ixmap结构，描述索引映射
 * @param offset  索引映射起始位置的绝对文件偏移
 * @param len     映射的长度（以实际文件字节为单位）
 * @param map_buf 用于查找数据的数组缓冲区-数组中所需元素的数量可以从函数SPIFFS_bytes_to_ix_map_entries中导出，给定长度
 */
s32_t SPIFFS_ix_map(spiffs *fs, spiffs_file fh, spiffs_ix_map *map,
    u32_t offset, u32_t len, spiffs_page_ix *map_buf);

/**
 * 取消映射此文件句柄的索引查找。所有未来的读数将照常进行，需要从物理介质读取一级指数。函数SPIFFS_ix_map中给定的映射和映射缓冲区将不再被spiff引用。关闭文件之前不必严格取消映射，因为关闭文件会自动取消映射。
 * @param fs      文件系统结构
 * @param fh      要取消映射的文件的文件句柄
 */
s32_t SPIFFS_ix_unmap(spiffs *fs, spiffs_file fh);

/**
 * 移动函数SPIFFS_ix_map中给定的索引映射的偏移量。将重新填充部分或全部贴图缓冲区。
 * @param fs      文件系统结构
 * @param fh      要重新映射的文件的映射文件句柄
 * @param offset  开始索引映射的新绝对文件偏移量
 */
s32_t SPIFFS_ix_remap(spiffs *fs, spiffs_file fh, u32_t offs);

/**
 * 获取映射缓冲区必须包含的spiffs_page_ix项数的实用程序函数，以便映射给定数量的文件数据（以字节为单位）。请参见函数SPIFFS_ix_map和SPIFFS_ix_map_entries_to_bytes。
 * @param fs      文件系统结构
 * @param bytes   要映射的文件数据字节数
 * @return        spiffs_page_ix数组中映射文件中给定字节所需的元素数
 */
s32_t SPIFFS_bytes_to_ix_map_entries(spiffs *fs, u32_t bytes);

/**
 * 当映射具有给定数量spiffs_page_ix项的缓冲区的文件时，可以映射的文件数据字节数的实用函数。请参见函数SPIFFS_ix_map和SPIFFS_bytes_to_ix_map_entries。
 * @param fs      文件系统结构
 * @param map_page_ix_entries   spiffs_page_ix数组中的条目数
 * @return        给定具有给定数量spiffs_page_ix项的映射缓冲区，可以映射的文件数据量（字节）
 */
s32_t SPIFFS_ix_map_entries_to_bytes(spiffs *fs, u32_t map_page_ix_entries);

#endif // SPIFFS_IX_MAP


#if SPIFFS_TEST_VISUALISATION
/**
 * 打印文件系统的可视化。
 * @param fs            文件系统结构
 */
s32_t SPIFFS_vis(spiffs *fs);
#endif

#if SPIFFS_BUFFER_HELP
/**
 * 返回给定文件描述符数量的文件描述符缓冲区所需的字节数。
 */
u32_t SPIFFS_buffer_bytes_for_filedescs(spiffs *fs, u32_t num_descs);

#if SPIFFS_CACHE
/**
 * 返回给定缓存页数量的缓存缓冲区所需的字节数。
 */
u32_t SPIFFS_buffer_bytes_for_cache(spiffs *fs, u32_t num_pages);
#endif
#endif

#if SPIFFS_CACHE
#endif
#if defined(__cplusplus)
}
#endif

#endif /* SPIFFS_H_ */

