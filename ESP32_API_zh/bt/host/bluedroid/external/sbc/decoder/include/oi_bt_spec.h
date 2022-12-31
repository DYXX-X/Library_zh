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
#ifndef _OI_BT_SPEC_H
#define _OI_BT_SPEC_H
/**
 * @file
 *
 * 此文件包含蓝牙规范中的常见定义。
 *
 */

/**********************************************************************************
  $版本：#1$
***********************************************************************************/

#include "oi_stddefs.h"

/**\addtogroup其他杂项API*/
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**微微网中活动从属设备的最大数量。*/
#define OI_BT_MAX_ACTIVE_SLAVES 7

/**蓝牙设备地址（BD_ADDR）中的字节数*/
#define OI_BD_ADDR_BYTE_SIZE   6

/**
 * 48位蓝牙设备地址
 *
 * 因为48位整数可能在所有平台上都不受支持，所以地址被定义为字节数组。这个数组是big endian，这意味着
 *  -阵列[0]包含位47-40，
 *  -阵列[1]包含位39-32，
 *  -阵列[2]包含位31-24，
 *  -阵列[3]包含位23-16，
 *  -阵列[4]包含位15-8，并且
 *  -数组[5]包含位7-0。
 */
typedef struct  {
    OI_UINT8    addr[OI_BD_ADDR_BYTE_SIZE] ;   /**<蓝牙设备地址表示为8位值的数组*/
} OI_BD_ADDR ;

/**
 * @name 使用UUID的数据类型UUID为16字节（128位）。
 *
 * 为了避免一直传递128位值，定义了32位和16位UUID，以及从较短版本到完整版本的映射。
 *
 * @{
 */

/**
 * 128位UUID的16位表示
 */
typedef OI_UINT16 OI_UUID16;

/**
 * 128位UUID的32位表示
 */
typedef OI_UINT32 OI_UUID32;

/**
 * 128位UUID中的字节数
 */
#define OI_BT_UUID128_SIZE  16

/**
 * IPv6样式地址中的字节数
 */
#define OI_BT_IPV6ADDR_SIZE  16

/**
 * 128位UUID的类型定义
 *
 * 为了简化128位UUID与16位和32位UUID之间的转换，最重要的32位以与目标（本地）设备上本地的相同的端号存储。128位UUID的其余部分按大端顺序存储为字节。
 */
typedef struct {
    OI_UINT32 ms32bits;                                    /**<128位UUID的最高有效32位*/
    OI_UINT8 base[OI_BT_UUID128_SIZE - sizeof(OI_UINT32)]; /**<128位UUID的余数，8位值的数组*/
} OI_UUID128;

/** @} */

/**链接密钥中的字节数*/
#define OI_BT_LINK_KEY_SIZE    16

/**
 * 基带链路密钥的类型定义
 *
 * 因为128位整数可能在所有平台上都不受支持，所以我们将链接键定义为字节数组。与蓝牙设备地址不同，链接密钥以小端顺序存储，这意味着
 *  -数组[0]包含位0-7，
 *  -阵列[1]包含位8-15，
 *  -阵列[2]包含位16-23，
 *  -阵列[3]包含位24-31，
 *  -阵列[4]包含位32-39，
 *  -阵列[5]包含位40-47，
 *  -阵列[6]包含位48-55，
 *  -阵列[7]包含位56-63，
 *  -阵列[8]包含位64-71，
 *  -阵列[9]包含位72-79，
 *  -阵列[10]包含位80-87，
 *  -阵列[11]包含位88-95，
 *  -阵列[12]包含位96-103，
 *  -阵列[13]包含位104-111，
 *  -数组[14]包含位112-119，以及
 *  -数组[15]包含位120-127。
 */
typedef struct {
    OI_UINT8    key[OI_BT_LINK_KEY_SIZE] ;   /**<链接键表示为8位值的数组*/
} OI_LINK_KEY ;


/**带外数据大小-C和R值各为16字节*/
#define OI_BT_OOB_NUM_BYTES     16

typedef struct {
    OI_UINT8    value[OI_BT_OOB_NUM_BYTES] ;   /**<用于C和R值的相同结构*/
} OI_OOB_DATA ;


/**
 * 链接键类型
 */
typedef enum  {
    OI_LINK_KEY_TYPE_COMBO              = 0,    /**<组合键*/
    OI_LINK_KEY_TYPE_LOCAL_UNIT         = 1,    /**<本地单元键*/
    OI_LINK_KEY_TYPE_REMOTE_UNIT        = 2,    /**<远程单元键*/
    OI_LINK_KEY_TYPE_DEBUG_COMBO        = 3,    /**<调试组合键*/
    OI_LINK_KEY_TYPE_UNAUTHENTICATED    = 4,    /**<未经身份验证*/
    OI_LINK_KEY_TYPE_AUTHENTICATED      = 5,    /**<已验证*/
    OI_LINK_KEY_TYPE_CHANGED_COMBO      = 6     /**<已更改*/

} OI_BT_LINK_KEY_TYPE ;


/**为PIN（个人身份号码）分配的空间量（字节）*/
#define OI_BT_PIN_CODE_SIZE    16

/**PIN的数据类型（PIN被视为字符串，因此不应用端序。）*/
typedef struct  {
    OI_UINT8    pin[OI_BT_PIN_CODE_SIZE] ; /**<PIN表示为8位值的数组*/
} OI_PIN_CODE ;

/**每个设备的最大SCO连接数，从蓝牙规范2.0+EDR版本起为3（见第2卷B部分第4.3节）*/
#define OI_BT_MAX_SCO_CONNECTIONS  3

/**时钟偏移的数据类型*/
typedef OI_UINT16   OI_BT_CLOCK_OFFSET ;

/**LM句柄的数据类型*/
typedef OI_UINT16 OI_HCI_LM_HANDLE;

/**SCO或ACL连接句柄的不透明数据类型*/
typedef struct _OI_HCI_CONNECTION *OI_HCI_CONNECTION_HANDLE;

/**HCI错误代码的数据类型，如oi_hcispec中所定义。小时*/
typedef OI_UINT8    OI_HCI_ERROR_CODE ;

/**
 * 蓝牙设备类型由24位位字段表示，在堆栈中表示为32位数字。设备类的位布局和值在文件oi_bt_assigned_nos中指定。h和蓝牙“分配的号码”规范http://www.bluetooth.org/assigned-numbers/.
 */
typedef OI_UINT32   OI_BT_DEVICE_CLASS ;

#define OI_BT_DEV_CLASS_FORMAT_MASK        0x000003    /**<位0-1包含格式类型。*/
#define OI_BT_DEV_CLASS_MINOR_DEVICE_MASK  0x0000FC    /**<位2-7包含次要设备类值。*/
#define OI_BT_DEV_CLASS_MAJOR_DEVICE_MASK  0x001F00    /**<位8-12包含主要设备类别值。*/
#define OI_BT_DEV_CLASS_MAJOR_SERVICE_MASK 0xFFE000    /**<第13-23位包含主要服务类别值。*/

/**目前只定义了一种设备类格式，类型00。*/
#define OI_BT_DEV_CLASS_FORMAT_TYPE        00

/**设备类别中的第13位表示有限的可发现性模式（GAP v2.0+EDR，第4.1.2.2节）*/
#define OI_BT_DEV_CLASS_LIMITED_DISCO_BIT  BIT13

/**宏以测试设备类格式的有效性*/
#define OI_BT_VALID_DEVICE_CLASS_FORMAT(class) (OI_BT_DEV_CLASS_FORMAT_TYPE == ((class) & OI_BT_DEV_CLASS_FORMAT_MASK))

/**基带时钟信号之间的时间，当前为625微秒（一个时隙）*/
#define OI_BT_TICK 625
/**一些宏可以转换为基带时钟信号，不使用浮点！*/
#define OI_SECONDS_TO_BT_TICKS(secs)    ((secs)*1600)
#define OI_BT_TICKS_TO_SECONDS(ticks)   ((ticks)/1600)
#define OI_MSECS_TO_BT_TICKS(msecs)     (((msecs)*8)/5)
#define OI_BT_TICKS_TO_MSECS(ticks)     (((ticks)*5)/8)

/**EIR字节顺序*/
#define OI_EIR_BYTE_ORDER   OI_LITTLE_ENDIAN_BYTE_ORDER


#ifdef __cplusplus
}
#endif

/**@}*/

/*****************************************************************************/
#endif /* _OI_BT_SPEC_H */

