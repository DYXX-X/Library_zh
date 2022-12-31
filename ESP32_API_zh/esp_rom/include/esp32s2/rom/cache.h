// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _ROM_CACHE_H_
#define _ROM_CACHE_H_


#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup cache_apis，缓存操作相关api
  * @brief 缓存api
  */

/** @addtogroup 缓存_ pis@{
  */

#define MIN_CACHE_SIZE                  8192
#define MAX_CACHE_SIZE                  16384
#define MIN_CACHE_WAYS                  4
#define MAX_CACHE_WAYS                  4
#define MIN_CACHE_LINE_SIZE             16
//通常应为（MAX_CACHE_SIZE/MIN_CACHE_WAYS/MIN_CCHEE_LINE_SIZE），然而，这些项并非都在一个标记内存块中。
#define MAX_TAG_BLOCK_ITEMS             (MAX_CACHE_SIZE / 8 / MIN_CACHE_LINE_SIZE)
#define TAG_SIZE                        4
#define MAX_TAG_BLOCK_SIZE              (MAX_TAG_BLOCK_ITEMS * TAG_SIZE)

#define INVALID_PHY_PAGE 0xffff
#define ESP_CACHE_TEMP_ADDR DROM0_ADDRESS_LOW
#define CACHE_MAX_OPERATION_SIZE BUS_ADDR_SIZE


typedef enum {
    CACHE_DCACHE = 0,
    CACHE_ICACHE = 1,
} cache_t;

typedef enum {
    CACHE_MEMORY_INVALID = 0,
    CACHE_MEMORY_ICACHE_LOW = 1<<0,
    CACHE_MEMORY_ICACHE_HIGH = 1<<1,
    CACHE_MEMORY_DCACHE_LOW = 1<<2,
    CACHE_MEMORY_DCACHE_HIGH = 1<<3,
} cache_layout_t;

#define CACHE_SIZE_8KB  CACHE_SIZE_HALF
#define CACHE_SIZE_16KB CACHE_SIZE_FULL
typedef enum {
    CACHE_SIZE_HALF = 0,                /*!< 8KB用于icache和dcache*/
    CACHE_SIZE_FULL = 1,                /*!< 16KB用于icache和dcache*/
} cache_size_t;

typedef enum {
    CACHE_4WAYS_ASSOC = 0,              /*!< 4路关联缓存*/
} cache_ways_t;

typedef enum {
    CACHE_LINE_SIZE_16B = 0,            /*!< 16字节缓存行大小*/
    CACHE_LINE_SIZE_32B = 1,            /*!< 32字节缓存行大小*/
} cache_line_size_t;

typedef enum {
    CACHE_AUTOLOAD_POSITIVE = 0,        /*!< 缓存自动加载步骤为正*/
    CACHE_AUTOLOAD_NEGATIVE = 1,        /*!< 缓存自动加载步骤为负*/
} cache_autoload_order_t;

#define CACHE_AUTOLOAD_STEP(i) ((i) - 1)

typedef enum {
    CACHE_AUTOLOAD_MISS_TRIGGER = 0,    /*!< 仅由缓存未命中触发自动加载*/
    CACHE_AUTOLOAD_HIT_TRIGGER  = 1,    /*!< 仅由缓存命中触发自动加载*/
    CACHE_AUTOLOAD_BOTH_TRIGGER = 2,    /*!< 由缓存未命中和命中触发的自动加载*/
} cache_autoload_trigger_t;

struct cache_mode {
    uint32_t cache_size;                /*!< 缓存大小（字节）*/
    uint16_t cache_line_size;           /*!< 缓存行大小（字节）*/
    uint8_t cache_ways;                 /*!< 缓存方式，始终为4*/
    uint8_t icache;                     /*!< 缓存索引，0表示dcache，1表示icache*/
};

struct tag_item {
    uint32_t dirty:1;                   /*!< 缓存行值是否脏*/
    uint32_t tag:14;                    /*!< 标签是高速缓存地址的高部分，但是只有16MB的范围，没有低部分*/
    uint32_t valid:1;                   /*!< 标记项是否有效*/
    uint32_t fifo_cnt:3;                /*!< fifo cnt，0~3用于4路缓存，0~7用于8路缓存*/
    uint32_t lock:1;                    /*!< 缓存行是否锁定*/
    uint32_t attr:3;                    /*!< 外部内存物理地址的属性*/
    uint32_t access:1;                  /*!< 软件可访问，由硬件使用*/
    uint32_t reserved:8;
};

struct autoload_config {
    uint8_t order;                      /*!< 自动加载步骤为正或负*/
    uint8_t trigger;                    /*!< 自动加载触发器*/
    uint8_t ena0;                       /*!< 自动加载区域0启用*/
    uint8_t ena1;                       /*!< 自动加载区域1启用*/
    uint32_t addr0;                     /*!< 自动加载区域0起始地址*/
    uint32_t size0;                     /*!< 自动加载区域0大小*/
    uint32_t addr1;                     /*!< 自动加载区域1起始地址*/
    uint32_t size1;                     /*!< 自动加载区域1大小*/
};

struct tag_group_info {
    struct cache_mode mode;                         /*!< 缓存和缓存模式*/
    uint32_t filter_addr;                           /*!< 用于生成结构的地址*/
    uint32_t vaddr_offset;		            /*!< 缓存方式的虚拟地址偏移*/
    uint32_t tag_addr[MAX_CACHE_WAYS];              /*!< 标记内存地址，只有[0~mode.ways-1]可以使用*/
    uint32_t cache_memory_offset[MAX_CACHE_WAYS];   /*!< 缓存内存地址，只有[0~mode.ways-1]可以使用*/
};

struct lock_config {
    uint32_t addr;                                  /*!< 手动锁定地址*/
    uint16_t size;                                  /*!< 手动锁尺寸*/
    uint16_t group;                                 /*!< 手动锁定组，0或1*/
};

#define ESP_ROM_ERR_INVALID_ARG         1
#define MMU_SET_ADDR_ALIGNED_ERROR      2
#define MMU_SET_PASE_SIZE_ERROR         3
#define MMU_SET_VADDR_OUT_RANGE         4

/**
  * @brief 初始化缓存mmu，将所有条目标记为无效。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void Cache_MMU_Init(void);

/**
  * @brief 设置ICache mmu映射。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t ext_ram：DPORT_MMU_ACCESS_FLASH表示闪存，DPORT_MMU_ACCESS_SPIRAM表示螺旋，DPORT-MMU_INVALID表示无效。
  *
  * @param  uint32_t vaddr：CPU地址空间中的虚拟地址。可以是Iram0、Iram1、Irom0、Drom0和AHB总线地址。应按psize对齐。
  *
  * @param  uint32_t paddr：外部内存中的物理地址。应按psize对齐。
  *
  * @param  uint32_t psize：ICache的页面大小，以KB为单位。这里应该是64。
  *
  * @param  uint32_t num：要设置的页面。
  *
  * @param  uint32_t 修复：0表示物理页面随虚拟页面增长，其他表示虚拟页面映射到同一物理页面。
  *
  * @return uint32_t：错误状态0:mmu设置成功2:vaddr或paddr未对齐3:psize错误4:vaddr超出范围
  */
int Cache_Ibus_MMU_Set(uint32_t ext_ram, uint32_t vaddr, uint32_t paddr,  uint32_t psize, uint32_t num, uint32_t fixed);

/**
  * @brief 设置DCache mmu映射。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t ext_ram：DPORT_MMU_ACCESS_FLASH表示闪存，DPORT_MMU_ACCESS_SPIRAM表示螺旋，DPORT-MMU_INVALID表示无效。
  *
  * @param  uint32_t vaddr：CPU地址空间中的虚拟地址。可以是DRam0、DRam1、DRom0、DPort和AHB总线地址。应按psize对齐。
  *
  * @param  uint32_t paddr：外部内存中的物理地址。应按psize对齐。
  *
  * @param  uint32_t psize：DCache的页面大小，以KB为单位。这里应该是64。
  *
  * @param  uint32_t num：要设置的页面。

  * @param  uint32_t 修复：0表示物理页面随虚拟页面增长，其他表示虚拟页面映射到同一物理页面。
  *
  * @return uint32_t：错误状态0:mmu设置成功2:vaddr或paddr未对齐3:psize错误4:vaddr超出范围
  */
int Cache_Dbus_MMU_Set(uint32_t ext_ram, uint32_t vaddr, uint32_t paddr, uint32_t psize, uint32_t num, uint32_t fixed);

/**
  * @brief 计算映射到Flash的总线室地址中的页面。请不要在SDK应用程序中调用此函数。
  *
  * @param uint32_t 公共汽车：用来计数的公共汽车。
  *
  * @param uint32_t *page0mapped：值应为用户的初始值，0表示未映射，其他表示映射计数。
  *
  * return uint32_t：映射到Flash的页面数。
  */
uint32_t Cache_Count_Flash_Pages(uint32_t bus, uint32_t * page0_mapped);

/**
  * @brief 将指令或rodata从Flash复制到SPIRAM，然后重新映射到SPIRAM。请不要在SDK应用程序中调用此函数。
  *
  * @param uint32_t bus：需要复制到SPIRAM的总线。
  *
  * @param uint32_t bus_start_addr：总线的起始虚拟地址。
  *
  * @param uint32_t start_page：SPIRAM中的起始（64KB）页码。
  *
  * @param uint32_t *page0_page：SPIRAM页码中的flash page0，0xffff表示无效。
  *
  * return uint32_t：未映射SPIRAM的下一个起始页码。
  */
uint32_t Cache_Flash_To_SPIRAM_Copy(uint32_t bus, uint32_t bus_start_addr, uint32_t start_page, uint32_t * page0_page);


/**
  * @brief 分配ICache和DCache使用的内存。请不要在SDK应用程序中调用此函数。
  *
  * @param cache_layout_t sram0_layout：第一个8KB内部内存块的用法，可以是CACHE_memory_INVALID、CACHE_MMEMORY_ICACHE_LOW、CACHE_memory_ICACHE_HIGH、CACHE.memory_DCACHE_LOW和CACHE_MEM ORY_DCACHE_HIGH
  *
  * @param cache_layout_t sram1_layout：第二个8KB内部内存块的使用
  *
  * @param cache_layout_t sram2_layout：第三个8KB内部内存块的使用情况
  *
  * @param cache_layout_t sram3_layout：第四个8KB内部内存块的使用
  *
  * 不返回
  */
void Cache_Allocate_SRAM(cache_layout_t sram0_layout, cache_layout_t sram1_layout, cache_layout_t sram2_layout, cache_layout_t sram3_layout);

/**
  * @brief 获取ICache或DCache的缓存模式。请不要在SDK应用程序中调用此函数。
  *
  * @param struct cache_mode*mode：缓存模式结构的指针，调用者应设置icache字段
  *
  * 不返回
  */
void Cache_Get_Mode(struct cache_mode * mode);

/**
  * @brief 设置ICache模式：缓存大小、关联方式和缓存行大小。请不要在SDK应用程序中调用此函数。
  *
  * @param cache_size_t cache_size：缓存大小，可以是cache_size_HALF和cache_SSIZE_FULL
  *
  * @param cache_ways_t 方式：缓存的关联方式，只能是cache_4WAYS_ASSOC
  *
  * @param cache_line_size_t cache_line_size：缓存行大小，可以是cache_line_size_16B、cache_line _size_32B
  *
  * 不返回
  */
void Cache_Set_ICache_Mode(cache_size_t cache_size, cache_ways_t ways, cache_line_size_t cache_line_size);

/**
  * @brief 设置DCache模式：缓存大小、关联方式和缓存行大小。请不要在SDK应用程序中调用此函数。
  *
  * @param cache_size_t cache_size：缓存大小，可以是cache_size_HALF和cache_SSIZE_FULL
  *
  * @param cache_ways_t 方式：缓存的关联方式，只能是cache_4WAYS_ASSOC
  *
  * @param cache_line_size_t cache_line_size：缓存行大小，可以是cache_line_size_16B、cache_line _size_32B
  *
  * 不返回
  */
void Cache_Set_DCache_Mode(cache_size_t cache_size, cache_ways_t ways, cache_line_size_t cache_line_size);

/**
  * @brief 检查地址是否通过ICache访问。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：要检查的地址。
  *
  * @return 如果地址是通过ICache访问的，则为1；如果不是，则为0。
  */
uint32_t Cache_Address_Through_ICache(uint32_t addr);

/**
  * @brief 检查地址是否通过DCache访问。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：要检查的地址。
  *
  * @return 如果通过DCache访问地址，则为1，否则为0。
  */
uint32_t Cache_Address_Through_DCache(uint32_t addr);

/**
  * @brief 使ICache的缓存项无效。将执行CACHE_LINE_SIZE对齐操作。如果该区域不在ICache地址室中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：要使无效的起始地址
  *
  * @param  uint32_t items：要使缓存行无效，items*cache_line_size不应超过总线地址大小（4MB）
  *
  * @return 没有一个
  */
void Cache_Invalidate_ICache_Items(uint32_t addr, uint32_t items);

/**
  * @brief 使DCache的缓存项无效。将执行CACHE_LINE_SIZE对齐操作。如果该区域不在DCache地址室中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：要使无效的起始地址
  *
  * @param  uint32_t items：要使缓存行无效，items*cache_line_size不应超过总线地址大小（4MB）
  *
  * @return 没有一个
  */
void Cache_Invalidate_DCache_Items(uint32_t addr, uint32_t items);

/**
  * @brief 清除DCache的缓存项的脏位。将执行CACHE_LINE_SIZE对齐操作。如果该区域不在DCache地址室中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：要清理的起始地址
  *
  * @param  uint32_t items：要使缓存行无效，items*cache_line_size不应超过总线地址大小（4MB）
  *
  * @return 没有一个
  */
void Cache_Clean_Items(uint32_t addr, uint32_t items);

/**
  * @brief 写回DCache的缓存项。将执行CACHE_LINE_SIZE对齐操作。如果该区域不在DCache地址室中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：要写回的起始地址
  *
  * @param  uint32_t items：要使缓存行无效，items*cache_line_size不应超过总线地址大小（4MB）
  *
  * @return 没有一个
  */
void Cache_WriteBack_Items(uint32_t addr, uint32_t items);

/**
  * @brief 使区域中的缓存项从ICache或DCache无效。如果该区域不在缓存地址空间中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：无效的区域起始地址。
  *
  * @param  uint32_t size：无效区域大小。
  *
  * @return 0表示成功1表示无效参数
  */
int Cache_Invalidate_Addr(uint32_t addr, uint32_t size);

/**
  * @brief 从DCache中清除区域中缓存项的脏位。如果该区域不在DCache地址室中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：已清理区域的起始地址。
  *
  * @param  uint32_t size：清洁区域大小。
  *
  * @return 0表示成功1表示无效参数
  */
int Cache_Clean_Addr(uint32_t addr, uint32_t size);

/**
  * @brief 从DCache中写回区域中的Cache项（同时清除脏位）。如果该区域不在DCache地址室中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：写回区域起始地址。
  *
  * @param  uint32_t size：写回区域大小。
  *
  * @return 0表示成功1表示无效参数
  */
int Cache_WriteBack_Addr(uint32_t addr, uint32_t size);


/**
  * @brief 使ICache中的所有缓存项无效。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void Cache_Invalidate_ICache_All(void);

/**
  * @brief 使DCache中的所有缓存项无效。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void Cache_Invalidate_DCache_All(void);

/**
  * @brief 清除DCache中所有缓存项的脏位。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void Cache_Clean_All(void);

/**
  * @brief 写回DCache中的所有缓存项。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void Cache_WriteBack_All(void);

/**
  * @brief 通过ICache和DCache屏蔽所有总线。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void Cache_Mask_All(void);

/**
  * @brief 通过ICache取消屏蔽DRom0总线。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void Cache_UnMask_Drom0(void);

/**
  * @brief 挂起ICache自动预加载操作，然后您可以在一些ICache操作后恢复它。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return uint32_t:0表示ICache在挂起前未自动预加载。
  */
uint32_t Cache_Suspend_ICache_Autoload(void);

/**
  * @brief 在一些ICache操作后恢复ICache自动预加载操作。请不要在SDK应用程序中调用此函数。
  *
  * @param uint32_t autoload：0表示ICache在挂起前未自动预加载。
  *
  * @return 没有一个
  */
void Cache_Resume_ICache_Autoload(uint32_t autoload);

/**
  * @brief 挂起DCache自动预加载操作，然后您可以在一些DCache操作后恢复它。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return uint32_t:0表示DCache在挂起前未自动预加载。
  */
uint32_t Cache_Suspend_DCache_Autoload(void);

/**
  * @brief 在执行一些DCache操作后，恢复DCache自动预加载操作。请不要在SDK应用程序中调用此函数。
  *
  * @param uint32_t autoload：0表示DCache在挂起前未自动预加载。
  *
  * @return 没有一个
  */
void Cache_Resume_DCache_Autoload(uint32_t autoload);

/**
  * @brief 启动ICache手动预加载，将暂停ICache的自动预加载。请不要在SDK应用程序中调用此函数。
  *
  * @param uint32_t addr：预加载区域的起始地址。
  *
  * @param uint32_t size：预加载区域的大小，不应超过ICache的大小。
  *
  * @param uint32_t order：预加载顺序，0表示正，其他表示负
  *
  * @return uint32_t:0表示ICache在手动预加载之前未自动预加载。
  */
uint32_t Cache_Start_ICache_Preload(uint32_t addr, uint32_t size, uint32_t order);

/**
  * @brief 如果ICache手动预加载完成，则返回。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return uint32_t:0表示ICache手动预加载未完成。
  */
uint32_t Cache_ICache_Preload_Done(void);

/**
  * @brief 结束ICache手动预加载以恢复ICache的自动预加载。请不要在SDK应用程序中调用此函数。
  *
  * @param uint32_t 自动加载：0表示ICache在手动预加载之前未自动预加载。
  *
  * @return 没有一个
  */
void Cache_End_ICache_Preload(uint32_t autoload);

/**
  * @brief 启动DCache手动预加载，将暂停DCache的自动预加载。请不要在SDK应用程序中调用此函数。
  *
  * @param uint32_t addr：预加载区域的起始地址。
  *
  * @param uint32_t size：预加载区域的大小，不应超过DCache的大小。
  *
  * @param uint32_t order：预加载顺序，0表示正，其他表示负
  *
  * @return uint32_t:0表示DCache在手动预加载之前未自动预加载。
  */
uint32_t Cache_Start_DCache_Preload(uint32_t addr, uint32_t size, uint32_t order);

/**
  * @brief 如果DCache手动预加载完成，则返回。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return uint32_t:0表示未完成DCache手动预加载。
  */
uint32_t Cache_DCache_Preload_Done(void);

/**
  * @brief 结束DCache手动预加载以恢复DCache的自动预加载。请不要在SDK应用程序中调用此函数。
  *
  * @param uint32_t 自动加载：0表示DCache在手动预加载之前未自动预加载。
  *
  * @return 没有一个
  */
void Cache_End_DCache_Preload(uint32_t autoload);

/**
  * @brief 配置ICache的自动加载参数。请不要在SDK应用程序中调用此函数。
  *
  * @param struct autoload_config*配置：自动加载参数。
  *
  * @return 没有一个
  */
void Cache_Config_ICache_Autoload(const struct autoload_config * config);

/**
  * @brief 启用ICache的自动预加载。请不要在SDK应用程序中调用此函数。
  *
  * @param None
  *
  * @return 没有一个
  */
void Cache_Enable_ICache_Autoload(void);

/**
  * @brief 禁用ICache的自动预加载。请不要在SDK应用程序中调用此函数。
  *
  * @param None
  *
  * @return 没有一个
  */
void Cache_Disable_ICache_Autoload(void);

/**
  * @brief 配置DCache的自动加载参数。请不要在SDK应用程序中调用此函数。
  *
  * @param struct autoload_config*配置：自动加载参数。
  *
  * @return 没有一个
  */
void Cache_Config_DCache_Autoload(const struct autoload_config * config);

/**
  * @brief 启用DCache的自动预加载。请不要在SDK应用程序中调用此函数。
  *
  * @param None
  *
  * @return 没有一个
  */
void Cache_Enable_DCache_Autoload(void);

/**
  * @brief 禁用DCache的自动预加载。请不要在SDK应用程序中调用此函数。
  *
  * @param None
  *
  * @return 没有一个
  */
void Cache_Disable_DCache_Autoload(void);

/**
  * @brief 配置ICache的一组预锁定参数。请不要在SDK应用程序中调用此函数。
  *
  * @param struct lock_config*config：一组锁参数。
  *
  * @return 没有一个
  */

void Cache_Enable_ICache_PreLock(const struct lock_config *config);

/**
  * @brief 禁用ICache的一组预锁定参数。但是，锁定的数据不会被释放。请不要在SDK应用程序中调用此函数。
  *
  * @param uint16_t 组：0代表组0，1代表组1。
  *
  * @return 没有一个
  */
void Cache_Disable_ICache_PreLock(uint16_t group);

/**
  * @brief 锁定ICache的缓存项。将执行CACHE_LINE_SIZE对齐操作。如果该区域不在ICache地址室中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：要锁定的起始地址
  *
  * @param  uint32_t items：要锁定的缓存行，items*cache_line_size不应超过总线地址大小（4MB）
  *
  * @return 没有一个
  */
void Cache_Lock_ICache_Items(uint32_t addr, uint32_t items);

/**
  * @brief 解锁ICache的缓存项。将执行CACHE_LINE_SIZE对齐操作。如果该区域不在ICache地址室中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：要解锁的起始地址
  *
  * @param  uint32_t items：要解锁的缓存行，items*cache_line_size不应超过总线地址大小（4MB）
  *
  * @return 没有一个
  */
void Cache_Unlock_ICache_Items(uint32_t addr, uint32_t items);

/**
  * @brief 配置DCache的一组预锁定参数。请不要在SDK应用程序中调用此函数。
  *
  * @param struct lock_config*config：一组锁参数。
  *
  * @return 没有一个
  */
void Cache_Enable_DCache_PreLock(const struct lock_config *config);

/**
  * @brief 禁用DCache的一组预锁定参数。但是，锁定的数据不会被释放。请不要在SDK应用程序中调用此函数。
  *
  * @param uint16_t 组：0代表组0，1代表组1。
  *
  * @return 没有一个
  */
void Cache_Disable_DCache_PreLock(uint16_t group);

/**
  * @brief 锁定DCache的缓存项。将执行CACHE_LINE_SIZE对齐操作。如果该区域不在DCache地址室中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：要锁定的起始地址
  *
  * @param  uint32_t items：要锁定的缓存行，items*cache_line_size不应超过总线地址大小（4MB）
  *
  * @return 没有一个
  */
void Cache_Lock_DCache_Items(uint32_t addr, uint32_t items);

/**
  * @brief 解锁DCache的缓存项。将执行CACHE_LINE_SIZE对齐操作。如果该区域不在DCache地址室中，则不会执行任何操作。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t addr：要解锁的起始地址
  *
  * @param  uint32_t items：要解锁的缓存行，items*cache_line_size不应超过总线地址大小（4MB）
  *
  * @return 没有一个
  */
void Cache_Unlock_DCache_Items(uint32_t addr, uint32_t items);

/**
  * @brief 为ICache或DCache锁定标记内存中的缓存项。请不要在SDK应用程序中调用此函数。
  *
  * @param uint32_t addr：锁定区域的起始地址。
  *
  * @param uint32_t size：锁定区域的大小。
  *
  * @return 0表示成功1表示无效参数
  */
int Cache_Lock_Addr(uint32_t addr, uint32_t size);

/**
  * @brief 为ICache或DCache解锁标记内存中的缓存项。请不要在SDK应用程序中调用此函数。
  *
  * @param uint32_t addr：解锁区域的起始地址。
  *
  * @param uint32_t size：解锁区域的大小。
  *
  * @return 0表示成功1表示无效参数
  */
int Cache_Unlock_Addr(uint32_t addr, uint32_t size);

/**
  * @brief 禁用cpu的ICache访问。此操作将使所有ICache标记内存无效，CPU无法访问ICache，ICache将保持空闲。请不要在SDK应用程序中调用此函数。
  *
  * @return uint32_t：之前已启用自动预加载
  */
uint32_t Cache_Disable_ICache(void);

/**
  * @brief 启用cpu的ICache访问。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t 自动加载：然后ICache将预加载。
  *
  * @return 没有一个
  */
void Cache_Enable_ICache(uint32_t autoload);

/**
  * @brief 禁用cpu的DCache访问。此操作将使所有DCache标记内存无效，CPU无法访问DCache，DCache将保持空闲。请不要在SDK应用程序中调用此函数。
  *
  * @return uint32_t：之前已启用自动预加载
  */
uint32_t Cache_Disable_DCache(void);

/**
  * @brief 启用cpu的DCache访问。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t 自动加载：然后DCache将预加载。
  *
  * @return 没有一个
  */
void Cache_Enable_DCache(uint32_t autoload);

/**
  * @brief 暂停cpu的ICache访问。ICache标记内存仍在，CPU无法访问ICache，ICache将保持空闲。请不要更改MMU、缓存模式或标记内存（在某些特殊情况下可以更改标记内存）。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return uint32_t：之前已启用自动预加载
  */
uint32_t Cache_Suspend_ICache(void);

/**
  * @brief 恢复cpu的ICache访问。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t 自动加载：然后ICache将预加载。
  *
  * @return 没有一个
  */
void Cache_Resume_ICache(uint32_t autoload);

/**
  * @brief 暂停cpu的DCache访问。ICache标签内存仍在，CPU无法访问DCache，DCache将保持空闲。×请不要更改MMU、缓存模式或标记内存（在某些特殊情况下可以更改标记内存）。请不要在SDK应用程序中调用此函数。
  *
  * @param  None
  *
  * @return uint32_t：之前已启用自动预加载
  */
uint32_t Cache_Suspend_DCache(void);

/**
  * @brief 恢复cpu的DCache访问。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t 自动加载：然后DCache将预加载。
  *
  * @return 没有一个
  */
void Cache_Resume_DCache(uint32_t autoload);

/**
  * @brief 获取ICache缓存行大小
  *
  * @param  None
  *
  * @return uint32_t:16，32字节
  */
uint32_t Cache_Get_ICache_Line_Size(void);

/**
  * @brief 获取DCache缓存行大小
  *
  * @param  None
  *
  * @return uint32_t:16，32字节
  */
uint32_t Cache_Get_DCache_Line_Size(void);

/**
  * @brief 从启动设置默认模式，8KB ICache，16Byte缓存行大小。
  *
  * @param  None
  *
  * @return 没有一个
  */
void Cache_Set_Default_Mode(void);

/**
  * @brief 从启动设置默认模式，8KB DCache，16Byte缓存行大小。
  *
  * @param None
  *
  * @return 没有一个
  */
void Cache_Enable_Defalut_DCache_Mode(void);

/**
  * @brief 行程标签存储器，用于运行回拨功能。执行此操作时，ICache和DCache将挂起。回调将获得参数tag_group_info，其中包含一组标记内存地址和缓存内存地址。请不要在SDK应用程序中调用此函数。
  *
  * @param  struct cache_mode*模式：要检查的缓存和缓存模式。
  *
  * @param  uint32_t filter_addr：只有可能包含filter_address的缓存行将返回给回调函数。0表示不筛选，将返回所有缓存行。
  *
  * @param  void （*process）（structtag_group_info*）：回调函数，可以多次调用，一次调用一个组（组中的地址在缓存方式中位于同一位置）。
  *
  * @return 没有一个
  */
void Cache_Travel_Tag_Memory(struct cache_mode * mode, uint32_t filter_addr, void (* process)(struct tag_group_info *));

/**
  * @brief 从缓存模式、缓存标签和缓存方式的虚拟地址偏移中获取虚拟地址。请不要在SDK应用程序中调用此函数。
  *
  * @param  struct cache_mode*模式：用于计算虚拟地址和缓存模式的缓存。
  *
  * @param  uint32_t 标签：标签项的标签部分，12-14位。
  *
  * @param  uint32_t addr_offset：缓存通道的虚拟地址偏移量。
  *
  * @return uint32_t：虚拟地址。
  */
uint32_t Cache_Get_Virtual_Addr(struct cache_mode *mode, uint32_t tag, uint32_t vaddr_offset);

/**
  * @brief 获取缓存内存块基地址。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t icache：0代表dcache，其他代表icache。
  *
  * @param  uint32_t 高：0表示低部分块，1表示高部分块。
  *
  * @return uint32_t：缓存内存块基地址，如果未使用该块，则为0。
  */
uint32_t Cache_Get_Memory_BaseAddr(uint32_t icache, uint32_t high);

/**
  * @brief 从缓存模式、缓存内存偏移量和缓存方式的虚拟地址偏移量中获取缓存内存地址。请不要在SDK应用程序中调用此函数。
  *
  * @param  struct cache_mode*模式：用于计算虚拟地址和缓存模式的缓存。
  *
  * @param  uint32_t cache_memory_offset：缓存行的整个缓存（ICache或DCache）的缓存内存偏移量。
  *
  * @param  uint32_t addr_offset：缓存通道的虚拟地址偏移量。
  *
  * @return uint32_t：虚拟地址。
  */
uint32_t Cache_Get_Memory_Addr(struct cache_mode *mode, uint32_t cache_memory_offset, uint32_t vaddr_offset);

/**
  * @brief 通过DRAM地址获取缓存内存值。请不要在SDK应用程序中调用此函数。
  *
  * @param  uint32_t cache_memory_addr：缓存的DRAM地址。
  *
  * @return uint32_t：地址的字值。
  */
uint32_t Cache_Get_Memory_value(uint32_t cache_memory_addr);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* _ROM_CACHE_H_ */

