// 版权所有2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef ESP_EVENT_H_
#define ESP_EVENT_H_

#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include "esp_event_base.h"
// 遗留事件循环未在Linux目标上实现
#if !CONFIG_IDF_TARGET_LINUX
#include "esp_event_legacy.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

///用于创建事件循环的配置
typedef struct {
    int32_t queue_size;                         /**<事件循环队列的大小*/
    const char *task_name;                      /**<事件循环任务的名称；如果为NULL，则不会为事件循环创建专用任务*/
    UBaseType_t task_priority;                  /**<事件循环任务的优先级，如果任务名称为NULL，则忽略*/
    uint32_t task_stack_size;                   /**<事件循环任务的堆栈大小，如果任务名称为NULL，则忽略*/
    BaseType_t task_core_id;                    /**<事件循环任务固定到的核心，如果任务名称为NULL，则忽略*/
} esp_event_loop_args_t;

/**
 * @brief 创建新的事件循环。
 *
 * @param[in] event_loop_args 要创建的事件循环的配置结构
 * @param[out] event_loop 创建的事件循环的句柄
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG:event_loop_args或event_loop为空
 *  -ESP_ERR_NO_MEM:无法为事件循环列表分配内存
 *  -ESP_FAIL:无法创建任务循环
 *  -其他：失败
 */
esp_err_t esp_event_loop_create(const esp_event_loop_args_t *event_loop_args, esp_event_loop_handle_t *event_loop);

/**
 * @brief 删除现有事件循环。
 *
 * @param[in] event_loop 要删除的事件循环，不能为NULL
 *
 * @return
 *  -ESP_OK：成功
 *  -其他：失败
 */
esp_err_t esp_event_loop_delete(esp_event_loop_handle_t event_loop);

/**
 * @brief 创建默认事件循环
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_NO_MEM:无法为事件循环列表分配内存
 *  -ESP_FAIL:无法创建任务循环
 *  -其他：失败
 */
esp_err_t esp_event_loop_create_default(void);

/**
 * @brief 删除默认事件循环
 *
 * @return
 *  -ESP_OK：成功
 *  -其他：失败
 */
esp_err_t esp_event_loop_delete_default(void);

/**
 * @brief 分派发布到事件循环的事件。
 *
 * 此函数用于分派发布到没有专用任务的循环的事件，即在创建循环期间，在event_loop_args参数中将任务名称设置为NULL。此函数包含一个参数来限制它运行的时间，当该时间到期（或稍后某个时间）时，将控制权返回给调用者。无法保证对该函数的调用将在到期时退出。也不能保证在调用期间已调度事件，因为函数可能已在事件队列上花费了所有分配的时间。然而，一旦事件被取消排队，它就保证被调度。这种保证导致无法在到期时完全退出，因为（1）内部互斥锁的阻塞是调度未排队事件所必需的，（2）在调度未排队的事件期间，无法控制处理程序代码执行所占用的时间。因此，保证退出时间是分配的时间+调度最后一个未排队事件所需的时间量。
 *
 * 在等待队列超时的情况下，返回ESP_OK而不是ESP_ERR_TIMEOUT，因为这是正常行为。
 *
 * @param[in] event_loop 从中分派已发布事件的事件循环不能为NULL
 * @param[in] ticks_to_run 运行循环的节拍数
 *
 * @note 遇到已发布到循环的未知事件只会生成警告，而不是错误。
 *
 * @return
 *  -ESP_OK：成功
 *  -其他：失败
 */
esp_err_t esp_event_loop_run(esp_event_loop_handle_t event_loop, TickType_t ticks_to_run);

/**
 * @brief 将事件处理程序注册到系统事件循环（传统）。
 *
 * @note 此函数已过时，很快将被弃用，请改用esp_event_handler_instance_register（）。
 *
 * 此函数可用于注册以下事件的处理程序：（1）特定事件，（2）特定事件库的所有事件，或（3）系统事件循环已知的所有事件。
 *
 *  -特定事件：指定确切的event_base和event_id
 *  -特定基的所有事件：指定确切的event_base，并使用ESP_event_ANY_ID作为event_ID
 *  -循环已知的所有事件：使用ESP_EVENT_ANY_BASE作为EVENT_BASE，使用ESP_EVENT_ANY_ID作为EVENT_ID
 *
 * 可以向事件注册多个处理程序。也可以将单个处理程序注册到多个事件。但是，将同一处理程序多次注册到同一事件会导致覆盖以前的注册。
 *
 * @param[in] event_base 要为其注册处理程序的事件的基id
 * @param[in] event_id 要为其注册处理程序的事件的id
 * @param[in] event_handler 分派事件时调用的处理程序函数
 * @param[in] event_handler_arg 除了事件数据之外，在调用处理程序时传递给它的数据
 *
 * @note 事件循环库不维护eventhandler_arg的副本，因此用户应确保在调用处理程序时eventhandler_arg仍然指向有效位置
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_NO_MEM:无法为处理程序分配内存
 *  -ESP_ERR_INVALID_ARG：事件基础和事件id的组合无效
 *  -其他：失败
 */
esp_err_t esp_event_handler_register(esp_event_base_t event_base,
                                     int32_t event_id,
                                     esp_event_handler_t event_handler,
                                     void *event_handler_arg);

/**
 * @brief 将事件处理程序注册到特定循环（传统）。
 *
 * @note 此函数已过时，很快将被弃用，请改用esp_event_handler_instance_register_with（）。
 *
 * 此函数的行为方式与esp_event_handler_register相同，除了要向其注册处理程序的事件循环的附加规范。
 *
 * @param[in] event_loop 将此处理程序函数注册到的事件循环不能为NULL
 * @param[in] event_base 要为其注册处理程序的事件的基id
 * @param[in] event_id 要为其注册处理程序的事件的id
 * @param[in] event_handler 分派事件时调用的处理程序函数
 * @param[in] event_handler_arg 除了事件数据之外，在调用处理程序时传递给它的数据
 *
 * @note 事件循环库不维护eventhandler_arg的副本，因此用户应确保在调用处理程序时eventhandler_arg仍然指向有效位置
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_NO_MEM:无法为处理程序分配内存
 *  -ESP_ERR_INVALID_ARG：事件基础和事件id的组合无效
 *  -其他：失败
 */
esp_err_t esp_event_handler_register_with(esp_event_loop_handle_t event_loop,
                                          esp_event_base_t event_base,
                                          int32_t event_id,
                                          esp_event_handler_t event_handler,
                                          void *event_handler_arg);

/**
 * @brief 将事件处理程序的实例注册到特定循环。
 *
 * 此函数可用于注册以下事件的处理程序：（1）特定事件，（2）特定事件库的所有事件，或（3）系统事件循环已知的所有事件。
 *
 *  -特定事件：指定确切的event_base和event_id
 *  -特定基的所有事件：指定确切的event_base，并使用ESP_event_ANY_ID作为event_ID
 *  -循环已知的所有事件：使用ESP_EVENT_ANY_BASE作为EVENT_BASE，使用ESP_EVENT_ANY_ID作为EVENT_ID
 *
 * 除了错误之外，该函数还返回一个实例对象作为输出参数，以标识每个注册。这是在删除事件循环之前删除（注销）注册所必需的。
 *
 * 向事件注册多个处理程序、向多个事件注册单个处理程序以及向同一事件多次注册同一处理程序是可能的。每个注册都产生一个不同的实例对象，该对象在注册生存期内标识它。
 *
 * @param[in] event_loop 将此处理程序函数注册到的事件循环不能为NULL
 * @param[in] event_base 要为其注册处理程序的事件的基id
 * @param[in] event_id 要为其注册处理程序的事件的id
 * @param[in] event_handler 分派事件时调用的处理程序函数
 * @param[in] event_handler_arg 除了事件数据之外，在调用处理程序时传递给它的数据
 * @param[out] instance 与已注册事件处理程序和数据相关的事件处理程序实例对象可以为NULL。如果在删除整个事件循环之前应注销特定回调实例，则需要保留此选项。可以多次注册同一事件处理程序，并生成不同的实例对象。所有注册的数据都可以相同。如果不需要注销，但应该在删除事件循环时删除处理程序，则实例可以为NULL。
 *
 * @note 事件循环库不维护eventhandler_arg的副本，因此用户应确保在调用处理程序时eventhandler_arg仍然指向有效位置
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_NO_MEM:无法为处理程序分配内存
 *  -ESP_ERR_INVALID_ARG：事件基和事件id的组合无效，或实例为NULL
 *  -其他：失败
 */
esp_err_t esp_event_handler_instance_register_with(esp_event_loop_handle_t event_loop,
                                                  esp_event_base_t event_base,
                                                  int32_t event_id,
                                                  esp_event_handler_t event_handler,
                                                  void *event_handler_arg,
                                                  esp_event_handler_instance_t *instance);

/**
 * @brief 将事件处理程序的实例注册到默认循环。
 *
 * 此函数的作用与esp_event_handler_instance_register_with相同，只是它将处理程序注册到默认事件循环中。
 *
 * @param[in] event_base 要为其注册处理程序的事件的基id
 * @param[in] event_id 要为其注册处理程序的事件的id
 * @param[in] event_handler 分派事件时调用的处理程序函数
 * @param[in] event_handler_arg 除了事件数据之外，在调用处理程序时传递给它的数据
 * @param[out] instance 与已注册事件处理程序和数据相关的事件处理程序实例对象可以为NULL。如果在删除整个事件循环之前应注销特定回调实例，则需要保留此选项。可以多次注册同一事件处理程序，并生成不同的实例对象。所有注册的数据都可以相同。如果不需要注销，但应该在删除事件循环时删除处理程序，则实例可以为NULL。
 *
 * @note 事件循环库不维护eventhandler_arg的副本，因此用户应确保在调用处理程序时eventhandler_arg仍然指向有效位置
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_NO_MEM:无法为处理程序分配内存
 *  -ESP_ERR_INVALID_ARG：事件基和事件id的组合无效，或实例为NULL
 *  -其他：失败
 */
esp_err_t esp_event_handler_instance_register(esp_event_base_t event_base,
                                             int32_t event_id,
                                             esp_event_handler_t event_handler,
                                             void *event_handler_arg,
                                             esp_event_handler_instance_t *instance);

/**
 * @brief 使用系统事件循环注销处理程序（旧版）。
 *
 * @note 此函数已过时，很快将被弃用，请改用esp_event_handler_instance_unregister（）。
 *
 * 注销处理程序，以便在分派期间不再调用它。可以为先前注册的event_base和event_id的任意组合注销处理程序。要注销处理程序，event_base和event_id参数必须与注册该处理程序时传递给esp_event_handler_register（）的参数完全匹配。传递ESP_EVENT_ANY_BASE和/或ESP_EVENT_ANY_ID将仅注销使用相同通配符参数注册的处理程序。
 *
 * @note 使用ESP_EVENT_ANY_ID时，不会注销使用相同基注册到特定事件ID的处理程序。使用ESP_EVENT_ANY_BASE时，注册到特定基的事件也不会被注销。这避免了意外注销其他用户或组件注册的处理程序。
 *
 * @param[in] event_base 用于注销处理程序的事件的基
 * @param[in] event_id 用于注销处理程序的事件的id
 * @param[in] event_handler 要注销的处理程序
 *
 * @return ESP_OK成功
 * @return ESP_ERR_INVALID_ARG事件基础和事件id的组合无效
 * @return 其他人失败
 */
esp_err_t esp_event_handler_unregister(esp_event_base_t event_base,
                                       int32_t event_id,
                                       esp_event_handler_t event_handler);

/**
 * @brief 从特定事件循环（传统）中注销处理程序。
 *
 * @note 此函数已过时，很快将被弃用，请改用esp_event_handler_instance_unregister_with（）。
 *
 * 此函数的行为方式与esp_event_handler_unregister相同，只是对用于注销处理程序的事件循环进行了额外的规范。
 *
 * @param[in] event_loop 用于注销此处理程序函数的事件循环不能为NULL
 * @param[in] event_base 用于注销处理程序的事件的基
 * @param[in] event_id 用于注销处理程序的事件的id
 * @param[in] event_handler 要注销的处理程序
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG：事件基础和事件id的组合无效
 *  -其他：失败
 */
esp_err_t esp_event_handler_unregister_with(esp_event_loop_handle_t event_loop,
                                            esp_event_base_t event_base,
                                            int32_t event_id,
                                            esp_event_handler_t event_handler);

/**
 * @brief 从特定事件循环中注销处理程序实例。
 *
 * 注销处理程序实例，以便在分派期间不再调用它。可以为先前注册的event_base和event_id的任意组合注销处理程序实例。要注销处理程序实例，event_base和event_id参数必须与注册该处理程序实例时传递给esp_event_handler_instance_register（）的参数完全匹配。传递ESP_EVENT_ANY_BASE和/或ESP_EVENT_ANY_ID将仅注销使用相同通配符参数注册的处理程序实例。
 *
 * @note 使用ESP_EVENT_ANY_ID时，不会注销使用相同基注册到特定事件ID的处理程序。使用ESP_EVENT_ANY_BASE时，注册到特定基的事件也不会被注销。这避免了意外注销其他用户或组件注册的处理程序。
 *
 * @param[in] event_loop 用于注销此处理程序函数的事件循环不能为NULL
 * @param[in] event_base 用于注销处理程序的事件的基
 * @param[in] event_id 用于注销处理程序的事件的id
 * @param[in] instance 要注销的注册的实例对象
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG：事件基础和事件id的组合无效
 *  -其他：失败
 */
esp_err_t esp_event_handler_instance_unregister_with(esp_event_loop_handle_t event_loop,
                                                     esp_event_base_t event_base,
                                                     int32_t event_id,
                                                     esp_event_handler_instance_t instance);

/**
 * @brief 从系统事件循环中注销处理程序。
 *
 * 此函数的作用与esp_event_handler_instance_unregister_with相同，只是它从默认事件循环中注销处理程序实例。
 *
 * @param[in] event_base 用于注销处理程序的事件的基
 * @param[in] event_id 用于注销处理程序的事件的id
 * @param[in] instance 要注销的注册的实例对象
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG：事件基础和事件id的组合无效
 *  -其他：失败
 */
esp_err_t esp_event_handler_instance_unregister(esp_event_base_t event_base,
                                                int32_t event_id,
                                                esp_event_handler_instance_t instance);

/**
 * @brief 将事件发布到系统默认事件循环。事件循环库保存event_data的副本，并自动管理副本的生命周期（分配+删除）；这确保了处理程序接收的数据始终有效。
 *
 * @param[in] event_base 标识事件的事件库
 * @param[in] event_id 标识事件的事件id
 * @param[in] event_data 传递给处理程序的特定于事件发生的数据
 * @param[in] event_data_size 事件数据的大小
 * @param[in] ticks_to_wait 完整事件队列上要阻止的标记数
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_TIMEOUT：等待事件队列解除阻止的时间已过期，从ISR发布时队列已满
 *  -ESP_ERR_INVALID_ARG：事件基础和事件id的组合无效
 *  -其他：失败
 */
esp_err_t esp_event_post(esp_event_base_t event_base,
                         int32_t event_id,
                         void *event_data,
                         size_t event_data_size,
                         TickType_t ticks_to_wait);

/**
 * @brief 将事件发布到指定的事件循环。事件循环库保存event_data的副本，并自动管理副本的生命周期（分配+删除）；这确保了处理程序接收的数据始终有效。
 *
 * 此函数的行为方式与esp_event_post_to相同，只是对要将事件发布到的事件循环进行了额外的规范。
 *
 * @param[in] event_loop 要发布到的事件循环不能为NULL
 * @param[in] event_base 标识事件的事件库
 * @param[in] event_id 标识事件的事件id
 * @param[in] event_data 传递给处理程序的特定于事件发生的数据
 * @param[in] event_data_size 事件数据的大小
 * @param[in] ticks_to_wait 完整事件队列上要阻止的标记数
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_TIMEOUT：等待事件队列解除阻止的时间已过期，从ISR发布时队列已满
 *  -ESP_ERR_INVALID_ARG：事件基础和事件id的组合无效
 *  -其他：失败
 */
esp_err_t esp_event_post_to(esp_event_loop_handle_t event_loop,
                            esp_event_base_t event_base,
                            int32_t event_id,
                            void *event_data,
                            size_t event_data_size,
                            TickType_t ticks_to_wait);

#if CONFIG_ESP_EVENT_POST_FROM_ISR
/**
 * @brief esp_event_post的特殊变体，用于从中断处理程序发布事件。
 *
 * @param[in] event_base 标识事件的事件库
 * @param[in] event_id 标识事件的事件id
 * @param[in] event_data 传递给处理程序的特定于事件发生的数据
 * @param[in] event_data_size 事件数据的大小；最大值为4字节
 * @param[out] task_unblocked 可选参数（可以是NULL），其指示具有比当前运行任务更高优先级的事件任务已被发布的事件解除阻止；应该在中断存在之前请求上下文切换。
 *
 * @note 此功能仅在启用CONFIG_ESP_EVENT_POST_ROM_ISR时可用
 * @note 当从IRAM中的中断处理程序调用此函数时，也应通过启用CONFIG_ESP_EVENT_POST_ROM_RAM_ISR将此函数置于IRAM中
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：默认事件循环的事件队列已满
 *  -ESP_ERR_INVALID_ARG：事件基础和事件id的组合无效，数据大小超过4字节
 *  -其他：失败
 */
esp_err_t esp_event_isr_post(esp_event_base_t event_base,
                             int32_t event_id,
                             void *event_data,
                             size_t event_data_size,
                             BaseType_t *task_unblocked);

/**
 * @brief esp_event_post_to的特殊变体，用于从中断处理程序发布事件
 *
 * @param[in] event_loop 要发布到的事件循环不能为NULL
 * @param[in] event_base 标识事件的事件库
 * @param[in] event_id 标识事件的事件id
 * @param[in] event_data 传递给处理程序的特定于事件发生的数据
 * @param[in] event_data_size 事件数据的大小
 * @param[out] task_unblocked 可选参数（可以是NULL），其指示具有比当前运行任务更高优先级的事件任务已被发布的事件解除阻止；应该在中断存在之前请求上下文切换。
 *
 * @note 此功能仅在启用CONFIG_ESP_EVENT_POST_ROM_ISR时可用
 * @note 当从IRAM中的中断处理程序调用此函数时，也应通过启用CONFIG_ESP_EVENT_POST_ROM_RAM_ISR将此函数置于IRAM中
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_FAIL：循环已满的事件队列
 *  -ESP_ERR_INVALID_ARG：事件基础和事件id的组合无效，数据大小超过4字节
 *  -其他：失败
 */
esp_err_t esp_event_isr_post_to(esp_event_loop_handle_t event_loop,
                                esp_event_base_t event_base,
                                int32_t event_id,
                                void *event_data,
                                size_t event_data_size,
                                BaseType_t *task_unblocked);
#endif

/**
 * @brief 转储所有事件循环的统计信息。
 *
 * 以以下格式转储事件循环信息：
 *
 @逐字事件循环处理程序…事件循环处理处理程序。。。

  哪里：

   事件循环格式：address，name rx:total_recieved dr:total_dropped其中：address-事件循环的内存地址name-事件循环名称，如果没有专用任务total_receved，则为“none”-成功发布的事件总数total_dropped-由于队列已满而未成功发布的次数

   处理程序格式：address ev:base，id inv:total_invoked run:total_runtime其中：address-处理程序函数基的地址，id-由事件基指定的事件，以及此处理程序执行的id total_invoked-调用此处理程序的次数total_runtime-调用该处理程序所用的总时间

 @逐字结尾
 *
 * @param[in] file 要输出到的文件流
 *
 * @note 当CONFIG_ESP_EVENT_LOOP_ProfLING被禁用时，此函数为noop
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_NO_MEM:无法为事件循环列表分配内存
 *  -其他：失败
 */
esp_err_t esp_event_dump(FILE *file);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // #如果是ESP_EVENT_H_

