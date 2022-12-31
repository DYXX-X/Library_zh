// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
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

/**
 * @file 测试_ atfs_通用.h
 * @brief SDMMC上FAT和WL上FAT测试的通用例程
 */

#define HEAP_SIZE_CAPTURE(heap_size)  \
     heap_size = esp_get_free_heap_size();

#define HEAP_SIZE_CHECK(heap_size, tolerance) \
    do {\
        size_t final_heap_size = esp_get_free_heap_size(); \
        if (final_heap_size < heap_size - tolerance) { \
            printf("Initial heap size: %d, final: %d, diff=%d\n", heap_size, final_heap_size, heap_size - final_heap_size); \
        } \
    } while(0)

const char* fatfs_test_hello_str;
const char* fatfs_test_hello_str_utf;

void test_fatfs_create_file_with_text(const char* name, const char* text);

void test_fatfs_overwrite_append(const char* filename);

void test_fatfs_read_file(const char* filename);

void test_fatfs_read_file_utf_8(const char* filename);

void test_fatfs_pread_file(const char* filename);

void test_fatfs_pwrite_file(const char* filename);

void test_fatfs_open_max_files(const char* filename_prefix, size_t files_count);

void test_fatfs_lseek(const char* filename);

void test_fatfs_truncate_file(const char* path);

void test_fatfs_stat(const char* filename, const char* root_dir);

void test_fatfs_utime(const char* filename, const char* root_dir);

void test_fatfs_unlink(const char* filename);

void test_fatfs_link_rename(const char* filename_prefix);

void test_fatfs_concurrent(const char* filename_prefix);

void test_fatfs_mkdir_rmdir(const char* filename_prefix);

void test_fatfs_can_opendir(const char* path);

void test_fatfs_opendir_readdir_rewinddir(const char* dir_prefix);

void test_fatfs_opendir_readdir_rewinddir_utf_8(const char* dir_prefix);

void test_fatfs_rw_speed(const char* filename, void* buf, size_t buf_size, size_t file_size, bool write);

