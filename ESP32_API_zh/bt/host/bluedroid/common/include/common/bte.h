/******************************************************************************
 * 版权所有（C）2001-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 该文件包含bte项目的常量和定义
 *
 ******************************************************************************/
#ifndef BTE_H
#define BTE_H

//#包括<osi/signature.h>
//#包含<signal.h>
//#包括<pthread.h>
#include "common/bt_target.h"

/* 默认情况下，关闭时，波特率重置115kbits。对于杀死BTE驱动程序并移除/重置BT芯片的平台来说，这不需要
 */
#ifndef BTE_RESET_BAUD_ON_BT_DISABLE
#define BTE_RESET_BAUD_ON_BT_DISABLE TRUE
#endif

/* 目标模式（基于硬件上的跳线设置[参见用户手册]）*/
enum {
    /* BTE                  BBY                     */
    /* J3   J4              SW3-3   SW3-2   SW3-1   */
    /* -------------------------------------------- */
    BTE_MODE_SERIAL_APP,    /* OUT OUT OFF OFF OFF样本串口应用程序*/
    BTE_MODE_APPL,          /* 通过RPC与测试仪一起使用的IN OUT OFF ON目标*/
    BTE_MODE_RESERVED,      /* OUT IN OFF ON OFF保留*/
    BTE_MODE_SAMPLE_APPS,   /* IN IN OFF ON样品应用（ICP/HSP）*/
    BTE_MODE_DONGLE,        /* 尚不支持ON-OFF-OFF加密狗模式*/
    BTE_MODE_APPL_PROTOCOL_TRACE, /* 这是一种伪模式，不允许在没有rpc的应用程序中进行协议跟踪*/
    BTE_MODE_INVALID
};

extern volatile UINT8    bte_target_mode;    /* 指示板正在运行的模式*/

/* 启动选项*/
extern UINT32 bte_startup_options;                      /* 启动时的开关和跳线设置*/
void bte_get_startup_options(UINT32 *p_options);        /* 用于获取启动选项的平台特定功能*/

#define BTE_OPTIONS_TARGET_MODE_MASK    0x00000007      /* 位2-0表示目标模式（QuickConnect:jp3和jp4，BBY:SW3-1和SW3-2）*/


/****************************************************************************
 * 用于定义生成的应用程序类型的定义
 ****************************************************************************/
#define BUILD_HCITOOL         FALSE
#define BUILD_L2PING          FALSE


#define LINUX_FM_DRIVER_INCLUDED        FALSE


/* hcisu用户操作。应该进入btype以避免冲突！*/
#define BT_EVT_TO_HCISU_USERIAL_OP (0x0080 | BT_EVT_HCISU)
/* 上述hcisu事件的操作*/
#define BT_HCISU_USERIAL_OPEN (0)   /* 打开串行端口调用USERIAL_open（）*/
#define BT_HCISU_USERIAL_CLOSE (1)  /* 关闭用户端口*/
/* 与关闭操作关联的选项*/
#define BT_HCISU_USERIAL_CL_NO_DIS_BT   0 /* 不要触摸bt_wake和powergpio*/
#define BT_HCISU_USERIAL_CL_DIS_BT      1 /* 将电源和bt_wake置于定义的关闭状态以保持电源*/
/* 回调的状态代码*/
/*
#define BTE_HCISU_USERIAL_FAIL 0#define BTE-HCISU_SERIAL_OK 1typedef void（tOSSERIAL_MSG_BACK）（int状态）；typedef结构tHCISU_USERIAL_MSG_tag｛BT_HDR HDR；tOSIREAL_MSG_CBACK p_CBACK；UINT8端口；//端口号UINT8 op；UINT9选项；//操作选项。取决于操作｝tHCIS_USERIAL_MSG；

extern void bte_hcisus_userial_oper（tOSSERIAL_MSG_BACK*p_CBACK，UINT8端口，UINT8op，UINT9选项）；
*/

/* 指向向HCI传输发送HCI命令和数据的函数的指针*/
extern int (*p_bte_hci_send)(UINT16 port, BT_HDR *p_msg);


/* 协议跟踪掩码*/
extern UINT32 bte_proto_trace_mask;

typedef struct tBAUD_REG_tag {
    UINT8 DHBR;
    UINT8 DLBR;
    UINT8 ExplicitBaudRate0;
    UINT8 ExplicitBaudRate1;
    UINT8 ExplicitBaudRate2;
    UINT8 ExplicitBaudRate3;
} tBAUD_REG;


extern const tBAUD_REG baud_rate_regs[];

#endif  /* BTE_H */

