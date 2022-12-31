/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/**组：LCD配置寄存器*/
/** lcd_clock寄存器类型lcd时钟寄存器
 */
typedef union {
    struct {
        /** lcd_clkcnt_n:R/W；比特位置：[5:0]；默认值：3；当reg_CLK_equ_sysclk为0时，f_LCD_PCLK=f_LCD_CLK/（reg_clkcnt_N+1）。
         */
        uint32_t lcd_clkcnt_n: 6;
        /** lcd_clk_equi_sysclk:R/W；位位置：[6]；默认值：1；1： f_LCD_PCLK＝f_LCD_CLK。0:f_LCD_PCLK=f_LCD_CLK/（reg_clkcnt_N+1）。
         */
        uint32_t lcd_clk_equ_sysclk: 1;
        /** lcd_ck_idle_edge:R/W；位位置：[7]；默认值：0；1： LCD_PCLK线在空闲0时为高电平：LCD_PCLK线在闲置时为低电平。
         */
        uint32_t lcd_ck_idle_edge: 1;
        /** lcd_ck_out_edge:R/W；位位置：[8]；默认值：0；1： LCD_PCLK在前半个时钟周期中为高电平。0:LCD_PCLK在前半个时钟周期低。
         */
        uint32_t lcd_ck_out_edge: 1;
        /** lcd_clkm_div_num:R/W；比特位置：[16:9]；默认值：4；积分LCD时钟分频器值
         */
        uint32_t lcd_clkm_div_num: 8;
        /** lcd_clkm_div_b:R/W；比特位置：[22:17]；默认值：0；分数分频器分子值
         */
        uint32_t lcd_clkm_div_b: 6;
        /** lcd_clkm_div_a:R/W；位位置：[28:23]；默认值：0；分数分频器分母值
         */
        uint32_t lcd_clkm_div_a: 6;
        /** lcd_clk_sel:R/W；位位置：[30:29]；默认值：0；选择LCD模块源时钟。0：无时钟。1： 应用程序。2： CLK160.3：无时钟。
         */
        uint32_t lcd_clk_sel: 2;
        /** clk_en:R/W；位位置：[31]；默认值：0；设置此位以启用clk门
         */
        uint32_t clk_en: 1;
    };
    uint32_t val;
} lcd_cam_lcd_clock_reg_t;

/** lcd_rgb_yuv寄存器类型lcd配置寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0: 20;
        /** lcd_conv_8bits_data_inv:R/W；位位置：[20]；默认值：0；1： 每两个8位输入数据反相一次。2.禁用。
         */
        uint32_t lcd_conv_8bits_data_inv: 1;
        /** lcd_conv_txtorx:R/W；位位置：[21]；默认值：0；0:txtorx模式关闭。1:txtorx方式打开。
         */
        uint32_t lcd_conv_txtorx: 1;
        /** lcd_conv_yuv2yuv_mode:R/W；比特位置：[23:22]；默认值：3；0:到yuv422.1:到yuv420.2:到yuv411.3:禁用。要启用yuv2yuv模式，trans_mode必须设置为1。
         */
        uint32_t lcd_conv_yuv2yuv_mode: 2;
        /** lcd_conv_yuv_mode:R/W；位位置：[25:24]；默认值：0；0:yuv422.1:yuv420.2:yuv411.当处于yuv2yuv模式时，yuv_mode决定Data_in的yuv模式
         */
        uint32_t lcd_conv_yuv_mode: 2;
        /** lcd_conv_协议模式：R/W；位位置：[26]；默认值：0；0:BT601。1:BT709。
         */
        uint32_t lcd_conv_protocol_mode: 1;
        /** lcd_conv_data_out_mode：R/W；位位置：[27]；默认值：0；数据输出的LIMIT或FULL模式。0：限制。1： 满的，满的
         */
        uint32_t lcd_conv_data_out_mode: 1;
        /** lcd_conv_data_in_mode：R/W；位位置：[28]；默认值：0；数据输入的LIMIT或FULL模式。0：限制。1： 满的，满的
         */
        uint32_t lcd_conv_data_in_mode: 1;
        /** lcd_conv_mode_8bits_on:R/W；位位置：[29]；默认值：0；0:16位模式。1： 8位模式。
         */
        uint32_t lcd_conv_mode_8bits_on: 1;
        /** lcd_conv_trans_mode：R/W；位位置：[30]；默认值：0；0:YUV到RGB。1： RGB转换为YUV。
         */
        uint32_t lcd_conv_trans_mode: 1;
        /** lcd_conv-bypass:R/W；位位置：[31]；默认值：0；0：旁路转换器。1： 启用转换器。
         */
        uint32_t lcd_conv_bypass: 1;
    };
    uint32_t val;
} lcd_cam_lcd_rgb_yuv_reg_t;

/** lcd_user寄存器类型lcd配置寄存器
 */
typedef union {
    struct {
        /** lcd_dout_cyclelen:R/W；位位置：[12:0]；默认值：1；LCD模块的输出数据周期为负1。
         */
        uint32_t lcd_dout_cyclelen: 13;
        /** lcd_always_out_en:R/W；位位置：[13]；默认值：0；当LCD处于LCD_OUT状态时，LCD始终输出，除非清除reg_LCD_start或设置reg_LCD_reset。
         */
        uint32_t lcd_always_out_en: 1;
        uint32_t reserved_14: 5;
        /** lcd_8bits_order：R/W；位位置：[19]；默认值：0；1： 每两个数据字节反转一次，在1字节模式下有效。0：没有变化。
         */
        uint32_t lcd_8bits_order: 1;
        /** lcd_update_reg:R/W；位位置：[20]；默认值：0；1： 更新LCD寄存器，将由硬件清除。0：没关系。
         */
        uint32_t lcd_update: 1;
        /** lcd_bit_order:R/W；位位置：[21]；默认值：0；1： 更改数据位顺序，在单字节模式中将LCD_data_out[7:0]更改为LCD_data_out[0:7]，在双字节模式中将位[15:0]更改为位[0:15]。0：没有变化。
         */
        uint32_t lcd_bit_order: 1;
        /** lcd_byte_order:R/W；位位置：[22]；默认值：0；1： 反转数据字节顺序，仅在2字节模式下有效。0：没有变化。
         */
        uint32_t lcd_byte_order: 1;
        /** lcd_2byte_en:R/W；位位置：[23]；默认值：0；1： 输出LCD数据的位数为9～16。0：输出LCD数据位数为0～8。
         */
        uint32_t lcd_2byte_en: 1;
        /** lcd_dout:R/W；位位置：[24]；默认值：0；1： 当LCD启动时，能够按LCD顺序发送数据。0：禁用。
         */
        uint32_t lcd_dout: 1;
        /** lcd_dummy：R/W；位位置：[25]；默认值：0；1： 当LCD启动时，启用LCD序列中的DUMMY阶段。0：禁用。
         */
        uint32_t lcd_dummy: 1;
        /** lcd_cmd:R/W；位位置：[26]；默认值：0；1： 当LCD启动时，能够按LCD顺序发送命令。0：禁用。
         */
        uint32_t lcd_cmd: 1;
        /** lcd_start：R/W；位位置：[27]；默认值：0；LCD开始发送数据使能信号，高电平有效。
         */
        uint32_t lcd_start: 1;
        /** lcd_reset:WO；位位置：[28]；默认值：0；命令的值。
         */
        uint32_t lcd_reset: 1;
        /** lcd_dummy_cyclelen:R/W；位位置：[30:29]；默认值：0；虚拟循环长度减1。
         */
        uint32_t lcd_dummy_cyclelen: 2;
        /** lcd_cmd_2_cycle_en:R/W；位位置：[31]；默认值：0；命令阶段的周期长度。1： 2个循环。0:1循环。
         */
        uint32_t lcd_cmd_2_cycle_en: 1;
    };
    uint32_t val;
} lcd_cam_lcd_user_reg_t;

/** lcd_misc寄存器类型lcd配置寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0: 1;
        /** lcd_afifo_threshold_num:R/W；比特位置：[5:1]；默认值：11；lcd_afifo的错误阈值数。
         */
        uint32_t lcd_afifo_threshold_num: 5;
        /** lcd_vfk_cyclelen:R/W；位位置：[11:6]；默认值：3；LCD非RGB模式下的设置周期长度减1。
         */
        uint32_t lcd_vfk_cyclelen: 6;
        /** lcd_vbk_cyclelen:R/W；比特位置：[24:12]；默认值：0；在LCD RGB模式下，垂直背面空白区域周期长度减1，或在LCD非RGB模式下的保持时间周期长度。
         */
        uint32_t lcd_vbk_cyclelen: 13;
        /** lcd_next_frame_en:R/W；位位置：[25]；默认值：0；1： 发送当前帧时发送下一帧数据。0：当前帧发出时LCD停止。
         */
        uint32_t lcd_next_frame_en: 1;
        /** lcd_bk_en:R/W；位位置：[26]；默认值：0；1： LCD发送数据时启用空白区域。0：无空白区域。
         */
        uint32_t lcd_bk_en: 1;
        /** lcd_afifo_reset：工单；位位置：[27]；默认值：0；LCD AFIFO复位信号。
         */
        uint32_t lcd_afifo_reset: 1;
        /** lcd_cd_data_set:R/W；位位置：[28]；默认值：0；1： LCD_CD=！当lcd_st[2:0]处于lcd_OUT状态时，reg_cd_idle_edge。0:LCD_CD=reg_CD_idle_edge。
         */
        uint32_t lcd_cd_data_set: 1;
        /** lcd_cd_dummy_set:R/W；位位置：[29]；默认值：0；1： LCD_CD=！当lcd_st[2:0]处于lcd_DUMMY状态时，reg_cd_idle_edge。0:LCD_CD=reg_CD_idle_edge。
         */
        uint32_t lcd_cd_dummy_set: 1;
        /** lcd_cd_cmd_set:R/W；位位置：[30]；默认值：0；1： LCD_CD=！当lcd_st[2:0]处于lcd_CMD状态时，reg_cd_idle_edge。0:LCD_CD=reg_CD_idle_edge。
         */
        uint32_t lcd_cd_cmd_set: 1;
        /** lcd_cd_idle_edge:R/W；位位置：[31]；默认值：0；LCD_CD的默认值。
         */
        uint32_t lcd_cd_idle_edge: 1;
    };
    uint32_t val;
} lcd_cam_lcd_misc_reg_t;

/** lcd_ctrl寄存器类型lcd配置寄存器
 */
typedef union {
    struct {
        /** lcd_hb_front:R/W；位位置：[10:0]；默认值：0；它是框架的水平空白前门廊。
         */
        uint32_t lcd_hb_front: 11;
        /** lcd_va_height:R/W；比特位置：[20:11]；默认值：0；它是框架的垂直活动高度。
         */
        uint32_t lcd_va_height: 10;
        /** lcd_vt_height:R/W；位位置：[30:21]；默认值：0；它是框架的垂直总高度。
         */
        uint32_t lcd_vt_height: 10;
        /** lcd_rgb_mode_en:R/W；位位置：[31]；默认值：0；1： 启用注册模式输入vsync、hsync、de.0：禁用。
         */
        uint32_t lcd_rgb_mode_en: 1;
    };
    uint32_t val;
} lcd_cam_lcd_ctrl_reg_t;

/** lcd_ctrl1寄存器类型lcd配置寄存器
 */
typedef union {
    struct {
        /** lcd_vb_front:R/W；位位置：[7:0]；默认值：0；它是框架的垂直空白前门廊。
         */
        uint32_t lcd_vb_front: 8;
        /** lcd_ha_width:R/W；比特位置：[19:8]；默认值：0；它是帧的水平活动宽度。
         */
        uint32_t lcd_ha_width: 12;
        /** lcd_ht_width:R/W；位位置：[31:20]；默认值：0；它是框架的水平总宽度。
         */
        uint32_t lcd_ht_width: 12;
    };
    uint32_t val;
} lcd_cam_lcd_ctrl1_reg_t;

/** lcd_ctrl2寄存器类型lcd配置寄存器
 */
typedef union {
    struct {
        /** lcd_vsync_width:R/W；比特位置：[6:0]；默认值：1；这是一行中LCD_VSYNC激活脉冲的位置。
         */
        uint32_t lcd_vsync_width: 7;
        /** lcd_vsync_inidle_pol:R/W；位位置：[7]；默认值：0；它是LCD_VSYNC的空闲值。
         */
        uint32_t lcd_vsync_idle_pol: 1;
        /** lcd_de_idle_pol:R/W；位位置：[8]；默认值：0；它是LCD_D的空闲值。
         */
        uint32_t lcd_de_idle_pol: 1;
        /** lcd_hs_blank_en:R/W；位位置：[9]；默认值：0；1： LCD_HSYNC的脉冲在垂直消隐线RGB模式下输出。0:LCD_HSYNC脉冲仅在RGB模式下的有源区行中有效。
         */
        uint32_t lcd_hs_blank_en: 1;
        uint32_t reserved_10: 6;
        /** lcd_hsync_width:R/W；比特位置：[22:16]；默认值：1；这是一行中LCD_HSYNC激活脉冲的位置。
         */
        uint32_t lcd_hsync_width: 7;
        /** lcd_hsync_inidle_pol:R/W；位位置：[23]；默认值：0；它是LCD_HSYNC的空闲值。
         */
        uint32_t lcd_hsync_idle_pol: 1;
        /** lcd_hsync_position:R/W；位位置：[31:24]；默认值：0；这是一行中LCD_HSYNC激活脉冲的位置。
         */
        uint32_t lcd_hsync_position: 8;
    };
    uint32_t val;
} lcd_cam_lcd_ctrl2_reg_t;

/** lcd_cmd_val寄存器类型lcd配置寄存器
 */
typedef union {
    struct {
        /** lcd_cmd_value:R/W；位位置：[31:0]；默认值：0；LCD写入命令值。
         */
        uint32_t lcd_cmd_value: 32;
    };
    uint32_t val;
} lcd_cam_lcd_cmd_val_reg_t;

/** lcd_dly_mode寄存器类型lcd配置寄存器
 */
typedef union {
    struct {
        /** lcd_cd_mode：R/W；位位置：[1:0]；默认值：0；输出LCD_CD被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t lcd_cd_mode: 2;
        /** lcd_de_mode：R/W；位位置：[3:2]；默认值：0；输出LCD_D被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t lcd_de_mode: 2;
        /** lcd_hsync_mode:R/W；比特位置：[5:4]；默认值：0；输出LCD_HSYNC被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t lcd_hsync_mode: 2;
        /** lcd_vsync_mode:R/W；位位置：[7:6]；默认值：0；输出LCD_VSYNC被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t lcd_vsync_mode: 2;
        uint32_t reserved_8: 24;
    };
    uint32_t val;
} lcd_cam_lcd_dly_mode_reg_t;

/** lcd_data_dout_mode寄存器类型lcd配置寄存器
 */
typedef union {
    struct {
        /** dout0_mode：R/W；位位置：[1:0]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout0_mode: 2;
        /** dout1_mode：R/W；位位置：[3:2]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout1_mode: 2;
        /** 双模式：R/W；比特位置：[5:4]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout2_mode: 2;
        /** dout3_mode：R/W；位位置：[7:6]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout3_mode: 2;
        /** dout4_mode：R/W；比特位置：[9:8]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout4_mode: 2;
        /** dout5_mode：R/W；比特位置：[11:10]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout5_mode: 2;
        /** dout6_mode：R/W；比特位置：[13:12]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout6_mode: 2;
        /** 双7模式：R/W；比特位置：[15:14]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout7_mode: 2;
        /** 双8_模式：R/W；比特位置：[17:16]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout8_mode: 2;
        /** 双9_模式：R/W；比特位置：[19:18]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout9_mode: 2;
        /** dout10_mode：R/W；比特位置：[21:20]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout10_mode: 2;
        /** dout11_mode：R/W；比特位置：[23:22]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout11_mode: 2;
        /** dout12_mode：R/W；位位置：[25:24]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout12_mode: 2;
        /** dout13_模式：R/W；位位置：[27:26]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout13_mode: 2;
        /** dout14_模式：R/W；位位置：[29:28]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout14_mode: 2;
        /** dout15_模式：R/W；比特位置：[31:30]；默认值：0；输出数据位$n被模块时钟LCD_CLK延迟。0：无延迟输出。1： LCD_CLK的正沿延迟。2： LCD_CLK的负边缘延迟。
         */
        uint32_t dout15_mode: 2;
    };
    uint32_t val;
} lcd_cam_lcd_data_dout_mode_reg_t;


/**组：摄像机配置寄存器*/
/** cam_ctrl寄存器类型相机配置寄存器
 */
typedef union {
    struct {
        /** cam_stop_en:R/W；位位置：[0]；默认值：0；相机停止启用信号，1：DMA Rx FIFO满时相机停止。0：不停止。
         */
        uint32_t cam_stop_en: 1;
        /** cam_vsync_filter_threes:R/W；位位置：[3:1]；默认值：0；CAM_VSYNC信号的滤波器阈值。
         */
        uint32_t cam_vsync_filter_thres: 3;
        /** cam_update_reg:R/W；位位置：[4]；默认值：0；1： 更新摄像头寄存器，将由硬件清除。0：没关系。
         */
        uint32_t cam_update: 1;
        /** cam_byte_order:R/W；位位置：[5]；默认值：0；1： 更改数据位顺序，在单字节模式中将CAM_data_in[7:0]更改为CAM_data.in[0:7]，在双字节模式中将位[15:0]更改为位[0:15]。0：没有变化。
         */
        uint32_t cam_byte_order: 1;
        /** cam_bit_order:R/W；位位置：[6]；默认值：0；1： 反转数据字节顺序，仅在2字节模式下有效。0：没有变化。
         */
        uint32_t cam_bit_order: 1;
        /** cam_line_int_en:R/W；位位置：[7]；默认值：0；1： 启用以生成CAM_HS_INT。0：禁用。
         */
        uint32_t cam_line_int_en: 1;
        /** cam_vs_eof_en:R/W；位位置：[8]；默认值：0；1： CAM_VSYNC生成in_suc_eof。0:in_suc_eof由reg_cam_rec_data_cyclelen控制。
         */
        uint32_t cam_vs_eof_en: 1;
        /** cam_clkm_div_num:R/W；比特位置：[16:9]；默认值：4；积分相机时钟分频器值
         */
        uint32_t cam_clkm_div_num: 8;
        /** cam_clkm_div_b:R/W；比特位置：[22:17]；默认值：0；分数分频器分子值
         */
        uint32_t cam_clkm_div_b: 6;
        /** cam_clkm_div_a:R/W；位位置：[28:23]；默认值：0；分数分频器分母值
         */
        uint32_t cam_clkm_div_a: 6;
        /** cam_clk_sel:R/W；位位置：[30:29]；默认值：0；选择相机模块源时钟。0：无时钟。1： 应用程序。2： CLK160.3：无时钟。
         */
        uint32_t cam_clk_sel: 2;
        uint32_t reserved_31: 1;
    };
    uint32_t val;
} lcd_cam_cam_ctrl_reg_t;

/** cam_ctrl1寄存器类型相机配置寄存器
 */
typedef union {
    struct {
        /** cam_rec_data_bytelen:R/W；比特位置：[15:0]；默认值：0；摄像机接收数据字节长度减1以设置DMA in_suc_eof_int。
         */
        uint32_t cam_rec_data_bytelen: 16;
        /** cam_line_int_num:R/W；比特位置：[21:16]；默认值：0；行号减1以生成cam_hs_int。
         */
        uint32_t cam_line_int_num: 6;
        /** cam_clk_inv:R/W；位位置：[22]；默认值：0；1： 反转输入信号CAM_PCLK。0：不反转。
         */
        uint32_t cam_clk_inv: 1;
        /** cam_vsync_filter_en:R/W；位位置：[23]；默认值：0；1： 启用CAM_VSYNC过滤器功能。0：旁路。
         */
        uint32_t cam_vsync_filter_en: 1;
        /** cam_2byte_en:R/W；位位置：[24]；默认值：0；1： 输入数据的位数为9～16。0：输入数据的位位数为0～8。
         */
        uint32_t cam_2byte_en: 1;
        /** cam_de_inv:R/W；位位置：[25]；默认值：0；CAM_DE反相启用信号，高电平有效。
         */
        uint32_t cam_de_inv: 1;
        /** cam_hsync_inv:R/W；位位置：[26]；默认值：0；CAM_HSYNC反相启用信号，高电平有效。
         */
        uint32_t cam_hsync_inv: 1;
        /** cam_vsync_inv:R/W；位位置：[27]；默认值：0；CAM_VSYNC反相启用信号，高电平有效。
         */
        uint32_t cam_vsync_inv: 1;
        /** cam_vh_de_mode_en:R/W；位位置：[28]；默认值：0；1： 输入控制信号为CAM_DE CAM_HSYNC和CAM_VSYNC。0：输入控制信号是CAM_DE和CAM_VYNC。CAM_HSYNC和CAM_DE同时为1。
         */
        uint32_t cam_vh_de_mode_en: 1;
        /** cam_start:R/W；位位置：[29]；默认值：0；摄像头模块启动信号。
         */
        uint32_t cam_start: 1;
        /** cam_reset：工单；位位置：[30]；默认值：0；摄像头模块复位信号。
         */
        uint32_t cam_reset: 1;
        /** cam_afifo_reset:WO；位位置：[31]；默认值：0；相机AFIFO复位信号。
         */
        uint32_t cam_afifo_reset: 1;
    };
    uint32_t val;
} lcd_cam_cam_ctrl1_reg_t;

/** cam_rgb_yuv寄存器类型相机配置寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0: 21;
        /** cam_conv_8bits_data_inv:R/W；位位置：[21]；默认值：0；1： 每两个8位输入数据反相一次。2.禁用。
         */
        uint32_t cam_conv_8bits_data_inv: 1;
        /** cam_conv_yuv2yuv_mode:R/W；比特位置：[23:22]；默认值：3；0:到yuv422.1:到yuv420.2:到yuv411.3:禁用。要启用yuv2yuv模式，trans_mode必须设置为1。
         */
        uint32_t cam_conv_yuv2yuv_mode: 2;
        /** cam_conv_yuv_mode:R/W；位位置：[25:24]；默认值：0；0:yuv422.1:yuv420.2:yuv411.当处于yuv2yuv模式时，yuv_mode决定Data_in的yuv模式
         */
        uint32_t cam_conv_yuv_mode: 2;
        /** cam_conv_protocol_mode：R/W；位位置：[26]；默认值：0；0:BT601。1:BT709。
         */
        uint32_t cam_conv_protocol_mode: 1;
        /** cam_conv_data_out_mode：R/W；位位置：[27]；默认值：0；数据输出的LIMIT或FULL模式。0：限制。1： 满的，满的
         */
        uint32_t cam_conv_data_out_mode: 1;
        /** cam_conv_data_in_mode：R/W；位位置：[28]；默认值：0；数据输入的LIMIT或FULL模式。0：限制。1： 满的，满的
         */
        uint32_t cam_conv_data_in_mode: 1;
        /** cam_conv_mode_8bits_on:R/W；位位置：[29]；默认值：0；0:16位模式。1： 8位模式。
         */
        uint32_t cam_conv_mode_8bits_on: 1;
        /** cam_conv_trans_mode：R/W；位位置：[30]；默认值：0；0:YUV到RGB。1： RGB转换为YUV。
         */
        uint32_t cam_conv_trans_mode: 1;
        /** 凸轮_凸轮_旁通：R/W；位位置：[31]；默认值：0；0：旁路转换器。1： 启用转换器。
         */
        uint32_t cam_conv_bypass: 1;
    };
    uint32_t val;
} lcd_cam_cam_rgb_yuv_reg_t;


/**组：中断寄存器*/
/** lc_dma_int_ena寄存器LCD_camera dma中断启用寄存器的类型
 */
typedef union {
    struct {
        /** lcd_vsync_int_ena:R/W；位位置：[0]；默认值：0；LCD帧结束中断的启用位。
         */
        uint32_t lcd_vsync_int_ena: 1;
        /** lcd_trans_done_int_ena:R/W；位位置：[1]；默认值：0；lcd传输结束中断的启用位。
         */
        uint32_t lcd_trans_done_int_ena: 1;
        /** cam_vsync_int_ena:R/W；位位置：[2]；默认值：0；摄像机帧结束中断的启用位。
         */
        uint32_t cam_vsync_int_ena: 1;
        /** cam_hs_int_ena:R/W；位位置：[3]；默认值：0；摄像机线路中断的启用位。
         */
        uint32_t cam_hs_int_ena: 1;
        uint32_t reserved_4: 28;
    };
    uint32_t val;
} lcd_cam_lc_dma_int_ena_reg_t;

/** lc_dma_int_raw寄存器LCD_camera dma raw中断状态寄存器的类型
 */
typedef union {
    struct {
        /** lcd_vsync_int_raw:RO；位位置：[0]；默认值：0；LCD帧结束中断的原始位。
         */
        uint32_t lcd_vsync_int_raw: 1;
        /** lcd_trans_done_int_raw:RO；位位置：[1]；默认值：0；lcd传输结束中断的原始位。
         */
        uint32_t lcd_trans_done_int_raw: 1;
        /** cam_vsync_int_raw:RO；位位置：[2]；默认值：0；相机帧结束中断的原始位。
         */
        uint32_t cam_vsync_int_raw: 1;
        /** cam_hs_int_raw:RO；位位置：[3]；默认值：0；摄像机线路中断的原始位。
         */
        uint32_t cam_hs_int_raw: 1;
        uint32_t reserved_4: 28;
    };
    uint32_t val;
} lcd_cam_lc_dma_int_raw_reg_t;

/** lc_dma_int_st寄存器LCD_camera dma掩码中断状态寄存器的类型
 */
typedef union {
    struct {
        /** lcd_vsync_int_st:RO；位位置：[0]；默认值：0；LCD帧结束中断的状态位。
         */
        uint32_t lcd_vsync_int_st: 1;
        /** lcd_trans_done_int_st:RO；位位置：[1]；默认值：0；lcd传输结束中断的状态位。
         */
        uint32_t lcd_trans_done_int_st: 1;
        /** cam_vsync_int_st:RO；位位置：[2]；默认值：0；摄像机帧结束中断的状态位。
         */
        uint32_t cam_vsync_int_st: 1;
        /** cam_hs_int_st:RO；位位置：[3]；默认值：0；摄像机传输结束中断的状态位。
         */
        uint32_t cam_hs_int_st: 1;
        uint32_t reserved_4: 28;
    };
    uint32_t val;
} lcd_cam_lc_dma_int_st_reg_t;

/** lc_dma_int_clr寄存器LCD_camera dma中断清除寄存器的类型
 */
typedef union {
    struct {
        /** lcd_vsync_int_clr:WO；位位置：[0]；默认值：0；LCD帧结束中断的清除位。
         */
        uint32_t lcd_vsync_int_clr: 1;
        /** lcd_trans_done_int_clr:工单；位位置：[1]；默认值：0；lcd传输结束中断的清除位。
         */
        uint32_t lcd_trans_done_int_clr: 1;
        /** cam_vsync_int_clr:工单；位位置：[2]；默认值：0；相机帧结束中断的清除位。
         */
        uint32_t cam_vsync_int_clr: 1;
        /** cam_hs_int_clr:WO；位位置：[3]；默认值：0；摄像头线路中断的清除位。
         */
        uint32_t cam_hs_int_clr: 1;
        uint32_t reserved_4: 28;
    };
    uint32_t val;
} lcd_cam_lc_dma_int_clr_reg_t;


/**组：版本寄存器*/
/** lc_reg_date寄存器类型版本寄存器
 */
typedef union {
    struct {
        /** lc_date:R/W；位位置：[27:0]；默认值：33566752；LCD_CAM版本控制寄存器
         */
        uint32_t lc_date: 28;
        uint32_t reserved_28: 4;
    };
    uint32_t val;
} lcd_cam_lc_reg_date_reg_t;


typedef struct lcd_cam_dev_t {
    volatile lcd_cam_lcd_clock_reg_t lcd_clock;
    volatile lcd_cam_cam_ctrl_reg_t cam_ctrl;
    volatile lcd_cam_cam_ctrl1_reg_t cam_ctrl1;
    volatile lcd_cam_cam_rgb_yuv_reg_t cam_rgb_yuv;
    volatile lcd_cam_lcd_rgb_yuv_reg_t lcd_rgb_yuv;
    volatile lcd_cam_lcd_user_reg_t lcd_user;
    volatile lcd_cam_lcd_misc_reg_t lcd_misc;
    volatile lcd_cam_lcd_ctrl_reg_t lcd_ctrl;
    volatile lcd_cam_lcd_ctrl1_reg_t lcd_ctrl1;
    volatile lcd_cam_lcd_ctrl2_reg_t lcd_ctrl2;
    volatile lcd_cam_lcd_cmd_val_reg_t lcd_cmd_val;
    uint32_t reserved_02c;
    volatile lcd_cam_lcd_dly_mode_reg_t lcd_dly_mode;
    uint32_t reserved_034;
    volatile lcd_cam_lcd_data_dout_mode_reg_t lcd_data_dout_mode;
    uint32_t reserved_03c[10];
    volatile lcd_cam_lc_dma_int_ena_reg_t lc_dma_int_ena;
    volatile lcd_cam_lc_dma_int_raw_reg_t lc_dma_int_raw;
    volatile lcd_cam_lc_dma_int_st_reg_t lc_dma_int_st;
    volatile lcd_cam_lc_dma_int_clr_reg_t lc_dma_int_clr;
    uint32_t reserved_074[34];
    volatile lcd_cam_lc_reg_date_reg_t lc_reg_date;
} lcd_cam_dev_t;

#ifndef __cplusplus
_Static_assert(sizeof(lcd_cam_dev_t) == 0x100, "Invalid size of lcd_cam_dev_t structure");
#endif

extern lcd_cam_dev_t LCD_CAM;

#ifdef __cplusplus
}
#endif

