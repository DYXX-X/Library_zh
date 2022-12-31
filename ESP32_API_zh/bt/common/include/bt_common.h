
// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#ifndef _BT_COMMON_H_
#define _BT_COMMON_H_

#include <assert.h>
#include "bt_user_config.h"
#include "esp_log.h"

#ifndef FALSE
#define FALSE  false
#endif

#ifndef TRUE
#define TRUE   true
#endif


#if (UC_BT_BLUFI_ENABLE)
#define BLUFI_INCLUDED              TRUE
#else
#define BLUFI_INCLUDED              FALSE
#endif

#ifdef CONFIG_BT_BLUEDROID_ENABLED
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gatt_defs.h"
#define ESP_BLE_HOST_STATUS_ENABLED ESP_BLUEDROID_STATUS_ENABLED
#define ESP_BLE_HOST_STATUS_CHECK(status) ESP_BLUEDROID_STATUS_CHECK(status)
#else
#define ESP_BLE_HOST_STATUS_ENABLED 0
#define ESP_BLE_HOST_STATUS_CHECK(status)  do {} while (0)
#endif

#ifndef BT_QUEUE_CONGEST_SIZE
#define BT_QUEUE_CONGEST_SIZE    40
#endif

#define BTC_INITIAL_TRACE_LEVEL             UC_BT_LOG_BTC_TRACE_LEVEL
#define OSI_INITIAL_TRACE_LEVEL             UC_BT_LOG_OSI_TRACE_LEVEL
#define BLUFI_INITIAL_TRACE_LEVEL           UC_BT_LOG_BLUFI_TRACE_LEVEL

#if UC_BT_BLE_DYNAMIC_ENV_MEMORY
#define BT_BLE_DYNAMIC_ENV_MEMORY  TRUE
#define BTC_DYNAMIC_MEMORY         TRUE
#else
#define BT_BLE_DYNAMIC_ENV_MEMORY  FALSE
#define BTC_DYNAMIC_MEMORY         FALSE
#endif

#ifndef BT_BLE_DYNAMIC_ENV_MEMORY
#define BT_BLE_DYNAMIC_ENV_MEMORY  FALSE
#endif

/* 用户配置中的操作系统配置（例如：sdkconfig）*/
#define TASK_PINNED_TO_CORE         UC_TASK_PINNED_TO_CORE
#define BT_TASK_MAX_PRIORITIES      configMAX_PRIORITIES
#define BT_BTC_TASK_STACK_SIZE      UC_BTC_TASK_STACK_SIZE

/* 定义跟踪级别*/
#define BT_TRACE_LEVEL_NONE    UC_TRACE_LEVEL_NONE          /* 不生成跟踪消息*/
#define BT_TRACE_LEVEL_ERROR   UC_TRACE_LEVEL_ERROR         /* 错误条件跟踪消息*/
#define BT_TRACE_LEVEL_WARNING UC_TRACE_LEVEL_WARNING       /* 警告条件跟踪消息*/
#define BT_TRACE_LEVEL_API     UC_TRACE_LEVEL_API           /* API跟踪*/
#define BT_TRACE_LEVEL_EVENT   UC_TRACE_LEVEL_EVENT         /* 事件的调试消息*/
#define BT_TRACE_LEVEL_DEBUG   UC_TRACE_LEVEL_DEBUG         /* 完整调试消息*/
#define BT_TRACE_LEVEL_VERBOSE UC_TRACE_LEVEL_VERBOSE       /* 详细调试消息*/

#define MAX_TRACE_LEVEL        UC_TRACE_LEVEL_VERBOSE

#ifndef LOG_LOCAL_LEVEL
#ifndef BOOTLOADER_BUILD
#define LOG_LOCAL_LEVEL  UC_LOG_DEFAULT_LEVEL
#else
#define LOG_LOCAL_LEVEL  UC_BOOTLOADER_LOG_LEVEL
#endif
#endif

// ESP_LOG_LEVEL和BT_TRACE_LEVEL之间的映射
#if (LOG_LOCAL_LEVEL >= 4)
#define LOG_LOCAL_LEVEL_MAPPING (LOG_LOCAL_LEVEL+1)
#else
#define LOG_LOCAL_LEVEL_MAPPING LOG_LOCAL_LEVEL
#endif

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define BT_LOG_LEVEL_CHECK(LAYER, LEVEL) (MAX(LAYER##_INITIAL_TRACE_LEVEL, LOG_LOCAL_LEVEL_MAPPING) >= BT_TRACE_LEVEL_##LEVEL)

#define BT_PRINT_E(tag, format, ...)   {esp_log_write(ESP_LOG_ERROR,   tag, LOG_FORMAT(E, format), esp_log_timestamp(), tag, ##__VA_ARGS__); }
#define BT_PRINT_W(tag, format, ...)   {esp_log_write(ESP_LOG_WARN,    tag, LOG_FORMAT(W, format), esp_log_timestamp(), tag, ##__VA_ARGS__); }
#define BT_PRINT_I(tag, format, ...)   {esp_log_write(ESP_LOG_INFO,    tag, LOG_FORMAT(I, format), esp_log_timestamp(), tag, ##__VA_ARGS__); }
#define BT_PRINT_D(tag, format, ...)   {esp_log_write(ESP_LOG_DEBUG,   tag, LOG_FORMAT(D, format), esp_log_timestamp(), tag, ##__VA_ARGS__); }
#define BT_PRINT_V(tag, format, ...)   {esp_log_write(ESP_LOG_VERBOSE, tag, LOG_FORMAT(V, format), esp_log_timestamp(), tag, ##__VA_ARGS__); }


#if !UC_BT_STACK_NO_LOG
/* 定义BTC的跟踪*/
#define BTC_TRACE_ERROR(fmt, args...)      {if (BTC_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(BTC, ERROR)) BT_PRINT_E("BT_BTC", fmt, ## args);}
#define BTC_TRACE_WARNING(fmt, args...)    {if (BTC_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(BTC, WARNING)) BT_PRINT_W("BT_BTC", fmt, ## args);}
#define BTC_TRACE_API(fmt, args...)        {if (BTC_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(BTC,API)) BT_PRINT_I("BT_BTC", fmt, ## args);}
#define BTC_TRACE_EVENT(fmt, args...)      {if (BTC_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(BTC,EVENT)) BT_PRINT_D("BT_BTC", fmt, ## args);}
#define BTC_TRACE_DEBUG(fmt, args...)      {if (BTC_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(BTC,DEBUG)) BT_PRINT_D("BT_BTC", fmt, ## args);}
#define BTC_TRACE_VERBOSE(fmt, args...)    {if (BTC_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_VERBOSE && BT_LOG_LEVEL_CHECK(BTC,VERBOSE)) BT_PRINT_V("BT_BTC", fmt, ## args);}

/* 定义OSI跟踪*/
#define OSI_TRACE_ERROR(fmt, args...)      {if (OSI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(OSI, ERROR)) BT_PRINT_E("BT_OSI", fmt, ## args);}
#define OSI_TRACE_WARNING(fmt, args...)    {if (OSI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(OSI, WARNING)) BT_PRINT_W("BT_OSI", fmt, ## args);}
#define OSI_TRACE_API(fmt, args...)        {if (OSI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(OSI,API)) BT_PRINT_I("BT_OSI", fmt, ## args);}
#define OSI_TRACE_EVENT(fmt, args...)      {if (OSI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(OSI,EVENT)) BT_PRINT_D("BT_OSI", fmt, ## args);}
#define OSI_TRACE_DEBUG(fmt, args...)      {if (OSI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(OSI,DEBUG)) BT_PRINT_D("BT_OSI", fmt, ## args);}
#define OSI_TRACE_VERBOSE(fmt, args...)    {if (OSI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_VERBOSE && BT_LOG_LEVEL_CHECK(OSI,VERBOSE)) BT_PRINT_V("BT_OSI", fmt, ## args);}

/* 定义BLUFI的跟踪*/
#define BLUFI_TRACE_ERROR(fmt, args...)      {if (BLUFI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_ERROR && BT_LOG_LEVEL_CHECK(BLUFI, ERROR)) BT_PRINT_E("BT_BLUFI", fmt, ## args);}
#define BLUFI_TRACE_WARNING(fmt, args...)    {if (BLUFI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_WARNING && BT_LOG_LEVEL_CHECK(BLUFI, WARNING)) BT_PRINT_W("BT_BLUFI", fmt, ## args);}
#define BLUFI_TRACE_API(fmt, args...)        {if (BLUFI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_API && BT_LOG_LEVEL_CHECK(BLUFI,API)) BT_PRINT_I("BT_BLUFI", fmt, ## args);}
#define BLUFI_TRACE_EVENT(fmt, args...)      {if (BLUFI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_EVENT && BT_LOG_LEVEL_CHECK(BLUFI,EVENT)) BT_PRINT_D("BT_BLUFI", fmt, ## args);}
#define BLUFI_TRACE_DEBUG(fmt, args...)      {if (BLUFI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_DEBUG && BT_LOG_LEVEL_CHECK(BLUFI,DEBUG)) BT_PRINT_D("BT_BLUFI", fmt, ## args);}
#define BLUFI_TRACE_VERBOSE(fmt, args...)    {if (BLUFI_INITIAL_TRACE_LEVEL >= BT_TRACE_LEVEL_VERBOSE && BT_LOG_LEVEL_CHECK(BLUFI,VERBOSE)) BT_PRINT_V("BT_BLUFI", fmt, ## args);}

#else

/* 定义BTC的跟踪*/
#define BTC_TRACE_ERROR(fmt, args...)
#define BTC_TRACE_WARNING(fmt, args...)
#define BTC_TRACE_API(fmt, args...)
#define BTC_TRACE_EVENT(fmt, args...)
#define BTC_TRACE_DEBUG(fmt, args...)
#define BTC_TRACE_VERBOSE(fmt, args...)

/* 定义OSI跟踪*/
#define OSI_TRACE_ERROR(fmt, args...)
#define OSI_TRACE_WARNING(fmt, args...)
#define OSI_TRACE_API(fmt, args...)
#define OSI_TRACE_EVENT(fmt, args...)
#define OSI_TRACE_DEBUG(fmt, args...)
#define OSI_TRACE_VERBOSE(fmt, args...)

/* 定义BLUFI的跟踪*/
#define BLUFI_TRACE_ERROR(fmt, args...)
#define BLUFI_TRACE_WARNING(fmt, args...)
#define BLUFI_TRACE_API(fmt, args...)
#define BLUFI_TRACE_EVENT(fmt, args...)
#define BLUFI_TRACE_DEBUG(fmt, args...)
#define BLUFI_TRACE_VERBOSE(fmt, args...)

#endif

/**蓝牙错误状态*/
/**我们需要以此为基础*/

/* 与ESP_BT_defs中的ESP_BT_STATUS_xxx相关。小时*/
typedef enum {
    BT_STATUS_SUCCESS = 0,
    BT_STATUS_FAIL,
    BT_STATUS_NOT_READY,
    BT_STATUS_NOMEM,
    BT_STATUS_BUSY,
    BT_STATUS_DONE,        /* 请求已完成*/
    BT_STATUS_UNSUPPORTED,
    BT_STATUS_PARM_INVALID,
    BT_STATUS_UNHANDLED,
    BT_STATUS_AUTH_FAILURE,
    BT_STATUS_RMT_DEV_DOWN,
    BT_STATUS_AUTH_REJECTED,
    BT_STATUS_INVALID_STATIC_RAND_ADDR,
    BT_STATUS_PENDING,
    BT_STATUS_UNACCEPT_CONN_INTERVAL,
    BT_STATUS_PARAM_OUT_OF_RANGE,
    BT_STATUS_TIMEOUT,
    BT_STATUS_MEMORY_FULL,
    BT_STATUS_EIR_TOO_LARGE,
} bt_status_t;

typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef bool BOOLEAN;
/* 最大UUID大小-16字节，结构可容纳任何类型的UUID。*/
#define MAX_UUID_SIZE              16

typedef struct {
#define LEN_UUID_16     2
#define LEN_UUID_32     4
#define LEN_UUID_128    16

    UINT16          len;

    union {
        UINT16      uuid16;
        UINT32      uuid32;
        UINT8       uuid128[MAX_UUID_SIZE];
    } uu;

} tBT_UUID;

/* 通用蓝牙字段定义*/
#define BD_ADDR_LEN     6                   /* 设备地址长度*/
typedef UINT8 BD_ADDR[BD_ADDR_LEN];         /* 设备地址*/

#endif /* _BT_COMMON_H_ */

