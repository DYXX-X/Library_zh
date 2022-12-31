// 版权所有2018 Espressif Systems（上海）私人有限公司
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
//
// 此头文件基于的termios头
// “单一UNIX（r）规范，第2版，版权所有（c）1997 The Open Group”。

#ifndef __ESP_SYS_TERMIOS_H__
#define __ESP_SYS_TERMIOS_H__

// ESP-IDF注意：此标头仅为sys/termios.h中定义的宏和函数提供一个兼容层。
// 并非所有的ESP-IDF都有明确的含义（例如，流程负责人ID），因此很可能会被淘汰
// 在实际实现中。


#include <stdint.h>
#include <sys/types.h>
#include "sdkconfig.h"

#ifdef CONFIG_VFS_SUPPORT_TERMIOS

// 数组c_cc的下标：
#define VEOF                        0           /**EOF字符*/
#define VEOL                        1           /**EOL字符*/
#define VERASE                      2           /**ERASE字符*/
#define VINTR                       3           /**INTR字符*/
#define VKILL                       4           /**KILL字符*/
#define VMIN                        5           /**MIN值*/
#define VQUIT                       6           /**QUIT字符*/
#define VSTART                      7           /**START字符*/
#define VSTOP                       8           /**STOP字符*/
#define VSUSP                       9           /**SUSP字符*/
#define VTIME                      10           /**TIME值*/
#define NCCS                       (VTIME + 1)  /**控制字符数组c_cc的大小*/

// 用作c_iflag字段中标志的输入模式
#define BRKINT      (1u << 0)       /**休息时信号中断。*/
#define ICRNL       (1u << 1)       /**输入时将CR映射到NL。*/
#define IGNBRK      (1u << 2)       /**忽略中断条件。*/
#define IGNCR       (1u << 3)       /**忽略CR。*/
#define IGNPAR      (1u << 4)       /**忽略具有奇偶校验错误的字符。*/
#define INLCR       (1u << 5)       /**输入时将NL映射到CR。*/
#define INPCK       (1u << 6)       /**启用输入奇偶校验。*/
#define ISTRIP      (1u << 7)       /**剥离字符。*/
#define IUCLC       (1u << 8)       /**输入时将大写字母映射到小写字母（LEGACY）。*/
#define IXANY       (1u << 9)       /**启用任何字符以重新启动输出。*/
#define IXOFF       (1u << 10)      /**启用启动/停止输入控制。*/
#define IXON        (1u << 11)      /**启用启动/停止输出控制。*/
#define PARMRK      (1u << 12)      /**标记奇偶校验错误。*/

// 输出模式，用作c_ofag字段中的标志
#define OPOST       (1u <<  0)       /**后处理输出*/
#define OLCUC       (1u <<  1)       /**将输出上的小写字母映射到大写字母（LEGACY）。*/
#define ONLCR       (1u <<  2)       /**将NL映射到输出上的CR-NL。*/
#define OCRNL       (1u <<  3)       /**将输出上的CR映射到NL。*/
#define ONOCR       (1u <<  4)       /**第0列无CR输出。*/
#define ONLRET      (1u <<  5)       /**NL执行CR功能。*/
#define OFILL       (1u <<  6)       /**使用填充字符表示延迟。*/
#define NLDLY       (1u <<  7)       /**选择换行延迟：*/
#define   NL0       (0u <<  7)       /**换行符类型0。*/
#define   NL1       (1u <<  7)       /**换行符类型1。*/
#define CRDLY       (3u <<  8)       /**选择回车延迟：*/
#define   CR0       (0u <<  8)       /**回车延迟类型0。*/
#define   CR1       (1u <<  8)       /**回车延迟类型1。*/
#define   CR2       (2u <<  8)       /**回车延迟类型2。*/
#define   CR3       (3u <<  8)       /**回车延迟类型3。*/
#define TABDLY      (3u << 10)       /**选择水平选项卡延迟：*/
#define   TAB0      (0u << 10)       /**水平标签延迟类型0。*/
#define   TAB1      (1u << 10)       /**水平标签延迟类型1。*/
#define   TAB2      (2u << 10)       /**水平标签延迟类型2。*/
#define   TAB3      (3u << 10)       /**将选项卡展开到空格。*/
#define BSDLY       (1u << 12)       /**选择退格延迟：*/
#define   BS0       (0u << 12)       /**退格延迟类型0。*/
#define   BS1       (1u << 12)       /**退格延迟类型1。*/
#define VTDLY       (1u << 13)       /**选择垂直选项卡延迟：*/
#define   VT0       (0u << 13)       /**垂直标签延迟类型0。*/
#define   VT1       (1u << 13)       /**垂直标签延迟类型1。*/
#define FFDLY       (1u << 14)       /**选择表单馈送延迟：*/
#define   FF0       (0u << 14)       /**表单馈送延迟类型0。*/
#define   FF1       (1u << 14)       /**表单馈送延迟类型1。*/

// 波特率选择。speed_t类型对象的有效值：
// CBAUD范围B0-B38400
#define B0          0   /**挂断*/
#define B50         1
#define B75         2
#define B110        3
#define B134        4
#define B150        5
#define B200        6
#define B300        7
#define B600        8
#define B1200       9
#define B1800      10
#define B2400      11
#define B4800      12
#define B9600      13
#define B19200     14
#define B38400     15
// CBAUDEX范围B57600-B4000000
#define B57600     16
#define B115200    17
#define B230400    18
#define B460800    19
#define B500000    20
#define B576000    21
#define B921600    22
#define B1000000   23
#define B1152000   24
#define B1500000   25
#define B2000000   26
#define B2500000   27
#define B3000000   28
#define B3500000   29
#define B4000000   30

// c_cflag字段的控制模式：
#define CSIZE      (3u << 0)        /* 字符大小：*/
#define   CS5      (0u << 0)        /**5位。*/
#define   CS6      (1u << 0)        /**6位。*/
#define   CS7      (2u << 0)        /**7位。*/
#define   CS8      (3u << 0)        /**8位。*/
#define CSTOPB     (1u << 2)        /**发送两个停止位，另一个。*/
#define CREAD      (1u << 3)        /**启用接收器。*/
#define PARENB     (1u << 4)        /**奇偶校验启用。*/
#define PARODD     (1u << 5)        /**奇数奇偶校验，否则为偶数。*/
#define HUPCL      (1u << 6)        /**挂断最后一关。*/
#define CLOCAL     (1u << 7)        /**忽略调制解调器状态行。*/
#define CBAUD      (1u << 8)        /**使用B0-B38400宏定义的波特率。*/
#define CBAUDEX    (1u << 9)        /**使用B57600-B4000000宏定义的波特率。*/
#define BOTHER     (1u << 10)       /**使用自定义波特率*/

// lflag字段的本地模式（_L）：
#define ECHO       (1u << 0)        /**启用回声。*/
#define ECHOE      (1u << 1)        /**回显擦除字符作为纠错退格。*/
#define ECHOK      (1u << 2)        /**回声杀手。*/
#define ECHONL     (1u << 3)        /**回声NL。*/
#define ICANON     (1u << 4)        /**标准输入（擦除和终止处理）。*/
#define IEXTEN     (1u << 5)        /**启用扩展输入字符处理。*/
#define ISIG       (1u << 6)        /**启用信号。*/
#define NOFLSH     (1u << 7)        /**中断或退出后禁用刷新。*/
#define TOSTOP     (1u << 8)        /**发送SIGTTOU进行后台输出。*/
#define XCASE      (1u << 9)        /**标准上/下展示（LEGACY）。*/

// 用于tcsetattr（）的属性选择常量：
#define TCSANOW    0                /**立即更改属性。*/
#define TCSADRAIN  1                /**输出耗尽时更改属性。*/
#define TCSAFLUSH  2                /**输出耗尽时更改属性；也刷新挂起的输入。*/

// 用于tcflush（）的线路控制常数：
#define TCIFLUSH    0               /**刷新挂起的输入。刷新未发送的输出。*/
#define TCIOFLUSH   1               /**刷新挂起的输入和未发送的输出。*/
#define TCOFLUSH    2               /**刷新未发送的输出。*/

// 用于tcflow（）的常量：
#define TCIOFF      0               /**发送STOP字符，用于暂停输入数据。*/
#define TCION       1               /**发送一个START字符，用于重新启动输入数据。*/
#define TCOOFF      2               /**挂起输出。*/
#define TCOON       3               /**重新启动输出。*/

typedef uint8_t cc_t;
typedef uint32_t speed_t;
typedef uint16_t tcflag_t;

struct termios
{
    tcflag_t c_iflag;    /**输入模式*/
    tcflag_t c_oflag;    /**输出模式*/
    tcflag_t c_cflag;    /**控制模式*/
    tcflag_t c_lflag;    /**本地模式*/
    cc_t     c_cc[NCCS]; /**控制字符*/
    speed_t  c_ispeed;   /**输入波特率*/
    speed_t  c_ospeed;   /**输出波特率*/
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 从输入结构中精确提取输入波特率（无需解释）。
 *
 * @param p 输入端结构
 * @return 输入波特率
 */
speed_t cfgetispeed(const struct termios *p);

/**
 * @brief 从输入结构中精确提取输出波特率（无需解释）。
 *
 * @param p 输入端结构
 * @return 输出波特率
 */
speed_t cfgetospeed(const struct termios *p);

/**
 * @brief 在终端结构中设置输入波特率
 *
 * 在随后调用tcsetttr（）之前，硬件不会产生任何影响。
 *
 * @param p 输入端结构
 * @param sp 输入波特率
 * @return 成功时为0，否则为-1，并设置errno
 */
int cfsetispeed(struct termios *p, speed_t sp);

/**
 * @brief 在termios结构中设置输出波特率
 *
 * 在随后调用tcsetttr（）之前，硬件不会产生任何影响。
 *
 * @param p 输入端结构
 * @param sp 输出波特率
 * @return 成功时为0，否则为-1，并设置errno
 */
int cfsetospeed(struct termios *p, speed_t sp);

/**
 * @brief 等待输出传输
 *
 * @param fd 终端的文件描述符
 * @return 成功时为0，否则为-1，并设置errno
 */
int tcdrain(int fd);

/**
 * @brief 暂停或重新启动数据传输或接收
 *
 * @param fd 终端的文件描述符
 * @param action 选择要执行的操作
 * @return 成功时为0，否则为-1，并设置errno
 */
int tcflow(int fd, int action);

/**
 * @brief 刷新未传输的输出数据和未读取的输入数据
 *
 * @param fd 终端的文件描述符
 * @param select 选择应该刷新的内容
 * @return 成功时为0，否则为-1，并设置errno
 */
int tcflush(int fd, int select);

/**
 * @brief 获取终端的参数
 *
 * @param fd 终端的文件描述符
 * @param p 输出端结构
 * @return 成功时为0，否则为-1，并设置errno
 */
int tcgetattr(int fd, struct termios *p);

/**
 * @brief 获取控制终端会话负责人的进程组ID
 *
 * @param fd 终端的文件描述符
 * @return 成功时为进程组ID，否则为-1，并设置errno
 */
pid_t tcgetsid(int fd);

/**
 * @brief 发送特定持续时间的休息
 *
 * @param fd 终端的文件描述符
 * @param duration 中断持续时间
 * @return 成功时为0，否则为-1，并设置errno
 */
int tcsendbreak(int fd, int duration);

/**
 * @brief 设置终端的参数
 *
 * @param fd 终端的文件描述符
 * @param optional_actions 可选操作
 * @param p 输入端结构
 * @return 成功时为0，否则为-1，并设置errno
 */
int tcsetattr(int fd, int optional_actions, const struct termios *p);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // CONFIG_VFS_SUPPORT_TERMIOS

#endif //__ESP_SYS_TERMIOS_H__

