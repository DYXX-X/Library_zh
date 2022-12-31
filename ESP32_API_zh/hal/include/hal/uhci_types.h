// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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



// 虽然UHCI驱动程序尚未发布，但此处定义了一些类型
// 供用户在HAL上开发。参见示例：controller_hci_art_esp32c3

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief UHCI逃逸序列
 */
typedef struct {
    uint8_t seper_chr;        /*!< 转义序列字符*/
    uint8_t sub_chr1;         /*!< 转义序列子字符1*/
    uint8_t sub_chr2;         /*!< 转义序列子字符2*/
    bool sub_chr_en;          /*!< 启用转义序列的子程序*/
} uhci_seper_chr_t;

/**
 * @brief UHCI软件流量控制
 */
typedef struct {
    uint8_t xon_chr;          /*!< XON字符*/
    uint8_t xon_sub1;         /*!< XON的子字符1*/
    uint8_t xon_sub2;         /*!< XON的子字符2*/
    uint8_t xoff_chr;         /*!< XOFF的字符2*/
    uint8_t xoff_sub1;        /*!< XOFF的子字符1*/
    uint8_t xoff_sub2;        /*!< XOFF的子字符2*/
    uint8_t flow_en;          /*!< 启用软件流控制*/
} uhci_swflow_ctrl_sub_chr_t;

#ifdef __cplusplus
}
#endif

