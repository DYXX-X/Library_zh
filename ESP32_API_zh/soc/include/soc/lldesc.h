// 版权所有2010-2019 Espressif Systems（上海）私人有限公司
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
#include <stdbool.h>
#include "sdkconfig.h"

#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/lldesc.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/lldesc.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/lldesc.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/lldesc.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/rom/lldesc.h"
#endif

//大小字段有12位，但4096的大小字段为0。
//为了避免大小不对齐时可能出现的问题，我们每个desc只使用4096-4。
/**DMA描述符可以保存的缓冲区中数据的最大大小。*/
#define LLDESC_MAX_NUM_PER_DESC (4096-4)

// 某些DMA操作可能会对长度施加某些对齐限制
#define LLDESC_MAX_NUM_PER_DESC_16B_ALIGNED (4096 - 16)
#define LLDESC_MAX_NUM_PER_DESC_32B_ALIGNED (4096 - 32)

/**
 * 生成指向描述符数组中的（巨大）缓冲区的链接列表。
 *
 * 调用者应该通过使用相同的max_desc_size参数调用``lldesc_get_required_num_constraine``来确保有足够的大小来容纳数组。
 *
 * @param[out] out_desc_array 描述符数组的输出，头应该被馈送到DMA。
 * @param buffer 描述符指向的缓冲区。
 * @param size 缓冲区的大小（或TX的长度）
 * @param max_desc_size 每个描述符的最大长度
 * @param isrx RX DMA可能要求缓冲器字对齐，对于RX链路设置为真，否则为假。
 */
void lldesc_setup_link_constrained(lldesc_t *out_desc_array, const void *buffer, int size, int max_desc_size, bool isrx);

/**
 * 生成指向描述符数组中的（巨大）缓冲区的链接列表。
 *
 * 调用者应该通过调用“lldesc_get_required_num”来确保有足够的大小来容纳数组。
 *
 * @param[out] out_desc_array 描述符数组的输出，头应该被馈送到DMA。
 * @param buffer 描述符指向的缓冲区。
 * @param size 缓冲区的大小（或TX的长度）
 * @param isrx RX DMA可能要求缓冲器字对齐，对于RX链路设置为真，否则为假。
 */
#define lldesc_setup_link(out_desc_array, buffer, size, isrx) lldesc_setup_link_constrained(out_desc_array, buffer, size, LLDESC_MAX_NUM_PER_DESC, isrx)

/**
 * @brief 获取链接列表的接收长度，直到链接结束或eof。
 *
 * @param head      链接列表的标题。
 * @param[out] out_next EOF描述符的下一个描述符的输出。如果没有EOF，则返回NULL。如果不需要下一个描述符，则可以设置为NULL。
 * @return 所有描述符的“len”字段的累积，直到EOF或链路结束。
 */
int lldesc_get_received_len(lldesc_t* head, lldesc_t** out_next);

/**
 * 获取给定缓冲区大小所需的描述符数。
 *
 * @param data_size 检查描述符编号的大小。
 *
 * @return 需要数字。
 */
static inline int lldesc_get_required_num_constrained(int data_size, int max_desc_size)
{
    return (data_size + max_desc_size - 1) / max_desc_size;
}

/**
 * 获取给定缓冲区大小所需的描述符数。
 *
 * @param data_size 检查描述符编号的大小。
 * @param max_desc_size 每个描述符的最大长度
 * @return 需要数字。
 */
#define lldesc_get_required_num(data_size) lldesc_get_required_num_constrained(data_size, LLDESC_MAX_NUM_PER_DESC)

