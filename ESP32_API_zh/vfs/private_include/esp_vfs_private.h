/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#include "esp_vfs.h"
#include "esp_vfs_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vfs_entry_ {
    esp_vfs_t vfs;          // 包含指向VFS函数的指针
    char path_prefix[ESP_VFS_PATH_MAX]; // 映射到此VFS的路径前缀
    size_t path_prefix_len; // 微优化以避免额外的工作
    void* ctx;              // 可传递给VFS的可选指针
    int offset;             // svfs数组中此结构的索引
} vfs_entry_t;


/**
 * @brief 获取uart vfs的指针。
 *
 * 在vfs_console中调用此函数，以获得uart的vfs实现。
 *
 * @return 指向结构esp_vfs_t的指针
 */
const esp_vfs_t *esp_vfs_uart_get_vfs(void);

/**
 * @brief 获取cdcacm-vfs的指针。
 *
 * 在vfs_console中调用此函数，以获得cdcacm的vfs实现。
 *
 * @return 指向结构esp_vfs_t的指针
 */
const esp_vfs_t *esp_vfs_cdcacm_get_vfs(void);

/**
 * @brief 获取usbserialjtagvfs的指针。
 *
 * 在vfs_console中调用此函数，以获得usb_serial_jtag的vfs实现。
 *
 * @return 指向结构esp_vfs_nonblocking_console_t的指针
 */
const esp_vfs_t *esp_vfs_usb_serial_jtag_get_vfs(void);

/**
 * 注册虚拟文件系统。
 *
 * @param base_path  与文件系统关联的文件路径前缀。必须是以零结尾的C字符串，可以为空。如果不为空，则长度必须最多为ESP_VFS_PATH_MAX个字符，且至少为2个字符。名称必须以“/”开头，不得以“/“结尾。例如，“/data”或“/dev/spi”是有效的。然后调用这些VFSE来处理文件路径，例如“/data/myfile.txt”或“/dev/spi/0”。在空base_path的特殊情况下，将注册“回退”VFS。这样的VFS将处理与任何其他注册的VFS不匹配的路径。
 * @param len  base_path的长度。
 * @param vfs  指向esp_vfs_t的指针，该结构将系统调用映射到文件系统驱动程序函数。VFS组件不承担此指针的所有权。
 * @param ctx  如果vfs->标志设置了ESP_vfs_FLAG_CONTEXT_PTR，则应将指针传递给vfs函数。否则，为NULL。
 * @param vfs_index 获取vfs内容的索引。
 *
 * @return  如果成功，则返回ESP_OK。如果注册的VFS太多，则为ESP_ERR_NO_MEM。如果给定的参数无效，则返回ESP_ERR_INVALID_ARG。
 */
esp_err_t esp_vfs_register_common(const char *base_path, size_t len, const esp_vfs_t* vfs, void* ctx, int *vfs_index);

/**
 * 获取具有给定路径的vfs-fd。
 *
 * @param path 与文件系统关联的文件路径前缀。
 *
 * @return 指向与给定路径对应的“vfs_entry_t”的指针，该路径不能为NULL。
 */
const vfs_entry_t *get_vfs_for_path(const char *path);

/**
 * 使用给定的vfs索引获取vfs-fd。
 *
 * @param index VFS指数。
 *
 * @return 指向与给定路径对应的“vfs_entry_t”的指针，该路径不能为NULL。
 */
const vfs_entry_t *get_vfs_for_index(int index);

#ifdef __cplusplus
}
#endif

