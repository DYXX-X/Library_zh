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
#ifndef _OI_STATUS_H
#define _OI_STATUS_H
/**
 * @file 此文件包含BLUEmagic 3.0软件的状态代码。
 */

#include "oi_stddefs.h"

/**\addtogroup其他杂项API*/
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif


/**测试它**/

/**
 * OI_STATUS必须适合16位，因此状态代码的范围可以从0到66535（包括0和66535）。
 */

typedef enum {
    OI_STATUS_SUCCESS                      = 0,   /**<#OI_OK的函数调用成功别名*/
    OI_OK                                  = 0,   /**<#OI_STATUS_SSUCCESS的函数调用成功别名*/
    OI_STATUS_INVALID_PARAMETERS           = 101, /**<无效的函数输入参数*/
    OI_STATUS_NOT_IMPLEMENTED              = 102, /**<尝试使用未实现的函数*/
    OI_STATUS_NOT_INITIALIZED              = 103, /**<数据未初始化*/
    OI_STATUS_NO_RESOURCES                 = 104, /**<一般资源分配失败状态*/
    OI_STATUS_INTERNAL_ERROR               = 105, /**<内部不一致*/
    OI_STATUS_OUT_OF_MEMORY                = 106, /**<通常，OI_Malloc失败*/
    OI_ILLEGAL_REENTRANT_CALL              = 107, /**<违反不可重入模块策略*/
    OI_STATUS_INITIALIZATION_FAILED        = 108, /**<模块初始化失败*/
    OI_STATUS_INITIALIZATION_PENDING       = 109, /**<初始化尚未完成*/
    OI_STATUS_NO_SCO_SUPPORT               = 110, /**<SCO操作被拒绝；未为SCO配置系统*/
    OI_STATUS_OUT_OF_STATIC_MEMORY         = 111, /**<静态malloc失败*/
    OI_TIMEOUT                             = 112, /**<通用超时*/
    OI_OS_ERROR                            = 113, /**<某些操作系统错误*/
    OI_FAIL                                = 114, /**<一般故障*/
    OI_STRING_FORMAT_ERROR                 = 115, /**＜VarString格式字符串中的错误*/
    OI_STATUS_PENDING                      = 116, /**<操作正在挂起。*/
    OI_STATUS_INVALID_COMMAND              = 117, /**<命令无效。*/
    OI_BUSY_FAIL                           = 118, /**<命令因忙而被拒绝*/
    OI_STATUS_ALREADY_REGISTERED           = 119, /**<已执行注册。*/
    OI_STATUS_NOT_FOUND                    = 120, /**<未找到引用的资源。*/
    OI_STATUS_NOT_REGISTERED               = 121, /**<未注册*/
    OI_STATUS_NOT_CONNECTED                = 122, /**<未连接*/
    OI_CALLBACK_FUNCTION_REQUIRED          = 123, /**<需要回调函数参数。*/
    OI_STATUS_MBUF_OVERFLOW                = 124, /**<没有空间向mbuf添加另一个缓冲区。*/
    OI_STATUS_MBUF_UNDERFLOW               = 125, /**<试图从mbuf中提取太多字节。*/
    OI_STATUS_CONNECTION_EXISTS            = 126, /**<连接存在*/
    OI_STATUS_NOT_CONFIGURED               = 127, /**<模块未配置*/
    OI_LOWER_STACK_ERROR                   = 128, /**<下层堆栈API报告了错误。这用于嵌入式平台。*/
    OI_STATUS_RESET_IN_PROGRESS            = 129, /**<请求失败/被拒绝，因为我们正忙于重置。*/
    OI_STATUS_ACCESS_DENIED                = 130, /**<一般访问被拒绝错误。*/
    OI_STATUS_DATA_ERROR                   = 131, /**<一般数据错误。*/
    OI_STATUS_INVALID_ROLE                 = 132, /**<请求的角色无效。*/
    OI_STATUS_ALREADY_CONNECTED            = 133, /**<请求的连接已建立。*/
    OI_STATUS_PARSE_ERROR                  = 134, /**<分析错误*/
    OI_STATUS_END_OF_FILE                  = 135, /**<文件结尾*/
    OI_STATUS_READ_ERROR                   = 136, /**<一般读取错误*/
    OI_STATUS_WRITE_ERROR                  = 137, /**<一般写入错误*/
    OI_STATUS_NEGOTIATION_FAILURE          = 138, /**<协商错误*/
    OI_STATUS_READ_IN_PROGRESS             = 139, /**<读取已在进行中*/
    OI_STATUS_ALREADY_INITIALIZED          = 140, /**<初始化已完成*/
    OI_STATUS_STILL_CONNECTED              = 141, /**<服务无法关闭，因为仍有活动连接。*/
    OI_STATUS_MTU_EXCEEDED                 = 142, /**<数据包太大*/
    OI_STATUS_LINK_TERMINATED              = 143, /**<链接已终止*/
    OI_STATUS_PIN_CODE_TOO_LONG            = 144, /**<应用程序给我们的pin码太长*/
    OI_STATUS_STILL_REGISTERED             = 145, /**<服务无法关闭，因为仍有活动注册。*/
    OI_STATUS_SPEC_VIOLATION               = 146, /**<某些应用程序行为违反BT规范*/


    OI_STATUS_PSM_ALREADY_REGISTERED       = 402, /**<L2CAP：指定的PSM已注册。*/
    OI_STATUS_INVALID_CID                  = 403, /**<L2CAP:CID无效或不再有效（连接终止）*/
    OI_STATUS_CID_NOT_FOUND                = 404, /**<L2CAP:CID不表示当前连接*/
    OI_STATUS_CHANNEL_NOT_FOUND            = 406, /**<L2CAP:CID不表示当前连接*/
    OI_STATUS_PSM_NOT_FOUND                = 407, /**<L2CAP:找不到PSM*/
    OI_STATUS_INVALID_STATE                = 408, /**＜L2CAP：无效状态*/
    OI_STATUS_WRITE_IN_PROGRESS            = 410, /**＜L2CAP：正在写入*/
    OI_STATUS_INVALID_PACKET               = 411, /**＜L2CAP：无效数据包*/
    OI_STATUS_SEND_COMPLETE                = 412, /**＜L2CAP：发送完成*/
    OI_STATUS_INVALID_HANDLE               = 414, /**＜L2CAP：句柄无效*/
    OI_STATUS_GROUP_FULL                   = 418, /**<L2CAP:无法向指定组添加更多成员。*/
    OI_STATUS_DEVICE_ALREADY_IN_GROUP      = 423, /**<L2CAP:设备已存在于组中。*/
    OI_STATUS_DUPLICATE_GROUP              = 425, /**＜L2CAP：尝试添加多个组*/
    OI_STATUS_EMPTY_GROUP                  = 426, /**＜L2CAP：组为空*/
    OI_STATUS_PACKET_NOT_FOUND             = 427, /**＜L2CAP：未找到数据包*/
    OI_STATUS_BUFFER_TOO_SMALL             = 428, /**<L2CAP:缓冲区大小太小。*/
    OI_STATUS_IDENTIFIER_NOT_FOUND         = 429, /**＜L2CAP：未找到标识符*/

    OI_L2CAP_DISCONNECT_LOWER_LAYER        = 430, /**<L2CAP：较低级别强制断开连接。*/
    OI_L2CAP_DISCONNECT_REMOTE_REQUEST     = 431, /**<L2CAP:远程设备请求断开连接。*/
    OI_L2CAP_GROUP_ADD_CONNECT_FAIL        = 433, /**＜L2CAP：组添加连接失败*/
    OI_L2CAP_GROUP_REMOVE_FAILURE          = 434, /**＜L2CAP：组删除失败*/
    OI_L2CAP_DATA_WRITE_ERROR_LINK_TERM    = 435, /**＜L2CAP：数据写入错误LINK_TERM*/
    OI_L2CAP_DISCONNECT_LOCAL_REQUEST      = 436, /**<L2CAP：断开本地请求*/

    OI_L2CAP_CONNECT_TIMEOUT               = 437, /**＜L2CAP：连接超时*/
    OI_L2CAP_DISCONNECT_TIMEOUT            = 439, /**＜L2CAP：断开连接超时*/
    OI_L2CAP_PING_TIMEOUT                  = 440, /**＜L2CAP：Ping超时*/
    OI_L2CAP_GET_INFO_TIMEOUT              = 441, /**<L2CAP:获取信息超时*/
    OI_L2CAP_INVALID_ADDRESS               = 444, /**＜L2CAP：地址无效*/
    OI_L2CAP_CMD_REJECT_RCVD               = 445, /**<L2CAP:remote向我们发送了“命令拒绝”响应*/

    OI_L2CAP_CONNECT_BASE                  = 450, /**<L2CAP：连接底座*/
    OI_L2CAP_CONNECT_PENDING               = 451, /**<L2CAP:连接挂起*/
    OI_L2CAP_CONNECT_REFUSED_INVALID_PSM   = 452, /**<L2CAP:连接被拒绝无效PSM*/
    OI_L2CAP_CONNECT_REFUSED_SECURITY      = 453, /**<L2CAP:连接被拒绝安全*/
    OI_L2CAP_CONNECT_REFUSED_NO_RESOURCES  = 454, /**<L2CAP:连接被拒绝没有资源*/

    OI_L2CAP_CONFIG_BASE                   = 460, /**<L2CAP：配置库*/
    OI_L2CAP_CONFIG_FAIL_INVALID_PARAMETERS = 461, /**<L2CAP:配置失败无效参数*/
    OI_L2CAP_CONFIG_FAIL_NO_REASON         = 462, /**<L2CAP:配置失败无原因*/
    OI_L2CAP_CONFIG_FAIL_UNKNOWN_OPTIONS   = 463, /**<L2CAP:配置失败未知选项*/

    OI_L2CAP_GET_INFO_BASE                 = 470, /**<L2CAP:获取信息库*/
    OI_L2CAP_GET_INFO_NOT_SUPPORTED        = 471, /**<L2CAP:不支持获取信息*/
    OI_L2CAP_MTU_EXCEEDED                  = 472, /**＜L2CAP：超过了通道的MTU*/
    OI_L2CAP_INVALID_PSM                   = 482, /**<L2CAP：PSM无效*/
    OI_L2CAP_INVALID_MTU                   = 483, /**＜L2CAP：MTU无效*/
    OI_L2CAP_INVALID_FLUSHTO               = 484, /**＜L2CAP：刷新超时无效*/

    OI_HCI_NO_SUCH_CONNECTION               = 601, /**<HCI:调用者指定了不存在的连接句柄*/
    OI_HCI_CB_LIST_FULL                     = 603, /**<HCI:回调列表已满，无法尝试发送命令*/
    OI_HCI_EVENT_UNDERRUN                   = 605, /**<HCI:解析事件包，参数过早结束*/
    OI_HCI_UNKNOWN_EVENT_CODE               = 607, /**<HCI:接收到事件-事件代码未知*/
    OI_HCI_BAD_EVENT_PARM_LEN               = 608, /**<HCI:事件-参数长度不正确*/
    OI_HCI_CMD_QUEUE_FULL                   = 611, /**<HCI:命令队列已满*/
    OI_HCI_SHORT_EVENT                      = 612, /**<HCI：收到事件，缺少事件代码和/或参数长度*/
    OI_HCI_TRANSMIT_NOT_READY               = 613, /**<HCI:ACL/SCO传输请求失败-忙或无可用缓冲区*/
    OI_HCI_ORPHAN_SENT_EVENT                = 614, /**<HCI:从传输层获得虚假的“已发送”事件*/
    OI_HCI_CMD_TABLE_ERROR                  = 615, /**<HCI:内部命令表不一致*/
    OI_HCI_UNKNOWN_CMD_ID                   = 616, /**<HCI:HciApi命令-未知命令id*/
    OI_HCI_UNEXPECTED_EVENT                 = 619, /**<HCI:接收到的事件，仅在响应命令时发生*/
    OI_HCI_EVENT_TABLE_ERROR                = 620, /**<HCI:内部事件表中的不一致*/
    OI_HCI_EXPECTED_EVENT_TIMOUT            = 621, /**<HCI:等待预期事件超时*/
    OI_HCI_NO_CMD_DESC_FOR_OPCODE           = 622, /**<HCI:事件操作码未知*/
    OI_HCI_INVALID_OPCODE_ERROR             = 623, /**<HCI:命令操作码无效*/
    OI_HCI_FLOW_CONTROL_DISABLED            = 624, /**<HCI:如果在配置中禁用，则无法使用主机流控制API*/
    OI_HCI_TX_COMPLETE                      = 625, /**<HCI:完成向主机控制器的数据包传送*/
    OI_HCI_TX_ERROR                         = 626, /**<HCI:无法将数据包传递到主机控制器*/
    OI_HCI_DEVICE_NOT_INITIALIZED           = 627, /**<HCI:在设备启动并运行之前，不允许来自上层的命令*/
    OI_HCI_UNSUPPORTED_COMMAND              = 628, /**<HCI:本地设备不支持请求的命令*/
    OI_HCI_PASSTHROUGH_ERROR                = 629, /**<HCI:处理passthrough命令时出错*/
    OI_HCI_PASSTHROUGH_ALREADY_SET          = 630, /**<HCI:已启用直通模式*/
    OI_HCI_RESET_FAILURE                    = 631, /**<HCI:重置设备/基带失败*/
    OI_HCI_TRANSPORT_RESET                  = 632, /**<HCI:由于传输中的重置，某些操作失败*/
    OI_HCIERR_HCIIFC_INIT_FAILURE           = 633, /**<HCI:未能初始化传输层接口*/

    OI_HCIERR_FIRST_ERROR_VALUE                = 701, /**<第一个HCI协议错误的标记*/
    OI_HCIERR_UNKNOWN_HCI_COMMAND              = 701, /**<HCI:协议错误0x01*/
    OI_HCIERR_NO_CONNECTION                    = 702, /**<HCI:协议错误0x02*/
    OI_HCIERR_HARDWARE_FAILURE                 = 703, /**<HCI:协议错误0x03*/
    OI_HCIERR_PAGE_TIMEOUT                     = 704, /**<HCI:协议错误0x04*/
    OI_HCIERR_AUTHENTICATION_FAILURE           = 705, /**<HCI:协议错误0x05*/
    OI_HCIERR_KEY_MISSING                      = 706, /**<HCI:协议错误0x06*/
    OI_HCIERR_MEMORY_FULL                      = 707, /**<HCI:协议错误0x07*/
    OI_HCIERR_CONNECTION_TIMEOUT               = 708, /**<HCI:协议错误0x08*/
    OI_HCIERR_MAX_NUM_OF_CONNECTIONS           = 709, /**<HCI:协议错误0x09*/
    OI_HCIERR_MAX_NUM_OF_SCO_CONNECTIONS       = 710, /**<HCI:协议错误0x0A*/
    OI_HCIERR_ACL_CONNECTION_ALREADY_EXISTS    = 711, /**<HCI:协议错误0x0B*/
    OI_HCIERR_COMMAND_DISALLOWED               = 712, /**<HCI:协议错误0x0C*/
    OI_HCIERR_HOST_REJECTED_RESOURCES          = 713, /**<HCI:协议错误0x0D*/
    OI_HCIERR_HOST_REJECTED_SECURITY           = 714, /**<HCI:协议错误0x0E*/
    OI_HCIERR_HOST_REJECTED_PERSONAL_DEVICE    = 715, /**<HCI:协议错误0x0F*/
    OI_HCIERR_HOST_TIMEOUT                     = 716, /**<HCI:协议错误0x10*/
    OI_HCIERR_UNSUPPORTED                      = 717, /**<HCI:协议错误0x11*/
    OI_HCIERR_INVALID_PARAMETERS               = 718, /**<HCI:协议错误0x12*/
    OI_HCIERR_OTHER_END_USER_DISCONNECT        = 719, /**<HCI:协议错误0x13*/
    OI_HCIERR_OTHER_END_LOW_RESOURCES          = 720, /**<HCI:协议错误0x14*/
    OI_HCIERR_OTHER_END_POWERING_OFF           = 721, /**<HCI:协议错误0x15*/
    OI_HCIERR_CONNECTION_TERMINATED_LOCALLY    = 722, /**<HCI:协议错误0x16*/
    OI_HCIERR_REPEATED_ATTEMPTS                = 723, /**<HCI:协议错误0x17*/
    OI_HCIERR_PAIRING_NOT_ALLOWED              = 724, /**<HCI:协议错误0x18*/
    OI_HCIERR_UNKNOWN_LMP_PDU                  = 725, /**<HCI:协议错误0x19*/
    OI_HCIERR_UNSUPPORTED_REMOTE_FEATURE       = 726, /**<HCI:协议错误0x1A*/
    OI_HCIERR_SCO_OFFSET_REJECTED              = 727, /**<HCI:协议错误0x1B*/
    OI_HCIERR_SCO_INTERVAL_REJECTED            = 728, /**<HCI:协议错误0x1C*/
    OI_HCIERR_SCO_AIR_MODE_REJECTED            = 729, /**<HCI:协议错误0x1D*/
    OI_HCIERR_INVALID_LMP_PARMS                = 730, /**<HCI:协议错误0x1E*/
    OI_HCIERR_UNSPECIFIED_ERROR                = 731, /**<HCI:协议错误0x1F*/
    OI_HCIERR_UNSUPPORTED_LMP_PARAMETERS       = 732, /**<HCI:协议错误0x20*/
    OI_HCIERR_ROLE_CHANGE_NOT_ALLOWED          = 733, /**<HCI:协议错误0x21*/
    OI_HCIERR_LMP_RESPONSE_TIMEOUT             = 734, /**<HCI:协议错误0x22*/
    OI_HCIERR_LMP_ERROR_TRANS_COLLISION        = 735, /**<HCI:协议错误0x23*/
    OI_HCIERR_LMP_PDU_NOT_ALLOWED              = 736, /**<HCI:协议错误0x24*/
    OI_HCIERR_ENCRYPTION_MODE_NOT_ACCEPTABLE   = 737, /**<HCI:协议错误0x25*/
    OI_HCIERR_UNIT_KEY_USED                    = 738, /**<HCI:协议错误0x26*/
    OI_HCIERR_QOS_NOT_SUPPORTED                = 739, /**<HCI:协议错误0x27*/
    OI_HCIERR_INSTANT_PASSED                   = 740, /**<HCI:协议错误0x28*/
    OI_HCIERR_UNIT_KEY_PAIRING_UNSUPPORTED     = 741, /**<HCI:协议错误0x29*/
    OI_HCIERR_DIFFERENT_TRANS_COLLISION        = 742, /**<HCI:协议错误0x2A*/
    OI_HCIERR_RESERVED_2B                      = 743, /**<HCI:协议错误0x2B*/
    OI_HCIERR_QOS_UNACCEPTABLE_PARAMETER       = 744, /**<HCI:协议错误0x2C*/
    OI_HCIERR_QOS_REJECTED                     = 745, /**<HCI:协议错误0x2D*/
    OI_HCIERR_CHANNEL_CLASSIFICATION_NS        = 746, /**<HCI:协议错误0x2E*/
    OI_HCIERR_INSUFFICIENT_SECURITY            = 747, /**<HCI:协议错误0x2F*/
    OI_HCIERR_PARM_OUT_OF_MANDATORY_RANGE      = 748, /**<HCI:协议错误0x30*/
    OI_HCIERR_RESERVED_31                      = 749, /**<HCI:协议错误0x31*/
    OI_HCIERR_ROLE_SWITCH_PENDING              = 750, /**<HCI:协议错误0x32*/
    OI_HCIERR_RESERVED_33                      = 751, /**<HCI:协议错误0x33*/
    OI_HCIERR_RESERVED_SLOT_VIOLATION          = 752, /**<HCI:协议错误0x34*/
    OI_HCIERR_ROLE_SWITCH_FAILED               = 753, /**<HCI:协议错误0x35*/
    OI_HCIERR_EIR_TOO_LARGE                    = 754, /**<HCI:协议错误0x36*/
    OI_HCIERR_SSP_NOT_SUPPORTED_BY_HOST        = 755, /**<HCI:协议错误0x37*/
    OI_HCIERR_HOST_BUSY_PAIRING                = 756, /**<HCI:协议错误0x38*/

    OI_HCIERR_UNKNOWN_ERROR                    = 757, /**<HCI:未知错误代码*/
    OI_HCIERR_LAST_ERROR_VALUE                 = 757, /**<上次HCI协议错误的标记*/

    OI_SDP_SPEC_ERROR                    = 800, /**<SDP:将OI_status代码映射到SDP错误的基本错误状态*/
    OI_SDP_INVALID_SERVICE_RECORD_HANDLE = (OI_SDP_SPEC_ERROR + 2), /**<SDP:协议错误服务记录句柄无效*/
    OI_SDP_INVALID_REQUEST_SYNTAX        = (OI_SDP_SPEC_ERROR + 3), /**<SDP:协议错误无效请求语法*/
    OI_SDP_INVALID_PDU_SIZE              = (OI_SDP_SPEC_ERROR + 4), /**<SDP:协议错误PDU大小无效*/
    OI_SDP_INVALID_CONTINUATION_STATE    = (OI_SDP_SPEC_ERROR + 5), /**<SDP:协议错误无效的继续状态*/
    OI_SDP_INSUFFICIENT_RESOURCES        = (OI_SDP_SPEC_ERROR + 6), /**<SDP:协议错误资源不足*/
    OI_SDP_ERROR                         = 807, /**<SDP:服务器返回错误代码*/
    OI_SDP_CORRUPT_DATA_ELEMENT          = 808, /**<SDP:无效或损坏的数据元素表示*/
    OI_SDP_SERVER_NOT_CONNECTED          = 810, /**<SDP:尝试从未连接的服务器断开连接*/
    OI_SDP_ACCESS_DENIED                 = 811, /**<SDP:服务器拒绝访问服务器*/
    OI_SDP_ATTRIBUTES_OUT_OF_ORDER       = 812, /**<SDP:属性列表中的属性不是升序*/
    OI_SDP_DEVICE_DOES_NOT_SUPPORT_SDP   = 813, /**<SDP:尝试连接到不支持SDP的设备*/
    OI_SDP_NO_MORE_DATA                  = 815, /**<SDP:服务器没有更多的延续数据*/
    OI_SDP_REQUEST_PARAMS_TOO_LONG       = 816, /**<SDP:请求的参数超过L2CAP缓冲区大小*/
    OI_SDP_REQUEST_PENDING               = 817, /**<SDP:在处理另一个请求时无法发出请求*/
    OI_SDP_SERVER_CONNECT_FAILED         = 819, /**<SDP:尝试连接到SDP服务器失败*/
    OI_SDP_SERVER_TOO_MANY_CONNECTIONS   = 821, /**<SDP:超过了同时服务器连接的最大数量*/
    OI_SDP_NO_MATCHING_SERVICE_RECORD    = 823, /**<SDP:没有与UUID列表匹配的服务记录*/
    OI_SDP_PARTIAL_RESPONSE              = 824, /**<SDP:仅供内部使用*/
    OI_SDP_ILLEGAL_ARGUMENT              = 825, /**<SDP:传递给SDP函数的非法参数*/
    OI_SDP_ATTRIBUTE_NOT_FOUND           = 826, /**<SDP:在服务记录中找不到请求的属性*/
    OI_SDP_DATABASE_OUT_OF_RESOURCES     = 827, /**<SDP:服务器数据库内存不足*/
    OI_SDP_SHORT_PDU                     = 829, /**<SDP:数据包中的字节不足*/
    OI_SDP_TRANSACTION_ID_MISMATCH       = 830, /**<SDP:事务Id不符合预期*/
    OI_SDP_UNEXPECTED_RESPONSE_PDU_ID    = 831, /**<SDP:不需要此响应PDU*/
    OI_SDP_REQUEST_TIMEOUT               = 832, /**<SDP:在超时时间内未得到响应*/
    OI_SDP_INVALID_RESPONSE_SYNTAX       = 833, /**<SDP:响应格式不正确*/
    OI_SDP_CONNECTION_TIMEOUT            = 834, /**<SDP:连接尝试在较低层超时*/
    OI_SDP_RESPONSE_DATA_ERROR           = 835, /**<SDP:对服务请求的响应似乎已损坏*/
    OI_SDP_TOO_MANY_ATTRIBUTE_BYTES      = 836, /**<SDP:响应包含的字节数超过请求的字节数。*/
    OI_SDP_TOO_MANY_SERVICE_RECORDS      = 837, /**<SDP:响应包含的服务记录比请求的多。*/
    OI_SDP_INVALID_CONNECTION_ID         = 838, /**<SDP:SDP请求中的连接ID无效*/
    OI_SDP_CANNOT_SET_ATTRIBUTE          = 839, /**<SDP:尝试设置动态属性值失败*/
    OI_SDP_BADLY_FORMED_ATTRIBUTE_VALUE  = 840, /**<SDP:属性值的类型或结构错误*/
    OI_SDP_NO_ATTRIBUTE_LIST_TO_REMOVE   = 841, /**<SDP:尝试从服务记录中删除不存在的属性列表*/
    OI_SDP_ATTRIBUTE_LIST_ALREADY_ADDED  = 842, /**<SDP:属性列表已添加到服务记录*/
    OI_SDP_DATA_ELEMENT_TRUNCATED        = 843, /**<SDP:数据元素被截断（字节太少）*/

    OI_RFCOMM_WRITE_IN_PROGRESS          = 901, /**<RFCOMM:正在写入*/
    OI_RFCOMM_INVALID_BAUDRATE           = 903, /**<RFCOMM:无效波特率*/
    OI_RFCOMM_INVALID_DATABIT            = 904, /**<RFCOMM:无效数据位*/
    OI_RFCOMM_INVALID_STOPBIT            = 905, /**<RFCOMM:停止位无效*/
    OI_RFCOMM_INVALID_PARITY             = 906, /**<RFCOMM:无效的奇偶校验*/
    OI_RFCOMM_INVALID_PARITYTYPE         = 907, /**<RFCOMM:无效的paritytype*/
    OI_RFCOMM_INVALID_FLOWCONTROL        = 908, /**<RFCOMM:流控制无效*/
    OI_RFCOMM_SESSION_EXISTS             = 909, /**<RFCOMM:会话存在*/
    OI_RFCOMM_INVALID_CHANNEL            = 910, /**<RFCOMM:通道无效*/
    OI_RFCOMM_DLCI_EXISTS                = 911, /**<RFCOMM:DLCI存在*/
    OI_RFCOMM_LINK_NOT_FOUND             = 912, /**<RFCOMM:未找到链接*/
    OI_RFCOMM_REMOTE_REJECT              = 913, /**<RFCOMM:远程拒绝*/
    OI_RFCOMM_TEST_IN_PROGRESS           = 915, /**<RFCOMM:测试正在进行*/
    OI_RFCOMM_SESSION_NOT_FOUND          = 916, /**<RFCOMM:找不到会话*/
    OI_RFCOMM_INVALID_PACKET             = 917, /**<RFCOMM:数据包无效*/
    OI_RFCOMM_FRAMESIZE_EXCEEDED         = 918, /**<RFCOMM:超过帧大小*/
    OI_RFCOMM_INVALID_DLCI               = 920, /**<RFCOMM:无效的dlci*/
    OI_RFCOMM_SERVER_NOT_REGISTERED      = 921, /**<RFCOMM:服务器未注册*/
    OI_RFCOMM_CREDIT_ERROR               = 922, /**<RFCOMM:信用错误*/
    OI_RFCOMM_NO_CHANNEL_NUMBER          = 923, /**<RFCOMM:无信道号*/
    OI_RFCOMM_QUERY_IN_PROGRESS          = 924, /**<RFCOMM:正在进行查询*/
    OI_RFCOMM_SESSION_SHUTDOWN           = 925, /**<RFCOMM:会话关闭*/
    OI_RFCOMM_LOCAL_DEVICE_DISCONNECTED  = 926, /**<RFCOMM:本地设备已断开连接*/
    OI_RFCOMM_REMOTE_DEVICE_DISCONNECTED = 927, /**<RFCOMM:远程设备已断开连接*/
    OI_RFCOMM_OUT_OF_SERVER_CHANNELS     = 928, /**<RFCOMM:服务器通道外*/

    OI_DISPATCH_INVALID_CB_HANDLE        = 1001, /**<Dispatcher收到了无效的回调句柄*/
    OI_DISPATCH_TABLE_OVERFLOW           = 1002, /**<Dispatcher表已满*/

    OI_TEST_UNKNOWN_TEST                 = 1101, /**<TEST:未知测试*/
    OI_TEST_FAIL                         = 1102, /**<测试：失败*/

    OI_HCITRANS_CANNOT_CONNECT_TO_DEVICE   = 1201, /**<TRANSPORT:无法连接到设备*/
    OI_HCITRANS_BUFFER_TOO_SMALL           = 1203, /**<TRANSPORT:缓冲区太小*/
    OI_HCITRANS_NULL_DEVICE_HANDLE         = 1204, /**<TRANSPORT:空设备句柄*/
    OI_HCITRANS_IO_ERROR                   = 1205, /**<TRANSPORT:IO错误*/
    OI_HCITRANS_DEVICE_NOT_READY           = 1206, /**<TRANSPORT:设备未就绪*/
    OI_HCITRANS_FUNCTION_NOT_SUPPORTED     = 1207, /**<TRANSPORT:功能不支持D*/
    OI_HCITRANS_ACCESS_DENIED              = 1209, /**<运输：win32*/
    OI_HCITRANS_ACL_DATA_ERROR             = 1210, /**<TRANSPORT:ACL数据错误*/
    OI_HCITRANS_SCO_DATA_ERROR             = 1211, /**<TRANSPORT:SCO数据错误*/
    OI_HCITRANS_EVENT_DATA_ERROR           = 1212, /**<TRANSPORT:HCI事件数据错误*/
    OI_HCITRANS_INTERNAL_ERROR             = 1214, /**<TRANSPORT:传输中的内部错误*/
    OI_HCITRANS_LINK_NOT_ACTIVE            = 1215, /**<TRANSPORT:设备链接当前未激活*/
    OI_HCITRANS_INITIALIZING               = 1216, /**<TRANSPORT:传输正在初始化*/

    OI_DEVMGR_NO_CONNECTION                = 1301, /**<DEVMGR:无连接*/
    OI_DEVMGR_HARDWARE_ERROR               = 1305, /**<DEVMGR:HCI报告的错误*/
    OI_DEVMGR_PENDING_CONNECT_LIST_FULL    = 1307, /**<DEVMGR:挂起连接列表已满*/
    OI_DEVMGR_CONNECTION_LIST_FULL         = 1309, /**<DEVMGR:连接列表已满*/
    OI_DEVMGR_NO_SUCH_CONNECTION           = 1310, /**<DEVMGR:无此类连接*/
    OI_DEVMGR_INQUIRY_IN_PROGRESS          = 1311, /**<DEVMGR:查询中*/
    OI_DEVMGR_PERIODIC_INQUIRY_ACTIVE      = 1312, /**<DEVMGR:定期查询激活*/
    OI_DEVMGR_NO_INQUIRIES_ACTIVE          = 1313, /**<DEVMGR：如果未激活，则无法取消/退出*/
    OI_DEVMGR_DUPLICATE_CONNECTION         = 1314, /**<DEVMGR：内部错误*/
    OI_DEVMGR_DUPLICATE_EVENT_CALLBACK     = 1316, /**<DEVMGR:尝试注册同一回调两次*/
    OI_DEVMGR_EVENT_CALLBACK_LIST_FULL     = 1317, /**<DEVMGR:无法注册事件回调，列表已满*/
    OI_DEVMGR_EVENT_CALLBACK_NOT_FOUND     = 1318, /**<DEVMGR:尝试注销回调失败*/
    OI_DEVMGR_BUSY                         = 1319, /**<DEVMGR:某些操作一次只能执行一个*/
    OI_DEVMGR_ENUM_UNEXPECTED_INQ_COMPLETE = 1320, /**<DEVMGR:查询完成事件处于不适当的枚举状态*/
    OI_DEVMGR_ENUM_UNEXPECTED_INQ_RESULT   = 1321, /**<DEVMGR:查询结果事件处于不适当的枚举状态*/
    OI_DEVMGR_ENUM_DATABASE_FULL           = 1322, /**<DEVMGR:设备枚举，数据库已满，无法添加新设备*/
    OI_DEVMGR_ENUM_INQUIRIES_OVERLAP       = 1323, /**<DEVMGR:设备枚举，定期查询发生得太近*/
    OI_DEVMGR_UNKNOWN_LINK_TYPE            = 1324, /**<DEVMGR:HCI连接请求具有未知链接类型*/
    OI_DEVMGR_PARAM_IO_ACTIVE              = 1325, /**<DEVMGR:在参数读/写活动时请求参数读/写入*/
    OI_DEVMGR_UNKNOWN_IAC_LAP              = 1326, /**<DEVMGR:无法识别IAC LAP*/
    OI_DEVMGR_SCO_ALREADY_REGISTERED       = 1327, /**<DEVMGR:只有一个应用程序可以使用SCO*/
    OI_DEVMGR_SCO_NOT_REGISTERED           = 1328, /**<DEVMGR:SCO应用程序在使用API之前必须注册*/
    OI_DEVMGR_SCO_WITHOUT_ACL              = 1329, /**<DEVMGR:已获得SCO连接，但没有基础ACL连接*/
    OI_DEVMGR_NO_SUPPORT                   = 1330, /**<DEVMGR:设备不支持请求*/
    OI_DEVMGR_WRITE_POLICY_FAILED          = 1331, /**<DEVMGR:连接尝试失败-无法写入链接策略*/
    OI_DEVMGR_NOT_IN_MASTER_MODE           = 1332, /**<DEVMGR:OI_DEVMGR-EndMasterMode，没有先前的OI_DEVMGR_BeginMasterMode*/
    OI_DEVMGR_POLICY_VIOLATION             = 1333, /**<DEVMGR:低功率请求被拒绝-链接策略不允许*/
    OI_DEVMGR_BUSY_TIMEOUT                 = 1334, /**<DEVMGR:队列中的排队操作超时；\n可通过@ref OI_CONFIG_DEVMGR:：connectQueueTimeoutSecs“connectQueueTimeoutSecs”配置超时*/
    OI_DEVMGR_REENCRYPT_FAILED             = 1335, /**<DEVMGR:角色切换后无法重新加密链接*/
    OI_DEVMGR_ROLE_POLICY_CONFLICT         = 1336, /**<DEVMGR:请求的角色与当前策略冲突*/
    OI_DEVMGR_BAD_INTERVAL                 = 1337, /**<DEVMGR：当前链接TO超出请求的最小/最大间隔范围*/
    OI_DEVMGR_INVALID_SCO_HANDLE           = 1338, /**<DEVMGR:HCI SCO事件，无效句柄*/
    OI_DEVMGR_CONNECTION_OVERLAP           = 1339, /**<DEVMGR:由于与远程端的竞争条件，连接失败*/
    OI_DEVMGR_ORPHAN_SUBRATE_COMPLETE      = 1340, /**<DEVMGR:嗅探子速率完成，但没有回调*/
    OI_DEVMGR_EIR_RESPONSE_2_LARGE         = 1341, /**<DEVMGR:eir生成器，响应长度将超过规范最大值*/

    OI_SECMGR_NO_POLICY                    = 1401, /**<SECMGR:尚未建立安全策略*/
    OI_SECMGR_INTERNAL_ERROR               = 1402, /**<SECMGR：内部不一致*/
    OI_SECMGR_ORPHANED_CALLBACK            = 1403, /**<SECMGR:我们被召回，但CB上下文已消失*/
    OI_SECMGR_BUSY                         = 1404, /**<SECMGR:配置和访问请求不能并发*/
    OI_SECMGR_DEVICE_NOT_TRUSTED           = 1405, /**<SECMGR:l2cap访问被拒绝-设备不受信任*/
    OI_SECMGR_DEVICE_ENCRYPT_FAIL          = 1407, /**<SECMGR:l2cap访问被拒绝-无法启动加密*/
    OI_SECMGR_DISCONNECTED_FAIL            = 1408, /**<SECMGR:l2cap访问被拒绝-已断开连接*/
    OI_SECMGR_ACCESS_PENDING               = 1409, /**<SECMGR:l2cap访问请求仍处于挂起状态*/
    OI_SECMGR_PIN_CODE_TOO_SHORT           = 1410, /**<SECMGR:更高层的过程给了我们一个太短的pin代码*/
    OI_SECMGR_UNKNOWN_ENCRYPT_VALUE        = 1411, /**<SECMGR:获取EncryptionChange事件，未知加密启用值*/
    OI_SECMGR_INVALID_POLICY               = 1412, /**<SECMGR:指定的安全策略对于安全模式无效*/
    OI_SECMGR_AUTHORIZATION_FAILED         = 1413, /**<SECMGR:设备授权失败*/
    OI_SECMGR_ENCRYPTION_FAILED            = 1414, /**<SECMGR:设备加密失败*/
    OI_SECMGR_UNIT_KEY_UNSUPPORTED         = 1415, /**<SECMGR:由于不支持单元密钥，身份验证失败*/
    OI_SECMGR_NOT_REGISTERED               = 1416, /**<SECMGR:尚未进行所需注册*/
    OI_SECMGR_ILLEGAL_WRITE_SSP_MODE       = 1417, /**<SECMGR:2.1 HCI规范不允许禁用SSP模式*/
    OI_SECMGR_INVALID_SEC_LEVEL            = 1418, /**<SECMGR:服务的安全级别不是有效值*/
    OI_SECMGR_INSUFFICIENT_LINK_KEY        = 1419, /**<SECMGR:链接密钥类型不足以满足服务要求*/
    OI_SECMGR_INVALID_KEY_TYPE             = 1420, /**<SECMGR:链接密钥类型不是有效值*/
    OI_SECMGR_SSP_NOT_ENCRYPTED            = 1421, /**<SECMGR:ssp要求对传入链路进行加密*/
    OI_SECMGR_ORPHAN_EVENT                 = 1422, /**<SECMGR:一些与当前流程无关的HCI安全事件*/
    OI_SECMGR_NOT_BONDABLE                 = 1423, /**<SECMGR：不处于可绑定模式*/

    OI_TCS_INVALID_ELEMENT_TYPE            = 1602, /**<TCS:元素类型无效*/
    OI_TCS_INVALID_PACKET                  = 1603, /**<TCS：数据包无效*/
    OI_TCS_CALL_IN_PROGRESS                = 1604, /**<TCS：呼叫正在进行*/
    OI_TCS_NO_CALL_IN_PROGRESS             = 1605, /**<TCS：无呼叫进行中*/

    OI_OBEX_CONTINUE                       = 1701, /**<OBEX：继续处理OBEX请求*/
    OI_OBEX_COMMAND_ERROR                  = 1702, /**<OBEX：无法识别的OBEX命令操作码*/
    OI_OBEX_CONNECTION_TIMEOUT             = 1703, /**<OBEX：等待请求响应超时*/
    OI_OBEX_CONNECT_FAILED                 = 1704, /**<OBEX:OBEX连接请求未成功*/
    OI_OBEX_DISCONNECT_FAILED              = 1705, /**<OBEX：断开连接失败，可能是因为连接不存在*/
    OI_OBEX_ERROR                          = 1706, /**<OBEX：未指定的OBEX错误*/
    OI_OBEX_INCOMPLETE_PACKET              = 1707, /**<OBEX：数据包太短或损坏*/
    OI_OBEX_LENGTH_REQUIRED                = 1708, /**<OBEX：OBEX命令中需要长度标头*/
    OI_OBEX_NOT_CONNECTED                  = 1709, /**<OBEX：未连接到OBEX服务器*/
    OI_OBEX_NO_MORE_CONNECTIONS            = 1710, /**<OBEX：已达到最大连接限制*/
    OI_OBEX_OPERATION_IN_PROGRESS          = 1711, /**<OBEX：另一个操作仍在连接上进行*/
    OI_OBEX_PUT_RESPONSE_ERROR             = 1712, /**<OBEX：PUT命令响应中的错误*/
    OI_OBEX_GET_RESPONSE_ERROR             = 1713, /**<OBEX：GET命令响应中的错误*/
    OI_OBEX_REQUIRED_HEADER_NOT_FOUND      = 1714, /**<OBEX:数据包缺少必需的标头*/
    OI_OBEX_SERVICE_UNAVAILABLE            = 1715, /**<OBEX：取消运行OBEX目标或所需服务*/
    OI_OBEX_TOO_MANY_HEADER_BYTES          = 1716, /**<OBEX：标头将不适合单个OBEX数据包*/
    OI_OBEX_UNKNOWN_COMMAND                = 1717, /**<OBEX：无法识别的OBEX命令*/
    OI_OBEX_UNSUPPORTED_VERSION            = 1718, /**<OBEX：版本不匹配*/
    OI_OBEX_CLIENT_ABORTED_COMMAND         = 1719, /**<OBEX：服务器收到中止命令*/
    OI_OBEX_BAD_PACKET                     = 1720, /**<OBEX：任何格式错误的OBEX数据包*/
    OI_OBEX_BAD_REQUEST                    = 1721, /**<OBEX：映射到同名的OBEX响应*/
    OI_OBEX_OBJECT_OVERFLOW                = 1723, /**<OBEX：接收的字节太多。*/
    OI_OBEX_NOT_FOUND                      = 1724, /**<OBEX：映射到同名的OBEX响应*/
    OI_OBEX_ACCESS_DENIED                  = 1735, /**<OBEX:无法读取或写入对象。*/
    OI_OBEX_VALUE_NOT_ACCEPTABLE           = 1736, /**<OBEX：命令中的值不在可接受范围内。*/
    OI_OBEX_PACKET_OVERFLOW                = 1737, /**<OBEX：缓冲区将无法容纳单个OBEX数据包。*/
    OI_OBEX_NO_SUCH_FOLDER                 = 1738, /**<OBEX：setpath操作返回的错误。*/
    OI_OBEX_NAME_REQUIRED                  = 1739, /**<OBEX：名称必须为非null和非空。*/
    OI_OBEX_PASSWORD_TOO_LONG              = 1740, /**<OBEX：密码超过了实施强加的长度限制。*/
    OI_OBEX_PRECONDITION_FAILED            = 1741, /**<OBEX：响应前提条件失败*/
    OI_OBEX_UNAUTHORIZED                   = 1742, /**<OBEX:身份验证未成功。*/
    OI_OBEX_NOT_IMPLEMENTED                = 1743, /**<OBEX：未实现的功能。*/
    OI_OBEX_INVALID_AUTH_DIGEST            = 1744, /**<OBEX：身份验证摘要错误。*/
    OI_OBEX_INVALID_OPERATION              = 1745, /**<OBEX：此时不允许操作。*/
    OI_OBEX_DATABASE_FULL                  = 1746, /**<OBEX：同步数据库已满。*/
    OI_OBEX_DATABASE_LOCKED                = 1747, /**<OBEX：同步数据库已锁定。*/
    OI_OBEX_INTERNAL_SERVER_ERROR          = 1748, /**<OBEX：响应内部服务器错误*/
    OI_OBEX_UNSUPPORTED_MEDIA_TYPE         = 1749, /**<OBEX：响应不支持的媒体类型*/
    OI_OBEX_PARTIAL_CONTENT                = 1750, /**<OBEX：响应部分内容*/
    OI_OBEX_METHOD_NOT_ALLOWED             = 1751, /**<OBEX：不允许响应方法*/
    OI_OBEXSRV_INCOMPLETE_GET              = 1752, /**<OBEX：向GET处理程序指示请求阶段仍在进行中*/
    OI_OBEX_FOLDER_BROWSING_NOT_ALLOWED    = 1753, /**<OBEX：表示FTP服务器不允许文件夹浏览*/
    OI_OBEX_SERVER_FORCED_DISCONNECT       = 1754, /**<OBEX：连接被服务器强制终止*/
    OI_OBEX_OFS_ERROR                      = 1755, /**<OBEX:发生OPP对象文件系统错误*/
    OI_OBEX_FILEOP_ERROR                   = 1756, /**<OBEX:发生FTP/PBAP文件操作系统错误*/
    OI_OBEX_USERID_TOO_LONG                = 1757, /**<OBEX：用户Id超过规范限制的长度限制。*/

    OI_HANDSFREE_EVENT_REPORTING_DISABLED  = 1801, /**<HANDSFREE:事件报告已禁用*/
    OI_HANDSFREE_NOT_CONNECTED             = 1802, /**<免提：未连接*/
    OI_HANDSFREE_SERVICE_NOT_STARTED       = 1803, /**<免提：如果未启动免提服务，则无法连接到免提AG*/
    OI_HANDSFREE_AG_SERVICE_NOT_STARTED    = 1804, /**<免提：如果免提AG服务未启动，则无法连接到免提设备*/
    OI_HANDSFREE_COMMAND_IN_PROGRESS       = 1805, /**<HANDSFREE:此时无法接受命令*/
    OI_HANDSFREE_AUDIO_ALREADY_CONNECTED   = 1806, /**<免提：音频已连接*/
    OI_HANDSFREE_AUDIO_NOT_CONNECTED       = 1807, /**<免提：音频未连接*/
    OI_HANDSFREE_FEATURE_NOT_SUPPORTED     = 1808, /**<HANDSFREE:请求的命令不支持本地或远程功能*/

    OI_HEADSET_SERVICE_NOT_STARTED         = 1901, /**<HEADSET:如果耳机服务未启动，则无法连接到耳机AG*/
    OI_HEADSET_AG_SERVICE_NOT_STARTED      = 1902, /**<HEADSET:如果未启动耳机AG服务，则无法连接到耳机设备*/
    OI_HEADSET_COMMAND_IN_PROGRESS         = 1903, /**<HEADSET:此时无法接受命令*/

    OI_BNEP_INVALID_MTU                             = 2001, /**<BNEP：远程设备无法支持最小BNEP MTU*/
    OI_BNEP_SETUP_TIMEOUT                           = 2002, /**<BNEP:安装请求超时。*/
    OI_BNEP_SERVICE_NOT_REGISTERED                  = 2003, /**<BNEP:未找到请求的服务。*/
    OI_BNEP_INVALID_HANDLE                          = 2004, /**<BNEP:指定的连接句柄无效。*/
    OI_BNEP_RESPONSE_TIMEOUT                        = 2005, /**<BNEP：接收响应的计时器已过期。*/
    OI_BNEP_INVALID_CONNECTION                      = 2006, /**<BNEP：连接无效*/
    OI_BNEP_INVALID_FILTER                          = 2007, /**<BNEP:提供的筛选器无效。*/
    OI_BNEP_CONNECTION_EXISTS                       = 2008, /**<BNEP:试图创建重复连接。*/
    OI_BNEP_NOT_INITIALIZED                         = 2009, /**<BNEP:尚未调用Init*/
    OI_BNEP_CONNECT_BASE                            = 2010, /**<BNEP：连接响应代码*/
    OI_BNEP_CONNECT_FAILED_INVALID_DEST_UUID        = 2011, /**<BNEP:连接响应代码无效目标UUID*/
    OI_BNEP_CONNECT_FAILED_INVALID_SOURCE_UUID      = 2012, /**<BNEP:连接响应代码无效源UUID*/
    OI_BNEP_CONNECT_FAILED_INVALID_UUID_SIZE        = 2013, /**<BNEP:连接响应代码UUID大小无效*/
    OI_BNEP_CONNECT_FAILED_NOT_ALLOWED              = 2014, /**<BNEP：不允许连接响应代码*/
    OI_BNEP_FILTER_NET_BASE                         = 2020, /**<BNEP：过滤器响应代码*/
    OI_BNEP_FILTER_NET_UNSUPPORTED_REQUEST          = 2021, /**<BNEP:筛选器响应代码不支持的请求*/
    OI_BNEP_FILTER_NET_FAILED_INVALID_PROTOCOL_TYPE = 2022, /**＜BNEP：过滤器响应代码无效协议类型*/
    OI_BNEP_FILTER_NET_FAILED_MAX_LIMIT_REACHED     = 2023, /**<BNEP：达到过滤器响应代码最大限制*/
    OI_BNEP_FILTER_NET_FAILED_SECURITY              = 2024, /**<BNEP：过滤器响应代码安全*/
    OI_BNEP_FILTER_MULTI_BASE                       = 2030, /**<BNEP：多播响应代码*/
    OI_BNEP_FILTER_MULTI_UNSUPPORTED_REQUEST        = 2031, /**<BNEP:多播响应代码不支持的请求*/
    OI_BNEP_FILTER_MULTI_FAILED_INVALID_ADDRESS     = 2032, /**<BNEP:多播响应代码无效地址*/
    OI_BNEP_FILTER_MULTI_FAILED_MAX_LIMIT_REACHED   = 2033, /**<BNEP:已达到多播响应代码最大限制*/
    OI_BNEP_FILTER_MULTI_FAILED_SECURITY            = 2034, /**<BNEP:多播响应代码安全*/
    OI_BNEP_LOCAL_DEVICE_MUST_BE_MASTER             = 2040, /**<BNEP：设备必须是微微网的主控设备才能执行此功能*/
    OI_BNEP_PACKET_FILTERED_OUT                     = 2041, /**<BNEP:数据包未通过当前筛选器*/

    OI_NETIFC_UP_FAILED                    = 2101, /**<NETIFC:无法打开网络接口*/
    OI_NETIFC_COULD_NOT_CREATE_THREAD      = 2102, /**<NETIFC:网络接口无法创建读取线程*/
    OI_NETIFC_INITIALIZATION_FAILED        = 2103, /**<NETIFC:网络接口初始化错误*/
    OI_NETIFC_INTERFACE_ALREADY_UP         = 2104, /**<NETIFC:网络接口已启动*/
    OI_NETIFC_INTERFACE_NOT_UP             = 2105, /**<NETIFC:网络接口未启动*/
    OI_NETIFC_PACKET_TOO_BIG               = 2106, /**<NETIFC:数据包太大*/

    OI_PAN_ROLE_ALREADY_REGISTERED         = 2201, /**<PAN:此PAN角色已注册*/
    OI_PAN_ROLE_NOT_ALLOWED                = 2202, /**<PAN:当前不允许PAN角色*/
    OI_PAN_INCOMPATIBLE_ROLES              = 2203, /**<PAN:仅允许某些本地和远程角色组合*/
    OI_PAN_INVALID_ROLE                    = 2204, /**<PAN:指定的角色不是定义的PAN角色之一*/
    OI_PAN_CONNECTION_IN_PROGRESS          = 2205, /**<PAN:当前正在建立PAN连接*/
    OI_PAN_USER_ALREADY_CONNECTED          = 2206, /**<PAN:PAN用户角色仅允许单个连接*/
    OI_PAN_DEVICE_CONNECTED                = 2207, /**<PAN:已存在到指定设备的PAN连接*/

    OI_CODEC_SBC_NO_SYNCWORD               = 2301, /**<CODEC:找不到SBC SYNCWORD*/
    OI_CODEC_SBC_NOT_ENOUGH_HEADER_DATA    = 2302, /**<CODEC：提供的数据不足，无法解码SBC标头*/
    OI_CODEC_SBC_NOT_ENOUGH_BODY_DATA      = 2303, /**<CODEC:解码了标头，但没有足够的数据来包含帧的其余部分*/
    OI_CODEC_SBC_NOT_ENOUGH_AUDIO_DATA     = 2304, /**<CODEC:此帧的音频数据不足*/
    OI_CODEC_SBC_CHECKSUM_MISMATCH         = 2305, /**<CODEC:帧标头与校验和不匹配*/
    OI_CODEC_SBC_PARTIAL_DECODE            = 2306, /**<CODEC:解码成功，但帧数据仍保留。下一次呼叫将提供音频而不消耗输入数据。*/

    OI_FIFOQ_QUEUE_NOT_ALIGNED             = 2401, /**<FIFOQ:队列必须32位对齐*/
    OI_FIFOQ_INVALID_Q                     = 2402, /**<FIFOQ:队列参数不是有效的队列*/
    OI_FIFOQ_BUF_TOO_LARGE                 = 2403, /**<FIFOQ:尝试对太大的缓冲区进行排队*/
    OI_FIFOQ_FULL                          = 2404, /**<FIFOQ:enqueue（）失败，队列已满*/
    OI_FIFOQ_NOT_ALLOCATED                 = 2405, /**<FIFOQ:Enqueue QBuf（）失败，未分配缓冲区*/
    OI_FIFOQ_INVALID_DATA_PTR              = 2406, /**<FIFOQ:Enqueue QBuf（）失败，数据指针不匹配*/

    OI_HID_HOST_SERVICE_NOT_STARTED        = 2601, /**<HID:除非启动HID主机，否则无法连接到HID设备*/
    OI_HID_DEVICE_SERVICE_NOT_STARTED      = 2602, /**<HID:除非启动HID设备，否则无法连接到HID主机*/

    OI_AT_ERROR                            = 2701, /**<AT:ERROR响应*/
    OI_AT_NO_CARRIER                       = 2702, /**<AT:无载波响应*/
    OI_AT_BUSY                             = 2703, /**<AT:忙响应*/
    OI_AT_NO_ANSWER                        = 2704, /**<AT:无应答*/
    OI_AT_DELAYED                          = 2705, /**<AT:延迟响应*/
    OI_AT_BLACKLISTED                      = 2706, /**<AT:黑名单响应*/
    OI_AT_CME_ERROR                        = 2707, /**<AT:+CME错误响应*/
    OI_AT_CMS_ERROR                        = 2708, /**<AT:+CMS错误响应*/

    OI_BLST_CHARACTER_TIMEOUT              = 2801, /**<BLST:等待来自客户端的字符时超时。*/
    OI_BLST_ACKNOWLDGE_TIMEOUT             = 2802, /**<BLST:等待客户端的事件确认时超时*/
    OI_BLST_TX_NOT_READY                   = 2803, /**<BLST:BLST未准备好向客户端发送BHAPI消息。*/
    OI_BLST_TX_BUSY                        = 2804, /**<BLST:BLST传输缓冲区正在使用中。*/

    OI_AVDTP_CONNECTION_SEQ_ERROR          = 2901, /**<AVDTP:信令/媒体信道连接的顺序中断。*/
    OI_AVDTP_OUT_OF_RESOURCES              = 2902, /**<AVDTP:尝试分配过多的端点或信令信道。*/

    OI_PBAP_REPOSITORY_NOT_SET             = 3001, /**<PBAP:必须设置电话簿存储库才能完成操作。*/
    OI_PBAP_PHONEBOOK_NOT_SET              = 3002, /**<PBAP:设置电话簿以完成操作。*/

    OI_AADP_BAD_ENDPOINT                   = 3101, /**<AADP:指定的本地终结点无效*/
    OI_AADP_BAD_STATE                      = 3102, /**<AADP:AADP状态对此操作不正确。*/

    OI_UNICODE_INVALID_SOURCE              = 3200, /**<Unicode转换：源字符串具有无效的字符编码。*/
    OI_UNICODE_SOURCE_EXHAUSTED            = 3201, /**<Unicode转换：源缓冲区末尾的Unicode字符不完整。*/
    OI_UNICODE_DESTINATION_EXHAUSTED       = 3202, /**＜Unicode转换：目标缓冲区不够大，无法容纳生成的Unicode字符串。*/

    OI_AVRCP_TOO_MANY_CONNECTIONS          = 3300, /**<AVRCP：超过了同时AVCTP连接的最大数量。*/
    OI_AVRCP_NOT_IMPLEMENTED               = 3301, /**<AVRCP:目标未实现操作码和操作数指定的命令。*/
    OI_AVRCP_REJECTED                      = 3302, /**<AVRCP:由于命令包中的操作数无效，目标无法响应。*/
    OI_AVRCP_INVALID_RESPONSE              = 3303, /**<AVRCP:控制器收到参数无效的响应*/
    OI_AVRCP_RESPONSE_PACKET_OVERFLOW      = 3304, /**<AVRCP：响应消息在一个AVRCP数据包（512字节）中不存在，必须被分段。*/
    OI_AVRCP_RESPONSE_INVALID_PDU          = 3305, /**<AVRCP:命令被拒绝：目标收到了一个它不理解的PDU。*/
    OI_AVRCP_RESPONSE_INVALID_PARAMETER    = 3306, /**<AVRCP:命令被拒绝：目标收到了一个参数ID不正确的PDU。*/
    OI_AVRCP_RESPONSE_PARAMETER_NOT_FOUND  = 3307, /**<AVRCP:命令被拒绝：未找到指定的参数，如果了解参数ID，但内容错误或损坏，则发送。*/
    OI_AVRCP_RESPONSE_INTERNAL_ERROR       = 3308, /**<AVRCP:命令被拒绝：目标检测到其他错误条件。*/
    OI_MAX_BM3_STATUS_VAL,       /* 最大BM3状态代码*/

    /* 为BM3 SDK平台特定实现保留的状态代码值*/
    OI_STATUS_RESERVED_FOR_BCOT = 9000,

    /* 为BHAPI产品保留的状态代码值*/
    OI_STATUS_RESERVED_FOR_BHAPI = 9200,

    /* 为Soundabout产品保留的状态代码值*/
    OI_STATUS_RESERVED_FOR_SOUNDABOUT = 9400,

    /*
     * 大于或等于此值的状态代码值保留供应用程序使用。但是，由于编译器之间的差异以及16位和32位平台之间的差异，自定义状态代码应在16位范围内，因此状态代码的范围可以从0到65534（包括65535）
     */
    OI_STATUS_RESERVED_FOR_APPS = 10000,



    OI_STATUS_NONE = 0xffff     /**<特殊状态代码，表示没有状态。（仅用于涉及OI_SLOG_ERROR（）和OI_SLOG_WARNING（）的特殊情况。）*/

} OI_STATUS;


/* 当新的保留块添加到上面的列表中时，请记住更新下面的#define。*/
#define OI_NUM_RESERVED_STATUS_BLOCKS 4 /**<保留的状态代码块数，包括用户应用程序*/


/**
 * 测试是否成功
 */
#define OI_SUCCESS(x)    ((x) == OI_OK)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* _OI_STATUS_H */

