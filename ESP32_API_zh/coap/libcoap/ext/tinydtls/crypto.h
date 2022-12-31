/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

#ifndef _DTLS_CRYPTO_H_
#define _DTLS_CRYPTO_H_

#include <stdlib.h>		/* 对于rand（）和srand（）*/
#include <stdint.h>

#include "aes/rijndael.h"

#include "tinydtls.h"
#include "global.h"
#include "state.h"
#include "numeric.h"
#include "hmac.h"
#include "ccm.h"

/* TLS_PSK_WITH_AES_128_CCM_8 */
#define DTLS_MAC_KEY_LENGTH    0
#define DTLS_KEY_LENGTH        16 /* AES-128 */
#define DTLS_BLK_LENGTH        16 /* AES-128 */
#define DTLS_MAC_LENGTH        DTLS_HMAC_DIGEST_SIZE
#define DTLS_IV_LENGTH         4  /* nonce_explicit的长度*/

/** 
 * 生成的密钥块的最大大小。注意，MAX_KEYBLOCK_LENGTH必须足够大，以容纳pre_master_secret，即预共享密钥长度的两倍+1。
 */
#define MAX_KEYBLOCK_LENGTH  \
  (2 * DTLS_MAC_KEY_LENGTH + 2 * DTLS_KEY_LENGTH + 2 * DTLS_IV_LENGTH)

/**DTLS master_secret的长度*/
#define DTLS_MASTER_SECRET_LENGTH 48
#define DTLS_RANDOM_LENGTH 32

typedef enum { AES128=0 
} dtls_crypto_alg;

typedef enum {
  DTLS_ECDH_CURVE_SECP256R1
} dtls_ecdh_curve;

/**TLS_PSK_WITH_AES_128_CCM_8密码套件的密码上下文。*/
typedef struct {
  rijndael_ctx ctx;		       /**<AES-128加密上下文*/
  uint8_t tag_length;                  /**<MAC标签长度（=M）*/
  uint8_t l;                           /**<长度*字段中的字节数（=L）*/
} aes128_ccm_t;

typedef struct dtls_cipher_context_t {
  /**此密码套件的数字标识符（按主机字节顺序）。*/
  aes128_ccm_t data;		/**<加密上下文*/
} dtls_cipher_context_t;

typedef struct {
  uint8 own_eph_priv[32];
  uint8 other_eph_pub_x[32];
  uint8 other_eph_pub_y[32];
  uint8 other_pub_x[32];
  uint8 other_pub_y[32];
} dtls_handshake_parameters_ecdsa_t;

/* 这是psk客户端标识和psk服务器标识提示的最大支持长度*/
#ifndef DTLS_PSK_MAX_CLIENT_IDENTITY_LEN
#define DTLS_PSK_MAX_CLIENT_IDENTITY_LEN   32
#endif /* DTLS_PSK_MAX_CLIENT_IDENTITY_LEN */

/* 这是预共享密钥的最大支持长度。*/
#define DTLS_PSK_MAX_KEY_LEN DTLS_KEY_LENGTH

typedef struct {
  uint16_t id_length;
  unsigned char identity[DTLS_PSK_MAX_CLIENT_IDENTITY_LEN];
} dtls_handshake_parameters_psk_t;

typedef struct {
    uint64_t cseq;
    uint64_t bitfield;
} seqnum_t;

typedef struct {
  dtls_compression_t compression;	/**<压缩方法*/

  dtls_cipher_t cipher;		/**<密码类型*/
  uint16_t epoch;	     /**<密码状态更改计数器*/
  uint64_t rseq;	     /**<发送的最后一条记录的序列号*/

  /** 
   * 从应用于客户端和服务器随机字节的PRF生成的密钥块。实际大小由所选密码给出，可以使用dtls_kb_size（）计算。使用\c dtls_kb_宏访问键块的组件。
   */
  uint8 key_block[MAX_KEYBLOCK_LENGTH];
  
  seqnum_t cseq;        /**<接收到的最后一条记录的序列号*/
} dtls_security_parameters_t;

struct netq_t;

typedef struct {
  union {
    struct random_t {
      uint8 client[DTLS_RANDOM_LENGTH];	/**<客户端随机gmt和字节*/
      uint8 server[DTLS_RANDOM_LENGTH];	/**<服务器随机gmt和字节*/
    } random;
    /**会议的主要秘密*/
    uint8 master_secret[DTLS_MASTER_SECRET_LENGTH];
  } tmp;
  struct netq_t *reorder_queue;	/**<要重新排序的数据包*/
  dtls_hs_state_t hs_state;  /**<握手协议状态*/

  dtls_compression_t compression;		/**<压缩方法*/
  dtls_cipher_t cipher;		/**<密码类型*/
  unsigned int do_client_auth:1;
  unsigned int extended_master_secret:1;
  union {
#ifdef DTLS_ECC
    dtls_handshake_parameters_ecdsa_t ecdsa;
#endif /* DTLS_ECC */
#ifdef DTLS_PSK
    dtls_handshake_parameters_psk_t psk;
#endif /* DTLS_PSK */
  } keyx;
} dtls_handshake_parameters_t;

/* 以下宏提供对安全参数中key_block组件的访问。*/

#define dtls_kb_client_mac_secret(Param, Role) ((Param)->key_block)
#define dtls_kb_server_mac_secret(Param, Role)				\
  (dtls_kb_client_mac_secret(Param, Role) + DTLS_MAC_KEY_LENGTH)
#define dtls_kb_remote_mac_secret(Param, Role)				\
  ((Role) == DTLS_SERVER						\
   ? dtls_kb_client_mac_secret(Param, Role)				\
   : dtls_kb_server_mac_secret(Param, Role))
#define dtls_kb_local_mac_secret(Param, Role)				\
  ((Role) == DTLS_CLIENT						\
   ? dtls_kb_client_mac_secret(Param, Role)				\
   : dtls_kb_server_mac_secret(Param, Role))
#define dtls_kb_mac_secret_size(Param, Role) DTLS_MAC_KEY_LENGTH
#define dtls_kb_client_write_key(Param, Role)				\
  (dtls_kb_server_mac_secret(Param, Role) + DTLS_MAC_KEY_LENGTH)
#define dtls_kb_server_write_key(Param, Role)				\
  (dtls_kb_client_write_key(Param, Role) + DTLS_KEY_LENGTH)
#define dtls_kb_remote_write_key(Param, Role)				\
  ((Role) == DTLS_SERVER						\
   ? dtls_kb_client_write_key(Param, Role)				\
   : dtls_kb_server_write_key(Param, Role))
#define dtls_kb_local_write_key(Param, Role)				\
  ((Role) == DTLS_CLIENT						\
   ? dtls_kb_client_write_key(Param, Role)				\
   : dtls_kb_server_write_key(Param, Role))
#define dtls_kb_key_size(Param, Role) DTLS_KEY_LENGTH
#define dtls_kb_client_iv(Param, Role)					\
  (dtls_kb_server_write_key(Param, Role) + DTLS_KEY_LENGTH)
#define dtls_kb_server_iv(Param, Role)					\
  (dtls_kb_client_iv(Param, Role) + DTLS_IV_LENGTH)
#define dtls_kb_remote_iv(Param, Role)					\
  ((Role) == DTLS_SERVER						\
   ? dtls_kb_client_iv(Param, Role)					\
   : dtls_kb_server_iv(Param, Role))
#define dtls_kb_local_iv(Param, Role)					\
  ((Role) == DTLS_CLIENT						\
   ? dtls_kb_client_iv(Param, Role)					\
   : dtls_kb_server_iv(Param, Role))
#define dtls_kb_iv_size(Param, Role) DTLS_IV_LENGTH

#define dtls_kb_size(Param, Role)					\
  (2 * (dtls_kb_mac_secret_size(Param, Role) +				\
	dtls_kb_key_size(Param, Role) + dtls_kb_iv_size(Param, Role)))

/* 只是为了一致性*/
#define dtls_kb_digest_size(Param, Role) DTLS_MAC_LENGTH

/** 
 * 根据RFC 4346第5节中指定的算法，将密钥和密钥扩展为DTLS_HMAC_MAX大小的块。
 *
 * \param h要使用的哈希函数的标识符。\param key秘密。\param keylen \p键的长度。\param seed种子。\param seedlen \p种子的长度。\param buf输出缓冲区，其中结果被异或为缓冲区。缓冲区必须至少能够容纳\p个缓冲字节。\return写入\p buf的实际字节数或出错时的0。
 */
size_t dtls_p_hash(dtls_hashfunc_t h, 
		   const unsigned char *key, size_t keylen,
		   const unsigned char *label, size_t labellen,
		   const unsigned char *random1, size_t random1len,
		   const unsigned char *random2, size_t random2len,
		   unsigned char *buf, size_t buflen);

/**
 * 此函数实现DTLS_VERSION的TLS PRF。对于版本1.0，PRF为P_MD5^P_SHA1，而版本1.2使用P_SHA256。当前，实际的PRF在编译时选择。
 */
size_t dtls_prf(const unsigned char *key, size_t keylen,
		const unsigned char *label, size_t labellen,
		const unsigned char *random1, size_t random1len,
		const unsigned char *random2, size_t random2len,
		unsigned char *buf, size_t buflen);

/**
 * 计算记录+明文数据包的MAC，并将结果放入\p buf。给定的\p hmac_ctx必须使用要使用的hmac函数和正确的密钥进行初始化。由于DTLS mac计算需要记录头中的数据，因此记录必须指向大小至少为（DTLS_record_header_t）字节的缓冲区。通常，剩余的数据包将被加密，因此，明文在\p数据包中单独传递。
 * 
 * \param hmac_ctx用于MAC计算的hmac上下文。\param record记录头。\param packet要应用MAC的Cleartext有效负载。\param length \p数据包的大小。\param buf足够大的结果缓冲区，可以容纳生成的摘要。
 */
void dtls_mac(dtls_hmac_context_t *hmac_ctx, 
	      const unsigned char *record,
	      const unsigned char *packet, size_t length,
	      unsigned char *buf);

/**
 * 表示dtls_encrypt_params（）的AEAD参数。
 */
typedef struct {
  const uint8_t *nonce;         /**<必须正好是15-l字节*/
  uint8_t tag_length;           /**<MAC标签长度（M）*/
  uint8_t l;                    /**<长度*字段中的字节数（L）*/
} dtls_ccm_params_t;

/**
 * 加密给定长度的指定\p src，将结果写入\p buf。密码实现可以向结果缓冲器添加更多数据，例如初始化向量或填充（例如。因此，调用者必须确保\pbuf提供足够的存储空间来保存结果。通常这意味着（2+\p长度/块大小）块大小。该函数在出错时返回一个小于零的值，否则返回写入的字节数。
 *
 * \param params AEAD参数：Nonce、M和L。\param src要加密的数据。\param length \p src的实际大小。\param buf结果缓冲区。\p src和\p buf不能重叠。\param aad AEAD密码的附加数据\param aad_length实际大小@p aad\return成功时加密的字节数，否则小于零。
 */
int dtls_encrypt_params(const dtls_ccm_params_t *params,
                        const unsigned char *src, size_t length,
                        unsigned char *buf,
                        const unsigned char *key, size_t keylen,
                        const unsigned char *aad, size_t aad_length);

/** 
 * 加密给定长度的指定\p src，将结果写入\p buf。密码实现可以向结果缓冲器添加更多数据，例如初始化向量或填充（例如。因此，调用者必须确保\pbuf提供足够的存储空间来保存结果。通常这意味着（2+\p长度/块大小）块大小。该函数在出错时返回一个小于零的值，否则返回写入的字节数。
 *
 * \param src要加密的数据。\param length \p src的实际大小。\param buf结果缓冲区。\p src和\p buf不能重叠。\param nonce用于加密的nonce。必须正好为13个字节，因为L设置为2。\param aad AEAD密码的附加数据\param aad_length实际大小@p aad\return成功时加密的字节数，否则小于零。
 *
 * \已弃用的dtls_encrypt（）始终设置M=8，L=2。请改用dtls_eencrypt_params（）。
 */
int dtls_encrypt(const unsigned char *src, size_t length,
		 unsigned char *buf,
		 const unsigned char *nonce,
		 const unsigned char *key, size_t keylen,
		 const unsigned char *aad, size_t aad_length);

/**
 * 解密给定长度的给定缓冲区\p src，将结果写入\p buf。如果出现错误或写入的字节数，函数将返回\c-1。注意，对于块密码，\p长度必须是密码块大小的倍数。介于\c 0和实际长度之间的返回值表示只处理了\c n-1个块。与dtls_encrypt（）不同，dtls_decrypt（）的源和目标可能重叠。
 *
 * \param params AEAD参数：Nonce、M和L。\param length输入缓冲区的长度。\param buf结果缓冲区。\param aad AEAD密码的附加身份验证数据\param aad_length实际大小@p aad\return出错时小于零，否则为解密字节数。
 */
int dtls_decrypt_params(const dtls_ccm_params_t *params,
                        const unsigned char *src, size_t length,
                        unsigned char *buf,
                        const unsigned char *key, size_t keylen,
                        const unsigned char *aad, size_t aad_length);

/** 
 * 解密给定长度的给定缓冲区\p src，将结果写入\p buf。如果出现错误或写入的字节数，函数将返回\c-1。注意，对于块密码，\p长度必须是密码块大小的倍数。介于\c 0和实际长度之间的返回值表示只处理了\c n-1个块。与dtls_encrypt（）不同，dtls_decrypt（）的源和目标可能重叠。
 * 
 * \param src要解密的缓冲区。\param length输入缓冲区的长度。\param buf结果缓冲区。\param nonce用于加密的nonce。必须正好为13个字节，因为L设置为2。\param aad AEAD密码的附加身份验证数据\param aad_length实际大小@p aad\return出错时小于零，否则为解密字节数。
 *
 * \已弃用的dtls_decrypt（）始终设置M=8，L=2。请改用dtls_decrypt_params（）。
 */
int dtls_decrypt(const unsigned char *src, size_t length,
		 unsigned char *buf,
		 const unsigned char *nonce,
		 const unsigned char *key, size_t keylen,
		 const unsigned char *a_data, size_t a_data_length);

/* 助手函数*/

/** 
 * 根据给定的PSK生成pre_master_sercet，并根据RFC 4279第2节中的“普通PSK”情况填充结果。目前不支持Diffie-Hellman和RSA密钥交换。
 *
 * @param key    共享密钥。
 * @param keylen @p键的长度（字节）。
 * @param result 派生的预主密钥。
 * @return @p结果的实际长度。
 */
int dtls_psk_pre_master_secret(unsigned char *key, size_t keylen,
			       unsigned char *result, size_t result_len);

#define DTLS_EC_KEY_SIZE 32

int dtls_ecdh_pre_master_secret(unsigned char *priv_key,
				unsigned char *pub_key_x,
                                unsigned char *pub_key_y,
                                size_t key_size,
                                unsigned char *result,
                                size_t result_len);

void dtls_ecdsa_generate_key(unsigned char *priv_key,
			     unsigned char *pub_key_x,
			     unsigned char *pub_key_y,
			     size_t key_size);

void dtls_ecdsa_create_sig_hash(const unsigned char *priv_key, size_t key_size,
				const unsigned char *sign_hash, size_t sign_hash_size,
				uint32_t point_r[9], uint32_t point_s[9]);

void dtls_ecdsa_create_sig(const unsigned char *priv_key, size_t key_size,
			   const unsigned char *client_random, size_t client_random_size,
			   const unsigned char *server_random, size_t server_random_size,
			   const unsigned char *keyx_params, size_t keyx_params_size,
			   uint32_t point_r[9], uint32_t point_s[9]);

int dtls_ecdsa_verify_sig_hash(const unsigned char *pub_key_x,
			       const unsigned char *pub_key_y, size_t key_size,
			       const unsigned char *sign_hash, size_t sign_hash_size,
			       unsigned char *result_r, unsigned char *result_s);

int dtls_ecdsa_verify_sig(const unsigned char *pub_key_x,
			  const unsigned char *pub_key_y, size_t key_size,
			  const unsigned char *client_random, size_t client_random_size,
			  const unsigned char *server_random, size_t server_random_size,
			  const unsigned char *keyx_params, size_t keyx_params_size,
			  unsigned char *result_r, unsigned char *result_s);

int dtls_ec_key_from_uint32_asn1(const uint32_t *key, size_t key_size,
				 unsigned char *buf);


dtls_handshake_parameters_t *dtls_handshake_new(void);

void dtls_handshake_free(dtls_handshake_parameters_t *handshake);

dtls_security_parameters_t *dtls_security_new(void);

void dtls_security_free(dtls_security_parameters_t *security);
void crypto_init(void);

#endif /* _DTLS_CRYPTO_H_ */


