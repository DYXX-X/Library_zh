/*
 * 版权所有2020 Espressif Systems（上海）私人有限公司
 *
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifdef __cplusplus
extern "C" {
#endif

#if MYNEWT_VAL(BLE_HOST_BASED_PRIVACY)
/*
 * 解析列表中的条目。
 */
struct ble_hs_resolv_entry {
    uint8_t rl_addr_type;
    uint8_t rl_local_irk[16];
    uint8_t rl_peer_irk[16];
    uint8_t rl_identity_addr[BLE_DEV_ADDR_LEN];
    uint8_t rl_pseudo_id[BLE_DEV_ADDR_LEN];
    uint8_t rl_local_rpa[BLE_DEV_ADDR_LEN];
    uint8_t rl_peer_rpa[BLE_DEV_ADDR_LEN];
};

#if MYNEWT_VAL(BLE_STORE_CONFIG_PERSIST)
/* 将对等记录保存在NVS中。XXX需要在“存储”模块中处理此问题*/
int ble_store_persist_peer_records(void);
#endif

struct ble_hs_peer_sec {
    ble_addr_t peer_addr;
    uint8_t irk[16];
    uint8_t irk_present: 1;
};
/*
 * BLE主机对等设备记录，这有助于在创建绑定和交换IRK之前存储对等RPA。
 */
struct ble_hs_dev_records {
    bool rec_used;
    uint8_t rand_addr_type;
    uint8_t pseudo_addr[BLE_DEV_ADDR_LEN];
    uint8_t rand_addr[BLE_DEV_ADDR_LEN];
    uint8_t identity_addr[BLE_DEV_ADDR_LEN];
    struct ble_hs_peer_sec peer_sec;
};

/* 将设备添加到解析列表*/
int ble_hs_resolv_list_add(uint8_t *cmdbuf);
int ble_hs_gen_own_private_rnd(void);
uint8_t *ble_hs_get_rpa_local(void);

/* 从解析列表中删除设备*/
int ble_hs_resolv_list_rmv(uint8_t, uint8_t *);
/* 清除解析列表和对等开发记录*/
void ble_hs_resolv_list_clear_all(void);

/* 地址解析启用命令*/
void ble_hs_resolv_enable(bool);
void ble_hs_resolv_nrpa_enable(void);
void ble_hs_resolv_nrpa_disable(void);

/* 在解析列表中查找“addr”。不检查是否启用了地址解析*/
struct ble_hs_resolv_entry *
ble_hs_resolv_list_find(uint8_t *addr);

/* 如果启用了基于主机的RPA（隐私），则返回true*/
bool ble_host_rpa_enabled(void);

/* 搜索对等设备记录（RPA），如果找到RL，则将匹配的RL、peer_address提取到输入参数中*/
void
ble_rpa_replace_peer_params_with_rl(uint8_t *, uint8_t *, struct ble_hs_resolv_entry **);

int ble_rpa_resolv_add_peer_rec(uint8_t *);

struct ble_hs_dev_records *ble_rpa_get_peer_dev_records(void);
int ble_rpa_get_num_peer_dev_records(void);
void ble_rpa_set_num_peer_dev_records(int);
int ble_rpa_remove_peer_dev_rec(struct ble_hs_dev_records *);
struct ble_hs_dev_records *ble_rpa_find_peer_dev_rec(uint8_t *);

/* 设置可解析的专用地址超时*/
int ble_hs_resolv_set_rpa_tmo(uint16_t);

/* 解析可解析的专用地址*/
int ble_hs_resolv_rpa(uint8_t *rpa, uint8_t *irk);

/* 初始化分辨率*/
void ble_hs_resolv_init(void);

#ifdef __cplusplus
}
#endif

#endif

