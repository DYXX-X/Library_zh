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
-------------------------- END-OF-HEADER -----------------------------

文件：SEGGER_SYSVIEW_FreeRTOS。h目的：FreeRTOS和SystemView之间的接口。版本：$Rev:3734$

注意：（1）在FreeRTOSConfig.h末尾包含此文件
*/

#ifndef SYSVIEW_FREERTOS_H
#define SYSVIEW_FREERTOS_H

#include "SEGGER_SYSVIEW.h"

/*********************************************************************
* 定义，可配置
*
**********************************************************************
*/

#define SYSVIEW_FREERTOS_MAX_NOF_TASKS  CONFIG_APPTRACE_SV_MAX_TASKS

/*********************************************************************
* 定义，固定
*
**********************************************************************
*/

// 对于双核目标，我们使用事件ID来保持核心ID位（0或1）
// 使用事件ID的最高-1位表示核心ID
// 由于事件ID编码方法，无法使用最高位
// 这将支持的ID范围减少到[0..63]（对于1字节ID）加上[128..16383]（对于2字节ID）
// 因此，原始连续事件ID范围分为两个子范围，分别为1字节ID和2字节ID

// 使用apiFastID_ OFFSET的事件将具有1字节ID，
// 因此，为了节省带宽，更频繁地生成的事件应该使用该ID偏移
// 当前所有使用的事件都属于此范围
#define apiFastID_OFFSET                          (32u)

#define apiID_VTASKDELETE                         (1u)
#define apiID_VTASKDELAY                          (2u)
#define apiID_VTASKDELAYUNTIL                     (3u)
#define apiID_VTASKSUSPEND                        (4u)
#define apiID_ULTASKNOTIFYTAKE                    (5u)
#define apiID_VTASKNOTIFYGIVEFROMISR              (6u)
#define apiID_VTASKPRIORITYINHERIT                (7u)
#define apiID_VTASKRESUME                         (8u)
#define apiID_VTASKSTEPTICK                       (9u)
#define apiID_XTASKPRIORITYDISINHERIT             (10u)
#define apiID_XTASKRESUMEFROMISR                  (11u)
#define apiID_XTASKGENERICNOTIFY                  (12u)
#define apiID_XTASKGENERICNOTIFYFROMISR           (13u)
#define apiID_XTASKNOTIFYWAIT                     (14u)
#define apiID_XQUEUEGENERICCREATE                 (15u)
#define apiID_VQUEUEDELETE                        (16u)
#define apiID_XQUEUEGENERICRECEIVE                (17u)
#define apiID_XQUEUEPEEKFROMISR                   (18u)
#define apiID_XQUEUERECEIVEFROMISR                (19u)
#define apiID_VQUEUEADDTOREGISTRY                 (20u)
#define apiID_XQUEUEGENERICSEND                   (21u)
#define apiID_XQUEUEGENERICSENDFROMISR            (22u)
#define apiID_VTASKPRIORITYSET                    (23u)
#define apiID_UXTASKPRIORITYGETFROMISR            (24u)
#define apiID_XTASKGETTICKCOUNTFROMISR            (25u)
#define apiID_XEVENTGROUPCLEARBITSFROMISR         (26u)
#define apiID_XEVENTGROUPSETBITSFROMISR           (27u)
#define apiID_XEVENTGROUPGETBITSFROMISR           (28u)
#define apiID_XQUEUEGIVEFROMISR                   (29u)
#define apiID_XQUEUEISQUEUEEMPTYFROMISR           (30u)
#define apiID_XQUEUEISQUEUEFULLFROMISR            (31u) // 第一个ID范围允许的最大apiID

// 使用apiSlowID_OFFSET的事件将具有2字节ID
#define apiSlowID_OFFSET                          (127u)

#define apiID_VTASKALLOCATEMPUREGIONS             (1u)
#define apiID_UXTASKPRIORITYGET                   (2u)
#define apiID_ETASKGETSTATE                       (3u)
#define apiID_VTASKSTARTSCHEDULER                 (4u)
#define apiID_VTASKENDSCHEDULER                   (5u)
#define apiID_VTASKSUSPENDALL                     (6u)
#define apiID_XTASKRESUMEALL                      (7u)
#define apiID_XTASKGETTICKCOUNT                   (8u)
#define apiID_UXTASKGETNUMBEROFTASKS              (9u)
#define apiID_PCTASKGETTASKNAME                   (10u)
#define apiID_UXTASKGETSTACKHIGHWATERMARK         (11u)
#define apiID_VTASKSETAPPLICATIONTASKTAG          (12u)
#define apiID_XTASKGETAPPLICATIONTASKTAG          (13u)
#define apiID_VTASKSETTHREADLOCALSTORAGEPOINTER   (14u)
#define apiID_PVTASKGETTHREADLOCALSTORAGEPOINTER  (15u)
#define apiID_XTASKCALLAPPLICATIONTASKHOOK        (16u)
#define apiID_XTASKGETIDLETASKHANDLE              (17u)
#define apiID_UXTASKGETSYSTEMSTATE                (18u)
#define apiID_VTASKLIST                           (19u)
#define apiID_VTASKGETRUNTIMESTATS                (20u)
#define apiID_XTASKNOTIFYSTATECLEAR               (21u)
#define apiID_XTASKGETCURRENTTASKHANDLE           (22u)
#define apiID_VTASKSETTIMEOUTSTATE                (23u)
#define apiID_XTASKCHECKFORTIMEOUT                (24u)
#define apiID_VTASKMISSEDYIELD                    (25u)
#define apiID_XTASKGETSCHEDULERSTATE              (26u)
#define apiID_XTASKGENERICCREATE                  (27u)
#define apiID_UXTASKGETTASKNUMBER                 (28u)
#define apiID_VTASKSETTASKNUMBER                  (29u)
#define apiID_ETASKCONFIRMSLEEPMODESTATUS         (30u)
#define apiID_XTIMERCREATE                        (31u)
#define apiID_PVTIMERGETTIMERID                   (32u)
#define apiID_VTIMERSETTIMERID                    (33u)
#define apiID_XTIMERISTIMERACTIVE                 (34u)
#define apiID_XTIMERGETTIMERDAEMONTASKHANDLE      (35u)
#define apiID_XTIMERPENDFUNCTIONCALLFROMISR       (36u)
#define apiID_XTIMERPENDFUNCTIONCALL              (37u)
#define apiID_PCTIMERGETTIMERNAME                 (38u)
#define apiID_XTIMERCREATETIMERTASK               (39u)
#define apiID_XTIMERGENERICCOMMAND                (40u)
#define apiID_UXQUEUEMESSAGESWAITING              (41u)
#define apiID_UXQUEUESPACESAVAILABLE              (42u)
#define apiID_UXQUEUEMESSAGESWAITINGFROMISR       (43u)
#define apiID_XQUEUEALTGENERICSEND                (44u)
#define apiID_XQUEUEALTGENERICRECEIVE             (45u)
#define apiID_XQUEUECRSENDFROMISR                 (46u)
#define apiID_XQUEUECRRECEIVEFROMISR              (47u)
#define apiID_XQUEUECRSEND                        (48u)
#define apiID_XQUEUECRRECEIVE                     (49u)
#define apiID_XQUEUECREATEMUTEX                   (50u)
#define apiID_XQUEUECREATECOUNTINGSEMAPHORE       (51u)
#define apiID_XQUEUEGETMUTEXHOLDER                (52u)
#define apiID_XQUEUETAKEMUTEXRECURSIVE            (53u)
#define apiID_XQUEUEGIVEMUTEXRECURSIVE            (54u)
#define apiID_VQUEUEUNREGISTERQUEUE               (55u)
#define apiID_XQUEUECREATESET                     (56u)
#define apiID_XQUEUEADDTOSET                      (57u)
#define apiID_XQUEUEREMOVEFROMSET                 (58u)
#define apiID_XQUEUESELECTFROMSET                 (59u)
#define apiID_XQUEUESELECTFROMSETFROMISR          (60u)
#define apiID_XQUEUEGENERICRESET                  (61u)
#define apiID_VLISTINITIALISE                     (62u)
#define apiID_VLISTINITIALISEITEM                 (63u)
#define apiID_VLISTINSERT                         (64u)
#define apiID_VLISTINSERTEND                      (65u)
#define apiID_UXLISTREMOVE                        (66u)
#define apiID_XEVENTGROUPCREATE                   (67u)
#define apiID_XEVENTGROUPWAITBITS                 (68u)
#define apiID_XEVENTGROUPCLEARBITS                (69u)
#define apiID_XEVENTGROUPSETBITS                  (70u)
#define apiID_XEVENTGROUPSYNC                     (71u)
#define apiID_VEVENTGROUPDELETE                   (72u)
#define apiID_UXEVENTGROUPGETNUMBER               (73u)

#define traceTASK_NOTIFY_TAKE( uxIndexToWait )                        SEGGER_SYSVIEW_RecordU32x2(apiFastID_OFFSET + apiID_ULTASKNOTIFYTAKE, xClearCountOnExit, xTicksToWait)
#define traceTASK_DELAY()                                             SEGGER_SYSVIEW_RecordU32(apiFastID_OFFSET + apiID_VTASKDELAY, xTicksToDelay)
#define traceTASK_DELAY_UNTIL()                                       SEGGER_SYSVIEW_RecordVoid(apiFastID_OFFSET + apiID_VTASKDELAYUNTIL)
#define traceTASK_DELETE( pxTCB )                                     if (pxTCB != NULL) {                                              \
						                                                SEGGER_SYSVIEW_RecordU32(apiFastID_OFFSET + apiID_VTASKDELETE,  \
						                                                                      SEGGER_SYSVIEW_ShrinkId((U32)pxTCB)); 	\
					                                                    SYSVIEW_DeleteTask((U32)pxTCB);                                 \
					                                                  }
#define traceTASK_NOTIFY_GIVE_FROM_ISR( uxIndexToNotify )             SEGGER_SYSVIEW_RecordU32x2(apiFastID_OFFSET + apiID_VTASKNOTIFYGIVEFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB), (U32)pxHigherPriorityTaskWoken)
#define traceTASK_PRIORITY_INHERIT( pxTCB, uxPriority )               SEGGER_SYSVIEW_RecordU32(apiFastID_OFFSET + apiID_VTASKPRIORITYINHERIT, (U32)pxMutexHolder)
#define traceTASK_RESUME( pxTCB )                                     SEGGER_SYSVIEW_RecordU32(apiFastID_OFFSET + apiID_VTASKRESUME, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB))
#define traceINCREASE_TICK_COUNT( xTicksToJump )                      SEGGER_SYSVIEW_RecordU32(apiFastID_OFFSET + apiID_VTASKSTEPTICK, xTicksToJump)
#define traceTASK_SUSPEND( pxTCB )                                    SEGGER_SYSVIEW_RecordU32(apiFastID_OFFSET + apiID_VTASKSUSPEND, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB))
#define traceTASK_PRIORITY_DISINHERIT( pxTCB, uxBasePriority )        SEGGER_SYSVIEW_RecordU32(apiFastID_OFFSET + apiID_XTASKPRIORITYDISINHERIT, (U32)pxMutexHolder)
#define traceTASK_RESUME_FROM_ISR( pxTCB )                            SEGGER_SYSVIEW_RecordU32(apiFastID_OFFSET + apiID_XTASKRESUMEFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB))
#define traceTASK_NOTIFY( uxIndexToNotify )                           SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XTASKGENERICNOTIFY, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB), ulValue, eAction, (U32)pulPreviousNotificationValue)
#define traceTASK_NOTIFY_FROM_ISR( uxIndexToNotify )                  SYSVIEW_RecordU32x5(apiFastID_OFFSET + apiID_XTASKGENERICNOTIFYFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB), ulValue, eAction, (U32)pulPreviousNotificationValue, (U32)pxHigherPriorityTaskWoken)
#define traceTASK_NOTIFY_WAIT( uxIndexToWait )                        SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XTASKNOTIFYWAIT, ulBitsToClearOnEntry, ulBitsToClearOnExit, (U32)pulNotificationValue, xTicksToWait)

#define traceQUEUE_CREATE( pxNewQueue )                               SEGGER_SYSVIEW_RecordU32x3(apiFastID_OFFSET + apiID_XQUEUEGENERICCREATE, uxQueueLength, uxItemSize, ucQueueType)
#define traceQUEUE_DELETE( pxQueue )                                  SEGGER_SYSVIEW_RecordU32(apiFastID_OFFSET + apiID_VQUEUEDELETE, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue))
#define traceQUEUE_PEEK( pxQueue )                                    SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XQUEUEGENERICRECEIVE, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)pvBuffer), xTicksToWait, 0)
#define traceQUEUE_PEEK_FROM_ISR( pxQueue )                           SEGGER_SYSVIEW_RecordU32x2(apiFastID_OFFSET + apiID_XQUEUEPEEKFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)pvBuffer))
#define traceQUEUE_PEEK_FROM_ISR_FAILED( pxQueue )                    SEGGER_SYSVIEW_RecordU32x2(apiFastID_OFFSET + apiID_XQUEUEPEEKFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)pvBuffer))
#define traceQUEUE_RECEIVE( pxQueue )                                 SEGGER_SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XQUEUEGENERICRECEIVE, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)0), xTicksToWait, 1)
#define traceQUEUE_RECEIVE_FAILED( pxQueue )                          SEGGER_SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XQUEUEGENERICRECEIVE, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)0), xTicksToWait, 1)
#define traceQUEUE_SEMAPHORE_RECEIVE( pxQueue )                       SEGGER_SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XQUEUEGENERICRECEIVE, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)0), xTicksToWait, 0)
#define traceQUEUE_RECEIVE_FROM_ISR( pxQueue )                        SEGGER_SYSVIEW_RecordU32x3(apiFastID_OFFSET + apiID_XQUEUERECEIVEFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)pvBuffer), (U32)pxHigherPriorityTaskWoken)
#define traceQUEUE_RECEIVE_FROM_ISR_FAILED( pxQueue )                 SEGGER_SYSVIEW_RecordU32x3(apiFastID_OFFSET + apiID_XQUEUERECEIVEFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)pvBuffer), (U32)pxHigherPriorityTaskWoken)
#define traceQUEUE_REGISTRY_ADD( xQueue, pcQueueName )                SEGGER_SYSVIEW_RecordU32x2(apiFastID_OFFSET + apiID_VQUEUEADDTOREGISTRY, SEGGER_SYSVIEW_ShrinkId((U32)xQueue), (U32)pcQueueName)
#if ( configUSE_QUEUE_SETS != 1 )
  #define traceQUEUE_SEND( pxQueue )                                    SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XQUEUEGENERICSEND, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), (U32)pvItemToQueue, xTicksToWait, xCopyPosition)
#else
  #define traceQUEUE_SEND( pxQueue )                                    SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XQUEUEGENERICSEND, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), 0, 0, xCopyPosition)
#endif
#define traceQUEUE_SEND_FAILED( pxQueue )                             SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XQUEUEGENERICSEND, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), (U32)pvItemToQueue, xTicksToWait, xCopyPosition)
#define traceQUEUE_SEND_FROM_ISR( pxQueue )                           SEGGER_SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XQUEUEGENERICSENDFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), (U32)pvItemToQueue, (U32)pxHigherPriorityTaskWoken, xCopyPosition)
#define traceQUEUE_SEND_FROM_ISR_FAILED( pxQueue )                    SEGGER_SYSVIEW_RecordU32x4(apiFastID_OFFSET + apiID_XQUEUEGENERICSENDFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), (U32)pvItemToQueue, (U32)pxHigherPriorityTaskWoken, xCopyPosition)
#define traceQUEUE_GIVE_FROM_ISR( pxQueue )                           SEGGER_SYSVIEW_RecordU32x2(apiFastID_OFFSET + apiID_XQUEUEGIVEFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), (U32)pxHigherPriorityTaskWoken)
#define traceQUEUE_GIVE_FROM_ISR_FAILED( pxQueue )                    SEGGER_SYSVIEW_RecordU32x2(apiFastID_OFFSET + apiID_XQUEUEGIVEFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), (U32)pxHigherPriorityTaskWoken)

#if( portSTACK_GROWTH < 0 )
#define traceTASK_CREATE(pxNewTCB)                  if (pxNewTCB != NULL) {                                             \
                                                      SEGGER_SYSVIEW_OnTaskCreate((U32)pxNewTCB);                       \
                                                      SYSVIEW_AddTask((U32)pxNewTCB,                                    \
                                                                      &(pxNewTCB->pcTaskName[0]),                       \
                                                                      pxNewTCB->uxPriority,                             \
                                                                      (U32)pxNewTCB->pxStack,                           \
                                                                      ((U32)pxNewTCB->pxTopOfStack - (U32)pxNewTCB->pxStack) \
                                                                      );                                                \
                                                    }
#else
#define traceTASK_CREATE(pxNewTCB)                  if (pxNewTCB != NULL) {                                             \
                                                      SEGGER_SYSVIEW_OnTaskCreate((U32)pxNewTCB);                       \
                                                      SYSVIEW_AddTask((U32)pxNewTCB,                                    \
                                                                      &(pxNewTCB->pcTaskName[0]),                       \
                                                                      pxNewTCB->uxPriority,                             \
                                                                      (U32)pxNewTCB->pxStack,                           \
                                                                      (U32)(pxNewTCB->pxStack-pxNewTCB->pxTopOfStack)   \
                                                                      );                                                \
                                                    }
#endif
#define traceTASK_PRIORITY_SET(pxTask, uxNewPriority) {                                                                 \
                                                        SEGGER_SYSVIEW_RecordU32x2(apiFastID_OFFSET+apiID_VTASKPRIORITYSET, \
                                                                                   SEGGER_SYSVIEW_ShrinkId((U32)pxTCB), \
                                                                                   uxNewPriority                        \
                                                                                  );                                    \
                                                        SYSVIEW_UpdateTask((U32)pxTask,                                 \
                                                                           &(pxTask->pcTaskName[0]),                    \
                                                                           uxNewPriority,                               \
                                                                           (U32)pxTask->pxStack,                        \
                                                                           0                                            \
                                                                          );                                            \
                                                      }
//
// 在FreeRTOSConfig中将INCLUDE_xTaskGetIdleTaskHandle定义为1。h以允许识别空闲状态。
//
#if ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
  #define traceTASK_SWITCHED_IN()                   if(prvGetTCBFromHandle(NULL) == xTaskGetIdleTaskHandle()) {           \
                                                      SEGGER_SYSVIEW_OnIdle();                                          \
                                                    } else {                                                            \
                                                      SEGGER_SYSVIEW_OnTaskStartExec((U32)pxCurrentTCB[cpu_hal_get_core_id()]); \
                                                    }
#else
  #define traceTASK_SWITCHED_IN()                   {                                                                   \
                                                      if (memcmp(pxCurrentTCB[cpu_hal_get_core_id()]->pcTaskName, "IDLE", 5) != 0) { \
                                                        SEGGER_SYSVIEW_OnTaskStartExec((U32)pxCurrentTCB[cpu_hal_get_core_id()]);    \
                                                      } else {                                                          \
                                                        SEGGER_SYSVIEW_OnIdle();                                        \
                                                      }                                                                 \
                                                    }
#endif

#define traceMOVED_TASK_TO_READY_STATE(pxTCB)       SEGGER_SYSVIEW_OnTaskStartReady((U32)pxTCB)
#define traceREADDED_TASK_TO_READY_STATE(pxTCB)

#define traceMOVED_TASK_TO_DELAYED_LIST()           SEGGER_SYSVIEW_OnTaskStopReady((U32)pxCurrentTCB[cpu_hal_get_core_id()],  (1u << 2))
#define traceMOVED_TASK_TO_OVERFLOW_DELAYED_LIST()  SEGGER_SYSVIEW_OnTaskStopReady((U32)pxCurrentTCB[cpu_hal_get_core_id()],  (1u << 2))
#define traceMOVED_TASK_TO_SUSPENDED_LIST(pxTCB)    SEGGER_SYSVIEW_OnTaskStopReady((U32)pxTCB,         ((3u << 3) | 3))

#define traceISR_EXIT_TO_SCHEDULER()                SEGGER_SYSVIEW_RecordExitISRToScheduler()
#define traceISR_EXIT()                             SEGGER_SYSVIEW_RecordExitISR()
#define traceISR_ENTER(_n_)                         SEGGER_SYSVIEW_RecordEnterISR(_n_)


/*********************************************************************
* API函数
*
**********************************************************************
*/
#ifdef __cplusplus
extern "C" {
#endif
void SYSVIEW_AddTask      (U32 xHandle, const char* pcTaskName, unsigned uxCurrentPriority, U32  pxStack, unsigned uStackHighWaterMark);
void SYSVIEW_UpdateTask   (U32 xHandle, const char* pcTaskName, unsigned uxCurrentPriority, U32 pxStack, unsigned uStackHighWaterMark);
void SYSVIEW_DeleteTask   (U32 xHandle);
void SYSVIEW_SendTaskInfo (U32 TaskID, const char* sName, unsigned Prio, U32 StackBase, unsigned StackSize);
void SYSVIEW_RecordU32x4  (unsigned Id, U32 Para0, U32 Para1, U32 Para2, U32 Para3);
void SYSVIEW_RecordU32x5  (unsigned Id, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4);

#ifdef __cplusplus
}
#endif

#endif

/***************************文件结尾****************************/

