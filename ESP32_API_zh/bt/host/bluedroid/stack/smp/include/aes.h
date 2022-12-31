/*
 ---------------------------------------------------------------------------版权所有（c）1998-2008，布赖恩·格拉德曼，英国伍斯特。保留所有权利。

 LICENSE TERMS

 允许在不支付费用或特许权使用费的情况下重新分发和使用本软件（无论有无更改），前提是：

  1.源代码分发包括上述版权声明、本条件列表和以下免责声明；

  2.二进制发行包括上述版权声明、本条件列表和以下文档中的免责声明；

  3.未经特定书面许可，不得使用版权持有人的名称为使用本软件构建的产品背书。

 DISCLAIMER

 本软件按“原样”提供，对其属性（包括但不限于正确性和/或适用性）没有任何明示或暗示的保证。
 ---------------------------------------------------------------------------2006年9月9日发行

 这是一个AES实现，仅对密码状态使用8位字节操作。
 */

#ifndef AES_H
#define AES_H

#if 1
#  define AES_ENC_PREKEYED  /* 使用预先计算的密钥计划进行AES加密*/
#endif
#if 1
#  define AES_DEC_PREKEYED  /* 使用预先计算的密钥调度进行AES解密*/
#endif
#if 1
#  define AES_ENC_128_OTFK  /* 使用“动态”128位密钥的AES加密*/
#endif
#if 1
#  define AES_DEC_128_OTFK  /* 使用“动态”128位密钥的AES解密*/
#endif
#if 1
#  define AES_ENC_256_OTFK  /* 使用“动态”256位密钥的AES加密*/
#endif
#if 1
#  define AES_DEC_256_OTFK  /* 使用“动态”256位密钥的AES解密*/
#endif

#define N_ROW                   4
#define N_COL                   4
#define N_BLOCK   (N_ROW * N_COL)
#define N_MAX_ROUNDS           14

typedef unsigned char uint_8t;

typedef uint_8t return_type;

/*  警告：256位密钥的密钥长度溢出一个字节（请参阅下面的注释）
*/

typedef uint_8t length_type;

typedef struct {
    uint_8t ksch[(N_MAX_ROUNDS + 1) * N_BLOCK];
    uint_8t rnd;
} aes_context;

/*  以下调用用于预计算的密钥调度

    注：如果用于密钥长度的length_type是无符号8位字符，则必须输入256位密钥长度作为字节长度（因此有效输入为128、192、16、24和32）。
*/

#if defined( AES_ENC_PREKEYED ) || defined( AES_DEC_PREKEYED )

return_type aes_set_key( const unsigned char key[],
                         length_type keylen,
                         aes_context ctx[1] );
#endif

#if defined( AES_ENC_PREKEYED )

return_type bluedroid_aes_encrypt( const unsigned char in[N_BLOCK],
                                   unsigned char out[N_BLOCK],
                                   const aes_context ctx[1] );

return_type aes_cbc_encrypt( const unsigned char *in,
                             unsigned char *out,
                             int n_block,
                             unsigned char iv[N_BLOCK],
                             const aes_context ctx[1] );
#endif

#if defined( AES_DEC_PREKEYED )

return_type bluedroid_aes_decrypt( const unsigned char in[N_BLOCK],
                                   unsigned char out[N_BLOCK],
                                   const aes_context ctx[1] );

return_type aes_cbc_decrypt( const unsigned char *in,
                             unsigned char *out,
                             int n_block,
                             unsigned char iv[N_BLOCK],
                             const aes_context ctx[1] );
#endif

/*  以下调用用于“动态”键控。在这种情况下，加密和解密密钥是不同的。

    加密子例程采用密钥[L]中字节数组中的密钥，其中对于128、192和256位的密钥长度，L分别为16、24或32字节。然后，他们用这个密钥对输入数据进行加密，输入[]，并将重用放入输出数组out[]。此外，第二密钥数组o_key[L]用于输出解密子例程所需的密钥，以反转加密操作。两个键数组可以是相同的数组，但在这种情况下，原始键将被覆盖。

    以同样的方式，解密子例程输出密钥，当用于加密时，这些密钥可用于反转其效果。

    在这些“动态”模式中，仅支持128位和256位密钥。
*/

#if defined( AES_ENC_128_OTFK )
void bluedroid_aes_encrypt_128( const unsigned char in[N_BLOCK],
                                unsigned char out[N_BLOCK],
                                const unsigned char key[N_BLOCK],
                                uint_8t o_key[N_BLOCK] );
#endif

#if defined( AES_DEC_128_OTFK )
void bluedroid_aes_decrypt_128( const unsigned char in[N_BLOCK],
                                unsigned char out[N_BLOCK],
                                const unsigned char key[N_BLOCK],
                                unsigned char o_key[N_BLOCK] );
#endif

#if defined( AES_ENC_256_OTFK )
void bluedroid_aes_encrypt_256( const unsigned char in[N_BLOCK],
                                unsigned char out[N_BLOCK],
                                const unsigned char key[2 * N_BLOCK],
                                unsigned char o_key[2 * N_BLOCK] );
#endif

#if defined( AES_DEC_256_OTFK )
void bluedroid_aes_decrypt_256( const unsigned char in[N_BLOCK],
                                unsigned char out[N_BLOCK],
                                const unsigned char key[2 * N_BLOCK],
                                unsigned char o_key[2 * N_BLOCK] );
#endif

#endif

