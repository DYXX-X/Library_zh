// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

/**
 * @brief 以太网帧CRC长度
 *
 */
#define ETH_CRC_LEN (4)

/**
* @brief 以太网接口
*
*/
typedef enum {
    EMAC_DATA_INTERFACE_RMII,    /*!< 减少了与媒体无关的界面*/
    EMAC_DATA_INTERFACE_MII,     /*!< 媒体独立界面*/
} eth_data_interface_t;

/**
* @brief 以太网链路状态
*
*/
typedef enum {
    ETH_LINK_UP,  /*!< 以太网链路已打开*/
    ETH_LINK_DOWN /*!< 以太网链路已断开*/
} eth_link_t;

/**
* @brief 以太网速度
*
*/
typedef enum {
    ETH_SPEED_10M,  /*!< 以太网速度为10Mbps*/
    ETH_SPEED_100M, /*!< 以太网速度为100Mbps*/
    ETH_SPEED_MAX   /*!< 最大速度模式（用于检查）*/
} eth_speed_t;

/**
* @brief 以太网双工模式
*
*/
typedef enum {
    ETH_DUPLEX_HALF,    /*!< 以太网为半双工*/
    ETH_DUPLEX_FULL,    /*!< 以太网为全双工*/
} eth_duplex_t;

/**
* @brief 以太网校验和
*/
typedef enum {
    ETH_CHECKSUM_SW, /*!< 通过软件计算以太网校验和*/
    ETH_CHECKSUM_HW  /*!< 通过硬件计算以太网校验和*/
} eth_checksum_t;

