/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成Achim Kraus-会话恢复
 *
 *******************************************************************************/

/**
 * @file 分时
 * @brief 高级DTLS API和可见结构。
 */

#ifndef _DTLS_DTLS_H_
#define _DTLS_DTLS_H_

#include <stdint.h>

#include "tinydtls.h"

#include "state.h"
#include "peer.h"

#include "uthash.h"

#include "alert.h"
#include "crypto.h"
#include "hmac.h"

#include "global.h"
#include "dtls_time.h"

#ifndef DTLSv12
#define DTLS_VERSION 0xfeff	/* DTLS 1.1版*/
#else
#define DTLS_VERSION 0xfefd	/* DTLS 1.2版*/
#endif

typedef enum dtls_credentials_type_t {
  DTLS_PSK_HINT, DTLS_PSK_IDENTITY, DTLS_PSK_KEY
} dtls_credentials_type_t;

typedef struct dtls_ecdsa_key_t {
  dtls_ecdh_curve curve;
  const unsigned char *priv_key;	/**<私钥为字节>*/
  const unsigned char *pub_key_x;	/**<给定私钥的公钥的x部分>*/
  const unsigned char *pub_key_y;	/**<给定私钥的公钥的y部分>*/
} dtls_ecdsa_key_t;

/**用于生成Hello Verify cookie的密钥长度。*/
#define DTLS_COOKIE_SECRET_LENGTH 12

struct dtls_context_t;

/**
 * 此结构包含tinydtls用于与应用程序通信的回调函数。至少必须提供写入功能。DTLS状态机调用它通过网络发送数据包。调用read函数以传递解密和验证的应用程序数据。第三个回调是一个事件处理程序函数，当遇到警告消息或发生库生成的事件时调用该函数。
 */ 
typedef struct {
  /** 
   * 从dtls_handle_message（）调用以通过网络发送dtls数据包。回调函数必须使用session->ifindex表示的网络接口来发送数据。
   *
   * @param ctx  当前DTLS上下文。
   * @param session 会话对象，包括要发送数据的远程对等体的地址。
   * @param buf  要发送的数据。
   * @param len  @p buf的实际长度。
   * @return 回调函数必须返回发送的字节数，或者返回一个小于零的值以指示错误。
   */
  int (*write)(struct dtls_context_t *ctx, 
	       session_t *session, uint8 *buf, size_t len);

  /** 
   * 从dtls_handle_message（）调用传递在给定会话上接收的应用程序数据。只有在解密和验证成功后，才能传送数据。
   *
   * @param ctx  当前DTLS上下文。
   * @param session 会话对象，包括数据源的地址。
   * @param buf  接收到的数据包。
   * @param len  @p buf的实际长度。
   * @return 忽略
   */
  int (*read)(struct dtls_context_t *ctx, 
	       session_t *session, uint8 *buf, size_t len);

  /**
   * 当接收到来自警报协议的消息或DTLS会话的状态发生变化时，将调用事件处理程序。
   *
   * @param ctx     当前dtls上下文。
   * @param session 受影响的会话对象。
   * @param level   发生非警报事件时的警报级别或@c 0。
   * @param code    小于@c 256的值表示警报，而
   *                @c 256或更大指示内部DTLS会话改变。
   * @return 忽略
   */
  int (*event)(struct dtls_context_t *ctx, session_t *session, 
		dtls_alert_level_t level, unsigned short code);

#ifdef DTLS_PSK
  /**
   * 在握手期间调用以获取与psk密钥交换相关的信息。请求的信息类型为
   * indicated by @p 类型，它将是DTLS_PSK_HINT、DTLS_PSK_IDENTITY或DTLS_PSK _KEY之一。被调用的函数必须将请求的项存储在的缓冲区@p结果中
   * size @p result_长度。成功时，函数必须返回写入@presult的实际字节数，错误时该值小于零。参数@p desc可以包含额外的请求信息（例如，当@p type==@c DTLS_psk_key时，为其请求密钥的psk_identity）。
   *
   * @param ctx     当前dtls上下文。
   * @param session 将使用密钥的会话。
   * @param type    请求信息的类型。
   * @param desc    其他请求信息
   * @param desc_len 描述的实际长度。
   * @param result  必须填写所需信息。
   * @param result_length  @p结果的最大大小。
   * @return 写入@p结果的字节数或出错时小于零的值。
   */
  int (*get_psk_info)(struct dtls_context_t *ctx,
		      const session_t *session,
		      dtls_credentials_type_t type,
		      const unsigned char *desc, size_t desc_len,
		      unsigned char *result, size_t result_length);

#endif /* DTLS_PSK */

#ifdef DTLS_ECC
  /**
   * 在握手期间调用，以获取用于在此会话中验证此服务器或客户端的服务器或客户端ecdsa密钥。如果找到，密钥必须存储在@p结果中，并且
   * the return value must be @c 0。如果找不到，@p结果未定义，返回值必须小于零。
   *
   * 如果不支持ECDSA，请将此指针设置为NULL。
   *
   * 如果您想向其他对等方提供自己的证书，请执行此操作。这对于提供ECDSA支持的服务器是强制性的，对于客户端是可选的。执行DTLS客户端身份验证的客户端必须实现此回调。
   *
   * @param ctx     当前dtls上下文。
   * @param session 将使用密钥的会话。
   * @param result  必须设置为用于给定会话的密钥对象。
   * @return @c 0（如果结果已设置），或在错误时小于零。
   */
  int (*get_ecdsa_key)(struct dtls_context_t *ctx, 
		       const session_t *session,
		       const dtls_ecdsa_key_t **result);

  /**
   * 在握手期间调用以检查此会话中对等方的公钥。如果公钥与会话匹配且应被视为有效，则返回值必须为@c 0。如果无效，则返回的值必须小于零。
   *
   * 如果不支持ECDSA，请将此指针设置为NULL。
   *
   * 如果要验证其他对等公钥，请执行此操作。这对于基于ECDSA身份验证的DTLS客户端来说是强制性的。实现此功能的服务器将请求客户端进行DTLS客户端身份验证。
   *
   * @param ctx          当前dtls上下文。
   * @param session      将使用密钥的会话。
   * @param other_pub_x  公钥的x分量。
   * @param other_pub_y  公钥的y分量。
   * @return @c 0（如果公钥匹配），或在错误时小于零。错误代码：返回dtls_alert_fatal_create（dtls_alert_BAD_CERTIFICATE）；返回dtls_alert_fatal_create（dtls_alert_UNSUPPORTED_CERTIFICATE）；返回dtls_alert_fatal_create（dtls_alert_CERTIFICATE_REVOKED）；返回dtls_alert_fatal_create（dtls_alert_CERTIFICATE_EXPIRED）；返回dtls_alert_fatal_create（dtls_alert_CERTIFICATEE_UNKNOWN）；返回dtls_alert_fatal_create（dtls_alert_UNKNOWN_CA）；
   */
  int (*verify_ecdsa_key)(struct dtls_context_t *ctx, 
			  const session_t *session,
			  const unsigned char *other_pub_x,
			  const unsigned char *other_pub_y,
			  size_t key_size);
#endif /* DTLS_ECC */
} dtls_handler_t;

struct netq_t;

/**保存DTLS引擎的全局信息。*/
typedef struct dtls_context_t {
  unsigned char cookie_secret[DTLS_COOKIE_SECRET_LENGTH];
  clock_time_t cookie_secret_age; /**<秘密产生的时间*/

  dtls_peer_t *peers;		/**<对等哈希映射*/
#ifdef WITH_CONTIKI
  struct etimer retransmit_timer; /**<必须发送下一个数据包时激发*/
#endif /* WITH_CONTIKI */

  struct netq_t *sendqueue;     /**<要发送的数据包*/

  void *app;			/**<应用程序特定数据*/

  dtls_handler_t *h;		/**<回调处理程序*/
} dtls_context_t;

/** 
 * 此函数初始化tinyDTLS内存管理，必须首先调用。
 */
void dtls_init(void);

/** 
 * 创建新的上下文对象。必须使用dtls_free_context（）释放为新对象分配的存储。*/
dtls_context_t *dtls_new_context(void *app_data);

/**释放为ctx分配的所有存储。*/
void dtls_free_context(dtls_context_t *ctx);

#define dtls_set_app_data(CTX,DATA) ((CTX)->app = (DATA))
#define dtls_get_app_data(CTX) ((CTX)->app)

/**将@p ctx的回调处理程序对象设置为@p h。*/
static inline void dtls_set_handler(dtls_context_t *ctx, dtls_handler_t *h) {
  ctx->h = h;
}

/**
 * 使用指定的远程对等点@p dst建立DTLS信道。
 * This function returns @c 如果该通道已存在，则为0；发送新的ClientHello消息时，该值大于零；如果出现错误，则该值小于零。
 *
 * @param ctx    要使用的DTLS上下文。
 * @param dst    要连接到的远程方。
 * @return 错误时小于零的值，否则大于或等于。
 */
int dtls_connect(dtls_context_t *ctx, const session_t *dst);

/**
 * 与指定的远程对等方建立DTLS信道。
 * This function returns @c 0，如果该通道已存在并且已启动重新协商，则在发送新的ClientHello消息时，该值大于零，如果出错，则该值小于零。
 *
 * @param ctx    要使用的DTLS上下文。
 * @param peer   描述会话的对等对象。
 * @return 错误时小于零的值，否则大于或等于。
 */
int dtls_connect_peer(dtls_context_t *ctx, dtls_peer_t *peer);

/**
 * Closes the DTLS connection associated with @p 遥远的此函数成功时返回零，错误时返回小于零的值。
 */
int dtls_close(dtls_context_t *ctx, const session_t *remote);

/**
 * 基于指定的会话重新协商DTLS频道。发送新的ClientHello消息时，此函数返回一个大于零的值，出错时返回一个小于零的值。
 *
 * @param ctx    要使用的DTLS上下文。
 * @param dst    描述现有会话的会话对象。
 * @return 错误时小于零的值，否则大于零。
 */
int dtls_renegotiate(dtls_context_t *ctx, const session_t *dst);

/** 
 * 将@p buf中给定的应用程序数据写入指定的对等方
 * by @p 一场
 * 
 * @param ctx      要使用的DTLS上下文。
 * @param session  远程传输地址和本地接口。
 * @param buf      要写入的数据。
 * @param len      @p数据的实际长度。
 * 
 * @return 写入的字节数，发生错误时为@c-1，如果对等方已存在但尚未连接，则为@c 0。
 */
int dtls_write(struct dtls_context_t *ctx, session_t *session, 
	       uint8 *buf, size_t len);

/**
 * 检查给定DTLS上下文对象的发送队列中要传输的任何未完成数据包。
 *
 * @param context 要使用的DTLS上下文对象。
 * @param next    如果不为NULL，则@p next将填充下一次计划重传的时间戳，或在没有数据包等待时填充@c 0。
 */
void dtls_check_retransmit(dtls_context_t *context, clock_time_t *next);

#define DTLS_COOKIE_LENGTH 16

#define DTLS_CT_CHANGE_CIPHER_SPEC 20
#define DTLS_CT_ALERT              21
#define DTLS_CT_HANDSHAKE          22
#define DTLS_CT_APPLICATION_DATA   23

/**DTLS记录层的通用标头结构。*/
typedef struct __attribute__((__packed__)) {
  uint8 content_type;		/**<包含消息的内容类型*/
  uint16 version;		/**<协议版本*/
  uint16 epoch;		        /**<密码状态更改计数器*/
  uint48 sequence_number;       /**<序列号*/
  uint16 length;		/**<以下片段的长度*/
  /* 碎片*/
} dtls_record_header_t;

/* 握手类型*/

#define DTLS_HT_HELLO_REQUEST        0
#define DTLS_HT_CLIENT_HELLO         1
#define DTLS_HT_SERVER_HELLO         2
#define DTLS_HT_HELLO_VERIFY_REQUEST 3
#define DTLS_HT_CERTIFICATE         11
#define DTLS_HT_SERVER_KEY_EXCHANGE 12
#define DTLS_HT_CERTIFICATE_REQUEST 13
#define DTLS_HT_SERVER_HELLO_DONE   14
#define DTLS_HT_CERTIFICATE_VERIFY  15
#define DTLS_HT_CLIENT_KEY_EXCHANGE 16
#define DTLS_HT_FINISHED            20

/**DTLS握手协议的报头结构。*/
typedef struct __attribute__((__packed__)) {
  uint8 msg_type; /**<握手消息类型（DTLS_HT_之一）*/
  uint24 length;  /**<此消息的长度*/
  uint16 message_seq; 	/**<消息序列号*/
  uint24 fragment_offset;	/**<片段偏移。*/
  uint24 fragment_length;	/**<片段长度。*/
  /* 身体*/
} dtls_handshake_header_t;

/**客户端Hello消息的结构。*/
typedef struct __attribute__((__packed__)) {
  uint16 version;	  /**<客户端版本*/
  uint32 gmt_random;	  /**<随机字节创建的GMT时间*/
  unsigned char random[28];	/**<客户端随机字节*/
  /* 会话id（最多32字节）*/
  /* cookie（最多32字节）*/
  /* 密码套件（2到2^16-1字节）*/
  /* 压缩法*/
} dtls_client_hello_t;

/**Hello Verify请求的结构。*/
typedef struct __attribute__((__packed__)) {
  uint16 version;		/**<服务器版本*/
  uint8 cookie_length;	/**<包含cookie的长度*/
  uint8 cookie[];		/**<最多32个字节构成cookie*/
} dtls_hello_verify_t;  

#if 0
/** 
 * 检查接收到的DTLS记录的一致性，并最终解密、验证、解压缩和重新组装所包含的片段，以交付给高级客户端。
 * 
 * \param state当前会话的DTLS记录状态。\参数
 */
int dtls_record_read(dtls_state_t *state, uint8 *msg, int msglen);
#endif

/** 
 * 将来自给定对等方的传入数据作为DTLS消息处理。
 *
 * @param ctx     要使用的dtls上下文。
 * @param session 当前会话
 * @param msg     收到的数据
 * @param msglen  @p消息的实际长度。
 * @return 错误时小于零，成功时小于零。
 */
int dtls_handle_message(dtls_context_t *ctx, session_t *session,
			uint8 *msg, int msglen);

/**
 * Check if @p 会话与@p上下文中的对等对象相关联。如果找到，此函数将返回指向对等方的指针，否则返回NULL。
 *
 * @param context  要搜索的DTLS上下文。
 * @param session  远程地址和本地接口
 * @return 指向与@p会话关联的对等方的指针，如果不存在，则返回NULL。
 */
dtls_peer_t *dtls_get_peer(const dtls_context_t *context,
			   const session_t *session);

/**
 * 重置与@p peer的所有连接。
 *
 * @param context  活动的DTLS上下文。
 * @param peer     要重置的对等方。
 */
void dtls_reset_peer(dtls_context_t *context, dtls_peer_t *peer);

#endif /* _DTLS_DTLS_H_ */

/**
 * @mainpage 
 *
 * @author 奥拉夫·伯格曼，TZI Uni Bremen
 *
 * 这个库提供了一个支持DTLS的非常简单的数据报服务器。它旨在支持单线程应用程序中的会话复用，因此专门针对嵌入式系统。
 *
 * @section 许可证许可证
 *
 * 该软件位于<a href=“http://www.opensource.org/licenses/mit-license.php“>MIT许可证</a>。
 * 
 * @subsection uthash uthash
 *
 * 此库使用<a href=“http://uthash.sourceforge.net/“>uthash</a>要管理
 * its peers (not used for Contiki). @b uthash使用<b>BSD修订版许可证</b>，请参见<a href=“http://uthash.sourceforge.net/license.html">http://uthash.sourceforge.net/license.html</a>。
 *
 * @subsection sha256 Aaron D.Gifford的sha256实现
 *
 * tinyDTLS为HMAC-SHA256提供Aaron D.Gifford的BSD许可代码，请参见<a href=“http://www.aarongifford.com/“>www.aarongifford.com</a>。
 *
 * @subsection 来自OpenBSD的aes Rijndael实现
 *
 * AES实现取自rijndael。｛c，h｝包含在OpenBSD操作系统的加密子系统中。版权归文森特·里梅恩、安托翁·博塞拉斯和保罗·巴雷托所有。参见<a href=“http://www.openbsd.org/cgi-bin/cvsweb/src/sys/crypto/rijndael.c“>rijndael.c</a>获取许可证信息。
 *
 * @section 下载获取文件
 *
 * 您可以从<a href=“http://sourceforge.net/projects/tinydtls/files“>下载</a>部分或通过git从<a href=”http://sourceforge.net/projects/tinydtls/develop“>项目开发页面</a>。
 *
 * @section 配置配置
 *
 * Use @c 配置以设置成功生成所需的一切。对于Contiki，请使用
 * option @c --与contiki。
 *
 * @section 建筑
 *
 * 配置后，只需键入
 * @code
制作
 * @endcode 可选地后跟
 * @code
制造安装
 * @endcode Contiki版本与Contiki构建系统集成，因此您不需要
 * need to invoke @c 明确地作出。只需将@c tinydtls添加到变量@c APPS
 * in your @c 生成文件。
 *
 * @addtogroup dtls_usage dtls用法
 *
 * @section dtls_server_example dtls服务器示例
 *
 * 本节介绍如何使用DTLS库函数来设置简单的安全UDP echo服务器。应用程序负责整个网络通信，因此看起来像一个普通的UDP服务器，具有套接字创建和绑定以及典型的选择循环，如下所示。DTLS所需的最低配置是使用DTLS_new_context（）创建DTLS_context_t，以及用于发送数据的回调。接收到的数据包由应用程序读取并传递给dtls_handle_message（），如@ref dtls_read_cb所示。为了实现任何有用的通信，还应注册读写回调和密钥管理功能。
 * 
 * @code 
 dtls_context_t *the_context = NULL;
 int fd，结果；

 静态dtls_handler_t cb={
   .write=发送_to_peer，
   read＝read_from_peer，
   .event=空，
   .get_psk_key=get_psk_key
 };

 fd=插座（…）；
 如果（fd＜0 | |绑定（fd，…）＜0）
   出口（-1）；

 the_context=dtls_new_context（&fd）；
 dtls_set_handler（the_context，&cb）；

 而（1）{
   …初始化fd_set rfds并超时。。。
   result=select（fd+1，&rfd，NULL，0，NULL）；
    
   if（FD_ISSET（FD，&rfds））
     dtls_handle_read（文本）；
 }

 dtls_free_context（the_context）；
 * @endcode
 * 
 * @subsection dtls_read_cb读取回调
 *
 * DTLS库要求将接收到的原始数据传递给DTLS_handle_message（）。应用程序负责用远程对等体的地址数据填充session_t结构，如下例所示：
 * 
 * @code
int dtls_handle_read（结构dtls_context_t*ctx）{
  int*fd；
  session_t会话；
  静态uint8 buf[DTLS_MAX_buf]；
  整数长度；

  fd=dtls_get_app_data（ctx）；

  断言（fd）；

  一场size=sizeof（session.addr）；
  len = recvfrom(*fd, buf，sizeof（buf），0，&session.addr。sa和会话大小）；
  
  返回长度<0？len：dtls_handle_message（ctx，&session，buf，len）；
}    
 * @endcode 
 * 
 * 一旦建立了新的DTLS会话并且接收到了DTLS ApplicationData，DTLS服务器将以MAC验证的明文数据作为参数调用读取回调。简单echo服务器的读取回调可能如下所示：
 * @code
int read_from_peer(struct dtls_context_t *ctx, session_t*会话，uint8*数据，size_t len）{
  返回dtls_write（ctx，session，data，len）；
}
 * @endcode 
 * 
 * @subsection dtls_send_cb发送回调
 * 
 * 每当必须通过网络发送数据时，都会调用回调函数send_to_peer（）。这里，sendto（）系统调用用于在给定会话内传输数据。使用DTLS_new_context（）创建DTLS上下文时，sendto（）所需的套接字描述符已注册为应用程序数据。请注意，当调用回调时无法发送数据时，应用程序需要缓冲数据。因此，以下示例是不完整的，因为它必须以某种方式处理EAGAIN。
 * @code
int send_to_peer(struct dtls_context_t *ctx, session_t*会话，uint8*数据，size_t len）{
  int fd = *(int *)dtls_get_app_data（ctx）；
  返回sendto（fd，data，len，MSG_DONTWAIT，&session->addr.sa，session->size）；
}
 * @endcode
 * 
 * @subsection dtls_get_psk_info密钥存储
 *
 * 创建新的DTLS会话时，库必须向应用程序请求密钥材料。为此，它使用当前上下文和会话信息作为参数调用已注册的回调函数get_psk_info（）。调用回调函数时，参数@p类型设置为
 * @c DTLS_PSK_IDENTITY，如果是服务器，则结果参数@p result必须填写PSK_IDENTITY_hint，或者
 * case of a client. When @p 类型为@c DTLS_PSK_KEY，result参数必须用给定标识@p id的键填充。函数必须返回写入@p result的字节数，该值不得超过
 * @p result_长度。如果发生错误，函数必须返回一个负值，该负值对应于alert.h中定义的有效错误代码。
 * 
 * @code
int get_psk_info（结构dtls_context_t*ctx UNUSED_PARAM，
	    const session_t *session UNUSED_PARAM,
dtls_ credentials_，
常量无符号字符*id，size_t id_len，
	    unsigned char *result, 大小_结果_长度）{

  开关（类型）{
  案例DTLS_PSK_IDENTITY：
    如果（result_length<psk_id_length）{
      dtls_warn（“无法设置psk_identity--缓冲区太小\n”）；
      返回dtls_alert_fatal_create（dtls_alert_INTERNAL_ERROR）；
    }

    memcpy（结果，psk_id，psk_id_length）；
    返回psk_id_length；
  案例DTLS_PSK_KEY：
    如果（id_len！=psk_id_length | | memcmp（psk_id，id，id_len）！=0) {
      dtls_warn（“请求未知id的PSK，正在退出\n”）；
      返回dtls_alert_fatal_create（dtls_alert_ILLEGAL_PARAMETER）；
    }否则如果（result_length<psk_key_length）{
      dtls_warn（“无法将psk--缓冲区设置得太小\n”）；
      返回dtls_alert_fatal_create（dtls_alert_INTERNAL_ERROR）；
    }

    memcpy（结果，pskkey，pskkey_length）；
    返回psk_key_length；
  违约：
    dtls_warn（“不支持的请求类型：%d\n”，类型）；
  }

  返回dtls_alert_fatal_create（dtls_alert_INTERNAL_ERROR）；
}
 * @endcode
 * 
 * @subsection dtls_events事件通知程序
 *
 * Applications that want to be notified whenever the status of a DTLS session has changed can register an event handling function with the field @c dtls_handler_t结构中的事件（请参见\ref dtls_server_example）。回调函数用于警报消息和内部状态更改。用于警报
 * messages, the argument @p 级别将设置为大于零的值，并且
 * @p 代码将指示通知代码。对于内部事件，@p级别
 * is @c 0，并且@p编码大于@c 255的值。
 *
 * 内部事件为DTLS_EVENT_CONNECTED、@c DTLS_EVENT_CONNECT和
 * @c DTLS_EVENT_RENEGOTIATE.
 *
 * @code
int handle_event（结构dtls_context_t*ctx，session_t*session，
                 dtls_alert_level_t级别，无符号短代码）{
  …用事件做点什么。。。
  返回0；
}
 * @endcode
 *
 * @section dtls_client_example dtls客户端示例
 *
 * DTLS客户端的构造类似于服务器，但需要在某个时刻通过调用DTLS_connect（）来主动设置新会话。由于此函数通常在建立新的DTLS通道之前返回，因此应用程序必须注册事件处理程序并等待@c DTLS_event_CONNECT，然后才能通过DTLS通道发送数据。
 *
 */

/**
 * @addtogroup 康蒂基康蒂基
 *
 * 要使用tinyDTLS作为Contiki应用程序，请将源代码放在目录中
 * @c 在Contiki源树中的apps/tinydtls，并使用选项调用configure
 * @c --与contiki。这将在tinydtls中定义WITH_CONTIKI。h和包括
 * @c 生成文件。contiki在主Makefile中。要为另一个平台交叉编译，您需要设置主机并相应地构建系统。例如，当为ARM配置时，您将调用
 * @code
./configure--with contiki--build=x86_64-linux-gnu--host=arm none-eabi
 * @endcode 在x86_64 linux主机上。
 *
 * Then, create a Contiki project with @c APPS+=其Makefile中的tinydtls。示例服务器可能是这样的（上面显示了read_from_peer（）和get_psk_key（））。
 *
 * @code
#包括“contiki.h”

#包括“tinydtls.h”
#包括“dtls.h”

#定义UIP_IP_BUF（（结构UIP_IP_hdr*）&UIP_BUF[UIP_LLH_LEN]）
#定义UIP_UDP_BUF（（结构UIP_UDP_hdr*）&UIP_BUF[UIP_LIPH_LEN]）

int send_to_peer（结构dtls_context_t*，session_t*，uint8*，size_t）；

静态结构uip_udp_conn*server_conn；
静态dtls_context_t*dtls_context；

静态dtls_handler_t cb={
  .write=发送_to_peer，
  read＝read_from_peer，
  .event=空，
  .get_psk_key=get_psk_key
};

PROCESS（服务器进程，“DTLS服务器进程”）；
AUTOSTART_process（&server_process）；

PROCESS_THREAD（服务器_进程，ev，数据）
{
  PROCESS_BEGIN();

  dtls_init（）；

  server_conn=udp_new（NULL，0，NULL）；
  udp_bind（server_conn，UIP_HTONS（5684））；

  dtls_context=dtls_new_context（服务器_conn）；
  if（！dtls_context）{
    dtls_emerg（“无法创建上下文\n”）；
    PROCESS_EXIT();
  }

  dtls_set_handler（dtls_context，&cb）；

  而（1）{
    PROCESS_WAIT_EVENT();
    如果（ev==tcpip_event&&uip_newdata（））{
      session_t会话；

      uip_ipaddr_copy（&session.addr，&uip_IP_BUF->srcipaddr）；
      session.port=UIP_UDP_BUF->srcport；
      session.size=sizeof（session.addr）+sizeof（会话.port）；
    
      dtls_handle_message（ctx、&session、uip_appdata、uip_dataren（））；
    }
  }

  PROCESS_END();
}

int send_to_peer(struct dtls_context_t *ctx, session_t*会话，uint8*数据，size_t len）{
  struct uip_udp_conn *conn =（结构uip_udp_conn*）dtls_get_app_data（ctx）；

  uip_ipaddr_copy（&connen->riaddr，&session->addr）；
  conn->rport=会话->端口；

  uip_udp_packet_send（连接、数据、长度）；

  内存集（&connen->ripaddr，0，sizeof（server_conn->riaddr））；
  内存集（&conn->rport，0，sizeof（conn->corpot））；

  返回长度；
}
 * @endcode
 */

