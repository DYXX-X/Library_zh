/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLECENT_
#define H_BLECENT_

#include "os/mynewt.h"
#include "modlog/modlog.h"
#ifdef __cplusplus
extern "C" {
#endif

struct ble_hs_adv_fields;
struct ble_gap_conn_desc;
struct ble_hs_cfg;
union ble_store_value;
union ble_store_key;

#define BLECENT_SVC_ALERT_UUID              0x1811
#define BLECENT_CHR_SUP_NEW_ALERT_CAT_UUID  0x2A47
#define BLECENT_CHR_NEW_ALERT               0x2A46
#define BLECENT_CHR_SUP_UNR_ALERT_CAT_UUID  0x2A48
#define BLECENT_CHR_UNR_ALERT_STAT_UUID     0x2A45
#define BLECENT_CHR_ALERT_NOT_CTRL_PT       0x2A44

/**其他。*/
void print_bytes(const uint8_t *bytes, int len);
void print_mbuf(const struct os_mbuf *om);
char *addr_str(const void *addr);
void print_uuid(const ble_uuid_t *uuid);
void print_conn_desc(const struct ble_gap_conn_desc *desc);
void print_adv_fields(const struct ble_hs_adv_fields *fields);

/**同行。*/
struct peer_dsc {
    SLIST_ENTRY(peer_dsc) next;
    struct ble_gatt_dsc dsc;
};
SLIST_HEAD(peer_dsc_list, peer_dsc);

struct peer_chr {
    SLIST_ENTRY(peer_chr) next;
    struct ble_gatt_chr chr;

    struct peer_dsc_list dscs;
};
SLIST_HEAD(peer_chr_list, peer_chr);

struct peer_svc {
    SLIST_ENTRY(peer_svc) next;
    struct ble_gatt_svc svc;

    struct peer_chr_list chrs;
};
SLIST_HEAD(peer_svc_list, peer_svc);

struct peer;
typedef void peer_disc_fn(const struct peer *peer, int status, void *arg);

struct peer {
    SLIST_ENTRY(peer) next;

    uint16_t conn_handle;

    /**发现的GATT服务清单。*/
    struct peer_svc_list svcs;

    /**跟踪我们在服务发现过程中的位置。*/
    uint16_t disc_prev_chr_val;
    struct peer_svc *cur_svc;

    /**服务发现完成时执行的回调。*/
    peer_disc_fn *disc_cb;
    void *disc_cb_arg;
};

int peer_disc_all(uint16_t conn_handle, peer_disc_fn *disc_cb,
                  void *disc_cb_arg);
const struct peer_dsc *
peer_dsc_find_uuid(const struct peer *peer, const ble_uuid_t *svc_uuid,
                   const ble_uuid_t *chr_uuid, const ble_uuid_t *dsc_uuid);
const struct peer_chr *
peer_chr_find_uuid(const struct peer *peer, const ble_uuid_t *svc_uuid,
                   const ble_uuid_t *chr_uuid);
const struct peer_svc *
peer_svc_find_uuid(const struct peer *peer, const ble_uuid_t *uuid);
int peer_delete(uint16_t conn_handle);
int peer_add(uint16_t conn_handle);
int peer_init(int max_peers, int max_svcs, int max_chrs, int max_dscs);

#ifdef __cplusplus
}
#endif

#endif

