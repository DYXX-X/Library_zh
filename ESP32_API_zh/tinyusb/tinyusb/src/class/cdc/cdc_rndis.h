/* 
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019 Ha Thach（tinyusb.org）
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

/** \ingroup ClassDriver_CDC通信设备类（CDC）\defgroup CDC_RNDIS远程网络驱动程序接口规范（RNDIS）@{\defgroup CDC_RNDIS_通用定义
 *  @{ */

#ifndef _TUSB_CDC_RNDIS_H_
#define _TUSB_CDC_RNDIS_H_

#include "cdc.h"

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __CC_ARM
#pragma diag_suppress 66 // 抑制Keil警告#66-D：枚举值超出“int”范围
#endif

///RNDIS消息类型
typedef enum
{
  RNDIS_MSG_PACKET           = 0x00000001UL, ///<主机和设备使用此功能相互发送网络数据。

  RNDIS_MSG_INITIALIZE       = 0x00000002UL, ///<由主机发送以初始化设备。
  RNDIS_MSG_INITIALIZE_CMPLT = 0x80000002UL, ///<设备对初始化消息的响应。

  RNDIS_MSG_HALT             = 0x00000003UL, ///<由主机发送以停止设备。这没有回应。设备可以选择向主机发送此消息。

  RNDIS_MSG_QUERY            = 0x00000004UL, ///<由主机发送以发送查询OID。
  RNDIS_MSG_QUERY_CMPLT      = 0x80000004UL, ///<设备对查询OID的响应。

  RNDIS_MSG_SET              = 0x00000005UL, ///<由主机发送以发送设置的OID。
  RNDIS_MSG_SET_CMPLT        = 0x80000005UL, ///<设备对设置OID的响应。

  RNDIS_MSG_RESET            = 0x00000006UL, ///<由主机发送以在设备上执行软重置。
  RNDIS_MSG_RESET_CMPLT      = 0x80000006UL, ///<重置消息的设备响应。

  RNDIS_MSG_INDICATE_STATUS  = 0x00000007UL, ///<当接收到无法识别的消息时，由设备发送以指示其状态或错误。

  RNDIS_MSG_KEEP_ALIVE       = 0x00000008UL, ///<在空闲期间，主机每隔几秒发送一次，以检查设备是否仍有响应。设备可以选择发送此消息以检查主机是否处于活动状态。
  RNDIS_MSG_KEEP_ALIVE_CMPLT = 0x80000008UL  ///<设备对保持活动消息的响应。当设备实现可选的KeepAliveTimer时，主机可以用此消息响应来自设备的保活消息。
}rndis_msg_type_t;

///RNDIS消息状态值
typedef enum
{
  RNDIS_STATUS_SUCCESS          = 0x00000000UL, ///<成功
  RNDIS_STATUS_FAILURE          = 0xC0000001UL, ///<未指定的错误
  RNDIS_STATUS_INVALID_DATA     = 0xC0010015UL, ///<无效数据错误
  RNDIS_STATUS_NOT_SUPPORTED    = 0xC00000BBUL, ///<不支持的请求错误
  RNDIS_STATUS_MEDIA_CONNECT    = 0x4001000BUL, ///<设备连接到网络介质。
  RNDIS_STATUS_MEDIA_DISCONNECT = 0x4001000CUL  ///<设备与介质断开连接。
}rndis_msg_status_t;

#ifdef __CC_ARM
#pragma diag_default 66 // 将Keil 66恢复到正常严重程度
#endif

//--------------------------------------------------------------------+
// MESSAGE STRUCTURE
//--------------------------------------------------------------------+

//-------------初始化-------------//
///\ brief初始化消息
///\details主机必须发送此消息以初始化设备。
typedef struct {
  uint32_t type          ; ///<消息类型，必须是\ref RNDIS_MSG_INITIALIZE
  uint32_t length        ; ///<消息长度（字节），必须为0x18
  uint32_t request_id    ; ///<由主机生成的32位整数值，用于将主机发送的请求与设备的响应相匹配。
  uint32_t major_version ; ///<主机实现的RNDIS协议的主要版本。
  uint32_t minor_version ; ///<主机实现的RNDIS协议的次要版本
  uint32_t max_xfer_size ; ///<主机希望从设备接收的任何单总线数据传输的最大大小（字节）。
}rndis_msg_initialize_t;

///\ brief初始化完成消息
///\details设备必须响应初始化消息发送此消息。
typedef struct {
  uint32_t type                    ; ///<消息类型，必须是\ref RNDIS_MSG_INITIALIZE_CMPLT
  uint32_t length                  ; ///<消息长度（字节），必须为0x30
  uint32_t request_id              ; ///<此消息作为响应的\ref rndis_msg_initialize_t的request_id字段中的32位整数值。
  uint32_t status                  ; ///<设备的初始化状态，值来自\ref rndis_msg_status_t
  uint32_t major_version           ; ///<设备支持的编号最高的RNDIS协议版本。
  uint32_t minor_version           ; ///<设备支持的编号最高的RNDIS协议版本。
  uint32_t device_flags            ; ///<必须设置为0x000000010。保留其他值以供将来使用。
  uint32_t medium                  ; ///对于RNDIS_MEDIUM_802_3，<为0x00
  uint32_t max_packet_per_xfer     ; ///<设备在单个总线传输中可以处理的最大级联\ref RNDIS_MSG_PACKET消息数。该值必须至少为1。
  uint32_t max_xfer_size           ; ///<设备希望从主机接收的任何单总线数据传输的最大大小（字节）。
  uint32_t packet_alignment_factor ; ///<设备对作为多消息传输一部分的每个RNDIS消息期望的字节对齐。该值指定为2的指数；例如，主机使用2<SUP>{PacketAlignmentFactor}</SUP>作为对齐值。
  uint32_t reserved[2]             ;
} rndis_msg_initialize_cmplt_t;

//-------------查询-------------//
///\brief查询消息
///\details主机必须发送此消息以查询OID。
typedef struct {
  uint32_t type          ; ///<消息类型，必须是\ref RNDIS_MSG_QUERY
  uint32_t length        ; ///<以字节为单位的消息长度，包括标头和缓冲区
  uint32_t request_id    ; ///<由主机生成的32位整数值，用于将主机发送的请求与设备的响应相匹配。
  uint32_t oid           ; ///<主机操作系统定义的标识符的整数值，用于查询的设备的参数。
  uint32_t buffer_length ; ///<OID查询所需输入数据的长度（字节）。当没有与OID关联的输入数据时，必须将其设置为0。
  uint32_t buffer_offset ; ///<request_id字段开头的偏移量（字节），查询的输入数据位于消息中。当没有与OID关联的输入数据时，此值必须设置为0。
  uint32_t reserved      ;
  uint8_t  oid_buffer[]  ; ///<灵活阵列包含主机提供的输入数据，根据主机NDIS规范，设备处理OID查询请求所需的输入数据。
} rndis_msg_query_t, rndis_msg_set_t;

TU_VERIFY_STATIC(sizeof(rndis_msg_query_t) == 28, "Make sure flexible array member does not affect layout");

///\brief查询完成消息
///\details此消息必须由设备响应查询OID消息发送。
typedef struct {
  uint32_t type          ; ///<消息类型，必须是\ref RNDIS_MSG_QUERY_CMPLT
  uint32_t length        ; ///<以字节为单位的消息长度，包括标头和缓冲区
  uint32_t request_id    ; ///<此消息作为响应的\ref rndis_msg_query_t的request_id字段中的32位整数值。
  uint32_t status        ; ///<查询请求的处理状态的值来自\ref rndis_msg_status_t。
  uint32_t buffer_length ; ///<查询响应中数据的长度（字节）。当没有OIDInputBuffer时，必须将其设置为0。
  uint32_t buffer_offset ; ///<消息中查询响应数据所在的request_id字段开头的偏移量（以字节为单位）。当没有\ref oid_buffer时，必须将其设置为0。
  uint8_t  oid_buffer[]  ; ///<Flexible数组成员包含主机指定的OID查询请求的响应数据。
} rndis_msg_query_cmplt_t;

TU_VERIFY_STATIC(sizeof(rndis_msg_query_cmplt_t) == 24, "Make sure flexible array member does not affect layout");

//-------------重置-------------//
///\ brief重置消息
///\details主机必须发送此消息才能在设备上执行软重置。
typedef struct {
  uint32_t type     ; ///<消息类型，必须是\ref RNDIS_MSG_RESET
  uint32_t length   ; ///<消息长度（字节），必须为0x06
  uint32_t reserved ;
} rndis_msg_reset_t;

///\ brief重置完成消息
///\details此消息必须由设备发送以响应重置消息。
typedef struct {
  uint32_t type             ; ///<消息类型，必须是\ref RNDIS_MSG_RESET_CMPLT
  uint32_t length           ; ///<消息长度（字节），必须为0x10
  uint32_t status           ; ///<\ref rndis_msg_reset_t的处理状态的值来自\ref rndis_msg_status_t。
  uint32_t addressing_reset ; ///<此字段指示在重置操作期间是否丢失了作为多播地址列表或分组过滤器的寻址信息。如果设备要求主机重新发送寻址信息，则必须设置为0x00000001，否则必须设置为零。
} rndis_msg_reset_cmplt_t;

//typedef结构{
//  uint32_t型；
//  uint32_t长度；
//  uint32_t状态；
//  uint32_t缓冲区长度；
//  uint32_t缓冲_偏移；
//  uint32_t诊断状态；//可选择的
//  uint32_t诊断错误偏移量；//可选择的
//  uint32_t状态缓冲区[0]；//可选择的
//}rndis_msg_indicate_status_t；

///\ brief保持活动消息
///\details主机必须发送此消息以检查设备是否仍有响应。设备可以选择发送此消息以检查主机是否处于活动状态
typedef struct {
  uint32_t type       ; ///<消息类型
  uint32_t length     ; ///<消息长度（字节），必须为0x10
  uint32_t request_id ;
} rndis_msg_keep_alive_t, rndis_msg_halt_t;

///\ brief设置完整消息
///该消息必须响应请求消息发送
typedef struct {
  uint32_t type       ; ///<消息类型
  uint32_t length     ; ///<消息长度（字节），必须为0x10
  uint32_t request_id ; ///<必须与请求消息相同
  uint32_t status     ; ///<此消息作为响应的设备对请求消息请求的处理状态。
} rndis_msg_set_cmplt_t, rndis_msg_keep_alive_cmplt_t;

///\ brief数据包消息
///\ brief主机和设备必须使用此消息相互发送网络数据。
typedef struct {
  uint32_t type                          ; ///<消息类型，必须是\ref RNDIS_MSG_PACKET
  uint32_t length                        ; ///<消息长度（字节），此RNDIS消息的总长度，包括报头、有效载荷和填充。
  uint32_t data_offset                   ; ///<指定从该消息的data_offset字段开始到数据开始的偏移量（以字节为单位）。这必须是4的整数倍。
  uint32_t data_length                   ; ///<指定此消息有效负载中的字节数。
  uint32_t out_of_band_data_offet        ; ///<指定此消息中DataOffset字段开头的第一个带外数据记录的偏移量（以字节为单位）。当存在带外数据时，必须是4的整数倍，否则设置为0。当有多个带外数据记录时，每个后续记录必须立即跟随前一个带外记录。
  uint32_t out_of_band_data_length       ; ///<指定带外数据的总长度（以字节为单位）。
  uint32_t num_out_of_band_data_elements ; ///<指定此消息中带外记录的数量。
  uint32_t per_packet_info_offset        ; ///<指定此消息中每个数据包信息数据记录的起始位置与data_offset字段起始位置之间的偏移量（以字节为单位）。当存在每个数据包信息数据记录时，必须是4的整数倍，否则必须设置为0。当存在多个每包信息数据记录时，每个后续记录必须紧跟在前一记录之后。
  uint32_t per_packet_info_length        ; ///<指定此消息中包含的每个数据包信息的总长度（以字节为单位）。
  uint32_t reserved[2]                   ;
  uint32_t payload[0]                    ; ///<此消息中包含的网络数据。

  // uint8_t填充[0]
  // 在消息末尾添加额外的零字节，以符合
  // 内部和外部填充要求。内部衬垫应符合
  // 带外数据记录和每包信息数据记录的规范。外部
  //填充大小应根据PacketAlignmentFactor字段规范确定
  //在设备的REMOTE_NDIS_INITIALIZE_CMPLT消息中，当多个
  //REMOTE_NDIS_PACKET_MSG消息捆绑在一条总线本机消息中。
  //在这种情况下，除最后一个REMOTE_NDIS_PACKET_MSG外，其他所有人都必须遵守
  //PacketAlignmentFactor字段。

  // rndis_msg_packet_t[0]：（可选）如果支持每个总线事务多个数据包
} rndis_msg_packet_t;


typedef struct {
  uint32_t size    ; ///<此标头以及附加数据和填充的长度（以字节为单位）。该值必须是4的整数倍。
  uint32_t type    ; ///<必须符合主机操作系统规范。
  uint32_t offset  ; ///<此记录开头到数据开头的字节偏移量。
  uint32_t data[0] ; ///<灵活阵列包含数据
} rndis_msg_out_of_band_data_t, rndis_msg_per_packet_info_t;

//--------------------------------------------------------------------+
// NDIS对象ID
//--------------------------------------------------------------------+

///NDIS对象ID
typedef enum
{
  //-------------一般要求OID-------------//
  RNDIS_OID_GEN_SUPPORTED_LIST          = 0x00010101, ///<支持的OID列表
  RNDIS_OID_GEN_HARDWARE_STATUS         = 0x00010102, ///<硬件状态
  RNDIS_OID_GEN_MEDIA_SUPPORTED         = 0x00010103, ///<支持的媒体类型（编码）
  RNDIS_OID_GEN_MEDIA_IN_USE            = 0x00010104, ///<正在使用的媒体类型（已编码）
  RNDIS_OID_GEN_MAXIMUM_LOOKAHEAD       = 0x00010105, ///<
  RNDIS_OID_GEN_MAXIMUM_FRAME_SIZE      = 0x00010106, ///<最大帧大小（字节）
  RNDIS_OID_GEN_LINK_SPEED              = 0x00010107, ///<以100 bps为单位的链路速度
  RNDIS_OID_GEN_TRANSMIT_BUFFER_SPACE   = 0x00010108, ///<传输缓冲区空间
  RNDIS_OID_GEN_RECEIVE_BUFFER_SPACE    = 0x00010109, ///<接收缓冲区空间
  RNDIS_OID_GEN_TRANSMIT_BLOCK_SIZE     = 0x0001010A, ///<单个数据包在NIC的传输缓冲区空间中占用的最小存储量（字节）
  RNDIS_OID_GEN_RECEIVE_BLOCK_SIZE      = 0x0001010B, ///<单个数据包在NIC的接收缓冲区空间中占用的存储量（字节）
  RNDIS_OID_GEN_VENDOR_ID               = 0x0001010C, ///<供应商NIC代码
  RNDIS_OID_GEN_VENDOR_DESCRIPTION      = 0x0001010D, ///<供应商网卡说明
  RNDIS_OID_GEN_CURRENT_PACKET_FILTER   = 0x0001010E, ///<当前数据包筛选器（已编码）
  RNDIS_OID_GEN_CURRENT_LOOKAHEAD       = 0x0001010F, ///<当前前瞻大小（字节）
  RNDIS_OID_GEN_DRIVER_VERSION          = 0x00010110, ///<驱动程序使用的NDIS版本号
  RNDIS_OID_GEN_MAXIMUM_TOTAL_SIZE      = 0x00010111, ///<最大数据包总长度（字节）
  RNDIS_OID_GEN_PROTOCOL_OPTIONS        = 0x00010112, ///<可选协议标志（编码）
  RNDIS_OID_GEN_MAC_OPTIONS             = 0x00010113, ///<可选NIC标志（编码）
  RNDIS_OID_GEN_MEDIA_CONNECT_STATUS    = 0x00010114, ///<NIC是否连接到网络
  RNDIS_OID_GEN_MAXIMUM_SEND_PACKETS    = 0x00010115, ///<驱动程序每次调用MiniportSendPackets函数时可以接受的最大发送数据包数

  //-------------一般可选OID-------------//
  RNDIS_OID_GEN_VENDOR_DRIVER_VERSION   = 0x00010116, ///<供应商指定的驱动程序版本号
  RNDIS_OID_GEN_SUPPORTED_GUIDS         = 0x00010117, ///<微型端口驱动程序支持的自定义GUID（全局唯一标识符）
  RNDIS_OID_GEN_NETWORK_LAYER_ADDRESSES = 0x00010118, ///<与传输和驱动程序之间的绑定相关联的网络层地址列表
  RNDIS_OID_GEN_TRANSPORT_HEADER_OFFSET = 0x00010119, ///<数据包的附加标头大小
  RNDIS_OID_GEN_MEDIA_CAPABILITIES      = 0x00010201, ///<
  RNDIS_OID_GEN_PHYSICAL_MEDIUM         = 0x00010202, ///<微型端口驱动程序支持的物理介质（已编码）

  //-------------802.3对象（以太网）-------------//
  RNDIS_OID_802_3_PERMANENT_ADDRESS     = 0x01010101, ///<永久站点地址
  RNDIS_OID_802_3_CURRENT_ADDRESS       = 0x01010102, ///<当前电台地址
  RNDIS_OID_802_3_MULTICAST_LIST        = 0x01010103, ///<当前多播地址列表
  RNDIS_OID_802_3_MAXIMUM_LIST_SIZE     = 0x01010104, ///<多播地址列表的最大大小
} rndis_oid_type_t;

///RNDIS数据包过滤器位\ref RNDIS_OID_GEN_CURRENT_Packet_Filter。
typedef enum
{
  RNDIS_PACKET_TYPE_DIRECTED              = 0x00000001, ///<定向数据包。定向数据包包含的目标地址等于NIC的站点地址。
  RNDIS_PACKET_TYPE_MULTICAST             = 0x00000002, ///<发送到多播地址列表中的地址的多播地址数据包。
  RNDIS_PACKET_TYPE_ALL_MULTICAST         = 0x00000004, ///<所有多播地址数据包，而不仅仅是多播地址列表中列举的数据包。
  RNDIS_PACKET_TYPE_BROADCAST             = 0x00000008, ///<广播数据包。
  RNDIS_PACKET_TYPE_SOURCE_ROUTING        = 0x00000010, ///<所有源路由数据包。如果协议驱动程序设置此位，NDIS库将尝试充当源路由桥。
  RNDIS_PACKET_TYPE_PROMISCUOUS           = 0x00000020, ///<指定所有数据包，无论是否启用VLAN筛选以及VLAN标识符是否匹配。
  RNDIS_PACKET_TYPE_SMT                   = 0x00000040, ///<FDDI NIC接收的SMT数据包。
  RNDIS_PACKET_TYPE_ALL_LOCAL             = 0x00000080, ///<由已安装协议发送的所有数据包以及由给定NdisBindingHandle标识的NIC指示的所有数据。
  RNDIS_PACKET_TYPE_GROUP                 = 0x00001000, ///<发送到当前组地址的数据包。
  RNDIS_PACKET_TYPE_ALL_FUNCTIONAL        = 0x00002000, ///<所有功能地址数据包，而不仅仅是当前功能地址中的数据包。
  RNDIS_PACKET_TYPE_FUNCTIONAL            = 0x00004000, ///<发送到当前功能地址中包含的地址的功能地址数据包。
  RNDIS_PACKET_TYPE_MAC_FRAME             = 0x00008000, ///<令牌环NIC接收的NIC驱动程序帧。
  RNDIS_PACKET_TYPE_NO_LOCAL              = 0x00010000,
} rndis_packet_filter_type_t;

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_CDC_RNDIS_H_ */

/** @} */
/** @} */

