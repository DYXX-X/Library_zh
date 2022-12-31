// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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
#ifndef _SOC_GPIO_SD_STRUCT_H_
#define _SOC_GPIO_SD_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct gpio_sd_dev_s {
    union {
        struct {
            uint32_t duty:        8;
            uint32_t prescale:    8;
            uint32_t reserved16: 16;
        };
        uint32_t val;
    } channel[8];
    union {
        struct {
            uint32_t reserved0: 31;
            uint32_t clk_en:     1;
        };
        uint32_t val;
    } cg;
    union {
        struct {
            uint32_t reserved0: 31;
            uint32_t spi_swap:   1;
        };
        uint32_t val;
    } misc;
    union {
        struct {
            uint32_t date:      28;
            uint32_t reserved28: 4;
        };
        uint32_t val;
    } version;
} gpio_sd_dev_t;
extern gpio_sd_dev_t SIGMADELTA;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_GPIO_SD_STRUCT_H_ */

