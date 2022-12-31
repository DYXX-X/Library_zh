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
  @addtogroup BLE_GATTS通用属性配置文件（GATT）服务器@{
  @GATTS接口的简要定义和原型。
 */

#ifndef BLE_GATTS_H__
#define BLE_GATTS_H__

#include <stdint.h>
#include "nrf_svc.h"
#include "nrf_error.h"
#include "ble_hci.h"
#include "ble_ranges.h"
#include "ble_types.h"
#include "ble_err.h"
#include "ble_gatt.h"
#include "ble_gap.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup BLE_GATTS_ENUMERATIONS枚举
 * @{ */

/**
 * @brief GATTS API SVC编号。
 */
enum BLE_GATTS_SVCS
{
  SD_BLE_GATTS_SERVICE_ADD = BLE_GATTS_SVC_BASE, /**<添加服务。*/
  SD_BLE_GATTS_INCLUDE_ADD,                      /**<添加包含的服务。*/
  SD_BLE_GATTS_CHARACTERISTIC_ADD,               /**<添加特征。*/
  SD_BLE_GATTS_DESCRIPTOR_ADD,                   /**<添加泛型属性。*/
  SD_BLE_GATTS_VALUE_SET,                        /**<设置属性值。*/
  SD_BLE_GATTS_VALUE_GET,                        /**<获取属性值。*/
  SD_BLE_GATTS_HVX,                              /**<处理值通知或指示。*/
  SD_BLE_GATTS_SERVICE_CHANGED,                  /**<向一个或多个对等方执行服务更改指示。*/
  SD_BLE_GATTS_RW_AUTHORIZE_REPLY,               /**<答复对一个或多个属性的读或写操作的授权请求。*/
  SD_BLE_GATTS_SYS_ATTR_SET,                     /**<设置连接的持久系统属性。*/
  SD_BLE_GATTS_SYS_ATTR_GET,                     /**<检索持久系统属性。*/
  SD_BLE_GATTS_INITIAL_USER_HANDLE_GET,          /**<检索第一个有效的用户句柄。*/
  SD_BLE_GATTS_ATTR_GET,                         /**<检索属性的UUID和/或元数据。*/
  SD_BLE_GATTS_EXCHANGE_MTU_REPLY                /**<回复Exchange MTU请求。*/
};

/**
 * @brief GATT服务器事件ID。
 */
enum BLE_GATTS_EVTS
{
  BLE_GATTS_EVT_WRITE = BLE_GATTS_EVT_BASE,       /**<已执行写入操作。\n请参见@ref ble_gatts_evt_write_t。*/
  BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST,             /**<读/写授权请求。\n回复@ref sd_ble_gatts_rw_authorize_Reply。\n请参见@ref ble_gatts_evt_rw_authorize_request_t。*/
  BLE_GATTS_EVT_SYS_ATTR_MISSING,                 /**<持久系统属性访问处于挂起状态。\n回复@ref sd_ble_gatts_sys_attr_set。\n请参见@ref ble_gatts_evt_sys_attr_missing_t。*/
  BLE_GATTS_EVT_HVC,                              /**<处理值确认。\n请参见@ref ble_gatts_evt_hvc_t。*/
  BLE_GATTS_EVT_SC_CONFIRM,                       /**<服务更改确认。\n不适用其他事件结构。*/
  BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST,             /**<Exchange MTU请求。\n回复@ref sd_ble_gatts_exchange_mtu_Reply。\n请参见@ref ble_gatts_evt_exchange_mtu_request_t。*/
  BLE_GATTS_EVT_TIMEOUT,                          /**<对等方未能及时响应ATT请求。\n请参见@ref ble_gatts_evt_timeout_t。*/
  BLE_GATTS_EVT_HVN_TX_COMPLETE                   /**<句柄值通知传输完成。\n请参见@ref ble_gatts_evt_hvn_tx_complete_t。*/
};

/**@brief GATTS配置ID。
 *
 * 唯一标识GATTS配置的ID。
 */
enum BLE_GATTS_CFGS
{
  BLE_GATTS_CFG_SERVICE_CHANGED = BLE_GATTS_CFG_BASE, /**<服务已更改配置。*/
  BLE_GATTS_CFG_ATTR_TAB_SIZE,                        /**<属性表大小配置。*/
};

/** @} */

/** @addtogroup BLE_GATTS_DEFINES定义
 * @{ */

/** @defgroup BLE_ERRORS_GATTS特定于GATTS的SVC返回值
 * @{ */
#define BLE_ERROR_GATTS_INVALID_ATTR_TYPE   (NRF_GATTS_ERR_BASE + 0x000) /**<属性类型无效。*/
#define BLE_ERROR_GATTS_SYS_ATTR_MISSING    (NRF_GATTS_ERR_BASE + 0x001) /**<缺少系统属性。*/
/** @} */

/** @defgroup BLE_GATTS_ATTR_LENS_MAX最大属性长度
 * @{ */
#define BLE_GATTS_FIX_ATTR_LEN_MAX (510)  /**<固定长度属性值的最大长度。*/
#define BLE_GATTS_VAR_ATTR_LEN_MAX (512)  /**<可变长度属性值的最大长度。*/
/** @} */

/** @defgroup BLE_GATTS_SRVC_TYPES GATT服务器服务类型
 * @{ */
#define BLE_GATTS_SRVC_TYPE_INVALID          0x00  /**<服务类型无效。*/
#define BLE_GATTS_SRVC_TYPE_PRIMARY          0x01  /**<主要服务。*/
#define BLE_GATTS_SRVC_TYPE_SECONDARY        0x02  /**<次要类型。*/
/** @} */


/** @defgroup BLE_GATTS_ATTR_TYPES GATT服务器属性类型
 * @{ */
#define BLE_GATTS_ATTR_TYPE_INVALID         0x00  /**<属性类型无效。*/
#define BLE_GATTS_ATTR_TYPE_PRIM_SRVC_DECL  0x01  /**<主要服务声明。*/
#define BLE_GATTS_ATTR_TYPE_SEC_SRVC_DECL   0x02  /**<辅助服务声明。*/
#define BLE_GATTS_ATTR_TYPE_INC_DECL        0x03  /**<包括声明。*/
#define BLE_GATTS_ATTR_TYPE_CHAR_DECL       0x04  /**<特性声明。*/
#define BLE_GATTS_ATTR_TYPE_CHAR_VAL        0x05  /**<特征值。*/
#define BLE_GATTS_ATTR_TYPE_DESC            0x06  /**<描述符。*/
#define BLE_GATTS_ATTR_TYPE_OTHER           0x07  /**<其他非GATT特定类型。*/
/** @} */


/** @defgroup BLE_GATTS_OPS GATT服务器操作
 * @{ */
#define BLE_GATTS_OP_INVALID                0x00  /**<无效操作。*/
#define BLE_GATTS_OP_WRITE_REQ              0x01  /**<写入请求。*/
#define BLE_GATTS_OP_WRITE_CMD              0x02  /**<写入命令。*/
#define BLE_GATTS_OP_SIGN_WRITE_CMD         0x03  /**<签名写入命令。*/
#define BLE_GATTS_OP_PREP_WRITE_REQ         0x04  /**<准备写入请求。*/
#define BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL  0x05  /**<执行写入请求：取消所有准备的写入。*/
#define BLE_GATTS_OP_EXEC_WRITE_REQ_NOW     0x06  /**<执行写入请求：立即执行所有准备好的写入。*/
/** @} */

/** @defgroup BLE_GATTS_VLOCS GATT值位置
 * @{ */
#define BLE_GATTS_VLOC_INVALID       0x00  /**<无效位置。*/
#define BLE_GATTS_VLOC_STACK         0x01  /**<属性值位于堆栈内存中，不需要用户内存。*/
#define BLE_GATTS_VLOC_USER          0x02  /**<属性值位于用户内存中。这需要用户在属性的整个生命周期内保持有效的缓冲区，因为堆栈将使用API中提供的指针直接读取和写入内存。缓冲区没有对齐要求。*/
/** @} */

/** @defgroup BLE_GATTS_AUTHORIZE_TYPES GATT服务器授权类型
 * @{ */
#define BLE_GATTS_AUTHORIZE_TYPE_INVALID    0x00  /**<无效类型。*/
#define BLE_GATTS_AUTHORIZE_TYPE_READ       0x01  /**<授权读取操作。*/
#define BLE_GATTS_AUTHORIZE_TYPE_WRITE      0x02  /**<授权写请求操作。*/
/** @} */

/** @defgroup BLE_GATTS_SYS_ATTR_FLAGS系统属性标志
 * @{ */
#define BLE_GATTS_SYS_ATTR_FLAG_SYS_SRVCS (1 << 0)  /**<仅将系统属性限制为系统服务。*/
#define BLE_GATTS_SYS_ATTR_FLAG_USR_SRVCS (1 << 1)  /**<仅将系统属性限制为用户服务。*/
/** @} */

/** @defgroup BLE_GATTS_SERVICE_CHANGED服务已更改包含值@{
 */
#define BLE_GATTS_SERVICE_CHANGED_DEFAULT   (1)   /**<默认值是在属性表中包含服务更改特性。*/
/** @} */

/** @defgroup BLE_GATTS_ATTR_TAB_SIZE属性表大小@{
 */
#define BLE_GATTS_ATTR_TAB_SIZE_MIN         (248)  /**<最小属性表大小*/
#define BLE_GATTS_ATTR_TAB_SIZE_DEFAULT     (1408) /**<默认属性表大小。*/
/** @} */

/** @defgroup BLE_GATTS_DEFAULT GATT服务器默认值@{
 */
#define BLE_GATTS_HVN_TX_QUEUE_SIZE_DEFAULT  1 /**<可排队等待传输的句柄值通知的默认数量。*/
/** @} */

/** @} */

/** @addtogroup BLE_GATTS_STRUCTURES结构
 * @{ */

/**
 * @brief BLE GATTS连接配置参数，用@ref sd_BLE_cfg_set设置。
 */
typedef struct
{
  uint8_t  hvn_tx_queue_size; /**<可排队传输的最小保证句柄值通知数。默认值为@ref BLE_GATTS_HVN_TX_QUEUE_SIZE_default*/
} ble_gatts_conn_cfg_t;

/**@brief 属性元数据。*/
typedef struct
{
  ble_gap_conn_sec_mode_t read_perm;       /**<读取权限。*/
  ble_gap_conn_sec_mode_t write_perm;      /**<写入权限。*/
  uint8_t                 vlen       :1;   /**<可变长度属性。*/
  uint8_t                 vloc       :2;   /**<值位置，请参见@ref BLE_GATTS_VLOCS。*/
  uint8_t                 rd_auth    :1;   /**<每次读取操作都会向应用程序请求读取授权和值。*/
  uint8_t                 wr_auth    :1;   /**<在每次写入请求操作（但不是写入命令）时，将从应用程序请求写入授权。*/
} ble_gatts_attr_md_t;


/**@brief GATT属性。*/
typedef struct
{
  ble_uuid_t const          *p_uuid;        /**<指向属性UUID的指针。*/
  ble_gatts_attr_md_t const *p_attr_md;     /**<指向属性元数据结构的指针。*/
  uint16_t                   init_len;      /**<初始属性值长度（字节）。*/
  uint16_t                   init_offs;     /**<初始属性值偏移量（字节）。如果与零不同，则属性值的第一个init_offs字节将保持未初始化状态。*/
  uint16_t                   max_len;       /**<最大属性值长度（字节），请参阅@ref BLE_GATTS_ATTR_LENS_MAX获取最大值。*/
  uint8_t                   *p_value;       /**<指向属性数据的指针。请注意，如果在属性元数据中选择了@ref BLE_GATTS_VLOC_USER值位置，则必须指向在属性的整个生命周期内保持有效的缓冲区。这排除了可能超出范围或任何其他临时位置的自动变量的使用。堆栈可以在应用程序不知道的情况下直接访问该存储器。对于可写特性，此值不能是闪存中的位置。*/
} ble_gatts_attr_t;

/**@brief GATT属性值。*/
typedef struct
{
  uint16_t  len;        /**<要写入或读取的字节长度。成功返回后写入或读取的字节长度。*/
  uint16_t  offset;     /**<属性值偏移。*/
  uint8_t  *p_value;    /**<指向存储或将存储值的位置的指针。如果值存储在用户内存中，则当p_value==NULL时，仅更新属性长度。读取时设置为NULL以获取属性值的完整长度*/
} ble_gatts_value_t;


/**@brief GATT特征表示格式。*/
typedef struct
{
  uint8_t          format;      /**<值的格式，请参见@ref BLE_GATT_CPF_FORMATS。*/
  int8_t           exponent;    /**<整数数据类型的指数。*/
  uint16_t         unit;        /**<来自蓝牙分配号码的单位。*/
  uint8_t          name_space;  /**<来自蓝牙分配号码的命名空间，请参阅@ref BLE_GATT_CPF_NAMESPACES。*/
  uint16_t         desc;        /**<来自Bluetooth Assigned Numbers的命名空间描述，请参见@ref BLE_GATT_CPF_NAMESPACES。*/
} ble_gatts_char_pf_t;


/**@brief GATT特征元数据。*/
typedef struct
{
  ble_gatt_char_props_t       char_props;               /**<特性特性。*/
  ble_gatt_char_ext_props_t   char_ext_props;           /**<特性扩展属性。*/
  uint8_t const              *p_char_user_desc;         /**<指向UTF-8编码字符串（非NULL终止）的指针，如果不需要描述符，则为NULL。*/
  uint16_t                    char_user_desc_max_size;  /**<用户描述描述符的最大字节数。*/
  uint16_t                    char_user_desc_size;      /**<用户描述的大小必须小于或等于char_user_desc_max_size。*/
  ble_gatts_char_pf_t const  *p_char_pf;                /**<指向表示格式结构的指针，如果不需要CPF描述符，则为NULL。*/
  ble_gatts_attr_md_t const  *p_user_desc_md;           /**<用户描述描述符的属性元数据，或默认值为NULL。*/
  ble_gatts_attr_md_t const  *p_cccd_md;                /**<客户端特征配置描述符的属性元数据，或默认值为NULL。*/
  ble_gatts_attr_md_t const  *p_sccd_md;                /**<服务器特征配置描述符的属性元数据，或默认值为NULL。*/
} ble_gatts_char_md_t;


/**@brief GATT特征定义处理。*/
typedef struct
{
  uint16_t          value_handle;       /**<特征值的句柄。*/
  uint16_t          user_desc_handle;   /**<用户描述描述符的句柄，或@ref BLE_GATT_Handle_INVALID（如果不存在）。*/
  uint16_t          cccd_handle;        /**<客户端特征配置描述符的句柄，或@ref BLE_GATT_Handle_INVALID（如果不存在）。*/
  uint16_t          sccd_handle;        /**<服务器特征配置描述符的句柄，或@ref BLE_GATT_Handle_INVALID（如果不存在）。*/
} ble_gatts_char_handles_t;


/**@brief GATT HVx参数。*/
typedef struct
{
  uint16_t          handle;             /**<特征值句柄。*/
  uint8_t           type;               /**<指示或通知，请参阅@ref BLE_GATT_HVX_TYPES。*/
  uint16_t          offset;             /**<属性值内的偏移。*/
  uint16_t         *p_len;              /**<要写入的字节长度，返回后写入的字节数。*/
  uint8_t const    *p_data;             /**<实际数据内容，使用NULL使用当前属性值。*/
} ble_gatts_hvx_params_t;

/**@brief GATT授权参数。*/
typedef struct
{
  uint16_t          gatt_status;        /**<操作的GATT状态代码，请参见@ref BLE_GATT_status_CODES。*/
  uint8_t           update : 1;         /**< 如果设置，p_data中提供的数据将用于更新属性值。
                                             请注意，对于@ref BLE_GATTS_AUTHORIZE_TYPE_WRITE操作，必须始终设置此位，因为要写入的数据需要存储，稍后由应用程序提供。*/
  uint16_t          offset;             /**<正在更新的属性值的偏移。*/
  uint16_t          len;                /**<p_data指针中值的字节长度，请参见@ref BLE_GATTS_ATTR_LENS_MAX。*/
  uint8_t const    *p_data;             /**<指向用于更新属性值的新值的指针。*/
} ble_gatts_authorize_params_t;

/**@brief GATT读取或写入授权回复参数。*/
typedef struct
{
  uint8_t                               type;   /**<授权操作类型，请参阅@ref BLE_GATTS_authorize_TYPES。*/
  union {
    ble_gatts_authorize_params_t        read;   /**<读取授权参数。*/
    ble_gatts_authorize_params_t        write;  /**<写入授权参数。*/
  } params;                                     /**<回复参数。*/
} ble_gatts_rw_authorize_reply_params_t;

/**@brief 服务已更改包含配置参数，使用@ref sd_ble_cfg_set设置。*/
typedef struct
{
  uint8_t service_changed : 1;       /**<如果为1，则在属性表中包括服务更改特性。默认值为@ref BLE_GATTS_SERVICE_CHANGED_Default。*/
} ble_gatts_cfg_service_changed_t;

/**@brief 属性表大小配置参数，使用@ref sd_ble_cfg_set设置。
 *
 * @retval ：：NRF_ERROR_INVALID_LENGTH以下一项或多项为真：
 *                                    -指定的属性表大小太小。最小可接受大小由@ref BLE_GATTS_ATTR_TAB_size_MIN定义。
 *                                    -指定的属性表大小不是4的倍数。
 */
typedef struct
{
  uint32_t attr_tab_size; /**<属性表大小。默认值为@ref BLE_GATTS_ATTR_TAB_SIZE_Default，最小值为@ref BLE_GATTS_ATTR_TAB_StIZE_MIN。*/
} ble_gatts_cfg_attr_tab_size_t;

/**@brief GATTS配置的配置结构。*/
typedef union
{
  ble_gatts_cfg_service_changed_t service_changed;  /**<包括服务更改特征，cfg_id为@ref BLE_GATTS_cfg_service_changed。*/
  ble_gatts_cfg_attr_tab_size_t attr_tab_size;      /**<属性表大小，cfg_id为@ref BLE_GATTS_cfg_ATTR_TAB_size。*/
} ble_gatts_cfg_t;


/**@brief @ref BLE_GATTS_EVT_WRITE的事件结构。*/
typedef struct
{
  uint16_t                    handle;             /**<属性句柄。*/
  ble_uuid_t                  uuid;               /**<属性UUID。*/
  uint8_t                     op;                 /**<写入操作类型，请参阅@ref BLE_GATTS_OPS。*/
  uint8_t                     auth_required;      /**<由于授权要求，写入操作延迟。应用程序可以使用@ref sd_ble_gatts_value_set完成写入操作。*/
  uint16_t                    offset;             /**<写入操作的偏移量。*/
  uint16_t                    len;                /**<接收数据的长度。*/
  uint8_t                     data[1];            /**<接收数据@注意：这是一个可变长度数组。指示的大小1只是用于编译的占位符。有关如何将事件结构与可变长度数组成员一起使用的更多信息，请参见@ref sd_ble_evt_get。*/
} ble_gatts_evt_write_t;

/**@brief 授权读取请求的事件子结构，请参见@ref ble_gatts_evt_rw_authorize_request_t。*/
typedef struct
{
  uint16_t                    handle;             /**<属性句柄。*/
  ble_uuid_t                  uuid;               /**<属性UUID。*/
  uint16_t                    offset;             /**<读取操作的偏移量。*/
} ble_gatts_evt_read_t;

/**@brief @ref BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST的事件结构。*/
typedef struct
{
  uint8_t                     type;             /**<授权操作类型，请参阅@ref BLE_GATTS_authorize_TYPES。*/
  union {
    ble_gatts_evt_read_t      read;             /**<属性读取参数。*/
    ble_gatts_evt_write_t     write;            /**<属性写入参数。*/
  } request;                                    /**<请求参数。*/
} ble_gatts_evt_rw_authorize_request_t;

/**@brief @ref BLE_GATTS_EVT_SYS_ATTR_MISSING的事件结构。*/
typedef struct
{
  uint8_t hint;                                 /**<提示（当前未使用）。*/
} ble_gatts_evt_sys_attr_missing_t;


/**@brief @ref BLE_GATTS_EVT_HVC的事件结构。*/
typedef struct
{
  uint16_t          handle;                       /**<属性句柄。*/
} ble_gatts_evt_hvc_t;

/**@brief @ref BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST的事件结构。*/
typedef struct
{
  uint16_t          client_rx_mtu;              /**<客户端RX MTU大小。*/
} ble_gatts_evt_exchange_mtu_request_t;

/**@brief @ref BLE_GATTS_EVT_TIMEOUT的事件结构。*/
typedef struct
{
  uint8_t          src;                       /**<超时源，请参见@ref BLE_GATT_Timeout_SOURCES。*/
} ble_gatts_evt_timeout_t;

/**@brief @ref BLE_GATTS_EVT_HVN_TX_COMPLETE的事件结构。*/
typedef struct
{
  uint8_t          count;                     /**<完成的通知传输数。*/
} ble_gatts_evt_hvn_tx_complete_t;

/**@brief GATTS事件结构。*/
typedef struct
{
  uint16_t conn_handle;                                       /**<发生事件的连接句柄。*/
  union
  {
    ble_gatts_evt_write_t                 write;                 /**<写入事件参数。*/
    ble_gatts_evt_rw_authorize_request_t  authorize_request;     /**<读取或写入授权请求参数。*/
    ble_gatts_evt_sys_attr_missing_t      sys_attr_missing;      /**<缺少系统属性。*/
    ble_gatts_evt_hvc_t                   hvc;                   /**<句柄值确认事件参数。*/
    ble_gatts_evt_exchange_mtu_request_t  exchange_mtu_request;  /**<Exchange MTU请求事件参数。*/
    ble_gatts_evt_timeout_t               timeout;               /**<超时事件。*/
    ble_gatts_evt_hvn_tx_complete_t       hvn_tx_complete;       /**<句柄值通知传输完成事件参数。*/
  } params;                                                      /**<事件参数。*/
} ble_gatts_evt_t;

/** @} */

/** @addtogroup BLE_GATTS_FUNCTIONS函数
 * @{ */

/**@brief 将服务声明添加到属性表。
 *
 * @note 辅助服务仅在引用它们的实体的上下文中相关，因此禁止在稍后的属性表中添加未被其他服务引用的辅助服务声明。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_ATT_TABLE_POP_MSC}
 * @endmscs
 *
 * @param[in] type      在主服务和辅助服务之间切换，请参见@ref BLE_GATTS_SRVC_TYPES。
 * @param[in] p_uuid    指向服务UUID的指针。
 * @param[out] p_handle 指向将存储指定句柄的16位字的指针。
 *
 * @retval ：：NRF_SUCCESS成功添加服务声明。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效，表中需要存在供应商特定UUID。
 * @retval ：：提供了NRF_ERROR_FORBIDDEN禁止值，为堆栈保留了某些UUID。
 * @retval ：：NRF_ERROR_NO_MEM内存不足，无法完成操作。
 */
SVCALL(SD_BLE_GATTS_SERVICE_ADD, uint32_t, sd_ble_gatts_service_add(uint8_t type, ble_uuid_t const *p_uuid, uint16_t *p_handle));


/**@brief 将include声明添加到属性表。
 *
 * @note 当前只能向最后添加的服务添加include声明（即，此时只支持顺序填充）。
 *
 * @note 在此调用之前，包含的服务必须已存在于属性表中。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_ATT_TABLE_POP_MSC}
 * @endmscs
 *
 * @param[in] service_handle    要放置包含服务的服务的句柄，如果使用@ref BLE_GATT_Handle_INVALID，则将按顺序放置。
 * @param[in] inc_srvc_handle   包含服务的句柄。
 * @param[out] p_include_handle 指向将存储指定句柄的16位字的指针。
 *
 * @retval ：：NRF_SUCCESS成功添加了include声明。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效，句柄值需要匹配先前添加的服务。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效，需要服务上下文。
 * @retval ：：NRF_ERROR_NOT_SUPPORTED功能不受支持，service_handle必须是上次添加的服务的名称。
 * @retval ：：提供了NRF_ERROR_FORBIDDEN禁止值，不允许自包含。
 * @retval ：：NRF_ERROR_NO_MEM内存不足，无法完成操作。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND属性。
 */
SVCALL(SD_BLE_GATTS_INCLUDE_ADD, uint32_t, sd_ble_gatts_include_add(uint16_t service_handle, uint16_t inc_srvc_handle, uint16_t *p_include_handle));


/**@brief 将特性声明、特性值声明和可选特性描述符声明添加到属性表中。
 *
 * @note 当前只能向最后添加的服务添加特征（即，此时仅支持顺序填充）。
 *
 * @note 一些限制适用于参数，例如用户描述描述符和可写辅助位之间的匹配权限、可读（无安全性）和可写（可选）CCCD和SCCD以及有效的呈现格式值。
 *
 * @note 如果没有为可选描述符提供元数据，则其权限将从特征权限派生。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_ATT_TABLE_POP_MSC}
 * @endmscs
 *
 * @param[in] service_handle    要放置特征的服务的句柄，如果使用@ref BLE_GATT_Handle_INVALID，则将按顺序放置。
 * @param[in] p_char_md         特征元数据。
 * @param[in] p_attr_char_value 指向与特征值对应的属性结构的指针。
 * @param[out] p_handles        指向将存储分配句柄的结构的指针。
 *
 * @retval ：：NRF_SUCCESS成功添加特征。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效，服务句柄、供应商特定UUID、长度和权限需要遵守约束。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效，需要服务上下文。
 * @retval ：：提供了NRF_ERROR_FORBIDDEN禁止值，为堆栈保留了某些UUID。
 * @retval ：：NRF_ERROR_NO_MEM内存不足，无法完成操作。
 * @retval ：：NRF_ERROR_DATA_SIZE提供的数据大小无效，属性长度受@ref BLE_GATTS_ATTR_LENS_MAX限制。
 */
SVCALL(SD_BLE_GATTS_CHARACTERISTIC_ADD, uint32_t, sd_ble_gatts_characteristic_add(uint16_t service_handle, ble_gatts_char_md_t const *p_char_md, ble_gatts_attr_t const *p_attr_char_value, ble_gatts_char_handles_t *p_handles));


/**@brief 向属性表添加描述符。
 *
 * @note 目前，只能向最后添加的特征添加描述符（即，此时仅支持顺序填充）。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_ATT_TABLE_POP_MSC}
 * @endmscs
 *
 * @param[in] char_handle   要放置描述符的特征的句柄，如果使用@ref BLE_GATT_Handle_INVALID，则将按顺序放置。
 * @param[in] p_attr        指向属性结构的指针。
 * @param[out] p_handle     指向将存储指定句柄的16位字的指针。
 *
 * @retval ：：NRF_SUCCESS成功添加描述符。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效，特征句柄、供应商特定UUID、长度和权限需要遵守约束。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效，需要特征上下文。
 * @retval ：：提供了NRF_ERROR_FORBIDDEN禁止值，为堆栈保留了某些UUID。
 * @retval ：：NRF_ERROR_NO_MEM内存不足，无法完成操作。
 * @retval ：：NRF_ERROR_DATA_SIZE提供的数据大小无效，属性长度受@ref BLE_GATTS_ATTR_LENS_MAX限制。
 */
SVCALL(SD_BLE_GATTS_DESCRIPTOR_ADD, uint32_t, sd_ble_gatts_descriptor_add(uint16_t char_handle, ble_gatts_attr_t const *p_attr, uint16_t *p_handle));

/**@brief 设置给定属性的值。
 *
 * @note 无论是否存在任何活动连接，都可以随时设置系统属性以外的值。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_QUEUE_FULL_MSC}
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_NOBUF_NOAUTH_MSC}
 * @endmscs
 *
 * @param[in] conn_handle  连接手柄。如果值不属于系统属性，则忽略。
 * @param[in] handle       属性句柄。
 * @param[in,out] p_value  属性值信息。
 *
 * @retval ：：NRF_SUCCESS成功设置属性值。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND属性。
 * @retval ：：提供了NRF_ERROR_FORBIDDEN禁止句柄，应用程序无法修改某些属性。
 * @retval ：：NRF_ERROR_DATA_SIZE提供的数据大小无效，属性长度受@ref BLE_GATTS_ATTR_LENS_MAX限制。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE系统属性上提供的连接句柄无效。
 */
SVCALL(SD_BLE_GATTS_VALUE_SET, uint32_t, sd_ble_gatts_value_set(uint16_t conn_handle, uint16_t handle, ble_gatts_value_t *p_value));

/**@brief 获取给定属性的值。
 *
 * @note                 如果属性值长于所提供的缓冲器的大小，
 *                       @ref ble_gatts_value_t：：len将返回总属性值长度（不包括偏移量），而不是@ref ble_gatts-value_t:：p_value中实际返回的字节数。应用程序可以使用该信息来分配合适的缓冲区大小。
 *
 * @note                 使用此函数检索系统属性值时，连接句柄可能引用已断开的连接。请参阅
 *                       @ref sd_ble_gatts_sys_attr_get获取更多信息。
 *
 * @param[in] conn_handle  连接手柄。如果值不属于系统属性，则忽略。
 * @param[in] handle       属性句柄。
 * @param[in,out] p_value  属性值信息。
 *
 * @retval ：：NRF_SUCCESS成功检索到属性的值。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND属性。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的属性偏移量无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE系统属性上提供的连接句柄无效。
 * @retval ：：BLE_ERROR_GATTS_SYS_ATTR_MISSING缺少系统属性，请使用@ref sd_BLE_GATTS_SYS_ATTR_set将其设置为已知值。
 */
SVCALL(SD_BLE_GATTS_VALUE_GET, uint32_t, sd_ble_gatts_value_get(uint16_t conn_handle, uint16_t handle, ble_gatts_value_t *p_value));

/**@brief 通知或指示属性值。
 *
 * @details 此函数检查相关的客户端特征配置描述符值，以验证客户端已启用相关操作（通知或指示）。它还能够在发布PDU之前更新属性值，以便应用程序可以通过单个API调用自动执行值更新和服务器启动的事务。
 *
 * @note    即使由于执行过程中的错误而没有将传出分组发送到对等端，也可以更新本地属性值。如果返回以下错误代码之一，属性表已更新：@ref NRF_error_INVALID_STATE、@ref NRF-error_BUSY、，
 *          @ref NRF_ERROR_FORBIDDEN、@ref BLE_ERROR_GATTS_SYS_ATTR_MISSING和@ref NRF_ERROR_RESOURCES。调用者可以通过查看（@ref ble_gatts_hvx_params_t:：p_len）的内容来检查值是否已更新。
 *
 * @note    每个连接一次只能进行一个指示过程。如果应用程序试图在另一个指示过程正在进行时指示属性值，则函数调用将返回@ref NRF_ERROR_BUSY。
 *          A @ref 一旦对等方收到确认，将立即发出BLE_GATTS_EVT_HVC事件。
 *
 * @note    可以排队的句柄值通知数由@ref ble_gatts_conn_cfg_t:：hvn_tx_queue_size配置。当队列已满时，函数调用将返回@ref NRF_ERROR_RESOURCES。
 *          A @ref 一旦通知传输完成，将立即发出BLE_GATTS_EVT_HVN_TX_COMPLETE事件。
 *
 * @note    应用程序可以通过以下过程跟踪通知的可用队列元素计数：
 *          -将初始队列元素计数存储在变量中。
 *          -当调用此函数返回@ref NRF_SUCCESS时，将存储当前可用队列元素计数的变量减一。
 *          -用@ref BLE_GATTS_EVT_HVN_TX_COMPLETE事件中的计数变量递增变量，该变量存储当前可用的队列元素计数。
 *
 * @events
 * @event{@ref BLE_GATTS_EVT_HVN_TX_COMPLETE，通知传输完成。}
 * @event{@ref BLE_GATTS_EVT_HVC，从对等方收到确认。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_HVX_SYS_ATTRS_MISSING_MSC}
 * @mmsc{@ref BLE_GATTS_HVN_MSC}
 * @mmsc{@ref BLE_GATTS_HVI_MSC}
 * @mmsc{@ref BLE_GATTS_HVX_DISABLED_MSC}
 * @endmscs
 *
 * @param[in] conn_handle      连接手柄。
 * @param[in,out] p_hvx_params 指向HVx参数结构的指针。如果@ref ble_gatts_hvx_params_t:：p_data包含非NULL指针，则在发送通知或指示之前，将使用其所指向的内容更新属性值。如果属性值
 *                             is updated, @ref ble_gatts_hvx_params_t:：p_len由SoftDevice更新，以包含实际写入的字节数，否则将设置为0。
 *
 * @retval ：：NRF_SUCCESS成功将通知或指示排入队列进行传输，并可选地更新了属性值。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE以下一项或多项为真：
 *                                   -无效的连接状态
 *                                   -CCCD中未启用通知和/或指示
 *                                   -ATT_MTU交换正在进行
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：BLE_ERROR_INVALID_ATTR_HANDLE提供的属性句柄无效。只有应用程序直接添加的属性才可用于通知和指示。
 * @retval ：：BLE_ERROR_GATTS_INVALID_ATTR_TYPE提供的属性类型无效，只能通知和指示特征值。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND属性。
 * @retval ：：NRF_ERROR_FORBIDDEN连接的当前安全级别低于与此特性关联的CCCD的写入权限所需的安全级别。
 * @retval ：：NRF_ERROR_DATA_SIZE提供的数据大小无效。
 * @retval ：：NRF_ERROR_BUSY For@ref BLE_GATT_HVX_INDICATION过程已在进行中。等待@ref BLE_GATTS_EVT_HVC事件并重试。
 * @retval ：：BLE_ERROR_GATTS_SYS_ATTR_MISSING缺少系统属性，请使用@ref sd_BLE_GATTS_SYS_ATTR_set将其设置为已知值。
 * @retval ：：NRF_ERROR_RESOURCES排队的通知太多。
 *                               Wait for a @ref BLE_GATTS_EVT_HVN_TX_COMPLETE事件，然后重试。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTS_HVX, uint32_t, sd_ble_gatts_hvx(uint16_t conn_handle, ble_gatts_hvx_params_t const *p_hvx_params));

/**@brief 指示Service Changed属性值。
 *
 * @details 此调用将向连接的一个或多个对等端发送句柄值指示，以通知它们属性表布局已更改。一旦对等方确认该指示，将发出@ref BLE_GATTS_EVT_SC_CONFIRM事件。
 *
 * @note    适用于@ref sd_ble_gatts_hvx的一些限制也适用于此处。
 *
 * @events
 * @event{@ref BLE_GATTS_EVT_SC_CONFIRM，从对等方接收到属性表更改的确认。｝
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_SC_MSC}
 * @endmscs
 *
 * @param[in] conn_handle  连接手柄。
 * @param[in] start_handle 受影响属性控制柄范围的开始。
 * @param[in] end_handle   受影响的属性控制柄范围结束。
 *
 * @retval ：：NRF_SUCCESS成功将“服务更改”指示排队等待传输。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：初始化时未启用NRF_ERROR_NOT_SUPPORTED服务更改。请参见@ref sd_ble_cfg_set和@ref ble_gatts_cfg_service_changed_t。
 * @retval ：：NRF_ERROR_INVALID_STATE以下一项或多项为真：
 *                                   -无效的连接状态
 *                                   -CCCD中未启用通知和/或指示
 *                                   -ATT_MTU交换正在进行
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：BLE_ERROR_INVALID_ATTR_HANDLE提供的属性句柄无效，句柄必须在应用程序填充的范围内。
 * @retval ：：NRF_ERROR_BUSY过程已在进行中。
 * @retval ：：BLE_ERROR_GATTS_SYS_ATTR_MISSING缺少系统属性，请使用@ref sd_BLE_GATTS_SYS_ATTR_set将其设置为已知值。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTS_SERVICE_CHANGED, uint32_t, sd_ble_gatts_service_changed(uint16_t conn_handle, uint16_t start_handle, uint16_t end_handle));

/**@brief 响应读/写授权请求。
 *
 * @note 此调用只能用作对向应用程序发出的@ref BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST事件的响应。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_NOBUF_AUTH_MSC}
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_BUF_AUTH_MSC}
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_NOBUF_NOAUTH_MSC}
 * @mmsc{@ref BLE_GATTS_READ_REQ_AUTH_MSC}
 * @mmsc{@ref BLE_GATTS_WRITE_REQ_AUTH_MSC}
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_QUEUE_FULL_MSC}
 * @mmsc{@ref BLE_GATTS_QUEUED_WRITE_PEER_CANCEL_MSC}
 * @endmscs
 *
 * @param[in] conn_handle                 连接手柄。
 * @param[in] p_rw_authorize_reply_params 指向具有应用程序提供的属性的结构的指针。
 *
 * @note @使用此函数响应时，将忽略ref ble_gatts_authorize_params_t:：p_data
 *       to a @ref 如果@ref BLE_GATTS_AUTHORIZE_params_t:：update设置为0，则发生BLE_GATTS_AUTHORIZE_TYPE_READ事件。
 *
 * @retval ：：NRF_SUCCESS成功将响应排队到对等方，在写入操作的情况下，属性表已更新。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_BUSY堆栈正忙，请处理挂起的事件并重试。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效或没有挂起的授权请求。
 * @retval ：：NRF_ERROR_INVALID_PARAM授权操作无效，提供的句柄与请求的句柄不匹配，或者应用程序提供的要写入的数据无效。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTS_RW_AUTHORIZE_REPLY, uint32_t, sd_ble_gatts_rw_authorize_reply(uint16_t conn_handle, ble_gatts_rw_authorize_reply_params_t const *p_rw_authorize_reply_params));


/**@brief 更新持久系统属性信息。
 *
 * @details 向堆栈提供有关持久系统属性的信息，以前使用@ref sd_ble_gatts_sys_attr_get获取。此调用仅适用于活动连接，通常在与已知绑定设备建立连接后立即进行，通常作为对@ref BLE_GATTS_EVT_SYS_ATTR_MISSING的响应。
 *
 *          p_sysattrs可以直接指向应用程序存储的系统属性副本
 *          obtained using @ref sd_ble_gatts_sys_attr_get。如果指针为NULL，则初始化系统属性信息，假设应用程序没有此设备的任何先前保存的系统属性数据。
 *
 * @note 持久系统属性的状态在连接建立时重置，然后在其持续时间内被记住。
 *
 * @note 如果此调用返回的错误代码与@ref NRF_SUCCESS不同，则持久系统属性的存储可能只完成了一部分。这意味着属性表的状态未定义，应用程序应使用此同一调用提供一组新的属性，或重置SoftDevice以返回到已知状态。
 *
 * @note 当@ref BLE_GATTS_SYS_ATTR_FLAG_SYS_SRVCS与此函数一起使用时，仅修改系统服务中包含的系统属性。
 * @note 当@ref BLE_GATTS_SYS_ATTR_FLAG_USR_SRVCS与此函数一起使用时，仅修改用户服务中包含的系统属性。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_HVX_SYS_ATTRS_MISSING_MSC}
 * @mmsc{@ref BLE_GATTS_SYS_ATTRS_UNK_PEER_MSC}
 * @mmsc{@ref BLE_GATTS_SYS_ATTRS_BONDED_PEER_MSC}
 * @endmscs
 *
 * @param[in]  conn_handle        连接手柄。
 * @param[in]  p_sys_attr_data    指向提供给堆栈的系统属性的已保存副本的指针，或NULL。
 * @param[in]  len                p_sys_attr_data指向的数据大小，以八位字节为单位。
 * @param[in]  flags              可选附加标志，请参见@ref BLE_GATTS_SYS_ATTR_flags
 *
 * @retval ：：NRF_SUCCESS成功设置系统属性信息。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的标志无效。
 * @retval ：：NRF_ERROR_INVALID_DATA提供的数据无效，数据应与使用@ref sd_ble_gatts_sys_attr_get检索的数据完全相同。
 * @retval ：：NRF_ERROR_NO_MEM内存不足，无法完成操作。
 */
SVCALL(SD_BLE_GATTS_SYS_ATTR_SET, uint32_t, sd_ble_gatts_sys_attr_set(uint16_t conn_handle, uint8_t const *p_sys_attr_data, uint16_t len, uint32_t flags));


/**@brief 从堆栈中检索持久系统属性信息。
 *
 * @details 此调用用于检索有关应用程序在连接生存期内或连接终止后持久存储的值的信息。当与同一绑定设备建立新连接时，应使用@ref sd_ble_gatts_sys_attr_set恢复使用此函数检索的系统属性信息。如果在断开连接后检索，则应在建立新连接之前读取数据。在创建一个新的连接以允许此API调用引用它之前，上一个现已断开连接的连接句柄将保持有效。也可以使用属于活动连接的连接句柄，但应小心，因为在连接的生命周期内，对等方可以随时写入系统属性。
 *
 * @note 当@ref BLE_GATTS_SYS_ATTR_FLAG_SYS_SRVCS与此函数一起使用时，将仅返回系统服务中包含的系统属性。
 * @note 当@ref BLE_GATTS_SYS_ATTR_FLAG_USR_SRVCS与此函数一起使用时，将仅返回用户服务中包含的系统属性。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_SYS_ATTRS_BONDED_PEER_MSC}
 * @endmscs
 *
 * @param[in]     conn_handle       最近终止的连接的连接句柄。
 * @param[out]    p_sys_attr_data   指向一个缓冲区的指针，将在该缓冲区中填充有关系统属性的更新信息。描述了数据的格式
 *                                  in @ref BLE_GATTS_SYS_ATTRS_FORMAT。可以提供NULL来获得数据的长度。
 * @param[in,out] p_len             如果p_sys_attr_data不为NULL，则应用程序缓冲区的大小。无条件更新为系统属性数据的实际长度。
 * @param[in]     flags             可选附加标志，请参见@ref BLE_GATTS_SYS_ATTR_flags
 *
 * @retval ：：NRF_SUCCESS成功检索到系统属性信息。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的标志无效。
 * @retval ：：NRF_ERROR_DATA_SIZE系统属性信息不适合提供的缓冲区。
 * @retval ：：NRF_ERROR_NOT_FOUND未找到系统属性。
 */
SVCALL(SD_BLE_GATTS_SYS_ATTR_GET, uint32_t, sd_ble_gatts_sys_attr_get(uint16_t conn_handle, uint8_t *p_sys_attr_data, uint16_t *p_len, uint32_t flags));


/**@brief 检索第一个有效的用户属性句柄。
 *
 * @param[out] p_handle   指向将存储句柄的整数的指针。
 *
 * @retval ：：NRF_SUCCESS成功检索句柄。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 */
SVCALL(SD_BLE_GATTS_INITIAL_USER_HANDLE_GET, uint32_t, sd_ble_gatts_initial_user_handle_get(uint16_t *p_handle));

/**@brief 检索属性UUID和/或元数据。
 *
 * @param[in]  handle 属性句柄
 * @param[out] p_uuid 属性的UUID。使用NULL忽略此字段。
 * @param[out] p_md 属性的元数据。使用NULL忽略此字段。
 *
 * @retval ：：NRF_SUCCESS成功检索到属性元数据，
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。当@cp_uuid和@cp_md都为NULL时返回。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND属性。
 */
SVCALL(SD_BLE_GATTS_ATTR_GET, uint32_t, sd_ble_gatts_attr_get(uint16_t handle, ble_uuid_t * p_uuid, ble_gatts_attr_md_t * p_md));

/**@brief 通过向客户端发送exchange MTU响应来回复ATT_MTU交换请求。
 *
 * @details 此函数仅用于回复@ref BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST事件。
 *
 * @details SoftDevice将ATT_MTU设置为以下最小值：
 *          - The Client RX MTU value from @ref BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST，和
 *          -服务器RX MTU值。
 *
 *          但是，SoftDevice从不将ATT_MTU设置为低于@ref BLE_GATT_ATT_MTU_DEFAULT。
 *
 * @mscs
 * @mmsc{@ref BLE_GATTS_MTU_EXCHANGE}
 * @endmscs
 *
 * @param[in] conn_handle    标识要对其执行此过程的连接的连接句柄。
 * @param[in] server_rx_mtu  服务器RX MTU大小。
 *                           -最小值为@ref BLE_GATT_ATT_MTU_DEFAULT。
 *                           - The maximum value is @ref 用于此连接的连接配置中的ble_gatt_conn_cfg_t:：att_mtu。
 *                           - The value must be equal to Client RX MTU size given in @ref sd_ble_gattc_exchange_mtu_request，如果ATT_mtu交换已经在另一方向上执行。
 *
 * @retval ：：NRF_SUCCESS已成功向客户端发送响应。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE连接状态无效或没有ATT_MTU交换请求挂起。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的服务器RX MTU大小无效。
 * @retval ：：NRF_ERROR_TIMEOUT GATT过程超时。不重新建立连接，就不能执行新的GATT程序。
 */
SVCALL(SD_BLE_GATTS_EXCHANGE_MTU_REPLY, uint32_t, sd_ble_gatts_exchange_mtu_reply(uint16_t conn_handle, uint16_t server_rx_mtu));
/** @} */

#ifdef __cplusplus
}
#endif
#endif // BLE_GATTS_H__

/**
  @}
*/

