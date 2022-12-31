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

#include "esp_err.h"
#include "esp_event_base.h"
#include "hal/eth_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 最大以太网负载大小
 *
 */
#define ETH_MAX_PAYLOAD_LEN (1500)

/**
 * @brief 最小以太网负载大小
 *
 */
#define ETH_MIN_PAYLOAD_LEN (46)

/**
 * @brief 以太网帧头大小：Dest-addr（6字节）+Src-addr（6个字节）+长度/类型（2个字节）
 *
 */
#define ETH_HEADER_LEN (14)

/**
 * @brief 可选802.1q VLAN标签长度
 *
 */
#define ETH_VLAN_TAG_LEN (4)

/**
 * @brief 巨型帧有效载荷大小
 *
 */
#define ETH_JUMBO_FRAME_PAYLOAD_LEN (9000)

/**
 * @brief 最大帧大小（1522字节）
 *
 */
#define ETH_MAX_PACKET_SIZE (ETH_HEADER_LEN + ETH_VLAN_TAG_LEN + ETH_MAX_PAYLOAD_LEN + ETH_CRC_LEN)

/**
 * @brief 最小帧大小（64字节）
 *
 */
#define ETH_MIN_PACKET_SIZE (ETH_HEADER_LEN + ETH_MIN_PAYLOAD_LEN + ETH_CRC_LEN)

/**
* @brief 以太网驱动程序状态
*
*/
typedef enum {
    ETH_STATE_LLINIT, /*!< 低电平初始化完成*/
    ETH_STATE_DEINIT, /*!< Deinit完成*/
    ETH_STATE_LINK,   /*!< 链接状态已更改*/
    ETH_STATE_SPEED,  /*!< 速度已更新*/
    ETH_STATE_DUPLEX, /*!< 双面打印已更新*/
    ETH_STATE_PAUSE,  /*!< 暂停功能已更新*/
} esp_eth_state_t;

/**
* @brief ioctl API的命令列表
*
*/
typedef enum {
    ETH_CMD_G_MAC_ADDR,    /*!< 获取MAC地址*/
    ETH_CMD_S_MAC_ADDR,    /*!< 设置MAC地址*/
    ETH_CMD_G_PHY_ADDR,    /*!< 获取PHY地址*/
    ETH_CMD_S_PHY_ADDR,    /*!< 设置PHY地址*/
    ETH_CMD_G_SPEED,       /*!< 获取速度*/
    ETH_CMD_S_PROMISCUOUS, /*!< 设置混杂模式*/
    ETH_CMD_S_FLOW_CTRL,   /*!< 设置流量控制*/
    ETH_CMD_G_DUPLEX_MODE, /*!< 获取双工模式*/
    ETH_CMD_S_PHY_LOOPBACK,/*!< 设置PHY环回*/
} esp_eth_io_cmd_t;

/**
* @brief 以太网调解器
*
*/
typedef struct esp_eth_mediator_s esp_eth_mediator_t;

/**
* @brief 以太网调解器
*
*/
struct esp_eth_mediator_s {
    /**
    * @brief 读取PHY寄存器
    *
    * @param[in] eth: 以太网驱动程序中介器
    * @param[in] phy_addr: PHY芯片地址（0~31）
    * @param[in] phy_reg: PHY寄存器索引码
    * @param[out] reg_value: PHY寄存器值
    *
    * @return
    *       -ESP_OK：成功读取PHY寄存器
    *       -ESP_FAIL:读取PHY寄存器失败，因为发生了一些错误
    *
    */
    esp_err_t (*phy_reg_read)(esp_eth_mediator_t *eth, uint32_t phy_addr, uint32_t phy_reg, uint32_t *reg_value);

    /**
    * @brief 写入PHY寄存器
    *
    * @param[in] eth: 以太网驱动程序中介器
    * @param[in] phy_addr: PHY芯片地址（0~31）
    * @param[in] phy_reg: PHY寄存器索引码
    * @param[in] reg_value: PHY寄存器值
    *
    * @return
    *       -ESP_OK：成功写入PHY寄存器
    *       -ESP_FAIL:写入PHY寄存器失败，因为发生了一些错误
    */
    esp_err_t (*phy_reg_write)(esp_eth_mediator_t *eth, uint32_t phy_addr, uint32_t phy_reg, uint32_t reg_value);

    /**
    * @brief 将数据包传送到上层堆栈
    *
    * @param[in] eth: 以太网驱动程序中介器
    * @param[in] buffer: 分组缓冲器
    * @param[in] length: 数据包的长度
    *
    * @return
    *       -ESP_OK：将数据包成功传递到上层堆栈
    *       -ESP_FAIL:由于发生错误，传递数据包失败
    *
    */
    esp_err_t (*stack_input)(esp_eth_mediator_t *eth, uint8_t *buffer, uint32_t length);

    /**
    * @brief 以太网上的回调状态已更改
    *
    * @param[in] eth: 以太网驱动程序中介器
    * @param[in] state: 新国家
    * @param[in] args: 新状态的可选参数
    *
    * @return
    *       -ESP_OK：成功处理新状态
    *       -ESP_FAIL:处理新状态失败，因为发生了一些错误
    *
    */
    esp_err_t (*on_state_changed)(esp_eth_mediator_t *eth, esp_eth_state_t state, void *args);
};

/**
* @brief 以太网事件声明
*
*/
typedef enum {
    ETHERNET_EVENT_START,        /*!< 以太网驱动程序启动*/
    ETHERNET_EVENT_STOP,         /*!< 以太网驱动程序停止*/
    ETHERNET_EVENT_CONNECTED,    /*!< 以太网获得有效链接*/
    ETHERNET_EVENT_DISCONNECTED, /*!< 以太网丢失了有效链路*/
} eth_event_t;

/**
* @brief 以太网事件库声明
*
*/
ESP_EVENT_DECLARE_BASE(ETH_EVENT);

/**
* @brief 检测PHY地址
*
* @param[in] eth: 以太网驱动程序中介器
* @param[out] detected_addr: 检测后的有效地址
* @return
*       -ESP_OK：成功检测物理地址
*       -ESP_ERR_INVALID_ARG：参数无效
*       -ESP_ERR_NOT_FOUND：无法检测任何PHY设备
*       -ESP_FAIL:检测物理地址失败，因为发生了一些错误
*/
esp_err_t esp_eth_detect_phy_addr(esp_eth_mediator_t *eth, int *detected_addr);

#ifdef __cplusplus
}
#endif

