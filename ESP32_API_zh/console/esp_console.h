/*
 * SPDX文件版权文本：2016-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "sdkconfig.h"
#include "esp_err.h"

// 转发声明。linenoise/linenoise.h中的定义。
typedef struct linenoiseCompletions linenoiseCompletions;

/**
 * @brief 控制台初始化参数
 */
typedef struct {
    size_t max_cmdline_length;  //!< 命令行缓冲区的长度（字节）
    size_t max_cmdline_args;    //!< 要分析的命令行参数的最大数量
    int hint_color;             //!< 提示文本的ASCII颜色代码
    int hint_bold;              //!< 设置为1以粗体打印提示文本
} esp_console_config_t;

/**
 * @brief 默认控制台配置值
 *
 */
#define ESP_CONSOLE_CONFIG_DEFAULT() \
    {                                \
        .max_cmdline_length = 256,   \
        .max_cmdline_args = 32,      \
        .hint_color = 39,            \
        .hint_bold = 0               \
    }

/**
 * @brief 控制台REPL（读取评估打印循环）的参数
 *
 */
typedef struct {
    uint32_t max_history_len;      //!< 历史记录的最大长度
    const char *history_save_path; //!< 用于保存历史命令的文件路径，设置为NULL不会保存到文件系统
    uint32_t task_stack_size;      //!< repl任务堆栈大小
    uint32_t task_priority;        //!< repl任务优先级
    const char *prompt;            //!< 提示（NULL表示默认值：“esp>”）
    size_t max_cmdline_length;     //!< 命令行的最大长度。如果为0，将使用默认值
} esp_console_repl_config_t;

/**
 * @brief 默认控制台repl配置值
 *
 */
#define ESP_CONSOLE_REPL_CONFIG_DEFAULT() \
{                                         \
        .max_history_len = 32,            \
        .history_save_path = NULL,        \
        .task_stack_size = 4096,          \
        .task_priority = 2,               \
        .prompt = NULL,                   \
        .max_cmdline_length = 0,          \
}

/**
 * @brief 控制台设备参数：UART
 *
 */
typedef struct {
    int channel;     //!< UART信道号（从零开始计数）
    int baud_rate;   //!< 通信波特率
    int tx_gpio_num; //!< TX路径的GPIO编号，-1表示使用默认值
    int rx_gpio_num; //!< RX路径的GPIO编号，-1表示使用默认值
} esp_console_dev_uart_config_t;

#ifdef CONFIG_ESP_CONSOLE_UART_CUSTOM
#define ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT()       \
{                                                   \
    .channel = CONFIG_ESP_CONSOLE_UART_NUM,         \
    .baud_rate = CONFIG_ESP_CONSOLE_UART_BAUDRATE,  \
    .tx_gpio_num = CONFIG_ESP_CONSOLE_UART_TX_GPIO, \
    .rx_gpio_num = CONFIG_ESP_CONSOLE_UART_RX_GPIO, \
}
#else
#define ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT()      \
{                                                  \
    .channel = CONFIG_ESP_CONSOLE_UART_NUM,        \
    .baud_rate = CONFIG_ESP_CONSOLE_UART_BAUDRATE, \
    .tx_gpio_num = -1,                             \
    .rx_gpio_num = -1,                             \
}
#endif

/**
 * @brief 控制台设备参数：USB CDC
 *
 * @note 现在这是一个空的结构，留给未来
 *
 */
typedef struct {

} esp_console_dev_usb_cdc_config_t;

#define ESP_CONSOLE_DEV_CDC_CONFIG_DEFAULT() \
{                                            \
}

#if CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG
/**
 * @brief 控制台设备参数：USB-SRIAL-JTAG
 *
 * @note 现在这是一个空的结构，留给未来
 *
 */
typedef struct {

} esp_console_dev_usb_serial_jtag_config_t;

#define ESP_CONSOLE_DEV_USB_SERIAL_JTAG_CONFIG_DEFAULT() {}

#endif // CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG

/**
 * @brief 初始化控制台模块
 * @param config 控制台配置
 * @note  在使用其他控制台模块功能之前调用一次
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_NO_MEM（如果内存不足）
 *      -ESP_ERR_INVALID_STATE（如果已初始化）
 *      -如果配置无效，则为ESP_ERR_INVALID_ARG
 */
esp_err_t esp_console_init(const esp_console_config_t *config);

/**
 * @brief 取消初始化控制台模块
 * @note  使用控制台模块功能完成后调用一次
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_INVALID_STATE（如果尚未初始化）
 */
esp_err_t esp_console_deinit(void);

/**
 * @brief 控制台命令主功能
 * @param argc 参数的数量
 * @param argv 带有argc项的数组，每个项都指向以零结尾的字符串参数
 * @return 控制台命令返回代码，0表示“成功”
 */
typedef int (*esp_console_cmd_func_t)(int argc, char **argv);

/**
 * @brief 控制台命令说明
 */
typedef struct {
    /**
     * 命令名称。不能为NULL，不能包含空格。在调用esp_console_init之前，指针必须有效。
     */
    const char *command;
    /**
     * 命令的帮助文本，由Help命令显示。如果设置，指针必须在调用esp_console_init之前有效。如果未设置，命令将不会在“help”输出中列出。
     */
    const char *help;
    /**
     * 提示文本，通常列出可能的参数。如果设置为NULL，并且“argtable”字段为非NULL，则将自动生成提示
     */
    const char *hint;
    /**
     * 指向实现命令的函数的指针。
     */
    esp_console_cmd_func_t func;
    /**
     * 指向arg_xxx结构的指针数组或结构可能为NULL。用于在'hint'设置为NULL时生成提示文本。此字段指向的数组/结构必须以arg_end结尾。仅用于esp_console_cmd_register调用的持续时间。
     */
    void *argtable;
} esp_console_cmd_t;

/**
 * @brief 注册控制台命令
 * @param cmd 指向命令描述的指针；可以指向临时值
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_NO_MEM（如果内存不足）
 *      -如果命令描述包含无效参数，则为ESP_ERR_INVALID_ARG
 */
esp_err_t esp_console_cmd_register(const esp_console_cmd_t *cmd);

/**
 * @brief 运行命令行
 * @param cmdline 命令行（命令名后跟多个参数）
 * @param[out] cmd_ret 命令的返回代码（如果运行命令则设置）
 * @return
 *      -ESP_OK，如果命令已运行
 *      -如果命令行为空或仅包含空格，则返回ESP_ERR_INVALID_ARG
 *      -如果未注册具有给定名称的命令，则返回ESP_ERR_NOT_FOUND
 *      -如果未调用ESP_console_init，则返回ESP_ERR_INVALID_STATE
 */
esp_err_t esp_console_run(const char *cmdline, int *cmd_ret);

/**
 * @brief 将命令行就地拆分为参数
 * @verbatim
 * -此函数在给定的输入行中查找空格分隔的参数。
 *
 *     “abc定义1 20.3”->[“abc”，“def”，“1”，“20”，“.3”]
 *
 * -包含空格的参数可以用引号括起来。在这种情况下，保留空格并去掉引号。
 *
 *     'abc“123 456”def'->['abc'，'123 456'，'def']
 *
 * -转义序列可用于产生反斜杠、双引号和空格：
 *
 *     'a\b\\c\“'->['a b\c”']
 * @endverbatim
 * @note argv数组中最多返回argv_size-1个参数的指针。最后一个指针（即argv[argc]）之后的指针设置为NULL。
 *
 * @param line 指向要解析的缓冲区的指针；它被修改了
 * @param argv 写入参数指针的数组
 * @param argv_size argv_array中的元素数（最大参数数）
 * @return 找到的参数数（argc）
 */
size_t esp_console_split_argv(char *line, char **argv, size_t argv_size);

/**
 * @brief 为linenoise库提供命令完成的回调
 *
 * 当使用linenoise进行行编辑时，可以像这样启用命令完成支持：
 *
 *   linenoiseSetCompletionCallback（&esp_console_get_completion）；
 *
 * @param buf 用户键入的字符串
 * @param lc linenoise要填写的完成
 */
void esp_console_get_completion(const char *buf, linenoiseCompletions *lc);

/**
 * @brief 为linenoise库提供命令提示的回调
 *
 * 使用linenoise进行行编辑时，可以按如下方式启用提示支持：
 *
 *   linenoiseSetHintsCallback（（linenoiseHintsCallback*）&esp_console_get_hint）；
 *
 * 需要额外的强制转换，因为linenoiseHintsCallback被定义为返回一个字符而不是常量字符。
 *
 * @param buf 用户键入的行
 * @param[out] color 显示提示时使用的ANSI颜色代码
 * @param[out] bold 如果提示必须以粗体显示，则设置为1
 * @return 包含提示文本的字符串。此字符串是持久的，不应释放（即不应使用linenoiseSetFreeHintsCallback）。
 */
const char *esp_console_get_hint(const char *buf, int *color, int *bold);

/**
 * @brief 注册“help”命令
 *
 * 默认“help”命令打印已注册命令的列表以及提示和帮助字符串。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果未调用ESP_console_init，则返回ESP_ERR_INVALID_STATE
 */
esp_err_t esp_console_register_help_command(void);

/******************************************************************************
 *              控制台REPL
 ******************************************************************************/

/**
 * @brief 为控制台REPL定义的类型
 *
 */
typedef struct esp_console_repl_s esp_console_repl_t;

/**
 * @brief 控制台REPL基础结构
 *
 */
struct esp_console_repl_s {
    /**
     * @brief 删除控制台REPL环境
     * @param[in] repl 从esp_console_new_REPL_xxx@return返回REPL句柄
     *      -成功时ESP_OK
     *      -ESP_FAIL出现错误
     */
    esp_err_t (*del)(esp_console_repl_t *repl);
};

/**
 * @brief 通过UART驱动程序建立控制台REPL环境
 *
 * @param[in] dev_config UART设备配置
 * @param[in] repl_config REPL配置
 * @param[out] ret_repl 初始化成功后返回REPL句柄，否则返回NULL
 *
 * @note 这是一个建立REPL所需环境的一体化功能，包括：
 *       -在控制台UART（8n1，115200，REF_TICK时钟源）上安装UART驱动程序
 *       -配置stdin/stdout以通过UART驱动程序
 *       -初始化线路噪声
 *       -生成新线程以在后台运行REPL
 *
 * @attention 此函数用于示例中，以使代码更紧凑。使用控制台功能的应用程序应基于底层linenoise和esp_console函数。
 *
 * @return
 *      -成功时ESP_OK
 *      -ESP_FAIL参数错误
 */
esp_err_t esp_console_new_repl_uart(const esp_console_dev_uart_config_t *dev_config, const esp_console_repl_config_t *repl_config, esp_console_repl_t **ret_repl);

/**
 * @brief 通过USB CDC建立控制台REPL环境
 *
 * @param[in] dev_config USB CDC配置
 * @param[in] repl_config REPL配置
 * @param[out] ret_repl 初始化成功后返回REPL句柄，否则返回NULL
 *
 * @note 这是一个建立REPL所需环境的一体化功能，包括：
 *       -初始化线路噪声
 *       -生成新线程以在后台运行REPL
 *
 * @attention 此函数用于示例中，以使代码更紧凑。使用控制台功能的应用程序应基于底层linenoise和esp_console函数。
 *
 * @return
 *      -成功时ESP_OK
 *      -ESP_FAIL参数错误
 */
esp_err_t esp_console_new_repl_usb_cdc(const esp_console_dev_usb_cdc_config_t *dev_config, const esp_console_repl_config_t *repl_config, esp_console_repl_t **ret_repl);

#if CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG
/**
 * @brief 通过USB-SRIAL-JTAG建立控制台REPL（读取评估打印循环）环境
 *
 * @param[in] dev_config USB-SRIAL-JTAG配置
 * @param[in] repl_config REPL配置
 * @param[out] ret_repl 初始化成功后返回REPL句柄，否则返回NULL
 *
 * @note 这是一个建立REPL所需环境的一体化功能，包括：
 *       -初始化线路噪声
 *       -生成新线程以在后台运行REPL
 *
 * @attention 此函数用于示例中，以使代码更紧凑。使用控制台功能的应用程序应基于底层linenoise和esp_console函数。
 *
 * @return
 *      -成功时ESP_OK
 *      -ESP_FAIL参数错误
 */
esp_err_t esp_console_new_repl_usb_serial_jtag(const esp_console_dev_usb_serial_jtag_config_t *dev_config, const esp_console_repl_config_t *repl_config, esp_console_repl_t **ret_repl);
#endif // CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG

/**
 * @brief 启动REPL环境
 * @param[in] repl 从esp_console_new_REPL_xxx返回REPL句柄
 * @note 一旦REPL启动，它将不会停止，直到用户调用REPL->del（REPL）来销毁REPL环境。
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_INVALID_STATE，如果复制已启动
 */
esp_err_t esp_console_start_repl(esp_console_repl_t *repl);

#ifdef __cplusplus
}
#endif

