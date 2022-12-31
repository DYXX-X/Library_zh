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
#include <stdbool.h>
#include "esp_attr.h"
#include "soc/periph_defs.h"
#include "soc/dport_reg.h"
#include "soc/dport_access.h"

static inline uint32_t periph_ll_get_clk_en_mask(periph_module_t periph)
{
    switch (periph) {
    case PERIPH_LEDC_MODULE:
        return DPORT_LEDC_CLK_EN;
    case PERIPH_UART0_MODULE:
        return DPORT_UART_CLK_EN;
    case PERIPH_UART1_MODULE:
        return DPORT_UART1_CLK_EN;
    case PERIPH_UART2_MODULE:
        return DPORT_UART2_CLK_EN;
    case PERIPH_I2C0_MODULE:
        return DPORT_I2C_EXT0_CLK_EN;
    case PERIPH_I2C1_MODULE:
        return DPORT_I2C_EXT1_CLK_EN;
    case PERIPH_I2S0_MODULE:
        return DPORT_I2S0_CLK_EN;
    case PERIPH_I2S1_MODULE:
        return DPORT_I2S1_CLK_EN;
    case PERIPH_TIMG0_MODULE:
        return DPORT_TIMERGROUP_CLK_EN;
    case PERIPH_TIMG1_MODULE:
        return DPORT_TIMERGROUP1_CLK_EN;
    case PERIPH_PWM0_MODULE:
        return DPORT_PWM0_CLK_EN;
    case PERIPH_PWM1_MODULE:
        return DPORT_PWM1_CLK_EN;
    case PERIPH_UHCI0_MODULE:
        return DPORT_UHCI0_CLK_EN;
    case PERIPH_UHCI1_MODULE:
        return DPORT_UHCI1_CLK_EN;
    case PERIPH_RMT_MODULE:
        return DPORT_RMT_CLK_EN;
    case PERIPH_PCNT_MODULE:
        return DPORT_PCNT_CLK_EN;
    case PERIPH_SPI_MODULE:
        return DPORT_SPI01_CLK_EN;
    case PERIPH_HSPI_MODULE:
        return DPORT_SPI2_CLK_EN;
    case PERIPH_VSPI_MODULE:
        return DPORT_SPI3_CLK_EN;
    case PERIPH_SPI_DMA_MODULE:
        return DPORT_SPI_DMA_CLK_EN;
    case PERIPH_SDMMC_MODULE:
        return DPORT_WIFI_CLK_SDIO_HOST_EN;
    case PERIPH_SDIO_SLAVE_MODULE:
        return DPORT_WIFI_CLK_SDIOSLAVE_EN;
    case PERIPH_TWAI_MODULE:
        return DPORT_TWAI_CLK_EN;
    case PERIPH_EMAC_MODULE:
        return DPORT_WIFI_CLK_EMAC_EN;
    case PERIPH_RNG_MODULE:
        return DPORT_WIFI_CLK_RNG_EN;
    case PERIPH_WIFI_MODULE:
        return DPORT_WIFI_CLK_WIFI_EN_M;
    case PERIPH_BT_MODULE:
        return DPORT_WIFI_CLK_BT_EN_M;
    case PERIPH_WIFI_BT_COMMON_MODULE:
        return DPORT_WIFI_CLK_WIFI_BT_COMMON_M;
    case PERIPH_BT_BASEBAND_MODULE:
        return DPORT_BT_BASEBAND_EN;
    case PERIPH_BT_LC_MODULE:
        return DPORT_BT_LC_EN;
    case PERIPH_AES_MODULE:
        return DPORT_PERI_EN_AES;
    case PERIPH_SHA_MODULE:
        return DPORT_PERI_EN_SHA;
    case PERIPH_RSA_MODULE:
        return DPORT_PERI_EN_RSA;
    default:
        return 0;
    }
}

static inline uint32_t periph_ll_get_rst_en_mask(periph_module_t periph, bool enable)
{
    switch (periph) {
    case PERIPH_LEDC_MODULE:
        return DPORT_LEDC_RST;
    case PERIPH_UART0_MODULE:
        return DPORT_UART_RST;
    case PERIPH_UART1_MODULE:
        return DPORT_UART1_RST;
    case PERIPH_UART2_MODULE:
        return DPORT_UART2_RST;
    case PERIPH_I2C0_MODULE:
        return DPORT_I2C_EXT0_RST;
    case PERIPH_I2C1_MODULE:
        return DPORT_I2C_EXT1_RST;
    case PERIPH_I2S0_MODULE:
        return DPORT_I2S0_RST;
    case PERIPH_I2S1_MODULE:
        return DPORT_I2S1_RST;
    case PERIPH_TIMG0_MODULE:
        return DPORT_TIMERGROUP_RST;
    case PERIPH_TIMG1_MODULE:
        return DPORT_TIMERGROUP1_RST;
    case PERIPH_PWM0_MODULE:
        return DPORT_PWM0_RST;
    case PERIPH_PWM1_MODULE:
        return DPORT_PWM1_RST;
    case PERIPH_UHCI0_MODULE:
        return DPORT_UHCI0_RST;
    case PERIPH_UHCI1_MODULE:
        return DPORT_UHCI1_RST;
    case PERIPH_RMT_MODULE:
        return DPORT_RMT_RST;
    case PERIPH_PCNT_MODULE:
        return DPORT_PCNT_RST;
    case PERIPH_SPI_MODULE:
        return DPORT_SPI01_RST;
    case PERIPH_HSPI_MODULE:
        return DPORT_SPI2_RST;
    case PERIPH_VSPI_MODULE:
        return DPORT_SPI3_RST;
    case PERIPH_SPI_DMA_MODULE:
        return DPORT_SPI_DMA_RST;
    case PERIPH_SDMMC_MODULE:
        return DPORT_SDIO_HOST_RST;
    case PERIPH_SDIO_SLAVE_MODULE:
        return DPORT_SDIO_RST;
    case PERIPH_TWAI_MODULE:
        return DPORT_TWAI_RST;
    case PERIPH_EMAC_MODULE:
        return DPORT_EMAC_RST;
    case PERIPH_AES_MODULE:
        if (enable == true) {
            // 清除数字签名和安全引导单元上的重置，否则AES单元也保持重置状态。
            return (DPORT_PERI_EN_AES | DPORT_PERI_EN_DIGITAL_SIGNATURE | DPORT_PERI_EN_SECUREBOOT);
        } else {
            //不要返回要重置的其他单元，因为这会分别对RSA和SHA单元进行重置。
            return DPORT_PERI_EN_AES;
        }
    case PERIPH_SHA_MODULE:
        if (enable == true) {
            // 在安全启动时清除重置，否则SHA保持重置
            return (DPORT_PERI_EN_SHA | DPORT_PERI_EN_SECUREBOOT);
        } else {
            // 不要在安全启动时断言重置，否则AES将保持重置状态
            return DPORT_PERI_EN_SHA;
        }
    case PERIPH_RSA_MODULE:
        if (enable == true) {
            // 同时清除数字签名上的重置，否则RSA将保持重置状态
            return (DPORT_PERI_EN_RSA | DPORT_PERI_EN_DIGITAL_SIGNATURE);
        } else {
            // 不要重置数字签名单元，因为这也会重置AES
            return DPORT_PERI_EN_RSA;
        }
    default:
        return 0;
    }
}

static inline uint32_t periph_ll_get_clk_en_reg(periph_module_t periph)
{
    switch (periph) {
    case PERIPH_AES_MODULE:
    case PERIPH_SHA_MODULE:
    case PERIPH_RSA_MODULE:
        return DPORT_PERI_CLK_EN_REG;
    case PERIPH_SDMMC_MODULE:
    case PERIPH_SDIO_SLAVE_MODULE:
    case PERIPH_EMAC_MODULE:
    case PERIPH_RNG_MODULE:
    case PERIPH_WIFI_MODULE:
    case PERIPH_BT_MODULE:
    case PERIPH_WIFI_BT_COMMON_MODULE:
    case PERIPH_BT_BASEBAND_MODULE:
    case PERIPH_BT_LC_MODULE:
        return DPORT_WIFI_CLK_EN_REG;
    default:
        return DPORT_PERIP_CLK_EN_REG;
    }
}

static inline uint32_t periph_ll_get_rst_en_reg(periph_module_t periph)
{
    switch (periph) {
    case PERIPH_AES_MODULE:
    case PERIPH_SHA_MODULE:
    case PERIPH_RSA_MODULE:
        return DPORT_PERI_RST_EN_REG;
    case PERIPH_SDMMC_MODULE:
    case PERIPH_SDIO_SLAVE_MODULE:
    case PERIPH_EMAC_MODULE:
    case PERIPH_RNG_MODULE:
    case PERIPH_WIFI_MODULE:
    case PERIPH_BT_MODULE:
    case PERIPH_WIFI_BT_COMMON_MODULE:
    case PERIPH_BT_BASEBAND_MODULE:
    case PERIPH_BT_LC_MODULE:
        return DPORT_CORE_RST_EN_REG;
    default:
        return DPORT_PERIP_RST_EN_REG;
    }
}

static inline void periph_ll_enable_clk_clear_rst(periph_module_t periph)
{
    DPORT_SET_PERI_REG_MASK(periph_ll_get_clk_en_reg(periph), periph_ll_get_clk_en_mask(periph));
    DPORT_CLEAR_PERI_REG_MASK(periph_ll_get_rst_en_reg(periph), periph_ll_get_rst_en_mask(periph, true));
}

static inline void periph_ll_disable_clk_set_rst(periph_module_t periph)
{
    DPORT_CLEAR_PERI_REG_MASK(periph_ll_get_clk_en_reg(periph), periph_ll_get_clk_en_mask(periph));
    DPORT_SET_PERI_REG_MASK(periph_ll_get_rst_en_reg(periph), periph_ll_get_rst_en_mask(periph, false));
}

static inline void IRAM_ATTR periph_ll_wifi_bt_module_enable_clk_clear_rst(void)
{
    DPORT_SET_PERI_REG_MASK(DPORT_WIFI_CLK_EN_REG, DPORT_WIFI_CLK_WIFI_BT_COMMON_M);
    DPORT_CLEAR_PERI_REG_MASK(DPORT_CORE_RST_EN_REG, 0);
}

static inline void IRAM_ATTR periph_ll_wifi_bt_module_disable_clk_set_rst(void)
{
    DPORT_CLEAR_PERI_REG_MASK(DPORT_WIFI_CLK_EN_REG, DPORT_WIFI_CLK_WIFI_BT_COMMON_M);
    DPORT_SET_PERI_REG_MASK(DPORT_CORE_RST_EN_REG, 0);
}

static inline void periph_ll_reset(periph_module_t periph)
{
    DPORT_SET_PERI_REG_MASK(periph_ll_get_rst_en_reg(periph), periph_ll_get_rst_en_mask(periph, false));
    DPORT_CLEAR_PERI_REG_MASK(periph_ll_get_rst_en_reg(periph), periph_ll_get_rst_en_mask(periph, false));
}

static inline bool IRAM_ATTR periph_ll_periph_enabled(periph_module_t periph)
{
    return DPORT_REG_GET_BIT(periph_ll_get_rst_en_reg(periph), periph_ll_get_rst_en_mask(periph, false)) == 0 &&
        DPORT_REG_GET_BIT(periph_ll_get_clk_en_reg(periph), periph_ll_get_clk_en_mask(periph)) != 0;
}

static inline void periph_ll_wifi_module_enable_clk_clear_rst(void)
{
    DPORT_SET_PERI_REG_MASK(DPORT_WIFI_CLK_EN_REG, DPORT_WIFI_CLK_WIFI_EN_M);
    DPORT_CLEAR_PERI_REG_MASK(DPORT_CORE_RST_EN_REG, 0);
}

static inline void periph_ll_wifi_module_disable_clk_set_rst(void)
{
    DPORT_CLEAR_PERI_REG_MASK(DPORT_WIFI_CLK_EN_REG, DPORT_WIFI_CLK_WIFI_EN_M);
    DPORT_SET_PERI_REG_MASK(DPORT_CORE_RST_EN_REG, 0);
}

#ifdef __cplusplus
}
#endif

