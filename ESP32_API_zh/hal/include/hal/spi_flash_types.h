// 版权所有2010-2019 Espressif Systems（上海）私人有限公司
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

#include <esp_types.h>
#include <esp_bit_defs.h>
#include "esp_flash_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**公共事务的定义。还保存返回值。*/
typedef struct {
    uint8_t reserved;           ///<保留，必须为0。
    uint8_t mosi_len;           ///<输出数据长度，字节
    uint8_t miso_len;           ///<输入数据长度，字节
    uint8_t address_bitlen;     ///<地址长度（位），如果命令不需要地址，则设置为0
    uint32_t address;           ///<执行操作的地址
    const uint8_t *mosi_data;   ///<输出数据到救助
    uint8_t *miso_data;         ///<[out]从从站输入数据，小端
    uint32_t flags;             ///<此事务的标志。暂时设置为0。
#define SPI_FLASH_TRANS_FLAG_CMD16          BIT(0)  ///<发送16位命令
#define SPI_FLASH_TRANS_FLAG_IGNORE_BASEIO  BIT(1)  ///<不为此事务应用基本io模式配置
#define SPI_FLASH_TRANS_FLAG_BYTE_SWAP      BIT(2)  ///<用于DTR模式，用于交换一对上升/下降沿的字节
    uint16_t command;           ///<发送命令
    uint8_t dummy_bitlen;       ///<要使用的基本虚拟位
    uint32_t io_mode;           ///<指定“SPI_Flash_IGNORE_BASEIO”时的闪存工作模式。
} spi_flash_trans_t;

/**
 * @brief SPI闪存时钟速度值，总是通过枚举而不是实际值来引用它们（列表中可能会附加更多速度）。
 *
 * 选择最大允许速度的策略是从“ESP_FLSH_speed_MAX-1”或闪存支持的最高频率中枚举，并降低速度直到探测成功。
 */
typedef enum {
    ESP_FLASH_5MHZ = 0, ///<闪光灯在5MHz下运行
    ESP_FLASH_10MHZ,    ///<闪光灯在10MHz下运行
    ESP_FLASH_20MHZ,    ///<闪光灯在20MHz下运行
    ESP_FLASH_26MHZ,    ///<闪光灯在26MHz下运行
    ESP_FLASH_40MHZ,    ///<闪光灯在40MHz以下运行
    ESP_FLASH_80MHZ,    ///<闪光灯在80MHz下运行
    ESP_FLASH_120MHZ,   ///<闪光灯在120MHz、120MHz下运行，只有在系统中进行定时调整后，主闪光灯才能使用。不要在任何API中直接使用这个。
    ESP_FLASH_SPEED_MAX, ///<主机支持的最大频率为``ESP_FLASH_SPEED_MAX-1``。
} esp_flash_speed_t;

///驾驶员支持的最低速度，当前为5 MHz
#define ESP_FLASH_SPEED_MIN     ESP_FLASH_5MHZ

// 这些位不太像“IO模式”，但可以附加到IO模式并由HAL使用。
#define SPI_FLASH_CONFIG_CONF_BITS      BIT(31) ///<或io_mode与此掩码，以启用虚拟输出功能或将前几个虚拟位替换为地址，以满足conf位的要求。（用于DIO/QIO/OIO模式）

/** @brief 用于从SPI闪存读取的模式*/
typedef enum {
    SPI_FLASH_SLOWRD = 0, ///<使用单个I/O读取数据，速度有一些限制
    SPI_FLASH_FASTRD, ///<使用单个I/O读取数据，无速度限制
    SPI_FLASH_DOUT,   ///<使用双I/O读取数据
    SPI_FLASH_DIO,    ///<使用双I/O传输地址和数据
    SPI_FLASH_QOUT,   ///<使用四路I/O读取数据
    SPI_FLASH_QIO,    ///<使用四路I/O传输地址和数据
#define SPI_FLASH_OPI_FLAG 16    ///<opi模式下闪存工作的标志，下面的io模式是opi，上面是SPI/QSPI模式。不要在任何API中使用此值。
    SPI_FLASH_OPI_STR = SPI_FLASH_OPI_FLAG,///<仅支持OPI闪存，STR模式下的闪存读写
    SPI_FLASH_OPI_DTR,///<仅支持OPI闪存，DTR模式下的闪存读写
    SPI_FLASH_READ_MODE_MAX,    ///<主机支持的最快io模式是``ESP_FLASH_READ_mode_MAX-1``。
} esp_flash_io_mode_t;

///闪存芯片挂起功能的配置结构。
typedef struct {
    uint32_t sus_mask;     ///<闪存寄存器中的SUS/SUS1/SUS2位。
    struct {
        uint32_t cmd_rdsr    :8;             ///<读取闪存状态寄存器（2）命令。
        uint32_t sus_cmd     :8;             ///<闪存暂停命令。
        uint32_t res_cmd     :8;             ///<闪存恢复命令。
        uint32_t reserved    :8;             ///<保留，设置为0。
    };
} spi_flash_sus_cmd_conf;

///闪存加密操作的结构。
typedef struct
{
    /**
     * @brief 启用闪存加密
    */
    void (*flash_encryption_enable)(void);
    /**
     * @brief 禁用闪存加密
    */
    void (*flash_encryption_disable)(void);
    /**
     * 操作前准备闪存加密。
     *
     * @param address 写入操作的闪存中的目标地址。
     * @param buffer 编程数据
     * @param size 按程序调整大小。
     *
     * @note 地址和缓冲区必须是8字对齐的。
     */
    void (*flash_encryption_data_prepare)(uint32_t address, const uint32_t* buffer, uint32_t size);
    /**
     * @brief 完成闪存数据加密操作。
     */
    void (*flash_encryption_done)(void);
    /**
     * 销毁加密结果
    */
    void (*flash_encryption_destroy)(void);
    /**
     * 检查是否有资格加密缓冲区
     *
     * @param address 写入的闪存分区的地址。
     * @param length 缓冲区大小。
     */
    bool (*flash_encryption_check)(uint32_t address, uint32_t length);
} spi_flash_encryption_t;

///ESP32支持的慢速io模式，目前为SlowRd
#define SPI_FLASH_READ_MODE_MIN SPI_FLASH_SLOWRD

struct spi_flash_host_driver_s;
typedef struct spi_flash_host_driver_s spi_flash_host_driver_t;

/**SPI闪存主机驱动程序实例*/
typedef struct {
    const struct spi_flash_host_driver_s* driver;  ///<指向实现函数表的指针
    // 实现可以将此结构包装为自己的结构，并在此处附加其他数据
} spi_flash_host_inst_t ;


/**主机驱动程序配置和上下文结构。*/
struct spi_flash_host_driver_s {
    /**
     * 在事务之前配置与设备相关的寄存器。这节省了在我们连续发送时重新配置这些寄存器的时间
     */
    esp_err_t (*dev_config)(spi_flash_host_inst_t *host);
    /**
     * 向设备发送用户定义的spi事务。
     */
    esp_err_t (*common_command)(spi_flash_host_inst_t *host, spi_flash_trans_t *t);
    /**
     * 读取闪存ID。
     */
    esp_err_t (*read_id)(spi_flash_host_inst_t *host, uint32_t *id);
    /**
     * 擦除整个闪存芯片。
     */
    void (*erase_chip)(spi_flash_host_inst_t *host);
    /**
     * 按起始地址擦除特定扇区。
     */
    void (*erase_sector)(spi_flash_host_inst_t *host, uint32_t start_address);
    /**
     * 按起始地址擦除特定块。
     */
    void (*erase_block)(spi_flash_host_inst_t *host, uint32_t start_address);
    /**
     * 读取闪存芯片的状态。
     */
    esp_err_t (*read_status)(spi_flash_host_inst_t *host, uint8_t *out_sr);
    /**
     * 禁用写保护。
     */
    esp_err_t (*set_write_protect)(spi_flash_host_inst_t *host, bool wp);
    /**
     * 编程一页闪存。检查“max_write_bytes”以获取允许的最大写入长度。
     */
    void (*program_page)(spi_flash_host_inst_t *host, const void *buffer, uint32_t address, uint32_t length);
    /**检查给定的缓冲区是否可以直接用于写入*/
    bool (*supports_direct_write)(spi_flash_host_inst_t *host, const void *p);
    /**
     * 用于写入数据的切片器。应使用此函数的返回值迭代调用“program_page”。
     *
     * @param address 开始写入闪存地址
     * @param len 要写入的长度请求
     * @param align_addr 要写入的对齐地址的输出
     * @param page_size 闪存芯片的物理页面大小
     * @return 一次“program_page”调用中实际可写入的长度
     */
    int (*write_data_slicer)(spi_flash_host_inst_t *host, uint32_t address, uint32_t len, uint32_t *align_addr,
                             uint32_t page_size);
    /**
     * 从闪存读取数据。检查“max_read_bytes”以获取允许的最大读取长度。
     */
    esp_err_t (*read)(spi_flash_host_inst_t *host, void *buffer, uint32_t address, uint32_t read_len);
    /**检查给定的缓冲区是否可以直接用于读取*/
    bool (*supports_direct_read)(spi_flash_host_inst_t *host, const void *p);
    /**
     * 用于读取数据的切片器。应使用此函数的返回值迭代调用“read”。
     *
     * @param address 开始读取闪存地址
     * @param len 要读取的长度请求
     * @param align_addr 要读取的对齐地址的输出
     * @param page_size 闪存芯片的物理页面大小
     * @return 在一次“读取”调用中可以实际读取的长度
     */
    int (*read_data_slicer)(spi_flash_host_inst_t *host, uint32_t address, uint32_t len, uint32_t *align_addr, uint32_t page_size);
    /**
     * 检查主机状态，0：忙，1：空闲，2：挂起。
     */
    uint32_t (*host_status)(spi_flash_host_inst_t *host);
    /**
     * 配置主机以在不同的读取模式下工作。负责补偿时间并设置IO模式。
     */
    esp_err_t (*configure_host_io_mode)(spi_flash_host_inst_t *host, uint32_t command,
                                        uint32_t addr_bitlen, int dummy_bitlen_base,
                                        esp_flash_io_mode_t io_mode);
    /**
     *  内部使用，轮询硬件，直到完成最后一次操作。
     */
    void (*poll_cmd_done)(spi_flash_host_inst_t *host);
    /**
     * 对于某些主机（SPI1），它们与缓存共享。修改数据时，需要刷新缓存。如果不支持，则保留NULL。
     */
    esp_err_t (*flush_cache)(spi_flash_host_inst_t* host, uint32_t addr, uint32_t size);

    /**
     * 暂停检查擦除/编程操作，保留给ESP32-C3和ESP32-S3 spi闪存ROM IMPL。
     */
    void (*check_suspend)(spi_flash_host_inst_t *host);

    /**
     * 手动从挂起恢复闪存
     */
    void (*resume)(spi_flash_host_inst_t *host);

    /**
     * 手动设置闪存挂起状态
     */
    void (*suspend)(spi_flash_host_inst_t *host);

    /**
     * 挂起设置cmd和状态寄存器掩码的功能设置。
     */
    esp_err_t (*sus_setup)(spi_flash_host_inst_t *host, const spi_flash_sus_cmd_conf *sus_conf);
};

#ifdef __cplusplus
}
#endif

