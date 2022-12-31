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

/** \inggroup Group_Common\defgroup Group_Compiler Compiler\brief Group_Compiller brief
 *  @{ */

#ifndef _TUSB_COMPILER_H_
#define _TUSB_COMPILER_H_

#define TU_STRING(x)      #x              ///<无扩展的字符串
#define TU_XSTRING(x)     TU_STRING(x)    ///<展开然后是字符串
#define TU_STRCAT(a, b)   a##b            ///<凹而不展开
#define TU_XSTRCAT(a, b)  TU_STRCAT(a, b) ///<先展开后凹

#if defined __COUNTER__ && __COUNTER__ != __COUNTER__
  #define _TU_COUNTER_ __COUNTER__
#else
  #define _TU_COUNTER_ __LINE__
#endif

// 编译时断言
#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
  #define TU_VERIFY_STATIC   _Static_assert
#elif defined (__cplusplus) && __cplusplus >= 201103L
  #define TU_VERIFY_STATIC   static_assert
#else
  #define TU_VERIFY_STATIC(const_expr, _mess) enum { TU_XSTRCAT(_verify_static_, _TU_COUNTER_) = 1/(!!(const_expr)) }
#endif

// 对于保留字段的声明，请使用_TU_COUNTER_
#define TU_RESERVED           TU_XSTRCAT(reserved, _TU_COUNTER_)

#define TU_LITTLE_ENDIAN (0x12u)
#define TU_BIG_ENDIAN (0x21u)

//--------------------------------------------------------------------+
// 带有属性和Endian的编译器移植
//--------------------------------------------------------------------+

// TODO重构，因为许多编译器都支持__attribute__
#if defined(__GNUC__)
  #define TU_ATTR_ALIGNED(Bytes)        __attribute__ ((aligned(Bytes)))
  #define TU_ATTR_SECTION(sec_name)     __attribute__ ((section(#sec_name)))
  #define TU_ATTR_PACKED                __attribute__ ((packed))
  #define TU_ATTR_WEAK                  __attribute__ ((weak))
  #define TU_ATTR_ALWAYS_INLINE         __attribute__ ((always_inline))
  #define TU_ATTR_DEPRECATED(mess)      __attribute__ ((deprecated(mess))) // 如果使用具有此属性的函数，则发出警告
  #define TU_ATTR_UNUSED                __attribute__ ((unused))           // 函数/变量可能未使用
  #define TU_ATTR_USED                  __attribute__ ((used))             // 要使用函数/变量

  // Endian转换使用众所周知的主机到网络（big Endian）命名
  #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define TU_BYTE_ORDER TU_LITTLE_ENDIAN
  #else
    #define TU_BYTE_ORDER TU_BIG_ENDIAN
  #endif

  #define TU_BSWAP16(u16) (__builtin_bswap16(u16))
  #define TU_BSWAP32(u32) (__builtin_bswap32(u32))

#elif defined(__TI_COMPILER_VERSION__)
  #define TU_ATTR_ALIGNED(Bytes)        __attribute__ ((aligned(Bytes)))
  #define TU_ATTR_SECTION(sec_name)     __attribute__ ((section(#sec_name)))
  #define TU_ATTR_PACKED                __attribute__ ((packed))
  #define TU_ATTR_WEAK                  __attribute__ ((weak))
  #define TU_ATTR_ALWAYS_INLINE         __attribute__ ((always_inline))
  #define TU_ATTR_DEPRECATED(mess)      __attribute__ ((deprecated(mess))) // 如果使用具有此属性的函数，则发出警告
  #define TU_ATTR_UNUSED                __attribute__ ((unused))           // 函数/变量可能未使用
  #define TU_ATTR_USED                  __attribute__ ((used))

  // __BYTE_ORDER是在TI ARM编译器中定义的，但不是MSP430（小端）
  #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__)) || defined(__MSP430__)
    #define TU_BYTE_ORDER TU_LITTLE_ENDIAN
  #else
    #define TU_BYTE_ORDER TU_BIG_ENDIAN
  #endif

  #define TU_BSWAP16(u16) (__builtin_bswap16(u16))
  #define TU_BSWAP32(u32) (__builtin_bswap32(u32))

#elif defined(__ICCARM__)
  #include <intrinsics.h>
  #define TU_ATTR_ALIGNED(Bytes)        __attribute__ ((aligned(Bytes)))
  #define TU_ATTR_SECTION(sec_name)     __attribute__ ((section(#sec_name)))
  #define TU_ATTR_PACKED                __attribute__ ((packed))
  #define TU_ATTR_WEAK                  __attribute__ ((weak))
  #define TU_ATTR_ALWAYS_INLINE         __attribute__ ((always_inline))
  #define TU_ATTR_DEPRECATED(mess)      __attribute__ ((deprecated(mess))) // 如果使用具有此属性的函数，则发出警告
  #define TU_ATTR_UNUSED                __attribute__ ((unused))           // 函数/变量可能未使用
  #define TU_ATTR_USED                  __attribute__ ((used))             // 要使用函数/变量

  // Endian转换使用众所周知的主机到网络（big Endian）命名
  #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define TU_BYTE_ORDER TU_LITTLE_ENDIAN
  #else
    #define TU_BYTE_ORDER TU_BIG_ENDIAN
  #endif

  #define TU_BSWAP16(u16) (__iar_builtin_REV16(u16))
  #define TU_BSWAP32(u32) (__iar_builtin_REV(u32))
#else 
  #error "Compiler attribute porting is required"
#endif

#if (TU_BYTE_ORDER == TU_LITTLE_ENDIAN)

  #define tu_htons(u16)  (TU_BSWAP16(u16))
  #define tu_ntohs(u16)  (TU_BSWAP16(u16))

  #define tu_htonl(u32)  (TU_BSWAP32(u32))
  #define tu_ntohl(u32)  (TU_BSWAP32(u32))

  #define tu_htole16(u16) (u16)
  #define tu_le16toh(u16) (u16)

  #define tu_htole32(u32) (u32)
  #define tu_le32toh(u32) (u32)

#elif (TU_BYTE_ORDER == TU_BIG_ENDIAN)

  #define tu_htons(u16)  (u16)
  #define tu_ntohs(u16)  (u16)

  #define tu_htonl(u32)  (u32)
  #define tu_ntohl(u32)  (u32)

  #define tu_htole16(u16) (tu_bswap16(u16))
  #define tu_le16toh(u16) (tu_bswap16(u16))

  #define tu_htole32(u32) (tu_bswap32(u32))
  #define tu_le32toh(u32) (tu_bswap32(u32))

#else
  #error Byte order is undefined
#endif

#endif /* _TUSB_COMPILER_H_ */

/// @}

