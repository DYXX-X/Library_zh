/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HW_
#define H_BLE_HW_

#ifdef __cplusplus
extern "C" {
#endif

#include "syscfg/syscfg.h"

#if defined(ARCH_sim)
#define BLE_USES_HW_WHITELIST   (0)
#else
#define BLE_USES_HW_WHITELIST   MYNEWT_VAL(BLE_HW_WHITELIST_ENABLE)
#endif

/* 返回硬件白名单元素的数量*/
uint8_t ble_hw_whitelist_size(void);

/* 清除白名单*/
void ble_hw_whitelist_clear(void);

/* 从硬件白名单中删除设备*/
void ble_hw_whitelist_rmv(const uint8_t *addr, uint8_t addr_type);

/* 将设备添加到硬件白名单*/
int ble_hw_whitelist_add(const uint8_t *addr, uint8_t addr_type);

/* 启用硬件白名单*/
void ble_hw_whitelist_enable(void);

/* 启用硬件白名单*/
void ble_hw_whitelist_disable(void);

/* 如果地址与白名单条目匹配，则布尔函数返回true*/
int ble_hw_whitelist_match(void);

/* 加密数据*/
struct ble_encryption_block;
int ble_hw_encrypt_block(struct ble_encryption_block *ecb);

/* 随机数生成*/
typedef void (*ble_rng_isr_cb_t)(uint8_t rnum);
int ble_hw_rng_init(ble_rng_isr_cb_t cb, int bias);

/**
 * 启动随机数生成器
 *
 * @return 整数
 */
int ble_hw_rng_start(void);

/**
 * 停止随机生成器
 *
 * @return 整数
 */
int ble_hw_rng_stop(void);

/**
 * 读取随机数生成器。
 *
 * @return 单位8_t
 */
uint8_t ble_hw_rng_read(void);

/*  清除解析列表*/
void ble_hw_resolv_list_clear(void);

/* 将设备添加到硬件解析列表*/
int ble_hw_resolv_list_add(uint8_t *irk);

/* 从硬件解析列表中删除设备*/
void ble_hw_resolv_list_rmv(int index);

/* 返回硬件中白名单的大小*/
uint8_t ble_hw_resolv_list_size(void);

/* 启用解析列表*/
void ble_hw_resolv_list_enable(void);

/* 禁用解析列表设备*/
void ble_hw_resolv_list_disable(void);

/* 返回解析地址的索引-如果未解决，则为1*/
int ble_hw_resolv_list_match(void);

/* 返回公共设备地址，如果不存在，则返回-1*/
int ble_hw_get_public_addr(ble_addr_t *addr);

/* 返回随机静态地址，如果不存在，则返回-1*/
int ble_hw_get_static_addr(ble_addr_t *addr);

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_HW_ */

