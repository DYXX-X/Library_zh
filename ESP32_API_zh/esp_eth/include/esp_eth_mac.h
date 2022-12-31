// 版权所有2019 Espressif Systems（上海）私人有限公司
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

/**
* @brief 以太网MAC
*
*/
typedef struct esp_eth_mac_s esp_eth_mac_t;

/**
* @brief 以太网MAC
*
*/
struct esp_eth_mac_s {
    /**
    * @brief 为以太网MAC设置调解器
    *
    * @param[in] mac: 以太网MAC实例
    * @param[in] eth: 以太网调解器
    *
    * @return
    *      -ESP_OK：成功为以太网MAC设置调解器
    *      -ESP_ERR_INVALID_ARG:为以太网MAC设置调解器失败，因为参数无效
    *
    */
    esp_err_t (*set_mediator)(esp_eth_mac_t *mac, esp_eth_mediator_t *eth);

    /**
    * @brief 初始化以太网MAC
    *
    * @param[in] mac: 以太网MAC实例
    *
    * @return
    *      -ESP_OK：成功初始化以太网MAC
    *      -ESP_ERR_TIMEOUT:由于超时，初始化以太网MAC失败
    *      -ESP_FAIL:初始化以太网MAC失败，因为发生了其他错误
    *
    */
    esp_err_t (*init)(esp_eth_mac_t *mac);

    /**
    * @brief 取消初始化以太网MAC
    *
    * @param[in] mac: 以太网MAC实例
    *
    * @return
    *      -ESP_OK:成功取消初始化以太网MAC
    *      -ESP_FAIL:由于发生错误，取消初始化以太网MAC失败
    *
    */
    esp_err_t (*deinit)(esp_eth_mac_t *mac);

    /**
    * @brief 启动以太网MAC
    *
    * @param[in] mac: 以太网MAC实例
    *
    * @return
    *      -ESP_OK：成功启动以太网MAC
    *      -ESP_FAIL:由于发生其他错误，启动以太网MAC失败
    *
    */
    esp_err_t (*start)(esp_eth_mac_t *mac);

    /**
    * @brief 停止以太网MAC
    *
    * @param[in] mac: 以太网MAC实例
    *
    * @return
    *      -ESP_OK：成功停止以太网MAC
    *      -ESP_FAIL:停止以太网MAC失败，因为发生了一些错误
    *
    */
    esp_err_t (*stop)(esp_eth_mac_t *mac);

    /**
    * @brief 从以太网MAC传输数据包
    *
    * @param[in] mac: 以太网MAC实例
    * @param[in] buf: 要发送的数据包缓冲区
    * @param[in] length: 数据包长度
    *
    * @return
    *      -ESP_OK：成功传输数据包
    *      -ESP_ERR_INVALID_ARG：由于参数无效，传输数据包失败
    *      -ESP_ERR_INVALID_STATE:由于MAC状态错误，传输数据包失败
    *      -ESP_FAIL:传输数据包失败，因为发生了其他错误
    *
    */
    esp_err_t (*transmit)(esp_eth_mac_t *mac, uint8_t *buf, uint32_t length);

    /**
    * @brief 从以太网MAC接收数据包
    *
    * @param[in] mac: 以太网MAC实例
    * @param[out] buf: 将保存接收帧的分组缓冲器
    * @param[out] length: 接收数据包的长度
    *
    * @note buf的内存在Layer2中分配，请确保在处理后释放。
    * @note 在调用此函数之前，“长度”的值应该由用户设置，等于缓冲区的大小。函数返回后，“length”的值表示接收数据的实际长度。
    *
    * @return
    *      -ESP_OK：成功接收数据包
    *      -ESP_ERR_INVALID_ARG：由于参数无效，接收数据包失败
    *      -ESP_ERR_INVALID_SIZE：输入缓冲区大小不足以容纳传入数据。在这种情况下，返回的“长度”值表示传入数据的实际大小。
    *      -ESP_FAIL:由于发生其他错误，接收数据包失败
    *
    */
    esp_err_t (*receive)(esp_eth_mac_t *mac, uint8_t *buf, uint32_t *length);

    /**
    * @brief 读取PHY寄存器
    *
    * @param[in] mac: 以太网MAC实例
    * @param[in] phy_addr: PHY芯片地址（0~31）
    * @param[in] phy_reg: PHY寄存器索引码
    * @param[out] reg_value: PHY寄存器值
    *
    * @return
    *      -ESP_OK：成功读取PHY寄存器
    *      -ESP_ERR_INVALID_ARG：由于参数无效，读取PHY寄存器失败
    *      -ESP_ERR_INVALID_STATE:由于MAC状态错误，读取PHY寄存器失败
    *      -ESP_ERR_TIMEOUT：由于超时，读取PHY寄存器失败
    *      -ESP_FAIL:读取PHY寄存器失败，因为发生了其他错误
    *
    */
    esp_err_t (*read_phy_reg)(esp_eth_mac_t *mac, uint32_t phy_addr, uint32_t phy_reg, uint32_t *reg_value);

    /**
    * @brief 写入PHY寄存器
    *
    * @param[in] mac: 以太网MAC实例
    * @param[in] phy_addr: PHY芯片地址（0~31）
    * @param[in] phy_reg: PHY寄存器索引码
    * @param[in] reg_value: PHY寄存器值
    *
    * @return
    *      -ESP_OK：成功写入PHY寄存器
    *      -ESP_ERR_INVALID_STATE:由于MAC状态错误，写入PHY寄存器失败
    *      -ESP_ERR_TIMEOUT:由于超时，写入PHY寄存器失败
    *      -ESP_FAIL:由于发生其他错误，写入PHY寄存器失败
    *
    */
    esp_err_t (*write_phy_reg)(esp_eth_mac_t *mac, uint32_t phy_addr, uint32_t phy_reg, uint32_t reg_value);

    /**
    * @brief 设置MAC地址
    *
    * @param[in] mac: 以太网MAC实例
    * @param[in] addr: MAC地址
    *
    * @return
    *      -ESP_OK：设置MAC地址成功
    *      -ESP_ERR_INVALID_ARG:由于参数无效，设置MAC地址失败
    *      -ESP_FAIL:由于发生其他错误，设置MAC地址失败
    *
    */
    esp_err_t (*set_addr)(esp_eth_mac_t *mac, uint8_t *addr);

    /**
    * @brief 获取MAC地址
    *
    * @param[in] mac: 以太网MAC实例
    * @param[out] addr: MAC地址
    *
    * @return
    *      -ESP_OK：成功获取MAC地址
    *      -ESP_ERR_INVALID_ARG:获取MAC地址失败，因为参数无效
    *      -ESP_FAIL:由于发生其他错误，获取MAC地址失败
    *
    */
    esp_err_t (*get_addr)(esp_eth_mac_t *mac, uint8_t *addr);

    /**
    * @brief 设置MAC速度
    *
    * @param[in] ma:c 以太网MAC实例
    * @param[in] speed: MAC速度
    *
    * @return
    *      -ESP_OK：成功设置MAC速度
    *      -ESP_ERR_INVALID_ARG：由于参数无效，设置MAC速度失败
    *      -ESP_FAIL:由于发生其他错误，设置MAC速度失败
    *
    */
    esp_err_t (*set_speed)(esp_eth_mac_t *mac, eth_speed_t speed);

    /**
    * @brief 设置MAC的双工模式
    *
    * @param[in] mac: 以太网MAC实例
    * @param[in] duplex: MAC双工
    *
    * @return
    *      -ESP_OK：成功设置MAC双工模式
    *      -ESP_ERR_INVALID_ARG:由于参数无效，设置MAC双工失败
    *      -ESP_FAIL:由于发生其他错误，设置MAC双工失败
    *
    */
    esp_err_t (*set_duplex)(esp_eth_mac_t *mac, eth_duplex_t duplex);

    /**
    * @brief 设置MAC的链接状态
    *
    * @param[in] mac: 以太网MAC实例
    * @param[in] link: 链接状态
    *
    * @return
    *      -ESP_OK：成功设置链接状态
    *      -ESP_ERR_INVALID_ARG：由于参数无效，设置链接状态失败
    *      -ESP_FAIL:由于发生其他错误，设置链接状态失败
    *
    */
    esp_err_t (*set_link)(esp_eth_mac_t *mac, eth_link_t link);

    /**
    * @brief 设置MAC的混杂
    *
    * @param[in] mac: 以太网MAC实例
    * @param[in] enable: 设置为true以启用混杂模式；设置false以禁用混杂模式
    *
    * @return
    *      -ESP_OK：成功设置混杂模式
    *      -ESP_FAIL:由于发生错误，设置混杂模式失败
    *
    */
    esp_err_t (*set_promiscuous)(esp_eth_mac_t *mac, bool enable);

    /**
    * @brief 是否在MAC层上启用流量控制
    *
    * @param[in] mac: 以太网MAC实例
    * @param[in] enable: 设置为true以启用流量控制；设置为false以禁用流量控制
    *
    * @return
    *      -ESP_OK：成功设置流量控制
    *      -ESP_FAIL:由于发生错误，设置流控制失败
    *
    */
    esp_err_t (*enable_flow_ctrl)(esp_eth_mac_t *mac, bool enable);

    /**
    * @brief 设置对等节点的PAUSE功能
    *
    * @param[in] mac: 以太网MAC实例
    * @param[in] ability: 零表示链接伙伴支持暂停功能；非零表示链接伙伴不支持暂停函数
    *
    * @return
    *      -ESP_OK：成功设置对等暂停功能
    *      -ESP_FAIL:由于发生错误，设置对等暂停功能失败
    */
    esp_err_t (*set_peer_pause_ability)(esp_eth_mac_t *mac, uint32_t ability);

    /**
    * @brief 以太网MAC的可用内存
    *
    * @param[in] mac: 以太网MAC实例
    *
    * @return
    *      -ESP_OK:成功释放以太网MAC实例
    *      -ESP_FAIL:由于发生错误，空闲以太网MAC实例失败
    *
    */
    esp_err_t (*del)(esp_eth_mac_t *mac);
};

/**
 * @brief RMII时钟模式选项
 *
 */
typedef enum {
    /**
     * @brief 当选择“Default”时，将使用使用Kconfig配置的默认值。
     *
     */
    EMAC_CLK_DEFAULT,

    /**
     * @brief 从外部输入RMII时钟。选择此选项时，需要配置EMAC时钟GPIO编号。
     *
     * @note MAC将从外部获取RMII时钟。注意，ESP32仅支持GPIO0输入RMII时钟。
     *
     */
    EMAC_CLK_EXT_IN,

    /**
     * @brief 从内部APLL时钟输出RMII时钟。选择此选项时，需要配置EMAC时钟GPIO编号。
     *
     */
    EMAC_CLK_OUT
} emac_rmii_clock_mode_t;

/**
 * @brief RMII时钟GPIO编号选项
 *
 */
typedef enum {
    /**
     * @brief MAC将在该GPIO从外部获取RMII时钟。
     *
     * @note ESP32仅支持GPIO0输入RMII时钟。
     *
     */
    EMAC_CLK_IN_GPIO = 0,

    /**
     * @brief GPIO0可从内部APLL时钟输出RMII时钟
     *
     * @note GPIO0可设置为输出预分频PLL时钟（仅限测试！）。启用此选项将配置GPIO0以输出50MHz时钟。事实上，该时钟与EMAC外围设备没有直接关系。有时，这个时钟不能很好地与您的PHY芯片配合使用。您可能需要在GPIO0之后添加一些额外的设备（例如反相器）。注意，在GPIO0上输出RMII时钟是一种实验实践。如果您希望以太网与WiFi一起工作，请不要选择GPIO0输出模式以保持稳定。
     *
     */
    EMAC_APPL_CLK_OUT_GPIO = 0,

    /**
     * @brief GPIO16提供的内部APLL时钟输出RMII时钟
     *
     */
    EMAC_CLK_OUT_GPIO = 16,

    /**
     * @brief GPIO17提供的内部APLL时钟的反相输出RMII时钟
     *
     */
    EMAC_CLK_OUT_180_GPIO = 17
} emac_rmii_clock_gpio_t;

/**
 * @brief 以太网MAC时钟配置
 *
 */
typedef union {
    struct {
        // MII接口未完全实现。。。
        // 为MII模式下的GPIO编号、时钟源等预留
    } mii; /*!< EMAC MII时钟配置*/
    struct {
        emac_rmii_clock_mode_t clock_mode; /*!< RMII时钟模式配置*/
        emac_rmii_clock_gpio_t clock_gpio; /*!< RMII时钟GPIO配置*/
    } rmii; /*!< EMAC RMII时钟配置*/
} eth_mac_clock_config_t;


/**
* @brief 以太网MAC对象的配置
*
*/
typedef struct {
    uint32_t sw_reset_timeout_ms;        /*!< 软件重置超时值（单位：ms）*/
    uint32_t rx_task_stack_size;         /*!< 接收任务的堆栈大小*/
    uint32_t rx_task_prio;               /*!< 接收任务的优先级*/
    int smi_mdc_gpio_num;                /*!< SMI MDC GPIO编号，设置为-1可以绕过SMI GPIO配置*/
    int smi_mdio_gpio_num;               /*!< SMI MDIO GPIO编号，设置为-1可绕过SMI GPIO配置*/
    uint32_t flags;                      /*!< 为mac驱动程序指定额外功能的标志*/
    eth_data_interface_t interface;      /*!< 至PHY的EMAC数据接口（MII/RMII）*/
    eth_mac_clock_config_t clock_config; /*!< EMAC接口时钟配置*/
} eth_mac_config_t;

#define ETH_MAC_FLAG_WORK_WITH_CACHE_DISABLE (1 << 0) /*!< 禁用缓存时，MAC驱动程序可以工作*/
#define ETH_MAC_FLAG_PIN_TO_CORE (1 << 1)             /*!< 将MAC任务固定到安装驱动程序的CPU核心*/

/**
 * @brief 以太网MAC对象的默认配置
 *
 */
#define ETH_MAC_DEFAULT_CONFIG()                          \
    {                                                     \
        .sw_reset_timeout_ms = 100,                       \
        .rx_task_stack_size = 2048,                       \
        .rx_task_prio = 15,                               \
        .smi_mdc_gpio_num = 23,                           \
        .smi_mdio_gpio_num = 18,                          \
        .flags = 0,                                       \
        .interface = EMAC_DATA_INTERFACE_RMII,            \
        .clock_config =                                   \
        {                                                 \
            .rmii =                                       \
            {                                             \
                .clock_mode = EMAC_CLK_DEFAULT,           \
                .clock_gpio = EMAC_CLK_IN_GPIO            \
            }                                             \
        }                                                 \
    }

#if CONFIG_ETH_USE_ESP32_EMAC
/**
* @brief 创建ESP32以太网MAC实例
*
* @param config: 以太网MAC配置
*
* @return
*      -实例：成功创建MAC实例
*      -NULL：创建MAC实例失败，因为发生了一些错误
*/
esp_eth_mac_t *esp_eth_mac_new_esp32(const eth_mac_config_t *config);
#endif // CONFIG_ETH_USE_ESP32_EMAC

#if CONFIG_ETH_SPI_ETHERNET_DM9051
/**
 * @brief DM9051特定配置
 *
 */
typedef struct {
    void *spi_hdl;     /*!< SPI设备驱动程序的句柄*/
    int int_gpio_num;  /*!< 中断GPIO编号*/
} eth_dm9051_config_t;

/**
 * @brief 默认DM9051特定配置
 *
 */
#define ETH_DM9051_DEFAULT_CONFIG(spi_device) \
    {                                         \
        .spi_hdl = spi_device,                \
        .int_gpio_num = 4,                    \
    }

/**
* @brief 创建DM9051以太网MAC实例
*
* @param dm9051_config: DM9051特定配置
* @param mac_config: 以太网MAC配置
*
* @return
*      -实例：成功创建MAC实例
*      -NULL：创建MAC实例失败，因为发生了一些错误
*/
esp_eth_mac_t *esp_eth_mac_new_dm9051(const eth_dm9051_config_t *dm9051_config, const eth_mac_config_t *mac_config);
#endif // CONFIG_ETH_SPI_ETHERNET_DM9051

#if CONFIG_ETH_SPI_ETHERNET_W5500
/**
 * @brief W5500特定配置
 *
 */
typedef struct {
    void *spi_hdl;     /*!< SPI设备驱动程序的句柄*/
    int int_gpio_num;  /*!< 中断GPIO编号*/
} eth_w5500_config_t;

/**
 * @brief 默认W5500特定配置
 *
 */
#define ETH_W5500_DEFAULT_CONFIG(spi_device) \
    {                                        \
        .spi_hdl = spi_device,               \
        .int_gpio_num = 4,                   \
    }

/**
* @brief 创建W5500以太网MAC实例
*
* @param w5500_config: W5500特定配置
* @param mac_config: 以太网MAC配置
*
* @return
*      -实例：成功创建MAC实例
*      -NULL：创建MAC实例失败，因为发生了一些错误
*/
esp_eth_mac_t *esp_eth_mac_new_w5500(const eth_w5500_config_t *w5500_config, const eth_mac_config_t *mac_config);
#endif // CONFIG_ETH_SPI_ETHERNET_W5500

#if CONFIG_ETH_SPI_ETHERNET_KSZ8851SNL
/**
 * @brief KSZ8851SNL特定配置
 *
 */
typedef struct {
    void *spi_hdl;     /*!< SPI设备驱动程序的句柄*/
    int int_gpio_num;  /*!< 中断GPIO编号*/
} eth_ksz8851snl_config_t;

/**
 * @brief 默认KSZ8851SNL特定配置
 *
 */
#define ETH_KSZ8851SNL_DEFAULT_CONFIG(spi_device) \
    {                                        \
        .spi_hdl = spi_device,               \
        .int_gpio_num = 14,                   \
    }

/**
* @brief 创建KSZ8851SNL以太网MAC实例
*
* @param ksz8851snl_config: KSZ8851SNL特定配置
* @param mac_config: 以太网MAC配置
*
* @return
*      -实例：成功创建MAC实例
*      -NULL：创建MAC实例失败，因为发生了一些错误
*/
esp_eth_mac_t *esp_eth_mac_new_ksz8851snl(const eth_ksz8851snl_config_t *ksz8851snl_config, const eth_mac_config_t *mac_config);
#endif // CONFIG_ETH_SPI_ETHERNET_KSZ8851

#if CONFIG_ETH_USE_OPENETH
/**
* @brief 创建OpenCores以太网MAC实例
*
* @param config: 以太网MAC配置
*
* @return
*      -实例：成功创建MAC实例
*      -NULL：创建MAC实例失败，因为发生了一些错误
*/
esp_eth_mac_t *esp_eth_mac_new_openeth(const eth_mac_config_t *config);
#endif // CONFIG_ETH_USE_OPENETH

#ifdef __cplusplus
}
#endif

