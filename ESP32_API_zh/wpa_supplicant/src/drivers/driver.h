/*
 * 驱动程序界面定义版权所有（c）2003-2017，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 *
 * 此文件定义了%wpa_supplicant和hostapd使用的驱动程序接口。文件的第一部分定义了各种驱动程序操作中使用的数据结构。后面是结构wpa_driver_ops，每个驱动程序包装器将使用回调函数定义该结构，以请求驱动程序操作。在此之后，有了使用wpa_supplicant_event（）进行驱动程序事件报告的定义，以及一些可用于报告事件的方便助手函数。
 */

#ifndef DRIVER_H
#define DRIVER_H

#define WPA_SUPPLICANT_DRIVER_VERSION 4

#include "common/defs.h"
#include "common/ieee802_11_defs.h"
#include "common/wpa_common.h"
#include "utils/list.h"
struct wpa_bss;
struct wpa_supplicant;
/**
 * struct wpa_scan_res-BSS/IBSS的扫描结果
 * @flags: 有关BSS/IBSS（WPA_SCAN_*）的信息标志
 * @bssid: BSSID
 * @freq: 信道频率（MHz）（例如，2412=信道1）
 * @beacon_int: TU中的信标间隔（主机字节顺序）
 * @caps: 主机字节顺序的能力信息字段
 * @qual: 信号质量
 * @noise: 噪声级
 * @level: 信号电平
 * @tsf: 时间戳
 * @age: 以毫秒为单位的信息年龄（即，接收到最后一个信标或探测响应帧之前的毫秒数）
 * @snr: 信噪比（dB）（在扫描结果处理期间计算）
 * @parent_tsf: 根据%TSF_bssid指定的BSS的TSF接收到信标/探测响应帧的时间。
 * @tsf_bssid: %parent_tsf tsf时间引用的BSS。
 * @ie_len: 以下IE字段的长度（八位字节）
 * @beacon_ie_len: 以下信标IE字段的长度（八位字节）
 *
 * 此结构用作驱动程序扫描结果的通用格式。每个驱动程序接口实现负责将驱动程序或操作系统特定的扫描结果转换为此格式。
 *
 * 如果驱动程序不支持报告所有IE，则IE数据结构由可用的IE构成。该字段还需要包含IE格式的SSID。鼓励所有驱动程序扩展到报告所有IE，以便于支持未来的添加。
 *
 * 该结构数据之后是来自探测响应帧的ie的ie_len八位字节（或者如果驱动器没有指示ie的源，则这些也可以来自信标帧）。在第一组ie之后，如果驱动程序提供了两个ie集，则可以跟随另一组ie（具有beacon_ie_len八位字节数据）。
 */
struct wpa_scan_res {
	unsigned int flags;
	u8 bssid[ETH_ALEN];
	int chan;
	u16 beacon_int;
	u16 caps;
	int noise;
	int level;
	u64 tsf;
	unsigned int age;
	u64 parent_tsf;
	u8 tsf_bssid[ETH_ALEN];
	size_t ie_len;
	size_t beacon_ie_len;
	/* 后跟ie数据的ie_len+beacon_ie_len八位字节*/
};

/**
 * 结构wpa_scan_results-扫描结果
 * @res: 指向分配的可变长度扫描结果项的指针数组
 * @num: 扫描结果数组中的条目数
 * @fetch_time: 从驱动程序获取结果的时间
 */
struct wpa_scan_results {
	struct wpa_scan_res **res;
	size_t num;
	struct os_reltime fetch_time;
};

#define WPAS_MAX_SCAN_SSIDS 1

/**
 * 结构wpa_driver_scan_ssid-要扫描的ssid
 * @ssid -要扫描的特定SSID（ProbeReq）%NULL或零长度SSID用于指示带有通配符SSID的活动扫描。
 * @ssid_len -SSID的长度（八位字节）
 */
struct wpa_driver_scan_ssid {
	const u8 *ssid;
	size_t ssid_len;
};

/**
 * struct wpa_driver_scan_params-扫描结构wpa_diver_ops:：scan2（）的参数数据。
 */
struct wpa_driver_scan_params {
	/**
	 * ssids-要扫描的SSID
	 */
	struct wpa_driver_scan_ssid ssids[WPAS_MAX_SCAN_SSIDS];

	/**
	 * num_ssids—ssids数组中的条目数零表示被动扫描请求。
	 */
	size_t num_ssids;

	/**
	 * freqs-要扫描的频率数组或所有频率的%NULL
	 *
	 * 频率设置为MHz。数组以零结尾。
	 */
	int channel;

	/**
	 * bssid-要扫描的特定bssid
	 *
	 * 此可选参数可用于将默认通配符BSSID替换为特定的BSSID，以便在仅需要单个BSS的结果时进行扫描。
	 */
	const u8 *bssid;

	 /**
	  * 持续时间-每个通道的停留时间
	  *
	  * 此可选参数可用于设置每个通道的停留时间。在TU中。
	  */
	 u16 duration;

	 unsigned int duration_mandatory;
	 u8 mode;
};

/**
 * struct scan_info-EVENT_scan_RESULTS事件的可选数据
 * @aborted: 扫描是否已中止
 * @freqs: 扫描频率（MHz）（%NULL=扫描的所有信道）
 * @num_freqs: freq数组中的条目数
 * @ssids: 扫描的SSID（%NULL或零长度SSID表示通配符SSID）
 * @num_ssids: ssids阵列中的条目数
 * @external_scan: 扫描信息是否用于外部扫描
 * @nl_scan_event: 如果此扫描事件的源是正常扫描，则为1；如果扫描事件的来源是供应商扫描，则0
 * @scan_start_tsf: 根据请求扫描的接口连接到的BSS的TSF，扫描开始的时间（如果可用）。
 * @scan_start_tsf_bssid: 根据其设置%scan_start_tsf的BSSID。
 */
struct scan_info {
	int aborted;
	const int *freqs;
	size_t num_freqs;
	struct wpa_driver_scan_ssid ssids[WPAS_MAX_SCAN_SSIDS];
	size_t num_ssids;
	int external_scan;
	int nl_scan_event;
	u64 scan_start_tsf;
	u8 scan_start_tsf_bssid[ETH_ALEN];
} scan_info;

struct wpa_bss_trans_info {
	u8 mbo_transition_reason;
	u8 n_candidates;
	u8 *bssid;
};

struct wpa_bss_candidate_info {
	u8 num;
	struct candidate_list {
		u8 bssid[ETH_ALEN];
		u8 is_accept;
		u32 reject_reason;
	} *candidates;
};

/* 驱动程序_通用.c*/
void wpa_scan_results_free(struct wpa_scan_results *res);

int wpa_drv_send_action(struct wpa_supplicant *wpa_s,
			unsigned int chan, unsigned int wait,
			const u8 *data, size_t data_len, int no_cck);

void wpa_supplicant_connect(struct wpa_supplicant *wpa_s,
			    struct wpa_bss *bss, char *ssid);
#endif /* DRIVER_H */

