/*
 * 服务器coap.h--LwIP示例
 *
 * 版权所有（C）2013-2016 Christian Amsüss<chrysn@fsfe.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#include "coap_config.h"
#include <coap3/coap.h>

void server_coap_init(void);
/* 当你认为资源可能是肮脏的时候，就称之为*/
void server_coap_poll(void);

