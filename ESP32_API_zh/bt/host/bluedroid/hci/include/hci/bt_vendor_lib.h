/******************************************************************************
 * 版权所有（C）2009-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef BT_VENDOR_LIB_H
#define BT_VENDOR_LIB_H

#include <stdint.h>
//#包括<sys/cdfs.h>
//#包括<sys/types.h>

/**结构类型*/


/**Typedefs和定义*/

/**供应商特定操作OPCODE*/
typedef enum {
    /*  [操作]打开或关闭BT控制器。[input param]指向int类型的指针，内容为bt_vendor_power_state_t。类型转换：（int）param。[return]0-默认值，无需在意。[回调]无。
     */
    BT_VND_OP_POWER_CTRL,

    /*  [操作]在BT控制器上执行任何供应商特定的初始化或配置。这在堆栈初始化之前调用。[input param]无。[return]0-默认值，无需在意。〔callback〕完成供应商特定初始化后，必须调用fwcfg_cb通知堆栈完成。
     */
    BT_VND_OP_FW_CFG,

    /*  [操作]在BT控制器上执行任何供应商特定的SCO/PCM配置。这在堆栈初始化后调用。[input param]无。[return]0-默认值，无需在意。〔callback〕一旦完成特定于供应商的SCO配置，必须调用scocfg_cb通知堆栈完成。
     */
    BT_VND_OP_SCO_CFG,

    /*  [操作]打开连接BT控制器的UART端口。这在堆栈初始化之前调用。[input param]指向打开文件描述符的int数组类型的指针。在bt_vendor_HCI_channels_t中给出了HCI通道到int阵列中fd插槽的映射。而且，它需要供应商库在返回调用之前填充内容。类型转换：（int（）[]）参数。[return]打开的文件描述符数。有效编号：1-通过同一fd（例如UART）的CMD/EVT/ACL In/ACL Out；2-一个fd上的CMD/EVT，另一个fd的ACL In/ACL Out；4-CMD、EVT、ACL In、ACL Out位于各自的fd上[回调]无。
     */
    BT_VND_OP_USERIAL_OPEN,

    /*  [操作]关闭先前打开的UART端口。[输入参数]无。[return]0-默认值，无需在意。[回调]无。
     */
    BT_VND_OP_USERIAL_CLOSE,

    /*  [操作]获取LPM空闲超时（毫秒）。一旦下游HCI分组被传送，堆栈使用该信息在尝试去断言LPM WAKE信号之前启动定时器延迟。[input param]堆栈传入的uint32_t类型指针。而且，它需要供应商库在返回调用之前填充内容。类型转换：（uint32_t）参数。[return]0-默认值，无需在意。[回调]无。
     */
    BT_VND_OP_GET_LPM_IDLE_TIMEOUT,

    /*  [操作]启用或禁用BT控制器上的LPM模式。[input param]指向uint8_t类型的指针，内容为bt_vendor_lpm_mode_t。类型转换：（uint8_t）参数。[return]0-默认值，无需在意。〔callback〕在lpm禁用/启用过程完成后，必须调用lpm_cb以通知堆栈该过程已完成。
     */
    BT_VND_OP_LPM_SET_MODE,

    /*  [操作]在BT控制器上断言或取消LPM WAKE。[input param]指向uint8_t类型的指针，内容为bt_vendor_lpm_wake_state_t。类型转换：（uint8_t）参数。[return]0-默认值，无需在意。[回调]无。
     */
    BT_VND_OP_LPM_WAKE_SET_STATE,

    /*  [操作]执行与音频状态更改相关的任何供应商特定命令。[input param]指向bt_vendor_op_audio_state_t的指针，指示设置了什么音频状态。[return]0-默认值，无需在意。[回调]无。
     */
    BT_VND_OP_SET_AUDIO_STATE,

    /*  [操作]对供应商模块的epilog调用，以便它可以在调用方调用cleanup（）之前执行任何供应商特定的过程（例如，向BT控制器发送HCI_RESET）。[input param]无。[return]0-默认值，无需在意。[callback]必须调用epilog_cb，以通知堆栈特定于供应商的epilog进程完成后的完成情况。
     */
    BT_VND_OP_EPILOG,
} bt_vendor_opcode_t;

/**电源开/关控制状态*/
typedef enum {
    BT_VND_PWR_OFF,
    BT_VND_PWR_ON,
}  bt_vendor_power_state_t;

/** 在BT_VND_OP_USERIAL_OPEN操作中使用的文件描述符数组中定义HCI通道标识符。
 */
typedef enum {
    CH_CMD,     // HCI命令通道
    CH_EVT,     // HCI事件通道
    CH_ACL_OUT, // HCI ACL下游通道
    CH_ACL_IN,  // HCI ACL上游通道

    CH_MAX      // 通道总数
}  bt_vendor_hci_channels_t;

/**LPM禁用/启用请求*/
typedef enum {
    BT_VND_LPM_DISABLE,
    BT_VND_LPM_ENABLE,
} bt_vendor_lpm_mode_t;

/**LPM WAKE设置状态请求*/
typedef enum {
    BT_VND_LPM_WAKE_ASSERT,
    BT_VND_LPM_WAKE_DEASSERT,
} bt_vendor_lpm_wake_state_t;

/**回调结果值*/
typedef enum {
    BT_VND_OP_RESULT_SUCCESS,
    BT_VND_OP_RESULT_FAIL,
} bt_vendor_op_result_t;

/**音频（SCO）状态更改触发VS配置命令*/
typedef struct {
    uint16_t    handle;
    uint16_t    peer_codec;
    uint16_t    state;
} bt_vendor_op_audio_state_t;

/*
 * 蓝牙主机/控制器供应商回调结构。
 */

/* 供应商初始化/配置回调*/
typedef void (*cfg_result_cb)(bt_vendor_op_result_t result);

/* 数据路径缓冲区分配回调（callout）
 *
 *  如果缓冲区用于构建将通过xmit_cb发送到BT控制器的HCI命令包，则供应商库需要通过HCI库的alloc callout函数请求缓冲区。
 *
 *  对于每个缓冲区分配，请求的大小必须足够大，以容纳下面的标头加上完整的HCI数据包——typedef struct｛uint16_t event；uint16_t len；uint 16_t offset；uint6_t layer_specific；｝HC_BT_HDR；
 *
 *  HCI lib返回一个指向缓冲区的指针，Vendor lib应使用该缓冲区构造HCI命令包，格式如下：
 *
 *  --------------------------------------------|HC_BT_HDR|HCI命令|
 *  --------------------------------------------其中HC_BT_HDR。事件=0x2000；HC_BT_HDR。len=HCI命令的长度；HC_BT_HDR。偏移=0；HC_BT_HDR。层特定=0；
 *
 *  例如，HCI_RESET命令将形成为
 *  ------------------------|HC_BT_HDR|03|0c|00|
 *  ------------------------用HC_ BT_。事件=0x2000；HC_BT_HDR。len=3；HC_BT_HDR。偏移=0；HC_BT_HDR。层特定=0；
 */
typedef void *(*malloc_cb)(int size);

/* 数据路径缓冲区释放回调（callout）*/
typedef void (*mdealloc_cb)(void *p_buf);

/* 定义cmdxmit_cb的回调
 *
 *  HCI lib将在返回命令完成包时调用的回调函数。供应商库负责通过调用dealloc callout函数来释放在p_mem参数处传入的缓冲区。
 */
typedef void (*tINT_CMD_CBACK)(void *p_mem);

/* hci命令包传输回调（callout）
 *
 *  供应商库调用xmit_cb callout函数，以便向BT控制器发送HCI命令包。承载HCI命令包内容的缓冲区需要首先通过alloc callout函数分配。一旦HCI lib将数据包内容传递给BT控制器，它将释放Vendor lib的缓冲区。
 *
 *  供应商库还需要提供一个回调函数（p_cback），HCI库将在返回命令完成包时调用该函数。
 *
 *  操作码参数给出HCI命令包的HCI opcode（OGF和OCF的组合）。例如，HCI_RESET命令包的操作码=0x0c03。
 */
typedef uint8_t (*cmd_xmit_cb)(uint16_t opcode, void *p_buf, tINT_CMD_CBACK p_cback);

typedef struct {
    /**设置为sizeof（bt_vendor_callback_t）*/
    size_t         size;

    /*
     * 回调和调用函数已在HCI库（libbt-HCI.so）中实现。
     */

    /* 通知调用方固件配置请求的结果*/
    cfg_result_cb  fwcfg_cb;

    /* 通知调用方sco配置请求的结果*/
    cfg_result_cb  scocfg_cb;

    /* 通知调用方lpm启用/禁用的结果*/
    cfg_result_cb  lpm_cb;

    /* 通知编解码器设置的结果*/
    cfg_result_cb audio_state_cb;

    /* 缓冲区分配请求*/
    malloc_cb   alloc;

    /* 缓冲区释放请求*/
    mdealloc_cb dealloc;

    /* hci命令包传输请求*/
    cmd_xmit_cb xmit_cb;

    /* 通知调用方完成epilog进程*/
    cfg_result_cb epilog_cb;
} bt_vendor_callbacks_t;

/*
 * 蓝牙主机/控制器厂商接口
 */
typedef struct {
    /**设置为sizeof（bt_vndor_interface_t）*/
    size_t          size;

    /*
     * 函数需要在Vendor库（libbt Vendor.so）中实现。
     */

    /**
     * 调用者将打开接口并将回调例程传递给该接口的实现。
     */
    int   (*init)(const bt_vendor_callbacks_t *p_cb, unsigned char *local_bdaddr);

    /**供应商特定操作*/
    int (*op)(bt_vendor_opcode_t opcode, void *param);

    /**关闭界面*/
    void  (*cleanup)(void);
} bt_vendor_interface_t;


/*
 * 外部共享库函数/数据
 */

/* DLib的入口点--供应商库需要实现bt_Vendor_interface_t结构的主体，并使用以下名称作为变量名。HCI库将使用此符号名称通过dlsym调用获取对象的地址。
 */
//外部常量bt_vendor_interface_t BLUETOOTH_vendor_LIB_interface；

#endif /* BT_VENDOR_LIB_H */

