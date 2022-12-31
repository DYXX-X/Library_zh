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

/**中断寄存器*/
/** dma_int_raw寄存器原始中断状态的类型
 */
typedef union {
    struct {
        /** dma_in_done_int_raw:RO；位位置：[0]；默认值：0；这是中断原始位。当接收到帧的最后一个数据或内联描述符指示的接收缓冲区已满时触发。
         */
        uint32_t dma_in_done_int_raw: 1;
        /** dma_in_suc_eof_int_raw:RO；位位置：[1]；默认值：0；这是中断原始位。当接收到一帧的最后数据时触发。
         */
        uint32_t dma_in_suc_eof_int_raw: 1;
        /** dma_out_done_int_raw:RO；位位置：[2]；默认值：0；这是中断原始位。当一个输出描述符指示的所有数据都被推入Tx FIFO时触发。
         */
        uint32_t dma_out_done_int_raw: 1;
        /** dma_out_eof_int_raw:RO；位位置：[3]；默认值：0；这是中断原始位。当带有EOF标志的最后一个数据被推入Tx FIFO时触发。
         */
        uint32_t dma_out_eof_int_raw: 1;
        /** dma_in_dscr_err_int_raw:RO；位位置：[4]；默认值：0；这是中断原始位。检测到内联描述符错误时触发，包括所有者错误、内联描述符的第二个和第三个单词错误。
         */
        uint32_t dma_in_dscr_err_int_raw: 1;
        /** dma_out_dscr_err_int_raw:RO；位位置：[5]；默认值：0；这是中断原始位。检测到outlink描述符错误时触发，包括所有者错误、outlink描述符的第二个和第三个单词错误。
         */
        uint32_t dma_out_dscr_err_int_raw: 1;
        /** dma_in_dscr_empty_int_raw:RO；位位置：[6]；默认值：0；这是中断原始位。当接收数据完成且没有更多内联描述符时触发。
         */
        uint32_t dma_in_dscr_empty_int_raw: 1;
        /** dma_out_total_eof_int_raw:RO；位位置：[7]；默认值：0；这是中断原始位。当发送出与所有outlink描述符和具有有效EOF的最后一个描述符相对应的数据时触发。
         */
        uint32_t dma_out_total_eof_int_raw: 1;
        /** dma_crc_done_int_raw:RO；位位置：[8]；默认值：0；这是中断原始位。完成crc计算时触发。
         */
        uint32_t dma_crc_done_int_raw: 1;
        uint32_t reserved9: 23;
    };
    uint32_t val;
} cp_dma_int_raw_reg_t;

/** dma_int_st寄存器类型屏蔽中断状态
 */
typedef union {
    struct {
        /** dma_in_done_int_st:RO；位位置：[0]；默认值：0；这是当cp_in_done_int_ena设置为1时，cp_in_done _int中断的屏蔽中断位。
         */
        uint32_t dma_in_done_int_st: 1;
        /** dma_in_suc_eof_int_st:RO；位位置：[1]；默认值：0；这是当cp_in_suc_eof_int_ena设置为1时，cp_in_suce_eof_int中断的屏蔽中断位。
         */
        uint32_t dma_in_suc_eof_int_st: 1;
        /** dma_out_done_int_st:RO；位位置：[2]；默认值：0；这是当cp_out_done_int_ena设置为1时，cp_out_done_int中断的屏蔽中断位。
         */
        uint32_t dma_out_done_int_st: 1;
        /** dma_out_eof_int_st:RO；位位置：[3]；默认值：0；这是当cp_out_eof_int_ena设置为1时，cp_out_eof_int中断的屏蔽中断位。
         */
        uint32_t dma_out_eof_int_st: 1;
        /** dma_in_dscr_err_int_st:RO；位位置：[4]；默认值：0；这是当cp_in_dscr_err_int_ena设置为1时，cp_in_dcr_err_int中断的屏蔽中断位。
         */
        uint32_t dma_in_dscr_err_int_st: 1;
        /** dma_out_dscr_err_int_st:RO；位位置：[5]；默认值：0；这是当cp_out_dscr_err_int_ena设置为1时，cp_out_dscr_err.int中断的屏蔽中断位。
         */
        uint32_t dma_out_dscr_err_int_st: 1;
        /** dma_in_dscr_empty_int_st:RO；位位置：[6]；默认值：0；这是当cp_in_dscr_empty_int_ena设置为1时，cp_in_dcr_empty.int中断的屏蔽中断位。
         */
        uint32_t dma_in_dscr_empty_int_st: 1;
        /** dma_out_total_eof_int_st:RO；位位置：[7]；默认值：0；这是当cp_out_total_eof_int_ena设置为1时，cp_out_total_eoff_int中断的屏蔽中断位。
         */
        uint32_t dma_out_total_eof_int_st: 1;
        /** dma_crc_done_int_st:RO；位位置：[8]；默认值：0；这是当cp_crc_done_int_ena设置为1时，cp_crc_done_int中断的屏蔽中断位。
         */
        uint32_t dma_crc_done_int_st: 1;
        uint32_t reserved9: 23;
    };
    uint32_t val;
} cp_dma_int_st_reg_t;

/** dma_int_ena寄存器中断启用位的类型
 */
typedef union {
    struct {
        /** dma_in_done_int_ena:R/W；位位置：[0]；默认值：0；这是cp_in_done_int中断的中断启用位。
         */
        uint32_t dma_in_done_int_ena: 1;
        /** dma_in_suc_eof_int_ena:R/W；位位置：[1]；默认值：0；这是cp_in_suc_eof_int中断的中断启用位。
         */
        uint32_t dma_in_suc_eof_int_ena: 1;
        /** dma_out_done_int_ena:R/W；位位置：[2]；默认值：0；这是cp_out_done_int中断的中断启用位。
         */
        uint32_t dma_out_done_int_ena: 1;
        /** dma_out_eof_int_ena:R/W；位位置：[3]；默认值：0；这是cp_out_eof_int中断的中断启用位。
         */
        uint32_t dma_out_eof_int_ena: 1;
        /** dma_in_dscr_err_int_ena:R/W；位位置：[4]；默认值：0；这是cp_in_dscr_err_int中断的中断启用位。
         */
        uint32_t dma_in_dscr_err_int_ena: 1;
        /** dma_out_dscr_err_int_ena:R/W；位位置：[5]；默认值：0；这是cp_out_dscr_err_int中断的中断启用位。
         */
        uint32_t dma_out_dscr_err_int_ena: 1;
        /** dma_in_dscr_empty_int_ena:R/W；位位置：[6]；默认值：0；这是cp_in_dscr_empty_int中断的中断启用位。
         */
        uint32_t dma_in_dscr_empty_int_ena: 1;
        /** dma_out_total_eof_int_ena:R/W；位位置：[7]；默认值：0；这是cp_out_total_eof_int中断的中断启用位。
         */
        uint32_t dma_out_total_eof_int_ena: 1;
        /** dma_crc_done_int_ena:R/W；位位置：[8]；默认值：0；这是cp_crc_done_int中断的中断启用位。
         */
        uint32_t dma_crc_done_int_ena: 1;
        uint32_t reserved9: 23;
    };
    uint32_t val;
} cp_dma_int_ena_reg_t;

/** dma_int_clr寄存器类型中断清除位
 */
typedef union {
    struct {
        /** dma_in_done_int_clr:工单；位位置：[0]；默认值：0；设置此位以清除cp_in_done_int中断。
         */
        uint32_t dma_in_done_int_clr: 1;
        /** dma_in_suc_eof_int_clr:工单；位位置：[1]；默认值：0；设置此位以清除cp_in_suc_eof_int中断。
         */
        uint32_t dma_in_suc_eof_int_clr: 1;
        /** dma_out_done_int_clr:工单；位位置：[2]；默认值：0；设置此位以清除cp_out_done_int中断。
         */
        uint32_t dma_out_done_int_clr: 1;
        /** dma_out_eof_int_clr：工单；位位置：[3]；默认值：0；设置此位以清除cp_out_eof_int中断。
         */
        uint32_t dma_out_eof_int_clr: 1;
        /** dma_in_dscr_err_int_clr:工单；位位置：[4]；默认值：0；设置此位以清除cp_in_dscr_err_int中断。
         */
        uint32_t dma_in_dscr_err_int_clr: 1;
        /** dma_out_dscr_err_int_clr:工单；位位置：[5]；默认值：0；设置此位以清除cp_out_dscr_err_int中断。
         */
        uint32_t dma_out_dscr_err_int_clr: 1;
        /** dma_in_dscr_empty_int_clr:WO；位位置：[6]；默认值：0；设置此位以清除cp_in_dscr_empty_int中断。
         */
        uint32_t dma_in_dscr_empty_int_clr: 1;
        /** dma_out_total_eof_int_clr:工单；位位置：[7]；默认值：0；设置此位以清除cp_out_total_eof_int中断。
         */
        uint32_t dma_out_total_eof_int_clr: 1;
        /** dma_crc_done_int_clr:工单；位位置：[8]；默认值：0；设置此位以清除cp_crc_done_int中断。
         */
        uint32_t dma_crc_done_int_clr: 1;
        uint32_t reserved9: 23;
    };
    uint32_t val;
} cp_dma_int_clr_reg_t;


/**配置寄存器*/
/** dma_out_link寄存器的类型链接描述符地址和控制
 */
typedef union {
    struct {
        /** dma_outlink_addr:R/W；比特位置：[19:0]；默认值：0；该寄存器用于指定第一个输出链接描述符地址的最低有效20位。
         */
        uint32_t dma_outlink_addr: 20;
        uint32_t reserved_20: 8;
        /** dma_outlink_stop:R/W；位位置：[28]；默认值：0；设置此位以停止处理outlink描述符。
         */
        uint32_t dma_outlink_stop: 1;
        /** dma_outlink_start:R/W；位位置：[29]；默认值：0；设置此位以启动新的outlink描述符。
         */
        uint32_t dma_outlink_start: 1;
        /** dma_outlink_restart：R/W；位位置：[30]；默认值：0；设置此位以从最后一个地址重新启动outlink descriptpr。
         */
        uint32_t dma_outlink_restart: 1;
        /** dma_outlink_park:RO；位位置：[31]；默认值：0；1： outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。
         */
        uint32_t dma_outlink_park: 1;
    };
    uint32_t val;
} cp_dma_out_link_reg_t;

/** dma_in_link寄存器的类型链接描述符地址和控制
 */
typedef union {
    struct {
        /** dma_inlink_addr:R/W；比特位置：[19:0]；默认值：0；该寄存器用于指定第一个内联描述符地址的最低有效20位。
         */
        uint32_t dma_inlink_addr: 20;
        uint32_t reserved_20: 8;
        /** dma_inlink_stop:R/W；位位置：[28]；默认值：0；设置此位以停止处理内联描述符。
         */
        uint32_t dma_inlink_stop: 1;
        /** dma_inlink_start:R/W；位位置：[29]；默认值：0；设置此位以开始处理内联描述符。
         */
        uint32_t dma_inlink_start: 1;
        /** dma_inlink_restart：R/W；位位置：[30]；默认值：0；设置此位以重新启动新的内联描述符。
         */
        uint32_t dma_inlink_restart: 1;
        /** dma_inlink_park:RO；位位置：[31]；默认值：0；1： 内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。
         */
        uint32_t dma_inlink_park: 1;
    };
    uint32_t val;
} cp_dma_in_link_reg_t;

/** dma_conf寄存器类型复制dma配置寄存器
 */
typedef union {
    struct {
        /** dma_in_rst:R/W；位位置：[0]；默认值：0；设置此位以重置in_inf状态机。
         */
        uint32_t dma_in_rst: 1;
        /** dma_out_rst:R/W；位位置：[1]；默认值：0；设置此位以重置out_inf状态机。
         */
        uint32_t dma_out_rst: 1;
        /** dma_cmdfifo_rst:R/W；位位置：[2]；默认值：0；设置此位以重置in_cmd fifo和out_cmd fivo。
         */
        uint32_t dma_cmdfifo_rst: 1;
        /** dma_fifo_rst:R/W；位位置：[3]；默认值：0；设置此位以重置接收FIFO中的数据。
         */
        uint32_t dma_fifo_rst: 1;
        /** dma_out_owner:R/W；位位置：[4]；默认值：0；这用于配置OUT描述符中的所有者位。这仅在设置reg_out_auto_wrback时有效。
         */
        uint32_t dma_out_owner: 1;
        /** dma_in_owner:R/W；位位置：[5]；默认值：0；这用于配置in描述符中的所有者位。
         */
        uint32_t dma_in_owner: 1;
        /** dma_out_auto_werback:R/W；位位置：[6]；默认值：0；当硬件已经使用此描述符时，此位用于写回描述符。
         */
        uint32_t dma_out_auto_wrback: 1;
        /** dma_check_owner:R/W；位位置：[7]；默认值：0；设置此位以启用所有者位签入描述符。
         */
        uint32_t dma_check_owner: 1;
        /** dma_crc_cal_reset:R/W；位位置：[8]；默认值：0；设置此位以重置crc计算。
         */
        uint32_t dma_crc_cal_reset: 1;
        /** dma_crc_cal_en:R/W；位位置：[9]；默认值：0；设置此位启用crc计算功能。
         */
        uint32_t dma_crc_cal_en: 1;
        /** dma_crc_big_endin_en:R/W；位位置：[10]；默认值：0；设置此位以重新排序将被发送以执行crc的数据位。
         */
        uint32_t dma_crc_big_endian_en: 1;
        /** dma_crc_out_reverse_en:R/W；位位置：[11]；默认值：0；设置此位以反转crc计算结果。
         */
        uint32_t dma_crc_out_reverse_en: 1;
        uint32_t reserved_12: 19;
        /** dma_clk_en:R/W；位位置：[31]；默认值：0；1’b1：强制打开寄存器时钟。1’b0：仅当应用程序写入寄存器时才支持时钟。
         */
        uint32_t dma_clk_en: 1;
    };
    uint32_t val;
} cp_dma_conf_reg_t;


/**状态寄存器*/
/** 发生eof时dma_out_eof_des_addr寄存器异常描述符地址的类型
 */
typedef union {
    struct {
        /** dma_out_eof_des_addr:RO；位位置：[31:0]；默认值：0；当该描述符中的EOF位为1时，该寄存器存储outlink描述符的地址。
         */
        uint32_t dma_out_eof_des_addr: 32;
    };
    uint32_t val;
} cp_dma_out_eof_des_addr_reg_t;

/** 发生eof时dma_in_eof_des_addr寄存器Inlink描述符地址的类型
 */
typedef union {
    struct {
        /** dma_in_suc_eof_des_addr:RO；位位置：[31:0]；默认值：0；当收到成功的EOF时，此寄存器存储内联描述符的地址。
         */
        uint32_t dma_in_suc_eof_des_addr: 32;
    };
    uint32_t val;
} cp_dma_in_eof_des_addr_reg_t;

/** dma_out_eof_bfr_des_addr寄存器的类型最后一个Outlink描述符之前的Outlink描述符地址
 */
typedef union {
    struct {
        /** dma_out_eof_bfr_des_addr:RO；位位置：[31:0]；默认值：0；此寄存器存储最后一个outlink描述符之前的outlink描述符的地址。
         */
        uint32_t dma_out_eof_bfr_des_addr: 32;
    };
    uint32_t val;
} cp_dma_out_eof_bfr_des_addr_reg_t;

/** dma_inlink_dscr寄存器类型当前内联描述符的地址
 */
typedef union {
    struct {
        /** dma_inlink_dscr:RO；位位置：[31:0]；默认值：0；当前内联描述符x的地址。
         */
        uint32_t dma_inlink_dscr: 32;
    };
    uint32_t val;
} cp_dma_inlink_dscr_reg_t;

/** dma_inlink_dscr_bf0寄存器类型最后一个内联描述符的地址
 */
typedef union {
    struct {
        /** dma_inlink_dscr_bf0:RO；位位置：[31:0]；默认值：0；最后一个内联描述符x-1的地址。
         */
        uint32_t dma_inlink_dscr_bf0: 32;
    };
    uint32_t val;
} cp_dma_inlink_dscr_bf0_reg_t;

/** dma_inlink_dscr_bf1寄存器类型倒数第二个内联描述符的地址
 */
typedef union {
    struct {
        /** dma_inlink_dscr_bf1:RO；位位置：[31:0]；默认值：0；倒数第二个内联描述符x-2的地址。
         */
        uint32_t dma_inlink_dscr_bf1: 32;
    };
    uint32_t val;
} cp_dma_inlink_dscr_bf1_reg_t;

/** dma_outlink_dscr寄存器类型当前outlink描述符的地址
 */
typedef union {
    struct {
        /** dma_outlink_dscr:RO；位位置：[31:0]；默认值：0；当前outlink描述符y的地址。
         */
        uint32_t dma_outlink_dscr: 32;
    };
    uint32_t val;
} cp_dma_outlink_dscr_reg_t;

/** dma_outlink_dscr_bf0寄存器类型最后一个outlink描述符的地址
 */
typedef union {
    struct {
        /** dma_outlink_dscr_bf0:RO；位位置：[31:0]；默认值：0；最后一个outlink描述符y-1的地址。
         */
        uint32_t dma_outlink_dscr_bf0: 32;
    };
    uint32_t val;
} cp_dma_outlink_dscr_bf0_reg_t;

/** dma_outlink_dscr_bf1寄存器类型倒数第二个outlink描述符的地址
 */
typedef union {
    struct {
        /** dma_outlink_dscr_bf1:RO；位位置：[31:0]；默认值：0；倒数第二个outlink描述符y-2的地址。
         */
        uint32_t dma_outlink_dscr_bf1: 32;
    };
    uint32_t val;
} cp_dma_outlink_dscr_bf1_reg_t;

/** dma_in_st寄存器类型接收数据的状态寄存器
 */
typedef union {
    struct {
        /** dma_inlink_dscr_addr:RO；比特位置：[17:00]；默认值：0；此寄存器存储当前内联描述符的地址。
         */
        uint32_t dma_inlink_dscr_addr: 18;
        /** dma_in_dscr_state:RO；比特位置：[19:18]；默认值：0；保留。
         */
        uint32_t dma_in_dscr_state: 2;
        /** dma_in_state:RO；比特位置：[22:20]；默认值：0；保留。
         */
        uint32_t dma_in_state: 3;
        /** dma_fifo_empty:RO；位位置：[23]；默认值：0；复制DMA FIFO空信号。
         */
        uint32_t dma_fifo_empty: 1;
        uint32_t reserved24: 8;
    };
    uint32_t val;
} cp_dma_in_st_reg_t;

/** dma_out_st寄存器类型传输数据的状态寄存器
 */
typedef union {
    struct {
        /** dma_outlink_dscr_addr:RO；比特位置：[17:00]；默认值：0；此寄存器存储当前outlink描述符的地址。
         */
        uint32_t dma_outlink_dscr_addr: 18;
        /** dma_out_dscr_state:RO；比特位置：[19:18]；默认值：0；保留。
         */
        uint32_t dma_out_dscr_state: 2;
        /** dma_out_state:RO；比特位置：[22:20]；默认值：0；保留。
         */
        uint32_t dma_out_state: 3;
        /** dma_fifo_full:RO；位位置：[23]；默认值：0；复制DMA FIFO满信号。
         */
        uint32_t dma_fifo_full: 1;
        uint32_t reserved24: 8;
    };
    uint32_t val;
} cp_dma_out_st_reg_t;

/** dma_crc_out寄存器crc结果寄存器的类型
 */
typedef union {
    struct {
        /** dma_crc_result:RO；位位置：[31:0]；默认值：0；该寄存器存储CRC的结果。
         */
        uint32_t dma_crc_result: 32;
    };
    uint32_t val;
} cp_dma_crc_out_reg_t;

/** dma_date寄存器类型复制dma版本寄存器
 */
typedef union {
    struct {
        /** dma_dma_date:R/W；位位置：[31:0]；默认值：403185664；这是版本寄存器。
         */
        uint32_t dma_dma_date: 32;
    };
    uint32_t val;
} cp_dma_date_reg_t;


typedef struct {
    volatile cp_dma_int_raw_reg_t dma_int_raw;
    volatile cp_dma_int_st_reg_t dma_int_st;
    volatile cp_dma_int_ena_reg_t dma_int_ena;
    volatile cp_dma_int_clr_reg_t dma_int_clr;
    volatile cp_dma_out_link_reg_t dma_out_link;
    volatile cp_dma_in_link_reg_t dma_in_link;
    volatile cp_dma_out_eof_des_addr_reg_t dma_out_eof_des_addr;
    volatile cp_dma_in_eof_des_addr_reg_t dma_in_eof_des_addr;
    volatile cp_dma_out_eof_bfr_des_addr_reg_t dma_out_eof_bfr_des_addr;
    volatile cp_dma_inlink_dscr_reg_t dma_inlink_dscr;
    volatile cp_dma_inlink_dscr_bf0_reg_t dma_inlink_dscr_bf0;
    volatile cp_dma_inlink_dscr_bf1_reg_t dma_inlink_dscr_bf1;
    volatile cp_dma_outlink_dscr_reg_t dma_outlink_dscr;
    volatile cp_dma_outlink_dscr_bf0_reg_t dma_outlink_dscr_bf0;
    volatile cp_dma_outlink_dscr_bf1_reg_t dma_outlink_dscr_bf1;
    volatile cp_dma_conf_reg_t dma_conf;
    volatile cp_dma_in_st_reg_t dma_in_st;
    volatile cp_dma_out_st_reg_t dma_out_st;
    volatile cp_dma_crc_out_reg_t dma_crc_out;
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
    volatile cp_dma_date_reg_t dma_date;
} cp_dma_dev_t;

_Static_assert(sizeof(cp_dma_dev_t) == 0x100, "cp_dma_dev_t should occupy 0x100 bytes in memory");

extern cp_dma_dev_t CP_DMA;

#ifdef __cplusplus
}
#endif

