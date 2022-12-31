/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_WHITELIST_
#define H_BLE_LL_WHITELIST_

#ifdef __cplusplus
extern "C" {
#endif

/* 清除白名单*/
int ble_ll_whitelist_clear(void);

/* 读取白名单的大小*/
int ble_ll_whitelist_read_size(uint8_t *rspbuf, uint8_t *rsplen);

/* 将设备添加到白名单*/
int ble_ll_whitelist_add(const uint8_t *cmdbuf, uint8_t len);

/* 从白名单中删除设备*/
int ble_ll_whitelist_rmv(const uint8_t *cmdbuf, uint8_t len);

/* 启用白名单*/
void ble_ll_whitelist_enable(void);

/* 禁用白名单*/
void ble_ll_whitelist_disable(void);

/* 如果地址与白名单条目匹配，则布尔函数返回true*/
int ble_ll_whitelist_match(uint8_t *addr, uint8_t addr_type, int is_ident);

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_LL_WHITELIST_ */

