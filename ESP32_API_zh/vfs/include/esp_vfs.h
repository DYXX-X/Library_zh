/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __ESP_VFS_H__
#define __ESP_VFS_H__

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>
#include <utime.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include <sys/types.h>
#include <sys/reent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/termios.h>
#include <sys/poll.h>
#include <sys/dirent.h>
#include <string.h>
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SYS_TYPES_FD_SET
#error "VFS should be used with FD_SETSIZE and FD_SET from sys/types.h"
#endif

/**
 * （全局）文件描述符的最大数量。
 */
#define MAX_FDS         FD_SETSIZE /* 要与fd_set和select（）兼容*/

/**
 * 路径前缀的最大长度（不包括零终止符）
 */
#define ESP_VFS_PATH_MAX 15

/**
 * esp_vfs_t结构中标志成员的默认值。
 */
#define ESP_VFS_FLAG_DEFAULT        0

/**
 * 指示FS在系统调用中需要额外上下文指针的标志。
 */
#define ESP_VFS_FLAG_CONTEXT_PTR    1

/*
 * @brief 用于esp_VFS_register_with_id（）的VFS标识符
 */
typedef int esp_vfs_id_t;

/**
 * @brief select（）的VFS信号量类型
 *
 */
typedef struct
{
    bool is_sem_local;      /*!< 当为true时，“sem”的类型为SemaphoreHandle_t，否则由套接字驱动程序定义*/
    void *sem;              /*!< 信号量实例*/
} esp_vfs_select_sem_t;

/**
 * @brief VFS定义结构
 *
 * 该结构应填充指向相应FS驱动程序函数的指针。
 *
 * VFS组件将转换所有FD，以便文件系统实现看到它们从零开始。调用方看到一个全局FD，其前缀是预文件系统实现。
 *
 * 一些FS实现期望某些状态（例如指向某个结构的指针）作为第一个参数传入。对于这些实现，填充具有_p后缀的此结构的成员，将标志成员设置为ESP_VFS_FLAG_CONTEXT_PTR，并提供ESP_VFS_register函数的上下文指针。如果实现不使用此额外参数，则填充不带_p后缀的成员，并将flags成员设置为ESP_VFS_FLAG_DEFAULT。
 *
 * 如果FS驱动程序不提供某些函数，请将相应的成员设置为NULL。
 */
typedef struct
{
    int flags;      /*!< ESP_VFS_FLAG_CONTEXT_PTR或ESP_VFS-FLAG_DEFAULT*/
    union {
        ssize_t (*write_p)(void* p, int fd, const void * data, size_t size);                         /*!< 使用上下文指针写入*/
        ssize_t (*write)(int fd, const void * data, size_t size);                                    /*!< 无上下文指针写入*/
    };
    union {
        off_t (*lseek_p)(void* p, int fd, off_t size, int mode);                                     /*!< 使用上下文指针查找*/
        off_t (*lseek)(int fd, off_t size, int mode);                                                /*!< 无上下文指针的查找*/
    };
    union {
        ssize_t (*read_p)(void* ctx, int fd, void * dst, size_t size);                               /*!< 使用上下文指针读取*/
        ssize_t (*read)(int fd, void * dst, size_t size);                                            /*!< 无上下文指针读取*/
    };
    union {
        ssize_t (*pread_p)(void *ctx, int fd, void * dst, size_t size, off_t offset);                /*!< 带上下文指针的pread*/
        ssize_t (*pread)(int fd, void * dst, size_t size, off_t offset);                             /*!< 无上下文指针的pread*/
    };
    union {
        ssize_t (*pwrite_p)(void *ctx, int fd, const void *src, size_t size, off_t offset);          /*!< 带有上下文指针的pwrite*/
        ssize_t (*pwrite)(int fd, const void *src, size_t size, off_t offset);                       /*!< 无上下文指针的pwrite*/
    };
    union {
        int (*open_p)(void* ctx, const char * path, int flags, int mode);                            /*!< 使用上下文指针打开*/
        int (*open)(const char * path, int flags, int mode);                                         /*!< 无上下文指针打开*/
    };
    union {
        int (*close_p)(void* ctx, int fd);                                                           /*!< 用上下文指针关闭*/
        int (*close)(int fd);                                                                        /*!< 无上下文指针关闭*/
    };
    union {
        int (*fstat_p)(void* ctx, int fd, struct stat * st);                                         /*!< 带上下文指针的fstat*/
        int (*fstat)(int fd, struct stat * st);                                                      /*!< 无上下文指针的fstat*/
    };
#ifdef CONFIG_VFS_SUPPORT_DIR
    union {
        int (*stat_p)(void* ctx, const char * path, struct stat * st);                               /*!< 带上下文指针的stat*/
        int (*stat)(const char * path, struct stat * st);                                            /*!< 无上下文指针的stat*/
    };
    union {
        int (*link_p)(void* ctx, const char* n1, const char* n2);                                    /*!< 带有上下文指针的链接*/
        int (*link)(const char* n1, const char* n2);                                                 /*!< 无上下文指针的链接*/
    };
    union {
        int (*unlink_p)(void* ctx, const char *path);                                                /*!< 取消与上下文指针的链接*/
        int (*unlink)(const char *path);                                                             /*!< 无上下文指针取消链接*/
    };
    union {
        int (*rename_p)(void* ctx, const char *src, const char *dst);                               /*!< 使用上下文指针重命名*/
        int (*rename)(const char *src, const char *dst);                                            /*!< 无上下文指针重命名*/
    };
    union {
        DIR* (*opendir_p)(void* ctx, const char* name);                                             /*!< 带有上下文指针的opendir*/
        DIR* (*opendir)(const char* name);                                                          /*!< 没有上下文指针的opendir*/
    };
    union {
        struct dirent* (*readdir_p)(void* ctx, DIR* pdir);                                          /*!< 带有上下文指针的readdir*/
        struct dirent* (*readdir)(DIR* pdir);                                                       /*!< 没有上下文指针的readdir*/
    };
    union {
        int (*readdir_r_p)(void* ctx, DIR* pdir, struct dirent* entry, struct dirent** out_dirent); /*!< 带有上下文指针的readdir_r*/
        int (*readdir_r)(DIR* pdir, struct dirent* entry, struct dirent** out_dirent);              /*!< 没有上下文指针的readdir_r*/
    };
    union {
        long (*telldir_p)(void* ctx, DIR* pdir);                                                    /*!< 带上下文指针的telldir*/
        long (*telldir)(DIR* pdir);                                                                 /*!< 不带上下文指针的telldir*/
    };
    union {
        void (*seekdir_p)(void* ctx, DIR* pdir, long offset);                                       /*!< 带有上下文指针的seekdir*/
        void (*seekdir)(DIR* pdir, long offset);                                                    /*!< 无上下文指针的seekdir*/
    };
    union {
        int (*closedir_p)(void* ctx, DIR* pdir);                                                    /*!< 带有上下文指针的closedir*/
        int (*closedir)(DIR* pdir);                                                                 /*!< 不带上下文指针的closedir*/
    };
    union {
        int (*mkdir_p)(void* ctx, const char* name, mode_t mode);                                   /*!< 带有上下文指针的mkdir*/
        int (*mkdir)(const char* name, mode_t mode);                                                /*!< 没有上下文指针的mkdir*/
    };
    union {
        int (*rmdir_p)(void* ctx, const char* name);                                                /*!< 带上下文指针的rmdir*/
        int (*rmdir)(const char* name);                                                             /*!< 不带上下文指针的rmdir*/
    };
#endif // CONFIG_VFS_SUPPORT_DIR
    union {
        int (*fcntl_p)(void* ctx, int fd, int cmd, int arg);                                        /*!< 带上下文指针的fcntl*/
        int (*fcntl)(int fd, int cmd, int arg);                                                     /*!< 不带上下文指针的fcntl*/
    };
    union {
        int (*ioctl_p)(void* ctx, int fd, int cmd, va_list args);                                   /*!< 带上下文指针的ioctl*/
        int (*ioctl)(int fd, int cmd, va_list args);                                                /*!< 没有上下文指针的ioctl*/
    };
    union {
        int (*fsync_p)(void* ctx, int fd);                                                          /*!< 带上下文指针的fsync*/
        int (*fsync)(int fd);                                                                       /*!< 不带上下文指针的fsync*/
    };
#ifdef CONFIG_VFS_SUPPORT_DIR
    union {
        int (*access_p)(void* ctx, const char *path, int amode);                                    /*!< 使用上下文指针访问*/
        int (*access)(const char *path, int amode);                                                 /*!< 无上下文指针访问*/
    };
    union {
        int (*truncate_p)(void* ctx, const char *path, off_t length);                               /*!< 使用上下文指针截断*/
        int (*truncate)(const char *path, off_t length);                                            /*!< 无上下文指针截断*/
    };
    union {
        int (*utime_p)(void* ctx, const char *path, const struct utimbuf *times);                   /*!< 带上下文指针的utilme*/
        int (*utime)(const char *path, const struct utimbuf *times);                                /*!< 不带上下文指针的utilme*/
    };
#endif // CONFIG_VFS_SUPPORT_DIR
#ifdef CONFIG_VFS_SUPPORT_TERMIOS
    union {
        int (*tcsetattr_p)(void *ctx, int fd, int optional_actions, const struct termios *p);       /*!< 带上下文指针的tcetattr*/
        int (*tcsetattr)(int fd, int optional_actions, const struct termios *p);                    /*!< 无上下文指针的tcsettr*/
    };
    union {
        int (*tcgetattr_p)(void *ctx, int fd, struct termios *p);                                   /*!< 带上下文指针的tcgetattr*/
        int (*tcgetattr)(int fd, struct termios *p);                                                /*!< 没有上下文指针的tcgetattr*/
    };
    union {
        int (*tcdrain_p)(void *ctx, int fd);                                                        /*!< 带上下文指针的tcdrain*/
        int (*tcdrain)(int fd);                                                                     /*!< 无上下文指针的tcdrain*/
    };
    union {
        int (*tcflush_p)(void *ctx, int fd, int select);                                            /*!< 带上下文指针的tcflush*/
        int (*tcflush)(int fd, int select);                                                         /*!< 无上下文指针的tcflush*/
    };
    union {
        int (*tcflow_p)(void *ctx, int fd, int action);                                             /*!< 带上下文指针的tcflow*/
        int (*tcflow)(int fd, int action);                                                          /*!< 没有上下文指针的tcflow*/
    };
    union {
        pid_t (*tcgetsid_p)(void *ctx, int fd);                                                     /*!< 带有上下文指针的tcgetsid*/
        pid_t (*tcgetsid)(int fd);                                                                  /*!< 没有上下文指针的tcgetsid*/
    };
    union {
        int (*tcsendbreak_p)(void *ctx, int fd, int duration);                                      /*!< 带上下文指针的tcsendbreak*/
        int (*tcsendbreak)(int fd, int duration);                                                   /*!< 无上下文指针的tcsendbreak*/
    };
#endif // CONFIG_VFS_SUPPORT_TERMIOS
#ifdef CONFIG_VFS_SUPPORT_SELECT
    /**start_select用于设置给定VFS中所需文件描述符的同步I/O复用*/
    esp_err_t (*start_select)(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, esp_vfs_select_sem_t sem, void **end_select_args);
    /**具有POSIX select（）功能的套接字FD的套接字选择功能；这应该只为套接字VFS设置*/
    int (*socket_select)(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);
    /**当从非套接字VFS驱动程序激活select时，由VFS调用以中断socket_select调用；仅为套接字驱动程序设置*/
    void (*stop_socket_select)(void *sem);
    /**stop_socket_select，可从ISR调用；仅为套接字驱动程序设置*/
    void (*stop_socket_select_isr)(void *sem, BaseType_t *woken);
    /**调用end_select以停止I/O多路复用并取消初始化start_select为给定VFS创建的环境*/
    void* (*get_socket_select_semaphore)(void);
    /**get_socket_select_semaphore返回套接字驱动程序中分配的信号量；仅为套接字驱动程序设置*/
    esp_err_t (*end_select)(void *end_select_args);
#endif // CONFIG_VFS_SUPPORT_SELECT
} esp_vfs_t;

/**
 * 为给定的路径前缀注册虚拟文件系统。
 *
 * @param base_path  与文件系统关联的文件路径前缀。必须是以零结尾的C字符串，可以为空。如果不为空，则长度必须最多为ESP_VFS_PATH_MAX个字符，且至少为2个字符。名称必须以“/”开头，不得以“/“结尾。例如，“/data”或“/dev/spi”是有效的。然后调用这些VFSE来处理文件路径，例如“/data/myfile.txt”或“/dev/spi/0”。在空base_path的特殊情况下，将注册“回退”VFS。这样的VFS将处理与任何其他注册的VFS不匹配的路径。
 * @param vfs  指向esp_vfs_t的指针，该结构将系统调用映射到文件系统驱动程序函数。VFS组件不承担此指针的所有权。
 * @param ctx  如果vfs->标志设置了ESP_vfs_FLAG_CONTEXT_PTR，则应将指针传递给vfs函数。否则，为NULL。
 *
 * @return  如果成功，则ESP_OK；如果注册了太多VFSE，则ESP_ERR_NO_MEM。
 */
esp_err_t esp_vfs_register(const char* base_path, const esp_vfs_t* vfs, void* ctx);


/**
 * 用于注册VFS的特殊情况函数，该VFS使用open（）以外的方法从间隔<min_fd；max_fd）。
 *
 * 这是一个专用函数，用于将LWIP套接字注册到VFS。
 *
 * @param vfs 指向esp_vfs_t的指针。含义与esp_vfs_register（）相同。
 * @param ctx 指向上下文结构的指针。含义与esp_vfs_register（）相同。
 * @param min_fd VFS将使用的最小文件描述符。
 * @param max_fd VFS将使用的文件描述符的上限（最大的文件描述符加上一个）。
 *
 * @return  如果成功，则ESP_OK；如果注册了太多VFS，则ESP_ERR_NO_MEM；如果文件描述符边界不正确，则ESP-ERR_INVALID_ARG。
 */
esp_err_t esp_vfs_register_fd_range(const esp_vfs_t *vfs, void *ctx, int min_fd, int max_fd);

/**
 * 用于注册使用open（）以外的方法打开新文件描述符的VFS的特殊情况函数。与esp_vfs_register_fd_range相比，此函数不预先注册文件描述符的间隔。稍后可以使用esp_vfs_register_fd注册文件描述符。
 *
 * @param vfs 指向esp_vfs_t的指针。含义与esp_vfs_register（）相同。
 * @param ctx 指向上下文结构的指针。含义与esp_vfs_register（）相同。
 * @param vfs_id 这里将写入VFS ID，该ID可以传递给esp_VFS_register_fd以注册文件描述符。
 *
 * @return  如果成功，则ESP_OK；如果注册了太多VFS，则ESP_ERR_NO_MEM；如果文件描述符边界不正确，则ESP-ERR_INVALID_ARG。
 */
esp_err_t esp_vfs_register_with_id(const esp_vfs_t *vfs, void *ctx, esp_vfs_id_t *vfs_id);

/**
 * 注销给定路径前缀的虚拟文件系统
 *
 * @param base_path  以前在esp_vfs_register调用中使用的文件前缀
 * @return 如果成功，则ESP_OK；如果尚未注册给定前缀的VFS，则ESP_ERR_INVALID_STATE
 */
esp_err_t esp_vfs_unregister(const char* base_path);

/**
 * 使用给定索引注销虚拟文件系统
 *
 * @param vfs_id  esp_VFS_register_with_ID返回的VFS ID
 * @return 如果成功，则ESP_OK；如果尚未注册给定索引的VFS，则ESP_ERR_INVALID_STATE
 */
esp_err_t esp_vfs_unregister_with_id(esp_vfs_id_t vfs_id);

/**
 * 用于为esp_VFS_register_with_id注册的VFS注册另一个文件描述符的特殊函数。
 *
 * @param vfs_id esp_VFS_register_with_id返回的VFS标识符。
 * @param fd 注册的文件描述符将写入此地址。
 *
 * @return  如果注册成功，则ESP_OK；如果注册的文件描述符太多，则ESP_ERR_NO_MEM；如果参数不正确，则ESP-ERR_INVALID_ARG。
 */
esp_err_t esp_vfs_register_fd(esp_vfs_id_t vfs_id, int *fd);

/**
 * 用于为esp_VFS_register_with_id注册的VFS注册具有给定local_fd的另一个文件描述符的特殊函数。
 *
 * @param vfs_id esp_VFS_register_with_id返回的VFS标识符。
 * @param local_fd 本地vfs中的fd。传递-1会将本地fd设置为（*fd）值。
 * @param permanent fd是否应视为permannet（关闭后不移除）
 * @param fd 注册的文件描述符将写入此地址。
 *
 * @return  如果注册成功，则ESP_OK；如果注册的文件描述符太多，则ESP_ERR_NO_MEM；如果参数不正确，则ESP-ERR_INVALID_ARG。
 */
esp_err_t esp_vfs_register_fd_with_local_fd(esp_vfs_id_t vfs_id, int local_fd, bool permanent, int *fd);

/**
 * 用于注销属于由esp_VFS_register_with_id注册的VFS的文件描述符的特殊功能。
 *
 * @param vfs_id esp_VFS_register_with_id返回的VFS标识符。
 * @param fd 应注销的文件描述符。
 *
 * @return  如果注册成功，则ESP_OK；如果参数不正确，则ESP_ERR_INVALID_ARG。
 */
esp_err_t esp_vfs_unregister_fd(esp_vfs_id_t vfs_id, int fd);

/**
 * 这些函数将在newlib系统调用表中使用。当需要使用任何系统调用时，newlib将调用它们。
 */
/**@{*/
ssize_t esp_vfs_write(struct _reent *r, int fd, const void * data, size_t size);
off_t esp_vfs_lseek(struct _reent *r, int fd, off_t size, int mode);
ssize_t esp_vfs_read(struct _reent *r, int fd, void * dst, size_t size);
int esp_vfs_open(struct _reent *r, const char * path, int flags, int mode);
int esp_vfs_close(struct _reent *r, int fd);
int esp_vfs_fstat(struct _reent *r, int fd, struct stat * st);
int esp_vfs_stat(struct _reent *r, const char * path, struct stat * st);
int esp_vfs_link(struct _reent *r, const char* n1, const char* n2);
int esp_vfs_unlink(struct _reent *r, const char *path);
int esp_vfs_rename(struct _reent *r, const char *src, const char *dst);
int esp_vfs_utime(const char *path, const struct utimbuf *times);
/**@}*/

/**
 * @brief 为VFS实现POSIX select（）功能的同步I/O多路复用
 * @param nfds      指定应检查的描述符范围。将在每个集合中检查第一个nfds描述符。
 * @param readfds   如果不为NULL，则指向一个描述符集，该描述符集在输入时指定应检查哪些描述符准备好读取，在输出时指示哪些描述符准备就绪读取。
 * @param writefds  如果不为NULL，则指向一个描述符集，该描述符集在输入时指定应检查哪些描述符准备好写入，在输出时指示哪些描述符准备就绪写入。
 * @param errorfds  如果不为NULL，则指向一个描述符集，该描述符集在输入时指定应检查哪些描述符的错误条件，在输出时指示哪些描述符具有错误条件。
 * @param timeout   如果不为NULL，则指向timeval结构，该结构指定函数应超时并返回的时间段。如果为NULL，则函数不会超时。请注意，超时时间将四舍五入到系统刻度并递增一。
 *
 * @return      描述符集合中设置的描述符数，或发生错误（由errno指定）时为-1。
 */
int esp_vfs_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);

/**
 * @brief 来自VFS驱动程序的关于读/写/错误条件的通知
 *
 * 当VFS驱动程序检测到前一次调用start_select所请求的读/写/错误条件时，调用此函数。
 *
 * @param sem start_select调用传递给驱动程序的信号量结构
 */
void esp_vfs_select_triggered(esp_vfs_select_sem_t sem);

/**
 * @brief 来自VFS驱动程序的有关读/写/错误条件的通知（ISR版本）
 *
 * 当VFS驱动程序检测到前一次调用start_select所请求的读/写/错误条件时，调用此函数。
 *
 * @param sem start_select调用传递给驱动程序的信号量结构
 * @param woken 如果函数唤醒具有较高优先级的任务，则设置为pdTRUE
 */
void esp_vfs_select_triggered_isr(esp_vfs_select_sem_t sem, BaseType_t *woken);

/**
 *
 * @brief 实现POSIX pread（）的VFS层
 *
 * @param fd         用于读取的文件描述符
 * @param dst        指向将写入输出的缓冲区的指针
 * @param size       要读取的字节数
 * @param offset     读取的起始偏移
 *
 * @return           正返回值表示读取的字节数-1表示失败时返回，并相应地设置errno。
 */
ssize_t esp_vfs_pread(int fd, void *dst, size_t size, off_t offset);

/**
 *
 * @brief 实现POSIX pwrite（）的VFS层
 *
 * @param fd         用于写入的文件描述符
 * @param src        指向将从中读取输出的缓冲区的指针
 * @param size       要写入的字节数
 * @param offset     写入的起始偏移量
 *
 * @return           正返回值表示写入的字节数-1表示失败时返回，并相应地设置errno。
 */
ssize_t esp_vfs_pwrite(int fd, const void *src, size_t size, off_t offset);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif //__ESP_VFS_H__

