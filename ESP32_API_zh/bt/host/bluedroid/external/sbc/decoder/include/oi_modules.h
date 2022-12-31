/******************************************************************************
 * 版权所有（C）2014 Android开源项目版权所有2002-2004 Open Interface North America，Inc.保留所有权利。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/
#ifndef _OI_MODULES_H
#define _OI_MODULES_H
/**
 * @file
 *
 * 定义小型堆栈组件的枚举类型。
 *
 */

/**********************************************************************************
  $版本：#1$
***********************************************************************************/


/**\addtogroup其他杂项API*/
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif


/**
 * 此枚举列出了用于引用BLUEmagic 3.0协议栈组件、配置文件和其他功能的常量。
 *
 * 为了区分模块的类型，项目用标记分组，以描述组的开始和结束
 *
 * 模块类型用于各种目的：调试打印语句中的标识访问初始化标志访问配置表
 */

typedef enum {
    /* 配置文件和协议-->更新oi_debug.c和oi_config_table.c*/

    /*   XX-->保持枚举值最新！*/
    OI_MODULE_AT,               /**<00 AT命令处理*/
    OI_MODULE_A2DP,             /**<01高级音频分发配置文件*/
    OI_MODULE_AVCTP,            /**<02视听控制传输配置文件*/
    OI_MODULE_AVDTP,            /**<03视听分发协议*/
    OI_MODULE_AVRCP,            /**<04视听遥控配置文件*/
    OI_MODULE_BIP_CLI,          /**<05基本成像配置文件协议客户端*/
    OI_MODULE_BIP_SRV,          /**<06基本成像配置文件协议服务器*/
    OI_MODULE_BNEP,             /**<07蓝牙网络封装协议*/
    OI_MODULE_BPP_SENDER,       /**<08基本打印配置文件*/
    OI_MODULE_BPP_PRINTER,      /**<09基本打印配置文件*/
    OI_MODULE_CTP,              /**<10无绳电话配置文件*/
    OI_MODULE_DUN,              /**<11拨号网络配置文件*/
    OI_MODULE_FAX,              /**<12传真配置文件*/
    OI_MODULE_FTP_CLI,          /**<13文件传输配置文件协议客户端*/
    OI_MODULE_FTP_SRV,          /**<14文件传输配置文件协议服务器*/
    OI_MODULE_HANDSFREE,        /**<15免提模式*/
    OI_MODULE_HANDSFREE_AG,     /**<16免提模式*/
    OI_MODULE_HCRP_CLI,         /**<17硬拷贝电缆更换配置文件*/
    OI_MODULE_HCRP_SRV,         /**<18硬拷贝电缆更换配置文件*/
    OI_MODULE_HEADSET,          /**<19耳机模式*/
    OI_MODULE_HEADSET_AG,       /**<20耳机模式*/
    OI_MODULE_HID,              /**<21人机界面设备配置文件*/
    OI_MODULE_INTERCOM,         /**<22对讲机配置文件*/
    OI_MODULE_OBEX_CLI,         /**<23 OBEX协议客户端，通用对象交换配置文件*/
    OI_MODULE_OBEX_SRV,         /**<24 OBEX协议服务器，通用对象交换配置文件*/
    OI_MODULE_OPP_CLI,          /**<25对象推送配置文件协议客户端*/
    OI_MODULE_OPP_SRV,          /**<26对象推送配置文件协议服务器*/
    OI_MODULE_PAN,              /**<27 PAN配置文件*/
    OI_MODULE_PBAP_CLI,         /**<28电话簿访问配置文件客户端*/
    OI_MODULE_PBAP_SRV,         /**<29电话簿访问配置文件服务器*/
    OI_MODULE_SAP_CLI,          /**<30 SIM卡接入模式*/
    OI_MODULE_SAP_SRV,          /**<31 SIM卡接入模式*/
    OI_MODULE_SPP,              /**<32串行端口配置文件*/
    OI_MODULE_SYNC_CLI,         /**<33同步配置文件*/
    OI_MODULE_SYNC_SRV,         /**<34同步配置文件*/
    OI_MODULE_SYNC_CMD_CLI,     /**<35同步配置文件*/
    OI_MODULE_SYNC_CMD_SRV,     /**<36同步配置文件*/
    OI_MODULE_SYNCML,           /**<37 SyncML配置文件*/
    OI_MODULE_TCS,              /**<38 TCS二进制*/
    OI_MODULE_VDP,              /**<39视频分发配置文件*/

    /* corestack组件-->对oi_debug.c和oi_config_table.c的更新*/

    OI_MODULE_COMMON_CONFIG,    /**<40常见配置，模块除了用于配置结构之外没有其他含义*/
    OI_MODULE_CMDCHAIN,         /**<41命令链接实用程序*/
    OI_MODULE_DISPATCH,         /**<42调度员*/
    OI_MODULE_DATAELEM,         /**<43数据元素，编组员*/
    OI_MODULE_DEVMGR,           /**<44设备管理器*/
    OI_MODULE_DEVMGR_MODES,     /**<45设备管理器可连接性/可发现性模式*/
    OI_MODULE_HCI,              /**<46主机控制器接口命令层*/
    OI_MODULE_L2CAP,            /**< 47 L2CAP */
    OI_MODULE_MEMMGR,           /**<48个执行内存管理的模块*/
    OI_MODULE_POLICYMGR,        /**<49政策经理*/
    OI_MODULE_RFCOMM,           /**< 50 RFCOMM */
    OI_MODULE_RFCOMM_SD,        /**<51 RFCOMM服务发现*/
    OI_MODULE_SDP_CLI,          /**<52服务发现协议客户端*/
    OI_MODULE_SDP_SRV,          /**<53服务发现协议服务器*/
    OI_MODULE_SDPDB,            /**<54服务发现协议数据库*/
    OI_MODULE_SECMGR,           /**<55安全经理*/
    OI_MODULE_SNIFFLOG,         /**<56嗅探日志*/
    OI_MODULE_SUPPORT,          /**<57个支持函数，包括CThru Dispatcher、时间函数和堆栈初始化*/
    OI_MODULE_TRANSPORT,        /**<58 HCI命令层和驱动程序之间的传输层*/
    OI_MODULE_TEST,             /**<59用于调试内部测试程序的输出*/
    OI_MODULE_XML,              /**<60 XML/CSS解析器*/

    OI_MODULE_DI,               /**<61设备识别配置文件*/

    // bhapi组件-->对oi_debug.c的更新

    OI_MODULE_BHAPI,            /**<62 BLUEmagic主机API通用*/
    OI_MODULE_BHCLI,            /**<63 BLUEmagic主机API客户端*/
    OI_MODULE_BHSRV,            /**<64 BLUEmagic主机API服务器端*/
    OI_MODULE_MSGQ,             /**<65处理消息队列的模块*/
    OI_MODULE_BHAPI_TRANSPORT,  /**<66处理消息队列的模块*/
    OI_MODULE_BLST_SRV,         /**<67模块，提供服务器端BHAPI轻量级串行传输*/
    OI_MODULE_BLST_CLI,         /**<68模块，提供客户端BHAPI轻量级串行传输*/

    // OEM文件-->oi_debug.c更新
    OI_MODULE_OEM,              /**<69应用程序内存分配*/

    // 应用程序胶-->对oi_debug.c的更新
    OI_MODULE_APP,              /**<70应用程序内存分配*/

    /* 各种代码依赖于按特定顺序出现的最后2个元素：OI_MODULE_ALL必须是倒数第二个元素OI_MODURE_UNKNOWN必须是最后一个元素
       */
    OI_MODULE_ALL,              /**<71识别所有模块的特殊值-用于控制调试打印语句*/
    OI_MODULE_UNKNOWN           /**<72特殊值-用于调试打印语句*/
} OI_MODULE;

/**
 * 此常数是列表中实际模块的数量。ALL和UNKNOWN是实际上不是模块的特殊值。用于调试打印和memmgr分析
 */
#define OI_NUM_MODULES  OI_MODULE_ALL


/**
 * 这个常数是轮廓和核心组件的数量。它用于调整初始化和配置表的大小。
 */
#define OI_NUM_STACK_MODULES    OI_MODULE_BHAPI


#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* _OI_MODULES_H */

