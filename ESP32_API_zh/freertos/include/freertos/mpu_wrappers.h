/*
 * FreeRTOS内核V10.4.3版权所有（C）2020 Amazon。com，Inc.或其附属公司。保留所有权利。
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org https://github.com/FreeRTOS
 *
 */

#ifndef MPU_WRAPPERS_H
#define MPU_WRAPPERS_H

/* 该文件重新定义了通过包装宏调用的API函数，但仅适用于使用MPU的端口。*/
#if portUSING_MPU_WRAPPERS

/* 当队列中包含此文件时，将定义MPU_WRAPPERS_INCLUDED_FROM_API_FILE。c或任务。c以防止其在这些文件中产生影响。*/
    #ifndef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*
 * 将标准（非MPU）API函数映射到启动“MPU_”的等效函数。这将导致应用程序代码调用MPU_版本，该版本将非MPU版本包装为特权提升然后降级代码，因此内核代码始终以完全特权运行。
 */

/* 映射标准任务。h API功能与MPU等效。*/
        #define xTaskCreate                            MPU_xTaskCreate
        #define xTaskCreateStatic                      MPU_xTaskCreateStatic
        #define xTaskCreateRestricted                  MPU_xTaskCreateRestricted
        #define vTaskAllocateMPURegions                MPU_vTaskAllocateMPURegions
        #define vTaskDelete                            MPU_vTaskDelete
        #define vTaskDelay                             MPU_vTaskDelay
        #define vTaskDelayUntil                        MPU_vTaskDelayUntil
        #define xTaskAbortDelay                        MPU_xTaskAbortDelay
        #define uxTaskPriorityGet                      MPU_uxTaskPriorityGet
        #define eTaskGetState                          MPU_eTaskGetState
        #define vTaskGetInfo                           MPU_vTaskGetInfo
        #define vTaskPrioritySet                       MPU_vTaskPrioritySet
        #define vTaskSuspend                           MPU_vTaskSuspend
        #define vTaskResume                            MPU_vTaskResume
        #define vTaskSuspendAll                        MPU_vTaskSuspendAll
        #define xTaskResumeAll                         MPU_xTaskResumeAll
        #define xTaskGetTickCount                      MPU_xTaskGetTickCount
        #define uxTaskGetNumberOfTasks                 MPU_uxTaskGetNumberOfTasks
        #define pcTaskGetName                          MPU_pcTaskGetName
        #define xTaskGetHandle                         MPU_xTaskGetHandle
        #define uxTaskGetStackHighWaterMark            MPU_uxTaskGetStackHighWaterMark
        #define uxTaskGetStackHighWaterMark2           MPU_uxTaskGetStackHighWaterMark2
        #define vTaskSetApplicationTaskTag             MPU_vTaskSetApplicationTaskTag
        #define xTaskGetApplicationTaskTag             MPU_xTaskGetApplicationTaskTag
        // #定义vTaskSetThreadLocalStoragePointer MPU_vTaskSet线程本地存储指针
        // #定义pvTaskGetThreadLocalStoragePointer MPU_pvTaskGet线程本地存储指针
        #define xTaskCallApplicationTaskHook           MPU_xTaskCallApplicationTaskHook
        #define xTaskGetIdleTaskHandle                 MPU_xTaskGetIdleTaskHandle
        #define uxTaskGetSystemState                   MPU_uxTaskGetSystemState
        #define vTaskList                              MPU_vTaskList
        #define vTaskGetRunTimeStats                   MPU_vTaskGetRunTimeStats
        #define ulTaskGetIdleRunTimeCounter            MPU_ulTaskGetIdleRunTimeCounter
        #define xTaskGenericNotify                     MPU_xTaskGenericNotify
        #define xTaskNotifyWait                        MPU_xTaskNotifyWait
        #define ulTaskNotifyTake                       MPU_ulTaskNotifyTake
        #define xTaskNotifyStateClear                  MPU_xTaskNotifyStateClear
        #define xTaskCatchUpTicks                      MPU_xTaskCatchUpTicks

        #define xTaskGetCurrentTaskHandle              MPU_xTaskGetCurrentTaskHandle
        #define vTaskSetTimeOutState                   MPU_vTaskSetTimeOutState
        #define xTaskCheckForTimeOut                   MPU_xTaskCheckForTimeOut
        #define xTaskGetSchedulerState                 MPU_xTaskGetSchedulerState

        /* 映射标准队列。h API功能与MPU等效。*/
        #define xQueueGenericSend                      MPU_xQueueGenericSend
        #define xQueueReceive                          MPU_xQueueReceive
        #define xQueuePeek                             MPU_xQueuePeek
        #define xQueueSemaphoreTake                    MPU_xQueueSemaphoreTake
        #define uxQueueMessagesWaiting                 MPU_uxQueueMessagesWaiting
        #define uxQueueSpacesAvailable                 MPU_uxQueueSpacesAvailable
        #define vQueueDelete                           MPU_vQueueDelete
        #define xQueueCreateMutex                      MPU_xQueueCreateMutex
        #define xQueueCreateMutexStatic                MPU_xQueueCreateMutexStatic
        #define xQueueCreateCountingSemaphore          MPU_xQueueCreateCountingSemaphore
        #define xQueueCreateCountingSemaphoreStatic    MPU_xQueueCreateCountingSemaphoreStatic
        #define xQueueGetMutexHolder                   MPU_xQueueGetMutexHolder
        #define xQueueTakeMutexRecursive               MPU_xQueueTakeMutexRecursive
        #define xQueueGiveMutexRecursive               MPU_xQueueGiveMutexRecursive
        #define xQueueGenericCreate                    MPU_xQueueGenericCreate
        #define xQueueGenericCreateStatic              MPU_xQueueGenericCreateStatic
        #define xQueueCreateSet                        MPU_xQueueCreateSet
        #define xQueueAddToSet                         MPU_xQueueAddToSet
        #define xQueueRemoveFromSet                    MPU_xQueueRemoveFromSet
        #define xQueueSelectFromSet                    MPU_xQueueSelectFromSet
        #define xQueueGenericReset                     MPU_xQueueGenericReset

        #if ( configQUEUE_REGISTRY_SIZE > 0 )
            #define vQueueAddToRegistry                MPU_vQueueAddToRegistry
            #define vQueueUnregisterQueue              MPU_vQueueUnregisterQueue
            #define pcQueueGetName                     MPU_pcQueueGetName
        #endif

/* 映射标准计时器。h API功能与MPU等效。*/
        #define xTimerCreate                           MPU_xTimerCreate
        #define xTimerCreateStatic                     MPU_xTimerCreateStatic
        #define pvTimerGetTimerID                      MPU_pvTimerGetTimerID
        #define vTimerSetTimerID                       MPU_vTimerSetTimerID
        #define xTimerIsTimerActive                    MPU_xTimerIsTimerActive
        #define xTimerGetTimerDaemonTaskHandle         MPU_xTimerGetTimerDaemonTaskHandle
        #define xTimerPendFunctionCall                 MPU_xTimerPendFunctionCall
        #define pcTimerGetName                         MPU_pcTimerGetName
        #define vTimerSetReloadMode                    MPU_vTimerSetReloadMode
        #define xTimerGetPeriod                        MPU_xTimerGetPeriod
        #define xTimerGetExpiryTime                    MPU_xTimerGetExpiryTime
        #define xTimerGenericCommand                   MPU_xTimerGenericCommand

/* 映射标准事件组。h API功能与MPU等效。*/
        #define xEventGroupCreate                      MPU_xEventGroupCreate
        #define xEventGroupCreateStatic                MPU_xEventGroupCreateStatic
        #define xEventGroupWaitBits                    MPU_xEventGroupWaitBits
        #define xEventGroupClearBits                   MPU_xEventGroupClearBits
        #define xEventGroupSetBits                     MPU_xEventGroupSetBits
        #define xEventGroupSync                        MPU_xEventGroupSync
        #define vEventGroupDelete                      MPU_vEventGroupDelete

/* 映射标准消息/stream_buffer。h API功能与MPU等效。*/
        #define xStreamBufferSend                      MPU_xStreamBufferSend
        #define xStreamBufferReceive                   MPU_xStreamBufferReceive
        #define xStreamBufferNextMessageLengthBytes    MPU_xStreamBufferNextMessageLengthBytes
        #define vStreamBufferDelete                    MPU_vStreamBufferDelete
        #define xStreamBufferIsFull                    MPU_xStreamBufferIsFull
        #define xStreamBufferIsEmpty                   MPU_xStreamBufferIsEmpty
        #define xStreamBufferReset                     MPU_xStreamBufferReset
        #define xStreamBufferSpacesAvailable           MPU_xStreamBufferSpacesAvailable
        #define xStreamBufferBytesAvailable            MPU_xStreamBufferBytesAvailable
        #define xStreamBufferSetTriggerLevel           MPU_xStreamBufferSetTriggerLevel
        #define xStreamBufferGenericCreate             MPU_xStreamBufferGenericCreate
        #define xStreamBufferGenericCreateStatic       MPU_xStreamBufferGenericCreateStatic


/* 删除特权函数宏，但保留privileged_DATA宏，以便应用程序可以将数据放在特权访问部分（使用静态分配的对象时很有用）。*/
        #define PRIVILEGED_FUNCTION
        #define PRIVILEGED_DATA    __attribute__( ( section( "privileged_data" ) ) )
        #define FREERTOS_SYSTEM_CALL

    #else /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

/* 确保API函数位于特权执行部分。*/
        #define PRIVILEGED_FUNCTION     __attribute__( ( section( "privileged_functions" ) ) )
        #define PRIVILEGED_DATA         __attribute__( ( section( "privileged_data" ) ) )
        #define FREERTOS_SYSTEM_CALL    __attribute__( ( section( "freertos_system_calls" ) ) )

    #endif /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

#else /* 端口USING_MPU_WRAPPERS*/

    #define PRIVILEGED_FUNCTION
    #define PRIVILEGED_DATA
    #define FREERTOS_SYSTEM_CALL
    #define portUSING_MPU_WRAPPERS    0

#endif /* 端口USING_MPU_WRAPPERS*/


#endif /* MPU_WRAPPERS_H */

