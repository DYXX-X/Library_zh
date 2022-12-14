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
#ifndef _ESP32_COMPAT_H_
#define _ESP32_COMPAT_H_

// 跳过这些包含文件
#define ESP_MDNS_NETWORKING_H_
#define _TCPIP_ADAPTER_H_
#define _ESP_TASK_H_

#ifdef USE_BSD_STRING
#include <bsd/string.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "esp_timer.h"

#define ESP_FAIL                    -1

#define ESP_ERR_NO_MEM              0x101
#define ESP_ERR_INVALID_ARG         0x102
#define ESP_ERR_INVALID_STATE       0x103
#define ESP_ERR_INVALID_SIZE        0x104
#define ESP_ERR_NOT_FOUND           0x105
#define ESP_ERR_NOT_SUPPORTED       0x106
#define ESP_ERR_TIMEOUT             0x107
#define ESP_ERR_INVALID_RESPONSE    0x108
#define ESP_ERR_INVALID_CRC         0x109

#define pdTRUE                      true
#define pdFALSE                     false
#define pdPASS			( pdTRUE )
#define pdFAIL			( pdFALSE )

#define portMAX_DELAY               0xFFFFFFFF
#define portTICK_PERIOD_MS          1
#define ESP_LOGW(a,b)
#define ESP_LOGD(a,b)
#define ESP_LOGE(a,b,c)
#define ESP_LOGV(a,b,c,d)

#define LWIP_HDR_PBUF_H
#define __ESP_SYSTEM_H__
#define INC_TASK_H

#define pdMS_TO_TICKS(a) a
#define portTICK_RATE_MS 10
#define xSemaphoreTake(s,d)        true
#define xTaskDelete(a)
#define vTaskDelete(a)             free(a)
#define xSemaphoreGive(s)
#define xQueueCreateMutex(s)
#define _mdns_pcb_init(a,b)         true
#define _mdns_pcb_deinit(a,b)       true
#define xSemaphoreCreateMutex()     malloc(1)
#define xSemaphoreCreateBinary()    malloc(1)
#define vSemaphoreDelete(s)         free(s)
#define queueQUEUE_TYPE_MUTEX       ( ( uint8_t ) 1U
#define xTaskCreatePinnedToCore(a,b,c,d,e,f,g)     *(f) = malloc(1)
#define vTaskDelay(m)               usleep((m)*0)
#define esp_random()                (rand()%UINT32_MAX)


#define ESP_TASK_PRIO_MAX 25
#define ESP_TASKD_EVENT_PRIO 5
#define _mdns_udp_pcb_write(tcpip_if, ip_protocol, ip, port, data, len) len
#define xTaskHandle TaskHandle_t


typedef int32_t esp_err_t;

typedef void * xSemaphoreHandle;
typedef void * SemaphoreHandle_t;
typedef void * xQueueHandle;
typedef void * QueueHandle_t;
typedef void * TaskHandle_t;
typedef int    BaseType_t;
typedef uint32_t TickType_t;
typedef uint32_t portTickType;


extern const char * WIFI_EVENT;
extern const char * IP_EVENT;
extern const char * ETH_EVENT;

/* DHCP客户端或DHCP服务器的状态*/
typedef enum {
    TCPIP_ADAPTER_DHCP_INIT = 0,    /**<DHCP客户端/服务器处于初始状态*/
    TCPIP_ADAPTER_DHCP_STARTED,     /**<DHCP客户端/服务器已启动*/
    TCPIP_ADAPTER_DHCP_STOPPED,     /**<DHCP客户端/服务器已停止*/
    TCPIP_ADAPTER_DHCP_STATUS_MAX
} tcpip_adapter_dhcp_status_t;

struct udp_pcb {
    uint8_t dummy;
};

struct ip4_addr {
  uint32_t addr;
};
typedef struct ip4_addr ip4_addr_t;

struct ip6_addr {
  uint32_t addr[4];
};
typedef struct ip6_addr ip6_addr_t;

typedef struct {
    ip4_addr_t ip;
    ip4_addr_t netmask;
    ip4_addr_t gw;
} tcpip_adapter_ip_info_t;

typedef enum {
    TCPIP_ADAPTER_IF_STA = 0,     /**<ESP32站接口*/
    TCPIP_ADAPTER_IF_AP,          /**<ESP32软AP接口*/
    TCPIP_ADAPTER_IF_ETH,         /**<ESP32以太网接口*/
    TCPIP_ADAPTER_IF_MAX
} tcpip_adapter_if_t;

typedef struct {
    ip6_addr_t ip;
} tcpip_adapter_ip6_info_t;

typedef void* system_event_t;

struct pbuf {
  struct pbuf *next;
  void *payload;
  uint16_t tot_len;
  uint16_t  len;
  uint8_t  /*pbuf_类型*/ type;
  uint8_t  flags;
  uint16_t  ref;
};

uint32_t xTaskGetTickCount(void);
typedef void (*esp_timer_cb_t)(void* arg);

// 队列模拟
QueueHandle_t xQueueCreate( uint32_t uxQueueLength,
                            uint32_t uxItemSize );

void vQueueDelete( QueueHandle_t xQueue );

uint32_t xQueueSend(QueueHandle_t xQueue, const void * pvItemToQueue, TickType_t xTicksToWait);

uint32_t xQueueReceive(QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait);

void GetLastItem(void *pvBuffer);

void ForceTaskDelete(void);

esp_err_t esp_event_handler_register(const char * event_base, int32_t event_id, void* event_handler, void* event_handler_arg);

esp_err_t esp_event_handler_unregister(const char * event_base, int32_t event_id, void* event_handler);


TaskHandle_t xTaskGetCurrentTaskHandle(void);
void xTaskNotifyGive(TaskHandle_t task);
BaseType_t xTaskNotifyWait(uint32_t bits_entry_clear, uint32_t bits_exit_clear, uint32_t *value, TickType_t wait_time );

#endif //_ESP32_COMPAT_H_

