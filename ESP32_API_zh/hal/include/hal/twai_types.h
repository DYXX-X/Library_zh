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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "soc/soc_caps.h"

/**
 * @brief   TWAI常量
 */
#define TWAI_EXTD_ID_MASK               0x1FFFFFFF  /**＜29位扩展帧格式ID的位掩码*/
#define TWAI_STD_ID_MASK                0x7FF       /**＜11位标准帧格式ID的位掩码*/
#define TWAI_FRAME_MAX_DLC              8           /**<TWAI中允许的最大数据字节数*/
#define TWAI_FRAME_EXTD_ID_LEN_BYTES    4           /**<EFF ID需要4字节（29位）*/
#define TWAI_FRAME_STD_ID_LEN_BYTES     2           /**<SFF ID需要2个字节（11位）*/
#define TWAI_ERR_PASS_THRESH            128         /**<被动错误计数器阈值*/

/**@秒*/    //Doxy命令从文档中隐藏预处理器定义
/**
 * @brief   TWAI消息标志
 *
 * 消息标志用于指示发送/接收的消息类型。某些标志还指定传输类型。
 */
#define TWAI_MSG_FLAG_NONE              0x00        /**<无消息标志（标准帧格式）*/
#define TWAI_MSG_FLAG_EXTD              0x01        /**<扩展帧格式（29位ID）*/
#define TWAI_MSG_FLAG_RTR               0x02        /**<消息是远程帧*/
#define TWAI_MSG_FLAG_SS                0x04        /**<作为单次发射发射。未使用，已接收。*/
#define TWAI_MSG_FLAG_SELF              0x08        /**<作为自我接收请求发送。未使用，已接收。*/
#define TWAI_MSG_FLAG_DLC_NON_COMP      0x10        /**<消息的数据长度代码大于8。这将违反TWAI*/

#define TWAI_BRP_MAX    SOC_TWAI_BRP_MAX    /**<最大可配置BRP值*/
#define TWAI_BRP_MIN    SOC_TWAI_BRP_MIN    /**<最小可配置BRP值*/


/**
 * @brief 定时配置结构的初始化器宏
 *
 * 以下初始化器宏提供常见的比特率。这些宏将采样点放置在位时间的80%或67%。
 *
 * @note 这些定时值基于APB时钟为80MHz的假设
 * @note 可用比特率取决于芯片目标和修订。
 */
#if (SOC_TWAI_BRP_MAX > 256)
#define TWAI_TIMING_CONFIG_1KBITS()     {.brp = 4000, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_5KBITS()     {.brp = 800, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_10KBITS()    {.brp = 400, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .triple_sampling = false}
#endif
#if (SOC_TWAI_BRP_MAX > 128) || (CONFIG_ESP32_REV_MIN >= 2)
#define TWAI_TIMING_CONFIG_12_5KBITS()  {.brp = 256, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_16KBITS()    {.brp = 200, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_20KBITS()    {.brp = 200, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .triple_sampling = false}
#endif
#define TWAI_TIMING_CONFIG_25KBITS()    {.brp = 128, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_50KBITS()    {.brp = 80, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_100KBITS()   {.brp = 40, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_125KBITS()   {.brp = 32, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_250KBITS()   {.brp = 16, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_500KBITS()   {.brp = 8, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_800KBITS()   {.brp = 4, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .triple_sampling = false}
#define TWAI_TIMING_CONFIG_1MBITS()     {.brp = 4, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .triple_sampling = false}

/**
 * @brief   筛选器配置的初始化器宏接受所有ID
 */
#define TWAI_FILTER_CONFIG_ACCEPT_ALL() {.acceptance_code = 0, .acceptance_mask = 0xFFFFFFFF, .single_filter = true}
/**@结束秒*/

/**
 * @brief   TWAI控制器操作模式
 */
typedef enum {
    TWAI_MODE_NORMAL,               /**＜TWAI控制器可以发送/接收/确认消息的正常操作模式*/
    TWAI_MODE_NO_ACK,               /**<传输不需要确认。使用此模式进行自检*/
    TWAI_MODE_LISTEN_ONLY,          /**<TWAI控制器不会影响总线（无传输或确认），但可以接收消息*/
} twai_mode_t;

/**
 * @brief   存储TWAI消息的结构
 *
 * @note    标志成员已弃用
 */
typedef struct {
    union {
        struct {
            //出于兼容性原因，这些位的顺序必须与弃用的消息标志相匹配
            uint32_t extd: 1;           /**<扩展帧格式（29位ID）*/
            uint32_t rtr: 1;            /**<消息是远程帧*/
            uint32_t ss: 1;             /**<作为单次发射发射。未使用，已接收。*/
            uint32_t self: 1;           /**<作为自我接收请求发送。未使用，已接收。*/
            uint32_t dlc_non_comp: 1;   /**<消息的数据长度代码大于8。这将违反ISO 11898-1*/
            uint32_t reserved: 27;      /**<保留位*/
        };
        //待办事项：不推荐标志
        uint32_t flags;                 /**<不推荐：使用消息标志设置位的替代方法*/
    };
    uint32_t identifier;                /**<11或29位标识符*/
    uint8_t data_length_code;           /**<数据长度代码*/
    uint8_t data[TWAI_FRAME_MAX_DLC];    /**<数据字节（与RTR帧无关）*/
} twai_message_t;

/**
 * @brief   TWAI驱动程序的位定时配置结构
 *
 * @note    宏初始化器可用于此结构
 */
typedef struct {
    uint32_t brp;                   /**<波特率预分频器（即APB时钟分频器）。ESP32为2到128之间的任意偶数，ESP32S2为2到32768。对于ESP32 Rev 2或更高版本，也支持132到256之间的4的倍数*/
    uint8_t tseg_1;                 /**<计时段1（时间量的数量，介于1到16之间）*/
    uint8_t tseg_2;                 /**<计时段2（时间量的数量，1到8）*/
    uint8_t sjw;                    /**<同步跳转宽度（同步从1到4的最大时间量跳转）*/
    bool triple_sampling;           /**<当TWAI控制器采样一点时，启用三重采样*/
} twai_timing_config_t;

/**
 * @brief   TWAI驱动程序的验收过滤器配置结构（请参阅文档）
 *
 * @note    宏初始化器可用于此结构
 */
typedef struct {
    uint32_t acceptance_code;       /**<32位接受代码*/
    uint32_t acceptance_mask;       /**<32位接受掩码*/
    bool single_filter;             /**<使用单过滤器模式（请参阅文档）*/
} twai_filter_config_t;

#ifdef __cplusplus
}
#endif

