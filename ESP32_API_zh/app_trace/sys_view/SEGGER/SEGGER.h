/*********************************************************************
*                SEGGER微控制器GmbH&Co.KG*嵌入式专家
**********************************************************************
*                                                                    *（c）2015-2017 SEGGER微控制器股份有限公司
*                                                                    *
*       网址：www.segger。com支持：support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER SystemView*实时应用程序分析*
*                                                                    *
**********************************************************************
*                                                                    *
* 保留所有权利*
*                                                                    *
* SEGGER强烈建议不要对本软件的源代码进行任何更改*或修改，以便与RTT协议和J-Link保持兼容。
*                                                                    *
* 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否经过修改：
*                                                                    *
* o源代码的重新分发必须保留上述版权*声明、本条件列表和以下免责声明。
*                                                                    *
* o二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述*版权声明、本条件列表和以下免责声明。
*                                                                    *
* o未经事先书面许可，不得使用SEGGER Microcontroller GmbH&Co.KG*的名称或其贡献者的名称来支持或推广源自本软件的产品。
*                                                                    *
* 本软件由版权持有人和贡献者“按原样”提供，不承担任何明示或暗示的保证，包括但不限于适销性和特定用途适用性的暗示保证。在任何情况下，SEGGER微控制器对任何直接、间接、附带、特殊、惩戒性或后果性损害（包括但不限于购买替代商品或服务；使用、数据或利润损失；或业务中断）均不承担责任，无论是由何原因引起的，也不以任何责任理论为依据，或因使用本软件而以任何方式产生的侵权行为（包括疏忽或其他），即使已告知此类损害的可能性。
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView版本：V2.42*
*                                                                    *
**********************************************************************
----------------------------------------------------------------------文件：SEGGER。h用途：全局类型等和通用实用功能
---------------------------END-OF-HEADER------------------------------
*/

#ifndef SEGGER_H            // 防止多重包含
#define SEGGER_H

#include "Global.h"         // 类型定义：U8、U16、U32、I8、I16、I32

#if defined(__cplusplus)
extern "C" {     /* 确保我们在C++程序中有C声明*/
#endif

/*********************************************************************
* 关键字/说明符
*
**********************************************************************
*/

#ifndef INLINE
  #ifdef _WIN32
    //
    // Microsoft VC6和更新版本。
    // 强制内联而不进行成本检查。
    //
    #define INLINE  __forceinline
  #else
    #if (defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__) || defined(__RX) || defined(__ICCRX__))
      //
      // 其他已知编译器。
      //
      #define INLINE  inline
    #else
      //
      // 未知编译器。
      //
      #define INLINE
    #endif
  #endif
#endif

/*********************************************************************
* 函数式宏
*
**********************************************************************
*/

#define SEGGER_COUNTOF(a)          (sizeof((a))/sizeof((a)[0]))
#define SEGGER_MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define SEGGER_MAX(a,b)            (((a) > (b)) ? (a) : (b))

/*********************************************************************
* 类型
*
**********************************************************************
*/

typedef struct {
  char *pBuffer;
  int   BufferSize;
  int   Cnt;
} SEGGER_BUFFER_DESC;

typedef struct {
  int  CacheLineSize;                                // 0：无缓存。大多数系统（如ARM9）使用32字节缓存行大小。
  void (*pfDMB)       (void);                        // 数据内存屏障的可选DMB功能，确保所有内存操作均已完成。
  void (*pfClean)     (void *p, unsigned NumBytes);  // 缓存内存的可选清理函数。
  void (*pfInvalidate)(void *p, unsigned NumBytes);  // 缓存内存的可选无效函数。
} SEGGER_CACHE_CONFIG;

/*********************************************************************
* 实用程序功能
*
**********************************************************************
*/

void SEGGER_ARM_memcpy   (void *pDest, const void *pSrc, int NumBytes);
void SEGGER_memcpy       (void *pDest, const void *pSrc, int NumBytes);
void SEGGER_memxor       (void *pDest, const void *pSrc, unsigned NumBytes);
void SEGGER_StoreChar    (SEGGER_BUFFER_DESC *p, char c);
void SEGGER_PrintUnsigned(SEGGER_BUFFER_DESC *pBufferDesc, U32 v, unsigned Base, int NumDigits);
void SEGGER_PrintInt     (SEGGER_BUFFER_DESC *pBufferDesc, I32 v, unsigned Base, unsigned NumDigits);
int  SEGGER_snprintf     (char *pBuffer, int BufferSize, const char *sFormat, ...);


#if defined(__cplusplus)
}                /* 确保我们在C++程序中有C声明*/
#endif

#endif                      // 避免多次包含

/***************************文件结尾****************************/

