/*
 * wpa_supplicant-wpa定义版权所有（c）2003-2007，Jouni Malinen<j@w1.fi>
 *
 * 该程序是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证第2版的条款重新分发和/或修改它。
 *
 * 或者，此软件可以根据BSD许可证条款进行分发。
 *
 * 有关详细信息，请参阅自述和复制。
 */

#ifndef WPA_H
#define WPA_H

#include "sdkconfig.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/ets_sys.h" // 将在idf v5.0中删除
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/ets_sys.h"
#endif
#include "utils/common.h"
#include "common/defs.h"
#include "common/wpa_common.h"
#include "esp_wifi_types.h"
#include "esp_wifi_crypto_types.h"
#include "wpa_i.h"


#define WPA_SM_STATE(_sm) ((_sm)->wpa_state)

struct wpa_sm;

int wpa_sm_rx_eapol(u8 *src_addr, u8 *buf, u32 len);
bool wpa_sta_is_cur_pmksa_set(void);
bool wpa_sta_in_4way_handshake(void);
bool wpa_sta_cur_pmksa_matches_akm(void);

#define WPA_ASSERT  assert

struct l2_ethhdr {
    u8 h_dest[ETH_ALEN];
    u8 h_source[ETH_ALEN];
    be16 h_proto;
} STRUCT_PACKED;

/**
 * set_key-配置加密密钥
 * @ifname: 接口名称（用于多SSID/VLAN支持）
 * @priv: 专用驱动程序接口数据
 * @alg: 加密算法（%WPA_ALG_NONE、%WPA_ALG_WEP、%WPA_ALG_TKIP、%WPA-ALG_CCMP、%WPA_DLG_IGTK、%WPA_BLG_PMK）；%WPA_ALG_NONE清除密钥。
 * @addr: 对等STA的地址或广播/默认密钥的ff:ff:ff:ff:ff:ff
 * @key_idx: 密钥索引（0..3），对于单播密钥通常为0；0..4095用于IGTK
 * @set_tx: 将此密钥配置为默认Tx密钥（仅在驱动程序不支持单独的单播/单独密钥时使用
 * @seq: 序列号/包号，seq_len八位字节，下一个用于重放保护的包号；为Rx密钥配置（在大多数情况下，这仅用于广播密钥，对于单播密钥设置为零）
 * @seq_len: seq的长度取决于算法：TKIP:6个八位字节，CCMP:6个八位字节，IGTK:6个8位字节
 * @key: 密钥缓冲区；TKIP:16字节临时密钥、8字节Tx Mic密钥、8个字节Rx Mic密钥
 * @key_len: 密钥缓冲区的长度（以八位字节为单位）（WEP:5或13，TKIP:32，CCMP:16，IGTK:16）
 *
 * 返回：成功时返回0，失败时返回-1
 *
 * 为内核驱动程序配置给定的密钥。如果驱动程序支持单独的键（4个默认键+1个单独键），则可以使用addr来确定该键是默认键还是单独键。如果只支持4个键，则使用键索引为0的默认键作为单个键。STA必须配置为将其用作默认Tx密钥（设置了set_Tx），并接受所有密钥索引的Rx。在大多数情况下，WPA只使用密钥索引1和2作为广播密钥，因此密钥索引0可用于此类配置。
 *
 * 请注意，TKIP密钥包括单独的TX和RX MIC密钥，某些驱动程序可能希望它们的顺序与wpa_supplicant使用的顺序不同。如果交换了TX/RX密钥，所有TKIP加密的数据包都会欺骗Michael MIC错误。这可以通过交换driver_中密钥的字节16..23和24..31来改变MIC密钥的顺序来解决。c set_key（）实现，请参见driver_ndis。c是如何做到这一点的示例。
 */


/**
 * send_eapol-发送eapol数据包的可选函数
 * @priv: 专用驱动程序接口数据
 * @dest: 目标MAC地址
 * @proto: 以太网类型
 * @data: EAPOL数据包以IEEE 802.1X报头开头
 * @data_len: EAPOL数据包的大小
 *
 * 返回：成功时返回0，失败时返回-1
 *
 * 此可选函数可用于覆盖具有驱动程序特定功能的l2_packet操作。如果设置了此函数指针，则完全不使用l2_packet模块，并且驱动程序接口代码负责接收和发送所有EAPOL数据包。接收到的EAPOL包通过EVENT_EAPOL_RX事件发送到核心代码。如果使用send_eapol（），则需要驱动程序接口来实现get_mac_addr（）处理程序。
 */

#define KEYENTRY_TABLE_MAP(key_entry_valid)  ((key_entry_valid)%5)

void pp_michael_mic_failure(u16 isunicast);

void wpa_sm_set_state(enum wpa_states state);

char * dup_binstr(const void *src, size_t len);

void wpa_set_pmk(uint8_t *pmk, const u8 *pmkid, bool cache_pmksa);

int wpa_hook_init(void);

bool wpa_hook_deinit(void);

char * dup_binstr(const void *src, size_t len);

int wpa_michael_mic_failure(u16 isunicast);

wifi_cipher_type_t cipher_type_map_supp_to_public(unsigned cipher);

unsigned cipher_type_map_public_to_supp(wifi_cipher_type_t cipher);

void wpa_sta_clear_curr_pmksa(void);

#endif /* WPA_H */

