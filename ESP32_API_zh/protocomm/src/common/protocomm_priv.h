// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#include <sys/queue.h>
#include <protocomm_security.h>
#include <esp_err.h>

#define PROTOCOMM_NO_SESSION_ID UINT32_MAX

/* 用于指示处理器处理请求或建立安全会话的预期功能的位标志*/
#define REQ_EP      (1 << 0)    /*!< 指示请求处理终结点的标志*/
#define SEC_EP      (1 << 1)    /*!< 指示安全处理终结点的标志*/
#define VER_EP      (1 << 2)    /*!< 指示版本处理终结点的标志*/

/**
 * @brief   Protocomm端点表条目原型
 *
 * 存储在端点表中的条目的结构。
 */
typedef struct protocomm_ep {
    const char              *ep_name;       /*!< 唯一端点名称*/
    protocomm_req_handler_t  req_handler;   /*!< 请求处理程序函数*/

    /* 指向在调用时作为参数传递给处理程序函数的私有数据的指针。如果未使用，则设置为NULL。*/
    void            *priv_data;

    uint32_t         flag;          /*!< 指示端点功能的标志*/

    /* 用于存储端点处理程序的单链接列表中的下一个端点条目*/
    SLIST_ENTRY(protocomm_ep) next;
} protocomm_ep_t;

/**
 * @brief   Protocomm实例的原型结构
 *
 * 当调用API protocomm_new（）时，此结构对应于返回的protocomm的唯一实例。其余的ProtocommAPI需要将此对象作为第一个参数。
 */
struct protocomm {
    /* 传输特定函数的函数原型，调用protocomm_add_endpoint（）时在内部调用。*/
    int (*add_endpoint)(const char *ep_name, protocomm_req_handler_t h, void *priv_data);

    /* 传输特定函数的函数原型，在调用protocomm_remove_endpoint（）时在内部调用。*/
    int (*remove_endpoint)(const char *ep_name);

    /* 指向内部用于建立安全会话的安全层的指针*/
    const protocomm_security_t *sec;

    /* 安全层实例的句柄*/
    protocomm_security_handle_t sec_inst;

    /* 指向占有证明对象的指针*/
    protocomm_security_pop_t *pop;

    /* 用于存储端点处理程序的单链接列表的头*/
    SLIST_HEAD(eptable_t, protocomm_ep) endpoints;

    /* protocomm实例内部使用的私有数据*/
    void* priv;

    /* 特定于应用程序的版本字符串*/
    const char* ver;
};

