// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef __BTC_CONFIG_H__
#define __BTC_CONFIG_H__

#include <stdbool.h>
#include <stddef.h>

#include "stack/bt_types.h"

typedef struct btc_config_section_iter_t btc_config_section_iter_t;

bool btc_config_init(void);
bool btc_config_shut_down(void);
bool btc_config_clean_up(void);

bool btc_config_has_section(const char *section);
bool btc_config_exist(const char *section, const char *key);
bool btc_config_get_int(const char *section, const char *key, int *value);
bool btc_config_set_int(const char *section, const char *key, int value);
bool btc_config_get_str(const char *section, const char *key, char *value, int *size_bytes);
bool btc_config_set_str(const char *section, const char *key, const char *value);
bool btc_config_get_bin(const char *section, const char *key, uint8_t *value, size_t *length);
bool btc_config_set_bin(const char *section, const char *key, const uint8_t *value, size_t length);
bool btc_config_remove(const char *section, const char *key);
bool btc_config_remove_section(const char *section);

size_t btc_config_get_bin_length(const char *section, const char *key);

const btc_config_section_iter_t *btc_config_section_begin(void);
const btc_config_section_iter_t *btc_config_section_end(void);
const btc_config_section_iter_t *btc_config_section_next(const btc_config_section_iter_t *section);
const char *btc_config_section_name(const btc_config_section_iter_t *section);

void btc_config_flush(void);
int btc_config_clear(void);

// TODO（zachoverflow）：呃……我们需要把这些搬出去。这些是对等体特定的，而不是配置通用的。
bool btc_get_address_type(const BD_ADDR bd_addr, int *p_addr_type);
bool btc_compare_address_key_value(const char *section, const char *key_type, void *key_value, int key_length);
bool btc_get_device_type(const BD_ADDR bd_addr, int *p_device_type);

void btc_config_lock(void);
void btc_config_unlock(void);

#endif

