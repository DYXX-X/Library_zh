// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
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

#ifndef _WL_State_H_
#define _WL_State_H_
#include "esp_err.h"

/**
* @brief 此结构用于存储闪存访问的当前状态
*
*/
#if defined(_MSC_VER)
#define ALIGNED_(x) __declspec(align(x))
#else
#if defined(__GNUC__)
#define ALIGNED_(x) __attribute__ ((aligned(x)))
#endif
#endif

typedef struct ALIGNED_(32) WL_State_s {
public:
    uint32_t pos;           /*!< 当前虚拟块位置*/
    uint32_t max_pos;       /*!< 最大持仓量*/
    uint32_t move_count;    /*!< 移动计数总数。用于计算地址*/
    uint32_t access_count;  /*!< 当前访问计数*/
    uint32_t max_count;     /*!< 移动块时的最大访问计数*/
    uint32_t block_size;    /*!< 移动块大小*/
    uint32_t version;       /*!< 用于标识当前libary实现版本的状态id*/
    uint32_t device_id;     /*!< 当前WL实例的ID*/
    uint32_t reserved[7];   /*!< 预留空间供将来使用*/
    uint32_t crc;           /*!< 结构CRC*/
} wl_state_t;

#ifndef _MSC_VER // MSVS对此定义具有不同的格式
static_assert(sizeof(wl_state_t) % 16 == 0, "Size of wl_state_t structure should be compatible with flash encryption");
#endif // _MSC_VER

#define WL_STATE_CRC_LEN_V1 offsetof(wl_state_t, device_id)
#define WL_STATE_CRC_LEN_V2 offsetof(wl_state_t, crc)

#endif // _WL_状态_H_

