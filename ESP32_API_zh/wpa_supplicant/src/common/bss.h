/*
 * BSS表版权所有（c）2009-2019，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 */

#ifndef BSS_H
#define BSS_H

struct wpa_scan_res;

/**
 * 结构wpa_bss-bss表
 *
 * 该结构用于以通用格式存储关于相邻BSS的信息。它主要根据驱动程序的扫描结果进行更新。
 */
struct wpa_bss {
	/**结构wpa_supplicant:：bss的列表项*/
	struct dl_list list;
	/**结构wpa_supplicant:：bss_id的列表项*/
	struct dl_list list_id;
	/**此BSS条目的唯一标识符*/
	unsigned int id;
	/**上次扫描更新的索引*/
	unsigned int last_update_idx;
	/**有关BSS/IBSS（WPA_BSS_*）的信息标志*/
	unsigned int flags;
	/** BSSID */
	u8 bssid[ETH_ALEN];
	/** SSID */
	u8 ssid[SSID_MAX_LEN];
	/**SSID长度*/
	size_t ssid_len;
	/**信道频率（MHz）（例如，2412=信道1）*/
	int channel;
	/**TU中的信标间隔（主机字节顺序）*/
	u16 beacon_int;
	/**主机字节顺序的能力信息字段*/
	u16 caps;
	/**信号质量*/
	int qual;
	/**噪声级*/
	int noise;
	/**信号电平*/
	int level;
	/**最后一个信标/探测响应帧的时间戳*/
	u64 tsf;
	/**获取的父文件的时间戳*/
	u64 parent_tsf;
	/**上次更新的时间（即信标或探测响应RX）*/
	struct os_reltime last_update;
	/**以下IE字段的长度（八位字节）（来自探测响应）*/
	size_t ie_len;
	/**以下信标IE字段的长度（八位字节）*/
	size_t beacon_ie_len;
	/* 后跟ie的ie_len八位字节*/
	/* 后跟ie的beacon_ie_len八位字节*/
	u8 ies[];
};

static inline const u8 * wpa_bss_ie_ptr(const struct wpa_bss *bss)
{
	return bss->ies;
}

void wpa_bss_update_start(struct wpa_supplicant *wpa_s);
void wpa_bss_update_scan_res(struct wpa_supplicant *wpa_s,
			     struct wpa_scan_res *res,
			     struct os_reltime *fetch_time);
void wpa_bss_remove(struct wpa_supplicant *wpa_s, struct wpa_bss *bss,
		    const char *reason);
void wpa_bss_update_end(struct wpa_supplicant *wpa_s);
int wpa_bss_init(struct wpa_supplicant *wpa_s);
void wpa_bss_deinit(struct wpa_supplicant *wpa_s);
void wpa_bss_flush(struct wpa_supplicant *wpa_s);
struct wpa_bss * wpa_bss_get(struct wpa_supplicant *wpa_s, const u8 *bssid,
			     const u8 *ssid, size_t ssid_len);
struct wpa_bss * wpa_bss_get_bssid(struct wpa_supplicant *wpa_s,
				   const u8 *bssid);
const u8 * wpa_bss_get_ie(const struct wpa_bss *bss, u8 ie);
const u8 * wpa_bss_get_vendor_ie(const struct wpa_bss *bss, u32 vendor_type);
int wpa_bss_ext_capab(const struct wpa_bss *bss, unsigned int capab);
struct wpa_bss * wpa_bss_get_next_bss(struct wpa_supplicant *wpa_s,
				   struct wpa_bss *prev_bss);

void calculate_update_time(const struct os_reltime *fetch_time,
			   unsigned int age_ms,
			   struct os_reltime *update_time);

#endif /* BSS_H */

