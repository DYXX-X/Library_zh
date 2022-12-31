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
  @添加组BLE_COMMON@{
  @加法组nrf_error@{
    @ingroup BLE_COMMON@}

  @defgroup ble_err常规错误代码@{

  @BLE API的一般错误代码定义。

  @内部组BLE_COMMON
*/
#ifndef NRF_BLE_ERR_H__
#define NRF_BLE_ERR_H__

#include "nrf_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/* @defgroup BLE_ERRORS错误代码
 * @{ */
#define BLE_ERROR_NOT_ENABLED            (NRF_ERROR_STK_BASE_NUM+0x001) /**尚未调用<@ref sd_ble_enable。*/
#define BLE_ERROR_INVALID_CONN_HANDLE    (NRF_ERROR_STK_BASE_NUM+0x002) /**<连接句柄无效。*/
#define BLE_ERROR_INVALID_ATTR_HANDLE    (NRF_ERROR_STK_BASE_NUM+0x003) /**<属性句柄无效。*/
#define BLE_ERROR_INVALID_ADV_HANDLE     (NRF_ERROR_STK_BASE_NUM+0x004) /**<无效的广告句柄。*/
#define BLE_ERROR_INVALID_ROLE           (NRF_ERROR_STK_BASE_NUM+0x005) /**<无效角色。*/
#define BLE_ERROR_BLOCKED_BY_OTHER_LINKS (NRF_ERROR_STK_BASE_NUM+0x006) /**<由于其他链接的调度，更改链接设置的尝试失败。*/
/** @} */


/** @defgroup BLE_ERROR_SUBRANGES模块特定错误代码子范围
 *  @brief 模块特定错误代码的子范围分配。
 *  @note 有关特定错误代码，请参阅ble_<module>。h或ble_error<模块>.h。
 * @{ */
#define NRF_L2CAP_ERR_BASE             (NRF_ERROR_STK_BASE_NUM+0x100) /**＜L2CAP特定错误。*/
#define NRF_GAP_ERR_BASE               (NRF_ERROR_STK_BASE_NUM+0x200) /**<GAP特定错误。*/
#define NRF_GATTC_ERR_BASE             (NRF_ERROR_STK_BASE_NUM+0x300) /**<GATT客户特定错误。*/
#define NRF_GATTS_ERR_BASE             (NRF_ERROR_STK_BASE_NUM+0x400) /**<GATT服务器特定错误。*/
/** @} */

#ifdef __cplusplus
}
#endif
#endif


/**
  @} @}
*/

