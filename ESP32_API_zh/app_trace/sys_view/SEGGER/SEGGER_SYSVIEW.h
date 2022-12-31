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
--------------------------标题结束--------------------------文件：SEGGER_SYSVIEW。h目的：系统可视化API。版本：$Rev:5626$
*/

#ifndef SEGGER_SYSVIEW_H
#define SEGGER_SYSVIEW_H

/*********************************************************************
* #包含部分
*
**********************************************************************
*/

#include "SEGGER.h"

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************
* 定义，固定
*
**********************************************************************
*/

#define SEGGER_SYSVIEW_VERSION        21000

#define SEGGER_SYSVIEW_INFO_SIZE      9   // 必须为数据包保留的最小大小。消息类型为1-2字节，有效载荷长度为0-2字节，时间戳为1-5字节。
#define SEGGER_SYSVIEW_QUANTA_U32     5   // 应为数据包中的每个32位值保留编码U32的最大字节数。

#define SEGGER_SYSVIEW_LOG            (0u)
#define SEGGER_SYSVIEW_WARNING        (1u)
#define SEGGER_SYSVIEW_ERROR          (2u)
#define SEGGER_SYSVIEW_FLAG_APPEND    (1u << 6)

#define SEGGER_SYSVIEW_PREPARE_PACKET(p)  (p) + 4
//
// SystemView事件。从0..31开始的前32个ID保留给这些
//
#define   SYSVIEW_EVTID_NOP                0  // 虚拟数据包。
#define   SYSVIEW_EVTID_OVERFLOW           1
#define   SYSVIEW_EVTID_ISR_ENTER          2
#define   SYSVIEW_EVTID_ISR_EXIT           3
#define   SYSVIEW_EVTID_TASK_START_EXEC    4
#define   SYSVIEW_EVTID_TASK_STOP_EXEC     5
#define   SYSVIEW_EVTID_TASK_START_READY   6
#define   SYSVIEW_EVTID_TASK_STOP_READY    7
#define   SYSVIEW_EVTID_TASK_CREATE        8
#define   SYSVIEW_EVTID_TASK_INFO          9
#define   SYSVIEW_EVTID_TRACE_START       10
#define   SYSVIEW_EVTID_TRACE_STOP        11
#define   SYSVIEW_EVTID_SYSTIME_CYCLES    12
#define   SYSVIEW_EVTID_SYSTIME_US        13
#define   SYSVIEW_EVTID_SYSDESC           14
#define   SYSVIEW_EVTID_USER_START        15
#define   SYSVIEW_EVTID_USER_STOP         16
#define   SYSVIEW_EVTID_IDLE              17
#define   SYSVIEW_EVTID_ISR_TO_SCHEDULER  18
#define   SYSVIEW_EVTID_TIMER_ENTER       19
#define   SYSVIEW_EVTID_TIMER_EXIT        20
#define   SYSVIEW_EVTID_STACK_INFO        21
#define   SYSVIEW_EVTID_MODULEDESC        22

#define   SYSVIEW_EVTID_INIT              24
#define   SYSVIEW_EVTID_NAME_RESOURCE     25
#define   SYSVIEW_EVTID_PRINT_FORMATTED   26
#define   SYSVIEW_EVTID_NUMMODULES        27
#define   SYSVIEW_EVTID_END_CALL          28
#define   SYSVIEW_EVTID_TASK_TERMINATE    29

#define   SYSVIEW_EVTID_EX                31
//
// 禁用/启用事件的事件掩码
//
#define   SYSVIEW_EVTMASK_NOP               (1 << SYSVIEW_EVTID_NOP)
#define   SYSVIEW_EVTMASK_OVERFLOW          (1 << SYSVIEW_EVTID_OVERFLOW)
#define   SYSVIEW_EVTMASK_ISR_ENTER         (1 << SYSVIEW_EVTID_ISR_ENTER)
#define   SYSVIEW_EVTMASK_ISR_EXIT          (1 << SYSVIEW_EVTID_ISR_EXIT)
#define   SYSVIEW_EVTMASK_TASK_START_EXEC   (1 << SYSVIEW_EVTID_TASK_START_EXEC)
#define   SYSVIEW_EVTMASK_TASK_STOP_EXEC    (1 << SYSVIEW_EVTID_TASK_STOP_EXEC)
#define   SYSVIEW_EVTMASK_TASK_START_READY  (1 << SYSVIEW_EVTID_TASK_START_READY)
#define   SYSVIEW_EVTMASK_TASK_STOP_READY   (1 << SYSVIEW_EVTID_TASK_STOP_READY)
#define   SYSVIEW_EVTMASK_TASK_CREATE       (1 << SYSVIEW_EVTID_TASK_CREATE)
#define   SYSVIEW_EVTMASK_TASK_INFO         (1 << SYSVIEW_EVTID_TASK_INFO)
#define   SYSVIEW_EVTMASK_TRACE_START       (1 << SYSVIEW_EVTID_TRACE_START)
#define   SYSVIEW_EVTMASK_TRACE_STOP        (1 << SYSVIEW_EVTID_TRACE_STOP)
#define   SYSVIEW_EVTMASK_SYSTIME_CYCLES    (1 << SYSVIEW_EVTID_SYSTIME_CYCLES)
#define   SYSVIEW_EVTMASK_SYSTIME_US        (1 << SYSVIEW_EVTID_SYSTIME_US)
#define   SYSVIEW_EVTMASK_SYSDESC           (1 << SYSVIEW_EVTID_SYSDESC)
#define   SYSVIEW_EVTMASK_USER_START        (1 << SYSVIEW_EVTID_USER_START)
#define   SYSVIEW_EVTMASK_USER_STOP         (1 << SYSVIEW_EVTID_USER_STOP)
#define   SYSVIEW_EVTMASK_IDLE              (1 << SYSVIEW_EVTID_IDLE)
#define   SYSVIEW_EVTMASK_ISR_TO_SCHEDULER  (1 << SYSVIEW_EVTID_ISR_TO_SCHEDULER)
#define   SYSVIEW_EVTMASK_TIMER_ENTER       (1 << SYSVIEW_EVTID_TIMER_ENTER)
#define   SYSVIEW_EVTMASK_TIMER_EXIT        (1 << SYSVIEW_EVTID_TIMER_EXIT)
#define   SYSVIEW_EVTMASK_STACK_INFO        (1 << SYSVIEW_EVTID_STACK_INFO)
#define   SYSVIEW_EVTMASK_MODULEDESC        (1 << SYSVIEW_EVTID_MODULEDESC)

#define   SYSVIEW_EVTMASK_INIT              (1 << SYSVIEW_EVTID_INIT)
#define   SYSVIEW_EVTMASK_NAME_RESOURCE     (1 << SYSVIEW_EVTID_NAME_RESOURCE)
#define   SYSVIEW_EVTMASK_PRINT_FORMATTED   (1 << SYSVIEW_EVTID_PRINT_FORMATTED)
#define   SYSVIEW_EVTMASK_NUMMODULES        (1 << SYSVIEW_EVTID_NUMMODULES)
#define   SYSVIEW_EVTMASK_END_CALL          (1 << SYSVIEW_EVTID_END_CALL)
#define   SYSVIEW_EVTMASK_TASK_TERMINATE    (1 << SYSVIEW_EVTID_TASK_TERMINATE)

#define   SYSVIEW_EVTMASK_EX                (1 << SYSVIEW_EVTID_EX)

#define   SYSVIEW_EVTMASK_ALL_INTERRUPTS    ( SYSVIEW_EVTMASK_ISR_ENTER           \
                                            | SYSVIEW_EVTMASK_ISR_EXIT            \
                                            | SYSVIEW_EVTMASK_ISR_TO_SCHEDULER)
#define   SYSVIEW_EVTMASK_ALL_TASKS         ( SYSVIEW_EVTMASK_TASK_START_EXEC     \
                                            | SYSVIEW_EVTMASK_TASK_STOP_EXEC      \
                                            | SYSVIEW_EVTMASK_TASK_START_READY    \
                                            | SYSVIEW_EVTMASK_TASK_STOP_READY     \
                                            | SYSVIEW_EVTMASK_TASK_CREATE         \
                                            | SYSVIEW_EVTMASK_TASK_INFO           \
                                            | SYSVIEW_EVTMASK_STACK_INFO          \
                                            | SYSVIEW_EVTMASK_TASK_TERMINATE)

/*********************************************************************
* 结构
*
**********************************************************************
*/

typedef struct {
  U32          TaskID;
  const char*  sName;
  U32          Prio;
  U32          StackBase;
  U32          StackSize;
} SEGGER_SYSVIEW_TASKINFO;

typedef struct SEGGER_SYSVIEW_MODULE_STRUCT SEGGER_SYSVIEW_MODULE;

struct SEGGER_SYSVIEW_MODULE_STRUCT {
  const char*                   sModule;
        U32                     NumEvents;
        U32                     EventOffset;
        void                    (*pfSendModuleDesc)(void);
        SEGGER_SYSVIEW_MODULE*  pNext;
};

typedef void (SEGGER_SYSVIEW_SEND_SYS_DESC_FUNC)(void);

/*********************************************************************
* API函数
*
**********************************************************************
*/

typedef struct {
  U64  (*pfGetTime)      (void);
  void (*pfSendTaskList) (void);
} SEGGER_SYSVIEW_OS_API;

/*********************************************************************
* 控制和初始化功能
*/
void SEGGER_SYSVIEW_Init                          (U32 SysFreq, U32 CPUFreq, const SEGGER_SYSVIEW_OS_API *pOSAPI, SEGGER_SYSVIEW_SEND_SYS_DESC_FUNC pfSendSysDesc);
void SEGGER_SYSVIEW_SetRAMBase                    (U32 RAMBaseAddress);
void SEGGER_SYSVIEW_Start                         (void);
void SEGGER_SYSVIEW_Stop                          (void);
void SEGGER_SYSVIEW_GetSysDesc                    (void);
void SEGGER_SYSVIEW_SendTaskList                  (void);
void SEGGER_SYSVIEW_SendTaskInfo                  (const SEGGER_SYSVIEW_TASKINFO* pInfo);
void SEGGER_SYSVIEW_SendSysDesc                   (const char* sSysDesc);
// 检查是否已启动跟踪
U8 SEGGER_SYSVIEW_Started(void);

/*********************************************************************
* 事件记录功能
*/
void SEGGER_SYSVIEW_RecordVoid                    (unsigned int EventId);
void SEGGER_SYSVIEW_RecordU32                     (unsigned int EventId, U32 Para0);
void SEGGER_SYSVIEW_RecordU32x2                   (unsigned int EventId, U32 Para0, U32 Para1);
void SEGGER_SYSVIEW_RecordU32x3                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2);
void SEGGER_SYSVIEW_RecordU32x4                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3);
void SEGGER_SYSVIEW_RecordU32x5                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4);
void SEGGER_SYSVIEW_RecordU32x6                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4, U32 Para5);
void SEGGER_SYSVIEW_RecordU32x7                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4, U32 Para5, U32 Para6);
void SEGGER_SYSVIEW_RecordU32x8                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4, U32 Para5, U32 Para6, U32 Para7);
void SEGGER_SYSVIEW_RecordU32x9                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4, U32 Para5, U32 Para6, U32 Para7, U32 Para8);
void SEGGER_SYSVIEW_RecordU32x10                  (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4, U32 Para5, U32 Para6, U32 Para7, U32 Para8, U32 Para9);
void SEGGER_SYSVIEW_RecordString                  (unsigned int EventId, const char* pString);
void SEGGER_SYSVIEW_RecordSystime                 (void);
void SEGGER_SYSVIEW_RecordEnterISR                (U32 IrqId);
void SEGGER_SYSVIEW_RecordExitISR                 (void);
void SEGGER_SYSVIEW_RecordExitISRToScheduler      (void);
void SEGGER_SYSVIEW_RecordEnterTimer              (U32 TimerId);
void SEGGER_SYSVIEW_RecordExitTimer               (void);
void SEGGER_SYSVIEW_RecordEndCall                 (unsigned int EventID);
void SEGGER_SYSVIEW_RecordEndCallU32              (unsigned int EventID, U32 Para0);

void SEGGER_SYSVIEW_OnIdle                        (void);
void SEGGER_SYSVIEW_OnTaskCreate                  (U32 TaskId);
void SEGGER_SYSVIEW_OnTaskTerminate               (U32 TaskId);
void SEGGER_SYSVIEW_OnTaskStartExec               (U32 TaskId);
void SEGGER_SYSVIEW_OnTaskStopExec                (void);
void SEGGER_SYSVIEW_OnTaskStartReady              (U32 TaskId);
void SEGGER_SYSVIEW_OnTaskStopReady               (U32 TaskId, unsigned int Cause);
void SEGGER_SYSVIEW_OnUserStart                   (unsigned int UserId);       // 用户定义事件的开始（如配置文件的子例程）
void SEGGER_SYSVIEW_OnUserStop                    (unsigned int UserId);       // 用户定义事件的开始

void SEGGER_SYSVIEW_NameResource                  (U32 ResourceId, const char* sName);

int  SEGGER_SYSVIEW_SendPacket                    (U8* pPacket, U8* pPayloadEnd, unsigned int EventId);

/*********************************************************************
* 事件参数编码函数
*/
U8*  SEGGER_SYSVIEW_EncodeU32                     (U8* pPayload, U32 Value);
U8*  SEGGER_SYSVIEW_EncodeData                    (U8* pPayload, const char* pSrc, unsigned int Len);
U8*  SEGGER_SYSVIEW_EncodeString                  (U8* pPayload, const char* s, unsigned int MaxLen);
U8*  SEGGER_SYSVIEW_EncodeId                      (U8* pPayload, U32 Id);
U32  SEGGER_SYSVIEW_ShrinkId                      (U32 Id);


/*********************************************************************
* 中间件模块注册
*/
void SEGGER_SYSVIEW_RegisterModule                (SEGGER_SYSVIEW_MODULE* pModule);
void SEGGER_SYSVIEW_RecordModuleDescription       (const SEGGER_SYSVIEW_MODULE* pModule, const char* sDescription);
void SEGGER_SYSVIEW_SendModule                    (U8 ModuleId);
void SEGGER_SYSVIEW_SendModuleDescription         (void);
void SEGGER_SYSVIEW_SendNumModules                (void);

/*********************************************************************
* printf样式函数
*/
#ifndef SEGGER_SYSVIEW_EXCLUDE_PRINTF // 在项目中定义以避免有关变量参数列表的警告
void SEGGER_SYSVIEW_PrintfHostEx                  (const char* s, U32 Options, ...);
void SEGGER_SYSVIEW_PrintfTargetEx                (const char* s, U32 Options, ...);
void SEGGER_SYSVIEW_PrintfHost                    (const char* s, ...);
void SEGGER_SYSVIEW_PrintfTarget                  (const char* s, ...);
void SEGGER_SYSVIEW_WarnfHost                     (const char* s, ...);
void SEGGER_SYSVIEW_WarnfTarget                   (const char* s, ...);
void SEGGER_SYSVIEW_ErrorfHost                    (const char* s, ...);
void SEGGER_SYSVIEW_ErrorfTarget                  (const char* s, ...);
#endif

void SEGGER_SYSVIEW_Print                         (const char* s);
void SEGGER_SYSVIEW_Warn                          (const char* s);
void SEGGER_SYSVIEW_Error                         (const char* s);

/*********************************************************************
* 运行时配置功能
*/
void SEGGER_SYSVIEW_EnableEvents                  (U32 EnableMask);
void SEGGER_SYSVIEW_DisableEvents                 (U32 DisableMask);

/*********************************************************************
* 应用程序提供的功能
*/
void SEGGER_SYSVIEW_Conf                          (void);
U32  SEGGER_SYSVIEW_X_GetTimestamp                (void);
U32  SEGGER_SYSVIEW_X_GetInterruptId              (void);

#ifdef __cplusplus
}
#endif

#endif

/***************************文件结尾****************************/

