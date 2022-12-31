// 版权所有2019 Espressif Systems（上海）私人有限公司
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
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef volatile struct emac_dma_dev_s {
    union {
        struct {
            uint32_t sw_rst : 1;         /*当设置该位时，MAC DMA控制器重置MAC的逻辑和所有内部寄存器。在所有ETH_ C时钟域中完成重置操作后，将自动清除。在重新编程ETH_ C的任何寄存器之前，您应该读取该位中的零（0）值。*/
            uint32_t dma_arb_sch : 1;    /*该位指定发送和接收路径之间的仲裁方案。1’b0：在PR中指定RX:TX或TX:RX优先级的加权循环（位[15:14]）。1’b1固定优先级（Rx优先于Tx）。*/
            uint32_t desc_skip_len : 5;  /*该位指定在两个非约束描述符之间跳过的单词数。地址跳过从当前描述符的结尾开始到下一个描述符的开头。当DSL（DESC_SKIP_LEN）值等于零时，DMA在环形模式中将描述符表视为连续的。*/
            uint32_t alt_desc_size : 1;  /*设置后，备用描述符的大小将增加到32字节。*/
            uint32_t prog_burst_len : 6; /*这些位指示在一个DMA事务中要传输的最大节拍数。如果要传输的心跳数超过32，则执行以下步骤：1.设置PBLx8模式2.设置PBL（PROG_BURST_LEN）。*/
            uint32_t pri_ratio : 2;      /*这些比特控制Rx DMA和Tx DMA之间的加权循环仲裁中的优先级比。这些位仅在位1（DA）复位时有效。由每个比特表示的优先级比Rx:Tx：2’b00--1:1 2’b01--2:0 2’b10--3:1 2’b11--4:1*/
            uint32_t fixed_burst : 1;    /*该位控制AHB主接口是否执行固定突发传输。设置后，AHB接口在正常突发传输开始时仅使用SINGLE INCR4 INCR8或INCR16。复位时，AHB接口使用SINGLE和INCR突发传输操作。*/
            uint32_t rx_dma_pbl : 6;     /*此字段指示一个Rx DMA事务中要传输的最大拍数。这是单块读取或写入中使用的最大值。每当Rx DMA在主机总线上开始突发传输时，它总是尝试按照RPBL（Rx_DMA_PBL）位中的规定进行突发。您可以使用值1 2 4 8 16和32对RPBL进行编程。任何其他值都会导致未定义的行为。此字段仅在USP（USE_SEP_PBL）设置为高时有效且适用。*/
            uint32_t use_sep_pbl : 1;    /*当设置为高时，该位将Rx DMA配置为使用位[22:17]中配置的值作为PBL。位[13:8]中的PBL值仅适用于Tx DMA操作。当重置为低时，位[13:8]中的PBL值适用于两个DMA引擎。*/
            uint32_t pblx8_mode : 1;     /*当设置为高时，该位将编程的PBL值（位[22:17]和位[13:8]）乘以八倍。因此，DMA根据PBL值以8 16 32 64 128和256拍传送数据。*/
            uint32_t dmaaddralibea : 1;  /*当该位设置为高且FIXED_BURST位为1时，AHB接口生成与起始地址LS位对齐的所有突发。如果FIXED_BURST位为0，则第一个脉冲串（访问数据缓冲器的起始地址）不对齐，但随后的脉冲串与该地址对齐。*/
            uint32_t dmamixedburst : 1;  /*当该位设置为高且FIXED_BURST位为低时，AHB主接口启动长度大于16的所有突发（INCR（未定义突发），而对于长度小于等于16的突发，其恢复为固定突发传输（INCRx和SINGLE）。*/
            uint32_t reserved27 : 1;
            uint32_t reserved28 : 2;
            uint32_t reserved30 : 1;
            uint32_t reserved31 : 1;
        };
        uint32_t val;
    } dmabusmode;
    uint32_t dmatxpolldemand; /*当用任何值写入这些位时，DMA读取寄存器（当前主机传输描述符寄存器）所指向的当前描述符。如果该描述符不可用（由主机拥有），则传输返回到挂起状态，状态寄存器的位[2]（TU）被断言。如果描述符可用，则恢复传输。*/
    uint32_t dmarxpolldemand; /*当用任何值写入这些位时，DMA读取当前主机接收描述符寄存器所指向的当前描述符。如果该描述符不可用（由主机拥有），则接收返回到挂起状态，状态寄存器的位[7]（RU）被断言。如果描述符可用，则Rx DMA返回到活动状态。*/
    uint32_t dmarxbaseaddr;   /*此字段包含接收描述符列表中第一个描述符的基地址。LSB位[1:0]被忽略，DMA内部将其取为全零。因此，这些LSB位是只读的。*/
    uint32_t dmatxbaseaddr;   /*此字段包含传输描述符列表中第一个描述符的基地址。LSB位[1:0]被忽略，DMA内部将其视为全零。因此，这些LSB位是只读的。*/
    union {
        struct {
            uint32_t trans_int : 1;         /*该位指示帧传输完成。当传输完成时，TDES0的比特[31]（OWN）被重置，并且特定帧状态信息在描述符中被更新。*/
            uint32_t trans_proc_stop : 1;   /*该位在传输停止时设置。*/
            uint32_t trans_buf_unavail : 1; /*此位表示主机拥有传输列表中的下一个描述符，DMA无法获取该描述符。传输被暂停。位[22:20]解释传输过程状态转换。要继续处理传输描述符，主机应通过设置TDES0[31]更改描述符的所有权，然后发出传输轮询请求命令。*/
            uint32_t trans_jabber_to : 1;   /*此位表示传输Jabber计时器已过期，当帧大小超过2048（启用Jumbo帧时为10 240字节）时，会发生这种情况。当Jabber超时发生时，传输过程被中止并处于停止状态。这会导致Transmit Jabber Timeout TDES0[14]标志生效。*/
            uint32_t recv_ovflow : 1;       /*此位表示接收缓冲区在帧接收期间发生溢出。如果部分帧被传输到应用程序，则在RDES0[11]中设置溢出状态。*/
            uint32_t trans_undflow : 1;     /*该位表示在帧传输期间，传输缓冲区存在欠流。传输暂停，并设置欠流错误TDES0[1]。*/
            uint32_t recv_int : 1;          /*该位表示帧接收完成。当接收完成时，RDES1（完成时禁用中断）的位[31]在最后一个描述符中被重置，并且特定帧状态信息在描述符中被更新。接收保持在运行状态。*/
            uint32_t recv_buf_unavail : 1;  /*此位表示主机拥有接收列表中的下一个描述符，DMA无法获取该描述符。接收进程被挂起。要继续处理接收描述符，主机应更改描述符的所有权并发出接收轮询请求命令。如果没有发出接收轮询请求，则在接收到下一个识别的传入帧时，接收过程将继续。仅当DMA拥有前一个接收描述符时，才设置此位。*/
            uint32_t recv_proc_stop : 1;    /*当接收进程进入停止状态时，该位被断言。*/
            uint32_t recv_wdt_to : 1;       /*当设置此位时，表示接收看门狗定时器在接收当前帧时过期，并且在看门狗超时后当前帧被截断。*/
            uint32_t early_trans_int : 1;   /*该位表示要传输的帧已完全传输到MTL传输FIFO。*/
            uint32_t reserved11 : 2;
            uint32_t fatal_bus_err_int : 1; /*该位表示发生了位[25:23]中所述的总线错误。当设置该位时，相应的DMA引擎禁用其所有总线访问。*/
            uint32_t early_recv_int : 1;    /*该位指示DMA填充了数据包的第一数据缓冲区。当软件向该位写入1或设置该寄存器的位[6]（RI）时（以较早发生的为准），该位被清除。*/
            uint32_t abn_int_summ : 1;      /*异常中断摘要位值是在中断启用寄存器中启用相应中断位时的以下逻辑或：位[1]：传输进程已停止。Bit[3]：传输Jabber超时。Bit[4]：接收FIFO溢出。Bit[5]：传输欠流。位[7]：接收缓冲区不可用。Bit[8]：接收进程已停止。Bit[9]：接收看门狗超时。Bit[10]：早期传输中断。Bit[13]：严重总线错误。只有未屏蔽的位才会影响异常中断摘要位。这是一个粘性位，每次清除导致设置AIS的相应位时，必须清除（通过向该位写入1）。*/
            uint32_t norm_int_summ : 1;     /*正常中断摘要位值是在中断启用寄存器中启用相应中断位时以下位的逻辑或：位[0]：传输中断。Bit[2]：传输缓冲区不可用。Bit[6]：接收中断。Bit[14]：早期接收中断。只有未屏蔽的位才会影响正常中断摘要位。这是一个粘性位，每次清除导致设置NIS的相应位时，都必须清除（通过向该位写入1）。*/
            uint32_t recv_proc_state : 3;   /*此字段指示接收DMA FSM状态。此字段不会生成中断。3'b000:停止。发出重置或停止接收命令。3'b001：正在运行。正在获取接收传输描述符。2010年3月：保留供将来使用。2011年3月：正在运行。正在等待RX数据包。3'b100：暂停。接收描述符不可用。3'b101：正在运行。正在关闭接收描述符。3'b110:TIME_STAMP写入状态。3'b111：正在运行。将TX分组数据从接收缓冲器传输到主机存储器。*/
            uint32_t trans_proc_state : 3;  /*此字段表示传输DMA FSM状态。此字段不会生成中断。3'b000:停止。发出重置或停止传输命令。3'b001：正在运行。正在获取传输传输描述符。2010年3月：保留供将来使用。2011年3月：正在运行。正在等待TX数据包。3'b100：暂停。接收描述符不可用。3'b101：正在运行。正在关闭传输描述符。3'b110:TIME_STAMP写入状态。3'b111：正在运行。将TX分组数据从传输缓冲器传输到主机存储器。*/
            uint32_t error_bits : 3;        /*此字段指示导致总线错误的错误类型，例如AHB接口上的错误响应。此字段仅在设置Bit[13]（FBI）时有效。此字段不会生成中断。3'b000:Rx DMA写入数据传输期间出错。3'b011:Tx DMA读取数据传输期间出错。3'b100：Rx DMA描述符写入访问期间出错。3'b101：Tx DMA描述符写入访问期间出错。3'b110：Rx DMA描述符读取访问期间出错。3'b111:Tx DMA描述符读取访问期间出错。*/
            uint32_t reserved26 : 1;
            uint32_t reserved27 : 1;
            uint32_t pmt_int : 1;    /*该位表示ETH_ C的PMT模块中的中断事件。软件必须读取MAC中的PMT控制和状态寄存器，以获得中断的确切原因，并清除其源，将该位重置为1’b0。*/
            uint32_t ts_tri_int : 1; /*该位指示ETH_MAC的时间戳生成器块中的中断事件。软件必须读取ETH_ C中的相应寄存器，以获得中断的确切原因，并清除其源，将该位重置为1’b0。*/
            uint32_t reserved30 : 1;
            uint32_t reserved31 : 1;
        };
        uint32_t val;
    } dmastatus;
    union {
        struct {
            uint32_t reserved0 : 1;
            uint32_t start_stop_rx : 1;    /*设置此位后，接收进程将处于运行状态。DMA尝试从接收列表获取描述符并处理传入帧。当该位被清除时，Rx DMA操作在传输当前帧之后停止。*/
            uint32_t opt_second_frame : 1; /*当设置该位时，它指示DMA甚至在获得第一帧的状态之前处理传输数据的第二帧。*/
            uint32_t rx_thresh_ctrl : 2;   /*这两位控制MTL接收FIFO的阈值电平。当MTL接收FIFO内的帧大小大于阈值时，开始向DMA传输（请求）。2英尺00:64，2英尺01:32，2英尺10:96，2英尺11:128。*/
            uint32_t drop_gfrm : 1;        /*当设置时，MAC将接收到的巨型帧丢弃在Rx FIFO中，即大于计算出的巨型帧限制的帧。*/
            uint32_t fwd_under_gf : 1;     /*当设置时，Rx FIFO转发尺寸不足的帧（即无错误且长度小于64字节的帧），包括填充字节和CRC。*/
            uint32_t fwd_err_frame : 1;    /*重置此位时，Rx FIFO丢弃具有错误状态的帧（CRC错误冲突错误巨型帧看门狗超时或溢出）。*/
            uint32_t reserved8 : 1;
            uint32_t reserved9 : 2;
            uint32_t reserved11 : 2;
            uint32_t start_stop_transmission_command : 1; /*当该位被设置时，传输被置于运行状态，DMA检查当前位置的传输列表中要传输的帧。当该位被复位时，在完成当前帧的传输之后，传输过程被置于停止状态。*/
            uint32_t tx_thresh_ctrl : 3;                  /*这些位控制MTL传输FIFO的阈值电平。当MTL传输FIFO内的帧大小大于阈值时，传输开始。此外，还发送长度小于阈值的完整帧。这些位仅在Tx_Str_fwd复位时使用。3'b000:64 3'b001:128 3'b010:192 3'b011:256 3'b100:40 3'b10:32 3'b110:24 3'b111:16。*/
            uint32_t reserved17 : 3;
            uint32_t flush_tx_fifo : 1; /*当该位被设置时，发送FIFO控制器逻辑被重置为其默认值，因此Tx FIFO中的所有数据都丢失或刷新。冲洗操作完成后，该位在内部清除。*/
            uint32_t tx_str_fwd : 1;    /*设置此位后，当MTL传输FIFO中存在完整帧时，传输开始。设置此位时，忽略Tx_Thresh_Ctrl中指定的Tx_Threth_Ctrl值。*/
            uint32_t reserved22 : 1;
            uint32_t reserved23 : 1;
            uint32_t dis_flush_recv_frames : 1;   /*当设置此位时，由于接收描述符或缓冲区不可用，Rx DMA不刷新任何帧。*/
            uint32_t rx_store_forward : 1;        /*当该位被设置时，MTL仅在完整帧被写入之后才从Rx FIFO读取帧。*/
            uint32_t dis_drop_tcpip_err_fram : 1; /*当设置此位时，MAC不会丢弃仅具有由接收校验和引擎检测到的错误的帧。重置此位时，如果Fwd_Err_Frame位被重置，则所有错误帧都将被丢弃。*/
            uint32_t reserved27 : 5;
        };
        uint32_t val;
    } dmaoperation_mode;
    union {
        struct {
            uint32_t dmain_tie : 1;  /*当该位设置为正常中断摘要启用（位[16]）时，传输中断被启用。重置此位时，传输中断被禁用。*/
            uint32_t dmain_tse : 1;  /*当该位设置为异常中断摘要启用（位[15]）时，传输停止中断被启用。当重置该位时，传输停止中断被禁用。*/
            uint32_t dmain_tbue : 1; /*当该位设置为正常中断摘要启用（位16）时，传输缓冲区不可用中断被启用。重置此位时，传输缓冲区不可用中断被禁用。*/
            uint32_t dmain_tjte : 1; /*当该位设置为“异常中断摘要启用”（位[15]）时，将启用“发送Jabber超时中断”。当重置此位时，传输Jabber超时中断被禁用。*/
            uint32_t dmain_oie : 1;  /*当该位设置为异常中断摘要启用（位[15]）时，接收溢出中断被启用。重置此位时，溢出中断被禁用。*/
            uint32_t dmain_uie : 1;  /*当该位设置为异常中断摘要启用（位[15]）时，传输欠流中断启用。重置此位时，欠流中断被禁用。*/
            uint32_t dmain_rie : 1;  /*当该位设置为正常中断摘要启用（位[16]）时，接收中断被启用。重置此位时，接收中断被禁用。*/
            uint32_t dmain_rbue : 1; /*当该位设置为异常中断摘要启用（位[15]）时，接收缓冲区不可用中断被启用。重置此位时，接收缓冲区不可用中断被禁用。*/
            uint32_t dmain_rse : 1;  /*当该位设置为异常中断摘要启用（位[15]）时，接收停止中断被启用。重置此位时，接收停止中断被禁用。*/
            uint32_t dmain_rwte : 1; /*当该位设置为异常中断摘要启用（位[15]）时，接收看门狗超时中断被启用。重置此位时，接收看门狗超时中断被禁用。*/
            uint32_t dmain_etie : 1; /*当该位设置为异常中断摘要启用（位[15]）时，启用早期传输中断。当重置该位时，早期传输中断被禁用。*/
            uint32_t reserved11 : 2;
            uint32_t dmain_fbee : 1; /*当该位设置为异常中断摘要启用（位[15]）时，将启用致命总线错误中断。重置此位时，禁用致命总线错误启用中断。*/
            uint32_t dmain_erie : 1; /*当该位设置为正常中断摘要启用（位[16]）时，启用早期接收中断。当该位复位时，早期接收中断被禁用。*/
            uint32_t dmain_aise : 1; /*当设置该位时，启用异常中断汇总。当该位复位时，异常中断汇总被禁用。此位启用状态寄存器中的以下中断：位[1]：传输进程已停止。Bit[3]：传输Jabber超时。Bit[4]：接收溢出。Bit[5]：传输欠流。位[7]：接收缓冲区不可用。Bit[8]：接收进程已停止。Bit[9]：接收看门狗超时。Bit[10]：早期传输中断。Bit[13]：严重总线错误。*/
            uint32_t dmain_nise : 1; /*设置此位时，启用正常中断汇总。当该位复位时，正常中断汇总被禁用。此位启用状态寄存器中的以下中断：位[0]：传输中断。Bit[2]：传输缓冲区不可用。Bit[6]：接收中断。Bit[14]：早期接收中断。*/
            uint32_t reserved17 : 15;
        };
        uint32_t val;
    } dmain_en;
    union {
        struct {
            uint32_t missed_fc : 16;    /*此字段指示控制器由于主机接收缓冲区不可用而丢失的帧数。每次DMA丢弃传入帧时，此计数器都会递增。读取此寄存器时，计数器被清除。*/
            uint32_t overflow_bmfc : 1; /*每当Missed Frame Counter（Bits[15:0]）溢出时，即DMA丢弃传入帧，因为主机接收缓冲区不可用，而Missed Frame计数器处于最大值时，设置此位。在这种情况下，Missed帧计数器被重置为全零，该位表示发生了翻转。*/
            uint32_t overflow_fc : 11;  /*此字段指示应用程序错过的帧数。每次MTL FIFO溢出时，此计数器递增。读取此寄存器时，计数器被清除。*/
            uint32_t overflow_bfoc : 1; /*每当溢出帧计数器（位[27:17]）溢出时，即Rx FIFO溢出，溢出帧计数器处于最大值时，设置该位。在这种情况下，溢出帧计数器被重置为全零，该位表示发生了翻转。*/
            uint32_t reserved29 : 3;
        };
        uint32_t val;
    } dmamissedfr;
    union {
        struct {
            uint32_t riwtc : 8; /*该位表示设置看门狗定时器的系统时钟周期数乘以256。在Rx DMA完成帧的传输后，看门狗定时器被编程值触发，因为相应描述符RDES1[31]中的设置，未设置RI（RECV_INT）状态位。当看门狗计时器用完时，设置RI位并停止计时器。由于根据任何接收帧的RDES1[31]自动设置RI，当RI位设置为高时，看门狗定时器复位。*/
            uint32_t reserved8 : 24;
        };
        uint32_t val;
    } dmarintwdtimer;
    uint32_t reserved_28;
    uint32_t reserved_2c;
    uint32_t reserved_30;
    uint32_t reserved_34;
    uint32_t reserved_38;
    uint32_t reserved_3c;
    uint32_t reserved_40;
    uint32_t reserved_44;
    uint32_t dmatxcurrdesc;     /*当前接收描述符列表的地址。重置时清除。DMA在操作期间更新了指针。*/
    uint32_t dmarxcurrdesc;     /*当前接收描述符列表的地址。重置时清除。DMA在操作期间更新了指针。*/
    uint32_t dmatxcurraddr_buf; /*当前接收描述符列表的地址。重置时清除。DMA在操作期间更新了指针。*/
    uint32_t dmarxcurraddr_buf; /*当前接收描述符列表的地址。重置时清除。DMA在操作期间更新了指针。*/
} emac_dma_dev_t;

extern emac_dma_dev_t EMAC_DMA;

#ifdef __cplusplus
}
#endif

