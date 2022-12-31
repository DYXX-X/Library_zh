/* 版权所有2018 Espressif Systems（上海）私人有限公司
 *
 * 根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _MB_IFACE_COMMON_H
#define _MB_IFACE_COMMON_H

#include "driver/uart.h"                    // 对于UART类型

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("esp_check.h")
#include "esp_check.h"

#define MB_RETURN_ON_FALSE(a, err_code, tag, format, ...) ESP_RETURN_ON_FALSE(a, err_code, tag, format __VA_OPT__(,) __VA_ARGS__)

#else

// 如果不能包含esp_check，则使用自定义检查宏

#define MB_RETURN_ON_FALSE(a, err_code, tag, format, ...) do {                                         \
        if (!(a)) {                                                                              \
            ESP_LOGE(tag, "%s(%d): " format, __FUNCTION__, __LINE__ __VA_OPT__(,) __VA_ARGS__);        \
            return err_code;                                                                               \
        }                                                                                                  \
} while(0)

#endif

#define MB_CONTROLLER_STACK_SIZE            (CONFIG_FMB_CONTROLLER_STACK_SIZE)   // Modbus控制器的堆栈大小
#define MB_CONTROLLER_PRIORITY              (CONFIG_FMB_PORT_TASK_PRIO - 1)    // MB控制器任务的优先级

// 默认端口定义
#define MB_DEVICE_ADDRESS   (1)             // Modbus中的默认从属设备地址
#define MB_DEVICE_SPEED     (115200)        // 默认Modbus速度现在已硬定义
#define MB_UART_PORT        (UART_NUM_MAX - 1)  // 默认UART端口号
#define MB_PAR_INFO_TOUT    (10)            // 获取参数信息超时
#define MB_PARITY_NONE      (UART_PARITY_DISABLE)

// 下面的宏在将N字节数据传输到缓冲区时处理端序
#define _XFER_4_RD(dst, src) { \
    *(uint8_t *)(dst)++ = *(uint8_t*)(src + 1); \
    *(uint8_t *)(dst)++ = *(uint8_t*)(src + 0); \
    *(uint8_t *)(dst)++ = *(uint8_t*)(src + 3); \
    *(uint8_t *)(dst)++ = *(uint8_t*)(src + 2); \
    (src) += 4; \
}

#define _XFER_2_RD(dst, src) { \
    *(uint8_t *)(dst)++ = *(uint8_t *)(src + 1); \
    *(uint8_t *)(dst)++ = *(uint8_t *)(src + 0); \
    (src) += 2; \
}

#define _XFER_4_WR(dst, src) { \
    *(uint8_t *)(dst + 1) = *(uint8_t *)(src)++; \
    *(uint8_t *)(dst + 0) = *(uint8_t *)(src)++; \
    *(uint8_t *)(dst + 3) = *(uint8_t *)(src)++; \
    *(uint8_t *)(dst + 2) = *(uint8_t *)(src)++ ; \
}

#define _XFER_2_WR(dst, src) { \
    *(uint8_t *)(dst + 1) = *(uint8_t *)(src)++; \
    *(uint8_t *)(dst + 0) = *(uint8_t *)(src)++; \
}

/**
 * @brief 实际Modbus实现类型
 */
typedef enum
{
    MB_PORT_SERIAL_MASTER = 0x00,   /*!< Modbus端口型串行主机。*/
    MB_PORT_SERIAL_SLAVE,           /*!< Modbus端口型串行从站。*/
    MB_PORT_TCP_MASTER,             /*!< Modbus端口类型TCP主机。*/
    MB_PORT_TCP_SLAVE,              /*!< Modbus端口类型TCP从站。*/
    MB_PORT_COUNT,                  /*!< Modbus端口计数。*/
    MB_PORT_INACTIVE = 0xFF
} mb_port_type_t;

/**
 * @brief 参数通知的事件组
 */
typedef enum
{
    MB_EVENT_NO_EVENTS = 0x00,
    MB_EVENT_HOLDING_REG_WR = BIT0,         /*!< Modbus事件写入保持寄存器。*/
    MB_EVENT_HOLDING_REG_RD = BIT1,         /*!< Modbus事件读取保持寄存器。*/
    MB_EVENT_INPUT_REG_RD = BIT3,           /*!< Modbus事件读取输入寄存器。*/
    MB_EVENT_COILS_WR = BIT4,               /*!< Modbus事件写入线圈。*/
    MB_EVENT_COILS_RD = BIT5,               /*!< Modbus事件读取线圈。*/
    MB_EVENT_DISCRETE_RD = BIT6,            /*!< Modbus事件读取离散位。*/
    MB_EVENT_STACK_STARTED = BIT7           /*!< Modbus事件堆栈已启动*/
} mb_event_group_t;

/**
 * @brief Modbus参数类型
 */
typedef enum {
    MB_PARAM_HOLDING = 0x00,         /*!< Modbus保持寄存器。*/
    MB_PARAM_INPUT,                  /*!< Modbus输入寄存器。*/
    MB_PARAM_COIL,                   /*!< Modbus线圈。*/
    MB_PARAM_DISCRETE,               /*!< Modbus离散位。*/
    MB_PARAM_COUNT,
    MB_PARAM_UNKNOWN = 0xFF
} mb_param_type_t;

/*!
 * \简单的Modbus串行传输模式（RTU/ASCII）。
 */
typedef enum {
    MB_MODE_RTU,                     /*!< RTU传输模式。*/
    MB_MODE_ASCII,                   /*!< ASCII传输模式。*/
    MB_MODE_TCP,                     /*!< TCP通信模式。*/
    MB_MODE_UDP                      /*!< UDP通信模式。*/
} mb_mode_type_t;

/*!
 * \简单的Modbus TCP地址类型。
 */
typedef enum {
    MB_IPV4 = 0,                     /*!< TCP IPV4寻址*/
    MB_IPV6 = 1                      /*!< TCP IPV6寻址*/
} mb_tcp_addr_type_t;

/**
 * @brief 设置Modbus控制器的设备通信结构
 */
typedef union {
    // 串行通信结构
    struct {
        mb_mode_type_t mode;                    /*!< Modbus通信模式*/
        uint8_t slave_addr;                     /*!< Modbus从站地址字段（虚拟主站）*/
        uart_port_t port;                       /*!< Modbus通信端口（UART）编号*/
        uint32_t baudrate;                      /*!< Modbus波特率*/
        uart_parity_t parity;                   /*!< Modbus UART奇偶校验设置*/
        uint16_t dummy_port;                    /*!< 虚拟字段，未使用*/
    };
    // TCP/UDP通信结构
    struct {
        mb_mode_type_t ip_mode;                /*!< Modbus通信模式*/
        uint16_t ip_port;                      /*!< Modbus端口*/
        mb_tcp_addr_type_t ip_addr_type;       /*!< Modbus地址类型*/
        void* ip_addr;                         /*!< 用于连接的Modbus地址表*/
        void* ip_netif_ptr;                    /*!< Modbus网络接口*/
    };
} mb_communication_info_t;

/**
 * 通用接口方法类型
 */
typedef esp_err_t (*iface_init)(void**);        /*!< 接口方法init*/
typedef esp_err_t (*iface_destroy)(void);       /*!< 接口方法销毁*/
typedef esp_err_t (*iface_setup)(void*);        /*!< 接口方法设置*/
typedef esp_err_t (*iface_start)(void);         /*!< 接口方法启动*/

#ifdef __cplusplus
}
#endif

#endif // _MB_IFACE_COMMON_H

