/* 自动生成的配置文件peripheral_clk_config。小时*/
#ifndef PERIPHERAL_CLK_CONFIG_H
#define PERIPHERAL_CLK_CONFIG_H

// <<<在上下文菜单中使用配置向导>>

/**
 * \def CONF_HCLK_FREQUENCY\brief HCLK的时钟频率
 */
#ifndef CONF_HCLK_FREQUENCY
#define CONF_HCLK_FREQUENCY 300000000
#endif

/**
 * \def CONF_FCLK_FREQUENCY\简要FCLK的时钟频率
 */
#ifndef CONF_FCLK_FREQUENCY
#define CONF_FCLK_FREQUENCY 300000000
#endif

/**
 * \def CONF_CPU_FREQUENCY\简述CPU的时钟频率
 */
#ifndef CONF_CPU_FREQUENCY
#define CONF_CPU_FREQUENCY 300000000
#endif

/**
 * \def CONF_SLCK_FREQUENCY\短暂慢时钟频率
 */
#define CONF_SLCK_FREQUENCY 0

/**
 * \def CONF_MCK_FREQUENCY\简要主时钟频率
 */
#define CONF_MCK_FREQUENCY 150000000

/**
 * \def CONF_PCK6_FREQUENCY\简要可编程时钟控制器6频率
 */
#define CONF_PCK6_FREQUENCY 1714285

// <h> USART时钟设置
// <o> USART时钟源

// <0=>主时钟（MCK）
// USART的<1=>MCK/8
// <2=>可编程时钟控制器4（PMC_PCK4）
// <3=>外部时钟
// <i> 这定义了USART的时钟源
// <id>使用rt_clock_source
#ifndef CONF_USART1_CK_SRC
#define CONF_USART1_CK_SRC 0
#endif

// <o> SCK上的USART外部时钟输入<1-4294967295>
// <i> 在SCK上输入外部时钟频率
// <id>使用rt_clock_freq
#ifndef CONF_USART1_SCK_FREQ
#define CONF_USART1_SCK_FREQ 10000000
#endif

// </h>

/**
 * \def USART FREQUENCY\简要介绍USART的时钟频率
 */
#ifndef CONF_USART1_FREQUENCY
#define CONF_USART1_FREQUENCY 150000000
#endif

#ifndef CONF_SRC_USB_480M
#define CONF_SRC_USB_480M 0
#endif

#ifndef CONF_SRC_USB_48M
#define CONF_SRC_USB_48M 1
#endif

// <y> USB全速/低速时钟
// <CONF_SRC_USB_48M“>USB时钟控制器（USB_48M）
// <id>usb_fsls_clock_source
// <i> 48MHz时钟源，用于低速和全速。
// <i> 当主机驱动程序支持低速时，它必须可用。
// <i> 选择低功率模式时必须可用。
#ifndef CONF_USBHS_FSLS_SRC
#define CONF_USBHS_FSLS_SRC CONF_SRC_USB_48M
#endif

// <y> USB时钟源（正常/低功耗模式选择）
// <CONF_SRC_USB_480M“>USB高速时钟（USB_480M）
// <CONF_SRC_USB_48M“>USB时钟控制器（USB_48M）
// <id>usb_clock_source
// <i> 选择USB的时钟源。
// <i> 在正常模式下，使用“USB高速时钟（USB_480M）”。
// <i> 在低功耗模式下，使用“USB时钟控制器（USB_48M）”。
#ifndef CONF_USBHS_SRC
#define CONF_USBHS_SRC CONF_SRC_USB_480M
#endif

/**
 * \def CONF_USBHS_FSLS_FREQUENCY\brief USBHS的全速/低速时钟源频率
 */
#ifndef CONF_USBHS_FSLS_FREQUENCY
#define CONF_USBHS_FSLS_FREQUENCY 48000000
#endif

/**
 * \def CONF_USBHS_FREQUENCY\ brief USBHS选择的时钟源频率
 */
#ifndef CONF_USBHS_FREQUENCY
#define CONF_USBHS_FREQUENCY 480000000
#endif

// <<<配置节末尾>>

#endif // PERIPHERAL_CLK_CONFIG_H

