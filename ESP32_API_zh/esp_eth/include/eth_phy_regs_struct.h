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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************基本PHY寄存器*******************/

/**
 * @brief 基本模式控制寄存器
 *
 */
typedef union {
    struct {
        uint32_t reserved : 7;          /*!< 保留*/
        uint32_t collision_test : 1;    /*!< 碰撞试验*/
        uint32_t duplex_mode : 1;       /*!< 双工模式：全双工（1）和半双工（0）*/
        uint32_t restart_auto_nego : 1; /*!< 重新启动自动协商*/
        uint32_t isolate : 1;           /*!< 将PHY与MII隔离，SMI接口除外*/
        uint32_t power_down : 1;        /*!< 关闭PHY（SMI接口除外）*/
        uint32_t en_auto_nego : 1;      /*!< 启用自动协商*/
        uint32_t speed_select : 1;      /*!< 选择速度：100Mbps（1）和10Mbps（0）*/
        uint32_t en_loopback : 1;       /*!< 允许将传输数据路由到接收路径*/
        uint32_t reset : 1;             /*!< 重置PHY寄存器。这个比特是自动清除的。*/
    };
    uint32_t val;
} bmcr_reg_t;
#define ETH_PHY_BMCR_REG_ADDR (0x00)

/**
 * @brief BMSR（基本模式状态寄存器）
 *
 */
typedef union {
    struct {
        uint32_t ext_capability : 1;       /*!< 扩展寄存器功能*/
        uint32_t jabber_detect : 1;        /*!< 检测到Jabber状况*/
        uint32_t link_status : 1;          /*!< 链接状态*/
        uint32_t auto_nego_ability : 1;    /*!< 自动协商能力*/
        uint32_t remote_fault : 1;         /*!< 检测到远程故障*/
        uint32_t auto_nego_complete : 1;   /*!< 自动协商已完成*/
        uint32_t mf_preamble_suppress : 1; /*!< 管理帧的前导码抑制能力*/
        uint32_t reserved : 1;             /*!< 保留*/
        uint32_t ext_status : 1;           /*!< 扩展状态*/
        uint32_t base100_t2_hdx : 1;       /*!< 100Base-T2半双工功能*/
        uint32_t base100_t2_fdx : 1;       /*!< 100Base-T2全双工功能*/
        uint32_t base10_t_hdx : 1;         /*!< 10Base-T半双工能力*/
        uint32_t base10_t_fdx : 1;         /*!< 10Base-T全双工功能*/
        uint32_t base100_tx_hdx : 1;       /*!< 100Base Tx半双工功能*/
        uint32_t base100_tx_fdx : 1;       /*!< 100Base Tx全双工功能*/
        uint32_t based100_t4 : 1;          /*!< 100Base-T4能力*/
    };
    uint32_t val;
} bmsr_reg_t;
#define ETH_PHY_BMSR_REG_ADDR (0x01)

/**
 * @brief PHYIDR1（PHY标识符寄存器1）
 *
 */
typedef union {
    struct {
        uint32_t oui_msb : 16; /*!< 组织唯一标识符（OUI）最高有效位*/
    };
    uint32_t val;
} phyidr1_reg_t;
#define ETH_PHY_IDR1_REG_ADDR (0x02)

/**
 * @brief PHYIDR2（PHY标识符寄存器2）
 *
 */
typedef union {
    struct {
        uint32_t model_revision : 4; /*!< 型号修订号*/
        uint32_t vendor_model : 6;   /*!< 供应商型号*/
        uint32_t oui_lsb : 6;        /*!< 组织唯一标识符（OUI）最低有效位*/
    };
    uint32_t val;
} phyidr2_reg_t;
#define ETH_PHY_IDR2_REG_ADDR (0x03)

/**
 * @brief 自动协商广告登记簿
 *
 */
typedef union {
    struct {
        uint32_t protocol_select : 5;  /*!< 此PHY支持的二进制编码选择器*/
        uint32_t base10_t : 1;         /*!< 10Base-T支持*/
        uint32_t base10_t_fd : 1;      /*!< 10Base-T全双工支持*/
        uint32_t base100_tx : 1;       /*!< 100Base TX支持*/
        uint32_t base100_tx_fd : 1;    /*!< 100Base TX全双工支持*/
        uint32_t base100_t4 : 1;       /*!< 100Base-T4支持*/
        uint32_t symmetric_pause : 1;  /*!< 全双工链路的对称暂停支持*/
        uint32_t asymmetric_pause : 1; /*!< 全双工链路的非对称暂停支持*/
        uint32_t reserved1 : 1;        /*!< 保留*/
        uint32_t remote_fault : 1;     /*!< 宣传远程故障检测功能*/
        uint32_t acknowledge : 1;      /*!< 链路伙伴能力数据接收已确认*/
        uint32_t next_page : 1;        /*!< 下一页指示，如果设置，则需要下一页传输*/
    };
    uint32_t val;
} anar_reg_t;
#define ETH_PHY_ANAR_REG_ADDR (0x04)

/**
 * @brief ANLPAR（自动协商链路伙伴能力寄存器）
 *
 */
typedef union {
    struct {
        uint32_t protocol_select : 5;  /*!< 链接伙伴的二进制编码节点选择器*/
        uint32_t base10_t : 1;         /*!< 10Base-T支持*/
        uint32_t base10_t_fd : 1;      /*!< 10Base-T全双工支持*/
        uint32_t base100_tx : 1;       /*!< 100Base TX支持*/
        uint32_t base100_tx_fd : 1;    /*!< 100Base TX全双工支持*/
        uint32_t base100_t4 : 1;       /*!< 100Base-T4支持*/
        uint32_t symmetric_pause : 1;  /*!< Link Partner支持的对称暂停*/
        uint32_t asymmetric_pause : 1; /*!< 链接合作伙伴支持的非对称暂停*/
        uint32_t reserved : 1;         /*!< 保留*/
        uint32_t remote_fault : 1;     /*!< 链路伙伴指示远程故障*/
        uint32_t acknowledge : 1;      /*!< 从链接伙伴确认*/
        uint32_t next_page : 1;        /*!< 下一页指示*/
    };
    uint32_t val;
} anlpar_reg_t;
#define ETH_PHY_ANLPAR_REG_ADDR (0x05)

/**
 * @brief 自动协商扩展寄存器
 *
 */
typedef union {
    struct {
        uint32_t link_partner_auto_nego_able : 1; /*!< 链接伙伴自动协商能力*/
        uint32_t link_page_received : 1;          /*!< 链接代码字页已收到*/
        uint32_t next_page_able : 1;              /*!< 下一页功能*/
        uint32_t link_partner_next_page_able : 1; /*!< 链接合作伙伴下一页功能*/
        uint32_t parallel_detection_fault : 1;    /*!< 并联检测故障*/
        uint32_t reserved : 11;                   /*!< 保留*/
    };
    uint32_t val;
} aner_reg_t;
#define ETH_PHY_ANER_REG_ADDR (0x06)

#ifdef __cplusplus
}
#endif

