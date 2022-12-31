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

#ifndef __ESP_SEC_API_H__
#define __ESP_SEC_API_H__

#include "stack/bt_types.h"

#define APP_SEC_IRK_FLAG        (0)
#define RAND_NB_LEN         0x08
#define SEC_KEY_LEN         0x10

/*
 * STRUCTURES DEFINITIONS
 ****************************************************************************************
 */


///通用安全密钥结构
typedef struct {
    ///键值MSB->LSB
    UINT8 key[SEC_KEY_LEN];
} smp_sec_key;

///随机数结构
typedef struct {
    ///随机数的8字节数组
    UINT8     nb[RAND_NB_LEN];
} rand_nb;

typedef struct {
    // LTK
    smp_sec_key ltk;
    // 随机数
    rand_nb rand_nb;
    // EDIV
    UINT16 ediv;
    // LTK密钥大小
    UINT8 key_size;

    // 上次配对的对等地址类型
    UINT8 peer_addr_type;
    // 上次配对的对等地址
    BD_ADDR peer_addr;

    // 身份验证级别
    UINT8 auth;

} tAPP_SEC_ENV;

extern tAPP_SEC_ENV app_sec_env;

/*
* GLOBAL FUNCTIONS DECLARATIONS
****************************************************************************************
*/

void app_ble_sec_init(void);

void app_ble_sec_pairing_cmp_evt_send(UINT8);

UINT32 app_ble_sec_gen_tk(void);

void app_ble_sec_gen_ltk(UINT8 key_size);

void app_ble_security_start(void);

#endif /* __ESP_SEC_API_H__ */

