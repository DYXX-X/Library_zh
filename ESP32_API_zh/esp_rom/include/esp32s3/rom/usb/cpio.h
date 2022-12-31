// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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


/**
 * 存档以解析newc和crc格式的cpio数据。通过例如find.|cpio-o-H newc>archive.cpio生成这样的cpio存档
 */

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CPIO_MODE_FILETYPE_MASK     0xF000
#define CPIO_MODE_FILETYPE_SOCKET   0xC000
#define CPIO_MODE_FILETYPE_SYMLINK  0xA000
#define CPIO_MODE_FILETYPE_REGULAR  0x8000
#define CPIO_MODE_FILETYPE_BLOCKDEV 0x6000
#define CPIO_MODE_FILETYPE_DIR      0x4000
#define CPIO_MODE_FILETYPE_CHARDEV  0x2000
#define CPIO_MODE_FILETYPE_FIFO     0x1000
#define CPIO_MODE_SUID              0x0800
#define CPIO_MODE_SGID              0x0400
#define CPIO_MODE_STICKY            0x0200

typedef struct {
    size_t filesize;
    char *name;
    uint32_t mode;
    uint32_t check;
} cpio_file_t;

typedef enum {
    CPIO_RET_MORE = 0,
    CPIO_RET_DONE,
    CPIO_RET_ERR
} cpio_ret_t;

typedef struct cpio_handle_data_t cpio_handle_data_t;
typedef cpio_handle_data_t *cpio_handle_t;

typedef enum {
    CPIO_RSN_FILE_ALL = 0,
    CPIO_RSN_FILE_INITIAL,
    CPIO_RSN_FILE_MORE,
    CPIO_RSN_FILE_END
} cpio_callback_reason_t;


/**
 * cpio文件数据的回调。
 *
 * 库将调用此回调以指示文件的数据可用。
 *
 * 对于cpio存档中完全适合内部缓冲区的文件，或者当没有可用的内部缓冲区时，完全包含在馈送到cpio_feed（）的缓冲区中，此回调只调用一次，原因为cpio_RNS_FILE_ALL。fileinfo将包含该特定文件的信息（名称、大小…），buff_offset将为0，buff_len是文件大小，buff包含该文件的所有信息。
 *
 * 对于不适合缓冲区的文件，将多次调用此回调。初始时间，原因=CPIO_RSN_FILE_initial，此时CPIO_RSN _FILE_more有更多数据可用，最后是CPIO_RSN_FILE_END。对于这些调用，fileinfo将再次包含文件信息。buff将是文件中包含的信息，偏移量为buff_offset，缓冲区的长度为bufflen。
 *
 * 该库保证将所有文件数据连续地提供给回调，因此在同一文件中，来自调用的buff_offset将始终是来自之前调用的（buff_offset+buff_len）。如果cpio_start为
 *
 * 库还保证cpio存档中的每个文件都将使用cpio_RSN_ALL生成一个回调调用，或使用顺序为cpio_RSN _file_INITIAL、0或更多cpio_RS_file_more的多个回调调用以及最后一个cpio_RSN_file_END。
 *
 * 当一个非零缓冲区大小传递给cpio_start时，库保证所有原因为cpio_RSN_FILE_INITIAL和cpio_RSN _FILE_MORE的回调调用都将有一个缓冲区，该缓冲区正好填充了这个字节数。
 *
 */
typedef void (*cpio_callback_t)(cpio_callback_reason_t reason, cpio_file_t *fileinfo, size_t buff_offset, size_t buff_len, char *buff, void *arg);


/**
 * @brief      初始化cpio句柄。
 *
 * 调用此命令开始解析cpio存档。您可以在此处设置处理文件/数据的回调。
 *
 * @param  callback 将处理cpio存档中文件数据的回调
 *
 * @param  cbarg 用户提供的参数。将使用此作为参数调用回调。
 *
 * @param  buflen 使用的内部缓冲区长度。如果该值为零，则调用回调时，调用cpio_feed（）的人将使用提供给cpio库的数据缓冲区中的数据。因为这个库没有缓冲区的电源，所以回调一次只能传递1字节，最多只能传递INT_MAX字节。如果此值为非零，则库将分配此大小的内部缓冲区。所有cpio_feed（）-调用都将被重新缓冲，并且只要文件中有足够的数据来填充，就可以保证只使用缓冲区中的这么多字节来调用回调。
 *
 * @param memchunk 用于分配所有内容（句柄、I/O缓冲区、文件名缓冲区）的内存块。最小大小（估计值）为160+buflen+sizeof（最大文件名/路径）。
 * @param memchunklen 内存块的大小
 *
 * @return
 *     -成功：指向cpio句柄的指针
 *     -错误：NULL
 *
 */
cpio_handle_t cpio_start(cpio_callback_t callback, void *cbarg, size_t buflen, void *memchunk, int memchunklen);

/**
 * @brief      将cpio存档中的数据输入到库中
 *
 * 此例程用于将cpio存档的连续数据馈送到库中。在处理过程中，库可以根据需要调用回调函数一次或多次。
 *
 * @param  cpio 通过调用cpio_start（）获得的句柄
 *
 * @param  buffer 指向包含cpio存档数据的缓冲区的指针
 *
 * @param  len 缓冲区长度（字节）
 *
 * @return
 *     -CPIO_RET_MORE:CPIO存档尚未完成，请输入更多数据。
 *     -CPIO_RET_DONE:CPUI存档已完成。
 *     -CPIO_RET_ERR：无效的CPIO存档数据；解码中止。
 *
 */
cpio_ret_t cpio_feed(cpio_handle_t cpio, char *buffer, int len);

/**
 * @brief      表示没有更多的cpio数据要输入存档
 *
 * 当源数据耗尽时，将调用此调用。通常，库可以通过查找结束标记来查找cpio存档的结束，
 *
 * @param  timer_conf LEDC计时器配置结构的指针
 *
 *
 * @return
 *     -CPIO_RET_DONE成功
 *     -CPIO存档无效时的CPIO_RET_ERR
 *
 */
cpio_ret_t cpio_done(cpio_handle_t cpio);


/**
 * @brief      释放为cpio句柄分配的内存。
 *
 * @param  cpio 通过调用cpio_start（）获得的句柄
 *
 * @return
 *     -CPIO_RET_DONE成功
 *
 */
cpio_ret_t cpio_destroy(cpio_handle_t cpio);

#ifdef __cplusplus
}
#endif

