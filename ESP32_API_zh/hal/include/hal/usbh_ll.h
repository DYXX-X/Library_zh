/*
 * SPDX文件版权所有文本：2020-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "soc/usbh_struct.h"
#include "hal/usb_types_private.h"
#include "hal/misc.h"


/* -----------------------------------------------------------------------------
-------------------------------全局寄存器-------------------------------
----------------------------------------------------------------------------- */

/*
 * GINTSTS和GINTMSK寄存器的中断位掩码
 */
#define USB_LL_INTR_CORE_WKUPINT        (1 << 31)
#define USB_LL_INTR_CORE_SESSREQINT     (1 << 30)
#define USB_LL_INTR_CORE_DISCONNINT     (1 << 29)
#define USB_LL_INTR_CORE_CONIDSTSCHNG   (1 << 28)
#define USB_LL_INTR_CORE_PTXFEMP        (1 << 26)
#define USB_LL_INTR_CORE_HCHINT         (1 << 25)
#define USB_LL_INTR_CORE_PRTINT         (1 << 24)
#define USB_LL_INTR_CORE_RESETDET       (1 << 23)
#define USB_LL_INTR_CORE_FETSUSP        (1 << 22)
#define USB_LL_INTR_CORE_INCOMPIP       (1 << 21)
#define USB_LL_INTR_CORE_INCOMPISOIN    (1 << 20)
#define USB_LL_INTR_CORE_OEPINT         (1 << 19)
#define USB_LL_INTR_CORE_IEPINT         (1 << 18)
#define USB_LL_INTR_CORE_EPMIS          (1 << 17)
#define USB_LL_INTR_CORE_EOPF           (1 << 15)
#define USB_LL_INTR_CORE_ISOOUTDROP     (1 << 14)
#define USB_LL_INTR_CORE_ENUMDONE       (1 << 13)
#define USB_LL_INTR_CORE_USBRST         (1 << 12)
#define USB_LL_INTR_CORE_USBSUSP        (1 << 11)
#define USB_LL_INTR_CORE_ERLYSUSP       (1 << 10)
#define USB_LL_INTR_CORE_GOUTNAKEFF     (1 << 7)
#define USB_LL_INTR_CORE_GINNAKEFF      (1 << 6)
#define USB_LL_INTR_CORE_NPTXFEMP       (1 << 5)
#define USB_LL_INTR_CORE_RXFLVL         (1 << 4)
#define USB_LL_INTR_CORE_SOF            (1 << 3)
#define USB_LL_INTR_CORE_OTGINT         (1 << 2)
#define USB_LL_INTR_CORE_MODEMIS        (1 << 1)
#define USB_LL_INTR_CORE_CURMOD         (1 << 0)

/*
 * HPRT寄存器的中断生成位的位掩码。这些位被“或”运算到USB_LL_INTR_CORE_PRINT中断中。
 *
 * 注意：HPRT的某些字段是W1C（写1清除），这是我们无法执行简单的读写回操作来清除HPRT中断位的。相反，我们需要一个W1C掩码非中断相关位
 */
#define USBH_LL_HPRT_W1C_MSK                (0x2E)
#define USBH_LL_HPRT_ENA_MSK                (0x04)
#define USBH_LL_INTR_HPRT_PRTOVRCURRCHNG    (1 << 5)
#define USBH_LL_INTR_HPRT_PRTENCHNG         (1 << 3)
#define USBH_LL_INTR_HPRT_PRTCONNDET        (1 << 1)

/*
 * 通道中断的位掩码（HCINTi和HCINTMSKi寄存器）
 *
 * 注意：在分散/聚集DMA模式下，只能取消屏蔽以下中断
 * - DESC_LS_ROLL
 * -XCS_XACT_ERR（始终未屏蔽）
 * - BNAINTR
 * - CHHLTD
 * -XFERCOMPL剩余的中断位仍将被设置（当相应事件发生时），但不会产生中断。因此，我们必须通过USBH_LL_INTR_CHAN_CHHLTD中断代理来检查其他中断位。
 */
#define USBH_LL_INTR_CHAN_DESC_LS_ROLL      (1 << 13)
#define USBH_LL_INTR_CHAN_XCS_XACT_ERR      (1 << 12)
#define USBH_LL_INTR_CHAN_BNAINTR           (1 << 11)
#define USBH_LL_INTR_CHAN_DATATGLERR        (1 << 10)
#define USBH_LL_INTR_CHAN_FRMOVRUN          (1 << 9)
#define USBH_LL_INTR_CHAN_BBLEER            (1 << 8)
#define USBH_LL_INTR_CHAN_XACTERR           (1 << 7)
#define USBH_LL_INTR_CHAN_NYET              (1 << 6)
#define USBH_LL_INTR_CHAN_ACK               (1 << 5)
#define USBH_LL_INTR_CHAN_NAK               (1 << 4)
#define USBH_LL_INTR_CHAN_STALL             (1 << 3)
#define USBH_LL_INTR_CHAN_AHBERR            (1 << 2)
#define USBH_LL_INTR_CHAN_CHHLTD            (1 << 1)
#define USBH_LL_INTR_CHAN_XFERCOMPL         (1 << 0)

/*
 * 分散/聚集DMA模式中使用的QTD（队列传输描述符）结构。每个QTD描述一次转移。分散收集模式将自动将传输拆分为多个MPS数据包。每个QTD的大小为64位
 *
 * 注：QTD的状态信息部分根据IN或OUT以及ISO或非ISO进行不同的解释
 */
typedef struct {
    union {
        struct {
            uint32_t xfer_size: 17;
            uint32_t aqtd_offset: 6;
            uint32_t aqtd_valid: 1;
            uint32_t reserved_24: 1;
            uint32_t intr_cplt: 1;
            uint32_t eol: 1;
            uint32_t reserved_27: 1;
            uint32_t rx_status: 2;
            uint32_t reserved_30: 1;
            uint32_t active: 1;
        } in_non_iso;
        struct {
            uint32_t xfer_size: 12;
            uint32_t reserved_12_24: 13;
            uint32_t intr_cplt: 1;
            uint32_t reserved_26_27: 2;
            uint32_t rx_status: 2;
            uint32_t reserved_30: 1;
            uint32_t active: 1;
        } in_iso;
        struct {
            uint32_t xfer_size: 17;
            uint32_t reserved_17_23: 7;
            uint32_t is_setup: 1;
            uint32_t intr_cplt: 1;
            uint32_t eol: 1;
            uint32_t reserved_27: 1;
            uint32_t tx_status: 2;
            uint32_t reserved_30: 1;
            uint32_t active: 1;
        } out_non_iso;
        struct {
            uint32_t xfer_size: 12;
            uint32_t reserved_12_24: 13;
            uint32_t intr_cplt: 1;
            uint32_t eol: 1;
            uint32_t reserved_27: 1;
            uint32_t tx_status: 2;
            uint32_t reserved_30: 1;
            uint32_t active: 1;
        } out_iso;
        uint32_t buffer_status_val;
    };
    uint8_t *buffer;
} usbh_ll_dma_qtd_t;


/* -----------------------------------------------------------------------------
-------------------------------全局寄存器-------------------------------
----------------------------------------------------------------------------- */

// ---------------------------GAHBCFG寄存器--------------------------------

static inline void usb_ll_en_dma_mode(usbh_dev_t *hw)
{
    hw->gahbcfg_reg.dmaen = 1;
}

static inline void usb_ll_en_slave_mode(usbh_dev_t *hw)
{
    hw->gahbcfg_reg.dmaen = 0;
}

static inline void usb_ll_set_hbstlen(usbh_dev_t *hw, uint32_t burst_len)
{
    hw->gahbcfg_reg.hbstlen = burst_len;
}

static inline void usb_ll_en_global_intr(usbh_dev_t *hw)
{
    hw->gahbcfg_reg.glbllntrmsk = 1;
}

static inline void usb_ll_dis_global_intr(usbh_dev_t *hw)
{
    hw->gahbcfg_reg.glbllntrmsk = 0;
}

// ---------------------------GUSBCFG寄存器--------------------------------

static inline void usb_ll_set_host_mode(usbh_dev_t *hw)
{
    hw->gusbcfg_reg.forcehstmode = 1;
}

static inline void usb_ll_dis_hnp_cap(usbh_dev_t *hw)
{
    hw->gusbcfg_reg.hnpcap = 0;
}

static inline void usb_ll_dis_srp_cap(usbh_dev_t *hw)
{
    hw->gusbcfg_reg.srpcap = 0;
}

// ---------------------------GRSTCTL寄存器--------------------------------

static inline bool usb_ll_check_ahb_idle(usbh_dev_t *hw)
{
    return hw->grstctl_reg.ahbidle;
}

static inline bool usb_ll_check_dma_req_in_progress(usbh_dev_t *hw)
{
    return hw->grstctl_reg.dmareq;
}

static inline void usb_ll_flush_nptx_fifo(usbh_dev_t *hw)
{
    hw->grstctl_reg.txfnum = 0;     //将TX FIFO编号设置为0以选择非周期性TX FIFO
    hw->grstctl_reg.txfflsh = 1;    //刷新选定的TX FIFO
    //等待冲洗完成
    while (hw->grstctl_reg.txfflsh) {
        ;
    }
}

static inline void usb_ll_flush_ptx_fifo(usbh_dev_t *hw)
{
    hw->grstctl_reg.txfnum = 1;     //将TX FIFO编号设置为1以选择周期性TX FIFO
    hw->grstctl_reg.txfflsh = 1;    //F按下选择的TX FIFO
    //等待冲洗完成
    while (hw->grstctl_reg.txfflsh) {
        ;
    }
}

static inline void usb_ll_flush_rx_fifo(usbh_dev_t *hw)
{
    hw->grstctl_reg.rxfflsh = 1;
    //等待冲洗完成
    while (hw->grstctl_reg.rxfflsh) {
        ;
    }
}

static inline void usb_ll_reset_frame_counter(usbh_dev_t *hw)
{
    hw->grstctl_reg.frmcntrrst = 1;
}

static inline void usb_ll_core_soft_reset(usbh_dev_t *hw)
{
    hw->grstctl_reg.csftrst = 1;
}

static inline bool usb_ll_check_core_soft_reset(usbh_dev_t *hw)
{
    return hw->grstctl_reg.csftrst;
}

// ---------------------------GINTSTS寄存器--------------------------------

/**
 * @brief 读取并清除全局中断寄存器
 *
 * @param hw DWC_OTG寄存器的起始地址
 * @return uint32_t中断掩码
 */
static inline uint32_t usb_ll_intr_read_and_clear(usbh_dev_t *hw)
{
    usb_gintsts_reg_t gintsts;
    gintsts.val = hw->gintsts_reg.val;
    hw->gintsts_reg.val = gintsts.val;  //写回以清除
    return gintsts.val;
}

/**
 * @brief 清除特定中断
 *
 * @param hw DWC_OTG寄存器的起始地址
 * @param intr_msk 要清除的中断掩码
 */
static inline void usb_ll_intr_clear(usbh_dev_t *hw, uint32_t intr_msk)
{
    //所有GINTSTS字段都是W1C或只读。直接写很安全
    hw->gintsts_reg.val = intr_msk;
}

// ---------------------------GINTMSK寄存器--------------------------------

static inline void usb_ll_en_intrs(usbh_dev_t *hw, uint32_t intr_mask)
{
    hw->gintmsk_reg.val |= intr_mask;
}

static inline void usb_ll_dis_intrs(usbh_dev_t *hw, uint32_t intr_mask)
{
    hw->gintmsk_reg.val &= ~intr_mask;
}

// ---------------------------GRXFSIZ寄存器--------------------------------

static inline void usb_ll_set_rx_fifo_size(usbh_dev_t *hw, uint32_t num_lines)
{
    //设置文字大小
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->grxfsiz_reg, rxfdep, num_lines);
}

// --------------------------GNPTXFSIZ寄存器-------------------------------

static inline void usb_ll_set_nptx_fifo_size(usbh_dev_t *hw, uint32_t addr, uint32_t num_lines)
{
    usb_gnptxfsiz_reg_t gnptxfsiz;
    gnptxfsiz.val = hw->gnptxfsiz_reg.val;
    HAL_FORCE_MODIFY_U32_REG_FIELD(gnptxfsiz, nptxfstaddr, addr);
    HAL_FORCE_MODIFY_U32_REG_FIELD(gnptxfsiz, nptxfdep, num_lines);
    hw->gnptxfsiz_reg.val = gnptxfsiz.val;
}

static inline uint32_t usb_ll_get_controller_core_id(usbh_dev_t *hw)
{
    return hw->gsnpsid_reg.val;
}

/**
 * @brief 获取DWC_OTG控制器的硬件配置注册表
 *
 * 硬件配置寄存器是只读的，指示DWC_OTG核心的各种功能。
 *
 * @param hw DWC_OTG寄存器的起始地址
 * @param[out] ghwcfg1 硬件配置寄存器1
 * @param[out] ghwcfg2 硬件配置寄存器2
 * @param[out] ghwcfg3 硬件配置寄存器3
 * @param[out] ghwcfg4 硬件配置寄存器4
 */
static inline void usb_ll_get_hardware_config(usbh_dev_t *hw, uint32_t *ghwcfg1, uint32_t *ghwcfg2, uint32_t *ghwcfg3, uint32_t *ghwcfg4)
{
    *ghwcfg1 = hw->ghwcfg1_reg.val;
    *ghwcfg2 = hw->ghwcfg2_reg.val;
    *ghwcfg3 = hw->ghwcfg3_reg.val;
    *ghwcfg4 = hw->ghwcfg4_reg.val;
}

// ---------------------------HPTXFSIZ寄存器-------------------------------

static inline void usbh_ll_set_ptx_fifo_size(usbh_dev_t *hw, uint32_t addr, uint32_t num_lines)
{
    usb_hptxfsiz_reg_t hptxfsiz;
    hptxfsiz.val = hw->hptxfsiz_reg.val;
    HAL_FORCE_MODIFY_U32_REG_FIELD(hptxfsiz, ptxfstaddr, addr);
    HAL_FORCE_MODIFY_U32_REG_FIELD(hptxfsiz, ptxfsize, num_lines);
    hw->hptxfsiz_reg.val = hptxfsiz.val;
}

/* -----------------------------------------------------------------------------
--------------------------------主机寄存器--------------------------------
----------------------------------------------------------------------------- */

// -----------------------------HCFG登记簿---------------------------------

static inline void usbh_ll_hcfg_en_perio_sched(usbh_dev_t *hw)
{
    hw->hcfg_reg.perschedena = 1;
}

static inline void usbh_ll_hcfg_dis_perio_sched(usbh_dev_t *hw)
{
    hw->hcfg_reg.perschedena = 0;
}

/**
 * 设置帧列表的长度
 *
 * @param num_entires 帧列表中的整数
 */
static inline void usbh_ll_hcfg_set_num_frame_list_entries(usbh_dev_t *hw, usb_hal_frame_list_len_t num_entries)
{
    uint32_t frlisten;
    switch (num_entries) {
        case USB_HAL_FRAME_LIST_LEN_8:
            frlisten = 0;
            break;
        case USB_HAL_FRAME_LIST_LEN_16:
            frlisten = 1;
            break;
        case USB_HAL_FRAME_LIST_LEN_32:
            frlisten = 2;
            break;
        default: //USB_HAL_FRAME_LIST_LEN_64
            frlisten = 3;
            break;
    }
    hw->hcfg_reg.frlisten = frlisten;
}

static inline void usbh_ll_hcfg_en_scatt_gatt_dma(usbh_dev_t *hw)
{
    hw->hcfg_reg.descdma = 1;
}

static inline void usbh_ll_hcfg_set_fsls_supp_only(usbh_dev_t *hw)
{
    hw->hcfg_reg.fslssupp = 1;
}

static inline void usbh_ll_hcfg_set_fsls_pclk_sel(usbh_dev_t *hw)
{
    hw->hcfg_reg.fslspclksel = 1;
}

/**
 * @brief 将一些默认值设置为HCFG，以便在具有分散/聚集DMA的主机模式下运行
 *
 * @param hw DWC_OTG寄存器的起始地址
 * @param speed 初始化主机端口的速度
 */
static inline void usbh_ll_hcfg_set_defaults(usbh_dev_t *hw, usb_priv_speed_t speed)
{
    hw->hcfg_reg.descdma = 1;   //启用scatt/gatt
    hw->hcfg_reg.fslssupp = 1;  //仅FS/LS支持
    /*
    向OTG核心指出PHY时钟的速度。注意：在LS模式下，PHY似乎应用了隐式8分频器，因此必须相应调整FSLSPclkSel和FrInt的值。
    */
    hw->hcfg_reg.fslspclksel = (speed == USB_PRIV_SPEED_FULL) ? 1 : 2;  //仅适用于FS/LS的esp32 sx上的PHY时钟
    hw->hcfg_reg.perschedena = 0;   //禁用perio sched
}

// -----------------------------HFIR寄存器---------------------------------

static inline void usbh_ll_hfir_set_defaults(usbh_dev_t *hw, usb_priv_speed_t speed)
{
    usb_hfir_reg_t hfir;
    hfir.val = hw->hfir_reg.val;
    hfir.hfirrldctrl = 0;       //禁用动态加载
    /*
    将帧间隔设置为等于1ms注意：在LS模式下，PHY似乎应用了隐式8分频器，因此必须相应调整FSLSPclkSel和FrInt的值。
    */
    hfir.frint = (speed == USB_PRIV_SPEED_FULL) ? 48000 : 6000; //esp32 sx目标仅支持FS或LS
    hw->hfir_reg.val = hfir.val;
}

// -----------------------------HFNUM寄存器--------------------------------

static inline uint32_t usbh_ll_get_frm_time_rem(usbh_dev_t *hw)
{
    return HAL_FORCE_READ_U32_REG_FIELD(hw->hfnum_reg, frrem);
}

static inline uint32_t usbh_ll_get_frm_num(usbh_dev_t *hw)
{
    return hw->hfnum_reg.frnum;
}

// ----------------------------HPTXSTS寄存器-------------------------------

static inline uint32_t usbh_ll_get_p_tx_queue_top(usbh_dev_t *hw)
{
    return HAL_FORCE_READ_U32_REG_FIELD(hw->hptxsts_reg, ptxqtop);
}

static inline uint32_t usbh_ll_get_p_tx_queue_space_avail(usbh_dev_t *hw)
{
    return hw->hptxsts_reg.ptxqspcavail;
}

static inline uint32_t usbh_ll_get_p_tx_fifo_space_avail(usbh_dev_t *hw)
{
    return HAL_FORCE_READ_U32_REG_FIELD(hw->hptxsts_reg, ptxfspcavail);
}

// -----------------------------HAINT登记--------------------------------

static inline uint32_t usbh_ll_get_chan_intrs_msk(usbh_dev_t *hw)
{
    return HAL_FORCE_READ_U32_REG_FIELD(hw->haint_reg, haint);
}

// ---------------------------HAINTMSK寄存器-------------------------------

static inline void usbh_ll_haintmsk_en_chan_intr(usbh_dev_t *hw, uint32_t mask)
{

    hw->haintmsk_reg.val |= mask;
}

static inline void usbh_ll_haintmsk_dis_chan_intr(usbh_dev_t *hw, uint32_t mask)
{
    hw->haintmsk_reg.val &= ~mask;
}

// ---------------------------HFLBAddr寄存器-------------------------------

/**
 * @brief 设置调度帧列表的基地址
 *
 * @note 由于某种原因，该地址必须对齐512字节，否则当帧列表滚动时，将无法调度一堆帧。然而，根据数据手册，没有提到需要调整HFLBAddr。
 *
 * @param hw DWC_OTG寄存器的起始地址
 * @param addr 调度帧列表的基地址
 */
static inline void usbh_ll_set_frame_list_base_addr(usbh_dev_t *hw, uint32_t addr)
{
    hw->hflbaddr_reg.hflbaddr = addr;
}

/**
 * @brief 获取调度帧列表的基地址
 *
 * @param hw DWC_OTG寄存器的起始地址
 * @return uint32_t调度帧列表的基地址
 */
static inline uint32_t usbh_ll_get_frame_list_base_addr(usbh_dev_t *hw)
{
    return hw->hflbaddr_reg.hflbaddr;
}

// -----------------------------HPRT寄存器---------------------------------

static inline usb_priv_speed_t usbh_ll_hprt_get_speed(usbh_dev_t *hw)
{
    usb_priv_speed_t speed;
    //esp32-s2和esp32-s3仅支持FS或LS
    switch (hw->hprt_reg.prtspd) {
        case 1:
            speed = USB_PRIV_SPEED_FULL;
            break;
        default:
            speed = USB_PRIV_SPEED_LOW;
            break;
    }
    return speed;
}

static inline uint32_t usbh_ll_hprt_get_test_ctl(usbh_dev_t *hw)
{
    return hw->hprt_reg.prttstctl;
}

static inline void usbh_ll_hprt_set_test_ctl(usbh_dev_t *hw, uint32_t test_mode)
{
    usb_hprt_reg_t hprt;
    hprt.val = hw->hprt_reg.val;
    hprt.prttstctl = test_mode;
    hw->hprt_reg.val = hprt.val & (~USBH_LL_HPRT_W1C_MSK);
}

static inline void usbh_ll_hprt_en_pwr(usbh_dev_t *hw)
{
    usb_hprt_reg_t hprt;
    hprt.val = hw->hprt_reg.val;
    hprt.prtpwr = 1;
    hw->hprt_reg.val = hprt.val & (~USBH_LL_HPRT_W1C_MSK);
}

static inline void usbh_ll_hprt_dis_pwr(usbh_dev_t *hw)
{
    usb_hprt_reg_t hprt;
    hprt.val = hw->hprt_reg.val;
    hprt.prtpwr = 0;
    hw->hprt_reg.val = hprt.val & (~USBH_LL_HPRT_W1C_MSK);
}

static inline uint32_t usbh_ll_hprt_get_pwr_line_status(usbh_dev_t *hw)
{
    return hw->hprt_reg.prtlnsts;
}

static inline void usbh_ll_hprt_set_port_reset(usbh_dev_t *hw, bool reset)
{
    usb_hprt_reg_t hprt;
    hprt.val = hw->hprt_reg.val;
    hprt.prtrst = reset;
    hw->hprt_reg.val = hprt.val & (~USBH_LL_HPRT_W1C_MSK);
}

static inline bool usbh_ll_hprt_get_port_reset(usbh_dev_t *hw)
{
    return hw->hprt_reg.prtrst;
}

static inline void usbh_ll_hprt_set_port_suspend(usbh_dev_t *hw)
{
    usb_hprt_reg_t hprt;
    hprt.val = hw->hprt_reg.val;
    hprt.prtsusp = 1;
    hw->hprt_reg.val = hprt.val & (~USBH_LL_HPRT_W1C_MSK);
}

static inline bool usbh_ll_hprt_get_port_suspend(usbh_dev_t *hw)
{
    return hw->hprt_reg.prtsusp;
}

static inline void usbh_ll_hprt_set_port_resume(usbh_dev_t *hw)
{
    usb_hprt_reg_t hprt;
    hprt.val = hw->hprt_reg.val;
    hprt.prtres = 1;
    hw->hprt_reg.val = hprt.val & (~USBH_LL_HPRT_W1C_MSK);
}

static inline void usbh_ll_hprt_clr_port_resume(usbh_dev_t *hw)
{
    usb_hprt_reg_t hprt;
    hprt.val = hw->hprt_reg.val;
    hprt.prtres = 0;
    hw->hprt_reg.val = hprt.val & (~USBH_LL_HPRT_W1C_MSK);
}

static inline bool usbh_ll_hprt_get_port_resume(usbh_dev_t *hw)
{
    return hw->hprt_reg.prtres;
}

static inline bool usbh_ll_hprt_get_port_overcur(usbh_dev_t *hw)
{
    return hw->hprt_reg.prtovrcurract;
}

static inline bool usbh_ll_hprt_get_port_en(usbh_dev_t *hw)
{
    return hw->hprt_reg.prtena;
}

static inline void usbh_ll_hprt_port_dis(usbh_dev_t *hw)
{
    usb_hprt_reg_t hprt;
    hprt.val = hw->hprt_reg.val;
    hprt.prtena = 1;        //W1C禁用
    //我们想要W1C ENA而不是W1C中断位
    hw->hprt_reg.val = hprt.val & ((~USBH_LL_HPRT_W1C_MSK) | USBH_LL_HPRT_ENA_MSK);
}

static inline bool usbh_ll_hprt_get_conn_status(usbh_dev_t *hw)
{
    return hw->hprt_reg.prtconnsts;
}

static inline uint32_t usbh_ll_hprt_intr_read_and_clear(usbh_dev_t *hw)
{
    usb_hprt_reg_t hprt;
    hprt.val = hw->hprt_reg.val;
    //我们想要W1C中断位，但不是ENA
    hw->hprt_reg.val = hprt.val & (~USBH_LL_HPRT_ENA_MSK);
    //仅返回中断位
    return (hprt.val & (USBH_LL_HPRT_W1C_MSK & ~(USBH_LL_HPRT_ENA_MSK)));
}

static inline void usbh_ll_hprt_intr_clear(usbh_dev_t *hw, uint32_t intr_mask)
{
    usb_hprt_reg_t hprt;
    hprt.val = hw->hprt_reg.val;
    hw->hprt_reg.val = ((hprt.val & ~USBH_LL_HPRT_ENA_MSK) & ~USBH_LL_HPRT_W1C_MSK) | intr_mask;
}

//每通道寄存器

// ---------------------------HCCHARi寄存器--------------------------------

static inline void usbh_ll_chan_start(volatile usb_host_chan_regs_t *chan)
{
    chan->hcchar_reg.chena = 1;
}

static inline bool usbh_ll_chan_is_active(volatile usb_host_chan_regs_t *chan)
{
    return chan->hcchar_reg.chena;
}

static inline void usbh_ll_chan_halt(volatile usb_host_chan_regs_t *chan)
{
    chan->hcchar_reg.chdis = 1;
}

static inline void usbh_ll_chan_xfer_odd_frame(volatile usb_host_chan_regs_t *chan)
{
    chan->hcchar_reg.oddfrm = 1;
}

static inline void usbh_ll_chan_xfer_even_frame(volatile usb_host_chan_regs_t *chan)
{
    chan->hcchar_reg.oddfrm = 0;
}

static inline void usbh_ll_chan_set_dev_addr(volatile usb_host_chan_regs_t *chan, uint32_t addr)
{
    chan->hcchar_reg.devaddr = addr;
}

static inline void usbh_ll_chan_set_ep_type(volatile usb_host_chan_regs_t *chan, usb_priv_xfer_type_t type)
{
    uint32_t ep_type;
    switch (type) {
        case USB_PRIV_XFER_TYPE_CTRL:
            ep_type = 0;
            break;
        case USB_PRIV_XFER_TYPE_ISOCHRONOUS:
            ep_type = 1;
            break;
        case USB_PRIV_XFER_TYPE_BULK:
            ep_type = 2;
            break;
        default:    //USB_PRIV_XFER_TYPE_INTR
            ep_type = 3;
            break;
    }
    chan->hcchar_reg.eptype = ep_type;
}

//指示信道是否与通过FS集线器连接的LS设备通信。将此位设置为1将导致
//每个数据包前面都有一个前导数据包
static inline void usbh_ll_chan_set_lspddev(volatile usb_host_chan_regs_t *chan, bool is_ls)
{
    chan->hcchar_reg.lspddev = is_ls;
}

static inline void usbh_ll_chan_set_dir(volatile usb_host_chan_regs_t *chan, bool is_in)
{
    chan->hcchar_reg.epdir = is_in;
}

static inline void usbh_ll_chan_set_ep_num(volatile usb_host_chan_regs_t *chan, uint32_t num)
{
    chan->hcchar_reg.epnum = num;
}

static inline void usbh_ll_chan_set_mps(volatile usb_host_chan_regs_t *chan, uint32_t mps)
{
    chan->hcchar_reg.mps = mps;
}

static inline void usbh_ll_chan_hcchar_init(volatile usb_host_chan_regs_t *chan, int dev_addr, int ep_num, int mps, usb_priv_xfer_type_t type, bool is_in, bool is_ls)
{
    //设置通道在其生命周期z内的所有持久字段
    usbh_ll_chan_set_dev_addr(chan, dev_addr);
    usbh_ll_chan_set_ep_type(chan, type);
    usbh_ll_chan_set_lspddev(chan, is_ls);
    usbh_ll_chan_set_dir(chan, is_in);
    usbh_ll_chan_set_ep_num(chan, ep_num);
    usbh_ll_chan_set_mps(chan, mps);
}

// ----------------------------HCINTi寄存器--------------------------------

static inline uint32_t usbh_ll_chan_intr_read_and_clear(volatile usb_host_chan_regs_t *chan)
{
    usb_hcint_reg_t hcint;
    hcint.val = chan->hcint_reg.val;
    chan->hcint_reg.val = hcint.val;
    return hcint.val;
}

// ---------------------------HCINTMSKi寄存器------------------------------

static inline void usbh_ll_chan_set_intr_mask(volatile usb_host_chan_regs_t *chan, uint32_t mask)
{
    chan->hcintmsk_reg.val = mask;
}

// ----------------------HCTSIZi和HCDMAi寄存器-------------------------

static inline void usbh_ll_chan_set_pid(volatile usb_host_chan_regs_t *chan, uint32_t data_pid)
{
    if (data_pid == 0) {
        chan->hctsiz_reg.pid = 0;
    } else {
        chan->hctsiz_reg.pid = 2;
    }
}

static inline uint32_t usbh_ll_chan_get_pid(volatile usb_host_chan_regs_t *chan) {
    if (chan->hctsiz_reg.pid == 0) {
        return 0;   //DATA0
    } else {
        return 1;   //DATA1
    }
}

static inline void usbh_ll_chan_set_dma_addr_non_iso(volatile usb_host_chan_regs_t *chan,
                                                    void *dmaaddr,
                                                    uint32_t qtd_idx)
{
    //设置HCDMAi
    chan->hcdma_reg.val = 0;
    chan->hcdma_reg.non_iso.dmaaddr = (((uint32_t)dmaaddr) >> 9) & 0x7FFFFF;  //512字节对齐地址的MSB
    chan->hcdma_reg.non_iso.ctd = qtd_idx;
}

static inline int usbh_ll_chan_get_ctd(usb_host_chan_regs_t *chan)
{
    return chan->hcdma_reg.non_iso.ctd;
}

static inline void usbh_ll_chan_hctsiz_init(volatile usb_host_chan_regs_t *chan)
{
    chan->hctsiz_reg.dopng = 0;         //不执行ping
    HAL_FORCE_MODIFY_U32_REG_FIELD(chan->hctsiz_reg, sched_info, 0xFF); //对于全速，Scheduleinfo始终为0xFF。未在批量/Ctrl通道中使用
}

static inline void usbh_ll_chan_set_qtd_list_len(volatile usb_host_chan_regs_t *chan, int qtd_list_len)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(chan->hctsiz_reg, ntd, qtd_list_len - 1);    //设置描述符列表的长度
}

// ----------------------------HCDMABi寄存器-------------------------------

static inline void *usbh_ll_chan_get_cur_buff_addr(volatile usb_host_chan_regs_t *chan)
{
    return (void *)chan->hcdmab_reg.hcdmab;
}

/* -----------------------------------------------------------------------------
----------------------------分散/收集DMA QTD---------------------------
----------------------------------------------------------------------------- */

// ----------------------------Helper函数-------------------------------

/**
 * @brief 根据通道索引获取通道寄存器的基址
 *
 * @param dev DWC_OTG寄存器的起始地址
 * @param chan_idx 频道索引
 * @return usb_host_chan_regs_t*指向通道寄存器的指针
 */
static inline usb_host_chan_regs_t *usbh_ll_get_chan_regs(usbh_dev_t *dev, int chan_idx)
{
    return &dev->host_chans[chan_idx];
}

// ------------------------------QTD相关----------------------------------

#define USBH_LL_QTD_STATUS_SUCCESS      0x0     //如果处理了QTD，则表示数据传输/接收成功
#define USBH_LL_QTD_STATUS_PKTERR       0x1     //发送/接收的数据有错误（CRC/超时/填充/错误EOP/过量NAK）。
//注意：0x2是保留的
#define USBH_LL_QTD_STATUS_BUFFER       0x3     //发生AHB错误。
#define USBH_LL_QTD_STATUS_NOT_EXECUTED 0x4     //未处理的QTD

/**
 * @brief 为非同步IN传输设置QTD
 *
 * @param qtd 指向QTD的指针
 * @param data_buff 指向包含要传输数据的缓冲区的指针
 * @param xfer_len 传输中的字节数。设置0将执行零长度IN传输。非零长度必须是端点MPS的倍数。
 * @param hoc 完成时停止（将产生中断并停止通道）
 */
static inline void usbh_ll_set_qtd_in(usbh_ll_dma_qtd_t *qtd, uint8_t *data_buff, int xfer_len, bool hoc)
{
    qtd->buffer = data_buff;        //设置指向数据缓冲区的指针
    qtd->buffer_status_val = 0;     //将所有标志重置为零
    qtd->in_non_iso.xfer_size = xfer_len;
    if (hoc) {
        qtd->in_non_iso.intr_cplt = 1;  //我们需要设置此项以区分因QTD导致的停机
        qtd->in_non_iso.eol = 1;        //用于在此qtd停止频道
    }
    qtd->in_non_iso.active = 1;
}

/**
 * @brief 为非同步OUT传输设置QTD
 *
 * @param qtd Poitner至QTD
 * @param data_buff 指向包含要传输数据的缓冲区的指针
 * @param xfer_len 要传输的字节数。设置0将执行零长度传输。对于ctrl设置数据包，该值应设置为8。
 * @param hoc 完成时停止（将生成中断）
 * @param is_setup 指示这是控制传输设置数据包还是正常的OUT数据传输。（根据USB协议，设备不能将设置数据包设置为STALLd或NAKd）
 */
static inline void usbh_ll_set_qtd_out(usbh_ll_dma_qtd_t *qtd, uint8_t *data_buff, int xfer_len, bool hoc, bool is_setup)
{
    qtd->buffer = data_buff;        //设置指向数据缓冲区的指针
    qtd->buffer_status_val = 0;     //将所有标志重置为零
    qtd->out_non_iso.xfer_size = xfer_len;
    if (is_setup) {
        qtd->out_non_iso.is_setup = 1;
    }
    if (hoc) {
        qtd->in_non_iso.intr_cplt = 1;  //我们需要设置此项以区分因QTD导致的停机
        qtd->in_non_iso.eol = 1;        //用于在此qtd停止频道
    }
    qtd->out_non_iso.active = 1;
}

/**
 * @brief 将QTD设置为NULL
 *
 * 这将QTD设置为值0。仅当您需要将空白QTD插入QTD列表时，这才有用
 *
 * @param qtd 指向QTD的指针
 */
static inline void usbh_ll_set_qtd_null(usbh_ll_dma_qtd_t *qtd)
{
    qtd->buffer = NULL;
    qtd->buffer_status_val = 0;     //通过将qtd清零来禁用qtd。被interrut/isoc用作非屏蔽帧
}

/**
 * @brief 获取QTD的状态
 *
 * 当通道获取暂停时，调用此命令检查每个QTD是否成功执行
 *
 * @param qtd Poitner至QTD
 * @param[out] rem_len QTD中分支的字节数
 * @param[out] status QTD的状态
 */
static inline void usbh_ll_get_qtd_status(usbh_ll_dma_qtd_t *qtd, int *rem_len, int *status)
{
    //无论IN或OUT，状态都相同
    if (qtd->in_non_iso.active) {
        //QTD从未处理
        *status = USBH_LL_QTD_STATUS_NOT_EXECUTED;
    } else {
        *status = qtd->in_non_iso.rx_status;
    }
    *rem_len = qtd->in_non_iso.xfer_size;
    //为了安全起见，清除QTD
    qtd->buffer_status_val = 0;
}

#ifdef __cplusplus
}
#endif

