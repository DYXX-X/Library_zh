/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_RESOLV_
#define H_BLE_LL_RESOLV_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 解析列表中的条目。标识地址以小端格式存储。本地rpa以little-endian格式存储。IRK以大端格式存储。
 *
 *  注意：rl_local_mark和rl_peer_irk需要单词对齐
 */
struct ble_ll_resolv_entry
{
    uint8_t rl_addr_type;
    uint8_t rl_priv_mode;
    uint8_t rl_has_local;
    uint8_t rl_has_peer;
    uint8_t rl_local_irk[16];
    uint8_t rl_peer_irk[16];
    uint8_t rl_identity_addr[BLE_DEV_ADDR_LEN];
    uint8_t rl_local_rpa[BLE_DEV_ADDR_LEN];
    uint8_t rl_peer_rpa[BLE_DEV_ADDR_LEN];
};

extern struct ble_ll_resolv_entry g_ble_ll_resolv_list[];

/* 清除解析列表*/
int ble_ll_resolv_list_clr(void);

/* 读取解析列表的大小*/
int ble_ll_resolv_list_read_size(uint8_t *rspbuf, uint8_t *rsplen);

/* 将设备添加到解析列表*/
int ble_ll_resolv_list_add(const uint8_t *cmdbuf, uint8_t len);

/* 从解析列表中删除设备*/
int ble_ll_resolv_list_rmv(const uint8_t *cmdbuf, uint8_t len);

/* 地址解析启用命令*/
int ble_ll_resolv_enable_cmd(const uint8_t *cmdbuf, uint8_t len);

int ble_ll_resolv_peer_addr_rd(const uint8_t *cmdbuf, uint8_t len,
                               uint8_t *rspbuf, uint8_t *rsplen);
int ble_ll_resolv_local_addr_rd(const uint8_t *cmdbuf, uint8_t len,
                                uint8_t *rspbuf, uint8_t *rsplen);

/* 在解析列表中查找“addr”。不检查是否启用了地址解析*/
struct ble_ll_resolv_entry *
ble_ll_resolv_list_find(const uint8_t *addr, uint8_t addr_type);

/* 如果启用了地址解析，则返回true*/
uint8_t ble_ll_resolv_enabled(void);

/* 重置专用地址解析*/
void ble_ll_resolv_list_reset(void);

/* 生成本地或对等RPA。呼叫方应确保RL上存在所需的IRK
 */
void ble_ll_resolv_get_priv_addr(struct ble_ll_resolv_entry *rl, int local,
                                 uint8_t *addr);

void ble_ll_resolv_set_peer_rpa(int index, uint8_t *rpa);
void ble_ll_resolv_set_local_rpa(int index, uint8_t *rpa);

/* 生成可解析的专用地址。*/
int ble_ll_resolv_gen_rpa(uint8_t *addr, uint8_t addr_type, uint8_t *rpa,
                          int local);

/* 设置可解析的专用地址超时*/
int ble_ll_resolv_set_rpa_tmo(const uint8_t *cmdbuf, uint8_t len);

/* 设置隐私模式*/
int ble_ll_resolve_set_priv_mode(const uint8_t *cmdbuf, uint8_t len);

/* 获取RPA超时（秒）*/
uint32_t ble_ll_resolv_get_rpa_tmo(void);

/* 解析可解析的专用地址*/
int ble_ll_resolv_rpa(const uint8_t *rpa, const uint8_t *irk);

/* 尝试解析对等RPA并返回RL上的索引（如果匹配）*/
int ble_ll_resolv_peer_rpa_any(const uint8_t *rpa);

/* 初始化分辨率*/
void ble_ll_resolv_init(void);

#ifdef __cplusplus
}
#endif

#endif

