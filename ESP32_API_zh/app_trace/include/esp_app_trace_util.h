/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef ESP_APP_TRACE_UTIL_H_
#define ESP_APP_TRACE_UTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "freertos/FreeRTOS.h"
#include "esp_err.h"
#include "esp_timer.h"

/**无限等待超时*/
#define ESP_APPTRACE_TMO_INFINITE               ((uint32_t)-1)

/** 保存测量时间间隔所需数据的结构。
 *
 *  通过esp_apptrace_tmo_init（）进行初始化后，用户需要定期调用esp_apptrack_tmo_check（）来检查过期超时。
 */
typedef struct {
    int64_t   start;   ///<时间间隔开始（以美国为单位）
    int64_t   tmo;     ///<超时值（以美国为单位）
    int64_t   elapsed; ///<经过的时间（以美国为单位）
} esp_apptrace_tmo_t;

/**
 * @brief 初始化超时结构。
 *
 * @param tmo       指向要初始化的超时结构的指针。
 * @param user_tmo  超时值（单位：us）。使用ESP_APPTRACE_TMO_INFINITE等待。
*/
static inline void esp_apptrace_tmo_init(esp_apptrace_tmo_t *tmo, uint32_t user_tmo)
{
    tmo->start = esp_timer_get_time();
    tmo->tmo = user_tmo == ESP_APPTRACE_TMO_INFINITE ? (int64_t)-1 : (int64_t)user_tmo;
    tmo->elapsed = 0;
}

/**
 * @brief 检查过期超时。
 *
 * @param tmo 指向超时结构的指针。
 *
 * @return 直到tmo的剩余人数。
 */
esp_err_t esp_apptrace_tmo_check(esp_apptrace_tmo_t *tmo);

static inline uint32_t esp_apptrace_tmo_remaining_us(esp_apptrace_tmo_t *tmo)
{
    return tmo->tmo != (int64_t)-1 ? (tmo->elapsed - tmo->tmo) : ESP_APPTRACE_TMO_INFINITE;
}

/**跟踪模块同步锁*/
typedef struct {
    portMUX_TYPE mux;
    unsigned int_state;
} esp_apptrace_lock_t;

/**
 * @brief 初始化锁结构。
 *
 * @param lock 指向要初始化的锁结构的指针。
 */
static inline void esp_apptrace_lock_init(esp_apptrace_lock_t *lock)
{
    portMUX_INITIALIZE(&lock->mux);
    lock->int_state = 0;
}

/**
 * @brief 尝试在指定的时间段内获取锁定。
 *
 * @param lock 指向锁结构的指针。
 * @param tmo  指向超时结构的指针。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_apptrace_lock_take(esp_apptrace_lock_t *lock, esp_apptrace_tmo_t *tmo);

/**
 * @brief 释放锁。
 *
 * @param lock 指向锁结构的指针。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_apptrace_lock_give(esp_apptrace_lock_t *lock);

/** 环形缓冲区控制结构。
 *
 * @note 为了应用程序跟踪模块的目的，如果没有足够的空间用于用户数据，并且可以包装写指针，则可以暂时缩小当前环形缓冲区的大小，以便提供具有请求大小的缓冲区。
 */
typedef struct {
    uint8_t *data;      ///<指向数据存储的指针
    volatile uint32_t size;      ///<数据存储的大小
    volatile uint32_t cur_size;  ///<数据存储的当前大小
    volatile uint32_t rd;        ///<读取指针
    volatile uint32_t wr;        ///<写入指针
} esp_apptrace_rb_t;

/**
 * @brief 初始化环形缓冲区控制结构。
 *
 * @param rb   指向要初始化的环形缓冲区结构的指针。
 * @param data 指向用作环形缓冲区数据存储的缓冲区的指针。
 * @param size 用作环形缓冲区数据存储的缓冲区大小。
 */
static inline void esp_apptrace_rb_init(esp_apptrace_rb_t *rb, uint8_t *data, uint32_t size)
{
    rb->data = data;
    rb->size = rb->cur_size = size;
    rb->rd = 0;
    rb->wr = 0;
}

/**
 * @brief 在环形缓冲区中分配内存块。
 *
 * @param rb   指向环形缓冲区结构的指针。
 * @param size 要分配的内存大小。
 *
 * @return 指向已分配内存的指针，失败时为NULL。
 */
uint8_t *esp_apptrace_rb_produce(esp_apptrace_rb_t *rb, uint32_t size);

/**
 * @brief 消耗环形缓冲区中的内存块。
 *
 * @param rb   指向环形缓冲区结构的指针。
 * @param size 要消耗的内存大小。
 *
 * @return 指向已消耗内存块的指针，如果失败，则返回NULL。
 */
uint8_t *esp_apptrace_rb_consume(esp_apptrace_rb_t *rb, uint32_t size);

/**
 * @brief 获取一次调用esp_apptrace_rb_consumer（）可消耗的内存大小。
 *
 * @param rb 指向环形缓冲区结构的指针。
 *
 * @return 可消耗的内存大小。
 *
 * @note 由于读取指针换行，返回的大小可能小于可用数据的总大小。
 */
uint32_t esp_apptrace_rb_read_size_get(esp_apptrace_rb_t *rb);

/**
 * @brief 获取通过调用esp_apptrace_rb_produce（）可以生成的内存大小。
 *
 * @param rb 指向环形缓冲区结构的指针。
 *
 * @return 可生成的内存大小。
 *
 * @note 由于写指针包装，返回的大小可能小于可用数据的总大小。
 */
uint32_t esp_apptrace_rb_write_size_get(esp_apptrace_rb_t *rb);

int esp_apptrace_log_lock(void);
void esp_apptrace_log_unlock(void);

#define ESP_APPTRACE_LOG( format, ... )   \
    do { \
        esp_apptrace_log_lock(); \
        esp_rom_printf(format, ##__VA_ARGS__); \
        esp_apptrace_log_unlock(); \
    } while(0)

#define ESP_APPTRACE_LOG_LEV( _L_, level, format, ... )   \
    do { \
        if (LOG_LOCAL_LEVEL >= level) { \
            ESP_APPTRACE_LOG(LOG_FORMAT(_L_, format), esp_log_early_timestamp(), TAG, ##__VA_ARGS__); \
        } \
    } while(0)

#define ESP_APPTRACE_LOGE( format, ... )  ESP_APPTRACE_LOG_LEV(E, ESP_LOG_ERROR, format, ##__VA_ARGS__)
#define ESP_APPTRACE_LOGW( format, ... )  ESP_APPTRACE_LOG_LEV(W, ESP_LOG_WARN, format, ##__VA_ARGS__)
#define ESP_APPTRACE_LOGI( format, ... )  ESP_APPTRACE_LOG_LEV(I, ESP_LOG_INFO, format, ##__VA_ARGS__)
#define ESP_APPTRACE_LOGD( format, ... )  ESP_APPTRACE_LOG_LEV(D, ESP_LOG_DEBUG, format, ##__VA_ARGS__)
#define ESP_APPTRACE_LOGV( format, ... )  ESP_APPTRACE_LOG_LEV(V, ESP_LOG_VERBOSE, format, ##__VA_ARGS__)
#define ESP_APPTRACE_LOGO( format, ... )  ESP_APPTRACE_LOG_LEV(E, ESP_LOG_NONE, format, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif //ESP_APP_TRACE_UTIL_H_

