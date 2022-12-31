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

#ifndef _ROM_EFUSE_H_
#define _ROM_EFUSE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup efuse_API efuse API
  * @brief     ESP32 efuse读/写API
  * @attention
  *
  */

/** @addtogroup efuse_API@{
  */

/**
  * @brief  执行efuse读取操作，将efuse值更新为efuse读取寄存器。
  *
  * @param  null
  *
  * @return 无效的
  */
void ets_efuse_read_op(void);

/**
  * @brief  执行efuse写入操作，将efuse写入寄存器更新为efuse，然后需要再次调用ets_efuse_read_op。
  *
  * @param  null
  *
  * @return 无效的
  */
void ets_efuse_program_op(void);

/**
  * @brief  在efuse中读取8M模拟时钟值（8位），模拟时钟不会随温度变化。它可用于测试外部xtal频率，请勿触摸此efuse字段。
  *
  * @param  null
  *
  * @return u32:1用于100KHZ，范围为0到255。
  */
uint32_t ets_efuse_get_8M_clock(void);

/**
  * @brief  从Efuse读取spi闪存引脚配置
  *
  * @return
  * -0表示默认SPI引脚。
  * -默认HSPI引脚为1。
  * -其他值定义自定义引脚配置掩码。引脚按照EFUSE_SPICONFIG_RET_SPICLK、EFUSE_SPICONFIG_RET_SPIQ、EFUSE_StPICONFIG_RET_SPID、EFUSE_PPICONFIG_RET_SPICS0、EFUSE_SPICONFIG-RET_SPIHD宏进行编码。WP引脚（用于四输入/输出模式）未保存在efuse中，且此功能不会返回。
  */
uint32_t ets_efuse_get_spiconfig(void);

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
  * @brief  用于efuse检查的crc8算法。
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

#endif /* _ROM_EFUSE_H_ */

