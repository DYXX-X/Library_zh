/* 自动生成的配置文件hpl_usart_config。小时*/
#ifndef HPL_USART_CONFIG_H
#define HPL_USART_CONFIG_H

// <<<在上下文菜单中使用配置向导>>

#include <peripheral_clk_config.h>

#ifndef CONF_USART_1_ENABLE
#define CONF_USART_1_ENABLE 1
#endif

// <h> 基本配置

// <o> 帧奇偶校验
// <0x0=>偶校验
// <0x1=>奇数奇偶校验
// <0x2=>奇偶校验强制为0
// <0x3=>奇偶校验强制为1
// <0x4=>无奇偶校验
// <i> USART帧的奇偶校验位模式
// <id>usart_parity
#ifndef CONF_USART_1_PARITY
#define CONF_USART_1_PARITY 0x4
#endif

// <o> 字符大小
// <0x0=>5位
// <0x1=>6位
// <0x2=>7位
// <0x3=>8位
// <i> USART帧中的数据字符大小
// <id>使用的字符大小
#ifndef CONF_USART_1_CHSIZE
#define CONF_USART_1_CHSIZE 0x3
#endif

// <o> 停止位
// <0=>1个停止位
// <1=>1.5个停止位
// <2=>2个停止位
// <i> USART帧中的停止位数
// 使用开始_停止_比特
#ifndef CONF_USART_1_SBMODE
#define CONF_USART_1_SBMODE 0
#endif

// <o> 时钟输出选择
// <0=>USART不驱动SCK引脚
// <1=>如果USCLKS未选择外部时钟SCK，USART驱动SCK引脚
// <i> 在USART sck中选择时钟输出，如果处于usrt主模式，请驱动sck。
// <id>使用rt_clock_output_select
#ifndef CONF_USART_1_CLKO
#define CONF_USART_1_CLKO 0
#endif

// <o> 波特率<1-30000>
// <i> USART波特率设置
// <id>使用折扣率
#ifndef CONF_USART_1_BAUD
#define CONF_USART_1_BAUD 9600
#endif

// </h>

// <e> 高级配置
// <id>usart_advanced（使用高级）
#ifndef CONF_USART_1_ADVANCED_CONFIG
#define CONF_USART_1_ADVANCED_CONFIG 0
#endif

// <o> 通道模式
// <0=>正常模式
// <1=>自动回声
// <2=>本地环回
// <3=>远程环回
// <i> USART帧中的信道模式
// <id>使用频道模式
#ifndef CONF_USART_1_CHMODE
#define CONF_USART_1_CHMODE 0
#endif

// <q> 9位字符启用
// <i> 启用9位字符，其优先级高于5/6/7/8位。
// <id>usart_9bits_enable（启用）
#ifndef CONF_USART_1_MODE9
#define CONF_USART_1_MODE9 0
#endif

// <o> 变量同步
// <0=>用户定义的配置
// 当字符被写入US_THR时，＜1＝＞同步字段被更新
// <i> 命令/数据同步启动Frarm分隔符的变量同步
// <id>变量_同步
#ifndef CONF_USART_1_VAR_SYNC
#define CONF_USART_1_VAR_SYNC 0
#endif

// <o> 过采样模式
// <0=>16过采样
// <1=>8过采样
// <i> UART模式下的过采样模式
// 使用过采样模式
#ifndef CONF_USART_1_OVER
#define CONF_USART_1_OVER 0
#endif

// <o> 禁止不确认
// <0=>生成NACK
// <1=>未生成NACK
// <i> 禁止不确认
// <id>使用__inack
#ifndef CONF_USART_1_INACK
#define CONF_USART_1_INACK 1
#endif

// <o> 禁用连续NACK
// 当出现奇偶校验错误时，立即在ISO线上发送NACK
// <1=>许多奇偶校验错误在ISO线上生成NACK
// <i> 禁用连续NACK
// <id>美国点心
#ifndef CONF_USART_1_DSNACK
#define CONF_USART_1_DSNACK 0
#endif

// <o> 反转的数据
// <0=>数据未反转，正常模式
// <1=>数据被反转
// <i> 反转的数据
// <id>使用数据
#ifndef CONF_USART_1_INVDATA
#define CONF_USART_1_INVDATA 0
#endif

// <o> 最大自动迭代次数<0-7>
// <i> 定义ISO7816模式下的最大迭代次数，协议T=0。
// <id>使用rt_max_迭代
#ifndef CONF_USART_1_MAX_ITERATION
#define CONF_USART_1_MAX_ITERATION 0
#endif

// <q> 接收线过滤器启用
// <i> USART是否使用三采样滤波器对接收线进行滤波
// <id>usart_receive_filter_enable
#ifndef CONF_USART_1_FILTER
#define CONF_USART_1_FILTER 0
#endif

// <q> 曼彻斯特编码器/解码器启用
// <i> USART曼彻斯特编码器/解码器
// 启用usart_manchester_filter
#ifndef CONF_USART_1_MAN
#define CONF_USART_1_MAN 0
#endif

// <o> 曼彻斯特同步模式
// <0=>曼彻斯特起始位是0到1的转换
// ＜1＝＞曼彻斯特起始位是1到0的转换
// <i> 曼彻斯特同步模式
// <id>使用rt_manchester_synchronization_mode
#ifndef CONF_USART_1_MODSYNC
#define CONF_USART_1_MODSYNC 0
#endif

// <o> 开始帧分隔符选择器
// <0=>开始帧定界符是COMMAND或DATA SYNC
// ＜1＝＞开始帧分隔符是一位
// <i> 开始帧分隔符选择器
// <id>usart_start_frame_delimiter
#ifndef CONF_USART_1_ONEBIT
#define CONF_USART_1_ONEBIT 0
#endif

// <o> 分数部分<0-7>
// <i> 如果波特率生成器处于小数模式，则波特率的小数部分
// <id>usart_arch_fractional公司
#ifndef CONF_USART_1_FRACTIONAL
#define CONF_USART_1_FRACTIONAL 0x0
#endif

// <o> 数据顺序
// <0=>LSB首先传输
// ＜1＝＞MSB首先传输
// <i> 帧中数据位的数据顺序
// <id>使用时间_搜索时间_msbf
#ifndef CONF_USART_1_MSBF
#define CONF_USART_1_MSBF 0
#endif

// </e>

#define CONF_USART_1_MODE 0x0

// 在UART模式下计算BAUD寄存器值
#if CONF_USART1_CK_SRC < 3
#ifndef CONF_USART_1_BAUD_CD
#define CONF_USART_1_BAUD_CD ((CONF_USART1_FREQUENCY) / CONF_USART_1_BAUD / 8 / (2 - CONF_USART_1_OVER))
#endif
#ifndef CONF_USART_1_BAUD_FP
#define CONF_USART_1_BAUD_FP                                                                                           \
	((CONF_USART1_FREQUENCY) / CONF_USART_1_BAUD / (2 - CONF_USART_1_OVER) - 8 * CONF_USART_1_BAUD_CD)
#endif
#elif CONF_USART1_CK_SRC == 3
// 没有分区处于活动状态。写入US_BRGR的值无效。
#ifndef CONF_USART_1_BAUD_CD
#define CONF_USART_1_BAUD_CD 1
#endif
#ifndef CONF_USART_1_BAUD_FP
#define CONF_USART_1_BAUD_FP 1
#endif
#endif

// <<<配置节末尾>>

#endif // HPL_USART_CONFIG_H

