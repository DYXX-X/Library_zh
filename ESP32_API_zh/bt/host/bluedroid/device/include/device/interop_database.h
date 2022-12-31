/******************************************************************************
 * 版权所有（C）2015谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _INTEROP_DATABASE_H_
#define _INTEROP_DATABASE_H_

#include "device/interop.h"

typedef struct {
    bt_bdaddr_t addr;
    uint8_t len;
    interop_feature_t feature;
} interop_entry_t;

static const interop_entry_t interop_database[] = {
    // Nexus远程（Spike）
    // 注意：可能会影响其他华硕品牌设备
    {{{0x08, 0x62, 0x66,    0,    0,    0}}, 3, INTEROP_DISABLE_LE_SECURE_CONNECTIONS},
    {{{0x38, 0x2c, 0x4a, 0xc9,    0,    0}}, 4, INTEROP_DISABLE_LE_SECURE_CONNECTIONS},
    {{{0x38, 0x2c, 0x4a, 0xe6,    0,    0}}, 4, INTEROP_DISABLE_LE_SECURE_CONNECTIONS},
    {{{0x54, 0xa0, 0x50, 0xd9,    0,    0}}, 4, INTEROP_DISABLE_LE_SECURE_CONNECTIONS},
    {{{0xac, 0x9e, 0x17,    0,    0,    0}}, 3, INTEROP_DISABLE_LE_SECURE_CONNECTIONS},
    {{{0xf0, 0x79, 0x59,    0,    0,    0}}, 3, INTEROP_DISABLE_LE_SECURE_CONNECTIONS},

    // 摩托罗拉密钥链接
    {{{0x1c, 0x96, 0x5a,    0,    0,    0}}, 3, INTEROP_DISABLE_LE_SECURE_CONNECTIONS},

    // Flic智能按钮
    {{{0x80, 0xe4, 0xda, 0x70,    0,    0}}, 4, INTEROP_DISABLE_LE_SECURE_CONNECTIONS},

    // 宝马汽车套件（哈曼/贝克尔）
    {{{0x9c, 0xdf, 0x03,    0,    0,    0}}, 3, INTEROP_AUTO_RETRY_PAIRING}
};

#endif /*_INTEROP_DATABASE_H_*/

