/*
 * 版权所有（c）2011-2018，Nordic Semiconductor ASA保留所有权利。
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
  @addtogroup BLE_GAP通用访问配置文件（GAP）@{
  @GAP接口的简要定义和原型。
 */

#ifndef BLE_GAP_H__
#define BLE_GAP_H__

#include <stdint.h>
#include "nrf_svc.h"
#include "nrf_error.h"
#include "ble_hci.h"
#include "ble_ranges.h"
#include "ble_types.h"
#include "ble_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@addtogroup BLE_GAP_ENUMERATIONS枚举
 * @{ */

/**@brief GAP API SVC编号。
 */
enum BLE_GAP_SVCS
{
  SD_BLE_GAP_ADDR_SET              = BLE_GAP_SVC_BASE,       /**<设置自己的蓝牙地址。*/
  SD_BLE_GAP_ADDR_GET              = BLE_GAP_SVC_BASE + 1,   /**<获取自己的蓝牙地址。*/
  SD_BLE_GAP_WHITELIST_SET         = BLE_GAP_SVC_BASE + 2,   /**<设置活动白名单。*/
  SD_BLE_GAP_DEVICE_IDENTITIES_SET = BLE_GAP_SVC_BASE + 3,   /**<设置设备标识列表。*/
  SD_BLE_GAP_PRIVACY_SET           = BLE_GAP_SVC_BASE + 4,   /**<设置隐私设置*/
  SD_BLE_GAP_PRIVACY_GET           = BLE_GAP_SVC_BASE + 5,   /**<获取隐私设置*/
  SD_BLE_GAP_ADV_SET_CONFIGURE     = BLE_GAP_SVC_BASE + 6,   /**<配置广告集。*/
  SD_BLE_GAP_ADV_START             = BLE_GAP_SVC_BASE + 7,   /**<开始广告。*/
  SD_BLE_GAP_ADV_STOP              = BLE_GAP_SVC_BASE + 8,   /**<停止广告。*/
  SD_BLE_GAP_CONN_PARAM_UPDATE     = BLE_GAP_SVC_BASE + 9,   /**<连接参数更新。*/
  SD_BLE_GAP_DISCONNECT            = BLE_GAP_SVC_BASE + 10,  /**<断开连接。*/
  SD_BLE_GAP_TX_POWER_SET          = BLE_GAP_SVC_BASE + 11,  /**<设置发送功率。*/
  SD_BLE_GAP_APPEARANCE_SET        = BLE_GAP_SVC_BASE + 12,  /**<设置外观。*/
  SD_BLE_GAP_APPEARANCE_GET        = BLE_GAP_SVC_BASE + 13,  /**<获得外观。*/
  SD_BLE_GAP_PPCP_SET              = BLE_GAP_SVC_BASE + 14,  /**<设置PPCP。*/
  SD_BLE_GAP_PPCP_GET              = BLE_GAP_SVC_BASE + 15,  /**<获取PPCP。*/
  SD_BLE_GAP_DEVICE_NAME_SET       = BLE_GAP_SVC_BASE + 16,  /**<设置设备名称。*/
  SD_BLE_GAP_DEVICE_NAME_GET       = BLE_GAP_SVC_BASE + 17,  /**<获取设备名称。*/
  SD_BLE_GAP_AUTHENTICATE          = BLE_GAP_SVC_BASE + 18,  /**<启动配对/绑定。*/
  SD_BLE_GAP_SEC_PARAMS_REPLY      = BLE_GAP_SVC_BASE + 19,  /**<回复安全参数。*/
  SD_BLE_GAP_AUTH_KEY_REPLY        = BLE_GAP_SVC_BASE + 20,  /**<使用身份验证密钥回复。*/
  SD_BLE_GAP_LESC_DHKEY_REPLY      = BLE_GAP_SVC_BASE + 21,  /**<使用LE安全连接DHKey回复。*/
  SD_BLE_GAP_KEYPRESS_NOTIFY       = BLE_GAP_SVC_BASE + 22,  /**<在验证过程中通知按键。*/
  SD_BLE_GAP_LESC_OOB_DATA_GET     = BLE_GAP_SVC_BASE + 23,  /**<获取本地LE安全连接OOB数据。*/
  SD_BLE_GAP_LESC_OOB_DATA_SET     = BLE_GAP_SVC_BASE + 24,  /**<设置远程LE安全连接OOB数据。*/
  SD_BLE_GAP_ENCRYPT               = BLE_GAP_SVC_BASE + 25,  /**<启动加密程序。*/
  SD_BLE_GAP_SEC_INFO_REPLY        = BLE_GAP_SVC_BASE + 26,  /**<回复安全信息。*/
  SD_BLE_GAP_CONN_SEC_GET          = BLE_GAP_SVC_BASE + 27,  /**<获取连接安全级别。*/
  SD_BLE_GAP_RSSI_START            = BLE_GAP_SVC_BASE + 28,  /**<开始报告RSSI的变化。*/
  SD_BLE_GAP_RSSI_STOP             = BLE_GAP_SVC_BASE + 29,  /**<停止报告RSSI的变化。*/
  SD_BLE_GAP_SCAN_START            = BLE_GAP_SVC_BASE + 30,  /**<开始扫描。*/
  SD_BLE_GAP_SCAN_STOP             = BLE_GAP_SVC_BASE + 31,  /**<停止扫描。*/
  SD_BLE_GAP_CONNECT               = BLE_GAP_SVC_BASE + 32,  /**<连接。*/
  SD_BLE_GAP_CONNECT_CANCEL        = BLE_GAP_SVC_BASE + 33,  /**<取消正在进行的连接过程。*/
  SD_BLE_GAP_RSSI_GET              = BLE_GAP_SVC_BASE + 34,  /**<获取最后一个RSSI样本。*/
  SD_BLE_GAP_PHY_UPDATE            = BLE_GAP_SVC_BASE + 35,  /**<启动或响应PHY更新程序。*/
  SD_BLE_GAP_DATA_LENGTH_UPDATE    = BLE_GAP_SVC_BASE + 36,  /**<启动或响应数据长度更新程序。*/
  SD_BLE_GAP_QOS_CHANNEL_SURVEY_START  = BLE_GAP_SVC_BASE + 37, /**<启动服务质量（QoS）信道调查模块。*/
  SD_BLE_GAP_QOS_CHANNEL_SURVEY_STOP   = BLE_GAP_SVC_BASE + 38, /**<停止服务质量（QoS）信道调查模块。*/
  SD_BLE_GAP_ADV_ADDR_GET          = BLE_GAP_SVC_BASE + 39, /**<广告时获取广播中使用的地址。*/
};

/**@brief GAP事件ID。唯一标识从堆栈到应用程序的事件的ID。
 */
enum BLE_GAP_EVTS
{
  BLE_GAP_EVT_CONNECTED                   = BLE_GAP_EVT_BASE,       /**<已连接到对等端。\n请参见@ref ble_gap_evt_connected_t*/
  BLE_GAP_EVT_DISCONNECTED                = BLE_GAP_EVT_BASE + 1,   /**<与对等方断开连接。\n请参见@ref ble_gap_evt_disconnected_t。*/
  BLE_GAP_EVT_CONN_PARAM_UPDATE           = BLE_GAP_EVT_BASE + 2,   /**<连接参数已更新。\n请参见@ref ble_gap_evt_conn_param_update_t。*/
  BLE_GAP_EVT_SEC_PARAMS_REQUEST          = BLE_GAP_EVT_BASE + 3,   /**<请求提供安全参数。\n回复@ref sd_ble_gap_sec_params_Reply。\n请参见@ref ble_gap_evt_sec_params_request_t。*/
  BLE_GAP_EVT_SEC_INFO_REQUEST            = BLE_GAP_EVT_BASE + 4,   /**<请求提供安全信息。\n回复@ref sd_ble_gap_sec_info_Reply。\n请参见@ref ble_gap_evt_sec_info_request_t。*/
  BLE_GAP_EVT_PASSKEY_DISPLAY             = BLE_GAP_EVT_BASE + 5,   /**<请求向用户显示密钥。\n在LESC数值比较中，回复@ref sd_ble_gap_auth_key_reply。\n请参见@ref ble_gap_evt_passkey_display_t。*/
  BLE_GAP_EVT_KEY_PRESSED                 = BLE_GAP_EVT_BASE + 6,   /**<远程设备上按键的通知。\n请参见@ref ble_gap_evt_key_pressed_t*/
  BLE_GAP_EVT_AUTH_KEY_REQUEST            = BLE_GAP_EVT_BASE + 7,   /**<请求提供身份验证密钥。\n回复@ref sd_ble_gap_auth_key_Reply。\n请参见@ref ble_gap_evt_auth_key_request_t。*/
  BLE_GAP_EVT_LESC_DHKEY_REQUEST          = BLE_GAP_EVT_BASE + 8,   /**<请求计算LE安全连接DHKey。\n回复@ref sd_ble_gap_lesc_dhkey_Reply。\n请参见@ref ble_gap_evt_lesc_dhkey_request_t*/
  BLE_GAP_EVT_AUTH_STATUS                 = BLE_GAP_EVT_BASE + 9,   /**<身份验证过程已完成，状态为。\n请参见@ref ble_gap_evt_auth_status_t。*/
  BLE_GAP_EVT_CONN_SEC_UPDATE             = BLE_GAP_EVT_BASE + 10,  /**<已更新连接安全性。\n请参见@ref ble_gap_evt_conn_sec_update_t。*/
  BLE_GAP_EVT_TIMEOUT                     = BLE_GAP_EVT_BASE + 11,  /**<超时已过期。\n请参见@ref ble_gap_evt_timeout_t。*/
  BLE_GAP_EVT_RSSI_CHANGED                = BLE_GAP_EVT_BASE + 12,  /**<RSSI报告。\n请参见@ref ble_gap_evt_rssi_changed_t。*/
  BLE_GAP_EVT_ADV_REPORT                  = BLE_GAP_EVT_BASE + 13,  /**<广告报道。\n请参见@ref ble_gap_evt_adv_report_t。*/
  BLE_GAP_EVT_SEC_REQUEST                 = BLE_GAP_EVT_BASE + 14,  /**<安全请求。\n请参见@ref ble_gap_evt_sec_request_t。*/
  BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST   = BLE_GAP_EVT_BASE + 15,  /**<连接参数更新请求。\n回复@ref sd_ble_gap_conn_param_update。\n请参见@ref ble_gap_evt_conn_param_update_request_t。*/
  BLE_GAP_EVT_SCAN_REQ_REPORT             = BLE_GAP_EVT_BASE + 16,  /**<扫描请求报告。\n请参见@ref ble_gap_evt_scan_req_report_t。*/
  BLE_GAP_EVT_PHY_UPDATE_REQUEST          = BLE_GAP_EVT_BASE + 17,  /**<PHY更新请求。\n回复@ref sd_ble_gap_phy_update。\n请参见@ref ble_gap_evt_phy_update_request_t。*/
  BLE_GAP_EVT_PHY_UPDATE                  = BLE_GAP_EVT_BASE + 18,  /**<PHY更新程序已完成。\n请参见@ref ble_gap_evt_phy_update_t。*/
  BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST = BLE_GAP_EVT_BASE + 19,   /**<数据长度更新请求。\n回复@ref sd_ble_gap_data_length_update。\n请参见@ref ble_gap_evt_data_length_update_request_t。*/
  BLE_GAP_EVT_DATA_LENGTH_UPDATE         = BLE_GAP_EVT_BASE + 20,   /**<LL数据信道PDU有效负载长度已更新。\n请参见@ref ble_gap_evt_data_length_update_t。*/
  BLE_GAP_EVT_QOS_CHANNEL_SURVEY_REPORT  = BLE_GAP_EVT_BASE + 21,   /**<渠道调查报告。\n请参见@ref ble_gap_evt_qos_channel_survey_report_t。*/
  BLE_GAP_EVT_ADV_SET_TERMINATED         = BLE_GAP_EVT_BASE + 22,   /**<广告集已终止。\n请参见@ref ble_gap_evt_adv_set_terminated_t。*/
};

/**@brief GAP选项ID。唯一标识GAP选项的ID。
 */
enum BLE_GAP_OPTS
{
  BLE_GAP_OPT_CH_MAP                 = BLE_GAP_OPT_BASE,       /**<通道贴图@参考文件_文件_文件*/
  BLE_GAP_OPT_LOCAL_CONN_LATENCY     = BLE_GAP_OPT_BASE + 1,   /**<本地连接延迟@参考文件_时间_位置_时间_延迟*/
  BLE_GAP_OPT_PASSKEY                = BLE_GAP_OPT_BASE + 2,   /**<设置密钥@参考文件_标签_标签_密钥_*/
  BLE_GAP_OPT_COMPAT_MODE_1          = BLE_GAP_OPT_BASE + 3,   /**<兼容性模式@参考文件_ ap_opt_compat_mode_1_t*/
  BLE_GAP_OPT_AUTH_PAYLOAD_TIMEOUT   = BLE_GAP_OPT_BASE + 4,   /**<设置经过身份验证的负载超时@参考文件_ ap_opt_auth_payload_timeout_t*/
  BLE_GAP_OPT_SLAVE_LATENCY_DISABLE  = BLE_GAP_OPT_BASE + 5,   /**<禁用从属延迟@参考文件_ ap_opt_slave_latency_disable_t*/
};

/**@brief GAP配置ID。
 *
 * 唯一标识GAP配置的ID。
 */
enum BLE_GAP_CFGS
{
  BLE_GAP_CFG_ROLE_COUNT    = BLE_GAP_CFG_BASE,     /**<角色计数配置。*/
  BLE_GAP_CFG_DEVICE_NAME   = BLE_GAP_CFG_BASE + 1, /**<设备名称配置。*/
};

/**@brief GAP TX Power角色。
 */
enum BLE_GAP_TX_POWER_ROLES
{
  BLE_GAP_TX_POWER_ROLE_ADV       = 1,           /**<广告商角色。*/
  BLE_GAP_TX_POWER_ROLE_SCAN_INIT = 2,           /**<扫描仪和启动器角色。*/
  BLE_GAP_TX_POWER_ROLE_CONN      = 3,           /**<连接角色。*/
};

/** @} */

/**@addtogroup BLE_GAP_DEFINES定义
 * @{ */

/**@defgroup BLE_ERRORS_GAP SVC返回特定于GAP的值
 * @{ */
#define BLE_ERROR_GAP_UUID_LIST_MISMATCH            (NRF_GAP_ERR_BASE + 0x000)  /**<UUID列表不包含整数个UUID。*/
#define BLE_ERROR_GAP_DISCOVERABLE_WITH_WHITELIST   (NRF_GAP_ERR_BASE + 0x001)  /**<不允许在可发现的广告中使用白名单。*/
#define BLE_ERROR_GAP_INVALID_BLE_ADDR              (NRF_GAP_ERR_BASE + 0x002)  /**<地址的上两位与指定的地址类型不对应。*/
#define BLE_ERROR_GAP_WHITELIST_IN_USE              (NRF_GAP_ERR_BASE + 0x003)  /**<当其他操作正在使用时，尝试修改白名单。*/
#define BLE_ERROR_GAP_DEVICE_IDENTITIES_IN_USE      (NRF_GAP_ERR_BASE + 0x004)  /**<当另一个操作正在使用时，尝试修改设备标识列表。*/
#define BLE_ERROR_GAP_DEVICE_IDENTITIES_DUPLICATE   (NRF_GAP_ERR_BASE + 0x005)  /**<设备标识列表包含具有重复标识地址的条目。*/
/**@} */


/**@defgroup BLE_GAP_ROLES GAP角色
 * @{ */
#define BLE_GAP_ROLE_INVALID     0x0            /**<无效角色。*/
#define BLE_GAP_ROLE_PERIPH      0x1            /**<外围角色。*/
#define BLE_GAP_ROLE_CENTRAL     0x2            /**<中心角色。*/
/**@} */


/**@defgroup BLE_GAP_TIMEOUT_SOURCES GAP超时源
 * @{ */
#define BLE_GAP_TIMEOUT_SRC_SCAN                       0x01 /**<扫描超时。*/
#define BLE_GAP_TIMEOUT_SRC_CONN                       0x02 /**<连接超时。*/
#define BLE_GAP_TIMEOUT_SRC_AUTH_PAYLOAD               0x03 /**<经过身份验证的有效负载超时。*/
/**@} */


/**@defgroup BLE_GAP_ADDR_TYPES GAP地址类型
 * @{ */
#define BLE_GAP_ADDR_TYPE_PUBLIC                        0x00 /**<公共（身份）地址。*/
#define BLE_GAP_ADDR_TYPE_RANDOM_STATIC                 0x01 /**<随机静态（身份）地址。*/
#define BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE     0x02 /**<随机私有可解析地址。*/
#define BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_NON_RESOLVABLE 0x03 /**<随机私有不可解析地址。*/
#define BLE_GAP_ADDR_TYPE_ANONYMOUS                     0x7F /**<广告客户可以在没有地址的情况下进行广告。这种类型的广告称为匿名广告。*/
/**@} */


/**@brief 刷新专用地址的默认间隔（秒）。*/
#define BLE_GAP_DEFAULT_PRIVATE_ADDR_CYCLE_INTERVAL_S (900) /* 15分钟。*/
/**@brief 刷新专用地址的最大间隔（秒）。*/
#define BLE_GAP_MAX_PRIVATE_ADDR_CYCLE_INTERVAL_S     (41400) /* 11小时30分钟。*/


/** @brief BLE地址长度。*/
#define BLE_GAP_ADDR_LEN (6)

/**@defgroup BLE_GAP_PRIVACY_MODES隐私模式
 * @{ */
#define BLE_GAP_PRIVACY_MODE_OFF                       0x00 /**<设备将发送并接受其自身地址的身份地址。*/
#define BLE_GAP_PRIVACY_MODE_DEVICE_PRIVACY            0x01 /**<设备将仅发送和接受其自身地址的专用地址。*/
#define BLE_GAP_PRIVACY_MODE_NETWORK_PRIVACY           0x02 /**<设备将仅发送和接受其自身地址的私有地址，并且在交换对等IRK（非零）并将其添加到身份列表中时，不会接受使用身份地址作为发送者地址的对等方。*/
/**@} */

/** @brief 无效的功率电平。*/
#define BLE_GAP_POWER_LEVEL_INVALID     127

/** @brief 未设置广告设置句柄。*/
#define BLE_GAP_ADV_SET_HANDLE_NOT_SET (0xFF)

/** @brief 广告集的默认数量。*/
#define BLE_GAP_ADV_SET_COUNT_DEFAULT   (1)

/** @brief 此SoftDevice支持的最大广告集数。*/
#define BLE_GAP_ADV_SET_COUNT_MAX       (1)

/**@defgroup BLE_GAP_ADV_SET_DATA_SIZES广告数据大小。
 * @{ */
#define BLE_GAP_ADV_SET_DATA_SIZE_MAX                    (31)   /**<广告集的最大数据长度。如果需要更多的广告数据，请改用扩展广告。*/
#define BLE_GAP_ADV_SET_DATA_SIZE_EXTENDED_MAX_SUPPORTED (255)  /**<扩展广告集支持的最大数据长度。*/

#define BLE_GAP_ADV_SET_DATA_SIZE_EXTENDED_CONNECTABLE_MAX_SUPPORTED (238) /**<扩展的可连接广告集支持的最大数据长度。*/
/**@}. */

/** @brief 设置ID在广告报告中不可用。*/
#define BLE_GAP_ADV_REPORT_SET_ID_NOT_AVAILABLE                    0xFF

/**@defgroup BLE_GAP_EVT_ADV_SET_TERMINATED_REASON GAP广告集终止原因
 * @{ */
#define BLE_GAP_EVT_ADV_SET_TERMINATED_REASON_TIMEOUT              0x01  /**<达到超时值。*/
#define BLE_GAP_EVT_ADV_SET_TERMINATED_REASON_LIMIT_REACHED        0x02  /**已达到<@ref ble_gap_adv_params_t:：max_adv_evts。*/
/**@} */

/**@defgroup BLE_GAP_AD_TYPE_DEFINITION间隙广告和扫描响应数据格式
 * @note 在找到https://www.bluetooth.org/Technical/AssignedNumbers/generic_access_profile.htm
 * @{ */
#define BLE_GAP_AD_TYPE_FLAGS                               0x01 /**<可发现性标志。*/
#define BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_MORE_AVAILABLE   0x02 /**<16位服务UUID的部分列表。*/
#define BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE         0x03 /**<16位服务UUID的完整列表。*/
#define BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_MORE_AVAILABLE   0x04 /**<32位服务UUID的部分列表。*/
#define BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_COMPLETE         0x05 /**<32位服务UUID的完整列表。*/
#define BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_MORE_AVAILABLE  0x06 /**<128位服务UUID的部分列表。*/
#define BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_COMPLETE        0x07 /**<128位服务UUID的完整列表。*/
#define BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME                    0x08 /**<短本地设备名称。*/
#define BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME                 0x09 /**<完整的本地设备名称。*/
#define BLE_GAP_AD_TYPE_TX_POWER_LEVEL                      0x0A /**<发射功率电平。*/
#define BLE_GAP_AD_TYPE_CLASS_OF_DEVICE                     0x0D /**<设备类别。*/
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C               0x0E /**<简单配对哈希C。*/
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RANDOMIZER_R         0x0F /**<简单配对随机化R。*/
#define BLE_GAP_AD_TYPE_SECURITY_MANAGER_TK_VALUE           0x10 /**<Security Manager TK值。*/
#define BLE_GAP_AD_TYPE_SECURITY_MANAGER_OOB_FLAGS          0x11 /**<安全管理器带外标志。*/
#define BLE_GAP_AD_TYPE_SLAVE_CONNECTION_INTERVAL_RANGE     0x12 /**<从属连接间隔范围。*/
#define BLE_GAP_AD_TYPE_SOLICITED_SERVICE_UUIDS_16BIT       0x14 /**<16位服务请求UUID列表。*/
#define BLE_GAP_AD_TYPE_SOLICITED_SERVICE_UUIDS_128BIT      0x15 /**<128位服务请求UUID列表。*/
#define BLE_GAP_AD_TYPE_SERVICE_DATA                        0x16 /**<服务数据-16位UUID。*/
#define BLE_GAP_AD_TYPE_PUBLIC_TARGET_ADDRESS               0x17 /**<公共目标地址。*/
#define BLE_GAP_AD_TYPE_RANDOM_TARGET_ADDRESS               0x18 /**<随机目标地址。*/
#define BLE_GAP_AD_TYPE_APPEARANCE                          0x19 /**<外观。*/
#define BLE_GAP_AD_TYPE_ADVERTISING_INTERVAL                0x1A /**<广告间隔。*/
#define BLE_GAP_AD_TYPE_LE_BLUETOOTH_DEVICE_ADDRESS         0x1B /**<LE蓝牙设备地址。*/
#define BLE_GAP_AD_TYPE_LE_ROLE                             0x1C /**<LE角色。*/
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C256            0x1D /**<简单配对哈希C-256。*/
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RANDOMIZER_R256      0x1E /**<简单配对随机化器R-256。*/
#define BLE_GAP_AD_TYPE_SERVICE_DATA_32BIT_UUID             0x20 /**<服务数据-32位UUID。*/
#define BLE_GAP_AD_TYPE_SERVICE_DATA_128BIT_UUID            0x21 /**<服务数据-128位UUID。*/
#define BLE_GAP_AD_TYPE_LESC_CONFIRMATION_VALUE             0x22 /**<LE安全连接确认值*/
#define BLE_GAP_AD_TYPE_LESC_RANDOM_VALUE                   0x23 /**<LE安全连接随机值*/
#define BLE_GAP_AD_TYPE_URI                                 0x24 /**< URI */
#define BLE_GAP_AD_TYPE_3D_INFORMATION_DATA                 0x3D /**<3D信息数据。*/
#define BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA          0xFF /**<制造商特定数据。*/
/**@} */


/**@defgroup BLE_GAP_ADV_FLAGS GAP播发标志
 * @{ */
#define BLE_GAP_ADV_FLAG_LE_LIMITED_DISC_MODE         (0x01)   /**<LE有限可发现模式。*/
#define BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE         (0x02)   /**<LE常规可发现模式。*/
#define BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED         (0x04)   /**<BR/EDR不受支持。*/
#define BLE_GAP_ADV_FLAG_LE_BR_EDR_CONTROLLER         (0x08)   /**<同时LE和BR/EDR，控制器。*/
#define BLE_GAP_ADV_FLAG_LE_BR_EDR_HOST               (0x10)   /**<同时LE和BR/EDR，主机。*/
#define BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE   (BLE_GAP_ADV_FLAG_LE_LIMITED_DISC_MODE | BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED)   /**<LE有限可发现模式，不支持BR/EDR。*/
#define BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE   (BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE | BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED)   /**<LE常规可发现模式，不支持BR/EDR。*/
/**@} */


/**@defgroup BLE_GAP_ADV_INTERVALS GAP广告间隔最大值和最小值
 * @{ */
#define BLE_GAP_ADV_INTERVAL_MIN        0x000020 /**<最小广告间隔为625 us单位，即20 ms。*/
#define BLE_GAP_ADV_INTERVAL_MAX        0x004000 /**<最大广告间隔（625美国单位），即10.24秒。*/
 /**@}  */


/**@defgroup BLE_GAP_SCAN_INTERVALS GAP扫描间隔最大值和最小值
 * @{ */
#define BLE_GAP_SCAN_INTERVAL_MIN       0x0004 /**<最小扫描间隔（625 us单位），即2.5 ms。*/
#define BLE_GAP_SCAN_INTERVAL_MAX       0xFFFF /**<最大扫描间隔（625 us单位），即40959.375 s。*/
 /** @}  */


/**@defgroup BLE_GAP_SCAN_WINDOW GAP扫描窗口最大值和最小值
 * @{ */
#define BLE_GAP_SCAN_WINDOW_MIN         0x0004 /**<625 us单位的最小扫描窗口，即2.5 ms。*/
#define BLE_GAP_SCAN_WINDOW_MAX         0xFFFF /**<最大扫描窗口（625 us单位），即40959.375 s。*/
 /** @}  */


/**@defgroup BLE_GAP_SCAN_TIMEOUT GAP扫描超时最大值和最小值
 * @{ */
#define BLE_GAP_SCAN_TIMEOUT_MIN        0x0001 /**<以10毫秒为单位的最小扫描超时，即10毫秒。*/
#define BLE_GAP_SCAN_TIMEOUT_UNLIMITED  0x0000 /**<永远继续扫描。*/
 /** @}  */

/**@defgroup BLE_GAP_SCAN_BUFFER_SIZE GAP最小扫描仪缓冲区大小
 *
 * 扫描缓冲器用于存储从广告客户接收的广告数据。
 * If ble_gap_scan_params_t::extended is set to 0, @ref BLE_GAP_SCAN_BUFFER_MIN是最小扫描缓冲区长度。否则最小扫描缓冲区大小为@ref BLE_GAP_scan_buffer_EXTENDED_MIN。
 * @{ */
#define BLE_GAP_SCAN_BUFFER_MIN                    (31)                             /**<广告集的最小数据长度。*/
#define BLE_GAP_SCAN_BUFFER_MAX                    (31)                             /**<广告集的最大数据长度。*/
#define BLE_GAP_SCAN_BUFFER_EXTENDED_MIN           (255)                            /**<扩展广告集的最小数据长度。*/
#define BLE_GAP_SCAN_BUFFER_EXTENDED_MAX           (1650)                           /**<扩展广告集的最大数据长度。*/
#define BLE_GAP_SCAN_BUFFER_EXTENDED_MAX_SUPPORTED (255)                            /**<扩展广告集支持的最大数据长度。*/
/** @}  */

/**@defgroup BLE_GAP_ADV_TYPES GAP广告类型
 *
 * 蓝牙核心规范v5.0，第6卷，B部分，第4.4.2节中定义的广告类型。
 *
 * The maximum advertising data length is defined by @ref BLE_GAP_ADV_SET_DATA_SIZE_MAX。扩展广告客户支持的最大数据长度由以下定义
 * @ref BLE_GAP_ADV_SET_DATA_SIZE_EXTENDED_MAX_SUPPORTED注意，某些广告类型不支持广告数据。不可扫描类型不支持扫描响应数据。
 *
 * @{ */
#define BLE_GAP_ADV_TYPE_CONNECTABLE_SCANNABLE_UNDIRECTED                   0x01   /**<可连接和可扫描的无方向广告事件。*/
#define BLE_GAP_ADV_TYPE_CONNECTABLE_NONSCANNABLE_DIRECTED_HIGH_DUTY_CYCLE  0x02   /**<可连接的不可扫描定向广告事件。广告间隔小于3.75毫秒。请使用此类型快速重新连接@注意：不支持广告数据。*/
#define BLE_GAP_ADV_TYPE_CONNECTABLE_NONSCANNABLE_DIRECTED                  0x03   /**<可连接的不可扫描定向广告事件@注意：不支持广告数据。*/
#define BLE_GAP_ADV_TYPE_NONCONNECTABLE_SCANNABLE_UNDIRECTED                0x04   /**<不可连接的可扫描无方向广告事件。*/
#define BLE_GAP_ADV_TYPE_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED             0x05   /**<不可连接、不可扫描的无方向广告事件。*/
#define BLE_GAP_ADV_TYPE_EXTENDED_CONNECTABLE_NONSCANNABLE_UNDIRECTED       0x06   /**<使用扩展广告PDU的可连接的不可扫描无方向广告事件。*/
#define BLE_GAP_ADV_TYPE_EXTENDED_CONNECTABLE_NONSCANNABLE_DIRECTED         0x07   /**<使用扩展广告PDU连接不可扫描的定向广告事件。*/
#define BLE_GAP_ADV_TYPE_EXTENDED_NONCONNECTABLE_SCANNABLE_UNDIRECTED       0x08   /**<使用扩展广告PDU的不可连接的可扫描无方向广告事件@注意：仅支持扫描响应数据。*/
#define BLE_GAP_ADV_TYPE_EXTENDED_NONCONNECTABLE_SCANNABLE_DIRECTED         0x09   /**<使用扩展广告PDU的不可连接的可扫描定向广告事件@注意：仅支持扫描响应数据。*/
#define BLE_GAP_ADV_TYPE_EXTENDED_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED    0x0A   /**<使用扩展广告PDU的不可连接、不可扫描的无方向广告事件。*/
#define BLE_GAP_ADV_TYPE_EXTENDED_NONCONNECTABLE_NONSCANNABLE_DIRECTED      0x0B   /**<使用扩展广告PDU的不可连接、不可扫描的定向广告事件。*/
/**@} */

/**@defgroup BLE_GAP_ADV_FILTER_POLICIES GAP广告过滤器策略
 * @{ */
#define BLE_GAP_ADV_FP_ANY                0x00   /**<允许来自任何设备的扫描请求和连接请求。*/
#define BLE_GAP_ADV_FP_FILTER_SCANREQ     0x01   /**<使用白名单筛选扫描请求。*/
#define BLE_GAP_ADV_FP_FILTER_CONNREQ     0x02   /**<使用白名单过滤连接请求。*/
#define BLE_GAP_ADV_FP_FILTER_BOTH        0x03   /**<使用白名单过滤扫描和连接请求。*/
/**@} */

/**@defgroup BLE_GAP_ADV_DATA_STATUS GAP广告数据状态
 * @{ */
#define BLE_GAP_ADV_DATA_STATUS_COMPLETE             0x00 /**<已收到广告事件中的所有数据。*/
#define BLE_GAP_ADV_DATA_STATUS_INCOMPLETE_MORE_DATA 0x01 /**<需要接收更多数据@注意：只有当@ref ble_gap_scan_params_t:：report_incomplete_evts和@ref ble_gap_adv_report_type_t:：extended_pdu设置为true时，才会使用此值。*/
#define BLE_GAP_ADV_DATA_STATUS_INCOMPLETE_TRUNCATED 0x02 /**<数据不完整。缓冲区大小不足以接收更多@注意：只有当@ref ble_gap_adv_report_type_t:：extended_pdu设置为true时，才会使用此值。*/
#define BLE_GAP_ADV_DATA_STATUS_INCOMPLETE_MISSED    0x03 /**<无法接收剩余数据@注意：只有当@ref ble_gap_adv_report_type_t:：extended_pdu设置为true时，才会使用此值。*/
/**@} */

/**@defgroup BLE_GAP_SCAN_FILTER_POLICIES GAP扫描仪筛选器策略
 * @{ */
#define BLE_GAP_SCAN_FP_ACCEPT_ALL                      0x00  /**<接受所有广告数据包，但不指向此设备的定向广告数据包除外。*/
#define BLE_GAP_SCAN_FP_WHITELIST                       0x01  /**<接受来自白名单中设备的广告数据包，但不指向此设备的定向数据包除外。*/
#define BLE_GAP_SCAN_FP_ALL_NOT_RESOLVED_DIRECTED       0x02  /**<接受@ref BLE_GAP_SCAN_FP_Accept_all中指定的所有广告数据包。此外，接受定向广告包，其中广告客户的地址是无法解析的可解析的私有地址。*/
#define BLE_GAP_SCAN_FP_WHITELIST_NOT_RESOLVED_DIRECTED 0x03  /**<接受@ref BLE_GAP_SCAN_FP_WHITELIST中指定的所有广告包。此外，接受定向广告包，其中广告客户的地址是无法解析的可解析的私有地址。*/
/**@} */

/**@defgroup BLE_GAP_ADV_TIMEOUT_VALUES GAP广告超时值（以10毫秒为单位）
 * @{ */
#define BLE_GAP_ADV_TIMEOUT_HIGH_DUTY_MAX     (128)   /**<最大高负荷广告时间，单位为10ms。对应1.28秒。*/
#define BLE_GAP_ADV_TIMEOUT_LIMITED_MAX       (18000) /**<在有限可发现模式下，对应于TGAP（lim_adv_timeout）的10毫秒单位的最大广告时间=180秒。*/
#define BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED (0)     /**<一般可发现模式下的无限广告。对于高占空比广告，这对应于@ref BLE_GAP_ADV_TIMEOUT_high_duty_MAX。*/
/**@} */


/**@defgroup BLE_GAP_DISC_MODES GAP发现模式
 * @{ */
#define BLE_GAP_DISC_MODE_NOT_DISCOVERABLE  0x00   /**<不可发现的发现模式。*/
#define BLE_GAP_DISC_MODE_LIMITED           0x01   /**<有限发现模式。*/
#define BLE_GAP_DISC_MODE_GENERAL           0x02   /**<常规发现模式。*/
/**@} */


/**@defgroup BLE_GAP_IO_CAPS GAP IO功能
 * @{ */
#define BLE_GAP_IO_CAPS_DISPLAY_ONLY      0x00   /**<仅显示。*/
#define BLE_GAP_IO_CAPS_DISPLAY_YESNO     0x01   /**<显示和是/否输入。*/
#define BLE_GAP_IO_CAPS_KEYBOARD_ONLY     0x02   /**<仅键盘。*/
#define BLE_GAP_IO_CAPS_NONE              0x03   /**<无I/O功能。*/
#define BLE_GAP_IO_CAPS_KEYBOARD_DISPLAY  0x04   /**<键盘和显示器。*/
/**@} */


/**@defgroup BLE_GAP_AUTH_KEY_TYPES GAP身份验证密钥类型
 * @{ */
#define BLE_GAP_AUTH_KEY_TYPE_NONE        0x00   /**<无键（可用于拒绝）。*/
#define BLE_GAP_AUTH_KEY_TYPE_PASSKEY     0x01   /**<6位密码。*/
#define BLE_GAP_AUTH_KEY_TYPE_OOB         0x02   /**<带外数据。*/
/**@} */


/**@defgroup BLE_GAP_KP_NOT_TYPES GAP键盘通知类型
 * @{ */
#define BLE_GAP_KP_NOT_TYPE_PASSKEY_START       0x00   /**<开始输入密钥。*/
#define BLE_GAP_KP_NOT_TYPE_PASSKEY_DIGIT_IN    0x01   /**<输入了密钥数字。*/
#define BLE_GAP_KP_NOT_TYPE_PASSKEY_DIGIT_OUT   0x02   /**<密码数字已擦除。*/
#define BLE_GAP_KP_NOT_TYPE_PASSKEY_CLEAR       0x03   /**<已清除密钥。*/
#define BLE_GAP_KP_NOT_TYPE_PASSKEY_END         0x04   /**<密码输入完成。*/
/**@} */


/**@defgroup BLE_GAP_SEC_STATUS GAP安全状态
 * @{ */
#define BLE_GAP_SEC_STATUS_SUCCESS                0x00  /**<程序成功完成。*/
#define BLE_GAP_SEC_STATUS_TIMEOUT                0x01  /**<过程超时。*/
#define BLE_GAP_SEC_STATUS_PDU_INVALID            0x02  /**<收到无效PDU。*/
#define BLE_GAP_SEC_STATUS_RFU_RANGE1_BEGIN       0x03  /**<保留供未来使用范围#1开始。*/
#define BLE_GAP_SEC_STATUS_RFU_RANGE1_END         0x80  /**<保留供未来使用范围#1结束。*/
#define BLE_GAP_SEC_STATUS_PASSKEY_ENTRY_FAILED   0x81  /**<密码输入失败（用户取消或其他）。*/
#define BLE_GAP_SEC_STATUS_OOB_NOT_AVAILABLE      0x82  /**<带外密钥不可用。*/
#define BLE_GAP_SEC_STATUS_AUTH_REQ               0x83  /**<未满足身份验证要求。*/
#define BLE_GAP_SEC_STATUS_CONFIRM_VALUE          0x84  /**<确认值失败。*/
#define BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP       0x85  /**<不支持配对。*/
#define BLE_GAP_SEC_STATUS_ENC_KEY_SIZE           0x86  /**<加密密钥大小。*/
#define BLE_GAP_SEC_STATUS_SMP_CMD_UNSUPPORTED    0x87  /**<不支持的SMP命令。*/
#define BLE_GAP_SEC_STATUS_UNSPECIFIED            0x88  /**<未指定原因。*/
#define BLE_GAP_SEC_STATUS_REPEATED_ATTEMPTS      0x89  /**<自上次尝试以来所用时间太少。*/
#define BLE_GAP_SEC_STATUS_INVALID_PARAMS         0x8A  /**<无效参数。*/
#define BLE_GAP_SEC_STATUS_DHKEY_FAILURE          0x8B  /**<DHKey检查失败。*/
#define BLE_GAP_SEC_STATUS_NUM_COMP_FAILURE       0x8C  /**<数值比较失败。*/
#define BLE_GAP_SEC_STATUS_BR_EDR_IN_PROG         0x8D  /**<BR/EDR配对正在进行中。*/
#define BLE_GAP_SEC_STATUS_X_TRANS_KEY_DISALLOWED 0x8E  /**<BR/EDR链接密钥不能用于LE密钥。*/
#define BLE_GAP_SEC_STATUS_RFU_RANGE2_BEGIN       0x8F  /**<保留供将来使用范围#2开始。*/
#define BLE_GAP_SEC_STATUS_RFU_RANGE2_END         0xFF  /**<保留供将来使用范围#2结束。*/
/**@} */


/**@defgroup BLE_GAP_SEC_STATUS_SOURCES GAP安全状态源
 * @{ */
#define BLE_GAP_SEC_STATUS_SOURCE_LOCAL           0x00  /**<局部故障。*/
#define BLE_GAP_SEC_STATUS_SOURCE_REMOTE          0x01  /**<远程故障。*/
/**@} */


/**@defgroup BLE_GAP_CP_LIMITS GAP连接参数限制
 * @{ */
#define BLE_GAP_CP_MIN_CONN_INTVL_NONE           0xFFFF  /**<连接参数中未指定新的最小连接间隔。*/
#define BLE_GAP_CP_MIN_CONN_INTVL_MIN            0x0006  /**<允许的最小连接间隔，单位为1.25 ms，即7.5 ms。*/
#define BLE_GAP_CP_MIN_CONN_INTVL_MAX            0x0C80  /**<允许的最大最小连接间隔，单位为1.25毫秒，即4秒。*/
#define BLE_GAP_CP_MAX_CONN_INTVL_NONE           0xFFFF  /**<连接参数中未指定新的最大连接间隔。*/
#define BLE_GAP_CP_MAX_CONN_INTVL_MIN            0x0006  /**<允许的最小最大连接间隔，单位为1.25 ms，即7.5 ms。*/
#define BLE_GAP_CP_MAX_CONN_INTVL_MAX            0x0C80  /**<允许的最大连接间隔，单位为1.25毫秒，即4秒。*/
#define BLE_GAP_CP_SLAVE_LATENCY_MAX             0x01F3  /**<连接事件中允许的最高从属延迟。*/
#define BLE_GAP_CP_CONN_SUP_TIMEOUT_NONE         0xFFFF  /**<连接参数中未指定新的监督超时。*/
#define BLE_GAP_CP_CONN_SUP_TIMEOUT_MIN          0x000A  /**<允许的最低监督超时，单位为10ms，即100ms。*/
#define BLE_GAP_CP_CONN_SUP_TIMEOUT_MAX          0x0C80  /**<允许的最高监督超时，单位为10毫秒，即32秒。*/
/**@} */


/**@defgroup BLE_GAP_DEVNAME GAP设备名称定义。
 * @{ */
#define BLE_GAP_DEVNAME_DEFAULT                  "nRF5x" /**<默认设备名称值。*/
#define BLE_GAP_DEVNAME_DEFAULT_LEN              31      /**<设备名称中的默认八位字节数。*/
#define BLE_GAP_DEVNAME_MAX_LEN                  248     /**<设备名称中的最大八位字节数。*/
/**@} */


/**@brief 禁用连接的RSSI事件*/
#define BLE_GAP_RSSI_THRESHOLD_INVALID 0xFF

/**@defgroup BLE_GAP_PHYS间隙PHY
 * @{ */
#define BLE_GAP_PHY_AUTO                         0x00    /**<自动PHY选择。有关详细信息，请参阅@ref sd_ble_gap_phy_update。*/
#define BLE_GAP_PHY_1MBPS                        0x01    /**<1 Mbps物理层。*/
#define BLE_GAP_PHY_2MBPS                        0x02    /**<2 Mbps物理层。*/
#define BLE_GAP_PHY_CODED                        0x04    /**<编码PHY。*/
#define BLE_GAP_PHY_NOT_SET                      0xFF    /**<未配置PHY。*/

/**@brief 支持连接、扫描和广告中的PHY。*/
#define BLE_GAP_PHYS_SUPPORTED  (BLE_GAP_PHY_1MBPS | BLE_GAP_PHY_2MBPS | BLE_GAP_PHY_CODED) /**<支持所有PHY。*/

/**@} */

/**@defgroup BLE_GAP_CONN_SEC_MODE_SET_MACROS GAP属性安全要求设置器
 *
 * See @ref ble_gap_conn_sec_mode_t。
 * @{ */
/**@brief 将ptr指向的sec_mode设置为没有访问权限。*/
#define BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(ptr)          do {(ptr)->sm = 0; (ptr)->lv = 0;} while(0)
/**@brief 将ptr指向的sec_mode设置为无需保护，打开链接。*/
#define BLE_GAP_CONN_SEC_MODE_SET_OPEN(ptr)               do {(ptr)->sm = 1; (ptr)->lv = 1;} while(0)
/**@brief 将ptr指向的sec_mode设置为需要加密，但不需要MITM保护。*/
#define BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(ptr)        do {(ptr)->sm = 1; (ptr)->lv = 2;} while(0)
/**@brief 将ptr指向的sec_mode设置为需要加密和MITM保护。*/
#define BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(ptr)      do {(ptr)->sm = 1; (ptr)->lv = 3;} while(0)
/**@brief 将ptr指向的sec_mode设置为需要LESC加密和MITM保护。*/
#define BLE_GAP_CONN_SEC_MODE_SET_LESC_ENC_WITH_MITM(ptr) do {(ptr)->sm = 1; (ptr)->lv = 4;} while(0)
/**@brief 将ptr指向的sec_mode设置为需要签名或加密，不需要MITM保护。*/
#define BLE_GAP_CONN_SEC_MODE_SET_SIGNED_NO_MITM(ptr)     do {(ptr)->sm = 2; (ptr)->lv = 1;} while(0)
/**@brief 将ptr指向的sec_mode设置为需要使用MITM保护进行签名或加密。*/
#define BLE_GAP_CONN_SEC_MODE_SET_SIGNED_WITH_MITM(ptr)   do {(ptr)->sm = 2; (ptr)->lv = 2;} while(0)
/**@} */


/**@brief GAP安全随机数长度。*/
#define BLE_GAP_SEC_RAND_LEN 8


/**@brief GAP安全密钥长度。*/
#define BLE_GAP_SEC_KEY_LEN 16


/**@brief GAP LE安全连接椭圆曲线Diffie Hellman P-256公钥长度。*/
#define BLE_GAP_LESC_P256_PK_LEN 64


/**@brief GAP LE安全连接椭圆曲线Diffie Hellman DHKey长度。*/
#define BLE_GAP_LESC_DHKEY_LEN   32


/**@brief GAP密钥长度。*/
#define BLE_GAP_PASSKEY_LEN 6


/**@brief 白名单中的最大地址数量。*/
#define BLE_GAP_WHITELIST_ADDR_MAX_COUNT (8)


/**@brief 设备标识列表中标识的最大数量。*/
#define BLE_GAP_DEVICE_IDENTITIES_MAX_COUNT (8)


/**@brief 配置的默认连接计数。*/
#define BLE_GAP_CONN_COUNT_DEFAULT (1)


/**@defgroup BLE_GAP_EVENT_LENGTH GAP事件长度定义。
 * @{ */
#define BLE_GAP_EVENT_LENGTH_MIN            (2)  /**<最小事件长度，单位为1.25 ms。*/
#define BLE_GAP_EVENT_LENGTH_CODED_PHY_MIN  (6)  /**<支持LE编码PHY的1.25毫秒单位中的最短事件长度。*/
#define BLE_GAP_EVENT_LENGTH_DEFAULT        (3)  /**<默认事件长度，以1.25毫秒为单位。*/
/**@} */


/**@defgroup BLE_GAP_ROLE_COUNT GAP并发连接计数定义。
 * @{ */
#define BLE_GAP_ROLE_COUNT_PERIPH_DEFAULT      (1)   /**<同时充当外围设备的默认最大连接数。*/
#define BLE_GAP_ROLE_COUNT_CENTRAL_DEFAULT     (3)   /**<同时充当中心的默认最大连接数。*/
#define BLE_GAP_ROLE_COUNT_CENTRAL_SEC_DEFAULT (1)   /**<作为中心的所有连接之间共享的SMP实例的默认数量。*/
#define BLE_GAP_ROLE_COUNT_COMBINED_MAX        (20)  /**<外围和中心角色组合的最大支持并发连接数。*/

/**@} */

/**@brief 自动数据长度参数。*/
#define BLE_GAP_DATA_LENGTH_AUTO 0

/**@defgroup BLE_GAP_AUTH_PAYLOAD_TIMEOUT已验证有效负载超时定义。
  * @{ */
#define BLE_GAP_AUTH_PAYLOAD_TIMEOUT_MAX (48000) /**<以10毫秒为单位的最大认证有效负载超时，即8分钟。*/
#define BLE_GAP_AUTH_PAYLOAD_TIMEOUT_MIN (1)     /**<以10ms为单位的最小认证有效负载超时，即10ms。*/
/**@} */

/**@defgroup GAP_SEC_MODES GAP安全模式
 * @{ */
#define BLE_GAP_SEC_MODE 0x00 /**<无键（可用于拒绝）。*/
/**@} */

/**@brief Bluetooth低能模式下的信道总数。*/
#define BLE_GAP_CHANNEL_COUNT      (40)

/**@defgroup BLE_GAP_QOS_CHANNEL_SURVEY_INTERVALS服务质量（QOS）信道调查间隔定义
 * @{ */
#define BLE_GAP_QOS_CHANNEL_SURVEY_INTERVAL_CONTINUOUS  (0)       /**<连续渠道调查。*/
#define BLE_GAP_QOS_CHANNEL_SURVEY_INTERVAL_MIN_US      (7500)    /**<以微秒（7.5毫秒）为单位的最小信道测量间隔。*/
#define BLE_GAP_QOS_CHANNEL_SURVEY_INTERVAL_MAX_US      (4000000) /**<以微秒（4秒）为单位的最大信道测量间隔。*/
 /**@}  */

/** @} */


/**@addtogroup BLE_GAP_STRUCTURES结构
 * @{ */

/**@brief 广告事件属性。*/
typedef struct
{
  uint8_t type;                 /**<广告类型。请参见@ref BLE_GAP_ADV_TYPES。*/
  uint8_t anonymous        : 1; /**< 从所有PDU中省略广告客户的地址。
                                     @注意：匿名广告仅适用于
                                     @ref BLE_GAP_ADV_TYPE_EXTENDED_NONCONNECTABLE_NONSCANABLE_INDIRECTED和@ref BLE_GAP-ADV_TYPE_EXTENDED _NONCONNECT ABLE_NONsCANABLE_DIRECTED。*/
  uint8_t include_tx_power : 1; /**<此SoftDevice不支持此功能。*/
} ble_gap_adv_properties_t;


/**@brief 广告报告类型。*/
typedef struct
{
  uint16_t connectable   : 1; /**<可连接的广告事件类型。*/
  uint16_t scannable     : 1; /**<可扫描的广告事件类型。*/
  uint16_t directed      : 1; /**<定向广告事件类型。*/
  uint16_t scan_response : 1; /**<收到扫描响应。*/
  uint16_t extended_pdu  : 1; /**<收到扩展广告集。*/
  uint16_t status        : 2; /**<数据状态。请参见@ref BLE_GAP_ADV_DATA_STATUS。*/
  uint16_t reserved      : 9; /**<保留以备将来使用。*/
} ble_gap_adv_report_type_t;

/**@brief 广告辅助指针。*/
typedef struct
{
  uint16_t  aux_offset;   /**<从广告包开始到辅助包的时间偏移，单位为100 us。*/
  uint8_t   aux_phy;      /**<表示发送辅助广告数据包的PHY。参见@ref BLE_GAP_PHYS。*/
} ble_gap_aux_pointer_t;

/**@brief 蓝牙低能耗地址。*/
typedef struct
{
  uint8_t addr_id_peer : 1;       /**< 仅对对等地址有效。此位由SoftDevice设置，以指示地址是否已从可解析的专用地址解析（当对等方使用隐私时）。
                                       如果设置为1，则@ref addr和@ref addr_type指的是解析地址的标识地址。

                                       当@ref ble_gap_addr_t类型的变量用作API函数的输入时，将忽略此位。*/
  uint8_t addr_type    : 7;       /**<参见@ref BLE_GAP_ADDR_TYPES。*/
  uint8_t addr[BLE_GAP_ADDR_LEN]; /**<48位地址，LSB格式@如果@ref addr_type为@ref BLE_GAP_addr_type_ANONYMOUS，则不使用ref addr。*/
} ble_gap_addr_t;


/**@brief GAP连接参数。
 *
 * @note  当在事件中接收到ble_conn_params_t时，min_conn_interval和max_conn_interval将等于中心设置的连接间隔。
 *
 * @note  如果同时指定了conn_sup_timeout和max_conn_interval，则以下约束适用：conn_sup_timeout 4>（1+slave_elatency）max_conn_interval，对应于以下蓝牙规范要求：以毫秒为单位的监督超时应大于（1+conn_latency）conn_interval_max 2，其中conn_interval_max以毫秒为。
 */
typedef struct
{
  uint16_t min_conn_interval;         /**<以1.25 ms为单位的最小连接间隔，请参阅@ref BLE_GAP_CP_LIMITS。*/
  uint16_t max_conn_interval;         /**<以1.25 ms为单位的最大连接间隔，请参阅@ref BLE_GAP_CP_LIMITS。*/
  uint16_t slave_latency;             /**<连接事件数中的从属延迟，请参阅@ref BLE_GAP_CP_LIMITS。*/
  uint16_t conn_sup_timeout;          /**<以10ms为单位的连接监控超时，请参阅@ref BLE_GAP_CP_LIMITS。*/
} ble_gap_conn_params_t;


/**@brief GAP连接安全模式。
 *
 * 安全模式0级别0：完全没有访问权限（蓝牙核心规范未定义此级别）。\n安全模式1级别1：不需要安全（也称为开放链接）。\n安全模式1级别2：需要加密链路，不需要MITM保护。\n安全模式1级别3：需要MITM保护的加密链接。\n安全模式1第4级：LESC MITM保护加密链路，需要128位加密密钥。\n安全模式2级别1：需要签名或加密，不需要MITM保护。\n安全模式2级别2：需要MITM保护签名，除非链接是MITM保护加密的。\n
 */
typedef struct
{
  uint8_t sm : 4;                     /**<安全模式（1或2），0表示完全没有权限。*/
  uint8_t lv : 4;                     /**<级别（1、2、3或4），0表示完全没有权限。*/

} ble_gap_conn_sec_mode_t;


/**@brief GAP连接安全状态。*/
typedef struct
{
  ble_gap_conn_sec_mode_t sec_mode;           /**<此连接当前处于活动安全模式。*/
  uint8_t                 encr_key_size;      /**<当前有效加密密钥的长度，7到16个八位字节（仅适用于绑定过程）。*/
} ble_gap_conn_sec_t;

/**@brief 身份解析密钥。*/
typedef struct
{
  uint8_t irk[BLE_GAP_SEC_KEY_LEN];   /**<包含IRK的数组。*/
} ble_gap_irk_t;


/**@brief 信道掩码（40位）。每个信道都用一个位表示，该位按照蓝牙核心规范v5.0第6卷B部分第1.4.1节中定义的信道索引定位。数组元素0中包含的LSB表示信道索引0，位39表示信道索引39。如果位设置为1，则不使用信道。
 */
typedef uint8_t ble_gap_ch_mask_t[5];


/**@brief GAP广告参数。*/
typedef struct
{
  ble_gap_adv_properties_t properties;              /**<广告事件的属性。*/
  ble_gap_addr_t const    *p_peer_addr;             /**< Address of a known peer. @note ble_gap_addr_t:：addr_type不能是@ref ble_gap_addr_type_ANONYMOUS。
                                                         -当启用隐私并且本地设备使用@ref BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLABLE地址时，将在设备标识列表中搜索匹配的条目。如果设置了该设备标识的本地IRK，则该设备的本地IRK将用于生成广告分组中的广告客户地址字段。
                                                         -如果指向@ref ble_gap_adv_properties_t:：type，则必须将其设置为目标扫描仪或启动器。如果对等地址在设备标识列表中，则该设备的对等IRK将用于生成广告事件PDU中使用的@ref BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLABLE目标地址。*/
  uint32_t                 interval;                /**< Advertising interval in 625 us units. @sa BLE_GAP_ADV_interval@注意：如果@ref ble_gap_adv_properties_t:：type设置为
                                                               @ref BLE_GAP_ADV_TYPE_CONNECTABLE_NONSCANABLE_DIRECTED_HIGH_DUTY_CYCLE广告，忽略此参数。*/
  uint16_t                 duration;                /**< 以10ms为单位的广告持续时间。达到超时时，将引发@ref BLE_GAP_EVT_ADV_SET_TERMINATED类型的事件@sa BLE_GAP_ADV_TIMEOUT_VALUES（BLE_GAP_ ADV_TIMEOUT_VALUE）。
                                                         @注意：即使持续时间设置得太低，SoftDevice也将始终完成至少一个广告事件。*/
  uint8_t                  max_adv_evts;            /**< 禁用广告之前应发送的最大广告事件数。将值设置为0将禁用限制。当达到此参数指定的广告事件计数（如果不是0）时，广告将自动停止，并引发类型为@ref BLE_GAP_EVT_ADV_SET_TERMINATED的事件@note如果@ref BLE_GAP_ADV_properties_t:：type设置为
                                                               @ref BLE_GAP_ADV_TYPE_CONNECTABLE_NONSCANABLE_DIRECTED_HIGH_DUTY_CYCLE，忽略此参数。*/
  ble_gap_ch_mask_t        channel_mask;            /**<主要和次要广告频道的频道掩码。必须使用至少一个主信道，即信道索引37-39。不支持屏蔽辅助广告频道。*/
  uint8_t                  filter_policy;           /**<过滤策略@sa BLE_GAP_ADV_过滤器_。*/
  uint8_t                  primary_phy;             /**< Indicates the PHY on which the primary advertising channel packets are transmitted. If set to @ref 将使用BLE_GAP_PHY_AUTO，@ref BLE_GAP_MHY_1MBPS。有效值为@ref BLE_GAP_PHY_1MBPS和@ref BLE_GAP_PHY_CODED。
                                                         @注：如果@ref BLE_GAP_adv_properties_t:：类型不是扩展广告类型，primary_phy应指示@ref BLE_GAP_phy_1MBPS。*/
  uint8_t                  secondary_phy;           /**< 指示在其上传输辅助广告信道分组的PHY。如果设置为@ref BLE_GAP_PHY_AUTO，将使用@ref BLE_GAP_PHY_1MBPS。有效值为
                                                         @ref BLE_GAP_PHY_1MBPS、@ref BLE_GAP-PHY_2MBPS和@ref BLE-GAP_PHY_CODED。
                                                         如果@ref ble_gap_adv_properties_t:：type是扩展广告类型且可连接，则这是将用于建立连接并发送AUX_adv_IND数据包的PHY。@注意：当@ref ble_gap_adv.properties_t:：type不是扩展广告类型时，将忽略此参数。*/
  uint8_t                  set_id:4;                /**<广告集标识符将该广告集与由该设备和其他设备发送的其他广告集区分开来@注意：当@ref ble_gap_adv_properties_t:：type不是扩展广告类型时，将忽略此参数。*/
  uint8_t                  scan_req_notification:1; /**<为此广告集启用扫描请求通知。当收到扫描请求并且筛选器策略允许扫描仪地址时，将引发@ref BLE_GAP_EVT_scan_REQ_REPORT@注意：当@ref ble_gap_adv_properties_t:：type是不可扫描的广告类型时，将忽略此参数。*/
} ble_gap_adv_params_t;


/**@brief GAP广告数据缓冲区。
 *
 * 应用程序必须为播发提供缓冲区。存储器应位于应用程序RAM中，并且在广告时不得修改。数据应保持有效，直到：
 *  - @ref 引发BLE_GAP_EVT_ADV_SET_TERMINATED。
 *  - @ref BLE_GAP_EVT_CONNECTED被引发，@ref BLE_GAP_EVT_CONNECTED_t:：adv_handle设置为相应的广告句柄。
 *  -广告停止。
 *  -广告数据已更改。要在广告时更新广告数据，请为@ref sd_ble_gap_adv_set_figure提供新的缓冲区。*/
typedef struct
{
  ble_data_t       adv_data;                     /**<广告数据@注意：只能为允许包含广告数据的@ref ble_gap_adv_properties_t:：类型指定广告数据。*/
  ble_data_t       scan_rsp_data;                /**<扫描响应数据@注意：只能为可扫描的@ref ble_gap_adv_properties_t:：类型指定扫描响应数据。*/
} ble_gap_adv_data_t;


/**@brief GAP扫描参数。*/
typedef struct
{
  uint8_t               extended               : 1; /**<如果为1，扫描仪将接受扩展的广告包。如果设置为0，扫描仪将不会在辅助广告频道上接收广告包，并且无法接收长广告PDU。*/
  uint8_t               report_incomplete_evts : 1; /**< If 1, events of type @ref ble_gap_evt_adv_report_t可以将@ref ble_gap_adv_rereport_type_t:：状态设置为@ref ble_gap_adv_DATA_status_INCOMPLETE_MORE_DATA。与@ref sd_ble_gap_connect一起使用时忽略此参数
                                                         @注意：这可能用于中止从扩展广告事件接收更多数据包，并且仅适用于扩展扫描，请参阅@ref sd_ble_gap_scan_start@注意：此SoftDevice不支持此功能。*/
  uint8_t               active                 : 1; /**<如果为1，则通过发送扫描请求来执行活动扫描。当与@ref sd_ble_gap_connect一起使用时，将忽略此参数。*/
  uint8_t               filter_policy          : 2; /**<扫描筛选器策略@sa BLE_GAP_SCAN_过滤器_@注意：当与@ref sd_BLE_GAP_connect一起使用时，只有@ref BLE_GAP_SCAN_FP_ACCEPT_ALL和@ref BLE-GAP_SCAN-FP_WHITELIST有效*/
  uint8_t               scan_phys;                  /**< Bitfield of PHYs to scan on. If set to @ref BLE_GAP_PHY_AUTO，scan_phys将默认为@ref BLE_GAP-PHY_1MBPS。
                                                         -如果@ref ble_gap_scan_params_t:：extended设置为0，则唯一支持的PHY是@ref ble_gap_PHY_1MBPS。
                                                         -当与@ref sd_ble_gap_scan_start一起使用时，位字段指示扫描仪将用于扫描主要广告频道的PHY。扫描仪将接受
                                                           @ref BLE_GAP_PHYS_SUPPORTED作为辅助广告信道PHY。
                                                         -当与@ref sd_ble_gap_connect一起使用时，位字段指示启动器将用于扫描主要广告频道的PHY。启动器将接受在@ref BLE_GAP_PHYS_SUPPORTED PHY上启动的连接。如果scan_phys包含@ref BLE_GAP_PHY_1MBPS和/或@ref BLE_GAP_PHY_2MBPS，则主扫描PHY为@ref BLE-GAP_PHY_1 MBPS。如果scan_phys还包含@ref BLE_GAP_PHY_CODED，则主扫描PHY也将包含@ref BLE_GAP_PHY_CODED。如果唯一的扫描PHY是@ref BLE_GAP_PHY_CODED，则主扫描PHY仅是@ref BLE_GAP_PHY_CODED。*/
  uint16_t              interval;                   /**<扫描间隔（625美制单位）@sa BLE_GAP_SCAN_INTERVALS（BLE_GAP_扫描_终止）。*/
  uint16_t              window;                     /**<扫描窗口（625美制单位）@sa BLE_GAP_SCAN_WINDOW（BLE_GAP_扫描_窗口）。如果scan_phys同时包含@ref BLE_GAP_PHY_1MBPS和@ref BLE-GAP_PHY_CODED，则间隔应大于或等于扫描窗口的两倍。*/
  uint16_t              timeout;                    /**<以10毫秒为单位的扫描超时@sa BLE_GAP_SCAN_TIMEOUT。*/
  ble_gap_ch_mask_t     channel_mask;               /**<主要和次要广告频道的频道掩码。必须将至少一个主信道（即信道索引37-39）设置为0。不支持掩蔽次要信道。*/
} ble_gap_scan_params_t;


/**@brief 隐私
 *
 *        隐私功能为设备提供了一种避免在一段时间内被跟踪的方法。启用隐私功能后，将隐藏本地设备标识，并将其替换为以指定间隔自动刷新的专用地址。
 *
 *        如果设备仍然希望被其他对等方识别，则需要共享其身份解析密钥（IRK）。使用该密钥，设备可以生成一个只有拥有该密钥的对等方才能识别的随机私有地址，并且设备可以在不暴露其真实身份的情况下建立连接。
 *
 *        Both network privacy (@ref BLE_GAP_PRIVACY_MODE_NETWORK_PRIVACY）和设备隐私（@ref BLE_GAP_ RIVACY.MODE_device_PRIVACY）。
 *
 * @note  如果更新了设备IRK，则新的IRK将成为在@ref sd_ble_gap_privacy_set返回后执行的所有绑定过程中分发的IRK。绑定过程中分发的IRK是在调用@ref sd_ble_gap_sec_params_reply时激活的设备IRK。
 */
typedef struct
{
  uint8_t        privacy_mode;         /**<隐私模式，请参阅@ref BLE_GAP_Privacy_MODES。默认值为@ref BLE_GAP_PRIVACY_MODE_OFF。*/
  uint8_t        private_addr_type;    /**<专用地址类型必须是@ref BLE_GAP_ADDR_type_RANDOM_private_RESOLABLE或@ref BLE_GAP_ADDR_type_RANDOM_PRIVAT_NON_RESOLABLE。*/
  uint16_t       private_addr_cycle_s; /**<专用地址周期间隔（秒）。提供地址周期值0将使用@ref BLE_GAP_default_PRIVATE_ADDR_cycle_INTERVAL_S定义的默认值。*/
  ble_gap_irk_t *p_device_irk;         /**<用作输入时，指向将用作默认IRK的IRK结构的指针。如果为NULL，将使用设备默认IRK。当用作输出时，指向将写入当前默认IRK的IRK结构的指针。如果为NULL，则忽略此参数。默认情况下，默认IRK用于为本地设备生成随机私有可解析地址，除非另有指示。*/
} ble_gap_privacy_params_t;


/**@brief TX和RX的PHY首选项
 * @note  tx_phys和rx_phys是位字段。可以在其中设置多个比特以指示每个方向的多个优选PHY。
 * @code
 * p_gap_phys->tx_phys=BLE_gap_PHY_1MBPS | BLE_gap-PHY_2MBPS；
 * p_gap_phys->rx_phys=BLE_gap_PHY_1MBPS | BLE_gap-PHY_2MBPS；
 * @endcode
 *
 */
typedef struct
{
  uint8_t tx_phys;     /**<首选传输PHY，请参阅@ref BLE_GAP_PHYs。*/
  uint8_t rx_phys;     /**<首选接收PHY，请参阅@ref BLE_GAP_PHYs。*/
} ble_gap_phys_t;

/** @brief 可在粘接过程中更换的钥匙。*/
typedef struct
{
  uint8_t enc     : 1;                        /**<长期密钥和主标识。*/
  uint8_t id      : 1;                        /**<身份解析密钥和身份地址信息。*/
  uint8_t sign    : 1;                        /**<连接签名解析密钥。*/
  uint8_t link    : 1;                        /**<从LTK导出链接密钥。*/
} ble_gap_sec_kdist_t;


/**@brief GAP安全参数。*/
typedef struct
{
  uint8_t               bond      : 1;             /**<执行粘合。*/
  uint8_t               mitm      : 1;             /**<启用中间人保护。*/
  uint8_t               lesc      : 1;             /**<启用LE安全连接配对。*/
  uint8_t               keypress  : 1;             /**<启用按键通知的生成。*/
  uint8_t               io_caps   : 3;             /**<IO能力，请参阅@ref BLE_GAP_IO_CAPS。*/
  uint8_t               oob       : 1;             /**< OOB数据标志。
                                                        -在LE传统配对中，如果设备具有带外认证数据，则设置此标志。如果两个设备都具有带外认证数据，则使用OOB方法。
                                                        -在LE安全连接配对中，如果设备具有对等设备的带外认证数据，则设置此标志。如果至少一个设备的OOB数据可用，则使用OOB方法。*/
  uint8_t               min_key_size;              /**<最小加密密钥大小（以八位字节为单位），介于7和16之间。如果为0，则不适用于此实例。*/
  uint8_t               max_key_size;              /**<min_key_size和16之间的最大加密密钥大小（以八位字节为单位）。*/
  ble_gap_sec_kdist_t   kdist_own;                 /**<密钥分发位图：本地设备将分发的密钥。*/
  ble_gap_sec_kdist_t   kdist_peer;                /**<密钥分发位图：远程设备将分发的密钥。*/
} ble_gap_sec_params_t;


/**@brief GAP加密信息。*/
typedef struct
{
  uint8_t   ltk[BLE_GAP_SEC_KEY_LEN];   /**<长期密钥。*/
  uint8_t   lesc : 1;                   /**<使用LE安全连接生成的密钥。*/
  uint8_t   auth : 1;                   /**<已验证密钥。*/
  uint8_t   ltk_len : 6;                /**<LTK长度（八位字节）。*/
} ble_gap_enc_info_t;


/**@brief GAP主标识。*/
typedef struct
{
  uint16_t  ediv;                       /**<加密多元化。*/
  uint8_t   rand[BLE_GAP_SEC_RAND_LEN]; /**<随机数。*/
} ble_gap_master_id_t;


/**@brief GAP签署信息。*/
typedef struct
{
  uint8_t   csrk[BLE_GAP_SEC_KEY_LEN];        /**<连接签名解析密钥。*/
} ble_gap_sign_info_t;


/**@brief GAP LE安全连接P-256公钥。*/
typedef struct
{
  uint8_t   pk[BLE_GAP_LESC_P256_PK_LEN];        /**<LE安全连接椭圆曲线Diffie-Hellman P-256公钥。以标准SMP协议格式存储：｛X，Y｝都以小端序存储。*/
} ble_gap_lesc_p256_pk_t;


/**@brief GAP LE安全连接DHKey。*/
typedef struct
{
  uint8_t   key[BLE_GAP_LESC_DHKEY_LEN];        /**<LE安全连接椭圆曲线Diffie-Hellman密钥。以小端序存储。*/
} ble_gap_lesc_dhkey_t;


/**@brief GAP LE安全连接OOB数据。*/
typedef struct
{
  ble_gap_addr_t  addr;                          /**<设备的蓝牙地址。*/
  uint8_t         r[BLE_GAP_SEC_KEY_LEN];        /**<随机数。*/
  uint8_t         c[BLE_GAP_SEC_KEY_LEN];        /**<确认值。*/
} ble_gap_lesc_oob_data_t;


/**@brief @ref BLE_GAP_EVT_CONNECTED的事件结构。*/
typedef struct
{
  ble_gap_addr_t        peer_addr;              /**<对等设备的蓝牙地址。如果已解析的peer_addr：@ref ble_gap_addr_t:：addr_id_epeer设置为1，并且该地址是设备的标识地址。*/
  uint8_t               role;                   /**<此连接的BLE角色，请参见@ref BLE_GAP_ROLES*/
  ble_gap_conn_params_t conn_params;            /**<GAP连接参数。*/
  uint8_t               adv_handle;             /**<广告已结束的广告句柄。仅当角色设置为@ref BLE_GAP_role_PERIPH时，才设置此变量。*/
  ble_gap_adv_data_t    adv_data;               /**<与终止的广告集相对应的广告缓冲区。@ref sd_ble_gap_adv_set_figure中提供的广告缓冲区现已释放。仅当角色设置为@ref BLE_GAP_role_PERIPH时，才设置此变量。*/
} ble_gap_evt_connected_t;


/**@brief @ref BLE_GAP_EVT_DISCONNECTED的事件结构。*/
typedef struct
{
  uint8_t reason;                               /**<HCI错误代码，请参阅@ref BLE_HCI_STATUS_CODES。*/
} ble_gap_evt_disconnected_t;


/**@brief @ref BLE_GAP_EVT_CONN_PARAM_UPDATE的事件结构。*/
typedef struct
{
  ble_gap_conn_params_t conn_params;            /**<GAP连接参数。*/
} ble_gap_evt_conn_param_update_t;

/**@brief @ref BLE_GAP_EVT_PHY_UPDATE_REQUEST的事件结构。*/
typedef struct
{
  ble_gap_phys_t peer_preferred_phys;            /**<对等方更喜欢使用的PHY。*/
} ble_gap_evt_phy_update_request_t;

/**@brief @ref BLE_GAP_EVT_PHY_UPDATE的事件结构。*/
typedef struct
{
  uint8_t status;                               /**<过程状态，请参见@ref BLE_HCI_Status_CODES。*/
  uint8_t tx_phy;                               /**<此连接的TX PHY，请参阅@ref BLE_GAP_PHYS。*/
  uint8_t rx_phy;                               /**<此连接的RX PHY，请参阅@ref BLE_GAP_PHYS。*/
} ble_gap_evt_phy_update_t;

/**@brief @ref BLE_GAP_EVT_SEC_PARAMS_REQUEST的事件结构。*/
typedef struct
{
  ble_gap_sec_params_t peer_params;             /**<启动器安全参数。*/
} ble_gap_evt_sec_params_request_t;


/**@brief @ref BLE_GAP_EVT_SEC_INFO_REQUEST的事件结构。*/
typedef struct
{
  ble_gap_addr_t      peer_addr;                     /**<对等设备的蓝牙地址。*/
  ble_gap_master_id_t master_id;                     /**<LTK查找的主标识。*/
  uint8_t             enc_info  : 1;                 /**<如果为1，则需要加密信息。*/
  uint8_t             id_info   : 1;                 /**<如果为1，则需要身份信息。*/
  uint8_t             sign_info : 1;                 /**<如果为1，则需要签名信息。*/
} ble_gap_evt_sec_info_request_t;


/**@brief @ref BLE_GAP_EVT_PASSKEY_DISPLAY的事件结构。*/
typedef struct
{
  uint8_t passkey[BLE_GAP_PASSKEY_LEN];         /**<6位ASCII密码（仅限“0”-“9”位）。*/
  uint8_t match_request : 1;                    /**<如果1要求应用程序使用@ref sd_ble_gap_auth_key_reply报告匹配，如果没有匹配，则使用@ref ble_gap_auth_key_TYPE_NONE，如果有匹配，则采用@ref ble_gap_auth_2KEY_TYPE-PASSKEY。*/
} ble_gap_evt_passkey_display_t;

/**@brief @ref BLE_GAP_EVT_KEY_PRESSED的事件结构。*/
typedef struct
{
  uint8_t kp_not;         /**<按键通知类型，请参见@ref BLE_GAP_KP_NOT_TYPES。*/
} ble_gap_evt_key_pressed_t;


/**@brief @ref BLE_GAP_EVT_AUTH_KEY_REQUEST的事件结构。*/
typedef struct
{
  uint8_t key_type;                             /**<参见@ref BLE_GAP_AUTH_KEY_TYPES。*/
} ble_gap_evt_auth_key_request_t;

/**@brief @ref BLE_GAP_EVT_LESC_DHKEY_REQUEST的事件结构。*/
typedef struct
{
  ble_gap_lesc_p256_pk_t *p_pk_peer;  /**<LE安全连接远程P-256公钥。这将指向调用@ref sd_ble_gap_sec_params_reply期间键集中应用程序提供的内存。*/
  uint8_t oobd_req       :1;          /**<需要LESC OOB数据。需要调用@ref sd_ble_gap_lesc_oob_data_set来完成该过程。*/
} ble_gap_evt_lesc_dhkey_request_t;


/**@brief 支持安全级别。
 * @note  参见蓝牙规范4.2版第3卷C部分第10章第10.2.1节。
*/
typedef struct
{
  uint8_t lv1 : 1;                              /**<如果1：支持级别1。*/
  uint8_t lv2 : 1;                              /**<如果1：支持级别2。*/
  uint8_t lv3 : 1;                              /**<如果1：支持级别3。*/
  uint8_t lv4 : 1;                              /**<如果1：支持级别4。*/
} ble_gap_sec_levels_t;


/**@brief 加密密钥。*/
typedef struct
{
  ble_gap_enc_info_t    enc_info;             /**<加密信息。*/
  ble_gap_master_id_t   master_id;            /**<主标识。*/
} ble_gap_enc_key_t;


/**@brief 身份密钥。*/
typedef struct
{
  ble_gap_irk_t         id_info;              /**<身份解析密钥。*/
  ble_gap_addr_t        id_addr_info;         /**<身份地址。*/
} ble_gap_id_key_t;


/**@brief 安全密钥。*/
typedef struct
{
  ble_gap_enc_key_t      *p_enc_key;           /**<加密密钥，或NULL。*/
  ble_gap_id_key_t       *p_id_key;            /**<标识密钥，或NULL。*/
  ble_gap_sign_info_t    *p_sign_key;          /**<签名密钥，或NULL。*/
  ble_gap_lesc_p256_pk_t *p_pk;                /**<LE安全连接P-256公钥。当处于调试模式时，应用程序必须使用核心蓝牙规范v4.2第3卷第H部分第2.3.5.6.1节中定义的值*/
} ble_gap_sec_keys_t;


/**@brief 本地密钥和对等密钥的安全密钥集。*/
typedef struct
{
  ble_gap_sec_keys_t            keys_own;     /**<本地设备分发的密钥。对于LE安全连接，加密密钥将在本地生成，并在绑定时始终存储。*/
  ble_gap_sec_keys_t            keys_peer;    /**<远程设备分发的密钥。对于LE安全连接，p_enc_key必须始终为NULL。*/
} ble_gap_sec_keyset_t;


/**@brief 数据长度更新过程参数。*/
typedef struct
{
  uint16_t max_tx_octets;   /**<控制器支持传输单个链路层数据信道PDU的最大有效载荷八位字节数。*/
  uint16_t max_rx_octets;   /**<控制器支持接收单个链路层数据信道PDU的最大有效载荷八位字节数。*/
  uint16_t max_tx_time_us;  /**<控制器支持传输单个链路层数据信道PDU的最长时间（以微秒为单位）。*/
  uint16_t max_rx_time_us;  /**<控制器支持接收单个链路层数据信道PDU的最长时间（以微秒为单位）。*/
} ble_gap_data_length_params_t;


/**@brief 数据长度更新过程本地限制。*/
typedef struct
{
  uint16_t tx_payload_limited_octets; /**<如果>0，则所请求的TX数据包长度太长了这么多八位字节。*/
  uint16_t rx_payload_limited_octets; /**<如果>0，则所请求的RX数据包长度太长了这么多八位字节。*/
  uint16_t tx_rx_time_limited_us;     /**<如果>0，则所请求的TX和RX分组长度的组合太长了这么多微秒。*/
} ble_gap_data_length_limitation_t;


/**@brief @ref BLE_GAP_EVT_AUTH_STATUS的事件结构。*/
typedef struct
{
  uint8_t               auth_status;            /**<身份验证状态，请参阅@ref BLE_GAP_SEC_status。*/
  uint8_t               error_src : 2;          /**<出错时，导致故障的源，请参阅@ref BLE_GAP_SEC_STATUS_SOURCES。*/
  uint8_t               bonded : 1;             /**<程序导致债券。*/
  uint8_t               lesc : 1;               /**<过程导致LE安全连接。*/
  ble_gap_sec_levels_t  sm1_levels;             /**<安全模式1支持的级别。*/
  ble_gap_sec_levels_t  sm2_levels;             /**<安全模式2支持的级别。*/
  ble_gap_sec_kdist_t   kdist_own;              /**<说明本地设备交换（分发）了哪些密钥的位图。如果与LE安全连接绑定，则始终设置enc位。*/
  ble_gap_sec_kdist_t   kdist_peer;             /**<说明远程设备交换（分发）了哪些密钥的位图。如果与LE安全连接绑定，则永远不会设置enc位。*/
} ble_gap_evt_auth_status_t;


/**@brief @ref BLE_GAP_EVT_CONN_SEC_UPDATE的事件结构。*/
typedef struct
{
  ble_gap_conn_sec_t conn_sec;                  /**<连接安全级别。*/
} ble_gap_evt_conn_sec_update_t;


/**@brief @ref BLE_GAP_EVT_TIMEOUT的事件结构。*/
typedef struct
{
  uint8_t src;                                  /**<超时事件源，请参阅@ref BLE_GAP_timeout_SOURCES。*/
  union
  {
    ble_data_t adv_report_buffer;               /**<如果源设置为@ref BLE_GAP_TIMEOUT_SRC_SCAN，则释放的扫描缓冲区包含在此字段中。*/
  } params;                                     /**<事件参数。*/
} ble_gap_evt_timeout_t;


/**@brief @ref BLE_GAP_EVT_RSSI_CHANGED的事件结构。*/
typedef struct
{
  int8_t  rssi;                                 /**<接收信号强度指示（dBm）@注ERRATA-153要求基于温度测量对rssi样本进行补偿。*/
  uint8_t ch_index;                             /**<测量信号强度的数据信道索引（0-36）。*/
} ble_gap_evt_rssi_changed_t;

/**@brief @ref BLE_GAP_EVT_ADV_SET_TERMINATED的事件结构*/
typedef struct
{
  uint8_t             reason;                         /**<广告集终止的原因。参见@ref BLE_GAP_EVT_ADV_SET_TERMINATED_REASON。*/
  uint8_t             adv_handle;                     /**<广告已结束的广告句柄。*/
  uint8_t             num_completed_adv_events;       /**<如果@ref ble_gap_adv_params_t:：max_adv_evts未设置为0，则此字段表示已完成的广告事件数。*/
  ble_gap_adv_data_t  adv_data;                       /**<与终止的广告集相对应的广告缓冲区。@ref sd_ble_gap_adv_set_figure中提供的广告缓冲区现已释放。*/
} ble_gap_evt_adv_set_terminated_t;

/**@brief @ref BLE_GAP_EVT_ADV_REPORT的事件结构。
 *
 * @note 如果@ref ble_gap_adv_report_type_t:：status设置为@ref ble_gap_adv_DATA_status_INCOMPLETE_MORE_DATA，则广告报告中的所有字段可能都不可用。
 *
 * @note 当ble_gap_adv_report_type_t:：status未设置为@ref ble_gap_adv_DATA_status_INCOMPLETE_MORE_DATA时，扫描将暂停。要继续扫描，请调用@ref sd_ble_gap_scan_start。
 */
typedef struct
{
  ble_gap_adv_report_type_t type;                  /**<广告报告类型。请参见@ref ble_gap_adv_report_type_t。*/
  ble_gap_addr_t            peer_addr;             /**< 对等设备的蓝牙地址。如果已解析peer_addr：
                                                        @ref ble_gap_addr_t:：addr_idpeer设置为1，并且该地址是对等体的标识地址。*/
  ble_gap_addr_t            direct_addr;           /**< 包含广告事件的目标地址，如果
                                                        @ref ble_gap_adv_report_type_t:：directed设置为1。如果SoftDevice能够解析地址，
                                                        @ref ble_gap_addr_t:：addr_idpeer设置为1，direct_addr包含本地标识地址。如果广告事件的目标地址是@ref BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLABLE，并且SoftDevice无法解析该地址，则应用程序可以尝试解析该地址以确定广告事件是否指向我们。*/
  uint8_t                   primary_phy;           /**<表示接收主要广告数据包的PHY。参见@ref BLE_GAP_PHYS。*/
  uint8_t                   secondary_phy;         /**< 指示接收辅助广告数据包的PHY。
                                                        参见@ref BLE_GAP_PHYS。如果在辅助广告频道上没有接收到数据包，则此字段设置为@ref BLE_GAP_PHY_NOT_set。*/
  int8_t                    tx_power;              /**<广告主在接收的最后一个数据包报头中报告的发送功率。如果最后接收的数据包不包含Tx功率字段，则该字段设置为@ref BLE_GAP_POWER_LEVEL_INVALID@注意，TX功率仅包含在扩展广告包中。*/
  int8_t                    rssi;                  /**<接收到的最后一个数据包的接收信号强度指示（dBm）@注ERRATA-153要求基于温度测量对rssi样本进行补偿。*/
  uint8_t                   ch_index;              /**<接收最后一个广告包的频道索引（0-39）。*/
  uint8_t                   set_id;                /**<设置接收到的广告数据的ID。如果设置为@ref BLE_GAP_ADV_REPORT_Set_ID_not_AVAILABLE，则不存在集合ID。*/
  uint16_t                  data_id:12;            /**<接收到的广告数据的广告数据ID。如果@ref ble_gap_evt_adv_report_t:：set_ID设置为@ref ble_gap_adv_report_set_ID_not_AVAILABLE，则不存在数据ID。*/
  ble_data_t                data;                  /**< Received advertising or scan response data. If @ref ble_gap_adv_report_type_t:：状态未设置为
                                                        @ref BLE_GAP_ADV_DATA_STATUS_INCOMPLETE_MORE_DATA，@ref sd_BLE_GAP_scan_start中提供的数据缓冲区现已释放。*/
  ble_gap_aux_pointer_t     aux_pointer;           /**< 此扩展广告中下一个广告包的偏移量和PHY
                                                        事件@注意：仅当@ref ble_gap_adv_report_type_t:：status设置为@ref ble_gap_adv_DATA_status_INCOMPLETE_MORE_DATA时，才设置此字段。*/
} ble_gap_evt_adv_report_t;


/**@brief @ref BLE_GAP_EVT_SEC_REQUEST的事件结构。*/
typedef struct
{
  uint8_t    bond       : 1;                       /**<执行粘合。*/
  uint8_t    mitm       : 1;                       /**<要求中间人保护。*/
  uint8_t    lesc       : 1;                       /**<请求的LE安全连接。*/
  uint8_t    keypress   : 1;                       /**<请求生成按键通知。*/
} ble_gap_evt_sec_request_t;


/**@brief @ref BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST的事件结构。*/
typedef struct
{
  ble_gap_conn_params_t conn_params;            /**<GAP连接参数。*/
} ble_gap_evt_conn_param_update_request_t;


/**@brief @ref BLE_GAP_EVT_SCAN_REQ_REPORT的事件结构。*/
typedef struct
{
  uint8_t                 adv_handle;        /**<接收到扫描请求的广告集的广告句柄*/
  int8_t                  rssi;              /**<接收信号强度指示（dBm）@注ERRATA-153要求基于温度测量对rssi样本进行补偿。*/
  ble_gap_addr_t          peer_addr;         /**<对等设备的蓝牙地址。如果已解析的peer_addr：@ref ble_gap_addr_t:：addr_id_epeer设置为1，并且该地址是设备的标识地址。*/
} ble_gap_evt_scan_req_report_t;


/**@brief @ref BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST的事件结构。*/
typedef struct
{
  ble_gap_data_length_params_t peer_params; /**<对等数据长度参数。*/
} ble_gap_evt_data_length_update_request_t;

/**@brief @ref BLE_GAP_EVT_DATA_LENGTH_UPDATE的事件结构。*/
typedef struct
{
  ble_gap_data_length_params_t effective_params;  /**<有效数据长度参数。*/
} ble_gap_evt_data_length_update_t;


/**@brief @ref BLE_GAP_EVT_QOS_CHANNEL_SURVEY_REPORT的事件结构。*/
typedef struct
{
  int8_t channel_energy[BLE_GAP_CHANNEL_COUNT]; /**<蓝牙低能量信道上的测量能量，单位为dBm，由信道索引索引。如果给定信道没有可用的测量，则channel_energy设置为@ref BLE_GAP_POWER_LEVEL_INVALID。*/
} ble_gap_evt_qos_channel_survey_report_t;

/**@brief GAP事件结构。*/
typedef struct
{
  uint16_t conn_handle;                                     /**<发生事件的连接句柄。*/
  union                                                     /**<由封闭结构中的evt_id标识的联合替换项。*/
  {
    ble_gap_evt_connected_t                   connected;                    /**<连接的事件参数。*/
    ble_gap_evt_disconnected_t                disconnected;                 /**<断开连接的事件参数。*/
    ble_gap_evt_conn_param_update_t           conn_param_update;            /**<连接参数更新参数。*/
    ble_gap_evt_sec_params_request_t          sec_params_request;           /**<安全参数请求事件参数。*/
    ble_gap_evt_sec_info_request_t            sec_info_request;             /**<安全信息请求事件参数。*/
    ble_gap_evt_passkey_display_t             passkey_display;              /**<Passkey显示事件参数。*/
    ble_gap_evt_key_pressed_t                 key_pressed;                  /**<按键事件参数。*/
    ble_gap_evt_auth_key_request_t            auth_key_request;             /**<身份验证密钥请求事件参数。*/
    ble_gap_evt_lesc_dhkey_request_t          lesc_dhkey_request;           /**<LE安全连接DHKey计算请求。*/
    ble_gap_evt_auth_status_t                 auth_status;                  /**<身份验证状态事件参数。*/
    ble_gap_evt_conn_sec_update_t             conn_sec_update;              /**<连接安全更新事件参数。*/
    ble_gap_evt_timeout_t                     timeout;                      /**<超时事件参数。*/
    ble_gap_evt_rssi_changed_t                rssi_changed;                 /**<RSSI事件参数。*/
    ble_gap_evt_adv_report_t                  adv_report;                   /**<广告报告事件参数。*/
    ble_gap_evt_adv_set_terminated_t          adv_set_terminated;           /**<广告设置终止事件参数。*/
    ble_gap_evt_sec_request_t                 sec_request;                  /**<安全请求事件参数。*/
    ble_gap_evt_conn_param_update_request_t   conn_param_update_request;    /**<连接参数更新参数。*/
    ble_gap_evt_scan_req_report_t             scan_req_report;              /**<扫描请求报告参数。*/
    ble_gap_evt_phy_update_request_t          phy_update_request;           /**<PHY更新请求事件参数。*/
    ble_gap_evt_phy_update_t                  phy_update;                   /**<PHY更新参数。*/
    ble_gap_evt_data_length_update_request_t  data_length_update_request;   /**<数据长度更新请求事件参数。*/
    ble_gap_evt_data_length_update_t          data_length_update;           /**<数据长度更新事件参数。*/
    ble_gap_evt_qos_channel_survey_report_t   qos_channel_survey_report;    /**<服务质量（QoS）信道调查报告参数。*/
  } params;                                                                 /**<事件参数。*/
} ble_gap_evt_t;


/**
 * @brief BLE GAP连接配置参数，用@ref sd_BLE_cfg_set设置。
 *
 * @retval ：：NRF_ERROR_CONN_COUNT连接配置的连接计数为零。
 * @retval ：：NRF_ERROR_INVALID_PARAM以下一项或多项为真：
 *                                    -所有连接配置的conn_count总和超过了UINT8_MAX。
 *                                    -事件长度小于@ref BLE_GAP_event_length_MIN。
 */
typedef struct
{
  uint8_t  conn_count;     /**<应用程序可以使用此配置创建的并发连接数。默认值和最小值为@ref BLE_GAP_CONN_COUNT_default。*/
  uint16_t event_length;   /**< 在每个连接间隔上为该连接留出的时间，单位为1.25毫秒。
                                默认值为@ref BLE_GAP_EVENT_LENGTH_default，最小值为@ref BLE_GAP-EVENT_LENGTH_MIN。事件长度和连接间隔是设置连接吞吐量的主要参数。有关吞吐量的详细信息，请参阅SoftDevice规范。*/
} ble_gap_conn_cfg_t;


/**
 * @brief 不同连接角色中最大并发连接的配置，设置为
 * @ref sd_ble_cfg_set设置。
 *
 * @retval ：：NRF_ERROR_CONN_COUNT peripher_role_COUNT和central_role_COUNT之和太大。支持的最大并发连接总数为@ref BLE_GAP_ROLE_COUNT_COMBINED_MAX。
 * @retval ：：NRF_ERROR_INVALID_PARAM central_sec_count大于central_role_count。
 * @retval ：：NRF_ERROR_RESOURCES adv_set_count太大。支持的最大广告句柄为@ref BLE_GAP_ADV_SET_COUNT_MAX。
 */
typedef struct
{
  uint8_t adv_set_count;      /**<广告集的最大数量。默认值为@ref BLE_GAP_ADV_SET_COUNT_Default。*/
  uint8_t periph_role_count;  /**<同时充当外围设备的最大连接数。默认值为@ref BLE_GAP_ROLE_COUNT_PERIPH_Default。*/
  uint8_t central_role_count; /**<同时充当中心的最大连接数。默认值为@ref BLE_GAP_ROLE_COUNT_CENTRAL_Default。*/
  uint8_t central_sec_count;  /**<充当中心的所有连接之间共享的SMP实例数。默认值为@ref BLE_GAP_ROLE_COUNT_CENTRAL_SEC_Default。*/
  uint8_t qos_channel_survey_role_available:1; /**<如果设置，则应用程序可以使用@ref sd_ble_gap_QoS_channel_survey_start使用服务质量（QoS）信道调查模块。*/
} ble_gap_cfg_role_count_t;


/**
 * @brief 设备名称及其属性，用@ref sd_ble_cfg_set设置。
 *
 * @note  如果未配置设备名称，则默认设备名称将为
 *        @ref BLE_GAP_DEVNAME_DEFAULT，最大设备名称长度为
 *        @ref BLE_GAP_DEVNAME_DEFAULT_LEN，vloc将设置为@ref BLE_GATTS_vloc_STACK，设备名称将没有写入权限。
 *
 * @note  如果@ref max_len大于@ref BLE_GAP_DEVNAME_DEFAULT_len，并且vloc设置为@ref BLE_GATTS_vloc_STACK，则必须增加属性表大小，以便为较长的设备名称留出空间（请参见
 *        @ref sd_ble_cfg_set和@ref ble_gatts_cfg_attr_tab_size_t）。
 *
 * @note  如果vloc为@ref BLE_GATTS_vloc_STACK：
 *        -p_value必须指向非易失性存储器（闪存）或为NULL。
 *        -如果p_value为NULL，则设备名称最初将为空。
 *
 * @note  如果vloc为@ref BLE_GATTS_vloc_USER：
 *        -p_value不能为NULL。
 *        -如果设备名是可写的，p_value必须指向易失性存储器（RAM）。
 *
 * @retval ：：NRF_ERROR_INVALID_PARAM以下一项或多项为真：
 *                                    -设备名称位置（vloc）无效。
 *                                    -设备名称安全模式无效。
 * @retval ：：NRF_ERROR_INVALID_LENGTH以下一项或多项为真：
 *                                    -设备名称长度无效（必须介于0和@ref BLE_GAP_DEVNAME_MAX_LEN之间）。
 *                                    -对于给定的属性表，设备名称长度太长。
 * @retval ：：不支持NRF_ERROR_NOT_SUPPORTED设备名称安全模式。
 */
typedef struct
{
  ble_gap_conn_sec_mode_t  write_perm;   /**<写入权限。*/
  uint8_t                  vloc:2;       /**<值位置，请参见@ref BLE_GATTS_VLOCS。*/
  uint8_t                 *p_value;      /**<指向存储或将存储值（设备名称）的位置的指针。*/
  uint16_t                 current_len;  /**<p_value指向的内存的当前长度（字节）。*/
  uint16_t                 max_len;      /**<p_value指向的内存的最大长度（字节）。*/
} ble_gap_cfg_device_name_t;


/**@brief GAP配置的配置结构。*/
typedef union
{
  ble_gap_cfg_role_count_t  role_count_cfg;  /**<角色计数配置，cfg_id为@ref BLE_GAP_cfg_Role_count。*/
  ble_gap_cfg_device_name_t device_name_cfg; /**<设备名称配置，cfg_id为@ref BLE_GAP_cfg_Device_name。*/
} ble_gap_cfg_t;


/**@brief 通道贴图选项。
 *
 * @details 与@ref sd_ble_opt_get一起使用以获取当前频道映射
 *          or @ref sd_ble_opt_set设置新的频道映射。设置频道映射时，它将应用于所有当前和将来的连接。获取当前频道映射时，它将应用于单个连接，并且必须提供连接句柄。
 *
 * @note 根据连接参数，设置频道映射可能需要一些时间。每个连接所花费的时间可能不同，get操作将返回先前的频道映射，直到新的频道映射生效。
 *
 * @note 设置频道映射后，根据规范，在经过至少1秒后才能再次设置。参见蓝牙规范4.1版第2卷E部分第7.3.46节。
 *
 * @retval ：：NRF_SUCCESS获取或设置成功。
 * @retval ：：NRF_ERROR_INVALID_PARAM以下一项或多项为真：
 *                                   -在@ref ch_map中设置少于两位。
 *                                   -设置用于主要广告频道（37-39）的位。
 * @retval ：：在足够的时间过去之前，再次设置了NRF_ERROR_BUSY频道映射。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE为获取提供的连接句柄无效。
 *
 */
typedef struct
{
  uint16_t conn_handle;                   /**<连接手柄（仅适用于get）*/
  uint8_t ch_map[5];                      /**<通道图（37位）。*/
} ble_gap_opt_ch_map_t;


/**@brief 本地连接延迟选项。
 *
 * @details 本地连接延迟是一种功能，它允许从设备通过忽略对等设备设置的从设备延迟来提高电流消耗。本地连接延迟只能设置为从属延迟的倍数，并且不能超过监管超时的一半。
 *
 * @details 与@ref sd_ble_opt_set一起使用以设置本地连接延迟。这个
 *          @ref 此选项不支持sd_ble_opt_get，但在设置该选项时，将实际本地连接延迟（除非设置为NULL）设置为返回参数。
 *
 * @note 延迟集将被截断为最接近的从属延迟事件倍数，或在监控超时的一半之前的最接近倍数。
 *
 * @note 默认情况下，本地连接延迟被禁用，并且需要为新连接以及每当更新连接时启用本地连接延迟。
 *
 * @retval ：：NRF_SUCCESS设置成功。
 * @retval ：：不支持NRF_ERROR_NOT_SUPPORTED Get。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄参数无效。
 */
typedef struct
{
  uint16_t   conn_handle;                       /**<连接手柄*/
  uint16_t   requested_latency;                 /**<请求的本地连接延迟。*/
  uint16_t * p_actual_latency;                  /**<指向实际本地连接延迟的存储的指针（可以设置为NULL以跳过返回值）。*/
} ble_gap_opt_local_conn_latency_t;

/**@brief 禁用从属延迟
 *
 * @details 与@ref sd_ble_opt_set一起使用，暂时禁用外围连接的从属延迟
 *          (see @ref ble_gap_conn_params_t:：slave_elatency）。并再次启用它。禁用时，外围设备将忽略中心设置的slave_elatency。
 *
 * @note  只能在外围链路上调用。
 *
 * @retval ：：NRF_SUCCESS设置成功。
 * @retval ：：不支持NRF_ERROR_NOT_SUPPORTED Get。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄参数无效。
 */
typedef struct
{
  uint16_t   conn_handle;    /**<连接手柄*/
  uint8_t    disable : 1;    /**<设置为1以禁用从属延迟。设置为0将再次启用。*/
} ble_gap_opt_slave_latency_disable_t;

/**@brief Passkey选项。
 *
 * @details 包含配对期间要使用的密钥的结构。这可以与@ref sd_ble_opt_set一起使用，以使SoftDevice使用预编程的密钥进行身份验证，而不是生成随机密钥。
 *
 * @note 使用相同的预编程密钥重复配对尝试使配对容易受到MITM攻击。
 *
 * @note @此选项不支持ref sd_ble_opt_get。
 *
 */
typedef struct
{
  uint8_t const * p_passkey;                    /**<指向配对过程中使用的6位ASCII字符串（仅限数字0..9，无NULL终止）密钥的指针。如果为NULL，SoftDevice将根据需要生成随机密钥。*/
} ble_gap_opt_passkey_t;


/**@brief 兼容性模式1选项。
 *
 * @details 这可以与@ref sd_ble_opt_set一起使用，以启用和禁用兼容模式1。默认情况下，兼容模式1被禁用。
 *
 * @note 兼容模式1启用与不支持链路层CONNECT_IND数据包中WinOffset参数值为0的设备的互操作性。这适用于来自其他供应商的一组有限的传统外围设备。只有当本地设备充当中央设备并启动与外围设备的连接时，启用此兼容性模式才会生效。在这种情况下，可能会导致所有连接的连接创建需要更长的一个连接间隔才能完成。
 *
 *  @retval ：：NRF_SUCCESS设置成功。
 *  @retval ：：NRF_ERROR_INVALID_STATE设置模式1时正在创建连接。
 */
typedef struct
{
   uint8_t enable : 1;                           /**<启用兼容模式1。*/
} ble_gap_opt_compat_mode_1_t;


/**@brief 已验证的负载超时选项。
 *
 * @details 这可以与@ref sd_ble_opt_set一起使用，将Authenticated有效负载超时更改为其他值
 *          than the default of @ref BLE_GAP_AUTH_PAYLOAD_TIMEOUT_MAX.
 *
 * @note 如果AUTH_payload_timeout时间已过，而未在加密链路上接收到具有有效MIC的数据包，则将生成经过身份验证的有效负载超时事件：：BLE_GAP_timeout_SRC_AUTH_payload。
 *
 * @note LE ping程序将在计时器到期之前启动，以使对等方有机会重置计时器。此外，堆栈将尝试将LE ping的运行优先于其他活动，以增加在计时器到期之前完成LE ping的机会。为了避免对其他活动产生副作用，建议使用高超时值。建议超时>2（connInterval（6+connSlaveLatency））。
 *
 * @retval ：：NRF_SUCCESS设置成功。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。auth_payload_timeout超出允许的范围。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄参数无效。
 */
typedef struct
{
  uint16_t   conn_handle;                       /**<连接手柄*/
  uint16_t   auth_payload_timeout;              /**<以10ms为单位的请求超时，请参阅@ref BLE_GAP_AUTH_PAYLOAD_timeout。*/
} ble_gap_opt_auth_payload_timeout_t;

/**@brief GAP选项的选项结构。*/
typedef union
{
  ble_gap_opt_ch_map_t                  ch_map;                    /**<通道贴图选项的参数。*/
  ble_gap_opt_local_conn_latency_t      local_conn_latency;        /**<本地连接延迟选项的参数*/
  ble_gap_opt_passkey_t                 passkey;                   /**<Passkey选项的参数。*/
  ble_gap_opt_compat_mode_1_t           compat_mode_1;             /**<兼容模式1选项的参数。*/
  ble_gap_opt_auth_payload_timeout_t    auth_payload_timeout;      /**<已验证有效负载超时选项的参数。*/
  ble_gap_opt_slave_latency_disable_t   slave_latency_disable;     /**<禁用从属延迟选项的参数*/
} ble_gap_opt_t;
/**@} */


/**@addtogroup BLE_GAP_FUNCTIONS函数
 * @{ */

/**@brief 设置本地蓝牙标识地址。
 *
 *        本地蓝牙标识地址是向其他对等方标识此设备的地址。
 *        The address type must be either @ref BLE_GAP_ADDR_TYPE_PUBLIC或@ref BLE_GAP_ADDR_TYPE-RANDOM_STATIC。
 *
 * @note  在广告、扫描或创建连接时无法更改标识地址。
 *
 * @note  此地址将在绑定期间分发给对等方。如果地址更改，存储在对等设备中的地址将无效，并且将失去使用旧地址重新连接的能力。
 *
 * @note  默认情况下，SoftDevice将在启用时设置@ref BLE_GAP_ADDR_type_RANDOM_STATIC类型的地址。地址是在IC制造过程中填充的随机数，并且在每个IC的寿命期间保持不变。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_ADV_MSC}
 * @endmscs
 *
 * @param[in] p_addr 指向地址结构的指针。
 *
 * @retval ：：成功设置NRF_SUCCESS地址。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_GAP_INVALID_BLE_ADDR地址无效。
 * @retval ：：NRF_ERROR_BUSY堆栈正忙，请处理挂起的事件并重试。
 * @retval ：：NRF_ERROR_INVALID_STATE播发、扫描或创建连接时无法更改标识地址。
 */
SVCALL(SD_BLE_GAP_ADDR_SET, uint32_t, sd_ble_gap_addr_set(ble_gap_addr_t const *p_addr));


/**@brief 获取本地蓝牙标识地址。
 *
 * @note  这将始终返回身份地址，而与隐私设置无关，
 *        i.e. the address type will always be either @ref BLE_GAP_ADDR_TYPE_PUBLIC或@ref BLE_GAP_ADDR_TYPE-RANDOM_STATIC。
 *
 * @param[out] p_addr 指向要填充的地址结构的指针。
 *
 * @retval ：：成功检索到NRF_SUCCESS地址。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效或为NULL。
 */
SVCALL(SD_BLE_GAP_ADDR_GET, uint32_t, sd_ble_gap_addr_get(ble_gap_addr_t *p_addr));


/**@brief 获取广告商使用的蓝牙设备地址。
 *
 * @note  此函数将返回广告PDU中使用的本地蓝牙地址。使用隐私时，SoftDevice将每隔
 *        @ref ble_gap_privacy_params_t:：private_addr_cycle_s使用配置
 *        @ref sd_ble_gap_privacy_set。因此，根据应用程序何时调用此API，返回的地址可能不是广告PDU中使用的最新地址。
 *
 * @param[in]  adv_handle 从中获取地址的广告句柄。
 * @param[out] p_addr     指向要填充的地址结构的指针。
 *
 * @retval ：：成功检索到NRF_SUCCESS地址。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效或为NULL。
 * @retval ：：BLE_ERROR_INVALID_ADV_HANDLE未找到提供的广告句柄。
 * @retval ：：NRF_ERROR_INVALID_STATE广告集当前未进行广告。
 */
SVCALL(SD_BLE_GAP_ADV_ADDR_GET, uint32_t, sd_ble_gap_adv_addr_get(uint8_t adv_handle, ble_gap_addr_t *p_addr));


/**@brief 在SoftDevice中设置活动白名单。
 *
 * @note  一次只能使用一个白名单，并且白名单在BLE角色之间共享。如果BLE角色正在使用白名单，则无法设置白名单。
 *
 * @note  如果使用设备标识列表中的信息解析地址，则白名单过滤策略适用于对等方标识地址，而不是通过空中发送的可解析地址。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_WL_SHARE_MSC}
 * @mmsc{@ref BLE_GAP_PRIVACY_SCAN_PRIVATE_SCAN_MSC}
 * @endmscs
 *
 * @param[in] pp_wl_addrs 指向对等地址白名单的指针，如果为NULL，则白名单将被清除。
 * @param[in] len         白名单的长度，最大@ref BLE_GAP_whitelist_ADDR_MAX_COUNT。
 *
 * @retval ：：NRF_SUCCESS白名单已成功设置/清除。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的白名单（或其中一个条目）无效。
 * @retval ：：BLE_ERROR_GAP_WHITELIST_IN_USE白名单正由BLE角色使用，无法设置或清除。
 * @retval ：：BLE_ERROR_GAP_INVALID_BLE_ADDR提供的地址类型无效。
 * @retval ：：NRF_ERROR_DATA_SIZE给定的白名单大小无效（零或太大）；只有当pp_wl_addrs不为NULL时才能返回。
 */
SVCALL(SD_BLE_GAP_WHITELIST_SET, uint32_t, sd_ble_gap_whitelist_set(ble_gap_addr_t const * const * pp_wl_addrs, uint8_t len));


/**@brief 设置设备标识列表。
 *
 * @note  一次只能使用一个设备标识列表，该列表在BLE角色之间共享。如果BLE角色正在使用设备标识列表，则无法设置该列表。
 *
 * @param[in] pp_id_keys     指向对等标识地址和对等IRK数组的指针，如果为NULL，则将清除设备标识列表。
 * @param[in] pp_local_irks  指向本地IRK数组的指针。数组中的每个条目都映射到同一索引的pp_id_keys中的条目。要使用当前设置的所有对等设备的设备IRK填充列表，请设置为NULL。
 * @param[in] len            设备标识列表的长度，最大@ref BLE_GAP_device_IDENTIES_MAX_COUNT。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PRIVACY_ADV_MSC}
 * @mmsc{@ref BLE_GAP_PRIVACY_SCAN_MSC}
 * @mmsc{@ref BLE_GAP_PRIVACY_SCAN_PRIVATE_SCAN_MSC}
 * @mmsc{@ref BLE_GAP_PRIVACY_ADV_DIR_PRIV_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_CONN_PRIV_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_CONN_PRIV_MSC}
 * @endmscs
 *
 * @retval ：：NRF_SUCCESS设备标识列表已成功设置/清除。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的设备标识列表（或其中一个条目）无效。如果本地IRK列表也包含无效条目，则可能返回此代码。
 * @retval ：：BLE_ERROR_GAP_DEVICE_IDENTITIES_IN_USE设备标识列表正在使用，无法设置或清除。
 * @retval ：：BLE_ERROR_GAP_DEVICE_IDENTITIES_DUPLICATE设备标识列表包含具有相同标识地址的多个条目。
 * @retval ：：BLE_ERROR_GAP_INVALID_BLE_ADDR提供的地址类型无效。
 * @retval ：：NRF_ERROR_DATA_SIZE给定的设备标识列表大小无效（零或太大）；这只能在pp_id_keys不为NULL时返回。
 */
SVCALL(SD_BLE_GAP_DEVICE_IDENTITIES_SET, uint32_t, sd_ble_gap_device_identities_set(ble_gap_id_key_t const * const * pp_id_keys, ble_gap_irk_t const * const * pp_local_irks, uint8_t len));


/**@brief 设置隐私设置。
 *
 * @note  在广告、扫描或创建连接时，不能更改隐私设置。
 *
 * @param[in] p_privacy_params 隐私设置。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PRIVACY_ADV_MSC}
 * @mmsc{@ref BLE_GAP_PRIVACY_SCAN_MSC}
 * @mmsc{@ref BLE_GAP_PRIVACY_ADV_DIR_PRIV_MSC}
 * @endmscs
 *
 * @retval ：：NRF_SUCCESS设置成功。
 * @retval ：：NRF_ERROR_BUSY堆栈正忙，请处理挂起的事件并重试。
 * @retval ：：BLE_ERROR_GAP_INVALID_BLE_ADDR提供的地址类型无效。
 * @retval ：：NRF_ERROR_INVALID_ADDR指向隐私设置的指针为NULL或无效。否则，privacy参数中的p_device_irk指针是无效指针。
 * @retval ：：提供了NRF_ERROR_INVALID_PARAM超出范围的参数。
 * @retval ：：NRF_ERROR_INVALID_STATE播发、扫描或创建连接时，无法更改隐私设置。
 */
SVCALL(SD_BLE_GAP_PRIVACY_SET, uint32_t, sd_ble_gap_privacy_set(ble_gap_privacy_params_t const *p_privacy_params));


/**@brief 获取隐私设置。
 *
 * @note ：：ble_gap_privacy_params_t:：p_device_irk必须初始化为NULL或有效地址，然后才能调用此函数。如果它被初始化为有效地址，则返回时指向的地址将包含当前设备IRK。
 *
 * @param[in,out] p_privacy_params 隐私设置。
 *
 * @retval ：：NRF_SUCCESS读取隐私设置。
 * @retval ：：NRF_ERROR_INVALID_ADDR返回隐私设置的指针可能为NULL或无效。否则，privacy参数中的p_device_irk指针是无效指针。
 */
SVCALL(SD_BLE_GAP_PRIVACY_GET, uint32_t, sd_ble_gap_privacy_get(ble_gap_privacy_params_t *p_privacy_params));


/**@brief 配置广告集。设置、清除或更新广告和扫描响应数据。
 *
 * @note  此调用将检查广告数据的格式，以确保互操作性。此API调用对所提供数据的限制包括在扫描响应数据中具有标志数据类型，并在广告数据和扫描响应数据上复制本地名称。
 *
 * @note 为了在广告时更新广告数据，必须提供新的广告缓冲区。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_ADV_MSC}
 * @mmsc{@ref BLE_GAP_WL_SHARE_MSC}
 * @endmscs
 *
 * @param[in,out] p_adv_handle                         提供指向包含@ref BLE_GAP_ADV_SET_handle_NOT_SET的句柄的指针，以配置新的广告集。成功后，将通过指针返回一个新句柄。提供指向现有广告句柄的指针以配置现有广告集。
 * @param[in]     p_adv_data                           广告数据。如果设置为NULL，则不会使用广告数据。请参见@ref ble_gap_adv_data_t。
 * @param[in]     p_adv_params                         广告参数。当此函数用于在广告时更新广告数据时，此参数必须为NULL。请参见@ref ble_gap_adv_params_t。
 *
 * @retval ：：NRF_SUCCESS广告集已成功配置。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效：
 *                                                      -指定的广告数据配置无效。请参见@ref ble_gap_adv_data_t。
 *                                                      -p_adv_param的配置无效。请参见@ref ble_gap_adv_params_t。
 *                                                      -请求使用白名单，但尚未设置白名单，请参阅@ref sd_ble_gap_whitelist_set。
 * @retval ：：BLE_ERROR_GAP_INVALID_BLE_ADDR BLE_GAP_adv_params_t:：p_peer_ADDR无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效。以下任一项：
 *                                                     -在广告时提供非NULL广告集参数是无效的。
 *                                                     -在广告时提供相同的数据缓冲区是无效的。要更新广告数据，请提供新的广告缓冲区。
 * @retval ：：BLE_ERROR_GAP_DISCOVERABLE_WITH_WHITELIST可发现模式和白名单不兼容。
 * @retval ：：BLE_ERROR_INVALID_ADV_HANDLE未找到提供的广告句柄。使用@ref BLE_GAP_ADV_SET_HANDLE_NOT_SET配置新的广告句柄。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_FLAGS提供的广告标志组合无效。
 * @retval ：：NRF_ERROR_INVALID_DATA提供的数据类型无效。检查蓝牙规范5.0版第3卷C部分第11章中给出的广告数据格式规范。
 * @retval ：：NRF_ERROR_INVALID_LENGTH提供的数据长度无效。
 * @retval ：：NRF_ERROR_NOT_SUPPORTED不支持的数据长度或播发参数配置。
 * @retval ：：NRF_ERROR_NO_MEM内存不足，无法配置新的播发句柄。改为更新现有的广告句柄。
 * @retval ：：BLE_ERROR_GAP_UUID_LIST_MISMATCH提供的UUID列表无效。
 */
SVCALL(SD_BLE_GAP_ADV_SET_CONFIGURE, uint32_t, sd_ble_gap_adv_set_configure(uint8_t *p_adv_handle, ble_gap_adv_data_t const *p_adv_data, ble_gap_adv_params_t const *p_adv_params));


/**@brief 开始广告（GAP可发现、可连接模式、广播程序）。
 *
 * @note 任何时候只能有一个广告客户处于活动状态。
 *
 * @events
 * @event{@ref BLE_GAP_EVT_CONNECTED，通过可连接广告建立连接后生成。}
 * @event{@ref BLE_GAP_EVT_ADV_SET_TERMINATED，广告集已终止。}
 * @event{@ref BLE_GAP_EVT_SCAN_REQ_REPORT，收到扫描请求。｝
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_ADV_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_CONN_PRIV_MSC}
 * @mmsc{@ref BLE_GAP_PRIVACY_ADV_DIR_PRIV_MSC}
 * @mmsc{@ref BLE_GAP_WL_SHARE_MSC}
 * @endmscs
 *
 * @param[in] adv_handle   从@ref sd_ble_gap_adv_set_figure接收的要在其上进行广告的广告句柄。
 * @param[in] conn_cfg_tag 标识由@ref sd_ble_cfg_set或
 *                         @ref BLE_CONN_CFG_TAG_DEFAULT使用默认连接配置。对于不可连接的广告，此项被忽略。
 *
 * @retval ：：NRF_SUCCESS BLE堆栈已开始播发。
 * @retval ：：NRF_ERROR_INVALID_STATE adv_handle未配置或已发布。
 * @retval ：：NRF_ERROR_CONN_COUNT已达到可用连接的限制；无法启动可连接的广告客户。
 * @retval ：：未找到BLE_ERROR_INVALID_ADV_HANDLE广告句柄。使用@ref sd_ble_gap_adv_set_config配置新的adveriting句柄。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND conn_cfg_tag。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效：
 *                                        -p_adv_param的配置无效。请参见@ref ble_gap_adv_params_t。
 *                                        -请求使用白名单，但尚未设置白名单，请参阅@ref sd_ble_gap_whitelist_set。
 * @retval ：：NRF_ERROR_RESOURCES：
 *                                        -advhandle配置了可连接的广告，但与conncfg_tag关联的eventlength参数太小，无法在所选广告物理上建立连接。使用@ref sd_ble_cfg_set增加事件长度。
 *                                        -没有足够的BLE角色槽可用。停止一个或多个当前活动的角色（中央、外围、广播或观察员），然后重试。
 *                                        -p_adv_param配置有可连接的广告，但与conncfg_tag相关联的event_length参数太小，无法在所选广告物理上建立连接。使用@ref sd_ble_cfg_set增加事件长度。
 */
SVCALL(SD_BLE_GAP_ADV_START, uint32_t, sd_ble_gap_adv_start(uint8_t adv_handle, uint8_t conn_cfg_tag));


/**@brief 停止广告（GAP可发现、可连接模式、广播程序）。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_ADV_MSC}
 * @mmsc{@ref BLE_GAP_WL_SHARE_MSC}
 * @endmscs
 *
 * @param[in] adv_handle 应该停止广告的广告手柄。
 *
 * @retval ：：NRF_SUCCESS BLE堆栈已停止播发。
 * @retval ：：BLE_ERROR_INVALID_ADV_HANDLE无效的广告句柄。
 * @retval ：：NRF_ERROR_INVALID_STATE播发句柄未播发。
 */
SVCALL(SD_BLE_GAP_ADV_STOP, uint32_t, sd_ble_gap_adv_stop(uint8_t adv_handle));



/**@brief 更新连接参数。
 *
 * @details 在中心角色中，这将启动链路层连接参数更新过程，否则在外围角色中，将发送相应的L2CAP请求并等待中心执行该过程。在这两种情况下，无论成功与否，应用程序都将通过@ref BLE_GAP_EVT_CONN_PARAM_UPDATE事件通知结果。
 *
 * @details 此函数既可以用作回复@ref BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST的中心，也可以作为未请求的过程的中心。
 *
 * @events
 * @event{@ref BLE_GAP_EVT_CONN_PARAM_UPDATE，连接参数更新过程的结果。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_CPU_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_ENC_AUTH_MUTEX_MSC}
 * @mmsc{@ref BLE_GAP_MULTILINK_CPU_MSC}
 * @mmsc{@ref BLE_GAP_MULTILINK_CTRL_PROC_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_CPU_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] p_conn_params  指向所需连接参数的指针。如果在外围角色上提供NULL，则将使用GAP服务的PPCP特性中的参数。如果在中心角色上提供NULL并响应@ref BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST，则将拒绝外围请求
 *
 * @retval ：：NRF_SUCCESS连接更新过程已成功启动。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效，请检查参数限制和约束。
 * @retval ：：NRF_ERROR_INVALID_STATE正在断开连接或尚未建立链接。
 * @retval ：：NRF_ERROR_BUSY过程已在进行中，请等待挂起的过程完成，然后重试。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 * @retval ：：NRF_ERROR_NO_MEM内存不足，无法完成操作。
 */
SVCALL(SD_BLE_GAP_CONN_PARAM_UPDATE, uint32_t, sd_ble_gap_conn_param_update(uint16_t conn_handle, ble_gap_conn_params_t const *p_conn_params));


/**@brief 断开（GAP链路终端）。
 *
 * @details 此调用启动断开过程，其完成情况将通知应用程序
 *          with a @ref BLE_GAP_EVT_DISCONNECTED事件。
 *
 * @events
 * @event{@ref BLE_GAP_EVT_DISCONNECTED，断开过程完成时生成。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_CONN_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] hci_status_code HCI状态代码，请参见@ref BLE_HCI_status_CODES（接受的值为@ref BLE_CCI_REMOTE_USER_TERMINATED_CONNECTION和@ref BLE_LCI_CONN_INTERVAL_UNACCEPTABLE）。
 *
 * @retval ：：NRF_SUCCESS已成功启动断开过程。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE正在断开连接或尚未建立链接。
 */
SVCALL(SD_BLE_GAP_DISCONNECT, uint32_t, sd_ble_gap_disconnect(uint16_t conn_handle, uint8_t hci_status_code));


/**@brief 设置收音机的发射功率。
 *
 * @param[in] role 要为其设置发射功率的角色，请参阅@ref BLE_GAP_TX_power_ROLES了解可能的角色。
 * @param[in] handle   句柄参数根据角色进行解释：
 *                     - If role is @ref BLE_GAP_TX_POWER_ROLE_CONN，此值是特定的连接句柄。
 *                     - If role is @ref BLE_GAP_TX_POWER_ROLE_ADV（用广告句柄标识的广告集）将使用指定的发射功率，并在以下情况下将其包含在广告包报头中
 *                       @ref ble_gap_adv_properties_t：：include_tx_power set。
 *                     -对于所有其他角色，句柄将被忽略。
 * @param[in] tx_power 无线电发射功率，单位为dBm（可接受值见注释）。
 *
  * @note 支持的tx_power值：-40dBm、-20dBm、-16dBm、-12dBm、-8dBm、-4dBm、0dBm、+2dBm、+3dBm、+4dBm、+5dBm、+6dBm、+7dBm和+8dBm。
  * @note 启动器将具有与扫描仪相同的发射功率。
 * @note 当创建连接时，它将从连接的发起方或广告客户继承传输功率。
 *
 * @retval ：：NRF_SUCCESS成功更改发射功率。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：未找到BLE_ERROR_INVALID_ADV_HANDLE广告句柄。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 */
SVCALL(SD_BLE_GAP_TX_POWER_SET, uint32_t, sd_ble_gap_tx_power_set(uint8_t role, uint16_t handle, int8_t tx_power));


/**@brief 设置GAP Appearance值。
 *
 * @param[in] appearance 外观（16位），请参见@ref BLE_APPERANCES。
 *
 * @retval ：：NRF_SUCCESS外观值设置成功。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 */
SVCALL(SD_BLE_GAP_APPEARANCE_SET, uint32_t, sd_ble_gap_appearance_set(uint16_t appearance));


/**@brief 获取GAP外观值。
 *
 * @param[out] p_appearance 指向要填充的外观（16位）的指针，请参见@ref BLE_APPERANCES。
 *
 * @retval ：：成功检索到NRF_SUCCESS外观值。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 */
SVCALL(SD_BLE_GAP_APPEARANCE_GET, uint32_t, sd_ble_gap_appearance_get(uint16_t *p_appearance));


/**@brief 设置GAP外围设备首选连接参数。
 *
 * @param[in] p_conn_params 指向带有所需参数的@ref ble_gap_conn_params_t结构的指针。
 *
 * @retval ：：NRF_SUCCESS外围首选连接参数设置成功。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 */
SVCALL(SD_BLE_GAP_PPCP_SET, uint32_t, sd_ble_gap_ppcp_set(ble_gap_conn_params_t const *p_conn_params));


/**@brief 获取GAP外围设备首选连接参数。
 *
 * @param[out] p_conn_params 指向将存储参数的@ref ble_gap_conn_params_t结构的指针。
 *
 * @retval ：：成功检索到NRF_SUCCESS外围首选连接参数。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 */
SVCALL(SD_BLE_GAP_PPCP_GET, uint32_t, sd_ble_gap_ppcp_get(ble_gap_conn_params_t *p_conn_params));


/**@brief 设置GAP设备名称。
 *
 * @note  如果设备名称位于应用程序闪存中（请参见@ref ble_gap_cfg_device_name_t），
 *        it cannot be changed. Then @ref 将返回NRF_ERROR_FORBIDDEN。
 *
 * @param[in] p_write_perm 设备名称特性的写入权限，请参见@ref ble_gap_conn_sec_mode_t。
 * @param[in] p_dev_name 指向UTF-8编码的<b>非NULL终止的</b>字符串的指针。
 * @param[in] len p_dev_name指向的UTF-8、<b>非NULL终止的</b>字符串的长度（以八位字节为单位）（必须小于或等于@ref BLE_GAP_DEVNAME_MAX_LEN）。
 *
 * @retval ：：NRF_SUCCESS GAP设备名称和权限设置成功。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_DATA_SIZE提供的数据大小无效。
 * @retval ：：NRF_ERROR_FORBIDDEN设备名称不可写。
 */
SVCALL(SD_BLE_GAP_DEVICE_NAME_SET, uint32_t, sd_ble_gap_device_name_set(ble_gap_conn_sec_mode_t const *p_write_perm, uint8_t const *p_dev_name, uint16_t len));


/**@brief 获取GAP设备名称。
 *
 * @note  如果设备名大于提供的缓冲区的大小，p_len将返回完整的设备名长度，而不是p_dev_name中实际返回的字节数。应用程序可以使用该信息来分配合适的缓冲区大小。
 *
 * @param[out]    p_dev_name 指向将放置UTF-8<b>非NULL终止的</b>字符串的空缓冲区的指针。设置为NULL以获取完整的设备名称长度。
 * @param[in,out] p_len      p_dev_name指向的缓冲区长度，输出时的完整设备名称长度。
 *
 * @retval ：：成功检索到NRF_SUCCESS GAP设备名称。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_DATA_SIZE提供的数据大小无效。
 */
SVCALL(SD_BLE_GAP_DEVICE_NAME_GET, uint32_t, sd_ble_gap_device_name_get(uint8_t *p_dev_name, uint16_t *p_len));


/**@brief 启动GAP认证程序。
 *
 * @details 在中心角色中，此功能将发送SMP配对请求（如果被拒绝，则发送SMP配对失败），否则在外围角色中，将发送SMP安全请求。
 *
 * @events
 * @event{Depending 在设置的安全参数和与对等方交换的数据包上，可能会生成以下事件：｝
 * @event{@ref BLE_GAP_EVT_SEC_PARAMS_REQUEST}
 * @event{@ref BLE_GAP_EVT_SEC_INFO_REQUEST}
 * @event{@ref BLE_GAP_EVT_PASSKEY_DISPLAY}
 * @event{@ref BLE_GAP_EVT_KEY_PRESSED}
 * @event{@ref BLE_GAP_EVT_AUTH_KEY_REQUEST}
 * @event{@ref BLE_GAP_EVT_LESC_DHKEY_REQUEST}
 * @event{@ref BLE_GAP_EVT_CONN_SEC_UPDATE}
 * @event{@ref BLE_GAP_EVT_AUTH_STATUS}
 * @event{@ref BLE_GAP_EVT_TIMEOUT}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PERIPH_SEC_REQ_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_SEC_REQ_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_ENC_AUTH_MUTEX_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_PAIRING_JW_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_BONDING_JW_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_BONDING_PK_PERIPH_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_BONDING_PK_PERIPH_OOB_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_PAIRING_JW_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_NC_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_PKE_PD_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_PKE_CD_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_OOB_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] p_sec_params 指向@ref ble_gap_sec_params_t结构的指针，其中包含在配对或绑定过程中使用的安全参数。在外围角色中，仅使用这种结构的键、mitm、lesc和按键场。在中心角色中，此指针可能为NULL以拒绝安全请求。
 *
 * @retval ：：NRF_SUCCESS成功启动身份验证过程。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效。以下任一项：
 *                                   -尚未建立链接。
 *                                   -加密已在执行或排队。
 * @retval ：：NRF_ERROR_NO_MEM已达到给定角色可并行运行的身份验证过程的最大数量。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 * @retval ：：NRF_ERROR_NOT_SUPPORTED不支持在@ref ble_gap_sec_kdist_t中设置符号或链接字段。
 * @retval ：：NRF_ERROR_TIMEOUT发生SMP超时，禁止在此链路上执行进一步的SMP操作。
 */
SVCALL(SD_BLE_GAP_AUTHENTICATE, uint32_t, sd_ble_gap_authenticate(uint16_t conn_handle, ble_gap_sec_params_t const *p_sec_params));


/**@brief 回复GAP安全参数。
 *
 * @details 此函数仅用于回复@ref BLE_GAP_EVT_SEC_PARAMS_REQUEST，在其他时间调用它将导致@ref NRF_ERROR_INVALID_STATE。
 * @note    如果调用返回错误代码，则请求仍处于挂起状态，可以使用更正的参数重复应答调用。
 *
 * @events
 * @event{This 函数在身份验证过程中使用，请参阅@ref sd_ble_gap_authenticate文档中的事件列表
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PERIPH_PAIRING_JW_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_BONDING_JW_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_BONDING_PK_PERIPH_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_BONDING_PK_CENTRAL_OOB_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_BONDING_STATIC_PK_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_PAIRING_CONFIRM_FAIL_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_PAIRING_JW_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_NC_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_PKE_PD_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_PKE_CD_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_OOB_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_PAIRING_KS_TOO_SMALL_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_PAIRING_APP_ERROR_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_PAIRING_REMOTE_PAIRING_FAIL_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_PAIRING_TIMEOUT_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_PAIRING_JW_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_BONDING_JW_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_BONDING_PK_PERIPH_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_BONDING_PK_PERIPH_OOB_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_PAIRING_JW_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_NC_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_PKE_PD_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_PKE_CD_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_OOB_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] sec_status 安全状态，请参阅@ref BLE_GAP_SEC_status。
 * @param[in] p_sec_params 指向@ref ble_gap_sec_params_t安全参数结构的指针。在中心角色中，必须将其设置为NULL，因为在上次调用@ref sd_ble_gap_authenticate时已经提供了参数。
 * @param[in,out] p_sec_keyset 指向@ref ble_gap_sec_keyset_t安全密钥集结构的指针。由于正在进行的安全过程而生成和/或分发的任何密钥都将存储在该结构内的指针所引用的存储器中。收到@ref BLE_GAP_EVT_AUTH_STATUS事件后，密钥将被存储并可用于应用程序。请注意，SoftDevice希望应用程序提供存储对等方密钥的内存。因此，必须确保此结构中的相关指针不为NULL。但是，指向本地密钥的指针可以为NULL，在这种情况下，应用程序在收到
 *                         @ref BLE_GAP_EVT_AUTH_STATUS事件。
 *
 * @retval ：：NRF_SUCCESS成功接受应用程序的安全参数。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_BUSY堆栈正忙，请处理挂起的事件并重试。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：尚未请求NRF_ERROR_INVALID_STATE安全参数。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 * @retval ：：NRF_ERROR_NOT_SUPPORTED不支持在@ref ble_gap_sec_kdist_t中设置符号或链接字段。
 */
SVCALL(SD_BLE_GAP_SEC_PARAMS_REPLY, uint32_t, sd_ble_gap_sec_params_reply(uint16_t conn_handle, uint8_t sec_status, ble_gap_sec_params_t const *p_sec_params, ble_gap_sec_keyset_t const *p_sec_keyset));


/**@brief 使用身份验证密钥答复。
 *
 * @details 此函数仅用于回复@ref BLE_GAP_EVT_AUTH_KEY_REQUEST或@ref BLE_GAP_EVT_PASSKEY_DISPLAY，在其他时间调用它将导致@ref NRF_ERROR_INVALID_STATE。
 * @note    如果调用返回错误代码，则请求仍处于挂起状态，可以使用更正的参数重复应答调用。
 *
 * @events
 * @event{This 函数在身份验证过程中使用，请参阅@ref sd_ble_gap_authenticate文档中的事件列表
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PERIPH_BONDING_PK_CENTRAL_OOB_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_NC_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_PKE_CD_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_BONDING_PK_PERIPH_OOB_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_NC_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_PKE_CD_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] key_type 请参见@ref BLE_GAP_AUTH_KEY_TYPES。
 * @param[in] p_key 如果密钥类型为@ref BLE_GAP_AUTH_key_type_NONE，则为NULL。
 *                  If key type is @ref BLE_GAP_AUTH_KEY_TYPE_PASSKEY，然后是6字节ASCII字符串（仅限数字0..9，无NULL终止）或确认LE安全连接数值比较时为NULL。
 *                  If key type is @ref BLE_GAP_AUTH_KEY_TYPE_OOB，然后是小端格式的16字节OOB键值。
 *
 * @retval ：：NRF_SUCCESS身份验证密钥已成功设置。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：尚未请求NRF_ERROR_INVALID_STATE身份验证密钥。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 */
SVCALL(SD_BLE_GAP_AUTH_KEY_REPLY, uint32_t, sd_ble_gap_auth_key_reply(uint16_t conn_handle, uint8_t key_type, uint8_t const *p_key));


/**@brief 回复LE安全连接DHKey。
 *
 * @details 此函数仅用于回复@ref BLE_GAP_EVT_LESC_DHKEY_REQUEST，在其他时间调用它将导致@ref NRF_ERROR_INVALID_STATE。
 * @note    如果调用返回错误代码，则请求仍处于挂起状态，可以使用更正的参数重复应答调用。
 *
 * @events
 * @event{This 函数在身份验证过程中使用，请参阅@ref sd_ble_gap_authenticate文档中的事件列表
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_PAIRING_JW_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_NC_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_PKE_PD_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_PKE_CD_MSC}
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_OOB_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_PAIRING_JW_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_NC_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_PKE_PD_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_PKE_CD_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_OOB_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] p_dhkey LE安全连接DHKey。
 *
 * @retval ：：NRF_SUCCESS DHKey已成功设置。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效。以下任一项：
 *                                   -对等方未通过身份验证。
 *                                   -应用程序未提取@ref BLE_GAP_EVT_LESC_DHKEY_REQUEST事件。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 */
SVCALL(SD_BLE_GAP_LESC_DHKEY_REPLY, uint32_t, sd_ble_gap_lesc_dhkey_reply(uint16_t conn_handle, ble_gap_lesc_dhkey_t const *p_dhkey));


/**@brief 通知对等方本地按键。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_PKE_CD_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_PKE_CD_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] kp_not 参见@ref BLE_GAP_KP_NOT_TYPES。
 *
 * @retval ：：NRF_SUCCESS按键通知已成功排队等待传输。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效。以下任一项：
 *                                   -未请求身份验证密钥。
 *                                   -尚未输入密钥。
 *                                   -两个对等方均未启用按键。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 * @retval ：：NRF_ERROR_BUSY BLE堆栈正忙。稍后重试。
 */
SVCALL(SD_BLE_GAP_KEYPRESS_NOTIFY, uint32_t, sd_ble_gap_keypress_notify(uint16_t conn_handle, uint8_t kp_not));


/**@brief 生成一组OOB数据以发送到带外对等端。
 *
 * @note  返回的OOB数据中包含的@ref ble_gap_addr_t将是当前活动的（或者，如果已经建立了连接，则是连接设置期间使用的）。应用程序可以用更新的值手动覆盖它。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_OOB_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_OOB_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。如果尚未建立BLE连接，则可以为@ref BLE_CONN_HANDLE_INVALID。
 * @param[in] p_pk_own LE安全连接本地P-256公钥。
 * @param[out] p_oobd_own 要带外发送给对等方的OOB数据。
 *
 * @retval ：：成功生成NRF_SUCCESS OOB数据。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 */
SVCALL(SD_BLE_GAP_LESC_OOB_DATA_GET, uint32_t, sd_ble_gap_lesc_oob_data_get(uint16_t conn_handle, ble_gap_lesc_p256_pk_t const *p_pk_own, ble_gap_lesc_oob_data_t *p_oobd_own));

/**@brief 提供带外发送/接收的OOB数据。
 *
 * @note  当调用此函数时，必须正在进行一个选择OOB作为算法的身份验证过程。
 * @note  调用此函数之前，必须接收到oobd_req设置为1的@ref BLE_GAP_EVT_LESC_DHKEY_REQUEST事件。
 *
 * @events
 * @event{This 函数在身份验证过程中使用，请参阅@ref sd_ble_gap_authenticate文档中的事件列表
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PERIPH_LESC_BONDING_OOB_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_LESC_BONDING_OOB_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] p_oobd_own 带外发送给对等方的OOB数据，如果对等方未收到OOB数据则为NULL。
 *                       Must correspond to @ref @ref ble_gap_EVT_sec_params_REQUEST中的ble_gap_sec_params_t:：oob标志。
 * @param[in] p_oobd_peer 从对等端带外接收的OOB数据，如果没有接收到，则为NULL。必须对应于@ref ble_gap_sec_params_t:：oob标志
 *                        in @ref sd_ble_gap_authenticate处于中心角色或
 *                        in @ref sd_ble_gap_sec_params_reply作为外设角色。
 *
 * @retval ：：接受NRF_SUCCESS OOB数据。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效。以下任一项：
 *                                   -未请求身份验证密钥
 *                                   -不需要LESC OOB数据
 *                                   -实际上没有交换密钥。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 */
SVCALL(SD_BLE_GAP_LESC_OOB_DATA_SET, uint32_t, sd_ble_gap_lesc_oob_data_set(uint16_t conn_handle, ble_gap_lesc_oob_data_t const *p_oobd_own, ble_gap_lesc_oob_data_t const *p_oobd_peer));


/**@brief 启动GAP加密程序。
 *
 * @details 作为中心角色，该功能将使用提供的加密信息启动加密过程。
 *
 * @events
 * @event{@ref BLE_GAP_EVT_CONN_SEC_UPDATE，连接安全性已更新。｝
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_CENTRAL_ENC_AUTH_MUTEX_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_ENC_MSC}
 * @mmsc{@ref BLE_GAP_MULTILINK_CTRL_PROC_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_SEC_REQ_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] p_master_id 指向@ref ble_gap_master_id_t主标识结构的指针。
 * @param[in] p_enc_info  指向@ref ble_gap_enc_info_t加密信息结构的指针。
 *
 * @retval ：：NRF_SUCCESS成功启动身份验证过程。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_STATE尚未建立链接。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 * @retval ：：外设角色不支持BLE_ERROR_INVALID_ROLE操作。
 * @retval ：：NRF_ERROR_BUSY过程已在进行中或此时不允许，请等待挂起的过程完成，然后重试。
 */
SVCALL(SD_BLE_GAP_ENCRYPT, uint32_t, sd_ble_gap_encrypt(uint16_t conn_handle, ble_gap_master_id_t const *p_master_id, ble_gap_enc_info_t const *p_enc_info));


/**@brief 回复GAP安全信息。
 *
 * @details 此函数仅用于回复@ref BLE_GAP_EVT_SEC_INFO_REQUEST，在其他时间调用它将导致@ref NRF_ERROR_INVALID_STATE。
 * @note    如果调用返回错误代码，则请求仍处于挂起状态，可以使用更正的参数重复应答调用。
 * @note    尚不支持数据签名，因此p_sign_info必须为NULL。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_PERIPH_ENC_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] p_enc_info 指向@ref ble_gap_enc_info_t加密信息结构的指针。可能为NULL，表示无可用。
 * @param[in] p_id_info 指向@ref ble_gap_irk_t标识信息结构的指针。可能为NULL，表示无可用。
 * @param[in] p_sign_info 指向@ref ble_gap_sign_info_t签名信息结构的指针。可能为NULL，表示无可用。
 *
 * @retval ：：NRF_SUCCESS成功接受安全信息。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效。以下任一项：
 *                                   -尚未建立链接。
 *                                   -没有@ref BLE_GAP_EVT_SEC_REQUEST挂起。
 *                                   -不允许LE长期密钥请求命令。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 */
SVCALL(SD_BLE_GAP_SEC_INFO_REPLY, uint32_t, sd_ble_gap_sec_info_reply(uint16_t conn_handle, ble_gap_enc_info_t const *p_enc_info, ble_gap_irk_t const *p_id_info, ble_gap_sign_info_t const *p_sign_info));


/**@brief 获取当前连接安全性。
 *
 * @param[in]  conn_handle 连接手柄。
 * @param[out] p_conn_sec  指向要填充的@ref ble_gap_conn_sec_t结构的指针。
 *
 * @retval ：：NRF_SUCCESS成功检索到当前连接安全性。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 */
SVCALL(SD_BLE_GAP_CONN_SEC_GET, uint32_t, sd_ble_gap_conn_sec_get(uint16_t conn_handle, ble_gap_conn_sec_t *p_conn_sec));


/**@brief 开始向应用程序报告接收到的信号强度。
 *
 *        每当RSSI值更改时，都会报告一个新事件，直到调用@ref sd_ble_gap_RSSI_stop。
 *
 * @events
 * @event{@ref BLE_GAP_EVT_RSSI_CHANGED，新RSSI数据可用。事件的生成频率取决于<code>threshold_dbm</code>和<code>skip_count</code>输入参数的设置。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_CENTRAL_RSSI_READ_MSC}
 * @mmsc{@ref BLE_GAP_RSSI_FILT_MSC}
 * @endmscs
 *
 * @param[in] conn_handle        连接手柄。
 * @param[in] threshold_dbm      触发@ref BLE_GAP_EVT_RSSI_CHANGED事件之前的最小dBm变化。如果threshold_dbm等于@ref BLE_GAP_RSSI_threshold_INVALID，则禁用事件。
 * @param[in] skip_count         发送新的@ref BLE_GAP_EVT_RSSI_CHANGED事件之前，阈值变化为dbm或更大的RSSI样本数。
 *
 * @retval ：：NRF_SUCCESS成功激活RSSI报告。
 * @retval ：：NRF_ERROR_INVALID_STATE RSSI报告已在进行中。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 */
SVCALL(SD_BLE_GAP_RSSI_START, uint32_t, sd_ble_gap_rssi_start(uint16_t conn_handle, uint8_t threshold_dbm, uint8_t skip_count));


/**@brief 停止报告接收到的信号强度。
 *
 * @note  在呼叫之前检测到RSSI变化，但应用程序尚未接收到
 *        may be reported after @ref 已调用sd_ble_gap_rssi_stop。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_CENTRAL_RSSI_READ_MSC}
 * @mmsc{@ref BLE_GAP_RSSI_FILT_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 *
 * @retval ：：NRF_SUCCESS成功停用RSSI报告。
 * @retval ：：NRF_ERROR_INVALID_STATE RSSI报告未进行。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 */
SVCALL(SD_BLE_GAP_RSSI_STOP, uint32_t, sd_ble_gap_rssi_stop(uint16_t conn_handle));


/**@brief 获取上次连接事件的接收信号强度。
 *
 *        @ref 在使用此函数之前，必须调用sd_ble_gap_rssi_start以开始报告rssi@将返回ref NRF_ERROR_NOT_FOUND，直到调用@ref sd_ble_gap_RSSI_start后第一次采样RSSI。
 * @note ERRATA-153要求基于温度测量对rssi样本进行补偿。
 * @mscs
 * @mmsc{@ref BLE_GAP_CENTRAL_RSSI_READ_MSC}
 * @endmscs
 *
 * @param[in]  conn_handle 连接手柄。
 * @param[out] p_rssi      指向存储RSSI测量值的位置的指针。
 * @param[out] p_ch_index  指向存储RSSI测量信道索引的位置的指针。
 *
 * @retval ：：NRF_SUCCESS成功读取RSSI。
 * @retval ：：NRF_ERROR_NOT_FOUND没有可用的样本。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE RSSI报告未进行。
 */
SVCALL(SD_BLE_GAP_RSSI_GET, uint32_t, sd_ble_gap_rssi_get(uint16_t conn_handle, int8_t *p_rssi, uint8_t *p_ch_index));


/**@brief 开始或继续扫描（GAP发现程序、观察程序）。
 *
 * @note    调用此函数将要求应用程序保持p_adv_report_buffer指向的内存处于活动状态，直到释放缓冲区。当扫描仪停止或用另一个缓冲区调用此函数时，将释放缓冲区。
 *
 * @note    在以下情况下，扫描仪将自动停止：
 *           - @ref 调用sd_ble_gap_scan_stop。
 *           - @ref sd_ble_gap_connect被调用。
 *           - A @ref 接收到源设置为@ref的BLE_GAP_EVT_TIMEOUT BLE_GAP_TIMEOUT_SRC_SCAN。
 *           - When a @ref 收到BLE_GAP_EVT_ADV_REPORT事件，且@ref BLE_GAP_ADV_REPORT_type_t:：状态未设置为
 *             @ref BLE_GAP_ADV_DATA_STATUS_uncomplete_MORE_DATA。在这种情况下，扫描仅暂停以允许应用程序访问接收的数据。应用程序必须调用此函数以继续扫描，或调用@ref sd_ble_gap_scan_stop以停止扫描。
 *
 * @note    如果接收到@ref BLE_GAP_EVT_ADV_REPORT事件，且@ref BLE_GAP_ADV_REPORT_type_t:：状态设置为
 *          @ref BLE_GAP_ADV_DATA_STATUS_INCOMPLETE_MORE_DATA，扫描仪将继续扫描，应用程序将从此广告事件接收更多报告。以下报告将包括新旧接收数据。
 *
 * @events
 * @event{@ref BLE_GAP_EVT_ADV_REPORT，已收到广告或扫描响应包。｝
 * @event{@ref BLE_GAP_EVT_TIMEOUT，扫描仪已超时。｝
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_SCAN_MSC}
 * @mmsc{@ref BLE_GAP_WL_SHARE_MSC}
 * @endmscs
 *
 * @param[in] p_scan_params       指向扫描参数结构的指针。使用此函数继续扫描时，此参数必须为NULL。
 * @param[in] p_adv_report_buffer 指向用于存储传入广告数据的缓冲区的指针。指向的内存应保持活动状态，直到扫描停止。
 *                                See @ref BLE_GAP_SCAN_BUFFER_SIZE用于最小和最大缓冲区大小。如果扫描器接收到大于可以存储在缓冲器中的广告数据，
 *                                a @ref BLE_GAP_EVT_ADV_REPORT将引发@ref BLE_GAP_ADV_REPORT_type:：status
 *                                set to @ref BLE_GAP_ADV_DATA_STATUS_INCOMPLETE_TRUNCATED.
 *
 * @retval ：：NRF_SUCCESS成功启动扫描过程。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效。以下任一项：
 *                                   -扫描已在进行，p_scan_params不为NULL
 *                                   -扫描未运行，p_scan_param为空。
 *                                   -调用此函数继续扫描时，扫描仪已超时。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。请参见@ref ble_gap_scan_params_t。
 * @retval ：：NRF_ERROR_NOT_SUPPORTED提供了不支持的参数。请参见@ref ble_gap_scan_params_t。
 * @retval ：：NRF_ERROR_INVALID_LENGTH提供的缓冲区长度无效。请参见@ref BLE_GAP_SCAN_BUFFER_MIN。
 * @retval ：：NRF_ERROR_RESOURCES没有足够的BLE角色槽可用。停止一个或多个当前活动的角色（中央、外围或广播），然后重试
 */
SVCALL(SD_BLE_GAP_SCAN_START, uint32_t, sd_ble_gap_scan_start(ble_gap_scan_params_t const *p_scan_params, ble_data_t const * p_adv_report_buffer));


/**@brief 停止扫描（GAP发现程序、观察程序）。
 *
 * @note 释放@ref sd_ble_gap_scan_start中提供的缓冲区。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_SCAN_MSC}
 * @mmsc{@ref BLE_GAP_WL_SHARE_MSC}
 * @endmscs
 *
 * @retval ：：NRF_SUCCESS成功停止扫描过程。
 * @retval ：：NRF_ERROR_INVALID_STATE未处于扫描状态。
 */
SVCALL(SD_BLE_GAP_SCAN_STOP, uint32_t, sd_ble_gap_scan_stop(void));


/**@brief 创建连接（GAP链路建立）。
 *
 * @note 如果扫描过程当前正在进行，则在调用此函数时将自动停止。即使函数返回错误，扫描过程也将停止。
 *
 * @events
 * @event{@ref BLE_GAP_EVT_CONNECTED，已建立连接。}
 * @event{@ref BLE_GAP_EVT_TIMEOUT，无法建立连接。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_WL_SHARE_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_CONN_PRIV_MSC}
 * @mmsc{@ref BLE_GAP_CENTRAL_CONN_MSC}
 * @endmscs
 *
 * @param[in] p_peer_addr   指向对等标识地址的指针。如果@ref ble_gap_scan_params_t:：filter_policy设置为使用白名单，则p_peer_addr将被忽略。
 * @param[in] p_scan_params 指向扫描参数结构的指针。
 * @param[in] p_conn_params 指向所需连接参数的指针。
 * @param[in] conn_cfg_tag  标识由@ref sd_ble_cfg_set或
 *                          @ref BLE_CONN_CFG_TAG_DEFAULT使用默认连接配置。
 *
 * @retval ：：NRF_SUCCESS成功启动连接过程。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的参数指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 *                                   -p_scan_param或p_conn_params中的参数无效。
 *                                   -请求使用白名单，但尚未设置白名单，请参阅@ref sd_ble_gap_whitelist_set。
 *                                   -设备标识列表中不存在对等地址，请参阅@ref sd_ble_gap_device_identities_set。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND conn_cfg_tag。
 * @retval ：：NRF_ERROR_INVALID_STATE SoftDevice处于无效状态，无法执行此操作。这可能是由于现有的本地启动的连接过程，在再次启动之前必须完成该过程。
 * @retval ：：BLE_ERROR_GAP_INVALID_BLE_ADDR对等地址无效。
 * @retval ：：NRF_ERROR_CONN_COUNT已达到可用连接的限制。
 * @retval ：：NRF_ERROR_RESOURCES：
 *                                 -没有足够的BLE角色槽可用。停止一个或多个当前活动的角色（中心、外围或观察者），然后重试。
 *                                 -与conn_cfg_tag关联的event_length参数太小，无法在选定的@ref ble_gap_scan_params_t:：scan_phys上建立连接。
 *                                   Use @ref sd_ble_cfg_set以增加事件长度。
 */
SVCALL(SD_BLE_GAP_CONNECT, uint32_t, sd_ble_gap_connect(ble_gap_addr_t const *p_peer_addr, ble_gap_scan_params_t const *p_scan_params, ble_gap_conn_params_t const *p_conn_params, uint8_t conn_cfg_tag));


/**@brief 取消连接建立。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_CENTRAL_CONN_MSC}
 * @endmscs
 *
 * @retval ：：NRF_SUCCESS成功取消了正在进行的连接过程。
 * @retval ：：NRF_ERROR_INVALID_STATE未启动本地启动的连接过程或未完成连接。
 */
SVCALL(SD_BLE_GAP_CONNECT_CANCEL, uint32_t, sd_ble_gap_connect_cancel(void));


/**@brief 启动或响应PHY更新程序
 *
 * @details   此功能用于启动或响应PHY更新程序。它将永远
 *            generate a @ref 如果成功执行，则发生BLE_GAP_EVT_PHY_UPDATE事件。如果此功能用于启动PHY更新程序，并且唯一的选项
 *            provided in @ref ble_gap_phys_t:：tx_phys和@ref ble_gap_prhys_t:：rx_phys是各自方向上当前活动的PHY，SoftDevice将生成
 *            @ref BLE_GAP_EVT_PHY_UPDATE设置了当前PHY，并且不会在链路层中启动该过程。
 *
 *            If @ref ble_gap_phys_t:：tx_phys或@ref ble_gap_phys_t:：rx_phys为@ref ble_gap_PHY_AUTO，则堆栈将基于对等体的PHY首选项和本地链路配置选择PHY。在这种情况下，PHY更新过程将导致PHY组合，该组合尊重用@ref sd_ble_cfg_set配置的时间约束和当前链路层数据长度。
 *
 *            当作为中心时，SoftDevice将在每个方向上选择最快的公共PHY。
 *
 *            如果对等方不支持PHY更新过程，则生成
 *            @ref BLE_GAP_EVT_PHY_UPDATE事件的状态将设置为
 *            @ref BLE_HCI_UNSUPPORTED_REMOTE_FEATURE.
 *
 *            如果PHY过程由于过程冲突而被对等方拒绝，则状态
 *            will be @ref BLE_HCI_STATUS_CODE_LMP_ERROR_TRANSACTION_COLION或
 *            @ref BLE_HCI_difference事务冲突。如果对等端以无效参数响应PHY更新过程，则状态
 *            will be @ref BLE_HCI_STATUS_CODE_INVALID_LMP_参数。如果PHY过程因其他原因被对等方拒绝，则状态将包含对等方指定的原因。
 *
 * @events
 * @event{@ref BLE_GAP_EVT_PHY_UPDATE，PHY更新过程的结果。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_CENTRAL_PHY_UPDATE}
 * @mmsc{@ref BLE_GAP_PERIPHERAL_PHY_UPDATE}
 * @endmscs
 *
 * @param[in] conn_handle   连接句柄，用于指示请求PHY更新的连接。
 * @param[in] p_gap_phys    指向PHY结构的指针。
 *
 * @retval ：：NRF_SUCCESS成功请求PHY更新。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_INVALID_STATE尚未建立链接。
 * @retval ：：NRF_ERROR_RESOURCES为此链接配置的连接事件长度不足以
 *                               @ref ble_gap_phys_t:：tx_phys、@ref ble_gap_prhys_t:：rx_phys和@ref ble_gap_data_length_params_t。使用@ref sd_BLE_CFG_set使用@ref BLE_CONN_CFG_GAP配置连接事件长度。
 * @retval ：：NRF_ERROR_BUSY过程已在进行中或此时不允许。处理挂起事件并等待挂起过程完成，然后重试。
 *
 */
SVCALL(SD_BLE_GAP_PHY_UPDATE, uint32_t, sd_ble_gap_phy_update(uint16_t conn_handle, ble_gap_phys_t const *p_gap_phys));


/**@brief 启动或响应数据长度更新程序。
 *
 * @note 如果应用程序对p_dl_param的一个或多个成员使用@ref BLE_GAP_DATA_LENGTH_AUTO，SoftDevice将选择当前配置和连接参数中支持的最高值。
 * @note  如果链路PHY被编码，则SoftDevice将确保数据长度更新过程中使用的MaxTxTime和/或MaxRxTime至少为2704us。否则，MaxTxTime和MaxRxTime将被限制为最大2120 us。
 *
 * @param[in]   conn_handle       连接手柄。
 * @param[in]   p_dl_params       指向要在数据长度更新过程中使用的本地参数的指针。将任何成员设置为@ref BLE_GAP_DATA_LENGTH_AUTO，让SoftDevice自动决定该成员的值。设置为NULL可对所有成员使用自动值。
 * @param[out]  p_dl_limitation   指向当本地设备没有足够的资源或不支持请求的数据长度更新参数时要写入的限制的指针。如果为NULL，则忽略。
 *
 * @mscs
 * @mmsc{@ref BLE_GAP_DATA_LENGTH_UPDATE_PROCEDURE_MSC}
 * @endmscs
 *
 * @retval ：：NRF_SUCCESS成功设置数据长度扩展启动/响应参数。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE提供的连接句柄参数无效。
 * @retval ：：NRF_ERROR_INVALID_STATE尚未建立链接。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_NOT_SUPPORTED SoftDevice不支持请求的参数。检查p_dl_limition以查看不支持哪个参数。
 * @retval ：：NRF_ERROR_RESOURCES为此链接配置的连接事件长度不足以满足请求的参数。
 *                               Use @ref sd_ble_cfg_set与@ref ble_CONN_cfg_GAP一起使用以增加连接事件长度。检查p_dl_limition以查看限制的位置。
 * @retval ：：NRF_ERROR_BUSY对等端已启动数据长度更新过程。处理
 *                          pending @ref BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST事件以响应。
 */
SVCALL(SD_BLE_GAP_DATA_LENGTH_UPDATE, uint32_t, sd_ble_gap_data_length_update(uint16_t conn_handle, ble_gap_data_length_params_t const *p_dl_params, ble_gap_data_length_limitation_t *p_dl_limitation));

/**@brief   启动服务质量（QoS）信道调查模块。
 *
 * @details 信道测量模块提供蓝牙低能量信道上的能量水平测量。当模块启用时，@ref BLE_GAP_EVT_QOS_CHANNEL_SURVEY_REPORT事件将定期报告每个通道的测量能级。
 *
 * @note    与其他蓝牙低能耗角色、无线电时隙API事件和Flash API事件相比，测量的优先级较低。
 *
 * @note    信道测量模块将尝试进行测量，以便测量之间的平均间隔为interval_us。然而，由于频道调查模块具有所有角色和模块中最低的优先级，这可能是不可能的。在这种情况下，可能会给出比预期更少的渠道调查报告。
 *
 * @note    为了使用信道测量模块，必须设置@ref ble_gap_cfg_role_count_t:：qos_channel_survey_role_available。这是使用@ref sd_ble_cfg_set完成的。
 *
 * @param[in]   interval_us      测量和报告的请求平均间隔。看见
 *                               @ref 有效范围的BLE_GAP_QOS_CHANNEL_SURVEY_INTERVALS。如果已设置
 *                               to @ref BLE_GAP_QOS_CHANNEL_SURVEY_INTERVAL_CONTINUOUS，将在每个可用的机会安排频道调查角色。
 *
 * @retval ：：NRF_SUCCESS模块已成功启动。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。interval_us超出允许的范围。
 * @retval ：：NRF_ERROR_INVALID_STATE正在运行时尝试启动模块。
 * @retval ：：NRF_ERROR_RESOURCES应用程序无法使用频道测量模块。
 *                                   Set @ref ble_gap_cfg_role_count_t：：qos_channel_survey_role_available使用@ref sd_ble_cfg_set。
 */
SVCALL(SD_BLE_GAP_QOS_CHANNEL_SURVEY_START, uint32_t, sd_ble_gap_qos_channel_survey_start(uint32_t interval_us));

/**@brief   停止服务质量（QoS）信道调查模块。
 *
 * @retval ：：NRF_SUCCESS模块已成功停止。
 * @retval ：：NRF_ERROR_INVALID_STATE尝试在模块未运行时停止它。
 */
SVCALL(SD_BLE_GAP_QOS_CHANNEL_SURVEY_STOP, uint32_t, sd_ble_gap_qos_channel_survey_stop(void));


/** @} */

#ifdef __cplusplus
}
#endif
#endif // BLE_GAP_H__

/**
  @}
*/

