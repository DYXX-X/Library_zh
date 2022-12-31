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

/** \ingroup group_class\defgroup ClassDriver_MSC MassStorage（MSC）
 *  @{ */

/**  \defgroup ClassDriver_MSC_通用通用定义
 *  @{ */

#ifndef _TUSB_MSC_H_
#define _TUSB_MSC_H_

#include "common/tusb_common.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 大容量存储类常量
//--------------------------------------------------------------------+
///MassStorage子类
typedef enum
{
  MSC_SUBCLASS_RBC = 1 , ///<缩减块命令（RBC）T10项目1240-D
  MSC_SUBCLASS_SFF_MMC , ///<SFF-8020i、MMC-2（ATAPI）。通常由CD/DVD设备使用
  MSC_SUBCLASS_QIC     , ///<QIC-157.通常由磁带设备使用
  MSC_SUBCLASS_UFI     , ///<UFI。通常由软盘驱动器（FDD）设备使用
  MSC_SUBCLASS_SFF     , ///<SFF-8070i。可由软盘驱动器（FDD）设备使用
  MSC_SUBCLASS_SCSI      ///<SCSI透明命令集
}msc_subclass_type_t;

enum {
  MSC_CBW_SIGNATURE = 0x43425355, ///<恒定值43425355h（小端）
  MSC_CSW_SIGNATURE = 0x53425355  ///<恒定值53425355h（小端）
};

///\ brief MassStorage协议。
///CBI仅批准与全速防淹盘一起使用，不得与高速或防淹盘以外的设备一起使用
typedef enum
{
  MSC_PROTOCOL_CBI              = 0 ,  ///<控制/批量/中断协议（带命令完成中断）
  MSC_PROTOCOL_CBI_NO_INTERRUPT = 1 ,  ///<控制/批量/中断协议（无命令完成中断）
  MSC_PROTOCOL_BOT              = 0x50 ///<仅散装运输
}msc_protocol_type_t;

///MassStorage类特定控制请求
typedef enum
{
  MSC_REQ_GET_MAX_LUN = 254, ///<Get Max LUN设备请求用于确定设备支持的逻辑单元数。设备上的逻辑单元编号应从LUN 0开始连续编号，最多15个LUN
  MSC_REQ_RESET       = 255  ///<此请求用于重置大容量存储设备及其相关接口。该类特定请求应为主机的下一个CBW准备好设备。
}msc_request_type_t;

///\p简要命令块状态值
///\details指示命令的成功或失败。如果命令完成，设备应将此字节设置为零
///成功。非零值应表示命令执行过程中出现以下故障
typedef enum
{
  MSC_CSW_STATUS_PASSED = 0 , ///< MSC_CSW_STATUS_PASSED
  MSC_CSW_STATUS_FAILED     , ///< MSC_CSW_STATUS_FAILED
  MSC_CSW_STATUS_PHASE_ERROR  ///< MSC_CSW_STATUS_PHASE_ERROR
}msc_csw_status_t;

///命令块包装器
typedef struct TU_ATTR_PACKED
{
  uint32_t signature;   ///<帮助将此数据包标识为CBW的签名。签名字段应包含值43425355h（小端），表示CBW。
  uint32_t tag;         ///<主机发送的标记。设备应在相关CSW的dCSWTag字段中将此字段的内容回传给主机。dCSWTag将CSW与相应的CBW正相关。
  uint32_t total_bytes; ///<在执行此命令期间，主机希望在Bulk In或Bulk Out端点上传输的数据字节数（由方向位指示）。如果该字段为零，则设备和主机不得在CBW和相关CSW之间传输数据，并且设备应忽略bmCBWFlags中的Direction位值。
  uint8_t dir;          ///<此字段的第7位定义传输方向\n-0：从主机到设备的数据输出。\n-1：从设备到主机的数据输入。
  uint8_t lun;          ///<要向其发送命令块的设备逻辑单元号（LUN）。对于支持多个LUN的设备，主机应将此命令块寻址到的LUN放入此字段。否则，主机应将此字段设置为零。
  uint8_t cmd_len;      ///<CBWCBin字节的有效长度。这定义了命令块的有效长度。唯一合法值为1到16
  uint8_t command[16];  ///<设备要执行的命令块。设备应将此字段中的第一个cmd_len字节解释为命令块
}msc_cbw_t;

TU_VERIFY_STATIC(sizeof(msc_cbw_t) == 31, "size is not correct");

///命令状态包装器
typedef struct TU_ATTR_PACKED
{
  uint32_t signature    ; ///<帮助将此数据包标识为CSW的签名。签名字段应包含值53425355h（小端），表示CSW。
  uint32_t tag          ; ///<设备应将该字段设置为相关CBW的dCBWTag中接收的值。
  uint32_t data_residue ; ///<对于数据输出，设备应在dCSWDataResi中报告dCBWDataTransferLength中规定的预期数据量与设备处理的实际数据量之间的差异。对于数据输入，设备应在dCSWDataResi中报告dCBWDataTransferLength中规定的预期数据量与设备发送的相关数据的实际数量之间的差异
  uint8_t  status       ; ///<表示命令的成功或失败。\ref msc_csw_status_t中的值
}msc_csw_t;

TU_VERIFY_STATIC(sizeof(msc_csw_t) == 13, "size is not correct");

//--------------------------------------------------------------------+
// SCSI常量
//--------------------------------------------------------------------+

///SCSI命令操作代码
typedef enum
{
  SCSI_CMD_TEST_UNIT_READY              = 0x00, ///<SCSI Test Unit Ready（SCSI测试单元就绪）命令用于确定设备是否准备好传输数据（读/写），即磁盘是否已启动、磁带是否已加载并就绪等。设备不执行自检操作。
  SCSI_CMD_INQUIRY                      = 0x12, ///＜SCSI查询命令用于从目标设备获取基本信息。
  SCSI_CMD_MODE_SELECT_6                = 0x15, ///<为应用程序客户端提供了一种向设备服务器指定介质、逻辑单元或外围设备参数的方法。执行MODE SELECT（6）命令的设备服务器也应执行MODE SENSE（6）指令。应用程序客户端应在每次MODE SELECT（6）之前发出MODE SENSE（6），以确定支持的模式页面、页面长度和其他参数。
  SCSI_CMD_MODE_SENSE_6                 = 0x1A, ///<为设备服务器提供了向应用程序客户端报告参数的方法。它是MODE SELECT（6）命令的补充命令。执行MODE SENSE（6）命令的设备服务器也应执行MODE SELECT（6）指令。
  SCSI_CMD_START_STOP_UNIT              = 0x1B,
  SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL = 0x1E,
  SCSI_CMD_READ_CAPACITY_10             = 0x25, ///<SCSI Read Capacity命令用于从目标设备获取数据容量信息。
  SCSI_CMD_REQUEST_SENSE                = 0x03, ///<SCSI请求检测命令是SCSI计算机协议标准的一部分。此命令用于从目标设备获取感测数据（状态/错误信息）。
  SCSI_CMD_READ_FORMAT_CAPACITY         = 0x23, ///<该命令允许主机请求已安装的可写介质的可能格式容量列表。此命令还可以在安装介质时报告介质的可写容量
  SCSI_CMD_READ_10                      = 0x28, ///<READ（10）命令请求设备服务器读取指定的逻辑块并将其传输到缓冲区中的数据。
  SCSI_CMD_WRITE_10                     = 0x2A, ///<WRITE（10）命令请求设备服务器从数据输出缓冲区传输指定的逻辑块并将其写入。
}scsi_cmd_type_t;

///SCSI检测密钥
typedef enum
{
  SCSI_SENSE_NONE            = 0x00, ///<无特定感测键。这是一个成功的命令
  SCSI_SENSE_RECOVERED_ERROR = 0x01, ///<表示最后一个命令已成功完成，并由磁盘驱动器执行了某些恢复操作。
  SCSI_SENSE_NOT_READY       = 0x02, ///<表示无法访问寻址的逻辑单元。
  SCSI_SENSE_MEDIUM_ERROR    = 0x03, ///<表示命令因未恢复的错误条件而终止。
  SCSI_SENSE_HARDWARE_ERROR  = 0x04, ///<表示磁盘驱动器在执行命令或自检期间检测到不可恢复的硬件故障。
  SCSI_SENSE_ILLEGAL_REQUEST = 0x05, ///<指示命令描述符块或其他参数中的非法参数
  SCSI_SENSE_UNIT_ATTENTION  = 0x06, ///<表示磁盘驱动器可能已重置。
  SCSI_SENSE_DATA_PROTECT    = 0x07, ///<表示尝试在受此操作保护的块上执行读取或写入介质的命令。不执行读取或写入操作。
  SCSI_SENSE_FIRMWARE_ERROR  = 0x08, ///<供应商特定的感应键。
  SCSI_SENSE_ABORTED_COMMAND = 0x0b, ///<表示磁盘驱动器已中止命令。
  SCSI_SENSE_EQUAL           = 0x0c, ///<表示SEARCH DATA命令满足相等的比较。
  SCSI_SENSE_VOLUME_OVERFLOW = 0x0d, ///<表示缓冲的外围设备已到达介质分区的末尾，并且数据仍保留在尚未写入介质的缓冲区中。
  SCSI_SENSE_MISCOMPARE      = 0x0e  ///<表示源数据与从介质读取的数据不匹配。
}scsi_sense_key_type_t;

//--------------------------------------------------------------------+
// SCSI主命令（SPC-4）
//--------------------------------------------------------------------+

///SCSI测试单元就绪命令
typedef struct TU_ATTR_PACKED
{
  uint8_t cmd_code    ; ///<SCSI_CMD_TEST_UNIT_READY的SCSI OpCode
  uint8_t lun         ; ///<逻辑单元
  uint8_t reserved[3] ;
  uint8_t control     ;
} scsi_test_unit_ready_t;

TU_VERIFY_STATIC(sizeof(scsi_test_unit_ready_t) == 6, "size is not correct");

///SCSI查询命令
typedef struct TU_ATTR_PACKED
{
  uint8_t cmd_code     ; ///<SCSI_CMD_INQUIRY的SCSI OpCode
  uint8_t reserved1    ;
  uint8_t page_code    ;
  uint8_t reserved2    ;
  uint8_t alloc_length ; ///<指定USB主机在数据输入缓冲区中分配的最大字节数。分配长度为零表示不应传输任何数据。
  uint8_t control      ;
} scsi_inquiry_t, scsi_request_sense_t;

TU_VERIFY_STATIC(sizeof(scsi_inquiry_t) == 6, "size is not correct");

///SCSI查询响应数据
typedef struct TU_ATTR_PACKED
{
  uint8_t peripheral_device_type     : 5;
  uint8_t peripheral_qualifier       : 3;

  uint8_t                            : 7;
  uint8_t is_removable               : 1;

  uint8_t version;

  uint8_t response_data_format       : 4;
  uint8_t hierarchical_support       : 1;
  uint8_t normal_aca                 : 1;
  uint8_t                            : 2;

  uint8_t additional_length;

  uint8_t protect                    : 1;
  uint8_t                            : 2;
  uint8_t third_party_copy           : 1;
  uint8_t target_port_group_support  : 2;
  uint8_t access_control_coordinator : 1;
  uint8_t scc_support                : 1;

  uint8_t addr16                     : 1;
  uint8_t                            : 3;
  uint8_t multi_port                 : 1;
  uint8_t                            : 1; // 特定于供应商
  uint8_t enclosure_service          : 1;
  uint8_t                            : 1;

  uint8_t                            : 1; // 特定于供应商
  uint8_t cmd_que                    : 1;
  uint8_t                            : 2;
  uint8_t sync                       : 1;
  uint8_t wbus16                     : 1;
  uint8_t                            : 2;

  uint8_t vendor_id[8]  ; ///<8字节的ASCII数据，用于识别产品供应商。
  uint8_t product_id[16]; ///<16字节的供应商定义的ASCII数据。
  uint8_t product_rev[4]; ///<供应商定义的4字节ASCII数据。
} scsi_inquiry_resp_t;

TU_VERIFY_STATIC(sizeof(scsi_inquiry_resp_t) == 36, "size is not correct");


typedef struct TU_ATTR_PACKED
{
  uint8_t response_code : 7; ///<70h-当前错误，固定格式71h-延迟错误，固定模式
  uint8_t valid         : 1;

  uint8_t reserved;

  uint8_t sense_key     : 4;
  uint8_t               : 1;
  uint8_t ili           : 1; ///<长度指示器不正确
  uint8_t end_of_medium : 1;
  uint8_t filemark      : 1;

  uint32_t information;
  uint8_t  add_sense_len;
  uint32_t command_specific_info;
  uint8_t  add_sense_code;
  uint8_t  add_sense_qualifier;
  uint8_t  field_replaceable_unit_code;

  uint8_t  sense_key_specific[3]; ///<sense键特定的有效位是键[0]的第7位，即Big Endian布局中的MSB

} scsi_sense_fixed_resp_t;

TU_VERIFY_STATIC(sizeof(scsi_sense_fixed_resp_t) == 18, "size is not correct");

typedef struct TU_ATTR_PACKED
{
  uint8_t cmd_code     ; ///<SCSI_CMD_MODE_SENSE_6的SCSI OpCode

  uint8_t : 3;
  uint8_t disable_block_descriptor : 1;
  uint8_t : 4;

  uint8_t page_code : 6;
  uint8_t page_control : 2;

  uint8_t subpage_code;
  uint8_t alloc_length;
  uint8_t control;
} scsi_mode_sense6_t;

TU_VERIFY_STATIC( sizeof(scsi_mode_sense6_t) == 6, "size is not correct");

// 这只是模式参数标题（6）。
typedef struct TU_ATTR_PACKED
{
  uint8_t data_len;
  uint8_t medium_type;

  uint8_t reserved : 7;
  bool write_protected : 1;

  uint8_t block_descriptor_len;
} scsi_mode_sense6_resp_t;

TU_VERIFY_STATIC( sizeof(scsi_mode_sense6_resp_t) == 4, "size is not correct");

typedef struct TU_ATTR_PACKED
{
  uint8_t cmd_code; ///＜SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL的SCSI OpCode
  uint8_t reserved[3];
  uint8_t prohibit_removal;
  uint8_t control;
} scsi_prevent_allow_medium_removal_t;

TU_VERIFY_STATIC( sizeof(scsi_prevent_allow_medium_removal_t) == 6, "size is not correct");

typedef struct TU_ATTR_PACKED
{
  uint8_t cmd_code;

  uint8_t immded : 1;
  uint8_t        : 7;

  uint8_t TU_RESERVED;

  uint8_t power_condition_mod : 4;
  uint8_t                     : 4;

  uint8_t start           : 1;
  uint8_t load_eject      : 1;
  uint8_t no_flush        : 1;
  uint8_t                 : 1;
  uint8_t power_condition : 4;

  uint8_t control;
} scsi_start_stop_unit_t;

TU_VERIFY_STATIC( sizeof(scsi_start_stop_unit_t) == 6, "size is not correct");

//--------------------------------------------------------------------+
// SCSI MMC
//--------------------------------------------------------------------+
///SCSI读取格式容量：写入容量
typedef struct TU_ATTR_PACKED
{
  uint8_t cmd_code;
  uint8_t reserved[6];
  uint16_t alloc_length;
  uint8_t control;
} scsi_read_format_capacity_t;

TU_VERIFY_STATIC( sizeof(scsi_read_format_capacity_t) == 10, "size is not correct");

typedef struct TU_ATTR_PACKED{
  uint8_t reserved[3];
  uint8_t list_length; ///必须是8*n，后面是可格式化容量描述符的字节长度。

  uint32_t block_num; ///逻辑块数
  uint8_t  descriptor_type; // 00:保留，01未格式化媒体，10格式化媒体，11不存在媒体

  uint8_t  reserved2;
  uint16_t block_size_u16;

} scsi_read_format_capacity_data_t;

TU_VERIFY_STATIC( sizeof(scsi_read_format_capacity_data_t) == 12, "size is not correct");

//--------------------------------------------------------------------+
// SCSI块命令（SBC-3）
// 注：SCSI命令中的所有数据都在Big Endian中
//--------------------------------------------------------------------+

///SCSI读取容量10命令：读取容量
typedef struct TU_ATTR_PACKED
{
  uint8_t  cmd_code                 ; ///＜SCSI_CMD_READ_CAPACITY_10的SCSI OpCode
  uint8_t  reserved1                ;
  uint32_t lba                      ; ///<此命令访问的第一个逻辑块地址（LBA）
  uint16_t reserved2                ;
  uint8_t  partial_medium_indicator ;
  uint8_t  control                  ;
} scsi_read_capacity10_t;

TU_VERIFY_STATIC(sizeof(scsi_read_capacity10_t) == 10, "size is not correct");

///SCSI读取容量10响应数据
typedef struct {
  uint32_t last_lba   ; ///<设备的最后一个逻辑块地址
  uint32_t block_size ; ///<块大小（字节）
} scsi_read_capacity10_resp_t;

TU_VERIFY_STATIC(sizeof(scsi_read_capacity10_resp_t) == 8, "size is not correct");

///SCSI读取10命令
typedef struct TU_ATTR_PACKED
{
  uint8_t  cmd_code    ; ///<SCSI操作码
  uint8_t  reserved    ; // 根据wiki，具有LUN
  uint32_t lba         ; ///<此命令访问的第一个逻辑块地址（LBA）
  uint8_t  reserved2   ;
  uint16_t block_count ; ///<此命令使用的块数
  uint8_t  control     ;
} scsi_read10_t, scsi_write10_t;

TU_VERIFY_STATIC(sizeof(scsi_read10_t) == 10, "size is not correct");
TU_VERIFY_STATIC(sizeof(scsi_write10_t) == 10, "size is not correct");

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_MSC_H_ */

/// @}
/// @}

