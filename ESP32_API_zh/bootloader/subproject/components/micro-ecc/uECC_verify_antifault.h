/*
 * SPDX文件版权文本：2014，Kenneth MacKay
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * SPDX文件贡献者：2020-2021浓缩咖啡系统（上海）有限公司
 */
#pragma once
#include "uECC.h"

/* 版本uECC_verify（），如果签名有效，也会将message_hash复制到verified_hash，并以更难使用错误注入进行攻击的方式执行。
*/
int uECC_verify_antifault(const uint8_t *public_key,
                          const uint8_t *message_hash,
                          unsigned hash_size,
                          const uint8_t *signature,
                          uECC_Curve curve,
                          uint8_t *verified_hash);

