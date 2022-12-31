/* ==========================================
    CMock项目-C版自动模拟生成版权所有（C）2007 Mike Karlesky，Mark VanderVoord，Greg Williams[根据MIT许可证发布。请参阅License.txt了解详细信息]
========================================== */

#ifndef CMOCK_FRAMEWORK_H
#define CMOCK_FRAMEWORK_H

#include "cmock_internals.h"

#define CMOCK_VERSION_MAJOR    2
#define CMOCK_VERSION_MINOR    5
#define CMOCK_VERSION_BUILD    2
#define CMOCK_VERSION          ((CMOCK_VERSION_MAJOR << 16) | (CMOCK_VERSION_MINOR << 8) | CMOCK_VERSION_BUILD)

/* 应该足够大以索引CMOCK_MEM_MAX的整个范围*/
#ifndef CMOCK_MEM_INDEX_TYPE
#include <stddef.h>
#define CMOCK_MEM_INDEX_TYPE  size_t
#endif

#define CMOCK_GUTS_NONE   (0)

/*-------------------------------------------------------
 * 内存API
 *-------------------------------------------------------*/
CMOCK_MEM_INDEX_TYPE  CMock_Guts_MemNew(CMOCK_MEM_INDEX_TYPE size);
CMOCK_MEM_INDEX_TYPE  CMock_Guts_MemChain(CMOCK_MEM_INDEX_TYPE root_index, CMOCK_MEM_INDEX_TYPE obj_index);
CMOCK_MEM_INDEX_TYPE  CMock_Guts_MemNext(CMOCK_MEM_INDEX_TYPE previous_item_index);
CMOCK_MEM_INDEX_TYPE  CMock_Guts_MemEndOfChain(CMOCK_MEM_INDEX_TYPE root_index);

void*                 CMock_Guts_GetAddressFor(CMOCK_MEM_INDEX_TYPE index);

CMOCK_MEM_INDEX_TYPE CMock_Guts_MemBytesCapacity(void);
CMOCK_MEM_INDEX_TYPE  CMock_Guts_MemBytesFree(void);
CMOCK_MEM_INDEX_TYPE  CMock_Guts_MemBytesUsed(void);
void                  CMock_Guts_MemFreeAll(void);
void                  CMock_Guts_MemFreeFinal(void);

#endif /* CMOCK_FRAMEWORK_H结束*/

