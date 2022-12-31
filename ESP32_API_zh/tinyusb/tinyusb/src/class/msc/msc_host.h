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

#ifndef _TUSB_MSC_HOST_H_
#define _TUSB_MSC_HOST_H_

#include "common/tusb_common.h"
#include "host/usbh.h"
#include "msc.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 类驱动程序配置
//--------------------------------------------------------------------+

#ifndef CFG_TUH_MSC_MAXLUN
#define CFG_TUH_MSC_MAXLUN  4
#endif


/** \addtogroup ClassDriver_MSC @{ \defgroup MSC_Host Host接口API包括状态检查功能、数据传输功能和回调功能
 *  @{ */

typedef bool (*tuh_msc_complete_cb_t)(uint8_t dev_addr, msc_cbw_t const* cbw, msc_csw_t const* csw);

//--------------------------------------------------------------------+
// 应用程序API
//--------------------------------------------------------------------+

// 检查设备是否支持MassStorage接口。
// 此函数在tuh_msc_mounted_cb（）之后为true，在tuh_msc_unmounted_cb）之后为false
bool tuh_msc_mounted(uint8_t dev_addr);

// 检查接口当前是否就绪或正在忙于传输数据
bool tuh_msc_ready(uint8_t dev_addr);

// 获取Max Lun
uint8_t tuh_msc_get_maxlun(uint8_t dev_addr);

// 获取块数
uint32_t tuh_msc_get_block_count(uint8_t dev_addr, uint8_t lun);

// 获取块大小（字节）
uint32_t tuh_msc_get_block_size(uint8_t dev_addr, uint8_t lun);

// 以非阻塞方式执行完整SCSI命令（cbw、data、csw）。
// SCSI操作完成时调用Complete回调。
// 如果成功，则返回true；如果已经有挂起的操作，则返回false。
bool tuh_msc_scsi_command(uint8_t dev_addr, msc_cbw_t const* cbw, void* data, tuh_msc_complete_cb_t complete_cb);

// 执行SCSI查询命令
// SCSI操作完成时调用Complete回调。
bool tuh_msc_inquiry(uint8_t dev_addr, uint8_t lun, scsi_inquiry_resp_t* response, tuh_msc_complete_cb_t complete_cb);

// 执行SCSI测试单元就绪命令
// SCSI操作完成时调用Complete回调。
bool tuh_msc_test_unit_ready(uint8_t dev_addr, uint8_t lun, tuh_msc_complete_cb_t complete_cb);

// 执行SCSI请求检测10命令
// SCSI操作完成时调用Complete回调。
bool tuh_msc_request_sense(uint8_t dev_addr, uint8_t lun, void *resposne, tuh_msc_complete_cb_t complete_cb);

// 执行SCSI Read 10命令。从LBA到缓冲区读取n个块
// SCSI操作完成时调用Complete回调。
bool  tuh_msc_read10(uint8_t dev_addr, uint8_t lun, void * buffer, uint32_t lba, uint16_t block_count, tuh_msc_complete_cb_t complete_cb);

// 执行SCSI Write 10命令。从LBA开始向设备写入n个块
// SCSI操作完成时调用Complete回调。
bool tuh_msc_write10(uint8_t dev_addr, uint8_t lun, void const * buffer, uint32_t lba, uint16_t block_count, tuh_msc_complete_cb_t complete_cb);

// 执行SCSI读取容量10命令
// SCSI操作完成时调用Complete回调。
// 注意：在枚举期间，主机堆栈已执行此请求。应用程序可以通过以下方式检索容量
// 只需调用tuh_msc_get_block_count（）和tuh-msc_get_block_size（）
bool tuh_msc_read_capacity(uint8_t dev_addr, uint8_t lun, scsi_read_capacity10_resp_t* response, tuh_msc_complete_cb_t complete_cb);

//-------------应用程序回调-------------//

// 装载具有MassStorage接口的设备时调用
void tuh_msc_mount_cb(uint8_t dev_addr);

// 在卸载具有MassStorage接口的设备时调用
void tuh_msc_unmount_cb(uint8_t dev_addr);

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+

void msch_init(void);
bool msch_open(uint8_t rhport, uint8_t dev_addr, tusb_desc_interface_t const *itf_desc, uint16_t *p_length);
bool msch_set_config(uint8_t dev_addr, uint8_t itf_num);
bool msch_xfer_cb(uint8_t dev_addr, uint8_t ep_addr, xfer_result_t event, uint32_t xferred_bytes);
void msch_close(uint8_t dev_addr);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_MSC_HOST_H_ */

/// @}
/// @}

