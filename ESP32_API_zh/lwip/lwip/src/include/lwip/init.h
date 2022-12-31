/**
 * @file lwIP初始化API
 */

/*
 * 版权所有（c）2001-2004瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */
#ifndef LWIP_HDR_INIT_H
#define LWIP_HDR_INIT_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup lwip_version版本
 * @ingroup 低密度聚乙烯@{
 */

/**X.X.X：堆栈的主要版本*/
#define LWIP_VERSION_MAJOR      2
/**x.x.x：堆栈的次要版本*/
#define LWIP_VERSION_MINOR      1
/**x.x.x：堆栈的修订*/
#define LWIP_VERSION_REVISION   3
/**对于候选版本，此值设置为1..254对于正式版本，此设置为255（LWIP_RC_release）对于开发版本（Git），此设置设置为0（LWIP-RC_development）*/
#define LWIP_VERSION_RC         LWIP_RC_DEVELOPMENT

/**对于正式版本，LWIP_VERSION_RC设置为LWIP_RC_RELEASE*/
#define LWIP_RC_RELEASE         255
/**对于Git版本，LWIP_VERSION_RC设置为LWIP_RC_DEVELOPMENT*/
#define LWIP_RC_DEVELOPMENT     0

#define LWIP_VERSION_IS_RELEASE     (LWIP_VERSION_RC == LWIP_RC_RELEASE)
#define LWIP_VERSION_IS_DEVELOPMENT (LWIP_VERSION_RC == LWIP_RC_DEVELOPMENT)
#define LWIP_VERSION_IS_RC          ((LWIP_VERSION_RC != LWIP_RC_RELEASE) && (LWIP_VERSION_RC != LWIP_RC_DEVELOPMENT))

/* 某些帮助器定义以获取版本字符串*/
#define LWIP_VERSTR2(x) #x
#define LWIP_VERSTR(x) LWIP_VERSTR2(x)
#if LWIP_VERSION_IS_RELEASE
#define LWIP_VERSION_STRING_SUFFIX ""
#elif LWIP_VERSION_IS_DEVELOPMENT
#define LWIP_VERSION_STRING_SUFFIX "d"
#else
#define LWIP_VERSION_STRING_SUFFIX "rc" LWIP_VERSTR(LWIP_VERSION_RC)
#endif

/**提供堆栈的版本*/
#define LWIP_VERSION   ((LWIP_VERSION_MAJOR) << 24   | (LWIP_VERSION_MINOR) << 16 | \
                        (LWIP_VERSION_REVISION) << 8 | (LWIP_VERSION_RC))
/**以字符串形式提供堆栈的版本*/
#define LWIP_VERSION_STRING     LWIP_VERSTR(LWIP_VERSION_MAJOR) "." LWIP_VERSTR(LWIP_VERSION_MINOR) "." LWIP_VERSTR(LWIP_VERSION_REVISION) LWIP_VERSION_STRING_SUFFIX

/**
 * @}
 */

/* 模块初始化*/
void lwip_init(void);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_INIT_H */

