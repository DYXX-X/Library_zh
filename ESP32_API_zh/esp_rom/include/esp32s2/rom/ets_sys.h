// 版权所有2010-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _ROM_ETS_SYS_H_
#define _ROM_ETS_SYS_H_

#include <stdint.h>
#include <stdbool.h>

#include "soc/soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup ets_sys_apis，ets系统相关api
  * @brief ets系统api
  */

/** @addtogroup ets_sys_apis@{
  */

/************************************************************************
  *                                注：此头文件中的许多函数无法在FreeRTOS中运行。请参见函数的注释。还有一些函数没有在标题中列出就不能在FreeRTOS上工作，例如：xtos函数在ld文件中以“_xtos_”开头。
  *
  ***********************************************************************
  */

/** \defgroup ets_apis，Espressif任务调度器相关api
  * @brief ets api
  */

/** @addtogroup ets_apis公司@{
  */

typedef enum {
    ETS_OK     = 0, /**<在ets中返回成功*/
    ETS_FAILED = 1  /**<在ets中返回失败*/
} ETS_STATUS;

typedef ETS_STATUS ets_status_t;

typedef uint32_t ETSSignal;
typedef uint32_t ETSParam;

typedef struct ETSEventTag ETSEvent;    /**<事件发送/接收*/

struct ETSEventTag {
    ETSSignal sig;  /**<事件信号，在同一任务中，不同的事件具有不同的信号*/
    ETSParam  par;  /**<事件参数，有时不使用，则将设置为0*/
};

typedef void (*ETSTask)(ETSEvent *e);       /**<任务处理程序的类型*/
typedef void (* ets_idle_cb_t)(void *arg);  /**<系统空闲回调的类型*/

/**
  * @brief  启动Espressif Task Scheduler，这是一个无限循环。请不要在后面添加代码。
  *
  * @param  none
  *
  * @return 没有一个
  */
void ets_run(void);

/**
  * @brief  设置空闲回调，当处理任务时，将在CPU进入睡眠状态之前调用回调。
  *
  * @param  ets_idle_cb_t func：回调函数。
  *
  * @param  void *arg：回调的参数。
  *
  * @return 没有一个
  */
void ets_set_idle_cb(ets_idle_cb_t func, void *arg);

/**
  * @brief  使用处理器、优先级、接收事件的队列、队列长度初始化任务。
  *
  * @param  ETSTask task：任务处理程序。
  *
  * @param  uint8_t prio：任务优先级，0-31，更大的num具有高优先级，一个优先级具有一个任务。
  *
  * @param  ETSEvent *队列：队列属于任务，任务总是接收事件，队列是循环使用的。
  *
  * @param  uint8_t qlen：队列长度。
  *
  * @return 没有一个
  */
void ets_task(ETSTask task, uint8_t prio, ETSEvent *queue, uint8_t qlen);

/**
  * @brief  将事件发布到Task。
  *
  * @param  uint8_t prio：任务的优先级。
  *
  * @param  ETSSignal sig：事件信号。
  *
  * @param  ETSParam  par：事件参数
  *
  * @return ETS_OK：发布成功
  * @return ETS_FAILED:发布失败
  */
ETS_STATUS ets_post(uint8_t prio, ETSSignal sig, ETSParam par);

/**
  * @}
  */

/** \defgroup ets_boot_apis，引导路由相关api
  * @brief ets引导api
  */

/** @addtogroup ets_apis公司@{
  */

extern const char *const exc_cause_table[40];   ///**<排除由核心定义的原因。*/

/**
  * @brief  设置Pro cpu入口代码，当引导未完成时，可以在Pro cpu中调用代码。当Pro CPU引导完成时，如果不是NULL，Pro CPU将调用Entry代码。
  *
  * @param  uint32_t start：uint32_t中的PRO Entry代码地址值
  *
  * @return 没有一个
  */
void ets_set_user_start(uint32_t start);

/**
  * @brief  设置Pro cpu启动代码，可以在启动未完成时调用代码，或在Entry代码中调用代码。当输入代码完成时，如果不是NULL，CPU将调用启动代码，否则调用ets_run。
  *
  * @param  uint32_t callback：uint32_t中的启动代码地址值
  *
  * @return 无：发布成功
  */
void ets_set_startup_callback(uint32_t callback);

/**
  * @brief  设置App cpu入口代码，代码可以在PRO cpu中调用。当APP启动完成时，如果不是NULL，APP CPU将调用Entry代码。
  *
  * @param  uint32_t start：uint32_t中的APP条目代码地址值，存储在寄存器APPCPU_CTRL_REG_D中。
  *
  * @return 没有一个
  */
void ets_set_appcpu_boot_addr(uint32_t start);

/**
  * @}
  */

/** \defgroup ets_printf_api，ets中使用的ets_printf相关api
  * @brief ets printf api
  */

/** @addtogroup ets_printf_api@{
  */

/**
  * @brief  将字符串打印到uart或其他设备，类似于Printf，比Printf简单。无法打印浮点数据格式或longlong数据格式。所以我们可能只在ROM中使用这个。
  *
  * @param  const char*fmt：请参见printf。
  *
  * @param  ... ：参见printf。
  *
  * @return int：打印到输出设备的长度。
  */
int ets_printf(const char *fmt, ...);

/**
  * @brief  设置ets_printf（uart_tx_one_char）的uart通道。ROM将根据efuse和gpio设置对其进行设置，但这可以在启动后更改。
  *
  * @param  uart_no ：0代表UART0，1代表UART1，2代表UART2。
  *
  * @return 没有一个
  */
void ets_set_printf_channel(uint8_t uart_no);

/**
  * @brief 获取ets_printf（uart_tx_one_char）的uart通道。
  *
  * @return ets_printf使用的uint8_t uart通道（uart_tx_one_char）。
  */
uint8_t ets_get_printf_channel(void);

/**
  * @brief  向uart输出一个字符，要输出的uart（在ROM的uart模块中）不在函数的范围内。无法打印浮点数据格式或longlong数据格式
  *
  * @param  char c：要输出的字符。
  *
  * @return 没有一个
  */
void ets_write_char_uart(char c);

/**
  * @brief  Ets_printf有两个输出函数：putc1和putc2，如果需要输出，将调用这两个函数。要安装putc1，在非静默启动模式下默认安装为ets_write_char_uart，在静默模式下安装为NULL。
  *
  * @param  void （*）（char）p：要安装的输出函数。
  *
  * @return 没有一个
  */
void ets_install_putc1(void (*p)(char c));

/**
  * @brief  Ets_printf有两个输出函数：putc1和putc2，如果需要输出，将调用这两个函数。安装putc2，默认安装为NULL。
  *
  * @param  void （*）（char）p：要安装的输出函数。
  *
  * @return 没有一个
  */
void ets_install_putc2(void (*p)(char c));

/**
  * @brief  将putc1安装为ets_write_char_uart。在静默启动模式下（为了避免干扰UART连接的MCU），我们可以在启动ok后调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void ets_install_uart_printf(void);

#define ETS_PRINTF(...) ets_printf(...)

#define ETS_ASSERT(v) do { \
    if (!(v)) {             \
        ets_printf("%s %u \n", __FILE__, __LINE__); \
        while (1) {};   \
    }                   \
} while (0);

/**
  * @}
  */

/** \defgroup ets_timer_api，ets中使用的ets_timer相关api
  * @brief ets计时器api
  */

/** @addtogroup ets_timer_api@{
  */
typedef void ETSTimerFunc(void *timer_arg);/**<计时器处理程序*/

typedef struct _ETSTIMER_ {
    struct _ETSTIMER_    *timer_next;   /**<计时器链接器*/
    uint32_t              timer_expire; /**<计时器到期时的抽象时间*/
    uint32_t              timer_period; /**<计时器周期，0表示计时器不定期重复*/
    ETSTimerFunc         *timer_func;   /**<计时器处理程序*/
    void                 *timer_arg;    /**<计时器处理程序参数*/
} ETSTimer;

/**
  * @brief  初始化计时器，此计时器范围为640 us到429496 ms。在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  None
  *
  * @return 没有一个
  */
void ets_timer_init(void);

/**
  * @brief  在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  None
  *
  * @return 没有一个
  */
void ets_timer_deinit(void);

/**
  * @brief  装备一个ets定时器，这个定时器范围是640 us到429496 ms。在FreeRTOS中，请调用FreeRTOS api，不要调用这个api。
  *
  * @param  ETSTimer *timer：计时器结构指针。
  *
  * @param  uint32_t tmout：计时器值（以毫秒为单位），范围为1到429496。
  *
  * @param  bool repeat：计时器周期性重复。
  *
  * @return 没有一个
  */
void ets_timer_arm(ETSTimer *timer, uint32_t tmout, bool repeat);

/**
  * @brief  装备一个ets定时器，这个定时器范围是640 us到429496 ms。在FreeRTOS中，请调用FreeRTOS api，不要调用这个api。
  *
  * @param  ETSTimer *timer：计时器结构指针。
  *
  * @param  uint32_t tmout：我们的计时器值，范围为1到429496729。
  *
  * @param  bool repeat：计时器周期性重复。
  *
  * @return 没有一个
  */
void ets_timer_arm_us(ETSTimer *ptimer, uint32_t us, bool repeat);

/**
  * @brief  解除ets计时器的防护。在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  ETSTimer *timer：计时器结构指针。
  *
  * @return 没有一个
  */
void ets_timer_disarm(ETSTimer *timer);

/**
  * @brief  设置计时器回调和参数。在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  ETSTimer *timer：计时器结构指针。
  *
  * @param  ETSTimerFunc *pfunction：计时器回调。
  *
  * @param  void *parg：计时器回调参数。
  *
  * @return 没有一个
  */
void ets_timer_setfn(ETSTimer *ptimer, ETSTimerFunc *pfunction, void *parg);

/**
  * @brief  取消将计时器回调和参数设置为NULL。在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  ETSTimer *timer：计时器结构指针。
  *
  * @return 没有一个
  */
void ets_timer_done(ETSTimer *ptimer);

/**
  * @brief  CPU执行while循环一段时间。在FreeRTOS任务中，请调用FreeRTOS api。
  *
  * @param  uint32_t 我们：拖延时间。
  *
  * @return 没有一个
  */
void ets_delay_us(uint32_t us);

/**
  * @brief  将每个用户的实际CPU节拍设置为ets，以便ets_delay_us准确。当CPU频率改变时调用此函数。
  *
  * @param  uint32_t ticks_per_us：每小时CPU节拍数。
  *
  * @return 没有一个
  */
void ets_update_cpu_frequency(uint32_t ticks_per_us);

/**
  * @brief  将每个用户的实际CPU节拍设置为ets，以便ets_delay_us准确。
  *
  * @note 此函数仅设置当前CPU的节拍率。它位于ROM中，因此即使IRAM尚未初始化，深度睡眠存根也可以使用它。
  *
  * @param  uint32_t ticks_per_us：每小时CPU节拍数。
  *
  * @return 没有一个
  */
void ets_update_cpu_frequency_rom(uint32_t ticks_per_us);

/**
  * @brief  将我们每个人的实际CPU节拍获取到ets。此函数不返回每个用户的实际CPU节拍，只返回ets中的记录。它可用于检查实际CPU频率。
  *
  * @param  None
  *
  * @return uint32_t:ets中每us记录的CPU节拍数。
  */
uint32_t ets_get_cpu_frequency(void);

/**
  * @brief  获取xtal_freq值，如果值未存储在RTC_STORE5中，则存储。
  *
  * @param  None
  *
  * @return uint32_t：如果存储在efuse（非0）时钟中，则=ets_efuse_get_xtal_freq（）1000000；否则，如果efuse clock中的analog_8M=ets_get_xtal_scale（）625/16 ets_efuse_get_8M_clock（）；否则时钟=40M。
  */
uint32_t ets_get_xtal_freq(void);

/**
  * @brief  获取apb除数。xtal频率除以该值以生成APB时钟。当发生任何类型的重置时，默认值为2。
  *
  * @param  None
  *
  * @return uint32_t:1或2。
  */
uint32_t ets_get_xtal_div(void);


/**
  * @brief  修改apb除数。xtal频率被这个分频以生成APB时钟。
  *
  * @note 默认情况下，xtal频率除数为2，因为当它为1时，故障检测器无法正确停止故障。请不要在PLL激活之前将除数设置为1，而不知道您可能会引入安全风险。
  *
  * @param  div 除法器。1=x频率，2=1/2 x频率。
  */
void ets_set_xtal_div(int div);


/**
  * @brief  获取apb_freq值，如果值未存储在RTC_STORE5中，则存储。
  *
  * @param  None
  *
  * @return uint32_t：如果rtc存储值（rtc_STORE5高16位和低16位具有相同值），则从rtc寄存器读取。时钟=（REG_READ（RTC_STORE5）&0xffff）<<12；否则将ets_get_detected_xxtal_freq（）存储在中。
  */
uint32_t ets_get_apb_freq(void);

/**
  * @}
  */

/** \defgroup ets_intr_apis，ets中断配置相关api
  * @brief ets intr api
  */

/** @addtogroup ets_intr_api@{
  */

typedef void (* ets_isr_t)(void *);/**<中断处理程序类型*/

/**
  * @brief  将中断处理程序附加到CPU中断号。此函数等于_xtos_set_interrupt_handler_arg（i，func，arg）。在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  int i：CPU中断号。
  *
  * @param  ets_isr_t func：中断处理程序。
  *
  * @param  void *arg：处理程序的参数。
  *
  * @return 没有一个
  */
void ets_isr_attach(int i, ets_isr_t func, void *arg);

/**
  * @brief  屏蔽屏蔽位中显示的中断。此函数等于_xtos_ints_off（掩码）。在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  uint32_t 掩码：BIT（i）表示掩码CPU中断号i。
  *
  * @return 没有一个
  */
void ets_isr_mask(uint32_t mask);

/**
  * @brief  取消屏蔽屏蔽位中显示的中断。此函数等于_xtos_ints_on（掩码）。在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  uint32_t 掩码：BIT（i）表示掩码CPU中断号i。
  *
  * @return 没有一个
  */
void ets_isr_unmask(uint32_t unmask);

/**
  * @brief  将中断锁定到2级。此功能直接设置CPU寄存器。在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  None
  *
  * @return 没有一个
  */
void ets_intr_lock(void);

/**
  * @brief  将中断解锁至0级。此功能直接设置CPU寄存器。在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  None
  *
  * @return 没有一个
  */
void ets_intr_unlock(void);

/**
  * @brief  将中断解锁到0级，CPU将进入省电模式（等待中断）。此函数直接设置CPU寄存器。在FreeRTOS中，请调用FreeRTOS api，切勿调用此api。
  *
  * @param  None
  *
  * @return 没有一个
  */
void ets_waiti0(void);

/**
  * @brief  将CPU中断连接到硬件源。我们有4个步骤来使用中断：1.将硬件中断源连接到CPU。intr_matrix_set（0，ETS_WIFIMAC_intr_SOURCE，ETS_WMAC_INUM）；2.设置中断处理程序。xt_set_interrupt_handler（ETS_WMAC_INUM，函数，NULL）；3.启用CPU中断。xt_ints_on（1<<ETS_WMAC_INUM）；4.启用模块中的中断。
  *
  * @param  int cpu_no：中断号所属的cpu。
  *
  * @param  uint32_t model_num：中断硬件源编号，请参阅中断硬件源表。
  *
  * @param  uint32_t intr_num：中断号CPU，请参阅中断CPU使用表。
  *
  * @return 没有一个
  */
void intr_matrix_set(int cpu_no, uint32_t model_num, uint32_t intr_num);

#define _ETSTR(v) # v
#define _ETS_SET_INTLEVEL(intlevel)        ({ unsigned __tmp; \
            __asm__ __volatile__(   "rsil   %0, " _ETSTR(intlevel) "\n" \
                        : "=a" (__tmp) : : "memory" ); \
            })

#ifdef CONFIG_NONE_OS
#define ETS_INTR_LOCK() \
        ets_intr_lock()

#define ETS_INTR_UNLOCK() \
        ets_intr_unlock()

#define ETS_ISR_ATTACH \
        ets_isr_attach

#define ETS_INTR_ENABLE(inum) \
        ets_isr_unmask((1<<inum))

#define ETS_INTR_DISABLE(inum) \
        ets_isr_mask((1<<inum))

#define ETS_WMAC_INTR_ATTACH(func, arg) \
        ETS_ISR_ATTACH(ETS_WMAC_INUM, (func), (void *)(arg))

#define ETS_TG0_T0_INTR_ATTACH(func, arg) \
        ETS_ISR_ATTACH(ETS_TG0_T0_INUM, (func), (void *)(arg))

#define ETS_GPIO_INTR_ATTACH(func, arg) \
        ETS_ISR_ATTACH(ETS_GPIO_INUM, (func), (void *)(arg))

#define ETS_UART0_INTR_ATTACH(func, arg) \
        ETS_ISR_ATTACH(ETS_UART0_INUM, (func), (void *)(arg))

#define ETS_WDT_INTR_ATTACH(func, arg) \
        ETS_ISR_ATTACH(ETS_WDT_INUM, (func), (void *)(arg))

#define ETS_SLC_INTR_ATTACH(func, arg) \
        ETS_ISR_ATTACH(ETS_SLC_INUM, (func), (void *)(arg))

#define ETS_BB_INTR_ENABLE() \
        ETS_INTR_ENABLE(ETS_BB_INUM)

#define ETS_BB_INTR_DISABLE() \
        ETS_INTR_DISABLE(ETS_BB_INUM)

#define ETS_UART0_INTR_ENABLE() \
        ETS_INTR_ENABLE(ETS_UART0_INUM)

#define ETS_UART0_INTR_DISABLE() \
        ETS_INTR_DISABLE(ETS_UART0_INUM)

#define ETS_GPIO_INTR_ENABLE() \
        ETS_INTR_ENABLE(ETS_GPIO_INUM)

#define ETS_GPIO_INTR_DISABLE() \
        ETS_INTR_DISABLE(ETS_GPIO_INUM)

#define ETS_WDT_INTR_ENABLE() \
        ETS_INTR_ENABLE(ETS_WDT_INUM)

#define ETS_WDT_INTR_DISABLE() \
        ETS_INTR_DISABLE(ETS_WDT_INUM)

#define ETS_TG0_T0_INTR_ENABLE() \
        ETS_INTR_ENABLE(ETS_TG0_T0_INUM)

#define ETS_TG0_T0_INTR_DISABLE() \
        ETS_INTR_DISABLE(ETS_TG0_T0_INUM)

#define ETS_SLC_INTR_ENABLE() \
        ETS_INTR_ENABLE(ETS_SLC_INUM)

#define ETS_SLC_INTR_DISABLE() \
        ETS_INTR_DISABLE(ETS_SLC_INUM)
#endif

/**
  * @}
  */

#ifndef MAC2STR
#define MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#endif

#define ETS_MEM_BAR() asm volatile ( "" : : : "memory" )

typedef enum {
    OK = 0,
    FAIL,
    PENDING,
    BUSY,
    CANCEL,
} STATUS;

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* _ROM_ETS_SYS_H_ */

