/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_HCI_
#define H_BLE_HS_HCI_

/**
 * @brief 蓝牙主机HCI实用程序
 * @defgroup bt_host_hci蓝牙主机hci实用程序
 * @ingroup bt_主机@{
 */

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 向控制器查询用于指定连接的频道映射。通道映射表示为五个字节的数组，每个位对应于一个单独的通道。该数组被解释为小端序，这样：map[0]和0x01-->通道0。map[0]和x02-->通道1…map[1]和0x01-->通道8。
 *
 * 由于有37个通道，因此只写入前37位。
 *
 * 如果位为1，则使用相应的信道。否则，该通道未使用。
 *
 * @param conn_handle           正在读取其通道映射的连接的句柄。
 * @param out_chan_map          成功后，将在此处写入检索到的频道映射。此缓冲区的大小必须大于等于5字节。
 *
 * @return                      成功时为0；如果控制器拒绝请求，BLE主机HCI返回代码；BLE主机核心在出现意外错误时返回代码。
 */
int ble_hs_hci_read_chan_map(uint16_t conn_handle, uint8_t *out_chan_map);

/**
 * 指示控制器使用指定的频道映射。通道映射表示为五个字节的数组，每个位对应于一个单独的通道。该数组被解释为小端序，这样：map[0]和0x01-->通道0。map[0]和x02-->通道1…map[1]和0x01-->通道8。
 *
 * 由于有37个通道，因此只使用应写入的前37位。
 *
 * 如果位为1，则可以使用相应的信道。否则，不应使用通道。
 *
 * @param chan_map              要配置的频道映射。此缓冲区的大小应为5字节。
 *
 * @return                      成功时为0；如果控制器拒绝请求，BLE主机HCI返回代码；BLE主机核心在出现意外错误时返回代码。
 */
int ble_hs_hci_set_chan_class(const uint8_t *chan_map);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif

