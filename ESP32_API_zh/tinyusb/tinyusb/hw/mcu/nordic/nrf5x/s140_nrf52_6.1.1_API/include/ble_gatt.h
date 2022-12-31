/*
 * 版权所有（c）2013-2018，Nordic Semiconductor ASA保留所有权利。
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
  @addtogroup BLE_GATT通用属性配置文件（GATT）通用@{
  @GATT接口的简要通用定义和原型。
 */

#ifndef BLE_GATT_H__
#define BLE_GATT_H__

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

/** @addtogroup BLE_GATT_DEFINES定义
 * @{ */

/** @brief 默认ATT MTU（字节）。*/
#define BLE_GATT_ATT_MTU_DEFAULT          23

/**@brief 属性句柄无效。*/
#define BLE_GATT_HANDLE_INVALID            0x0000

/**@brief 第一属性句柄。*/
#define BLE_GATT_HANDLE_START              0x0001

/**@brief 最后一个属性句柄。*/
#define BLE_GATT_HANDLE_END                0xFFFF

/** @defgroup BLE_GATT_TIMEOUT_SOURCES GATT超时源
 * @{ */
#define BLE_GATT_TIMEOUT_SRC_PROTOCOL      0x00  /**<ATT协议超时。*/
/** @} */

/** @defgroup BLE_GATT_WRITE_OPS GATT写入操作
 * @{ */
#define BLE_GATT_OP_INVALID                0x00  /**<无效操作。*/
#define BLE_GATT_OP_WRITE_REQ              0x01  /**<写入请求。*/
#define BLE_GATT_OP_WRITE_CMD              0x02  /**<写入命令。*/
#define BLE_GATT_OP_SIGN_WRITE_CMD         0x03  /**<签名写入命令。*/
#define BLE_GATT_OP_PREP_WRITE_REQ         0x04  /**<准备写入请求。*/
#define BLE_GATT_OP_EXEC_WRITE_REQ         0x05  /**<执行写入请求。*/
/** @} */

/** @defgroup BLE_GATT_EXEC_WRITE_FLAGS GATT执行写入标志
 * @{ */
#define BLE_GATT_EXEC_WRITE_FLAG_PREPARED_CANCEL 0x00   /**<取消准备的写入。*/
#define BLE_GATT_EXEC_WRITE_FLAG_PREPARED_WRITE  0x01   /**<执行准备好的写入。*/
/** @} */

/** @defgroup BLE_GATT_HVX_TYPES GATT句柄值操作
 * @{ */
#define BLE_GATT_HVX_INVALID               0x00  /**<无效操作。*/
#define BLE_GATT_HVX_NOTIFICATION          0x01  /**<句柄值通知。*/
#define BLE_GATT_HVX_INDICATION            0x02  /**<手柄值指示。*/
/** @} */

/** @defgroup BLE_GATT_STATUS_CODES GATT状态代码
 * @{ */
#define BLE_GATT_STATUS_SUCCESS                           0x0000  /**<成功。*/
#define BLE_GATT_STATUS_UNKNOWN                           0x0001  /**<未知或不适用状态。*/
#define BLE_GATT_STATUS_ATTERR_INVALID                    0x0100  /**<ATT错误：错误代码无效。*/
#define BLE_GATT_STATUS_ATTERR_INVALID_HANDLE             0x0101  /**<ATT错误：属性句柄无效。*/
#define BLE_GATT_STATUS_ATTERR_READ_NOT_PERMITTED         0x0102  /**<ATT错误：不允许读取。*/
#define BLE_GATT_STATUS_ATTERR_WRITE_NOT_PERMITTED        0x0103  /**<ATT错误：不允许写入。*/
#define BLE_GATT_STATUS_ATTERR_INVALID_PDU                0x0104  /**<ATT错误：在ATT中用作无效PDU。*/
#define BLE_GATT_STATUS_ATTERR_INSUF_AUTHENTICATION       0x0105  /**<ATT错误：需要经过身份验证的链接。*/
#define BLE_GATT_STATUS_ATTERR_REQUEST_NOT_SUPPORTED      0x0106  /**<ATT错误：在ATT中用作不支持的请求。*/
#define BLE_GATT_STATUS_ATTERR_INVALID_OFFSET             0x0107  /**<ATT错误：指定的偏移超过了属性的结尾。*/
#define BLE_GATT_STATUS_ATTERR_INSUF_AUTHORIZATION        0x0108  /**<ATT错误：在ATT中用作授权不足。*/
#define BLE_GATT_STATUS_ATTERR_PREPARE_QUEUE_FULL         0x0109  /**<ATT错误：在ATT中用作准备队列已满。*/
#define BLE_GATT_STATUS_ATTERR_ATTRIBUTE_NOT_FOUND        0x010A  /**<ATT错误：在ATT中使用，因为找不到属性。*/
#define BLE_GATT_STATUS_ATTERR_ATTRIBUTE_NOT_LONG         0x010B  /**<ATT错误：无法使用读/写blob请求读取或写入属性。*/
#define BLE_GATT_STATUS_ATTERR_INSUF_ENC_KEY_SIZE         0x010C  /**<ATT错误：使用的加密密钥大小不足。*/
#define BLE_GATT_STATUS_ATTERR_INVALID_ATT_VAL_LENGTH     0x010D  /**<ATT错误：值大小无效。*/
#define BLE_GATT_STATUS_ATTERR_UNLIKELY_ERROR             0x010E  /**<ATT错误：非常不可能的错误。*/
#define BLE_GATT_STATUS_ATTERR_INSUF_ENCRYPTION           0x010F  /**<ATT错误：需要加密链接。*/
#define BLE_GATT_STATUS_ATTERR_UNSUPPORTED_GROUP_TYPE     0x0110  /**<ATT错误：属性类型不是受支持的分组属性。*/
#define BLE_GATT_STATUS_ATTERR_INSUF_RESOURCES            0x0111  /**<ATT错误：需要加密链接。*/
#define BLE_GATT_STATUS_ATTERR_RFU_RANGE1_BEGIN           0x0112  /**<ATT错误：保留供将来使用范围#1开始。*/
#define BLE_GATT_STATUS_ATTERR_RFU_RANGE1_END             0x017F  /**<ATT错误：保留供将来使用范围#1结束。*/
#define BLE_GATT_STATUS_ATTERR_APP_BEGIN                  0x0180  /**<ATT错误：应用程序范围开始。*/
#define BLE_GATT_STATUS_ATTERR_APP_END                    0x019F  /**<ATT错误：应用程序范围结束。*/
#define BLE_GATT_STATUS_ATTERR_RFU_RANGE2_BEGIN           0x01A0  /**<ATT错误：保留供将来使用范围#2开始。*/
#define BLE_GATT_STATUS_ATTERR_RFU_RANGE2_END             0x01DF  /**<ATT错误：保留供将来使用范围#2结束。*/
#define BLE_GATT_STATUS_ATTERR_RFU_RANGE3_BEGIN           0x01E0  /**<ATT错误：保留供将来使用范围#3开始。*/
#define BLE_GATT_STATUS_ATTERR_RFU_RANGE3_END             0x01FC  /**<ATT错误：保留供将来使用范围#3结束。*/
#define BLE_GATT_STATUS_ATTERR_CPS_WRITE_REQ_REJECTED     0x01FC  /**<ATT公共配置文件和服务错误：写入请求被拒绝。*/
#define BLE_GATT_STATUS_ATTERR_CPS_CCCD_CONFIG_ERROR      0x01FD  /**<ATT公共配置文件和服务错误：客户端特征配置描述符配置不正确。*/
#define BLE_GATT_STATUS_ATTERR_CPS_PROC_ALR_IN_PROG       0x01FE  /**<ATT常见配置文件和服务错误：程序已在进行中。*/
#define BLE_GATT_STATUS_ATTERR_CPS_OUT_OF_RANGE           0x01FF  /**<ATT公共配置文件和服务错误：超出范围。*/
/** @} */


/** @defgroup BLE_GATT_CPF_FORMATS特征表示格式
 *  @note 在找到http://developer.bluetooth.org/gatt/descriptors/Pages/DescriptorViewer.aspx?u=org.bluetooth.descriptor.gatt.characteristic_presentation_format.xml
 * @{ */
#define BLE_GATT_CPF_FORMAT_RFU                 0x00 /**<保留以备将来使用。*/
#define BLE_GATT_CPF_FORMAT_BOOLEAN             0x01 /**<布尔值。*/
#define BLE_GATT_CPF_FORMAT_2BIT                0x02 /**<无符号2位整数。*/
#define BLE_GATT_CPF_FORMAT_NIBBLE              0x03 /**<无符号4位整数。*/
#define BLE_GATT_CPF_FORMAT_UINT8               0x04 /**<无符号8位整数。*/
#define BLE_GATT_CPF_FORMAT_UINT12              0x05 /**<无符号12位整数。*/
#define BLE_GATT_CPF_FORMAT_UINT16              0x06 /**<无符号16位整数。*/
#define BLE_GATT_CPF_FORMAT_UINT24              0x07 /**<无符号24位整数。*/
#define BLE_GATT_CPF_FORMAT_UINT32              0x08 /**<无符号32位整数。*/
#define BLE_GATT_CPF_FORMAT_UINT48              0x09 /**<无符号48位整数。*/
#define BLE_GATT_CPF_FORMAT_UINT64              0x0A /**<无符号64位整数。*/
#define BLE_GATT_CPF_FORMAT_UINT128             0x0B /**<无符号128位整数。*/
#define BLE_GATT_CPF_FORMAT_SINT8               0x0C /**<有符号2位整数。*/
#define BLE_GATT_CPF_FORMAT_SINT12              0x0D /**<有符号12位整数。*/
#define BLE_GATT_CPF_FORMAT_SINT16              0x0E /**<有符号16位整数。*/
#define BLE_GATT_CPF_FORMAT_SINT24              0x0F /**<有符号24位整数。*/
#define BLE_GATT_CPF_FORMAT_SINT32              0x10 /**<有符号32位整数。*/
#define BLE_GATT_CPF_FORMAT_SINT48              0x11 /**<有符号48位整数。*/
#define BLE_GATT_CPF_FORMAT_SINT64              0x12 /**<有符号64位整数。*/
#define BLE_GATT_CPF_FORMAT_SINT128             0x13 /**<有符号128位整数。*/
#define BLE_GATT_CPF_FORMAT_FLOAT32             0x14 /**<IEEE-754 32位浮点。*/
#define BLE_GATT_CPF_FORMAT_FLOAT64             0x15 /**<IEEE-754 64位浮点。*/
#define BLE_GATT_CPF_FORMAT_SFLOAT              0x16 /**<IEEE-11073 16位SFLOAT。*/
#define BLE_GATT_CPF_FORMAT_FLOAT               0x17 /**<IEEE-11073 32位浮点。*/
#define BLE_GATT_CPF_FORMAT_DUINT16             0x18 /**<IEEE-20601格式。*/
#define BLE_GATT_CPF_FORMAT_UTF8S               0x19 /**<UTF-8字符串。*/
#define BLE_GATT_CPF_FORMAT_UTF16S              0x1A /**<UTF-16字符串。*/
#define BLE_GATT_CPF_FORMAT_STRUCT              0x1B /**<不透明结构。*/
/** @} */

/** @defgroup BLE_GATT_CPF_NAMESPACES GATT蓝牙命名空间@{
 */
#define BLE_GATT_CPF_NAMESPACE_BTSIG            0x01 /**<蓝牙SIG定义的命名空间。*/
#define BLE_GATT_CPF_NAMESPACE_DESCRIPTION_UNKNOWN 0x0000 /**<命名空间描述未知。*/
/** @} */

/** @} */

/** @addtogroup BLE_GATT_STRUCTURES结构
 * @{ */

/**
 * @brief BLE GATT连接配置参数，用@ref sd_BLE_cfg_set设置。
 *
 * @retval ：：NRF_ERROR_INVALID_PARAM att_mtu小于@ref BLE_GATT_att_mtu_DEFAULT。
 */
typedef struct
{
  uint16_t  att_mtu;          /**< Maximum size of ATT packet the SoftDevice can send or receive. The default and minimum value is @ref BLE_GATT_ATT_MTU_DEFAULT@mscs@mmsc｛@ref BLE_GATTC_MTU_EXCHANGE｝@mmsc
                              */
} ble_gatt_conn_cfg_t;

/**@brief GATT特性。*/
typedef struct
{
  /* 标准特性*/
  uint8_t broadcast       :1; /**<允许值的广播。*/
  uint8_t read            :1; /**<读取允许的值。*/
  uint8_t write_wo_resp   :1; /**<允许使用写入命令写入值。*/
  uint8_t write           :1; /**<允许使用写入请求写入值。*/
  uint8_t notify          :1; /**<允许值的通知。*/
  uint8_t indicate        :1; /**<允许值的指示。*/
  uint8_t auth_signed_wr  :1; /**<允许使用带符号的写入命令写入值。*/
} ble_gatt_char_props_t;

/**@brief GATT特征扩展属性。*/
typedef struct
{
  /* 扩展属性*/
  uint8_t reliable_wr     :1; /**<允许使用排队写入操作写入值。*/
  uint8_t wr_aux          :1; /**<允许写入特征用户描述描述符。*/
} ble_gatt_char_ext_props_t;

/** @} */

#ifdef __cplusplus
}
#endif
#endif // BLE_GATT_H__

/** @} */

