// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/** \defgroup efuse_API efuse API
  * @brief     ESP32 efuse读/写API
  * @attention
  *
  */

/** @addtogroup efuse_API@{
  */

typedef enum {
    ETS_EFUSE_KEY_PURPOSE_USER = 0,
    ETS_EFUSE_KEY_PURPOSE_RESERVED = 1,
    ETS_EFUSE_KEY_PURPOSE_XTS_AES_256_KEY_1 = 2,
    ETS_EFUSE_KEY_PURPOSE_XTS_AES_256_KEY_2 = 3,
    ETS_EFUSE_KEY_PURPOSE_XTS_AES_128_KEY = 4,
    ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_ALL = 5,
    ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_JTAG = 6,
    ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_DIGITAL_SIGNATURE = 7,
    ETS_EFUSE_KEY_PURPOSE_HMAC_UP = 8,
    ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST0 = 9,
    ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST1 = 10,
    ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST2 = 11,
    ETS_EFUSE_KEY_PURPOSE_MAX,
} ets_efuse_purpose_t;

typedef enum {
    ETS_EFUSE_BLOCK0 = 0,
    ETS_EFUSE_MAC_SPI_SYS_0 = 1,
    ETS_EFUSE_BLOCK_SYS_DATA = 2,
    ETS_EFUSE_BLOCK_USR_DATA = 3,
    ETS_EFUSE_BLOCK_KEY0 = 4,
    ETS_EFUSE_BLOCK_KEY1 = 5,
    ETS_EFUSE_BLOCK_KEY2 = 6,
    ETS_EFUSE_BLOCK_KEY3 = 7,
    ETS_EFUSE_BLOCK_KEY4 = 8,
    ETS_EFUSE_BLOCK_KEY5 = 9,
    ETS_EFUSE_BLOCK_KEY6 = 10,
    ETS_EFUSE_BLOCK_MAX,
} ets_efuse_block_t;

/**
 * @brief 根据apb时钟设置定时，因此不会发生读取错误或写入错误。
 *
 * @param clock: apb时钟为HZ，仅接受5M（在FPGA中）、10M（在FPGA中）、20M、40M、80M。
 *
 * @return ：如果成功，则为0，如果不接受时钟，则为其他
 */
int ets_efuse_set_timing(uint32_t clock);

/**
 * @brief 启用efuse子系统。重置后调用。不需要再次调用。
 */
void ets_efuse_start(void);

/**
  * @brief  Efuse读取操作：将数据从物理Efuse复制到Efuse读取寄存器。
  *
  * @param  null
  *
  * @return ：如果成功，则为0，如果不接受apb时钟，则为其他
  */
int ets_efuse_read(void);

/**
  * @brief  Efuse写入操作：将数据从Efuse写入寄存器复制到Efuse。一次只对一块efuse进行操作。
  *
  * @note 此函数不更新read-efuses，在所有编程完成后调用ets_efuse_read（）。
  *
  * @return ：如果成功，则为0，如果不接受apb时钟，则为其他
  */
int ets_efuse_program(ets_efuse_block_t block);

/**
 * @brief 将所有Efuse程序寄存器设置为零。
 *
 * 在将新数据写入程序寄存器之前调用此命令。
 */
void ets_efuse_clear_program_registers(void);

/**
 * @brief 将密钥数据块编程为efuse块
 *
 * @param key_block 要读取目的的块。必须在ETS_EFUSE_BLOCK_KEY0到ETS_EFUSE_BLOCK_KEY6的范围内。密钥块必须未使用（@ref ETS_EFUSE_Key_BLOCK_unused）。
 * @param purpose 设置此密钥的目的。目的必须已设置。
 * @param data 指向要写入的数据的指针。
 * @param data_len 要写入的数据长度。
 *
 * @note 该函数还为指定的块和块0调用ets_efuse_program（）（设置目的）
 */
int ets_efuse_write_key(ets_efuse_block_t key_block, ets_efuse_purpose_t purpose, const void *data, size_t data_len);


/* @brief 返回特定efuse块的第一个读取寄存器的地址
 *
 * @param block 要查找的efuse块索引
 *
 * @return 如果块无效，则为0，否则为块中第一个字的数字读取寄存器地址。
 */
uint32_t ets_efuse_get_read_register_address(ets_efuse_block_t block);

/**
 * @brief 返回efuse密钥块的当前目的集
 *
 * @param key_block 要读取目的的块。必须在ETS_EFUSE_BLOCK_KEY0到ETS_EFUSE_BLOCK_KEY6的范围内。
 */
ets_efuse_purpose_t ets_efuse_get_key_purpose(ets_efuse_block_t key_block);

/**
 * @brief 查找具有特定目的集的关键块
 *
 * @param purpose 要搜索的目的。
 * @param[out] key_block 如果找到，将设置到键块的指针。如果只需要测试密钥块存在，则可以为NULL。
 * @return 如果找到则为true，如果未找到则为false。如果为false，则key_block指针处的值不变。
 */
bool ets_efuse_find_purpose(ets_efuse_purpose_t purpose, ets_efuse_block_t *key_block);

/**
 * 如果密钥块未使用，则返回true，否则返回false。
 *
 * 未使用的密钥块全部为零内容，不受读或写保护，用途为0（ETS_EFUSE_key_purpose_USER）
 *
 * @param key_block 要检查的键块。
 *
 * @return 如果键块未使用，则为true；如果键块或已使用，或指定的块索引不是键块，则为false。
 */
bool ets_efuse_key_block_unused(ets_efuse_block_t key_block);


/**
 * @brief 搜索未使用的密钥块并返回找到的第一个密钥块。
 *
 * See @ref ets_efuse_key_block_unused用于描述未使用的密钥块。
 *
 * @return 第一个未使用的密钥块，如果未找到未使用的键块，则为ETS_EFUSE_block_MAX。
 */
ets_efuse_block_t ets_efuse_find_unused_key_block(void);

/**
 * @brief 返回未使用的efuse键块数（0-6）
 */
unsigned ets_efuse_count_unused_key_blocks(void);

/**
 * @brief 计算efuse数据块的Reed-Solomon编码值。
 *
 * @param data 指向数据缓冲区的指针（长度32字节）
 * @param rs_values 将编码数据写入的指针（长度为12字节）
 */
void ets_efuse_rs_calculate(const void *data, void *rs_values);

/**
  * @brief  从Efuse读取spi闪存垫配置
  *
  * @return
  * -0表示默认SPI引脚。
  * -默认HSPI引脚为1。
  * -其他值定义自定义引脚配置掩码。引脚按照EFUSE_SPICONFIG_RET_SPICLK、EFUSE_SPICONFIG_RET_SPIQ、EFUSE_StPICONFIG_RET_SPID、EFUSE_PPICONFIG_RET_SPICS0、EFUSE_SPICONFIG-RET_SPIHD宏进行编码。WP引脚（用于四输入/输出模式）未保存在efuse中，且此功能不会返回。
  */
uint32_t ets_efuse_get_spiconfig(void);

/**
  * @brief  从Efuse读取spi flash wp pad
  *
  * @return
  * -0x3f表示无效。
  * -0~46有效。
  */
uint32_t ets_efuse_get_wp_pad(void);

/**
 * @brief 从Efuse读取opi闪存垫配置
 *
 * @return
 * -0表示默认SPI引脚。
 * -其他值定义自定义引脚配置掩码。从LSB开始，每6位代表GPIO编号，相应地代表：DQS、D4、D5、D6、D7。
 */
uint32_t ets_efuse_get_opiconfig(void);

/**
  * @brief  如果Efuse禁用下载模式，则读取
  *
  * @return
  * -efuse禁用下载模式为true。
  * -efuse的false不会禁用下载模式。
  */
bool ets_efuse_download_modes_disabled(void);

/**
  * @brief  读取Efuse是否禁用了传统spi闪存引导模式
  *
  * @return
  * -efusedisablelegacyspiflash引导模式为true。
  * -efuse的false不会禁用传统spi闪存引导模式。
  */
bool ets_efuse_legacy_spi_boot_mode_disabled(void);

/**
  * @brief  读取Efuse的uart打印控制值
  *
  * @return
  * -0表示uart强制打印。
  * -数字复位时GPIO46低时，1用于uart打印。当数字复位时GPIO46为高电平时，2用于uart打印。3表示uart force slient
  */
uint32_t ets_efuse_get_uart_print_control(void);

/**
  * @brief  读取ROM将使用哪个通道进行打印
  *
  * @return
  * -0表示UART0。
  * -1用于UART1。
  */
uint32_t ets_efuse_get_uart_print_channel(void);

/**
  * @brief  读取Efuse是否禁用usb下载模式
  *
  * （如果启用了安全下载模式，也会返回true，因为此模式禁用USB下载。）
  *
  * @return
  * -efuse禁用usb下载模式为true。
  * -efuse的false不会禁用usb下载模式。
  */
bool ets_efuse_usb_download_mode_disabled(void);

/**
  * @brief  如果Efuse禁用微型基本模式，则读取
  *
  * @return
  * -efuse禁用微型基本模式为true。
  * -efuse的false不会禁用微小的基本模式。
  */
bool ets_efuse_tiny_basic_mode_disabled(void);

/**
  * @brief  从Efuse读取usb模块是否禁用
  *
  * @return
  * -efuse禁用usb模块为true。
  * -efuse的false不会禁用usb模块。
  */
bool ets_efuse_usb_module_disabled(void);

/**
  * @brief  读取Efuse是否启用安全下载模式
  *
  * @return
  * -efuse启用安全下载模式为true。
  * -efuse的false不启用安全下载模式。
  */
bool ets_efuse_security_download_modes_enabled(void);

/**
 * @brief 如果在EFuse中启用了安全引导，则返回true
 */
bool ets_efuse_secure_boot_enabled(void);

/**
 * @brief 如果在EFuse中启用了安全引导主动撤销，则返回true
 */
bool ets_efuse_secure_boot_aggressive_revoke_enabled(void);

/**
 * @brief 如果通过EFuse从启动时启用了缓存加密（闪存、PSRAM等），则返回true
 */
bool ets_efuse_cache_encryption_enabled(void);

/**
 * @brief 如果EFuse指示USB需要使用外部phy，则返回true
 */
bool ets_efuse_usb_use_ext_phy(void);

/**
 * @brief 如果EFuse指示USB设备持久性已禁用，则返回true
 */
bool ets_efuse_usb_force_nopersist(void);

/**
 * @brief 如果OPI引脚GPIO33-37由VDDSPI供电，则返回真，否则由VDD33CPU供电
 */
bool ets_efuse_flash_opi_5pads_power_sel_vddspi(void);

/**
 * @brief 如果EFuse指示连接了opi闪存，则返回true。
 */
bool ets_efuse_flash_opi_mode(void);

/**
 * @brief 如果EFuse指示发送闪存恢复命令，则返回true。
 */
bool ets_efuse_force_send_resume(void);

/**
  * @brief  返回我们ROM引导需要等待闪存从Efuse通电的时间
  *
  * @return
  * -uint32不是我们的时间。
  */
uint32_t ets_efuse_get_flash_delay_us(void);

#define EFUSE_SPICONFIG_SPI_DEFAULTS 0
#define EFUSE_SPICONFIG_HSPI_DEFAULTS 1

#define EFUSE_SPICONFIG_RET_SPICLK_MASK         0x3f
#define EFUSE_SPICONFIG_RET_SPICLK_SHIFT        0
#define EFUSE_SPICONFIG_RET_SPICLK(ret)         (((ret) >> EFUSE_SPICONFIG_RET_SPICLK_SHIFT) & EFUSE_SPICONFIG_RET_SPICLK_MASK)

#define EFUSE_SPICONFIG_RET_SPIQ_MASK           0x3f
#define EFUSE_SPICONFIG_RET_SPIQ_SHIFT          6
#define EFUSE_SPICONFIG_RET_SPIQ(ret)           (((ret) >> EFUSE_SPICONFIG_RET_SPIQ_SHIFT) & EFUSE_SPICONFIG_RET_SPIQ_MASK)

#define EFUSE_SPICONFIG_RET_SPID_MASK           0x3f
#define EFUSE_SPICONFIG_RET_SPID_SHIFT          12
#define EFUSE_SPICONFIG_RET_SPID(ret)           (((ret) >> EFUSE_SPICONFIG_RET_SPID_SHIFT) & EFUSE_SPICONFIG_RET_SPID_MASK)

#define EFUSE_SPICONFIG_RET_SPICS0_MASK         0x3f
#define EFUSE_SPICONFIG_RET_SPICS0_SHIFT        18
#define EFUSE_SPICONFIG_RET_SPICS0(ret)         (((ret) >> EFUSE_SPICONFIG_RET_SPICS0_SHIFT) & EFUSE_SPICONFIG_RET_SPICS0_MASK)


#define EFUSE_SPICONFIG_RET_SPIHD_MASK          0x3f
#define EFUSE_SPICONFIG_RET_SPIHD_SHIFT         24
#define EFUSE_SPICONFIG_RET_SPIHD(ret)          (((ret) >> EFUSE_SPICONFIG_RET_SPIHD_SHIFT) & EFUSE_SPICONFIG_RET_SPIHD_MASK)

/**
 * @brief 通过将JTAG HMAC“密钥”写入JTAG_CTRL寄存器，暂时启用JTAG。
 *
 * 如果JTAG已通过燃烧EFUSE_soft_DIS_JTAG EFUSE“软”禁用，则工作。
 *
 * 将使HMAC模块从已保存在efuse中的密钥生成“下游”HMAC值，然后写入JTAG HMAC“密钥”，如果两个密钥匹配，则启用JTAG。
 *
 * @param jtag_hmac_key 指向包含有效密钥的32字节数组的指针。由用户提供。
 * @param key_block 包含此密钥源的密钥块的索引。
 *
 * @return 如果HMAC操作失败或参数无效，则ETS_FAILED，否则ETS_OK。ETS_OK不一定意味着JTAG已启用。
 */
int ets_jtag_enable_temporarily(const uint8_t *jtag_hmac_key, ets_efuse_block_t key_block);

/**
  * @brief  efuse中用于MAC地址的crc8算法
  *
  * @param  unsigned char const*p：指向原始数据的指针。
  *
  * @param  unsigned int len：以字节为单位的数据长度。
  *
  * @return 无符号字符：Crc值。
  */
unsigned char esp_crc8(unsigned char const *p, unsigned int len);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

