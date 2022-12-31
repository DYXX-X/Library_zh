/*
 * wpa_supplicant-WPA2/RSN PMKSA缓存函数版权所有（c）2003-2009、2011-2012，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef PMKSA_CACHE_H
#define PMKSA_CACHE_H

/**
 * 结构rsn_pmksa_cache_entry-pmksa缓存条目
 */
struct rsn_pmksa_cache_entry {
    struct rsn_pmksa_cache_entry *next;
    u8 pmkid[PMKID_LEN];
    u8 pmk[PMK_LEN_MAX];
    size_t pmk_len;
    os_time_t expiration;
    int akmp; /* WPA_KEY_MGMT_* */
    u8 aa[ETH_ALEN];

    os_time_t reauth_time;

    /**
     * network_ctx-网络配置上下文
     *
     * 此字段仅用于将PMKSA缓存条目与特定网络配置（例如，特定SSID和安全策略）相匹配。这可以是指向配置项的指针，但PMKSA缓存代码不会取消引用该值，这可以是任何类型的标识符。
     */
    void *network_ctx;
    int opportunistic;
};

struct rsn_pmksa_cache;

enum pmksa_free_reason {
    PMKSA_FREE,
    PMKSA_REPLACE,
    PMKSA_EXPIRE,
};

#ifdef IEEE8021X_EAPOL

struct rsn_pmksa_cache *
pmksa_cache_init(void (*free_cb)(struct rsn_pmksa_cache_entry *entry,
            void *ctx, enum pmksa_free_reason reason),
        void *ctx, struct wpa_sm *sm);
void pmksa_cache_deinit(struct rsn_pmksa_cache *pmksa);
struct rsn_pmksa_cache_entry * pmksa_cache_get(struct rsn_pmksa_cache *pmksa,
        const u8 *aa, const u8 *pmkid,
        const void *network_ctx);
int pmksa_cache_list(struct rsn_pmksa_cache *pmksa, char *buf, size_t len);
struct rsn_pmksa_cache_entry *
pmksa_cache_add(struct rsn_pmksa_cache *pmksa, const u8 *pmk, size_t pmk_len,
        const u8 *pmkid, const u8 *kck, size_t kck_len,
        const u8 *aa, const u8 *spa, void *network_ctx, int akmp);
struct rsn_pmksa_cache_entry * pmksa_cache_get_current(struct wpa_sm *sm);
void pmksa_cache_clear_current(struct wpa_sm *sm);
int pmksa_cache_set_current(struct wpa_sm *sm, const u8 *pmkid,
        const u8 *bssid, void *network_ctx,
        int try_opportunistic);
struct rsn_pmksa_cache_entry *
pmksa_cache_get_opportunistic(struct rsn_pmksa_cache *pmksa,
        void *network_ctx, const u8 *aa);
void pmksa_cache_flush(struct rsn_pmksa_cache *pmksa, void *network_ctx,
        const u8 *pmk, size_t pmk_len);

#else /* IEEE8021X_EAPOL */

    static inline struct rsn_pmksa_cache *
pmksa_cache_init(void (*free_cb)(struct rsn_pmksa_cache_entry *entry,
            void *ctx, enum pmksa_free_reason reason),
        void *ctx, struct wpa_sm *sm)
{
    return (void *) -1;
}

static inline void pmksa_cache_deinit(struct rsn_pmksa_cache *pmksa)
{
}

    static inline struct rsn_pmksa_cache_entry *
pmksa_cache_get(struct rsn_pmksa_cache *pmksa, const u8 *aa, const u8 *pmkid,
        const void *network_ctx)
{
    return NULL;
}

    static inline struct rsn_pmksa_cache_entry *
pmksa_cache_get_current(struct wpa_sm *sm)
{
    return NULL;
}

static inline int pmksa_cache_list(struct rsn_pmksa_cache *pmksa, char *buf,
        size_t len)
{
    return -1;
}

    static inline struct rsn_pmksa_cache_entry *
pmksa_cache_add(struct rsn_pmksa_cache *pmksa, const u8 *pmk, size_t pmk_len,
        const u8 *pmkid, const u8 *kck, size_t kck_len,
        const u8 *aa, const u8 *spa, void *network_ctx, int akmp)
{
    return NULL;
}

static inline void pmksa_cache_clear_current(struct wpa_sm *sm)
{
}

static inline int pmksa_cache_set_current(struct wpa_sm *sm, const u8 *pmkid,
        const u8 *bssid,
        void *network_ctx,
        int try_opportunistic)
{
    return -1;
}

static inline void pmksa_cache_flush(struct rsn_pmksa_cache *pmksa,
        void *network_ctx,
        const u8 *pmk, size_t pmk_len)
{
}

#endif /* IEEE8021X_EAPOL */

#endif /* PMKSA_CACHE_H */

