// 版权所有（c）2021 Vladimir Chistyakov
//
// 特此免费向任何获得副本的人授予许可
// 本软件和相关文档文件（“软件”）
// 不受限制，包括但不限于
// 使用、复制、修改、合并、发布、分发、再许可和/或出售
// 软件的副本，并允许软件所属人员
// 按照以下条件提供：
//
// 上述版权声明和本许可声明应包含在
// 软件的所有副本或主要部分。
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once


typedef enum {
    KSZ8851_CCR                = 0x08, ///<芯片配置寄存器
    KSZ8851_MARL               = 0x10, ///<主机MAC地址寄存器低
    KSZ8851_MARM               = 0x12, ///<主机MAC地址寄存器中间
    KSZ8851_MARH               = 0x14, ///<主机MAC地址寄存器高
    KSZ8851_OBCR               = 0x20, ///<片上总线控制寄存器
    KSZ8851_EEPCR              = 0x22, ///<EEPROM控制寄存器
    KSZ8851_MBIR               = 0x24, ///<内存内置自检（BIST）信息寄存器
    KSZ8851_GRR                = 0x26, ///<全局重置寄存器
    KSZ8851_WFCR               = 0x2A, ///<唤醒帧控制寄存器
    KSZ8851_WF0CRC0            = 0x30, ///<唤醒帧0 CRC0寄存器（低16位）
    KSZ8851_WF0CRC1            = 0x32, ///<唤醒帧0 CRC1寄存器（高位16位）
    KSZ8851_WF0BM0             = 0x34, ///<唤醒帧0字节掩码0寄存器（0-15）
    KSZ8851_WF0BM1             = 0x36, ///<唤醒帧0字节掩码1寄存器（16-31）
    KSZ8851_WF0BM2             = 0x38, ///<唤醒帧0字节掩码2寄存器（32-47）
    KSZ8851_WF0BM3             = 0x3A, ///<唤醒帧0字节掩码3寄存器（48-63）
    KSZ8851_WF1CRC0            = 0x40, ///<唤醒帧1 CRC0寄存器（低16位）
    KSZ8851_WF1CRC1            = 0x42, ///<唤醒帧1 CRC1寄存器（高位16位）
    KSZ8851_WF1BM0             = 0x44, ///<唤醒帧1字节掩码0寄存器（0-15）
    KSZ8851_WF1BM1             = 0x46, ///<唤醒帧1字节掩码1寄存器（16-31）
    KSZ8851_WF1BM2             = 0x48, ///<唤醒帧1字节掩码2寄存器（32-47）
    KSZ8851_WF1BM3             = 0x4A, ///<唤醒帧1字节掩码3寄存器（48-63）
    KSZ8851_WF2CRC0            = 0x50, ///<唤醒帧2 CRC0寄存器（低16位）
    KSZ8851_WF2CRC1            = 0x52, ///<唤醒帧2 CRC1寄存器（高位16位）
    KSZ8851_WF2BM0             = 0x54, ///<唤醒帧2字节掩码0寄存器（0-15）
    KSZ8851_WF2BM1             = 0x56, ///<唤醒帧2字节掩码1寄存器（16-31）
    KSZ8851_WF2BM2             = 0x58, ///<唤醒帧2字节掩码2寄存器（32-47）
    KSZ8851_WF2BM3             = 0x5A, ///<唤醒帧2字节掩码3寄存器（48-63）
    KSZ8851_WF3CRC0            = 0x60, ///<唤醒帧3 CRC0寄存器（低16位）
    KSZ8851_WF3CRC1            = 0x62, ///<唤醒帧3 CRC1寄存器（高位16位）
    KSZ8851_WF3BM0             = 0x64, ///<唤醒帧3字节掩码0寄存器（0-15）
    KSZ8851_WF3BM1             = 0x66, ///<唤醒帧3字节掩码1寄存器（16-31）
    KSZ8851_WF3BM2             = 0x68, ///<唤醒帧3字节掩码2寄存器（32-47）
    KSZ8851_WF3BM3             = 0x6A, ///<唤醒帧3字节掩码3寄存器（48-63）
    KSZ8851_TXCR               = 0x70, ///<传输控制寄存器
    KSZ8851_TXSR               = 0x72, ///<传输状态寄存器
    KSZ8851_RXCR1              = 0x74, ///<接收控制寄存器1
    KSZ8851_RXCR2              = 0x76, ///<接收控制寄存器2
    KSZ8851_TXMIR              = 0x78, ///<TXQ内存信息寄存器
    KSZ8851_RXFHSR             = 0x7C, ///<接收帧标题状态寄存器
    KSZ8851_RXFHBCR            = 0x7E, ///<接收帧标题字节计数寄存器
    KSZ8851_TXQCR              = 0x80, ///<TXQ命令寄存器
    KSZ8851_RXQCR              = 0x82, ///<RXQ命令寄存器
    KSZ8851_TXFDPR             = 0x84, ///<TX帧数据指针寄存器
    KSZ8851_RXFDPR             = 0x86, ///<RX帧数据指针寄存器
    KSZ8851_RXDTTR             = 0x8C, ///<RX持续时间计时器阈值寄存器
    KSZ8851_RXDBCTR            = 0x8E, ///<RX数据字节计数阈值寄存器
    KSZ8851_IER                = 0x90, ///<中断启用寄存器
    KSZ8851_ISR                = 0x92, ///<中断状态寄存器
    KSZ8851_RXFCTR             = 0x9C, ///<RX帧计数和阈值寄存器
    KSZ8851_TXNTFSR            = 0x9E, ///<TX下一个总帧大小寄存器
    KSZ8851_MAHTR0             = 0xA0, ///<MAC地址哈希表寄存器0
    KSZ8851_MAHTR1             = 0xA2, ///<MAC地址哈希表寄存器1
    KSZ8851_MAHTR2             = 0xA4, ///<MAC地址哈希表寄存器2
    KSZ8851_MAHTR3             = 0xA6, ///<MAC地址哈希表寄存器3
    KSZ8851_FCLWR              = 0xB0, ///<流量控制低水印寄存器
    KSZ8851_FCHWR              = 0xB2, ///<流量控制高水印寄存器
    KSZ8851_FCOWR              = 0xB4, ///<流量控制溢出水印寄存器
    KSZ8851_CIDER              = 0xC0, ///<芯片ID和启用寄存器
    KSZ8851_CGCR               = 0xC6, ///<芯片全局控制寄存器
    KSZ8851_IACR               = 0xC8, ///<间接访问控制寄存器
    KSZ8851_IADLR              = 0xD0, ///<间接访问数据低寄存器
    KSZ8851_IADHR              = 0xD2, ///<间接访问数据高位寄存器
    KSZ8851_PMECR              = 0xD4, ///<电源管理事件控制寄存器
    KSZ8851_GSWUTR             = 0xD6, ///<进入睡眠和唤醒时间登记
    KSZ8851_PHYRR              = 0xD8, ///<PHY复位寄存器
    KSZ8851_P1MBCR             = 0xE4, ///<PHY 1 MII寄存器基本控制寄存器
    KSZ8851_P1MBSR             = 0xE6, ///<PHY 1 MII寄存器基本状态寄存器
    KSZ8851_PHY1ILR            = 0xE8, ///<PHY 1 PHY ID低寄存器
    KSZ8851_PHY1IHR            = 0xEA, ///<PHY 1 PHY ID高寄存器
    KSZ8851_P1ANAR             = 0xEC, ///<PHY 1自动协商广告寄存器
    KSZ8851_P1ANLPR            = 0xEE, ///<PHY 1自动协商链路伙伴能力寄存器
    KSZ8851_P1SCLMD            = 0xF4, ///<端口1 PHY特殊控制/状态，LinkMD
    KSZ8851_P1CR               = 0xF6, ///<端口1控制寄存器
    KSZ8851_P1SR               = 0xF8, ///<端口1状态寄存器
    KSZ8851_VALID_ADDRESS_MASK = 0xFE, ///<所有寄存器地址都在此掩码下
} ksz8851_registers_t;

typedef enum {
    CCR_EEPROM_PRESENCE    = 0x0200U, ///<RO EEPROM存在
    CCR_SPI_BUS_MODE       = 0x0100U, ///<RO SPI总线模式
    CCR_32PIN_CHIP_PACKAGE = 0x0001U, ///<RO 32引脚芯片封装

    OBCR_OUTPUT_PIN_DRIVE_STRENGTH    = 0x0040U, ///<RW输出引脚驱动强度：8mA（0）或16mA（1）
    OBCR_ONCHIP_BUS_CLOCK_SELECTION   = 0X0004U, ///<RW片上总线时钟选择：125MHz（0）
    OBCR_ONCHIP_BUS_CLOCK_DIVIDE_BY_1 = 0x0000U, ///<RW片上总线时钟分频器选择
    OBCR_ONCHIP_BUS_CLCOK_DIVIDE_BY_2 = 0x0001U, ///<Rw片上总线时钟分频器选择
    OBCR_ONCHIP_BUS_CLCOK_DIVIDE_BY_3 = 0x0002U, ///<RW片上总线时钟分频器选择

    EEPCR_EESRWA = 0x0020U, ///<RW EEPROM软件读取（0）或写入（1）访问
    EEPCR_EESA   = 0x0010U, ///<RW EEPROM软件访问
    EEPCR_EESB   = 0x0008U, ///<RO EEPROM数据接收
    EEPCR_EECB2  = 0x0004U, ///<RW EEPROM数据传输
    EEPCR_EECB1  = 0x0002U, ///<RW EEPROM串行时钟
    EEPCR_EECB0  = 0x0001U, ///<RW EEPROM芯片选择

    MBIR_TXMBF        = 0x1000U,                  ///<RO TX内存BIST测试完成
    MBIR_TXMBFA       = 0x0800U,                  ///<RO TX内存BIST测试失败
    MBIR_TXMBFC_SHIFT = 8U,                       ///<RO TX存储器BIST测试失败计数移位
    MBIR_TXMBFC_MASK  = 0x7 << MBIR_TXMBFC_SHIFT, ///<RO TX内存BIST测试失败计数掩码
    MBIR_RXMBF        = 0x0010U,                  ///<RO RX内存Bist完成
    MBIR_RXMBFA       = 0x0008U,                  ///<RO RX内存短路故障
    MBIR_RXMBFC       = 0x7U,                     ///<RO RX内存BIST测试失败计数

    GRR_QMU_MODULE_SOFT_RESET = 0x0002U, ///<RW QMU模块软重置
    GRR_GLOBAL_SOFT_RESET     = 0x0001U, ///<Rw全局软重置

    WFCR_MPRXE = 0x0080U, ///<RW Magic Packet RX启用
    WFCR_WF3E  = 0x0008U, ///<RW唤醒帧3启用
    WFCR_WF2E  = 0x0004U, ///<RW唤醒帧2启用
    WFCR_WF1E  = 0x0002U, ///<RW唤醒帧1启用
    WFCR_WF0E  = 0x0001U, ///<RW唤醒帧0启用

    TXCR_TCGICMP = 0x0100U, ///<ICMP的RW传输校验和生成
    TXCR_TCGTCP  = 0x0040U, ///<RW TCP传输校验和生成
    TXCR_TCGIP   = 0x0020U, ///<RW IP传输校验和生成
    TXCR_FTXQ    = 0x0010U, ///<RW刷新传输队列
    TXCR_TXFCE   = 0x0008U, ///<RW传输流控制启用
    TXCR_TXPE    = 0x0004U, ///<RW传输填充启用
    TXCR_TXCE    = 0x0002U, ///<RW传输CRC启用
    TXCR_TXE     = 0x0001U, ///<RW传输启用

    TXSR_TXLC       = 0x2000U, ///<RO传输延迟冲突
    TXSR_TXMC       = 0x1000U, ///<RO传输最大冲突
    TXSR_TXFID_MASK = 0x003FU, ///<RO传输帧ID掩码

    RXCR1_FRXQ     = 0x8000U, ///<RW刷新接收队列
    RXCR1_RXUDPFCC = 0x4000U, ///<RW接收UDP帧校验和检查启用
    RXCR1_RXTCPFCC = 0x2000U, ///<RW接收TCP帧校验和检查启用
    RXCR1_RXIPFCC  = 0x1000U, ///<RW接收IP帧校验和检查启用
    RXCR1_RXPAFMA  = 0x0800U, ///<RW接收物理地址过滤，启用MAC地址
    RXCR1_RXFCE    = 0x0400U, ///<RW接收流控制启用
    RXCR1_RXEFE    = 0x0200U, ///<RW接收错误帧启用
    RXCR1_RXMAFMA  = 0x0100U, ///<启用MAC地址的RW接收多播地址过滤
    RXCR1_RXBE     = 0x0080U, ///<RW接收广播启用
    RXCR1_RXME     = 0x0040U, ///<RW接收多播启用
    RXCR1_RXUE     = 0x0020U, ///<RW接收单播启用
    RXCR1_RXAE     = 0x0010U, ///<RW接收全部启用
    RXCR1_RXINVF   = 0x0002U, ///<RW接收反向过滤
    RXCR1_RXE      = 0x0001U, ///<RW接收启用

    RXCR2_SRDBL_SHIFT = 5U,      ///<WO SPI接收数据突发长度：4/8/16/32/帧（0-4）
    RXCR2_IUFFP       = 0x0010U, ///<RW IPv4/IPv6/UDP片段帧传递
    RXCR2_RXIUFCEZ    = 0x0008U, ///<RW接收IPv4/IPv6/UDP帧校验和等于零
    RXCR2_UDPLFE      = 0x0004U, ///<RW Lite框架启用
    RXCR2_RXICMPFCC   = 0x0002U, ///<RW接收ICMP帧校验和检查启用
    RXCR2_RXSAF       = 0x0001U, ///<RW接收源地址筛选

    TXMIR_TXMA_MASK = 0x1FFFU, ///<RO传输内存可用掩码

    RXFHSR_RXFV      = 0x8000U, ///<RO接收帧有效
    RXFHSR_RXICMPFCS = 0x2000U, ///<RO接收ICMP帧校验和状态
    RXFHSR_RXIPFCS   = 0x1000U, ///<RO接收IP帧校验和状态
    RXFHSR_RXTCPFCS  = 0x0800U, ///<RO接收TCP帧校验和状态
    RXFHSR_RXUDPFCS  = 0x0400U, ///<RO接收UDP帧校验和状态
    RXFHSR_RXBF      = 0x0080U, ///<RO接收广播帧
    RXFHSR_RXMF      = 0x0040U, ///<RO接收多播帧
    RXFHSR_RXUF      = 0x0020U, ///<RO接收单播帧
    RXFHSR_RXMR      = 0x0010U, ///<RO接收MII错误
    RXFHSR_RXFT      = 0x0008U, ///<RO接收帧类型
    RXFHSR_RXFTL     = 0x0004U, ///<RO接收帧太长
    RXFHSR_RXRF      = 0x0002U, ///<RO接收横档帧
    RXFHSR_RXCE      = 0x0001U, ///<RO接收CRC错误

    RXFHBCR_RXBC_MASK = 0x0FFFU, ///<RO接收字节计数掩码

    TXQCR_AETFE  = 0x0004U, ///<RW自动排队TXQ帧启用
    TXQCR_TXQMAM = 0x0002U, ///<RW TXQ内存可用监视器
    TXQCR_METFE  = 0x0001U, ///<RW（SC）手动排队TXQ帧启用

    RXQCR_RXDTTS   = 0x1000U, ///<RO RX持续时间计时器阈值状态
    RXQCR_RXDBCTS  = 0x0800U, ///<RO RX数据字节计数阈值状态
    RXQCR_RXFCTS   = 0x0400U, ///<RO RX帧计数阈值状态
    RXQCR_RXIPHTOE = 0x0200U, ///<RW RX IP报头两字节偏移启用
    RXQCR_RXDTTE   = 0x0080U, ///<RW RX持续时间计时器阈值启用
    RXQCR_RXDBCTE  = 0x0040U, ///<RW RX数据字节计数阈值启用
    RXQCR_RXFCTE   = 0x0020U, ///<RW RX帧计数阈值启用
    RXQCR_ADRFE    = 0x0010U, ///<RW自动退出RXQ帧启用
    RXQCR_SDA      = 0x0008U, ///<WO启动DMA访问
    RXQCR_RRXEF    = 0x0001U, ///<RW释放RX错误帧

    TXFDPR_TXFPAI    = 0x4000U, ///<RW TX帧数据指针自动递增
    TXFDPR_TXFP_MASK = 0x07FFU, ///<RO TX帧指针掩码

    RXFDPR_RXFPAI    = 0x4000U, ///<RW RX帧指针自动递增
    RXFDPR_RXFP_MASK = 0x07FFU, ///<WO RX帧指针掩码

    IER_LCIE    = 0x8000U, ///<RW链路更改中断启用
    IER_TXIE    = 0x4000U, ///<RW传输中断启用
    IER_RXIE    = 0x2000U, ///<RW接收中断启用
    IER_RXOIE   = 0x0800U, ///<RW接收超限中断启用
    IER_TXPSIE  = 0x0200U, ///<RW传输进程停止中断启用
    IER_RXPSIE  = 0x0100U, ///<RW接收进程停止中断启用
    IER_TXSAIE  = 0x0040U, ///<RW传输空间可用中断启用
    IER_RXWFDIE = 0x0020U, ///<RW接收唤醒帧检测中断启用
    IER_RXMPDIE = 0x0010U, ///<RW接收魔术包检测中断启用
    IER_LDIE    = 0x0008U, ///<RW链接检测中断启用
    IER_EDIE    = 0x0004U, ///<RW能量检测中断启用
    IER_SPIBEIE = 0x0002U, ///<RW SPI总线错误中断启用
    IER_DEDIE   = 0x0001U, ///<RW延迟能量检测中断启用

    ISR_LCIS    = 0x8000U, ///<RO（W1C）链路更改中断状态
    ISR_TXIS    = 0x4000U, ///<RO（W1C）传输中断状态
    ISR_RXIS    = 0x2000U, ///<RO（W1C）接收中断状态
    ISR_RXOIS   = 0x0800U, ///<RO（W1C）接收超限中断状态
    ISR_TXPSIS  = 0x0200U, ///<RO（W1C）传输进程停止中断状态
    ISR_RXPSIS  = 0x0100U, ///<RO（W1C）接收进程已停止中断状态
    ISR_TXSAIS  = 0x0040U, ///<RO（W1C）传输空间可用中断状态
    ISR_RXWFDIS = 0x0020U, ///<RO（W1C）接收唤醒帧检测中断状态
    ISR_RXMPDIS = 0x0010U, ///<RO（W1C）接收魔术包检测中断状态
    ISR_LDIS    = 0x0008U, ///<RO（W1C）链接检测中断状态
    ISR_EDIS    = 0x0004U, ///<RO（W1C）能量检测中断状态
    ISR_SPIBEIS = 0x0002U, ///<RO（W1C）SPI总线错误中断状态
    ISR_ALL     = 0xFFFFU, ///<WO清除寄存器值

    RXFCTR_RXFC_SHIFT = 8U,                        ///<RO RX帧计数移位
    RXFCTR_RXFC_MASK  = 0xFF << RXFCTR_RXFC_SHIFT, ///<RO RX帧计数掩码
    RXFCTR_RXFCT_MASK = 0xFFU,                     ///<RW接收帧计数阈值

    FCLWR_MASK = 0x0FFFU, ///<RW流量控制低水位线配置掩码
    FCHWR_MASK = 0x0FFFU, ///<RW流量控制高水位线配置掩码
    FCOWR_MASK = 0x0FFFU, ///<RW流量控制溢出水印配置掩码

    CIDER_KSZ8851SNL_FAMILY_ID = 0x88U,                          ///<KSZ8851SNL系列ID
    CIDER_KSZ8851SNL_CHIP_ID   = 0x7U,                           ///<KSZ8851SNL芯片ID
    CIDER_FAMILY_ID_SHIFT      = 8U,                             ///<RO系列ID转换
    CIDER_FAMILY_ID_MASK       = 0xFF << CIDER_FAMILY_ID_SHIFT,  ///<RO系列ID掩码
    CIDER_CHIP_ID_SHIFT        = 4U,                             ///<RO芯片ID偏移
    CIDER_CHIP_ID_MASK         = 0xF << CIDER_CHIP_ID_SHIFT,     ///<RO芯片ID掩码
    CIDER_REVISION_ID_SHIFT    = 1U,                             ///<RO修订ID移位
    CIDER_REVISION_ID_MASK     = 0x7 << CIDER_REVISION_ID_SHIFT, ///<RO修订ID掩码

    CGCR_LEDSEL0 = 0x0200U, ///<RW PHY LED模式：0-100BT+LINK/ACTU，1-ACT+LINK

    IACR_READ_ENABLE           = 0x1000U, ///<RW读取启用
    IACR_MIB_COUNTER_SELECT    = 0x0C00U, ///<RW表格选择
    IACR_INDIRECT_ADDRESS_MASK = 0x001FU, ///<RW间接地址掩码

    PMECR_PME_DELAY_ENABLE         = 0x4000U, ///<RW PME延迟启用
    PMECR_PME_OUTPUT_POLARITY      = 0x1000U, ///<RW PME输出极性
    PMECR_WUP_FRAME_EN             = 0x0800U, ///<RW LAN唤醒至PME输出启用接收唤醒帧
    PMECR_MAGIC_PACKET             = 0x0400U, ///<RW LAN唤醒至PME输出启用接收魔术包
    PMECR_LINK_CHANGE_TO_UP        = 0x0200U, ///<RW LAN唤醒至PME输出启用链接更改为向上
    PMECR_SIGNAL_ENERGY_DETECTED   = 0x0100U, ///<RW LAN唤醒至PME输出启用检测到的能量
    PMECR_AUTO_WAKEUP_ENABLE       = 0x0080U, ///<RW自动唤醒启用
    PMECR_WAKEUP_TO_NORMAL         = 0x0040U, ///<RW唤醒至正常操作模式
    PMECR_WAKEUP_FRAME_EVENT       = 0x0020U, ///<检测到RO（W1C）唤醒事件指示唤醒帧事件
    PMECR_WAKEUP_MAGIC_PACKET      = 0x0010U, ///<检测到RO（W1C）唤醒事件指示魔术包事件
    PMECR_WAKEUP_LINK              = 0x0008U, ///<检测到RO（W1C）唤醒事件指示链接事件
    PMECR_WAKEUP_ENERGY            = 0x0004U, ///<检测到RO（W1C）唤醒事件指示能量事件
    PMECR_PME_MODE_MASK            = 0x0003U, ///<RW电源管理模式掩码
    PMECR_PME_MODE_NORMAL          = 0x0000U, ///<RW正常操作模式
    PMECR_PME_MODE_ENERGY_DETECT   = 0x0001U, ///<RW能量检测模式
    PMECR_PME_MODE_SOFT_POWER_DOWN = 0x0002U, ///<RW软关机模式
    PMECR_PME_MODE_POWER_SAVING    = 0x0003U, ///<RW省电模式

    GSWUTR_WAKE_UP_TIME_SHIFT = 8U,                                ///<RW唤醒时移
    GSWUTR_WAKE_UP_TIME_MASK  = 0xFF << GSWUTR_WAKE_UP_TIME_SHIFT, ///<RW唤醒时间掩码
    GSWUTR_GO_SLEEP_TIME_MASK = 0x0003U,                           ///<RW进入睡眠时间掩码

    PHYRR_PHY_RESET = 0x0001U, ///<WO（SC）PHY重置位

    P1MBCR_LOCAL_LOOPBACK    = 0x4000U, ///<RW本地（远端）环回（llb）
    P1MBCR_FORCE100          = 0x2000U, ///<RW力100
    P1MBCR_AN_ENABLE         = 0x1000U, ///<RW AN启用
    P1MBCR_RESTART_AN        = 0x0200U, ///<RW重新启动AN
    P1MBCR_FORCE_FULL_DUPLEX = 0x0100U, ///<RW强制全双工
    P1MBCR_HP_MDIX           = 0x0020U, ///<RW HP Auto MDI-X模式
    P1MBCR_FORCE_MDIX        = 0x0010U, ///<RWForce MDI-X
    P1MBCR_DISABLE_MDIX      = 0x0008U, ///<RW禁用MDI-X
    P1MBCR_DISABLE_TRANSMIT  = 0x0002U, ///<RW禁用传输
    P1MBCR_DISABLE_LED       = 0x0001U, ///<RW禁用LED

    P1MBSR_T4_CAPABLE          = 0x8000U, ///<RO T4能力
    P1MBSR_100_FULL_CAPABLE    = 0x4000U, ///<RO 100全功能
    P1MBSR_100_HALF_CAPABLE    = 0x2000U, ///<RO 100半功能
    P1MBSR_10_FULL_CAPABLE     = 0x1000U, ///<RO 10全功能
    P1MBSR_10_HALF_CAPABLE     = 0x0800U, ///<RO 10半功能
    P1MBSR_PREAMBLE_SUPPRESSED = 0x0040U, ///<抑制RO前导码（不支持）
    P1MBSR_AN_COMPLETE         = 0x0020U, ///<RO AN完成
    P1MBSR_AN_CAPABLE          = 0x0008U, ///<支持RO AN
    P1MBSR_LINK_STATUS         = 0x0004U, ///<RO链路状态
    P1MBSR_JABBER_TEST         = 0x0002U, ///<RO Jabber测试（不支持）
    P1MBSR_EXTENDED_CAPABLE    = 0x0001U, ///<RO扩展功能

    P1ANAR_NEXT_PAGE    = 0x8000U, ///<RO下一页（不支持）
    P1ANAR_REMOTE_FAULT = 0x2000U, ///<RO远程故障（不支持）
    P1ANAR_PAUSE        = 0x0400U, ///<RW暂停（流量控制功能）
    P1ANAR_ADV_100_FULL = 0x0100U, ///<RW Adv 100满
    P1ANAR_ADV_100_HALF = 0x0080U, ///<RW Adv 100一半
    P1ANAR_ADV_10_FULL  = 0x0040U, ///<RW Adv 10满
    P1ANAR_ADV_10_HALF  = 0x0020U, ///<RW Adv 10一半

    P1ANLPR_NEXT_PAGE    = 0x8000U, ///<RO下一页（不支持）
    P1ANLPR_LP_ACK       = 0x4000U, ///<RO LP ACK（不支持）
    P1ANLPR_REMOTE_FAULT = 0x2000U, ///<RO远程故障（不支持）
    P1ANLPR_PAUSE        = 0x0400U, ///<RO暂停
    P1ANLPR_ADV_100_FULL = 0x0100U, ///<RO Adv 100满
    P1ANLPR_ADV_100_HALF = 0x0080U, ///<RO Adv 100一半
    P1ANLPR_ADV_10_FULL  = 0x0040U, ///<RO Adv 10满
    P1ANLPR_ADV_10_HALF  = 0x0020U, ///<RO Adv 10一半

    P1SCLMD_VCT_RESULT_SHIFT       = 13U,                             ///<RO VCT结果移位
    P1SCLMD_VCT_RESULT_MASK        = 0x3 << P1SCLMD_VCT_RESULT_SHIFT, ///<RO VCT结果掩码
    P1SCLMD_VCT_RESULT_NORMAL      = 0x0U,                            ///<RO VCT结果正常条件
    P1SCLMD_VCT_RESULT_OPEN        = 0x1U,                            ///<RO VCT结果开路电缆条件
    P1SCLMD_VCT_RESULT_SHORT       = 0x2U,                            ///<RO VCT结果短电缆条件
    P1SCLMD_VCT_RESULT_TEST_FAILED = 0x3U,                            ///<RO VCT结果测试失败
    P1SCLMD_VCT_ENABLE             = 0x1000U,                         ///<RW（SC）VCT启用
    P1SCLMD_FORCE_LINK             = 0x0800U,                         ///<RW力链接
    P1SCLMD_REMOTE_LOOPBACK        = 0x0200U,                         ///<RW远程（近端）环回（rlb）
    P1SCLMD_VCT_FAULT_COUNT_MASK   = 0x1FU,                           ///<RO到故障的距离*0.4m

    P1CR_LED_OFF                                 = 0x8000U, ///<RW关闭所有端口1指示灯
    P1CR_TXIDS                                   = 0x4000U, ///<RW禁用端口的发射器。
    P1CR_RESTART_AN                              = 0x2000U, ///<RW重新启动AN
    P1CR_DISABLE_AUTO_MDI_MDIX                   = 0x0400U, ///<RW禁用自动MDI/MDI-X
    P1CR_FORCE_MDIX                              = 0x0200U, ///<RW力MDI-X
    P1CR_AUTO_NEGOTIATION_ENABLE                 = 0x0080U, ///<RW自动协商启用
    P1CR_FORCE_SPEED                             = 0x0040U, ///<RW强制速度100
    P1CR_FORCE_DUPLEX                            = 0x0020U, ///<RW强制全双工
    P1CR_ADVERTISED_FLOW_CONTROL_CAPABILITY      = 0x0010U, ///<RW广告流控制功能
    P1CR_ADVERTISED_100BT_FULL_DUPLEX_CAPABILITY = 0x0008U, ///<RW广告100BT全双工功能
    P1CR_ADVERTISED_100BT_HALF_DUPLEX_CAPABILITY = 0x0004U, ///<RW广告100BT半双工功能
    P1CR_ADVERTISED_10BT_FULL_DUPLEX_CAPABILITY  = 0x0002U, ///<RW广告10BT全双工功能
    P1CR_ADVERTISED_10BT_HALF_DUPLEX_CAPABILITY  = 0x0001U, ///<RW广告10BT半双工功能

    P1SR_HP_MDIX                              = 0x8000U, ///<RW HP Auto MDI-X模式
    P1SR_POLARITY_REVERSE                     = 0x2000U, ///<RO极性反转
    P1SR_OPERATION_SPEED                      = 0x0400U, ///<RO运行速度100
    P1SR_OPERATION_DUPLEX                     = 0x0200U, ///<RO操作双工满
    P1SR_MDIX_STATUS                          = 0x0080U, ///<RO MDI状态
    P1SR_AN_DONE                              = 0x0040U, ///<RO AN完成
    P1SR_LINK_GOOD                            = 0x0020U, ///<RO链路良好
    P1SR_PARTNER_FLOW_CONTROL_CAPABILITY      = 0x0010U, ///<RO合作伙伴流量控制能力
    P1SR_PARTNER_100BT_FULL_DUPLEX_CAPABILITY = 0x0008U, ///<RO合作伙伴100BT全双工能力
    P1SR_PARTNER_100BT_HALF_DUPLEX_CAPABILITY = 0x0004U, ///<RO合作伙伴100BT半双工能力
    P1SR_PARTNER_10BT_FULL_DUPLEX_CAPABILITY  = 0x0002U, ///<RO合作伙伴10BT全双工能力
    P1SR_PARTNER_10BT_HALF_DUPLEX_CAPABILITY  = 0x0001U, ///<RO合作伙伴10BT半双工能力
} ksz8851_register_bits_t;

