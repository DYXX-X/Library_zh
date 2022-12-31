// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once
#include "esp_err.h"
#include <stdint.h>
#include <stdbool.h>

#include "hal/spi_flash_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct spi_flash_chip_t;
typedef struct spi_flash_chip_t spi_flash_chip_t;

typedef struct esp_flash_t esp_flash_t;

/** @brief 用于描述闪光区域的结构*/
typedef struct {
    uint32_t offset;    ///<此区域的起始地址
    uint32_t size;      ///<区域大小
} esp_flash_region_t;

/** @brief 操作系统级集成挂钩，用于访问正在运行的操作系统中的闪存芯片
 *
 * 它位于公共标头中，因为某些实例应该在启动代码中静态分配。可能会根据硬件版本和新的闪存芯片功能要求进行更新，不应视为公共API。
 *
 *  对于高级开发人员，您可以用自己的实现替换其中的一些，风险由您自己承担。
*/
typedef struct {
    /**
     * 在开始任何闪存操作之前调用。不需要递归（即每次调用“end”时最多调用一次）。
     */
    esp_err_t (*start)(void *arg);

    /**在完成任何闪存操作后调用。*/
    esp_err_t (*end)(void *arg);

    /**在任何擦除/写入操作之前调用，以检查区域是否受操作系统限制*/
    esp_err_t (*region_protected)(void* arg, size_t start_addr, size_t size);

    /**延迟至少“us”微秒。在“start”和“end”之间调用。*/
    esp_err_t (*delay_us)(void *arg, uint32_t us);

    /**当应用程序中的缓冲区无法直接读入/写入时，调用获取临时缓冲区。*/
    void *(*get_temp_buffer)(void* arg, size_t reqest_size, size_t* out_size);

    /**为释放临时缓冲区调用。*/
    void (*release_temp_buffer)(void* arg, void *temp_buf);

    #define SPI_FLASH_YIELD_REQ_YIELD   BIT(0)
    #define SPI_FLASH_YIELD_REQ_SUSPEND BIT(1)

    /**屈服于其他任务。在擦除操作期间调用@返回ESP_OK表示需要调用yield（获得要处理的事件），而ESP_ERR_TIMEOUT表示跳过yield。*/
    esp_err_t (*check_yield)(void *arg, uint32_t chip_status, uint32_t* out_request);

    #define SPI_FLASH_YIELD_STA_RESUME  BIT(2)

    /**屈服于其他任务。在擦除操作期间调用。*/
    esp_err_t (*yield)(void *arg, uint32_t* out_status);

    /**调用获取系统时间。*/
    int64_t (*get_system_time)(void *arg);

} esp_flash_os_functions_t;

/** @brief 用于描述连接到系统的SPI闪存芯片的结构。

    结构必须在使用前初始化（传递给esp_flash_init（））。它位于公共标头中，因为某些实例应该在启动代码中静态分配。可能会根据硬件版本和新的闪存芯片功能要求进行更新，不应视为公共API。

    对于高级开发人员，您可以用自己的实现替换其中的一些，风险由您自己承担。
*/
struct esp_flash_t {
    spi_flash_host_inst_t* host;   ///<指向特定于硬件的“host_driver”结构的指针。必须在使用前进行初始化。
    const spi_flash_chip_t *chip_drv;   ///<指向芯片型号特定“适配器”结构的指针。如果为NULL，将在初始化期间检测到。

    const esp_flash_os_functions_t *os_func;    ///<指向操作系统特定钩子结构的指针。在主机正确初始化后，调用``esp_flash_init_os_functions（）``设置此字段。
    void *os_func_data;                         ///<指向操作系统特定钩子的参数的指针。保留NULL，并将用``os_func``初始化。

    esp_flash_io_mode_t read_mode; ///<已配置SPI闪存读取模式。在调用`esp_flash_init``之前设置。
    uint32_t size;                   ///<SPI闪存大小（字节）。如果为0，将在初始化期间检测大小。
    uint32_t chip_id;               ///<检测到芯片id。
    uint32_t busy             :1;   ///<此标志用于验证芯片的状态。
    uint32_t reserved_flags   :31;  ///<保留。
};


/** @brief 初始化SPI闪存芯片接口。
 *
 * 在为该芯片调用任何其他API函数之前，必须先调用该函数。
 *
 * @note 在调用此函数之前，只有芯片结构的“host”和“read_mode”字段必须初始化。如果设置为零或NULL，则可以自动检测其他字段。
 *
 * @note 如果chip->drv指针为空，将根据其制造商和产品ID自动检测chip-drv。有关此过程的详细信息，请参见``esp_flash_registered_flash_drivers'`指针。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 * @return 成功时ESP_OK，或初始化失败时闪烁错误代码。
 */
esp_err_t esp_flash_init(esp_flash_t *chip);

/**
 * 检查是否设置了适当的芯片驱动程序。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 *
 * @return 如果设置为true，则为false。
 */
bool esp_flash_chip_driver_initialized(const esp_flash_t *chip);

/** @brief 通过通用“RDID”SPI闪存命令读取闪存ID。
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 * @param[out] out_id 用于接收ID值的指针。
 *
 * ID是24位值。“id”的低16位是芯片id，高8位是制造商id。
 *
 * @return 成功时为ESP_OK，如果操作失败则为闪存错误代码。
 */
esp_err_t esp_flash_read_id(esp_flash_t *chip, uint32_t *out_id);

/** @brief 根据闪存ID检测闪存大小。
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 * @param[out] out_size 检测到的大小（字节）。
 *
 * @note 大多数闪存芯片使用闪存ID的通用格式，其中较低的4位指定大小为2的幂。如果制造商不遵循此惯例，则可能会错误检测到大小。
 *
 * @return 成功时为ESP_OK，如果操作失败则为闪存错误代码。
 */
esp_err_t esp_flash_get_size(esp_flash_t *chip, uint32_t *out_size);

/** @brief 通过通用“RDUID”SPI闪存命令读取闪存唯一ID。
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化。
 * @param[out] out_id 用于接收唯一ID值的指针。
 *
 * ID是64位值。
 *
 * @return
 *      -成功时为ESP_OK，如果操作失败则为闪存错误代码。
 *      -如果芯片不支持读取id，则为ESP_ERR_NOT_SUPPORTED。
 */
esp_err_t esp_flash_read_unique_chip_id(esp_flash_t *chip, uint64_t *out_id);

/** @brief 擦除闪存芯片内容
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 *
 *
 * @return
 *      -成功时ESP_ OK，
 *      -如果芯片无法执行操作，则返回ESP_ERR_NOT_SUPPORTED。发送命令后，WREN=1表示这一点。
 *      -操作失败时的其他闪存错误代码。
 */
esp_err_t esp_flash_erase_chip(esp_flash_t *chip);

/** @brief 擦除闪存芯片的某个区域
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 * @param start 开始擦除闪存的地址。必须与扇区对齐。
 * @param len 要擦除的区域长度。还必须与扇区对齐。
 *
 * 扇区大小在chip->drv->Sector_size字段中指定（通常为4096字节）。如果开始和长度不是此大小的倍数，则返回ESP_ERR_INVALID_ARG。
 *
 * 在可能的情况下，使用块（多扇区）擦除执行擦除（块大小在chip->drv->block_Erase_size字段中指定，通常为65536字节）。使用单个扇区擦除命令擦除剩余扇区。
 *
 * @return
 *      -成功时ESP_ OK，
 *      -如果芯片无法执行操作，则返回ESP_ERR_NOT_SUPPORTED。发送命令后，WREN=1表示这一点。
 *      -操作失败时的其他闪存错误代码。
 */
esp_err_t esp_flash_erase_region(esp_flash_t *chip, uint32_t start, uint32_t len);

/** @brief 读取整个芯片是否写保护
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 * @param[out] write_protected 指向布尔值的指针，设置为写保护标志的值。
 *
 * @note 此标志的正确结果取决于使用的SPI闪存芯片型号和chip_drv（通过“chip->drv”字段）。
 *
 * @return 成功时为ESP_OK，如果操作失败则为闪存错误代码。
 */
esp_err_t esp_flash_get_chip_write_protect(esp_flash_t *chip, bool *write_protected);

/** @brief 为SPI闪存芯片设置写保护
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 * @param write_protect 写保护标志的布尔值
 *
 * @note 此函数的正确行为取决于使用的SPI闪存芯片型号和chip_drv（通过“chip->drv”字段）。
 *
 * 在清除写保护状态之前，某些SPI闪存芯片可能需要重新通电。否则，可以通过后续调用此函数来删除写保护。
 *
 * @return 成功时为ESP_OK，如果操作失败则为闪存错误代码。
 */
esp_err_t esp_flash_set_chip_write_protect(esp_flash_t *chip, bool write_protect);


/** @brief 阅读此SPI闪存芯片的可单独保护区域列表。
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 * @param[out] out_regions 用于接收指向芯片的可保护区域阵列的指针的指针。
 * @param[out] out_num_regions 指向接收“regions”中返回的数组中可保护区域计数的整数的指针。
 *
 * @note 此函数的正确行为取决于使用的SPI闪存芯片型号和chip_drv（通过“chip->drv”字段）。
 *
 * @return 成功时为ESP_OK，如果操作失败则为闪存错误代码。
 */
esp_err_t esp_flash_get_protectable_regions(const esp_flash_t *chip, const esp_flash_region_t **out_regions, uint32_t *out_num_regions);


/** @brief 检测SPI闪存芯片的某个区域是否受到保护
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 * @param region 指向描述受保护区域的结构的指针。这必须与从esp_flash_get_protectable_regions（…）返回的区域之一匹配。
 * @param[out] out_protected 指向基于此区域的受保护状态设置的标志的指针。
 *
 * @note 如果对整个芯片启用了保护，则此结果可能为假，写入操作仍然失败。
 *
 * @note 此函数的正确行为取决于使用的SPI闪存芯片型号和chip_drv（通过“chip->drv”字段）。
 *
 * @return 成功时为ESP_OK，如果操作失败则为闪存错误代码。
 */
esp_err_t esp_flash_get_protected_region(esp_flash_t *chip, const esp_flash_region_t *region, bool *out_protected);

/** @brief 更新SPI闪存芯片区域的受保护状态
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 * @param region 指向描述受保护区域的结构的指针。这必须与从esp_flash_get_protectable_regions（…）返回的区域之一匹配。
 * @param protect 写入要设置的保护标志。
 *
 * @note 如果对整个芯片启用保护，则区域保护标志可能被清除，写入操作仍然失败。
 *
 * @note 此函数的正确行为取决于使用的SPI闪存芯片型号和chip_drv（通过“chip->drv”字段）。
 *
 * @return 成功时为ESP_OK，如果操作失败则为闪存错误代码。
 */
esp_err_t esp_flash_set_protected_region(esp_flash_t *chip, const esp_flash_region_t *region, bool protect);

/** @brief 从SPI闪存芯片读取数据
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 * @param buffer 指向将读取数据的缓冲区的指针。为了获得更好的性能，这应该在DRAM和字对齐。
 * @param address 闪存上要读取的地址。必须小于芯片->大小字段。
 * @param length 要读取的数据长度（字节）。
 *
 * 缓冲区、地址或长度没有对齐约束。
 *
 * @note 如果使用片上闪存加密，此函数将返回原始（即加密）数据。使用闪存缓存透明地解密数据。
 *
 * @return
 *      -ESP_OK：成功
 *      -ESP_ERR_NO_MEM:缓冲区位于无法同时访问的外部PSRAM中，并且无法分配临时内部缓冲区。
 *      -如果操作失败，则返回闪存错误代码。
 */
esp_err_t esp_flash_read(esp_flash_t *chip, void *buffer, uint32_t address, uint32_t length);

/** @brief 将数据写入SPI闪存芯片
 *
 * @param chip 用于标识闪存芯片的指针。必须已通过esp_flash_init（）成功初始化
 * @param address 闪存上要写入的地址。必须事先擦除（SPI NOR闪存只能写入位1->0）。
 * @param buffer 指向要写入数据的缓冲区的指针。为了获得更好的性能，这应该在DRAM和字对齐。
 * @param length 要写入的数据长度（字节）。
 *
 * 缓冲区、地址或长度没有对齐约束。
 *
 * @return
 *      -成功时ESP_ OK，
 *      -如果芯片无法执行操作，则返回ESP_ERR_NOT_SUPPORTED。发送命令后，WREN=1表示这一点。
 *      -操作失败时的其他闪存错误代码。
 */
esp_err_t esp_flash_write(esp_flash_t *chip, const void *buffer, uint32_t address, uint32_t length);

/** @brief 使用片上硬件闪存加密将数据加密并写入SPI闪存芯片
 *
 * @param chip 用于标识闪存芯片的指针。必须为NULL（主闪存芯片）。对于其他芯片，不支持加密写入。
 * @param address 闪存上要写入的地址对齐。16字节。必须事先擦除（SPI NOR闪存只能写入位1->0）。
 * @param buffer 指向要写入数据的缓冲区的指针。
 * @param length 要写入的数据长度（字节）。16字节对齐。
 *
 * @note 地址和长度必须为16字节对齐，因为这是加密块大小
 *
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_NOT_SUPPORTED：此芯片不支持加密写入。
 *  -ESP_ERR_INVALID_ARG：地址、缓冲区或长度无效。
 *  -或spi_flash_write_encrypted（）中的其他闪存错误代码。
 */
esp_err_t esp_flash_write_encrypted(esp_flash_t *chip, uint32_t address, const void *buffer, uint32_t length);

/** @brief 使用片上硬件闪存加密从SPI闪存芯片读取和解密数据
 *
 * @param chip 用于标识闪存芯片的指针。必须为NULL（主闪存芯片）。对于其他芯片，不支持加密读取。
 * @param address 闪存上要读取的地址。
 * @param out_buffer 指向要读取数据的缓冲区的指针。
 * @param length 要读取的数据长度（字节）。
 *
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_NOT_SUPPORTED：此芯片不支持加密读取。
 *  -或spi_flash_read_encrypted（）中的其他闪存错误代码。
 */
esp_err_t esp_flash_read_encrypted(esp_flash_t *chip, uint32_t address, void *out_buffer, uint32_t length);

/** @brief 指向“默认”SPI闪存芯片的指针，即连接到MCU的主芯片。

   如果传递给esp_flash_xxx API函数的“chip”参数始终为NULL，则使用此芯片。
*/
extern esp_flash_t *esp_flash_default_chip;


/*******************************************************************************
 * 实用程序功能
 ******************************************************************************/

/**
 * @brief 如果芯片配置为四路I/O或四路快速读取，则返回true。
 *
 * @param chip 指向要使用的SPI闪存芯片的指针。如果为NULL，则替换esp_flash_default_chip。
 *
 * @return 如果flash在四模式下工作，则为true，否则为false
 */
static inline bool esp_flash_is_quad_mode(const esp_flash_t *chip)
{
    return (chip->read_mode == SPI_FLASH_QIO) || (chip->read_mode == SPI_FLASH_QOUT);
}

#ifdef __cplusplus
}
#endif

