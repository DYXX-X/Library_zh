/* 自动生成的配置文件hpl_pmc_config。小时*/
#ifndef HPL_PMC_CONFIG_H
#define HPL_PMC_CONFIG_H

// <<<在上下文菜单中使用配置向导>>

#include <peripheral_clk_config.h>

#define CLK_SRC_OPTION_OSC32K 0
#define CLK_SRC_OPTION_XOSC32K 1
#define CLK_SRC_OPTION_OSC12M 2
#define CLK_SRC_OPTION_XOSC20M 3

#define CLK_SRC_OPTION_SLCK 0
#define CLK_SRC_OPTION_MAINCK 1
#define CLK_SRC_OPTION_PLLACK 2
#define CLK_SRC_OPTION_UPLLCKDIV 3
#define CLK_SRC_OPTION_MCK 4

#define CLK_SRC_OPTION_UPLLCK 3

#define CONF_RC_4M 0
#define CONF_RC_8M 1
#define CONF_RC_12M 2

#define CONF_XOSC32K_NO_BYPASS 0
#define CONF_XOSC32K_BYPASS 1

#define CONF_XOSC20M_NO_BYPASS 0
#define CONF_XOSC20M_BYPASS 1

// <e> Clock_SLCK配置
// <i> 指示是否启用SLCK配置
// <id>启用_clk_gen_slck
#ifndef CONF_CLK_SLCK_CONFIG
#define CONF_CLK_SLCK_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器SLCK源

// <CLK_SRC_OPTION_OSC32K“>32kHz高精度内部振荡器（OSC32K）

// <CLK_SRC_OPTION_XOSC32K“>32kHz外部晶体振荡器（XOSC32K）

// <i> 这定义了SLCK的时钟源
// ＜id＞clk_gen_slck_soscillator
#ifndef CONF_CLK_GEN_SLCK_SRC
#define CONF_CLK_GEN_SLCK_SRC CLK_SRC_OPTION_OSC32K
#endif

// <q> 启用Clock_SLCK
// <i> 指示SLCK是启用还是禁用
// ＜id＞clk_gen_slck_arch_enable
#ifndef CONF_CLK_SLCK_ENABLE
#define CONF_CLK_SLCK_ENABLE 1
#endif

// </h>

// <小时>

// </h>
// </e>//<e>时钟_MAINCK配置
// <i> 指示MAINCK配置是否已启用
// <id>启用_clk_gen_manck
#ifndef CONF_CLK_MAINCK_CONFIG
#define CONF_CLK_MAINCK_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器MAINCK源

// <CLK_SRC_OPTION_OSC12M“>嵌入式4/8/12MHz RC振荡器（OSC12M）

// <CLK_SRC_OPTION_XOSC20M“>外部3-20MHz振荡器（XOSC20M）

// <i> 这定义了MAINCK的时钟源
// ＜id＞clk_gen_manck_soscillator
#ifndef CONF_CLK_GEN_MAINCK_SRC
#define CONF_CLK_GEN_MAINCK_SRC CLK_SRC_OPTION_XOSC20M
#endif

// <q> 启用时钟_MAINCK
// <i> 指示MAINCK是启用还是禁用
// ＜id＞clk_gen_manck_arch_enable
#ifndef CONF_CLK_MAINCK_ENABLE
#define CONF_CLK_MAINCK_ENABLE 1
#endif

// <q> 启用主时钟故障检测
// <i> 指示主时钟故障检测是启用还是禁用。
// <i> 必须选择4/8/12MHz RC振荡器作为MAINCK的源。
// ＜id＞clk_gen_cfden_enable
#ifndef CONF_CLK_CFDEN_ENABLE
#define CONF_CLK_CFDEN_ENABLE 0
#endif

// </h>

// <小时>

// </h>
// </e>//<e>时钟_MCKR配置
// <i> 指示是否启用MCKR配置
// <id>启用_clk_gen_mckr
#ifndef CONF_CLK_MCKR_CONFIG
#define CONF_CLK_MCKR_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器MCKR源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <CLK_SRC_OPTION_MAINCK“>主时钟（MAINCK）

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_UPLLCKDIV“>带分频器的UDPLL（MCKR UPLLDIV2）

// <i> 这定义了MCKR的时钟源
// <id>clk_gen_mckr_振荡器
#ifndef CONF_CLK_GEN_MCKR_SRC
#define CONF_CLK_GEN_MCKR_SRC CLK_SRC_OPTION_PLLACK
#endif

// <q> 启用时钟_MCKR
// <i> 指示MCKR是启用还是禁用
// ＜id＞clk_gen_mckr_arch_enable
#ifndef CONF_CLK_MCKR_ENABLE
#define CONF_CLK_MCKR_ENABLE 1
#endif

// </h>

// <小时>

// <o> 主时钟预分频器
// <0=> 1
// <1=> 2
// <2=> 4
// <3=> 8
// <4=> 16
// <5=> 32
// <6=> 64
// <7=> 3
// <i> 选择时钟预分频器。
// ＜id＞mckr_presc
#ifndef CONF_MCKR_PRESC
#define CONF_MCKR_PRESC 0
#endif

// </h>
// </e>//<e>时钟_时钟配置
// <i> 指示是否启用MCK配置
// <id>启用_clk_gen_mck
#ifndef CONF_CLK_MCK_CONFIG
#define CONF_CLK_MCK_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器MCK源

// <CLK_SRC_OPTION_MCKR“>主时钟控制器（PMC_MCKR）

// <i> 这定义了MCK的时钟源
// <id>clk_gen_mck_oscillator（时钟振荡器）
#ifndef CONF_CLK_GEN_MCK_SRC
#define CONF_CLK_GEN_MCK_SRC CLK_SRC_OPTION_MCKR
#endif

// </h>

// <小时>

//<o> 主时钟控制器分频器MCK分频器
// <0=> 1
// <1=> 2
// <3=> 3
// <2=> 4
// <i> 选择主时钟分频器。
// ＜id＞mck_div
#ifndef CONF_MCK_DIV
#define CONF_MCK_DIV 1
#endif

// </h>
// </e>//<e>时钟_系统配置
// <i> 指示是否启用SYSTICK配置
// <id>启用_clk_gen_systick
#ifndef CONF_CLK_SYSTICK_CONFIG
#define CONF_CLK_SYSTICK_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器SYSTICK源

// <CLK_SRC_OPTION_MCKR“>主时钟控制器（PMC_MCKR）

// <i> 这定义了SYSTICK的时钟源
// <id>clk_gen_systick_oscillator
#ifndef CONF_CLK_GEN_SYSTICK_SRC
#define CONF_CLK_GEN_SYSTICK_SRC CLK_SRC_OPTION_MCKR
#endif

// </h>

// <小时>

// <o> Systick时钟分频器
// <8=> 8
// <i> 选择系统时钟分频器
// <id>系统锁定目录
#ifndef CONF_SYSTICK_DIV
#define CONF_SYSTICK_DIV 8
#endif

// </h>
// </e>//<e>时钟_FCLK配置
// <i> 指示FCLK配置是否已启用
// <id>启用_clk_gen_fclk
#ifndef CONF_CLK_FCLK_CONFIG
#define CONF_CLK_FCLK_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器FCLK源

// <CLK_SRC_OPTION_MCKR“>主时钟控制器（PMC_MCKR）

// <i> 这定义了FCLK的时钟源
// ＜id＞clk_gen_fclk_soscillator
#ifndef CONF_CLK_GEN_FCLK_SRC
#define CONF_CLK_GEN_FCLK_SRC CLK_SRC_OPTION_MCKR
#endif

// </h>

// <小时>

// </h>
// </e>//<e>时钟_GCLK0配置
// <i> 指示GCLK0配置是否已启用
// <id>启用_clk_gen_gclk0
#ifndef CONF_CLK_GCLK0_CONFIG
#define CONF_CLK_GCLK0_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器GCLK0源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <CLK_SRC_OPTION_MAINCK“>主时钟（MAINCK）

// <CLK_SRC_OPTION_UPLLCK“>USB 480M时钟（UPLLCK）

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_MCK“>主时钟（MCK）

// <i> 这定义了GCLK0的时钟源
// ＜id＞clk_gen_gclk0_soscillator
#ifndef CONF_CLK_GEN_GCLK0_SRC
#define CONF_CLK_GEN_GCLK0_SRC CLK_SRC_OPTION_MCK
#endif

// <q> 启用时钟_GCLK0
// <i> 指示GCLK0是启用还是禁用
// ＜id＞clk_gen_gclk0_arch_enable
#ifndef CONF_CLK_GCLK0_ENABLE
#define CONF_CLK_GCLK0_ENABLE 1
#endif

// </h>

// <小时>
// <q> 启用GCLK0 GCLKEN
// <i> 指示GCLK0 GCLKEN是启用还是禁用
// ＜id＞gclk0_gclken_enable
#ifndef CONF_GCLK0_GCLKEN_ENABLE
#define CONF_GCLK0_GCLKEN_ENABLE 0
#endif

// <o> 通用时钟GCLK0分频器<1-256>
// <i> 选择时钟分频器（分频器=GCLKDIV+1）。
// ＜id＞gclk0_div
#ifndef CONF_GCLK0_DIV
#define CONF_GCLK0_DIV 2
#endif

// </h>
// </e>//<e>时钟_GCLK1配置
// <i> 指示GCLK1配置是否已启用
// <id>启用_clk_gen_gclk1
#ifndef CONF_CLK_GCLK1_CONFIG
#define CONF_CLK_GCLK1_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器GCLK1源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <CLK_SRC_OPTION_MAINCK“>主时钟（MAINCK）

// <CLK_SRC_OPTION_UPLLCK“>USB 480M时钟（UPLLCK）

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_MCK“>主时钟（MCK）

// <i> 这定义了GCLK1的时钟源
// <id>clk_gen_gclk1_oscillator
#ifndef CONF_CLK_GEN_GCLK1_SRC
#define CONF_CLK_GEN_GCLK1_SRC CLK_SRC_OPTION_PLLACK
#endif

// <q> 启用时钟_GCLK1
// <i> 指示GCLK1是启用还是禁用
// ＜id＞clk_gen_gclk1_arch_enable
#ifndef CONF_CLK_GCLK1_ENABLE
#define CONF_CLK_GCLK1_ENABLE 1
#endif

// </h>

// <小时>
// <q> 启用GCLK1 GCLKEN
// <i> 指示GCLK1 GCLKEN是启用还是禁用
// ＜id＞gclk1_gclken_enable
#ifndef CONF_GCLK1_GCLKEN_ENABLE
#define CONF_GCLK1_GCLKEN_ENABLE 0
#endif

// <o> 通用时钟GCLK1分频器<1-256>
// <i> 选择时钟分频器（分频器=GCLKDIV+1）。
// ＜id＞gclk1_div
#ifndef CONF_GCLK1_DIV
#define CONF_GCLK1_DIV 3
#endif

// </h>
// </e>//<e>时钟_PCK0配置
// <i> 指示PCK0配置是否已启用
// <id>启用_clk_gen_pck0
#ifndef CONF_CLK_PCK0_CONFIG
#define CONF_CLK_PCK0_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器PCK0源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <CLK_SRC_OPTION_MAINCK“>主时钟（MAINCK）

// <CLK_SRC_OPTION_UPLLCKDIV“>带分频器的UDPLL（MCKR UPLLDIV2）

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_MCK“>主时钟（MCK）

// <i> 这定义了PCK0的时钟源
// ＜id＞clk_gen_pck0_soscillator
#ifndef CONF_CLK_GEN_PCK0_SRC
#define CONF_CLK_GEN_PCK0_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> 启用时钟_PCK0
// <i> 指示PCK0是启用还是禁用
// ＜id＞clk_gen_pck0_arch_enable
#ifndef CONF_CLK_PCK0_ENABLE
#define CONF_CLK_PCK0_ENABLE 0
#endif

// </h>

// <小时>

// <o> 可编程时钟控制器预分频器<1-256>
// <i> 选择时钟预分频器（预分频器=PRESC+1）。
// ＜id＞pck0_precs
#ifndef CONF_PCK0_PRESC
#define CONF_PCK0_PRESC 1
#endif

// </h>
// </e>//<e>时钟_PCK1配置
// <i> 指示PCK1配置是否启用
// <id>启用_clk_gen_pck1
#ifndef CONF_CLK_PCK1_CONFIG
#define CONF_CLK_PCK1_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器PCK1源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <CLK_SRC_OPTION_MAINCK“>主时钟（MAINCK）

// <CLK_SRC_OPTION_UPLLCKDIV“>带分频器的UDPLL（MCKR UPLLDIV2）

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_MCK“>主时钟（MCK）

// <i> 这定义了PCK1的时钟源
// <id>clk_gen_pck1_振荡器
#ifndef CONF_CLK_GEN_PCK1_SRC
#define CONF_CLK_GEN_PCK1_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> 启用时钟_PCK1
// <i> 指示PCK1是启用还是禁用
// ＜id＞clk_gen_pck1_arch_enable
#ifndef CONF_CLK_PCK1_ENABLE
#define CONF_CLK_PCK1_ENABLE 0
#endif

// </h>

// <小时>

// <o> 可编程时钟控制器预分频器<1-256>
// <i> 选择时钟预分频器（预分频器=PRESC+1）。
// <id>pck1_presc
#ifndef CONF_PCK1_PRESC
#define CONF_PCK1_PRESC 2
#endif

// </h>
// </e>//<e>时钟_PCK2配置
// <i> 指示PCK2配置是否已启用
// <id>启用_clk_gen_pck2
#ifndef CONF_CLK_PCK2_CONFIG
#define CONF_CLK_PCK2_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器PCK2源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <CLK_SRC_OPTION_MAINCK“>主时钟（MAINCK）

// <CLK_SRC_OPTION_UPLLCKDIV“>带分频器的UDPLL（MCKR UPLLDIV2）

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_MCK“>主时钟（MCK）

// <i> 这定义了PCK2的时钟源
// <id>clk_gen_pck2_振荡器
#ifndef CONF_CLK_GEN_PCK2_SRC
#define CONF_CLK_GEN_PCK2_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> 启用时钟_PCK2
// <i> 指示PCK2是启用还是禁用
// ＜id＞clk_gen_pck2_arch_enable
#ifndef CONF_CLK_PCK2_ENABLE
#define CONF_CLK_PCK2_ENABLE 0
#endif

// </h>

// <小时>

// <o> 可编程时钟控制器预分频器<1-256>
// <i> 选择时钟预分频器（预分频器=PRESC+1）。
// ＜id＞pck2_precs
#ifndef CONF_PCK2_PRESC
#define CONF_PCK2_PRESC 3
#endif

// </h>
// </e>//<e>时钟_PCK3配置
// <i> 指示PCK3配置是否已启用
// <id>启用_clk_gen_pck3
#ifndef CONF_CLK_PCK3_CONFIG
#define CONF_CLK_PCK3_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器PCK3源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <CLK_SRC_OPTION_MAINCK“>主时钟（MAINCK）

// <CLK_SRC_OPTION_UPLLCKDIV“>带分频器的UDPLL（MCKR UPLLDIV2）

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_MCK“>主时钟（MCK）

// <i> 这定义了PCK3的时钟源
// <id>clk_gen_pck3_振荡器
#ifndef CONF_CLK_GEN_PCK3_SRC
#define CONF_CLK_GEN_PCK3_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> 启用时钟_PCK3
// <i> 指示PCK3是启用还是禁用
// ＜id＞clk_gen_pck3_arch_enable
#ifndef CONF_CLK_PCK3_ENABLE
#define CONF_CLK_PCK3_ENABLE 0
#endif

// </h>

// <小时>

// <o> 可编程时钟控制器预分频器<1-256>
// <i> 选择时钟预分频器（预分频器=PRESC+1）。
// <id>pck3_prec
#ifndef CONF_PCK3_PRESC
#define CONF_PCK3_PRESC 4
#endif

// </h>
// </e>//<e>时钟_PCK4配置
// <i> 指示PCK4配置是否启用
// <id>启用_clk_gen_pck4
#ifndef CONF_CLK_PCK4_CONFIG
#define CONF_CLK_PCK4_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器PCK4源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <CLK_SRC_OPTION_MAINCK“>主时钟（MAINCK）

// <CLK_SRC_OPTION_UPLLCKDIV“>带分频器的UDPLL（MCKR UPLLDIV2）

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_MCK“>主时钟（MCK）

// <i> 这定义了PCK4的时钟源
// <id>clk_gen_pck4_振荡器
#ifndef CONF_CLK_GEN_PCK4_SRC
#define CONF_CLK_GEN_PCK4_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> 启用时钟_PCK4
// <i> 指示PCK4是启用还是禁用
// ＜id＞clk_gen_pck4_arch_enable
#ifndef CONF_CLK_PCK4_ENABLE
#define CONF_CLK_PCK4_ENABLE 0
#endif

// </h>

// <小时>

// <o> 可编程时钟控制器预分频器<1-256>
// <i> 选择时钟预分频器（预分频器=PRESC+1）。
// <id>pck4_prec
#ifndef CONF_PCK4_PRESC
#define CONF_PCK4_PRESC 5
#endif

// </h>
// </e>//<e>时钟_PCK5配置
// <i> 指示PCK5配置是否已启用
// <id>启用_clk_gen_pck5
#ifndef CONF_CLK_PCK5_CONFIG
#define CONF_CLK_PCK5_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器PCK5源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <CLK_SRC_OPTION_MAINCK“>主时钟（MAINCK）

// <CLK_SRC_OPTION_UPLLCKDIV“>带分频器的UDPLL（MCKR UPLLDIV2）

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_MCK“>主时钟（MCK）

// <i> 这定义了PCK5的时钟源
// <id>clk_gen_pck5_振荡器
#ifndef CONF_CLK_GEN_PCK5_SRC
#define CONF_CLK_GEN_PCK5_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> 启用时钟_PCK5
// <i> 指示PCK5是启用还是禁用
// ＜id＞clk_gen_pck5_arch_enable
#ifndef CONF_CLK_PCK5_ENABLE
#define CONF_CLK_PCK5_ENABLE 0
#endif

// </h>

// <小时>

// <o> 可编程时钟控制器预分频器<1-256>
// <i> 选择时钟预分频器（预分频器=PRESC+1）。
// ＜id＞pck5_prec
#ifndef CONF_PCK5_PRESC
#define CONF_PCK5_PRESC 6
#endif

// </h>
// </e>//<e>时钟_PCK6配置
// <i> 指示PCK6配置是否已启用
// <id>启用_clk_gen_pck6
#ifndef CONF_CLK_PCK6_CONFIG
#define CONF_CLK_PCK6_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器PCK6源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <CLK_SRC_OPTION_MAINCK“>主时钟（MAINCK）

// <CLK_SRC_OPTION_UPLLCKDIV“>带分频器的UDPLL（MCKR UPLLDIV2）

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_MCK“>主时钟（MCK）

// <i> 这定义了PCK6的时钟源
// <id>clk_gen_pck6_振荡器
#ifndef CONF_CLK_GEN_PCK6_SRC
#define CONF_CLK_GEN_PCK6_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> 启用时钟_PCK6
// <i> 指示PCK6是启用还是禁用
// ＜id＞clk_gen_pck6_arch_enable
#ifndef CONF_CLK_PCK6_ENABLE
#define CONF_CLK_PCK6_ENABLE 0
#endif

// </h>

// <小时>

// <o> 可编程时钟控制器预分频器<1-256>
// <i> 选择时钟预分频器（预分频器=PRESC+1）。
// <id>pck6_prec
#ifndef CONF_PCK6_PRESC
#define CONF_PCK6_PRESC 7
#endif

// </h>
// </e>//<e>时钟_USB_480M配置
// <i> 指示是否启用USB_480M配置
// <id>启用_clk_gen_usb_480m
#ifndef CONF_CLK_USB_480M_CONFIG
#define CONF_CLK_USB_480M_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器USB_480M源

// <CLK_SRC_OPTION_UPLLCK“>USB 480M时钟（UPLLCK）

// <i> 这定义了USB_480M的时钟源
// <id>clk_gen_usb_480m_振荡器
#ifndef CONF_CLK_GEN_USB_480M_SRC
#define CONF_CLK_GEN_USB_480M_SRC CLK_SRC_OPTION_UPLLCK
#endif

// </h>

// <小时>

// </h>
// </e>//<e>时钟_USB_48M配置
// <i> 指示是否启用USB_48M配置
// <id>启用_clk_gen_usb_48m
#ifndef CONF_CLK_USB_48M_CONFIG
#define CONF_CLK_USB_48M_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器USB_48M源

// <CLK_SRC_OPTION_PLLACK“>PLLA时钟（PLLACK）

// <CLK_SRC_OPTION_UPLLCKDIV“>带分频器的UDPLL（MCKR UPLLDIV2）

// <i> 这定义了USB_48M的时钟源
// <id>clk_gen_usb_48m_振荡器
#ifndef CONF_CLK_GEN_USB_48M_SRC
#define CONF_CLK_GEN_USB_48M_SRC CLK_SRC_OPTION_UPLLCKDIV
#endif

// <q> 启用时钟_USB_48M
// <i> 指示USB_48M是启用还是禁用
// <id>clk_gen_usb_48m_arch_enable
#ifndef CONF_CLK_USB_48M_ENABLE
#define CONF_CLK_USB_48M_ENABLE 1
#endif

// </h>

// <小时>

// <o> USB时钟控制器分频器<1-16>
// <i> 选择USB时钟分频器（分频器=USBDIV+1）。
// <id>usb_48m_div
#ifndef CONF_USB_48M_DIV
#define CONF_USB_48M_DIV 5
#endif

// </h>
// </e>//<e>时钟_SLCK2配置
// <i> 指示SLCK2配置是否已启用
// <id>启用_clk_gen_slck2
#ifndef CONF_CLK_SLCK2_CONFIG
#define CONF_CLK_SLCK2_CONFIG 1
#endif

//<h> 时钟发生器
// <y> 时钟发生器SLCK2源

// <CLK_SRC_OPTION_SLCK“>慢时钟（SLCK）

// <i> 这定义了SLCK2的时钟源
// <id>clk_gen_slck2_振荡器
#ifndef CONF_CLK_GEN_SLCK2_SRC
#define CONF_CLK_GEN_SLCK2_SRC CLK_SRC_OPTION_SLCK
#endif

// </h>

// <小时>

// </h>
// </e>

// <e> 系统配置
// <i> 指示是否启用系统配置
// <id>启用_时钟_时钟
#ifndef CONF_SYSTEM_CONFIG
#define CONF_SYSTEM_CONFIG 1
#endif

// <h> 处理器时钟设置
// <y> 处理器时钟源
// <MCKR“>主时钟控制器（PMC_MCKR）
// <i> 这定义了HCLK（处理器时钟）的时钟源
// ＜id＞hclk_clock_source
#ifndef CONF_HCLK_SRC
#define CONF_HCLK_SRC MCKR
#endif

// <o> 闪存等待状态
// <0=>1个周期
// <1=>2个周期
// <2=>3个周期
// <3=>4个周期
// <4=>5个周期
// <5=>6个周期
// <6=>7个周期
// <i> 此字段定义读取和写入操作的等待状态数。
// ＜id＞efc_fws
#ifndef CONF_EFC_WAIT_STATE
#define CONF_EFC_WAIT_STATE 5
#endif

// </h>
// </e>

// <e> SysTick时钟
// <id>启用_隐藏_锁定
#ifndef CONF_SYSTICK_CLK_CONFIG
#define CONF_SYSTICK_CLK_CONFIG 1
#endif

// <y> SysTick时钟源
// <MCKR“>主时钟控制器（PMC_MCKR）
// <i> 这定义了SysTick时钟的时钟源
// <id>系统时钟源
#ifndef CONF_SYSTICK_CLK_SRC
#define CONF_SYSTICK_CLK_SRC MCKR
#endif

// <o> SysTick时钟分频器
// <8=> 8
// <i> 如果Systick未使用处理器时钟，则固定为8
// <id>系统时钟
#ifndef CONF_SYSTICK_CLK_DIV
#define CONF_SYSTICK_CLK_DIV 8
#endif

// </e>

// <e> OSC32K振荡器配置
// <i> 指示OSC32K的配置是否已启用
// <id>启用osc32k
#ifndef CONF_OSC32K_CONFIG
#define CONF_OSC32K_CONFIG 1
#endif

// <h> OSC32K振荡器控制
// <q> OSC32K振荡器启用
// <i> 指示OSC32K振荡器是否启用
// ＜id＞osc32k_arch_enable
#ifndef CONF_OSC32K_ENABLE
#define CONF_OSC32K_ENABLE 0
#endif
// </h>
// </e>

// <e> XOSC32K振荡器配置
// <i> 指示是否启用XOSC32K的配置
// <id>启用_xosc32k
#ifndef CONF_XOSC32K_CONFIG
#define CONF_XOSC32K_CONFIG 0
#endif

// <h> XOSC32K振荡器控制
// <y> 振荡器旁路选择
// <CONF_XOSC32K_NO_BYPASS“>32kHz晶体振荡器未被旁路。
// <CONF_XOSC32K_BYPASS“>32kHz晶体振荡器被旁路。
// <i> 指示是否绕过XOSC32K。
// <id>xosc32k_b旁路
#ifndef CONF_XOSC32K
#define CONF_XOSC32K CONF_XOSC32K_NO_BYPASS
#endif

// <q> XOSC32K振荡器启用
// <i> 指示XOSC32K振荡器是否启用
// ＜id＞xosc32k_arch_enable
#ifndef CONF_XOSC32K_ENABLE
#define CONF_XOSC32K_ENABLE 0
#endif
// </h>
// </e>

// <e> OSC12M振荡器配置
// <i> 指示OSC12M的配置是否已启用
// <id>启用_osc12m
#ifndef CONF_OSC12M_CONFIG
#define CONF_OSC12M_CONFIG 0
#endif

// <h> OSC12M振荡器控制
// <q> OSC12M振荡器启用
// <i> 指示OSC12M振荡器是否启用。
// 启用osc12m_arch_enable
#ifndef CONF_OSC12M_ENABLE
#define CONF_OSC12M_ENABLE 0
#endif

// <o> OSC12M选择器
//  <0=> 4000000
//  <1=> 8000000
//  <2=> 12000000
// <i> 选择嵌入式快速RC振荡器的频率。
// ＜id＞osc12m_selector
#ifndef CONF_OSC12M_SELECTOR
#define CONF_OSC12M_SELECTOR 2
#endif
// </h>
// </e>

// <e> XOSC20M振荡器配置
// <i> 指示是否启用XOSC20M的配置。
// <id>启用_xosc20m
#ifndef CONF_XOSC20M_CONFIG
#define CONF_XOSC20M_CONFIG 1
#endif

// <h> XOSC20M振荡器控制
// <o> XOSC20M选择器<3000000-2000000>
// <i> 选择晶体或陶瓷谐振器振荡器的频率。
// xosc20m_选择器
#ifndef CONF_XOSC20M_SELECTOR
#define CONF_XOSC20M_SELECTOR 12000000
#endif

// <o> 外部振荡器的启动时间（ms）：<0-256>
// <i> 选择启动时间。
// <id>xosc20m_启动时间
#ifndef CONF_XOSC20M_STARTUP_TIME
#define CONF_XOSC20M_STARTUP_TIME 62
#endif

// <y> 振荡器旁路选择
// <CONF_XOSC20M_NO_BYPASS“>外部晶体振荡器未被旁路。
// <CONF_XOSC20M_BYPASS“>外部晶体振荡器被旁路。
// <i> 指示是否绕过XOSC20M。
// <id>xosc20m_旁路
#ifndef CONF_XOSC20M
#define CONF_XOSC20M CONF_XOSC20M_NO_BYPASS
#endif

// <q> XOSC20M振荡器启用
// <i> 指示XOSC20M振荡器是否启用
// ＜id＞xosc20m_arch_enable
#ifndef CONF_XOSC20M_ENABLE
#define CONF_XOSC20M_ENABLE 1
#endif
// </h>
// </e>

// <e> PLLACK振荡器配置
// <i> 指示PLLACK的配置是否已启用
// <id>启用_回填
#ifndef CONF_PLLACK_CONFIG
#define CONF_PLLACK_CONFIG 1
#endif

// <y> PLLACK参考时钟源
// <MAINCK“>主时钟（MAINCK）
// <i> 选择时钟源。
// ＜id＞pllack_ref_clock
#ifndef CONF_PLLACK_CLK
#define CONF_PLLACK_CLK MAINCK
#endif

// <h> PLLACK振荡器控制
// <q> PLLACK振荡器启用
// <i> 指示PLLACK振荡器是否启用
// ＜id＞pllack_arch_enable
#ifndef CONF_PLLACK_ENABLE
#define CONF_PLLACK_ENABLE 1
#endif

// <o> PLLA前端分隔器（DIVA）<1-255>
// <i> 选择时钟分频器
// ＜id＞pllack_div
#ifndef CONF_PLLACK_DIV
#define CONF_PLLACK_DIV 1
#endif

// <o> PLLACK Muliplier<1-62>
// <i> 表示PLLA乘数（乘数=MULA+1）。
// ＜id＞pllack_mul
#ifndef CONF_PLLACK_MUL
#define CONF_PLLACK_MUL 25
#endif
// </h>
// </e>

// <e> UPLLCK振荡器配置
// <i> 指示UPLLCK的配置是否已启用
// <id>启用_
#ifndef CONF_UPLLCK_CONFIG
#define CONF_UPLLCK_CONFIG 1
#endif

// <y> UPLLCK参考时钟源
// <XOSC20M“>外部3-20MHz振荡器（XOSC20MM）
// <i> 选择时钟源，仅当输入频率为12M或16M时，上行链路输出为480M。
// <id>上传_参考_块
#ifndef CONF_UPLLCK_CLK
#define CONF_UPLLCK_CLK XOSC20M
#endif

// <h> UPLLCK振荡器控制
// <q> UPLLCK振荡器启用
// <i> 指示UPLLCK振荡器是否启用
// ＜id＞uplck_arch_enable
#ifndef CONF_UPLLCK_ENABLE
#define CONF_UPLLCK_ENABLE 1
#endif
// </h>
// </e>

// <e> UPLLCKDIV振荡器配置
// <i> 指示UPLLCKDIV的配置是否已启用
// <id>启用_upllckdiv
#ifndef CONF_UPLLCKDIV_CONFIG
#define CONF_UPLLCKDIV_CONFIG 1
#endif

// <y> UPLLCKDIV参考时钟源
// <UPLLCK“>USB 480M时钟（UPLLCK）
// <i> 选择时钟源。
// ＜id＞uplckdiv_ref_clock
#ifndef CONF_UPLLCKDIV_CLK
#define CONF_UPLLCKDIV_CLK UPLLCK
#endif

// <h> UPLLCKDIV振荡器控制
// <o> UPLLCKDIV时钟分频器
// <0=> 1
// <1=> 2
// <i> 选择时钟分频器。
// <id>上传kdiv_div
#ifndef CONF_UPLLCKDIV_DIV
#define CONF_UPLLCKDIV_DIV 1
#endif
// </h>
// </e>

// <e> 麦克/8
// <id>启用_确认_
#ifndef CONF_MCK_DIV_8_CONFIG
#define CONF_MCK_DIV_8_CONFIG 0
#endif

// <o> MCK/8来源
// <0=>主时钟（MCK）
// ＜id＞mck_div_8_src
#ifndef CONF_MCK_DIV_8_SRC
#define CONF_MCK_DIV_8_SRC 0
#endif
// </e>

// <e> 外部时钟输入配置
// <id>启用_摘要_文本
#ifndef CONF_DUMMY_EXT_CONFIG
#define CONF_DUMMY_EXT_CONFIG 1
#endif

// <o> 外部时钟输入源
// <i> 这里都是虚设值
// <i> 有关实际输入信息，请参阅外围设备设置
// <0=>来自特定引脚的特定时钟输入
// ＜id＞dummy_ext_src
#ifndef CONF_DUMMY_EXT_SRC
#define CONF_DUMMY_EXT_SRC 0
#endif
// </e>

// <e> 外部时钟配置
// <id>启用_摘要_文本_
#ifndef CONF_DUMMY_EXT_CLK_CONFIG
#define CONF_DUMMY_EXT_CLK_CONFIG 1
#endif

// <o> 外部时钟源
// <i> 这里都是虚拟值
// <i> 有关实际输入信息，请参阅外围设备设置
// <0=>外部时钟输入
// ＜id＞dummy_ext_clk_src
#ifndef CONF_DUMMY_EXT_CLK_SRC
#define CONF_DUMMY_EXT_CLK_SRC 0
#endif
// </e>

// <<<配置节末尾>>

#endif // HPL_PMC_CONFIG_H

