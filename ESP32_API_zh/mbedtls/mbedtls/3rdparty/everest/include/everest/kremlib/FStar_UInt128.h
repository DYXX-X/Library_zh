/* 版权所有（c）INRIA和Microsoft Corporation。保留所有权利。根据Apache 2.0许可证许可。*/

/* 此文件由KreMLin生成<https://github.com/FStarLang/kremlin>KreMLin调用：../krml-fc89-fparentthesis-fno shadow-header/mnt/e/everest/verify/hdrB9w-minimal-fparentThesis-fcurly大括号-fno shade-header版权标头。txt-minimal-tmpdir dist/uint128-跳过编译-提取uints-添加include＜inttypes。h> -add include<stdbool。h> -add include“kremlin/internal/types.h”-bundle FStar。UInt128=已提取/prims。krml提取/FStar_Servasives_Native。krml提取/FStar_。krml提取/FStar_Mul。krml提取/FStar_Squash。krml提取/FStar_经典。krml提取/FStar_StrongExcludedMiddle。krml提取/FStar_FunctionalExtensionity。krml提取/FStar_List_Tot_Base。krml提取/FStar_List_Tot_Properties。krml提取/FStar_List_Tot。krml提取/FStar_Seq_Base。krml提取/FStar_Seq_Properties。krml提取/FStar_Seq。krml提取/FStar_Math_Lib。krml提取/FStar_Math_Lemmas。krml提取/FStar_BitVector。krml提取/FStar_Int。krml提取/FStar_Int32.krml提取/FStar_Int。krml提取/FStar_Int16.krml提取/FStar_Prerder。krml提取/FStar_host。krml提取/FStar_RasedLogic。krml提取/FStar_Int64.krml提取/FStar_Set。krml提取/FStar_位置扩展性。krml提取/FStar_医疗扩展性。krml提取/FStar_Set。krml提取/FStar_Monotonic_Heap。krml提取/FSrar_Heap。krml提取/FStar_Map。krml提取/FStar_Monotonic_HyperHeap。krml提取/FStar_Monotonic_HyperStack。krml提取/FStar_TyperStack。krml提取/FStar_Monotonic_见证。krml提取/FStar_TyperStack_ST。krml提取/FStar_TyperStack_All。krml提取/FStar_Date。krml提取/FStar_Universe。krml提取/FStar_GSet。krml提取/FStar_ModifiesGen。krml提取/LowStar_Monotonic_Buffer。krml提取/LowStar_Buffer。krml提取/Spec_Loops。krml提取/LowStar_BufferOps。krml提取/C_ Loops。krml提取/FStar_Int8.krml提取-FStar_Kremlin_Endianness。krml提取/FStar_Int63.krml提取-FStar_Exn。krml提取/FStar_。krml提取/FStar_ All。krml提取/FStar_Dyn。krml提取/FStar_Int63.krml提取/FStar_Int64.krml提取/Pstar_Int32.krml提取-FStar_Int8.krml提取/FStar_Int16.krml提取/FStar_Int_Cast。krml提取/FStar_Int128.krml提取/C_ Endianness。krml提取/FStar_List。krml提取/FStar_Float。krml提取/FStar_IO。krml提取/C。krml提取/FSrar_Char。krml提取/FStar_String。krml提取/LowStar_Modifies。krml提取/C_String。krml提取/FStar_Bytes。krml提取/FStar_TyperStack_IO。krml提取/C_失败。krml提取/TestLib。krml提取/FStar_Int_Cast_Full。krml F版本：059db0c8 KreMLin版本：916c37ac
 */



#ifndef __FStar_UInt128_H
#define __FStar_UInt128_H


#include <inttypes.h>
#include <stdbool.h>
#include "kremlin/internal/types.h"

uint64_t FStar_UInt128___proj__Mkuint128__item__low(FStar_UInt128_uint128 projectee);

uint64_t FStar_UInt128___proj__Mkuint128__item__high(FStar_UInt128_uint128 projectee);

typedef FStar_UInt128_uint128 FStar_UInt128_t;

FStar_UInt128_uint128 FStar_UInt128_add(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128
FStar_UInt128_add_underspec(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128 FStar_UInt128_add_mod(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128 FStar_UInt128_sub(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128
FStar_UInt128_sub_underspec(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128 FStar_UInt128_sub_mod(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128 FStar_UInt128_logand(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128 FStar_UInt128_logxor(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128 FStar_UInt128_logor(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128 FStar_UInt128_lognot(FStar_UInt128_uint128 a);

FStar_UInt128_uint128 FStar_UInt128_shift_left(FStar_UInt128_uint128 a, uint32_t s);

FStar_UInt128_uint128 FStar_UInt128_shift_right(FStar_UInt128_uint128 a, uint32_t s);

bool FStar_UInt128_eq(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

bool FStar_UInt128_gt(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

bool FStar_UInt128_lt(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

bool FStar_UInt128_gte(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

bool FStar_UInt128_lte(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128 FStar_UInt128_eq_mask(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128 FStar_UInt128_gte_mask(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b);

FStar_UInt128_uint128 FStar_UInt128_uint64_to_uint128(uint64_t a);

uint64_t FStar_UInt128_uint128_to_uint64(FStar_UInt128_uint128 a);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Plus_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Plus_Question_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Plus_Percent_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Subtraction_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Subtraction_Question_Hat)(
  FStar_UInt128_uint128 x0,
  FStar_UInt128_uint128 x1
);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Subtraction_Percent_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Amp_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Hat_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Bar_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Less_Less_Hat)(FStar_UInt128_uint128 x0, uint32_t x1);

extern FStar_UInt128_uint128
(*FStar_UInt128_op_Greater_Greater_Hat)(FStar_UInt128_uint128 x0, uint32_t x1);

extern bool (*FStar_UInt128_op_Equals_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern bool
(*FStar_UInt128_op_Greater_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern bool (*FStar_UInt128_op_Less_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern bool
(*FStar_UInt128_op_Greater_Equals_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

extern bool
(*FStar_UInt128_op_Less_Equals_Hat)(FStar_UInt128_uint128 x0, FStar_UInt128_uint128 x1);

FStar_UInt128_uint128 FStar_UInt128_mul32(uint64_t x, uint32_t y);

FStar_UInt128_uint128 FStar_UInt128_mul_wide(uint64_t x, uint64_t y);

#define __FStar_UInt128_H_DEFINED
#endif

