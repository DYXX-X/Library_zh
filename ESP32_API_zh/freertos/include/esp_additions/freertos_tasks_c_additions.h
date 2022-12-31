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

/**
 * 此文件将包含在“任务”中。因此，它不能包含在任何（其他）文件中。下面的函数只包含“tasks”中静态变量的getter。c`文件。应该调用这些函数的唯一源文件是“/addings”目录中的文件。
 */

#if ( configENABLE_TASK_SNAPSHOT == 1 )

	UBaseType_t pxTCBGetSize ( void )
	{
		return sizeof(TCB_t);
	}

	ListItem_t*	pxTCBGetStateListItem ( void *pxTCB )
	{
		return &(((TCB_t*)pxTCB)->xStateListItem);
	}

	StackType_t* pxTCBGetStartOfStack ( void *pxTCB )
	{
		return (StackType_t*) ((TCB_t*)pxTCB)->pxStack;
	}

	StackType_t* pxTCBGetTopOfStack ( void *pxTCB )
	{
		return (StackType_t*) ((TCB_t*)pxTCB)->pxTopOfStack;
	}

	StackType_t* pxTCBGetEndOfStack ( void *pxTCB )
	{
		return (StackType_t*) ((TCB_t*)pxTCB)->pxEndOfStack;
	}


	List_t* pxListGetReadyTask ( UBaseType_t idx )
	{
		return &( pxReadyTasksLists[idx] );
	}

	List_t* pxListGetReadyPendingTask ( UBaseType_t idx )
	{
		return &( xPendingReadyList[idx] );
	}

	List_t* pxGetDelayedTaskList ( void ) {
		return pxDelayedTaskList;
	}

	List_t* pxGetOverflowDelayedTaskList ( void ) {
		return pxOverflowDelayedTaskList;
	}

	List_t* pxGetTasksWaitingTermination ( void ) {
		return &xTasksWaitingTermination;
	}

	List_t* pxGetSuspendedTaskList ( void ) {
		return &xSuspendedTaskList;
	}

#endif

