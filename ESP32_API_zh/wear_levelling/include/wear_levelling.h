// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
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

#ifndef _wear_levelling_H_
#define _wear_levelling_H_

#include "esp_log.h"
#include "esp_partition.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief 磨损调平手柄
*/
typedef int32_t wl_handle_t;

#define WL_INVALID_HANDLE -1

/**
* @brief 为定义的分区安装WL
*
* @param partition 将用于访问
* @param out_handle WL实例的句柄
*
* @return
*       -如果分配成功，则返回ESP_OK；
*       -如果WL分配失败，则返回ESP_ERR_INVALID_ARG；
*       -如果没有内存分配WL组件，则返回ESP_ERR_NO_MEM；
*/
esp_err_t wl_mount(const esp_partition_t *partition, wl_handle_t *out_handle);

/**
* @brief 卸载已定义分区的WL
*
* @param handle WL分区句柄
*
* @return
*       -ESP_OK，如果操作成功完成；
*       -或来自低级闪存驱动器的错误代码之一。
*/
esp_err_t wl_unmount(wl_handle_t handle);

/**
* @brief 擦除部分WL存储
*
* @param handle 与分区相关的WL句柄
* @param start_addr 擦除操作应开始的地址。必须与函数wl_sector_size（…）的结果对齐。
* @param size 应擦除的范围大小（以字节为单位）。必须可被函数wl_sector_size（…）的结果整除。。
*
* @return
*       -ESP_OK，如果成功擦除范围；
*       -如果迭代器或dst为空，则返回ESP_ERR_INVALID_ARG；
*       -如果擦除将超出分区边界，则返回ESP_ERR_INVALID_SIZE；
*       -或来自低级闪存驱动器的错误代码之一。
*/
esp_err_t wl_erase_range(wl_handle_t handle, size_t start_addr, size_t size);

/**
* @brief 将数据写入WL存储器
*
* 在将数据写入闪存之前，需要擦除闪存的相应区域。这可以使用wl_erase_range函数完成。
*
* @param handle 与分区相关的WL句柄
* @param dest_addr 应写入数据的地址，相对于分区的开头。
* @param src 指向源缓冲区的指针。指针必须为非NULL，缓冲区长度必须至少为“size”字节。
* @param size 要写入的数据大小（字节）。
*
* @note 在写入WL存储之前，请确保已使用WL_erase_range调用将其擦除。
*
* @return
*       -ESP_OK，如果数据写入成功；
*       -如果dst_offset超过分区大小，则返回ESP_ERR_INVALID_ARG；
*       -ESP_ERR_INVALID_SIZE，如果写入将超出分区边界；
*       -或来自低级闪存驱动器的错误代码之一。
*/
esp_err_t wl_write(wl_handle_t handle, size_t dest_addr, const void *src, size_t size);

/**
* @brief 从WL存储器读取数据
*
* @param handle 之前初始化的WL模块实例
* @param dest 指向应存储数据的缓冲区的指针。指针必须为非NULL，缓冲区长度必须至少为“size”字节。
* @param src_addr 要读取的数据的地址，相对于分区的开头。
* @param size 要读取的数据大小（字节）。
*
* @return
*       -ESP_OK，如果数据读取成功；
*       -如果src_offset超过分区大小，则返回ESP_ERR_INVALID_ARG；
*       -ESP_ERR_INVALID_SIZE，如果读取将超出分区的边界；
*       -或来自低级闪存驱动器的错误代码之一。
*/
esp_err_t wl_read(wl_handle_t handle, size_t src_addr, void *dest, size_t size);

/**
* @brief 获取WL存储的大小
*
* @param handle 之前初始化的WL模块句柄
* @return 可用大小（字节）
*/
size_t wl_size(wl_handle_t handle);

/**
* @brief 获取WL实例的扇区大小
*
* @param handle 之前初始化的WL模块句柄
* @return 扇区大小（字节）
*/
size_t wl_sector_size(wl_handle_t handle);


#ifdef __cplusplus
} // 外部“C”
#endif

#endif // _磨损水平H_

