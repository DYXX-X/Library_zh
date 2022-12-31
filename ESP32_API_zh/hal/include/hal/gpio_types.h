// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#include "soc/gpio_periph.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    GPIO_PORT_0 = 0,
    GPIO_PORT_MAX,
} gpio_port_t;

#define GPIO_SEL_0              (BIT(0))                         /*!< 已选择插针0*/
#define GPIO_SEL_1              (BIT(1))                         /*!< 已选择针脚1*/
#define GPIO_SEL_2              (BIT(2))                         /*!< 已选择针脚2*/
#define GPIO_SEL_3              (BIT(3))                         /*!< 已选择针脚3*/
#define GPIO_SEL_4              (BIT(4))                         /*!< 已选择针脚4*/
#define GPIO_SEL_5              (BIT(5))                         /*!< 已选择针脚5*/
#define GPIO_SEL_6              (BIT(6))                         /*!< 已选择针脚6*/
#define GPIO_SEL_7              (BIT(7))                         /*!< 已选择针脚7*/
#define GPIO_SEL_8              (BIT(8))                         /*!< 已选择针脚8*/
#define GPIO_SEL_9              (BIT(9))                         /*!< 已选择针脚9*/
#define GPIO_SEL_10             (BIT(10))                        /*!< 已选择针脚10*/
#define GPIO_SEL_11             (BIT(11))                        /*!< 已选择针脚11*/
#define GPIO_SEL_12             (BIT(12))                        /*!< 已选择针脚12*/
#define GPIO_SEL_13             (BIT(13))                        /*!< 已选择针脚13*/
#define GPIO_SEL_14             (BIT(14))                        /*!< 已选择针脚14*/
#define GPIO_SEL_15             (BIT(15))                        /*!< 已选择针脚15*/
#define GPIO_SEL_16             (BIT(16))                        /*!< 已选择针脚16*/
#define GPIO_SEL_17             (BIT(17))                        /*!< 已选择针脚17*/
#define GPIO_SEL_18             (BIT(18))                        /*!< 已选择针脚18*/
#define GPIO_SEL_19             (BIT(19))                        /*!< 已选择针脚19*/
#define GPIO_SEL_20             (BIT(20))                        /*!< 已选择针脚20*/
#define GPIO_SEL_21             (BIT(21))                        /*!< 已选择针脚21*/
#if CONFIG_IDF_TARGET_ESP32
#define GPIO_SEL_22             (BIT(22))                        /*!< 已选择针脚22*/
#define GPIO_SEL_23             (BIT(23))                        /*!< 已选择针脚23*/

#define GPIO_SEL_25             (BIT(25))                        /*!< 已选择针脚25*/
#endif
#define GPIO_SEL_26             (BIT(26))                        /*!< 已选择针脚26*/
#define GPIO_SEL_27             (BIT(27))                        /*!< 已选择针脚27*/
#define GPIO_SEL_28             (BIT(28))                        /*!< 已选择针脚28*/
#define GPIO_SEL_29             (BIT(29))                        /*!< 已选择针脚29*/
#define GPIO_SEL_30             (BIT(30))                        /*!< 已选择针脚30*/
#define GPIO_SEL_31             (BIT(31))                        /*!< 已选择针脚31*/
#define GPIO_SEL_32             ((uint64_t)(((uint64_t)1)<<32))  /*!< 已选择针脚32*/
#define GPIO_SEL_33             ((uint64_t)(((uint64_t)1)<<33))  /*!< 已选择针脚33*/
#define GPIO_SEL_34             ((uint64_t)(((uint64_t)1)<<34))  /*!< 已选择针脚34*/
#define GPIO_SEL_35             ((uint64_t)(((uint64_t)1)<<35))  /*!< 已选择针脚35*/
#define GPIO_SEL_36             ((uint64_t)(((uint64_t)1)<<36))  /*!< 已选择针脚36*/
#define GPIO_SEL_37             ((uint64_t)(((uint64_t)1)<<37))  /*!< 已选择针脚37*/
#define GPIO_SEL_38             ((uint64_t)(((uint64_t)1)<<38))  /*!< 已选择针脚38*/
#define GPIO_SEL_39             ((uint64_t)(((uint64_t)1)<<39))  /*!< 已选择针脚39*/
#if SOC_GPIO_PIN_COUNT > 40
#define GPIO_SEL_40             ((uint64_t)(((uint64_t)1)<<40))  /*!< 已选择针脚40*/
#define GPIO_SEL_41             ((uint64_t)(((uint64_t)1)<<41))  /*!< 已选择针脚41*/
#define GPIO_SEL_42             ((uint64_t)(((uint64_t)1)<<42))  /*!< 已选择针脚42*/
#define GPIO_SEL_43             ((uint64_t)(((uint64_t)1)<<43))  /*!< 已选择针脚43*/
#define GPIO_SEL_44             ((uint64_t)(((uint64_t)1)<<44))  /*!< 已选择针脚44*/
#define GPIO_SEL_45             ((uint64_t)(((uint64_t)1)<<45))  /*!< 已选择针脚45*/
#define GPIO_SEL_46             ((uint64_t)(((uint64_t)1)<<46))  /*!< 已选择针脚46*/
#if CONFIG_IDF_TARGET_ESP32S3
#define GPIO_SEL_47             ((uint64_t)(((uint64_t)1)<<47))  /*!< 已选择针脚47*/
#define GPIO_SEL_48             ((uint64_t)(((uint64_t)1)<<48))  /*!< 已选择针脚48*/
#endif
#endif

#define GPIO_PIN_REG_0          IO_MUX_GPIO0_REG
#define GPIO_PIN_REG_1          IO_MUX_GPIO1_REG
#define GPIO_PIN_REG_2          IO_MUX_GPIO2_REG
#define GPIO_PIN_REG_3          IO_MUX_GPIO3_REG
#define GPIO_PIN_REG_4          IO_MUX_GPIO4_REG
#define GPIO_PIN_REG_5          IO_MUX_GPIO5_REG
#define GPIO_PIN_REG_6          IO_MUX_GPIO6_REG
#define GPIO_PIN_REG_7          IO_MUX_GPIO7_REG
#define GPIO_PIN_REG_8          IO_MUX_GPIO8_REG
#define GPIO_PIN_REG_9          IO_MUX_GPIO9_REG
#define GPIO_PIN_REG_10          IO_MUX_GPIO10_REG
#define GPIO_PIN_REG_11          IO_MUX_GPIO11_REG
#define GPIO_PIN_REG_12          IO_MUX_GPIO12_REG
#define GPIO_PIN_REG_13          IO_MUX_GPIO13_REG
#define GPIO_PIN_REG_14          IO_MUX_GPIO14_REG
#define GPIO_PIN_REG_15          IO_MUX_GPIO15_REG
#define GPIO_PIN_REG_16          IO_MUX_GPIO16_REG
#define GPIO_PIN_REG_17          IO_MUX_GPIO17_REG
#define GPIO_PIN_REG_18          IO_MUX_GPIO18_REG
#define GPIO_PIN_REG_19          IO_MUX_GPIO19_REG
#define GPIO_PIN_REG_20          IO_MUX_GPIO20_REG
#define GPIO_PIN_REG_21          IO_MUX_GPIO21_REG
#define GPIO_PIN_REG_22          IO_MUX_GPIO22_REG
#define GPIO_PIN_REG_23          IO_MUX_GPIO23_REG
#define GPIO_PIN_REG_24          IO_MUX_GPIO24_REG
#define GPIO_PIN_REG_25          IO_MUX_GPIO25_REG
#define GPIO_PIN_REG_26          IO_MUX_GPIO26_REG
#define GPIO_PIN_REG_27          IO_MUX_GPIO27_REG
#define GPIO_PIN_REG_28          IO_MUX_GPIO28_REG
#define GPIO_PIN_REG_29          IO_MUX_GPIO29_REG
#define GPIO_PIN_REG_30          IO_MUX_GPIO30_REG
#define GPIO_PIN_REG_31          IO_MUX_GPIO31_REG
#define GPIO_PIN_REG_32          IO_MUX_GPIO32_REG
#define GPIO_PIN_REG_33          IO_MUX_GPIO33_REG
#define GPIO_PIN_REG_34          IO_MUX_GPIO34_REG
#define GPIO_PIN_REG_35          IO_MUX_GPIO35_REG
#define GPIO_PIN_REG_36          IO_MUX_GPIO36_REG
#define GPIO_PIN_REG_37          IO_MUX_GPIO37_REG
#define GPIO_PIN_REG_38          IO_MUX_GPIO38_REG
#define GPIO_PIN_REG_39          IO_MUX_GPIO39_REG
#define GPIO_PIN_REG_40          IO_MUX_GPIO40_REG
#define GPIO_PIN_REG_41          IO_MUX_GPIO41_REG
#define GPIO_PIN_REG_42          IO_MUX_GPIO42_REG
#define GPIO_PIN_REG_43          IO_MUX_GPIO43_REG
#define GPIO_PIN_REG_44          IO_MUX_GPIO44_REG
#define GPIO_PIN_REG_45          IO_MUX_GPIO45_REG
#define GPIO_PIN_REG_46          IO_MUX_GPIO46_REG
#define GPIO_PIN_REG_47          IO_MUX_GPIO47_REG
#define GPIO_PIN_REG_48          IO_MUX_GPIO48_REG

#if CONFIG_IDF_TARGET_ESP32
typedef enum {
    GPIO_NUM_NC = -1,    /*!< 用于信号未连接到S/W*/
    GPIO_NUM_0 = 0,     /*!< GPIO0，输入和输出*/
    GPIO_NUM_1 = 1,     /*!< GPIO1，输入和输出*/
    GPIO_NUM_2 = 2,     /*!< GPIO2，输入和输出*/
    GPIO_NUM_3 = 3,     /*!< GPIO3，输入和输出*/
    GPIO_NUM_4 = 4,     /*!< GPIO4，输入和输出*/
    GPIO_NUM_5 = 5,     /*!< GPIO5，输入和输出*/
    GPIO_NUM_6 = 6,     /*!< GPIO6，输入和输出*/
    GPIO_NUM_7 = 7,     /*!< GPIO7，输入和输出*/
    GPIO_NUM_8 = 8,     /*!< GPIO8，输入和输出*/
    GPIO_NUM_9 = 9,     /*!< GPIO9，输入和输出*/
    GPIO_NUM_10 = 10,   /*!< GPIO10，输入和输出*/
    GPIO_NUM_11 = 11,   /*!< GPIO11，输入和输出*/
    GPIO_NUM_12 = 12,   /*!< GPIO12，输入和输出*/
    GPIO_NUM_13 = 13,   /*!< GPIO13，输入和输出*/
    GPIO_NUM_14 = 14,   /*!< GPIO14，输入和输出*/
    GPIO_NUM_15 = 15,   /*!< GPIO15，输入和输出*/
    GPIO_NUM_16 = 16,   /*!< GPIO16，输入和输出*/
    GPIO_NUM_17 = 17,   /*!< GPIO17，输入和输出*/
    GPIO_NUM_18 = 18,   /*!< GPIO18，输入和输出*/
    GPIO_NUM_19 = 19,   /*!< GPIO19，输入和输出*/
    GPIO_NUM_20 = 20,   /*!< GPIO20，输入和输出*/
    GPIO_NUM_21 = 21,   /*!< GPIO21，输入和输出*/
    GPIO_NUM_22 = 22,   /*!< GPIO22，输入和输出*/
    GPIO_NUM_23 = 23,   /*!< GPIO23，输入和输出*/
    GPIO_NUM_25 = 25,   /*!< GPIO25，输入和输出*/
    GPIO_NUM_26 = 26,   /*!< GPIO26，输入和输出*/
    GPIO_NUM_27 = 27,   /*!< GPIO27，输入和输出*/
    GPIO_NUM_28 = 28,   /*!< GPIO28，输入和输出*/
    GPIO_NUM_29 = 29,   /*!< GPIO29，输入和输出*/
    GPIO_NUM_30 = 30,   /*!< GPIO30，输入和输出*/
    GPIO_NUM_31 = 31,   /*!< GPIO31，输入和输出*/
    GPIO_NUM_32 = 32,   /*!< GPIO32，输入和输出*/
    GPIO_NUM_33 = 33,   /*!< GPIO33，输入和输出*/
    GPIO_NUM_34 = 34,   /*!< GPIO34，仅输入模式*/
    GPIO_NUM_35 = 35,   /*!< GPIO35，仅输入模式*/
    GPIO_NUM_36 = 36,   /*!< GPIO36，仅输入模式*/
    GPIO_NUM_37 = 37,   /*!< GPIO37，仅输入模式*/
    GPIO_NUM_38 = 38,   /*!< GPIO38，仅输入模式*/
    GPIO_NUM_39 = 39,   /*!< GPIO39，仅输入模式*/
    GPIO_NUM_MAX,
/**@结束秒*/
} gpio_num_t;
#elif CONFIG_IDF_TARGET_ESP32S2
typedef enum {
    GPIO_NUM_NC = -1,    /*!< 用于信号未连接到S/W*/
    GPIO_NUM_0 = 0,     /*!< GPIO0，输入和输出*/
    GPIO_NUM_1 = 1,     /*!< GPIO1，输入和输出*/
    GPIO_NUM_2 = 2,     /*!< GPIO2，输入和输出*/
    GPIO_NUM_3 = 3,     /*!< GPIO3，输入和输出*/
    GPIO_NUM_4 = 4,     /*!< GPIO4，输入和输出*/
    GPIO_NUM_5 = 5,     /*!< GPIO5，输入和输出*/
    GPIO_NUM_6 = 6,     /*!< GPIO6，输入和输出*/
    GPIO_NUM_7 = 7,     /*!< GPIO7，输入和输出*/
    GPIO_NUM_8 = 8,     /*!< GPIO8，输入和输出*/
    GPIO_NUM_9 = 9,     /*!< GPIO9，输入和输出*/
    GPIO_NUM_10 = 10,   /*!< GPIO10，输入和输出*/
    GPIO_NUM_11 = 11,   /*!< GPIO11，输入和输出*/
    GPIO_NUM_12 = 12,   /*!< GPIO12，输入和输出*/
    GPIO_NUM_13 = 13,   /*!< GPIO13，输入和输出*/
    GPIO_NUM_14 = 14,   /*!< GPIO14，输入和输出*/
    GPIO_NUM_15 = 15,   /*!< GPIO15，输入和输出*/
    GPIO_NUM_16 = 16,   /*!< GPIO16，输入和输出*/
    GPIO_NUM_17 = 17,   /*!< GPIO17，输入和输出*/
    GPIO_NUM_18 = 18,   /*!< GPIO18，输入和输出*/
    GPIO_NUM_19 = 19,   /*!< GPIO19，输入和输出*/
    GPIO_NUM_20 = 20,   /*!< GPIO20，输入和输出*/
    GPIO_NUM_21 = 21,   /*!< GPIO21，输入和输出*/
    GPIO_NUM_26 = 26,   /*!< GPIO26，输入和输出*/
    GPIO_NUM_27 = 27,   /*!< GPIO27，输入和输出*/
    GPIO_NUM_28 = 28,   /*!< GPIO28，输入和输出*/
    GPIO_NUM_29 = 29,   /*!< GPIO29，输入和输出*/
    GPIO_NUM_30 = 30,   /*!< GPIO30，输入和输出*/
    GPIO_NUM_31 = 31,   /*!< GPIO31，输入和输出*/
    GPIO_NUM_32 = 32,   /*!< GPIO32，输入和输出*/
    GPIO_NUM_33 = 33,   /*!< GPIO33，输入和输出*/
    GPIO_NUM_34 = 34,   /*!< GPIO34，输入和输出*/
    GPIO_NUM_35 = 35,   /*!< GPIO35，输入和输出*/
    GPIO_NUM_36 = 36,   /*!< GPIO36，输入和输出*/
    GPIO_NUM_37 = 37,   /*!< GPIO37，输入和输出*/
    GPIO_NUM_38 = 38,   /*!< GPIO38，输入和输出*/
    GPIO_NUM_39 = 39,   /*!< GPIO39，输入和输出*/
    GPIO_NUM_40 = 40,   /*!< GPIO40，输入和输出*/
    GPIO_NUM_41 = 41,   /*!< GPIO41，输入和输出*/
    GPIO_NUM_42 = 42,   /*!< GPIO42，输入和输出*/
    GPIO_NUM_43 = 43,   /*!< GPIO43，输入和输出*/
    GPIO_NUM_44 = 44,   /*!< GPIO44，输入和输出*/
    GPIO_NUM_45 = 45,   /*!< GPIO45，输入和输出*/
    GPIO_NUM_46 = 46,   /*!< GPIO46，仅输入模式*/
    GPIO_NUM_MAX,
/**@结束秒*/
} gpio_num_t;
#elif CONFIG_IDF_TARGET_ESP32S3
typedef enum {
    GPIO_NUM_NC = -1,    /*!< 用于信号未连接到S/W*/
    GPIO_NUM_0 = 0,     /*!< GPIO0，输入和输出*/
    GPIO_NUM_1 = 1,     /*!< GPIO1，输入和输出*/
    GPIO_NUM_2 = 2,     /*!< GPIO2，输入和输出*/
    GPIO_NUM_3 = 3,     /*!< GPIO3，输入和输出*/
    GPIO_NUM_4 = 4,     /*!< GPIO4，输入和输出*/
    GPIO_NUM_5 = 5,     /*!< GPIO5，输入和输出*/
    GPIO_NUM_6 = 6,     /*!< GPIO6，输入和输出*/
    GPIO_NUM_7 = 7,     /*!< GPIO7，输入和输出*/
    GPIO_NUM_8 = 8,     /*!< GPIO8，输入和输出*/
    GPIO_NUM_9 = 9,     /*!< GPIO9，输入和输出*/
    GPIO_NUM_10 = 10,   /*!< GPIO10，输入和输出*/
    GPIO_NUM_11 = 11,   /*!< GPIO11，输入和输出*/
    GPIO_NUM_12 = 12,   /*!< GPIO12，输入和输出*/
    GPIO_NUM_13 = 13,   /*!< GPIO13，输入和输出*/
    GPIO_NUM_14 = 14,   /*!< GPIO14，输入和输出*/
    GPIO_NUM_15 = 15,   /*!< GPIO15，输入和输出*/
    GPIO_NUM_16 = 16,   /*!< GPIO16，输入和输出*/
    GPIO_NUM_17 = 17,   /*!< GPIO17，输入和输出*/
    GPIO_NUM_18 = 18,   /*!< GPIO18，输入和输出*/
    GPIO_NUM_19 = 19,   /*!< GPIO19，输入和输出*/
    GPIO_NUM_20 = 20,   /*!< GPIO20，输入和输出*/
    GPIO_NUM_21 = 21,   /*!< GPIO21，输入和输出*/
    GPIO_NUM_26 = 26,   /*!< GPIO26，输入和输出*/
    GPIO_NUM_27 = 27,   /*!< GPIO27，输入和输出*/
    GPIO_NUM_28 = 28,   /*!< GPIO28，输入和输出*/
    GPIO_NUM_29 = 29,   /*!< GPIO29，输入和输出*/
    GPIO_NUM_30 = 30,   /*!< GPIO30，输入和输出*/
    GPIO_NUM_31 = 31,   /*!< GPIO31，输入和输出*/
    GPIO_NUM_32 = 32,   /*!< GPIO32，输入和输出*/
    GPIO_NUM_33 = 33,   /*!< GPIO33，输入和输出*/
    GPIO_NUM_34 = 34,   /*!< GPIO34，输入和输出*/
    GPIO_NUM_35 = 35,   /*!< GPIO35，输入和输出*/
    GPIO_NUM_36 = 36,   /*!< GPIO36，输入和输出*/
    GPIO_NUM_37 = 37,   /*!< GPIO37，输入和输出*/
    GPIO_NUM_38 = 38,   /*!< GPIO38，输入和输出*/
    GPIO_NUM_39 = 39,   /*!< GPIO39，输入和输出*/
    GPIO_NUM_40 = 40,   /*!< GPIO40，输入和输出*/
    GPIO_NUM_41 = 41,   /*!< GPIO41，输入和输出*/
    GPIO_NUM_42 = 42,   /*!< GPIO42，输入和输出*/
    GPIO_NUM_43 = 43,   /*!< GPIO43，输入和输出*/
    GPIO_NUM_44 = 44,   /*!< GPIO44，输入和输出*/
    GPIO_NUM_45 = 45,   /*!< GPIO45，输入和输出*/
    GPIO_NUM_46 = 46,   /*!< GPIO46，输入和输出*/
    GPIO_NUM_47 = 47,   /*!< GPIO47，输入和输出*/
    GPIO_NUM_48 = 48,   /*!< GPIO48，输入和输出*/
    GPIO_NUM_MAX,
/**@结束秒*/
} gpio_num_t;
#elif CONFIG_IDF_TARGET_ESP32C3
typedef enum {
    GPIO_NUM_NC = -1,    /*!< 用于信号未连接到S/W*/
    GPIO_NUM_0 = 0,     /*!< GPIO0，输入和输出*/
    GPIO_NUM_1 = 1,     /*!< GPIO1，输入和输出*/
    GPIO_NUM_2 = 2,     /*!< GPIO2，输入和输出*/
    GPIO_NUM_3 = 3,     /*!< GPIO3，输入和输出*/
    GPIO_NUM_4 = 4,     /*!< GPIO4，输入和输出*/
    GPIO_NUM_5 = 5,     /*!< GPIO5，输入和输出*/
    GPIO_NUM_6 = 6,     /*!< GPIO6，输入和输出*/
    GPIO_NUM_7 = 7,     /*!< GPIO7，输入和输出*/
    GPIO_NUM_8 = 8,     /*!< GPIO8，输入和输出*/
    GPIO_NUM_9 = 9,     /*!< GPIO9，输入和输出*/
    GPIO_NUM_10 = 10,   /*!< GPIO10，输入和输出*/
    GPIO_NUM_11 = 11,   /*!< GPIO11，输入和输出*/
    GPIO_NUM_12 = 12,   /*!< GPIO12，输入和输出*/
    GPIO_NUM_13 = 13,   /*!< GPIO13，输入和输出*/
    GPIO_NUM_14 = 14,   /*!< GPIO14，输入和输出*/
    GPIO_NUM_15 = 15,   /*!< GPIO15，输入和输出*/
    GPIO_NUM_16 = 16,   /*!< GPIO16，输入和输出*/
    GPIO_NUM_17 = 17,   /*!< GPIO17，输入和输出*/
    GPIO_NUM_18 = 18,   /*!< GPIO18，输入和输出*/
    GPIO_NUM_19 = 19,   /*!< GPIO19，输入和输出*/
    GPIO_NUM_20 = 20,   /*!< GPIO20，输入和输出*/
    GPIO_NUM_21 = 21,   /*!< GPIO21，输入和输出*/
    GPIO_NUM_MAX,
/**@结束秒*/
} gpio_num_t;
#elif CONFIG_IDF_TARGET_ESP32H2
typedef enum {
    GPIO_NUM_NC = -1,    /*!< 用于信号未连接到S/W*/
    GPIO_NUM_0 = 0,     /*!< GPIO0，输入和输出*/
    GPIO_NUM_1 = 1,     /*!< GPIO1，输入和输出*/
    GPIO_NUM_2 = 2,     /*!< GPIO2，输入和输出*/
    GPIO_NUM_3 = 3,     /*!< GPIO3，输入和输出*/
    GPIO_NUM_4 = 4,     /*!< GPIO4，输入和输出*/
    GPIO_NUM_5 = 5,     /*!< GPIO5，输入和输出*/
    GPIO_NUM_6 = 6,     /*!< GPIO6，输入和输出*/
    GPIO_NUM_7 = 7,     /*!< GPIO7，输入和输出*/
    GPIO_NUM_8 = 8,     /*!< GPIO8，输入和输出*/
    GPIO_NUM_9 = 9,     /*!< GPIO9，输入和输出*/
    GPIO_NUM_10 = 10,   /*!< GPIO10，输入和输出*/
    GPIO_NUM_11 = 11,   /*!< GPIO11，输入和输出*/
    GPIO_NUM_12 = 12,   /*!< GPIO12，输入和输出*/
    GPIO_NUM_13 = 13,   /*!< GPIO13，输入和输出*/
    GPIO_NUM_14 = 14,   /*!< GPIO14，输入和输出*/
    GPIO_NUM_15 = 15,   /*!< GPIO15，输入和输出*/
    GPIO_NUM_16 = 16,   /*!< GPIO16，输入和输出*/
    GPIO_NUM_17 = 17,   /*!< GPIO17，输入和输出*/
    GPIO_NUM_18 = 18,   /*!< GPIO18，输入和输出*/
    GPIO_NUM_19 = 19,   /*!< GPIO19，输入和输出*/
    GPIO_NUM_20 = 20,   /*!< GPIO20，输入和输出*/
    GPIO_NUM_21 = 21,   /*!< GPIO21，输入和输出*/
    GPIO_NUM_22 = 22,   /*!< GPIO22，输入和输出*/
    GPIO_NUM_26 = 26,   /*!< GPIO26，输入和输出*/
    GPIO_NUM_27 = 27,   /*!< GPIO27，输入和输出*/
    GPIO_NUM_28 = 28,   /*!< GPIO28，输入和输出*/
    GPIO_NUM_29 = 29,   /*!< GPIO29，输入和输出*/
    GPIO_NUM_30 = 30,   /*!< GPIO30，输入和输出*/
    GPIO_NUM_31 = 31,   /*!< GPIO31，输入和输出*/
    GPIO_NUM_32 = 32,   /*!< GPIO32，输入和输出*/
    GPIO_NUM_33 = 33,   /*!< GPIO33，输入和输出*/
    GPIO_NUM_34 = 34,   /*!< GPIO34，输入和输出*/
    GPIO_NUM_35 = 35,   /*!< GPIO35，输入和输出*/
    GPIO_NUM_36 = 36,   /*!< GPIO36，输入和输出*/
    GPIO_NUM_37 = 37,   /*!< GPIO37，输入和输出*/
    GPIO_NUM_38 = 38,   /*!< GPIO38，输入和输出*/
    GPIO_NUM_39 = 39,   /*!< GPIO39，输入和输出*/
    GPIO_NUM_40 = 40,   /*!< GPIO40，输入和输出*/
    GPIO_NUM_MAX,
/**@结束秒*/
} gpio_num_t;
#endif

typedef enum {
    GPIO_INTR_DISABLE = 0,     /*!< 禁用GPIO中断*/
    GPIO_INTR_POSEDGE = 1,     /*!< GPIO中断类型：上升沿*/
    GPIO_INTR_NEGEDGE = 2,     /*!< GPIO中断类型：下降沿*/
    GPIO_INTR_ANYEDGE = 3,     /*!< GPIO中断类型：上升沿和下降沿*/
    GPIO_INTR_LOW_LEVEL = 4,   /*!< GPIO中断类型：输入低电平触发*/
    GPIO_INTR_HIGH_LEVEL = 5,  /*!< GPIO中断类型：输入高电平触发*/
    GPIO_INTR_MAX,
} gpio_int_type_t;

/**@秒*/
#define GPIO_MODE_DEF_DISABLE         (0)
#define GPIO_MODE_DEF_INPUT           (BIT0)    ///<输入位掩码
#define GPIO_MODE_DEF_OUTPUT          (BIT1)    ///<输出位掩码
#define GPIO_MODE_DEF_OD              (BIT2)    ///<OD模式的位掩码
/**@结束秒*/

typedef enum {
    GPIO_MODE_DISABLE = GPIO_MODE_DEF_DISABLE,                                                         /*!< GPIO模式：禁用输入和输出*/
    GPIO_MODE_INPUT = GPIO_MODE_DEF_INPUT,                                                             /*!< GPIO模式：仅输入*/
    GPIO_MODE_OUTPUT = GPIO_MODE_DEF_OUTPUT,                                                           /*!< GPIO模式：仅输出模式*/
    GPIO_MODE_OUTPUT_OD = ((GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)),                               /*!< GPIO模式：仅在漏极开路模式下输出*/
    GPIO_MODE_INPUT_OUTPUT_OD = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)), /*!< GPIO模式：具有漏极开路模式的输出和输入*/
    GPIO_MODE_INPUT_OUTPUT = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT)),                         /*!< GPIO模式：输出和输入模式*/
} gpio_mode_t;

typedef enum {
    GPIO_PULLUP_DISABLE = 0x0,     /*!< 禁用GPIO上拉电阻器*/
    GPIO_PULLUP_ENABLE = 0x1,      /*!< 启用GPIO上拉电阻器*/
} gpio_pullup_t;

typedef enum {
    GPIO_PULLDOWN_DISABLE = 0x0,   /*!< 禁用GPIO下拉电阻器*/
    GPIO_PULLDOWN_ENABLE = 0x1,    /*!< 启用GPIO下拉电阻器*/
} gpio_pulldown_t;

/**
 * @brief GPIO_config功能的GPIO焊盘配置参数
 */
typedef struct {
    uint64_t pin_bit_mask;          /*!< GPIO引脚：设置位掩码，每个位映射到GPIO*/
    gpio_mode_t mode;               /*!< GPIO模式：设置输入/输出模式*/
    gpio_pullup_t pull_up_en;       /*!< GPIO上拉*/
    gpio_pulldown_t pull_down_en;   /*!< GPIO下拉*/
    gpio_int_type_t intr_type;      /*!< GPIO中断类型*/
} gpio_config_t;

typedef enum {
    GPIO_PULLUP_ONLY,               /*!< 衬垫上拉*/
    GPIO_PULLDOWN_ONLY,             /*!< 衬垫下拉*/
    GPIO_PULLUP_PULLDOWN,           /*!< 衬垫上拉+下拉*/
    GPIO_FLOATING,                  /*!< 极板浮动*/
} gpio_pull_mode_t;

typedef enum {
    GPIO_DRIVE_CAP_0       = 0,    /*!< 极板驱动能力：弱*/
    GPIO_DRIVE_CAP_1       = 1,    /*!< 衬垫驱动能力：更强*/
    GPIO_DRIVE_CAP_2       = 2,    /*!< 极板驱动能力：中等*/
    GPIO_DRIVE_CAP_DEFAULT = 2,    /*!< 极板驱动能力：中等*/
    GPIO_DRIVE_CAP_3       = 3,    /*!< 极板驱动能力：最强*/
    GPIO_DRIVE_CAP_MAX,
} gpio_drive_cap_t;

typedef void (*gpio_isr_t)(void *);

#ifdef __cplusplus
}
#endif

