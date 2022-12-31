/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */


/**
 * @addtogroup HAL @{
 *   @defgroup HALGpio HAL GPIO公司@{
 */

#ifndef H_HAL_GPIO_
#define H_HAL_GPIO_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * gpio的“模式”。gpio要么是输入，要么是输出，要么是“未连接”（指定的引脚不起gpio的作用）
 */
enum hal_gpio_mode_e {
    /**未连接*/
    HAL_GPIO_MODE_NC = -1,
    /**输入*/
    HAL_GPIO_MODE_IN = 0,
    /**输出*/
    HAL_GPIO_MODE_OUT = 1
};
typedef enum hal_gpio_mode_e hal_gpio_mode_t;

/*
 * gpio的“拉力”。这是输入或输出。
 */
enum hal_gpio_pull {
    /**上拉/下拉未启用*/
    HAL_GPIO_PULL_NONE = 0,
    /**已启用上拉*/
    HAL_GPIO_PULL_UP = 1,
    /**已启用下拉*/
    HAL_GPIO_PULL_DOWN = 2
};
typedef enum hal_gpio_pull hal_gpio_pull_t;

/*
 * IRQ触发器类型。
 */
enum hal_gpio_irq_trigger {
    HAL_GPIO_TRIG_NONE = 0,
    /**IRQ出现在上升沿*/
    HAL_GPIO_TRIG_RISING = 1,
    /**IRQ发生在下降沿*/
    HAL_GPIO_TRIG_FALLING = 2,
    /**IRQ出现在任一边缘*/
    HAL_GPIO_TRIG_BOTH = 3,
    /**线路低时出现IRQ*/
    HAL_GPIO_TRIG_LOW = 4,
    /**线路高时出现IRQ*/
    HAL_GPIO_TRIG_HIGH = 5
};
typedef enum hal_gpio_irq_trigger hal_gpio_irq_trig_t;

/* GPIO irq处理器函数的函数原型*/
typedef void (*hal_gpio_irq_handler_t)(void *arg);

/**
 * 将指定的管脚初始化为输入
 *
 * @param pin   要设置为输入的引脚号
 * @param pull  拉力式
 *
 * @return int 0：无错误-否则为1。
 */
int hal_gpio_init_in(int pin, hal_gpio_pull_t pull);

/**
 * 将指定的管脚初始化为输出，将管脚设置为指定值。
 *
 * @param pin 要设置为输出的引脚号
 * @param val 设置引脚的值
 *
 * @return int 0：无错误-否则为1。
 */
int hal_gpio_init_out(int pin, int val);

/**
 * 取消初始化指定的管脚以恢复先前的初始化
 *
 * @param pin 要取消设置的端号
 *
 * @return int 0：无错误-否则为1。
 */
int hal_gpio_deinit(int pin);

/**
 * 将值（高或低）写入指定引脚。
 *
 * @param pin 要设置的引脚
 * @param val 设置引脚的值（0：低1：高）
 */
void hal_gpio_write(int pin, int val);

/**
 * 读取指定的引脚。
 *
 * @param pin 要读取的引脚号
 *
 * @return int 0：低，1：高
 */
int hal_gpio_read(int pin);

/**
 * 切换指定的接点
 *
 * @param pin 要切换的端号
 *
 * @return 当前gpio状态int 0：低，1：高
 */
int hal_gpio_toggle(int pin);

/**
 * 初始化给定引脚以触发GPIO IRQ回调。
 *
 * @param pin     触发GPIO中断的引脚
 * @param handler 要调用的处理程序函数
 * @param arg     要提供给IRQ处理程序的参数
 * @param trig    触发模式（例如上升、下降）
 * @param pull    引脚的模式（例如，上拉、下拉）
 *
 * @return 成功时为0，失败时为非零错误代码。
 */
int hal_gpio_irq_init(int pin, hal_gpio_irq_handler_t handler, void *arg,
                      hal_gpio_irq_trig_t trig, hal_gpio_pull_t pull);

/**
 * 释放一个引脚，使其不被配置为在状态改变时触发IRQ。
 *
 * @param pin 要释放的销
 */
void hal_gpio_irq_release(int pin);

/**
 * 在通过的引脚上启用IRQ
 *
 * @param pin 启用IRQ的引脚
 */
void hal_gpio_irq_enable(int pin);

/**
 * 禁用通过引脚上的IRQ
 *
 * @param pin 禁用IRQ的引脚
 */
void hal_gpio_irq_disable(int pin);


#ifdef __cplusplus
}
#endif

#endif /* H_HAL_GPIO_ */

/**
 *   @} 哈尔格皮奥
 * @} HAL
 */

