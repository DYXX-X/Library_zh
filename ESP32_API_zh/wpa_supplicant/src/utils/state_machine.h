/*
 * wpa_suppliant/hostapd-状态机定义版权所有（c）2002-2005，Jouni Malinen<j@w1.fi>
 *
 * 此软件可以根据BSD许可证的条款进行分发。有关详细信息，请参阅自述文件。
 *
 * 此文件包含一组可用于实现状态机的预处理器宏。除了包含此头文件之外，实现状态机的每个文件必须将state_machine_DATA定义为包含状态变量（enum machine_state，Boolean changed）的数据结构，将state_MAC HINE_DEBUG_PREFIX定义为用作所有调试消息前缀的字符串。如果SM_ENTRY_MA宏用于定义一组具有共享数据结构的状态机，则需要定义state_MACHINE_ADDR以指向调试输出中使用的MAC地址。SM_ENTRY_M宏可用于定义类似的状态机组，而无需额外的调试信息。
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

/**
 * SM_STATE-状态机函数的声明
 * @machine: 状态机名称
 * @state: 状态机状态
 *
 * 此宏用于声明状态机函数。它用来代替C函数定义，在通过调用SM_ENTER或SM_ENTER_GLOBAL进入状态时声明要运行的函数。
 */
#define SM_STATE(machine, state) \
static void sm_ ## machine ## _ ## state ## _Enter(STATE_MACHINE_DATA *sm, \
	int global)

/**
 * SM_ENTRY-状态机功能入口点
 * @machine: 状态机名称
 * @state: 状态机状态
 *
 * 此宏用于使用SM_state声明的每个状态机函数中。SM_ENTRY应该在函数体的开头，但在声明可能的局部变量之后。此宏打印有关状态转换的调试信息并更新状态机状态。
 */
#define SM_ENTRY(machine, state) \
if (!global || sm->machine ## _state != machine ## _ ## state) { \
	sm->changed = TRUE; \
	wpa_printf(MSG_DEBUG, STATE_MACHINE_DEBUG_PREFIX ": " #machine \
		   " entering state " #state); \
} \
sm->machine ## _state = machine ## _ ## state;

/**
 * SM_ENTRY_M-状态机组的状态机函数入口点
 * @machine: 状态机名称
 * @_state: 状态机状态
 * @data: 状态变量前缀（完整变量：prefix_State）
 *
 * 此宏类似于SM_ENTRY，但适用于为多个状态机使用共享数据结构的状态机组。机器和前缀参数都设置为“子状态机”名称。前缀用于允许在同一数据结构中存储多个状态变量。
 */
#define SM_ENTRY_M(machine, _state, data) \
if (!global || sm->data ## _ ## state != machine ## _ ## _state) { \
	sm->changed = TRUE; \
	wpa_printf(MSG_DEBUG, STATE_MACHINE_DEBUG_PREFIX ": " \
		   #machine " entering state " #_state); \
} \
sm->data ## _ ## state = machine ## _ ## _state;

/**
 * SM_ENTRY_MA-状态机组的状态机函数入口点
 * @machine: 状态机名称
 * @_state: 状态机状态
 * @data: 状态变量前缀（完整变量：prefix_State）
 *
 * 此宏类似于SM_ENTRY_M，但调试输出中包含MAC地址。STATE_MACHINE_ADDR必须定义为指向要包含在调试中的MAC地址。
 */
#define SM_ENTRY_MA(machine, _state, data) \
if (!global || sm->data ## _ ## state != machine ## _ ## _state) { \
	sm->changed = TRUE; \
	wpa_printf(MSG_DEBUG, STATE_MACHINE_DEBUG_PREFIX ": " MACSTR " " \
		   #machine " entering state " #_state"\n", \
		   MAC2STR(STATE_MACHINE_ADDR)); \
} \
sm->data ## _ ## state = machine ## _ ## _state;

/**
 * SM_ENTER-输入新的状态机状态
 * @machine: 状态机名称
 * @state: 状态机状态
 *
 * 此宏扩展为对使用SM_state宏定义的状态机函数的函数调用。SM_ENTER用于状态机步进函数，以将状态机移动到新状态。
 */
#define SM_ENTER(machine, state) \
sm_ ## machine ## _ ## state ## _Enter(sm, 0)

/**
 * SM_ENTER_GLOBAL-根据全局规则输入新的状态机状态
 * @machine: 状态机名称
 * @state: 状态机状态
 *
 * 此宏类似于SM_ENTER，但它在基于全局（不特定于任何特定状态）规则进入新状态时使用。当相同的全局规则强制状态机保持打开状态时，使用单独的宏来避免不必要的调试消息泛滥。
 */
#define SM_ENTER_GLOBAL(machine, state) \
sm_ ## machine ## _ ## state ## _Enter(sm, 1)

/**
 * SM_STEP-状态机步进函数的声明
 * @machine: 状态机名称
 *
 * 此宏用于声明状态机步骤函数。它用来代替C函数定义来声明一个函数，该函数用于根据状态变量将状态机移动到新状态。此函数使用SM_ENTER和SM_ENTER_GLOBAL宏进入新状态。
 */
#define SM_STEP(machine) \
static void sm_ ## machine ## _Step(STATE_MACHINE_DATA *sm)

/**
 * SM_STEP_RUN-调用状态机步骤函数
 * @machine: 状态机名称
 *
 * 此宏扩展为对使用SM_step宏定义的状态机步骤函数的函数调用。
 */
#define SM_STEP_RUN(machine) sm_ ## machine ## _Step(sm)

#endif /* STATE_MACHINE_H */

