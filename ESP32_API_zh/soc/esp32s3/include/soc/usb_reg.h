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
#include "soc/soc.h"
#include "soc.h"
#ifdef __cplusplus
extern "C" {
#endif

/**控制/状态寄存器*/
/** USB_GOTGCTL_REG寄存器OTG控制和状态寄存器
 */
#define USB_GOTGCTL_REG (SOC_DPORT_USB_BASE + 0x0)
/** USB_SESREQSCS:RO；位位置：[0]；默认值：0；会话请求成功。当会话请求启动成功时，内核设置此位
 */
#define USB_SESREQSCS    (BIT(0))
#define USB_SESREQSCS_M  (USB_SESREQSCS_V << USB_SESREQSCS_S)
#define USB_SESREQSCS_V  0x00000001
#define USB_SESREQSCS_S  0
/** USB_SESREQ:R/W；位位置：[1]；默认值：0；会话请求。应用程序设置此位以启动USB上的会话请求。当OTG中断寄存器（GOTGINT_REG.USB_HSTNEGSUCTSCHNG）中的主机协商成功状态更改位置位时，应用程序可以通过写入0来清除此位。当清除USB_HSTNEGSUCTSCHNG位时，内核清除该位
 */
#define USB_SESREQ    (BIT(1))
#define USB_SESREQ_M  (USB_SESREQ_V << USB_SESREQ_S)
#define USB_SESREQ_V  0x00000001
#define USB_SESREQ_S  1
/** USB_VBVALIDOVEN:R/W；位位置：[2]；默认值：0；VBUS有效覆盖启用1’b1：从PHY接收的内部Bvalid被GOTGCTL_REG覆盖。REG_VBVALIDOVVAl 1’b0：超控被禁用，控制器内部使用来自所选相应PHY的有效信号
 */
#define USB_VBVALIDOVEN    (BIT(2))
#define USB_VBVALIDOVEN_M  (USB_VBVALIDOVEN_V << USB_VBVALIDOVEN_S)
#define USB_VBVALIDOVEN_V  0x00000001
#define USB_VBVALIDOVEN_S  2
/** USB_vbvalidoval:R/W；位位置：[3]；默认值：0；VBUS有效覆盖值1’b0：当GOTGCTL_REG时，VBUS有效值为1’b0。USB_VBVALIDOVEN=1 1‘b1：当GOTGCTL_REG时，vbus有效值为1‘b1。USB_VBVALIDOVEN=1
 */
#define USB_VBVALIDOVVAL    (BIT(3))
#define USB_VBVALIDOVVAL_M  (USB_VBVALIDOVVAL_V << USB_VBVALIDOVVAL_S)
#define USB_VBVALIDOVVAL_V  0x00000001
#define USB_VBVALIDOVVAL_S  3
/** USB_AVALIDOVEN:R/W；位位置：[4]；默认值：0；该位用于启用/禁用软件，以使用GOTGCTL覆盖Avalid信号。AVALIDOVAL 1’b1：从PHY接收的内部Avaid被GOTGCTL_REG覆盖。REG_AVALIDOVVAL 1’b0：覆盖被禁用，核心内部使用来自所选相应PHY的有效信号
 */
#define USB_AVALIDOVEN    (BIT(4))
#define USB_AVALIDOVEN_M  (USB_AVALIDOVEN_V << USB_AVALIDOVEN_S)
#define USB_AVALIDOVEN_V  0x00000001
#define USB_AVALIDOVEN_S  4
/** USB_AVALIDOVVAL:R/W；位位置：[5]；默认值：0；A-Peripheral Session Valid OverrideValue 1’b0:当GOTGCTL_REG时，Avaid值为1’b0。USB_AVALIDOVEN=1 1’b1：当GOTGCTL_REG时，Avaid值为1’b1。USB_AVALIDOVEN=1
 */
#define USB_AVALIDOVVAL    (BIT(5))
#define USB_AVALIDOVVAL_M  (USB_AVALIDOVVAL_V << USB_AVALIDOVVAL_S)
#define USB_AVALIDOVVAL_V  0x00000001
#define USB_AVALIDOVVAL_S  5
/** USB_BVALIDOVEN:R/W；位位置：[6]；默认值：0；该位用于启用/禁用软件，以使用GOTGCTREG覆盖Bvalid信号。BVALIDOVVAL 1’b1：从PHY接收的内部Bvalid被GOTGCTL_REG覆盖。USB_BVALIDOVVAL 1’b0：超驰被禁用，来自所选相应PHY的有效信号被部队内部使用
 */
#define USB_BVALIDOVEN    (BIT(6))
#define USB_BVALIDOVEN_M  (USB_BVALIDOVEN_V << USB_BVALIDOVEN_S)
#define USB_BVALIDOVEN_V  0x00000001
#define USB_BVALIDOVEN_S  6
/** USB_BVALIDOVVAL:R/W；位位置：[7]；默认值：0；B—外围会话有效覆盖值1’b0：当GOTGCTL_REG时，B有效值为1’b0。USB_BVALIDOVEN=1 1’b1：当GOTGCTL_REG时，B有效值为1’b1。USB_BVALIDOVEN=1
 */
#define USB_BVALIDOVVAL    (BIT(7))
#define USB_BVALIDOVVAL_M  (USB_BVALIDOVVAL_V << USB_BVALIDOVVAL_S)
#define USB_BVALIDOVVAL_V  0x00000001
#define USB_BVALIDOVVAL_S  7
/** USB_HSTNEGSCS:RO；位位置：[8]；默认值：0；主持人协商成功。当主机协商成功时，控制器设置此位。当设置该寄存器中的HNP请求（HNPReq）位时，控制器清除该位。
 */
#define USB_HSTNEGSCS    (BIT(8))
#define USB_HSTNEGSCS_M  (USB_HSTNEGSCS_V << USB_HSTNEGSCS_S)
#define USB_HSTNEGSCS_V  0x00000001
#define USB_HSTNEGSCS_S  8
/** USB_HNPREQ:R/W；位位置：[9]；默认值：0；HNP请求。应用程序设置此位以向连接的USB主机发起HNP请求。当OTG中断寄存器（GOTGINT_REG.HSTNEGSUCSTSCHNG）中的主机协商成功状态更改位置位时，应用程序可以通过写入0来清除此位。当HSTNEGSUCSTSCHNG位被清除时，控制器清除该位。
 */
#define USB_HNPREQ    (BIT(9))
#define USB_HNPREQ_M  (USB_HNPREQ_V << USB_HNPREQ_S)
#define USB_HNPREQ_V  0x00000001
#define USB_HNPREQ_S  9
/** USB_HSTSETHNPEN:R/W；位位置：[10]；默认值：0；主机设置HNP启用。应用程序在已成功启用连接设备上的HNP（使用SetFeature.SetHNPEnable命令）时设置此位1’b0：未启用主机集HNP 1’b1：已启用主机集
 */
#define USB_HSTSETHNPEN    (BIT(10))
#define USB_HSTSETHNPEN_M  (USB_HSTSETHNPEN_V << USB_HSTSETHNPEN_S)
#define USB_HSTSETHNPEN_V  0x00000001
#define USB_HSTSETHNPEN_S  10
/** USB_DEVHNPEN:R/W；位位置：[11]；默认值：0；设备HNP已启用。应用程序在成功接收SetFeature时设置此位。来自连接的USB主机1’b0的SetHNPEnable命令：应用程序1’b1中未启用HNP：应用程序中已启用HNP
 */
#define USB_DEVHNPEN    (BIT(11))
#define USB_DEVHNPEN_M  (USB_DEVHNPEN_V << USB_DEVHNPEN_S)
#define USB_DEVHNPEN_V  0x00000001
#define USB_DEVHNPEN_S  11
/** USB_EHEN:R/W；位位置：[12]；默认值：0；嵌入式主机启用。用于在OTG A设备状态机和嵌入式主机状态机之间进行选择1’b0：选择OTG A状态机1’b1：选择嵌入式主机状态机器
 */
#define USB_EHEN    (BIT(12))
#define USB_EHEN_M  (USB_EHEN_V << USB_EHEN_S)
#define USB_EHEN_V  0x00000001
#define USB_EHEN_S  12
/** USB_DBNCEFLTRBYPASS:R/W；位位置：[15]；默认值：0；启用时绕过avaid、bvalid、vbusvalid、sessend、iddig信号的去抖动滤波器1’b0：禁用1’b1：启用
 */
#define USB_DBNCEFLTRBYPASS    (BIT(15))
#define USB_DBNCEFLTRBYPASS_M  (USB_DBNCEFLTRBYPASS_V << USB_DBNCEFLTRBYPASS_S)
#define USB_DBNCEFLTRBYPASS_V  0x00000001
#define USB_DBNCEFLTRBYPASS_S  15
/** USB_conidts:RO；位位置：[16]；默认值：0；连接器ID状态。指示连接事件1’b0上的连接器ID状态：核心处于a设备模式1’b1：核心处于B设备模式
 */
#define USB_CONIDSTS    (BIT(16))
#define USB_CONIDSTS_M  (USB_CONIDSTS_V << USB_CONIDSTS_S)
#define USB_CONIDSTS_V  0x00000001
#define USB_CONIDSTS_S  16
/** USB_DBNCTIME:RO；位位置：[17]；默认值：0；长/短消抖时间。指示检测到的连接的防抖时间1’b0：长防抖时间，用于物理连接（100ms+2.5微秒）1’b1：短防抖时间（用于软连接（2.5微秒）
 */
#define USB_DBNCTIME    (BIT(17))
#define USB_DBNCTIME_M  (USB_DBNCTIME_V << USB_DBNCTIME_S)
#define USB_DBNCTIME_V  0x00000001
#define USB_DBNCTIME_S  17
/** USB_ASESVLD:RO；位位置：[18]；默认值：0；A会话有效。指示主机模式收发器状态1’b0:A会话无效1’b1:A会话有效
 */
#define USB_ASESVLD    (BIT(18))
#define USB_ASESVLD_M  (USB_ASESVLD_V << USB_ASESVLD_S)
#define USB_ASESVLD_V  0x00000001
#define USB_ASESVLD_S  18
/** USB_BSESVLD:RO；位位置：[19]；默认值：0；B会话有效。表示设备模式收发器状态1’b0:B会话无效1’b1:B会话有效
 */
#define USB_BSESVLD    (BIT(19))
#define USB_BSESVLD_M  (USB_BSESVLD_V << USB_BSESVLD_S)
#define USB_BSESVLD_V  0x00000001
#define USB_BSESVLD_S  19
/** USB_OTGVER:R/W；位位置：[20]；默认值：0；OTG版本1’b0:支持OTG版本1.3 1’b1：支持OTG 2.0
 */
#define USB_OTGVER    (BIT(20))
#define USB_OTGVER_M  (USB_OTGVER_V << USB_OTGVER_S)
#define USB_OTGVER_V  0x00000001
#define USB_OTGVER_S  20
/** USB_CURMOD:RO；位位置：[21]；默认值：0；当前操作模式1’b0：设备模式1’b1：主机模式
 */
#define USB_CURMOD    (BIT(21))
#define USB_CURMOD_M  (USB_CURMOD_V << USB_CURMOD_S)
#define USB_CURMOD_V  0x00000001
#define USB_CURMOD_S  21


/** USB_GDFIFOCFG_REG寄存器全局DFIFO配置寄存器
 */
#define USB_GDFIFOCFG_REG (SOC_DPORT_USB_BASE + 0x5c)
/** USB_GDFIFOCFG:R/W；位位置：[16:0]；默认值：0；GDFI聚焦
 */
#define USB_GDFIFOCFG    0x0000FFFF
#define USB_GDFIFOCFG_M  (USB_GDFIFOCFG_V << USB_GDFIFOCFG_S)
#define USB_GDFIFOCFG_V  0x0000FFFF
#define USB_GDFIFOCFG_S  0
/** USB_EPINFOBASEADDR:R/W；位位置：[32:16]；默认值：0；EPInfoBase地址
 */
#define USB_EPINFOBASEADDR    0x0000FFFF
#define USB_EPINFOBASEADDR_M  (USB_EPINFOBASEADDR_V << USB_EPINFOBASEADDR_S)
#define USB_EPINFOBASEADDR_V  0x0000FFFF
#define USB_EPINFOBASEADDR_S  16


/** USB_HPTXFSIZ_REG寄存器主机周期传输FIFO大小寄存器
 */
#define USB_HPTXFSIZ_REG (SOC_DPORT_USB_BASE + 0x100)
/** USB_PTXFSTADDR:R/W；位位置：[16:0]；默认值：512；主机周期TxFIFO起始地址。
 */
#define USB_PTXFSTADDR    0x0000FFFF
#define USB_PTXFSTADDR_M  (USB_PTXFSTADDR_V << USB_PTXFSTADDR_S)
#define USB_PTXFSTADDR_V  0x0000FFFF
#define USB_PTXFSTADDR_S  0
/** USB_PTXFSIZE:R/W；位位置：[32:16]；默认值：4096；主机周期TxFIFO深度，此值以32位字表示。。
 */
#define USB_PTXFSIZE    0x0000FFFF
#define USB_PTXFSIZE_M  (USB_PTXFSIZE_V << USB_PTXFSIZE_S)
#define USB_PTXFSIZE_V  0x0000FFFF
#define USB_PTXFSIZE_S  16


/** USB_DIEPTXF1_REG寄存器设备IN端点传输FIFO大小寄存器
 */
#define USB_DIEPTXF1_REG (SOC_DPORT_USB_BASE + 0x104)
/** USB_INEP1TXFSTADDR:R/W；位位置：[16:0]；默认值：512；IN Endpoint FIFOn传输RAM起始地址。
 */
#define USB_INEP1TXFSTADDR    0x0000FFFF
#define USB_INEP1TXFSTADDR_M  (USB_INEP1TXFSTADDR_V << USB_INEP1TXFSTADDR_S)
#define USB_INEP1TXFSTADDR_V  0x0000FFFF
#define USB_INEP1TXFSTADDR_S  0
/** USB_INEP1TXFDEP:R/W；位位置：[32:16]；默认值：4096；IN端点TxFIFO深度
 */
#define USB_INEP1TXFDEP    0x0000FFFF
#define USB_INEP1TXFDEP_M  (USB_INEP1TXFDEP_V << USB_INEP1TXFDEP_S)
#define USB_INEP1TXFDEP_V  0x0000FFFF
#define USB_INEP1TXFDEP_S  16


/** USB_DIEPTXF2_REG寄存器设备IN端点传输FIFO大小寄存器
 */
#define USB_DIEPTXF2_REG (SOC_DPORT_USB_BASE + 0x108)
/** USB_INEP2TXFSTADDR:R/W；位位置：[16:0]；默认值：512；IN Endpoint FIFOn传输RAM起始地址。
 */
#define USB_INEP2TXFSTADDR    0x0000FFFF
#define USB_INEP2TXFSTADDR_M  (USB_INEP2TXFSTADDR_V << USB_INEP2TXFSTADDR_S)
#define USB_INEP2TXFSTADDR_V  0x0000FFFF
#define USB_INEP2TXFSTADDR_S  0
/** USB_INEP2TXFDEP:R/W；位位置：[32:16]；默认值：4096；IN端点TxFIFO深度
 */
#define USB_INEP2TXFDEP    0x0000FFFF
#define USB_INEP2TXFDEP_M  (USB_INEP2TXFDEP_V << USB_INEP2TXFDEP_S)
#define USB_INEP2TXFDEP_V  0x0000FFFF
#define USB_INEP2TXFDEP_S  16


/** USB_DIEPTXF3_REG寄存器设备IN端点传输FIFO大小寄存器
 */
#define USB_DIEPTXF3_REG (SOC_DPORT_USB_BASE + 0x10c)
/** USB_INEP3TXFSTADDR:R/W；位位置：[16:0]；默认值：512；IN Endpoint FIFOn传输RAM起始地址。
 */
#define USB_INEP3TXFSTADDR    0x0000FFFF
#define USB_INEP3TXFSTADDR_M  (USB_INEP3TXFSTADDR_V << USB_INEP3TXFSTADDR_S)
#define USB_INEP3TXFSTADDR_V  0x0000FFFF
#define USB_INEP3TXFSTADDR_S  0
/** USB_INEP3TXFDEP:R/W；位位置：[32:16]；默认值：4096；IN端点TxFIFO深度
 */
#define USB_INEP3TXFDEP    0x0000FFFF
#define USB_INEP3TXFDEP_M  (USB_INEP3TXFDEP_V << USB_INEP3TXFDEP_S)
#define USB_INEP3TXFDEP_V  0x0000FFFF
#define USB_INEP3TXFDEP_S  16


/** USB_DIEPTXF4_REG寄存器设备IN端点传输FIFO大小寄存器
 */
#define USB_DIEPTXF4_REG (SOC_DPORT_USB_BASE + 0x110)
/** USB_INEP4TXFSTADDR:R/W；位位置：[16:0]；默认值：512；IN Endpoint FIFOn传输RAM起始地址。
 */
#define USB_INEP4TXFSTADDR    0x0000FFFF
#define USB_INEP4TXFSTADDR_M  (USB_INEP4TXFSTADDR_V << USB_INEP4TXFSTADDR_S)
#define USB_INEP4TXFSTADDR_V  0x0000FFFF
#define USB_INEP4TXFSTADDR_S  0
/** USB_INEP4TXFDEP:R/W；位位置：[32:16]；默认值：4096；IN端点TxFIFO深度
 */
#define USB_INEP4TXFDEP    0x0000FFFF
#define USB_INEP4TXFDEP_M  (USB_INEP4TXFDEP_V << USB_INEP4TXFDEP_S)
#define USB_INEP4TXFDEP_V  0x0000FFFF
#define USB_INEP4TXFDEP_S  16


/** USB_HCFG_REG寄存器主机配置寄存器
 */
#define USB_HCFG_REG (SOC_DPORT_USB_BASE + 0x400)
/** USB_H_FSLSPCLKSEL:R/W；位位置：[2:0]；默认值：0；0x0:PHY时钟以30/60 MHz运行0x1:PHY钟以48 MHz运行0x2:PHY时钟以6 MHz运行
 */
#define USB_H_FSLSPCLKSEL    0x00000003
#define USB_H_FSLSPCLKSEL_M  (USB_H_FSLSPCLKSEL_V << USB_H_FSLSPCLKSEL_S)
#define USB_H_FSLSPCLKSEL_V  0x00000003
#define USB_H_FSLSPCLKSEL_S  0
/** USB_H_fslsupp:R/W；位位置：[2]；默认值：0；FS-和LS仅支持1’b0:HS/FS/LS，基于连接设备1’b1:FS/LS支持的最大速度，即使连接设备可以支持HS
 */
#define USB_H_FSLSSUPP    (BIT(2))
#define USB_H_FSLSSUPP_M  (USB_H_FSLSSUPP_V << USB_H_FSLSSUPP_S)
#define USB_H_FSLSSUPP_V  0x00000001
#define USB_H_FSLSSUPP_S  2
/** USB_H_ENA32KHZS:R/W；位位置：[7]；默认值：0；1'b0:32 KHz暂停模式已禁用1'b1:32 KHz暂停模式已启用
 */
#define USB_H_ENA32KHZS    (BIT(7))
#define USB_H_ENA32KHZS_M  (USB_H_ENA32KHZS_V << USB_H_ENA32KHZS_S)
#define USB_H_ENA32KHZS_V  0x00000001
#define USB_H_ENA32KHZS_S  7
/** USB_H_descma:R/W；位位置：[23]；默认值：0；GAHBCFG_REG.USB_dman=0，HCFG_REG。USB_DESCDMA=0=>从模式GAHBCFG_REG。USB_DMAEN=0，HCFG_REG。USB_DESCDMA=1=>GAHBCFG_REG无效。USB_DMAEN=1，HCFG_REG。USB_DESCDMA=0=>缓冲DMA GAHBCFG_REG。USB_DMAEN=1，HCFG_REG。USB_DESCDMA=1=>分散/收集DMA模式
 */
#define USB_H_DESCDMA    (BIT(23))
#define USB_H_DESCDMA_M  (USB_H_DESCDMA_V << USB_H_DESCDMA_S)
#define USB_H_DESCDMA_V  0x00000001
#define USB_H_DESCDMA_S  23
/** USB_H_frent:R/W；比特位置：[26:24]；默认值：0；帧列表条目2'b00:8条目2'b01:16条目2'b10:32条目2'b11:64条目
 */
#define USB_H_FRLISTEN    0x00000003
#define USB_H_FRLISTEN_M  (USB_H_FRLISTEN_V << USB_H_FRLISTEN_S)
#define USB_H_FRLISTEN_V  0x00000003
#define USB_H_FRLISTEN_S  24
/** USB_H_PERSCHEDENA:R/W；位位置：[26]；默认值：0；0x0（DISABLED）：禁用核心内的定期调度0x1（ENABLED）：启用核心内的周期性调度
 */
#define USB_H_PERSCHEDENA    (BIT(26))
#define USB_H_PERSCHEDENA_M  (USB_H_PERSCHEDENA_V << USB_H_PERSCHEDENA_S)
#define USB_H_PERSCHEDENA_V  0x00000001
#define USB_H_PERSCHEDENA_S  26
/** USB_H_MODECHTIMEN:R/W；位位置：[31]；默认值：0；模式更改就绪计时器启用，1’b0：主机核心在恢复结束时等待200个PHY时钟周期或SE0行状态，以将操作模式从2’b10更改为2’b00。
 */
#define USB_H_MODECHTIMEN    (BIT(31))
#define USB_H_MODECHTIMEN_M  (USB_H_MODECHTIMEN_V << USB_H_MODECHTIMEN_S)
#define USB_H_MODECHTIMEN_V  0x00000001
#define USB_H_MODECHTIMEN_S  31


/** USB_HFIR_REG寄存器主机帧间隔寄存器
 */
#define USB_HFIR_REG (SOC_DPORT_USB_BASE + 0x404)
/** USB_FRINT:R/W；位位置：[16:0]；默认值：6103；帧间隔.1 ms（FS/LS的PHY时钟频率）
 */
#define USB_FRINT    0x0000FFFF
#define USB_FRINT_M  (USB_FRINT_V << USB_FRINT_S)
#define USB_FRINT_V  0x0000FFFF
#define USB_FRINT_S  0
/** USB_hfirldctrl:R/W；位位置：[16]；默认值：0；重新加载控件1’b0:HFIR无法动态重新加载1’b1：HFIR可以在运行时动态重新加载
 */
#define USB_HFIRRLDCTRL    (BIT(16))
#define USB_HFIRRLDCTRL_M  (USB_HFIRRLDCTRL_V << USB_HFIRRLDCTRL_S)
#define USB_HFIRRLDCTRL_V  0x00000001
#define USB_HFIRRLDCTRL_S  16


/** USB_HFLBADDR_REG寄存器主机帧列表基址寄存器
 */
#define USB_HFLBADDR_REG (SOC_DPORT_USB_BASE + 0x41c)
/** USB_HFLBADDR:R/W；位位置：[32:0]；默认值：0；帧列表的起始地址。此寄存器仅用于同步和中断信道。
 */
#define USB_HFLBADDR    0xFFFFFFFF
#define USB_HFLBADDR_M  (USB_HFLBADDR_V << USB_HFLBADDR_S)
#define USB_HFLBADDR_V  0xFFFFFFFF
#define USB_HFLBADDR_S  0


/** USB_HPRT_REG寄存器主机端口控制和状态寄存器
 */
#define USB_HPRT_REG (SOC_DPORT_USB_BASE + 0x440)
/** USB_prtconnests:RO；位位置：[0]；默认值：0；端口连接状态0x0：没有设备连接到端口0x1：有设备连接到该端口
 */
#define USB_PRTCONNSTS    (BIT(0))
#define USB_PRTCONNSTS_M  (USB_PRTCONNSTS_V << USB_PRTCONNSTS_S)
#define USB_PRTCONNSTS_V  0x00000001
#define USB_PRTCONNSTS_S  0
/** USB_prtconnedet:R/W；位位置：[1]；默认值：0；检测到端口连接。0x1：检测到设备连接。0x0:未检测到设备连接。
 */
#define USB_PRTCONNDET    (BIT(1))
#define USB_PRTCONNDET_M  (USB_PRTCONNDET_V << USB_PRTCONNDET_S)
#define USB_PRTCONNDET_V  0x00000001
#define USB_PRTCONNDET_S  1
/** USB_PRTENA:R/W；位位置：[2]；默认值：0；端口启用1’b0：端口禁用1’b1：端口启用
 */
#define USB_PRTENA    (BIT(2))
#define USB_PRTENA_M  (USB_PRTENA_V << USB_PRTENA_S)
#define USB_PRTENA_V  0x00000001
#define USB_PRTENA_S  2
/** USB_PRTENCHNG:R/W；位位置：[3]；默认值：0；端口启用/禁用更改0x0：端口启用位2未更改0x1：端口禁用位2已更改
 */
#define USB_PRTENCHNG    (BIT(3))
#define USB_PRTENCHNG_M  (USB_PRTENCHNG_V << USB_PRTENCHNG_S)
#define USB_PRTENCHNG_V  0x00000001
#define USB_PRTENCHNG_S  3
/** USB_PRTOVRCURRACT:RO；位位置：[4]；默认值：0；端口过电流激活1’b0：无过电流条件1’b1：过电流条件
 */
#define USB_PRTOVRCURRACT    (BIT(4))
#define USB_PRTOVRCURRACT_M  (USB_PRTOVRCURRACT_V << USB_PRTOVRCURRACT_S)
#define USB_PRTOVRCURRACT_V  0x00000001
#define USB_PRTOVRCURRACT_S  4
/** USB_PRTOVRCURRCHNG:R/W；位位置：[5]；默认值：0；端口过电流更改0x0：端口过电流状态状态未更改0x1：端口电流状态已更改
 */
#define USB_PRTOVRCURRCHNG    (BIT(5))
#define USB_PRTOVRCURRCHNG_M  (USB_PRTOVRCURRCHNG_V << USB_PRTOVRCURRCHNG_S)
#define USB_PRTOVRCURRCHNG_V  0x00000001
#define USB_PRTOVRCURRCHNG_S  5
/** USB_PRTRES:R/W；位位置：[6]；默认值：0；端口恢复1’b0：无恢复驱动1’b1：恢复驱动
 */
#define USB_PRTRES    (BIT(6))
#define USB_PRTRES_M  (USB_PRTRES_V << USB_PRTRES_S)
#define USB_PRTRES_V  0x00000001
#define USB_PRTRES_S  6
/** USB_PRTSUSP:R/W；位位置：[7]；默认值：0；端口挂起1’b0：端口未处于挂起模式1’b1：端口处于挂起状态
 */
#define USB_PRTSUSP    (BIT(7))
#define USB_PRTSUSP_M  (USB_PRTSUSP_V << USB_PRTSUSP_S)
#define USB_PRTSUSP_V  0x00000001
#define USB_PRTSUSP_S  7
/** USB_PRTRST:R/W；位位置：[8]；默认值：0；端口重置。1’b0：端口未重置1’b1：端口重置
 */
#define USB_PRTRST    (BIT(8))
#define USB_PRTRST_M  (USB_PRTRST_V << USB_PRTRST_S)
#define USB_PRTRST_V  0x00000001
#define USB_PRTRST_S  8
/** USB_PRTLNSTS:RO；比特位置：[12:10]；默认值：0；端口线状态位[10]：D+位[11]的逻辑电平：D的逻辑电平-
 */
#define USB_PRTLNSTS    0x00000003
#define USB_PRTLNSTS_M  (USB_PRTLNSTS_V << USB_PRTLNSTS_S)
#define USB_PRTLNSTS_V  0x00000003
#define USB_PRTLNSTS_S  10
/** USB_PRTPWR:R/W；位位置：[12]；默认值：0；端口电源1’b0：关闭电源1’b1：打开电源
 */
#define USB_PRTPWR    (BIT(12))
#define USB_PRTPWR_M  (USB_PRTPWR_V << USB_PRTPWR_S)
#define USB_PRTPWR_V  0x00000001
#define USB_PRTPWR_S  12
/** USB_PRTTSTCTL:R/W；比特位置：[17:13]；默认值：0；端口测试控制4'b0000:测试模式已禁用4'b0001:测试_J模式4'b00010:测试_K模式4'b 0011:测试_SE0_NAK模式4'b0100:测试包模式4'b10101:测试_强制_启用其他：保留
 */
#define USB_PRTTSTCTL    0x0000000F
#define USB_PRTTSTCTL_M  (USB_PRTTSTCTL_V << USB_PRTTSTCTL_S)
#define USB_PRTTSTCTL_V  0x0000000F
#define USB_PRTTSTCTL_S  13
/** USB_PRTSPD:RO；比特位置：[19:17]；默认值：0；端口速度2’b00：高速2’b01：全速2’b10：低速2’b11：保留
 */
#define USB_PRTSPD    0x00000003
#define USB_PRTSPD_M  (USB_PRTSPD_V << USB_PRTSPD_S)
#define USB_PRTSPD_V  0x00000003
#define USB_PRTSPD_S  17


/** USB_HCCHAR0_REG寄存器主机通道0特性寄存器
 */
#define USB_HCCHAR0_REG (SOC_DPORT_USB_BASE + 0x500)
/** USB_H_mp0:R/W；位位置：[11:0]；默认值：0；最大数据包大小。
 */
#define USB_H_MPS0    0x000007FF
#define USB_H_MPS0_M  (USB_H_MPS0_V << USB_H_MPS0_S)
#define USB_H_MPS0_V  0x000007FF
#define USB_H_MPS0_S  0
/** USB_H_EPNUM0:R/W；比特位置：[15:11]；默认值：0；端点编号。
 */
#define USB_H_EPNUM0    0x0000000F
#define USB_H_EPNUM0_M  (USB_H_EPNUM0_V << USB_H_EPNUM0_S)
#define USB_H_EPNUM0_V  0x0000000F
#define USB_H_EPNUM0_S  11
/** USB_H_EPDIR0:R/W；位位置：[15]；默认值：0；1’b0：输出1’b1：输入
 */
#define USB_H_EPDIR0    (BIT(15))
#define USB_H_EPDIR0_M  (USB_H_EPDIR0_V << USB_H_EPDIR0_S)
#define USB_H_EPDIR0_V  0x00000001
#define USB_H_EPDIR0_S  15
/** USB_H_LSPDDEV0:R/W；位位置：[17]；默认值：0；0x0：不与低速设备通信0x1：与低速设备进行通信
 */
#define USB_H_LSPDDEV0    (BIT(17))
#define USB_H_LSPDDEV0_M  (USB_H_LSPDDEV0_V << USB_H_LSPDDEV0_S)
#define USB_H_LSPDDEV0_V  0x00000001
#define USB_H_LSPDDEV0_S  17
/** USB_H_EPTYPE0:R/W；比特位置：[20:18]；默认值：0；0x0（CTRL）：控制0x1（ISOC）：同步0x2（BULK）：批量0x3（INTERR）：中断
 */
#define USB_H_EPTYPE0    0x00000003
#define USB_H_EPTYPE0_M  (USB_H_EPTYPE0_V << USB_H_EPTYPE0_S)
#define USB_H_EPTYPE0_V  0x00000003
#define USB_H_EPTYPE0_S  18
/** USB_H_EC0:R/W；位位置：[21]；默认值：0；多计数（MC）/错误计数（EC）0x0（RESERVED）：保留。此字段产生未定义的结果0x1（TRANSONE）：1个事务0x2（TRANSTWO）：每个微帧将为此端点发出2个事务0x3（TRANSTHREE）：每个微帧将为此终结点发出3个事务
 */
#define USB_H_EC0    (BIT(21))
#define USB_H_EC0_M  (USB_H_EC0_V << USB_H_EC0_S)
#define USB_H_EC0_V  0x00000001
#define USB_H_EC0_S  21
/** USB_H_DEVADDR0:R/W；位位置：[29:22]；默认值：0；设备地址。此字段选择用作数据源或接收器的特定设备。
 */
#define USB_H_DEVADDR0    0x0000007F
#define USB_H_DEVADDR0_M  (USB_H_DEVADDR0_V << USB_H_DEVADDR0_S)
#define USB_H_DEVADDR0_V  0x0000007F
#define USB_H_DEVADDR0_S  22
/** USB_H_odfrm0:R/W；位位置：[29]；默认值：0；奇数帧1’b0：偶数（微）帧1’b1：奇数（微）
 */
#define USB_H_ODDFRM0    (BIT(29))
#define USB_H_ODDFRM0_M  (USB_H_ODDFRM0_V << USB_H_ODDFRM0_S)
#define USB_H_ODDFRM0_V  0x00000001
#define USB_H_ODDFRM0_S  29
/** USB_H_CHDIS0:R/W；位位置：[30]；默认值：0；信道禁用0x0：发送/接收正常0x1：停止在信道上发送/接收数据
 */
#define USB_H_CHDIS0    (BIT(30))
#define USB_H_CHDIS0_M  (USB_H_CHDIS0_V << USB_H_CHDIS0_S)
#define USB_H_CHDIS0_V  0x00000001
#define USB_H_CHDIS0_S  30
/** USB_H_CHENA0:R/W；位位置：[31]；默认值：0；通道启用0x0：如果启用了分散/聚集模式，则表示描述符结构尚未就绪。如果散射/聚集模式被禁用，则表示通道被禁用0x1：如果散射/汇聚模式被启用，则表示描述符结构和数据缓冲区已设置，该通道可以访问描述符。如果“散布/聚集”模式已禁用，则表示通道已启用
 */
#define USB_H_CHENA0    (BIT(31))
#define USB_H_CHENA0_M  (USB_H_CHENA0_V << USB_H_CHENA0_S)
#define USB_H_CHENA0_V  0x00000001
#define USB_H_CHENA0_S  31


/** USB_HCDMA0_REG寄存器主机通道0 DMA地址寄存器
 */
#define USB_HCDMA0_REG (SOC_DPORT_USB_BASE + 0x514)
/** USB_H_daddr0:R/W；位位置：[32:0]；默认值：0；非等时散点采集DMA（DescDMA）模式：[31:9]：DMA地址[8:3]：当前传输描述[2:0]：保留
 */
#define USB_H_DMAADDR0    0xFFFFFFFF
#define USB_H_DMAADDR0_M  (USB_H_DMAADDR0_V << USB_H_DMAADDR0_S)
#define USB_H_DMAADDR0_V  0xFFFFFFFF
#define USB_H_DMAADDR0_S  0


/** USB_HCCHAR1_REG寄存器主机通道1特性寄存器
 */
#define USB_HCCHAR1_REG (SOC_DPORT_USB_BASE + 0x520)
/** USB_H_MPS1:R/W；位位置：[11:0]；默认值：0；最大数据包大小。
 */
#define USB_H_MPS1    0x000007FF
#define USB_H_MPS1_M  (USB_H_MPS1_V << USB_H_MPS1_S)
#define USB_H_MPS1_V  0x000007FF
#define USB_H_MPS1_S  0
/** USB_H_EPNUM1:R/W；比特位置：[15:11]；默认值：0；端点编号。
 */
#define USB_H_EPNUM1    0x0000000F
#define USB_H_EPNUM1_M  (USB_H_EPNUM1_V << USB_H_EPNUM1_S)
#define USB_H_EPNUM1_V  0x0000000F
#define USB_H_EPNUM1_S  11
/** USB_H_EPDIR1:R/W；位位置：[15]；默认值：0；1’b0：输出1’b1：输入
 */
#define USB_H_EPDIR1    (BIT(15))
#define USB_H_EPDIR1_M  (USB_H_EPDIR1_V << USB_H_EPDIR1_S)
#define USB_H_EPDIR1_V  0x00000001
#define USB_H_EPDIR1_S  15
/** USB_H_lspdev1:R/W；位位置：[17]；默认值：0；0x0：不与低速设备通信0x1：与低速设备进行通信
 */
#define USB_H_LSPDDEV1    (BIT(17))
#define USB_H_LSPDDEV1_M  (USB_H_LSPDDEV1_V << USB_H_LSPDDEV1_S)
#define USB_H_LSPDDEV1_V  0x00000001
#define USB_H_LSPDDEV1_S  17
/** USB_H_EPTYPE1:R/W；比特位置：[20:18]；默认值：0；0x0（CTRL）：控制0x1（ISOC）：同步0x2（BULK）：批量0x3（INTERR）：中断
 */
#define USB_H_EPTYPE1    0x00000003
#define USB_H_EPTYPE1_M  (USB_H_EPTYPE1_V << USB_H_EPTYPE1_S)
#define USB_H_EPTYPE1_V  0x00000003
#define USB_H_EPTYPE1_S  18
/** USB_H_EC1:R/W；位位置：[21]；默认值：0；多计数（MC）/错误计数（EC）0x0（RESERVED）：保留。此字段产生未定义的结果0x1（TRANSONE）：1个事务0x2（TRANSTWO）：每个微帧将为此端点发出2个事务0x3（TRANSTHREE）：每个微帧将为此终结点发出3个事务
 */
#define USB_H_EC1    (BIT(21))
#define USB_H_EC1_M  (USB_H_EC1_V << USB_H_EC1_S)
#define USB_H_EC1_V  0x00000001
#define USB_H_EC1_S  21
/** USB_H_devadr1:R/W；位位置：[29:22]；默认值：0；设备地址。此字段选择用作数据源或接收器的特定设备。
 */
#define USB_H_DEVADDR1    0x0000007F
#define USB_H_DEVADDR1_M  (USB_H_DEVADDR1_V << USB_H_DEVADDR1_S)
#define USB_H_DEVADDR1_V  0x0000007F
#define USB_H_DEVADDR1_S  22
/** USB_H_odfrm1:R/W；位位置：[29]；默认值：0；奇数帧1’b0：偶数（微）帧1’b1：奇数（微）
 */
#define USB_H_ODDFRM1    (BIT(29))
#define USB_H_ODDFRM1_M  (USB_H_ODDFRM1_V << USB_H_ODDFRM1_S)
#define USB_H_ODDFRM1_V  0x00000001
#define USB_H_ODDFRM1_S  29
/** USB_H_CHDIS1:R/W；位位置：[30]；默认值：0；信道禁用0x0：发送/接收正常0x1：停止在信道上发送/接收数据
 */
#define USB_H_CHDIS1    (BIT(30))
#define USB_H_CHDIS1_M  (USB_H_CHDIS1_V << USB_H_CHDIS1_S)
#define USB_H_CHDIS1_V  0x00000001
#define USB_H_CHDIS1_S  30
/** USB_H_CHENA1:R/W；位位置：[31]；默认值：0；通道启用0x0：如果启用了分散/聚集模式，则表示描述符结构尚未就绪。如果散射/聚集模式被禁用，则表示通道被禁用0x1：如果散射/汇聚模式被启用，则表示描述符结构和数据缓冲区已设置，该通道可以访问描述符。如果“散布/聚集”模式已禁用，则表示通道已启用
 */
#define USB_H_CHENA1    (BIT(31))
#define USB_H_CHENA1_M  (USB_H_CHENA1_V << USB_H_CHENA1_S)
#define USB_H_CHENA1_V  0x00000001
#define USB_H_CHENA1_S  31


/** USB_HCDMA1_REG寄存器主机通道1 DMA地址寄存器
 */
#define USB_HCDMA1_REG (SOC_DPORT_USB_BASE + 0x534)
/** USB_H_daddr1:R/W；位位置：[32:0]；默认值：0；非等时散点采集DMA（DescDMA）模式：[31:9]：DMA地址[8:3]：当前传输描述[2:0]：保留
 */
#define USB_H_DMAADDR1    0xFFFFFFFF
#define USB_H_DMAADDR1_M  (USB_H_DMAADDR1_V << USB_H_DMAADDR1_S)
#define USB_H_DMAADDR1_V  0xFFFFFFFF
#define USB_H_DMAADDR1_S  0


/** USB_HCCHAR2_REG寄存器主机通道2特性寄存器
 */
#define USB_HCCHAR2_REG (SOC_DPORT_USB_BASE + 0x540)
/** USB_H_MPS2:R/W；位位置：[11:0]；默认值：0；最大数据包大小。
 */
#define USB_H_MPS2    0x000007FF
#define USB_H_MPS2_M  (USB_H_MPS2_V << USB_H_MPS2_S)
#define USB_H_MPS2_V  0x000007FF
#define USB_H_MPS2_S  0
/** USB_H_EPNUM2:R/W；比特位置：[15:11]；默认值：0；端点编号。
 */
#define USB_H_EPNUM2    0x0000000F
#define USB_H_EPNUM2_M  (USB_H_EPNUM2_V << USB_H_EPNUM2_S)
#define USB_H_EPNUM2_V  0x0000000F
#define USB_H_EPNUM2_S  11
/** USB_H_EPDIR2:R/W；位位置：[15]；默认值：0；1’b0：输出1’b1：输入
 */
#define USB_H_EPDIR2    (BIT(15))
#define USB_H_EPDIR2_M  (USB_H_EPDIR2_V << USB_H_EPDIR2_S)
#define USB_H_EPDIR2_V  0x00000001
#define USB_H_EPDIR2_S  15
/** USB_H_lspdev2:R/W；位位置：[17]；默认值：0；0x0：不与低速设备通信0x1：与低速设备进行通信
 */
#define USB_H_LSPDDEV2    (BIT(17))
#define USB_H_LSPDDEV2_M  (USB_H_LSPDDEV2_V << USB_H_LSPDDEV2_S)
#define USB_H_LSPDDEV2_V  0x00000001
#define USB_H_LSPDDEV2_S  17
/** USB_H_EPTYPE2:R/W；比特位置：[20:18]；默认值：0；0x0（CTRL）：控制0x1（ISOC）：同步0x2（BULK）：批量0x3（INTERR）：中断
 */
#define USB_H_EPTYPE2    0x00000003
#define USB_H_EPTYPE2_M  (USB_H_EPTYPE2_V << USB_H_EPTYPE2_S)
#define USB_H_EPTYPE2_V  0x00000003
#define USB_H_EPTYPE2_S  18
/** USB_H_EC2:R/W；位位置：[21]；默认值：0；多计数（MC）/错误计数（EC）0x0（RESERVED）：保留。此字段产生未定义的结果0x1（TRANSONE）：1个事务0x2（TRANSTWO）：每个微帧将为此端点发出2个事务0x3（TRANSTHREE）：每个微帧将为此终结点发出3个事务
 */
#define USB_H_EC2    (BIT(21))
#define USB_H_EC2_M  (USB_H_EC2_V << USB_H_EC2_S)
#define USB_H_EC2_V  0x00000001
#define USB_H_EC2_S  21
/** USB_H_DEVADDR2:R/W；位位置：[29:22]；默认值：0；设备地址。此字段选择用作数据源或接收器的特定设备。
 */
#define USB_H_DEVADDR2    0x0000007F
#define USB_H_DEVADDR2_M  (USB_H_DEVADDR2_V << USB_H_DEVADDR2_S)
#define USB_H_DEVADDR2_V  0x0000007F
#define USB_H_DEVADDR2_S  22
/** USB_H_odfrfrm2:R/W；位位置：[29]；默认值：0；奇数帧1’b0：偶数（微）帧1’b1：奇数（微）
 */
#define USB_H_ODDFRM2    (BIT(29))
#define USB_H_ODDFRM2_M  (USB_H_ODDFRM2_V << USB_H_ODDFRM2_S)
#define USB_H_ODDFRM2_V  0x00000001
#define USB_H_ODDFRM2_S  29
/** USB_H_CHDIS2:R/W；位位置：[30]；默认值：0；信道禁用0x0：发送/接收正常0x1：停止在信道上发送/接收数据
 */
#define USB_H_CHDIS2    (BIT(30))
#define USB_H_CHDIS2_M  (USB_H_CHDIS2_V << USB_H_CHDIS2_S)
#define USB_H_CHDIS2_V  0x00000001
#define USB_H_CHDIS2_S  30
/** USB_H_CHENA2:R/W；位位置：[31]；默认值：0；通道启用0x0：如果启用了分散/聚集模式，则表示描述符结构尚未就绪。如果散射/聚集模式被禁用，则表示通道被禁用0x1：如果散射/汇聚模式被启用，则表示描述符结构和数据缓冲区已设置，该通道可以访问描述符。如果“散布/聚集”模式已禁用，则表示通道已启用
 */
#define USB_H_CHENA2    (BIT(31))
#define USB_H_CHENA2_M  (USB_H_CHENA2_V << USB_H_CHENA2_S)
#define USB_H_CHENA2_V  0x00000001
#define USB_H_CHENA2_S  31


/** USB_HCDMA2_REG寄存器主机通道2 DMA地址寄存器
 */
#define USB_HCDMA2_REG (SOC_DPORT_USB_BASE + 0x554)
/** USB_H_daddr2:R/W；位位置：[32:0]；默认值：0；非等时散点采集DMA（DescDMA）模式：[31:9]：DMA地址[8:3]：当前传输描述[2:0]：保留
 */
#define USB_H_DMAADDR2    0xFFFFFFFF
#define USB_H_DMAADDR2_M  (USB_H_DMAADDR2_V << USB_H_DMAADDR2_S)
#define USB_H_DMAADDR2_V  0xFFFFFFFF
#define USB_H_DMAADDR2_S  0


/** USB_HCCHAR3_REG寄存器主机通道3特性寄存器
 */
#define USB_HCCHAR3_REG (SOC_DPORT_USB_BASE + 0x560)
/** USB_H_MPS3:R/W；位位置：[11:0]；默认值：0；最大数据包大小。
 */
#define USB_H_MPS3    0x000007FF
#define USB_H_MPS3_M  (USB_H_MPS3_V << USB_H_MPS3_S)
#define USB_H_MPS3_V  0x000007FF
#define USB_H_MPS3_S  0
/** USB_H_EPNUM3:R/W；比特位置：[15:11]；默认值：0；端点编号。
 */
#define USB_H_EPNUM3    0x0000000F
#define USB_H_EPNUM3_M  (USB_H_EPNUM3_V << USB_H_EPNUM3_S)
#define USB_H_EPNUM3_V  0x0000000F
#define USB_H_EPNUM3_S  11
/** USB_H_EPDIR3:R/W；位位置：[15]；默认值：0；1’b0：输出1’b1：输入
 */
#define USB_H_EPDIR3    (BIT(15))
#define USB_H_EPDIR3_M  (USB_H_EPDIR3_V << USB_H_EPDIR3_S)
#define USB_H_EPDIR3_V  0x00000001
#define USB_H_EPDIR3_S  15
/** USB_H_lspdev3:R/W；位位置：[17]；默认值：0；0x0：不与低速设备通信0x1：与低速设备进行通信
 */
#define USB_H_LSPDDEV3    (BIT(17))
#define USB_H_LSPDDEV3_M  (USB_H_LSPDDEV3_V << USB_H_LSPDDEV3_S)
#define USB_H_LSPDDEV3_V  0x00000001
#define USB_H_LSPDDEV3_S  17
/** USB_H_EPTYPE3:R/W；比特位置：[20:18]；默认值：0；0x0（CTRL）：控制0x1（ISOC）：同步0x2（BULK）：批量0x3（INTERR）：中断
 */
#define USB_H_EPTYPE3    0x00000003
#define USB_H_EPTYPE3_M  (USB_H_EPTYPE3_V << USB_H_EPTYPE3_S)
#define USB_H_EPTYPE3_V  0x00000003
#define USB_H_EPTYPE3_S  18
/** USB_H_EC3:R/W；位位置：[21]；默认值：0；多计数（MC）/错误计数（EC）0x0（RESERVED）：保留。此字段产生未定义的结果0x1（TRANSONE）：1个事务0x2（TRANSTWO）：每个微帧将为此端点发出2个事务0x3（TRANSTHREE）：每个微帧将为此终结点发出3个事务
 */
#define USB_H_EC3    (BIT(21))
#define USB_H_EC3_M  (USB_H_EC3_V << USB_H_EC3_S)
#define USB_H_EC3_V  0x00000001
#define USB_H_EC3_S  21
/** USB_H_DEVADDR3:R/W；位位置：[29:22]；默认值：0；设备地址。此字段选择用作数据源或接收器的特定设备。
 */
#define USB_H_DEVADDR3    0x0000007F
#define USB_H_DEVADDR3_M  (USB_H_DEVADDR3_V << USB_H_DEVADDR3_S)
#define USB_H_DEVADDR3_V  0x0000007F
#define USB_H_DEVADDR3_S  22
/** USB_H_odfrm3:R/W；位位置：[29]；默认值：0；奇数帧1’b0：偶数（微）帧1’b1：奇数（微）
 */
#define USB_H_ODDFRM3    (BIT(29))
#define USB_H_ODDFRM3_M  (USB_H_ODDFRM3_V << USB_H_ODDFRM3_S)
#define USB_H_ODDFRM3_V  0x00000001
#define USB_H_ODDFRM3_S  29
/** USB_H_CHDIS3:R/W；位位置：[30]；默认值：0；信道禁用0x0：发送/接收正常0x1：停止在信道上发送/接收数据
 */
#define USB_H_CHDIS3    (BIT(30))
#define USB_H_CHDIS3_M  (USB_H_CHDIS3_V << USB_H_CHDIS3_S)
#define USB_H_CHDIS3_V  0x00000001
#define USB_H_CHDIS3_S  30
/** USB_H_CHENA3:R/W；位位置：[31]；默认值：0；通道启用0x0：如果启用了分散/聚集模式，则表示描述符结构尚未就绪。如果散射/聚集模式被禁用，则表示通道被禁用0x1：如果散射/汇聚模式被启用，则表示描述符结构和数据缓冲区已设置，该通道可以访问描述符。如果“散布/聚集”模式已禁用，则表示通道已启用
 */
#define USB_H_CHENA3    (BIT(31))
#define USB_H_CHENA3_M  (USB_H_CHENA3_V << USB_H_CHENA3_S)
#define USB_H_CHENA3_V  0x00000001
#define USB_H_CHENA3_S  31


/** USB_HCDMA3_REG寄存器主机通道3 DMA地址寄存器
 */
#define USB_HCDMA3_REG (SOC_DPORT_USB_BASE + 0x574)
/** USB_H_daddr3:R/W；位位置：[32:0]；默认值：0；非等时散点采集DMA（DescDMA）模式：[31:9]：DMA地址[8:3]：当前传输描述[2:0]：保留
 */
#define USB_H_DMAADDR3    0xFFFFFFFF
#define USB_H_DMAADDR3_M  (USB_H_DMAADDR3_V << USB_H_DMAADDR3_S)
#define USB_H_DMAADDR3_V  0xFFFFFFFF
#define USB_H_DMAADDR3_S  0


/** USB_HCCHAR4_REG寄存器主机通道4特性寄存器
 */
#define USB_HCCHAR4_REG (SOC_DPORT_USB_BASE + 0x580)
/** USB_H_ps4:R/W；位位置：[11:0]；默认值：0；最大数据包大小。
 */
#define USB_H_MPS4    0x000007FF
#define USB_H_MPS4_M  (USB_H_MPS4_V << USB_H_MPS4_S)
#define USB_H_MPS4_V  0x000007FF
#define USB_H_MPS4_S  0
/** USB_H_EPNUM4:R/W；比特位置：[15:11]；默认值：0；端点编号。
 */
#define USB_H_EPNUM4    0x0000000F
#define USB_H_EPNUM4_M  (USB_H_EPNUM4_V << USB_H_EPNUM4_S)
#define USB_H_EPNUM4_V  0x0000000F
#define USB_H_EPNUM4_S  11
/** USB_H_EPDIR4:R/W；位位置：[15]；默认值：0；1’b0：输出1’b1：输入
 */
#define USB_H_EPDIR4    (BIT(15))
#define USB_H_EPDIR4_M  (USB_H_EPDIR4_V << USB_H_EPDIR4_S)
#define USB_H_EPDIR4_V  0x00000001
#define USB_H_EPDIR4_S  15
/** USB_H_LSPDDEV4:R/W；位位置：[17]；默认值：0；0x0：不与低速设备通信0x1：与低速设备进行通信
 */
#define USB_H_LSPDDEV4    (BIT(17))
#define USB_H_LSPDDEV4_M  (USB_H_LSPDDEV4_V << USB_H_LSPDDEV4_S)
#define USB_H_LSPDDEV4_V  0x00000001
#define USB_H_LSPDDEV4_S  17
/** USB_H_EPTYPE4:R/W；比特位置：[20:18]；默认值：0；0x0（CTRL）：控制0x1（ISOC）：同步0x2（BULK）：批量0x3（INTERR）：中断
 */
#define USB_H_EPTYPE4    0x00000003
#define USB_H_EPTYPE4_M  (USB_H_EPTYPE4_V << USB_H_EPTYPE4_S)
#define USB_H_EPTYPE4_V  0x00000003
#define USB_H_EPTYPE4_S  18
/** USB_H_EC4:R/W；位位置：[21]；默认值：0；多计数（MC）/错误计数（EC）0x0（RESERVED）：保留。此字段产生未定义的结果0x1（TRANSONE）：1个事务0x2（TRANSTWO）：每个微帧将为此端点发出2个事务0x3（TRANSTHREE）：每个微帧将为此终结点发出3个事务
 */
#define USB_H_EC4    (BIT(21))
#define USB_H_EC4_M  (USB_H_EC4_V << USB_H_EC4_S)
#define USB_H_EC4_V  0x00000001
#define USB_H_EC4_S  21
/** USB_H_devadr4:R/W；位位置：[29:22]；默认值：0；设备地址。此字段选择用作数据源或接收器的特定设备。
 */
#define USB_H_DEVADDR4    0x0000007F
#define USB_H_DEVADDR4_M  (USB_H_DEVADDR4_V << USB_H_DEVADDR4_S)
#define USB_H_DEVADDR4_V  0x0000007F
#define USB_H_DEVADDR4_S  22
/** USB_H_ODDFRM4:R/W；位位置：[29]；默认值：0；奇数帧1’b0：偶数（微）帧1’b1：奇数（微）
 */
#define USB_H_ODDFRM4    (BIT(29))
#define USB_H_ODDFRM4_M  (USB_H_ODDFRM4_V << USB_H_ODDFRM4_S)
#define USB_H_ODDFRM4_V  0x00000001
#define USB_H_ODDFRM4_S  29
/** USB_H_CHDIS4:R/W；位位置：[30]；默认值：0；信道禁用0x0：发送/接收正常0x1：停止在信道上发送/接收数据
 */
#define USB_H_CHDIS4    (BIT(30))
#define USB_H_CHDIS4_M  (USB_H_CHDIS4_V << USB_H_CHDIS4_S)
#define USB_H_CHDIS4_V  0x00000001
#define USB_H_CHDIS4_S  30
/** USB_H_CHENA4:R/W；位位置：[31]；默认值：0；通道启用0x0：如果启用了分散/聚集模式，则表示描述符结构尚未就绪。如果散射/聚集模式被禁用，则表示通道被禁用0x1：如果散射/汇聚模式被启用，则表示描述符结构和数据缓冲区已设置，该通道可以访问描述符。如果“散布/聚集”模式已禁用，则表示通道已启用
 */
#define USB_H_CHENA4    (BIT(31))
#define USB_H_CHENA4_M  (USB_H_CHENA4_V << USB_H_CHENA4_S)
#define USB_H_CHENA4_V  0x00000001
#define USB_H_CHENA4_S  31


/** USB_HCDMA4_REG寄存器主机通道4 DMA地址寄存器
 */
#define USB_HCDMA4_REG (SOC_DPORT_USB_BASE + 0x594)
/** USB_H_daddr4:R/W；位位置：[32:0]；默认值：0；非等时散点采集DMA（DescDMA）模式：[31:9]：DMA地址[8:3]：当前传输描述[2:0]：保留
 */
#define USB_H_DMAADDR4    0xFFFFFFFF
#define USB_H_DMAADDR4_M  (USB_H_DMAADDR4_V << USB_H_DMAADDR4_S)
#define USB_H_DMAADDR4_V  0xFFFFFFFF
#define USB_H_DMAADDR4_S  0


/** USB_HCCHAR5_REG寄存器主机通道5特性寄存器
 */
#define USB_HCCHAR5_REG (SOC_DPORT_USB_BASE + 0x5a0)
/** USB_H_MPS5:R/W；位位置：[11:0]；默认值：0；最大数据包大小。
 */
#define USB_H_MPS5    0x000007FF
#define USB_H_MPS5_M  (USB_H_MPS5_V << USB_H_MPS5_S)
#define USB_H_MPS5_V  0x000007FF
#define USB_H_MPS5_S  0
/** USB_H_EPNUM5:R/W；比特位置：[15:11]；默认值：0；端点编号。
 */
#define USB_H_EPNUM5    0x0000000F
#define USB_H_EPNUM5_M  (USB_H_EPNUM5_V << USB_H_EPNUM5_S)
#define USB_H_EPNUM5_V  0x0000000F
#define USB_H_EPNUM5_S  11
/** USB_H_EPDIR5:R/W；位位置：[15]；默认值：0；1’b0：输出1’b1：输入
 */
#define USB_H_EPDIR5    (BIT(15))
#define USB_H_EPDIR5_M  (USB_H_EPDIR5_V << USB_H_EPDIR5_S)
#define USB_H_EPDIR5_V  0x00000001
#define USB_H_EPDIR5_S  15
/** USB_H_LSPDDEV5:R/W；位位置：[17]；默认值：0；0x0：不与低速设备通信0x1：与低速设备进行通信
 */
#define USB_H_LSPDDEV5    (BIT(17))
#define USB_H_LSPDDEV5_M  (USB_H_LSPDDEV5_V << USB_H_LSPDDEV5_S)
#define USB_H_LSPDDEV5_V  0x00000001
#define USB_H_LSPDDEV5_S  17
/** USB_H_EPTYPE5:R/W；比特位置：[20:18]；默认值：0；0x0（CTRL）：控制0x1（ISOC）：同步0x2（BULK）：批量0x3（INTERR）：中断
 */
#define USB_H_EPTYPE5    0x00000003
#define USB_H_EPTYPE5_M  (USB_H_EPTYPE5_V << USB_H_EPTYPE5_S)
#define USB_H_EPTYPE5_V  0x00000003
#define USB_H_EPTYPE5_S  18
/** USB_H_EC5:R/W；位位置：[21]；默认值：0；多计数（MC）/错误计数（EC）0x0（RESERVED）：保留。此字段产生未定义的结果0x1（TRANSONE）：1个事务0x2（TRANSTWO）：每个微帧将为此端点发出2个事务0x3（TRANSTHREE）：每个微帧将为此终结点发出3个事务
 */
#define USB_H_EC5    (BIT(21))
#define USB_H_EC5_M  (USB_H_EC5_V << USB_H_EC5_S)
#define USB_H_EC5_V  0x00000001
#define USB_H_EC5_S  21
/** USB_H_DEVADDR5:R/W；位位置：[29:22]；默认值：0；设备地址。此字段选择用作数据源或接收器的特定设备。
 */
#define USB_H_DEVADDR5    0x0000007F
#define USB_H_DEVADDR5_M  (USB_H_DEVADDR5_V << USB_H_DEVADDR5_S)
#define USB_H_DEVADDR5_V  0x0000007F
#define USB_H_DEVADDR5_S  22
/** USB_H_odfrm5:R/W；位位置：[29]；默认值：0；奇数帧1’b0：偶数（微）帧1’b1：奇数（微）
 */
#define USB_H_ODDFRM5    (BIT(29))
#define USB_H_ODDFRM5_M  (USB_H_ODDFRM5_V << USB_H_ODDFRM5_S)
#define USB_H_ODDFRM5_V  0x00000001
#define USB_H_ODDFRM5_S  29
/** USB_H_CHDIS5:R/W；位位置：[30]；默认值：0；信道禁用0x0：发送/接收正常0x1：停止在信道上发送/接收数据
 */
#define USB_H_CHDIS5    (BIT(30))
#define USB_H_CHDIS5_M  (USB_H_CHDIS5_V << USB_H_CHDIS5_S)
#define USB_H_CHDIS5_V  0x00000001
#define USB_H_CHDIS5_S  30
/** USB_H_CHENA5:R/W；位位置：[31]；默认值：0；通道启用0x0：如果启用了分散/聚集模式，则表示描述符结构尚未就绪。如果散射/聚集模式被禁用，则表示通道被禁用0x1：如果散射/汇聚模式被启用，则表示描述符结构和数据缓冲区已设置，该通道可以访问描述符。如果“散布/聚集”模式已禁用，则表示通道已启用
 */
#define USB_H_CHENA5    (BIT(31))
#define USB_H_CHENA5_M  (USB_H_CHENA5_V << USB_H_CHENA5_S)
#define USB_H_CHENA5_V  0x00000001
#define USB_H_CHENA5_S  31


/** USB_HCDMA5_REG寄存器主机通道5 DMA地址寄存器
 */
#define USB_HCDMA5_REG (SOC_DPORT_USB_BASE + 0x5b4)
/** USB_H_daddr5:R/W；位位置：[32:0]；默认值：0；非等时散点采集DMA（DescDMA）模式：[31:9]：DMA地址[8:3]：当前传输描述[2:0]：保留
 */
#define USB_H_DMAADDR5    0xFFFFFFFF
#define USB_H_DMAADDR5_M  (USB_H_DMAADDR5_V << USB_H_DMAADDR5_S)
#define USB_H_DMAADDR5_V  0xFFFFFFFF
#define USB_H_DMAADDR5_S  0


/** USB_HCCHAR6_REG寄存器主机通道6特性寄存器
 */
#define USB_HCCHAR6_REG (SOC_DPORT_USB_BASE + 0x5c0)
/** USB_H_MPS6:R/W；位位置：[11:0]；默认值：0；最大数据包大小。
 */
#define USB_H_MPS6    0x000007FF
#define USB_H_MPS6_M  (USB_H_MPS6_V << USB_H_MPS6_S)
#define USB_H_MPS6_V  0x000007FF
#define USB_H_MPS6_S  0
/** USB_H_EPNUM6:R/W；比特位置：[15:11]；默认值：0；端点编号。
 */
#define USB_H_EPNUM6    0x0000000F
#define USB_H_EPNUM6_M  (USB_H_EPNUM6_V << USB_H_EPNUM6_S)
#define USB_H_EPNUM6_V  0x0000000F
#define USB_H_EPNUM6_S  11
/** USB_H_EPDIR6:R/W；位位置：[15]；默认值：0；1’b0：输出1’b1：输入
 */
#define USB_H_EPDIR6    (BIT(15))
#define USB_H_EPDIR6_M  (USB_H_EPDIR6_V << USB_H_EPDIR6_S)
#define USB_H_EPDIR6_V  0x00000001
#define USB_H_EPDIR6_S  15
/** USB_H_lspdev6:R/W；位位置：[17]；默认值：0；0x0：不与低速设备通信0x1：与低速设备进行通信
 */
#define USB_H_LSPDDEV6    (BIT(17))
#define USB_H_LSPDDEV6_M  (USB_H_LSPDDEV6_V << USB_H_LSPDDEV6_S)
#define USB_H_LSPDDEV6_V  0x00000001
#define USB_H_LSPDDEV6_S  17
/** USB_H_EPTYPE6:R/W；比特位置：[20:18]；默认值：0；0x0（CTRL）：控制0x1（ISOC）：同步0x2（BULK）：批量0x3（INTERR）：中断
 */
#define USB_H_EPTYPE6    0x00000003
#define USB_H_EPTYPE6_M  (USB_H_EPTYPE6_V << USB_H_EPTYPE6_S)
#define USB_H_EPTYPE6_V  0x00000003
#define USB_H_EPTYPE6_S  18
/** USB_H_EC6:R/W；位位置：[21]；默认值：0；多计数（MC）/错误计数（EC）0x0（RESERVED）：保留。此字段产生未定义的结果0x1（TRANSONE）：1个事务0x2（TRANSTWO）：每个微帧将为此端点发出2个事务0x3（TRANSTHREE）：每个微帧将为此终结点发出3个事务
 */
#define USB_H_EC6    (BIT(21))
#define USB_H_EC6_M  (USB_H_EC6_V << USB_H_EC6_S)
#define USB_H_EC6_V  0x00000001
#define USB_H_EC6_S  21
/** USB_H_DEVADDR6:R/W；位位置：[29:22]；默认值：0；设备地址。此字段选择用作数据源或接收器的特定设备。
 */
#define USB_H_DEVADDR6    0x0000007F
#define USB_H_DEVADDR6_M  (USB_H_DEVADDR6_V << USB_H_DEVADDR6_S)
#define USB_H_DEVADDR6_V  0x0000007F
#define USB_H_DEVADDR6_S  22
/** USB_H_odfrm6：随机；位位置：[29]；默认值：0；奇数帧1’b0：偶数（微）帧1’b1：奇数（微）
 */
#define USB_H_ODDFRM6    (BIT(29))
#define USB_H_ODDFRM6_M  (USB_H_ODDFRM6_V << USB_H_ODDFRM6_S)
#define USB_H_ODDFRM6_V  0x00000001
#define USB_H_ODDFRM6_S  29
/** USB_H_CHDIS6:R/W；位位置：[30]；默认值：0；信道禁用0x0：发送/接收正常0x1：停止在信道上发送/接收数据
 */
#define USB_H_CHDIS6    (BIT(30))
#define USB_H_CHDIS6_M  (USB_H_CHDIS6_V << USB_H_CHDIS6_S)
#define USB_H_CHDIS6_V  0x00000001
#define USB_H_CHDIS6_S  30
/** USB_H_CHENA6:R/W；位位置：[31]；默认值：0；通道启用0x0：如果启用了分散/聚集模式，则表示描述符结构尚未就绪。如果散射/聚集模式被禁用，则表示通道被禁用0x1：如果散射/汇聚模式被启用，则表示描述符结构和数据缓冲区已设置，该通道可以访问描述符。如果“散布/聚集”模式已禁用，则表示通道已启用
 */
#define USB_H_CHENA6    (BIT(31))
#define USB_H_CHENA6_M  (USB_H_CHENA6_V << USB_H_CHENA6_S)
#define USB_H_CHENA6_V  0x00000001
#define USB_H_CHENA6_S  31


/** USB_HCDMA6_REG寄存器主机通道6 DMA地址寄存器
 */
#define USB_HCDMA6_REG (SOC_DPORT_USB_BASE + 0x5d4)
/** USB_H_daddr6:R/W；位位置：[32:0]；默认值：0；非等时散点采集DMA（DescDMA）模式：[31:9]：DMA地址[8:3]：当前传输描述[2:0]：保留
 */
#define USB_H_DMAADDR6    0xFFFFFFFF
#define USB_H_DMAADDR6_M  (USB_H_DMAADDR6_V << USB_H_DMAADDR6_S)
#define USB_H_DMAADDR6_V  0xFFFFFFFF
#define USB_H_DMAADDR6_S  0


/** USB_HCCHAR7_REG寄存器主机通道7特性寄存器
 */
#define USB_HCCHAR7_REG (SOC_DPORT_USB_BASE + 0x5e0)
/** USB_H_MPS7:R/W；位位置：[11:0]；默认值：0；最大数据包大小。
 */
#define USB_H_MPS7    0x000007FF
#define USB_H_MPS7_M  (USB_H_MPS7_V << USB_H_MPS7_S)
#define USB_H_MPS7_V  0x000007FF
#define USB_H_MPS7_S  0
/** USB_H_EPNUM7:R/W；比特位置：[15:11]；默认值：0；端点编号。
 */
#define USB_H_EPNUM7    0x0000000F
#define USB_H_EPNUM7_M  (USB_H_EPNUM7_V << USB_H_EPNUM7_S)
#define USB_H_EPNUM7_V  0x0000000F
#define USB_H_EPNUM7_S  11
/** USB_H_EPDIR7:R/W；位位置：[15]；默认值：0；1’b0：输出1’b1：输入
 */
#define USB_H_EPDIR7    (BIT(15))
#define USB_H_EPDIR7_M  (USB_H_EPDIR7_V << USB_H_EPDIR7_S)
#define USB_H_EPDIR7_V  0x00000001
#define USB_H_EPDIR7_S  15
/** USB_H_lspdev7:R/W；位位置：[17]；默认值：0；0x0：不与低速设备通信0x1：与低速设备进行通信
 */
#define USB_H_LSPDDEV7    (BIT(17))
#define USB_H_LSPDDEV7_M  (USB_H_LSPDDEV7_V << USB_H_LSPDDEV7_S)
#define USB_H_LSPDDEV7_V  0x00000001
#define USB_H_LSPDDEV7_S  17
/** USB_H_EPTYPE7:R/W；比特位置：[20:18]；默认值：0；0x0（CTRL）：控制0x1（ISOC）：同步0x2（BULK）：批量0x3（INTERR）：中断
 */
#define USB_H_EPTYPE7    0x00000003
#define USB_H_EPTYPE7_M  (USB_H_EPTYPE7_V << USB_H_EPTYPE7_S)
#define USB_H_EPTYPE7_V  0x00000003
#define USB_H_EPTYPE7_S  18
/** USB_H_EC7:R/W；位位置：[21]；默认值：0；多计数（MC）/错误计数（EC）0x0（RESERVED）：保留。此字段产生未定义的结果0x1（TRANSONE）：1个事务0x2（TRANSTWO）：每个微帧将为此端点发出2个事务0x3（TRANSTHREE）：每个微帧将为此终结点发出3个事务
 */
#define USB_H_EC7    (BIT(21))
#define USB_H_EC7_M  (USB_H_EC7_V << USB_H_EC7_S)
#define USB_H_EC7_V  0x00000001
#define USB_H_EC7_S  21
/** USB_H_DEVADDR7:R/W；位位置：[29:22]；默认值：0；设备地址。此字段选择用作数据源或接收器的特定设备。
 */
#define USB_H_DEVADDR7    0x0000007F
#define USB_H_DEVADDR7_M  (USB_H_DEVADDR7_V << USB_H_DEVADDR7_S)
#define USB_H_DEVADDR7_V  0x0000007F
#define USB_H_DEVADDR7_S  22
/** USB_H_odfrm7:R/W；位位置：[29]；默认值：0；奇数帧1’b0：偶数（微）帧1’b1：奇数（微）
 */
#define USB_H_ODDFRM7    (BIT(29))
#define USB_H_ODDFRM7_M  (USB_H_ODDFRM7_V << USB_H_ODDFRM7_S)
#define USB_H_ODDFRM7_V  0x00000001
#define USB_H_ODDFRM7_S  29
/** USB_H_CHDIS7:R/W；位位置：[30]；默认值：0；信道禁用0x0：发送/接收正常0x1：停止在信道上发送/接收数据
 */
#define USB_H_CHDIS7    (BIT(30))
#define USB_H_CHDIS7_M  (USB_H_CHDIS7_V << USB_H_CHDIS7_S)
#define USB_H_CHDIS7_V  0x00000001
#define USB_H_CHDIS7_S  30
/** USB_H_CHENA7:R/W；位位置：[31]；默认值：0；通道启用0x0：如果启用了分散/聚集模式，则表示描述符结构尚未就绪。如果散射/聚集模式被禁用，则表示通道被禁用0x1：如果散射/汇聚模式被启用，则表示描述符结构和数据缓冲区已设置，该通道可以访问描述符。如果“散布/聚集”模式已禁用，则表示通道已启用
 */
#define USB_H_CHENA7    (BIT(31))
#define USB_H_CHENA7_M  (USB_H_CHENA7_V << USB_H_CHENA7_S)
#define USB_H_CHENA7_V  0x00000001
#define USB_H_CHENA7_S  31


/** USB_HCDMA7_REG寄存器主机通道7 DMA地址寄存器
 */
#define USB_HCDMA7_REG (SOC_DPORT_USB_BASE + 0x5f4)
/** USB_H_daddr7:R/W；位位置：[32:0]；默认值：0；非等时散点采集DMA（DescDMA）模式：[31:9]：DMA地址[8:3]：当前传输描述[2:0]：保留
 */
#define USB_H_DMAADDR7    0xFFFFFFFF
#define USB_H_DMAADDR7_M  (USB_H_DMAADDR7_V << USB_H_DMAADDR7_S)
#define USB_H_DMAADDR7_V  0xFFFFFFFF
#define USB_H_DMAADDR7_S  0


/** USB_DCFG_REG寄存器设备配置寄存器
 */
#define USB_DCFG_REG (SOC_DPORT_USB_BASE + 0x800)
/** USB_NZSTSOUTHSHK:R/W；位位置：[2]；默认值：0；1’b0：将接收到的OUT数据包发送到应用程序（零长度或非零长度），并根据Devce端点控制寄存器1’b1中端点的NAK和STALL位发送握手：在非零长度状态OUT事务上发送STALL握手，不将接收到OUT数据包发送给应用程序
 */
#define USB_NZSTSOUTHSHK    (BIT(2))
#define USB_NZSTSOUTHSHK_M  (USB_NZSTSOUTHSHK_V << USB_NZSTSOUTHSHK_S)
#define USB_NZSTSOUTHSHK_V  0x00000001
#define USB_NZSTSOUTHSHK_S  2
/** USB_DEVADDR:R/W；位位置：[11:4]；默认值：0；设备地址。
 */
#define USB_DEVADDR    0x0000007F
#define USB_DEVADDR_M  (USB_DEVADDR_V << USB_DEVADDR_S)
#define USB_DEVADDR_V  0x0000007F
#define USB_DEVADDR_S  4
/** USB_PERFRLINT:R/W；比特位置：[13:11]；默认值：0；0x0（EOPF80）：（micro）帧间隔的80%0x1（EOPF 85）：（micro）帧间隔0x2的85%（EOPF90）：（micro）帧时间间隔0x3的90%（EOPF95）：（微型）帧时间的95%
 */
#define USB_PERFRLINT    0x00000003
#define USB_PERFRLINT_M  (USB_PERFRLINT_V << USB_PERFRLINT_S)
#define USB_PERFRLINT_V  0x00000003
#define USB_PERFRLINT_S  11
/** USB_ENDEVOUTNAK:R/W；位位置：[13]；默认值：0；1’b0：核心在批量输出传输完成后未设置NAK 1’b1：核心在完成批量输出传输后设置NAK
 */
#define USB_ENDEVOUTNAK    (BIT(13))
#define USB_ENDEVOUTNAK_M  (USB_ENDEVOUTNAK_V << USB_ENDEVOUTNAK_S)
#define USB_ENDEVOUTNAK_V  0x00000001
#define USB_ENDEVOUTNAK_S  13
/** USB_XCVRDLY:R/W；位位置：[14]；默认值：0；0x0：设备啁啾期间xcvr_sel和txvalid之间无延迟0x1：在设备啁啾期间启用xcvr_se1和txvalid
 */
#define USB_XCVRDLY    (BIT(14))
#define USB_XCVRDLY_M  (USB_XCVRDLY_V << USB_XCVRDLY_S)
#define USB_XCVRDLY_V  0x00000001
#define USB_XCVRDLY_S  14
/** USB_erranticntsk:R/W；位位置：[15]；默认值：0；0x0：在不稳定错误时生成早期挂起中断0x1：在错误不稳定时屏蔽早期挂起
 */
#define USB_ERRATICINTMSK    (BIT(15))
#define USB_ERRATICINTMSK_M  (USB_ERRATICINTMSK_V << USB_ERRATICINTMSK_S)
#define USB_ERRATICINTMSK_V  0x00000001
#define USB_ERRATICINTMSK_S  15
/** USB_EPMISCNT:R/W；比特位置：[23:18]；默认值：4；IN端点不匹配计数。
 */
#define USB_EPMISCNT    0x0000001F
#define USB_EPMISCNT_M  (USB_EPMISCNT_V << USB_EPMISCNT_S)
#define USB_EPMISCNT_V  0x0000001F
#define USB_EPMISCNT_S  18
/** USB_DESCDMA:R/W；位位置：[23]；默认值：0；1’b0：禁用分散/聚集DMA 1’b1：启用分散/收集DMA
 */
#define USB_DESCDMA    (BIT(23))
#define USB_DESCDMA_M  (USB_DESCDMA_V << USB_DESCDMA_S)
#define USB_DESCDMA_V  0x00000001
#define USB_DESCDMA_S  23
/** USB_PERSCHINTVL:R/W；比特位置：[26:24]；默认值：0；周期调度间隔0x0（MF25）：（micro）帧0x1的25%（MF50）：（micro）帧0x2的50%（MF75）：（micro）帧0x3的75%（RESERVED）：保留
 */
#define USB_PERSCHINTVL    0x00000003
#define USB_PERSCHINTVL_M  (USB_PERSCHINTVL_V << USB_PERSCHINTVL_S)
#define USB_PERSCHINTVL_V  0x00000003
#define USB_PERSCHINTVL_S  24
/** USB_RESVALID:R/W；位位置：[32:26]；默认值：2；此字段仅在DCFG时有效。Ena32KHzSusp已设置。它控制核心从挂起恢复时的恢复时间。设置此位时，用于检测有效恢复的ResValid时钟周期数的核心计数
 */
#define USB_RESVALID    0x0000003F
#define USB_RESVALID_M  (USB_RESVALID_V << USB_RESVALID_S)
#define USB_RESVALID_V  0x0000003F
#define USB_RESVALID_S  26


/** USB_DCTL_REG寄存器设备控制寄存器
 */
#define USB_DCTL_REG (SOC_DPORT_USB_BASE + 0x804)
/** USB_RMTWKUPSIG:R/W；位位置：[0]；默认值：0；0x0：核心未发送远程唤醒信号0x1：核心发送远程唤醒信令
 */
#define USB_RMTWKUPSIG    (BIT(0))
#define USB_RMTWKUPSIG_M  (USB_RMTWKUPSIG_V << USB_RMTWKUPSIG_S)
#define USB_RMTWKUPSIG_V  0x00000001
#define USB_RMTWKUPSIG_S  0
/** USB_sft发现：R/W；位位置：[1]；默认值：0；1’b0：正常操作。当在软断开连接后清除此位时，内核将UTMI+上的phy_opmode_o信号驱动到2’00，这将生成到USB主机的设备连接事件。当设备重新连接时，USB主机会重新启动设备枚举1’b1：核心会将UTMI+上的phy_opmode_o信号驱动到2’b01，这会向USB主机生成设备断开事件
 */
#define USB_SFTDISCON    (BIT(1))
#define USB_SFTDISCON_M  (USB_SFTDISCON_V << USB_SFTDISCON_S)
#define USB_SFTDISCON_V  0x00000001
#define USB_SFTDISCON_S  1
/** USB_gnpinnaks:RO；位位置：[2]；默认值：0；0x0：根据传输FIFO中的数据可用性发送握手0x1：在所有非周期in端点上发送NAK握手，而不管传输FIFO中数据可用性如何
 */
#define USB_GNPINNAKSTS    (BIT(2))
#define USB_GNPINNAKSTS_M  (USB_GNPINNAKSTS_V << USB_GNPINNAKSTS_S)
#define USB_GNPINNAKSTS_V  0x00000001
#define USB_GNPINNAKSTS_S  2
/** USB_GOUTNAKSTS:RO；位位置：[3]；默认值：0；0x0：根据FIFO状态以及NAK和STALL位设置发送握手0x1：无数据写入RxFIFO，无论空间可用性如何。对所有数据包发送NAK握手，SETUP事务除外。丢弃所有同步OUT数据包
 */
#define USB_GOUTNAKSTS    (BIT(3))
#define USB_GOUTNAKSTS_M  (USB_GOUTNAKSTS_V << USB_GOUTNAKSTS_S)
#define USB_GOUTNAKSTS_V  0x00000001
#define USB_GOUTNAKSTS_S  3
/** USB_TSTCTL:R/W；位位置：[7:4]；默认值：0；0x0:测试模式已禁用0x1:测试_J模式0x2:测试_K模式0x3:测试_SE0_NAK模式0x4:测试包模式0x5:测试强制启用
 */
#define USB_TSTCTL    0x00000007
#define USB_TSTCTL_M  (USB_TSTCTL_V << USB_TSTCTL_S)
#define USB_TSTCTL_V  0x00000007
#define USB_TSTCTL_S  4
/** USB_SGNPINNAK:WO；位位置：[7]；默认值：0；设置全局非周期IN NAK。写入此字段将设置全局非周期IN NAK。应用程序使用此位在所有非周期IN端点上发送NAK握手。当在共享FIFO操作中的非周期端点上检测到超时条件时，内核也可以设置此位。只有在确保清除了核心中断寄存器（GINTSTS.GINNakEff）中的全局IN NAK有效位后，应用程序才能设置此位
 */
#define USB_SGNPINNAK    (BIT(7))
#define USB_SGNPINNAK_M  (USB_SGNPINNAK_V << USB_SGNPINNAK_S)
#define USB_SGNPINNAK_V  0x00000001
#define USB_SGNPINNAK_S  7
/** USB_CGNPINNAK:WO；位位置：[8]；默认值：0；清除全局非周期IN NAK。写入此字段将清除全局非周期IN NAK。
 */
#define USB_CGNPINNAK    (BIT(8))
#define USB_CGNPINNAK_M  (USB_CGNPINNAK_V << USB_CGNPINNAK_S)
#define USB_CGNPINNAK_V  0x00000001
#define USB_CGNPINNAK_S  8
/** USB_SGOUTNAK:WO；位位置：[9]；默认值：0；设置全局输出NAK。写入此字段将设置全局OUT NAK。应用程序使用此位在所有OUT端点上发送NAK握手。只有在确保核心中断寄存器（GINTSTS.GOUTNakEff）中的全局OUT NAK有效位被清除后，应用程序才能设置该位。
 */
#define USB_SGOUTNAK    (BIT(9))
#define USB_SGOUTNAK_M  (USB_SGOUTNAK_V << USB_SGOUTNAK_S)
#define USB_SGOUTNAK_V  0x00000001
#define USB_SGOUTNAK_S  9
/** USB_CGOUTNAK:WO；位位置：[10]；默认值：0；清除全局输出NAK。写入此字段将清除全局OUT NAK。
 */
#define USB_CGOUTNAK    (BIT(10))
#define USB_CGOUTNAK_M  (USB_CGOUTNAK_V << USB_CGOUTNAK_S)
#define USB_CGOUTNAK_V  0x00000001
#define USB_CGOUTNAK_S  10
/** USB_PWRONPRGDONE:R/W；位位置：[11]；默认值：0；1’b0：开机编程未完成1’b1：开机编程已完成
 */
#define USB_PWRONPRGDONE    (BIT(11))
#define USB_PWRONPRGDONE_M  (USB_PWRONPRGDONE_V << USB_PWRONPRGDONE_S)
#define USB_PWRONPRGDONE_V  0x00000001
#define USB_PWRONPRGDONE_S  11
/** USB_GMC:R/W；比特位置：[15:13]；默认值：1；全局多重计数。仅适用于分散/聚集DMA模式0x0:无效0x1:1数据包0x2:2数据包0x3:3数据包
 */
#define USB_GMC    0x00000003
#define USB_GMC_M  (USB_GMC_V << USB_GMC_S)
#define USB_GMC_V  0x00000003
#define USB_GMC_S  13
/** USB_IGNRFRMNUM:R/W；位位置：[15]；默认值：0；0：核心仅在打算传输数据包的帧号中传输数据包1：核心忽略帧号，在数据包准备就绪时立即发送数据包
 */
#define USB_IGNRFRMNUM    (BIT(15))
#define USB_IGNRFRMNUM_M  (USB_IGNRFRMNUM_V << USB_IGNRFRMNUM_S)
#define USB_IGNRFRMNUM_V  0x00000001
#define USB_IGNRFRMNUM_S  15
/** USB_NAKONBBLE:R/W；位位置：[16]；默认值：0；1’b0：禁用巴贝尔错误的NAK 1’b1：巴贝尔错误时的NAK
 */
#define USB_NAKONBBLE    (BIT(16))
#define USB_NAKONBBLE_M  (USB_NAKONBBLE_V << USB_NAKONBBLE_S)
#define USB_NAKONBBLE_V  0x00000001
#define USB_NAKONBBLE_S  16
/** USB_encoutonbna:R/W；位位置：[17]；默认值：0；1’b0：收到BNA中断后，内核禁用端点。当应用程序重新启用端点时，内核从DOEPDMA描述符1’b1开始处理：在接收到BNA中断后，内核禁用端点。当应用程序重新启用端点时，内核从接收到BNA中断的描述符开始处理
 */
#define USB_ENCOUNTONBNA    (BIT(17))
#define USB_ENCOUNTONBNA_M  (USB_ENCOUNTONBNA_V << USB_ENCOUNTONBNA_S)
#define USB_ENCOUNTONBNA_V  0x00000001
#define USB_ENCOUNTONBNA_S  17
/** USB_DEEPSLEEPBESLREJECT：R/W；位位置：[18]；默认值：0；1’b0:禁用深度睡眠BESL拒绝功能1’b1：启用深度睡眠BESL-拒绝功能
 */
#define USB_DEEPSLEEPBESLREJECT    (BIT(18))
#define USB_DEEPSLEEPBESLREJECT_M  (USB_DEEPSLEEPBESLREJECT_V << USB_DEEPSLEEPBESLREJECT_S)
#define USB_DEEPSLEEPBESLREJECT_V  0x00000001
#define USB_DEEPSLEEPBESLREJECT_S  18


/** USB_DVBUSDIS_REG寄存器设备VBUS放电时间寄存器
 */
#define USB_DVBUSDIS_REG (SOC_DPORT_USB_BASE + 0x828)
/** USB_DVBUSDIS:R/W；位位置：[16:0]；默认值：6103；指定SRP期间VBUS脉冲后的VBUS放电时间。该值等于（PHY时钟中的VBUS放电时间）/1024。您使用的值取决于PHY是以30MHz（16位数据宽度）还是60MHz（8位数据长度）运行。根据VBUS负载，此值可能需要调整。
 */
#define USB_DVBUSDIS    0x0000FFFF
#define USB_DVBUSDIS_M  (USB_DVBUSDIS_V << USB_DVBUSDIS_S)
#define USB_DVBUSDIS_V  0x0000FFFF
#define USB_DVBUSDIS_S  0


/** USB_DVBUSPULSE_REG寄存器设备VBUS脉冲时间寄存器
 */
#define USB_DVBUSPULSE_REG (SOC_DPORT_USB_BASE + 0x82c)
/** USB_DVBUSPULSE:R/W；位位置：[12:0]；默认值：1464；指定SRP期间的VBUS脉冲时间。该值等于（PHY时钟中的VBUS脉冲时间）/1024。您使用的值取决于PHY是以30MHz（16位数据宽度）还是60MHz（8位数据长度）运行。
 */
#define USB_DVBUSPULSE    0x00000FFF
#define USB_DVBUSPULSE_M  (USB_DVBUSPULSE_V << USB_DVBUSPULSE_S)
#define USB_DVBUSPULSE_V  0x00000FFF
#define USB_DVBUSPULSE_S  0


/** USB_DTHRCTL_REG寄存器设备阈值控制寄存器
 */
#define USB_DTHRCTL_REG (SOC_DPORT_USB_BASE + 0x830)
/** USB_nonisothern：R/W；位位置：[0]；默认值：0；非ISO IN端点阈值启用0x0：无阈值0x1：为非同步IN端点启用阈值
 */
#define USB_NONISOTHREN    (BIT(0))
#define USB_NONISOTHREN_M  (USB_NONISOTHREN_V << USB_NONISOTHREN_S)
#define USB_NONISOTHREN_V  0x00000001
#define USB_NONISOTHREN_S  0
/** USB_isotren:R/W；位位置：[1]；默认值：0；ISO IN端点阈值启用0x0：无阈值0x1：为同步IN端点启用阈值
 */
#define USB_ISOTHREN    (BIT(1))
#define USB_ISOTHREN_M  (USB_ISOTHREN_V << USB_ISOTHREN_S)
#define USB_ISOTHREN_V  0x00000001
#define USB_ISOTHREN_S  1
/** USB_TXTHRLEN:R/W；位位置：[11:2]；默认值：8；此字段指定DWORDS中的传输阈值大小。这也形成了MAC阈值，并指定了在核心可以开始在USB上传输之前，相应端点传输FIFO中的数据量（以字节为单位）。当AHBThrRatio的值为2'000时，阈值长度必须至少为八个DWORD。如果AHBThrRatio为非零，则应用程序需要确保AHB阈值不低于建议的八个DWORD值。该字段控制同步和非同步IN端点阈值。ThrLen的建议值应与编程的AHB突发长度（GAHBCFG.HBstLen）相同。
 */
#define USB_TXTHRLEN    0x000001FF
#define USB_TXTHRLEN_M  (USB_TXTHRLEN_V << USB_TXTHRLEN_S)
#define USB_TXTHRLEN_V  0x000001FF
#define USB_TXTHRLEN_S  2
/** USB_ahbthr比值：R/W；比特位置：[13:11]；默认值：0；2'b00:AHB阈值=MAC阈值2'b01:AHB阈值=MAC阈值/2 2'b10:AHB门限=MAC阈值/4 2'b11:AHB门限=MAC阈值/8
 */
#define USB_AHBTHRRATIO    0x00000003
#define USB_AHBTHRRATIO_M  (USB_AHBTHRRATIO_V << USB_AHBTHRRATIO_S)
#define USB_AHBTHRRATIO_V  0x00000003
#define USB_AHBTHRRATIO_S  11
/** USB_RXTHREN:R/W；位位置：[16]；默认值：0；0x0：禁用阈值设置0x1：启用接收方向的阈值设置
 */
#define USB_RXTHREN    (BIT(16))
#define USB_RXTHREN_M  (USB_RXTHREN_V << USB_RXTHREN_S)
#define USB_RXTHREN_V  0x00000001
#define USB_RXTHREN_S  16
/** USB_RXTHRLEN:R/W；比特位置：[26:17]；默认值：1；接收阈值长度。此字段指定DWORDS中的接收阈值大小。该字段还指定核心可以开始在AHB上传输之前在USB上接收的数据量。阈值长度必须至少为八个DWORD。ThrLen的建议值应与编程的AHB突发长度（GAHBCFG.HBstLen）相同。
 */
#define USB_RXTHRLEN    0x000001FF
#define USB_RXTHRLEN_M  (USB_RXTHRLEN_V << USB_RXTHRLEN_S)
#define USB_RXTHRLEN_V  0x000001FF
#define USB_RXTHRLEN_S  17
/** USB_ARBPRKEN:R/W；位位置：[27]；默认值：1；0x0：禁用DMA仲裁器停放0x1：为IN端点启用DMA仲裁器停泊
 */
#define USB_ARBPRKEN    (BIT(27))
#define USB_ARBPRKEN_M  (USB_ARBPRKEN_V << USB_ARBPRKEN_S)
#define USB_ARBPRKEN_V  0x00000001
#define USB_ARBPRKEN_S  27


/** USB_DIEPCTL0_REG寄存器设备控制IN终结点$n控制寄存器
 */
#define USB_DIEPCTL0_REG (SOC_DPORT_USB_BASE + 0x900)
/** USB_D_MPS0:R/W；位位置：[2:0]；默认值：0；最大数据包大小0x0:64字节0x1:32字节0x2:16字节0x3:8字节
 */
#define USB_D_MPS0    0x00000003
#define USB_D_MPS0_M  (USB_D_MPS0_V << USB_D_MPS0_S)
#define USB_D_MPS0_V  0x00000003
#define USB_D_MPS0_S  0
/** USB_D_USBACTEP0:RO；位位置：[15]；默认值：1；USB活动端点0x1：控制端点始终处于活动状态
 */
#define USB_D_USBACTEP0    (BIT(15))
#define USB_D_USBACTEP0_M  (USB_D_USBACTEP0_V << USB_D_USBACTEP0_S)
#define USB_D_USBACTEP0_V  0x00000001
#define USB_D_USBACTEP0_S  15
/** USB_D_nakst:RO；位位置：[17]；默认值：0；NAK状态0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_D_NAKSTS0    (BIT(17))
#define USB_D_NAKSTS0_M  (USB_D_NAKSTS0_V << USB_D_NAKSTS0_S)
#define USB_D_NAKSTS0_V  0x00000001
#define USB_D_NAKSTS0_S  17
/** USB_D_EPTYPE0:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制0
 */
#define USB_D_EPTYPE0    0x00000003
#define USB_D_EPTYPE0_M  (USB_D_EPTYPE0_V << USB_D_EPTYPE0_S)
#define USB_D_EPTYPE0_V  0x00000003
#define USB_D_EPTYPE0_S  18
/** USB_D_STALL0:R/W；位位置：[21]；默认值：0；应用程序只能设置此位，内核将其清除0x0：无暂停0x1：暂停握手
 */
#define USB_D_STALL0    (BIT(21))
#define USB_D_STALL0_M  (USB_D_STALL0_V << USB_D_STALL0_S)
#define USB_D_STALL0_V  0x00000001
#define USB_D_STALL0_S  21
/** USB_D_TXFNUM0:R/W；比特位置：[26:22]；默认值：0；TxFIFO编号。
 */
#define USB_D_TXFNUM0    0x0000000F
#define USB_D_TXFNUM0_M  (USB_D_TXFNUM0_V << USB_D_TXFNUM0_S)
#define USB_D_TXFNUM0_V  0x0000000F
#define USB_D_TXFNUM0_S  22
/** USB_D_CNAK0:WO；位位置：[26]；默认值：0；写入此位将清除端点的NAK位0x0:无操作0x1:清除NAK
 */
#define USB_D_CNAK0    (BIT(26))
#define USB_D_CNAK0_M  (USB_D_CNAK0_V << USB_D_CNAK0_S)
#define USB_D_CNAK0_V  0x00000001
#define USB_D_CNAK0_S  26
/** USB_DI_SNAK0:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DI_SNAK0    (BIT(27))
#define USB_DI_SNAK0_M  (USB_DI_SNAK0_V << USB_DI_SNAK0_S)
#define USB_DI_SNAK0_V  0x00000001
#define USB_DI_SNAK0_S  27
/** USB_D_EPDIS0:R/W；位位置：[30]；默认值：0；终结点禁用0x0：无操作0x1：已禁用终结点
 */
#define USB_D_EPDIS0    (BIT(30))
#define USB_D_EPDIS0_M  (USB_D_EPDIS0_V << USB_D_EPDIS0_S)
#define USB_D_EPDIS0_V  0x00000001
#define USB_D_EPDIS0_S  30
/** USB_D_EPENA0:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_D_EPENA0    (BIT(31))
#define USB_D_EPENA0_M  (USB_D_EPENA0_V << USB_D_EPENA0_S)
#define USB_D_EPENA0_V  0x00000001
#define USB_D_EPENA0_S  31


/** USB_DIEPTSIZ0_REG寄存器设备IN终结点0传输大小寄存器
 */
#define USB_DIEPTSIZ0_REG (SOC_DPORT_USB_BASE + 0x910)
/** USB_D_XFERSIZE0:R/W；位位置：[7:0]；默认值：0；传输大小IN端点：每次将来自外部存储器的数据包写入TxFIFO OUT端点时，核心会减小此字段：每次从RxFIFO读取数据包并将其写入外部存储器时，核心都会减小此区域
 */
#define USB_D_XFERSIZE0    0x0000007F
#define USB_D_XFERSIZE0_M  (USB_D_XFERSIZE0_V << USB_D_XFERSIZE0_S)
#define USB_D_XFERSIZE0_V  0x0000007F
#define USB_D_XFERSIZE0_S  0
/** USB_D_PKTCNT0:R/W；比特位置：[21:19]；默认值：0；数据包计数IN端点：每次从TxFIFO OUT端点读取数据包（最大大小或短数据包）时，此字段都会减小：每次将数据包（最小大小或短）写入RxFIFO时，此区域都会减小
 */
#define USB_D_PKTCNT0    0x00000003
#define USB_D_PKTCNT0_M  (USB_D_PKTCNT0_V << USB_D_PKTCNT0_S)
#define USB_D_PKTCNT0_V  0x00000003
#define USB_D_PKTCNT0_S  19


/** USB_DIEPDMA0_REG寄存器设备IN终结点0 DMA地址寄存器
 */
#define USB_DIEPDMA0_REG (SOC_DPORT_USB_BASE + 0x914)
/** USB_D_dmaddr0:R/W；位位置：[32:0]；默认值：0；此字段保存用于存储或获取端点数据的外部存储器的起始地址。
 */
#define USB_D_DMAADDR0    0xFFFFFFFF
#define USB_D_DMAADDR0_M  (USB_D_DMAADDR0_V << USB_D_DMAADDR0_S)
#define USB_D_DMAADDR0_V  0xFFFFFFFF
#define USB_D_DMAADDR0_S  0


/** USB_DIEPCTL1_REG寄存器设备控制IN终结点$n控制寄存器
 */
#define USB_DIEPCTL1_REG (SOC_DPORT_USB_BASE + 0x920)
/** USB_D_MPS1:R/W；位位置：[2:0]；默认值：0；最大数据包大小0x0:64字节0x1:32字节0x2:16字节0x3:8字节
 */
#define USB_D_MPS1    0x00000003
#define USB_D_MPS1_M  (USB_D_MPS1_V << USB_D_MPS1_S)
#define USB_D_MPS1_V  0x00000003
#define USB_D_MPS1_S  0
/** USB_D_USBACTEP1:RO；位位置：[15]；默认值：1；USB活动端点0x1：控制端点始终处于活动状态
 */
#define USB_D_USBACTEP1    (BIT(15))
#define USB_D_USBACTEP1_M  (USB_D_USBACTEP1_V << USB_D_USBACTEP1_S)
#define USB_D_USBACTEP1_V  0x00000001
#define USB_D_USBACTEP1_S  15
/** USB_D_NAKSTS1:RO；位位置：[17]；默认值：0；NAK状态0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_D_NAKSTS1    (BIT(17))
#define USB_D_NAKSTS1_M  (USB_D_NAKSTS1_V << USB_D_NAKSTS1_S)
#define USB_D_NAKSTS1_V  0x00000001
#define USB_D_NAKSTS1_S  17
/** USB_D_EPTYPE1:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制0
 */
#define USB_D_EPTYPE1    0x00000003
#define USB_D_EPTYPE1_M  (USB_D_EPTYPE1_V << USB_D_EPTYPE1_S)
#define USB_D_EPTYPE1_V  0x00000003
#define USB_D_EPTYPE1_S  18
/** USB_D_STALL1:R/W；位位置：[21]；默认值：0；应用程序只能设置此位，内核将其清除0x0：无暂停0x1：暂停握手
 */
#define USB_D_STALL1    (BIT(21))
#define USB_D_STALL1_M  (USB_D_STALL1_V << USB_D_STALL1_S)
#define USB_D_STALL1_V  0x00000001
#define USB_D_STALL1_S  21
/** USB_D_TXFNUM1:R/W；比特位置：[26:22]；默认值：0；TxFIFO编号。
 */
#define USB_D_TXFNUM1    0x0000000F
#define USB_D_TXFNUM1_M  (USB_D_TXFNUM1_V << USB_D_TXFNUM1_S)
#define USB_D_TXFNUM1_V  0x0000000F
#define USB_D_TXFNUM1_S  22
/** USB_D_CNAK1:WO；位位置：[26]；默认值：0；写入此位将清除端点的NAK位0x0:无操作0x1:清除NAK
 */
#define USB_D_CNAK1    (BIT(26))
#define USB_D_CNAK1_M  (USB_D_CNAK1_V << USB_D_CNAK1_S)
#define USB_D_CNAK1_V  0x00000001
#define USB_D_CNAK1_S  26
/** USB_DI_SNAK1:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DI_SNAK1    (BIT(27))
#define USB_DI_SNAK1_M  (USB_DI_SNAK1_V << USB_DI_SNAK1_S)
#define USB_DI_SNAK1_V  0x00000001
#define USB_DI_SNAK1_S  27
/** USB_DI_SETD0PID1:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DI_SETD0PID1    (BIT(28))
#define USB_DI_SETD0PID1_M  (USB_DI_SETD0PID1_V << USB_DI_SETD0PID1_S)
#define USB_DI_SETD0PID1_V  0x00000001
#define USB_DI_SETD0PID1_S  28
/** USB_DI_SETD1PID1:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DI_SETD1PID1    (BIT(29))
#define USB_DI_SETD1PID1_M  (USB_DI_SETD1PID1_V << USB_DI_SETD1PID1_S)
#define USB_DI_SETD1PID1_V  0x00000001
#define USB_DI_SETD1PID1_S  29
/** USB_D_EPDIS1:R/W；位位置：[30]；默认值：0；终结点禁用0x0：无操作0x1：已禁用终结点
 */
#define USB_D_EPDIS1    (BIT(30))
#define USB_D_EPDIS1_M  (USB_D_EPDIS1_V << USB_D_EPDIS1_S)
#define USB_D_EPDIS1_V  0x00000001
#define USB_D_EPDIS1_S  30
/** USB_D_EPENA1:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_D_EPENA1    (BIT(31))
#define USB_D_EPENA1_M  (USB_D_EPENA1_V << USB_D_EPENA1_S)
#define USB_D_EPENA1_V  0x00000001
#define USB_D_EPENA1_S  31


/** USB_DIEPTSIZ1_REG寄存器设备IN端点1传输大小寄存器
 */
#define USB_DIEPTSIZ1_REG (SOC_DPORT_USB_BASE + 0x930)
/** USB_D_XFERSIZE1:R/W；位位置：[7:0]；默认值：0；传输大小IN端点：每次将来自外部存储器的数据包写入TxFIFO OUT端点时，核心会减小此字段：每次从RxFIFO读取数据包并将其写入外部存储器时，核心都会减小此区域
 */
#define USB_D_XFERSIZE1    0x0000007F
#define USB_D_XFERSIZE1_M  (USB_D_XFERSIZE1_V << USB_D_XFERSIZE1_S)
#define USB_D_XFERSIZE1_V  0x0000007F
#define USB_D_XFERSIZE1_S  0
/** USB_D_PKTCNT1:R/W；比特位置：[21:19]；默认值：0；数据包计数IN端点：每次从TxFIFO OUT端点读取数据包（最大大小或短数据包）时，此字段都会减小：每次将数据包（最小大小或短）写入RxFIFO时，此区域都会减小
 */
#define USB_D_PKTCNT1    0x00000003
#define USB_D_PKTCNT1_M  (USB_D_PKTCNT1_V << USB_D_PKTCNT1_S)
#define USB_D_PKTCNT1_V  0x00000003
#define USB_D_PKTCNT1_S  19


/** USB_DIEPDMA1_REG寄存器设备IN端点1 DMA地址寄存器
 */
#define USB_DIEPDMA1_REG (SOC_DPORT_USB_BASE + 0x934)
/** USB_D_DMAADDR1:R/W；位位置：[32:0]；默认值：0；此字段保存用于存储或获取端点数据的外部存储器的起始地址。
 */
#define USB_D_DMAADDR1    0xFFFFFFFF
#define USB_D_DMAADDR1_M  (USB_D_DMAADDR1_V << USB_D_DMAADDR1_S)
#define USB_D_DMAADDR1_V  0xFFFFFFFF
#define USB_D_DMAADDR1_S  0


/** USB_DIEPCTL2_REG寄存器设备控制IN端点2控制寄存器
 */
#define USB_DIEPCTL2_REG (SOC_DPORT_USB_BASE + 0x940)
/** USB_D_MPS2:R/W；位位置：[2:0]；默认值：0；最大数据包大小0x0:64字节0x1:32字节0x2:16字节0x3:8字节
 */
#define USB_D_MPS2    0x00000003
#define USB_D_MPS2_M  (USB_D_MPS2_V << USB_D_MPS2_S)
#define USB_D_MPS2_V  0x00000003
#define USB_D_MPS2_S  0
/** USB_D_USBACTEP2:RO；位位置：[15]；默认值：1；USB活动端点0x1：控制端点始终处于活动状态
 */
#define USB_D_USBACTEP2    (BIT(15))
#define USB_D_USBACTEP2_M  (USB_D_USBACTEP2_V << USB_D_USBACTEP2_S)
#define USB_D_USBACTEP2_V  0x00000001
#define USB_D_USBACTEP2_S  15
/** USB_D_NAKSTS2:RO；位位置：[17]；默认值：0；NAK状态0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_D_NAKSTS2    (BIT(17))
#define USB_D_NAKSTS2_M  (USB_D_NAKSTS2_V << USB_D_NAKSTS2_S)
#define USB_D_NAKSTS2_V  0x00000001
#define USB_D_NAKSTS2_S  17
/** USB_D_EPTYPE2:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制0
 */
#define USB_D_EPTYPE2    0x00000003
#define USB_D_EPTYPE2_M  (USB_D_EPTYPE2_V << USB_D_EPTYPE2_S)
#define USB_D_EPTYPE2_V  0x00000003
#define USB_D_EPTYPE2_S  18
/** USB_D_STALL2:R/W；位位置：[21]；默认值：0；应用程序只能设置此位，内核将其清除0x0：无暂停0x1：暂停握手
 */
#define USB_D_STALL2    (BIT(21))
#define USB_D_STALL2_M  (USB_D_STALL2_V << USB_D_STALL2_S)
#define USB_D_STALL2_V  0x00000001
#define USB_D_STALL2_S  21
/** USB_D_TXFNUM2:R/W；比特位置：[26:22]；默认值：0；TxFIFO编号。
 */
#define USB_D_TXFNUM2    0x0000000F
#define USB_D_TXFNUM2_M  (USB_D_TXFNUM2_V << USB_D_TXFNUM2_S)
#define USB_D_TXFNUM2_V  0x0000000F
#define USB_D_TXFNUM2_S  22
/** USB_D_CNAK2:WO；位位置：[26]；默认值：0；写入此位将清除端点的NAK位0x0:无操作0x1:清除NAK
 */
#define USB_D_CNAK2    (BIT(26))
#define USB_D_CNAK2_M  (USB_D_CNAK2_V << USB_D_CNAK2_S)
#define USB_D_CNAK2_V  0x00000001
#define USB_D_CNAK2_S  26
/** USB_DI_SNAK2:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DI_SNAK2    (BIT(27))
#define USB_DI_SNAK2_M  (USB_DI_SNAK2_V << USB_DI_SNAK2_S)
#define USB_DI_SNAK2_V  0x00000001
#define USB_DI_SNAK2_S  27
/** USB_DI_SETD0PID2:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DI_SETD0PID2    (BIT(28))
#define USB_DI_SETD0PID2_M  (USB_DI_SETD0PID2_V << USB_DI_SETD0PID2_S)
#define USB_DI_SETD0PID2_V  0x00000001
#define USB_DI_SETD0PID2_S  28
/** USB_DI_SETD1PID2:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DI_SETD1PID2    (BIT(29))
#define USB_DI_SETD1PID2_M  (USB_DI_SETD1PID2_V << USB_DI_SETD1PID2_S)
#define USB_DI_SETD1PID2_V  0x00000001
#define USB_DI_SETD1PID2_S  29
/** USB_D_EPDIS2:R/W；位位置：[30]；默认值：0；终结点禁用0x0：无操作0x1：已禁用终结点
 */
#define USB_D_EPDIS2    (BIT(30))
#define USB_D_EPDIS2_M  (USB_D_EPDIS2_V << USB_D_EPDIS2_S)
#define USB_D_EPDIS2_V  0x00000001
#define USB_D_EPDIS2_S  30
/** USB_D_EPENA2:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_D_EPENA2    (BIT(31))
#define USB_D_EPENA2_M  (USB_D_EPENA2_V << USB_D_EPENA2_S)
#define USB_D_EPENA2_V  0x00000001
#define USB_D_EPENA2_S  31


/** USB_DIEPTSIZ2_REG寄存器设备IN端点2传输大小寄存器
 */
#define USB_DIEPTSIZ2_REG (SOC_DPORT_USB_BASE + 0x950)
/** USB_D_XFERSIZE2:R/W；位位置：[7:0]；默认值：0；传输大小IN端点：每次将来自外部存储器的数据包写入TxFIFO OUT端点时，核心会减小此字段：每次从RxFIFO读取数据包并将其写入外部存储器时，核心都会减小此区域
 */
#define USB_D_XFERSIZE2    0x0000007F
#define USB_D_XFERSIZE2_M  (USB_D_XFERSIZE2_V << USB_D_XFERSIZE2_S)
#define USB_D_XFERSIZE2_V  0x0000007F
#define USB_D_XFERSIZE2_S  0
/** USB_D_PKTCNT2:R/W；比特位置：[21:19]；默认值：0；数据包计数IN端点：每次从TxFIFO OUT端点读取数据包（最大大小或短数据包）时，此字段都会减小：每次将数据包（最小大小或短）写入RxFIFO时，此区域都会减小
 */
#define USB_D_PKTCNT2    0x00000003
#define USB_D_PKTCNT2_M  (USB_D_PKTCNT2_V << USB_D_PKTCNT2_S)
#define USB_D_PKTCNT2_V  0x00000003
#define USB_D_PKTCNT2_S  19


/** USB_DIEPDMA2_REG寄存器设备IN端点2 DMA地址寄存器
 */
#define USB_DIEPDMA2_REG (SOC_DPORT_USB_BASE + 0x954)
/** USB_D_DMAADDR2:R/W；位位置：[32:0]；默认值：0；此字段保存用于存储或获取端点数据的外部存储器的起始地址。
 */
#define USB_D_DMAADDR2    0xFFFFFFFF
#define USB_D_DMAADDR2_M  (USB_D_DMAADDR2_V << USB_D_DMAADDR2_S)
#define USB_D_DMAADDR2_V  0xFFFFFFFF
#define USB_D_DMAADDR2_S  0


/** USB_DIEPCTL3_REG寄存器设备控制IN终结点$n控制寄存器
 */
#define USB_DIEPCTL3_REG (SOC_DPORT_USB_BASE + 0x960)
/** USB_DI_MPS3:R/W；位位置：[2:0]；默认值：0；最大数据包大小0x0:64字节0x1:32字节0x2:16字节0x3:8字节
 */
#define USB_DI_MPS3    0x00000003
#define USB_DI_MPS3_M  (USB_DI_MPS3_V << USB_DI_MPS3_S)
#define USB_DI_MPS3_V  0x00000003
#define USB_DI_MPS3_S  0
/** USB_DI_USBACTEP3:RO；位位置：[15]；默认值：1；USB活动端点0x1：控制端点始终处于活动状态
 */
#define USB_DI_USBACTEP3    (BIT(15))
#define USB_DI_USBACTEP3_M  (USB_DI_USBACTEP3_V << USB_DI_USBACTEP3_S)
#define USB_DI_USBACTEP3_V  0x00000001
#define USB_DI_USBACTEP3_S  15
/** USB_DI_nakts3:RO；位位置：[17]；默认值：0；NAK状态0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_DI_NAKSTS3    (BIT(17))
#define USB_DI_NAKSTS3_M  (USB_DI_NAKSTS3_V << USB_DI_NAKSTS3_S)
#define USB_DI_NAKSTS3_V  0x00000001
#define USB_DI_NAKSTS3_S  17
/** USB_DI_EPTYPE3:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制0
 */
#define USB_DI_EPTYPE3    0x00000003
#define USB_DI_EPTYPE3_M  (USB_DI_EPTYPE3_V << USB_DI_EPTYPE3_S)
#define USB_DI_EPTYPE3_V  0x00000003
#define USB_DI_EPTYPE3_S  18
/** USB_DI_STALL3:R/W；位位置：[21]；默认值：0；应用程序只能设置此位，内核将其清除0x0：无暂停0x1：暂停握手
 */
#define USB_DI_STALL3    (BIT(21))
#define USB_DI_STALL3_M  (USB_DI_STALL3_V << USB_DI_STALL3_S)
#define USB_DI_STALL3_V  0x00000001
#define USB_DI_STALL3_S  21
/** USB_DI_TXFNUM3:R/W；比特位置：[26:22]；默认值：0；TxFIFO编号。
 */
#define USB_DI_TXFNUM3    0x0000000F
#define USB_DI_TXFNUM3_M  (USB_DI_TXFNUM3_V << USB_DI_TXFNUM3_S)
#define USB_DI_TXFNUM3_V  0x0000000F
#define USB_DI_TXFNUM3_S  22
/** USB_DI_CNAK3:WO；位位置：[26]；默认值：0；写入此位将清除端点的NAK位0x0:无操作0x1:清除NAK
 */
#define USB_DI_CNAK3    (BIT(26))
#define USB_DI_CNAK3_M  (USB_DI_CNAK3_V << USB_DI_CNAK3_S)
#define USB_DI_CNAK3_V  0x00000001
#define USB_DI_CNAK3_S  26
/** USB_DI_SNAK3:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DI_SNAK3    (BIT(27))
#define USB_DI_SNAK3_M  (USB_DI_SNAK3_V << USB_DI_SNAK3_S)
#define USB_DI_SNAK3_V  0x00000001
#define USB_DI_SNAK3_S  27
/** USB_DI_SETD0PID3:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DI_SETD0PID3    (BIT(28))
#define USB_DI_SETD0PID3_M  (USB_DI_SETD0PID3_V << USB_DI_SETD0PID3_S)
#define USB_DI_SETD0PID3_V  0x00000001
#define USB_DI_SETD0PID3_S  28
/** USB_DI_SETD1PID3:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DI_SETD1PID3    (BIT(29))
#define USB_DI_SETD1PID3_M  (USB_DI_SETD1PID3_V << USB_DI_SETD1PID3_S)
#define USB_DI_SETD1PID3_V  0x00000001
#define USB_DI_SETD1PID3_S  29
/** USB_DI_EPDIS3:R/W；位位置：[30]；默认值：0；终结点禁用0x0：无操作0x1：已禁用终结点
 */
#define USB_DI_EPDIS3    (BIT(30))
#define USB_DI_EPDIS3_M  (USB_DI_EPDIS3_V << USB_DI_EPDIS3_S)
#define USB_DI_EPDIS3_V  0x00000001
#define USB_DI_EPDIS3_S  30
/** USB_DI_EPENA3:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_DI_EPENA3    (BIT(31))
#define USB_DI_EPENA3_M  (USB_DI_EPENA3_V << USB_DI_EPENA3_S)
#define USB_DI_EPENA3_V  0x00000001
#define USB_DI_EPENA3_S  31


/** USB_DIEPTSIZ3_REG寄存器设备IN终结点3传输大小寄存器
 */
#define USB_DIEPTSIZ3_REG (SOC_DPORT_USB_BASE + 0x970)
/** USB_D_XFERSIZE3:R/W；位位置：[7:0]；默认值：0；传输大小IN端点：每次将来自外部存储器的数据包写入TxFIFO OUT端点时，核心会减小此字段：每次从RxFIFO读取数据包并将其写入外部存储器时，核心都会减小此区域
 */
#define USB_D_XFERSIZE3    0x0000007F
#define USB_D_XFERSIZE3_M  (USB_D_XFERSIZE3_V << USB_D_XFERSIZE3_S)
#define USB_D_XFERSIZE3_V  0x0000007F
#define USB_D_XFERSIZE3_S  0
/** USB_D_PKTCNT3:R/W；比特位置：[21:19]；默认值：0；数据包计数IN端点：每次从TxFIFO OUT端点读取数据包（最大大小或短数据包）时，此字段都会减小：每次将数据包（最小大小或短）写入RxFIFO时，此区域都会减小
 */
#define USB_D_PKTCNT3    0x00000003
#define USB_D_PKTCNT3_M  (USB_D_PKTCNT3_V << USB_D_PKTCNT3_S)
#define USB_D_PKTCNT3_V  0x00000003
#define USB_D_PKTCNT3_S  19


/** USB_DIEPDMA3_REG寄存器设备IN终结点3 DMA地址寄存器
 */
#define USB_DIEPDMA3_REG (SOC_DPORT_USB_BASE + 0x974)
/** USB_D_DMAADDR3:R/W；位位置：[32:0]；默认值：0；此字段保存用于存储或获取端点数据的外部存储器的起始地址。
 */
#define USB_D_DMAADDR3    0xFFFFFFFF
#define USB_D_DMAADDR3_M  (USB_D_DMAADDR3_V << USB_D_DMAADDR3_S)
#define USB_D_DMAADDR3_V  0xFFFFFFFF
#define USB_D_DMAADDR3_S  0


/** USB_DIEPCTL4_REG寄存器设备控制IN终结点$n控制寄存器
 */
#define USB_DIEPCTL4_REG (SOC_DPORT_USB_BASE + 0x980)
/** USB_D_MPS4:R/W；位位置：[2:0]；默认值：0；最大数据包大小0x0:64字节0x1:32字节0x2:16字节0x3:8字节
 */
#define USB_D_MPS4    0x00000003
#define USB_D_MPS4_M  (USB_D_MPS4_V << USB_D_MPS4_S)
#define USB_D_MPS4_V  0x00000003
#define USB_D_MPS4_S  0
/** USB_D_USBACTEP4:RO；位位置：[15]；默认值：1；USB活动端点0x1：控制端点始终处于活动状态
 */
#define USB_D_USBACTEP4    (BIT(15))
#define USB_D_USBACTEP4_M  (USB_D_USBACTEP4_V << USB_D_USBACTEP4_S)
#define USB_D_USBACTEP4_V  0x00000001
#define USB_D_USBACTEP4_S  15
/** USB_D_nakss4:RO；位位置：[17]；默认值：0；NAK状态0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_D_NAKSTS4    (BIT(17))
#define USB_D_NAKSTS4_M  (USB_D_NAKSTS4_V << USB_D_NAKSTS4_S)
#define USB_D_NAKSTS4_V  0x00000001
#define USB_D_NAKSTS4_S  17
/** USB_D_EPTYPE4:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制0
 */
#define USB_D_EPTYPE4    0x00000003
#define USB_D_EPTYPE4_M  (USB_D_EPTYPE4_V << USB_D_EPTYPE4_S)
#define USB_D_EPTYPE4_V  0x00000003
#define USB_D_EPTYPE4_S  18
/** USB_D_STALL4:R/W；位位置：[21]；默认值：0；应用程序只能设置此位，内核将其清除0x0：无暂停0x1：暂停握手
 */
#define USB_D_STALL4    (BIT(21))
#define USB_D_STALL4_M  (USB_D_STALL4_V << USB_D_STALL4_S)
#define USB_D_STALL4_V  0x00000001
#define USB_D_STALL4_S  21
/** USB_D_TXFNUM4:R/W；比特位置：[26:22]；默认值：0；TxFIFO编号。
 */
#define USB_D_TXFNUM4    0x0000000F
#define USB_D_TXFNUM4_M  (USB_D_TXFNUM4_V << USB_D_TXFNUM4_S)
#define USB_D_TXFNUM4_V  0x0000000F
#define USB_D_TXFNUM4_S  22
/** USB_D_CNAK4:WO；位位置：[26]；默认值：0；写入此位将清除端点的NAK位0x0:无操作0x1:清除NAK
 */
#define USB_D_CNAK4    (BIT(26))
#define USB_D_CNAK4_M  (USB_D_CNAK4_V << USB_D_CNAK4_S)
#define USB_D_CNAK4_V  0x00000001
#define USB_D_CNAK4_S  26
/** USB_DI_SNAK4:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DI_SNAK4    (BIT(27))
#define USB_DI_SNAK4_M  (USB_DI_SNAK4_V << USB_DI_SNAK4_S)
#define USB_DI_SNAK4_V  0x00000001
#define USB_DI_SNAK4_S  27
/** USB_DI_SETD0PID4:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DI_SETD0PID4    (BIT(28))
#define USB_DI_SETD0PID4_M  (USB_DI_SETD0PID4_V << USB_DI_SETD0PID4_S)
#define USB_DI_SETD0PID4_V  0x00000001
#define USB_DI_SETD0PID4_S  28
/** USB_DI_SETD1PID4:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DI_SETD1PID4    (BIT(29))
#define USB_DI_SETD1PID4_M  (USB_DI_SETD1PID4_V << USB_DI_SETD1PID4_S)
#define USB_DI_SETD1PID4_V  0x00000001
#define USB_DI_SETD1PID4_S  29
/** USB_D_EPDIS4:R/W；位位置：[30]；默认值：0；终结点禁用0x0：无操作0x1：已禁用终结点
 */
#define USB_D_EPDIS4    (BIT(30))
#define USB_D_EPDIS4_M  (USB_D_EPDIS4_V << USB_D_EPDIS4_S)
#define USB_D_EPDIS4_V  0x00000001
#define USB_D_EPDIS4_S  30
/** USB_D_EPENA4:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_D_EPENA4    (BIT(31))
#define USB_D_EPENA4_M  (USB_D_EPENA4_V << USB_D_EPENA4_S)
#define USB_D_EPENA4_V  0x00000001
#define USB_D_EPENA4_S  31


/** USB_DIEPTSIZ4_REG寄存器设备IN端点4传输大小寄存器
 */
#define USB_DIEPTSIZ4_REG (SOC_DPORT_USB_BASE + 0x990)
/** USB_D_XFERSIZE4:R/W；位位置：[7:0]；默认值：0；传输大小IN端点：每次将来自外部存储器的数据包写入TxFIFO OUT端点时，核心会减小此字段：每次从RxFIFO读取数据包并将其写入外部存储器时，核心都会减小此区域
 */
#define USB_D_XFERSIZE4    0x0000007F
#define USB_D_XFERSIZE4_M  (USB_D_XFERSIZE4_V << USB_D_XFERSIZE4_S)
#define USB_D_XFERSIZE4_V  0x0000007F
#define USB_D_XFERSIZE4_S  0
/** USB_D_PKTCNT4:R/W；比特位置：[21:19]；默认值：0；数据包计数IN端点：每次从TxFIFO OUT端点读取数据包（最大大小或短数据包）时，此字段都会减小：每次将数据包（最小大小或短）写入RxFIFO时，此区域都会减小
 */
#define USB_D_PKTCNT4    0x00000003
#define USB_D_PKTCNT4_M  (USB_D_PKTCNT4_V << USB_D_PKTCNT4_S)
#define USB_D_PKTCNT4_V  0x00000003
#define USB_D_PKTCNT4_S  19


/** USB_DIEPDMA4_REG寄存器设备IN端点4 DMA地址寄存器
 */
#define USB_DIEPDMA4_REG (SOC_DPORT_USB_BASE + 0x994)
/** USB_D_dmaddr4:R/W；位位置：[32:0]；默认值：0；此字段保存用于存储或获取端点数据的外部存储器的起始地址。
 */
#define USB_D_DMAADDR4    0xFFFFFFFF
#define USB_D_DMAADDR4_M  (USB_D_DMAADDR4_V << USB_D_DMAADDR4_S)
#define USB_D_DMAADDR4_V  0xFFFFFFFF
#define USB_D_DMAADDR4_S  0


/** USB_DIEPCTL5_REG寄存器设备控制IN终结点$n控制寄存器
 */
#define USB_DIEPCTL5_REG (SOC_DPORT_USB_BASE + 0x9a0)
/** USB_DI_MPS5:R/W；位位置：[2:0]；默认值：0；最大数据包大小0x0:64字节0x1:32字节0x2:16字节0x3:8字节
 */
#define USB_DI_MPS5    0x00000003
#define USB_DI_MPS5_M  (USB_DI_MPS5_V << USB_DI_MPS5_S)
#define USB_DI_MPS5_V  0x00000003
#define USB_DI_MPS5_S  0
/** USB_DI_usbactp5:RO；位位置：[15]；默认值：1；USB活动端点0x1：控制端点始终处于活动状态
 */
#define USB_DI_USBACTEP5    (BIT(15))
#define USB_DI_USBACTEP5_M  (USB_DI_USBACTEP5_V << USB_DI_USBACTEP5_S)
#define USB_DI_USBACTEP5_V  0x00000001
#define USB_DI_USBACTEP5_S  15
/** USB_DI_nakts5:RO；位位置：[17]；默认值：0；NAK状态0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_DI_NAKSTS5    (BIT(17))
#define USB_DI_NAKSTS5_M  (USB_DI_NAKSTS5_V << USB_DI_NAKSTS5_S)
#define USB_DI_NAKSTS5_V  0x00000001
#define USB_DI_NAKSTS5_S  17
/** USB_DI_EPTYPE5:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制0
 */
#define USB_DI_EPTYPE5    0x00000003
#define USB_DI_EPTYPE5_M  (USB_DI_EPTYPE5_V << USB_DI_EPTYPE5_S)
#define USB_DI_EPTYPE5_V  0x00000003
#define USB_DI_EPTYPE5_S  18
/** USB_DI_STALL5:R/W；位位置：[21]；默认值：0；应用程序只能设置此位，内核将其清除0x0：无暂停0x1：暂停握手
 */
#define USB_DI_STALL5    (BIT(21))
#define USB_DI_STALL5_M  (USB_DI_STALL5_V << USB_DI_STALL5_S)
#define USB_DI_STALL5_V  0x00000001
#define USB_DI_STALL5_S  21
/** USB_DI_TXFNUM5:R/W；比特位置：[26:22]；默认值：0；TxFIFO编号。
 */
#define USB_DI_TXFNUM5    0x0000000F
#define USB_DI_TXFNUM5_M  (USB_DI_TXFNUM5_V << USB_DI_TXFNUM5_S)
#define USB_DI_TXFNUM5_V  0x0000000F
#define USB_DI_TXFNUM5_S  22
/** USB_DI_CNAK5:WO；位位置：[26]；默认值：0；写入此位将清除端点的NAK位0x0:无操作0x1:清除NAK
 */
#define USB_DI_CNAK5    (BIT(26))
#define USB_DI_CNAK5_M  (USB_DI_CNAK5_V << USB_DI_CNAK5_S)
#define USB_DI_CNAK5_V  0x00000001
#define USB_DI_CNAK5_S  26
/** USB_DI_SNAK5:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DI_SNAK5    (BIT(27))
#define USB_DI_SNAK5_M  (USB_DI_SNAK5_V << USB_DI_SNAK5_S)
#define USB_DI_SNAK5_V  0x00000001
#define USB_DI_SNAK5_S  27
/** USB_DI_SETD0PID5:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DI_SETD0PID5    (BIT(28))
#define USB_DI_SETD0PID5_M  (USB_DI_SETD0PID5_V << USB_DI_SETD0PID5_S)
#define USB_DI_SETD0PID5_V  0x00000001
#define USB_DI_SETD0PID5_S  28
/** USB_DI_SETD1PID5:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DI_SETD1PID5    (BIT(29))
#define USB_DI_SETD1PID5_M  (USB_DI_SETD1PID5_V << USB_DI_SETD1PID5_S)
#define USB_DI_SETD1PID5_V  0x00000001
#define USB_DI_SETD1PID5_S  29
/** USB_DI_EPDIS5:R/W；位位置：[30]；默认值：0；终结点禁用0x0：无操作0x1：已禁用终结点
 */
#define USB_DI_EPDIS5    (BIT(30))
#define USB_DI_EPDIS5_M  (USB_DI_EPDIS5_V << USB_DI_EPDIS5_S)
#define USB_DI_EPDIS5_V  0x00000001
#define USB_DI_EPDIS5_S  30
/** USB_DI_EPENA5:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_DI_EPENA5    (BIT(31))
#define USB_DI_EPENA5_M  (USB_DI_EPENA5_V << USB_DI_EPENA5_S)
#define USB_DI_EPENA5_V  0x00000001
#define USB_DI_EPENA5_S  31


/** USB_DIEPTSIZ5_REG寄存器设备IN端点5传输大小寄存器
 */
#define USB_DIEPTSIZ5_REG (SOC_DPORT_USB_BASE + 0x9b0)
/** USB_D_XFERSIZE5:R/W；位位置：[7:0]；默认值：0；传输大小IN端点：每次将来自外部存储器的数据包写入TxFIFO OUT端点时，核心会减小此字段：每次从RxFIFO读取数据包并将其写入外部存储器时，核心都会减小此区域
 */
#define USB_D_XFERSIZE5    0x0000007F
#define USB_D_XFERSIZE5_M  (USB_D_XFERSIZE5_V << USB_D_XFERSIZE5_S)
#define USB_D_XFERSIZE5_V  0x0000007F
#define USB_D_XFERSIZE5_S  0
/** USB_D_PKTCNT5:R/W；比特位置：[21:19]；默认值：0；数据包计数IN端点：每次从TxFIFO OUT端点读取数据包（最大大小或短数据包）时，此字段都会减小：每次将数据包（最小大小或短）写入RxFIFO时，此区域都会减小
 */
#define USB_D_PKTCNT5    0x00000003
#define USB_D_PKTCNT5_M  (USB_D_PKTCNT5_V << USB_D_PKTCNT5_S)
#define USB_D_PKTCNT5_V  0x00000003
#define USB_D_PKTCNT5_S  19


/** USB_DIEPDMA5_REG寄存器设备IN端点5 DMA地址寄存器
 */
#define USB_DIEPDMA5_REG (SOC_DPORT_USB_BASE + 0x9b4)
/** USB_D_dmaddr5:R/W；位位置：[32:0]；默认值：0；此字段保存用于存储或获取端点数据的外部存储器的起始地址。
 */
#define USB_D_DMAADDR5    0xFFFFFFFF
#define USB_D_DMAADDR5_M  (USB_D_DMAADDR5_V << USB_D_DMAADDR5_S)
#define USB_D_DMAADDR5_V  0xFFFFFFFF
#define USB_D_DMAADDR5_S  0


/** USB_DIEPCTL6_REG寄存器设备控制IN端点$n控制寄存器
 */
#define USB_DIEPCTL6_REG (SOC_DPORT_USB_BASE + 0x9c0)
/** USB_D_MPS6:R/W；位位置：[2:0]；默认值：0；最大数据包大小0x0:64字节0x1:32字节0x2:16字节0x3:8字节
 */
#define USB_D_MPS6    0x00000003
#define USB_D_MPS6_M  (USB_D_MPS6_V << USB_D_MPS6_S)
#define USB_D_MPS6_V  0x00000003
#define USB_D_MPS6_S  0
/** USB_D_USBACTEP6:RO；位位置：[15]；默认值：1；USB活动端点0x1：控制端点始终处于活动状态
 */
#define USB_D_USBACTEP6    (BIT(15))
#define USB_D_USBACTEP6_M  (USB_D_USBACTEP6_V << USB_D_USBACTEP6_S)
#define USB_D_USBACTEP6_V  0x00000001
#define USB_D_USBACTEP6_S  15
/** USB_D_naks6:RO；位位置：[17]；默认值：0；NAK状态0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_D_NAKSTS6    (BIT(17))
#define USB_D_NAKSTS6_M  (USB_D_NAKSTS6_V << USB_D_NAKSTS6_S)
#define USB_D_NAKSTS6_V  0x00000001
#define USB_D_NAKSTS6_S  17
/** USB_D_EPTYPE6:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制0
 */
#define USB_D_EPTYPE6    0x00000003
#define USB_D_EPTYPE6_M  (USB_D_EPTYPE6_V << USB_D_EPTYPE6_S)
#define USB_D_EPTYPE6_V  0x00000003
#define USB_D_EPTYPE6_S  18
/** USB_D_STALL6:R/W；位位置：[21]；默认值：0；应用程序只能设置此位，内核将其清除0x0：无暂停0x1：暂停握手
 */
#define USB_D_STALL6    (BIT(21))
#define USB_D_STALL6_M  (USB_D_STALL6_V << USB_D_STALL6_S)
#define USB_D_STALL6_V  0x00000001
#define USB_D_STALL6_S  21
/** USB_D_TXFNUM6:R/W；比特位置：[26:22]；默认值：0；TxFIFO编号。
 */
#define USB_D_TXFNUM6    0x0000000F
#define USB_D_TXFNUM6_M  (USB_D_TXFNUM6_V << USB_D_TXFNUM6_S)
#define USB_D_TXFNUM6_V  0x0000000F
#define USB_D_TXFNUM6_S  22
/** USB_D_CNAK6:WO；位位置：[26]；默认值：0；写入此位将清除端点的NAK位0x0:无操作0x1:清除NAK
 */
#define USB_D_CNAK6    (BIT(26))
#define USB_D_CNAK6_M  (USB_D_CNAK6_V << USB_D_CNAK6_S)
#define USB_D_CNAK6_V  0x00000001
#define USB_D_CNAK6_S  26
/** USB_DI_SNAK6:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DI_SNAK6    (BIT(27))
#define USB_DI_SNAK6_M  (USB_DI_SNAK6_V << USB_DI_SNAK6_S)
#define USB_DI_SNAK6_V  0x00000001
#define USB_DI_SNAK6_S  27
/** USB_DI_SETD0PID6:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DI_SETD0PID6    (BIT(28))
#define USB_DI_SETD0PID6_M  (USB_DI_SETD0PID6_V << USB_DI_SETD0PID6_S)
#define USB_DI_SETD0PID6_V  0x00000001
#define USB_DI_SETD0PID6_S  28
/** USB_DI_SETD1PID6:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DI_SETD1PID6    (BIT(29))
#define USB_DI_SETD1PID6_M  (USB_DI_SETD1PID6_V << USB_DI_SETD1PID6_S)
#define USB_DI_SETD1PID6_V  0x00000001
#define USB_DI_SETD1PID6_S  29
/** USB_D_EPDIS6:R/W；位位置：[30]；默认值：0；终结点禁用0x0：无操作0x1：已禁用终结点
 */
#define USB_D_EPDIS6    (BIT(30))
#define USB_D_EPDIS6_M  (USB_D_EPDIS6_V << USB_D_EPDIS6_S)
#define USB_D_EPDIS6_V  0x00000001
#define USB_D_EPDIS6_S  30
/** USB_D_EPENA6:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_D_EPENA6    (BIT(31))
#define USB_D_EPENA6_M  (USB_D_EPENA6_V << USB_D_EPENA6_S)
#define USB_D_EPENA6_V  0x00000001
#define USB_D_EPENA6_S  31


/** USB_DIEPTSIZ6_REG寄存器设备IN端点6传输大小寄存器
 */
#define USB_DIEPTSIZ6_REG (SOC_DPORT_USB_BASE + 0x9d0)
/** USB_D_XFERSIZE6:R/W；位位置：[7:0]；默认值：0；传输大小IN端点：每次将来自外部存储器的数据包写入TxFIFO OUT端点时，核心会减小此字段：每次从RxFIFO读取数据包并将其写入外部存储器时，核心都会减小此区域
 */
#define USB_D_XFERSIZE6    0x0000007F
#define USB_D_XFERSIZE6_M  (USB_D_XFERSIZE6_V << USB_D_XFERSIZE6_S)
#define USB_D_XFERSIZE6_V  0x0000007F
#define USB_D_XFERSIZE6_S  0
/** USB_D_PKTCNT6:R/W；比特位置：[21:19]；默认值：0；数据包计数IN端点：每次从TxFIFO OUT端点读取数据包（最大大小或短数据包）时，此字段都会减小：每次将数据包（最小大小或短）写入RxFIFO时，此区域都会减小
 */
#define USB_D_PKTCNT6    0x00000003
#define USB_D_PKTCNT6_M  (USB_D_PKTCNT6_V << USB_D_PKTCNT6_S)
#define USB_D_PKTCNT6_V  0x00000003
#define USB_D_PKTCNT6_S  19


/** USB_DIEPDMA6_REG寄存器设备IN端点6 DMA地址寄存器
 */
#define USB_DIEPDMA6_REG (SOC_DPORT_USB_BASE + 0x9d4)
/** USB_D_dmaddr6:R/W；位位置：[32:0]；默认值：0；此字段保存用于存储或获取端点数据的外部存储器的起始地址。
 */
#define USB_D_DMAADDR6    0xFFFFFFFF
#define USB_D_DMAADDR6_M  (USB_D_DMAADDR6_V << USB_D_DMAADDR6_S)
#define USB_D_DMAADDR6_V  0xFFFFFFFF
#define USB_D_DMAADDR6_S  0


/** USB_DOEPCTL0_REG寄存器设备控制输出端点$n控制寄存器
 */
#define USB_DOEPCTL0_REG (SOC_DPORT_USB_BASE + 0xb00)
/** USB_MPS0:RO；位位置：[2:0]；默认值：0；最大数据包大小0x0:64字节0x1:32字节0x2:16字节0x3:8字节
 */
#define USB_MPS0    0x00000003
#define USB_MPS0_M  (USB_MPS0_V << USB_MPS0_S)
#define USB_MPS0_V  0x00000003
#define USB_MPS0_S  0
/** USB_USBACTEP0:RO；位位置：[15]；默认值：1；0x1:USB活动端点0
 */
#define USB_USBACTEP0    (BIT(15))
#define USB_USBACTEP0_M  (USB_USBACTEP0_V << USB_USBACTEP0_S)
#define USB_USBACTEP0_V  0x00000001
#define USB_USBACTEP0_S  15
/** USB_naks0:RO；位位置：[17]；默认值：0；0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_NAKSTS0    (BIT(17))
#define USB_NAKSTS0_M  (USB_NAKSTS0_V << USB_NAKSTS0_S)
#define USB_NAKSTS0_V  0x00000001
#define USB_NAKSTS0_S  17
/** USB_EPTYPE0:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控件$n
 */
#define USB_EPTYPE0    0x00000003
#define USB_EPTYPE0_M  (USB_EPTYPE0_V << USB_EPTYPE0_S)
#define USB_EPTYPE0_V  0x00000003
#define USB_EPTYPE0_S  18
/** USB_SNP0:R/W；位位置：[20]；默认值：0；0x0:保留0 0x1:保留1
 */
#define USB_SNP0    (BIT(20))
#define USB_SNP0_M  (USB_SNP0_V << USB_SNP0_S)
#define USB_SNP0_V  0x00000001
#define USB_SNP0_S  20
/** USB_STALL0:R/W；位位置：[21]；默认值：0；当接收到此端点的SETUP令牌0x0（INACTIVE）：无暂停0x1（ACTIVE）：暂停握手时，应用程序只能设置此位，内核将其清除
 */
#define USB_STALL0    (BIT(21))
#define USB_STALL0_M  (USB_STALL0_V << USB_STALL0_S)
#define USB_STALL0_V  0x00000001
#define USB_STALL0_S  21
/** USB_CNAK0:WO；位位置：[26]；默认值：0；0x0：无操作0x1：清除NAK
 */
#define USB_CNAK0    (BIT(26))
#define USB_CNAK0_M  (USB_CNAK0_V << USB_CNAK0_S)
#define USB_CNAK0_V  0x00000001
#define USB_CNAK0_S  26
/** USB_DO_SNAK0:WO；位位置：[27]；默认值：0；0x0：无操作0x1：设置NAK
 */
#define USB_DO_SNAK0    (BIT(27))
#define USB_DO_SNAK0_M  (USB_DO_SNAK0_V << USB_DO_SNAK0_S)
#define USB_DO_SNAK0_V  0x00000001
#define USB_DO_SNAK0_S  27
/** USB_EPDIS0:RO；位位置：[30]；默认值：0；终结点禁用0x0：无终结点禁用
 */
#define USB_EPDIS0    (BIT(30))
#define USB_EPDIS0_M  (USB_EPDIS0_V << USB_EPDIS0_S)
#define USB_EPDIS0_V  0x00000001
#define USB_EPDIS0_S  30
/** USB_EPENA0:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_EPENA0    (BIT(31))
#define USB_EPENA0_M  (USB_EPENA0_V << USB_EPENA0_S)
#define USB_EPENA0_V  0x00000001
#define USB_EPENA0_S  31


/** USB_DOEPTSIZ0_REG寄存器设备输出端点0传输大小寄存器
 */
#define USB_DOEPTSIZ0_REG (SOC_DPORT_USB_BASE + 0xb10)
/** USB_XFERSIZE0:R/W；位位置：[7:0]；默认值：0；传输大小。指示ENDPOINT0的传输大小（字节）
 */
#define USB_XFERSIZE0    0x0000007F
#define USB_XFERSIZE0_M  (USB_XFERSIZE0_V << USB_XFERSIZE0_S)
#define USB_XFERSIZE0_V  0x0000007F
#define USB_XFERSIZE0_S  0
/** USB_PKTCNT0:R/W；位位置：[19]；默认值：0；数据包计数（PktCnt）。将数据包写入RxFIFO后，此字段将减为零。
 */
#define USB_PKTCNT0    (BIT(19))
#define USB_PKTCNT0_M  (USB_PKTCNT0_V << USB_PKTCNT0_S)
#define USB_PKTCNT0_V  0x00000001
#define USB_PKTCNT0_S  19
/** USB_SUPCNT0:R/W；位位置：[31:29]；默认值：0；设置数据包计数（SUPCnt）。此字段指定端点可以接收的背靠背SETUP数据包的数量：2’b01：1包2’b10：2包2’b11：3包
 */
#define USB_SUPCNT0    0x00000003
#define USB_SUPCNT0_M  (USB_SUPCNT0_V << USB_SUPCNT0_S)
#define USB_SUPCNT0_V  0x00000003
#define USB_SUPCNT0_S  29


/** USB_DOEPDMA0_REG寄存器设备输出端点0 DMA地址寄存器
 */
#define USB_DOEPDMA0_REG (SOC_DPORT_USB_BASE + 0xb14)
/** USB_dmaddr0:R/W；位位置：[32:0]；默认值：0；保存用于存储或获取端点数据的外部内存的起始地址。
 */
#define USB_DMAADDR0    0xFFFFFFFF
#define USB_DMAADDR0_M  (USB_DMAADDR0_V << USB_DMAADDR0_S)
#define USB_DMAADDR0_V  0xFFFFFFFF
#define USB_DMAADDR0_S  0


/** USB_DOEPDMAB0_REG寄存器设备输出端点16缓冲区地址寄存器
 */
#define USB_DOEPDMAB0_REG (SOC_DPORT_USB_BASE + 0xb1c)
/** USB_DMABUFFERADDR0:R/W；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_DMABUFFERADDR0    0xFFFFFFFF
#define USB_DMABUFFERADDR0_M  (USB_DMABUFFERADDR0_V << USB_DMABUFFERADDR0_S)
#define USB_DMABUFFERADDR0_V  0xFFFFFFFF
#define USB_DMABUFFERADDR0_S  0


/** USB_DOEPCTL1_REG寄存器设备控制输出端点1控制寄存器
 */
#define USB_DOEPCTL1_REG (SOC_DPORT_USB_BASE + 0xb20)
/** USB_MPS1:RO；位位置：[11:0]；默认值：0；最大数据包大小（字节）
 */
#define USB_MPS1    0x000007FF
#define USB_MPS1_M  (USB_MPS1_V << USB_MPS1_S)
#define USB_MPS1_V  0x000007FF
#define USB_MPS1_S  0
/** USB_USBACTEP1:RO；位位置：[15]；默认值：1；0x1:USB活动端点0
 */
#define USB_USBACTEP1    (BIT(15))
#define USB_USBACTEP1_M  (USB_USBACTEP1_V << USB_USBACTEP1_S)
#define USB_USBACTEP1_V  0x00000001
#define USB_USBACTEP1_S  15
/** USB_NAKSTS1:RO；位位置：[17]；默认值：0；0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_NAKSTS1    (BIT(17))
#define USB_NAKSTS1_M  (USB_NAKSTS1_V << USB_NAKSTS1_S)
#define USB_NAKSTS1_V  0x00000001
#define USB_NAKSTS1_S  17
/** USB_EPTYPE1:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制1
 */
#define USB_EPTYPE1    0x00000003
#define USB_EPTYPE1_M  (USB_EPTYPE1_V << USB_EPTYPE1_S)
#define USB_EPTYPE1_V  0x00000003
#define USB_EPTYPE1_S  18
/** USB_SNP1:R/W；位位置：[20]；默认值：0；0x0:保留0 0x1:保留1
 */
#define USB_SNP1    (BIT(20))
#define USB_SNP1_M  (USB_SNP1_V << USB_SNP1_S)
#define USB_SNP1_V  0x00000001
#define USB_SNP1_S  20
/** USB_STALL1:R/W；位位置：[21]；默认值：0；当接收到此端点的SETUP令牌0x0（INACTIVE）：无暂停0x1（ACTIVE）：暂停握手时，应用程序只能设置此位，内核将其清除
 */
#define USB_STALL1    (BIT(21))
#define USB_STALL1_M  (USB_STALL1_V << USB_STALL1_S)
#define USB_STALL1_V  0x00000001
#define USB_STALL1_S  21
/** USB_CNAK1:WO；位位置：[26]；默认值：0；0x0：无操作0x1：清除NAK
 */
#define USB_CNAK1    (BIT(26))
#define USB_CNAK1_M  (USB_CNAK1_V << USB_CNAK1_S)
#define USB_CNAK1_V  0x00000001
#define USB_CNAK1_S  26
/** USB_DO_SNAK1:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DO_SNAK1    (BIT(27))
#define USB_DO_SNAK1_M  (USB_DO_SNAK1_V << USB_DO_SNAK1_S)
#define USB_DO_SNAK1_V  0x00000001
#define USB_DO_SNAK1_S  27
/** USB_DO_SETD0PID1:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DO_SETD0PID1    (BIT(28))
#define USB_DO_SETD0PID1_M  (USB_DO_SETD0PID1_V << USB_DO_SETD0PID1_S)
#define USB_DO_SETD0PID1_V  0x00000001
#define USB_DO_SETD0PID1_S  28
/** USB_DO_SETD1PID1:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DO_SETD1PID1    (BIT(29))
#define USB_DO_SETD1PID1_M  (USB_DO_SETD1PID1_V << USB_DO_SETD1PID1_S)
#define USB_DO_SETD1PID1_V  0x00000001
#define USB_DO_SETD1PID1_S  29
/** USB_EPDIS1:RO；位位置：[30]；默认值：0；终结点禁用0x0：无终结点禁用
 */
#define USB_EPDIS1    (BIT(30))
#define USB_EPDIS1_M  (USB_EPDIS1_V << USB_EPDIS1_S)
#define USB_EPDIS1_V  0x00000001
#define USB_EPDIS1_S  30
/** USB_EPENA1:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_EPENA1    (BIT(31))
#define USB_EPENA1_M  (USB_EPENA1_V << USB_EPENA1_S)
#define USB_EPENA1_V  0x00000001
#define USB_EPENA1_S  31


/** USB_DOEPTSIZ1_REG寄存器设备输出端点1传输大小寄存器
 */
#define USB_DOEPTSIZ1_REG (SOC_DPORT_USB_BASE + 0xb30)
/** USB_XFERSIZE1:R/W；位位置：[7:0]；默认值：0；传输大小。指示ENDPOINT1的传输大小（字节）
 */
#define USB_XFERSIZE1    0x0000007F
#define USB_XFERSIZE1_M  (USB_XFERSIZE1_V << USB_XFERSIZE1_S)
#define USB_XFERSIZE1_V  0x0000007F
#define USB_XFERSIZE1_S  0
/** USB_PKTCNT1:R/W；位位置：[19]；默认值：0；数据包计数（PktCnt）。将数据包写入RxFIFO后，此字段将减为零。
 */
#define USB_PKTCNT1    (BIT(19))
#define USB_PKTCNT1_M  (USB_PKTCNT1_V << USB_PKTCNT1_S)
#define USB_PKTCNT1_V  0x00000001
#define USB_PKTCNT1_S  19
/** USB_SUPCNT1:R/W；位位置：[31:29]；默认值：0；设置数据包计数（SUPCnt）。此字段指定端点可以接收的背靠背SETUP数据包的数量：2’b01：1包2’b10：2包2’b11：3包
 */
#define USB_SUPCNT1    0x00000003
#define USB_SUPCNT1_M  (USB_SUPCNT1_V << USB_SUPCNT1_S)
#define USB_SUPCNT1_V  0x00000003
#define USB_SUPCNT1_S  29


/** USB_DOEPDMA1_REG寄存器设备输出端点1 DMA地址寄存器
 */
#define USB_DOEPDMA1_REG (SOC_DPORT_USB_BASE + 0xb34)
/** USB_DMAADDR1:R/W；位位置：[32:0]；默认值：0；保存用于存储或获取端点数据的外部内存的起始地址。
 */
#define USB_DMAADDR1    0xFFFFFFFF
#define USB_DMAADDR1_M  (USB_DMAADDR1_V << USB_DMAADDR1_S)
#define USB_DMAADDR1_V  0xFFFFFFFF
#define USB_DMAADDR1_S  0


/** USB_DOEPDMAB1_REG寄存器设备输出端点16缓冲区地址寄存器
 */
#define USB_DOEPDMAB1_REG (SOC_DPORT_USB_BASE + 0xb3c)
/** USB_DMABUFFERADDR1：R/W；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_DMABUFFERADDR1    0xFFFFFFFF
#define USB_DMABUFFERADDR1_M  (USB_DMABUFFERADDR1_V << USB_DMABUFFERADDR1_S)
#define USB_DMABUFFERADDR1_V  0xFFFFFFFF
#define USB_DMABUFFERADDR1_S  0


/** USB_DOEPCTL2_REG寄存器设备控制输出端点2控制寄存器
 */
#define USB_DOEPCTL2_REG (SOC_DPORT_USB_BASE + 0xb40)
/** USB_MPS2:RO；位位置：[11:0]；默认值：0；最大数据包大小（字节）
 */
#define USB_MPS2    0x000007FF
#define USB_MPS2_M  (USB_MPS2_V << USB_MPS2_S)
#define USB_MPS2_V  0x000007FF
#define USB_MPS2_S  0
/** USB_USBACTEP2:RO；位位置：[15]；默认值：1；0x1:USB活动端点0
 */
#define USB_USBACTEP2    (BIT(15))
#define USB_USBACTEP2_M  (USB_USBACTEP2_V << USB_USBACTEP2_S)
#define USB_USBACTEP2_V  0x00000001
#define USB_USBACTEP2_S  15
/** USB_nakss2:RO；位位置：[17]；默认值：0；0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_NAKSTS2    (BIT(17))
#define USB_NAKSTS2_M  (USB_NAKSTS2_V << USB_NAKSTS2_S)
#define USB_NAKSTS2_V  0x00000001
#define USB_NAKSTS2_S  17
/** USB_EPTYPE2:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制2
 */
#define USB_EPTYPE2    0x00000003
#define USB_EPTYPE2_M  (USB_EPTYPE2_V << USB_EPTYPE2_S)
#define USB_EPTYPE2_V  0x00000003
#define USB_EPTYPE2_S  18
/** USB_SNP2:R/W；位位置：[20]；默认值：0；0x0:保留0 0x1:保留1
 */
#define USB_SNP2    (BIT(20))
#define USB_SNP2_M  (USB_SNP2_V << USB_SNP2_S)
#define USB_SNP2_V  0x00000001
#define USB_SNP2_S  20
/** USB_STALL2:R/W；位位置：[21]；默认值：0；当接收到此端点的SETUP令牌0x0（INACTIVE）：无暂停0x1（ACTIVE）：暂停握手时，应用程序只能设置此位，内核将其清除
 */
#define USB_STALL2    (BIT(21))
#define USB_STALL2_M  (USB_STALL2_V << USB_STALL2_S)
#define USB_STALL2_V  0x00000001
#define USB_STALL2_S  21
/** USB_CNAK2:WO；位位置：[26]；默认值：0；0x0：无操作0x1：清除NAK
 */
#define USB_CNAK2    (BIT(26))
#define USB_CNAK2_M  (USB_CNAK2_V << USB_CNAK2_S)
#define USB_CNAK2_V  0x00000001
#define USB_CNAK2_S  26
/** USB_DO_SNAK2:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DO_SNAK2    (BIT(27))
#define USB_DO_SNAK2_M  (USB_DO_SNAK2_V << USB_DO_SNAK2_S)
#define USB_DO_SNAK2_V  0x00000001
#define USB_DO_SNAK2_S  27
/** USB_DO_SETD0PID2:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DO_SETD0PID2    (BIT(28))
#define USB_DO_SETD0PID2_M  (USB_DO_SETD0PID2_V << USB_DO_SETD0PID2_S)
#define USB_DO_SETD0PID2_V  0x00000001
#define USB_DO_SETD0PID2_S  28
/** USB_DO_SETD1PID2:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DO_SETD1PID2    (BIT(29))
#define USB_DO_SETD1PID2_M  (USB_DO_SETD1PID2_V << USB_DO_SETD1PID2_S)
#define USB_DO_SETD1PID2_V  0x00000001
#define USB_DO_SETD1PID2_S  29
/** USB_EPDIS2:RO；位位置：[30]；默认值：0；终结点禁用0x0：无终结点禁用
 */
#define USB_EPDIS2    (BIT(30))
#define USB_EPDIS2_M  (USB_EPDIS2_V << USB_EPDIS2_S)
#define USB_EPDIS2_V  0x00000001
#define USB_EPDIS2_S  30
/** USB_EPENA2:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_EPENA2    (BIT(31))
#define USB_EPENA2_M  (USB_EPENA2_V << USB_EPENA2_S)
#define USB_EPENA2_V  0x00000001
#define USB_EPENA2_S  31


/** USB_DOEPTSIZ2_REG寄存器设备输出端点2传输大小寄存器
 */
#define USB_DOEPTSIZ2_REG (SOC_DPORT_USB_BASE + 0xb50)
/** USB_XFERSIZE2:R/W；位位置：[7:0]；默认值：0；传输大小。指示ENDPOINT2的传输大小（字节）
 */
#define USB_XFERSIZE2    0x0000007F
#define USB_XFERSIZE2_M  (USB_XFERSIZE2_V << USB_XFERSIZE2_S)
#define USB_XFERSIZE2_V  0x0000007F
#define USB_XFERSIZE2_S  0
/** USB_PKTCNT2:R/W；位位置：[19]；默认值：0；数据包计数（PktCnt）。将数据包写入RxFIFO后，此字段将减为零。
 */
#define USB_PKTCNT2    (BIT(19))
#define USB_PKTCNT2_M  (USB_PKTCNT2_V << USB_PKTCNT2_S)
#define USB_PKTCNT2_V  0x00000001
#define USB_PKTCNT2_S  19
/** USB_SUPCNT2:R/W；位位置：[31:29]；默认值：0；设置数据包计数（SUPCnt）。此字段指定端点可以接收的背靠背SETUP数据包的数量：2’b01：1包2’b10：2包2’b11：3包
 */
#define USB_SUPCNT2    0x00000003
#define USB_SUPCNT2_M  (USB_SUPCNT2_V << USB_SUPCNT2_S)
#define USB_SUPCNT2_V  0x00000003
#define USB_SUPCNT2_S  29


/** USB_DOEPDMA2_REG寄存器设备输出端点2 DMA地址寄存器
 */
#define USB_DOEPDMA2_REG (SOC_DPORT_USB_BASE + 0xb54)
/** USB_DMAADDR2:R/W；位位置：[32:0]；默认值：0；保存用于存储或获取端点数据的外部内存的起始地址。
 */
#define USB_DMAADDR2    0xFFFFFFFF
#define USB_DMAADDR2_M  (USB_DMAADDR2_V << USB_DMAADDR2_S)
#define USB_DMAADDR2_V  0xFFFFFFFF
#define USB_DMAADDR2_S  0


/** USB_DOEPDMAB2_REG寄存器设备输出端点16缓冲区地址寄存器
 */
#define USB_DOEPDMAB2_REG (SOC_DPORT_USB_BASE + 0xb5c)
/** USB_DMABUFFERADDR2:R/W；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_DMABUFFERADDR2    0xFFFFFFFF
#define USB_DMABUFFERADDR2_M  (USB_DMABUFFERADDR2_V << USB_DMABUFFERADDR2_S)
#define USB_DMABUFFERADDR2_V  0xFFFFFFFF
#define USB_DMABUFFERADDR2_S  0


/** USB_DOEPCTL3_REG寄存器设备控制输出端点3控制寄存器
 */
#define USB_DOEPCTL3_REG (SOC_DPORT_USB_BASE + 0xb60)
/** USB_MPS3:RO；位位置：[11:0]；默认值：0；最大数据包大小（字节）
 */
#define USB_MPS3    0x000007FF
#define USB_MPS3_M  (USB_MPS3_V << USB_MPS3_S)
#define USB_MPS3_V  0x000007FF
#define USB_MPS3_S  0
/** USB_USBACTEP3:RO；位位置：[15]；默认值：1；0x1:USB活动端点0
 */
#define USB_USBACTEP3    (BIT(15))
#define USB_USBACTEP3_M  (USB_USBACTEP3_V << USB_USBACTEP3_S)
#define USB_USBACTEP3_V  0x00000001
#define USB_USBACTEP3_S  15
/** USB_NAKSTS3:RO；位位置：[17]；默认值：0；0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_NAKSTS3    (BIT(17))
#define USB_NAKSTS3_M  (USB_NAKSTS3_V << USB_NAKSTS3_S)
#define USB_NAKSTS3_V  0x00000001
#define USB_NAKSTS3_S  17
/** USB_EPTYPE3:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制3
 */
#define USB_EPTYPE3    0x00000003
#define USB_EPTYPE3_M  (USB_EPTYPE3_V << USB_EPTYPE3_S)
#define USB_EPTYPE3_V  0x00000003
#define USB_EPTYPE3_S  18
/** USB_SNP3:R/W；位位置：[20]；默认值：0；0x0:保留0 0x1:保留1
 */
#define USB_SNP3    (BIT(20))
#define USB_SNP3_M  (USB_SNP3_V << USB_SNP3_S)
#define USB_SNP3_V  0x00000001
#define USB_SNP3_S  20
/** USB_STALL3:R/W；位位置：[21]；默认值：0；当接收到此端点的SETUP令牌0x0（INACTIVE）：无暂停0x1（ACTIVE）：暂停握手时，应用程序只能设置此位，内核将其清除
 */
#define USB_STALL3    (BIT(21))
#define USB_STALL3_M  (USB_STALL3_V << USB_STALL3_S)
#define USB_STALL3_V  0x00000001
#define USB_STALL3_S  21
/** USB_CNAK3:WO；位位置：[26]；默认值：0；0x0：无操作0x1：清除NAK
 */
#define USB_CNAK3    (BIT(26))
#define USB_CNAK3_M  (USB_CNAK3_V << USB_CNAK3_S)
#define USB_CNAK3_V  0x00000001
#define USB_CNAK3_S  26
/** USB_DO_SNAK3:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DO_SNAK3    (BIT(27))
#define USB_DO_SNAK3_M  (USB_DO_SNAK3_V << USB_DO_SNAK3_S)
#define USB_DO_SNAK3_V  0x00000001
#define USB_DO_SNAK3_S  27
/** USB_DO_SETD0PID3:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DO_SETD0PID3    (BIT(28))
#define USB_DO_SETD0PID3_M  (USB_DO_SETD0PID3_V << USB_DO_SETD0PID3_S)
#define USB_DO_SETD0PID3_V  0x00000001
#define USB_DO_SETD0PID3_S  28
/** USB_DO_SETD1PID3:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DO_SETD1PID3    (BIT(29))
#define USB_DO_SETD1PID3_M  (USB_DO_SETD1PID3_V << USB_DO_SETD1PID3_S)
#define USB_DO_SETD1PID3_V  0x00000001
#define USB_DO_SETD1PID3_S  29
/** USB_EPDIS3:RO；位位置：[30]；默认值：0；终结点禁用0x0：无终结点禁用
 */
#define USB_EPDIS3    (BIT(30))
#define USB_EPDIS3_M  (USB_EPDIS3_V << USB_EPDIS3_S)
#define USB_EPDIS3_V  0x00000001
#define USB_EPDIS3_S  30
/** USB_EPENA3:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_EPENA3    (BIT(31))
#define USB_EPENA3_M  (USB_EPENA3_V << USB_EPENA3_S)
#define USB_EPENA3_V  0x00000001
#define USB_EPENA3_S  31


/** USB_DOEPTSIZ3_REG寄存器设备输出端点3传输大小寄存器
 */
#define USB_DOEPTSIZ3_REG (SOC_DPORT_USB_BASE + 0xb70)
/** USB_XFERSIZE3:R/W；位位置：[7:0]；默认值：0；传输大小。指示ENDPOINT3的传输大小（字节）
 */
#define USB_XFERSIZE3    0x0000007F
#define USB_XFERSIZE3_M  (USB_XFERSIZE3_V << USB_XFERSIZE3_S)
#define USB_XFERSIZE3_V  0x0000007F
#define USB_XFERSIZE3_S  0
/** USB_PKTCNT3:R/W；位位置：[19]；默认值：0；数据包计数（PktCnt）。将数据包写入RxFIFO后，此字段将减为零。
 */
#define USB_PKTCNT3    (BIT(19))
#define USB_PKTCNT3_M  (USB_PKTCNT3_V << USB_PKTCNT3_S)
#define USB_PKTCNT3_V  0x00000001
#define USB_PKTCNT3_S  19
/** USB_SUPCNT3:R/W；位位置：[31:29]；默认值：0；设置数据包计数（SUPCnt）。此字段指定端点可以接收的背靠背SETUP数据包的数量：2’b01：1包2’b10：2包2’b11：3包
 */
#define USB_SUPCNT3    0x00000003
#define USB_SUPCNT3_M  (USB_SUPCNT3_V << USB_SUPCNT3_S)
#define USB_SUPCNT3_V  0x00000003
#define USB_SUPCNT3_S  29


/** USB_DOEPDMA3_REG寄存器设备输出端点3 DMA地址寄存器
 */
#define USB_DOEPDMA3_REG (SOC_DPORT_USB_BASE + 0xb74)
/** USB_DMAADDR3:R/W；位位置：[32:0]；默认值：0；保存用于存储或获取端点数据的外部内存的起始地址。
 */
#define USB_DMAADDR3    0xFFFFFFFF
#define USB_DMAADDR3_M  (USB_DMAADDR3_V << USB_DMAADDR3_S)
#define USB_DMAADDR3_V  0xFFFFFFFF
#define USB_DMAADDR3_S  0


/** USB_DOEPDMAB3_REG寄存器设备输出端点16缓冲区地址寄存器
 */
#define USB_DOEPDMAB3_REG (SOC_DPORT_USB_BASE + 0xb7c)
/** USB_DMABUFFERADDR3:R/W；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_DMABUFFERADDR3    0xFFFFFFFF
#define USB_DMABUFFERADDR3_M  (USB_DMABUFFERADDR3_V << USB_DMABUFFERADDR3_S)
#define USB_DMABUFFERADDR3_V  0xFFFFFFFF
#define USB_DMABUFFERADDR3_S  0


/** USB_DOEPCTL4_REG寄存器设备控制输出端点4控制寄存器
 */
#define USB_DOEPCTL4_REG (SOC_DPORT_USB_BASE + 0xb80)
/** USB_MPS4:RO；位位置：[11:0]；默认值：0；最大数据包大小（字节）
 */
#define USB_MPS4    0x000007FF
#define USB_MPS4_M  (USB_MPS4_V << USB_MPS4_S)
#define USB_MPS4_V  0x000007FF
#define USB_MPS4_S  0
/** USB_USBACTEP4:RO；位位置：[15]；默认值：1；0x1:USB活动端点0
 */
#define USB_USBACTEP4    (BIT(15))
#define USB_USBACTEP4_M  (USB_USBACTEP4_V << USB_USBACTEP4_S)
#define USB_USBACTEP4_V  0x00000001
#define USB_USBACTEP4_S  15
/** USB_nakss4:RO；位位置：[17]；默认值：0；0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_NAKSTS4    (BIT(17))
#define USB_NAKSTS4_M  (USB_NAKSTS4_V << USB_NAKSTS4_S)
#define USB_NAKSTS4_V  0x00000001
#define USB_NAKSTS4_S  17
/** USB_EPTYPE4:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制4
 */
#define USB_EPTYPE4    0x00000003
#define USB_EPTYPE4_M  (USB_EPTYPE4_V << USB_EPTYPE4_S)
#define USB_EPTYPE4_V  0x00000003
#define USB_EPTYPE4_S  18
/** USB_SNP4:R/W；位位置：[20]；默认值：0；0x0:保留0 0x1:保留1
 */
#define USB_SNP4    (BIT(20))
#define USB_SNP4_M  (USB_SNP4_V << USB_SNP4_S)
#define USB_SNP4_V  0x00000001
#define USB_SNP4_S  20
/** USB_STALL4:R/W；位位置：[21]；默认值：0；当接收到此端点的SETUP令牌0x0（INACTIVE）：无暂停0x1（ACTIVE）：暂停握手时，应用程序只能设置此位，内核将其清除
 */
#define USB_STALL4    (BIT(21))
#define USB_STALL4_M  (USB_STALL4_V << USB_STALL4_S)
#define USB_STALL4_V  0x00000001
#define USB_STALL4_S  21
/** USB_CNAK4:WO；位位置：[26]；默认值：0；0x0：无操作0x1：清除NAK
 */
#define USB_CNAK4    (BIT(26))
#define USB_CNAK4_M  (USB_CNAK4_V << USB_CNAK4_S)
#define USB_CNAK4_V  0x00000001
#define USB_CNAK4_S  26
/** USB_DO_SNAK4:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DO_SNAK4    (BIT(27))
#define USB_DO_SNAK4_M  (USB_DO_SNAK4_V << USB_DO_SNAK4_S)
#define USB_DO_SNAK4_V  0x00000001
#define USB_DO_SNAK4_S  27
/** USB_DO_SETD0PID4:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DO_SETD0PID4    (BIT(28))
#define USB_DO_SETD0PID4_M  (USB_DO_SETD0PID4_V << USB_DO_SETD0PID4_S)
#define USB_DO_SETD0PID4_V  0x00000001
#define USB_DO_SETD0PID4_S  28
/** USB_DO_SETD1PID4:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DO_SETD1PID4    (BIT(29))
#define USB_DO_SETD1PID4_M  (USB_DO_SETD1PID4_V << USB_DO_SETD1PID4_S)
#define USB_DO_SETD1PID4_V  0x00000001
#define USB_DO_SETD1PID4_S  29
/** USB_EPDIS4:RO；位位置：[30]；默认值：0；终结点禁用0x0：无终结点禁用
 */
#define USB_EPDIS4    (BIT(30))
#define USB_EPDIS4_M  (USB_EPDIS4_V << USB_EPDIS4_S)
#define USB_EPDIS4_V  0x00000001
#define USB_EPDIS4_S  30
/** USB_EPENA4:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_EPENA4    (BIT(31))
#define USB_EPENA4_M  (USB_EPENA4_V << USB_EPENA4_S)
#define USB_EPENA4_V  0x00000001
#define USB_EPENA4_S  31


/** USB_DOEPTSIZ4_REG寄存器设备输出端点4传输大小寄存器
 */
#define USB_DOEPTSIZ4_REG (SOC_DPORT_USB_BASE + 0xb90)
/** USB_XFERSIZE4:R/W；位位置：[7:0]；默认值：0；传输大小。指示ENDPOINT4的传输大小（字节）
 */
#define USB_XFERSIZE4    0x0000007F
#define USB_XFERSIZE4_M  (USB_XFERSIZE4_V << USB_XFERSIZE4_S)
#define USB_XFERSIZE4_V  0x0000007F
#define USB_XFERSIZE4_S  0
/** USB_PKTCNT4:R/W；位位置：[19]；默认值：0；数据包计数（PktCnt）。将数据包写入RxFIFO后，此字段将减为零。
 */
#define USB_PKTCNT4    (BIT(19))
#define USB_PKTCNT4_M  (USB_PKTCNT4_V << USB_PKTCNT4_S)
#define USB_PKTCNT4_V  0x00000001
#define USB_PKTCNT4_S  19
/** USB_SUPCNT4:R/W；位位置：[31:29]；默认值：0；设置数据包计数（SUPCnt）。此字段指定端点可以接收的背靠背SETUP数据包的数量：2’b01：1包2’b10：2包2’b11：3包
 */
#define USB_SUPCNT4    0x00000003
#define USB_SUPCNT4_M  (USB_SUPCNT4_V << USB_SUPCNT4_S)
#define USB_SUPCNT4_V  0x00000003
#define USB_SUPCNT4_S  29


/** USB_DOEPDMA4_REG寄存器设备输出端点4 DMA地址寄存器
 */
#define USB_DOEPDMA4_REG (SOC_DPORT_USB_BASE + 0xb94)
/** USB_dmaddr4:R/W；位位置：[32:0]；默认值：0；保存用于存储或获取端点数据的外部内存的起始地址。
 */
#define USB_DMAADDR4    0xFFFFFFFF
#define USB_DMAADDR4_M  (USB_DMAADDR4_V << USB_DMAADDR4_S)
#define USB_DMAADDR4_V  0xFFFFFFFF
#define USB_DMAADDR4_S  0


/** USB_DOEPDMAB4_REG寄存器设备输出端点16缓冲区地址寄存器
 */
#define USB_DOEPDMAB4_REG (SOC_DPORT_USB_BASE + 0xb9c)
/** USB_DMABUFFERADDR4:R/W；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_DMABUFFERADDR4    0xFFFFFFFF
#define USB_DMABUFFERADDR4_M  (USB_DMABUFFERADDR4_V << USB_DMABUFFERADDR4_S)
#define USB_DMABUFFERADDR4_V  0xFFFFFFFF
#define USB_DMABUFFERADDR4_S  0


/** USB_DOEPCTL5_REG寄存器设备控制输出端点5控制寄存器
 */
#define USB_DOEPCTL5_REG (SOC_DPORT_USB_BASE + 0xba0)
/** USB_MPS5:RO；位位置：[11:0]；默认值：0；最大数据包大小（字节）
 */
#define USB_MPS5    0x000007FF
#define USB_MPS5_M  (USB_MPS5_V << USB_MPS5_S)
#define USB_MPS5_V  0x000007FF
#define USB_MPS5_S  0
/** USB_USBACTEP5:RO；位位置：[15]；默认值：1；0x1:USB活动端点0
 */
#define USB_USBACTEP5    (BIT(15))
#define USB_USBACTEP5_M  (USB_USBACTEP5_V << USB_USBACTEP5_S)
#define USB_USBACTEP5_V  0x00000001
#define USB_USBACTEP5_S  15
/** USB_NAKSTS5:RO；位位置：[17]；默认值：0；0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_NAKSTS5    (BIT(17))
#define USB_NAKSTS5_M  (USB_NAKSTS5_V << USB_NAKSTS5_S)
#define USB_NAKSTS5_V  0x00000001
#define USB_NAKSTS5_S  17
/** USB_EPTYPE5:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制5
 */
#define USB_EPTYPE5    0x00000003
#define USB_EPTYPE5_M  (USB_EPTYPE5_V << USB_EPTYPE5_S)
#define USB_EPTYPE5_V  0x00000003
#define USB_EPTYPE5_S  18
/** USB_SNP5:R/W；位位置：[20]；默认值：0；0x0:保留0 0x1:保留1
 */
#define USB_SNP5    (BIT(20))
#define USB_SNP5_M  (USB_SNP5_V << USB_SNP5_S)
#define USB_SNP5_V  0x00000001
#define USB_SNP5_S  20
/** USB_STALL5:R/W；位位置：[21]；默认值：0；当接收到此端点的SETUP令牌0x0（INACTIVE）：无暂停0x1（ACTIVE）：暂停握手时，应用程序只能设置此位，内核将其清除
 */
#define USB_STALL5    (BIT(21))
#define USB_STALL5_M  (USB_STALL5_V << USB_STALL5_S)
#define USB_STALL5_V  0x00000001
#define USB_STALL5_S  21
/** USB_CNAK5:WO；位位置：[26]；默认值：0；0x0：无操作0x1：清除NAK
 */
#define USB_CNAK5    (BIT(26))
#define USB_CNAK5_M  (USB_CNAK5_V << USB_CNAK5_S)
#define USB_CNAK5_V  0x00000001
#define USB_CNAK5_S  26
/** USB_DO_SNAK5:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DO_SNAK5    (BIT(27))
#define USB_DO_SNAK5_M  (USB_DO_SNAK5_V << USB_DO_SNAK5_S)
#define USB_DO_SNAK5_V  0x00000001
#define USB_DO_SNAK5_S  27
/** USB_DO_SETD0PID5:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DO_SETD0PID5    (BIT(28))
#define USB_DO_SETD0PID5_M  (USB_DO_SETD0PID5_V << USB_DO_SETD0PID5_S)
#define USB_DO_SETD0PID5_V  0x00000001
#define USB_DO_SETD0PID5_S  28
/** USB_DO_SETD1PID5:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DO_SETD1PID5    (BIT(29))
#define USB_DO_SETD1PID5_M  (USB_DO_SETD1PID5_V << USB_DO_SETD1PID5_S)
#define USB_DO_SETD1PID5_V  0x00000001
#define USB_DO_SETD1PID5_S  29
/** USB_EPDIS5:RO；位位置：[30]；默认值：0；终结点禁用0x0：无终结点禁用
 */
#define USB_EPDIS5    (BIT(30))
#define USB_EPDIS5_M  (USB_EPDIS5_V << USB_EPDIS5_S)
#define USB_EPDIS5_V  0x00000001
#define USB_EPDIS5_S  30
/** USB_EPENA5:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_EPENA5    (BIT(31))
#define USB_EPENA5_M  (USB_EPENA5_V << USB_EPENA5_S)
#define USB_EPENA5_V  0x00000001
#define USB_EPENA5_S  31


/** USB_DOEPTSIZ5_REG寄存器设备输出端点5传输大小寄存器
 */
#define USB_DOEPTSIZ5_REG (SOC_DPORT_USB_BASE + 0xbb0)
/** USB_XFERSIZE5:R/W；位位置：[7:0]；默认值：0；传输大小。指示ENDPOINT5的传输大小（字节）
 */
#define USB_XFERSIZE5    0x0000007F
#define USB_XFERSIZE5_M  (USB_XFERSIZE5_V << USB_XFERSIZE5_S)
#define USB_XFERSIZE5_V  0x0000007F
#define USB_XFERSIZE5_S  0
/** USB_PKTCNT5:R/W；位位置：[19]；默认值：0；数据包计数（PktCnt）。将数据包写入RxFIFO后，此字段将减为零。
 */
#define USB_PKTCNT5    (BIT(19))
#define USB_PKTCNT5_M  (USB_PKTCNT5_V << USB_PKTCNT5_S)
#define USB_PKTCNT5_V  0x00000001
#define USB_PKTCNT5_S  19
/** USB_SUPCNT5:R/W；位位置：[31:29]；默认值：0；设置数据包计数（SUPCnt）。此字段指定端点可以接收的背靠背SETUP数据包的数量：2’b01：1包2’b10：2包2’b11：3包
 */
#define USB_SUPCNT5    0x00000003
#define USB_SUPCNT5_M  (USB_SUPCNT5_V << USB_SUPCNT5_S)
#define USB_SUPCNT5_V  0x00000003
#define USB_SUPCNT5_S  29


/** USB_DOEPDMA5_REG寄存器设备输出端点5 DMA地址寄存器
 */
#define USB_DOEPDMA5_REG (SOC_DPORT_USB_BASE + 0xbb4)
/** USB_dmaddr5:R/W；位位置：[32:0]；默认值：0；保存用于存储或获取端点数据的外部内存的起始地址。
 */
#define USB_DMAADDR5    0xFFFFFFFF
#define USB_DMAADDR5_M  (USB_DMAADDR5_V << USB_DMAADDR5_S)
#define USB_DMAADDR5_V  0xFFFFFFFF
#define USB_DMAADDR5_S  0


/** USB_DOEPDMAB5_REG寄存器设备输出端点16缓冲区地址寄存器
 */
#define USB_DOEPDMAB5_REG (SOC_DPORT_USB_BASE + 0xbbc)
/** USB_DMABUFFERADDR5:R/W；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_DMABUFFERADDR5    0xFFFFFFFF
#define USB_DMABUFFERADDR5_M  (USB_DMABUFFERADDR5_V << USB_DMABUFFERADDR5_S)
#define USB_DMABUFFERADDR5_V  0xFFFFFFFF
#define USB_DMABUFFERADDR5_S  0


/** USB_DOEPCTL6_REG寄存器设备控制输出端点6控制寄存器
 */
#define USB_DOEPCTL6_REG (SOC_DPORT_USB_BASE + 0xbc0)
/** USB_MPS6:RO；位位置：[11:0]；默认值：0；最大数据包大小（字节）
 */
#define USB_MPS6    0x000007FF
#define USB_MPS6_M  (USB_MPS6_V << USB_MPS6_S)
#define USB_MPS6_V  0x000007FF
#define USB_MPS6_S  0
/** USB_USBACTEP6:RO；位位置：[15]；默认值：1；0x1:USB活动端点0
 */
#define USB_USBACTEP6    (BIT(15))
#define USB_USBACTEP6_M  (USB_USBACTEP6_V << USB_USBACTEP6_S)
#define USB_USBACTEP6_V  0x00000001
#define USB_USBACTEP6_S  15
/** USB_naks6:RO；位位置：[17]；默认值：0；0x0：核心正在基于FIFO状态发送非NAK握手0x1：核心在此端点上发送NAK握手
 */
#define USB_NAKSTS6    (BIT(17))
#define USB_NAKSTS6_M  (USB_NAKSTS6_V << USB_NAKSTS6_S)
#define USB_NAKSTS6_V  0x00000001
#define USB_NAKSTS6_S  17
/** USB_EPTYPE6:RO；比特位置：[20:18]；默认值：0；终结点类型0x0:终结点控制6
 */
#define USB_EPTYPE6    0x00000003
#define USB_EPTYPE6_M  (USB_EPTYPE6_V << USB_EPTYPE6_S)
#define USB_EPTYPE6_V  0x00000003
#define USB_EPTYPE6_S  18
/** USB_SNP6:R/W；位位置：[20]；默认值：0；0x0:保留0 0x1:保留1
 */
#define USB_SNP6    (BIT(20))
#define USB_SNP6_M  (USB_SNP6_V << USB_SNP6_S)
#define USB_SNP6_V  0x00000001
#define USB_SNP6_S  20
/** USB_STALL6:R/W；位位置：[21]；默认值：0；当接收到此端点的SETUP令牌0x0（INACTIVE）：无暂停0x1（ACTIVE）：暂停握手时，应用程序只能设置此位，内核将其清除
 */
#define USB_STALL6    (BIT(21))
#define USB_STALL6_M  (USB_STALL6_V << USB_STALL6_S)
#define USB_STALL6_V  0x00000001
#define USB_STALL6_S  21
/** USB_CNAK6:WO；位位置：[26]；默认值：0；0x0：无操作0x1：清除NAK
 */
#define USB_CNAK6    (BIT(26))
#define USB_CNAK6_M  (USB_CNAK6_V << USB_CNAK6_S)
#define USB_CNAK6_V  0x00000001
#define USB_CNAK6_S  26
/** USB_DO_SNAK6:WO；位位置：[27]；默认值：0；写入此位将设置端点的NAK位0x0:无操作0x1:设置NAK
 */
#define USB_DO_SNAK6    (BIT(27))
#define USB_DO_SNAK6_M  (USB_DO_SNAK6_V << USB_DO_SNAK6_S)
#define USB_DO_SNAK6_V  0x00000001
#define USB_DO_SNAK6_S  27
/** USB_DO_SETD0PID6:WO；位位置：[28]；默认值：0；设置DATA0 PID
 */
#define USB_DO_SETD0PID6    (BIT(28))
#define USB_DO_SETD0PID6_M  (USB_DO_SETD0PID6_V << USB_DO_SETD0PID6_S)
#define USB_DO_SETD0PID6_V  0x00000001
#define USB_DO_SETD0PID6_S  28
/** USB_DO_SETD1PID6:WO；位位置：[29]；默认值：0；设置DATA1 PID
 */
#define USB_DO_SETD1PID6    (BIT(29))
#define USB_DO_SETD1PID6_M  (USB_DO_SETD1PID6_V << USB_DO_SETD1PID6_S)
#define USB_DO_SETD1PID6_V  0x00000001
#define USB_DO_SETD1PID6_S  29
/** USB_EPDIS6:RO；位位置：[30]；默认值：0；终结点禁用0x0：无终结点禁用
 */
#define USB_EPDIS6    (BIT(30))
#define USB_EPDIS6_M  (USB_EPDIS6_V << USB_EPDIS6_S)
#define USB_EPDIS6_V  0x00000001
#define USB_EPDIS6_S  30
/** USB_EPENA6:R/W；位位置：[31]；默认值：0；端点启用0x0：无操作0x1：启用端点
 */
#define USB_EPENA6    (BIT(31))
#define USB_EPENA6_M  (USB_EPENA6_V << USB_EPENA6_S)
#define USB_EPENA6_V  0x00000001
#define USB_EPENA6_S  31


/** USB_DOEPTSIZ6_REG寄存器设备输出端点6传输大小寄存器
 */
#define USB_DOEPTSIZ6_REG (SOC_DPORT_USB_BASE + 0xbd0)
/** USB_XFERSIZE6:R/W；位位置：[7:0]；默认值：0；传输大小。指示ENDPOINT6的传输大小（字节）
 */
#define USB_XFERSIZE6    0x0000007F
#define USB_XFERSIZE6_M  (USB_XFERSIZE6_V << USB_XFERSIZE6_S)
#define USB_XFERSIZE6_V  0x0000007F
#define USB_XFERSIZE6_S  0
/** USB_PKTCNT6:R/W；位位置：[19]；默认值：0；数据包计数（PktCnt）。将数据包写入RxFIFO后，此字段将减为零。
 */
#define USB_PKTCNT6    (BIT(19))
#define USB_PKTCNT6_M  (USB_PKTCNT6_V << USB_PKTCNT6_S)
#define USB_PKTCNT6_V  0x00000001
#define USB_PKTCNT6_S  19
/** USB_SUPCNT6:R/W；位位置：[31:29]；默认值：0；设置数据包计数（SUPCnt）。此字段指定端点可以接收的背靠背SETUP数据包的数量：2’b01：1包2’b10：2包2’b11：3包
 */
#define USB_SUPCNT6    0x00000003
#define USB_SUPCNT6_M  (USB_SUPCNT6_V << USB_SUPCNT6_S)
#define USB_SUPCNT6_V  0x00000003
#define USB_SUPCNT6_S  29


/** USB_DOEPDMA6_REG寄存器设备输出端点6 DMA地址寄存器
 */
#define USB_DOEPDMA6_REG (SOC_DPORT_USB_BASE + 0xbd4)
/** USB_dmaddr6:R/W；位位置：[32:0]；默认值：0；保存用于存储或获取端点数据的外部内存的起始地址。
 */
#define USB_DMAADDR6    0xFFFFFFFF
#define USB_DMAADDR6_M  (USB_DMAADDR6_V << USB_DMAADDR6_S)
#define USB_DMAADDR6_V  0xFFFFFFFF
#define USB_DMAADDR6_S  0


/** USB_DOEPDMAB6_REG寄存器设备输出端点16缓冲区地址寄存器
 */
#define USB_DOEPDMAB6_REG (SOC_DPORT_USB_BASE + 0xbdc)
/** USB_DMABUFFERADDR6:R/W；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_DMABUFFERADDR6    0xFFFFFFFF
#define USB_DMABUFFERADDR6_M  (USB_DMABUFFERADDR6_V << USB_DMABUFFERADDR6_S)
#define USB_DMABUFFERADDR6_V  0xFFFFFFFF
#define USB_DMABUFFERADDR6_S  0


/** USB_PCGCCTL_REG寄存器电源和时钟门控控制寄存器
 */
#define USB_PCGCCTL_REG (SOC_DPORT_USB_BASE + 0xe00)
/** USB_stopclk:R/W；位位置：[0]；默认值：0；0x0：禁用停止Pclk 0x1：启用停止Pcl
 */
#define USB_STOPPCLK    (BIT(0))
#define USB_STOPPCLK_M  (USB_STOPPCLK_V << USB_STOPPCLK_S)
#define USB_STOPPCLK_V  0x00000001
#define USB_STOPPCLK_S  0
/** USB_GATEHCLK:R/W；位位置：[1]；默认值：0；gate hclk 0x0：当USB恢复或新会话开始时清除此位0x1：当暂停USB或会话无效时，将此位设置为将hclk选通到模块
 */
#define USB_GATEHCLK    (BIT(1))
#define USB_GATEHCLK_M  (USB_GATEHCLK_V << USB_GATEHCLK_S)
#define USB_GATEHCLK_V  0x00000001
#define USB_GATEHCLK_S  1
/** USB_pwrcmp:R/W；位位置：[2]；默认值：0；0x0：在电源打开之前清除此位以禁用箝位0x1：仅在部分断电模式下，设置此位以在电源关闭之前箝位通电模块和断电模块之间的信号
 */
#define USB_PWRCLMP    (BIT(2))
#define USB_PWRCLMP_M  (USB_PWRCLMP_V << USB_PWRCLMP_S)
#define USB_PWRCLMP_V  0x00000001
#define USB_PWRCLMP_S  2
/** USB_RSTPDWNMODULE：R/W；位位置：[3]；默认值：0；重置掉电模块。0x0：电源打开0x1：电源关闭
 */
#define USB_RSTPDWNMODULE    (BIT(3))
#define USB_RSTPDWNMODULE_M  (USB_RSTPDWNMODULE_V << USB_RSTPDWNMODULE_S)
#define USB_RSTPDWNMODULE_V  0x00000001
#define USB_RSTPDWNMODULE_S  3
/** USB_PHYSLEEP:RO；位位置：[6]；默认值：0；0x0:Phy未处于睡眠状态0x1:Phy处于睡眠状态
 */
#define USB_PHYSLEEP    (BIT(6))
#define USB_PHYSLEEP_M  (USB_PHYSLEEP_V << USB_PHYSLEEP_S)
#define USB_PHYSLEEP_V  0x00000001
#define USB_PHYSLEEP_S  6
/** USB_l1暂停：RO；位位置：[7]；默认值：0；L1深度睡眠0x0：非深度睡眠0x1：深度睡眠
 */
#define USB_L1SUSPENDED    (BIT(7))
#define USB_L1SUSPENDED_M  (USB_L1SUSPENDED_V << USB_L1SUSPENDED_S)
#define USB_L1SUSPENDED_V  0x00000001
#define USB_L1SUSPENDED_S  7
/** USB_resetafersust:R/W；位位置：[8]；默认值：0；挂起后重置0x0：在仅主机模式下，主机发出挂起后恢复0x1：在只主机模式中，如果主机需要发出挂起之后重置，则主机在移除箝位之前设置此位
 */
#define USB_RESETAFTERSUSP    (BIT(8))
#define USB_RESETAFTERSUSP_M  (USB_RESETAFTERSUSP_V << USB_RESETAFTERSUSP_S)
#define USB_RESETAFTERSUSP_V  0x00000001
#define USB_RESETAFTERSUSP_S  8




/**中断寄存器*/
/** USB_GOTGINT_REG寄存器OTG中断寄存器
 */
#define USB_GOTGINT_REG (SOC_DPORT_USB_BASE + 0x4)
/** USB_SESENDDET:R/W1C；位位置：[2]；默认值：0；检测到会话结束。当utmiotg_valid信号无效时，控制器设置该位。此位只能由内核设置，应用程序应写入1以清除它
 */
#define USB_SESENDDET    (BIT(2))
#define USB_SESENDDET_M  (USB_SESENDDET_V << USB_SESENDDET_S)
#define USB_SESENDDET_V  0x00000001
#define USB_SESENDDET_S  2
/** USB_SESREQSUCSTSCHNG:R/W1C；位位置：[8]；默认值：0；会话请求成功状态更改。核心在会话请求的成功或失败时设置此位。应用程序必须读取OTG控制和状态寄存器（GOTGCTL_REG.USB_SESREQSCS）中的会话请求成功位，以检查是否成功或失败。这个位只能由内核设置，应用程序应该写1来清除它。
 */
#define USB_SESREQSUCSTSCHNG    (BIT(8))
#define USB_SESREQSUCSTSCHNG_M  (USB_SESREQSUCSTSCHNG_V << USB_SESREQSUCSTSCHNG_S)
#define USB_SESREQSUCSTSCHNG_V  0x00000001
#define USB_SESREQSUCSTSCHNG_S  8
/** USB_HSTNEGSUCSTSCHNG:R/W1C；位位置：[9]；默认值：0；主机协商成功状态更改。核心在USB主机协商请求成功或失败时设置此位。应用程序必须读取OTG控制和状态寄存器（GOTGCTL_REG.USB_HSTNEGSCS）的主机协商成功位，以检查是否成功或失败。此位只能由内核设置，应用程序应写入1以清除它
 */
#define USB_HSTNEGSUCSTSCHNG    (BIT(9))
#define USB_HSTNEGSUCSTSCHNG_M  (USB_HSTNEGSUCSTSCHNG_V << USB_HSTNEGSUCSTSCHNG_S)
#define USB_HSTNEGSUCSTSCHNG_V  0x00000001
#define USB_HSTNEGSUCSTSCHNG_S  9
/** USB_HSTNEGDET:R/W1C；位位置：[17]；默认值：0；检测到主机协商。核心在检测到USB上的主机协商请求时设置此位。这个位只能由内核设置，应用程序应该写1来清除它。
 */
#define USB_HSTNEGDET    (BIT(17))
#define USB_HSTNEGDET_M  (USB_HSTNEGDET_V << USB_HSTNEGDET_S)
#define USB_HSTNEGDET_V  0x00000001
#define USB_HSTNEGDET_S  17
/** USB_adevtouthg:R/W1C；位位置：[18]；默认值：0；A设备超时更改。核心设置此位以指示A设备在等待B设备连接时超时。此位只能由内核设置，应用程序应写入1以清除它
 */
#define USB_ADEVTOUTCHG    (BIT(18))
#define USB_ADEVTOUTCHG_M  (USB_ADEVTOUTCHG_V << USB_ADEVTOUTCHG_S)
#define USB_ADEVTOUTCHG_V  0x00000001
#define USB_ADEVTOUTCHG_S  18
/** USB_dbancedone:R/W1C；位位置：[19]；默认值：0；取消反弹完成。当设备连接后完成反跳时，内核设置该位。应用程序可以在看到此中断后开始驱动USB重置。仅当核心USB配置寄存器（分别为GUSBCFG.HNPCap或GUSBCFG.SRPCap）中设置了支持HNP或支持SRP的位时，该位才有效。此位只能由内核设置，应用程序应写入1以清除它
 */
#define USB_DBNCEDONE    (BIT(19))
#define USB_DBNCEDONE_M  (USB_DBNCEDONE_V << USB_DBNCEDONE_S)
#define USB_DBNCEDONE_V  0x00000001
#define USB_DBNCEDONE_S  19


/** USB_GINTSTS_REG寄存器中断寄存器
 */
#define USB_GINTSTS_REG (SOC_DPORT_USB_BASE + 0x14)
/** USB_CURMOD_INT:RO；位位置：[0]；默认值：0；当前操作模式1’b0：设备模式1’b1：主机模式
 */
#define USB_CURMOD_INT    (BIT(0))
#define USB_CURMOD_INT_M  (USB_CURMOD_INT_V << USB_CURMOD_INT_S)
#define USB_CURMOD_INT_V  0x00000001
#define USB_CURMOD_INT_S  0
/** USB_MODEMIS：R/W1C；位位置：[1]；默认值：0；模式不匹配中断。当控制器在设备模式下运行时，内核在应用程序试图访问：主机模式寄存器时设置此位
 */
#define USB_MODEMIS    (BIT(1))
#define USB_MODEMIS_M  (USB_MODEMIS_V << USB_MODEMIS_S)
#define USB_MODEMIS_V  0x00000001
#define USB_MODEMIS_S  1
/** USB_OTGINT:RO；位位置：[2]；默认值：0；OTG中断。控制器设置此位以指示OTG协议事件。应用程序必须读取OTG中断状态（GOTGINT_REG）寄存器，以确定导致此中断的确切事件。应用程序必须清除GOTGINT_REG寄存器中的相应状态位才能清除此位。
 */
#define USB_OTGINT    (BIT(2))
#define USB_OTGINT_M  (USB_OTGINT_V << USB_OTGINT_S)
#define USB_OTGINT_V  0x00000001
#define USB_OTGINT_S  2
/** USB_SOF:R/W1C；位位置：[3]；默认值：0；（micro）帧（Sof）的开始在主机模式下，内核设置此位以指示Sof（FS）、micro Sof（HS）或Keep Alive（LS）在USB上传输。应用程序必须向该位写入1以清除中断。在设备模式下，控制器设置该位以指示已在USB上接收到SOF令牌。应用程序可以读取设备状态寄存器以获取当前（微）帧号。只有当内核在HS或FS下运行时，才会看到此中断。此位只能由内核设置，应用程序必须写入1才能清除它
 */
#define USB_SOF    (BIT(3))
#define USB_SOF_M  (USB_SOF_V << USB_SOF_S)
#define USB_SOF_V  0x00000001
#define USB_SOF_S  3
/** USB_rxvlvi:RO；位位置：[4]；默认值：0；RxFIFO非空。表示至少有一个数据包等待从RxFIFO 1’b0:Rx Fifo为空1’b1：Rx Fivo不为空
 */
#define USB_RXFLVI    (BIT(4))
#define USB_RXFLVI_M  (USB_RXFLVI_V << USB_RXFLVI_S)
#define USB_RXFLVI_V  0x00000001
#define USB_RXFLVI_S  4
/** USB_NPTXFEMP:RO；位位置：[5]；默认值：0；非周期性TxFIFO为空。当非周期性TxFIFO为一半或完全为空，并且有空间将至少一个条目写入非周期性传输请求队列时，会断言此中断。半空或完全空状态由核心AHB配置寄存器（GAHBCFG_REG.USB_NPTXFEMPLVL）中的非周期TxFIFO空电平位确定。
 */
#define USB_NPTXFEMP    (BIT(5))
#define USB_NPTXFEMP_M  (USB_NPTXFEMP_V << USB_NPTXFEMP_S)
#define USB_NPTXFEMP_V  0x00000001
#define USB_NPTXFEMP_S  5
/** USB_GINNAKEFF:RO；位位置：[6]；默认值：0；仅限设备。全局IN非周期性NAK有效。表示应用程序设置的设备控制寄存器（DCTL.SGPINNak）中的设置全局非周期性IN NAK位已在核心中生效。也就是说，内核已经对应用程序的全局IN NAK位集进行了采样。可以通过清除设备控制寄存器（DCTL.CGNPNNak）中的清除全局非周期性IN NAK位来清除此位。此中断不一定意味着在USB上发送NAK握手。STALL位优先于NAK位。
 */
#define USB_GINNAKEFF    (BIT(6))
#define USB_GINNAKEFF_M  (USB_GINNAKEFF_V << USB_GINNAKEFF_S)
#define USB_GINNAKEFF_V  0x00000001
#define USB_GINNAKEFF_S  6
/** USB_GOUTNAKEFF:RO；位位置：[7]；默认值：0；仅限设备。全局OUT NAK有效。表示由应用程序设置的设备控制寄存器（DCTL_REG.USB_SGOUTNAK）中的Set Global OUT NAK位已在内核中生效。通过将清除全局输出NAK位写入设备控制寄存器（DCTL_REG.REG_CGOUTNAK），可以清除该位。
 */
#define USB_GOUTNAKEFF    (BIT(7))
#define USB_GOUTNAKEFF_M  (USB_GOUTNAKEFF_V << USB_GOUTNAKEFF_S)
#define USB_GOUTNAKEFF_V  0x00000001
#define USB_GOUTNAKEFF_S  7
/** USB_ERLYSUSP:R/W1C；位位置：[10]；默认值：0；仅限设备。早期挂起。控制器设置此位以指示USB上已检测到空闲状态3毫秒。
 */
#define USB_ERLYSUSP    (BIT(10))
#define USB_ERLYSUSP_M  (USB_ERLYSUSP_V << USB_ERLYSUSP_S)
#define USB_ERLYSUSP_V  0x00000001
#define USB_ERLYSUSP_S  10
/** USB_USBSUSP:R/W1C；位位置：[11]；默认值：0；仅设备.USB挂起。控制器设置此位以指示在USB上检测到挂起。当线路状态信号在延长的时间段内没有活动时，控制器进入暂停状态。
 */
#define USB_USBSUSP    (BIT(11))
#define USB_USBSUSP_M  (USB_USBSUSP_V << USB_USBSUSP_S)
#define USB_USBSUSP_V  0x00000001
#define USB_USBSUSP_S  11
/** USB_USBRST:R/W1C；位位置：[12]；默认值：0；仅限设备USB重置。控制器设置此位以指示在USB上检测到重置
 */
#define USB_USBRST    (BIT(12))
#define USB_USBRST_M  (USB_USBRST_V << USB_USBRST_S)
#define USB_USBRST_V  0x00000001
#define USB_USBRST_S  12
/** USB_ENUMDONE:R/W1C；位位置：[13]；默认值：0；仅设备。枚举完成。核心设置此位以指示速度枚举完成。应用程序必须读取设备状态（DSTS_REG）寄存器以获得枚举速度。
 */
#define USB_ENUMDONE    (BIT(13))
#define USB_ENUMDONE_M  (USB_ENUMDONE_V << USB_ENUMDONE_S)
#define USB_ENUMDONE_V  0x00000001
#define USB_ENUMDONE_S  13
/** USB_ISOOUTDROP:R/W1C；位位置：[14]；默认值：0；仅限设备。等时OUT数据包丢弃中断。当控制器无法将等时OUT包写入RxFIFO时，控制器会设置此位，因为RxFIFO没有足够的空间来容纳等时OUT端点的最大数据包大小。
 */
#define USB_ISOOUTDROP    (BIT(14))
#define USB_ISOOUTDROP_M  (USB_ISOOUTDROP_V << USB_ISOOUTDROP_S)
#define USB_ISOOUTDROP_V  0x00000001
#define USB_ISOOUTDROP_S  14
/** USB_EOPF:R/W1C；位位置：[15]；默认值：0；仅限设备。周期帧中断结束。表示在当前微帧中已达到设备配置寄存器（DCFG_REG.REG_PERFRINT）的周期帧间隔字段中指定的周期。
 */
#define USB_EOPF    (BIT(15))
#define USB_EOPF_M  (USB_EOPF_V << USB_EOPF_S)
#define USB_EOPF_V  0x00000001
#define USB_EOPF_S  15
/** USB_EPMIS：R/W1C；位位置：[17]；默认值：0；仅限设备。端点不匹配中断。此中断仅在共享FIFO操作中有效。表示已收到非周期性端点的IN令牌，但另一个端点的数据位于非周期性传输FIFO的顶部，并且应用程序编程的IN端点不匹配计数已过期。
 */
#define USB_EPMIS    (BIT(17))
#define USB_EPMIS_M  (USB_EPMIS_V << USB_EPMIS_S)
#define USB_EPMIS_V  0x00000001
#define USB_EPMIS_S  17
/** USB_IEPINT:RO；位位置：[18]；默认值：0；仅限设备。IN端点中断。核心设置此位以指示在核心的一个IN端点上有一个中断挂起（处于设备模式）。应用程序必须读取设备所有端点中断（DAINT）寄存器，以确定设备IN端点n中断（DIEPINTn）寄存器上IN端点的确切数量，以确定中断的确切原因。应用程序必须清除相应DIEPINTn寄存器中的相应状态位才能清除该位。
 */
#define USB_IEPINT    (BIT(18))
#define USB_IEPINT_M  (USB_IEPINT_V << USB_IEPINT_S)
#define USB_IEPINT_V  0x00000001
#define USB_IEPINT_S  18
/** USB_OEPINT:RO；位位置：[19]；默认值：0；仅限设备。OUT端点中断。控制器设置该位，以指示在核心的OUT端点之一（在设备模式下）上有中断挂起。应用程序必须读取设备所有端点中断（DAINT）寄存器，以确定发生中断的OUT端点的确切数量，然后读取相应的设备OUT端点-n中断（DOEPINTn）寄存器，确定中断的确切原因。应用程序必须清除相应DOEPINTn寄存器中的相应状态位才能清除此位。
 */
#define USB_OEPINT    (BIT(19))
#define USB_OEPINT_M  (USB_OEPINT_V << USB_OEPINT_S)
#define USB_OEPINT_V  0x00000001
#define USB_OEPINT_S  19
/** USB_impisoin:R/W1C；位位置：[20]；默认值：0；仅限设备。不完全同步IN传输。核心设置此中断以指示在当前微帧中至少有一个同步IN端点上未完成传输。该中断与该寄存器中的周期性帧中断结束（EOPF）位一起被断言。
 */
#define USB_INCOMPISOIN    (BIT(20))
#define USB_INCOMPISOIN_M  (USB_INCOMPISOIN_V << USB_INCOMPISOIN_S)
#define USB_INCOMPISOIN_V  0x00000001
#define USB_INCOMPISOIN_S  20
/** USB_uncip:R/W1C；位位置：[21]；默认值：0；在主机模式下，当有不完整的周期性事务仍在等待处理时，内核会设置此中断位，这些事务是为当前微帧调度的。在设备模式下，内核设置此中断以指示在当前微帧中至少有一个未完成传输的等时OUT端点。该中断与该寄存器中的周期性帧中断结束（EOPF）位一起被断言。
 */
#define USB_INCOMPIP    (BIT(21))
#define USB_INCOMPIP_M  (USB_INCOMPIP_V << USB_INCOMPIP_S)
#define USB_INCOMPIP_V  0x00000001
#define USB_INCOMPIP_S  21
/** USB_fetsup:R/W1C；位位置：[22]；默认值：0；仅限设备。数据获取已挂起。此中断仅在DMA模式下有效。此中断表示内核已停止获取数据。对于IN端点，由于TxFIFO空间或请求队列空间不可用。此中断由应用程序用于端点不匹配算法
 */
#define USB_FETSUSP    (BIT(22))
#define USB_FETSUSP_M  (USB_FETSUSP_V << USB_FETSUSP_S)
#define USB_FETSUSP_V  0x00000001
#define USB_FETSUSP_S  22
/** USB_RESETDET:R/W1C；位位置：[23]；默认值：0；重置检测到的中断在设备模式下，当在部分断电模式下USB上检测到重置时，该中断被断言，当设备处于主机模式下的挂起时，不会断言该中断
 */
#define USB_RESETDET    (BIT(23))
#define USB_RESETDET_M  (USB_RESETDET_V << USB_RESETDET_S)
#define USB_RESETDET_V  0x00000001
#define USB_RESETDET_S  23
/** USB_PRTLNT:RO；位位置：[24]；默认值：0；仅限主机。主机端口中断。内核设置此位以指示主机模式下控制器端口之一的端口状态发生变化。应用程序必须读取主机端口控制和状态（HPRT）寄存器，以确定导致此中断的确切事件。应用程序必须清除主机端口控制和状态寄存器中的相应状态位才能清除此位。
 */
#define USB_PRTLNT    (BIT(24))
#define USB_PRTLNT_M  (USB_PRTLNT_V << USB_PRTLNT_S)
#define USB_PRTLNT_V  0x00000001
#define USB_PRTLNT_S  24
/** USB_HCHLNT:RO；位位置：[25]；默认值：0；仅限主机。主机通道中断。内核设置此位以指示内核的一个通道上有一个中断挂起（在主机模式下）。应用程序必须读取主机所有通道中断（HAINT）寄存器，以确定发生中断的通道的确切数量，然后读取相应的主机通道n中断（HCINTn）寄存器，确定中断的确切原因。应用程序必须清除HCINTn寄存器中的相应状态位才能清除此位。
 */
#define USB_HCHLNT    (BIT(25))
#define USB_HCHLNT_M  (USB_HCHLNT_V << USB_HCHLNT_S)
#define USB_HCHLNT_V  0x00000001
#define USB_HCHLNT_S  25
/** USB_PTXFEMP:RO；位位置：[26]；默认值：0；仅限主机。定期TxFIFO清空。当周期性传输FIFO为半空或完全空，并且周期性请求队列中至少有一个条目需要写入时，该中断被断言。半空或完全空状态由核心AHB配置寄存器（GAHBCFG.PTxFEmpLvl）中的周期性TxFIFO空电平位确定
 */
#define USB_PTXFEMP    (BIT(26))
#define USB_PTXFEMP_M  (USB_PTXFEMP_V << USB_PTXFEMP_S)
#define USB_PTXFEMP_V  0x00000001
#define USB_PTXFEMP_S  26
/** USB_conidschng:R/W1C；位位置：[28]；默认值：0；连接器ID状态更改1’b0:未激活1’b1：连接器ID状态改变
 */
#define USB_CONIDSTSCHNG    (BIT(28))
#define USB_CONIDSTSCHNG_M  (USB_CONIDSTSCHNG_V << USB_CONIDSTSCHNG_S)
#define USB_CONIDSTSCHNG_V  0x00000001
#define USB_CONIDSTSCHNG_S  28
/** USB_disconnent:R/W1C；位位置：[29]；默认值：0；断开检测到的中断1’b0：未激活1’b1：断开检测的中断
 */
#define USB_DISCONNINT    (BIT(29))
#define USB_DISCONNINT_M  (USB_DISCONNINT_V << USB_DISCONNINT_S)
#define USB_DISCONNINT_V  0x00000001
#define USB_DISCONNINT_S  29
/** USB_sessrreqint：R/W1C；位位置：[30]；默认值：0；1’b0:未激活1’b1：检测到会话请求新会话
 */
#define USB_SESSREQINT    (BIT(30))
#define USB_SESSREQINT_M  (USB_SESSREQINT_V << USB_SESSREQINT_S)
#define USB_SESSREQINT_V  0x00000001
#define USB_SESSREQINT_S  30
/** USB_WKUPINT：R/W1C；位位置：[31]；默认值：0；恢复/远程唤醒检测到中断1’b0：未激活1’b1：恢复或远程唤醒检测中断
 */
#define USB_WKUPINT    (BIT(31))
#define USB_WKUPINT_M  (USB_WKUPINT_V << USB_WKUPINT_S)
#define USB_WKUPINT_V  0x00000001
#define USB_WKUPINT_S  31


/** USB_GINTMSK_REG寄存器中断掩码寄存器
 */
#define USB_GINTMSK_REG (SOC_DPORT_USB_BASE + 0x18)
/** USB_MODEMISMSK:R/W；位位置：[1]；默认值：0；1’b0：模式不匹配中断掩码1’b1：无模式不匹配的中断掩码
 */
#define USB_MODEMISMSK    (BIT(1))
#define USB_MODEMISMSK_M  (USB_MODEMISMSK_V << USB_MODEMISMSK_S)
#define USB_MODEMISMSK_V  0x00000001
#define USB_MODEMISMSK_S  1
/** USB_OTGINTMSK:R/W；位位置：[2]；默认值：0；1’b0：OTG中断掩码1’b1：无OTG中断屏蔽
 */
#define USB_OTGINTMSK    (BIT(2))
#define USB_OTGINTMSK_M  (USB_OTGINTMSK_V << USB_OTGINTMSK_S)
#define USB_OTGINTMSK_V  0x00000001
#define USB_OTGINTMSK_S  2
/** USB_SOFMSK:R/W；位位置：[3]；默认值：0；1’b0：（微）帧掩码的开始1’b1：无（微）框掩码的开始
 */
#define USB_SOFMSK    (BIT(3))
#define USB_SOFMSK_M  (USB_SOFMSK_V << USB_SOFMSK_S)
#define USB_SOFMSK_V  0x00000001
#define USB_SOFMSK_S  3
/** USB_rxfxlvimsk:R/W；位位置：[4]；默认值：0；1’b0：接收FIFO非空掩码1’b1：无接收FIFO非空白掩码
 */
#define USB_RXFLVIMSK    (BIT(4))
#define USB_RXFLVIMSK_M  (USB_RXFLVIMSK_V << USB_RXFLVIMSK_S)
#define USB_RXFLVIMSK_V  0x00000001
#define USB_RXFLVIMSK_S  4
/** USB_NPTXFEMPMSK:R/W；位位置：[5]；默认值：0；1’b0：非周期性TxFIFO空掩码1’b1：无非周期性TxFIFO空掩码
 */
#define USB_NPTXFEMPMSK    (BIT(5))
#define USB_NPTXFEMPMSK_M  (USB_NPTXFEMPMSK_V << USB_NPTXFEMPMSK_S)
#define USB_NPTXFEMPMSK_V  0x00000001
#define USB_NPTXFEMPMSK_S  5
/** USB_GINNAKEFFMSK:R/W；位位置：[6]；默认值：0；1’b0：全局非周期性IN NAK有效掩码1’b1：无全局非周期IN NAK无效掩码
 */
#define USB_GINNAKEFFMSK    (BIT(6))
#define USB_GINNAKEFFMSK_M  (USB_GINNAKEFFMSK_V << USB_GINNAKEFFMSK_S)
#define USB_GINNAKEFFMSK_V  0x00000001
#define USB_GINNAKEFFMSK_S  6
/** USB_GOUTNACKEFFMSK:R/W；位位置：[7]；默认值：0；1’b0：全局OUT NAK有效面罩1’b1：无全局OUT NAK有效面罩
 */
#define USB_GOUTNACKEFFMSK    (BIT(7))
#define USB_GOUTNACKEFFMSK_M  (USB_GOUTNACKEFFMSK_V << USB_GOUTNACKEFFMSK_S)
#define USB_GOUTNACKEFFMSK_V  0x00000001
#define USB_GOUTNACKEFFMSK_S  7
/** USB_ERLYSUSPMSK:R/W；位位置：[10]；默认值：0；1’b0：早期挂起掩码1’b1：无早期挂起遮罩
 */
#define USB_ERLYSUSPMSK    (BIT(10))
#define USB_ERLYSUSPMSK_M  (USB_ERLYSUSPMSK_V << USB_ERLYSUSPMSK_S)
#define USB_ERLYSUSPMSK_V  0x00000001
#define USB_ERLYSUSPMSK_S  10
/** USB_USBSUSPMSK：R/W；位位置：[11]；默认值：0；1’b0:USB挂起掩码1’b1：无USB挂起屏蔽
 */
#define USB_USBSUSPMSK    (BIT(11))
#define USB_USBSUSPMSK_M  (USB_USBSUSPMSK_V << USB_USBSUSPMSK_S)
#define USB_USBSUSPMSK_V  0x00000001
#define USB_USBSUSPMSK_S  11
/** USB_USBRSTMSK:R/W；位位置：[12]；默认值：0；1’b0：USB重置掩码1’b1：无USB重置掩码
 */
#define USB_USBRSTMSK    (BIT(12))
#define USB_USBRSTMSK_M  (USB_USBRSTMSK_V << USB_USBRSTMSK_S)
#define USB_USBRSTMSK_V  0x00000001
#define USB_USBRSTMSK_S  12
/** USB_ENUMDONEMSK:R/W；位位置：[13]；默认值：0；1'b0:枚举完成掩码1'b1:没有枚举完成掩码
 */
#define USB_ENUMDONEMSK    (BIT(13))
#define USB_ENUMDONEMSK_M  (USB_ENUMDONEMSK_V << USB_ENUMDONEMSK_S)
#define USB_ENUMDONEMSK_V  0x00000001
#define USB_ENUMDONEMSK_S  13
/** USB_ISOOUTDROPMSK:R/W；位位置：[14]；默认值：0；1’b0：等时OUT数据包丢弃中断掩码1’b1：无等时OUT分组丢弃中断掩码
 */
#define USB_ISOOUTDROPMSK    (BIT(14))
#define USB_ISOOUTDROPMSK_M  (USB_ISOOUTDROPMSK_V << USB_ISOOUTDROPMSK_S)
#define USB_ISOOUTDROPMSK_V  0x00000001
#define USB_ISOOUTDROPMSK_S  14
/** USB_EOPFMSK:R/W；位位置：[15]；默认值：0；1’b0：周期帧中断掩码结束1’b1：周期帧无中断掩码结束
 */
#define USB_EOPFMSK    (BIT(15))
#define USB_EOPFMSK_M  (USB_EOPFMSK_V << USB_EOPFMSK_S)
#define USB_EOPFMSK_V  0x00000001
#define USB_EOPFMSK_S  15
/** USB_EPMISMSK:R/W；位位置：[17]；默认值：0；1’b0：端点不匹配中断掩码1’b1：无端点不匹配的中断掩码
 */
#define USB_EPMISMSK    (BIT(17))
#define USB_EPMISMSK_M  (USB_EPMISMSK_V << USB_EPMISMSK_S)
#define USB_EPMISMSK_V  0x00000001
#define USB_EPMISMSK_S  17
/** USB_IEPINTMSK:R/W；位位置：[18]；默认值：0；1'b0:IN端点中断掩码1'b1：无IN端点中断屏蔽
 */
#define USB_IEPINTMSK    (BIT(18))
#define USB_IEPINTMSK_M  (USB_IEPINTMSK_V << USB_IEPINTMSK_S)
#define USB_IEPINTMSK_V  0x00000001
#define USB_IEPINTMSK_S  18
/** USB_OEPINTMSK:R/W；位位置：[19]；默认值：0；1'b0:OUT端点中断掩码1'b1：无OUT端点中断屏蔽
 */
#define USB_OEPINTMSK    (BIT(19))
#define USB_OEPINTMSK_M  (USB_OEPINTMSK_V << USB_OEPINTMSK_S)
#define USB_OEPINTMSK_V  0x00000001
#define USB_OEPINTMSK_S  19
/** USB_不兼容掩码：R/W；位位置：[20]；默认值：0；1’b0：不完全等时IN传输掩码1’b1：无不完全等时间IN传输掩码
 */
#define USB_INCOMPISOINMSK    (BIT(20))
#define USB_INCOMPISOINMSK_M  (USB_INCOMPISOINMSK_V << USB_INCOMPISOINMSK_S)
#define USB_INCOMPISOINMSK_V  0x00000001
#define USB_INCOMPISOINMSK_S  20
/** USB_uncipmsk:R/W；位位置：[21]；默认值：0；1’b0：主机模式：不完整周期传输掩码设备模式：不完全等时OUT传输掩码1’b1：主机模式，无不完整周期转移掩码设备模式，无完整等时OUT转移掩码
 */
#define USB_INCOMPIPMSK    (BIT(21))
#define USB_INCOMPIPMSK_M  (USB_INCOMPIPMSK_V << USB_INCOMPIPMSK_S)
#define USB_INCOMPIPMSK_V  0x00000001
#define USB_INCOMPIPMSK_S  21
/** USB_fetsumsk：R/W；位位置：[22]；默认值：0；1’b0：数据获取挂起掩码1’b1：无数据获取挂挂掩码
 */
#define USB_FETSUSPMSK    (BIT(22))
#define USB_FETSUSPMSK_M  (USB_FETSUSPMSK_V << USB_FETSUSPMSK_S)
#define USB_FETSUSPMSK_V  0x00000001
#define USB_FETSUSPMSK_S  22
/** USB_RESETDETMSK:R/W；位位置：[23]；默认值：0；1’b0：重置检测到的中断掩码1’b1：没有重置检测到中断掩码
 */
#define USB_RESETDETMSK    (BIT(23))
#define USB_RESETDETMSK_M  (USB_RESETDETMSK_V << USB_RESETDETMSK_S)
#define USB_RESETDETMSK_V  0x00000001
#define USB_RESETDETMSK_S  23
/** USB_PRTLNTMSK:R/W；位位置：[24]；默认值：0；1’b0：主机端口中断掩码1’b1：无主机端口中断屏蔽
 */
#define USB_PRTLNTMSK    (BIT(24))
#define USB_PRTLNTMSK_M  (USB_PRTLNTMSK_V << USB_PRTLNTMSK_S)
#define USB_PRTLNTMSK_V  0x00000001
#define USB_PRTLNTMSK_S  24
/** USB_HCHINTMSK：R/W；位位置：[25]；默认值：0；1’b0：主机通道中断掩码1’b1：无主机通道中断屏蔽
 */
#define USB_HCHINTMSK    (BIT(25))
#define USB_HCHINTMSK_M  (USB_HCHINTMSK_V << USB_HCHINTMSK_S)
#define USB_HCHINTMSK_V  0x00000001
#define USB_HCHINTMSK_S  25
/** USB_PTXFEMPMSK:R/W；位位置：[26]；默认值：0；1’b0：定期TxFIFO空掩码1’b1：无定期TxFIFO空白掩码
 */
#define USB_PTXFEMPMSK    (BIT(26))
#define USB_PTXFEMPMSK_M  (USB_PTXFEMPMSK_V << USB_PTXFEMPMSK_S)
#define USB_PTXFEMPMSK_V  0x00000001
#define USB_PTXFEMPMSK_S  26
/** USB_conidschngmsk:R/W；位位置：[28]；默认值：0；1’b0：连接器ID状态更改掩码1’b1：无连接器ID状态改变掩码
 */
#define USB_CONIDSTSCHNGMSK    (BIT(28))
#define USB_CONIDSTSCHNGMSK_M  (USB_CONIDSTSCHNGMSK_V << USB_CONIDSTSCHNGMSK_S)
#define USB_CONIDSTSCHNGMSK_V  0x00000001
#define USB_CONIDSTSCHNGMSK_S  28
/** USB_disconintmsk:R/W；位位置：[29]；默认值：0；1’b0：断开检测到的中断掩码1’b1：未检测到断开连接中断掩码
 */
#define USB_DISCONNINTMSK    (BIT(29))
#define USB_DISCONNINTMSK_M  (USB_DISCONNINTMSK_V << USB_DISCONNINTMSK_S)
#define USB_DISCONNINTMSK_V  0x00000001
#define USB_DISCONNINTMSK_S  29
/** USB_sessrreqintmsk:R/W；位位置：[30]；默认值：0；1’b0：会话请求或检测到新会话中断掩码1’b1：无会话请求或新会话检测到中断掩码
 */
#define USB_SESSREQINTMSK    (BIT(30))
#define USB_SESSREQINTMSK_M  (USB_SESSREQINTMSK_V << USB_SESSREQINTMSK_S)
#define USB_SESSREQINTMSK_V  0x00000001
#define USB_SESSREQINTMSK_S  30
/** USB_WKUPINTMSK:R/W；位位置：[31]；默认值：0；1’b0：恢复或远程唤醒检测到的中断掩码1’b1：取消掩码恢复远程唤醒检测的中断
 */
#define USB_WKUPINTMSK    (BIT(31))
#define USB_WKUPINTMSK_M  (USB_WKUPINTMSK_V << USB_WKUPINTMSK_S)
#define USB_WKUPINTMSK_V  0x00000001
#define USB_WKUPINTMSK_S  31


/** USB_HAINT_REG寄存器主机所有通道中断寄存器
 */
#define USB_HAINT_REG (SOC_DPORT_USB_BASE + 0x414)
/** USB_HAINT:RO；位位置：[8:0]；默认值：0；通道号的通道中断。
 */
#define USB_HAINT    0x000000FF
#define USB_HAINT_M  (USB_HAINT_V << USB_HAINT_S)
#define USB_HAINT_V  0x000000FF
#define USB_HAINT_S  0


/** USB_HAINTMSK_REG寄存器主机所有通道中断掩码寄存器
 */
#define USB_HAINTMSK_REG (SOC_DPORT_USB_BASE + 0x418)
/** USB_HAINTMSK:R/W；位位置：[8:0]；默认值：0；通道中断掩码（HAINTMSK_REG）每个通道一位：通道0的位0，通道15的位15。
 */
#define USB_HAINTMSK    0x000000FF
#define USB_HAINTMSK_M  (USB_HAINTMSK_V << USB_HAINTMSK_S)
#define USB_HAINTMSK_V  0x000000FF
#define USB_HAINTMSK_S  0


/** USB_HCINT0_REG寄存器主机通道0中断寄存器
 */
#define USB_HCINT0_REG (SOC_DPORT_USB_BASE + 0x508)
/** USB_H_xfercomple0:R/W1C；位位置：[0]；默认值：0；1’b0：正在传输或无活动传输1’b1：传输正常完成，无任何错误
 */
#define USB_H_XFERCOMPL0    (BIT(0))
#define USB_H_XFERCOMPL0_M  (USB_H_XFERCOMPL0_V << USB_H_XFERCOMPL0_S)
#define USB_H_XFERCOMPL0_V  0x00000001
#define USB_H_XFERCOMPL0_S  0
/** USB_H_chltd0:R/W1C；位位置：[1]；默认值：0；1’b0：频道未停止1’b1：频道已停止
 */
#define USB_H_CHHLTD0    (BIT(1))
#define USB_H_CHHLTD0_M  (USB_H_CHHLTD0_V << USB_H_CHHLTD0_S)
#define USB_H_CHHLTD0_V  0x00000001
#define USB_H_CHHLTD0_S  1
/** USB_H_ahber0:R/W1C；位位置：[2]；默认值：0；1’b0：无AHB错误1’b1：AHB读/写期间发生AHB错误
 */
#define USB_H_AHBERR0    (BIT(2))
#define USB_H_AHBERR0_M  (USB_H_AHBERR0_V << USB_H_AHBERR0_S)
#define USB_H_AHBERR0_V  0x00000001
#define USB_H_AHBERR0_S  2
/** USB_H_安装0：R/W1C；位位置：[3]；默认值：0；1’b0：未收到暂停响应中断1’b1：收到暂停响应
 */
#define USB_H_STALL0    (BIT(3))
#define USB_H_STALL0_M  (USB_H_STALL0_V << USB_H_STALL0_S)
#define USB_H_STALL0_V  0x00000001
#define USB_H_STALL0_S  3
/** USB_H_nak0:R/W1C；位位置：[4]；默认值：0；1’b0：未收到NAK响应中断1’b1：收到NAK应答中断
 */
#define USB_H_NACK0    (BIT(4))
#define USB_H_NACK0_M  (USB_H_NACK0_V << USB_H_NACK0_S)
#define USB_H_NACK0_V  0x00000001
#define USB_H_NACK0_S  4
/** USB_H_ACK0:R/W1C；位位置：[5]；默认值：0；1’b0：未收到或发送ACK响应中断1’b1：收到或发送的ACK响应中断
 */
#define USB_H_ACK0    (BIT(5))
#define USB_H_ACK0_M  (USB_H_ACK0_V << USB_H_ACK0_S)
#define USB_H_ACK0_V  0x00000001
#define USB_H_ACK0_S  5
/** USB_H_NYET0:R/W1C；位位置：[6]；默认值：0；1’b0：未收到NYET响应中断1’b1：收到NYET应答中断
 */
#define USB_H_NYET0    (BIT(6))
#define USB_H_NYET0_M  (USB_H_NYET0_V << USB_H_NYET0_S)
#define USB_H_NYET0_V  0x00000001
#define USB_H_NYET0_S  6
/** USB_H_xacter0:R/W1C；位位置：[7]；默认值：0；指示USB上发生以下错误之一：CRC检查失败超时位填充错误错误错误EOP
 */
#define USB_H_XACTERR0    (BIT(7))
#define USB_H_XACTERR0_M  (USB_H_XACTERR0_V << USB_H_XACTERR0_S)
#define USB_H_XACTERR0_V  0x00000001
#define USB_H_XACTERR0_S  7
/** USB_H_bbblerr0:R/W1C；位位置：[8]；默认值：0；1’b0：无巴贝尔错误1’b1：巴贝尔错误
 */
#define USB_H_BBLERR0    (BIT(8))
#define USB_H_BBLERR0_M  (USB_H_BBLERR0_V << USB_H_BBLERR0_S)
#define USB_H_BBLERR0_V  0x00000001
#define USB_H_BBLERR0_S  8
/** USB_H_FRMOVRUN0:R/W1C；位位置：[9]；默认值：0；1’b0：无帧超限1’b1：帧超限
 */
#define USB_H_FRMOVRUN0    (BIT(9))
#define USB_H_FRMOVRUN0_M  (USB_H_FRMOVRUN0_V << USB_H_FRMOVRUN0_S)
#define USB_H_FRMOVRUN0_V  0x00000001
#define USB_H_FRMOVRUN0_S  9
/** USB_H_DATATGLERR0:R/W1C；位位置：[10]；默认值：0；1’b0：无数据切换错误1’b1：数据切换错误
 */
#define USB_H_DATATGLERR0    (BIT(10))
#define USB_H_DATATGLERR0_M  (USB_H_DATATGLERR0_V << USB_H_DATATGLERR0_S)
#define USB_H_DATATGLERR0_V  0x00000001
#define USB_H_DATATGLERR0_S  10
/** USB_H_baintr0:R/W1C；位位置：[11]；默认值：0；1’b0：无BNA中断1’b1：BNA中断
 */
#define USB_H_BNAINTR0    (BIT(11))
#define USB_H_BNAINTR0_M  (USB_H_BNAINTR0_V << USB_H_BNAINTR0_S)
#define USB_H_BNAINTR0_V  0x00000001
#define USB_H_BNAINTR0_S  11
/** USB_hxcs_XACT_ERR0:R/W1C；位位置：[12]；默认值：0；1’b0：无过度交易错误1’b1：过度交易错误
 */
#define USB_H_XCS_XACT_ERR0    (BIT(12))
#define USB_H_XCS_XACT_ERR0_M  (USB_H_XCS_XACT_ERR0_V << USB_H_XCS_XACT_ERR0_S)
#define USB_H_XCS_XACT_ERR0_V  0x00000001
#define USB_H_XCS_XACT_ERR0_S  12
/** USB_H_DESC_LST_ROLLINTR0:R/W1C；位位置：[13]；默认值：0；1’b0：无描述符翻转中断1’b1：描述符翻转中断
 */
#define USB_H_DESC_LST_ROLLINTR0    (BIT(13))
#define USB_H_DESC_LST_ROLLINTR0_M  (USB_H_DESC_LST_ROLLINTR0_V << USB_H_DESC_LST_ROLLINTR0_S)
#define USB_H_DESC_LST_ROLLINTR0_V  0x00000001
#define USB_H_DESC_LST_ROLLINTR0_S  13


/** USB_HCINTMSK0_REG寄存器主机通道0中断掩码寄存器
 */
#define USB_HCINTMSK0_REG (SOC_DPORT_USB_BASE + 0x50c)
/** USB_H_xfercomplexk0:R/W；位位置：[0]；默认值：0；1’b0：传输完成掩码1’b1：无传输完成掩码
 */
#define USB_H_XFERCOMPLMSK0    (BIT(0))
#define USB_H_XFERCOMPLMSK0_M  (USB_H_XFERCOMPLMSK0_V << USB_H_XFERCOMPLMSK0_S)
#define USB_H_XFERCOMPLMSK0_V  0x00000001
#define USB_H_XFERCOMPLMSK0_S  0
/** USB_H_chltdmsk0:R/W；位位置：[1]；默认值：0；1’b0：信道暂停掩码1’b1：无信道暂停掩码
 */
#define USB_H_CHHLTDMSK0    (BIT(1))
#define USB_H_CHHLTDMSK0_M  (USB_H_CHHLTDMSK0_V << USB_H_CHHLTDMSK0_S)
#define USB_H_CHHLTDMSK0_V  0x00000001
#define USB_H_CHHLTDMSK0_S  1
/** USB_H_AHBERRMSK0:R/W；位位置：[2]；默认值：0；1’b0:AHB错误掩码1’b1：无AHB错误屏蔽
 */
#define USB_H_AHBERRMSK0    (BIT(2))
#define USB_H_AHBERRMSK0_M  (USB_H_AHBERRMSK0_V << USB_H_AHBERRMSK0_S)
#define USB_H_AHBERRMSK0_V  0x00000001
#define USB_H_AHBERRMSK0_S  2
/** USB_H_sstallmsk0:R/W；位位置：[3]；默认值：0；1’b0：屏蔽收到的STALL响应中断1’b1：没有收到STALL响应的中断屏蔽
 */
#define USB_H_STALLMSK0    (BIT(3))
#define USB_H_STALLMSK0_M  (USB_H_STALLMSK0_V << USB_H_STALLMSK0_S)
#define USB_H_STALLMSK0_V  0x00000001
#define USB_H_STALLMSK0_S  3
/** USB_H_akmsk0:R/W；位位置：[4]；默认值：0；1’b0：屏蔽收到的NAK响应中断1’b1：没有收到NAK响应的中断屏蔽
 */
#define USB_H_NAKMSK0    (BIT(4))
#define USB_H_NAKMSK0_M  (USB_H_NAKMSK0_V << USB_H_NAKMSK0_S)
#define USB_H_NAKMSK0_V  0x00000001
#define USB_H_NAKMSK0_S  4
/** USB_H_ACKMSK0:R/W；位位置：[5]；默认值：0；1’b0：屏蔽接收/发送的ACK响应中断1’b1：未接收/发送ACK响应中断屏蔽
 */
#define USB_H_ACKMSK0    (BIT(5))
#define USB_H_ACKMSK0_M  (USB_H_ACKMSK0_V << USB_H_ACKMSK0_S)
#define USB_H_ACKMSK0_V  0x00000001
#define USB_H_ACKMSK0_S  5
/** USB_H_NYETMSK0:R/W；位位置：[6]；默认值：0；1’b0：屏蔽接收到的NYET响应中断1’b1：未接收到NYET响应的中断屏蔽
 */
#define USB_H_NYETMSK0    (BIT(6))
#define USB_H_NYETMSK0_M  (USB_H_NYETMSK0_V << USB_H_NYETMSK0_S)
#define USB_H_NYETMSK0_V  0x00000001
#define USB_H_NYETMSK0_S  6
/** USB_H_axaterrmsk0:R/W；位位置：[7]；默认值：0；1’b0：掩码事务错误1’b1：无事务错误掩码
 */
#define USB_H_XACTERRMSK0    (BIT(7))
#define USB_H_XACTERRMSK0_M  (USB_H_XACTERRMSK0_V << USB_H_XACTERRMSK0_S)
#define USB_H_XACTERRMSK0_V  0x00000001
#define USB_H_XACTERRMSK0_S  7
/** USB_H_bbblerrmsk0:R/W；位位置：[8]；默认值：0；巴贝尔错误掩码1’b0：掩码巴贝尔错误1’b1：无巴贝尔错误遮罩
 */
#define USB_H_BBLERRMSK0    (BIT(8))
#define USB_H_BBLERRMSK0_M  (USB_H_BBLERRMSK0_V << USB_H_BBLERRMSK0_S)
#define USB_H_BBLERRMSK0_V  0x00000001
#define USB_H_BBLERRMSK0_S  8
/** USB_H_FRMOVRUNMSK0:R/W；位位置：[9]；默认值：0；帧溢出掩码0x0（Mask）：掩码溢出掩码0x1（NOMASK）：无帧溢出掩码
 */
#define USB_H_FRMOVRUNMSK0    (BIT(9))
#define USB_H_FRMOVRUNMSK0_M  (USB_H_FRMOVRUNMSK0_V << USB_H_FRMOVRUNMSK0_S)
#define USB_H_FRMOVRUNMSK0_V  0x00000001
#define USB_H_FRMOVRUNMSK0_S  9
/** USB_H_DATATGLERRMSK0:R/W；位位置：[10]；默认值：0；主机1’b0的数据切换错误掩码n分散/聚集DMA模式：掩码数据切换错误1’b1：无数据切换错误屏蔽
 */
#define USB_H_DATATGLERRMSK0    (BIT(10))
#define USB_H_DATATGLERRMSK0_M  (USB_H_DATATGLERRMSK0_V << USB_H_DATATGLERRMSK0_S)
#define USB_H_DATATGLERRMSK0_V  0x00000001
#define USB_H_DATATGLERRMSK0_S  10
/** USB_H_baintrmsk0:R/W；位位置：[11]；默认值：0；BNA（缓冲区不可用）中断屏蔽寄存器1’b0:BNA中断屏蔽1’b1：BNA中断未屏蔽
 */
#define USB_H_BNAINTRMSK0    (BIT(11))
#define USB_H_BNAINTRMSK0_M  (USB_H_BNAINTRMSK0_V << USB_H_BNAINTRMSK0_S)
#define USB_H_BNAINTRMSK0_V  0x00000001
#define USB_H_BNAINTRMSK0_S  11
/** USB_H_DESC_LST_ROLLINTRMSK0:R/W；位位置：[13]；默认值：0；描述符列表滚动中断掩码1'b0:描述符滚动中断掩码1'b1：未屏蔽描述符滚动中断
 */
#define USB_H_DESC_LST_ROLLINTRMSK0    (BIT(13))
#define USB_H_DESC_LST_ROLLINTRMSK0_M  (USB_H_DESC_LST_ROLLINTRMSK0_V << USB_H_DESC_LST_ROLLINTRMSK0_S)
#define USB_H_DESC_LST_ROLLINTRMSK0_V  0x00000001
#define USB_H_DESC_LST_ROLLINTRMSK0_S  13


/** USB_HCINT1_REG寄存器主机通道1中断寄存器
 */
#define USB_HCINT1_REG (SOC_DPORT_USB_BASE + 0x528)
/** USB_H_xfercomple1:R/W1C；位位置：[0]；默认值：0；1’b0：正在传输或无活动传输1’b1：传输正常完成，无任何错误
 */
#define USB_H_XFERCOMPL1    (BIT(0))
#define USB_H_XFERCOMPL1_M  (USB_H_XFERCOMPL1_V << USB_H_XFERCOMPL1_S)
#define USB_H_XFERCOMPL1_V  0x00000001
#define USB_H_XFERCOMPL1_S  0
/** USB_H_chltd1:R/W1C；位位置：[1]；默认值：0；1’b0：频道未停止1’b1：频道已停止
 */
#define USB_H_CHHLTD1    (BIT(1))
#define USB_H_CHHLTD1_M  (USB_H_CHHLTD1_V << USB_H_CHHLTD1_S)
#define USB_H_CHHLTD1_V  0x00000001
#define USB_H_CHHLTD1_S  1
/** USB_H_ahber1:R/W1C；位位置：[2]；默认值：0；1’b0：无AHB错误1’b1：AHB读/写期间发生AHB错误
 */
#define USB_H_AHBERR1    (BIT(2))
#define USB_H_AHBERR1_M  (USB_H_AHBERR1_V << USB_H_AHBERR1_S)
#define USB_H_AHBERR1_V  0x00000001
#define USB_H_AHBERR1_S  2
/** USB_H_安装1:R/W1C；位位置：[3]；默认值：0；1’b0：未收到暂停响应中断1’b1：收到暂停响应
 */
#define USB_H_STALL1    (BIT(3))
#define USB_H_STALL1_M  (USB_H_STALL1_V << USB_H_STALL1_S)
#define USB_H_STALL1_V  0x00000001
#define USB_H_STALL1_S  3
/** USB_H_nak1:R/W1C；位位置：[4]；默认值：0；1’b0：未收到NAK响应中断1’b1：收到NAK应答中断
 */
#define USB_H_NACK1    (BIT(4))
#define USB_H_NACK1_M  (USB_H_NACK1_V << USB_H_NACK1_S)
#define USB_H_NACK1_V  0x00000001
#define USB_H_NACK1_S  4
/** USB_H_ACK1:R/W1C；位位置：[5]；默认值：0；1’b0：未收到或发送ACK响应中断1’b1：收到或发送的ACK响应中断
 */
#define USB_H_ACK1    (BIT(5))
#define USB_H_ACK1_M  (USB_H_ACK1_V << USB_H_ACK1_S)
#define USB_H_ACK1_V  0x00000001
#define USB_H_ACK1_S  5
/** USB_H_NYET1:R/W1C；位位置：[6]；默认值：0；1’b0：未收到NYET响应中断1’b1：收到NYET应答中断
 */
#define USB_H_NYET1    (BIT(6))
#define USB_H_NYET1_M  (USB_H_NYET1_V << USB_H_NYET1_S)
#define USB_H_NYET1_V  0x00000001
#define USB_H_NYET1_S  6
/** USB_H_xacter1:R/W1C；位位置：[7]；默认值：0；指示USB上发生以下错误之一：CRC检查失败超时位填充错误错误错误EOP
 */
#define USB_H_XACTERR1    (BIT(7))
#define USB_H_XACTERR1_M  (USB_H_XACTERR1_V << USB_H_XACTERR1_S)
#define USB_H_XACTERR1_V  0x00000001
#define USB_H_XACTERR1_S  7
/** USB_H_bbblerr1:R/W1C；位位置：[8]；默认值：0；1’b0：无巴贝尔错误1’b1：巴贝尔错误
 */
#define USB_H_BBLERR1    (BIT(8))
#define USB_H_BBLERR1_M  (USB_H_BBLERR1_V << USB_H_BBLERR1_S)
#define USB_H_BBLERR1_V  0x00000001
#define USB_H_BBLERR1_S  8
/** USB_H_FRMOVRUN1:R/W1C；位位置：[9]；默认值：0；1’b0：无帧超限1’b1：帧超限
 */
#define USB_H_FRMOVRUN1    (BIT(9))
#define USB_H_FRMOVRUN1_M  (USB_H_FRMOVRUN1_V << USB_H_FRMOVRUN1_S)
#define USB_H_FRMOVRUN1_V  0x00000001
#define USB_H_FRMOVRUN1_S  9
/** USB_H_datatgler1:R/W1C；位位置：[10]；默认值：0；1’b0：无数据切换错误1’b1：数据切换错误
 */
#define USB_H_DATATGLERR1    (BIT(10))
#define USB_H_DATATGLERR1_M  (USB_H_DATATGLERR1_V << USB_H_DATATGLERR1_S)
#define USB_H_DATATGLERR1_V  0x00000001
#define USB_H_DATATGLERR1_S  10
/** USB_H_baintr1:R/W1C；位位置：[11]；默认值：0；1’b0：无BNA中断1’b1：BNA中断
 */
#define USB_H_BNAINTR1    (BIT(11))
#define USB_H_BNAINTR1_M  (USB_H_BNAINTR1_V << USB_H_BNAINTR1_S)
#define USB_H_BNAINTR1_V  0x00000001
#define USB_H_BNAINTR1_S  11
/** USB_hxcs_XACT_ERR1:R/W1C；位位置：[12]；默认值：0；1’b0：无过度交易错误1’b1：过度交易错误
 */
#define USB_H_XCS_XACT_ERR1    (BIT(12))
#define USB_H_XCS_XACT_ERR1_M  (USB_H_XCS_XACT_ERR1_V << USB_H_XCS_XACT_ERR1_S)
#define USB_H_XCS_XACT_ERR1_V  0x00000001
#define USB_H_XCS_XACT_ERR1_S  12
/** USB_H_DESC_LST_ROLLINTR1:R/W1C；位位置：[13]；默认值：0；1’b0：无描述符翻转中断1’b1：描述符翻转中断
 */
#define USB_H_DESC_LST_ROLLINTR1    (BIT(13))
#define USB_H_DESC_LST_ROLLINTR1_M  (USB_H_DESC_LST_ROLLINTR1_V << USB_H_DESC_LST_ROLLINTR1_S)
#define USB_H_DESC_LST_ROLLINTR1_V  0x00000001
#define USB_H_DESC_LST_ROLLINTR1_S  13


/** USB_HCINTMSK1_REG寄存器主机通道1中断掩码寄存器
 */
#define USB_HCINTMSK1_REG (SOC_DPORT_USB_BASE + 0x52c)
/** USB_H_xfercomplexk1:R/W；位位置：[0]；默认值：0；1’b0：传输完成掩码1’b1：无传输完成掩码
 */
#define USB_H_XFERCOMPLMSK1    (BIT(0))
#define USB_H_XFERCOMPLMSK1_M  (USB_H_XFERCOMPLMSK1_V << USB_H_XFERCOMPLMSK1_S)
#define USB_H_XFERCOMPLMSK1_V  0x00000001
#define USB_H_XFERCOMPLMSK1_S  0
/** USB_H_chltdmsk1:R/W；位位置：[1]；默认值：0；1’b0：信道暂停掩码1’b1：无信道暂停掩码
 */
#define USB_H_CHHLTDMSK1    (BIT(1))
#define USB_H_CHHLTDMSK1_M  (USB_H_CHHLTDMSK1_V << USB_H_CHHLTDMSK1_S)
#define USB_H_CHHLTDMSK1_V  0x00000001
#define USB_H_CHHLTDMSK1_S  1
/** USB_H_ahberbrmsk1:R/W；位位置：[2]；默认值：0；1’b0:AHB错误掩码1’b1：无AHB错误屏蔽
 */
#define USB_H_AHBERRMSK1    (BIT(2))
#define USB_H_AHBERRMSK1_M  (USB_H_AHBERRMSK1_V << USB_H_AHBERRMSK1_S)
#define USB_H_AHBERRMSK1_V  0x00000001
#define USB_H_AHBERRMSK1_S  2
/** USB_H_安装msk1:R/W；位位置：[3]；默认值：0；1’b0：屏蔽收到的STALL响应中断1’b1：没有收到STALL响应的中断屏蔽
 */
#define USB_H_STALLMSK1    (BIT(3))
#define USB_H_STALLMSK1_M  (USB_H_STALLMSK1_V << USB_H_STALLMSK1_S)
#define USB_H_STALLMSK1_V  0x00000001
#define USB_H_STALLMSK1_S  3
/** USB_H_NAKMSK1:R/W；位位置：[4]；默认值：0；1’b0：屏蔽收到的NAK响应中断1’b1：没有收到NAK响应的中断屏蔽
 */
#define USB_H_NAKMSK1    (BIT(4))
#define USB_H_NAKMSK1_M  (USB_H_NAKMSK1_V << USB_H_NAKMSK1_S)
#define USB_H_NAKMSK1_V  0x00000001
#define USB_H_NAKMSK1_S  4
/** USB_H_ACKMSK1:R/W；位位置：[5]；默认值：0；1’b0：屏蔽接收/发送的ACK响应中断1’b1：未接收/发送ACK响应中断屏蔽
 */
#define USB_H_ACKMSK1    (BIT(5))
#define USB_H_ACKMSK1_M  (USB_H_ACKMSK1_V << USB_H_ACKMSK1_S)
#define USB_H_ACKMSK1_V  0x00000001
#define USB_H_ACKMSK1_S  5
/** USB_H_NYETMSK1:R/W；位位置：[6]；默认值：0；1’b0：屏蔽接收到的NYET响应中断1’b1：未接收到NYET响应的中断屏蔽
 */
#define USB_H_NYETMSK1    (BIT(6))
#define USB_H_NYETMSK1_M  (USB_H_NYETMSK1_V << USB_H_NYETMSK1_S)
#define USB_H_NYETMSK1_V  0x00000001
#define USB_H_NYETMSK1_S  6
/** USB_H_axaterrmsk1:R/W；位位置：[7]；默认值：0；1’b0：掩码事务错误1’b1：无事务错误掩码
 */
#define USB_H_XACTERRMSK1    (BIT(7))
#define USB_H_XACTERRMSK1_M  (USB_H_XACTERRMSK1_V << USB_H_XACTERRMSK1_S)
#define USB_H_XACTERRMSK1_V  0x00000001
#define USB_H_XACTERRMSK1_S  7
/** USB_H_bbblerrmsk1:R/W；位位置：[8]；默认值：0；巴贝尔错误掩码1’b0：掩码巴贝尔错误1’b1：无巴贝尔错误遮罩
 */
#define USB_H_BBLERRMSK1    (BIT(8))
#define USB_H_BBLERRMSK1_M  (USB_H_BBLERRMSK1_V << USB_H_BBLERRMSK1_S)
#define USB_H_BBLERRMSK1_V  0x00000001
#define USB_H_BBLERRMSK1_S  8
/** USB_H_FRMOVRUNMSK1:R/W；位位置：[9]；默认值：0；帧溢出掩码0x0（Mask）：掩码溢出掩码0x1（NOMASK）：无帧溢出掩码
 */
#define USB_H_FRMOVRUNMSK1    (BIT(9))
#define USB_H_FRMOVRUNMSK1_M  (USB_H_FRMOVRUNMSK1_V << USB_H_FRMOVRUNMSK1_S)
#define USB_H_FRMOVRUNMSK1_V  0x00000001
#define USB_H_FRMOVRUNMSK1_S  9
/** USB_H_DATATGLERRMSK1:R/W；位位置：[10]；默认值：0；主机1’b0的数据切换错误掩码n分散/聚集DMA模式：掩码数据切换错误1’b1：无数据切换错误屏蔽
 */
#define USB_H_DATATGLERRMSK1    (BIT(10))
#define USB_H_DATATGLERRMSK1_M  (USB_H_DATATGLERRMSK1_V << USB_H_DATATGLERRMSK1_S)
#define USB_H_DATATGLERRMSK1_V  0x00000001
#define USB_H_DATATGLERRMSK1_S  10
/** USB_H_baintrmsk1:R/W；位位置：[11]；默认值：0；BNA（缓冲区不可用）中断屏蔽寄存器1’b0:BNA中断屏蔽1’b1：BNA中断未屏蔽
 */
#define USB_H_BNAINTRMSK1    (BIT(11))
#define USB_H_BNAINTRMSK1_M  (USB_H_BNAINTRMSK1_V << USB_H_BNAINTRMSK1_S)
#define USB_H_BNAINTRMSK1_V  0x00000001
#define USB_H_BNAINTRMSK1_S  11
/** USB_H_DESC_LST_ROLLINTRMSK1:R/W；位位置：[13]；默认值：0；描述符列表滚动中断掩码1'b0:描述符滚动中断掩码1'b1：未屏蔽描述符滚动中断
 */
#define USB_H_DESC_LST_ROLLINTRMSK1    (BIT(13))
#define USB_H_DESC_LST_ROLLINTRMSK1_M  (USB_H_DESC_LST_ROLLINTRMSK1_V << USB_H_DESC_LST_ROLLINTRMSK1_S)
#define USB_H_DESC_LST_ROLLINTRMSK1_V  0x00000001
#define USB_H_DESC_LST_ROLLINTRMSK1_S  13


/** USB_HCINT2_REG寄存器主机通道2中断寄存器
 */
#define USB_HCINT2_REG (SOC_DPORT_USB_BASE + 0x548)
/** USB_H_xfercomple2:R/W1C；位位置：[0]；默认值：0；1’b0：正在传输或无活动传输1’b1：传输正常完成，无任何错误
 */
#define USB_H_XFERCOMPL2    (BIT(0))
#define USB_H_XFERCOMPL2_M  (USB_H_XFERCOMPL2_V << USB_H_XFERCOMPL2_S)
#define USB_H_XFERCOMPL2_V  0x00000001
#define USB_H_XFERCOMPL2_S  0
/** USB_H_chltd2:R/W1C；位位置：[1]；默认值：0；1’b0：频道未停止1’b1：频道已停止
 */
#define USB_H_CHHLTD2    (BIT(1))
#define USB_H_CHHLTD2_M  (USB_H_CHHLTD2_V << USB_H_CHHLTD2_S)
#define USB_H_CHHLTD2_V  0x00000001
#define USB_H_CHHLTD2_S  1
/** USB_H_ahber2:R/W1C；位位置：[2]；默认值：0；1’b0：无AHB错误1’b1：AHB读/写期间发生AHB错误
 */
#define USB_H_AHBERR2    (BIT(2))
#define USB_H_AHBERR2_M  (USB_H_AHBERR2_V << USB_H_AHBERR2_S)
#define USB_H_AHBERR2_V  0x00000001
#define USB_H_AHBERR2_S  2
/** USB_H_安装2：R/W1C；位位置：[3]；默认值：0；1’b0：未收到暂停响应中断1’b1：收到暂停响应
 */
#define USB_H_STALL2    (BIT(3))
#define USB_H_STALL2_M  (USB_H_STALL2_V << USB_H_STALL2_S)
#define USB_H_STALL2_V  0x00000001
#define USB_H_STALL2_S  3
/** USB_H_nak2:R/W1C；位位置：[4]；默认值：0；1’b0：未收到NAK响应中断1’b1：收到NAK应答中断
 */
#define USB_H_NACK2    (BIT(4))
#define USB_H_NACK2_M  (USB_H_NACK2_V << USB_H_NACK2_S)
#define USB_H_NACK2_V  0x00000001
#define USB_H_NACK2_S  4
/** USB_H_ACK2:R/W1C；位位置：[5]；默认值：0；1’b0：未收到或发送ACK响应中断1’b1：收到或发送的ACK响应中断
 */
#define USB_H_ACK2    (BIT(5))
#define USB_H_ACK2_M  (USB_H_ACK2_V << USB_H_ACK2_S)
#define USB_H_ACK2_V  0x00000001
#define USB_H_ACK2_S  5
/** USB_H_NYET2:R/W1C；位位置：[6]；默认值：0；1’b0：未收到NYET响应中断1’b1：收到NYET应答中断
 */
#define USB_H_NYET2    (BIT(6))
#define USB_H_NYET2_M  (USB_H_NYET2_V << USB_H_NYET2_S)
#define USB_H_NYET2_V  0x00000001
#define USB_H_NYET2_S  6
/** USB_H_xacter2:R/W1C；位位置：[7]；默认值：0；指示USB上发生以下错误之一：CRC检查失败超时位填充错误错误错误EOP
 */
#define USB_H_XACTERR2    (BIT(7))
#define USB_H_XACTERR2_M  (USB_H_XACTERR2_V << USB_H_XACTERR2_S)
#define USB_H_XACTERR2_V  0x00000001
#define USB_H_XACTERR2_S  7
/** USB_H_bbblerr2:R/W1C；位位置：[8]；默认值：0；1’b0：无巴贝尔错误1’b1：巴贝尔错误
 */
#define USB_H_BBLERR2    (BIT(8))
#define USB_H_BBLERR2_M  (USB_H_BBLERR2_V << USB_H_BBLERR2_S)
#define USB_H_BBLERR2_V  0x00000001
#define USB_H_BBLERR2_S  8
/** USB_H_FRMOVRUN2:R/W1C；位位置：[9]；默认值：0；1’b0：无帧超限1’b1：帧超限
 */
#define USB_H_FRMOVRUN2    (BIT(9))
#define USB_H_FRMOVRUN2_M  (USB_H_FRMOVRUN2_V << USB_H_FRMOVRUN2_S)
#define USB_H_FRMOVRUN2_V  0x00000001
#define USB_H_FRMOVRUN2_S  9
/** USB_H_datatgler2:R/W1C；位位置：[10]；默认值：0；1’b0：无数据切换错误1’b1：数据切换错误
 */
#define USB_H_DATATGLERR2    (BIT(10))
#define USB_H_DATATGLERR2_M  (USB_H_DATATGLERR2_V << USB_H_DATATGLERR2_S)
#define USB_H_DATATGLERR2_V  0x00000001
#define USB_H_DATATGLERR2_S  10
/** USB_H_baintr2:R/W1C；位位置：[11]；默认值：0；1’b0：无BNA中断1’b1：BNA中断
 */
#define USB_H_BNAINTR2    (BIT(11))
#define USB_H_BNAINTR2_M  (USB_H_BNAINTR2_V << USB_H_BNAINTR2_S)
#define USB_H_BNAINTR2_V  0x00000001
#define USB_H_BNAINTR2_S  11
/** USB_hxcs_XACT_ERR2:R/W1C；位位置：[12]；默认值：0；1’b0：无过度交易错误1’b1：过度交易错误
 */
#define USB_H_XCS_XACT_ERR2    (BIT(12))
#define USB_H_XCS_XACT_ERR2_M  (USB_H_XCS_XACT_ERR2_V << USB_H_XCS_XACT_ERR2_S)
#define USB_H_XCS_XACT_ERR2_V  0x00000001
#define USB_H_XCS_XACT_ERR2_S  12
/** USB_H_DESC_LST_ROLLINTR2:R/W1C；位位置：[13]；默认值：0；1’b0：无描述符翻转中断1’b1：描述符翻转中断
 */
#define USB_H_DESC_LST_ROLLINTR2    (BIT(13))
#define USB_H_DESC_LST_ROLLINTR2_M  (USB_H_DESC_LST_ROLLINTR2_V << USB_H_DESC_LST_ROLLINTR2_S)
#define USB_H_DESC_LST_ROLLINTR2_V  0x00000001
#define USB_H_DESC_LST_ROLLINTR2_S  13


/** USB_HCINTMSK2_REG寄存器主机通道2中断掩码寄存器
 */
#define USB_HCINTMSK2_REG (SOC_DPORT_USB_BASE + 0x54c)
/** USB_H_xfercomplexk2:R/W；位位置：[0]；默认值：0；1’b0：传输完成掩码1’b1：无传输完成掩码
 */
#define USB_H_XFERCOMPLMSK2    (BIT(0))
#define USB_H_XFERCOMPLMSK2_M  (USB_H_XFERCOMPLMSK2_V << USB_H_XFERCOMPLMSK2_S)
#define USB_H_XFERCOMPLMSK2_V  0x00000001
#define USB_H_XFERCOMPLMSK2_S  0
/** USB_H_chltdmsk2:R/W；位位置：[1]；默认值：0；1’b0：信道暂停掩码1’b1：无信道暂停掩码
 */
#define USB_H_CHHLTDMSK2    (BIT(1))
#define USB_H_CHHLTDMSK2_M  (USB_H_CHHLTDMSK2_V << USB_H_CHHLTDMSK2_S)
#define USB_H_CHHLTDMSK2_V  0x00000001
#define USB_H_CHHLTDMSK2_S  1
/** USB_H_ahberbrmsk2:R/W；位位置：[2]；默认值：0；1’b0:AHB错误掩码1’b1：无AHB错误屏蔽
 */
#define USB_H_AHBERRMSK2    (BIT(2))
#define USB_H_AHBERRMSK2_M  (USB_H_AHBERRMSK2_V << USB_H_AHBERRMSK2_S)
#define USB_H_AHBERRMSK2_V  0x00000001
#define USB_H_AHBERRMSK2_S  2
/** USB_H_sstallmsk2:R/W；位位置：[3]；默认值：0；1’b0：屏蔽收到的STALL响应中断1’b1：没有收到STALL响应的中断屏蔽
 */
#define USB_H_STALLMSK2    (BIT(3))
#define USB_H_STALLMSK2_M  (USB_H_STALLMSK2_V << USB_H_STALLMSK2_S)
#define USB_H_STALLMSK2_V  0x00000001
#define USB_H_STALLMSK2_S  3
/** USB_H_akmsk2:R/W；位位置：[4]；默认值：0；1’b0：屏蔽收到的NAK响应中断1’b1：没有收到NAK响应的中断屏蔽
 */
#define USB_H_NAKMSK2    (BIT(4))
#define USB_H_NAKMSK2_M  (USB_H_NAKMSK2_V << USB_H_NAKMSK2_S)
#define USB_H_NAKMSK2_V  0x00000001
#define USB_H_NAKMSK2_S  4
/** USB_H_ACKMSK2:R/W；位位置：[5]；默认值：0；1’b0：屏蔽接收/发送的ACK响应中断1’b1：未接收/发送ACK响应中断屏蔽
 */
#define USB_H_ACKMSK2    (BIT(5))
#define USB_H_ACKMSK2_M  (USB_H_ACKMSK2_V << USB_H_ACKMSK2_S)
#define USB_H_ACKMSK2_V  0x00000001
#define USB_H_ACKMSK2_S  5
/** USB_H_NYETMSK2:R/W；位位置：[6]；默认值：0；1’b0：屏蔽接收到的NYET响应中断1’b1：未接收到NYET响应的中断屏蔽
 */
#define USB_H_NYETMSK2    (BIT(6))
#define USB_H_NYETMSK2_M  (USB_H_NYETMSK2_V << USB_H_NYETMSK2_S)
#define USB_H_NYETMSK2_V  0x00000001
#define USB_H_NYETMSK2_S  6
/** USB_H_axaterrmsk2:R/W；位位置：[7]；默认值：0；1’b0：掩码事务错误1’b1：无事务错误掩码
 */
#define USB_H_XACTERRMSK2    (BIT(7))
#define USB_H_XACTERRMSK2_M  (USB_H_XACTERRMSK2_V << USB_H_XACTERRMSK2_S)
#define USB_H_XACTERRMSK2_V  0x00000001
#define USB_H_XACTERRMSK2_S  7
/** USB_H_bbblerrmsk2:R/W；位位置：[8]；默认值：0；巴贝尔错误掩码1’b0：掩码巴贝尔错误1’b1：无巴贝尔错误遮罩
 */
#define USB_H_BBLERRMSK2    (BIT(8))
#define USB_H_BBLERRMSK2_M  (USB_H_BBLERRMSK2_V << USB_H_BBLERRMSK2_S)
#define USB_H_BBLERRMSK2_V  0x00000001
#define USB_H_BBLERRMSK2_S  8
/** USB_H_FRMOVRUNMSK2:R/W；位位置：[9]；默认值：0；帧溢出掩码0x0（Mask）：掩码溢出掩码0x1（NOMASK）：无帧溢出掩码
 */
#define USB_H_FRMOVRUNMSK2    (BIT(9))
#define USB_H_FRMOVRUNMSK2_M  (USB_H_FRMOVRUNMSK2_V << USB_H_FRMOVRUNMSK2_S)
#define USB_H_FRMOVRUNMSK2_V  0x00000001
#define USB_H_FRMOVRUNMSK2_S  9
/** USB_H_DATATGLERRMSK2:R/W；位位置：[10]；默认值：0；主机1’b0的数据切换错误掩码n分散/聚集DMA模式：掩码数据切换错误1’b1：无数据切换错误屏蔽
 */
#define USB_H_DATATGLERRMSK2    (BIT(10))
#define USB_H_DATATGLERRMSK2_M  (USB_H_DATATGLERRMSK2_V << USB_H_DATATGLERRMSK2_S)
#define USB_H_DATATGLERRMSK2_V  0x00000001
#define USB_H_DATATGLERRMSK2_S  10
/** USB_H_baintrmsk2:R/W；位位置：[11]；默认值：0；BNA（缓冲区不可用）中断屏蔽寄存器1’b0:BNA中断屏蔽1’b1：BNA中断未屏蔽
 */
#define USB_H_BNAINTRMSK2    (BIT(11))
#define USB_H_BNAINTRMSK2_M  (USB_H_BNAINTRMSK2_V << USB_H_BNAINTRMSK2_S)
#define USB_H_BNAINTRMSK2_V  0x00000001
#define USB_H_BNAINTRMSK2_S  11
/** USB_H_DESC_LST_ROLLINTRMSK2:R/W；位位置：[13]；默认值：0；描述符列表滚动中断掩码1'b0:描述符滚动中断掩码1'b1：未屏蔽描述符滚动中断
 */
#define USB_H_DESC_LST_ROLLINTRMSK2    (BIT(13))
#define USB_H_DESC_LST_ROLLINTRMSK2_M  (USB_H_DESC_LST_ROLLINTRMSK2_V << USB_H_DESC_LST_ROLLINTRMSK2_S)
#define USB_H_DESC_LST_ROLLINTRMSK2_V  0x00000001
#define USB_H_DESC_LST_ROLLINTRMSK2_S  13


/** USB_HCINT3_REG寄存器主机通道3中断寄存器
 */
#define USB_HCINT3_REG (SOC_DPORT_USB_BASE + 0x568)
/** USB_H_XFERCOMPL3:R/W1C；位位置：[0]；默认值：0；1’b0：正在传输或无活动传输1’b1：传输正常完成，无任何错误
 */
#define USB_H_XFERCOMPL3    (BIT(0))
#define USB_H_XFERCOMPL3_M  (USB_H_XFERCOMPL3_V << USB_H_XFERCOMPL3_S)
#define USB_H_XFERCOMPL3_V  0x00000001
#define USB_H_XFERCOMPL3_S  0
/** USB_H_chltd3:R/W1C；位位置：[1]；默认值：0；1’b0：频道未停止1’b1：频道已停止
 */
#define USB_H_CHHLTD3    (BIT(1))
#define USB_H_CHHLTD3_M  (USB_H_CHHLTD3_V << USB_H_CHHLTD3_S)
#define USB_H_CHHLTD3_V  0x00000001
#define USB_H_CHHLTD3_S  1
/** USB_H_ahber3:R/W1C；位位置：[2]；默认值：0；1’b0：无AHB错误1’b1：AHB读/写期间发生AHB错误
 */
#define USB_H_AHBERR3    (BIT(2))
#define USB_H_AHBERR3_M  (USB_H_AHBERR3_V << USB_H_AHBERR3_S)
#define USB_H_AHBERR3_V  0x00000001
#define USB_H_AHBERR3_S  2
/** USB_H_安装3：R/W1C；位位置：[3]；默认值：0；1’b0：未收到暂停响应中断1’b1：收到暂停响应
 */
#define USB_H_STALL3    (BIT(3))
#define USB_H_STALL3_M  (USB_H_STALL3_V << USB_H_STALL3_S)
#define USB_H_STALL3_V  0x00000001
#define USB_H_STALL3_S  3
/** USB_H_nak3:R/W1C；位位置：[4]；默认值：0；1’b0：未收到NAK响应中断1’b1：收到NAK应答中断
 */
#define USB_H_NACK3    (BIT(4))
#define USB_H_NACK3_M  (USB_H_NACK3_V << USB_H_NACK3_S)
#define USB_H_NACK3_V  0x00000001
#define USB_H_NACK3_S  4
/** USB_H_ACK3:R/W1C；位位置：[5]；默认值：0；1’b0：未收到或发送ACK响应中断1’b1：收到或发送的ACK响应中断
 */
#define USB_H_ACK3    (BIT(5))
#define USB_H_ACK3_M  (USB_H_ACK3_V << USB_H_ACK3_S)
#define USB_H_ACK3_V  0x00000001
#define USB_H_ACK3_S  5
/** USB_H_NYET3:R/W1C；位位置：[6]；默认值：0；1’b0：未收到NYET响应中断1’b1：收到NYET应答中断
 */
#define USB_H_NYET3    (BIT(6))
#define USB_H_NYET3_M  (USB_H_NYET3_V << USB_H_NYET3_S)
#define USB_H_NYET3_V  0x00000001
#define USB_H_NYET3_S  6
/** USB_H_xacter3:R/W1C；位位置：[7]；默认值：0；指示USB上发生以下错误之一：CRC检查失败超时位填充错误错误错误EOP
 */
#define USB_H_XACTERR3    (BIT(7))
#define USB_H_XACTERR3_M  (USB_H_XACTERR3_V << USB_H_XACTERR3_S)
#define USB_H_XACTERR3_V  0x00000001
#define USB_H_XACTERR3_S  7
/** USB_H_bbblerr3:R/W1C；位位置：[8]；默认值：0；1’b0：无巴贝尔错误1’b1：巴贝尔错误
 */
#define USB_H_BBLERR3    (BIT(8))
#define USB_H_BBLERR3_M  (USB_H_BBLERR3_V << USB_H_BBLERR3_S)
#define USB_H_BBLERR3_V  0x00000001
#define USB_H_BBLERR3_S  8
/** USB_H_FRMOVRUN3:R/W1C；位位置：[9]；默认值：0；1’b0：无帧超限1’b1：帧超限
 */
#define USB_H_FRMOVRUN3    (BIT(9))
#define USB_H_FRMOVRUN3_M  (USB_H_FRMOVRUN3_V << USB_H_FRMOVRUN3_S)
#define USB_H_FRMOVRUN3_V  0x00000001
#define USB_H_FRMOVRUN3_S  9
/** USB_H_DATATGLERR3:R/W1C；位位置：[10]；默认值：0；1’b0：无数据切换错误1’b1：数据切换错误
 */
#define USB_H_DATATGLERR3    (BIT(10))
#define USB_H_DATATGLERR3_M  (USB_H_DATATGLERR3_V << USB_H_DATATGLERR3_S)
#define USB_H_DATATGLERR3_V  0x00000001
#define USB_H_DATATGLERR3_S  10
/** USB_H_baintr3:R/W1C；位位置：[11]；默认值：0；1’b0：无BNA中断1’b1：BNA中断
 */
#define USB_H_BNAINTR3    (BIT(11))
#define USB_H_BNAINTR3_M  (USB_H_BNAINTR3_V << USB_H_BNAINTR3_S)
#define USB_H_BNAINTR3_V  0x00000001
#define USB_H_BNAINTR3_S  11
/** USB_hxcs_XACT_ERR3:R/W1C；位位置：[12]；默认值：0；1’b0：无过度交易错误1’b1：过度交易错误
 */
#define USB_H_XCS_XACT_ERR3    (BIT(12))
#define USB_H_XCS_XACT_ERR3_M  (USB_H_XCS_XACT_ERR3_V << USB_H_XCS_XACT_ERR3_S)
#define USB_H_XCS_XACT_ERR3_V  0x00000001
#define USB_H_XCS_XACT_ERR3_S  12
/** USB_H_DESC_LST_ROLLINTR3:R/W1C；位位置：[13]；默认值：0；1’b0：无描述符翻转中断1’b1：描述符翻转中断
 */
#define USB_H_DESC_LST_ROLLINTR3    (BIT(13))
#define USB_H_DESC_LST_ROLLINTR3_M  (USB_H_DESC_LST_ROLLINTR3_V << USB_H_DESC_LST_ROLLINTR3_S)
#define USB_H_DESC_LST_ROLLINTR3_V  0x00000001
#define USB_H_DESC_LST_ROLLINTR3_S  13


/** USB_HCINTMSK3_REG寄存器主机通道3中断掩码寄存器
 */
#define USB_HCINTMSK3_REG (SOC_DPORT_USB_BASE + 0x56c)
/** USB_H_xfercomplexk3:R/W；位位置：[0]；默认值：0；1’b0：传输完成掩码1’b1：无传输完成掩码
 */
#define USB_H_XFERCOMPLMSK3    (BIT(0))
#define USB_H_XFERCOMPLMSK3_M  (USB_H_XFERCOMPLMSK3_V << USB_H_XFERCOMPLMSK3_S)
#define USB_H_XFERCOMPLMSK3_V  0x00000001
#define USB_H_XFERCOMPLMSK3_S  0
/** USB_H_chltdmsk3:R/W；位位置：[1]；默认值：0；1’b0：信道暂停掩码1’b1：无信道暂停掩码
 */
#define USB_H_CHHLTDMSK3    (BIT(1))
#define USB_H_CHHLTDMSK3_M  (USB_H_CHHLTDMSK3_V << USB_H_CHHLTDMSK3_S)
#define USB_H_CHHLTDMSK3_V  0x00000001
#define USB_H_CHHLTDMSK3_S  1
/** USB_H_AHBERRMSK3:R/W；位位置：[2]；默认值：0；1’b0:AHB错误掩码1’b1：无AHB错误屏蔽
 */
#define USB_H_AHBERRMSK3    (BIT(2))
#define USB_H_AHBERRMSK3_M  (USB_H_AHBERRMSK3_V << USB_H_AHBERRMSK3_S)
#define USB_H_AHBERRMSK3_V  0x00000001
#define USB_H_AHBERRMSK3_S  2
/** USB_H_安装msk3:R/W；位位置：[3]；默认值：0；1’b0：屏蔽收到的STALL响应中断1’b1：没有收到STALL响应的中断屏蔽
 */
#define USB_H_STALLMSK3    (BIT(3))
#define USB_H_STALLMSK3_M  (USB_H_STALLMSK3_V << USB_H_STALLMSK3_S)
#define USB_H_STALLMSK3_V  0x00000001
#define USB_H_STALLMSK3_S  3
/** USB_H_akmsk3:R/W；位位置：[4]；默认值：0；1’b0：屏蔽收到的NAK响应中断1’b1：没有收到NAK响应的中断屏蔽
 */
#define USB_H_NAKMSK3    (BIT(4))
#define USB_H_NAKMSK3_M  (USB_H_NAKMSK3_V << USB_H_NAKMSK3_S)
#define USB_H_NAKMSK3_V  0x00000001
#define USB_H_NAKMSK3_S  4
/** USB_H_ACKMSK3:R/W；位位置：[5]；默认值：0；1’b0：屏蔽接收/发送的ACK响应中断1’b1：未接收/发送ACK响应中断屏蔽
 */
#define USB_H_ACKMSK3    (BIT(5))
#define USB_H_ACKMSK3_M  (USB_H_ACKMSK3_V << USB_H_ACKMSK3_S)
#define USB_H_ACKMSK3_V  0x00000001
#define USB_H_ACKMSK3_S  5
/** USB_H_NYETMSK3:R/W；位位置：[6]；默认值：0；1’b0：屏蔽接收到的NYET响应中断1’b1：未接收到NYET响应的中断屏蔽
 */
#define USB_H_NYETMSK3    (BIT(6))
#define USB_H_NYETMSK3_M  (USB_H_NYETMSK3_V << USB_H_NYETMSK3_S)
#define USB_H_NYETMSK3_V  0x00000001
#define USB_H_NYETMSK3_S  6
/** USB_H_axaterrmsk3:R/W；位位置：[7]；默认值：0；1’b0：掩码事务错误1’b1：无事务错误掩码
 */
#define USB_H_XACTERRMSK3    (BIT(7))
#define USB_H_XACTERRMSK3_M  (USB_H_XACTERRMSK3_V << USB_H_XACTERRMSK3_S)
#define USB_H_XACTERRMSK3_V  0x00000001
#define USB_H_XACTERRMSK3_S  7
/** USB_H_bbblerrmsk3:R/W；位位置：[8]；默认值：0；巴贝尔错误掩码1’b0：掩码巴贝尔错误1’b1：无巴贝尔错误遮罩
 */
#define USB_H_BBLERRMSK3    (BIT(8))
#define USB_H_BBLERRMSK3_M  (USB_H_BBLERRMSK3_V << USB_H_BBLERRMSK3_S)
#define USB_H_BBLERRMSK3_V  0x00000001
#define USB_H_BBLERRMSK3_S  8
/** USB_H_FRMOVRUNMSK3:R/W；位位置：[9]；默认值：0；帧溢出掩码0x0（Mask）：掩码溢出掩码0x1（NOMASK）：无帧溢出掩码
 */
#define USB_H_FRMOVRUNMSK3    (BIT(9))
#define USB_H_FRMOVRUNMSK3_M  (USB_H_FRMOVRUNMSK3_V << USB_H_FRMOVRUNMSK3_S)
#define USB_H_FRMOVRUNMSK3_V  0x00000001
#define USB_H_FRMOVRUNMSK3_S  9
/** USB_H_DATATGLERRMSK3:R/W；位位置：[10]；默认值：0；主机1’b0的数据切换错误掩码n分散/聚集DMA模式：掩码数据切换错误1’b1：无数据切换错误屏蔽
 */
#define USB_H_DATATGLERRMSK3    (BIT(10))
#define USB_H_DATATGLERRMSK3_M  (USB_H_DATATGLERRMSK3_V << USB_H_DATATGLERRMSK3_S)
#define USB_H_DATATGLERRMSK3_V  0x00000001
#define USB_H_DATATGLERRMSK3_S  10
/** USB_H_baintrmsk3:R/W；位位置：[11]；默认值：0；BNA（缓冲区不可用）中断屏蔽寄存器1’b0:BNA中断屏蔽1’b1：BNA中断未屏蔽
 */
#define USB_H_BNAINTRMSK3    (BIT(11))
#define USB_H_BNAINTRMSK3_M  (USB_H_BNAINTRMSK3_V << USB_H_BNAINTRMSK3_S)
#define USB_H_BNAINTRMSK3_V  0x00000001
#define USB_H_BNAINTRMSK3_S  11
/** USB_H_DESC_LST_ROLLINTRMSK3:R/W；位位置：[13]；默认值：0；描述符列表滚动中断掩码1'b0:描述符滚动中断掩码1'b1：未屏蔽描述符滚动中断
 */
#define USB_H_DESC_LST_ROLLINTRMSK3    (BIT(13))
#define USB_H_DESC_LST_ROLLINTRMSK3_M  (USB_H_DESC_LST_ROLLINTRMSK3_V << USB_H_DESC_LST_ROLLINTRMSK3_S)
#define USB_H_DESC_LST_ROLLINTRMSK3_V  0x00000001
#define USB_H_DESC_LST_ROLLINTRMSK3_S  13


/** USB_HCINT4_REG寄存器主机通道4中断寄存器
 */
#define USB_HCINT4_REG (SOC_DPORT_USB_BASE + 0x588)
/** USB_H_XFERCOMPL4:R/W1C；位位置：[0]；默认值：0；1’b0：正在传输或无活动传输1’b1：传输正常完成，无任何错误
 */
#define USB_H_XFERCOMPL4    (BIT(0))
#define USB_H_XFERCOMPL4_M  (USB_H_XFERCOMPL4_V << USB_H_XFERCOMPL4_S)
#define USB_H_XFERCOMPL4_V  0x00000001
#define USB_H_XFERCOMPL4_S  0
/** USB_H_chltd4:R/W1C；位位置：[1]；默认值：0；1’b0：频道未停止1’b1：频道已停止
 */
#define USB_H_CHHLTD4    (BIT(1))
#define USB_H_CHHLTD4_M  (USB_H_CHHLTD4_V << USB_H_CHHLTD4_S)
#define USB_H_CHHLTD4_V  0x00000001
#define USB_H_CHHLTD4_S  1
/** USB_H_ahber4:R/W1C；位位置：[2]；默认值：0；1’b0：无AHB错误1’b1：AHB读/写期间发生AHB错误
 */
#define USB_H_AHBERR4    (BIT(2))
#define USB_H_AHBERR4_M  (USB_H_AHBERR4_V << USB_H_AHBERR4_S)
#define USB_H_AHBERR4_V  0x00000001
#define USB_H_AHBERR4_S  2
/** USB_H_安装4：R/W1C；位位置：[3]；默认值：0；1’b0：未收到暂停响应中断1’b1：收到暂停响应
 */
#define USB_H_STALL4    (BIT(3))
#define USB_H_STALL4_M  (USB_H_STALL4_V << USB_H_STALL4_S)
#define USB_H_STALL4_V  0x00000001
#define USB_H_STALL4_S  3
/** USB_H_nak4:R/W1C；位位置：[4]；默认值：0；1’b0：未收到NAK响应中断1’b1：收到NAK应答中断
 */
#define USB_H_NACK4    (BIT(4))
#define USB_H_NACK4_M  (USB_H_NACK4_V << USB_H_NACK4_S)
#define USB_H_NACK4_V  0x00000001
#define USB_H_NACK4_S  4
/** USB_H_ACK4:R/W1C；位位置：[5]；默认值：0；1’b0：未收到或发送ACK响应中断1’b1：收到或发送的ACK响应中断
 */
#define USB_H_ACK4    (BIT(5))
#define USB_H_ACK4_M  (USB_H_ACK4_V << USB_H_ACK4_S)
#define USB_H_ACK4_V  0x00000001
#define USB_H_ACK4_S  5
/** USB_H_NYET4:R/W1C；位位置：[6]；默认值：0；1’b0：未收到NYET响应中断1’b1：收到NYET应答中断
 */
#define USB_H_NYET4    (BIT(6))
#define USB_H_NYET4_M  (USB_H_NYET4_V << USB_H_NYET4_S)
#define USB_H_NYET4_V  0x00000001
#define USB_H_NYET4_S  6
/** USB_H_xacter4:R/W1C；位位置：[7]；默认值：0；指示USB上发生以下错误之一：CRC检查失败超时位填充错误错误错误EOP
 */
#define USB_H_XACTERR4    (BIT(7))
#define USB_H_XACTERR4_M  (USB_H_XACTERR4_V << USB_H_XACTERR4_S)
#define USB_H_XACTERR4_V  0x00000001
#define USB_H_XACTERR4_S  7
/** USB_H_bbblerr4:R/W1C；位位置：[8]；默认值：0；1’b0：无巴贝尔错误1’b1：巴贝尔错误
 */
#define USB_H_BBLERR4    (BIT(8))
#define USB_H_BBLERR4_M  (USB_H_BBLERR4_V << USB_H_BBLERR4_S)
#define USB_H_BBLERR4_V  0x00000001
#define USB_H_BBLERR4_S  8
/** USB_H_FRMOVRUN4:R/W1C；位位置：[9]；默认值：0；1’b0：无帧超限1’b1：帧超限
 */
#define USB_H_FRMOVRUN4    (BIT(9))
#define USB_H_FRMOVRUN4_M  (USB_H_FRMOVRUN4_V << USB_H_FRMOVRUN4_S)
#define USB_H_FRMOVRUN4_V  0x00000001
#define USB_H_FRMOVRUN4_S  9
/** USB_H_DATATGLERR4:R/W1C；位位置：[10]；默认值：0；1’b0：无数据切换错误1’b1：数据切换错误
 */
#define USB_H_DATATGLERR4    (BIT(10))
#define USB_H_DATATGLERR4_M  (USB_H_DATATGLERR4_V << USB_H_DATATGLERR4_S)
#define USB_H_DATATGLERR4_V  0x00000001
#define USB_H_DATATGLERR4_S  10
/** USB_H_baintr4:R/W1C；位位置：[11]；默认值：0；1’b0：无BNA中断1’b1：BNA中断
 */
#define USB_H_BNAINTR4    (BIT(11))
#define USB_H_BNAINTR4_M  (USB_H_BNAINTR4_V << USB_H_BNAINTR4_S)
#define USB_H_BNAINTR4_V  0x00000001
#define USB_H_BNAINTR4_S  11
/** USB_hxcs_XACT_ERR4:R/W1C；位位置：[12]；默认值：0；1’b0：无过度交易错误1’b1：过度交易错误
 */
#define USB_H_XCS_XACT_ERR4    (BIT(12))
#define USB_H_XCS_XACT_ERR4_M  (USB_H_XCS_XACT_ERR4_V << USB_H_XCS_XACT_ERR4_S)
#define USB_H_XCS_XACT_ERR4_V  0x00000001
#define USB_H_XCS_XACT_ERR4_S  12
/** USB_H_DESC_LST_ROLLINTR4:R/W1C；位位置：[13]；默认值：0；1’b0：无描述符翻转中断1’b1：描述符翻转中断
 */
#define USB_H_DESC_LST_ROLLINTR4    (BIT(13))
#define USB_H_DESC_LST_ROLLINTR4_M  (USB_H_DESC_LST_ROLLINTR4_V << USB_H_DESC_LST_ROLLINTR4_S)
#define USB_H_DESC_LST_ROLLINTR4_V  0x00000001
#define USB_H_DESC_LST_ROLLINTR4_S  13


/** USB_HCINTMSK4_REG寄存器主机通道4中断掩码寄存器
 */
#define USB_HCINTMSK4_REG (SOC_DPORT_USB_BASE + 0x58c)
/** USB_H_xfercomplexk4:R/W；位位置：[0]；默认值：0；1’b0：传输完成掩码1’b1：无传输完成掩码
 */
#define USB_H_XFERCOMPLMSK4    (BIT(0))
#define USB_H_XFERCOMPLMSK4_M  (USB_H_XFERCOMPLMSK4_V << USB_H_XFERCOMPLMSK4_S)
#define USB_H_XFERCOMPLMSK4_V  0x00000001
#define USB_H_XFERCOMPLMSK4_S  0
/** USB_H_chltdmsk4:R/W；位位置：[1]；默认值：0；1’b0：信道暂停掩码1’b1：无信道暂停掩码
 */
#define USB_H_CHHLTDMSK4    (BIT(1))
#define USB_H_CHHLTDMSK4_M  (USB_H_CHHLTDMSK4_V << USB_H_CHHLTDMSK4_S)
#define USB_H_CHHLTDMSK4_V  0x00000001
#define USB_H_CHHLTDMSK4_S  1
/** USB_H_AHBERRMSK4：R/W；位位置：[2]；默认值：0；1’b0:AHB错误掩码1’b1：无AHB错误屏蔽
 */
#define USB_H_AHBERRMSK4    (BIT(2))
#define USB_H_AHBERRMSK4_M  (USB_H_AHBERRMSK4_V << USB_H_AHBERRMSK4_S)
#define USB_H_AHBERRMSK4_V  0x00000001
#define USB_H_AHBERRMSK4_S  2
/** USB_H_安装msk4：R/W；位位置：[3]；默认值：0；1’b0：屏蔽收到的STALL响应中断1’b1：没有收到STALL响应的中断屏蔽
 */
#define USB_H_STALLMSK4    (BIT(3))
#define USB_H_STALLMSK4_M  (USB_H_STALLMSK4_V << USB_H_STALLMSK4_S)
#define USB_H_STALLMSK4_V  0x00000001
#define USB_H_STALLMSK4_S  3
/** USB_H_NAKMSK4:转/转；位位置：[4]；默认值：0；1’b0：屏蔽收到的NAK响应中断1’b1：没有收到NAK响应的中断屏蔽
 */
#define USB_H_NAKMSK4    (BIT(4))
#define USB_H_NAKMSK4_M  (USB_H_NAKMSK4_V << USB_H_NAKMSK4_S)
#define USB_H_NAKMSK4_V  0x00000001
#define USB_H_NAKMSK4_S  4
/** USB_H_ACKMSK4:R/W；位位置：[5]；默认值：0；1’b0：屏蔽接收/发送的ACK响应中断1’b1：未接收/发送ACK响应中断屏蔽
 */
#define USB_H_ACKMSK4    (BIT(5))
#define USB_H_ACKMSK4_M  (USB_H_ACKMSK4_V << USB_H_ACKMSK4_S)
#define USB_H_ACKMSK4_V  0x00000001
#define USB_H_ACKMSK4_S  5
/** USB_H_NYETMSK4:R/W；位位置：[6]；默认值：0；1’b0：屏蔽接收到的NYET响应中断1’b1：未接收到NYET响应的中断屏蔽
 */
#define USB_H_NYETMSK4    (BIT(6))
#define USB_H_NYETMSK4_M  (USB_H_NYETMSK4_V << USB_H_NYETMSK4_S)
#define USB_H_NYETMSK4_V  0x00000001
#define USB_H_NYETMSK4_S  6
/** USB_H_axaterrmsk4:R/W；位位置：[7]；默认值：0；1’b0：掩码事务错误1’b1：无事务错误掩码
 */
#define USB_H_XACTERRMSK4    (BIT(7))
#define USB_H_XACTERRMSK4_M  (USB_H_XACTERRMSK4_V << USB_H_XACTERRMSK4_S)
#define USB_H_XACTERRMSK4_V  0x00000001
#define USB_H_XACTERRMSK4_S  7
/** USB_H_bbblerrmsk4:R/W；位位置：[8]；默认值：0；巴贝尔错误掩码1’b0：掩码巴贝尔错误1’b1：无巴贝尔错误遮罩
 */
#define USB_H_BBLERRMSK4    (BIT(8))
#define USB_H_BBLERRMSK4_M  (USB_H_BBLERRMSK4_V << USB_H_BBLERRMSK4_S)
#define USB_H_BBLERRMSK4_V  0x00000001
#define USB_H_BBLERRMSK4_S  8
/** USB_H_FRMOVRUNMSK4:R/W；位位置：[9]；默认值：0；帧溢出掩码0x0（Mask）：掩码溢出掩码0x1（NOMASK）：无帧溢出掩码
 */
#define USB_H_FRMOVRUNMSK4    (BIT(9))
#define USB_H_FRMOVRUNMSK4_M  (USB_H_FRMOVRUNMSK4_V << USB_H_FRMOVRUNMSK4_S)
#define USB_H_FRMOVRUNMSK4_V  0x00000001
#define USB_H_FRMOVRUNMSK4_S  9
/** USB_H_DATATGLERRMSK4:R/W；位位置：[10]；默认值：0；主机1’b0的数据切换错误掩码n分散/聚集DMA模式：掩码数据切换错误1’b1：无数据切换错误屏蔽
 */
#define USB_H_DATATGLERRMSK4    (BIT(10))
#define USB_H_DATATGLERRMSK4_M  (USB_H_DATATGLERRMSK4_V << USB_H_DATATGLERRMSK4_S)
#define USB_H_DATATGLERRMSK4_V  0x00000001
#define USB_H_DATATGLERRMSK4_S  10
/** USB_H_baintrmsk4:R/W；位位置：[11]；默认值：0；BNA（缓冲区不可用）中断屏蔽寄存器1’b0:BNA中断屏蔽1’b1：BNA中断未屏蔽
 */
#define USB_H_BNAINTRMSK4    (BIT(11))
#define USB_H_BNAINTRMSK4_M  (USB_H_BNAINTRMSK4_V << USB_H_BNAINTRMSK4_S)
#define USB_H_BNAINTRMSK4_V  0x00000001
#define USB_H_BNAINTRMSK4_S  11
/** USB_H_DESC_LST_ROLLINTRMSK4:R/W；位位置：[13]；默认值：0；描述符列表滚动中断掩码1'b0:描述符滚动中断掩码1'b1：未屏蔽描述符滚动中断
 */
#define USB_H_DESC_LST_ROLLINTRMSK4    (BIT(13))
#define USB_H_DESC_LST_ROLLINTRMSK4_M  (USB_H_DESC_LST_ROLLINTRMSK4_V << USB_H_DESC_LST_ROLLINTRMSK4_S)
#define USB_H_DESC_LST_ROLLINTRMSK4_V  0x00000001
#define USB_H_DESC_LST_ROLLINTRMSK4_S  13


/** USB_HCINT_5_REG寄存器主机通道5中断寄存器
 */
#define USB_HCINT5_REG (SOC_DPORT_USB_BASE + 0x5a8)
/** USB_H_xfercomple5:R/W1C；位位置：[0]；默认值：0；1’b0：正在传输或无活动传输1’b1：传输正常完成，无任何错误
 */
#define USB_H_XFERCOMPL5    (BIT(0))
#define USB_H_XFERCOMPL5_M  (USB_H_XFERCOMPL5_V << USB_H_XFERCOMPL5_S)
#define USB_H_XFERCOMPL5_V  0x00000001
#define USB_H_XFERCOMPL5_S  0
/** USB_H_chltd5:R/W1C；位位置：[1]；默认值：0；1’b0：频道未停止1’b1：频道已停止
 */
#define USB_H_CHHLTD5    (BIT(1))
#define USB_H_CHHLTD5_M  (USB_H_CHHLTD5_V << USB_H_CHHLTD5_S)
#define USB_H_CHHLTD5_V  0x00000001
#define USB_H_CHHLTD5_S  1
/** USB_H_AHBERR5:R/W1C；位位置：[2]；默认值：0；1’b0：无AHB错误1’b1：AHB读/写期间发生AHB错误
 */
#define USB_H_AHBERR5    (BIT(2))
#define USB_H_AHBERR5_M  (USB_H_AHBERR5_V << USB_H_AHBERR5_S)
#define USB_H_AHBERR5_V  0x00000001
#define USB_H_AHBERR5_S  2
/** USB_H_安装5：R/W1C；位位置：[3]；默认值：0；1’b0：未收到暂停响应中断1’b1：收到暂停响应
 */
#define USB_H_STALL5    (BIT(3))
#define USB_H_STALL5_M  (USB_H_STALL5_V << USB_H_STALL5_S)
#define USB_H_STALL5_V  0x00000001
#define USB_H_STALL5_S  3
/** USB_H_nak5:R/W1C；位位置：[4]；默认值：0；1’b0：未收到NAK响应中断1’b1：收到NAK应答中断
 */
#define USB_H_NACK5    (BIT(4))
#define USB_H_NACK5_M  (USB_H_NACK5_V << USB_H_NACK5_S)
#define USB_H_NACK5_V  0x00000001
#define USB_H_NACK5_S  4
/** USB_H_ACK5:R/W1C；位位置：[5]；默认值：0；1’b0：未收到或发送ACK响应中断1’b1：收到或发送的ACK响应中断
 */
#define USB_H_ACK5    (BIT(5))
#define USB_H_ACK5_M  (USB_H_ACK5_V << USB_H_ACK5_S)
#define USB_H_ACK5_V  0x00000001
#define USB_H_ACK5_S  5
/** USB_H_NYET5:R/W1C；位位置：[6]；默认值：0；1’b0：未收到NYET响应中断1’b1：收到NYET应答中断
 */
#define USB_H_NYET5    (BIT(6))
#define USB_H_NYET5_M  (USB_H_NYET5_V << USB_H_NYET5_S)
#define USB_H_NYET5_V  0x00000001
#define USB_H_NYET5_S  6
/** USB_H_xacter5:R/W1C；位位置：[7]；默认值：0；指示USB上发生以下错误之一：CRC检查失败超时位填充错误错误错误EOP
 */
#define USB_H_XACTERR5    (BIT(7))
#define USB_H_XACTERR5_M  (USB_H_XACTERR5_V << USB_H_XACTERR5_S)
#define USB_H_XACTERR5_V  0x00000001
#define USB_H_XACTERR5_S  7
/** USB_H_bbblerr5:R/W1C；位位置：[8]；默认值：0；1’b0：无巴贝尔错误1’b1：巴贝尔错误
 */
#define USB_H_BBLERR5    (BIT(8))
#define USB_H_BBLERR5_M  (USB_H_BBLERR5_V << USB_H_BBLERR5_S)
#define USB_H_BBLERR5_V  0x00000001
#define USB_H_BBLERR5_S  8
/** USB_H_FRMOVRUN5:R/W1C；位位置：[9]；默认值：0；1’b0：无帧超限1’b1：帧超限
 */
#define USB_H_FRMOVRUN5    (BIT(9))
#define USB_H_FRMOVRUN5_M  (USB_H_FRMOVRUN5_V << USB_H_FRMOVRUN5_S)
#define USB_H_FRMOVRUN5_V  0x00000001
#define USB_H_FRMOVRUN5_S  9
/** USB_H_DATATGLERR5:R/W1C；位位置：[10]；默认值：0；1’b0：无数据切换错误1’b1：数据切换错误
 */
#define USB_H_DATATGLERR5    (BIT(10))
#define USB_H_DATATGLERR5_M  (USB_H_DATATGLERR5_V << USB_H_DATATGLERR5_S)
#define USB_H_DATATGLERR5_V  0x00000001
#define USB_H_DATATGLERR5_S  10
/** USB_H_baintr5:R/W1C；位位置：[11]；默认值：0；1’b0：无BNA中断1’b1：BNA中断
 */
#define USB_H_BNAINTR5    (BIT(11))
#define USB_H_BNAINTR5_M  (USB_H_BNAINTR5_V << USB_H_BNAINTR5_S)
#define USB_H_BNAINTR5_V  0x00000001
#define USB_H_BNAINTR5_S  11
/** USB_hxcs_XACT_ERR5:R/W1C；位位置：[12]；默认值：0；1’b0：无过度交易错误1’b1：过度交易错误
 */
#define USB_H_XCS_XACT_ERR5    (BIT(12))
#define USB_H_XCS_XACT_ERR5_M  (USB_H_XCS_XACT_ERR5_V << USB_H_XCS_XACT_ERR5_S)
#define USB_H_XCS_XACT_ERR5_V  0x00000001
#define USB_H_XCS_XACT_ERR5_S  12
/** USB_H_DESC_LST_rollint5:R/W1C；位位置：[13]；默认值：0；1’b0：无描述符翻转中断1’b1：描述符翻转中断
 */
#define USB_H_DESC_LST_ROLLINTR5    (BIT(13))
#define USB_H_DESC_LST_ROLLINTR5_M  (USB_H_DESC_LST_ROLLINTR5_V << USB_H_DESC_LST_ROLLINTR5_S)
#define USB_H_DESC_LST_ROLLINTR5_V  0x00000001
#define USB_H_DESC_LST_ROLLINTR5_S  13


/** USB_HCINTMSK5_REG寄存器主机通道5中断掩码寄存器
 */
#define USB_HCINTMSK5_REG (SOC_DPORT_USB_BASE + 0x5ac)
/** USB_H_xfercomplexk5:R/W；位位置：[0]；默认值：0；1’b0：传输完成掩码1’b1：无传输完成掩码
 */
#define USB_H_XFERCOMPLMSK5    (BIT(0))
#define USB_H_XFERCOMPLMSK5_M  (USB_H_XFERCOMPLMSK5_V << USB_H_XFERCOMPLMSK5_S)
#define USB_H_XFERCOMPLMSK5_V  0x00000001
#define USB_H_XFERCOMPLMSK5_S  0
/** USB_H_chltdmsk5:R/W；位位置：[1]；默认值：0；1’b0：信道暂停掩码1’b1：无信道暂停掩码
 */
#define USB_H_CHHLTDMSK5    (BIT(1))
#define USB_H_CHHLTDMSK5_M  (USB_H_CHHLTDMSK5_V << USB_H_CHHLTDMSK5_S)
#define USB_H_CHHLTDMSK5_V  0x00000001
#define USB_H_CHHLTDMSK5_S  1
/** USB_H_ahberbrmsk5：R/W；位位置：[2]；默认值：0；1’b0:AHB错误掩码1’b1：无AHB错误屏蔽
 */
#define USB_H_AHBERRMSK5    (BIT(2))
#define USB_H_AHBERRMSK5_M  (USB_H_AHBERRMSK5_V << USB_H_AHBERRMSK5_S)
#define USB_H_AHBERRMSK5_V  0x00000001
#define USB_H_AHBERRMSK5_S  2
/** USB_H_sstallmsk5:R/W；位位置：[3]；默认值：0；1’b0：屏蔽收到的STALL响应中断1’b1：没有收到STALL响应的中断屏蔽
 */
#define USB_H_STALLMSK5    (BIT(3))
#define USB_H_STALLMSK5_M  (USB_H_STALLMSK5_V << USB_H_STALLMSK5_S)
#define USB_H_STALLMSK5_V  0x00000001
#define USB_H_STALLMSK5_S  3
/** USB_H_NAKMSK5:转/转；位位置：[4]；默认值：0；1’b0：屏蔽收到的NAK响应中断1’b1：没有收到NAK响应的中断屏蔽
 */
#define USB_H_NAKMSK5    (BIT(4))
#define USB_H_NAKMSK5_M  (USB_H_NAKMSK5_V << USB_H_NAKMSK5_S)
#define USB_H_NAKMSK5_V  0x00000001
#define USB_H_NAKMSK5_S  4
/** USB_H_ACKMSK5:R/W；位位置：[5]；默认值：0；1’b0：屏蔽接收/发送的ACK响应中断1’b1：未接收/发送ACK响应中断屏蔽
 */
#define USB_H_ACKMSK5    (BIT(5))
#define USB_H_ACKMSK5_M  (USB_H_ACKMSK5_V << USB_H_ACKMSK5_S)
#define USB_H_ACKMSK5_V  0x00000001
#define USB_H_ACKMSK5_S  5
/** USB_H_NYETMSK5:R/W；位位置：[6]；默认值：0；1’b0：屏蔽接收到的NYET响应中断1’b1：未接收到NYET响应的中断屏蔽
 */
#define USB_H_NYETMSK5    (BIT(6))
#define USB_H_NYETMSK5_M  (USB_H_NYETMSK5_V << USB_H_NYETMSK5_S)
#define USB_H_NYETMSK5_V  0x00000001
#define USB_H_NYETMSK5_S  6
/** USB_H_axaterrmsk5：R/W；位位置：[7]；默认值：0；1’b0：掩码事务错误1’b1：无事务错误掩码
 */
#define USB_H_XACTERRMSK5    (BIT(7))
#define USB_H_XACTERRMSK5_M  (USB_H_XACTERRMSK5_V << USB_H_XACTERRMSK5_S)
#define USB_H_XACTERRMSK5_V  0x00000001
#define USB_H_XACTERRMSK5_S  7
/** USB_H_bbblerrmsk5:R/W；位位置：[8]；默认值：0；巴贝尔错误掩码1’b0：掩码巴贝尔错误1’b1：无巴贝尔错误遮罩
 */
#define USB_H_BBLERRMSK5    (BIT(8))
#define USB_H_BBLERRMSK5_M  (USB_H_BBLERRMSK5_V << USB_H_BBLERRMSK5_S)
#define USB_H_BBLERRMSK5_V  0x00000001
#define USB_H_BBLERRMSK5_S  8
/** USB_H_FRMOVRUNMSK5:R/W；位位置：[9]；默认值：0；帧溢出掩码0x0（Mask）：掩码溢出掩码0x1（NOMASK）：无帧溢出掩码
 */
#define USB_H_FRMOVRUNMSK5    (BIT(9))
#define USB_H_FRMOVRUNMSK5_M  (USB_H_FRMOVRUNMSK5_V << USB_H_FRMOVRUNMSK5_S)
#define USB_H_FRMOVRUNMSK5_V  0x00000001
#define USB_H_FRMOVRUNMSK5_S  9
/** USB_H_DATATGLERRMSK5:R/W；位位置：[10]；默认值：0；主机1’b0的数据切换错误掩码n分散/聚集DMA模式：掩码数据切换错误1’b1：无数据切换错误屏蔽
 */
#define USB_H_DATATGLERRMSK5    (BIT(10))
#define USB_H_DATATGLERRMSK5_M  (USB_H_DATATGLERRMSK5_V << USB_H_DATATGLERRMSK5_S)
#define USB_H_DATATGLERRMSK5_V  0x00000001
#define USB_H_DATATGLERRMSK5_S  10
/** USB_H_baintrmsk5:R/W；位位置：[11]；默认值：0；BNA（缓冲区不可用）中断屏蔽寄存器1’b0:BNA中断屏蔽1’b1：BNA中断未屏蔽
 */
#define USB_H_BNAINTRMSK5    (BIT(11))
#define USB_H_BNAINTRMSK5_M  (USB_H_BNAINTRMSK5_V << USB_H_BNAINTRMSK5_S)
#define USB_H_BNAINTRMSK5_V  0x00000001
#define USB_H_BNAINTRMSK5_S  11
/** USB_H_DESC_LST_ROLLINTRMSK5:R/W；位位置：[13]；默认值：0；描述符列表滚动中断掩码1'b0:描述符滚动中断掩码1'b1：未屏蔽描述符滚动中断
 */
#define USB_H_DESC_LST_ROLLINTRMSK5    (BIT(13))
#define USB_H_DESC_LST_ROLLINTRMSK5_M  (USB_H_DESC_LST_ROLLINTRMSK5_V << USB_H_DESC_LST_ROLLINTRMSK5_S)
#define USB_H_DESC_LST_ROLLINTRMSK5_V  0x00000001
#define USB_H_DESC_LST_ROLLINTRMSK5_S  13


/** USB_HCINT6_REG寄存器主机通道6中断寄存器
 */
#define USB_HCINT6_REG (SOC_DPORT_USB_BASE + 0x5c8)
/** USB_H_XFERCOMPL6:R/W1C；位位置：[0]；默认值：0；1’b0：正在传输或无活动传输1’b1：传输正常完成，无任何错误
 */
#define USB_H_XFERCOMPL6    (BIT(0))
#define USB_H_XFERCOMPL6_M  (USB_H_XFERCOMPL6_V << USB_H_XFERCOMPL6_S)
#define USB_H_XFERCOMPL6_V  0x00000001
#define USB_H_XFERCOMPL6_S  0
/** USB_H_chltd6:R/W1C；位位置：[1]；默认值：0；1’b0：频道未停止1’b1：频道已停止
 */
#define USB_H_CHHLTD6    (BIT(1))
#define USB_H_CHHLTD6_M  (USB_H_CHHLTD6_V << USB_H_CHHLTD6_S)
#define USB_H_CHHLTD6_V  0x00000001
#define USB_H_CHHLTD6_S  1
/** USB_H_ahber6:R/W1C；位位置：[2]；默认值：0；1’b0：无AHB错误1’b1：AHB读/写期间发生AHB错误
 */
#define USB_H_AHBERR6    (BIT(2))
#define USB_H_AHBERR6_M  (USB_H_AHBERR6_V << USB_H_AHBERR6_S)
#define USB_H_AHBERR6_V  0x00000001
#define USB_H_AHBERR6_S  2
/** USB_H_安装6：R/W1C；位位置：[3]；默认值：0；1’b0：未收到暂停响应中断1’b1：收到暂停响应
 */
#define USB_H_STALL6    (BIT(3))
#define USB_H_STALL6_M  (USB_H_STALL6_V << USB_H_STALL6_S)
#define USB_H_STALL6_V  0x00000001
#define USB_H_STALL6_S  3
/** USB_H_nak6:R/W1C；位位置：[4]；默认值：0；1’b0：未收到NAK响应中断1’b1：收到NAK应答中断
 */
#define USB_H_NACK6    (BIT(4))
#define USB_H_NACK6_M  (USB_H_NACK6_V << USB_H_NACK6_S)
#define USB_H_NACK6_V  0x00000001
#define USB_H_NACK6_S  4
/** USB_H_ACK6:R/W1C；位位置：[5]；默认值：0；1’b0：未收到或发送ACK响应中断1’b1：收到或发送的ACK响应中断
 */
#define USB_H_ACK6    (BIT(5))
#define USB_H_ACK6_M  (USB_H_ACK6_V << USB_H_ACK6_S)
#define USB_H_ACK6_V  0x00000001
#define USB_H_ACK6_S  5
/** USB_H_NYET6:R/W1C；位位置：[6]；默认值：0；1’b0：未收到NYET响应中断1’b1：收到NYET应答中断
 */
#define USB_H_NYET6    (BIT(6))
#define USB_H_NYET6_M  (USB_H_NYET6_V << USB_H_NYET6_S)
#define USB_H_NYET6_V  0x00000001
#define USB_H_NYET6_S  6
/** USB_H_xacter6:R/W1C；位位置：[7]；默认值：0；指示USB上发生以下错误之一：CRC检查失败超时位填充错误错误错误EOP
 */
#define USB_H_XACTERR6    (BIT(7))
#define USB_H_XACTERR6_M  (USB_H_XACTERR6_V << USB_H_XACTERR6_S)
#define USB_H_XACTERR6_V  0x00000001
#define USB_H_XACTERR6_S  7
/** USB_H_bbblerr6:R/W1C；位位置：[8]；默认值：0；1’b0：无巴贝尔错误1’b1：巴贝尔错误
 */
#define USB_H_BBLERR6    (BIT(8))
#define USB_H_BBLERR6_M  (USB_H_BBLERR6_V << USB_H_BBLERR6_S)
#define USB_H_BBLERR6_V  0x00000001
#define USB_H_BBLERR6_S  8
/** USB_H_FRMOVRUN6:R/W1C；位位置：[9]；默认值：0；1’b0：无帧超限1’b1：帧超限
 */
#define USB_H_FRMOVRUN6    (BIT(9))
#define USB_H_FRMOVRUN6_M  (USB_H_FRMOVRUN6_V << USB_H_FRMOVRUN6_S)
#define USB_H_FRMOVRUN6_V  0x00000001
#define USB_H_FRMOVRUN6_S  9
/** USB_H_DATATGLERR6:R/W1C；位位置：[10]；默认值：0；1’b0：无数据切换错误1’b1：数据切换错误
 */
#define USB_H_DATATGLERR6    (BIT(10))
#define USB_H_DATATGLERR6_M  (USB_H_DATATGLERR6_V << USB_H_DATATGLERR6_S)
#define USB_H_DATATGLERR6_V  0x00000001
#define USB_H_DATATGLERR6_S  10
/** USB_H_baintr6:R/W1C；位位置：[11]；默认值：0；1’b0：无BNA中断1’b1：BNA中断
 */
#define USB_H_BNAINTR6    (BIT(11))
#define USB_H_BNAINTR6_M  (USB_H_BNAINTR6_V << USB_H_BNAINTR6_S)
#define USB_H_BNAINTR6_V  0x00000001
#define USB_H_BNAINTR6_S  11
/** USB_hxcs_XACT_ERR6:R/W1C；位位置：[12]；默认值：0；1’b0：无过度交易错误1’b1：过度交易错误
 */
#define USB_H_XCS_XACT_ERR6    (BIT(12))
#define USB_H_XCS_XACT_ERR6_M  (USB_H_XCS_XACT_ERR6_V << USB_H_XCS_XACT_ERR6_S)
#define USB_H_XCS_XACT_ERR6_V  0x00000001
#define USB_H_XCS_XACT_ERR6_S  12
/** USB_H_DESC_LST_rollintra:R/W1C；位位置：[13]；默认值：0；1’b0：无描述符翻转中断1’b1：描述符翻转中断
 */
#define USB_H_DESC_LST_ROLLINTR6    (BIT(13))
#define USB_H_DESC_LST_ROLLINTR6_M  (USB_H_DESC_LST_ROLLINTR6_V << USB_H_DESC_LST_ROLLINTR6_S)
#define USB_H_DESC_LST_ROLLINTR6_V  0x00000001
#define USB_H_DESC_LST_ROLLINTR6_S  13


/** USB_HCINTMSK6_REG寄存器主机通道6中断掩码寄存器
 */
#define USB_HCINTMSK6_REG (SOC_DPORT_USB_BASE + 0x5cc)
/** USB_H_xfercomplexk6:R/W；位位置：[0]；默认值：0；1’b0：传输完成掩码1’b1：无传输完成掩码
 */
#define USB_H_XFERCOMPLMSK6    (BIT(0))
#define USB_H_XFERCOMPLMSK6_M  (USB_H_XFERCOMPLMSK6_V << USB_H_XFERCOMPLMSK6_S)
#define USB_H_XFERCOMPLMSK6_V  0x00000001
#define USB_H_XFERCOMPLMSK6_S  0
/** USB_H_chltdmsk6:R/W；位位置：[1]；默认值：0；1’b0：信道暂停掩码1’b1：无信道暂停掩码
 */
#define USB_H_CHHLTDMSK6    (BIT(1))
#define USB_H_CHHLTDMSK6_M  (USB_H_CHHLTDMSK6_V << USB_H_CHHLTDMSK6_S)
#define USB_H_CHHLTDMSK6_V  0x00000001
#define USB_H_CHHLTDMSK6_S  1
/** USB_H_AHBERRMSK6:R/W；位位置：[2]；默认值：0；1’b0:AHB错误掩码1’b1：无AHB错误屏蔽
 */
#define USB_H_AHBERRMSK6    (BIT(2))
#define USB_H_AHBERRMSK6_M  (USB_H_AHBERRMSK6_V << USB_H_AHBERRMSK6_S)
#define USB_H_AHBERRMSK6_V  0x00000001
#define USB_H_AHBERRMSK6_S  2
/** USB_H_sstallmsk6:R/W；位位置：[3]；默认值：0；1’b0：屏蔽收到的STALL响应中断1’b1：没有收到STALL响应的中断屏蔽
 */
#define USB_H_STALLMSK6    (BIT(3))
#define USB_H_STALLMSK6_M  (USB_H_STALLMSK6_V << USB_H_STALLMSK6_S)
#define USB_H_STALLMSK6_V  0x00000001
#define USB_H_STALLMSK6_S  3
/** USB_H_NAKMSK6:R/W；位位置：[4]；默认值：0；1’b0：屏蔽收到的NAK响应中断1’b1：没有收到NAK响应的中断屏蔽
 */
#define USB_H_NAKMSK6    (BIT(4))
#define USB_H_NAKMSK6_M  (USB_H_NAKMSK6_V << USB_H_NAKMSK6_S)
#define USB_H_NAKMSK6_V  0x00000001
#define USB_H_NAKMSK6_S  4
/** USB_H_ACKMSK6:R/W；位位置：[5]；默认值：0；1’b0：屏蔽接收/发送的ACK响应中断1’b1：未接收/发送ACK响应中断屏蔽
 */
#define USB_H_ACKMSK6    (BIT(5))
#define USB_H_ACKMSK6_M  (USB_H_ACKMSK6_V << USB_H_ACKMSK6_S)
#define USB_H_ACKMSK6_V  0x00000001
#define USB_H_ACKMSK6_S  5
/** USB_H_NYETMSK6:R/W；位位置：[6]；默认值：0；1’b0：屏蔽接收到的NYET响应中断1’b1：未接收到NYET响应的中断屏蔽
 */
#define USB_H_NYETMSK6    (BIT(6))
#define USB_H_NYETMSK6_M  (USB_H_NYETMSK6_V << USB_H_NYETMSK6_S)
#define USB_H_NYETMSK6_V  0x00000001
#define USB_H_NYETMSK6_S  6
/** USB_H_axaterrmsk6:R/W；位位置：[7]；默认值：0；1’b0：掩码事务错误1’b1：无事务错误掩码
 */
#define USB_H_XACTERRMSK6    (BIT(7))
#define USB_H_XACTERRMSK6_M  (USB_H_XACTERRMSK6_V << USB_H_XACTERRMSK6_S)
#define USB_H_XACTERRMSK6_V  0x00000001
#define USB_H_XACTERRMSK6_S  7
/** USB_H_bbblerrmsk6:R/W；位位置：[8]；默认值：0；巴贝尔错误掩码1’b0：掩码巴贝尔错误1’b1：无巴贝尔错误遮罩
 */
#define USB_H_BBLERRMSK6    (BIT(8))
#define USB_H_BBLERRMSK6_M  (USB_H_BBLERRMSK6_V << USB_H_BBLERRMSK6_S)
#define USB_H_BBLERRMSK6_V  0x00000001
#define USB_H_BBLERRMSK6_S  8
/** USB_H_FRMOVRUNMSK6:R/W；位位置：[9]；默认值：0；帧溢出掩码0x0（Mask）：掩码溢出掩码0x1（NOMASK）：无帧溢出掩码
 */
#define USB_H_FRMOVRUNMSK6    (BIT(9))
#define USB_H_FRMOVRUNMSK6_M  (USB_H_FRMOVRUNMSK6_V << USB_H_FRMOVRUNMSK6_S)
#define USB_H_FRMOVRUNMSK6_V  0x00000001
#define USB_H_FRMOVRUNMSK6_S  9
/** USB_H_DATATGLERRMSK6:R/W；位位置：[10]；默认值：0；主机1’b0的数据切换错误掩码n分散/聚集DMA模式：掩码数据切换错误1’b1：无数据切换错误屏蔽
 */
#define USB_H_DATATGLERRMSK6    (BIT(10))
#define USB_H_DATATGLERRMSK6_M  (USB_H_DATATGLERRMSK6_V << USB_H_DATATGLERRMSK6_S)
#define USB_H_DATATGLERRMSK6_V  0x00000001
#define USB_H_DATATGLERRMSK6_S  10
/** USB_H_baintrmsk6:R/W；位位置：[11]；默认值：0；BNA（缓冲区不可用）中断屏蔽寄存器1’b0:BNA中断屏蔽1’b1：BNA中断未屏蔽
 */
#define USB_H_BNAINTRMSK6    (BIT(11))
#define USB_H_BNAINTRMSK6_M  (USB_H_BNAINTRMSK6_V << USB_H_BNAINTRMSK6_S)
#define USB_H_BNAINTRMSK6_V  0x00000001
#define USB_H_BNAINTRMSK6_S  11
/** USB_H_DESC_LST_ROLLINTRMSK6:R/W；位位置：[13]；默认值：0；描述符列表滚动中断掩码1'b0:描述符滚动中断掩码1'b1：未屏蔽描述符滚动中断
 */
#define USB_H_DESC_LST_ROLLINTRMSK6    (BIT(13))
#define USB_H_DESC_LST_ROLLINTRMSK6_M  (USB_H_DESC_LST_ROLLINTRMSK6_V << USB_H_DESC_LST_ROLLINTRMSK6_S)
#define USB_H_DESC_LST_ROLLINTRMSK6_V  0x00000001
#define USB_H_DESC_LST_ROLLINTRMSK6_S  13


/** USB_HCINT7_REG寄存器主机通道7中断寄存器
 */
#define USB_HCINT7_REG (SOC_DPORT_USB_BASE + 0x5e8)
/** USB_H_xfercomple7:R/W1C；位位置：[0]；默认值：0；1’b0：正在传输或无活动传输1’b1：传输正常完成，无任何错误
 */
#define USB_H_XFERCOMPL7    (BIT(0))
#define USB_H_XFERCOMPL7_M  (USB_H_XFERCOMPL7_V << USB_H_XFERCOMPL7_S)
#define USB_H_XFERCOMPL7_V  0x00000001
#define USB_H_XFERCOMPL7_S  0
/** USB_H_chltd7:R/W1C；位位置：[1]；默认值：0；1’b0：频道未停止1’b1：频道已停止
 */
#define USB_H_CHHLTD7    (BIT(1))
#define USB_H_CHHLTD7_M  (USB_H_CHHLTD7_V << USB_H_CHHLTD7_S)
#define USB_H_CHHLTD7_V  0x00000001
#define USB_H_CHHLTD7_S  1
/** USB_H_ahber7:R/W1C；位位置：[2]；默认值：0；1’b0：无AHB错误1’b1：AHB读/写期间发生AHB错误
 */
#define USB_H_AHBERR7    (BIT(2))
#define USB_H_AHBERR7_M  (USB_H_AHBERR7_V << USB_H_AHBERR7_S)
#define USB_H_AHBERR7_V  0x00000001
#define USB_H_AHBERR7_S  2
/** USB_H_安装7：R/W1C；位位置：[3]；默认值：0；1’b0：未收到暂停响应中断1’b1：收到暂停响应
 */
#define USB_H_STALL7    (BIT(3))
#define USB_H_STALL7_M  (USB_H_STALL7_V << USB_H_STALL7_S)
#define USB_H_STALL7_V  0x00000001
#define USB_H_STALL7_S  3
/** USB_H_nak7:R/W1C；位位置：[4]；默认值：0；1’b0：未收到NAK响应中断1’b1：收到NAK应答中断
 */
#define USB_H_NACK7    (BIT(4))
#define USB_H_NACK7_M  (USB_H_NACK7_V << USB_H_NACK7_S)
#define USB_H_NACK7_V  0x00000001
#define USB_H_NACK7_S  4
/** USB_H_ACK7:R/W1C；位位置：[5]；默认值：0；1’b0：未收到或发送ACK响应中断1’b1：收到或发送的ACK响应中断
 */
#define USB_H_ACK7    (BIT(5))
#define USB_H_ACK7_M  (USB_H_ACK7_V << USB_H_ACK7_S)
#define USB_H_ACK7_V  0x00000001
#define USB_H_ACK7_S  5
/** USB_H_NYET7:R/W1C；位位置：[6]；默认值：0；1’b0：未收到NYET响应中断1’b1：收到NYET应答中断
 */
#define USB_H_NYET7    (BIT(6))
#define USB_H_NYET7_M  (USB_H_NYET7_V << USB_H_NYET7_S)
#define USB_H_NYET7_V  0x00000001
#define USB_H_NYET7_S  6
/** USB_H_xacter7:R/W1C；位位置：[7]；默认值：0；指示USB上发生以下错误之一：CRC检查失败超时位填充错误错误错误EOP
 */
#define USB_H_XACTERR7    (BIT(7))
#define USB_H_XACTERR7_M  (USB_H_XACTERR7_V << USB_H_XACTERR7_S)
#define USB_H_XACTERR7_V  0x00000001
#define USB_H_XACTERR7_S  7
/** USB_H_bbblerr7:R/W1C；位位置：[8]；默认值：0；1’b0：无巴贝尔错误1’b1：巴贝尔错误
 */
#define USB_H_BBLERR7    (BIT(8))
#define USB_H_BBLERR7_M  (USB_H_BBLERR7_V << USB_H_BBLERR7_S)
#define USB_H_BBLERR7_V  0x00000001
#define USB_H_BBLERR7_S  8
/** USB_H_FRMOVRUN7:R/W1C；位位置：[9]；默认值：0；1’b0：无帧超限1’b1：帧超限
 */
#define USB_H_FRMOVRUN7    (BIT(9))
#define USB_H_FRMOVRUN7_M  (USB_H_FRMOVRUN7_V << USB_H_FRMOVRUN7_S)
#define USB_H_FRMOVRUN7_V  0x00000001
#define USB_H_FRMOVRUN7_S  9
/** USB_H_DATATGLERR7:R/W1C；位位置：[10]；默认值：0；1’b0：无数据切换错误1’b1：数据切换错误
 */
#define USB_H_DATATGLERR7    (BIT(10))
#define USB_H_DATATGLERR7_M  (USB_H_DATATGLERR7_V << USB_H_DATATGLERR7_S)
#define USB_H_DATATGLERR7_V  0x00000001
#define USB_H_DATATGLERR7_S  10
/** USB_H_baintr7:R/W1C；位位置：[11]；默认值：0；1’b0：无BNA中断1’b1：BNA中断
 */
#define USB_H_BNAINTR7    (BIT(11))
#define USB_H_BNAINTR7_M  (USB_H_BNAINTR7_V << USB_H_BNAINTR7_S)
#define USB_H_BNAINTR7_V  0x00000001
#define USB_H_BNAINTR7_S  11
/** USB_hxcs_XACT_ERR7:R/W1C；位位置：[12]；默认值：0；1’b0：无过度交易错误1’b1：过度交易错误
 */
#define USB_H_XCS_XACT_ERR7    (BIT(12))
#define USB_H_XCS_XACT_ERR7_M  (USB_H_XCS_XACT_ERR7_V << USB_H_XCS_XACT_ERR7_S)
#define USB_H_XCS_XACT_ERR7_V  0x00000001
#define USB_H_XCS_XACT_ERR7_S  12
/** USB_H_DESC_LST_ROLLINTR7:R/W1C；位位置：[13]；默认值：0；1’b0：无描述符翻转中断1’b1：描述符翻转中断
 */
#define USB_H_DESC_LST_ROLLINTR7    (BIT(13))
#define USB_H_DESC_LST_ROLLINTR7_M  (USB_H_DESC_LST_ROLLINTR7_V << USB_H_DESC_LST_ROLLINTR7_S)
#define USB_H_DESC_LST_ROLLINTR7_V  0x00000001
#define USB_H_DESC_LST_ROLLINTR7_S  13


/** USB_HCINTMSK7_REG寄存器主机通道7中断掩码寄存器
 */
#define USB_HCINTMSK7_REG (SOC_DPORT_USB_BASE + 0x5ec)
/** USB_H_xfercomplexk7:R/W；位位置：[0]；默认值：0；1’b0：传输完成掩码1’b1：无传输完成掩码
 */
#define USB_H_XFERCOMPLMSK7    (BIT(0))
#define USB_H_XFERCOMPLMSK7_M  (USB_H_XFERCOMPLMSK7_V << USB_H_XFERCOMPLMSK7_S)
#define USB_H_XFERCOMPLMSK7_V  0x00000001
#define USB_H_XFERCOMPLMSK7_S  0
/** USB_H_chltdmsk7:R/W；位位置：[1]；默认值：0；1’b0：信道暂停掩码1’b1：无信道暂停掩码
 */
#define USB_H_CHHLTDMSK7    (BIT(1))
#define USB_H_CHHLTDMSK7_M  (USB_H_CHHLTDMSK7_V << USB_H_CHHLTDMSK7_S)
#define USB_H_CHHLTDMSK7_V  0x00000001
#define USB_H_CHHLTDMSK7_S  1
/** USB_H_AHBERRMSK7:R/W；位位置：[2]；默认值：0；1’b0:AHB错误掩码1’b1：无AHB错误屏蔽
 */
#define USB_H_AHBERRMSK7    (BIT(2))
#define USB_H_AHBERRMSK7_M  (USB_H_AHBERRMSK7_V << USB_H_AHBERRMSK7_S)
#define USB_H_AHBERRMSK7_V  0x00000001
#define USB_H_AHBERRMSK7_S  2
/** USB_H_安装msk7:R/W；位位置：[3]；默认值：0；1’b0：屏蔽收到的STALL响应中断1’b1：没有收到STALL响应的中断屏蔽
 */
#define USB_H_STALLMSK7    (BIT(3))
#define USB_H_STALLMSK7_M  (USB_H_STALLMSK7_V << USB_H_STALLMSK7_S)
#define USB_H_STALLMSK7_V  0x00000001
#define USB_H_STALLMSK7_S  3
/** USB_H_akmsk7:R/W；位位置：[4]；默认值：0；1’b0：屏蔽收到的NAK响应中断1’b1：没有收到NAK响应的中断屏蔽
 */
#define USB_H_NAKMSK7    (BIT(4))
#define USB_H_NAKMSK7_M  (USB_H_NAKMSK7_V << USB_H_NAKMSK7_S)
#define USB_H_NAKMSK7_V  0x00000001
#define USB_H_NAKMSK7_S  4
/** USB_H_ACKMSK7:R/W；位位置：[5]；默认值：0；1’b0：屏蔽接收/发送的ACK响应中断1’b1：未接收/发送ACK响应中断屏蔽
 */
#define USB_H_ACKMSK7    (BIT(5))
#define USB_H_ACKMSK7_M  (USB_H_ACKMSK7_V << USB_H_ACKMSK7_S)
#define USB_H_ACKMSK7_V  0x00000001
#define USB_H_ACKMSK7_S  5
/** USB_H_NYETMSK7:R/W；位位置：[6]；默认值：0；1’b0：屏蔽接收到的NYET响应中断1’b1：未接收到NYET响应的中断屏蔽
 */
#define USB_H_NYETMSK7    (BIT(6))
#define USB_H_NYETMSK7_M  (USB_H_NYETMSK7_V << USB_H_NYETMSK7_S)
#define USB_H_NYETMSK7_V  0x00000001
#define USB_H_NYETMSK7_S  6
/** USB_H_axaterrmsk7:R/W；位位置：[7]；默认值：0；1’b0：掩码事务错误1’b1：无事务错误掩码
 */
#define USB_H_XACTERRMSK7    (BIT(7))
#define USB_H_XACTERRMSK7_M  (USB_H_XACTERRMSK7_V << USB_H_XACTERRMSK7_S)
#define USB_H_XACTERRMSK7_V  0x00000001
#define USB_H_XACTERRMSK7_S  7
/** USB_H_bbblerrmsk7:R/W；位位置：[8]；默认值：0；巴贝尔错误掩码1’b0：掩码巴贝尔错误1’b1：无巴贝尔错误遮罩
 */
#define USB_H_BBLERRMSK7    (BIT(8))
#define USB_H_BBLERRMSK7_M  (USB_H_BBLERRMSK7_V << USB_H_BBLERRMSK7_S)
#define USB_H_BBLERRMSK7_V  0x00000001
#define USB_H_BBLERRMSK7_S  8
/** USB_H_FRMOVRUNMSK7:R/W；位位置：[9]；默认值：0；帧溢出掩码0x0（Mask）：掩码溢出掩码0x1（NOMASK）：无帧溢出掩码
 */
#define USB_H_FRMOVRUNMSK7    (BIT(9))
#define USB_H_FRMOVRUNMSK7_M  (USB_H_FRMOVRUNMSK7_V << USB_H_FRMOVRUNMSK7_S)
#define USB_H_FRMOVRUNMSK7_V  0x00000001
#define USB_H_FRMOVRUNMSK7_S  9
/** USB_H_DATATGLERRMSK7:R/W；位位置：[10]；默认值：0；主机1’b0的数据切换错误掩码n分散/聚集DMA模式：掩码数据切换错误1’b1：无数据切换错误屏蔽
 */
#define USB_H_DATATGLERRMSK7    (BIT(10))
#define USB_H_DATATGLERRMSK7_M  (USB_H_DATATGLERRMSK7_V << USB_H_DATATGLERRMSK7_S)
#define USB_H_DATATGLERRMSK7_V  0x00000001
#define USB_H_DATATGLERRMSK7_S  10
/** USB_H_baintrmsk7:R/W；位位置：[11]；默认值：0；BNA（缓冲区不可用）中断屏蔽寄存器1’b0:BNA中断屏蔽1’b1：BNA中断未屏蔽
 */
#define USB_H_BNAINTRMSK7    (BIT(11))
#define USB_H_BNAINTRMSK7_M  (USB_H_BNAINTRMSK7_V << USB_H_BNAINTRMSK7_S)
#define USB_H_BNAINTRMSK7_V  0x00000001
#define USB_H_BNAINTRMSK7_S  11
/** USB_H_DESC_LST_ROLLINTRMSK7:R/W；位位置：[13]；默认值：0；描述符列表滚动中断掩码1'b0:描述符滚动中断掩码1'b1：未屏蔽描述符滚动中断
 */
#define USB_H_DESC_LST_ROLLINTRMSK7    (BIT(13))
#define USB_H_DESC_LST_ROLLINTRMSK7_M  (USB_H_DESC_LST_ROLLINTRMSK7_V << USB_H_DESC_LST_ROLLINTRMSK7_S)
#define USB_H_DESC_LST_ROLLINTRMSK7_V  0x00000001
#define USB_H_DESC_LST_ROLLINTRMSK7_S  13


/** USB_DIEPMSK_REG寄存器设备IN端点公共中断掩码寄存器
 */
#define USB_DIEPMSK_REG (SOC_DPORT_USB_BASE + 0x810)
/** USB_DI_XFERCOMPLMSK:R/W；位位置：[0]；默认值：0；0x0：掩码传输完成中断0x1：无传输完成中断掩码
 */
#define USB_DI_XFERCOMPLMSK    (BIT(0))
#define USB_DI_XFERCOMPLMSK_M  (USB_DI_XFERCOMPLMSK_V << USB_DI_XFERCOMPLMSK_S)
#define USB_DI_XFERCOMPLMSK_V  0x00000001
#define USB_DI_XFERCOMPLMSK_S  0
/** USB_DI_EPDISBLDMSK:R/W；位位置：[1]；默认值：0；0x0：屏蔽端点禁用中断0x1：无端点禁用中断掩码
 */
#define USB_DI_EPDISBLDMSK    (BIT(1))
#define USB_DI_EPDISBLDMSK_M  (USB_DI_EPDISBLDMSK_V << USB_DI_EPDISBLDMSK_S)
#define USB_DI_EPDISBLDMSK_V  0x00000001
#define USB_DI_EPDISBLDMSK_S  1
/** USB_DI_AHBERMSK:R/W；位位置：[2]；默认值：0；0x0：屏蔽AHB错误中断0x1：无AHB错误干扰屏蔽
 */
#define USB_DI_AHBERMSK    (BIT(2))
#define USB_DI_AHBERMSK_M  (USB_DI_AHBERMSK_V << USB_DI_AHBERMSK_S)
#define USB_DI_AHBERMSK_V  0x00000001
#define USB_DI_AHBERMSK_S  2
/** USB_TIMEOUTMSK:R/W；位位置：[3]；默认值：0；0x0：掩码超时条件中断0x1：无超时条件中断掩码
 */
#define USB_TIMEOUTMSK    (BIT(3))
#define USB_TIMEOUTMSK_M  (USB_TIMEOUTMSK_V << USB_TIMEOUTMSK_S)
#define USB_TIMEOUTMSK_V  0x00000001
#define USB_TIMEOUTMSK_S  3
/** USB_INTKNTXFEMPMSK:R/W；位位置：[4]；默认值：0；0x0：TxFIFO空中断时接收到掩码IN令牌0x1：TxFIFO空中断时未接收到IN令牌
 */
#define USB_INTKNTXFEMPMSK    (BIT(4))
#define USB_INTKNTXFEMPMSK_M  (USB_INTKNTXFEMPMSK_V << USB_INTKNTXFEMPMSK_S)
#define USB_INTKNTXFEMPMSK_V  0x00000001
#define USB_INTKNTXFEMPMSK_S  4
/** USB_intknepmissk:R/W；位位置：[5]；默认值：0；0x0:接收到带有EP不匹配中断的掩码IN令牌0x1：没有接收到带有EPMismatch中断的掩码IN令牌
 */
#define USB_INTKNEPMISMSK    (BIT(5))
#define USB_INTKNEPMISMSK_M  (USB_INTKNEPMISMSK_V << USB_INTKNEPMISMSK_S)
#define USB_INTKNEPMISMSK_V  0x00000001
#define USB_INTKNEPMISMSK_S  5
/** USB_INEPNAKEFFMSK:R/W；位位置：[6]；默认值：0；0x0：屏蔽IN端点NAK有效中断0x1：无IN端点NAK有效中断掩码
 */
#define USB_INEPNAKEFFMSK    (BIT(6))
#define USB_INEPNAKEFFMSK_M  (USB_INEPNAKEFFMSK_V << USB_INEPNAKEFFMSK_S)
#define USB_INEPNAKEFFMSK_V  0x00000001
#define USB_INEPNAKEFFMSK_S  6
/** USB_TXFIFOUNDRNMSK:R/W；位位置：[8]；默认值：0；0x0：屏蔽Fifo欠载中断0x1：无Fifo欠运行中断掩码
 */
#define USB_TXFIFOUNDRNMSK    (BIT(8))
#define USB_TXFIFOUNDRNMSK_M  (USB_TXFIFOUNDRNMSK_V << USB_TXFIFOUNDRNMSK_S)
#define USB_TXFIFOUNDRNMSK_V  0x00000001
#define USB_TXFIFOUNDRNMSK_S  8
/** USB_BNAININTRMSK:R/W；位位置：[9]；默认值：0；0x0：屏蔽BNA中断0x1：无BNA中断屏蔽
 */
#define USB_BNAININTRMSK    (BIT(9))
#define USB_BNAININTRMSK_M  (USB_BNAININTRMSK_V << USB_BNAININTRMSK_S)
#define USB_BNAININTRMSK_V  0x00000001
#define USB_BNAININTRMSK_S  9
/** USB_DI_NAKMSK:R/W；位位置：[13]；默认值：0；0x0：掩码NAK中断0x1：无掩码NAK干扰
 */
#define USB_DI_NAKMSK    (BIT(13))
#define USB_DI_NAKMSK_M  (USB_DI_NAKMSK_V << USB_DI_NAKMSK_S)
#define USB_DI_NAKMSK_V  0x00000001
#define USB_DI_NAKMSK_S  13


/** USB_DOEPMSK_REG寄存器设备输出端点公共中断掩码寄存器
 */
#define USB_DOEPMSK_REG (SOC_DPORT_USB_BASE + 0x814)
/** USB_xfer完成：R/W；位位置：[0]；默认值：0；0x0：掩码传输完成中断0x1：无传输完成中断掩码
 */
#define USB_XFERCOMPLMSK    (BIT(0))
#define USB_XFERCOMPLMSK_M  (USB_XFERCOMPLMSK_V << USB_XFERCOMPLMSK_S)
#define USB_XFERCOMPLMSK_V  0x00000001
#define USB_XFERCOMPLMSK_S  0
/** USB_epdispldmsk:R/W；位位置：[1]；默认值：0；0x0：屏蔽端点禁用中断0x1：无端点禁用中断掩码
 */
#define USB_EPDISBLDMSK    (BIT(1))
#define USB_EPDISBLDMSK_M  (USB_EPDISBLDMSK_V << USB_EPDISBLDMSK_S)
#define USB_EPDISBLDMSK_V  0x00000001
#define USB_EPDISBLDMSK_S  1
/** USB_AHBERMSK:R/W；位位置：[2]；默认值：0；0x0：屏蔽AHB错误中断0x1：无AHB错误干扰屏蔽
 */
#define USB_AHBERMSK    (BIT(2))
#define USB_AHBERMSK_M  (USB_AHBERMSK_V << USB_AHBERMSK_S)
#define USB_AHBERMSK_V  0x00000001
#define USB_AHBERMSK_S  2
/** USB_SETUPMSK:R/W；位位置：[3]；默认值：0；0x0：屏蔽设置阶段完成中断0x1：无设置阶段完成的中断屏蔽
 */
#define USB_SETUPMSK    (BIT(3))
#define USB_SETUPMSK_M  (USB_SETUPMSK_V << USB_SETUPMSK_S)
#define USB_SETUPMSK_V  0x00000001
#define USB_SETUPMSK_S  3
/** USB_OUTTKNEPDISMSK:R/W；位位置：[4]；默认值：0；0x0：禁用端点时接收到屏蔽OUT令牌中断0x1：禁用终结点时未接收到OUT令牌中断屏蔽
 */
#define USB_OUTTKNEPDISMSK    (BIT(4))
#define USB_OUTTKNEPDISMSK_M  (USB_OUTTKNEPDISMSK_V << USB_OUTTKNEPDISMSK_S)
#define USB_OUTTKNEPDISMSK_V  0x00000001
#define USB_OUTTKNEPDISMSK_S  4
/** USB_STSPHSERCVDMSK:R/W；位位置：[5]；默认值：0；0x0：状态阶段已接收掩码0x1：无状态阶段已收到掩码
 */
#define USB_STSPHSERCVDMSK    (BIT(5))
#define USB_STSPHSERCVDMSK_M  (USB_STSPHSERCVDMSK_V << USB_STSPHSERCVDMSK_S)
#define USB_STSPHSERCVDMSK_V  0x00000001
#define USB_STSPHSERCVDMSK_S  5
/** USB_BACK2BACKSETUP:R/W；位位置：[6]；默认值：0；0x0：屏蔽接收到的背靠背设置数据包中断0x1：没有接收到背靠背设置包中断屏蔽
 */
#define USB_BACK2BACKSETUP    (BIT(6))
#define USB_BACK2BACKSETUP_M  (USB_BACK2BACKSETUP_V << USB_BACK2BACKSETUP_S)
#define USB_BACK2BACKSETUP_V  0x00000001
#define USB_BACK2BACKSETUP_S  6
/** USB_OUTPKTERRMSK:R/W；位位置：[8]；默认值：0；0x0：屏蔽OUT数据包错误中断0x1：无OUT数据包故障中断屏蔽
 */
#define USB_OUTPKTERRMSK    (BIT(8))
#define USB_OUTPKTERRMSK_M  (USB_OUTPKTERRMSK_V << USB_OUTPKTERRMSK_S)
#define USB_OUTPKTERRMSK_V  0x00000001
#define USB_OUTPKTERRMSK_S  8
/** USB_bnaoutitrmsk:R/W；位位置：[9]；默认值：0；0x0：屏蔽BNA中断0x1：无BNA中断屏蔽
 */
#define USB_BNAOUTINTRMSK    (BIT(9))
#define USB_BNAOUTINTRMSK_M  (USB_BNAOUTINTRMSK_V << USB_BNAOUTINTRMSK_S)
#define USB_BNAOUTINTRMSK_V  0x00000001
#define USB_BNAOUTINTRMSK_S  9
/** USB_BBLEERRMSK:R/W；位位置：[12]；默认值：0；0x0：屏蔽巴氏错误中断0x1：无巴氏错误中断掩码
 */
#define USB_BBLEERRMSK    (BIT(12))
#define USB_BBLEERRMSK_M  (USB_BBLEERRMSK_V << USB_BBLEERRMSK_S)
#define USB_BBLEERRMSK_V  0x00000001
#define USB_BBLEERRMSK_S  12
/** USB_NAKMSK:R/W；位位置：[13]；默认值：0；0x0：掩码NAK中断0x1：无NAK中断掩码
 */
#define USB_NAKMSK    (BIT(13))
#define USB_NAKMSK_M  (USB_NAKMSK_V << USB_NAKMSK_S)
#define USB_NAKMSK_V  0x00000001
#define USB_NAKMSK_S  13
/** USB_NYETMSK:R/W；位位置：[14]；默认值：0；NYET中断掩码0x0：屏蔽NYET中断0x1：无NYET中断屏蔽
 */
#define USB_NYETMSK    (BIT(14))
#define USB_NYETMSK_M  (USB_NYETMSK_V << USB_NYETMSK_S)
#define USB_NYETMSK_V  0x00000001
#define USB_NYETMSK_S  14


/** USB_DAINT_REG寄存器设备所有端点中断寄存器
 */
#define USB_DAINT_REG (SOC_DPORT_USB_BASE + 0x818)
/** USB_INEPINT0:RO；位位置：[0]；默认值：0；IN端点0中断位。
 */
#define USB_INEPINT0    (BIT(0))
#define USB_INEPINT0_M  (USB_INEPINT0_V << USB_INEPINT0_S)
#define USB_INEPINT0_V  0x00000001
#define USB_INEPINT0_S  0
/** USB_INEPINT1:RO；位位置：[1]；默认值：0；IN端点1中断位。
 */
#define USB_INEPINT1    (BIT(1))
#define USB_INEPINT1_M  (USB_INEPINT1_V << USB_INEPINT1_S)
#define USB_INEPINT1_V  0x00000001
#define USB_INEPINT1_S  1
/** USB_INEPINT2:RO；位位置：[2]；默认值：0；IN端点2中断位。
 */
#define USB_INEPINT2    (BIT(2))
#define USB_INEPINT2_M  (USB_INEPINT2_V << USB_INEPINT2_S)
#define USB_INEPINT2_V  0x00000001
#define USB_INEPINT2_S  2
/** USB_INEPINT3:RO；位位置：[3]；默认值：0；IN端点3中断位。
 */
#define USB_INEPINT3    (BIT(3))
#define USB_INEPINT3_M  (USB_INEPINT3_V << USB_INEPINT3_S)
#define USB_INEPINT3_V  0x00000001
#define USB_INEPINT3_S  3
/** USB_INEPINT4:RO；位位置：[4]；默认值：0；IN端点4中断位。
 */
#define USB_INEPINT4    (BIT(4))
#define USB_INEPINT4_M  (USB_INEPINT4_V << USB_INEPINT4_S)
#define USB_INEPINT4_V  0x00000001
#define USB_INEPINT4_S  4
/** USB_INEPINT5:RO；位位置：[5]；默认值：0；IN端点5中断位。
 */
#define USB_INEPINT5    (BIT(5))
#define USB_INEPINT5_M  (USB_INEPINT5_V << USB_INEPINT5_S)
#define USB_INEPINT5_V  0x00000001
#define USB_INEPINT5_S  5
/** USB_INEPINT6:RO；位位置：[6]；默认值：0；IN端点6中断位。
 */
#define USB_INEPINT6    (BIT(6))
#define USB_INEPINT6_M  (USB_INEPINT6_V << USB_INEPINT6_S)
#define USB_INEPINT6_V  0x00000001
#define USB_INEPINT6_S  6
/** USB_outepin0:RO；位位置：[16]；默认值：0；OUT端点0中断位。
 */
#define USB_OUTEPINT0    (BIT(16))
#define USB_OUTEPINT0_M  (USB_OUTEPINT0_V << USB_OUTEPINT0_S)
#define USB_OUTEPINT0_V  0x00000001
#define USB_OUTEPINT0_S  16
/** USB_OUTEPINT1:RO；位位置：[17]；默认值：0；OUT端点1中断位。
 */
#define USB_OUTEPINT1    (BIT(17))
#define USB_OUTEPINT1_M  (USB_OUTEPINT1_V << USB_OUTEPINT1_S)
#define USB_OUTEPINT1_V  0x00000001
#define USB_OUTEPINT1_S  17
/** USB_OUTEPINT2:RO；位位置：[18]；默认值：0；OUT端点2中断位。
 */
#define USB_OUTEPINT2    (BIT(18))
#define USB_OUTEPINT2_M  (USB_OUTEPINT2_V << USB_OUTEPINT2_S)
#define USB_OUTEPINT2_V  0x00000001
#define USB_OUTEPINT2_S  18
/** USB_OUTEPINT3:RO；位位置：[19]；默认值：0；OUT端点3中断位。
 */
#define USB_OUTEPINT3    (BIT(19))
#define USB_OUTEPINT3_M  (USB_OUTEPINT3_V << USB_OUTEPINT3_S)
#define USB_OUTEPINT3_V  0x00000001
#define USB_OUTEPINT3_S  19
/** USB_outepin4:RO；位位置：[20]；默认值：0；OUT端点4中断位。
 */
#define USB_OUTEPINT4    (BIT(20))
#define USB_OUTEPINT4_M  (USB_OUTEPINT4_V << USB_OUTEPINT4_S)
#define USB_OUTEPINT4_V  0x00000001
#define USB_OUTEPINT4_S  20
/** USB_OUTEPINT5:RO；位位置：[21]；默认值：0；OUT端点5中断位。
 */
#define USB_OUTEPINT5    (BIT(21))
#define USB_OUTEPINT5_M  (USB_OUTEPINT5_V << USB_OUTEPINT5_S)
#define USB_OUTEPINT5_V  0x00000001
#define USB_OUTEPINT5_S  21
/** USB_OUTEPINT6:RO；位位置：[22]；默认值：0；OUT端点6中断位。
 */
#define USB_OUTEPINT6    (BIT(22))
#define USB_OUTEPINT6_M  (USB_OUTEPINT6_V << USB_OUTEPINT6_S)
#define USB_OUTEPINT6_V  0x00000001
#define USB_OUTEPINT6_S  22


/** USB_DAINTMSK_REG寄存器设备所有端点中断掩码寄存器
 */
#define USB_DAINTMSK_REG (SOC_DPORT_USB_BASE + 0x81c)
/** USB_INEPMSK0:R/W；位位置：[0]；默认值：0；IN端点0中断掩码位。
 */
#define USB_INEPMSK0    (BIT(0))
#define USB_INEPMSK0_M  (USB_INEPMSK0_V << USB_INEPMSK0_S)
#define USB_INEPMSK0_V  0x00000001
#define USB_INEPMSK0_S  0
/** USB_INEPMSK1:R/W；位位置：[1]；默认值：0；IN端点1中断掩码位。
 */
#define USB_INEPMSK1    (BIT(1))
#define USB_INEPMSK1_M  (USB_INEPMSK1_V << USB_INEPMSK1_S)
#define USB_INEPMSK1_V  0x00000001
#define USB_INEPMSK1_S  1
/** USB_INEPMSK2:R/W；位位置：[2]；默认值：0；IN端点2中断掩码位。
 */
#define USB_INEPMSK2    (BIT(2))
#define USB_INEPMSK2_M  (USB_INEPMSK2_V << USB_INEPMSK2_S)
#define USB_INEPMSK2_V  0x00000001
#define USB_INEPMSK2_S  2
/** USB_INEPMSK3:R/W；位位置：[3]；默认值：0；IN端点3中断掩码位。
 */
#define USB_INEPMSK3    (BIT(3))
#define USB_INEPMSK3_M  (USB_INEPMSK3_V << USB_INEPMSK3_S)
#define USB_INEPMSK3_V  0x00000001
#define USB_INEPMSK3_S  3
/** USB_INEPMSK4:R/W；位位置：[4]；默认值：0；IN端点4中断掩码位。
 */
#define USB_INEPMSK4    (BIT(4))
#define USB_INEPMSK4_M  (USB_INEPMSK4_V << USB_INEPMSK4_S)
#define USB_INEPMSK4_V  0x00000001
#define USB_INEPMSK4_S  4
/** USB_INEPMSK5:R/W；位位置：[5]；默认值：0；IN端点5中断掩码位。
 */
#define USB_INEPMSK5    (BIT(5))
#define USB_INEPMSK5_M  (USB_INEPMSK5_V << USB_INEPMSK5_S)
#define USB_INEPMSK5_V  0x00000001
#define USB_INEPMSK5_S  5
/** USB_INEPMSK6:R/W；位位置：[6]；默认值：0；IN端点6中断掩码位。
 */
#define USB_INEPMSK6    (BIT(6))
#define USB_INEPMSK6_M  (USB_INEPMSK6_V << USB_INEPMSK6_S)
#define USB_INEPMSK6_V  0x00000001
#define USB_INEPMSK6_S  6
/** USB_OUTEPMSK0:R/W；位位置：[16]；默认值：0；OUT端点0中断掩码位。
 */
#define USB_OUTEPMSK0    (BIT(16))
#define USB_OUTEPMSK0_M  (USB_OUTEPMSK0_V << USB_OUTEPMSK0_S)
#define USB_OUTEPMSK0_V  0x00000001
#define USB_OUTEPMSK0_S  16
/** USB_OUTEPMSK1:R/W；位位置：[17]；默认值：0；OUT端点1中断掩码位。
 */
#define USB_OUTEPMSK1    (BIT(17))
#define USB_OUTEPMSK1_M  (USB_OUTEPMSK1_V << USB_OUTEPMSK1_S)
#define USB_OUTEPMSK1_V  0x00000001
#define USB_OUTEPMSK1_S  17
/** USB_OUTEPMSK2:R/W；位位置：[18]；默认值：0；OUT端点2中断掩码位。
 */
#define USB_OUTEPMSK2    (BIT(18))
#define USB_OUTEPMSK2_M  (USB_OUTEPMSK2_V << USB_OUTEPMSK2_S)
#define USB_OUTEPMSK2_V  0x00000001
#define USB_OUTEPMSK2_S  18
/** USB_OUTEPMSK3:R/W；位位置：[19]；默认值：0；OUT端点3中断掩码位。
 */
#define USB_OUTEPMSK3    (BIT(19))
#define USB_OUTEPMSK3_M  (USB_OUTEPMSK3_V << USB_OUTEPMSK3_S)
#define USB_OUTEPMSK3_V  0x00000001
#define USB_OUTEPMSK3_S  19
/** USB_OUTEPMSK4:R/W；位位置：[20]；默认值：0；OUT端点4中断掩码位。
 */
#define USB_OUTEPMSK4    (BIT(20))
#define USB_OUTEPMSK4_M  (USB_OUTEPMSK4_V << USB_OUTEPMSK4_S)
#define USB_OUTEPMSK4_V  0x00000001
#define USB_OUTEPMSK4_S  20
/** USB_OUTEPMSK5:R/W；位位置：[21]；默认值：0；OUT端点5中断掩码位。
 */
#define USB_OUTEPMSK5    (BIT(21))
#define USB_OUTEPMSK5_M  (USB_OUTEPMSK5_V << USB_OUTEPMSK5_S)
#define USB_OUTEPMSK5_V  0x00000001
#define USB_OUTEPMSK5_S  21
/** USB_OUTEPMSK6:R/W；位位置：[22]；默认值：0；OUT端点6中断掩码位。
 */
#define USB_OUTEPMSK6    (BIT(22))
#define USB_OUTEPMSK6_M  (USB_OUTEPMSK6_V << USB_OUTEPMSK6_S)
#define USB_OUTEPMSK6_V  0x00000001
#define USB_OUTEPMSK6_S  22


/** USB_DIEPEMPMSK_REG寄存器设备IN终结点FIFO空中断掩码寄存器
 */
#define USB_DIEPEMPMSK_REG (SOC_DPORT_USB_BASE + 0x834)
/** USB_D_INEPTXFEMPMSK:R/W；位位置：[16:0]；默认值：0；IN EP Tx FIFO空中断掩码位0x1（EP0_Mask）：掩码IN EP0 Tx FIFO空白中断0x2中断0x80（EP7_MASK）：屏蔽EP7 Tx FIFO空中断0x100（EP8_MASK）：掩码EP8 Tx FIFO空白中断0x200（EP9_MASK0x4000（EP14_MASK）：屏蔽EP14 Tx FIFO空中断0x8000（EP15_MASK
 */
#define USB_D_INEPTXFEMPMSK    0x0000FFFF
#define USB_D_INEPTXFEMPMSK_M  (USB_D_INEPTXFEMPMSK_V << USB_D_INEPTXFEMPMSK_S)
#define USB_D_INEPTXFEMPMSK_V  0x0000FFFF
#define USB_D_INEPTXFEMPMSK_S  0


/** USB_DIEPINT0_REG寄存器设备IN端点0中断寄存器
 */
#define USB_DIEPINT0_REG (SOC_DPORT_USB_BASE + 0x908)
/** USB_D_xfercomple0:R/W1C；位位置：[0]；默认值：0；0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_D_XFERCOMPL0    (BIT(0))
#define USB_D_XFERCOMPL0_M  (USB_D_XFERCOMPL0_V << USB_D_XFERCOMPL0_S)
#define USB_D_XFERCOMPL0_V  0x00000001
#define USB_D_XFERCOMPL0_S  0
/** USB_D_epdispld0:R/W1C；位位置：[1]；默认值：0；0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_D_EPDISBLD0    (BIT(1))
#define USB_D_EPDISBLD0_M  (USB_D_EPDISBLD0_V << USB_D_EPDISBLD0_S)
#define USB_D_EPDISBLD0_V  0x00000001
#define USB_D_EPDISBLD0_S  1
/** USB_D_AHBERR0:R/W1C；位位置：[2]；默认值：0；0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_D_AHBERR0    (BIT(2))
#define USB_D_AHBERR0_M  (USB_D_AHBERR0_V << USB_D_AHBERR0_S)
#define USB_D_AHBERR0_V  0x00000001
#define USB_D_AHBERR0_S  2
/** USB_D_TIMEOUT0:R/W1C；位位置：[3]；默认值：0；0x0：无超时中断0x1：超时中断
 */
#define USB_D_TIMEOUT0    (BIT(3))
#define USB_D_TIMEOUT0_M  (USB_D_TIMEOUT0_V << USB_D_TIMEOUT0_S)
#define USB_D_TIMEOUT0_V  0x00000001
#define USB_D_TIMEOUT0_S  3
/** USB_D_intkntxemp0:R/W1C；位位置：[4]；默认值：0；0x0：TxFIFO空中断时未收到IN令牌0x1：TxFIFO空中断时收到IN令牌
 */
#define USB_D_INTKNTXFEMP0    (BIT(4))
#define USB_D_INTKNTXFEMP0_M  (USB_D_INTKNTXFEMP0_V << USB_D_INTKNTXFEMP0_S)
#define USB_D_INTKNTXFEMP0_V  0x00000001
#define USB_D_INTKNTXFEMP0_S  4
/** USB_D_INTKNEPMIS0:R/W1C；位位置：[5]；默认值：0；0x0：未接收到带EP不匹配中断的IN令牌0x1：接收到带EP-Match中断的IN代币
 */
#define USB_D_INTKNEPMIS0    (BIT(5))
#define USB_D_INTKNEPMIS0_M  (USB_D_INTKNEPMIS0_V << USB_D_INTKNEPMIS0_S)
#define USB_D_INTKNEPMIS0_V  0x00000001
#define USB_D_INTKNEPMIS0_S  5
/** USB_D_INEPNAKEFF0:R/W1C；位位置：[6]；默认值：0；IN终结点NAK有效0x0：无IN终结点NACK有效中断0x1:IN终结点NA有效中断
 */
#define USB_D_INEPNAKEFF0    (BIT(6))
#define USB_D_INEPNAKEFF0_M  (USB_D_INEPNAKEFF0_V << USB_D_INEPNAKEFF0_S)
#define USB_D_INEPNAKEFF0_V  0x00000001
#define USB_D_INEPNAKEFF0_S  6
/** USB_D_TXFEMP0:RO；位位置：[7]；默认值：0；当此端点的TxFIFO为半空或完全空时，会断言此中断0x0：无传输FIFO空中断0x1：发送FIFO空中断
 */
#define USB_D_TXFEMP0    (BIT(7))
#define USB_D_TXFEMP0_M  (USB_D_TXFEMP0_V << USB_D_TXFEMP0_S)
#define USB_D_TXFEMP0_V  0x00000001
#define USB_D_TXFEMP0_S  7
/** USB_D_TXFIFOUNDRN0:R/W1C；位位置：[8]；默认值：0；当内核在阈值模式下检测到该端点的传输FIFO欠载情况时，内核会生成该中断0x0:No FIFO underrun interrupt 0x1:FIFO Underruninterrupt
 */
#define USB_D_TXFIFOUNDRN0    (BIT(8))
#define USB_D_TXFIFOUNDRN0_M  (USB_D_TXFIFOUNDRN0_V << USB_D_TXFIFOUNDRN0_S)
#define USB_D_TXFIFOUNDRN0_V  0x00000001
#define USB_D_TXFIFOUNDRN0_S  8
/** USB_D_BNAINTR0:R/W1C；位位置：[9]；默认值：0；此位仅在启用分散/聚集DMA模式时有效。当访问的描述符未准备好供核心处理时，如主机忙或DMA已完成0x0:No BNA中断0x1:BNA中断，核心会生成此中断
 */
#define USB_D_BNAINTR0    (BIT(9))
#define USB_D_BNAINTR0_M  (USB_D_BNAINTR0_V << USB_D_BNAINTR0_S)
#define USB_D_BNAINTR0_V  0x00000001
#define USB_D_BNAINTR0_S  9
/** USB_D_PKTDRPSTS0：R/W1C；位位置：[11]；默认值：0；数据包丢弃状态。该位向应用程序指示ISOC OUT数据包已被丢弃。该位没有关联的掩码位，并且不会生成中断0x0：无中断0x1：数据包丢弃状态
 */
#define USB_D_PKTDRPSTS0    (BIT(11))
#define USB_D_PKTDRPSTS0_M  (USB_D_PKTDRPSTS0_V << USB_D_PKTDRPSTS0_S)
#define USB_D_PKTDRPSTS0_V  0x00000001
#define USB_D_PKTDRPSTS0_S  11
/** USB_D_bbleer0:R/W1C；位位置：[12]；默认值：0；当接收到端点0x0:No interrupt 0x1:BbleErr interrupt时，内核生成此中断
 */
#define USB_D_BBLEERR0    (BIT(12))
#define USB_D_BBLEERR0_M  (USB_D_BBLEERR0_V << USB_D_BBLEERR0_S)
#define USB_D_BBLEERR0_V  0x00000001
#define USB_D_BBLEERR0_S  12
/** USB_D_nakintrt0:R/W1C；位位置：[13]；默认值：0；NAK中断。当设备发送或接收NAK时，内核生成此中断0x0:无中断0x1:NAK中断
 */
#define USB_D_NAKINTRPT0    (BIT(13))
#define USB_D_NAKINTRPT0_M  (USB_D_NAKINTRPT0_V << USB_D_NAKINTRPT0_S)
#define USB_D_NAKINTRPT0_V  0x00000001
#define USB_D_NAKINTRPT0_S  13
/** USB_D_NYETINTRPT0:R/W1C；位位置：[14]；默认值：0；NYET中断。当为非同步OUT端点发送NYET响应0x0:No interrupt 0x1:NYET interrupt时，内核生成此中断
 */
#define USB_D_NYETINTRPT0    (BIT(14))
#define USB_D_NYETINTRPT0_M  (USB_D_NYETINTRPT0_V << USB_D_NYETINTRPT0_S)
#define USB_D_NYETINTRPT0_V  0x00000001
#define USB_D_NYETINTRPT0_S  14


/** USB_DIEPINT1_REG寄存器设备IN端点1中断寄存器
 */
#define USB_DIEPINT1_REG (SOC_DPORT_USB_BASE + 0x928)
/** USB_D_xfercomplex1:R/W1C；位位置：[0]；默认值：0；0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_D_XFERCOMPL1    (BIT(0))
#define USB_D_XFERCOMPL1_M  (USB_D_XFERCOMPL1_V << USB_D_XFERCOMPL1_S)
#define USB_D_XFERCOMPL1_V  0x00000001
#define USB_D_XFERCOMPL1_S  0
/** USB_D_epdispld1:R/W1C；位位置：[1]；默认值：0；0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_D_EPDISBLD1    (BIT(1))
#define USB_D_EPDISBLD1_M  (USB_D_EPDISBLD1_V << USB_D_EPDISBLD1_S)
#define USB_D_EPDISBLD1_V  0x00000001
#define USB_D_EPDISBLD1_S  1
/** USB_D_AHBERR1:R/W1C；位位置：[2]；默认值：0；0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_D_AHBERR1    (BIT(2))
#define USB_D_AHBERR1_M  (USB_D_AHBERR1_V << USB_D_AHBERR1_S)
#define USB_D_AHBERR1_V  0x00000001
#define USB_D_AHBERR1_S  2
/** USB_D_TIMEOUT1:R/W1C；位位置：[3]；默认值：0；0x0：无超时中断0x1：超时中断
 */
#define USB_D_TIMEOUT1    (BIT(3))
#define USB_D_TIMEOUT1_M  (USB_D_TIMEOUT1_V << USB_D_TIMEOUT1_S)
#define USB_D_TIMEOUT1_V  0x00000001
#define USB_D_TIMEOUT1_S  3
/** USB_D_intkntxemp1:R/W1C；位位置：[4]；默认值：0；0x0：TxFIFO空中断时未收到IN令牌0x1：TxFIFO空中断时收到IN令牌
 */
#define USB_D_INTKNTXFEMP1    (BIT(4))
#define USB_D_INTKNTXFEMP1_M  (USB_D_INTKNTXFEMP1_V << USB_D_INTKNTXFEMP1_S)
#define USB_D_INTKNTXFEMP1_V  0x00000001
#define USB_D_INTKNTXFEMP1_S  4
/** USB_D_intknepm为1:R/W1C；位位置：[5]；默认值：0；0x0：未接收到带EP不匹配中断的IN令牌0x1：接收到带EP-Match中断的IN代币
 */
#define USB_D_INTKNEPMIS1    (BIT(5))
#define USB_D_INTKNEPMIS1_M  (USB_D_INTKNEPMIS1_V << USB_D_INTKNEPMIS1_S)
#define USB_D_INTKNEPMIS1_V  0x00000001
#define USB_D_INTKNEPMIS1_S  5
/** USB_D_INEPNAKEFF1:R/W1C；位位置：[6]；默认值：0；IN终结点NAK有效0x0：无IN终结点NACK有效中断0x1:IN终结点NA有效中断
 */
#define USB_D_INEPNAKEFF1    (BIT(6))
#define USB_D_INEPNAKEFF1_M  (USB_D_INEPNAKEFF1_V << USB_D_INEPNAKEFF1_S)
#define USB_D_INEPNAKEFF1_V  0x00000001
#define USB_D_INEPNAKEFF1_S  6
/** USB_D_TXFEMP1:RO；位位置：[7]；默认值：0；当此端点的TxFIFO为半空或完全空时，会断言此中断0x0：无传输FIFO空中断0x1：发送FIFO空中断
 */
#define USB_D_TXFEMP1    (BIT(7))
#define USB_D_TXFEMP1_M  (USB_D_TXFEMP1_V << USB_D_TXFEMP1_S)
#define USB_D_TXFEMP1_V  0x00000001
#define USB_D_TXFEMP1_S  7
/** USB_D_TXFIFOUNDRN1:R/W1C；位位置：[8]；默认值：0；当内核在阈值模式下检测到该端点的传输FIFO欠载情况时，内核会生成该中断0x0:No FIFO underrun interrupt 0x1:FIFO Underruninterrupt
 */
#define USB_D_TXFIFOUNDRN1    (BIT(8))
#define USB_D_TXFIFOUNDRN1_M  (USB_D_TXFIFOUNDRN1_V << USB_D_TXFIFOUNDRN1_S)
#define USB_D_TXFIFOUNDRN1_V  0x00000001
#define USB_D_TXFIFOUNDRN1_S  8
/** USB_D_BNAINTR1:R/W1C；位位置：[9]；默认值：0；此位仅在启用分散/聚集DMA模式时有效。当访问的描述符未准备好供核心处理时，如主机忙或DMA已完成0x0:No BNA中断0x1:BNA中断，核心会生成此中断
 */
#define USB_D_BNAINTR1    (BIT(9))
#define USB_D_BNAINTR1_M  (USB_D_BNAINTR1_V << USB_D_BNAINTR1_S)
#define USB_D_BNAINTR1_V  0x00000001
#define USB_D_BNAINTR1_S  9
/** USB_D_PKTDRPSTS1：R/W1C；位位置：[11]；默认值：0；数据包丢弃状态。该位向应用程序指示ISOC OUT数据包已被丢弃。该位没有关联的掩码位，并且不会生成中断0x0：无中断0x1：数据包丢弃状态
 */
#define USB_D_PKTDRPSTS1    (BIT(11))
#define USB_D_PKTDRPSTS1_M  (USB_D_PKTDRPSTS1_V << USB_D_PKTDRPSTS1_S)
#define USB_D_PKTDRPSTS1_V  0x00000001
#define USB_D_PKTDRPSTS1_S  11
/** USB_D_bbleer1:R/W1C；位位置：[12]；默认值：0；当接收到端点0x0:No interrupt 0x1:BbleErr interrupt时，内核生成此中断
 */
#define USB_D_BBLEERR1    (BIT(12))
#define USB_D_BBLEERR1_M  (USB_D_BBLEERR1_V << USB_D_BBLEERR1_S)
#define USB_D_BBLEERR1_V  0x00000001
#define USB_D_BBLEERR1_S  12
/** USB_D_nakintrt1:R/W1C；位位置：[13]；默认值：0；NAK中断。当设备发送或接收NAK时，内核生成此中断0x0:无中断0x1:NAK中断
 */
#define USB_D_NAKINTRPT1    (BIT(13))
#define USB_D_NAKINTRPT1_M  (USB_D_NAKINTRPT1_V << USB_D_NAKINTRPT1_S)
#define USB_D_NAKINTRPT1_V  0x00000001
#define USB_D_NAKINTRPT1_S  13
/** USB_D_NYETINTRPT1:R/W1C；位位置：[14]；默认值：0；NYET中断。当为非同步OUT端点发送NYET响应0x0:No interrupt 0x1:NYET interrupt时，内核生成此中断
 */
#define USB_D_NYETINTRPT1    (BIT(14))
#define USB_D_NYETINTRPT1_M  (USB_D_NYETINTRPT1_V << USB_D_NYETINTRPT1_S)
#define USB_D_NYETINTRPT1_V  0x00000001
#define USB_D_NYETINTRPT1_S  14


/** USB_DIEPINT2_REG寄存器设备IN端点2中断寄存器
 */
#define USB_DIEPINT2_REG (SOC_DPORT_USB_BASE + 0x948)
/** USB_D_xfercomple2:R/W1C；位位置：[0]；默认值：0；0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_D_XFERCOMPL2    (BIT(0))
#define USB_D_XFERCOMPL2_M  (USB_D_XFERCOMPL2_V << USB_D_XFERCOMPL2_S)
#define USB_D_XFERCOMPL2_V  0x00000001
#define USB_D_XFERCOMPL2_S  0
/** USB_D_epdispld2:R/W1C；位位置：[1]；默认值：0；0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_D_EPDISBLD2    (BIT(1))
#define USB_D_EPDISBLD2_M  (USB_D_EPDISBLD2_V << USB_D_EPDISBLD2_S)
#define USB_D_EPDISBLD2_V  0x00000001
#define USB_D_EPDISBLD2_S  1
/** USB_D_AHBERR2:R/W1C；位位置：[2]；默认值：0；0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_D_AHBERR2    (BIT(2))
#define USB_D_AHBERR2_M  (USB_D_AHBERR2_V << USB_D_AHBERR2_S)
#define USB_D_AHBERR2_V  0x00000001
#define USB_D_AHBERR2_S  2
/** USB_D_TIMEOUT2:R/W1C；位位置：[3]；默认值：0；0x0：无超时中断0x1：超时中断
 */
#define USB_D_TIMEOUT2    (BIT(3))
#define USB_D_TIMEOUT2_M  (USB_D_TIMEOUT2_V << USB_D_TIMEOUT2_S)
#define USB_D_TIMEOUT2_V  0x00000001
#define USB_D_TIMEOUT2_S  3
/** USB_D_intkntxemp2:R/W1C；位位置：[4]；默认值：0；0x0：TxFIFO空中断时未收到IN令牌0x1：TxFIFO空中断时收到IN令牌
 */
#define USB_D_INTKNTXFEMP2    (BIT(4))
#define USB_D_INTKNTXFEMP2_M  (USB_D_INTKNTXFEMP2_V << USB_D_INTKNTXFEMP2_S)
#define USB_D_INTKNTXFEMP2_V  0x00000001
#define USB_D_INTKNTXFEMP2_S  4
/** USB_D_INTKNEPMIS2:R/W1C；位位置：[5]；默认值：0；0x0：未接收到带EP不匹配中断的IN令牌0x1：接收到带EP-Match中断的IN代币
 */
#define USB_D_INTKNEPMIS2    (BIT(5))
#define USB_D_INTKNEPMIS2_M  (USB_D_INTKNEPMIS2_V << USB_D_INTKNEPMIS2_S)
#define USB_D_INTKNEPMIS2_V  0x00000001
#define USB_D_INTKNEPMIS2_S  5
/** USB_D_INEPNAKEFF2:R/W1C；位位置：[6]；默认值：0；IN终结点NAK有效0x0：无IN终结点NACK有效中断0x1:IN终结点NA有效中断
 */
#define USB_D_INEPNAKEFF2    (BIT(6))
#define USB_D_INEPNAKEFF2_M  (USB_D_INEPNAKEFF2_V << USB_D_INEPNAKEFF2_S)
#define USB_D_INEPNAKEFF2_V  0x00000001
#define USB_D_INEPNAKEFF2_S  6
/** USB_D_TXFEMP2:RO；位位置：[7]；默认值：0；当此端点的TxFIFO为半空或完全空时，会断言此中断0x0：无传输FIFO空中断0x1：发送FIFO空中断
 */
#define USB_D_TXFEMP2    (BIT(7))
#define USB_D_TXFEMP2_M  (USB_D_TXFEMP2_V << USB_D_TXFEMP2_S)
#define USB_D_TXFEMP2_V  0x00000001
#define USB_D_TXFEMP2_S  7
/** USB_D_TXFIFOUNDRN2:R/W1C；位位置：[8]；默认值：0；当内核在阈值模式下检测到该端点的传输FIFO欠载情况时，内核会生成该中断0x0:No FIFO underrun interrupt 0x1:FIFO Underruninterrupt
 */
#define USB_D_TXFIFOUNDRN2    (BIT(8))
#define USB_D_TXFIFOUNDRN2_M  (USB_D_TXFIFOUNDRN2_V << USB_D_TXFIFOUNDRN2_S)
#define USB_D_TXFIFOUNDRN2_V  0x00000001
#define USB_D_TXFIFOUNDRN2_S  8
/** USB_D_BNAINTR2:R/W1C；位位置：[9]；默认值：0；此位仅在启用分散/聚集DMA模式时有效。当访问的描述符未准备好供核心处理时，如主机忙或DMA已完成0x0:No BNA中断0x1:BNA中断，核心会生成此中断
 */
#define USB_D_BNAINTR2    (BIT(9))
#define USB_D_BNAINTR2_M  (USB_D_BNAINTR2_V << USB_D_BNAINTR2_S)
#define USB_D_BNAINTR2_V  0x00000001
#define USB_D_BNAINTR2_S  9
/** USB_D_PKTDRPSTS2:R/W1C；位位置：[11]；默认值：0；数据包丢弃状态。该位向应用程序指示ISOC OUT数据包已被丢弃。该位没有关联的掩码位，并且不会生成中断0x0：无中断0x1：数据包丢弃状态
 */
#define USB_D_PKTDRPSTS2    (BIT(11))
#define USB_D_PKTDRPSTS2_M  (USB_D_PKTDRPSTS2_V << USB_D_PKTDRPSTS2_S)
#define USB_D_PKTDRPSTS2_V  0x00000001
#define USB_D_PKTDRPSTS2_S  11
/** USB_D_bbleer2:R/W1C；位位置：[12]；默认值：0；当接收到端点0x0:No interrupt 0x1:BbleErr interrupt时，内核生成此中断
 */
#define USB_D_BBLEERR2    (BIT(12))
#define USB_D_BBLEERR2_M  (USB_D_BBLEERR2_V << USB_D_BBLEERR2_S)
#define USB_D_BBLEERR2_V  0x00000001
#define USB_D_BBLEERR2_S  12
/** USB_D_nakintrt2:R/W1C；位位置：[13]；默认值：0；NAK中断。当设备发送或接收NAK时，内核生成此中断0x0:无中断0x1:NAK中断
 */
#define USB_D_NAKINTRPT2    (BIT(13))
#define USB_D_NAKINTRPT2_M  (USB_D_NAKINTRPT2_V << USB_D_NAKINTRPT2_S)
#define USB_D_NAKINTRPT2_V  0x00000001
#define USB_D_NAKINTRPT2_S  13
/** USB_D_NYETINTRPT2:R/W1C；位位置：[14]；默认值：0；NYET中断。当为非同步OUT端点发送NYET响应0x0:No interrupt 0x1:NYET interrupt时，内核生成此中断
 */
#define USB_D_NYETINTRPT2    (BIT(14))
#define USB_D_NYETINTRPT2_M  (USB_D_NYETINTRPT2_V << USB_D_NYETINTRPT2_S)
#define USB_D_NYETINTRPT2_V  0x00000001
#define USB_D_NYETINTRPT2_S  14


/** USB_DIEPINT3_REG寄存器设备IN终结点3中断寄存器
 */
#define USB_DIEPINT3_REG (SOC_DPORT_USB_BASE + 0x968)
/** USB_D_XFERCOMPL3:R/W1C；位位置：[0]；默认值：0；0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_D_XFERCOMPL3    (BIT(0))
#define USB_D_XFERCOMPL3_M  (USB_D_XFERCOMPL3_V << USB_D_XFERCOMPL3_S)
#define USB_D_XFERCOMPL3_V  0x00000001
#define USB_D_XFERCOMPL3_S  0
/** USB_D_epdispld3:R/W1C；位位置：[1]；默认值：0；0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_D_EPDISBLD3    (BIT(1))
#define USB_D_EPDISBLD3_M  (USB_D_EPDISBLD3_V << USB_D_EPDISBLD3_S)
#define USB_D_EPDISBLD3_V  0x00000001
#define USB_D_EPDISBLD3_S  1
/** USB_D_AHBERR3:R/W1C；位位置：[2]；默认值：0；0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_D_AHBERR3    (BIT(2))
#define USB_D_AHBERR3_M  (USB_D_AHBERR3_V << USB_D_AHBERR3_S)
#define USB_D_AHBERR3_V  0x00000001
#define USB_D_AHBERR3_S  2
/** USB_D_TIMEOUT3:R/W1C；位位置：[3]；默认值：0；0x0：无超时中断0x1：超时中断
 */
#define USB_D_TIMEOUT3    (BIT(3))
#define USB_D_TIMEOUT3_M  (USB_D_TIMEOUT3_V << USB_D_TIMEOUT3_S)
#define USB_D_TIMEOUT3_V  0x00000001
#define USB_D_TIMEOUT3_S  3
/** USB_D_intkntxemp3:R/W1C；位位置：[4]；默认值：0；0x0：TxFIFO空中断时未收到IN令牌0x1：TxFIFO空中断时收到IN令牌
 */
#define USB_D_INTKNTXFEMP3    (BIT(4))
#define USB_D_INTKNTXFEMP3_M  (USB_D_INTKNTXFEMP3_V << USB_D_INTKNTXFEMP3_S)
#define USB_D_INTKNTXFEMP3_V  0x00000001
#define USB_D_INTKNTXFEMP3_S  4
/** USB_D_INTKNEPMIS3:R/W1C；位位置：[5]；默认值：0；0x0：未接收到带EP不匹配中断的IN令牌0x1：接收到带EP-Match中断的IN代币
 */
#define USB_D_INTKNEPMIS3    (BIT(5))
#define USB_D_INTKNEPMIS3_M  (USB_D_INTKNEPMIS3_V << USB_D_INTKNEPMIS3_S)
#define USB_D_INTKNEPMIS3_V  0x00000001
#define USB_D_INTKNEPMIS3_S  5
/** USB_D_INEPNAKEFF3:R/W1C；位位置：[6]；默认值：0；IN终结点NAK有效0x0：无IN终结点NACK有效中断0x1:IN终结点NA有效中断
 */
#define USB_D_INEPNAKEFF3    (BIT(6))
#define USB_D_INEPNAKEFF3_M  (USB_D_INEPNAKEFF3_V << USB_D_INEPNAKEFF3_S)
#define USB_D_INEPNAKEFF3_V  0x00000001
#define USB_D_INEPNAKEFF3_S  6
/** USB_D_TXFEMP3:RO；位位置：[7]；默认值：0；当此端点的TxFIFO为半空或完全空时，会断言此中断0x0：无传输FIFO空中断0x1：发送FIFO空中断
 */
#define USB_D_TXFEMP3    (BIT(7))
#define USB_D_TXFEMP3_M  (USB_D_TXFEMP3_V << USB_D_TXFEMP3_S)
#define USB_D_TXFEMP3_V  0x00000001
#define USB_D_TXFEMP3_S  7
/** USB_D_TXFIFOUNDRN3:R/W1C；位位置：[8]；默认值：0；当内核在阈值模式下检测到该端点的传输FIFO欠载情况时，内核会生成该中断0x0:No FIFO underrun interrupt 0x1:FIFO Underruninterrupt
 */
#define USB_D_TXFIFOUNDRN3    (BIT(8))
#define USB_D_TXFIFOUNDRN3_M  (USB_D_TXFIFOUNDRN3_V << USB_D_TXFIFOUNDRN3_S)
#define USB_D_TXFIFOUNDRN3_V  0x00000001
#define USB_D_TXFIFOUNDRN3_S  8
/** USB_D_BNAINTR3:R/W1C；位位置：[9]；默认值：0；此位仅在启用分散/聚集DMA模式时有效。当访问的描述符未准备好供核心处理时，如主机忙或DMA已完成0x0:No BNA中断0x1:BNA中断，核心会生成此中断
 */
#define USB_D_BNAINTR3    (BIT(9))
#define USB_D_BNAINTR3_M  (USB_D_BNAINTR3_V << USB_D_BNAINTR3_S)
#define USB_D_BNAINTR3_V  0x00000001
#define USB_D_BNAINTR3_S  9
/** USB_D_PKTDRPSTS3:R/W1C；位位置：[11]；默认值：0；数据包丢弃状态。该位向应用程序指示ISOC OUT数据包已被丢弃。该位没有关联的掩码位，并且不会生成中断0x0：无中断0x1：数据包丢弃状态
 */
#define USB_D_PKTDRPSTS3    (BIT(11))
#define USB_D_PKTDRPSTS3_M  (USB_D_PKTDRPSTS3_V << USB_D_PKTDRPSTS3_S)
#define USB_D_PKTDRPSTS3_V  0x00000001
#define USB_D_PKTDRPSTS3_S  11
/** USB_D_bbleer3:R/W1C；位位置：[12]；默认值：0；当接收到端点0x0:No interrupt 0x1:BbleErr interrupt时，内核生成此中断
 */
#define USB_D_BBLEERR3    (BIT(12))
#define USB_D_BBLEERR3_M  (USB_D_BBLEERR3_V << USB_D_BBLEERR3_S)
#define USB_D_BBLEERR3_V  0x00000001
#define USB_D_BBLEERR3_S  12
/** USB_D_nakintrt3:R/W1C；位位置：[13]；默认值：0；NAK中断。当设备发送或接收NAK时，内核生成此中断0x0:无中断0x1:NAK中断
 */
#define USB_D_NAKINTRPT3    (BIT(13))
#define USB_D_NAKINTRPT3_M  (USB_D_NAKINTRPT3_V << USB_D_NAKINTRPT3_S)
#define USB_D_NAKINTRPT3_V  0x00000001
#define USB_D_NAKINTRPT3_S  13
/** USB_D_NYETINTRPT3:R/W1C；位位置：[14]；默认值：0；NYET中断。当为非同步OUT端点发送NYET响应0x0:No interrupt 0x1:NYET interrupt时，内核生成此中断
 */
#define USB_D_NYETINTRPT3    (BIT(14))
#define USB_D_NYETINTRPT3_M  (USB_D_NYETINTRPT3_V << USB_D_NYETINTRPT3_S)
#define USB_D_NYETINTRPT3_V  0x00000001
#define USB_D_NYETINTRPT3_S  14


/** USB_DIEPINT4_REG寄存器设备IN端点4中断寄存器
 */
#define USB_DIEPINT4_REG (SOC_DPORT_USB_BASE + 0x988)
/** USB_D_XFERCOMPL4:R/W1C；位位置：[0]；默认值：0；0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_D_XFERCOMPL4    (BIT(0))
#define USB_D_XFERCOMPL4_M  (USB_D_XFERCOMPL4_V << USB_D_XFERCOMPL4_S)
#define USB_D_XFERCOMPL4_V  0x00000001
#define USB_D_XFERCOMPL4_S  0
/** USB_D_epdispld4:R/W1C；位位置：[1]；默认值：0；0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_D_EPDISBLD4    (BIT(1))
#define USB_D_EPDISBLD4_M  (USB_D_EPDISBLD4_V << USB_D_EPDISBLD4_S)
#define USB_D_EPDISBLD4_V  0x00000001
#define USB_D_EPDISBLD4_S  1
/** USB_D_AHBERR4:R/W1C；位位置：[2]；默认值：0；0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_D_AHBERR4    (BIT(2))
#define USB_D_AHBERR4_M  (USB_D_AHBERR4_V << USB_D_AHBERR4_S)
#define USB_D_AHBERR4_V  0x00000001
#define USB_D_AHBERR4_S  2
/** USB_D_TIMEOUT4:R/W1C；位位置：[3]；默认值：0；0x0：无超时中断0x1：超时中断
 */
#define USB_D_TIMEOUT4    (BIT(3))
#define USB_D_TIMEOUT4_M  (USB_D_TIMEOUT4_V << USB_D_TIMEOUT4_S)
#define USB_D_TIMEOUT4_V  0x00000001
#define USB_D_TIMEOUT4_S  3
/** USB_D_INTKNTXFEMP4:R/W1C；位位置：[4]；默认值：0；0x0：TxFIFO空中断时未收到IN令牌0x1：TxFIFO空中断时收到IN令牌
 */
#define USB_D_INTKNTXFEMP4    (BIT(4))
#define USB_D_INTKNTXFEMP4_M  (USB_D_INTKNTXFEMP4_V << USB_D_INTKNTXFEMP4_S)
#define USB_D_INTKNTXFEMP4_V  0x00000001
#define USB_D_INTKNTXFEMP4_S  4
/** USB_D_INTKNEPMIS4:R/W1C；位位置：[5]；默认值：0；0x0：未接收到带EP不匹配中断的IN令牌0x1：接收到带EP-Match中断的IN代币
 */
#define USB_D_INTKNEPMIS4    (BIT(5))
#define USB_D_INTKNEPMIS4_M  (USB_D_INTKNEPMIS4_V << USB_D_INTKNEPMIS4_S)
#define USB_D_INTKNEPMIS4_V  0x00000001
#define USB_D_INTKNEPMIS4_S  5
/** USB_D_INEPNAKEFF4:R/W1C；位位置：[6]；默认值：0；IN终结点NAK有效0x0：无IN终结点NACK有效中断0x1:IN终结点NA有效中断
 */
#define USB_D_INEPNAKEFF4    (BIT(6))
#define USB_D_INEPNAKEFF4_M  (USB_D_INEPNAKEFF4_V << USB_D_INEPNAKEFF4_S)
#define USB_D_INEPNAKEFF4_V  0x00000001
#define USB_D_INEPNAKEFF4_S  6
/** USB_D_TXFEMP4:RO；位位置：[7]；默认值：0；当此端点的TxFIFO为半空或完全空时，会断言此中断0x0：无传输FIFO空中断0x1：发送FIFO空中断
 */
#define USB_D_TXFEMP4    (BIT(7))
#define USB_D_TXFEMP4_M  (USB_D_TXFEMP4_V << USB_D_TXFEMP4_S)
#define USB_D_TXFEMP4_V  0x00000001
#define USB_D_TXFEMP4_S  7
/** USB_D_TXFIFOUNDRN4:R/W1C；位位置：[8]；默认值：0；当内核在阈值模式下检测到该端点的传输FIFO欠载情况时，内核会生成该中断0x0:No FIFO underrun interrupt 0x1:FIFO Underruninterrupt
 */
#define USB_D_TXFIFOUNDRN4    (BIT(8))
#define USB_D_TXFIFOUNDRN4_M  (USB_D_TXFIFOUNDRN4_V << USB_D_TXFIFOUNDRN4_S)
#define USB_D_TXFIFOUNDRN4_V  0x00000001
#define USB_D_TXFIFOUNDRN4_S  8
/** USB_D_BNAINTR4:R/W1C；位位置：[9]；默认值：0；此位仅在启用分散/聚集DMA模式时有效。当访问的描述符未准备好供核心处理时，如主机忙或DMA已完成0x0:No BNA中断0x1:BNA中断，核心会生成此中断
 */
#define USB_D_BNAINTR4    (BIT(9))
#define USB_D_BNAINTR4_M  (USB_D_BNAINTR4_V << USB_D_BNAINTR4_S)
#define USB_D_BNAINTR4_V  0x00000001
#define USB_D_BNAINTR4_S  9
/** USB_D_PKTDRPSTS4:R/W1C；位位置：[11]；默认值：0；数据包丢弃状态。该位向应用程序指示ISOC OUT数据包已被丢弃。该位没有关联的掩码位，并且不会生成中断0x0：无中断0x1：数据包丢弃状态
 */
#define USB_D_PKTDRPSTS4    (BIT(11))
#define USB_D_PKTDRPSTS4_M  (USB_D_PKTDRPSTS4_V << USB_D_PKTDRPSTS4_S)
#define USB_D_PKTDRPSTS4_V  0x00000001
#define USB_D_PKTDRPSTS4_S  11
/** USB_D_BBLEERR4:R/W1C；位位置：[12]；默认值：0；当接收到端点0x0:No interrupt 0x1:BbleErr interrupt时，内核生成此中断
 */
#define USB_D_BBLEERR4    (BIT(12))
#define USB_D_BBLEERR4_M  (USB_D_BBLEERR4_V << USB_D_BBLEERR4_S)
#define USB_D_BBLEERR4_V  0x00000001
#define USB_D_BBLEERR4_S  12
/** USB_D_nakintrt4:R/W1C；位位置：[13]；默认值：0；NAK中断。当设备发送或接收NAK时，内核生成此中断0x0:无中断0x1:NAK中断
 */
#define USB_D_NAKINTRPT4    (BIT(13))
#define USB_D_NAKINTRPT4_M  (USB_D_NAKINTRPT4_V << USB_D_NAKINTRPT4_S)
#define USB_D_NAKINTRPT4_V  0x00000001
#define USB_D_NAKINTRPT4_S  13
/** USB_D_NYETINTRPT4:R/W1C；位位置：[14]；默认值：0；NYET中断。当为非同步OUT端点发送NYET响应0x0:No interrupt 0x1:NYET interrupt时，内核生成此中断
 */
#define USB_D_NYETINTRPT4    (BIT(14))
#define USB_D_NYETINTRPT4_M  (USB_D_NYETINTRPT4_V << USB_D_NYETINTRPT4_S)
#define USB_D_NYETINTRPT4_V  0x00000001
#define USB_D_NYETINTRPT4_S  14


/** USB_DIEPINT5_REG寄存器设备IN端点5中断寄存器
 */
#define USB_DIEPINT5_REG (SOC_DPORT_USB_BASE + 0x9a8)
/** USB_D_xfercompl:R/W1C；位位置：[0]；默认值：0；0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_D_XFERCOMPL5    (BIT(0))
#define USB_D_XFERCOMPL5_M  (USB_D_XFERCOMPL5_V << USB_D_XFERCOMPL5_S)
#define USB_D_XFERCOMPL5_V  0x00000001
#define USB_D_XFERCOMPL5_S  0
/** USB_D_epdispld5:R/W1C；位位置：[1]；默认值：0；0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_D_EPDISBLD5    (BIT(1))
#define USB_D_EPDISBLD5_M  (USB_D_EPDISBLD5_V << USB_D_EPDISBLD5_S)
#define USB_D_EPDISBLD5_V  0x00000001
#define USB_D_EPDISBLD5_S  1
/** USB_D_AHBERR5:R/W1C；位位置：[2]；默认值：0；0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_D_AHBERR5    (BIT(2))
#define USB_D_AHBERR5_M  (USB_D_AHBERR5_V << USB_D_AHBERR5_S)
#define USB_D_AHBERR5_V  0x00000001
#define USB_D_AHBERR5_S  2
/** USB_D_TIMEOUT5:R/W1C；位位置：[3]；默认值：0；0x0：无超时中断0x1：超时中断
 */
#define USB_D_TIMEOUT5    (BIT(3))
#define USB_D_TIMEOUT5_M  (USB_D_TIMEOUT5_V << USB_D_TIMEOUT5_S)
#define USB_D_TIMEOUT5_V  0x00000001
#define USB_D_TIMEOUT5_S  3
/** USB_D_INTKNTXFEMP5:R/W1C；位位置：[4]；默认值：0；0x0：TxFIFO空中断时未收到IN令牌0x1：TxFIFO空中断时收到IN令牌
 */
#define USB_D_INTKNTXFEMP5    (BIT(4))
#define USB_D_INTKNTXFEMP5_M  (USB_D_INTKNTXFEMP5_V << USB_D_INTKNTXFEMP5_S)
#define USB_D_INTKNTXFEMP5_V  0x00000001
#define USB_D_INTKNTXFEMP5_S  4
/** USB_D_INTKNEPMIS5:R/W1C；位位置：[5]；默认值：0；0x0：未接收到带EP不匹配中断的IN令牌0x1：接收到带EP-Match中断的IN代币
 */
#define USB_D_INTKNEPMIS5    (BIT(5))
#define USB_D_INTKNEPMIS5_M  (USB_D_INTKNEPMIS5_V << USB_D_INTKNEPMIS5_S)
#define USB_D_INTKNEPMIS5_V  0x00000001
#define USB_D_INTKNEPMIS5_S  5
/** USB_D_INEPNAKEFF5:R/W1C；位位置：[6]；默认值：0；IN终结点NAK有效0x0：无IN终结点NACK有效中断0x1:IN终结点NA有效中断
 */
#define USB_D_INEPNAKEFF5    (BIT(6))
#define USB_D_INEPNAKEFF5_M  (USB_D_INEPNAKEFF5_V << USB_D_INEPNAKEFF5_S)
#define USB_D_INEPNAKEFF5_V  0x00000001
#define USB_D_INEPNAKEFF5_S  6
/** USB_D_TXFEMP5:RO；位位置：[7]；默认值：0；当此端点的TxFIFO为半空或完全空时，会断言此中断0x0：无传输FIFO空中断0x1：发送FIFO空中断
 */
#define USB_D_TXFEMP5    (BIT(7))
#define USB_D_TXFEMP5_M  (USB_D_TXFEMP5_V << USB_D_TXFEMP5_S)
#define USB_D_TXFEMP5_V  0x00000001
#define USB_D_TXFEMP5_S  7
/** USB_D_TXFIFOUNDRN5:R/W1C；位位置：[8]；默认值：0；当内核在阈值模式下检测到该端点的传输FIFO欠载情况时，内核会生成该中断0x0:No FIFO underrun interrupt 0x1:FIFO Underruninterrupt
 */
#define USB_D_TXFIFOUNDRN5    (BIT(8))
#define USB_D_TXFIFOUNDRN5_M  (USB_D_TXFIFOUNDRN5_V << USB_D_TXFIFOUNDRN5_S)
#define USB_D_TXFIFOUNDRN5_V  0x00000001
#define USB_D_TXFIFOUNDRN5_S  8
/** USB_D_BNAINTR5:R/W1C；位位置：[9]；默认值：0；此位仅在启用分散/聚集DMA模式时有效。当访问的描述符未准备好供核心处理时，如主机忙或DMA已完成0x0:No BNA中断0x1:BNA中断，核心会生成此中断
 */
#define USB_D_BNAINTR5    (BIT(9))
#define USB_D_BNAINTR5_M  (USB_D_BNAINTR5_V << USB_D_BNAINTR5_S)
#define USB_D_BNAINTR5_V  0x00000001
#define USB_D_BNAINTR5_S  9
/** USB_D_PKTDRPSTS5:R/W1C；位位置：[11]；默认值：0；数据包丢弃状态。该位向应用程序指示ISOC OUT数据包已被丢弃。该位没有关联的掩码位，并且不会生成中断0x0：无中断0x1：数据包丢弃状态
 */
#define USB_D_PKTDRPSTS5    (BIT(11))
#define USB_D_PKTDRPSTS5_M  (USB_D_PKTDRPSTS5_V << USB_D_PKTDRPSTS5_S)
#define USB_D_PKTDRPSTS5_V  0x00000001
#define USB_D_PKTDRPSTS5_S  11
/** USB_D_bbleerr:R/W1C；位位置：[12]；默认值：0；当接收到端点0x0:No interrupt 0x1:BbleErr interrupt时，内核生成此中断
 */
#define USB_D_BBLEERR5    (BIT(12))
#define USB_D_BBLEERR5_M  (USB_D_BBLEERR5_V << USB_D_BBLEERR5_S)
#define USB_D_BBLEERR5_V  0x00000001
#define USB_D_BBLEERR5_S  12
/** USB_D_nakintrt5:R/W1C；位位置：[13]；默认值：0；NAK中断。当设备发送或接收NAK时，内核生成此中断0x0:无中断0x1:NAK中断
 */
#define USB_D_NAKINTRPT5    (BIT(13))
#define USB_D_NAKINTRPT5_M  (USB_D_NAKINTRPT5_V << USB_D_NAKINTRPT5_S)
#define USB_D_NAKINTRPT5_V  0x00000001
#define USB_D_NAKINTRPT5_S  13
/** USB_D_NYETINTRPT5:R/W1C；位位置：[14]；默认值：0；NYET中断。当为非同步OUT端点发送NYET响应0x0:No interrupt 0x1:NYET interrupt时，内核生成此中断
 */
#define USB_D_NYETINTRPT5    (BIT(14))
#define USB_D_NYETINTRPT5_M  (USB_D_NYETINTRPT5_V << USB_D_NYETINTRPT5_S)
#define USB_D_NYETINTRPT5_V  0x00000001
#define USB_D_NYETINTRPT5_S  14


/** USB_DIEPINT6_REG寄存器设备IN端点6中断寄存器
 */
#define USB_DIEPINT6_REG (SOC_DPORT_USB_BASE + 0x9c8)
/** USB_D_XFERCOMPL6:R/W1C；位位置：[0]；默认值：0；0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_D_XFERCOMPL6    (BIT(0))
#define USB_D_XFERCOMPL6_M  (USB_D_XFERCOMPL6_V << USB_D_XFERCOMPL6_S)
#define USB_D_XFERCOMPL6_V  0x00000001
#define USB_D_XFERCOMPL6_S  0
/** USB_D_epdispld6:R/W1C；位位置：[1]；默认值：0；0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_D_EPDISBLD6    (BIT(1))
#define USB_D_EPDISBLD6_M  (USB_D_EPDISBLD6_V << USB_D_EPDISBLD6_S)
#define USB_D_EPDISBLD6_V  0x00000001
#define USB_D_EPDISBLD6_S  1
/** USB_D_AHBERR6:R/W1C；位位置：[2]；默认值：0；0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_D_AHBERR6    (BIT(2))
#define USB_D_AHBERR6_M  (USB_D_AHBERR6_V << USB_D_AHBERR6_S)
#define USB_D_AHBERR6_V  0x00000001
#define USB_D_AHBERR6_S  2
/** USB_D_TIMEOUT6:R/W1C；位位置：[3]；默认值：0；0x0：无超时中断0x1：超时中断
 */
#define USB_D_TIMEOUT6    (BIT(3))
#define USB_D_TIMEOUT6_M  (USB_D_TIMEOUT6_V << USB_D_TIMEOUT6_S)
#define USB_D_TIMEOUT6_V  0x00000001
#define USB_D_TIMEOUT6_S  3
/** USB_D_intkntxemp6:R/W1C；位位置：[4]；默认值：0；0x0：TxFIFO空中断时未收到IN令牌0x1：TxFIFO空中断时收到IN令牌
 */
#define USB_D_INTKNTXFEMP6    (BIT(4))
#define USB_D_INTKNTXFEMP6_M  (USB_D_INTKNTXFEMP6_V << USB_D_INTKNTXFEMP6_S)
#define USB_D_INTKNTXFEMP6_V  0x00000001
#define USB_D_INTKNTXFEMP6_S  4
/** USB_D_INTKNEPMIS6:R/W1C；位位置：[5]；默认值：0；0x0：未接收到带EP不匹配中断的IN令牌0x1：接收到带EP-Match中断的IN代币
 */
#define USB_D_INTKNEPMIS6    (BIT(5))
#define USB_D_INTKNEPMIS6_M  (USB_D_INTKNEPMIS6_V << USB_D_INTKNEPMIS6_S)
#define USB_D_INTKNEPMIS6_V  0x00000001
#define USB_D_INTKNEPMIS6_S  5
/** USB_D_INEPNAKEFF6:R/W1C；位位置：[6]；默认值：0；IN终结点NAK有效0x0：无IN终结点NACK有效中断0x1:IN终结点NA有效中断
 */
#define USB_D_INEPNAKEFF6    (BIT(6))
#define USB_D_INEPNAKEFF6_M  (USB_D_INEPNAKEFF6_V << USB_D_INEPNAKEFF6_S)
#define USB_D_INEPNAKEFF6_V  0x00000001
#define USB_D_INEPNAKEFF6_S  6
/** USB_D_TXFEMP6:RO；位位置：[7]；默认值：0；当此端点的TxFIFO为半空或完全空时，会断言此中断0x0：无传输FIFO空中断0x1：发送FIFO空中断
 */
#define USB_D_TXFEMP6    (BIT(7))
#define USB_D_TXFEMP6_M  (USB_D_TXFEMP6_V << USB_D_TXFEMP6_S)
#define USB_D_TXFEMP6_V  0x00000001
#define USB_D_TXFEMP6_S  7
/** USB_D_TXFIFOUNDRN6:R/W1C；位位置：[8]；默认值：0；当内核在阈值模式下检测到该端点的传输FIFO欠载情况时，内核会生成该中断0x0:No FIFO underrun interrupt 0x1:FIFO Underruninterrupt
 */
#define USB_D_TXFIFOUNDRN6    (BIT(8))
#define USB_D_TXFIFOUNDRN6_M  (USB_D_TXFIFOUNDRN6_V << USB_D_TXFIFOUNDRN6_S)
#define USB_D_TXFIFOUNDRN6_V  0x00000001
#define USB_D_TXFIFOUNDRN6_S  8
/** USB_D_BNAINTR6:R/W1C；位位置：[9]；默认值：0；此位仅在启用分散/聚集DMA模式时有效。当访问的描述符未准备好供核心处理时，如主机忙或DMA已完成0x0:No BNA中断0x1:BNA中断，核心会生成此中断
 */
#define USB_D_BNAINTR6    (BIT(9))
#define USB_D_BNAINTR6_M  (USB_D_BNAINTR6_V << USB_D_BNAINTR6_S)
#define USB_D_BNAINTR6_V  0x00000001
#define USB_D_BNAINTR6_S  9
/** USB_D_PKTDRPSTS6:R/W1C；位位置：[11]；默认值：0；数据包丢弃状态。该位向应用程序指示ISOC OUT数据包已被丢弃。该位没有关联的掩码位，并且不会生成中断0x0：无中断0x1：数据包丢弃状态
 */
#define USB_D_PKTDRPSTS6    (BIT(11))
#define USB_D_PKTDRPSTS6_M  (USB_D_PKTDRPSTS6_V << USB_D_PKTDRPSTS6_S)
#define USB_D_PKTDRPSTS6_V  0x00000001
#define USB_D_PKTDRPSTS6_S  11
/** USB_D_BBLEERR6:R/W1C；位位置：[12]；默认值：0；当接收到端点0x0:No interrupt 0x1:BbleErr interrupt时，内核生成此中断
 */
#define USB_D_BBLEERR6    (BIT(12))
#define USB_D_BBLEERR6_M  (USB_D_BBLEERR6_V << USB_D_BBLEERR6_S)
#define USB_D_BBLEERR6_V  0x00000001
#define USB_D_BBLEERR6_S  12
/** USB_D_NAKINTRPT6:R/W1C；位位置：[13]；默认值：0；NAK中断。当设备发送或接收NAK时，内核生成此中断0x0:无中断0x1:NAK中断
 */
#define USB_D_NAKINTRPT6    (BIT(13))
#define USB_D_NAKINTRPT6_M  (USB_D_NAKINTRPT6_V << USB_D_NAKINTRPT6_S)
#define USB_D_NAKINTRPT6_V  0x00000001
#define USB_D_NAKINTRPT6_S  13
/** USB_D_NYETINTRPT6:R/W1C；位位置：[14]；默认值：0；NYET中断。当为非同步OUT端点发送NYET响应0x0:No interrupt 0x1:NYET interrupt时，内核生成此中断
 */
#define USB_D_NYETINTRPT6    (BIT(14))
#define USB_D_NYETINTRPT6_M  (USB_D_NYETINTRPT6_V << USB_D_NYETINTRPT6_S)
#define USB_D_NYETINTRPT6_V  0x00000001
#define USB_D_NYETINTRPT6_S  14


/** USB_DOEPINT0_REG寄存器设备输出端点0中断寄存器
 */
#define USB_DOEPINT0_REG (SOC_DPORT_USB_BASE + 0xb08)
/** USB_xfercomplex:R/W1C；位位置：[0]；默认值：0；传输完成中断0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_XFERCOMPL0    (BIT(0))
#define USB_XFERCOMPL0_M  (USB_XFERCOMPL0_V << USB_XFERCOMPL0_S)
#define USB_XFERCOMPL0_V  0x00000001
#define USB_XFERCOMPL0_S  0
/** USB_epdispld0:R/W1C；位位置：[1]；默认值：0；端点禁用中断0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_EPDISBLD0    (BIT(1))
#define USB_EPDISBLD0_M  (USB_EPDISBLD0_V << USB_EPDISBLD0_S)
#define USB_EPDISBLD0_V  0x00000001
#define USB_EPDISBLD0_S  1
/** USB_AHBERR0:R/W1C；位位置：[2]；默认值：0；AHB错误0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_AHBERR0    (BIT(2))
#define USB_AHBERR0_M  (USB_AHBERR0_V << USB_AHBERR0_S)
#define USB_AHBERR0_V  0x00000001
#define USB_AHBERR0_S  2
/** USB_SETUP0:R/W1C；位位置：[3]；默认值：0；设置阶段完成0x0：没有设置阶段完成0x1：设置阶段完成
 */
#define USB_SETUP0    (BIT(3))
#define USB_SETUP0_M  (USB_SETUP0_V << USB_SETUP0_S)
#define USB_SETUP0_V  0x00000001
#define USB_SETUP0_S  3
/** USB_OUTTKNEPDIS0:R/W1C；位位置：[4]；默认值：0；禁用端点时收到OUT令牌0x0:禁用端点时未收到OUT令牌0x1：禁用端点时接收OUT令牌
 */
#define USB_OUTTKNEPDIS0    (BIT(4))
#define USB_OUTTKNEPDIS0_M  (USB_OUTTKNEPDIS0_V << USB_OUTTKNEPDIS0_S)
#define USB_OUTTKNEPDIS0_V  0x00000001
#define USB_OUTTKNEPDIS0_S  4
/** USB_STSPHSERCVD0:R/W1C；位位置：[5]；默认值：0；接收到控制写入的状态阶段0x0：未接收到控制写的状态阶段0x1：接收到控制读的状态阶段
 */
#define USB_STSPHSERCVD0    (BIT(5))
#define USB_STSPHSERCVD0_M  (USB_STSPHSERCVD0_V << USB_STSPHSERCVD0_S)
#define USB_STSPHSERCVD0_V  0x00000001
#define USB_STSPHSERCVD0_S  5
/** USB_BACK2BACKSETUP0:R/W1C；位位置：[6]；默认值：0；收到背靠背SETUP数据包0x0：未收到背靠背设置数据包0x1：收到背靠背安装数据包
 */
#define USB_BACK2BACKSETUP0    (BIT(6))
#define USB_BACK2BACKSETUP0_M  (USB_BACK2BACKSETUP0_V << USB_BACK2BACKSETUP0_S)
#define USB_BACK2BACKSETUP0_V  0x00000001
#define USB_BACK2BACKSETUP0_S  6
/** USB_OUTPKTERR0:R/W1C；位位置：[8]；默认值：0；OUT数据包错误0x0:无OUT数据包错0x1:OUT数据包出错
 */
#define USB_OUTPKTERR0    (BIT(8))
#define USB_OUTPKTERR0_M  (USB_OUTPKTERR0_V << USB_OUTPKTERR0_S)
#define USB_OUTPKTERR0_V  0x00000001
#define USB_OUTPKTERR0_S  8
/** USB_BNAINTR0:R/W1C；位位置：[9]；默认值：0；缓冲区不可用中断0x0:No BNA中断0x1:BNA中断
 */
#define USB_BNAINTR0    (BIT(9))
#define USB_BNAINTR0_M  (USB_BNAINTR0_V << USB_BNAINTR0_S)
#define USB_BNAINTR0_V  0x00000001
#define USB_BNAINTR0_S  9
/** USB_PKTDRPSTS0：R/W1C；位位置：[11]；默认值：0；0x0：无中断0x1：数据包丢弃状态中断
 */
#define USB_PKTDRPSTS0    (BIT(11))
#define USB_PKTDRPSTS0_M  (USB_PKTDRPSTS0_V << USB_PKTDRPSTS0_S)
#define USB_PKTDRPSTS0_V  0x00000001
#define USB_PKTDRPSTS0_S  11
/** USB_BBLEERR0:R/W1C；位位置：[12]；默认值：0；0x0：无BbleErr中断0x1:BbleErr
 */
#define USB_BBLEERR0    (BIT(12))
#define USB_BBLEERR0_M  (USB_BBLEERR0_V << USB_BBLEERR0_S)
#define USB_BBLEERR0_V  0x00000001
#define USB_BBLEERR0_S  12
/** USB_nakintrt0:R/W1C；位位置：[13]；默认值：0；0x0：无NAK中断0x1:NAK中断
 */
#define USB_NAKINTRPT0    (BIT(13))
#define USB_NAKINTRPT0_M  (USB_NAKINTRPT0_V << USB_NAKINTRPT0_S)
#define USB_NAKINTRPT0_V  0x00000001
#define USB_NAKINTRPT0_S  13
/** USB_nyepintpt0:R/W1C；位位置：[14]；默认值：0；0x0:无NYET中断0x1:NYET中断
 */
#define USB_NYEPINTRPT0    (BIT(14))
#define USB_NYEPINTRPT0_M  (USB_NYEPINTRPT0_V << USB_NYEPINTRPT0_S)
#define USB_NYEPINTRPT0_V  0x00000001
#define USB_NYEPINTRPT0_S  14
/** USB_stumpktrcvd0:R/W1C；位位置：[15]；默认值：0；0x0：未接收到安装包0x1：已接收到安装数据包
 */
#define USB_STUPPKTRCVD0    (BIT(15))
#define USB_STUPPKTRCVD0_M  (USB_STUPPKTRCVD0_V << USB_STUPPKTRCVD0_S)
#define USB_STUPPKTRCVD0_V  0x00000001
#define USB_STUPPKTRCVD0_S  15


/** USB_DOEPINT1_REG寄存器设备输出端点1中断寄存器
 */
#define USB_DOEPINT1_REG (SOC_DPORT_USB_BASE + 0xb28)
/** USB_XFERCOMPL1:R/W1C；位位置：[0]；默认值：0；传输完成中断0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_XFERCOMPL1    (BIT(0))
#define USB_XFERCOMPL1_M  (USB_XFERCOMPL1_V << USB_XFERCOMPL1_S)
#define USB_XFERCOMPL1_V  0x00000001
#define USB_XFERCOMPL1_S  0
/** USB_epdiscld1:R/W1C；位位置：[1]；默认值：0；端点禁用中断0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_EPDISBLD1    (BIT(1))
#define USB_EPDISBLD1_M  (USB_EPDISBLD1_V << USB_EPDISBLD1_S)
#define USB_EPDISBLD1_V  0x00000001
#define USB_EPDISBLD1_S  1
/** USB_AHBERR1:R/W1C；位位置：[2]；默认值：0；AHB错误0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_AHBERR1    (BIT(2))
#define USB_AHBERR1_M  (USB_AHBERR1_V << USB_AHBERR1_S)
#define USB_AHBERR1_V  0x00000001
#define USB_AHBERR1_S  2
/** USB_SETUP1:R/W1C；位位置：[3]；默认值：0；设置阶段完成0x0：没有设置阶段完成0x1：设置阶段完成
 */
#define USB_SETUP1    (BIT(3))
#define USB_SETUP1_M  (USB_SETUP1_V << USB_SETUP1_S)
#define USB_SETUP1_V  0x00000001
#define USB_SETUP1_S  3
/** USB_OUTTKNEPDIS1:R/W1C；位位置：[4]；默认值：0；禁用端点时收到OUT令牌0x0:禁用端点时未收到OUT令牌0x1：禁用端点时接收OUT令牌
 */
#define USB_OUTTKNEPDIS1    (BIT(4))
#define USB_OUTTKNEPDIS1_M  (USB_OUTTKNEPDIS1_V << USB_OUTTKNEPDIS1_S)
#define USB_OUTTKNEPDIS1_V  0x00000001
#define USB_OUTTKNEPDIS1_S  4
/** USB_STSPHSERCVD1:R/W1C；位位置：[5]；默认值：0；接收到控制写入的状态阶段0x0：未接收到控制写的状态阶段0x1：接收到控制读的状态阶段
 */
#define USB_STSPHSERCVD1    (BIT(5))
#define USB_STSPHSERCVD1_M  (USB_STSPHSERCVD1_V << USB_STSPHSERCVD1_S)
#define USB_STSPHSERCVD1_V  0x00000001
#define USB_STSPHSERCVD1_S  5
/** USB_BACK2BACKSETUP1:R/W1C；位位置：[6]；默认值：0；收到背靠背SETUP数据包0x0：未收到背靠背设置数据包0x1：收到背靠背安装数据包
 */
#define USB_BACK2BACKSETUP1    (BIT(6))
#define USB_BACK2BACKSETUP1_M  (USB_BACK2BACKSETUP1_V << USB_BACK2BACKSETUP1_S)
#define USB_BACK2BACKSETUP1_V  0x00000001
#define USB_BACK2BACKSETUP1_S  6
/** USB_OUTPKTERR1：R/W1C；位位置：[8]；默认值：0；OUT数据包错误0x0:无OUT数据包错0x1:OUT数据包出错
 */
#define USB_OUTPKTERR1    (BIT(8))
#define USB_OUTPKTERR1_M  (USB_OUTPKTERR1_V << USB_OUTPKTERR1_S)
#define USB_OUTPKTERR1_V  0x00000001
#define USB_OUTPKTERR1_S  8
/** USB_BNAINTR1:R/W1C；位位置：[9]；默认值：0；缓冲区不可用中断0x0:No BNA中断0x1:BNA中断
 */
#define USB_BNAINTR1    (BIT(9))
#define USB_BNAINTR1_M  (USB_BNAINTR1_V << USB_BNAINTR1_S)
#define USB_BNAINTR1_V  0x00000001
#define USB_BNAINTR1_S  9
/** USB_PKTDRPSTS1：R/W1C；位位置：[11]；默认值：0；0x0：无中断0x1：数据包丢弃状态中断
 */
#define USB_PKTDRPSTS1    (BIT(11))
#define USB_PKTDRPSTS1_M  (USB_PKTDRPSTS1_V << USB_PKTDRPSTS1_S)
#define USB_PKTDRPSTS1_V  0x00000001
#define USB_PKTDRPSTS1_S  11
/** USB_bbleer1:R/W1C；位位置：[12]；默认值：0；0x0：无BbleErr中断0x1:BbleErr
 */
#define USB_BBLEERR1    (BIT(12))
#define USB_BBLEERR1_M  (USB_BBLEERR1_V << USB_BBLEERR1_S)
#define USB_BBLEERR1_V  0x00000001
#define USB_BBLEERR1_S  12
/** USB_nakintrt1:R/W1C；位位置：[13]；默认值：0；0x0：无NAK中断0x1:NAK中断
 */
#define USB_NAKINTRPT1    (BIT(13))
#define USB_NAKINTRPT1_M  (USB_NAKINTRPT1_V << USB_NAKINTRPT1_S)
#define USB_NAKINTRPT1_V  0x00000001
#define USB_NAKINTRPT1_S  13
/** USB_nyepntrpt1:R/W1C；位位置：[14]；默认值：0；0x0:无NYET中断0x1:NYET中断
 */
#define USB_NYEPINTRPT1    (BIT(14))
#define USB_NYEPINTRPT1_M  (USB_NYEPINTRPT1_V << USB_NYEPINTRPT1_S)
#define USB_NYEPINTRPT1_V  0x00000001
#define USB_NYEPINTRPT1_S  14
/** USB_STUPPKTRCVD1:R/W1C；位位置：[15]；默认值：0；0x0：未接收到安装包0x1：已接收到安装数据包
 */
#define USB_STUPPKTRCVD1    (BIT(15))
#define USB_STUPPKTRCVD1_M  (USB_STUPPKTRCVD1_V << USB_STUPPKTRCVD1_S)
#define USB_STUPPKTRCVD1_V  0x00000001
#define USB_STUPPKTRCVD1_S  15


/** USB_DOEPINT2_REG寄存器设备输出端点2中断寄存器
 */
#define USB_DOEPINT2_REG (SOC_DPORT_USB_BASE + 0xb48)
/** USB_xfercomple2:R/W1C；位位置：[0]；默认值：0；传输完成中断0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_XFERCOMPL2    (BIT(0))
#define USB_XFERCOMPL2_M  (USB_XFERCOMPL2_V << USB_XFERCOMPL2_S)
#define USB_XFERCOMPL2_V  0x00000001
#define USB_XFERCOMPL2_S  0
/** USB_epdiscld2:R/W1C；位位置：[1]；默认值：0；端点禁用中断0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_EPDISBLD2    (BIT(1))
#define USB_EPDISBLD2_M  (USB_EPDISBLD2_V << USB_EPDISBLD2_S)
#define USB_EPDISBLD2_V  0x00000001
#define USB_EPDISBLD2_S  1
/** USB_AHBERR2:R/W1C；位位置：[2]；默认值：0；AHB错误0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_AHBERR2    (BIT(2))
#define USB_AHBERR2_M  (USB_AHBERR2_V << USB_AHBERR2_S)
#define USB_AHBERR2_V  0x00000001
#define USB_AHBERR2_S  2
/** USB_SETUP2:R/W1C；位位置：[3]；默认值：0；设置阶段完成0x0：没有设置阶段完成0x1：设置阶段完成
 */
#define USB_SETUP2    (BIT(3))
#define USB_SETUP2_M  (USB_SETUP2_V << USB_SETUP2_S)
#define USB_SETUP2_V  0x00000001
#define USB_SETUP2_S  3
/** USB_OUTTKNEPDIS2:R/W1C；位位置：[4]；默认值：0；禁用端点时收到OUT令牌0x0:禁用端点时未收到OUT令牌0x1：禁用端点时接收OUT令牌
 */
#define USB_OUTTKNEPDIS2    (BIT(4))
#define USB_OUTTKNEPDIS2_M  (USB_OUTTKNEPDIS2_V << USB_OUTTKNEPDIS2_S)
#define USB_OUTTKNEPDIS2_V  0x00000001
#define USB_OUTTKNEPDIS2_S  4
/** USB_STSPHSERCVD2:R/W1C；位位置：[5]；默认值：0；接收到控制写入的状态阶段0x0：未接收到控制写的状态阶段0x1：接收到控制读的状态阶段
 */
#define USB_STSPHSERCVD2    (BIT(5))
#define USB_STSPHSERCVD2_M  (USB_STSPHSERCVD2_V << USB_STSPHSERCVD2_S)
#define USB_STSPHSERCVD2_V  0x00000001
#define USB_STSPHSERCVD2_S  5
/** USB_BACK2BACKSETUP2:R/W1C；位位置：[6]；默认值：0；收到背靠背SETUP数据包0x0：未收到背靠背设置数据包0x1：收到背靠背安装数据包
 */
#define USB_BACK2BACKSETUP2    (BIT(6))
#define USB_BACK2BACKSETUP2_M  (USB_BACK2BACKSETUP2_V << USB_BACK2BACKSETUP2_S)
#define USB_BACK2BACKSETUP2_V  0x00000001
#define USB_BACK2BACKSETUP2_S  6
/** USB_OUTPKTERR2:R/W1C；位位置：[8]；默认值：0；OUT数据包错误0x0:无OUT数据包错0x1:OUT数据包出错
 */
#define USB_OUTPKTERR2    (BIT(8))
#define USB_OUTPKTERR2_M  (USB_OUTPKTERR2_V << USB_OUTPKTERR2_S)
#define USB_OUTPKTERR2_V  0x00000001
#define USB_OUTPKTERR2_S  8
/** USB_BNAINTR2:R/W1C；位位置：[9]；默认值：0；缓冲区不可用中断0x0:No BNA中断0x1:BNA中断
 */
#define USB_BNAINTR2    (BIT(9))
#define USB_BNAINTR2_M  (USB_BNAINTR2_V << USB_BNAINTR2_S)
#define USB_BNAINTR2_V  0x00000001
#define USB_BNAINTR2_S  9
/** USB_PKTDRPSTS2:R/W1C；位位置：[11]；默认值：0；0x0：无中断0x1：数据包丢弃状态中断
 */
#define USB_PKTDRPSTS2    (BIT(11))
#define USB_PKTDRPSTS2_M  (USB_PKTDRPSTS2_V << USB_PKTDRPSTS2_S)
#define USB_PKTDRPSTS2_V  0x00000001
#define USB_PKTDRPSTS2_S  11
/** USB_bbleer2:R/W1C；位位置：[12]；默认值：0；0x0：无BbleErr中断0x1:BbleErr
 */
#define USB_BBLEERR2    (BIT(12))
#define USB_BBLEERR2_M  (USB_BBLEERR2_V << USB_BBLEERR2_S)
#define USB_BBLEERR2_V  0x00000001
#define USB_BBLEERR2_S  12
/** USB_nakintrt2:R/W1C；位位置：[13]；默认值：0；0x0：无NAK中断0x1:NAK中断
 */
#define USB_NAKINTRPT2    (BIT(13))
#define USB_NAKINTRPT2_M  (USB_NAKINTRPT2_V << USB_NAKINTRPT2_S)
#define USB_NAKINTRPT2_V  0x00000001
#define USB_NAKINTRPT2_S  13
/** USB_nyepntrpt2:R/W1C；位位置：[14]；默认值：0；0x0:无NYET中断0x1:NYET中断
 */
#define USB_NYEPINTRPT2    (BIT(14))
#define USB_NYEPINTRPT2_M  (USB_NYEPINTRPT2_V << USB_NYEPINTRPT2_S)
#define USB_NYEPINTRPT2_V  0x00000001
#define USB_NYEPINTRPT2_S  14
/** USB_STUPPKTRCVD2:R/W1C；位位置：[15]；默认值：0；0x0：未接收到安装包0x1：已接收到安装数据包
 */
#define USB_STUPPKTRCVD2    (BIT(15))
#define USB_STUPPKTRCVD2_M  (USB_STUPPKTRCVD2_V << USB_STUPPKTRCVD2_S)
#define USB_STUPPKTRCVD2_V  0x00000001
#define USB_STUPPKTRCVD2_S  15


/** USB_DOEPINT3_REG寄存器设备输出端点3中断寄存器
 */
#define USB_DOEPINT3_REG (SOC_DPORT_USB_BASE + 0xb68)
/** USB_XFERCOMPL3:R/W1C；位位置：[0]；默认值：0；传输完成中断0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_XFERCOMPL3    (BIT(0))
#define USB_XFERCOMPL3_M  (USB_XFERCOMPL3_V << USB_XFERCOMPL3_S)
#define USB_XFERCOMPL3_V  0x00000001
#define USB_XFERCOMPL3_S  0
/** USB_epdiscld3:R/W1C；位位置：[1]；默认值：0；端点禁用中断0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_EPDISBLD3    (BIT(1))
#define USB_EPDISBLD3_M  (USB_EPDISBLD3_V << USB_EPDISBLD3_S)
#define USB_EPDISBLD3_V  0x00000001
#define USB_EPDISBLD3_S  1
/** USB_AHBERR3:R/W1C；位位置：[2]；默认值：0；AHB错误0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_AHBERR3    (BIT(2))
#define USB_AHBERR3_M  (USB_AHBERR3_V << USB_AHBERR3_S)
#define USB_AHBERR3_V  0x00000001
#define USB_AHBERR3_S  2
/** USB_SETUP3:R/W1C；位位置：[3]；默认值：0；设置阶段完成0x0：没有设置阶段完成0x1：设置阶段完成
 */
#define USB_SETUP3    (BIT(3))
#define USB_SETUP3_M  (USB_SETUP3_V << USB_SETUP3_S)
#define USB_SETUP3_V  0x00000001
#define USB_SETUP3_S  3
/** USB_OUTTKNEPDIS3:R/W1C；位位置：[4]；默认值：0；禁用端点时收到OUT令牌0x0:禁用端点时未收到OUT令牌0x1：禁用端点时接收OUT令牌
 */
#define USB_OUTTKNEPDIS3    (BIT(4))
#define USB_OUTTKNEPDIS3_M  (USB_OUTTKNEPDIS3_V << USB_OUTTKNEPDIS3_S)
#define USB_OUTTKNEPDIS3_V  0x00000001
#define USB_OUTTKNEPDIS3_S  4
/** USB_STSPHSERCVD3:R/W1C；位位置：[5]；默认值：0；接收到控制写入的状态阶段0x0：未接收到控制写的状态阶段0x1：接收到控制读的状态阶段
 */
#define USB_STSPHSERCVD3    (BIT(5))
#define USB_STSPHSERCVD3_M  (USB_STSPHSERCVD3_V << USB_STSPHSERCVD3_S)
#define USB_STSPHSERCVD3_V  0x00000001
#define USB_STSPHSERCVD3_S  5
/** USB_BACK2BACKSETUP3:R/W1C；位位置：[6]；默认值：0；收到背靠背SETUP数据包0x0：未收到背靠背设置数据包0x1：收到背靠背安装数据包
 */
#define USB_BACK2BACKSETUP3    (BIT(6))
#define USB_BACK2BACKSETUP3_M  (USB_BACK2BACKSETUP3_V << USB_BACK2BACKSETUP3_S)
#define USB_BACK2BACKSETUP3_V  0x00000001
#define USB_BACK2BACKSETUP3_S  6
/** USB_OUTPKTERR3:R/W1C；位位置：[8]；默认值：0；OUT数据包错误0x0:无OUT数据包错0x1:OUT数据包出错
 */
#define USB_OUTPKTERR3    (BIT(8))
#define USB_OUTPKTERR3_M  (USB_OUTPKTERR3_V << USB_OUTPKTERR3_S)
#define USB_OUTPKTERR3_V  0x00000001
#define USB_OUTPKTERR3_S  8
/** USB_BNAINTR3:R/W1C；位位置：[9]；默认值：0；缓冲区不可用中断0x0:No BNA中断0x1:BNA中断
 */
#define USB_BNAINTR3    (BIT(9))
#define USB_BNAINTR3_M  (USB_BNAINTR3_V << USB_BNAINTR3_S)
#define USB_BNAINTR3_V  0x00000001
#define USB_BNAINTR3_S  9
/** USB_PKTDRPSTS3:R/W1C；位位置：[11]；默认值：0；0x0：无中断0x1：数据包丢弃状态中断
 */
#define USB_PKTDRPSTS3    (BIT(11))
#define USB_PKTDRPSTS3_M  (USB_PKTDRPSTS3_V << USB_PKTDRPSTS3_S)
#define USB_PKTDRPSTS3_V  0x00000001
#define USB_PKTDRPSTS3_S  11
/** USB_bbleer3:R/W1C；位位置：[12]；默认值：0；0x0：无BbleErr中断0x1:BbleErr
 */
#define USB_BBLEERR3    (BIT(12))
#define USB_BBLEERR3_M  (USB_BBLEERR3_V << USB_BBLEERR3_S)
#define USB_BBLEERR3_V  0x00000001
#define USB_BBLEERR3_S  12
/** USB_nakintrt3:R/W1C；位位置：[13]；默认值：0；0x0：无NAK中断0x1:NAK中断
 */
#define USB_NAKINTRPT3    (BIT(13))
#define USB_NAKINTRPT3_M  (USB_NAKINTRPT3_V << USB_NAKINTRPT3_S)
#define USB_NAKINTRPT3_V  0x00000001
#define USB_NAKINTRPT3_S  13
/** USB_nyepntrpt3:R/W1C；位位置：[14]；默认值：0；0x0:无NYET中断0x1:NYET中断
 */
#define USB_NYEPINTRPT3    (BIT(14))
#define USB_NYEPINTRPT3_M  (USB_NYEPINTRPT3_V << USB_NYEPINTRPT3_S)
#define USB_NYEPINTRPT3_V  0x00000001
#define USB_NYEPINTRPT3_S  14
/** USB_STUPPKTRCVD3:R/W1C；位位置：[15]；默认值：0；0x0：未接收到安装包0x1：已接收到安装数据包
 */
#define USB_STUPPKTRCVD3    (BIT(15))
#define USB_STUPPKTRCVD3_M  (USB_STUPPKTRCVD3_V << USB_STUPPKTRCVD3_S)
#define USB_STUPPKTRCVD3_V  0x00000001
#define USB_STUPPKTRCVD3_S  15


/** USB_DOEPINT4_REG寄存器设备输出端点4中断寄存器
 */
#define USB_DOEPINT4_REG (SOC_DPORT_USB_BASE + 0xb88)
/** USB_XFERCOMPL4:R/W1C；位位置：[0]；默认值：0；传输完成中断0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_XFERCOMPL4    (BIT(0))
#define USB_XFERCOMPL4_M  (USB_XFERCOMPL4_V << USB_XFERCOMPL4_S)
#define USB_XFERCOMPL4_V  0x00000001
#define USB_XFERCOMPL4_S  0
/** USB_epdiscld4:R/W1C；位位置：[1]；默认值：0；端点禁用中断0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_EPDISBLD4    (BIT(1))
#define USB_EPDISBLD4_M  (USB_EPDISBLD4_V << USB_EPDISBLD4_S)
#define USB_EPDISBLD4_V  0x00000001
#define USB_EPDISBLD4_S  1
/** USB_AHBERR4:R/W1C；位位置：[2]；默认值：0；AHB错误0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_AHBERR4    (BIT(2))
#define USB_AHBERR4_M  (USB_AHBERR4_V << USB_AHBERR4_S)
#define USB_AHBERR4_V  0x00000001
#define USB_AHBERR4_S  2
/** USB_SETUP4:R/W1C；位位置：[3]；默认值：0；设置阶段完成0x0：没有设置阶段完成0x1：设置阶段完成
 */
#define USB_SETUP4    (BIT(3))
#define USB_SETUP4_M  (USB_SETUP4_V << USB_SETUP4_S)
#define USB_SETUP4_V  0x00000001
#define USB_SETUP4_S  3
/** USB_OUTTKNEPDIS4:R/W1C；位位置：[4]；默认值：0；禁用端点时收到OUT令牌0x0:禁用端点时未收到OUT令牌0x1：禁用端点时接收OUT令牌
 */
#define USB_OUTTKNEPDIS4    (BIT(4))
#define USB_OUTTKNEPDIS4_M  (USB_OUTTKNEPDIS4_V << USB_OUTTKNEPDIS4_S)
#define USB_OUTTKNEPDIS4_V  0x00000001
#define USB_OUTTKNEPDIS4_S  4
/** USB_STSPHSERCVD4:R/W1C；位位置：[5]；默认值：0；接收到控制写入的状态阶段0x0：未接收到控制写的状态阶段0x1：接收到控制读的状态阶段
 */
#define USB_STSPHSERCVD4    (BIT(5))
#define USB_STSPHSERCVD4_M  (USB_STSPHSERCVD4_V << USB_STSPHSERCVD4_S)
#define USB_STSPHSERCVD4_V  0x00000001
#define USB_STSPHSERCVD4_S  5
/** USB_BACK2BACKSETUP4:R/W1C；位位置：[6]；默认值：0；收到背靠背SETUP数据包0x0：未收到背靠背设置数据包0x1：收到背靠背安装数据包
 */
#define USB_BACK2BACKSETUP4    (BIT(6))
#define USB_BACK2BACKSETUP4_M  (USB_BACK2BACKSETUP4_V << USB_BACK2BACKSETUP4_S)
#define USB_BACK2BACKSETUP4_V  0x00000001
#define USB_BACK2BACKSETUP4_S  6
/** USB_OUTPKTERR4:R/W1C；位位置：[8]；默认值：0；OUT数据包错误0x0:无OUT数据包错0x1:OUT数据包出错
 */
#define USB_OUTPKTERR4    (BIT(8))
#define USB_OUTPKTERR4_M  (USB_OUTPKTERR4_V << USB_OUTPKTERR4_S)
#define USB_OUTPKTERR4_V  0x00000001
#define USB_OUTPKTERR4_S  8
/** USB_BNAINTR4:R/W1C；位位置：[9]；默认值：0；缓冲区不可用中断0x0:No BNA中断0x1:BNA中断
 */
#define USB_BNAINTR4    (BIT(9))
#define USB_BNAINTR4_M  (USB_BNAINTR4_V << USB_BNAINTR4_S)
#define USB_BNAINTR4_V  0x00000001
#define USB_BNAINTR4_S  9
/** USB_PKTDRPSTS4:R/W1C；位位置：[11]；默认值：0；0x0：无中断0x1：数据包丢弃状态中断
 */
#define USB_PKTDRPSTS4    (BIT(11))
#define USB_PKTDRPSTS4_M  (USB_PKTDRPSTS4_V << USB_PKTDRPSTS4_S)
#define USB_PKTDRPSTS4_V  0x00000001
#define USB_PKTDRPSTS4_S  11
/** USB_BBLEERR4:R/W1C；位位置：[12]；默认值：0；0x0：无BbleErr中断0x1:BbleErr
 */
#define USB_BBLEERR4    (BIT(12))
#define USB_BBLEERR4_M  (USB_BBLEERR4_V << USB_BBLEERR4_S)
#define USB_BBLEERR4_V  0x00000001
#define USB_BBLEERR4_S  12
/** USB_nakintrt4:R/W1C；位位置：[13]；默认值：0；0x0：无NAK中断0x1:NAK中断
 */
#define USB_NAKINTRPT4    (BIT(13))
#define USB_NAKINTRPT4_M  (USB_NAKINTRPT4_V << USB_NAKINTRPT4_S)
#define USB_NAKINTRPT4_V  0x00000001
#define USB_NAKINTRPT4_S  13
/** USB_NYEPINTRPT4:R/W1C；位位置：[14]；默认值：0；0x0:无NYET中断0x1:NYET中断
 */
#define USB_NYEPINTRPT4    (BIT(14))
#define USB_NYEPINTRPT4_M  (USB_NYEPINTRPT4_V << USB_NYEPINTRPT4_S)
#define USB_NYEPINTRPT4_V  0x00000001
#define USB_NYEPINTRPT4_S  14
/** USB_stumpktrcvd4：R/W1C；位位置：[15]；默认值：0；0x0：未接收到安装包0x1：已接收到安装数据包
 */
#define USB_STUPPKTRCVD4    (BIT(15))
#define USB_STUPPKTRCVD4_M  (USB_STUPPKTRCVD4_V << USB_STUPPKTRCVD4_S)
#define USB_STUPPKTRCVD4_V  0x00000001
#define USB_STUPPKTRCVD4_S  15


/** USB_DOEPINT5_REG寄存器设备输出端点5中断寄存器
 */
#define USB_DOEPINT5_REG (SOC_DPORT_USB_BASE + 0xba8)
/** USB_xfercompl:R/W1C；位位置：[0]；默认值：0；传输完成中断0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_XFERCOMPL5    (BIT(0))
#define USB_XFERCOMPL5_M  (USB_XFERCOMPL5_V << USB_XFERCOMPL5_S)
#define USB_XFERCOMPL5_V  0x00000001
#define USB_XFERCOMPL5_S  0
/** USB_epdiscld5:R/W1C；位位置：[1]；默认值：0；端点禁用中断0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_EPDISBLD5    (BIT(1))
#define USB_EPDISBLD5_M  (USB_EPDISBLD5_V << USB_EPDISBLD5_S)
#define USB_EPDISBLD5_V  0x00000001
#define USB_EPDISBLD5_S  1
/** USB_AHBERR5:R/W1C；位位置：[2]；默认值：0；AHB错误0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_AHBERR5    (BIT(2))
#define USB_AHBERR5_M  (USB_AHBERR5_V << USB_AHBERR5_S)
#define USB_AHBERR5_V  0x00000001
#define USB_AHBERR5_S  2
/** USB_SETUP5:R/W1C；位位置：[3]；默认值：0；设置阶段完成0x0：没有设置阶段完成0x1：设置阶段完成
 */
#define USB_SETUP5    (BIT(3))
#define USB_SETUP5_M  (USB_SETUP5_V << USB_SETUP5_S)
#define USB_SETUP5_V  0x00000001
#define USB_SETUP5_S  3
/** USB_OUTTKNEPDIS5:R/W1C；位位置：[4]；默认值：0；禁用端点时收到OUT令牌0x0:禁用端点时未收到OUT令牌0x1：禁用端点时接收OUT令牌
 */
#define USB_OUTTKNEPDIS5    (BIT(4))
#define USB_OUTTKNEPDIS5_M  (USB_OUTTKNEPDIS5_V << USB_OUTTKNEPDIS5_S)
#define USB_OUTTKNEPDIS5_V  0x00000001
#define USB_OUTTKNEPDIS5_S  4
/** USB_STSPHSERCVD5:R/W1C；位位置：[5]；默认值：0；接收到控制写入的状态阶段0x0：未接收到控制写的状态阶段0x1：接收到控制读的状态阶段
 */
#define USB_STSPHSERCVD5    (BIT(5))
#define USB_STSPHSERCVD5_M  (USB_STSPHSERCVD5_V << USB_STSPHSERCVD5_S)
#define USB_STSPHSERCVD5_V  0x00000001
#define USB_STSPHSERCVD5_S  5
/** USB_BACK2BACKSETUP5:R/W1C；位位置：[6]；默认值：0；收到背靠背SETUP数据包0x0：未收到背靠背设置数据包0x1：收到背靠背安装数据包
 */
#define USB_BACK2BACKSETUP5    (BIT(6))
#define USB_BACK2BACKSETUP5_M  (USB_BACK2BACKSETUP5_V << USB_BACK2BACKSETUP5_S)
#define USB_BACK2BACKSETUP5_V  0x00000001
#define USB_BACK2BACKSETUP5_S  6
/** USB_OUTPKTERR5:R/W1C；位位置：[8]；默认值：0；OUT数据包错误0x0:无OUT数据包错0x1:OUT数据包出错
 */
#define USB_OUTPKTERR5    (BIT(8))
#define USB_OUTPKTERR5_M  (USB_OUTPKTERR5_V << USB_OUTPKTERR5_S)
#define USB_OUTPKTERR5_V  0x00000001
#define USB_OUTPKTERR5_S  8
/** USB_BNAINTR5:R/W1C；位位置：[9]；默认值：0；缓冲区不可用中断0x0:No BNA中断0x1:BNA中断
 */
#define USB_BNAINTR5    (BIT(9))
#define USB_BNAINTR5_M  (USB_BNAINTR5_V << USB_BNAINTR5_S)
#define USB_BNAINTR5_V  0x00000001
#define USB_BNAINTR5_S  9
/** USB_PKTDRPSTS5:R/W1C；位位置：[11]；默认值：0；0x0：无中断0x1：数据包丢弃状态中断
 */
#define USB_PKTDRPSTS5    (BIT(11))
#define USB_PKTDRPSTS5_M  (USB_PKTDRPSTS5_V << USB_PKTDRPSTS5_S)
#define USB_PKTDRPSTS5_V  0x00000001
#define USB_PKTDRPSTS5_S  11
/** USB_BBLEERR5:R/W1C；位位置：[12]；默认值：0；0x0：无BbleErr中断0x1:BbleErr
 */
#define USB_BBLEERR5    (BIT(12))
#define USB_BBLEERR5_M  (USB_BBLEERR5_V << USB_BBLEERR5_S)
#define USB_BBLEERR5_V  0x00000001
#define USB_BBLEERR5_S  12
/** USB_nakintrt5:R/W1C；位位置：[13]；默认值：0；0x0：无NAK中断0x1:NAK中断
 */
#define USB_NAKINTRPT5    (BIT(13))
#define USB_NAKINTRPT5_M  (USB_NAKINTRPT5_V << USB_NAKINTRPT5_S)
#define USB_NAKINTRPT5_V  0x00000001
#define USB_NAKINTRPT5_S  13
/** USB_nyepntrpt5:R/W1C；位位置：[14]；默认值：0；0x0:无NYET中断0x1:NYET中断
 */
#define USB_NYEPINTRPT5    (BIT(14))
#define USB_NYEPINTRPT5_M  (USB_NYEPINTRPT5_V << USB_NYEPINTRPT5_S)
#define USB_NYEPINTRPT5_V  0x00000001
#define USB_NYEPINTRPT5_S  14
/** USB_stumpktrcvd5：R/W1C；位位置：[15]；默认值：0；0x0：未接收到安装包0x1：已接收到安装数据包
 */
#define USB_STUPPKTRCVD5    (BIT(15))
#define USB_STUPPKTRCVD5_M  (USB_STUPPKTRCVD5_V << USB_STUPPKTRCVD5_S)
#define USB_STUPPKTRCVD5_V  0x00000001
#define USB_STUPPKTRCVD5_S  15


/** USB_DOEPINT6_REG寄存器设备输出端点6中断寄存器
 */
#define USB_DOEPINT6_REG (SOC_DPORT_USB_BASE + 0xbc8)
/** USB_XFERCOMPL6:R/W1C；位位置：[0]；默认值：0；传输完成中断0x0：无传输完成中断0x1：传输完成中断
 */
#define USB_XFERCOMPL6    (BIT(0))
#define USB_XFERCOMPL6_M  (USB_XFERCOMPL6_V << USB_XFERCOMPL6_S)
#define USB_XFERCOMPL6_V  0x00000001
#define USB_XFERCOMPL6_S  0
/** USB_epdiscld6:R/W1C；位位置：[1]；默认值：0；端点禁用中断0x0：无端点禁用中断0x1：端点禁用中断
 */
#define USB_EPDISBLD6    (BIT(1))
#define USB_EPDISBLD6_M  (USB_EPDISBLD6_V << USB_EPDISBLD6_S)
#define USB_EPDISBLD6_V  0x00000001
#define USB_EPDISBLD6_S  1
/** USB_AHBERR6:R/W1C；位位置：[2]；默认值：0；AHB错误0x0：无AHB错误中断0x1:AHB错误中断
 */
#define USB_AHBERR6    (BIT(2))
#define USB_AHBERR6_M  (USB_AHBERR6_V << USB_AHBERR6_S)
#define USB_AHBERR6_V  0x00000001
#define USB_AHBERR6_S  2
/** USB_SETUP6:R/W1C；位位置：[3]；默认值：0；设置阶段完成0x0：没有设置阶段完成0x1：设置阶段完成
 */
#define USB_SETUP6    (BIT(3))
#define USB_SETUP6_M  (USB_SETUP6_V << USB_SETUP6_S)
#define USB_SETUP6_V  0x00000001
#define USB_SETUP6_S  3
/** USB_OUTTKNEPDIS6:R/W1C；位位置：[4]；默认值：0；禁用端点时收到OUT令牌0x0:禁用端点时未收到OUT令牌0x1：禁用端点时接收OUT令牌
 */
#define USB_OUTTKNEPDIS6    (BIT(4))
#define USB_OUTTKNEPDIS6_M  (USB_OUTTKNEPDIS6_V << USB_OUTTKNEPDIS6_S)
#define USB_OUTTKNEPDIS6_V  0x00000001
#define USB_OUTTKNEPDIS6_S  4
/** USB_STSPHSERCVD6:R/W1C；位位置：[5]；默认值：0；接收到控制写入的状态阶段0x0：未接收到控制写的状态阶段0x1：接收到控制读的状态阶段
 */
#define USB_STSPHSERCVD6    (BIT(5))
#define USB_STSPHSERCVD6_M  (USB_STSPHSERCVD6_V << USB_STSPHSERCVD6_S)
#define USB_STSPHSERCVD6_V  0x00000001
#define USB_STSPHSERCVD6_S  5
/** USB_BACK2BACKSETUP6:R/W1C；位位置：[6]；默认值：0；收到背靠背SETUP数据包0x0：未收到背靠背设置数据包0x1：收到背靠背安装数据包
 */
#define USB_BACK2BACKSETUP6    (BIT(6))
#define USB_BACK2BACKSETUP6_M  (USB_BACK2BACKSETUP6_V << USB_BACK2BACKSETUP6_S)
#define USB_BACK2BACKSETUP6_V  0x00000001
#define USB_BACK2BACKSETUP6_S  6
/** USB_OUTPKTERR6:R/W1C；位位置：[8]；默认值：0；OUT数据包错误0x0:无OUT数据包错0x1:OUT数据包出错
 */
#define USB_OUTPKTERR6    (BIT(8))
#define USB_OUTPKTERR6_M  (USB_OUTPKTERR6_V << USB_OUTPKTERR6_S)
#define USB_OUTPKTERR6_V  0x00000001
#define USB_OUTPKTERR6_S  8
/** USB_BNAINTR6:R/W1C；位位置：[9]；默认值：0；缓冲区不可用中断0x0:No BNA中断0x1:BNA中断
 */
#define USB_BNAINTR6    (BIT(9))
#define USB_BNAINTR6_M  (USB_BNAINTR6_V << USB_BNAINTR6_S)
#define USB_BNAINTR6_V  0x00000001
#define USB_BNAINTR6_S  9
/** USB_PKTDRPSTS6:R/W1C；位位置：[11]；默认值：0；0x0：无中断0x1：数据包丢弃状态中断
 */
#define USB_PKTDRPSTS6    (BIT(11))
#define USB_PKTDRPSTS6_M  (USB_PKTDRPSTS6_V << USB_PKTDRPSTS6_S)
#define USB_PKTDRPSTS6_V  0x00000001
#define USB_PKTDRPSTS6_S  11
/** USB_BBLEERR6:R/W1C；位位置：[12]；默认值：0；0x0：无BbleErr中断0x1:BbleErr
 */
#define USB_BBLEERR6    (BIT(12))
#define USB_BBLEERR6_M  (USB_BBLEERR6_V << USB_BBLEERR6_S)
#define USB_BBLEERR6_V  0x00000001
#define USB_BBLEERR6_S  12
/** USB_nakintrt6:R/W1C；位位置：[13]；默认值：0；0x0：无NAK中断0x1:NAK中断
 */
#define USB_NAKINTRPT6    (BIT(13))
#define USB_NAKINTRPT6_M  (USB_NAKINTRPT6_V << USB_NAKINTRPT6_S)
#define USB_NAKINTRPT6_V  0x00000001
#define USB_NAKINTRPT6_S  13
/** USB_nyepintpt6:R/W1C；位位置：[14]；默认值：0；0x0:无NYET中断0x1:NYET中断
 */
#define USB_NYEPINTRPT6    (BIT(14))
#define USB_NYEPINTRPT6_M  (USB_NYEPINTRPT6_V << USB_NYEPINTRPT6_S)
#define USB_NYEPINTRPT6_V  0x00000001
#define USB_NYEPINTRPT6_S  14
/** USB_STUPPKTRCVD6:R/W1C；位位置：[15]；默认值：0；0x0：未接收到安装包0x1：已接收到安装数据包
 */
#define USB_STUPPKTRCVD6    (BIT(15))
#define USB_STUPPKTRCVD6_M  (USB_STUPPKTRCVD6_V << USB_STUPPKTRCVD6_S)
#define USB_STUPPKTRCVD6_V  0x00000001
#define USB_STUPPKTRCVD6_S  15




/**配置寄存器*/
/** USB_GAHBCFG_REG寄存器AHB配置寄存器
 */
#define USB_GAHBCFG_REG (SOC_DPORT_USB_BASE + 0x8)
/** USB_GLBLLNTRMSK:R/W；位位置：[0]；默认值：0；1’b0：屏蔽应用程序的中断断言。1’b1：取消屏蔽应用程序的中断断言
 */
#define USB_GLBLLNTRMSK    (BIT(0))
#define USB_GLBLLNTRMSK_M  (USB_GLBLLNTRMSK_V << USB_GLBLLNTRMSK_S)
#define USB_GLBLLNTRMSK_V  0x00000001
#define USB_GLBLLNTRMSK_S  0
/** USB_HBSTLEN:R/W；比特位置：[5:1]；默认值：0；该字段用于内部DMA模式4'b00000单个4'b0001:INCR 4'b0011 INCR4 4'b0101 INCR8 4'b00111 INCR16其他：保留
 */
#define USB_HBSTLEN    0x0000000F
#define USB_HBSTLEN_M  (USB_HBSTLEN_V << USB_HBSTLEN_S)
#define USB_HBSTLEN_V  0x0000000F
#define USB_HBSTLEN_S  1
/** USB_dman:R/W；位位置：[5]；默认值：0；当选择了仅从模式时，此位始终为0 1’b0：核心在从模式下运行1’b1：核心在DMA模式下运行
 */
#define USB_DMAEN    (BIT(5))
#define USB_DMAEN_M  (USB_DMAEN_V << USB_DMAEN_S)
#define USB_DMAEN_V  0x00000001
#define USB_DMAEN_S  5
/** USB_NPTXFEMPLVL:R/W；位位置：[7]；默认值：0；非周期TxFIFO空电平1’b0:DEIPINTn_REG。REG_TXFEMP中断表示非周期TxFIFO为半空或IN端点TxFIFO为一半空1’b1:GINTSTS_REG。USB_NPTXFEMP中断表示非周期TxFIFO完全为空或IN端点TxFIFO完全空
 */
#define USB_NPTXFEMPLVL    (BIT(7))
#define USB_NPTXFEMPLVL_M  (USB_NPTXFEMPLVL_V << USB_NPTXFEMPLVL_S)
#define USB_NPTXFEMPLVL_V  0x00000001
#define USB_NPTXFEMPLVL_S  7
/** USB_PTXFEMPLVL:R/W；位位置：[8]；默认值：0；指示何时触发核心中断寄存器（GINTSTS_REG.USB_PTXFEMP）中的周期性TxFIFO空中断位。此位仅在从模式1’b0:GINTSTS_REG中使用。USB_PTXFEMP中断指示周期TxFIFO为半空1’b1:GINTSTS_REG。USB_PTXFEMP中断表示周期TxFIFO完全为空
 */
#define USB_PTXFEMPLVL    (BIT(8))
#define USB_PTXFEMPLVL_M  (USB_PTXFEMPLVL_V << USB_PTXFEMPLVL_S)
#define USB_PTXFEMPLVL_V  0x00000001
#define USB_PTXFEMPLVL_S  8
/** USB_rememsupp:R/W；位位置：[21]；默认值：0；远程内存支持（RemMemSupp）此位被编程为使功能能够等待DMA写入传输的系统DMA完成信号1’b0：远程内存支持功能已禁用1’b1：远程内存支撑功能已启用
 */
#define USB_REMMEMSUPP    (BIT(21))
#define USB_REMMEMSUPP_M  (USB_REMMEMSUPP_V << USB_REMMEMSUPP_S)
#define USB_REMMEMSUPP_V  0x00000001
#define USB_REMMEMSUPP_S  21
/** USB_notalldmawrit:R/W；位位置：[22]；默认值：0；通知所有DMA写入事务（NotifyAllDmaWrit）该位编程为启用与通道/端点对应的所有DMA写事务的系统DMA完成功能。此位仅在GAHBCFG时有效。RemMemSupp设置为1
 */
#define USB_NOTIALLDMAWRIT    (BIT(22))
#define USB_NOTIALLDMAWRIT_M  (USB_NOTIALLDMAWRIT_V << USB_NOTIALLDMAWRIT_S)
#define USB_NOTIALLDMAWRIT_V  0x00000001
#define USB_NOTIALLDMAWRIT_S  22
/** USB_AHBSINGLE:R/W；位位置：[23]；默认值：0；AHB单一支持（AHBSingle）当内核以DMA模式运行时，该位在编程时支持传输中剩余数据的单一传输1’b0：传输中的剩余数据使用INCR突发大小1’b1发送：传输中剩余的数据使用单一突发大小发送
 */
#define USB_AHBSINGLE    (BIT(23))
#define USB_AHBSINGLE_M  (USB_AHBSINGLE_V << USB_AHBSINGLE_S)
#define USB_AHBSINGLE_V  0x00000001
#define USB_AHBSINGLE_S  23
/** USB_invdescendanes:R/W；位位置：[24]；默认值：0；反转描述符结尾1’b0：描述符结尾与AHB主结尾1’b1相同：根据AHB主末尾反转描述符结尾
 */
#define USB_INVDESCENDIANESS    (BIT(24))
#define USB_INVDESCENDIANESS_M  (USB_INVDESCENDIANESS_V << USB_INVDESCENDIANESS_S)
#define USB_INVDESCENDIANESS_V  0x00000001
#define USB_INVDESCENDIANESS_S  24


/** USB_GUSBCFG_REG寄存器USB配置寄存器
 */
#define USB_GUSBCFG_REG (SOC_DPORT_USB_BASE + 0xc)
/** USB_TOUTCAL:R/W；位位置：[3:0]；默认值：0；FS超时校准
 */
#define USB_TOUTCAL    0x00000007
#define USB_TOUTCAL_M  (USB_TOUTCAL_V << USB_TOUTCAL_S)
#define USB_TOUTCAL_V  0x00000007
#define USB_TOUTCAL_S  0
/** USB_PHYIF:R/W；位位置：[3]；默认值：0；应用程序使用此位来配置内核，以支持具有8位或16位接口的UTMI+PHY。选择ULPI PHY时，必须将其设置为8位模式1’b0:8位1’b1:16位
 */
#define USB_PHYIF    (BIT(3))
#define USB_PHYIF_M  (USB_PHYIF_V << USB_PHYIF_S)
#define USB_PHYIF_V  0x00000001
#define USB_PHYIF_S  3
/** USB_ULPI_UTMI_SEL:RO；位位置：[4]；默认值：0；1’b0:UTMI+接口1’b1:ULPI接口
 */
#define USB_ULPI_UTMI_SEL    (BIT(4))
#define USB_ULPI_UTMI_SEL_M  (USB_ULPI_UTMI_SEL_V << USB_ULPI_UTMI_SEL_S)
#define USB_ULPI_UTMI_SEL_V  0x00000001
#define USB_ULPI_UTMI_SEL_S  4
/** USB_FSINTF:R/W；位位置：[5]；默认值：0；1’b0:6针单向全速串行接口1’b1:3针双向全速串行接口
 */
#define USB_FSINTF    (BIT(5))
#define USB_FSINTF_M  (USB_FSINTF_V << USB_FSINTF_S)
#define USB_FSINTF_V  0x00000001
#define USB_FSINTF_S  5
/** USB_PHYSEL:RO；位位置：[6]；默认值：1；1’b0:USB 2.0高速UTMI+或ULPI PHY 1’b1:USB 1.1全速串行收发器
 */
#define USB_PHYSEL    (BIT(6))
#define USB_PHYSEL_M  (USB_PHYSEL_V << USB_PHYSEL_S)
#define USB_PHYSEL_V  0x00000001
#define USB_PHYSEL_S  6
/** USB_SRPCAP:R/W；位位置：[8]；默认值：0；1’b0:SRP功能未启用1’b1：SRP功能已启用
 */
#define USB_SRPCAP    (BIT(8))
#define USB_SRPCAP_M  (USB_SRPCAP_V << USB_SRPCAP_S)
#define USB_SRPCAP_V  0x00000001
#define USB_SRPCAP_S  8
/** USB_HNPCAP:R/W；位位置：[9]；默认值：0；1’b0：未启用HNP功能1’b1：已启用HNP能力
 */
#define USB_HNPCAP    (BIT(9))
#define USB_HNPCAP_M  (USB_HNPCAP_V << USB_HNPCAP_S)
#define USB_HNPCAP_V  0x00000001
#define USB_HNPCAP_S  9
/** USB_USBTRDTIM:R/W；比特位置：[14:10]；默认值：5；4'h5：当MAC接口为16位UTMI时+4'h9：当MAC界面为8位UTMI+
 */
#define USB_USBTRDTIM    0x0000000F
#define USB_USBTRDTIM_M  (USB_USBTRDTIM_V << USB_USBTRDTIM_S)
#define USB_USBTRDTIM_V  0x0000000F
#define USB_USBTRDTIM_S  10
/** USB_TERMSELDLPULSE:R/W；位位置：[22]；默认值：0；TermSel DLine Pulsing Selection 1’b0：使用utmi_txvalid（默认）1’b1的数据线脉冲
 */
#define USB_TERMSELDLPULSE    (BIT(22))
#define USB_TERMSELDLPULSE_M  (USB_TERMSELDLPULSE_V << USB_TERMSELDLPULSE_S)
#define USB_TERMSELDLPULSE_V  0x00000001
#define USB_TERMSELDLPULSE_S  22
/** USB_TXENDDELAY:R/W；位位置：[28]；默认值：0；1’b0：正常模式1’b1：Tx结束延迟
 */
#define USB_TXENDDELAY    (BIT(28))
#define USB_TXENDDELAY_M  (USB_TXENDDELAY_V << USB_TXENDDELAY_S)
#define USB_TXENDDELAY_V  0x00000001
#define USB_TXENDDELAY_S  28
/** USB_forcehsmode:R/W；位位置：[29]；默认值：0；1’b0：正常模式1’b1：强制主机模式
 */
#define USB_FORCEHSTMODE    (BIT(29))
#define USB_FORCEHSTMODE_M  (USB_FORCEHSTMODE_V << USB_FORCEHSTMODE_S)
#define USB_FORCEHSTMODE_V  0x00000001
#define USB_FORCEHSTMODE_S  29
/** USB_FORCEDEVMODE:R/W；位位置：[30]；默认值：0；1’b0：正常模式1’b1：强制设备模式
 */
#define USB_FORCEDEVMODE    (BIT(30))
#define USB_FORCEDEVMODE_M  (USB_FORCEDEVMODE_V << USB_FORCEDEVMODE_S)
#define USB_FORCEDEVMODE_V  0x00000001
#define USB_FORCEDEVMODE_S  30
/** USB_corruptxpkt:R/W；位位置：[31]；默认值：0；此位仅用于调试目的。从不将此位设置为1。应用程序应始终将1’b0写入此位1’b0:正常模式1’b1：调试模式
 */
#define USB_CORRUPTTXPKT    (BIT(31))
#define USB_CORRUPTTXPKT_M  (USB_CORRUPTTXPKT_V << USB_CORRUPTTXPKT_S)
#define USB_CORRUPTTXPKT_V  0x00000001
#define USB_CORRUPTTXPKT_S  31


/** USB_GRSTCTL_REG寄存器重置寄存器
 */
#define USB_GRSTCTL_REG (SOC_DPORT_USB_BASE + 0x10)
/** USB_CSFTRST:R_WS_SC；位位置：[0]；默认值：0；核心软重置
 */
#define USB_CSFTRST    (BIT(0))
#define USB_CSFTRST_M  (USB_CSFTRST_V << USB_CSFTRST_S)
#define USB_CSFTRST_V  0x00000001
#define USB_CSFTRST_S  0
/** USB_PIUFSSFTRST:R_WS_SC；位位置：[1]；默认值：0；1’b0：无重置1’b1：PIU FS专用控制器软重置
 */
#define USB_PIUFSSFTRST    (BIT(1))
#define USB_PIUFSSFTRST_M  (USB_PIUFSSFTRST_V << USB_PIUFSSFTRST_S)
#define USB_PIUFSSFTRST_V  0x00000001
#define USB_PIUFSSFTRST_S  1
/** USB_FRMCNTRRST:R/W1S；位位置：[2]；默认值：0；仅限主机。主机帧计数器重置。应用程序写入此位以重置内核内的（微）帧数计数器。当重置（微）帧计数器时，核心发送的后续SOF的（微）帧数为0
 */
#define USB_FRMCNTRRST    (BIT(2))
#define USB_FRMCNTRRST_M  (USB_FRMCNTRRST_V << USB_FRMCNTRRST_S)
#define USB_FRMCNTRRST_V  0x00000001
#define USB_FRMCNTRRST_S  2
/** USB_RXFFLSH：R/W1S；位位置：[4]；默认值：0；RxFIFO刷新。应用程序可以使用此位刷新整个RxFIFO，但必须首先确保内核不在事务的中间。应用程序必须在检查控制器既没有从RxFIFO读取也没有向RxFIFO 1’b0写入后才写入该位：不刷新整个RxFIFO 1'b1：刷新整个Rx FIFO
 */
#define USB_RXFFLSH    (BIT(4))
#define USB_RXFFLSH_M  (USB_RXFFLSH_V << USB_RXFFLSH_S)
#define USB_RXFFLSH_V  0x00000001
#define USB_RXFFLSH_S  4
/** USB_txffls:R/W1S；位位置：[5]；默认值：0；TxFIFO刷新。此位有选择地刷新单个或所有传输FIFO，但如果核心处于事务处理过程中，则无法刷新。应用程序必须在检查内核既没有写入TxFIFO，也没有从TxFIFO读取后才写入此位。
 */
#define USB_TXFFLSH    (BIT(5))
#define USB_TXFFLSH_M  (USB_TXFFLSH_V << USB_TXFFLSH_S)
#define USB_TXFFLSH_V  0x00000001
#define USB_TXFFLSH_S  5
/** USB_TXFNUM:R/W；位位置：[11:6]；默认值：0；TxFIFO编号。这是必须使用TxFIFO刷新位刷新的FIFO编号。在核心清除TxFIFO刷新位之前，不得更改此字段
 */
#define USB_TXFNUM    0x0000001F
#define USB_TXFNUM_M  (USB_TXFNUM_V << USB_TXFNUM_S)
#define USB_TXFNUM_V  0x0000001F
#define USB_TXFNUM_S  6
/** USB_DMAREQ:RO；位位置：[30]；默认值：0；DMA请求信号1’b0：无DMA请求1’b1：DMA请求正在进行
 */
#define USB_DMAREQ    (BIT(30))
#define USB_DMAREQ_M  (USB_DMAREQ_V << USB_DMAREQ_S)
#define USB_DMAREQ_V  0x00000001
#define USB_DMAREQ_S  30
/** USB_AHBIDLE:RO；位位置：[31]；默认值：0；AHB主闲置1’b0：非闲置1’b1：AHB主空闲
 */
#define USB_AHBIDLE    (BIT(31))
#define USB_AHBIDLE_M  (USB_AHBIDLE_V << USB_AHBIDLE_S)
#define USB_AHBIDLE_V  0x00000001
#define USB_AHBIDLE_S  31


/** USB_GRXFSIZ_REG寄存器接收FIFO大小寄存器
 */
#define USB_GRXFSIZ_REG (SOC_DPORT_USB_BASE + 0x24)
/** USB_RXFDEP:R/W；位位置：[16:0]；默认值：256；RxFIFO深度。此值以32位字表示。最小值为16，最大值为32768
 */
#define USB_RXFDEP    0x0000FFFF
#define USB_RXFDEP_M  (USB_RXFDEP_V << USB_RXFDEP_S)
#define USB_RXFDEP_V  0x0000FFFF
#define USB_RXFDEP_S  0


/** USB_GNPTXFSIZ_REG寄存器非周期传输FIFO大小寄存器
 */
#define USB_GNPTXFSIZ_REG (SOC_DPORT_USB_BASE + 0x28)
/** USB_NPTXFSTADDR:R/W；位位置：[16:0]；默认值：256；NPTxFStAddr字段描述仅对主机模式有效。此字段包含非周期传输FIFO RAM的存储器起始地址。
 */
#define USB_NPTXFSTADDR    0x0000FFFF
#define USB_NPTXFSTADDR_M  (USB_NPTXFSTADDR_V << USB_NPTXFSTADDR_S)
#define USB_NPTXFSTADDR_V  0x0000FFFF
#define USB_NPTXFSTADDR_S  0
/** USB_NPTXFDEP:R/W；位位置：[32:16]；默认值：256；当OTG_EN_DED_TX_FIFO=0时，NPTxFDep字段描述仅对主机模式或设备模式有效。最小值为16，最大值为32768。
 */
#define USB_NPTXFDEP    0x0000FFFF
#define USB_NPTXFDEP_M  (USB_NPTXFDEP_V << USB_NPTXFDEP_S)
#define USB_NPTXFDEP_V  0x0000FFFF
#define USB_NPTXFDEP_S  16


/** USB_GNPTXSTS_REG寄存器非周期传输FIFO/队列状态寄存器
 */
#define USB_GNPTXSTS_REG (SOC_DPORT_USB_BASE + 0x2c)
/** USB_NPTXFSPCAVAIL:RO；位位置：[16:0]；默认值：256；非周期TxFIFO可用空间。指示非周期TxFIFO中可用的可用空间量。值以32位字表示。
 */
#define USB_NPTXFSPCAVAIL    0x0000FFFF
#define USB_NPTXFSPCAVAIL_M  (USB_NPTXFSPCAVAIL_V << USB_NPTXFSPCAVAIL_S)
#define USB_NPTXFSPCAVAIL_V  0x0000FFFF
#define USB_NPTXFSPCAVAIL_S  0
/** USB_NPTXQSPCAVAIL:RO；比特位置：[20:16]；默认值：4；非周期性传输请求队列空间可用。指示非周期性传输请求队列中可用的可用空间量。此队列在主机模式下同时保存IN和OUT请求。设备模式只有IN请求。
 */
#define USB_NPTXQSPCAVAIL    0x0000000F
#define USB_NPTXQSPCAVAIL_M  (USB_NPTXQSPCAVAIL_V << USB_NPTXQSPCAVAIL_S)
#define USB_NPTXQSPCAVAIL_V  0x0000000F
#define USB_NPTXQSPCAVAIL_S  16
/** USB_NPTXQTOP:RO；位位置：[31:24]；默认值：0；非周期性传输请求队列的顶部。位[30:27]：通道/端点编号。位[26:25]：2’b00:IN/OUT令牌2’b01：零长度传输包（设备IN/主机OUT）2’b10:PING/CSPLIT令牌2’b11：信道暂停命令。位[24]：终止（所选信道/端点的最后一个条目）。
 */
#define USB_NPTXQTOP    0x0000007F
#define USB_NPTXQTOP_M  (USB_NPTXQTOP_V << USB_NPTXQTOP_S)
#define USB_NPTXQTOP_V  0x0000007F
#define USB_NPTXQTOP_S  24


/** USB_HCTSIZ0_REG寄存器主机通道0传输大小寄存器
 */
#define USB_HCTSIZ0_REG (SOC_DPORT_USB_BASE + 0x510)
/** USB_H_xpersize0:R/W；比特位置：[19:0]；默认值：0；非分散/聚集DMA模式：传输大小。分散/聚集DMA模式：[18:16]：保留[15:8]：NTD（传输描述符的数量）
 */
#define USB_H_XFERSIZE0    0x0007FFFF
#define USB_H_XFERSIZE0_M  (USB_H_XFERSIZE0_V << USB_H_XFERSIZE0_S)
#define USB_H_XFERSIZE0_V  0x0007FFFF
#define USB_H_XFERSIZE0_S  0
/** USB_H_PKTCNT0:R/W；位：[29:19]；默认值：0；当处于非分散/聚集DMA模式时：数据包计数。此字段由应用程序使用预期发送（OUT）或接收（in）的数据包数进行编程。分散/聚集DMA模式：保留。
 */
#define USB_H_PKTCNT0    0x000003FF
#define USB_H_PKTCNT0_M  (USB_H_PKTCNT0_V << USB_H_PKTCNT0_S)
#define USB_H_PKTCNT0_V  0x000003FF
#define USB_H_PKTCNT0_S  19
/** USB_H_PID0:R/W；位位置：[31:29]；默认值：0；2’b00:DATA0 2’b01:DATA2 2’b10:DATA1 2’b11:MDATA（非控制）/设置（控制）
 */
#define USB_H_PID0    0x00000003
#define USB_H_PID0_M  (USB_H_PID0_V << USB_H_PID0_S)
#define USB_H_PID0_V  0x00000003
#define USB_H_PID0_S  29
/** USB_H_dopg0:R/W；位位置：[31]；默认值：0；此位仅用于OUT传输。将此字段设置为1将引导主机执行PING协议1’b0：无PING协议2’b1：PING协议
 */
#define USB_H_DOPNG0    (BIT(31))
#define USB_H_DOPNG0_M  (USB_H_DOPNG0_V << USB_H_DOPNG0_S)
#define USB_H_DOPNG0_V  0x00000001
#define USB_H_DOPNG0_S  31


/** USB_HCTSIZ1_REG寄存器主机通道1传输大小寄存器
 */
#define USB_HCTSIZ1_REG (SOC_DPORT_USB_BASE + 0x530)
/** USB_H_xpersize1:R/W；比特位置：[19:0]；默认值：0；非分散/聚集DMA模式：传输大小。分散/聚集DMA模式：[18:16]：保留[15:8]：NTD（传输描述符的数量）
 */
#define USB_H_XFERSIZE1    0x0007FFFF
#define USB_H_XFERSIZE1_M  (USB_H_XFERSIZE1_V << USB_H_XFERSIZE1_S)
#define USB_H_XFERSIZE1_V  0x0007FFFF
#define USB_H_XFERSIZE1_S  0
/** USB_H_PKTCNT1:R/W；位：[29:19]；默认值：0；当处于非分散/聚集DMA模式时：数据包计数。此字段由应用程序使用预期发送（OUT）或接收（in）的数据包数进行编程。分散/聚集DMA模式：保留。
 */
#define USB_H_PKTCNT1    0x000003FF
#define USB_H_PKTCNT1_M  (USB_H_PKTCNT1_V << USB_H_PKTCNT1_S)
#define USB_H_PKTCNT1_V  0x000003FF
#define USB_H_PKTCNT1_S  19
/** USB_H_PID1:R/W；位位置：[31:29]；默认值：0；2’b00:DATA0 2’b01:DATA2 2’b10:DATA1 2’b11:MDATA（非控制）/设置（控制）
 */
#define USB_H_PID1    0x00000003
#define USB_H_PID1_M  (USB_H_PID1_V << USB_H_PID1_S)
#define USB_H_PID1_V  0x00000003
#define USB_H_PID1_S  29
/** USB_H_DOPNG1:R/W；位位置：[31]；默认值：0；此位仅用于OUT传输。将此字段设置为1将引导主机执行PING协议1’b0：无PING协议2’b1：PING协议
 */
#define USB_H_DOPNG1    (BIT(31))
#define USB_H_DOPNG1_M  (USB_H_DOPNG1_V << USB_H_DOPNG1_S)
#define USB_H_DOPNG1_V  0x00000001
#define USB_H_DOPNG1_S  31


/** USB_HCTSIZ2_REG寄存器主机通道2传输大小寄存器
 */
#define USB_HCTSIZ2_REG (SOC_DPORT_USB_BASE + 0x550)
/** USB_H_xpersize2:R/W；比特位置：[19:0]；默认值：0；非分散/聚集DMA模式：传输大小。分散/聚集DMA模式：[18:16]：保留[15:8]：NTD（传输描述符的数量）
 */
#define USB_H_XFERSIZE2    0x0007FFFF
#define USB_H_XFERSIZE2_M  (USB_H_XFERSIZE2_V << USB_H_XFERSIZE2_S)
#define USB_H_XFERSIZE2_V  0x0007FFFF
#define USB_H_XFERSIZE2_S  0
/** USB_H_PKTCNT2:R/W；位：[29:19]；默认值：0；当处于非分散/聚集DMA模式时：数据包计数。该字段由应用程序编程，具有要发送（OUT）或接收（IN）的预期分组数。分散/聚集DMA模式：保留。
 */
#define USB_H_PKTCNT2    0x000003FF
#define USB_H_PKTCNT2_M  (USB_H_PKTCNT2_V << USB_H_PKTCNT2_S)
#define USB_H_PKTCNT2_V  0x000003FF
#define USB_H_PKTCNT2_S  19
/** USB_H_PID2:R/W；位位置：[31:29]；默认值：0；2’b00:DATA0 2’b01:DATA2 2’b10:DATA1 2’b11:MDATA（非控制）/设置（控制）
 */
#define USB_H_PID2    0x00000003
#define USB_H_PID2_M  (USB_H_PID2_V << USB_H_PID2_S)
#define USB_H_PID2_V  0x00000003
#define USB_H_PID2_S  29
/** USB_H_dopg2:R/W；位位置：[31]；默认值：0；此位仅用于OUT传输。将此字段设置为1将引导主机执行PING协议1’b0：无PING协议2’b1：PING协议
 */
#define USB_H_DOPNG2    (BIT(31))
#define USB_H_DOPNG2_M  (USB_H_DOPNG2_V << USB_H_DOPNG2_S)
#define USB_H_DOPNG2_V  0x00000001
#define USB_H_DOPNG2_S  31


/** USB_HCTSIZ3_REG寄存器主机通道3传输大小寄存器
 */
#define USB_HCTSIZ3_REG (SOC_DPORT_USB_BASE + 0x570)
/** USB_H_xpersize3:R/W；比特位置：[19:0]；默认值：0；非分散/聚集DMA模式：传输大小。分散/聚集DMA模式：[18:16]：保留[15:8]：NTD（传输描述符的数量）
 */
#define USB_H_XFERSIZE3    0x0007FFFF
#define USB_H_XFERSIZE3_M  (USB_H_XFERSIZE3_V << USB_H_XFERSIZE3_S)
#define USB_H_XFERSIZE3_V  0x0007FFFF
#define USB_H_XFERSIZE3_S  0
/** USB_H_PKTCNT3:R/W；位：[29:19]；默认值：0；当处于非分散/聚集DMA模式时：数据包计数。该字段由应用程序编程，具有要发送（OUT）或接收（IN）的预期分组数。分散/聚集DMA模式：保留。
 */
#define USB_H_PKTCNT3    0x000003FF
#define USB_H_PKTCNT3_M  (USB_H_PKTCNT3_V << USB_H_PKTCNT3_S)
#define USB_H_PKTCNT3_V  0x000003FF
#define USB_H_PKTCNT3_S  19
/** USB_H_PID3:R/W；位位置：[31:29]；默认值：0；2’b00:DATA0 2’b01:DATA2 2’b10:DATA1 2’b11:MDATA（非控制）/设置（控制）
 */
#define USB_H_PID3    0x00000003
#define USB_H_PID3_M  (USB_H_PID3_V << USB_H_PID3_S)
#define USB_H_PID3_V  0x00000003
#define USB_H_PID3_S  29
/** USB_H_dopg3:R/W；位位置：[31]；默认值：0；此位仅用于OUT传输。将此字段设置为1将引导主机执行PING协议1’b0：无PING协议2’b1：PING协议
 */
#define USB_H_DOPNG3    (BIT(31))
#define USB_H_DOPNG3_M  (USB_H_DOPNG3_V << USB_H_DOPNG3_S)
#define USB_H_DOPNG3_V  0x00000001
#define USB_H_DOPNG3_S  31


/** USB_HCTSIZ4_REG寄存器主机通道4传输大小寄存器
 */
#define USB_HCTSIZ4_REG (SOC_DPORT_USB_BASE + 0x590)
/** USB_H_xpersize4:R/W；比特位置：[19:0]；默认值：0；非分散/聚集DMA模式：传输大小。分散/聚集DMA模式：[18:16]：保留[15:8]：NTD（传输描述符的数量）
 */
#define USB_H_XFERSIZE4    0x0007FFFF
#define USB_H_XFERSIZE4_M  (USB_H_XFERSIZE4_V << USB_H_XFERSIZE4_S)
#define USB_H_XFERSIZE4_V  0x0007FFFF
#define USB_H_XFERSIZE4_S  0
/** USB_H_PKTCNT4:R/W；位：[29:19]；默认值：0；当处于非分散/聚集DMA模式时：数据包计数。该字段由应用程序编程，具有要发送（OUT）或接收（IN）的预期分组数。分散/聚集DMA模式：保留。
 */
#define USB_H_PKTCNT4    0x000003FF
#define USB_H_PKTCNT4_M  (USB_H_PKTCNT4_V << USB_H_PKTCNT4_S)
#define USB_H_PKTCNT4_V  0x000003FF
#define USB_H_PKTCNT4_S  19
/** USB_H_PID4:R/W；位位置：[31:29]；默认值：0；2’b00:DATA0 2’b01:DATA2 2’b10:DATA1 2’b11:MDATA（非控制）/设置（控制）
 */
#define USB_H_PID4    0x00000003
#define USB_H_PID4_M  (USB_H_PID4_V << USB_H_PID4_S)
#define USB_H_PID4_V  0x00000003
#define USB_H_PID4_S  29
/** USB_H_dopg4:R/W；位位置：[31]；默认值：0；此位仅用于OUT传输。将此字段设置为1将引导主机执行PING协议1’b0：无PING协议2’b1：PING协议
 */
#define USB_H_DOPNG4    (BIT(31))
#define USB_H_DOPNG4_M  (USB_H_DOPNG4_V << USB_H_DOPNG4_S)
#define USB_H_DOPNG4_V  0x00000001
#define USB_H_DOPNG4_S  31


/** USB_HCTSIZ5_REG寄存器主机通道5传输大小寄存器
 */
#define USB_HCTSIZ5_REG (SOC_DPORT_USB_BASE + 0x5b0)
/** USB_H_xpersize5:R/W；比特位置：[19:0]；默认值：0；非分散/聚集DMA模式：传输大小。分散/聚集DMA模式：[18:16]：保留[15:8]：NTD（传输描述符的数量）
 */
#define USB_H_XFERSIZE5    0x0007FFFF
#define USB_H_XFERSIZE5_M  (USB_H_XFERSIZE5_V << USB_H_XFERSIZE5_S)
#define USB_H_XFERSIZE5_V  0x0007FFFF
#define USB_H_XFERSIZE5_S  0
/** USB_H_PKTCNT5:R/W；位：[29:19]；默认值：0；当处于非分散/聚集DMA模式时：数据包计数。该字段由应用程序编程，具有要发送（OUT）或接收（IN）的预期分组数。分散/聚集DMA模式：保留。
 */
#define USB_H_PKTCNT5    0x000003FF
#define USB_H_PKTCNT5_M  (USB_H_PKTCNT5_V << USB_H_PKTCNT5_S)
#define USB_H_PKTCNT5_V  0x000003FF
#define USB_H_PKTCNT5_S  19
/** USB_H_PID5:R/W；位位置：[31:29]；默认值：0；2’b00:DATA0 2’b01:DATA2 2’b10:DATA1 2’b11:MDATA（非控制）/设置（控制）
 */
#define USB_H_PID5    0x00000003
#define USB_H_PID5_M  (USB_H_PID5_V << USB_H_PID5_S)
#define USB_H_PID5_V  0x00000003
#define USB_H_PID5_S  29
/** USB_H_DOPNG5:R/W；位位置：[31]；默认值：0；此位仅用于OUT传输。将此字段设置为1将引导主机执行PING协议1’b0：无PING协议2’b1：PING协议
 */
#define USB_H_DOPNG5    (BIT(31))
#define USB_H_DOPNG5_M  (USB_H_DOPNG5_V << USB_H_DOPNG5_S)
#define USB_H_DOPNG5_V  0x00000001
#define USB_H_DOPNG5_S  31


/** USB_HCTSIZ6_REG寄存器主机通道6传输大小寄存器
 */
#define USB_HCTSIZ6_REG (SOC_DPORT_USB_BASE + 0x5d0)
/** USB_H_xpersize6:R/W；比特位置：[19:0]；默认值：0；非分散/聚集DMA模式：传输大小。分散/聚集DMA模式：[18:16]：保留[15:8]：NTD（传输描述符的数量）
 */
#define USB_H_XFERSIZE6    0x0007FFFF
#define USB_H_XFERSIZE6_M  (USB_H_XFERSIZE6_V << USB_H_XFERSIZE6_S)
#define USB_H_XFERSIZE6_V  0x0007FFFF
#define USB_H_XFERSIZE6_S  0
/** USB_H_PKTCNT6:R/W；位：[29:19]；默认值：0；当处于非分散/聚集DMA模式时：数据包计数。该字段由应用程序编程，具有要发送（OUT）或接收（IN）的预期分组数。分散/聚集DMA模式：保留。
 */
#define USB_H_PKTCNT6    0x000003FF
#define USB_H_PKTCNT6_M  (USB_H_PKTCNT6_V << USB_H_PKTCNT6_S)
#define USB_H_PKTCNT6_V  0x000003FF
#define USB_H_PKTCNT6_S  19
/** USB_H_PID6:R/W；位位置：[31:29]；默认值：0；2’b00:DATA0 2’b01:DATA2 2’b10:DATA1 2’b11:MDATA（非控制）/设置（控制）
 */
#define USB_H_PID6    0x00000003
#define USB_H_PID6_M  (USB_H_PID6_V << USB_H_PID6_S)
#define USB_H_PID6_V  0x00000003
#define USB_H_PID6_S  29
/** USB_H_dopg6:R/W；位位置：[31]；默认值：0；此位仅用于OUT传输。将此字段设置为1将引导主机执行PING协议1’b0：无PING协议2’b1：PING协议
 */
#define USB_H_DOPNG6    (BIT(31))
#define USB_H_DOPNG6_M  (USB_H_DOPNG6_V << USB_H_DOPNG6_S)
#define USB_H_DOPNG6_V  0x00000001
#define USB_H_DOPNG6_S  31


/** USB_HCTSIZ7_REG寄存器主机通道7传输大小寄存器
 */
#define USB_HCTSIZ7_REG (SOC_DPORT_USB_BASE + 0x5f0)
/** USB_H_xpersize7:R/W；比特位置：[19:0]；默认值：0；非分散/聚集DMA模式：传输大小。分散/聚集DMA模式：[18:16]：保留[15:8]：NTD（传输描述符的数量）
 */
#define USB_H_XFERSIZE7    0x0007FFFF
#define USB_H_XFERSIZE7_M  (USB_H_XFERSIZE7_V << USB_H_XFERSIZE7_S)
#define USB_H_XFERSIZE7_V  0x0007FFFF
#define USB_H_XFERSIZE7_S  0
/** USB_H_PKTCNT7:R/W；位：[29:19]；默认值：0；当处于非分散/聚集DMA模式时：数据包计数。此字段由应用程序使用预期发送（OUT）或接收（in）的数据包数进行编程。分散/聚集DMA模式：保留。
 */
#define USB_H_PKTCNT7    0x000003FF
#define USB_H_PKTCNT7_M  (USB_H_PKTCNT7_V << USB_H_PKTCNT7_S)
#define USB_H_PKTCNT7_V  0x000003FF
#define USB_H_PKTCNT7_S  19
/** USB_H_PID7:R/W；位位置：[31:29]；默认值：0；2’b00:DATA0 2’b01:DATA2 2’b10:DATA1 2’b11:MDATA（非控制）/设置（控制）
 */
#define USB_H_PID7    0x00000003
#define USB_H_PID7_M  (USB_H_PID7_V << USB_H_PID7_S)
#define USB_H_PID7_V  0x00000003
#define USB_H_PID7_S  29
/** USB_H_dopg7:R/W；位位置：[31]；默认值：0；此位仅用于OUT传输。将此字段设置为1将引导主机执行PING协议1’b0：无PING协议2’b1：PING协议
 */
#define USB_H_DOPNG7    (BIT(31))
#define USB_H_DOPNG7_M  (USB_H_DOPNG7_V << USB_H_DOPNG7_S)
#define USB_H_DOPNG7_V  0x00000001
#define USB_H_DOPNG7_S  31




/**状态寄存器*/
/** USB_GRXTSR_REG寄存器接收状态调试读取寄存器
 */
#define USB_GRXSTSR_REG (SOC_DPORT_USB_BASE + 0x1c)
/** USB_G_CHNUM:RO；位位置：[4:0]；默认值：0；频道号：仅主机。指示当前接收数据包所属的信道号。端点编号：设备仅指示当前接收数据包所属的端点编号
 */
#define USB_G_CHNUM    0x0000000F
#define USB_G_CHNUM_M  (USB_G_CHNUM_V << USB_G_CHNUM_S)
#define USB_G_CHNUM_V  0x0000000F
#define USB_G_CHNUM_S  0
/** USB_G_BCNT:RO；比特位置：[15:4]；默认值：0；在主机模式下，表示接收到的In数据包的字节计数
 */
#define USB_G_BCNT    0x000007FF
#define USB_G_BCNT_M  (USB_G_BCNT_V << USB_G_BCNT_S)
#define USB_G_BCNT_V  0x000007FF
#define USB_G_BCNT_S  4
/** USB_G_DPID:RO；比特位置：[17:15]；默认值：0；数据PID 0x0（DATA0）：DATA0 0x2（DATA1）：DATA1 0x1（DATA2）：DATA2 0x3（MDATA）：MDATA
 */
#define USB_G_DPID    0x00000003
#define USB_G_DPID_M  (USB_G_DPID_V << USB_G_DPID_S)
#define USB_G_DPID_V  0x00000003
#define USB_G_DPID_S  15
/** USB_G_pkts:RO；比特位置：[21:17]；默认值：0；0x1（OUTNAK）：设备模式下的全局OUT NAK（触发中断）0x2（INOUTDPRX）：主机模式下接收的in数据包和设备模式下接收到的OUT数据0x3（INOUTTRCOM）：主机和设备中完成的in或OUT传输（触发中断中断）0x4主机模式0x6（DSETUPRX）：在设备模式0x7（CHHALT）下接收到SETUP数据包：在主机模式下信道停止（触发中断）
 */
#define USB_G_PKTSTS    0x0000000F
#define USB_G_PKTSTS_M  (USB_G_PKTSTS_V << USB_G_PKTSTS_S)
#define USB_G_PKTSTS_V  0x0000000F
#define USB_G_PKTSTS_S  17
/** USB_G_FN:RO；位位置：[25:21]；默认值：0；这是在USB上接收数据包的（微）帧号的最低有效4位。仅当支持同步OUT端点时才支持此字段
 */
#define USB_G_FN    0x0000000F
#define USB_G_FN_M  (USB_G_FN_V << USB_G_FN_S)
#define USB_G_FN_V  0x0000000F
#define USB_G_FN_S  21


/** USB_GRXSTSP_REG寄存器接收状态读取/弹出寄存器
 */
#define USB_GRXSTSP_REG (SOC_DPORT_USB_BASE + 0x20)
/** USB_CHNUM:RO；位位置：[4:0]；默认值：0；频道号：仅主机。指示当前接收数据包所属的信道号。端点编号：设备仅指示当前接收数据包所属的端点编号
 */
#define USB_CHNUM    0x0000000F
#define USB_CHNUM_M  (USB_CHNUM_V << USB_CHNUM_S)
#define USB_CHNUM_V  0x0000000F
#define USB_CHNUM_S  0
/** USB_BCNT:RO；比特位置：[15:4]；默认值：0；在主机模式下，表示接收到的In数据包的字节计数
 */
#define USB_BCNT    0x000007FF
#define USB_BCNT_M  (USB_BCNT_V << USB_BCNT_S)
#define USB_BCNT_V  0x000007FF
#define USB_BCNT_S  4
/** USB_DPID:RO；比特位置：[17:15]；默认值：0；数据PID 0x0（DATA0）：DATA0 0x2（DATA1）：DATA1 0x1（DATA2）：DATA2 0x3（MDATA）：MDATA
 */
#define USB_DPID    0x00000003
#define USB_DPID_M  (USB_DPID_V << USB_DPID_S)
#define USB_DPID_V  0x00000003
#define USB_DPID_S  15
/** USB_pkts:RO；比特位置：[21:17]；默认值：0；0x1（OUTNAK）：设备模式下的全局OUT NAK（触发中断）0x2（INOUTDPRX）：在主机模式下接收的in数据包和在设备模式下接收到的OUT数据包0x3（INOUTTRCOM）：在主模式和设备模式下完成的in或OUT传输（触发中断（触发中断）在主机模式0x6（DSETUPRX）：在设备模式0x7（CHHALT）下接收到SETUP数据包：在主机模式下信道暂停（触发中断
 */
#define USB_PKTSTS    0x0000000F
#define USB_PKTSTS_M  (USB_PKTSTS_V << USB_PKTSTS_S)
#define USB_PKTSTS_V  0x0000000F
#define USB_PKTSTS_S  17
/** USB_FN:RO；位位置：[25:21]；默认值：0；这是在USB上接收数据包的（微）帧号的最低有效4位。仅当支持同步OUT端点时才支持此字段
 */
#define USB_FN    0x0000000F
#define USB_FN_M  (USB_FN_V << USB_FN_S)
#define USB_FN_V  0x0000000F
#define USB_FN_S  21


/** USB_GSNPSID_REG寄存器Synopsys ID寄存器
 */
#define USB_GSNPSID_REG (SOC_DPORT_USB_BASE + 0x40)
/** USB_synopsyid:RO；位位置：[32:0]；默认值：1330921482；ID寄存器
 */
#define USB_SYNOPSYSID    0xFFFFFFFF
#define USB_SYNOPSYSID_M  (USB_SYNOPSYSID_V << USB_SYNOPSYSID_S)
#define USB_SYNOPSYSID_V  0xFFFFFFFF
#define USB_SYNOPSYSID_S  0


/** USB_GHWCFG1_REG寄存器用户硬件配置1寄存器
 */
#define USB_GHWCFG1_REG (SOC_DPORT_USB_BASE + 0x44)
/** USB_EPDIR:RO；位位置：[32:0]；默认值：0；此32位字段使用每个端点两位来确定端点方向。位[31:30]：端点15方向位[29:28]：端点14方向…方向：2'b00:BIDIR（IN和OUT）端点2'b01:IN端点2'b10:OUT端点2'b11：保留
 */
#define USB_EPDIR    0xFFFFFFFF
#define USB_EPDIR_M  (USB_EPDIR_V << USB_EPDIR_S)
#define USB_EPDIR_V  0xFFFFFFFF
#define USB_EPDIR_S  0


/** USB_GHWCFG2_REG寄存器用户硬件配置2寄存器
 */
#define USB_GHWCFG2_REG (SOC_DPORT_USB_BASE + 0x48)
/** USB_OTGMODE:RO；位位置：[3:0]；默认值：0；3'b000:支持HNP和SRP的OTG（主机设备）
 */
#define USB_OTGMODE    0x00000007
#define USB_OTGMODE_M  (USB_OTGMODE_V << USB_OTGMODE_S)
#define USB_OTGMODE_V  0x00000007
#define USB_OTGMODE_S  0
/** USB_OTGARCH:RO；比特位置：[5:3]；默认值：2；2’b10：内部DMA
 */
#define USB_OTGARCH    0x00000003
#define USB_OTGARCH_M  (USB_OTGARCH_V << USB_OTGARCH_S)
#define USB_OTGARCH_V  0x00000003
#define USB_OTGARCH_S  3
/** USB_SINGPNT:RO；位位置：[5]；默认值：1；点对点1’b1：单点应用程序（无集线器和拆分支持）。
 */
#define USB_SINGPNT    (BIT(5))
#define USB_SINGPNT_M  (USB_SINGPNT_V << USB_SINGPNT_S)
#define USB_SINGPNT_V  0x00000001
#define USB_SINGPNT_S  5
/** USB_HSPHYTYPE:RO；位位置：[8:6]；默认值：0；高速PHY接口类型2’b00：不支持高速接口
 */
#define USB_HSPHYTYPE    0x00000003
#define USB_HSPHYTYPE_M  (USB_HSPHYTYPE_V << USB_HSPHYTYPE_S)
#define USB_HSPHYTYPE_V  0x00000003
#define USB_HSPHYTYPE_S  6
/** USB_FSPHYTYPE:RO；比特位置：[10:8]；默认值：1；全速PHY接口类型。
 */
#define USB_FSPHYTYPE    0x00000003
#define USB_FSPHYTYPE_M  (USB_FSPHYTYPE_V << USB_FSPHYTYPE_S)
#define USB_FSPHYTYPE_V  0x00000003
#define USB_FSPHYTYPE_S  8
/** USB_NUMDEVEPS:RO；比特位置：[14:10]；默认值：6；设备端点数。
 */
#define USB_NUMDEVEPS    0x0000000F
#define USB_NUMDEVEPS_M  (USB_NUMDEVEPS_V << USB_NUMDEVEPS_S)
#define USB_NUMDEVEPS_V  0x0000000F
#define USB_NUMDEVEPS_S  10
/** USB_numhschnl:RO；比特位置：[18:14]；默认值：7；主机通道数。
 */
#define USB_NUMHSTCHNL    0x0000000F
#define USB_NUMHSTCHNL_M  (USB_NUMHSTCHNL_V << USB_NUMHSTCHNL_S)
#define USB_NUMHSTCHNL_V  0x0000000F
#define USB_NUMHSTCHNL_S  14
/** USB_PERIOSUPPORT:RO；位位置：[18]；默认值：1；1’b0：主机模式不支持周期性OUT信道1’b1：主机模式支持周期性输出信道
 */
#define USB_PERIOSUPPORT    (BIT(18))
#define USB_PERIOSUPPORT_M  (USB_PERIOSUPPORT_V << USB_PERIOSUPPORT_S)
#define USB_PERIOSUPPORT_V  0x00000001
#define USB_PERIOSUPPORT_S  18
/** USB_dynfosizing:RO；位位置：[19]；默认值：1；1’b0：禁用动态FIFO大小1’b1：启用动态FIFO大小
 */
#define USB_DYNFIFOSIZING    (BIT(19))
#define USB_DYNFIFOSIZING_M  (USB_DYNFIFOSIZING_V << USB_DYNFIFOSIZING_S)
#define USB_DYNFIFOSIZING_V  0x00000001
#define USB_DYNFIFOSIZING_S  19
/** USB_multicintrt:RO；位位置：[20]；默认值：0；1’b0：无多处理器中断启用1’b1：多处理器中断已启用
 */
#define USB_MULTIPROCINTRPT    (BIT(20))
#define USB_MULTIPROCINTRPT_M  (USB_MULTIPROCINTRPT_V << USB_MULTIPROCINTRPT_S)
#define USB_MULTIPROCINTRPT_V  0x00000001
#define USB_MULTIPROCINTRPT_S  20
/** USB_NPTXQDEPTH:RO；位位置：[24:22]；默认值：1；非周期性请求队列深度2’b01:4
 */
#define USB_NPTXQDEPTH    0x00000003
#define USB_NPTXQDEPTH_M  (USB_NPTXQDEPTH_V << USB_NPTXQDEPTH_S)
#define USB_NPTXQDEPTH_V  0x00000003
#define USB_NPTXQDEPTH_S  22
/** USB_PTXQDEPTH:RO；比特位置：[26:24]；默认值：2；主机模式定期请求队列深度。2英尺10:8
 */
#define USB_PTXQDEPTH    0x00000003
#define USB_PTXQDEPTH_M  (USB_PTXQDEPTH_V << USB_PTXQDEPTH_S)
#define USB_PTXQDEPTH_V  0x00000003
#define USB_PTXQDEPTH_S  24
/** USB_tknq深度：RO；位位置：[31:26]；默认值：8；设备模式IN令牌序列学习队列深度。
 */
#define USB_TKNQDEPTH    0x0000001F
#define USB_TKNQDEPTH_M  (USB_TKNQDEPTH_V << USB_TKNQDEPTH_S)
#define USB_TKNQDEPTH_V  0x0000001F
#define USB_TKNQDEPTH_S  26
/** USB_OTG_ENABLE_IC_USB:RO；位位置：[31]；默认值：0；0x0（DISABLE）：禁用IC_USB全速串行收发器接口0x1（ENABLE）：启用IC_USB高速串行收发器接口
 */
#define USB_OTG_ENABLE_IC_USB    (BIT(31))
#define USB_OTG_ENABLE_IC_USB_M  (USB_OTG_ENABLE_IC_USB_V << USB_OTG_ENABLE_IC_USB_S)
#define USB_OTG_ENABLE_IC_USB_V  0x00000001
#define USB_OTG_ENABLE_IC_USB_S  31


/** USB_GHWCFG3_REG寄存器用户硬件配置3寄存器
 */
#define USB_GHWCFG3_REG (SOC_DPORT_USB_BASE + 0x4c)
/** USB_XFERSIZEWIDTH:RO；位位置：[4:0]；默认值：5；传输大小计数器的宽度0x5（WIDTH16）：传输大小计数器16位的宽度
 */
#define USB_XFERSIZEWIDTH    0x0000000F
#define USB_XFERSIZEWIDTH_M  (USB_XFERSIZEWIDTH_V << USB_XFERSIZEWIDTH_S)
#define USB_XFERSIZEWIDTH_V  0x0000000F
#define USB_XFERSIZEWIDTH_S  0
/** USB_PKTSIZEWIDTH:RO；位位置：[7:4]；默认值：3；数据包大小计数器3’b011的宽度：7位
 */
#define USB_PKTSIZEWIDTH    0x00000007
#define USB_PKTSIZEWIDTH_M  (USB_PKTSIZEWIDTH_V << USB_PKTSIZEWIDTH_S)
#define USB_PKTSIZEWIDTH_V  0x00000007
#define USB_PKTSIZEWIDTH_S  4
/** USB_OTGEN:RO；位位置：[7]；默认值：1；OTG功能已启用。
 */
#define USB_OTGEN    (BIT(7))
#define USB_OTGEN_M  (USB_OTGEN_V << USB_OTGEN_S)
#define USB_OTGEN_V  0x00000001
#define USB_OTGEN_S  7
/** USB_I2CINTSEL:RO；位位置：[8]；默认值：0；1’b0:I2C接口在控制器上不可用。
 */
#define USB_I2CINTSEL    (BIT(8))
#define USB_I2CINTSEL_M  (USB_I2CINTSEL_V << USB_I2CINTSEL_S)
#define USB_I2CINTSEL_V  0x00000001
#define USB_I2CINTSEL_S  8
/** USB_VNDCTLSUPT:RO；位位置：[9]；默认值：0；供应商控制界面不可用。
 */
#define USB_VNDCTLSUPT    (BIT(9))
#define USB_VNDCTLSUPT_M  (USB_VNDCTLSUPT_V << USB_VNDCTLSUPT_S)
#define USB_VNDCTLSUPT_V  0x00000001
#define USB_VNDCTLSUPT_S  9
/** USB_OPTFEATURE:RO；位位置：[10]；默认值：1；可选功能已删除。
 */
#define USB_OPTFEATURE    (BIT(10))
#define USB_OPTFEATURE_M  (USB_OPTFEATURE_V << USB_OPTFEATURE_S)
#define USB_OPTFEATURE_V  0x00000001
#define USB_OPTFEATURE_S  10
/** USB_RSTTYPE:RO；位位置：[11]；默认值：0；核心使用异步复位
 */
#define USB_RSTTYPE    (BIT(11))
#define USB_RSTTYPE_M  (USB_RSTTYPE_V << USB_RSTTYPE_S)
#define USB_RSTTYPE_V  0x00000001
#define USB_RSTTYPE_S  11
/** USB_adsupport:RO；位位置：[12]；默认值：0；ADP逻辑不随控制器一起出现。
 */
#define USB_ADPSUPPORT    (BIT(12))
#define USB_ADPSUPPORT_M  (USB_ADPSUPPORT_V << USB_ADPSUPPORT_S)
#define USB_ADPSUPPORT_V  0x00000001
#define USB_ADPSUPPORT_S  12
/** USB_HSICMODE:RO；位位置：[13]；默认值：0；为操作模式指定的HSIC模式。1’b0：不支持HSIC
 */
#define USB_HSICMODE    (BIT(13))
#define USB_HSICMODE_M  (USB_HSICMODE_V << USB_HSICMODE_S)
#define USB_HSICMODE_V  0x00000001
#define USB_HSICMODE_S  13
/** USB_BCSUPPORT:RO；位位置：[14]；默认值：0；1’b0：无电池充电器支持
 */
#define USB_BCSUPPORT    (BIT(14))
#define USB_BCSUPPORT_M  (USB_BCSUPPORT_V << USB_BCSUPPORT_S)
#define USB_BCSUPPORT_V  0x00000001
#define USB_BCSUPPORT_S  14
/** USB_LPMMODE:RO；位位置：[15]；默认值：0；为操作模式指定的LPM模式。
 */
#define USB_LPMMODE    (BIT(15))
#define USB_LPMMODE_M  (USB_LPMMODE_V << USB_LPMMODE_S)
#define USB_LPMMODE_V  0x00000001
#define USB_LPMMODE_S  15
/** USB_dfi深度：RO；位位置：[32:16]；默认值：256；DFIFO深度。此值以32位字为单位。
 */
#define USB_DFIFODEPTH    0x0000FFFF
#define USB_DFIFODEPTH_M  (USB_DFIFODEPTH_V << USB_DFIFODEPTH_S)
#define USB_DFIFODEPTH_V  0x0000FFFF
#define USB_DFIFODEPTH_S  16


/** USB_GHWCFG4_REG寄存器用户硬件配置4寄存器
 */
#define USB_GHWCFG4_REG (SOC_DPORT_USB_BASE + 0x50)
/** USB_G_NUMDEVPERIOEPS:RO；位位置：[4:0]；默认值：0；设备模式周期IN端点的数量。
 */
#define USB_G_NUMDEVPERIOEPS    0x0000000F
#define USB_G_NUMDEVPERIOEPS_M  (USB_G_NUMDEVPERIOEPS_V << USB_G_NUMDEVPERIOEPS_S)
#define USB_G_NUMDEVPERIOEPS_V  0x0000000F
#define USB_G_NUMDEVPERIOEPS_S  0
/** USB_G_PARTIALPWRDN:RO；位位置：[4]；默认值：1；启用部分断电。
 */
#define USB_G_PARTIALPWRDN    (BIT(4))
#define USB_G_PARTIALPWRDN_M  (USB_G_PARTIALPWRDN_V << USB_G_PARTIALPWRDN_S)
#define USB_G_PARTIALPWRDN_V  0x00000001
#define USB_G_PARTIALPWRDN_S  4
/** USB_G_AHBFREQ:RO；位位置：[5]；默认值：1；最小AHB频率小于60 MHz
 */
#define USB_G_AHBFREQ    (BIT(5))
#define USB_G_AHBFREQ_M  (USB_G_AHBFREQ_V << USB_G_AHBFREQ_S)
#define USB_G_AHBFREQ_V  0x00000001
#define USB_G_AHBFREQ_S  5
/** USB_G_hibernate：RO；位位置：[6]；默认值：0；1’b0:休眠功能未启用。
 */
#define USB_G_HIBERNATION    (BIT(6))
#define USB_G_HIBERNATION_M  (USB_G_HIBERNATION_V << USB_G_HIBERNATION_S)
#define USB_G_HIBERNATION_V  0x00000001
#define USB_G_HIBERNATION_S  6
/** USB_G_extended休眠：RO；位位置：[7]；默认值：0；未启用扩展休眠功能
 */
#define USB_G_EXTENDEDHIBERNATION    (BIT(7))
#define USB_G_EXTENDEDHIBERNATION_M  (USB_G_EXTENDEDHIBERNATION_V << USB_G_EXTENDEDHIBERNATION_S)
#define USB_G_EXTENDEDHIBERNATION_V  0x00000001
#define USB_G_EXTENDEDHIBERNATION_S  7
/** USB_G_ACGSUPT:RO；位位置：[12]；默认值：0；未启用活动时钟门控。
 */
#define USB_G_ACGSUPT    (BIT(12))
#define USB_G_ACGSUPT_M  (USB_G_ACGSUPT_V << USB_G_ACGSUPT_S)
#define USB_G_ACGSUPT_V  0x00000001
#define USB_G_ACGSUPT_S  12
/** USB_G_ENHANCEDLPMSUPT:RO；位位置：[13]；默认值：1；增强的LPM支持。
 */
#define USB_G_ENHANCEDLPMSUPT    (BIT(13))
#define USB_G_ENHANCEDLPMSUPT_M  (USB_G_ENHANCEDLPMSUPT_V << USB_G_ENHANCEDLPMSUPT_S)
#define USB_G_ENHANCEDLPMSUPT_V  0x00000001
#define USB_G_ENHANCEDLPMSUPT_S  13
/** USB_G_PHYDATAWIDTH:RO；比特位置：[16:14]；默认值：2；UTMI+PHY/ULPI到内部UTMI+包装器数据宽度（PhyDataWidth）当使用ULPI PHY时，内部包装器将ULPI转换为UTMI+2'b10:8/16位，软件可选
 */
#define USB_G_PHYDATAWIDTH    0x00000003
#define USB_G_PHYDATAWIDTH_M  (USB_G_PHYDATAWIDTH_V << USB_G_PHYDATAWIDTH_S)
#define USB_G_PHYDATAWIDTH_V  0x00000003
#define USB_G_PHYDATAWIDTH_S  14
/** USB_G_NUMCTLEPS:RO；比特位置：[20:16]；默认值：0；除了端点0之外，设备模式控制端点的数量
 */
#define USB_G_NUMCTLEPS    0x0000000F
#define USB_G_NUMCTLEPS_M  (USB_G_NUMCTLEPS_V << USB_G_NUMCTLEPS_S)
#define USB_G_NUMCTLEPS_V  0x0000000F
#define USB_G_NUMCTLEPS_S  16
/** USB_G_IDDQFLTR:RO；位位置：[20]；默认值：1；IDDIG过滤器启用。
 */
#define USB_G_IDDQFLTR    (BIT(20))
#define USB_G_IDDQFLTR_M  (USB_G_IDDQFLTR_V << USB_G_IDDQFLTR_S)
#define USB_G_IDDQFLTR_V  0x00000001
#define USB_G_IDDQFLTR_S  20
/** USB_G_vbusvalidltr:RO；位位置：[21]；默认值：1；VBUS有效筛选器已启用。
 */
#define USB_G_VBUSVALIDFLTR    (BIT(21))
#define USB_G_VBUSVALIDFLTR_M  (USB_G_VBUSVALIDFLTR_V << USB_G_VBUSVALIDFLTR_S)
#define USB_G_VBUSVALIDFLTR_V  0x00000001
#define USB_G_VBUSVALIDFLTR_S  21
/** USB_G_AVALIDFLTR:RO；位位置：[22]；默认值：1；a_valid筛选器已启用。
 */
#define USB_G_AVALIDFLTR    (BIT(22))
#define USB_G_AVALIDFLTR_M  (USB_G_AVALIDFLTR_V << USB_G_AVALIDFLTR_S)
#define USB_G_AVALIDFLTR_V  0x00000001
#define USB_G_AVALIDFLTR_S  22
/** USB_G_BVALIDFLTR:RO；位位置：[23]；默认值：1；b_valid筛选器已启用。
 */
#define USB_G_BVALIDFLTR    (BIT(23))
#define USB_G_BVALIDFLTR_M  (USB_G_BVALIDFLTR_V << USB_G_BVALIDFLTR_S)
#define USB_G_BVALIDFLTR_V  0x00000001
#define USB_G_BVALIDFLTR_S  23
/** USB_G_SESSENDFLTR:RO；位位置：[24]；默认值：1；session_end筛选器已启用。
 */
#define USB_G_SESSENDFLTR    (BIT(24))
#define USB_G_SESSENDFLTR_M  (USB_G_SESSENDFLTR_V << USB_G_SESSENDFLTR_S)
#define USB_G_SESSENDFLTR_V  0x00000001
#define USB_G_SESSENDFLTR_S  24
/** USB_G_DEDFIFOMODE:RO；位位置：[25]；默认值：1；为设备IN端点启用专用传输FIFO
 */
#define USB_G_DEDFIFOMODE    (BIT(25))
#define USB_G_DEDFIFOMODE_M  (USB_G_DEDFIFOMODE_V << USB_G_DEDFIFOMODE_S)
#define USB_G_DEDFIFOMODE_V  0x00000001
#define USB_G_DEDFIFOMODE_S  25
/** USB_G_INEPS:RO；位位置：[30:26]；默认值：4；设备模式IN端点（包括控制端点）的数量。
 */
#define USB_G_INEPS    0x0000000F
#define USB_G_INEPS_M  (USB_G_INEPS_V << USB_G_INEPS_S)
#define USB_G_INEPS_V  0x0000000F
#define USB_G_INEPS_S  26
/** USB_G_descdenabled:RO；位位置：[30]；默认值：1；0x1：分散/聚集DMA配置。
 */
#define USB_G_DESCDMAENABLED    (BIT(30))
#define USB_G_DESCDMAENABLED_M  (USB_G_DESCDMAENABLED_V << USB_G_DESCDMAENABLED_S)
#define USB_G_DESCDMAENABLED_V  0x00000001
#define USB_G_DESCDMAENABLED_S  30
/** USB_G_DESCDMA:RO；位位置：[31]；默认值：1；分散/收集DMA配置1’b1：动态配置
 */
#define USB_G_DESCDMA    (BIT(31))
#define USB_G_DESCDMA_M  (USB_G_DESCDMA_V << USB_G_DESCDMA_S)
#define USB_G_DESCDMA_V  0x00000001
#define USB_G_DESCDMA_S  31


/** USB_HFNUM_REG寄存器帧号配置Resigster
 */
#define USB_HFNUM_REG (SOC_DPORT_USB_BASE + 0x408)
/** USB_FRNUM:RO；位位置：[14:0]；默认值：16383；帧号0x0（INACTIVE）：未发送SOF 0x1（ACTIVE）：发送SOF
 */
#define USB_FRNUM    0x00003FFF
#define USB_FRNUM_M  (USB_FRNUM_V << USB_FRNUM_S)
#define USB_FRNUM_V  0x00003FFF
#define USB_FRNUM_S  0
/** USB_FRREM:RO；位位置：[32:16]；默认值：0；帧剩余时间。以PHY时钟表示当前微帧（HS）或帧（FS/LS）中剩余的时间量。
 */
#define USB_FRREM    0x0000FFFF
#define USB_FRREM_M  (USB_FRREM_V << USB_FRREM_S)
#define USB_FRREM_V  0x0000FFFF
#define USB_FRREM_S  16


/** USB_HPTXSTS_REG寄存器主机周期传输FIFO/队列状态寄存器
 */
#define USB_HPTXSTS_REG (SOC_DPORT_USB_BASE + 0x410)
/** USB_ptxfspcavaid:RO；位位置：[16:0]；默认值：256；周期性传输数据FIFO可用空间。值以32位字表示。
 */
#define USB_PTXFSPCAVAIL    0x0000FFFF
#define USB_PTXFSPCAVAIL_M  (USB_PTXFSPCAVAIL_V << USB_PTXFSPCAVAIL_S)
#define USB_PTXFSPCAVAIL_V  0x0000FFFF
#define USB_PTXFSPCAVAIL_S  0
/** USB_PTXQSPCAVAIL:RO；比特位置：[21:16]；默认值：8；定期传输请求队列空间可用。
 */
#define USB_PTXQSPCAVAIL    0x0000001F
#define USB_PTXQSPCAVAIL_M  (USB_PTXQSPCAVAIL_V << USB_PTXQSPCAVAIL_S)
#define USB_PTXQSPCAVAIL_V  0x0000001F
#define USB_PTXQSPCAVAIL_S  16
/** USB_PTXQTOP:RO；位位置：[32:24]；默认值：0；Bit[31]：奇数/偶数（微）帧。1’b0：发送偶数（微）帧位[30:27]：信道/端点号位[26:25]：类型。2’00：进/出。2’b01：零长度数据包。2'b10:CSPLIT 2'b11：禁用信道命令位[24]：终止
 */
#define USB_PTXQTOP    0x000000FF
#define USB_PTXQTOP_M  (USB_PTXQTOP_V << USB_PTXQTOP_S)
#define USB_PTXQTOP_V  0x000000FF
#define USB_PTXQTOP_S  24


/** USB_HCDMAB$n_REG寄存器主机通道$n DMA缓冲区地址寄存器
 */
#define USB_HCDMAB$N_REG (SOC_DPORT_USB_BASE + 0x51c)
/** USB_H-HCDMAB0:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址
 */
#define USB_H_HCDMAB0    0xFFFFFFFF
#define USB_H_HCDMAB0_M  (USB_H_HCDMAB0_V << USB_H_HCDMAB0_S)
#define USB_H_HCDMAB0_V  0xFFFFFFFF
#define USB_H_HCDMAB0_S  0


/** USB_HCDMAB1_REG寄存器主机通道1 DMA缓冲区地址寄存器
 */
#define USB_HCDMAB1_REG (SOC_DPORT_USB_BASE + 0x53c)
/** USB_H-HCDMAB1:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址
 */
#define USB_H_HCDMAB1    0xFFFFFFFF
#define USB_H_HCDMAB1_M  (USB_H_HCDMAB1_V << USB_H_HCDMAB1_S)
#define USB_H_HCDMAB1_V  0xFFFFFFFF
#define USB_H_HCDMAB1_S  0


/** USB_HCDMAB2_REG寄存器主机通道2 DMA缓冲区地址寄存器
 */
#define USB_HCDMAB2_REG (SOC_DPORT_USB_BASE + 0x55c)
/** USB_H-HCDMAB2:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址
 */
#define USB_H_HCDMAB2    0xFFFFFFFF
#define USB_H_HCDMAB2_M  (USB_H_HCDMAB2_V << USB_H_HCDMAB2_S)
#define USB_H_HCDMAB2_V  0xFFFFFFFF
#define USB_H_HCDMAB2_S  0


/** USB_HCDMAB3_REG寄存器主机通道3 DMA缓冲区地址寄存器
 */
#define USB_HCDMAB3_REG (SOC_DPORT_USB_BASE + 0x57c)
/** USB_H-HCDMAB3:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址
 */
#define USB_H_HCDMAB3    0xFFFFFFFF
#define USB_H_HCDMAB3_M  (USB_H_HCDMAB3_V << USB_H_HCDMAB3_S)
#define USB_H_HCDMAB3_V  0xFFFFFFFF
#define USB_H_HCDMAB3_S  0


/** USB_HCDMAB4_REG寄存器主机通道4 DMA缓冲区地址寄存器
 */
#define USB_HCDMAB4_REG (SOC_DPORT_USB_BASE + 0x59c)
/** USB_H-HCDMAB4:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址
 */
#define USB_H_HCDMAB4    0xFFFFFFFF
#define USB_H_HCDMAB4_M  (USB_H_HCDMAB4_V << USB_H_HCDMAB4_S)
#define USB_H_HCDMAB4_V  0xFFFFFFFF
#define USB_H_HCDMAB4_S  0


/** USB_HCDMAB5_REG寄存器主机通道5 DMA缓冲区地址寄存器
 */
#define USB_HCDMAB5_REG (SOC_DPORT_USB_BASE + 0x5bc)
/** USB_H-HCDMAB5:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址
 */
#define USB_H_HCDMAB5    0xFFFFFFFF
#define USB_H_HCDMAB5_M  (USB_H_HCDMAB5_V << USB_H_HCDMAB5_S)
#define USB_H_HCDMAB5_V  0xFFFFFFFF
#define USB_H_HCDMAB5_S  0


/** USB_HCDMAB6_REG寄存器主机通道6 DMA缓冲区地址寄存器
 */
#define USB_HCDMAB6_REG (SOC_DPORT_USB_BASE + 0x5dc)
/** USB_H-HCDMAB6:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址
 */
#define USB_H_HCDMAB6    0xFFFFFFFF
#define USB_H_HCDMAB6_M  (USB_H_HCDMAB6_V << USB_H_HCDMAB6_S)
#define USB_H_HCDMAB6_V  0xFFFFFFFF
#define USB_H_HCDMAB6_S  0


/** USB_HCDMAB7_REG寄存器主机通道7 DMA缓冲区地址寄存器
 */
#define USB_HCDMAB7_REG (SOC_DPORT_USB_BASE + 0x5fc)
/** USB_H-HCDMAB7:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址
 */
#define USB_H_HCDMAB7    0xFFFFFFFF
#define USB_H_HCDMAB7_M  (USB_H_HCDMAB7_V << USB_H_HCDMAB7_S)
#define USB_H_HCDMAB7_V  0xFFFFFFFF
#define USB_H_HCDMAB7_S  0


/** USB_DSTS_REG寄存器设备状态寄存器
 */
#define USB_DSTS_REG (SOC_DPORT_USB_BASE + 0x808)
/** USB_sussts:RO；位位置：[0]；默认值：0；挂起状态0x0：无挂起状态0x1：挂起状态
 */
#define USB_SUSPSTS    (BIT(0))
#define USB_SUSPSTS_M  (USB_SUSPSTS_V << USB_SUSPSTS_S)
#define USB_SUSPSTS_V  0x00000001
#define USB_SUSPSTS_S  0
/** USB_ENUMSPD:RO；位位置：[3:1]；默认值：1；0x0：高速（PHY时钟以30或60 MHz运行）0x1：全速（PHY钟以30或60MHz运行）0x2：低速（PHY钟以6 MHz运行）0x3：全速（物理时钟以48 MHz运行）
 */
#define USB_ENUMSPD    0x00000003
#define USB_ENUMSPD_M  (USB_ENUMSPD_V << USB_ENUMSPD_S)
#define USB_ENUMSPD_V  0x00000003
#define USB_ENUMSPD_S  1
/** USB_ERRTICERR:RO；位位置：[3]；默认值：0；0x0：无异常错误0x1：异常错误
 */
#define USB_ERRTICERR    (BIT(3))
#define USB_ERRTICERR_M  (USB_ERRTICERR_V << USB_ERRTICERR_S)
#define USB_ERRTICERR_V  0x00000001
#define USB_ERRTICERR_S  3
/** USB_SOFFN:RO；比特位置：[22:8]；默认值：0；接收SOF（SOFFN）的帧或微帧编号。此字段包含帧编号。
 */
#define USB_SOFFN    0x00003FFF
#define USB_SOFFN_M  (USB_SOFFN_V << USB_SOFFN_S)
#define USB_SOFFN_V  0x00003FFF
#define USB_SOFFN_S  8
/** USB_DEVLNSTS:RO；位位置：[24:22]；默认值：0；设备线状态DevLnSts[1]：D+DevLnSts[0]的逻辑电平：D的逻辑电平-
 */
#define USB_DEVLNSTS    0x00000003
#define USB_DEVLNSTS_M  (USB_DEVLNSTS_V << USB_DEVLNSTS_S)
#define USB_DEVLNSTS_V  0x00000003
#define USB_DEVLNSTS_S  22


/** USB_DTXFSTS0_REG寄存器设备IN端点传输FIFO状态寄存器0
 */
#define USB_DTXFSTS0_REG (SOC_DPORT_USB_BASE + 0x918)
/** USB_D_ineptxfspcavaid0:RO；位位置：[16:0]；默认值：0；指示端点TxFIFO中可用的可用空间量。
 */
#define USB_D_INEPTXFSPCAVAIL0    0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL0_M  (USB_D_INEPTXFSPCAVAIL0_V << USB_D_INEPTXFSPCAVAIL0_S)
#define USB_D_INEPTXFSPCAVAIL0_V  0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL0_S  0


/** USB_DIEPDMAB0_REG寄存器设备IN端点16缓冲区地址寄存器
 */
#define USB_DIEPDMAB0_REG (SOC_DPORT_USB_BASE + 0x91c)
/** USB_D_DMABUFFERADDR0:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_D_DMABUFFERADDR0    0xFFFFFFFF
#define USB_D_DMABUFFERADDR0_M  (USB_D_DMABUFFERADDR0_V << USB_D_DMABUFFERADDR0_S)
#define USB_D_DMABUFFERADDR0_V  0xFFFFFFFF
#define USB_D_DMABUFFERADDR0_S  0


/** USB_DTXFSTS1_REG寄存器设备IN端点传输FIFO状态寄存器1
 */
#define USB_DTXFSTS1_REG (SOC_DPORT_USB_BASE + 0x938)
/** USB_D_INEPTXFSPCAVAIL1:RO；位位置：[16:0]；默认值：0；指示端点TxFIFO中可用的可用空间量。
 */
#define USB_D_INEPTXFSPCAVAIL1    0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL1_M  (USB_D_INEPTXFSPCAVAIL1_V << USB_D_INEPTXFSPCAVAIL1_S)
#define USB_D_INEPTXFSPCAVAIL1_V  0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL1_S  0


/** USB_DIEPDMAB1_REG寄存器设备IN端点16缓冲区地址寄存器
 */
#define USB_DIEPDMAB1_REG (SOC_DPORT_USB_BASE + 0x93c)
/** USB_D_DMABUFFERADDR1：RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_D_DMABUFFERADDR1    0xFFFFFFFF
#define USB_D_DMABUFFERADDR1_M  (USB_D_DMABUFFERADDR1_V << USB_D_DMABUFFERADDR1_S)
#define USB_D_DMABUFFERADDR1_V  0xFFFFFFFF
#define USB_D_DMABUFFERADDR1_S  0


/** USB_DTXFSTS2_REG寄存器设备IN端点传输FIFO状态寄存器2
 */
#define USB_DTXFSTS2_REG (SOC_DPORT_USB_BASE + 0x958)
/** USB_D_ineptxfspcavaid2:RO；位位置：[16:0]；默认值：0；指示端点TxFIFO中可用的可用空间量。
 */
#define USB_D_INEPTXFSPCAVAIL2    0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL2_M  (USB_D_INEPTXFSPCAVAIL2_V << USB_D_INEPTXFSPCAVAIL2_S)
#define USB_D_INEPTXFSPCAVAIL2_V  0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL2_S  0


/** USB_DIEPDMAB2_REG寄存器设备IN端点16缓冲区地址寄存器
 */
#define USB_DIEPDMAB2_REG (SOC_DPORT_USB_BASE + 0x95c)
/** USB_D_DMABUFFERADDR2:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_D_DMABUFFERADDR2    0xFFFFFFFF
#define USB_D_DMABUFFERADDR2_M  (USB_D_DMABUFFERADDR2_V << USB_D_DMABUFFERADDR2_S)
#define USB_D_DMABUFFERADDR2_V  0xFFFFFFFF
#define USB_D_DMABUFFERADDR2_S  0


/** USB_DTXFSTS3_REG寄存器设备入端点传输FIFO状态寄存器3
 */
#define USB_DTXFSTS3_REG (SOC_DPORT_USB_BASE + 0x978)
/** USB_D_ineptxfspcavaid3:RO；位位置：[16:0]；默认值：0；指示端点TxFIFO中可用的可用空间量。
 */
#define USB_D_INEPTXFSPCAVAIL3    0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL3_M  (USB_D_INEPTXFSPCAVAIL3_V << USB_D_INEPTXFSPCAVAIL3_S)
#define USB_D_INEPTXFSPCAVAIL3_V  0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL3_S  0


/** USB_DIEPDMAB3_REG寄存器设备IN端点16缓冲区地址寄存器
 */
#define USB_DIEPDMAB3_REG (SOC_DPORT_USB_BASE + 0x97c)
/** USB_D_DMABUFFERADDR3:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_D_DMABUFFERADDR3    0xFFFFFFFF
#define USB_D_DMABUFFERADDR3_M  (USB_D_DMABUFFERADDR3_V << USB_D_DMABUFFERADDR3_S)
#define USB_D_DMABUFFERADDR3_V  0xFFFFFFFF
#define USB_D_DMABUFFERADDR3_S  0


/** USB_DTXFSTS4_REG寄存器设备入端点传输FIFO状态寄存器4
 */
#define USB_DTXFSTS4_REG (SOC_DPORT_USB_BASE + 0x998)
/** USB_D_INEPTXFSPCAVAIL4:RO；位位置：[16:0]；默认值：0；指示端点TxFIFO中可用的可用空间量。
 */
#define USB_D_INEPTXFSPCAVAIL4    0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL4_M  (USB_D_INEPTXFSPCAVAIL4_V << USB_D_INEPTXFSPCAVAIL4_S)
#define USB_D_INEPTXFSPCAVAIL4_V  0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL4_S  0


/** USB_DIEPDMAB4_REG寄存器设备IN端点16缓冲区地址寄存器
 */
#define USB_DIEPDMAB4_REG (SOC_DPORT_USB_BASE + 0x99c)
/** USB_D_DMABUFFERADDR4:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_D_DMABUFFERADDR4    0xFFFFFFFF
#define USB_D_DMABUFFERADDR4_M  (USB_D_DMABUFFERADDR4_V << USB_D_DMABUFFERADDR4_S)
#define USB_D_DMABUFFERADDR4_V  0xFFFFFFFF
#define USB_D_DMABUFFERADDR4_S  0


/** USB_DTXFSTS5_REG寄存器设备入端点传输FIFO状态寄存器5
 */
#define USB_DTXFSTS5_REG (SOC_DPORT_USB_BASE + 0x9b8)
/** USB_D_INEPTXFSPCAVAIL5:RO；位位置：[16:0]；默认值：0；指示端点TxFIFO中可用的可用空间量。
 */
#define USB_D_INEPTXFSPCAVAIL5    0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL5_M  (USB_D_INEPTXFSPCAVAIL5_V << USB_D_INEPTXFSPCAVAIL5_S)
#define USB_D_INEPTXFSPCAVAIL5_V  0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL5_S  0


/** USB_DIEPDMAB5_REG寄存器设备IN端点16缓冲区地址寄存器
 */
#define USB_DIEPDMAB5_REG (SOC_DPORT_USB_BASE + 0x9bc)
/** USB_D_DMABUFFERADDR5:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_D_DMABUFFERADDR5    0xFFFFFFFF
#define USB_D_DMABUFFERADDR5_M  (USB_D_DMABUFFERADDR5_V << USB_D_DMABUFFERADDR5_S)
#define USB_D_DMABUFFERADDR5_V  0xFFFFFFFF
#define USB_D_DMABUFFERADDR5_S  0


/** USB_DTXFSTS6_REG寄存器设备入端点传输FIFO状态寄存器6
 */
#define USB_DTXFSTS6_REG (SOC_DPORT_USB_BASE + 0x9d8)
/** USB_D_INEPTXFSPCAVAIL6:RO；位位置：[16:0]；默认值：0；指示端点TxFIFO中可用的可用空间量。
 */
#define USB_D_INEPTXFSPCAVAIL6    0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL6_M  (USB_D_INEPTXFSPCAVAIL6_V << USB_D_INEPTXFSPCAVAIL6_S)
#define USB_D_INEPTXFSPCAVAIL6_V  0x0000FFFF
#define USB_D_INEPTXFSPCAVAIL6_S  0


/** USB_DIEPDMAB6_REG寄存器设备IN端点16缓冲区地址寄存器
 */
#define USB_DIEPDMAB6_REG (SOC_DPORT_USB_BASE + 0x9dc)
/** USB_D_DMABUFFERADDR6:RO；位位置：[32:0]；默认值：0；保存当前缓冲区地址。当相应端点的数据传输正在进行时，该寄存器将被更新。此寄存器仅在分散/聚集DMA模式下存在。否则将保留此字段。
 */
#define USB_D_DMABUFFERADDR6    0xFFFFFFFF
#define USB_D_DMABUFFERADDR6_M  (USB_D_DMABUFFERADDR6_V << USB_D_DMABUFFERADDR6_S)
#define USB_D_DMABUFFERADDR6_V  0xFFFFFFFF
#define USB_D_DMABUFFERADDR6_S  0




#ifdef __cplusplus
}
#endif

