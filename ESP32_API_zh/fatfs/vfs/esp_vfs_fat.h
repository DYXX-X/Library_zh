// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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
#include <stddef.h>
#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/sdmmc_types.h"
#include "driver/sdspi_host.h"
#include "ff.h"
#include "wear_levelling.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 向VFS组件注册FATFS
 *
 * 此函数在VFS中指定的基本路径上注册给定的FAT驱动器。如果只使用一个驱动器，fat_drive参数可以是空字符串。有关如何指定FAT驱动器，请参阅FATFS库文档。此函数还分配应用于f_mount调用的FATFS结构。
 *
 * @note 此函数不将驱动器装入FATFS，它只将POSIX和C标准库IO函数与FATFS连接。您需要将所需的驱动器单独装入FATFS。
 *
 * @param base_path  应注册FATFS的路径前缀
 * @param fat_drive  FATFS驱动器规范；如果仅使用一个驱动器，则可以是空字符串
 * @param max_files  同时可以打开的最大文件数
 * @param[out] out_fs  可用于FATFS f_mount调用的指向FATFS结构的指针通过此参数返回。
 * @return
 *      -成功时ESP_OK
 *      -如果已调用ESP_vfs_fat_register，则为ESP_ERR_INVALID_STATE
 *      -如果内存不足或已注册的VFS过多，则为ESP_ERR_NO_MEM
 */
esp_err_t esp_vfs_fat_register(const char* base_path, const char* fat_drive,
        size_t max_files, FATFS** out_fs);

/**
 * @brief 从VFS取消注册FATFS
 *
 * @note esp_vfs_fat_register返回的FATFS结构在此调用后被销毁。在调用esp_vfs_fat_unregister_ctx之前，请确保调用f_mount函数卸载它。此功能与上述功能的区别在于，此功能将释放正确的驱动器，而上述功能将释放最后注册的驱动器
 *
 * @param base_path     注册FATFS的路径前缀。这与调用esp_vfs_fat_register时使用的相同
 * @return
 *      -成功时ESP_OK
 *      -如果FATFS未在VFS中注册，则为ESP_ERR_INVALID_STATE
 */
esp_err_t esp_vfs_fat_unregister_path(const char* base_path);


/**
 * @brief esp_vfs_fat_sdmmc_mount和esp_vfs-fat_spiflash_mount函数的配置参数
 */
typedef struct {
    /**
     * 如果无法装载FAT分区，并且此参数为true，请创建分区表并格式化文件系统。
     */
    bool format_if_mount_failed;
    int max_files;                  ///<最大打开文件数
    /**
     * 如果设置了format_If_mount_failed，并且装载失败，请使用给定的分配单元大小格式化卡。必须是2的幂，介于扇区大小和128扇区大小之间。对于SD卡，扇区大小始终为512字节。对于wear_levelling，扇区大小由CONFIG_WL_sector_size选项确定。
     *
     * 当存储小文件时，使用更大的分配单元大小将导致更高的读/写性能和更高的开销。
     *
     * 将此字段设置为0将导致分配单位设置为扇区大小。
     */
    size_t allocation_unit_size;
} esp_vfs_fat_mount_config_t;

// 兼容性定义
typedef esp_vfs_fat_mount_config_t esp_vfs_fat_sdmmc_mount_config_t;

/**
 * @brief 在VFS中注册SD卡上获取FAT文件系统的方便功能
 *
 * 这是一个多功能一体的功能，可执行以下操作：
 * -使用host_config中的配置初始化SDMMC驱动程序或SPI驱动程序
 * -使用slot_config中的配置初始化SD卡
 * -使用FATFS库在SD卡上安装FAT分区，配置为mount_config
 * -用VFS注册FATFS库，前缀由base_prefix变量给定
 *
 * 此函数旨在使示例代码更紧凑。对于真实世界的应用程序，开发人员应该实现探测SD卡、定位和安装分区以及在VFS中注册FATFS的逻辑，并进行适当的错误检查和异常情况处理。
 *
 * @note 不推荐使用此API通过SDSPI安装卡。对于这种情况，请调用`esp_vfs_fat_sdspi_mount（）`。
 *
 * @param base_path     应该注册分区的路径（例如“/sdcard”）
 * @param host_config   指向描述SDMMC主机的结构的指针。使用SDMMC外围设备时，可以使用SDMMC_HOST_DEFAULT（）宏初始化此结构。使用SPI外设时，可以使用SDSPI_HOST_DEFAULT（）宏初始化此结构。
 * @param slot_config   指向具有插槽配置的结构的指针。对于SDMMC外围设备，将指针传递到使用SDMMC_slot_config_DEFAULT初始化的SDMMC_slot_config_t结构。（不推荐）对于SPI外设，将指针传递到使用sdspi_slot_config_DEFAULT（）初始化的sdspi_slot_config_t结构。
 * @param mount_config  指向带有用于安装FATFS的额外参数的结构的指针
 * @param[out] out_card  如果不是NULL，将通过此参数返回指向卡信息结构的指针
 * @return
 *      -成功时ESP_OK
 *      -如果已调用ESP_vfs_fat_sdmmc_mount，则为ESP_ERR_INVALID_STATE
 *      -如果无法分配内存，则为ESP_ERR_NO_MEM
 *      -如果无法装载分区，则为ESP_FAIL
 *      -SDMMC或SPI驱动程序、SDMMC协议或FATFS驱动程序的其他错误代码
 */
esp_err_t esp_vfs_fat_sdmmc_mount(const char* base_path,
    const sdmmc_host_t* host_config,
    const void* slot_config,
    const esp_vfs_fat_mount_config_t* mount_config,
    sdmmc_card_t** out_card);

/**
 * @brief 在VFS中注册SD卡上获取FAT文件系统的方便功能
 *
 * 这是一个多功能一体的功能，可执行以下操作：
 * -使用slot_config中的配置基于SPI Master驱动程序初始化SPI Master设备，并将其连接到已初始化的SPI总线。
 * -使用host_config_input中的配置初始化SD卡
 * -使用FATFS库在SD卡上安装FAT分区，配置为mount_config
 * -用VFS注册FATFS库，前缀由base_prefix变量给定
 *
 * 此函数旨在使示例代码更紧凑。对于真实世界的应用程序，开发人员应该实现探测SD卡、定位和安装分区以及在VFS中注册FATFS的逻辑，并进行适当的错误检查和异常情况处理。
 *
 * @note 此函数尝试将新的SD SPI设备连接到host_config中指定的总线。确保“host_config->slot”中指定的SPI总线之前已由“SPI_bus_initialize（）”初始化。
 *
 * @param base_path     应该注册分区的路径（例如“/sdcard”）
 * @param host_config_input 指向描述SDMMC主机的结构的指针。可以使用SDSPI_HOST_DEFAULT（）宏初始化此结构。
 * @param slot_config   指向具有插槽配置的结构的指针。对于SPI外设，将指针传递到使用sdspi_device_config_DEFAULT（）初始化的sdspi_device_config_t结构。
 * @param mount_config  指向带有用于安装FATFS的额外参数的结构的指针
 * @param[out] out_card 如果不为NULL，将通过此参数返回指向卡信息结构的指针。建议握住此手柄，如果需要，稍后使用它卸下卡。否则，建议不要同时使用多个卡，并在应用程序中卸载其中一个卡。
 * @return
 *      -成功时ESP_OK
 *      -如果已调用ESP_vfs_fat_sdmmc_mount，则为ESP_ERR_INVALID_STATE
 *      -如果无法分配内存，则为ESP_ERR_NO_MEM
 *      -如果无法装载分区，则为ESP_FAIL
 *      -SDMMC或SPI驱动程序、SDMMC协议或FATFS驱动程序的其他错误代码
 */
esp_err_t esp_vfs_fat_sdspi_mount(const char* base_path,
                                  const sdmmc_host_t* host_config_input,
                                  const sdspi_device_config_t* slot_config,
                                  const esp_vfs_fat_mount_config_t* mount_config,
                                  sdmmc_card_t** out_card);

/**
 * @brief 卸载FAT文件系统并释放使用esp_vfs_FAT_sdmmc_mount获取的资源
 *
 * @deprecated 请改用“esp_vfs_fat_sdcard_unmount（）”。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果尚未调用ESP_vfs_fat_sdmmc_mount，则为ESP_ERR_INVALID_STATE
 */
esp_err_t esp_vfs_fat_sdmmc_unmount(void);

/**
 * @brief 从FAT文件系统卸载SD卡并释放使用“esp_vfs_FAT_sdmmc_mount（）”或“esp_vfs_FAT_sdspi_mount”（）获取的资源`
 *
 * @return
 *      -成功时ESP_OK
 *      -如果卡参数未注册，则为ESP_ERR_INVALID_ARG
 *      -如果尚未调用ESP_vfs_fat_sdmmc_mount，则为ESP_ERR_INVALID_STATE
 */
esp_err_t esp_vfs_fat_sdcard_unmount(const char *base_path, sdmmc_card_t *card);

/**
 * @brief 在SPI闪存中初始化FAT文件系统并在VFS中注册的便利功能
 *
 * 这是一个多功能一体的功能，可执行以下操作：
 *
 * -找到定义了partition_label的分区。分区标签应在分区表中配置。
 * -初始化给定分区顶部的闪存磨损平衡库
 * -在闪存磨损均衡库的顶部使用FATFS库安装FAT分区
 * -用VFS注册FATFS库，前缀由base_prefix变量给定
 *
 * 此函数旨在使示例代码更紧凑。
 *
 * @param base_path        应安装FATFS分区的路径（例如“/spiflash”）
 * @param partition_label  应使用的分区的标签
 * @param mount_config     指向带有用于安装FATFS的额外参数的结构的指针
 * @param[out] wl_handle   磨损调平驱动器手柄
 * @return
 *      -成功时ESP_OK
 *      -如果分区表不包含具有给定标签的FATFS分区，则为ESP_ERR_NOT_FOUND
 *      -如果已调用ESP_vfs_fat_spiflash_mount，则为ESP_ERR_INVALID_STATE
 *      -如果无法分配内存，则为ESP_ERR_NO_MEM
 *      -如果无法装载分区，则为ESP_FAIL
 *      -来自磨损均衡库、SPI闪存驱动程序或FATFS驱动程序的其他错误代码
 */
esp_err_t esp_vfs_fat_spiflash_mount(const char* base_path,
    const char* partition_label,
    const esp_vfs_fat_mount_config_t* mount_config,
    wl_handle_t* wl_handle);

/**
 * @brief 卸载FAT文件系统并释放使用esp_vfs_FAT_spiflash_mount获取的资源
 *
 * @param base_path  应该注册分区的路径（例如“/spiflash”）
 * @param wl_handle  esp_vfs_fat_spiflash_mount返回的磨损调平驱动器手柄
 *
 * @return
 *      -成功时ESP_OK
 *      -如果尚未调用ESP_vfs_fat_spiflash_mount，则为ESP_ERR_INVALID_STATE
 */
 esp_err_t esp_vfs_fat_spiflash_unmount(const char* base_path, wl_handle_t wl_handle);


/**
 * @brief 初始化只读FAT文件系统并在VFS中注册的便利功能
 *
 * 这是一个多功能一体的功能，可执行以下操作：
 *
 * -找到定义了partition_label的分区。分区标签应在分区表中配置。
 * -使用FATFS库装载FAT分区
 * -用VFS注册FATFS库，前缀由base_prefix变量给定
 *
 * @note 使用此功能以只读模式安装FAT时，不使用磨损平衡。
 *
 * @param base_path        应安装FATFS分区的路径（例如“/spiflash”）
 * @param partition_label  应使用的分区的标签
 * @param mount_config     指向带有用于安装FATFS的额外参数的结构的指针
 * @return
 *      -成功时ESP_OK
 *      -如果分区表不包含具有给定标签的FATFS分区，则为ESP_ERR_NOT_FOUND
 *      -如果已为同一分区调用ESP_vfs_fat_rawflash_mount，则为ESP_ERR_INVALID_STATE
 *      -如果无法分配内存，则为ESP_ERR_NO_MEM
 *      -如果无法装载分区，则为ESP_FAIL
 *      -SPI闪存驱动程序或FATFS驱动程序的其他错误代码
 */
esp_err_t esp_vfs_fat_rawflash_mount(const char* base_path,
    const char* partition_label,
    const esp_vfs_fat_mount_config_t* mount_config);

/**
 * @brief 卸载FAT文件系统并释放使用esp_vfs_FAT_rawflash_mount获取的资源
 *
 * @param base_path  应该注册分区的路径（例如“/spiflash”）
 * @param partition_label 要卸载的分区的标签
 *
 * @return
 *      -成功时ESP_OK
 *      -如果尚未调用ESP_vfs_fat_spiflash_mount，则为ESP_ERR_INVALID_STATE
 */
 esp_err_t esp_vfs_fat_rawflash_unmount(const char* base_path, const char* partition_label);


#ifdef __cplusplus
}
#endif

