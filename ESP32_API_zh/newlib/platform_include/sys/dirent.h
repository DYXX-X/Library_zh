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

#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * 此头文件提供与POSIX兼容的目录访问数据类型定义。从newlib 3.3开始，相关函数在'dirent中定义。h’与newlib绑定。看见http://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html以供参考。
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 不透明目录结构
 */
typedef struct {
    uint16_t dd_vfs_idx; /*!< VFS索引，不供应用程序使用*/
    uint16_t dd_rsv;     /*!< 保留用于将来扩展的字段*/
    /* 其余字段由VFS实现定义*/
} DIR;

/**
 * @brief 目录条目结构
 */
struct dirent {
    int d_ino;          /*!< 文件编号*/
    uint8_t d_type;     /*!< 未在POSIX中定义，但在BSD和Linux中存在*/
#define DT_UNKNOWN  0
#define DT_REG      1
#define DT_DIR      2
#if __BSD_VISIBLE
#define MAXNAMLEN 255
    char d_name[MAXNAMLEN+1];   /*!< 以零结尾的文件名*/
#else
    char d_name[256];
#endif
};

DIR* opendir(const char* name);
struct dirent* readdir(DIR* pdir);
long telldir(DIR* pdir);
void seekdir(DIR* pdir, long loc);
void rewinddir(DIR* pdir);
int closedir(DIR* pdir);
int readdir_r(DIR* pdir, struct dirent* entry, struct dirent** out_dirent);

#ifdef __cplusplus
}
#endif

