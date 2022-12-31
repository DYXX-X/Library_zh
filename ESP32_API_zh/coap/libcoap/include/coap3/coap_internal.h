/*
 * coap_internal。h——不暴露于应用程序编程的结构、枚举和函数
 *
 * 版权所有（C）2019-2021 Jon Shallow<supjps-libcoap@jpshallow.com>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

/*
 * 所有libcoap库文件都应该包含该文件，然后该文件会拉入所有其他适当的头文件。
 *
 * 注意：此文件不应包含在应用程序代码中（内部测试套件可能除外）。
 */

/**
 * @file 凝聚内部.h
 * @brief 将所有仅内部的头文件拉到一起
 */

#ifndef COAP_INTERNAL_H_
#define COAP_INTERNAL_H_

#include "coap_config.h"

/*
 * 基于libcoap的NDEBUG正确设置assert（）
 */
#if defined(HAVE_ASSERT_H) && !defined(assert)
# include <assert.h>
#endif

#include "coap3/coap.h"

/*
 * 包括所有仅供内部使用的头文件。
 */

/* 未在coap中定义。h-内部使用.h文件*/
#include "utlist.h"
#include "uthash.h"
#include "coap_hashkey.h"
#include "coap_mutex.h"

/* 专门定义的内部.h文件*/
#include "coap_asn1_internal.h"
#include "coap_async_internal.h"
#include "coap_block_internal.h"
#include "coap_cache_internal.h"
#include "coap_dtls_internal.h"
#include "coap_io_internal.h"
#include "coap_net_internal.h"
#include "coap_pdu_internal.h"
#include "coap_session_internal.h"
#include "coap_resource_internal.h"
#include "coap_session_internal.h"
#include "coap_subscribe_internal.h"
#include "coap_tcp_internal.h"

#endif /* COAP_INTERNAL_H_ */

