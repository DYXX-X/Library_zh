/*
 * 版权所有（c）2011-2017，Nordic Semiconductor ASA保留所有权利。
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
  @addtogroup BLE_GATTC通用属性配置文件（GATT）客户端@{
  @GATT客户界面的简要定义和原型。
 */

#ifndef BLE_GATTC_H__
#define BLE_GATTC_H__

#include <stdint.h>
#include "nrf.h"
#include "nrf_svc.h"
#include "nrf_error.h"
#include "ble_ranges.h"
#include "ble_types.h"
#include "ble_err.h"
#include "ble_gatt.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup BLE_GATTC_ENUMERATIONS枚举
 * @{ */

/**@brief GATTC API SVC编号。*/
enum BLE_GATTC_SVCS
{
  SD_BLE_GATTC_PRIMARY_SERVICES_DISCOVER = BLE_GATTC_SVC_BASE, /**<主要服务发现。*/
  SD_BLE_GATTC_RELATIONSHIPS_DISCOVER,                         /**<关系发现。*/
  SD_BLE_GATTC_CHARACTERISTICS_DISCOVER,                       /**<特性发现。*/
  SD_BLE_GATTC_DESCRIPTORS_DISCOVER,                           /**<特征描述符发现。*/
  SD_BLE_GATTC_ATTR_INFO_DISCOVER,                             /**<属性信息发现。*/
  SD_BLE_GATTC_CHAR_VALUE_BY_UUID_READ,                        /**<按UUID读取特征值。*/
  SD_BLE_GATTC_READ,                                           /**<通用读取。*/
  SD_BLE_GATTC_CHAR_VALUES_READ,                               /**<读取多个特征值。*/
  SD_BLE_GATTC_WRITE,                                          /**<通用写入。*/
  SD_BLE_GATTC_HV_CONFIRM,                                     /**<处理值确认。*/
  SD_BLE_GATTC_EXCHANGE_MTU_REQUEST,                           /**<Exchange MTU请求。*/
};

/**
 * @brief GATT客户端事件ID。
 */
enum BLE_GATTC_EVTS
{
  BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP = BLE_GATTC_EVT_BASE,  /**<主服务发现响应事件。\n请参见@ref ble_gattc_evt_prim_srvc_disc_rsp_t。*/
  BLE_GATTC_EVT_REL_DISC_RSP,                             /**<关系发现响应事件。\n请参见@ref ble_gattc_evt_rel_disc_rsp_t。*/
  BLE_GATTC_EVT_CHAR_DISC_RSP,                            /**<特征发现响应事件。\n请参见@ref ble_gattc_evt_char_disc_rsp_t。*/
  BLE_GATTC_EVT_DESC_DISC_RSP,                            /**<描述符发现响应事件。\n请参见@ref ble_gattc_evt_desc_disc_rsp_t。*/
  BLE_GATTC_EVT_ATTR_INFO_DISC_RSP,                       /**<属性信息响应事件。\n请参见@ref ble_gattc_evt_attr_info_disc_rsp_t。*/
  BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP,                /**<读取UUID响应事件。\n请参见@ref ble_gattc_evt_char_val_by_uid_read_rsp_t。*/
  BLE_GATTC_EVT_READ_RSP,                                 /**<读取响应事件。\n请参见@ref ble_gattc_evt_read_rsp_t。*/
  BLE_GATTC_EVT_CHAR_VALS_READ_RSP,                       /**<读取多个响应事件。\n请参见@ref ble_gattc_evt_char_vals_read_rsp_t。*/
  BLE_GATTC_EVT_WRITE_RSP,                                /**<写入响应事件。\n请参见@ref ble_gattc_evt_write_rsp_t。*/
  BLE_GATTC_EVT_HVX,                                      /**<句柄值通知或指示事件。\n用@ref sd_ble_gattc_hv_Confirm确认指示。\n请参见@ref ble_gattc_evt_hvx_t。*/
  BLE_GATTC_EVT_EXCHANGE_MTU_RSP,                         /**<Exchange MTU响应事件。\n请参见@ref ble_gattc_evt_exchange_mtu_rsp_t。*/
  BLE_GATTC_EVT_TIMEOUT,                                  /**<超时事件。\n请参见@ref ble_gattc_evt_timeout_t。*/
  BLE_GATTC_EVT_WRITE_CMD_TX_COMPLETE                     /**<写入而无响应传输完成。\n请参见@ref ble_gattc_evt_write_cmd_tx_complete_t。*/
};

/** @} */

/** @addtogroup BLE_GATTC_DEFINES定义
 * @{ */

/** @defgroup BLE_ERRORS_GATTC SVC特定于GATTC的返回值
 * @{ */
#define BLE_ERROR_GATTC_PROC_NOT_PERMITTED    (NRF_GATTC_ERR_BASE + 0x000) /**<程序不允许。*/
/** @} */

/** @defgroup BLE_GATTC_ATTR_INFO_FORMAT属性信息格式
 * @{ */
#define BLE_GATTC_ATTR_INFO_FORMAT_16BIT    1 /**＜16位属性信息格式。*/
#define BLE_GATTC_ATTR_INFO_FORMAT_128BIT   2 /**＜128位属性信息格式。*/
/** @} */

/** @defgroup BLE_GATTC_DEFAULT GATT客户端默认值
 * @{ */
#define BLE_GATTC_WRITE_CMD_TX_QUEUE_SIZE_DEFAULT  1 /**<可以排队等待传输的默认无响应写入数。*/
/** @} */

/** @} */

/** @addtogroup BLE_GATTC_STRUCTURES结构
 * @{ */

/**
 * @brief BLE GATTC连接配置参数，用@ref sd_BLE_cfg_set设置。
 */
typedef struct
{
  uint8_t  write_cmd_tx_queue_size; /**<可排队等待传输的无响应写入的保证最小数量。默认值为@ref BLE_GATTC_WRITE_CMD_TX_QUEUE_SIZE_default*/
} ble_gattc_conn_cfg_t;

/**@brief 操作手柄范围。*/
typedef struct
{
  uint16_t          start_handle; /**<启动手柄。*/
  uint16_t          end_handle;   /**<末端手柄。*/
} ble_gattc_handle_range_t;


/**@brief GATT服务。*/
typedef struct
{
  ble_uuid_t               uuid;          /**<服务UUID。*/
  ble_gattc_handle_range_t handle_range;  /**<服务手柄范围。*/
} ble_gattc_service_t;


/**@brief  GATT包括。*/
typedef struct
{
  uint16_t            handle;           /**<包括手柄。*/
  ble_gattc_service_t included_srvc;    /**<包含服务的句柄。*/
} ble_gattc_include_t;


/**@brief GATT特征。*/
typedef struct
{
  ble_uuid_t              uuid;                 /**<特征UUID。*/
  ble_gatt_char_props_t   char_props;           /**<特性特性。*/
  uint8_t                 char_ext_props : 1;   /**<存在扩展属性。*/
  uint16_t                handle_decl;          /**<特征声明的处理。*/
  uint16_t                handle_value;         /**<特征值的句柄。*/
} ble_gattc_char_t;


/**@brief GATT描述符。*/
typedef struct
{
  uint16_t          handle;         /**<描述符句柄。*/
  ble_uuid_t        uuid;           /**<描述符UUID。*/
} ble_gattc_desc_t;


/**@brief 写入参数。*/
typedef struct
{
  uint8_t        write_op;             /**<要执行的写入操作，请参阅@ref BLE_GATT_Write_OPS。*/
  uint8_t        flags;                /**<标志，请参见@ref BLE_GATT_EXEC_WRITE_Flags。*/
  uint16_t       handle;               /**<要写入的属性的句柄。*/
  uint16_t       offset;               /**<偏移量（字节）@注意：对于WRITE_CMD和WRITE_REQ，偏移量必须为0。*/
  uint16_t       len;                  /**<数据长度（字节）。*/
  uint8_t const *p_value;              /**<指向值数据的指针。*/
} ble_gattc_write_params_t;

/**@brief 16位属性UUID的属性信息。*/
typedef struct
{
  uint16_t       handle;               /**<属性句柄。*/
  ble_uuid_t     uuid;                 /**<16位属性UUID。*/
} ble_gattc_attr_info16_t;

/**@brief 128位属性UUID的属性信息。*/
typedef struct
{
  uint16_t       handle;               /**<属性句柄。*/
  ble_uuid128_t  uuid;                 /**<128位属性UUID。*/
} ble_gattc_attr_info128_t;

/**@brief @ref BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP的事件结构。*/
typedef struct
{
  uint16_t             count;           /**<服务计数。*/
  ble_gattc_service_t services[1];      /**<服务数据@注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
} ble_gattc_evt_prim_srvc_disc_rsp_t;

/**@brief @ref BLE_GATTC_EVT_REL_DISC_RSP的事件结构。*/
typedef struct
{
  uint16_t             count;           /**<包括计数。*/
  ble_gattc_include_t includes[1];      /**<包括数据@注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
} ble_gattc_evt_rel_disc_rsp_t;

/**@brief @ref BLE_GATTC_EVT_CHAR_DISC_RSP的事件结构。*/
typedef struct
{
  uint16_t            count;          /**<特征计数。*/
  ble_gattc_char_t    chars[1];       /**<特征数据@注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
} ble_gattc_evt_char_disc_rsp_t;

/**@brief @ref BLE_GATTC_EVT_DESC_ISC_RSP的事件结构。*/
typedef struct
{
  uint16_t            count;          /**<描述符计数。*/
  ble_gattc_desc_t    descs[1];       /**<描述符数据@注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
} ble_gattc_evt_desc_disc_rsp_t;

/**@brief @ref BLE_GATTC_EVT_ATTR_INFO_DISC_RSP的事件结构。*/
typedef struct
{
  uint16_t                     count;            /**<属性计数。*/
  uint8_t                      format;           /**<属性信息格式，请参见@ref BLE_GATTC_ATTR_INFO_format。*/
  union {
    ble_gattc_attr_info16_t  attr_info16[1];     /**< 16位属性UUID的属性信息。
                                                      @注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
    ble_gattc_attr_info128_t attr_info128[1];    /**< 128位属性UUID的属性信息。
                                                      @注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
  } info;                                        /**<属性信息联合。*/
} ble_gattc_evt_attr_info_disc_rsp_t;

/**@brief GATT由UUID句柄值对读取。*/
typedef struct
{
  uint16_t            handle;          /**<属性句柄。*/
  uint8_t            *p_value;         /**<指向属性值的指针，长度在@ref ble_gattc_evt_char_val_by_uid_read_rsp_t:：Value_len中可用。*/
} ble_gattc_handle_value_t;

/**@brief @ref BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP的事件结构。*/
typedef struct
{
  uint16_t                  count;            /**<句柄值对计数。*/
  uint16_t                  value_len;        /**<句柄值列表中值的长度。*/
  uint8_t                   handle_value[1];  /**< 句柄值列表。要遍历列表，请使用@ref sd_ble_gattc_evt_char_val_by_uid_read_rsp_iter。
                                                   @注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
} ble_gattc_evt_char_val_by_uuid_read_rsp_t;

/**@brief @ref BLE_GATTC_EVT_READ_RSP的事件结构。*/
typedef struct
{
  uint16_t            handle;         /**<属性句柄。*/
  uint16_t            offset;         /**<属性数据的偏移量。*/
  uint16_t            len;            /**<属性数据长度。*/
  uint8_t             data[1];        /**<属性数据@注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
} ble_gattc_evt_read_rsp_t;

/**@brief @ref BLE_GATTC_EVT_CHAR_VALS_READ_RSP的事件结构。*/
typedef struct
{
  uint16_t            len;            /**<级联属性值长度。*/
  uint8_t             values[1];      /**<属性值@注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
} ble_gattc_evt_char_vals_read_rsp_t;

/**@brief @ref BLE_GATTC_EVT_WRITE_RSP的事件结构。*/
typedef struct
{
  uint16_t            handle;           /**<属性句柄。*/
  uint8_t             write_op;         /**<写入操作类型，请参阅@ref BLE_GATT_write_OPS。*/
  uint16_t            offset;           /**<数据偏移。*/
  uint16_t            len;              /**<数据长度。*/
  uint8_t             data[1];          /**<数据@注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
} ble_gattc_evt_write_rsp_t;

/**@brief @ref BLE_GATTC_EVT_HVX的事件结构。*/
typedef struct
{
  uint16_t            handle;         /**<HVx操作适用的手柄。*/
  uint8_t             type;           /**<指示或通知，请参阅@ref BLE_GATT_HVX_TYPES。*/
  uint16_t            len;            /**<属性数据长度。*/
  uint8_t             data[1];        /**<属性数据@注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
} ble_gattc_evt_hvx_t;

/**@brief @ref BLE_GATTC_EVT_EXCHANGE_MTU_RSP的事件结构。*/
typedef struct
{
  uint16_t          server_rx_mtu;            /**<服务器RX MTU大小。*/
} ble_gattc_evt_exchange_mtu_rsp_t;

/**@brief @ref BLE_GATTC_EVT_TIMEOUT的事件结构。*/
typedef struct
{
  uint8_t          src;                       /**<超时源，请参见@ref BLE_GATT_Timeout_SOURCES。*/
} ble_gattc_evt_timeout_t;

/**@brief @ref BLE_GATTC_EVT_WRITE_CMD_TX_COMPLETE的事件结构。*/
typedef struct
{
  uint8_t             count;            /**<未完成响应传输的写入次数。*/
} ble_gattc_evt_write_cmd_tx_complete_t;

/**@brief GATTC事件结构。*/
typedef struct
{
  uint16_t            conn_handle;                /**<发生事件的连接句柄。*/
  uint16_t            gatt_status;                /**<操作的GATT状态代码，请参见@ref BLE_GATT_status_CODES。*/
  uint16_t            error_handle;               /**<如果出现错误：导致错误的句柄。在所有其他情况下，@ref BLE_GATT_HANDLE_INVALID。*/
  union
  {
    ble_gattc_evt_prim_srvc_disc_rsp_t          prim_srvc_disc_rsp;         /**<主要服务发现响应事件参数。*/
    ble_gattc_evt_rel_disc_rsp_t                rel_disc_rsp;               /**<关系发现响应事件参数。*/
    ble_gattc_evt_char_disc_rsp_t               char_disc_rsp;              /**<特征发现响应事件参数。*/
    ble_gattc_evt_desc_disc_rsp_t               desc_disc_rsp;              /**<描述符发现响应事件参数。*/
    ble_gattc_evt_char_val_by_uuid_read_rsp_t   char_val_by_uuid_read_rsp;  /**<UUID响应事件参数读取的特征值。*/
    ble_gattc_evt_read_rsp_t                    read_rsp;                   /**<读取响应事件参数。*/
    ble_gattc_evt_char_vals_read_rsp_t          char_vals_read_rsp;         /**<特征值读取响应事件参数。*/
    ble_gattc_evt_write_rsp_t                   write_rsp;                  /**<写入响应事件参数。*/
    ble_gattc_evt_hvx_t                         hvx;                        /**<句柄值通知/指示事件参数。*/
    ble_gattc_evt_exchange_mtu_rsp_t            exchange_mtu_rsp;           /**<Exchange MTU响应事件参数。*/
    ble_gattc_evt_timeout_t                     timeout;                    /**<超时事件参数。*/
    ble_gattc_evt_attr_info_disc_rsp_t          attr_info_disc_rsp;         /**<属性信息发现事件参数。*/
    ble_gattc_evt_write_cmd_tx_complete_t       write_cmd_tx_complete;      /**<写入无响应传输完成事件参数。*/
  } params;                                                                 /**<事件参数@注意：仅当@ref gatt_status==@ref BLE_gatt_status_SSUCCESS时有效。*/
} ble_gattc_evt_t;
/** @} */

/** @addtogroup BLE_GATTC_FUNCTIONS函数
 * @{ */

/**@brief 启动或继续GATT主要服务发现程序。
 *
 * @details 此函数从提供的句柄开始启动或恢复主服务发现过程。如果尚未到达最后一个服务，则必须使用更新的开始句柄值再次调用此函数以继续搜索。
 *
 * @note 如果发现的任何服务具有128位UUID，而这些UUID不在提供给ble_vs_UUIDs_assign的表中
 *       type @ref BLE_UUID_TYPE_UNKNOWN将在相应事件中接收。
 *
 * @events
 * @event{@ref BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTC_PRIM_SRVC_DISC_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 标识要对其执行此过程的连接的连接句柄。
 * @param[in] start_handle 开始搜索的句柄。
 * @param[in] p_srvc_uuid 指向要找到的服务UUID的指针。如果为NULL，则返回所有主服务。
 *
 * @retval ：：NRF_SUCCESS成功启动或恢复主服务发现过程。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_BUSY客户端过程已在进行中。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_PRIMARY_SERVICES_DISCOVER, uint32_t, sd_ble_gattc_primary_services_discover(uint16_t conn_handle, uint16_t start_handle, ble_uuid_t const *p_srvc_uuid));


/**@brief 启动或继续GATT关系发现程序。
 *
 * @details 此函数启动或恢复“查找包含的服务”子过程。如果尚未到达最后包含的服务，则必须使用更新的句柄范围再次调用该服务以继续搜索。
 *
 * @events
 * @event{@ref BLE_GATTC_EVT_REL_DISC_RSP}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTC_REL_DISC_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 标识要对其执行此过程的连接的连接句柄。
 * @param[in] p_handle_range 指向要对其执行此过程的服务句柄范围的指针。
 *
 * @retval ：：NRF_SUCCESS成功启动或恢复关系发现过程。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_BUSY客户端过程已在进行中。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_RELATIONSHIPS_DISCOVER, uint32_t, sd_ble_gattc_relationships_discover(uint16_t conn_handle, ble_gattc_handle_range_t const *p_handle_range));


/**@brief 启动或继续GATT特征发现程序。
 *
 * @details 此函数启动或恢复特征发现过程。如果尚未达到最后一个特征，则必须使用更新的句柄范围再次调用该特征以继续查找。
 *
 * @note 如果发现的任何特征具有128位UUID，而这些UUID不在提供给ble_vs_UUIDs_assign的表中
 *       type @ref BLE_UUID_TYPE_UNKNOWN将在相应事件中接收。
 *
 * @events
 * @event{@ref BLE_GATTC_EVT_CHAR_DISC_RSP}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTC_CHAR_DISC_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 标识要对其执行此过程的连接的连接句柄。
 * @param[in] p_handle_range 指向要对其执行此过程的服务句柄范围的指针。
 *
 * @retval ：：NRF_SUCCESS成功启动或恢复特征发现过程。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_BUSY客户端过程已在进行中。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_CHARACTERISTICS_DISCOVER, uint32_t, sd_ble_gattc_characteristics_discover(uint16_t conn_handle, ble_gattc_handle_range_t const *p_handle_range));


/**@brief 启动或继续GATT特征描述符发现程序。
 *
 * @details 此函数启动或恢复特征描述符发现过程。如果尚未到达最后一个描述符，则必须使用更新的句柄范围再次调用该描述符以继续查找。
 *
 * @events
 * @event{@ref BLE_GATTC_EVT_DESC_DISC_RSP}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTC_DESC_DISC_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 标识要对其执行此过程的连接的连接句柄。
 * @param[in] p_handle_range 指向要对其执行此过程的特征的句柄范围的指针。
 *
 * @retval ：：NRF_SUCCESS成功启动或恢复描述符发现过程。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_BUSY客户端过程已在进行中。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_DESCRIPTORS_DISCOVER, uint32_t, sd_ble_gattc_descriptors_discover(uint16_t conn_handle, ble_gattc_handle_range_t const *p_handle_range));


/**@brief 使用特征UUID程序启动或继续GATT读取。
 *
 * @details 此函数启动或恢复使用特征UUID的读取过程。如果尚未达到最后一个特征，则必须使用更新的句柄范围再次调用该特征以继续查找。
 *
 * @events
 * @event{@ref BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTC_READ_UUID_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 标识要对其执行此过程的连接的连接句柄。
 * @param[in] p_uuid 指向要读取的特征值UUID的指针。
 * @param[in] p_handle_range 指向要对其执行此过程的句柄范围的指针。
 *
 * @retval ：：NRF_SUCCESS成功启动或恢复使用特征UUID读取过程。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_BUSY客户端过程已在进行中。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_CHAR_VALUE_BY_UUID_READ, uint32_t, sd_ble_gattc_char_value_by_uuid_read(uint16_t conn_handle, ble_uuid_t const *p_uuid, ble_gattc_handle_range_t const *p_handle_range));


/**@brief 启动或继续GATT读取（长）特征或描述符程序。
 *
 * @details 此函数启动或恢复GATT读取（长）特征或描述符过程。如果要读取的特征或描述符长于ATT_MTU-1，则必须多次调用此函数，并使用适当的偏移量读取完整值。
 *
 * @events
 * @event{@ref BLE_GATTC_EVT_READ_RSP}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTC_VALUE_READ_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 标识要对其执行此过程的连接的连接句柄。
 * @param[in] handle 要读取的属性的句柄。
 * @param[in] offset 要读取的属性值的偏移量。
 *
 * @retval ：：NRF_SUCCESS成功启动或恢复读取（长）过程。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效。
 * @retval ：：NRF_ERROR_BUSY客户端过程已在进行中。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_READ, uint32_t, sd_ble_gattc_read(uint16_t conn_handle, uint16_t handle, uint16_t offset));


/**@brief 启动GATT读取多个特征值程序。
 *
 * @details 此函数启动GATT读取多个特征值过程。
 *
 * @events
 * @event{@ref BLE_GATTC_EVT_CHAR_VALS_READ_RSP}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTC_READ_MULT_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 标识要对其执行此过程的连接的连接句柄。
 * @param[in] p_handles 指向要读取的属性句柄的指针。
 * @param[in] handle_count p_handles中的句柄数。
 *
 * @retval ：：NRF_SUCCESS成功启动读取多个特征值过程。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_BUSY客户端过程已在进行中。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_CHAR_VALUES_READ, uint32_t, sd_ble_gattc_char_values_read(uint16_t conn_handle, uint16_t const *p_handles, uint16_t handle_count));


/**@brief 执行写入（特征值或描述符，有无响应，有无签名，长或可靠）过程。
 *
 * @details 此函数可以执行GATT中描述的所有写入过程。
 *
 * @note    每个连接一次只能执行一个带响应的写入过程。如果应用程序尝试使用响应写入，而另一个使用响应写入过程正在进行，则函数调用将返回@ref NRF_ERROR_BUSY。
 *          A @ref 一旦写入响应从对等端到达，将立即发出BLE_GATTC_EVT_WRITE_RSP事件。
 *
 * @note    可以排队的无响应写入的数量由@ref ble_gattc_conn_cfg_t:：Write_cmd_tx_queue_size配置。当队列已满时，函数调用将返回@ref NRF_ERROR_RESOURCES。
 *          A @ref 写入无响应传输完成后，将立即发出BLE_GATTC_EVT_WRITE_CMD_TX_COMPLETE事件。
 *
 * @note    应用程序可以通过以下过程跟踪无响应写入的可用队列元素计数：
 *          -将初始队列元素计数存储在变量中。
 *          -当调用此函数返回@ref NRF_SUCCESS时，将存储当前可用队列元素计数的变量减一。
 *          -用@ref BLE_GATTC_EVT_WRITE_CMD_TX_COMPLETE事件中的计数变量递增存储当前可用队列元素计数的变量。
 *
 * @events
 * @event{@ref BLE_GATTC_EVT_WRITE_CMD_TX_COMPLETE，写入而无响应传输完成。}
 * @event{@ref BLE_GATTC_EVT_WRITE_RSP，从对等端收到的写入响应。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTC_VALUE_WRITE_WITHOUT_RESP_MSC}
 * @mmsc{@ref BLE_GATTC_VALUE_WRITE_MSC}
 * @mmsc{@ref BLE_GATTC_VALUE_LONG_WRITE_MSC}
 * @mmsc{@ref BLE_GATTC_VALUE_RELIABLE_WRITE_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 标识要对其执行此过程的连接的连接句柄。
 * @param[in] p_write_params 指向写入参数结构的指针。
 *
 * @retval ：：NRF_SUCCESS成功启动写入过程。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_DATA_SIZE提供的数据大小无效。
 * @retval ：：NRF_ERROR_BUSY对于带响应的写入，过程已在进行中。等待@ref BLE_GATTC_EVT_WRITE_RSP事件，然后重试。
 * @retval ：：NRF_ERROR_RESOURCES队列中没有响应的写入太多。
 *                               Wait for a @ref BLE_GATTC_EVT_WRITE_CMD_TX_COMPLETE事件，然后重试。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_WRITE, uint32_t, sd_ble_gattc_write(uint16_t conn_handle, ble_gattc_write_params_t const *p_write_params));


/**@brief 向GATT服务器发送句柄值确认。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTC_HVI_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 标识要对其执行此过程的连接的连接句柄。
 * @param[in] handle 指示中属性的句柄。
 *
 * @retval ：：NRF_SUCCESS已成功将句柄值确认排队等待传输。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效或没有待确认的指示。
 * @retval ：：BLE_ERROR_INVALID_ATTR_HANDLE属性句柄无效。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_HV_CONFIRM, uint32_t, sd_ble_gattc_hv_confirm(uint16_t conn_handle, uint16_t handle));

/**@brief 发现有关GATT服务器上一系列属性的信息。
 *
 * @events
 * @event{@ref BLE_GATTC_EVT_ATTR_INFO_DISC_RSP，当接收到有关属性范围的信息时生成。}
 * @endevents
 *
 * @param[in] conn_handle    标识要对其执行此过程的连接的连接句柄。
 * @param[in] p_handle_range 请求有关信息的句柄范围。
 *
 * @retval ：：NRF_SUCCESS成功启动属性信息发现过程。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_BUSY客户端过程已在进行中。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_ATTR_INFO_DISCOVER, uint32_t, sd_ble_gattc_attr_info_discover(uint16_t conn_handle, ble_gattc_handle_range_t const * p_handle_range));

/**@brief 通过向服务器发送exchange MTU请求来启动ATT_MTU交换。
 *
 * @details SoftDevice将ATT_MTU设置为以下最小值：
 *          -客户端RX MTU值，以及
 *          -@ref BLE_GATTC_EVT_EXCHANGE_MTU_RSP中的服务器RX MTU值。
 *
 *          但是，SoftDevice从不将ATT_MTU设置为低于@ref BLE_GATT_ATT_MTU_DEFAULT。
 *
 * @events
 * @event{@ref BLE_GATTC_EVT_EXCHANGE_MTU_RSP}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTC_MTU_EXCHANGE}
 * @endmscs
 *
 * @param[in] conn_handle    标识要对其执行此过程的连接的连接句柄。
 * @param[in] client_rx_mtu  客户端RX MTU大小。
 *                           -最小值为@ref BLE_GATT_ATT_MTU_DEFAULT。
 *                           - The maximum value is @ref 用于此连接的连接配置中的ble_gatt_conn_cfg_t:：att_mtu。
 *                           - The value must be equal to Server RX MTU size given in @ref sd_ble_gatts_exchange_mtu_reply，如果已经在另一方向上执行ATT_mtu交换。
 *
 * @retval ：：NRF_SUCCESS已成功向服务器发送请求。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效或ATT_MTU交换已请求一次。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的客户端RX MTU大小无效。
 * @retval ：：NRF_ERROR_BUSY客户端过程已在进行中。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTC_EXCHANGE_MTU_REQUEST, uint32_t, sd_ble_gattc_exchange_mtu_request(uint16_t conn_handle, uint16_t client_rx_mtu));

/**@brief 遍历@ref BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP事件中的句柄值列表。
 *
 * @param[in] p_gattc_evt  指向包含@ref BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP事件的事件缓冲区的指针。
 *                         @note 如果缓冲区包含不同的事件，则行为未定义。
 * @param[in,out] p_iter   迭代器指向@ref ble_gattc_handle_value_t结构，该结构将在每次迭代中用下一个handle-value对填充。如果函数返回的不是
 *                         @ref NRF_SUCCESS，将不会更改。
 *                         -要开始迭代，请将结构初始化为零。
 *                         -若要继续，请传递上一次迭代的值。
 *
 * \代码ble_gattc_handle_value_titer；内存集（&iter，0，sizeof（ble_gattc_handle_value_t））；而（sd_ble_gattc_evt_char_val_by_uid_read_rsp_iter（&ble_evt.evt.gattc_evt，&iter）==NRF_SUCCESS）{app_handle=iter.handle；memcpy（app_value，iter.p_value，ble_evt.evt.gattc_evt.prarams.char_val_by_uid_read _rsp.value_len）；}\结束代码
 *
 * @retval ：：NRF_SUCCESS成功检索到下一个句柄值对。
 * @retval ：：NRF_ERROR_NOT_FOUND列表中没有更多的句柄值对可用。
 */
__STATIC_INLINE uint32_t sd_ble_gattc_evt_char_val_by_uuid_read_rsp_iter(ble_gattc_evt_t *p_gattc_evt, ble_gattc_handle_value_t *p_iter);

/** @} */

#ifndef SUPPRESS_INLINE_IMPLEMENTATION

__STATIC_INLINE uint32_t sd_ble_gattc_evt_char_val_by_uuid_read_rsp_iter(ble_gattc_evt_t *p_gattc_evt, ble_gattc_handle_value_t *p_iter)
{
  uint32_t value_len = p_gattc_evt->params.char_val_by_uuid_read_rsp.value_len;
  uint8_t *p_first = p_gattc_evt->params.char_val_by_uuid_read_rsp.handle_value;
  uint8_t *p_next = p_iter->p_value ? p_iter->p_value + value_len : p_first;

  if ((p_next - p_first) / (sizeof(uint16_t) + value_len) < p_gattc_evt->params.char_val_by_uuid_read_rsp.count)
  {
    p_iter->handle = (uint16_t)p_next[1] << 8 | p_next[0];
    p_iter->p_value = p_next + sizeof(uint16_t);
    return NRF_SUCCESS;
  }
  else
  {
    return NRF_ERROR_NOT_FOUND;
  }
}

#endif /* SUPPRESS_INLINE_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif
#endif /* BLE_GATTC_H__ */

/**
  @}
*/

