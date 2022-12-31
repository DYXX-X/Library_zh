/*
 * 内部WPA/RSN请求方状态机定义版权所有（c）2004-2010，Jouni Malinen<j@w1.fi>
 *
 * 该程序是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证第2版的条款重新分发和/或修改它。
 *
 * 或者，此软件可以根据BSD许可证条款进行分发。
 *
 * 有关详细信息，请参阅自述和复制。
 */

#ifndef WPA_I_H
#define WPA_I_H

struct install_key {
    int mic_errors_seen; /* Michael MIC错误与当前PTK*/
    int keys_cleared;
    enum wpa_alg alg;
    u8 addr[ETH_ALEN];
    int key_idx;
    int set_tx;
    u8 seq[10];
    u8 key[32];
};

/**
 * structwpa_sm-内部wpa状态机数据
 */
struct wpa_sm {
    u8 pmk[PMK_LEN_MAX];
    size_t pmk_len;

    struct wpa_ptk ptk, tptk;
    int ptk_set, tptk_set;
    u8 snonce[WPA_NONCE_LEN];
    u8 anonce[WPA_NONCE_LEN]; /* ANonce来自最后一条1/4消息*/
    int renew_snonce;
    u8 rx_replay_counter[WPA_REPLAY_COUNTER_LEN];
    int rx_replay_counter_set;
    u8 request_counter[WPA_REPLAY_COUNTER_LEN];
    struct rsn_pmksa_cache *pmksa; /* PMKSA缓存*/
    struct rsn_pmksa_cache_entry *cur_pmksa; /* 当前PMKSA条目*/

    unsigned int pairwise_cipher;
    unsigned int group_cipher;
    unsigned int key_mgmt;
    unsigned int mgmt_group_cipher;
    void *network_ctx;

    int rsn_enabled; /* 配置中是否启用RSN*/

    int countermeasures; /*TKIP对抗状态标志，1：处于对抗状态*/
    ETSTimer  cm_timer;

    u8 *assoc_wpa_ie; /* 拥有（再）AssocReq的WPA/RSN IE*/
    size_t assoc_wpa_ie_len;

    u8 eapol_version;

    int wpa_ptk_rekey;
    u8 own_addr[ETH_ALEN];

    u8 bssid[ETH_ALEN];

    unsigned int proto;
    enum wpa_states wpa_state;

    u8 *ap_wpa_ie, *ap_rsn_ie;
    size_t ap_wpa_ie_len, ap_rsn_ie_len;

    bool key_install;

    struct install_key install_ptk;
    struct install_key install_gtk;

    void (* sendto) (void *buffer, uint16_t len);
    void (*config_assoc_ie) (u8 proto, u8 *assoc_buf, u32 assoc_wpa_ie_len);
    void (*install_ppkey) (enum wpa_alg alg, u8 *addr, int key_idx, int set_tx,
               u8 *seq, unsigned int seq_len, u8 *key, unsigned int key_len, enum key_flag key_flag);
    int (*get_ppkey) (uint8_t *ifx, int *alg, uint8_t *addr, int *key_idx,
               uint8_t *key, size_t key_len, enum key_flag key_flag);
    void (*wpa_deauthenticate)(u8 reason_code);
    void (*wpa_neg_complete)(void);
    struct wpa_gtk_data gd; //用于calllback保存参数
    u16 key_info;       //用于txcallback参数
    u16 txcb_flags;
    bool   ap_notify_completed_rsne;
    wifi_pmf_config_t pmf_cfg;
    u8 eapol1_count;
    struct rsn_sppamsdu_sup spp_sup;
};

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


typedef void (* WPA_SEND_FUNC)(void *buffer, u16 len);

typedef void (* WPA_SET_ASSOC_IE)(u8 proto, u8 *assoc_buf, u32 assoc_wpa_ie_len);

typedef void (*WPA_INSTALL_KEY) (enum wpa_alg alg, u8 *addr, int key_idx, int set_tx,
               u8 *seq, size_t seq_len, u8 *key, size_t key_len, enum key_flag key_flag);

typedef int (*WPA_GET_KEY) (u8 *ifx, int *alg, u8 *addt, int *keyidx, u8 *key, size_t key_len, enum key_flag key_flag);

typedef void (*WPA_DEAUTH_FUNC)(u8 reason_code);

typedef void (*WPA_NEG_COMPLETE)(void);

bool wpa_sm_init(char * payload, WPA_SEND_FUNC snd_func, \
        WPA_SET_ASSOC_IE set_assoc_ie_func, \
        WPA_INSTALL_KEY ppinstallkey, \
        WPA_GET_KEY ppgetkey, \
        WPA_DEAUTH_FUNC wpa_deauth, \
        WPA_NEG_COMPLETE wpa_neg_complete);

void wpa_sm_deinit(void);

void eapol_txcb(void *eb);

void wpa_set_profile(u32 wpa_proto, u8 auth_mode);

int wpa_set_bss(char *macddr, char * bssid, u8 pairwise_cipher, u8 group_cipher, char *passphrase, u8 *ssid, size_t ssid_len);

int wpa_sm_rx_eapol(u8 *src_addr, u8 *buf, u32 len);
#endif /* WPA_I_H */

