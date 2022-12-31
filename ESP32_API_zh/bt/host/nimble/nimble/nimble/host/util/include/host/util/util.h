/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_HOST_UTIL_
#define H_HOST_UTIL_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 尝试使用至少一个蓝牙地址配置设备。地址以特定于硬件的方式恢复。
 *
 * @param prefer_random         在检查是否已配置公共地址之前，是否尝试还原随机地址。
 *
 * @return                      成功时为0；如果设备没有任何可用地址，则返回BLE_HS_ENOADDR。其他BLE主机核心代码出错。
 */
int ble_hs_util_ensure_addr(int prefer_random);

#ifdef __cplusplus
}
#endif

#endif

