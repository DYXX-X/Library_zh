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
#ifndef _SOC_I2S_STRUCT_H_
#define _SOC_I2S_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct i2s_dev_s {
    uint32_t reserved_0;
    uint32_t reserved_4;
    uint32_t reserved_8;
    union {
        struct {
            uint32_t rx_done:         1;             /*i2s_rx_done_int中断的原始中断状态位*/
            uint32_t tx_done:         1;             /*i2s_tx_done_int中断的原始中断状态位*/
            uint32_t rx_hung:         1;             /*i2s_rx_hung_int中断的原始中断状态位*/
            uint32_t tx_hung:         1;             /*i2s_tx_hung_int中断的原始中断状态位*/
            uint32_t reserved4:      28;             /*储备*/
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t rx_done:        1;              /*i2s_rx_done_int中断的屏蔽中断状态位*/
            uint32_t tx_done:        1;              /*i2s_tx_done_int中断的屏蔽中断状态位*/
            uint32_t rx_hung:        1;              /*i2s_rx_hung_int中断的屏蔽中断状态位*/
            uint32_t tx_hung:        1;              /*i2s_tx_hung_int中断的屏蔽中断状态位*/
            uint32_t reserved4:     28;              /*储备*/
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t rx_done:         1;             /*i2s_rx_done_int中断的中断启用位*/
            uint32_t tx_done:         1;             /*i2s_tx_done_int中断的中断启用位*/
            uint32_t rx_hung:         1;             /*i2s_rx_hung_int中断的中断启用位*/
            uint32_t tx_hung:         1;             /*i2s_tx_hung_int中断的中断启用位*/
            uint32_t reserved4:      28;             /*储备*/
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t rx_done:         1;             /*设置此位以清除i2s_rx_done_int中断*/
            uint32_t tx_done:         1;             /*设置此位以清除i2s_tx_done_int中断*/
            uint32_t rx_hung:         1;             /*设置此位以清除i2s_rx_hung_int中断*/
            uint32_t tx_hung:         1;             /*设置此位以清除i2s_tx_hung_int中断*/
            uint32_t reserved4:      28;             /*储备*/
        };
        uint32_t val;
    } int_clr;
    uint32_t reserved_1c;
    union {
        struct {
            uint32_t rx_reset:              1;       /*设置此位以重置接收器*/
            uint32_t rx_fifo_reset:         1;       /*设置此位以重置Rx AFIFO*/
            uint32_t rx_start:              1;       /*设置此位以开始接收数据*/
            uint32_t rx_slave_mod:          1;       /*设置此位以启用从属接收器模式*/
            uint32_t reserved4:             1;       /*保留*/
            uint32_t rx_mono:               1;       /*设置此位以启用单声道模式下的接收器*/
            uint32_t reserved6:             1;
            uint32_t rx_big_endian:         1;       /*I2S Rx字节尾数1：低地址值到高地址。0：地址值低的低地址。*/
            uint32_t rx_update:             1;       /*设置1以将I2S RX寄存器从APB时钟域更新到I2S RX时钟域。更新寄存器完成后，硬件将清除该位。*/
            uint32_t rx_mono_fst_vld:       1;       /*1： 第一信道数据值在I2S RX单声道模式下有效。0：第二个信道数据值在I2S RX单声道模式下有效。*/
            uint32_t rx_pcm_conf:           2;       /*I2S RX压缩/解压缩配置位。&0（环礁）：A-Law解压缩1（ltoa）：A-Law压缩2（utol）：u-Law解压缩3（ltou）：u-Law压缩&*/
            uint32_t rx_pcm_bypass:         1;       /*设置此位以绕过接收数据的压缩/解压缩模块。*/
            uint32_t rx_stop_mode:          2;       /*0:I2S Rx仅在清除reg_Rx_start时停止。1： 当reg_rx_start为0或in_suc_eof为1时停止。2：当reg_rx.start为0或者rx FIFO已满时停止I2S rx。*/
            uint32_t rx_left_align:         1;       /*1： I2S RX左对齐模式。0:I2S RX右对齐模式。*/
            uint32_t rx_24_fill_en:         1;       /*1： 将24个信道位存储到32位。0：存储24个通道位到24个位。*/
            uint32_t rx_ws_idle_pol:        1;       /*0:WS在接收左声道数据时应为0，而WS在右声道中为1。1： 当接收左声道数据时，WS应为1，而右声道中WS应为0。*/
            uint32_t rx_bit_order:          1;       /*I2S Rx位尾数。1： 首先接收LSB的小端。0:首先接收MSB的大端。*/
            uint32_t rx_tdm_en:             1;       /*1： 启用I2S TDM Rx模式。0：禁用。*/
            uint32_t rx_pdm_en:             1;       /*1： 启用I2S PDM Rx模式。0：禁用。*/
            uint32_t reserved23:            11;       /*储备*/
        };
        uint32_t val;
    } rx_conf;
    union {
        struct {
            uint32_t tx_reset:        1;             /*设置此位以重置变送器*/
            uint32_t tx_fifo_reset:   1;             /*设置此位以重置Tx AFIFO*/
            uint32_t tx_start:        1;             /*设置此位以开始传输数据*/
            uint32_t tx_slave_mod:    1;             /*设置此位以启用从发射机模式*/
            uint32_t reserved4:       1;             /*保留*/
            uint32_t tx_mono:         1;             /*设置此位以启用单声道模式下的发射器*/
            uint32_t tx_chan_equal:   1;             /*1： 在I2S TX单声道模式或TDM信道选择模式中，左信道数据的值等于右信道数据的数值。0：在i2s TX单声道模式或TDM信道选择模式下，无效信道数据为reg_i2s_single_data。*/
            uint32_t tx_big_endian:   1;             /*I2S Tx字节尾数1：低地址值到高地址。0：地址值低的低地址。*/
            uint32_t tx_update:       1;             /*设置1以将I2S TX寄存器从APB时钟域更新到I2S TX时钟域。更新寄存器完成后，硬件将清除该位。*/
            uint32_t tx_mono_fst_vld: 1;             /*1： 第一信道数据值在I2S TX单声道模式下有效。0：第二个信道数据值在I2S TX单声道模式下有效。*/
            uint32_t tx_pcm_conf:     2;             /*I2S TX压缩/解压缩配置位。&0（环礁）：A-Law解压缩1（ltoa）：A-Law压缩2（utol）：u-Law解压缩3（ltou）：u-Law压缩&*/
            uint32_t tx_pcm_bypass:   1;             /*设置此位以绕过压缩/解压缩模块以传输数据。*/
            uint32_t tx_stop_en:      1;             /*设置此位以在tx FIFO为emtpy时停止禁用输出BCK信号和WS信号*/
            uint32_t reserved14:      1;
            uint32_t tx_left_align:   1;             /*1： I2S TX左对齐模式。0:I2S TX右对齐模式。*/
            uint32_t tx_24_fill_en:   1;             /*1： 以24通道位模式发送32位。0：以24通道位模式发送24位*/
            uint32_t tx_ws_idle_pol:  1;             /*0:发送左通道数据时WS应为0，右通道中WS为1。1： 发送左通道数据时WS应为1，右通道中WS应为0。*/
            uint32_t tx_bit_order:    1;             /*I2S Tx位尾数。1： 首先发送LSB的小端。0:首先发送MSB的大端。*/
            uint32_t tx_tdm_en:       1;             /*1： 启用I2S TDM Tx模式。0：禁用。*/
            uint32_t tx_pdm_en:       1;             /*1： 启用I2S PDM Tx模式。0：禁用。*/
            uint32_t reserved21:      3;             /*保留*/
            uint32_t tx_chan_mod:     3;             /*I2S发射机信道模式配置位。*/
            uint32_t sig_loopback:    1;             /*启用信号环回模式，发射器模块和接收器模块共享相同的WS和BCK信号。*/
            uint32_t reserved28:      4;             /*保留*/
        };
        uint32_t val;
    } tx_conf;
    union {
        struct {
            uint32_t rx_tdm_ws_width:     7;         /*TDM模式下rx_ws_out的宽度为（reg_rx_TDM_ws_width[6:0]+1）*T_bck*/
            uint32_t rx_bck_div_num:      6;         /*接收器模式中的位时钟配置位。*/
            uint32_t rx_bits_mod:         5;         /*设置比特以配置I2S接收器信道的比特长度。*/
            uint32_t rx_half_sample_bits: 6;         /*I2S Rx半采样位-1。*/
            uint32_t rx_tdm_chan_bits:    5;         /*TDM模式下每个信道的Rx位数减去1。*/
            uint32_t rx_msb_shift:        1;         /*设置此位以启用菲利普斯标准模式下的接收器*/
            uint32_t reserved30:          2;         /*保留*/
        };
        uint32_t val;
    } rx_conf1;
    union {
        struct {
            uint32_t tx_tdm_ws_width:     7;         /*TDM模式下tx_ws_out的宽度为（reg_tx_TDM_ws_width[6:0]+1）*T_bck*/
            uint32_t tx_bck_div_num:      6;         /*发射机模式中的位时钟配置位。*/
            uint32_t tx_bits_mod:         5;         /*设置比特以配置I2S发射机信道的比特长度。*/
            uint32_t tx_half_sample_bits: 6;         /*I2S Tx半采样位-1。*/
            uint32_t tx_tdm_chan_bits:    5;         /*TDM模式下每个信道的Tx位数减去1。*/
            uint32_t tx_msb_shift:        1;         /*设置此位以启用菲利普斯标准模式下的变送器*/
            uint32_t tx_bck_no_dly:       1;         /*1： 在主模式下，BCK不会延迟以生成正/负边缘。0:BCK被延迟以在主模式下生成正/负边缘。*/
            uint32_t reserved31:          1;               /* 保留*/
        };
        uint32_t val;
    } tx_conf1;
    union {
        struct {
            uint32_t rx_clkm_div_num: 8;             /*积分I2S时钟分频器值*/
            uint32_t reserved8:      18;             /*保留*/
            uint32_t rx_clk_active:   1;             /*I2S Rx模块时钟启用信号。*/
            uint32_t rx_clk_sel:      2;             /*选择I2S Rx模块源时钟。0：无时钟。1： 应用程序。2： CLK160.3:I2S_MCLK_in。*/
            uint32_t mclk_sel:        1;             /*0：将I2S Tx模块时钟用作I2S_MCLK_OUT。1： 使用I2S Rx模块时钟作为I2S_MCLK_OUT。*/
            uint32_t reserved30:      2;             /*保留*/
        };
        uint32_t val;
    } rx_clkm_conf;
    union {
        struct {
            uint32_t tx_clkm_div_num: 8;             /*积分I2S TX时钟分频器值。f_ I2S_CLK＝f_。将有（a-b）*n-div和b*（n+1）-div。因此，平均组合将是：对于b<=a/2z*[x*n-div+（n+1）-div]+y*n-div。对于b>a/2z*[n-div+x*（n+1）-div]+y*（n+2）-div。*/
            uint32_t reserved8:      18;             /*保留*/
            uint32_t tx_clk_active:   1;             /*I2S Tx模块时钟启用信号。*/
            uint32_t tx_clk_sel:      2;             /*选择I2S Tx模块源时钟。0:XTAL时钟。1： 应用程序。2： CLK160.3:I2S_MCLK_in。*/
            uint32_t clk_en:          1;             /*设置此位以启用clk门*/
            uint32_t reserved30:      2;             /*保留*/
        };
        uint32_t val;
    } tx_clkm_conf;
    union {
        struct {
            uint32_t rx_clkm_div_z:   9;             /*对于b<=a/2，I2S_RX_CLKM_DIV_Z的值为b。对于b>a/2，I_2S_RX_CLKM_DIV_Z的值是（a-b）。*/
            uint32_t rx_clkm_div_y:   9;             /*对于b<=a/2，I2S_RX_CLKM_DIV_Y的值为（a%b）。对于b>a/2，I_2S_RX_CLKM_DIV_Y的值是（a%（a-b））。*/
            uint32_t rx_clkm_div_x:   9;             /*对于b<=a/2，I2S_RX_CLKM_DIV_X的值为（a/b）-1。对于b>a/2，I_2S_RX_CLKM_DIV_X的值是（a/（a-b））-1。*/
            uint32_t rx_clkm_div_yn1: 1;             /*对于b<=a/2，I2S_RX_CLKM_DIV_YN1的值为0。对于b>a/2，I_2S_RX_CLKM_DIV_YN1的数值为1。*/
            uint32_t reserved28:      4;             /*保留*/
        };
        uint32_t val;
    } rx_clkm_div_conf;
    union {
        struct {
            uint32_t tx_clkm_div_z:   9;             /*对于b<=a/2，I2S_TX_CLKM_DIV_Z的值为b。对于b>a/2，I_2S_TX_CLK_DIV_Z值为（a-b）。*/
            uint32_t tx_clkm_div_y:   9;             /*对于b<=a/2，I2S_TX_CLKM_DIV_Y的值为（a%b）。对于b>a/2，则I2S_TX-CLKM_DIV_Y的值是（a%（a-b））。*/
            uint32_t tx_clkm_div_x:   9;             /*对于b<=a/2，I2S_TX_CLKM_DIV_X的值为（a/b）-1。对于b>a/2，则I2S_TX-CLKM_DIF_X的值是（a/（a-b））-1。*/
            uint32_t tx_clkm_div_yn1: 1;             /*对于b<=a/2，I2S_TX_CLKM_DIV_YN1的值为0。对于b>a/2，I_2S_TX_CLK_DIV_YN2的值为1。*/
            uint32_t reserved28:      4;             /*保留*/
        };
        uint32_t val;
    } tx_clkm_div_conf;
    union {
        struct {
            uint32_t tx_pdm_hp_bypass              :    1;  /*I2S TX PDM是否旁通高压过滤器。该选项已删除。*/
            uint32_t tx_pdm_sinc_osr2              :    4;  /*I2S TX PDM OSR2值*/
            uint32_t tx_pdm_prescale               :    8;  /*用于sigmadelta的I2S TX PDM预缩放*/
            uint32_t tx_pdm_hp_in_shift            :    2;  /*I2S TX PDM sigmadelta刻度移位数：0:/2，1:x1，2:x2，3:x4*/
            uint32_t tx_pdm_lp_in_shift            :    2;  /*I2S TX PDM sigmadelta刻度移位数：0:/2，1:x1，2:x2，3:x4*/
            uint32_t tx_pdm_sinc_in_shift          :    2;  /*I2S TX PDM sigmadelta刻度移位数：0:/2，1:x1，2:x2，3:x4*/
            uint32_t tx_pdm_sigmadelta_in_shift    :    2;  /*I2S TX PDM sigmadelta刻度移位数：0:/2，1:x1，2:x2，3:x4*/
            uint32_t tx_pdm_sigmadelta_dither2     :    1;  /*I2S TX PDM sigmadelta抖动2值*/
            uint32_t tx_pdm_sigmadelta_dither      :    1;  /*I2S TX PDM sigmadelta抖动值*/
            uint32_t tx_pdm_dac_2out_en            :    1;  /*I2S TX PDM dac模式启用*/
            uint32_t tx_pdm_dac_mode_en            :    1;  /*I2S TX PDM dac 2信道启用*/
            uint32_t pcm2pdm_conv_en               :    1;  /*I2S TX PDM转换器启用*/
            uint32_t reserved26                    :    6;  /*保留*/
        };
        uint32_t val;
    } tx_pcm2pdm_conf;
    union {
        struct {
            uint32_t tx_pdm_fp                     :    10;  /*I2S发送PDM Fp*/
            uint32_t tx_pdm_fs                     :    10;  /*I2S TX PDM F*/
            uint32_t tx_iir_hp_mult12_5            :    3;  /*PDM TX IIR_HP滤波器2级的第四个参数为（504+I2S_TX_IIR_HP_MULT125[2:0]）*/
            uint32_t tx_iir_hp_mult12_0            :    3;  /*PDM TX IIR_HP滤波器1级的第四个参数为（504+I2S_TX_IIR_HP_MULT12_0[2:0]）*/
            uint32_t reserved26                    :    6;  /*保留*/
        };
        uint32_t val;
    } tx_pcm2pdm_conf1;
    uint32_t reserved_48;
    uint32_t reserved_4c;
    union {
        struct {
            uint32_t rx_tdm_pdm_chan0_en           :    1;  /*1： 启用I2S RX TDM或PDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_pdm_chan1_en           :    1;  /*1： 启用I2S RX TDM或PDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_pdm_chan2_en           :    1;  /*1： 启用I2S RX TDM或PDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_pdm_chan3_en           :    1;  /*1： 启用I2S RX TDM或PDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_pdm_chan4_en           :    1;  /*1： 启用I2S RX TDM或PDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_pdm_chan5_en           :    1;  /*1： 启用I2S RX TDM或PDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_pdm_chan6_en           :    1;  /*1： 启用I2S RX TDM或PDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_pdm_chan7_en           :    1;  /*1： 启用I2S RX TDM或PDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_chan8_en               :    1;  /*1： 启用I2S RX TDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_chan9_en               :    1;  /*1： 启用I2S RX TDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_chan10_en              :    1;  /*1： 启用I2S RX TDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_chan11_en              :    1;  /*1： 启用I2S RX TDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_chan12_en              :    1;  /*1： 启用I2S RX TDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_chan13_en              :    1;  /*1： 启用I2S RX TDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_chan14_en              :    1;  /*1： 启用I2S RX TDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_chan15_en              :    1;  /*1： 启用I2S RX TDM信道$n的有效数据输入。0：禁用，只需在此通道中输入0。*/
            uint32_t rx_tdm_tot_chan_num: 4;         /*I2S TX TDM模式的总信道数。*/
            uint32_t reserved20:         12;         /*保留*/
        };
        uint32_t val;
    } rx_tdm_ctrl;
    union {
        struct {
            uint32_t tx_tdm_chan0_en:     1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan1_en:     1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan2_en:     1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan3_en:     1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan4_en:     1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan5_en:     1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan6_en:     1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan7_en:     1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan8_en:     1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan9_en:     1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan10_en:    1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan11_en:    1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan12_en:    1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan13_en:    1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan14_en:    1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_chan15_en:    1;         /*1： 启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
            uint32_t tx_tdm_tot_chan_num: 4;         /*I2S TX TDM模式的总信道数减1。*/
            uint32_t tx_tdm_skip_msk_en:  1;         /*当DMA TX缓冲器存储（REG_TX_TDM_TOT_CHAN_NUM+1）信道的数据，并且仅发送启用信道的数据时，应设置该位。当DMA TX缓冲区中存储的所有数据都用于启用的信道时，清除该选项。*/
            uint32_t reserved21:         11;         /*保留*/
        };
        uint32_t val;
    } tx_tdm_ctrl;
    union {
        struct {
            uint32_t rx_sd_in_dm:   2;               /*I2S Rx SD输入信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved2                     :    14;  /* 保留*/
            uint32_t rx_ws_out_dm:  2;               /*I2S Rx WS输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved18:    2;
            uint32_t rx_bck_out_dm: 2;               /*I2S Rx BCK输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved22:    2;
            uint32_t rx_ws_in_dm:   2;               /*I2S Rx WS输入信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved26:    2;
            uint32_t rx_bck_in_dm:  2;               /*I2S Rx BCK输入信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved30:    2;
        };
        uint32_t val;
    } rx_timing;
    union {
        struct {
            uint32_t tx_sd_out_dm                  :    2;  /*I2S TX SD输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved2                     :    2;  /* 保留*/
            uint32_t tx_sd1_out_dm                 :    2;  /*I2S TX SD1输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved6                     :    10;  /* 保留*/
            uint32_t tx_ws_out_dm                  :    2;  /*I2S TX WS输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved18                    :    2;  /* 保留*/
            uint32_t tx_bck_out_dm                 :    2;  /*I2S TX BCK输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved22                    :    2;  /* 保留*/
            uint32_t tx_ws_in_dm                   :    2;  /*I2S TX WS输入信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved26                    :    2;  /* 保留*/
            uint32_t tx_bck_in_dm                  :    2;  /*I2S TX BCK输入信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
            uint32_t reserved30                    :    2;  /* 保留*/
        };
        uint32_t val;
    } tx_timing;
    union {
        struct {
            uint32_t fifo_timeout:          8;       /*当fifo挂起计数器等于该值时，将触发i2s_tx_hung_int中断或i2s_rx-hung_int*/
            uint32_t fifo_timeout_shift:    3;       /*这些位用于缩放刻度计数器阈值。当计数器值>=88000/2^i2s_lc_fifo_timeout_shift时，滴答计数器复位*/
            uint32_t fifo_timeout_ena:      1;       /*FIFO超时的启用位*/
            uint32_t reserved12:           20;       /*保留*/
        };
        uint32_t val;
    } lc_hung_conf;
    union {
        struct {
            uint32_t rx_eof_num:12;                  /*要接收的数据的长度。它将触发i2s_in_suc_eof_int。*/
            uint32_t reserved12:20;                  /*保留*/
        };
        uint32_t val;
    } rx_eof_num;
    uint32_t conf_single_data;                     /*右通道或左通道根据tx_chan_mod和regtx_msb_right输出存储在该寄存器中的常量值*/
    union {
        struct {
            uint32_t tx_idle:    1;                  /*1： i2s_tx是空闲状态。0:i2s_tx正在工作。*/
            uint32_t reserved1: 31;                  /*保留*/
        };
        uint32_t val;
    } state;
    uint32_t reserved_70;
    uint32_t reserved_74;
    uint32_t reserved_78;
    uint32_t reserved_7c;
    union {
        struct {
            uint32_t date:      28;                  /*版本控制寄存器*/
            uint32_t reserved28: 4;                  /*保留*/
        };
        uint32_t val;
    } date;
} i2s_dev_t;
extern i2s_dev_t I2S0;
#ifdef __cplusplus
}
#endif

#endif  /* _SOC_I2S_STRUCT_H_ */

