#ifndef LWIP_HDR_APPS_SMTP_OPTS_H
#define LWIP_HDR_APPS_SMTP_OPTS_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/**
 * @defgroup smtp_opts选项
 * @ingroup smtp公司
 * 
 * @{
 */
    
/**将此值设置为1以启用BODY上的数据处理程序回调*/
#ifndef SMTP_BODYDH
#define SMTP_BODYDH             0
#endif

/**SMTP_DEBUG：启用SNTP调试。*/
#ifndef SMTP_DEBUG
#define SMTP_DEBUG              LWIP_DBG_OFF
#endif

/**为服务器名称保留的最大长度，包括终止0字节*/
#ifndef SMTP_MAX_SERVERNAME_LEN
#define SMTP_MAX_SERVERNAME_LEN 256
#endif

/**为用户名保留的最大长度*/
#ifndef SMTP_MAX_USERNAME_LEN
#define SMTP_MAX_USERNAME_LEN   32
#endif

/**密码保留的最大长度*/
#ifndef SMTP_MAX_PASS_LEN
#define SMTP_MAX_PASS_LEN       32
#endif

/**如果您知道在smtp会话期间身份验证数据不会更改，则将此值设置为0，这样可以节省一些堆空间。*/
#ifndef SMTP_COPY_AUTHDATA
#define SMTP_COPY_AUTHDATA      1
#endif

/** 如果您确定传递到此模块的所有数据都符合SMTP RFC中的要求，请将此值设置为0以节省一些代码空间。警告：小心使用！
 */
#ifndef SMTP_CHECK_DATA
#define SMTP_CHECK_DATA         1
#endif

/**将此值设置为1以启用AUTH PLAIN支持*/
#ifndef SMTP_SUPPORT_AUTH_PLAIN
#define SMTP_SUPPORT_AUTH_PLAIN 1
#endif

/**将此值设置为1以启用AUTH LOGIN支持*/
#ifndef SMTP_SUPPORT_AUTH_LOGIN
#define SMTP_SUPPORT_AUTH_LOGIN 1
#endif

/* 可以覆盖内存分配/释放。。。*/
#ifndef SMTP_STATE_MALLOC
#define SMTP_STATE_MALLOC(size)       mem_malloc(size)
#define SMTP_STATE_FREE(ptr)          mem_free(ptr)
#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* SMTP_OPTS_H */


