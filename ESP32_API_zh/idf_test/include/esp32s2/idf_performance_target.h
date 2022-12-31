/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#define IDF_PERFORMANCE_MIN_AES_CBC_THROUGHPUT_MBSEC                            43.0
#define IDF_PERFORMANCE_MIN_AES_GCM_CRYPT_TAG_THROUGHPUT_MBSEC                  30.0
#define IDF_PERFORMANCE_MIN_AES_GCM_UPDATE_THROUGHPUT_MBSEC                     2.1

// 240MHz时的SHA256硬件吞吐量，阈值设置低于最坏情况
#define IDF_PERFORMANCE_MIN_SHA256_THROUGHPUT_MBSEC                             90.0
// esp_sha（）从RAM处理32KB输入数据的时间
#define IDF_PERFORMANCE_MAX_TIME_SHA1_32KB                                      900
#define IDF_PERFORMANCE_MAX_TIME_SHA512_32KB                                    900

#define IDF_PERFORMANCE_MAX_RSA_2048KEY_PUBLIC_OP                               13500
#define IDF_PERFORMANCE_MAX_RSA_2048KEY_PRIVATE_OP                              130000
#define IDF_PERFORMANCE_MAX_RSA_3072KEY_PUBLIC_OP                               36000
#define IDF_PERFORMANCE_MAX_RSA_3072KEY_PRIVATE_OP                              400000
#define IDF_PERFORMANCE_MAX_RSA_4096KEY_PUBLIC_OP                               62000
#define IDF_PERFORMANCE_MAX_RSA_4096KEY_PRIVATE_OP                              800000

#define IDF_PERFORMANCE_MAX_SPI_PER_TRANS_NO_POLLING                            32
#define IDF_PERFORMANCE_MAX_SPI_PER_TRANS_NO_POLLING_NO_DMA                     30

