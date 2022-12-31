// 版权所有2019-2021 Espressif Systems（Shanghai）PTE LTD
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

#include <stdbool.h>
#include "esp_eth_com.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ETH_PHY_ADDR_AUTO (-1)

/**
* @brief 以太网PHY
*
*/
typedef struct esp_eth_phy_s esp_eth_phy_t;

/**
* @brief 以太网PHY
*
*/
struct esp_eth_phy_s {
    /**
    * @brief 为PHY设置调解器
    *
    * @param[in] phy: 以太网PHY实例
    * @param[in] mediator: 以太网驱动程序中介器
    *
    * @return
    *      -ESP_OK：成功为以太网PHY实例设置调解器
    *      -ESP_ERR_INVALID_ARG：为以太网PHY实例设置调解器失败，因为某些参数无效
    *
    */
    esp_err_t (*set_mediator)(esp_eth_phy_t *phy, esp_eth_mediator_t *mediator);

    /**
    * @brief 软件重置以太网PHY
    *
    * @param[in] phy: 以太网PHY实例
    *
    * @return
    *      -ESP_OK：成功重置以太网PHY
    *      -ESP_FAIL:重置以太网PHY失败，因为发生了一些错误
    *
    */
    esp_err_t (*reset)(esp_eth_phy_t *phy);

    /**
    * @brief 硬件重置以太网PHY
    *
    * @note 硬件重置主要通过下拉和上拉PHY的nRST引脚完成
    *
    * @param[in] phy: 以太网PHY实例
    *
    * @return
    *      -ESP_OK：成功重置以太网PHY
    *      -ESP_FAIL:重置以太网PHY失败，因为发生了一些错误
    *
    */
    esp_err_t (*reset_hw)(esp_eth_phy_t *phy);

    /**
    * @brief 初始化以太网PHY
    *
    * @param[in] phy: 以太网PHY实例
    *
    * @return
    *      -ESP_OK：成功初始化以太网PHY
    *      -ESP_FAIL:初始化以太网PHY失败，因为发生了一些错误
    *
    */
    esp_err_t (*init)(esp_eth_phy_t *phy);

    /**
    * @brief 取消初始化以太网PHY
    *
    * @param[in] phyL 以太网PHY实例
    *
    * @return
    *      -ESP_OK：成功取消初始化以太网PHY
    *      -ESP_FAIL:由于发生错误，取消初始化以太网PHY失败
    *
    */
    esp_err_t (*deinit)(esp_eth_phy_t *phy);

    /**
    * @brief 开始自动协商
    *
    * @param[in] phy: 以太网PHY实例
    *
    * @return
    *      -ESP_OK:成功重启自动协商
    *      -ESP_FAIL:重新启动自动协商失败，因为发生了一些错误
    *
    */
    esp_err_t (*negotiate)(esp_eth_phy_t *phy);

    /**
    * @brief 获取以太网PHY链路状态
    *
    * @param[in] phy: 以太网PHY实例
    *
    * @return
    *      -ESP_OK：成功获取以太网PHY链路状态
    *      -ESP_FAIL:获取以太网PHY链路状态失败，因为发生了一些错误
    *
    */
    esp_err_t (*get_link)(esp_eth_phy_t *phy);

    /**
    * @brief 以太网PHY的功率控制
    *
    * @param[in] phy: 以太网PHY实例
    * @param[in] enable: 设置为true，以开启以太网PHY；ser false关闭以太网PHY
    *
    * @return
    *      -ESP_OK：成功控制以太网PHY电源
    *      -ESP_FAIL:由于发生错误，控制以太网PHY电源失败
    *
    */
    esp_err_t (*pwrctl)(esp_eth_phy_t *phy, bool enable);

    /**
    * @brief 设置PHY芯片地址
    *
    * @param[in] phy: 以太网PHY实例
    * @param[in] addr: PHY芯片地址
    *
    * @return
    *      -ESP_OK：成功设置以太网PHY地址
    *      -ESP_FAIL:设置以太网PHY地址失败，因为发生了一些错误
    *
    */
    esp_err_t (*set_addr)(esp_eth_phy_t *phy, uint32_t addr);

    /**
    * @brief 获取PHY芯片地址
    *
    * @param[in] phy: 以太网PHY实例
    * @param[out] addr: PHY芯片地址
    *
    * @return
    *      -ESP_OK：成功获取以太网PHY地址
    *      -ESP_ERR_INVALID_ARG：由于参数无效，获取以太网PHY地址失败
    *
    */
    esp_err_t (*get_addr)(esp_eth_phy_t *phy, uint32_t *addr);

    /**
    * @brief MAC层支持的广告暂停功能
    *
    * @param[in] phy: 以太网PHY实例
    * @param[out] addr: 暂停功能
    *
    * @return
    *      -ESP_OK:广告暂停功能成功
    *      -ESP_ERR_INVALID_ARG:由于参数无效，播发暂停功能失败
    *
    */
    esp_err_t (*advertise_pause_ability)(esp_eth_phy_t *phy, uint32_t ability);

    /**
    * @brief
    *
    * @param[in] phy: 以太网PHY实例
    * @param[in] enable: 启用或禁用PHY环回
    *
    * @return
    *      -ESP_OK：成功配置PHY实例环回功能
    *      -ESP_FAIL:PHY实例环回配置失败，因为发生了一些错误
    *
    */
    esp_err_t (*loopback)(esp_eth_phy_t *phy, bool enable);

    /**
    * @brief 以太网PHY实例的可用内存
    *
    * @param[in] phy: 以太网PHY实例
    *
    * @return
    *      -ESP_OK:成功释放PHY实例
    *      -ESP_FAIL:由于发生错误，释放PHY实例失败
    *
    */
    esp_err_t (*del)(esp_eth_phy_t *phy);
};

/**
* @brief 以太网PHY配置
*
*/
typedef struct {
    int32_t phy_addr;             /*!< PHY地址，设置为-1以在初始化阶段启用PHY地址检测*/
    uint32_t reset_timeout_ms;    /*!< 重置超时值（单位：ms）*/
    uint32_t autonego_timeout_ms; /*!< 自动协商超时值（单位：毫秒）*/
    int reset_gpio_num;           /*!< 重置GPIO编号，-1表示无硬件重置*/
} eth_phy_config_t;

/**
 * @brief 以太网PHY对象的默认配置
 *
 */
#define ETH_PHY_DEFAULT_CONFIG()           \
    {                                      \
        .phy_addr = ESP_ETH_PHY_ADDR_AUTO, \
        .reset_timeout_ms = 100,           \
        .autonego_timeout_ms = 4000,       \
        .reset_gpio_num = 5,               \
    }

/**
* @brief 创建IP101的PHY实例
*
* @param[in] config: PHY配置
*
* @return
*      -实例：成功创建PHY实例
*      -NULL：由于发生错误，创建PHY实例失败
*/
esp_eth_phy_t *esp_eth_phy_new_ip101(const eth_phy_config_t *config);

/**
* @brief 创建RTL8201的PHY实例
*
* @param[in] config: PHY配置
*
* @return
*      -实例：成功创建PHY实例
*      -NULL：由于发生错误，创建PHY实例失败
*/
esp_eth_phy_t *esp_eth_phy_new_rtl8201(const eth_phy_config_t *config);

/**
* @brief 创建LAN87xx的PHY实例
*
* @param[in] config: PHY配置
*
* @return
*      -实例：成功创建PHY实例
*      -NULL：由于发生错误，创建PHY实例失败
*/
esp_eth_phy_t *esp_eth_phy_new_lan87xx(const eth_phy_config_t *config);

/**
* @brief 创建LAN8720的PHY实例
*
* @note 出于ESP-IDF向后兼容性的原因。在所有其他情况下，请改用esp_eth_phy_new_lan87xx。
*
* @param[in] config: PHY配置
*
* @return
*      -实例：成功创建PHY实例
*      -NULL：由于发生错误，创建PHY实例失败
*/
static inline esp_eth_phy_t *esp_eth_phy_new_lan8720(const eth_phy_config_t *config)
{
    return esp_eth_phy_new_lan87xx(config);
}

/**
* @brief 创建DP83848的PHY实例
*
* @param[in] config: PHY配置
*
* @return
*      -实例：成功创建PHY实例
*      -NULL：由于发生错误，创建PHY实例失败
*/
esp_eth_phy_t *esp_eth_phy_new_dp83848(const eth_phy_config_t *config);

/**
* @brief 创建KSZ8041的PHY实例
*
* @param[in] config: PHY配置
*
* @return
*      -实例：成功创建PHY实例
*      -NULL：由于发生错误，创建PHY实例失败
*/
esp_eth_phy_t *esp_eth_phy_new_ksz8041(const eth_phy_config_t *config);

/**
* @brief 创建KSZ8081的PHY实例
*
* @param[in] config: PHY配置
*
* @return
*      -实例：成功创建PHY实例
*      -NULL：由于发生错误，创建PHY实例失败
*/
esp_eth_phy_t *esp_eth_phy_new_ksz8081(const eth_phy_config_t *config);

#if CONFIG_ETH_SPI_ETHERNET_DM9051
/**
* @brief 创建DM9051的PHY实例
*
* @param[in] config: PHY配置
*
* @return
*      -实例：成功创建PHY实例
*      -NULL：由于发生错误，创建PHY实例失败
*/
esp_eth_phy_t *esp_eth_phy_new_dm9051(const eth_phy_config_t *config);
#endif

#if CONFIG_ETH_SPI_ETHERNET_W5500
/**
* @brief 创建W5500的PHY实例
*
* @param[in] config: PHY配置
*
* @return
*      -实例：成功创建PHY实例
*      -NULL：由于发生错误，创建PHY实例失败
*/
esp_eth_phy_t *esp_eth_phy_new_w5500(const eth_phy_config_t *config);
#endif

#if CONFIG_ETH_SPI_ETHERNET_KSZ8851SNL
/**
* @brief 创建KSZ8851SNL的PHY实例
*
* @param[in] config: PHY配置
*
* @return
*      -实例：成功创建PHY实例
*      -NULL：由于发生错误，创建PHY实例失败
*/
esp_eth_phy_t *esp_eth_phy_new_ksz8851snl(const eth_phy_config_t *config);
#endif
#ifdef __cplusplus
}
#endif

