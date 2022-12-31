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
#include "esp_flash.h"
#include "esp_attr.h"

struct esp_flash_t;
typedef struct esp_flash_t esp_flash_t;

typedef struct spi_flash_chip_t spi_flash_chip_t;

/**闪存操作超时配置*/
typedef struct {
    uint32_t idle_timeout;          ///<主机发送其他命令并通过闪存完成的默认超时
    uint32_t chip_erase_timeout;    ///<芯片擦除操作超时
    uint32_t block_erase_timeout;   ///<块擦除操作超时
    uint32_t sector_erase_timeout;  ///<扇区擦除操作超时
    uint32_t page_program_timeout;  ///<页面程序操作超时
} flash_chip_op_timeout_t;

typedef enum {
    SPI_FLASH_REG_STATUS = 1,
} spi_flash_register_t;

typedef enum {
   SPI_FLASH_CHIP_CAP_SUSPEND = BIT(0),            ///<闪存芯片支持挂起功能。
   SPI_FLASH_CHIP_CAP_32MB_SUPPORT = BIT(1),       ///<Flash芯片驱动程序支持大于32M字节的闪存大小。
   SPI_FLASH_CHIP_CAP_UNIQUE_ID = BIT(2),          ///<闪存芯片驱动程序支持读取闪存唯一id。
} spi_flash_caps_t;
FLAG_ATTR(spi_flash_caps_t)

/** @brief SPI闪存芯片驱动程序定义结构。
 *
 * 芯片驱动程序结构包含指向执行SPI闪存操作的函数的芯片特定指针，以及一些芯片特定数值。
 *
 * @note 这不是公共API。这些函数是从公共API（在esp_flash.h中声明）调用的。他们假设调用者已经验证了参数并启用了相关保护（禁用闪存缓存、防止并发SPI访问等）
 *
 * 不要在其他上下文中直接调用芯片驱动程序函数。
 *
 * 通用芯片的通用驱动程序及其相关操作在spi_flash_chip_generic中定义。h，其可用作写入的新的/特定的SPI闪存芯片驱动器的构建块。
 *
 * @note 所有这些函数都可以在禁用SPI闪存缓存的情况下调用，因此只能访问IRAM/DRAM/ROM。
 */
struct spi_flash_chip_t {
    const char *name; ///<芯片驱动程序的名称
    const flash_chip_op_timeout_t *timeout; ///<此芯片的超时配置
    /* 探测是否找到受支持的SPI闪存芯片。
     *
     * 尝试使用这些操作配置“芯片”，并探测匹配的SPI闪存芯片。
     *
     * SPI闪存芯片的自动检测依次在每个已注册的驱动程序上调用此函数（请参见esp_flash_registered_flash_drivers）。
     *
     * 提供了由spi_flash_generic_read_ID（）读取的ID，因此每个探针函数不需要不必要地读取ID，但允许探针以任何非破坏性的方式查询闪存。
     *
     * 如果探测成功，则允许驱动程序修改“芯片”结构（具体而言，如果对驱动程序有用，则向driver_data指针分配一些内容）
     *
     * @return 如果探测成功，则返回ESP_OK，否则返回错误。驱动程序可能会假设返回ESP_OK意味着它已认领此芯片。
     */
    esp_err_t (*probe)(esp_flash_t *chip, uint32_t flash_id);

    esp_err_t (*reset)(esp_flash_t *chip);


    /* 检测SPI闪存大小
     *
     * 询问芯片以检测其大小。
     */
    esp_err_t (*detect_size)(esp_flash_t *chip, uint32_t *size);

    /* 擦除整个芯片

       呼叫者已验证芯片没有写保护。
     */
    esp_err_t (*erase_chip)(esp_flash_t *chip);

    /* 擦除芯片的一个扇区。扇区大小在“Sector_size”字段中指定。

       sector_address是以字节为单位的偏移量。

       调用方已验证此扇区应为非写保护。
     */
    esp_err_t (*erase_sector)(esp_flash_t *chip, uint32_t sector_address);

    /* 擦除芯片的多扇区块。块大小在“Block_erase_size”字段中指定。sector_address是以字节为单位的偏移量。

       调用方已验证此块应为非写保护。
     */
    esp_err_t (*erase_block)(esp_flash_t *chip, uint32_t block_address);

    uint32_t sector_size; /* 扇区是最小擦除大小*/
    uint32_t block_erase_size; /* 此芯片上多扇区擦除的最佳（最快）块大小*/

    /* 读取整个芯片的写保护状态。*/
    esp_err_t (*get_chip_write_protect)(esp_flash_t *chip, bool *out_write_protected);

    /* 设置整个芯片的写保护状态。*/
    esp_err_t (*set_chip_write_protect)(esp_flash_t *chip, bool chip_write_protect);

    /* 此芯片上可单独写入的保护区域数。范围0-63。*/
    uint8_t num_protectable_regions;
    /* 指向描述每个可保护区域的数组的指针。应具有num_proctecable_regions元素。*/
    const esp_flash_region_t *protectable_regions;
    /* 获取描述芯片上所有可保护区域的位掩码。每个位表示protectable_regions数组中的一个条目，即设置位（1<<N），然后数组条目N处的区域被写保护。*/
    esp_err_t (*get_protected_regions)(esp_flash_t *chip, uint64_t *regions);

    /* 在芯片上设置可保护区域。每个位表示可保护区域阵列中的入口。*/
    esp_err_t (*set_protected_regions)(esp_flash_t *chip, uint64_t regions);

    /* 从芯片读取数据。
     *
     * 在调用此函数之前，调用者将调用chip->drv->set_read_mode（chip），以便正确配置芯片的读取模式。
     */
    esp_err_t (*read)(esp_flash_t *chip, void *buffer, uint32_t address, uint32_t length);

    /* 将任意数量的数据写入芯片。
     */
    esp_err_t (*write)(esp_flash_t *chip, const void *buffer, uint32_t address, uint32_t length);


    /* 使用page program命令将数据写入芯片。
     *
     * 此函数预期由chip->drv->write调用（如果chip->drv->write实现没有调用它，则可以将其保留为NULL。）
     *
     * -提供给此函数的长度参数最多为“page_size”字节。
     *
     * -“address”和“address+length”之间的区域不会跨越page_size对齐的边界（在调用page_program之前，写入实现应该将这样的写入拆分为两部分。）
     */
    esp_err_t (*program_page)(esp_flash_t *chip, const void *buffer, uint32_t address, uint32_t length);

    /* 页面大小由Page_program函数编写。通常为256字节。*/
    uint32_t page_size;

    /* 使用内部闪存加密硬件对芯片进行加密写入。*/
    esp_err_t (*write_encrypted)(esp_flash_t *chip, const void *buffer, uint32_t address, uint32_t length);


    /* 等待SPI闪存芯片空闲（任何写入操作都将完成）。该函数既可以从高级API函数调用，也可以从该结构中的其他函数调用。

       timeout_ms应该是函数返回ESP_ERR_timeout之前的超时（以毫秒为单位）。如果芯片没有响应（即返回所有0xFF或类似值），这有助于避免挂起
    */
    esp_err_t (*wait_idle)(esp_flash_t *chip, uint32_t timeout_us);

    /* 为chip->read_mode中指定的读取模式配置SPI主机和芯片。
     *
     * 在调用“read”函数之前，高级API会调用此函数。
     *
     * 如果指定的模式不受支持，则可以返回ESP_ERR_FLASH_UNSUPPORTED_HOST或ESP_ERR-FLASH_UNSUPPORTED_CHIP。
     */
    esp_err_t (*set_io_mode)(esp_flash_t *chip);

    /*
     * 获取是否设置了Quad Enable（QE）。（*out_io_mode）=SPI_FLASH_QOUT（如果启用），否则禁用
     */
    esp_err_t (*get_io_mode)(esp_flash_t *chip, esp_flash_io_mode_t* out_io_mode);

    /*
     * 读取芯片ID。在设置芯片驱动程序时调用，但我们想知道确切的芯片ID（以获取大小等）。
     */
    esp_err_t (*read_id)(esp_flash_t *chip, uint32_t* out_chip_id);

    /*
     * 读取请求的寄存器（状态等）。
     */
    esp_err_t (*read_reg)(esp_flash_t *chip, spi_flash_register_t reg_id, uint32_t* out_reg);

    /**屈服于其他任务。在擦除操作期间调用。*/
    esp_err_t (*yield)(esp_flash_t *chip, uint32_t wip);

    /**设置闪存挂起配置。*/
    esp_err_t (*sus_setup)(esp_flash_t *chip);

    /**
     * 读取芯片唯一ID。
     */
    esp_err_t (*read_unique_id)(esp_flash_t *chip, uint64_t* flash_unique_id);

    /**
     * 获取闪存芯片的功能。请参阅SPI_FLASH_CHIP_CAP_*宏作为参考。
     */
    spi_flash_caps_t (*get_chip_caps)(esp_flash_t *chip);

    /**
     *  配置主机寄存器以使用“chip->read_mode”中设置的指定读取模式。
     */
    esp_err_t (*config_host_io_mode)(esp_flash_t *chip, uint32_t flags);
};

/* 指向指向闪存芯片所有已知驱动程序的指针数组的指针。如果调用方未提供闪存芯片驱动程序，esp_flash_init（）将使用此数组来检测闪存芯片驱动。

   数组以NULL指针终止。

   该指针可以用指向新阵列的指针覆盖，以更新已知闪存芯片的列表。
 */
extern const spi_flash_chip_t **esp_flash_registered_chips;

