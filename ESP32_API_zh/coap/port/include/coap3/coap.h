/* 修改ESP32平台的头文件实现。
 *
 * 在使用并发定义操作时，使用libcoap软件实现进行故障切换。
 *
 * 围板。h——libcoap的CoAP堆栈的主头文件
 *
 * 版权所有（C）2010-20122015-2016 Olaf Bergmann<bergmann@tzi.org>2015年Carsten Schoenert<c.schoenert@t-online.de>
 *
 * 版权所有2015-2016 Espressif Systems（上海）私人有限公司
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef _COAP_H_
#define _COAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "coap3/libcoap.h"

#include "coap3/coap_forward_decls.h"
#include "coap3/address.h"
#include "coap3/async.h"
#include "coap3/block.h"
#include "coap3/coap_cache.h"
#include "coap3/coap_dtls.h"
#include "coap3/coap_event.h"
#include "coap3/coap_io.h"
#include "coap3/coap_time.h"
#include "coap3/coap_debug.h"
#include "coap3/encode.h"
#include "coap3/mem.h"
#include "coap3/net.h"
#include "coap3/option.h"
#include "coap3/pdu.h"
#include "coap3/coap_prng.h"
#include "coap3/resource.h"
#include "coap3/str.h"
#include "coap3/subscribe.h"
#include "coap3/uri.h"

#ifdef __cplusplus
}
#endif

#endif /* _COAP_H_ */

