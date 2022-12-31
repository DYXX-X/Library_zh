#pragma once

#include "esp_attr.h"

#ifdef __cplusplus
extern "C" {
#endif

#define portBYTE_ALIGNMENT			16

/* 类型定义。*/
#define portCHAR		uint8_t
#define portFLOAT		float
#define portDOUBLE		double
#define portLONG		int32_t
#define portSHORT		int16_t
#define portSTACK_TYPE	uint8_t
#define portBASE_TYPE	int
// 中断模块将屏蔽优先级低于阈值的中断
#define RVHAL_EXCM_LEVEL    4

typedef portSTACK_TYPE			StackType_t;
typedef portBASE_TYPE			BaseType_t;
typedef unsigned portBASE_TYPE	UBaseType_t;
typedef uint32_t TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffffffffUL

typedef int portMUX_TYPE;

#ifdef __cplusplus
}
#endif

