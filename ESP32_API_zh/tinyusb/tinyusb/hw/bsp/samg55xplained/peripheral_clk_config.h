/* 自动生成的配置文件peripheral_clk_config。小时*/
#ifndef PERIPHERAL_CLK_CONFIG_H
#define PERIPHERAL_CLK_CONFIG_H

// <<<在上下文菜单中使用配置向导>>

/**
 * \def CONF_HCLK_FREQUENCY\brief HCLK的时钟频率
 */
#ifndef CONF_HCLK_FREQUENCY
#define CONF_HCLK_FREQUENCY 8000000
#endif

/**
 * \def CONF_FCLK_FREQUENCY\简要FCLK的时钟频率
 */
#ifndef CONF_FCLK_FREQUENCY
#define CONF_FCLK_FREQUENCY 8000000
#endif

/**
 * \def CONF_CPU_FREQUENCY\简述CPU的时钟频率
 */
#ifndef CONF_CPU_FREQUENCY
#define CONF_CPU_FREQUENCY 8000000
#endif

/**
 * \def CONF_SLCK_FREQUENCY\短暂慢时钟频率
 */
#define CONF_SLCK_FREQUENCY 32768

/**
 * \def CONF_MCK_FREQUENCY\简要主时钟频率
 */
#define CONF_MCK_FREQUENCY 8000000

// <o> USB时钟源
// <0=>USB时钟控制器（USB_48M）
// <id>usb_clock_source
// <i> 选择USB的时钟源。
#ifndef CONF_UDP_SRC
#define CONF_UDP_SRC 0
#endif

/**
 * \def CONF_UDP_FREQUENCY\brief UDP的时钟频率
 */
#ifndef CONF_UDP_FREQUENCY
#define CONF_UDP_FREQUENCY 48005120
#endif

// <h> FLEXCOM时钟设置
// <o> FLEXCOM时钟源
// <0=>主时钟（MCK）
// <1=> MCK / 8
// <2=>可编程时钟控制器6（PMC_PCK6）
// <2=>可编程时钟控制器7（PMC_PCK7）
// <3=>外部时钟
// <i> 这定义了FLEXCOM的时钟源，PCK6用于FLEXCOM0/1/2/3，PCK7用于FLEXCOM 4/5/6/7
// <id>flexcom_clock_source
#ifndef CONF_FLEXCOM7_CK_SRC
#define CONF_FLEXCOM7_CK_SRC 0
#endif

// <o> SCK上的FLEXCOM外部时钟输入<1-4294967295>
// <i> 在SCK上输入外部时钟频率
// <id>flexcom_clock_freq
#ifndef CONF_FLEXCOM7_SCK_FREQ
#define CONF_FLEXCOM7_SCK_FREQ 10000000
#endif

#ifndef CONF_FLEXCOM7_FREQUENCY
#define CONF_FLEXCOM7_FREQUENCY 8000000
#endif

// <<<配置节末尾>>

#endif // PERIPHERAL_CLK_CONFIG_H

