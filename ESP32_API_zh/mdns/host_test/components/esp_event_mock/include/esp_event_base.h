// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

typedef enum {
    WIFI_EVENT_STA_CONNECTED,            /**<ESP32站连接到AP*/
    WIFI_EVENT_STA_DISCONNECTED,         /**<ESP32站与AP断开*/
    WIFI_EVENT_AP_START,                 /**<ESP32软AP启动*/
    WIFI_EVENT_AP_STOP,                  /**<ESP32软AP停止*/
} mdns_used_event_t;

