// 版权所有2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#pragma once

#ifdef CONFIG_HEAP_TASK_TRACKING

#ifdef __cplusplus
extern "C" {
#endif

// 此宏控制为每个任务分区提供的空间大小
// 堆分配信息。
#define NUM_HEAP_TASK_CAPS 4

/** @brief 用于收集按所选上限划分的每个任务堆分配总数的结构*/
typedef struct {
    TaskHandle_t task;                ///<这些总计所属的任务
    size_t size[NUM_HEAP_TASK_CAPS];  ///<按所选上限划分的总分配
    size_t count[NUM_HEAP_TASK_CAPS]; ///<按所选大写分隔的块数
} heap_task_totals_t;

/** @brief 提供任务分配的块的详细信息的结构*/
typedef struct {
    TaskHandle_t task;                ///<分配块的任务
    void *address;                    ///<分配块的用户地址
    uint32_t size;                    ///<分配块的大小
} heap_task_block_t;

/** @brief 为heap_caps_get_per_task_info提供参数的结构
 *
 * “caps”和“mask”数组允许按选定的堆区域功能集划分每个任务的堆分配总数，以便在一次扫描中累积多个区域的总数。按顺序将每个区域的能力标志与掩码[i]进行AND比较；该区域中的分配将添加到第一个匹配的i的总计->大小[i]和总计->计数[i]。要在不进行任何分区的情况下收集总数，请将掩码[0]和大写[0]都设置为零。分配总数在heap_task_totals_tructs的“totals”数组中返回。为了便于比较连续调用之间的总计数组，可以在一次调用到下一次调用之间填充该数组，这样即使某些任务释放了其块或被删除，任务的顺序也相同。预填充的块的数量由num_totals给出，返回时更新。如果分配的任务多于总阵列的容量（由max_totals给出），则不会收集多余任务的信息。如果不需要总计，则总计数组指针可以为NULL。
 *
 * “tasks”数组包含任务的句柄列表，这些任务的块详细信息将在heap_task_block_t结构的“blocks”数组中返回。如果任务数组指针为NULL，则所有任务的块详细信息将返回到缓冲区数组的容量（由max_blocks给出）。函数返回值告诉填充到数组中的块数。如果不需要块详细信息，则块数组指针可以为NULL，或者max_blocks可以设置为零。
 */
typedef struct {
    int32_t caps[NUM_HEAP_TASK_CAPS]; ///<分区任务总数的上限数组
    int32_t mask[NUM_HEAP_TASK_CAPS]; ///<caps必须匹配的掩码数组
    TaskHandle_t *tasks;              ///<返回块信息的任务数组
    size_t num_tasks;                 ///<任务数组的长度
    heap_task_totals_t *totals;       ///<收集任务总数的结构数组
    size_t *num_totals;               ///<当前在数组中的任务结构数
    size_t max_totals;                ///<任务总数结构数组的容量
    heap_task_block_t *blocks;        ///<任务块详细结构数组
    size_t max_blocks;                ///<任务块信息结构阵列的容量
} heap_task_info_params_t;

/**
 * @brief 返回每个任务的堆分配总数和块列表。
 *
 * 对于从堆中分配了内存的每个任务，返回与一组或多组功能匹配的区域内的分配总数。
 *
 * 还可以选择返回一个结构数组，提供一个或多个请求任务或所有任务分配的每个块的详细信息。
 *
 * @param params 用于保存函数所有参数的结构
 * (@see heap_task_info_params_t）。
 * @return 返回的块详细结构数（@参见heap_task_block_t）。
 */
extern size_t heap_caps_get_per_task_info(heap_task_info_params_t *params);

#ifdef __cplusplus
}
#endif

#endif // CONFIG_HEAP_TASK_TRACKING

