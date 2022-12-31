// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#ifndef ESP_EVENT_INTERNAL_H_
#define ESP_EVENT_INTERNAL_H_

#include "sys/queue.h"
#include <stdbool.h>
#include "esp_event.h"
#include "stdatomic.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef SLIST_HEAD(base_nodes, base_node) base_nodes_t;

typedef struct esp_event_handler_context {
    esp_event_handler_t handler;                                    /**<事件处理程序函数*/
    void* arg;
} esp_event_handler_instance_context_t;                             /**<事件处理程序参数*/

///事件处理程序
typedef struct esp_event_handler_node {
    esp_event_handler_instance_context_t* handler_ctx;              /**<事件处理程序上下文*/
#ifdef CONFIG_ESP_EVENT_LOOP_PROFILING
    uint32_t invoked;                                               /**<调用此处理程序的次数*/
    int64_t time;                                                   /**<此处理程序在所有调用中的总运行时间*/
#endif
    SLIST_ENTRY(esp_event_handler_node) next;                   /**<列表中的下一个事件处理程序*/
} esp_event_handler_node_t;

typedef SLIST_HEAD(esp_event_handler_instances, esp_event_handler_node) esp_event_handler_nodes_t;

///事件
typedef struct esp_event_id_node {
    int32_t id;                                                     /**<事件的id号*/
    esp_event_handler_nodes_t handlers;                             /**＜引发此事件时要执行的处理程序列表*/
    SLIST_ENTRY(esp_event_id_node) next;                            /**<指向链接列表上的下一个事件节点的指针*/
} esp_event_id_node_t;

typedef SLIST_HEAD(esp_event_id_nodes, esp_event_id_node) esp_event_id_nodes_t;

typedef struct esp_event_base_node {
    esp_event_base_t base;                                          /**<事件的基本标识符*/
    esp_event_handler_nodes_t handlers;                             /**<event基本级别处理程序，具有此基本级别的所有事件的处理程序*/
    esp_event_id_nodes_t id_nodes;                                  /**<此基的事件ID列表*/
    SLIST_ENTRY(esp_event_base_node) next;                          /**<指向链接列表上的下一个基节点的指针*/
} esp_event_base_node_t;

typedef SLIST_HEAD(esp_event_base_nodes, esp_event_base_node) esp_event_base_nodes_t;

typedef struct esp_event_loop_node {
    esp_event_handler_nodes_t handlers;                             /**事件循环级处理程序*/
    esp_event_base_nodes_t base_nodes;                              /**注册到循环的事件库列表*/
    SLIST_ENTRY(esp_event_loop_node) next;                          /**指向下一个循环节点的指针，该节点包含事件循环级处理程序和注册到该循环的其余事件基*/
} esp_event_loop_node_t;

typedef SLIST_HEAD(esp_event_loop_nodes, esp_event_loop_node) esp_event_loop_nodes_t;

///事件循环
typedef struct esp_event_loop_instance {
    const char* name;                                               /**<此事件循环的名称*/
    QueueHandle_t queue;                                            /**<事件队列*/
    TaskHandle_t task;                                              /**<消耗事件队列的任务*/
    TaskHandle_t running_task;                                      /**<对于没有专用任务的循环，使用队列的任务*/
    SemaphoreHandle_t mutex;                                        /**<mutex用于更新事件链接列表*/
    esp_event_loop_nodes_t loop_nodes;                              /**<包含循环的注册处理程序的链接列表集*/
#ifdef CONFIG_ESP_EVENT_LOOP_PROFILING
    atomic_uint_least32_t events_recieved;                          /**<成功发布到循环的事件数*/
    atomic_uint_least32_t events_dropped;                           /**<由于队列已满而丢弃的事件数*/
    SemaphoreHandle_t profiling_mutex;                              /**<用于配置文件的互斥*/
    SLIST_ENTRY(esp_event_loop_instance) next;                      /**<列表中的下一个事件循环*/
#endif
} esp_event_loop_instance_t;

#if CONFIG_ESP_EVENT_POST_FROM_ISR
typedef union esp_event_post_data {
    uint32_t val;
    void *ptr;
} esp_event_post_data_t;
#else
typedef void* esp_event_post_data_t;
#endif

///发布到事件队列的事件
typedef struct esp_event_post_instance {
#if CONFIG_ESP_EVENT_POST_FROM_ISR
    bool data_allocated;                                             /**<表示是否从堆分配数据*/
    bool data_set;                                                   /**<表示数据是否为空*/
#endif
    esp_event_base_t base;                                           /**<事件基础*/
    int32_t id;                                                      /**<事件id*/
    esp_event_post_data_t data;                                      /**<与事件相关的数据*/
} esp_event_post_instance_t;

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // #如果是ESP_EVENT_INTERNAL_H_

