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

/** \ingroup Group_HCD @{ \defgroup OHCI \简要OHCI驱动程序。除非另有说明，此处提及的所有文件来源（如第3.5节）均指OHCI规范
 *  @{ */

#ifndef _TUSB_OHCI_H_
#define _TUSB_OHCI_H_

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// OHCI CONFIGURATION & CONSTANTS
//--------------------------------------------------------------------+
#define HOST_HCD_XFER_INTERRUPT // TODO中断使用广泛，应始终予以处罚
#define OHCI_PERIODIC_LIST (defined HOST_HCD_XFER_INTERRUPT || defined HOST_HCD_XFER_ISOCHRONOUS)

// TODO将OHCI与EHCI合并
enum {
  OHCI_MAX_ITD = 4
};

enum {
  OHCI_PID_SETUP = 0,
  OHCI_PID_OUT,
  OHCI_PID_IN,
};

//--------------------------------------------------------------------+
// OHCI数据结构
//--------------------------------------------------------------------+
typedef struct {
  uint32_t interrupt_table[32];
  volatile uint16_t frame_number;
  volatile uint16_t frame_pad;
  volatile uint32_t done_head;
  uint8_t reserved[116+4];  // 如果可能，TODO尝试使用此区域，额外的4字节使整个结构大小=256
}ohci_hcca_t; // TU_ATTR_ALIGNED(256)

TU_VERIFY_STATIC( sizeof(ohci_hcca_t) == 256, "size is not correct" );

typedef struct {
  uint32_t reserved[2];
  volatile uint32_t next;
  uint32_t reserved2;
}ohci_td_item_t;


typedef struct TU_ATTR_ALIGNED(16)
{
	// 单词0
	uint32_t used                    : 1;
	uint32_t index                   : 4;  // td所属的端点索引，或控制xfer时的设备地址
  uint32_t expected_bytes          : 13; // 可用于hcd的TODO

  uint32_t buffer_rounding         : 1;
  uint32_t pid                     : 2;
  uint32_t delay_interrupt         : 3;
  volatile uint32_t data_toggle    : 2;
  volatile uint32_t error_count    : 2;
  volatile uint32_t condition_code : 4;

	// 单词1
	volatile uint8_t* current_buffer_pointer;

	// 单词2：下一个TD
	volatile uint32_t next;

	// 单词3
	uint8_t* buffer_end;
} ohci_gtd_t;

TU_VERIFY_STATIC( sizeof(ohci_gtd_t) == 16, "size is not correct" );

typedef struct TU_ATTR_ALIGNED(16)
{
  // 单词0
	uint32_t dev_addr          : 7;
	uint32_t ep_number         : 4;
	uint32_t pid               : 2; // 来自TD的00b，01b输出，10b输入
	uint32_t speed             : 1;
	uint32_t skip              : 1;
	uint32_t is_iso            : 1;
	uint32_t max_packet_size   : 11;
	      // HCD：使用5个保留位
	uint32_t used              : 1;
	uint32_t is_interrupt_xfer : 1;
	uint32_t is_stalled        : 1;
	uint32_t                   : 2;

	// 单词1
	uint32_t td_tail;

	// 单词2
	volatile union {
		uint32_t address;
		struct {
			uint32_t halted : 1;
			uint32_t toggle : 1;
			uint32_t : 30;
		};
	}td_head;

	// 单词3：下一个ED
	uint32_t next;
} ohci_ed_t;

TU_VERIFY_STATIC( sizeof(ohci_ed_t) == 16, "size is not correct" );

typedef struct TU_ATTR_ALIGNED(32)
{
	/*----------单词1----------*/
  uint32_t starting_frame          : 16;
  uint32_t                         : 5; // 可以使用
  uint32_t delay_interrupt         : 3;
  uint32_t frame_count             : 3;
  uint32_t                         : 1; // 可以使用
  volatile uint32_t condition_code : 4;

	/*----------单词2----------*/
	uint32_t buffer_page0;	// 可以使用12个lsb位

	/*----------单词3----------*/
	volatile uint32_t next;

	/*----------单词4----------*/
	uint32_t buffer_end;

	/*----------单词5-8----------*/
	volatile uint16_t offset_packetstatus[8];
} ochi_itd_t;

TU_VERIFY_STATIC( sizeof(ochi_itd_t) == 32, "size is not correct" );

// 构件对齐要求从大到小的结构
typedef struct TU_ATTR_ALIGNED(256)
{
  ohci_hcca_t hcca;

  ohci_ed_t bulk_head_ed; // 静态大头（假人）
  ohci_ed_t period_head_ed; // 静态周期列表头（虚拟）

  // 控制终结点具有保留的资源
  struct {
    ohci_ed_t ed;
    ohci_gtd_t gtd;
  }control[CFG_TUSB_HOST_DEVICE_MAX+1];

  //  ochi_id_titd[OHCI_MAX_itd]；//itd要求对齐32
  ohci_ed_t ed_pool[HCD_MAX_ENDPOINT];
  ohci_gtd_t gtd_pool[HCD_MAX_XFER];

  volatile uint16_t frame_number_hi;

} ohci_data_t;

//--------------------------------------------------------------------+
// OHCI操作寄存器
//--------------------------------------------------------------------+


//--------------------------------------------------------------------+
// OHCI数据组织
//--------------------------------------------------------------------+
typedef volatile struct
{
  uint32_t revision;

  union {
    uint32_t control;
    struct {
      uint32_t control_bulk_service_ratio : 2;
      uint32_t periodic_list_enable       : 1;
      uint32_t isochronous_enable         : 1;
      uint32_t control_list_enable        : 1;
      uint32_t bulk_list_enable           : 1;
      uint32_t hc_functional_state        : 2;
      uint32_t interrupt_routing          : 1;
      uint32_t remote_wakeup_connected    : 1;
      uint32_t remote_wakeup_enale        : 1;
      uint32_t TU_RESERVED                : 21;
    }control_bit;
  };

  union {
    uint32_t command_status;
    struct {
      uint32_t controller_reset         : 1;
      uint32_t control_list_filled      : 1;
      uint32_t bulk_list_filled         : 1;
      uint32_t ownership_change_request : 1;
      uint32_t                          : 12;
      uint32_t scheduling_overrun_count : 2;
    }command_status_bit;
  };

  uint32_t interrupt_status;
  uint32_t interrupt_enable;
  uint32_t interrupt_disable;

  uint32_t hcca;
  uint32_t period_current_ed;
  uint32_t control_head_ed;
  uint32_t control_current_ed;
  uint32_t bulk_head_ed;
  uint32_t bulk_current_ed;
  uint32_t done_head;

  uint32_t frame_interval;
  uint32_t frame_remaining;
  uint32_t frame_number;
  uint32_t periodic_start;
  uint32_t lowspeed_threshold;

  uint32_t rh_descriptorA;
  uint32_t rh_descriptorB;

  union {
    uint32_t rh_status;
    struct {
      uint32_t local_power_status            : 1; // 读取本地电源状态；写：清除全球力量
      uint32_t over_current_indicator        : 1;
      uint32_t                               : 13;
      uint32_t device_remote_wakeup_enable   : 1;
      uint32_t local_power_status_change     : 1;
      uint32_t over_current_indicator_change : 1;
      uint32_t                               : 13;
      uint32_t clear_remote_wakeup_enable    : 1;
    }rh_status_bit;
  };

  union {
    uint32_t rhport_status[2]; // TODO NXP OHCI控制器只有2个端口
    struct {
      uint32_t current_connect_status             : 1;
      uint32_t port_enable_status                 : 1;
      uint32_t port_suspend_status                : 1;
      uint32_t port_over_current_indicator        : 1;
      uint32_t port_reset_status                  : 1;
      uint32_t                                    : 3;
      uint32_t port_power_status                  : 1;
      uint32_t low_speed_device_attached          : 1;
      uint32_t                                    : 6;
      uint32_t connect_status_change              : 1;
      uint32_t port_enable_status_change          : 1;
      uint32_t port_suspend_status_change         : 1;
      uint32_t port_over_current_indicator_change : 1;
      uint32_t port_reset_status_change           : 1;
      uint32_t TU_RESERVED                        : 11;
    }rhport_status_bit[2];
  };
}ohci_registers_t;

TU_VERIFY_STATIC( sizeof(ohci_registers_t) == 0x5c, "size is not correct");

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_OHCI_H_ */

/** @} */
/** @} */

