/*
 * ESP32平台的libcoap配置实现。
 *
 * 在使用并发配置操作时，使用libcoap软件实现进行故障切换。
 *
 * 围板。h——libcoap的CoAP堆栈的主头文件
 *
 * 版权所有（C）2010-20122015-2016 Olaf Bergmann<bergmann@tzi.org>2015年Carsten Schoenert<c.schoenert@t-online.de>
 *
 * 版权所有2015-2016 Espressif Systems（上海）私人有限公司
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

/* 始终在ESP-IDF中启用*/
#ifndef WITH_POSIX
#define WITH_POSIX
#endif

#include "coap_config_posix.h"

#define HAVE_STDIO_H
#define HAVE_ASSERT_H

#define PACKAGE_STRING PACKAGE_NAME PACKAGE_VERSION

/* 它只是由libc提供的。我希望我们不要得到太多这样的东西，因为实际上我们需要再次使用自动工具来了解我们正在构建的环境*/
#define HAVE_STRNLEN 1

#define HAVE_LIMITS_H

#define COAP_RESOURCES_NOHASH

#endif /* _CONFIG_H_ */

