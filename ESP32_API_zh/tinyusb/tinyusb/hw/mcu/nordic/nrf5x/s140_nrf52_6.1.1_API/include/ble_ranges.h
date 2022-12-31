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
  @defgroup ble_ranges模块特定SVC、事件和选项编号子范围@{

  @每个API模块的SVC、事件和选项编号子范围的简要定义。

  @注意SVC、事件和选项编号被划分为每个API模块的子范围。每个模块接收其整个分配的SVC调用范围（无论是否实现），但对于其范围内未实现或未定义的调用，返回BLE_ERROR_not_SUPPORTED。

  注意，符号BLE_<module>_SVC_LAST是分配的SVC范围的末尾，而不是实际定义和实现的最后一个SVC函数调用。

  特定的SVC、事件和选项值在每个模块的ble_<module>.h文件中定义，该文件根据范围起始值定义每个SVC代码的名称。
*/

#ifndef BLE_RANGES_H__
#define BLE_RANGES_H__

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_SVC_BASE           0x60       /**<普通BLE SVC基础。*/
#define BLE_SVC_LAST           0x6B       /**<最后一个公共BLE SVC。*/

#define BLE_GAP_SVC_BASE       0x6C       /**<间隙BLE SVC底座。*/
#define BLE_GAP_SVC_LAST       0x9A       /**<GAP BLE SVC last。*/

#define BLE_GATTC_SVC_BASE     0x9B       /**<GATTC BLE SVC基础。*/
#define BLE_GATTC_SVC_LAST     0xA7       /**<GATTC BLE SVC last。*/

#define BLE_GATTS_SVC_BASE     0xA8       /**<GATTS BLE SVC基础。*/
#define BLE_GATTS_SVC_LAST     0xB7       /**<最后关闭SVC。*/

#define BLE_L2CAP_SVC_BASE     0xB8       /**<L2CAP BLE SVC基础。*/
#define BLE_L2CAP_SVC_LAST     0xBF       /**＜L2CAP BLE SVC last。*/


#define BLE_EVT_INVALID        0x00       /**<无效BLE事件。*/

#define BLE_EVT_BASE           0x01       /**<公共BLE事件库。*/
#define BLE_EVT_LAST           0x0F       /**<公共BLE事件最后。*/

#define BLE_GAP_EVT_BASE       0x10       /**<GAP BLE事件库。*/
#define BLE_GAP_EVT_LAST       0x2F       /**<GAP BLE事件最后一次。*/

#define BLE_GATTC_EVT_BASE     0x30       /**<GATTC BLE事件库。*/
#define BLE_GATTC_EVT_LAST     0x4F       /**<GATTC BLE事件最后。*/

#define BLE_GATTS_EVT_BASE     0x50       /**<GATTS BLE事件库。*/
#define BLE_GATTS_EVT_LAST     0x6F       /**<GATTS BLE事件最后。*/

#define BLE_L2CAP_EVT_BASE     0x70       /**<L2CAP BLE事件基础。*/
#define BLE_L2CAP_EVT_LAST     0x8F       /**<最后一个L2CAP BLE事件。*/


#define BLE_OPT_INVALID        0x00       /**<BLE选项无效。*/

#define BLE_OPT_BASE           0x01       /**<通用BLE选项基础。*/
#define BLE_OPT_LAST           0x1F       /**<最后一个通用BLE选项。*/

#define BLE_GAP_OPT_BASE       0x20       /**<GAP BLE选项基础。*/
#define BLE_GAP_OPT_LAST       0x3F       /**<最后一个GAP BLE选项。*/

#define BLE_GATT_OPT_BASE      0x40       /**<GATT BLE期权基础。*/
#define BLE_GATT_OPT_LAST      0x5F       /**<GATT BLE选项最后。*/

#define BLE_GATTC_OPT_BASE     0x60       /**<GATTC BLE选项基础。*/
#define BLE_GATTC_OPT_LAST     0x7F       /**<GATTC BLE选项最后。*/

#define BLE_GATTS_OPT_BASE     0x80       /**<GATTS BLE选项基础。*/
#define BLE_GATTS_OPT_LAST     0x9F       /**<GATTS BLE选项最后。*/

#define BLE_L2CAP_OPT_BASE     0xA0       /**<L2CAP BLE选项基础。*/
#define BLE_L2CAP_OPT_LAST     0xBF       /**<最后一个L2CAP BLE选项。*/


#define BLE_CFG_INVALID        0x00       /**<BLE配置无效。*/

#define BLE_CFG_BASE           0x01       /**<通用BLE配置基础。*/
#define BLE_CFG_LAST           0x1F       /**<最后一个通用BLE配置。*/

#define BLE_CONN_CFG_BASE      0x20       /**<BLE连接配置基础。*/
#define BLE_CONN_CFG_LAST      0x3F       /**<BLE连接配置最后。*/

#define BLE_GAP_CFG_BASE       0x40       /**<GAP BLE配置基础。*/
#define BLE_GAP_CFG_LAST       0x5F       /**<最后一个GAP BLE配置。*/

#define BLE_GATT_CFG_BASE      0x60       /**<GATT BLE配置基础。*/
#define BLE_GATT_CFG_LAST      0x7F       /**<GATT BLE配置最后。*/

#define BLE_GATTC_CFG_BASE     0x80       /**<GATTC BLE配置基础。*/
#define BLE_GATTC_CFG_LAST     0x9F       /**<GATTC BLE配置最后。*/

#define BLE_GATTS_CFG_BASE     0xA0       /**<GATTS BLE配置基础。*/
#define BLE_GATTS_CFG_LAST     0xBF       /**<GATTS BLE配置最后。*/

#define BLE_L2CAP_CFG_BASE     0xC0       /**<L2CAP BLE配置基础。*/
#define BLE_L2CAP_CFG_LAST     0xDF       /**<最后一个L2CAP BLE配置。*/





#ifdef __cplusplus
}
#endif
#endif /* BLE_RANGES_H__ */

/**
  @} @}
*/

