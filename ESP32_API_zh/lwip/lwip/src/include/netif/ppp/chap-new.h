/*
 * 新朋友。c-新的CHAP实施。
 *
 * 版权所有（c）2003 Paul Mackerras。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.未经事先书面许可，不得使用本软件作者的姓名来背书或推广源自本软件的产品。
 *
 * 3.任何形式的再发行都必须保留以下确认：“本产品包括Paul Mackerras开发的软件<paulus@samba.org>".
 *
 * THE AUTHORS OF THIS SOFTWARE DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT && CHAP_SUPPORT  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifndef CHAP_H
#define CHAP_H

#include "ppp.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * CHAP数据包以带有代码、id、len（2字节）的标准标头开头。
 */
#define CHAP_HDRLEN	4

/*
 * 代码字段的值。
 */
#define CHAP_CHALLENGE	1
#define CHAP_RESPONSE	2
#define CHAP_SUCCESS	3
#define CHAP_FAILURE	4

/*
 * CHAP摘要代码。
 */
#define CHAP_MD5		5
#if MSCHAP_SUPPORT
#define CHAP_MICROSOFT		0x80
#define CHAP_MICROSOFT_V2	0x81
#endif /* MSCHAP_SUPPORT */

/*
 * 挑战和应对领域的半任意限制。
 */
#define MAX_CHALLENGE_LEN	64
#define MAX_RESPONSE_LEN	64

/*
 * 这些限制适用于我们发送的质询和响应数据包。+4是我们实际需要舍入的+1。
 */
#define CHAL_MAX_PKTLEN	(PPP_HDRLEN + CHAP_HDRLEN + 4 + MAX_CHALLENGE_LEN + MAXNAMELEN)
#define RESP_MAX_PKTLEN	(PPP_HDRLEN + CHAP_HDRLEN + 4 + MAX_RESPONSE_LEN + MAXNAMELEN)

/* 支持算法的位掩码*/
#if MSCHAP_SUPPORT
#define MDTYPE_MICROSOFT_V2	0x1
#define MDTYPE_MICROSOFT	0x2
#endif /* MSCHAP_SUPPORT */
#define MDTYPE_MD5		0x4
#define MDTYPE_NONE		0

#if MSCHAP_SUPPORT
/* 返回摘要alg。最首选摘要类型的ID。*/
#define CHAP_DIGEST(mdtype) \
    ((mdtype) & MDTYPE_MD5)? CHAP_MD5: \
    ((mdtype) & MDTYPE_MICROSOFT_V2)? CHAP_MICROSOFT_V2: \
    ((mdtype) & MDTYPE_MICROSOFT)? CHAP_MICROSOFT: \
    0
#else /* !MSCHAP_SUPPORT */
#define CHAP_DIGEST(mdtype) \
    ((mdtype) & MDTYPE_MD5)? CHAP_MD5: \
    0
#endif /* MSCHAP_SUPPORT */

/* 返回我们最喜欢的摘要类型的位标志（lsb-set）。*/
#define CHAP_MDTYPE(mdtype) ((mdtype) ^ ((mdtype) - 1)) & (mdtype)

/* 返回给定摘要算法ID的位标志。*/
#if MSCHAP_SUPPORT
#define CHAP_MDTYPE_D(digest) \
    ((digest) == CHAP_MICROSOFT_V2)? MDTYPE_MICROSOFT_V2: \
    ((digest) == CHAP_MICROSOFT)? MDTYPE_MICROSOFT: \
    ((digest) == CHAP_MD5)? MDTYPE_MD5: \
    0
#else /* !MSCHAP_SUPPORT */
#define CHAP_MDTYPE_D(digest) \
    ((digest) == CHAP_MD5)? MDTYPE_MD5: \
    0
#endif /* MSCHAP_SUPPORT */

/* 我们可以做要求的摘要吗？*/
#if MSCHAP_SUPPORT
#define CHAP_CANDIGEST(mdtype, digest) \
    ((digest) == CHAP_MICROSOFT_V2)? (mdtype) & MDTYPE_MICROSOFT_V2: \
    ((digest) == CHAP_MICROSOFT)? (mdtype) & MDTYPE_MICROSOFT: \
    ((digest) == CHAP_MD5)? (mdtype) & MDTYPE_MD5: \
    0
#else /* !MSCHAP_SUPPORT */
#define CHAP_CANDIGEST(mdtype, digest) \
    ((digest) == CHAP_MD5)? (mdtype) & MDTYPE_MD5: \
    0
#endif /* MSCHAP_SUPPORT */

/*
 * 每个摘要类型的代码都必须提供其中之一。
 */
struct chap_digest_type {
	int code;

#if PPP_SERVER
	/*
	 * 注意：下面的质询和响应参数格式为长度字节，后跟实际质询/响应数据。
	 */
	void (*generate_challenge)(ppp_pcb *pcb, unsigned char *challenge);
	int (*verify_response)(ppp_pcb *pcb, int id, const char *name,
		const unsigned char *secret, int secret_len,
		const unsigned char *challenge, const unsigned char *response,
		char *message, int message_space);
#endif /* PPP_SERVER */
	void (*make_response)(ppp_pcb *pcb, unsigned char *response, int id, const char *our_name,
		const unsigned char *challenge, const char *secret, int secret_len,
		unsigned char *priv);
	int (*check_success)(ppp_pcb *pcb, unsigned char *pkt, int len, unsigned char *priv);
	void (*handle_failure)(ppp_pcb *pcb, unsigned char *pkt, int len);
};

/*
 * 每个接口由章节结构描述。
 */
#if CHAP_SUPPORT
typedef struct chap_client_state {
	u8_t flags;
	const char *name;
	const struct chap_digest_type *digest;
	unsigned char priv[64];		/* 摘要专用区*/
} chap_client_state;

#if PPP_SERVER
typedef struct chap_server_state {
	u8_t flags;
	u8_t id;
	const char *name;
	const struct chap_digest_type *digest;
	int challenge_xmits;
	int challenge_pktlen;
	unsigned char challenge[CHAL_MAX_PKTLEN];
} chap_server_state;
#endif /* PPP_SERVER */
#endif /* CHAP_SUPPORT */

#if 0 /* UNUSED */
/* 挂钩用于验证CHAP挑战的插件*/
extern int (*chap_verify_hook)(char *name, char *ourname, int id,
			const struct chap_digest_type *digest,
			unsigned char *challenge, unsigned char *response,
			char *message, int message_space);
#endif /* UNUSED */

#if PPP_SERVER
/* 由身份验证代码调用以开始对对等方进行身份验证。*/
extern void chap_auth_peer(ppp_pcb *pcb, const char *our_name, int digest_code);
#endif /* PPP_SERVER */

/* 由身份验证调用。开始向对等方验证我们的代码。*/
extern void chap_auth_with_peer(ppp_pcb *pcb, const char *our_name, int digest_code);

/* 表示主pppd代码的CHAP协议*/
extern const struct protent chap_protent;

#ifdef __cplusplus
}
#endif

#endif /* CHAP_H */
#endif /* PPP_SUPPORT && CHAP_SUPPORT */

