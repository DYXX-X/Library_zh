// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief DMA描述符的类型
 *
 */
typedef struct dma_descriptor_s {
    struct {
        uint32_t size : 12;         /*!< 缓冲区大小*/
        uint32_t length : 12;       /*!< 缓冲区中的有效字节数*/
        uint32_t reversed24_27 : 4; /*!< 保留*/
        uint32_t err_eof : 1;       /*!< 接收到的缓冲区是否包含错误*/
        uint32_t reserved29 : 1;    /*!< 保留*/
        uint32_t suc_eof : 1;       /*!< 描述符是否是链接中的最后一个*/
        uint32_t owner : 1;         /*!< 允许谁访问此描述符指向的缓冲区*/
    } dw0;                          /*!< 描述符字0*/
    void *buffer;                   /*!< 指向缓冲区的指针*/
    struct dma_descriptor_s *next;  /*!< 指向下一个描述符的指针（如果描述符是最后一个，则设置为NULL，例如suc_eof=1）*/
} dma_descriptor_t;

_Static_assert(sizeof(dma_descriptor_t) == 12, "dma_descriptor_t should occupy 12 bytes in memory");

#define DMA_DESCRIPTOR_BUFFER_OWNER_CPU (0)   /*!< 允许CPU访问DMA缓冲区*/
#define DMA_DESCRIPTOR_BUFFER_OWNER_DMA (1)   /*!< DMA引擎允许访问DMA缓冲区*/
#define DMA_DESCRIPTOR_BUFFER_MAX_SIZE (4095) /*!< 可附加到描述符的缓冲区的最大大小*/

#ifdef __cplusplus
}
#endif

