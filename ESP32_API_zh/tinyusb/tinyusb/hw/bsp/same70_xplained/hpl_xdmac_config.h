/* 自动生成的配置文件hpl_xdmac_config。小时*/
#ifndef HPL_XDMAC_CONFIG_H
#define HPL_XDMAC_CONFIG_H

// <<<在上下文菜单中使用配置向导>>

// <e> XDMAC启用
// <i> 指示xdmac是否已启用
// 启用xdmac_enable
#ifndef CONF_DMA_ENABLE
#define CONF_DMA_ENABLE 0
#endif

// <e> 频道0设置
// ＜id＞dmac_channel_0_settings
#ifndef CONF_DMAC_CHANNEL_0_SETTINGS
#define CONF_DMAC_CHANNEL_0_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burstze_0
#ifndef CONF_DMAC_BURSTSIZE_0
#define CONF_DMAC_BURSTSIZE_0 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_0
#ifndef CONF_DMAC_CHUNKSIZE_0
#define CONF_DMAC_CHUNKSIZE_0 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_0
#ifndef CONF_DMAC_BEATSIZE_0
#define CONF_DMAC_BEATSIZE_0 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_0
#ifndef CONF_DMAC_SRC_INTERFACE_0
#define CONF_DMAC_SRC_INTERFACE_0 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_0
#ifndef CONF_DMAC_DES_INTERFACE_0
#define CONF_DMAC_DES_INTERFACE_0 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_0
#ifndef CONF_DMAC_SRCINC_0
#define CONF_DMAC_SRCINC_0 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_0
#ifndef CONF_DMAC_DSTINC_0
#define CONF_DMAC_DSTINC_0 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// ＜id＞dma_trans_type_0
#ifndef CONF_DMAC_TRANS_TYPE_0
#define CONF_DMAC_TRANS_TYPE_0 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_0
#ifndef CONF_DMAC_TRIGSRC_0
#define CONF_DMAC_TRIGSRC_0 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_0 == 0
#define CONF_DMAC_TYPE_0 0
#define CONF_DMAC_DSYNC_0 0
#elif CONF_DMAC_TRANS_TYPE_0 == 1
#define CONF_DMAC_TYPE_0 1
#define CONF_DMAC_DSYNC_0 0
#elif CONF_DMAC_TRANS_TYPE_0 == 2
#define CONF_DMAC_TYPE_0 1
#define CONF_DMAC_DSYNC_0 1
#endif

#if CONF_DMAC_TRIGSRC_0 == 0xFF
#define CONF_DMAC_SWREQ_0 1
#else
#define CONF_DMAC_SWREQ_0 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_0_SETTINGS == 1 && CONF_DMAC_BEATSIZE_0 != 2 && ((!CONF_DMAC_SRCINC_0) || (!CONF_DMAC_DSTINC_0)))
#if (!CONF_DMAC_SRCINC_0)
#define CONF_DMAC_SRC_STRIDE_0 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_0)
#define CONF_DMAC_DES_STRIDE_0 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_0
#define CONF_DMAC_SRC_STRIDE_0 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_0
#define CONF_DMAC_DES_STRIDE_0 0
#endif

// <e> 通道1设置
// ＜id＞dmac_channel_1_settings
#ifndef CONF_DMAC_CHANNEL_1_SETTINGS
#define CONF_DMAC_CHANNEL_1_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_1
#ifndef CONF_DMAC_BURSTSIZE_1
#define CONF_DMAC_BURSTSIZE_1 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_1
#ifndef CONF_DMAC_CHUNKSIZE_1
#define CONF_DMAC_CHUNKSIZE_1 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_1
#ifndef CONF_DMAC_BEATSIZE_1
#define CONF_DMAC_BEATSIZE_1 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_1
#ifndef CONF_DMAC_SRC_INTERFACE_1
#define CONF_DMAC_SRC_INTERFACE_1 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_1
#ifndef CONF_DMAC_DES_INTERFACE_1
#define CONF_DMAC_DES_INTERFACE_1 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_1
#ifndef CONF_DMAC_SRCINC_1
#define CONF_DMAC_SRCINC_1 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_1
#ifndef CONF_DMAC_DSTINC_1
#define CONF_DMAC_DSTINC_1 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_1
#ifndef CONF_DMAC_TRANS_TYPE_1
#define CONF_DMAC_TRANS_TYPE_1 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// ＜id＞dmac_trifsrc_1
#ifndef CONF_DMAC_TRIGSRC_1
#define CONF_DMAC_TRIGSRC_1 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_1 == 0
#define CONF_DMAC_TYPE_1 0
#define CONF_DMAC_DSYNC_1 0
#elif CONF_DMAC_TRANS_TYPE_1 == 1
#define CONF_DMAC_TYPE_1 1
#define CONF_DMAC_DSYNC_1 0
#elif CONF_DMAC_TRANS_TYPE_1 == 2
#define CONF_DMAC_TYPE_1 1
#define CONF_DMAC_DSYNC_1 1
#endif

#if CONF_DMAC_TRIGSRC_1 == 0xFF
#define CONF_DMAC_SWREQ_1 1
#else
#define CONF_DMAC_SWREQ_1 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_1_SETTINGS == 1 && CONF_DMAC_BEATSIZE_1 != 2 && ((!CONF_DMAC_SRCINC_1) || (!CONF_DMAC_DSTINC_1)))
#if (!CONF_DMAC_SRCINC_1)
#define CONF_DMAC_SRC_STRIDE_1 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_1)
#define CONF_DMAC_DES_STRIDE_1 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_1
#define CONF_DMAC_SRC_STRIDE_1 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_1
#define CONF_DMAC_DES_STRIDE_1 0
#endif

// <e> 通道2设置
// ＜id＞dmac_channel_2_settings
#ifndef CONF_DMAC_CHANNEL_2_SETTINGS
#define CONF_DMAC_CHANNEL_2_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_2
#ifndef CONF_DMAC_BURSTSIZE_2
#define CONF_DMAC_BURSTSIZE_2 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_2
#ifndef CONF_DMAC_CHUNKSIZE_2
#define CONF_DMAC_CHUNKSIZE_2 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_2
#ifndef CONF_DMAC_BEATSIZE_2
#define CONF_DMAC_BEATSIZE_2 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_2
#ifndef CONF_DMAC_SRC_INTERFACE_2
#define CONF_DMAC_SRC_INTERFACE_2 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_2
#ifndef CONF_DMAC_DES_INTERFACE_2
#define CONF_DMAC_DES_INTERFACE_2 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_2
#ifndef CONF_DMAC_SRCINC_2
#define CONF_DMAC_SRCINC_2 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_2
#ifndef CONF_DMAC_DSTINC_2
#define CONF_DMAC_DSTINC_2 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_2
#ifndef CONF_DMAC_TRANS_TYPE_2
#define CONF_DMAC_TRANS_TYPE_2 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// ＜id＞dmac_trifsrc_2
#ifndef CONF_DMAC_TRIGSRC_2
#define CONF_DMAC_TRIGSRC_2 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_2 == 0
#define CONF_DMAC_TYPE_2 0
#define CONF_DMAC_DSYNC_2 0
#elif CONF_DMAC_TRANS_TYPE_2 == 1
#define CONF_DMAC_TYPE_2 1
#define CONF_DMAC_DSYNC_2 0
#elif CONF_DMAC_TRANS_TYPE_2 == 2
#define CONF_DMAC_TYPE_2 1
#define CONF_DMAC_DSYNC_2 1
#endif

#if CONF_DMAC_TRIGSRC_2 == 0xFF
#define CONF_DMAC_SWREQ_2 1
#else
#define CONF_DMAC_SWREQ_2 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_2_SETTINGS == 1 && CONF_DMAC_BEATSIZE_2 != 2 && ((!CONF_DMAC_SRCINC_2) || (!CONF_DMAC_DSTINC_2)))
#if (!CONF_DMAC_SRCINC_2)
#define CONF_DMAC_SRC_STRIDE_2 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_2)
#define CONF_DMAC_DES_STRIDE_2 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_2
#define CONF_DMAC_SRC_STRIDE_2 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_2
#define CONF_DMAC_DES_STRIDE_2 0
#endif

// <e> 通道3设置
// ＜id＞dmac_channel_3_settings
#ifndef CONF_DMAC_CHANNEL_3_SETTINGS
#define CONF_DMAC_CHANNEL_3_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_3
#ifndef CONF_DMAC_BURSTSIZE_3
#define CONF_DMAC_BURSTSIZE_3 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_3
#ifndef CONF_DMAC_CHUNKSIZE_3
#define CONF_DMAC_CHUNKSIZE_3 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_3
#ifndef CONF_DMAC_BEATSIZE_3
#define CONF_DMAC_BEATSIZE_3 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_3
#ifndef CONF_DMAC_SRC_INTERFACE_3
#define CONF_DMAC_SRC_INTERFACE_3 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_3
#ifndef CONF_DMAC_DES_INTERFACE_3
#define CONF_DMAC_DES_INTERFACE_3 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_3
#ifndef CONF_DMAC_SRCINC_3
#define CONF_DMAC_SRCINC_3 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_3
#ifndef CONF_DMAC_DSTINC_3
#define CONF_DMAC_DSTINC_3 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_3
#ifndef CONF_DMAC_TRANS_TYPE_3
#define CONF_DMAC_TRANS_TYPE_3 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_3
#ifndef CONF_DMAC_TRIGSRC_3
#define CONF_DMAC_TRIGSRC_3 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_3 == 0
#define CONF_DMAC_TYPE_3 0
#define CONF_DMAC_DSYNC_3 0
#elif CONF_DMAC_TRANS_TYPE_3 == 1
#define CONF_DMAC_TYPE_3 1
#define CONF_DMAC_DSYNC_3 0
#elif CONF_DMAC_TRANS_TYPE_3 == 2
#define CONF_DMAC_TYPE_3 1
#define CONF_DMAC_DSYNC_3 1
#endif

#if CONF_DMAC_TRIGSRC_3 == 0xFF
#define CONF_DMAC_SWREQ_3 1
#else
#define CONF_DMAC_SWREQ_3 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_3_SETTINGS == 1 && CONF_DMAC_BEATSIZE_3 != 2 && ((!CONF_DMAC_SRCINC_3) || (!CONF_DMAC_DSTINC_3)))
#if (!CONF_DMAC_SRCINC_3)
#define CONF_DMAC_SRC_STRIDE_3 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_3)
#define CONF_DMAC_DES_STRIDE_3 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_3
#define CONF_DMAC_SRC_STRIDE_3 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_3
#define CONF_DMAC_DES_STRIDE_3 0
#endif

// <e> 通道4设置
// ＜id＞dmac_channel_4_settings
#ifndef CONF_DMAC_CHANNEL_4_SETTINGS
#define CONF_DMAC_CHANNEL_4_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_4
#ifndef CONF_DMAC_BURSTSIZE_4
#define CONF_DMAC_BURSTSIZE_4 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_4
#ifndef CONF_DMAC_CHUNKSIZE_4
#define CONF_DMAC_CHUNKSIZE_4 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_4
#ifndef CONF_DMAC_BEATSIZE_4
#define CONF_DMAC_BEATSIZE_4 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_4
#ifndef CONF_DMAC_SRC_INTERFACE_4
#define CONF_DMAC_SRC_INTERFACE_4 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_4
#ifndef CONF_DMAC_DES_INTERFACE_4
#define CONF_DMAC_DES_INTERFACE_4 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_4
#ifndef CONF_DMAC_SRCINC_4
#define CONF_DMAC_SRCINC_4 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_4
#ifndef CONF_DMAC_DSTINC_4
#define CONF_DMAC_DSTINC_4 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_4
#ifndef CONF_DMAC_TRANS_TYPE_4
#define CONF_DMAC_TRANS_TYPE_4 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// ＜id＞dmac_trifsrc_4
#ifndef CONF_DMAC_TRIGSRC_4
#define CONF_DMAC_TRIGSRC_4 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_4 == 0
#define CONF_DMAC_TYPE_4 0
#define CONF_DMAC_DSYNC_4 0
#elif CONF_DMAC_TRANS_TYPE_4 == 1
#define CONF_DMAC_TYPE_4 1
#define CONF_DMAC_DSYNC_4 0
#elif CONF_DMAC_TRANS_TYPE_4 == 2
#define CONF_DMAC_TYPE_4 1
#define CONF_DMAC_DSYNC_4 1
#endif

#if CONF_DMAC_TRIGSRC_4 == 0xFF
#define CONF_DMAC_SWREQ_4 1
#else
#define CONF_DMAC_SWREQ_4 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_4_SETTINGS == 1 && CONF_DMAC_BEATSIZE_4 != 2 && ((!CONF_DMAC_SRCINC_4) || (!CONF_DMAC_DSTINC_4)))
#if (!CONF_DMAC_SRCINC_4)
#define CONF_DMAC_SRC_STRIDE_4 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_4)
#define CONF_DMAC_DES_STRIDE_4 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_4
#define CONF_DMAC_SRC_STRIDE_4 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_4
#define CONF_DMAC_DES_STRIDE_4 0
#endif

// <e> 通道5设置
// ＜id＞dmac_channel_5_settings
#ifndef CONF_DMAC_CHANNEL_5_SETTINGS
#define CONF_DMAC_CHANNEL_5_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_5
#ifndef CONF_DMAC_BURSTSIZE_5
#define CONF_DMAC_BURSTSIZE_5 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_5
#ifndef CONF_DMAC_CHUNKSIZE_5
#define CONF_DMAC_CHUNKSIZE_5 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_5
#ifndef CONF_DMAC_BEATSIZE_5
#define CONF_DMAC_BEATSIZE_5 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_5
#ifndef CONF_DMAC_SRC_INTERFACE_5
#define CONF_DMAC_SRC_INTERFACE_5 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_5
#ifndef CONF_DMAC_DES_INTERFACE_5
#define CONF_DMAC_DES_INTERFACE_5 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc5
#ifndef CONF_DMAC_SRCINC_5
#define CONF_DMAC_SRCINC_5 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_5
#ifndef CONF_DMAC_DSTINC_5
#define CONF_DMAC_DSTINC_5 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// ＜id＞dma_trans_type_5
#ifndef CONF_DMAC_TRANS_TYPE_5
#define CONF_DMAC_TRANS_TYPE_5 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// ＜id＞dmac_trifsrc_5
#ifndef CONF_DMAC_TRIGSRC_5
#define CONF_DMAC_TRIGSRC_5 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_5 == 0
#define CONF_DMAC_TYPE_5 0
#define CONF_DMAC_DSYNC_5 0
#elif CONF_DMAC_TRANS_TYPE_5 == 1
#define CONF_DMAC_TYPE_5 1
#define CONF_DMAC_DSYNC_5 0
#elif CONF_DMAC_TRANS_TYPE_5 == 2
#define CONF_DMAC_TYPE_5 1
#define CONF_DMAC_DSYNC_5 1
#endif

#if CONF_DMAC_TRIGSRC_5 == 0xFF
#define CONF_DMAC_SWREQ_5 1
#else
#define CONF_DMAC_SWREQ_5 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_5_SETTINGS == 1 && CONF_DMAC_BEATSIZE_5 != 2 && ((!CONF_DMAC_SRCINC_5) || (!CONF_DMAC_DSTINC_5)))
#if (!CONF_DMAC_SRCINC_5)
#define CONF_DMAC_SRC_STRIDE_5 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_5)
#define CONF_DMAC_DES_STRIDE_5 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_5
#define CONF_DMAC_SRC_STRIDE_5 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_5
#define CONF_DMAC_DES_STRIDE_5 0
#endif

// <e> 通道6设置
// ＜id＞dmac_channel_6_settings
#ifndef CONF_DMAC_CHANNEL_6_SETTINGS
#define CONF_DMAC_CHANNEL_6_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_6
#ifndef CONF_DMAC_BURSTSIZE_6
#define CONF_DMAC_BURSTSIZE_6 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_6
#ifndef CONF_DMAC_CHUNKSIZE_6
#define CONF_DMAC_CHUNKSIZE_6 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_6
#ifndef CONF_DMAC_BEATSIZE_6
#define CONF_DMAC_BEATSIZE_6 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_6
#ifndef CONF_DMAC_SRC_INTERFACE_6
#define CONF_DMAC_SRC_INTERFACE_6 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_6
#ifndef CONF_DMAC_DES_INTERFACE_6
#define CONF_DMAC_DES_INTERFACE_6 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_6
#ifndef CONF_DMAC_SRCINC_6
#define CONF_DMAC_SRCINC_6 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_6
#ifndef CONF_DMAC_DSTINC_6
#define CONF_DMAC_DSTINC_6 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_6
#ifndef CONF_DMAC_TRANS_TYPE_6
#define CONF_DMAC_TRANS_TYPE_6 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_6
#ifndef CONF_DMAC_TRIGSRC_6
#define CONF_DMAC_TRIGSRC_6 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_6 == 0
#define CONF_DMAC_TYPE_6 0
#define CONF_DMAC_DSYNC_6 0
#elif CONF_DMAC_TRANS_TYPE_6 == 1
#define CONF_DMAC_TYPE_6 1
#define CONF_DMAC_DSYNC_6 0
#elif CONF_DMAC_TRANS_TYPE_6 == 2
#define CONF_DMAC_TYPE_6 1
#define CONF_DMAC_DSYNC_6 1
#endif

#if CONF_DMAC_TRIGSRC_6 == 0xFF
#define CONF_DMAC_SWREQ_6 1
#else
#define CONF_DMAC_SWREQ_6 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_6_SETTINGS == 1 && CONF_DMAC_BEATSIZE_6 != 2 && ((!CONF_DMAC_SRCINC_6) || (!CONF_DMAC_DSTINC_6)))
#if (!CONF_DMAC_SRCINC_6)
#define CONF_DMAC_SRC_STRIDE_6 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_6)
#define CONF_DMAC_DES_STRIDE_6 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_6
#define CONF_DMAC_SRC_STRIDE_6 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_6
#define CONF_DMAC_DES_STRIDE_6 0
#endif

// <e> 通道7设置
// ＜id＞dmac_channel_7_settings
#ifndef CONF_DMAC_CHANNEL_7_SETTINGS
#define CONF_DMAC_CHANNEL_7_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_7
#ifndef CONF_DMAC_BURSTSIZE_7
#define CONF_DMAC_BURSTSIZE_7 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_7
#ifndef CONF_DMAC_CHUNKSIZE_7
#define CONF_DMAC_CHUNKSIZE_7 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_7
#ifndef CONF_DMAC_BEATSIZE_7
#define CONF_DMAC_BEATSIZE_7 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_7
#ifndef CONF_DMAC_SRC_INTERFACE_7
#define CONF_DMAC_SRC_INTERFACE_7 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_7
#ifndef CONF_DMAC_DES_INTERFACE_7
#define CONF_DMAC_DES_INTERFACE_7 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_7
#ifndef CONF_DMAC_SRCINC_7
#define CONF_DMAC_SRCINC_7 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_7
#ifndef CONF_DMAC_DSTINC_7
#define CONF_DMAC_DSTINC_7 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_7
#ifndef CONF_DMAC_TRANS_TYPE_7
#define CONF_DMAC_TRANS_TYPE_7 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_7
#ifndef CONF_DMAC_TRIGSRC_7
#define CONF_DMAC_TRIGSRC_7 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_7 == 0
#define CONF_DMAC_TYPE_7 0
#define CONF_DMAC_DSYNC_7 0
#elif CONF_DMAC_TRANS_TYPE_7 == 1
#define CONF_DMAC_TYPE_7 1
#define CONF_DMAC_DSYNC_7 0
#elif CONF_DMAC_TRANS_TYPE_7 == 2
#define CONF_DMAC_TYPE_7 1
#define CONF_DMAC_DSYNC_7 1
#endif

#if CONF_DMAC_TRIGSRC_7 == 0xFF
#define CONF_DMAC_SWREQ_7 1
#else
#define CONF_DMAC_SWREQ_7 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_7_SETTINGS == 1 && CONF_DMAC_BEATSIZE_7 != 2 && ((!CONF_DMAC_SRCINC_7) || (!CONF_DMAC_DSTINC_7)))
#if (!CONF_DMAC_SRCINC_7)
#define CONF_DMAC_SRC_STRIDE_7 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_7)
#define CONF_DMAC_DES_STRIDE_7 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_7
#define CONF_DMAC_SRC_STRIDE_7 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_7
#define CONF_DMAC_DES_STRIDE_7 0
#endif

// <e> 通道8设置
// ＜id＞dmac_channel_8_settings
#ifndef CONF_DMAC_CHANNEL_8_SETTINGS
#define CONF_DMAC_CHANNEL_8_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_8
#ifndef CONF_DMAC_BURSTSIZE_8
#define CONF_DMAC_BURSTSIZE_8 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_8
#ifndef CONF_DMAC_CHUNKSIZE_8
#define CONF_DMAC_CHUNKSIZE_8 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_8
#ifndef CONF_DMAC_BEATSIZE_8
#define CONF_DMAC_BEATSIZE_8 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_8
#ifndef CONF_DMAC_SRC_INTERFACE_8
#define CONF_DMAC_SRC_INTERFACE_8 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_8
#ifndef CONF_DMAC_DES_INTERFACE_8
#define CONF_DMAC_DES_INTERFACE_8 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_8
#ifndef CONF_DMAC_SRCINC_8
#define CONF_DMAC_SRCINC_8 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_8
#ifndef CONF_DMAC_DSTINC_8
#define CONF_DMAC_DSTINC_8 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_8
#ifndef CONF_DMAC_TRANS_TYPE_8
#define CONF_DMAC_TRANS_TYPE_8 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_8
#ifndef CONF_DMAC_TRIGSRC_8
#define CONF_DMAC_TRIGSRC_8 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_8 == 0
#define CONF_DMAC_TYPE_8 0
#define CONF_DMAC_DSYNC_8 0
#elif CONF_DMAC_TRANS_TYPE_8 == 1
#define CONF_DMAC_TYPE_8 1
#define CONF_DMAC_DSYNC_8 0
#elif CONF_DMAC_TRANS_TYPE_8 == 2
#define CONF_DMAC_TYPE_8 1
#define CONF_DMAC_DSYNC_8 1
#endif

#if CONF_DMAC_TRIGSRC_8 == 0xFF
#define CONF_DMAC_SWREQ_8 1
#else
#define CONF_DMAC_SWREQ_8 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_8_SETTINGS == 1 && CONF_DMAC_BEATSIZE_8 != 2 && ((!CONF_DMAC_SRCINC_8) || (!CONF_DMAC_DSTINC_8)))
#if (!CONF_DMAC_SRCINC_8)
#define CONF_DMAC_SRC_STRIDE_8 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_8)
#define CONF_DMAC_DES_STRIDE_8 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_8
#define CONF_DMAC_SRC_STRIDE_8 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_8
#define CONF_DMAC_DES_STRIDE_8 0
#endif

// <e> 通道9设置
// ＜id＞dmac_channel_9_settings
#ifndef CONF_DMAC_CHANNEL_9_SETTINGS
#define CONF_DMAC_CHANNEL_9_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_9
#ifndef CONF_DMAC_BURSTSIZE_9
#define CONF_DMAC_BURSTSIZE_9 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_9
#ifndef CONF_DMAC_CHUNKSIZE_9
#define CONF_DMAC_CHUNKSIZE_9 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_9
#ifndef CONF_DMAC_BEATSIZE_9
#define CONF_DMAC_BEATSIZE_9 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_9
#ifndef CONF_DMAC_SRC_INTERFACE_9
#define CONF_DMAC_SRC_INTERFACE_9 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_9
#ifndef CONF_DMAC_DES_INTERFACE_9
#define CONF_DMAC_DES_INTERFACE_9 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_9
#ifndef CONF_DMAC_SRCINC_9
#define CONF_DMAC_SRCINC_9 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_9
#ifndef CONF_DMAC_DSTINC_9
#define CONF_DMAC_DSTINC_9 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_9
#ifndef CONF_DMAC_TRANS_TYPE_9
#define CONF_DMAC_TRANS_TYPE_9 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_9
#ifndef CONF_DMAC_TRIGSRC_9
#define CONF_DMAC_TRIGSRC_9 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_9 == 0
#define CONF_DMAC_TYPE_9 0
#define CONF_DMAC_DSYNC_9 0
#elif CONF_DMAC_TRANS_TYPE_9 == 1
#define CONF_DMAC_TYPE_9 1
#define CONF_DMAC_DSYNC_9 0
#elif CONF_DMAC_TRANS_TYPE_9 == 2
#define CONF_DMAC_TYPE_9 1
#define CONF_DMAC_DSYNC_9 1
#endif

#if CONF_DMAC_TRIGSRC_9 == 0xFF
#define CONF_DMAC_SWREQ_9 1
#else
#define CONF_DMAC_SWREQ_9 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_9_SETTINGS == 1 && CONF_DMAC_BEATSIZE_9 != 2 && ((!CONF_DMAC_SRCINC_9) || (!CONF_DMAC_DSTINC_9)))
#if (!CONF_DMAC_SRCINC_9)
#define CONF_DMAC_SRC_STRIDE_9 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_9)
#define CONF_DMAC_DES_STRIDE_9 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_9
#define CONF_DMAC_SRC_STRIDE_9 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_9
#define CONF_DMAC_DES_STRIDE_9 0
#endif

// <e> 通道10设置
// ＜id＞dmac_channel_10_settings
#ifndef CONF_DMAC_CHANNEL_10_SETTINGS
#define CONF_DMAC_CHANNEL_10_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_10
#ifndef CONF_DMAC_BURSTSIZE_10
#define CONF_DMAC_BURSTSIZE_10 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_10
#ifndef CONF_DMAC_CHUNKSIZE_10
#define CONF_DMAC_CHUNKSIZE_10 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_10
#ifndef CONF_DMAC_BEATSIZE_10
#define CONF_DMAC_BEATSIZE_10 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_10
#ifndef CONF_DMAC_SRC_INTERFACE_10
#define CONF_DMAC_SRC_INTERFACE_10 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_10
#ifndef CONF_DMAC_DES_INTERFACE_10
#define CONF_DMAC_DES_INTERFACE_10 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_10
#ifndef CONF_DMAC_SRCINC_10
#define CONF_DMAC_SRCINC_10 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_10
#ifndef CONF_DMAC_DSTINC_10
#define CONF_DMAC_DSTINC_10 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// ＜id＞dma_trans_type_10
#ifndef CONF_DMAC_TRANS_TYPE_10
#define CONF_DMAC_TRANS_TYPE_10 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_10
#ifndef CONF_DMAC_TRIGSRC_10
#define CONF_DMAC_TRIGSRC_10 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_10 == 0
#define CONF_DMAC_TYPE_10 0
#define CONF_DMAC_DSYNC_10 0
#elif CONF_DMAC_TRANS_TYPE_10 == 1
#define CONF_DMAC_TYPE_10 1
#define CONF_DMAC_DSYNC_10 0
#elif CONF_DMAC_TRANS_TYPE_10 == 2
#define CONF_DMAC_TYPE_10 1
#define CONF_DMAC_DSYNC_10 1
#endif

#if CONF_DMAC_TRIGSRC_10 == 0xFF
#define CONF_DMAC_SWREQ_10 1
#else
#define CONF_DMAC_SWREQ_10 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_10_SETTINGS == 1 && CONF_DMAC_BEATSIZE_10 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_10) || (!CONF_DMAC_DSTINC_10)))
#if (!CONF_DMAC_SRCINC_10)
#define CONF_DMAC_SRC_STRIDE_10 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_10)
#define CONF_DMAC_DES_STRIDE_10 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_10
#define CONF_DMAC_SRC_STRIDE_10 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_10
#define CONF_DMAC_DES_STRIDE_10 0
#endif

// <e> 通道11设置
// <id>dmac_channel_11_settings
#ifndef CONF_DMAC_CHANNEL_11_SETTINGS
#define CONF_DMAC_CHANNEL_11_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_11
#ifndef CONF_DMAC_BURSTSIZE_11
#define CONF_DMAC_BURSTSIZE_11 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_11
#ifndef CONF_DMAC_CHUNKSIZE_11
#define CONF_DMAC_CHUNKSIZE_11 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_11
#ifndef CONF_DMAC_BEATSIZE_11
#define CONF_DMAC_BEATSIZE_11 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_11
#ifndef CONF_DMAC_SRC_INTERFACE_11
#define CONF_DMAC_SRC_INTERFACE_11 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_11
#ifndef CONF_DMAC_DES_INTERFACE_11
#define CONF_DMAC_DES_INTERFACE_11 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_11
#ifndef CONF_DMAC_SRCINC_11
#define CONF_DMAC_SRCINC_11 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_11
#ifndef CONF_DMAC_DSTINC_11
#define CONF_DMAC_DSTINC_11 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_11
#ifndef CONF_DMAC_TRANS_TYPE_11
#define CONF_DMAC_TRANS_TYPE_11 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_11
#ifndef CONF_DMAC_TRIGSRC_11
#define CONF_DMAC_TRIGSRC_11 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_11 == 0
#define CONF_DMAC_TYPE_11 0
#define CONF_DMAC_DSYNC_11 0
#elif CONF_DMAC_TRANS_TYPE_11 == 1
#define CONF_DMAC_TYPE_11 1
#define CONF_DMAC_DSYNC_11 0
#elif CONF_DMAC_TRANS_TYPE_11 == 2
#define CONF_DMAC_TYPE_11 1
#define CONF_DMAC_DSYNC_11 1
#endif

#if CONF_DMAC_TRIGSRC_11 == 0xFF
#define CONF_DMAC_SWREQ_11 1
#else
#define CONF_DMAC_SWREQ_11 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_11_SETTINGS == 1 && CONF_DMAC_BEATSIZE_11 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_11) || (!CONF_DMAC_DSTINC_11)))
#if (!CONF_DMAC_SRCINC_11)
#define CONF_DMAC_SRC_STRIDE_11 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_11)
#define CONF_DMAC_DES_STRIDE_11 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_11
#define CONF_DMAC_SRC_STRIDE_11 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_11
#define CONF_DMAC_DES_STRIDE_11 0
#endif

// <e> 通道12设置
// <id>dmac_channel_12_settings
#ifndef CONF_DMAC_CHANNEL_12_SETTINGS
#define CONF_DMAC_CHANNEL_12_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_12
#ifndef CONF_DMAC_BURSTSIZE_12
#define CONF_DMAC_BURSTSIZE_12 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_12
#ifndef CONF_DMAC_CHUNKSIZE_12
#define CONF_DMAC_CHUNKSIZE_12 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_12
#ifndef CONF_DMAC_BEATSIZE_12
#define CONF_DMAC_BEATSIZE_12 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_12
#ifndef CONF_DMAC_SRC_INTERFACE_12
#define CONF_DMAC_SRC_INTERFACE_12 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_12
#ifndef CONF_DMAC_DES_INTERFACE_12
#define CONF_DMAC_DES_INTERFACE_12 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_12
#ifndef CONF_DMAC_SRCINC_12
#define CONF_DMAC_SRCINC_12 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_12
#ifndef CONF_DMAC_DSTINC_12
#define CONF_DMAC_DSTINC_12 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_12
#ifndef CONF_DMAC_TRANS_TYPE_12
#define CONF_DMAC_TRANS_TYPE_12 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// ＜id＞dmac_trifsrc_12
#ifndef CONF_DMAC_TRIGSRC_12
#define CONF_DMAC_TRIGSRC_12 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_12 == 0
#define CONF_DMAC_TYPE_12 0
#define CONF_DMAC_DSYNC_12 0
#elif CONF_DMAC_TRANS_TYPE_12 == 1
#define CONF_DMAC_TYPE_12 1
#define CONF_DMAC_DSYNC_12 0
#elif CONF_DMAC_TRANS_TYPE_12 == 2
#define CONF_DMAC_TYPE_12 1
#define CONF_DMAC_DSYNC_12 1
#endif

#if CONF_DMAC_TRIGSRC_12 == 0xFF
#define CONF_DMAC_SWREQ_12 1
#else
#define CONF_DMAC_SWREQ_12 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_12_SETTINGS == 1 && CONF_DMAC_BEATSIZE_12 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_12) || (!CONF_DMAC_DSTINC_12)))
#if (!CONF_DMAC_SRCINC_12)
#define CONF_DMAC_SRC_STRIDE_12 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_12)
#define CONF_DMAC_DES_STRIDE_12 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_12
#define CONF_DMAC_SRC_STRIDE_12 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_12
#define CONF_DMAC_DES_STRIDE_12 0
#endif

// <e> 通道13设置
// <id>dmac_channel_13_settings
#ifndef CONF_DMAC_CHANNEL_13_SETTINGS
#define CONF_DMAC_CHANNEL_13_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_13
#ifndef CONF_DMAC_BURSTSIZE_13
#define CONF_DMAC_BURSTSIZE_13 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_13
#ifndef CONF_DMAC_CHUNKSIZE_13
#define CONF_DMAC_CHUNKSIZE_13 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_13
#ifndef CONF_DMAC_BEATSIZE_13
#define CONF_DMAC_BEATSIZE_13 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_13
#ifndef CONF_DMAC_SRC_INTERFACE_13
#define CONF_DMAC_SRC_INTERFACE_13 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_13
#ifndef CONF_DMAC_DES_INTERFACE_13
#define CONF_DMAC_DES_INTERFACE_13 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_13
#ifndef CONF_DMAC_SRCINC_13
#define CONF_DMAC_SRCINC_13 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_13
#ifndef CONF_DMAC_DSTINC_13
#define CONF_DMAC_DSTINC_13 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_13
#ifndef CONF_DMAC_TRANS_TYPE_13
#define CONF_DMAC_TRANS_TYPE_13 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// ＜id＞dmac_trifsrc_13
#ifndef CONF_DMAC_TRIGSRC_13
#define CONF_DMAC_TRIGSRC_13 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_13 == 0
#define CONF_DMAC_TYPE_13 0
#define CONF_DMAC_DSYNC_13 0
#elif CONF_DMAC_TRANS_TYPE_13 == 1
#define CONF_DMAC_TYPE_13 1
#define CONF_DMAC_DSYNC_13 0
#elif CONF_DMAC_TRANS_TYPE_13 == 2
#define CONF_DMAC_TYPE_13 1
#define CONF_DMAC_DSYNC_13 1
#endif

#if CONF_DMAC_TRIGSRC_13 == 0xFF
#define CONF_DMAC_SWREQ_13 1
#else
#define CONF_DMAC_SWREQ_13 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_13_SETTINGS == 1 && CONF_DMAC_BEATSIZE_13 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_13) || (!CONF_DMAC_DSTINC_13)))
#if (!CONF_DMAC_SRCINC_13)
#define CONF_DMAC_SRC_STRIDE_13 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_13)
#define CONF_DMAC_DES_STRIDE_13 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_13
#define CONF_DMAC_SRC_STRIDE_13 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_13
#define CONF_DMAC_DES_STRIDE_13 0
#endif

// <e> 通道14设置
// <id>dmac_channel_14_settings
#ifndef CONF_DMAC_CHANNEL_14_SETTINGS
#define CONF_DMAC_CHANNEL_14_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_14
#ifndef CONF_DMAC_BURSTSIZE_14
#define CONF_DMAC_BURSTSIZE_14 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_14
#ifndef CONF_DMAC_CHUNKSIZE_14
#define CONF_DMAC_CHUNKSIZE_14 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_14
#ifndef CONF_DMAC_BEATSIZE_14
#define CONF_DMAC_BEATSIZE_14 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_14
#ifndef CONF_DMAC_SRC_INTERFACE_14
#define CONF_DMAC_SRC_INTERFACE_14 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_14
#ifndef CONF_DMAC_DES_INTERFACE_14
#define CONF_DMAC_DES_INTERFACE_14 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_14
#ifndef CONF_DMAC_SRCINC_14
#define CONF_DMAC_SRCINC_14 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_14
#ifndef CONF_DMAC_DSTINC_14
#define CONF_DMAC_DSTINC_14 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_14
#ifndef CONF_DMAC_TRANS_TYPE_14
#define CONF_DMAC_TRANS_TYPE_14 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_14
#ifndef CONF_DMAC_TRIGSRC_14
#define CONF_DMAC_TRIGSRC_14 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_14 == 0
#define CONF_DMAC_TYPE_14 0
#define CONF_DMAC_DSYNC_14 0
#elif CONF_DMAC_TRANS_TYPE_14 == 1
#define CONF_DMAC_TYPE_14 1
#define CONF_DMAC_DSYNC_14 0
#elif CONF_DMAC_TRANS_TYPE_14 == 2
#define CONF_DMAC_TYPE_14 1
#define CONF_DMAC_DSYNC_14 1
#endif

#if CONF_DMAC_TRIGSRC_14 == 0xFF
#define CONF_DMAC_SWREQ_14 1
#else
#define CONF_DMAC_SWREQ_14 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_14_SETTINGS == 1 && CONF_DMAC_BEATSIZE_14 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_14) || (!CONF_DMAC_DSTINC_14)))
#if (!CONF_DMAC_SRCINC_14)
#define CONF_DMAC_SRC_STRIDE_14 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_14)
#define CONF_DMAC_DES_STRIDE_14 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_14
#define CONF_DMAC_SRC_STRIDE_14 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_14
#define CONF_DMAC_DES_STRIDE_14 0
#endif

// <e> 通道15设置
// <id>dmac_channel_15_设置
#ifndef CONF_DMAC_CHANNEL_15_SETTINGS
#define CONF_DMAC_CHANNEL_15_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_15
#ifndef CONF_DMAC_BURSTSIZE_15
#define CONF_DMAC_BURSTSIZE_15 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_15
#ifndef CONF_DMAC_CHUNKSIZE_15
#define CONF_DMAC_CHUNKSIZE_15 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_15
#ifndef CONF_DMAC_BEATSIZE_15
#define CONF_DMAC_BEATSIZE_15 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_15
#ifndef CONF_DMAC_SRC_INTERFACE_15
#define CONF_DMAC_SRC_INTERFACE_15 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_15
#ifndef CONF_DMAC_DES_INTERFACE_15
#define CONF_DMAC_DES_INTERFACE_15 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_15
#ifndef CONF_DMAC_SRCINC_15
#define CONF_DMAC_SRCINC_15 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_15
#ifndef CONF_DMAC_DSTINC_15
#define CONF_DMAC_DSTINC_15 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>数据传输类型_15
#ifndef CONF_DMAC_TRANS_TYPE_15
#define CONF_DMAC_TRANS_TYPE_15 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// ＜id＞dmac_trifsrc_15
#ifndef CONF_DMAC_TRIGSRC_15
#define CONF_DMAC_TRIGSRC_15 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_15 == 0
#define CONF_DMAC_TYPE_15 0
#define CONF_DMAC_DSYNC_15 0
#elif CONF_DMAC_TRANS_TYPE_15 == 1
#define CONF_DMAC_TYPE_15 1
#define CONF_DMAC_DSYNC_15 0
#elif CONF_DMAC_TRANS_TYPE_15 == 2
#define CONF_DMAC_TYPE_15 1
#define CONF_DMAC_DSYNC_15 1
#endif

#if CONF_DMAC_TRIGSRC_15 == 0xFF
#define CONF_DMAC_SWREQ_15 1
#else
#define CONF_DMAC_SWREQ_15 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_15_SETTINGS == 1 && CONF_DMAC_BEATSIZE_15 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_15) || (!CONF_DMAC_DSTINC_15)))
#if (!CONF_DMAC_SRCINC_15)
#define CONF_DMAC_SRC_STRIDE_15 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_15)
#define CONF_DMAC_DES_STRIDE_15 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_15
#define CONF_DMAC_SRC_STRIDE_15 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_15
#define CONF_DMAC_DES_STRIDE_15 0
#endif

// <e> 通道16设置
// <id>dmac_channel_16_settings（Dmc_channel_16_设置）
#ifndef CONF_DMAC_CHANNEL_16_SETTINGS
#define CONF_DMAC_CHANNEL_16_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_16
#ifndef CONF_DMAC_BURSTSIZE_16
#define CONF_DMAC_BURSTSIZE_16 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_16
#ifndef CONF_DMAC_CHUNKSIZE_16
#define CONF_DMAC_CHUNKSIZE_16 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_16
#ifndef CONF_DMAC_BEATSIZE_16
#define CONF_DMAC_BEATSIZE_16 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_16
#ifndef CONF_DMAC_SRC_INTERFACE_16
#define CONF_DMAC_SRC_INTERFACE_16 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_16
#ifndef CONF_DMAC_DES_INTERFACE_16
#define CONF_DMAC_DES_INTERFACE_16 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_16
#ifndef CONF_DMAC_SRCINC_16
#define CONF_DMAC_SRCINC_16 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_16
#ifndef CONF_DMAC_DSTINC_16
#define CONF_DMAC_DSTINC_16 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_16
#ifndef CONF_DMAC_TRANS_TYPE_16
#define CONF_DMAC_TRANS_TYPE_16 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_16
#ifndef CONF_DMAC_TRIGSRC_16
#define CONF_DMAC_TRIGSRC_16 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_16 == 0
#define CONF_DMAC_TYPE_16 0
#define CONF_DMAC_DSYNC_16 0
#elif CONF_DMAC_TRANS_TYPE_16 == 1
#define CONF_DMAC_TYPE_16 1
#define CONF_DMAC_DSYNC_16 0
#elif CONF_DMAC_TRANS_TYPE_16 == 2
#define CONF_DMAC_TYPE_16 1
#define CONF_DMAC_DSYNC_16 1
#endif

#if CONF_DMAC_TRIGSRC_16 == 0xFF
#define CONF_DMAC_SWREQ_16 1
#else
#define CONF_DMAC_SWREQ_16 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_16_SETTINGS == 1 && CONF_DMAC_BEATSIZE_16 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_16) || (!CONF_DMAC_DSTINC_16)))
#if (!CONF_DMAC_SRCINC_16)
#define CONF_DMAC_SRC_STRIDE_16 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_16)
#define CONF_DMAC_DES_STRIDE_16 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_16
#define CONF_DMAC_SRC_STRIDE_16 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_16
#define CONF_DMAC_DES_STRIDE_16 0
#endif

// <e> 通道17设置
// <id>dmac_channel_17_设置
#ifndef CONF_DMAC_CHANNEL_17_SETTINGS
#define CONF_DMAC_CHANNEL_17_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_17
#ifndef CONF_DMAC_BURSTSIZE_17
#define CONF_DMAC_BURSTSIZE_17 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_17
#ifndef CONF_DMAC_CHUNKSIZE_17
#define CONF_DMAC_CHUNKSIZE_17 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_17
#ifndef CONF_DMAC_BEATSIZE_17
#define CONF_DMAC_BEATSIZE_17 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_17
#ifndef CONF_DMAC_SRC_INTERFACE_17
#define CONF_DMAC_SRC_INTERFACE_17 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_17
#ifndef CONF_DMAC_DES_INTERFACE_17
#define CONF_DMAC_DES_INTERFACE_17 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_17
#ifndef CONF_DMAC_SRCINC_17
#define CONF_DMAC_SRCINC_17 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_17
#ifndef CONF_DMAC_DSTINC_17
#define CONF_DMAC_DSTINC_17 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_17
#ifndef CONF_DMAC_TRANS_TYPE_17
#define CONF_DMAC_TRANS_TYPE_17 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// ＜id＞dmac_trifsrc_17
#ifndef CONF_DMAC_TRIGSRC_17
#define CONF_DMAC_TRIGSRC_17 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_17 == 0
#define CONF_DMAC_TYPE_17 0
#define CONF_DMAC_DSYNC_17 0
#elif CONF_DMAC_TRANS_TYPE_17 == 1
#define CONF_DMAC_TYPE_17 1
#define CONF_DMAC_DSYNC_17 0
#elif CONF_DMAC_TRANS_TYPE_17 == 2
#define CONF_DMAC_TYPE_17 1
#define CONF_DMAC_DSYNC_17 1
#endif

#if CONF_DMAC_TRIGSRC_17 == 0xFF
#define CONF_DMAC_SWREQ_17 1
#else
#define CONF_DMAC_SWREQ_17 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_17_SETTINGS == 1 && CONF_DMAC_BEATSIZE_17 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_17) || (!CONF_DMAC_DSTINC_17)))
#if (!CONF_DMAC_SRCINC_17)
#define CONF_DMAC_SRC_STRIDE_17 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_17)
#define CONF_DMAC_DES_STRIDE_17 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_17
#define CONF_DMAC_SRC_STRIDE_17 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_17
#define CONF_DMAC_DES_STRIDE_17 0
#endif

// <e> 通道18设置
// ＜id＞dmac_channel_18_settings
#ifndef CONF_DMAC_CHANNEL_18_SETTINGS
#define CONF_DMAC_CHANNEL_18_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_18
#ifndef CONF_DMAC_BURSTSIZE_18
#define CONF_DMAC_BURSTSIZE_18 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_18
#ifndef CONF_DMAC_CHUNKSIZE_18
#define CONF_DMAC_CHUNKSIZE_18 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_18
#ifndef CONF_DMAC_BEATSIZE_18
#define CONF_DMAC_BEATSIZE_18 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_18
#ifndef CONF_DMAC_SRC_INTERFACE_18
#define CONF_DMAC_SRC_INTERFACE_18 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_18
#ifndef CONF_DMAC_DES_INTERFACE_18
#define CONF_DMAC_DES_INTERFACE_18 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_18
#ifndef CONF_DMAC_SRCINC_18
#define CONF_DMAC_SRCINC_18 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_18
#ifndef CONF_DMAC_DSTINC_18
#define CONF_DMAC_DSTINC_18 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_18
#ifndef CONF_DMAC_TRANS_TYPE_18
#define CONF_DMAC_TRANS_TYPE_18 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// ＜id＞dmac_trifsrc_18
#ifndef CONF_DMAC_TRIGSRC_18
#define CONF_DMAC_TRIGSRC_18 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_18 == 0
#define CONF_DMAC_TYPE_18 0
#define CONF_DMAC_DSYNC_18 0
#elif CONF_DMAC_TRANS_TYPE_18 == 1
#define CONF_DMAC_TYPE_18 1
#define CONF_DMAC_DSYNC_18 0
#elif CONF_DMAC_TRANS_TYPE_18 == 2
#define CONF_DMAC_TYPE_18 1
#define CONF_DMAC_DSYNC_18 1
#endif

#if CONF_DMAC_TRIGSRC_18 == 0xFF
#define CONF_DMAC_SWREQ_18 1
#else
#define CONF_DMAC_SWREQ_18 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_18_SETTINGS == 1 && CONF_DMAC_BEATSIZE_18 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_18) || (!CONF_DMAC_DSTINC_18)))
#if (!CONF_DMAC_SRCINC_18)
#define CONF_DMAC_SRC_STRIDE_18 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_18)
#define CONF_DMAC_DES_STRIDE_18 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_18
#define CONF_DMAC_SRC_STRIDE_18 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_18
#define CONF_DMAC_DES_STRIDE_18 0
#endif

// <e> 通道19设置
// <id>dmac_channel_19_设置
#ifndef CONF_DMAC_CHANNEL_19_SETTINGS
#define CONF_DMAC_CHANNEL_19_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_19
#ifndef CONF_DMAC_BURSTSIZE_19
#define CONF_DMAC_BURSTSIZE_19 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_19
#ifndef CONF_DMAC_CHUNKSIZE_19
#define CONF_DMAC_CHUNKSIZE_19 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_19
#ifndef CONF_DMAC_BEATSIZE_19
#define CONF_DMAC_BEATSIZE_19 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_19
#ifndef CONF_DMAC_SRC_INTERFACE_19
#define CONF_DMAC_SRC_INTERFACE_19 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_19
#ifndef CONF_DMAC_DES_INTERFACE_19
#define CONF_DMAC_DES_INTERFACE_19 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_19
#ifndef CONF_DMAC_SRCINC_19
#define CONF_DMAC_SRCINC_19 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// Dmc_dstinc_19
#ifndef CONF_DMAC_DSTINC_19
#define CONF_DMAC_DSTINC_19 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_19
#ifndef CONF_DMAC_TRANS_TYPE_19
#define CONF_DMAC_TRANS_TYPE_19 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_19
#ifndef CONF_DMAC_TRIGSRC_19
#define CONF_DMAC_TRIGSRC_19 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_19 == 0
#define CONF_DMAC_TYPE_19 0
#define CONF_DMAC_DSYNC_19 0
#elif CONF_DMAC_TRANS_TYPE_19 == 1
#define CONF_DMAC_TYPE_19 1
#define CONF_DMAC_DSYNC_19 0
#elif CONF_DMAC_TRANS_TYPE_19 == 2
#define CONF_DMAC_TYPE_19 1
#define CONF_DMAC_DSYNC_19 1
#endif

#if CONF_DMAC_TRIGSRC_19 == 0xFF
#define CONF_DMAC_SWREQ_19 1
#else
#define CONF_DMAC_SWREQ_19 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_19_SETTINGS == 1 && CONF_DMAC_BEATSIZE_19 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_19) || (!CONF_DMAC_DSTINC_19)))
#if (!CONF_DMAC_SRCINC_19)
#define CONF_DMAC_SRC_STRIDE_19 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_19)
#define CONF_DMAC_DES_STRIDE_19 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_19
#define CONF_DMAC_SRC_STRIDE_19 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_19
#define CONF_DMAC_DES_STRIDE_19 0
#endif

// <e> 通道20设置
// ＜id＞dmac_channel_20_settings
#ifndef CONF_DMAC_CHANNEL_20_SETTINGS
#define CONF_DMAC_CHANNEL_20_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_20
#ifndef CONF_DMAC_BURSTSIZE_20
#define CONF_DMAC_BURSTSIZE_20 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_20
#ifndef CONF_DMAC_CHUNKSIZE_20
#define CONF_DMAC_CHUNKSIZE_20 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_20
#ifndef CONF_DMAC_BEATSIZE_20
#define CONF_DMAC_BEATSIZE_20 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_20
#ifndef CONF_DMAC_SRC_INTERFACE_20
#define CONF_DMAC_SRC_INTERFACE_20 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_20
#ifndef CONF_DMAC_DES_INTERFACE_20
#define CONF_DMAC_DES_INTERFACE_20 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_20
#ifndef CONF_DMAC_SRCINC_20
#define CONF_DMAC_SRCINC_20 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_20
#ifndef CONF_DMAC_DSTINC_20
#define CONF_DMAC_DSTINC_20 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// ＜id＞dma_trans_type_20
#ifndef CONF_DMAC_TRANS_TYPE_20
#define CONF_DMAC_TRANS_TYPE_20 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_20
#ifndef CONF_DMAC_TRIGSRC_20
#define CONF_DMAC_TRIGSRC_20 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_20 == 0
#define CONF_DMAC_TYPE_20 0
#define CONF_DMAC_DSYNC_20 0
#elif CONF_DMAC_TRANS_TYPE_20 == 1
#define CONF_DMAC_TYPE_20 1
#define CONF_DMAC_DSYNC_20 0
#elif CONF_DMAC_TRANS_TYPE_20 == 2
#define CONF_DMAC_TYPE_20 1
#define CONF_DMAC_DSYNC_20 1
#endif

#if CONF_DMAC_TRIGSRC_20 == 0xFF
#define CONF_DMAC_SWREQ_20 1
#else
#define CONF_DMAC_SWREQ_20 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_20_SETTINGS == 1 && CONF_DMAC_BEATSIZE_20 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_20) || (!CONF_DMAC_DSTINC_20)))
#if (!CONF_DMAC_SRCINC_20)
#define CONF_DMAC_SRC_STRIDE_20 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_20)
#define CONF_DMAC_DES_STRIDE_20 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_20
#define CONF_DMAC_SRC_STRIDE_20 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_20
#define CONF_DMAC_DES_STRIDE_20 0
#endif

// <e> 通道21设置
// <id>dmac_channel_21_settings
#ifndef CONF_DMAC_CHANNEL_21_SETTINGS
#define CONF_DMAC_CHANNEL_21_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_21
#ifndef CONF_DMAC_BURSTSIZE_21
#define CONF_DMAC_BURSTSIZE_21 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_21
#ifndef CONF_DMAC_CHUNKSIZE_21
#define CONF_DMAC_CHUNKSIZE_21 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_21
#ifndef CONF_DMAC_BEATSIZE_21
#define CONF_DMAC_BEATSIZE_21 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_21
#ifndef CONF_DMAC_SRC_INTERFACE_21
#define CONF_DMAC_SRC_INTERFACE_21 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_21
#ifndef CONF_DMAC_DES_INTERFACE_21
#define CONF_DMAC_DES_INTERFACE_21 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_21
#ifndef CONF_DMAC_SRCINC_21
#define CONF_DMAC_SRCINC_21 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_21
#ifndef CONF_DMAC_DSTINC_21
#define CONF_DMAC_DSTINC_21 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// ＜id＞dma_trans_type_21
#ifndef CONF_DMAC_TRANS_TYPE_21
#define CONF_DMAC_TRANS_TYPE_21 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_21
#ifndef CONF_DMAC_TRIGSRC_21
#define CONF_DMAC_TRIGSRC_21 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_21 == 0
#define CONF_DMAC_TYPE_21 0
#define CONF_DMAC_DSYNC_21 0
#elif CONF_DMAC_TRANS_TYPE_21 == 1
#define CONF_DMAC_TYPE_21 1
#define CONF_DMAC_DSYNC_21 0
#elif CONF_DMAC_TRANS_TYPE_21 == 2
#define CONF_DMAC_TYPE_21 1
#define CONF_DMAC_DSYNC_21 1
#endif

#if CONF_DMAC_TRIGSRC_21 == 0xFF
#define CONF_DMAC_SWREQ_21 1
#else
#define CONF_DMAC_SWREQ_21 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_21_SETTINGS == 1 && CONF_DMAC_BEATSIZE_21 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_21) || (!CONF_DMAC_DSTINC_21)))
#if (!CONF_DMAC_SRCINC_21)
#define CONF_DMAC_SRC_STRIDE_21 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_21)
#define CONF_DMAC_DES_STRIDE_21 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_21
#define CONF_DMAC_SRC_STRIDE_21 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_21
#define CONF_DMAC_DES_STRIDE_21 0
#endif

// <e> 通道22设置
// <id>dmac_channel_22_settings
#ifndef CONF_DMAC_CHANNEL_22_SETTINGS
#define CONF_DMAC_CHANNEL_22_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_22
#ifndef CONF_DMAC_BURSTSIZE_22
#define CONF_DMAC_BURSTSIZE_22 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_22
#ifndef CONF_DMAC_CHUNKSIZE_22
#define CONF_DMAC_CHUNKSIZE_22 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_22
#ifndef CONF_DMAC_BEATSIZE_22
#define CONF_DMAC_BEATSIZE_22 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_22
#ifndef CONF_DMAC_SRC_INTERFACE_22
#define CONF_DMAC_SRC_INTERFACE_22 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_22
#ifndef CONF_DMAC_DES_INTERFACE_22
#define CONF_DMAC_DES_INTERFACE_22 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_22
#ifndef CONF_DMAC_SRCINC_22
#define CONF_DMAC_SRCINC_22 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_22
#ifndef CONF_DMAC_DSTINC_22
#define CONF_DMAC_DSTINC_22 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// ＜id＞dma_trans_type_22
#ifndef CONF_DMAC_TRANS_TYPE_22
#define CONF_DMAC_TRANS_TYPE_22 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// <id>dmac_trifsrc_22
#ifndef CONF_DMAC_TRIGSRC_22
#define CONF_DMAC_TRIGSRC_22 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_22 == 0
#define CONF_DMAC_TYPE_22 0
#define CONF_DMAC_DSYNC_22 0
#elif CONF_DMAC_TRANS_TYPE_22 == 1
#define CONF_DMAC_TYPE_22 1
#define CONF_DMAC_DSYNC_22 0
#elif CONF_DMAC_TRANS_TYPE_22 == 2
#define CONF_DMAC_TYPE_22 1
#define CONF_DMAC_DSYNC_22 1
#endif

#if CONF_DMAC_TRIGSRC_22 == 0xFF
#define CONF_DMAC_SWREQ_22 1
#else
#define CONF_DMAC_SWREQ_22 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_22_SETTINGS == 1 && CONF_DMAC_BEATSIZE_22 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_22) || (!CONF_DMAC_DSTINC_22)))
#if (!CONF_DMAC_SRCINC_22)
#define CONF_DMAC_SRC_STRIDE_22 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_22)
#define CONF_DMAC_DES_STRIDE_22 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_22
#define CONF_DMAC_SRC_STRIDE_22 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_22
#define CONF_DMAC_DES_STRIDE_22 0
#endif

// <e> 通道23设置
// <id>dmac_channel_23_settings
#ifndef CONF_DMAC_CHANNEL_23_SETTINGS
#define CONF_DMAC_CHANNEL_23_SETTINGS 0
#endif

// <o> 突发大小
// <0x0=>1突发大小
// <0x1=>4突发大小
// <0x2=>8突发大小
// <0x3=>16突发大小
// <i> 定义内存突发大小
// <id>dmac_burtsize_23
#ifndef CONF_DMAC_BURSTSIZE_23
#define CONF_DMAC_BURSTSIZE_23 0x0
#endif

// <o> 块大小（Chunk Size）
// <0x0=>1个数据已传输
// <0x1=>2个数据传输
// <0x2=>4个数据传输
// <0x3=>传输了8个数据
// <0x4=>传输了16个数据
// <i> 定义外围块大小
// <id>dmac_chunksize_23
#ifndef CONF_DMAC_CHUNKSIZE_23
#define CONF_DMAC_CHUNKSIZE_23 0x0
#endif

// <o> 节拍大小
// <0=>8位总线传输
// <1=>16位总线传输
// <2=>32位总线传输
// <i> 定义一个节拍的大小
// <id>dmac_beatsize_23
#ifndef CONF_DMAC_BEATSIZE_23
#define CONF_DMAC_BEATSIZE_23 0x0
#endif

// <o> 源接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1读取的数据
// <id>dma_src_interface_23
#ifndef CONF_DMAC_SRC_INTERFACE_23
#define CONF_DMAC_SRC_INTERFACE_23 0x0
#endif

// <o> 目标接口标识符
// <0x0=>AHB_IF0
// <0x1=>AHB_IF1
// <i> 定义通过系统总线接口0或1写入的数据
// <id>dma_des_interface_23
#ifndef CONF_DMAC_DES_INTERFACE_23
#define CONF_DMAC_DES_INTERFACE_23 0x0
#endif

// <q> 源地址增量
// <i> 指示源地址是否按节拍大小递增
// <id>dmac_srcinc_23
#ifndef CONF_DMAC_SRCINC_23
#define CONF_DMAC_SRCINC_23 0
#endif

// <q> 目标地址增量
// <i> 指示目标地址是否按节拍大小递增
// <id>dmac_dstinc_23
#ifndef CONF_DMAC_DSTINC_23
#define CONF_DMAC_DSTINC_23 0
#endif

// <o> 传输类型
// <0x0=>内存到内存传输
// <0x1=>外设到内存传输
// <0x2=>内存到外围设备传输
// <i> 定义数据传输类型
// <id>dma_trans_type_23
#ifndef CONF_DMAC_TRANS_TYPE_23
#define CONF_DMAC_TRANS_TYPE_23 0x0
#endif

// <o> 触发器源
// <0xFF=>软件触发器
// <0x00=>HSMCI TX/RX触发器
// <0x01=>SPI0 TX触发器
// <0x02=>SPI0 RX触发器
// <0x03=>SPI1 TX触发器
// <0x04=>SPI1 RX触发器
// <0x05=>QSPI TX触发器
// <0x06=>QSPI RX触发器
// <0x07=>USART0 TX触发器
// <0x08=>USART0 RX触发器
// <0x09=>USART1 TX触发器
// <0x0A=>USART1 RX触发器
// <0x0B=>USART2 TX触发器
// ＜0x0C＝＞USART2 RX触发器
// <0x0D=>PWM0 TX触发器
// ＜0x0E＝＞TWIHS0 TX触发器
// ＜0x0F＝＞TWIHS0 RX触发器
// <0x10=>TWIHS1 TX触发器
// <0x11=>TWIHS1 RX触发器
// <0x12=>TWIH2 TX触发器
// <0x13=>TWIH2 RX触发器
// <0x14=>UART0 TX触发器
// <0x15=>UART0 RX触发器
// <0x16=>UART1 TX触发器
// <0x17=>UART1 RX触发器
// <0x18=>UART2 TX触发器
// <0x19=>UART2 RX触发器
// <0x1A=>UART3 TX触发器
// <0x1B=>UART3 RX触发器
// <0x1C=>UART4 TX触发器
// <0x1D=>UART4 RX触发器
// <0x1E=>DACC TX触发器
// <0x20=>SSC TX触发器
// <0x21=>SSC RX触发器
// <0x22=>PIOA RX触发器
// <0x23=>AFEC0 RX触发器
// <0x24=>AFEC1 RX触发器
// <0x25=>AES TX触发器
// <0x26=>AES RX触发器
// <0x27=>PWM1 TX触发器
// <0x28=>TC0 RX触发器
// <0x29=>TC3 RX触发器
// <0x2A=>TC6 RX触发器
// <0x2B=>TC9 RX触发器
// <0x2C=>I2SC0 TX左触发器
// <0x2D=>I2SC0 RX左触发器
// <0x2E=>I2SC1 TX左触发器
// <0x2F=>I2SC1 RX左触发器
// <0x30=>I2SC0 TX右触发器
// <0x31=>I2SC0 RX右触发器
// <0x32=>I2SC1 TX右触发器
// <0x33=>I2SC1 RX右触发器
// <i> 定义DMA触发源
// ＜id＞dmac_trifsrc_23
#ifndef CONF_DMAC_TRIGSRC_23
#define CONF_DMAC_TRIGSRC_23 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_23 == 0
#define CONF_DMAC_TYPE_23 0
#define CONF_DMAC_DSYNC_23 0
#elif CONF_DMAC_TRANS_TYPE_23 == 1
#define CONF_DMAC_TYPE_23 1
#define CONF_DMAC_DSYNC_23 0
#elif CONF_DMAC_TRANS_TYPE_23 == 2
#define CONF_DMAC_TYPE_23 1
#define CONF_DMAC_DSYNC_23 1
#endif

#if CONF_DMAC_TRIGSRC_23 == 0xFF
#define CONF_DMAC_SWREQ_23 1
#else
#define CONF_DMAC_SWREQ_23 0
#endif

/* 错误：如果XDMA用于以固定源地址或固定目标地址模式传输8位或16位数据，则源地址和目标地址将增加8位或6位。解决方法：用户可以通过将源寻址模式设置为使用微块和数据跨步来解决问题，微块跨步设置为0，数据跨步设置设置为-1。
 */
#if (CONF_DMAC_CHANNEL_23_SETTINGS == 1 && CONF_DMAC_BEATSIZE_23 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_23) || (!CONF_DMAC_DSTINC_23)))
#if (!CONF_DMAC_SRCINC_23)
#define CONF_DMAC_SRC_STRIDE_23 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_23)
#define CONF_DMAC_DES_STRIDE_23 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_23
#define CONF_DMAC_SRC_STRIDE_23 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_23
#define CONF_DMAC_DES_STRIDE_23 0
#endif

// </e>

// <<<配置节末尾>>

#endif // HPL_XDMAC_CONFIG_H

