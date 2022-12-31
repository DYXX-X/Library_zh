// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

/*******************************************************************************
 * 注意ll不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// TWAI的低层

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "hal/misc.h"
#include "hal/twai_types.h"
#include "soc/twai_periph.h"
#include "soc/twai_struct.h"

/* -------------------------定义和Typedefs---------------------------*/

#define TWAI_LL_STATUS_RBS      (0x1 << 0)      //接收缓冲区状态
#define TWAI_LL_STATUS_DOS      (0x1 << 1)      //数据超限状态
#define TWAI_LL_STATUS_TBS      (0x1 << 2)      //传输缓冲区状态
#define TWAI_LL_STATUS_TCS      (0x1 << 3)      //变速箱完成状态
#define TWAI_LL_STATUS_RS       (0x1 << 4)      //接收状态
#define TWAI_LL_STATUS_TS       (0x1 << 5)      //传输状态
#define TWAI_LL_STATUS_ES       (0x1 << 6)      //错误状态
#define TWAI_LL_STATUS_BS       (0x1 << 7)      //总线状态
#define TWAI_LL_STATUS_MS       (0x1 << 8)      //未命中状态

#define TWAI_LL_INTR_RI         (0x1 << 0)      //接收中断
#define TWAI_LL_INTR_TI         (0x1 << 1)      //传输中断
#define TWAI_LL_INTR_EI         (0x1 << 2)      //错误中断
//由于硬件特性，软件中不支持数据超限中断
#define TWAI_LL_INTR_EPI        (0x1 << 5)      //错误被动中断
#define TWAI_LL_INTR_ALI        (0x1 << 6)      //仲裁中断中断
#define TWAI_LL_INTR_BEI        (0x1 << 7)      //总线错误中断

/*
 * 以下帧结构具有与TX缓冲器的每个字节几乎相同的位字段布局。这允许在时间关键区域（即ISR）之外对帧进行格式化和解析。ISR所需要做的就是将一个字节一个字节地复制到TX/RX缓冲区，或者从TX/RX缓冲器中复制。TX缓冲器中的两个保留位在帧结构中用于存储self_reception和single_shot标志，这些标志依次指示要执行的传输类型。
 */
typedef union {
    struct {
        struct {
            uint8_t dlc: 4;             //帧的数据长度代码（0到8）
            uint8_t self_reception: 1;  //应使用自接收命令发送此帧
            uint8_t single_shot: 1;     //应使用单发命令传输此帧
            uint8_t rtr: 1;             //此帧是远程传输请求
            uint8_t frame_format: 1;    //框架格式（1=扩展，0=标准）
        };
        union {
            struct {
                uint8_t id[2];          //11位标准帧标识符
                uint8_t data[8];        //数据字节（0到8）
                uint8_t reserved8[2];
            } standard;
            struct {
                uint8_t id[4];          //29位扩展帧标识符
                uint8_t data[8];        //数据字节（0到8）
            } extended;
        };
    };
    uint8_t bytes[13];
} __attribute__((packed)) twai_ll_frame_buffer_t;

_Static_assert(sizeof(twai_ll_frame_buffer_t) == 13, "TX/RX buffer type should be 13 bytes");

/* ----------------------------模式寄存器------------------------------*/

/**
 * @brief   进入重置模式
 *
 * 当处于重置模式时，TWAI控制器与TWAI总线有效断开连接，不会参与任何总线激活。需要重置模式才能写入大多数配置寄存器。
 *
 * @param hw TWAI寄存器的起始地址
 *
 * @note 在BUS OFF条件下自动进入复位模式
 */
static inline void twai_ll_enter_reset_mode(twai_dev_t *hw)
{
    hw->mode_reg.rm = 1;
}

/**
 * @brief   退出重置模式
 *
 * 当不处于重置模式时，TWAI控制器将根据操作模式参与总线活动（例如，发送/接收/确认消息和错误帧）。
 *
 * @param hw TWAI寄存器的起始地址
 *
 * @note 必须退出重置模式才能启动BUS OFF恢复
 */
static inline void twai_ll_exit_reset_mode(twai_dev_t *hw)
{
    hw->mode_reg.rm = 0;
}

/**
 * @brief   检查是否处于重置模式
 * @param hw TWAI寄存器的起始地址
 * @return 如果处于重置模式，则为true
 */
static inline bool twai_ll_is_in_reset_mode(twai_dev_t *hw)
{
    return hw->mode_reg.rm;
}

/**
 * @brief   设置TWAI控制器的操作模式
 *
 * @param hw TWAI寄存器的起始地址
 * @param mode 操作模式
 *
 * @note 必须在重置模式下调用
 */
static inline void twai_ll_set_mode(twai_dev_t *hw, twai_mode_t mode)
{
    if (mode == TWAI_MODE_NORMAL) {           //正常工作模式
        hw->mode_reg.lom = 0;
        hw->mode_reg.stm = 0;
    } else if (mode == TWAI_MODE_NO_ACK) {    //自检模式（无确认）
        hw->mode_reg.lom = 0;
        hw->mode_reg.stm = 1;
    } else if (mode == TWAI_MODE_LISTEN_ONLY) {       //仅侦听模式
        hw->mode_reg.lom = 1;
        hw->mode_reg.stm = 0;
    }
}

/* ---------------------------命令寄存器---------------------------*/

/**
 * @brief   设置TX命令
 *
 * 设置TX命令将导致TWAI控制器尝试发送存储在TX缓冲区中的帧。TX缓冲器将被占用（即锁定），直到TX完成。
 *
 * @param hw TWAI寄存器的起始地址
 *
 * @note 应最后调用传输命令（即，在处理缓冲区释放和清除数据溢出之后），以防止其他命令用0覆盖此锁存的TX位。
 */
static inline void twai_ll_set_cmd_tx(twai_dev_t *hw)
{
    hw->command_reg.tr = 1;
}

/**
 * @brief   设置单发TX命令
 *
 * 类似于设置TX命令，但TWAI控制器不会在出现错误（例如，由于确认错误）时自动重试传输。
 *
 * @param hw TWAI寄存器的起始地址
 *
 * @note 应最后调用传输命令（即，在处理缓冲区释放和清除数据溢出之后），以防止其他命令用0覆盖此锁存的TX位。
 */
static inline void twai_ll_set_cmd_tx_single_shot(twai_dev_t *hw)
{
    hw->command_reg.val = 0x03; //设置command_reg。tr和command_reg。同时用于单次发射请求
}

/**
 * @brief   中止发送
 *
 * 等待发送的帧将被中止。已发送的帧不会被中止。传输完成状态位自动设置为1。类似于设置TX命令，但TWAI控制器不会在出现错误（例如，由于确认错误）时自动重试传输。
 *
 * @param hw TWAI寄存器的起始地址
 *
 * @note 应最后调用传输命令（即，在处理缓冲区释放和清除数据溢出之后），以防止其他命令用0覆盖此锁存的TX位。
 */
static inline void twai_ll_set_cmd_abort_tx(twai_dev_t *hw)
{
    hw->command_reg.at = 1;
}

/**
 * @brief   释放RX缓冲区
 *
 * 将RX缓冲器旋转到RX FIFO中的下一帧。
 *
 * @param hw TWAI寄存器的起始地址
 */
static inline void twai_ll_set_cmd_release_rx_buffer(twai_dev_t *hw)
{
    hw->command_reg.rrb = 1;
}

/**
 * @brief   清除数据超限
 *
 * 清除数据超限状态位
 *
 * @param hw TWAI寄存器的起始地址
 */
static inline void twai_ll_set_cmd_clear_data_overrun(twai_dev_t *hw)
{
    hw->command_reg.cdo = 1;
}

/**
 * @brief   设置自接收单发命令
 *
 * 类似于设置TX命令，但是TWAI控制器也同时接收发送的帧，并且通常用于自检目的。TWAI控制器不会确认收到的消息，因此考虑使用NO_ACK操作模式。
 *
 * @param hw TWAI寄存器的起始地址
 *
 * @note 应最后调用传输命令（即，在处理缓冲区释放和清除数据溢出之后），以防止其他命令用0覆盖此锁存的TX位。
 */
static inline void twai_ll_set_cmd_self_rx_request(twai_dev_t *hw)
{
    hw->command_reg.srr = 1;
}

/**
 * @brief   设置自接收请求命令
 *
 * 类似于设置自接收请求，但TWAI控制器不会在出现错误（例如，由于和确认错误）时自动重试传输。
 *
 * @param hw TWAI寄存器的起始地址
 *
 * @note 应最后调用传输命令（即，在处理缓冲区释放和清除数据溢出之后），以防止其他命令用0覆盖此锁存的TX位。
 */
static inline void twai_ll_set_cmd_self_rx_single_shot(twai_dev_t *hw)
{
    hw->command_reg.val = 0x12; //设置command_reg。srr和command_reg。同时进行单次自接收请求
}

/* ---------------------------状态寄存器------------------------------*/

/**
 * @brief   获取所有状态位
 *
 * @param hw TWAI寄存器的起始地址
 * @return 状态位
 */
static inline uint32_t twai_ll_get_status(twai_dev_t *hw)
{
    return hw->status_reg.val;
}

/**
 * @brief   检查是否设置了RX FIFO超限状态位
 *
 * @param hw TWAI寄存器的起始地址
 * @return 超限状态位
 */
static inline bool twai_ll_is_fifo_overrun(twai_dev_t *hw)
{
    return hw->status_reg.dos;
}

/**
 * @brief   检查先前发送是否成功
 *
 * @param hw TWAI寄存器的起始地址
 * @return 上一次发送是否成功
 */
static inline bool twai_ll_is_last_tx_successful(twai_dev_t *hw)
{
    return hw->status_reg.tcs;
}

/* --------------------------中断寄存器-------------------------*/

/**
 * @brief   获取当前设置的中断
 *
 * 读取中断寄存器将自动清除除接收中断外的所有中断。
 *
 * @param hw TWAI寄存器的起始地址
 * @return 设置中断的位掩码
 */
static inline uint32_t twai_ll_get_and_clear_intrs(twai_dev_t *hw)
{
    return hw->interrupt_reg.val;
}

/* -----------------------中断启用寄存器-----------------------*/

/**
 * @brief   设置启用的中断
 *
 * @param hw TWAI寄存器的起始地址
 * @param Bit 要启用的中断掩码
 *
 * @note 必须在重置模式下调用
 */
static inline void twai_ll_set_enabled_intrs(twai_dev_t *hw, uint32_t intr_mask)
{
    hw->interrupt_enable_reg.val = intr_mask;
}

/* ------------------------总线定时寄存器---------------------------*/

/**
 * @brief   设置总线定时
 *
 * @param hw TWAI寄存器的起始地址
 * @param brp 波特率预分频器
 * @param sjw 同步跳转宽度
 * @param tseg1 计时段1
 * @param tseg2 计时段2
 * @param triple_sampling 三重采样启用/禁用
 *
 * @note 必须在重置模式下调用
 * @note ESP32H2 brp可以是2到32768之间的任意偶数
 */
static inline void twai_ll_set_bus_timing(twai_dev_t *hw, uint32_t brp, uint32_t sjw, uint32_t tseg1, uint32_t tseg2, bool triple_sampling)
{
    hw->bus_timing_0_reg.brp = (brp / 2) - 1;
    hw->bus_timing_0_reg.sjw = sjw - 1;
    hw->bus_timing_1_reg.tseg1 = tseg1 - 1;
    hw->bus_timing_1_reg.tseg2 = tseg2 - 1;
    hw->bus_timing_1_reg.sam = triple_sampling;
}

/* -----------------------------ALC寄存器------------------------------*/

/**
 * @brief   清除仲裁丢失捕获寄存器
 *
 * 读取ALC寄存器重新启动仲裁丢失中断
 *
 * @param hw TWAI寄存器的起始地址
 */
static inline void twai_ll_clear_arb_lost_cap(twai_dev_t *hw)
{
    (void)hw->arbitration_lost_captue_reg.val;
}

/* -----------------------------ECC寄存器------------------------------*/

/**
 * @brief   清除错误代码捕获寄存器
 *
 * 读取ECC寄存器重新启动总线错误中断
 *
 * @param hw TWAI寄存器的起始地址
 */
static inline void twai_ll_clear_err_code_cap(twai_dev_t *hw)
{
    (void)hw->error_code_capture_reg.val;
}

/* -----------------------------EWL寄存器------------------------------*/

/**
 * @brief   设置错误警告限制
 *
 * @param hw TWAI寄存器的起始地址
 * @param ewl 错误警告限制
 *
 * @note 必须在重置模式下调用
 */
static inline void twai_ll_set_err_warn_lim(twai_dev_t *hw, uint32_t ewl)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->error_warning_limit_reg, ewl, ewl);
}

/**
 * @brief   获取错误警告限制
 *
 * @param hw TWAI寄存器的起始地址
 * @return 错误警告限制
 */
static inline uint32_t twai_ll_get_err_warn_lim(twai_dev_t *hw)
{
    return hw->error_warning_limit_reg.val;
}

/* ------------------------RX错误计数寄存器-----------------------*/

/**
 * @brief   获取RX错误计数器
 *
 * @param hw TWAI寄存器的起始地址
 * @return REC值
 *
 * @note REC在复位模式下未冻结。仅听模式将冻结它。BUS OFF条件自动将REC设置为0。
 */
static inline uint32_t twai_ll_get_rec(twai_dev_t *hw)
{
    return hw->rx_error_counter_reg.val;
}

/**
 * @brief   设置RX错误计数器
 *
 * @param hw TWAI寄存器的起始地址
 * @param rec REC值
 *
 * @note 必须在重置模式下调用
 */
static inline void twai_ll_set_rec(twai_dev_t *hw, uint32_t rec)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->rx_error_counter_reg, rxerr, rec);
}

/* ------------------------TX错误计数寄存器-----------------------*/

/**
 * @brief   获取TX错误计数器
 *
 * @param hw TWAI寄存器的起始地址
 * @return TEC值
 *
 * @note BUS OFF（总线关闭）条件将自动将其设置为128
 */
static inline uint32_t twai_ll_get_tec(twai_dev_t *hw)
{
    return hw->tx_error_counter_reg.val;
}

/**
 * @brief   设置TX错误计数器
 *
 * @param hw TWAI寄存器的起始地址
 * @param tec TEC值
 *
 * @note 必须在重置模式下调用
 */
static inline void twai_ll_set_tec(twai_dev_t *hw, uint32_t tec)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->tx_error_counter_reg, txerr, tec);
}

/* ----------------------接受过滤器寄存器------------------------*/

/**
 * @brief   设置接受筛选器
 * @param hw TWAI寄存器的起始地址
 * @param code 验收代码
 * @param mask 接受掩码
 * @param single_filter 是否启用单过滤器模式
 *
 * @note 必须在重置模式下调用
 */
static inline void twai_ll_set_acc_filter(twai_dev_t* hw, uint32_t code, uint32_t mask, bool single_filter)
{
    uint32_t code_swapped = __builtin_bswap32(code);
    uint32_t mask_swapped = __builtin_bswap32(mask);
    for (int i = 0; i < 4; i++) {
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->acceptance_filter.acr[i], byte, ((code_swapped >> (i * 8)) & 0xFF));
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->acceptance_filter.amr[i], byte, ((mask_swapped >> (i * 8)) & 0xFF));
    }
    hw->mode_reg.afm = single_filter;
}

/* -------------------------TX/RX缓冲寄存器---------------------------*/

/**
 * @brief   将格式化的TWAI帧复制到TX缓冲区以进行传输
 *
 * @param hw TWAI寄存器的起始地址
 * @param tx_frame 指向格式化帧的指针
 *
 * @note 调用twai_ll_format_frame_buffer（）格式化帧
 */
static inline void twai_ll_set_tx_buffer(twai_dev_t *hw, twai_ll_frame_buffer_t *tx_frame)
{
    //将格式化帧复制到TX缓冲区
    for (int i = 0; i < 13; i++) {
        hw->tx_rx_buffer[i].val = tx_frame->bytes[i];
    }
}

/**
 * @brief   从RX缓冲区复制接收到的帧以进行分析
 *
 * @param hw TWAI寄存器的起始地址
 * @param rx_frame 指向存储格式化帧的指针
 *
 * @note 调用twai_ll_prase_frame_buffer（）解析格式化的帧
 */
static inline void twai_ll_get_rx_buffer(twai_dev_t *hw, twai_ll_frame_buffer_t *rx_frame)
{
    //将RX缓冲寄存器复制到帧中
    for (int i = 0; i < 13; i++) {
        rx_frame->bytes[i] =  HAL_FORCE_READ_U32_REG_FIELD(hw->tx_rx_buffer[i], byte);
    }
}

/**
 * @brief   将TWAI帧的内容格式化为TX缓冲区的布局
 *
 * 此函数将消息编码为帧结构。帧结构具有与TX缓冲器相同的布局，允许将帧结构直接复制到TX缓冲器中。
 *
 * @param[in] 11bit 或29位ID
 * @param[in] dlc 数据长度代码
 * @param[in] data 指向包含数据的8字节数组的指针。如果没有数据，则为NULL
 * @param[in] format TWAI帧类型
 * @param[in] single_shot 失败时不会重新发送帧
 * @param[in] self_rx 还将同时接收帧
 * @param[out] tx_frame 指向存储格式化帧的指针
 */
static inline void twai_ll_format_frame_buffer(uint32_t id, uint8_t dlc, const uint8_t *data,
                                              uint32_t flags, twai_ll_frame_buffer_t *tx_frame)
{
    bool is_extd = flags & TWAI_MSG_FLAG_EXTD;
    bool is_rtr = flags & TWAI_MSG_FLAG_RTR;

    //设置帧信息
    tx_frame->dlc = dlc;
    tx_frame->frame_format = is_extd;
    tx_frame->rtr = is_rtr;
    tx_frame->self_reception = (flags & TWAI_MSG_FLAG_SELF) ? 1 : 0;
    tx_frame->single_shot = (flags & TWAI_MSG_FLAG_SS) ? 1 : 0;

    //设置ID。ID寄存器是大端的，并且左对齐，因此需要bswap
    if (is_extd) {
        uint32_t id_temp = __builtin_bswap32((id & TWAI_EXTD_ID_MASK) << 3); //（（id<<3）>>8*（3-i））
        for (int i = 0; i < 4; i++) {
            tx_frame->extended.id[i] = (id_temp >> (8 * i)) & 0xFF;
        }
    } else {
        uint32_t id_temp =  __builtin_bswap16((id & TWAI_STD_ID_MASK) << 5); //（（id<<5）>>8*（1-i））
        for (int i = 0; i < 2; i++) {
            tx_frame->standard.id[i] = (id_temp >> (8 * i)) & 0xFF;
        }
    }

    uint8_t *data_buffer = (is_extd) ? tx_frame->extended.data : tx_frame->standard.data;
    if (!is_rtr) {  //仅当帧是数据帧（即，不是远程帧）时复制数据
        for (int i = 0; (i < dlc) && (i < TWAI_FRAME_MAX_DLC); i++) {
            data_buffer[i] = data[i];
        }
    }
}

/**
 * @brief   将格式化的TWAI帧（RX缓冲区布局）解析为其组成内容
 *
 * @param[in] rx_frame 指向格式化帧的指针
 * @param[out] id 11或29位ID
 * @param[out] dlc 数据长度代码
 * @param[out] data 数据剩余字节设置为0。
 * @param[out] format TWAI帧类型
 */
static inline void twai_ll_prase_frame_buffer(twai_ll_frame_buffer_t *rx_frame, uint32_t *id, uint8_t *dlc,
                                             uint8_t *data, uint32_t *flags)
{
    //复制帧信息
    *dlc = rx_frame->dlc;
    uint32_t flags_temp = 0;
    flags_temp |= (rx_frame->frame_format) ? TWAI_MSG_FLAG_EXTD : 0;
    flags_temp |= (rx_frame->rtr) ? TWAI_MSG_FLAG_RTR : 0;
    flags_temp |= (rx_frame->dlc > TWAI_FRAME_MAX_DLC) ? TWAI_MSG_FLAG_DLC_NON_COMP : 0;
    *flags = flags_temp;

    //复制ID。ID寄存器是大端的并左对齐，因此需要bswap
    if (rx_frame->frame_format) {
        uint32_t id_temp = 0;
        for (int i = 0; i < 4; i++) {
            id_temp |= rx_frame->extended.id[i] << (8 * i);
        }
        id_temp = __builtin_bswap32(id_temp) >> 3;  //（（字节[i]<<8*（3-i））>>3）
        *id = id_temp & TWAI_EXTD_ID_MASK;
    } else {
        uint32_t id_temp = 0;
        for (int i = 0; i < 2; i++) {
            id_temp |= rx_frame->standard.id[i] << (8 * i);
        }
        id_temp = __builtin_bswap16(id_temp) >> 5;  //（（字节[i]<<8*（1-i））>>5）
        *id = id_temp & TWAI_STD_ID_MASK;
    }

    uint8_t *data_buffer = (rx_frame->frame_format) ? rx_frame->extended.data : rx_frame->standard.data;
    //仅当帧是数据帧（即，不是远程帧）时复制数据
    int data_length = (rx_frame->rtr) ? 0 : ((rx_frame->dlc > TWAI_FRAME_MAX_DLC) ? TWAI_FRAME_MAX_DLC : rx_frame->dlc);
    for (int i = 0; i < data_length; i++) {
        data[i] = data_buffer[i];
    }
    //将数据的剩余字节设置为0
    for (int i = data_length; i < TWAI_FRAME_MAX_DLC; i++) {
        data[i] = 0;
    }
}

/* -----------------------RX消息计数寄存器-----------------------*/

/**
 * @brief   获取RX消息计数器
 *
 * @param hw TWAI寄存器的起始地址
 * @return RX消息计数器
 */
static inline uint32_t twai_ll_get_rx_msg_count(twai_dev_t *hw)
{
    return hw->rx_message_counter_reg.val;
}

/* -------------------------时钟分频器寄存器-----------------------*/

/**
 * @brief   设置CLKOUT除法器并启用/禁用
 *
 * 配置CLKOUT。CLKOUT是APB CLK的预缩放版本。除法器可以是1，也可以是2到490之间的任何偶数。将除法器设置为0以禁用CLKOUT。
 *
 * @param hw TWAI寄存器的起始地址
 * @param divider CLKOUT除法器（2到490之间的任何偶数）。设置为0以禁用CLKOUT
 */
static inline void twai_ll_set_clkout(twai_dev_t *hw, uint32_t divider)
{
    if (divider >= 2 && divider <= 490) {
        hw->clock_divider_reg.co = 0;
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clock_divider_reg, cd, (divider / 2) - 1);
    } else if (divider == 1) {
        //将除法器reg设置为最大值（255）表示除法器为1
        hw->clock_divider_reg.co = 0;
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clock_divider_reg, cd, 255);
    } else {
        hw->clock_divider_reg.co = 1;
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clock_divider_reg, cd, 0);
    }
}

#ifdef __cplusplus
}
#endif

