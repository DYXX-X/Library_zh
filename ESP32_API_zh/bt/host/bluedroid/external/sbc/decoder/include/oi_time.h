/******************************************************************************
 * 版权所有（C）2014 Android开源项目版权所有2002-2004 Open Interface North America，Inc.保留所有权利。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/
#ifndef _OI_TIME_H
#define _OI_TIME_H
/** @file
 *
 * 此文件提供时间类型定义和时间相关函数的接口。
 *
 * 堆栈保持64位实时毫秒时钟。选择毫秒是为了方便，而不是精确。
 *
 * 超时指定为32位值的十分之一秒。蓝牙规范规定的超时值通常是几秒，因此精确到十分之一秒就足够了。
 *
 * 该文件还包含在秒和链接管理器的1.28秒单位之间转换的宏。
 *
 */

/**********************************************************************************
  $版本：#1$
***********************************************************************************/

#include "oi_stddefs.h"


/**\addtogroup其他杂项API*/
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif



/**
 * 在核心堆栈中，超时以十分之一秒的间隔指定
 */

typedef OI_UINT16 OI_INTERVAL;
#define OI_INTERVALS_PER_SECOND     10
#define MSECS_PER_OI_INTERVAL       (1000 / OI_INTERVALS_PER_SECOND)

/**最大间隔（54分36.7秒）*/
#define OI_MAX_INTERVAL   0x7fff


/**
 * 将秒转换为OI_INTERVAL时间单位的宏
 */

#define OI_SECONDS(n)    ((OI_INTERVAL) ((n) * OI_INTERVALS_PER_SECOND))

/**
 * 将毫秒转换为OI_INTERVAL时间单位的宏（向上舍入）
 */

#define OI_MSECONDS(n)   ((OI_INTERVAL) ((n + MSECS_PER_OI_INTERVAL - 1) / MSECS_PER_OI_INTERVAL))

/**
 * 将分钟转换为OI_INTERVAL时间单位的宏
 */

#define OI_MINUTES(n)    ((OI_INTERVAL) ((n) * OI_SECONDS(60)))

/**将OI_INTERVAL转换为毫秒。*/
#define OI_INTERVAL_TO_MILLISECONDS(i) ((i) * MSECS_PER_OI_INTERVAL)

/**
 * 堆栈取决于相对时间而不是绝对时间。堆栈的实时时钟与绝对时间和日期之间的任何映射都取决于实现。
 */

typedef struct {
    OI_INT32 seconds;
    OI_INT16 mseconds;
} OI_TIME;

/**
 * 将OI_TIME转换为毫秒。
 *
 * @param t  转换的时间
 *
 * @return 以毫秒为单位的时间
 */
OI_UINT32 OI_Time_ToMS(OI_TIME *t);


/**
 * 此函数用于比较两个时间值。
 *
 * @param T1 第一次比较。
 *
 * @param T2 第二次比较。
 *
 * @return
 @逐字逐句的
     -1如果t1＜t2 0如果t1＝t2+1如果t1＞t2
 @逐字结尾
 */

OI_INT16 OI_Time_Compare(OI_TIME *T1,
                         OI_TIME *T2);


/**
 * 此函数将两次之间的间隔返回到0.1秒的粒度。
 *
 * @param Sooner 时间值比Later更近
 *
 * @param Later 晚于Sooner的时间值
 *
 * @note 结果是OI_INTERVAL值，因此此函数仅适用于小于约71分钟的时间间隔。
 *
 * @return 两次之间的时间间隔=（晚一点-早一点）
 */

OI_INTERVAL OI_Time_Interval(OI_TIME *Sooner,
                             OI_TIME *Later);



/**
 * 此函数将两次之间的间隔返回到毫秒的粒度。
 *
 * @param Sooner 时间值比Later更近
 *
 * @param Later 晚于Sooner的时间值
 *
 * @note 结果是OI_UINT32值，因此此函数仅适用于小于约50天的时间间隔。
 *
 * @return 两次之间的时间间隔=（晚一点-早一点）
 */

OI_UINT32 OI_Time_IntervalMsecs(OI_TIME *Sooner,
                                OI_TIME *Later);



/**
 * 这个函数回答了一个问题：我们是否达到或超过了目标时间？
 *
 * @param pTargetTime   目标时间
 *
 * @return  TRUE表示当前时间处于或超过目标时间FALSE表示目标时间仍在未来某个时间
 */

OI_BOOL  OI_Time_NowReachedTime(OI_TIME *pTargetTime);

/**
 *  使用1.25转换系数将秒转换为链接管理器1.28秒单位近似值。
 */

#define OI_SECONDS_TO_LM_TIME_UNITS(lmUnits) ((lmUnits)<4?(lmUnits):(lmUnits)-((lmUnits)>>2))


/**
 *  将链接管理器1.28秒单位转换为秒。使用1.25换算系数进行近似。
 */

#define OI_LM_TIME_UNITS_TO_SECONDS(lmUnits) ((lmUnits) + ((lmUnits)>>2))

#ifdef __cplusplus
}
#endif

/**@}*/

/* OI_Time_Now（）原型的Include必须包含在末尾才能获得OI_Time typedef
 */
#include "oi_osinterface.h"

/*****************************************************************************/
#endif /* _OI_TIME_H */

