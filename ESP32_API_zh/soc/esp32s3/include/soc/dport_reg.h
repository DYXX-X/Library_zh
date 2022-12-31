/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include "soc.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "interrupt_reg.h"
#include "system_reg.h"
#include "sensitive_reg.h"
#include "soc.h"

#define DPORT_DATE_REG SYSTEM_DATE_REG

#ifndef __ASSEMBLER__
#include "dport_access.h"
#endif

#ifdef __cplusplus
}
#endif

