/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_MBUF_
#define H_BLE_HS_MBUF_

/**
 * @brief 蓝牙主机链接内存缓冲区（mbuf）
 * @defgroup bt_host_mbuf蓝牙主机链接内存缓冲区（mbuf）
 * @ingroup bt_主机@{
 */

#include <inttypes.h>
#ifdef __cplusplus
extern "C" {
#endif

struct os_mbuf;

/**
 * 分配适合ATT命令包的mbuf。生成的数据包具有足够的前导空间：
 *  -ACL数据头
 *  -L2CAP B帧标头
 *  -最大的ATT命令库（准备写请求/响应）。
 *
 * @return 成功时为空mbuf，错误时为NULL。
 */
struct os_mbuf *ble_hs_mbuf_att_pkt(void);

/**
 * 分配mbuf并用指定的平面缓冲区的内容填充它。
 *
 * @param buf 要从中复制的平面缓冲区。
 * @param len 平面缓冲区的长度。
 *
 * @return 成功时新分配的mbuf，错误时为NULL。
 */
struct os_mbuf *ble_hs_mbuf_from_flat(const void *buf, uint16_t len);

/**
 * 将mbuf的内容复制到指定的平面缓冲区。如果平面缓冲区太小，无法容纳mbuf的内容，则将其填充到容量，并返回BLE_HS_EMSGSIZE。
 *
 * @param om            要从中复制的mbuf。
 * @param flat          目标平面缓冲区。
 * @param max_len       平面缓冲区的大小。
 * @param out_copy_len  实际复制的字节数写在这里。
 *
 * @return               成功时为0，错误时为BLE主机核心返回代码。
 */
int ble_hs_mbuf_to_flat(const struct os_mbuf *om, void *flat, uint16_t max_len,
                        uint16_t *out_copy_len);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif

