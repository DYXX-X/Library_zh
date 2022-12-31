/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file 此文件包含CC2538寄存器定义。
 *
 */

#ifndef CC2538_REG_H_
#define CC2538_REG_H_

#include <stdint.h>

// clang格式关闭

#define HWREG(x)                                (*((volatile uint32_t *)(x)))

/*!
 * 对于32位整数数组的寄存器。
 *
 * @param       reg     注册地址
 * @param       idx     寄存器数组索引
 */
#define HWREG_ARR(reg, idx)                     HWREG((reg) + ((idx) << 2))

#define NVIC_ST_CTRL                            0xE000E010  // SysTick控制和状态
#define NVIC_ST_RELOAD                          0xE000E014  // SysTick重新加载值寄存器
#define NVIC_EN0                                0xE000E100  // 中断0-31设置启用

#define NVIC_ST_CTRL_COUNT                      0x00010000  // 计数标志
#define NVIC_ST_CTRL_CLK_SRC                    0x00000004  // 时钟源
#define NVIC_ST_CTRL_INTEN                      0x00000002  // 中断启用
#define NVIC_ST_CTRL_ENABLE                     0x00000001  // 使可能

#define RFCORE_XREG_SRCMATCH_EN                 0x00000001  // SRCMATCH.SRC_MATCH_EN(1)
#define RFCORE_XREG_SRCMATCH_AUTOPEND           0x00000002  // SRCMATCH.AUTOPEND(1)
#define RFCORE_XREG_SRCMATCH_PEND_DATAREQ_ONLY  0x00000004  // SRCMATCH.PEND_DATAREQ_ONLY(1)

#define RFCORE_XREG_SRCMATCH_ENABLE_STATUS_SIZE 3           // 源匹配启用状态的寄存器数
#define RFCORE_XREG_SRCMATCH_SHORT_ENTRIES      24          // 最多24个短地址条目
#define RFCORE_XREG_SRCMATCH_EXT_ENTRIES        12          // 最多12个扩展地址条目
#define RFCORE_XREG_SRCMATCH_SHORT_ENTRY_OFFSET 4           // 一个短地址条目的地址偏移量
#define RFCORE_XREG_SRCMATCH_EXT_ENTRY_OFFSET   8           // 一个扩展地址项的地址偏移量

#define INT_UART0                               21          // UART0接收和发送

#define IEEE_EUI64                              0x00280028  // IEEE EUI-64地址

#define RFCORE_FFSM_SRCADDRESS_TABLE            0x40088400  // 源地址表

#define RFCORE_FFSM_SRCEXTPENDEN0               0x40088590  // 启用/禁用每个扩展地址的自动挂起
#define RFCORE_FFSM_SRCSHORTPENDEN0             0x4008859C  // 启用/禁用每个短地址的自动挂起
#define RFCORE_FFSM_EXT_ADDR0                   0x400885A8  // 本地地址信息
#define RFCORE_FFSM_PAN_ID0                     0x400885C8  // 本地地址信息
#define RFCORE_FFSM_PAN_ID1                     0x400885CC  // 本地地址信息
#define RFCORE_FFSM_SHORT_ADDR0                 0x400885D0  // 本地地址信息
#define RFCORE_FFSM_SHORT_ADDR1                 0x400885D4  // 本地地址信息
#define RFCORE_XREG_FRMFILT0                    0x40088600  // 帧过滤功能
#define RFCORE_XREG_SRCMATCH                    0x40088608  // 源地址匹配和挂起位
#define RFCORE_XREG_SRCSHORTEN0                 0x4008860C  // 短地址匹配
#define RFCORE_XREG_SRCEXTEN0                   0x40088618  // 扩展地址匹配

#define RFCORE_XREG_FRMCTRL0                    0x40088624  // 框架处理
#define RFCORE_XREG_FRMCTRL1                    0x40088628  // 框架处理
#define RFCORE_XREG_RXENABLE                    0x4008862C  // RX启用
#define RFCORE_XREG_FREQCTRL                    0x4008863C  // 控制射频频率
#define RFCORE_XREG_TXPOWER                     0x40088640  // 控制输出功率
#define RFCORE_XREG_FSMSTAT0                    0x40088648  // 无线电有限状态机状态
#define RFCORE_XREG_FSMSTAT1                    0x4008864C  // 无线电状态寄存器
#define RFCORE_XREG_FIFOPCTRL                   0x40088650  // FIFOP阈值
#define RFCORE_XREG_CCACTRL0                    0x40088658  // CCA阈值
#define RFCORE_XREG_RSSI                        0x40088660  // RSSI状态寄存器
#define RFCORE_XREG_RSSISTAT                    0x40088664  // RSSI有效状态寄存器
#define RFCORE_XREG_AGCCTRL1                    0x400886C8  // AGC参考电平
#define RFCORE_XREG_RFC_OBS_CTRL                0x400887AC  // 射频核心可观测输出
#define RFCORE_XREG_TXFILTCFG                   0x400887E8  // TX滤波器配置
#define RFCORE_XREG_RFRND                       0x4008869C  // 随机数据
#define RFCORE_SFR_RFDATA                       0x40088828  // TX FIFO和RX FIFO
#define RFCORE_SFR_RFERRF                       0x4008882C  // RF错误中断标志
#define RFCORE_SFR_RFIRQF0                      0x40088834  // RF中断标志
#define RFCORE_SFR_RFST                         0x40088838  // 射频CSMA-CA/选通处理器
#define CCTEST_OBSSEL                           0x44010014  // CCTEST可观测输出路线

#define RFCORE_XREG_FRMFILT0_FRAME_FILTER_EN    0x00000001  // 启用帧过滤

#define RFCORE_XREG_FRMCTRL0_AUTOACK            0x00000020
#define RFCORE_XREG_FRMCTRL0_ENERGY_SCAN        0x00000010
#define RFCORE_XREG_FRMCTRL0_AUTOCRC            0x00000040
#define RFCORE_XREG_FRMCTRL0_INFINITY_RX        0x00000008

#define RFCORE_XREG_FRMCTRL1_PENDING_OR         0x00000004

#define RFCORE_XREG_RFRND_IRND                  0x00000001

#define RFCORE_XREG_FSMSTAT0_STATE_MASK         0x0000003F
#define RFCORE_XREG_FSMSTAT0_CAL_DONE           0x00000080
#define RFCORE_XREG_FSMSTAT0_CAL_RUN            0x00000040

#define RFCORE_XREG_FSMSTAT0_STATE_IDLE         0x00000000
#define RFCORE_XREG_FSMSTAT0_STATE_RX_CAL       0x00000002
#define RFCORE_XREG_FSMSTAT0_STATE_SFD_WAIT0    0x00000003
#define RFCORE_XREG_FSMSTAT0_STATE_SFD_WAIT1    0x00000004
#define RFCORE_XREG_FSMSTAT0_STATE_SFD_WAIT2    0x00000005
#define RFCORE_XREG_FSMSTAT0_STATE_SFD_WAIT3    0x00000006
#define RFCORE_XREG_FSMSTAT0_STATE_RX0          0x00000007
#define RFCORE_XREG_FSMSTAT0_STATE_RX1          0x00000008
#define RFCORE_XREG_FSMSTAT0_STATE_RX2          0x00000009
#define RFCORE_XREG_FSMSTAT0_STATE_RX3          0x0000000A
#define RFCORE_XREG_FSMSTAT0_STATE_RX4          0x0000000B
#define RFCORE_XREG_FSMSTAT0_STATE_RX5          0x0000000C
#define RFCORE_XREG_FSMSTAT0_STATE_RX6          0x0000000D
#define RFCORE_XREG_FSMSTAT0_STATE_RX_WAIT      0x0000000E
#define RFCORE_XREG_FSMSTAT0_STATE_RX_FRST      0x00000010
#define RFCORE_XREG_FSMSTAT0_STATE_RX_OVER      0x00000011
#define RFCORE_XREG_FSMSTAT0_STATE_TX_CAL       0x00000020
#define RFCORE_XREG_FSMSTAT0_STATE_TX0          0x00000022
#define RFCORE_XREG_FSMSTAT0_STATE_TX1          0x00000023
#define RFCORE_XREG_FSMSTAT0_STATE_TX2          0x00000024
#define RFCORE_XREG_FSMSTAT0_STATE_TX3          0x00000025
#define RFCORE_XREG_FSMSTAT0_STATE_TX4          0x00000026
#define RFCORE_XREG_FSMSTAT0_STATE_TX_FINAL     0x00000027
#define RFCORE_XREG_FSMSTAT0_STATE_RXTX_TRANS   0x00000028
#define RFCORE_XREG_FSMSTAT0_STATE_ACK_CAL      0x00000030
#define RFCORE_XREG_FSMSTAT0_STATE_ACK0         0x00000031
#define RFCORE_XREG_FSMSTAT0_STATE_ACK1         0x00000032
#define RFCORE_XREG_FSMSTAT0_STATE_ACK2         0x00000033
#define RFCORE_XREG_FSMSTAT0_STATE_ACK3         0x00000034
#define RFCORE_XREG_FSMSTAT0_STATE_ACK4         0x00000035
#define RFCORE_XREG_FSMSTAT0_STATE_ACK5         0x00000036
#define RFCORE_XREG_FSMSTAT0_STATE_ACK_DELAY    0x00000037
#define RFCORE_XREG_FSMSTAT0_STATE_TX_UNDER     0x00000038
#define RFCORE_XREG_FSMSTAT0_STATE_TX_DOWN0     0x0000001A
#define RFCORE_XREG_FSMSTAT0_STATE_TX_DOWN1     0x0000003A

#define RFCORE_XREG_FSMSTAT1_RX_ACTIVE          0x00000001
#define RFCORE_XREG_FSMSTAT1_TX_ACTIVE          0x00000002
#define RFCORE_XREG_FSMSTAT1_LOCK_STATUS        0x00000004
#define RFCORE_XREG_FSMSTAT1_SAMPLED_CCA        0x00000008
#define RFCORE_XREG_FSMSTAT1_CCA                0x00000010  // 清晰通道评估
#define RFCORE_XREG_FSMSTAT1_SFD                0x00000020
#define RFCORE_XREG_FSMSTAT1_FIFOP              0x00000040
#define RFCORE_XREG_FSMSTAT1_FIFO               0x00000080

#define RFCORE_XREG_RSSISTAT_RSSI_VALID         0x00000001  // RSSI值有效。

#define RFCORE_XREG_RFC_OBS_POL_INV             0x00000040  // OBS信号极性反转
#define RFCORE_XREG_RFC_OBS_MUX_ZERO            0x00000000  // 可观测=恒定零
#define RFCORE_XREG_RFC_OBS_MUX_ONE             0x00000001  // 可观测=常数1
#define RFCORE_XREG_RFC_OBS_MUX_SNIFF_DATA      0x00000008  // RFC嗅探数据
#define RFCORE_XREG_RFC_OBS_MUX_SNIFF_CLK       0x00000009  // RFC嗅探时钟
#define RFCORE_XREG_RFC_OBS_MUX_RSSI_VALID      0x0000000c  // RSSI有效
#define RFCORE_XREG_RFC_OBS_MUX_DEMOD_CCA       0x0000000d  // 清晰通道评估
#define RFCORE_XREG_RFC_OBS_MUX_SAMPLED_CCA     0x0000000e  // 采样CCA信号
#define RFCORE_XREG_RFC_OBS_MUX_SFD_SYNC        0x0000000f  // 接收或发送SFD
#define RFCORE_XREG_RFC_OBS_MUX_TX_ACTIVE       0x00000010  // 变送器激活
#define RFCORE_XREG_RFC_OBS_MUX_RX_ACTIVE       0x00000011  // 接收器激活
#define RFCORE_XREG_RFC_OBS_MUX_FFCTRL_FIFO     0x00000012  // FIFO中的一个或多个字节
#define RFCORE_XREG_RFC_OBS_MUX_FFCTRL_FIFOP    0x00000013  // FIFO中的一个或多个帧
#define RFCORE_XREG_RFC_OBS_MUX_PACKET_DONE     0x00000014  // 数据包已接收
#define RFCORE_XREG_RFC_OBS_MUX_RFC_XOR_RAND_IQ 0x00000016  // RAND I ^ RAND Q
#define RFCORE_XREG_RFC_OBS_MUX_RFC_RAND_Q      0x00000017  // 来自Q通道的随机数据
#define RFCORE_XREG_RFC_OBS_MUX_RFC_RAND_I      0x00000018  // 来自I通道的随机数据
#define RFCORE_XREG_RFC_OBS_MUX_LOCK_STATUS     0x00000019  // PLL锁定
#define RFCORE_XREG_RFC_OBS_MUX_PA_PD           0x00000028  // 电源放大器断电
#define RFCORE_XREG_RFC_OBS_MUX_LNA_PD          0x0000002a  // LNA电源关闭

#define RFCORE_SFR_RFERRF_NLOCK                 0x00000001  // 未能实现PLL锁定。
#define RFCORE_SFR_RFERRF_RXABO                 0x00000002  // RX中止。
#define RFCORE_SFR_RFERRF_RXOVERF               0x00000004  // RX FIFO溢出。
#define RFCORE_SFR_RFERRF_RXUNDERF              0x00000008  // RX FIFO下溢。
#define RFCORE_SFR_RFERRF_TXOVERF               0x00000010  // TX FIFO溢出。
#define RFCORE_SFR_RFERRF_TXUNDERF              0x00000020  // TX FIFO下溢。
#define RFCORE_SFR_RFERRF_STROBEERR             0x00000040  // 命令选通错误。

#define RFCORE_SFR_RFST_INSTR_RXON              0xE3        // 指令集RX开启
#define RFCORE_SFR_RFST_INSTR_TXON              0xE9        // 指令集TX开启
#define RFCORE_SFR_RFST_INSTR_RFOFF             0xEF        // 指令设置RF关闭
#define RFCORE_SFR_RFST_INSTR_FLUSHRX           0xED        // 指令集刷新rx缓冲区
#define RFCORE_SFR_RFST_INSTR_FLUSHTX           0xEE        // 指令集刷新tx缓冲区

#define CCTEST_OBSSEL_EN                        0x00000080  // 启用此引脚上的OBS输出
#define CCTEST_OBSSEL_SEL_OBS0                  0x00000000  // 将OBS0路由到针脚
#define CCTEST_OBSSEL_SEL_OBS1                  0x00000001  // 将OBS1路由至针脚
#define CCTEST_OBSSEL_SEL_OBS2                  0x00000002  // 将OBS2路由到针脚

#define ANA_REGS_BASE                           0x400D6000  // ANA_REGS
#define ANA_REGS_O_IVCTRL                       0x00000004  // 模拟控制寄存器

#define SYS_CTRL_CLOCK_CTRL                     0x400D2000  // 时钟控制寄存器
#define SYS_CTRL_SYSDIV_32MHZ                   0x00000000  // sysclk 32MHz的Sys_div
#define SYS_CTRL_CLOCK_CTRL_AMP_DET             0x00200000

#define SYS_CTRL_PWRDBG                         0x400D2074
#define SYS_CTRL_PWRDBG_FORCE_WARM_RESET        0x00000008

#define SYS_CTRL_RCGCUART                       0x400D2028
#define SYS_CTRL_SCGCUART                       0x400D202C
#define SYS_CTRL_DCGCUART                       0x400D2030
#define SYS_CTRL_I_MAP                          0x400D2098
#define SYS_CTRL_RCGCRFC                        0x400D20A8
#define SYS_CTRL_SCGCRFC                        0x400D20AC
#define SYS_CTRL_DCGCRFC                        0x400D20B0
#define SYS_CTRL_EMUOVR                         0x400D20B4

#define SYS_CTRL_RCGCRFC_RFC0                   0x00000001
#define SYS_CTRL_SCGCRFC_RFC0                   0x00000001
#define SYS_CTRL_DCGCRFC_RFC0                   0x00000001

#define SYS_CTRL_I_MAP_ALTMAP                   0x00000001

#define SYS_CTRL_RCGCUART_UART0                 0x00000001
#define SYS_CTRL_SCGCUART_UART0                 0x00000001
#define SYS_CTRL_DCGCUART_UART0                 0x00000001

#define SYS_CTRL_RCGCUART_UART1                 0x00000002
#define SYS_CTRL_SCGCUART_UART1                 0x00000002
#define SYS_CTRL_DCGCUART_UART1                 0x00000002

#define IOC_PA0_SEL                             0x400D4000  // 外围设备选择控制
#define IOC_PA1_SEL                             0x400D4004  // 外围设备选择控制
#define IOC_PA2_SEL                             0x400D4008
#define IOC_PA3_SEL                             0x400D400C
#define IOC_UARTRXD_UART0                       0x400D4100
#define IOC_UARTRXD_UART1                       0x400D4108

#define IOC_PA0_OVER                            0x400D4080
#define IOC_PA1_OVER                            0x400D4084
#define IOC_PA2_OVER                            0x400D4088
#define IOC_PA3_OVER                            0x400D408C

#define IOC_MUX_OUT_SEL_UART0_TXD               0x00000000
#define IOC_MUX_OUT_SEL_UART1_TXD               0x00000002

#define IOC_OVERRIDE_OE                         0x00000008  // PAD配置超控输出启用
#define IOC_OVERRIDE_DIS                        0x00000000  // PAD配置超控已禁用

#define IOC_PAD_IN_SEL_PA0                      0x00000000  // PA0
#define IOC_PAD_IN_SEL_PA1                      0x00000001  // PA1
#define IOC_PAD_IN_SEL_PA2                      0x00000002  // PA2
#define IOC_PAD_IN_SEL_PA3                      0x00000003  // PA3

#define UART0_BASE                              0x4000C000
#define UART1_BASE                              0x4000D000
#define GPIO_A_BASE                             0x400D9000  // GPIO A
#define GPIO_B_BASE                             0x400DA000  // GPIO B
#define GPIO_C_BASE                             0x400DB000  // GPIO C
#define GPIO_D_BASE                             0x400DC000  // GPIO D

#define GPIO_O_DIR                              0x00000400
#define GPIO_O_AFSEL                            0x00000420

#define GPIO_PIN(x)                             (1UL << x)  // 任意GPIO引脚
#define GPIO_PIN_0                              0x00000001  // GPIO引脚0
#define GPIO_PIN_1                              0x00000002  // GPIO引脚1
#define GPIO_PIN_2                              0x00000004  // GPIO引脚2
#define GPIO_PIN_3                              0x00000008  // GPIO引脚3
#define GPIO_PIN_4                              0x00000010  // GPIO引脚4
#define GPIO_PIN_5                              0x00000020  // GPIO引脚5
#define GPIO_PIN_6                              0x00000040  // GPIO引脚6
#define GPIO_PIN_7                              0x00000080  // GPIO引脚7

#define UART_O_DR                               0x00000000  // UART数据
#define UART_O_FR                               0x00000018  // UART标志
#define UART_O_IBRD                             0x00000024
#define UART_O_FBRD                             0x00000028
#define UART_O_LCRH                             0x0000002C
#define UART_O_CTL                              0x00000030  // UART控制
#define UART_O_IM                               0x00000038  // UART中断掩码
#define UART_O_MIS                              0x00000040  // UART屏蔽中断状态
#define UART_O_ICR                              0x00000044  // UART中断清除
#define UART_O_CC                               0x00000FC8  // UART时钟配置

#define UART_FR_RXFE                            0x00000010  // UART接收FIFO为空
#define UART_FR_TXFF                            0x00000020  // UART传输FIFO已满
#define UART_FR_RXFF                            0x00000040  // UART接收FIFO已满

#define UART_CONFIG_WLEN_8                      0x00000060  // 8位数据
#define UART_CONFIG_STOP_ONE                    0x00000000  // 一个停止位
#define UART_CONFIG_PAR_NONE                    0x00000000  // 无奇偶校验

#define UART_CTL_UARTEN                         0x00000001  // UART启用
#define UART_CTL_TXE                            0x00000100  // UART传输启用
#define UART_CTL_RXE                            0x00000200  // UART接收启用

#define UART_IM_RXIM                            0x00000010  // UART接收中断掩码
#define UART_IM_RTIM                            0x00000040  // UART接收超时中断

#define SOC_ADC_ADCCON1                         0x400D7000  // ADC控制
#define SOC_ADC_RNDL                            0x400D7014  // RNG低数据
#define SOC_ADC_RNDH                            0x400D7018  // RNG高数据

#define SOC_ADC_ADCCON1_RCTRL0                  0x00000004  // ADCCON1 RCTRL位0
#define SOC_ADC_ADCCON1_RCTRL1                  0x00000008  // ADCCON1 RCTRL位1

#define FLASH_CTRL_FCTL                         0x400D3008  // 闪光灯控制
#define FLASH_CTRL_DIECFG0                      0x400D3014  // Flash信息

// clang格式打开

#endif

