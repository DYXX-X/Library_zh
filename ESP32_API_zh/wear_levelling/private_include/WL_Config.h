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

#ifndef _WL_Config_H_
#define _WL_Config_H_

#include "Flash_Access.h"

/**
* @brief 此类用作配置磨损均衡模块的结构
*
*/

#if defined(_MSC_VER)
#define ALIGNED_(x) __declspec(align(x))
#else
#if defined(__GNUC__)
#define ALIGNED_(x) __attribute__ ((aligned(x)))
#endif
#endif

typedef struct ALIGNED_(16) WL_Config_s { /*!< wl_config_t结构的大小应除以16进行加密*/
    size_t   start_addr;    /*!< 闪存中的起始地址*/
    uint32_t full_mem_size; /*!< 用于存储数据的内存量（字节）*/
    uint32_t page_size;     /*!< 一个页面大小（字节）。页面可能大于内存块。此参数必须为page_size>=N*block_size。*/
    uint32_t sector_size;   /*!< 将立即擦除和存储的闪存扇区的大小（擦除）*/
    uint32_t updaterate;    /*!< 移动块之前的访问量*/
    uint32_t wr_size;       /*!< 写入操作时每个块的最小字节数：1。。。*/
    uint32_t version;       /*!< 当前实现的版本。要擦除和重新分配完整内存，此ID必须与之前的ID不同。*/
    size_t   temp_buff_size;  /*!< 要从一个闪存区域复制到另一个闪存区的临时分配缓冲区的大小。最好的方法是，如果该值等于扇区大小。*/
    uint32_t crc;           /*!< 此配置的CRC*/
} wl_config_t;

#ifndef _MSC_VER // MSVS对此定义具有不同的格式
static_assert(sizeof(wl_config_t) % 16 == 0, "Size of wl_config_t structure should be compatible with flash encryption");
#endif // _MSC_VER

#endif // _WL_配置_H_

