/*
 * 版权所有（c）Espressif System 2019
 *
 */

#ifndef _ROM_OPI_FLASH_H_
#define _ROM_OPI_FLASH_H_
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "spi_flash.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t cmd;                /*!< 命令值*/
    uint16_t cmdBitLen;          /*!< 命令字节长度*/
    uint32_t *addr;              /*!< 指向地址值*/
    uint32_t addrBitLen;         /*!< 地址字节长度*/
    uint32_t *txData;            /*!< 发送数据缓冲区的点*/
    uint32_t txDataBitLen;       /*!< 发送数据字节长度。*/
    uint32_t *rxData;            /*!< 指向接收数据缓冲区*/
    uint32_t rxDataBitLen;       /*!< Recevie数据字节长度。*/
    uint32_t dummyBitLen;
} esp_rom_spi_cmd_t;

#define ESP_ROM_OPIFLASH_MUX_TAKE()
#define ESP_ROM_OPIFLASH_MUX_GIVE()
#define ESP_ROM_OPIFLASH_SEL_CS0     (BIT(0))
#define ESP_ROM_OPIFLASH_SEL_CS1     (BIT(1))

// MX25UM25645G八位闪存的定义
// SPI状态寄存器
#define ESP_ROM_SPIFLASH_BUSY_FLAG     BIT0
#define ESP_ROM_SPIFLASH_WRENABLE_FLAG BIT1
#define ESP_ROM_SPIFLASH_BP0           BIT2
#define ESP_ROM_SPIFLASH_BP1           BIT3
#define ESP_ROM_SPIFLASH_BP2           BIT4
#define ESP_ROM_SPIFLASH_WR_PROTECT    (ESP_ROM_SPIFLASH_BP0|ESP_ROM_SPIFLASH_BP1|ESP_ROM_SPIFLASH_BP2)
#define ESP_ROM_SPIFLASH_QE            BIT9

#define FLASH_OP_MODE_RDCMD_DOUT       0x3B
#define ESP_ROM_FLASH_SECTOR_SIZE      0x1000
#define ESP_ROM_FLASH_BLOCK_SIZE_64K   0x10000
#define ESP_ROM_FLASH_PAGE_SIZE        256

// FLASH命令
#define ROM_FLASH_CMD_RDID             0x9F
#define ROM_FLASH_CMD_WRSR             0x01
#define ROM_FLASH_CMD_WRSR2            0x31 /* 并非所有SPI闪存都使用此命令*/
#define ROM_FLASH_CMD_WREN             0x06
#define ROM_FLASH_CMD_WRDI             0x04
#define ROM_FLASH_CMD_RDSR             0x05
#define ROM_FLASH_CMD_RDSR2            0x35 /* 并非所有SPI闪存都使用此命令*/
#define ROM_FLASH_CMD_ERASE_SEC        0x20
#define ROM_FLASH_CMD_ERASE_BLK_32K    0x52
#define ROM_FLASH_CMD_ERASE_BLK_64K    0xD8
#define ROM_FLASH_CMD_OTPEN            0x3A /* 启用OTP模式，并非所有SPI闪存都使用此命令*/
#define ROM_FLASH_CMD_RSTEN            0x66
#define ROM_FLASH_CMD_RST              0x99

#define ROM_FLASH_CMD_SE4B             0x21
#define ROM_FLASH_CMD_SE4B_OCT         0xDE21
#define ROM_FLASH_CMD_BE4B             0xDC
#define ROM_FLASH_CMD_BE4B_OCT         0x23DC
#define ROM_FLASH_CMD_RSTEN_OCT        0x9966
#define ROM_FLASH_CMD_RST_OCT          0x6699

#define ROM_FLASH_CMD_FSTRD4B_STR      0x13EC
#define ROM_FLASH_CMD_FSTRD4B_DTR      0x11EE
#define ROM_FLASH_CMD_FSTRD4B          0x0C
#define ROM_FLASH_CMD_PP4B             0x12
#define ROM_FLASH_CMD_PP4B_OCT         0xED12

#define ROM_FLASH_CMD_RDID_OCT         0x609F
#define ROM_FLASH_CMD_WREN_OCT         0xF906
#define ROM_FLASH_CMD_RDSR_OCT         0xFA05
#define ROM_FLASH_CMD_RDCR2            0x71
#define ROM_FLASH_CMD_RDCR2_OCT        0x8E71
#define ROM_FLASH_CMD_WRCR2            0x72
#define ROM_FLASH_CMD_WRCR2_OCT        0x8D72

// GigaDevice GD25LX256E闪存的定义
#define ROM_FLASH_CMD_RDFSR_GD            0x70
#define ROM_FLASH_CMD_RD_GD               0x03
#define ROM_FLASH_CMD_RD4B_GD             0x13
#define ROM_FLASH_CMD_FSTRD_GD            0x0B
#define ROM_FLASH_CMD_FSTRD4B_GD          0x0C
#define ROM_FLASH_CMD_FSTRD_OOUT_GD       0x8B
#define ROM_FLASH_CMD_FSTRD4B_OOUT_GD     0x7C
#define ROM_FLASH_CMD_FSTRD_OIOSTR_GD     0xCB
#define ROM_FLASH_CMD_FSTRD4B_OIOSTR_GD   0xCC
#define ROM_FLASH_CMD_FSTRD4B_OIODTR_GD   0xFD

#define ROM_FLASH_CMD_PP_GD               0x02
#define ROM_FLASH_CMD_PP4B_GD             0x12
#define ROM_FLASH_CMD_PP_OOUT_GD          0x82
#define ROM_FLASH_CMD_PP4B_OOUT_GD        0x84
#define ROM_FLASH_CMD_PP_OIO_GD           0xC2
#define ROM_FLASH_CMD_PP4B_OIOSTR_GD      0x8E

#define ROM_FLASH_CMD_SE_GD               0x20
#define ROM_FLASH_CMD_SE4B_GD             0x21
#define ROM_FLASH_CMD_BE32K_GD            0x52
#define ROM_FLASH_CMD_BE32K4B_GD          0x5C
#define ROM_FLASH_CMD_BE64K_GD            0xD8
#define ROM_FLASH_CMD_BE64K4B_GD          0xDC

#define ROM_FLASH_CMD_EN4B_GD             0xB7
#define ROM_FLASH_CMD_DIS4B_GD            0xE9

// spi用户模式命令配置

/**
 * @brief 配置spi用户命令
 * @param spi_num spi端口
 * @param pcmd 用于接受spi命令结构的指针
 */
void esp_rom_spi_cmd_config(int spi_num, esp_rom_spi_cmd_t* pcmd);

/**
 * @brief 启动spi用户命令序列
 * @param spi_num spi端口
 * @param rx_buf 接收数据的缓冲区指针
 * @param rx_len 接收数据长度（字节）
 * @param cs_en_mask 决定使用哪个cs，0表示cs0，1表示cs1
 * @param is_write_erase 指示这是写操作还是擦除操作，因为CPU将检查权限
 */
void esp_rom_spi_cmd_start(int spi_num, uint8_t* rx_buf, uint16_t rx_len, uint8_t cs_en_mask, bool is_write_erase);

/**
 * @brief 根据efuse设置配置opi闪存盘。
 */
void esp_rom_opiflash_pin_config(void);

// 设置SPI读/写模式
/**
 * @brief 设置SPI操作模式
 * @param spi_num spi端口
 * @param mode 闪存读取模式
 */
void esp_rom_spi_set_op_mode(int spi_num, esp_rom_spiflash_read_mode_t mode);

/**
 * @brief 将数据交换模式设置为DTR（DDR）模式
 * @param spi_num spi端口
 * @param wr_swap 决定是否在dtr写入操作中交换fifo数据
 * @param rd_swap 决定是否在dtr读取操作中交换fifo数据
 */
void esp_rom_spi_set_dtr_swap_mode(int spi, bool wr_swap, bool rd_swap);


/**
 * @brief 以spi/opi str/opi dtr模式发送重置命令（用于MX25UM25645G）
 * @param spi_num spi端口
 */
void esp_rom_opiflash_mode_reset(int spi_num);

#if 0
// MX25UM25645G opi闪存接口
/**
 * @brief 执行闪存操作命令
 * @param spi_num spi端口
 * @param mode 闪存读取模式
 * @param cmd 命令字段中要发送的数据
 * @param cmd_bit_len 命令字段的位长度
 * @param addr 地址字段中要发送的数据
 * @param addr_bit_len 地址字段的位长度
 * @param dummy_bits 伪字段的位长度
 * @param mosi_data 要在mosi字段中发送的数据缓冲区
 * @param mosi_bit_len 要在mosi字段中发送的数据缓冲区的位长度
 * @param miso_data 数据缓冲区，用于接受miso字段中的数据
 * @param miso_bit_len 接受miso字段中数据的数据缓冲区的位长度
 * @param cs_mark 决定使用哪个cs引脚。0:cs0，1:cs1
 * @param is_write_erase_operation 指示这是写入还是擦除闪存操作
 */
void esp_rom_opiflash_exec_cmd(int spi_num, esp_rom_spiflash_read_mode_t mode,
                                  uint32_t cmd, int cmd_bit_len,
                                  uint32_t addr, int addr_bit_len,
                                  int dummy_bits,
                                  uint8_t* mosi_data, int mosi_bit_len,
                                  uint8_t* miso_data, int miso_bit_len,
                                  uint32_t cs_mask,
                                  bool is_write_erase_operation);

/**
 * @brief 向opi flash发送重置命令
 * @param spi_num spi端口
 * @param mode 闪存操作模式
 */
void esp_rom_opiflash_soft_reset(int spi_num, esp_rom_spiflash_read_mode_t mode);

/**
 * @brief 读取opi闪存ID（用于MX25UM25645G）
 * @param spi_num spi端口
 * @param mode 闪存操作模式
 * @return opi flash id
 */
uint32_t esp_rom_opiflash_read_id(int spi_num, esp_rom_spiflash_read_mode_t mode);

/**
 * @brief 读取opi闪存状态寄存器（用于MX25UM25645G）
 * @param spi_num spi端口
 * @param mode 闪存操作模式
 * @return opi闪光状态值
 */
uint8_t esp_rom_opiflash_rdsr(int spi_num, esp_rom_spiflash_read_mode_t mode);

/**
 * @brief 等待opi闪存状态寄存器空闲
 * @param spi_num spi端口
 * @param mode 闪存操作模式
 */
void esp_rom_opiflash_wait_idle(int spi_num, esp_rom_spiflash_read_mode_t mode);

/**
 * @brief 读取配置寄存器2（用于MX25UM25645G）
 * @param spi_num spi端口
 * @param mode 闪存操作模式
 * @param addr 配置寄存器的地址
 * @return 配置寄存器2的值
 */
uint8_t esp_rom_opiflash_rdcr2(int spi_num, esp_rom_spiflash_read_mode_t mode, uint32_t addr);

/**
 * @brief 写入配置寄存器2（用于MX25UM25645G）
 * @param spi_num spi端口
 * @param mode 闪存操作模式
 * @param addr 配置寄存器的地址
 * @param val 要写入的值
 */
void esp_rom_opiflash_wrcr2(int spi_num, esp_rom_spiflash_read_mode_t mode, uint32_t addr, uint8_t val);

/**
 * @brief 擦除闪存扇区（用于MX25UM25645G）
 * @param spi_num spi端口
 * @param address 要擦除的扇区地址
 * @param mode 闪光操作模式
 * @return 闪光操作结果
 */
esp_rom_spiflash_result_t esp_rom_opiflash_erase_sector(int spi_num, uint32_t address, esp_rom_spiflash_read_mode_t mode);

/**
 * @brief 擦除闪存块（用于MX25UM25645G）
 * @param spi_num spi端口
 * @param address 要擦除的块地址
 * @param mode 闪光操作模式
 * @return 闪光操作结果
 */
esp_rom_spiflash_result_t esp_rom_opiflash_erase_block_64k(int spi_num, uint32_t address, esp_rom_spiflash_read_mode_t mode);

/**
 * @brief 擦除由起始地址和长度定义的闪存区域（对于MX25UM25645G）
 * @param spi_num spi端口
 * @param start_addr 要擦除的起始地址
 * @param area_len 要擦除的erea长度
 * @param mode 闪光操作模式
 * @return 闪光操作结果
 */
esp_rom_spiflash_result_t esp_rom_opiflash_erase_area(int spi_num, uint32_t start_addr, uint32_t area_len, esp_rom_spiflash_read_mode_t mode);

/**
 * @brief 从opi闪存读取数据（用于MX25UM25645G）
 * @param spi_num spi端口
 * @param mode 闪光操作模式
 * @param flash_addr 从中读取数据的闪存地址
 * @param data_addr 接受数据的数据缓冲区
 * @param len 要读取的数据长度
 * @return 闪光操作结果
 */
esp_rom_spiflash_result_t esp_rom_opiflash_read(int spi_num, esp_rom_spiflash_read_mode_t mode, uint32_t flash_addr, uint8_t *data_addr, int len);

/**
 * @brief 将数据写入opi闪存（用于MX25UM25645G）
 * @param spi_num spi端口
 * @param mode 闪光操作模式
 * @param flash_addr 写入数据的闪存地址
 * @param data_addr 写入闪存的数据缓冲区
 * @param len 要写入的数据长度
 * @return 闪光操作结果
 */
esp_rom_spiflash_result_t esp_rom_opiflash_write(int spi_num, esp_rom_spiflash_read_mode_t mode, uint32_t flash_addr, uint8_t *data_addr, uint32_t len);

/**
 * @brief 设置opi闪存操作模式（适用于MX25UM25645G）
 * @param spi_num spi端口
 * @param cur_mode 当前运行模式
 * @param target 要设置的目标操作模式
 */
void esp_rom_opiflash_set_mode(int spi_num, esp_rom_spiflash_read_mode_t cur_mode, esp_rom_spiflash_read_mode_t target_mode);
#endif

#ifdef __cplusplus
}
#endif

#endif

