/*
 * 版权所有（c）2012-2017，Nordic Semiconductor ASA保留所有权利。
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
  @添加组BLE_COMMON@{
*/


#ifndef BLE_HCI_H__
#define BLE_HCI_H__
#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup BLE_HCI_STATUS_CODES蓝牙状态代码
 * @{ */

#define BLE_HCI_STATUS_CODE_SUCCESS                        0x00   /**<成功。*/
#define BLE_HCI_STATUS_CODE_UNKNOWN_BTLE_COMMAND           0x01   /**<未知BLE命令。*/
#define BLE_HCI_STATUS_CODE_UNKNOWN_CONNECTION_IDENTIFIER  0x02   /**<未知连接标识符。*/
/*0x03 硬件故障0x04页面超时
*/
#define BLE_HCI_AUTHENTICATION_FAILURE                     0x05   /**<身份验证失败。*/
#define BLE_HCI_STATUS_CODE_PIN_OR_KEY_MISSING             0x06   /**<缺少Pin或Key。*/
#define BLE_HCI_MEMORY_CAPACITY_EXCEEDED                   0x07   /**<超过内存容量。*/
#define BLE_HCI_CONNECTION_TIMEOUT                         0x08   /**<连接超时。*/
/*0x09超过连接限制0x0A超过设备的同步连接限制0x0B ACL连接已存在*/
#define BLE_HCI_STATUS_CODE_COMMAND_DISALLOWED             0x0C   /**<不允许使用命令。*/
/*0x0D连接因资源有限而被拒绝x0E连接因安全原因而被拒绝sx0F连接因不可接受BD_ADDR0x10连接接受超时而被拒绝0x11不支持的功能或参数值*/
#define BLE_HCI_STATUS_CODE_INVALID_BTLE_COMMAND_PARAMETERS 0x12  /**<BLE命令参数无效。*/
#define BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION           0x13  /**<远程用户终止连接。*/
#define BLE_HCI_REMOTE_DEV_TERMINATION_DUE_TO_LOW_RESOURCES 0x14  /**<由于资源不足，远程设备终止连接。*/
#define BLE_HCI_REMOTE_DEV_TERMINATION_DUE_TO_POWER_OFF     0x15  /**<由于电源关闭，远程设备终止连接。*/
#define BLE_HCI_LOCAL_HOST_TERMINATED_CONNECTION            0x16  /**<本地主机终止连接。*/
/*
0x17重复尝试0x18不允许配对0x19未知LMP PDU
*/
#define BLE_HCI_UNSUPPORTED_REMOTE_FEATURE 0x1A                   /**<不支持的远程功能。*/
/*
0x1B SCO偏移被拒绝0x1C SCO间隔被拒绝0x1D SCO空中模式被拒绝*/
#define BLE_HCI_STATUS_CODE_INVALID_LMP_PARAMETERS     0x1E       /**<无效的LMP参数。*/
#define BLE_HCI_STATUS_CODE_UNSPECIFIED_ERROR          0x1F       /**<未指定的错误。*/
/*0x20 不支持的LMP参数值0x21不允许更改角色
*/
#define BLE_HCI_STATUS_CODE_LMP_RESPONSE_TIMEOUT            0x22       /**<LMP响应超时。*/
#define BLE_HCI_STATUS_CODE_LMP_ERROR_TRANSACTION_COLLISION 0x23  /**<LMP错误事务冲突/LL过程冲突。*/
#define BLE_HCI_STATUS_CODE_LMP_PDU_NOT_ALLOWED             0x24       /**<不允许LMP PDU。*/
/*0x25 加密模式不可接受0x26无法更改链接密钥0x27请求的QoS不受支持
*/
#define BLE_HCI_INSTANT_PASSED                         0x28       /**<立即通过。*/
#define BLE_HCI_PAIRING_WITH_UNIT_KEY_UNSUPPORTED      0x29       /**<不支持与单元密钥配对。*/
#define BLE_HCI_DIFFERENT_TRANSACTION_COLLISION        0x2A       /**<不同交易冲突。*/
/*
0x2B保留0x2C QoS不可接受参数0x2D QoS被拒绝0x2E信道分类不受支持0x2F安全性不足
*/
#define BLE_HCI_PARAMETER_OUT_OF_MANDATORY_RANGE       0x30            /**<参数超出强制范围。*/
/*
0x31保留0x32角色切换挂起0x33保留0x34保留插槽冲突0x35角色切换失败0x36扩展查询响应太大0x37主机不支持安全简单配对。0x38主机忙-由于找不到合适的通道，配对0x39连接被拒绝*/
#define BLE_HCI_CONTROLLER_BUSY                        0x3A       /**<控制器忙。*/
#define BLE_HCI_CONN_INTERVAL_UNACCEPTABLE             0x3B       /**<连接间隔不可接受。*/
#define BLE_HCI_DIRECTED_ADVERTISER_TIMEOUT            0x3C       /**<定向广告超时。*/
#define BLE_HCI_CONN_TERMINATED_DUE_TO_MIC_FAILURE     0x3D       /**<连接因MIC故障而终止。*/
#define BLE_HCI_CONN_FAILED_TO_BE_ESTABLISHED          0x3E       /**<无法建立连接。*/

/** @} */


#ifdef __cplusplus
}
#endif
#endif // BLE_HCI_H__

/** @} */

