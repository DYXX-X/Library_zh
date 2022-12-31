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

#ifndef ESP_SPI_FLASH_H
#define ESP_SPI_FLASH_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "sdkconfig.h"
#include "esp_spi_flash_counters.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ERR_FLASH_OP_FAIL    (ESP_ERR_FLASH_BASE + 1)
#define ESP_ERR_FLASH_OP_TIMEOUT (ESP_ERR_FLASH_BASE + 2)

#define SPI_FLASH_SEC_SIZE  4096    /**<SPI闪存扇区大小*/

#define SPI_FLASH_MMU_PAGE_SIZE 0x10000 /**<闪存缓存MMU映射页面大小*/

typedef enum {
    FLASH_WRAP_MODE_8B = 0,
    FLASH_WRAP_MODE_16B = 2,
    FLASH_WRAP_MODE_32B = 4,
    FLASH_WRAP_MODE_64B = 6,
    FLASH_WRAP_MODE_DISABLE = 1
} spi_flash_wrap_mode_t;

/**
 * @brief 设置flash的换行模式
 *
 * @param mode: 包装模式支持禁用，16 32，64字节
 *
 * @return esp_err_t:esp_OK表示成功。
 *
 */
esp_err_t spi_flash_wrap_set(spi_flash_wrap_mode_t mode);

/**
 * @brief  初始化SPI闪存访问驱动程序
 *
 *  在调用任何其他spi_flash函数之前，该函数必须被调用一次。当前，此函数是从启动代码调用的。不需要从应用程序代码调用它。
 *
 */
void spi_flash_init(void);

/**
 * @brief  获取二进制图像标头中设置的闪存芯片大小
 *
 * @note 该值不一定与实际闪存大小匹配。
 *
 * @return 闪存芯片的大小，以字节为单位
 */
size_t spi_flash_get_chip_size(void);

/**
 * @brief  擦除闪存扇区。
 *
 * @param  sector: 扇区号，计数从扇区0开始，每个扇区4KB。
 *
 * @return 电子邮箱地址
 */
esp_err_t spi_flash_erase_sector(size_t sector);

/**
 * @brief  擦除一系列闪存扇区
 *
 * @param  start_address  必须开始擦除操作的地址。必须对齐4kB
 * @param  size  擦除范围的大小，以字节为单位。必须可被4kB整除。
 *
 * @return 电子邮箱地址
 */
esp_err_t spi_flash_erase_range(size_t start_address, size_t size);


/**
 * @brief  将数据写入闪存。
 *
 * @note 为了获得最快的写入性能，请从DRAM中的源缓冲区以4字节对齐的偏移量在闪存中写入4字节对齐大小。改变这些参数中的任何一个仍然有效，但由于缓冲，速度会变慢。
 *
 * @note 一次写入超过8KB的数据将分为多个写入操作，以避免中断系统中的其他任务。
 *
 * @param  dest_addr Flash中的目标地址。
 * @param  src       指向源缓冲区的指针。
 * @param  size      数据长度，以字节为单位。
 *
 * @return 电子邮箱地址
 */
esp_err_t spi_flash_write(size_t dest_addr, const void *src, size_t size);


/**
 * @brief  将加密数据写入Flash。
 *
 * @note 必须启用Flash加密才能使此功能正常工作。
 *
 * @note 调用此函数时必须启用Flash加密。如果禁用了闪存加密，函数将返回ESP_ERR_INVALID_STATE。使用esp_flash_encryption_enabled（）函数确定是否启用了闪存加密。
 *
 * @note dest_addr和size必须是16字节的倍数。为了获得绝对的最佳性能，dest_addr和size参数都应该是32字节的倍数。
 *
 * @param  dest_addr Flash中的目标地址。必须是16字节的倍数。
 * @param  src       指向源缓冲区的指针。
 * @param  size      数据长度，以字节为单位。必须是16字节的倍数。
 *
 * @return 电子邮箱地址
 */
esp_err_t spi_flash_write_encrypted(size_t dest_addr, const void *src, size_t size);

/**
 * @brief  从Flash读取数据。
 *
 * @note 为了获得最快的读取性能，所有参数都应为4字节对齐。如果源地址和读取大小不是4字节对齐的，则可以将读取拆分为多个闪存操作。如果目标缓冲区未对齐4字节，则将在堆栈上分配临时缓冲区。
 *
 * @note 一次读取超过16KB的数据将被分成多个读取，以避免中断系统中的其他任务。考虑使用spi_flash_map（）读取大量数据。
 *
 * @param  src_addr Flash中数据的源地址。
 * @param  dest     指向目标缓冲区的指针
 * @param  size     数据长度
 *
 *
 * @return 电子邮箱地址
 */
esp_err_t spi_flash_read(size_t src_addr, void *dest, size_t size);


/**
 * @brief  从加密闪存读取数据。
 *
 * 如果启用了闪存加密，该功能将在读取数据时透明地解密数据。如果未启用闪存加密，则此函数的行为与spi_flash_read（）相同。
 *
 * 请参阅esp_flash_encryption_enabled（）以获取检查是否启用了闪存加密的函数。
 *
 * @param  src   Flash中数据的源地址。
 * @param  dest  指向目标缓冲区的指针
 * @param  size  数据长度
 *
 * @return 电子邮箱地址
 */
esp_err_t spi_flash_read_encrypted(size_t src, void *dest, size_t size);

/**
 * @brief 指定mmap调用中请求的内存空间的枚举
 */
typedef enum {
    SPI_FLASH_MMAP_DATA,    /**<映射到数据存储器（Vaddr0），允许字节对齐访问，总共4 MB*/
    SPI_FLASH_MMAP_INST,    /**<映射到指令存储器（Vaddr1-3），仅允许4字节对齐访问，总共11 MB*/
} spi_flash_mmap_memory_t;

/**
 * @brief 从spi_flash_mmap获得的内存区域的不透明句柄。
 */
typedef uint32_t spi_flash_mmap_handle_t;

/**
 * @brief 将闪存区域映射到数据或指令地址空间
 *
 * 此功能分配足够数量的64kB MMU页面，并将其配置为将所请求的闪存区域映射到地址空间。它可以重用已经提供所需映射的MMU页面。
 *
 * 与任何分配器一样，如果mmap/munmap被大量使用，那么地址空间可能会变得支离破碎。要解决页面分配问题，请使用spi_flash_map_dump（）函数。
 *
 * @param src_addr  闪存中请求区域开始的物理地址。此地址必须与64kB边界对齐（SPI_FLASH_MMU_PAGE_SIZE）
 * @param size  要映射的区域的大小。此大小将舍入为64kB边界
 * @param memory  应映射区域的地址空间（数据或指令）
 * @param[out] out_ptr  输出，指向映射内存区域的指针
 * @param[out] out_handle  输出，应用于spi_flash_munmap调用的句柄
 *
 * @return  成功时为ESP_OK，如果无法分配页面，则为ESP_ERR_NO_MEM
 */
esp_err_t spi_flash_mmap(size_t src_addr, size_t size, spi_flash_mmap_memory_t memory,
                         const void** out_ptr, spi_flash_mmap_handle_t* out_handle);

/**
 * @brief 将闪存页面序列映射到数据或指令地址空间
 *
 * 此功能分配足够数量的64kB MMU页面，并将其配置为将所指示的闪存页面连续映射到地址空间。在这方面，它的工作方式与spi_flash_mmap（）类似，但它允许将一组（可能是非连续的）页面映射到一个连续的内存区域。
 *
 * @param pages 一个数字数组，表示闪存中64kB的页面将连续映射到内存中。这些指示64kB页的索引，而不是其他函数中使用的字节大小地址。数组必须位于内部内存中。
 * @param page_count  页面数组中的条目数
 * @param memory  应映射区域的地址空间（指令或数据）
 * @param[out] out_ptr  输出，指向映射内存区域的指针
 * @param[out] out_handle  输出，应用于spi_flash_munmap调用的句柄
 *
 * @return
 *      -成功时ESP_OK
 *      -如果无法分配页面，则为ESP_ERR_NO_MEM
 *      -如果页面计数为零或页面阵列不在内部内存中，则为ESP_ERR_INVALID_ARG
 */
esp_err_t spi_flash_mmap_pages(const int *pages, size_t page_count, spi_flash_mmap_memory_t memory,
                         const void** out_ptr, spi_flash_mmap_handle_t* out_handle);


/**
 * @brief 先前使用spi_flash_map获得的释放区域
 *
 * @note 调用此函数不一定会取消映射内存区域。只有在没有其他句柄引用此区域时，才会取消映射区域。在部分重叠区域的情况下，可能会部分取消映射内存。
 *
 * @param handle  从spi_flash_mmap获取的句柄
 */
void spi_flash_munmap(spi_flash_mmap_handle_t handle);

/**
 * @brief 显示有关映射区域的信息
 *
 * 此函数列出使用spi_flash_map获得的句柄，以及分配给每个句柄的页面范围。它还列出了MMU表的所有非零条目和相应的引用计数。
 */
void spi_flash_mmap_dump(void);

/**
 * @brief 获取可以是mmap的免费页数
 *
 * 此函数将返回mmu表中可用的可用页面数。在调用实际的spi_flash_map（将闪存范围映射到DCache或ICache内存）以检查是否有足够的空间可用于映射之前，这可能很有用。
 *
 * @param memory MMU表空闲页的内存类型
 *
 * @return 可编辑的可用页数
 */
uint32_t spi_flash_mmap_get_free_pages(spi_flash_mmap_memory_t memory);


#define SPI_FLASH_CACHE2PHYS_FAIL UINT32_MAX /*<! 如果闪存缓存地址无效，则spi_flash_cache2phys（）的结果*/

/**
 * @brief 给定闪存映射的内存地址，返回相应的物理闪存偏移量。
 *
 * 缓存地址尚未通过spi_flash_map（）分配，可以查找内存映射闪存空间中的任何地址。
 *
 * @param cached 指向闪存缓存内存的指针。
 *
 * @return
 * -SPI_FLASH_CACHE2PHYS_FAIL如果缓存地址在闪存缓存区域之外，或者地址未映射。
 * -否则，返回闪存中的物理偏移
 */
size_t spi_flash_cache2phys(const void *cached);

/** @brief 给定闪存中的物理偏移量，返回其在内存空间中映射的地址。
 *
 * 物理地址不必通过spi_flash_map（）分配，可以查找闪存中的任何地址。
 *
 * @note 只返回第一个匹配的缓存地址。如果MMU闪存缓存表被配置为多个条目指向同一物理地址，则可能有多个缓存地址对应于该物理地址。也可以将单个物理地址映射到IROM和DROM区域。
 *
 * @note 此函数不施加任何对齐约束，但如果内存参数为SPI_FLASH_MMAP_INST，并且phys_offs未对齐4字节，则从返回的指针读取将导致崩溃。
 *
 * @param phys_offs 闪存中要查找的物理偏移量。
 * @param memory 查找闪存缓存地址映射的地址空间类型（指令或数据）
 *
 * @return
 * -如果物理地址无效或未映射到指定内存类型的闪存缓存，则为NULL。
 * -与phys_off相对应的缓存内存地址（在IROM或DROM空间中）。
 */
const void *spi_flash_phys2cache(size_t phys_offs, spi_flash_mmap_memory_t memory);

/** @brief 在运行时检查是否在两个CPU上都启用了闪存缓存
 *
 * @return 如果两个CPU都启用了闪存缓存，则为true，否则为false。
 */
bool spi_flash_cache_enabled(void);

/**
 * @brief 为定义为cpuid参数的核心重新启用缓存。
 *
 * @param cpuid 要为其启用指令缓存的核心号
 */
void spi_flash_enable_cache(uint32_t cpuid);

/**
 * @brief SPI闪存关键部分进入功能。
 *
 */
typedef void (*spi_flash_guard_start_func_t)(void);
/**
 * @brief SPI闪存关键部分退出功能。
 */
typedef void (*spi_flash_guard_end_func_t)(void);
/**
 * @brief SPI闪存操作锁定功能。
 */
typedef void (*spi_flash_op_lock_func_t)(void);
/**
 * @brief SPI闪存操作解锁功能。
 */
typedef void (*spi_flash_op_unlock_func_t)(void);
/**
 * @brief 保护SPI闪存关键区域损坏的功能。
 */
typedef bool (*spi_flash_is_safe_write_address_t)(size_t addr, size_t size);
/**
 * @brief 在擦除操作期间向OS让步的函数。
 */
typedef void (*spi_flash_os_yield_t)(void);

/**
 * 保持SPI闪存访问关键部分管理功能的结构。
 *
 * Flash API使用两种类型的闪存访问管理功能：1）在调用适当的ROM功能（SPIWrite、SPIRead和SPIEraseBlock）之前准备/恢复闪存缓存和中断的功能：
 *   -“start”函数应禁用闪存缓存和非IRAM中断，并在调用上述ROM函数之前调用。
 *   -“end”函数应恢复闪存缓存和非IRAM中断的状态，并在调用上述ROM函数后调用。这两个函数不是递归的。2） 同步flash API使用的内部数据访问的函数。这些函数主要用于在多线程环境中同步对flash API内部数据的访问，并使用操作系统原语：
 *   -“op_lock”锁定对flash API内部数据的访问。
 *   -“op_unlock”解锁对flash API内部数据的访问。这两个函数是递归的，可以在多次调用“start”和“end”的外部使用，以创建原子多部分闪存操作。3） 当CONFIG_SPI_FLASH_DANGEROUS_WRITE_ALLOWED被禁用时，闪存写入/擦除API检查用户提供的地址，以避免损坏关键闪存区域（引导加载程序、分区表、正在运行的应用程序等）。
 *
 * 应根据执行上下文（使用或不使用功能OS）使用不同版本的保护功能。在正常情况下，当从任务调用flash API时，函数使用OS原语。当根本没有操作系统或无法保证操作系统正常工作（从异常处理程序访问闪存）时，这些功能无法使用操作系统原语，甚至不需要它们（不可能进行多线程访问）。
 *
 * @note 结构和相应的保护功能不应驻留在闪存中。例如，结构可以放在DRAM中，功能放在IRAM部分中。
 */
typedef struct {
    spi_flash_guard_start_func_t        start;      /**<临界段启动功能。*/
    spi_flash_guard_end_func_t          end;        /**<临界截面端函数。*/
    spi_flash_op_lock_func_t            op_lock;    /**<闪存访问API锁定功能。*/
    spi_flash_op_unlock_func_t          op_unlock;  /**<闪存访问API解锁功能。*/
#if !CONFIG_SPI_FLASH_DANGEROUS_WRITE_ALLOWED
    spi_flash_is_safe_write_address_t   is_safe_write_address; /**<检查闪存写入地址。*/
#endif
    spi_flash_os_yield_t                yield;      /**<闪存擦除期间向操作系统屈服*/
} spi_flash_guard_funcs_t;

/**
 * @brief  设置访问闪存的保护功能。
 *
 * @note 定点结构和相应的保护功能不应驻留在闪存中。例如，结构可以放在DRAM中，功能放在IRAM部分中。
 *
 * @param funcs 指向保存闪存访问保护功能的结构的指针。
 */
void spi_flash_guard_set(const spi_flash_guard_funcs_t* funcs);

/**
 * @brief 获取用于闪存访问的保护功能
 *
 * @return 通过spi_flash_guard_set（）设置的保护函数。如果实现自定义的低级SPI闪存操作，则可以调用这些函数。
 */
const spi_flash_guard_funcs_t *spi_flash_guard_get(void);

/**
 * @brief 默认OS感知闪存访问保护功能
 */
extern const spi_flash_guard_funcs_t g_flash_guard_default_ops;

/**
 * @brief 非操作系统闪存访问保护功能
 *
 * @note 此版本的闪存保护功能将在没有操作系统或来自紧急处理程序时使用。它不使用任何OS原语和IPC，并暗示只有调用CPU是活动的。
 */
extern const spi_flash_guard_funcs_t g_flash_guard_no_os_ops;

#ifdef __cplusplus
}
#endif


#endif /* ESP_SPI_FLASH_H */

