/*
 * 版权所有（c）2015-2018，Nordic Semiconductor ASA保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行，除非嵌入产品中的Nordic Semiconductor ASA集成电路或该产品的软件更新，否则必须在发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用Nordic Semiconductor ASA的名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * 4.本软件无论是否经过修改，只能与Nordic Semiconductor ASA集成电路一起使用。
 *
 * 5.根据本许可证以二进制形式提供的任何软件不得进行反向工程、反编译、修改和/或反汇编。
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @defgroup nrf_soc_api soc库api@{
 *
 * @brief SoC库的API。
 *
 */

#ifndef NRF_SOC_H__
#define NRF_SOC_H__

#include <stdint.h>
#include "nrf.h"
#include "nrf_svc.h"
#include "nrf_error.h"
#include "nrf_error_soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@addtogroup NRF_SOC_DEFINES定义
 * @{ */

/**@brief 为SoC库保留的最低SVC编号。*/
#define SOC_SVC_BASE               (0x20)                   /**<禁用SoftDevice时可用的SVC的基本值。*/
#define SOC_SVC_BASE_NOT_AVAILABLE (0x2C)                   /**<禁用SoftDevice时不可用的SVC的基本值。*/

/**@brief 应用程序处理无线电非活动通知的保证时间。*/
#define NRF_RADIO_NOTIFICATION_INACTIVE_GUARANTEED_TIME_US  (62)

/**@brief 允许的最短时隙延长时间。*/
#define NRF_RADIO_MINIMUM_TIMESLOT_LENGTH_EXTENSION_TIME_US (200)

/**@brief 处理时隙扩展的最长处理时间。*/
#define NRF_RADIO_MAX_EXTENSION_PROCESSING_TIME_US           (17)

/**@brief 时隙结束前的最晚时间，可以延长时隙。*/
#define NRF_RADIO_MIN_EXTENSION_MARGIN_US                    (79)

#define SOC_ECB_KEY_LENGTH                (16)                       /**<ECB密钥长度。*/
#define SOC_ECB_CLEARTEXT_LENGTH          (16)                       /**<ECB明文长度。*/
#define SOC_ECB_CIPHERTEXT_LENGTH         (SOC_ECB_CLEARTEXT_LENGTH) /**<ECB密文长度。*/

#define SD_EVT_IRQn                       (SWI2_IRQn)        /**<SoftDevice事件IRQ编号。用于协议事件和SoC事件。*/
#define SD_EVT_IRQHandler                 (SWI2_IRQHandler)  /**<SoftDevice事件IRQ处理程序。用于协议事件和SoC事件。此处理程序的默认中断优先级设置为6*/
#define RADIO_NOTIFICATION_IRQn           (SWI1_IRQn)        /**<无线电通知IRQ编号。*/
#define RADIO_NOTIFICATION_IRQHandler     (SWI1_IRQHandler)  /**<无线电通知IRQ处理程序。此处理程序的默认中断优先级设置为6*/
#define NRF_RADIO_LENGTH_MIN_US           (100)               /**<允许的最短无线电时隙，以微秒为单位。*/
#define NRF_RADIO_LENGTH_MAX_US           (100000)            /**<允许的最长无线电时隙，以微秒为单位。*/

#define NRF_RADIO_DISTANCE_MAX_US         (128000000UL - 1UL) /**<请求中距离参数（请参见@ref nrf_readio_request_normal_t）允许的最长时隙距离（以微秒为单位）。*/

#define NRF_RADIO_EARLIEST_TIMEOUT_MAX_US (128000000UL - 1UL) /**<请求最早可能的时隙时允许的最长超时（以微秒为单位）。*/

#define NRF_RADIO_START_JITTER_US         (2)                 /**<相对于请求的开始时间，@ref NRF_RADIO_CALLBACK_SIGNAL_TYPE_START中的最大抖动。*/

/**@brief SoftDevice禁用时SoftDevice保留的PPI信道掩码。*/
#define NRF_SOC_SD_PPI_CHANNELS_SD_DISABLED_MSK ((uint32_t)(0))

/**@brief 启用SoftDevice时SoftDevice保留的PPI信道掩码。*/
#define NRF_SOC_SD_PPI_CHANNELS_SD_ENABLED_MSK  ((uint32_t)( \
      (1U << 17) \
    | (1U << 18) \
    | (1U << 19) \
    | (1U << 20) \
    | (1U << 21) \
    | (1U << 22) \
    | (1U << 23) \
    | (1U << 24) \
    | (1U << 25) \
    | (1U << 26) \
    | (1U << 27) \
    | (1U << 28) \
    | (1U << 29) \
    | (1U << 30) \
    | (1U << 31) \
  ))

/**@brief 禁用SoftDevice时，应用程序可用的PPI通道掩码。*/
#define NRF_SOC_APP_PPI_CHANNELS_SD_DISABLED_MSK (~NRF_SOC_SD_PPI_CHANNELS_SD_DISABLED_MSK)

/**@brief 启用SoftDevice时，应用程序可用的PPI通道掩码。*/
#define NRF_SOC_APP_PPI_CHANNELS_SD_ENABLED_MSK  (~NRF_SOC_SD_PPI_CHANNELS_SD_ENABLED_MSK)

/**@brief SoftDevice禁用时SoftDevice保留的PPI组掩码。*/
#define NRF_SOC_SD_PPI_GROUPS_SD_DISABLED_MSK    ((uint32_t)(0))

/**@brief 启用SoftDevice时SoftDevice保留的PPI组掩码。*/
#define NRF_SOC_SD_PPI_GROUPS_SD_ENABLED_MSK     ((uint32_t)( \
      (1U << 4) \
    | (1U << 5) \
  ))

/**@brief 禁用SoftDevice时应用程序可用的PPI组掩码。*/
#define NRF_SOC_APP_PPI_GROUPS_SD_DISABLED_MSK   (~NRF_SOC_SD_PPI_GROUPS_SD_DISABLED_MSK)

/**@brief 启用SoftDevice时应用程序可用的PPI组掩码。*/
#define NRF_SOC_APP_PPI_GROUPS_SD_ENABLED_MSK    (~NRF_SOC_SD_PPI_GROUPS_SD_ENABLED_MSK)

/**@} */

/**@addtogroup NRF_SOC_ENUMS枚举
 * @{ */

/**@brief SoC库中SVC函数使用的SVC编号。*/
enum NRF_SOC_SVCS
{
  SD_PPI_CHANNEL_ENABLE_GET   = SOC_SVC_BASE,
  SD_PPI_CHANNEL_ENABLE_SET   = SOC_SVC_BASE + 1,
  SD_PPI_CHANNEL_ENABLE_CLR   = SOC_SVC_BASE + 2,
  SD_PPI_CHANNEL_ASSIGN       = SOC_SVC_BASE + 3,
  SD_PPI_GROUP_TASK_ENABLE    = SOC_SVC_BASE + 4,
  SD_PPI_GROUP_TASK_DISABLE   = SOC_SVC_BASE + 5,
  SD_PPI_GROUP_ASSIGN         = SOC_SVC_BASE + 6,
  SD_PPI_GROUP_GET            = SOC_SVC_BASE + 7,
  SD_FLASH_PAGE_ERASE         = SOC_SVC_BASE + 8,
  SD_FLASH_WRITE              = SOC_SVC_BASE + 9,
  SD_PROTECTED_REGISTER_WRITE = SOC_SVC_BASE + 11,
  SD_MUTEX_NEW                            = SOC_SVC_BASE_NOT_AVAILABLE,
  SD_MUTEX_ACQUIRE                        = SOC_SVC_BASE_NOT_AVAILABLE + 1,
  SD_MUTEX_RELEASE                        = SOC_SVC_BASE_NOT_AVAILABLE + 2,
  SD_RAND_APPLICATION_POOL_CAPACITY_GET   = SOC_SVC_BASE_NOT_AVAILABLE + 3,
  SD_RAND_APPLICATION_BYTES_AVAILABLE_GET = SOC_SVC_BASE_NOT_AVAILABLE + 4,
  SD_RAND_APPLICATION_VECTOR_GET          = SOC_SVC_BASE_NOT_AVAILABLE + 5,
  SD_POWER_MODE_SET                       = SOC_SVC_BASE_NOT_AVAILABLE + 6,
  SD_POWER_SYSTEM_OFF                     = SOC_SVC_BASE_NOT_AVAILABLE + 7,
  SD_POWER_RESET_REASON_GET               = SOC_SVC_BASE_NOT_AVAILABLE + 8,
  SD_POWER_RESET_REASON_CLR               = SOC_SVC_BASE_NOT_AVAILABLE + 9,
  SD_POWER_POF_ENABLE                     = SOC_SVC_BASE_NOT_AVAILABLE + 10,
  SD_POWER_POF_THRESHOLD_SET              = SOC_SVC_BASE_NOT_AVAILABLE + 11,
  SD_POWER_POF_THRESHOLDVDDH_SET          = SOC_SVC_BASE_NOT_AVAILABLE + 12,
  SD_POWER_RAM_POWER_SET                  = SOC_SVC_BASE_NOT_AVAILABLE + 13,
  SD_POWER_RAM_POWER_CLR                  = SOC_SVC_BASE_NOT_AVAILABLE + 14,
  SD_POWER_RAM_POWER_GET                  = SOC_SVC_BASE_NOT_AVAILABLE + 15,
  SD_POWER_GPREGRET_SET                   = SOC_SVC_BASE_NOT_AVAILABLE + 16,
  SD_POWER_GPREGRET_CLR                   = SOC_SVC_BASE_NOT_AVAILABLE + 17,
  SD_POWER_GPREGRET_GET                   = SOC_SVC_BASE_NOT_AVAILABLE + 18,
  SD_POWER_DCDC_MODE_SET                  = SOC_SVC_BASE_NOT_AVAILABLE + 19,
  SD_POWER_DCDC0_MODE_SET                 = SOC_SVC_BASE_NOT_AVAILABLE + 20,
  SD_APP_EVT_WAIT                         = SOC_SVC_BASE_NOT_AVAILABLE + 21,
  SD_CLOCK_HFCLK_REQUEST                  = SOC_SVC_BASE_NOT_AVAILABLE + 22,
  SD_CLOCK_HFCLK_RELEASE                  = SOC_SVC_BASE_NOT_AVAILABLE + 23,
  SD_CLOCK_HFCLK_IS_RUNNING               = SOC_SVC_BASE_NOT_AVAILABLE + 24,
  SD_RADIO_NOTIFICATION_CFG_SET           = SOC_SVC_BASE_NOT_AVAILABLE + 25,
  SD_ECB_BLOCK_ENCRYPT                    = SOC_SVC_BASE_NOT_AVAILABLE + 26,
  SD_ECB_BLOCKS_ENCRYPT                   = SOC_SVC_BASE_NOT_AVAILABLE + 27,
  SD_RADIO_SESSION_OPEN                   = SOC_SVC_BASE_NOT_AVAILABLE + 28,
  SD_RADIO_SESSION_CLOSE                  = SOC_SVC_BASE_NOT_AVAILABLE + 29,
  SD_RADIO_REQUEST                        = SOC_SVC_BASE_NOT_AVAILABLE + 30,
  SD_EVT_GET                              = SOC_SVC_BASE_NOT_AVAILABLE + 31,
  SD_TEMP_GET                             = SOC_SVC_BASE_NOT_AVAILABLE + 32,
  SD_POWER_USBPWRRDY_ENABLE               = SOC_SVC_BASE_NOT_AVAILABLE + 33,
  SD_POWER_USBDETECTED_ENABLE             = SOC_SVC_BASE_NOT_AVAILABLE + 34,
  SD_POWER_USBREMOVED_ENABLE              = SOC_SVC_BASE_NOT_AVAILABLE + 35,
  SD_POWER_USBREGSTATUS_GET               = SOC_SVC_BASE_NOT_AVAILABLE + 36,
  SVC_SOC_LAST                            = SOC_SVC_BASE_NOT_AVAILABLE + 37
};

/**@brief a：：nrf_mute_t的可能值。*/
enum NRF_MUTEX_VALUES
{
  NRF_MUTEX_FREE,
  NRF_MUTEX_TAKEN
};

/**@brief 电源模式。*/
enum NRF_POWER_MODES
{
  NRF_POWER_MODE_CONSTLAT,  /**<恒定延迟模式。请参阅参考手册中的电源管理。*/
  NRF_POWER_MODE_LOWPWR     /**<低功率模式。请参阅参考手册中的电源管理。*/
};


/**@brief 电源故障阈值*/
enum NRF_POWER_THRESHOLDS
{
  NRF_POWER_THRESHOLD_V17 = 4UL, /**<1.7伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V18,       /**<1.8伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V19,       /**<1.9伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V20,       /**<2.0伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V21,       /**<2.1伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V22,       /**<2.2伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V23,       /**<2.3伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V24,       /**<2.4伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V25,       /**<2.5伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V26,       /**<2.6伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V27,       /**<2.7伏电源故障阈值。*/
  NRF_POWER_THRESHOLD_V28        /**<2.8伏电源故障阈值。*/
};

/**@brief 高压电源故障阈值*/
enum NRF_POWER_THRESHOLDVDDHS
{
  NRF_POWER_THRESHOLDVDDH_V27,       /**<2.7伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V28,       /**<2.8伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V29,       /**<2.9伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V30,       /**<3.0伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V31,       /**<3.1伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V32,       /**<3.2伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V33,       /**<3.3伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V34,       /**<3.4伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V35,       /**<3.5伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V36,       /**<3.6伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V37,       /**<3.7伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V38,       /**<3.8伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V39,       /**<3.9伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V40,       /**<4.0伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V41,       /**<4.1伏电源故障阈值。*/
  NRF_POWER_THRESHOLDVDDH_V42        /**<4.2伏电源故障阈值。*/
};


/**@brief DC/DC转换器模式。*/
enum NRF_POWER_DCDC_MODES
{
  NRF_POWER_DCDC_DISABLE,          /**<禁用DCDC。*/
  NRF_POWER_DCDC_ENABLE            /**<DCDC已启用。*/
};

/**@brief 无线电通知距离。*/
enum NRF_RADIO_NOTIFICATION_DISTANCES
{
  NRF_RADIO_NOTIFICATION_DISTANCE_NONE = 0, /**<事件没有通知。*/
  NRF_RADIO_NOTIFICATION_DISTANCE_800US,    /**<从活动通知到无线电活动开始的距离。*/
  NRF_RADIO_NOTIFICATION_DISTANCE_1740US,   /**<从活动通知到无线电活动开始的距离。*/
  NRF_RADIO_NOTIFICATION_DISTANCE_2680US,   /**<从活动通知到无线电活动开始的距离。*/
  NRF_RADIO_NOTIFICATION_DISTANCE_3620US,   /**<从活动通知到无线电活动开始的距离。*/
  NRF_RADIO_NOTIFICATION_DISTANCE_4560US,   /**<从活动通知到无线电活动开始的距离。*/
  NRF_RADIO_NOTIFICATION_DISTANCE_5500US    /**<从活动通知到无线电活动开始的距离。*/
};


/**@brief 无线电通知类型。*/
enum NRF_RADIO_NOTIFICATION_TYPES
{
  NRF_RADIO_NOTIFICATION_TYPE_NONE = 0,        /**<事件没有无线电通知信号。*/
  NRF_RADIO_NOTIFICATION_TYPE_INT_ON_ACTIVE,   /**<启用收音机时使用中断进行通知。*/
  NRF_RADIO_NOTIFICATION_TYPE_INT_ON_INACTIVE, /**<禁用收音机时使用中断进行通知。*/
  NRF_RADIO_NOTIFICATION_TYPE_INT_ON_BOTH,     /**<在启用和禁用无线电时使用中断进行通知。*/
};

/**@brief 无线电信号回调类型。*/
enum NRF_RADIO_CALLBACK_SIGNAL_TYPE
{
  NRF_RADIO_CALLBACK_SIGNAL_TYPE_START,             /**<此信号表示无线电时隙的开始。*/
  NRF_RADIO_CALLBACK_SIGNAL_TYPE_TIMER0,            /**<此信号表示NRF_TIMER0中断。*/
  NRF_RADIO_CALLBACK_SIGNAL_TYPE_RADIO,             /**<此信号表示NRF_RADIO中断。*/
  NRF_RADIO_CALLBACK_SIGNAL_TYPE_EXTEND_FAILED,     /**<此信号表示扩展操作失败。*/
  NRF_RADIO_CALLBACK_SIGNAL_TYPE_EXTEND_SUCCEEDED   /**<此信号表示扩展操作成功。*/
};

/**@brief 信号回调请求的操作。
 *
 *  该代码向SOC提供了当信号回调返回时要采取的操作的指令。
 */
enum NRF_RADIO_SIGNAL_CALLBACK_ACTION
{
  NRF_RADIO_SIGNAL_CALLBACK_ACTION_NONE,            /**<返回而不执行操作。*/
  NRF_RADIO_SIGNAL_CALLBACK_ACTION_EXTEND,          /**<请求当前时隙的扩展。此操作的最长执行时间：@ref NRF_RADIO_MAX_EXTENSION_PROCESSING_time_US。此操作必须在时隙结束前至少@ref NRF_RADIO_MIN_EXTENSION_MARGIN_US启动。*/
  NRF_RADIO_SIGNAL_CALLBACK_ACTION_END,             /**<结束当前无线电时隙。*/
  NRF_RADIO_SIGNAL_CALLBACK_ACTION_REQUEST_AND_END  /**<请求新的无线电时隙并结束当前时隙。*/
};

/**@brief 无线电时隙高频时钟源配置。*/
enum NRF_RADIO_HFCLK_CFG
{
  NRF_RADIO_HFCLK_CFG_XTAL_GUARANTEED, /**< SoftDevice将保证在整个时隙期间，高频时钟源为外部晶体。这应该是使用无线电或需要高计时精度的事件的首选选项。
                                           @注意：SoftDevice将分别在时隙开始和结束时自动打开和关闭外部晶体。在SoftDevice在时隙结束后不久需要晶体的情况下，晶体也可以故意在时隙之后保持运行。*/
  NRF_RADIO_HFCLK_CFG_NO_GUARANTEE    /**< 这种配置允许更早和更严格地调度时隙。RC振荡器可以是时隙的部分或整个持续时间的时钟源。因此，必须考虑RC振荡器的精度。
                                           @注意：如果应用程序将在具有此配置的时隙中使用无线电外围设备，则在启动无线电之前，必须确保晶体运行稳定。*/
};

/**@brief 无线电时隙优先级。*/
enum NRF_RADIO_PRIORITY
{
  NRF_RADIO_PRIORITY_HIGH,                          /**<高（与SoftDevice堆栈的正常连接优先级相同）。*/
  NRF_RADIO_PRIORITY_NORMAL,                        /**<正常（与SoftDevice堆栈的次要活动的优先级相等）。*/
};

/**@brief 无线电时隙请求类型。*/
enum NRF_RADIO_REQUEST_TYPE
{
  NRF_RADIO_REQ_TYPE_EARLIEST,                      /**<尽早请求无线电时隙。这应始终用于会话中的第一个请求。*/
  NRF_RADIO_REQ_TYPE_NORMAL                         /**<正常无线电时隙请求。*/
};

/**@brief SoC事件。*/
enum NRF_SOC_EVTS
{
  NRF_EVT_HFCLKSTARTED,                         /**<表示HFCLK已启动的事件。*/
  NRF_EVT_POWER_FAILURE_WARNING,                /**<表示发生电源故障警告的事件。*/
  NRF_EVT_FLASH_OPERATION_SUCCESS,              /**<指示正在进行的闪存操作已成功完成的事件。*/
  NRF_EVT_FLASH_OPERATION_ERROR,                /**<事件，表示正在进行的闪存操作已超时并出现错误。*/
  NRF_EVT_RADIO_BLOCKED,                        /**<指示无线电时隙被阻塞的事件。*/
  NRF_EVT_RADIO_CANCELED,                       /**<SoftDevice取消无线电时隙的事件。*/
  NRF_EVT_RADIO_SIGNAL_CALLBACK_INVALID_RETURN, /**<指示无线电时隙信号回调处理程序返回无效的事件。*/
  NRF_EVT_RADIO_SESSION_IDLE,                   /**<指示无线时隙会话空闲的事件。*/
  NRF_EVT_RADIO_SESSION_CLOSED,                 /**<指示无线电时隙会话关闭的事件。*/
  NRF_EVT_POWER_USB_POWER_READY,                /**<指示USB 3.3 V电源已就绪的事件。*/
  NRF_EVT_POWER_USB_DETECTED,                   /**<表示VBUS上检测到电压供应的事件。*/
  NRF_EVT_POWER_USB_REMOVED,                    /**<指示电压供应从VBUS移除的事件。*/
  NRF_EVT_NUMBER_OF_EVTS
};

/**@} */


/**@addtogroup NRF_SOC_STRUCTURES结构
 * @{ */

/**@brief 表示用于nrf_mmutex函数的互斥体。
 * @note 直接访问值是不安全的，请使用互斥函数！
 */
typedef volatile uint8_t nrf_mutex_t;

/**@brief 尽早请求时隙的参数。*/
typedef struct
{
  uint8_t       hfclk;                              /**<高频时钟源，请参见@ref NRF_RADIO_HFCLK_CFG。*/
  uint8_t       priority;                           /**<无线电时隙优先级，请参见@ref NRF_radio_priority。*/
  uint32_t      length_us;                          /**<无线电时隙长度（在100到100000微秒的范围内）。*/
  uint32_t      timeout_us;                         /**<所请求时隙开始之前的最长可接受延迟（最多@ref NRF_RADIO_EARLIEST_TIMEOUT_MAX_US微秒）。*/
} nrf_radio_request_earliest_t;

/**@brief 正常无线电时隙请求的参数。*/
typedef struct
{
  uint8_t       hfclk;                              /**<高频时钟源，请参见@ref NRF_RADIO_HFCLK_CFG。*/
  uint8_t       priority;                           /**<无线电时隙优先级，请参见@ref NRF_radio_priority。*/
  uint32_t      distance_us;                        /**<与上一个无线电时隙开始的距离（最多@ref NRF_radio_Distance_MAX_US微秒）。*/
  uint32_t      length_us;                          /**<无线电时隙长度（在[100..100000]微秒的范围内）。*/
} nrf_radio_request_normal_t;

/**@brief 无线电时隙请求参数。*/
typedef struct
{
  uint8_t                         request_type;     /**<请求类型，请参阅@ref NRF_RADIO_request_Type。*/
  union
  {
    nrf_radio_request_earliest_t  earliest;         /**<用于尽早请求无线电时隙的参数。*/
    nrf_radio_request_normal_t    normal;           /**<请求正常无线电时隙的参数。*/
  } params;                                         /**<参数联合。*/
} nrf_radio_request_t;

/**@brief 返回无线时隙信号回调的参数。*/
typedef struct
{
  uint8_t               callback_action;            /**<应用程序从信号回调返回时请求的操作，请参阅@ref NRF_RADIO_signal_callback_action。*/
  union
  {
    struct
    {
      nrf_radio_request_t * p_next;                 /**<下一个无线电时隙的请求参数。*/
    } request;                                      /**<return_code@ref NRF_RADIO_SIGNAL_CALLBACK_ACTION_REQUEST_AND_END的其他参数。*/
    struct
    {
      uint32_t              length_us;              /**<请求延长无线电时隙持续时间（微秒）（有关最短时间，请参阅@ref NRF_radio_minimum_timeslot_LENGTH_extension_time_US）。*/
    } extend;                                       /**<return_code@ref NRF_RADIO_SIGNAL_CALLBACK_ACTION_EXTEND的其他参数。*/
  } params;                                         /**<参数联合。*/
} nrf_radio_signal_callback_return_param_t;

/**@brief 无线电时隙信号回调类型。
 *
 * @note 在返回参数无效的情况下，无线电时隙将在从信号回调和
 *       @ref 将发送NRF_EVT_RADIO_SIGNAL_CALLBACK_INVALID_RETURN事件。
 * @note 在信号回调函数返回后，返回的结构指针必须保持有效。例如，这意味着它不能指向堆栈变量。
 *
 * @param[in] signal_type 信号类型，请参见@ref NRF_RADIO_CALLBACK_signal_Type。
 *
 * @return 指向包含应用程序请求的操作的结构的指针。
 */
typedef nrf_radio_signal_callback_return_param_t * (*nrf_radio_signal_callback_t) (uint8_t signal_type);

/**@brief AES ECB参数typedefs*/
typedef uint8_t soc_ecb_key_t[SOC_ECB_KEY_LENGTH];                /**<加密密钥类型。*/
typedef uint8_t soc_ecb_cleartext_t[SOC_ECB_CLEARTEXT_LENGTH];    /**<Cleartext数据类型。*/
typedef uint8_t soc_ecb_ciphertext_t[SOC_ECB_CIPHERTEXT_LENGTH];  /**<密文数据类型。*/

/**@brief AES ECB数据结构*/
typedef struct
{
  soc_ecb_key_t        key;            /**<加密密钥。*/
  soc_ecb_cleartext_t  cleartext;      /**<明文数据。*/
  soc_ecb_ciphertext_t ciphertext;     /**<密文数据。*/
} nrf_ecb_hal_data_t;

/**@brief AES ECB块。用于在对@ref sd_ecb_blocks_encrypt的单个调用中提供多个块。*/
typedef struct
{
  soc_ecb_key_t const *       p_key;           /**<指向加密密钥的指针。*/
  soc_ecb_cleartext_t const * p_cleartext;     /**<指向明文数据的指针。*/
  soc_ecb_ciphertext_t *      p_ciphertext;    /**<指向密文数据的指针。*/
} nrf_ecb_hal_data_block_t;

/**@} */

/**@addtogroup NRF_SOC_FUNCTIONS函数
 * @{ */

/**@brief 初始化互斥体。
 *
 * @param[in] p_mutex 指向要初始化的互斥对象的指针。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_MUTEX_NEW, uint32_t, sd_mutex_new(nrf_mutex_t * p_mutex));

/**@brief 尝试获取互斥锁。
 *
 * @param[in] p_mutex 指向要获取的互斥对象的指针。
 *
 * @retval ：：NRF_SUCCESS已成功获取互斥对象。
 * @retval ：：NRF_ERROR_SOC_MUTEX_ALREADY_TAKEN无法获取互斥体。
 */
SVCALL(SD_MUTEX_ACQUIRE, uint32_t, sd_mutex_acquire(nrf_mutex_t * p_mutex));

/**@brief 释放互斥锁。
 *
 * @param[in] p_mutex 指向要释放的互斥对象的指针。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_MUTEX_RELEASE, uint32_t, sd_mutex_release(nrf_mutex_t * p_mutex));

/**@brief 查询应用程序随机池的容量。
 *
 * @param[out] p_pool_capacity 池的容量。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_RAND_APPLICATION_POOL_CAPACITY_GET, uint32_t, sd_rand_application_pool_capacity_get(uint8_t * p_pool_capacity));

/**@brief 获取应用程序可用的随机字节数。
 *
 * @param[out] p_bytes_available 池中当前可用的字节数。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_RAND_APPLICATION_BYTES_AVAILABLE_GET, uint32_t, sd_rand_application_bytes_available_get(uint8_t * p_bytes_available));

/**@brief 从应用程序池中获取随机字节。
 *
 * @param[out]  p_buff  指向用于存储字节的unit8_t缓冲区的指针。
 * @param[in]   length  从池中获取并放入p_buff的字节数。
 *
 * @retval ：：NRF_SUCCESS请求的字节已写入p_buff。
 * @retval ：：NRF_ERROR_SOC_RAND_NOT_ENOUGH_VALUES没有字节写入缓冲区，因为没有足够的字节可用。
*/
SVCALL(SD_RAND_APPLICATION_VECTOR_GET, uint32_t, sd_rand_application_vector_get(uint8_t * p_buff, uint8_t length));

/**@brief 获取重置原因寄存器。
 *
 * @param[out]  p_reset_reason  NRF_POWER->RESETREAS寄存器的内容。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_RESET_REASON_GET, uint32_t, sd_power_reset_reason_get(uint32_t * p_reset_reason));

/**@brief 清除重置原因寄存器的位。
 *
 * @param[in] reset_reason_clr_msk 包含要从重置原因寄存器中清除的位。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_RESET_REASON_CLR, uint32_t, sd_power_reset_reason_clr(uint32_t reset_reason_clr_msk));

/**@brief 设置CPU休眠时的电源模式。
 *
 * @param[in] power_mode CPU休眠时使用的电源模式，请参阅@ref NRF_power_MODES@sa sd_app_evt_wait
 *
 * @retval ：：NRF_SUCCESS电源模式已设置。
 * @retval ：：NRF_ERROR_SOC_POWER_MODE_UNKNOWN电源模式未知。
 */
SVCALL(SD_POWER_MODE_SET, uint32_t, sd_power_mode_set(uint8_t power_mode));

/**@brief 将芯片置于系统关闭模式。
 *
 * @retval ::NRF_ERROR_SOC_POWER_OFF_SHOULD_NOT_RETURN
 */
SVCALL(SD_POWER_SYSTEM_OFF, uint32_t, sd_power_system_off(void));

/**@brief 启用或禁用电源故障比较器。
 *
 * 启用此选项将在出现电源故障警告时发出SoftDevice事件（NRF_EVT_POWER_FAILURE_WARNING）。可以使用sd_evt_get（）检索事件；
 *
 * @param[in] pof_enable    如果应启用断电比较器，则为True；如果应禁用，则为false。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_POF_ENABLE, uint32_t, sd_power_pof_enable(uint8_t pof_enable));

/**@brief 启用或禁用USB电源就绪事件。
 *
 * 当USB 3.3 V电源就绪时，启用此选项将产生SoftDevice事件（NRF_EVT_POWER_USB_POWER_READY）。可以使用sd_evt_get（）检索事件；
 *
 * @param[in] usbpwrrdy_enable    如果应启用电源就绪事件，则为True；如果应禁用，则为false。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_USBPWRRDY_ENABLE, uint32_t, sd_power_usbpwrrdy_enable(uint8_t usbpwrrdy_enable));

/**@brief 启用或禁用电源USB检测事件。
 *
 * 当VBUS上检测到电压供应时，启用此选项将产生SoftDevice事件（NRF_EVT_POWER_USB_DETECTED）。可以使用sd_evt_get（）检索事件；
 *
 * @param[in] usbdetected_enable    如果应启用电源就绪事件，则为True；如果应禁用，则为false。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_USBDETECTED_ENABLE, uint32_t, sd_power_usbdetected_enable(uint8_t usbdetected_enable));

/**@brief 启用或禁用电源USB移除事件。
 *
 * 当电压供应从VBUS中移除时，启用此选项将产生SoftDevice事件（NRF_EVT_POWER_USB_REMOVED）。可以使用sd_evt_get（）检索事件；
 *
 * @param[in] usbremoved_enable    如果应启用电源就绪事件，则为True；如果应禁用，则为false。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_USBREMOVED_ENABLE, uint32_t, sd_power_usbremoved_enable(uint8_t usbremoved_enable));

/**@brief 获取USB电源状态寄存器内容。
 *
 * @param[out] usbregstatus    USBREGSTATUS寄存器的内容。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_USBREGSTATUS_GET, uint32_t, sd_power_usbregstatus_get(uint32_t * usbregstatus));

/**@brief 设置电源故障比较器阈值。
 *
 * @note: 电源故障比较器阈值设置。此设置适用于正常电压模式（电源连接到VDD和VDDH）和高压模式（电源仅连接到VDDH）。
 *
 * @param[in] threshold 要使用的电源故障阈值，请参阅@ref NRF_power_THRESHOLDS。
 *
 * @retval ：：NRF_SUCCESS已设置电源故障阈值。
 * @retval ：：NRF_ERROR_SOC_POWER_POF_THRESHOLD_UNKOWN电源故障阈值未知。
 */
SVCALL(SD_POWER_POF_THRESHOLD_SET, uint32_t, sd_power_pof_threshold_set(uint8_t threshold));

/**@brief 设置高电压的电源故障比较器阈值。
 *
 * @note: 高电压模式的电源故障比较器阈值设置（电源仅连接到VDDH）。此设置不适用于正常电压模式（电源连接到VDD和VDDH）。
 *
 * @param[in] threshold 要使用的电源故障阈值，请参阅@ref NRF_power_THRESHOLDVDDHS。
 *
 * @retval ：：NRF_SUCCESS已设置电源故障阈值。
 * @retval ：：NRF_ERROR_SOC_POWER_POF_THRESHOLD_UNKOWN电源故障阈值未知。
 */
SVCALL(SD_POWER_POF_THRESHOLDVDDH_SET, uint32_t, sd_power_pof_thresholdvddh_set(uint8_t threshold));

/**@brief 写入NRF_POWER->RAM[index]。POWERSET寄存器。
 *
 * @param[in] index 包含NRF_POWER->RAM[index]中的索引。要写入的POWERSET寄存器。
 * @param[in] ram_powerset 包含要写入NRF_POWER->RAM[index]的单词。POWERSET寄存器。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_RAM_POWER_SET, uint32_t, sd_power_ram_power_set(uint8_t index, uint32_t ram_powerset));

/**@brief 写入NRF_POWER->RAM[index]。POWERCLR寄存器。
 *
 * @param[in] index 包含NRF_POWER->RAM[index]中的索引。要写入的POWERCLR寄存器。
 * @param[in] ram_powerclr 包含要写入NRF_POWER->RAM[index]的单词。POWERCLR寄存器。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_RAM_POWER_CLR, uint32_t, sd_power_ram_power_clr(uint8_t index, uint32_t ram_powerclr));

/**@brief 获取NRF_POWER->RAM[index]的内容。POWER寄存器，指示RAM[index]块的电源状态。
 *
 * @param[in] index 包含NRF_POWER->RAM[index]中的索引。要读取的POWER寄存器。
 * @param[out] p_ram_power NRF_POWER->RAM[index]的内容。POWER寄存器。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_RAM_POWER_GET, uint32_t, sd_power_ram_power_get(uint8_t index, uint32_t * p_ram_power));

/**@brief 设置通用保留寄存器（NRF_POWER->GPREGRET*）中的位。
 *
 * @param[in] gpregret_id GPREGRET为0，GPREGRET2为1。
 * @param[in] gpregret_msk 要在GPREGRET寄存器中设置的位。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_GPREGRET_SET, uint32_t, sd_power_gpregret_set(uint32_t gpregret_id, uint32_t gpregret_msk));

/**@brief 清除通用保留寄存器（NRF_POWER->GPREGRET*）中的位。
 *
 * @param[in] gpregret_id GPREGRET为0，GPREGRET2为1。
 * @param[in] gpregret_msk GPREGRET寄存器中要清除的位。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_GPREGRET_CLR, uint32_t, sd_power_gpregret_clr(uint32_t gpregret_id, uint32_t gpregret_msk));

/**@brief 获取通用保留寄存器（NRF_POWER->GPREGRET*）的内容。
 *
 * @param[in] gpregret_id GPREGRET为0，GPREGRET2为1。
 * @param[out] p_gpregret GPREGRET寄存器的内容。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_POWER_GPREGRET_GET, uint32_t, sd_power_gpregret_get(uint32_t gpregret_id, uint32_t *p_gpregret));

/**@brief 启用或禁用调节器1级（REG1）的DC/DC调节器。
 *
 * @param[in] dcdc_mode DCDC的模式，请参阅@ref NRF_POWER_DCDC_MODES。
 *
 * @retval ::NRF_SUCCESS
 * @retval ：：NRF_ERROR_INVALID_PARAM DCDC模式无效。
 */
SVCALL(SD_POWER_DCDC_MODE_SET, uint32_t, sd_power_dcdc_mode_set(uint8_t dcdc_mode));

/**@brief 启用或禁用调节器阶段0（REG0）的DC/DC调节器。
 *
 * 有关REG0阶段的更多详细信息，请参阅产品规范。
 *
 * @param[in] dcdc_mode DCDC0的模式，请参阅@ref NRF_POWER_DCDC_MODES。
 *
 * @retval ::NRF_SUCCESS
 * @retval ：：NRF_ERROR_INVALID_PARAM dcdc_mode无效。
 */
SVCALL(SD_POWER_DCDC0_MODE_SET, uint32_t, sd_power_dcdc0_mode_set(uint8_t dcdc_mode));

/**@brief 请求高频晶体振荡器。
 *
 * 将启动高频晶体振荡器，晶体的启动时间会发生变化，可以轮询：：sd_clock_hfclk_is_running函数以检查其是否已启动。
 *
 * @see sd_clock_hfclk_is正在运行
 * @see sd_clock_hfclk_release
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_CLOCK_HFCLK_REQUEST, uint32_t, sd_clock_hfclk_request(void));

/**@brief 释放高频晶体振荡器。
 *
 * 将停止高频晶体振荡器，这会立即发生。
 *
 * @see sd_clock_hfclk_is正在运行
 * @see sd_clock_hfclk_请求
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_CLOCK_HFCLK_RELEASE, uint32_t, sd_clock_hfclk_release(void));

/**@brief 检查高频晶体振荡器是否正在运行。
 *
 * @see sd_clock_hfclk_请求
 * @see sd_clock_hfclk_release
 *
 * @param[out] p_is_running 如果外部晶体振荡器正在运行，则为1；如果没有，则为0。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_CLOCK_HFCLK_IS_RUNNING, uint32_t, sd_clock_hfclk_is_running(uint32_t * p_is_running));

/**@brief 等待应用程序事件。
 *
 * 当中断被禁用时，应用程序事件是应用程序中断或挂起的中断。
 *
 * 当应用程序通过调用此函数来等待应用程序事件时，由于此函数将在线程模式下等待，因此将在挂起时立即执行已启用的中断，然后执行将在应用程序的主线程中返回。
 *
 * 为了从禁用中断中唤醒，必须在Cortex-M MCU的系统控制寄存器（SCR）CMSIS_SCB中设置SEVONPEND标志。在这种情况下，当禁用的中断被挂起时，该函数将返回应用程序的主线程。
 *
 * @note 应用程序必须确保使用：：sd_nvic_ClearEndingIRQ清除挂起标志，以便使用此函数休眠。这仅对禁用的中断是必要的，因为中断处理程序将自动清除启用中断的挂起标志。
 *
 * @note 如果自上次调用sd_app_evt_wait以来发生了应用程序中断，则该函数将立即返回，不会进入休眠状态。这是为了避免在中断处理程序中更新标志并在主循环中处理标志时可能出现的竞争条件。
 *
 * @post 发生了应用程序中断或设置了中断挂起标志。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_APP_EVT_WAIT, uint32_t, sd_app_evt_wait(void));

/**@brief 获取PPI通道启用寄存器内容。
 *
 * @param[out] p_channel_enable PPI CHEN寄存器的内容。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_PPI_CHANNEL_ENABLE_GET, uint32_t, sd_ppi_channel_enable_get(uint32_t * p_channel_enable));

/**@brief 设置PPI通道启用寄存器。
 *
 * @param[in] channel_enable_set_msk 包含要在PPI CHEN寄存器中设置的位的掩码。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_PPI_CHANNEL_ENABLE_SET, uint32_t, sd_ppi_channel_enable_set(uint32_t channel_enable_set_msk));

/**@brief 清除PPI通道启用寄存器。
 *
 * @param[in] channel_enable_clr_msk 包含PPI CHEN寄存器中要清除的位的掩码。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_PPI_CHANNEL_ENABLE_CLR, uint32_t, sd_ppi_channel_enable_clr(uint32_t channel_enable_clr_msk));

/**@brief 为PPI通道分配端点。
 *
 * @param[in] channel_num 要分配的PPI通道的编号。
 * @param[in] evt_endpoint PPI通道的事件端点。
 * @param[in] task_endpoint PPI通道的任务端点。
 *
 * @retval ：：NRF_ERROR_SOC_PPI_INVALID_CHANNEL信道号无效。
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_PPI_CHANNEL_ASSIGN, uint32_t, sd_ppi_channel_assign(uint8_t channel_num, const volatile void * evt_endpoint, const volatile void * task_endpoint));

/**@brief 启用频道组的任务。
 *
 * @param[in] group_num 通道组的编号。
 *
 * @retval ：：NRF_ERROR_SOC_PPI_INVALID_GROUP组编号无效
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_PPI_GROUP_TASK_ENABLE, uint32_t, sd_ppi_group_task_enable(uint8_t group_num));

/**@brief 禁用频道组的任务。
 *
 * @param[in] group_num PPI组的编号。
 *
 * @retval ：：NRF_ERROR_SOC_PPI_INVALID_GROUP组编号无效。
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_PPI_GROUP_TASK_DISABLE, uint32_t, sd_ppi_group_task_disable(uint8_t group_num));

/**@brief 将PPI信道分配给信道组。
 *
 * @param[in] group_num 通道组的编号。
 * @param[in] channel_msk 要分配给组的通道掩码。
 *
 * @retval ：：NRF_ERROR_SOC_PPI_INVALID_GROUP组编号无效。
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_PPI_GROUP_ASSIGN, uint32_t, sd_ppi_group_assign(uint8_t group_num, uint32_t channel_msk));

/**@brief 获取频道组的PPI频道。
 *
 * @param[in]   group_num 通道组的编号。
 * @param[out]  p_channel_msk 分配给组的通道掩码。
 *
 * @retval ：：NRF_ERROR_SOC_PPI_INVALID_GROUP组编号无效。
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_PPI_GROUP_GET, uint32_t, sd_ppi_group_get(uint8_t group_num, uint32_t * p_channel_msk));

/**@brief 配置无线电通知信号。
 *
 * @note
 *      -通知信号延迟取决于用于通知信号的SWI的中断优先级设置。
 *      -为了确保无线电通知信号以一致的方式运行，必须在没有协议堆栈或其他SoftDevice活动正在进行时配置无线电通知。建议在启用SoftDevice后直接配置无线电通知信号。
 *      -在ACTIVE信号和无线电事件开始之间的时间段内，SoftDevice将中断应用程序以进行无线电事件准备。
 *      -使用无线电通知功能可能会限制带宽，因为SoftDevice可能必须缩短连接事件，以便有时间接收无线电通知信号。
 *
 * @param[in]  type      通知信号类型，请参见@ref NRF_RADIO_notification_TYPES。
 *                       @ref NRF_RADIO_NOTIFICATION_TYPE_NONE应用于关闭无线电通知。建议（但不是必需）使用@ref NRF_RADIO_NOTIFICATION_DISTANCE_NONE与
 *                       @ref NRF_RADIO_NOTIFICATION_TYPE_NONE.
 *
 * @param[in]  distance  通知信号与无线电活动开始之间的距离，请参见@ref NRF_radio_notification_DISTANCES。当@ref NRF_RADIO_NOTIFICATION_TYPE_NONE或
 *                       @ref 使用NRF_RADIO_NOTIFICATION_TYPE_INT_ON_INACTIVE。
 *
 * @retval ：：NRF_ERROR_INVALID_PARAM组编号无效。
 * @retval ：：NRF_ERROR_INVALID_STATE协议堆栈或其他SoftDevice正在运行。停止所有正在运行的活动并重试。
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_RADIO_NOTIFICATION_CFG_SET, uint32_t, sd_radio_notification_cfg_set(uint8_t type, uint8_t distance));

/**@brief 根据指定的参数加密块。
 *
 * 128位AES加密。
 *
 * @note:
 *    -应用程序可以将SCR中的SEVONPEND位设置为1，以在ECB运行时使SoftDevice休眠。SEVONPEND位只能从应用程序主中断或低中断级别清除（设置为0）。
 *
 * @param[in, out] p_ecb_data指向ecb参数结构的指针（两个输入参数和一个输出参数）。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_ECB_BLOCK_ENCRYPT, uint32_t, sd_ecb_block_encrypt(nrf_ecb_hal_data_t * p_ecb_data));

/**@brief 加密作为数据块结构阵列提供的多个数据块。
 *
 * @details: 对多个数据块执行128位AES加密
 *
 * @note:
 *    -应用程序可以将SCR中的SEVONPEND位设置为1，以在ECB运行时使SoftDevice休眠。SEVONPEND位只能从应用程序主中断或低中断级别清除（设置为0）。
 *
 * @param[in]     block_count     p_data_blocks数组中的块计数。
 * @param[in,out] p_data_blocks   指向
 *                                @ref nrf_ecb_hal_data_block_t结构。
 *
 * @retval ::NRF_SUCCESS
 */
SVCALL(SD_ECB_BLOCKS_ENCRYPT, uint32_t, sd_ecb_blocks_encrypt(uint8_t block_count, nrf_ecb_hal_data_block_t * p_data_blocks));

/**@brief 获取SoC API生成的任何挂起事件。
 *
 * 应用程序应继续调用此函数以获取事件，直到返回：：NRF_ERROR_NOT_FOUND。
 *
 * @param[out] p_evt_id 如果有任何事件待定，则设置为@ref NRF_SOC_EVTS中的值之一。
 *
 * @retval ：：NRF_SUCCESS事件挂起。事件id写入p_evt_id参数中。
 * @retval ：：NRF_ERROR_NOT_FOUND无未决事件。
 */
SVCALL(SD_EVT_GET, uint32_t, sd_evt_get(uint32_t * p_evt_id));

/**@brief 在芯片上测量温度
 *
 * 在完成温度测量之前，此功能将被阻止。从打电话到回来大约需要50人。
 *
 * @param[out] p_temp 温度测量结果。模具温度为0.25摄氏度。
 *
 * @retval ：：NRF_SUCCESS完成温度测量，并将温度写入temp
 */
SVCALL(SD_TEMP_GET, uint32_t, sd_temp_get(int32_t * p_temp));

/**@brief 闪存写入
*
* 将缓冲区写入闪存的命令
*
* 如果SoftDevice已启用：此调用将启动闪存访问命令，其完成情况将通过以下事件之一通知应用程序：
*      - @ref NRF_EVT_FLASH_OPERATION_SUCCESS-命令已成功完成。
*      - @ref NRF_EVT_FLASH_OPERATION_ERROR-无法启动命令。
*
* 如果未启用SoftDevice，则不会生成任何事件，并且在写入完成后，此调用将返回@ref NRF_SUCCESS
*
* @note
*      -在闪存擦除和写入期间，此调用将控制收音机和CPU，以确保它们不会干扰闪存访问。这意味着所有中断将在可预测的时间内被阻止（取决于设备产品规范中的NVMC规范和命令参数）。
*      -p_src缓冲区中的数据不应在@ref NRF_EVT_FLASH_OPERATION_SUCCESS之前修改
*        or the @ref 如果SoftDevice已启用，则已收到NRF_EVT_FLASH_OPERATION_ERROR。
*      -如果页面受到保护，则此调用将使SoftDevice在写入页面时触发硬故障。
*
*
* @param[in]  p_dst 指向要写入的闪存位置开始的指针。
* @param[in]  p_src 指向要写入数据的缓冲区的指针。
* @param[in]  size  要写入的32位字数。最大大小是一个flash页面中的单词数。有关详细信息，请参阅设备的产品规范。
*
* @retval ：：NRF_ERROR_INVALID_ADDR尝试写入不存在的闪存地址，或p_dst或p_src未对齐。
* @retval ：：NRF_ERROR_BUSY上一个命令尚未完成。
* @retval ：：NRF_ERROR_INVALID_LENGTH大小为0，或大于允许的最大大小。
* @retval ：：NRF_ERROR_FORBIDDEN尝试写入应用程序闪存区域外的地址。
* @retval ：：NRF_SUCCESS命令已被接受。
*/
SVCALL(SD_FLASH_WRITE, uint32_t, sd_flash_write(uint32_t * p_dst, uint32_t const * p_src, uint32_t size));


/**@brief 闪存擦除页面
*
* 擦除闪存页面的命令如果SoftDevice已启用：此调用将启动闪存访问命令，其完成情况将通过以下事件之一通知应用程序：
*      - @ref NRF_EVT_FLASH_OPERATION_SUCCESS-命令已成功完成。
*      - @ref NRF_EVT_FLASH_OPERATION_ERROR-无法启动命令。
*
* 如果SoftDevice未启用，则不会生成任何事件，擦除完成后，此调用将返回@ref NRF_SUCCESS
*
* @note
*      -在闪存擦除和写入期间，此调用将控制收音机和CPU，以确保它们不会干扰闪存访问。这意味着所有中断将在可预测的时间内被阻止（取决于设备产品规范中的NVMC规范和命令参数）。
*      -如果页面受到保护，则此调用将使SoftDevice在页面被擦除时触发硬故障。
*
*
* @param[in]  page_number           要擦除的页面的页码
*
* @retval ：：NRF_ERROR_INTERNAL如果由于内部错误而无法打开新会话。
* @retval ：：NRF_ERROR_INVALID_ADDR尝试擦除到不存在的闪存页。
* @retval ：：NRF_ERROR_BUSY上一个命令尚未完成。
* @retval ：：NRF_ERROR_FORBIDDEN尝试擦除应用程序闪存区域外的页面。
* @retval ：：NRF_SUCCESS命令已被接受。
*/
SVCALL(SD_FLASH_PAGE_ERASE, uint32_t, sd_flash_page_erase(uint32_t page_number));



/**@brief 为无线电时隙请求打开会话。
 *
 * @note 一次只能打开一个会话。
 * @note 当无线时隙开始时，将调用p_radio_signal_callback（@ref NRF_radio_callback_signal_TYPE_START）。此时，应用程序可以自由访问NRF_RADIO和NRF_TIMER0外围设备。
 * @note 每当发生NRF_TIMER0中断时，都会调用p_radio_signal_callback（@ref NRF_radio_callback_signal_TYPE_TIMER0）。
 * @note 每当发生NRF_radio中断时，都会调用p_radio_signal_callback（@ref NRF_radio_callback_signal_TYPE_radio）。
 * @note p_radio_signal_callback（）将以ARM中断优先级0调用。这意味着不能从p_radio_signal_callback（）使用任何sd_API调用。
 *
 * @param[in] p_radio_signal_callback 信号回调。
 *
 * @retval ：：NRF_ERROR_INVALID_ADDR p_radio_signal_callback是无效的函数指针。
 * @retval ：：NRF_ERROR_BUSY如果无法打开会话。
 * @retval ：：NRF_ERROR_INTERNAL如果由于内部错误而无法打开新会话。
 * @retval ：：NRF_SUCCESS否则。
 */
 SVCALL(SD_RADIO_SESSION_OPEN, uint32_t, sd_radio_session_open(nrf_radio_signal_callback_t p_radio_signal_callback));

/**@brief 关闭无线电时隙请求的会话。
 *
 * @note 任何当前无线电时隙都将在会话关闭之前完成。
 * @note 如果在会话关闭时安排了无线电时隙，则该时隙将被取消。
 * @note 在收到@ref NRF_EVT_RADIO_session_closed事件之前，应用程序无法认为会话已关闭。
 *
 * @retval ：：NRF_ERROR_FORBIDDEN如果会话未打开。
 * @retval ：：NRF_ERROR_BUSY如果会话当前正在关闭。
 * @retval ：：NRF_SUCCESS否则。
 */
 SVCALL(SD_RADIO_SESSION_CLOSE, uint32_t, sd_radio_session_close(void));

/**@brief 请求无线电时隙。
 *
 * @note 请求类型由p_request->request_type确定，可以是@ref NRF_RADIO_REQ_type_EARLIEST之一
 *       and @ref NRF_ RADIO_REQ_类型_正常。会话中的第一个请求必须始终为@ref NRF_RADIO_REQ_type_EARLIEST类型。
 * @note 对于正常请求（@ref NRF_RADIO_REQ_TYPE_normal），无线时隙的开始时间由p_request->distance e_us指定，并相对于前一时隙的开始给出。
 * @note p_request->distance_us太小将导致@ref NRF_EVT_RADIO_BLOCKED事件。
 * @note 时间表安排得太近将导致@ref NRF_EVT_RADIO_BLOCKED事件。
 * @note 有关无线时隙调度、距离和长度的更多信息，请参阅SoftDevice规范。
 * @note 如果在调用此函数后100毫秒内未找到第一个无线电时隙的机会，则不会对其进行调度，而是发送@ref NRF_EVT_radio_BLOCKED事件。然后，应用程序可以尝试再次调度第一无线电时隙。
 * @note 成功的请求将导致nrf_readio_signal_callback_t（@ref nrf_radio_callback_signal_TYPE_START）。
 *       Unsuccessful requests will result in a @ref NRF_EVT_RADIO_BLOCKED事件，请参阅@ref NRF_SOC_EVTS。
 * @note 无线电时隙开始时间的抖动为+/-@ref NRF_radio_start_jitter_US。
 * @note nrf_readio_signal_callback_t（@ref nrf_radio_callback_signal_TYPE_START）调用相对于指定的无线电时隙开始具有延迟，但这不会影响时隙的实际开始时间。
 * @note NRF_TIMER0在无线电时隙开始时复位，并从高频（16MHz）时钟源以1MHz计时。如果p_request->hfclk_force_xtal为真，则保证从外部晶体对高频时钟进行计时。
 * @note SoftDevice在无线电时隙期间既不会访问NRF_RADIO外围设备，也不会访问NRD_TIMER0外围设备。
 *
 * @param[in] p_request 指向请求参数的指针。
 *
 * @retval ：：NRF_ERROR_FORBIDDEN如果会话未打开或会话未空闲。
 * @retval ：：NRF_ERROR_INVALID_ADDR如果p_request指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM如果p_request的参数无效。
 * @retval ：：NRF_SUCCESS否则。
 */
 SVCALL(SD_RADIO_REQUEST, uint32_t, sd_radio_request(nrf_radio_request_t const * p_request));

/**@brief 受SoftDevice保护的写入寄存器
 *
 * 此函数写入受SoftDevice写保护的寄存器。有关受SoftDevice保护的寄存器的详细信息，请参阅SoftDevice规范。此功能可写入以下受保护的外围设备：
 *  - ACL
 *
 * @note 可以直接读取受保护的寄存器。
 * @note 一次写入的寄存器将在第二次设置时返回@ref NRF_SUCCESS，即使寄存器中的值没有改变。有关寄存器属性的详细信息，请参阅产品规范。
 *
 * @param[in]  p_register 指向要写入的寄存器的指针。
 * @param[in]  value 要写入寄存器的值。
 *
 * @retval ：：NRF_ERROR_INVALID_ADDR此函数无法写入要求的寄存器。
 * @retval ：：NRF_SUCCESS值已成功写入寄存器。
 *
 */
SVCALL(SD_PROTECTED_REGISTER_WRITE, uint32_t, sd_protected_register_write(volatile uint32_t * p_register, uint32_t value));

/**@} */

#ifdef __cplusplus
}
#endif
#endif // NRF_SOC_H__

/**@} */

