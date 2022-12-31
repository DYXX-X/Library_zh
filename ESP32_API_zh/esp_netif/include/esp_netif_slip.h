// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
//

#ifndef _ESP_NETIF_SLIP_H_
#define _ESP_NETIF_SLIP_H_

#include "esp_netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief SLIP网络接口的配置结构
 *
 */
typedef struct esp_netif_slip_config {
    esp_ip6_addr_t ip6_addr;        /* 本地IP6地址*/

} esp_netif_slip_config_t;


/** @brief 为提供的esp netif设置公共参数。
 *
 * @param[in]  esp_netif 滑动把手（尤指netif实例）
 * @param[in]  config 指向SLIP netif配置结构的指针
 *
 * @return     成功时ESP_OK，如果NETIF为空或不为SLIP，则ESP_ERR_ESP_NETIF_INVALID_PARAMS
 */
esp_err_t esp_netif_slip_set_params(esp_netif_t *netif, const esp_netif_slip_config_t *config);

#if CONFIG_LWIP_IPV6
/** @brief 为提供的esp netif设置IPV6地址。
 *
 * @param[in]  netif 滑动把手（尤指netif实例）
 * @param[in]  ipv6 SLIP接口的IPv6地址
 *
 * @return     成功时ESP_OK，如果NETIF为空或不为SLIP，则ESP_ERR_ESP_NETIF_INVALID_PARAMS
 */
esp_err_t esp_netif_slip_set_ipv6(esp_netif_t *netif, const esp_ip6_addr_t *ipv6);
#endif

/**
 * @brief  通过SLIP接口写入原始数据包的数据路径API
 *
 * 此API通常在实现用户定义的方法时使用
 *
 * @param[in]    esp_netif 滑动把手（尤指netif实例）
 * @param[in]    buffer 指向传出数据的指针
 * @param[in]    len 数据的长度
 *
 * @return
 *         -成功时ESP_OK
 */
void esp_netif_lwip_slip_raw_output(esp_netif_t *netif, void *buffer, size_t len);

/**
 * @brief  获取连接到SLIP接口的IP6地址
 *
 * @param[in]    esp_netif 滑动把手（尤指netif实例）
 * @param[in]    address 索引（未使用）
 *
 * @return
 *         -指向内部ip6地址对象的指针
 */
const esp_ip6_addr_t *esp_slip_get_ip6(esp_netif_t *slip_netif);

#ifdef __cplusplus
}
#endif
#endif //_ESP_NETIF_SLIP_H_

