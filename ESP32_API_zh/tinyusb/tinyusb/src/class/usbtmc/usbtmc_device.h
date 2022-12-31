/*
 * usbtmc_设备.h
 *
 *  创建日期：2019年9月10日作者：康纳德
 */
/*
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019 N Conrad
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */


#ifndef CLASS_USBTMC_USBTMC_DEVICE_H_
#define CLASS_USBTMC_USBTMC_DEVICE_H_

#include "usbtmc.h"

// 默认情况下启用488模式
#if !defined(CFG_TUD_USBTMC_ENABLE_488)
#define CFG_TUD_USBTMC_ENABLE_488 (1)
#endif

// USB规范规定全速率必须为8、16、32或64。
// 然而，此驱动程序实现要求它大于=32
#define USBTMCD_MAX_PACKET_SIZE (64u)

/***********************************************
 *  类实现要实现的函数
 */

// 为了继续，应用程序必须在以下期间或之后调用调用tud_usbtmc_start_bus_read（rhport）：
// *开放式数据库
// *研究_任务_消息_数据_ cb
// *tud_usbtmc_msgBulkIn_complete_cb
// *tudi_usbtmc_msg_trigger_cb
// *（成功）tud_usbtmc_check_abort_bulk_out_cb
// *（成功）tud_usbtmc_check_abort_bulk_in_cb
// *（成功）tud_usmtmc_bulkOut_clearFeature_cb

#if (CFG_TUD_USBTMC_ENABLE_488)
usbtmc_response_capabilities_488_t const * tud_usbtmc_get_capabilities_cb(void);
#else
usbtmc_response_capabilities_t const * tud_usbtmc_get_capabilities_cb(void);
#endif

void tud_usbtmc_open_cb(uint8_t interface_id);

bool tud_usbtmc_msgBulkOut_start_cb(usbtmc_msg_request_dev_dep_out const * msgHeader);
// transfer_complete并不意味着消息已完成。
bool tud_usbtmc_msg_data_cb( void *data, size_t len, bool transfer_complete);
void tud_usbtmc_bulkOut_clearFeature_cb(void); // 通知清除并中止待定的批量输出传输

bool tud_usbtmc_msgBulkIn_request_cb(usbtmc_msg_request_dev_dep_in const * request);
bool tud_usbtmc_msgBulkIn_complete_cb(void);
void tud_usbtmc_bulkIn_clearFeature_cb(void); // 通知清除并中止待定的批量输出传输

bool tud_usbtmc_initiate_abort_bulk_in_cb(uint8_t *tmcResult);
bool tud_usbtmc_initiate_abort_bulk_out_cb(uint8_t *tmcResult);
bool tud_usbtmc_initiate_clear_cb(uint8_t *tmcResult);

bool tud_usbtmc_check_abort_bulk_in_cb(usbtmc_check_abort_bulk_rsp_t *rsp);
bool tud_usbtmc_check_abort_bulk_out_cb(usbtmc_check_abort_bulk_rsp_t *rsp);
bool tud_usbtmc_check_clear_cb(usbtmc_get_clear_status_rsp_t *rsp);

// 指示器脉冲应为0.5至1.0秒
TU_ATTR_WEAK bool tud_usbtmc_indicator_pulse_cb(tusb_control_request_t const * msg, uint8_t *tmcResult);

#if (CFG_TUD_USBTMC_ENABLE_488)
uint8_t tud_usbtmc_get_stb_cb(uint8_t *tmcResult);
TU_ATTR_WEAK bool tud_usbtmc_msg_trigger_cb(usbtmc_msg_generic_t* msg);
//TU_ATTR_WEAK布尔tud_usbtmc_app_go_to_local_cb（）；
#endif

/*******************************************
 * 从应用调用
 *
 * 我们保留对缓冲区的引用，因此在通知应用程序传输完成之前，它不得更改。
 ******************************************/

bool tud_usbtmc_transmit_dev_msg_data(
    const void * data, size_t len,
    bool endOfMessage, bool usingTermChar);

bool tud_usbtmc_start_bus_read(void);


/* 来自USB设备核心的“回调”*/

uint16_t usbtmcd_open_cb(uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len);
void     usbtmcd_reset_cb(uint8_t rhport);
bool     usbtmcd_xfer_cb(uint8_t rhport, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes);
bool     usbtmcd_control_xfer_cb(uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);
void     usbtmcd_init_cb(void);

/************************************************************
 * USBTMC描述符模板
 *************************************************************/


#endif /* CLASS_USBTMC_USBTMC_DEVICE_H_ */

