/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_MBUF_PRIV_
#define H_BLE_HS_MBUF_PRIV_

#ifdef __cplusplus
extern "C" {
#endif

struct os_mbuf;

struct os_mbuf *ble_hs_mbuf_bare_pkt(void);
struct os_mbuf *ble_hs_mbuf_acl_pkt(void);
struct os_mbuf *ble_hs_mbuf_l2cap_pkt(void);
int ble_hs_mbuf_pullup_base(struct os_mbuf **om, int base_len);

#ifdef __cplusplus
}
#endif

#endif

