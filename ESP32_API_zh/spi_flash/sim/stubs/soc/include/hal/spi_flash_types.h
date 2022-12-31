/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 *
 * 这是编译ESP-IDF以在主机系统上运行测试时使用的STUB FILE HEADER。通常用于ESP-IDF的头文件具有相同的名称，但位于其他位置。
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**公共事务的定义。还保存返回值。*/
typedef struct {
    uint8_t command;            ///<发送命令，始终为8位
    uint8_t mosi_len;           ///<输出数据长度，字节
    uint8_t miso_len;           ///<输入数据长度，字节
    uint8_t address_bitlen;     ///<地址长度（位），如果命令不需要地址，则设置为0
    uint32_t address;           ///<执行操作的地址
    const uint8_t *mosi_data;   ///<输出数据到救助
    uint8_t *miso_data;         ///<[out]从从站输入数据，小端
} spi_flash_trans_t;

/** @brief 用于从SPI闪存读取的模式*/
typedef enum {
    SPI_FLASH_SLOWRD = 0, ///<使用单个I/O读取数据，速度有一些限制
    SPI_FLASH_FASTRD, ///<使用单个I/O读取数据，无速度限制
    SPI_FLASH_DOUT,   ///<使用双I/O读取数据
    SPI_FLASH_DIO,    ///<使用双I/O传输地址和数据
    SPI_FLASH_QOUT,   ///<使用四路I/O读取数据
    SPI_FLASH_QIO,    ///<使用四路I/O传输地址和数据

    SPI_FLASH_READ_MODE_MAX,    ///<主机支持的最快io模式是``ESP_FLASH_READ_mode_MAX-1``。
} esp_flash_io_mode_t;

/**
 * 闪存芯片挂起功能的配置结构。
 */
typedef struct spi_flash_sus_cmd_conf_dummy spi_flash_sus_cmd_conf;

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
///ESP32支持的慢速io模式，目前为SlowRd
#define SPI_FLASH_READ_MODE_MIN SPI_FLASH_SLOWRD

#ifdef __cplusplus
}
#endif

