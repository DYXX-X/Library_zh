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

#pragma once

#include <stdint.h>
#include "usb_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct usb_reg {
    volatile uint32_t gotgctl;              // 0x0000 OTG控制和状态寄存器
    volatile uint32_t gotgint;              // 0x0004 OTG中断寄存器
    volatile uint32_t gahbcfg;              // 0x0008 AHB配置寄存器
    volatile uint32_t gusbcfg;              // 0x000c USB配置寄存器
    volatile uint32_t grstctl;              // 0x0010重置寄存器
    volatile uint32_t gintsts;              // 0x0014中断寄存器
    volatile uint32_t gintmsk;              // 0x0018中断掩码寄存器
    volatile uint32_t grxstsr;              // 0x001c接收状态调试读取寄存器
    volatile uint32_t grxstsp;              // 0x0020接收状态读取/弹出寄存器
    volatile uint32_t grxfsiz;              // 0x0024接收FIFO大小寄存器
    volatile uint32_t gnptxfsiz;            // 0x0028非周期传输FIFO大小寄存器
    volatile uint32_t gnptxsts;             // 0x002c非周期传输FIFO/队列状态寄存器
    uint32_t reserved_0x0030_0x0040[4];     // 0x0030到0x0040
    volatile uint32_t gsnpsid;              // 0x0040 Synopsys ID寄存器
    volatile uint32_t ghwcfg1;              // 0x0044用户硬件配置1寄存器
    volatile uint32_t ghwcfg2;              // 0x0048用户硬件配置2寄存器
    volatile uint32_t ghwcfg3;              // 0x004c用户硬件配置3寄存器
    volatile uint32_t ghwcfg4;              // 0x0050用户硬件配置4寄存器
    uint32_t reserved_0x0054_0x005c[2];     // 0x0054至0x005c
    volatile uint32_t gdfifocfg;            // 0x005c全局DFIFO配置寄存器
    uint32_t reserved_0x0060_0x0100[40];    // 0x0060至0x0100
    volatile uint32_t hptxfsiz;             // 0x0100主机周期传输FIFO大小寄存器
    volatile uint32_t dieptxf[4];           // 0x0104到0x0114设备IN端点传输FIFO大小寄存器i
    uint32_t reserved_0x0114_0x0140[11];    // 0x0114至0x0140
    uint32_t reserved_0x0140_0x0400[176];   // 0x0140至0x0400
    /**
     * 主机模式寄存器从0x0400到0x07FF的偏移
     */
    volatile uint32_t hcfg;                 // 0x0400主机配置寄存器
    volatile uint32_t hfir;                 // 0x0404主机帧间隔寄存器
    volatile uint32_t hfnum;                // 0x0408主机帧号/剩余帧寄存器
    uint32_t reserved0x40C;                 // 0x040c保留
    volatile uint32_t hptxsts;              // 0x0410主机定期传输FIFO/队列状态寄存器
    volatile uint32_t haint;                // 0x0414主机所有通道中断寄存器
    volatile uint32_t haintmsk;             // 0x0418主机所有通道中断掩码寄存器
    volatile uint32_t hflbaddr;             // 0x041c主机帧列表基址寄存器
    uint32_t reserved0x0420_0x0440[8];      // 0x0420至0x0440
    volatile uint32_t hprt;                 // 0x0440主机端口控制和状态寄存器
    uint32_t reserved_0x0444_0x0500[47];    // 0x0444到0x0500
    //跳过主机通道寄存器
    volatile uint32_t host_chan_regs[128];  // 0x0500至0x0700
    uint32_t reserved_0x0700_0x0800[64];    // 0x0700至0x0800
    /**
     * 设备模式寄存器从
     */
    volatile uint32_t dcfg;                 // 0x0800设备配置寄存器
    volatile uint32_t dctl;                 // 0x0804设备控制寄存器
    volatile uint32_t dsts;                 // 0x0808设备状态寄存器（只读）
    uint32_t reserved0x80c;                 // 0x080c
    volatile uint32_t diepmsk;              // 0x0810设备IN端点公共中断掩码寄存器
    volatile uint32_t doepmsk;              // 0x0814设备输出端点公共中断掩码寄存器
    volatile uint32_t daint;                // 0x0818设备所有端点中断寄存器
    volatile uint32_t daintmsk;             // 0x081c设备所有端点中断掩码寄存器
    uint32_t reserved_0x0820_0x0828[2];     // 0x0820至0x0828
    volatile uint32_t dvbusdis;             // 0x0828设备VBUS放电寄存器
    volatile uint32_t dvbuspulse;           // 0x082c设备VBUS脉冲寄存器
    volatile uint32_t dthrctl;              // 0x0830设备阈值控制寄存器（读/写）
    volatile uint32_t dtknqr4_fifoemptymsk; // 0x0834设备IN终结点FIFO空中断掩码寄存器
    uint32_t reserved_0x0838_0x0900[50];    // 0x0838至0x0900
    // 输入端点
    usb_in_endpoint_t in_ep_reg[USB_IN_EP_NUM];     // 0x0900至0x09e0 IN EP寄存器
    uint32_t reserved_0x09e0_0x0b00[72];    // 0x09e0到0x0b00
    // 输出端点
    usb_out_endpoint_t out_ep_reg[USB_OUT_EP_NUM];  // 0x0b00到0x0be0 OUT EP寄存器
    uint32_t reserved_0x0be0_0x0d00[72];    // 0x0be0到0x0d00
    uint32_t reserved_0x0d00_0x0e00[64];    // 0x0d00到0x0e00
    /**
     * 电源控制和直接FIFO访问
     */
    uint32_t pcgctrl;                       // 0x0e00电源和时钟门控控制寄存器
    uint32_t reserved_0x0e04;               // 0x0e04
    uint8_t reserved8[0x1000 - 0xe08];      // 0x0d00至0x1000
    uint32_t fifo[16][0x400];               // 0x1000至0x2000设备EP i/主机通道i FIFO
    uint8_t reserved0x11000[0x20000 - 0x11000];
    uint32_t dbg_fifo[0x20000];             // 0x2000到0x22000直接访问数据FIFO RAM进行调试
} usb_dev_t;

extern usb_dev_t USB0;

#ifdef __cplusplus
}
#endif

