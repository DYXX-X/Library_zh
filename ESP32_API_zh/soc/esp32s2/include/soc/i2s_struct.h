// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

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
    union {
        struct {
            uint32_t tx_reset:         1;               /*设置此位以重置变送器*/
            uint32_t rx_reset:         1;               /*设置此位以重置接收器*/
            uint32_t tx_fifo_reset:    1;               /*设置此位以重置txFIFO*/
            uint32_t rx_fifo_reset:    1;               /*设置此位以重置rxFIFO*/
            uint32_t tx_start:         1;               /*设置此位以开始传输数据*/
            uint32_t rx_start:         1;               /*设置此位以开始接收数据*/
            uint32_t tx_slave_mod:     1;               /*设置此位以启用从发射机模式*/
            uint32_t rx_slave_mod:     1;               /*设置此位以启用从属接收器模式*/
            uint32_t tx_right_first:   1;               /*设置此位以首先传输右通道数据*/
            uint32_t rx_right_first:   1;               /*设置此位以首先接收右通道数据*/
            uint32_t tx_msb_shift:     1;               /*设置此位以启用菲利普斯标准模式下的变送器*/
            uint32_t rx_msb_shift:     1;               /*设置此位以启用菲利普斯标准模式下的接收器*/
            uint32_t tx_short_sync:    1;               /*设置此位以启用PCM标准模式下的发射器*/
            uint32_t rx_short_sync:    1;               /*设置此位以启用PCM标准模式下的接收器*/
            uint32_t tx_mono:          1;               /*设置此位以启用单声道模式下的发射器*/
            uint32_t rx_mono:          1;               /*设置此位以启用单声道模式下的接收器*/
            uint32_t tx_msb_right:     1;               /*设置此位以将右通道数据置于传输FIFO中的MSB。*/
            uint32_t rx_msb_right:     1;               /*设置此位以将右通道数据置于接收FIFO中的MSB。*/
            uint32_t tx_lsb_first_dma: 1;               /*1： DMA/APB中的数据从低位转换*/
            uint32_t rx_lsb_first_dma: 1;               /*1： DMA/APB中的数据从低位转换*/
            uint32_t sig_loopback:     1;               /*启用信号环回模式，发射器模块和接收器模块共享相同的WS和BCK信号。*/
            uint32_t tx_fifo_reset_st: 1;               /*1： i2s_tx_fifo重置不正常0:i2s_tx_fifo_reset正常*/
            uint32_t rx_fifo_reset_st: 1;               /*1： i2s_rx_fifo重置不正常0:i2s_rx-fifo重置正常*/
            uint32_t tx_reset_st:      1;               /*1： i2s_tx_reset不正常0:i2s_tx_reset正常*/
            uint32_t tx_dma_equal:     1;               /*1： 左通道的数据等于右通道的数据*/
            uint32_t rx_dma_equal:     1;               /*1： 左通道的数据等于右通道的数据*/
            uint32_t pre_req_en:       1;               /*设置此位以使i2s能够更早地准备数据*/
            uint32_t tx_big_endian:    1;
            uint32_t rx_big_endian:    1;
            uint32_t rx_reset_st:      1;
            uint32_t reserved30:       2;
        };
        uint32_t val;
    } conf;
    union {
        struct {
            uint32_t rx_take_data:          1;          /*i2s_rx_take_data_int中断的原始中断状态位*/
            uint32_t tx_put_data:           1;          /*i2s_tx_put_data_int中断的原始中断状态位*/
            uint32_t rx_wfull:              1;          /*i2s_rx_wull_int中断的原始中断状态位*/
            uint32_t rx_rempty:             1;          /*i2s_rx_rempty_int中断的原始中断状态位*/
            uint32_t tx_wfull:              1;          /*i2s_tx_wfull_int中断的原始中断状态位*/
            uint32_t tx_rempty:             1;          /*i2s_tx_rempty_int中断的原始中断状态位*/
            uint32_t rx_hung:               1;          /*i2s_rx_hung_int中断的原始中断状态位*/
            uint32_t tx_hung:               1;          /*i2s_tx_hung_int中断的原始中断状态位*/
            uint32_t in_done:               1;          /*i2s_in_done_int中断的原始中断状态位*/
            uint32_t in_suc_eof:            1;          /*i2s_in_suc_eof_int中断的原始中断状态位*/
            uint32_t in_err_eof:            1;          /*不要使用*/
            uint32_t out_done:              1;          /*i2s_out_done_int中断的原始中断状态位*/
            uint32_t out_eof:               1;          /*i2s_out_eof_int中断的原始中断状态位*/
            uint32_t in_dscr_err:           1;          /*i2s_in_dscr_err_int中断的原始中断状态位*/
            uint32_t out_dscr_err:          1;          /*i2s_out_dscr_err_int中断的原始中断状态位*/
            uint32_t in_dscr_empty:         1;          /*i2s_in_dscr_empty_int中断的原始中断状态位*/
            uint32_t out_total_eof:         1;          /*i2s_out_total_eof_int中断的原始中断状态位*/
            uint32_t v_sync:                1;          /*i2s_v_sync_int中断的原始中断状态位*/
            uint32_t reserved18:           14;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t rx_take_data:         1;           /*i2s_rx_take_data_int中断的屏蔽中断状态位*/
            uint32_t tx_put_data:          1;           /*i2s_tx_put_data_int中断的屏蔽中断状态位*/
            uint32_t rx_wfull:             1;           /*i2s_rx_wull_int中断的屏蔽中断状态位*/
            uint32_t rx_rempty:            1;           /*i2s_rx_rempty_int中断的屏蔽中断状态位*/
            uint32_t tx_wfull:             1;           /*i2s_tx_wfull_int中断的屏蔽中断状态位*/
            uint32_t tx_rempty:            1;           /*i2s_tx_rempty_int中断的屏蔽中断状态位*/
            uint32_t rx_hung:              1;           /*i2s_rx_hung_int中断的屏蔽中断状态位*/
            uint32_t tx_hung:              1;           /*i2s_tx_hung_int中断的屏蔽中断状态位*/
            uint32_t in_done:              1;           /*i2s_in_done_int中断的屏蔽中断状态位*/
            uint32_t in_suc_eof:           1;           /*i2s_in_suc_eof_int中断的屏蔽中断状态位*/
            uint32_t in_err_eof:           1;           /*不要使用*/
            uint32_t out_done:             1;           /*i2s_out_done_int中断的屏蔽中断状态位*/
            uint32_t out_eof:              1;           /*i2s_out_eof_int中断的屏蔽中断状态位*/
            uint32_t in_dscr_err:          1;           /*i2s_in_dscr_err_int中断的屏蔽中断状态位*/
            uint32_t out_dscr_err:         1;           /*i2s_out_dscr_err_int中断的屏蔽中断状态位*/
            uint32_t in_dscr_empty:        1;           /*i2s_in_dscr_empty_int中断的屏蔽中断状态位*/
            uint32_t out_total_eof:        1;           /*i2s_out_total_eof_int中断的屏蔽中断状态位*/
            uint32_t v_sync:               1;           /*i2s_v_sync_int中断的屏蔽中断状态位*/
            uint32_t reserved18:          14;
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t rx_take_data:          1;          /*i2s_rx_take_data_int中断的中断启用位*/
            uint32_t tx_put_data:           1;          /*i2s_tx_put_data_int中断的中断启用位*/
            uint32_t rx_wfull:              1;          /*i2s_rx_wull_int中断的中断启用位*/
            uint32_t rx_rempty:             1;          /*i2s_rx_rempty_int中断的中断启用位*/
            uint32_t tx_wfull:              1;          /*i2s_tx_wfull_int中断的中断启用位*/
            uint32_t tx_rempty:             1;          /*i2s_tx_rempty_int中断的中断启用位*/
            uint32_t rx_hung:               1;          /*i2s_rx_hung_int中断的中断启用位*/
            uint32_t tx_hung:               1;          /*i2s_tx_hung_int中断的中断启用位*/
            uint32_t in_done:               1;          /*i2s_in_done_int中断的中断启用位*/
            uint32_t in_suc_eof:            1;          /*i2s_in_suc_eof_int中断的中断启用位*/
            uint32_t in_err_eof:            1;          /*不要使用*/
            uint32_t out_done:              1;          /*i2s_out_done_int中断的中断启用位*/
            uint32_t out_eof:               1;          /*i2s_out_eof_int中断的中断启用位*/
            uint32_t in_dscr_err:           1;          /*i2s_in_dscr_err_int中断的中断启用位*/
            uint32_t out_dscr_err:          1;          /*i2s_out_dscr_err_int中断的中断启用位*/
            uint32_t in_dscr_empty:         1;          /*i2s_in_dscr_empty_int中断的中断启用位*/
            uint32_t out_total_eof:         1;          /*i2s_out_total_eof_int中断的中断启用位*/
            uint32_t v_sync:                1;          /*i2s_v_sync_int中断的中断启用位*/
            uint32_t reserved18:           14;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t take_data:             1;          /*设置此位以清除i2s_rx_take_data_int中断*/
            uint32_t put_data:              1;          /*设置此位以清除i2s_tx_put_data_int中断*/
            uint32_t rx_wfull:              1;          /*设置此位以清除i2s_rx_wull_int中断*/
            uint32_t rx_rempty:             1;          /*设置此位以清除i2s_rx_rempty_int中断*/
            uint32_t tx_wfull:              1;          /*设置此位以清除i2s_tx_wfull_int中断*/
            uint32_t tx_rempty:             1;          /*设置此位以清除i2s_tx_rempty_int中断*/
            uint32_t rx_hung:               1;          /*设置此位以清除i2s_rx_hung_int中断*/
            uint32_t tx_hung:               1;          /*设置此位以清除i2s_tx_hung_int中断*/
            uint32_t in_done:               1;          /*设置此位以清除i2s_in_done_int中断*/
            uint32_t in_suc_eof:            1;          /*设置此位以清除i2s_in_suc_eof_int中断*/
            uint32_t in_err_eof:            1;          /*不要使用*/
            uint32_t out_done:              1;          /*设置此位以清除i2s_out_done_int中断*/
            uint32_t out_eof:               1;          /*设置此位以清除i2s_out_eof_int中断*/
            uint32_t in_dscr_err:           1;          /*设置此位以清除i2s_in_dscr_err_int中断*/
            uint32_t out_dscr_err:          1;          /*设置此位以清除i2s_out_dscr_err_int中断*/
            uint32_t in_dscr_empty:         1;          /*设置此位以清除i2s_in_dscr_empty_int中断*/
            uint32_t out_total_eof:         1;          /*设置此位以清除i2s_out_total_eof_int中断*/
            uint32_t v_sync:                1;          /*设置此位以清除i2s_v_sync_int中断*/
            uint32_t reserved18:           14;
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t tx_bck_in_delay:   2;              /*BCK进入发射机的延迟周期数*/
            uint32_t tx_ws_in_delay:    2;              /*WS进入变送器的延迟周期数*/
            uint32_t rx_bck_in_delay:   2;              /*BCK进入接收机的延迟周期数*/
            uint32_t rx_ws_in_delay:    2;              /*WS进入接收器的延迟周期数*/
            uint32_t rx_sd_in_delay:    2;              /*SD进入接收器的延迟周期数*/
            uint32_t tx_bck_out_delay:  2;              /*BCK离开发射机的延迟周期数*/
            uint32_t tx_ws_out_delay:   2;              /*WS离开发射机的延迟周期数*/
            uint32_t tx_sd_out_delay:   2;              /*SD离开变送器的延迟周期数*/
            uint32_t rx_ws_out_delay:   2;              /*WS离开接收器的延迟周期数*/
            uint32_t rx_bck_out_delay:  2;              /*BCK出接收机的延迟周期数*/
            uint32_t tx_dsync_sw:       1;              /*设置此位以使信号与双同步方法同步到发射器中*/
            uint32_t rx_dsync_sw:       1;              /*设置此位以使信号与双同步方法同步到接收器中*/
            uint32_t data_enable_delay: 2;              /*数据有效标志的延迟周期数。*/
            uint32_t tx_bck_in_inv:     1;              /*设置该位以反转输入到从发射机的BCK信号*/
            uint32_t reserved25:        7;
        };
        uint32_t val;
    } timing;
    union {
        struct {
            uint32_t rx_data_num:          6;           /*接收器FIFO中的数据长度阈值*/
            uint32_t tx_data_num:          6;           /*发射机FIFO中的数据长度阈值*/
            uint32_t dscr_en:              1;           /*设置此位以启用I2S DMA模式*/
            uint32_t tx_fifo_mod:          3;           /*发射机FIFO模式配置位*/
            uint32_t rx_fifo_mod:          3;           /*接收机FIFO模式配置位*/
            uint32_t tx_fifo_mod_force_en: 1;           /*该位应始终设置为1*/
            uint32_t rx_fifo_mod_force_en: 1;           /*该位应始终设置为1*/
            uint32_t rx_fifo_sync:         1;           /*强制将rx数据写回内存*/
            uint32_t rx_24msb_en:          1;           /*仅在rx 24位模式下有用。1： 高24位在i2s fifo 0中有效：低24位在i2s fifo中有效*/
            uint32_t tx_24msb_en:          1;           /*仅在tx 24位模式下有用。1： 高24位在i2s fifo 0中有效：低24位在i2s fifo中有效*/
            uint32_t reserved24:           8;
        };
        uint32_t val;
    } fifo_conf;
    uint32_t rx_eof_num;                              /*要接收的数据的长度。它将触发i2s_in_suc_eof_int。*/
    uint32_t conf_single_data;                        /*右通道或左通道根据tx_chan_mod和regtx_msb_right输出存储在该寄存器中的常量值*/
    union {
        struct {
            uint32_t tx_chan_mod: 3;                    /*I2S发射机信道模式配置位。*/
            uint32_t rx_chan_mod: 2;                    /*I2S接收机信道模式配置位。*/
            uint32_t reserved5:  27;
        };
        uint32_t val;
    } conf_chan;
    union {
        struct {
            uint32_t addr:           20;                /*第一个outlink描述符的地址*/
            uint32_t reserved20:      8;
            uint32_t stop:            1;                /*设置此位以停止outlink描述符*/
            uint32_t start:           1;                /*设置此位以启动outlink描述符*/
            uint32_t restart:         1;                /*设置此位以重新启动outlink描述符*/
            uint32_t park:            1;
        };
        uint32_t val;
    } out_link;
    union {
        struct {
            uint32_t addr:          20;                 /*第一个内联描述符的地址*/
            uint32_t reserved20:     8;
            uint32_t stop:           1;                 /*设置此位以停止内联描述符*/
            uint32_t start:          1;                 /*设置此位以启动内联描述符*/
            uint32_t restart:        1;                 /*设置此位以重新启动内联描述符*/
            uint32_t park:           1;
        };
        uint32_t val;
    } in_link;
    uint32_t out_eof_des_addr;                          /*产生EOF的outlink描述符的地址*/
    uint32_t in_eof_des_addr;                           /*产生EOF的内联描述符的地址*/
    uint32_t out_eof_bfr_des_addr;                      /*相对于产生EOF的outlink描述符的缓冲区地址*/
    union {
        struct {
            uint32_t mode:         3;
            uint32_t reserved3:    1;
            uint32_t addr:         2;
            uint32_t reserved6:   26;
        };
        uint32_t val;
    } ahb_test;
    uint32_t in_link_dscr;                               /*当前内联描述符的地址*/
    uint32_t in_link_dscr_bf0;                           /*下一个内联描述符的地址*/
    uint32_t in_link_dscr_bf1;                           /*下一个内联数据缓冲区的地址*/
    uint32_t out_link_dscr;                              /*当前outlink描述符的地址*/
    uint32_t out_link_dscr_bf0;                          /*下一个outlink描述符的地址*/
    uint32_t out_link_dscr_bf1;                          /*下一个outlink数据缓冲区的地址*/
    union {
        struct {
            uint32_t in_rst:             1;             /*将此位设置为在dma FSM中重置*/
            uint32_t out_rst:            1;             /*设置此位以重置dma FSM*/
            uint32_t ahbm_fifo_rst:      1;             /*设置此位以重置DMA的ahb接口cmdFIFO*/
            uint32_t ahbm_rst:           1;             /*设置此位以重置DMA的ahb接口*/
            uint32_t out_loop_test:      1;             /*将此位设置为循环测试内联*/
            uint32_t in_loop_test:       1;             /*将此位设置为循环测试输出*/
            uint32_t out_auto_wrback:    1;             /*设置此位以在输出缓冲区传输完成时启用自动写回的outlink。*/
            uint32_t out_no_restart_clr: 1;             /*不要使用*/
            uint32_t out_eof_mode:       1;             /*DMA输出EOF标志生成模式。1：当DMA从FIFO弹出所有数据时0：当ahb将所有数据推送到FIFO时*/
            uint32_t outdscr_burst_en:   1;             /*DMA outlink描述符传输模式配置位。1： 使用突发模式0准备outlink描述符：使用字节模式准备outlink描述符*/
            uint32_t indscr_burst_en:    1;             /*DMA内联描述符传输模式配置位。1： 使用突发模式0准备内联描述符：使用字节模式准备内联描述符*/
            uint32_t out_data_burst_en:  1;             /*变送器数据传输模式配置位。1： 以突发模式0准备输出数据：以字节模式准备输出数据*/
            uint32_t check_owner:        1;             /*设置此位以启用硬件检查所有者位*/
            uint32_t mem_trans_en:       1;             /*不要使用*/
            uint32_t ext_mem_bk_size:    2;             /*DMA访问外部内存块大小。0:16字节1:32字节2:64字节3:保留*/
            uint32_t reserved16:        16;
        };
        uint32_t val;
    } lc_conf;
    union {
        struct {
            uint32_t wdata:         9;
            uint32_t reserved9:     7;
            uint32_t push:          1;
            uint32_t reserved17:   15;
        };
        uint32_t val;
    } out_fifo_push;
    union {
        struct {
            uint32_t rdata:       12;
            uint32_t reserved12:   4;
            uint32_t pop:          1;
            uint32_t reserved17:  15;
        };
        uint32_t val;
    } in_fifo_pop;
    union {
        struct {
            uint32_t dscr_addr:        18;
            uint32_t out_dscr_state:    2;
            uint32_t out_state:         3;
            uint32_t cnt:               7;
            uint32_t out_full:          1;
            uint32_t out_empty:         1;              /*DMA发射机状态寄存器*/
        };
        uint32_t val;
    } lc_state0;
    union {
        struct {
            uint32_t dscr_addr:       18;
            uint32_t in_dscr_state:    2;
            uint32_t in_state:         3;
            uint32_t cnt_debug:        7;
            uint32_t in_full:          1;
            uint32_t in_empty:         1;               /*DMA接收机状态寄存器*/
        };
        uint32_t val;
    } lc_state1;
    union {
        struct {
            uint32_t fifo_timeout:          8;          /*当fifo挂起计数器等于该值时，将触发i2s_tx_hung_int中断或i2s_rx-hung_int*/
            uint32_t fifo_timeout_shift:    3;          /*这些位用于缩放刻度计数器阈值。当计数器值>=88000/2^i2s_lc_fifo_timeout_shift时，滴答计数器复位*/
            uint32_t fifo_timeout_ena:      1;          /*FIFO超时的启用位*/
            uint32_t reserved12:           20;
        };
        uint32_t val;
    } lc_hung_conf;
    uint32_t reserved_78;
    uint32_t reserved_7c;
    uint32_t reserved_80;
    uint32_t reserved_84;
    uint32_t reserved_88;
    uint32_t reserved_8c;
    uint32_t reserved_90;
    uint32_t reserved_94;
    uint32_t reserved_98;
    uint32_t reserved_9c;
    union {
        struct {
            uint32_t tx_pcm_conf:    3;                 /*压缩/解压缩模块配置位。0：解压缩传输数据1：压缩传输数据*/
            uint32_t tx_pcm_bypass:  1;                 /*设置此位以绕过压缩/解压缩模块以传输数据。*/
            uint32_t rx_pcm_conf:    3;                 /*压缩/解压缩模块配置位。0：解压缩接收数据1：压缩接收数据*/
            uint32_t rx_pcm_bypass:  1;                 /*设置此位以绕过接收数据的压缩/解压缩模块。*/
            uint32_t tx_stop_en:     1;                 /*设置此位以在tx FIFO为emtpy时停止禁用输出BCK信号和WS信号*/
            uint32_t tx_zeros_rm_en: 1;                 /*不要使用*/
            uint32_t reserved10:    22;
        };
        uint32_t val;
    } conf1;
    union {
        struct {
            uint32_t fifo_force_pd:    1;               /*强制FIFO断电*/
            uint32_t fifo_force_pu:    1;               /*强制FIFO通电*/
            uint32_t plc_mem_force_pd: 1;
            uint32_t plc_mem_force_pu: 1;
            uint32_t dma_ram_force_pd: 1;
            uint32_t dma_ram_force_pu: 1;
            uint32_t dma_ram_clk_fo:   1;
            uint32_t reserved7:       25;
        };
        uint32_t val;
    } pd_conf;
    union {
        struct {
            uint32_t camera_en:             1;          /*设置此位以启用相机模式*/
            uint32_t lcd_tx_wrx2_en:        1;          /*LCD WR双用于一个数据。*/
            uint32_t lcd_tx_sdx2_en:        1;          /*设置此位以在LCD模式下复制数据对（帧格式2）。*/
            uint32_t data_enable_test_en:   1;          /*用于调试相机模式启用*/
            uint32_t data_enable:           1;          /*用于调试相机模式启用*/
            uint32_t lcd_en:                1;          /*设置此位以启用LCD模式*/
            uint32_t ext_adc_start_en:      1;          /*设置此位以启用外部信号触发ADC模式的功能。*/
            uint32_t inter_valid_en:        1;          /*设置此位以启用相机内部有效*/
            uint32_t cam_sync_fifo_reset:   1;          /*设置此位以重置cam_sync_fifo*/
            uint32_t cam_clk_loopback:      1;          /*将此位设置为从i2s_rx环回cam_clk*/
            uint32_t i_v_sync_filter_en:    1;
            uint32_t i_v_sync_filter_thres: 3;
            uint32_t reserved14:           18;
        };
        uint32_t val;
    } conf2;
    union {
        struct {
            uint32_t clkm_div_num: 8;                   /*积分I2S时钟分频器值*/
            uint32_t clkm_div_b:   6;                   /*分数分频器分子值*/
            uint32_t clkm_div_a:   6;                   /*分数分频器分母值*/
            uint32_t clk_en:       1;                   /*设置此位以启用clk门*/
            uint32_t clk_sel:      2;                   /*设置此位以启用clk_apl*/
            uint32_t reserved23:   9;
        };
        uint32_t val;
    } clkm_conf;
    union {
        struct {
            uint32_t tx_bck_div_num: 6;                 /*发射机模式中的位时钟配置位。*/
            uint32_t rx_bck_div_num: 6;                 /*接收器模式中的位时钟配置位。*/
            uint32_t tx_bits_mod:    6;                 /*设置比特以配置I2S发射机信道的比特长度。*/
            uint32_t rx_bits_mod:    6;                 /*设置比特以配置I2S接收器信道的比特长度。*/
            uint32_t reserved24:     8;
        };
        uint32_t val;
    } sample_rate_conf;
    uint32_t reserved_b4;
    uint32_t reserved_b8;
    union {
        struct {
            uint32_t tx_idle:    1;
            uint32_t reserved1: 31;                     /*1： i2s_tx为空闲状态*/
        };
        uint32_t val;
    } state;
    uint32_t reserved_c0;
    uint32_t reserved_c4;
    uint32_t reserved_c8;
    uint32_t reserved_cc;
    uint32_t reserved_d0;
    uint32_t reserved_d4;
    uint32_t reserved_d8;
    uint32_t reserved_dc;
    uint32_t reserved_e0;
    uint32_t reserved_e4;
    uint32_t reserved_e8;
    uint32_t reserved_ec;
    uint32_t reserved_f0;
    uint32_t reserved_f4;
    uint32_t reserved_f8;
    uint32_t date;                                      /**/
} i2s_dev_t;
extern i2s_dev_t I2S0;

_Static_assert(sizeof(i2s_dev_t)==0x100, "invalid i2s_dev_t size");

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_I2S_STRUCT_H_ */

