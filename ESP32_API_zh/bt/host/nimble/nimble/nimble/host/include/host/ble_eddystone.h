/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_EDDYSTONE_
#define H_BLE_EDDYSTONE_

/**
 * @brief Edestone-来自谷歌的BLE信标
 * @defgroup bt_eddystone eddystone-来自谷歌的BLE信标
 * @ingroup bt_主机@{
 */

#include <inttypes.h>
#ifdef __cplusplus
extern "C" {
#endif

struct ble_hs_adv_fields;

#define BLE_EDDYSTONE_MAX_UUIDS16           3
#define BLE_EDDYSTONE_URL_MAX_LEN           17

#define BLE_EDDYSTONE_URL_SCHEME_HTTP_WWW   0
#define BLE_EDDYSTONE_URL_SCHEME_HTTPS_WWW  1
#define BLE_EDDYSTONE_URL_SCHEME_HTTP       2
#define BLE_EDDYSTONE_URL_SCHEME_HTTPS      3

#define BLE_EDDYSTONE_URL_SUFFIX_COM_SLASH  0x00
#define BLE_EDDYSTONE_URL_SUFFIX_ORG_SLASH  0x01
#define BLE_EDDYSTONE_URL_SUFFIX_EDU_SLASH  0x02
#define BLE_EDDYSTONE_URL_SUFFIX_NET_SLASH  0x03
#define BLE_EDDYSTONE_URL_SUFFIX_INFO_SLASH 0x04
#define BLE_EDDYSTONE_URL_SUFFIX_BIZ_SLASH  0x05
#define BLE_EDDYSTONE_URL_SUFFIX_GOV_SLASH  0x06
#define BLE_EDDYSTONE_URL_SUFFIX_COM        0x07
#define BLE_EDDYSTONE_URL_SUFFIX_ORG        0x08
#define BLE_EDDYSTONE_URL_SUFFIX_EDU        0x09
#define BLE_EDDYSTONE_URL_SUFFIX_NET        0x0a
#define BLE_EDDYSTONE_URL_SUFFIX_INFO       0x0b
#define BLE_EDDYSTONE_URL_SUFFIX_BIZ        0x0c
#define BLE_EDDYSTONE_URL_SUFFIX_GOV        0x0d
#define BLE_EDDYSTONE_URL_SUFFIX_NONE       0xff

/**
 * 配置设备以通告埃迪斯通UID信标。
 *
 * @param adv_fields            基本广告字段将转换为eddystone信标。保留所有配置的字段；您可能希望在调用此函数之前清除此结构。
 * @param uid                   要播发的16字节UID。
 * @param measured_power        测量功率（0米处的RSSI值）。
 *
 * @return                      成功时为0；BLE_HS_EBUSY，如果广告正在进行中；BLE_HS_EMSGSIZE，如果指定的数据太大而无法容纳在广告中；其他非零故障。
 */
int ble_eddystone_set_adv_data_uid(struct ble_hs_adv_fields *adv_fields,
                                   void *uid, int8_t measured_power);

/**
 * 配置设备以通告埃迪斯通URL信标。
 *
 * @param adv_fields            基本广告字段将转换为eddystone信标。保留所有配置的字段；您可能希望在调用此函数之前清除此结构。
 * @param url_scheme            URL的前缀；BLE_EDDYSTONE_URL_SCHEME值之一。
 * @param url_body              URL的中间位置。如果有合适的后缀代码，则不要包含后缀。
 * @param url_body_len          url_body参数的字符串长度。
 * @param url_suffix            URL的后缀；BLE_EDDYSTONE_URL_SUFFIX值之一；如果后缀嵌入主体参数中，请使用BLE_EDDYSTONE_URL_SUFFIX_NONE。
 * @param measured_power        测量功率（0米处的RSSI值）。
 *
 * @return                      成功时为0；BLE_HS_EBUSY，如果广告正在进行中；BLE_HS_EMSGSIZE，如果指定的数据太大而无法容纳在广告中；其他非零故障。
 */
int ble_eddystone_set_adv_data_url(struct ble_hs_adv_fields *adv_fields,
                                   uint8_t url_scheme, char *url_body,
                                   uint8_t url_body_len, uint8_t suffix,
                                   int8_t measured_power);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif

