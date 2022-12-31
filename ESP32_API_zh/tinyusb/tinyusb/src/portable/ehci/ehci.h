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

/** \ingroup Group_HCD @{ \defgroup EHCI \简要EHCI驱动程序。除非另有说明，此处提及的所有文件来源（如第3.5节）均指EHCI规范
 *  @{ */

#ifndef _TUSB_EHCI_H_
#define _TUSB_EHCI_H_


/* 缩写HC：主机控制器HCD：主机控制器驱动程序QHD：非ISO传输的队列头QTD：非ISO转换的队列传输描述符ITD：高速的ISO传输描述符SITD：全速的拆分ISO传输描述符SMASK：滑动事务的开始拆分掩码CMASK：滑动交易的完整拆分掩码
*/

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// EHCI CONFIGURATION & CONSTANTS
//--------------------------------------------------------------------+
#define	EHCI_CFG_FRAMELIST_SIZE_BITS		7			///帧列表大小（NXP特定）（0:1024）-（1:512）-（2:256）-（3:128）-（4:64）-（5:32）-（6:16）-（7:8）
#define EHCI_FRAMELIST_SIZE             (1024 >> EHCI_CFG_FRAMELIST_SIZE_BITS)

// TODO将OHCI与EHCI合并
enum {
  EHCI_MAX_ITD  = 4,
  EHCI_MAX_SITD = 16
};

//-------------验证-------------//
TU_VERIFY_STATIC(EHCI_CFG_FRAMELIST_SIZE_BITS <= 7, "incorrect value");

//--------------------------------------------------------------------+
// EHCI数据结构
//--------------------------------------------------------------------+
enum
{
  EHCI_QTYPE_ITD = 0 ,
  EHCI_QTYPE_QHD     ,
  EHCI_QTYPE_SITD    ,
  EHCI_QTYPE_FSTN
};

/// EHCI PID
enum
{
  EHCI_PID_OUT = 0 ,
  EHCI_PID_IN      ,
  EHCI_PID_SETUP
};

///链接指针
typedef union {
	uint32_t address;
	struct  {
		uint32_t terminate : 1;
		uint32_t type      : 2;
	};
}ehci_link_t;

///队列元素传输描述符
///Qtd用于声明ehci_qhd_t中的覆盖层->不能用TU_ATTR_ALIGNED（32）声明
typedef struct
{
	// 字0：下一个QTD指针
	ehci_link_t next;

	// 单词1：备用下一个QTD指针（未使用）
	union{
	  ehci_link_t alternate;
	  struct {
	    uint32_t                : 5;
	    uint32_t used           : 1;
	    uint32_t                : 10;
	    uint32_t expected_bytes : 16;
	  };
	};

	// 单词2:qTQ令牌
	volatile uint32_t ping_err             : 1  ; ///<对于高速：0输出，1 Ping。满/慢用作错误指示器
	volatile uint32_t non_hs_split_state   : 1  ; ///<HC用于跟踪滑动交易状态
	volatile uint32_t non_hs_missed_uframe : 1  ; ///<HC错过了完整的滑移交易
	volatile uint32_t xact_err             : 1  ; ///<错误（超时、CRC、错误PID…）
	volatile uint32_t babble_err           : 1  ; ///<检测到巴贝尔，也将停止位设置为1
	volatile uint32_t buffer_err           : 1  ; ///<数据超限/欠载错误
	volatile uint32_t halted               : 1  ; ///<收到严重错误或STALL
	volatile uint32_t active               : 1  ; ///<开始传输，完成后由HC清除

	uint32_t pid                           : 2  ; ///<0:OUT，1:IN，2设置
	volatile uint32_t err_count            : 2  ; ///<连续错误的错误计数器
	volatile uint32_t current_page         : 3  ; ///<索引到qTD缓冲区指针列表
	uint32_t int_on_complete               : 1  ; ///<完成时中断
	volatile uint32_t total_bytes          : 15 ; ///<传输字节，在事务期间减少
	volatile uint32_t data_toggle          : 1  ; ///<Data Toogle位


	///缓冲页指针列表，列表中的每个元素都是4K页对齐的物理内存地址。由于每个内存指针必须引用4K页的开头，因此每个指针中的低12位都是保留的（第一位除外）
	uint32_t buffer[5];
} ehci_qtd_t;

TU_VERIFY_STATIC( sizeof(ehci_qtd_t) == 32, "size is not correct" );

///队列标头
typedef struct TU_ATTR_ALIGNED(32)
{
  // 单词0：下一个QHD
	ehci_link_t next;

	// 单词1：端点特征
	uint32_t dev_addr              : 7  ; ///<设备地址
	uint32_t fl_inactive_next_xact : 1  ; ///<仅适用于周期性全速/慢速
	uint32_t ep_number             : 4  ; ///<EP编号
	uint32_t ep_speed              : 2  ; ///<0:满，1:低，2:高
	uint32_t data_toggle_control   : 1  ; ///<0：在qHD中使用DT，1：在qTD中使用DT
	uint32_t head_list_flag        : 1  ; ///<队列负责人
	uint32_t max_packet_size       : 11 ; ///<最大数据包大小
	uint32_t fl_ctrl_ep_flag       : 1  ; ///<1，如果是全速/低速控制终点
	uint32_t nak_reload            : 4  ; ///<HC使用

	// 单词2：端点功能
	uint32_t int_smask             : 8  ; ///<中断计划掩码
	uint32_t fl_int_cmask          : 8  ; ///<全速/慢速拆分完成掩码
	uint32_t fl_hub_addr           : 7  ; ///<全速/低速的集线器地址
	uint32_t fl_hub_port           : 7  ; ///<全速/低速的集线器端口
	uint32_t mult                  : 2  ; ///<每个微帧的事务

	// 字3：当前qTD指针
	volatile uint32_t qtd_addr;

	// 单词4-11：传输覆盖
	volatile ehci_qtd_t qtd_overlay;

	//--------------------------------------------------------------------+
  ///由于QHD是32字节对齐的，但仅占用48字节
	///因此，我们可以使用16个字节的空闲填充。
  //--------------------------------------------------------------------+
	uint8_t used;
	uint8_t removing; // 从异步列表中删除，等待异步前进
	uint8_t pid;
	uint8_t interval_ms; // 轮询间隔（以帧为单位）（或毫秒）

	uint16_t total_xferred_bytes; // 设置了ioc位的qtd之前xferred的字节数
	uint8_t reserved2[2];

	ehci_qtd_t * volatile p_qtd_list_head;	// 计划TD列表的标题
	ehci_qtd_t * volatile p_qtd_list_tail;	// 计划TD列表的尾部
} ehci_qhd_t;

TU_VERIFY_STATIC( sizeof(ehci_qhd_t) == 64, "size is not correct" );

///高速等时传输描述符（第3.3节）
typedef struct TU_ATTR_ALIGNED(32) {
	// 单词0:下一个链接指针
	ehci_link_t next;

	// 单词1-8:iTD事务状态和控制列表
	struct  {
	  // iTD控制
		volatile uint32_t offset          : 12 ; ///<此字段是一个值，它是从缓冲区开始的偏移量，以字节表示。
		volatile uint32_t page_select     : 3  ; ///<这些位由软件设置，以指示该时隙中的偏移字段应连接到哪个缓冲页指针，以产生该事务的起始存储器地址。此字段的有效值范围为0到6
             uint32_t int_on_complete : 1  ; ///<如果该位设置为1，则指定当该事务完成时，主机控制器应在下一个中断阈值发出中断
		volatile uint32_t length          : 12 ; ///<对于OUT，此字段是主机控制器在事务期间将发送的数据字节数。主机控制器无需更新此字段以反映传输过程中传输的实际字节数
																						 ///<对于IN，字段的初始值是主机希望端点传递的字节数。在状态更新期间，主机控制器写回成功接收的字节数。此寄存器中的值是实际字节计数
		// iTD状态
		volatile uint32_t error           : 1  ; ///<如果主机未收到设备的有效响应（超时、CRC、错误PID等），则在状态更新期间由主机控制器设置为1。此位只能为同步IN事务设置。
		volatile uint32_t babble_err      : 1  ; ///<在事务期间检测到咿呀声时，在状态更新期间由主机控制器设置为1
		volatile uint32_t buffer_err      : 1  ; ///<在状态更新期间由主机控制器设置为1，以指示主机控制器无法跟上传入数据的接收（超限）或无法在传输期间足够快地提供数据（欠载）。
		volatile uint32_t active          : 1  ; ///<通过软件设置为1，以允许主机控制器执行同步事务
	} xact[8];

	// 字9-15缓冲页指针列表（加号）
	uint32_t BufferPointer[7];

////FIXME：将元数据存储到为保存内存而保留的缓冲区指针中
//	/*----------HCD区域----------*/
//使用uint32_t；
//uint32_t IhdIdx；
//uint32_t保留[6]；
} ehci_itd_t;

TU_VERIFY_STATIC( sizeof(ehci_itd_t) == 64, "size is not correct" );

///分离（全速）等时传输描述符
typedef struct TU_ATTR_ALIGNED(32)
{
  // 单词0:下一个链接指针
	ehci_link_t next;

	// 单词1:siTD端点特征
	uint32_t dev_addr    : 7; ///<此字段选择用作数据源或接收器的特定设备。
	uint32_t             : 1; ///<保留
	uint32_t ep_number   : 4; ///<此4位字段选择用作数据源或接收器的设备上的特定端点编号。
	uint32_t             : 4; ///<此字段为保留字段，应设置为零。
	uint32_t hub_addr    : 7; ///<此字段保存事务转换器集线器的设备地址。
	uint32_t             : 1; ///<保留
	uint32_t port_number : 7; ///<此字段是收件人事务转换器的端口号。
	uint32_t direction   : 1; ///<0=OUT；1=英寸。该字段编码全速事务应该是IN还是OUT。

	// 字2：微框架进度控制
	uint8_t int_smask   ; ///<此字段（连同Statusbyte中的Active和SplitX状态字段）用于确定主机控制器应在哪些微帧期间执行完整的拆分事务
	uint8_t fl_int_cmask; ///<此字段（以及Statusbyte中的Active和SplitX状态字段）用于确定主机控制器应在哪些微帧期间执行开始拆分事务。
	uint16_t reserved ; ///<保留

	// 字3:siTD传输状态和控制
	// 状态[7:0]TODO标识到qTD令牌的状态-->折射器
	volatile uint32_t                 : 1  ; // 保留
	volatile uint32_t split_state     : 1  ;
	volatile uint32_t missed_uframe   : 1  ;
	volatile uint32_t xact_err        : 1  ;
	volatile uint32_t babble_err      : 1  ;
	volatile uint32_t buffer_err      : 1  ;
	volatile uint32_t error           : 1  ;
	volatile uint32_t active          : 1  ;
	// 微框架进度控制
	volatile uint32_t cmask_progress  : 8  ; ///<此字段由主机控制器用于记录已执行的拆分完成。行为要求见第4.12.3.3.2节。
	volatile uint32_t total_bytes     : 10 ; ///<此字段由软件初始化为此传输中预期的总字节数。最大值为1023
	volatile uint32_t                 : 4  ; ///<保留
	volatile uint32_t page_select     : 1  ; ///<用于指示应将哪个数据页指针与CurrentOffsetfield连接以构造数据缓冲区指针
					 uint32_t int_on_complete : 1  ; ///<交易完成时不要中断。1=事务完成时执行中断
					 uint32_t                 : 0  ; // 填充到当前存储单元的末尾

	///字4-5：缓冲区指针列表
	uint32_t buffer[2];		// buffer[1]TP:事务位置-T-Count:事务计数

// 联合，联合{
// uint32_t缓冲指针1；
// 结构{
// volatile uint32_t TCount:3；
// 挥发性uint32_t位置：2；
// 		};
// 	};

	/*----------单词6----------*/
	ehci_link_t back;

	///SITD是32字节对齐的，但仅占用28-->4字节用于存储额外数据
	uint8_t used;
	uint8_t ihd_idx;
	uint8_t reserved2[2];
} ehci_sitd_t;

TU_VERIFY_STATIC( sizeof(ehci_sitd_t) == 32, "size is not correct" );

//--------------------------------------------------------------------+
// EHCI操作寄存器
//--------------------------------------------------------------------+
enum ehci_interrupt_mask_{
  EHCI_INT_MASK_USB                   = TU_BIT(0),
  EHCI_INT_MASK_ERROR                 = TU_BIT(1),
  EHCI_INT_MASK_PORT_CHANGE           = TU_BIT(2),

  EHCI_INT_MASK_FRAMELIST_ROLLOVER    = TU_BIT(3),
  EHCI_INT_MASK_PCI_HOST_SYSTEM_ERROR = TU_BIT(4),
  EHCI_INT_MASK_ASYNC_ADVANCE         = TU_BIT(5),
  EHCI_INT_MASK_NXP_SOF               = TU_BIT(7),

  EHCI_INT_MASK_NXP_ASYNC             = TU_BIT(18),
  EHCI_INT_MASK_NXP_PERIODIC          = TU_BIT(19),

  EHCI_INT_MASK_ALL                   =
      EHCI_INT_MASK_USB | EHCI_INT_MASK_ERROR | EHCI_INT_MASK_PORT_CHANGE |
      EHCI_INT_MASK_FRAMELIST_ROLLOVER | EHCI_INT_MASK_PCI_HOST_SYSTEM_ERROR |
      EHCI_INT_MASK_ASYNC_ADVANCE | EHCI_INT_MASK_NXP_SOF |
      EHCI_INT_MASK_NXP_ASYNC | EHCI_INT_MASK_NXP_PERIODIC
};

enum ehci_usbcmd_pos_ {
  EHCI_USBCMD_POS_RUN_STOP               = 0,
  EHCI_USBCMD_POS_FRAMELIST_SZIE         = 2,
  EHCI_USBCMD_POS_PERIOD_ENABLE          = 4,
  EHCI_USBCMD_POS_ASYNC_ENABLE           = 5,
  EHCI_USBCMD_POS_NXP_FRAMELIST_SIZE_MSB = 15,
  EHCI_USBCMD_POS_INTERRUPT_THRESHOLD    = 16
};

enum ehci_portsc_change_mask_{
  EHCI_PORTSC_MASK_CURRENT_CONNECT_STATUS = TU_BIT(0),
  EHCI_PORTSC_MASK_CONNECT_STATUS_CHANGE = TU_BIT(1),
  EHCI_PORTSC_MASK_PORT_EANBLED = TU_BIT(2),
  EHCI_PORTSC_MASK_PORT_ENABLE_CHAGNE = TU_BIT(3),
  EHCI_PORTSC_MASK_OVER_CURRENT_CHANGE = TU_BIT(5),

  EHCI_PORTSC_MASK_PORT_RESET = TU_BIT(8),

  EHCI_PORTSC_MASK_ALL =
      EHCI_PORTSC_MASK_CONNECT_STATUS_CHANGE |
      EHCI_PORTSC_MASK_PORT_ENABLE_CHAGNE |
      EHCI_PORTSC_MASK_OVER_CURRENT_CHANGE
};

typedef volatile struct
{
  union {
    uint32_t command;

    struct {
      uint32_t run_stop               : 1 ; ///<1=运行。0=停止
      uint32_t reset                  : 1 ; ///<SW写入1以重置HC，完成后由HC清除
      uint32_t framelist_size         : 2 ; ///<帧列表大小0:1024，1:512，2:256
      uint32_t periodic_enable        : 1 ; ///<此位控制主机控制器是否跳过周期计划的处理。值表示：0b不处理定期计划1b使用PERIODICLISTBASE寄存器访问定期计划。
      uint32_t async_enable           : 1 ; ///<此位控制主机控制器是否跳过处理异步调度。值表示：0b不处理异步调度1b使用ASYNCLISTADDR寄存器访问异步调度。
      uint32_t async_adv_doorbell     : 1 ; ///<告诉HC下次推进异步列表时中断。HC清除
      uint32_t light_reset            : 1 ; ///<重置HC而不影响端口状态
      uint32_t async_park_count       : 2 ; ///<tinyusb未使用
      uint32_t                        : 1 ;
      uint32_t async_park_enable      : 1 ; ///<启用驻车模式，tinyusb未使用
      uint32_t                        : 3 ;
      uint32_t nxp_framelist_size_msb : 1 ; ///<NXP自定义：帧列表大小位的第2位\n 011b:128个元素\n 100b:64个元素\n 101b:32个元素\n 110b:16个元素\n 111b:8个元素
      uint32_t int_threshold          : 8 ; ///<默认值08h。以微帧为单位的中断率
    }command_bm;
  };

  union {
    uint32_t status;

    struct {
      uint32_t usb                   : 1  ; ///国际奥委会的<qTD已退役
      uint32_t usb_error             : 1  ; ///<qTD因错误而失效
      uint32_t port_change_detect    : 1  ; ///<当PortOwner或ForcePortResume从0更改时设置->1
      uint32_t framelist_rollover    : 1  ; ///<R/WC当帧列表索引（参见第2.3.4节）从其最大值翻转到零时，主机控制器将此位设置为1。滚动发生的确切值取决于帧列表大小。例如，如果帧列表大小（如在USBCMD寄存器的帧列表大小字段中编程的）为1024，则每当FRINDEX[13]切换时，帧索引寄存器都会进行循环。类似地，如果大小为512，则每当FRINDEX[12]切换时，主机控制器都会将此位设置为1。
      uint32_t pci_host_system_error : 1  ; ///<R/WC（NXP未使用）当涉及主机控制器模块的主机系统访问期间发生严重错误时，主机控制器将此位设置为1。在PCI系统中，将此位设置为1的条件包括PCI奇偶校验错误、PCI主中止和PCI目标中止。发生此错误时，主机控制器清除命令寄存器中的运行/停止位，以防止进一步执行调度的TD。
      uint32_t async_adv             : 1  ; ///<异步提前中断
      uint32_t                       : 1  ;
      uint32_t nxp_int_sof           : 1  ; ///<NXP自定义：此位将每125us设置一次，可由主机控制器驱动程序用作时基。
      uint32_t                       : 4  ;
      uint32_t hc_halted             : 1  ; ///<run_stop位的相反值。
      uint32_t reclamation           : 1  ; ///<用于检测空异步会话
      uint32_t periodic_status       : 1  ; ///<定期计划状态
      uint32_t async_status          : 1  ; ///<异步计划状态
      uint32_t                       : 2  ;
      uint32_t nxp_int_async         : 1  ; ///<NXP自定义：当中断的原因是USB事务的完成时，该位由主机控制器设置，其中传输描述符（TD）设置了中断完成（IOC）位，并且TD来自异步调度。当检测到短数据包且数据包处于异步调度时，主机也会设置该位。
      uint32_t nxp_int_period        : 1  ; ///<NXP自定义：当中断的原因是USB事务的完成，其中传输描述符（TD）设置了完成时中断（IOC）位，并且TD来自定期计划时，主机控制器会设置该位。
      uint32_t                       : 12 ;
    }status_bm;
  };

  union{
    uint32_t inten;

    struct {
      uint32_t usb                   : 1  ;
      uint32_t usb_error             : 1  ;
      uint32_t port_change_detect    : 1  ;
      uint32_t framelist_rollover    : 1  ;
      uint32_t pci_host_system_error : 1  ;
      uint32_t async_adv             : 1  ;
      uint32_t                       : 1  ;
      uint32_t nxp_int_sof           : 1  ;
      uint32_t                       : 10 ;
      uint32_t nxp_int_async         : 1  ;
      uint32_t nxp_int_period        : 1  ;
      uint32_t                       : 12 ;
    }inten_bm;
  };

  uint32_t frame_index        ; ///<微帧计数器
  uint32_t ctrl_ds_seg        ; ///<控制数据结构段
  uint32_t periodic_list_base ; ///<周期帧列表的起始地址
  uint32_t async_list_addr    ; ///<要执行的下一个异步QHD的地址
  uint32_t nxp_tt_control     ; ///<nxp嵌入式事务转换器（由EHCI规范保留）
  uint32_t reserved[8]        ;
  uint32_t config_flag        ; ///<恩智浦未使用

  union {
    uint32_t portsc             ; ///<端口状态和控制
    struct {
      uint32_t current_connect_status      : 1; ///<0:没有设备，1:端口上存在设备
      uint32_t connect_status_change       : 1; ///<当前连接状态的变化
      uint32_t port_enabled                : 1; ///<端口只能由HC作为重置和启用的一部分启用。软件可以写入0以禁用
      uint32_t port_enable_change          : 1; ///<端口启用已更改
      uint32_t over_current_active         : 1; ///<端口过流
      uint32_t over_current_change         : 1; ///<更改为过电流激活
      uint32_t force_port_resume           : 1; ///<在端口上检测到/驱动恢复。为操作此位而定义的此功能取决于Suspend位的值。
      uint32_t suspend                     : 1; ///<端口处于挂起状态
      uint32_t port_reset                  : 1; ///<1=端口处于重置状态。0=端口未处于重置状态
      uint32_t nxp_highspeed_status        : 1; ///<NXP自定义：0=连接到端口未处于高速模式，1=连接到该端口处于高速模式
      uint32_t line_status                 : 2; ///<D+/D-状态：00:SE0，10:J状态，01:K状态
      uint32_t port_power                  : 1; ///<0=断电，1=通电
      uint32_t port_owner                  : 1; ///<恩智浦未使用
      uint32_t port_indicator_control      : 2; ///＜00b：关闭，01b：琥珀色，10b：绿色，11b：未定义
      uint32_t port_test_control           : 4; ///<端口测试模式，tinyusb未使用
      uint32_t wake_on_connect_enable      : 1; ///<启用设备连接作为唤醒事件
      uint32_t wake_on_disconnect_enable   : 1; ///<启用设备断开连接作为唤醒事件
      uint32_t wake_on_over_current_enable : 1; ///<启用过电流条件作为唤醒事件
      uint32_t nxp_phy_clock_disable       : 1; ///<NXP定制：当下游设备已进入挂起模式或未连接下游设备时，PHY可以进入低功耗挂起–时钟禁用。低功耗暂停完全由软件控制。0：启用PHY时钟，1：禁用PHY时钟
      uint32_t nxp_port_force_fullspeed    : 1; ///<NXP自定义：将此位写入1将强制端口仅以全速连接。它禁用允许端口将自己标识为高速的啁啾序列。这对于使用HS主机、集线器或设备测试FS配置非常有用。
      uint32_t                             : 1;
      uint32_t nxp_port_speed              : 2; ///<NXP自定义：此寄存器字段指示端口运行的速度。对于主机控制器中的HS模式操作和设备控制器中的HS/FS操作，端口路由将数据引导到协议引擎。对于主机控制器中的FS和LS模式操作，端口路由将数据导向带有嵌入式事务转换器的协议引擎。0x0：全速，0x1：低速，0x2：高速
      uint32_t TU_RESERVED                 : 4;
    }portsc_bm;
  };
}ehci_registers_t;

//--------------------------------------------------------------------+
// EHCI数据组织
//--------------------------------------------------------------------+
typedef struct
{
  ehci_link_t period_framelist[EHCI_FRAMELIST_SIZE];

  // 对于NXP ECHI，仅实现1毫秒、2毫秒和4毫秒、8毫秒（帧列表）
  // [0]:1ms，[1]:2ms，[2]:4ms，[3]:8ms
  ehci_qhd_t period_head_arr[4];

  // dev0的注释控件qhd用作异步列表的头
  struct {
    ehci_qhd_t qhd;
    ehci_qtd_t qtd;
  }control[CFG_TUSB_HOST_DEVICE_MAX+1];

  ehci_qhd_t qhd_pool[HCD_MAX_ENDPOINT];
  ehci_qtd_t qtd_pool[HCD_MAX_XFER] TU_ATTR_ALIGNED(32);

  ehci_registers_t* regs;

  volatile uint32_t uframe_number;
}ehci_data_t;

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_EHCI_H_ */

/** @} */
/** @} */

