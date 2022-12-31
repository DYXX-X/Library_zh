/*******************************************************************************
 * 版权所有（c）2011、2012、2013、2014、2015奥拉夫·伯格曼（TZI）和其他人。保留所有权利。本程序和随附材料根据本发行版附带的Eclipse公共许可证v1.0和Eclipse发行许可证v1.1的条款提供。
 *
 * Eclipse公共许可证位于http://www.eclipse.org/legal/epl-v10.htmlEclipse发行许可证在http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * 贡献者：Olaf Bergmann-初始API和实现Hauke Mehrtens-内存优化、ECC集成
 *
 *******************************************************************************/

#ifndef _DTLS_NUMERIC_H_
#define _DTLS_NUMERIC_H_

#include <stdint.h>

#ifndef min
#define min(A,B) ((A) <= (B) ? (A) : (B))
#endif

#ifndef max
#define max(A,B) ((A) < (B) ? (B) : (A))
#endif

/* 这是为了一致性。。。*/
static inline int dtls_int_to_uint8(unsigned char *field, uint8_t value)
{
  field[0] = value & 0xff;
  return 1;
}

static inline int dtls_int_to_uint16(unsigned char *field, uint16_t value)
{
  field[0] = (value >> 8) & 0xff;
  field[1] = value & 0xff;
  return 2;
}

static inline int dtls_int_to_uint24(unsigned char *field, uint32_t value)
{
  field[0] = (value >> 16) & 0xff;
  field[1] = (value >> 8) & 0xff;
  field[2] = value & 0xff;
  return 3;
}

static inline int dtls_int_to_uint32(unsigned char *field, uint32_t value)
{
  field[0] = (value >> 24) & 0xff;
  field[1] = (value >> 16) & 0xff;
  field[2] = (value >> 8) & 0xff;
  field[3] = value & 0xff;
  return 4;
}

static inline int dtls_int_to_uint48(unsigned char *field, uint64_t value)
{
  field[0] = (value >> 40) & 0xff;
  field[1] = (value >> 32) & 0xff;
  field[2] = (value >> 24) & 0xff;
  field[3] = (value >> 16) & 0xff;
  field[4] = (value >> 8) & 0xff;
  field[5] = value & 0xff;
  return 6;
}

static inline int dtls_int_to_uint64(unsigned char *field, uint64_t value)
{
  field[0] = (value >> 56) & 0xff;
  field[1] = (value >> 48) & 0xff;
  field[2] = (value >> 40) & 0xff;
  field[3] = (value >> 32) & 0xff;
  field[4] = (value >> 24) & 0xff;
  field[5] = (value >> 16) & 0xff;
  field[6] = (value >> 8) & 0xff;
  field[7] = value & 0xff;
  return 8;
}

static inline uint8_t dtls_uint8_to_int(const unsigned char *field)
{
  return (uint8_t)field[0];
}

static inline uint16_t dtls_uint16_to_int(const unsigned char *field)
{
  return ((uint16_t)field[0] << 8)
	 | (uint16_t)field[1];
}

static inline uint32_t dtls_uint24_to_int(const unsigned char *field)
{
  return ((uint32_t)field[0] << 16)
	 | ((uint32_t)field[1] << 8)
	 | (uint32_t)field[2];
}

static inline uint32_t dtls_uint32_to_int(const unsigned char *field)
{
  return ((uint32_t)field[0] << 24)
	 | ((uint32_t)field[1] << 16)
	 | ((uint32_t)field[2] << 8)
	 | (uint32_t)field[3];
}

static inline uint64_t dtls_uint48_to_int(const unsigned char *field)
{
  return ((uint64_t)field[0] << 40)
	 | ((uint64_t)field[1] << 32)
	 | ((uint64_t)field[2] << 24)
	 | ((uint64_t)field[3] << 16)
	 | ((uint64_t)field[4] << 8)
	 | (uint64_t)field[5];
}

static inline uint64_t dtls_uint64_to_int(const unsigned char *field)
{
  return ((uint64_t)field[0] << 56)
	 | ((uint64_t)field[1] << 48)
	 | ((uint64_t)field[2] << 40)
	 | ((uint64_t)field[3] << 32)
	 | ((uint64_t)field[4] << 24)
	 | ((uint64_t)field[5] << 16)
	 | ((uint64_t)field[6] << 8)
	 | (uint64_t)field[7];
}

#endif /* _DTLS_NUMERIC_H_ */

