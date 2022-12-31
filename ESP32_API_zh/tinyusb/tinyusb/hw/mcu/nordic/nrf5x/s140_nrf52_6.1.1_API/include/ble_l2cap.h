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
  @添加组BLE_L2CAP逻辑链路控制和适配协议（L2CAP）@{
  @L2CAP接口的简要定义和原型。
 */

#ifndef BLE_L2CAP_H__
#define BLE_L2CAP_H__

#include <stdint.h>
#include "nrf_svc.h"
#include "nrf_error.h"
#include "ble_ranges.h"
#include "ble_types.h"
#include "ble_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@addtogroup BLE_L2CAP_术语@{
 * @details
 *
 * L2CAP SDU
 * -应用程序可以向对等方发送/从对等方接收的数据单元。
 *
 * L2CAP PDU
 * -在本地和远程L2CAP实体之间交换的数据单元。它由L2CAP协议控制信息和有效载荷字段组成。有效载荷字段可以包含L2CAP SDU或L2CAP SD单元的一部分。
 *
 * L2CAP MTU
 * -L2CAP SDU的最大长度。
 *
 * L2CAP MPS
 * -L2CAP PDU负载字段的最大长度。
 *
 * 信用
 * -一个值，指示信用的接收方可以向对等方发送的L2CAP PDU的数量。
 * @} */

/**@addtogroup BLE_L2CAP_ENUMERATIONS枚举
 * @{ */

/**@brief L2CAP API SVC编号。*/
enum BLE_L2CAP_SVCS
{
  SD_BLE_L2CAP_CH_SETUP        = BLE_L2CAP_SVC_BASE + 0, /**<设置L2CAP通道。*/
  SD_BLE_L2CAP_CH_RELEASE      = BLE_L2CAP_SVC_BASE + 1, /**<释放L2CAP通道。*/
  SD_BLE_L2CAP_CH_RX           = BLE_L2CAP_SVC_BASE + 2, /**<在L2CAP信道上接收SDU。*/
  SD_BLE_L2CAP_CH_TX           = BLE_L2CAP_SVC_BASE + 3, /**<在L2CAP信道上传输SDU。*/
  SD_BLE_L2CAP_CH_FLOW_CONTROL = BLE_L2CAP_SVC_BASE + 4, /**<高级SDU接收流控制。*/
};

/**@brief L2CAP事件ID。*/
enum BLE_L2CAP_EVTS
{
  BLE_L2CAP_EVT_CH_SETUP_REQUEST    = BLE_L2CAP_EVT_BASE + 0,    /**＜L2CAP信道设置请求事件。\n请参见@ref ble_l2cap_evt_ch_setup_request_t。*/
  BLE_L2CAP_EVT_CH_SETUP_REFUSED    = BLE_L2CAP_EVT_BASE + 1,    /**＜L2CAP频道设置被拒绝事件。\n请参见@ref ble_l2cap_evt_ch_setup_refused_t。*/
  BLE_L2CAP_EVT_CH_SETUP            = BLE_L2CAP_EVT_BASE + 2,    /**<L2CAP通道设置完成事件。\n请参见@ref ble_l2cap_evt_ch_setup_t。*/
  BLE_L2CAP_EVT_CH_RELEASED         = BLE_L2CAP_EVT_BASE + 3,    /**<L2CAP通道释放事件。\n不适用其他事件结构。*/
  BLE_L2CAP_EVT_CH_SDU_BUF_RELEASED = BLE_L2CAP_EVT_BASE + 4,    /**＜L2CAP通道SDU数据缓冲区释放事件。\n请参见@ref ble_l2cap_evt_ch_sdu_buf_released_t。*/
  BLE_L2CAP_EVT_CH_CREDIT           = BLE_L2CAP_EVT_BASE + 5,    /**<收到L2CAP信道信用。\n请参见@ref ble_l2cap_evt_ch_credit_t。*/
  BLE_L2CAP_EVT_CH_RX               = BLE_L2CAP_EVT_BASE + 6,    /**<接收到L2CAP信道SDU。\n参见@ref ble_l2cap_evt_ch_rx_t。*/
  BLE_L2CAP_EVT_CH_TX               = BLE_L2CAP_EVT_BASE + 7,   /**<传输了L2CAP信道SDU。\n请参见@ref ble_l2cap_evt_ch_tx_t。*/
};

/** @} */

/**@addtogroup BLE_L2CAP_DEFINES定义
 * @{ */

/**@brief 每个连接的最大L2CAP通道数。*/
#define BLE_L2CAP_CH_COUNT_MAX    (64)

/**@brief 最小L2CAP MTU（字节）。*/
#define BLE_L2CAP_MTU_MIN         (23)

/**@brief 最小L2CAP MPS（字节）。*/
#define BLE_L2CAP_MPS_MIN         (23)

/**@brief CID无效。*/
#define BLE_L2CAP_CID_INVALID     (0x0000)

/**@brief @ref sd_ble_l2cap_ch_flow_control的默认点数。*/
#define BLE_L2CAP_CREDITS_DEFAULT (1)

/**@defgroup BLE_L2CAP_CH_SETUP_REFUSED_SRCS L2CAP通道设置拒绝源
 * @{ */
#define BLE_L2CAP_CH_SETUP_REFUSED_SRC_LOCAL            (0x01)    /**<本地。*/
#define BLE_L2CAP_CH_SETUP_REFUSED_SRC_REMOTE           (0x02)    /**<远程。*/
 /** @}  */

 /** @defgroup BLE_L2CAP_CH_STATUS_CODES L2CAP信道状态代码
 * @{ */
#define BLE_L2CAP_CH_STATUS_CODE_SUCCESS                (0x0000)  /**<成功。*/
#define BLE_L2CAP_CH_STATUS_CODE_LE_PSM_NOT_SUPPORTED   (0x0002)  /**<LE_PSM不受支持。*/
#define BLE_L2CAP_CH_STATUS_CODE_NO_RESOURCES           (0x0004)  /**<无可用资源。*/
#define BLE_L2CAP_CH_STATUS_CODE_INSUFF_AUTHENTICATION  (0x0005)  /**<身份验证不足。*/
#define BLE_L2CAP_CH_STATUS_CODE_INSUFF_AUTHORIZATION   (0x0006)  /**<授权不足。*/
#define BLE_L2CAP_CH_STATUS_CODE_INSUFF_ENC_KEY_SIZE    (0x0007)  /**<加密密钥大小不足。*/
#define BLE_L2CAP_CH_STATUS_CODE_INSUFF_ENC             (0x0008)  /**<加密不足。*/
#define BLE_L2CAP_CH_STATUS_CODE_INVALID_SCID           (0x0009)  /**<源CID无效。*/
#define BLE_L2CAP_CH_STATUS_CODE_SCID_ALLOCATED         (0x000A)  /**<源CID已分配。*/
#define BLE_L2CAP_CH_STATUS_CODE_UNACCEPTABLE_PARAMS    (0x000B)  /**<不可接受的参数。*/
#define BLE_L2CAP_CH_STATUS_CODE_NOT_UNDERSTOOD         (0x8000)  /**<接收到命令拒绝而不是基于LE信用的连接响应。*/
#define BLE_L2CAP_CH_STATUS_CODE_TIMEOUT                (0xC000)  /**<操作超时。*/
/** @} */

/** @} */

/**@addtogroup BLE_L2CAP_STRUCTURES结构
 * @{ */

/**
 * @brief BLE L2CAP连接配置参数，用@ref sd_BLE_cfg_set设置。
 *
 * @note  这些参数是按连接设置的，因此在此连接上创建的所有L2CAP通道都将具有相同的参数。
 *
 * @retval ：：NRF_ERROR_INVALID_PARAM以下一项或多项为真：
 *                                    -rx_mps小于@ref BLE_L2CAP_mps_MIN。
 *                                    -tx_mps小于@ref BLE_L2CAP_mps_MIN。
 *                                    -ch_count大于@ref BLE_L2CAP_ch_count_MAX。
 * @retval ：：NRF_ERROR_NO_MEM rx_mps或tx_mps设置过高。
 */
typedef struct
{
  uint16_t    rx_mps;        /**<使用此配置的连接上，L2CAP应能够在L2CAP信道上接收的最大L2CAP PDU有效载荷大小（以字节为单位）。最小值为@ref BLE_L2CAP_MPS_MIN。*/
  uint16_t    tx_mps;        /**<使用此配置的连接上，L2CAP应能够在L2CAP信道上传输的最大L2CAP PDU有效载荷大小（以字节为单位）。最小值为@ref BLE_L2CAP_MPS_MIN。*/
  uint8_t     rx_queue_size; /**<每个L2CAP信道可排队接收的SDU数据缓冲区数。最小值为1。*/
  uint8_t     tx_queue_size; /**<每个L2CAP信道可排队传输的SDU数据缓冲区数。最小值为1。*/
  uint8_t     ch_count;      /**< 应用程序可以使用此配置为每个连接创建的L2CAP通道数。默认值为零，最大值为@ref BLE_L2CAP_CH_COUNT_MAX。
                                  @注意，如果此参数设置为零，则会忽略@ref blel2cap_conncfgt中的所有其他参数。*/
} ble_l2cap_conn_cfg_t;

/**@brief L2CAP信道RX参数。*/
typedef struct
{
  uint16_t    rx_mtu;        /**<L2CAP应能够在此L2CAP信道上接收的最大L2CAP SDU大小（以字节为单位）。-必须等于或大于@ref BLE_L2CAP_MTU_MIN。*/
  uint16_t    rx_mps;        /**< L2CAP应能够在此L2CAP信道上接收的最大L2CAP PDU有效载荷大小（以字节为单位）。
                                  -必须等于或大于@ref BLE_L2CAP_MPS_MIN。-必须等于或小于@ref ble_l2cap_conn_cfg_t:：rx_mps。*/
  ble_data_t  sdu_buf;       /**< 用于接收的SDU数据缓冲器。
                                  -如果@ref ble_data_t:：p_data为非NULL，则向对等方发出初始信用。
                                  -如果@ref ble_data_t:：p_data为NULL，则不会向对等方发出初始信用。*/
} ble_l2cap_ch_rx_params_t;

/**@brief L2CAP信道设置参数。*/
typedef struct
{
  ble_l2cap_ch_rx_params_t      rx_params;  /**<L2CAP信道RX参数。*/
  uint16_t                      le_psm;     /**<LE协议/服务复用器。请求设置L2CAP信道时使用，否则忽略。*/
  uint16_t                      status;     /**<状态代码，请参阅@ref BLE_L2CAP_CH_Status_CODES。在回复L2CAP信道的设置请求时使用，否则忽略。*/
} ble_l2cap_ch_setup_params_t;

/**@brief L2CAP信道TX参数。*/
typedef struct
{
  uint16_t    tx_mtu;        /**<L2CAP能够在此L2CAP信道上传输的最大L2CAP SDU大小（以字节为单位）。*/
  uint16_t    peer_mps;      /**<对等方能够在此L2CAP信道上接收的最大L2CAP PDU负载大小（以字节为单位）。*/
  uint16_t    tx_mps;        /**<L2CAP能够在此L2CAP信道上传输的最大L2CAP PDU负载大小（以字节为单位）。这是有效的tx_mps，由SoftDevice选择为MIN（@ref ble_l2cap_ch_tx_rams_t:：peer_mps，@ref ble_l2cap_conn_cfg_t:：tx_mps）*/
  uint16_t    credits;       /**<同行给予的初始学分。*/
} ble_l2cap_ch_tx_params_t;

/**@brief L2CAP通道设置请求事件。*/
typedef struct
{
  ble_l2cap_ch_tx_params_t  tx_params;  /**<L2CAP信道TX参数。*/
  uint16_t                  le_psm;     /**<LE协议/服务复用器。*/
} ble_l2cap_evt_ch_setup_request_t;

/**@brief L2CAP通道设置被拒绝事件。*/
typedef struct
{
  uint8_t  source;           /**<来源，请参见@ref BLE_L2CAP_CH_SETUP_REFUSED_SRCS*/
  uint16_t status;           /**<状态代码，请参见@ref BLE_L2CAP_CH_Status_CODES*/
} ble_l2cap_evt_ch_setup_refused_t;

/**@brief L2CAP通道设置完成事件。*/
typedef struct
{
  ble_l2cap_ch_tx_params_t tx_params;  /**<L2CAP信道TX参数。*/
} ble_l2cap_evt_ch_setup_t;

/**@brief L2CAP通道SDU数据缓冲区释放事件。*/
typedef struct
{
  ble_data_t  sdu_buf;       /**<返回的接收或传输SDU数据缓冲区。SoftDevice返回应用程序提供的SDU数据缓冲区，这些缓冲区之前尚未通过@ref BLE_L2CAP_EVT_CH_RX或@ref BLE-L2CAP_EVT _CH_TX事件返回。*/
} ble_l2cap_evt_ch_sdu_buf_released_t;

/**@brief L2CAP信道信用收到事件。*/
typedef struct
{
  uint16_t  credits;         /**<同行给予的额外积分。*/
} ble_l2cap_evt_ch_credit_t;

/**@brief L2CAP信道接收到SDU事件。*/
typedef struct
{
  uint16_t    sdu_len;       /**<SDU总长度（字节）。*/
  ble_data_t  sdu_buf;       /**< SDU数据缓冲区。
                                  @注意：如果缓冲区中没有足够的空间（sdu_buf.len＜sdu_len），则SoftDevice将默默丢弃sdu的其余部分。*/
} ble_l2cap_evt_ch_rx_t;

/**@brief L2CAP信道传输了SDU事件。*/
typedef struct
{
  ble_data_t  sdu_buf;       /**<SDU数据缓冲区。*/
} ble_l2cap_evt_ch_tx_t;

/**@brief L2CAP事件结构。*/
typedef struct
{
  uint16_t conn_handle;                                     /**<发生事件的连接句柄。*/
  uint16_t local_cid;                                       /**<L2CAP信道的本地信道ID，或@ref BLE_L2CAP_CID_INVALID（如果不存在）。*/
  union
  {
    ble_l2cap_evt_ch_setup_request_t    ch_setup_request;   /**<L2CAP信道设置请求事件参数。*/
    ble_l2cap_evt_ch_setup_refused_t    ch_setup_refused;   /**<L2CAP信道设置拒绝事件参数。*/
    ble_l2cap_evt_ch_setup_t            ch_setup;           /**<L2CAP通道设置完成事件参数。*/
    ble_l2cap_evt_ch_sdu_buf_released_t ch_sdu_buf_released;/**<L2CAP通道SDU数据缓冲区释放事件参数。*/
    ble_l2cap_evt_ch_credit_t           credit;             /**<L2CAP信道信用接收事件参数。*/
    ble_l2cap_evt_ch_rx_t               rx;                 /**<L2CAP信道SDU接收事件参数。*/
    ble_l2cap_evt_ch_tx_t               tx;                 /**<L2CAP信道SDU传输的事件参数。*/
  } params;                                                 /**<事件参数。*/
} ble_l2cap_evt_t;

/** @} */

/**@addtogroup BLE_L2CAP_FUNCTIONS函数
 * @{ */

/**@brief 设置L2CAP通道。
 *
 * @details 此功能用于：
 *          -请求建立L2CAP信道：向对等方发送基于LE信用的连接请求包。
 *          -回复L2CAP信道的设置请求（如果是响应
 *            @ref BLE_L2CAP_EVT_CH_SETUP_REQUEST事件）：向对等端发送基于LE信用的连接响应包。
 *
 * @note    调用此函数将要求应用程序保持SDU数据缓冲区活动，直到在@ref BLE_L2CAP_EVT_CH_RX或
 *          @ref BLE_L2CAP_EVT_CH_SDU_BUF_RELEASED事件。
 *
 * @events
 * @event{@ref BLE_L2CAP_EVT_CH_SETUP，安装成功。}
 * @event{@ref BLE_L2CAP_EVT_CH_SETUP_REFUSED，安装失败。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_L2CAP_CH_SETUP_MSC}
 * @endmscs
 *
 * @param[in] conn_handle      连接手柄。
 * @param[in,out] p_local_cid  指向包含L2CAP信道的本地信道ID的uint16_t的指针：
 *                             - As input: @ref 请求设置L2CAP信道时的BLE_L2CAP_CID_INVALID，或回复L2CAP信道设置请求时@ref BLE_L2CAP-EVT_CH_setup_REQUEST事件中提供的local_CID。
 *                             -作为输出：此通道的local_cid。
 * @param[in] p_params         L2CAP信道参数。
 *
 * @retval ：：NRF_SUCCESS成功排队请求或响应以进行传输。
 * @retval ：：NRF_ERROR_BUSY堆栈正忙，请处理挂起的事件并重试。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_PARAM提供的参数无效。
 * @retval ：：NRF_ERROR_INVALID_LENGTH提供的rx_mps高于此链路上配置的rx_mp。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效（L2CAP通道已设置）。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND CID。
 * @retval ：：NRF_ERROR_RESOURCES已达到可用L2CAP通道的限制，请参阅@ref ble_L2CAP_conn_cfg_t:：ch_count。
 */
SVCALL(SD_BLE_L2CAP_CH_SETUP, uint32_t, sd_ble_l2cap_ch_setup(uint16_t conn_handle, uint16_t *p_local_cid, ble_l2cap_ch_setup_params_t const *p_params));

/**@brief 释放L2CAP通道。
 *
 * @details 这将向对等端发送断开请求数据包。
 *
 * @events
 * @event{@ref BLE_L2CAP_EVT_CH_RELEASED，发布完成。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_L2CAP_CH_RELEASE_MSC}
 * @endmscs
 *
 * @param[in] conn_handle   连接手柄。
 * @param[in] local_cid     L2CAP信道的本地信道ID。
 *
 * @retval ：：NRF_SUCCESS成功排队请求传输。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效（L2CAP通道的安装或释放正在进行中）。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND CID。
 */
SVCALL(SD_BLE_L2CAP_CH_RELEASE, uint32_t, sd_ble_l2cap_ch_release(uint16_t conn_handle, uint16_t local_cid));

/**@brief 在L2CAP信道上接收SDU。
 *
 * @details 这可以使用LE流控制信用分组向对等体发出附加信用。
 *
 * @note    调用此函数将要求应用程序保持内存指向
 *          @ref ble_data_t:：p_data活动，直到在@ref ble_L2CAP_EVT_CH_RX中返回SDU数据缓冲区
 *          or @ref BLE_L2CAP_EVT_CH_SDU_BUF_RELEASED事件。
 *
 * @note    SoftDevice可以排队到@ref ble_l2cap_conn_cfg_t:：rx_queue_size SDU数据缓冲区，以便每个l2cap信道接收。
 *
 * @events
 * @event{@ref BLE_L2CAP_EVT_CH_RX，收到SDU。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_L2CAP_CH_RX_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] local_cid   L2CAP信道的本地信道ID。
 * @param[in] p_sdu_buf   指向SDU数据缓冲区的指针。
 *
 * @retval ：：接受NRF_SUCCESS缓冲区。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效（L2CAP通道的安装或释放正在进行中）。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND CID。
 * @retval ：：NRF_ERROR_RESOURCES提供的SDU数据缓冲区太多。等待@ref BLE_L2CAP_EVT_CH_RX事件并重试。
 */
SVCALL(SD_BLE_L2CAP_CH_RX, uint32_t, sd_ble_l2cap_ch_rx(uint16_t conn_handle, uint16_t local_cid, ble_data_t const *p_sdu_buf));

/**@brief 在L2CAP信道上发送SDU。
 *
 * @note    调用此函数将要求应用程序保持内存指向
 *          @ref ble_data_t:：p_data活动，直到在@ref ble_L2CAP_EVT_CH_TX中返回SDU数据缓冲区
 *          or @ref BLE_L2CAP_EVT_CH_SDU_BUF_RELEASED事件。
 *
 * @note    SoftDevice可以排队到@ref ble_l2cap_conn_cfg_t:：tx_queue_size SDU，以便每个l2cap信道进行传输。
 *
 * @note    应用程序可以通过以下程序跟踪可用的传输信用：
 *          -将对等方提供的初始积分存储在变量中。（初始积分在@ref BLE_L2CAP_EVT_CH_SETUP事件中提供。）
 *          -将存储当前可用信用的变量递减
 *            ceiling((@ref ble_data_t:：len+2）/tx_mps）当对此函数的调用返回时
 *            @ref NRF_成功。（tx_mps在@ref BLE_L2CAP_EVT_CH_SETUP事件中提供。）
 *          -将存储当前可用信用的变量增加@ref BLE_L2CAP_EVT_CH_CREDIT事件中对等方提供的额外信用。
 *
 * @events
 * @event{@ref BLE_L2CAP_EVT_CH_TX，发送SDU。}
 * @endevents
 *
 * @mscs
 * @mmsc{@ref BLE_L2CAP_CH_TX_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] local_cid   L2CAP信道的本地信道ID。
 * @param[in] p_sdu_buf   指向SDU数据缓冲区的指针。
 *
 * @retval ：：NRF_SUCCESS已成功将L2CAP SDU排队等待传输。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效（L2CAP通道的安装或释放正在进行中）。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND CID。
 * @retval ：：NRF_ERROR_DATA_SIZE提供的SDU长度无效，不能大于
 *                                          @ref @ref ble_l2cap_EVT_ch_SETUP事件中提供的ble_l2cap_ch_tx_rams_t:：tx_mtu。
 * @retval ：：NRF_ERROR_RESOURCES排队等待传输的SDU太多。等待@ref BLE_L2CAP_EVT_CH_TX事件并重试。
 */
SVCALL(SD_BLE_L2CAP_CH_TX, uint32_t, sd_ble_l2cap_ch_tx(uint16_t conn_handle, uint16_t local_cid, ble_data_t const *p_sdu_buf));

/**@brief 高级SDU接收流控制。
 *
 * @details 调整SoftDevice向对等方发放积分的方式。这可以使用LE流控制信用分组向对等体发出附加信用。
 *
 * @mscs
 * @mmsc{@ref BLE_L2CAP_CH_FLOW_CONTROL_MSC}
 * @endmscs
 *
 * @param[in] conn_handle 连接手柄。
 * @param[in] local_cid   L2CAP信道的本地信道ID或@ref BLE_L2CAP_CID_INVALID设置将用于新创建信道的值。
 * @param[in] credits     SoftDevice每次开始使用新的接收缓冲区时将确保对等方拥有的信用数。
 *                        - @ref BLE_L2CAP_CREDITS_DEFAULT是如果未调用此函数，SoftDevice将使用的默认值。
 *                        -如果设置为零，SoftDevice将停止为应用程序提供或已提供的新接收缓冲区发放信用。将允许当前正在进行的SDU接收完成。
 * @param[out] p_credits  NULL或指向uint16_t的指针。如果提供了有效指针，则SoftDevice将使用对等方可用的信用数写入该指针。当credits参数设置为0时，如果SoftDevice写入的值为0，则在credits>0时再次调用此函数提供更多credits之前，对等方将无法发送更多数据。当local_cid设置为
 *                        @ref BLE_L2CAP_CID_INVALID.
 *
 * @note 应用程序应注意设置高于默认值的信用数。在这种情况下，应用程序必须确保SoftDevice始终具有接收缓冲区
 *       available (see @ref sd_ble_l2cap_ch_rx）。如果SoftDevice没有这样的缓冲区可用，则可以在链路层上对分组进行NACK，并且可以暂停连接句柄上的所有蓝牙通信，直到SoftDevice再次具有可用的接收缓冲区。即使应用程序使用此调用将信用设置回默认值或零，这也适用。
 *
 * @retval ：：接受NRF_SUCCESS流量控制参数。
 * @retval ：：NRF_ERROR_INVALID_ADDR提供的指针无效。
 * @retval ：：BLE_ERROR_INVALID_CONN_HANDLE连接句柄无效。
 * @retval ：：NRF_ERROR_INVALID_STATE执行操作的状态无效（L2CAP通道的安装或释放正在进行中）。
 * @retval ：：未找到NRF_ERROR_NOT_FOUND CID。
 */
SVCALL(SD_BLE_L2CAP_CH_FLOW_CONTROL, uint32_t, sd_ble_l2cap_ch_flow_control(uint16_t conn_handle, uint16_t local_cid, uint16_t credits, uint16_t *p_credits));

/** @} */

#ifdef __cplusplus
}
#endif
#endif // BLE_L2CAP_H__

/**
  @}
*/

