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

#include "esp_eth_com.h"
#include "esp_eth_mac.h"
#include "esp_eth_phy.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief 以太网驱动程序句柄
*
*/
typedef void *esp_eth_handle_t;

/**
* @brief 以太网驱动程序配置
*
*/
typedef struct {
    /**
    * @brief 以太网MAC对象
    *
    */
    esp_eth_mac_t *mac;

    /**
    * @brief 以太网PHY对象
    *
    */
    esp_eth_phy_t *phy;

    /**
    * @brief 检查以太网链路状态的周期时间
    *
    */
    uint32_t check_link_period_ms;

    /**
    * @brief 将帧缓冲区输入到用户堆栈
    *
    * @param[in] eth_handle: 以太网驱动程序句柄
    * @param[in] buffer: 将输入到上层堆栈的帧缓冲区
    * @param[in] length: 帧缓冲区的长度
    *
    * @return
    *      -ESP_OK：成功将帧缓冲区输入到上层堆栈
    *      -ESP_FAIL：将缓冲区输入上层堆栈时出错
    *
    */
    esp_err_t (*stack_input)(esp_eth_handle_t eth_handle, uint8_t *buffer, uint32_t length, void *priv);

    /**
    * @brief 低级初始化完成时调用回调函数
    *
    * @param[in] eth_handle: 以太网驱动程序句柄
    *
    * @return
    *       -ESP_OK：成功处理超低级别初始化
    *       -ESP_FAIL：处理超低级初始化时出错
    */
    esp_err_t (*on_lowlevel_init_done)(esp_eth_handle_t eth_handle);

    /**
    * @brief 完成低级去初始化时调用回调函数
    *
    * @param[in] eth_handle: 以太网驱动程序句柄
    *
    * @return
    *       -ESP_OK：成功处理超低级去初始化
    *       -ESP_FAIL：处理超低级去初始化时出错
    */
    esp_err_t (*on_lowlevel_deinit_done)(esp_eth_handle_t eth_handle);

    /**
    * @brief 读取PHY寄存器
    *
    * @note 通常，PHY寄存器读/写功能由MAC（SMI接口）提供，但如果PHY设备由其他接口（例如I2C）管理，则用户需要实现相应的读/写。将此设置为NULL意味着您的PHY设备由MAC的SMI接口管理。
    *
    * @param[in] eth_handle: 以太网驱动程序句柄
    * @param[in] phy_addr: PHY芯片地址（0~31）
    * @param[in] phy_reg: PHY寄存器索引码
    * @param[out] reg_value: PHY寄存器值
    *
    * @return
    *      -ESP_OK：成功读取PHY寄存器
    *      -ESP_ERR_INVALID_ARG：由于参数无效，读取PHY寄存器失败
    *      -ESP_ERR_TIMEOUT：由于超时，读取PHY寄存器失败
    *      -ESP_FAIL:读取PHY寄存器失败，因为发生了其他错误
    */
    esp_err_t (*read_phy_reg)(esp_eth_handle_t eth_handle, uint32_t phy_addr, uint32_t phy_reg, uint32_t *reg_value);

    /**
    * @brief 写入PHY寄存器
    *
    * @note 通常，PHY寄存器读/写功能由MAC（SMI接口）提供，但如果PHY设备由其他接口（例如I2C）管理，则用户需要实现相应的读/写。将此设置为NULL意味着您的PHY设备由MAC的SMI接口管理。
    *
    * @param[in] eth_handle: 以太网驱动程序句柄
    * @param[in] phy_addr: PHY芯片地址（0~31）
    * @param[in] phy_reg: PHY寄存器索引码
    * @param[in] reg_value: PHY寄存器值
    *
    * @return
    *      -ESP_OK：成功写入PHY寄存器
    *      -ESP_ERR_INVALID_ARG：由于参数无效，读取PHY寄存器失败
    *      -ESP_ERR_TIMEOUT:由于超时，写入PHY寄存器失败
    *      -ESP_FAIL:由于发生其他错误，写入PHY寄存器失败
    */
    esp_err_t (*write_phy_reg)(esp_eth_handle_t eth_handle, uint32_t phy_addr, uint32_t phy_reg, uint32_t reg_value);
} esp_eth_config_t;

/**
 * @brief 以太网驱动程序的默认配置
 *
 */
#define ETH_DEFAULT_CONFIG(emac, ephy)   \
    {                                    \
        .mac = emac,                     \
        .phy = ephy,                     \
        .check_link_period_ms = 2000,    \
        .stack_input = NULL,             \
        .on_lowlevel_init_done = NULL,   \
        .on_lowlevel_deinit_done = NULL, \
        .read_phy_reg = NULL,            \
        .write_phy_reg = NULL,           \
    }

/**
* @brief 安装以太网驱动程序
*
* @param[in]  config: 以太网驱动程序的配置
* @param[out] out_hdl: 以太网驱动程序句柄
*
* @return
*       -ESP_OK:成功安装ESP_eth驱动程序
*       -ESP_ERR_INVALID_ARG:由于某些无效参数，安装ESP_eth驱动程序失败
*       -ESP_ERR_NO_MEM:安装ESP_eth驱动程序失败，因为没有驱动程序的内存
*       -ESP_FAIL:由于发生其他错误，安装ESP_eth驱动程序失败
*/
esp_err_t esp_eth_driver_install(const esp_eth_config_t *config, esp_eth_handle_t *out_hdl);

/**
* @brief 卸载以太网驱动程序
* @note 不建议卸载以太网驱动程序，除非它在应用程序代码中不再使用。要卸载以太网驱动程序，您必须确保已释放对该驱动程序的所有引用。只有当引用计数器等于1时，才能成功卸载以太网驱动程序。
*
* @param[in] hdl: 以太网驱动程序句柄
*
* @return
*       -ESP_OK:成功卸载ESP_eth驱动程序
*       -ESP_ERR_INVALID_ARG:由于某些无效参数，卸载ESP_eth驱动程序失败
*       -ESP_ERR_INVALID_STATE:卸载ESP_eth驱动程序失败，因为它有多个引用
*       -ESP_FAIL:卸载ESP_eth驱动程序失败，因为发生了其他错误
*/
esp_err_t esp_eth_driver_uninstall(esp_eth_handle_t hdl);

/**
* @brief 在独立模式下启动以太网驱动程序**仅**（即无TCP/IP堆栈）
*
* @note 此API将启动驱动程序状态机和内部软件计时器（用于检查链接状态）。
*
* @param[in] hdl 以太网驱动程序句柄
*
* @return
*       -ESP_OK：成功启动ESP_eth驱动程序
*       -ESP_ERR_INVALID_ARG:由于某些无效参数，启动ESP_eth驱动程序失败
*       -ESP_ERR_INVALID_STATE:启动ESP_eth驱动程序失败，因为驱动程序已启动
*       -ESP_FAIL:由于发生其他错误，启动ESP_eth驱动程序失败
*/
esp_err_t esp_eth_start(esp_eth_handle_t hdl);

/**
* @brief 停止以太网驱动程序
*
* @note 此函数执行“esp_eth_start”的opsite操作。
*
* @param[in] hdl 以太网驱动程序句柄
* @return
*       -ESP_OK：成功停止ESP_eth驱动程序
*       -ESP_ERR_INVALID_ARG:由于某些无效参数，停止ESP_eth驱动程序失败
*       -ESP_ERR_INVALID_STATE:停止ESP_eth驱动程序失败，因为驱动程序尚未启动
*       -ESP_FAIL:由于发生其他错误，停止ESP_eth驱动程序失败
*/
esp_err_t esp_eth_stop(esp_eth_handle_t hdl);

/**
* @brief 更新以太网数据输入路径（即指定传递输入缓冲区的位置）
*
* @note 安装驱动程序后，以太网仍然不知道在哪里传递输入缓冲区。事实上，这个API注册了一个回调函数，当以太网接收到新的数据包时会调用该函数。
*
* @param[in] hdl 以太网驱动程序句柄
* @param[in] stack_input 函数指针，对传入的数据包进行实际处理
* @param[in] priv 私有资源，无需任何修改即可传递给“stack_input”回调
* @return
*       -ESP_OK:成功更新输入路径
*       -ESP_ERR_INVALID_ARG:由于某些无效参数，更新输入路径失败
*       -ESP_FAIL:由于发生其他错误，更新输入路径失败
*/
esp_err_t esp_eth_update_input_path(
    esp_eth_handle_t hdl,
    esp_err_t (*stack_input)(esp_eth_handle_t hdl, uint8_t *buffer, uint32_t length, void *priv),
    void *priv);

/**
* @brief 常规传输
*
* @param[in] hdl: 以太网驱动程序句柄
* @param[in] buf: 要传输的数据包的缓冲区
* @param[in] length: 要传输的缓冲区长度
*
* @return
*       -ESP_OK：成功传输帧缓冲区
*       -ESP_ERR_INVALID_ARG：由于某些无效参数，传输帧缓冲区失败
*       -ESP_FAIL:由于发生其他错误，传输帧缓冲区失败
*/
esp_err_t esp_eth_transmit(esp_eth_handle_t hdl, void *buf, size_t length);

/**
* @brief 由于以太网不支持轮询，通用接收已被弃用，不能从应用程序代码访问。
*
* @param[in] hdl: 以太网驱动程序句柄
* @param[out] buf: 保存接收到的数据包的缓冲区
* @param[out] length: 接收数据包的长度
*
* @note 在调用此函数之前，“长度”的值应该由用户设置，等于缓冲区的大小。函数返回后，“length”的值表示接收数据的实际长度。
* @note 此API是意外暴露的，用户不应在其应用程序中使用此API。以太网驱动程序是中断驱动的，不支持轮询模式。相反，用户应该使用“esp_eth_update_input_path”注册输入回调。
*
* @return
*       -ESP_OK：成功接收帧缓冲区
*       -ESP_ERR_INVALID_ARG：由于某些无效参数，接收帧缓冲区失败
*       -ESP_ERR_INVALID_SIZE：输入缓冲区大小不足以容纳传入数据。在这种情况下，返回的“长度”值表示传入数据的实际大小。
*       -ESP_FAIL:由于发生其他错误，接收帧缓冲区失败
*/
esp_err_t esp_eth_receive(esp_eth_handle_t hdl, uint8_t *buf, uint32_t *length) __attribute__((deprecated("Ethernet driver is interrupt driven only, please register input callback with esp_eth_update_input_path")));

/**
* @brief Ethent驱动程序的其他IO功能
*
* @param[in] hdl: 以太网驱动程序句柄
* @param[in] cmd: IO控制命令
* @param[in, out] data：“set”命令的数据地址或与“get”命令一起使用时存储数据的地址
*
* @return
*       -ESP_OK:成功处理io命令
*       -ESP_ERR_INVALID_ARG:进程io命令因某些无效参数而失败
*       -ESP_FAIL:进程io命令失败，因为发生了其他错误
*
* 支持以下IO控制命令：
* @li @c ETH_CMD_SMAC_ADDR设置以太网接口MAC地址@c数据参数是指向预期大小为6字节的MAC地址缓冲区的指针。
* @li @c ETH_CMD_GMAC_ADDR获取以太网接口MAC地址@c数据参数是指向要复制MAC地址的缓冲区的指针。缓冲区大小必须至少为6字节。
* @li @c ETH_CMD_S_PHY_ADDR将PHY地址设置在<0-31>的范围内@c数据参数是指向uint32_t数据类型内存的指针，从该内存读取配置选项。
* @li @c ETH_CMD_G_PHY_ADDR获取PHY地址@c数据参数是指向要存储PHY地址的uint32_t数据类型的内存的指针。
* @li @c ETH_CMD_G_SPEED获取当前以太网链路速度@c数据参数是指向eth_speed_t数据类型的内存的指针，该数据类型将存储速度。
* @li @c ETH_CMD_S_PROMISCUUS设置/重置以太网接口混杂模式@c数据参数是指向bool数据类型的内存的指针，从该内存中读取配置选项。
* @li @c ETH_CMD_S_FLOW_CTRL设置/重置以太网接口流量控制@c数据参数是指向bool数据类型的内存的指针，从该内存中读取配置选项。
* @li @c ETH_CMD_G_DUPLEX_MODE获取当前以太网链路双工模式@c数据参数是指向要存储双工模式的eth_duplex-t数据类型的内存的指针。
* @li @c ETH_CMD_S_PHY_LOOPBACK将PHY设置/重置为环回模式@c数据参数是指向bool数据类型的内存的指针，从该内存中读取配置选项。
*
*/
esp_err_t esp_eth_ioctl(esp_eth_handle_t hdl, esp_eth_io_cmd_t cmd, void *data);

/**
* @brief 增加以太网驱动程序参考
* @note 以太网驱动程序句柄可以通过os计时器、netif等获得。当线程A使用以太网但线程B卸载驱动程序时，这是危险的。使用引用计数器可以防止这种风险，但应注意，当您获得以太网驱动程序时，必须调用此API，以便在使用期间不会卸载驱动程序。
*
*
* @param[in] hdl: 以太网驱动程序句柄
* @return
*       -ESP_OK：成功增加引用
*       -ESP_ERR_INVALID_ARG:由于某些无效参数，增加引用失败
*/
esp_err_t esp_eth_increase_reference(esp_eth_handle_t hdl);

/**
* @brief 减少以太网驱动程序参考
*
* @param[in] hdl: 以太网驱动程序句柄
* @return
*       -ESP_OK：成功增加引用
*       -ESP_ERR_INVALID_ARG:由于某些无效参数，增加引用失败
*/
esp_err_t esp_eth_decrease_reference(esp_eth_handle_t hdl);

#ifdef __cplusplus
}
#endif

