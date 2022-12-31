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

#ifndef _TUSB_MSC_DEVICE_H_
#define _TUSB_MSC_DEVICE_H_

#include "common/tusb_common.h"
#include "device/usbd.h"
#include "msc.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 类驱动程序配置
//--------------------------------------------------------------------+

#if !defined(CFG_TUD_MSC_EP_BUFSIZE) & defined(CFG_TUD_MSC_BUFSIZE)
  // TODO警告用户稍后使用新名称
  // #警告CFG_TUD_MSC_BUFSIZE已重命名为CFG_TUD-MSC_EP_BUFSIZE，请更新以使用新名称
  #define CFG_TUD_MSC_EP_BUFSIZE  CFG_TUD_MSC_BUFSIZE
#endif

#ifndef CFG_TUD_MSC_EP_BUFSIZE
  #error CFG_TUD_MSC_EP_BUFSIZE must be defined, value of a block size should work well, the more the better
#endif

TU_VERIFY_STATIC(CFG_TUD_MSC_EP_BUFSIZE < UINT16_MAX, "Size is not correct");

/** \addtogroup ClassDriver_MSC@{\defgroup MSC_Device设备
 *  @{ */

bool tud_msc_set_sense(uint8_t lun, uint8_t sense_key, uint8_t add_sense_code, uint8_t add_sense_qualifier);

//--------------------------------------------------------------------+
// 应用程序回调（WEAK是可选的）
//--------------------------------------------------------------------+

/**
 * 在收到\ref SCSI_CMD_READ_10命令时调用\param[in]lun逻辑单元编号\param[iin]lba要读取的逻辑块地址\param[i]offset lba的字节偏移量\param[out]缓冲区应用程序需要使用响应数据更新的缓冲区。\param[in]bufsize请求的字节
 *
 * \return读取的字节数，如果小于请求的字节，则返回字节数。Tinyusb将首先转移该金额，并再次调用该金额以获取剩余数据。
 *
 * \retval zero表示应用程序尚未准备好响应，例如磁盘I/O未完成。tinyusb稍后将再次使用相同的参数调用此回调。
 *
 * \retval negative表示错误，例如读取磁盘I/O。tinyusb将在命令状态包装器阶段停止相应的端点并返回失败状态。
 */
int32_t tud_msc_read10_cb (uint8_t lun, uint32_t lba, uint32_t offset, void* buffer, uint32_t bufsize);

/**
 * 收到\ref SCSI_CMD_WRITE_10命令时调用\param[in]lun逻辑单元编号\param[iin]lba要写入的逻辑块地址\param[in]offset从lba\param[out]缓冲区的字节偏移量保存写入数据的缓冲区。\param[in]bufsize请求的字节
 *
 * \return写入的字节数，如果它小于请求的字节数。Tinyusb将继续其他工作，并使用调整后的参数再次调用。
 *
 * \retval zero表示应用程序尚未就绪，例如磁盘I/O未完成。Tinyusb稍后将再次使用相同的参数调用此回调。
 *
 * \retval negative表示写入磁盘I/O时出错。Tinyusb将在命令状态包装器阶段停止相应的端点并返回失败状态。
 */
int32_t tud_msc_write10_cb (uint8_t lun, uint32_t lba, uint32_t offset, uint8_t* buffer, uint32_t bufsize);

// 收到SCSI_CMD_INQUIRY时调用
// 应用程序分别用最多8、16和4个字符的字符串填写供应商id、产品id和修订版
void tud_msc_inquiry_cb(uint8_t lun, uint8_t vendor_id[8], uint8_t product_id[16], uint8_t product_rev[4]);

// 收到测试单元就绪命令时调用。
// 返回true，允许主机读取/写入此LUN，例如插入SD卡
bool tud_msc_test_unit_ready_cb(uint8_t lun);

// 收到SCSI_CMD_READ_CAPACITY_10和SCSI_CMD_READ_FORMAT_CCAPITATION时调用，以确定磁盘大小
// 应用程序更新块计数和块大小
void tud_msc_capacity_cb(uint8_t lun, uint32_t* block_count, uint16_t* block_size);

/**
 * 收到不在下面内置列表中的SCSI命令时调用。
 * - READ_CAPACITY10, READ_FORMAT_CAPACITY, INQUIRY, TEST_UNIT_READY, START_STOP_UNIT, MODE_SENSE6, REQUEST_SENSE
 * -READ10和WRITE10有自己的回调
 *
 * \param[in]lun逻辑单元号\param[in]scsi_cmd scsi命令内容，应用程序必须检查这些内容才能相应响应\param[out]buffer buffer for scsi Data Stage。
 *                            -对于INPUT：应用程序必须用响应填充。
 *                            -对于OUTPUT，它保存来自host\param[in]bufsize Buffer的数据长度。
 *
 * \return实际处理的字节数，对于无数据命令，可以为零。\retval negative表示错误，例如不受支持的命令，tinyusb将停止相应的端点，并在命令状态包装阶段返回失败状态。
 */
int32_t tud_msc_scsi_cb (uint8_t lun, uint8_t const scsi_cmd[16], void* buffer, uint16_t bufsize);

/*-------------可选回调-------------*/

// 收到多个LUN实施所需的GET_MAX_LUN请求时调用
TU_ATTR_WEAK uint8_t tud_msc_get_maxlun_cb(void);

// 收到启动/停止单元命令时调用
// -Start=0：停止电源模式，如果load_eject=1：卸载磁盘存储
// -Start=1：活动模式，如果load_eject=1：加载磁盘存储
TU_ATTR_WEAK bool tud_msc_start_stop_cb(uint8_t lun, uint8_t power_condition, bool start, bool load_eject);

// 在Read10命令完成时调用
TU_ATTR_WEAK void tud_msc_read10_complete_cb(uint8_t lun);

// Write10命令完成时调用，可用于刷新闪存缓存
TU_ATTR_WEAK void tud_msc_write10_complete_cb(uint8_t lun);

// 在tud_msc_scsi_cb中的命令完成时调用
TU_ATTR_WEAK void tud_msc_scsi_complete_cb(uint8_t lun, uint8_t const scsi_cmd[16]);

// 挂钩以使大容量存储设备为只读。TODO删除
TU_ATTR_WEAK bool tud_msc_is_writable_cb(uint8_t lun);

/** @} */
/** @} */

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+
void     mscd_init            (void);
void     mscd_reset           (uint8_t rhport);
uint16_t mscd_open            (uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len);
bool     mscd_control_xfer_cb (uint8_t rhport, uint8_t stage, tusb_control_request_t const * p_request);
bool     mscd_xfer_cb         (uint8_t rhport, uint8_t ep_addr, xfer_result_t event, uint32_t xferred_bytes);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_MSC_DEVICE_H_ */

