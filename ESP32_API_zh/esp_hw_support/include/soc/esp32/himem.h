/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stddef.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

//不透明指针作为ram/范围数据的句柄
typedef struct esp_himem_ramdata_t *esp_himem_handle_t;
typedef struct esp_himem_rangedata_t *esp_himem_rangehandle_t;

//ESP32 MMU块大小
#define ESP_HIMEM_BLKSZ (0x8000)

#define ESP_HIMEM_MAPFLAG_RO 1 /*!< 指示仅从中读取映射。请注意，这是目前未使用的。*/

/**
 * @brief 在高内存中分配块
 *
 * @param size 要分配的块的大小，以字节为单位。注意，这需要是外部RAM mmu块大小（32K）的倍数。
 * @param[out] handle_out 要返回的句柄
 * @returns -ESP_OK（如果成功）
 *          -ESP_ERR_NO_MEM（如果内存不足）
 *          -如果大小不是32K的倍数，则为ESP_ERR_INVALID_SIZE
 */
esp_err_t esp_himem_alloc(size_t size, esp_himem_handle_t *handle_out);


/**
 * @brief 分配内存区域以将块映射到
 *
 * 这将分配一个连续的CPU内存区域，可用于将物理内存块映射到。
 *
 * @param size 要分配的范围的大小。注意，这需要是外部RAM mmu块大小（32K）的倍数。
 * @param[out] handle_out 要返回的句柄
 * @returns -ESP_OK（如果成功）
 *          -如果内存或地址空间不足，则为ESP_ERR_NO_MEM
 *          -如果大小不是32K的倍数，则为ESP_ERR_INVALID_SIZE
 */
esp_err_t esp_himem_alloc_map_range(size_t size, esp_himem_rangehandle_t *handle_out);

/**
 * @brief 将一块高内存映射到CPU地址空间
 *
 * 这有效地使块可用于读/写操作。
 *
 * @note 要映射的区域需要具有与SPI RAM MMU块大小（32K）对齐的偏移量和大小
 *
 * @param handle 内存块的句柄，如esp_himem_alloc所示
 * @param range 映射内存的范围句柄
 * @param ram_offset 要映射的块的物理内存块中的偏移量
 * @param range_offset 将映射块的地址范围的偏移量
 * @param len 要映射的区域长度
 * @param flags ESP_HIMEM_MAPFLAG之一_*
 * @param[out] out_ptr 指向存储结果内存指针的变量的指针
 * @returns -ESP_OK（如果可以映射内存）
 *          -ESP_ERR_INVALID_ARG如果偏移、范围或长度未对齐MMU块（32K）
 *          -如果偏移量/长度不符合分配的内存或范围，则为ESP_ERR_INVALID_SIZE
 *          -ESP_ERR_INVALID_STATE，如果所选ram偏移量/长度中的块已经映射，或者如果所选范围偏移量/距离中的块已映射。
 */
esp_err_t esp_himem_map(esp_himem_handle_t handle, esp_himem_rangehandle_t range, size_t ram_offset, size_t range_offset, size_t len, int flags, void **out_ptr);


/**
 * @brief 释放一块物理内存
 *
 * 这将清除关联的句柄，使内存可再次重新分配。仅当当前没有内存块具有映射时，此操作才会成功。
 *
 * @param handle 内存块的句柄，如esp_himem_alloc所示
 * @returns -如果成功释放内存，则ESP_OK
 *          -ESP_ERR_INVALID_ARG（如果句柄仍然（部分）映射）
 */
esp_err_t esp_himem_free(esp_himem_handle_t handle);



/**
 * @brief 释放映射范围
 *
 * 这将清除关联的句柄，使该范围可再次重新分配。仅当当前没有任何范围块用于映射时，此操作才会成功。
 *
 * @param handle 范围块的句柄，如esp_himem_alloc_map_range所示
 * @returns -如果成功释放内存，则ESP_OK
 *          -如果句柄仍然（部分）映射到
 */
esp_err_t esp_himem_free_map_range(esp_himem_rangehandle_t handle);


/**
 * @brief 取消映射区域
 *
 * @param range 量程手柄
 * @param ptr esp_himem_map返回的指针
 * @param len 要取消映射的块的长度。必须与SPI RAM MMU块大小（32K）对齐
 * @returns -如果存储器被成功地取消映射，
 *          -如果ptr或len无效，则返回ESP_ERR_INVALID_ARG。
 */
esp_err_t esp_himem_unmap(esp_himem_rangehandle_t range, void *ptr, size_t len);


/**
 * @brief 在himem API的控制下获取内存总量
 *
 * @returns 内存量（字节）
 */
size_t esp_himem_get_phys_size(void);

/**
 * @brief 在himem API的控制下获取可用内存量
 *
 * @returns 可用内存量（字节）
 */
size_t esp_himem_get_free_size(void);


/**
 * @brief 获取银行交换所需的SPI内存地址空间
 *
 * @note 这在esp32/spiram中也有很弱的定义。c并在那里返回0，因此如果该文件中没有使用其他函数，则不会保留内存。
 *
 * @returns 保留区域的数量（字节）
 */
size_t esp_himem_reserved_area_size(void);


#ifdef __cplusplus
}
#endif

