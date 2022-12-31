// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#define W5500_ADDR_OFFSET (16) // 地址长度
#define W5500_BSB_OFFSET  (3)  // 块选择位偏移
#define W5500_RWB_OFFSET  (2)  // 读写位偏移

#define W5500_BSB_COM_REG        (0x00)    // 通用寄存器
#define W5500_BSB_SOCK_REG(s)    ((s)*4+1) // 套接字寄存器
#define W5500_BSB_SOCK_TX_BUF(s) ((s)*4+2) // 套接字TX缓冲区
#define W5500_BSB_SOCK_RX_BUF(s) ((s)*4+3) // 套接字RX缓冲区

#define W5500_ACCESS_MODE_READ  (0) // 读取模式
#define W5500_ACCESS_MODE_WRITE (1) // 写入模式

#define W5500_SPI_OP_MODE_VDM   (0x00) // 可变数据长度模式（SPI帧由CS线控制）
#define W5500_SPI_OP_MODE_FDM_1 (0x01) // 固定数据长度模式，1字节长度
#define W5500_SPI_OP_MODE_FDM_2 (0x02) // 固定数据长度模式，2字节长度
#define W5500_SPI_OP_MODE_FDM_4 (0x03) // 固定数据长度模式，4字节长度

#define W5500_MAKE_MAP(offset, bsb) ((offset) << W5500_ADDR_OFFSET | (bsb) << W5500_BSB_OFFSET)

#define W5500_REG_MR        W5500_MAKE_MAP(0x0000, W5500_BSB_COM_REG) // 模式
#define W5500_REG_MAC       W5500_MAKE_MAP(0x0009, W5500_BSB_COM_REG) // MAC地址
#define W5500_REG_INTLEVEL  W5500_MAKE_MAP(0x0013, W5500_BSB_COM_REG) // 中断级别超时
#define W5500_REG_IR        W5500_MAKE_MAP(0x0015, W5500_BSB_COM_REG) // 打断
#define W5500_REG_IMR       W5500_MAKE_MAP(0x0016, W5500_BSB_COM_REG) // 中断掩码
#define W5500_REG_SIR       W5500_MAKE_MAP(0x0017, W5500_BSB_COM_REG) // 套接字中断
#define W5500_REG_SIMR      W5500_MAKE_MAP(0x0018, W5500_BSB_COM_REG) // 套接字中断掩码
#define W5500_REG_RTR       W5500_MAKE_MAP(0x0019, W5500_BSB_COM_REG) // 重试时间
#define W5500_REG_RCR       W5500_MAKE_MAP(0x001B, W5500_BSB_COM_REG) // 重试计数
#define W5500_REG_PHYCFGR   W5500_MAKE_MAP(0x002E, W5500_BSB_COM_REG) // PHY配置
#define W5500_REG_VERSIONR  W5500_MAKE_MAP(0x0039, W5500_BSB_COM_REG) // 芯片版本

#define W5500_REG_SOCK_MR(s)         W5500_MAKE_MAP(0x0000, W5500_BSB_SOCK_REG(s)) // 套接字模式
#define W5500_REG_SOCK_CR(s)         W5500_MAKE_MAP(0x0001, W5500_BSB_SOCK_REG(s)) // Socket命令
#define W5500_REG_SOCK_IR(s)         W5500_MAKE_MAP(0x0002, W5500_BSB_SOCK_REG(s)) // 套接字中断
#define W5500_REG_SOCK_SR(s)         W5500_MAKE_MAP(0x0004, W5500_BSB_SOCK_REG(s)) // 套接字状态
#define W5500_REG_SOCK_RXBUF_SIZE(s) W5500_MAKE_MAP(0x001E, W5500_BSB_SOCK_REG(s)) // 套接字接收缓冲区大小
#define W5500_REG_SOCK_TXBUF_SIZE(s) W5500_MAKE_MAP(0x001F, W5500_BSB_SOCK_REG(s)) // 套接字传输缓冲区大小
#define W5500_REG_SOCK_TX_FSR(s)     W5500_MAKE_MAP(0x0020, W5500_BSB_SOCK_REG(s)) // 插座TX自由尺寸
#define W5500_REG_SOCK_TX_RD(s)      W5500_MAKE_MAP(0x0022, W5500_BSB_SOCK_REG(s)) // 套接字TX读取指针
#define W5500_REG_SOCK_TX_WR(s)      W5500_MAKE_MAP(0x0024, W5500_BSB_SOCK_REG(s)) // 套接字TX写入指针
#define W5500_REG_SOCK_RX_RSR(s)     W5500_MAKE_MAP(0x0026, W5500_BSB_SOCK_REG(s)) // 插座RX接收尺寸
#define W5500_REG_SOCK_RX_RD(s)      W5500_MAKE_MAP(0x0028, W5500_BSB_SOCK_REG(s)) // 套接字RX读取指针
#define W5500_REG_SOCK_RX_WR(s)      W5500_MAKE_MAP(0x002A, W5500_BSB_SOCK_REG(s)) // 套接字RX写入指针
#define W5500_REG_SOCK_IMR(s)        W5500_MAKE_MAP(0x002C, W5500_BSB_SOCK_REG(s)) // 套接字中断掩码

#define W5500_MEM_SOCK_TX(s,addr) W5500_MAKE_MAP(addr, W5500_BSB_SOCK_TX_BUF(s)) // 套接字TX缓冲区地址
#define W5500_MEM_SOCK_RX(s,addr) W5500_MAKE_MAP(addr, W5500_BSB_SOCK_RX_BUF(s)) // 套接字RX缓冲区地址

#define W5500_MR_RST (1<<7) // 软件重置
#define W5500_MR_PB  (1<<4) // Ping块（阻止对Ping请求的响应）

#define W5500_SIMR_SOCK0 (1<<0) // 套接字0中断

#define W5500_SMR_MAC_RAW    (1<<2) // MAC RAW模式
#define W5500_SMR_MAC_FILTER (1<<7) // MAC过滤器

#define W5500_SCR_OPEN  (0x01) // 打开命令
#define W5500_SCR_CLOSE (0x10) // “关闭”命令
#define W5500_SCR_SEND  (0x20) // 发送命令
#define W5500_SCR_RECV  (0x40) // Recv命令

#define W5500_SIR_RECV (1<<2)  // 接收完成
#define W5500_SIR_SEND (1<<4)  // 发送完成

