// 版权所有2015-2021 Espressif Systems（Shanghai）PTE LTD
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#if ( configENABLE_TASK_SNAPSHOT == 1 )

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 选中`freertos_tasks_c_additions。h`file获取有关这些函数声明的更多信息。
 */
UBaseType_t pxTCBGetSize ( void );
ListItem_t*	pxTCBGetStateListItem ( void *pxTCB );
StackType_t* pxTCBGetStartOfStack ( void *pxTCB );
StackType_t* pxTCBGetTopOfStack ( void *pxTCB );
StackType_t* pxTCBGetEndOfStack ( void *pxTCB );
List_t* pxListGetReadyTask ( UBaseType_t idx );
List_t* pxListGetReadyPendingTask ( UBaseType_t idx );
List_t* pxGetDelayedTaskList ( void );
List_t* pxGetOverflowDelayedTaskList ( void );
List_t* pxGetTasksWaitingTermination ( void );
List_t* pxGetSuspendedTaskList ( void );

/**
 * 与uxTaskGetSnapshotAll（）函数一起使用，保存系统中每个任务的内存快照。我们需要这个结构，因为TCB_t是在tasks.c中定义的（隐藏的）。
 */
typedef struct xTASK_SNAPSHOT
{
	void        *pxTCB;         /*!< 任务控制块的地址。*/
	StackType_t *pxTopOfStack;  /*!< 指向放置在任务堆栈上的最后一个项目的位置。*/
	StackType_t *pxEndOfStack;  /*!< 指向堆栈的末端。pxTopOfStack＜pxEndOfStack，堆栈增长高2hi*/
} TaskSnapshot_t;


/*
 * 此函数为系统中的每个任务使用TaskSnapshot_t结构填充数组。由紧急处理代码用于获取系统中所有任务的快照。仅当configENABLE_TASK_SNAPSHOT设置为1时可用。
 * @param pxTaskSnapshotArray 指向存储任务快照数据的TaskSnapshot_t结构数组的指针。
 * @param uxArraySize 任务快照阵列的大小。
 * @param pxTcbSz 指向TCB存储大小的指针。
 * @return 数组中存储的元素数。
 */
UBaseType_t uxTaskGetSnapshotAll( TaskSnapshot_t * const pxTaskSnapshotArray, const UBaseType_t uxArraySize, UBaseType_t * const pxTcbSz );

/*
 * 此函数迭代系统中的所有任务。由紧急处理代码用于迭代系统中的任务。仅当configENABLE_TASK_SNAPSHOT设置为1时可用。
 * @note FreeRTOS运行时不应使用此功能（因为它不获取任何锁）。
 * @param pxTask 任务句柄。
 * @return 下一个任务的句柄。如果pxTask为NULL，则返回第一个任务的hadnle。
 */
TaskHandle_t pxTaskGetNext( TaskHandle_t pxTask );

/*
 * 此函数用于填充指定任务的TaskSnapshot_t结构。由紧急处理代码用于获取任务快照。仅当configENABLE_TASK_SNAPSHOT设置为1时可用。
 * @note FreeRTOS运行时不应使用此功能（因为它不获取任何锁）。
 * @param pxTask 任务句柄。
 * @param pxTaskSnapshot 要填充的TaskSnapshot_t结构的地址。
 */
void vTaskGetSnapshot( TaskHandle_t pxTask, TaskSnapshot_t *pxTaskSnapshot );

#ifdef __cplusplus
}
#endif

#endif

