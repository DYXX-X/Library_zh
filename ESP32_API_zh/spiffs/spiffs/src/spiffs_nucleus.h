/*
 * 溢出_核.h
 *
 *  创建日期：2013年6月15日作者：peter
 */

/* SPIFFS布局
 *
 * 溢油设计用于以下溢油闪蒸特性：
 *   -只能擦除大面积的数据（块）
 *   -擦除将块中的所有位重置为1
 *   -写作会将1变为0
 *   -如果不擦除，则不能将零拉为1
 *   -磨损平整度
 *
 * spiffs还可以在嵌入式内存受限设备上运行。
 *
 * 整个区域被划分为块。整个区域也按页面划分。每个块包含相同数量的页面。页面无法擦除，但块可以擦除。
 *
 * 整个区域必须为block_size*x page_size必须为blocks_size/（2^y），其中y>2
 *
 * 例如：区域=1024*1024字节，块大小=65536字节，页面大小=256字节
 *
 * 块0 PAGE 0对象查找1 PAGE 1对象查找2…PAGE n-1对象查找n PAGE n对象数据1 PAGE n+1对象数据2…PAGE n+m-1对象数据m
 *
 * 块1 PAGE n+m对象查找1 PAGE n+m+1对象查找2…PAGE 2n+m-1对象查找n PAGE 2n+m对象数据1 PAGE 2n+m对象数据2…PAGE 2n+2m-1对象数据m。。。
 *
 * n是对象查找页面的数量，这是按对象id索引块中所有页面所需的页面数量：block_size/page_size sizeof（obj_id）/page_sizem是数据页面数量，它是块中的页面数量减去查找页面数量：block_size/paage_size-block_size/pages_size/page _size size-of（objid）/page_size因此，n+m是块中页面的总数：block_size/page-size
 *
 * 例如：n=65536/256*2/256=2，m=65536/256-2=254=>n+m=65536/2056=256
 *
 * 对象查找页面包含对象id条目。每个条目表示相应的数据页。假设一个16位的对象id，0xffff的对象id表示一个空闲页。对象id为0x0000表示已删除页面。
 *
 * 例如：第0页：查找：0008 0001 0aaa ffff ffff ffffffffff…第1页：查询：ffff fff ffff ffoff fffffff…第2页：数据：对象id 0008的数据第3页：数据，对象id 0001的数据第4页：数据，对象id 0aaa的数据。。。
 *
 * 对象数据页可以是对象索引页或对象内容。所有对象数据页都包含一个数据页标题，其中包含对象id和跨度索引。span索引表示具有相同对象id的数据页之间的对象页顺序。这适用于对象索引页（当索引跨越多个条目页时）和对象数据页。对象索引页包含指向对象内容页的页面条目。对象索引页中的条目索引与实际对象数据页中的跨度索引相关。第一个对象索引页（span索引0）称为对象索引头页，还包含对象标志（目录/文件）、大小、对象名称等。
 *
 * 例如：BLOCK 1 PAGE 256：对象查找页1[123][123][123][123][123][122][123][122][123][free][free][free][free]…PAGE 257：对象查找页面2[free][free][free][free][free][自由][free]…PAGE 258：对象索引页（标头）obj.id:0123 span。ix：0000标志：INDEX大小：1600名称：ex。txt类型：文件[259][260][261][262]第259页：对象数据页obj.id:0123 span。ix：0000标志：DATA PAGE 260：对象数据页obj.id:0123 span。ix：0001标志：DATA PAGE 261：对象数据页obj.id:0123 span。ix:0002标志：DATA PAGE 262：对象数据页obj.id:0123 span。ix:0003标志：DATA PAGE 263：对象索引页obj.id:0123 span。ix：0001标志：INDEX[264][265][fre][fre][fre][fre][[fre][fre][fre][fre]PAGE 264：对象数据页对象。id:0123 span。ix：0004标志：DATA PAGE 265：对象数据页obj.id:0123 span。ix:0005标志：DATA
 *
 */
#ifndef SPIFFS_NUCLEUS_H_
#define SPIFFS_NUCLEUS_H_

#define _SPIFFS_ERR_CHECK_FIRST         (SPIFFS_ERR_INTERNAL - 1)
#define SPIFFS_ERR_CHECK_OBJ_ID_MISM    (SPIFFS_ERR_INTERNAL - 1)
#define SPIFFS_ERR_CHECK_SPIX_MISM      (SPIFFS_ERR_INTERNAL - 2)
#define SPIFFS_ERR_CHECK_FLAGS_BAD      (SPIFFS_ERR_INTERNAL - 3)
#define _SPIFFS_ERR_CHECK_LAST          (SPIFFS_ERR_INTERNAL - 4)

// 访问者结果，继续搜索
#define SPIFFS_VIS_COUNTINUE            (SPIFFS_ERR_INTERNAL - 20)
// 访问者结果，重新加载lu缓冲区后继续搜索
#define SPIFFS_VIS_COUNTINUE_RELOAD     (SPIFFS_ERR_INTERNAL - 21)
// 访问者结果，停止搜索
#define SPIFFS_VIS_END                  (SPIFFS_ERR_INTERNAL - 22)

// 更新对象索引内容
#define SPIFFS_EV_IX_UPD                (0)
// 创建新的对象索引
#define SPIFFS_EV_IX_NEW                (1)
// 删除对象索引
#define SPIFFS_EV_IX_DEL                (2)
// 移动对象索引而不更新内容
#define SPIFFS_EV_IX_MOV                (3)
// 仅更新对象索引标头数据，而不更新表本身
#define SPIFFS_EV_IX_UPD_HDR            (4)

#define SPIFFS_OBJ_ID_IX_FLAG           ((spiffs_obj_id)(1<<(8*sizeof(spiffs_obj_id)-1)))

#define SPIFFS_UNDEFINED_LEN            (u32_t)(-1)

#define SPIFFS_OBJ_ID_DELETED           ((spiffs_obj_id)0)
#define SPIFFS_OBJ_ID_FREE              ((spiffs_obj_id)-1)



#if defined(__GNUC__) || defined(__clang__)
    /* 对于GCC和clang*/
#define SPIFFS_PACKED __attribute__((packed))
#elif defined(__ICCARM__) || defined(__CC_ARM)
    /* 用于IAR ARM和Keil MDK-ARM编译器*/
#define SPIFFS_PACKED 

#else
    /* 未知编译器*/
#define SPIFFS_PACKED 
#endif



#if SPIFFS_USE_MAGIC
#if !SPIFFS_USE_MAGIC_LENGTH
#define SPIFFS_MAGIC(fs, bix)           \
  ((spiffs_obj_id)(0x20140529 ^ SPIFFS_CFG_LOG_PAGE_SZ(fs)))
#else // SPIFFS_USE_MAGIC_LENGTH
#define SPIFFS_MAGIC(fs, bix)           \
  ((spiffs_obj_id)(0x20140529 ^ SPIFFS_CFG_LOG_PAGE_SZ(fs) ^ ((fs)->block_count - (bix))))
#endif // SPIFFS_USE_MAGIC_LENGTH
#endif // SPIFFS_USE_MAGIC

#define SPIFFS_CONFIG_MAGIC             (0x20090315)

#if SPIFFS_SINGLETON == 0
#define SPIFFS_CFG_LOG_PAGE_SZ(fs) \
  ((fs)->cfg.log_page_size)
#define SPIFFS_CFG_LOG_BLOCK_SZ(fs) \
  ((fs)->cfg.log_block_size)
#define SPIFFS_CFG_PHYS_SZ(fs) \
  ((fs)->cfg.phys_size)
#define SPIFFS_CFG_PHYS_ERASE_SZ(fs) \
  ((fs)->cfg.phys_erase_block)
#define SPIFFS_CFG_PHYS_ADDR(fs) \
  ((fs)->cfg.phys_addr)
#endif

// 总页数
#define SPIFFS_MAX_PAGES(fs) \
  ( SPIFFS_CFG_PHYS_SZ(fs)/SPIFFS_CFG_LOG_PAGE_SZ(fs) )
// 每个块的总页数，包括对象查找页
#define SPIFFS_PAGES_PER_BLOCK(fs) \
  ( SPIFFS_CFG_LOG_BLOCK_SZ(fs)/SPIFFS_CFG_LOG_PAGE_SZ(fs) )
// 每个块的对象查找页数
#define SPIFFS_OBJ_LOOKUP_PAGES(fs)     \
  (MAX(1, (SPIFFS_PAGES_PER_BLOCK(fs) * sizeof(spiffs_obj_id)) / SPIFFS_CFG_LOG_PAGE_SZ(fs)) )
// 检查页面索引是否属于对象查找
#define SPIFFS_IS_LOOKUP_PAGE(fs,pix)     \
  (((pix) % SPIFFS_PAGES_PER_BLOCK(fs)) < SPIFFS_OBJ_LOOKUP_PAGES(fs))
// 所有对象查找页面中的对象查找条目数
#define SPIFFS_OBJ_LOOKUP_MAX_ENTRIES(fs) \
  (SPIFFS_PAGES_PER_BLOCK(fs)-SPIFFS_OBJ_LOOKUP_PAGES(fs))
// 将块转换为物理地址
#define SPIFFS_BLOCK_TO_PADDR(fs, block) \
  ( SPIFFS_CFG_PHYS_ADDR(fs) + (block)* SPIFFS_CFG_LOG_BLOCK_SZ(fs) )
// 将对象查找条目转换为页面索引
#define SPIFFS_OBJ_LOOKUP_ENTRY_TO_PIX(fs, block, entry) \
  ((block)*SPIFFS_PAGES_PER_BLOCK(fs) + (SPIFFS_OBJ_LOOKUP_PAGES(fs) + entry))
// 将对象查找条目转换为相应页面的物理地址
#define SPIFFS_OBJ_LOOKUP_ENTRY_TO_PADDR(fs, block, entry) \
  (SPIFFS_BLOCK_TO_PADDR(fs, block) + (SPIFFS_OBJ_LOOKUP_PAGES(fs) + entry) * SPIFFS_CFG_LOG_PAGE_SZ(fs) )
// 将页面转换为物理地址
#define SPIFFS_PAGE_TO_PADDR(fs, page) \
  ( SPIFFS_CFG_PHYS_ADDR(fs) + (page) * SPIFFS_CFG_LOG_PAGE_SZ(fs) )
// 将物理地址转换为页面
#define SPIFFS_PADDR_TO_PAGE(fs, addr) \
  ( ((addr) -  SPIFFS_CFG_PHYS_ADDR(fs)) / SPIFFS_CFG_LOG_PAGE_SZ(fs) )
// 在页面中为物理地址提供索引
#define SPIFFS_PADDR_TO_PAGE_OFFSET(fs, addr) \
  ( ((addr) - SPIFFS_CFG_PHYS_ADDR(fs)) % SPIFFS_CFG_LOG_PAGE_SZ(fs) )
// 返回包含给定页面的块
#define SPIFFS_BLOCK_FOR_PAGE(fs, page) \
  ( (page) / SPIFFS_PAGES_PER_BLOCK(fs) )
// 返回块的起始页
#define SPIFFS_PAGE_FOR_BLOCK(fs, block) \
  ( (block) * SPIFFS_PAGES_PER_BLOCK(fs) )
// 将页面转换为对象查找页面中的条目
#define SPIFFS_OBJ_LOOKUP_ENTRY_FOR_PAGE(fs, page) \
  ( (page) % SPIFFS_PAGES_PER_BLOCK(fs) - SPIFFS_OBJ_LOOKUP_PAGES(fs) )
// 返回数据页中的数据大小
#define SPIFFS_DATA_PAGE_SIZE(fs) \
    ( SPIFFS_CFG_LOG_PAGE_SZ(fs) - sizeof(spiffs_page_header) )
// 返回块擦除计数的物理地址，
// 始终在最后一个对象查找页面的物理最后一个条目中
#define SPIFFS_ERASE_COUNT_PADDR(fs, bix) \
  ( SPIFFS_BLOCK_TO_PADDR(fs, bix) + SPIFFS_OBJ_LOOKUP_PAGES(fs) * SPIFFS_CFG_LOG_PAGE_SZ(fs) - sizeof(spiffs_obj_id) )
// 返回块魔法的物理地址，
// 始终在最后一个对象查找页面的物理第二个最后一个条目中
#define SPIFFS_MAGIC_PADDR(fs, bix) \
  ( SPIFFS_BLOCK_TO_PADDR(fs, bix) + SPIFFS_OBJ_LOOKUP_PAGES(fs) * SPIFFS_CFG_LOG_PAGE_SZ(fs) - sizeof(spiffs_obj_id)*2 )
// 检查物体luts中是否有魔法空间
#define SPIFFS_CHECK_MAGIC_POSSIBLE(fs) \
  ( (SPIFFS_OBJ_LOOKUP_MAX_ENTRIES(fs) % (SPIFFS_CFG_LOG_PAGE_SZ(fs)/sizeof(spiffs_obj_id))) * sizeof(spiffs_obj_id) \
    <= (SPIFFS_CFG_LOG_PAGE_SZ(fs)-sizeof(spiffs_obj_id)*2) )

// 定义助手对象

// 对象标题页索引中的条目
#define SPIFFS_OBJ_HDR_IX_LEN(fs) \
  ((SPIFFS_CFG_LOG_PAGE_SZ(fs) - sizeof(spiffs_page_object_ix_header))/sizeof(spiffs_page_ix))
// 对象页索引中的条目
#define SPIFFS_OBJ_IX_LEN(fs) \
  ((SPIFFS_CFG_LOG_PAGE_SZ(fs) - sizeof(spiffs_page_object_ix))/sizeof(spiffs_page_ix))
// 给定数据跨度索引的对象索引项
#define SPIFFS_OBJ_IX_ENTRY(fs, spix) \
  ((spix) < SPIFFS_OBJ_HDR_IX_LEN(fs) ? (spix) : (((spix)-SPIFFS_OBJ_HDR_IX_LEN(fs))%SPIFFS_OBJ_IX_LEN(fs)))
// 给定数据跨度索引或条目的对象索引跨度索引号
#define SPIFFS_OBJ_IX_ENTRY_SPAN_IX(fs, spix) \
  ((spix) < SPIFFS_OBJ_HDR_IX_LEN(fs) ? 0 : (1+((spix)-SPIFFS_OBJ_HDR_IX_LEN(fs))/SPIFFS_OBJ_IX_LEN(fs)))
// 获取对象索引span索引的数据span索引
#define SPIFFS_DATA_SPAN_IX_FOR_OBJ_IX_SPAN_IX(fs, spix) \
  ( (spix) == 0 ? 0 : (SPIFFS_OBJ_HDR_IX_LEN(fs) + (((spix)-1) * SPIFFS_OBJ_IX_LEN(fs))) )

#if SPIFFS_FILEHDL_OFFSET
#define SPIFFS_FH_OFFS(fs, fh)   ((fh) != 0 ? ((fh) + (fs)->cfg.fh_ix_offset) : 0)
#define SPIFFS_FH_UNOFFS(fs, fh) ((fh) != 0 ? ((fh) - (fs)->cfg.fh_ix_offset) : 0)
#else
#define SPIFFS_FH_OFFS(fs, fh)   (fh)
#define SPIFFS_FH_UNOFFS(fs, fh) (fh)
#endif


#define SPIFFS_OP_T_OBJ_LU    (0<<0)
#define SPIFFS_OP_T_OBJ_LU2   (1<<0)
#define SPIFFS_OP_T_OBJ_IX    (2<<0)
#define SPIFFS_OP_T_OBJ_DA    (3<<0)
#define SPIFFS_OP_C_DELE      (0<<2)
#define SPIFFS_OP_C_UPDT      (1<<2)
#define SPIFFS_OP_C_MOVS      (2<<2)
#define SPIFFS_OP_C_MOVD      (3<<2)
#define SPIFFS_OP_C_FLSH      (4<<2)
#define SPIFFS_OP_C_READ      (5<<2)
#define SPIFFS_OP_C_WRTHRU    (6<<2)

#define SPIFFS_OP_TYPE_MASK (3<<0)
#define SPIFFS_OP_COM_MASK  (7<<2)


// 如果为0，则将此页写入，否则清除
#define SPIFFS_PH_FLAG_USED   (1<<0)
// 如果为0，则写入已完成，否则正在修改
#define SPIFFS_PH_FLAG_FINAL  (1<<1)
// 如果为0，则这是索引页，否则是数据页
#define SPIFFS_PH_FLAG_INDEX  (1<<2)
// 如果为0，则页面被删除，否则有效
#define SPIFFS_PH_FLAG_DELET  (1<<7)
// 如果为0，则将删除此索引标头
#define SPIFFS_PH_FLAG_IXDELE (1<<6)


#define SPIFFS_CHECK_MOUNT(fs) \
  ((fs)->mounted != 0)

#define SPIFFS_CHECK_CFG(fs) \
  ((fs)->config_magic == SPIFFS_CONFIG_MAGIC)

#define SPIFFS_CHECK_RES(res) \
  do { \
    if ((res) < SPIFFS_OK) return (res); \
  } while (0);

#define SPIFFS_API_CHECK_MOUNT(fs) \
  if (!SPIFFS_CHECK_MOUNT((fs))) { \
    (fs)->err_code = SPIFFS_ERR_NOT_MOUNTED; \
    return SPIFFS_ERR_NOT_MOUNTED; \
  }

#define SPIFFS_API_CHECK_CFG(fs) \
  if (!SPIFFS_CHECK_CFG((fs))) { \
    (fs)->err_code = SPIFFS_ERR_NOT_CONFIGURED; \
    return SPIFFS_ERR_NOT_CONFIGURED; \
  }

#define SPIFFS_API_CHECK_RES(fs, res) \
  if ((res) < SPIFFS_OK) { \
    (fs)->err_code = (res); \
    return (res); \
  }

#define SPIFFS_API_CHECK_RES_UNLOCK(fs, res) \
  if ((res) < SPIFFS_OK) { \
    (fs)->err_code = (res); \
    SPIFFS_UNLOCK(fs); \
    return (res); \
  }

#define SPIFFS_VALIDATE_OBJIX(ph, objid, spix) \
    if (((ph).flags & SPIFFS_PH_FLAG_USED) != 0) return SPIFFS_ERR_IS_FREE; \
    if (((ph).flags & SPIFFS_PH_FLAG_DELET) == 0) return SPIFFS_ERR_DELETED; \
    if (((ph).flags & SPIFFS_PH_FLAG_FINAL) != 0) return SPIFFS_ERR_NOT_FINALIZED; \
    if (((ph).flags & SPIFFS_PH_FLAG_INDEX) != 0) return SPIFFS_ERR_NOT_INDEX; \
    if (((objid) & SPIFFS_OBJ_ID_IX_FLAG) == 0) return SPIFFS_ERR_NOT_INDEX; \
    if ((ph).span_ix != (spix)) return SPIFFS_ERR_INDEX_SPAN_MISMATCH;
    //如果（（spix）==0&&（ph）。flags&SPIFFS_PH_FLAG_IXDELE）==0）返回SPIFFS_ERROR_DELETED；

#define SPIFFS_VALIDATE_DATA(ph, objid, spix) \
    if (((ph).flags & SPIFFS_PH_FLAG_USED) != 0) return SPIFFS_ERR_IS_FREE; \
    if (((ph).flags & SPIFFS_PH_FLAG_DELET) == 0) return SPIFFS_ERR_DELETED; \
    if (((ph).flags & SPIFFS_PH_FLAG_FINAL) != 0) return SPIFFS_ERR_NOT_FINALIZED; \
    if (((ph).flags & SPIFFS_PH_FLAG_INDEX) == 0) return SPIFFS_ERR_IS_INDEX; \
    if ((objid) & SPIFFS_OBJ_ID_IX_FLAG) return SPIFFS_ERR_IS_INDEX; \
    if ((ph).span_ix != (spix)) return SPIFFS_ERR_DATA_SPAN_MISMATCH;


// 检查id，仅访问匹配的objec id
#define SPIFFS_VIS_CHECK_ID     (1<<0)
// 将参数对象id报告给访问者-否则将报告对象查找id
#define SPIFFS_VIS_CHECK_PH     (1<<1)
// 在所有查找页的末尾停止搜索
#define SPIFFS_VIS_NO_WRAP      (1<<2)

#if SPIFFS_HAL_CALLBACK_EXTRA

#define SPIFFS_HAL_WRITE(_fs, _paddr, _len, _src) \
  (_fs)->cfg.hal_write_f((_fs), (_paddr), (_len), (_src))
#define SPIFFS_HAL_READ(_fs, _paddr, _len, _dst) \
  (_fs)->cfg.hal_read_f((_fs), (_paddr), (_len), (_dst))
#define SPIFFS_HAL_ERASE(_fs, _paddr, _len) \
  (_fs)->cfg.hal_erase_f((_fs), (_paddr), (_len))

#else // SPIFFS_HAL_CALLBACK_EXTRA

#define SPIFFS_HAL_WRITE(_fs, _paddr, _len, _src) \
  (_fs)->cfg.hal_write_f((_paddr), (_len), (_src))
#define SPIFFS_HAL_READ(_fs, _paddr, _len, _dst) \
  (_fs)->cfg.hal_read_f((_paddr), (_len), (_dst))
#define SPIFFS_HAL_ERASE(_fs, _paddr, _len) \
  (_fs)->cfg.hal_erase_f((_paddr), (_len))

#endif // SPIFFS_HAL_CALLBACK_EXTRA

#if SPIFFS_CACHE

#define SPIFFS_CACHE_FLAG_DIRTY       (1<<0)
#define SPIFFS_CACHE_FLAG_WRTHRU      (1<<1)
#define SPIFFS_CACHE_FLAG_OBJLU       (1<<2)
#define SPIFFS_CACHE_FLAG_OBJIX       (1<<3)
#define SPIFFS_CACHE_FLAG_DATA        (1<<4)
#define SPIFFS_CACHE_FLAG_TYPE_WR     (1<<7)

#define SPIFFS_CACHE_PAGE_SIZE(fs) \
  (sizeof(spiffs_cache_page) + SPIFFS_CFG_LOG_PAGE_SZ(fs))

#define spiffs_get_cache(fs) \
  ((spiffs_cache *)((fs)->cache))

#define spiffs_get_cache_page_hdr(fs, c, ix) \
  ((spiffs_cache_page *)(&((c)->cpages[(ix) * SPIFFS_CACHE_PAGE_SIZE(fs)])))

#define spiffs_get_cache_page(fs, c, ix) \
  ((u8_t *)(&((c)->cpages[(ix) * SPIFFS_CACHE_PAGE_SIZE(fs)])) + sizeof(spiffs_cache_page))

// 缓存页结构
typedef struct {
  // 缓存标志
  u8_t flags;
  // 缓存页索引
  u8_t ix;
  // 上次访问此缓存页
  u32_t last_access;
  union {
    // 类型读取缓存
    struct {
      // 读缓存页索引
      spiffs_page_ix pix;
    };
#if SPIFFS_CACHE_WR
    // 类型写缓存
    struct {
      // 写缓存
      spiffs_obj_id obj_id;
      // 缓存页中的偏移量
      u32_t offset;
      // 缓存页大小
      u16_t size;
    };
#endif
  };
} spiffs_cache_page;

// 缓存结构
typedef struct {
  u8_t cpage_count;
  u32_t last_access;
  u32_t cpage_use_map;
  u32_t cpage_use_mask;
  u8_t *cpages;
} spiffs_cache;

#endif


// spiffs nucleus文件描述符
typedef struct {
  // 此描述符的文件系统
  spiffs *fs;
  // 文件描述符的数量-如果为0，则关闭文件描述符
  spiffs_file file_nbr;
  // 对象id-如果SPIFFS_OBC_id_ERASED，则文件已删除
  spiffs_obj_id obj_id;
  // 文件的大小
  u32_t size;
  // 缓存对象索引头页索引
  spiffs_page_ix objix_hdr_pix;
  // 缓存的偏移量对象索引页索引
  spiffs_page_ix cursor_objix_pix;
  // 缓存的偏移量对象索引范围索引
  spiffs_span_ix cursor_objix_spix;
  // 电流绝对偏移
  u32_t offset;
  // 当前文件描述符偏移量（缓存）
  u32_t fdoffset;
  // fd标志
  spiffs_flags flags;
#if SPIFFS_CACHE_WR
  spiffs_cache_page *cache_page;
#endif
#if SPIFFS_TEMPORAL_FD_CACHE
  // 文件名的djb2哈希
  u32_t name_hash;
  // 命中分数（分数==0表示从未使用fd）
  u16_t score;
#endif
#if SPIFFS_IX_MAP
  // 溢出索引映射，如果为0，则表示未映射
  spiffs_ix_map *ix_map;
#endif
} spiffs_fd;


// 对象结构

// 页面标题，除对象查找页面外的每个页面的一部分
// 注意：当数据页是对象索引时，这总是对齐的，
// 在本例中，使用structspiffs_page_object_ix
typedef struct SPIFFS_PACKED {
  // 对象id
  spiffs_obj_id obj_id;
  // 对象跨度索引
  spiffs_span_ix span_ix;
  // 旗帜
  u8_t flags;
} spiffs_page_header;

// 对象索引标题页标题
typedef struct SPIFFS_PACKED
#if SPIFFS_ALIGNED_OBJECT_INDEX_TABLES
                __attribute(( aligned(sizeof(spiffs_page_ix)) ))
#endif
{
  // 公共页眉
  spiffs_page_header p_hdr;
  // 对齐
  u8_t _align[4 - ((sizeof(spiffs_page_header)&3)==0 ? 4 : (sizeof(spiffs_page_header)&3))];
  // 对象的大小
  u32_t size;
  // 对象的类型
  spiffs_obj_type type;
  // 对象的名称
  u8_t name[SPIFFS_OBJ_NAME_LEN];
#if SPIFFS_OBJ_META_LEN
  // 元数据。SPIFFS不会以任何方式解释。
  u8_t meta[SPIFFS_OBJ_META_LEN];
#endif
} spiffs_page_object_ix_header;

// 对象索引页标题
typedef struct SPIFFS_PACKED {
 spiffs_page_header p_hdr;
 u8_t _align[4 - ((sizeof(spiffs_page_header)&3)==0 ? 4 : (sizeof(spiffs_page_header)&3))];
} spiffs_page_object_ix;

// 对象查找访问者的回调函数
typedef s32_t (*spiffs_visitor_f)(spiffs *fs, spiffs_obj_id id, spiffs_block_ix bix, int ix_entry,
    const void *user_const_p, void *user_var_p);


#if SPIFFS_CACHE
#define _spiffs_rd(fs, op, fh, addr, len, dst) \
    spiffs_phys_rd((fs), (op), (fh), (addr), (len), (dst))
#define _spiffs_wr(fs, op, fh, addr, len, src) \
    spiffs_phys_wr((fs), (op), (fh), (addr), (len), (src))
#else
#define _spiffs_rd(fs, op, fh, addr, len, dst) \
    spiffs_phys_rd((fs), (addr), (len), (dst))
#define _spiffs_wr(fs, op, fh, addr, len, src) \
    spiffs_phys_wr((fs), (addr), (len), (src))
#endif

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

// ---------------

s32_t spiffs_phys_rd(
    spiffs *fs,
#if SPIFFS_CACHE
    u8_t op,
    spiffs_file fh,
#endif
    u32_t addr,
    u32_t len,
    u8_t *dst);

s32_t spiffs_phys_wr(
    spiffs *fs,
#if SPIFFS_CACHE
    u8_t op,
    spiffs_file fh,
#endif
    u32_t addr,
    u32_t len,
    u8_t *src);

s32_t spiffs_phys_cpy(
    spiffs *fs,
    spiffs_file fh,
    u32_t dst,
    u32_t src,
    u32_t len);

s32_t spiffs_phys_count_free_blocks(
    spiffs *fs);

s32_t spiffs_obj_lu_find_entry_visitor(
    spiffs *fs,
    spiffs_block_ix starting_block,
    int starting_lu_entry,
    u8_t flags,
    spiffs_obj_id obj_id,
    spiffs_visitor_f v,
    const void *user_const_p,
    void *user_var_p,
    spiffs_block_ix *block_ix,
    int *lu_entry);

s32_t spiffs_erase_block(
    spiffs *fs,
    spiffs_block_ix bix);

#if SPIFFS_USE_MAGIC && SPIFFS_USE_MAGIC_LENGTH
s32_t spiffs_probe(
    spiffs_config *cfg);
#endif // SPIFFS_USE_MAGIC && SPIFFS_USE_MAGIC_LENGTH

// ---------------

s32_t spiffs_obj_lu_scan(
    spiffs *fs);

s32_t spiffs_obj_lu_find_free_obj_id(
    spiffs *fs,
    spiffs_obj_id *obj_id,
    const u8_t *conflicting_name);

s32_t spiffs_obj_lu_find_free(
    spiffs *fs,
    spiffs_block_ix starting_block,
    int starting_lu_entry,
    spiffs_block_ix *block_ix,
    int *lu_entry);

s32_t spiffs_obj_lu_find_id(
    spiffs *fs,
    spiffs_block_ix starting_block,
    int starting_lu_entry,
    spiffs_obj_id obj_id,
    spiffs_block_ix *block_ix,
    int *lu_entry);

s32_t spiffs_obj_lu_find_id_and_span(
    spiffs *fs,
    spiffs_obj_id obj_id,
    spiffs_span_ix spix,
    spiffs_page_ix exclusion_pix,
    spiffs_page_ix *pix);

s32_t spiffs_obj_lu_find_id_and_span_by_phdr(
    spiffs *fs,
    spiffs_obj_id obj_id,
    spiffs_span_ix spix,
    spiffs_page_ix exclusion_pix,
    spiffs_page_ix *pix);

// ---------------

s32_t spiffs_page_allocate_data(
    spiffs *fs,
    spiffs_obj_id obj_id,
    spiffs_page_header *ph,
    u8_t *data,
    u32_t len,
    u32_t page_offs,
    u8_t finalize,
    spiffs_page_ix *pix);

s32_t spiffs_page_move(
    spiffs *fs,
    spiffs_file fh,
    u8_t *page_data,
    spiffs_obj_id obj_id,
    spiffs_page_header *page_hdr,
    spiffs_page_ix src_pix,
    spiffs_page_ix *dst_pix);

s32_t spiffs_page_delete(
    spiffs *fs,
    spiffs_page_ix pix);

// ---------------

s32_t spiffs_object_create(
    spiffs *fs,
    spiffs_obj_id obj_id,
    const u8_t name[],
    const u8_t meta[],
    spiffs_obj_type type,
    spiffs_page_ix *objix_hdr_pix);

s32_t spiffs_object_update_index_hdr(
    spiffs *fs,
    spiffs_fd *fd,
    spiffs_obj_id obj_id,
    spiffs_page_ix objix_hdr_pix,
    u8_t *new_objix_hdr_data,
    const u8_t name[],
    const u8_t meta[],
    u32_t size,
    spiffs_page_ix *new_pix);

#if SPIFFS_IX_MAP

s32_t spiffs_populate_ix_map(
    spiffs *fs,
    spiffs_fd *fd,
    u32_t vec_entry_start,
    u32_t vec_entry_end);

#endif

void spiffs_cb_object_event(
    spiffs *fs,
    spiffs_page_object_ix *objix,
    int ev,
    spiffs_obj_id obj_id,
    spiffs_span_ix spix,
    spiffs_page_ix new_pix,
    u32_t new_size);

s32_t spiffs_object_open_by_id(
    spiffs *fs,
    spiffs_obj_id obj_id,
    spiffs_fd *f,
    spiffs_flags flags,
    spiffs_mode mode);

s32_t spiffs_object_open_by_page(
    spiffs *fs,
    spiffs_page_ix pix,
    spiffs_fd *f,
    spiffs_flags flags,
    spiffs_mode mode);

s32_t spiffs_object_append(
    spiffs_fd *fd,
    u32_t offset,
    u8_t *data,
    u32_t len);

s32_t spiffs_object_modify(
    spiffs_fd *fd,
    u32_t offset,
    u8_t *data,
    u32_t len);

s32_t spiffs_object_read(
    spiffs_fd *fd,
    u32_t offset,
    u32_t len,
    u8_t *dst);

s32_t spiffs_object_truncate(
    spiffs_fd *fd,
    u32_t new_len,
    u8_t remove_object);

s32_t spiffs_object_find_object_index_header_by_name(
    spiffs *fs,
    const u8_t name[SPIFFS_OBJ_NAME_LEN],
    spiffs_page_ix *pix);

// ---------------

s32_t spiffs_gc_check(
    spiffs *fs,
    u32_t len);

s32_t spiffs_gc_erase_page_stats(
    spiffs *fs,
    spiffs_block_ix bix);

s32_t spiffs_gc_find_candidate(
    spiffs *fs,
    spiffs_block_ix **block_candidate,
    int *candidate_count,
    char fs_crammed);

s32_t spiffs_gc_clean(
    spiffs *fs,
    spiffs_block_ix bix);

s32_t spiffs_gc_quick(
    spiffs *fs, u16_t max_free_pages);

// ---------------

s32_t spiffs_fd_find_new(
    spiffs *fs,
    spiffs_fd **fd,
    const char *name);

s32_t spiffs_fd_return(
    spiffs *fs,
    spiffs_file f);

s32_t spiffs_fd_get(
    spiffs *fs,
    spiffs_file f,
    spiffs_fd **fd);

#if SPIFFS_TEMPORAL_FD_CACHE
void spiffs_fd_temporal_cache_rehash(
    spiffs *fs,
    const char *old_path,
    const char *new_path);
#endif

#if SPIFFS_CACHE
void spiffs_cache_init(
    spiffs *fs);

void spiffs_cache_drop_page(
    spiffs *fs,
    spiffs_page_ix pix);

#if SPIFFS_CACHE_WR
spiffs_cache_page *spiffs_cache_page_allocate_by_fd(
    spiffs *fs,
    spiffs_fd *fd);

void spiffs_cache_fd_release(
    spiffs *fs,
    spiffs_cache_page *cp);

spiffs_cache_page *spiffs_cache_page_get_by_fd(
    spiffs *fs,
    spiffs_fd *fd);
#endif
#endif

s32_t spiffs_lookup_consistency_check(
    spiffs *fs,
    u8_t check_all_objects);

s32_t spiffs_page_consistency_check(
    spiffs *fs);

s32_t spiffs_object_index_consistency_check(
    spiffs *fs);

// memcpy宏，
// 签入测试生成，否则为纯memcpy（除非已定义）
#ifdef _SPIFFS_TEST
#define _SPIFFS_MEMCPY(__d, __s, __l) do { \
    intptr_t __a1 = (intptr_t)((u8_t*)(__s)); \
    intptr_t __a2 = (intptr_t)((u8_t*)(__s)+(__l)); \
    intptr_t __b1 = (intptr_t)((u8_t*)(__d)); \
    intptr_t __b2 = (intptr_t)((u8_t*)(__d)+(__l)); \
    if (__a1 <= __b2 && __b1 <= __a2) { \
      printf("FATAL OVERLAP: memcpy from %lx..%lx to %lx..%lx\n", __a1, __a2, __b1, __b2); \
      ERREXIT(); \
    } \
    memcpy((__d),(__s),(__l)); \
} while (0)
#else
#ifndef _SPIFFS_MEMCPY
#define _SPIFFS_MEMCPY(__d, __s, __l) do{memcpy((__d),(__s),(__l));}while(0)
#endif
#endif //_SPIFFS_TEST

#endif /* SPIFFS_NUCLEUS_H_ */

