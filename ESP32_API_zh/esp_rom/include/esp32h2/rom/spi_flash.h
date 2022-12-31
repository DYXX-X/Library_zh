// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#ifndef _ROM_SPI_FLASH_H_
#define _ROM_SPI_FLASH_H_

#include <stdint.h>
#include <stdbool.h>

#include "esp_attr.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup spi_flash_api，spi-flash操作相关api
  * @brief spi_flash api
  */

/** @addtogroup spi_flash_api@{
  */

#define PERIPHS_SPI_FLASH_CMD                 SPI_MEM_CMD_REG(1)
#define PERIPHS_SPI_FLASH_ADDR                SPI_MEM_ADDR_REG(1)
#define PERIPHS_SPI_FLASH_CTRL                SPI_MEM_CTRL_REG(1)
#define PERIPHS_SPI_FLASH_CTRL1               SPI_MEM_CTRL1_REG(1)
#define PERIPHS_SPI_FLASH_STATUS              SPI_MEM_RD_STATUS_REG(1)
#define PERIPHS_SPI_FLASH_USRREG              SPI_MEM_USER_REG(1)
#define PERIPHS_SPI_FLASH_USRREG1             SPI_MEM_USER1_REG(1)
#define PERIPHS_SPI_FLASH_USRREG2             SPI_MEM_USER2_REG(1)
#define PERIPHS_SPI_FLASH_C0                  SPI_MEM_W0_REG(1)
#define PERIPHS_SPI_FLASH_C1                  SPI_MEM_W1_REG(1)
#define PERIPHS_SPI_FLASH_C2                  SPI_MEM_W2_REG(1)
#define PERIPHS_SPI_FLASH_C3                  SPI_MEM_W3_REG(1)
#define PERIPHS_SPI_FLASH_C4                  SPI_MEM_W4_REG(1)
#define PERIPHS_SPI_FLASH_C5                  SPI_MEM_W5_REG(1)
#define PERIPHS_SPI_FLASH_C6                  SPI_MEM_W6_REG(1)
#define PERIPHS_SPI_FLASH_C7                  SPI_MEM_W7_REG(1)
#define PERIPHS_SPI_FLASH_TX_CRC              SPI_MEM_TX_CRC_REG(1)

#define SPI0_R_QIO_DUMMY_CYCLELEN             5
#define SPI0_R_QIO_ADDR_BITSLEN               23
#define SPI0_R_FAST_DUMMY_CYCLELEN            7
#define SPI0_R_DIO_DUMMY_CYCLELEN             3
#define SPI0_R_FAST_ADDR_BITSLEN              23
#define SPI0_R_SIO_ADDR_BITSLEN               23

#define SPI1_R_QIO_DUMMY_CYCLELEN             5
#define SPI1_R_QIO_ADDR_BITSLEN               23
#define SPI1_R_FAST_DUMMY_CYCLELEN            7
#define SPI1_R_DIO_DUMMY_CYCLELEN             3
#define SPI1_R_DIO_ADDR_BITSLEN               23
#define SPI1_R_FAST_ADDR_BITSLEN              23
#define SPI1_R_SIO_ADDR_BITSLEN               23

#define ESP_ROM_SPIFLASH_W_SIO_ADDR_BITSLEN   23

#define ESP_ROM_SPIFLASH_TWO_BYTE_STATUS_EN   SPI_MEM_WRSR_2B

//SPI地址寄存器
#define ESP_ROM_SPIFLASH_BYTES_LEN            24
#define ESP_ROM_SPIFLASH_BUFF_BYTE_WRITE_NUM  32
#define ESP_ROM_SPIFLASH_BUFF_BYTE_READ_NUM   16
#define ESP_ROM_SPIFLASH_BUFF_BYTE_READ_BITS  0xf

//SPI状态寄存器
#define  ESP_ROM_SPIFLASH_BUSY_FLAG           BIT0
#define  ESP_ROM_SPIFLASH_WRENABLE_FLAG       BIT1
#define  ESP_ROM_SPIFLASH_BP0                 BIT2
#define  ESP_ROM_SPIFLASH_BP1                 BIT3
#define  ESP_ROM_SPIFLASH_BP2                 BIT4
#define  ESP_ROM_SPIFLASH_WR_PROTECT          (ESP_ROM_SPIFLASH_BP0|ESP_ROM_SPIFLASH_BP1|ESP_ROM_SPIFLASH_BP2)
#define  ESP_ROM_SPIFLASH_QE                  BIT9

#define FLASH_ID_GD25LQ32C  0xC86016

typedef enum {
    ESP_ROM_SPIFLASH_QIO_MODE = 0,
    ESP_ROM_SPIFLASH_QOUT_MODE,
    ESP_ROM_SPIFLASH_DIO_MODE,
    ESP_ROM_SPIFLASH_DOUT_MODE,
    ESP_ROM_SPIFLASH_FASTRD_MODE,
    ESP_ROM_SPIFLASH_SLOWRD_MODE
} esp_rom_spiflash_read_mode_t;

typedef enum {
    ESP_ROM_SPIFLASH_RESULT_OK,
    ESP_ROM_SPIFLASH_RESULT_ERR,
    ESP_ROM_SPIFLASH_RESULT_TIMEOUT
} esp_rom_spiflash_result_t;

typedef struct {
    uint32_t device_id;
    uint32_t chip_size;    // 芯片大小（字节）
    uint32_t block_size;
    uint32_t sector_size;
    uint32_t page_size;
    uint32_t status_mask;
} esp_rom_spiflash_chip_t;

typedef struct {
    uint8_t  data_length;
    uint8_t  read_cmd0;
    uint8_t  read_cmd1;
    uint8_t  write_cmd;
    uint16_t data_mask;
    uint16_t data;
} esp_rom_spiflash_common_cmd_t;

/**
  * @brief 修复SPI硬件与Flash/Ext SRAM高速通信中的错误。请不要在SDK中调用此函数。
  *
  * @param  uint8_t spi:0表示SPI0（缓存访问），1表示SPI1（闪存读/写）。
  *
  * @param  uint8_t freqdiv:Pll为80M，4为20M，3为26.7M，2为40M，1为80M。
  *
  * @return 没有一个
  */
void esp_rom_spiflash_fix_dummylen(uint8_t spi, uint8_t freqdiv);

/**
  * @brief 当从闪存读取WP焊盘时，选择SPI闪存至QIO模式。请不要在SDK中调用此函数。
  *
  * @param  uint8_t wp_gpio_num：wp gpio编号。
  *
  * @param  uint32_t ishspi:0表示spi，1表示hspi，闪存板由捆扎其他决定，位[5:0]spiclk，位[11:6]spiq，位[17:12]spid，位[23:18]spics0，位[29:24]spihd
  *
  * @return 没有一个
  */
void esp_rom_spiflash_select_qiomode(uint8_t wp_gpio_num, uint32_t ishspi);

/**
  * @brief 设置SPI闪存板驱动程序。请不要在SDK中调用此函数。
  *
  * @param  uint8_t wp_gpio_num：wp gpio编号。
  *
  * @param  uint32_t ishspi:0表示spi，1表示hspi，闪存板由捆扎其他决定，位[5:0]spiclk，位[11:6]spiq，位[17:12]spid，位[23:18]spics0，位[29:24]spihd
  *
  * @param  uint8_t *drvs：cpiclk的drvs[0]-位[3:0]，spiq的位[7:4]，spid的drvs[1]-位[3.0]，spiddrvs[2]的drvs[7:4]；spihd的drvs[2]-位[3:4]。值通常由rom代码从falsh读取，函数通常由rom码调用。如果设置了位（3）的值，则该值有效，位[2:0]为实际值。
  *
  * @return 没有一个
  */
void esp_rom_spiflash_set_drvs(uint8_t wp_gpio_num, uint32_t ishspi, uint8_t *drvs);

/**
  * @brief 为焊盘选择SPI闪存功能。请不要在SDK中调用此函数。
  *
  * @param  uint32_t ishspi:0表示spi，1表示hspi，闪存板由捆扎其他决定，位[5:0]spiclk，位[11:6]spiq，位[17:12]spid，位[23:18]spics0，位[29:24]spihd
  *
  * @return 没有一个
  */
void esp_rom_spiflash_select_padsfunc(uint32_t ishspi);

/**
  * @brief SPI闪存初始化，时钟除数为4，使用1行慢速读取模式。请不要在SDK中调用此函数。
  *
  * @param  uint32_t ishspi:0表示spi，1表示hspi，闪存板由捆扎其他决定，位[5:0]spiclk，位[11:6]spiq，位[17:12]spid，位[23:18]spics0，位[29:24]spihd
  *
  * @param  uint8_t legacy：在legacy模式下，行中使用更多SPI命令。
  *
  * @return 没有一个
  */
void esp_rom_spiflash_attach(uint32_t ishspi, bool legacy);

/**
  * @brief SPI读取闪存状态寄存器。我们使用CMD 0x05（RDSR）。请不要在SDK中调用此函数。
  *
  * @param  esp_rom_spiflash_chip_t *spi：从ld文件导出的Flash信息。
  *
  * @param  uint32_t *status：返回Flash状态值的指针。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:读取正常。ESP_ROM_StPIFLASH_RESULT_ERR：读取错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：读取超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_read_status(esp_rom_spiflash_chip_t *spi, uint32_t *status);

/**
  * @brief SPI读闪存状态寄存器位8-15。我们使用CMD 0x35（RDSR2）。请不要在SDK中调用此函数。
  *
  * @param  esp_rom_spiflash_chip_t *spi：从ld文件导出的Flash信息。
  *
  * @param  uint32_t *status：返回Flash状态值的指针。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:读取正常。ESP_ROM_StPIFLASH_RESULT_ERR：读取错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：读取超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_read_statushigh(esp_rom_spiflash_chip_t *spi, uint32_t *status);

/**
  * @brief 将状态写入Falsh状态寄存器。请不要在SDK中调用此函数。
  *
  * @param  esp_rom_spiflash_chip_t *spi：从ld文件导出的Flash信息。
  *
  * @param  uint32_t status_value：值为。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:写入正常。ESP_ROM_StPIFLASH_RESULT_ERR：写入错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：写入超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_write_status(esp_rom_spiflash_chip_t *spi, uint32_t status_value);

/**
  * @brief 使用命令读取闪存状态寄存器。请不要在SDK中调用此函数。
  *
  * @param  esp_rom_spiflash_chip_t *spi：从ld文件导出的Flash信息。
  *
  * @param  uint32_t*status ：返回Flash状态值的指针。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:读取正常。ESP_ROM_StPIFLASH_RESULT_ERR：读取错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：读取超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_read_user_cmd(uint32_t *status, uint8_t cmd);

/**
  * @brief 初始化时配置SPI闪存读取模式。请不要在SDK中调用此函数。
  *
  * @param  esp_rom_spiflash_read_mode_t 模式：QIO/QOUT/DIO/DOUT/FastRD/SlowRD。
  *
  * 此函数不尝试在状态寄存器中设置QIO启用位，调用方对此负责。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:配置正常。ESP_ROM_StPIFLASH_RESULT_ERR:配置错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：配置超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_config_readmode(esp_rom_spiflash_read_mode_t mode);

/**
  * @brief 配置SPI闪存时钟分频器。请不要在SDK中调用此函数。
  *
  * @param  uint8_t freqdiv：时钟除数。
  *
  * @param  uint8_t spi:0表示SPI0，1表示SPI1。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:配置正常。ESP_ROM_StPIFLASH_RESULT_ERR:配置错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：配置超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_config_clk(uint8_t freqdiv, uint8_t spi);

/**
  * @brief 将CommonCmd发送到Flash，这样它就可以进入QIO模式，一些Flash使用不同的CMD。请不要在SDK中调用此函数。
  *
  * @param  esp_rom_spiflash_common_cmd_t *cmd：显示命令操作的结构。
  *
  * @return uint16_t0：不再发送命令。1：转到下一个命令。n>1：跳过（n-1）命令。
  */
uint16_t esp_rom_spiflash_common_cmd(esp_rom_spiflash_common_cmd_t *cmd);

/**
  * @brief 解锁SPI写保护。请不要在SDK中调用此函数。
  *
  * @param  None.
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:解锁正常。ESP_ROM_StPIFLASH_RESULT_ERR:解锁错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：解锁超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_unlock(void);

/**
  * @brief SPI写保护。请不要在SDK中调用此函数。
  *
  * @param  None.
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:锁定正常。ESP_ROM_StPIFLASH_RESULT_ERR:锁定错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：锁定超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_lock(void);

/**
  * @brief 更新SPI闪存参数。请不要在SDK中调用此函数。
  *
  * @param  uint32_t deviceId：从SPI读取的设备ID，低32位。
  *
  * @param  uint32_t chip_size：Flash大小。
  *
  * @param  uint32_t block_size：Flash块大小。
  *
  * @param  uint32_t sector_size：闪存扇区大小。
  *
  * @param  uint32_t page_size：Flash页面大小。
  *
  * @param  uint32_t status_mask：从Flash读取状态时使用的掩码（使用单个CMD）。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:更新正常。ESP_ROM_StPIFLASH_RESULT_ERR:更新错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：更新超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_config_param(uint32_t deviceId, uint32_t chip_size, uint32_t block_size,
        uint32_t sector_size, uint32_t page_size, uint32_t status_mask);

/**
  * @brief 擦除整个闪存芯片。请不要在SDK中调用此函数。
  *
  * @param  None
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:擦除正常。ESP_ROM_StPIFLASH_RESULT_ERR:擦除错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：擦除超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_erase_chip(void);

/**
  * @brief 擦除64KB的闪存块使用SPI闪存命令D8H。请不要在SDK中调用此函数。
  *
  * @param  uint32_t block_num：要擦除的块。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:擦除正常。ESP_ROM_StPIFLASH_RESULT_ERR:擦除错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：擦除超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_erase_block(uint32_t block_num);

/**
  * @brief 擦除一段闪存。使用SPI闪存命令20H。请不要在SDK中调用此函数。
  *
  * @param  uint32_t sector_num：要擦除的扇区。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:擦除正常。ESP_ROM_StPIFLASH_RESULT_ERR:擦除错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：擦除超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_erase_sector(uint32_t sector_num);

/**
  * @brief 擦除某些扇区。请不要在SDK中调用此函数。
  *
  * @param  uint32_t start_addr：要擦除的起始地址，应与扇区对齐。
  *
  * @param  uint32_t area_len：要擦除的长度，应与扇区对齐。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:擦除正常。ESP_ROM_StPIFLASH_RESULT_ERR:擦除错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：擦除超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_erase_area(uint32_t start_addr, uint32_t area_len);

/**
  * @brief 将数据写入闪存，如果需要，应自行擦除。请不要在SDK中调用此函数。
  *
  * @param  uint32_t dest_addr：要写入的地址，应对齐4个字节。
  *
  * @param  const uint32_t*src：指向要写入的数据的指针。
  *
  * @param  uint32_t len：要写入的长度，应对齐4个字节。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:写入正常。ESP_ROM_StPIFLASH_RESULT_ERR:写入错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：写入超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_write(uint32_t dest_addr, const uint32_t *src, int32_t len);

/**
  * @brief 从Flash读取数据，如果需要，您应该自己擦除。请不要在SDK中调用此函数。
  *
  * @param  uint32_t src_addr：要读取的地址，应为4字节对齐。
  *
  * @param  uint32_t *dest：读取数据的buf。
  *
  * @param  uint32_t len：要读取的长度，应对齐4个字节。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:读取正常。ESP_ROM_StPIFLASH_RESULT_ERR:读取错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：读取超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_read(uint32_t src_addr, uint32_t *dest, int32_t len);

/**
  * @brief SPI1进入加密模式。请不要在SDK中调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void esp_rom_spiflash_write_encrypted_enable(void);

/**
  * @brief 准备32字节的数据以进行encrpto写入，如果需要，您应该自己擦除。请不要在SDK中调用此函数。
  *
  * @param  uint32_t flash_addr：要写入的地址，应为32字节对齐。
  *
  * @param  uint32_t *data：指向要写入的数据的指针。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:准备正常。ESP_ROM_StPIFLASH_RESULT_ERR:准备错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：准备超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_prepare_encrypted_data(uint32_t flash_addr, uint32_t *data);

/**
  * @brief SPI1退出加密模式。请不要在SDK中调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void esp_rom_spiflash_write_encrypted_disable(void);

/**
  * @brief 使用透明加密将数据写入闪存。
  * @note 要写入的扇区应该已经被擦除。
  *
  * @note 请不要在SDK中调用此函数。
  *
  * @param  uint32_t flash_addr：要写入的地址，应该是32字节对齐的。
  *
  * @param  uint32_t *data：指向要写入的数据的指针。注意，此指针必须是32位对齐的，数据内容将由加密函数修改。
  *
  * @param  uint32_t len：要写入的长度，应为32字节对齐。
  *
  * @return ESP_ROM_SPIFLASH_RESULT_OK:数据写入成功。ESP_ROM_SPIFLASH_RESULT_ERR:加密写入错误。ESP_ROM_SPIFLASH_RESULT_TIMEOUT：加密写入超时。
  */
esp_rom_spiflash_result_t esp_rom_spiflash_write_encrypted(uint32_t flash_addr, uint32_t *data, uint32_t len);


/* TODO:找出如何将它们映射到新名称*/
typedef enum {
    SPI_ENCRYPT_DESTINATION_FLASH,
} SpiEncryptDest;

typedef esp_rom_spiflash_result_t SpiFlashOpResult;

SpiFlashOpResult SPI_Encrypt_Write(uint32_t flash_addr, const void *data, uint32_t len);
SpiFlashOpResult SPI_Encrypt_Write_Dest(SpiEncryptDest dest, uint32_t flash_addr, const void *data, uint32_t len);
void SPI_Write_Encrypt_Enable(void);
void SPI_Write_Encrypt_Disable(void);

/** @brief 等待SPI闪存写入操作完成
 *
 * @note 请不要在SDK中调用此函数。
 *
 * 读取SPI闪存状态寄存器的“正在写入”位，重复该位直到该位为零（表示写入完成）。
 *
 * @return ESP_ROM_SPIFLASH_RESULT_OK:写入完成ESP_ROM_StPIFLASH_RESULT_ERR:读取状态时出错。
 */
esp_rom_spiflash_result_t esp_rom_spiflash_wait_idle(esp_rom_spiflash_chip_t *spi);


/** @brief 启用四路I/O引脚功能
 *
 * @note 请不要在SDK中调用此函数。
 *
 * 基于efuse SPI引脚配置，设置四路I/O模式的HD&WP引脚功能。
 *
 * @param wp_gpio_num -要为四路I/O重新配置的WP引脚数。
 *
 * @param spiconfig -引脚配置，从ets_efuse_get_spiconfig（）返回。
 * -如果此参数为0，则使用默认SPI引脚，并忽略wp_gpio_num参数。
 * -如果此参数为1，则使用默认HSPI引脚，并忽略wp_gpio_num参数。
 * -对于其他值，此参数编码HD管脚编号和CLK管脚编号。CLK引脚选择用于确定是否使用HSPI或SPI外设（如果CLK引脚是HSPI时钟引脚，则使用HSPI，否则使用SPI）。HD和WP引脚均通过GPIO矩阵配置，以映射到所选外围设备。
 */
void esp_rom_spiflash_select_qio_pins(uint8_t wp_gpio_num, uint32_t spiconfig);


typedef void (* spi_flash_func_t)(void);
typedef SpiFlashOpResult (* spi_flash_op_t)(void);
typedef SpiFlashOpResult (* spi_flash_erase_t)(uint32_t);
typedef SpiFlashOpResult (* spi_flash_rd_t)(uint32_t, uint32_t*, int);
typedef SpiFlashOpResult (* spi_flash_wr_t)(uint32_t, const uint32_t*, int);
typedef SpiFlashOpResult (* spi_flash_ewr_t)(uint32_t, const void*, uint32_t);
typedef SpiFlashOpResult (* spi_flash_wren_t)(void*);

typedef struct {
    uint32_t read_sub_len;
    uint32_t write_sub_len;
    spi_flash_op_t unlock;
    spi_flash_erase_t erase_sector;
    spi_flash_erase_t erase_block;
    spi_flash_rd_t read;
    spi_flash_wr_t write;
    spi_flash_ewr_t encrypt_write;
    spi_flash_func_t check_sus;
    spi_flash_wren_t wren;
    spi_flash_op_t wait_idle;
} spiflash_legacy_funcs_t;


extern const spiflash_legacy_funcs_t *rom_spiflash_legacy_funcs;

/** @brief 传统SPI闪存功能使用的全局ROM spiflash数据
*/
typedef struct {
    esp_rom_spiflash_chip_t chip;
    uint8_t dummy_len_plus[3];
    uint8_t sig_matrix;
} spiflash_legacy_data_t;

extern spiflash_legacy_data_t *rom_spiflash_legacy_data;

/* 定义使H2 ROM合法数据访问与以前的芯片兼容*/
#define g_rom_flashchip (rom_spiflash_legacy_data->chip)
#define g_rom_spiflash_dummy_len_plus (rom_spiflash_legacy_data->dummy_len_plus)

/**
 * @brief 无条件清除WEL位。
 *
 * @return 始终为ESP_ROM_SPIFLASH_RESULT_OK
 */
esp_rom_spiflash_result_t esp_rom_spiflash_write_disable(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* _ROM_SPI_FLASH_H_ */

