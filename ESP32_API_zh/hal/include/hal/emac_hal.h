/*
 * SPDX文件版权文本：2021-2022浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "hal/eth_types.h"
#include "soc/emac_dma_struct.h"
#include "soc/emac_mac_struct.h"
#include "soc/emac_ext_struct.h"

/**
* @brief 以太网DMA TX描述符
*
*/
typedef struct {
    volatile union {
        struct {
            uint32_t Deferred : 1;                /*!< MAC在传输之前延迟*/
            uint32_t UnderflowErr : 1;            /*!< DMA遇到空的传输缓冲区*/
            uint32_t ExcessiveDeferral : 1;       /*!< 超过24288位时间的过度延迟*/
            uint32_t CollisionCount : 4;          /*!< 传输前发生的冲突数*/
            uint32_t VLanFrame : 1;               /*!< 传输的帧是VLAN类型的帧*/
            uint32_t ExcessiveCollision : 1;      /*!< 连续16次碰撞后传输中止*/
            uint32_t LateCollision : 1;           /*!< 碰撞窗口后发生碰撞*/
            uint32_t NoCarrier : 1;               /*!< 未断言来自PHY的载波检测信号*/
            uint32_t LossCarrier : 1;             /*!< 传输过程中发生载波丢失*/
            uint32_t PayloadChecksumErr : 1;      /*!< TCP/UDP/ICMP数据报负载中的校验和错误*/
            uint32_t FrameFlushed : 1;            /*!< DMA或MTL刷新帧*/
            uint32_t JabberTimeout : 1;           /*!< MAC发射机出现刺针超时*/
            uint32_t ErrSummary : 1;              /*!< 错误摘要*/
            uint32_t IPHeadErr : 1;               /*!< IP标头错误*/
            uint32_t TxTimestampStatus : 1;       /*!< 为传输帧捕获的时间戳*/
            uint32_t VLANInsertControl : 2;       /*!< 传输前VLAN标记或取消标记*/
            uint32_t SecondAddressChained : 1;    /*!< 描述符中的第二个地址是下一个描述符地址*/
            uint32_t TransmitEndRing : 1;         /*!< 描述符列表已到达其最终描述符*/
            uint32_t ChecksumInsertControl : 2;   /*!< 控制校验和计算和插入*/
            uint32_t CRCReplacementControl : 1;   /*!< 控制CRC替换*/
            uint32_t TransmitTimestampEnable : 1; /*!< 启用IEEE1588硬件时间戳*/
            uint32_t DisablePad : 1;              /*!< 控制在帧短于64字节时添加填充*/
            uint32_t DisableCRC : 1;              /*!< 控制将CRC附加到帧末尾*/
            uint32_t FirstSegment : 1;            /*!< 缓冲区包含帧的第一段*/
            uint32_t LastSegment : 1;             /*!< 缓冲区包含帧的最后一段*/
            uint32_t InterruptOnComplete : 1;     /*!< 帧传输后中断*/
            uint32_t Own : 1;                     /*!< 此描述符的所有者：DMA控制器或主机*/
        };
        uint32_t Value;
    } TDES0;
    union {
        struct {
            uint32_t TransmitBuffer1Size : 13; /*!< 第一个数据缓冲区字节大小*/
            uint32_t Reserved : 3;             /*!< 保留*/
            uint32_t TransmitBuffer2Size : 13; /*!< 第二个数据缓冲区字节大小*/
            uint32_t SAInsertControl : 3;      /*!< 控制MAC添加或替换源地址字段*/
        };
        uint32_t Value;
    } TDES1;
    uint32_t Buffer1Addr;         /*!< 缓冲区1地址指针*/
    uint32_t Buffer2NextDescAddr; /*!< 缓冲区2或下一个描述符地址指针*/
    uint32_t Reserved1;           /*!< 保留*/
    uint32_t Reserved2;           /*!< 保留*/
    uint32_t TimeStampLow;        /*!< 传输帧时间戳低*/
    uint32_t TimeStampHigh;       /*!< 传输帧时间戳高*/
} eth_dma_tx_descriptor_t;
#define EMAC_DMATXDESC_CHECKSUM_BYPASS 0            /*!< 校验和发动机旁通*/
#define EMAC_DMATXDESC_CHECKSUM_IPV4HEADER 1        /*!< IPv4标头校验和插入*/
#define EMAC_DMATXDESC_CHECKSUM_TCPUDPICMPSEGMENT 2 /*!< TCP/UDP/ICMP校验和插入仅在段上计算*/
#define EMAC_DMATXDESC_CHECKSUM_TCPUDPICMPFULL 3    /*!< TCP/UDP/ICMP校验和插入已完全计算*/

_Static_assert(sizeof(eth_dma_tx_descriptor_t) == 32, "eth_dma_tx_descriptor_t should occupy 32 bytes in memory");

/**
* @brief 以太网DMA RX描述符
*
*/
typedef struct {
    volatile union {
        struct {
            uint32_t ExtendStatusAvailable : 1;          /*!< RDES4中提供了扩展的statsu*/
            uint32_t CRCErr : 1;                         /*!< 帧上发生CRC错误*/
            uint32_t DribbleBitErr : 1;                  /*!< 帧包含8位的非整数倍*/
            uint32_t ReceiveErr : 1;                     /*!< 接收错误*/
            uint32_t ReceiveWatchdogTimeout : 1;         /*!< 接收看门狗超时*/
            uint32_t FrameType : 1;                      /*!< 以太网类型或IEEE802.3*/
            uint32_t LateCollision : 1;                  /*!< 接收过程中发生延迟碰撞*/
            uint32_t TSAvailIPChecksumErrGiantFrame : 1; /*!< 时间戳可用或IP校验和错误或巨型帧*/
            uint32_t LastDescriptor : 1;                 /*!< 帧的最后一个缓冲区*/
            uint32_t FirstDescriptor : 1;                /*!< 帧的第一个缓冲区*/
            uint32_t VLANTag : 1;                        /*!< VLAN标签：收到的帧是VLAN帧*/
            uint32_t OverflowErr : 1;                    /*!< 由于缓冲区溢出，帧已损坏*/
            uint32_t LengthErr : 1;                      /*!< 帧大小与长度字段不匹配*/
            uint32_t SourceAddrFilterFail : 1;           /*!< 帧的SA字段未通过SA筛选器*/
            uint32_t DescriptorErr : 1;                  /*!< 帧被截断，DMA没有下一个描述符*/
            uint32_t ErrSummary : 1;                     /*!< 错误摘要，RDES中所有错误的OR*/
            uint32_t FrameLength : 14;                   /*!< 接收帧的字节长度*/
            uint32_t DestinationAddrFilterFail : 1;      /*!< MAC中DA筛选器中的帧失败*/
            uint32_t Own : 1;                            /*!< 此描述符的所有者：DMA控制器或主机*/
        };
        uint32_t Value;
    } RDES0;
    union {
        struct {
            uint32_t ReceiveBuffer1Size : 13;        /*!< 第一个数据缓冲区大小（字节）*/
            uint32_t Reserved1 : 1;                  /*!< 保留*/
            uint32_t SecondAddressChained : 1;       /*!< 第二个地址是下一个描述符地址*/
            uint32_t ReceiveEndOfRing : 1;           /*!< 描述符已到达其最终描述符*/
            uint32_t ReceiveBuffer2Size : 13;        /*!< 第二个数据缓冲区大小（字节）*/
            uint32_t Reserved : 2;                   /*!< 保留*/
            uint32_t DisableInterruptOnComplete : 1; /*!< 禁用对主机的中断断言*/
        };
        uint32_t Value;
    } RDES1;
    uint32_t Buffer1Addr;         /*!< 缓冲区1地址指针*/
    uint32_t Buffer2NextDescAddr; /*!< 缓冲区2或下一个描述符地址指针*/
    volatile union {
        struct {
            uint32_t IPPayloadType : 3;                 /*!< IP数据报中的有效负载类型*/
            uint32_t IPHeadErr : 1;                     /*!< IP标头错误*/
            uint32_t IPPayloadErr : 1;                  /*!< IP负载错误*/
            uint32_t IPChecksumBypass : 1;              /*!< 校验和卸载引擎被绕过*/
            uint32_t IPv4PacketReceived : 1;            /*!< 收到的数据包是IPv4数据包*/
            uint32_t IPv6PacketReceived : 1;            /*!< 接收的数据包是IPv6数据包*/
            uint32_t MessageType : 4;                   /*!< PTP消息类型*/
            uint32_t PTPFrameType : 1;                  /*!< PTP消息通过以太网或IPv4/IPv6*/
            uint32_t PTPVersion : 1;                    /*!< PTP协议版本*/
            uint32_t TimestampDropped : 1;              /*!< 由于溢出而丢弃的时间戳*/
            uint32_t Reserved1 : 1;                     /*!< 保留*/
            uint32_t AVPacketReceived : 1;              /*!< 接收到AV数据包*/
            uint32_t AVTaggedPacketReceived : 1;        /*!< 收到AV标记的数据包*/
            uint32_t VLANTagPrioVal : 3;                /*!< 收到的数据包中VLAN标签的用户值*/
            uint32_t Reserved2 : 3;                     /*!< 保留*/
            uint32_t Layer3FilterMatch : 1;             /*!< 接收的帧与启用的第3层IP之一匹配*/
            uint32_t Layer4FilterMatch : 1;             /*!< 接收的帧与启用的第4层IP之一匹配*/
            uint32_t Layer3Layer4FilterNumberMatch : 2; /*!< 与接收帧匹配的第3层和第4层筛选器的数量*/
            uint32_t Reserved3 : 4;                     /*!< 保留*/
        };
        uint32_t Value;
    } ExtendedStatus;
    uint32_t Reserved;      /*!< 保留*/
    uint32_t TimeStampLow;  /*!< 接收帧时间戳低*/
    uint32_t TimeStampHigh; /*!< 接收帧时间戳高*/
} eth_dma_rx_descriptor_t;

_Static_assert(sizeof(eth_dma_rx_descriptor_t) == 32, "eth_dma_rx_descriptor_t should occupy 32 bytes in memory");

typedef struct {
    emac_mac_dev_t *mac_regs;
    emac_dma_dev_t *dma_regs;
    emac_ext_dev_t *ext_regs;
    uint8_t **rx_buf;
    uint8_t **tx_buf;
    void *descriptors;
    eth_dma_rx_descriptor_t *rx_desc;
    eth_dma_tx_descriptor_t *tx_desc;

} emac_hal_context_t;

void emac_hal_init(emac_hal_context_t *hal, void *descriptors,
                   uint8_t **rx_buf, uint8_t **tx_buf);

void emac_hal_iomux_init_mii(void);

void emac_hal_iomux_init_rmii(void);

void emac_hal_iomux_rmii_clk_input(void);

void emac_hal_iomux_rmii_clk_ouput(int num);

void emac_hal_iomux_init_tx_er(void);

void emac_hal_iomux_init_rx_er(void);

void emac_hal_reset_desc_chain(emac_hal_context_t *hal);

void emac_hal_reset(emac_hal_context_t *hal);

bool emac_hal_is_reset_done(emac_hal_context_t *hal);

void emac_hal_set_csr_clock_range(emac_hal_context_t *hal, int freq);

void emac_hal_init_mac_default(emac_hal_context_t *hal);

void emac_hal_init_dma_default(emac_hal_context_t *hal);

void emac_hal_set_speed(emac_hal_context_t *hal, uint32_t speed);

void emac_hal_set_duplex(emac_hal_context_t *hal, eth_duplex_t duplex);

void emac_hal_set_promiscuous(emac_hal_context_t *hal, bool enable);

/**
 * @brief 向对等端发送MAC-CTRL帧（EtherType=0x8808，opcode=0x0001，dest_addr=MAC-specific-CTRL-proto-01（01:80:c2:00:00:01））
 */
void emac_hal_send_pause_frame(emac_hal_context_t *hal, bool enable);

bool emac_hal_is_mii_busy(emac_hal_context_t *hal);

void emac_hal_set_phy_cmd(emac_hal_context_t *hal, uint32_t phy_addr, uint32_t phy_reg, bool write);

void emac_hal_set_phy_data(emac_hal_context_t *hal, uint32_t reg_value);

uint32_t emac_hal_get_phy_data(emac_hal_context_t *hal);

void emac_hal_set_address(emac_hal_context_t *hal, uint8_t *mac_addr);

/**
 * @brief 开始EMAC传输和接收
 *
 * @param hal EMAC HAL上下文信息结构
 */
void emac_hal_start(emac_hal_context_t *hal);

/**
 * @brief 停止EMAC传输和接收
 *
 * @param hal EMAC HAL上下文信息结构
 * @return
 *     -ESP_OK：成功
  *    -ESP_ERR_INVALID_STATE：前一帧传输/接收未完成。当出现此错误时，请等待并再次到达EMAC站点。
 */
esp_err_t emac_hal_stop(emac_hal_context_t *hal);

uint32_t emac_hal_get_tx_desc_owner(emac_hal_context_t *hal);

uint32_t emac_hal_transmit_frame(emac_hal_context_t *hal, uint8_t *buf, uint32_t length);

uint32_t emac_hal_receive_frame(emac_hal_context_t *hal, uint8_t *buf, uint32_t size, uint32_t *frames_remain, uint32_t *free_desc);

void emac_hal_enable_flow_ctrl(emac_hal_context_t *hal, bool enable);

uint32_t emac_hal_get_intr_enable_status(emac_hal_context_t *hal);

uint32_t emac_hal_get_intr_status(emac_hal_context_t *hal);

void emac_hal_clear_corresponding_intr(emac_hal_context_t *hal, uint32_t bits);

void emac_hal_clear_all_intr(emac_hal_context_t *hal);

#ifdef __cplusplus
}
#endif

