/* 
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019 Ha Thach（tinyusb.org）
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

/** \ingroup Group_Common\defgroup Group_CommonH Common.h
 *  @{ */

#ifndef _TUSB_COMMON_H_
#define _TUSB_COMMON_H_

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 宏帮助程序
//--------------------------------------------------------------------+
#define TU_ARRAY_SIZE(_arr)   ( sizeof(_arr) / sizeof(_arr[0]) )
#define TU_MIN(_x, _y)        ( ( (_x) < (_y) ) ? (_x) : (_y) )
#define TU_MAX(_x, _y)        ( ( (_x) > (_y) ) ? (_x) : (_y) )

#define TU_U16_HIGH(u16)      ((uint8_t) (((u16) >> 8) & 0x00ff))
#define TU_U16_LOW(u16)       ((uint8_t) ((u16)       & 0x00ff))
#define U16_TO_U8S_BE(u16)    TU_U16_HIGH(u16), TU_U16_LOW(u16)
#define U16_TO_U8S_LE(u16)    TU_U16_LOW(u16), TU_U16_HIGH(u16)

#define U32_B1_U8(u32)        ((uint8_t) ((((uint32_t) u32) >> 24) & 0x000000ff)) // MSB
#define U32_B2_U8(u32)        ((uint8_t) ((((uint32_t) u32) >> 16) & 0x000000ff))
#define U32_B3_U8(u32)        ((uint8_t) ((((uint32_t) u32) >>  8) & 0x000000ff))
#define U32_B4_U8(u32)        ((uint8_t) (((uint32_t)  u32)        & 0x000000ff)) // LSB

#define U32_TO_U8S_BE(u32)    U32_B1_U8(u32), U32_B2_U8(u32), U32_B3_U8(u32), U32_B4_U8(u32)
#define U32_TO_U8S_LE(u32)    U32_B4_U8(u32), U32_B3_U8(u32), U32_B2_U8(u32), U32_B1_U8(u32)

#define TU_BIT(n)             (1U << (n))

//--------------------------------------------------------------------+
// 包括
//--------------------------------------------------------------------+

// 标准页眉
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

// Tinyusb通用接头
#include "tusb_option.h"
#include "tusb_compiler.h"
#include "tusb_verify.h"
#include "tusb_error.h" // TODO删除
#include "tusb_timeout.h"
#include "tusb_types.h"

//-------------备忘录-------------//
#define tu_memclr(buffer, size)  memset((buffer), 0, (size))
#define tu_varclr(_var)          tu_memclr(_var, sizeof(*(_var)))

//-------------字节-------------//
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_u32(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
  return ( ((uint32_t) b1) << 24) | ( ((uint32_t) b2) << 16) | ( ((uint32_t) b3) << 8) | b4;
}

TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_u16(uint8_t high, uint8_t low)
{
  return (uint16_t) ((((uint16_t) high) << 8) | low);
}

TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_u16_high(uint16_t u16) { return (uint8_t) (((uint16_t) (u16 >> 8)) & 0x00ff); }
TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_u16_low (uint16_t u16) { return (uint8_t) (u16 & 0x00ff); }

//-------------钻头-------------//
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_bit_set  (uint32_t value, uint8_t pos) { return value | TU_BIT(pos);                  }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_bit_clear(uint32_t value, uint8_t pos) { return value & (~TU_BIT(pos));               }
TU_ATTR_ALWAYS_INLINE static inline bool     tu_bit_test (uint32_t value, uint8_t pos) { return (value & TU_BIT(pos)) ? true : false; }

//-------------最小值-------------//
TU_ATTR_ALWAYS_INLINE static inline uint8_t  tu_min8  (uint8_t  x, uint8_t y ) { return (x < y) ? x : y; }
TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_min16 (uint16_t x, uint16_t y) { return (x < y) ? x : y; }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_min32 (uint32_t x, uint32_t y) { return (x < y) ? x : y; }

//-------------最大值-------------//
TU_ATTR_ALWAYS_INLINE static inline uint8_t  tu_max8  (uint8_t  x, uint8_t y ) { return (x > y) ? x : y; }
TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_max16 (uint16_t x, uint16_t y) { return (x > y) ? x : y; }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_max32 (uint32_t x, uint32_t y) { return (x > y) ? x : y; }

//-------------对齐-------------//
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_align(uint32_t value, uint32_t alignment)
{
  return value & ((uint32_t) ~(alignment-1));
}

TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_align32 (uint32_t value) { return (value & 0xFFFFFFE0UL); }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_align16 (uint32_t value) { return (value & 0xFFFFFFF0UL); }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_align4k (uint32_t value) { return (value & 0xFFFFF000UL); }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_offset4k(uint32_t value) { return (value & 0xFFFUL); }

//-------------数学-------------//
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_abs(int32_t value) { return (uint32_t)((value < 0) ? (-value) : value); }

///包含范围检查TODO删除
TU_ATTR_ALWAYS_INLINE static inline bool tu_within(uint32_t lower, uint32_t value, uint32_t upper)
{
  return (lower <= value) && (value <= upper);
}

// 值的log2是其MSB的位置
// TODO使用clz TODO移除
static inline uint8_t tu_log2(uint32_t value)
{
  uint8_t result = 0;
  while (value >>= 1) { result++; }
  return result;
}

//-------------未对齐的访问-------------//
#if TUP_ARCH_STRICT_ALIGN

typedef struct { uint16_t val; } TU_ATTR_PACKED tu_unaligned_uint16_t;
typedef struct { uint32_t val; } TU_ATTR_PACKED tu_unaligned_uint32_t;

TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_unaligned_read32(const void* mem)
{
  tu_unaligned_uint32_t const* ua32 = (tu_unaligned_uint32_t const*) mem;
  return ua32->val;
}

TU_ATTR_ALWAYS_INLINE static inline void tu_unaligned_write32(void* mem, uint32_t value)
{
  tu_unaligned_uint32_t* ua32 = (tu_unaligned_uint32_t*) mem;
  ua32->val = value;
}

TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_unaligned_read16(const void* mem)
{
  tu_unaligned_uint16_t const* ua16 = (tu_unaligned_uint16_t const*) mem;
  return ua16->val;
}

TU_ATTR_ALWAYS_INLINE static inline void tu_unaligned_write16(void* mem, uint16_t value)
{
  tu_unaligned_uint16_t* ua16 = (tu_unaligned_uint16_t*) mem;
  ua16->val = value;
}

#else

TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_unaligned_read32  (const void* mem           ) { return *((uint32_t*) mem);  }
TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_unaligned_read16  (const void* mem           ) { return *((uint16_t*) mem);  }

TU_ATTR_ALWAYS_INLINE static inline void     tu_unaligned_write32 (void* mem, uint32_t value ) { *((uint32_t*) mem) = value; }
TU_ATTR_ALWAYS_INLINE static inline void     tu_unaligned_write16 (void* mem, uint16_t value ) { *((uint16_t*) mem) = value; }

#endif

/*------------------------------------------------------------------*/
/* __VA_ARGS的参数计数__
 * -参考https://groups.google.com/forum/#!主题/comp.std.c/d-6Mj5Lko_s
 * -_GET_NTH_ARG（）接受参数>=N（64），但仅扩展到第N个（64）
 * -_RSEQ_N（）与N的顺序相反，以添加填充，使第N个位置与参数的数量相同
 * -##__VA_ARGS__用于处理0参数（包含逗号）
 *------------------------------------------------------------------*/
#ifndef TU_ARGS_NUM

#define TU_ARGS_NUM(...) 	 _TU_NARG(_0, ##__VA_ARGS__,_RSEQ_N())

#define _TU_NARG(...)        _GET_NTH_ARG(__VA_ARGS__)
#define _GET_NTH_ARG( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define _RSEQ_N() \
         62,61,60,                      \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0
#endif

// 待移除
//-------------二进制常数-------------//
#if defined(__GNUC__) && !defined(__CC_ARM)

#define TU_BIN8(x)               ((uint8_t)  (0b##x))
#define TU_BIN16(b1, b2)         ((uint16_t) (0b##b1##b2))
#define TU_BIN32(b1, b2, b3, b4) ((uint32_t) (0b##b1##b2##b3##b4))

#else

//  B8、B16、B32的内部宏
#define _B8__(x) (((x&0x0000000FUL)?1:0) \
                +((x&0x000000F0UL)?2:0) \
                +((x&0x00000F00UL)?4:0) \
                +((x&0x0000F000UL)?8:0) \
                +((x&0x000F0000UL)?16:0) \
                +((x&0x00F00000UL)?32:0) \
                +((x&0x0F000000UL)?64:0) \
                +((x&0xF0000000UL)?128:0))

#define TU_BIN8(d) ((uint8_t) _B8__(0x##d##UL))
#define TU_BIN16(dmsb,dlsb) (((uint16_t)TU_BIN8(dmsb)<<8) + TU_BIN8(dlsb))
#define TU_BIN32(dmsb,db2,db3,dlsb) \
            (((uint32_t)TU_BIN8(dmsb)<<24) \
            + ((uint32_t)TU_BIN8(db2)<<16) \
            + ((uint32_t)TU_BIN8(db3)<<8) \
            + TU_BIN8(dlsb))
#endif

//--------------------------------------------------------------------+
// 调试函数
//--------------------------------------------------------------------+

// CFG_TUSB_DEBUG用于调试
// 0：无调试
// 1：错误时打印
// 2：打印日志
#if CFG_TUSB_DEBUG

void tu_print_mem(void const *buf, uint32_t count, uint8_t indent);

#ifdef CFG_TUSB_DEBUG_PRINTF
  extern int CFG_TUSB_DEBUG_PRINTF(const char *format, ...);
  #define tu_printf    CFG_TUSB_DEBUG_PRINTF
#else
  #define tu_printf    printf
#endif

static inline
void tu_print_var(uint8_t const* buf, uint32_t bufsize)
{
  for(uint32_t i=0; i<bufsize; i++) tu_printf("%02X ", buf[i]);
}

// 使用调试级别1记录
#define TU_LOG1               tu_printf
#define TU_LOG1_MEM           tu_print_mem
#define TU_LOG1_VAR(_x)       tu_print_var((uint8_t const*)(_x), sizeof(*(_x)))
#define TU_LOG1_INT(_x)       tu_printf(#_x " = %ld\n", (uint32_t) (_x) )
#define TU_LOG1_HEX(_x)       tu_printf(#_x " = %lX\n", (uint32_t) (_x) )
#define TU_LOG1_LOCATION()    tu_printf("%s: %d:\r\n", __PRETTY_FUNCTION__, __LINE__)
#define TU_LOG1_FAILED()      tu_printf("%s: %d: Failed\r\n", __PRETTY_FUNCTION__, __LINE__)

// 使用调试级别2记录
#if CFG_TUSB_DEBUG > 1
  #define TU_LOG2             TU_LOG1
  #define TU_LOG2_MEM         TU_LOG1_MEM
  #define TU_LOG2_VAR         TU_LOG1_VAR
  #define TU_LOG2_INT         TU_LOG1_INT
  #define TU_LOG2_HEX         TU_LOG1_HEX
  #define TU_LOG2_LOCATION()  TU_LOG1_LOCATION()
#endif


typedef struct
{
  uint32_t key;
  const char* data;
} tu_lookup_entry_t;

typedef struct
{
  uint16_t count;
  tu_lookup_entry_t const* items;
} tu_lookup_table_t;

static inline const char* tu_lookup_find(tu_lookup_table_t const* p_table, uint32_t key)
{
  for(uint16_t i=0; i<p_table->count; i++)
  {
    if (p_table->items[i].key == key) return p_table->items[i].data;
  }

  return NULL;
}

#endif // CFG_TUSB_DEBUG

#ifndef TU_LOG1
  #define TU_LOG1(...)
  #define TU_LOG1_MEM(...)
  #define TU_LOG1_VAR(...)
  #define TU_LOG1_INT(...)
  #define TU_LOG1_HEX(...)
  #define TU_LOG1_LOCATION()
  #define TU_LOG1_FAILED()
#endif

#ifndef TU_LOG2
  #define TU_LOG2(...)
  #define TU_LOG2_MEM(...)
  #define TU_LOG2_VAR(...)
  #define TU_LOG2_INT(...)
  #define TU_LOG2_HEX(...)
  #define TU_LOG2_LOCATION()
#endif

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_COMMON_H_ */

/**  @} */

