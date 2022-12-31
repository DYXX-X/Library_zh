/*
 * coap_config.h.lwip—libcoap的lwip配置
 *
 * 版权所有（C）2021 Olaf Bergmann<bergmann@tzi.org>和其他
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_CONFIG_H_
#define COAP_CONFIG_H_

#include <lwip/opt.h>
#include <lwip/debug.h>
#include <lwip/def.h> /* 提供ntohs，htons*/

#define WITH_LWIP 1

#ifndef COAP_CONSTRAINED_STACK
#define COAP_CONSTRAINED_STACK 1
#endif

#ifndef COAP_DISABLE_TCP
#define COAP_DISABLE_TCP 1
#endif

#define PACKAGE_NAME "libcoap"
#define PACKAGE_VERSION "4.3.0"
#define PACKAGE_STRING "libcoap 4.3.0"

#define assert(x) LWIP_ASSERT("CoAP assert failed", x)

/* 它只是由libc提供的。我希望我们不要得到太多这样的东西，因为实际上我们需要再次使用自动工具来了解我们正在构建的环境*/
#define HAVE_STRNLEN 1

#define HAVE_LIMITS_H

#endif /* COAP_CONFIG_H_ */

