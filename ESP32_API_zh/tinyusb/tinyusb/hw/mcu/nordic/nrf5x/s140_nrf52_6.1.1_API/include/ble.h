/*
 * 版权所有（c）2012-2018，Nordic Semiconductor ASA保留所有权利。
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
  @addtogroup BLE_COMMON BLE SoftDevice公用@{
  @defgroup ble_api事件、类型定义和api调用@{

  @BLE SoftDevice的简短模块无关事件、类型定义和API调用。

 */

#ifndef BLE_H__
#define BLE_H__

#include <stdint.h>
#include "nrf_svc.h"
#include "nrf_error.h"
#include "ble_err.h"
#include "ble_gap.h"
#include "ble_l2cap.h"
#include "ble_gatt.h"
#include "ble_gattc.h"
#include "ble_gatts.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup BLE_COMMON_ENUMERATIONS枚举
 * @{ */

/**
 * @brief 通用API SVC编号。
 */
enum BLE_COMMON_SVCS
{
  SD_BLE_ENABLE = BLE_SVC_BASE,         /**<启用并初始化BLE堆栈*/
  SD_BLE_EVT_GET,                       /**<从挂起事件队列中获取事件。*/
  SD_BLE_UUID_VS_ADD,                   /**<添加供应商特定的基本UUID。*/
  SD_BLE_UUID_DECODE,                   /**<解码UUID字节。*/
  SD_BLE_UUID_ENCODE,                   /**<编码UUID字节。*/
  SD_BLE_VERSION_GET,                   /**<获取本地版本信息（公司ID、链接层版本、链接层子版本）。*/
  SD_BLE_USER_MEM_REPLY,                /**<用户记忆回复。*/
  SD_BLE_OPT_SET,                       /**<设置BLE选项。*/
  SD_BLE_OPT_GET,                       /**<获取BLE选项。*/
  SD_BLE_CFG_SET,                       /**<向BLE堆栈添加配置。*/
  SD_BLE_UUID_VS_REMOVE,                /**<删除供应商特定的基本UUID。*/
};

/**
 * @brief BLE模块独立事件ID。
 */
enum BLE_COMMON_EVTS
{
  BLE_EVT_USER_MEM_REQUEST = BLE_EVT_BASE + 0,   /**<用户内存请求@参考文件_ evt_user_mem_request_t*/
  BLE_EVT_USER_MEM_RELEASE = BLE_EVT_BASE + 1,   /**<用户内存释放@参考文件_evt_user_mem_release_t*/
};

/**@brief BLE连接配置ID。
 *
 * 唯一标识连接配置的ID。
 */
enum BLE_CONN_CFGS
{
    BLE_CONN_CFG_GAP   = BLE_CONN_CFG_BASE + 0, /**<BLE GAP特定连接配置。*/
    BLE_CONN_CFG_GATTC = BLE_CONN_CFG_BASE + 1, /**<BLE GATTC特定连接配置。*/
    BLE_CONN_CFG_GATTS = BLE_CONN_CFG_BASE + 2, /**<BLE GATTS特定连接配置。*/
    BLE_CONN_CFG_GATT  = BLE_CONN_CFG_BASE + 3, /**<BLE GATT特定连接配置。*/
    BLE_CONN_CFG_L2CAP = BLE_CONN_CFG_BASE + 4, /**<BLE L2CAP特定连接配置。*/
};

/**@brief BLE通用配置ID。
 *
 * 唯一标识公共配置的ID。
 */
enum BLE_COMMON_CFGS
{
  BLE_COMMON_CFG_VS_UUID = BLE_CFG_BASE, /**<供应商特定的基本UUID配置*/
};

/**@brief 通用选项ID。唯一标识公共选项的ID。
 */
enum BLE_COMMON_OPTS
{
  BLE_COMMON_OPT_PA_LNA          = BLE_OPT_BASE + 0, /**<PA和LNA选项*/
  BLE_COMMON_OPT_CONN_EVT_EXT    = BLE_OPT_BASE + 1, /**<扩展连接事件选项*/
  BLE_COMMON_OPT_EXTENDED_RC_CAL = BLE_OPT_BASE + 2, /**<扩展RC校准选项*/
  BLE_COMMON_OPT_ADV_SCHED_CFG   = BLE_OPT_BASE + 3, /**<播发程序角色调度配置选项*/
};

/** @} */

/** @addtogroup BLE_COMMON_DEFINES定义
 * @{ */

/** @brief  BLE事件所需的指针对齐。
*/
#define BLE_EVT_PTR_ALIGNMENT    4

/** @brief  保留两个参数的最大值。
*/
#define BLE_MAX(a, b) ((a) < (b) ? (b) : (a))

/** @brief  BLE事件的最大可能长度。
 * @note 在任何连接配置中，@ref ble_gatt_conn_cfg_t:：att_mtu使用的最高值都应用作参数。如果尚未为任何连接配置该值，则必须改用@ref BLE_GATT_ATT_MTU_DEFAULT。
*/
#define BLE_EVT_LEN_MAX(ATT_MTU) ( \
    offsetof(ble_evt_t, evt.gattc_evt.params.prim_srvc_disc_rsp.services) + ((ATT_MTU) - 1) / 4 * sizeof(ble_gattc_service_t) \
)

/** @defgroup ADV_SCHED_CFG播发程序角色调度配置
 * @{ */
#define ADV_SCHED_CFG_DEFAULT  0  /**<默认广告客户角色调度配置。*/
#define ADV_SCHED_CFG_IMPROVED 1  /**<改进的广告客户角色调度配置，减少了内务管理时间。*/
/** @} */

/** @defgroup BLE_USER_MEM_TYPES用户内存类型
 * @{ */
#define BLE_USER_MEM_TYPE_INVALID               0x00  /**<无效的用户内存类型。*/
#define BLE_USER_MEM_TYPE_GATTS_QUEUED_WRITES   0x01  /**<GATTS队列写入的用户内存。*/
/** @} */

/** @defgroup BLE_UUID_VS_COUNTS供应商特定的基本UUID计数@{
 */
#define BLE_UUID_VS_COUNT_DEFAULT 10  /**<默认VS UUID计数。*/
#define BLE_UUID_VS_COUNT_MAX     254 /**<最大VS UUID计数。*/
/** @} */

/** @defgroup BLE_COMMON_CFG_DEFAULT配置默认值@{
 */
#define BLE_CONN_CFG_TAG_DEFAULT  0    /**<Default configuration tag，SoftDevice默认连接配置。*/

/** @} */

/** @} */

/** @addtogroup BLE_COMMON_STRUCTURES结构
 * @{ */

/**@brief 用户内存块。*/
typedef struct
{
  uint8_t          *p_mem;      /**<指向用户内存块开头的指针。*/
  uint16_t          len;        /**<用户内存块的字节长度。*/
} ble_user_mem_block_t;

/**@brief @ref BLE_EVT_USER_MEM_REQUEST的事件结构。*/
typedef struct
{
  uint8_t                     type;     /**<用户内存类型，请参阅@ref BLE_User_MEM_TYPES。*/
} ble_evt_user_mem_request_t;

/**@brief @ref BLE_EVT_USER_MEM_RELEASE的事件结构。*/
typedef struct
{
  uint8_t                     type;       /**<用户内存类型，请参阅@ref BLE_User_MEM_TYPES。*/
  ble_user_mem_block_t        mem_block;  /**<用户内存块*/
} ble_evt_user_mem_release_t;

/**@brief 与特定功能模块无关的事件的事件结构。*/
typedef struct
{
  uint16_t conn_handle;                                 /**<发生此事件的连接句柄。*/
  union
  {
    ble_evt_user_mem_request_t      user_mem_request;    /**<用户内存请求事件参数。*/
    ble_evt_user_mem_release_t      user_mem_release;    /**<用户内存释放事件参数。*/
  } params;                                              /**<事件参数联合。*/
} ble_common_evt_t;

/**@brief BLE事件标题。*/
typedef struct
{
  uint16_t evt_id;                /**<BLE_<模块>_EVT系列的值。*/
  uint16_t evt_len;               /**<包含此标头的八位字节长度。*/
} ble_evt_hdr_t;

/**@brief 通用BLE事件类型，包装模块特定的事件报告。*/
typedef struct
{
  ble_evt_hdr_t header;           /**<事件标题。*/
  union
  {
    ble_common_evt_t  common_evt; /**<公共事件，BLE_evt_*系列中的evt_id。*/
    ble_gap_evt_t     gap_evt;    /**<GAP起源事件，BLE_GAP_evt_*系列中的evt_id。*/
    ble_gattc_evt_t   gattc_evt;  /**<GATT客户端发起的事件，BLE_GATTC_evt*系列中的evt_id。*/
    ble_gatts_evt_t   gatts_evt;  /**<GATT服务器发起的事件，BLE_GATTS_evt*系列中的evt_id。*/
    ble_l2cap_evt_t   l2cap_evt;  /**<L2CAP起源事件，BLE_L2CAP_evt*系列中的evt_id。*/
  } evt;                          /**<事件联合。*/
} ble_evt_t;


/**
 * @brief 版本信息。
 */
typedef struct
{
  uint8_t   version_number;    /**<链接层版本号。看见https://www.bluetooth.org/en-us/specification/assigned-numbers/link-layer指定值。*/
  uint16_t  company_id;        /**<公司ID，Nordic Semiconductor的公司ID为89（0x0059）(https://www.bluetooth.org/apps/content/Default.aspx?doc_id=49708). */
  uint16_t  subversion_number; /**<链路层子版本号，对应于SoftDevice配置ID或固件ID（FWID）。*/
} ble_version_t;

/**
 * @brief PA和LNA的配置参数。
 */
typedef struct
{
     uint8_t enable :1;      /**<启用此放大器的切换*/
     uint8_t active_high :1; /**<将引脚设置为高电平*/
     uint8_t gpio_pin :6;    /**<用于切换此放大器的GPIO引脚*/
} ble_pa_lna_cfg_t;

/**
 * @brief PA和LNA GPIO切换配置
 *
 * 此选项可将SoftDevice配置为在无线电处于活动状态以与功率放大器和/或低噪声放大器一起使用时切换引脚。
 *
 * 通过使用两个PPI通道和一个GPIOTE通道实现引脚切换。硬件信道ID由应用程序提供，只要启用任何PA/LNA切换，就应视为保留。
 *
 * @note  @此选项不支持ref sd_ble_opt_get。
 * @note  在无线电正在使用时（即任何角色都处于活动状态）设置此选项可能会产生未定义的后果，应用程序必须避免。
 */
typedef struct
{
   ble_pa_lna_cfg_t pa_cfg;   /**<功率放大器配置*/
   ble_pa_lna_cfg_t lna_cfg;  /**<低噪声放大器配置*/

   uint8_t ppi_ch_id_set;     /**<用于无线电引脚设置的PPI信道*/
   uint8_t ppi_ch_id_clr;     /**<用于无线电引脚清除的PPI信道*/
   uint8_t gpiote_ch_id;      /**<GPIOTE信道用于无线电引脚切换*/
} ble_common_opt_pa_lna_t;

/**
 * @brief 扩展BLE连接事件的配置。
 *
 * 启用后，SoftDevice将在可能时动态扩展连接事件。
 *
 * The connection event length is controlled by the connection configuration as set by @ref ble_gap_conn_cfg_t:：事件长度。如果在下一个连接间隔开始之前有时间发送另一个数据包对，并且与请求无线电时间的其他BLE角色没有冲突，则可以延长连接事件。
 *
 * @note @此选项不支持ref sd_ble_opt_get。
 */
typedef struct
{
   uint8_t enable : 1; /**<启用扩展BLE连接事件，默认情况下禁用。*/
} ble_common_opt_conn_evt_ext_t;

/**
 * @brief 启用/禁用扩展RC校准。
 *
 * If extended RC calibration is enabled and the internal RC oscillator (@ref NRF_CLOCK_LF_SRC_RC）用作SoftDevice LFCLK源，如果未接收到两个连续数据包，则作为外围设备的SoftDevice将默认尝试增加接收窗口。如果发现由于时钟漂移而没有接收到数据包，则开始RC校准。此校准是由@ref sd_softdevice_enable（）配置的定期校准的补充。当仅使用外围设备连接时，由于外围设备能够自动检测和调整时钟漂移，并根据需要进行校准，因此可以以更长的间隔配置周期校准。
 *
 * 如果禁用了扩展RC校准，并且内部RC振荡器用作SoftDevice LFCLK源，则RC振荡器将按照@ref sd_SoftDevice_enable（）的配置定期校准。
 *
 * @note @此选项不支持ref sd_ble_opt_get。
 */
typedef struct
{
   uint8_t enable : 1; /**<启用扩展RC校准，默认启用。*/
} ble_common_opt_extended_rc_cal_t;

/**
 * @brief BLE广告客户角色调度的配置。
 *
 * @note @此选项不支持ref sd_ble_opt_get。
 */
typedef struct
{
  uint8_t sched_cfg;  /**<参见@ref ADV_SCHED_CFG。*/
} ble_common_opt_adv_sched_cfg_t;

/**@brief 普通期权的期权结构。*/
typedef union
{
  ble_common_opt_pa_lna_t          pa_lna;          /**<用于控制PA和LNA引脚切换的参数。*/
  ble_common_opt_conn_evt_ext_t    conn_evt_ext;    /**<用于启用扩展连接事件的参数。*/
  ble_common_opt_extended_rc_cal_t extended_rc_cal; /**<启用扩展RC校准的参数。*/
  ble_common_opt_adv_sched_cfg_t   adv_sched_cfg;   /**<用于配置广告客户角色调度的参数。*/
} ble_common_opt_t;

/**@brief 通用BLE选项类型，包装模块特定选项。*/
typedef union
{
  ble_common_opt_t  common_opt;         /**<COMMON选项，@ref BLE_COMMON_OPS系列中的opt_id。*/
  ble_gap_opt_t     gap_opt;            /**<GAP选项，@ref BLE_GAP_OPTS系列中的opt_id。*/
} ble_opt_t;

/**@brief BLE连接配置类型，包装模块特定配置，设置为
 * @ref sd_ble_cfg_set设置。
 *
 * @note 不必设置连接配置。如果未设置任何配置，或者设置的连接配置少于启用的连接，则将自动为其余连接添加默认连接配置。使用默认配置创建连接时，@ref BLE_CONN_CFG_TAG_default应用于
 * place of @ref ble_conn_cfg_t:：conn_cfg_tag。
 *
 * @sa sd_ble_gap_adv_start（）
 * @sa sd_ble_gap_connect（）
 *
 * @mscs
 * @mmsc{@ref BLE_CONN_CFG}
 * @endmscs

 */
typedef struct
{
  uint8_t              conn_cfg_tag;        /**< 它可以与
                                                 @ref sd_ble_gap_adv_start（）和@ref sd_ble _gap_connect（）调用在创建连接时选择此配置。对于添加的所有连接配置必须不同，而不是@ref BLE_CONN_CFG_TAG_DEFAULT。*/
  union {
    ble_gap_conn_cfg_t   gap_conn_cfg;      /**<GAP连接配置，cfg_id为@ref BLE_CONN_cfg_GAP。*/
    ble_gattc_conn_cfg_t gattc_conn_cfg;    /**<GATTC连接配置，cfg_id为@ref BLE_CONN_cfg_GATTC。*/
    ble_gatts_conn_cfg_t gatts_conn_cfg;    /**<GATTS连接配置，cfg_id为@ref BLE_CONN_cfg_GATTS。*/
    ble_gatt_conn_cfg_t  gatt_conn_cfg;     /**<GATT连接配置，cfg_id为@ref BLE_CONN_cfg_GATT。*/
    ble_l2cap_conn_cfg_t l2cap_conn_cfg;    /**＜L2CAP连接配置，cfg_id为@ref BLE_CONN_cfg_L2CAP。*/
  } params;                                 /**<连接配置联合。*/
} ble_conn_cfg_t;

/**
 * @brief 配置供应商特定的基本UUID，用@ref sd_ble_cfg_set设置。
 *
 * @retval ：：NRF_ERROR_INVALID_PARAM配置的UUID太多。
 */
typedef struct
{
  uint8_t vs_uuid_count; /**< 要为其分配内存的128位供应商特定基UUID基的数量。
                              默认值为@ref BLE_UUID_VS_COUNT_Default。最大值为@ref BLE_UUID_VS_COUNT_MAX。*/
} ble_common_cfg_vs_uuid_t;

/**@brief 通用BLE配置类型，包装通用配置。*/
typedef union
{
  ble_common_cfg_vs_uuid_t  vs_uuid_cfg;  /**<供应商特定的基本UUID配置，cfg_id为@ref BLE_COMMON_cfg_VS_UID。*/
} ble_common_cfg_t;

/**@brief BLE配置类型，包装模块特定配置。*/
typedef union
{
  ble_conn_cfg_t    conn_cfg;   /**<连接特定配置，@ref BLE_CONN_CFGS系列中的cfg_id。*/
  ble_common_cfg_t  common_cfg; /**<全局通用配置，@ref BLE_common_CFGS系列中的cfg_id。*/
  ble_gap_cfg_t     gap_cfg;    /**<全局GAP配置，@ref BLE_GAP_CFGS系列中的cfg_id。*/
  ble_gatts_cfg_t   gatts_cfg;  /**<全局GATTS配置，@ref BLE_GATTS_CFGS系列中的cfg_id。*/
} ble_cfg_t;

/** @} */

/** @addtogroup BLE_COMMON_FUNCTIONS函数
 * @{ */

/**@brief 启用BLE堆栈
 *
 * @param[in, out] p_app_ram_base指向包含应用程序ram区域起始地址（app_ram_base）的变量的指针。返回时，这将包含SoftDevice为此配置所需的应用程序RAM区域的最小起始地址。
 *
 * @note 具有相同主要版本号的SoftDevices之间，特定配置的内存需求不会增加。
 *
 * @note 在运行时，IC的RAM分为两个区域：SoftDevice RAM区域位于0x20000000和APP_RAM_BASE-1之间，应用程序的RAM区域位于APP_RAM-BASE和调用堆栈的开始之间。
 *
 * @details 此调用初始化BLE堆栈，在此之前不能调用除@ref sd_BLE_cfg_set之外的任何BLE相关函数。
 *
 * @mscs
 * @mmsc{@ref BLE_COMMON_ENABLE}
 * @endmscs
 *
 * @retval ：：NRF_SUCCESS BLE堆栈已成功初始化。
 * @retval ：：NRF_ERROR_INVALID_STATE BLE堆栈已初始化，无法重新初始化。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效或未充分对齐。
 * @retval ：：NRF_ERROR_NO_MEM以下一项或多项为真：
 *                                    -*p_app_ram_base分配给SoftDevice的内存量不足以满足此配置的内存需求。检查p_app_ram_base并相应地设置应用程序ram区域的起始地址。
 *                                    -SoftDevice RAM区域的动态部分大于当前不支持的64kB。
 * @retval ：：NRF_ERROR_RESOURCES使用@ref sd_ble_cfg_set配置的L2CAP通道总数太大。
 */
SVCALL(SD_BLE_ENABLE, uint32_t, sd_ble_enable(uint32_t * p_app_ram_base));

/**@brief 为BLE堆栈添加配置
 *
 * @param[in] cfg_id              配置ID，请参见@ref BLE_CONN_CFGS、@ref BLE_COMMON_CFGS，@ref BLE_GAP_CFGS或@ref BLE_GATTS_CFGS。
 * @param[in] p_cfg               指向包含配置值的ble_cfg_t结构的指针。
 * @param[in] app_ram_base        应用程序RAM区域的起始地址（APP_RAM_BASE）。
 *                                See @ref sd_ble_enable获取有关APP_RAM_BASE的详细信息。
 *
 * @note 具有相同主要版本号的SoftDevices之间，特定配置的内存需求不会增加。
 *
 * @note 如果配置设置了多次，则最后一次设置将在
 *       @ref sd_ble_enable。
 *
 * @note BLE堆栈中未配置@ref sd_BLE_cfg_set的任何部分都将具有默认配置。
 *
 * @note @当SoftDevice的ble部分未启用时（请参见@ref sd_SoftDevice_enable），可以在启用SoftDevice时的任何时间调用ref sd_ble_cfg_set。
 *
 * @note 配置结构中描述了配置的错误代码。
 *
 * @mscs
 * @mmsc{@ref BLE_COMMON_ENABLE}
 * @endmscs
 *
 * @retval ：：NRF_SUCCESS已成功添加配置。
 * @retval ：：NRF_ERROR_INVALID_STATE BLE堆栈已初始化。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效或未充分对齐。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的cfg_id无效。
 * @retval ：：NRF_ERROR_NO_MEM app_ram_base分配给SoftDevice的内存量不足以满足此配置的内存需求。
 */
SVCALL(SD_BLE_CFG_SET, uint32_t, sd_ble_cfg_set(uint32_t cfg_id, ble_cfg_t const * p_cfg, uint32_t app_ram_base));

/**@brief 从挂起事件队列中获取事件。
 *
 * @param[out] p_dest 指向要用事件填充的缓冲区的指针，或NULL以检索事件长度。此缓冲区<b>必须与@ref BLE_EVT_PTR_ALIGNMENT</b>定义的扩展对齐。缓冲区应解释为@ref ble_evt_t结构。
 * @param[in, out] p_len指针缓冲区的长度，返回时用事件长度填充。
 *
 * @details 此调用允许应用程序从BLE堆栈中提取BLE事件。通过触发SD_EVT_IRQn中断，向应用程序发信号通知BLE堆栈中有事件可用。应用程序可以自由选择是从线程模式（主上下文）调用该函数，还是直接从映射到SD_EVT_IRQn的中断服务例程调用该函数。然而，在任何情况下，由于BLE堆栈以比应用程序更高的优先级运行，因此每次引发SD_EVT_IRQn时都应在循环中调用该函数（直到返回@ref NRF_ERROR_NOT_FOUND），以确保从BLE堆栈中提取所有可用事件。否则，可能会在应用程序不知道这一事实的情况下将事件留在内部队列中。
 *
 * 调整p_dest缓冲区的大小同样重要，因为应用程序需要提供将事件复制到应用程序内存所需的所有内存。如果所提供的缓冲器不足以容纳事件的全部内容，
 * @ref 将返回NRF_ERROR_DATA_SIZE，然后应用程序可以使用更大的缓冲区大小再次调用。
 * The maximum possible event length is defined by @ref BLE_EVT_LEN_MAX。应用程序还可以通过提供p_dest作为NULL指针并在返回时检查p_len的值来“窥探”事件长度：
 *
 *     \代码uint16_t len；错误代码=sd_ble_evt_get（NULL，&len）；\结束代码
 *
 * @mscs
 * @mmsc{@ref BLE_COMMON_IRQ_EVT_MSC}
 * @mmsc{@ref BLE_COMMON_THREAD_EVT_MSC}
 * @endmscs
 *
 * @retval ：：NRF_SUCCESS事件被拉入并存储到提供的缓冲区中。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效或未充分对齐。
 * @retval ：：NRF_ERROR_NOT_FOUND没有可提取的事件。
 * @retval ：：NRF_ERROR_DATA_SIZE事件已就绪，但无法放入提供的缓冲区。
 */
SVCALL(SD_BLE_EVT_GET, uint32_t, sd_ble_evt_get(uint8_t *p_dest, uint16_t *p_len));


/**@brief 添加供应商特定的基本UUID。
 *
 * @details 此调用使应用程序能够将特定于供应商的基本UUID添加到BLE堆栈的表中，以便以后与所有其他模块和API一起使用。这样，当处理16位和128位uuid时，应用程序就可以使用更短的24位@ref ble_uuid_t格式，而不必检查长度和代码路径。这通过扩展蓝牙SIG标准基本UUID用于所有其他128位UUID的分组机制来实现。@ref ble_uuid_t结构中的类型字段是一个索引（相对于
 * @ref BLE_UUID_TYPE_VENDOR_BEGIN）添加到由多次调用此函数填充的表中，并且相同结构中的UUID字段包含索引12和13处的2个字节。因此，应用程序可用的128位UUID的数量是借助此函数添加的供应商特定UUID的数乘以65536，尽管限于为所提供的数组中的每个条目修改字节12和13。
 *
 * @note 提供的UUID的字节12和13不会在内部使用，因为它们总是被@ref ble_UUID_t中的16位UUID字段替换。
 *
 * @note 如果BLE堆栈的内部表中已经存在UUID，则将在p_UUID_type中返回相应的索引，并返回@ref NRF_SUCCESS错误代码。
 *
 * @param[in]  p_vs_uuid    指向16个八位字节（128位）小端供应商特定基本UUID的指针，忽略字节12和13。
 * @param[out] p_uuid_type  指向uint8_t的指针，其中将存储与此uuid对应的@ref ble_uuid_t中的类型字段。
 *
 * @retval ：：NRF_SUCCESS成功添加供应商特定的基本UUID。
 * @retval ：：NRF_ERROR_INVALID_ADDR如果p_vs_uuid或p_uuid_type为NULL或无效。
 * @retval ：：NRF_ERROR_NO_MEM如果VS UUID没有更多可用插槽。
 */
SVCALL(SD_BLE_UUID_VS_ADD, uint32_t, sd_ble_uuid_vs_add(ble_uuid128_t const *p_vs_uuid, uint8_t *p_uuid_type));


/**@brief 删除供应商特定的基本UUID。
 * 
 * @details 此调用将删除添加了@ref sd_ble_UUID_vs_add的供应商特定基本UUID。此函数允许应用程序重用为供应商特定的基本UUID分配的内存。
 *
 * @note 当前，只能在p_uuid_type设置为@ref BLE_uuid_type_UNKNOWN或最后添加的uuid类型的情况下调用此函数。
 *
 * @param[in]  p_uuid_type  指向uint8_t的指针，其中@ref ble_uuid_t:：type中的类型字段对应于要删除的uuid类型。如果类型设置为@ref BLE_UUID_type_UNKNOWN，或指针为NULL，则将删除最后一个特定于供应商的基本UUID。
 * @param[out] p_uuid_type  指向uint8_t的指针，其中@ref ble_uuid_t中的类型字段对应于删除的uuid类型。如果函数返回失败，则它包含ATT服务器正在使用的最后一种类型。
 *
 * @retval ：：NRF_SUCCESS成功删除供应商特定的基本UUID。
 * @retval ：：NRF_ERROR_INVALID_ADDR如果p_uuid_type无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM如果p_uuid_type指向无效的uuid类型。
 * @retval ：：NRF_ERROR_FORBIDDEN如果ATT服务器正在使用供应商特定的基本UUID。
 */

SVCALL(SD_BLE_UUID_VS_REMOVE, uint32_t, sd_ble_uuid_vs_remove(uint8_t *p_uuid_type));


/** @brief 将小端原始UUID字节（16位或128位）解码为24位@ref ble_UUID_t结构。
 *
 * @details p_UUID_le的原始UUID字节（不包括字节12和13（即字节0-11和14-15））与填充有@ref sd_ble_UUID_vs_add的供应商特定基本UUID表的每个条目中的对应UUID进行比较，以查找匹配。如果存在这样的匹配，则返回字节12和13作为p_uuid->uuid和索引
 * relative to @ref BLE_UUID_TYPE_VENDOR_BEGIN作为p_UUID->类型。
 *
 * @note 如果提供的UUID长度为2，则此调用设置的类型将始终为@ref BLE_UUID_type_BLE。
 *
 * @param[in]   uuid_le_len p_uuid_le指向的缓冲区的字节长度（必须为2或16字节）。
 * @param[in]   p_uuid_le   指向小端原始UUID字节的指针。
 * @param[out]  p_uuid      指向要填充的@ref ble_uuid_t结构的指针。
 *
 * @retval ：：NRF_SUCCESS成功解码为@ref ble_uuid_t结构。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_LENGTH UUID长度无效。
 * @retval ：：NRF_ERROR_NOT_FOUND对于128位UUID，UUID填充表中没有匹配项。
 */
SVCALL(SD_BLE_UUID_DECODE, uint32_t, sd_ble_uuid_decode(uint8_t uuid_le_len, uint8_t const *p_uuid_le, ble_uuid_t *p_uuid));


/** @brief 将@ref ble_uuid_t结构编码为小端原始uuid字节（16位或128位）。
 *
 * @note 指向目标缓冲区p_uuid_le的指针可能为NULL，在这种情况下，只计算p_uuid的有效性和大小。
 *
 * @param[in]   p_uuid        指向将编码为字节的@ref ble_uuid_t结构的指针。
 * @param[out]  p_uuid_le_len 指向将用编码长度（2或16字节）填充的uint8_t的指针。
 * @param[out]  p_uuid_le     指向将存储小端原始UUID字节（2或16）的缓冲区的指针。
 *
 * @retval ：：NRF_SUCCESS成功编码到缓冲区。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM UUID类型无效。
 */
SVCALL(SD_BLE_UUID_ENCODE, uint32_t, sd_ble_uuid_encode(ble_uuid_t const *p_uuid, uint8_t *p_uuid_le_len, uint8_t *p_uuid_le));


/**@brief 获取版本信息。
 *
 * @details 此调用允许应用程序获取BLE堆栈版本信息。
 *
 * @param[out] p_version 指向要填充的ble_version_t结构的指针。
 *
 * @retval ：：NRF_SUCCESS版本信息已成功存储。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_BUSY BLE堆栈忙（通常执行本地启动的断开过程）。
 */
SVCALL(SD_BLE_VERSION_GET, uint32_t, sd_ble_version_get(ble_version_t *p_version));


/**@brief 提供用户内存块。
 *
 * @note 此调用只能用作对向应用程序发出的@ref BLE_EVT_USER_MEM_REQUEST事件的响应。
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] p_block 指向用户内存块结构的指针，如果内存由应用程序管理，则为NULL。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_PEER_CANCEL_MSC}
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_NOBUF_AUTH_MSC}
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_NOBUF_NOAUTH_MSC}
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_BUF_AUTH_MSC}
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_BUF_NOAUTH_MSC}
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_QUEUE_FULL_MSC}
 * @endmscs
 *
 * @retval ：：NRF_SUCCESS成功将响应排队到对等方。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_BUSY堆栈正忙，请处理挂起的事件并重试。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_LENGTH提供的用户内存块长度无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效或没有挂起的用户内存请求。
 */
SVCALL(SD_BLE_USER_MEM_REPLY, uint32_t, sd_ble_user_mem_reply(uint16_t conn_handle, ble_user_mem_block_t const *p_block));

/**@brief 设置BLE选项。
 *
 * @details 此调用允许应用程序设置选项的值。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PERIPH_BONDING_STATIC_PK_MSC}
 * @endmscs
 *
 * @param[in] opt_id 选项ID，请参见@ref BLE_COMMON_OPTS和@ref BLE_GAP_OPTS。
 * @param[in] p_opt 指向包含选项值的ble_opt_t结构的指针。
 *
 * @retval ：：NRF_SUCCESS选项设置成功。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效，请检查参数限制和约束。
 * @retval ：：NRF_ERROR_INVALID_STATE此时无法设置参数。
 * @retval ：：NRF_ERROR_BUSY BLE堆栈忙或上一个过程尚未完成。
 */
SVCALL(SD_BLE_OPT_SET, uint32_t, sd_ble_opt_set(uint32_t opt_id, ble_opt_t const *p_opt));


/**@brief 获取BLE选项。
 *
 * @details 此调用允许应用程序检索选项的值。
 *
 * @param[in] opt_id 选项ID，请参见@ref BLE_COMMON_OPTS和@ref BLE_GAP_OPTS。
 * @param[out] p_opt 指向要填充的ble_opt_t结构的指针。
 *
 * @retval ：：成功检索到NRF_SUCCESS选项。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效，请检查参数限制和约束。
 * @retval ：：NRF_ERROR_INVALID_STATE此时无法检索参数。
 * @retval ：：NRF_ERROR_BUSY BLE堆栈忙或上一个过程尚未完成。
 * @retval ：：NRF_ERROR_NOT_SUPPORTED不支持此选项。
 *
 */
SVCALL(SD_BLE_OPT_GET, uint32_t, sd_ble_opt_get(uint32_t opt_id, ble_opt_t *p_opt));

/** @} */
#ifdef __cplusplus
}
#endif
#endif /* BLE_H__ */

/**
  @} @}
*/

