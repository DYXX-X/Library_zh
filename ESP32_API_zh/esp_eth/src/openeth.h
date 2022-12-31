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
#include <stddef.h>
#include <assert.h>
#include "sdkconfig.h"
#include "soc/soc.h"

#ifdef __cplusplus
extern "C" {
#endif

// 以下是OpenCores以太网MAC的寄存器定义。
// 请参见esp_eth_mac_openath中的注释。c了解有关此驱动程序的详细信息。

// DMA缓冲区配置
#define DMA_BUF_SIZE    1600
#define RX_BUF_COUNT    CONFIG_ETH_OPENETH_DMA_RX_BUFFER_NUM
#define TX_BUF_COUNT    CONFIG_ETH_OPENETH_DMA_TX_BUFFER_NUM

// 该驱动器使用ESP32芯片的内部EMAC的中断源编号，
// 并且使用相同的寄存器地址基。当然，这只适用于QEMU，其中
// OpenCores MAC映射到相同的寄存器基和相同的中断
// 来源这个驱动程序进行了一次健全性检查，确认它没有在真正的ESP32上运行
// 芯片，使用EMAC日期寄存器。
#define OPENETH_INTR_SOURCE         ETS_ETH_MAC_INTR_SOURCE
#define OPENETH_BASE                DR_REG_EMAC_BASE

// OpenCores ethmac寄存器
#define OPENETH_MODER_REG           (OPENETH_BASE + 0x00)
#define OPENETH_MODER_DEFAULT       0xa000
// OPENETH_RST：重置MAC
#define OPENETH_RST   BIT(11)
// OPENETH_PRO：启用混杂模式
#define OPENETH_PRO   BIT(5)
// OPENETH_TXEN：启用传输
#define OPENETH_TXEN   BIT(1)
// OPENETH_RXEN：启用接收
#define OPENETH_RXEN   BIT(0)

#define OPENETH_INT_SOURCE_REG      (OPENETH_BASE + 0x04)
#define OPENETH_INT_MASK_REG        (OPENETH_BASE + 0x08)
// 这些位适用于INT_SOURCE和INT_MASK寄存器：
// OPENETH_INT_BUSY:由于缺少缓冲区，缓冲区被接收并丢弃
#define OPENETH_INT_BUSY   BIT(4)
// OPENETH_INT_RXB：收到帧
#define OPENETH_INT_RXB   BIT(2)
// OPENETH_INT_TXB：传输的帧
#define OPENETH_INT_TXB   BIT(0)

// IPGT、IPGR1、IPGR2寄存器未在QEMU中实现，因此此处不使用
#define OPENETH_PACKETLEN_REG       (OPENETH_BASE + 0x18)
// OPENETH_MINFL：最小帧长度
#define OPENETH_MINFL_S 16
#define OPENETH_MINFL_V 0xffff
#define OPENETH_MINFL_M (OPENETH_MINFL_V << OPENETH_MINFL_S)
// OPENETH_MAXFL：最大帧长度
#define OPENETH_MAXFL_S 0
#define OPENETH_MAXFL_V 0xffff
#define OPENETH_MAXFL_M (OPENETH_MAXFL_V << OPENETH_MAXFL_S)

// COLLCONF未在QEMU中实现
#define OPENETH_TX_BD_NUM_REG       (OPENETH_BASE + 0x20)
// CTRLMODER、MIIMODER未在QEMU中实现
#define OPENETH_MIICOMMAND_REG      (OPENETH_BASE + 0x2c)
// OPENETH_WCTRLDATA:写入控制数据
#define OPENETH_WCTRLDATA   BIT(2)
// OPENETH_RSTAT：读取状态
#define OPENETH_RSTAT       BIT(1)
// OPENETH_SCANSTAT:扫描状态
#define OPENETH_SCANSTAT    BIT(0)

#define OPENETH_MIIADDRESS_REG      (OPENETH_BASE + 0x30)
// OPENETH_RGAD：寄存器地址
#define OPENETH_RGAD_S 8
#define OPENETH_RGAD_V 0x1f
#define OPENETH_RGAD_M (OPENETH_RGAD_V << OPENETH_RGAD_S)
// OPENETH_FIAD:PHY地址
#define OPENETH_FIAD_S 0
#define OPENETH_FIAD_V 0x1f
#define OPENETH_FIAD_N (OPENETH_FIAD_V << OPENETH_FIAD_S)

#define OPENETH_MIITX_DATA_REG      (OPENETH_BASE + 0x34)
#define OPENETH_MIIRX_DATA_REG      (OPENETH_BASE + 0x38)
#define OPENETH_MII_DATA_MASK 0xffff

#define OPENETH_MIISTATUS_REG       (OPENETH_BASE + 0x3c)
// OPENETH_LINKFAIL:链接已关闭
#define OPENETH_LINKFAIL BIT(0)

// OPENETH_MAC_ADDR0_REG:MAC地址的字节2-5（LSB中的字节5）
#define OPENETH_MAC_ADDR0_REG       (OPENETH_BASE + 0x40)
// OPENETH_MAC_ADDR1_REG：MAC地址的字节0-1（LSB中的字节1）
#define OPENETH_MAC_ADDR1_REG       (OPENETH_BASE + 0x44)

#define OPENETH_HASH0_ADR_REG       (OPENETH_BASE + 0x48)
#define OPENETH_HASH1_ADR_REG       (OPENETH_BASE + 0x4c)

// DMA描述符的位置
#define OPENETH_DESC_BASE           (OPENETH_BASE + 0x400)
// （TX+RX）DMA描述符总数
#define OPENETH_DESC_CNT            128


// 描述TX和RX描述符的结构。
// 字段名称与OpenCores ethmac文档中的相同。
typedef struct {
    uint16_t cs: 1;     //!< 载波检测丢失（HW设置的标志）
    uint16_t df: 1;     //!< 延迟指示（HW设置的标志）
    uint16_t lc: 1;     //!< 发生延迟碰撞（HW设置的标志）
    uint16_t rl: 1;     //!< 由于重传限制（HW设置的标志），发送失败
    uint16_t rtry: 4;   //!< 发送帧之前的重试次数（由硬件设置）
    uint16_t ur: 1;     //!< 欠载状态（HW设置的标志）
    uint16_t rsv: 2;    //!< 保留
    uint16_t crc: 1;    //!< 在数据包末尾添加CRC
    uint16_t pad: 1;    //!< 在短数据包末尾添加填充
    uint16_t wr: 1;     //!< 绕过去。0：不是表中的最后一个描述符，1：最后一个描述符。
    uint16_t irq: 1;    //!< 传输此描述符后生成中断
    uint16_t rd: 1;     //!< 描述符就绪。0：软件拥有的描述符，1：硬件拥有的描述符。硬件已清除。

    uint16_t len;       //!< 要传输的字节数
    void* txpnt;        //!< 指向要传输的数据的指针
} openeth_tx_desc_t;

_Static_assert(sizeof(openeth_tx_desc_t) == 8, "incorrect size of openeth_tx_desc_t");

typedef struct {
    uint16_t lc: 1;     //!< 晚碰撞标志
    uint16_t crc: 1;    //!< RX CRC错误标志
    uint16_t sf: 1;     //!< 帧短于PACKETLEN寄存器中设置的帧
    uint16_t tl: 1;     //!< 帧长于PACKETLEN寄存器中的设置
    uint16_t dn: 1;     //!< 运球半字节（帧长度不能被8位整除）标志
    uint16_t is: 1;     //!< 无效的符号标志
    uint16_t or: 1;     //!< 超限标志
    uint16_t m: 1;      //!< 由于混杂模式而收到的帧
    uint16_t rsv: 5;    //!< 保留
    uint16_t wr: 1;     //!< 绕过去。0：不是表中的最后一个描述符，1：最后一个描述符。
    uint16_t irq: 1;    //!< 传输此描述符后生成中断
    uint16_t e: 1;      //!< 缓冲区为空。0：软件拥有的描述符，1：硬件拥有的描述符。

    uint16_t len;       //!< 接收的字节数（由硬件填写）
    void* rxpnt;        //!< 指向接收缓冲区的指针
} openeth_rx_desc_t;

_Static_assert(sizeof(openeth_rx_desc_t) == 8, "incorrect size of openeth_rx_desc_t");


static inline openeth_tx_desc_t* openeth_tx_desc(int idx)
{
    assert(idx < TX_BUF_COUNT);
    return &((openeth_tx_desc_t*)OPENETH_DESC_BASE)[idx];
}

static inline openeth_rx_desc_t* openeth_rx_desc(int idx)
{
    assert(idx < OPENETH_DESC_CNT - TX_BUF_COUNT);
    return &((openeth_rx_desc_t*)OPENETH_DESC_BASE)[idx + TX_BUF_COUNT];
}

static inline void openeth_enable(void)
{
    REG_SET_BIT(OPENETH_MODER_REG, OPENETH_TXEN | OPENETH_RXEN | OPENETH_PRO);
    REG_SET_BIT(OPENETH_INT_MASK_REG, OPENETH_INT_RXB);
}

static inline void openeth_disable(void)
{
    REG_CLR_BIT(OPENETH_INT_MASK_REG, OPENETH_INT_RXB);
    REG_CLR_BIT(OPENETH_MODER_REG, OPENETH_TXEN | OPENETH_RXEN | OPENETH_PRO);
}

static inline void openeth_reset(void)
{
    REG_SET_BIT(OPENETH_MODER_REG, OPENETH_RST);
    REG_CLR_BIT(OPENETH_MODER_REG, OPENETH_RST);
}

static inline void openeth_init_tx_desc(openeth_tx_desc_t* desc, void* buf)
{
    *desc = (openeth_tx_desc_t) {
        .rd = 0,
        .txpnt = buf
    };
}

static inline void openeth_init_rx_desc(openeth_rx_desc_t* desc, void* buf)
{
    *desc = (openeth_rx_desc_t) {
        .e = 1,
        .irq = 1,
        .rxpnt = buf
    };
}

static inline void openeth_set_tx_desc_cnt(int tx_desc_cnt)
{
    assert(tx_desc_cnt <= OPENETH_DESC_CNT);
    REG_WRITE(OPENETH_TX_BD_NUM_REG, tx_desc_cnt);
}

#ifdef __cplusplus
}
#endif

