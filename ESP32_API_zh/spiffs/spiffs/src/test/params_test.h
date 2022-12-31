/*
 * 参数_测试.h
 *
 *  创建日期：2013年5月26日作者：peter
 */

#ifndef PARAMS_TEST_H_
#define PARAMS_TEST_H_

//////////////// TEST PARAMS ////////////////

// 默认测试总模拟spi闪存大小
#define PHYS_FLASH_SIZE       (16*1024*1024)
// 默认测试溢出文件系统大小
#define SPIFFS_FLASH_SIZE     (2*1024*1024)
// 模拟spi闪存中的默认测试spiffs文件系统偏移
#define SPIFFS_PHYS_ADDR      (4*1024*1024)
// 默认测试扇区大小
#define SECTOR_SIZE         65536
// 默认测试逻辑块大小
#define LOG_BLOCK           (SECTOR_SIZE*2)
// 默认测试逻辑页面大小
#define LOG_PAGE            (SECTOR_SIZE/256)
// filedescs的默认测试数
#define DEFAULT_NUM_FD            16
// 缓存页的默认测试数
#define DEFAULT_NUM_CACHE_PAGES   8

// 测试时，测试台创建参考文件以进行比较
// 实际硬盘驱动器。默认情况下，将这些设置在ram驱动器上以提高速度。
#define TEST_PATH "/dev/shm/spiffs/test-data/"

#define ASSERT(c, m) real_assert((c),(m), __FILE__, __LINE__);
void real_assert(int c, const char *n, const char *file, int l);

/////////// SPIFFS BUILD CONFIG  ////////////

// 使用文件系统魔术进行测试
#ifndef SPIFFS_USE_MAGIC
#define SPIFFS_USE_MAGIC    1
#endif
// 使用文件系统magic长度进行测试
#ifndef SPIFFS_USE_MAGIC_LENGTH
#define SPIFFS_USE_MAGIC_LENGTH   1
#endif
// 在回调中使用额外参数进行测试
#ifndef SPIFFS_HAL_CALLBACK_EXTRA
#define SPIFFS_HAL_CALLBACK_EXTRA       1
#endif
// 使用文件句柄偏移量进行测试
#ifndef SPIFFS_FILEHDL_OFFSET
#define SPIFFS_FILEHDL_OFFSET           1
// 使用此偏移
#define TEST_SPIFFS_FILEHDL_OFFSET      0x1000
#endif

#ifdef NO_TEST
#define SPIFFS_LOCK(fs)
#define SPIFFS_UNLOCK(fs)
#else
struct spiffs_t;
extern void test_lock(struct spiffs_t *fs);
extern void test_unlock(struct spiffs_t *fs);
#define SPIFFS_LOCK(fs)   test_lock(fs)
#define SPIFFS_UNLOCK(fs) test_unlock(fs)
#endif

// dbg输出
#define SPIFFS_DBG(_f, ...) //打印f（“\x1b[32m”_f“\x1b[0m”，##__VA_ARGS__）
#define SPIFFS_API_DBG(_f, ...) //printf（“\n\x1b[1m\x1b[7m”_f“\x1b[0m”，##__VA_ARGS__）
#define SPIFFS_GC_DBG(_f, ...) //打印f（“\x1b[36m”_f“\x1b[0m”，##__VA_ARGS__）
#define SPIFFS_CACHE_DBG(_f, ...) //打印f（“\x1b[33m”_f“\x1b[0m”，##__VA_ARGS__）
#define SPIFFS_CHECK_DBG(_f, ...) //打印f（“\x1b[31m”_f“\x1b[0m”，##__VA_ARGS__）

// 所需类型
typedef signed int s32_t;
typedef unsigned int u32_t;
typedef signed short s16_t;
typedef unsigned short u16_t;
typedef signed char s8_t;
typedef unsigned char u8_t;

#endif /* PARAMS_TEST_H_ */

