/** 版权所有2020 Espressif Systems（上海）私人有限公司
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#pragma once

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/**控制/状态寄存器*/
/** otg_conf寄存器PAD/DFIFO/PHY配置寄存器的类型。
 */
typedef union {
    struct {
        /** srp_sessend_override:R/W；位位置：[0]；默认值：0；该位用于启用srp会话结束信号的软件覆盖。1’b0：信号由芯片输入控制。1’b1：信号由软件控制。
         */
        uint32_t srp_sessend_override:1;
        /** srp_sessend_value：R/W；位位置：[1]；默认值：0；srp会话结束信号的软件覆盖值。
         */
        uint32_t srp_sessend_value:1;
        /** phy_sel:R/W；位位置：[2]；默认值：0；选择内部或外部PHY。1’b0：选择内部PHY。1’b1：选择外部PHY
         */
        uint32_t phy_sel:1;
        /** dfifo_force_pd:R/W；位位置：[3]；默认值：0；强制dfifo进入低功率模式。dfifo中的数据不会丢失。
         */
        uint32_t dfifo_force_pd:1;
        /** dbnce_fltr_bypass:R/W；位位置：[4]；默认值：0；绕过avalid的防抖滤波器。
         */
        uint32_t dbnce_fltr_bypass:1;
        /** exchg_pins_override:R/W；位位置：[5]；默认值：0；启用软件控制USB D+D-交换
         */
        uint32_t exchg_pins_override:1;
        /** exchg_pins：R/W；位位置：[6]；默认值：0；USB D+/D-交换。1’b0：不要改变。1’b1：交换D+D-。
         */
        uint32_t exchg_pins:1;
        /** vrefh:R/W；比特位置：[8:7]；默认值：0；控制单端输入高阈值。
         */
        uint32_t vrefh:2;
        /** vrefl:R/W；比特位置：[10:9]；默认值：0；控制单端输入低阈值。
         */
        uint32_t vrefl:2;
        /** vref_override:R/W；位位置：[11]；默认值：0；启用软件以控制输入阈值。
         */
        uint32_t vref_override:1;
        /** pad_pull_override:R/W；位位置：[12]；默认值：0；启用软件以在上拉或下拉模式下控制USB垫。
         */
        uint32_t pad_pull_override:1;
        /** dp_pullup:R/W；位位置：[13]；默认值：0；控制USB D+上拉。
         */
        uint32_t dp_pullup:1;
        /** dp_下拉：R/W；位位置：[14]；默认值：0；控制USB D+下拉。
         */
        uint32_t dp_pulldown:1;
        /** dm_pullup:R/W；位位置：[15]；默认值：0；控制USB D+上拉。
         */
        uint32_t dm_pullup:1;
        /** dm_下拉：R/W；位位置：[16]；默认值：0；控制USB D+下拉。
         */
        uint32_t dm_pulldown:1;
        /** 上拉值：R/W；位位置：[17]；默认值：0；控制上拉值。1’b0：典型值为2.4K。1’b1：典型值为1.2K。
         */
        uint32_t pullup_value:1;
        /** pad_enable:R/W；位位置：[18]；默认值：0；启用USB pad功能。
         */
        uint32_t pad_enable:1;
        /** ahb_clk_force_on:R/W；位位置：[19]；默认值：1；强制AHB时钟始终打开。
         */
        uint32_t ahb_clk_force_on:1;
        /** phy_clk_force_on:R/W；位位置：[20]；默认值：1；强制PHY时钟始终打开。
         */
        uint32_t phy_clk_force_on:1;
        /** phy_tx_edge_sel:R/W；位位置：[21]；默认值：0；选择PHY tx信号输出时钟边沿。1’b0：负边缘；1’b1：边缘。
         */
        uint32_t phy_tx_edge_sel:1;
        /** dfifo_force_pu:R/W；位位置：[22]；默认值：0；禁用dfifo以进入低功率模式。dfifo中的数据不会丢失。
         */
        uint32_t dfifo_force_pu:1;
        uint32_t reserved_23:8;
        /** clk_en:R/W；位位置：[31]；默认值：0；禁用CSR寄存器的自动时钟门控。
         */
        uint32_t clk_en:1;
    };
    uint32_t val;
} usb_wrap_otg_conf_reg_t;

/** test_conf寄存器test相关配置寄存器的类型。
 */
typedef union {
    struct {
        /** 测试启用：R/W；位位置：[0]；默认值：0；启用以测试USB垫。
         */
        uint32_t test_enable:1;
        /** test_usb_wrap_oe:R/W；位位置：[1]；默认值：0；USB板正在测试中。
         */
        uint32_t test_usb_wrap_oe:1;
        /** 测试tx-dp：R/W；位位置：[2]；默认值：0；测试中的USB D+tx值。
         */
        uint32_t test_tx_dp:1;
        /** 测试tx-dm:R/W；位位置：[3]；默认值：0；测试中的USB D-tx值。
         */
        uint32_t test_tx_dm:1;
        /** 测试rx_rcv:RO；位位置：[4]；默认值：0；测试中的USB差分rx值。
         */
        uint32_t test_rx_rcv:1;
        /** 测试rx_dp:RO；位位置：[5]；默认值：0；测试中的USB D+rx值。
         */
        uint32_t test_rx_dp:1;
        /** 测试rx_dm:RO；位位置：[6]；默认值：0；USB D-测试中的rx值。
         */
        uint32_t test_rx_dm:1;
        uint32_t reserved:25;
    };
    uint32_t val;
} usb_wrap_test_conf_reg_t;


/**状态寄存器*/
/** 日期寄存器类型版本寄存器。
 */
typedef union {
    struct {
        /** 日期：R/W；位位置：[31:0]；默认值：419631616；数据寄存器。
         */
        uint32_t date:32;
    };
    uint32_t val;
} usb_wrap_date_reg_t;


typedef struct {
    volatile usb_wrap_otg_conf_reg_t otg_conf;
    volatile usb_wrap_test_conf_reg_t test_conf;
    uint32_t reserved_008;
    uint32_t reserved_00c;
    uint32_t reserved_010;
    uint32_t reserved_014;
    uint32_t reserved_018;
    uint32_t reserved_01c;
    uint32_t reserved_020;
    uint32_t reserved_024;
    uint32_t reserved_028;
    uint32_t reserved_02c;
    uint32_t reserved_030;
    uint32_t reserved_034;
    uint32_t reserved_038;
    uint32_t reserved_03c;
    uint32_t reserved_040;
    uint32_t reserved_044;
    uint32_t reserved_048;
    uint32_t reserved_04c;
    uint32_t reserved_050;
    uint32_t reserved_054;
    uint32_t reserved_058;
    uint32_t reserved_05c;
    uint32_t reserved_060;
    uint32_t reserved_064;
    uint32_t reserved_068;
    uint32_t reserved_06c;
    uint32_t reserved_070;
    uint32_t reserved_074;
    uint32_t reserved_078;
    uint32_t reserved_07c;
    uint32_t reserved_080;
    uint32_t reserved_084;
    uint32_t reserved_088;
    uint32_t reserved_08c;
    uint32_t reserved_090;
    uint32_t reserved_094;
    uint32_t reserved_098;
    uint32_t reserved_09c;
    uint32_t reserved_0a0;
    uint32_t reserved_0a4;
    uint32_t reserved_0a8;
    uint32_t reserved_0ac;
    uint32_t reserved_0b0;
    uint32_t reserved_0b4;
    uint32_t reserved_0b8;
    uint32_t reserved_0bc;
    uint32_t reserved_0c0;
    uint32_t reserved_0c4;
    uint32_t reserved_0c8;
    uint32_t reserved_0cc;
    uint32_t reserved_0d0;
    uint32_t reserved_0d4;
    uint32_t reserved_0d8;
    uint32_t reserved_0dc;
    uint32_t reserved_0e0;
    uint32_t reserved_0e4;
    uint32_t reserved_0e8;
    uint32_t reserved_0ec;
    uint32_t reserved_0f0;
    uint32_t reserved_0f4;
    uint32_t reserved_0f8;
    uint32_t reserved_0fc;
    uint32_t reserved_100;
    uint32_t reserved_104;
    uint32_t reserved_108;
    uint32_t reserved_10c;
    uint32_t reserved_110;
    uint32_t reserved_114;
    uint32_t reserved_118;
    uint32_t reserved_11c;
    uint32_t reserved_120;
    uint32_t reserved_124;
    uint32_t reserved_128;
    uint32_t reserved_12c;
    uint32_t reserved_130;
    uint32_t reserved_134;
    uint32_t reserved_138;
    uint32_t reserved_13c;
    uint32_t reserved_140;
    uint32_t reserved_144;
    uint32_t reserved_148;
    uint32_t reserved_14c;
    uint32_t reserved_150;
    uint32_t reserved_154;
    uint32_t reserved_158;
    uint32_t reserved_15c;
    uint32_t reserved_160;
    uint32_t reserved_164;
    uint32_t reserved_168;
    uint32_t reserved_16c;
    uint32_t reserved_170;
    uint32_t reserved_174;
    uint32_t reserved_178;
    uint32_t reserved_17c;
    uint32_t reserved_180;
    uint32_t reserved_184;
    uint32_t reserved_188;
    uint32_t reserved_18c;
    uint32_t reserved_190;
    uint32_t reserved_194;
    uint32_t reserved_198;
    uint32_t reserved_19c;
    uint32_t reserved_1a0;
    uint32_t reserved_1a4;
    uint32_t reserved_1a8;
    uint32_t reserved_1ac;
    uint32_t reserved_1b0;
    uint32_t reserved_1b4;
    uint32_t reserved_1b8;
    uint32_t reserved_1bc;
    uint32_t reserved_1c0;
    uint32_t reserved_1c4;
    uint32_t reserved_1c8;
    uint32_t reserved_1cc;
    uint32_t reserved_1d0;
    uint32_t reserved_1d4;
    uint32_t reserved_1d8;
    uint32_t reserved_1dc;
    uint32_t reserved_1e0;
    uint32_t reserved_1e4;
    uint32_t reserved_1e8;
    uint32_t reserved_1ec;
    uint32_t reserved_1f0;
    uint32_t reserved_1f4;
    uint32_t reserved_1f8;
    uint32_t reserved_1fc;
    uint32_t reserved_200;
    uint32_t reserved_204;
    uint32_t reserved_208;
    uint32_t reserved_20c;
    uint32_t reserved_210;
    uint32_t reserved_214;
    uint32_t reserved_218;
    uint32_t reserved_21c;
    uint32_t reserved_220;
    uint32_t reserved_224;
    uint32_t reserved_228;
    uint32_t reserved_22c;
    uint32_t reserved_230;
    uint32_t reserved_234;
    uint32_t reserved_238;
    uint32_t reserved_23c;
    uint32_t reserved_240;
    uint32_t reserved_244;
    uint32_t reserved_248;
    uint32_t reserved_24c;
    uint32_t reserved_250;
    uint32_t reserved_254;
    uint32_t reserved_258;
    uint32_t reserved_25c;
    uint32_t reserved_260;
    uint32_t reserved_264;
    uint32_t reserved_268;
    uint32_t reserved_26c;
    uint32_t reserved_270;
    uint32_t reserved_274;
    uint32_t reserved_278;
    uint32_t reserved_27c;
    uint32_t reserved_280;
    uint32_t reserved_284;
    uint32_t reserved_288;
    uint32_t reserved_28c;
    uint32_t reserved_290;
    uint32_t reserved_294;
    uint32_t reserved_298;
    uint32_t reserved_29c;
    uint32_t reserved_2a0;
    uint32_t reserved_2a4;
    uint32_t reserved_2a8;
    uint32_t reserved_2ac;
    uint32_t reserved_2b0;
    uint32_t reserved_2b4;
    uint32_t reserved_2b8;
    uint32_t reserved_2bc;
    uint32_t reserved_2c0;
    uint32_t reserved_2c4;
    uint32_t reserved_2c8;
    uint32_t reserved_2cc;
    uint32_t reserved_2d0;
    uint32_t reserved_2d4;
    uint32_t reserved_2d8;
    uint32_t reserved_2dc;
    uint32_t reserved_2e0;
    uint32_t reserved_2e4;
    uint32_t reserved_2e8;
    uint32_t reserved_2ec;
    uint32_t reserved_2f0;
    uint32_t reserved_2f4;
    uint32_t reserved_2f8;
    uint32_t reserved_2fc;
    uint32_t reserved_300;
    uint32_t reserved_304;
    uint32_t reserved_308;
    uint32_t reserved_30c;
    uint32_t reserved_310;
    uint32_t reserved_314;
    uint32_t reserved_318;
    uint32_t reserved_31c;
    uint32_t reserved_320;
    uint32_t reserved_324;
    uint32_t reserved_328;
    uint32_t reserved_32c;
    uint32_t reserved_330;
    uint32_t reserved_334;
    uint32_t reserved_338;
    uint32_t reserved_33c;
    uint32_t reserved_340;
    uint32_t reserved_344;
    uint32_t reserved_348;
    uint32_t reserved_34c;
    uint32_t reserved_350;
    uint32_t reserved_354;
    uint32_t reserved_358;
    uint32_t reserved_35c;
    uint32_t reserved_360;
    uint32_t reserved_364;
    uint32_t reserved_368;
    uint32_t reserved_36c;
    uint32_t reserved_370;
    uint32_t reserved_374;
    uint32_t reserved_378;
    uint32_t reserved_37c;
    uint32_t reserved_380;
    uint32_t reserved_384;
    uint32_t reserved_388;
    uint32_t reserved_38c;
    uint32_t reserved_390;
    uint32_t reserved_394;
    uint32_t reserved_398;
    uint32_t reserved_39c;
    uint32_t reserved_3a0;
    uint32_t reserved_3a4;
    uint32_t reserved_3a8;
    uint32_t reserved_3ac;
    uint32_t reserved_3b0;
    uint32_t reserved_3b4;
    uint32_t reserved_3b8;
    uint32_t reserved_3bc;
    uint32_t reserved_3c0;
    uint32_t reserved_3c4;
    uint32_t reserved_3c8;
    uint32_t reserved_3cc;
    uint32_t reserved_3d0;
    uint32_t reserved_3d4;
    uint32_t reserved_3d8;
    uint32_t reserved_3dc;
    uint32_t reserved_3e0;
    uint32_t reserved_3e4;
    uint32_t reserved_3e8;
    uint32_t reserved_3ec;
    uint32_t reserved_3f0;
    uint32_t reserved_3f4;
    uint32_t reserved_3f8;
    volatile usb_wrap_date_reg_t date;
} usb_wrap_dev_t;

_Static_assert(sizeof(usb_wrap_dev_t)==0x400, "Invalid USB_WRAP size");

extern usb_wrap_dev_t USB_WRAP;

#ifdef __cplusplus
}
#endif

