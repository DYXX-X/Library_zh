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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief DM9051中的寄存器
 *
 */
#define DM9051_NCR (0x00)     // 网络控制寄存器
#define DM9051_NSR (0x01)     // 网络状态寄存器
#define DM9051_TCR (0x02)     // Tx控制寄存器
#define DM9051_TSR1 (0x03)    // Tx状态寄存器I
#define DM9051_TSR2 (0x04)    // Tx状态寄存器II
#define DM9051_RCR (0x05)     // Rx控制寄存器
#define DM9051_RSR (0x06)     // Rx状态寄存器
#define DM9051_ROCR (0x07)    // 接收溢出计数器寄存器
#define DM9051_BPTR (0x08)    // 背压阈值寄存器
#define DM9051_FCTR (0x09)    // 流量控制阈值寄存器
#define DM9051_FCR (0x0A)     // Rx/Tx流量控制寄存器
#define DM9051_EPCR (0x0B)    // EEPROM和PHY控制寄存器
#define DM9051_EPAR (0x0C)    // EEPROM和PHY地址寄存器
#define DM9051_EPDRL (0x0D)   // EEPROM和PHY数据寄存器低
#define DM9051_EPDRH (0x0E)   // EEPROM和PHY数据寄存器高
#define DM9051_WCR (0x0F)     // 唤醒控制寄存器
#define DM9051_PAR (0x10)     // 物理地址寄存器
#define DM9051_MAR (0x16)     // 多播地址哈希表寄存器
#define DM9051_GPCR (0x1E)    // 通用控制寄存器
#define DM9051_GPR (0x1F)     // 通用寄存器
#define DM9051_TRPAL (0x22)   // Tx存储器读取指针地址低字节
#define DM9051_TRPAH (0x23)   // Tx存储器读取指针地址高字节
#define DM9051_RWPAL (0x24)   // Rx内存读取指针地址低字节
#define DM9051_RWPAH (0x25)   // Rx内存读取指针地址高字节
#define DM9051_VIDL (0x28)    // 供应商ID低字节
#define DM9051_VIDH (0x29)    // 供应商ID高字节
#define DM9051_PIDL (0x2A)    // 产品ID低字节
#define DM9051_PIDH (0x2B)    // 产品ID高字节
#define DM9051_CHIPR (0x2C)   // CHIP修订
#define DM9051_TCR2 (0x2D)    // 发送控制寄存器2
#define DM9051_ATCR (0x30)    // 自动发送控制寄存器
#define DM9051_TCSCR (0x31)   // 发送校验和控制寄存器
#define DM9051_RCSCSR (0x32)  // 接收校验和控制状态寄存器
#define DM9051_SBCR (0x38)    // SPI总线控制寄存器
#define DM9051_INTCR (0x39)   // INT引脚控制寄存器
#define DM9051_PPCSR (0x3D)   // 暂停数据包控制状态寄存器
#define DM9051_EEE_IN (0x3E)  // IEEE 802.3az输入计数器寄存器
#define DM9051_EEE_OUT (0x3F) // IEEE 802.3az保留计数器寄存器
#define DM9051_ALNCR (0x4A)   // SPI字节对齐错误计数器寄存器
#define DM9051_RLENCR (0x52)  // Rx分组长度控制寄存器
#define DM9051_BCASTCR (0x53) // RX广播控制寄存器
#define DM9051_INTCKCR (0x54) // INT引脚时钟输出控制寄存器
#define DM9051_MPTRCR (0x55)  // 内存指针控制寄存器
#define DM9051_MLEDCR (0x57)  // 更多LED控制寄存器
#define DM9051_MEMSCR (0x59)  // 内存控制寄存器
#define DM9051_TMEMR (0x5A)   // 传输内存大小寄存器
#define DM9051_MBSR (0x5D)    // 内存BIST状态寄存器
#define DM9051_MRCMDX (0x70)  // 无地址增量寄存器的内存数据预取读取命令
#define DM9051_MRCMDX1 (0x71) // 无预取和无地址增量寄存器的内存读取命令
#define DM9051_MRCMD (0x72)   // 带有地址增量寄存器的存储器数据读取命令
#define DM9051_SDR_DLY (0x73) // SPI数据读取延迟计数器寄存器
#define DM9051_MRRL (0x74)    // 内存数据读取地址寄存器低字节
#define DM9051_MRRH (0x75)    // 存储器数据读取地址寄存器高字节
#define DM9051_MWCMDX (0x76)  // 无地址增量寄存器的存储器数据写入命令
#define DM9051_MWCMD (0x78)   // 带有地址增量寄存器的存储器数据写入命令
#define DM9051_MWRL (0x7A)    // 存储器数据写入地址寄存器低字节
#define DM9051_MWRH (0x7B)    // 存储器数据写入地址寄存器高字节
#define DM9051_TXPLL (0x7C)   // TX数据包长度低字节寄存器
#define DM9051_TXPLH (0x7D)   // TX数据包长度高字节寄存器
#define DM9051_ISR (0x7E)     // 中断状态寄存器
#define DM9051_IMR (0x7F)     // 中断掩码寄存器

/**
 * @brief DM9051特定寄存器的状态和标志
 *
 */
#define DM9051_SPI_RD (0) // 突发读取命令
#define DM9051_SPI_WR (1) // 突发写入命令

#define NCR_WAKEEN (1 << 6) // 启用唤醒功能
#define NCR_FDX (1 << 3)    // 内部PHY的双工模式
#define NCR_RST (1 << 0)    // 10us后软件重置和自动清除

#define NSR_SPEED (1 << 7)  // 内部PHY速度
#define NSR_LINKST (1 << 6) // 内部PHY的链路状态
#define NSR_WAKEST (1 << 5) // 唤醒事件状态
#define NSR_TX2END (1 << 3) // TX数据包索引II完成状态
#define NSR_TX1END (1 << 2) // TX数据包索引I完成状态
#define NSR_RXOV (1 << 1)   // RX内存溢出状态
#define NSR_RXRDY (1 << 0)  // RX数据包就绪

#define TCR_TXREQ (1 << 0) // TX请求。完全发送后自动清除

#define RCR_WTDIS (1 << 6)    // 看门狗定时器禁用
#define RCR_DIS_LONG (1 << 5) // 丢弃长数据包
#define RCR_DIS_CRC (1 << 4)  // 丢弃CRC错误数据包
#define RCR_ALL (1 << 3)      // 接收所有多播
#define RCR_RUNT (1 << 2)     // 接收Runt数据包
#define RCR_PRMSC (1 << 1)    // 混杂模式
#define RCR_RXEN (1 << 0)     // RX启用

#define RSR_RF (1 << 7)   // 横档框架
#define RSR_MF (1 << 6)   // 多播帧
#define RSR_LCS (1 << 5)  // 看到的晚碰撞
#define RSR_RWTO (1 << 4) // 接收看门狗超时
#define RSR_PLE (1 << 3)  // 物理层错误
#define RSR_AE (1 << 2)   //  对齐错误
#define RSR_CE (1 << 1)   // CRC错误
#define RSR_FOE (1 << 0)  // RX内存溢出错误

#define FCR_FLOW_ENABLE (0x39) // 启用流量控制

#define EPCR_REEP (1 << 5)  // 重新加载EEPROM
#define EPCR_WEP (1 << 4)   // 写入EEPROM启用
#define EPCR_EPOS (1 << 3)  // EEPROM或PHY操作选择
#define EPCR_ERPRR (1 << 2) // EEPROM读取或PHY寄存器读取命令
#define EPCR_ERPRW (1 << 1) // EEPROM写入或PHY寄存器写入命令
#define EPCR_ERRE (1 << 0)  // EEPROM访问状态或PHY访问状态

#define TCR2_RLCP (1 << 6) // 重试延迟冲突数据包

#define ATCR_AUTO_TX (1 << 7) // 自动传输控制

#define TCSCR_UDPCSE (1 << 2) // UDP校验和生成
#define TCSCR_TCPCSE (1 << 1) // TCP校验和生成
#define TCSCR_IPCSE (1 << 0)  // IPv4校验和生成

#define MPTRCR_RST_TX (1 << 1) // 重置TX内存指针
#define MPTRCR_RST_RX (1 << 0) // 重置RX内存指针

#define ISR_LNKCHGS (1 << 5) // 链接状态更改
#define ISR_ROO (1 << 3)     // 接收溢出计数器溢出
#define ISR_ROS (1 << 2)     // 接收溢出
#define ISR_PT (1 << 1)      // 数据包已发送
#define ISR_PR (1 << 0)      // 数据包已接收
#define ISR_CLR_STATUS (ISR_LNKCHGS | ISR_ROO | ISR_ROS | ISR_PT | ISR_PR)

#define IMR_PAR (1 << 7)     // 指针自动返回模式
#define IMR_LNKCHGI (1 << 5) // 启用链路状态更改中断
#define IMR_ROOI (1 << 3)    // 启用接收溢出计数器溢出中断
#define IMR_ROI (1 << 2)     // 启用接收溢出中断
#define IMR_PTI (1 << 1)     // 启用数据包传输中断
#define IMR_PRI (1 << 0)     // 启用数据包接收中断
#define IMR_ALL (IMR_PAR | IMR_LNKCHGI | IMR_ROOI | IMR_ROI | IMR_PTI | IMR_PRI)

#ifdef __cplusplus
}
#endif

