/*
 * 文件：sha2.h作者：Aaron D.Gifford-http://www.aarongifford.com/
 * 
 * 版权所有（c）2000-2001，Aaron D.Gifford保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或贡献者的姓名为本软件衍生的产品背书或推广。
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTOR(S) ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id:sha2.h，v 1.1 2001/11/08 00:02:01 adg到期日$
 */

#ifndef __SHA2_H__
#define __SHA2_H__

#ifdef __cplusplus
extern "C" {
#endif


/*
 * 从系统标头导入u_intXX_t size_t类型定义。您可能需要对此进行更改，或在此文件中自行定义这些内容。
 */
#include <sys/types.h>
#include "tinydtls.h"

#ifdef SHA2_USE_INTTYPES_H

#include <inttypes.h>

#endif /* SHA2_USE_INTTYPES_H */


/***SHA-256/384/512各种长度定义***********************/
#define DTLS_SHA256_BLOCK_LENGTH		64
#define DTLS_SHA256_DIGEST_LENGTH		32
#define DTLS_SHA256_DIGEST_STRING_LENGTH	(DTLS_SHA256_DIGEST_LENGTH * 2 + 1)
#define DTLS_SHA384_BLOCK_LENGTH		128
#define DTLS_SHA384_DIGEST_LENGTH		48
#define DTLS_SHA384_DIGEST_STRING_LENGTH	(DTLS_SHA384_DIGEST_LENGTH * 2 + 1)
#define DTLS_SHA512_BLOCK_LENGTH		128
#define DTLS_SHA512_DIGEST_LENGTH		64
#define DTLS_SHA512_DIGEST_STRING_LENGTH	(DTLS_SHA512_DIGEST_LENGTH * 2 + 1)


/***SHA-256/384/512上下文结构*******************************/
/* 注意：如果您的体系结构没有定义u_intXX_t类型或uintXX_t（来自inttypes.h），您可能需要为系统手动定义：
 */
#if 0
typedef unsigned char u_int8_t;		/* 1字节（8位）*/
typedef unsigned int u_int32_t;		/* 4字节（32位）*/
typedef unsigned long long u_int64_t;	/* 8字节（64位）*/
#endif
/*
 * 大多数BSD系统已经定义了u_intXX_t类型，Linux也是如此。但是，某些系统（如Compaq的Tru64 Unix）可以使用由最新的ANSI C标准定义的uintXX_t类型，并包含在文件中：
 *
 *   #包括<inttypes.h>
 *
 * 如果选择使用<intypes。h> 那么请定义：
 *
 *   #定义SHA2_USE_INTTYPES_H
 *
 * 或在编译期间在命令行上：
 *
 *   抄送-DSHA2_USE_INTTYPES_H。。。
 */
#ifdef SHA2_USE_INTTYPES_H

typedef struct _dtls_sha256_ctx {
	uint32_t	state[8];
	uint64_t	bitcount;
	uint8_t	buffer[DTLS_SHA256_BLOCK_LENGTH];
} dtls_sha256_ctx;
typedef struct _dtls_sha512_ctx {
	uint64_t	state[8];
	uint64_t	bitcount[2];
	uint8_t	buffer[DTLS_SHA512_BLOCK_LENGTH];
} dtls_sha512_ctx;

#else /* SHA2_USE_INTTYPES_H */

typedef struct _dtls_sha256_ctx {
	u_int32_t	state[8];
	u_int64_t	bitcount;
	u_int8_t	buffer[DTLS_SHA256_BLOCK_LENGTH];
} dtls_sha256_ctx;
typedef struct _dtls_sha512_ctx {
	u_int64_t	state[8];
	u_int64_t	bitcount[2];
	u_int8_t	buffer[DTLS_SHA512_BLOCK_LENGTH];
} dtls_sha512_ctx;

#endif /* SHA2_USE_INTTYPES_H */

typedef dtls_sha512_ctx dtls_sha384_ctx;


/***SHA-256/384/512功能原型******************************/
#ifndef NOPROTO
#ifdef SHA2_USE_INTTYPES_H

#ifdef WITH_SHA256
void dtls_sha256_init(dtls_sha256_ctx *);
void dtls_sha256_update(dtls_sha256_ctx*, const uint8_t*, size_t);
void dtls_sha256_final(uint8_t[DTLS_SHA256_DIGEST_LENGTH], dtls_sha256_ctx*);
char* dtls_sha256_end(dtls_sha256_ctx*, char[DTLS_SHA256_DIGEST_STRING_LENGTH]);
char* dtls_sha256_data(const uint8_t*, size_t, char[DTLS_SHA256_DIGEST_STRING_LENGTH]);
#endif

#ifdef WITH_SHA384
void dtls_sha384_init(dtls_sha384_ctx*);
void dtls_sha384_update(dtls_sha384_ctx*, const uint8_t*, size_t);
void dtls_sha384_final(uint8_t[DTLS_SHA384_DIGEST_LENGTH], dtls_sha384_ctx*);
char* dtls_sha384_end(dtls_sha384_ctx*, char[DTLS_SHA384_DIGEST_STRING_LENGTH]);
char* dtls_sha384_data(const uint8_t*, size_t, char[DTLS_SHA384_DIGEST_STRING_LENGTH]);
#endif

#ifdef WITH_SHA512
void dtls_sha512_init(dtls_sha512_ctx*);
void dtls_sha512_update(dtls_sha512_ctx*, const uint8_t*, size_t);
void dtls_sha512_final(uint8_t[DTLS_SHA512_DIGEST_LENGTH], dtls_sha512_ctx*);
char* dtls_sha512_end(dtls_sha512_ctx*, char[DTLS_SHA512_DIGEST_STRING_LENGTH]);
char* dtls_sha512_data(const uint8_t*, size_t, char[DTLS_SHA512_DIGEST_STRING_LENGTH]);
#endif

#else /* SHA2_USE_INTTYPES_H */

#ifdef WITH_SHA256
void dtls_sha256_init(dtls_sha256_ctx *);
void dtls_sha256_update(dtls_sha256_ctx*, const u_int8_t*, size_t);
void dtls_sha256_final(u_int8_t[DTLS_SHA256_DIGEST_LENGTH], dtls_sha256_ctx*);
char* dtls_sha256_end(dtls_sha256_ctx*, char[DTLS_SHA256_DIGEST_STRING_LENGTH]);
char* dtls_sha256_data(const u_int8_t*, size_t, char[DTLS_SHA256_DIGEST_STRING_LENGTH]);
#endif

#ifdef WITH_SHA384
void dtls_sha384_init(dtls_sha384_ctx*);
void dtls_sha384_update(dtls_sha384_ctx*, const u_int8_t*, size_t);
void dtls_sha384_final(u_int8_t[DTLS_SHA384_DIGEST_LENGTH], dtls_sha384_ctx*);
char* dtls_sha384_end(dtls_sha384_ctx*, char[DTLS_SHA384_DIGEST_STRING_LENGTH]);
char* dtls_sha384_data(const u_int8_t*, size_t, char[DTLS_SHA384_DIGEST_STRING_LENGTH]);
#endif

#ifdef WITH_SHA512
void dtls_sha512_init(dtls_sha512_ctx*);
void dtls_sha512_update(dtls_sha512_ctx*, const u_int8_t*, size_t);
void dtls_sha512_final(u_int8_t[DTLS_SHA512_DIGEST_LENGTH], dtls_sha512_ctx*);
char* dtls_sha512_end(dtls_sha512_ctx*, char[DTLS_SHA512_DIGEST_STRING_LENGTH]);
char* dtls_sha512_data(const u_int8_t*, size_t, char[DTLS_SHA512_DIGEST_STRING_LENGTH]);
#endif

#endif /* SHA2_USE_INTTYPES_H */

#else /* NOPROTO */

#ifdef WITH_SHA256
void dtls_sha256_init();
void dtls_sha256_update();
void dtls_sha256_final();
char* dtls_sha256_end();
char* dtls_sha256_data();
#endif

#ifdef WITH_SHA384
void dtls_sha384_init();
void dtls_sha384_update();
void dtls_sha384_final();
char* dtls_sha384_end();
char* dtls_sha384_data();
#endif

#ifdef WITH_SHA512
void dtls_sha512_init();
void dtls_sha512_update();
void dtls_sha512_final();
char* dtls_sha512_end();
char* dtls_sha512_data();
#endif

#endif /* NOPROTO */

#ifdef	__cplusplus
}
#endif /* __cplusplus公司*/

#endif /* __SHA2_H__ */


