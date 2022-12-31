/*$OpenBSD:rijndael。h、 v 1.13 2008/06/09 07:49:45 djm支出$*/

/**
 * 第八章
 *
 * @version 3.0（2000年12月）
 *
 * Rijndael密码（现为AES）的优化ANSI C代码
 *
 * @author 文森特·里梅恩<vincent.rijmen@esat.kuleuven.ac.be>
 * @author Anton Bosselars公司<antoon.bosselaers@esat.kuleuven.ac.be>
 * @author 保罗·巴雷托<paulo.barreto@terra.com.br>
 *
 * 此代码特此公开。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __RIJNDAEL_H
#define __RIJNDAEL_H

#include <stdint.h>

#define AES_MAXKEYBITS	(256)
#define AES_MAXKEYBYTES	(AES_MAXKEYBITS/8)
/* 对于256位密钥，128位密钥需要14个循环，只需要10个循环*/
#define AES_MAXROUNDS	10

/* bergmann：为了避免与来自某些Contiki平台的typedef冲突，以下类型名称的前缀为“aes_”：*/
typedef unsigned char	u_char;
typedef uint8_t		aes_u8;
typedef uint16_t	aes_u16;
typedef uint32_t	aes_u32;

/*  关键信息的结构*/
typedef struct {
#ifdef WITH_AES_DECRYPT
	int	enc_only;		/* 上下文仅包含加密计划*/
#endif
	int	Nr;			/* 取决于密钥长度的循环数*/
	aes_u32	ek[4*(AES_MAXROUNDS + 1)];	/* 加密密钥计划*/
#ifdef WITH_AES_DECRYPT
	aes_u32	dk[4*(AES_MAXROUNDS + 1)];	/* 解密密钥计划*/
#endif
} rijndael_ctx;

int	 rijndael_set_key(rijndael_ctx *, const u_char *, int);
int	 rijndael_set_key_enc_only(rijndael_ctx *, const u_char *, int);
void	 rijndael_decrypt(rijndael_ctx *, const u_char *, u_char *);
void	 rijndael_encrypt(rijndael_ctx *, const u_char *, u_char *);

int	rijndaelKeySetupEnc(aes_u32 rk[/*4*（个+1）*/], const aes_u8 cipherKey[], int keyBits);
int	rijndaelKeySetupDec(aes_u32 rk[/*4*（个+1）*/], const aes_u8 cipherKey[], int keyBits);
void	rijndaelEncrypt(const aes_u32 rk[/*4*（个+1）*/], int Nr, const aes_u8 pt[16], aes_u8 ct[16]);
#ifdef WITH_AES_DECRYPT
void	rijndaelDecrypt(const aes_u32 rk[/*4*（个+1）*/], int Nr, const aes_u8 ct[16], aes_u8 pt[16]);
#endif

#endif /* __RIJNDAEL_H */

